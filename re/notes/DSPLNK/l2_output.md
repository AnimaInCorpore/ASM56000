# DSPLNK.EXE - group l2_output: fixup.c, object.c, memctl.c

Evidence base: `re/out/DSPLNK/mod/{fixup,object,memctl}.c` (Ghidra decompile, read in full,
2223+1195+1881 lines), `re/out/DSPLNK/{modules,functions,globals,strings}.txt`, live
disassembly of the three keyword-lookup tables via `x86dis.py` + a small PE-reader script
(`scratch_l2_output/pe.py`, kept from a previous run) used to dump the tables directly out of
`re/bin/DSPLNK.EXE`'s `.rdata`. `re/notes/COFF.md` (from the COFDMP reconstruction) already
documents the on-disk COFF layout field-by-field and is reused verbatim below; object.c's
code matches it exactly at every offset checked.

Reused test inputs from the previous (interrupted) run of this task, still valid, in
`scratch_l2_output/`: `t1.asm`/`t2.asm` (two tiny modules, `sec1` P `xdef start`/`xref dat1`,
`sec2` X `dat1`, `sec3` Y `tab`+`xref start`) linked to `t.cld`/`t.map`/`t1.cln`/`t2.cln`,
and `pe.py` (reads `re/bin/DSPLNK.EXE`'s PE sections so a dword at a given VA, or a string it
points to, can be dumped without a disassembler - `python pe.py <hex-addr> <hex-end>`).

## Module boundary correction

`modules.txt` assigns `00421ec7,00421eef,00421f79,004221bc` to `memctl`, but their entries in
`functions.txt` show callers only in the `0x41e000-0x41f000` range (`FUN_0041f483`,
`FUN_00421674`, `FUN_0041ebe0`, `FUN_0041ee2c`) - outside the `memctl.c` call graph, which is
otherwise self-contained from `00423710` on (`00423710` calls `00423863` calls everything else
in the module). These 4 functions are very likely misattributed leftovers of the previous
module (probably `func.c`/`input.c`, object-symbol/tag merge helpers) rather than part of
`memctl.c`'s grammar. Named them anyway (required per module list) but at low confidence and
did not rely on them for the memctl.c analysis below. Likewise `00426562` votes into `object`
by address but is exclusively `memctl.c`'s own token reader (see below) - real code, wrong
module tag.

## fixup.c - purpose

Despite the name, this is not per-instruction relocation patching (DSP56000 opcodes are
already resolved values in the COFF raw data; there is no bit-field patch step). "Relocation"
here is what the tool itself calls it (`"%s: Beginning section and symbol relocation\n"`,
`FUN_0040d4e0` at `0040d4e0`): the **address-assignment pass** that walks every input section
collected from the linked object modules, in link order, and assigns each one a final address
inside the region/memory space it was placed into by `memctl.c` (or by default if
unconstrained), verifying it fits and tallying per-counter high-water marks used later for the
`?SIZE` symbols and the map file. A second half of the module (from `00410a84` on) turns the
now-addressed sections into the region-section stat records and eventually the relocation
information written by `object.c`.

## object.c - purpose

Writes the linked output COFF file: absolute (`.cld`, when `g_incremental`==0) or
incremental/relocatable (`.cln`, `g_incremental`!=0). Field layout matches `re/notes/COFF.md`
exactly (see cross-references below); this module only assembles the pieces (section list,
symbol table, string table, line numbers) and calls `fwrite`-style helpers in `util.c`
(`thunk_FUN_00430773`/`004307a4`/`004306a1`) to write them big-endian at the byte level - the
actual byte-swap-on-write is presumably in those `util.c` helpers, not visible in this module.

## memctl.c - purpose

Parses the `-r<memfil>` **memory control file**: an ad-hoc line-oriented, case-insensitive,
keyword-driven grammar for describing REGIONs of memory, placing SECTIONs into them, reserving
address ranges, defining absolute SET/SYMBOL values, MAP-file formatting, linker OPTIONs
(mirrors of `-x` command-line options / the `DSPLNKOPT` env var), and INCLUDE-file nesting.
`00423710` is the driving loop; `00423863` is the per-record dispatcher; `00426562` is the
shared token reader used by the whole grammar (`FUN_00426562(0)` = read next token into
`g_memctl_token`/classify; `FUN_00426562(4)` = skip to end of line/reprime for next statement,
matching its two `param_1` values `0`/`4`/`10` seen at call sites).

## The memory-control-file grammar (recovered from the live keyword tables)

`memctl.c` calls three generic table-search helpers in `util.c` (`thunk_FUN_0042d8d0`,
`thunk_FUN_0042d8f3`, `thunk_FUN_0042d916`, each a thin wrapper around a common
`bsearch`-style routine at `0040133e`: `search(key, table, nentries, entsize=8, cmp=0042d939)`).
Disassembling the three wrappers gives the exact table addresses; dumping them with `pe.py`
gives the literal keyword spellings and their numeric ids (verified against every `switch` in
the module - every id used in code is accounted for by a table entry and vice versa):

### Record-keyword table (`memctl_kw_tab`, `.rdata` 0x458010, 17*8=136 bytes) - top of `00423863`

