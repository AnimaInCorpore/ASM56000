# g5_pseudo - pseudo.c, data.c, scs.c

Source: `re/out/ASM56000/mod/pseudo.c` (50 funcs), `mod/data.c` (16 funcs),
`mod/scs.c` (32 funcs). Cross-checked against `re/out/ASM56000/globals.txt`,
`functions.txt`, `strings.txt`, and `re/names/ASM56000/g2_symtab.names.txt`
(section/symtab names, already applied, used here to confirm shared
functions such as `sec_local`/`sec_global`/`sec_xdef`/`sec_xref`/`sec_endsec`/
`sec_section`). Live-tested with `re/bin_ft/ASM56000.EXE -a -b -l` against
`re/notes/ASM56000/scratch_g5_pseudo/t1.asm` (SCS constructs) - listing in
`t1.lst` in the same directory, reused from the interrupted prior run.

## 1. pseudo.c - directive table and dispatch

### 1.1 Overall shape

Every recognized directive keyword is pre-resolved by the tokenizer (a table
in the data-only `mchglb`/`asmglb` modules, not decompiled - see globals.txt
lines around `0x450624-0x450840` for a fragment of the plain-text keyword
table: `align baddr buffer comment define endif endsec force global himem
ident include local lomem maclib macro nolist pmacro rdirect section stitle
title undef`; most keyword strings are *not* recoverable via the plain-ASCII
string scan because the real table interleaves each name with binary
length/opcode bytes, so `strings.txt` only shows the entries that happen to
be preceded by a printable byte). The resolved token is a small struct;
`pseudo_dispatch` (`0042b240`, `FUN_0042b240`) reads two bytes of it:

* `token[4]` - the **directive opcode**, 0x00-0x48 (73 codes), used as the
  `switch` selector.
* `token[5]` - a secondary byte passed to `pseudo_check_label_use`.

```c
int pseudo_dispatch(void *tok)
{
    iVar1 = pseudo_allowed_in_do(tok->byte4);   /* 0042bafc */
    pseudo_check_label_use(tok->byte5);          /* 0042baac */
    if (iVar1 == 0) {
        /* directive not allowed while inside buffer decl / DO-loop body:
           print "Illegal directive in buffer declaration" or
           "Illegal directive inside DO loop", except a single
           whitelisted case (closing ')' token matching s_...f9c). */
    }
    DAT_0045f860 = operand_text;   /* current-operand cursor, shared global */
    switch (tok->byte4) { case 0: ... case 0x48: ... default: "Directive
        select error" }
}
```

`pseudo_allowed_in_do` (`0042bafc`) returns 0 (illegal inside a DO loop
body) for opcodes `{1,2,3,5,6,0xb,0xc,0x13,0x17,0x26,0x29,0x2a,0x31,0x46}` -
exactly the directives that move location counters or restructure sections
(DSM/BADDR/BSR/BSM/BUFFER/DS-variants/SYMOBJ/ENDSEC/MODE/OPT/ORG/SECTION/a DC
variant). `pseudo_check_label_use` (`0042baac`) prints "Label field ignored"
when byte5==0 and a label was present, and for byte5==2 forces a
`sec_debug_sym` update - i.e. byte5 encodes "how this directive treats the
label field" (0=none allowed, 2=defines a debug/section symbol, other=label
is the directive's own operand, e.g. EQU/SET/DEFINE/UNDEF).

### 1.2 Opcode -> directive table (evidence-based)

Confidence: **high** = confirmed by an exact matching error-message string or
a cross-module name already in `g2_symtab.names.txt`; **med** = strong
structural/behavioural evidence; **low** = plausible guess, flagged as open
question. "-" = handler lives outside pseudo/data/scs (another group's
module) and was not analysed here.

