# SIM56000 group cdb2: cdbeval, cdbcall, cdbglue, misc2, dirs, tail, simmain

Names: `re/names/SIM56000/cdb2.names.txt` (228 functions = all functions of the 7 files, 52 globals).
Confidence column: high = strings/structure prove it, med = behaviour, low = guess.
Machine magics (same as DSPLNK/ASM56000): 0x2c5 DSP56000, 0x2c6 DSP96000, 0x2c7 DSP56100, 0x2c8 DSP56300,
0x2c9 DSP56800, 0x2ca DSP56600, 0x2cb SC100. Global `DAT_00503f44` = current target magic (`cdb_target_magic`);
`*(DAT_00505790+4)` is the same magic read from the device (cdb code sometimes uses one, sometimes the other).

## 0. Real module boundaries (the filemap.txt split is wrong for this group)

| range | real content | filemap name |
|---|---|---|
| 0x43e080-0x43e4f0 | snapshot pointer relocation (save/restore of the device-state heap, `snap_*`) | cdbglue |
| 0x43e4f0-0x43ec80 | `snap_restore` | cdbglue |
| 0x43e9b0-0x43ed?? | WATCH window: `watch_update_all/one`, `watch_display` | cdbglue |
| 0x46e1a0-0x46e870 | prologue scanners (saved regs per target) | cdbeval |
| 0x46e870-0x47a8a0 | cdbeval.c proper: C expression tree evaluator (strings "cdbeval.c" up to 0x47a310) | cdbeval |
| 0x47a900-0x47adf0 + 0x47b110/0x47b400 | host I/O (target `__send`/`__receive`/`F__send`/`_ARTREAD` breakpoints, file I/O emulation) `cdbhost` | cdbeval tail + misc2 head |
| 0x47b670-0x47c2c0 | profiler report output: PostScript writer + listing writer `profps` | misc2 |
| 0x47c2c0-0x47d160 | profiler `; call` directive parsing + call graph building (`profdir`) | dirs |
| 0x47d160-0x47efff | (not mine) NOT COFF loading: `_???_p:$%lx(<-%c:$%lx)` names, call-graph code; filemap "cofload" is really the profiler call graph continuation (cofload.c in mod/) | cofload |
| 0x47f090-0x47fb30 | yacc parser for C expressions: `yyparse` + node allocator (`cdbparse`) | cdbcall |
| 0x4804c0-0x481d3f | parser support + flex-style lexer (`cdblex`) | tail |
| 0x481d50-0x4833fa | profiler subroutine dependency tree / call graph PostScript output + graph layout (`profgraph`) | tail |

So the "cdb" C debugger is: lexer (0x480cb0/0x4819e0) -> yacc parser (0x47f240) building an expression tree
of `node` structs while type-checking each node as it is built (`mk_*_node` calls the `eval_*` function with
`do_eval=0`) -> `eval_tree` (0x46ec10) evaluating the tree (`do_eval=1`). Errors go through `FUN_0045f160(msg)`
(set C-eval error message, cdbutil), `FUN_0045f1b0(msg)` (same, other flavour), `FUN_0045f1f0(file,line)` and
`FUN_0045d280` (warning). The internal-error form `FUN_0045f1f0(0x4d413c /*"cdbeval.c"*/, line)` carries the
original `__LINE__` (e.g. 0x3f1, 0x480, 0xdc0, 0x1c57, 0x1d53, 0x1e1b ...): the original file is ~8000 lines.
Entry point used by the rest of the simulator: `parse_c_expression(text)` 0x46ec60 (returns root node, 0 on
error) then `eval_tree(root)` 0x46ec10 (1 ok / 0 error / 2 for a call node), result value in `root->value`.
The C expression must be wrapped in braces: `lex_init` (0x481220) requires text starting with `{` and ending
with `}` ("empty C expression"/"incomplete C expression"), matching the `${c_expression$}` syntax of EVALUATE/TYPE.

