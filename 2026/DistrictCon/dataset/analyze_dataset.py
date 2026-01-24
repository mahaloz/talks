#!/usr/bin/env python3
"""
Dataset analysis script for extracting decompilations from nginx CPVs.

This script reads the dataset TOML, and for each CPV:
- Grabs the crash.txt file
- Uses the nginx binary to decompile functions with angr, ghidra, and ida
- Saves decompilations to dec_<decompiler>.c files in each CPV folder
"""

import argparse
import json
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Any, Dict, List, Optional

import openai
import toml
from rich.console import Console
from rich.progress import Progress, SpinnerColumn, TextColumn, BarColumn, TaskProgressColumn
from rich.table import Table
from rich.panel import Panel
from rich import box

import re

from mana.tools.decompiler import Decompiler
from patchery.generator import LLMPlanPatchGenerator
from patchery.data import PoI, PoICluster, Program, ProgramAlert
from patchery.kumushi.code_parsing import CodeFunction


def parse_decompiled_functions(
    dec_code: str,
    file_path: str
) -> Dict[str, Dict]:
    """
    Parse decompiled code to extract individual functions with their line boundaries.

    The decompiled code format has functions marked with:
    // Function: <function_name>
    <function_code>

    Args:
        dec_code: The full decompiled code string
        file_path: Path to the decompiled file

    Returns:
        Dict mapping function names to dicts containing:
        - 'code': the function's code (including the comment header)
        - 'start_line': 1-indexed start line
        - 'end_line': 1-indexed end line (inclusive)
    """
    lines = dec_code.split('\n')
    functions = {}

    # Pattern to match function comment markers
    func_marker_pattern = re.compile(r'^// Function: (.+)$')

    current_func_name: Optional[str] = None
    current_func_start: int = 0

    for i, line in enumerate(lines):
        line_num = i + 1  # 1-indexed

        match = func_marker_pattern.match(line)
        if match:
            # Save the previous function if there was one
            if current_func_name is not None and current_func_start > 0:
                # End line is the line before this marker, excluding trailing blank lines
                end_line = line_num - 1
                while end_line > current_func_start and lines[end_line - 1].strip() == '':
                    end_line -= 1

                func_lines = lines[current_func_start - 1:end_line]
                functions[current_func_name] = {
                    'code': '\n'.join(func_lines),
                    'start_line': current_func_start,
                    'end_line': end_line,
                    'file_path': file_path
                }

            # Start a new function
            current_func_name = match.group(1).strip()
            current_func_start = line_num

    # Don't forget the last function
    if current_func_name is not None and current_func_start > 0:
        end_line = len(lines)
        # Exclude trailing blank lines
        while end_line > current_func_start and lines[end_line - 1].strip() == '':
            end_line -= 1

        func_lines = lines[current_func_start - 1:end_line]
        functions[current_func_name] = {
            'code': '\n'.join(func_lines),
            'start_line': current_func_start,
            'end_line': end_line,
            'file_path': file_path
        }

    return functions


def analyze_dataset(dataset_path: Path, binary_path: Path) -> None:
    """
    Analyze the dataset and extract decompilations for each CPV.

    Args:
        dataset_path: Path to the dataset.toml file
        binary_path: Path to the nginx binary to decompile
    """
    console = Console()

    # Read the dataset TOML
    console.print(f"\n[bold cyan]Reading dataset from[/] {dataset_path}")
    with open(dataset_path, 'r') as f:
        dataset = toml.load(f)

    dataset_name = dataset.get('name', 'unknown')

    # Display dataset info
    info_table = Table(show_header=False, box=box.ROUNDED, padding=(0, 2))
    info_table.add_row("[bold]Dataset:[/]", dataset_name)
    info_table.add_row("[bold]Binary:[/]", str(binary_path))
    console.print(info_table)

    # Get all CPV targets
    targets = dataset.get('targets', {})
    console.print(f"\n[bold green]Found {len(targets)} CPV targets[/]\n")

    decompilers = ['angr', 'ghidra', 'ida']

    # Process each decompiler with all CPVs (more efficient - initialize decompiler once)
    with Progress(
        SpinnerColumn(),
        TextColumn("[progress.description]{task.description}"),
        BarColumn(),
        TaskProgressColumn(),
        console=console
    ) as progress:

        overall_task = progress.add_task(
            "[cyan]Overall progress",
            total=len(targets) * len(decompilers)
        )

        # Outer loop: iterate through decompilers (expensive to initialize)
        for decompiler_name in decompilers:
            console.print(f"\n[bold blue]{'='*60}[/]")
            console.print(f"[bold blue]Starting {decompiler_name.upper()} decompiler[/]")
            console.print(f"[bold blue]{'='*60}[/]")

            # Try to initialize the decompiler once for all CPVs
            try:
                with Decompiler(binary_path, backend=decompiler_name) as dec:
                    console.print(f"[green]✓[/] {decompiler_name} initialized successfully\n")

                    # Inner loop: process each CPV with this decompiler
                    for cpv_name, cpv_data in targets.items():
                        console.print(f"[bold magenta]Processing {cpv_name} with {decompiler_name}[/]")

                        # Get the CPV folder
                        cpv_folder = dataset_path.parent / cpv_name
                        if not cpv_folder.exists():
                            console.print(f"[yellow]⚠ CPV folder does not exist, skipping...[/]")
                            progress.advance(overall_task)
                            continue

                        # Check for crash.txt
                        crash_file = cpv_folder / "crash.txt"
                        if crash_file.exists():
                            console.print(f"[green]  ✓[/] Found crash.txt")
                        else:
                            console.print(f"[yellow]  ⚠[/] crash.txt not found")

                        # Get functions to patch
                        funcs_patched = cpv_data.get('funcs_patched', [])
                        if not funcs_patched:
                            console.print(f"[yellow]  ⚠ No funcs_patched specified, skipping...[/]")
                            progress.advance(overall_task)
                            continue

                        console.print(f"[bold]  Functions:[/] {', '.join(funcs_patched)}")
                        console.print(f"[bold]  Difficulty:[/] {cpv_data.get('difficulty', 'unknown')}")

                        output_file = cpv_folder / f"dec_{decompiler_name}.c"

                        cpv_task = progress.add_task(
                            f"[yellow]{cpv_name}[/] - Starting...",
                            total=len(funcs_patched)
                        )

                        decompiled_code = []

                        # Decompile each function
                        for func_name in funcs_patched:
                            progress.update(
                                cpv_task,
                                description=f"[yellow]{cpv_name}[/] - {func_name}"
                            )

                            try:
                                code = dec.decompile(func_name)
                                if code:
                                    decompiled_code.append(f"// Function: {func_name}\n")
                                    decompiled_code.append(code)
                                    decompiled_code.append("\n\n")
                                    progress.advance(cpv_task)
                                else:
                                    error_msg = "// ERROR: Decompilation returned no code\n\n"
                                    decompiled_code.append(f"// Function: {func_name}\n")
                                    decompiled_code.append(error_msg)
                                    progress.advance(cpv_task)
                                    console.print(f"  [red]  ✗[/] {func_name} - no code returned")
                            except Exception as e:
                                error_msg = f"// ERROR: {str(e)}\n\n"
                                decompiled_code.append(f"// Function: {func_name}\n")
                                decompiled_code.append(error_msg)
                                progress.advance(cpv_task)
                                console.print(f"  [red]  ✗[/] {func_name} - {str(e)}")

                        # Write to output file
                        try:
                            with open(output_file, 'w') as f:
                                f.write(''.join(decompiled_code))
                            console.print(f"[green]  ✓[/] Wrote {output_file.name}")
                        except Exception as e:
                            console.print(f"[red]  ✗[/] Failed to write {output_file.name}: {str(e)}")

                        progress.update(
                            cpv_task,
                            description=f"[green]{cpv_name}[/] - Complete ✓"
                        )
                        progress.advance(overall_task)
                        progress.remove_task(cpv_task)

            except Exception as e:
                console.print(f"[red]✗ ERROR initializing {decompiler_name}: {str(e)}[/]")
                console.print(f"[yellow]Skipping all CPVs for {decompiler_name}...[/]\n")

                # Write error to all CPV files for this decompiler
                for cpv_name, cpv_data in targets.items():
                    cpv_folder = dataset_path.parent / cpv_name
                    if cpv_folder.exists():
                        output_file = cpv_folder / f"dec_{decompiler_name}.c"
                        try:
                            with open(output_file, 'w') as f:
                                f.write(f"// ERROR initializing {decompiler_name} decompiler:\n")
                                f.write(f"// {str(e)}\n")
                            console.print(f"[yellow]  Wrote error to {cpv_name}/dec_{decompiler_name}.c[/]")
                        except Exception as write_error:
                            console.print(f"[red]  Failed to write error file for {cpv_name}: {str(write_error)}[/]")

                    progress.advance(overall_task)

            console.print()  # Add blank line between decompilers

    console.print(f"\n[bold green]{'='*60}[/]")
    console.print(Panel("[bold green]Analysis complete![/]", box=box.DOUBLE))
    console.print(f"[bold green]{'='*60}[/]\n")


