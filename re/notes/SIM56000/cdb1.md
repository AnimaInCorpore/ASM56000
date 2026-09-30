# SIM56000.EXE - group cdb1 (cdbutil, cdbsym, profrep, cdbbt)

Names: `re/names/SIM56000/cdb1.names.txt` (259 functions, 51 globals). Inputs: `re/out/SIM56000/mod/{cdbutil,cdbsym,profrep,cdbbt}.c`.
Ghidra `local_NN` are +4 off real ebp offsets. Only `cdbutil.c` (0x4d30a4) and `cdbbt.c` (0x4d4060) are real
source names (strings passed to `cdb_internal_error(file, line)`); everything else is guessed.

## 0. The mod/*.c split does NOT match the real source modules

The address-based split lumps unrelated code together. Corrected picture (function ranges, evidence):

| range | proposed module | content |
|---|---|---|
| 0x45e5a0-0x45ef60 | `hostio` (host I/O / "syscall" service for the simulated C program) | packet buffers, `hio_step` state machine (open/close/read/write/lseek/unlink/rename/access), word<->byte packing, errno map. Called from 47adf0 (device I/O). |
| 0x45efe0-0x464f40 | `cdbutil.c` | C-debugger value access (load/store target lvalues), value/type formatting, register tables, arch parameters. |
| 0x464e30, 0x464f40 | cdbutil tail / `cdbsym` head | source file / function lookup in the COFF symbol table |
| 0x4650a0-0x466950 | `cdbsym.c` | walking the in-memory COFF symbol table: scope lookup, struct/enum members, function of PC, line table |
| 0x466950-0x46a36a | `cmdparse` (odd, unaligned addresses: different object/compiler options) | command argument syntax classifier, see 6. Entry `parse_command_line` (0x46a2d1) is called from cmdloop/help (0x43a470, 0x439410, 0x43b5a0). |
| 0x46a700-0x46aec0 | `avltree` | generic AVL tree + iterator (used by the profiler records (profrep) and by the 0x47c-0x482 modules) |
| 0x46b090-0x46bfd0 | `profrep` / profiler data model | error handler (`*** MAJOR PROFILING ERROR - SIMULATOR ABORTED ***`), file helpers, records for instructions/functions/lines/files |
| 0x46c000-0x46dfa0 | `cdbbt.c` | back trace / frame unwinding (three architectures) |
| 0x46e1a0-0x46e870 | (mod/ says cdbbt; NOT in my mod file) belongs to next group | |

## 1. Global context objects (shared with other groups)

| addr | name | meaning |
|---|---|---|
| 0x50578c | `cur_prog` | "loaded program" object, holds the COFF data in memory. Offsets used here: +0x30 (data-model flag 1..4, see parm_match_condition), +0x0c (current file/handle set by parm_filename), +0x3fac/+0x3fb0/+0x3fb4 frame list head/tail/current (see 8), +0x3fb8 default data memory space (1=X,2=Y,3=L?, see `cdb_detect_space_model`), +0x3fd8 symbol count (32-byte entries), +0x3fe0 symbol table (entries expanded to 0x20 bytes), +0x3fe4 string table pointer, +0x3fe8 string table size, +0x3fec line table entry count, +0x3ff0 line table (12-byte entries, sorted by address; word +8 == 0 means continuation). |
| 0x505790 | `cur_arch_desc` | architecture descriptor: +4 arch id (DAT_00503f44), +0xc capability flags (or a getter function at +0x4e8), +0x14 number of memory spaces, +0x18 space table (0x48-byte entries, +0x2c -> sub-table, name at +0), +0x1c number of register blocks, +0x20 register table (0x2c bytes each; +0x10 start, +0x18 flags, +0x20 mask), +0x28 vtable (+0xc = space/addr -> map-entry-index lookup), +0x40/+0x44 = port count / port table (0x14 each, name at +0), +0x4e8 optional flags callback. |
| 0x505794 | `cur_dev_ops` | device ops vtable: +0xc (load file), +0x10 (register instr), +0x18 -> table with +0x3c = decode instruction, +0x1c -> optional backtrace hooks (see 8). |
| 0x505798 | `cur_dev` | current device object: +4 device index, +0x1c current PC. |
| 0x503f44 | `cdb_arch` | target architecture id: see 2. |
| 0x505b64 | `prof_ctx` | profiler context (see 7). |