## 1. Structs

### node (0x1c bytes, malloc(0x1c) in `new_node` 0x47f0a0, +0x40-byte value block)
| off | field | evidence |
|---|---|---|
| +0x00 | left child (node*) | `mk_binary_node`, `eval_binary(&node->l, &node->r ...)` |
| +0x04 | middle child (node*), the operand of unary ops, the function of a call, the "then" of ?: | `mk_unary_node` sets [1]; `mk_call_node` sets [1]=func |
| +0x08 | right child | `mk_binary_node` |
| +0x0c | op: 0 = leaf, char ops as themselves ('*'=0x2a ...), or yacc token >= 0x123 (see table) | `eval_node` 0x4703c0 |
| +0x10 | value* (malloc 0x40, see below) | `*(node+0x10)` everywhere |
| +0x14 | arg list (call nodes; list cell = {node*, next}, 8 bytes) | `mk_call_node`, `push_args_*` |
| +0x18 | flag: 1 = already evaluated/constant | `eval_tree_core`, `tree_mark_leaves` |

`new_node` also records every allocated node in the list `node_alloc_list` (0x5046ac; cell = {node*, next}, 8 bytes) so that
`parse_free_all` (on parse failure) or `parse_free_keep_nodes` can free them (`free_node_list(plist, free_contents)`).
The evaluator functions take *pointers to child slots* (`node **`), because `coerce_array_func` may replace a child
by an implicit-address node (op 0x148 array, 0x149 function) and `usual_arith_conv`/`integral_promote`
wrap children in cast nodes (op 0x13f, `make_cast_node`) in place.

Op codes (yacc tokens, from `eval_unary`/`eval_binary`/`yyparse`): char ops ('*' 0x2a, '+' 0x2b, '-' 0x2d, '.'
0x2e, '/' 0x2f, '<' 0x3c, '=' 0x3d, '>' 0x3e, '^' 0x5e, '|' 0x7c, '~' 0x7e, '&' 0x26, '%' 0x25, '!' 0x21, '#' 0x23);
0x123 `?:`; 0x124 `*=`; 0x125 `/=`; 0x126 `%=`; 0x127 `+=`; 0x128 `-=`; 0x129 `&=`; 0x12a `^=`; 0x12b `|=`; 0x12c
`<<=`; 0x12d `>>=`; 0x12e `||`; 0x12f `&&`; 0x130 `==`; 0x131 `!=`; 0x132 `<=`; 0x133 `>=`; 0x134 `<<`;
0x135 `>>`; 0x138 `sizeof`; 0x139 `->`; 0x13b int const; 0x13c char const; 0x13d float const; 0x13e symbol;
0x10f typedef name token; 0x13f cast; 0x140/0x141/0x142/0x143 pre/post ++/-- (yacc rules 0x3a-0x3c map them);
0x144 `[]`; 0x145 function call; 0x146 `,`; 0x148 array->pointer; 0x149 function->pointer. (Exact 0x140..0x143
order pre/post is per `eval_incdec` strings "post-decrement/pre-decrement/post-increment/pre-increment".)

### value (0x40 bytes = 16 dwords, copied wholesale with `rep movsd`)
| off | field |
|---|---|
| +0x00 | double d (host double; used for float/double kinds and as scratch) |
| +0x08 | float f (single) |
| +0x0c | word0 (24- or 32-bit word; low word of an integer; for DSP float: exponent) |
| +0x10 | word1 (mid word; for DSP float: mantissa; for pointers/lvalues: space id in +0x1c) |
| +0x14 | word2 (high word of 3-word 56-bit/72-bit integers) |
| +0x18 | lvalue address (word) when storage class is memory |
| +0x1c | lvalue memory space (X/Y/P/L..., from `FUN_00465620`) |
| +0x20 | **kind** (type code, see below); modifier pairs in bits 4-5 |
| +0x24 | storage class: 0 rvalue, 1 symbol/lazy (load via `FUN_0045f390`), 2/3 memory lvalue (+0x18/+0x1c), 9 register?, 0x12 member/struct offset base |
| +0x28 | aux: struct/union tag index, or symbol-table index for functions/typedefs; `type_size` reads `value[+0x28]` as the tag for kinds 8/9 |
| +0x2c..+0x38 | four array dimensions (dim1..dim4; 1 = none) |
| +0x3c | short: 1 = value is a symbolic/lazy lvalue, needs `FUN_0045efe0` (value load) before use |