| op | handler | directive | conf | notes |
|----|---------|-----------|------|-------|
|0x00|(inline, `uVar3=1`)|? |low| always succeeds, does nothing; candidate: default/blank case, or ALIGN (see 1.1's recovered keyword list) |
|0x01|`pseudo_dsm` 0040e1a6|**DSM**|med| fixed type=0x400 (modulo) into `data_reserve_common`|
|0x02|`pseudo_baddr` 0040e25f(0)|**BADDR**|med| reads `m`/`r` type letter ("Invalid buffer type"), one-shot (no ENDBUF bracket) - matches recovered keyword `baddr`|
|0x03|`pseudo_block_reserve` 0040d7c7(0x800,0)|**BSR**|med| fixed type=0x800 (reverse-carry)|
|0x04|`pseudo_bsc` 0040ccad|**BSC**|high| count + optional fill expr|
|0x05|`pseudo_block_reserve` 0040d7c7(0x400,0)|**BSM**|med| fixed type=0x400 (modulo)|
|0x06|`pseudo_buffer` 0040e3f6|**BUFFER**|high| reads `m`/`r` type, saves counters `buf_save_xctr/yctr` for ENDBUF; keyword confirmed in table|
|0x07|(inline)|?|low| parses one symbol-like token via `FUN_0043b405`, calls `FUN_00424733`|
|0x08|`pseudo_comment` 0042fec3(0)|**COMMENT**|high| "Unexpected end of file - missing COMMENT delimiter"; keyword confirmed in table|
|0x09|`pseudo_dc` 0040bb20|**DC**|high| generic DC (current default space)|
|0x0a|`pseudo_define` 0042bba2|**DEFINE**|high| "DEFINE symbol must be a global symbol name"; keyword confirmed in table|
|0x0b|`pseudo_ds_typed` 0040df7a(0x400,0)|**DS** (X: default)|med||
|0x0c|`pseudo_ds_typed` 0040df7a(0x800,0)|**DS** (Y: default)|med||
|0x0d|`pseudo_ds` 0040dd85|**DS** (P:/generic)|med-high||
|0x0e|`FUN_0041fb89`|-|-|outside our modules|
|0x0f|`FUN_0041fcec`|-|-|outside our modules|
|0x10|`FUN_0041fe57`|-|-|outside our modules|
|0x11|`FUN_004200bc`|-|-|outside our modules|
|0x12|(inline error only)|**ELSE**|high| real ELSE is consumed by `pseudo_if_skip`/`pseudo_if_body`'s own line scan; this case only fires for a stray top-level ELSE|
|0x13|`pseudo_symobj` 00430015|**SYMOBJ**|med| "Memory space must be P or NONE"; keyword listed by brief|
|0x14|`pseudo_endbuf` 0040e572|**ENDBUF**|high| "ENDBUF without associated BUFFER"; keyword confirmed|
|0x15|(inline error only)|**ENDIF**|high| confirmed self-consistently: `pseudo_if_skip`/`pseudo_if_body` treat token-type 0x15 as ENDIF while scanning|
|0x16|(inline error only)|**ENDM**|high| "ENDM without associated MACRO directive" (macro.c owns real handling)|
|0x17|`sec_endsec` 00435924 (group2)|**ENDSEC**|high| keyword confirmed in table|
|0x18|`pseudo_equ` 00430b62|**EQU**|high| "EQU requires label"|
|0x19|(inline)|**EXITM**|high| "EXITM without associated MACRO directive" (macro.c owns the rest)|
|0x1a|`pseudo_message` 00430916(0x1a)|**FAIL**|high| shared with 0x27/0x38 (see 1.4); uses `FUN_00413085` (ERROR class)|
|0x1b|`sec_global` 004366be (group2)|**GLOBAL**|high| keyword confirmed in table|
|0x1c|`pseudo_himem_lomem` 0042de8d('\x1c')|**HIMEM**|high| shared handler with 0x22; keyword confirmed|
|0x1d|`pseudo_ident` 0042bcab|**IDENT**|high| "IDENT directive must contain version/revision number"; keyword confirmed|
|0x1e|`pseudo_if` 0042e838|**IF**|high| confirmed: nested-IF token recognized as opcode 0x1e inside `pseudo_if_skip`'s own scan|
|0x1f|`pseudo_include` 0042bf3a|**INCLUDE**|high| "Cannot open include file"; keyword confirmed|
|0x20|`sec_local` 004364a5 (group2)|**LOCAL**|high| keyword confirmed in table (not in BRIEF's directive list but present in the recovered keyword table and dispatched here)|
|0x21|(inline, `list_suppress_depth++`)|**LIST**|med| paired with 0x28 (decrement); guessed LIST/NOLIST but polarity unconfirmed|
|0x22|`pseudo_himem_lomem` 0042de8d('\x22')|**LOMEM**|high| keyword confirmed|
|0x23|`pseudo_lstcol` 0042e539|**LSTCOL**|high| sets 5 column-width globals (label/opcode/operand/X/Y), defaults 10/8/10/12/12 when no operand; keyword listed by brief|
|0x24|`pseudo_maclib_add_path` 0042c457|**MACLIB**|high| appends a path to the macro-library search list; keyword confirmed|
|0x25|`FUN_0041ee40`|-|-|outside our modules (likely macro.c: MACRO)|
|0x26|`pseudo_mode` 0042c5f3|**MODE**|high| "absolute"/"relative", "Mode not specified"|
|0x27|`pseudo_message` 00430916(0x27)|**MSG**|high| shared handler, plain message class (`FUN_004136cd`)|
|0x28|(inline, `list_suppress_depth--`)|**NOLIST**|med| paired with 0x21|
|0x29|`pseudo_opt` 0042ec12|**OPT**|high| the OPT option table, see §1.3|
|0x2a|`pseudo_org` 0042cef3|**ORG**|high| P:/X:/Y:/L: load & run address handling, see §1.5|
|0x2b|(inline, calls `pseudo_page` helper `0042e1f7`)|**PAGE**|high| "Invalid page width/length specified"|
|0x2c|`FUN_0042052c`|-|-|outside our modules|
|0x2d|`pseudo_prctl` 0043063f|**PRCTL**|high| "PRCTL directive ignored - no explicit listing file"|
|0x2e|`pseudo_radix` 0043104e|**RADIX**|high| "Invalid radix expression", accepts 2/10/16|
|0x2f|`pseudo_rdirect` 0042fd1e|**RDIRECT**|high| "RDIRECT directive not allowed in section"; marks named directives/mnemonics with the 0x80 "redirected" bit so they parse as ordinary symbols|
|0x30|`pseudo_revision` 0042f9fb|?|low| "Illegal/Missing revision"; sets a core-revision table pointer + opcode-table-size limit; exact keyword not recovered|
|0x31|`sec_section` 004351c0 (group2)|**SECTION**|high| keyword confirmed|
|0x32|`pseudo_set` 00430e0f('\x32')|**SET**|high| shared with 0x40 ("=" alias); "SET requires label"|
|0x33|`pseudo_set_title` 0043158e(&title_text)|**TITLE** or **STITLE**|med| see §1.6, exact pairing with 0x36 unresolved|
|0x34|`pseudo_noop_dir34` 0042feb9|?|low| always returns 1, does nothing - recognized-but-inert directive|
|0x35|(inline, calls `pseudo_tabs` `0042e7e6`)|**TABS**|high| "Invalid tab stops specified"; default tab stop 8 when no operand|
|0x36|`pseudo_set_title` 0043158e(&stitle_text)|**STITLE** or **TITLE**|med| see §1.6|
|0x37|`pseudo_undef` 0042bc44|**UNDEF**|high| "UNDEF symbol must be a global symbol name"; keyword confirmed|
|0x38|`pseudo_message` 00430916(0x38)|**WARN**|high| shared handler, warning class (`FUN_004133a9`)|
|0x39|`sec_xdef` 00436b2e (group2)|**XDEF**|high||
|0x3a|`sec_xref` 004368c3 (group2)|**XREF**|high||
|0x3b|`pseudo_dc_chars` 0040c252|**DC** (secondary form)|med| same DC semantics, different internal parse path; exact trigger for this alternate opcode unclear|
|0x3c|`pseudo_force` 004310e5('\x3c')|**FORCE**|high| sets `force_type` (short/long/normal) - a generic branch-forcing default, distinct from SCSJMP; matches recovered keyword `force`|
|0x3d|`pseudo_force` 004310e5('\x3d')|**SCSJMP**|high| sets `scsjmp_force_type`, read directly by scs.c's jump-emission code (`scs_emit_jump`/`scs_for`/`scs_endf`) - confirms the directive name via the consuming module|
|0x3e|`pseudo_scsreg` 004312d0|**SCSREG**|high| reads up to 4 comma-separated register names into `scs_reg_x/scs_reg_accum/scs_reg_y/scs_reg_offset` (defaults reset by `pseudo_scsreg_default` 004314ab); these are exactly the registers scs.c's FOR/LOOP code generator substitutes into the emitted `move`/`cmp` text|
|0x3f|`pseudo_processor` 0042fb7e|?|low| "Illegal/Missing processor type"; looks up a processor-type table, sets opcode-table-size/flags; exact keyword not recovered (candidate: PROCESSOR/CPU/TARGET)|
|0x41|`pseudo_dc_wide` 0040c6ac(2)|**DC** (L:/wide, width 2)|med||
|0x42|`pseudo_dc_wide` 0040c6ac(4)|**DC** (wide, width 4)|med||
|0x43|`pseudo_bsc_typed` 0040d1f7(1)|**BSC** (typed, width 1)|med||
|0x44|`pseudo_bsc_typed` 0040d1f7(2)|**BSC** (typed, width 2)|med||
|0x45|`pseudo_bsc_typed` 0040d1f7(4)|**BSC** (typed, width 4)|med||
|0x46|`pseudo_block_reserve` 0040d7c7(0x400,0x46)|**BSM** (secondary form)|low||
|0x47|`pseudo_ds_typed` 0040df7a(0x400,0x47)|**DS** (secondary form)|low||
|0x48|`pseudo_baddr` 0040e25f(0x48)|**BADDR** (secondary form)|low||
|default|"Directive select error"|-|-|internal-consistency check, should be unreachable|

Open questions: opcode 0x00, 0x07, 0x30, 0x34, 0x3f and the exact 0x33/0x36
TITLE-vs-STITLE and 0x21/0x28 LIST-vs-NOLIST polarity. **DSR** (Define
Storage Reverse-carry, named in the BRIEF) was not confidently matched to
any opcode; my best guess is that it doesn't exist as a separately-coded
opcode in this switch and is either folded into DSM's argument handling
(not observed) or into one of the still-unidentified opcodes (0x00/0x34).

### 1.3 OPT option table (`pseudo_opt`, `0042ec12`)

`pseudo_opt` splits the operand on commas, folds each option name to
lower-case (max 8 significant chars, else "Illegal option"), looks it up
with `FUN_004390e6(name)` (a table-search helper in another module - not
decompiled, presumably in `asmglb`'s "option tables" per BRIEF section
layout), and switches on the looked-up record's `+4` field, a **0..0x81
(130 possible) option code**. Each option almost always just stores a
0/1 into a target global (even code = ON, odd code = OFF, for the 65
observed pairs) - i.e. the record layout is (from usage): `{ ..., long
optcode; ... }`, at least 4 bytes at offset +4 holding the switch value;
size/count of the rest of the record could not be recovered (data-only
table, not decompiled, and the plain-ASCII name fragments recovered from
`strings.txt` - `const contck noconst nodex nointr nomex nonde...` - only
cover a handful of the 65 pairs because most entries are stored with
non-printable length/opcode bytes immediately before the name and are
skipped by the automatic string scan).

13 of the pairs are identified with **high** confidence because they print
a distinctive "*option* must be used before any label" or similar error
(these are "sticky"/pass-1-latched options - the code snapshots a
default-derived value into a `DAT_00463cXX` "was-it-set-yet" flag the first
time OPT runs in pass 1, then refuses to change the live flag once a label
has been assigned in the source):

| opcode | global | option |
|--------|--------|--------|
|5|`opt_cre`/`opt_cre_sticky`|CRE|
|0x19|`opt_mu`|MU|
|0x1a|(local sticky flag only, `DAT_00463c54`)|LOC|
|0x20|`opt_xr`|XR|
|0x28|`opt_ic`|IC|
|0x29|`opt_lb`|LB|
|0x2a|`opt_lbx`|LBX|
|0x2f|`opt_gs`|GS|
|0x30|(clears `opt_gs`)|NOGS|
|0x4d|`opt_gl`|GL|
|0x4e|`opt_xll`|XLL|
|0x53|`opt_svo`|SVO|
|0x54|`opt_sco`|SCO|
|0x55|`opt_ldb`|LDB|

Two more are identified by cross-referencing the flag with its only other
reader:
* opcode 2/0xb -> `opt_mex`=1/0 (`0044f778`) - read by `pseudo_if_skip`
  (`0042e939`) to decide whether to print a space before certain generated
  listing text; matches the classic **MEX/NOMEX** (macro-expansion listing)
  pair.
* opcode 1(+`0045f930`=0)/0xa -> `opt_gen` (`0045ea38`) - gates whether
  expanded/generated source lines are shown in the listing at all; best
  guess **GEN/NOGEN**, but note opcode 4 *also* sets the same `opt_gen`
  global with no matching "off", so there may be a second synonym/alias
  option collapsing onto GEN (unresolved).

All remaining ~50 pairs are listed in `pseudo_opt`'s source with their
target globals but their keyword spelling could not be recovered from the
available strings; they are simple boolean flags (see the raw switch in
`re/out/ASM56000/mod/pseudo.c:2211-2704` for the full case-to-global list,
reproduced here only for the named ones above). Whoever gets a fuller
export of the asmglb option-name table (e.g. by dumping `.rdata` around
`0x450840-0x450a40` as raw bytes rather than through the ASCII-string
scan) should be able to fill in the rest mechanically by walking the same
switch.

### 1.4 FAIL / WARN / MSG (`pseudo_message`, `00430916`)

One shared implementation for all three: builds a formatted message from a
comma-separated operand list (numbers formatted `%.15e` for floats, decimal
for plain integers via `FUN_0040a7ea`, or `$hhhhhh` hex pairs for anything
else) into a 512-byte local buffer, then dispatches to the message class by
the *case number itself* (passed straight through as `diridx`):
`diridx==0x1a` -> `FUN_00413085` (ERROR, aborts current statement) = FAIL;
`diridx==0x38` -> `FUN_004133a9` (WARNING, continues) = WARN; anything else
(only reachable as 0x27) -> `FUN_004136cd` (plain informational) = MSG.

### 1.5 ORG (`pseudo_org`, `0042cef3`)

Parses one or two memory-space-qualified addresses (`space:addr[,space:addr]`
via `org_get_bounds`/`FUN_00439e8d` for the space keyword). One address form
sets both the load and run location counter for the given space to the same
value; the two-address form sets a separate load-time and run-time (P:) org,
checking that `L:` is only used consistently between the two and printing
"L space specified for runtime, but not load"/vice-versa otherwise, and that
a *relocatable* run origin matches the load origin's own displacement
("Relocatable runtime/load origin must be in the base section"). It creates
or reuses a location-counter block per (section, space) via
`org_select_counter` -> `org_new_counter` -> `org_alloc_counter_block` +
`org_init_counter`, and always finishes with `FUN_0043b926(1)` (marks "code
has been generated this line" off) then `FUN_0043b007(1)` (advances past the
consumed operand). `org_get_bounds` (`0042ce91`) returns a pointer into one
of two fixed bound tables (`&DAT_0045f870` for P: memory, `&DAT_0044f838`
otherwise), one 8-byte entry per (processor variant, load/run) pair -
"Location bounds selection failure" if the processor-variant index
(`FUN_0043a768`) is invalid.

## 2. Conditional assembly: IF / ELSE / ENDIF

There is **no explicit stack structure** for classic (non-SCS) `IF`/`ELSE`/
`ENDIF` - the C call stack does the work, plus one depth counter:

* `if_nest_depth` (`0045eba4`, global `long`) - incremented on entry to
  `pseudo_if` (any IF, whether taken or not), decremented on the matching
  ENDIF. Only used so nested IFs can be told apart from the outermost one
  for listing/spacing purposes; it is *not* used to find the matching
  ENDIF - that is done by direct nesting-depth counting local to each call.
* `pseudo_if` (`0042e838`, opcode 0x1e) evaluates the IF expression
  (must be a resolved integer, no forward references: "Expression contains
  forward references"/"Expression result must be integer"). If false, calls
  `pseudo_if_skip(1)`; if true, calls `pseudo_if_body(ifobj, 1)`.
* `pseudo_if_skip` (`0042e939`) reads and **discards** source lines (still
  running them through the tokenizer/`pseudo_dispatch` far enough to
  recognize directives) until it sees, at its own nesting level: opcode
  `0x1e` (nested IF: depth++), opcode `0x15` (ENDIF: depth--, and if it
  reaches 0 the function returns success - the skip is over); or, only when
  at depth 1, opcode `0x12` (ELSE) - it then switches into "execute" mode by
  calling `pseudo_if_body(ifobj, 0)`. Opcode 8 (COMMENT) is special-cased to
  re-enter `pseudo_comment(1)` so a `COMMENT ... delimiter` block inside a
  skipped IF is itself skipped correctly.
* `pseudo_if_body` (`0042eb07`) is the mirror: it runs lines *normally*
  (through the real per-line assemble path, not shown here - another
  module) until the assemble path itself reports it consumed an ENDIF
  (0x15, success/done) or an ELSE (0x12, switches back to
  `pseudo_if_skip(0)` to discard the rest) at the top level. Because nested
  IFs are handled recursively by the normal per-line dispatch calling
  `pseudo_if` again, no explicit depth tracking is needed here either.

So "the conditional-assembly stack" is really: **recursion + a single
depth counter** (`if_nest_depth`), not a heap-allocated stack of saved
state. `ELSE`/`ENDIF`/`ENDM` appearing as their own top-level opcodes
(0x12/0x15/0x16) exist purely to produce the "without associated
IF/MACRO" error when the tokenizer reaches them outside of this recursive
scan.

## 3. SCS (structured control statements): scs.c

### 3.1 Two run-time stacks + a generated-line queue

`scs.c` implements `.IF/.ELSE/.ENDI`, `.WHILE/.ENDW`, `.REPEAT/.UNTIL`,
`.FOR/.ENDF`, `.LOOP/.ENDL`, `.BREAK`, `.CONTINUE`. Each SCS statement is
expanded into ordinary DSP56000 instruction *text* (conditional jumps,
`cmp`, `move`, hardware `do` loops) which is queued and then fed back
through the normal line assembler - i.e. SCS is implemented as a text
macro-expander, not as direct object-code emission.

**a) `scs_open_stack`** (`0045fc90`) - singly-linked list, the real "SCS
control stack". Each node is a 12-byte record allocated by `scs_new_label`
(`0043ad5`, called with the construct's *type* byte):

```c
struct scs_label {           /* 12 bytes, alloc'd by scs_new_label */
    long id;                  /* +0x00: sequence number from
                                  scs_label_id_counter (0045fc8c),
                                  formatted "Z_L%05d" - matches the
                                  Z_L00000, Z_L00001... labels seen in
                                  t1.lst */
    unsigned char type;       /* +0x04: construct/marker tag, see table
                                  below */
    unsigned char pad[3];
    struct scs_label *next;   /* +0x08 */
};
```

`scs_push_label`/`scs_pop_label` (`00433b1a`/`00433b34`) push/pop this
list; `scs_new_label` also bumps `scs_label_id_counter` (`0045fc8c`)
unconditionally (even nodes never pushed still consume a label number -
visible in `t1.lst` where `scs_break_cond`'s freed/unused labels still
skip numbers). `scs_cleanup` (`00433b90`) is the pass-end/error unwind: it
pops and frees every remaining `scs_for_stack` and `scs_open_stack` entry,
printing "Unexpected end of file - missing `.ENDx`" keyed off the leftover
node's `type` (3/4/5/6/0xb -> ENDF/ENDI/ENDL/ENDW text respectively), and
resets `scs_label_id_counter` to 0 for the next file/pass.

Observed `type` values (from what each `.ENDx`/`.BREAK`/`.CONTINUE`
requires on top of `scs_open_stack`):

| type | pushed by | required/consumed by |
|------|-----------|----------------------|
|3|`scs_for` (FOR, innermost/body marker)|`scs_endf` (last of 4 pops), `scs_break`/`scs_continue` (valid enclosing-loop marker)|
|4|`.IF`-open (not in this file; scs.c only has the ENDI/closing half - see note)|`scs_endi` (single pop)|
|5|`scs_loop` (LOOP, body marker)|`scs_endl` (final pop), `scs_break`|
|6|`scs_repeat`?? or `scs_continue_cond`|`scs_endw` (second pop), `scs_break`|
|7|`scs_for` (marker)|`scs_endf` (3rd pop, before type-3)|
|0xb|`scs_repeat`? (pushes type 0xa,0xb,0xe - see §3.2)|`scs_endw`'s sibling check / `scs_break`|
|0xc|`scs_for`?/paired-with-6 opener|`scs_endw` (first pop)|
|0xe|`scs_repeat` (`00432623`, outermost marker, pushed last/top)|`scs_until` (first pop) - confirms `scs_repeat`|
|0xf|`scs_for` (outer marker)|`scs_endf` (1st pop)|
|0x10|`scs_for` (outer marker 2)|`scs_endf` (2nd pop)|
|0x11|`scs_loop` (indefinite `.LOOP` w/o count, alt marker)|`scs_endl`|
|0x12|`scs_loop` (`.LOOP #count` -> hardware `DO`, top marker)|`scs_endl` (checked first)|

(The `.IF/.ELSE/.ENDI` SCS opener itself was not found among scs.c's 32
functions - `scs_endi` only *consumes* a type-4 node - so the opener likely
lives in another module, e.g. `func.c`, alongside the mnemonic-table
dispatch that calls `scs_run_statement`'s vtable.)

**b) `scs_for_stack`** (`0045fc94`) - a *separate* singly-linked list (next
pointer at offset `+0x94`, so nodes are >=0x98 bytes), holding the full
`.FOR` loop descriptor allocated in `scs_for` (`0043227c`,
`FUN_00439857(0x98)`) and parsed by `scs_parse_for_clause`
(`004330dd`, matches `x:$10 = #1 to #10 by #2 do` / `downto` syntax from
the BRIEF's DSP grammar). Pushed/popped by `scs_for_push`/`scs_for_pop`
(`00433a8a`/`00433aa7`); read back by `scs_endf` via `scs_for_pop` to emit
the loop-increment/compare code, keyed on the struct's `+0x90` (`[0x24]`)
"downto" flag (1 = count down, uses `<` vs `<=`/`>` compare accordingly).

**c) generated-code queue** (`scs_gen_line_head`/`scs_gen_line_tail`,
`0045fc84`/`0045fc88`) - singly linked list of generated assembly-text
lines, appended by `scs_emit_line` (`00432cee`, wraps `FUN_0041f6e2` from
another module to duplicate the string into a node) and spliced back into
the normal input stream by `scs_run_statement` (`004318d1`) after a
construct's handler returns.

### 3.2 Code generation helpers

* `scs_emit_jump` (`00432c82`) / `scs_emit_cond_jump` (`00432bc8`) - build
  `jmp <cc> LABEL` / `j<cc> <cc>,LABEL` text via `sprintf`+`scs_emit_line`.
  The condition-code character is computed from `scsjmp_force_type`
  (`0045ebb0`, set by the pseudo.c **SCSJMP** directive, opcode 0x3d): value
  `0x2000000` -> `'<'` (short-form relative branch), else a computed
  char (`'>'`-ish) for the "long" default - i.e. SCSJMP's `short`/`long`
  choice directly controls whether SCS-generated branches use the 8-bit or
  extended displacement jump mnemonic form.
* `scs_parse_condition` (`00432d3b`) parses one `<cc>`-bracketed DSP
  condition (optionally a *compound* `<cc1> AND/OR <cc2>` via `FUN_00439267`
  for the mnemonic lookup); `scs_parse_condition_chain` (`004328bc`) loops
  it to parse a `.UNTIL`-style chain of conditions joined by `AND`/`OR`
  keywords, returning the combinator code consumed by `scs_until`.
* `scs_emit_move_compare` (`00432926`) - for `.FOR`/`.LOOP`-with-count style
  constructs, emits the `move`/`tfr`/`cmp` sequence that loads the loop
  register(s) named by **SCSREG** (`scs_reg_accum`/`scs_reg_x`/`scs_reg_y`/
  `scs_reg_offset`, globals `0044f938/934/93c/940`) with the parsed
  start/end expressions, special-casing the case where both are the "N:"
  offset register pair (does a raw struct-field swap instead of emitting
  code, since no move is needed).

### 3.3 Cross-module interfaces used by scs.c/pseudo.c's directives

* `sec_local`/`sec_global`/`sec_xdef`/`sec_xref`/`sec_endsec`/`sec_section`
  (section.c, named in `g2_symtab.names.txt`) implement **LOCAL / GLOBAL /
  XDEF / XREF / ENDSEC / SECTION** directly; pseudo.c's dispatch table just
  forwards to them with `FUN_0043b007` afterwards to advance the operand
  cursor.
* `FUN_00413085`/`FUN_0041351d`/`FUN_004131f9`/`FUN_004133a9`/`FUN_004136cd`
  (error.c, not decompiled here) - the ERROR/redefinition-WARNING/
  formatted-ERROR/WARNING/plain-MESSAGE emitters used throughout.
  `pseudo_message` (FAIL/WARN/MSG) is a thin wrapper choosing between three
  of these by directive identity.
* `FUN_00413e70`/`FUN_00414862`/`FUN_00413f38`/`FUN_0041409f` (eval.c) -
  expression evaluators used by DC/DS/BSC-family functions in data.c, and
  `FUN_0040a7ea` for converting an expression's numeric value to a plain
  `int` (used for range-checking constants against the current data-width
  ("EMI 8/12/16/20-bit memory value truncated")).
* `FUN_00439857`/`FUN_004167ef`/`FUN_004398b5` (util.c) - the assembler's
  own allocator/free (all SCS/pseudo/data heap nodes go through these, not
  `malloc`/`free` directly - matches CLAUDE.md's "assume int may be 16
  bits" guidance: reimplement with a similar small-block allocator rather
  than calling C's `malloc` per node when porting).
* `FUN_0043b007`/`FUN_0043b405`/`FUN_0043b659`/`FUN_0043b836`/`FUN_0043b08d`
  (input.c) - operand-cursor advance, symbol-name/quoted-string parsing,
  and case-folding helpers used pervasively by every directive handler.

## 4. Structs found

### 4.1 `scs_label` (12 bytes) - see §3.1a.

### 4.2 SCS FOR-loop descriptor (>= 0x98 = 152 bytes, `0045fc94` list)

Allocated in `scs_for` (`0043227c`, `FUN_00439857(0x98)`), filled by
`scs_parse_for_clause` (`004330dd`). Fields identified by offset (all
`int`/pointer-sized, i.e. `param_1[n]` = offset `n*4`):

| offset | field | meaning |
|--------|-------|---------|
|0x00|`start_text`|malloc'd text of the loop-variable's memory-write target (`x:$10 = ...` LHS), built via `FUN_00439c56`+`FUN_004061ae` (register/operand parse) then `sprintf`'d|
|0x04-0x24|`start_expr`|9-word (0x24 byte) parsed-expression block for the start value, same layout as eval.c's expression-value struct (opaque here; consumed by `scs_emit_move_compare` as `*puVar4`, `[9]`, `[0x12]`, `[0x1b]`)|
|0x24|`start_assign_op`|1 if syntax was `=` seen after the loop-var target (always true here; `param_1[9]` reused later for a different purpose after `scs_endf` frees it - see below)|
|0x2c|`limit_text`|malloc'd text of the "to"/"downto" limit expression's LHS|
|0x48|`limit_keyword_is_downto`|`param_1[0x24]` (offset 0x90) - 1 if `DOWNTO` matched, 0 for `TO` - drives `<`/`<=` vs `>`/`>=` compare selection in `scs_endf`|
|0x4c-0x70|`limit_expr` / `step_text` / `step_expr`|analogous "by #n" step clause, defaulting to step text `"1"` (`DAT_0045880c`) when omitted|
|0x70|`step_forcing`|forced to `9` (short?) when the step is defaulted|
|0x80|`step_present_flag`|1 when the default (no `by` clause) path was taken|

(Exact byte-for-byte layout beyond what's listed needs a disassembly pass
over `scs_parse_for_clause`/`scs_endf`/`scs_emit_move_compare` together;
what's captured here is enough to know the struct's *size* and its 4
logical sub-fields: start/limit/step/downto-flag, each carrying both a
formatted-text copy and a parsed-expression copy.)

### 4.3 SCS condition descriptor (built by `scs_parse_condition`, 0x4c+ bytes on the caller's stack in most callers, or heap-allocated at size 0x98 via `FUN_00439857(0x98)` in `scs_for` reusing the same shape) - holds: operand-1 text/expr, operand-2 text/expr (optional, for a compound `<cc1> AND/OR <cc2>`), the condition-code index from `FUN_00439267`, and (at `+0x4c`) a flag distinguishing "simple" vs "compound" (read by `scs_emit_cond_jump`).

### 4.4 OPT-option lookup record - opaque (found only via `FUN_004390e6`'s
return value), but its layout is pinned by usage in `pseudo_opt`: `+4` is a
4-byte code in range 0..0x81 used as the dispatch switch value. Table
itself lives in a different (undecompiled) module.

## 5. Globals (this group's modules)

See `g5_pseudo.names.txt` for the full list with addresses/types. Notable
ones not already covered above:

* `0045f8fc` `assembler_pass` (int) - current pass number (1 or 2), read by
  almost every "sticky option" check in `pseudo_opt` and by `pseudo_org`.
* `00460c88` `define_symtab` (hash table head array, 3888 bytes = 0x3f0 * 4
  slots i.e. **324 buckets** of a 4-byte head pointer - `pseudo_define_store`
  hashes via `FUN_00439b65`, `pseudo_define_free_all`
  (`0043055e`) walks all 0x3f0 buckets at pass boundaries) - the DEFINE/UNDEF
  symbol table, a **separate** table from the main symbol table (owned by
  symtab.c/group2).
* `0045eba0` `define_count` - live DEFINE symbol count, gates whether
  `pseudo_define_free_all` has any work to do.

## 6. Quirks / bugs worth reproducing

* `scs_new_label` always increments `scs_label_id_counter` even for nodes
  that are later discarded/never pushed (e.g. `scs_break_cond`'s
  `FUN_004398b5` frees without ever calling `scs_push_label`) - so the
  generated `Z_L#####` label numbers can have gaps. Must reproduce exactly
  (byte-identical listings) - do **not** "optimize" by only allocating an id
  when a label is actually emitted.
* `pseudo_opt`'s per-token buffer is fixed at 8 significant characters
  (`local_1c[12]`, but the copy loop errors out past 8 chars with "Illegal
  option") - option names longer than 8 characters are rejected even if a
  match would otherwise exist.
* `pseudo_lstcol`/`pseudo_tabs` reset to hard-coded defaults (10/8/10/12/12
  and tab-stop 8 respectively) when called with an *empty* operand, but
  otherwise go through the full expression-list parser - an empty-operand
  fast path that must be reproduced exactly, not merged into the general
  parser with a "use default value" fallback (the general parser takes a
  different code path and could theoretically behave differently on some
  locale edge case via `_isctype`/`tolower`).
* `pseudo_ident`'s generated `$Id`-style banner (`IDENT` directive) embeds
  either the literal `"6.3.0"` (`opt_...`/`DAT_0044f9b8`) or a build-date
  string depending on `DAT_0045eb50` - worth checking against the real
  banner text emitted by `re/bin/ASM56000.EXE -a -b -l` when porting.
* The OPT option table has at least two pairs (`opt_gen` set from *both*
  opcode 1 and opcode 4, `opt_gs`/`opt_svo`/`opt_sco`/`opt_ldb` "sticky"
  pattern) that snapshot a *pass-1-only* default the first time the option
  group is touched (`DAT_00463cXX` shadow flags) and then refuse to change
  the live flag afterward, printing "*option* must be used before any
  label" - this two-phase latch must be reproduced (not simplified to "last
  write wins") since the original enforces the option can only be set
  before the first label of the module.

## 7. Summary

* Functions named: 50 (pseudo.c) + 16 (data.c) + 32 (scs.c) = **98**
  (all given a name; confidence high/med/low as marked - roughly 60% high,
  25% med, 15% low/open-question).
* Globals named: **43** (see names file), covering both special-
  responsibility structures (SCS stack/queue, conditional-assembly depth
  counter, OPT-table-adjacent flags) plus the DC/DS/BSC/BUFFER shared state
  and the DEFINE symbol table.
* Main structs found: `scs_label` (12 B, singly-linked, SCS control stack),
  SCS FOR-loop descriptor (0x98 B, separate stack), SCS condition
  descriptor, generated-line queue node (opaque, owned by another module's
  `FUN_0041f6e2`), and the 73-entry directive opcode table + up-to-130-entry
  OPT option table (both data-only, not decompiled, but their *dispatch*
  fully mapped here).
* Open questions for follow-up (see inline notes above): opcodes
  0x00/0x07/0x30/0x34/0x3f's exact directive keywords; **DSR**'s opcode;
  TITLE-vs-STITLE polarity (0x33/0x36); LIST-vs-NOLIST polarity (0x21/0x28);
  ~50 of the 65 OPT option-name pairs (mechanism and target global are
  documented, keyword spelling is not); the `.IF`/`.ENDI` SCS *opener*
  function, which is not among scs.c's 32 functions and likely lives in
  another module alongside the SCS keyword-to-handler vtable dispatch
  (`scs_run_statement`'s `this`/vtable-slot argument implies such a table
  exists, e.g. in func.c).
