# l3_map notes: map.c, symtab.c, sdi.c, eval.c, func.c, arith.c (DSPLNK.EXE)

Group l3_map. Special responsibility: global symbol struct, map file format
(column positions), sort orders. Evidence gathered from `re/out/DSPLNK/mod/*.c`
(Ghidra decompilation, `local_NN` offset by +4 from real `[ebp-NN]`),
`re/out/DSPLNK/{modules,functions,strings,globals}.txt`, and live experiments
against `re/bin_ft/DSPLNK.EXE` / `re/bin_ft/ASM56000.EXE` in
`re/notes/DSPLNK/scratch_l3_map/` (kept: `t1.asm`/`t2.asm` sources,
`t1.cln`/`t2.cln` linker inputs — **`.cln` is the DSPLNK link input, not
`.cld`**, `t1.map` a captured real map file, `g.ctl`/`k.ctl` memory-control
files used to toggle `map opt <keyword>`, `dd.py`/`ef/pe.py`/`ef/tab.py`/
`ef/ops.py` PE-reading helpers). Reused the run's leftover `ef/eval.dis`,
`ef/func.dis` disassembly and `ef/used.txt` (data addresses used by the func
dispatch table) rather than redoing them.

ASM56000's own eval/func/arith notes (`re/notes/ASM56000/g3_expr.md`) do not
exist yet at the time of writing (only `g2_symtab.names.txt` is present under
`re/names/ASM56000/`), so no cross-group alignment was possible; names below
are independent and should be reconciled centrally once g3_expr lands.

## IMPORTANT correction: sdi.c module boundary

The brief's working hypothesis was that sdi.c is the unvoted run
`0x42944b-0x429870` (5 functions) at the start of the "symtab" block in
`modules.txt`. **This is wrong.** Evidence:

- Every global those 5 functions touch (`0x461edc`, `0x461ee0`, `0x461ee8`,
  `0x461eec`, `0x461ff8`/hash table, `0x461f04`, `0x461f08`, `0x46c080`,
  `0x46c140`) is voted `symtab` (or `object`) in `globals.txt`, never `sdi`.
- Their code (see `sym_wrt_init`/`sym_wrt_rec`/`sym_wrt_str`/`sym_wrt_name`/
  `sym_wrt_all` at `0x42944b/429641/429716/429811/429870`) iterates the
  **global symbol hash table** (`0x461ff8`, 2003 buckets) and serialises
  flagged (`0x10000`) symbols into two growing buffers (a record array and a
  string pool) — this is incremental-link symbol export bookkeeping, i.e.
  squarely `symtab.c`'s job, not span-dependent-instruction resolution. They
  are called only from `input.c`'s `0x41882a` (a `.cld`/incremental-object
  reader).
- The address range `0x429a31-0x42a300` (2255 bytes) right after these 5
  functions is **not code**: `python re/scripts/x86dis.py re/bin/DSPLNK.EXE
  0x429a31 0x42a300` shows solid `int3` (0xCC) padding — an artefact of
  DSPLNK.EXE's own incremental link (per CLAUDE.md, DSPLNK.EXE itself is
  "incrementally linked"), not sdi.c code. This explains why `modmap.py`'s
  vote propagation stalls there: it is a real gap, not a scrambled module.
