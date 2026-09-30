# g2_symtab notes: sdi.c, section.c, symtab.c, util.c (ASM56000.EXE, CLAS56 v6.3.0)

Sources: `re/out/ASM56000/mod/{sdi,section,symtab,util}.c`, disassembly spot checks,
names in `re/names/ASM56000/g2_symtab.names.txt` (all function names below are from
there). Tests assembled with `re/bin_ft/ASM56000.EXE` live in
`re/notes/ASM56000/scratch_g2_symtab/` (`s1.asm` sections/XDEF/XREF/GLOBAL + `.cln`
dump, `r.asm` redefinition errors, `f.asm` float formatting, `t3.asm`/`t4.asm` `-j`).

Revisions ($Id): sdi.c 1.18 (1995/10/05), section.c 1.31 (1999/01/29), symtab.c 1.39
(1999/07/02), util.c 1.41 (1999/06/04).

## 0. Module boundaries (corrected)

`modules.txt` split the address range 0x433cb0-0x43dcc6 into 11/21/15/139 functions.
The `$Id` string is the first object of each module's `.data` (sdi 0x458960, section
0x458ac8, symtab 0x459398, util 0x459568), so every string a function uses tells its
module. That moves the boundaries:

| module | range | functions | evidence |
|---|---|---|---|
| sdi.c | 0x433cb0-0x4351bf | 13 | `sdi_branch_mnemonic` uses "jmp"/"bra" at 0x458ac0/c4, i.e. *before* section's $Id; `sdi_free` only touches SDI data |
| section.c | 0x4351c0-0x43770f | 21 | `sec_check_xdef` strings 0x4592f4..0x45937c < symtab $Id |
| symtab.c | 0x437710-0x43975f | 42 | `fref_next` string 0x459544 < util $Id; `sym_define` strings 0x4593d0.. > symtab $Id |
| util.c | 0x439760-0x43dcc6 | 110 | `str_dupcat` string 0x45959c > util $Id |

The names file's module column was corrected accordingly (the symtab/util cut
between 0x439374 and 0x439760 is certain; the string-less functions in between -
`strtab_free` .. `misc_list_free` - free symtab.c structures and were put in symtab.c).
Function order inside a module is the source order.

## 1. Module purposes

- **sdi.c** - span-dependent instruction ("SDI") optimisation: records every
  branch/jump whose short or long form depends on a label distance, resolves the
  forms iteratively after pass 1 and shifts label values. Enabled only by the hidden
  `-j` option (`sdi_enabled`, 0x45eb34). **In the shipped binary `-j` crashes on any
  input** ("ASM56000: Fatal segmentation or protection fault", exit 127), see 7.1, so the
  whole module is effectively dead but must exist.
- **section.c** - `SECTION`/`ENDSEC` and the section stack, the per-section
  `LOCAL`/`GLOBAL`/`XDEF`/`XREF` name lists and their checks against the symbol table,
  switching the run/load location counters when the current section changes, `.bs`/`.es`
  debug symbols.
- **symtab.c** - the symbol table proper (hash table, local-label blocks, macro locals,
  definition/lookup/scope resolution, cross-reference lists), the external-symbol table,
  the COFF string-table hash lookup, SDI value adjustment, lookups in the static tables
  (mnemonics, directives, OPT names, processors, revisions, SCS and debug directives,
  condition codes), the forward-reference sequence list and the end-of-pass free routines.
- **util.c** - grab bag: string/memory helpers (`xmalloc`...), binary search and the
  project quicksort, `hash_name`, memory-space parsing (`X:`, `EM`, `(ctr)`, maps),
  forcing operators `<`/`<<`/`>`, quoted-string/substring parsing, symbol-name scanning,
  bit-field insertion (numeric and as linker expression text), double formatting,
  byte-swapped object writes, location-counter overflow checks, plus several dead
  subsystems (generic stack, instruction list `ilist`/`ifix`, `lbl_list`, `darray`).

## 2. Structures

All offsets in bytes, all fields 4 bytes (int/long/pointer) unless noted. Allocation
is always `xmalloc` (`0x439857`, fatal "Out of memory - assembly aborted").

### 2.1 Symbol table entry `struct sym` - 0x60 bytes, `xmalloc(0x60)` in `sym_define` (0x437a9f)

| off | field | meaning / evidence |
|---|---|---|
| 0x00 | `name` | malloc'd copy; a local label is stored **without** its leading `_`; lower-cased when `OPT IC`. |
| 0x04 | - | never written by symtab.c (garbage from malloc). |
| 0x08 | `val[0]` | integer: sign byte of the 56-bit value (expr `W0`); float: low word of the double. |
| 0x0c | `val[1]` | integer: bits 47..24 (`W1`); float: high word of the double. |
| 0x10 | `val[2]` | integer: bits 23..0 (`W2`) - the "value" everyone reads (SDI adjust, phasing check, COFF `n_value`). Only copied when flag 0x100 (int); for floats only +8/+0xc are copied. |
| 0x14 | - | unused (expr `W3` slot). |
| 0x18 | `flags` | see table below; initialised to expr `W6 | W4` (type 0x100/0x200 merged into the flag word). |
| 0x1c | `space` | memory space (expr `W7`); SET symbols get 4 (none) unless `OPT SMS`. |
| 0x20 | `map` | memory map (`W8`), 4 for SET without SMS. |
| 0x24 | `counter` | location counter selector (`W9`), 0 for SET without SMS. |
| 0x28 | `emi` | EMI/secondary (`W10`), 0 for SET without SMS. |
| 0x2c | `buffer` | buffer number (`W17`); checked against `buffer_num` in `sym_lookup_local` ("Reference outside of current buffer"). |
| 0x30 | `overlay` | overlay number (`W18`); "Reference outside of current overlay". |
| 0x34 | `coff_scn` | COFF section index of the load counter (`W21` = `ld_counter_obj->scnum`); **re-written in pass 2** on every (re)definition; used as `n_scnum` by `obj_add_symbol` (`FUN_00424817`). |
| 0x38 | `sdi_cnt` | SDI records in the current group before the definition (`group->count`) or 0; `sdi_adjust_symbols` adds `table[sdi_cnt-1].cum_long`. |
| 0x3c | `sdi_cnt2` | `group->count2` snapshot. |
| 0x40 | `section` | `cur_section` at definition (listing "Section" column, `W15` = `section->number`). |
| 0x44 | `ctr_section` | `ctr_section` at definition (`W16` = its number). |
| 0x48 | `sdi_group` | `ctr_section->sdi_cur`. |
| 0x4c | `sdi_mark` | `ctr_section->sdi_mark_cur` if run==load counter and the mark is non-empty, else 0. |
| 0x50 | `refs` | cross-reference list, appended at the tail (2.8). |
| 0x54 | `dbg_sym` | 32-byte staged COFF symbol from debug.c (`DEF`...`ENDEF`), freed by `sym_free_all`. |
| 0x58 | `dbg_aux` | 32-byte staged aux record, same. |
| 0x5c | `next` | hash-chain / local-block chain link. |

`parse_term` (eval.c 0x41518e, lines 1384-1410) copies: +8/+0xc/+0x10 -> `W0..W2`,
+0x1c..+0x28 -> `W7..W10`, `flags & 0x7000` -> `W6`, `section->number` -> `W15`,
`ctr_section->number` -> `W16`, +0x2c -> `W17`, +0x30 -> `W18`, +0x38 -> `W19`,
+0x3c -> `W20`, +0x34 -> `W21`. `sym_define` copies the reverse way.

Symbol flag bits (+0x18):