## 2. Architecture ids (cdb_arch, set by `cdb_arch_init` 0x45f790)

Code tests these constants everywhere. Word geometry (`cdb_arch_init`):

| id | words | notes |
|---|---|---|
| 0x2c5, 0x2c8 | 24-bit (word_mask 0xffffff, ext_mask 0xff, bits 24, ext bits 8, sign 0x800000, ext sign 0x80) | DSP56000 (0x2c5), 0x2c8 = 56300-style variant (addr_mask 0xffffff for 0x2c8, 0xff0000+0xffffff-ish for 0x2c5 = `(-(id!=0x2c8) & 0xff010000)+0xffffff`) |
| 0x2c6 | 32-bit (all masks 0xffffffff, bits 32, sign 0x80000000) | DSP96002 (float capable; float/double formatted via native `%.15e`) |
| 0x2c7, 0x2ca, 0x2c9, 0x2cc | 16-bit words (word_mask 0xffff, ext_mask 0xf, bits 16, ext bits 4, sign 0x8000, ext sign 8; addr_mask 0xffff, 0x2cc: 0xffffff) | DSP56100 family (0x2c7 = 56100, backtrace hooks for 0x2c7/0x2c5/0x2c6 only) |
| 0x2cb | 16-bit data, 32-bit address mask, 16 bit words with 8-bit ext | 56600-like variant (memory read via `FUN_00457240/457060` = 2-word access, see 3) |

Registers used for unwinding (strings 0x4b2920..): `r2` (56100 frame reg) / `r6` (56000) / `r0` (other), `sp`, `sr`, `ssh`, `ssl`
(hardware stack), `a` (return value accumulator), `ictr`, `cyc` (counters saved around called functions), 96k: `d0.l/d0.s/d0.d` return regs.

## 3. Struct: C value (0x40 bytes) - "cdb_val"

Created by `cdb_lookup_variable` / `cdb_register_value` (via allocator FUN_0047f0a0, node points to it at node+0x10), copied by value in formatting
routines (`0x10` dwords). Fields (offset: use, evidence):

| off | field | meaning |
|---|---|---|
| +0x00,+0x04,+0x08 | `alt[3]` | secondary word triple: float/double image halves, or 16-bit halves at +8/+10 (short) |
| +0x0c,+0x10,+0x14 | `w[3]` | data words: low, mid/high, extended (accumulators use all three; `cdb_num_hex` prints w[2],w[1],w[0]) |
| +0x18 | `addr` | address / register number / symbol value |
| +0x1c | `space` | memory space number (0=P,1=X,2=Y,3=L; `cdb_default_space()`), or register block index |
| +0x20 | `type` | COFF type word: low nibble basic type (2 char,3 short,4 int,5 long,6 float,7 double,8 struct,9 union,10 enum,11 moe,12-15 unsigned), derived types in 2-bit-per-level 4-bit fields (`t&0x30`: 0x10 pointer, 0x20 function, 0x30 array; peeled with `t & 0x1000f \| (t>>2)&0x3ffebff0`), DSP additions 0x10000 frac,0x10001 unsigned frac,0x10002 long frac,0x10003 unsigned long frac,0x10004 accum,0x10005 long accum |
| +0x24 | `sclass` | COFF storage class: 1 auto, 2 extern, 3 static, 4 register, 9 arg, 0x11 regparm, 0x12 field (bit-field), 0x80000000 = device/special register |
| +0x28 | `tag` | symbol index of the struct/union/enum tag (aux entry), or size info for 0x80000000 kind (bit 0x2000000/0x80000 flags) |
| +0x2c..+0x38 | `dim[4]` | array dimensions (1 if scalar); for a bit-field +0x2c holds the bit width |
| +0x3c | `valid` (short) | 1 = lvalue read-in valid (checked by `cdb_load_value`) |

Dispatch on `sclass`: `cdb_load_value` (0x45efe0)/`cdb_store_value` (0x45f090): 1 -> auto (frame-relative), 2/3/0x12/0x13 -> memory, 4/0x11 -> register, 0x80000000 -> device register, 9 -> arg (= auto).
Bit-fields: `cdb_load_memory` reads up to 3 words at addr+off/word_bits, shifts/masks with `cdb_bitmask_tab` (0x4927f8, 33 masks) and sign-extends.

## 4. cdbutil functions (0x45e5a0-0x464f40)

