# g3_expr - eval.c / func.c / arith.c

Group `g3_expr`. Covers the expression parser/evaluator (`eval.c`, 27 functions,
`re/out/ASM56000/mod/eval.c`), the `@`-function library (`func.c`, 29 functions,
`.../mod/func.c`), and the arithmetic/conversion engine (`arith.c`, 50 functions,
`.../mod/arith.c`). Module ownership per `re/out/ASM56000/modules.txt` ($Id-based).

Reused prior work: `re/notes/ASM56000/scratch_g3_expr/` held a `pe.py` PE-section
reader and five hand-assembled test sources (`t1..t5.asm`) already run through
`re/bin_ft/ASM56000.EXE -a -b -l` to capture ground-truth `.lst` output. All five
were reused as-is (see "Numeric semantics" below, which is built directly from
their `.lst` output) and `pe.py` was reused to dump the `@`-function table and the
binary-operator dispatch table directly out of `re/bin/ASM56000.EXE`.

## Module purposes

- **eval.c**: recursive-descent/operator-precedence expression parser. Owns the
  `EXPR_VAL` allocator/stack, the tokenizer for numeric/string/char constants and
  identifiers, the binary-operator scanner+precedence table, and the "canonical
  form" text regenerator used to store an expression's source text verbatim when
  it contains an unresolved forward reference (so pass 2 can re-parse it). Also
  contains a handful of small helpers (`which_field`, `wrap_message`,
  `fatal_usage*`) that look like they belong to error-reporting but are physically
  in this source file per its `$Id` string.
