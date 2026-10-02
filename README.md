# ASM56000 - CLAS56 v6.3 reconstruction

Reconstruction of Motorola's DSP56000 toolchain (CLAS56 v6.3) as simple, portable
ANSI C89 that builds on retro machines (NeXT, Atari Falcon, ...).  The original Win32
executables are the test oracle: the rebuilt tools must produce identical output.

See `CLAUDE.md` for the portability rules, the build recipe and the workflow.

## Status

| Tool | State |
|------|-------|
| cldinfo, cldlod, cofdmp, dsplib, srec, strip, tiohist | done, tested against the originals |
| asm56000 (assembler) | working; nearly all cases in `tests/asm56000` match. Known weak spots: parts of the object writer are still fitted to test inputs (special cases in the relocatable writer), and error handling for malformed instruction operands is incomplete. See `tests/asm56000/cases.txt` |
| dsplnk (linker) | working; all cases in `tests/dsplnk` match. ABI/ELF output (`-c`, target 100) is stubbed (`abistub.c`); the port is in progress (`abi*.c`, `elfout.c`, `cof2elf.c` are work in progress and not yet in the Makefile). The hidden `-j` SDI optimiser is untested (it crashes in the original) |
| sim56000 (simulator) | analysis complete, foundation translation started: all 14 AVL routines plus memory/pool helpers translated; integration tests use reconstructed allocation and two comparators. No runnable simulator yet (see below) |

## Layout

- `assets/` original zip; `re/bin/` extracted originals; `re/out/<TOOL>/` Ghidra exports
  (`mod/` per-module splits); `re/names/`, `re/notes/` naming pass results and per-module notes;
  `re/scripts/` reverse-engineering helpers and table generators.
- `src/<tool>/` reconstructed sources; `tests/<tool>/` test inputs and `run_tests.sh`;
  `tests/compare.py` runs original and rebuilt tool side by side.

## Build and test

    make CC=gcc CFLAGS="-O2 -std=c89 -pedantic -Wall" EXE=.exe
    sh tests/run_all.sh
    python tests/check_sources.py

`make CC=m68k-atari-mintelf-gcc EXE=.ttp` builds for the Falcon.

## SIM56000 plan

`SIM56000.EXE` is a Win32 full-screen console program that ignores redirected stdin/stdout, so
the oracle is its session log (`LOG` command), driven by `tests/sim56000/condrive.py` and
`simtest.py` with golden sessions.  The rebuilt tool gets a plain line-oriented stdin/stdout
front end that prints the same transcript text; the original screen UI is not ported.
All 2260 functions are named and split into 65 modules (`re/notes/SIM56000/filemap.txt`);
`src/sim56000/` holds the shared header and generated data tables (`re/scripts/gentab_sim.py`).
`re/notes/SIM56000/TRANSLATE.md` defines 10 work packages (foundation and expressions,
instruction engine, assembler/disassembler, core and peripherals, front end, command
handlers, debug info, C expressions, profiler) with the suggested order.

## Notes

- The Motorola binaries and their behaviour belong to their owners; only the reconstruction
  and tooling in this repository are original work.