| bit | meaning | evidence |
|---|---|---|
| 0x10 | SET symbol (SET/GSET; redefinable) | `pseudo_set` ORs 0x10 into `W6`; `sym_set_value` requires it |
| 0x20 | local label (`_name`) | `sym_define` |
| 0x40 | GLOBAL (visible from all sections) | `sec_check_global`, listing "GLOBAL" |
| 0x80 | XDEF'd (exported; listing "EXTERN", COFF class 211) | `sym_define`, `obj_add_symbol` |
| 0x100 / 0x200 | integer / floating value | from `W4` |
| 0x400 | defined by EQU | `pseudo_equ` (pseudo.c l.3467); with `OPT CONST` such symbols are not written to the object file |
| 0x800 | 48-bit (long) value (`W5 == 6`) | `sym_define`, `sym_set_value` |
| 0x1000 | relocatable | `W6` |
| 0x2000 | defined inside a BUFFER (`in_buffer != 0`) | `sym_define_label` |
| 0x4000 | defined while run != load counter (overlay) | `sym_define_label` |
| 0x8000 | defined more than once (set in pass 1) | `sym_define` |
| 0x40000 | SCS-generated label (`Z_L`/`z_l` prefix, 3 chars) | `sym_define` |

### 2.2 Hash tables

Four tables of **1009 (0x3f1) bucket heads**, all indexed by `hash_name` (2.10):

| table | addr | node | chain |
|---|---|---|---|
| `sym_hash` | 0x45fcc0 | `struct sym` (2.1) | +0x5c, singly linked |
| `ext_hash` | 0x461c50 | `struct ext` (2.3) | +0x10 next, +0xc prev |
| `strtab_hash` | 0x462c18 | 8 bytes `{long offset_in_strtab_buf; next}` (created by procop.c `strtab_add` 0x42456e) | +4 |
| `lbl_index_hash` | 0x45da48 | 0xc `{name, darray *, next}` | dead (2.12) |

g5's `define_symtab` (0x460c88, DEFINE/UNDEF table) uses the same `hash_name`, so it
also has 1009 buckets (0x460c88..0x461c50 = 4040 bytes); g5_pseudo.md's "324 buckets"
is an arithmetic slip.

**Insertion order** (matters for the listing because the listing sort is not stable,
see 7.3): lookups leave a cursor at the *last node visited*: `sym_insert_pt`
(0x45fc34, set by `sym_lookup`/`sym_search`), `ext_insert_pt` (0x45fc54, `ext_lookup`),
`strtab_insert_pt` (0x45fc58, `strtab_lookup`). A new node is linked **after** that
node (`new->next = pt->next; pt->next = new`), or becomes the bucket head when the
bucket was empty. After an unsuccessful full scan the cursor is the tail, so new
names are appended. But `sym_search` stops early on a same-section match, and
`sym_define` may then reject that match (visibility rules, 3.3), so a new entry can be
inserted in the middle of a chain, right after the rejected same-name entry.

### 2.3 External symbol `struct ext` - 0x14 bytes, `ext_add` (0x43896d)

| off | field | meaning |
|---|---|---|
| 0x00 | name | malloc'd, lower-cased with `OPT IC` |
| 0x04 | flags | 0x40 or 0x80 (0x80 when `!OPT XR` and the name is in the XREF list, or forced); an existing 0x40 entry is changed to 0x80 by a later forced add |
| 0x08 | section | `cur_section`; `ext_lookup` matches name **and** section |
| 0x0c | prev | previous node in the chain (0 for the head) |
| 0x10 | next | |