Kind encoding: low 4 bits basic type: 1 void, 2 char, 3 short, 4 int, 5 long, 6 float, 7 double, 8 struct, 9 union,
0xa/0xb (int-like, sizes as int; enum/bitfield/short-fract?), 0xc uchar, 0xd ushort, 0xe uint, 0xf ulong;
bits 4-5: 0x10 pointer, 0x20 function, 0x30 array; further derived-type levels are stacked by shifting the
kind right by 2 (`kind = base | (kind & ~0x1000f) << 2`, e.g. `make_func_ptr_node`: `(k & 0x1000f) | ((k & ~..|4)<<2)`).
0x10000-0x10005: DSP fractional types (0x10000/1 fract16/short fract, 0x10002/3 long fract, 0x10004 accum/2-word, 0x10005 3-word).
`DAT_00503f44` decides sizes (`type_size` 0x46ecb0: int=1 word on 24-bit targets, 2 words on 56100/56800, 4 on SC100...).
Usual conversion order in `usual_arith_conv`: 0x10005 > 0x10004 > 0x10003 > ... > double > float > ulong > long > uint > int.

### saved-register node (0x14 bytes, `scan_saved_regs_*`)
`char name[8]` (register name copied from the opcode table), +0x08 int stack slot offset, +0x0c int register code, +0x10 next.
Opcode tables (12-byte entries {key, code, name*}, searched by `opcode_tab_search`): 0x492888 (13, 56100), 0x492928 (13, 56800),
0x4929c8 (36, 56000 family), 0x492b78 (348, 96000).

### parser globals / yacc
`yyparse` 0x47f240 is byacc/yacc output (stack depth 0x96=150, two 600-byte stacks `yy_state_stack`/`yy_val_stack`
allocated with malloc; grows with realloc "yacc stack overflow"). Semantic actions (`switch` on rule number 1..0x62):
rules 6/9/0xc/... -> `mk_binary_node(lhs, op, rhs)` (assignment ops), 0x12 `mk_ternary_node`, 0x14/0x16 `||` `&&`,
0x18/0x1a `|` `^`, 0x3a-0x3c unary ops via `mk_unary_node`, 0x3e `[]` (0x144), 0x3f/0x40 `mk_call_node` (+ the check
`dummy_call` symbol present in target program: "command-line function calls aren't supported in your crt0 file"),
0x41/0x42 `mk_member_dot/arrow`, 0x43/0x44 pre/post ++/-- ... 0x45 int const... Type-name grammar (rules 0x50-0x62)
produces `mk_type_node(kind)`; errors "two or more data types in cast", "There is no struct or union named %s",
"there is no enumeration called %s".

## 2. Functions by module

### simmain
* 0x401000 `main`: `FUN_00439000()` (init), `FUN_00435d40(0,"56001")` (default device), banner via `FUN_0043d3a0`,
  argv[1] handed to `FUN_0043b5a0(0, argv[1])`; then the endless scheduler: pick the next device whose `+0x40` (run state) is 0, read a command line
  (`FUN_00439410` cmd editor, or `FUN_0043a470` when `DAT_004a91dc` (macro/redirect input) is set) and execute it (`FUN_0043b5a0`);
  after each command, for every device with `(state+0x44)&0x20 == 0` call `FUN_00438a30(dev)` (run/step). Never returns (quit calls exit).