- sdi.c's own `$Id` data footprint (`strings.txt`) is `0x45a888` (`$Id:
  sdi.c,v 1.12 1995/02/21 22:25:48 tomc Exp $`) up to `0x45a90f`
  (symtab.c's `$Id` at `0x45a910`) — **only ~136 bytes**, just enough for the
  `$Id` string plus two short C strings:
  `0x45a8bc "Syntax error in expression"` and `0x45a8d8 "%lx"`.
- Those two strings are referenced by exactly one function:
  `0x42b005` (464 bytes), called from `symtab.c`'s `addr_assign`
  (`0x42aa32`) while it finalises a section piece's relocated value. It reads
  a symbol's raw "value" string; if the first character is not an identifier
  char it requires a `$` and `sscanf("%lx", ...)`'s the rest, i.e. it decodes
  the `name$hexvalue` deferred-value placeholder that the assembler leaves
  behind for a symbol whose value could not be fixed until link time
  (classic SDI deferral). Confirmed by the *writer* side: eval.c's
  `term_to_str` (`0x40ae96`) builds exactly that `"%s%lX"` / `"%s%lX%0*lX"`
  format.

**Conclusion: sdi.c is a single very small module. Its one identified
function is `0x42b005` (`sdi_resolve`, module `sdi` in the names file). The 5
functions at `0x42944b-0x429870` are re-assigned to `symtab.c`.** I could not
find further sdi.c-owned code; if it has more functions they are most likely
folded (by MSVC address-order, given the tiny/absent data section makes the
usual vote method blind for sdi.c) among symtab.c's `addr_resolve_all`
(`0x42a84c`)/`addr_assign`/`addr_converge` (`0x42ac5f`) family, which
implement the actual convergence loop for span-dependent pieces (see below) —
but I have no string/data evidence to reassign any of *those* to sdi.c, so
they stay in symtab.c pending better evidence.

## map.c — link map file writer

Purpose: formats and writes the `-m<mapfil>` link map: banner/page headers,
"Section Link Map by Address", "Section Link Map by Name", "Symbol Listing by
Name", "Symbol Listing by Value", "Global Link Map by Memory Space" (only
with `map opt globmap`), and the "Unresolved Externals" listing (to the map
file and, separately, to stderr/console). All output goes through a tiny
"terminal" layer (`map_putstr`/`map_newline`/`map_tab`) that tracks the
current column/line and paginates.

### Output plumbing (verified against a captured real map file, `t1.map`)

- `map_putstr` (`0x41d8d1`) — writes a string one byte at a time through the
  CRT's `_flsbuf`/`FILE` fast path (`MapFilePtr` = `0x461f3c`, a `FILE*`),
  tracking `MapCol`/`MapCol2` (`0x457bbc`/`0x457bc0`) and calling
  `map_newline` on `\n`.
- `map_newline` (`0x41da05`) — if the physical line counter `MapLine`
  (`0x457bcc`) has reached `MapLinesPerPage` (`0x457bd0`) starts a new page
  (`map_newpage`, `0x41db64`), else writes `\n`, resets `MapCol`/`MapCol2` to
  1, then calls `map_leftmargin` (`0x41dac4`) to pad column 1..
  `MapLeftMargin` (`0x457bc8`) with spaces (this is why every map line has a
  blank left gutter).
- `map_newpage` (`0x41db64`, `param_1`=1 to also print the header) — writes a
  form-feed (`\f`, 0x0c) if `MapPaged` (`0x461240`) is set, else pads with
  blank lines up to `MapLinesPerPage` again (i.e. "paged" mode = real `\f`,
  default mode = blank-line pages); bumps `MapPageNum` (`0x461310`) and calls
  `map_pageheader` (`0x41dcc0`).
- `map_pageheader` (`0x41dcc0`) — writes `MapHeaderLines` (`0x457bdc`) blank
  lines, then `map_header` if `MapTitleSet` (`0x457bd8`).
- `map_header` (`0x41dd75`) writes the exact banner seen in `t1.map`:
  3 blank lines are NOT part of it (caller's job); it prints
  `"Linker"+" Version "+"6.3.7 "+"  Release  "+date+"  "+time+"  "+filename+
  "  Page %d\n"` then two blank lines. Matches:
  ```
  DSP Linker  Version 6.3.7   99-07-14  14:00:00  t1.map  Page 1
  ```
  (date/time come from `0x461d48`/`0x461d58`, the same values `-v`/banner use
  elsewhere; with `DAT_00461260` set — an "extended"/64-bit? mode flag shared
  with `dsplnk`/`input` — it instead prints all-zero placeholders, i.e. a
  degraded/short banner form exists but wasn't exercised here).
- `map_putstr_wrap` (`0x41dea5`) — like `map_putstr` but calls `map_newline`
  first if the string would overflow the current line's right margin
  (`MapRightMargin`, `0x457bc4`); used for long output (e.g. `map_header`'s
  fields, "No sections found" style one-liners).
- `map_tab` (`0x41eb80`, argument = absolute target column) — pads with
  spaces up to column `param_1`, or if already past it just writes ONE space
  (this is why misaligned rows in the real map still get a one-space gap
  instead of running together). `map_tab_min` (`0x41feae`) is a simpler
  variant used by the two Symbol Listing tables that only pads (never emits
  the single fallback space).

### `map_write` (`0x41d7d0`) — top-level driver, in this exact order

1. If `NumSecs` (`0x46129c`) is 0: `map_putstr_wrap("No sections found")`.
   Else: `map_sec_by_addr` then `map_sec_by_name`.
2. If `NumSyms` (`0x4612dc`) is 0: if either `OptNosymname`/`OptNosymval`
   (`0x457b64`/`0x457b68`) is *not* set, force a new page and print "No
   symbols found". Else (symbols exist): force a new page if either listing
   is enabled, then `map_sym_by_name`, `map_sym_by_value`.
3. If `MapGlobmap` (`0x461208`, i.e. `map opt globmap` was given) and there
   are sections: new page, `map_global_by_memspace`.
4. If not "incremental" (`0x461248`==0) and there are unresolved externals
   (`NumUndef` `0x4612e0` != `0x4612e4`): new page, `map_unresolved`.

### Section Link Map by Address (`map_sec_by_addr`, `0x41e110`) — column layout

Confirmed byte-for-byte against `t1.map`:
```
Start    End     Length    Section          (16-bit / P,X,Y memory: DAT_00461f44 not in {1,3,4,5})
Start    End         Length    Section      (24-bit memory, or the two special memtypes 0x1c/0x11d)
Start     End           Length     Section  (DAT_00461f44 in {1,3,4,5}: 32-bit/extended)
```
i.e. **three column widths keyed off `MemModel` (`0x461f44`)**: narrow
(`%04lX %04lX %5lu`), medium (`%06lX %06lX %8lu`), wide (`%08lX %08lX
%10lu`), chosen per *memory-space group* (each "X Memory (0 - default)" /
"Y Memory" / "P Memory" block gets its own heading + width, matching
`s_XYLPEDU` space codes X,Y,L,P,E,D,U looked up via the section's memtype
through `thunk_FUN_0042f22f`). Gaps between sections print as
`"UNUSED"`-suffixed rows unless `OptNounused` — **verified**: `map opt
nounused` removes exactly the three `NNNN FFFF nnnnn UNUSED` rows from
`t1.map`, nothing else. Same-address/adjacent sections sharing a class print
an `*Overlap*` marker. Gated by `OptNosecaddr` (`0x457b5c`) — **verified**:
`map opt nosecaddr` drops the whole table, not just a column.

### Section Link Map by Name (`map_sec_by_name`, `0x41ee64`)

Same three-width value formatting, but grouped/sorted by **section name**
first (see Sort orders below); memory-space letter and attribute words
(`REL`/absolute-style flags aren't shown here, only LOCAL/OVERLAY/BUFFER-ish
markers via `map_tab(3)`+letter). Gated by `OptNosecname` (`0x457b60`) —
**verified**: `map opt nosecname` drops the whole table.

### Symbol Listing by Name / by Value (`map_sym_by_name` `0x41f797`,
`map_sym_by_value` `0x4200d0`)

Header: `Name             Type    Value             Section           Attributes`
(by Name) — 17-char dotted name field (`name..............`, padded with
`.` via `strncpy`+space fixups, truncated to 16 + `.` fill, or if
`DAT_004611e0==1`/"wide symbol names" mode the name is printed in full and a
"No symbols"/column-wrap loop kicks in instead — this is the `-x` "long
symbol name" mode). Both tables:
- **verified**: `map opt nosymname` removes exactly "Symbol Listing by
  Name"; `map opt nosymval` removes exactly "Symbol Listing by Value".
- **verified**: `map opt nolocal` (`0x457b50`) drops every `REL LOCAL` row;
  `map opt noconst` (`0x457b54`) drops every `ABS GLOBAL`
  (absolute/constant) row. Both use the same struct fields as below.
- Type column: `int` vs `fpt` from flags bit `0x200` (fpt) vs a second
  candidate bit `0x100`/other (a third, rarer value prints a blank — only 2
  of the 3 branches were exercised by the test symbols).
- Value column: memory-space letter (from `iVar3 = SYM.type` (offset
  `0x2c`, see struct below), via the *same* `X,Y,L,P` mapping as sections,
  default/blank for `iVar3==4` i.e. absolute) then the hex value formatted
  with the same narrow/medium/wide width choice as the section tables, OR
  (flags bit `0x200` set: float) a `%-.6E` scientific literal, OR (flags bit
  `0x800` set) a section+`:`-style variant via `thunk_FUN_004302d1` — this is
  the same "combined hi:lo" path used by `arith.c`'s `term_coerce`; not fully
  traced.
- Attributes: `LOCAL` (bit `0x20`) / `EXTERN` (bit `0x80`) / `GLOBAL` (bit
  `0x40`, i.e. XDEF'd) are mutually exclusive in that priority order, then
  independently `BUFFER` (bit `0x2000`) and `OVERLAY` (bit `0x4000`) can be
  appended. `ABS`/`REL` (the *other* word in `t1.map`'s Attributes column,
  e.g. `REL LOCAL`) is printed earlier, tied to whether the symbol carries a
  section pointer (`SYM.section`, offset `0x48`) vs is absolute.

### Global Link Map by Memory Space (`map_global_by_memspace`, `0x4207e9`)

Only emitted when `MapGlobmap` is set (`map opt globmap` — **verified**: adds
exactly this table, nothing else changes). Header:
```
Start     End       Section          Counter  Symbol              Value
```
(narrow variant has one less leading space, same X/Y/L/P width switch as
above). Per memory space, sections are listed once with start/end/length,
then (unless `OptNoglobsym`, `0x457b70` — **verified**: `map opt noglobsym`
removes exactly the per-symbol sub-rows, keeping the section start/end/name/
counter rows) every symbol *defined in* that section/counter is listed
indented under it, sorted by value (`map_build_sec_symlists`, `0x42154d`,
builds one sorted singly-linked list per (section, counter) pair by walking
the whole global symbol hash table once and inserting each symbol's node in
value order). `*Section Overlap*` / `*Symbol Overlap*` markers use the same
detection pattern as the by-Address table.

### Unresolved Externals

`map_unresolved` (`0x421b2a`, to the map file) and `map_unresolved_stderr`
(`0x421791`, to `DAT_00461f34`, a second `FILE*` — console/error stream) are
near-duplicates: both collect the *undefined-external* hash table
(`0x465e98`, 2003 buckets, distinct from the symbol table) into an array,
sort it (name, then...), and print `name (file1)(, file2)(, file3)...`
groups exactly like:
```
Unresolved Externals:

undef1 (t2.cln)
undef2 (t2.cln)
```
`(command line)` is substituted when the referencing "file" pointer is null
(i.e. `-u<symbol>`-defined externals). With `DAT_00461260` set, `.cln`/`.cld`
suffixes get swapped to a different extension via `strrchr`+`strcpy`
(the "short name" mode again).

### Sort orders (comparator functions; all installed via a tiny thunk that
sets a global compare-fn pointer `SortCmpFunc`/`0x461dc8` and an array
pointer `SortArrayPtr`/`0x461f18` then calls a generic `qsort`-style helper,
`thunk_FUN_0042e25d`, outside these modules)

- `sec_cmp_addr` (`0x41ebe0`, used by Section-by-Address): memtype
  (`FUN_00421f79`, case/alpha-ish string-ish compare — not one of my
  modules) → counter/base (`+0x10`) → start addr → end addr (descending) →
  section name (`strcmp`) → "is-overlay"(`0x1000`) tie-break.
- `sec_cmp_size` (`0x41ed5e`): section length descending. No confirmed
  caller found within map.c/symtab.c; likely used elsewhere (memctl auto-
  align?) — low confidence, left unassigned to a table.
- `sec_cmp_name` (`0x41f483`, Section-by-Name): name (`strcmp`) → memtype →
  counter → start → end (descending) → overlay tie-break. Same as
  `sec_cmp_addr` but name-first.
- `sym_cmp_name` (`0x41fef4`, Symbol-by-Name): name (`strcmp`) → symbol's
  owning section's memtype → numeric value (float compare via
  `term_int_to_double`/`term_long_to_double`, i.e. compares mixed int/float
  symbol values correctly).
- `sym_cmp_value` (`0x420653`, Symbol-by-Value): only compares *exported*
  symbols (has a section, or the "special" flag `0x20000`) by numeric value
  first, name as tie-break; un-exported symbols fall through to a plain name
  compare (kept out of the printed table anyway).
- `sec_cmp_memspace` (`0x421674`, Global-Link-Map-by-Memory-Space): memtype →
  start → end (descending) → name — i.e. same family as `sec_cmp_addr` but
  without the counter/overlay tie-breaks (used to group into the X/Y/P
  headings and order sections within each).
- `cmp_generic1`/`cmp_generic2` (`0x41edcc`/`0x41ee2c`): present in map.c's
  address range but I found no caller inside map.c/symtab.c and did not
  trace their field semantics fully — flagged low confidence, likely used by
  a different module (object.c/fixup.c) for a table also housed in this
  address block, or dead/unused code carried over from a shared template.

### `map opt` / `-x` keyword table (confirmed via `re/bin_ft` experiments)

Binary string table at `0x458970..0x458a30` (shared "linker option" keyword
list, used by both `-x<opt>[,<opt>...]` and the memory-control-file `map opt
<keyword>` directive — see `g.ctl`/`k.ctl`): `globmap, nobuffer, noconst,
noglobsym, nolocal, nooverlay, nosecaddr, nosecname, nosymname, nosymval,
nounused, noeso`. All flags default **on** (i.e. everything shown) except
`globmap` which defaults **off**; each `no*` keyword clears one
`OptNo*`/`0x457bXX` byte flag consumed by map.c (table in the names file).
`noeso` and `nooverlay`/`nobuffer` were not empirically distinguishable with
the tiny test program (no overlay/buffer sections available); `nooverlay`/
`nobuffer` are code-inferred with high confidence from the
`(piVar1[2]&0x2000)==0 || OptNobuffer` / `&0x4000 ... OptNooverlay` guards
used throughout map.c's section loops. `noeso` remains unidentified (its
flag byte was not isolated — candidates are `0x461248`/`0x46122c`/
`0x461238`, which also gate the "incremental"/pass-2/overlap-check paths
seen in map.c and symtab's `sym_wrt_*`, so `noeso` may mean "no
extra-symbol-output" for incremental-link mode rather than a plain map
table toggle).

## symtab.c — global symbol table, section table, hashing, -n

### Global symbol struct (`SYM`), 0x68 = 104 bytes, malloc'd by `sym_enter`
(`0x42c6c1`) — **the size is directly proven**: `sym_enter` copies exactly
`0x1a` (26) dwords from a caller-built template into the new record, then
`thunk_FUN_0042e170(0x68)` backs it. Hashed by `thunk_FUN_0042e3f9(name)`
(0..0x7d2, table size 2003=`0x7d3`) into `SymHashTab` (`0x461ff8`); the
per-bucket singly-linked chain pointer lives at **offset 0x60** (dword 24) —
same field slot is reused for the "local"/scope-limited symbol chain off a
class node's local-scope head. Fields identified by evidence (function+
offset; dword index in parens):

| off  | field | evidence |
|------|-------|----------|
| 0x00 (0) | `name` (malloc'd `char*`, case-folded if `-n`) | `sym_enter` `strcmp`s, calls `thunk_FUN_00430037` (uppercase-fold) when `CaseInsens` set |
| 0x08-0x0c (2,3) | value, low/high dword *or* IEEE double | `map.c` sort comparators: `*(double*)(sym+2)` when flags bit `0x800` set, else `term_long_to_double(sym[3],sym[4])`/`term_int_to_double(sym[4])` |
| 0x10 (4) | value low dword (int case) | as above |
| 0x14 (5) | compared against `DAT_00461f60` in `term_to_str` (word-size discriminator?) | `eval.c` `term_to_str` |
| 0x28 (0xa) | **flags** bitfield | `map_sym_by_name`/`by_value`: `0x20`=LOCAL, `0x80`=EXTERN, `0x40`=GLOBAL(XDEF'd), `0x2000`=BUFFER, `0x4000`=OVERLAY, `0x200`=float(`fpt`), `0xc0`=mask used by `OptNoconst`, `0x20000`="special"/placeholder (forces type=ABS(4) and clears value fields), `0x10000`= "referenced/export" (tested by `sym_wrt_all`) |
| 0x2c (0xb) | `type`/memory-space-of-value: 0=P?,1=X?,2=Y?,3=L?,4=ABS,0x1c/0x11d/0x11f=special | `map_sym_by_name` switch; also duplicate-check in `sym_enter` (`piVar1[0x12]==0` = "special symbol") |
| 0x48 (0x12) | owning **section** pointer (0 for absolute/global constants) | `map_sym_by_name`: `puVar1[0x12]!=0` gates whether a symbol is printed at all (must be exported or special) |
| 0x60 (0x18) | hash/scope chain next | `sym_enter` |

Not all 26 template dwords were individually pinned down (several are
copied verbatim from the caller without being read again inside these
modules); the table above lists only the fields this group's functions
actually dereference.

### Section-name / section-class / section-piece structures

Three-level structure, all reachable from `SecHashTab` (`0x463f48`, 2003
buckets, hashed the same way as `SYM`, case-folded under `-n`):

1. **Section-name entry** (0x14=20 bytes, `sec_name_intern`/`0x42bfcb`):
   `[0]` malloc'd name, `[1]` user/auto section number (`SecNumSeed`,
   `0x461298`, auto-increments), `[2]` head of class-node list, `[3]`
   unused/reserved (zeroed), `[4]` hash-chain next.
2. **Class node** (0x78=120 bytes, `sec_class_intern`/`0x42c1ef`, keyed by
   `(memtype, counter)` pair): `[+8]` memtype, `[+0x10]` counter, `[+0x18]`
   head of "piece" list #1, `[+0x1c]`?, `[+0x20]`?, `[+0x24]` head of
   "piece" list #2 (used by `sec_all_reset`/`sec_class_free` alongside
   list #1 — two parallel piece lists per class, purpose of the split not
   determined; possibly resolved-vs-unresolved or global-vs-local pieces),
   `[+0x74]` hash-chain next (`sec_class_find`, `0x42c32f`), `[0x1d]`
   (dword) also chains into the section-name entry's own `[+8]` list — this
   is a *second* linkage independent of the (name→class) hash, used by
   `addr_resolve_all` to walk "all classes of all sections" in bucket order.
3. **Section piece / class-default instance** (0x48=72 bytes,
   `class_node_alloc`/`0x42be92`, and enlarged variant 0x44=68 bytes built
   field-by-field by `sec_piece_new`/`0x42a38f`): `[0]` owning class-node
   pointer, `[2]` flags (`0x1000`=local/no-suffix?, `0x2000`=BUFFER,
   `0x4000`=OVERLAY, `0x20000`=? extra), `[3]`/`[4]` unresolved/resolved
   start? and low bits used for extended addressing, `[4]` start address,
   `[5]` end address (this is the `piVar1[4]`/`piVar1[5]` pair map.c's
   section tables print as Start/End), `[0x10]` counter/high-order value
   (used together with `*piVar1+8` = class node's memtype in every map.c
   section-table `local_3c`/`local_34` comparison), `[0x11]` next-pointer in
   the class node's piece chain, `[0x12]` back-pointer to an "overlay
   parent" class node when the `0x40000` flag is set (`addr_assign`).

`sec_lookup_create` (`0x42bc50`) is the `-o<mem><ctr><map>:<origin>` /
section-directive entry point: looks up-or-creates the name entry, then the
class node, then (only with `create!=0`, i.e. an actual output section, not
just an address query) allocates a memory-region default-address record
(`memreg_alloc`, `0x42c58b`) chained per `(mem,ctr)` bucket (`0x461de8`) and
bumps `NumSecs`.

### Span/address resolution (the actual SDI convergence loop)

`addr_resolve_all` (`0x42a84c`) is the top-level driver: for every class
node reachable through the section hash table's two piece-lists, if it has
a per-piece offset array (`class[+0x38]`, i.e. it was touched by a previous
pass) it's freed, then `addr_assign` (`0x42aa32`) builds a fresh 0x2c=44-
byte-stride offset-record array (one record per piece) copying each piece's
base fields and, for "extended"/overlay classes, adding the overlay's or
class's base address; for pieces whose value still needs runtime resolution
it calls `sdi_resolve` (`0x42b005` — see sdi.c section) and stores the
result, else marks the piece "self-referential" (`0x10000` bit). `
addr_converge` (`0x42ac5f`) then repeatedly (`while(!done)`) walks all
offset records, using `opsize_fits` (`0x42b501`) to check whether a
resolved value still satisfies its chosen DSP56000 operand-size encoding
(range tables for opcodes `8,0xc,0x45,-0x4d,-0x37,-0xf,-0x58,-0x5eb`, i.e.
byte/12-bit/PC-relative/short-branch/etc. immediate field widths — "Invalid
operand size" on an unrecognised code), and re-marks overlapping/oversized
pieces (`0x100`/`0x200` bits) until a fixed point is reached — classic
span-dependent-instruction relaxation, just implemented on the *linker*
side of the assembler/linker split (the assembler emits provisional
sizes + a `name$hexvalue` deferred term; the linker's `addr_converge`
re-checks and finalises them once real section addresses are known).
`opsize_fits`'s error path (`"Invalid operand size"`) is at `0x45a8e0`,
i.e. still inside sdi.c's tiny data range — a second piece of evidence that
this convergence machinery is what sdi.c narrowly exists to drive, even
though the driving *functions* physically live in the symtab.c code block.

### Case-insensitive mode (`-n`)

`CaseInsens` (`0x461214`) is checked by every hash/lookup entry point that
takes a caller-supplied name (`sec_class_lookup`, `sec_name_intern`,
`sec_name_lookup`, `file_name_intern`, `sym_enter`): the name is `strcpy`'d
into a 512-byte stack buffer and passed through `thunk_FUN_00430037`
(upper/lower-case fold, lives in `util.c`, not traced further) *before*
hashing/interning/storing, so both the hash bucket and the stored name are
folded — i.e. `-n` genuinely normalises stored names, it doesn't just
relax comparisons.

### Memory-region records

`memreg_alloc`/`memreg_find`/`memreg_map_or_create` (`0x42c58b`/`0x42c67b`/
`0x42c4e2`) maintain a small linked list per `(memspace,counter)` bucket
(`0x461de8`) of 0x3c=60-byte records: `[0]` owner class pointer, `[3..6]`
copy of the requested range, `[8]` default address-format mask (chosen from
`PTR_DAT_00458314` array indexed by counter, or `AddrMaskNarrow`/
`AddrMaskWide` otherwise) — this is the memory-control-file `region`/
`memory` directive's backing store; "Remapping region" (`0x45a978`) warns
when the same key is redefined without `-x`'s "allow remap" bit set.

## eval.c — expression tokenizer/parser front end

- `get_op_code` (`0x40ab66`) recognises the operator at the current parse
  pointer (`ExprPtr`, `0x461d68`) and returns a 1-22 opcode, **directly
  fixing the operator table**: `1=+ 2=- 3=* 4=/ 5=& 6=| 7=^ 8=% 9=<< 10=>>
  11=< 12=> 13== 14=<= 15=>= 16=!= 17=&& 18=|| 19=# 20=@ 21=: 22=!`. `:` does
  extra lookahead (`isalpha`-ish check 4 bytes on) to disambiguate a
  section-relative `sect:offset` colon from an expression operator.