Created only in relocatable mode (fatal "Attempt to store external reference in absolute
mode" otherwise; the local prefix `_` returns 0). Each new entry is emitted to the COFF
symbol table immediately via procop.c `FUN_00424b1a` and counted in `num_ext_symbols`.

### 2.4 Section `struct section` - 0x90 bytes, `sec_new` (0x435a59); the global section is the static object `global_section` at 0x44f878

| off | field | meaning |
|---|---|---|
| 0x00 | - | not initialised by `sec_new` (0 in `global_section`). |
| 0x04 | name | malloc'd (the global section points at the static "GLOBAL" 0x44f868). |
| 0x08 | number | 1..255 in creation order (`section_count`), 0 = global. Fatal "Too many sections in module" above 255. |
| 0x0c | flags | 0x08 being created; 0x10 STATIC; 0x20 LOCAL; 0x40 GLOBAL; 0x4000 saved "overlay" (run != load); 0x10000 saved run counter relocatable; 0x20000 saved load counter relocatable (`sec_new` sets 0x30000 in relocatable mode); 0x200000 DEBUG. |
| 0x10 | reloc_list | 0x10-byte nodes `{space, counter, char which, char reloc, next@0xc}` made by pseudo.c `FUN_0042dd26`; `pseudo_mode` rewrites byte +9 of each. |
| 0x14 / 0x18 | rt_ovf[abs] / ld_ovf[abs] | saved overflow flag (0x400) of the run / load counter, absolute mode |
| 0x1c / 0x20 | rt_ovf[rel] / ld_ovf[rel] | same, relocatable mode. Index = `reloc * 8`. |
| 0x24 | rt_spec[abs] | 4 longs `{space, map, counter, emi}` saved run counter spec |
| 0x34 | ld_spec[abs] | load counter spec |
| 0x44 | rt_spec[rel] | |
| 0x54 | ld_spec[rel] | index = `reloc * 0x20` |
| 0x64 | counters | circular list of location-counter objects (`struct counter`, 0x30 bytes, pseudo.c `org_new_counter`; +0x28 prev, +0x2c next, +0x24 -> 0x34-byte COFF section header record, `rt_pc` = &hdr->s_vaddr) |
| 0x68 | sdi_groups | list of `struct sdi_group` (2.5), newest first |
| 0x6c | sdi_cur | current SDI group |
| 0x70 | sdi_marks | list of `struct sdi_mark` (2.5), dummy head |
| 0x74 | sdi_mark_cur | tail in pass 1, cursor in pass 2 |
| 0x78 | xdef_list | 8-byte name nodes `{char *name; next}`, newest first |
| 0x7c | xref_list | same |
| 0x80 | local_list | same |
| 0x84 | global_list | same (only built in pass 1, see 3.2) |
| 0x88 | ctr_sec | section whose location counters are in use (self by default; the enclosing counter section for STATIC; see LOCAL in 3.2) |
| 0x8c | next | section list link (creation order, head = `global_section`) |

This contradicts nothing in g6: the "13-word section header" that `obj_pack_section_headers`
copies is the 0x34-byte record behind `counter+0x24`, not this struct.

Section stack node: 8 bytes `{struct section *sec; next}` (`sec_push`), head
`section_stack` (0x45fb84), depth `section_depth` (0x45eba8).

### 2.5 SDI structures (sdi.c)

`struct sdi_group` - 0x24 bytes, `sdi_select_group` (0x433e78); one per (counter section,
P-space counter number):

| off | field | meaning |
|---|---|---|
| 0x00 | key | run counter number (`rt_counter`, 0x45f8a8) |
| 0x04 | count | pass 1: records; after `sdi_build_table` 0; pass 2: cursor into table |
| 0x08 | count2 | pass 1: named records (`sdi_record` with target); pass 2: forms consumed |
| 0x0c | nentries | table size |
| 0x10 | nlong | long forms chosen in pass 2 (added to counter pcs by `org_select_counter`) |
| 0x14 | - | |
| 0x18 | records | list of `struct sdi_rec`, newest first (via +0x24) |
| 0x1c | table | `xmalloc((count+1)*0x1c)` array of `struct sdi_ent` |
| 0x20 | next | |

`struct sdi_rec` - 0x28 bytes, `sdi_record` (0x434023): +0 target name (malloc, `<`
stripped) or 0; +4 pc (`*rt_pc`); +8 range1; +0xc range2; +0x10 flags; +0x14 local block
number (-1 = none); +0x18 local block / macro-local node; +0x1c `cur_section`; +0x20
copy of the section stack (8-byte nodes) when `OPT NS`; +0x24 next.

`struct sdi_ent` - 0x1c bytes: +0 pc; +4 target value; +8 distance (target-pc); +0xc
range1; +0x10 range2; +0x14 flags; +0x18 cumulative number of long forms up to and
including this entry.

SDI flags: 1/2/3 = kind (1 pc-relative, 2 absolute, 3 either); 0x100 long form; 0x200
"middle" form (absolute too big but range2 fits); 0x1000 GSET mode at record time;
0x2000 no target (always counted, never optimised); 0x4000 target is a SET symbol;
0x8000 short form forced with `<`; 0x10000 target undefined / not optimisable;
0x20000 run counter relocatable.

`struct sdi_mark` - 0xc bytes, `sdi_mark_section` (0x433f67): `{group, count, next}`;
`count` is set to `group->count` by `sdi_record` when run != load counter.

### 2.6 Local-label blocks

`struct local_block` - 0xc bytes, `sym_new_local_block` (0x4382bb): `{long number;
struct sym *first; next}`. List `local_block_list` (0x45fc3c) / tail `local_block_last`
(0x45fc44), current `cur_local_block` (0x45fc40), number counter `local_block_num`
(0x45eb68). Each block holds the `_` labels defined between two non-local labels.

Macro locals: nodes of the same shape in `macro_local_list` (0x45fc48; node +0 =
listing line of the expansion, written by macro.c l.1399/1410), current
`cur_macro_local` (0x45fc4c); the chain head is also stored in the macro context
(`cur_macro + 0x20`). (g6 calls these `Macro_lineno_head/cur`; same objects.)

### 2.7 Forward-reference sequence list

Circular list with static sentinel `fref_head` (0x44f990): 0xc-byte nodes `{long
ref_seq; long file_line; next}`. `fref_add` (pass 1) inserts after the cursor
`fref_cur` (0x45fc70) `{sym_ref_seq, file_line_num}`; `fref_rewind` (pass 2 start)
resets the cursor; `fref_next` checks `cur->file_line == file_line_num` (fatal
"Forward reference sequence failure") and advances. Used by `parse_term`,
`fn_def_or_mac`, `dbg_symbol_begin`.

### 2.8 Cross-reference node - 0xc bytes, `sym_add_ref` (0x4388eb)

`{long lst_line; long type; next}`, appended at the tail of `sym->refs`; type 1 =
definition (listing prints `*`), 2 = use. Added only in pass 2, only with `OPT CRE`,
and never while `in_line_replay` (DO-loop line replay). Uses the **listing** line
number (`lst_line_num`, 0x45eb80) - verified in `s1.lst`: XDEF/GLOBAL/XREF directives
count as uses, every SET is a definition.

### 2.9 Static tables searched here (layouts per g1_main.md 1.1-1.5)

| finder | table | count | elem | compare |
|---|---|---|---|---|
| `find_mnemonic` | `mnemonic_tab` 0x44e0b0 | `mnemonic_count` (142) | 20 | `mnemonic_cmp`: strcmp; equal but entry byte +4 bit 0x80 -> returns 1 (hidden) |
| `find_directive` | `directive_tab` 0x44fab0 | 75 | 8 | `directive_cmp` (same 0x80 rule); result with code byte `'0'` (0x30) hidden unless `-t` |
| `find_option` | `option_tab` 0x44fd10 | 92 | 8 | strcmp |
| `find_revision` | 0x44ec70 | 4 | 12 | strcmp |
| `find_processor` | 0x44eca8 | 7 | 8 | strcmp |
| `find_scs_directive` | 0x4503b0 | 13 | 12 | strcmp on `name+1` (skips the `.`) |
| `find_debug_directive` | 0x450450 | 16 | 8 | strcmp after skipping the first char and following digits |
| `find_condition` | 0x44ebd0 | 19 | 8 | strcmp |

`find_mnemonic`/`find_directive(name, chk_macro)` return 0 when `chk_macro` and a macro
of that name exists (`mac_lookup(name, 2)`) - macros override instructions. All
comparators return strcmp's int (Ghidra shows `void`).

### 2.10 `hash_name` (0x439b65) - ELF/PJW hash

```c
unsigned long h = 0, g;
for (; *s; s++) {
    h = (h << 4) + (long)(signed char)*s;     /* char is sign-extended! */
    if ((g = h & 0xf0000000UL) != 0)
        h ^= (g >> 24) ^ g;                   /* == ELF: h ^= g>>24; h &= ~g */
}
return h % 1009;                               /* unsigned 32-bit arithmetic */
```
Keep the sign extension (bytes >= 0x80) and mask to 32 bits on 64-bit hosts.

### 2.11 Instruction list (dead): `ilist` 0x44-byte entries, `ifix` 0x20-byte entries

`ilist_tab` (0x464ecc) grows by 1000 entries (68000 bytes): +0 id, +4 pc, +8 counter,
+0xc target, +0x10/+0x14 64 attribute bits (46 named `ia_*` in `ia_attr_names`
0x459db0, e.g. `ia_inst_do`, `ia_insert_nop`). `ifix_tab` (0x464edc) grows by 20
entries: +0 key, +4, +8 type (0x25..0x2b in `ifix_apply`), +0xc name, +0x10 pc, +0x14
counter, +0x18, +0x1c. No code creates entries (`ilist_new`/`ifix_new` have no
callers), so `ilist_count` stays 0 and every consumer is a no-op; `ilist_dump` writes
"instlist.out"; `ilist_run_checks` calls 41 function pointers at 0x465a34 that overlap
the COFF staging buffers. A pipeline-restriction checker for another DSP compiled out.

### 2.12 Other dead helpers

`lbl_list` (0x464ee0, 0x10-byte `{name, value, next, prev}` nodes: `lbl_list_add` has
no callers, so `sym_define`'s pass-0 lookup never matches); `lbl_index_*` (hash of
names -> `darray`; `lbl_index_label` has no callers, only `lbl_index_free` runs);
`darray` (0x20 bytes: `{cap, count, data, fn append@0xc, set@0x10, get@0x14, init@0x18,
destroy@0x1c}`, grows by 100); generic stack (`stack_create`, 0x14 bytes `{top, count,
push@8, init@0xc, pop@0x10}`, 8-byte nodes); `misc_list` (0x45fc74, never filled).

## 3. Functions

### 3.1 sdi.c (13)

- `0x433cb0 sdi_operand(char *op)` -> pointer to the branch target name or 0. Returns 0
  unless `sdi_enabled`, not `in_buffer`, not `in_line_replay` and (absolute mode, or run
  and load counters both relocatable). Operand must start with a letter, `_` or `#`;
  in pass 2 returns 0 when the group's current entry has 0x4000. Skips `#`, sets
  `sdi_local_target` for `_`, accepts `[A-Za-z0-9_]*` followed by NUL or `,`.
- `0x433e78 sdi_select_group(long counter)` - find the group of `ctr_section` with that
  key or create one (pass 2: fatal "SDI list sequence failure"); becomes `sdi_cur`.
  Called from `sec_set_current` when the run space is P.
- `0x433f67 sdi_mark_section(void *sec)` - pass 1: append a mark `{sec->sdi_cur,0,0}`
  (creating a dummy head first); **any other pass: `sec->sdi_mark_cur =
  sec->sdi_mark_cur->next`** (crash when NULL, see 7.1).
- `0x434023 sdi_record(char *target, long range1, long range2, unsigned long flags)` - new
  `sdi_rec` pushed on `sdi_cur->records`; with target: strip `<` (flag 0x8000), copy,
  add 0x1000 (GSET mode) / 0x20000 (run reloc), capture local-block scope, the section
  and (OPT NS) a copy of the section stack; `count++`, `count2++`; overlay: mark->count
  = count. Without target: flag 0x2000, `count++`.
- `0x4342fb sdi_next_form(void)` -> 0 short, 1 middle, 2 long (2 also when no group).
  Pass 2 consumer: takes `table[count++]`, `count2++`; warns "SET symbol used as
  span-dependent instruction operand - using long encoding" (0x4000) and "Instruction
  operand too large to use short - long substituted" (long + 0x8000); for long forms
  bumps `rt_counter_obj->hdr+0x18` (and the load one) and `nlong`.
- `0x434430 sdi_optimize(void)` - for every section and group with records:
  `sdi_build_table`, `sdi_resolve`; then `sdi_adjust_symbols`. Called by `run_default`
  / `run_cmode` between the passes when `-j`.
- `0x43449c sdi_build_table(void *grp)` - array of `count+1` entries filled from the end,
  so table order = source order; target resolved by `sdi_find_target` (with
  `no_errors` set); undefined -> 0x10000; defined and not SET and not run-relocatable ->
  target/distance; otherwise 0x10000. Frees the records; `nentries = count`, `count =
  count2 = 0`.
- `0x4346c2 sdi_resolve(void *grp)` - fixpoint loop, see 7.2.
- `0x4349d5 sdi_find_target(void *rec)` -> sym or 0. Restores the record's context
  (`cur_section`, GSET mode, section stack/`opt_ns`, local block) and calls `sym_search`;
  marks 0x4000 when the symbol is SET.
- `0x434be7 sdi_expr(char *mnem, long flags, long r1, long r2, void *op1, void *op2)` -
  replaces `op1->text(+0x40)` with the linker expression
  `@SDI(%s,$%04lX,$%0*lX,$%0*lX,%d,$%0*lX,%s,%s)` (mnem, flags, r1, r2, prefix length,
  op2 value (+4), op2 text (+0x44), old op1 text), frees the operands' texts, counts
  the SDI in the group, calls procop `FUN_004247b1(reloc_count)` and increments
  `sdi_expr_count` (linker header `sditot`). Operand records are procop/encode
  structs (g4), not `EXPR_VAL`.
- `0x434d60 sdi2_expr(...)` - three-operand form `@SDI2(...)`; no callers.
- `0x434f48 sdi_free(void)` - frees every group, record (name, stack copy) and table;
  second loop over `global_section.sdi_groups` (0x44f8e0) is redundant (already
  freed/NULL). Called by `end_prepass`/`end_pass`.
- `0x4350d3 sdi_branch_mnemonic(void)` -> instruction entry of the short-branch
  equivalent of the `j...` opcode in `fld_opcode`: `jmp`->`bra`, else first letter
  `j`->`b` (`jcc`->`bcc`). No callers.

### 3.2 section.c (21)

- `0x4351c0 sec_section(char *name, char *mod1, char *mod2)` -> 1/0. `check_symbol`
  (-1 silent fail, 0 "Missing section name"); `_`-prefixed, "GLOBAL", "RESERVE" ->
  "Invalid section name". `OPT IC` lower-cases. Default attributes `OPT GL` -> 0x40,
  `OPT GS` -> 0x10; modifiers (lower-cased) `global` 0x40, `static` 0x10, `local` 0x20,
  `debug` 0x200000, else "Invalid section directive modifier" (see 7.6). Existing
  section (name search from `global_section->next`): `sec_push`,
  `sec_save_counters`, reset 0x70 and apply modifiers, `sec_set_current`. New
  (pass 1 only, pass 2 -> "Section not encountered on pass 1"): push, save, `sec_new`,
  number = ++`section_count`, flags = mods|8, `.bs` symbol unless LOCAL, `ctr_sec` = self
  or (STATIC) current `ctr_section`, `sec_set_current(sec,1)`, append to the section
  list, clear 8. LOCAL: `cur_section` is restored to the enclosing section and the
  enclosing section's `ctr_sec` is set to the new section (symbols stay in the outer
  section, only the counters change; `local_sec_parent` 0x45fb7c remembers it). In
  relocatable mode `ld_counter_obj->nsyms` (+0x20) is incremented; absolute mode clears
  0x1000 in `ld_counter_obj->flags`.
