# CLAS56 reconstruction

Goal: decompile Motorola's DSP56000 toolchain (CLAS56 v6.3, `assets/clas56-v6.3.0.zip`)
into simple portable C that builds on retro machines (NeXT, Atari Falcon, ...), with
output identical to the original Win32 executables.

## Layout

- `assets/` - original zip (never modify)
- `re/bin/` - extracted original EXEs (they run on this machine; they are the test oracle)
- `re/out/<TOOL>/` - Ghidra exports: `decomp.c`, `functions.txt`, `strings.txt`, `modules.txt`
- `re/crt/`, `re/names/` - `<TOOL>.names.txt` names/prototypes applied to the Ghidra project
- `re/scripts/` - `x86dis.py` (disassembly with string notes), `modmap.py` (function to
  module map via the RCS `$Id` strings), `crtmatch.py` (carries CRT names across binaries),
  `ExportAll.java` / `ApplyNames.java` (Ghidra headless)
- `src/<tool>/` - reconstructed sources, one directory per tool, original module names
  (e.g. `src/asm56000/eval.c`, taken from the embedded `$Id: eval.c,v 1.53 ...` strings)
- `tests/compare.py` - runs original and rebuilt tool side by side and diffs everything

## C conventions (portability rules)

- Dependency free: the sources use nothing but the ANSI C (C89) standard library. Allowed
  headers are exactly `assert.h ctype.h errno.h float.h limits.h locale.h math.h setjmp.h
  signal.h stdarg.h stddef.h stdio.h stdlib.h string.h time.h` (plus the project's own
  headers). No POSIX (`unistd.h`, `sys/*`, `fcntl.h`), no Win32, no third-party libraries.
  `tests/check_sources.py` enforces this.
- ANSI C89 only: prototypes, no `//` comments, no `long long`, no `<stdint.h>`, no C99
  declarations after statements, no VLAs.
- Assume `int` may be 16 bits (Pure C). Anything that must hold more than 16 bits is `long`.
  24-bit DSP words and 32-bit file fields are `long`/`unsigned long`. Watch `size_t`
  arithmetic and `malloc` sizes.
- Never read or write structures raw. The DSP COFF files are big-endian: decode and encode
  them byte by byte with helpers, so x86 and m68k hosts give identical files.
- Where the original relies on 32-bit wraparound, mask with `& 0xffffffffUL` so 64-bit
  `long` hosts agree.
- File names 8.3-friendly; keep memory use modest (the Falcon has 4-14 MB).
- Keep the original program structure and function names where they are known (error
  messages often name the function); strings and output formats must match byte for byte.
- A comment at the top of each file names the original binary/version and the module revision.

## Workflow per tool

1. Read `re/out/<TOOL>/decomp.c`. Ghidra drops varargs arguments (printf/fprintf/fscanf) and
   `local_NN` names are offset by 4 from the real ebp offsets. Use
   `python re/scripts/x86dis.py re/bin/<TOOL>.EXE <start> <end>` to check call arguments.
2. Write `src/<tool>/*.c`, add it to the `Makefile`.
3. Build (see below), then test from a directory holding the inputs:
   `python <root>/tests/compare.py <tool> args...` (must print `OK`). Cover error paths too.
4. Check that it compiles for m68k with 16-bit int:
   `/c/msys64/mingw64/bin/m68k-atari-mintelf-gcc -std=c89 -pedantic -Wall -mshort -c file.c`

## Building on this Windows machine

Use MSYS2 make from its own login shell (the Git Bash tool mixes MSYS runtimes and loses TMP):

    MSYSTEM=MINGW64 CHERE_INVOKING=1 /c/msys64/usr/bin/bash -lc 'cd /c/Arbeit/ASM56000 && make CC=gcc CFLAGS="-O2 -std=c89 -pedantic -Wall" EXE=.exe'

Test inputs: assemble with the original tools, e.g. `re/bin_ft/ASM56000.EXE -a -b -l t1.asm`.

## Tests

- `sh tests/run_all.sh` runs every `tests/<tool>/run_tests.sh` (each line a `compare.py` call
  that must print `OK`). Add a `run_tests.sh` with inputs for every tool you finish.
- `compare.py` options (before the tool name): `--stdin FILE`, `--ignore REGEX` (skip written
  files whose names match, e.g. tmpnam names), `--time` (fixed clock: runs the originals from
  `re/bin_ft/`, whose CRT `time()` is patched by `re/scripts/patchtime.py` to return 931953600,
  and gives the rebuilt tool `SOURCE_DATE_EPOCH=931953600`).
- Rebuilt tools that use the current time must take it from `SOURCE_DATE_EPOCH` when that is set
  (getenv + strtol), otherwise `time(NULL)`.
- Accepted difference: "[stderr line order differs (MSVC pipe buffering)]" - MSVC buffers stderr on
  pipes while `perror` writes directly.
- `python tests/check_sources.py` must pass (ANSI-only headers, no C99).
