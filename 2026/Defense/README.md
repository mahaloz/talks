## Toward a Science of Reverse Engineering
- Conference: None (Arizona State University, Defense)
- [Slides Link](https://docs.google.com/presentation/d/1e9ekcw35G1C47EaUYuemcCssgk_QNzf6Fv3JepUbdSE/edit?usp=sharing) 
- [Video Link](https://youtu.be/lqOyeOFA6J8)
- Topics: decompilation, llm, reversing, hex-rays, angr, defense, dissertation

### Abstract
This was the (recorded practice) of my defense on March 30th, 2026.
Below is the abstract of my dissertation associated with the talk.

Modern software systems are increasingly built, modified, and deployed by people who did
not create them. As a result, software reverse engineering (SRE), the process of recovering
structure, intent, and behavior from existing artifacts, has become a fundamental part of
interacting with software. Despite its importance, SRE remains largely an art: its goals
are inconsistently defined, its processes are poorly characterized, and its success is often
measured only through downstream outcomes.

This dissertation argues that SRE can be transformed into a science by systematically
studying three interconnected aspects of the discipline: the techniques that enable reverse
engineering, the processes by which those techniques compose into effective workflows,
and the applications that ultimately define reverse engineering’s utility.

First, we study reverse engineering techniques by introducing closeness-to-source as a
principled metric for evaluating decompilation quality and designing SAILR, a compiler-
aware decompilation framework that demonstrates how metrics-driven design advances
individual techniques. Second, we investigate the reverse engineering process through an
empirical study of human and LLM-assisted workflows, demonstrating that understand-
ing emerges through the iterative, strategy-dependent composition of multiple techniques.
Third, we examine the applications of reverse engineering through PatcherY, an autonomous
vulnerability patching system, showing that applications provide a concrete measure of
whether our techniques and metrics serve real-world needs.

Together, these contributions provide a unified foundation for SRE that connects tech-
niques, processes, and applications. By making each aspect explicit and measurable, this
work takes a step toward a science of reverse engineering.


### Useful Links
- [Dissertation]()
- [Decompilation Wiki](https://decompilation.wiki)
- [angr decompiler UI](https://github.com/angr/angr-management)
- [Artiphishell CRS](https://github.com/shellphish/artiphishell)
