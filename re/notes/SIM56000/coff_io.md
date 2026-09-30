# SIM56000 group coff_io: coffrd, cofload, symdisp, iohist, help, run

Names: re/names/SIM56000/coff_io.names.txt (130 functions = every function of the six mod/*.c files, 56 globals).
Confidence per line in the names file. Ghidra `local_NN` are offset by 4; `DAT_0050578c`.. are the four
"current" pointers that nearly all simulator code uses (see Globals).

IMPORTANT module-boundary findings (filemap.txt is string-cluster based):
* "coffrd" (0x440030-0x445f10) is NOT a plain COFF reader. It is the **debug-information database + the
  source/disassembly window + step logic**: reads a .cld (COFF) file into the per-device session (`g_sim`) and answers
  address<->symbol/line queries, formats "addr -> label+off", fills the two-mode code window (assembly / source),
  and holds the step/next/until helpers. Its last function 0x445f10 is a `step` command variant (belongs to the command
  handlers, 0x445030..0x446910 = cmd handlers list/next/until/view/unlock/up/type/step/trace...).
* "symdisp" (0x4466d0-0x4475b0) is three command-handler fragments: a step/trace variant handler (0x4466d0), the
  syntax matcher of `save` (0x447170) and the `redirect` status line (0x4475b0). Nothing symbol related.
* "cofload" (0x47d160-0x47ed70) = **subroutine profiler reports (0x47d160-0x47dc80) + a second, independent COFF reader
  used by the profiler / coverage code** (0x47dc80-0x47ed70; string "Failed to handle COFF file", .bm/.em/.bs/.es scanning,
  source line lookup with ";##" nested markers). The reports belong to profile/profrep (`__MOTHER__` root, "Subroutine Call
  Graph report").
* "iohist" (0x448740-0x44c890) = the INPUT/OUTPUT command back-end: I/O channel list objects, value parsers (dec/hex/bin/
  float literal parsers used by other modules too: 0x44af70..0x44b380), per-cycle input polling and output logging, and the
  `input` command's channel creation (0x44c340). "history" as such is not here (`history` handler is 0x44d140, right before help).
* "help" (0x44d160-0x44d3xx) = help command: list of all commands + topic lookup; tables described below.
* "run" (0x4523c0-0x452f20) = the `change` syntax matcher (0x4523c0), breakpoint list free, the post-cycle "check stop
  conditions / break hit" engine used by go/step/trace, and the "Break #%d" report. Not the run loop itself.

## Common conventions discovered

Command table (used by help, cmdloop, the `*_parse` matchers)
* `g_cmd_tab` (0x4a8dbc) holds a pointer to an array of `g_ncmd` (0x4a8db8 = 39) pointers to command descriptors
  (array at 0x4a8c90). Descriptor (24 bytes, in .data):
  `+0 char *name` ("assemble"... first one here is "asm"), `+4 char *abbrev` ("a"), `+8 char *fullname` (compared by
  `help <cmd>`), `+0xc char **usage_lines` (NULL terminated array of help text lines, `{A}SM [...]` format; braces mark
  the highlighted/mandatory part), `+0x10 char **help_lines` (NULL terminated, `{----- ASM: Single Line Assembler ---}` +
  examples), `+0x14 syntax matcher`: `void *(*)(void)` returning a pointer to a variant entry
  `{ handler fn, int flag }` (8 bytes) of that command's variant table, or NULL for a syntax error
  (e.g. `cmd_change_parse` returns &0x4cfec0[k*2]; `cmd_save_parse` returns &0x4c9538[k*2]). The matchers read the
  tokenised command line: `g_tok_start[]`/`g_cmdline`/`g_tok_type[]`/`g_tok_val` (0x4a9468/0x4a92e8/0x4a93e8/0x4a9670,
  token record 0x28 bytes, token type chars: 'p' line/pc number, 'S' source line, 'i' integer, '#' count, 'r'
  radix, 's' symbol, 'u', 'j' ...) via helpers 0x4682ea/0x468587/0x469720/0x4699be etc. (other groups).
  Table of the 39 commands with descriptor and matcher addresses: asm 4d18a0/454590, break 4d0708/453b30, change
  4cfed8/4523c0, copy 4cfb28/451120, device 4cf668/450f00, disassemble 4cf1f8/450ac0, display 4ce7e0/4506c0, down
  4ce550/44fe50, evaluate 4cdea8/44fc60, finish 4c70c8/4457f0, frame 4cdc90/44f120, go 4cd718/44eee0, help 4cc8e8/44ec10,
  history 4cc4f8/44d140, input 4cbf20/44cc80, list 4c7078/445500, load 4cba78/44abf0, log 4cb4c8/44a560, more 4cb2d8/449e40,
  next 4c6ec0/444900, output 4caaa0/449bb0, path 4ca720/447eb0, quit 4ca4f8/447b30, radix 4ca118/447980, redirect
  4c9b80/447630, reset 4c9898/447270, save 4c9548/447170, step 4c90b0/446910, streams 4c8d58/446600, system
  4c89d8/446510, trace 4c83d8/446080, type 4c8138/445dd0, until 4c6f50/444f00, unlock 4c7fc8/445970, up 4c7e70/445930,
  view 4c6fc0/445030, wait 4c6b28/43fdb0, watch 4c6660/43fa30, where 4c6408/43e8b0 (descriptor / matcher).
* Extra per-core help table: `*(g_core+0x14)` -> `{int count; entry *e}`, entry 0x14 bytes:
  `+0 name, +4 char **lines, +8 char *description, +0xc char **(*lines_fn)(void) (dynamic, may be NULL),
  +0x10 void (*post)(char **lines)`. The same struct is reachable per peripheral
  (`*(*(g_core+8)+i*4)+0x14`, i < `*(g_devtype+0x14)`), used for `help <register/peripheral>`.
* Topic table `g_help_topic_tab` (0x4cc810): entries of 5 dwords `{name, lines, 0,0,0}` from 0x4cc810 up to 0x4cc863:
  "tio", "tio2", "comments", "macros" (loop in help_topic starts at &entry[0].lines = 0x4cc814 and steps 5 dwords).
  0x4cc750 is the NULL terminated list of "Other Help Topics" lines (`{;}comment string entry`, `{Macro filename}`,
  `{io}`, `{map}`, `{mem}` ...).

Session state (DAT_0050578c = `g_sim`, one instance per simulated DSP, allocated by devinit; other groups name the
rest). Fields seen in this group (offsets from g_sim):

| off | meaning / evidence |
|---|---|
| +0x04 | array of memory-space records, 300 (0x12c) bytes each (`+4+space*300`); +0x18 ring head, +0x1c count of
|      | last-accessed addresses (`+0x20+..*4` ring of 16 addresses; break types 2/0xb watch them), +0xa4/+0xa8 head/count of second ring (`+0xac`, `+0xec`) (run.c sim_check_stop) |
| +0x08 | array of 8-byte pin/peripheral records `{flags, ptr}` (`+4` = pointer to per-pin flag words; bit 0x10000/0x20000 = break-on-read/-write pending; 0xfffcffff clears) |
| +0x14 c | see run.c: cleared per-device counters at `+0x14/+0x1c` inside 0x12c-stride records? (run.c 0x452d..) |
| +0x18/+0x1c | "stop requested"/"refresh requested" flags cleared after each stop check |
| +0x1c (also) | set to 1 by io code on input EOF (0x44b550/0x44b9d0/0x44bd60) |
| +0x28 | repeat count (step/trace/go count); decremented per stop condition |
| +0x2c | break number to stop at (go #n) ; +0x34 step mode (0 run,1 step,2 trace cyc,3.. 4 next-...; 5-0x15 source-level next/until/finish machine, see below); +0x38 mode variant; +0x3c "stop on any break" flag |
| +0x40 | screen refresh flag; +0x44 next I/O channel serial number (`name+0x164`); +0x48 abort flag ("SIMULATION ABORTED") |
| +0x14c | list head: input channels ("i" list, event driven files/pins) |
| +0x150 | list head: timed input channels (`input ... T`, kind 'j' in cmd_input_open) |
| +0x154 | list head: output channels (values written as `#delta value` lines, `io_out_*` first list) |
| +0x158 | list head: output channels, cycle stamped (`%lu value`, second list; also "history") |
| +0x15c/+0x160/+0x164/+0x168 | counters incremented by break actions i1..i4 (`break_hit` case 1-4) |
| +0x17c/+0x180 | predicted next pc (branch/jump target) and its space for the step machine |
| +0x184 | "echo break messages" flag |
| +0x3e78 | head of breakpoint list (see struct below) |
| +0x3fc8 | pin/register descriptor array, 0x2c per element (used by io_out_insn_trace) |
| +0x3fd0 | number of section headers + 1 (COFF nscns+1) |
| +0x3fd4 | file offset of symbol table (f_symptr) |
| +0x3fd8 | number of symbol table records incl. aux (f_nsyms) |
| +0x3fdc | symbol table (32 byte records), host-swapped |
| +0x3fe0 | pristine copy of the symbol table |
| +0x3fe4 / +0x3fe8 | string table (starts with its 4 byte length, names are at strtab+offset) / its length |
| +0x3fec | number of line-number records |
| +0x3ff0 | line table, 12 byte records `{ addr, space, line }` (line 0 = function/file marker) |
| +0x3ff8 | current source file number (or -1); +0x3ffc current top line in source window; +0x4000 last line shown; +0x4004 line of pc |
| +0x4008/+0x400c/+0x4010 | assembly window: first address, space, last address shown |
| +0x4014 | section table, 0x20 byte records (see below), index 0 = template `g_null_section` |
| +0x4018 | copy of the loaded file name |
| +0x401c | number of distinct source files; +0x4044 same |
| +0x4020 | source file table, 12 bytes each: `{ nlines, long *line_offsets, char *path }` |
| +0x4024/+0x4028 | window address / address mask (from memory space table `*(g_devtype+0x20)+0x20+i*0x2c`) |
| +0x402c | index of symbols sorted by address: `int n; ...; per-space start indexes` |
| +0x4030 | index of symbols sorted by name: `{ int n; int idx[n] }` (1 based, binary searched) |
| +0x4048 | per-line-record map `{ int line_index; int fileno }[nlines]` |
| +0x408c | per stream (stdin/stdout/stderr) redirect flags; +0x40a4 + n*0x100 redirect file names |
| +0x4400 | code window mode: 0 off, 1 assembly window, 2 source window; +0x4404 "source window wanted" |

Other "current" globals: `g_devtype` (0x505790) = device-type descriptor: `+8` pin mask, `+0xc` mode word (optionally
`(*(+0x4e8))()` gives it), `+0x14` #peripherals, `+0x18` peripheral table (0x48 bytes/entry, `+0x2c` -> record with
`+4` read fn, `+0x28` #bits), `+0x1c` count, `+0x20` memory-space table (0x2c bytes/entry), `+0x28` memory access ops
`{ read, ?, ..., +0xc space_of(addr) , +0x14 multi read, +0x24 disassemble-block }`, `+0x3c` pin table (0x18 bytes/entry:
`+0xc` port index, `+0x10` bit mask, `+0x14` next-pin flag), `+0x44` pin group table (0x14 bytes). `g_core` (0x505794) =
CPU core ops: `+8` array of per-peripheral ops (`+8 set text fn, +0xc format fn, +0x10 apply fn`), `+0x10` disassembler
`int (*)(long *words, char *text, mode, mode2, void *info)`, `+0x14` command table (see above), `+0x1c` -> hook
list (first entry called after a load), `+0x20` -> branch ops `{ is_branch(pc,&len), is_return(pc,&info) }` (optional).
`g_dev` (0x505798) = device instance: `+0` device type index, `+4` device number, `+0x18` pin/port state array
(0x128 bytes per port record: `+0` value, `+4` drive mask, `+8`/`+0xc` in-flags, `+0x14 + bit*4` float value for analog pins,
`+0x94/+0x98/+0xa0` previous copies), `+0x1c` pc, `+0x20` cycle counter, `+0x40` -> status (`+0xc`), `+0x44` flags
(bit 2 = illegal opcode, bit 3 = ran-a-cycle, bit 0x20 = disabled device, low bits 0..1 = stop reason).

## symdisp.c (0x4466d0-0x4475b0, 3 functions; actually command fragments)

* 0x4466d0 `cmd_run_devices` (low): `g_sim->repeat = (tok[?]=='i') ? DAT_004a96c0 : 1; g_sim->+0x2c = 0`; calls
  0x439140(dev) (select device) + 0x46c4c0() for each enabled device (dev+0x44 & 0x20 == 0), reselects `g_cur_dev`,
  0x433e80(), sets refresh flag +0x40. It is the variant handler of `step` when a plain count is given.
* 0x447170 `cmd_save_parse` (med): syntax matcher of `save`. `save s ...` (token 2 == "s", string 0x4c7e04) -> variant 0
  (0x446b50, state save; requires tokens 3..) ; otherwise >= 2 address block tokens ending with a file name -> variant 1
  (0x446c50). Returns &0x4c9538[idx*2] or NULL. Uses matchers 0x469d42(tok,str) 0x468587(n) 0x4682ea(n) 0x4699be(n)
  0x468b59(n).
* 0x4475b0 `redirect_show(int which)`: prints `stdin|stdout|stderr` status: `"%s off"` (0x4ca06c) if
  `g_sim->+0x408c[which]==0` else `"%s %s %s"` (name, "from"/"to", file name at `g_sim+0x40a4+which*0x100`);
  output through 0x43d3a0(text, 1) (screen line writer). Names table `g_redir_names` 0x492018 ("stdin","stdout","stderr"),
  `g_redir_modes` 0x492028 ("from","to","to").

## help.c (3 functions)

* 0x44d160 `help_list_all` (high): `help` without argument. `g_sim->+0x4400 = 0; 0x43db40()` (begin paged output),
  prints banner `{     -------------- DSP SIMULATOR COMMANDS --------------}` (0x4cd26c), for every command descriptor
  every line of `usage_lines` (+0xc), then the `g_help_misc_topics` block (0x4cc750), then for the core command table
  (`*(g_core+0x14)`) one line `" {%s} : %s"` (name, description) per entry with name and description non NULL, then the
  same for every distinct per-peripheral table (dedup by pointer). Each line goes through 0x43d3a0(line,1); paging
  aborts through `help_page_check` (returns -1 once `g_page_abort == 1`, checked before each line); ends 0x43db50().
* 0x44d370 `help_page_check(state)`: `return g_page_abort==1 ? -1 : state`.
* 0x44d390 `help_topic(char *topic)` (high): `help <topic>`; case sensitive (ushort-wise strcmp) lookup order:
  1. command descriptors by `+8` fullname -> lines = `+0x10` help_lines;
  2. core command table entries (name `+0`): lines = `+0xc` fn() if non NULL else `+4`; remember `post = +0x10`;
  3. per-peripheral tables (same entry format);
  4. topic table 0x4cc810 (loop from 0x4cc814 by 5 dwords until 0x4cc863).
  Not found: prints `{Help topic not found}` (0x4cd2a8). Otherwise paged print of all lines, then `post(lines)` if any.
  Sets `g_sim->+0x4400 = 0` and `DAT_004aaab0 = 0` (help-mode flag) first.

## run.c (4 functions)

* 0x4523c0 `cmd_change_parse` (high): syntax matcher of `change`: `change` (token2 empty) -> variant 0; `change regs/addr`
  with 1 or 2 args -> variant 0/1 (variant table 0x4cfec0: {0x451160,1},{0x451900,1},{0x452030,0}); loops over token pairs
  (0x469720(i) && 0x468361(i+1)) for the general multi-pair variant (idx 2, returns pointer 0x4cfec0+16).
* 0x452470 `break_list_free`: frees breakpoint list `g_sim->+0x3e78` (next at +0x240); type 0xc (C expression break)
  also frees the parsed expression (`+0x244`, via 0x45f270).
* 0x4524d0 `sim_check_stop` (med) called by the run loop after every executed cycle (0x43a8b0/0x43d180 etc., also by
  cmdloop 0x439410?). Reads the stop-reason word `g_dev+0x44` (bits: 0..1 stop reason, 2 illegal op-code, 0x40 error text
  `DAT_004a8dd0`, 8 = cycle executed, 0x10 = break requested) and `g_dev+0x48` abort, prints
  `{SIMULATION ABORTED}` / `{Illegal Op-Code Encountered}` / the pending error text, then walks the breakpoint list and
  calls `break_hit` for each triggered one. Returns nonzero when execution must stop. Second half: per `g_sim->+0x34` step
  mode: 0 = go (stop if repeat==0 && stop reason), 1 = step n instr (`repeat--`), 2 = trace with `{Trace cycle count=%lu}`
  after each cycle (fmt 0x4d175c), 3/4 = counters, default (5..0x15) = the source level step/next/until machine
  `step_advance`. After the report: refresh screen (0x43bb50), profile refresh (`0x45d280`, 0x46c4c0 per device when
  `DAT_004aaa90`), `win_update(0x7fff)` if the window is on, clear the per-pin break-pending bits.
  Breakpoint record (allocated elsewhere, >= 0x248 bytes, list link at +0x240):
  `+0 number, +4 type (0..0xc), +8 flags (bit0: always, bit1: only when g_dev+0x44 bit3), +0xc action (0 h(alt),
  1..4 i1..i4 counters, 5 note?, 6 s(top), 7 x(command exec)), +0x10 text of the break expression/address (name for
  reports), +0x110 command string for action 7, +0x210 enabled flag, +0x218.. 10 dwords of parameters copied to the
  stack (+2 lo address, +3 hi address, +0x10 (ushort) pin/space, +0x14 (ushort) reg index), +0x23c/+0x238 (ushort space/index
  for pin breaks, type 3..5), +0x240 next, +0x244 parsed C expression (type 0xc), +0x244.. `0x91*4` = C expr, `0x92/0x93` frame`.
  Types: 0/default = address (pc) match against last-fetch ring, 2/0xb = memory read/write via ring of 16 accessed
  addresses (types 9..0xb add space filter 0x80000), 3/4/5 = pin/peripheral flag bits 0x10000/0x20000, 6 = expression
  (`0x459480` value), 7 = register compare (`ushort` compare op at +0x236: ne, le, lt, ge, gt, eq), 8 = pc equals
  (`*(g_dev+0x1c)`), 0xc = C expression break. Type name strings: `g_bp_type_names` 0x4d04a8 (13 entries `r`, `rw`, `w`,
  `dr`, `drw`, `dw` ...), action names 0x4d488.
* 0x452f20 `break_hit(bp, &stop_run, &refresh)` (med): performs the action of a triggered break, `bar` logic on the repeat
  count (`g_sim->+0x28`, `+0x2c` = current break number). Prints `Break #%d %s%s %s %s;dev:%d pc:%04lx cyc:%ld`
  (0x4d17ac: number, type name, text, action name, command, `g_dev+4`, pc, cycle) via 0x43d1e0 for actions that stop
  (5,6 = also refresh) ; action 7 executes the stored command line through 0x43b5a0(dev, cmd).

## coffrd.c (63 functions): debug-info DB, source/assembly windows, step helpers

### Data structures (evidence: dbg_read_* functions)
* COFF file header: 0x1c bytes, fread'ed then swapped in place by `swap32_array` (dwords): `+0 magic (0x2c5..0x2cc are
  accepted by the profiler reader), +4 nscns, +8 timestamp, +0xc symptr, +0x10 nsyms, +0x14 opthdr size, +0x18 flags
  (bit 0 must be set = F_RELFLG in the profile reader)`. Kept in `g_cld_filhdr` (0x5021d0). Section headers start at
  `0x1c + opthdr` (`DAT_005021e4` = +0x14 of the header).
* Section header on disk: 0x34 bytes (13 dwords): `name[8], +8 paddr lo, +0xc paddr space, +0x10 vaddr lo,
  +0x14 vaddr space, +0x18 size, +0x1c scnptr, +0x20 relptr, +0x24 lnnoptr, +0x28 nreloc, +0x2c nlnno, +0x30 flags`
  (same layout as src/cofdmp). In memory (`dbg_read_sections`) one 0x20 byte record per section, index = section number
  (record 0 = template `g_null_section`); written as dwords: `[0]`,`[1]` = first line record `{addr, space}` (filled later by
  `dbg_set_section_line_start` when flags & 0x800 and lnno present), `[2]` paddr, `[3]` paddr space id, `[4]` size (or vaddr when flags & 0x400),
  `[5]` nlnno (later reused: first line index), `[6]` flags... EXACT: puVar[8..15] of the loop = `paddr(+8), space(+0xc), size-or-vaddr, s_flags-derived
  (+0x30 stored at [0xc]?)`: the code stores `[8]=hdr+8, [9]=hdr+0xc, [10]=size (vaddr if flags&0x400), [0xb]=hdr+0x1c(?), [0xc]=flags, [0xd]=nlnno, [0xe]=running line base,
  [0xf]=0` relative to a record start at index*0x20 (i.e. dwords 0..7 of record i+1 = the fields above). So in record terms:
  `+0 line start addr, +4 line start space, +8 paddr, +0xc paddr space, +0x10 flags-dependent size, +0x14 nlnno, +0x18 running index of first
  line record, +0x1c symbol index back reference (set to the class 0xca symbol by `dbg_number_symbols`)`. Flags used: 0x400 (paddr size is in vaddr), 0x800
  (line table to be remapped), 0x1000 (macro section).
* Symbol table record: 0x20 bytes: `+0 name[8]` or (`+0==0`, `+4` = string table offset; `dbg_sym_name`), `+8 value (address)`,
  `+0xc space id (index into g_space_names: p x y l n laa lab ... 0x12c entries? sic 0..)`, `+0x10 scnum`,
  `+0x14 type` (afterwards overwritten by `dbg_number_symbols` with the running file/scope number; type low
  bits `& 0x30 == 0x20` = function), `+0x18 storage class`, `+0x1c numaux`. Auxiliary entries follow (numaux). Storage
  classes seen: 200 (0xc8) and 0x67 = file (`.file`, aux holds the file name at aux+0x10 (or strtab offset when +0x10 == 0; `dbg_aux_name`),
  0xc9 = scope markers named `.bs`/`.es` (begin/end source?) and `.bm`/`.em` (class 0xcb: begin/end macro),
  0xca = section/`.bf`-style (begin function), 0xd2/0xd3/0xd5/0xd6/0xd7 = label kinds (0xd6 local/`global` flag), 2 = C_EXT,
  0x65 = `.bf`, 0x6a = fixed by `dbg_fix_symbol_classes` for symbols whose scnum == -1 and whose type is not a function/pointer.
  The reader keeps only names for class 0xd5/0xd3/0xd6/0xd2/0xd7/2 in the two sort indexes (`dbg_build_indexes`).
* Line record: 12 bytes `{ addr, space, line }`, line 0 = function marker (aux follows). `dbg_fix_linenos` rebases the
  line numbers of records by the `.bf` ("begin function") line offsets (`+ (bf_line - 1)`).
* Source file entry (`g_sim->+0x4020`, 12 bytes): `{ int nlines, long *offset (1-based, offset[line]=ftell), char *path }`
  built by `dbg_load_source_index` (counts '\n', opens with `fopen(name,"rb")`, path resolved by 0x438eb0(name,"",buf) =
  search path lookup).
* Source window buffer `g_win_buf` (0x4aaaa8): allocated `0x6464` bytes = 25 lines x 0x101 (line 0 = status line, lines 1..rows
  are text); width `g_win_cols`(0x4a8dac), rows `g_win_rows` (0x4a8db0). Lines are left justified and padded with spaces
  (`0x4c6d88` blank string).

### Functions (see names file for prototypes)
* 0x440030 `dbg_verify_section(dev,secno)`: for the section `secno` seeks `scnptr`, reads the words (or a single repeated word
  when flags&0x400) and compares with simulator memory via 0x457180(dev, space, addr, &value); returns number of
  mismatches (-1 on read errors); message `Error reading memory` (0x4c7abc). Used by `load` verification.
* 0x4401c0 `fread_swap32` = `fread` (0x484970) + 32 bit byte swap of `size*n & ~3` bytes; 0x440200 `swap32_array` (swaps
  every dword; note: called with size 4/count 2 to swap 8 char names, and size 1/count 0x10 for aux names(!)).
* 0x440240/0x440280: name accessors with error `invalid string table offset` (0x4c7ad4) (uses `g_sim->+0x3fe4`, `+0x3fe8`).
* 0x4402c0 `dbg_find_label(addr, space, &is_func)`: binary search in the address sorted index (`+0x402c`) for the closest
  symbol at or below `addr` in the same space class (space mapping through `g_devtype->+0x28 ops+0xc`), tie broken by
  file number distance; returns symbol index and sets is_func = (class == 0xd6).
* 0x440450/0x440c20 `dbg_find_sym_d2/d3`: walk the name index from `dbg_sym_bsearch` while names are equal until class 0xd2
  resp. 0xd3 is found. 0x440540 `dbg_sym_bsearch(name)`: binary search in the by-name index, returns first equal element
  (position, 1-based) or 0. 0x4404e0 `dbg_sym_name_eq`.
* 0x440730 `dbg_resolve_symbol(name, val)`: the general "symbol name -> value" lookup for the simulator's expression
  evaluator: accepts `file@name` (`@` separates file and symbol; `global@name` = search the .file entries for a
  match), else the current pc's file scope; names starting with `_` are locals (`dbg_find_local_label`,
  `dbg_find_macro_local`, `dbg_find_nearest_named`); other names via `dbg_find_scoped_sym`, block symbols
  (`dbg_find_block_sym`), sorted lookups and finally 0x464e30/0x464f40 (C symbol table, other group). Stores address
  and space in `val+0x14/+0x18` and returns the symbol index (0 = not found).
* 0x440670 `dbg_find_macro_of_file`, 0x440cb0, 0x440da0, 0x440e90, 0x440fe0, 0x4411c0, 0x441250: helpers scanning the symbol
  table between `.bm/.em` (class 0xcb), `.bs/.es` (class 0xc9) or `.bf` markers; nearest-address searches (`abs(addr -
  sym.value)` minimal). Semantics are only partly verified (low).
* 0x441320..0x4414c0: address -> file/line: `dbg_addr_to_file_sym` (first C_FILE symbol whose section start `<=` address...),
  `dbg_addr_to_fileno` (+0x14 field = renumbered file no), `dbg_addr_to_filename`, `dbg_addr_to_line_index` (scans the section's line
  records backwards for the entry `<= addr` with `line != 0`), `dbg_addr_to_line`, `dbg_fileno_to_name` (defaults to
  `dbg_addr_to_fileno(pc)` when arg < 0; range checked with `g_sim->+0x401c`).
* 0x441500 `dbg_format_addr(space, addr)` (high): returns pointer to `g_addr_str_buf` (0x5020d0) with
  `" %s:(%s%.200s+%lu)"` / `" %s:%s%.200s"` - i.e. ` p:(_label+3)`; `%s` first = space name from `g_space_names[space]`
  (p, x, y, l, n, laa, lab, ...), then `_` if the symbol is a function label(0x4c7b28) else empty, name, offset; empty
  when no symbol.
* 0x4415c0 `dbg_build_indexes`: allocates the two indexes (`+0x402c` by address, `+0x4030` by name; 4 bytes per symbol +
  headers), fills them with the record numbers of symbols with class 0xd5, 0xd3, 2, 0xd2, 0xd6 (not aux), qsorts (compare
  fns 0x4417e0 / 0x441890) and appends per-space start positions.
* 0x441910 `dbg_load_cld(dev, filename)` (high): the `load` back-end for debug symbols (`fopen(name,"rb")`, error
  `cannot open input file %s`). Temporarily switches the four current pointers to device `dev` (`g_dev = g_dev_tab[dev]`,
  `g_core`, `g_devtype`, `g_sim`), frees old data, copies the file name, then
  `dbg_read_filhdr` -> `dbg_read_strtab` -> `dbg_read_sections` -> `dbg_read_symbols` -> `dbg_read_linenos`, then
  `dbg_fix_symbol_classes`, `dbg_set_section_line_start`, `dbg_fix_section_line_range`, `dbg_number_symbols`,
  `dbg_load_source_files`, `dbg_build_line_map`, `dbg_build_indexes`, closes the file, 0x47ac00() (profile hookup) and
  finally runs `*(*(g_core+0x1c))` hook; on failure `dbg_free`. Restores the pointers. Returns 0/-1.
* 0x441b30/0x441ba0/0x441d10/0x442000/0x442340: readers, all with the error strings (0x4c7b2c..0x4c7c50: `cannot read string
  table length`, `cannot seek to symbol table`, `cannot read symbol table entries`, ...). `dbg_read_sections` fills the section
  records described above and accumulates `g_sim` running offsets; `dbg_read_linenos` reads only the line numbers of section
  1 (`lnnoptr` at header 1) and calls `dbg_fix_linenos`; `dbg_read_symbols` reads nsyms*0x20 bytes, swaps names (2 dwords) and file
  aux names, duplicates the table into `+0x3fe0`.
* 0x442530 `dbg_number_symbols`: renumbers symbols (scope/file counter into +0x14), links class 0xca symbols back to their
  section record `+0x1c`, and class 0xc9 (`.bs`) to enclosing scope. 0x4426f0 `dbg_load_source_files` /
  0x442930 `dbg_find_file_sym` / 0x4429f0 `dbg_load_source_index`: distinct source files from the class 200/0x67 entries and
  their line offset tables. 0x442c80 `dbg_free` frees everything and zeroes `+0x3fd0/+0x3fd4/+0x401c`.
* Windows: 0x442de0 `win_buf_alloc` (0x6464 bytes zeroed, into `DAT_004aaaa8`). 0x442e10 `win_update(delta)`: reselect
  the current device pointers, pc = `0x46c6a0()` (current pc), space via `space_of`, then mode 1 -> `asmwin_scroll`, else
  `srcwin_scroll`; if a window is active (`+0x4400 != 0`) `win_status_line()` and repaint 0x43dc00(buffer).
  0x442ee0 `win_status_line`: builds the status text in line 0 of the buffer with one of
  `no_source_file pc=%.20s@%lu %s:$%lx <%s%.12s%s>%s section:%.12s%s` /
  `src:%.20s@%lu pc=%.20s@%lu ...` / `asm:%s:$%lx pc=%.20s@%lu %s:$%lx <%s%.12s%s>%s section:%.12s%s`
  (0x4c7c70/0x4c7cb4/0x4c7cf8; args: file, line, pc-file, pc-line, space, pc, `=>`-suffix, label, `+off`, macro `macro:%.12s`, section name)
  and echoes it with 0x43d3a0 when the session log/echo flag `+0x184` and `+0x48` are set.
  0x443260 `asmwin_fill(addr, space)` (high): disassembly window: reads registers via 0x433f60/0x433f10 (names 0x4b2924/0x4b2928/
  0x4b2950/0x4b2934/0x4b2948/0x4b2990/0x4b2970), loops over `g_win_rows-1` rows: reads up to 10 words per instruction
  (via ops+0x24 or ops+0 / ops+0x14), calls the disassembler `g_core+0x10(words, text, sr, ..., &info)` producing the text and
  parallel-move info, appends memory access details (`%s` of `dbg_format_addr` for the info flag bits 1,2,4,8,0x10,0x20,0x40,0x80
  in `DAT_00502268` with data addresses `DAT_0050226c/70/74`), prefixes label (`%8.8s` / `%8.8s+%04lu`) and formats the
  row with `"%s%04lx %s %s%s%s"`, `"%s%06lx ..."` (24 bit address) or `"%s%08lx ..."` (mask bits 0x1000000/0x10000); the
  current pc row is marked with `=>` (0x4c7d9c) other rows two blanks.
  0x4431f0 `asmwin_scroll(delta, pc, space)`: `delta == 0x7fff` = recentre on pc unless already visible, else scroll by delta.
  0x443a40 `srcwin_scroll` similarly for source view (keeps `g_sim->+0x3ffc` top line, shows pc line at row 3),
  0x443c30 `srcwin_fill` reads the lines with `fseek(line_offsets[line])` + `fscanf("%160[^\n\r]")`, expands tabs to 8, formats
  `"  % 6d %s%s"` / `"%s% 6d %s%s"` (marker `=>` on the pc line) into rows padded to width.
* Step machine: `insn_is_branch` (0x443ed0) asks core branch ops (`g_core+0x20`) else disassembles 3 words and looks at the
  mnemonic: `b*`/`j*` except `bset`... - returns 1 and the instruction length; `step_classify_insn` (0x4444a0) classifies
  the instruction at addr (`rts` -> 0xc/0x11, branch/jump -> 0xb/0x10, other 0xa/0xf; +5 offset when the current mode is
  0xf..0x11 = "next" family); `step_mode_at_pc` (0x443e30), `step_setup_next` (0x4446d0), `step_advance` (0x443fd0, 0x4cd machine
  of modes 5..0x15 used by `next`, `until`, `finish`, `step line`) update `g_sim->+0x34` (mode), `+0x17c/+0x180` (target pc
  and space), `+0x28` (repeat), and set the refresh/stop flags; mode numbers: 5 run to line, 6 until pc, 7/8 step to next
  source line, 9 wait for `+0x17c`, 0xa/0xf next, 0xb/0x10 next over branch, 0xc/0x11 step out via `rts`, 0xd/0xe `finish`
  variants, 0x12..0x15 `until`/call-following (`0x465950` finds return address of C frame).
* 0x444ad0 `parse_line_spec(tok)`: parses `[file@]line` (`@` separated) or plain number for `until`/`list`; on success rewrites
  the token as type 'p' (0x70) with address/space, `Invalid line number` (0x4c7df0) else (sets `g_errmsg`, `g_err_tok`).
  0x444bf0 `dbg_line_to_addr(fileno, line, out{addr,space})`: address of the first line record `>=` line in file (closest
  greater line if not exact), 0 if none. 0x444cd0 `dbg_find_source_file(name)` (last to first, strcmp with file path).
  0x444d50 `dbg_parse_file_line`. 0x4450a0 `dbg_next_label(idx, &desc)`: next label alphabetically after symbol idx, description
  `%s%-20.20s %4s:$%-8lx section:%.20s` (`display labels`). 0x4455b0 `parse_list_spec(tok)`: list argument `[file@][line]`,
  sets tok type 'S' (0x53), start line clipped to file length. 0x445f10 `cmd_step_exec(arg)`: step variant (sets count from
  `DAT_004a96c0` when the token type char is 'i', step mode via `step_mode_at_pc(1)` when arg==1 or the window is
  in source mode, runs all devices, refresh).

Struct summary for the value cell used by parse_num_* (`val` pointer, shared with the expression evaluator):
`+8 low dword, +0xc high dword (24 bit DSPs: upper part shifted), +0x1c type flags (|0x100 integer, |0x200 float; low bits =
caller's type bits)`, float value is a `double` at `val+0` (see 0x44b2e0).

## iohist.c (33 functions): INPUT / OUTPUT channels

### I/O channel object (0x1e8 bytes, `calloc`'ed at 0x44c340 via 0x457e00(0x1e8,1))
`+0x000 char name[0x100]` (channel's file/pin name), `+0x100 char text[0x50]` = user visible name used in reports (`io+0x100` passed
to `"%s cyc=%lu:%s"`), `+0x150 FILE *fp` (NULL = terminal), `+0x154 int type`, `+0x158 int a` (space / peripheral index),
`+0x15c int first` (address / pin index / first pin), `+0x160 int last`, `+0x164 int serial` (from `g_sim->+0x44`), `+0x168
int b`, `+0x16c int c`, `+0x174 int peer_dev` (device for `input pin dvN:pin`), `+0x180 unsigned long cur[10]` (current value
cell, `g_null_value` 0x5024d8 initial; +0x188 = value lo used by memory/reg inputs), `+0x1a8 cur2[10]`, `+0x1d0 int immediate`
(1 = timed value pending), `+0x1d4 int radix` (0 binary,1 decimal,2 float,3 hex,4 unsigned; names `g_radix_names`
0x4cbed0: binary, decimal, float, hexadecimal, unsigned, string variant 5 = 'string' in outputs), `+0x1d8 int countdown` (input:
cycles until next value, -1 = EOF; output: cycle of last change), `+0x1dc void *loops` (stack of repeat loops read from the file `( ... ) n`:
16 byte records `{ long fpos, long started, long remaining, next }`, allocated in `io_in_skip_loops`), `+0x1e0 next`,
`+0x1e4 int id` (unique channel number, `io_alloc_id`).
Channel type (`+0x154`): 0 memory range (space `+0x158`, addr `first..last`), 1 register/pin group `t` (`+0x158` group), 2 `U`
(peripheral/port value, `+0x158`), 3/4 pin ('S') 3 = `S`-input text pins, 4 = `S`, 5/0xb = string source/`u` pin (`dev` in +0x174),
7 = memory of another device (`p`, `+0x168` space `+0x174` device), 8/3 = scalar pin/analog (`s`), 9 = peripheral bit
group (`g`), 0xa.. unused. (0x44c340 builds them from the token type char in `g_tok_type[n]`:
`P`/`X` -> 0, `S` -> 4, `U` -> 2, `g` -> 9, `p` -> 0, `s` -> 8 or 3, `t` -> 1; `j` = timed list; `r` sets radix from token).
Lists: `g_sim->+0x14c` inputs, `+0x150` timed inputs, `+0x154` outputs (delta format), `+0x158` outputs (stamped format).

### Functions
* 0x448740 `io_emit(io, text)` (high): if `io->fp == NULL` and text does not start with `#`, prints on the terminal
  `"%s cyc=%lu:%s"` (name, cycle counter `g_dev+0x20`, text with newlines replaced by blanks) through 0x43d3a0; else
  `fprintf(fp, text)` + flush (0x483a40 = fflush).
* 0x4487f0 `io_out_poll` (med): after every cycle, for output channels of types 3,4,8 compare pin state
  (`io_pin_state_str`) with the previous one and write `%01lu %s\n` (cycle stamped) or `#%01ld` + text (delta format).
* 0x448980 `io_pin_state_str(io, buf)`: builds the state string of pins `first..last` (walks the pin table
  `g_devtype+0x3c`, 0x18 bytes per pin, only pins in `g_devtype+8` mask): character per pin from `"01x"` (0x4caa78) or
  `"LHx"` (0x4caa7c) (low/high/unknown, driven/floating), or `%f` of the analog value (0x4cb16c) for type 8; returns 1 when
  anything changed.
* 0x448b60 `io_out_mem_write(space, addr, value)`: output channels of memory range type get `"%lx %s\n"` / `"%01lu %lx %s\n"`
  (address and value formatted by 0x457950(space, addr, radix, buf, value); radix 5 uses `io_read_string` for a 0-terminated
  string).
* 0x448de0 `io_out_reg_write`, 0x4496a0 `io_out_pin_write`: register / peripheral pin writes in the radix formats
  `%01lx`, `%01ld`, `%1.7f` (float via 0x45c6c0 from the DSP word), binary strings of 16/24/32 bits (mask table `DAT_004aab14+..`),
  `%15.15s` for the special float format; the per-peripheral formatter `g_core+8 -> ops+0xc` may override.
* 0x449200 `io_out_note(text)`: `stall`/`*** %s` note lines (`" *** %s"`, `"%01lu *** %s\n"`, `"\n*** %s"`); counts
  `g_sim->+0x47c` and returns whether a channel wants notes.
* 0x4493d0 `io_out_insn_trace(idx)`: "history" of executed instructions: `P:$%04lx %06lx <words...> <text>` variants
  (`%04lx`, `%06lx`, `%08lx` picked by mode bits 0x10000000/0x4000000/0x200/0x2000000 of the device mode word) using the
  disassembler; written to both output lists (type 6 channels).
* 0x449a70 `io_out_periph_write(a, b)`: peripheral bit group output (type 9) with 0x43bec0 formatter.
* 0x44ae30 `io_next_free_id`, 0x44c890 `io_alloc_id` (smallest unused id over lists +0x14c and +0x150), 0x44af20 `io_lists_reset`.
* 0x44af70/0x44b0b0/0x44b1d0/0x44b2e0: mutually recursive numeric literal parsers: `` ` `` prefix decimal, `$` hex, `%` binary,
  digits with `.` -> float (`strtod`, then 0x45a9c0 rounding to the DSP fixed format), leading `-` negates (64 bit two's complement in
  two 28 bit halves (base-10 accumulate) for decimal); result in `val+8/+0xc`, flags `type | 0x100` (float `| 0x200`). Used
  widely (expression evaluator, io files).
* 0x44b380 `io_parse_value(text, io, type)` dispatch by channel radix. 0x44b410 `io_in_mem_read(space, addr, &v)`,
  0x44bb90 `io_in_reg_read`, 0x44bbe0 `io_in_periph_read`, 0x44bc30 `io_in_pin_read`, 0x44bc80 `io_in_timed_pin_read`:
  lookup in the channel lists (0x43b860/0x43b880 helpers, other group) and advance via `io_in_next`.
* 0x44b4f0 `io_in_next(io)`: input file format: optional `# n` delay records (`" # %ld"`) then value token (`" %89[^ #()\n\t;]"`):
  `io_in_skip_loops` handles `(`/`)` repeat brackets and `;` comments (`" %1[(]"`, `" %[;]"`, `" %[)]"`, `%*[^\n]`), reads with 0x4839d0 (`fscanf`)
  and keeps `countdown = delay-1`; `io_in_read_token` (0x44b550) reads the value; if the file prefix is ` %[t]` (typed input from the terminal)
  it prompts `Enter %s value for %s:` / `Enter pin data for %s:` and edits with the line editor 0x439f40 (ESC aborts: countdown -1
  and sets `g_sim->+0x1c`). By channel type it stores the value with `io_parse_value`, the peripheral's set function
  (`g_core+8` ops+8), `io_pin_set_from_text` (chars `0 l p` clear, `1 h` set, `n`/`p` special, `x` release/tristate), etc.
* 0x44bce0 `io_in_timed_next`, 0x44bd60 `io_in_timed_advance`: timed inputs (`+0x1d0` immediate flag, `+0x1d8` = absolute cycle,
  reads `+ <cycle>` record `" %[+]"`), 0x44bde0 `io_in_poll` (med): per cycle over lists +0x150/+0x14c: applies pending values
  to memory/pins/peripherals (0x12c-byte port records: `word = mask & new | ~mask & old`), 0x44c150 `io_pin_copy`, 0x44c280 `io_pin_copy_tri`: pin-to-pin
  connection (`input pin dvN:pin`) with tri-state handling.
* 0x44c340 `cmd_input_open` (med): back-end of `input`/`output` opening (token types listed above): allocates the channel,
  copies the name, chooses list (+0x14c or +0x150), opens `fopen(path,"rb")` (path from 0x438eb0 search) printing `{Error opening:%s}`
  (0x4c5c7c) on failure, sets type/range and registers memory watch via 0x43a930(2, space, first, last, serial).

## cofload.c (24 functions)

### 0x47d160-0x47da20: subroutine profile (belongs with profile/profrep)
Profile context `g_prof` (0x505b64, same pointer that other modules use for instruction statistics): `+0x34e0` flags (bits 1..2 stack
over/underflow, bit 4 = nested, bit 0x10 disabled), `+0x34e8` string pool, `+0x3514` list of subroutine records, `+0x3518` root
(`__MOTHER__`), `+0x3520 + i*0x1c` call stack (7 dwords: `{ sub, retpc, entry cycle, ...}`, depth `+0x3788`), `+0x3798`, `+0x378c/0x3790` (file,line)
of overflow, `+0x37a0` state (1 none executed, 3 = profile ok), `+0xbc` current cycle count. Subroutine record: `+0 addr, +4 name,
+8 callers list, +0xc, +0x10 callee list, +0x14 caller list, +0x18 flags (1 named, 2 done, 4 called, 8 recursive?), +0x1c cycles, +0x20
recursive cycles, +0x24, +0x28 calls`. Names from `subr_format_name`: `_???_p:$%lx(<-%c:$%lx)` / `_???_p:$%lx`, "(M)" (main) and "(i)" (inline) suffixes.
`subr_report` prints Basic Subroutine Profile ("Routine Type #calls ..."), then Subroutine Call Graph report.

### 0x47dc80-0x47ed70: profiler's own COFF reader
Same file layout as coffrd but different tables: header in `g_prof_filhdr` (0x5042c8, accepts magic 0x2c5..0x2cc, requires flags bit0),
symbols in `g_prof_symtab` (32 byte records, aux via numaux), strings `g_prof_strtab`/`g_prof_strlen`, section table
`g_prof_sections` with 0x44 byte records: `+0..0x33` raw header (13 dwords), `+0x34` end address (paddr + size, size >> 1 for spaces
3/9/10), `+0x38` section index, `+0x3c` flag "file contains macro `.tx`", `+0x40` index of the file symbol. Error
`Failed to handle COFF file` (0x4d3e60) through 0x46b0a0(1, msg) which longjmps (`g_prof_jmpbuf`, `__setjmp3` in `prof_load_cld`).
`prof_load_cld` (0x47dc80) creates four lists (`0x46a700(kind)`: kinds 1,0,4,6 stored at `g_prof+8,+4,+0xc,+0x3514`), then if the
file name `g_prof+0x60` is set calls `prof_read_cld` (0x47dd20): open ("rb") -> `prof_read_filhdr` -> `prof_read_sections` -> `prof_read_strtab`
-> `prof_read_symbols` -> `prof_get_source_line(0)` init -> `prof_read_all_lines` -> close; then builds the subroutine list; source lines via
`prof_get_source_line(fileno, line)` which returns `g_prof_srcinfo` (0x504490: `{ name, line, text?, ... }` reading up to 400 bytes per line,
recognising `;##` markers (nested = `nested`), the `dc`/`ds` directives) and warns `Source file %s more recent than executable`
(0x4d3d30) when the file is newer than the executable (`g_now`, `g_prof+100`).
`prof_read_section_lines` reads the line records (12 bytes) of each code section and registers them (0x46b8b0(addr, space, target, srcinfo)) with
the file name; `prof_mark_data_section`/0x46b700 mark memory cells ("data" bit 2 in cell flags at +0xc).

## Globals (see names file; addresses)
Current pointers: 0x50578c `g_sim`, 0x505790 `g_devtype`, 0x505794 `g_core`, 0x505798 `g_dev`; `g_cur_dev` 0x4a8dcc, `g_ndev` 0x4aab0c (32), `g_dev_tab` 0x4aab10 (array of dev
pointers), 0x4aab08 (array of devtype pointers), 0x4a8db4 (core), 0x4a8d98 (per-dev `g_sim` array). Window: `g_win_buf` 0x4aaaa8 etc.
Command line tokens: 0x4a92e8 line text, 0x4a9468 token start offsets, 0x4a93e8 token type chars, 0x4a9670 token value records (0x28 bytes: `+0` value
`+4` end, `+0xc` space, `+0x10` ushort reg no, `+0x14` flags 0x4100 ...), `g_errmsg` 0x4a8dd0 (pending error text shown by `sim_check_stop`).

## Cross-module interfaces (called, not defined here)
0x43d3a0(text,1) write line to screen/log, 0x43d1e0 (same, for break reports), 0x43db40/0x43db50 begin/end paged output, 0x43dbc0 cursor/flush, 0x439080(space,pc)
space table index, 0x439140(dev) select device, 0x433f10/0x433f60 read register by name (name strings 0x4b29xx), 0x457180(dev,space,addr,&v)
read memory, 0x457e00(n,flag)/0x457ed0 malloc(calloc)/free wrappers, 0x45a8c0/0x45a8e0/0x45d2b0 error printers, 0x46c6a0() current pc,
0x46b510/0x46b0a0/0x46a700 (profiler file/list helpers), 0x43b860/0x43b880/0x43ba40 (I/O channel list lookup), 0x43b640 (string
setter), 0x43ddd0/0x43dd70 (string pool), 0x45c6c0 (word to double), 0x45a9c0 (round double to DSP format), 0x4839d0 (fscanf), 0x484970 (fread), 0x483a40 (fflush).

## Quirks
* `swap32_array` (0x440200) reverses the bytes of every dword: the .cld/COFF files are big-endian and the x86 original converts on read (agrees with CLAUDE.md). It is also applied to 8 char names with (size 4, count 2) and to aux file names with (size 1, count 0x10 -> 16 bytes, i.e. 4 dwords swapped as dwords), so name bytes appear dword-reversed on disk; a portable reader must replicate that (name chars: bytes of each dword in reverse order).
* `dbg_verify_section` returns the number of mismatches minus one convention (`param_2 = -1` initial, `0` after successful read, `+1` per mismatch).
* Help lookup is exact and case sensitive; the two-level tables mean `help <register>` prints a per-peripheral table.
* `parse_num_dec` accumulates into three 28 bit chunks (up to 84 bits) then folds to 56 bits: values above 2^56 wrap.

## Open questions
* Exact roles of section-record fields +0x14/+0x18/+0x1c in coffrd (only patterns known); exact stop-reason bits of `g_dev+0x44`.
* Step machine mode numbers 5..0x15 (partly deduced from `step_classify_insn` transitions).
* I/O channel types 5/0xb (`S`/`u` string sources) and the meaning of `t` (type 1 register/peripheral group).
* Whether the two explicit list heads +0x154/+0x158 are output vs. history lists (behaviour: +0x154 writes `#delta` records replayable by `input`, +0x158 writes cycle stamped `%lu value`).
