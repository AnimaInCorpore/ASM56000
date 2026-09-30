# SIM56000 exec_b: on-chip peripheral models (0x40e000-0x41c13f)

Group exec_b of module `exec`. 70 functions are decompiled in re/out/SIM56000/mod/exec.c; Ghidra
missed ~65 more entry points that sit in the gaps between them (they are only reachable through the
peripheral descriptor tables in .data). Both sets are named in re/names/SIM56000/exec_b.names.txt
(136 F lines; the 66 extra ones were found from the descriptor tables, addresses verified with
x86dis.py, prototypes from the disassembly: confidence column says how sure).

This range is NOT the instruction core. It is a set of cycle-driven models of the DSP56xxx on-chip
peripherals, one cluster per peripheral, in this address order:

| range | peripheral (evidence) | descriptor(s) in .data |
|---|---|---|
| 40fba0 | shared pin-drive helper (called from exec_a 40dd80) | - |
| 40fc20-4131d0 | SAI serial audio interface: "sai" record 0x4b56b0, regs Baud Rate / Receiver CSR / Transmit CSR | 0x4b5930, 0x4b5970 |
| 4132b0-413f42 | TIMER: regs `tcr`,`tcsr` (reg table 0x4b66e8), "Timer Count Register" strings | 0x4b6720 |
| 413f70-414e8d | PWM: 9 registers (PWMA/PWMB control/status, prescaler, count; 6 channels of 0x3c bytes) | 0x4b6b28 |
| 414e90-415482 | WATCHDOG / COP ("Watchdog Count Register", "Watchdog Control/Status Register") | 0x4b6f68 |
| 4155b0-415930 | "simvar" pseudo peripheral: simulator internal variables (instr count, cycle count, break counter, flags) | 0x4b71d0 (5 entries) |
| 4159b0-416190 | parallel PORTs (Data Register / Data Direction Register): 3 instances | 0x4b75f8, 0x4b7638, 0x4b7678 |
| 416190-418010 | SCI async serial ("Status/Receive Data/Transmit Data/Baud/Control Register", parity, break, idle) | 0x4b8358, 0x4b8398 (+ iofile pair 0x4b8178) |
| 418010-41a2dc | SSI (Control Register A/B, Time Slot Register, Serial Transmit/Receive, sync/frame logic) | 0x4b92e0 |
| 41a300-41c119 | HI host interface (HCR/HSR/HRX/HTX, "Host Processor Address 0..7", pin handshake HREQ/HACK) | 0x4ba678, 0x4ba6b8, 0x4ba6f8, 0x4ba738 |

The devices in the table 0x4b... instances that reuse the same code are the same peripheral in different
chips (56001/2/3/4/7...).  devinit (0x41c140..) owns the tables; the code here is only the behaviour.

## 1. The peripheral descriptor (the dispatch)

Each peripheral TYPE has a descriptor in .data.  The simulator's per-device block (0x48 bytes, array at
`sim->devs = *(DAT_00505790+0x18)`, count `*(DAT_00505790+0x14)`) points to it at `dev+0x2c`.
Layout of the descriptor (byte offsets):

    +0x00 read_reg   int (*)(int dev,int reg,unsigned long *out)       reg-index based read, no side effect (shared periph_read_reg 4132b0 = state[dev][reg])
    +0x04 write_reg  int (*)(int dev,int reg,unsigned long *val)       reg-index write with side effects; used by change cmd / state load; returns 1
    +0x08 read_io    int (*)(int dev,unsigned long addr,unsigned long *out,int side)   bus read; `side`=1 => side effects (clears flags)
    +0x0c write_io   int (*)(int dev,unsigned long addr,unsigned long val)             bus write (called with a 4th arg 1 by the port code; ignored)
    +0x10 tick       void (*)(int dev)      per instruction cycle clock (40ae40 = `ret` for passive peripherals; ports)
    +0x14 reset      int (*)(int dev [,int full])   returns 0
    +0x18 int_pending long (*)(int dev)     vector address (dev+0x20) if state[+0x14] && state[+0x18] else -1  (only some types)
    +0x1c int_ack    int (*)(int dev,long vec)  if vec==dev[+0x20]: clears the flag/pending, e.g. timer TCF
    +0x20 reset value of the activity/status code (0x26, see `status`)
    +0x24 small int (0xb Timer, 0x4 ...; unknown, maybe number of int sources)
    +0x28 number of registers
    +0x2c pointer to register table, element 0x1c bytes:
          +0x00 name (char *, "tcr"), +0x04 write mask (`reg &= mask`), +0x08 address offset within the device's
          address window (dev+0x1c is the base address), +0x0c ?, +0x10 flags (bit 0x40 = write has side effects and
          goes through *_write_reg_core; bit 0x20/0x40 (mask 0x60) = memory mapped => call mem_refresh(addr)),
          +0x14 pointer to doc text (bit-field diagram strings), +0x18 ?