def generate_patches(
    dataset_path: Path,
    model: str = "claude-3.7-sonnet",
    attempts: int = 10,
    target_cpvs: Optional[List[str]] = None,
    target_decompiler: Optional[str] = None
) -> None:
    """
    Generate patches for each CPV using PatcherY.

    Args:
        dataset_path: Path to the dataset.toml file
        model: LLM model to use for patch generation
        attempts: Number of patch attempts per CPV/decompiler combination
        target_cpvs: Optional list of CPVs to target (e.g., ['cpv1', 'cpv2'])
        target_decompiler: Optional single decompiler to use (angr, ghidra, or ida)
    """
    console = Console()

    # Read the dataset TOML
    console.print(f"\n[bold cyan]Reading dataset from[/] {dataset_path}")
    with open(dataset_path, 'r') as f:
        dataset = toml.load(f)

    dataset_name = dataset.get('name', 'unknown')

    # Display dataset info
    info_table = Table(show_header=False, box=box.ROUNDED, padding=(0, 2))
    info_table.add_row("[bold]Dataset:[/]", dataset_name)
    info_table.add_row("[bold]Model:[/]", model)
    info_table.add_row("[bold]Attempts per CPV/decompiler:[/]", str(attempts))
    console.print(info_table)

    # Get all CPV targets
    targets = dataset.get('targets', {})

    # Filter to specified CPVs if provided
    if target_cpvs:
        missing_cpvs = [cpv for cpv in target_cpvs if cpv not in targets]
        if missing_cpvs:
            console.print(f"\n[bold red]CPV(s) not found in dataset: {', '.join(missing_cpvs)}[/]")
            console.print(f"Available CPVs: {', '.join(targets.keys())}")
            return
        targets = {cpv: targets[cpv] for cpv in target_cpvs}
        console.print(f"\n[bold yellow]Filtering to CPVs: {', '.join(target_cpvs)}[/]\n")

    console.print(f"\n[bold green]Found {len(targets)} CPV targets[/]\n")

    # Set decompilers list (filter if single decompiler specified)
    decompilers = [target_decompiler] if target_decompiler else ['angr', 'ghidra', 'ida']
    if target_decompiler:
        console.print(f"[bold yellow]Using only {target_decompiler} decompiler[/]\n")

    # Process each CPV and decompiler combination
    with Progress(
        SpinnerColumn(),
        TextColumn("[progress.description]{task.description}"),
        BarColumn(),
        TaskProgressColumn(),
        console=console
    ) as progress:

        total_tasks = len(targets) * len(decompilers)
        overall_task = progress.add_task(
            "[cyan]Overall progress",
            total=total_tasks
        )

        for cpv_name, cpv_data in targets.items():
            console.print(f"\n[bold magenta]{'='*60}[/]")
            console.print(f"[bold magenta]Processing {cpv_name}[/]")
            console.print(f"[bold magenta]{'='*60}[/]")

            # Get the CPV folder
            cpv_folder = dataset_path.parent / cpv_name
            if not cpv_folder.exists():
                console.print(f"[yellow]⚠ CPV folder does not exist, skipping...[/]")
                progress.advance(overall_task, len(decompilers))
                continue

            # Check for crash.txt
            crash_file = cpv_folder / "crash.txt"
            if not crash_file.exists():
                console.print(f"[red]✗ crash.txt not found, skipping {cpv_name}...[/]")
                progress.advance(overall_task, len(decompilers))
                continue

            # Read the crash report
            console.print(f"[green]✓[/] Found crash.txt")
            with open(crash_file, 'r') as f:
                crash_report = f.read()
            

            # Get functions to patch
            funcs_patched = cpv_data.get('funcs_patched', [])
            if not funcs_patched:
                console.print(f"[yellow]⚠ No funcs_patched specified, skipping...[/]")
                progress.advance(overall_task, len(decompilers))
                continue

            console.print(f"[bold]Functions:[/] {', '.join(funcs_patched)}")

            # Process each decompiler
            for decompiler_name in decompilers:
                console.print(f"\n[bold blue]Generating patches with {decompiler_name} decompilation[/]")

                # Check if decompilation file exists
                dec_file = cpv_folder / f"dec_{decompiler_name}.c"
                if not dec_file.exists():
                    console.print(f"[red]✗ Decompilation file {dec_file.name} not found, skipping...[/]")
                    progress.advance(overall_task)
                    continue

                # Create output directory for patches
                patches_dir = cpv_folder / "generated_patches" / decompiler_name
                patches_dir.mkdir(parents=True, exist_ok=True)
                console.print(f"[green]✓[/] Created patches directory: {patches_dir.relative_to(dataset_path.parent)}")

                # Create a temporary directory for patch generation
                with tempfile.TemporaryDirectory() as temp_dir_str:
                    temp_dir = Path(temp_dir_str)
                    console.print(f"[dim]Using temporary directory: {temp_dir}[/]")

                    # Copy decompilation file to temp directory
                    temp_dec_file = temp_dir / f"dec_{decompiler_name}.c"
                    shutil.copy(dec_file, temp_dec_file)

                    # Initialize git repo in temp directory
                    try:
                        subprocess.run(
                            ["git", "init"],
                            cwd=temp_dir,
                            check=True,
                            capture_output=True
                        )
                        subprocess.run(
                            ["git", "add", "."],
                            cwd=temp_dir,
                            check=True,
                            capture_output=True
                        )
                        subprocess.run(
                            ["git", "commit", "-m", "Initial commit"],
                            cwd=temp_dir,
                            check=True,
                            capture_output=True
                        )
                    except subprocess.CalledProcessError as e:
                        console.print(f"[red]✗ Failed to initialize git repo: {e}[/]")
                        progress.advance(overall_task)
                        continue

                    # Initialize PatcherY
                    fake_program = Program(temp_dir, language="c")
                    generator = LLMPlanPatchGenerator(fake_program, model)

                    # Read decompilation
                    with open(temp_dec_file, 'r') as f:
                        dec_code = f.read()

                    # Parse the decompiled code into individual functions
                    parsed_functions = parse_decompiled_functions(dec_code, str(temp_dec_file))

                    # Attempt to generate patches
                    patch_task = progress.add_task(
                        f"[yellow]{cpv_name}/{decompiler_name}[/]",
                        total=attempts
                    )

                    successful_patches = 0
                    for attempt_num in range(1, attempts + 1):
                        progress.update(
                            patch_task,
                            description=f"[yellow]{cpv_name}/{decompiler_name}[/] - Attempt {attempt_num}/{attempts}"
                        )

                        try:
                            # Create CodeFunction for each function to be patched
                            pois = []
                            for func_name in funcs_patched:
                                if func_name in parsed_functions:
                                    func_info = parsed_functions[func_name]
                                    code_func = CodeFunction(
                                        func_name,
                                        func_info['start_line'],
                                        func_info['end_line'],
                                        code=func_info['code'],
                                        file_path=func_info['file_path'],
                                    )
                                    pois.append(PoI(code_func))
                                else:
                                    # Function not found in parsed output, fall back to whole file
                                    console.print(f"[yellow]    ⚠ Function {func_name} not found in decompilation, using whole file[/]")
                                    code_func = CodeFunction(
                                        func_name,
                                        1,
                                        len(dec_code.splitlines()),
                                        code=dec_code,
                                        file_path=str(temp_dec_file),
                                    )
                                    pois.append(PoI(code_func))

                            # Create PoI cluster with all functions
                            cluster = PoICluster.from_pois(pois)

                            # Append extra information about the file location
                            fixed_crash_report = f"NOTE: ALL FUNCTIONS CAN NOW BE FOUND IN THE {temp_dec_file} FILE NOW.\n" + crash_report

                            # Generate patch - capture the return value which contains the diff
                            patch = generator.generate_patch(cluster, reports=[fixed_crash_report])

                            # Check if patch was generated and has a diff
                            if patch and patch.diff and patch.diff.strip():
                                # Save the patch
                                patch_file = patches_dir / f"patch_{attempt_num}.diff"
                                with open(patch_file, 'w') as f:
                                    f.write(patch.diff)

                                console.print(f"[green]  ✓[/] Generated patch_{attempt_num}.diff")
                                successful_patches += 1
                            else:
                                console.print(f"[yellow]  ⚠[/] Attempt {attempt_num} produced no changes")

                        except Exception as e:
                            console.print(f"[red]  ✗[/] Attempt {attempt_num} failed: {str(e)}")

                        progress.advance(patch_task)

                    progress.remove_task(patch_task)
                    console.print(f"[bold green]Generated {successful_patches}/{attempts} patches for {decompiler_name}[/]")

                progress.advance(overall_task)

    console.print(f"\n[bold green]{'='*60}[/]")
    console.print(Panel("[bold green]Patch generation complete![/]", box=box.DOUBLE))
    console.print(f"[bold green]{'='*60}[/]\n")