- `op_precedence` (`0x40ade2`) maps the same opcodes to precedence classes
  1 (tightest: `* / %`) .. 7 (loosest: `&& ||`), classic precedence-climbing
  table: `2`={+,-}, `1`={*,/,%}, `6`={&,|,^}, `3`={<<,>>}, `4`={<,>,<=,>=},
  `5`={==,!=}, `7`={&&,||}. `#`,`@`,`:`,`!` (19-22) aren't binary-precedence
  ops in this table (they return 0 / are handled specially — `!` is unary,
  `@` starts the func-call syntax handled by func.c, `:` is the section-
  colon construct, `#` is consumed by `term_coerce` in arith.c).
- `op_bad` (`0x40ae82`) is opcode-0's handler: `"Expression operator
  failure"` — the sentinel/error case in the 23-entry dispatch table
  (`re/notes/DSPLNK/scratch_l3_map/ef/ops.py` dumped it: entries 1-22 point
  into arith.c, entry 0 points back here).
- `eval_expr` (`0x40af6e`, 6107 bytes — by far the largest function in
  these 6 modules) is the actual recursive-descent/precedence-climbing
  parser: literal forms (binary `%`, hex `$`, decimal, floating, string,
  `(`, `[`, `{` grouping — all three bracket kinds are accepted, each with
  its own "Missing ')'/']'/'}' in expression" message), relative-value
  handling ("Invalid relative expression"), symbol lookup ("Section map
  lookup failure" when a section-relative symbol can't be placed), and
  applies `get_op_code`/`op_precedence`/the arith.c dispatch table in a
  loop. Not traced statement-by-statement (huge switch-like control flow);
  documented at the structural level per the brief's guidance.
- `eval_line`/`eval_int`/`eval_abs`/`eval_uns`/`eval_uns_noforward`/
  `eval_rel_int` (`0x40a571`,`0x40a370`,`0x40a3e6`,`0x40a4ae`,`0x40a4fd`,
  `0x40a772`) are thin wrappers around `eval_expr` enforcing a required
  result shape (integer / absolute / non-negative / no-forward-ref /
  PC-relative-integer) via the matching error string, used by the memory-
  control-file directive parsers (`origin:`, `secsize`, etc. in memctl.c)
  and by fixup.c for relocation expressions.
- `term_to_str` (`0x40ae96`) / `term_to_str_colon` (`0x40c749`) render a
  term back to text: `%-.15E` for floats, `"%s%lX"`(name+hex) or
  `"%s%lX%0*lX"` (name+hi+lo) for the SDI-deferred placeholder form that
  `sdi_resolve` (symtab.c) parses back, and a `":$%08lX"` variant. This is
  how the assembler/linker round-trip an unresolved span-dependent value
  through the `.cld`/memory-control text format.
- `term_stack_pop` (`0x40ca80`): `"Expression stack underflow"` — pops the
  parser's operand stack.
- `term_binop_apply` (`0x40a7ed`): `"Operation not allowed with address
  term"` — applies a binary operator while enforcing that address/section-
  relative terms only allow the operators that make sense on them.
- `eval_helper1`/`eval_helper2` (`0x40c8ab`/`0x40c91d`): no strings, not
  traced (low confidence stack/term-copy helpers).

## func.c — `@function(args)` expression functions

`func_call_eval` (`0x4128e0`) is the entry point (`"Missing '(' for
function"`, `"Invalid function name"`, `"Invalid function type"`, `"Extra
characters in function argument or missing ')'"`). The function-name table
(confirmed directly from the binary via `ef/tab.py`, at `0x458278`, 14
entries of `{namestr, index}`):

| name | index | name | index |
|------|------:|------|------:|
| `fbf` | 1 | `imax` | 8 |
| `lrf` | 2 | `imin` | 9 |
| `enc` | 3 | `ceil2` | 0xa |
| `fb2` | 4 | `szck` | 0xb |
| `byt` | 5 | `aenc` | 0xc |
| `sdi` | 6 | `lb` | 0xd |
| `sdi2`| 7 | `hb` | 0xe |

i.e. the memory-control-file/relocation-expression language has `@FBF`,
`@LRF`, `@ENC`, `@FB2`, `@BYT`, `@SDI`, `@SDI2`, `@IMAX`, `@IMIN`, `@CEIL2`,
`@SZCK`, `@AENC`, `@LB`, `@HB`. This directly explains input.c's `"Invalid
@SDI expression"` message (`0x4573a0` range, function `0x41839c`) — `@SDI`/
`@SDI2` are ordinary func.c functions, evaluated the same way as `@IMIN`
etc., most likely used in memory control files to query whether an address
falls inside / query the size of a span-dependent instruction. I could not
confirm a clean 1:1 mapping of func.c's other 12 functions to these 14
names (`func_call_eval` is only 968 bytes for 14 functions, so most of the
per-function logic is likely table-driven rather than one dedicated
function each); the following are string-evidence guesses, marked
`medium`/`low` in the names file:
- `func_fbf`/`func_fb2` (`0x412d95`/`0x413290`, identical error pair `"Bit
  mask cannot span more than eight bits"`/`"Empty bit mask field"`) — likely
  `@FBF`/`@FB2` (bit-field encode, 1 vs 2-word forms).
- `func_byt` (`0x413acf`, `"Byte-addressable value too large"`) — likely
  `@BYT`.
- `func_imin_imax` (`0x4130a7`, two-arg, `"Relative expression not
  allowed"`+`"must be integer"`+comma) — likely shared `@IMIN`/`@IMAX`
  implementation.
- `func_multiarg1/2/3` (`0x4133da`/`0x4136d0`/`0x413832`) have many repeated
  `"Syntax error - expected comma"` (and `0x413832` also "expected
  terminating constant") — multi-argument functions, not identified by
  name; candidates are `@AENC`/`@SZCK`/`@LRF`/`@ENC`/`@CEIL2`/`@LB`/`@HB`.
- `func_name_lookup`/`func_arg_count`/`func_helper1`/`func_helper2`/
  `func_int_arg` (`0x412ce0`,`0x412d06`,`0x412d46`,`0x4133aa`,`0x412f0d`):
  small (38-79 byte), no strings — likely table lookup / arg-count / single-
  int-arg-check helpers shared by several `@name`s. Low confidence.

## arith.c — TERM arithmetic (the operator dispatch table's targets)

TERM struct (partially reconstructed from usage, not a single allocator
found in these 6 modules — likely allocated by eval.c's stack machine):
offset `+8` (as a `double*`, i.e. byte offset 16) holds a type tag (`0x100`
seen = "extended/long" numeric term), with the numeric payload occupying
the first two dwords either as a genuine `double` (`term_int_to_double`/
`term_long_to_double`, `0x40848c`/`0x4084f1`, convert an int or a hi:lo
long pair to `double` respectively — confirmed by both `map.c`'s symbol
sort comparators calling them to compare mixed int/float symbol values).

54 functions; the central 23-entry operator table (`re/notes/DSPLNK/
scratch_l3_map/ef/ops.py`, index = `get_op_code`'s return value) pins down
22 of them with `high` confidence purely from the index↔token mapping in
`eval.c`'s `get_op_code`:

`term_add`(1,+) `term_sub`(2,-) `term_mul`(3,*) `term_div`(4,/)
`term_and`(5,&) `term_or`(6,|) `term_xor`(7,^) `term_mod`(8,%)
`term_shl`(9,<<) `term_shr`(10,>>) `term_lt`(11,<) `term_gt`(12,>)
`term_eq`(13,==) `term_le`(14,<=) `term_ge`(15,>=) `term_ne`(16,!=)
`term_land`(17,&&) `term_lor`(18,||) `term_coerce`(19,#) `term_op_at`(20,@)
`term_colon`(21,:) `term_not`(22,! — unary).

Range-check helpers (string-confirmed): `pcrel_range_check` (`"Pc relative
value out of range"`), `signed_range_check` (`"Signed value out of
range"`), `unsigned_range_check` (`"Unsigned value out of range"`).
`term_reloc_compat` (`0x405bff`) is called from inside `term_add` to decide
whether two relocatable terms may legally be combined (guarded by
`DAT_00461200`, an "allow mixed section arithmetic" mode flag).

The remaining ~28 functions (`arith_helper1..15`, `term_ctor1..3`,
`term_fp_helper1..4`, `term_negate`, `term_complement`, `arith_stub_true`)
have no strings and were not individually traced — per the brief's "work
carefully rather than exhaustively" guidance for large families, they are
named generically with `low` confidence and grouped by apparent role (TERM
constructors/setters, unary negate/complement, floating-point-specific
arithmetic variants of add/sub/mul/div). Revisiting them would need
step-through disassembly against a live `eval_expr` test case (e.g. via
`re/scripts/x86dis.py` and small crafted `.asm` expressions), which was out
of scope for the time available in this pass.

## Cross-module interfaces used

- `arith.c` TERM operators are reached only through `eval.c`'s dispatch
  table (`get_op_code` → table → operator function), never called directly
  by map.c/symtab.c.
- `symtab.c`'s `addr_assign` calls `sdi_resolve` (sdi.c) and, indirectly
  through the term value, `arith.c`'s `term_int_to_double`/
  `term_long_to_double` (via map.c's sort comparators, not symtab.c
  itself).
- `map.c` never touches the symbol/section hash tables directly except
  through `map_collect_secs` (`0x41f5d6`) and the two `local_18/local_20`
  hash-walk loops in `map_sym_by_name`/`map_sym_by_value`/
  `map_global_by_memspace` — these duplicate symtab.c's 2003-bucket walk
  pattern rather than calling a shared iterator, so the "walk the hash
  table" idiom (`for(bucket=0;bucket<0x7d3;...) for(entry=table[bucket];
  entry;entry=entry->next)`) appears independently in both modules; keep
  that duplication when translating rather than inventing a shared
  function that doesn't exist in the original.
- `input.c`'s `0x41882a` (memory-control/incremental-object reader) is the
  only caller of symtab.c's `sym_wrt_*` family.
- `func.c`'s `@SDI`/`@SDI2` are evaluated the same way as any other `@name`
  function by `func_call_eval`; I found no direct call from func.c into
  `sdi_resolve` — they likely read different state (an in-progress SDI
  table, not yet located) rather than reusing the linker's own
  post-link resolver.

## Quirks / things to reproduce byte-for-byte

- **`.cln` vs `.cld` confusion for testers**: `ASM56000 -b<file>.cld`
  produces a *pair* `<file>.cld`+`<file>.cln`; DSPLNK's link-input files are
  the **`.cln`** ones, not `.cld` (confirmed empirically — feeding `.cld`
  gives `"Cannot read file header from object module"`). Worth a comment in
  `tests/` so nobody wastes time on this again.
- Map file pagination has two independently switchable behaviours
  (`MapPaged`/`0x461240`): real `\f` form-feeds vs. blank-line-only page
  breaks — both must be reproduced exactly since `tests/compare.py` diffs
  output byte-for-byte.
- The three-width (narrow/medium/wide hex) column selection in every map
  table is driven by `MemModel` (`0x461f44`) **and**, independently, by
  whether the *current section's* memtype is one of the two special values
  `0x1c`/`0x11d` (both trigger the wide/medium format regardless of
  `MemModel`) — a naive single-flag reimplementation will misalign columns
  for those memory types.
- `map_tab`'s "already past target column → emit exactly one space" rule
  is easy to drop when porting to a printf-based reimplementation; it's
  directly visible in real map files as irregular spacing when a section/
  symbol name is longer than its column budget.
- Y2K: `map_header` prints whatever date/time strings the caller built
  (see `dsplnk`'s own module for the actual `sprintf` of the 2-digit year);
  map.c itself just relays `0x461d48`/`0x461d58` — flagged here in case
  `dsplnk`'s group missed it, since the captured `t1.map` banner
  (`99-07-14`) shows the 2-digit-year format that will need reproducing
  verbatim including any Y2K rollover bug in the owning module.

## Summary

- Named 149 functions (36 map, 28 symtab + re-homed the 5 wrongly-guessed
  "sdi" ones into symtab, 1 sdi, 16 eval, 13 func, 54 arith) and 40 globals
  in `re/names/DSPLNK/l3_map.names.txt`.
- Main structs found: global `SYM` symbol record (0x68 bytes, 26-dword
  template, hashed 2003-bucket table with case-fold-on-insert `-n` mode),
  section-name/class-node/section-piece 3-level structure (0x14/0x78/0x48
  bytes), memory-region record (0x3c bytes), map-file pagination state
  (`0x457bbc..0x457bdc`), and the `map opt`/`-x` keyword table (12
  keywords, mostly empirically confirmed against real map-file diffs).
- Key correction: sdi.c is not the `0x42944b-0x429870` range (that's
  symtab.c's incremental-symbol-export writer); sdi.c is a single tiny
  function, `sdi_resolve`/`0x42b005`, pinned down via its own `$Id`-range
  strings.
- Open questions: exact byte layout of the remaining ~15 `SYM` template
  dwords; the two parallel piece-lists per section class node
  (`[+0x18]`/`[+0x24]`, purpose of the split); `noeso` keyword's flag
  address; a clean name-to-function mapping for 9 of func.c's 13 functions
  against the 14 `@name` table entries; individual identities of ~28
  arith.c helper functions (float-specific op variants, term
  constructors); whether sdi.c has any function besides `sdi_resolve`
  (none found, but the tiny/near-absent data footprint means the usual
  vote method can't rule additional ones out with certainty).
