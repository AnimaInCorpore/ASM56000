# SIM56000 group devinit_asm: devinit, asm, asmtab (0x41c140-0x433fff)

Names/prototypes: `re/names/SIM56000/devinit_asm.names.txt` (303 functions of functions.txt, 156 extra
"hidden" handlers, 80 globals). All addresses are VAs in `re/bin/SIM56000.EXE`.

## 0. Summary and corrected module boundaries

The filemap labels (devinit = device tables, asm = inline assembler, asmtab = field encoders/tables) are
only partly right. What the code really is:

| range | real content | source origin |
|-------|--------------|---------------|
| 0x41c140-0x41c43f | device registry: `device_install` (DEVICE DVn type [key]) + licence-key generator | new (sim) |
| 0x41c750-0x41cd7f | per-instruction statistics record helpers (`insn_stat_*`), `eval_cc`, `mnemonic_name` | sim |
| 0x41cfb0-0x41f9df | **instruction word decoder** (opcode word -> decoded record `DEC`), 110 handlers | sim |
| 0x41f9e0-0x41fb6f | `decode_insn` driver, `dec_init` | sim |
| 0x41fb70-0x423b0f | **disassembler formatters**, one per opcode class (produce token lists) | sim |
| 0x423b10-0x424190 | `disassemble` (token list -> text), effective-address calculator for the display | sim |
| 0x4240d0-0x42c470 | **inline assembler** (`asm_line`, `proc_instr`, operand parser, move-field encoders, `enc_*`, `*_code`) | **same source as ASM56000 amode.c/encode.c/procop.c/procxy.c** (different revision) |
| 0x42c4c0-0x42e370 | memory/register access engine: `mem_reg_read/write`, region lookup, per-device OMR remap hooks | sim |
| 0x42eec0-0x430850 | per-instruction attribute lookups (timing/class/EA-class/validate) used by the fetch stage 0x405000 | sim |
| 0x430850-0x433c80 | 56-bit ALU primitives + ALU op handlers (`alu_add56`, `alu_mpy`, `alu_mac`, ...) | sim (exec helper) |
| 0x433c80-0x433fff | ALU dispatch, peripheral reset/call/name lookup | sim |

Boundary corrections: devinit.c really ends at 0x424100 (asm.c starts with `bitrev16` 0x4240d0, though
the mod file starts there already). The "asmtab" module is NOT an assembler table module: the assembler
ends at 0x42c470 (`qq_code`, the last encoder); 0x42c4c0-0x433fff is the core memory/ALU engine.
The Ghidra export is **missing ~156 handlers** that are only reachable through data tables (decode
table 0x4c02b0, formatter table 0x4c1298 and the exec/move/class/validate/alu tables); their code lives in
gaps between the listed functions (0x41ce50-0x41f960, 0x41fd70-0x423b00, 0x42d460, 0x42e160, 0x42e370,
0x42e5c0-0x42e900, 0x42f4a0-0x42f9xx, 0x42fe60-0x4300xx, 0x430880-0x433650 ...). The names file gives
"hidden" rows (address not in functions.txt) for the decode, formatter and vtable handlers; the
exec/move/class/valid/alu handler tables are listed in appendix C only (addresses, no bodies).

## 1. Device tables (what is in `.data`, no code)

### 1.1 Device registry (0x41c140 `device_install`)
* `dev_table` @0x4aab08 -> array `DEV *[13]` at 0x4aaac8 (`max_devices` @0x4aab04 = 13). The first 10 slots
  are filled statically: 56000, 56001, 56002, 56004, 56004rom, 56005, 56007, 56009, 56011, 56012.
  Slots 10-12 are empty and get filled at run time.
* `keyed_dev_table` @0x4bf760: 2 entries x 16 bytes `{DEV *dev; char key[12]}` = `68356` (dev 0x4bcef8) and
  `56030` (dev 0x4be8e0): these two devices only work if the user supplies a matching key.
  The parallel array `keyed_dev_aux` @0x4bf758 (0x4bf708, 0x4bf730) and `dev_aux_table` @0x4a8db4
  (array at 0x4a8d50, capacity 0x15) receive a per-device companion pointer.
* `device_install(name, key)` (called from cmd DEVICE handler 0x435ce0): (1) search `dev_table` for `name`
  (wide compare loop, returns index if found); (2) if the table is full return -1; (3) look name up in
  `keyed_dev_table`; (4) call `device_keygen(name)` -> 8 lower-case alnum chars (NUL terminated at `keygen_out[8]`) and compare **9 bytes** (`for i=0..8: key[i]==gen[i]`, verified in disassembly 0x41c22d-0x41c239, so the supplied key must be exactly the 8 generated characters, case-sensitive); returns -1 on mismatch; (5) `dev_table[first free] = dev`, copy key text to
  `keyed_dev_table[i].key`, `dev->key_ptr(+0x4dc) = that text`, `dev_aux_table[idx] = aux[i]`.
  Returns the slot index.
* `device_keygen` (0x41c2c0): seed `keygen_seed = 0x12d715 + sum(tolower(c) << ((5*i) % 23))` with a
  linear-congruential step: `keygen_step`: `seed = (mulmod(seed, keygen_mult) + 1) % keygen_mod`,
  constants `keygen_mod` 100000000 (0x5f5e100, @0x4bf780), `keygen_base` 10000 (@0x4bf784), `keygen_mult` 0x1df5e0d (@0x4bf788).
  `mulmod(a,b) = (((a/B)*(b%B) + (b/B)*(a%B)) % B * B + (b%B)*(a%B)) % M` (B=base, M=mod; avoids 32-bit overflow).
  Per input char: `x ^= keygen_step()`; after the loop `x >>= 8`; then 8 output chars, each: loop
  `c = ((x ^ (step()>>8) ^ (step()>>8)) & 0x7f)` until `isalnum-ish` (`_isctype(c,0x107)` = alpha|digit),
  `tolower`, store, `x >>= 1`. Output in `keygen_out` @0x4dbdc8 (9 bytes). (Uses locale-dependent ctype in MSVC;
  C89 `isalnum`/`tolower` reproduce it in the "C" locale.)

### 1.2 DEV descriptor (one per device type; size 0x4e0, e.g. 56000 @0x4a4298, 56001 @0x4a4788, 56002 @0x4a3da8,
56004 @0x4a4c78, 56004rom @0x4a5168, 56005 @0x4a5658, 56007 @0x4a24f8, 56009 @0x4a33c8, 56011 @0x4a29e8,
56012 @0x4a2ed8, 68356 @0x4bcef8, 56030 @0x4be8e0)
Global pointer `cur_dev` @0x505790 = active DEV, `cur_devstate` @0x505798 = active DEVSTATE (see 1.4).

| off | field | evidence / values |
|-----|-------|-------------------|
| +0x00 | `char *name` | "56000" ... (strings 0x4a8298 etc.) |
| +0x04 | 0x2c5 (all devices) | unknown constant (version?) |
| +0x08 | `flags` = **family bit mask** | 56000=0x1, 56001=0x2, 56002=0x4, 56004=0x8, 56004rom=0x108, 56005=0x44, 56007=0x200, 56009=0x400, 56011=0x1000, 56012=0x2000, 68356=0x80, 56030=0x800. Tested everywhere (`& 0x3400`, `& 0x210`, `< 4` = "56000/56001 class", `dev->flags` passed as `cpu` to the opcode tables) |
| +0x0c | 0x04000008 (all) | unknown |
| +0x10 | 2 (56000, 56001, 56005, 68356, 56030) or 0 | unknown (number of core regs sets?) |
| +0x14 | `n_periph` | 7,7,8,6,6,10,6,6,8,8 (56000...56012), 7 (68356), 9 (56030) |
| +0x18 | `PERIPH *periph` (array, stride 0x48) | 56000: 0x495c98 (core, host, ssi, sci, portb ...) |
| +0x1c | `n_map` = number of memory-map entries | 0xf, 0x10, 0x11, 0x52 (56004), 0xa9 (56007/56009), 0x19/0x18 ... |
| +0x20 | `MAPENT *map` (array, stride 0x2c) | 56000: 0x49efd0; used by `mem_reg_read` (`map + idx*0x2c`: +0xc start addr, +0x10 end addr, +0x18 flags, 0x10000 = peripheral-backed) |
| +0x24 | `char *"DSPMEM"` (0x4a82c8) | name of the memory module |
| +0x28 | `void **vtable` = `core_vtable_*` | 0x4c2ab0 (56000, 56001, 56002, 56004, 56005, 56007, 68356, 56030), 0x4c2af0 (56009), 0x4c2b30 (56011), 0x4c2b70 (56012); see 1.5 |
| +0x2c | 0x1d (all) | number of memory-space ids? (first register id is 0x1d) |
| +0x30 | 5,5,6,7,7,6,7,7,7,7 / 6 / 7 | unknown (number of ...); differs between devices |
| +0x34 | pointer to a small table (56000 @0x4a0e98) `{0x1040f, 0x1040f, 0x6f800, 0x40000, 0...}` | bit masks per memory space (likely address-space size/OMR masks) |
| +0x4dc | `char *key` | set by `device_install` (keyed devices) else 0 |

`PERIPH` (0x48 bytes): `+0 name` ("core","host","ssi","sci","portb","pcc?"...), `+4 kind` (0 core, 2 host/port, 3 ssi/sci),
`+8 mask`, `+0x14 io base`, `+0x18/+0x1c/+0x20` per-peripheral register window info (ssi: 0x1f8, 0xffec, 0xc),
`+0x28 nreg`, `+0x2c PERIPHDESC *` (`+0x28 count`, `+0x2c` array of 7-dword register records whose first dword is the
register name, e.g. "ctrl","porta","addr" - used by `periph_find_reg` 0x433f60), `+0x30 char *` (empty-string
enable flag, 0x4db080). Interrupt vector name tables (e.g. 0x498a18 `{"reset", ..., "modc","nmi", "modb","irqb", "moda","irqa"}`,
records of 5 dwords: name1, name2, ?, ?, ?, ?) hang off the DEV via the pointer at +0x18's first element.