def grade_patches(
    dataset_path: Path,
    target_cpvs: Optional[List[str]] = None,
    target_decompiler: Optional[str] = None
) -> None:
    """
    Grade generated patches by comparing them to the good_patch.diff using an LLM.

    Args:
        dataset_path: Path to the dataset.toml file
        target_cpvs: Optional list of CPVs to grade (e.g., ['cpv1', 'cpv2'])
        target_decompiler: Optional single decompiler to grade (angr, ghidra, or ida)
    """
    console = Console()

    # Read the dataset TOML
    console.print(f"\n[bold cyan]Reading dataset from[/] {dataset_path}")
    with open(dataset_path, 'r') as f:
        dataset = toml.load(f)

    dataset_name = dataset.get('name', 'unknown')

    # Display dataset info
    info_table = Table(show_header=False, box=box.ROUNDED, padding=(0, 2))
    info_table.add_row("[bold]Dataset:[/]", dataset_name)
    info_table.add_row("[bold]Model:[/]", "gpt-5.2")
    console.print(info_table)

    # Get all CPV targets
    targets = dataset.get('targets', {})

    # Filter to specified CPVs if provided
    if target_cpvs:
        missing_cpvs = [cpv for cpv in target_cpvs if cpv not in targets]
        if missing_cpvs:
            console.print(f"\n[bold red]CPV(s) not found in dataset: {', '.join(missing_cpvs)}[/]")
            console.print(f"Available CPVs: {', '.join(targets.keys())}")
            return
        targets = {cpv: targets[cpv] for cpv in target_cpvs}
        console.print(f"\n[bold yellow]Filtering to CPVs: {', '.join(target_cpvs)}[/]\n")

    console.print(f"\n[bold green]Found {len(targets)} CPV targets[/]\n")

    # Set decompilers list (filter if single decompiler specified)
    decompilers = [target_decompiler] if target_decompiler else ['angr', 'ghidra', 'ida']
    if target_decompiler:
        console.print(f"[bold yellow]Using only {target_decompiler} decompiler[/]\n")

    # Initialize OpenAI client
    client = openai.OpenAI()

    # Process each CPV
    with Progress(
        SpinnerColumn(),
        TextColumn("[progress.description]{task.description}"),
        BarColumn(),
        TaskProgressColumn(),
        console=console
    ) as progress:

        total_tasks = len(targets) * len(decompilers)
        overall_task = progress.add_task(
            "[cyan]Overall progress",
            total=total_tasks
        )

        for cpv_name, cpv_data in targets.items():
            console.print(f"\n[bold magenta]{'='*60}[/]")
            console.print(f"[bold magenta]Grading {cpv_name}[/]")
            console.print(f"[bold magenta]{'='*60}[/]")

            # Get the CPV folder
            cpv_folder = dataset_path.parent / cpv_name
            if not cpv_folder.exists():
                console.print(f"[yellow]⚠ CPV folder does not exist, skipping...[/]")
                progress.advance(overall_task, len(decompilers))
                continue

            # Check for good_patch.diff
            good_patch_file = cpv_folder / "good_patch.diff"
            if not good_patch_file.exists():
                console.print(f"[red]✗ good_patch.diff not found, skipping {cpv_name}...[/]")
                progress.advance(overall_task, len(decompilers))
                continue

            # Read the good patch
            console.print(f"[green]✓[/] Found good_patch.diff")
            with open(good_patch_file, 'r') as f:
                good_patch = f.read()

            # Check for CPVINFO.md
            cpvinfo_file = cpv_folder / "CPVINFO.md"
            cpvinfo = ""
            if cpvinfo_file.exists():
                console.print(f"[green]✓[/] Found CPVINFO.md")
                with open(cpvinfo_file, 'r') as f:
                    cpvinfo = f.read()
            else:
                console.print(f"[yellow]⚠[/] CPVINFO.md not found")

            # Initialize grades dict for this CPV
            grades = {}

            # Process each decompiler
            for decompiler_name in decompilers:
                console.print(f"\n[bold blue]Grading patches from {decompiler_name}[/]")

                patches_dir = cpv_folder / "generated_patches" / decompiler_name
                if not patches_dir.exists():
                    console.print(f"[yellow]⚠ No patches directory for {decompiler_name}, skipping...[/]")
                    progress.advance(overall_task)
                    continue

                # Collect all patches for this decompiler
                patch_files = sorted(patches_dir.glob("patch_*.diff"))
                if not patch_files:
                    console.print(f"[yellow]⚠ No patch files found for {decompiler_name}, skipping...[/]")
                    progress.advance(overall_task)
                    continue

                console.print(f"[green]✓[/] Found {len(patch_files)} patches")

                # Read all patches
                patches_content = []
                for patch_file in patch_files:
                    with open(patch_file, 'r') as f:
                        patches_content.append({
                            "name": patch_file.name,
                            "content": f.read()
                        })

                # Build the prompt for the LLM
                patches_text = "\n\n".join([
                    f"=== {p['name']} ===\n{p['content']}"
                    for p in patches_content
                ])

                prompt = f"""You are an expert security researcher grading patches for a vulnerability fix.

## Context

The following vulnerability needs to be patched:

{cpvinfo}

## Reference Patch (Source Code)

This is the correct patch written against the original source code:

```diff
{good_patch}
```

## Generated Patches (Decompiled Code)

These patches were generated from decompiled code using the {decompiler_name} decompiler.
IMPORTANT: Variable names in decompiled code will be different (e.g., field_70, v12, ptr instead of pool, headers, buf).
This is EXPECTED and does NOT make a patch wrong.

A patch is CORRECT if it:
- Implements the same SEMANTIC fix as the reference patch
- Adds equivalent bounds checking, validation, or logic
- Fixes the vulnerability in a functionally equivalent way
- Fixes the vulnerability in a semantically equivalent way as the correct patch. I.e. instead of the exact same it implements a safe alternative.

A patch is WRONG if it:
- Is incomplete (missing key parts of the fix)
- Adds incorrect logic that doesn't fix the vulnerability
- Would introduce new bugs or not actually prevent the vulnerability
- Is empty or doesn't make meaningful changes

{patches_text}

## Task

For each patch, determine if it is semantically correct or wrong.
Respond with a JSON object where keys are patch filenames and values are "correct" or "wrong".

Example response format:
{{"patch_1.diff": "correct", "patch_2.diff": "wrong", "patch_3.diff": "correct"}}

Respond ONLY with the JSON object, no other text."""

                # Call the LLM
                grade_task = progress.add_task(
                    f"[yellow]{cpv_name}/{decompiler_name}[/] - Grading...",
                    total=1
                )

                result_text = ""
                try:
                    response = client.chat.completions.create(
                        model="gpt-5.2",
                        messages=[
                            {"role": "user", "content": prompt}
                        ],
                        temperature=0.0
                    )

                    # Parse the response
                    content = response.choices[0].message.content
                    if content is None:
                        raise ValueError("LLM returned empty response")
                    result_text = content.strip()

                    # Handle potential markdown code blocks
                    if result_text.startswith("```"):
                        result_text = result_text.split("```")[1]
                        if result_text.startswith("json"):
                            result_text = result_text[4:]
                        result_text = result_text.strip()

                    decompiler_grades = json.loads(result_text)
                    grades[decompiler_name] = decompiler_grades

                    # Display results
                    correct_count = sum(1 for v in decompiler_grades.values() if v == "correct")
                    total_count = len(decompiler_grades)
                    console.print(f"[green]✓[/] Graded: {correct_count}/{total_count} correct")

                    for patch_name, grade in decompiler_grades.items():
                        color = "green" if grade == "correct" else "red"
                        console.print(f"  [{color}]{patch_name}: {grade}[/{color}]")

                except json.JSONDecodeError as e:
                    console.print(f"[red]✗ Failed to parse LLM response: {e}[/]")
                    console.print(f"[dim]Response was: {result_text}[/]")
                    grades[decompiler_name] = {"error": f"Failed to parse: {str(e)}"}
                except Exception as e:
                    console.print(f"[red]✗ Error grading patches: {e}[/]")
                    grades[decompiler_name] = {"error": str(e)}

                progress.advance(grade_task)
                progress.remove_task(grade_task)
                progress.advance(overall_task)

            # Write grades.json for this CPV
            grades_file = cpv_folder / "grades.json"
            try:
                with open(grades_file, 'w') as f:
                    json.dump(grades, f, indent=2)
                console.print(f"\n[green]✓[/] Wrote {grades_file.name}")
            except Exception as e:
                console.print(f"[red]✗ Failed to write grades.json: {e}[/]")

    console.print(f"\n[bold green]{'='*60}[/]")
    console.print(Panel("[bold green]Grading complete![/]", box=box.DOUBLE))
    console.print(f"[bold green]{'='*60}[/]\n")


