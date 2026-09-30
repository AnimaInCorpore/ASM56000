# SIM56000 status
- step 3 (naming agents): launched, groups A-H (see re/names/SIM56000/*.names.txt, re/notes/SIM56000/<group>.md)
- step 4/5: not started
- step 1 (hidden functions) done: 2260 functions in re/out/SIM56000 (scripts/CreateHidden.java, hidden_SIM56000.txt, namehidden.py); step 2 done: names merged (override.txt), splitsim2.py/filemap.txt; step 3 in progress
- step 3: gentab_sim.py + simdata.py generate src/sim56000/simd_*.c/simdata.h (auto layout of ALL initialized data); header/TRANSLATE pending
- data generators verified (47k values); simdata.h/simd_*.c compile gcc + m68k -mshort; remaining: sim56000.h, TRANSLATE.md
- DONE (this pass): hidden functions created in Ghidra (2260 fn), names merged, corrected filemap (splitsim2.py), src/sim56000/{sim56000.h,simdata.h,simd_*.c,simbss.c,simproto.h} generated+verified, TRANSLATE.md (10 work packages)
- regenerate: python re/scripts/gentab_sim.py ; python re/scripts/genproto_sim.py ; verify: gentab_sim.py --verify then build re/out/SIM56000/simverify*.c with simd_*.c and compare with simverify.exp (mod CR)

## Translation status (latest)
Done and verified against the original in the Unicorn emulator (tests/sim56000/emu/diff_*.py, 0 differences): avltree, oprefs, mdisk, radix,
exprmp/exprop/exprprim/miscx (P1 expression evaluator), memacc + insexec (memacc tail), decode, insstat, insattr, alu, igrp, devreg,
disfmt, disasm and the first part of asm.c (bitrev16 .. dis_ea_tokens).  Method: HOWTO.md.
Not translated yet: the rest of asm.c (inline assembler, hid_4243f0 .. qq_code), P4 core/emi/dax/gpio/shi, P5 peripherals B, P6 front end
(state, console, cmdloop, main, help, cmdparse, dispval, macro, cmdexec, run, snap, watch), P7 (cmdh1-3, iochan), P8 (dbinfo, cofscan,
hostio, cdb*), P9 (cdbeval, cdbparse, cdblex), P10 profiler.  No Makefile target / simtest run until those exist.
Parallel agent attempt: ten agents were started in git worktrees (.claude/worktrees/, git-ignored, branches worktree-agent-*) and stopped
before finishing; their uncommitted partial work (e.g. dbinfo.c, cmdh1/cmdh2, peripherals B, core) remains there and can be inspected/merged.
Package extension headers src/sim56000/sim_{asm,core,periph,front,cmd,dbg,ceval,prof}.h exist for per-package declarations.