`MAPENT` (0x2c bytes, sample 56000 map at 0x49efd0 has 0xf entries: "pi", "pe", "xi", ... ):
`+0 name*`, `+4 ?`, `+8 kind flags` (0x8c300000, 0x80200000 ...), `+0xc start`, `+0x10 end` (0xffff / 0xeff), `+0x14 ?`,
`+0x18 flags` (0x201000, 0x607008 ...; 0x10000 = peripheral mapped), `+0x1c ?`, `+0x20 size-1`, `+0x24 0x04000001`, `+0x28 1`.
(Only start/end/flags are used by the code read here; the rest is unverified.)

### 1.3 Memory space / region ids (used by `mem_reg_read/write`, `mem_region_of`)
`id < 0x1d`: memory spaces/regions: 0/1/2 = P/X/Y logical space (`0` and `4` are treated alike = P), 3 = X and Y pair, 9 = P+X pair?,
10 = L pair; concrete region classes returned by `mem_region_of`: 0xd (P internal RAM/pm), 0xe (P ROM/boot? ), 0xf (P external),
0x12 (X internal), 0x13 (X ROM / peripherals), 0x14 (X external), 0x17 (Y internal), 0x18 (Y ROM), 0x19 (Y external), 0x1c = memory-mapped register bank via
`FUN_00458280`, 0x11d = special (register 0x11d handled like region 0x12/0xd).
`id >= 0x1d` (up to 0x11c): register ids: `id-0x1d` low bit = high/low half, bit6 = "pair" form, bit7 = 'split register' (2 or 4 parts),
tables at 0x4c2930/0x4c2950/0x4c2960/0x4c2970 give per-register width/mask; `reg_field_pack` (0x42c7f0) converts the raw value to the 24-bit
part stored in the register file (A/B are three 8/24/24-bit parts: sign extension via tables 0x4c28e0-0x4c2928, masks at 0x4c2a80/84/88).

### 1.4 DEVSTATE (one per DVn, array `dev_state_table` @0x4aab10 -> 0x4dbb08, 32 entries max)
`+0 device index` (into `dev_table`), `+4 register-file handle` (passed to `FUN_00458280(regfile, id, value, &out, ...)`),
`+0xc MEMBLK *` (array stride 0x10: `+8 data pointer (long*)`, `+0xc enabled flag` - the OMR remap hooks flip these to alias memory blocks),
`+0x18 -> struct` with `+0x4a0` (peripheral-window size?), `+0x1c` = current PC copy (fetch stage), `+0x44` = status bits (bit 2 set when
`insn_validate` != 0). Peripheral instance array is addressed through `DAT_0050578c` (`cur_devaux`; `+4` = instance array, stride 0x12c bytes,
`+8` = per-peripheral register bit arrays, `+0x24` counter).

### 1.5 Core vtables (`DEV+0x28`)
7 slots (0x4c2ab0 etc.), slot semantics from callers:
0 `mem_reg_read(id, addr, &out)` (0x42c4c0), 1 `mem_reg_write(id, addr, val)` (0x42da70), 2 `mem_write_n` (0x42d460: repeats slot-1 write `count` times, element size from table 0x4c2a1c), 3 `mem_region_of(space, addr)` (0x42d4c0),
4 mode-change hook `omr_remap_*` (called from 0x405440 when OMR changes; `NULL` for 56000/56001/56002/56004/...; 56009 -> 0x42dd70, 56011 -> 0x42dec0, 56012 -> 0x42e010),
5 `reg_write_check` (0x42e160), 6 `reg_read_check` (0x42e370). The hooks set flags `MEMBLK.enabled` for blocks 0xe/0x13/0x18 at 0x000/0x100-0x200/0x400-0x800 depending on OMR bits 0x13, 8, 4 (ROM/RAM aliasing per mode).

## 2. devinit.c: instruction decoder

### 2.1 Decoded instruction record `DEC` (0xb8+ bytes, ints; `dec_init` 0x41fab0 clears it from template 0x492000 (5 dwords) x 8)
```
dec[0]  = mnemonic id (index into mnemonic_names[0x67], see 2.3), 0 = "none"   ; +0x00
dec[1]  = 0xd / 0xe  cc-form marker ("if"/"ifu" style?)                          ; +0x04
dec[2..6]   OPERAND 0   ; dec+0x08    OPERAND = 5 dwords {kind, value, aux1, aux2, aux3}
dec[7..11]  OPERAND 1   ; dec+0x1c
dec[12..16] OPERAND 2   ; dec+0x30
dec[17..21] OPERAND 3   ; dec+0x44
dec[22..26] MOVE slot 0 ; dec+0x58    (parallel-move operands: source/dest of the two moves)
dec[27..31] MOVE slot 1 ; dec+0x6c
dec[32..36] MOVE slot 2 ; dec+0x80
dec[37..41] MOVE slot 3 ; dec+0x94
dec[0x2a]  = auxiliary field (cc number, shift amount, bit position) initial 0x10 ; dec+0xa8
dec[0x2b]  = flags: 0x20 "no parallel move", 0x40 "uses extension word", 0x80 "single word/none", 0x04 "needs word2" ; dec+0xac
dec[0x2c]  = sign (+1/-1) for post-inc/dec, `(bit? -1 : +1)` ; dec+0xb0
dec[0x2d]  = ? ; dec+0xb4
dec[0x2e]  = instruction word 0 ; dec+0xb8   dec[0x2f] = instruction word 1 (extension word)
```
OPERAND `kind`: 0xc = register (`value` = register id in the SIM enumeration; ids 0x21..0x28 = r0..r7? via `dec_ea6`, ids via tables 0x4c0000 (x0-group), 0x4c0008..), 10 = immediate/short value, 9 = extension-word value
(`dec_extword` = word 1, `dec_uses_extword` set), 0 = empty (template at 0x492000).
Register-id tables used by the decoders (all dword arrays): 0x4c0000 (`{1,5,0x31,0x34,0x32,0x35,0x51,0x50}` = the "d" accumulator/register selector), 0x4c0008 (a,b,x,y-select), 0x4c0028/48/68/88, 0x4c0098/0x4c00d8 (S1/S2 pairs for multiplies), 0x4c0148/0x4c0138/0x4c0118 (mnemonic-id tables: mpy/mpyr/mac/macr; mpyi/mpyri/maci/macri; add/-/or/eor/sub/cmp/and/-), 0x4bfc80 (6-bit "ddddd" register field -> id), 0x4bfd80 (32 entries: register id -> 'type').

`dec_ea6(slot, ea6)` (0x41d100): 6-bit effective address (mode = ea6>>3&7, reg = ea6&7): mode 6 = absolute (reg 0) or immediate (reg 4): `slot[0]=9` (or 10 with `slot[3]=0`), `slot[1]=0`, `slot[2]=dec_extword`, `dec_uses_extword=1`;
otherwise `slot[0]=mode+1`, `slot[1]=reg+0x21` (Rn id), `slot[2]=0`. Mode kinds 1..8 = `(Rn)-Nn, (Rn)+Nn, (Rn)-, (Rn)+, (Rn), (Rn+Nn), (special), -(Rn)` in DSP56000 order.

### 2.2 Driver
`decode_insn(dec, pc, unused, flags)` (0x41f9e0): `cls = opclass_lookup(dec.word0, dec_cpu_level)`; `dec_extword = dec.word1`;
`dec_init(dec)`; `r = insn_validate(word0, cur_dev.flags)`: r != 0 && r != 7 -> `dec[0]=0x19` (illegal) return false; r == 7 -> `*flags |= 4`;
then `dec_handlers[cls](word0, dec)`; if flag 0x20 set or dec[0]==0: `dec[0x2b] |= 0x80`; if the extension word was used `|= 0x40`.
`opclass_lookup(opw, cpu)` (0x430740): binary-ish linear search in `opclass_table` @0x4c45b0: 109 entries of 16 bytes
`{mask, match, class, flag}` sorted by decreasing match; first entry with `(opw & mask) == match` (and `flag == 0` when `cpu <= 3`; 0x4307d0 ignores the flag) wins; last entry (mask 0) = catch-all (illegal, handler 0x40ae40).
One-element cache (`opclass_key/opclass_last`). Entries with `flag=4` (56002+ only): inc/dec (0x000008/0x00000a), debug (0x000200/0x000300), mac/mpy variants (class 109). 
The full 109-entry table with decode handler and disassembly formatter per entry is in appendix A. Class ids 0..107 are used
directly as index into `dec_handlers` (0x4c02b0, 210 dword entries: entries >= 110 are second-level/other handlers, e.g. 56002/563xx forms 0x41ea90.. shift/extract/insert/clb/cmpu/dmac; they are referenced only from that table).

### 2.3 Names
`mnemonic_names` @0x4bf860 (`char *[0x67]`, index = `dec[0]`): 0 none,1 andi,2 bchg,3 bclr,4 brkcc,5 bset,6 btst,7 debug,8 do,9 doforever,0xa dor,0xb dorforever,0xc enddo,0xd if,0xe ifu,
0xf illegal,0x10 jmp,0x11 jclr,0x12 jsclr,0x13 jset,0x14 jsr,0x15 jsset,0x16 lra,0x17 lua,0x18 vsl,0x19 nop,0x1a norm,0x1b ori,0x1c pflush,0x1d pflushun,0x1e pfree,0x1f plock,0x20 plockr,
0x21 punlock,0x22 punlockr,0x23 rep,0x24 reset,0x25 rti,0x26 rts,0x27 stop,0x28 tcc,0x29 wait,0x2a trap,0x2b bra,0x2c bsr,0x2d brclr,0x2e bsclr,0x2f brset,0x30 bsset,0x31 abs,0x32 adc,0x33 add,
0x34 addl,0x35 addr,0x36 and,0x37 asl,0x38 asr,0x39 clb,0x3a clr,0x3b cmp,0x3c cmpm,0x3d cmpu,0x3e dec,0x3f div,0x40 dmac,0x41 eor,0x42 extract,0x43 extractu,0x44 inc,0x45 insert,0x46 lsl,0x47 lsr,
0x48 mac,0x49 maci,0x4a macr,0x4b macri,0x4c max,0x4d merge,0x4e mpy,0x4f mpyi,0x50 mpyr,0x51 mpyri,0x52 neg,0x53 normf,0x54 not,0x55 or,0x56 rnd,0x57 rol,0x58 ror,0x59 sbc,0x5a sub,0x5b subl,0x5c subr,
0x5d tfr,0x5e tst,0x5f ERROR,0x60 jcc,0x61 jscc,0x62 bcc,0x63 bscc,0x64 movec,0x65 movem,0x66 movep.
(The list contains DSP563xx mnemonics: the decoder tables are shared with the 563xx-capable simulator; only classes 0..109 are reachable at cpu level <= 3.)
`mnemonic_name(id)` (0x41cd00): returns `mnemonic_names[id]` (first entry "none" is replaced by the empty string at 0x4bfc6c; ids >= 0x5f use the shifted slot table, id >= 0x66 -> NULL).