- **func.c**: implements every `@NAME(...)` expression function. Holds the
  54-entry function-name table dispatcher (`eval_function`) and one implementation
  function per family (many ids share one implementation, selected by a small
  switch keyed on the table's id byte).
- **arith.c**: implements the binary/unary operators applied to two `EXPR_VAL`s
  (the table at `0x44fff8` indexed by opcode, called from `eval.c`'s
  `parse_binop_rhs`), the float<->fixed conversion routines (x87 80-bit
  intermediates, `_ftol` truncation, the domain-checked rounding-to-fraction
  routine), a small base-256 big-integer library used for 56-bit `*`, `/`, `%`,
  and, oddly, the DSP56000 **register-name lexer** (`match_register_name`) - the
  function that recognizes `A B X Y A0 A1 A2 B0 B1 B2 X0 X1 Y0 Y1 A10 B10 AB BA
  CCR LA LC M0-M7 MR N0-N7 OMR R0-R7 SP SR SSH SSL` and returns a small integer
  register id (used by `amode.c`, not this group, for addressing-mode parsing).

## The `EXPR_VAL` struct

Every parsed (sub-)expression is a heap-allocated, 0x60 (96)-byte, 4-byte-aligned
struct, always accessed through this same layout from eval.c/func.c/arith.c
(allocated by `new_expr_value` @00416653, freed by `free_expr` @004167ef). Field
names below are `W<n>` = offset `4*n`. Evidence: `new_expr_value`'s
initialization order, `classify_value` @004165e3, `parse_term` @0041518e's number
literal accumulation, `op_add`/`op_and`/etc.'s field masks, and `fn_convert`'s
type-field toggling.

| off  | field        | meaning |
|------|--------------|---------|
| 0x00 | `W0`  | integer: sign-extend byte of the 56-bit value (0x00 or 0xFF), i.e. bits 55-48. Float: low 32 bits of the `double`. String-pack mode (`pack_string_operand`): pointer to the malloc'd packed-word buffer. |
| 0x04 | `W1`  | integer: middle 24 bits (bits 47-24). Float: high 32 bits of the `double`. |
| 0x08 | `W2`  | integer: low 24 bits (bits 23-0) - the value most simple integer consumers read (`expr_as_int32` folds `W1`'s low byte above this). Also reused as the plain boolean/integer result slot by several `@`-functions (`@DEF`, `@LEN`, `@POS`, ...). |
| 0x0c | `W3`  | not observed written directly by this group; likely padding to keep the double 8-byte aligned. |
| 0x10 | `W4`  | **type**: `0x100` = integer/fixed, `0x200` = floating (`double` lives at `W0..W1`). |
| 0x14 | `W5`  | **format/width class**, set by `classify_value`: `3`=fits in 24 bits, `6`=needs the 48-bit (X:Y / long) pair, `7`=full 56-bit, `8`=floating. Also reused ad hoc: `pack_string_operand` sets it to 3 always (before it stores a pointer at `W0`, see below), `fn_lng` forces it to 6. |
| 0x18 | `W6`  | **flags** bitmask: `0x1000`=relative/relocatable (section-relative) term, `0x8000000`=result still contains an unresolved forward/external reference (pending pass-2 re-parse), `0x800`=value already flagged "too large for a machine word" (consumed by `fn_fld`'s range checks), `0x400`, `0x40000` = symbol-table attribute bits copied verbatim from the symbol (`0x7000` mask copied wholesale in `parse_term`), `0x100000`=set by `float_to_fixed_frac` to mark "this fixed value came from a rounded float" (arith.c only; not seen read anywhere in this group's code - likely read by `encode.c`/`pseudo.c`). |
| 0x1c | `W7`  | memory **space** attribute of a relative term (P/X/Y/L/... code, `4`=none/absolute - the default set by `new_expr_value`). |
| 0x20 | `W8`  | memory **map** attribute. |
| 0x24 | `W9`  | location-**counter** selector (which of several counters the relative term is tied to). |
| 0x28 | `W10` | secondary counter/emi selector, paired with `W9`. |
| 0x2c | `W11` | pointer to the originating symbol-table entry (set in `parse_term`'s identifier branch: `*(sym-entry**)(val+0x2c) = symtab_entry`). |
| 0x30 | `W12` | nonzero => `free_expr` also frees the pointer at `W11` (seen cleared/tested only; not seen set by this group - probably set by whichever module allocates a private symbol copy). |
| 0x34 | `W13` | `pack_string_operand`: character count of the packed string. |
| 0x38 | `W14` | `pack_string_operand`: word count of the packed-string buffer; `free_expr` frees `W0` (the buffer pointer) when this is nonzero. |
| 0x3c | `W15` | relocation/section id for a relative term; **negative = external symbol** (tested pervasively as `val[0xf] < 0` => "External reference not allowed in expression"). |
| 0x40 | `W16` | counter-object pointer paired with `W15` (`ld_counter_obj`/`rt_counter_obj`-derived `+8` field). |
| 0x44 | `W17` | `ilist` capacity/position snapshot for the relative term (rt side). |
| 0x48 | `W18` | ditto, ld side (`W17`/`W18` come from `rt_ilist_cap`/`ld_ilist_cap`-like globals gated on whether the run/load counters currently differ). |
| 0x4c | `W19` | copied from the resolved symbol's field `+0xe` (purpose not pinned down by this group - looked like another counter/pc snapshot). |
| 0x50 | `W20` | copied from the resolved symbol's field `+0xd`. |
| 0x54 | `W21` | copied from `ld_counter_obj + 0x1c` for the `*` (current-PC) token, and from the symbol's field `+0xd`(?) otherwise; `-1` by default. |
| 0x58 | `W22` | zero-initialized, not observed read/written elsewhere in this group. |

Constructor defaults (`new_expr_value`): `W4=0x100` (integer), `W5=3`,
`W6=0`, `W7=0x1c-word=4` (space "none"), `W8=4`, `W9=0`, `W10=0`,
`W21=0xFFFFFFFF`, everything else 0.

The 56-bit integer value is genuinely **8+24+24 bits**, i.e. it matches the DSP
56000's 56-bit accumulator width, not a 64-bit type: bitwise `AND/OR/XOR`
(`op_and`/`op_or`/`op_xor`) operate on exactly `W0,W1,W2`; shifts
(`op_shl`/`op_shr`) propagate carry bit-by-bit between the same three words, with
`op_shr` explicitly re-deriving the sign extension of `W0` after every step
(`if (W0 & 0x40) W0 |= 0x80;`) - i.e. it is an **arithmetic** shift that keeps
`W0` a valid sign-extension byte throughout, not just at the end.

## Expression stack

`new_expr_value`/`free_expr` push/pop pointers onto a growable array of
`EXPR_VAL*`: base `expr_stack_base` (0045fc98), top `expr_stack_top` (0045fc9c),
capacity in words `expr_stack_cap` (00453f7c, starts at some small count, doubles
on overflow via `xrealloc`). `free_expr_stack_all` (00416860) walks and frees
every entry still on the stack; it's the unwind path taken from `eval_expr`'s
`setjmp` handler (`_setjmp3(&DAT_00465b80,0)`) when a fatal error occurs while
parsing (typical error handling in this code is otherwise "return NULL and let
the caller propagate", but a few library calls presumably longjmp out through
`report_error`'s fatal variant caught here).

## Token / operator scheme and precedence

`get_operator` (0041 4e2e) peeks 1-2 characters and returns an **opcode** 0..0x12
(0 = "no operator here"):

| op | opcode | op | opcode | op | opcode |
|----|-------:|----|-------:|----|-------:|
| `+`  | 1 | `<<` | 9   | `==` | 0xd |
| `-`  | 2 | `>>` | 0xa | `!=` | 0xe |
| `*`  | 3 | `<`  | 0xb | `<=` | 0xf |
| `/`  | 4 | `>`  | 0xc | `>=` | 0x10 |
| `&`  | 5 | `&&` | 0x11 | | |
| `\|` | 6 | `\|\|` | 0x12 | | |
| `^`  | 7 | | | | |
| `%`  | 8 | | | | |

`op_precedence` (0041501f) maps opcode -> precedence class 1 (tightest) .. 7
(loosest): `{*, /, %}`=1, `{+, -}`=2, `{<<, >>}`=3, `{<, >, <=, >=}`=4,
`{==, !=}`=5, `{&, ^, \|}`=6, `{&&, \|\|}`=7. `parse_binop_rhs` (0041 4aa1) is a
classic precedence-climbing loop: it keeps consuming operators whose class is
`< min_prec`, recursing for the RHS at the next tighter class.

The dispatch table at **0x44fff8**, 0x13 (19) `__cdecl` function pointers indexed
directly by opcode (opcode 0 -> `arith_binop_stub`, a "Expression operator
failure" trap that should be unreachable), was dumped straight out of the binary
and matches the opcode table above exactly:

```
0 arith_binop_stub   4 op_div   8 op_mod    c op_gt   10 op_ge
1 op_add             5 op_and   9 op_shl    d op_eq   11 op_land
2 op_sub             6 op_or    a op_shr    e op_ne   12 op_lor
3 op_mul             7 op_xor   b op_lt     f op_le
```

Unary prefix operators are handled directly in `parse_term` (0041518e), not
through this table: `+` (no-op), `-` (`negate_value`), `~` (`complement_value`,
integer-only, else "Illegal operator for floating point element"), `!`
(`op_not`), and `^` (sets the transient global `force_long` (0045eb10) while
parsing the operand - forces the "print two words" 48-bit canonical-form path;
this is the `^`-prefix long/L-memory forcing operator documented for DSP56000
assemblers).

`op_check_operands` (0099d3) is the shared legality gate for `+ - * / & | ^` (not
called for shifts or comparisons): rejects mixing two *different* external/undef
symbols unless exactly one side is external, rejects mismatched non-`none`
memory spaces (`merge_mem_space`) with "Expression involves incompatible memory
spaces" / "Invalid address expression", and rejects two relative terms from
different sections ("Relative terms from different sections") or an otherwise
illegal relative combination ("Invalid relative expression").

## Numeric literal parsing (parse_term, 0041518e)

- `%` or (radix-mode 2) leading `0`/`1` run: binary constant, accumulated 3
  words at a time straight into `W2/W1/W0` (>0x30 binary digits => format 7,
  >0x18 => format 6, 0 digits => "Binary constant expected").
- `$` or `0x`/`0X` (case-insensitive): hex constant, same 3-word accumulation
  (>0xc hex digits => format 7, >6 => format 6, 0 digits => "Hex constant
  expected").
- `` ` `` prefix or (radix-mode 10 and leading digit/`.`): decimal integer or
  float. Digits are accumulated into a *4-word* base-10^6-ish carry chain
  (`local_2c/14/c/30`, base `0xfffff`+1 boundary, i.e. effectively unlimited
  precision until it hits `.`/`e`/`E`, at which point the whole run is instead
  re-parsed with the C library `strtod` and the result stored as an IEEE
  `double` (`type=0x200`, `format=8`). A run with no `.`/exponent and no digits
  at all (only `` ` ``) is "Decimal constant expected". Pure-integer decimal
  literals *are* range/format-classified into the 3-word integer form
  (>0xc "hex digit slots" equivalent thresholds mirrored from the hex path).
- `'x'`, `"x"`, `[x]`: character/string constant via `get_string` (owned by
  `util.c`), packed 3 bytes per instance into `W2/W1/W0` big-endian
  (`'abcdefg'` truncates with "String truncated in expression" past 6 chars -
  matches the DSP56000's 56-bit/7-byte character-pack limit).
- `*`: current-PC pseudo-symbol - snapshots the run/load counter's pc, space,
  map, counter and section fields into the value (`W7..W21`), flags it
  relocatable (`0x1000`) unless `opt_reloc_l`, and always runs it through
  `emit_deferred_symbol` for the canonical text.
- `@name(...)`: delegates to `eval_function` (func.c); the parenthesized call is
  reparsed into the canonical-form buffer verbatim only if the result was left
  external (`W15<0`).
- identifier: `get_symbol` (util.c) + `sym_lookup` (symtab.c, reftype 2). Pass 1
  and an unresolved lookup: queues a forward reference (`fref_add`) and marks the
  value `0x8000000` (unresolved) unless deferred-symbol regeneration is
  disabled, in which case it's a hard error. A resolved symbol copies its value,
  space/map/counter, symbol-attribute flag bits (`&0x7000`) and relocation/
  section-id fields straight across; whether the canonical text is regenerated
  as `{name}` or left as-is is gated by attribute bits `0x30`/`0x40000`/`0x400`
  combined with `gset_mode`(`opt_sco`?)/`opt_const`-style option flags.

## The `@`-function table (0x450048, 54 x 16-byte entries)

Dumped directly from `re/bin/ASM56000.EXE` (`re/notes/ASM56000/scratch_g3_expr/pe.py`,
count at `0x4503a8` = 54). Entry layout: `char *name` (offset 0, matched
case-insensitively by `strncmp(input, name, strlen(name))` in
`eval_func_name_cmp`), `unsigned char id` (offset 4), `void *fn1` (offset 8),
`void *fn2` (offset 0xc). `fn1`/`fn2`, when non-null, are direct CRT math
function pointers (via the 18 one-line wrappers at `0x401000-0x40116d`
documented in `re/crt/ASM56000.names.txt`) consumed by `fn_math1`/`fn_math2`.

| id | name | id | name | id | name | id | name |
|---:|------|---:|------|---:|------|---:|------|
|0x1|def|0x2|exp|0x3|int|0x4|lcv|
|0x5|msp|0x6|mac|0x7|scp|0x8|cvi|
|0x9|cvf|0xa|cvs|0xb|frc|0xc|acs|
|0xd|asn|0xe|atn|0xf|cos|0x10|log|
|0x11|l10|0x12|sin|0x13|sqt|0x14|tan|
|0x15|xpn|0x16|at2|0x17|pow|0x18|abs|
|0x19|sgn|0x1a|lst|0x1b|unf|0x1c|snh|
|0x1d|coh|0x1e|tnh|0x1f|flr|0x20|cel|
|0x21|min|0x22|max|0x23|rel|0x24|rnd|
|0x25|lfr|0x26|lun|0x27|lng|0x28|ccc|
|0x29|ctr|0x2a|cnt|0x2b|arg|0x2c|chk|
|0x2d|mxp|0x2e|len|0x2f|pos|0x30|fld|
|0x31|mjv|0x32|mnv|0x33|rvb|0x36|byte_address|
|0x37|word_address|0x38|long_address| | | | |

**Ids `0x34` and `0x35` are not present in the table** (jumps straight from
`0x33` to `0x36`) even though `eval_function`'s switch still has live `case 0x34:`
/`case 0x35:` arms calling `fn_lb_dead`/`fn_hb_dead`. Those two functions build a
deferred-canonical-form marker text `"@LB("`/`"@HB("` (strings at `0x454860`,
`0x454868`) and otherwise just double the value (`fn_lb_dead`) or double-plus-one
(`fn_hb_dead`) when it's not a forward reference - i.e. this looks like leftover
code for two functions that existed in an older CLAS56 release and were removed
from the name table but not from the switch. **Dead/unreachable code**, but note
for anyone reusing `eval_function`'s switch structure: don't be tempted to
"clean it up" out of existence without checking whether some other version of
the table (or `-95` compatibility option) re-enables ids `0x34`/`0x35`.

## `@`-function implementations, by id

- **`def`/`mac`** (`fn_def_or_mac`, id 1 or 6): is a symbol (`def`) or macro
  name (`mac`) defined? Optional quoted name, else identifier token.
- **`exp`** (`fn_exp`): true if the parsed sub-expression ends up referencing an
  external symbol (sets `fn_exp_flag`=0 before parsing, tests it after; the flag
  itself is set somewhere in the symbol-resolution path this group didn't fully
  trace - likely `symtab.c`/`ext_lookup`).
- **`int`** (`fn_int`): true if the sub-expression's type (`W4`) is integer.
- **`lcv`** (`fn_lcv`, `@LCV(Q)` / `@LCV(R)`, optional 2nd arg forces "Illegal
  function argument" per `t4.lst`): DO-loop-related counter query; the largest
  single function in func.c (1588 bytes) - only partially traced by this group,
  see cross-module interface notes below.
- **`msp`** (`fn_msp`): numeric memory-space code (0-5) of the parsed
  sub-expression's space attribute (`W7`).
- **`scp`** (`fn_scp`, `@SCP(s1,s2)`): reads two quoted strings and returns
  whether they compare equal (`strcmp==0`) - despite the name, this is a plain
  **string-compare** function, not a symbol-scope query.
- **`len`** (`fn_len`): length of a quoted string.
- **`pos`** (`fn_pos`, `@POS(hay,needle[,start])`): 0-based index of the first
  occurrence of `needle` in `hay` at/after `start` (default 0); if not found,
  or if `needle` is `""`, returns `strlen(hay)` (**not** `strlen(hay)+1`).
  Confirmed against `t2.lst`: `@POS('abc','x')`=3, `@POS('abcabc','c',3)`=5,
  `@POS('abc','')`=3.
- **`fld`** (`fn_fld`, `@FLD(word,val,width[,pos=0])`): `insert_bits`-style
  field write - inserts the low `width` bits of `val` into `word` at bit
  position `pos` (`width` 0-24, `pos` 0-23); confirmed `@FLD(0,-1,24)` =
  `0xFFFFFF`.
- **`cvi`/`cvf`/`frc`/`unf`/`lfr`/`lun`** (`fn_convert`, ids 8/9/0xb/0x1b/0x25/0x26):
  representation converters. `cvi`: force integer type (truncating, see
  "Numeric conversion semantics" below). `cvf`: force float type. `frc`:
  force the **rounded 24-bit fraction** representation (via
  `float_to_fixed_frac`, format 3). `unf`: reinterpret the low 24 bits as a
  signed Q.23 fraction and convert back to float. `lfr`/`lun`: 48-bit (format 6)
  analogues of `frc`/`unf`.
- **`cvs`** (`fn_cvs`, `@CVS(space,expr)`): attaches/converts the memory-space
  attribute of `expr` to the 1-letter `space` code.
- **`sgn`** (`fn_sgn`): -1/0/1 by sign of the (converted-to-double) argument.
- **`lst`/`rel`/`ccc`/`ctr`/`cnt`/`chk`/`mxp`/`mjv`/`mnv`** (`fn_query_misc`):
  parameterless queries: `lst`=list-enable flag, `rel`="relocatable mode"
  option, `ccc`=`ccc_value` global, `ctr`=`@CTR(L)`/`@CTR(R)` current load/run
  location-counter value (selected by a following `l`/`r` character), `cnt`=
  current macro-expansion iteration count ("Macro expansion not active" if none
  is active), `chk`=running checksum value, `mxp`=boolean "currently inside a
  macro expansion", `mjv`/`mnv`=assembler major/minor version numbers
  (`major_version`/`minor_version` globals - almost certainly `6`/`3` to match
  the "Version 6.3.0" banner, i.e. these globals are what the version banner
  itself is built from; worth double-checking against whichever group owns the
  banner-printing code).
- **`min`/`max`** (`fn_minmax`): running min/max over a comma-separated list of
  1-or-more expressions, as doubles; confirmed `@MIN(3,1.5,2)*4.0/8.0` = 0.75
  (`0x600000` = 0.75 in Q.23).
- **`rnd`** (`fn_rnd`, `@RND`, no arguments): **Win32-dependent** - seeds a
  Park-Miller "Minimal Standard" LCG (`a=16807, m=2^31-1`, Schrage's method,
  constants `0x1f31d`=127773, `0x41a7`=16807, `0xb14`=2836 match the textbook
  implementation exactly) from `GetCurrentProcessId()` on first call, advances
  it, returns `state/2147483647.0` as a float in `(0,1)`. **Portability note for
  the rewrite**: `GetCurrentProcessId` is a Win32 call and must be replaced (the
  project's `SOURCE_DATE_EPOCH`/`time(NULL)` convention is the natural seed
  substitute); the LCG *step* itself is trivially portable ANSI C and must be
  kept bit-for-bit identical, or `tests/compare.py --time` runs that happen to
  use `@RND` will disagree between original and rebuilt tool regardless of
  seeding (flag this to whoever owns test-input selection: prefer avoiding
  `@RND` in golden test inputs, since the seed can never match the original's
  PID-derived one).
- **`lng`** (`fn_lng`, `@LNG(hi,lo)`): packs two plain 24-bit integers into one
  48-bit "long" value (`hi` into `W1`, `lo` into `W2`, format forced to 6);
  confirmed `@LNG(-1,2)>>24` = `0xFFFFFF`. Both arguments must already be
  format-3 (plain 24-bit) values, else "Expression result too large".
- **`arg`** (`fn_arg`, `@ARG('name)` or `@ARG(n)`): true if the Nth (or
  named) macro dummy argument was passed a non-empty value; "Macro expansion
  not active" / "Dummy argument not found" otherwise.
- **`rvb`** (`fn_rvb`, `@RVB(val[,width=24])`): reverses the low `width` bits of
  `val`; confirmed `@RVB(1,0)`=0, `@RVB(1)`=`0x800000`.
- **`byte_address`/`word_address`/`long_address`** (ids 0x36/0x37/0x38): byte
  address stays unchanged (divide-by-1, effectively a no-op passthrough in this
  code - any actual "byte-addressable" tagging must happen downstream, not
  here), word address = value>>1 (with the dropped bit folded in from the next
  word up), long address = value>>2 (2 dropped bits folded in) - i.e. these
  convert a byte-granular address into 16-bit-word or 32-bit-word units.
- **acs/asn/atn/cos/log/l10/sin/sqt/tan/xpn/abs/snh/coh/tnh/flr/cel**
  (`fn_math1`, single-argument CRT math call via the table's `fn1`): converts
  the argument to `double`, calls the CRT function with `errno` cleared first,
  maps `EDOM`(0x21)/`ERANGE`(0x22) to "Argument outside function domain" /
  "Function result out of range", anything else to "Unknown math error".
  Confirmed against `t2.lst`/`t5.lst`: `@LOG(0.0)`=range error,
  `@SQT(-1.0)`=domain error, `@POW`-style errors go through `fn_math2` instead.
- **at2/pow** (`fn_math2`, two-argument, via `fn2`): same error handling,
  two `double` arguments.

## Numeric conversion semantics (must be bit-exact on non-x86 hosts)

This is the part of the brief that matters most for portability; every routine
below currently runs through the x87 FPU with **80-bit extended** (`float10`,
i.e. `long double` in Ghidra's naming) intermediates for `+ - * /` on floats
(`op_add`/`op_sub`/`op_mul`/`op_div`), narrowed back to `double` only at the
point a value is stored into `EXPR_VAL`. `%` (`op_mod`) is the one exception:
it calls the CRT `fmod(double,double)`, which on MSVC's calling convention
narrows both operands to 64-bit `double` *before* the call even though the
surrounding code is otherwise all `float10` - i.e. `op_mod`'s result is subtly
less precise than a hypothetical extended-precision modulo would be, and a
portable reimplementation using plain `double` throughout will therefore match
`op_mod` exactly while potentially differing very slightly from `op_add` et al.
in their last bit for values that stress 80-bit intermediate precision. Given
the project's target hosts have no 80-bit float type at all, the pragmatic
choice is "everything is `double`" and accept that this is already an
unavoidable, already-tiny deviation from the x86 original for chained
float arithmetic - flag any test failures here rather than trying to emulate
x87 extended precision on m68k/NeXT.

Two entirely different double -> fixed conversions exist; do not conflate them:

1. **Truncating "to integer"** (`float_to_fixed_raw` -> `double_to_int24_trunc`
   / `double_to_int48_trunc`), used by `@CVI`/`@CVS`/`@LNG`'s float branch and
   whenever a floating value is coerced to plain integer type. Plain
   truncation toward zero via the CRT's `_ftol` helper (MSVC's classic `_ftol`
   temporarily sets the FPU control word to round-toward-zero, converts, then
   restores it - i.e. it behaves exactly like an ISO C `(long)x` cast). **No
   domain check, no warning, no rounding** - `@CVI(2.5)`=2, `@CVI(-2.5)`=-2,
   `@CVI(-0.5)`=0 (all confirmed in `t1.lst`/`t3.lst`). A portable C89
   implementation can simply use `(long)x` (or careful manual truncation if
   `x` may exceed `LONG_MAX`) - no special rounding-mode dance is needed on
   any host.
2. **Rounding "to Q.23/Q.47 fraction"** (`float_to_fixed_frac` ->
   `double_to_frac24` / `double_to_frac_n`), used for the implicit conversion
   of a bare floating `dc` operand, and by `@FRC`/`@LFR`. This is the
   interesting one:
   - **Domain**: value must be in `[-1.0, +1.0)` (`+1.0` itself is *out* of
     domain). Outside this range: warning **"Expression value outside
     fractional domain"** and the result is clamped to the representable
     extreme (`0xFF800000` i.e. exactly -1.0 for `x < -1.0`; `0x7FFFFF` i.e.
     the maximum positive fraction for `x >= 1.0`). Confirmed exactly by
     `t1.lst`: `dc -1.5` and `dc 1.0` both warn (`1.0` is in-domain-looking but
     the check is **exclusive** at the top).
   - **Rounding**: scale by `2^23` (or `2^(width-1)` for `double_to_frac_n`'s
     arbitrary-width variant used elsewhere for 8/12/16-bit fraction fields),
     add `+0.5` (`x>=0`) or `-0.5` (`x<0`) bias, truncate toward zero via
     `_ftol`, **then**, if the biased value was itself an exact integer (i.e.
     the pre-bias fractional part was exactly `0.5` ULP), clear the result's
     LSB. That last step is round-**half-to-even** (banker's rounding)
     implemented as "round half away from zero, then nudge exact ties down to
     even" - this exact two-step algorithm must be reproduced bit-for-bit; a
     naive `nearbyint()`/"round half away from zero" alone will disagree on
     exact ties. Finally clamp the biased/truncated magnitude to the max
     positive representable value (`0x7FFFFF` for 24-bit) before masking to
     the field width, so a value that rounds *up to* exactly `1.0` after
     biasing does not overflow into the sign bit.
   - `double_to_frac_n`'s width parameter is a *mask* (`0xff`, `0xfff`,
     `0xffff`, or, implicitly, the 24-bit default `0xffffff`), and the
     "half" scale used for the `+-0.5` bias is `(mask+1)/2`; the final result
     is `min(scaled, ~mask & fullword) & mask` (sign-extended downward, i.e.
     negative results keep the mask's top bits set) - reproduce this
     generically as `frac_n(x, width_bits)` rather than four separate cases.

Integer `*`, `/`, `%` on values wider than 32 bits go through a small
unsigned base-256 (radix-256) big-integer library (`bigint_from_words` /
`bigint_to_words` pack/unpack the 8+24+24-bit `EXPR_VAL` triple into an 8-byte
little-endian array; `bigint_div_digit`/`bigint_mul_small`/`bigint_cmp_ge`/
`bigint_sub` implement classic schoolbook long division one base-256 digit at
a time, `bigint_divmod` is the shared entry point used by both `op_div` (takes
the quotient) and `op_mod` (takes the remainder)) - signs are stripped before
entry (`negate_value` on either operand that's negative) and reapplied after
(`negate_value` on the result per the XOR of the two original signs). This is
**not** the same code path as the float division/modulo above; confirm parity
by testing both large-magnitude and negative-operand integer division/modulo
in `tests/arith`.

`int24_to_float10`/`int48_to_float10` (integer -> float direction) use a
manual sign/magnitude technique (negate, convert magnitude, re-negate) rather
than relying on the compiler's native (u)int-to-float conversion - this was
presumably done in the original to control rounding of the top bit of a 24-
or 48-bit two's-complement value cleanly; a portable rewrite can just do the
same manual sign/magnitude conversion in `double` arithmetic, which will be
exact (no precision is lost converting a <=48-bit integer magnitude to
`double`).

`@RVB` (`fn_rvb` in func.c) and `insert_bits`/`insert_bits_field` (used by
`@FLD`) are exact, portable bit twiddling - no numeric-precision concerns
there, just make sure widths (0-24, 0-48 where relevant) are masked exactly
as the original.

## Cross-module interfaces (functions/data this group calls into, owned elsewhere)

- **error.c** (not this group): `report_error`/`report_warning`
  (Ghidra `FUN_00413085`/`FUN_004133a9`) - called from nearly every function in
  this group to print `"**** <line> [<file> <line>]: ERROR/WARNING --- <msg>
  (<field> field)"`; `which_field` (this group) supplies the `(<field> field)`
  suffix's field name via a pointer-range test against `fld_label` /
  `fld_opcode` / `fld_operand` / `fld_operand2` / `fld_operand3` (owned by
  whichever group parses the source line into those five field buffers -
  likely `dspasm.c`/`input.c`). `report_fatal` (`FUN_00412fa0`) is the
  `exit(-1)`-and-cleanup path used transitively via `report_error`'s callers,
  not called directly from eval/func/arith.
- **symtab.c**: `sym_lookup`, `sym_add_ref`, `ext_lookup`, `ext_add` for
  identifier resolution; the resolved-symbol struct's field layout (`local_18`
  in `parse_term`) is only partially reverse-engineered here (offsets `+0x10`,
  `+0x11`, `+0x2c`(value)... see `parse_term`'s copy block) - cross-check
  against `g2_symtab`'s struct notes for the authoritative symbol-entry layout.
- **util.c**: `get_symbol`, `get_string`, `xmalloc`/`xrealloc`/`xfree`
  (`FUN_00439857`/`84`/`b5`), `tab_search` (used by both `eval_function`'s
  name lookup and, indirectly, this group's own `match_register_name`-style
  callers elsewhere), `insert_bits`/`insert_bits_expr` (used by `fn_fld`).
- **macro.c**: `cur_macro` struct (`fn_arg`/`fn_query_misc`'s `cnt`/`mxp`
  cases reach into it at offsets `+4` and its dummy-argument linked list at
  `+0x10`, node layout `{name_ptr, value_ptr, next_ptr}` inferred from
  `fn_arg`'s traversal - not independently confirmed against macro.c's own
  allocator).
- **section.c**: `merge_mem_space`, and the run/load counter-object globals
  (`rt_counter_obj`/`ld_counter_obj`, `rt_pc`/`ld_pc`, `rt_space`/`ld_space`
  etc.) that `parse_term`'s `*`-token and `parse_binop_rhs`'s
  post-op canonical-text regeneration read.
- **listing.c**: `FUN_0041c9cf`/`FUN_0041cb65` (called from `eval_diag_note`
  and the fatal/warning printers) - presumed `list_output`/`list_flush`, not
  confirmed by this group.
- **pseudo.c**: `pack_string_operand` is called from the `DC`/`DCB`-style
  directive handlers there with the raw operand text; `fn_lcv`'s DO-loop
  counter access presumably mirrors state pseudo.c's `DO`/`ENDDO` handling
  owns.

## Quirks / bugs worth reproducing

1. **`@RND` reseeds from the Win32 process id** (`GetCurrentProcessId`) - not
   reproducible bit-for-bit on another OS/process by construction; the
   assembler's own output already isn't deterministic across *runs on the
   original Windows binary itself*, so this is a pre-existing non-determinism
   in the original tool, not something the rewrite can "get right" by matching
   the original more closely. Just implement the same LCG algorithm and seed
   from `SOURCE_DATE_EPOCH`/`time(NULL)` per project convention, and exclude
   `@RND` from golden-file byte-for-byte tests.
2. **Dead `@LB`/`@HB` (ids `0x34`/`0x35`)** - reachable only if some other,
   unseen table (or a compatibility option this group didn't find) still maps
   a name to those ids; otherwise pure dead code left over from an older
   CLAS56 release. Safe to port as literal dead code (keep the switch arms,
   just note in the C source that they are unreachable via the current name
   table) rather than silently dropping them, in case another tool version or
   option re-enables them.
3. **Round-half-to-even tie-break only on exact ties**: `double_to_frac24`'s
   even-correction only fires when the *biased* value lands on an exact
   integer, i.e. it detects "was the original fraction exactly N+0.5 ULP" by
   comparing the truncated result back against the pre-truncation biased
   double for bit-exact equality - this is an unusual, precision-sensitive
   test to replicate in portable C (equality compare on a computed double);
   don't "simplify" it into `x - floor(x) == 0.5` style logic without checking
   it still catches exactly the same set of ties as the original int
   round-trip comparison.
4. **`op_mod`'s narrowing to `double` via `fmod`** vs. every other float binop
   staying in extended precision on the original - see "Numeric conversion
   semantics" above; likely irrelevant once the whole rewrite uses `double`
   throughout, but worth a comment at `op_mod`'s call site explaining why it
   doesn't "need" the same extended-precision treatment as `+`/`-`/`*`/`/`.
5. **`fn_scp` is a string-compare, not a "scope" query** despite the name
   `SCP` suggesting "scope" - verified from its implementation (two
   `get_string` calls + `strcmp`), not just the table name.
6. **`@POS` "not found" sentinel is `strlen(haystack)`, not `strlen+1`** and
   an empty needle short-circuits to `strlen(haystack)` without ever entering
   the search loop - both confirmed against `t2.lst`; don't assume 1-based
   Pascal-style semantics just because the language target is retro.
7. **`byte_address_of`(`@BYTE_ADDRESS`) is a no-op passthrough** in this
   function alone (`FUN_00418cdb` literally just re-parses and returns the
   sub-expression) - if the original intent was to tag byte-granularity, that
   tagging must happen in a caller this group didn't trace; don't assume the
   three `*_address` functions are numerically symmetric (`byte`=`/1`,
   `word`=`/2`, `long`=`/4`) beyond what's shown here.

## Test evidence used

All five `t*.asm`/`t*.lst` pairs in `re/notes/ASM56000/scratch_g3_expr/` were
assembled with `re/bin_ft/ASM56000.EXE -a -b -l` (the fixed-time binary) and are
referenced by name throughout this document; they remain in place for reuse by
whoever implements `src/asm56000/eval.c` / `func.c` / `arith.c` as a ready-made
regression corpus for `tests/asm56000/run_tests.sh` (not added to the suite by
this group - out of scope per the brief, which asks this pass to produce names
and notes only).

## Summary

- 106 functions named (27 eval.c + 29 func.c + 50 arith.c), all high/med
  confidence except 4 (`eval_diag_note`, `fmt_storage_directive_text`,
  `fn_query_misc`'s per-id detail, `fn_lb_dead`/`fn_hb_dead`'s exact original
  names) marked low/med and flagged above.
- ~35 globals named (expression stack, canonical-form buffer, pass/option
  flags, macro/counter state); most are shared with 5+ other modules per
  `globals.txt` and will need central conflict resolution.
- Main structs: the 96-byte `EXPR_VAL` (fully mapped, see table above); the
  16-byte `@`-function table entry (`name*, id:u8, fn1*, fn2*`); the 19-entry
  binary-operator function-pointer table at `0x44fff8` (fully dumped and
  matched to opcodes).
- Open questions for other groups / follow-up: `EXPR_VAL` fields `W3`, `W19`,
  `W20`, `W22` (never observed written by this group's code, likely
  touched only by section.c/symtab.c producers); the exact symbol-table entry
  layout consumed by `parse_term` (cross-check with `g2_symtab`); who reads
  the `0x100000` "value came from rounded float" flag set by
  `float_to_fixed_frac`; `fn_exp_flag`'s true owner/setter (probably
  symtab.c/ext_lookup); `fn_lcv`'s full DO-loop-counter semantics (only
  skimmed, it's the largest function in func.c at 1588 bytes).