def compute_distance(
    dataset_path: Path,
    target_cpvs: Optional[List[str]] = None,
    target_decompiler: Optional[str] = None
) -> None:
    """
    Compute Graph Edit Distance (GED) between source and decompiled CFGs.

    Args:
        dataset_path: Path to the dataset.toml file
        target_cpvs: Optional list of CPVs to process (e.g., ['cpv1', 'cpv2'])
        target_decompiler: Optional single decompiler to use (angr, ghidra, or ida)
    """
    from pyjoern import parse_source
    from cfgutils.similarity import vj_ged

    console = Console()

    # Source code path
    source_path = Path.home() / "github" / "challenge-004-nginx-source" / "src"

    # Read the dataset TOML
    console.print(f"\n[bold cyan]Reading dataset from[/] {dataset_path}")
    with open(dataset_path, 'r') as f:
        dataset = toml.load(f)

    dataset_name = dataset.get('name', 'unknown')

    # Display dataset info
    info_table = Table(show_header=False, box=box.ROUNDED, padding=(0, 2))
    info_table.add_row("[bold]Dataset:[/]", dataset_name)
    info_table.add_row("[bold]Source:[/]", str(source_path))
    console.print(info_table)

    # Get all CPV targets
    targets = dataset.get('targets', {})

    # Filter to specified CPVs if provided
    if target_cpvs:
        missing_cpvs = [cpv for cpv in target_cpvs if cpv not in targets]
        if missing_cpvs:
            console.print(f"\n[bold red]CPV(s) not found in dataset: {', '.join(missing_cpvs)}[/]")
            console.print(f"Available CPVs: {', '.join(targets.keys())}")
            return
        targets = {cpv: targets[cpv] for cpv in target_cpvs}
        console.print(f"\n[bold yellow]Filtering to CPVs: {', '.join(target_cpvs)}[/]\n")

    console.print(f"\n[bold green]Found {len(targets)} CPV targets[/]\n")

    # Set decompilers list
    decompilers = [target_decompiler] if target_decompiler else ['angr', 'ghidra', 'ida']
    if target_decompiler:
        console.print(f"[bold yellow]Using only {target_decompiler} decompiler[/]\n")

    # Collect all unique function names needed across all CPVs
    all_func_names = set()
    for cpv_data in targets.values():
        funcs_patched = cpv_data.get('funcs_patched', [])
        all_func_names.update(funcs_patched)

    console.print(f"[bold cyan]Parsing source code for {len(all_func_names)} functions...[/]")

    # Parse source code to get CFGs for all functions
    try:
        source_cfgs_raw = parse_source(source_path)
        console.print(f"[green]✓[/] Parsed source code, found {len(source_cfgs_raw)} functions")

        # Source path is a directory, so keys are (name, filename) tuples
        # Create a lookup by function name only (take first match if duplicates)
        source_cfgs: Dict[str, Any] = {}
        for key, func in source_cfgs_raw.items():
            if isinstance(key, tuple):
                func_name = key[0]
            else:
                func_name = key
            if func_name not in source_cfgs:
                source_cfgs[func_name] = func
    except Exception as e:
        console.print(f"[red]✗ Failed to parse source code: {e}[/]")
        return

    # Process each CPV
    with Progress(
        SpinnerColumn(),
        TextColumn("[progress.description]{task.description}"),
        BarColumn(),
        TaskProgressColumn(),
        console=console
    ) as progress:

        total_tasks = len(targets) * len(decompilers)
        overall_task = progress.add_task(
            "[cyan]Overall progress",
            total=total_tasks
        )

        for cpv_name, cpv_data in targets.items():
            console.print(f"\n[bold magenta]{'='*60}[/]")
            console.print(f"[bold magenta]Processing {cpv_name}[/]")
            console.print(f"[bold magenta]{'='*60}[/]")

            # Get the CPV folder
            cpv_folder = dataset_path.parent / cpv_name
            if not cpv_folder.exists():
                console.print(f"[yellow]⚠ CPV folder does not exist, skipping...[/]")
                progress.advance(overall_task, len(decompilers))
                continue

            # Get functions to analyze
            funcs_patched = cpv_data.get('funcs_patched', [])
            if not funcs_patched:
                console.print(f"[yellow]⚠ No funcs_patched specified, skipping...[/]")
                progress.advance(overall_task, len(decompilers))
                continue

            console.print(f"[bold]Functions:[/] {', '.join(funcs_patched)}")

            # Initialize distance results for this CPV
            distance_results: Dict = {}

            # Process each decompiler
            for decompiler_name in decompilers:
                console.print(f"\n[bold blue]Computing distances for {decompiler_name}[/]")

                # Check if decompilation file exists
                dec_file = cpv_folder / f"dec_{decompiler_name}.c"
                if not dec_file.exists():
                    console.print(f"[red]✗ Decompilation file {dec_file.name} not found, skipping...[/]")
                    progress.advance(overall_task)
                    continue

                distance_results[decompiler_name] = {}

                # Parse decompiled code to get CFGs
                try:
                    dec_cfgs = parse_source(dec_file, is_decompilation=True)
                    console.print(f"[green]✓[/] Parsed {dec_file.name}, found {len(dec_cfgs)} functions")
                except Exception as e:
                    console.print(f"[red]✗ Failed to parse {dec_file.name}: {e}[/]")
                    progress.advance(overall_task)
                    continue

                # Compute GED for each function
                func_task = progress.add_task(
                    f"[yellow]{cpv_name}/{decompiler_name}[/]",
                    total=len(funcs_patched)
                )

                for func_name in funcs_patched:
                    progress.update(
                        func_task,
                        description=f"[yellow]{cpv_name}/{decompiler_name}[/] - {func_name}"
                    )

                    # Check if function exists in source CFGs
                    if func_name not in source_cfgs:
                        console.print(f"[yellow]  ⚠[/] Function {func_name} not found in source CFGs")
                        distance_results[decompiler_name][func_name] = {"error": "not_in_source"}
                        progress.advance(func_task)
                        continue

                    # Check if function exists in decompiled CFGs
                    if func_name not in dec_cfgs:
                        console.print(f"[yellow]  ⚠[/] Function {func_name} not found in decompiled CFGs")
                        distance_results[decompiler_name][func_name] = {"error": "not_in_decompiled"}
                        progress.advance(func_task)
                        continue

                    # Compute GED
                    try:
                        import networkx as nx

                        source_func = source_cfgs[func_name]
                        dec_func = dec_cfgs[func_name]
                        # Access the cfg attribute from Function objects
                        source_cfg = source_func.cfg
                        dec_cfg = dec_func.cfg

                        # Validate CFGs are DiGraphs
                        if not isinstance(source_cfg, nx.DiGraph):
                            distance_results[decompiler_name][func_name] = {"error": "invalid_source_cfg"}
                            console.print(f"[yellow]  ⚠[/] {func_name}: invalid source CFG")
                            progress.advance(func_task)
                            continue
                        if not isinstance(dec_cfg, nx.DiGraph):
                            distance_results[decompiler_name][func_name] = {"error": "invalid_decompiled_cfg"}
                            console.print(f"[yellow]  ⚠[/] {func_name}: invalid decompiled CFG")
                            progress.advance(func_task)
                            continue

                        ged = vj_ged(source_cfg, dec_cfg)
                        distance_results[decompiler_name][func_name] = {"ged": ged}
                        console.print(f"[green]  ✓[/] {func_name}: GED = {ged:.4f}")
                    except Exception as e:
                        console.print(f"[red]  ✗[/] {func_name}: {str(e)}")
                        distance_results[decompiler_name][func_name] = {"error": str(e)}

                    progress.advance(func_task)

                progress.remove_task(func_task)
                progress.advance(overall_task)

            # Write distance.json for this CPV
            distance_file = cpv_folder / "distance.json"
            try:
                with open(distance_file, 'w') as f:
                    json.dump(distance_results, f, indent=2)
                console.print(f"\n[green]✓[/] Wrote {distance_file.name}")
            except Exception as e:
                console.print(f"[red]✗ Failed to write distance.json: {e}[/]")

    console.print(f"\n[bold green]{'='*60}[/]")
    console.print(Panel("[bold green]Distance computation complete![/]", box=box.DOUBLE))
    console.print(f"[bold green]{'='*60}[/]\n")


