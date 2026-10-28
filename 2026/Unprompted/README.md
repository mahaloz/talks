## Kuna: Building a Competitive C Decompiler Through Autonomous AI Research
- Conference: Unprompted Con 2026
- [Slides](./unprompted_con_talk.pptx)
- [**Video Link**]() 
- Topics: decompilation, llm, reversing

### Abstract
At the core of every computing system is compiled code known as binaries. Decompilers turn binaries into source-like code, helping researchers and AI agents analyze software without its source. Despite decades of research, compilation’s information loss leaves decompilers dependent on expert-built heuristics that don’t scale.
Can agents develop better decompilation methods, rather than just use existing tools?
I present Kuna, an experiment extending my PhD research by giving agents a dataset, a problem space, and a platform to improve. Starting from Ghidra, we ported the decompiler to Rust, made its passes tunable, and built loops for agents to investigate failures and evaluate new methods. Within three months, Kuna reached a 33.7% perfect rate on C control flow structure versus Hex-Rays’ 32.2% on DecBench (33k samples).
I’ll show agent-developed methods, compare decompilation, and explain where autonomy worked, where human direction helped, and how it’s changing modern research.

### Useful Links
- [decompile.run](https://decompile.run)
- [Kuna (GitHub)](https://github.com/noelo-lab/kuna)
- [Kuna (Page)](https://kuna.noelo.org)

### Dataset
You can find the demoed binaries in this folder.