hostio (0x45e5a0-0x45ef60):
- `hio_buf_alloc/resize/free/clear` (5d0/620/680/5a0): packet buffer {+0 ready flag, +4 length, +8 capacity (words), +0xc data as array of 32-bit words holding one byte/word each}. `resize` exits with `memory exhausted.\n` (0x4d2c28) to stderr on failure.
- `hio_step(reply, request, fdtab, state, result)` (0x45e6a0): state machine driven by the packet's first word (request code): 0 (init/query), 1 (`FUN_0047aa10` chdir/remove by name), 2 (read: `FUN_0047a9a0` on fd < 0x15), 3, 4 (seek/lseek: `FUN_0047abc0`), 5..7, then stage 1..7 (open with flag translation 1->O_WRONLY.. 0x200/0x100/0x8000 text/binary, close `FUN_004915e0`, rename `FUN_00485a20`, access `FUN_00489900`). `fdtab[fd]` = 1 text mode / 0 binary. Result errno passed through `hio_errno_map`.
- `hio_errno_map` (0x45edd0): host errno -> simulated-C-library errno: 2->6, 9->8, 12->3, 13->7, 22->9, 29->10, 33->1, 34->2, else -1.
- `hio_words_to_bytes` (5ee70, low byte of each word), `hio_pack_words` (5eea0, big-endian bytes per device word size = `FUN_0047ade0()`), `hio_bytes_to_words` (5ef20), `hio_unpack_words` (5ef60).

