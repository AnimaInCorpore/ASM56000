# l1_main notes — DSPLNK.EXE: dsplnk.c, lnkglb, error.c, lib.c, input.c

Names proposed here are in `re/names/DSPLNK/l1_main.names.txt`. Confidence
"high" = confirmed by an error/usage string or unambiguous control flow;
"medium" = plausible from context/naming pattern, not directly proven;
"low" = placeholder for a scratch/bookkeeping variable whose exact role in
the algorithm is still unclear (kept distinguishable rather than left
`DAT_xxx`).

## 1. Overall link algorithm

DSPLNK links in **two passes** over the same input list (object files given
on the command line/`-f` command file/`DSPLNKOPT`, plus any `-l` libraries),
driven from `main` (`00401a20`):

1. **Command-line setup.** `main` installs signal handlers for SIGINT(2),
   SIGFPE(8) and SIGSEGV(11) (`lnk_signal_handler`, `0040303c`), derives the
   program's base name from `argv[0]` (extension stripped), reads
   `DSPLNKOPT` and does a *pre-scan* of `argv` for `-f`; if `-f` or
   `DSPLNKOPT` is present, `expand_dsplnkopt` (`0040343e`) splices the
   `DSPLNKOPT` tokens and any `-f <file>` command-file contents (recursively,
   `read_command_file`/`004039e5`) into the effective argument vector before
   any further parsing (see §2). It scans once for a hidden `-c` flag and for
   `-q` (banner/interrupt-message suppression) and once for `-e` (error
   file, opened immediately by `open_error_file_opt`/`00402a24` so that even
   very early command-line errors can be redirected).
   `default_base_name` (`00403172`) computes the default object/map file base
   name from a `-l` argument if present, else from `argv[0]`.
2. **`init_link_state_pass1`** (`00402b44`) resets all pass state, builds the
   default library search-path list node `"DEFAULT"`, and sets the global
   pass indicator `Cur_pass` (`00461294`) to 1.
3. **Pass 1** — `parse_cmdline_options` (`00402017`) is a `getopt`-style
   scan (see §2) that, for every input file name (`-b` and non-option
   arguments) and every `-l` library, calls `process_input_files`
   (`00414110`, `input.c`) which opens each file (`open_next_input_file`,
   `004143b4`) and, per object module, calls `process_module`
   (`004146c6`) — reading the COFF headers, walking the module's
   section/symbol table once, building the section map, counters and
   allocation tables (§4), and — for libraries — repeatedly rescanning
   the archive (`scan_library`, `0041c6d7`/`scan_library_members`,
   `0041c7d9`) pulling in members that define a still-undefined `GLOBAL`
   symbol, iterating (`Lib_rescan_needed`, `004611fc`) until a full pass
   pulls in nothing new. Undefined symbols are therefore resolved
   **during pass 1**, library member by member, by a fixed-point loop
   over "pull if it defines a symbol some already-loaded module
   references and it is not yet defined" (§5). No linker output is
   written in pass 1; it only builds the in-memory section/symbol
   database and counters.
4. Between passes, `main` prints the "Beginning pass 2" banner (if `-v`),
   calls `init_link_state_pass2` (`00402cd2`, sets `Cur_pass`=2) and,
   if no default object file was already named, opens one
   (`open_default_object_file`, `00403385`).
5. **Pass 2** — the same `process_input_files`/`process_module` are run
   again (branch `Cur_pass==2` inside most `input.c` functions); this time
   relocations are actually applied and the object/map/ELF-debug output is
   produced: for each defined-symbol record `apply_module_fixups`
   (`00416cf8`) computes final addresses/values, `check_value_truncation`
   (`00417a64`) checks for overflow of the target field width, and (unless
   `-z` strip) `emit_pass2_record` (`0041882a`) writes the corresponding
   output record. Section nesting for `SDI`/overlay pseudo-records is
   tracked incrementally (`section_nest_track`, `0041874a`) and `@SDI(...)`
   source-debug expressions are parsed and resolved by
   `parse_sdi_expression` (`0041839c`), which looks up up to three symbols
   via a symtab-module helper (`thunk_FUN_0040a571`, not part of this
   group).
6. **`finish_link`** (`00402e52`, called as `thunk_FUN_00402e52(0)` right
   after pass 2) reads a memory-control file if `-r` was given, writes the
   symbol table/relocation/map/ELF output (calls into `map.c`/`object.c`/
   `symtab.c`, all other groups), closes the object and map files, and
   deletes an incomplete object file if pass 2 produced errors and `-z`
   strip was requested but incomplete.
7. Back in `main`: optionally creates a separate ELF debug-information file
   next to the object file (`thunk_FUN_00432799`, object.c) when the target
   is `DSP56600` (`Cpu_magic==0x2cb`), `-b` object output is a real file
   (not stdout) and `-i` was not given; prints the final
   `"%s: errors: %d warnings: %d\n"` summary if the hidden `-s` option was
   given; `exit(Error_count)`.

## 2. dsplnk.c — main program, command line, phases

Purpose: process startup, argument/`DSPLNKOPT`/command-file expansion, the
main `getopt`-style option scanner, global per-pass state reset, the
target-processor table lookup, and top-level pass sequencing (`main` itself
lives here; the pass bodies live in `input.c`).

### Functions

- `main` (`00401a20`) — see §1.
- `lnk_usage` (`00401dfe`) — prints (if not quiet) the version banner, then
  the full usage text (verified against `re/out/DSPLNK/strings.txt`
  00453bcc–004540cc):
  `Usage: %s [-a] [-b[<objfil>]] [-e<a|w> <errfil>] [-f<argfil>] [-g] [-i]
  [-l<library>] [-m[<mapfil>]] [-n] [-o<mem>[<ctr>][<map>]:<origin>]
  [-p<lpath>] [-q] [-r[<memfil>]] [-u<symbol>] [-v] [-x<opt>[,<opt>...]]
  [-z] <lnkfil>...` plus a two-column explanation of every option
  and the `DSPLNKOPT` environment variable, then `exit(-1)`.
- `strip_ext_copy` (`00401fe0`) — `strcpy` then remove the trailing
  `.ext`; used to derive the ELF debug file name from the object file name.
