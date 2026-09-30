# l4_util - DSPLNK.EXE, address range 0042c8ba - 0043bc4e (271 functions)

Assigned as "util.c" (271 functions, 0x42c8ba-0x43a40d start addresses, body running to
0x43bc4e = end of user code before the CRT at 0x43c2d0). The vote in `modules.txt` tags every
one of these 271 functions `util` because they are the last group before the CRT and reference
no data closer to another module's `$Id` string - see "Module boundaries" below for what this
actually means.

## Module boundaries (corrected, with evidence)

`modules.txt`'s vote is data-proximity based (nearest `$Id`-owned global referenced) and DSPLNK
has only 15 `$Id` strings total (dsplnk, arith, error, eval, fixup, func, input, lib, lnkglb,
map, memctl, object, sdi, symtab, util - see `re/out/DSPLNK/strings.txt:46-680`). `util.c`
(`$Id: util.c,v 1.21 1997/07/30 22:07:06 lauren`, at data address 0x45aa40) is the *last*
module, so anything after it in `.data`/`.bss` that isn't clearly owned by an earlier module
defaults to "util" even when it isn't hand-written util.c code. Within the assigned range there
are, by content, at least four distinguishable pieces:

1. **0x42c8ba - 0x42d950** (20 functions) - the linker's own global/local **symbol-table hash
   tables** (`ext_lookup`/`ext_add`/`sym_lookup`/`sym_dedup_locals`/`sym_remove`/the various
   `*_free_all` sweepers). This is plausibly genuine util.c: ASM56000's util.c also owns
   `sym_free_all`/`ext_free_all`/`sym_free_local_blocks`/`strtab_free` (see
   `re/names/ASM56000/g2_symtab.names.txt:73-75`) even though *lookup* lives in symtab.c there.
   DSPLNK's linker-specific 2003-bucket (`0x7d3`) hash tables at `&DAT_00461ff8` (global
   externs) and `&DAT_00465e98` (per-module locals) are almost certainly declared and managed
   in util.c, just with lookup folded in here rather than kept in symtab.c. Medium confidence.
2. **0x42e170 - 0x430b53** (~65 functions) - **genuine, ASM56000-parallel util.c**: `xmalloc`/
   `xrealloc`/`xfree`/`tab_search`/`sort_ptrs`/`sort_swap`/`hash_name`/`base_name`/`get_string`/
   `get_symbol`/`get_mem_spec`/the `mem_space_*`/`char_to_*`/`emi_map` family/`str_upper`/
   `str_lower`/`set_file_buffer`/`merge_mem_space`/`fmt_double`/`fwrite_swapped`/`obj_fwrite*`/
   `swap_words`/`tm_to_secs`. 12 of these are **byte-identical** to ASM56000 functions per
   `re/out/DSPLNK/xmatch_ASM56000.txt` (xmalloc, xrealloc, tab_search, sort_swap, char_to_counter,
   str_upper, str_lower, set_file_buffer, fmt_double, swap_words, tm_to_secs, round_up_pow2)
   and the rest share names/strings/signatures with `re/names/ASM56000/g2_symtab.names.txt`'s
   `util` rows. High confidence this is the real util.c.
3. **0x430b53 - 0x433298** (~35 functions) - a **COFF -> ELF object-file converter**
   (`coff_to_elf`, `elf_init`, `elf_build_header`, `read_coff_headers`, `read_coff_strtab`,
   `read_coff_sections`, `coff_strtab_name`, the `elf_*`/`sec_list_add`/`record_*` helpers).
   Reads a DSPLNK-produced COFF file and re-emits a big-endian ELF32 file (magic strings
   `.shstrtab`, `.strtab`, `.note`, `.symtab`; header fields `ELFCLASS32`/`ELFDATA2MSB`/
   `ET_EXEC`/`e_machine=2` built explicitly at 0x432261). ASM56000 has no counterpart to this
   at all (the assembler never reads/writes COFF/ELF). This is DSPLNK-only code, most likely
   linked from util.c (no closer `$Id`) but conceptually a separate "coff2elf" facility.
   Medium confidence on the boundary; the individual functions are behaviourally clear.
4. **0x433620 - 0x43bc4e** (~150 functions) - a self-contained **"ABI expression language"**
   subsystem: 4 instantiations of a generic `InfArray` container (48 functions, see below), the
   `abi_func_*`/`abi_lnk_*`/`abi_mp_sym_*`/`op_*` runtime library, a field-bit-packing engine
   (`abi_mask_then_shift`, ~40 named "F#W#[O#]" pack routines), and a **Flex-generated lexer**
   (`yylex` and friends, confirmed by the literal strings `"fatal flex scanner internal
   error..."`, `"out of dynamic memory in yy_create_buffer()"`, etc.) plus a **Bison/Yacc-
   generated parser** (`yyparse` at 0x43a40d, confirmed by the literal strings `"yacc stack
   overflow"` and `"syntax error"`). Flex/Bison output files carry no Motorola `$Id` (they are
   machine-generated, e.g. from an `abi.l`/`abi.y` grammar), which is exactly why the vote
   heuristic has nothing better to attribute them to than the preceding util.c. This is almost
   certainly its own source module (something like `abi.c` + generated `lex.yy.c`/`y.tab.c`),
   not hand-written util.c. High confidence this is *not* util.c in the literal source-file
   sense, even though it is compiled into the same address run.

**Net**: only clusters 1-2 (roughly 0x42c8ba-0x430b53, ~85 functions) should be considered
"util.c" when translating to `src/dsplnk/util.c`; clusters 3 and 4 are better split into their
own reconstructed source files (e.g. `src/dsplnk/coff2elf.c` and `src/dsplnk/abi.c` +
generated lexer/parser) even though this naming pass files all 271 under group `util` as
instructed by the brief.

## What the "ABI expression language" is for

DSPLNK reads small textual "ABI" (Application Binary Interface) expressions - most likely from
a linker-control/map-description file or from `-abi`-style command-line text - that describe how
to extract, convert, range-check and bit-pack values (symbol addresses, sizes) into an output
image. The grammar supports: integer/64-bit arithmetic (`+ - * / % << >> & | ^ ~ ! - ==  !=
< <= > >= ?:`), assignment and compound assignment (`=`,	 and others reported through
`abi_assign_op`/"Not A Recognized Assign Operator!"), and calls to built-in functions
`abi_func_sym()`, `abi_func_pack()`, `abi_func_check()`, `abi_func_memcheck()`,
`abi_lnk_extract_val()`, `abi_lnk_convert_type()` (all of which embed their own name as a string
literal for error messages - e.g. `re/out/DSPLNK/strings.txt:1: "abi_func_pack" [ FUN_00437fc0
]`). Its entry point is `abi_expr_eval` (0x43a260) -> `abi_expr_eval_impl` (0x43a289), called
from elsewhere in DSPLNK (callers 0x416cf8/0x410668, outside this module); the only call into
this subsystem directly from `main()` is `abi_free_all` (0x43a394, caller 0x402e52).

## Generic "InfArray" container API

Referenced by four sets of assert()/error strings naming their source files (from
`re/out/DSPLNK/strings.txt:730-785`): `LONGInfArray.c`, `symtableInfArray.c`,
`ABI_mp_symtblInfArray.c`, `formtableInfArray.c`. Each instantiation is a hand-duplicated
(copy-pasted, not templated - the four bodies are near byte-identical, with the constant string
substituted) 12-function API over a growable array-of-elements structure:

| role | LONG (`longarr`) | symtable (`symtblarr`) | ABI_mp_symtbl (`abimparr`) | formtable (`formarr`) |
|---|---|---|---|---|
| destroy   | 0x433620 | 0x433d00 | 0x434550 | 0x434e80 |
| create    | 0x43364a | 0x433d2a | 0x43457a | 0x434eaa |
| dump      | 0x43374a | 0x433e2a | 0x43467a | 0x434faa |
| free_storage | 0x4337cc | 0x433eac | 0x4346fc | 0x43502c |
| compact   | 0x43386c | 0x433f4c | 0x43479c | 0x4350cc |
| grow      | 0x4338b8 | 0x433f98 | 0x4347e8 | 0x435118 |
| append    | 0x433a50 | 0x434130 | 0x434980 | 0x4352b0 |
| insert    | 0x433ab6 | 0x434196 | 0x4349e6 | 0x435316 |
| get (bounds-checked) | 0x433b02 | 0x4341e2 | 0x434a32 | 0x435362 |
| is_empty  | 0x433b3b | 0x43421b | 0x434a6b | 0x43539b |
| is_full   | 0x433b6a | 0x43424a | 0x434a9a | 0x4353ca |
| count     | 0x433b99 | 0x434279 | 0x434ac9 | 0x4353f9 |

Inferred struct layout of the array header (from the `create`/`grow`/`dump`/`get` bodies):

