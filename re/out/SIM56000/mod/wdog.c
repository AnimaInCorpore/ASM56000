/* ==== wdog_write_reg @ 00414e90 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int wdog_write_reg(int dev,int reg,ulong *val)

{
  int iVar1;
  
  wdog_status = *(int *)(cur_sim + 8) + dev * 8;
  _wdog_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  wdog_regflags = *(undefined4 *)(wdog_status + 4);
  _wdog_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  wdog_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  wdog_regs = *_wdog_stslot;
  iVar1 = *(int *)(wdog_dev + 0x2c);
  wdog_st = wdog_regs;
  if ((reg < *(int *)(iVar1 + 0x28)) &&
     ((*(byte *)(*(int *)(iVar1 + 0x2c) + 0x10 + reg * 0x1c) & 0x40) != 0)) {
    wdog_write_reg_core(reg,*val & 0xffffff);
    wdog_refresh_reg(reg);
    return 1;
  }
  if (reg < *(int *)(iVar1 + 0x24)) {
    *(ulong *)(wdog_regs + reg * 4) = *val & 0xffffff;
  }
  wdog_refresh_reg(reg);
  return 1;
}


/* ==== wdog_tick @ 00414f60 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void wdog_tick(int dev)

{
  wdog_status = *(int *)(cur_sim + 8) + dev * 8;
  _wdog_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  wdog_regflags = *(undefined4 *)(wdog_status + 4);
  _wdog_stslot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  wdog_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  wdog_regs = *_wdog_stslot;
  wdog_chipflags = *(int *)(cur_dev + 0x40);
  wdog_st = wdog_regs;
  if ((*(int *)(wdog_chipflags + 0xc) == 0) && (*(int *)(wdog_chipflags + 8) != 1)) {
    wdog_clock(dev);
  }
  return;
}


/* ==== wdog_write_io @ 00414ff0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int wdog_write_io(int dev,ulong addr,ulong val)

{
  int reg;
  
  wdog_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  if (addr == *(ulong *)(wdog_dev + 0x1c)) {
    reg = 0;
  }
  else if (addr - *(ulong *)(wdog_dev + 0x1c) == 1) {
    reg = 1;
  }
  else {
    if (addr != 0xffff) {
      return 0;
    }
    reg = 6;
  }
  wdog_status = *(int *)(cur_sim + 8) + dev * 8;
  _wdog_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  wdog_regflags = *(undefined4 *)(wdog_status + 4);
  _wdog_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  wdog_regs = *_wdog_stslot;
  wdog_st = wdog_regs;
  if (reg != 6) {
    wdog_write_reg_core(reg,val);
    return 0;
  }
  *(uint *)(wdog_regs + 0x18) = *(uint *)(wdog_dev + 0x28) & val;
  return 0;
}


/* ==== wdog_read_io @ 004150b0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int wdog_read_io(int dev,ulong addr,ulong *out,int side)

{
  int iVar1;
  int extraout_EAX;
  
  wdog_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  _wdog_stslot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  wdog_regs = *_wdog_stslot;
  iVar1 = addr - *(int *)(wdog_dev + 0x1c);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = iVar1 + -1;
    if (iVar1 != 0) {
      wdog_st = wdog_regs;
      return iVar1;
    }
    iVar1 = 1;
  }
  wdog_status = *(int *)(cur_sim + 8) + dev * 8;
  _wdog_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  wdog_regflags = *(undefined4 *)(wdog_status + 4);
  wdog_st = wdog_regs;
  wdog_read_reg_core(iVar1,out,side);
  return extraout_EAX;
}


/* ==== wdog_reset @ 00415150 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int wdog_reset(int dev)

{
  int extraout_EAX;
  int iVar1;
  int in_stack_00000008;
  
  wdog_status = *(int *)(cur_sim + 8) + dev * 8;
  _wdog_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  wdog_regflags = *(undefined4 *)(wdog_status + 4);
  _wdog_stslot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  wdog_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  wdog_regs = *_wdog_stslot;
  wdog_st = wdog_regs;
  wdog_stop();
  iVar1 = 0;
  if (in_stack_00000008 != 0) {
    wdog_reset_regs();
    iVar1 = extraout_EAX;
  }
  return iVar1;
}


/* ==== wdog_reset_regs @ 004151d0 ==== */

void wdog_reset_regs(void)

{
  wdog_set_reg(0,0);
  *(undefined4 *)(wdog_st + 0x1c) = 0;
  *(undefined4 *)(wdog_st + 0x14) = 0;
  *(undefined4 *)(wdog_st + 8) = 0;
  *(undefined4 *)(wdog_st + 0x10) = 0;
  *(undefined4 *)(wdog_st + 0xc) = 0;
  return;
}


/* ==== wdog_set_reg @ 00415210 ==== */

void __cdecl wdog_set_reg(int reg,ulong val)

{
  *(ulong *)(wdog_regs + reg * 4) = val;
  wdog_refresh_reg(reg);
  return;
}