- `parse_cmdline_options` (`00402017`) — the pass-1/pass-2 option loop
  built on `dsp_getopt` (see below) with option string
  `"AaB:bCcE:e:F:fGgIiL:l:M:m:Nn?o:pP:q:R:rSsTtU:u:Vv:xX:z"`-like coverage
  (actual accepted-letters string is
  `s_AaB_b_CcE__e__F_f_GgIiL_l_M_m_Nn_...`); dispatches on the lower-cased
  option letter:
  - `a` → `Opt_a_autoalign=1` (not if `-i`)
  - `b` → default/explicit object file name handling, opens the object
    output file (or `stdout` if the name is literally `-`)
  - `c` → **undocumented**: `Opt_c_flag=1` (see quirk below)
  - `e` → consumed (already handled earlier by `open_error_file_opt`)
  - `f` → consumed (already expanded by `expand_dsplnkopt`)
  - `g` → `Opt_g_debug=1`
  - `i` → `Opt_i_incremental=1`
  - `l` → stops option scanning (library name marks end of switches unless
    in the special pass)
  - `m` → open map file (or `stdout` if name is `-`)
  - `n` → `Opt_n_ignore_case=1` ("ignore symbol case")
  - `o` → **memory origin**, see below
  - `p` → `add_library_path` (`004044bd`)
  - `q` → consumed (handled earlier)
  - `r` → open memory-control file (with fallback: retries without the
    file's original extension if the first `fopen` fails)
  - `s` → **undocumented**: `Opt_s_summary=1`, enables the final
    `"errors: %d warnings: %d"` line
  - `t` → **undocumented**: `Opt_t_upcase_names=1`
  - `u` → force-define an undefined symbol (`thunk_FUN_0042cae9`, symtab.c)
  - `v` → `Opt_v_verbose=1`, with optional numeric verbosity level parsed
    via `sscanf(..., "%d", &Verbose_level)`
  - `x` → linker option (`thunk_FUN_00425cf1`, memctl/util group — see
    the `-x` keyword table in §3)
  - `z` → `Opt_z_strip=1`
  - any other letter → fatal "Illegal command line option"
  After the loop: `-g`+`-z` and `-z`/`-i`, `-a`/`-i` conflicts are checked
  (one of the two is silently disabled with a warning); also fatals if the
  object file name collides with the executable name or the map file name.
  **`-o` memory-origin syntax**: `-o<mem>[<ctr>][<map>]:<origin>`.
  `<mem>/<ctr>/<map>` (memory space / location counter / memory mapping
  names — single letters/short tokens looked up in the memctl tables, not
  this group's code) are parsed by `thunk_FUN_0042e743` (memctl.c) into a
  small on-stack struct, then `thunk_FUN_0042c4e2` (memctl.c) looks up (or
  creates) the corresponding origin-record; `<origin>` is parsed with
  `sscanf(ptr, "%lx", &rec[7])` after an optional leading `$` is skipped,
  and a "has explicit origin" bit (`0x100000`) is set in `rec[2]`.
- `deref_dword` (`00402871`) — trivial `return *p;`; used once, as an
  interface-compatible "peek next" callback in `process_input_files`'s
  pass-2 loop condition. Likely inlined away in the port.
- `scan_argv_for_opt` (`0040287b`) / `find_opt_argv_index` (`0040294c`) —
  two ad-hoc linear scans of `argv` for `-<letter>` used *before* the real
  getopt loop runs (to find `-c`/`-q` presence and the `-e` index
  respectively), independent of `dsp_getopt`'s internal state.
- `open_error_file_opt` (`00402a24`) — parses `-ea`/`-ew` (append/write
  mode) plus the following filename argument, `fopen`s it, and repoints
  `Msg_fp` (`00457c08`); falls back to `stderr`-alike stream
  `&DAT_0045d670` on failure (see quirk below).
- `init_link_state_pass1`/`init_link_state_pass2` (`00402b44`/`00402cd2`) —
  reset the large block of per-run globals in §6, seed the default library
  search path (`"DEFAULT"`, via `thunk_FUN_0042c373`, symtab/util) and call
  `init_float_format_table`.
- `finish_link` (`00402e52`) — see §1 step 6.
- `lnk_signal_handler` (`0040303c`) — SIGINT: prints "Interrupted" (unless
  quiet) and exits with the error count (or -1 if none); SIGFPE: re-arms
  itself, then either `longjmp`s back into the expression evaluator
  (`In_eval_flag` set) reporting "Arithmetic exception" as a normal error,
  or reports it fatally; SIGSEGV: prints
  `"%s: Fatal segmentation or protection fault; contact your tools
  vendor\n"` and exits.
- `default_base_name` (`00403172`) — scans `argv` for the first `-l`; if
  found, strips its leading `-` (and the following char, i.e. the option
  letter) and any extension to get the base name; else calls the same
  extension-strip on `argv[0]`.
- `set_default_ext` (`004032e9`) — replace or append the extension of the
  global name buffer (`Namebuf`, `00461528`) with the given one, returning
  the new pointer only if it actually changed anything.
- `open_default_object_file` (`00403385`) — builds `<base>.<objext>`,
  opens it, records the owned copy in `Object_file_name`.
- `expand_dsplnkopt` (`0040343e`) — builds a singly-linked list of argument
  strings: first the program name, then (if `DSPLNKOPT` is set)
  `tokenize_env_options` on it, then either every real `argv[1..]` element
  (expanding any `-f` via `read_command_file`) or, in "no-argv" mode
  (`Cur_no_argv_mode`/`004611f4`), just the single buffered string; the
  final list is flattened into a fresh `argv`-style array (`malloc`'d) and
  returned as the new `argc`.
- `tokenize_env_options` (`004036b4`) — whitespace/control-char tokenizer
  for the `DSPLNKOPT` string; recognises `-f` inline and recurses into
  `read_command_file` for it, otherwise appends each token as a list node.
- `read_command_file` (`004039e5`) — opens a `-f` command file and tokenizes
  it: whitespace-separated tokens, `;` starts a line comment, nested `-f`
  is expanded recursively; every other token becomes a list node.
- `dsp_getopt` (`004040eb`) — a hand-written `getopt(3)`-alike: globals
  `Getopt_index`/`00461da8` (like `optind`), `Getopt_optarg`/`00461dac`
  (like `optarg`), `Getopt_optarg2`/`00461db0` (a *second* option argument
  for two-colon option letters), and `Cur_parse_ptr`-like internal
  "rest of a bundled `-xyz`" pointer at `00461130` (not separately named —
  it is local getopt state, not a cross-module value). `optstring`
  characters may be followed by zero, one, or two `:`; `?` marks an
  option whose argument is itself optional-and-not-starting-with-`-`.
  On an unknown option letter, prints `sprintf("-%c",c)` and fatals.
- `add_library_path` (`004044bd`) — appends a `-p<lpath>` argument (after
  `ensure_trailing_backslash`) to the library search path list
  (`Lib_path_head`/`Lib_path_tail`).
- `ensure_trailing_backslash` (`0040456e`) — appends `\` to `Namebuf` in
  place unless it already ends in `\` or `:`.
- `set_target_cpu` (`004045d0`) — looks up the object file's target-name
  string in `target_cpu_table` (§3), aborting fatally
  ("Invalid object file for target processor") if not found; copies all
  the per-target address-width/mask constants (word size, P/X/Y address
  masks, min/max immediate ranges, hex-format strings) into the `Target_*`
  globals (§6); also back-patches the memory-control-file space records
  already parsed (`thunk_FUN_0042e743`/memctl output list) with the
  correct address mask for `L`-space vs. other spaces. Sets
  `Target_is_56600` when the target is entry 5 (`DSP56600`? — see open
  question in §7, index/name mapping not 100% certain for two entries).
- `init_float_format_table` (`00404859`) — registers eight symbolic
  floating-point display strings ("+Infinity"/"-Infinity", "+Huge"/
  "-Huge", "+Tiny"/"-Tiny", and two unlabeled ones) with a util.c table
  builder (`thunk_FUN_0042c6c1`) used later when printing out-of-range
  floating literals in error messages/maps.
- `get_date_time_strings` (`00404bba`) — `time()`/`localtime()` →
  `"MM-DD-YY"` and `"HH:MM:SS"` strings (used for the map file header, see
  Y2K note below), then frees/consumes the `tm*` via a util.c helper.

## 3. lnkglb — data-only global tables

This "module" (per the RCS `$Id` votes) does not contain its own functions;
it is the constant-data region `~0x457b48`–`~0x458fb0` referenced by many
modules. Tables identified so far (dumped live from `re/bin/DSPLNK.EXE`
with `scratch_l1_main/dd.py`):

- **`target_cpu_table`** (`00457c18`, 8 entries × 0x4c=76 bytes, used by
  `set_target_cpu`): each entry is `{const char *name; unsigned long magic;
  unsigned long word_size; ...more mask/format fields...}`. Confirmed
  entries (name → COFF optional-header "magic"):
  `DSP56000`→0x2c5, `DSP96000`→0x2c6, `DSP56100`→0x2c7, `DSP56300`→0x2c8,
  `DSP56800`→0x2c9, `DSP56600`→0x2ca, *(unnamed, magic 0x2cb — the name
  pointer for this entry decodes to the unrelated string `"100"`, which is
  almost certainly an artifact of the table being only partially
  initialized/laid out differently for this row; treat the 0x2cb name as
  unresolved)*, `DSP56700`→0x2cc. Each row also carries per-target hex
  print-format strings (`"%08lX"`, `"%06lX"`, `"%04lX"`, seen adjacent in
  memory) — these are the `Target_*` format-string globals copied out by
  `set_target_cpu` (`00461fb4`/`b8`/`bc` etc. in the names file).
- **Memory-control-file directive keywords** (`00458788`–`004588e8` area,
  single-letter/word tokens `L`, `H`, `alignsym`, `balign`, `base`, `endr`,
  `ident`, `include`, `map`, `memory`, `region`, `reserve`, `sbalign`,
  `secsize`, `section`, `set`, `sizsym`, `start`, `symbol` — the `-r`
  memory-control-file directive vocabulary). Owned/consumed by memctl.c
  (other group); listed here for completeness since it is a `lnkglb` table.
- **`-x` linker-option keyword table** (`00458970`–`004589e8`,
  densely-packed NUL-terminated strings, *not* an array of pointers —
  looked up by linear `strcmp` and index, presumably in
  `thunk_FUN_00425cf1`/util.c, not this group's code): `globmap`,
  `nobuffer`, `noconst`, `noglobsym`, `nolocal`, `nooverlay`, `nosecaddr`,
  `nosecname`, `nosymname`, `nosymval`, `nounused`, `symlen`. These are the
  `<opt>` values documented in the usage text as "linker option argument"
  for `-x<opt>[,<opt>...]`; exact semantics not traced (belongs to the
  util/memctl group's `thunk_FUN_00425cf1`), but names strongly suggest:
  include globals in map / suppress buffer stats / suppress constant
  folding / suppress global-symbol map / suppress local-symbol map /
  disable overlay checks / suppress section-address, -name, symbol-name,
  symbol-value columns in the map / suppress "unused" warnings / set
  max symbol-name length printed.
- **Another short-mnemonic table** (`004589f0`–`458b00`-ish: `abc`, `aec`,
  `asc`, `csl`, `eso`, `ff`, `isw`, `mcm`, `noabc`, `noaec`, ..., `ovlp`,
  `ro`, `rsc`, `sbm`, `sdi`, `svo`, `wdg`, `wex`, `wvr`, `aenc`, `byt`,
  `ceil2`, `enc`, `fb2`, `fbf`, `hb`, `imax`, `imin`, `lb`, `lrf`, `sdi2`,
  `szck`) — these mnemonics match the ASM56000 assembler's `OPT`
  pseudo-op keyword set (auto-branch-conversion, address-extension check,
  etc.) almost one-for-one; most likely this is the same `opt`-bitfield
  keyword table shared with the assembler and used here only to decode the
  `OPT` bits stored by ASM56000 in the object file's optional header for
  producing compatibility warnings. Cross-check with ASM56000 group's
  `func`/`eval` notes once available.
- **No central "error message table" was found.** Every `lnk_error*`/
  `lnk_warning*`/`lnk_fatal*` call in the whole binary passes a *literal*
  format string from its own call site (confirmed for all of error.c's
  callers via `strings.txt`); there is no error-code → message indirection
  table for DSPLNK, unlike what the brief's wording might suggest. Worth
  double-checking against the map.c/memctl.c/object.c call sites (other
  groups) before assuming this holds project-wide.
- `$Id: map.c,v 1.33 1998/12/15 19:29:00 russo Exp $` was found spliced
  into this same data region right after the `OPT` mnemonic table
  (`00458e38`) — confirms Ghidra's module-boundary voting put at least one
  `map.c`-owned string inside what is nominally the `lnkglb`/`util` range;
  the `util` owner for the big 3096-byte block (`00458358`) is therefore a
  vote-based approximation, not a hard boundary (matches the brief's
  warning about `util`'s big run possibly containing other modules).

## 4. error.c — error reporting

Purpose: the seven `lnk_*` message primitives shared by (almost) every
other module, plus three small standalone value-conversion helpers Ghidra
grouped into this address range that likely are *not* logically part of
error reporting.

### Message primitives

All seven follow the same shape and were reconstructed from
`re/out/DSPLNK/mod/error.c` (Ghidra dropped their varargs, but the
format-string call site always shows exactly one or two extra `%s`
arguments, confirmed against `re/out/DSPLNK/strings.txt`):

- `lnk_fatal1(fmt, ...)` (`004098b0`) — 1 string arg. Prints
  `"\n***** FATAL: <fmt>\n"` to `Err_fp` (`00461f34`), with a location
  header first if `Cur_section_rec` (`00461ddc`) is non-NULL: `"    File
  <name>  Module <name>\n"`, then either `"    Line <n>\n"`
  (`Cur_line_mode`≠0, i.e. reporting a source line in a listing context) or
  `"    Section <n-or-name>  Symbol <n>\n"` plus an optional
  `"    Source line <n>\n"`. Removes the partial object file if any, then
  `exit(-1)`. **Never suppressible** (ignores `Suppress_errors`).
- `lnk_error1`/`lnk_error2` (`00409a25`/`00409bfd`) — same header format,
  banner `"\n***** ERROR: <fmt>\n"`/two-arg variant, `Error_count++`
  *unless* `Suppress_errors` (`004611f0`) is set, in which case
  `Suppressed_error_count++` instead and nothing is printed. `lnk_error1`
  additionally appends `" (%s)"` with `Err_context_suffix` (`00461b40`)
  to both the opening and closing banner lines when that buffer is
  non-empty (`lnk_error2` and the fatal functions do not).
- `lnk_warning1`/`lnk_warning2` (`00409d88`/`00409f4d`) — same shape,
  banner `WARNING`, always increments `Warning_count`; `lnk_warning1` has
  the same `Err_context_suffix` behaviour as `lnk_error1`, `lnk_warning2`
  does not touch it and is never suppressed by `Suppress_errors` (no
  guard at all — check this against the real binary if it looks like a
  bug during porting; it may simply mean the "N" two-arg warnings are
  used only outside speculative/suppressed contexts).
- `lnk_cmdline_fatal1`/`lnk_cmdline_fatal2` (`0040a0ca`/`0040a0f6`) — used
  *before* the diagnostic stream is set up (during argument/library-path
  parsing); print `"%s: <fmt>\n"`/`"%s: <fmt> %s\n"`-shaped text directly
  to the CRT's stream at fixed address `&DAT_0045d650` (see quirk below),
  then `exit(-1)`.
- `lnk_cmdline_warn1` (`0040a126`) — same target stream, same
  `"%s: <fmt>\n"` shape, but does **not** exit (non-fatal command-line
  warning, e.g. "Duplicate object file specified - ignored").

### Value-conversion helpers (address range 00408b90–00408bba)

Ghidra's module-vote put these in error.c's address range, but their
callers (`00406edd`, `00416622`, `00417a64`, `00429870`) are arithmetic/
symbol-value-formatting code, not error reporting — treat the "error"
ownership as an address-range artifact, not a semantic one, when
translating.

- `identity_long` (`00408b90`) — `return v;`. Used as a
  calling-convention-compatible pass-through in two call sites.
- `dwords_to_double` (`00408ba1`) — combines two 32-bit halves into a
  double via `(double)CONCAT44(hi,lo)`; used once by `add_reloc_symbol`
  (`00416622`, input.c) to reinterpret a relocation's raw 8-byte payload as
  a double for out-of-range/overlay float diagnostics.
- `swap_dword_pair` (`00408bba`) — `*out1=b; *out2=a;` (exchanges the two
  halves into new locations, not in place). Used in `func`/`amode`-side
  arithmetic and by `symtab`'s FUN_00429870 to swap a value pair — plain
  utility, not endian byte-swapping (compare with util.c's real byte-swap
  helper `thunk_FUN_004307d5` used by input.c, §5).

## 5. lib.c — reading DSPLIB libraries

Purpose: scan a `.LIB`/archive-format library file for members whose
`GLOBAL` symbol table entries satisfy currently-undefined references, and
feed matching members through the normal object-module pipeline
(`process_module`, input.c). Structurally this is the classic iterative
"keep rescanning until nothing new is pulled" archive-search algorithm.

### Library member header format (confirmed against `-l` test libraries
built in `scratch_l1_main/t.clb`/`out.cld` and the `check_library_magic`
code)

`check_library_magic` (`0041c5ec`) reads and compares the first
`Lib_magic_len` (`00457fa0`, =7) bytes against `Lib_magic`
(`00457f98`) which is the literal string `"!<arch>\n"` truncated to 7
bytes (`"!<arch>"` — confirms the brief's `!<H>` shorthand: the archive
uses the classic Unix-ar-style `"!<arch>\n"` magic at the start of the
file), then seeks back to offset 0. Then `scan_library_members`
(`0041c7d9`) loops reading one member header line at a time with
`read_library_header_line` (`0041d288`, reads up to CR/LF/EOF, and if the
line is the archive end-marker, or does not match the member-header prefix
comparison against `Lib_magic`, treats it as invalid): each header line is
parsed with `sscanf(line, "%s %s %ld", name_buf, &member_size)` — i.e. a
whitespace-separated `<member-name> <?> <size>` triple (matches the
brief's `"!<H> name size time\r\n"` sketch: name, then further
whitespace-separated fields including a decimal size and presumably a
timestamp, though only name+size are actually consumed by this code —
Ghidra's `sscanf` recovery may have dropped a middle `%s`/date field;
worth re-checking with `x86dis.py` around `0041c7f8` if exact field count
matters for byte-identical member-header generation, which belongs to a
different group's `object.c`/library-writer code, not this reading path).
After the header, a 0x1c(28)-byte COFF file header is read
(`thunk_FUN_0043062d`, util.c) directly from the member position; if the
target hasn't been identified yet, `set_target_cpu` runs off this member's
target-name field. If the member's target matches, and the module hasn't
already been scanned once (bit `0x1`(`local_44`) clear), the member's
optional header is read (0x28 bytes = "no version" case, else real sizes),
and if the member has a non-zero symbol-table offset
(`local_4c`/COFF `f_symptr`), the member is a candidate: `process_library_
member` (`0041ca95`) is called with the member's name/size/offset.

### Symbol search algorithm

`process_library_member` (`0041ca95`) does **two passes over the member's
own symbol table** using `next_pullable_symbol` (`0041ce63`, iterates
32-byte COFF symbol-table slots, skipping the aux-entry count each time,
byte-swapping each slot with `thunk_FUN_004307d5`, util.c, unless already
swapped this run):

1. First pass (`DAT_00461148`=0/"collecting"): for every top-level
   (non-section, class `0x40` bit set) symbol whose linker already knows
   about ("`Lib_pull_mode`==1" — condition not fully traced, see open
   questions), records its name via `add_dup_global_name`
   (`0041cd73`) unless `dup_global_seen` (`0041ce1b`) says it's already
   recorded (linked list `Dup_globals_head`/`Dup_globals_tail`,
   `004611bc`/`004611b8`). This builds the running "which GLOBAL names has
   this whole link already pulled" duplicate-detector list, and fatals
   with "Found duplicate global symbol: %s in %s" if a name recurs.
2. Second pass (`DAT_00461148`=1/"matching"): for every symbol, calls a
   symtab.c hash-table lookup (`thunk_FUN_0042cd0d`) by name; if found and
   *not* already defined (`bit 0x100` clear) and it is a `GLOBAL`-class
   or matching-class symbol, that's a hit — stop scanning
   (`local_c` non-NULL breaks the loop).
   If a hit was found, `thunk_FUN_004145bb` (input.c, `new_module`) is
   called to allocate a MODULE record for the member (name/size/offset),
   linked onto the tail of the module chain rooted at
   `Cur_input_file[8]`/`[0xc]` (offset `+0x20`/`+0x30` field pair — this
   is the *library's own* input-file node, distinct from the top-level
   `Input_list_head` chain), and `process_module` runs it immediately.
   If no hit, the file position is simply restored to the next member.
   Either way the per-member symbol buffer (`Lib_member_symtab`/
   `Lib_member_strtab`, `00461e6c`/`00461e78`) is freed.

Back in `scan_library` (`0041c6d7`), pass 1 repeats
`scan_library_members` from the start of the file for as long as the
previous full scan pulled in at least one new member
(`Lib_rescan_needed`, `004611fc`) — the classic fixed-point archive scan.
In pass 2, `scan_library` instead simply re-walks the already-decided
module chain built in pass 1 (`Cur_input_file[0xc]` linked list, field
`+0x94`=next) and re-runs `process_module` on each pulled member without
rescanning candidates again.

## 6. input.c — reading COFF object files

Purpose: open object/library-member files, read and decode the COFF
module header/optional header/section table/symbol table/string
table/raw data/relocation/line-number tables, and (pass 1) build the
in-memory section map + counters, or (pass 2) apply relocations and hand
off records for output.

### Byte-order handling

**Confirmed cross-module fact, not implemented in this group's code**:
all fixed-size COFF structures (module file header, optional header,
section headers `read_section_headers`/`0041a8ef`, symbol entries
`read_symbol_entries`/`0041a937`) are loaded with a plain
`fread`-equivalent (`thunk_FUN_0043062d`(ptr,size,count,stream), util.c —
calls CRT `fread` then conditionally `thunk_FUN_004307d5`, also util.c,
which is the actual big-endian→host byte-swap routine, called
per-field/per-slot e.g. `thunk_FUN_004307d5((undefined1*)slot,4,2)` to
swap two 4-byte fields of one symbol-table slot). **None of that swap
logic lives in input.c** — input.c only calls the util.c wrappers; the
byte order handling itself must be reverse-engineered from util.c
(`0043062d`/`00430667`/`004307d5`) by whichever group owns it. This is
important for the port: `read_module_header`, `read_section_headers`,
`read_symbol_entries` etc. must NOT do a raw `fread` into a C struct on a
little-endian host — they need the same helpers.

### Structures identified

**`INFILE` — input-file list node, 0x14 (20) bytes** (built by
`open_next_input_file`/`004143b4`, iterated by `process_input_files`/
`00414110`, list head `Input_list_head`/`00461db8`, "current" pointer
`Cur_input_file`/`00461dbc` doubling as error.c's "current file/module"
context):
```
+0x00 char  *name        file name (owned copy)
+0x04 ulong  flags        bit 0x2 = is a library (else plain object file)
+0x08 void  *module       MODULE* for a plain object file (NULL for a
                           library — its members get their own MODULE
                           records discovered lazily by lib.c)
+0x0c ulong  (reserved)    always 0 at construction; not seen written later
+0x10 void  *next          singly linked, next INFILE
```

**`MODULE` — one COFF object module, 0x98 (152) bytes**
(`new_module`/`004145bb`; filled in by `read_module_header`/`00414d76`,
`read_module_raw_reloc_lines`/`0041516a`, `alloc_module_tables`/
`0041a5e0`):
```
+0x00 char  *name         module/member name (may be NULL)
+0x04 ulong  (unused)      always 0
+0x08 long   size          byte size of the module image
+0x0c long   offset        byte offset of the module's COFF header within
                            the file (0 for a plain object file, non-zero
                            inside a library)
+0x10 void **section_map   per-file-section-index → map-entry array,
                            count = optional-header field at +0x48
                            (alloc_module_tables)
+0x14 ulong *counter_tbl   pairs (8 bytes each), count = field at +0x4c
+0x18 ulong *alloc_tbl     pairs (8 bytes each), count = field at
                            +0x58, plus one extra terminator pair
+0x1c ulong *buffer_tbl    9-dword (0x24-byte) records, count = field at
                            +0x5c, plus one extra terminator record
+0x20 ..+0x3b  COFF file header, 0x1c (28) bytes, raw big-endian-decoded
                            fields (magic/flags/nsections/symtab
                            offset+count/opt-header size, ...)
+0x24            (COFF f_symptr-equivalent? — number of aux/opt bytes,
                            used to size read_section_headers's malloc)
+0x30            file header "flags" field (bit 0x1 = no relocation
                            info present → fatal; bit 0x10000 = has
                            overlay info; bit 0x20000 = has SDI info)
+0x34            optional-header size (0x28 = "no version fields" magic
                            case)
+0x3c ..         optional header, raw decoded, size from +0x34; known
                            sub-fields: +0x60/+0x64/+0x68 = object file
                            version major/minor/patch (compared against
                            the linker's own 6.3.7, `check_module_version`)
+0x74 void  *opt_header_ptr  pointer to the (separately malloc'd) full
                            decoded optional header (read_section_headers
                            result; despite the name this actually holds
                            the *section header table*, see below — the
                            field name needs re-checking against
                            x86dis.py)
+0x78 void  *raw_data       raw section-data blob (all sections'
                            initialized bytes concatenated), size = field
                            at +0x40 << 2 longwords
+0x7c..+0x80     (0 at construction; written by alloc_module_tables-like
                            code elsewhere for `-g` line info — not
                            fully traced)
+0x84 void  *reloc_tbl       0xc(12)-byte relocation entries, count =
                            field at +0x50 (or +0x54 in the "-g" variant
                            read by read_module_relocations)
+0x88 void  *line_tbl        0xc(12)-byte line-number entries, count =
                            field at +0x54
+0x8c void  *section_hdrs    section header table, one 0x20(32)-byte
                            entry per section, count = field at +0x30
+0x90 char  *strtab           module string table (4-byte length prefix
                            + bytes, `read_string_table`/0041a97f)
+0x94 void  *next             MODULE chain link used by lib.c
                            (`Cur_input_file[0xc]`/pass-2 walk)
```
(Field-offset mapping above is reconstructed from `read_module_header`,
`alloc_module_tables`, `process_module` and library code together; a few
offsets in the 0x74–0x84 range are evidenced only indirectly and should
be re-checked with `x86dis.py` before being relied on for a byte-exact
port.)

**Section-table-entry / symbol-table-entry slot, 0x20 (32) bytes**
(`process_module`'s main loop: `slot = section_hdrs + i*0x20`, i stepping
by `slot[7]+1`, i.e. 1 + aux-entry count — classic COFF symbol-table aux
mechanics also used here for section table records):
```
+0x00 ulong zero_flag   0 = long name (name held in string table at
                        strtab+slot[1]); nonzero = short inline name
                        packed into this slot itself (byte-swapped
                        4 bytes at a time, then used as char*)
+0x04 ulong name_off    string-table offset, valid only if +0x00==0
+0x10 long  value        section/symbol value (address or, for absolute
                        symbols, the literal value)
+0x14 ulong flags2       used for x/y/l memory-space selection etc.
+0x18 ulong rec_type     record/section "type" code: observed values
                        include 2, 3 (memory-space/counter def, aux
                        count 0 = "set current section"), 6, 0x67='g',
                        0x6a, 0x80, 0x81 (SDI record), 0xc9, 0xd2, 0xd3,
                        0xd4 (external, no relocation applied), 0xd5,
                        100, 200 (stack-model records)
+0x1c ulong num_aux      number of auxiliary 32-byte slots following
```
(This is deliberately partial — `process_module`'s dispatch on `rec_type`
is the "big switch-shaped function" the brief allows summarising rather
than exhaustively decoding; the case values collected above are the ones
observed guarding a call into a named function.)

### Functions

- `process_input_files` (`00414110`) — pass 1: loop over the *current*
  command-line/library argument list (`Cur_argc`/`Cur_argv`, or, in
  no-argv mode, a single synthetic argument), calling
  `open_next_input_file` per entry and then `process_module` (plain
  object) or `scan_library` (library) on it, closing the file afterward.
  Pass 2: instead walks the already-built `Input_list_head` chain,
  re-opening (`open_input_stream`) each file by name and re-running
  `process_module`/`scan_library` on it.
- `open_next_input_file` (`004143b4`) — determines library-vs-object via
  `check_l_switch_arg` (lib.c), retries the open with the default object/
  library extension appended if the plain name doesn't open, builds and
  links a new `INFILE` node, and — for plain object files — eagerly
  allocates its `MODULE` via `new_module` sized from `file_size`
  (`0041a8c0`).
- `new_module` (`004145bb`) — allocates and zero-initializes a `MODULE`
  (name copied if non-NULL, size/offset stored, all pointer fields
  cleared).
- `process_module` (`004146c6`) — the pass-1/pass-2 per-module driver
  described in §1 and above; also carries the compatible-debug-format
  check ("Incompatible debug format") and the stack-memory-model
  consistency check ("Memory model mismatch...").
- `read_module_header` (`00414d76`) — seeks to the module, reads the file
  header, calls `set_target_cpu` on first use / on target mismatch,
  fatals on "no relocation info" and on target mismatch, records the
  overlay/SDI-present flags, sets `Target_word_size`-derived
  `00457b48`("word width class", 1/2/3) purely from the target magic,
  reads the optional header, reads the section-header table via
  `read_section_headers`, and — the first time any module sets the
  target — copies its symbol-table string field into `Target_name`.
- `check_module_version` (`0041507a`) — copies the optional header's
  version-number triple and, pass 1 only, warns if the object file was
  built with a newer linker than this one (major/minor comparison against
  the `Linker_major/minor/patch` parsed from the embedded `"6.3.7"`
  version string).
- `read_module_raw_reloc_lines` (`0041516a`) — reads the raw section-data
  blob, the relocation-entry table, and the line-number-entry table
  (each only if its count field is non-zero and not already read).
- `read_module_relocations` (`00415316`) — the `-g` debug-mode variant
  that (re)reads just the relocation-entry table from a different offset
  field (`+0x54` vs `+0x50`); called instead of/in addition to the above
  when line-number info implies a different physical layout (only
  invoked when `Module_has_overlay` is set — needs re-verification).
- `set_current_section` (`004153a6`) — the "record type 3, aux-count 0"
  handler: given a section-record's from/to memory-space and
  counter/mapping numbers, looks up (creating on miss via a
  symtab.c hash, `thunk_FUN_0042bc50`) the corresponding section-map
  entries for both the "current section" and "current relocation
  section", sets a large block of `Cur_*` globals (§ names file) used by
  every subsequent record in the module, and (pass 1) accumulates the
  section's byte counts into running totals. Handles the "load address
  != run address" (overlay-style) case via bit `0x20` of the packed
  flags word.
- `add_reloc_symbol` (`00416622`) — record type in {2,3,0x6a,6,0xd2,0xd3,
  0xd4,0xd5} with a non-zero relocation-entry count: builds a relocation
  descriptor on the stack (target section/word width/relocation kind
  derived from the record type; the value itself either the raw 8-byte
  payload or, for record type "0xd4"-like float encodings, reinterpreted
  via `dwords_to_double`) and hands it to a symtab.c consumer
  (`thunk_FUN_0042c6c1`). Skips entirely (returns 1 unconditionally as a
  no-op) when the record type is `0xd4`.
- `add_plain_symbol` (`00416bed`) — the simpler case (record's
  relocation-entry count is 0, or a stack-model class match): builds the
  symbol name (optionally case-normalised if `-n`, via
  `thunk_FUN_00430037`, util.c) and links it onto the current section's
  symbol chain.
- `apply_module_fixups` (`00416cf8`) — pass-2-only, called right after
  `set_current_section` succeeds for a type-3/aux-0 record: walks that
  section's symbol/relocation chain and, per entry, calls
  `update_address_extent` and `check_value_truncation`, then a further
  set of util.c helpers (`thunk_FUN_0040a571` — the same symtab lookup
  used by `parse_sdi_expression`, `thunk_FUN_0043a289`,
  `thunk_FUN_0042a767`, `thunk_FUN_00429716`) to compute and store the
  final relocated value; the largest and least fully traced function in
  this module (3436 bytes) — treat as "the pass-2 relocation-application
  engine" rather than fully decoded.
- `check_value_truncation` (`00417a64`) — given a double value, a target
  field "kind" and flags, checks it against the target's field-width
  range and reports one of the "EMI 8-bit"/"X or Y 16-bit"/"P 24-bit"/
  "EMI 12-bit"/"EMI 16-bit memory value truncated" warnings, then stores
  the (possibly truncated) value through the output pointer.
- `parse_sdi_expression` (`0041839c`) — parses one `@SDI(...)`/`@SDI2...`
  auxiliary-record string (from the module's string table) of the form
  `@SDI(<name>,<a>,<b>,<c>` (or the alternate `@SDI2` 1-char-longer
  prefix), validates every `,`/`)`, looks up the leading `<name>` (or
  `(<...>)`-parenthesised complex expression, split on `@`) via
  `thunk_FUN_0040a571` (symtab.c) and reads three more comma-separated
  numeric sub-fields the same way — used to resolve source-debug-info
  cross references. Fatals "Invalid @SDI expression" with fairly precise
  per-field diagnostics (6 distinct message addresses for 6 different
  parse failure points).
- `section_nest_track` (`0041874a`) — push/pop a small stack
  (`00461f00`) keyed by a per-record id field; pop when the record's id
  field is 0, else push; fatals "Section nesting error" on pop-when-empty.
  Handles record types `0xc9`/`0x80` in `process_module`'s pass-2 loop.
- `emit_pass2_record` (`0041882a`) — called for every section-table
  record in pass 2 unless `-z` strip is set; the second-largest function
  here (3906 bytes) and not fully decoded — references a
  `"%04X %04X %04X "` format string (three hex halfwords, space
  terminated) suggesting it is emitting either a listing/map line or
  (more likely, given it runs unconditionally per record and calls
  further map.c/object.c helpers) driving the actual per-record object
  output writer; needs follow-up by whoever owns `object.c`/`map.c`.
- `update_address_extent` (`0041976c`) — updates the running low/high
  address-used extents (`Low_p_addr`/`High_p_addr` for P-space,
  `Low_xy_addr`/`High_xy_addr` for X/Y-space) and the corresponding
  "record number where the extreme occurred" fields in the optional
  `P_map_extent` table (`00461f08`), used later for map-file summary
  lines.
- `select_counter_block` (`0041999e`) — routes a record's flags word to
  one of three counter/allocation sources: `find_section_record` (normal
  section), `get_alloc_record` (bit `0x4000` — "needs a fresh allocation
  record", e.g. uninitialized/BSS-like space) or `find_overlay_record`
  (bit `0x2000` — overlay), fataling "Invalid data block type" if none
  apply; also derives `Cur_mapping_*` pairs used by `set_current_section`
  and `next` symbol-table walks.
- `find_section_record` (`00419ece`) / `find_overlay_record`
  (`00419ff9`) — section-map lookups by (flags, address); both can fatal
  "Cannot find section record". `find_overlay_record` additionally
  creates a new overlay record on a miss (larger function, 1068 vs.
  299 bytes) rather than only searching.
- `get_alloc_record` (`0041a425`) — obtains (creating via a symtab.c
  hash-table call, `thunk_FUN_0042bc50`/`thunk_FUN_0042be92`, if needed)
  the "allocation" record for the current buffer, tracking whether the
  buffer changed load-vs-run address (bit `0x10000` set on mismatch).
- `alloc_module_tables` (`0041a5e0`) — allocates and zero-fills the four
  per-module lookup arrays described in the `MODULE` struct above
  (`section_map`, `counter_tbl`, `alloc_tbl`, `buffer_tbl`), sized from
  optional-header count fields.
- `open_input_stream` (`0041a815`) — thin `fopen(name,"rb")`-equivalent
  wrapper (name inferred from call sites; body not shown in the excerpt
  read, but every caller passes a filename buffer and expects a `FILE*`
  or NULL).
- `file_size` (`0041a8c0`) — `fseek`/`ftell`-based file size (returns
  negative on failure, checked by callers as "cannot determine file
  size").
- `read_section_headers` (`0041a8ef`) — allocates and reads `count`
  section-header entries (fatals "Cannot read object module section
  headers").
- `read_symbol_entries` (`0041a937`) — allocates and reads `count`
  32-byte symbol/section-record slots (fatals "Cannot read object module
  symbol entries"); also (re)used in lib.c purely as a sizing/allocation
  call after the file position has already been set up by
  `process_library_member`.
- `read_string_table` (`0041a97f`) — reads the 4-byte string-table
  length prefix, then that many bytes into a fresh buffer (fatals
  "Cannot read module string table size" / "...string table").

## 7. Cross-module interfaces (functions of other modules relied on)

- **util.c**: `thunk_FUN_0042e170`/`thunk_FUN_0042e1ce` (malloc/free
  wrappers, used everywhere in this group), `thunk_FUN_0043062d`/
  `thunk_FUN_00430667` (fread + byte-swap), `thunk_FUN_004307d5` (raw
  N-byte-field byte swap — **the actual big-endian decode primitive**),
  `thunk_FUN_00430037` (uppercase-in-place, used for `-n`/`-t`),
  `thunk_FUN_0042c373`/`thunk_FUN_0042c4e2`/`thunk_FUN_0042e743`
  (library-path-list / memory-control-record helpers), `thunk_FUN_0042c6c1`
  (generic named-value table inserter, used both for the float-format
  table and for relocation records), `thunk_FUN_00425cf1` (the `-x`
  option-string parser).
- **symtab.c**: `thunk_FUN_0042bc50`/`thunk_FUN_0042be92` (section/symbol
  hash-table get-or-create), `thunk_FUN_0042cd0d` (symbol lookup by
  name, used by lib.c's second pass), `thunk_FUN_0042cae9` (symbol-name
  registration, used by `add_plain_symbol` and the `-u` option),
  `thunk_FUN_0040a571` (name→symbol-record resolver, used by both
  `parse_sdi_expression` and `apply_module_fixups`).
- **memctl.c**: `thunk_FUN_0042e743` (parses `-o`'s
  `<mem>[<ctr>][<map>]` prefix), `thunk_FUN_0042c4e2` (origin-record
  lookup/creation for `-o`), object of the `-r` memory-control-file
  keyword table (§3).
- **map.c/object.c**: everything called from `finish_link`
  (`thunk_FUN_0042d519`, `thunk_FUN_0042d5a4`, `thunk_FUN_0041df05`,
  `thunk_FUN_0041d7d0`, `thunk_FUN_0042d10b/175/229/3ef/484/73f`) and
  from `main`'s post-link ELF step (`thunk_FUN_00432799`); this group
  did not investigate their internals.

## 8. Quirks / things worth reproducing exactly

- **Undocumented `-c`, `-s`, `-t` options.** The usage text
  (`lnk_usage`) never mentions them, but `parse_cmdline_options`
  recognises all three: `-c` behaves like a second `-q` (also suppresses
  the startup banner and the SIGINT "Interrupted" message);
  `-s` enables the final `"errors: %d warnings: %d"` summary line;
  `-t` triggers uppercasing of the object/map file name buffer
  (`thunk_FUN_00430037`) right after it is built — plausibly a
  legacy "target an 8.3 DOS filesystem" behaviour. All three must be
  kept working identically (including remaining undocumented) for
  output/exit-code compatibility.
- **Command-line vs. `Msg_fp`/`&DAT_0045d650` split.** Command-line
  parsing errors (`lnk_cmdline_fatal1/2`, `lnk_cmdline_warn1`) always go
  to a *fixed* CRT stream at `&DAT_0045d650`, independent of `-e`
  (`Msg_fp`), because they can occur before `-e` has been parsed, or
  even during `-e`'s own parsing. Byte offset arithmetic on this and
  `&DAT_0045d670` (used as the fallback `Msg_fp` if `-e`'s `fopen`
  fails) is consistent with MSVC's static `_iob[]` array (each `FILE`
  is `0x20` bytes; `0x0045d650`/`0x0045d670` are 0x20 apart) — i.e.
  these are almost certainly `stdout`/`stderr` (`_iob[1]`/`_iob[2]`)
  referenced by fixed address rather than by name, matching the "static
  CRT, no symbols" build note in the brief. **Do not assume `stderr` is
  always used** — verify which of the two is which stream with a live
  test (`re/bin/DSPLNK.EXE` with `2>nul`/`1>nul` redirection) before
  porting, since getting this backwards would silently change which
  stream users see command-line errors on.
- **`get_date_time_strings`** stores a plain two-digit year
  (`"%02d-%02d-%02d"` from `tm_year%100`-style fields) — likely a Y2K
  display bug in the map file header inherited from the original 1990s
  source; reproduce exactly (do not "fix" to 4-digit years) since output
  must match byte for byte.
- **`lnk_warning2`** (two-`%s` warning) has no `Suppress_errors` guard
  in the decompiled code, unlike every sibling error/warning function —
  confirm this isn't a Ghidra artifact before relying on it; if real,
  callers evidently never invoke it from a suppressible (speculative
  evaluation) context.
- **Object file target-table row for magic 0x2cb** has a garbled/
  unconfirmed name in the live binary dump (decodes to `"100"`); the
  `main()` special-case `Cpu_magic==0x2cb` (controls automatic ELF debug
  file generation) still needs the *numeric* magic, not the name, so
  this is cosmetic for functionality but the name itself should be
  pinned down (likely from Motorola docs / the ASM56000 group's
  target-table notes) before writing user-facing text that names the
  chip.
- Library member header parsing (`read_library_header_line`) currently
  only extracts `name` and `size` via `sscanf("%s %s %ld", ...)`
  swallowing one field in between — cross-check against
  `re/notes/DSPLNK/scratch_l1_main/t.clb`'s actual header line bytes
  (a small hand-built test library from the earlier run of this task)
  and `x86dis.py` before assuming the discarded field is unused; the
  brief's `"!<H> name size time\r\n"` sketch implies at least one more
  field (a timestamp) actually exists on disk.

## 9. Open questions / follow-ups

1. Several `input.c` `MODULE` struct offsets in the `0x74`–`0x84` range
   (raw-data pointer vs. section-header-table pointer vs. line-info
   pointers) are inferred from usage patterns across three functions and
   should be re-verified with `x86dis.py` against `re/bin/DSPLNK.EXE`
   before being relied on for exact struct layout in the port.
2. `apply_module_fixups` (`00416cf8`, 3436 bytes) and `emit_pass2_record`
   (`0041882a`, 3906 bytes) are the two largest, least-decoded functions
   in this group's scope — they are almost certainly the real "apply
   relocations and write the object/map/S-record-ish output" engine.
   Whoever implements `input.c`/`object.c` in C should budget real time
   for a full disassembly-level pass over these two.
3. `Lib_pull_mode` (`004611e8`) — its exact meaning (something to do
   with `-u` forced symbols vs. ordinary undefined-reference pulls) is
   guessed from a single `==1` comparison in `process_library_member`;
   needs a live test (`-u<symbol>` against a multi-member library) to
   pin down.
4. The `lnkglb` `-x` option table and the `OPT`-mnemonic table (§3) were
   read as raw strings only; their *bit assignments* (which bit of which
   flags word each keyword sets) live in util.c's `thunk_FUN_00425cf1`
   and were not traced by this group.
5. `set_target_cpu`'s special case `Target_index==5` (sets
   `Target_is_56600`) doesn't line up cleanly with the table dump above
   (index 5 = `DSP56600`, magic `0x2ca` — plausible, but the corresponding
   `main()` check tests `Cpu_magic==0x2cb`, i.e. a *different* table row,
   for the ELF-debug-file condition); both should be reconciled with a
   live `-b` test against a `DSP56600`-target object file before the
   name/condition pairing is trusted.

## 10. Reused scratch material

`re/notes/DSPLNK/scratch_l1_main/dd.py` (a small PE-section-aware dword/
string dumper against the live `re/bin/DSPLNK.EXE`) from the earlier
interrupted run was reused as-is to resolve the `lnkglb` tables in §3
and the `MODULE`/section-record field values throughout §6; it remains in
the scratch directory for future groups. The `a.asm`/`b.asm`/`c.asm` /
`.cln`/`.map`/`t.clb`/`out.cld` files there are small hand-assembled test
inputs (a main module referencing an external `foo`, satisfied by a
one-line library) — useful for anyone validating the library-scan
algorithm in §5 or the COFF section/relocation format in §6 against a
live `re/bin_ft/DSPLNK.EXE` run.