- `0x435924 sec_endsec(void)` - "ENDSEC without associated SECTION directive" when the
  stack is empty (also sets `optr = 0`); `.es` unless the counter section is LOCAL; from
  the stack top picks the first non-LOCAL entry as new current section and the first
  non-STATIC as its counter section (fatal "Section stack mode error"), saves counters,
  `sec_set_current(sec,0)`, pops, `section_depth--`. Also called from `init_pass`,
  `end_prepass`, `end_pass`.
- `0x435a59 sec_new(char *name)` - allocate/initialise 2.4 (flags 0x30000 in relocatable
  mode, `ctr_sec` = self), `sdi_mark_section` when `-j`.
- `0x435c1a sec_push(void *sec)` - pushes the effective current section (the counter
  section if that is LOCAL, else `cur_section`); "Cannot nest section inside itself" if
  `sec` is it or already on the stack (two identical strings). `section_depth++`.
- `0x435cde sec_debug_sym(void *sec, int begin)` - `pass != 1` (pass 2; the pre-pass,
  pass 0, also passes the test), relocatable or `-g`: stages
  COFF symbol `.bs`/`.es` (n_value = string-table offset of the section name for `.bs`,
  0 for `.es`; mspace 4, n_scnum -1, class 201 A_SECT, 1 aux) and aux `{section number,
  file_line_num}`, written with procop `FUN_0042447e`. Confirmed in `s1.cln`.
- `0x435d9f sec_save_counters(void)` - stores run/load spec and overflow flags into
  `ctr_section`'s slots for the current `rt_reloc`/`ld_reloc`, and the modes into its
  flags (0x10000, 0x20000, 0x4000).
- `0x435eca sec_set_current(void *sec, int is_new)` - `cur_section = sec`,
  `ctr_section = sec->ctr_sec`; unless `sec` is STATIC: modes from the counter section's
  flags (`is_new`: both = `reloc_mode`, no overlay). Loads the run spec/overflow,
  `rt_counter_obj = org_select_counter(ctr, &rt_space, rt_reloc?0x1000:0 |
  overlay?0x4000:0, 0)`, `rt_pc = &obj->hdr->vaddr`, `rt_pc_start`, bounds via
  `org_get_bounds(0x22 lo / 0x1c hi, ...)`, `sdi_select_group` if P space; same for the
  load side if overlay, else load = run.
- `0x4361d3 sec_free_all(void)` - frees every section except `global_section`, its
  counters, SDI lists, name lists, reloc list; resets the list and `section_count`.