def visualize_results(
    dataset_path: Path,
    target_cpvs: Optional[List[str]] = None,
    target_decompiler: Optional[str] = None,
    pass_three: bool = False
) -> None:
    """
    Visualize probability of success vs GED across the dataset.

    Args:
        dataset_path: Path to the dataset.toml file
        target_cpvs: Optional list of CPVs to include (e.g., ['cpv1', 'cpv2'])
        target_decompiler: Optional single decompiler to filter by (angr, ghidra, or ida)
        pass_three: If True, use pass@3 metric (success if any of 3 attempts correct)
    """
    import matplotlib.pyplot as plt
    import numpy as np

    console = Console()

    # Read the dataset TOML
    console.print(f"\n[bold cyan]Reading dataset from[/] {dataset_path}")
    with open(dataset_path, 'r') as f:
        dataset = toml.load(f)

    dataset_name = dataset.get('name', 'unknown')

    # Get all CPV targets
    targets = dataset.get('targets', {})

    # Filter to specified CPVs if provided
    if target_cpvs:
        missing_cpvs = [cpv for cpv in target_cpvs if cpv not in targets]
        if missing_cpvs:
            console.print(f"\n[bold red]CPV(s) not found in dataset: {', '.join(missing_cpvs)}[/]")
            console.print(f"Available CPVs: {', '.join(targets.keys())}")
            return
        targets = {cpv: targets[cpv] for cpv in target_cpvs}
        console.print(f"\n[bold yellow]Filtering to CPVs: {', '.join(target_cpvs)}[/]\n")

    # Set decompilers list
    decompilers = [target_decompiler] if target_decompiler else ['angr', 'ghidra', 'ida']

    console.print(f"\n[bold green]Collecting data from {len(targets)} CPV targets[/]\n")

    # Collect all (ged, is_correct) pairs across the dataset
    data_points: List[tuple] = []  # List of (ged, is_correct, decompiler, cpv, patch)

    for cpv_name in targets.keys():
        cpv_folder = dataset_path.parent / cpv_name

        # Read distance.json
        distance_file = cpv_folder / "distance.json"
        if not distance_file.exists():
            console.print(f"[yellow]⚠ {cpv_name}: distance.json not found, skipping...[/]")
            continue

        with open(distance_file, 'r') as f:
            distances = json.load(f)

        # Read grades.json
        grades_file = cpv_folder / "grades.json"
        if not grades_file.exists():
            console.print(f"[yellow]⚠ {cpv_name}: grades.json not found, skipping...[/]")
            continue

        with open(grades_file, 'r') as f:
            grades = json.load(f)

        # Process each decompiler
        for decompiler_name in decompilers:
            if decompiler_name not in distances or decompiler_name not in grades:
                continue

            decompiler_distances = distances[decompiler_name]
            decompiler_grades = grades[decompiler_name]

            # Get the GED for this CPV/decompiler (average across functions if multiple)
            ged_values = []
            for func_name, func_data in decompiler_distances.items():
                if isinstance(func_data, dict) and "ged" in func_data:
                    ged_values.append(func_data["ged"])

            if not ged_values:
                continue

            avg_ged = sum(ged_values) / len(ged_values)

            # Get correctness for each patch
            for patch_name, grade in decompiler_grades.items():
                if patch_name == "error":
                    continue
                is_correct = 1 if grade == "correct" else 0
                data_points.append((avg_ged, is_correct, decompiler_name, cpv_name, patch_name))

    if not data_points:
        console.print("[red]No data points found! Make sure --distance and --grade have been run.[/]")
        return

    console.print(f"[green]✓[/] Collected {len(data_points)} data points")

    # If pass@3 mode, aggregate patches by (cpv, decompiler) and check if any of 3 are correct
    if pass_three:
        console.print(f"[bold cyan]Using pass@3 metric...[/]")
        # Group by (cpv, decompiler)
        grouped: Dict[tuple, List[tuple]] = {}
        for dp in data_points:
            key = (dp[3], dp[2])  # (cpv, decompiler)
            if key not in grouped:
                grouped[key] = []
            grouped[key].append(dp)

        # For each group, create pass@3 data points
        # If there are N patches, create N//3 pass@3 points
        pass3_data_points: List[tuple] = []
        for (cpv, decompiler), patches in grouped.items():
            # Sort patches by name to ensure consistent grouping
            patches_sorted = sorted(patches, key=lambda x: x[4])
            # Group into chunks of 3
            for i in range(0, len(patches_sorted), 3):
                chunk = patches_sorted[i:i+3]
                if len(chunk) < 3:
                    continue  # Skip incomplete groups
                # pass@3: success if ANY of the 3 patches is correct
                any_correct = 1 if any(p[1] == 1 for p in chunk) else 0
                avg_ged = chunk[0][0]  # GED is the same for all in group
                pass3_data_points.append((avg_ged, any_correct, decompiler, cpv, f"pass3_{i//3}"))

        data_points = pass3_data_points
        console.print(f"[green]✓[/] Aggregated to {len(data_points)} pass@3 data points")

    # Convert to numpy arrays for easier manipulation
    geds = np.array([dp[0] for dp in data_points])
    correctness = np.array([dp[1] for dp in data_points])
    decompiler_labels = [dp[2] for dp in data_points]

    # Filter out GED values above 50 (outliers)
    max_ged_cutoff = 50
    valid_mask = geds <= max_ged_cutoff
    filtered_count = (~valid_mask).sum()
    if filtered_count > 0:
        console.print(f"[yellow]⚠ Filtered out {filtered_count} data points with GED > {max_ged_cutoff}[/]")

    geds_filtered = geds[valid_mask]
    correctness_filtered = correctness[valid_mask]
    decompiler_labels_filtered = [d for d, v in zip(decompiler_labels, valid_mask) if v]

    # Separate correct and wrong patches
    correct_mask = correctness_filtered == 1
    wrong_mask = correctness_filtered == 0

    geds_correct = geds_filtered[correct_mask]
    geds_wrong = geds_filtered[wrong_mask]
    decompilers_correct = [d for d, m in zip(decompiler_labels_filtered, correct_mask) if m]
    decompilers_wrong = [d for d, m in zip(decompiler_labels_filtered, wrong_mask) if m]

    # Create the visualization with two horizontal panels
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 8), sharex=True)

    colors = {'angr': 'red', 'ghidra': 'green', 'ida': 'blue'}
    metric_label = "pass@3" if pass_three else "pass@1"

    # Top panel: Correct patches
    for decompiler in decompilers:
        dec_mask = [d == decompiler for d in decompilers_correct]
        if any(dec_mask):
            dec_geds = geds_correct[dec_mask]
            # Add small jitter to y for visibility when points overlap
            jitter = np.random.uniform(-0.1, 0.1, len(dec_geds))
            ax1.scatter(dec_geds, jitter, c=colors.get(decompiler, 'gray'),
                        label=f'{decompiler} (n={len(dec_geds)})', alpha=0.7, s=60, edgecolors='black', linewidths=0.5)

    ax1.set_ylabel('')
    ax1.set_title(f'Correct Patches ({metric_label}) - n={len(geds_correct)}', fontsize=14, fontweight='bold', color='green')
    ax1.set_yticks([])
    ax1.set_xlim(0, max_ged_cutoff)
    ax1.axvline(x=geds_correct.mean() if len(geds_correct) > 0 else 0, color='green', linestyle='--', alpha=0.7,
                label=f'Mean GED: {geds_correct.mean():.2f}' if len(geds_correct) > 0 else 'Mean GED: N/A')
    ax1.legend(loc='upper right')
    ax1.grid(axis='x', alpha=0.3)
    ax1.set_ylim(-0.5, 0.5)

    # Bottom panel: Wrong patches
    for decompiler in decompilers:
        dec_mask = [d == decompiler for d in decompilers_wrong]
        if any(dec_mask):
            dec_geds = geds_wrong[dec_mask]
            # Add small jitter to y for visibility when points overlap
            jitter = np.random.uniform(-0.1, 0.1, len(dec_geds))
            ax2.scatter(dec_geds, jitter, c=colors.get(decompiler, 'gray'),
                        label=f'{decompiler} (n={len(dec_geds)})', alpha=0.7, s=60, edgecolors='black', linewidths=0.5)

    ax2.set_xlabel('Graph Edit Distance (GED)', fontsize=12)
    ax2.set_ylabel('')
    ax2.set_title(f'Wrong Patches ({metric_label}) - n={len(geds_wrong)}', fontsize=14, fontweight='bold', color='red')
    ax2.set_yticks([])
    ax2.set_xlim(0, max_ged_cutoff)
    ax2.axvline(x=geds_wrong.mean() if len(geds_wrong) > 0 else 0, color='red', linestyle='--', alpha=0.7,
                label=f'Mean GED: {geds_wrong.mean():.2f}' if len(geds_wrong) > 0 else 'Mean GED: N/A')
    ax2.legend(loc='upper right')
    ax2.grid(axis='x', alpha=0.3)
    ax2.set_ylim(-0.5, 0.5)

    fig.suptitle(f'GED Distribution: Correct vs Wrong Patches\n({dataset_name}, GED ≤ {max_ged_cutoff})', fontsize=16, fontweight='bold')
    plt.tight_layout()

    # Save the figure
    suffix = "_pass3" if pass_three else ""
    output_path = dataset_path.parent / f"ged_vs_success{suffix}.png"
    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    console.print(f"\n[green]✓[/] Saved visualization to {output_path}")

    # Also show summary statistics (using filtered data)
    console.print(f"\n[bold cyan]Summary Statistics (GED ≤ {max_ged_cutoff}, {metric_label}):[/]")
    summary_table = Table(box=box.ROUNDED)
    summary_table.add_column("Metric", style="bold")
    summary_table.add_column("Value")
    summary_table.add_row("Total patches", str(len(geds_filtered)))
    summary_table.add_row(f"Filtered out (GED > {max_ged_cutoff})", str(filtered_count))
    summary_table.add_row("Correct patches", str(int(correctness_filtered.sum())))
    summary_table.add_row("Overall success rate", f"{correctness_filtered.mean():.2%}")
    summary_table.add_row("GED range", f"{geds_filtered.min():.2f} - {geds_filtered.max():.2f}")
    summary_table.add_row("Mean GED (all)", f"{geds_filtered.mean():.2f}")
    if len(geds_correct) > 0:
        summary_table.add_row("Mean GED (correct)", f"{geds_correct.mean():.2f}")
    if len(geds_wrong) > 0:
        summary_table.add_row("Mean GED (wrong)", f"{geds_wrong.mean():.2f}")
    console.print(summary_table)

    # Per-decompiler stats (using filtered data)
    console.print(f"\n[bold cyan]Per-Decompiler Statistics:[/]")
    dec_table = Table(box=box.ROUNDED)
    dec_table.add_column("Decompiler", style="bold")
    dec_table.add_column("Patches")
    dec_table.add_column("Success Rate")
    dec_table.add_column("Mean GED")

    for decompiler in decompilers:
        mask = np.array([d == decompiler for d in decompiler_labels_filtered])
        if mask.sum() > 0:
            dec_table.add_row(
                decompiler,
                str(mask.sum()),
                f"{correctness_filtered[mask].mean():.2%}",
                f"{geds_filtered[mask].mean():.2f}"
            )
    console.print(dec_table)

    plt.show()

    console.print(f"\n[bold green]{'='*60}[/]")
    console.print(Panel("[bold green]Visualization complete![/]", box=box.DOUBLE))
    console.print(f"[bold green]{'='*60}[/]\n")