| id | keyword | handled by |
|---|---|---|
| 1 | START | inline in `00423863`: sets `g_start_sym_name` |
| 2 | SECTION | inline: looks up the named output section, either marks it (and every subsection) ABSOLUTE-in-current-region outright, or (if followed by qualifiers) opens a `(...)`-style qualifier list via `memctl_parse_qualifiers` |
| 3 | SET / SYMBOL (both spellings share id 3) | `memctl_do_set` (`00425470`): `SET name[:mspace] value` - defines a symbol in the GLOBAL section |
| 5 | BASE | `memctl_parse_qualifiers(5, NULL)` - sets current region+mspace record's base address |
| 6 | MAP | `memctl_do_map` (`0042568f`) |
| 7 | MEMORY | `memctl_parse_qualifiers(7, NULL)` - sets current region+mspace record's high/end address |
| 9 | RESERVE | `memctl_parse_qualifiers(9, NULL)` - reads `addr..addr` range syntax (`"Invalid reserve range syntax"`), creates a RESERVE-list entry via `obj_reserve_entry_get` |
| 0xa | BALIGN | only reachable as a qualifier inside `SECTION(...)`; not otherwise handled explicitly in `00423863`/`00424879` bodies read - buffer alignment field |
| 0xb | IDENT | inline: `IDENT "modname" version.revision` - module name/version/revision (feeds `.cld`/`.cln` header comment fields) |
| 0xc | SECSIZE | `memctl_parse_qualifiers(0xc,...)` - requested section size, as an absolute count or (via `thunk_FUN_0040a571`, the "percentage" expression evaluator) a percentage-of-region-size |
| 0xd | REGION | inline: `REGION name [qualifiers]` - opens a region (`g_cur_region` set via `thunk_FUN_0042c373`, "region lookup/create"); trailing qualifiers on the same line go through `memctl_parse_qualifiers(0xd, NULL)` and set the region's own default-mspace size |
| 0xe | ENDR | inline: closes the region (`memctl_check_region_bounds`, then `g_cur_region = g_region_sentinel`); `"ENDR without corresponding REGION directive"` if not in one |
| 0xf | INCLUDE | `memctl_do_include` (`0042609f`) |
| 0x10 | SBALIGN | `memctl_parse_qualifiers(0x10, NULL)` - "section boundary align", forces re-placement/round-up (marks referencing input sections' `0x1000` bit dirty again) |
| 0x11 | SIZSYM | falls through to the generic "bare symbol = mem:addr" handler (`switchD_00423a32_caseD_11`) - `SIZSYM symname` auto-defines a symbol equal to a section's size |
| 0x12 | ALIGNSYM | same fallthrough - `ALIGNSYM symname` auto-defines a symbol equal to a section's alignment address |

The fallthrough label (reached for ids 0x11/0x12 and for any *unrecognized* leading token) is
the generic "bare identifier" statement: reads a symbol name, then a `mem[:ctr](map):expr`
address specifier via `thunk_FUN_0042e743` (util.c - `"Illegal memory space character"` etc.,
this is the same `<mem>[<ctr>][<map>]:<origin>` syntax documented in the `-o` command-line
option's usage text), then defines/looks up that symbol with `thunk_FUN_0042e743`/
`thunk_FUN_0042c6c1` (matches `-u<symbol>`/absolute-symbol semantics).

`memctl_parse_qualifiers` (`00424879`, shared body for ids 2/5/7/9/0xc/0xd/0x10) reads a
comma-separated list of `mem[:ctr](map):expr` terms; when called with `sec != NULL` (i.e. as a
`SECTION name (...)` qualifier list) it sets fields on the **section struct** instead of the
**region+mspace stat record** - e.g. id `2` inside a SECTION qualifier list sets an explicit
placement address on the section (`local_20[3]|=0x200; local_20[4]=addr`), id `0xc` (SECSIZE)
sets the section's requested size (`local_28[0x18]`, with `local_28[1]|=0x200000`, or
`|=0x2000000` plus a `double` percentage at `local_28[0x18..0x19]` for the percentage form),
id `0x10` (SBALIGN) sets `local_28[0x12]` and forces re-placement of every already-placed
member. Outside a SECTION (`sec==NULL`) the same ids set the current region+mspace record's
`base`(5)/`end`(7)/`reserve-range`(9)/`size`(0xd) fields directly.

### MAP-record table (`memctl_mapopt_tab`, 0x4580a0, 12*8=96 bytes) - used by `memctl_map_option`

`memctl_do_map` (`0042568f`) itself distinguishes `MAP PAGE ...` vs `MAP OPTION ...` by a
literal `strcmp` (not table-driven), dispatching to `memctl_map_page` (`00425747`, page
width/length/top-margin/bottom-margin/lines-per-page, with consistency checks:
`"Left margin exceeds page width"`, `"Page length too small ..."`) or `memctl_map_option`
(`00425a60`, comma list of options below, each optionally `opt=n` for the one with a numeric
argument):

| id | option | effect |
|---|---|---|
| 1 | NOCONST | `g_map_const = 0` |
| 2 | NOLOCAL | `g_map_local = 0` |
| 3 | NOSECADDR | `g_map_secaddr = 0` |
| 4 | NOSECNAME | `g_map_secname = 0` |
| 5 | NOSYMNAME | `g_map_symname = 0` |
| 6 | NOSYMVAL | `g_map_symval = 0` |
| 7 | NOBUFFER | `g_map_buffer = 0` |
| 8 | NOOVERLAY | `g_map_overlay = 0` |
| 9 | NOUNUSED | `g_map_unused = 0` |
| 0xa | GLOBMAP | `g_map_globmap = 1` |
| 0xb | NOGLOBSYM | `g_map_globsym = 0` |
| 0xc | SYMLEN=n | `g_map_symlen_flag = 1; g_map_symlen = n` (n parsed from after a literal `=` with `strtol`) |

(all the boolean flags default to "on"/1 and these keywords turn individual map-file sections
off, except GLOBMAP/SYMLEN which turn a feature on - map.c, another group's module, is the
actual consumer of every `g_map_*` flag.)

### `-x`/`OPTION`/`DSPLNKOPT` table (`memctl_xopt_tab`, 0x458108, 33*8=264 bytes) - `memctl_do_option`

Same 3-letter-code table drives both the memory-control-file `OPTION` record (if any -
`memctl_do_option`'s prototype takes the option string directly, so it is presumably also the
handler behind the command-line `-x` option and the `DSPLNKOPT` environment variable, since
usage text says `-x<opt>[,<opt>...]` and those are exactly the 3-letter codes below):

| id | code | flag | id | code | flag |
|---|---|---|---|---|---|
| 1 | ABC | `g_opt_abc=1` | 2 | NOABC | `g_opt_abc=0` |
| 3 | AEC | `g_opt_aec=1` | 4 | NOAEC | `g_opt_aec=0` |
| 5 | RO | `g_opt_ro=1` | 6 | NORO | `g_opt_ro=0` |
| 7 | ASC | `g_opt_asc=1` | 8 | NOASC | `g_opt_asc=0` |
| 9 | ESO | `g_opt_eso=1` | 0xa | NOESO | `g_opt_eso=0` |
| 0xb | WEX | `g_opt_wex=1` | 0xc | NOWEX | `g_opt_wex=0` |
| 0xd | OVLP | `g_opt_ovlp=1` | 0xe | NOOVLP | `g_opt_ovlp=0` |
| 0xf | SVO | `g_opt_svo=1` | (no NOSVO) | | |
| 0x10 | RSC | `g_opt_rsc=1` | 0x11 | NORSC | `g_opt_rsc=0` |
| 0x12 | FF | `g_opt_ff=1` | 0x13 | NOFF | `g_opt_ff=0` |
| 0x14 | CSL | `g_opt_csl=1` | 0x15 | NOCSL | `g_opt_csl=0` |
| 0x16 | SDI | `g_opt_sdi=1` | 0x17 | NOSDI | `g_opt_sdi=0` |
| 0x18 | SBM | `g_opt_sbm=1` (only if target chip id `DAT_00461f44` is 3 or 5) | 0x19 | NOSBM | `g_opt_sbm=0` (unless chip==5) |
| 0x1a | WVR | `g_opt_wvr=1` | 0x1b | NOWVR | `g_opt_wvr=0` |
| 0x1c | OSP | `g_opt_osp=1` | (no NOOSP) | | |
| 0x1d | ISW | `g_opt_isw=1` | (no NOISW) | | |
| 0x1e | WDG | `g_opt_wdg=1` | 0x1f | NOWDG | `g_opt_wdg=0` |
| 0x20 | MCM | `g_opt_mcm=1` | 0x21 | NOMCM | `g_opt_mcm=0` |

Semantics of the individual flags beyond "used by module X" were not traced outside
fixup/object/memctl (most are only tested in arith/eval/map/symtab, which are other groups'
modules); `g_opt_abc` ("Address Boundary Check", my guess from usage) gates the two
"Specified address/size greater than maximum memory address" warnings in
`memctl_parse_qualifiers`; `g_opt_ro` gates whether `object.c`/`fixup.c` write a second,
alternate copy of relocation data (`g_reloc_global_rec` vs `g_cur_reloc` comparisons) - my
best guess is "Relocatable Output" (suppress the always-generated duplicate needed only for
later re-incremental-linking).

## Functions

### fixup.c

- `0040cac2 fixup_free_worklist` - frees every pointer left between two shared stack-globals
  (owned jointly with eval.c: `DAT_00461f28..DAT_00461f2c`); a small cleanup helper, caller/use
  not pinned down.
- `0040d4e0 fixup_relocate` (**top-level entry point**) - prints
  `"%s: Beginning section and symbol relocation\n"` (verbose mode), frees pending eval results,
  clears `g_reloc_cur_symname`'s... wait: clears the counter-group list, rewinds the temp file
  if incremental, and runs `fixup_alloc_sections` once (non-incremental) or in a
  save/retry/restore loop (incremental: `fixup_save_counters` / `fixup_alloc_sections` /
  `fixup_restore_counters`, iterating while `g_pass2_changed` is set by a symtab callback
  `thunk_FUN_0042a84c` - i.e. address assignment is redone until a fixed point, because
  incremental output can change symbol->section resolution mid-pass) then closes the temp file.
- `0040d5e0 fixup_alloc_sections` (**core pass**) - for every input file/module in the link
  (`g_region_sentinel`-headed list, `+0xc`=next), for every relocation record in file order
  (`fixup_collect_relocs`), computes its target memory-space char (`thunk_FUN_0042f22f`), then
  for the first record of a new counter switches counter context (`fixup_get_counter_group`),
  and dispatches to the placer matching the record's flag bits: XDEF/global lists
  (`fixup_collect_xdefs`/`_all`), BUFFER lists (`fixup_collect_buffer_syms`,
  `fixup_place_buffer` via `fixup_place_group` for `mspace==3`(L)), overlay
  handling (`fixup_flush_pad_lists` when the section is L-space), SECSIZE symbols
  (`fixup_place_secsize_syms`), the group placer (`fixup_place_group`) and the catch-all
  (`fixup_place_default`). At the end, second loop over the section hash table
  (`g_sec_hash_tab`, 0x7d3 buckets) fixes up each output section's final address by adding its
  memory-space's counter base and, when target-chip-specific (`DAT_00461f44==6`), computes a
  masked/shifted "short address" field - and calls `fixup_size_symbols` if debug lines are on.
- `0040dd4a fixup_get_counter_group` - linear search (`g_counter_groups`, 0x28-byte nodes) for
  the per-counter (0-7, matches the `" XYLPEDU"` index table at `00457ff0`) bookkeeping node;
  creates one (8 zeroed slots) if missing; sets `g_counter_totals` to point at its data.
- `0040ddde fixup_flush_pad_lists` - frees a section's BUFFER/pad symbol lists for both its
  primary (mspace 1) and shared (mspace 2) counter groups via `fixup_collect_xdefs`/`_all`.
- `0040df91 fixup_check_secsizes` - walks every output section; if debug/overlay mode
  (`DAT_00461294==1`) propagates counter linkage and an `0x800000`/`0x20000` "already placed"
  bit to buffer members; compares the section's *actual* accumulated length against its
  requested (fixed or align-derived) length, emitting
  `"Actual length of section greater than specified size"` if it overflows, else growing the
  section to the requested size; runs the SIZE-symbol update (`fixup_size_symbols`) at the end
  if non-debug and reserve-count nonzero.
- `0040e2bd fixup_save_counters` / `0040e501 fixup_restore_counters` - checkpoint/rollback the
  per-section placement fields (`+0x38/0x3c` <-> `+0x40/0x44` "committed" copy, `+0x10/0x14`
  <-> `+0x28/0x2c` "trial" copy, clearing the `0x1000` "already placed" bit on restore) used by
  `fixup_relocate`'s retry loop.
- `0040e72e fixup_symbol_extent` - sums the byte length of every hash-table section matching a
  given symbol+counter pair (used to size an overlay).
- `0040e832/e8ba/e981/ea59/eb31` - five small "collect matching pointers into a
  NULL-terminated malloc'd array, then sort it" helpers (sort via `map.c`'s
  `thunk_FUN_0041ee04`/`0041eda4`/`0041ed36`) over a section's relocation-record or symbol
  list, filtered by flag bits (XDEF-only, non-XDEF, BUFFER-flagged, non-`N_UNDEF`).