- `0x4364a5 sec_local(void)`, `0x4366be sec_global(void)`, `0x4368c3 sec_xref(void)`,
  `0x436b2e sec_xdef(void)` -> 1/0 - directive handlers: "<DIR> without preceding
  SECTION directive" in the global section, "Missing symbol name", `check_fields(1)`,
  then for each `get_symbol()` separated by `,` ("Syntax error in symbol name list"):
  `_` names -> "Local symbol names cannot be used with <DIR>"; name already in one of
  the four lists -> "Symbol already defined as LOCAL/GLOBAL/XREF/XDEF" (GLOBAL only
  in pass 1 for GLOBAL itself); then the `sec_check_*` test and, if it passes, push a
  name node on the list. LOCAL additionally rejects a GLOBAL section ("LOCAL directive
  not valid in global section"); GLOBAL adds only in pass 1; XREF increments
  `ld_counter_obj->nsyms` and in pass 2 with `-g` and an object file stages a `.xr`
  symbol (n_value = strtab offset, n_scnum = `ld_counter_obj->scnum`, class 212).
- `0x436d1b sec_is_local`, `0x436d85 sec_is_global`, `0x436def sec_is_xref`,
  `0x436e56 sec_is_xdef (char *name)` -> 1 if the name is on the current section's list
  (always 0 in the global section).
- `0x436ebd sec_check_local(char *name)` - search `sym_hash` for the name in
  `cur_section`: not found -> pass 2 "Symbol undefined on pass 2", return 1; found with
  0xc0 -> "Symbol already defined as global"; relocatable + SET -> "SET symbol names
  cannot be used with ..."; else xref-use (pass 2, CRE).
- `0x437037 sec_check_global(char *name)` - found in `cur_section`: without `c_mode`
  and not yet 0x40 -> "Symbol defined in current section before GLOBAL directive"; SET
  check; sets 0x40; ref. Found elsewhere with 0x40 -> "Symbol already defined as
  global". Not found in pass 2: absolute "Symbol undefined on pass 2", relocatable
  warning "Unresolved external reference" only with `OPT UR`.
- `0x437220 sec_check_xref(char *name)` - any same-name symbol in `cur_section` that is
  not SET -> "Symbol already defined in current section"; symbols with 0x80 (0x40
  with `OPT XR` or for SET) get a ref. End of chain in pass 2: absolute -> "Symbol
  undefined on pass 2" unless one matched; relocatable -> `ext_add(name,1)` unless the
  *last* same-name symbol was SET, and "Unresolved external reference" whenever `OPT
  UR` (even if matched).
- `0x437418 sec_check_xdef(char *name)` - found in `cur_section`: must already carry
  0x80 (0x40 with `OPT XR`) unless the section is GLOBAL, else "Symbol defined in
  current section before XDEF directive"; SET check; ref. Found elsewhere with `OPT XR`
  and 0x40 -> "Symbol already defined as global".
- `0x4375e6 sec_free_names(void)` - frees the XREF, XDEF and LOCAL lists of all sections
  (not GLOBAL). Called by `init_pass`, `end_prepass`, `end_pass`, so XREF/XDEF/LOCAL
  lists are rebuilt in pass 2 while the GLOBAL list survives from pass 1.

### 3.3 symtab.c (42)

- `0x437710 lbl_index_add(char *)`, `0x437837 lbl_index_free(void)`, `0x4378e5
  lbl_index_find(char *)`, `0x43794f lbl_index_label(void)` - dead label index (2.12).
- `0x43797a sym_define_label(void)` -> 1 if `fld_label` is a valid symbol: runs
  `check_loc_counters(0)`, builds an `EXPR_VAL` on the stack (int, `W2 = *rt_pc`, W5 3,
  flags 0x1000 rt reloc | 0x2000 in buffer | 0x4000 overlay, run spec in W7..W10,
  W15/W16 section numbers, W17 `buffer_num` if in buffer, W18 `overlay_num` if
  overlay, W21 `ld_counter_obj->scnum`) and calls `sym_define`.
- `0x437a9f sym_define(char *name, void *val)` -> 1 ok / 0 error or "already known".
  Steps: (1) `flags = W6|W4`. (2) pass 0: dead `lbl_list` hook. (3) SET without `OPT
  SMS`: space/map/ctr/emi = 4,4,0,0. (4) `_` -> 0x20. Otherwise 0x40 if in the global
  section, the section is GLOBAL, the name is on the GLOBAL list, (`OPT XR` and on the
  XDEF list), or (SET and (GSET or on the XREF list)); else 0x80 if `!OPT XR` and on
  the XDEF list. `Z_L`/`z_l` prefix -> 0x40000, any other non-local name increments
  `local_block_num` (every call, both passes). (5) pass 1, not SET:
  `ld_counter_obj->nsyms++`. (6) `sym = sym_lookup(name, 1)`, then drop it unless
  visibility agrees: existing 0x40 needs new 0x40 (or SET on the XREF list), existing
  0x80 needs new 0x80, a plain one needs neither. (7) Not found: pass 2 -> 0 (error
  "Symbol undefined on pass 2" only for GSET outside the global section in relocatable
  mode); else counters (`num_symbols`, `num_zl_symbols`, `num_local_symbols` outside
  macros), create 2.1 (name without `_`, lower-cased with IC), SDI snapshot only if not
  SET and run space P, `sdi_mark` only when run == load. Insert: non-local and not
  `Z_L`-with-`OPT SCL` resets `cur_local_block`/`sym_local_tail`; after
  `sym_insert_pt`, or bucket head, or for locals `sym_new_local_block` (see 7.4).
  (8) Found: local-block bookkeeping (`local_block_cont`, advance `cur_local_block` on
  the first non-local label after locals, unless `Z_L` with `OPT SCL`). SET ->
  `sym_set_value`. Else pass 1: flag 0x8000, return 0. Pass 2: update +0x34; 0x8000 ->
  "Symbol redefined" (at **every** definition, verified `r.asm`), SET -> "Symbol
  already used as SET symbol"; else `obj_add_symbol` (procop `FUN_00424817`) when (not
  local or `OPT XLL`) and (not EQU or `!OPT CONST`) and (not `Z_L` or `OPT SCO`);
  relocatable P-space SDI labels get +0x38/+0x3c cleared; phasing check: int ok if
  `W2 == val[2]` or the symbol has SDI info (+0x38 or +0x4c); float ok if the doubles
  are equal; else "Phasing error".
- `0x4382bb sym_new_local_block(void *sym)` - outside a macro: new block `{local_block_num,
  sym, 0}` appended to the block list and made current; inside a macro (`cur_macro`):
  `cur_macro_local->first = sym`, `cur_macro+0x20 = sym`.
- `0x43835d sym_set_value(void *sym, void *val)` - needs flag 0x10 ("Symbol cannot be
  set to new value"); clears 0xf00, copies int (3 words, 0x100) or float (2 words,
  0x200), ORs 0x1000 relocatable and 0x800 long.
- `0x438441 sym_lookup(char *name, int reftype)` -> sym or 0. `sym_ref_seq++` unless
  replaying; IC lower-case; `_` -> `sym_lookup_local`; else `sym_insert_pt` = bucket head,
  `sym_search(name, reftype, 0)`; not found in pass 2: absolute "Symbol undefined on
  pass 2", relocatable "Unresolved external reference" (warning) with `OPT UR`; found
  in pass 2 with CRE: `sym_add_ref`. reftype: 1 definition, 2 use.
- `0x438583 sym_lookup_local(char *name, int reftype)` - name incl. `_`. Outside macros
  (or with the `^` operator, `outer_scope_ref`): only the current block if its number
  equals `local_block_num`; inside a macro: the chain `cur_macro+0x20`. Undefined in pass
  2 -> "Symbol undefined on pass 2" (name printed **without** the `_`); buffer/overlay
  mismatch with reftype 2 -> "Reference outside of current buffer/overlay". Sets
  `sym_local_tail` (0x45fc38) = cursor.
- `0x438713 sym_search(char *name, int reftype, int is_local)` - scope resolution, see 7.5.
- `0x4388eb sym_add_ref(void *sym, int reftype)` - 2.8 (no-op for reftype 0).
- `0x43896d ext_add(char *name, int force)` - 2.3.
- `0x438b28 ext_lookup(char *name)` - name+section match in `ext_hash`, sets
  `ext_insert_pt`.
- `0x438c00 strtab_lookup(char *name)` -> node or 0; names are at
  `strtab_buf + node->offset`; sets `strtab_insert_pt` (used by procop `strtab_add`).
- `0x438c80 sdi_adjust_symbols(void)` - for all symbols in `sym_hash`, the local blocks
  and macro locals: `val[2] = (val[2] + group->table[sdi_cnt-1].cum) & 0xffff` if
  `sdi_cnt`, then the same with the mark's group/count. 16-bit wrap.
- `0x438f1a find_mnemonic` .. `0x43928a condition_cmp` - 2.9. `0x438f9c
  str_lower_copy(char *)` lower-cases into the static 24-byte `lower_buf` (7.8).
- `0x4392a1 fref_free`, `0x439317 fref_rewind`, `0x439326 fref_add`, `0x439374 fref_next`
  - 2.7.
- `0x4393b2 strtab_free` (resets `strtab_size = 4`), `0x439431 sym_free_all` (clears
  `sym_insert_pt`, `num_symbols`, `num_zl_symbols`), `0x439547 sym_free_local_blocks`
  (also the macro-local symbols; `num_local_symbols = 0`), `0x439686 ext_free_all`,
  `0x439724 misc_list_free` - called by `end_prepass`/`end_pass`.

### 3.4 util.c (110) - grouped

Memory/strings:
- `0x439760 str_dupcat(char *s, ...)` - malloc'd concatenation of a NULL-terminated
  vararg list ("memory malloc failed" / "memory realloc failed" fatal); uses raw
  malloc/realloc.