cdbutil core:
- `cdb_arch_init` (0x45f790), `cdb_reg_name` (0x45f930; tables at 0x4921f0..0x492318 per arch, `(class,index)` -> register name; class 5/6/7/0xf = special/register-pair classes), `cdb_memspace_name` (0x45fb90; table 0x492340, 0x124 entries, default "?" at 0x4d2f3c).
- Error reporting: `cdb_error(msg)` (capitalises first char, formats with 0x4d30b0, shows via FUN_0045a8c0), `cdb_c_error(msg)` -> `"C error: %s"` (0x4d30b8) via FUN_0045d2b0, `cdb_internal_error(file,line)` -> `"C error: internal error, please report (file %s, line %d)"` (0x4d30c4). All suppressed when `cdb_quiet` (DAT_00503c84) is set (`cdb_set_quiet`, 0x45f150).
- Allocation wrappers: `cdb_malloc(n)` = FUN_00457e00(n,0), `cdb_realloc`, `cdb_free` (0x45f230/240/260).
- `cdb_free_expr(node)` (0x45f270): recursive free of a C-expression tree node {+0 left,+4 right,+8 third,+0xc token code (0x145 = function call),+0x10 string, +0x14 singly linked list of {child,next}}. `cdb_expr_has_call` (0x45fea0) searches for token 0x145.
- Output buffer: `cdb_out_reset` (0x464b50), `cdb_out_append(s)` (0x464b80): growable buffer `cdb_outbuf/cdb_outlen/cdb_outcap` (capacity doubles from `cdb_outcap` 0x4d30a0). `cdb_value_to_string(v,radix)` (0x45f2f0) and `cdb_type_to_string(v)` (0x45f310) reset the buffer, format, and return it. `cdb_print_typed_value(radix,v)` (0x45f330) prints `"<type>: <value>"` (string 0x4d3100 = ": ") through `cdb_print_wrapped`.
- `cdb_print_wrapped(text, prefix_first, prefix_cont, indent, to_log)` (0x45fbc0): tokenises `text` with strtok on 0x4c5890 (whitespace), breaks lines at `cdb_wrap_width` (DAT_004a8dac) honouring `"..."` quoting and the `},` sequence, writes each line with FUN_0043d1e0 (to_log==0) or FUN_0043d3a0. Line buffer `cdb_wrap_line` (0x502a70).
- `cdb_register_value(name)` (0x45f400): resolves a register name through FUN_00433f60 (name -> block,index) and builds a value (sclass 0x80000000); error strings: `"register <name> unknown"` (0x4d3104/0x4d3124), `"register <name> is write-only"` (0x4d3114). Sets `type` by name: `cnt` / `r<digit>` (0x1e) / `d<digit>[.s|.d|.x]` (6/7) else 0xe/0xf from block flags.
- Frame slot: `cdb_frame_slot(sclass, off, &space, &addr)` (0x45f390): frame pointer (via `cdb_frame_fp`) +/- `off` masked with `cdb_addr_mask` (arch 0x2cb: `fp + (8-off)`).
- Saved-state stack for evaluating function calls inside expressions: `cdb_saved_push/pop/clear` (0x45ff00/30/50, ring of 1024 in `cdb_saved_stack`, index `cdb_saved_idx`), `cdb_save_counters(retaddr)` (0x45ff60; reads `ictr` and `cyc` into 0x502a60/0x502b70, error `"unable to read register"`), `cdb_finish_call(&pc)` (0x460000; restores counters, pops the saved value node and fills its result words from the return registers according to its type: 1/2/3.. by `sclass`; internal error line 0x53d).
- Type/value formatting (`cdb_format_value` 0x460940 dispatches on type): pointer `cdb_fmt_pointer` (0x460b50; prints "<space>:<addr>" and, for char*, the string in quotes with escapes, max 0x400 chars, `...` appended), function `cdb_fmt_function`, array `cdb_fmt_array` (`{a, b, ...}`), char (escapes `\a \b \t \n \v \f \r \" \' \\`, else `'\%lo'`), short/int/long/accum/long accum/float/double, struct `cdb_fmt_struct` (`{name = value, ...}`; strings `"<%s contents not available>"` 0x4d3344). Radix argument mapping (from the dispatch in every `cdb_fmt_*`): 0 -> `cdb_num_bin` (0x4626a0, hex digit table 0x4927b8 printing 4 bits per entry, so nibble/4 grouping), 1 -> `cdb_num_signed` (decimal), 2 -> frac/float, 3 -> `cdb_num_hex` (`0x%lx%06lx%06lx` etc. by word size), 4 -> `cdb_num_unsigned`, default = natural for the type.  (The numeric helpers are all in 0x462010-0x462a20; for 24/32-bit arithmetic on 48/96-bit values they use FUN_0046f1a0/0046f3e0 = wide divide by 10 from cdbeval.)
- `cdb_type_name(v)` (0x4604e0): builds a C-like type name: `pointer to `, `function returning `, `array [%ld] of ` prefixes, then basic name (`char`, `short`, `int`, `long`, `float`, `double`, `unsigned ...`, `struct X`, `union X`, `enum X`, `frac`, `long frac`, `unsigned frac`, `unsigned long frac`, `accum`, `long accum`; unknown -> `<type unknown>`, missing tag -> `%s <%s type not available>`).
- Value access: `cdb_load_auto/store_auto` (0x462a50/0x462ab0: compute frame slot then memory access), `cdb_load_memory/store_memory` (0x462b10 / 0x463480, error strings `unable to read/write memory`), `cdb_load_register/store_register` (0x463e50 / 0x4642e0: register looked up via `cdb_reg_name(sclass,index)` + `cdb_find_saved_reg(frame_saved_list,name)` (0x464290, 5-char strncmp) so callers' registers saved in outer frames are read from the stack), `cdb_load_devreg/store_devreg` (0x464640/0x4648a0), `cdb_load_arg/store_arg` (0x464b10/0x464b30).
- Fractional conversions `cdb_frac1_to_double` (0x464d60) and `cdb_frac2_to_double` (0x464c30) (fixed point word(s) -> IEEE double bit pattern), `cdb_frac_to_double` (0x4628c0: 56000 accumulator with ext byte, divides by 2^(bits-1)), wrappers 0x4629d0/00/20 for frac/long frac/accum variants.
- `cdb_find_file_index(name)` (0x464e30): name up to '@' (source@line syntax) -> matches C_FILE (0x67) entries by basename; `cdb_find_function(name, file_sym)` (0x464f40).

## 5. cdbsym functions (0x4650a0-0x466950)

Symbol table entry (0x20 bytes, array `cur_prog+0x3fe0`, count `+0x3fd8`; expanded COFF symbol, aux entries follow the entry, +0x1c = number of aux slots so `next = i + 1 + numaux`):

| off | field |
|---|---|
| +0 | name[8], or `{0, strtab_offset}` when +0 is 0 (`cdb_symname_ptr` 0x4668b0: offset must be >3 and <= strtab size else error `invalid string table offset`; strings starting with `F` (function marker) are skipped by one char in `cdb_sym_name`) |
| +8 | value (address / offset / size) |
| +0xc | memory space or section |
| +0x10 | scnum (-2 = debug symbol) |
| +0x14 | type word (see 3) |
| +0x18 | storage class (COFF C_*: 100 block `.bb/.eb`, 101 fcn `.bf/.ef`, 102 EOS, 103 file `.file`, 15 ENTAG, 16 MOE, 13 TPDEF, 18 FIELD ...) |
| +0x1c | number of aux entries |
Aux entry (in following slot): +0x0 tag index (for struct/union/enum types: first member `iVar+1` index), +0xc/+0x10/+0x14/+0x18 up to 4 array dimensions, +0x4 (function: size), +0x10 (function: index of next function), +0x28 (field: bit size at +0x28 of the entry).

Functions: `cdb_lookup_symbol(name)` (0x4662f0: current block chain via `cdb_enclosing_block`, then `cdb_find_local`, args `cdb_find_arg`, then global `cdb_lookup_static_or_ext`; caches last hit in 0x4d4134/0x4d4138), `cdb_lookup_variable(name)` (0x465230: symbol -> value via `cdb_sym_to_value` (0x4654e0), error `"undeclared identifier %s"` / `"undeclared identifier"`), `cdb_lookup_scoped`/`cdb_lookup_global` (walk the table tracking block nesting via `.bb`(0x4d3408)/`.eb`,`.bf`(0x4c7c28)), `cdb_func_of_pc(pc)` (0x465a00: function symbol containing pc), `cdb_line_index(addr)` (0x4657c0: binary search in the line table with 12-byte entries), tag/member navigation (`cdb_find_member`, `cdb_next_member`, `cdb_struct_size` (value of the EOS entry), `cdb_enum_member_by_value`), type equality `cdb_types_match` and structure comparison helpers (`cdb_struct_layout_eq` etc.), `cdb_default_space`/`cdb_detect_space_model` (guess default data memory model from the first C_FILE aux `.file` type: 1,2,3 -> `cur_prog+0x3fb8`).

## 6. cmdparse (0x466950-0x46a36a): command-argument classifier

Central data: `parm_ctx` (DAT_00503c90, points to static `parm_ctx_storage` 0x4a91e8, size >= 0x1888):

| off | meaning |
|---|---|
| +0x000 | lower-cased copy of the command line (0x100 bytes; each token NUL terminated) |
| +0x100 | original-case copy |
| +0x200 | one classification letter per token (index = token number, 1-based; +0x201 = token 1) |
| +0x280 | token count; +0x280+4*i = offset of token i in the text; +0x284.. |
| +0x480+0x28*i | per-token parsed record (10 dwords copied from expression/number parser nodes `FUN_00459360/459480`); i.e. +0x488 primary value (index/number), +0x48c secondary (range end), +0x4a0/+0x4a2/+0x4a4/+0x4a6 = shorts: register index/class, register block, space/device index, device number |
| +0x1880 | base ptr; +0x1884 offset of the error position |
`parm_errmsg` (0x4a8dd0) holds the message shown by the caller: `Invalid parameter`, `Need more parameters`, `Too many parameters`, `Range of Break Number is 1-99`, `Frame number must be positive`.

`parm_tokenize(line)` (0x46a36a): splits on blanks, keeps `"..."`, `'...'`, `{...}` groups, ';' terminates (token letter `;`), initialises every token as `u` (unknown), the terminator token as `e`.
`parse_command_line(line)` (0x46a2d1): tokenises, tries `parm_command_name(1)` (0x467fa9: exact/prefix match of token 1 against the command table `cmd_tab` (0x4a8dbc, `cmd_count` entries; each command has name, abbreviation and a handler `->+0x14` that validates the remaining arguments and returns a "syntax vector"), returns `&PTR_FUN_004d3718` for a bare `;`-command, `&PTR_LAB_004d3720` for a device-only line (`dvN` as command with a following argument), or NULL.
Token classification letters (set by the `parm_*` matchers; `u` = no match/error; the command handlers test them): `K` (need more parameters), `c` command, `n` device `dvN` (0x468115), `t` device type / space/reg block name, `p` symbol/space prefix, `port:`-name `U`(0x55) / `s`(0x73) port name / `S` port range `a..b` (0x53), `g` register (`reg:` prefix, 0x469849), `G` register range `a..b` (0x47), `I` integer expr / `F` float expr / `P` `addr:space` pair (0x50) / `X` `a#count` range (0x58) / `Y` condition, `M/N/H/O/A/B/b/d/m/r/R/o/h/u/w` keyword classes (tables at 0x4d3458..0x4d3708):
- A (0x41): `h i1 i2 i3 i4 n s x` (0x4d3458)   - M (0x4d): `r rw w` (0x4d3478)   - N (0x4e): `dr drw dw` (0x4d3488)   - H (0x48): `!= == < >` (0x4d3498)   - O (0x4f): `and or then` (0x4d34a8)
- b (0x62): condition codes `al cc cs ec eq es ge gt lc le ls lt mi ne pl nr nn` (0x4d3630/0x4d35e8; 0x4d3678 for 96k with `hi vc vs` and `fgt ... fmi`); B (0x42) bus names (pcf pcm xab1 xab2 / pa xa ya / pcf pcm pcfm pce / dma pa xa ya / ...) chosen by arch flags
- d (0x64): `off on r rw w` (0x4d34f8)   - r (0x72): radix letters `b d f h u` (0x4d34b8), R `b d f h u` (0x4d3510), `-rb -rd -rf -rh -ru` (0x4d3528), `+ -rs` (0x4d3540)   - m (0x6d): `m0..m8` (0x4d34d0)   - u (0x75): `pullup` (0x4d353c)   - o (0x6f): `-a -c -o` (0x4d3558)   - h (0x68): `stdin stdout stderr` (0x4d3708)   - j (0x6a): `all io dsp` (0x4d3b34..3c) (used with `parm_keyword1`)
Helpers: `parm_match_keyword(idx, table, letter, count)` (0x469fe1) exact match; `parm_need_more(idx)` (0x4685b5); `parm_check_too_many(idx)`; `str_find_char/str_find_word` (0x46a0d3/0x46a134, word = delimited by non alphanumerics and '_'); `parm_c_expr` family (`parm_c_expr_check`, 0x467d7c: parses the token text with `FUN_0046ec60` (cdbeval parser) and rejects function calls with `"breakpoint expressions cannot contain function calls"` (0x4d3a70), `"type expressions cannot contain function calls"`, `"watch expressions cannot contain function calls"`).
Others: `parm_address_spec` (0x468b59) parses `[space:]addr`, `addr#count`, `addr..addr`; `parm_match_condition` (0x46706c) parses `reg op value` (op from `!= < > ==` with `<=`/`>=`) into the record; `parm_break_number` (0x4676e2) `#n` with range check 1-99 (`0x4d3454`), `parm_break_number_list` (0x467afb) `#1,#2..#5`, `parm_frame_number` `#n` >= 0.

## 7. avltree and profrep (0x46a700-0x46bfd0)

AVL tree (`avl_*`): tree header 3 dwords `{root, count, cmp_index}` (`avl_new(cmp_type)` = 0xc byte alloc, +8 = index into the comparator table `avl_cmp_tab` 0x4d3b48; comparator(a,b) returns 0 (a<b), 1 (equal), 2 (a>b), 3 (null)). Node 0x10 bytes `{height, left, item, right}` (`avl_set_node` 0x46a930 recomputes the height; `avl_rebalance` 0x46a990 performs rotations). `avl_insert(tree,item,replace)`, `avl_delete(tree,key,free_mode,repeat)` (returns the removed item; free_mode 0 none, 1 free item, others also free node), `avl_find(tree,key,mode)` (mode 1 = exact; other = nearest below/above), `avl_walk(tree,fn,order,bracket)` (order 0..5 = in/pre/post variations), `avl_copy_sorted` (rebuilds with a different comparator), iterator `avl_iter(tree,NULL,key)` allocates a 0x10c-byte cursor (stack of up to 32 `(state,node)` pairs at +0..+0xff, +0x100 top, +0x104 tree, +0x108 key) then `avl_iter(NULL,cursor,0)` returns successive items (in order from `key`) and frees the cursor at the end. Free lists: `avl_spare_node` (reuse a deleted node).

Profiler data model (`prof_ctx` = DAT_00505b64; the profiler is what writes `metrics.log` / "Code Coverage Report"): allocator switch `prof_ctx+0x3500 == 1` -> `prof_malloc` (0x46b150: `FUN_00457e00(n,1)`, on failure sets `prof_ctx+0x34e0 |= 0x10` and `longjmp(prof_jmpbuf)`), else arena at `prof_ctx+0x34e8` (FUN_0043dd70).
- `prof_error(level, fmt, ...)` (0x46b0a0): level 0 fatal (prints `*** MAJOR PROFILING ERROR - SIMULATOR ABORTED ***`, exit(-1)), 1 error + longjmp, 3 -> FUN_0047bdf0, else prints only. Prefix `Error: ` (level < 1) / `Warning: ` (0x4d3ef0/0x4d3ef8).
- File helpers `prof_fopen(name, mode, ext, level)` (0x46b1d0: modes `r`, `a`-like, uses default extension `ext`, searches paths with FUN_00438eb0, `fseek(end)` for append, records file size in `prof_file_size`, error `Failed to open file %s` (0x4d3bb4)), `prof_fread/prof_fwrite` (optional 32-bit byte swap `prof_swap32`; error `Failed to read from file %s` (0x4d3bcc)) - the profile database is stored big-endian words.
- Records: `prof_add_instr(addr, kind, spaceaddr, srcloc)` (0x46b8b0) builds a 0xdc-byte instruction record after calling the device decoder (`cur_dev_ops->+0x18 table +0x3c`) on a 0x284-byte scratch (`prof_instr_scratch`), increments counters at `prof_ctx+0xb0`, `+0xa8`, `+0x3e8+4*kind`, `+0xc8..`, `+0x1ce8/+0x2008/+0x2328` (per class counts), inserts into the address tree `prof_ctx+8`; default source `"{new}"` (0x4d3f04) when no `srcloc {file,line,col,func}`. `prof_find_instr(addr, ref, mode)` (0x46bac0) picks the best record in the tree (mode 0 highest count, 1 same source line, 2 with no source). `prof_add_file(name, kind)` (0x46bcd0: 0x20-byte file record, tree `prof_ctx+0xc`), `prof_add_func` (0x46be10: 0x54-byte function record with 4 sub-lists of sizes 10,10,2,2; id counter `prof_ctx+0x351c`, list at `+0x3514`), `prof_add_line` (0x46b700: 0x18 bytes, tree `prof_ctx+4`), generic list add (`prof_list_add` 0xc bytes), comparators `prof_cmp_ulong`, `prof_cmp_srcloc`, `prof_cmp_name_nocase`, `prof_strnicmp`, `prof_match_word` (skips blanks, case-insensitive prefix), `prof_func_fullname` (0x46b580: `"<file>" + ":" (0x4d32d4) + name`, file names from table `prof_ctx+0x350c`).
Note: the profiler code (this and 0x47b6xx-0x482xxx modules) looks like a separate library statically linked into the simulator; its `prof_error` is also used by the 0x47b..0x483 modules.

## 8. cdbbt - back trace (0x46c000-0x46dfa0)

Frame node (0x1c bytes, allocated with `cdb_malloc(0x1c)`): `+0 text` (`char *`, `"#%-2d p:0x%lx in %.50s ("` (0x4d3fe8) followed by args text and `)`), `+4 pc`, `+8 fp`, `+0xc sp`, `+0x10 saved-register list` (list of 0x14-byte nodes from `cdb_scan_prologue`: `+0..+7 name, +8 stack offset, +0xc register index`, `+0x10 next`), `+0x14 prev`, `+0x18 next`. Doubly linked list on `cur_prog`: `+0x3fac` first, `+0x3fb0` last, `+0x3fb4` current (`cdb_frame_first/last/current`, `cdb_set_frame_current`, `cdb_free_frames`).
`cdb_build_backtrace` (0x46c000): starts from PC (`cur_dev+0x1c`), fp and sp (device hook `cur_dev_ops->+0x1c->+0x14/+0x10` or registers `r2`/`r0` (56100: `0x4b2940`, others `0x4b2948`), `r6` (0x4b2930), `sp` (0x4b2928)), then loops: function of pc via `cdb_func_of_pc`; text uses `cdb_sym_name`, `main`/`???` sentinel (`main` (0x4d3fe0) terminates: loop ends after main), caller pc = `cdb_caller_pc`, caller fp = `cdb_caller_fp`, caller sp = `cdb_caller_sp`. Errors: `unable to read hardware sp` (0x4d4004), `unable to read stack register` (0x4d4020), `unable to read frame register` (0x4d4040), internal error lines 0x25c/0x27e/0x3be.
Arch dispatch (0x2c7 -> *_56100, 0x2c5 -> *_56000, 0x2c6 -> *_96000; a device vtable hook at `cur_dev_ops->+0x1c` overrides): `cdb_caller_pc` (0x46c7f0; reads return address from the software stack or hardware stack `cdb_hwstack_pop` 0x46ca50 which pops ssh/ssl while `sr` bit set; errors `error reading from program memory/memory/software stack`), `cdb_caller_fp` (0x46d100), `cdb_caller_sp` (0x46db40), `cdb_frame_adjust` (0x46d7a0: locals size from the prologue via instruction scanning, opcodes 0x3fdc `move` immediate + 0x3611 (`lua`) etc.), `cdb_count_pushes_*` (counts `push` opcodes `(op & 0xfc1f)==0x3806` or `0x1e6` in the prologue), `cdb_scan_prologue(pc, fp)` (0x46df10 -> per arch scanners 0x46dfa0 (56100), 0x46e1a0 (`0x2c9`), 0x46e3a0 (56000/0x2c8/0x2cb/0x2ca), 0x46e5c0 (96000); the latter three are NOT in my modules) builds the saved-register list with names from the table at 0x492888 (56100: 13 entries of 12 bytes `{opcode, regindex, name}`).
`cdb_frame_refresh_text(frame)` (0x46c590): re-renders args text via `FUN_0046e870(func_sym, pc)` (next group).

## 9. Cross-module interfaces used (functions of other groups, unnamed here)

`FUN_00433f60(dev, name, &block, &idx)` register-name lookup; `FUN_00433f10(dev, block, idx, &val)` / `FUN_00434270` register read/write; `FUN_00457180/457240/457060/457000` memory word read (16/24/32 bit, 2-word variants) and `FUN_004572a0/4570c0` write; `FUN_00457e00/457ed0/457f00` memory manager (malloc/free/realloc; second arg 1 = zero/abort variant); `FUN_0045a8c0`, `FUN_0045d2b0` message display; `FUN_0043d1e0/0043d3a0` console/log line output; `FUN_0046ec60` (C expression parser -> tree), `FUN_0046ecb0` (element iterator for arrays), `FUN_0046f1a0/f3e0/f0f0` (wide integer divide by 10 / float convert); `FUN_00459360/459480/45a860/45a990/45a9c0` number/expression node parse+free; `FUN_00444ad0` (device count check); `FUN_0047f0a0` value/node allocator; `FUN_00441320`.

## 10. Quirks worth reproducing

- `cdb_print_wrapped`: continuation lines are prefixed with `indent` spaces only when `indent < cdb_wrap_width` (`(width <= indent) - 1 & indent`), and breaking happens at the last blank seen before the width; quoted strings are never split.
- `cdb_num_float/double` (`%.15e`): if the third digit from the end of the exponent is '0' the exponent is shifted (`e+007` -> `e+07`), i.e. two-digit exponent output on MSVC.
- `cdb_fmt_pointer` limits strings to 0x400 characters; for other pointer targets prints `space:addr` where space name comes from `cdb_memspace_name`.
- `hio_step` translates host errno to a small simulated errno set (see hio_errno_map); unknown -> -1.
- `parm_tokenize` lower-cases the copy used for keyword matching but keeps the original at +0x100 for expressions; only the first 0xff characters of the line are used (`strncpy(...,0xff)`).
- `cdb_lookup_symbol` caches the last found (depth, symbol) pair in 0x4d4134/0x4d4138 (`-1,-1` initially); behaviour on a miss is to fall back to the second lookup order (globals) - keep it stateless in a port unless outputs differ.
- Unwinding: function name `main` (0x4d3fe0) ends the trace; `???` (0x4d3fdc) is printed when the PC is outside any function; a frame with no debug info still gets a `#n p:0x... in ???` line.

## 11. Open questions

- Exact meaning of the single-letter token classes in `parm_ctx+0x200` (only partially decoded; ranges/pairs `P`, `X`, `S`, `G`); the command table entries (`cmd_tab`, 0x4a8dbc) belong to another group (`->+0x14` validator function pointer).
- Architecture id -> product mapping (0x2c5..0x2cc) is inferred from word sizes; `0x2c8/0x2ca/0x2cb/0x2cc` names uncertain (56300? 56600?).
- `hio_step` request codes 0..7 (state variable `*state`) are only partly mapped to libc calls (open/close/read/write/lseek/unlink/rename/access); needs the target-side library protocol to confirm.
- `prof_add_instr` field layout of the 0xdc record (only +4 addr class, +8, +0xc flags 0x4/0x1000, +0x84.. source, +0xac, +0xb4 count, +0xbc.. seen).