### cdbglue (real content: snapshot relocation + watch)
* 0x43e080 `snap_reloc_add(unsigned long *slot, int kind)`: for a pointer stored in device-state memory, find which heap block holds it
  and which block it points into (`snap_find_block`), append 16-byte record {slot_block, slot_off, target_block, target_off} to list `snap_reloc_list` (0x502068),
  then recurse into the pointed struct by `kind` (1 = the whole device struct: registers, memory blocks 0x3510/0x350c arrays of `*(dev+0x3508)` entries...).
  Used when saving the complete simulator state to a binary snapshot (kinds 2..0xb are struct layouts: pointer-to-block, linked list nodes, ...).
* 0x43e4a0 `snap_find_block(addr, out[2])`: walks the block list `*(dev+0x34e8)` (each 0x14 bytes: +0 size, +4 kind, +8 start, +0xc end, +0x10 next; count `*(dev+0x34fc)`), returns 1 and {index, offset}.
* 0x43e4f0 `snap_restore(filename, ?, reopen)`: setjmp-protected; reads the 0x3aac-byte header into `sim+0x188`, the block descriptors, the relocation table and patches all pointers (`block_base[i] + off`); `filename==0` just fcloses `snap_file`.
  Sets `dev = sim+0x490` (`DAT_00505b64`). Uses `FUN_0046b1d0` (fopen wrapper), `FUN_0046b510` (fread wrapper), `FUN_0046b150` (alloc).
* 0x43e9b0 `watch_update_all`: iterate the watch list `*(sim+0x3fa8)` (link at +0x120) calling `watch_display`.
* 0x43ec80 `watch_update_one(dev, n)`: `FUN_0043cb40(dev,n)` finds watch n; display it.
* 0x43eca0 `watch_display(watch)`: formats `"%d: %s: %s"` -> "#n: <kind letter>: <text>" (kind letters at 0x4b29b0/0x4c6ab4/ab0/aa8/aac by radix +0x108), pads to 0x28 columns, evaluates the watch (kind +0x104: 0 = C expression `FUN_0046ec10`
  with scope check `FUN_00465750`(else "Expression out of scope"; failure "Error evaluating C expression"), 1 = register (`FUN_0043bec0`), 2/3 = memory (`FUN_0043f010`)), appends to the growing buffer `watch_line_buf`, prints with `FUN_0045fbc0(buf,0,0,0x28,0)`.
  **watch struct** (0x124+ bytes): +0 number, +4 text[0x100], +0x104 kind, +0x108 radix, +0x114 root node, +0x118/+0x11c scope, +0x120 next.

### cdbeval (0x46e1a0..0x47a8a0)
* `scan_saved_regs_56800/56000/96000` (0x46e1a0/0x46e3a0/0x46e5c0; 56100 is 0x46dfa0 in cdbbt, dispatcher `FUN_0046df10`): given a function address, walk its instructions
  (reading program memory `FUN_00457180(mem,space0,addr,&word)`, error "error reading from program memory") from the function symbol to the next symbol,
  recognise prologue push/move instructions by table and produce the list of saved registers with stack offsets (used by backtrace/frame). 0x3fdc/0x3611/0x76f400/0x22d000/0x204e00 etc. are target opcodes (`move`/`adjust sp` patterns).
* 0x46e870 `frame_locals_string(func_symidx, base)`: builds a "name=value, ..." string for the automatic variables of a frame (COFF symbol table entries 0x20 bytes: +0x18 storage class (9 auto, 0x11/0x13 reg/arg, 0x64/0x65 block/func end), +0x14 type), into growing buffer `frame_locals_buf` (0x503f40/size 0x4d3f94).
* `parse_c_expression`, `eval_tree`, `eval_tree_core` (worklist evaluation using cdbutil stack `FUN_0045ff30/00/50`: `&&`, `||`, `?:` evaluate lazily, marking skipped subtrees done), `eval_node` (dispatch unary/binary/ternary by which children are present), `tree_mark_leaves`.
* `eval_unary/eval_binary/eval_ternary` are the operator dispatchers (op switch) and are used for both type checking (`do_eval=0`) and evaluation; each `eval_<op>` prints the exact error strings, e.g. `eval_addr_of`: "operand of unary & invalid"/"...since it is in a register", `eval_deref` "operand of unary * invalid",
  `eval_sizeof`, `eval_call` "attempting function call on non-function object"/"attempting to pass void value to function as argument", `eval_assign` (struct/union assignment checks), the compound assignment families, `eval_incdec`.