- `0040ebca fixup_size_all_sections` / `0040ec8b fixup_size_section` - first sizing pass over
  every hash-bucket section: computes `end-start` (or, if zero, the sum of contained
  subsection lengths, feeding that back into the parent's running total).
- `0040ed4c fixup_place_reloc` - given a relocation record and counter, computes its length
  (`fixup_reloc_length`), then calls `fixup_gen_default_relocs`-style write-back
  (`FUN_004115dd`) for its primary counter and, for the combined L/1-or-2/3 counters, the
  alternate (X/Y/L split) copy, then re-writes both region-section pointer arrays.
- `0040f005 fixup_reloc_length` - caches `end-start` into field `[6]` on first call, also
  accumulating it into the owning section's `+0x4c` running total.
- `0040f04a fixup_place_buffer` - allocates address space for a BUFFER-flagged record via
  `fixup_alloc_range` (rounding to its natural size unless the auto-align option forces
  0-alignment), records the used range (`fixup_mark_used`), then updates the high-water mark
  (`fixup_update_high_water`) if the section had no explicit address.
- `0040f17f fixup_place_simple` - places a record directly after the previous one (no
  rounding), used for the "already contiguous" case.
- `0040f225 fixup_place_secsize_syms` - walks a region's per-mspace stat list, placing every
  SECSIZE(`0x100`)-flagged member the same way as `fixup_place_buffer`.
- `0040f3c5 fixup_place_group` / `0040f58e fixup_place_default` - place, respectively, a
  filtered array of records sharing a placement class, and the remaining "no special flags"
  (`flags&0x300==0`) records of a section, both via `fixup_alloc_range`+`fixup_mark_used`.
- `0040f722 fixup_update_high_water` - updates the per-counter high-water totals
  (`g_high_water_x/y/l/p/...`) used later by `fixup_size_symbols` and the map file's length
  columns; counter `3` (L) updates X, Y and L together (P/X/Y/L share the L counter).
- `0040f868 fixup_mark_used` - records a placed range against the primary counter
  (`fixup_check_bounds`) and, for the combined counters, against the X/Y/L alternates too.
- `0040fa6c fixup_alloc_range` (**the free-space allocator**) - classic first-fit allocator
  over a doubly-linked, address-sorted list of free blocks (`g_freelist_head`/cursor,
  20-byte nodes `base@4,end@8,prev@0xc,next@0x10` created by `fixup_freeblk_new`): rounds the
  candidate base up to the requested alignment (`thunk_FUN_00430ac9`, util.c), walks forward
  from the cursor for a block big enough, and (if `commit!=0`) shrinks/splits/removes the block
  it took the space from.
- `0040fdb9 fixup_freeblk_new` - allocate+link one free-block node before/after a given node
  (or as new head).
- `0040fe58 fixup_usedrng_add` / `0040ff2c fixup_usedrng_merge` - insert-sorted-by-address into
  a "used range" list (same 20-byte node shape), merging with an overlapping/adjacent neighbour
  on either side.
- `0041006f fixup_size_symbols` - defines/looks up the five well-known size symbols `DSIZE`,
  `XSIZE`, `YSIZE`, `LSIZE`, `PSIZE` (creating each, if missing, as a GLOBAL-section symbol via
  `thunk_FUN_0042bc50`+`thunk_FUN_0042c6c1`) and adds the corresponding high-water total
  (`g_high_water_x/y/l/p/cur`) to its existing value.
- `00410668 fixup_place_overlays` (**overlay resolution**) - for every "overlay group" table
  entry (`+0x5c` list on each output section, up to `field[0x5c]` count), if its target-symbol
  slot is non-null: looks up the overlay base symbol via `thunk_FUN_0043a260`/`thunk_FUN_0040a370`
  (eval.c), and if its value is negative reports `"Unresolved overlay base address"`; if its
  section has the "no relocation" bit (`0x4000`) reports `"Invalid overlay base address"`;
  otherwise rebases every member's placement by `(new_base - old_base)` and marks it
  relocated. Second sub-pass (only when not both incremental+quiet) fixes up P-memory
  long-addressing operand words for cross-page-jump instructions, reporting
  `"Overlay address involves incompatible memory spaces"` when the target instruction's
  memory-space class does not match.
- `00410a84 fixup_gen_relocs` (**second top-level driver**) - for every input file/module's
  DEFAULT-counter relocation record still flagged `0x4000` ("dirty"/needs final address),
  builds its region-section array (`fixup_collect_secsize_syms`) and dispatches to
  `fixup_gen_overlay_relocs`/`fixup_gen_buffer_relocs`/`fixup_gen_secsize_relocs` (guarded by
  the matching `0x1000`/`0x200`/`0x100` flag) then always `fixup_gen_default_relocs`, finally
  copying the trial address field back into the committed one (`+0x14=+0x10`).
- `00410c8b fixup_collect_secsize_syms` - builds the array of SECSIZE-flagged region-stat
  records referenced by a relocation record's region list.
- `00410d70/fe8/11200/11450 fixup_gen_{overlay,buffer,secsize,default}_relocs` - four
  near-identical "walk an array of same-tag relocation records sharing one memory run,
  assign each the next contiguous address after the previous one's end, call
  `fixup_check_bounds` to validate/report, relink into the owning section's list" generators;
  they differ only in which flag selects membership (overlay: `flags2&0x1000`; buffer:
  `flags&0x1000 && !flags2&0x1000` gated on the mspace's `0x200` bit; secsize: section's
  `0x100` bit, honouring an explicit alignment via `thunk_FUN_00430ac9`; default: unconditional
  remainder).
- `004115dd fixup_check_bounds` (**the overflow-check function named in the brief**) - given a
  placed relocation's `[lo,hi)` and its region, looks up the region's per-mspace stat record
  matching the relocation's memory-space char and counter; if `report!=0` (verbose/report
  mode), compares `lo` against the region's base (`"%s section \"%s\" %c(%ld) start address
  $%lX less than region %s base address of $%lX"`) and `hi-1` against the region's high address
  (`"...end address $%lX greater than region %s maximum address of $%lX"`), using
  `"Buffer"/"Overlay"/"Absolute"/"Relative"` as the placement-class word depending on the
  section's flags.