`dis_token_strings` @0x4c05f0 (256 `char *`): token id -> text for the disassembler: 1..0x3e mnemonic stems (abs, adc, add ... wait, stop, sub, ..., 0x3b "t", 0x3c tfr, 0x3d tst, 0x3e wait, 0x3f "U",
0x40 illegal, 0x41 inc, 0x42 dec, 0x43 debug, 0x47-0x56 condition codes cc,ge,ne,pl,nn,ec,lc,gt,cs,lt,eq,mi,nr,es,ls,le), 0x58.. registers (x0 x1 y0 y1 a0 b0 a2 b2 a1 b1 a b r0-r7 n0-n7 m0-m7, sr omr sp ssh ssl la lc, a10 b10 x y a b ab ba), 0x8d.. sub-forms,
0x99 ",", 0x9a " " (space), 0x9b tab, 0x9c mr, 0x9d ccr, 0x9e omr, 0xb0..0xbf `(rN)-nN / (rN)+nN`, 0xc0.. `(rN)-`, `(rN)+`, `(rN)`, `(rN+nN)`, 0xe0 ">", 0xe4 "#>", 0xe8..0xef `-(rN)`, 0xf0 "<", 0xf1 "<<", 0xf2 "#", 0xf3 "#<", 0xf4 "#>", 0xf5 ">", 0xf6 "x:", 0xf7 "y:", 0xf8 "l:", 0xf9 "p:".
Pseudo tokens in a token list: `0` = end/skip, `-2` = text in `dis_hex_ea` (0x4dbe88, `$xxxx` from `fmt_hex_dollar`), `-3` = `dis_hex_b` (0x4dbed0), `-4` = `$` + hex of pc (`fmt_hex24`), `-5` = pc+1.

### 2.4 Functions (devinit region)
| addr | name | notes |
|------|------|-------|
| 41c140 | device_install | see 1.1; args (name, key) -> slot index or -1 |
| 41c2c0 | device_keygen | see 1.1 |
| 41c400 | keygen_step | `keygen_seed = (mulmod(keygen_seed, keygen_mult)+1) % keygen_mod` |
| 41c430 | keygen_mulmod | overflow-safe modular multiply |
| 41c750 | insn_stat_classify(stat, dec) | copies dec words into a stat record (`+4 word0, +8 word1, +0x10 category, +0x88 aux, +0xc flags`), category 0x65/0x63/0x64 from opcode-bit patterns (e.g. `(w&0xfe4080)==0x84080` movep/ea forms -> 0x65), flag bits from dec flags (0x8/0x10 cc forms, 0x20 no-move, 0x40..0x400 move kinds) |
| 41c8b0 | insn_stat_operands(stat, dec) | copies the 4 operands and the 4 move slots into the stat record (stride 0x1c: 7 dwords, 4 dwords copied by `copy_operand4`), builds a 2-level linked list at `stat+0x84` (statics 0x4dbdd8...) for L: moves; final switch on category bumps counters (`+0x38`, `+0x1c`) - per-class dynamic statistics (the "addressing mode breakdown" report) |
| 41cb40 | copy_operand4 | copies 4 dwords |
| 41cb60 | eval_cc(ccr, cc) | condition-code evaluator, cc 0..15 = cc,ge,ne,pl,nn,ec,lc,gt,cs,lt,eq,mi,nr,es,ls,le; ccr bits: C=1, V=2, Z=4, N=8, U=0x10, E=0x20, L=0x40 (case 4 nn = `!(Z) && (U|E)...`) |
| 41cd00 | mnemonic_name | see 2.3 |
| 41cd40 | stat_lmove_class | inspects the L: move pair of a stat record: register pairs (id<<16\|id) 0x350034 -> class 0x54, 0x320031 -> 0x53, 0x59005b -> 0x4e, 0x5a005c -> 0x4f |
| 41ce10 | operand_is_xy_pair | operand compare `{a[0..2]==b[0..2], a[3]==1, b[3]==2}` -> 0 |
| 41cfb0 | swap_ptrs | |
| 41cfd0 | dec_alu | if `(byte)opw != 0`: `dec_flag_nomove`, then `dec_alu_mpy` (bit 7 set) or `dec_alu_dp` |
| 41d010 | dec_flag_nomove | `dec[0x2b] \|= 0x20` |
| 41d020 | dec_alu_dp | ALU op with data-ALU operand tables: `dec.op0 = reg 0xc/{0x4bfd80[opw&0x7f]}`, `op1 = table 0x4c0000[(opw>>3)&1]`, `dec[0] = table 0x4c0158[((opw>>4)&7)<<3\|opw&7]` |
| 41d090 | dec_alu_mpy | multiply group: tables 0x4c0098/0x4c00d8 (S1,S2 by opw>>4&7), `dec[0] = 0x4c0148[opw&3]`, sign `dec[0x2c]` from bit 2 |
| 41d100 | dec_ea6 | see 2.1 |
| 41d580 | dec_pm_update | `dec_alu` + `dec_ea6(&move0, opw>>8&0x3f)` ("U" move) |
| 41d830/41d870 | dec_jbit_ea / dec_bit_ea | X:ea bit ops (jclr/jset/jsclr/jsset/bclr/bset/bchg/btst with `#n,X:ea`): op0 = imm(bit), space from bit 6 (1=X,2=Y), ea via `dec_ea6`; the j-form adds the branch target (extension word) as move slot 2 |
| 41d9b0/41d9f0 | dec_jbit_reg / dec_bit_reg | `#n,reg` forms: reg via table `0x4bfc80[opw>>8&0x3f]` |
| 41db20/41db60 | dec_jbit_aa / dec_bit_aa | X:aa short-absolute forms (address = opw>>8&0x3f) |
| 41dca0/41dce0 | dec_jbit_pp / dec_bit_pp | X:pp I/O short forms: address `(opw&0x3f00 \| 0xffc000)>>8` (pp) or `\|0x40` variant when `spacesel==1` (Y) |
| 41e0e0 / 41e280 | dec_movep_ea / dec_movep_reg | MOVEP forms; args pick which operand is source/destination via `swap_ptrs` |
| 41e610/41e650/41e690/41e6e0 | dec_do_imm/reg/ea/aa | DO #imm12 (`opw>>8&0xff \| (opw&0xf)<<8`), DO reg, DO X:ea, DO X:aa; all add the loop-end address extension word (`dec[0]=8` do) |
| 41e950 | dec_tcc | Tcc (with optional second R-R transfer when bit 16) `dec[0]=0x28`, cc in `dec[0x2a]=opw>>12&0xf` |
| 41ea00 | dec_div | `dec[0]=0x3f` |
| 41ea50 | dec_incdec | id 0x44 (inc) / 0x3e (dec) selected by bit 1, acc by bit 0 |
| 41ea90.. 41f0b0 | dec_shift_imm, dec_shift_reg, dec_lsl_lsr_imm/reg, dec_extract_reg, dec_insert_reg, dec_normf_merge, dec_clb, dec_alu_imm_short/long, dec_cmpu, dec_mpy_reg, dec_mac_su, dec_mpyi, dec_extract_imm, dec_insert_imm | 56002/563xx-only forms (mnemonic ids 0x37/0x38, 0x46/0x47, 0x42/0x43, 0x45, 0x4d/0x53, 0x39, 0x3d, mpy/mac, imm ALU ops add/or/eor/sub/cmp/and via table 0x4c0118); referenced from `dec_handlers[110..]`, not from the 109-entry class table |
| 41f850 | dec_alu_cc | ALU op + `dec[0x2a]=opw>>8&0xf`, `dec[1]=0xd/0xe` from bit 12 |
| 41f9e0 | decode_insn | see 2.2 |
| 41fab0 | dec_init | zero/template-fill |
| 41fb70..423370.. | dis_fmt_cN | disassembly formatters (2.5) |
| 4203e0 | pm_is_short_ea | `(opw&0x80)==0 && tab[0x4c0ef0+(opw&0x7f)*4]` predicate used by 420210 |
| 4212a0 4213c0 4214e0 421670 4217f0 421970 421ae0 421c50 423730 4238a0 4235f0 4234d0 4233e0 ... | dis_fmt_c*/dis_fmt_h* | multi-entry formatter blocks: they contain several table entry points (see appendix A) |

