/* ==== gpio_m_peek @ 0040ad60 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int gpio_m_peek(int grp,int reg,ulong *out)

{
  _DAT_004dbc60 = (undefined4 *)(*(int *)(cur_dev + 8) + grp * 4);
  gpio_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  gpio_regs = *_DAT_004dbc60;
  gpio_read_reg(grp,reg,out,0);
  return 1;
}


/* ==== gpio_m_poke @ 0040adb0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int gpio_m_poke(int grp,int reg,ulong *val)

{
  _DAT_004dbc68 = *(int *)(cur_sim + 8) + grp * 8;
  _DAT_004dbc64 = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  gpio_flags = *(undefined4 *)(_DAT_004dbc68 + 4);
  _DAT_004dbc60 = (undefined4 *)(*(int *)(cur_dev + 8) + grp * 4);
  gpio_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  gpio_regs = *_DAT_004dbc60;
  gpio_write_reg(grp,reg,*val);
  gpio_touch_reg(reg);
  return 1;
}


/* ==== gpio_m_clock @ 0040ae40 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void gpio_m_clock(int grp)

{
  return;
}


/* ==== gpio_m_io_write @ 0040ae50 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int gpio_m_io_write(int grp,ulong addr,ulong val)

{
  gpio_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  if (addr == *(ulong *)(gpio_grp + 0x1c)) {
    _DAT_004dbc68 = *(int *)(cur_sim + 8) + grp * 8;
    _DAT_004dbc64 = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
    gpio_flags = *(undefined4 *)(_DAT_004dbc68 + 4);
    _DAT_004dbc60 = (undefined4 *)(*(int *)(cur_dev + 8) + grp * 4);
    gpio_regs = *_DAT_004dbc60;
    gpio_write_reg(grp,0,val);
  }
  return 0;
}


/* ==== gpio_m_io_read @ 0040aed0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int gpio_m_io_read(int grp,ulong addr,ulong *out,int side)

{
  int extraout_EAX;
  
  gpio_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  _DAT_004dbc60 = (undefined4 *)(*(int *)(cur_dev + 8) + grp * 4);
  gpio_regs = *_DAT_004dbc60;
  if (addr == *(ulong *)(gpio_grp + 0x1c)) {
    _DAT_004dbc68 = *(int *)(cur_sim + 8) + grp * 8;
    _DAT_004dbc64 = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
    gpio_flags = *(undefined4 *)(_DAT_004dbc68 + 4);
    gpio_read_reg(grp,0,out,side);
    grp = extraout_EAX;
  }
  return grp;
}


/* ==== gpio_m_reset @ 0040af60 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void gpio_m_reset(int grp)

{
  int in_stack_00000008;
  
  _DAT_004dbc68 = *(int *)(cur_sim + 8) + grp * 8;
  _DAT_004dbc64 = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  gpio_flags = *(undefined4 *)(_DAT_004dbc68 + 4);
  _DAT_004dbc60 = (undefined4 *)(*(int *)(cur_dev + 8) + grp * 4);
  gpio_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  gpio_regs = *_DAT_004dbc60;
  if (in_stack_00000008 != 0) {
    gpio_reset_regs();
  }
  return;
}


/* ==== gpio_reset_regs @ 0040afe0 ==== */

void gpio_reset_regs(void)

{
  *gpio_regs = 0;
  gpio_touch_reg(0);
  return;
}


/* ==== gpio_write_reg @ 0040b000 ==== */

void __cdecl gpio_write_reg(int grp,int reg,ulong val)

{
  int iVar1;
  int b;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  b = reg;
  uVar4 = *(uint *)(*(int *)(*(int *)(gpio_grp + 0x2c) + 0x2c) + 4);
  uVar2 = uVar4 & val;
  uVar4 = uVar4 & 0xff;
  iVar1 = *(int *)(cur_dev + 0x18) + *(int *)(*(int *)(cur_dtype + 0x18) + 4 + grp * 0x48) * 0x128;
  *(uint *)(gpio_regs + reg * 4) = uVar2;
  uVar3 = uVar2 >> 8 & uVar4;
  *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & ~uVar4 | uVar3;
  *(uint *)(iVar1 + 8) = uVar3 & uVar2 | *(uint *)(iVar1 + 8) & ~uVar4;
  *(uint *)(gpio_flags + reg * 4) = *(uint *)(gpio_flags + reg * 4) | 0xa0000;
  if (uVar3 != 0) {
    reg = uVar4 & *(uint *)(iVar1 + 8);
    io_out_pin_write(grp,(ulong *)&reg,0);
  }
  if ((*(uint *)(gpio_flags + b * 4) & 0x1800000) != 0) {
    io_out_periph_write((gpio_grp - *(int *)(cur_dtype + 0x18)) / 0x48,b);
  }
  return;
}


/* ==== gpio_touch_reg @ 0040b0f0 ==== */

void __cdecl gpio_touch_reg(int reg)

{
  int iVar1;
  
  if (reg < *(int *)(*(int *)(gpio_grp + 0x2c) + 0x28)) {
    *(uint *)(gpio_flags + reg * 4) = *(uint *)(gpio_flags + reg * 4) | 0xa0000;
    *(uint *)(gpio_regs + reg * 4) =
         *(uint *)(gpio_regs + reg * 4) &
         *(uint *)(*(int *)(*(int *)(gpio_grp + 0x2c) + 0x2c) + 4 + reg * 0x1c);
    iVar1 = reg * 0x1c + *(int *)(*(int *)(gpio_grp + 0x2c) + 0x2c);
    if ((*(byte *)(iVar1 + 0x10) & 0x60) != 0) {
      mem_trace_fetch(*(int *)(gpio_grp + 0x1c) + *(int *)(iVar1 + 8));
    }
    if ((*(uint *)(gpio_flags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write((gpio_grp - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
    }
  }
  return;
}


/* ==== gpio_read_reg @ 0040b1b0 ==== */

void __cdecl gpio_read_reg(int grp,int reg,ulong *out,int sample_pins)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  ulong local_28 [2];
  uint local_20;
  
  uVar2 = *(uint *)(*(int *)(*(int *)(gpio_grp + 0x2c) + 0x2c) + 4);
  uVar6 = uVar2 & 0xff;
  puVar1 = (uint *)(*(int *)(cur_dev + 0x18) +
                   *(int *)(*(int *)(cur_dtype + 0x18) + 4 + grp * 0x48) * 0x128);
  uVar3 = *(uint *)(gpio_regs + reg * 4);
  uVar5 = uVar3 >> 8 & uVar6;
  if ((sample_pins != 0) && (iVar4 = io_in_pin_read(grp,local_28), iVar4 != 0)) {
    puVar1[1] = puVar1[1] | uVar6;
    *puVar1 = *puVar1 & ~uVar6 | local_20 & uVar6;
  }
  *out = (uVar2 | uVar5) & uVar3 | (~uVar5 | uVar3 >> 0x10 & uVar6) & *puVar1 & uVar6;
  return;
}