* value operations (`*_values(a, b, out)`) implement each operator on the kind combinations; DSP arithmetic is done on 2/3 word integers with the helpers `dw_*` (two word add/neg/shl/shr/cmp; family without suffix carries via `word_bits` shift, `_b` variant via compare) driven by globals `cdb_word_mask` (0xffffff on 24-bit targets), `cdb_word_bits` (24), `cdb_sign_bit` (0x800000), etc.
* Division checks: "attempt to divide by 0" / "attempt to divide by 0.0" / "attempt to perform modulus by 0".
* Casts: `eval_cast` ("cannot cast from pointer to float", "cannot cast from float to pointer", "conversion of non-scalar to scalar requested", "conversion to non-scalar type attempted") + `cast_value` dispatch on target kind; conversions between host doubles and the DSP float/fixed formats (`value_dsp_to_double`, `double_to_fract_words`, ...).
* Function calls in the target: `call_target_function` (0x478d50) dispatch per magic: 56000 -> 0x478ea0, 56100 -> 0x479210, 56800 -> 0x479550, 56300/56600/SC100 -> 0x479890, 96000 -> 0x479bd0.
  Each: finds the register names (r6/r0/r2/pc, `sp`, from tables 0x4b2930 etc. via `FUN_00433f60`), reads/writes them (`FUN_00433f10/00434270`, errors "unable to read/write register r6/r0/r2/a1/pc", "unable to write memory"),
  pushes the arguments on the target stack (`push_args_*`, using `type_size` for the words per arg), stores the return address = address of the target function `dummy_call` (symbol looked up with `FUN_00440730("dummy_call")`), sets the pc to the callee, then `call_setup_run` starts the device running until it returns to `dummy_call`.
* Helpers for the parser: `usual_arith_conv`, `integral_promote`, `make_cast_node`, `clone_tree`/`clone_arglist` (deep copies, used for compound assignments `a op= b` -> `a = a op b`).

### cdbhost (0x47a900..0x47b40f) — target host-I/O emulation ("F__send/F__receive" in SC100, `__send/__receive` others, `putchar`+`_ARTREAD` on 56800)
* `host_io_init` looks up the breakpoint symbols per target (`putchar`/`_ARTREAD` 56800, `F__send`/`F__receive` SC100, `__send`/`__receive` others), stores their addresses in `sim+0x4070/0x4078`, `host_io_mode_var` 3/2/4/1 by target.
* `host_io_service` (0x47adf0): called when a breakpoint at these addresses is hit: for send, reads the buffer from target memory (`FUN_0047b110` = get arg/return-address via the stack, `FUN_0047b400` = 2nd), writes it with `host_write`; for receive reads via `host_read` and stores into target memory, "Error reading memory"/"Error writing memory".
* Host file table: `*(sim+0x4080)` array of 16-byte entries {crt fd, path copy, oflag, pmode}, count `sim+0x4088`, next-free `sim+0x4084`; fds 0/1/2 map to redirect streams (`sim+0x408c`/`0x4098`). `host_open/close/read/write/lseek` wrap `_open/_close/_read/_write/_lseek` (CRT `FUN_004899a0` is `_open`).

