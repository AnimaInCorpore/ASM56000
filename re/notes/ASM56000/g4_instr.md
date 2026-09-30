# g4_instr notes: amode.c, encode.c, procop.c, procxy.c (the instruction encoder)

Names/prototypes: `re/names/ASM56000/g4_instr.names.txt`. Scratch tests (all verified with
`re/bin_ft/ASM56000.EXE -a -b -l X.asm`): `re/notes/ASM56000/scratch_g4_instr/{t,cc,t3,t4,t5}.asm/.lst`,
table dumper `dump.py`, name-annotated decompilations `ann/*.c` (made by `ann.py`).

Revisions ($Id): amode.c 1.18 (1997/09/10), encode.c 1.13 (1996/07/31), procop.c 1.22 (1997/04/30),
procxy.c 1.11 (1994/07/15).

**Module boundary corrections** (string evidence: each module's literals follow its `$Id`):
- 0x405eea..0x405fd4 (5 funcs, modules.txt: amode) use strings *before* amode's `$Id` and are only
  called from dspasm/pseudo: almost certainly the tail of **dspasm.c**.
- 0x410901 (modules.txt: encode) resets debug.c's DEF staging state: tail of **debug.c**.
- 0x4127e6..0x412f33 (19 funcs, modules.txt: **error**, named `enc_*`/`y_code`... by g1) are
  **encode.c** ("Y/LLL/QQ encoding failure" precede error.c's `$Id` at 0x453d70). g4 names them in
  its names file (module column left `error`) - they are the parallel-move encoders, see 3.3.
- 0x42420d..0x424b1a (8 funcs, modules.txt: procop) use strings before procop's `$Id` (0x455d68):
  tail of **object.c** (COFF reloc/lineno/symbol/string tables).
- 0x42b12c, 0x42b1e5 (modules.txt: pseudo, g5 names `pseudo_check_move_class/_mask`) use a string
  before pseudo.c's `$Id`: they are **procxy.c** (called only from procxy/procop).

---------------------------------------------------------------------------------------------------

## 1. Data structures

### 1.1 Instruction table entry `IENTRY` (InstrTab @0x44e0b0, 142 x 20 bytes, mchglb)

Binary-searched by `util.c:FUN_00438f1a` (see g1_main.md 1.1). `proc_line1/2` (input.c ~l.828) does
`CycleCount = e->f4; proc_instr(e); CycleTotal += CycleCount;`.

| off | field | meaning (verified) |
|-----|-------|--------------------|
| +0x00 | `char *name` | lower-case mnemonic |
| +0x04 | `f1` = **iclass** | dispatch class for `proc_instr`'s switch; read as `(int)(signed char)` of the low byte. Bit 7 set = hidden (lookup callback) - no entry uses it. |
| +0x08 | `f2` = **pmclass** | parallel-move permission mask passed to `do_xy`: `0`=no parallel move, `1`=data-ALU moves (I,R,U,X,Y,L,XY,X:R,R:Y), `0x10`=MOVEC forms, `0x20`=MOVEM forms, `0x35`=MOVE (1\|0x10\|0x20\|4; bit 4 is never tested), **`2` = dynamic**: the handler's return value becomes the pmclass (and the handler's success is then assumed = 1). Used by and/or/mac/macr/mpy/mpyr: register forms return 1, `#imm` forms return 0. |
| +0x0c | `f3` = **template** | 24-bit opcode template, copied to `insn.word[0]`; field encoders OR/insert into it. For data-ALU ops it is the low byte (ALU opcode) - `proc_instr` adds bit 21 (0x200000 = "no parallel move" prefix `0010 0000 0000 0000`) when pmclass!=0 and the X field is empty. Condition-code mnemonics carry cc in bits 12-15 (jcc/jscc/tcc) or bits 0-3 (debugcc: 0x300\|cc). |
| +0x10 | `f4` = **cycles** | base clock count (oscillator clocks) printed by `OPT CC` as `[n - total]`; handlers add +2/+4/+6 to `CycleCount` for extra words etc. (verified: cc.asm/lst: nop 2, jmp $200 4, jmp $2000 6, movem 6, illegal 8, do 6). stop/wait have 0. |

iclass -> mnemonics -> handler (`proc_instr` @0x424bf0 switch):

| f1 | mnemonics | handler |
|----|-----------|---------|
| 0x01 | addl addr subl subr | p_addl 42578d |
| 0x02 | inc dec (56002+) | p_alu1 4256e7 |
| 0x03 | abs asl asr clr neg rnd | p_alu1 |
| 0x04 | and or | p_and_or 42562d |
| 0x05 / 0x06 | bchg bclr bset / btst | p_bitop 425abb |
| 0x07 | cmp cmpm | p_alu2 425883 |
| 0x08 | div | p_div 425a60 |
| 0x09 | do | p_do 425d15 |
| 0x0a | enddo | p_enddo 426106 |
| 0x0b 0x0c 0x0d 0x1b 0x29 0x2c | illegal, reset, stop wait, nop, debug*, swi | p_noarg 425340 |
| 0x0e / 0x13 | jcc (all cc) / jmp | p_jmp 426305 |
| 0x0f / 0x11 | jclr jset / jsclr jsset | p_jbit 426a45 |
| 0x10 / 0x12 | jscc / jsr | p_jsr 42666f |
| 0x14 | lea lua | p_lua 425a05 |
| 0x15 0x1a 0x2a 0x2b | mac mpy macr mpyr | p_mul 426ee5 |
| 0x16 0x17 0x18 | movec move movem | p_move 4270d6 |
| 0x19 | movep | p_movep 42712b |
| 0x1c | norm | p_norm 425945 |
| 0x1d | rep | p_rep 4261da |
| 0x1e 0x1f | rti rts | p_rts 42546b |
| 0x20 / 0x24 | eor / adc sbc | p_eor_adc 4257f4 |
| 0x22 0x23 | add sub / tfr | p_alu2 |
| 0x25 | andi ori | p_andi 425552 |
| 0x26 | tcc (all cc) | p_tcc 426dc3 |
| 0x27 | tst | p_alu1 |
| 0x28 | lsl lsr not rol ror | p_alu1 |
| other | - | `fatal("Error in mnemonic table")` |

CPU-variant gating (`CpuVariant` @0x44f9fc: default 0x1fff = everything; `-p56000/56001`=0,
`56001c`=1, `56002`=2...): illegal needs !=0; inc/dec, debug* need >=2 (else "Unrecognized
mnemonic", opcode field); register forms of bit ops / jclr etc. and some X:R forms need !=0
(verified t5.asm with -p56000/-p56001c/-p56002). **The opcode word is emitted even on error**
(e.g. `000005`, `0A0020` in t5.lst) - `proc_instr` emits regardless of the handler result.

### 1.2 Register ids (RegNameTab @0x44ece8, 51 `char *`, index = id returned by `arith.c:match_register_name`)

```
0 x   1 y   2 a   3 b   4 x0  5 y0  6 x1  7 y1  8 a0  9 b0  10 a1 11 b1 12 a2 13 b2
14-21 r0-r7   22-29 n0-n7   30-37 m0-m7   38 ab 39 ba 40 a10 41 b10
42 omr 43 sr 44 la 45 lc 46 ssh 47 ssl 48 sp 49 mr 50 ccr      (51: NULL)
```
g1's `RegNameTab`@0x44ed44 is `&RegNameTab[23]` of this same array (dspasm/pseudo index it that
way); the values after the NULL (0x44edb4) are g1's mask table. amode.c uses it only for
`err_s("Invalid register specified", RegNameTab[id])`.

### 1.3 Operand / addressing-mode descriptor `OPERAND` (32 bytes, always a stack local, 8 longs)

Filled by `get_amode` (reset: [0]=0, [1]=4 only if flags&4, [2..4]=0, [5]=-1, [6]=0, [7]=0).
Memory space is set before (by `util.c:get_mem_space(op, allowed)` which parses `x:`/`y:`/`p:`/`l:`
and writes [1]) or taken from the expression.

| idx/off | field | meaning |
|---------|-------|---------|
| [0] +0x00 | `mode` | addressing mode code, table below |
| [1] +0x04 | `space` | memory space: 0=P 1=X 2=Y 3=L 4=none (E=0x1c, D=0x11d not used here) |
| [2] +0x08 | `fwd` | `expr.W6 & 0x8000000` (value still contains a forward reference) |
| [3] +0x0c | `force` | 0 none, 0x1000000 `>` long, 0x2000000 `<` short, 0x4000000 `<<` I/O short (from `util.c:get_force(allowed)`: imm allows 0x3000000, abs 0x7000000) |
| [4] +0x10 | `value` | immediate value / absolute address (24 bit) |
| [5] +0x14 | `reg` | register id (reg-direct: the register; indirect: the Rn), -1 default |
| [6] +0x18 | `sect` | `expr.W15` relocation section id (<0 = external) |
| [7] +0x1c | `cform` | malloc'd relocation expression text or NULL (see 1.5); consumers free it and zero the slot |

Mode codes (`op.mode`), their MMM/RRR (`mmm_code`/`rrr_code`) and ext words:

| mode | syntax | MMM | RRR | words | producer |
|------|--------|-----|-----|-------|----------|
| 0 | (none) | | | | |
| 1 | register direct | | | | amode_register |
| 2 | `(Rn)` | 100 | n | | amode_indirect |
| 3 | `(Rn)+` | 011 | n | | |
| 4 | `(Rn)-` | 010 | n | | |
| 5 | `(Rn)+Nn` | 001 | n | | |
| 6 | `(Rn)-Nn` | 000 | n | | |
| 7 | `(Rn+Nn)` | 101 | n | +2 cycles | |
| 8 | `-(Rn)` | 111 | n | +2 cycles | |
| 9 | `#xxxxxx` long immediate | 110 | 100 | +1 | amode_immediate |
| 10 | `#xxx` 12-bit immediate (DO/REP) | | | | |
| 11 | `#xx` 8-bit short immediate | | | | |
| 12 | `#n` bit number 0..23 | | | | |
| 13 | `#n` signed 5-bit, abs<=23 | | | | |
| 14 | `xxxx` absolute long | 110 | 000 | +1 | amode_absolute |
| 15 | `aaa` absolute short 12-bit (<0x1000) | | | | |
| 16 | `aa` absolute short 6-bit (<0x40) | | | | |
| 17 | `pp` I/O short (0xffc0..0xffff, encoded as low 6 bits) | | | | |

### 1.4 Instruction build record `INSN` (80 bytes = 20 longs, local of `proc_instr`)

Only these fields are used (by encoders, `proc_instr`, `sdi.c:sdi_expr`); size 0x50 is proven by the
20-dword copy in p_jmp/p_jsr's SDI path.

| off | field | meaning |
|-----|-------|---------|
| +0x00 | `nwords` | 1 or 2 (set to 2 by `set_ext_word` or handlers) |
| +0x04 | `word[0]` | opcode word, init = `f3` |
| +0x08 | `word[1]` | extension word, init 0 |
| +0x0c..+0x3c | - | unused (not initialized) |
| +0x40 | `cform[0]` | `char *` relocation expression for word 0 (built by `util.c:encode_field` / `insert_bits_expr`), init NULL |
| +0x44 | `cform[1]` | same for word 1 (moved from `op.cform` by `set_ext_word`), init NULL |
| +0x48,+0x4c | - | unused |

`proc_instr` frame: `INSN insn` followed by four OPERANDs passed to `do_xy`: `xs` (X field
source), `xd` (X field dest), `ys` (Y field source), `yd` (Y field dest), each with `space=4` preset.

### 1.5 Relocation text ("cform")

When an operand value is relocatable or external (`expr.W6 & 0x1000` or `W15 < 0`) the operand
parser stores `arith.c:fmt_storage_directive_text(op)` in `op.cform` (NULL unless the global
canonical-form buffer `cform_buf` is active): `"%d!%s@%d#%d"` = `field!expr@space#width` with width
by mode: 10->12, 11->8, 12->1, 13->-1, 15->12, 16->6, 17->0x56 (I/O short marker), else plain
`"%s@%d#%d"` with width 0. Encoders that place such a value into a word call
`util.c:encode_field(insn, op, pos, width)`, which (when `op.cform`) formats the current word as
`"$%0*lX"` (6 digits) and wraps it via `insert_bits_expr` into
`((W&~(~(~0<<w)<<p))|((E&~(~0<<w))<<p))` stored in `insn.cform[0]`; ext words just move the
text (`set_ext_word`). `enc_loop_imm` / `enc_bit_abs` build their two-field expressions themselves
(`"$%06lx"` upper-cased, `"(%s>>8)"`). DO's target gets `"%s-1"`.

### 1.6 DO-loop stack node (DoStack @0x45fc30, 16 bytes, xmalloc(0x10) in p_do)
`{ unsigned long la /* target-1 = word[1] */; 0; 0; next }` - g1_main.md section 4.1 owns the rest.

---------------------------------------------------------------------------------------------------

## 2. amode.c - operand / addressing mode parser

Purpose: parse one operand at `optr` (0x45f860, the shared scan pointer) into an OPERAND, restricted
by four "class" arguments, with range checks, forcing (`<`,`>`,`<<`) and warnings, plus the
pipeline bookkeeping for register operands (register written in previous instruction, duplicate
destinations).

### 2.1 Class arguments of `get_amode(flags, op, regclass, eaclass, absclass, immclass)`

`flags`: bit0 = operand must be followed by `,` (consumed); bit1 = destination (register written);
bit2 = reset `op.space` to 4 first. A zero class disables that kind of operand. Order of attempts:
register (if regclass) -> immediate `#` (if immclass) -> indirect `(`/`-(` (if eaclass) -> absolute
(if absclass). Error cascade when nothing matches: "Only register direct addressing allowed" (no
imm/ea/abs), "Only immediate addressing allowed", "Only immediate and register direct addressing
allowed", "Only register indirect addressing allowed", "Only register direct and indirect addressing
allowed", "Only immediate and register direct and indirect addressing allowed", "Invalid
addressing mode" (abs class given but not absolute). Empty operand: two errors "Syntax error -
missing address mode specifier" + "Possible invalid white space between operands or arguments".

**regclass** (`amode_register` switch; value = allowed register ids):

| cls | ids | cls | ids |
|-----|-----|-----|-----|
| 1 | a b | 0x0d | a |
| 2 | y0 y1 | 0x0e | b |
| 3 | x0 x1 a b | 0x0f | a b x0 y0 x1 y1 |
| 4 | y0 y1 a b | 0x10 | r0-r7 |
| 5 | x y a b ab ba a10 b10 (L regs) | 0x11 | 2..37 and 42..48 (== 6) |
| 6 | 2..37 (a..m7), 42..48 (omr..sp) | 0x12 | 0..48 (all but mr, ccr) |
| 7 | 42..48 omr sr la lc ssh ssl sp | 0x13 | mr ccr omr |
| 8 | m0 m1 (ids 30,31) | 0x14 | r0-r7 n0-n7 |
| 9 | a b x0 y0 x1 y1, r0-r7, n0-n7 | 0x15 | x y a b x0 y0 x1 y1 |
| 10 | x y | 0x16 | x0 a b |
| 0x0b | x0 y0 x1 y1 | 0x17 | x0 y0 y1 a b |
| 0x0c | x y x0 y0 x1 y1 | 0x18 | a b a1 b1, **a1->a, b1->b** (lsl/lsr/rol/ror/not/eor/and/or accept `a1`) |

Non-register text -> returns 0 (try other modes, optr restored); a register outside the class ->
`err_s("Invalid register specified", name)`, returns -1. (The alternative message "Register direct
addressing not allowed" for regclass 0 is unreachable: callers never pass 0.)

**eaclass** (`amode_indirect`): 1 = all modes 2..8; 2 = XY-move modes `(Rn) (Rn)+ (Rn)- (Rn)+Nn`
(no `(Rn)-Nn` "Post-decrement by offset addressing mode not allowed", no `(Rn+Nn)` "Indexed address
mode not allowed", no `-(Rn)` "Pre-decrement addressing mode not allowed"); 3 = update modes
`(Rn)+ (Rn)- (Rn)+Nn (Rn)-Nn` (no `(Rn)` "No-update mode not allowed"). Offset register (`parse_offset_reg`)
must be `Nn` with n == Rn's n ("Offset register number must be the same as address register number",
other regs "Invalid register specified for offset"); a bare `N`/`n` is accepted as shorthand
(`(r0)+n`, verified t3.lst). Syntax errors: "expected ')'", "probably missing ')'", "expected comma
or end of field", "expected '+' or '-'". After success `get_amode` calls `check_areg_stall`.

**absclass** (`amode_absolute`, value = `expr_to_uint_bits(rt_addr_mask)`; the result mode):

| cls | allowed / chosen | used by |
|-----|------------------|---------|
| 1 | long only (14) | DO target, jclr target, X:R/imm long, P: |
| 2 | I/O short only (17, value must be 0xffc0..0xffff unless deferred) | - |
| 3 | 12-bit short only (15) | - |
| 4 | 6-bit short only (16) | DO/REP `x:aa` |
| 5 | long or 12-bit short (auto: fwd ref/relocatable -> long; <0x1000 -> short; `<` forced short: >0xfff warns "too large to use short - long substituted" or errors in pass 2 if fwd) | jmp/jsr/jcc |
| 6 | long, I/O short, 6-bit short (auto: <0x40 short, 0xffc0.. I/O, else long; `<<` with value 0x40..0x7f becomes `value|0xffc0`) | bit ops |
| 7 | 6-bit short or I/O short only (long -> warn "substituting short/I/O short", or errors) | jclr/jset ops |
| 8 | long or I/O short (`<` -> warn, long) | movep |
| 9 | long or 6-bit short (`<<` -> warn "I/O short ... cannot be forced - long substituted", long) | parallel moves, do/rep |

Also: `OptMsw` && `merge_mem_space(expr.space, op.space)==0xa2c2a` -> warning "Absolute address
involves incompatible memory spaces"; if `expr.space!=4 && op.space==4` then `op.space=expr.space`;
forced I/O short with external value -> value 0xffc0. `InMacroExpand` (DO replay) suppresses the
I/O-range checks. Unknown class -> fatal "Absolute mode select failure".

**immclass** (`amode_immediate`; `get_imm_expr` = `expr_to_int24`, negative allowed only for 1,5,6,
floats converted to 24-bit fraction only for 1,6 else "Floating point value not allowed"):

| cls | result | check |
|-----|--------|-------|
| 1 | 9 long | `<` warns "Short immediate cannot be forced" |
| 2 | 10 (12 bit) | >0xfff "Immediate value too large"; `>` warns "Long immediate cannot be forced" |
| 3 | 11 (8 bit) | >0xff |
| 4 | 12 (bit no.) | >0x17 (!) |
| 5 | 13 | |value| > 0x17 |
| 6 | 11 or 9 auto | see below |

Class 6 (parallel-move `#`): *fractional short rule*: if Y field (`Op3Field`) empty, not fwd, not
forced long, and `imm_dest_is_alu()` (lookahead with errors muted: next operand after `,` is
a,b,x0,y0,x1,y1) then unless (`OptSi` && value<=0xff && !forced short) the value is replaced by
`(v>>16)&0xff` when its low 16 bits are 0 (so `#0.5,x0` -> `244000`, `#$120000,a` -> `2E1200`,
`#$120000,r0` stays long; with `OPT SI` `#$12,x0` is long - verified t3.lst). Then: forced long
-> 9; forced short -> 11 (if not fwd and (>0xff or (float and not shifted)): warn "Immediate value
too large to use short - long substituted", 9; if fwd: pass-2 error when >0xff); unforced: fwd or
relocatable -> 9; >0xff or (from-float and value unchanged and !=0) -> 9; else 11.
Other classes: fatal "Immediate mode select failure". The `op.fwd` gating means range errors for
forward references are raised only in pass 2.

### 2.2 Pipeline / register-usage bookkeeping (amode side)

- `note_reg_direct(flags, regclass, reg)`: first control-type register seen on the line
  (m0-m7 or omr..ccr) sets `CtrlRegAccessed`. Source (flags&2==0): `LastSrcReg = reg`.
  Destination: if reg is r/n/m (14..37) and != LastSrcReg: `AregWritten |= 1<<(reg-14)`,
  `AregWritePc = *rt_pc`; then `check_dup_dest`.
- `check_dup_dest(regclass, reg)`: accumulator-part bitmask (a0=1 a1=2 a2=4 b0=0x10 b1=0x20
  b2=0x40; a=7/b=0x70 except regclass 0x18 where a=2/b=0x20; a10=3, b10=0x30, ab/ba=0x66;
  others not checked) accumulated in `DestRegMask`; overlap -> "Duplicate destination register not
  allowed", returns 1.
- `check_areg_stall(reg, mode)`: mask = Rn bit; +Nn bit (<<8) for modes 5-7; +Mn bit (<<16) for
  modes 3-8. If `AregWrittenPrev & mask` and (`*rt_pc == AregWritePc + PrevInstrWords` or
  `InMacroExpand`): if `!OptRp || InMacroExpand || ErrOnThisLine` -> err "Contents of register
  written in previous instruction not available", else `listing.c:FUN_0041bbb2` (named
  `lst_print_reg_note` by g6 - it actually **inserts a `\tnop` line**, warning "... - generating NOP
  instruction", verified t4.lst with `OPT RP`).
- Per line reset is `input.c:do_line_reset`: `AregWrittenPrev=AregWritten`, `HazardPrev=HazardCur`,
  clears the others; both "prev" values are cleared again at even addresses inside the vector area
  (`VectorCheck && *rt_pc < VectorAreaSize(0x40)`).

### 2.3 amode.c functions

- 0x405eea `long get_date_time(char *date, char *time)` (dspasm tail): `time(0)`, `localtime`,
  `sprintf(date,"%02d-%02d-%02d", tm_year, tm_mon+1, tm_mday)` - **tm_year unmodified -> "126" in
  2026, "99" in 1999** (the Y2K quirk of the listing header); `sprintf(time,"%02d:%02d:%02d",h,m,s)`;
  returns `util.c:tm_to_secs(tm)`. Called from `main` (-> 0x45f834/0x45f838/0x45f848).
- 0x405f6a `int set_file_type(fname, type, creator)`: returns 1. Mac file-type stub (called with
  "TEXT"/"MPS " for listing, "COFF"/"MPS " for object).
- 0x405f74 `void free_str_list(list)`: frees a `{char *s; next}` list (include paths, end of pass).
- 0x405fbe `set_opt_rp(on)` (ignored when `RpLocked` 0x45eb8c), 0x405fd4 `get_opt_rp()`: OPT RP/NORP
  (ids 0x39/0x3a) and init (on in `-c`/OptC mode).
- 0x405fe0 `int parse_xfield_src(op)`: `get_amode(0, op, 0x12, 1, 6, 6)`; if `op.space==4` and mode
  3..6 (U move `(Rn)+` alone) the field must end ("Address mode syntax error - extra characters"),
  otherwise a `,` must follow ("expected comma"). Frees `op.cform` on failure.
- 0x4060d8 `int parse_operand(flags, op, rc, ec, ac, ic)`: `get_amode`, then comma (flags&1: "Address
  mode syntax error - expected comma", cform *not* freed) or end-of-field check ("extra
  characters"). The workhorse used everywhere (also by scs.c 0x4312d0/0x4324d9).
- 0x4061ae `get_amode` (2.1). 1 = ok, 0 = error.
- 0x40641c `amode_register(regclass, op)`: 1 match (`op.mode=1, op.reg=id`), 0 not a register,
  -1 error.
- 0x406938 `note_reg_direct`, 0x4069eb `check_areg_stall`, 0x406aaf `check_dup_dest` (2.2).
- 0x406bfa `amode_indirect(eaclass, op)`: 1/0/-1 as above; `op.reg = Rn`.
- 0x406f87 `amode_immediate(immclass, op)`, 0x407462 `get_imm_expr(immclass)` (returns EXPR_VAL*,
  freed by caller with `free_expr`), 0x407511 `imm_dest_is_alu()`.
- 0x40758c `amode_absolute(absclass, op)`; `op.value` uses 0xffc0 for forced-I/O externals.
- 0x40800f `parse_addr_reg()`: next register must be r0-r7 else -1 (no message).
- 0x408046 `parse_offset_reg(areg)`: returns 1/0 (never -1). Quirk: `amode_indirect`'s `(Rn+Nn)`
  branch tests `== -1`, so an invalid offset there only yields the offset error and parsing goes on.

---------------------------------------------------------------------------------------------------

## 3. encode.c - opcode field encoders

Purpose: pure bit packing. Each `xxx_code(reg)` maps a register id (or mode) to a manual field value
and calls `fatal("<FIELD> encoding failure")` otherwise; each `enc_*` inserts fields into
`insn->word[0]` with `util.c:insert_bits(word, val, pos, width)` (plain values) or
`encode_field(insn, op, pos, width)` (operand value, cform-aware), and `set_ext_word` for ext words.
Convention for `_w` variants: set bit 15 (W) - or bit 22 (`w`, Y side of XY) - then call the base
encoder with the two operand arguments swapped. Bit positions below are verified against the
listing words in t.lst/t3.lst/t4.lst/cc.lst.

### 3.1 Field code functions

| func | field | mapping (reg id -> code) |
|------|-------|--------------------------|
| ee_code 410994 | EE | mr 0, ccr 1, omr 2 |
| d_code 410a2b | d | a 0, b 1 |
| jjj_code 410a61 | JJJ ("DXY") | a,b 0; x0 4, y0 5, x1 6, y1 7 (DIV uses the low 2 bits) |
| rrr_code 410b29(mode,reg) | RRR | mode 14 (abs long) -> 0, mode 9 (imm long) -> 4, else r0-r7 -> 0-7 |
| mmm_code 410c5c(mode) | MMM | 2->4 3->3 4->2 5->1 6->0 7->5 8->7 9,14->6 |
| s_code 410cfb(space) | S | space==Y |
| ddddd_code 410ec7 | DDDDD | x0 4 x1 5 y0 6 y1 7 (via dd_code), a0 8 b0 9 a2 0xa b2 0xb a1 0xc b1 0xd a 0xe b 0xf (via ddd_code), r0-7 0x10-17, n0-7 0x18-1f (nnn_code) |
| d6_code 410d97 | DDDDDD | ddddd for ids 2..29; m0-7 -> 0x20+fff_code; omr..sp -> 0x38+ccc_code (omr 2, sr 1, la 6, lc 7, ssh 4, ssl 5, sp 3) |
| dd/ddd/fff/nnn/ccc_code | sub-codes of the above | |
| xx_code 4121da | ee (XY X reg) | x0 0 x1 1 a 2 b 3 |
| yy_code 41223d | ff (XY Y reg / R:Y) | y0 0 y1 1 a 2 b 3 |
| x_code 4127b0 | e (R:Y) | x0 0 x1 1 |
| y_code 41290b | F (X:R) | y0 0 y1 1 |
| lll_code 4129d7 | L+LLL (4 bit) | a10 0 b10 1 x 2 y 3 a 8 b 9 ab 0xa ba 0xb |
| qq_code 412f33 | QQ | y1 0 x0 1 y0 2 x1 3 |

### 3.2 Non-parallel-move instruction encoders

| func | format produced (bit numbers) |
|------|-------------------------------|
| enc_andi 410950(insn,imm,dst) | word \|= 0xb8, EE@0(2), imm@8(8) (`and #` -> andi, `or #` -> template 0x40\|0xb8 = ori) |
| enc_div 4109d7(insn,src,dst) | d@3, JJ@4(2) |
| enc_norm 410acf(insn,Rn,dst) | d@3, RRR@8 |
| enc_loop_ea 410bcb | S@6, RRR@8, MMM@11, bit14 (DO/REP x:ea) |
| enc_loop_abs 410d0f | S@6, aa@8(6) |
| enc_loop_reg 410d51 | DDDDDD@8, 3@14(2) |
| enc_loop_imm 41118f | bit7, imm>>8 @0(4), imm@8(8); relocatable -> cform built from `"(%s>>8)"` and the plain text |
| enc_do_{ea,abs,reg,imm} 4112b9/4113ae/4113d5/4113fc(insn,op,target) | base + `set_ext_word(insn,target,1)` |
| set_ext_word 4112e0(insn,op,minus1) | only for op.mode 14 or 9: word[1]=value, nwords=2, cform[1]=op.cform (moved); minus1: value-1 (if !=0) and cform `"%s-1"` |
| enc_jmp_abs 411423 / enc_jcc_abs 411501 (identical code) | bit18, addr@0(12) |
| enc_jmp_ea 411457 | bit7, RRR@8, MMM@11, 3@14(2), bit17, ext |
| enc_jcc_ea 411535 | word \|= (word>>12)&0xf (cc to low nibble), 5@5(3), RRR, MMM, 3@14, ext |
| enc_tcc 411697(insn,s,d) | d@3, JJJ@4 |
| enc_tcc_r 4115dc(insn,s1,d1,s2,d2) | Rdst RRR@0, d@3, JJJ@4, Rsrc RRR@8, bit16 |
| enc_bit_ea 4116eb(insn,bit,op) | S@6, RRR@8, MMM@11, bit14, bit#@0(5), ext |
| enc_bit_reg 4117a2 | 0x301@6(10) (bits 6,14,15), DDDDDD@8, bit#@0(5) |
| enc_bit_abs 4117ff | S@6, bit#@0(5), aa@8(6); own two-field cform (`"$%06lx"` upper-cased) |
| enc_bit_pp 4119e4 | bit15 + enc_bit_abs |
| enc_jbit_{ea,reg,abs,pp} 411a18/411a43/411ab2/411add(insn,bit,op,target) | the bit-op encoders + target ext word; `_reg` inserts 0x180@7(9) (clears bit7, sets 14,15) |
| enc_movep_reg 411b08(insn,pp,reg) | DDDDDD@8, S(pp)@16, pp@0(6) |
| enc_movep_mem 411b70(insn,pp,mem) | S(pp)@16; mem.space==P: bit6 else S(mem)@6 + bit7; RRR@8, MMM@11, pp@0(6), ext |
| enc_movep_reg_w / _mem_w 411c6a/411c9e | W (peripheral is destination) |
| enc_movec_ea 411cd2 / ea2 411fc7 (identical) (insn,creg,mem) | \|0x40000, DDDDDD(creg)@0, S@6, RRR@8, MMM@11, bit14, bit16, ext |
| enc_movec_abs 411f11(insn,creg,abs) | \|0x40000, DDDDDD@0, S@6, bit16, aa@8(6) |
| enc_movec_reg 411e5a(insn,creg,reg) | \|0x40000, DDDDDD(creg)@0, bit7, DDDDDD(reg)@8, bit14 |
| enc_movec_imm 411de6(insn,imm,creg) | \|0x40000, DDDDDD@0, bit7, bit16, imm@8(8) |
| enc_movec_*_w | W = control register is the destination |
| enc_movem_ea 412ce3(insn,reg,mem) | \|0x70000, DDDDDD@0, bit7, RRR@8, MMM@11, bit14, ext |
| enc_movem_abs 412dd4 | \|0x70000, DDDDDD@0, aa@8(6) |
| enc_lua 412e4f(insn,mem,dst) | DDDDD(dst)@0(4), RRR@8, MM@11(2) |
| enc_mul_imm 412ecb(insn,s1,imm,dst) | d@3, QQ@4, n@8(5) |

### 3.3 Parallel-move encoders (word bits 8..23; bits 0..7 = ALU op from the template)

| func | move type (manual format) |
|------|---------------------------|
| enc_pm_imm 412baf(insn,imm,dst) | I: `001ddddd iiiiiiii` = DDDDD@16(5), bit21, imm@8(8) |
| enc_pm_reg 412c09(insn,src,dst) | R: DDDDD(dst)@8, DDDDD(src)@13, bit21 |
| enc_pm_update 412c72(insn,op) | U: RRR@8, MM@11(2), 0x81@14(8) (= bits 14,21) |
| enc_pm_x_ea 412424(insn,reg,mem) | X: RRR@8, MMM@11, bit14, DDDDD low3@16, DDDDD>>3 @20(2), bit22, ext (W=0: reg->mem) |
| enc_pm_y_ea 412532 | bit19 + X form (Y memory) |
| enc_pm_x_abs 41259a / y 41264a | same with aa@8(6), bit14=0 |
| `_w` of those (4124fe,412566,412616,41267e) | W: memory -> register |
| enc_pm_l_ea 412ac3(insn,reg,mem) | L: RRR@8, MMM@11, bit14, LLLL@16(4), bit22, ext; `enc_pm_l_abs` 41297d: LLLL@16, bit22, aa@8(6) |
| enc_pm_xr 412822(insn,xreg,xmem,s2,d2) | X:R class I `S1,X:ea S2,D2`: RRR, MMM, F(y_code d2)@16, d(s2)@17, ff(xx_code xreg)@18(2), bit20, ext |
| enc_pm_xr_w 412941 | W (X:ea -> reg); also used for `#xxxx,D` + Y-field forms (op mode 9 -> MMM=110 RRR=100) |
| enc_pm_xr2 412370(insn,acc,mem) | X:R class II `A,X:ea X0,A` / `B,Y:ea Y0,B`: RRR@8, MMM@11, S(mem)@15, d@16, bit19 |
| enc_pm_ry 4126b2(insn,s1,d1,yreg,ymem) | R:Y `S1,D1 S2,Y:ea`: RRR, MMM, bit14, ff(yy_code yreg)@16(2), e(x_code d1)@18, d(s1)@19, bit20, ext; `enc_pm_ry_w` 4127e6 = W |
| enc_pm_xy 4120db(insn,xreg,xmem,yreg,ymem) | XY: X RRR@8, X mm@11(2), Y rr@13(2) (reg&3), ff(yy)@16, ee(xx)@18, Y mm@20(2), bit23 |
| enc_pm_xy_wx 4122a4 / _wy 4122e0 / _wxy 41231c | bit15 (X read) / bit22 (Y read) / both |

---------------------------------------------------------------------------------------------------

## 4. procop.c - per-instruction processing

Purpose: `proc_instr` is the instruction entry point from `input.c:proc_line1/proc_line2` (pass 1 and
pass 2 both assemble fully); one handler per instruction class parses the operand field(s) with
`parse_operand`, performs DSP56000 restriction checks (REP, DO-loop end, pipeline, SSH/SP rules),
calls the encoders, and `proc_instr` then parses parallel moves (`do_xy`) and emits the words.

### 4.1 `int proc_instr(IENTRY *e)` @0x424bf0

1. `iclass = (signed char)e->f1`; emit width = 3 if `opt_lbx`(0x45eaa8) and the run/load
   counter *pointers* `rt_pc != ld_pc` differ, else 1 (passed to `obj_emit_word`).
2. `*rt_space != 0` (runtime space not P) -> err "Runtime space must be P", return 0 (nothing
   emitted).
3. `do_line_reset()`; `insn = {nwords 1, word0 f3, word1 0, cform NULL}`; `optr = Op1Field`;
   dispatch (table 1.1).
4. pmclass = `e->f2`, or (f2==2) the handler's return value (handler result then forced to 1).
5. pmclass 0: a non-empty `Op2Field` is an error ("Too many fields specified for instruction" +
   "Possible invalid white space...") except for movep (0x19) and tcc (0x26), which consume it
   themselves. pmclass!=0 and `Op2Field` empty: `word0 |= 0x200000`. Otherwise: `Op4Field`
   non-empty and not starting with `;` -> the same two errors (still continues); all four OPERANDs
   get space 4; `lst_xy_needs_swap()` before and after `do_xy(&insn, pmclass, &xs, &xd, &ys, &yd)`;
   movec (0x16) with `!CtrlRegAccessed` warns "No control registers accessed - using MOVE encoding";
   movem (0x18) with `xs.space!=P && xd.space!=P` warns "P space not accessed - using MOVE encoding".
6. `PrevInstrWords = insn.nwords`.
7. Unless `InMacroExpand` (DO-body replay) and not `InsertingNop`: DO bookkeeping (`DoStack` and not
   inserting: if ok and `HazardPrev & 0x100` -> `do_save_line(iclass)`; `do_stack_unwind(&insn)`);
   interrupt-vector warning ("Instruction cannot appear in interrupt vector locations", optr=mnemonic)
   if `VectorCheck && !AbsMode2 && *rt_pc < 0x40 && HazardCur & 0x200`; emit word0 (with cform0,
   freed); if 2 words: `HazardPrev & 1` -> err "Cannot repeat two-word instruction",
   `do_check_end_range_err(0)`, emit word1 (cform1); `opt_mu` -> `lst_mem_use_add(2, nwords)`;
   free the four operand cforms. **Emission ignores the handler result.**

Error field names: err() appends "(Opcode field)", "(Operand field)", "(X data move field)", "(Y data
move field)" according to which field `optr` points into; handlers therefore set
`optr = MnemField` before opcode-level checks and back to `Op1Field` afterwards.

"Field shift" idiom (p_noarg, p_rts, p_enddo, p_move, p_movep with empty X field): instructions
without an operand field have their X move in `Op1Field`, so `Op3=Op2; Op2=Op1; Op1=EmptyField("")`.

### 4.2 Hazard flags `HazardCur` (0x45ebb4, this line) / `HazardPrev` (0x45ebb8, previous line)

| bit | set by | tested by |
|-----|--------|-----------|
| 0x001 | REP | "Cannot repeat this instruction" (DO, ENDDO, REP, jumps, jbit, rti/rts, stop/wait/swi...), "Cannot repeat two-word instruction" |
| 0x004 | write to LA, LC, SSH, SSL, SP | DO: "Instruction cannot appear immediately after control register access" |
| 0x008 | write to SR, LA, LC, SSH, SSL, SP, MR (andi/ori) | ENDDO: same message |
| 0x010 | write to SP | "Move from SSH or SSL cannot follow update of SP", "Jump based on SSH or SSL cannot follow update of SP" |
| 0x040 | write to SSH, SSL, SP | RTS (0x40) and RTI (0xc0): same message as 0x004 |
| 0x080 | write to SR, CCR/MR (andi/ori) | RTI |
| 0x100 | DO pushed a loop | proc_instr -> do_save_line on the next line |
| 0x200 | any of the above control writes, DO, ENDDO, RTI/RTS | interrupt-vector warning |

Written by `note_ctrl_write(reg)` (0x42b12c): sr `|0x288`, la/lc `|0x20c`, ssh/ssl `|0x24c`, sp
`|0x25c`, each + `do_check_end_range_err(2)`; andi/ori: ccr `|0x280`, mr `|0x288` (+end range 2);
movep dest ctrl regs the same (+ source ssh `|0x24c`). With `OptRp` (and not replay/error line)
the "immediately after" conditions insert a NOP instead of erroring.

### 4.3 Handlers (operand classes = regclass/eaclass/absclass/immclass of `parse_operand`)

- **p_noarg** (0x425340): illegal: needs CpuVariant!=0; stop/wait/swi: HazardPrev&1 -> "Cannot
  repeat this instruction"; reset/stop/wait: `do_check_end_range_err(0)`; debug*: CpuVariant>=2.
  Field shift. Returns ok.
- **p_rts** (0x42546b): HazardCur|=0x200; REP check; prev control write check (0xc0 rti / 0x40 rts);
  end range 0; field shift.
- **p_andi** (0x425552): requires `#` ("Immediate operand required"); `#` imm class 3 (flags 5),
  dest reg class 0x13; ccr/mr hazards (4.2); `enc_andi`.
- **p_and_or** (0x42562d): `#` -> p_andi (result ignored, returns 0 => no parallel move); else word0 =
  0x46 (and) / 0x42 (or), S class 0xb, D class 0x18, `set_alu_reg` both; returns 1.
- **p_alu1** (0x4256e7) (inc/dec 2, abs.. 3, tst 0x27, logic 0x28): inc/dec need CpuVariant>=2;
  one operand, flags 2 (tst: 0), class 0x18 for 0x28 else 1; inc/dec: word0 |= (D!=a) bit0, others
  `set_alu_reg(2, D)`.
- **p_addl** (0x42578d): S class 1, D = the other accumulator (class 0xd/0xe); `set_alu_reg(2,D)`.
- **p_eor_adc** (0x4257f4): eor: S class 0xb, D class 0x18; adc/sbc: S class 10 (x,y), D class 1.
- **p_alu2** (0x425883) (cmp/cmpm 7, add/sub 0x22, tfr 0x23): S class 0x15 (add/sub) else 0xf;
  D: S==a -> class 0xe (b), S==b -> 0xd (a), else 1; dest flag 2 except cmp.
- **set_alu_reg(which, reg, &word)** (0x427d58): which==2 (dest): `|8` if b. Source: x 0x20, y 0x30,
  x0 0x40, y0 0x50, x1 0x60, y1 0x70, a/b: by `word&7`: 0,4 -> 0x10; 1,5,7 -> 0; 2,3,6 -> 0
  (JJJ of the manual). Others fatal "Register selection failure".
- **p_norm** (0x425945): Rn class 0x10 (flags 1), D class 1; own stall check on Rn (same rule as
  2.2, message "Contents of register written in previous instruction not available" or NOP);
  `enc_norm`.
- **p_lua** (0x425a05): ea class 3, D class 0x14; `enc_lua`.
- **p_div** (0x425a60): S class 0xb, D class 1; `enc_div`.
- **p_bitop** (0x425abb): `#n` imm class 4 (flags 5; on error `skip_symbol`), space via
  `get_mem_space(op, CpuVariant==0 ? 5 : 7)`; no space: reg class 0x11 (btst on ssh -> end range 2;
  bchg/bclr/bset -> `note_ctrl_write`) -> `enc_bit_reg`; memory: ea 1 / abs 6 (failure sets
  nwords 1 or 2 by force to keep addresses in sync); modes 7,8,14 +2 cycles -> `enc_bit_ea`; 16 ->
  `enc_bit_abs`; 17 -> `enc_bit_pp`.
- **p_do** (0x425d15): HazardCur|=0x200, REP/0x004 checks, end range 2, nwords=2; space
  (`get_mem_space` 7): none -> reg class 0x11 or imm class 2 (flags 1); `ssh` -> "Illegal use of SSH
  as loop count operand"; memory -> ea 1 / abs 4. Target: abs class 1 (flags 4), MSW warning.
  Encoders `enc_do_imm/reg/abs/ea`. Pass 2 (not replay): target section `op.sect` must equal
  `cur_section+8` ("DO loop address must be in current section"); `*rt_pc+1 < LA` else
  "Negative or empty DO loop not allowed"; push DoStack node unless `LA >= top->la` (warn "Improper
  nesting of DO loops", returns 0); HazardCur |= 0x100.
- **p_enddo** (0x426106): warn "ENDDO instruction not inside DO loop" if DoStack empty; REP and
  0x008 checks; field shift.
- **p_rep** (0x4261da): HazardCur|=1; REP check; end range 0; like DO's source (reg 0x11 / imm 2 /
  ea 1 / abs 4) -> `enc_loop_reg/imm/abs/ea` (no target).
- **p_jmp** (0x426305) (jcc 0xe, jmp 0x13) and **p_jsr** (0x42666f) (jscc 0x10, jsr 0x12, flags 4):
  end range 0, REP check; target ea 1 / abs 5 / reg class 0x10 (bare `Rn` becomes `(Rn)` mode 2 with
  a stall check; verified `jmp r0` = `0AE080`). Modes 14/15 go through SDI (`sdi.c`): `SdiHandle =
  sdi_operand(text)`; none -> short `enc_*_abs` or long (+2 cycles) `enc_*_ea`; pass 1 ->
  `sdi_record(h, 0xc, 0, 2)`; pass 2 without cform -> `sdi_next_form()` picks long/short; with
  cform -> both forms encoded into `insn` and a copy, `sdi_expr(sdi_local_target ? op.cform-copy :
  h, 2, 0xc, 0, &insn, &copy)`, nwords=1. Modes 7,8 +2 cycles. jsr/jscc in pass 2: target ==
  `DoStack->la` -> "Subroutine jump to loop address not allowed". Parse failure: nwords =
  (force!=short)+1.
- **p_jbit** (0x426a45) (0xf, 0x11): REP check (clears HazardPrev bit), nwords=2, `#n` imm 4, space
  as p_bitop; reg 0x11 (ssh end range 2) or ea 1 / abs 7; target abs 1 (flags 4); jsclr/jsset loop
  address error; ssh/ssl vs SP check; `enc_jbit_reg/abs/pp/ea` (ea modes 7,8 +2).
- **p_tcc** (0x426dc3): S class 0xf, D (other acc / class 1); no X field -> `enc_tcc`; else X field
  `Rs,Rd` (class 0x10 both) -> `enc_tcc_r`.
- **p_mul** (0x426ee5): optional `+`/`-` (bit 2 = negate); S1 class 0xb, S2 class 0xb or `#n` imm 4
  (flags 5), D class 1. Register S2: `mulreg` + return 1. Immediate (DSP56002 `mpy/mac(r) S,#n,D`):
  word0 = 0x100c2 mac / 0x100c0 mpy / 0x100c3 macr / 0x100c1 mpyr, `enc_mul_imm`, return 0 (no
  parallel moves; verified `mac y1,#3,b` = `0103CA`). Non-constant shift without relocation ->
  "Invalid shift amount".
- **mulreg(s1,s2,d,&word)** (0x427e5d): QQQ: x0x0 0, y0y0 0x10, x1x0 0x20, y1y0 0x30, x0y1 0x40,
  y0x0 0x50, x1y0 0x60, y1x1 0x70 (both orders), `|8` for b; "Invalid register combination".
- **p_move** (0x4270d6): Y field must be empty (`check_extra_operand`), field shift, then "Not enough
  fields specified for instruction" if nothing.
- **p_movep** (0x42712b): operands are in the X field (shifted); spaces: P -> ea 1/abs 1; none ->
  reg 0x11 or imm 1; X/Y -> ea 1 / abs 8. At least one X/Y side ("Either source or destination
  memory space must be X or Y"). Decides which side is the peripheral (mode 17): both forced/abs ->
  "Cannot force short addressing for source and destination" (warn); neither I/O -> choose by value
  (0xffc0..0xffff, or 0x40..0x7f with warnings "Source/Destination operand assumed I/O short");
  errors use the message chosen per space combination ("I/O short addressing must be used for
  source/destination operand" / "... either source or destination"). Hazards for ctrl regs as 4.2;
  DoStack with ssh/ctrl dest -> end range 2; CpuVariant>1 and dest r/n/m: `AregWritten=0`. Cycles
  only if `OptCc`: P side +2; reg side (not imm) and CpuVariant>1 and a reg in ids 2..12: -2; pp
  source with dest mode 7/8/14 +2; pp dest with source 7/8/14 +2, source imm +2 if CpuVariant<2.
  nwords 2 if a long imm/abs is involved. Encoders: pp source -> `enc_movep_reg` (dest reg) /
  `enc_movep_mem`; pp dest -> `enc_movep_reg_w` / `enc_movep_mem_w`. Non-empty X field after the
  shift check -> "Too many fields..." pair.

### 4.4 object.c tail living in procop.c's address range (0x42420d..0x424b1a)

- `obj_add_reloc(expr)`: absolute mode -> fatal "Attempt to write relocation entry in absolute mode";
  pass 2 with object file: append `{*ld_pc, strtab_add(expr), 0}` (12 bytes) to `Reloc_buf`
  (grows +0x1000 then x2 up to 0x40000 then +0x40000 entries), bumps section's reloc count
  (`*(ld_counter_obj+0x24)+0x28`); returns index (`Reloc_count++`).
- `obj_add_lineno(line)`: line 0 -> `{Symtab_count, ?, 0}` (function start) else `{*rt_pc, rt_map,
  line}`; pass-1 bumps section `+0x2c`; `File_scope_flags++`; returns index.
- `obj_add_symrec(rec)` (not with OptZ): copies 0x20-byte COFF symbol into `Symtab_buf`, returns index.
- `strtab_add(s)`: dedups via `strtab_lookup`/hash (`strtab_hash` 0x462c18, `strtab_insert_pt`),
  returns offset; grows the string table the same way; OptZ -> 0.
- `obj_cmt_sym(text,value)`: pass <2 counts `sec+0x20`; else stages `.cmt` symbol (name offset of
  text, sclass 4, value). `obj_sdi_sym(idx)`: `.sdi` symbol, value idx, section, type 0x81.
- `obj_emit_sym(sym)` (from `sym_define`): flushes a pending DEF record attached at sym+0x54/0x58,
  then builds the COFF symbol (name inline <8 chars else string offset; value/section from sym+0x10,
  sym+0xc; storage class 0xd5/0xd6/0xd7 local/global.., 0xd2/0x2 for sections by OptC, 0xd3; aux
  entry when needed). `obj_emit_ext_sym(ext)` (from `ext_add`): same for an external.
  (Details belong to g6/object.c.)

---------------------------------------------------------------------------------------------------

## 5. procxy.c - parallel data moves (X field / Y field)

Purpose: classify the X field (`Op2Field`) and optional Y field (`Op3Field`) of a data-ALU or MOVE
instruction into one of the DSP56000 parallel move types and encode it into bits 8..23 (or the
MOVEC/MOVEM formats). Always call pattern `handler(pmclass, insn, xs, xd, ys, yd)`.

- **chk_move_class(pmclass, mask, insn)** (0x42b1e5): `pmclass & mask` must be non-zero else err
  "Instruction does not allow data movement specified" (0). With `insn`: pmclass&0x10 -> word0 =
  0x40000 (MOVEC base), else pmclass&0x20 -> word0 = 0x70000 (MOVEM base) - i.e. **plain MOVE with
  a control/m register or P: operand is silently re-encoded as MOVEC/MOVEM** (`move m0,x0` ->
  `0444A0`, verified). Masks used: 0x11 (data move, also OK for MOVE), 0x01 (data-ALU only: Y field
  forms, L:, X:R, U), 0x10 (control-register forms), 0x20 (P: forms).
- **do_xy** (0x428040): `optr = Op2Field`; `get_mem_space(xs, 6)`. If no space: `parse_xfield_src`
  (reg 0x12 / ea 1 / abs 6 / imm 6); U move (modes 3..6 alone): Y field must be empty ->
  `enc_pm_update`; other memory modes without space -> "Missing memory space specifier" (nwords=2);
  imm short (11) -> `xy_imm_short`; imm long (9) -> `xy_imm_long`; register by id: x y ab ba a10 b10
  -> `xy_lreg`; a b -> `xy_acc`; x0 x1 -> `xy_xreg`; y0 y1 a0..b2 r n -> `xy_reg`; m0-m7 ->
  `xy_mreg`; omr..sp -> `xy_ctlreg`. Memory source: `parse_operand(1, xs, 0, 1, 9, 0)` then by
  space P -> `xy_psrc`, X -> `xy_xsrc`, Y -> `xy_ysrc`, L -> `xy_lsrc` (fatal "do_xy memory space
  select failure"). Parse failure: nwords = (force!=short)+1.
- **xy_imm_short** (0x42838d) / **xy_imm_long** (0x42859c): dest reg class 0x12 (flags 2); a,b,x0,x1
  with Y field: X:R form with `#` as long immediate (`xs.mode=9`, +2 cycles, warn "Cannot force short
  immediate with this parallel move" if forced) -> `enc_pm_xr_w` (Y field `S2,D2` classes 1 / 2);
  without Y field: short -> `enc_pm_imm`, long -> `enc_pm_x_ea_w` (X:#). Data/address regs: same
  without Y. m regs / control regs (`note_ctrl_write` for sr..sp): MOVEC `enc_movec_imm` (short) /
  `enc_movec_ea2_w`/`enc_movec_ea_w` (long). Long always +2 cycles.
- **xy_lreg** (0x4287cc) ("p_xyabba"): L move from register: dest `get_mem_space(xd,3)` (L only),
  ea 1 / abs 9; `enc_pm_l_ea` / `enc_pm_l_abs` (modes 7,8,14 +2). fatal "p_xyabba failure".
- **xy_acc** (0x4288fe) (source a/b): memory dest -> `xdst_mem`; reg dest: data/address regs ->
  `enc_pm_reg`; x0/x1 dest with Y field -> R:Y (`S1,D1 Y:ea,D2` or `S1,D1 S2,Y:ea`, Y-side space
  class 8, reg classes 4/imm long, `enc_pm_ry`/`enc_pm_ry_w`, extra +2 for modes 7,8,14 or long
  imm); m/control dest -> MOVEC `enc_movec_reg_w`.
- **xy_xreg** (0x428cce) (source x0/x1): mem dest -> `xdst_mem`; reg -> `enc_pm_reg` / MOVEC.
- **xdst_mem** (0x428e50) (register -> X:/Y: memory, with optional Y field): X: dest with modes 2..5
  and a Y field: Y-side source class `CpuVariant==0 ? 4 : 0x17`; Y-side register a/b ->
  `enc_pm_xr` (Y field `S2,D2`) or XY (`enc_pm_xy`, after `chk_xy_regs`) when the Y operand has
  space; x0 (id 4) -> X:R class II `enc_pm_xr2` (only with S1 a/b; "Invalid addressing mode");
  y0/y1 -> XY. Modes 6,7,8 (+2 for 7,8): Y class `CpuVariant==0 ? 1 : 0x16` -> `enc_pm_xr` or
  `enc_pm_xr2`. Mode 14 (+2): X:R only. Mode 16 without Y field: `enc_pm_x_abs`; with Y field it is
  converted to long (+2, warn "Short absolute address cannot be forced - long substituted") and
  X:R. Without Y field: `enc_pm_x_ea`. Y: dest: `enc_pm_y_ea`/`enc_pm_y_abs` and the fields are
  shifted (Y field consumed). L: -> `enc_pm_l_*`; P: -> `xy_pdst`; else "Illegal X field destination
  specified". fatal "xdst_mem failure".
- **xy_reg** (0x429729) (other data/address regs): reg dest -> `enc_pm_reg` / MOVEC (`enc_movec_reg_w`);
  a/b dest with Y field only on CpuVariant!=0 and source y0 (`xy` class II form `Y0,A A,Y:ea`) ->
  `enc_pm_xr2`, else "Invalid addressing mode"; X:/Y: dest -> `enc_pm_x/y_ea` / `_abs`; P: -> `xy_pdst`.
- **xy_mreg** (0x429b8a) / **xy_ctlreg** (0x429d39) (m regs / omr..sp source): MOVEC only (mask
  0x10): reg dest `enc_movec_reg`, X:/Y: `enc_movec_abs` / `enc_movec_ea(2)`, P: `xy_pdst`.
  ctlreg: ssh source -> HazardCur|=0x24c + end range 2, la -> end range 1 (result ignored),
  ssh/ssl after SP write -> error/NOP, "SSH cannot be both source and destination register".
- **xy_pdst** (0x429fb4) (register -> P: memory, MOVEM mask 0x20): ea 1 / abs 9; +4 cycles (+6 for
  modes 7,8,14); `enc_movem_abs` / `enc_movem_ea`.
- **xy_xsrc** (0x42a096) (X: memory source): modes 2..5: dest `get_mem_space(xd,0)` (must be none),
  reg class 0x12: a,b,x0,x1 -> `xy_xsrc_acc` (Y field -> X:R or XY), r/n/data regs -> `enc_pm_x_ea_w`
  (warn "Post-update operation will not occur on destination register" when dest Rn == the ea's Rn
  and mode != 2), m regs -> `enc_movec_ea2_w`, control regs -> `note_ctrl_write` + `enc_movec_ea_w`.
  Modes 6,7,8,14 (+2 for 7,8,14): same, Y field -> X:R (`enc_pm_xr_w`) only; post-update warning
  only for mode 6. Mode 16: `enc_pm_x_abs_w` / MOVEC `enc_movec_abs_w`; with Y field converted to
  long (+2, warning) and X:R.
- **xy_xsrc_acc** (0x42a7d2): no Y field -> `enc_pm_x_ea_w`; Y field (mask 1): Y-side reg class 4 ->
  a/b: next operand Y: mem (XY, `chk_xy_regs`, `enc_pm_xy_wx`) or reg class 2 (`enc_pm_xr_w`);
  y0/y1: XY; Y-side memory source -> `enc_pm_xy_wy`/`_wxy` after `chk_xy_regs`.
- **xy_ysrc** (0x42aa80) / **xy_lsrc** (0x42adb6) / **xy_psrc** (0x42ae87): analogous for Y:
  (`enc_pm_y_*_w`, MOVEC variants, XY via Y source), L: (dest reg class 5, `enc_pm_l_*_w`) and P:
  (MOVEM `enc_movem_*_w`, +4 / +6 cycles; quirk: for P: source modes other than 2..8,14,16 the
  function skips parsing the destination but still adds 4 cycles and returns 1).
- **chk_xy_regs(xreg, yreg)** (0x42b08d): both Rn in r0-r3 or both in r4-r7 -> err "Invalid XY address
  register specification" (returns 1). (The encoder stores Y's `reg&3`; the bank is implicit.)
- **note_ctrl_write(reg)** (0x42b12c): 4.2; returns 0 if the DO-end check failed (callers ignore it).

Errors in this module mostly: "Illegal X field destination register specified", "Illegal X field
destination specified" (wrong memory space), "Invalid addressing mode", "Missing memory space
specifier". Verified examples (t.lst, t3.lst): `a,x:(r0)+ x0,a` -> 081800 (X:R II),
`x:(r0)+,x0 a,y0` -> 109800 (X:R I), `x:(r0)+,x0 y:(r4)+,y0` -> F09800 (XY), `x0,x:(r0)+ a,y0`
-> 101800, `l:(r0)+,ab` -> 4AD800, `(r0)+` -> 205800, `x:(r0)+,x0 y:(r0)+,y0` -> XY bank error
(word 000000 emitted).

---------------------------------------------------------------------------------------------------

## 6. Globals

| addr | name | type | meaning / writers-readers |
|------|------|------|---------------------------|
| 0x44e0b0 / 0x44ebc8 | InstrTab / InstrTabCount | IENTRY[142] / long | 1.1 (mchglb) |
| 0x44ece8 | RegNameTab | char *[51] | 1.2 (mchglb); g1's 0x44ed44 = &RegNameTab[23] |
| 0x45f860 | optr | char * | scan pointer into the current field; set by handlers, advanced by parsers; err() derives the field name from it |
| 0x44f814..0x44f824 | MnemField, Op1Field, Op2Field (X move), Op3Field (Y move), Op4Field | char * | line fields from `parse_line`; shifted by handlers |
| 0x45ec04 | EmptyField | char[] "" | target of field shifts |
| 0x44f9fc | CpuVariant | long | 1.1; set by pseudo.c -p/-r handling, default 0x1fff |
| 0x44f95c | PrevInstrWords | long | written by proc_instr, used by stall checks; saved/restored around DO replay and NOP insertion |
| 0x45ebb4 / 0x45ebb8 | HazardCur / HazardPrev | ulong | 4.2; rotated by `do_line_reset` |
| 0x45f93c | DestRegMask | ulong | accumulator-part destinations of this line (dup check) |
| 0x45f940 / 0x45f944 | AregWritten / AregWrittenPrev | ulong | bit r0-7 (0-7), n0-7 (8-15), m0-7 (16-23) written |
| 0x45f948 | LastSrcReg | long | last register-direct source (a register moved onto itself does not count as written) |
| 0x45f94c | AregWritePc | ulong | `*rt_pc` when AregWritten was set |
| 0x45ea5c | CtrlRegAccessed | char | m/ctrl register seen (MOVEC warning) |
| 0x45eac8 | OptRp | char | OPT RP: insert NOPs for pipeline hazards (`set_opt_rp`) |
| 0x45eacc | InsertingNop | char | set by listing.c while re-assembling the inserted `\tnop` |
| 0x45eb8c | RpLocked | long | set by dspasm (option 'w' path); blocks `set_opt_rp` (low confidence) |
| 0x45ead4 | OptSi | char | OPT SI/NOSI (ids 0x3b/0x3c): short immediates stay integer (see 2.1 class 6) |
| 0x45ea38 | OptCc | char | OPT CC/NOCC (ids 1/0xa; id 1 also zeroes CycleTotal); listing prints `[%1d - %8ld]`. **g5 named it `opt_gen` - wrong** |
| 0x45f928 | CycleCount | long | cycles of current instruction (init f4). **g-listing named it `Dup_from` - wrong** |
| 0x45f930 | CycleTotal | long | running total. **other names `ccc_value`/`opt_macx_flag`/`Dup_to` are wrong** |
| 0x45ea90 | VectorCheck | char | interrupt-vector area checks enabled (dspasm init) |
| 0x44f924 | VectorAreaSize | ulong | 0x40 |
| 0x45f868 | SdiHandle | char * | result of `sdi_operand` for the current jump |

Read-only uses from other modules: `Pass` 0x45f8fc, `rt_pc` 0x45f8c0 / `ld_pc` 0x45f8cc (pointers to
counters), `rt_space` 0x45f8a0, `cur_section` 0x44f978, `rt_addr_mask` 0x44f91c, `OptMsw` 0x44f7a4,
`AbsMode` 0x44f790 / `AbsMode2` 0x44f794, `InMacroExpand` 0x45ea70 (really "DO-body replay in
progress"), `ErrOnThisLine` 0x45eb98, `no_errors` 0x45ea50, `DoStack` 0x45fc30, `opt_mu` 0x45ea10,
`opt_lbx` 0x45eaa8, `sdi_local_target` 0x45eb38, `LineBuf` 0x45f220 (sprintf scratch).

## 7. Cross-module interfaces used

util.c: `get_mem_space`, `get_force`, `merge_mem_space`, `insert_bits`, `insert_bits_expr`,
`encode_field`, `check_extra_operand` (Y field must be empty, else "Too many fields" pair),
`skip_symbol`, `str_upper`, `xmalloc/xfree/xrealloc`, `mem_space_index`. arith.c:
`match_register_name`, `fmt_storage_directive_text` (cform), `float_to_fixed_frac`. eval.c:
`expr_to_int24`, `expr_to_uint_bits`, `free_expr`. error.c: `err`, `err_s`, `warn`, `fatal`.
input.c: `do_line_reset`, `do_save_line`, `do_stack_unwind`, `do_check_end_range_err`.
listing.c: `lst_xy_needs_swap`, `FUN_0041bbb2` (NOP insertion), `lst_mem_use_add`. object.c:
`obj_emit_word`. sdi.c: `sdi_operand`, `sdi_record`, `sdi_next_form`, `sdi_expr`. Callers of
this group: input.c `proc_line1/2` -> `proc_instr`; scs.c uses `parse_operand`/`get_amode`.

## 8. Quirks to reproduce

1. Listing date prints `tm_year` raw (`126-09-28`), from `get_date_time`.
2. Object words are emitted even when the handler reported an error (template bits + whatever was
   encoded); only pmclass/f2==2 handlers also turn their failure into "no parallel move allowed".
3. MOVE with control/m registers or P: silently uses MOVEC/MOVEM encodings; the MOVEC/MOVEM
   mnemonics warn when no control register / no P space is involved.
4. `#n` bit numbers accept 0..23 (`>0x17` error), `a1`/`b1` accepted as `a`/`b` for logical ops.
5. Fractional short-immediate rule (2.1 class 6) depends on the Y field being empty.
6. `(Rn)+N` / `(Rn)-N` shorthand accepted; `(Rn+Nn)` offset errors do not abort parsing.
7. `enc_jmp_abs`/`enc_jcc_abs` and `enc_movec_ea`/`enc_movec_ea2` are byte-identical duplicates.
8. xy_psrc's odd default path (5.) and `set_alu_reg`'s dependence on the template's low 3 bits.
9. p_movep's cycle arithmetic only under OptCc, other handlers adjust CycleCount always.

## 9. Open questions

- `RpLocked` (0x45eb8c): exact option ('w'?) that sets it.
- Regclass 8 (m0/m1 only) and immclass 5 (signed 5-bit) are not used by these modules (maybe by
  scs.c 0x4312d0/0x4324d9/0x432d3b/0x4330dd, not checked).
- `listing.c` 0x45f92c (second cycle term printed as `[%1d+%1d - %6ld]`) is never set here.
- MOVEP's peripheral-side selection has many branches (0x42712b l.1960-2230 of the decompilation);
  described by rule above, translate literally from the decompilation.
