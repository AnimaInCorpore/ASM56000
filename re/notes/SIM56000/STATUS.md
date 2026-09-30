# SIM56000 status
- step 3 (naming agents): launched, groups A-H (see re/names/SIM56000/*.names.txt, re/notes/SIM56000/<group>.md)
- step 4/5: not started
- step 1 (hidden functions) done: 2260 functions in re/out/SIM56000 (scripts/CreateHidden.java, hidden_SIM56000.txt, namehidden.py); step 2 done: names merged (override.txt), splitsim2.py/filemap.txt; step 3 in progress
- step 3: gentab_sim.py + simdata.py generate src/sim56000/simd_*.c/simdata.h (auto layout of ALL initialized data); header/TRANSLATE pending
- data generators verified (47k values); simdata.h/simd_*.c compile gcc + m68k -mshort; remaining: sim56000.h, TRANSLATE.md
- DONE (this pass): hidden functions created in Ghidra (2260 fn), names merged, corrected filemap (splitsim2.py), src/sim56000/{sim56000.h,simdata.h,simd_*.c,simbss.c,simproto.h} generated+verified, TRANSLATE.md (10 work packages)
- regenerate: python re/scripts/gentab_sim.py ; python re/scripts/genproto_sim.py ; verify: gentab_sim.py --verify then build re/out/SIM56000/simverify*.c with simd_*.c and compare with simverify.exp (mod CR)