/* ==== wdog_int_pending @ 00415230 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long wdog_int_pending(int dev)

{
  long lVar1;
  
  _wdog_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  wdog_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  wdog_regs = *_wdog_stslot;
  wdog_st = wdog_regs;
  lVar1 = *(long *)(wdog_dev + 0x20);
  if (*(int *)(wdog_regs + 0x14) == 0) {
    lVar1 = -1;
  }
  return lVar1;
}


/* ==== wdog_int_ack @ 00415280 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int wdog_int_ack(int dev,long vec)

{
  int iVar1;
  
  _wdog_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  wdog_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  wdog_regs = *_wdog_stslot;
  iVar1 = wdog_regs;
  wdog_st = wdog_regs;
  if (vec == *(int *)(wdog_dev + 0x20)) {
    *(undefined4 *)(wdog_regs + 0x14) = 0;
  }
  return iVar1;
}


/* ==== wdog_write_reg_core @ 004152d0 ==== */

void __cdecl wdog_write_reg_core(int reg,ulong val)

{
  *(uint *)(wdog_regs + reg * 4) =
       *(uint *)(*(int *)(*(int *)(wdog_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c) & val;
  if (reg == 0) {
    if (((*wdog_st & 0x20) == 0) || (wdog_st[7] != 0)) {
      if (((*wdog_st & 0x20) == 0) && (wdog_st[7] == 1)) {
        wdog_stop();
      }
    }
    else {
      wdog_st[7] = 1;
      wdog_st[3] = (1 << ((byte)*wdog_st & 7) + 1) - 1;
      wdog_st[4] = wdog_st[3];
      wdog_st[2] = wdog_st[1];
    }
    if ((*wdog_st & 0x40) != 0) {
      wdog_st[3] = (1 << ((byte)*wdog_st & 7) + 1) - 1;
      wdog_st[4] = wdog_st[3];
      wdog_st[2] = wdog_st[1];
    }
  }
  *(uint *)(wdog_regflags + reg * 4) = *(uint *)(wdog_regflags + reg * 4) | 0xa0000;
  if ((*(uint *)(wdog_regflags + reg * 4) & 0x1800000) != 0) {
    io_out_periph_write((wdog_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
  }
  return;
}


/* ==== wdog_refresh_reg @ 004153d0 ==== */

void __cdecl wdog_refresh_reg(int reg)

{
  int iVar1;
  
  if (reg < *(int *)(*(int *)(wdog_dev + 0x2c) + 0x28)) {
    *(uint *)(wdog_regflags + reg * 4) = *(uint *)(wdog_regflags + reg * 4) | 0xa0000;
    *(uint *)(wdog_regs + reg * 4) =
         *(uint *)(wdog_regs + reg * 4) &
         *(uint *)(*(int *)(*(int *)(wdog_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c);
    iVar1 = reg * 0x1c + *(int *)(*(int *)(wdog_dev + 0x2c) + 0x2c);
    if ((*(byte *)(iVar1 + 0x10) & 0x60) != 0) {
      mem_trace_fetch(*(int *)(wdog_dev + 0x1c) + *(int *)(iVar1 + 8));
    }
    if ((*(uint *)(wdog_regflags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write((wdog_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
    }
  }
  return;
}


/* ==== wdog_read_reg_core @ 00415490 ==== */

void __cdecl wdog_read_reg_core(int reg,ulong *out,int side)

{
  *out = *(ulong *)(wdog_regs + reg * 4);
  if ((reg == 0) && (side == 1)) {
    wdog_set_reg(0,*wdog_st & 0xfffffff7);
  }
  return;
}


/* ==== wdog_stop @ 004154d0 ==== */

void wdog_stop(void)

{
  *(undefined4 *)(wdog_st + 0x1c) = 0;
  *wdog_status = 0x26;
  return;
}


/* ==== wdog_clock @ 004154f0 ==== */

void wdog_clock(void)

{
  if ((*wdog_st & 0x40) != 0) {
    wdog_set_reg(0,*wdog_st & 0xffffffbf);
  }
  if (wdog_st[7] != 0) {
    if ((*wdog_st & 0x10) == 0) {
      wdog_st[5] = 0;
    }
    if (*(int *)(wdog_chipflags + 4) != 0) {
      if (wdog_st[3] != 0) {
        wdog_st[3] = wdog_st[3] - 1;
        return;
      }
      wdog_st[3] = wdog_st[4];
      if (wdog_st[2] != 0) {
        wdog_st[2] = wdog_st[2] - 1;
        return;
      }
      wdog_st[2] = wdog_st[1];
      wdog_st[3] = (1 << ((byte)*wdog_st & 7) + 1) - 1;
      wdog_st[4] = wdog_st[3];
      if ((*wdog_st & 0x10) != 0) {
        wdog_st[5] = 1;
      }
      wdog_set_reg(0,*wdog_st | 8);
    }
  }
  return;
}