Short descriptors: 5 entries (simvar 0x4b71d0), 6 entries (ports: +0 = pin read, +1 = pin write, +2 read_io, +3 write_io,
+4 no-op, +5 reset; see 4159b0 / 415a00).  Ports use slots 0/1 for the PIN side (416050/415ed0), see section 3.

Device block fields seen (per device `dev`, stride 0x48): +4 = pin group / port index (indexes the
0x128-byte pin-group array `*(DAT_00505798+0x18)`), +8 = bit mask of the pins/interrupt sources of this
peripheral in its pin group, +0x18 = "enabled" flag, +0x1c = base I/O address, +0x20 = interrupt vector,
+0x2c = descriptor.  (exec_a documents the DSP state; keep names in sync.)

Pin group (0x128 bytes, `pingrp`): +0 external input level bits, +4 external "driven/valid" mask,
+8 output level, +0xc output drive (enabled) mask, +0x94.. a second copy of +0..+3 (previous / other
edge), interrupt request state lives elsewhere: `*(DAT_00505798+0x18)+0x5c8/0x5cc` = pending int
level/mask, `+0x5d0/0x5d4` = int output level/changed mask (see 413980, 414c20, 4154f0).

Global context pointers (shared by simulator core, filled at the top of every descriptor op):
DAT_00505790 = sim/chip config (+0x14 ndevs, +0x18 dev array, +8 chip model number, e.g. `<4`, `&0x880`);
DAT_0050578c: +8 = array of 8-byte entries {status word, regflags ptr} per dev;
DAT_00505794: +8 = array of pointers per dev (aux);
DAT_00505798: +8 = array of state pointers per dev (the peripheral state, int array), +0x18 = pin group
array (+0x5c8..0x5d4 interrupt lines), +0x40 = chip run flags {+4 running/clock enabled, +8 ==1: reset, +0xc: stopped}.
Each peripheral cluster caches these in its own globals (see section 2) via the entry op prologues
(pattern `ecx=[50578c]+8+dev*8; ...`), so the *_core functions take no dev argument.

Common conventions in every cluster:
* `<p>_set_reg(reg,val)`: `regs[reg]=val; <p>_refresh_reg(reg)` (internal write, no side effect).
* `<p>_refresh_reg(reg)`: `if reg < desc->nregs`: `regflags[reg] |= 0xa0000`; `regs[reg] &= regtab[reg].mask`;
  if `regtab[reg].flags & 0x60` => `mem_refresh(dev->base + regtab[reg].addr_off)` (FUN_00457de0);
  if `regflags[reg] & 0x1800000` => `reg_changed(dev - devs)/0x48, reg)` (FUN_00449a70).
  regflags bits: 0xa0000 = modified marks (display refresh), 0x800000/0x1000000 = watch/break-on-change
  requested (display on / break).
* `<p>_write_reg_core(reg,val)`: mask with `regtab[reg].mask`, do side effects, `regflags |= 0xa0000`,
  call reg_changed if watch bits.
* `<p>_read_reg_core(reg,*out,side)`: `*out = regs[reg]`; on `side` clears status bits (flag-read side effects).
* `<p>_reset_regs()`: zero the state and default registers; also sets `*status = 0x24..0x27`.
* `<p>_clock(...)`: per-cycle state machine.
`status` global (`*DAT_...` entry word 0): an activity code the simulator's speed/idle logic reads: 0x24/0x26 idle,
0x25/0x27 active (SAI reset writes 0x24, write of enable bits 0x25; SCI sets 0x27 when transmitting).