### profps (0x47b670..0x47c2c0) — profiler report writer
* `prof_out_open(objname, basename, ext)`: opens `<basename><ext>` as PostScript file `ps_file` (`%!PS-Adobe-1.0 %%PageOrder: Ascend` prolog at 0x4d4f84 with `/TM 770 def /BM 0 def /LM 25 def /RM 612 def`, defines `nf sh sc da li rv rc ia cp ra ar ...`) and the text listing `lst_file` (`stdout`-like when no name), computes date string (`time`+`ctime`, `prof_date_str`), version string ("Version x.y.z"), object name (basename after last `\`, "(scratch)" if none; warning "No object file loaded").
  Font names table `ps_font_names` (0x4d4ef0..0x4d4f0c: `Times_Italic`, `Helvetica_Oblique`, `Helvetica`...) with `_` converted to `-`.
* `ps_font(op, a, b)`: font stack machine (op 0/1/2 push, 3 set, 4 size-only, 5 re-set, 6 pop, 7 restore) emitting `/%s %d nf`.
* `ps_putc(c)`: buffer a line, handles \t (8 spaces), \n (new line, page after 0x3f lines), \f, escaping `( ) \`, emits `(...) sh`; `ps_flush_line`, `ps_new_page` ("%%Page: %d", header "Motorola Profiler ... Page n").
* `prof_printf(fmt, ...)` 0x47bdf0: vsprintf into `prof_fmt_buf` (0x503fc8) then interprets embedded control bytes (0x80/0x81/0x82 stream selectors: 0x80 = listing only, 0x81 = both?, 0x82 = PS only; 0x83 ... 0x83 = escape sequences: `C<n>` change column (`%d sc`), `N<spec>` number formatting via `prof_put_number`, `<ch><cnt>` repeat char); `lst_write_buf` (in dirs) writes the same to the listing with the "Motorola Profiler ... Page %d" heading every 0x3b lines.
* `prof_put_number`: field of width digit + '.' spec: prints fixed or `%de%d` exponent form for big/small values (fits column width).

### profdir (0x47c2c0..0x47d15f) — profiler call-graph directives and graph model
* `prof_parse_call_directive(line, text)`: scan the source comment for `call ...` directive (`prof_scan_call_directive` looks for a 3-char marker at 0x4d55c8 then `ignore`, `return`, `enter <name>[,]`, `<name2>` joint_ret), sets bits in `line+0xd8` (1 ignore, 2 return, 4 enter, 0x10 call, 8, 0x20 joint_ret), records names (call target/enter name up to 23 chars via `prof_scan_identifier`), errors "File %s, line %d: Directive %s not allowed here" (`'call'`), "File %s, line %d: Invalid directive". Uses the source-file object vtable `*(DAT_00505794+0x18)` slots 0x28/0x2c/0x30.
* Call graph model (in `dev+0x34e0..0x3798`): nodes (0x54+ bytes: +4 name, +8 callee-of list, +0xc, +0x10 callers/edges lists, +0x14 callees list, +0x18 flags (4, 8, 0x10, 0x20, 0x40), +0x1c/0x20/0x24/0x28 cycle/instruction/call counters, +0x2c mark, ...), edge cells {node, count, ...}. `cg_lookup_name(name,type)` = hash lookup (`FUN_0046bd40`), created with `FUN_0046be10`; `cg_note_pc_change` is called by the run loop on every executed pc change with a source line; `cg_push_call` maintains the call stack (0x1c-byte records at `dev+0x3520+i*0x1c`, depth `dev+0x3788` limit 0x15) and accumulates cycles; `cg_make_mother` builds the synthetic `__MOTHER__` root; `cg_merge_nodes/edges` merge recursive cycles.

### cdbcall / cdbparse (0x47f090..0x47fb30)
`parse_get_root`, `new_node`, `parse_free_all/keep`, `free_node_list`, `yyparse` (see §1).

### tail: cdblex (0x4804c0..0x481d3f)
* `yyerror` prints "%s near %s" using `yytext_buf`, or "premature end of C expression". `mk_*_node` build and type-check nodes (a node whose type-check fails returns 0). `mk_member_dot/arrow` ("`%s' is not a member of the %s" structure/union, "requesting member `%s' in item that is not structure or union", "attempting to use -> operator on item that is not pointer") resolve members through `FUN_00465430`.
* `yylex` 0x480cb0: token classes from the generated scanner `yy_scan` 0x4819e0 (lex tables at 0x4d6fe8/0x4d7520/0x4d78e8...; 0x33 states): 1 hex const ->0x13b, 2 octal, 3 decimal, 4 float ->0x13d ("float constant exceeds range"), 5 char const ->0x13c, 7 identifier (keyword table 34 entries at 0x4d6cc0 via `keyword_lookup`, else typedef name (`lex_typedef_name` via `FUN_004654c0`) -> 0x10f/0x13e symbol (`FUN_004654d0`), else error), operators -> tokens above. Int constants (`lex_int_const`) accumulate into two words with the target's word mask, suffix l/u picks kind 4/5/0xe/0xf.

### profgraph (0x481d50..0x4833fa)
Text dependency tree (`cg_print_tree_text` -> "Subroutine Dependency Graph", ASCII tree using `|`, `+` prefixes at 0x4d7a80..0x4d7aa8), PostScript call tree (`cg_ps_call_tree`, "Subroutine call tree start/end", `%d %d %d %d li`/`rv`/`rc`/`ia` commands) and call graph (`cg_ps_call_graph`: "Subroutine Dynamic Call Graph", "( : Sorry - Graph too Big)" when a node's cell counts exceed 100; layout in `cgl_*` = a small planar layout searching (with `rand`-based jitter) for shapes, then `cg_ps_graph_node` `cp` and `cg_ps_graph_arrow` `ar`/`ra` with a quadratic solve (`sqrt`) for arrow positions).

## 3. Cross-module interfaces used (not mine, addresses)
0x45efe0 value_load (fetch lvalue contents; 0 on error), 0x45f090 value_store, 0x45f160/0x45f1b0 set_error(msg), 0x45f1f0 internal_error(file,line), 0x45d280 warn, 0x45f230/0x45f240/0x45f260 cdb alloc/realloc/free, 0x45f390 symbol_addr, 0x45f2f0 value_to_string(value, radix), 0x45ff30/0x45ff00/0x45ff50 eval work stack, 0x465620 default memory space, 0x465a00/0x465b80 function start/end symbol index, 0x465110 struct size, 0x465170 types_compatible, 0x465430 member lookup, 0x4654c0/0x4654d0 typedef/symbol lookup,
0x433f60 register lookup by name, 0x433f10 register read, 0x434270 register write, 0x457000/0x457180 memory write/read (dspmem, space, addr, &word), 0x46a7d0/0x46aa90/0x46ac60/0x46aec0 list insert/remove/find/iterate, 0x46bd40/0x46be10 hash find/create.

## 4. Quirks
* All C-expression semantics use the *target's* word width; the same evaluator handles 24-bit (56000/56300/96000) and 16/32-bit (56100/56800/SC100) words via masks (`cdb_word_mask`).
* Internal-error line numbers (arg 2 of `FUN_0045f1f0`) identify original `cdbeval.c` source lines.
* Error message strings live at 0x4d4148 (divide), 0x4d406c ("error reading from program memory"), 0x4d413c ("cdbeval.c"), 0x4d33f0 ("unable to write memory") - they must be reproduced byte for byte.
* yacc/lex tables at 0x4d6fe8-0x4d7970 must be copied verbatim (or the grammar regenerated identically).

## 5. Open questions
* Exact meaning of value kinds 0xa/0xb and storage-class values 1/3/9 in `+0x24`.
* Precise field layout of the call-graph node (0x54 bytes?) — only the accessed offsets are listed.
* `snap_*` kinds 3,4,6,7,10,11 struct layouts (offsets in the code of `snap_reloc_add`).
* `cgl_*` layout algorithm details (low confidence names).