### 2.5 Disassembly (token list) formatters and `disassemble`
`disassemble(insn, text, a3, a4, info)` (0x423b10; `insn[0]` = opcode word, `insn[1]` = pc): `dis_reset()`;
`cls = opclass_lookup(word, dis_cpu_level)`; `n = dis_fmt_handlers[cls](word, tok[30])` returns the number of tokens; then concatenates
`dis_token_strings[tok[i]]` (with the pseudo tokens of 2.3) into a local 100-char buffer, then post-processes: `str_find_token(buf, 0x4c16b4, &p)` (search of a separator pattern) rewrites the line for
the "l:" style (writes `0x4c16e4` prefix + hex of `insn[0]` + `0x4c16e8` + ... returning 0/1/2 = word count?). Return value `uVar6`: 1 = normal, 2 = the
instruction has an extension word (a `-3/-4/-5` token was emitted), 0 = reserved word; copies the line to `text`. If `info != 0`: `info+0x74 = ret`, then `dis_move_addrs(info, pc)`.
`disassemble_l1` (0x424160) = `dis_cpu_level = 1` then `disassemble`.
The formatter table is `dis_fmt_handlers` @0x4c1298 (110 entries, appendix A). The parallel-move part is produced by `dis_ea_tokens(opw, tok)`
(0x4242c0; opw low byte = the move field; returns the number of tokens: register, `x:`/`y:`, `(rN)+nN`, etc.; also selects among tables 0x4c09d8, 0x4c0ae0, 0x4c0af0, 0x4c10f0, 0x4c1208, 0x4c1248).
Formatters also record the memory accesses of the instruction in `dis_effect_flags` @0x4dbea0 (bit 0 P source?, 1 X, 2 Y, 3 L?, 4/5 other) plus selector words
`dis_sel_a..e` (0x4dbea4..0x4dbeb4: value selects register file source for the ea calc: `0x100` special, `0x2000` = pc, `0x4000` = pc+1, bit 15 = `sel&7` names the address register,
bit 16 = update mode) and `dis_val_*` (0x4dbeb8..0x4dbec8: the numeric address to show for non-AGU accesses). `dis_move_addrs(info, pc)` (0x423d90) then computes for each flagged access
the effective address (`dis_ea_addr`, 0x423e90) using the AGU registers stored in `info` (`+0x14+4*n` Rn, `+0x34` Nn, `+0x54` Mn) and stores it in `info+0x7c/0x80/0x84`;
`dis_agu_addr(rn, nn, mn, negate, &out)` (0x423f90) emulates the address-generation modulo arithmetic (linear, modulo, bit-reverse via `bitrev16` 0x4240d0 when Mn==0).
This is what shows the "@address" annotations in the DISASSEMBLE/history output.

## 3. asm.c: the inline assembler (0x4240d0-0x42c470)

This is the ASM56000 instruction encoder ported into the simulator (`asm [b] [addr] instruction` command). Function names, prototypes and
semantics are identical to the ASM56000 versions documented in `re/notes/ASM56000/g4_instr.md` (amode.c/encode.c/procop.c/procxy.c). `re/scripts/xmatch.py` finds **no byte-identical
functions** in this range (both compilers/revisions differ; xmatch of SIM56000 vs ASM56000 gives 0 matches for devinit/asm/asmtab), so the mapping was made by strings, call graph and size:
see the cross reference (appendix B). The SIM version differs from ASM56000 in these ways:
* single-line, no macros/sections/expressions: `get_imm_expr` and `amode_absolute` use the *simulator* expression evaluator (0x459250 / 0x45a860 / 0x4593e0 / 0x45c890), errors go through `FUN_0045a8c0` (error printer),
  there is no forward reference/relocation handling (`op.fwd`, `cform`), no `OPT` variables, no pipeline-hazard (`check_areg_stall`) tracking.
* OPERAND is 24 bytes (6 dwords), not 32: `+0 space (1=X 2=Y 4=L 8=P, 0 none)`, `+4 mode` (1 reg, 2 (Rn), 3 (Rn)+, 4 (Rn)-, 5 (Rn)+Nn, 6 (Rn)-Nn, 7 (Rn+Nn), 8 -(Rn), 9 imm long, 0xa imm 12-bit, 0xb imm 8-bit, 0xc imm bit no, 0xd?, 0xe long abs, 0xf 12-bit short?, 0x10 6-bit short, 0x11 I/O short),
  `+8 ?`, `+0xc flags` (0x20 = forced/`<` marker), `+0x10 value`, `+0x14 register id` (-1 none). (Modes 8 and 0x10 line up with ASM56000's amode ids in g4_instr.md 2.1.)
* INSN result = 3 dwords `{count(1|2), word0, word1}`; the final result is published in `asm_result` @0x5059e0 (`count`, `word0`, `word1`) for the ASM command, and flag `word0 |= 0x200000` = "no parallel move".
* Register ids = ASM56000 RegNameTab ids: x=0 y=1 a=2 b=3 x0=4 y0=5 x1=6 y1=7 a0=8 b0=9 a1=10 b1=11 a2=12 b2=13 r0-r7 14-21 n0-n7 22-29 m0-m7 30-37 ... omr..sp 42-48 (`match_register_name` 0x425650 is the big switch parser).
* line parsing globals: `asm_split_fields` (0x424480): copies the line `asm_line_buf` (0x4dbf08) into fields separated by whitespace (`;` starts a comment): label -> `asm_label` (0x4dc010), then
  `asm_mnem_field` (0x4dc00c), `asm_op1_field` (0x4dc008), `asm_op2_field` (0x4dc118, X field), `asm_op3_field` (0x4dbf00, Y field), rest appended; `asm_line` (0x424730): mnemonic must be < 16 chars, lower-cased (`str_lower_copy` -> 0x4dc120),
  looked up by `find_mnemonic` = `bsearch_cb(name, asm_mnem_table, asm_mnem_count(0x8c=140), 12, cmp@0x4248a0)`; not found -> error "Unrecognized mnemonic"; found -> `proc_instr(entry)`.
  `optr` (0x5029e0) is the scan pointer like ASM56000.

### 3.1 Mnemonic table `asm_mnem_table` @0x4c16f0
140 entries (`asm_mnem_count` @0x4c1d80 = 0x8c) x 12 bytes, sorted by name (bsearch, case-folded compare callback at 0x4248a0):
`{char *name; unsigned char iclass /*+4*/; unsigned char pmclass /*+5*/; short pad /*+6*/; unsigned long template /*+8*/}`.
`iclass` equals ASM56000's InstrTab f1 (`proc_instr` switch: 1 addl/addr/subl/subr, 2 inc/dec, 3 abs/asl/asr/clr/neg/rnd, 4 and/or, 5 bchg/bclr/bset/btst (one class here),
7 cmp/cmpm, 8 div, 9 do, 0xa enddo, 0xb illegal, 0xc reset/stop/wait, 0xd swi, 0x1b nop, 0x29 debug*, 0xe jcc, 0x13 jmp, 0xf jclr/jset, 0x11 jsclr/jsset, 0x10 jscc, 0x12 jsr, 0x14 lua/lea,
0x15 mac, 0x2a macr, 0x1a mpy, 0x2b mpyr, 0x16 movec, 0x17 move, 0x18 movem, 0x19 movep, 0x1c norm, 0x1d rep, 0x1e rti, 0x1f rts, 0x20 eor, 0x24 adc/sbc, 0x22 add/sub, 0x23 tfr, 0x25 andi/ori,
0x26 tcc, 0x27 tst, 0x28 lsl/lsr/not/rol/ror). `pmclass` = parallel-move permission passed to `do_xy`: 0 = none, 1 = MOVE-family (move/movec/movem), 2 = data-ALU moves, 3 = dynamic (and, or, mac, macr, mpy, mpyr: handler return value becomes the class; ASM56000 numbers these 0/0x35/1/2).
`template` = opcode base word (ASM56000 f3, e.g. abs 0x26, adc 0x21, andi 0xb8, jcc 0xa0000 + cc<<12, tcc 0x20000 + cc<<12, debugcc 0x300|cc). No cycle counts in this table.