- `0x439857 xmalloc(unsigned long)`, `0x439884 xrealloc`, `0x4398b5 xfree` (NULL-safe).
- `0x43b7aa str_upper`, `0x43b836 str_lower` (in place, return arg), `0x43b8c2
  str_upper_copy` (32 chars into `upper_buf`, dead), `0x439bd4 base_name` (after the
  last `\`, `/` or `:`), `0x43c9d4 split_string(str, delims, argv, max)` (strdup +
  strtok, malloc'd copies, returns count; used for `DSPASMOPT`).
- `0x43ca8c name_cmp` (dead), `0x43cab6 name_ptr_cmp` (qsort comparator on `*(char**)`,
  used by dspasm.c for the error-class table 0x44f6a0).

Search/sort/hash:
- `0x4398cc tab_search(key, base, count, size, cmp)` - binary search, returns element
  address or 0 (`mid = lo + ((hi-lo)/size >> 1)*size`, `cmp<0` -> `hi = mid-size`).
- `0x43994a tab_search_pos` - same, returns the insertion point; no callers.
- `0x4399c9 sort_ptrs(int lo, int hi)`, `0x439b25 sort_swap(i, j)` - the quicksort
  over `sort_array` (0x45fc80) with comparator `sort_cmp` (0x45fb60) used for every
  listing table (symbols, sections, macros, memory map, DSP host symbols). See 7.3.
- `0x439b65 hash_name` - 2.10.

Memory spaces (codes: P 0, X 1, Y 2, L 3, N/none 4, E(EMI) 0x1c, D 0x11d, special map
codes 0x11e..0x120; error sentinel 0xa2c2a):
- `0x439c56 get_mem_space(void *op, int allowed)` - optional `c:` prefix at `optr`
  (default 4) -> `op+4`; `allowed` 0 N, 1 X, 2 Y, 3 L, 4 P, 5 X/Y, 6 X/Y/L/P/N, 7 X/Y/N,
  8 Y/N, 9 X/Y/P/N; else one of the "Illegal memory space specified ..." /
  "Missing or illegal memory space specifier" errors.
- `0x439e8d get_mem_spec(long spec[4])` -> 1 / 0 (no `:` or bad space) / -1 - parses
  `space[m][map][ctr|(expr)|emi-number]:` for ORG/debug values into `{space, map,
  counter, emi}` (`EM`/`DM` two-letter spaces, counter via `(expr)` < 0x10000,
  `E<n>` EMI maps via `emi_map`); errors "Illegal memory map character", "Illegal
  memory counter specified", "Memory counter designator value too large", "Syntax
  error - expected ':'" / "')'".
- `0x43a6c5 mem_space_char(space)` - `P X Y L`, 0x1c `E` (processor level >= 3) else
  `N`, 0x11d `D` (level > 1 and variant >= 0x2000) else `N`, others `N`.
- `0x43a768 mem_space_index(space)` - bounds-table index: P 4, X 1, Y 2, L 3, E 5/0,
  D 6/0, else 0.
- `0x43a807 char_to_mem_space(c)`, `0x43a91e char_to_counter(c)` (d/n 0, l 1, h 2, else
  -1), `0x43a9d1 char_to_mem_map(c, c2, space)` (`:` plain, `e` external, `i` internal,
  `r` ROM; per-space codes P 0/0xd/0xe/0xf, X 1/0x12/0x13/0x14, Y 2/0x17/0x18/0x19,
  L 3/9/10, D `:` only), `0x43baf1 merge_mem_space(a, b)` (combine operand spaces:
  N matches anything, L+X -> X, L+Y -> Y, X+Y/P+data -> error),
  `0x43aeb8 emi_map(n, unsigned long *attr)` (EMI map number -> map code `n+0x1d`,
  width attribute bits; invalid below processor level 3).

Operand/line parsing (all work on `optr`, 0x45f860):
- `0x43ae13 get_force(allowed)` - `<<` 0x4000000 (I/O short; "I/O short addressing mode
  not allowed" if not allowed), `<` 0x2000000, `>` 0x1000000, else `default_force`.
- `0x43b007 check_fields(int nused)` - "Extra fields ignored" + "Possible invalid white
  space between operands" when operand fields beyond `nused` are non-empty.
- `0x43bccb check_extra_operand(void)` - "Too many fields specified for instruction" +
  the white-space hint when `fld_operand3` is non-empty (error points at it).
- `0x43b08d get_string(src, dst)` -> after the closing quote or 0: delimiters `'` `"`
  `[`, doubled delimiter = literal, `'a'++'b'` concatenation, `[str,off,len]`
  substrings via `0x43b214 get_substring` (offset/length through
  `expr_to_nonneg_line`); errors "Syntax error - expected quote", "Missing quote in
  string", "Missing string after concatenation operator", "Offset/Length value greater
  than string length", "Missing delimiter in substring", "Syntax error - expected
  comma". `0x43b405 get_string_only` adds "Extra characters following string".
- `0x43b448 get_symbol(void)` -> `sym_name_buf` or 0: optional `_`, letter first
  ("Symbols must start with alphabetic character"), `[A-Za-z0-9_]`, max 512 chars
  ("Symbol name too long"); first `check_reserved`.
- `0x43b5bb check_reserved(char *name)` - register name (`match_register_name`)
  followed by a non-identifier char -> "Reserved name used for symbol name: <prefix>"
  (temporarily NUL-terminates at the match).
- `0x43b659 check_symbol(char *name)` -> 1 ok, 0 empty, -1 error (as `get_symbol` plus
  "Extra characters following symbol name").
- `0x43bc1b skip_symbol`, `0x43c7a6 next_field_has_space` (dead).

Location counters:
- `0x43b926 check_loc_counters(int chk_underflow)` - see 7.7.
- `0x43b8f1 set_file_buffer(fp, which)` - `setvbuf(fp, file_buf0/1, _IOFBF, 2048)`.

Encoding helpers (callers are encode.c/procop.c):
- `0x43bd1e insert_bits(word, val, pos, width)` = `(word & ~(m<<pos)) | ((val&m)<<pos)`,
  `m = ~(~0<<width)`, shift counts taken `& 31` (x86).
- `0x43bd53 insert_bits_expr(word_txt, val_txt, pos, width)` -> malloc'd linker
  expression, pos 0: `((%s&(~0<<%d))|(%s&~(~0<<%d)))` (word, width, val, width); else
  `((%s&~(~(~0<<%d)<<%d))|((%s&~(~0<<%d))<<%d))` (word, width, pos, val, width, pos).
- `0x43bdfb encode_field(code, op, pos, width)` - op without text (+0x1c): numeric insert
  into `code+4`; else `code+0x40 = insert_bits_expr("$%0*lX" of code+4, op text)`, frees
  op text. `0x43be85 encode_field2`/`0x43bf3d insert_bits2`/`0x43bfa7
  insert_bits2_expr` - two-part field version (masks/shifts), format at 0x459c68;
  `encode_field2` has no callers. `0x43c047 enc_expr` (`@enc(%s,$%lX,%s,%s)`, dead).
- `0x43c0ea fmt_double(buf, fmt, double)` - see 7.9.

Object output:
- `0x43c34d clear_coff_sym` - zero `coff_sym` (0x465a60, mspace = 4) and `coff_aux`
  (0x465880).
- `0x43c37e obj_fwrite` = `fwrite` (debug paths compiled out); `0x43c450
  fwrite_swapped`, `0x43c481 obj_fwrite_swapped` - `swap_words` **in place** then write;
  `0x43c4b2 swap_words(buf, size, n)` reverses each 4-byte group of the first
  `size*n & ~3` bytes. Portable rebuild: encode big-endian explicitly.

Misc:
- `0x43c528 tm_to_secs(struct tm *)` - mktime-like (UTC, uses `tm_yday`, -1 on invalid);
  its only caller (amode.c `FUN_00405eea`, listing date) discards the result: omit.
- `0x43c810 stack_create`, `stack_init`, `stack_push`, `stack_pop`, `stack_destroy` -
  dead.
- `0x43cae0 ilist_dump` .. `0x43d808 ilist_run_checks`, `0x43d091 lbl_list_*`,
  `0x43d27b ifix_*`, `0x43da70 darray_*` - dead subsystems 2.11/2.12 (only
  `ilist_free`, `ifix_free`, `lbl_list_free`, `ilist_rewind`, `ilist_current` are
  called, all no-ops in practice).

## 4. Globals (names from the names file; owner module in parentheses)

Symbol table (bss): `sym_hash` 0x45fcc0, `ext_hash` 0x461c50, `strtab_hash` 0x462c18;
cursors `sym_insert_pt` 0x45fc34, `sym_local_tail` 0x45fc38 (named `local_block_tail`
in the file), `ext_insert_pt` 0x45fc54, `strtab_insert_pt` 0x45fc58; counters
`num_symbols` 0x45eb64, `num_local_symbols` 0x45eb6c, `num_zl_symbols` 0x45eb70,
`num_ext_symbols` 0x45eb74 (read by pseudo.c for "OPT must come first" checks);
`local_block_num` 0x45eb68, `local_block_list` 0x45fc3c, `cur_local_block` 0x45fc40,
`local_block_last` 0x45fc44, `local_block_cont` 0x45ea84, `macro_local_list`
0x45fc48, `cur_macro_local` 0x45fc4c; `sym_ref_seq` 0x45f934; `fref_head` 0x44f990
(asmglb, 12 bytes, `.next` 0x44f998 initialised to itself), `fref_cur` 0x45fc70;
`strtab_buf` 0x45fbe4, `strtab_size` 0x44f988 (asmglb, init 4); `sym_name_buf`
0x464480 (513+), `lower_buf` 0x463c68 (24), `upper_buf` 0x464688.

Sections (asmglb data unless bss): `global_section` 0x44f878 (0x90 bytes, name
"GLOBAL" 0x44f868, `ctr_sec` = itself), `reserve_sec_name` 0x44f870 ("RESERVE"),
`cur_section` 0x44f978, `ctr_section` 0x44f97c, `section_list` 0x44f980, `section_tail`
0x44f984 (all four initialised to `&global_section`), `section_count` 0x45fb80,
`section_stack` 0x45fb84, `section_depth` 0x45eba8, `local_sec_parent` 0x45fb7c.

Location counters (bss, written by `sec_set_current`): run `rt_space/map/counter/emi`
0x45f8a0..ac, load `ld_*` 0x45f8b0..bc; `rt_pc` 0x45f8c0 / `ld_pc` 0x45f8cc (pointers
into the counter's COFF header record), `rt_pc_start` 0x45f8c4 / `ld_pc_start`
0x45f8d0, bounds `rt_lo_bound`/`rt_hi_bound` 0x45f8d4/d8, `ld_*` 0x45f8dc/e0,
`rt_counter_obj` 0x45fb88 / `ld_counter_obj` 0x45fb8c (g6: `Cur_pri/sec_section`),
`rt_overflow` 0x45eab8 / `ld_overflow` 0x45eabc, `rt/ld_ovf_reported` 0x464eb0/b4,
`rt_addr_mask`/`ld_addr_mask` 0x44f91c/20 (asmglb, init 0xffff); `reloc_mode` 0x44f790
(relocatable object, i.e. **not** `-a`), `rt_reloc`/`ld_reloc` 0x44f794/98 (MODE per
counter).

SDI: `sdi_enabled` 0x45eb34 (`-j`), `sdi_local_target` 0x45eb38, `sdi_expr_count`
0x45fca4, `global_section_sdi_list` 0x44f8e0 (= `global_section+0x68`), `no_errors`
0x45ea50 (set around `sdi_find_target`).

Options read here (bss, set by pseudo.c `pseudo_opt` unless noted): `opt_cre` 0x45ea3c,
`opt_xr` 0x45ea88, `opt_ic` 0x45eaa0, `opt_gl` 0x45eab0, `opt_gs` 0x45eab4, `opt_scl`
0x45ead0, `opt_ur` 0x45eaf4, `opt_const` 0x45eb08, `opt_xll` 0x45eb0c, `opt_sco`
0x45eb20, `opt_ns` 0x44f7ac, `opt_sms` 0x44f7c4 (asmglb); `c_mode` 0x45ea98 (`-c`),
`debug_mode` 0x45eadc (`-g`), `opt_t` 0x45eb50 (`-t`), `gset_mode` 0x45eb28 (set by
`pseudo_set` around a GSET, by `sdi_find_target` from the record).

Other state read: `pass` 0x45f8fc (0 pre-pass, 1, 2), `optr` 0x45f860 (operand cursor),
`fld_label/opcode/operand/operand2/operand3` 0x44f810..20, `local_prefix` 0x44f830
(`'_'`), `zl_prefix` 0x44f99c ("Z_L") / `zl_prefix_lc` 0x44f9a0 ("z_l"),
`file_line_num` 0x45eb78 (line in the current file), `lst_line_num` 0x45eb80 (listing
line; the error line format is `**** <lst_line_num> [<file> <file_line_num>]`),
`in_line_replay` 0x45ea70 (input.c DO-loop line replay), `outer_scope_ref` 0x45eb10
(`^` operator), `cur_macro` 0x45fb6c, `scs_stack` 0x45fc84, `in_buffer` 0x45ebc4,
`buffer_num` 0x45ebc0, `overlay_num` 0x45ebe8, `default_force` 0x45ebac, `proc_level`
0x44f9fc, `proc_variant` 0x44fa00, `obj_fp` 0x45fca8, `reloc_count` 0x45fbb4,
`tmp_buf` 0x45f220, `sort_array` 0x45fc80, `sort_cmp` 0x45fb60, `month_days` 0x450508
(31,29,31,...), COFF staging `coff_sym` 0x465a60 / `coff_aux` 0x465880.

## 5. Cross-module interfaces

Called from here:
- error.c: `fatal` 0x412fa0, `err` 0x413085, `err_s` 0x4131f9, `warn_s` 0x41351d,
  `warn` 0x4133a9.
- eval.c: `expr_to_nonneg_line` 0x41479f, `expr_to_nonneg_resolved` 0x4147ee,
  `check_field_size` 0x409618 (value fits in n bits, used by `sdi_resolve`).
- amode.c: `match_register_name` 0x4080dc.
- macro.c: `mac_lookup` 0x41faa5.
- pseudo.c: `org_select_counter` 0x42c829, `org_get_bounds` 0x42ce91.
- procop.c (g4, unnamed): `FUN_0042447e` append a staged 0x20-byte COFF record,
  `FUN_0042456e` strtab_add, `FUN_00424817` obj_add_symbol (sym -> COFF symbol: class
  210 GLOBAL / 2 with `c_mode`, 211 XDEF, 213 section-local, 214/215 local label
  outside/inside macro; n_type 4, 5 long, 6 float), `FUN_00424b1a` external symbol,
  `FUN_004247b1` SDI marker.

Provided: `sym_lookup`/`ext_add`/`get_symbol`/`fref_*` to eval.c; `sym_define` to
pseudo.c (EQU/SET) and via `sym_define_label` to procop/data/macro/debug; `sec_*`
directive handlers to `pseudo_dispatch`; `sec_set_current`/`sec_save_counters` to
input/macro/pseudo (include files and macro expansions switch sections back);
`hash_name`/`str_lower`/`xmalloc` everywhere; `sort_ptrs` to listing.c/macro.c;
`fmt_double` to listing/pseudo/eval; byte-swapped writers to object.c.

**COFF symbol order** does not depend on the hash tables: records are appended in the
order they are produced in pass 2 - `.bs` at SECTION, counter symbols when a counter
is first selected (pseudo.c), externals at their first `ext_add`, labels at their
pass-2 definition, `.es` at ENDSEC (checked in `s1.cln`). SET symbols and (without
`OPT XLL`) local labels are never emitted.

## 6. Contradictions with the other groups' notes

- **g3 `EXPR_VAL`**: `W16` (0x40) is the counter section's *number*
  (`ctr_section+8`), not a counter-object pointer; `W17`/`W18` are the buffer and overlay
  numbers (`buffer_num`/`overlay_num` 0x45ebc0/0x45ebe8), not ilist capacities (g3's
  `rt_ilist_cap`/`rt_ilist_count`/`ld_ilist_cap` names for 0x45ebc0/c4/e8 are wrong;
  the ilist is dead code); `W19`/`W20` are the symbol's SDI counts (sym +0x38/+0x3c),
  `W21` the COFF section index (sym +0x34).
- g3 `force_long` (0x45eb10): the `^` operator makes local-label lookup ignore the
  macro-local scope (`sym_lookup_local`, `sdi_record`): Motorola's "macro local label
  override". Named `outer_scope_ref` here.
- g1 `AbsMode` (0x44f790) is true in *relocatable* mode (`ext_add` fatal "Attempt to
  store external reference in absolute mode" when it is 0); g6 `Rel_mode` is right.
- g1 `CurInstrFieldMsg` (0x45f860) is the operand scan cursor (`optr`).
- g1 `InMacroExpand` (0x45ea70) is set only by input.c's DO-loop line replay.
- g1 `LineTotal`/`LineNo`: 0x45eb78 is the per-file line, 0x45eb80 the listing line
  (named `file_line_num`/`lst_line_num` here).
- g5 `define_symtab`: 1009 buckets, not 324.
- g6 `Opt_portable` / g1 `OptT` / here `opt_t` (0x45eb50): same `-t` flag; here it only
  unhides directive entries with code `'0'`.

## 7. Quirks worth reproducing

1. **`-j` crashes.** `init_globals`/`init_pass1` call `sdi_mark_section(&global_section)`
   while `pass` is 0, which takes the "pass 2" branch and dereferences the NULL
   `sdi_mark_cur`. Any `-j` run prints the banner, then "ASM56000: Fatal segmentation or
   protection fault; contact your tools vendor" (exit code 127; `t4.asm`). A rebuild
   can emit that message and exit instead of implementing SDI; porting the SDI code
   is optional.
2. `sdi_resolve` (if ported): repeat until no change: for each entry without
   0x10000/0x2000/0x100: `fa` = target fits range1, `fd1` = distance fits range1,
   `fd2` = distance fits range2 (0 if range2 is 0); ok = (kind&2 && fa) || (!(kind&2) &&
   kind&1 && fd1) || (kind&3 && fd2). If not ok or 0x4000: set 0x100, clear 0x200, and
   for every other live entry k compare **unsigned**: `pc_k <= pc_i < target_k` ->
   `dist_k++`; `target_k <= pc_i < pc_k` -> `dist_k--` (targets are not moved). Also
   set 0x200 when kind&3, still short, `!fa` and `fd2`. Then prefix sums of 0x100 into
   +0x18 (entries with 0x2000 keep their old value).
3. **Listing sort** (`sort_ptrs`): pivot = value of `a[(lo+hi)/2]` (left in place);
   `i=lo, j=hi`; loop { `while (i<j && cmp(a[i],p) <= 0) i++`; `while (i<j &&
   cmp(a[j],p) >= 0) j--`; `if (j <= i) break`; swap }; `if (mid < i && cmp(a[i],p) > 0)
   i--`; swap(i, mid); recurse on the smaller side first ([lo,i-1] / [i+1,hi]). Not
   stable and not the C library qsort: reproduce it exactly, together with the hash
   function and chain insertion order (2.2), or same-name symbols of different
   sections (and ties in other listing tables) can come out in a different order.
4. The local-symbol insertion branch "no cursor but `sym_local_tail` set" does
   `new->next = tail; tail->next = new` (a 2-cycle, verified in the disassembly at
   0x438272). Apparently unreachable; do not "fix" it into something that changes
   reachable behaviour.
5. `sym_search(name, reftype, is_local)` walks from `sym_insert_pt`, updating it on each
   node. Same name and `section == cur_section`: stop, unless GSET mode outside the
   global section. Other sections (only when `!is_local`): with `OPT NS` and reftype !=
   1 remember the symbol if its section is on the section stack (below the global
   entry, not LOCAL; the last such stack match wins), the first XDEF'd one (0x80) if
   reftype 1 or the name is on the current XREF list, and the first GLOBAL one (0x40).
   Afterwards the GLOBAL candidate wins if GSET mode, or if the stopped-on symbol is SET
   and on the XREF list. If nothing matched and the name is not on the LOCAL list:
   stack candidate, else XDEF candidate, else GLOBAL candidate.
6. `sec_section`: an invalid **second** modifier is reported with the text of the
   **first** modifier (`param_2`, the lower-cased copy, or the original pointer if the
   first modifier was empty). `sec_global` tests `*optr` (the cursor left over from
   earlier parsing) for "Missing symbol name", while the other three test
   `fld_operand`.
7. `check_loc_counters(chk)`: with `chk` it clears the "reported" flags and warns about
   underflow (`*pc < *lo_bound`) for run and (if different) load. Overflow is reported
   one call late: when the flag is already set it warns "Runtime/Load location counter
   overflow", clears the flag and marks it reported; otherwise, if not reported and
   (`*pc > *hi_bound` or `(*pc &= mask) < pc_start`) it sets the flag and masks the pc.
   Returns true when anything was reported.
8. `str_lower_copy` writes into a 24-byte static buffer without a length check (overflow
   runs into `file_buf0`); use a larger buffer, output is unaffected for sane sources.
9. `fmt_double(buf, fmt, d)`: `Inf`/`-Inf`/`NaN`/`-NaN` for exponent 0x7ff; +-0.0: the
   last char of `fmt` is replaced by `f`, printed, `-` prefixed for -0.0, then `E+000`
   appended; otherwise `sprintf(buf, fmt, d)`. Then, if an `E`/`e` exists and the char
   at E+4 is NUL or white space (**ctype mask 8 = space, not digit**; checked in the
   disassembly at 0x43c2c0), a 2-digit exponent is widened to 3 digits (`E+05` ->
   `E+005`). MSVC already prints 3 digits, so on other C libraries this function is
   what keeps listings identical: always produce 3-digit exponents
   (`1.500000E+010`, `-3.000000E-200` in `f.lst`).
10. Local labels: the scope ends at every non-local label (and at every non-local
    `sym_define`, including EQU/SET, which bumps `local_block_num`), except SCS `Z_L`
    labels with `OPT SCL`. Errors about undefined locals print the name without `_`;
    "Symbol redefined: _l1" keeps it (`r.asm`).
11. "Symbol redefined" is issued in pass 2 at *every* definition of a multiply defined
    symbol, including the first one.
12. `sdi_adjust_symbols` masks label values to 16 bits.
13. `hash_name` sign-extends chars (2.10); all 32-bit arithmetic must be masked on
    64-bit `long` hosts. `insert_bits` shift counts are taken modulo 32.
14. `swap_words` modifies the caller's buffer; object.c relies on staging buffers being
    rebuilt before reuse.

## Summary

- Functions: 186 named (sdi 13, section 21, symtab 42, util 110 after the corrected
  module split, section 0); about 40 of them are dead code (ilist/ifix/lbl_list/
  lbl_index/darray/stack helpers, `sdi2_expr`, `sdi_branch_mnemonic`, `enc_expr`,
  `encode_field2`, `tab_search_pos`, ...).
- Globals: 151 D entries in the names file (unchanged count; six renamed/retyped:
  `file_line_num`, `lst_line_num`, `in_line_replay`, `opt_t`, `macro_local_list`,
  `ia_check_fn`).
- Structs: symbol entry (0x60), external entry (0x14), section (0x90), section-stack
  and name-list nodes (8), local block (0xc), xref node (0xc), fref node (0xc), SDI
  group (0x24) / record (0x28) / table entry (0x1c) / mark (0xc), dead ilist (0x44) /
  ifix (0x20) / darray (0x20) / stack (0x14).
- Open: the exact meaning of `sdi_rec` ranges as passed by procop.c (g4); the
  0x34-byte counter header fields +0x18/+0x20 that SDI/XREF increment (probably
  `s_size` and a per-counter symbol count, confirm with g4/g6); symbol +0x04 and
  section +0x00 are never written here - check whether any consumer reads them.