```
struct InfArray {                 /* size not directly observed; header only */
    void  *array;         /* +0x00  malloc'd element storage                */
    long   array_size;    /* dumped as "1. array_size"  - allocated capacity */
    long   blocksz;       /* dumped as "2. blocksz"     - growth increment   */
    long   max_index;     /*  dumped as "3. max_index"  - highest valid idx  */
    long   last_index;    /*  dumped as "4. last_index" - last used idx      */
    long   remove_flag;   /*  dumped as "5. remove"                         */
    ...                           /* element-type-specific accessor/compare fns beyond this */
};
```

- `create(init_sz, blocksz)` asserts `(init_sz>=0)&&(blocksz>=0)` (string quoted verbatim in the
  binary), xmallocs the header, and calls `grow()` for the initial allocation.
- `grow()` is the real allocation primitive: `malloc` if the array pointer is still NULL, else
  `realloc`, then `memset`s the newly added tail to 0; on failure it `fprintf`s "Cannot alloc
  array\n" (with the InfArray-type filename string) to stderr and `exit()`s - **not recoverable**,
  unlike `xmalloc`/`xrealloc` which the InfArray family does *not* go through directly (it calls
  the C library `malloc`/`realloc` itself, see 0x4338b8 etc.) This is a quirk worth reproducing:
  InfArray OOM behaviour differs from the rest of util.c's `xmalloc` OOM behaviour (different
  message, no "link aborted" text, straight `exit(1)`-equivalent).
- `get(idx)` asserts `(index>=0) && (index <= arr->max_index)` (string quoted verbatim).
- `dump()` prints the 6-line "Dumping Array Information" block to stdout via `printf` (not
  `fprintf(stderr,...)` like everything else in this module) - purely a debug/trace aid, never
  seen called from any of the 271 functions in this range (dead in normal builds, presumably
  invoked only under a debug flag or from a debugger).
- `symtblarr`/`formarr`/`abimparr` (but not `longarr`) additionally get a companion linear
  "find by name" search function outside the 12-function template
  (`symtbl_find_by_name` 0x43447d, `form_find_by_name` 0x4355d6, `abi_mp_sym_find` 0x434d4d) that
  walks every element via the array's own accessor (a function-pointer slot at header+0x20,
  never resolved by Ghidra - `(**(code **)(param_1+0x20))(param_1,i)`), i.e. **the header
  carries a vtable-style accessor pointer beyond the fields dumped above**; exact offset of that
  slot within the header was not fully mapped (evidenced only through the +0x20 call site).
- `ABI_mp_symtbl` elements are themselves 0x18 (24) bytes: `{char *name; long unused;
  long v1; long v2; long v3;}` built by `abi_mp_sym_alloc` (0x434435, `xmalloc(0x18)+strdup`);
  some are instead built by `abi_mp_sym_build` (0x434c8f) which nests a **whole separate
  `longarr` inside the entry** (name = an "%#0lx" hex string, value = a `longarr` of related
  numbers) - i.e. `ABI_mp_symtblInfArray` is used both as a flat symbol table and, in at least
  one place, as a two-level table keyed by address. Two different element-destructors exist
  accordingly: `abi_mp_sym_free_elem` (0x4343e0, frees a plain element, plus a secondary owned
  pointer if type-tag==4) and `abi_mp_sym_free_with_arr` (0x434c30, frees name + destroys the
  nested `longarr`).
- `formtable` elements are 2 fields: `{char *name; void (*fn)();}` built by `form_define`
  (0x43559d) and freed by `form_elem_free` (0x435560); `fn` is one of the ~40
  `abi_pack_NN` field-format routines registered by `abi_form_table_init` (0x436210).

## Field-bit-packing engine

`abi_mask_then_shift` (0x435f5a) and `abi_bit_range_mask` (0x435f9f) are the two shared
primitives. `abi_bit_range_mask(lo,hi)` builds a `[lo,hi]` bit mask; `abi_mask_then_shift(v,
mask, pos, dir)` masks `v` then shifts it by `pos` bits in direction `dir` (`'<'` or `'>'`,
reporting `"abi_mask_then_shift shift_direction error"` for anything else). `abi_form_table_init`
(0x436210, 1605 bytes) registers ~40 named format codes - literal strings `F11W1`, `F11W2`,
`F11W3`, `F13W1`, `F13W2`, `F14W1`, `F14W2`, `F12W1`, `F10W1`, `F10W2`, `F9W2O1`, `F9W2O2`,
`F5W1O1`, `F5W1O2`, `F5W2O2`, `F5W3O1`, `F4W1O1`, `F4W1O2`, `F4W2O2`, `F4W3O1`, `F6W1O1`,
`F6W1O2`, `F6W2O2`, `F6W3O1`, `F16W1O1`, `F16W1O2`, `F16W2O1`, `F18W1O1`, `F18W1O2`, `F18W2O1`,
`F23W1`, `F17W1O1`, `F17W1O2`, `F17W2O1`, `F20W1`, `F21W1`, `F19W1`, `F19W2`, `F22W1`, `F22W2`,
`F15W1` (read as "Field-count W idth [Operand-index]") - into `formarr`, each bound to one of
the 50 near-identical `abi_pack_NN` routines at 0x436855-0x437427. There are 50 pack routines
for 40 named formats, so several formats likely share more than one routine (e.g. a plain pack
plus a pack-with-range-check variant going through `abi_pack_dispatch` 0x436012); **the exact
1:1 mapping between an `F#W#[O#]` string and its `abi_pack_NN` address was not established** -
would need either runtime tracing of `abi_form_table_init` or manual disassembly of its
1605-byte body matching each string load to the following `form_define` call's second argument.
Noted as an open question below.

## Full function list (all 271)