Cross-module functions called (names for the others to unify): FUN_00449a70 = reg_changed(devno,reg)
(watch/notify); FUN_00457de0 = mem_refresh(addr); FUN_004496a0 = outfile_write(dev,unsigned long *word,int tag)
(write a word to the device's output file, SCI/SAI tx, port change); FUN_0044bc30 = infile_next(dev,rec) returns 1 if
an input-file record was delivered, rec layout: words at rec+8/+0xc(+0x10) = value(s) (`local_28[2..]`);
FUN_0044b380 = parse_value(text,state,flags 0x4000001); FUN_004835f0 = strchr; FUN_00483570 = sprintf;
FUN_0045c6c0 = fixed-to-double conversion (for `%f:%f:%f` format).

## 2. Per-peripheral notes

Global cache layout per cluster (all 4-byte cells; the names file lists them): chipflags (= DAT_00505798+0x40 struct),
regs (int array = register file, index*4), st (state struct = same array extended beyond the registers), dev (device block),
regflags (per-register flag words, see refresh), stslot, aux, status (pointer to the activity word).
Base addresses: SAI 0x4dbca8, TIMER 0x4dbcc4, PWM 0x4dbce4, WDOG 0x4dbd04, simvar 0x4dbd28, PORT 0x4dbd40, SCI 0x4dbd58,
SSI 0x4dbd7c, HI 0x4dbda0 (SAI/SSI/HI have no separate `regs`: regs == st).
Notation: `st[i]` = dword index i of the state array; `st+0xNN` = byte offset.

### 2.1 Pin helper 0x40fba0 pin_drive_update(ctl, mode, pingrp, mask)
`pingrp[3] |= mask; pingrp[2] |= mask;` then, depending on `mode` (0x80, 0x100, 0x180 = pin control encoding) and bits 0x80000 /
0x8000 of `ctl`, the mask is cleared again from `pingrp[2]` (output level):
mode 0x80: clear unless ctl&0x80000; mode 0x100: clear unless ctl&0x8000; mode 0x180: if ctl&0x80000 then clear unless ctl&0x8000;
other modes: no clear. Called from exec_a (0x40dd80).

### 2.2 SAI (40fc20-4131d0)
State `sai_st`: [0] baud/prescaler reg (`(x&0xff)+1`, times 8 unless bit 8), [1] receiver control/status, [4] transmitter
control/status, [5..7] RX shift words (3 slots from the input file), [0xf]/[0x10] prescaler counter / clock phase,
[0x13..0x2f] and [0x34..0x6c] receiver / transmitter frame state machines, st+0x1b8 / +0x1bc pending input-file words (set by 40fe30).
* 40fc20 sai_iofile_parse(text,state): parse_value on "a:b", first value in state+0x188 second in +0x18c (split at ':' via strchr).
* 40fc80 sai_iofile_format(rec,_,out): formats 3 words by radix `rec+0x1d4` (0..4): `%01ld:%01ld:%01ld`, `%f:%f:%f`,
  `%01lx:%01lx:%01lx` (strings 0x4b6674 / 0x4b6668 / 0x4b6654); sign extends 24 bit words; TCS bit 5 selects word width (shift 8).
* 40fe30 sai_load_input(dev,rec): st+0x1b8/0x1bc = rec+8/rec+0xc, `<<8` when (TCS & 0x30)==0; st+0x17c = 1.
* 410270 sai_reset_regs. 410550 sai_write_reg_core(reg,val): reg 1 = RCS, 4 = TCS (bits 14/15 read-only: `(old ^ val) & 0xc000 ^ val`),
  5/6/7 = data registers (clear TX/RX empty flags in st+0xec, may reset the control via 410770(4)); other regs mask + notify.
  410830 sai_read_reg_core: reads of regs 1/2/3 clear overrun flags st+0x9c/0x94/0x98.
* 4108e0 sai_clock(dev): huge per-cycle function (6.6 KB). Generates the bit clock from the baud reg, runs frame sync / word length
  state machines for receiver (st[0x13..0x2f], st[0x48..0x53]) and transmitter (st[0x34..0x6c]), drives pins (pin bit masks derived from
  dev mask: `m<<1 .. m<<8`), shifts the 3 slot words (st[0x31..0x33] RX, st[0x56..0x58] TX), sets RCS/TCS flag bits 0x4000/0x8000
  (st[1], st[4]) and interrupt enable derived flags st[9..0xe]. Most of the body are small 4-state machines (`==1,2,3` tests on a
  phase counter) driven by the phase codes st[0x14]/st[0x22] (values 1,2,4,8). Translate literally.
* 4122e0 / 412c70 (rx / tx `decode_terms`): build a 9 bit input vector at st+0xf4 (tx: +0x58) from control and pin bits, an AND plane
  (masked compares such as `(v&0x9f)==0x80`) sets up to 32 product term bits in st+0xf8 (tx +0x5c), an OR plane sets 12 output
  bits in st+0xf0 (tx +0x58?). A PLA emulation of the SAI frame sync logic. 412b20 / 4131d0 spread the output bits back into flag
  words (st+0x100..0x11c / st+0xa4, 0x70..0x7c). Reproduce the constants exactly as in exec.c.

### 2.3 TIMER (4132b0-413f42)
Regs: 0 = tcr (address offset 1, mask 0xffffff), 1 = tcsr (offset 0, mask 0x7ff). State `timer_st`: [0] TCR, [1] TCSR (bit0 TE, bit1 TIE,
bits 3..5 = mode 0..7, bit 7 TCF (0x80), bit 8 = direction/inv (0x100), bit 9 (0x200) TIO level, bit 10 (0x400)), [2] running count,
[3] state (0 idle, 1 waiting, 2 counting), [4] latched TCSR, [6] interrupt request, [7] capture pending, [8] toggle level, [9] TIO level,
[10] edge state, [5] (+0x14) interrupt enable copy. Chip flags +4/+8/+0xc gate the clock.
* 413840 timer_write_reg_core(reg,val,force): reg 0 stores TCR; reg 1 keeps only bits 0x280 of the old value; TE 0->1 (or force)
  calls 413a00 timer_start_mode; TE clear clears the count state; special case for (tcsr&0x38)==0 with bits 0x40 and 0x100 set: sets TIO
  from bit 0x400 vs st[9] via 413980.
* 413a00 timer_start_mode(tcsr): mode = tcsr>>3&7. mode 2: st[8] = ~tcsr>>2&1; mode 3: state 0; modes 4,5: state 1 (wait for edge); else 2.
  count = TCR (except mode 4); mode 6: count = TCR ^ 0xffffff and timer_set_reg(0,count).
* 413bc0 timer_clock (each cycle): modes 0..2 internal down counter from TCR, on zero timer_expire(mode); modes 4,5 pulse width /
  period capture counting up (24 bit wrap); mode 6 external event counter on TIO edges (timer_edge_match); mode 7 down counter.
  Edge detection uses the pin group interrupt line bits `pin[0x5c8/0x5cc]`.
* 413e60 timer_edge_match(level): consumes edge state st+0x28 (0 none, 1 = match `level==1`, 2 = match then clear).
* 413ea0 timer_expire(mode): sets TCF (0x80) via 413ae0, sets st[6] when TIE, then per mode: 1 -> timer_set_tio(~level) and reload;
  2 -> timer_set_tio(st[8]) and toggle st[8]; 0,7 -> reload; 4 -> state 1 and timer_set_reg(0,count); 5 -> st[7] = 1.
* 413980 timer_set_tio(level): drives the TIO pin: `pin[0x5d4] |= dev mask; pin[0x5d0] = level ? |= : &= ~mask`, updates TCSR bit 9.
* 4133b0 timer_tick(dev): loads context, calls timer_clock unless chipflags say stopped / reset.
* 413710 int_pending: (st[5] && st[6]) ? dev[+0x20] : -1. 4137a0 int_ack(vec): if vec==dev[+0x20]: TCSR &= 0x7f, st[6]=0.
* 413440 write_io: addr - dev[+0x1c] == 0 -> reg 1, == 1 -> reg 0, 0xffff -> special (sets st[5] = (dev[+0x28] & val) != 0, i.e. interrupt
  enable from the IPR value), otherwise ignored. 413510 read_io mirrors it (TCSR read with side effect clears TCF when bit 7 set).

### 2.4 PWM (413f70-414e8d)
9 registers. Regs 0..2 = channel pulse width regs (A group), 3 = PWMA control/status, 4 = A enable/mode register, 5,6 = second group
widths, 7 = second control/status, 8 = second enable. State `pwm_st` is addressed in BYTES here: +0xc = control/status A copy,
+0x1c = control/status B copy, +0x10 / +0x20 = enable registers, six channels of 0x3c bytes at +0x28:
[0] state (0 idle, 1 running, 2 armed), [1] period, [2] count, [3] compare/reload mask, [4],[5] output polarity states, [10]
prescaler select (0 or 1; index into `pwm_prescale_tab` 0x4b6838[8] stored at +0x174/+0x178), [0xe] pending int flags.
+0x154..0x160 external line states, +0x164/+0x168 prescaler counters, +0x16c/+0x170 prescaler carry flags, +0x17c host int flag.
* 4142f0 pwm_reset_regs; 414640 pwm_write_reg_core (regs 0..2: pulse width `>>8`, negative if bit 15 -> `(~w+1)&0xffff`; 3/7 keep read-only
  bits `0xfc00 / 0xf000` and set the prescaler select `>>4&7`; 4/8 per channel enable: uses tables 0x4b6858.. and starts channels
  via 414920 pwm_chan_reload);
  414a40 pwm_clock (prescaler via 414cd0, per channel counting, output drive 414c20, sets CSR flag bits, `+0x17c=1` on int);
  414c20 pwm_drive_int(chan,level,bits): drives the int line bits (`pin[0x5d0/0x5d4]`), polarity from CSR & table 0x4b68d0.
Tables (int arrays indexed by channel/prescaler): 0x4b6838[8] divisors; 0x4b6858/0x4b6864, 0x4b6870/0x4b687c, 0x4b6888, 0x4b6898,
0x4b68a0, 0x4b68b8/0x4b68c4, 0x4b68d0: per-channel flag/enable bit masks (verify with data dump when translating).

### 2.5 Watchdog (414e90-415482)
Regs: 0 = control/status (bits 0..2 prescale exponent, 0x8 = expired flag, 0x10 = output pin enable, 0x20 = run enable, 0x40 = clear/reload),
1 = count. State `wdog_st`: [1] = count (reload value), [2] = current count, [3]/[4] = prescaler counter / reload
(`(1 << ((csr&7)+1)) - 1`), [5] = output level, [7] = running.
* 4152d0 write_reg_core(reg 0): run enable 0->1 starts: st[7]=1, prescaler and counter reloaded; enable 1->0 -> 4154d0 wdog_stop (st[7]=0,
  status 0x26). Bit 0x40 reloads the counters.
* 4154f0 wdog_clock: clears bit 0x40 by itself; while running counts prescaler then counter down; on expiry sets bit 8 (`wdog_set_reg(0, csr|8)`)
  and output level st[5] when bit 0x10.
* 415490 read_reg_core: reg 0 with side effect clears bit 3 (mask ~8).

### 2.6 simvar (4155b0-415930)
Pseudo registers exposing simulator internals (strings 0x4b72d0..: number of instructions executed, device clock cycle counter, break
counter, "branch or jump actually executed" flag, "device executing stop", "end of input file"). Short 5 entry descriptor 0x4b71d0
(no tick / reset): read_reg 4155b0, write_reg 4156a0, write_io 4157f0, refresh 415930. Only 415930 is decompiled.

### 2.7 PORT (4159b0-416190) three instances (0x4b75f8, 0x4b7638, 0x4b7678; the third has different read_io/write_io 415d60/415cb0)
3 registers (data, data direction, control). Descriptor slots 0/1 are the PIN side: port_read_reg 4159b0 -> 416050, port_write_reg 415a00 ->
415ed0.
* 416050 port_read_pins(dev,reg,*out,fetch): for reg != 2: OR over every enabled device sharing the pin group (`other[+4]==dev[+4]` and
  `other[+0x18] != 0`) of `other->desc->read_io(other_no, other_regaddr + base, &v, 1)`; reg 2 (data pins): builds `(word from other devices)
  | external input` under mask `regtab[2].mask` and, when `fetch`, reads the next input file record (infile_next) which loads pingrp[0]/[1].
* 415ed0 port_write_pins(dev,reg,val): calls `other->desc->write_io(other_no, addr, val, 1)` for all sharing devices (OR of results stored
  in regs[reg]); then merges into pingrp[2]/[3]/[1] under the register mask and writes changed pins to the output file
  (outfile_write(dev,&word,0)).
* 415b10 port_reset_regs zeroes regs 0..2 (through 415e10 port_refresh_reg), 415a90 port_reset(dev, full).

### 2.8 SCI (416190-418010) state `sci_st`
Regs (table at 0x4b8358, strings "Status Register", "Receive Data Register", "Transmit Data Register", "Clock Control Register", "Control Register"): 0 = control
(bits 0..2 = frame format 0..7 -> `sci_mode_bits_tab`/`sci_mode_nbits_tab` 0x4b83d8 / 0x4b83f8, bit 3 = MSB first, 0x10 parity...,
0x200 = enable, 0x400/0x800/0x2000 = interrupt enables, 0x1000, 0x4000/0x8000 = pin polarity), 1 = clock control (baud reload 0xfff),
2 = RX data, 3 = status, 5 = TX data, 6..9 = byte views (2 -> 6 -> 7 shifted by 8/16; 8/9 write views).
Fields: st+0x58 current word (0xfffffffe = idle, 0xfffffffd = break marker), st+0xc0.. = bit queue (dword per bit, ends with 0xfffffffe),
st+0x2c = RX shift register (-2 = idle, bit 0 = start), st+0x84, +0x90 = TX parity mode, +0x94 / 0x98 / 0x9c / 0xa0 = idle/break/tx-enable flags.
* 416b50 read_reg_core: reg 3 (status; reads clear sticky bits and set st+0x7c), reg 2/6/7 data (`st[2] << 0/8/16`), reg 5 returns 0; a
  status read re-runs 416c50 when idle.
* 416920 write_reg_core: reg 1 (control) tracks enable edges (0x400 rising with status bit 3, 0x10 rising -> st+0x9c=1); reg 5 (TX data)
  sets st+0x78=1; regs 8/9 shift the value down into reg 4; then rewrites the status register through 4167f0.
* 416c50 sci_reset_state: status := 3, clears the frame machines, marks idle (-2), status code 0x26.
* 416d20 sci_clock(dev, feed_input): per cycle bit clock (counter st[0x11] reload from control & 0xfff, /8 in sync mode), samples the RXD
  pin (pin group bits `m<<1`, `m<<2`, `m<<(2 or 9)`), assembles the received frame, checks start / stop / parity, sets flags in the status reg
  (RDRF 4, TDRE, overrun 0x10, framing 0x20/0x40, parity), drives TXD; transmit path: 417b20 picks the next TX word (from regs / file), encodes
  it (417f50) and queues the bits (417d00), and writes the word to the output file with outfile_write(dev,&word,0).
* 417ad0: if control bit 9 (0x200) clear -> abort TX (st+0x80=0, st+0xa0=1, status &= ~3) return 1. 417ed0 sci_decode_frame(data,parity,stop)
  bit-reverses the RX shift register into a byte (MSB first when control bit 3), 417f50 sci_encode_frame(word,frame): start bit + 8 data bits
  (+ parity 4:even 5:odd 6:extra) + stop bit(s) into one word.

### 2.9 SSI (418010-41a2dc) state `ssi_st`
Regs (strings "Time Slot Register", "Serial Transmit Register", "Serial Receive Register", "Control Register A/B"): 0 = time slot mask?, 1 = control B
(bit 12/13 (0x1000,0x2000) enable bits, 0x40 ...), 2/3 = data, 4/5 = TX data (write clears TDE, st+0xdc=1), 3 = status.
418010 iofmt_idle_parse: text "idle" -> `state[0x19c] = 0x8000; state[0x188] = -2; return 1` (also used for the PWM/port/SCI files, table
0x4b6980, 0x4b91c8); 413f70 iofmt_idle_format is the inverse (value -2 -> "IDLE").
418b20 ssi_clock(dev, feed_input) is the biggest function of the group (6 KB): frame sync and bit clock generation, word length
(`(ctrl>>8)&0x1f`), normal/network mode selection (`local_90` values 1,3,4,5,7,0x3d... ), TX/RX shift registers, time slot mask, pin group
bit shifts (mask << 1..5), input file feeding. 418690 write_reg_core: reg 1 clears st+0x84 / st+0x100 when bit 13 / 12 clear, re-runs
418910 ssi_reset_state when idle; regs 4/5 set st+0xdc and clear TDE flags (bit 4, 6 of reg 3); 418880 read_reg_core: reads of reg 2/3
clear status bits (0x20/0x10/0x80) and set st+0x50/+0x54.

### 2.10 HI host interface (41a300-41c119) state `hi_st`
Regs (Host Processor Address 0..7 on the host side; strings 0x4ba7f8..0x4babd4): ICR, CVR (command vector), ISR, IVR, TX/RX bytes low/mid/high,
interrupt vector/control registers. `hi_cmd_reg_tab` (0x4ba778[8]) maps host address (0..7) to the register index used by hi_write_reg.
* 41a300 hi_write_reg(dev,reg,*val) (also descriptor slot 1): 0 = control (bit 7 -> status bit 2), 5 = command (sets host command / vector
  bits 0x18, `0x60` flags, cross links status bits 0/1), 7/8/9/0xb/0xd byte writes (`& 0xff`), 0xc = TX byte 3 and assembles the
  24 bit word into st+0x78; registers flagged 0x40 go through 41abe0 hi_write_reg_masked (regs 1 and 4 have side effects), others
  are stored + refreshed.
* 41acb0 hi_read_reg_core (reg 2 read clears status bit 0 and can set bit 2 of reg 6), 41ad00 hi_reset_state(full).
* 41a9d0 hi_find_pin_shift: st[0x6c] = index of lowest set bit of dev mask (0..23), st[0x70] = 1, returns the index.
* 41adb0 hi_clock_a / 41b760 hi_clock_b (dev, feed_input): host port pin handshake state machines, two chip variants (41b760 additionally handles a
  0x8000<<shift pin and different masks). shift `local_68` = st[0x1b] (or 41a9d0()); pins live at `0x100<<shift .. 0x8000<<shift` of the
  pin group; input file values `<<shift` go into pingrp[0..1]; host writes are performed through hi_write_reg with
  `hi_cmd_reg_tab[(pins >> (shift+8)) & 7]`. Both ~2.4 KB and structurally identical; 41a570 (hi_tick_a) presumably calls 41adb0 and 41a600
  (hi_tick_b) 41b760 (not verified: the four descriptors differ only in slot 4, 41a570 vs 41a600).

## 3. Quirks and hints for the translator
* Everything is 32 bit unsigned int arithmetic with explicit 24 bit masking (`& 0xffffff`); use unsigned long with masks.
* The state arrays are addressed both as dwords (`st[i]`) and bytes (`*(st + 0xNN)`): keep one `unsigned long st[N]` and convert offsets
  by /4; PWM/timer/SCI state extends up to at least 0x180 bytes; allocate 0x200 bytes per peripheral state (the original allocation is
  done by devinit/exec_a via DAT_00505798+8).
* Do not restructure the tick functions; they are state machines over many flags whose exact update order matters
  (`prev = cur` copies at the end: st[0x21]=st[0x1c], st[0x24]=st[0x20], st[0x22]=st[0x14] ...).
* Unrecovered: register meaning of a few indices, exact sizes of state structs, simvar and port gap functions (only entry points named),
  hi_tick_a/b bodies (41a570, 41a600), SAI file record layout (parse yields 2 words, format prints 3), the 0x4b68xx / 0x4b83xx tables.
