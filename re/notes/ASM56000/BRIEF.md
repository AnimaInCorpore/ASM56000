# Naming / data-structure pass for ASM56000.EXE (brief for all group agents)

Project: C:\Arbeit\ASM56000 reconstructs Motorola's DSP56000 assembler ASM56000.EXE
(CLAS56 v6.3.0, 1999, Win32, MSVC 5, static CRT, no symbols) as portable ANSI C.
Read C:\Arbeit\ASM56000\CLAUDE.md first. This pass does NOT write C sources; it
produces names, prototypes and data-structure knowledge so that the modules can
later be translated consistently in parallel.

## Inputs

- `re/out/ASM56000/mod/<module>.c` - Ghidra decompilation of each original source
  module (split by address; module = original file, e.g. eval.c). CRT functions are
  already named (fopen, fprintf, strcmp, sin, ...); printf-style call arguments are
  recovered where Ghidra could (`va0` = value it could not track: check disassembly).
  Ghidra's `local_NN` names are offset by 4 from the real `[ebp-NN]`.
- `re/out/ASM56000/modules.txt` - addr, name, size, module, data-reference votes.
- `re/out/ASM56000/functions.txt` - call graph (calls:/callers:).
- `re/out/ASM56000/strings.txt` - every string with referencing functions.
- `re/out/ASM56000/globals.txt` - every referenced global data address: gap to the
  next referenced address, owner module ($Id-based: the module whose .data holds it;
  `bss` = uninitialized), and which modules use it.
- `re/crt/ASM56000.names.txt` - CRT names (don't rename those).
- Binary `re/bin/ASM56000.EXE` (runs here; use it to experiment: e.g.
  `re/bin_ft/ASM56000.EXE -a -b -l t.asm` with your own small test sources in a
  scratch dir under `re/notes/ASM56000/scratch_<group>/`).
- Disassembler: `python re/scripts/x86dis.py re/bin/ASM56000.EXE <start> <end>`.
- Section layout: .text 0x401000, .rdata 0x44d000, .data 0x44e000 (initialized to
  0x45d800, then BSS to 0x466d24). CRT code starts at 0x43dcd0, CRT data at 0x45a450.
- Module order in .data ($Id strings): mchglb 0x44e030, asmglb 0x44f668, dspasm,
  amode, arith, data, debug, encode, error, eval, func, input, listing, macro,
  object, procop, procxy, pseudo, scs, sdi, section, symtab, util 0x459568.
  mchglb and asmglb are data-only (global tables: instruction table, error
  message table, option tables, expression function table at 0x450048 ...), except
  that asmglb also holds the 18 math wrapper functions at 0x401000-0x40116d.

## Deliverables (only these two files; do not touch other groups' files)

1. `re/names/ASM56000/<group>.names.txt` - tab separated, one line each:
   `addr<TAB>F<TAB>name<TAB>prototype<TAB>confidence<TAB>module`   for EVERY function
   of your modules, and
   `addr<TAB>D<TAB>name<TAB>type<TAB>confidence<TAB>owner-module<TAB>size-bytes`   for
   every global your modules use that you can name (static and shared ones).
   - Prototypes must parse in Ghidra with basic types only: int, long, unsigned
     long, char *, void *, double, ... (use `void *` for struct pointers; mention
     the real struct in the notes). Use __cdecl arguments exactly as the code uses
     them (count and order).
   - Names: lower case with underscores in the style of 1990s Unix C
     (`eval_expr`, `get_token`, `sym_lookup`, `lst_line`...). Derive names from
     error/debug messages and behaviour. Globals of the original were probably
     short (`Pass`, `Lst_fp`...) - just be consistent and descriptive.
   - Globals used by several modules: name them anyway; conflicts between groups
     will be resolved centrally. Prefer the name that describes the meaning.
   - For tables in mchglb/asmglb that your modules index: give element size, count,
     and element layout in the notes.
2. `re/notes/ASM56000/<group>.md` - for each of your modules:
   - purpose of the module (2-5 lines);
   - every function: address, proposed name, one or two lines on what it does,
     arguments/return value;
   - every struct you meet (symbol table entry, section, macro, input file/stack
     entry, expression value/term, listing line, instruction table entry, ...):
     field offsets, sizes, types, meaning, and evidence (function + offset use);
     say which allocation (malloc size) creates it;
   - global variables: address, name, type, meaning, who writes/reads;
   - cross-module interfaces (functions of other modules you call and what you
     expect them to do);
   - quirks/bugs worth reproducing (e.g. Y2K year printing, buffer overruns that
     affect output).
   Keep it factual and compact; quote addresses so others can verify.

Work carefully rather than exhaustively on huge functions: for big switch-based
functions describe the structure and the case meanings. Do not modify anything in
re/out, re/crt, src or tests. Finish with a short summary in your final answer
(counts of named functions/globals, the main structs found, open questions).