### object.c

- `00426437 obj_reserve_entry_get` - finds an unused (`n_scnum==N_UNDEF`) RESERVE-list entry
  for a given symbol, reusing one with the `0x1000` bit clear, else allocates+links a new
  0x1000-byte-block node (`thunk_FUN_0042bfcb`/`0042c1ef`/`0042be92` - symtab.c internals) and
  bumps the global reserve counter; used by `memctl_parse_qualifiers`'s RESERVE handling, not
  by object-file writing proper - almost certainly misattributed to `object.c` by the address
  vote (belongs with memctl's RESERVE keyword, symtab.c-adjacent).
- `00426558 obj_default_ok` - `return 1;` stub, used as the default "ok" result before a real
  check (`FUN_00423710`) overwrites it.
- `00426562 memctl_get_token` (**memctl's lexer, not object.c**) - reads the next
  whitespace/`;`-comment-delimited token from the control file (mode 0), or the rest of the
  current line (mode 4/10, `';'`/`'\n'` stops), through the same buffered-stdio path CRT
  `getc`/`_filbuf` uses directly on `g_memctl_fp`, lower-casing identifier characters into
  `g_memctl_token`; tracks `g_line_number`. (Voted into `object` purely by address; every
  caller is in `memctl.c`.)
- `00427710 obj_layout_offsets` - computes the on-disk byte offsets for every COFF piece
  (`g_obj_scnptr`, `g_obj_rawptr`=`g_obj_scnptr+nscns*0x34`, `g_obj_relptr`,
  `g_obj_lnnoptr`, `g_obj_symptr`) from section/reloc/lineno/symbol counts and the
  absolute-vs-incremental header size (0xc0 vs 0x54 bytes, matching `re/notes/COFF.md`'s
  0x3c-byte optional header at file offset 0x1c+... vs the 0x38-byte linker header), then
  seeks the output file there.
- `0042785f obj_write_file` (**top-level driver**) - if an object file is open: for absolute
  output, writes the `.text`/`.data` fixed section headers
  (`obj_write_text_data_headers`) and, if any symbols were reserved, the RESERVE-list
  reconciliation (`FUN_00429870`, another group's module); always writes/reorders the symbol
  table (`obj_write_symtab`) and, if debug lines are on, the line-number table
  (`obj_write_linenos`); resolves and writes the entry-point (`START`) symbol's final
  address if one was named; then `obj_write_sdi_syms` and `obj_write_headers`.
- `00427941 obj_write_headers` - writes the 0x1c-byte COFF file header (`g_coff_fhdr` staging
  buffer: magic/nscns/timdat/symptr/nsyms/opthdr/flags - matches `COFF.md`'s File header table
  field for field) with flags built from incremental/debug/strip/SDI state, then either the
  0x3c-byte absolute optional header (`g_coff_ohdr_abs`: magic/vstamp/tsize/dsize/bsize + 5
  address/mspace pairs - matches `COFF.md`) or the 0x38-byte relocatable linker header
  (`g_coff_ohdr_inc`: modsize/datasize/endstr/secnt/ctrcnt/relocnt/lnocnt/bufcnt/ovlcnt/majver/
  minver/revno/unused/sditot - matches `COFF.md`, including the note about only being written
  when the SDI flag is set for the trailing `sditot` word), erroring
  `"Cannot write file header/optional header to object file"` on short writes.
- `00427d54 obj_write_text_data_headers` - writes the two synthetic `.text`/`.data` 0x34-byte
  section headers used only by the absolute-file format at fixed offset 0x58 (matches
  `COFF.md`'s section header layout: name/paddr+mspace/vaddr+mspace/size/scnptr/relptr/
  lnnoptr/nreloc/nlnno/flags, with `TEXT`(0x20)/`DATA`(0x40) flags set here via the literal
  0x20/0x40 constants).
- `00427ebb obj_write_section` - writes one input section's COFF section header(s) (array at
  `param+0x74`, computing each member's `scnptr`/`relptr`/`lnnoptr` from the running
  `g_obj_rawptr`/`g_obj_relptr`/`g_obj_lnnoptr`, skipping DSECT/NOLOAD sections' data pointer),
  its raw data (one 32-bit big-endian word per DSP word, `param+0x78`/`0x7c`), and (relocatable
  output only) its 12-byte relocation entries (`param+0x84`, matches `COFF.md`'s
  `r_vaddr,r_symndx,unused`); buffers any line-number entries (`param+0x88`) into the growing
  `g_obj_lnno_buf` array instead of writing them immediately.
- `004282de obj_write_linenos` - writes the accumulated 12-byte line-number entries
  (`address/mspace, l_lnno` per `COFF.md`) in one `fwrite`.
- `00428356 obj_write_symtab` - if any symbols were emitted (via `obj_build_symtab` +
  `obj_reorder_symtab` + `obj_link_symbol_tags` + `obj_patch_symtab_links`, non-incremental
  only), byte-swaps each 8-byte name field in place (`thunk_FUN_004307d5`, skipping aux
  entries via the `n_numaux`-driven stride) and writes the flat 0x20-byte-per-entry symbol
  array (matches `COFF.md`'s Symbol entry table exactly: n_name/n_value/mspace/n_scnum/n_type/
  n_sclass/n_numaux).
- `00428449 obj_build_symtab` - flattens the module's linked symbol list into the COFF array:
  copies name-ptr/value/type-ish fields (`+8,+0xc`) and an aux-entry's length/lnnoptr fields
  (`+0x48,+0x4c` from the symbol's `+0x18,+0x24`), computing `n_numaux` as `end-start` and the
  aux's own trailing fields, one entry+aux per input list node.
- `00428524 obj_reorder_symtab` - large, mostly-mechanical reordering pass moving related
  symbol-table entries (function `0x67`/`0xc8`, block-begin `0x65`, block-end `0x64`(? checked
  as `'b'` byte at `+1`), external-function `0xc9`, tag `0xcb`, and plain `0x3`) so that a
  symbol and everything that must follow it contiguously (its aux entries, per COFF rules) stay
  adjacent after earlier passes may have interleaved them; delegates the actual reordering to
  `obj_link_symbol_tags` for the "function+matching tag" case.
- `00428bc4 obj_link_symbol_tags` - within a `[param1,param3)`/`[param2,param4)` range pair,
  finds the struct/union/enum/array/function TAG entry (`n_type` 10/0xc/0xf) matching a given
  symbol's tag index and patches the symbol's aux `tagndx` field to point at it, reporting
  `"Symbol tag mismatch"` (two message variants: with vs. without a resolvable owning symbol
  name) when none is found.
- `00428e67 obj_patch_symtab_links` - second full pass over the flat symbol array: tracks the
  currently-open function/block/tag scopes and back-patches each one's aux `endndx`/`lnnoptr`
  field once its matching end-marker (`C_EFCN`=`-1`, or the next `0x67`/`200` "begin" of a new
  scope) is seen; reports `"No previous function declaration"` for an orphaned end-marker.
- `0042930e obj_write_sdi_syms` - appends two fixed debug symbols, `"etext"` and one more
  (string at `0x45a770`, owned by object.c, 1392 bytes - likely a second canned name/template,
  not fully read) to the symbol list via `thunk_FUN_00429641` (symtab.c).
- `00429399 obj_write_strtab` - writes the string table: big-endian length word (counting
  itself, matches `COFF.md`) followed by the accumulated NUL-terminated strings, in one write
  of `g_obj_strtab_size` bytes.

### memctl.c

- `00421ec7/00421eef/00421f79/004221bc` - see "Module boundary correction" above; not analysed
  further (out of scope: callers belong to another module).
- `00423710 memctl_process_file` (**top-level driver**) - pushes an initial input-stack frame,
  loops calling `memctl_parse_line` and (when it returns a completed included-file frame,
  i.e. `g_incfile_stack!=NULL`) popping back to the including file's saved position/line/token
  state, until the outermost file hits EOF (checked via the file's `0x10` "at EOF" bit);
  reports `"Region without associated ENDR directive"` if a REGION was left open; runs
  `obj_default_ok` (a currently-trivial "always ok" hook) unless the `g_opt_ro`-gated
  alternate-copy condition applies.
- `00423863 memctl_parse_line` (**per-statement dispatcher**) - see grammar table above; loops
  reading one leading keyword token per statement (skipping `;`-comments), looking it up in
  `memctl_kw_tab`, and dispatching; on any keyword validation failure calls
  `memctl_get_token(4)` to resynchronise to the next line and continues (i.e. one bad line does
  not abort the whole file - matches `compare.py`'s expectation of exercising error paths).
- `00424879 memctl_parse_qualifiers` - see grammar section; the shared `mem[:ctr](map):expr`
  list reader/applier for SECTION/BASE/MEMORY/RESERVE/SECSIZE/REGION/SBALIGN.
- `004250ad memctl_check_region_bounds` (**region overflow check**) - for every per-mspace stat
  record hanging off a closed region, if only some of {base(`0x100000`), high(`0x400000`),
  size(`0x200000`)} were given, derives the rest (`high=base+size-1`, or `size=high-base+1`, or
  `base=high-size+1`); if all three were given and they disagree, reports
  `"Region %s %c(%ld) size/address mismatch"`; if the computed high is still below base
  (`g_opt_abc` gated), reports `"Region %s %c(%ld) high address lower than base address"`.
- `004252ad memctl_assign_region` - links an output section into a region's per-mspace section
  list (dedup-searching by section pointer first), setting the `0x100`(ABSOLUTE, from a bare
  `SECTION name`)/`0x200`(qualified placement) bit on the region-stat record and the
  section-owning-region backlink (`section+0x70`); reports `"Duplicate region assignment for
  section"` if the section already belongs to a different region, `"Section already set as
  absolute"`/`"Duplicate section entry"` for the narrower conflicts.
- `00425470 memctl_do_set` - `SET`/`SYMBOL name[:mspace] value` - parses an optional
  `:mspace` counter-select suffix on the name, evaluates the value expression, defines the
  symbol as a GLOBAL-section absolute symbol.
- `0042568f memctl_do_map` / `00425747 memctl_map_page` / `00425a60 memctl_map_option` - see
  grammar section.
- `00425cf1 memctl_do_option` - parses a comma list of (at most 8-character) 3-letter option
  codes via `memctl_xopt_tab`, setting the boolean globals in the `-x` table above; reports
  `"Illegal option"`/`"Missing option"`/`"Option select error"`.
- `0042609f memctl_do_include` - `INCLUDE "filename"`: resolves the file by trying, in order,
  the name as given, then (if not found) each directory in `g_libpath_list` (the `-p<lpath>`
  search path) prepended, then the same two attempts again with a default extension appended
  (`thunk_FUN_004032e9`, presumably `.ctl`/similar - not confirmed); on success pushes a
  20-byte input-stack frame (saved token-dest ptr, file ptr, module-name index, line number,
  previous frame) onto `g_incfile_stack` and switches `g_memctl_fp` to the new file; reports
  `"Cannot open include file"`.

## Data structures (offsets confirmed by at least one direct field access in the code read)

### Region struct (linked list headed by `g_region_sentinel`)

| off | field | evidence |
|---|---|---|
| +0x08 | head of per-mspace stat-record list | `thunk_FUN_0042c4e2(region,...)` results get linked here; walked at `+0x38` next-link in `memctl_check_region_bounds`/`fixup_alloc_sections` |
| +0x0c | next region (list link) | `local_1c = *(int*)(local_1c+0xc)` in `fixup_alloc_sections`/`fixup_gen_relocs`; also `DAT_00461dcc[3]!=0` check in `fixup_relocate` |

Region name/for-messages field not pinned to an offset from the code read (message printfs use
`**(undefined4**)*piVar1`-style double-indirection through the owning *section*, not the
region struct itself).

### Region+mspace stat record ("region-section" record, returned by `thunk_FUN_0042c4e2`,
symtab.c; 12+ fields, allocation size not observed directly - at least 0x3c bytes used)

| off (int idx) | field | evidence |
|---|---|---|
| +0x08 [2] | flag bits: `0x100000` base given, `0x200000` size given, `0x400000` high given, others unidentified | `memctl_parse_qualifiers` cases 5/7/0xd; `memctl_check_region_bounds` |
| +0x0c [3] | symbol/name ref, used only for error-message text | `thunk_FUN_0042f22f(*(int*)(local_10+0xc))` in `memctl_check_region_bounds` |
| +0x14 [5] | address/value used in `%ld` of the two region error messages | `memctl_check_region_bounds` |
| +0x1c [7] | base address | set by BASE(id 5) in `memctl_parse_qualifiers`; read in `memctl_check_region_bounds` |
| +0x20 [8] | high/end address | set by MEMORY(id 7); read/derived in `memctl_check_region_bounds` |
| +0x24 [9] | size | set by REGION-inline-qualifier(id 0xd); read/derived in `memctl_check_region_bounds` |
| +0x38 | next-record link | list traversal in `memctl_check_region_bounds`, `fixup_alloc_sections` |

### Output/input section struct (returned by `thunk_FUN_0042c1ef`/`0042c13b`, symtab.c; only
the offsets actually dereferenced in fixup.c/object.c/memctl.c are listed - the authoritative
struct almost certainly belongs to whichever group covers symtab.c)

| off | field | evidence |
|---|---|---|
| +0x00 | owning-file/module back-pointer (or name symbol) | `*(int*)*piVar1` dereferenced through `+4` for mspace tag in many fixup.c placers |
| +0x04 | (as `int`) mspace/relocation-type tag | `*(int *)(*(int *)*piVar1 + 4)` throughout fixup.c |
| +0x08 | flags: `0x100`=ABSOLUTE, `0x200`=qualified-placed, `0x1000`=BUFFER, `0x4000`=OVERLAY, `0x20000`=already-relocated | `memctl_assign_region`, `fixup_alloc_sections`, `fixup_check_secsizes` |
| +0x10 | trial start address (working value during placement) | `fixup_save_counters`/`restore_counters`, `fixup_gen_*_relocs` |
| +0x14 | trial end / committed start (see save/restore swap) | ditto |
| +0x18 | requested length or list-head (context dependent; XDEF list head in some paths) | `fixup_size_section`, `fixup_collect_xdefs` |
| +0x1c/+0x20/+0x24 | subsection-list heads for 3 categories (matches `+0x18` "XDEF"/`+0x1c`/`+0x20` "BUFFER" lists walked by `fixup_collect_xdefs_all`/`fixup_collect_buffer_syms`) | fixup.c collectors |
| +0x38 | next-in-parent-list link | pervasive `local_c = *(int*)(local_c+0x38)` |
| +0x44 | next-in-sibling-list link (finer-grained list than +0x38) | pervasive in fixup.c placers |
| +0x4c | running accumulated-length total | `fixup_reloc_length` |
| +0x50/+0x54 | region/committed-length fields used in `fixup_size_section`'s zero-length fallback | `fixup_size_section` |
| +0x70 | owning-region back-pointer | `memctl_assign_region` (`*(int*)(*param_2+0x70)`) |
| +0x74 | section-header array (COFF, `.h`-style, 0x34-byte stride) used only in object.c | `obj_write_section` |
| +0x78/+0x7c | raw-data pointer(s) | `obj_write_section` |
| +0x84 | relocation-entry array (0xc-byte stride) | `obj_write_section` |
| +0x88 | line-number-entry array (0xc-byte stride, buffered not written directly) | `obj_write_section` |

### Free-block / used-range node (fixup.c's own allocator, 20 (0x14) bytes, confirmed by the
`thunk_FUN_0042e170(0x14)` allocation size in both `fixup_freeblk_new` and `fixup_usedrng_add`)

| off | field |
|---|---|
| +0x04 | low/base address |
| +0x08 | high/end address |
| +0x0c | prev link |
| +0x10 | next link |

### COFF file layout

Identical to `re/notes/COFF.md` at every offset checked against object.c's code (file header
0x1c bytes at file offset 0, absolute optional header 0x3c bytes vs. relocatable linker header
0x38 bytes both at file offset 0x1c, section headers 0x34 bytes each, relocation entries 0xc
bytes each, symbol entries 0x20 bytes each, string table length-prefixed) - reused as-is, no
corrections needed. The one addition from this pass: the two synthetic `.text`/`.data`
section headers in an **absolute** file are always written at the fixed offset **0x58**
(`obj_write_text_data_headers`), i.e. immediately after the 0x1c-byte file header + 0x3c-byte
optional header.

## Cross-module interfaces (functions in other modules called from here)

- **symtab.c**: `thunk_FUN_0042c4e2` (find/create region+mspace stat record),
  `thunk_FUN_0042c1ef` (find input subsection by name within a section),
  `thunk_FUN_0042bc50` (find/create a GLOBAL-section symbol for a given mspace+counter),
  `thunk_FUN_0042c13b` (find output section by name), `thunk_FUN_0042c373` (find/create region
  by name), `thunk_FUN_0042c6c1` (define/insert a symbol; `"Duplicate ... symbol"` family of
  errors), `thunk_FUN_0042bed4`/`0042bfcb` (RESERVE-list search/allocate),
  `thunk_FUN_00429641` (insert a canned debug symbol, used by `obj_write_sdi_syms`).
- **eval.c**: `thunk_FUN_0040a370` (evaluate an address expression),
  `thunk_FUN_0040a571` (evaluate allowing a `n%` percentage form, used by SECSIZE),
  `thunk_FUN_0040a4ae` (evaluate as a plain long, used by MAP PAGE numbers),
  `thunk_FUN_0040ca80` (free an evaluated value).
- **util.c**: `thunk_FUN_0042e170`/`0042e1ce`/`0042e19d` (malloc/free/realloc wrappers, `"Out
  of memory - link aborted"` on failure), `thunk_FUN_00430773`/`004307a4`/`004306a1` (the
  actual `fwrite` calls used by object.c - presumably where the big-endian byte order is
  enforced, not visible from this module), `thunk_FUN_00430ac9` (round an address up to an
  alignment boundary), `thunk_FUN_0042f22f` (mspace number -> display char, indexes the
  `" XYLPEDU"` table at `00457ff0`), `thunk_FUN_0042d8d0`/`0042d8f3`/`0042d916` (the three
  keyword-table lookups documented above), `thunk_FUN_0042e4df`/`0042e622`/`0042e743` (lexer
  helpers: quoted string, plain symbol, `mem[:ctr](map):addr` expression).
- **error.c**: `thunk_FUN_00409a25` (plain error), `thunk_FUN_00409bfd` (error + one `%s`),
  `thunk_FUN_004098b0` (fatal, aborts - used for "should never happen" `default:` switch arms
  and I/O failures), `thunk_FUN_00409d88`/`00409f4d` (warning variants).
- **map.c**: `thunk_FUN_0041ee04`/`0041eda4`/`0041ed36` (sort-array-of-N-pointers helpers used
  by fixup.c's `fixup_collect_*` family - odd that a sort utility lives in map.c, but the
  address-vote and callers both agree).

## Quirks / things a rebuild must reproduce

- **Retry loop for incremental links**: `fixup_relocate` re-runs the entire address-assignment
  pass (`fixup_alloc_sections`) with a save/restore of every section's placement state until a
  symtab callback stops signalling a change (`g_pass2_changed`). A from-scratch reimplementation
  must replicate this fixed-point iteration, not just run the pass once, or incremental-link
  output will differ from the original when a symbol's section only becomes known after a
  later file in the link is processed.
- **Combined L/X/Y counters**: several fixup.c functions special-case `param_2`/counter value
  `3` to mean "do it for X *and* Y (and L) together" (`fixup_place_reloc`, `fixup_mark_used`,
  `fixup_update_high_water`, `fixup_write`-style helpers in object.c). A DSP56000 `L` memory
  access is simultaneous X+Y, so this is intentional, not a bug - the rebuild must write to all
  three shadow counters whenever an L-space relocation is placed.
- **Absolute file's synthetic `.text`/`.data` headers are unconditional**: `obj_write_file`
  always calls `obj_write_text_data_headers` for absolute output even if the module produced no
  actual `.text`/`.data`-flagged sections (matching `t.cld`'s dump above, which has both
  present with correct start/end but zero relocations) - byte-for-byte matching requires
  writing these two headers even when empty.
- **One bad memory-control-file line does not abort parsing**: `memctl_parse_line` resyncs to
  the next line (`memctl_get_token(4)`) and keeps going after almost any validation error, only
  a handful of `default:` "should never happen" cases call the *fatal* error function. The
  rebuild's error-path tests should confirm this (matches `CLAUDE.md`'s "Cover error paths
  too").
- **Case-insensitive control file, case-sensitive elsewhere**: `memctl_get_token` lower-cases
  identifier characters as it reads (used before the keyword-table search and before section
  name compares reached via `thunk_FUN_0042c13b`), independent of the linker's global
  `-n`/`g_case_insens` symbol-case option - i.e. section names and keywords in the `-r` file
  are always matched case-insensitively even when symbol names elsewhere are not.
- **RESERVE range reuses freed entries**: `obj_reserve_entry_get` first tries to recycle an
  existing but currently-unused (`N_UNDEF`) RESERVE-list node before allocating a new
  0x1000-byte block, which affects the *order* (not just presence) of generated symbols/aux
  entries if the rebuild allocates fresh nodes every time instead.

## Open questions for whoever finishes the C rewrite

1. Exact semantics of several `-x` option flags (`ABC`, `AEC`, `RO`, `WEX`, `OVLP`, `SVO`,
   `RSC`, `FF`, `CSL`, `WVR`, `OSP`, `ISW`, `WDG`, `MCM`) beyond which boolean global they set -
   most are only *tested* in arith.c/eval.c/map.c/symtab.c (other groups' modules), not here;
   cross-check with whoever covers those.
2. The precise struct/allocation size and full field layout of the "output/input section"
   struct above is necessarily incomplete (only offsets touched by fixup/object/memctl.c are
   listed) - the authoritative version should come from whichever group reconstructs
   symtab.c (the struct's constructors `thunk_FUN_0042c1ef`/`0042c13b`/`0042bc50` all live
   there).
3. `00426562`/`memctl_get_token`'s `param_1==10` mode (vs. `0`/`4`) was read once in
   `memctl_do_option`-adjacent code but not fully traced; likely "read rest of line without
   lower-casing" for a MAP PAGE numeric argument context - needs a live test with `-r` to
   confirm before porting.
4. `00423710`'s exact `param_1` semantics (passed straight through to `memctl_parse_line`)
   were not resolved with certainty; best guess is a "quiet re-scan"/second-pass flag rather
   than region nesting (see function description) - worth confirming with a debugger trace
   before the C rewrite relies on it.
5. Module-boundary correction (see top): `00421ec7/eef/1f79/21bc` almost certainly belong to
   a different module; whoever owns that address range (probably `func.c` or `input.c`) should
   double check.

## Summary

- Named 69 functions (fixup.c 38, object.c 16, memctl.c 15) and ~95 globals (structural bss
  owned by the three modules, the three memory-control-file keyword tables recovered by direct
  binary inspection, and ~50 shared option/flag booleans whose exact keyword/meaning was
  recovered from those tables).
- Main structs identified (with offset evidence): the region list, the region+mspace
  placement-stat record, the fixup.c free-block/used-range allocator node (20 bytes), and the
  subset of the input/output section struct touched by these three modules; the COFF on-disk
  layout is unchanged from `re/notes/COFF.md` and object.c matches it exactly field for field,
  with one addition (absolute file's `.text`/`.data` headers always at file offset 0x58).
- The memory-control-file grammar is fully recovered, including exact keyword spellings and
  numeric ids for all three keyword tables (17 record keywords, 12 MAP OPTION suboptions, 33
  `-x`/OPTION/DSPLNKOPT codes), by disassembling the three table-lookup wrapper functions and
  reading the tables directly out of the binary's `.rdata` - not just inferred from switch
  case numbers.
- Open questions are listed above; the largest is that several `-x` option flags' *behaviour*
  is implemented in other groups' modules and wasn't chased further.