| addr | name | size | conf | description |
|---|---|---|---|---|
| 0042c8ba | `ext_lookup` | 559 | med | Multi-criteria external-symbol hash lookup: walks the 2003-bucket global extern table (ext_hash-like, base &DAT_00461ff8); prefers a definition from the currently loading module (DAT_00461ddc), else one seen in the outer link scope list (DAT_00461f00), else a "strong" (bit 0x80) definition, else a "weak" (bit 0x40) one; folds to lower case first if DAT_00461214 (case-insensitive mode) is set. |
| 0042cae9 | `ext_add` | 548 | med | Creates (via 0042cd0d lookup + xmalloc, 0x1c/28-byte node) or updates the global extern-table entry for name; sets strong(0x80)/weak(0x40) flag from force/reftype, records owning module and bumps DAT_004612e0 (symbol count). |
| 0042cd0d | `sym_lookup` | 415 | med | Hash lookup in the per-module "local/full" symbol table (2003-bucket table at &DAT_00465e98, next ptr at field[6]); prefers an entry matching the current module (DAT_00461ddc). |
| 0042ceac | `sym_dedup_locals` | 381 | low | Scans the whole local symbol table (2003 buckets) and removes (via 0042d029) any local entry that is now also present as a global extern (matched through ext_lookup-style comparison) or carries the "duplicate" flags in local_c[1]. |
| 0042d029 | `sym_remove` | 226 | med | Unlinks a symbol node from the local table's doubly linked hash chain (prev/next at fields[5]/[6]) and frees name+node via xfree; if bit 0x80 is set and DAT_00461248 (lazy-free mode) is active, instead just marks bit 0x100 and bumps a deferred-free counter (DAT_004612e4) instead of freeing immediately. |
| 0042d10b | `free_scratch_buffers` | 106 | low | Frees three small scratch pointers (DAT_00461f1c/1f20/1f24) used transiently elsewhere; trivial 3x if(p) free(p). |
| 0042d175 | `free_module_list` | 180 | low | Walks DAT_00461dcc (list of loaded object modules) freeing each module's name, a nested two-level substructure at offsets 0x30/0x38 (per-module symbol or section sublists), and the module record itself; clears DAT_00461e80. |
| 0042d229 | `free_reloc_table` | 454 | low | Frees a third 2003-bucket hash table (&DAT_00463f48): for every chain entry frees three nested sublists (offsets 0x18/0x1c/0x20), calling out to an external per-item cleanup function (0042b1d5, defined in another module) before freeing each item. |
| 0042d3ef | `ext_free_all` | 149 | med | Frees every bucket of the global extern table (&DAT_00461ff8, 2003 buckets, next at field[0x18]); frees name then node. Resets DAT_00461e88 and DAT_004612dc. Matches ASM56000 util.c ext_free_all in role. |
| 0042d484 | `sym_free_all` | 149 | med | Frees every bucket of the local/full symbol table (&DAT_00465e98, 2003 buckets, next at field[6]); frees name then node. Resets DAT_00461e8c and DAT_004612e0. Matches ASM56000 util.c sym_free_all in role. |
| 0042d519 | `free_reloc_table_entries` | 139 | low | For every bucket of a table rooted through DAT_00463f48 (buckets chained via +0x10), frees a nested list at +0xc without freeing the bucket record itself (companion of 0042d229). |
| 0042d5a4 | `free_section_symbols` | 411 | low | Walks the section list (DAT_00461db8) and, for each local/global sub-scope, frees three hashed sub-lists (+0x10 array of buckets, +0x18, +0x14) of per-section symbol records. |
| 0042d73f | `free_local_blocks` | 187 | low | Walks the local-block list (DAT_00461dbc) freeing per-block symbol chains and the blocks themselves; resets DAT_00461dbc to 0. |
| 0042d7fa | `free_chain` | 43 | low | Generic singly linked list free: walks next-pointer at offset 0x10 and xfrees every node. Used by 0042d825. |
| 0042d825 | `free_something_lists` | 171 | low | Frees 8 parallel sub-lists (via 0042d7fa) hung off each node of DAT_00461e24, then the outer nodes; clears 8 head globals starting at DAT_00461df8. |
| 0042d8d0 | `find_directive_or_macro` | 35 | low | tab_search wrapper over a table at 0x458010 (count at DAT_00458098, element size 8) using 0042d939 as comparator. |
| 0042d8f3 | `find_option_or_macro` | 35 | low | tab_search wrapper over a table at 0x4580a0 (count at DAT_00458100, element size 8) using 0042d939 as comparator. |
| 0042d916 | `find_keyword_or_macro` | 35 | low | tab_search wrapper over a table at 0x458108 (count at DAT_00458210, element size 8) using 0042d939 as comparator. |
| 0042d939 | `name_cmp` | 23 | med | strcmp(key, *(char**)entry); comparator used by tab_search callers 0042d8d0/8f3/916. Return value discarded by caller (Ghidra dropped it) - matches ASM56000 name_cmp in spirit. |
| 0042d950 | `mod_has_extern_ref` | 173 | low | Returns true if name is present in the current module's (DAT_00461ddc) own list of extern references (offset 0xc chain); used to decide default strong/weak flag when adding a symbol. |
| 0042e170 | `xmalloc` | 45 | high | malloc(size); on failure calls the fatal-error reporter with "Out of memory - link aborted" and does not return. Byte-identical to ASM56000 util.c xmalloc (xmatch). |
| 0042e19d | `xrealloc` | 49 | high | realloc(p,size); on failure calls the fatal-error reporter with "Out of memory - link aborted". Byte-identical to ASM56000 util.c xrealloc (xmatch). |
| 0042e1ce | `xfree` | 17 | high | free(p); no NULL/error check. Matches ASM56000 xfree in role. |
| 0042e1df | `tab_search` | 126 | high | Binary search over a sorted array (count elements of size bytes) using cmp(key,elem)->int; byte-identical to ASM56000 util.c tab_search (xmatch). |
| 0042e25d | `sort_ptrs` | 348 | high | Quicksort over the pointer array at DAT_00461f18 using comparator DAT_00461dc8; calls sort_swap (0042e3b9). Matches ASM56000 sort_ptrs by signature/behaviour (its twin sort_swap is byte-identical/xmatch). |
| 0042e3b9 | `sort_swap` | 64 | high | Swaps DAT_00461f18[i] and DAT_00461f18[j]. Byte-identical to ASM56000 util.c sort_swap (xmatch). |
| 0042e3f9 | `hash_name` | 111 | high | Classic ELF-style shift/xor hash, folded modulo 0x7d3 (2003) - DSPLNK uses 2003-bucket tables vs ASM56000's 1009; same algorithm as ASM56000 util.c hash_name. |
| 0042e468 | `base_name` | 119 | high | Returns pointer just past the last '\\' or ':' in path (or path itself if none). Matches ASM56000 util.c base_name. |
| 0042e4df | `get_string` | 323 | high | Copies a quoted (' or ") string literal from src into dst, honouring ''/"" doubling and '+'-concatenation of adjacent literals; reports "Missing string after concatenation operator" / "Missing quote in string". Matches ASM56000 get_string. |
| 0042e622 | `get_symbol` | 289 | high | Reads an identifier (first char alpha/underscore) from the global input cursor DAT_00461d68 into a 0x201-byte static buffer DAT_00469b90; reports "Invalid symbol" / "Symbol name too long". Matches ASM56000 get_symbol. |
| 0042e743 | `get_mem_spec` | 2563 | high | Parses a "space:counter" memory specification from the input cursor (calls char_to_mem_space via 0042f35d); reports the various "Illegal memory space/map/counter character" and "Syntax error - expected ':'" / "expected '):'" messages. Matches ASM56000 get_mem_spec in role (2563-byte function, largest in this cluster). |
| 0042f146 | `mem_space_char` | 116 | med | Space-code -> display character: P=0x50, X=0x58, Y=0x59, L=0x4c, E(0x1c)=0x45, D(0x11d)=0x44, U(0x11f)=0x55, default N=0x4e. Parallels ASM56000 mem_space_char. |
| 0042f1ca | `mem_space_index` | 69 | low | Maps a small set of encoded values (1,2,4,8) to array index 0..4 for internal counter arrays; parallels ASM56000 mem_space_index (exact mapping unverified). |
| 0042f22f | `get_mem_space` | 113 | low | Space-code -> small enumerated index (0..7), companion of 0x42f2b0 which is its inverse; parallels ASM56000 get_mem_space/char_to_mem_space cluster. |
| 0042f2b0 | `mem_space_from_index` | 90 | low | Inverse of 0x42f22f: enumerated index (0..7) -> space code (1,2,3,0,0x1c,0x11d,0x11f). |
| 0042f326 | `counter_index` | 55 | low | Maps counter code 0/0x10/0x20 to small index 0/1/2, else -1. |
| 0042f35d | `char_to_mem_space` | 185 | high | Lower-cases c then maps 'd'->0x11d, 'e'->0x1c, 'l'->3, 'n'->4, 'p'->0, ... default 0xa2c2a (error code). Matches ASM56000 char_to_mem_space. |
| 0042f450 | `char_to_counter` | 148 | high | Lower-cases c then maps 'd'/'n'->0, 'h'->2, 'l'->1, default -1. Byte-identical to ASM56000 util.c char_to_counter (xmatch). |
| 0042f503 | `char_to_mem_map` | 1138 | med | 1138-byte combined two-character memory-map-code parser (":"-combinations); parallels ASM56000 char_to_mem_map. |
| 0042facc | `get_force` | 282 | low | Character-class based bit-flag computation (0x20/0x30/0x50/0x40/0x60 families combined with a range-parity bit); parallels ASM56000 get_force. Referenced by string "Invalid EMI memory designation". |
| 0042fc06 | `emi_map` | 78 | low | Maps small (n,width in {8,16}) pairs to enumerated EMI codes 0x11e/0x120/0x121, else error code 0xa2c2a; parallels ASM56000 emi_map. |
| 0042fc54 | `mem_map_normalize` | 224 | low | Normalizes/canonicalizes a mem-map code range into a smaller code set; companion of char_to_mem_map. |
| 0042fd64 | `mem_map_encode` | 567 | low | 567-byte table mapping (kind in 0/1/.., size in {0x100,0x200,0x400,0x1000,0x2000,...}) to small enumerated codes (0xb..0x1f range); memory-map/EMI code family continued. |
| 0042ffab | `str_upper` | 140 | high | In-place upper-cases s using toupper/isupper. Byte-identical to ASM56000 str_upper (xmatch). |
| 00430037 | `str_lower` | 140 | high | In-place lower-cases s using tolower/islower. Byte-identical to ASM56000 str_lower (xmatch). |
| 004300c3 | `set_file_buffer` | 53 | high | setvbuf(fp, which?DAT_00469d98:DAT_00469390, _IOFBF, 0x800). Byte-identical to ASM56000 set_file_buffer (xmatch). |
| 004300f8 | `str_has_alpha` | 114 | low | Scans the static buffer at DAT_00461320 for the first alphabetic character; returns true iff one is found before the terminating NUL. |
| 0043016a | `merge_mem_space` | 343 | med | Combines two memory-space codes, rejecting incompatible combinations (returns error code 0xa2c2a); parallels ASM56000 merge_mem_space(int,int). |
| 004302d1 | `fmt_double` | 611 | high | Formats val into buf honouring fmt, with special-cased Inf/NaN text ("E+000" etc). Byte-identical to ASM56000 fmt_double (xmatch). |
| 00430534 | `clear_elf_scratch` | 39 | low | memset's two 0x20-byte scratch buffers (DAT_0046c140, DAT_0046c080) to zero; used by the COFF->ELF writer. |
| 0043055b | `obj_fread` | 210 | med | Thin fread() wrapper (redirection point), parallels ASM56000 obj_fwrite's role for reads. |
| 0043062d | `fread_swapped` | 58 | med | fread() directly, then byte-swaps via swap_words(); parallels ASM56000 fwrite_swapped. |
| 00430667 | `obj_fread_swapped` | 58 | med | Calls obj_fread() (redirectable) then swap_words(); parallels ASM56000 obj_fwrite_swapped. |
| 004306a1 | `obj_fwrite` | 210 | med | Thin fwrite() wrapper (redirection point); parallels ASM56000 obj_fwrite (not byte-identical here but same role). |
| 00430773 | `fwrite_swapped` | 49 | med | swap_words() then fwrite() directly; parallels ASM56000 fwrite_swapped. |
| 004307a4 | `obj_fwrite_swapped` | 49 | med | swap_words() then obj_fwrite() (redirectable); parallels ASM56000 obj_fwrite_swapped. |
| 004307d5 | `swap_words` | 118 | high | Byte-swaps n*size/4 groups of 4 bytes (big<->little endian). Byte-identical to ASM56000 swap_words (xmatch). |
| 0043084b | `tm_to_secs` | 638 | high | Converts a struct-tm-like sec/min/hour/day/month/year record to a flat second count via cascading base-60/24/... carries. Byte-identical to ASM56000 tm_to_secs (xmatch). |
| 00430ac9 | `buf_align_check` | 138 | low | Rounds need up using round_up_pow2(align), masks against a mode-selected limit (DAT_00461f44==5 ? limit : DAT_00461f74) and reports "Buffer block too large" if still short. |
| 00430b53 | `round_up_pow2` | 70 | high | Rounds n up to the next power of two (bit-clear-lowest loop then <<1); n<2 -> 0 or 2. Byte-identical to a routine also present (unrelated module) in ASM56000 (xmatch, coincidental generic pattern). |
| 00431630 | `elf_tell` | 10 | low | Returns the cached current output-file offset DAT_0046a938. |
| 0043163a | `elf_seek` | 49 | med | fseek(fp,pos,SEEK_SET); reports "Cannot seek to ELF object file position" on failure; updates the cached offset DAT_0046a938. |
| 0043166b | `elf_write_sections` | 1334 | low | Iterates the pending ELF section-record list (DAT_0046a958) and, per record type (0/2/3/...), seeks and writes its data via elf_seek/obj-write helpers. |
| 00431bbf | `elf_write_data` | 70 | low | fwrite() wrapper reporting "Cannot write data to ELF object file" on short write. |
| 00431c05 | `elf_write_data2` | 70 | low | Second fwrite() wrapper with the same "Cannot write data to ELF object file" message (used from a different call site than 0x431bbf). |
| 00431c4b | `elf_new_section` | 669 | low | Allocates a 0x40-byte ELF section-record, stores a copy of name and appends name to the shared string-table blob (via strtab_append 0x431ee8); links the record into DAT_0046a958. |
| 00431ee8 | `strtab_append` | 277 | low | Appends name (with terminating NUL) into a growable string blob (*tab=data ptr, tab[1]=used, tab[2]=capacity, geometric growth then +=0x400); returns the previous used-offset. |
| 00431ffd | `elf_init` | 612 | med | Resets all COFF->ELF writer state, builds the ELF file header (elf_build_header 0x432261) and creates the fixed "" / ".shstrtab" / ".strtab" / ".note" / ".symtab" section records via elf_new_section. |
| 00432261 | `elf_build_header` | 283 | high | Allocates and fills a 0x34-byte Elf32_Ehdr: magic "\x7fELF", ELFCLASS32, ELFDATA2MSB (big-endian, DSP target), version 1, e_type=ET_EXEC(2), e_machine=2, ehsize=0x34, shentsize=0x28. |
| 004326d0 | `elf_write_maybe_swapped` | 77 | low | If size<5 swaps 2/4-byte fields in place (0x43271d) else calls swap_words, then fwrite()s; used for ELF structures with mixed field widths. |
| 0043271d | `swap_field` | 124 | low | Byte-swaps a single 2- or 4-byte field in place (size==2 or 4). |
| 00432799 | `coff_to_elf` | 561 | med | Top-level COFF->ELF converter entry: opens coff_path for read and elf_path for write ("Cannot open %s\n" on failure), reads the COFF headers (read_coff_headers 0x432a34), calls elf_init, then converts each pending record via search 0x433153. |
| 004329ca | `free_elf_section_list` | 106 | low | Frees the pending ELF section-record list (DAT_0046ac64) built by sec_list_add, including each record's nested string sublist. |
| 00432a34 | `read_coff_headers` | 470 | med | Reads the COFF file/optional/linker headers via fread_swapped, validates the magic, and reads the COFF string table (read_coff_strtab 0x432c0a) if non-interactive linking; reports "Cannot read COFF file/optional/linker header", "Invalid COFF object file format". |
| 00432c0a | `read_coff_strtab` | 369 | med | Seeks to and reads the raw COFF string table into DAT_0046aba8 (size DAT_0046aba0); reports "cannot seek/read COFF string table", "invalid COFF string table length". |
| 00432d7b | `read_coff_sections` | 324 | med | Reads count 0x34-byte COFF section headers at off, resolving each name via coff_strtab_name; reports "COFF section header seek failure", "Can't read COFF section header". |
| 00432ebf | `sec_list_add` | 275 | low | Allocates (record_node_alloc) and appends a named 0x20-byte record to the global list DAT_0046ac64/DAT_0046ac60 (tail-append). |
| 00432fd2 | `record_node_alloc` | 40 | low | xmalloc(0x20) + memset 0; generic zeroed node allocator shared by sec_list_add/sub_record_list_add. |
| 00432ffa | `sub_record_list_add` | 172 | low | Same as sec_list_add but appends to a caller-supplied list head (*head) rather than the global list; used for a per-record sub-list. |
| 004330a6 | `record_list_find` | 63 | low | Linear search of DAT_0046ac64 by name (strcmp on field+8), next pointer at field+0x1c. |
| 004330e5 | `coff_strtab_name` | 86 | med | Resolves a COFF short/long section name: if the 8-byte inline name is empty, treats nameref[1] as a string-table byte offset (bounds-checked against DAT_0046aba0) and returns a pointer into the loaded COFF string table (0046aba8); reports "invalid COFF string table offset for section header name". |
| 0043313b | `test_bit1` | 24 | low | Returns (flags & 2)!=0; single-bit test used while reading COFF/linker header flags. |
| 00433153 | `record_list_total_size` | 331 | low | Walks a linked list (next at field 0) summing field[5] of every node; used to size the ELF symbol/string table before writing it out. |
| 0043329e | `noop_433` | 16 | low | Body not individually examined; sits between the COFF/ELF cluster and the LONGInfArray family. Placeholder name, low confidence. |
| 004335b0 | `dbg_print_str` | 26 | med | Debug trace helper: printf("Msg: %s, Val: %s \n", msg, val). Params recovered from stack (Ghidra dropped them as a no-arg function). |
| 004335ca | `dbg_print_long` | 26 | med | Debug trace helper: printf("Msg: %s, Val: %ld \n", msg, val). |
| 004335e4 | `dbg_print_ulong` | 26 | med | Debug trace helper: printf("Msg: %s, Unsigned long Val: %lu \n", msg, val). |
| 00433620 | `longarr_destroy` | 42 | med | InfArray generic container instantiated for LONG (source file "LONGInfArray.c" named in its assert()/error strings). |
| 0043364a | `longarr_create` | 256 | high | InfArray generic container instantiated for LONG (source file "LONGInfArray.c" named in its assert()/error strings). |
| 0043374a | `longarr_dump` | 130 | med | InfArray generic container instantiated for LONG (source file "LONGInfArray.c" named in its assert()/error strings). |
| 004337cc | `longarr_free_storage` | 160 | low | InfArray generic container instantiated for LONG (source file "LONGInfArray.c" named in its assert()/error strings). |
| 0043386c | `longarr_compact` | 76 | low | InfArray generic container instantiated for LONG (source file "LONGInfArray.c" named in its assert()/error strings). |
| 004338b8 | `longarr_grow` | 408 | high | InfArray generic container instantiated for LONG (source file "LONGInfArray.c" named in its assert()/error strings). |
| 00433a50 | `longarr_append` | 102 | low | InfArray generic container instantiated for LONG (source file "LONGInfArray.c" named in its assert()/error strings). |
| 00433ab6 | `longarr_insert` | 76 | low | InfArray generic container instantiated for LONG (source file "LONGInfArray.c" named in its assert()/error strings). |
| 00433b02 | `longarr_get` | 57 | med | InfArray generic container instantiated for LONG (source file "LONGInfArray.c" named in its assert()/error strings). |
| 00433b3b | `longarr_is_empty` | 47 | low | InfArray generic container instantiated for LONG (source file "LONGInfArray.c" named in its assert()/error strings). |
| 00433b6a | `longarr_is_full` | 47 | low | InfArray generic container instantiated for LONG (source file "LONGInfArray.c" named in its assert()/error strings). |
| 00433b99 | `longarr_count` | 5 | low | InfArray generic container instantiated for LONG (source file "LONGInfArray.c" named in its assert()/error strings). |
| 00433d00 | `symtblarr_destroy` | 42 | med | InfArray generic container instantiated for symtable (source file "symtableInfArray.c" named in its assert()/error strings). |
| 00433d2a | `symtblarr_create` | 256 | high | InfArray generic container instantiated for symtable (source file "symtableInfArray.c" named in its assert()/error strings). |
| 00433e2a | `symtblarr_dump` | 130 | med | InfArray generic container instantiated for symtable (source file "symtableInfArray.c" named in its assert()/error strings). |
| 00433eac | `symtblarr_free_storage` | 160 | low | InfArray generic container instantiated for symtable (source file "symtableInfArray.c" named in its assert()/error strings). |
| 00433f4c | `symtblarr_compact` | 76 | low | InfArray generic container instantiated for symtable (source file "symtableInfArray.c" named in its assert()/error strings). |
| 00433f98 | `symtblarr_grow` | 408 | high | InfArray generic container instantiated for symtable (source file "symtableInfArray.c" named in its assert()/error strings). |
| 00434130 | `symtblarr_append` | 102 | low | InfArray generic container instantiated for symtable (source file "symtableInfArray.c" named in its assert()/error strings). |
| 00434196 | `symtblarr_insert` | 76 | low | InfArray generic container instantiated for symtable (source file "symtableInfArray.c" named in its assert()/error strings). |
| 004341e2 | `symtblarr_get` | 57 | med | InfArray generic container instantiated for symtable (source file "symtableInfArray.c" named in its assert()/error strings). |
| 0043421b | `symtblarr_is_empty` | 47 | low | InfArray generic container instantiated for symtable (source file "symtableInfArray.c" named in its assert()/error strings). |
| 0043424a | `symtblarr_is_full` | 47 | low | InfArray generic container instantiated for symtable (source file "symtableInfArray.c" named in its assert()/error strings). |
| 00434279 | `symtblarr_count` | 5 | low | InfArray generic container instantiated for symtable (source file "symtableInfArray.c" named in its assert()/error strings). |
| 004343e0 | `abi_mp_sym_free_elem` | 85 | med | Element destructor for an ABI_mp_symtbl entry: frees its name, and (if its type tag == 4) a secondary owned pointer at field[2], then the element itself. |
| 00434435 | `abi_mp_sym_alloc` | 72 | med | Allocates a 0x18-byte ABI_mp_symtbl element (xmalloc + strdup(name) + 3 stored fields); the element type stored inside abimparr. |
| 0043447d | `symtbl_find_by_name` | 131 | med | Generic linear O(n) search through a symtblarr-shaped InfArray comparing element[0] (name) to name via the array's own accessor vtable slot at +0x20; reports "Table Search Name NULL" if name is NULL. |
| 00434550 | `abimparr_destroy` | 42 | med | InfArray generic container instantiated for ABI_mp_symtbl (source file "ABI_mp_symtblInfArray.c" named in its assert()/error strings). |
| 0043457a | `abimparr_create` | 256 | high | InfArray generic container instantiated for ABI_mp_symtbl (source file "ABI_mp_symtblInfArray.c" named in its assert()/error strings). |
| 0043467a | `abimparr_dump` | 130 | med | InfArray generic container instantiated for ABI_mp_symtbl (source file "ABI_mp_symtblInfArray.c" named in its assert()/error strings). |
| 004346fc | `abimparr_free_storage` | 160 | low | InfArray generic container instantiated for ABI_mp_symtbl (source file "ABI_mp_symtblInfArray.c" named in its assert()/error strings). |
| 0043479c | `abimparr_compact` | 76 | low | InfArray generic container instantiated for ABI_mp_symtbl (source file "ABI_mp_symtblInfArray.c" named in its assert()/error strings). |
| 004347e8 | `abimparr_grow` | 408 | high | InfArray generic container instantiated for ABI_mp_symtbl (source file "ABI_mp_symtblInfArray.c" named in its assert()/error strings). |
| 00434980 | `abimparr_append` | 102 | low | InfArray generic container instantiated for ABI_mp_symtbl (source file "ABI_mp_symtblInfArray.c" named in its assert()/error strings). |
| 004349e6 | `abimparr_insert` | 76 | low | InfArray generic container instantiated for ABI_mp_symtbl (source file "ABI_mp_symtblInfArray.c" named in its assert()/error strings). |
| 00434a32 | `abimparr_get` | 57 | med | InfArray generic container instantiated for ABI_mp_symtbl (source file "ABI_mp_symtblInfArray.c" named in its assert()/error strings). |
| 00434a6b | `abimparr_is_empty` | 47 | low | InfArray generic container instantiated for ABI_mp_symtbl (source file "ABI_mp_symtblInfArray.c" named in its assert()/error strings). |
| 00434a9a | `abimparr_is_full` | 47 | low | InfArray generic container instantiated for ABI_mp_symtbl (source file "ABI_mp_symtblInfArray.c" named in its assert()/error strings). |
| 00434ac9 | `abimparr_count` | 5 | low | InfArray generic container instantiated for ABI_mp_symtbl (source file "ABI_mp_symtblInfArray.c" named in its assert()/error strings). |
| 00434c30 | `abi_mp_sym_free_with_arr` | 95 | med | Element destructor for an ABI_mp_symtbl entry that owns a nested LONGInfArray: frees the name, calls longarr_destroy on field[1], then frees the element. |
| 00434c8f | `abi_mp_sym_build` | 190 | low | Builds a new ABI_mp_symtbl element keyed by a "%#0lx" hex string of key, containing a fresh nested longarr (via longarr_create) populated by iterating a source list; nested-container pattern (ABI_mp_symtbl element embeds a LONGInfArray). |
| 00434d4d | `abi_mp_sym_find` | 182 | med | Formats key as "%#0lx" then linear-searches arr the same way as symtbl_find_by_name; reports "ABI_mp_symtblInfArray Search Table is NULL" / "...key 'mp' is NULL". |
| 00434e80 | `formarr_destroy` | 42 | med | InfArray generic container instantiated for formtable (source file "formtableInfArray.c" named in its assert()/error strings). |
| 00434eaa | `formarr_create` | 256 | high | InfArray generic container instantiated for formtable (source file "formtableInfArray.c" named in its assert()/error strings). |
| 00434faa | `formarr_dump` | 130 | med | InfArray generic container instantiated for formtable (source file "formtableInfArray.c" named in its assert()/error strings). |
| 0043502c | `formarr_free_storage` | 160 | low | InfArray generic container instantiated for formtable (source file "formtableInfArray.c" named in its assert()/error strings). |
| 004350cc | `formarr_compact` | 76 | low | InfArray generic container instantiated for formtable (source file "formtableInfArray.c" named in its assert()/error strings). |
| 00435118 | `formarr_grow` | 408 | high | InfArray generic container instantiated for formtable (source file "formtableInfArray.c" named in its assert()/error strings). |
| 004352b0 | `formarr_append` | 102 | low | InfArray generic container instantiated for formtable (source file "formtableInfArray.c" named in its assert()/error strings). |
| 00435316 | `formarr_insert` | 76 | low | InfArray generic container instantiated for formtable (source file "formtableInfArray.c" named in its assert()/error strings). |
| 00435362 | `formarr_get` | 57 | med | InfArray generic container instantiated for formtable (source file "formtableInfArray.c" named in its assert()/error strings). |
| 0043539b | `formarr_is_empty` | 47 | low | InfArray generic container instantiated for formtable (source file "formtableInfArray.c" named in its assert()/error strings). |
| 004353ca | `formarr_is_full` | 47 | low | InfArray generic container instantiated for formtable (source file "formtableInfArray.c" named in its assert()/error strings). |
| 004353f9 | `formarr_count` | 5 | low | InfArray generic container instantiated for formtable (source file "formtableInfArray.c" named in its assert()/error strings). |
| 00435560 | `form_elem_free` | 61 | med | Element destructor for a formtable entry {name, fn}: frees the name then the element. |
| 0043559d | `form_define` | 57 | low | strdup(name)+xmalloc a 2-field record {name, fn} and appends it into the global format table (formarr) via formarr_append; called once per F-code by the registration function 0x436210. |
| 004355d6 | `form_find_by_name` | 131 | med | Same generic linear search pattern as symtbl_find_by_name, applied to a formarr (field-format table); reports "Table Search Name NULL". |
| 004356a0 | `op_uplus` | 11 | low | Unary "+": returns a unchanged (b unused - kept for a uniform int(*)(int,int) operator-table signature). |
| 004356ab | `op_uminus` | 11 | low | Unary "-": returns -a (b unused). |
| 004356b6 | `op_bitnot` | 12 | low | Bitwise complement: returns ~a (b unused). |
| 004356c2 | `op_div` | 35 | med | 32-bit "/": reports "Divide by Zero" and returns a sentinel via the no-op trampoline 0x43a408 when b==0, else a/b. |
| 004356e5 | `op_mod` | 37 | med | 32-bit "%": reports "Divide by Zero" via 0x43a408 when b==0, else a%b. |
| 0043570a | `op_add64` | 17 | low | 64-bit add on (hi:lo) operand pairs, done inline (add/adc); returns the 64-bit sum split across EAX:EDX (undefined8 in Ghidra). |
| 0043571b | `op_sub64` | 17 | low | 64-bit subtract on (hi:lo) operand pairs, done inline (sub/sbb). |
| 0043572c | `op_mul64` | 26 | med | 64-bit multiply via the MSVC CRT helper _allmul. |
| 00435746 | `op_div64` | 55 | med | 64-bit divide via the MSVC CRT helper _alldiv; reports "Divide by Zero" through 0x43a408 when the divisor is 0. |
| 0043577d | `op_mod64` | 55 | med | 64-bit modulo via the MSVC CRT helper _allrem; reports "Divide by Zero" through 0x43a408 when the divisor is 0. |
| 004357b4 | `op_shl` | 13 | low | Left shift a by n bits (n as byte). |
| 004357c1 | `op_shr` | 13 | low | (Arithmetic) right shift a by n bits (n as byte). |
| 004357ce | `op_neg` | 10 | low | Unary "-" (single-operand form): returns -a. |
| 004357d8 | `op_compl` | 10 | low | Unary "~": returns ~a. |
| 004357e2 | `op_not` | 14 | low | Logical "!": returns a==0. |
| 004357f0 | `op_and` | 39 | low | Bitwise "&" (or logical AND - not fully disassembled): returns a combined with b. |
| 00435817 | `op_or` | 39 | low | Bitwise "\|" (or logical OR - not fully disassembled): returns a combined with b. |
| 0043583e | `op_eq` | 18 | med | Relational "==": returns a==b as 0/1. |
| 00435850 | `op_ne` | 18 | med | Relational "!=": returns a!=b as 0/1. |
| 00435862 | `op_lt` | 18 | med | Relational "<": returns a<b as 0/1. |
| 00435874 | `op_le` | 18 | med | Relational "<=": returns a<=b as 0/1. |
| 00435886 | `op_gt` | 18 | med | Relational ">": returns a>b as 0/1. |
| 00435898 | `op_ge` | 18 | med | Relational ">=": returns a>=b as 0/1. |
| 004358aa | `op_uadd` | 11 | low | Unsigned variant arithmetic/bitwise op (exact operator not distinguished from op_usub/op_uxor). |
| 004358b5 | `op_usub` | 11 | low | Unsigned variant arithmetic/bitwise op (exact operator not distinguished). |
| 004358c0 | `op_uxor` | 11 | low | Unsigned variant arithmetic/bitwise op, likely "^" (exact operator not distinguished). |
| 004358cb | `op_cond` | 31 | high | C-style ternary "cond ? b : a" (returns param_3 when cond==0, else param_2). |
| 004358ea | `abi_assign_op` | 480 | med | Compound-assignment dispatcher for the ABI expression language: looks up (symtbl_find_by_name-style via 0x43447d) or creates (0x434435) the named element, then switch(op): 0x3d = plain "=", 0x101 = "+=" (via op_add64), and further cases for -=,*=,/=,etc; reports "Not A Recognized Assign Operator!" and exit(1) for an unknown op. |
| 00435d00 | `abi_ctx_free` | 45 | med | Frees the parser-context struct allocated by abi_ctx_new (frees its embedded pointer field then the struct itself). |
| 00435d2d | `abi_ctx_new` | 299 | med | Allocates a 0x70-byte parser-context structure and snapshots ~24 current linker globals (pass, symbol tables, flags, line info) into it so yyparse can run against a saved context. |
| 00435e58 | `abi_mp_sym_name` | 258 | low | Resolves (and caches) the display name of symbol idx within sec, either from a cached string array or computed via a vtable call and strdup()'d. |
| 00435f5a | `abi_mask_then_shift` | 69 | high | Masks v then shifts it by pos in the direction given by dir ('<' or '>'); reports "abi_mask_then_shift shift_direction error" for an unrecognised dir. Shared primitive used by nearly all field-format pack functions. |
| 00435f9f | `abi_bit_range_mask` | 115 | med | Builds a bit mask spanning bits [lo,hi]; called from almost every field-format pack function (0x436855..0x437427) and from the abi_mp_sym_* field helpers. |
| 00436012 | `abi_pack_dispatch` | 126 | low | Looks up a per-format pack routine via abi_bit_range_mask and invokes it; small dispatcher used by 0x437fc0/0x438042. |
| 00436090 | `abi_report_error` | 119 | med | Formats " %s at Location %s" (or, with lastsym, the extended form including the last referenced symbol name/value/index) into a 516-byte stack buffer and passes it to the generic link-error reporter (0x409a25). |
| 00436210 | `abi_form_table_init` | 1605 | med | 1605-byte initializer that registers all ~40 named field-format entries ("F11W1","F11W2",...,"F15W1") into a formarr via form_define, each bound to one of the pack routines at 0x436855-0x437427. |
| 00436855 | `abi_pack_01` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 0043687e | `abi_pack_02` | 38 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 004368a4 | `abi_pack_03` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 004368cd | `abi_pack_04` | 98 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 0043692f | `abi_pack_05` | 53 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436964 | `abi_pack_06` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 0043698d | `abi_pack_07` | 55 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 004369c4 | `abi_pack_08` | 53 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 004369f9 | `abi_pack_09` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436a22 | `abi_pack_10` | 45 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436a4f | `abi_pack_11` | 53 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436a84 | `abi_pack_12` | 53 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436ab9 | `abi_pack_13` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436ae2 | `abi_pack_14` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436b0b | `abi_pack_15` | 53 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436b40 | `abi_pack_16` | 53 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436b75 | `abi_pack_17` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436b9e | `abi_pack_18` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436bc7 | `abi_pack_19` | 53 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436bfc | `abi_pack_20` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436c25 | `abi_pack_21` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436c4e | `abi_pack_22` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436c77 | `abi_pack_23` | 53 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436cac | `abi_pack_24` | 53 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436ce1 | `abi_pack_25` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436d0a | `abi_pack_26` | 100 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436d6e | `abi_pack_27` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436d97 | `abi_pack_28` | 53 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436dcc | `abi_pack_29` | 53 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436e01 | `abi_pack_30` | 55 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436e38 | `abi_pack_31` | 45 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436e65 | `abi_pack_32` | 53 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436e9a | `abi_pack_33` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436ec3 | `abi_pack_34` | 99 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436f26 | `abi_pack_35` | 53 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436f5b | `abi_pack_36` | 87 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436fb2 | `abi_pack_37` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00436fdb | `abi_pack_38` | 55 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00437012 | `abi_pack_39` | 87 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00437069 | `abi_pack_40` | 45 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00437096 | `abi_pack_41` | 53 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 004370cb | `abi_pack_42` | 87 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00437122 | `abi_pack_43` | 41 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 0043714b | `abi_pack_44` | 183 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00437202 | `abi_pack_45` | 141 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 0043728f | `abi_pack_46` | 84 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 004372e3 | `abi_pack_47` | 84 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00437337 | `abi_pack_48` | 99 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 0043739a | `abi_pack_49` | 141 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00437427 | `abi_pack_50` | 127 | low | One of the ~40 named ABI field-format ("F#W#[O#]") pack routines registered by abi_form_table_init (0x436210); masks/shifts its operand into position via abi_bit_range_mask+abi_mask_then_shift, some also calling abi_pack_dispatch (0x437fc0). Individual F-code correspondence not established (see notes). |
| 00437950 | `abi_map_lookup` | 1270 | low | 9-argument function reporting "Section map lookup failure"; checks a revision/processor gate (DAT_00461fe8/fec/ff0) before resolving a section/location mapping. Called only from yyparse (0x43a40d). |
| 00437e46 | `abi_func_sym` | 378 | high | ABI expression-language builtin "abi_func_sym()": resolves symbol #idx, reporting "A Symbol is Not Found at Given Symbol Index=%ld"; builds its result via free()/sprintf and calls into 0x436090 for error reporting, 0x42c8ba/0x435e58 for lookup. |
| 00437fc0 | `abi_func_pack` | 130 | high | ABI expression-language builtin "abi_func_pack()": packs v into a field using abi_pack_dispatch/abi_bit_range_mask/abi_mask_then_shift; reports "Unable to Pack Value". |
| 00438042 | `abi_func_check` | 449 | high | ABI expression-language builtin "abi_func_check()": range-checks v against [lo,hi] as signed or unsigned per sign; reports "Value=%#0lx Must be %dbit-aligned", "Signed/Unsigned Value=%#0lx is Out of Range", "No Sign Specified (s/u) for Checking Value=%#0lx". |
| 00438203 | `abi_mp_sym_get_mask` | 87 | low | Reads the type field (offset 0x6c, default 2) and ANDs m with a bit-range mask computed via 0x435f9f(0,7). |
| 0043825a | `abi_mp_sym_shift_field` | 111 | low | Reads the type field (offset 0x6c, default 2) then right-shifts v by a bit range computed via 0x435f9f(8,0xf)/0x435f5a with direction '>'. |
| 004382c9 | `abi_func_memcheck` | 115 | high | ABI expression-language builtin "abi_func_memcheck()": validates v against a memory/section constraint via 0x42f2b0/0x43016a/0x436090; reports "Memory Constraint Violation!". |
| 0043833c | `set_cur_opt_char` | 16 | low | Stores and returns c via DAT_00461314 (simple global setter). |
| 0043834c | `abi_mp_sym_set_type` | 18 | low | Stores a 2-byte type/space code at offset 0x6c of an ABI_mp_symtbl element. |
| 004385f0 | `abi_lnk_extract_val` | 137 | high | ABI expression-language builtin "abi_lnk_extract_val()": extracts/converts a typed value; reports "Can not Convert to Incompatible Data Type" via 0x436090 ("Parser Error: %s in Location %s"). |
| 00438679 | `abi_lnk_convert_type` | 361 | high | ABI expression-language builtin "abi_lnk_convert_type()": dispatches to one of four type converters (0x4387f2/0x438889/0x43891b/0x4389ab) by totype; reports "Requested Data Type Not Found!". |
| 004387f2 | `abi_conv_case1` | 151 | low | One of 4 value-type converters dispatched by abi_lnk_convert_type; narrows/sign-extends into a 16-bit-tagged result. |
| 00438889 | `abi_conv_case2` | 146 | low | One of 4 value-type converters dispatched by abi_lnk_convert_type. |
| 0043891b | `abi_conv_case3` | 144 | low | One of 4 value-type converters dispatched by abi_lnk_convert_type. |
| 004389ab | `abi_conv_case4` | 159 | low | One of 4 value-type converters dispatched by abi_lnk_convert_type; sign-extends a 16/32-bit value into a 64-bit (hi:lo) result - likely the "convert to long" case. |
| 00438b60 | `yylex` | 2158 | high | Flex-generated scanner main function for the ABI expression-language lexer (DFA table walk); the huge (2158-byte) case/goto structure is flex boilerplate, not hand-written. |
| 004394be | `yy_get_next_buffer` | 645 | high | Flex-generated: refills the scan buffer from the input stream; reports "fatal flex scanner internal error--end of buffer missed" / "...input buffer overflow". |
| 00439743 | `yyunput` | 246 | low | Flex-generated: pushes character c back into the scan buffer (called only from yylex). |
| 00439839 | `input` | 192 | low | Flex-generated: reads and returns the next input character (called only from yylex). |
| 004398f9 | `yyrestart` | 62 | high | Flex-generated: (re)associates the scanner with input_file, creating (yy_create_buffer) and initializing (yy_init_buffer) the buffer, then yy_load_buffer_state. |
| 00439937 | `yy_switch_to_buffer` | 92 | high | Flex-generated: makes new_buffer the current scan buffer and calls yy_load_buffer_state. |
| 00439993 | `yy_load_buffer_state` | 72 | med | Flex-generated: copies the current buffer's scan-position fields into the global scanner state. |
| 004399db | `yy_create_buffer` | 124 | high | Flex-generated: allocates and returns a new scan-buffer structure; reports "out of dynamic memory in yy_create_buffer()". |
| 00439a57 | `yy_delete_buffer` | 70 | med | Flex-generated: frees a scan-buffer's character array then the buffer structure itself (via yy_flex_free). |
| 00439a9d | `yy_init_buffer` | 93 | high | Flex-generated: (re)initializes a scan buffer for file, setting its interactive flag via isatty(fileno(file)). |
| 00439afa | `yy_flush_buffer` | 90 | med | Flex-generated: resets a scan buffer's read position to the start, reloading state if it is the current buffer. |
| 00439b54 | `yy_scan_buffer` | 197 | high | Flex-generated: sets up scanning directly from an in-memory buffer; reports "out of dynamic memory in yy_scan_buffer()". |
| 00439c19 | `yy_scan_string` | 57 | med | Flex-generated: convenience wrapper - yy_scan_bytes(s, strlen(s)). |
| 00439c52 | `yy_scan_bytes` | 167 | high | Flex-generated: sets up scanning of an in-memory byte range; reports "out of dynamic memory in yy_scan_bytes()" / "bad buffer in yy_scan_bytes()". |
| 00439cf9 | `yy_fatal_error` | 37 | high | Flex-generated: fprintf(stderr,"%s\n",msg); exit(2). Generic scanner fatal-error reporter. |
| 00439d1e | `yy_flex_alloc` | 17 | high | Flex-generated allocator wrapper: calls xmalloc (0x42e170). |
| 00439d2f | `yy_flex_realloc` | 21 | high | Flex-generated allocator wrapper: calls xrealloc (0x42e19d). |
| 00439d44 | `yy_flex_free` | 17 | high | Flex-generated allocator wrapper: calls xfree (0x42e1ce). |
| 00439d55 | `yy_copy_buffer` | 102 | low | memcpy-based helper used from yy_get_next_buffer; exact role not fully isolated. |
| 00439dbb | `yy_more_flag` | 10 | low | Trivial flex-generated helper (10 bytes, no calls) referenced only from yylex; likely the yy_more()/yy_hold_char bookkeeping stub. |
| 0043a260 | `abi_expr_eval` | 41 | med | Thin public wrapper over abi_expr_eval_impl (0x43a289). |
| 0043a289 | `abi_expr_eval_impl` | 267 | med | Sets up the scanner input range (DAT_0046c070/074 = text/text+strlen), calls yyrestart, lazily creates the symtblarr/formarr tables and runs abi_form_table_init on first use, allocates a parser context (abi_ctx_new 0x435d2d), calls yyparse (0x43a40d), then frees the context. |
| 0043a394 | `abi_free_all` | 79 | high | Called once from main(): destroys the three persistent ABI tables (symtblarr, abimparr, formarr) via their *_destroy functions. Only function in this module called directly from dsplnk.c main(). |
| 0043a3e3 | `abi_mp_symtbl_dispatch` | 37 | low | Looks up an ABI_mp_symtbl entry by key (abi_mp_sym_build) then invokes a callback through the handler object's vtable slot at offset 0x34. |
| 0043a408 | `abi_expr_error_stub` | 5 | med | Empty (5-byte, "return;") no-op trampoline used as the error/divide-by-zero landing point by op_div/op_mod/op_div64/op_mod64 and called once from yyparse. |
| 0043a40d | `yyparse` | 5832 | high | 5832-byte Bison/Yacc-generated parser for the DSPLNK ABI expression language: table-driven shift/reduce automaton; reports "yacc stack overflow" and "syntax error"; its semantic actions call the op_*/abi_func_*/abi_mask_then_shift/abi_assign_op helpers documented above. |

## Symbol-table hash tables (cluster 1)

Three independent 2003-bucket (`0x7d3`) hash tables, all using the same `hash_name` (0042e3f9,
`sum = sum*16 + c` with periodic XOR-fold, `% 0x7d3`) - DSPLNK uses 2003 buckets where ASM56000's
equivalent tables use 1009 (compare `re/names/ASM56000/g2_symtab.names.txt`'s `sym_hash`/
`ext_hash`/`strtab_hash`, each `void*[1009]`):

- **`ext_hash`** (`&DAT_00461ff8`, global externs, chain-next at node offset `0x18`/24, node
  size 0x1c/28 bytes: `{char*name; long flags; void*module; long moduleval; void*outerptr; ...
  next@0x18}`). Populated by `ext_add` (0042cae9), read by `ext_lookup` (0042c8ba), fully freed
  by `ext_free_all` (0042d3ef). Flags bit 0x80 = "strong" definition, bit 0x40 = "weak"/tentative.
- **`sym_hash`** (`&DAT_00465e98`, per-module "local/full" symbols, chain-next at node offset
  `6`*4=0x18? - actually observed at field index `[6]`, i.e. offset 0x18 as well, consistent
  header shape). Populated implicitly (insertion site not found in this range - likely in
  symtab.c, outside this assignment), looked up by `sym_lookup` (0042cd0d), swept by
  `sym_dedup_locals` (0042ceac) and `sym_remove` (0042d029) and fully freed by `sym_free_all`
  (0042d484). Node duplicate-removal after a module's locals are merged into the global table.
- **third table** (`&DAT_00463f48`), also 2003 buckets, freed by `free_reloc_table` (0042d229)/
  `free_reloc_table_entries` (0042d519); each bucket entry owns three further sub-lists at
  offsets 0x18/0x1c/0x20, and item cleanup calls out to function 0x42b1d5 which is *outside*
  this assignment's range (defined in an earlier module, most likely fixup.c or object.c) -
  **this table's true owner module could not be determined from this range alone**; flagged as
  an open question.

## Memory allocators and their error behaviour

- **`xmalloc`/`xrealloc`** (0x42e170/0x42e19d): thin `malloc`/`realloc` wrappers; on failure
  print `"Out of memory - link aborted"` (via a shared fatal-error reporter, thunk to 0x4098b0 -
  outside this range) and **do not return** (the caller never needs a NULL check). Byte-identical
  to ASM56000's `xmalloc`/`xrealloc`.
- **`xfree`** (0x42e1ce): plain `free()`, no NULL guard beyond what `free()` itself tolerates.
- **InfArray `grow()`** (one per instantiation, e.g. 0x4338b8): a *second, independent*
  allocation path that calls the C library `malloc`/`realloc` **directly** (not through
  `xmalloc`/`xrealloc`), `memset`s newly grown space to 0, and on failure `fprintf(stderr,
  "Cannot alloc array\n")` + the source filename string, then `exit()`s. Quirk: two different
  out-of-memory behaviours coexist in the same module (message text differs, and InfArray does
  not go through `xmalloc`); reproduce both distinctly.
- **flex's own allocator wrappers** `yy_flex_alloc`/`yy_flex_realloc`/`yy_flex_free`
  (0x439d1e/0x439d2f/0x439d44) *do* call through to `xmalloc`/`xrealloc`/`xfree`, so the lexer's
  OOM behaviour is the same as the rest of util.c.

## Globals (selected; full list plus more transient ones in the .names.txt `D` rows)

| addr | name | type | notes |
|---|---|---|---|
| 0x00461ff8 | `ext_hash` | `void*[2003]` | global extern symbol hash table |
| 0x00465e98 | `sym_hash` | `void*[2003]` | per-module local symbol hash table |
| 0x00463f48 | `reloc_hash` | `void*[2003]` | third 2003-bucket table, owner unclear (see above) |
| 0x00461ddc | `cur_module` | `void*` | current object module being processed |
| 0x00461214 | `opt_ci` | `char` | case-insensitive symbol matching mode |
| 0x00461f18 | `sort_array` | `void**` | array being sorted by `sort_ptrs`/`sort_swap` |
| 0x00461dc8 | `sort_cmp` | `void*` | comparator function pointer for `sort_ptrs` |
| 0x00461d68 | `input_cursor` | `char*` | current parse position (get_string/get_symbol/get_mem_spec) |
| 0x0046a938 | `elf_file_pos` | `long` | cached ftell() position for the ELF writer |
| 0x0046a958 | `elf_section_list` | `void*` | pending ELF section records |
| 0x0046abac | `coff_fp` | `void*` | input COFF file handle (coff_to_elf) |
| 0x0046ac5c | `elf_fp` | `void*` | output ELF file handle (coff_to_elf) |
| 0x0046aba8 / 0x0046aba0 | `coff_strtab_buf` / `coff_strtab_size` | `char*` / `unsigned long` | loaded COFF string table |
| 0x0046c06c | `g_symtblarr` | `void*` | the one persistent `symtblarr` instance |
| 0x0046c078 | `g_formarr` | `void*` | the one persistent `formarr` instance (field-format table) |
| 0x0046c604 | `g_abimparr` | `void*` | the one persistent `abimparr` instance |
| 0x0046c070 / 0x0046c074 | `abi_expr_text` / `abi_expr_text_end` | `char*` | current ABI expression text range handed to the scanner |
| 0x0046c378 | `abi_parse_ctx` | `void*` | saved-globals context struct for the current `yyparse()` call |

## Cross-module interfaces

- **0042b1d5** (outside this range, earlier module - fixup.c or object.c by address) - per-item
  cleanup callback invoked by `free_reloc_table` (0042d229) while tearing down the third hash
  table; exact contract (what it frees / whether it can fail) unknown without reading that
  module.
- **0x409a25** (outside range, error/diagnostics module) - the generic "report a link error and
  continue" function; called by almost every parsing/range-check function in this module
  (`get_string`, `get_symbol`, `get_mem_spec`, `abi_report_error`, all `abi_func_*`). Distinct
  from `0x4098b0` which `xmalloc`/`xrealloc` call for the fatal "Out of memory" case (does not
  return) and from `yy_fatal_error`'s direct `fprintf`+`exit(2)`.
- **0x42b1d5** - see above.
- **Callers into this module from elsewhere**: `ext_lookup` (0042c8ba) is called from six
  addresses outside this range (0x40af6e, 0x41006f, 0x423863, 0x425470, 0x42b005, plus
  0x437e46 inside this range) - i.e. the linker's core symbol-resolution/fixup logic in other
  modules depends directly on this module's hash tables. `abi_expr_eval`/`abi_expr_eval_impl`
  (0x43a260/0x43a289) are called from 0x416cf8 and 0x410668 - wherever DSPLNK evaluates an ABI
  expression string (likely while processing a `-abi`/memory-map description file, outside this
  assignment). `abi_free_all` (0x43a394) is the only function here called directly from
  `main()` (0x402e52 in dsplnk.c), at program exit/cleanup.

## Quirks worth reproducing

- **Two independent OOM behaviours** in the same module (`xmalloc`'s "Out of memory - link
  aborted" + no-return, vs. InfArray `grow()`'s "Cannot alloc array\n" + `exit()`) - do not
  unify them when porting; keep the exact wording and exact function (`exit()` vs the shared
  fatal-error reporter) for each path.
- **2003-bucket hash tables** (`0x7d3`) vs. ASM56000's 1009-bucket tables for the conceptually
  same job - not a bug, but a divergence to preserve byte-for-byte (hash chain order affects
  nothing externally visible here since these are internal symbol tables, but keep the modulus
  exact in case any diagnostic dump - e.g. the unused-looking InfArray `dump()` functions -
  is ever enabled).
- **`round_up_pow2`** (0x430b53) is byte-identical to a routine ASM56000 happens to have at an
  address that the automatic module-mapper attributes to its unrelated "debug" module
  (`re/out/DSPLNK/xmatch_ASM56000.txt:48`); this is very likely MSVC/compiler-generated
  boilerplate or a tiny utility duplicated by hand in two unrelated places, not evidence that
  DSPLNK's util.c and ASM56000's debug.c share a source file. Do not read anything into that
  particular xmatch beyond "the machine code happens to be identical".
- **`abi_mask_then_shift`** silently reports an error string but the return value on the error
  path was not verified to be a safe/neutral value - check the disassembly before relying on it
  when reimplementing (`x86dis.py re/bin/DSPLNK.EXE 0x435f5a 0x435f9f`).
- The InfArray `dump()` functions print to **stdout via `printf`**, unlike essentially
  everything else in this module which uses `fprintf(stderr, ...)` for diagnostics - if ever
  reachable (no caller found in this range), this would interleave with normal DSPLNK stdout
  output in an unusual way.
- `abi_assign_op` (0x4358ea) calls `exit(1)` directly (not through a shared fatal-error path) on
  an unrecognised assignment operator - another distinct process-termination style to preserve.

## Open questions for later passes

1. Exact 1:1 correspondence between each of the ~40 `F#W#[O#]` format-code strings and its
   `abi_pack_NN` (0x436855-0x437427) implementation - needs either dynamic tracing of
   `abi_form_table_init` (0x436210) or a careful string-load-to-call-argument trace through its
   1605-byte disassembly.
2. True owner of the third 2003-bucket hash table at `&DAT_00463f48` (`free_reloc_table`/
   `free_reloc_table_entries`) - the per-item cleanup callback it invokes (0x42b1d5) lives
   outside this assignment's range; whichever group covers fixup.c/object.c should confirm.
3. Exact operator identity for `op_and`/`op_or`/`op_uadd`/`op_usub`/`op_uxor` (0x4357f0,
   0x435817, 0x4358aa-0x4358c0) - bodies were not individually disassembled beyond signature +
   call graph; likely bitwise `&`/`|` and something else respectively, given the surrounding
   relational-operator sextet (`op_eq`..`op_ge`, high confidence) is complete and unambiguous.
4. Whether clusters 3 (COFF->ELF writer) and 4 (ABI subsystem) should become their own
   `src/dsplnk/*.c` files rather than being folded into `util.c` when reconstruction begins -
   recommended given they are clearly separate source-level concerns (see "Module boundaries").
5. `abi_conv_case1..4` (0x4387f2/0x438889/0x43891b/0x4389ab) - the specific DSP/ABI data types
   being converted between (word/byte/long/float?) were not identified with confidence; only
   `abi_conv_case4`'s 64-bit sign-extension behaviour stood out.

## Summary

- **271/271 functions named** in `re/names/DSPLNK/l4_util.names.txt` (12 `high`-confidence
  byte-identical xmatches with ASM56000, plus behavioural/string-based matches; remainder
  named systematically by cluster with `low`/`med` confidence where the exact role could not be
  fully pinned down - see the table above for the full breakdown with one-line descriptions).
- **37 globals named** (`D` rows in the same file): the three symbol hash tables, sort/parse
  cursors, the COFF->ELF writer's file/section state, and the ABI subsystem's persistent table
  instances and parse-context pointer.
- **Main data structures documented**: the generic 12-function `InfArray` container (4
  instantiations: `LONGInfArray`/`symtableInfArray`/`ABI_mp_symtblInfArray`/`formtableInfArray`),
  its element layouts, the ELF32 writer's section-record list, and the field-bit-packing
  (`F#W#[O#]`) table.
- **Main open finding**: the assigned 271-function "util" range actually spans at least four
  source-level concerns - genuine util.c (~85 functions), a COFF->ELF converter (~35), and a
  self-contained ABI expression-language subsystem including a Flex/Bison-generated
  lexer/parser (~150) - none of which carry their own `$Id` string, which is why the automatic
  module mapper folded them all into "util".
