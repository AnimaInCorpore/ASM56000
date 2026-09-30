# SIM56000.EXE - group exec_a (module "exec", 0x401000-0x40dfff)

Inputs: `re/out/SIM56000/mod/exec.c` (84 decompiled functions in this range), disassembly with
`re/scripts/x86dis.py`, the static device tables in `.data` (dumped with a small python walker).
Names: `re/names/SIM56000/exec_a.names.txt` (84 decompiled functions + 42 functions that Ghidra
did not find, 61 globals).  Confidence tags in the names file: high / med / low.

## 0. What this module really is

`exec` is not "a switch over instructions".  It is a **phase/cycle level hardware model of the
DSP core plus its on-chip peripherals**.  One call of the core clock function
(`core_clock` 0x405b40) advances the pipeline by one machine cycle (or one phase, when called with
`phase_step != 0`); every peripheral has its own `*_clock` function that is called once per cycle
and drives its pins bit by bit.  Everything is state in flat `unsigned long` arrays ("register
files") indexed by small integers; there are no C structs in the modelled hardware.  The
decoder tables (0x42d000-0x430xxx) and the ALU micro-operations (0x433xxx-0x435xxx, `alu_op_tab`
0x4c4eb0) live in neighbouring modules and work on the same register array.

In this address range (0x401000-0x40dfff) the code is, in address order:

| range | content |
|---|---|
| 0x401000-0x401134 | `main` (not exec) |
| 0x401140-0x4013ce | instruction-group statistics methods (igrp_*) |
| 0x401a50-0x403af0 | **EMI #1** peripheral (DSP56004/56004rom: DRAM controller) incl. `emi1_clock` 0x402530 |
| 0x403ae0-0x40a0a0 | **core** (DSP56xxx CPU): register access, reset, `core_clock`, AGU, interrupts, memory bus |
| 0x40a0a0-0x40ad60 | **DAX** peripheral (digital audio transmitter, 56011/56012) |
| 0x40ad60-0x40b280 | **GPIO** peripheral (56004/56007/56009/56011/56012) |
| 0x40b280-0x40d5a0 | **EMI #2** peripheral (56007/56009), near copy of EMI #1 |
| 0x40d5a0-0x40fb00 | **SHI** peripheral (serial host interface SPI/I2C; 56004/56007/56009/56011/56012), `shi_clock` 0x40dd80 |

(sai starts at 0x40feb0 and belongs to exec_b.)

**Ghidra missed 42 functions** in this range: the ones reached only through method tables
(indirect calls).  They are listed with `MISS` in the names file and in section 9.  Their code is
plain (small wrappers), see section 2.4.  They should be created in the Ghidra project and
re-exported before the module is translated.

## 1. Device model (the data the whole simulator hangs on)

Three levels of static tables in `.data` plus one dynamic block per simulated device.

### 1.1 Device type descriptor (`cur_dtype` 0x505790 = `dtype_tab[type]`, table at *0x4aab08, count 0x4aab04 = 13, 10 used)

| off | meaning |
|---|---|
| +0 | name ptr (`"56000"`, `"56001"`, `"56002"`, `"56004"`, `"56004rom"`, `"56005"`, `"56007"`, `"56009"`, `"56011"`, `"56012"`) |
| +8 | **family bit mask** (the code tests it everywhere): 0x1 56000, 0x2 56001, 0x4 56002, 0x8 56004, 0x108 56004rom, 0x44 56005 (bit 0x4 and 0x40), 0x200 56007, 0x400 56009, 0x1000 56011, 0x2000 56012.  Bits 0x10, 0x20, 0x80, 0x800 are tested by exec.c but no shipped type sets them (0x80/0x800 code = dead code of unreleased parts; 0x60 test in some places = 56005 family). Useful groupings seen in the code: `(fam & 3)` = 56000/56001 (old core), `fam < 4` same, `(fam & 0x3618)==0` = "has X/Y/P pin model", `(fam & 0x3678)==0` = boot ROM reset PC ($E000) capable |
| +0xc | 0x4000008 (flags, e.g. bit 0x800 select 16-bit address mask) |
| +0x14 | number of peripheral groups |
| +0x18 | ptr to group array; **element size 0x48** (see 1.2) |
| +0x1c / +0x20 | number of memory regions / region array (**0x2c bytes each**: +0 name ptr ("p","pe","pi","pr","x","xe","xi","xr","y","ye","yi","yr","l","le","li"), +4 space id, +8 class flags, +0xc lo addr, +0x10 hi addr, +0x18 attribute (0x10000 = memory mapped peripheral I/O, 0x8 = read only, 0x20000 = holey), see `FUN_00439080`=`region_lookup(space, addr)`) |
| +0x24 | "DSPMEM" string |
| +0x4c + space*4 | first region index per space |
| +0x4e0 / +0x4e8 | optional hooks (function ptrs), e.g. address mask hook |

Memory **space ids** (from the region table): 0 p, 1 x, 2 y, 3 l (logical spaces),
0x9 le, 0xa li, 0xd pe (P external), 0xe pi (P internal), 0xf pr (P ROM),
0x12 xe, 0x13 xi, 0x14 xr, 0x17 ye, 0x18 yi, 0x19 yr, 0x1c and 0x1d..0x5c (EMI DRAM
banks, see 8), 0x11d (extended P after `core_ext_addr`).  Internal peripheral registers are in
region `xi` 0xffc0-0xffff (56000) and go through `FUN_00456f60/00456fb0` = peripheral I/O
write/read (they dispatch to the group's method slots 3/2).

### 1.2 Group element (0x48 bytes, `cur_dtype+0x18 + g*0x48`) and group definition

Group element (one per peripheral instance; group 0 is always "core"):

| off | meaning |
|---|---|
| +0 | name ptr ("core","host","ssi","sci","portb","portc","timer","count","sai","shi","emi","gpio","wdg","pwm","dax") |
| +4 | **pin block index** (0..6; pin block = 0x128 bytes at `cur_dev+0x18 + idx*0x128`) |
| +8 | pin mask of this group inside that block |
| +0x14, +0x18 | first / count of memory-mapped I/O addresses (ssi 0xffe1 ...) |
| +0x1c | I/O address base (e.g. host 0xffe8, ssi 0xffec, shi 0xfff0, emi 0xffe8) |
| +0x20 | interrupt vector base (returned by `*_m_irq_poll`) |
| +0x28 | interrupt priority (IPR) field mask |
| +0x2c | ptr to **group definition** |

Group definition (`elem+0x2c`), static:

| off | meaning |
|---|---|
| +0x00..+0x1c | **method table, 8 function pointers** (see 2.4) |
| +0x24 | number of storable registers (regs[i] plain store for i < this) |
| +0x28 | number of registers `nreg` |
| +0x2c | ptr to register table, **0x1c bytes per register**: +0 name, +4 write mask (`core_store_reg_masked`: `regs[i] = mask & value`), +8 memory-mapped I/O offset from +0x1c of the element, +0x10 flag word (0x40 = write has side effects: goes through `*_write_reg`; 0x20 = read has side effects; 0x60 tested in `*_touch_reg` = memory mapped, then `FUN_00457de0` refreshes the memory map view), +0x14 display hint ptr, +0x18 register index in group |

Register tables (index = position in `regs[]` of that group; index*4 = byte offset):

* core (48 entries for 56000/56001, 50 for 56002+): 0 A(composite) 1 a0 2 a1 3 a2 4 B(composite) 5 b0 6 b1 7 b2
  8 bcr 9 ipr 10 la 11 lc 12-19 m0..m7 20-27 n0..n7 28 omr 29 pc 30-37 r0..r7 38 sp 39 sr 40 ssh 41 ssl
  42 X(composite) 43 x0 44 x1 45 Y(composite) 46 y0 47 y1 48 gdb 49 pctl (48/49 only 56002+).  Masks: omr 0xc7, sp 0x3f, sr 0xaf7f, ipr 0xfc3f, bcr 0xffff, a2/b2 0xff, all data 0xffffff, addresses 0xffff.
* host cvr hcr hrx hsr htx icr isr ivr rxh rxl rxm txh txl txm (56011/12 use horx/hotx)
* ssi cra crb rx ssisr tsr tx ; sci sccr scr srx ssr stx stxa ; portb pbc pbddr pbd ; portc pcc pcddr pcd
* timer tcr tcsr ; count cnt1..4 cyc eof ictr jump stop ; sai brc rcs rx0 rx1 tcs tx0 tx1 tx2
* shi hckr hcsr hsar hrx htx ; emi ebar0 eor0 edrr0 ecsr ebar1 eor1 edrr1 ercr edwr0 edwr1 ewor
* gpio gpior ; wdg wcsr wcr ; pwm pwacr0-2 pwacsr0-1 pwbcr0-1 pwbcsr0-1 ; dax xadra xadrb xctr xstr

### 1.3 Per-device instance (`cur_dev` 0x505798 = `dev_tab[n]`, `*(int*)cur_dev` = device type index)

| off | meaning |
|---|---|
| +0 | device type index into `dtype_tab` |
| +4 | memory subsystem ptr (`FUN_00458280(dev+4,space,addr,&v,...)` read, `FUN_00458480(...)` write) |
| +8 | array of `regs*` per group (`dev[2][g]` = `unsigned long *regs`); size of a regs array is `group def word 9` dwords (core 0x129 = 297) |
| +0xc | memory map array (0x10 bytes per region: +8 = ptr to word array, element = one 32-bit word per address) |
| +0x18 | pin blocks, 0x128 bytes each: [0] pin inputs (external side; masked reads), [1] second input word/enable, [2] pin output levels, [3] drive/enable mask (see clock functions).  Block 0 = core pins (+0 IRQA=bit0 IRQB=bit1 RESET bit2 MODC bit3, output bit2..., ...), block 1 = address bus, block 4 = data bus, block 6 = GPIO port; peripherals reach theirs through `elem+4` |
| +0x1c | PC of the instruction being executed (written by `core_fetch_decode`, `core_write_reg` pc) |
| +0x20 / +0x24 | +0x24 = executed-instruction counter (`++` when an instruction completes in `core_clock`), +0x20 second counter (both zeroed by `core_reset_pipeline`) |
| +0x40 | ptr to the **cpu control block** (`core_ctl`): +0 pin-input word (IRQ/reset/mode pin state fed by the run loop), +4, +8 (==1: stopped, `core_clock` only runs `FUN_00408510`), +0xc (reset-active latch), +0x10 **phase** |
| +0x44 | event flags for the run loop: 1 = instruction boundary reached / stop, 2 = repeat boundary, 4 = illegal opcode seen ('Illegal Op-Code Encountered'), 8 = register write happened, 0x10 = special instruction (56002+ STOP/WAIT entry) |
| +0x48 | non-zero: suppress instruction-boundary events (single phase stepping) |

### 1.4 Simulator side block (`cur_sim` 0x50578c = `sim_tab[n]`)

+4 per-region reference statistics (0x12c bytes per region: `FUN_00457cc0(space,addr,is_read,pc)` keeps counters at +0x14 / +0xa0 and a 16-entry ring of the last addresses); +8 per-group runtime records (8 bytes/group: +4 = **per-register flag array** `flags[]`, one dword per register of the group); +0x18 "instruction executed" flag; +0x154/+0x158 watch/break tables; +0x3fc0 **trace ring** header (`core_trace`: [0]=count, [1]=head index, [2]=ring buffer, 0x2c bytes per entry {+0 pc, +4 opcode word (regs[0xdc]), +8 second word}, ring size `trace_ring_size` 0x4a8da0); +0x490 = `stats_base` (0x505b64): instruction statistics counters, see 7.

Per-register **flag dword** (`flags[reg]`, used by every `*_touch_reg`):
0x10000|0x40000 (0x50000) = read touched; 0x20000|0x80000 (0xa0000) = written/changed (display refresh marks); 0x400000 = register has an
input-file/pin injection on read (`core_touch_read` -> `FUN_0044bbe0` gets the value, then calls `core_write_reg`); 0x800000/0x1000000 (mask 0x1800000) = watch/break-on-change is set: `FUN_00449a70(dev, reg)` fires (display/log).

### 1.5 Per-peripheral context globals (the "prologue")

Every method entry copies the device pointers into globals so the helpers can be argument free.
Layout is the same for each peripheral (7 dwords, consecutive):

`[+0] cpu ctl (only set in the clock method)  [+4] regs  [+8] group element  [+0xc] flags  [+0x10] &dev[2][g]  [+0x14] itype aux (cur_itype[2][g])  [+0x18] sim group runtime record`

| peripheral | globals |
|---|---|
| EMI #1 | 0x4dbbec..0x4dbc04 |
| core | 0x4dbc08 pin block 6 (GPIO pins, only if fam&0x800), 0x4dbc0c ctl, 0x4dbc10 regs, 0x4dbc14 grp, 0x4dbc18 flags, 0x4dbc1c pin block 1 (address bus), 0x4dbc20 pin block 4 (data bus), 0x4dbc24 pin block 0, 0x4dbc28 &regs slot, 0x4dbc2c aux, 0x4dbc30 runtime, 0x4dbc34 trace ring |
| DAX | 0x4dbc38..0x4dbc50 |
| GPIO | 0x4dbc54 regs, 0x4dbc58 grp, 0x4dbc5c flags (+ slot/aux/runtime after) |
| EMI #2 | 0x4dbc6c ctl, 0x4dbc70/74 regs (two copies), 0x4dbc78 grp, 0x4dbc7c flags, 0x4dbc80..88 |
| SHI | 0x4dbc8c ctl, 0x4dbc90 regs, 0x4dbc94 grp, 0x4dbc98 flags, ... |

The translator can replace all this by one `struct periph_ctx` passed explicitly.

## 2. Method tables

### 2.1 The eight slots (group definition +0x00..+0x1c)

| slot | name | signature (from the code) | job |
|---|---|---|---|
| 0 | peek | `int (int dev_or_grp, int reg, ulong *out)` | debugger read of register (default = shared `0x4132b0`: `*out = dev[2][grp][reg]`; core has its own `core_m_peek` 0x403ae0 that also returns the composite regs A/B/X/Y as 3/2 words) |
| 1 | poke | `int (grp, reg, ulong *val)` | debugger write; registers with flag 0x40 go through `*_write_reg` (masks, side effects) and then `*_touch_reg` |
| 2 | io_read | `int (grp, addr, ulong *out, int side)` | memory mapped I/O read (address relative to elem+0x1c); calls `*_read_reg(reg,out,side)` |
| 3 | io_write | `int (grp, addr, ulong val)` | memory mapped I/O write; calls `*_write_reg` |
| 4 | clock | `void (grp[,dev])` | **one machine cycle**; loads the context globals, then calls `*_clock` |
| 5 | reset | `void (grp, kind, pinval)` | kind 1 = hard reset, 2 = RESET instruction, 0 = STOP/WAIT entry (see `FUN_00436b30`) |
| 6 | irq_poll | `int (grp)` | returns the vector address (elem+0x20 + n) of the highest pending peripheral interrupt or -1 |
| 7 | irq_ack | `void (grp, vec)` | clears the pending request for that vector |

`FUN_00436b30(kind,pinval)` loops over all groups and calls slot 5.  Core's `core_irq_arbitrate` calls slot 6 of
every group >= 1, `core_irq_ack` slot 7.

### 2.2 Instruction-group descriptor (`cur_itype+0x18`, static at 0x4ad360, one per device type family)

+0 number of groups (9), +4 0x66, +8 group names, +0xc mode-name table, +0x10 `igrp_map_kind` (0x401140),
+0x14 `igrp_names_hook` (0x401250 -> 0x41cd00), +0x18 `igrp_fill_mode_names` (0x401260), +0x1c `igrp_count_instr` (0x401380).

### 2.3 Slot addresses per group (all in this range)

| group | peek | poke | io_read | io_write | clock | reset | irq_poll | irq_ack |
|---|---|---|---|---|---|---|---|---|
| core | 403ae0 | 403c50 | 404480 | 4042f0 | 403f70 | 404040 | - | 404130 |
| emi (56004) | 4132b0 | 401a50 | 401da0 | 401c70 | 401be0 | 401eb0 | 401fc0 | 402010 |
| dax | 4132b0 | 40a0a0 | 40a2d0 | 40a1f0 | 40a170 | 40a380 | 40a460 | 40a4c0 |
| gpio | 40ad60 | 40adb0 | 40aed0 | 40ae50 | 40ae40 (empty) | 40af60 | - | - |
| emi (56007/9) | 4132b0 | 40b280 | 40b5d0 | 40b4a0 | 40b410 | 40b6e0 | 40b7f0 | 40b860 |
| shi | 4132b0 | 40d5a0 | 40d7d0 | 40d6f0 | 40d670 | 40d890 | 40d9a0 | 40da20 |

### 2.4 The undecompiled wrappers (all follow the same pattern)

`*_m_clock(g)`: load the 7 context globals (see 1.5), call `*_clock`.  `*_m_poke(g,reg,ulong*val)`: `if (reg < nreg && table[reg].flag & 0x40) { *_write_reg(reg,*val); *_touch_reg(reg) } else { if (reg < def[0x24]) regs[reg] = *val; *_touch_reg(reg) } return 1`.
`*_m_io_write(g,addr,val)`: `reg = (addr - elem[0x1c])` mapped through a small switch to the register index (e.g. dax: base+0 -> reg 0 (or 1 depending on `regs[0x38]`), base+2 -> 2, base+3 -> 3, 0xffff -> 0xd) then `*_write_reg`.  `*_m_io_read` same with `*_read_reg(reg,out,side)`.
`*_m_reset(g)`: zero shadow registers (dax: `dax_reset_regs`), `*_m_irq_poll`: `if pending flag(s) in regs[0x34/0x28/0x2c/0x30] return elem[0x20] + {0,2,6}`; `*_m_irq_ack` clears the flag.
`core_m_io_read/io_write` map addresses 0xffe6..0xffff to core registers: 0xffff ipr(9), 0xfffe bcr(8), 0xfffd pctl (0x31, family & 0x38ec), 0xffec/0xffed regs 0x33/0x32 (only fam&0x80, bit 0x100 of reg 0x32 preserved), then `core_get_reg` / `core_store_reg_masked` (0x4045f0).
`core_m_reset(dev,_,kind,pinval)`: `if (pinval >= 0) core_ctl[0] = pinval; if (kind==1) core_reset(); core_reset_io(kind)`.
`core_m_irq_ack(dev,vec)`: `vec-2` (0..0x3c) indexes a switch: 2 clear stack-error request (regs[0x408]), 4 trace (0x40c), 6 swi (0x410), 8 IRQA (0x414 and edge latch 0x2d0), 0xa IRQB (0x418/0x2d4), 0x2c IRQC (0x444/0x42c), 0x2e IRQD (0x448/0x430), 0x1e NMI (0x400; fam&0x60 also asks group 7 slot 6/7), 0x3e illegal (0x404).

## 3. Core register array (`core_regs`, 0x129 dwords = 0x4a4 bytes; byte offset shown; index = offset/4)

Convention in this whole note: `regs[0xNN]` (hex) always means the **byte offset** 0xNN into the array, i.e. the dword `((unsigned long *)regs)[0xNN/4]`, exactly as the decompiled `*(uint *)(regs + 0xNN)`.

All visible registers use the group-0 table above (offsets 0x00-0xc7).  Everything above is
internal hardware state ("wires" and latches).  Confidence: [H] verified by several uses, [M] inferred from one function.

| offset | name | meaning |
|---|---|---|
| 0x04,0x08,0x0c | a0 a1 a2 | accumulator A (a2 is 8 bit sign extension) [H]; `regs[0]` (A composite) has no storage |
| 0x14,0x18,0x1c | b0 b1 b2 | accumulator B [H] |
| 0x20 bcr, 0x24 ipr, 0x28 la, 0x2c lc | | bcr wait-state control, ipr interrupt priorities (IRQA level = ipr&3, IRQA mode bit 2, IRQB (ipr>>3)&3 / bit 5, IRQC (>>6)&3, IRQD (>>8)&3) [H] |
| 0x30-0x4c m0..m7, 0x50-0x6c n0..n7, 0x78-0x94 r0..r7 | | AGU registers [H] |
| 0x70 omr, 0x74 pc, 0x98 sp, 0x9c sr, 0xa0 ssh, 0xa4 ssl | | SR bit use in this range: C=bit0 V=1 Z=2 N=3 U=4 E=5 L=6 S=7, I0/I1=bits 8,9 (interrupt mask, compared with the level in `core_irq_arbitrate`), S0/S1=bits 10,11 (scaling), T (trace)=bit 13 (`regs[0x27c]=sr&0x2000`), LF (loop flag)=bit 15 (0x8000) [H]. SP: bits 0-3 = stack index (0 = empty; SSH/SSL arrays 1..15), bit 4 = stack error, `core_touch_reg_ex` case 0x26 latches it into `regs[0x2a0]` and raises exception request `regs[0x408]` [H] |
| 0xac x0, 0xb0 x1, 0xb8 y0, 0xbc y1 | | data regs; 0xa8/0xb4 are the composite X/Y (no storage) [H] |
| 0xc0 gdb, 0xc4 pctl | | 56002+ only; pctl reset value 0x1f3 (499), or `(pins>>7 & 0x2000000 | 0xd80)>>7`, or `pins >>7 & 0x40000` depending on family [M] |
| 0xc8 (idx 0x32) | | family 0x80 control (unreleased) [M] |
| 0xcc (0x33) | | high byte source for `core_ext_addr`: `((regs[0xcc]&0xff00)<<8)|addr` [M] |
| 0xd0-0xd8, 0xf0-0x104 | | family 0x80/0x800 timers/counters (unreleased parts) [M] |
| 0xdc | ir | **instruction register** (24-bit opcode word being decoded; byte 0xdd used) [H] |
| 0x11c, 0x120 | agu_out_lo, agu_out_hi | result of the AGU calculation for bank R0-R3 / R4-R7 (idx 0x47/0x48) [H] |
| 0x124/0x128 | agu_m_lo/hi | latched Mn for bank (idx 0x49/0x4a) [H] |
| 0x12c/0x130 | agu_n_lo/hi | latched Nn (0x4b/0x4c) [H] |
| 0x134/0x138 | agu_r_lo/hi | latched Rn (0x4d/0x4e) [H] |
| 0x13c xab, 0x140 yab, 0x144 pab | | address buses [H] |
| 0x148 xdb, 0x14c ydb, 0x150 pdb, 0x154 gdb, 0x158 (idx 0x56, "none", also LF source in `core_do_loop_end`), 0x15c (0x57 temp) | | data buses; **bus index constants** used as `dst`/`src` in `core_read_to_bus`, `core_ss_push/pop`: 0x52 xdb, 0x53 ydb, 0x54 pdb, 0x55 gdb, 0x56 none, 0x57 temp [H] |
| 0x160, 0x164 | ea_field_a/b | MMMRRR addressing field latches from IR (`IR>>8&0x3f`) [M] |
| 0x168, 0x16c, 0x170 | | PC pipeline: 0x16c = fetch PC, 0x170 = next fetch, 0x168 saved [M] |
| 0x174/0x178/0x17c | next_pab/xab/yab | address selected for the next cycle (AGU result or PC+1 mux) [M] |
| 0x180 | idb | internal data bus / operand value (bit ops, cc, moves) [H] |
| 0x184, 0x188, 0x18c | ir_ex, ir_id, ir_if | IR pipeline copies (0xdc -> 0x188 -> 0x184 -> 0x18c) [H] |
| 0x194/0x198/0x19c/0x1a0/0x1a4 | | pseudo-registers 0x65-0x69: return-address / vector latches used by `core_ss_push` (idx 0x66 0x67 0x69) [M] |
| 0x1a8 | ir2 | second word (extension word) latch [M] |
| 0x1ac | imm | short immediate / short absolute extracted from IR (fields depend on `regs[0x1ec]` code) [M] |
| 0x1b0, 0x2bc | omr_prev, omr_next | change detection -> calls `dtype+0x28+0x10` callback (`(*(fn*)(cur_dtype[0x28]+0x10))(omr)`) [M] |
| 0x1b4 | lc_save | [M] |
| 0x1b8-0x1cc | alu_desc | 6 dwords filled by `FUN_00433ce0(ir, &regs[0x1b8])`: [0] micro-op id -> `alu_op_tab[id]` call in `FUN_00433c80`, [1] state (1 new, 2 running), [2] src code, [3] second code, [4] dest (0x12c/0x12d = A/B limited), [5] flag [M] |
| 0x1d0 | agu_ctl | AGU/move control word from decode table (bits 0x1/0x2/0x4 R update, 0x10/0x20 latch, 0x40/0x80 select, 0x100..0x2000 bank routing) [M] |
| 0x1d4 | cc | condition code field (4 bit) of Jcc/Tcc/... [H] |
| 0x1d8 | instr_valid | copy of `regs[0x274]` [M] |
| 0x1dc | bitop_pending | set by fetch, cleared once `core_bit_op` ran [M] |
| 0x1e0 | trace_state | 0/1/2 counting trace entry completion [M] |
| 0x1e4 | irq_needed | interrupt pending, service at instruction boundary [M] |
| 0x1ec-0x208 | dec_moves[8] | outputs of `FUN_0042eec0` (parallel-move decode): 0x1fc code, 0x200 type, 0x204, 0x208 flags, 0x1f4 dest class... [M] |
| 0x20c, 0x210 | ea_x, ea_y | MMMRRR fields of first/second parallel move [H] |
| 0x214 | ir_copy | IR copy for bit-op decode: `regs[0x2cc]=ir&0x1f` (bit number), `regs[0x2c8]=(ir>>5)&1 | (ir&0x10000?2:0)` (op type) [H] |
| 0x218, 0x21c, 0x220 | dec_ctl[3] | outputs of `FUN_0042f2a0`: control bit masks for sequencing (0x218 bit0 DO/REP..., 0x21c 0x100 latch A, 0x200, 0x2000 RTS/RTI, bit 8 ...) [M] |
| 0x224..0x264 | sequencer state | 0x228 index of the pseudo-register holding the return PC (0x66 0x67 0x68 0x69), 0x22c PAB==LA, 0x230 LC==1, 0x234 instruction "executes" flag (cc true), 0x238/0x258 loop-end conditions, 0x23c loop-end pending, 0x240 0x244 0x248 (start-up cycles counter, decremented at end of `core_clock`), 0x24c flush, 0x250 IR strobe, 0x254, 0x25c shift register of loop states, 0x260, 0x264 (in REP/DO), 0x268 cancelled by cc [M] |
| 0x26c, 0x270 | move ctl | 0x270 = bit mask of pending bus transfers for this instruction: bit0 read src1 -> X? ... (0x1 xdb-from-reg, 0x2, 0x4 pdb, 0x8 x write, 0x10 y write, 0x20 gdb write, 0x100..0x2000 "value comes from idb" variants) [M] |
| 0x274 | fetch_valid | [M] |
| 0x278 | trace_pending | (`regs[0x288] && 0x21c&4 && !rep`), raises vector 4 [H] |
| 0x27c | trace_bit | `sr & 0x2000` [H] |
| 0x280, 0x284, 0x288 | | trace/step helpers [M] |
| 0x28c | rti_pending | after an interrupt return, restore SR (`core_ss_pop(0x69,0x27)`) [M] |
| 0x290, 0x294, 0x298, 0x29c | regsel | **register select numbers** (index into `regsel_tab` 0x4b2748 -> register index): 0x290 gdb-side, 0x294 x-source/dest, 0x298 y dest, 0x29c y source [H] |
| 0x2a0 | stack_err_latch | [H] |
| 0x2a4-0x2b0 | dec2 | copies of decode fields: 0x2a4=(0x1d0>>1)&3, 0x2a8=regs[0x1f8], 0x2ac=sequencer state, **0x2b0 = control opcode class** (0xe = STOP/WAIT class, 0xc, ...) [M] |
| 0x2b4 | insn_flags | instruction class bit mask from `FUN_0042fe10`: 0x1 STOP/WAIT class, 0x2, 0x10 RESET, 0x20/0x40 (or/and with regsel), 0x80|0x8000 stack-push kinds (do/jsr), 0x100 REP, 0x200 conditional (Jcc), 0x800 multi-word [M] |
| 0x2b8 | nmi_latch | level triggered request latch [M] |
| 0x2c4, 0x2f0, 0x2f4 | run state | 0x2f4 = **core halted** (reset/wait/stop), 0x2f0 bus grant/hold, 0x2c4 = halted && bus free [M] |
| 0x2c8, 0x2cc | bit op | see 0x214 [H] |
| 0x2d0..0x2ec | pins | IRQA/IRQB edge latches (0x2d0, 0x2d4), synchronizers (0x2d8, 0x2dc), chosen level `0x2e0`, pins 0x2e4 IRQA, 0x2e8 IRQB, 0x2ec reset (active low) [H] |
| 0x2f8..0x334 (idx 0xbe+sp) | ssh[0..15] | system stack high (PC) [H] |
| 0x348..0x384 (idx 0xd2+sp) | ssl[0..15] | system stack low (SR) [H] |
| 0x398..0x3bc | bus cycle control | 0x398 P access, 0x39c X access, 0x3a0 Y access, 0x3a4/0x3a8/0x3ac/0x3b0/0x3b4 derived read/write phases, **0x3b8 read strobes (bit0 X, bit1 Y, bit2 P), 0x3bc write strobes** [H] |
| 0x3c0 | wait_states | down counter; per-space wait cycles from `bcr` (`bcr>>12`, `>>8&0xf`, `&0xf`, `>>4&0xf`) [H] |
| 0x3c4 | irq_group | group index of the winning peripheral interrupt [H] |
| 0x3c8 | irq_pending | result of `core_irq_arbitrate` [H] |
| 0x3cc | irq_take | interrupt taken, `core_irq_ack` due next cycle [H] |
| 0x3d0, 0x3d4, 0x3d8 | irq_seq | interrupt sequencer state (0 idle, 1 wait for fetch, 2, 4, 8, 0xc) and cycle count (fast interrupt = 6 cycles) [M] |
| 0x3dc, 0x3e0 | | long-interrupt / instruction-finished strobes [M] |
| 0x3e4 | vector | interrupt vector address chosen [H] |
| 0x3e8, 0x3ec, 0x3f0, 0x3f4 | space | 0x3ec/0x3f0/0x3f4 = memory space ids returned by `FUN_0042d4c0(1|2|0, XAB|YAB|PAB)` for X/Y/P, 0x3e8 bit0/1/2 set if that access is **not** on the pins (internal or ROM) [H] |
| 0x400 NMI, 0x404 illegal, 0x408 stack error, 0x40c trace, 0x410 swi | exception requests (non-zero = pending) [H] |
| 0x414 IRQA req level, 0x418 IRQB, 0x41c/0x420 IRQA/B ipl from ipr, 0x424 executing, 0x428 REP active, 0x42c..0x450 IRQC/IRQD equivalents | [H/M] |
| 0x468-0x488 | alu latches | operands/results of the ALU micro-ops (module 0x433xxx): 0x468/46c/470 accumulator source 56-bit (lo/mid/ext), 0x474/478/47c shifted, 0x480/484/488 result [M] |
| 0x498/0x49c/0x4a0 | tmp_a0/a1/a2 | scratch copy of an accumulator used by `core_read_to_bus` (limiter/scaler) [H] |

## 4. Core clock (`core_clock` 0x405b40) - the phase machine

`core_clock(int phase_step)`.  Phase variable: `core_ctl[+0x10]`.

* 0x101 = start of the instruction cycle (execute part), 0x102 = second half / stall handling,
  0x108 = end of cycle (pin sampling), 0x118 = wait-state cycle, 0x100202/0x100204/0x100205/0x100210/0x100220/0x100280: same points but entered with the "single phase" bit 0x100000 when `phase_step != 0` (the function returns after `core_sample_pins` so the caller can step peripherals per phase).
* Start: if `core_ctl[8]==1` (stopped): notify `FUN_00436b30(1,pins)` and only sample pins.  Then two tiny down counters `regs[0xf0]`/`regs[0xfc]` (family 0x80).
* 0x101: bookkeeping for STOP/WAIT/RESET (`regs[0x2b4]&0x10` -> `FUN_00436b30(2,-1)`), interrupt/exception request latches (0x404 0x410 vs `regs[0x2b4]&0x80/0x8000`), run `core_cc_test(regs[0x1d4])` (or `core_bit_test`) to decide whether the instruction executes (`regs[0x234]`), update LA/LC loop state (`regs[0x22c]` PAB==LA, `regs[0x230]` LC==1), decrement LC (`core_set_reg(11,...)`), run `core_fetch_decode` (0x405000), execute stage: memory reads/writes on X/Y/P through `core_mem_read/core_mem_write` with strobes 0x3b8/0x3bc, register transfers through `core_read_to_bus(src,bus)` / `core_write_from_bus(src,dst)`, stack push/pop for do/jsr/rti/interrupt, `core_do_loop_end` at the last loop instruction, decode of the next instruction (`core_decode_ctl`), then sets phase and calls `core_sample_pins` (0x408510).
* Interrupt handling (fast/long) is done by the sequencer `regs[0x3d0]`: `core_irq_arbitrate` picks the vector each cycle, the interrupt injects a JSR/two-word fetch (regs[0x228] = 0x66/0x67/0x68/0x69 pseudo return address latches).
* Trace: each fetched instruction is appended to the trace ring (`core_fetch_decode`), the instruction counter `cur_dev[9]` is bumped when an instruction completes (end of `core_clock`), `cur_dev[0x11]` (offset 0x44) bit 0/1 tells the run loop.
* Stalls: `regs[0x3c0]` wait-state counter, each cycle `FUN_00449200(&DAT_004b3424)` (adds a wait cycle to the statistics).

### 4.1 Instruction decode / execute dispatch

There is **no per-opcode switch in exec.c**.  Decoding is table driven and lives in
`FUN_0042d4c0` (space selection), `FUN_0042eec0` (parallel-move decode; returns ptr into `0x4c2bb0 + n*0x20`,
uses `FUN_00430740` + jump table `0x4c36f0`), `FUN_0042f2a0`, `FUN_0042fdb0`, `FUN_0042fe10`, `FUN_00430850`
(illegal-opcode check: non-zero -> `cur_dev[0x44] |= 4`, the instruction is replaced by NOP `regs[0xdc]=0` unless the result is 2).
`core_fetch_decode` (0x405000) stores the results in `regs[0x1ec-0x208]`, `regs[0x1d0]`, `regs[0x218-0x220]`, `regs[0x2b4]`, splits IR into fields (`regs[0x160/164]`, `regs[0x2c8/2cc]`), then `core_decode_ctl` (0x405440) turns them into the bus/register selects (`regs[0x290-0x29c]`) and move control bits `regs[0x270]`, derived strobes `regs[0x398-0x3bc]`.
The ALU part: `FUN_00433ce0(ir_alu_field,&regs[0x1b8])` selects micro-op id/operands, `FUN_00433c80(regs)` calls `(*alu_op_tab[regs[0x1b8/4]])()` (table at 0x4c4eb0); the micro-ops read/write the ALU latches (0x468-0x488) and the local copy of SR (`DAT_004dc13c`) which is written back with `core_touch_reg(0x27)`.  These functions belong to the adjacent module (0x433xxx); they are the only place with the 56-bit add/sub/mac and the CCR flag equations.

### 4.2 Address generation unit

`core_agu_setup(ea, latch)` (0x409170): `ea` = MMMRRR (bits 0-2 Rn, bits 3-5 mode).  `ea == 0x30 || ea == 0x34` (immediate/absolute) does nothing.  Otherwise picks bank 0 (R0-R3) or 1 (R4-R7), copies R/M/N into the bank latches (`core_read_copy(0x1e+n -> 0x4d/0x4e)`, `0xc+n -> 0x49/0x4a`, `0x14+n -> 0x4b/0x4c`; with `latch==0` it copies the raw registers directly), then `core_agu_calc(mode,n)`.
`core_agu_calc(mode, n)` (0x409230), mode numbers of the 56000 MMM field:
* 0 (Rn)-Nn (subtract N), 1 (Rn)+Nn, 2 (Rn)- (-1), 3 (Rn)+ (+1), 4 (Rn) (no change), 5 (Rn+Nn) (adds N, result not written back), 7 -(Rn) (-1).
* M == 0: **reverse-carry**: `bit_reverse16` (0x409440, via the 16 entry mask table `bit_mask_tab` 0x4aab18, entry n = 1<<n) applied to R, offset and result.
* M == 0xffff: linear (natural 16-bit wrap); other M: **modulo** with modulus M+1: find the highest set bit of M in `bit_mask_tab`, `wrap_mask = agu_wrap_mask_tab[bit]` (0x4b2898), the sum is corrected once by +/- modulus when it leaves the window; for family >= 56002 and `(M & 0xc000)==0x8000` (multiple wrap-around modulo) the result is `(M&0x7fff & sum) | (R & ~(M&0x7fff))`.
Result goes to `agu_out_lo/hi`; write-back to Rn happens in `core_agu_writeback` (0x409470) for modes 0-3,7.

## 5. 56-bit accumulator / CCR semantics visible in this range

Data ALU proper: see 4.1 (not in this range).  What exec_a itself implements:

* **Accumulator storage**: A = {a2 (8 bit), a1 (24), a0 (24)}, B likewise; registers 0/4 are read as 3-word composites by `core_m_peek`.
* **Reading an accumulator onto a bus with scaling and limiting** (`core_read_to_bus(src,dst)` 0x408d20), pseudo sources 0x12a..0x12d:
  * 0x12a/0x12b = A10/B10 (two words to xdb+ydb = regs 0x52/0x53, "long move"), 0x12c/0x12d = A/B single word (a1 limited).
  * Copy a0,a1,a2 into scratch 0x498/0x49c/0x4a0.  Scaling by SR S1S0 (`sr & 0xc00`): 0x400 = scale down (`a1' = a1>>1 | (a2&1)<<23`, `a0' = a0>>1 | (a1&1)<<23`, `a2' = a2>>1` with bit 8 replicated if bit 6 set, i.e. `a2 = (a2>>1) | (a2&0x40 ? 0x180)`), 0x800 = scale up (`a1' = a1<<1 | a0>>23`, `a2' = a2<<1 | carry`), 0 = none.
  * **Limiter**: after scaling with 9 bit extension `e = a2'`: `e == 0` -> positive, overflow if `a1' >= 0x800000` (limit to 0x7fffff, set **L** (SR bit 6, `sr | 0x40`, sticky); `e == 0x1ff` -> negative, overflow if `a1' < 0x800000` (limit to 0x800000, set L); any other `e` -> overflow: value `0x800000` if `e > 0xff` else `0x7fffff`, set L.  For long moves the low word becomes 0xffffff / 0 accordingly.
  * Family >= 56002: if `(a1 & 0x600000)` is `0x400000` or `0x200000` (bits 22,21 differ) and the destination is xdb/ydb (0x52/0x53) then **S (SR bit 7)** is set (`sr | 0x80`) before limiting.
  * Non-accumulator sources: plain copy; **a2/b2 (idx 3, 7) are sign extended** on the bus: if bit 7 of the byte is set the value gets `| 0xffff00`.
* `core_write_from_bus(src,dst)` (0x409dd0): writing to A/B pseudo destinations 0x12a..0x12d (A10, B10, A, B): a2 = sign of bit 23 of the written word (`0xff` or 0), a1 = word, a0 = 0 (or the second word for the 48 bit forms; `dst == 0x53` copies ydb into a0).
* **Condition codes** `core_cc_test(cc)` (0x408a30, 16 entries, bits of SR: C=1 V=2 Z=4 N=8 U=0x10 E=0x20 L=0x40): 0 CC `!C`; 1 GE `!(N^V)`; 2 NE `!Z`; 3 PL `!N`; 4 NN `!(Z | (!U & !E))` (code: `sr&4==0 && sr&0x30 != 0`), 5 EC `!E`; 6 LC `!L`; 7 GT `!(Z | (N^V))`; 8 CS `C`; 9 LT `N^V`; 10 EQ `Z`; 11 MI `N`; 12 NR `Z | (!U & !E)`; 13 ES `E`; 14 LS `L`; 15 LE `Z | (N^V)`.
* Bit manipulation instructions: `core_bit_test()` = `(bit_mask_tab[regs[0x2cc]] & regs[0x180]) != 0`, `core_bit_test_not()` inverse (choice by `regs[0x2c8]&1`), `core_bit_op()` sets SR.C from the tested bit (`sr = sr&~1 | bit`) and then modifies the operand value in `regs[0x180]` by `regs[0x2c8]` (0 clear = `&= ~mask`, 1 set = `|= mask`, 2 change = clear if bit was set else set) then `core_touch_reg(0x27)`.
* **System stack**: SP = `regs[0x26]`; `core_ss_push(ssh_src, ssl_src)` (0x408bd0): `SP+1` (bit 4 flags the overflow; when the flag is set the index wraps within 4 bits keeping bits 4,5), `core_touch_reg(0x26)`, `ssh[sp] = regs[ssh_src] & 0xffff`, `ssl[sp] = regs[ssl_src] & 0xffff` (0x56 = "none" source skips that half), touch 0x28/0x29.  `core_ss_pop(ssh_dst, ssl_dst)` (0x408c70): reads ssh/ssl[sp] (0 when sp==0), `core_ss_dec` (0x408b80) decrements `SP` (`(sp&0xf)-1`, keeps flag bits 4-5 when bit 4 set).  `core_do_loop_end` (0x409f20) = pop of the DO frame: `core_ss_pop(0x57,0x56)` + dec, restores LF: `sr = sr&~0x8000 | regs[0x158]&0x8000`, then `core_ss_pop(la,lc)` + dec and touches 0xa/0xb (LA/LC restored).
* **Interrupt arbitration** `core_irq_scan` (0x4098a0) returns the vector address of the highest priority source, in this fixed order: illegal (0x404 -> 0x3e), NMI (0x400 -> 0x1e), stack error (0x408 -> 2), trace (0x40c -> 4), swi (0x410 -> 6), then IRQA (level `regs[0x414]`, vec 8), IRQB (`0x418`, vec 0xa), for fam&0x60 also IRQC/IRQD (`0x444`, `0x448`, vec 0x2c/0x2e), else -1; each IRQ level is 0 (masked) 1..3 from ipr, level-vs-edge selected by ipr bits 2/5.  `core_irq_arbitrate` (0x409750) additionally polls slot 6 of all peripheral groups (level = `(elem[0x28] & regs[0x24]) / lowest_set_bit(elem[0x28])`, i.e. IPL field of ipr) and takes the highest level that is greater than SR I1:I0 (`(sr>>8)&3 < level`), stores `regs[0x2e0]=level`, `regs[0x3e4]=vector`, `regs[0x3c4]=group`.

## 6. Core register access API (used by the debugger commands and by every helper)

* `core_write_reg(dev, reg, ulong *val)` (0x403c50) = slot 1.  Builds the context (the "prologue" listed in 1.5), then: reg 0 writes A = {val[0]->regs[1], val[1]->regs[2], val[2]->regs[3]}; reg 4 writes B; 0x2a X = {regs[0x2b], regs[0x2c]}; 0x2d Y; reg 0x1c omr (`|4` if fam&8; also `regs[0x1b0]=regs[0x2bc]=v`, callback); 0x1d pc: clears `sim[0x24]`, `regs[0x144]=regs[0x16c]=...` and runs `core_reset_pipeline`, `core_ctl[+0x10]=0x101`; 0x1e-0x21 and 0x22-0x25: r/n views ... (`regs[0x11c]`/`[0x120]` AGU latches); 0x28/0x29 write SSH/SSL at `sp` (needs sp != 0: `param_2 = sp + 0xbe / 0xd2`); reg with region attribute 0x40 is a memory mapped location (`FUN_00456f60`).  Otherwise `regs[reg] = value & 0xffffff` and `core_touch_reg`.
* `core_touch_reg_ex(reg, quiet)` (0x4046a0): for regs 1-3/5-7/0x2b/0x2c/0x2e/0x2f also marks the composite A/B/X/Y register (index 0/4/0x2a/0x2d) changed; re-applies the write mask; special reactions: reg 9 (ipr) recomputes edge latches (`0x2d0`, `0x2d4` cleared if IRQ mode is level), 0x1d (pc) `dev[0x44] |= 8`, 0x26 (sp) stack-error latch (see 3), 0x32 (family 0x80) forces bit 8; then flags, breakpoints (`FUN_00449a70`) and memory map refresh.
* `core_reset` (0x404ad0): M0-M7 = 0xffff, N/R untouched, BCR (via `FUN_00456f60(0xfffe,0xffff)`), SR = 0x300 (interrupts masked), SP = 0, omr from mode pins (`*core_ctl & 3`, MC->0x10 for fam>=4, `|4` for fam&8), pctl (fam&0x38ec), PC = 0 or 0xe000 (for fam 56000/1/2 when `(omr&0x13)==2`: boot from ROM), pin defaults (`core_pins[2/3]` OR/AND masks: address/data bus tri-stated `0x106fa00`).  `core_reset_pipeline` (0x404e30): clears all sequencer state (0x244 ... 0x428), `regs[0x170]=regs[0x144]`, PC latches = reset vector, `core_ctl[+0x10]=0x101`, trace ring reset, then `core_fetch_decode` + `core_decode_ctl`.
* `core_mem_read/core_mem_write(space, addr, ulong *data, strobe)` (0x409b40/0x409530): `space` = 0x12/0x17 (external X/Y) and 0xd (external P) go to the pin model (address/data pin blocks 1 and 4, `core_ext_addr_match` = does the extended-address/`regs[0xc8]` (fam 0x80) decode select it), 0x13/0xe/0x18 (internal RAM/ROM) index the region word array `dev[3][region*4+2][addr - lo]`; region attribute 0x10000 (X:$FFC0-$FFFF) is peripheral I/O (`FUN_00456fb0` read / `FUN_00456f60` write).  Every access calls `FUN_00457cc0` (region reference statistics with `regs[0x180]`/pc), watch hook `FUN_00448b60` and, if `PTR_DAT_004a8dc8 != 0`, the memory-access logger `FUN_00459140`.  `strobe` is compared with `regs[0x270]` bits: if `regs[0x270] & strobe` the value comes from the internal data bus `regs[0x180]` instead of the pins (for moves that are fed by an ALU result).

## 7. Instruction statistics (`igrp_*`, 0x401140-0x4016c9)

Called from the run loop after each executed instruction (through `cur_itype+0x18`+0x1c), argument = decoded instruction record `rec` (built by the asm/decode layer, see also run.c/stats.c).

Record fields used: +0x10 instruction kind id (mnemonic table index), +0x14 first operand mode, +0x30 second operand mode, +0x84 list of parallel moves (singly linked: +4 next, +8 ptr to move record with +0 source mode, +0x1c destination mode), +0x88 == 0x10 flags long form.

* `igrp_map_kind(rec)` (0x401140): remaps kinds for the control group: kind 0x10/0x14/0x2b/0x2c -> 0x5f/0x60/0x61/0x62 unless `rec[0x88]==0x10`; 0x49->0x48, 0x4b->0x4a, 0x4f->0x4e, 0x51->0x50; 0 stays 0.
* `igrp_count_instr(rec)` (0x401380): maps kind to one of 9 **instruction groups** (names: 0 Multiplication (mac,mpy,macr,mpyr), 1 Arithmetic/Logic, 2 Bit manipulation, 3 Bit field & Multi-bit shift, 4 Bit control (jclr..), 5 Control (jmp,jsr,jcc,jscc), 6 Loop (do), 7 Move source, 8 Move target) and increments `stats_base[0x2fe0/4 + group*16 + 0]` (group total) and `[... + bucket]` (operand mode).  Counter block = `stats_base + 0x2fe0` (dwords), 16 dwords per group, entry 0 = group total, entry `bucket` = per operand mode.  Kind -> group: 0x40 0x48 0x4a 0x4e 0x50 -> 0 (uses mode +0x30); 0x33 0x36 0x3b 0x41 0x55 0x5a -> 1 (+0x14); 2 3 5 6 -> 2 (+0x30); 0x37 0x38 0x42 0x43 0x45 -> 3 (+0x14); 0x11 0x12 0x13 0x15 0x2d-0x30 -> 4 (+0x30); 0x10 0x14 0x2b 0x2c 0x5f-0x62 -> 5 (+0x14); 8 10 -> 6 (+0x14).  Kind 0 (move only) counts group 7 (source, mode +0x14) and group 8 (target, mode +0x30), and every parallel move in the list counts group 7 with mode `**(node+8)` and group 8 with mode `*(node[8]+0x1c)`.  Both groups 7 and 8 also get a total (index 0) increment.  Unknown kinds fall through with no counting.
* `igrp_mode_bucket(mode)` (0x4016a0): operand mode code -> report column: 0 none, 9 absolute, 10 immediate, 0xc register, 0xd (Rn+absolute)/long displacement, 0xe relative stay; 1-6 and 8 (all register-indirect variants) -> 5 (indirect); anything else calls `FUN_00483550` (abort/assert).
* `igrp_fill_mode_names(char **tab)` (0x401260, undecompiled): tab is 20*16 = 0x140 dword table ("[group*16+mode]"): sets the report labels, e.g. g0 m12 "opcode reg1,reg2,acc", m10 "opcode reg,#n,acc"; g1 m12 "opcode reg,acc", m10 "opcode immediate,acc"; g2 m5 "opcode #n,s:indirect", m9 "#n,s:absolute", m12 "#n,reg"; g3 m12 "opcode reg,acc"; m10 "opcode immediate,reg,acc"; g4 (bit control) m5/m9/m12 with ",label"; g5 m9 "opcode label", m5 "opcode indirect", m12 "opcode relative_label", m14 "opcode relative_indirect"; g6 (do) m5 "s:indirect,label", m9 "s:absolute,label", m10 "immediate,label", m12 "reg,label"; g7 (move source) m5 "s:indirect,dst", m9 "s:absolute,dst", m10 "immediate,dst", m12 "reg,dst", m13 "s:(Rn+absolute),dst"; g8 (move target) m5 "src,s:indirect", m9 "src,s:absolute", m12 "src,reg", m13 "src,s:(Rn+absolute)".

## 8. Peripherals in this range

### 8.1 EMI (external memory interface with DRAM controller), two near identical copies

EMI #1 (56004, 56004rom; code 0x401a50-0x403b00, context 0x4dbbec..) and EMI #2 (56007/56009; 0x40b280-0x40d5a0, context 0x4dbc6c..; differs by the burst/page wrap check `emi2_check_wrap` 0x40bda0 and tables `emi2_burst_bits_tab` 0x4b47a0/0x4b4870).  Register indices: 0 ebar0, 1 eor0, 2 edrr0, 3 ecsr, 4 ebar1, 5 eor1, 6 edrr1, 7 ercr, 8 edwr0, 9 edwr1, 10 ewor.  Regs 1/5 and 2/6 are aliased by `emi*_write_reg`: writing eor0 stores into both regs[1] and regs[5]; writing edrr0 stores into 2 and 6 (and vice versa).

Write side effects (`emi1_write_reg` 0x402060): the register pairs (eor0,eor1) = (1,5), (edrr0,edrr1) = (2,6) and (edwr0,edwr1) = (8,9) are **aliases**: a write to one stores the (masked) value into both slots.  Writing reg 1 (or 5) also starts a read transfer if ecsr bit 0x800000 (enable) is set, ecsr bit 0x20000 is clear and the engine is idle (`regs[0x98]==0 && regs[0x9c]==0 && !(ecsr&0x4000)`): `regs[0x98]=1` (2 for reg 5) and `regs[0x88] = emi1_next_read_addr(ecsr, 0|4)` (= `regs[ebar_idx] - regs[0x14/4]`, with post-increment of the ebar when `ecsr & 0x80`); if the engine is busy the request is queued in `regs[0x9c]` instead.  Reg 3 (ecsr): bits 12-15 are read-only status (`v = (old ^ v) & 0xf000 ^ v`).  Regs 8/9 (edwr) start a write transfer (`regs[0x98]=4/8`, `regs[0x8c]=edwr value`, `regs[0x88]=emi1_next_write_addr(ecsr,idx)`), or queue it in `regs[0x9c]`. 
`emi1_read_reg` (0x402310): reading edrr0/edrr1 (regs 2, 6) with side effect: (a) if ecsr has 0x800000 and 0x20000 (read-ahead) set, start the next read transfer as above (or queue it); (b) if ecsr bit 0x4000 (data waiting in the shift register) is set: `edrr1 = shift register (byte offset 0x2c); edrr0 = edrr1`, both touched, ecsr bit 0x4000 cleared and the routine returns; otherwise ecsr bit 0x2000 (data ready) is cleared.  Reading reg 1 (eor0) has no side effect.
**EMI #2 differs in its private state layout**: the transfer bookkeeping moved: pending request kind is `regs[0x44]`, queued kind `regs[0x48]`, latched address `regs[0x94]`, data to write `regs[0x98]`, state number `regs[0x4c]`-ish (see `emi2_clock`), and the post-increment helpers call `emi2_check_wrap` (0x40bda0), which uses `emi2_burst_bits_tab` (index `((ecsr&7) | (ecsr>>13 &8)) + ((ecsr>>3)&0xf)*8`, entries 0xc-0xf use `emi2_burst_bits_tab2`): if the low `n` bits of the incremented address register are all ones (`regs[idx] & ~(-1<<n) == same`) it raises `regs[0x3c]` (idx 0) or `regs[0x40]` (other) = page/burst boundary flags.  Everything else is the same algorithm, so translate both from one source with an offset table.
`emi1_touch_reg` (0x401b20) = standard touch (flags + mask + peripheral I/O refresh + `FUN_00449a70`).

State (`regs[]` of the EMI, index = byte offset/4): 0x0-0x28 visible regs; 0x40 state number (see below), 0x44 latched ecsr for the running transfer, 0x48/0x4c refresh interval / prescaler counters (ercr: bit 0x800000 enable, 0xff interval, bits 18/19 prescaler, bit 0x100000 refresh-now), 0x50/0x54 phase lengths (from `emi1_timing_tab_*` indexed by `ecsr&7`), 0x58 words left in the burst (`emi1_timing_tab_a`), 0x5c column counter, 0x60 current DRAM word address, 0x64 which ebar (0 or 4), 0x68 phase down counter, 0x6c data mask (0xf nibble / 0xff byte, ecsr bit 0), 0x70 shift width (4/8), 0x74 = 0x18 - width, 0x78 = ((ecsr>>19)&0xf)+1 hold cycles, 0x7c/0x80 row/column address latches read back from the pins (`(pins[2]>>8)&0x7ff`), 0x84 refresh request, 0x88 = latched source address, 0x8c = data to write, 0x90 = latched DRAM address, 0x94 = data being assembled, 0x98 = current request kind (1 read/eor0, 2 read/eor1, 4 write edwr0, 8 write edwr1), 0x9c = queued request.
`emi1_clock` (0x402530) state machine (`regs[0x40]`): 1 idle-enabled, 2 idle, 3-6 refresh (RAS/CAS-before-RAS timing using 0x50/0x54), 7-0x11 read cycle: row address (`emi1_row_addr` mode/size decode -> address pins `pins[2]` bits 8-27), RAS, column address (`emi1_col_addr`), CAS, data sample (`emi1_sample_dram_data`: reads DRAM word from space 0x1c / 0x1d+(ecsr&0x3f) through `FUN_00458280`, or from an injected pin value `FUN_0044bc30/bc80`), shift into `regs[0x2c]` (`emi1_shift_in`); 0x12-0x18 write cycle (`emi1_drive_dram_data` writes via `FUN_00458480`, notifies pins `FUN_004496a0`); 0x19/0x1a start in write mode. Pin bit meanings in `pins[2]`(output level) / `pins[3]` (drive mask): 0x18000000 RAS0/RAS1 lines, 0x3000000 CAS lines, 0x1000000, 0x2000000, 0x4000000, ... (nibble/byte address multiplexing in bits 8-27).  Status outputs `regs[0x34]`/`regs[0x38]` = (ecsr&0x400/0x200 enable bits) & (bit 0x1000/0x2000 status) = **interrupt requests** (0x34 receive/refresh, 0x38 transmit) which `*_m_irq_poll` (0x401fc0) converts into vectors.
`emi1_row_addr(mode, addr, pins, ctl)` (0x403330) is a big switch on `mode & 0x1f` (DRAM organisation / address multiplexing: cases 8-0x1f), forming the row address word for the address pins from the 16 bit `addr` and the low bits of `ctl`; `emi1_col_addr(..., col)` (0x4036c0) forms the column address; `mode & 0x38 == 0` = plain.  `emi1_merge_shift_data`, `emi1_shift_in` (0x403ab0): merge the data pin byte/nibble into `regs[0x2c]` with shift by 0x70/0x74.

### 8.2 DAX (digital audio transmitter, 56011 and 56012)

Registers xadra(0) xadrb(1) xctr(2) xstr(3).  **In this section and 8.3/8.4 `r[n]` means dword index n** (the decompiler shows `DAT_004dbc3c[n]`); `dax_clock` uses dword indices, the small helpers use byte offsets (byte = 4*n).

State `r[]` of the DAX: r[4] copy of xadrb; **r[5] shift register** (bit 0 is sent, refilled from xadra/xadrb with bits 24/25/26 = xctr bits 10/11/12 = validity/user/channel-status added); r[6] biphase level / parity accumulator (`r[6] ^= r[5]&1` in the data states); r[7] xctr latched at subframe start; r[9] bit counter (reloaded with 0x1a, 26 = 24 data + 2 status bits); r[10],r[11],r[12] interrupt request flags (set in `dax_clock` end from xstr bits 0/2/3 gated by xctr bit 1; consumed by `dax_m_irq_poll` -> vector base+0/+2/+6, only if r[13] (= ipl copy at byte 0x34, written when the IPR address 0xffff is stored: `regs[0x34] = elem[0x28] & value`) is non-zero); r[14] cleared at subframe start; r[0x10] stop-pending request; r[0x11] previous input-edge sample; r[0x12] clock divider countdown (reload 2 / 7 / 3 depending on xctr bits 3-4); r[0x15] frame counter 0..0xbf (192 frames per channel status block: sets xstr bit 3 = block start when it wraps); r[0x16] halted/reset latch (from cpu ctl [8],[0xc]); r[0x18] last level of the source clock; **r[0x19] = bit-cell state machine, states 0..0x20**.
`dax_clock` (0x40a740): clock divider, then one state of the 33-state machine per divided clock.  It shifts out the subframe preamble (B/M/W by state 0-7, 8-0xf, 0x10.. from the frame counter), the 26 data bits (states 0x10/0x11 and 0x1c/0x1d loop, each bit generates a biphase-mark pair: a state either toggles the output pin (`pins[2] ^= mask`, `uVar5 = 1`) or not), reloads the shift register from xadra/xadrb (`FUN_004496a0` = pin output logger) and sets/clears xstr flags (`r[3]` bits 0 (A empty), 2 (B empty), 3 (block start), 4).  `dax_write_reg` (0x40a530): reg 0/1 (xadra/xadrb) clear empty flags (r[0xe], `regs[0xc]` &= 0xfffffff6 etc.), reg 2 (xctr): bit 0 (enable) going 1->0 while a subframe runs sets the stop request r[0x10] (state 0x1f -> 0x20 completes it); `dax_read_reg` reg 3 (xstr) read sets r[0x14] when xstr bit 2 set.  `dax_reset_regs` (0x40a3f0) zeroes all state and masks xstr to 0xfc00.

### 8.3 GPIO (gpior)

One register (index 0).  Data bits are in the low bits, direction bits in bits 8-15 of the same register (`dir = (gpior >> 8) & 0xff`), read-back pin data in bits 16-23 (written by hardware).  `gpio_write_reg(grp,reg,val)` (0x40b000): `regs[reg] = regmask & val`; pin block `[3] = ([3] & ~m) | dir` (drive enable follows the direction bits), `[2] = ([2] & ~m) | (dir & data)` (output pins take the written value where dir=1); when a direction bit is set the change is logged through `FUN_004496a0`; then the watch check.  `gpio_read_reg(grp,reg,out,sample_pins)` (0x40b1b0): if `sample_pins` and a pin-input injection exists (`FUN_0044bc30`) merge it into pin block `[1]` (mask) and `[0]` (value); result = `((regmask | dir) & regs) | ((~dir | (regs>>16 & m)) & pins[0] & m)` with `m = regmask & 0xff`.  `gpio_reset_regs` (0x40afe0) = `regs[0]=0` + touch.

### 8.4 SHI (serial host interface, SPI and I2C slave, DSP56004 family)

Registers hckr(0) hcsr(1) hsar(2) hrx(3) htx(4); `r[n]` = dword index.  State `r[]`: r[5] shift register; **r[0xf..0x18] receive FIFO (10 words), r[0x19] FIFO count**; r[0x1a] master clock divider countdown, r[0x1b] generated clock level (`hckr & 0x40` master: divider reload `((hckr>>3)+1) << ((hckr&4) ? 1 : 4)`); **r[0x1c] state machine 0..0x12**; r[0x1d] latched pin input word; r[0x1e] previous clock level; r[0x1f] bit counter (8); r[0x20] overrun read latch (`shi_read_reg`); r[0x21] R/W bit; r[0x22] bytes left in the word (`hcsr & 8` -> 3 bytes, `hcsr & 4` -> 2, else 1); r[0x24] previous data pin; r[0x25] byte transfer in progress.
`shi_clock` (0x40dd80, 7446 bytes): reads the pin block bits (masks derived from the group's pin mask `elem[8]`: lowest set bit = SCK, x2 = SDA/MOSI, x4 = SS/HREQ, x8 = MISO out, x16 = ...), `hckr & 1` = mode (1 I2C, 0 SPI), `hckr & 2` = clock phase, `hckr & 0x40` master, `hckr & 0x180` = HREQ output mode (0x80 / 0x100 / 0x180).  I2C slave: states 0-0x12 implement START detection, address compare (`(hsar>>1)&0x7f`), R/W bit, ACK, 8-bit shifts with ACK per byte (word length 1-3 bytes), STOP; the SPI branch shifts MOSI/MISO with the same word-length logic.  Received words are pushed into the FIFO (r[0xf+count]); when count reaches 10 (9 in 24-bit mode) the FIFO-full status (hcsr bit 0x80000) is set; HRNE (0x20000)/overrun (0x100000...) status and HREQ pin are updated by `FUN_0040fba0` (exec_b range).  `shi_write_reg` (0x40dac0): reg 1 (hcsr): writing 1 to bit 21 (0x200000) clears the overrun; status bits are preserved: `(v & 0xff453fff) | (old & 0xbac200)`; if `!(v&2) || !(v&0x40)` bit 9 is forced set; if the FIFO count >= 9/10 bit 0x80000 set; reg 4 (htx): clears bit 15 (`hcsr &= 0xffff7fff`) and touches hcsr.  `shi_read_reg` (0x40dc80): reading hcsr latches overrun state r[0x20]; reading hrx (reg 3) with side effect pops the FIFO (`r[0xf..0x17] = r[0x10..0x18]`, count-1), clears FIFO-full/HRNE according to the new count and copies the new head into `hrx` (r[3]).  `shi_reset_regs` (0x40d900): clears r[6-8,0xa-0xc,0x19,0x1a,0x1b,0x1c], hckr = 1, hcsr = 0x8200, hsar = 0x800000, touches 0,1,2.

## 9. Function catalogue (address, name, what it does)

Decompiled (Ghidra) functions in exec.c below 0x40e000:

| addr | name | description |
|---|---|---|
| 401140 | igrp_map_kind | remap instruction kind for statistics (7) |
| 401380 | igrp_count_instr | count one executed instruction into group/mode counters |
| 4016a0 | igrp_mode_bucket | operand mode -> report bucket |
| 401b20 | emi1_touch_reg | mark register changed, re-mask, I/O refresh, watch |
| 401fa0 | emi1_clear_pending | `regs[0x9c]=regs[0x98]=0` |
| 402060 | emi1_write_reg | EMI register write with transfer start (8.1) |
| 402310 | emi1_read_reg | EMI register read with side effects |
| 4024b0 | emi1_next_read_addr | address for read transfer = ebar - eor, post-increment ebar when `ecsr&0x80` |
| 4024f0 | emi1_next_write_addr | same for write (`ecsr&0x100`, edwr address regs, `regs[0x28]`) |
| 402530 | emi1_clock | one clock of the DRAM controller state machine |
| 403330 | emi1_row_addr | DRAM row address forming |
| 4036c0 | emi1_col_addr | DRAM column address forming |
| 403950 | emi1_sample_dram_data | read a word from DRAM space (or pin injection) |
| 403a10 | emi1_merge_shift_data | merge sampled data into pin block low byte |
| 403a40 | emi1_drive_dram_data | write shifted data to DRAM space, log pins |
| 403ab0 | emi1_shift_in | shift new data byte/nibble into shift reg (`regs[0x2c]`) |
| 403c50 | core_write_reg | slot 1: write core register (debugger `change`, state load) |
| 4042b0 | core_set_reg | `regs[reg]=v` + touch |
| 4042d0 | core_set_reg_quiet | same, touch without composite propagation |
| 4045f0 | core_store_reg_masked | `regs[reg]=mask&v` + special reactions (used by I/O writes) |
| 404690 | core_touch_reg | = `core_touch_reg_ex(reg,0)` |
| 4046a0 | core_touch_reg_ex | apply mask, side effects, flags, watch |
| 4048d0 | core_touch_reg_quiet | = `core_touch_reg_ex(reg,1)` |
| 4048e0 | core_get_reg | `*out = regs[reg]` |
| 404900 | core_copy_reg | `regs[dst]=regs[src]` + touch |
| 404920 | core_copy_reg_quiet | same, quiet |
| 404940 | core_read_copy | `core_touch_read(src)` then `regs[dst]=regs[src]` |
| 404960 | core_touch_read | mark read (0x50000), fire read-injection |
| 404a70 | core_reset_io | clear IRQ/pin request latches; `hard`: X:$FFFF=0 |
| 404ad0 | core_reset | power-on/hard reset of registers (see 6) |
| 404e30 | core_reset_pipeline | clear sequencer and pipeline state |
| 405000 | core_fetch_decode | latch PC/IR, trace ring, run decoders (4.1) |
| 405440 | core_decode_ctl | derive bus/register selects and access strobes |
| 405b40 | core_clock | one machine cycle of the core |
| 408510 | core_sample_pins | sample/drive core pins (IRQA/B, RESET, MODx, bus arbitration), detect IRQ edges |
| 408a30 | core_cc_test | condition code test (5) |
| 408b80 | core_ss_dec | SP-1 after pop |
| 408bd0 | core_ss_push | system stack push |
| 408c70 | core_ss_pop | system stack pop |
| 408d20 | core_read_to_bus | register -> bus with A/B scaling+limiting (5) |
| 409170 | core_agu_setup | AGU latch setup for MMMRRR |
| 409230 | core_agu_calc | AGU arithmetic linear/modulo/reverse-carry |
| 409440 | bit_reverse16 | 16-bit bit reversal via `bit_mask_tab` |
| 409470 | core_agu_writeback | copy AGU result back to Rn |
| 4094c0 | core_ext_addr_match | extended-address decode (fam 0x80) |
| 409530 | core_mem_write | memory write with region/pin model |
| 409730 | core_ext_addr | extended address = `(regs[0xcc]&0xff00)<<8 | addr` |
| 409750 | core_irq_arbitrate | pick pending interrupt (peripherals + core) |
| 4098a0 | core_irq_scan | core interrupt priority scan |
| 409b10 | core_irq_ack | acknowledge peripheral interrupt (slot 7) |
| 409b40 | core_mem_read | memory read with region/pin model |
| 409dd0 | core_write_from_bus | bus -> register, A/B sign extension |
| 409f20 | core_do_loop_end | pop DO frame at loop end |
| 409fa0 | core_bit_test | test bit `regs[0x2cc]` of `regs[0x180]` |
| 409fd0 | core_bit_test_not | inverted test |
| 40a000 | core_bit_op | bset/bclr/bchg/btst SR.C and operand update |
| 40a3f0 | dax_reset_regs | DAX state reset |
| 40a530 | dax_write_reg | DAX register write |
| 40a640 | dax_touch_reg | standard touch |
| 40a700 | dax_read_reg | DAX register read |
| 40a740 | dax_clock | DAX bit/subframe engine |
| 40afe0 | gpio_reset_regs | `gpior=0` |
| 40b000 | gpio_write_reg | write with direction/pin update |
| 40b0f0 | gpio_touch_reg | standard touch |
| 40b1b0 | gpio_read_reg | read with pin sampling |
| 40b350 | emi2_touch_reg | as 401b20 (regs at 0x4dbc70) |
| 40b7d0 | emi2_clear_pending | `regs[0x48]=regs[0x44]=0` (state block layout differs from EMI #1, see 8.1) |
| 40b900 | emi2_write_reg | as 402060 (state offsets 0x44/0x48/0x94/0x98) |
| 40bbc0 | emi2_read_reg | as 402310 |
| 40bd40 | emi2_next_read_addr | as 4024b0 plus wrap check |
| 40bda0 | emi2_check_wrap | after post-increment: table lookup `emi2_burst_bits_tab[...]` mask; if low bits all 1 sets `regs[0x3c]`/`[0x40]` (address wrapped flags) |
| 40be40 | emi2_next_write_addr | as 4024f0 plus wrap check |
| 40bea0 | emi2_clock | as 402530 (uses `emi2_*` state offsets) |
| 40cda0 | emi2_row_addr | identical to 403330 |
| 40d130 | emi2_col_addr | as 4036c0 (slightly different) |
| 40d410 | emi2_sample_dram_data | as 403950 |
| 40d4d0 | emi2_merge_shift_data | as 403a10 |
| 40d500 | emi2_drive_dram_data | as 403a40 |
| 40d570 | emi2_shift_in | as 403ab0 |
| 40d900 | shi_reset_regs | SHI reset |
| 40dac0 | shi_write_reg | SHI register write |
| 40dbc0 | shi_touch_reg | standard touch |
| 40dc80 | shi_read_reg | SHI register read |
| 40dd80 | shi_clock | SPI / I2C slave state machine |

Functions not found by Ghidra (names from the method tables / disassembly): 401250 401260 401a50 401be0 401c70 401da0 401eb0 401fc0 402010 403ae0 403f70 404040 404130 4042f0 404480 40a0a0 40a170 40a1f0 40a2d0 40a380 40a460 40a4c0 40ad60 40adb0 40ae40 40ae50 40aed0 40af60 40b280 40b410 40b4a0 40b5d0 40b6e0 40b7f0 40b860 40d5a0 40d670 40d6f0 40d7d0 40d890 40d9a0 40da20.  (0x4132b0, shared default peek, is in exec_b.)

## 10. Globals

See names file (61 entries).  Data used by this range but not named: `DAT_004b3424`/`DAT_004b3428` (strings/log tags passed to `FUN_00449200`), `DAT_004c2bb0` decode table base, `DAT_004c36f0` decode jump table, `DAT_004c4f50/004c5068/004c5268/004c52b0/004c54b0-004c54f0` ALU micro-op tables (`FUN_00433ce0`), `DAT_004dc13c..004dc144` (ALU scratch: SR copy, ok flag, regs ptr).

## 11. Cross-module interfaces used by exec_a

`FUN_00439080` = region_lookup(space,addr)->region index; `FUN_00457cc0` = record memory reference (space,addr,is_read,pc); `FUN_00457de0` = refresh memory-mapped view of a peripheral register (address); `FUN_00458280/00458480` = memory subsystem read/write (dev+4, space, addr, ptr/value[, flag]); `FUN_00456f60/00456fb0` = peripheral I/O write/read by address; `FUN_00448b60`, `FUN_00448de0` = watch/trace hooks for memory writes/reads (dev region, addr, value); `FUN_00449a70(dev,reg)` register write watch/break; `FUN_004496a0(group,&pinvalue,0)` pin output logger (feeds the `redirect`/output files); `FUN_0044bc30/0044bc80/0044b4f0/0044bbe0/0044bb90/0044b410` = input file (pin injection) lookups; `FUN_00449200(&tag)` statistics event; `FUN_0042da70` = report "input consumed"; `FUN_0045d280(dev,space,addr)` bus trace; `FUN_00436b30(kind,pins)` reset broadcast; `FUN_00459140` memory access logger; decode/ALU functions listed in 4.1; `FUN_00483550` = abort/assert.

## 12. Quirks worth reproducing / open questions

* The models are phase exact: instruction timing, wait states (`bcr`), interrupt latency (fast interrupt 6 cycles?), stack error semantics and even pin toggling (EMI, DAX, SHI, GPIO) are all produced here.  If the goal is byte-exact `LOG` output (cycle counts, `display` of registers) the internals must be reproduced, not approximated.
* Registers 1/5 and 2/6 of the EMI alias each other (write stores into both).
* `core_ss_push` keeps the stack error bit (bit 4) in SP; `core_touch_reg_ex` raises the exception request only on the 0 -> 1 edge.
* `core_cc_test` case 4 (NN) / 12 (NR) use the 56000 formula with U and E.
* `core_read_to_bus` sets S (SR bit 7) only for family >= 56002 (`fam >= 4`).
* The EMI clock functions are 3.5 kB / 3.7 kB of nested state machines; treating them as data (state tables) is possible: state numbers 1..0x1a listed in 8.1.
* Open: exact meaning of many `regs[0x1d0..0x2b4]` decode bits (marked [M]); the pin block field layout beyond words 0-3 (0x128 bytes; only words 0-3 used in this range); which unreleased parts use family bits 0x10/0x20/0x80/0x800.
* Files to look at next in the toolchain for the missing ALU/decode: 0x42d4c0..0x430850 (decoders), 0x433360..0x435xxx (ALU micro-operations), `FUN_004339b0`, `FUN_00433890`.
