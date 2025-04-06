## Buccaneers of the Binary: Plundering Compiler Optimizations for Decompilation Treasure
- Conference: REverse 2025
- [Talk Schedule Link](https://re-verse.sessionize.com/session/776160)
- [Talk Video](https://www.youtube.com/watch?v=VP29biKLoSw)
- Topics: decompilation, reversing, hex-rays, angr, binary ninja, ghidra, optimizations

### Abstract
From fixing a smart oven to exploiting a pesky drone, reverse engineers have long understood that the world is run by binaries. As such, decompilers, which turn binaries into source-like code, have become a cornerstone tool of the reversing community. Decompilers like IDA Pro, Ghidra, and Binja are hailed as our saviors from the verbose land of assembly.

Despite the accolades we bestow upon our favorite decompilers, we've all encountered the frustration of lousy decompilation. We've wrestled with a series of broken if-statements that stubbornly refuse to become a Switch. We've navigated through a maze of gotos that create an unnecessary spaghetti of code. And we've scratched our heads at code that just seems off—maybe duplicated? Maybe it is non-existent in the source? Regardless, something is wrong.

So what do all these problems have in common? Surprisingly, they aren't just buggy decompilers. They are fundamental flaws in the way we deal with compiler optimizations. Interestingly, not all compiler optimizations are equally destructive, and many can be reversed!

In our USENIX 2024 work, SAILR[^1], we not only measured the destructiveness of each compiler optimization but also pioneered techniques to reverse their effects. These cutting-edge algorithms are now implemented in the new angr decompiler, an open-source decompiler made by the hackademics of Shellphish.

In this talk, we will take a deep dive into the rocky seas that are compiler optimizations. We will explore the worst optimizations for your decompiler, with examples, and how you might reverse them, with demos. Finally, we'll talk about what we learned in the process and how we think compiler optimizations will play a future role in decompilers.

### Useful Links
- [angr decompiler UI](https://github.com/angr/angr-management)
- [angr decompiler (code)](https://github.com/angr/angr)
- [optimization reversing algorithms](https://www.usenix.org/system/files/sec23winter-prepub-301-basque.pdf)
- [evaluation on decompilers](https://github.com/mahaloz/sailr-eval)


[^1]: Basque, Zion Leonahenahe, et al. "Ahoy SAILR! There is no need to DREAM of C: A compiler-aware structuring algorithm for binary decompilation." 33st USENIX Security Symposium (USENIX Security 24). 2024.