def main():
    """Main entry point."""
    parser = argparse.ArgumentParser(
        description="Dataset analysis and patch generation tool for nginx CPVs"
    )
    parser.add_argument(
        "--decompile",
        action="store_true",
        help="Extract decompilations for all CPVs using angr, ghidra, and ida"
    )
    parser.add_argument(
        "--patch",
        action="store_true",
        help="Generate patches for all CPVs using PatcherY"
    )
    parser.add_argument(
        "--grade",
        action="store_true",
        help="Grade generated patches by comparing to good_patch.diff using gpt-5.2"
    )
    parser.add_argument(
        "--distance",
        action="store_true",
        help="Compute GED (Graph Edit Distance) between source and decompiled CFGs"
    )
    parser.add_argument(
        "--viz",
        action="store_true",
        help="Visualize probability of success vs GED across the dataset"
    )
    parser.add_argument(
        "--model",
        type=str,
        default="claude-3.7-sonnet",
        help="LLM model to use for patch generation (default: claude-3.7-sonnet)"
    )
    parser.add_argument(
        "--attempts",
        type=int,
        default=10,
        help="Number of patch attempts per CPV/decompiler (default: 10)"
    )
    parser.add_argument(
        "--cpv",
        type=str,
        nargs='*',
        default=None,
        help="Limit to specific CPVs (e.g., '--cpv cpv1 cpv2 cpv3')"
    )
    parser.add_argument(
        "--decompiler",
        type=str,
        choices=['angr', 'ghidra', 'ida'],
        default=None,
        help="Limit to a single decompiler (angr, ghidra, or ida) for testing"
    )
    parser.add_argument(
        "--pass-three",
        action="store_true",
        help="Use pass@3 metric for visualization (success if any of 3 attempts correct)"
    )

    args = parser.parse_args()

    # Validate that at least one action is specified
    if not args.decompile and not args.patch and not args.grade and not args.distance and not args.viz:
        parser.error("At least one of --decompile, --patch, --grade, --distance, or --viz must be specified")

    # Get paths
    script_dir = Path(__file__).parent
    dataset_path = script_dir / "aixcc" / "nginx" / "dataset.toml"
    binary_path = script_dir / "aixcc" / "nginx" / "nginx"

    # Validate paths
    if not dataset_path.exists():
        print(f"ERROR: Dataset TOML not found at {dataset_path}")
        sys.exit(1)

    # Run decompilation if requested
    if args.decompile:
        if not binary_path.exists():
            print(f"ERROR: nginx binary not found at {binary_path}")
            sys.exit(1)
        analyze_dataset(dataset_path, binary_path)

    # Run patch generation if requested
    if args.patch:
        generate_patches(
            dataset_path,
            model=args.model,
            attempts=args.attempts,
            target_cpvs=args.cpv,
            target_decompiler=args.decompiler
        )

    # Run grading if requested
    if args.grade:
        grade_patches(
            dataset_path,
            target_cpvs=args.cpv,
            target_decompiler=args.decompiler
        )

    # Run distance computation if requested
    if args.distance:
        compute_distance(
            dataset_path,
            target_cpvs=args.cpv,
            target_decompiler=args.decompiler
        )

    # Run visualization if requested
    if args.viz:
        visualize_results(
            dataset_path,
            target_cpvs=args.cpv,
            target_decompiler=args.decompiler,
            pass_three=args.pass_three
        )


if __name__ == "__main__":
    main()
