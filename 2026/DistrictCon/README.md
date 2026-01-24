## Your AI Is Only as Smart as Your Decompiler: Binary Hacking in the Age of LLMs 
- Conference: DistrictCon 2026
- [**Slides Link**](https://docs.google.com/presentation/d/1Hi3R1meVWhT3Zi0fnk3gIE45vs1KJuioYVzCPexqLTY/edit?usp=sharing)
- Topics: decompilation, llm, reversing, hex-rays, angr, ghidra

### Abstract
In the aftermath of DARPA’s AIxCC, one thing has become clear: LLMs are now powerful enough to identify 0-days and fix them at scale, but these systems rely almost entirely on high-quality source code. Give them binaries without source code and their program comprehension collapses.  
  
Decompilation should bridge this gap by recovering source from binaries yet today’s decompilers often produce lossy, misleading code that sends LLMs down the wrong path. In this talk I connect lessons from AIxCC with ongoing research in binary decompilation, showing that enabling LLM-driven cyber reasoning on binaries requires more than “best-effort” guessing and demands high-fidelity, near-source recovery.  
  
Using case studies from autonomous patching, I demonstrate how even small decompilation errors derail otherwise capable LLMs and how improving decompilation quality directly boosts success rates. Finally, I present two open-source tools: the angr decompiler and our improved AIxCC PatcherY patching system which has been preliminarily extended to work on binaries. Together they chart a path toward a future where LLMs can reason about and repair software even when source is nowhere to be found.


### Useful Links
- [angr decompiler UI](https://github.com/angr/angr-management)
- [angr decompiler (code)](https://github.com/angr/angr)
- [Artiphishell CRS](https://github.com/shellphish/artiphishell)
- [PatcherY (Artiphishell patcher)](https://github.com/shellphish/PatcherY)

### Dataset
You can find the dataset and all the analyses here in the `dataset` folder. See the analyzer script for more.