### 3.2 Functions
See names file for the whole list; grouped:
* line/dispatch: `asm_split_fields` 424480, `skip_to_space` 4246e0, `asm_line` 424730, `str_lower_copy` 424790, `lower_char` 4247d0, `find_mnemonic` 424810, `bsearch_cb` 424830, `proc_instr` 4248e0 (switch as in ASM56000 with class handlers `p_*` at 428df0..429f00; after the handler: if `nfields==3` -> use the handler result as pmclass; if the pm class is 0 and Op2 non-empty -> "Too many fields specified for instruction"; else if Op2 empty: `word0 |= 0x200000`; otherwise `canon_xy_fields()` (swap X/Y fields if Y: comes first) and `do_xy` 424c50).
* parallel moves (procxy.c): `do_xy` 424c50 (parses the first move operand with `parse_space` 424f60 + `parse_xfield_src` 425140, dispatches on the operand register/mode to `xy_lreg` 427020, `xy_acc` 427100, `xy_xreg` 4273b0, `xy_reg` 427c20, `xy_mreg` 427f40, `xy_ctlreg` 428070, `xy_imm_short` 426cd0 / `xy_imm_long` 426e50, and for memory-source moves on space X/Y/L/P to `xy_xsrc` 4281c0 (+ `xy_xsrc_acc` 4286e0), `xy_ysrc` 428910, `xy_lsrc` 428b40, `xy_psrc` 428bc0), `xdst_mem` 4274e0 (X-memory destination, string "xdst_mem failure"), `chk_move_class` 427b80 ("Instruction does not allow data movement specified"), `chk_xy_regs` 428cf0 ("Invalid XY address register specification"), `chk_no_yfield` 426c90.
* operand parser (amode.c): `parse_operand` 4251c0, `get_amode` 425230, `amode_register` 4267d0, `amode_indirect` 425390, `amode_immediate` 426210, `get_imm_expr` 426370, `amode_absolute` 426410, `note_reg_direct` 426b50, `check_dup_dest` 426b80, `parse_addr_reg` 4255d0, `parse_offset_reg` 4255f0, `match_register_name` 425650; error strings from 0x4c1f48 to 0x4c2684 (all messages of ASM56000's amode.c without `w/fwd` variants).
* class handlers (procop.c): `p_andi` 428e50, `p_and_or` 428ed0, `p_alu1` 429080, `p_addl` 429110, `p_eor_adc` 429180, `p_alu2` 429220, `p_norm` 4292e0, `p_lua` 429340, `p_div` 4293a0, `p_bitop` 429400, `p_do` 429540, `p_enddo` 4296e0, `p_rep` 429710, `p_jmp` 429800, `p_jsr` 4298d0, `p_jbit` 4299a0, `p_tcc` 429b00, `p_mul` 429c10 (+`mulreg` 429da0), `p_move` 429ea0, `p_movep` 429f00, `p_noarg` 428df0, `p_rts` 428e20; helper `p_alu_dst` 428fa0.
* encoders (encode.c): `enc_*` and the field-code helpers `ee_code d_code jjj_code rrr_code mmm_code s_code d6_code ccc_code ddddd_code dd_code nnn_code ddd_code fff_code xx_code yy_code x_code y_code lll_code qq_code` (42a440..42c470), `insert_bits` 42a410 (= `(word & ~(mask<<pos)) | ((val & mask)<<pos)` with `mask = ~(-1<<width)`), `set_ext_word` 42ad10, `skip_comma` 42a3a0.
* number formatting for the disassembler: `fmt_hex_dollar` 424200 (`"$" + lower hex`), `fmt_hex24` 424260 (24-bit hex, no `$`).

## 4. asmtab region (0x42c4c0-0x433fff): memory engine and ALU
* `mem_reg_read(id, addr, &out)` (0x42c4c0) -> returns 1 = ok / 0 = unmapped (writes value(s) to `out`; pair ids 3/9/10 recurse for X:Y, P+X, L; `id >= 0x1d` = registers: reads each part through `FUN_00458280(devstate->regfile, 0x1c, ...)`, joins them: unit shifts 4 or 8 bits), `mem_region_of(space, addr)` (0x42d4c0) picks the region class 0xd/0xe/0xf, 0x12/0x13/0x14, 0x18/0x19 from the device flags, OMR mode bits (`(*(dev+0x18)+0x1b0)`: 3 = mode a/b/c, 4 = ...) and the map table, `mem_reg_write` (0x42da70) is the mirror (calls `FUN_00456f60`, `FUN_00458480`).
* `omr_remap_*`: re-point memory block descriptors (`MEMBLK.data`/`enabled`) when OMR mode/bit 3/bit 2 change for 56009/56011/56012 (block ids 0xe/0x13/0x18 at 0/0x100..0x800: `p->data = q->data; p->enabled = mode bit; q->enabled = !mode bit`).
* fetch-stage attribute lookups (called only from `FUN_00405000`, which fills the pipeline record at `DAT_004dbc10+0x1d0..0x220`): `insn_class_code` 42fdb0 (`insn_class_handlers`), `insn_move_info` 42f2a0 (12-byte records at 0x4c38a8 selected by `insn_move_handlers[cls](opw, cpu, ...)`, 33 records), `insn_exec_info` 42eec0 (32-byte records at 0x4c2bb0: 8 dwords copied to core+0x1ec..0x208, selected by `insn_exec_handlers[cls]`, 5 records), `insn_ea_class` 42fe10 (tables 0x4c3e40/0x4c3ff8 indexed by class), `insn_validate` 430850 (`insn_valid_handlers[cls](opw)` -> 0 ok, 7 needs extension?, 2, other = illegal), `ea_mode_index` 42ff20 (opw low byte -> 0..0x42 index, 0x40/0x41 for `(Rn)` shorthand), `insn_valid_pm_a..f` (class-specific validity rules for move + ALU combinations, tables 0x4c41b0/0x4c43b0/0x4c0ef0).
* ALU engine (`alu_core` = `DAT_004dc144` = core register file pointer; layout used: `+0x9c` CCR image, `+0x184` current opcode word, `+0x1b8` ALU op index -> `alu_handlers` @0x4c4eb0, `+0x1bc` 1 = 56-bit "extended" mode, `+0x1c0/+0x1c4` source register ids, `+0x1c8` destination accumulator id 0x12c (A) / 0x12d (B) / 2 / 6, `+0x45c/+0x460/+0x464` operand 1 (ext/hi/lo 24-bit words), `+0x468/+0x46c/+0x470` operand 2, `+0x474..0x47c` shifted operand, `+0x480/+0x484/+0x488` 56-bit result (lo/hi/ext), `+0x48c/+0x490/+0x494` |operand| pieces). `alu_ccr` (0x4dc13c) collects CCR bits during an operation: 1 = ?, 2 = overflow candidate, 4 = zero, 8 = negative, 0x10 = unnormalized, 0x40 = limit. Primitives: `alu_norm_sum/res/abs` (carry propagation with 24-bit masks), `alu_add56` 430be0 (= handler index 3, 56-bit add incl. overflow detection `alu_ovf_add/sub`), `alu_set_ccr` 433890 (Z/N/U/E flags from the 56-bit result), `alu_mpy` 432d50 / `alu_mac` 433020 (24x24 multiply built from 6-bit pieces with explicit carries), `alu_round` 433250, `alu_shift1` 433360, `alu_load_*`, `alu_store_ext` 433700 (writes the extension register: a2/b2 sign extension for ids 0x12c/0x12d/2/6), `alu_execute` 433c80 (`alu_handlers[core+0x1b8]()`, writes CCR back to core+0x9c and notifies `FUN_00404690(0x27)`), `alu_decode` 433ce0.
* peripherals: `periph_reset` 433e80 (clears `DEVSTATE+0x44`, per-instance counters and per-register bit arrays), `periph_call` 433f10 (`dev->periph[i].desc.vtable[0](i, a, b)`), `periph_find_reg` 433f60 (search all peripherals whose enable-string is empty for register `name`, returns (periph index, reg index) or -1).

## 5. Globals (see names file for the full list)
`dev_table` 4aab08, `max_devices` 4aab04, `dev_state_table` 4aab10, `cur_dev` 505790, `cur_devstate` 505798, `cur_devaux` 50578c, `mnemonic_names` 4bf860, `dis_token_strings` 4c05f0,
`dec_handlers` 4c02b0, `dis_fmt_handlers` 4c1298, `opclass_table` 4c45b0, `asm_mnem_table` 4c16f0 (140), `asm_line_buf` 4dbf08, field pointers 4dc00c/4dc008/4dc118/4dbf00, `optr` 5029e0, `asm_result` 5059e0,
`dec_*` scratch 4dbe78/7c/80, `dis_*` scratch 4dbe88..4dbee8, `alu_core` 4dc144, `alu_ccr` 4dc13c.

## 6. Interfaces to other modules / quirks
* Calls out: `FUN_0045a8c0` = assembler error printer (`sim_error(msg)`; message text used by ASM command), `FUN_00439080(class,addr)` = memory-map region index lookup, `FUN_00458280` register-file access, `FUN_004340f0(a,b)` = case-insensitive name compare (state module), `FUN_00404690/00404900/00404920/00404940` register/pipeline update helpers (exec), `FUN_00459250/0045a860/004593e0/0045c890` expression evaluator used by `get_imm_expr`/`amode_absolute`.
* Entry points from the command dispatcher: `device_install` (0x435ce0), `asm_line` (assembler command), `disassemble`/`disassemble_l1` (DISASSEMBLE, history, list), `decode_insn` (fetch/execute), `insn_*` (0x405000), `alu_execute` (exec cores, 0x405b40 etc.).
* Quirk: the device key for 68356 / 56030 is a pure function of the lower-cased device name (`device_keygen`), so it is a constant per name; a rebuilt tool can compute and accept it identically (compare all 9 bytes including the NUL).
* Quirk: `disassemble` truncates at 100 chars (`local_dc[100]`).
* The formatter and decoder handler tables have hidden entries beyond Ghidra's function list; before translating, re-run Ghidra with function creation at the table entries, or disassemble from the addresses in appendices A and C.

## Appendix A: opcode class table (0x4c45b0, 109 entries), decode handler (0x4c02b0) and disassembly formatter (0x4c1298) per class

Entry: opw matches when `(opw & mask) == match`; entries are tried in order; `flag != 0` entries are skipped when the cpu level <= 3 (0x430740). Handler column: address and name from the names file (hidden = not in functions.txt).

| # | mask | match | flag | class | decode handler | disasm formatter |
|---|------|-------|------|-------|----------------|------------------|
| 0 | 800000 | 800000 | 0 | 0 | 41ce50 dec_c0_enddo | 41fb70 dis_fmt_c0 |
| 1 | f04000 | 704000 | 0 | 1 | 41d170 dec_c1_enddo | 41fd70 dis_fmt_c1 |
| 2 | f04000 | 700000 | 0 | 2 | 41d220 dec_c2_doforever | 41feb0 dis_fmt_c2 |
| 3 | f04000 | 604000 | 0 | 3 | 41d170 dec_c1_enddo | 41ffc0 dis_fmt_c3 |
| 4 | f04000 | 600000 | 0 | 4 | 41d220 dec_c2_doforever | 420100 dis_fmt_c4 |
| 5 | f04000 | 504000 | 0 | 5 | 41d170 dec_c1_enddo | 420210 dis_fmt_c5 |
| 6 | f04000 | 500000 | 0 | 6 | 41d220 dec_c2_doforever | 420400 dis_fmt_c6 |
| 7 | f44000 | 444000 | 0 | 7 | 41d170 dec_c1_enddo | 4205b0 dis_fmt_c7 |
| 8 | f44000 | 440000 | 0 | 8 | 41d220 dec_c2_doforever | 4206e0 dis_fmt_c8 |
| 9 | f44000 | 404000 | 0 | 9 | 41d2d0 dec_c9_enddo | 4207f0 dis_fmt_c9 |
| 10 | f44000 | 400000 | 0 | 10 | 41d3d0 dec_c10_doforever | 420980 dis_fmt_c10 |
| 11 | f80000 | 380000 | 0 | 11 | 41d4d0 dec_c11_pm | 420b00 dis_fmt_c11 |
| 12 | f80000 | 300000 | 0 | 12 | 41d4d0 dec_c11_pm | 420b80 dis_fmt_c12 |
| 13 | f80000 | 280000 | 0 | 13 | 41d4d0 dec_c11_pm | 420c00 dis_fmt_c13 |
| 14 | fc0000 | 240000 | 0 | 14 | 41d4d0 dec_c11_pm | 420d10 dis_fmt_c14 |
| 15 | fe0000 | 220000 | 0 | 15 | 41d530 dec_c15_pm | 420d90 dis_fmt_c15 |
| 16 | fd0000 | 210000 | 0 | 16 | 41d530 dec_c15_pm | 420d90 dis_fmt_c15 |
| 17 | fc8000 | 208000 | 0 | 17 | 41d530 dec_c15_pm | 420d90 dis_fmt_c15 |
| 18 | ffe000 | 204000 | 0 | 18 | 41d580 dec_pm_update | 420eb0 dis_fmt_c18 |
| 19 | ffc000 | 200000 | 0 | 19 | 41d5b0 dec_c19_pm | 420ef0 dis_fmt_c19 |
| 20 | f04000 | 104000 | 0 | 20 | 41d5d0 dec_c20_enddo | 420f50 dis_fmt_c20 |
| 21 | f04000 | 100000 | 0 | 21 | 41d690 dec_c21_pm | 4210f0 dis_fmt_c21 |
| 22 | ff0000 | 0f0000 | 0 | 22 | 41d770 dec_c22_pm | 421280 dis_fmt_c22 |
| 23 | ff0000 | 0e0000 | 0 | 23 | 41d770 dec_c22_pm | 421340 dis_fmt_c23 |
| 24 | ff0000 | 0d0000 | 0 | 24 | 41d770 dec_c22_pm | 421360 dis_fmt_c24 |
| 25 | ff0000 | 0c0000 | 0 | 25 | 41d770 dec_c22_pm | 421380 dis_fmt_c25 |
| 26 | ffc0a0 | 0bc0a0 | 0 | 26 | 41d7c0 dec_c26_pm | 4213a0 dis_fmt_c26 |
| 27 | ffc0a0 | 0bc080 | 0 | 27 | 41d7c0 dec_c26_pm | 421480 dis_fmt_c27 |
| 28 | ffc0e0 | 0bc060 | 0 | 28 | 41f350 dec_c28_btst | 423880 dis_fmt_c28 |
| 29 | ffc0e0 | 0bc040 | 0 | 29 | 41f370 dec_c29_bchg | 423960 dis_fmt_c29 |
| 30 | ffc0e0 | 0bc020 | 0 | 30 | 41d990 dec_c30_jsset | 423710 dis_fmt_c30 |
| 31 | ffc0e0 | 0bc000 | 0 | 31 | 41da20 dec_c31_jsclr | 423820 dis_fmt_c31 |
| 32 | ffc0a0 | 0b80a0 | 0 | 32 | 41dc80 dec_c32_jsset | 4214c0 dis_fmt_c32 |
| 33 | ffc0a0 | 0b8080 | 0 | 33 | 41dd30 dec_c33_jsclr | 4215f0 dis_fmt_c33 |
| 34 | ffc0a0 | 0b8020 | 0 | 34 | 41df10 dec_c34_btst | 421950 dis_fmt_c34 |
| 35 | ffc0a0 | 0b8000 | 0 | 35 | 41df30 dec_c35_bchg | 421a60 dis_fmt_c35 |
| 36 | ffc0a0 | 0b40a0 | 0 | 36 | 41d810 dec_c36_jsset | 421650 dis_fmt_c36 |
| 37 | ffc0a0 | 0b4080 | 0 | 37 | 41d8b0 dec_c37_jsclr | 421770 dis_fmt_c37 |
| 38 | ffc0a0 | 0b4020 | 0 | 38 | 41df90 dec_c38_btst | 421ac0 dis_fmt_c38 |
| 39 | ffc0a0 | 0b4000 | 0 | 39 | 41dfb0 dec_c39_bchg | 421bd0 dis_fmt_c39 |
| 40 | ffc0a0 | 0b00a0 | 0 | 40 | 41db00 dec_c40_jsset | 4217d0 dis_fmt_c40 |
| 41 | ffc0a0 | 0b0080 | 0 | 41 | 41dba0 dec_c41_jsclr | 4218f0 dis_fmt_c41 |
| 42 | ffc0a0 | 0b0020 | 0 | 42 | 41e010 dec_c42_btst | 421c30 dis_fmt_c42 |
| 43 | ffc0a0 | 0b0000 | 0 | 43 | 41e030 dec_c43_bchg | 421d30 dis_fmt_c43 |
| 44 | ffc0a0 | 0ac0a0 | 0 | 44 | 41d7c0 dec_c26_pm | 421460 dis_fmt_c44 |
| 45 | ffc0a0 | 0ac080 | 0 | 45 | 41d7c0 dec_c26_pm | 4214a0 dis_fmt_c45 |
| 46 | ffc0e0 | 0ac060 | 0 | 46 | 41f390 dec_c46_bset | 423980 dis_fmt_c46 |
| 47 | ffc0e0 | 0ac040 | 0 | 47 | 41f3b0 dec_c47_bclr | 4239a0 dis_fmt_c47 |
| 48 | ffc0e0 | 0ac020 | 0 | 48 | 41da40 dec_c48_jset | 423840 dis_fmt_c48 |
| 49 | ffc0e0 | 0ac000 | 0 | 49 | 41da60 dec_c49_jclr | 423860 dis_fmt_c49 |
| 50 | ffc0a0 | 0a80a0 | 0 | 50 | 41dd50 dec_c50_jset | 421610 dis_fmt_c50 |
| 51 | ffc0a0 | 0a8080 | 0 | 51 | 41dd70 dec_c51_jclr | 421630 dis_fmt_c51 |
| 52 | ffc0a0 | 0a8020 | 0 | 52 | 41df50 dec_c52_bset | 421a80 dis_fmt_c52 |
| 53 | ffc0a0 | 0a8000 | 0 | 53 | 41df70 dec_c53_bclr | 421aa0 dis_fmt_c53 |
| 54 | ffc0a0 | 0a40a0 | 0 | 54 | 41d910 dec_c54_jset | 421790 dis_fmt_c54 |
| 55 | ffc0a0 | 0a4080 | 0 | 55 | 41d930 dec_c55_jclr | 4217b0 dis_fmt_c55 |
| 56 | ffc0a0 | 0a4020 | 0 | 56 | 41dfd0 dec_c56_bset | 421bf0 dis_fmt_c56 |
| 57 | ffc0a0 | 0a4000 | 0 | 57 | 41dff0 dec_c57_bclr | 421c10 dis_fmt_c57 |
| 58 | ffc0a0 | 0a00a0 | 0 | 58 | 41dbc0 dec_c58_jset | 421910 dis_fmt_c58 |
| 59 | ffc0a0 | 0a0080 | 0 | 59 | 41dbe0 dec_c59_jclr | 421930 dis_fmt_c59 |
| 60 | ffc0a0 | 0a0020 | 0 | 60 | 41e050 dec_c60_bset | 421d50 dis_fmt_c60 |
| 61 | ffc0a0 | 0a0000 | 0 | 61 | 41e070 dec_c61_bclr | 421d70 dis_fmt_c61 |
| 62 | ffc000 | 098000 | 0 | 62 | 41f2e0 dec_c62_pm | 4236f0 dis_fmt_c62 |
| 63 | ffc000 | 090000 | 0 | 63 | 41f260 dec_c63_pm | 4235d0 dis_fmt_c63 |
| 64 | ffc000 | 088000 | 0 | 64 | 41f2e0 dec_c62_pm | 4235f0 dis_fmt_c64 |
| 65 | fe4080 | 084080 | 0 | 65 | 41e090 dec_c65_pm | 421d90 dis_fmt_c65 |
| 66 | fe40c0 | 084040 | 0 | 66 | 41e1a0 dec_c66_pm | 421f60 dis_fmt_c66 |
| 67 | fe40c0 | 084000 | 0 | 67 | 41e230 dec_c67_pm | 4220e0 dis_fmt_c67 |
| 68 | ffc000 | 080000 | 0 | 68 | 41f260 dec_c63_pm | 4234d0 dis_fmt_c68 |
| 69 | ff4080 | 074080 | 0 | 69 | 41e440 dec_c69_enddo | 422220 dis_fmt_c69 |
| 70 | ff4080 | 070000 | 0 | 70 | 41e4c0 dec_c70_doforever | 422330 dis_fmt_c70 |
| 71 | ffc0a0 | 06c020 | 0 | 71 | 41e570 dec_c71_rep | 4224a0 dis_fmt_c71 |
| 72 | ffc0a0 | 06c000 | 0 | 72 | 41e650 dec_do_reg | 422730 dis_fmt_c72 |
| 73 | ffc0a0 | 064020 | 0 | 73 | 41e5a0 dec_c73_rep | 422560 dis_fmt_c73 |
| 74 | ffc0a0 | 064000 | 0 | 74 | 41e690 dec_do_ea | 4227e0 dis_fmt_c74 |
| 75 | ff00a0 | 0600a0 | 0 | 75 | 41e540 dec_c75_rep | 422440 dis_fmt_c75 |
| 76 | ff00a0 | 060080 | 0 | 76 | 41e610 dec_do_imm | 4226a0 dis_fmt_c76 |
| 77 | ffc0a0 | 060020 | 0 | 77 | 41e5e0 dec_c77_rep | 4225f0 dis_fmt_c77 |
| 78 | ffc0a0 | 060000 | 0 | 78 | 41e6e0 dec_do_aa | 422890 dis_fmt_c78 |
| 79 | ff40b8 | 054038 | 0 | 79 | 41e760 dec_c79_enddo | 422c80 dis_fmt_c79 |
| 80 | ff40b8 | 054020 | 0 | 80 | 41e760 dec_c79_enddo | 4229d0 dis_fmt_c80 |
| 81 | ff00b8 | 0500b8 | 0 | 81 | 41e730 dec_c81_pm | 422c10 dis_fmt_c81 |
| 82 | ff00b8 | 0500a0 | 0 | 82 | 41e730 dec_c81_pm | 422960 dis_fmt_c82 |
| 83 | ff40b8 | 050038 | 0 | 83 | 41e7f0 dec_c83_doforever | 422dc0 dis_fmt_c83 |
| 84 | ff40b8 | 050020 | 0 | 84 | 41e7f0 dec_c83_doforever | 422b00 dis_fmt_c84 |
| 85 | ff40b8 | 0440b8 | 0 | 85 | 41e880 dec_c85_enddo | 422f80 dis_fmt_c85 |
| 86 | ff40b8 | 0440a0 | 0 | 86 | 41e880 dec_c85_enddo | 422ec0 dis_fmt_c86 |
| 87 | ff60b8 | 044018 | 0 | 87 | 41e900 dec_c87_lua | 4230c0 dis_fmt_c87 |
| 88 | ff60b8 | 044010 | 0 | 88 | 41e900 dec_c87_lua | 423050 dis_fmt_c88 |
| 89 | ff0080 | 030000 | 0 | 89 | 41e950 dec_tcc | 423130 dis_fmt_c89 |
| 90 | ff0080 | 020000 | 0 | 90 | 41e950 dec_tcc | 423210 dis_fmt_c90 |
| 91 | fff8f7 | 01d815 | 0 | 91 | 41f110 dec_c91_norm | 4232b0 dis_fmt_c91 |
| 92 | ffc0c0 | 018040 | 0 | 92 | 41ea00 dec_div | 423310 dis_fmt_c92 |
| 93 | ff00c0 | 0100c0 | 4 | 109 | 41ee80 dec_mpy_reg | 423a40 dis_fmt_c109 |
| 94 | fffff0 | 000300 | 4 | 93 | 41f3d0 dec_c93_debug | 4239c0 dis_fmt_c93 |
| 95 | ffffff | 000200 | 4 | 94 | 41f3d0 dec_c93_debug | 4239c0 dis_fmt_c93 |
| 96 | ff00fc | 0000f8 | 0 | 95 | 41f160 dec_c95_ori | 423370 dis_fmt_c95 |
| 97 | ff00fc | 0000b8 | 0 | 96 | 41f1a0 dec_c96_andi | 4233e0 dis_fmt_c96 |
| 98 | ff00af | 00008c | 0 | 97 | 41f1e0 dec_c97_enddo | 423450 dis_fmt_c97 |
| 99 | ff00af | 000087 | 0 | 98 | 41f1f0 dec_c98_stop | 423460 dis_fmt_c98 |
| 100 | ff00af | 000086 | 0 | 99 | 41f200 dec_c99_wait | 423470 dis_fmt_c99 |
| 101 | ff00af | 000084 | 0 | 100 | 41f210 dec_c100_reset | 423480 dis_fmt_c100 |
| 102 | ffffff | 00000c | 0 | 101 | 41f250 dec_c101_rts | 4234c0 dis_fmt_c101 |
| 103 | fffffe | 00000a | 4 | 102 | 41ea50 dec_incdec | 423a00 dis_fmt_c102 |
| 104 | fffffe | 000008 | 4 | 103 | 41ea50 dec_incdec | 423a00 dis_fmt_c102 |
| 105 | ffffff | 000006 | 0 | 104 | 41f220 dec_c104_trap | 423490 dis_fmt_c104 |
| 106 | ffffff | 000005 | 0 | 105 | 41f3f0 dec_c105_illegal | 4239f0 dis_fmt_c105 |
| 107 | ffffff | 000004 | 0 | 106 | 41f240 dec_c106_rti | 4234b0 dis_fmt_c106 |
| 108 | ffffff | 000000 | 0 | 107 | 41f230 dec_c107_nop | 4234a0 dis_fmt_c107 |

## Appendix C: other class-indexed handler tables (address only; bodies are hidden functions in the 0x42e5c0-0x42f9xx / 0x42fe60-0x4300xx / 0x430880-0x433650 gaps)

    
    insn_exec_handlers @4c36f0: 0:42e5d0 1:42e600 2:42e750 3:42e600 4:42e750 5:42e670 6:42e780 7:42e670 8:42e780 9:42e6e0 10:42e7b0 11:42e7e0 12:42e7e0 13:42e7f0 14:42e810 15:42e820 16:42e820 17:42e82
0 18:42e5c0 19:42e5c0 20:42e830 21:42e890 22:42e5c0 23:42e5c0 24:42e5c0 25:42e5c0 26:42e5c0 27:42e5c0 28:42ee90 29:42ee90 30:42ee80 31:42ee80 32:42e8f0 33:42e8f0 34:42e950 35:42e950 36:42e910 37:42e91
0 38:42e980 39:42e980 40:42e8f0 41:42e8f0 42:42e950 43:42e950 44:42e5c0 45:42e5c0 46:42ee90 47:42ee90 48:42ee80 49:42ee80 50:42e8f0 51:42e8f0 52:42e950 53:42e950 54:42e910 55:42e910 56:42e980 57:42e98
0 58:42e8f0 59:42e8f0 60:42e950 61:42e950 62:42ee40 63:42ee40 64:42ee40 65:42e9e0 66:42eaf0 67:42eb90 68:42ee40 69:42ec20 70:42ec90 71:42ecd0 72:42ecd0 73:42ece0 74:42ece0 75:42ecc0 76:42ecc0 77:42ed2
0 78:42ed20 79:42ed40 80:42ed40 81:42f220 82:42f220 83:42eda0 84:42eda0 85:42edc0 86:42edc0 87:42ede0 88:42ede0 89:42ee10 90:42e5c0 91:42e5c0 92:42e5c0 93:42e5c0 94:42e5c0 95:42ee20 96:42ee20 97:42e5c
0 98:42e5c0 99:42e5c0 100:42e5c0 101:42e5c0 102:42e5c0 103:42e5c0 104:42e5c0 105:42e5c0 106:42e5c0 107:42e5c0 108:42e5c0
    
    insn_move_handlers @4c3ad0: 0:42ef40 1:42ef50 2:42ef40 3:42ef50 4:42ef40 5:42ef50 6:42ef40 7:42ef50 8:42ef40 9:42ef50 10:42ef40 11:42ef40 12:42ef40 13:42ef40 14:42ef40 15:42ef40 16:42ef40 17:42ef4
0 18:42ef40 19:42ef40 20:42ef50 21:42ef50 22:42ef80 23:42ef80 24:42ef90 25:42ef90 26:42efa0 27:42efd0 28:42f290 29:42f290 30:42f000 31:42f000 32:42f000 33:42f000 34:42f290 35:42f290 36:42f010 37:42f01
0 38:42f040 39:42f040 40:42f000 41:42f000 42:42f290 43:42f290 44:42efa0 45:42efd0 46:42f290 47:42f290 48:42f000 49:42f000 50:42f000 51:42f000 52:42f290 53:42f290 54:42f010 55:42f010 56:42f040 57:42f04
0 58:42f000 59:42f000 60:42f290 61:42f290 62:42f270 63:42f270 64:42f270 65:42f070 66:42f0c0 67:42f0f0 68:42f270 69:42f0c0 70:42f120 71:42f130 72:42f170 73:42f140 74:42f180 75:42f130 76:42f170 77:42f13
0 78:42f170 79:42f1c0 80:42f1c0 81:42f1b0 82:42f1b0 83:42f1b0 84:42f1b0 85:42f1b0 86:42f1b0 87:42f1f0 88:42f1f0 89:42f200 90:42f200 91:42f210 92:42f210 93:42f1b0 94:42f1b0 95:42f1b0 96:42f1b0 97:42f22
0 98:42f230 99:42f230 100:42f240 101:42f260 102:42f210 103:42f210 104:42f250 105:42ef30 106:42f260 107:42f1b0 108:42ef30
    
    insn_class_handlers @4c3c88: 0:42f4b0 1:42f4d0 2:42f530 3:42f4d0 4:42f530 5:42f4d0 6:42f530 7:42f4d0 8:42f530 9:42f570 10:42f5c0 11:42f4a0 12:42f4a0 13:42f4a0 14:42f4a0 15:42f4a0 16:42f4a0 17:42f4
a0 18:42f5e0 19:42f4a0 20:42f5f0 21:42f640 22:42f690 23:42f690 24:42f690 25:42f690 26:42f6c0 27:42f6c0 28:42f4a0 29:42f4a0 30:42fd70 31:42fd70 32:42f710 33:42f710 34:42f770 35:42f770 36:42f7a0 37:42f7
a0 38:42f850 39:42f850 40:42f710 41:42f710 42:42f770 43:42f770 44:42f6c0 45:42f6c0 46:42f4a0 47:42f4a0 48:42fd70 49:42fd70 50:42f710 51:42f710 52:42f770 53:42f770 54:42f7a0 55:42f7a0 56:42f850 57:42f8
50 58:42f710 59:42f710 60:42f770 61:42f770 62:42fd20 63:42fcd0 64:42fd20 65:42f8b0 66:42fa60 67:42fba0 68:42fcd0 69:42fbe0 70:42fc30 71:42f4a0 72:42fd70 73:42fc50 74:42f7a0 75:42f4a0 76:42fd70 77:42f7
70 78:42f710 79:42f850 80:42f850 81:42f4a0 82:42f4a0 83:42f770 84:42f770 85:42f4a0 86:42f4a0 87:42fcb0 88:42fcb0 89:42f4a0 90:42f4a0 91:42f5e0 92:42f4a0 93:42f4a0 94:42f4a0 95:42f4a0 96:42f4a0 97:42f4
a0 98:42f4a0 99:42f4a0 100:42f4a0 101:42f4a0 102:42f4a0 103:42f4a0 104:42f4a0 105:42f4a0 106:42f4a0 107:42f4a0 108:42f4a0
    
    insn_valid_handlers @4c4c90: 0:42fe60 1:42ff80 2:42ffb0 3:42ff80 4:42ffb0 5:42ffc0 6:42ffc0 7:42ff80 8:42ffb0 9:4300a0 10:4300a0 11:42ffb0 12:42ffb0 13:430160 14:42ffb0 15:430210 16:430210 17:4302
10 18:42ffb0 19:4302d0 20:430300 21:430390 22:42e5c0 23:42e5c0 24:42e5c0 25:42e5c0 26:430410 27:430410 28:4306e0 29:4306e0 30:4306e0 31:4306e0 32:430430 33:430430 34:430430 35:430430 36:430450 37:4304
50 38:430480 39:430480 40:430430 41:430430 42:430430 43:430430 44:430410 45:430410 46:4306e0 47:4306e0 48:4306e0 49:4306e0 50:430430 51:430430 52:430430 53:430430 54:430450 55:430450 56:430480 57:4304
80 58:430430 59:430430 60:430430 61:430430 62:430670 63:430670 64:430670 65:4304b0 66:4304b0 67:4304e0 68:430670 69:430510 70:430550 71:4304e0 72:4305a0 73:430580 74:430580 75:42e5c0 76:42e5c0 77:42e5
c0 78:42e5c0 79:4304b0 80:4304b0 81:42e5c0 82:42e5c0 83:42e5c0 84:42e5c0 85:4305e0 86:4304e0 87:42e5c0 88:42e5c0 89:430630 90:430630 91:42e5c0 92:42ffb0 93:42e5c0 94:42e5c0 95:430650 96:430650 97:42e5
c0 98:42e5c0 99:42e5c0 100:42e5c0 101:42e5c0 102:42e5c0 103:42e5c0 104:42e5c0 105:42e5c0 106:42e5c0 107:42e5c0 108:42fe50
    
    alu_handlers @4c4eb0: 1:430880 2:430a90 3:430be0 4:430cd0 5:430e80 6:430fc0 7:431090 8:431170 9:4312b0 10:431300 11:4314a0 12:431700 13:431920 14:4319f0 15:431ac0 16:4325f0 17:432a70 18:431b80 19:
432d50 20:433020 21:431b90 22:433360 23:431c70 24:431d40 25:433650 26:431e10 27:431ef0 28:431fe0 29:432160 30:432290 31:432410 32:432590 33:4335a0 34:4318e0 35:4318a0 36:431270 37:431290 38:432120 39:
432140 40:12 41:20 42:5 43:21 44:ffffffff 45:a 46:1f 47:b 48:3 49:19 50:4 51:9 52:1d 53:ffffffff 54:1e 55:17 56:3 57:2 58:8 59:f 60:1d 61:1c 62:1 63:1b

## Appendix B: SIM56000 <-> ASM56000 cross reference (same source, different revision; matched by name, strings, call graph, size; not byte-identical)

| SIM56000 | ASM56000 | name |
|---|---|---|
| 424790 | 438f9c | str_lower_copy |
| 424810 | 438f1a | find_mnemonic |
| 4248e0 | 424bf0 | proc_instr |
| 424c50 | 428040 | do_xy |
| 425140 | 405fe0 | parse_xfield_src |
| 4251c0 | 4060d8 | parse_operand |
| 425230 | 4061ae | get_amode |
| 425390 | 406bfa | amode_indirect |
| 4255d0 | 40800f | parse_addr_reg |
| 4255f0 | 408046 | parse_offset_reg |
| 425650 | 4080dc | match_register_name |
| 426210 | 406f87 | amode_immediate |
| 426370 | 407462 | get_imm_expr |
| 426410 | 40758c | amode_absolute |
| 4267d0 | 40641c | amode_register |
| 426b50 | 406938 | note_reg_direct |
| 426b80 | 406aaf | check_dup_dest |
| 426cd0 | 42838d | xy_imm_short |
| 426e50 | 42859c | xy_imm_long |
| 427020 | 4287cc | xy_lreg |
| 427100 | 4288fe | xy_acc |
| 4273b0 | 428cce | xy_xreg |
| 4274e0 | 428e50 | xdst_mem |
| 427b80 | 42b1e5 | chk_move_class |
| 427c20 | 429729 | xy_reg |
| 427f40 | 429b8a | xy_mreg |
| 428070 | 429d39 | xy_ctlreg |
| 4281c0 | 42a096 | xy_xsrc |
| 4286e0 | 42a7d2 | xy_xsrc_acc |
| 428910 | 42aa80 | xy_ysrc |
| 428b40 | 42adb6 | xy_lsrc |
| 428bc0 | 42ae87 | xy_psrc |
| 428cf0 | 42b08d | chk_xy_regs |
| 428df0 | 425340 | p_noarg |
| 428e20 | 42546b | p_rts |
| 428e50 | 425552 | p_andi |
| 428ed0 | 42562d | p_and_or |
| 429080 | 4256e7 | p_alu1 |
| 429110 | 42578d | p_addl |
| 429180 | 4257f4 | p_eor_adc |
| 429220 | 425883 | p_alu2 |
| 4292e0 | 425945 | p_norm |
| 429340 | 425a05 | p_lua |
| 4293a0 | 425a60 | p_div |
| 429400 | 425abb | p_bitop |
| 429540 | 425d15 | p_do |
| 4296e0 | 426106 | p_enddo |
| 429710 | 4261da | p_rep |
| 429800 | 426305 | p_jmp |
| 4298d0 | 42666f | p_jsr |
| 4299a0 | 426a45 | p_jbit |
| 429b00 | 426dc3 | p_tcc |
| 429c10 | 426ee5 | p_mul |
| 429da0 | 427e5d | mulreg |
| 429ea0 | 4270d6 | p_move |
| 429f00 | 42712b | p_movep |
| 42a3c0 | 410950 | enc_andi |
| 42a410 | 43bd1e | insert_bits |
| 42a440 | 410994 | ee_code |
| 42a470 | 4109d7 | enc_div |
| 42a4c0 | 410a2b | d_code |
| 42a4f0 | 410a61 | jjj_code |
| 42a550 | 410acf | enc_norm |
| 42a5b0 | 410b29 | rrr_code |
| 42a640 | 410bcb | enc_loop_ea |
| 42a6c0 | 410c5c | mmm_code |
| 42a750 | 410cfb | s_code |
| 42a760 | 410d0f | enc_loop_abs |
| 42a7a0 | 410d51 | enc_loop_reg |
| 42a7e0 | 410d97 | d6_code |
| 42a870 | 410e44 | ccc_code |
| 42a8e0 | 410ec7 | ddddd_code |
| 42a980 | 410f7f | dd_code |
| 42a9d0 | 411104 | nnn_code |
| 42aa40 | 410fde | ddd_code |
| 42aac0 | 411079 | fff_code |
| 42ab30 | 41118f | enc_loop_imm |
| 42ab80 | 4112b9 | enc_do_ea |
| 42abb0 | 4113ae | enc_do_abs |
| 42abe0 | 4113d5 | enc_do_reg |
| 42ac10 | 4113fc | enc_do_imm |
| 42ac40 | 411423 | enc_jmp_abs |
| 42ac80 | 411457 | enc_jmp_ea |
| 42ad10 | 4112e0 | set_ext_word |
| 42ad40 | 411501 | enc_jcc_abs |
| 42ad80 | 411535 | enc_jcc_ea |
| 42ae10 | 4115dc | enc_tcc_r |
| 42aec0 | 411697 | enc_tcc |
| 42af10 | 4116eb | enc_bit_ea |
| 42afb0 | 4117a2 | enc_bit_reg |
| 42b010 | 4117ff | enc_bit_abs |
| 42b070 | 4119e4 | enc_bit_pp |
| 42b0e0 | 411a18 | enc_jbit_ea |
| 42b110 | 411a43 | enc_jbit_reg |
| 42b180 | 411ab2 | enc_jbit_abs |
| 42b1b0 | 411add | enc_jbit_pp |
| 42b1e0 | 411b08 | enc_movep_reg |
| 42b250 | 411b70 | enc_movep_mem |
| 42b320 | 411c6a | enc_movep_reg_w |
| 42b350 | 411c9e | enc_movep_mem_w |
| 42b380 | 411cd2 | enc_movec_ea |
| 42b440 | 411db2 | enc_movec_ea_w |
| 42b470 | 411de6 | enc_movec_imm |
| 42b4e0 | 411e5a | enc_movec_reg |
| 42b560 | 411edd | enc_movec_reg_w |
| 42b590 | 411f11 | enc_movec_abs |
| 42b610 | 411f93 | enc_movec_abs_w |
| 42b640 | 411fc7 | enc_movec_ea2 |
| 42b700 | 4120a7 | enc_movec_ea2_w |
| 42b730 | 4120db | enc_pm_xy |
| 42b810 | 4121da | xx_code |
| 42b860 | 41223d | yy_code |
| 42b8b0 | 4122a4 | enc_pm_xy_wx |
| 42b8f0 | 4122e0 | enc_pm_xy_wy |
| 42b930 | 41231c | enc_pm_xy_wxy |
| 42b980 | 412370 | enc_pm_xr2 |
| 42ba20 | 412424 | enc_pm_x_ea |
| 42bad0 | 4124fe | enc_pm_x_ea_w |
| 42bb00 | 412532 | enc_pm_y_ea |
| 42bb30 | 412566 | enc_pm_y_ea_w |
| 42bb60 | 41259a | enc_pm_x_abs |
| 42bbd0 | 412616 | enc_pm_x_abs_w |
| 42bc00 | 41264a | enc_pm_y_abs |
| 42bc30 | 41267e | enc_pm_y_abs_w |
| 42bc60 | 4126b2 | enc_pm_ry |
| 42bd40 | 4127b0 | x_code |
| 42bd70 | 4127e6 | enc_pm_ry_w |
| 42bdb0 | 412822 | enc_pm_xr |
| 42be80 | 41290b | y_code |
| 42beb0 | 412941 | enc_pm_xr_w |
| 42bef0 | 41297d | enc_pm_l_abs |
| 42bf50 | 4129d7 | lll_code |
| 42c000 | 412a8f | enc_pm_l_abs_w |
| 42c030 | 412ac3 | enc_pm_l_ea |
| 42c0d0 | 412b7b | enc_pm_l_ea_w |
| 42c100 | 412baf | enc_pm_imm |
| 42c160 | 412c09 | enc_pm_reg |
| 42c1c0 | 412c72 | enc_pm_update |
| 42c230 | 412ce3 | enc_movem_ea |
| 42c2e0 | 412da0 | enc_movem_ea_w |
| 42c310 | 412dd4 | enc_movem_abs |
| 42c360 | 412e1b | enc_movem_abs_w |
| 42c390 | 412e4f | enc_lua |
| 42c400 | 412ecb | enc_mul_imm |
| 42c470 | 412f33 | qq_code |