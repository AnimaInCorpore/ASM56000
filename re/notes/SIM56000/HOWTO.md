# SIM56000 translation - how the finished packages were done (read this first)

Rules: `CLAUDE.md` (portable ANSI C89, `long` for anything > 16 bit, `& 0xffffffffUL` for 32 bit wrap, allowed headers only,
`python tests/check_sources.py` must stay OK).  Work packages and interfaces: `TRANSLATE.md`.  Data tables/strings are already generated
(`src/sim56000/simd_*.c`, `simdata.h`, `simbss.c`, prototypes `simproto.h`, structs `sim56000.h`); do not hand edit the generated
`simd_*.c` (regenerate through `re/scripts/gentab_sim.py` if a *type* has to change).

## Loop per module
1. Read the Ghidra output `re/out/SIM56000/mod/<module>.c` (one file per module; function header `/* ==== name @ addr ==== */`)
   and the notes for the group (`re/notes/SIM56000/*.md`).  `python re/scripts/x86dis.py re/bin/SIM56000.EXE 0x<start> 0x<end>`
   disassembles (Ghidra drops varargs, mislabels arguments of functions called through tables, reads `char`/`byte` return values
   as `void`, and often misses the *start* of do-while loops: check the disassembly whenever a loop or a compare looks odd).
2. Write `src/sim56000/<module>.c` in C89.  Keep original function names (they are the names in the Ghidra file).  Small repetitive
   handler families: write a converter script in `re/scripts/g2c_<name>.py` (see `g2c_attr.py`, `g2c_alu.py`, `g2c_dis.py`,
   `g2c_dec.py`) and hand-fix the rest.  Structure/offset access of the original (`*(int *)(p + 0x1c)`) must become a named struct member
   of the host struct (never rely on host struct layout matching the 32 bit original: `sizeof(long)` may be 8), or an explicit word array.
3. Differential test against the original executable running in the Unicorn emulator (`pip install unicorn`; the EXE is `re/bin/SIM56000.EXE`):
   `tests/sim56000/emu/diff_<module>.py`, run with `cd tests/sim56000/emu && python3 diff_<module>.py` (prints a line per function
   with `N cases, 0 differences`; exit code 1 on any difference).  Add it to nothing else (run_all.sh globs `diff_*.py`).
4. `gcc -std=c89 -pedantic -Wall -c file.c` clean, `python tests/check_sources.py`, commit.

## The emulator harness (tests/sim56000/emu, re/scripts/emu.py)
* `pe = PE(EXE)`; `pe.call(va, [args...])` runs an original function (cdecl, returns EAX as unsigned 32 bit); `pe.w32/r32/wbytes/rbytes/alloc`
  access the emulated memory (image sections are mapped at their virtual addresses, so static data such as tables/strings is available;
  BSS is zero).  `pe.uc.hook_add(UC_HOOK_CODE, cb, begin=a, end=a)` lets you intercept calls to functions you do not test (log arguments, set
  `EIP` to the return address and add 4 to `ESP`): `diff_alu.py` does that for `core_copy_reg` etc.
* `common.build(name, [translation units], [generated data files])` compiles the units plus `stubs.c` into a shared library (`ctypes`);
  symbols of untranslated modules become empty stand-ins (autostubs) or weak stubs from `stubs.c` (add yours there with `W` = weak; tests can
  route them to callbacks `cb_...` that call the original through the emulator, or log calls like `call_log` in stubs.c).
  Data files needed: usually `simd_dec.c simd_e.c simd_a.c simd_b.c simd_c.c simd_f.c simd_dev.c simbss.c`.
* Set the same global state in both worlds (original: fixed VA of the global, see `re/notes/SIM56000/datamap.txt` for names/addresses of data
  and `re/out/SIM56000/decomp.c` for BSS; mine: `ctypes.c_long.in_dll(lib, 'name')`).  Random state + random arguments, compare return
  values, output buffers and every global/table entry the function may write.  Compare pointers by index/offset inside a table.  Cover error paths.
* Functions that call the C library (sprintf, strcmp...) work in the emulator only if the CRT code they reach is self contained; the CRT
  (`printf`, `strlen`...) is inside the EXE, so it normally runs fine.  Win32 imports do not (hook or avoid).
* Original code that is not reachable from a translated function stays out of a test; stub it (weak stub) instead.

## Pitfalls found so far
* Ghidra missed function entry points that are only reached through tables (`extern void h_XXXXXX()` in `simd_*.c` without a definition ->
  the test build reports an autostub, results are garbage): read the disassembly at that address and write the function by hand.
  Also functions folded into their neighbour (tail-call `jmp`): check `x86dis.py` at the start address.
* `bool`/`char`/`byte` returns: only the low 8 bits are defined in `eax`; compare accordingly.  Table handlers called with fewer
  arguments than the code reads see stack garbage: use the disassembly to see which arguments really are read.
* Arithmetic: 32 bit `int`/`uint` wrap in the original.  On 64 bit hosts mask (`& 0xffffffffUL`), keep values that are signed 32 bit as
  signed `long` (sign extend with `((x & 0xffffffffUL) ^ 0x80000000UL) - 0x80000000L`).  x87 code: NaN compares treat `== 0.0` as true etc.
  (see exprop.c); doubles are handled bytewise where NaN payloads matter.
* Pointers passed as `long` (`(long)&x`) are the project convention for the untranslated thunk interfaces (`dev_mem_read`, `periph_call`).
* Never read/write structs raw from files: big endian decode byte by byte (`BE32`).
* The inline sprintf/strcpy idioms of the decompiler (`rep movsd` loops, `~uVar - 1` = strlen) are just strlen/strcpy/memcpy.
* Test global buffers with the original's fixed size; `abort()` in the original (impossible cases) can be skipped in tests.

## Git
Commit small verified steps; `git add -A` is fine (build/ is ignored).  Do not rewrite shared files wholesale: `sim56000.h` and `simproto.h` are
shared between packages - make minimal local edits (add members / fix a prototype), keep the line order otherwise.
