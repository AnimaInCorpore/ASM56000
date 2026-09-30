# Naming / data-structure pass for SIM56000.EXE (brief for group agents)

Project: C:\Arbeit\ASM56000 reconstructs the CLAS56 v6.3 tools as portable C89. SIM56000.EXE
("MOTOROLA DSP56000 SIMULATOR: VERSION 6.3.0 01-15-1999", MSVC, static CRT, ~1330 user functions
0x401000-0x4833fa, CRT from 0x483400) is a Win32 full-screen console program (ReadConsoleInput,
private screen buffer).  READ re/notes/SIM56000/COMMANDS.md FIRST (oracle = session logs) and
re/notes/SIM56000/filemap.txt (approximate module ranges; there are no $Id strings, so boundaries
are string-cluster based and may be corrected with evidence).  Inputs: re/out/SIM56000/mod/<module>.c
(Ghidra output split by address), functions.txt, strings.txt, ../../crt/SIM56000.names.txt (CRT names),
Ghidra local_NN names are offset by 4.  The assembler's inline-assembler / disassembler tables may share
code with ASM56000 (see re/scripts/xmatch.py).  Same deliverables/format as the DSPLNK brief below
(names file re/names/SIM56000/<group>.names.txt, notes re/notes/SIM56000/<group>.md) - replace DSPLNK by
SIM56000 and ignore the DSPLNK specific paragraphs.  Suggested groups: exec (0x401140-0x41c13f, split in
two), devinit+asm+asmtab, state+cmdloop+macro+fmt+console+dispval, coffrd+cofload+symdisp+iohist+help+run,
profile+source+stats+radix+mdisk+expr+misc, cdbutil+cdbsym+profrep+cdbbt, cdbeval+cdbcall+misc2+dirs+tail.
Test the oracle with: python tests/sim56000/condrive.py --screen re/bin/SIM56000.EXE script.txt

--- DSPLNK brief (for the format) ---
# Naming / data-structure pass for DSPLNK.EXE (brief for all group agents)

Project: C:\Arbeit\ASM56000 reconstructs Motorola's DSP linker DSPLNK.EXE
(CLAS56 "DSP Linker Version 6.3.7", 1999, Win32, MSVC 5, static CRT, no symbols,
incrementally linked) as portable ANSI C. The assembler ASM56000.EXE is being
analysed in parallel by other agents: its modules arith/error/eval/func/input/object/
sdi/symtab/util share names (older/newer revisions of the same sources) - read their
notes in re/notes/ASM56000/*.md and names in re/names/ASM56000/*.names.txt when they
exist (they may still be in progress) and keep names consistent with them where the
code clearly corresponds. re/out/DSPLNK/xmatch_ASM56000.txt lists the 48 DSPLNK
functions that are byte-identical to ASM56000 functions.
Read C:\Arbeit\ASM56000\CLAUDE.md first. This pass does NOT write C sources; it
produces names, prototypes and data-structure knowledge so that the modules can
later be translated consistently in parallel.

## Inputs

- `re/out/DSPLNK/mod/<module>.c` - Ghidra decompilation of each original source
  module (split by address; module = original file, e.g. eval.c). CRT functions are
  already named (fopen, fprintf, strcmp, sin, ...); printf-style call arguments are
  recovered where Ghidra could (`va0` = value it could not track: check disassembly).
  Ghidra's `local_NN` names are offset by 4 from the real `[ebp-NN]`.
- `re/out/DSPLNK/modules.txt` - addr, name, size, module, data-reference votes.
- `re/out/DSPLNK/functions.txt` - call graph (calls:/callers:).
- `re/out/DSPLNK/strings.txt` - every string with referencing functions.
- `re/out/DSPLNK/globals.txt` - every referenced global data address: gap to the
  next referenced address, owner module ($Id-based: the module whose .data holds it;
  `bss` = uninitialized), and which modules use it.
- `re/crt/DSPLNK.names.txt` - CRT names (don't rename those).
- Binary `re/bin/DSPLNK.EXE` (runs here; use it to experiment: e.g.
  `re/bin_ft/DSPLNK.EXE ... (make inputs with re/bin_ft/ASM56000.EXE -b t.asm)` with your own small test sources in a
  scratch dir under `re/notes/DSPLNK/scratch_<group>/`).
- Disassembler: `python re/scripts/x86dis.py re/bin/DSPLNK.EXE <start> <end>`.
- Section layout: .text 0x401000 (0x401000-0x40150f = incremental-link jump thunks,
  user code 0x401a20-0x43bc4e), .rdata 0x450000, .data 0x453000 (initialized to
  0x461200, then BSS to 0x46dadc). CRT code starts at 0x43c2d0.
- Module order in .data ($Id strings): dsplnk 0x453a30, arith, error, eval, fixup, func,
  input, lib, lnkglb 0x457b10 (data-only global tables), map, memctl, object, sdi,
  symtab, util 0x45aa40. The module map in modules.txt is vote-based: sdi.c got no
  votes (it is probably the unvoted functions 0x42944b-0x429870 at the start of the
  "symtab" run) and util's run (271 functions) may contain other modules - report
  corrected boundaries with evidence.
- Usage text: run re/bin/DSPLNK.EXE without arguments.

## Deliverables (only these two files; do not touch other groups' files)

1. `re/names/DSPLNK/<group>.names.txt` - tab separated, one line each:
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
2. `re/notes/DSPLNK/<group>.md` - for each of your modules:
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
