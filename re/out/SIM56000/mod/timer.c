/* ==== periph_read_reg @ 004132b0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int periph_read_reg(int dev,int reg,ulong *out)

{
  *out = *(ulong *)(*(int *)(*(int *)(cur_dev + 8) + dev * 4) + reg * 4);
  return 1;
}


/* ==== timer_write_reg @ 004132e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int timer_write_reg(int dev,int reg,ulong *val)

{
  int iVar1;
  
  timer_status = *(int *)(cur_sim + 8) + dev * 8;
  _timer_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  timer_regflags = *(undefined4 *)(timer_status + 4);
  _timer_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  timer_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  timer_regs = *_timer_stslot;
  iVar1 = *(int *)(timer_dev + 0x2c);
  timer_st = timer_regs;
  if ((reg < *(int *)(iVar1 + 0x28)) &&
     ((*(byte *)(*(int *)(iVar1 + 0x2c) + 0x10 + reg * 0x1c) & 0x40) != 0)) {
    timer_write_reg_core(reg,*val,1);
    timer_refresh_reg(reg);
    return 1;
  }
  if (reg < *(int *)(iVar1 + 0x24)) {
    *(ulong *)(timer_regs + reg * 4) = *val;
  }
  timer_refresh_reg(reg);
  return 1;
}


/* ==== timer_tick @ 004133b0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void timer_tick(int dev)

{
  timer_status = *(int *)(cur_sim + 8) + dev * 8;
  _timer_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  timer_regflags = *(undefined4 *)(timer_status + 4);
  _timer_stslot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  timer_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  timer_regs = *_timer_stslot;
  timer_chipflags = *(int *)(cur_dev + 0x40);
  timer_st = timer_regs;
  if ((*(int *)(timer_chipflags + 0xc) == 0) && (*(int *)(timer_chipflags + 8) != 1)) {
    timer_clock(dev);
  }
  return;
}


/* ==== timer_write_io @ 00413440 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int timer_write_io(int dev,ulong addr,ulong val)

{
  int reg;
  
  timer_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  if (addr == *(ulong *)(timer_dev + 0x1c)) {
    reg = 1;
  }
  else if (addr - *(ulong *)(timer_dev + 0x1c) == 1) {
    reg = 0;
  }
  else {
    if (addr != 0xffff) {
      return 0;
    }
    reg = 5;
  }
  timer_status = *(int *)(cur_sim + 8) + dev * 8;
  _timer_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  timer_regflags = *(undefined4 *)(timer_status + 4);
  _timer_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  timer_regs = *_timer_stslot;
  timer_st = timer_regs;
  if (reg != 5) {
    timer_write_reg_core(reg,val,0);
    return 0;
  }
  *(uint *)(timer_regs + 0x14) =
       (uint)((*(uint *)(*(int *)(cur_dtype + 0x18) + 0x28 + dev * 0x48) & val) != 0);
  return 0;
}


/* ==== timer_read_io @ 00413510 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int timer_read_io(int dev,ulong addr,ulong *out,int side)

{
  int iVar1;
  uint extraout_EAX;
  uint extraout_EAX_00;
  uint uVar2;
  
  _timer_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  timer_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  timer_regs = *_timer_stslot;
  iVar1 = addr - *(int *)(timer_dev + 0x1c);
  if (iVar1 == 0) {
    iVar1 = 1;
  }
  else {
    iVar1 = iVar1 + -1;
    if (iVar1 != 0) {
      timer_st = timer_regs;
      return iVar1;
    }
    iVar1 = 0;
  }
  timer_status = *(int *)(cur_sim + 8) + dev * 8;
  _timer_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  timer_regflags = *(undefined4 *)(timer_status + 4);
  timer_st = timer_regs;
  timer_read_reg_core(iVar1,out,side);
  uVar2 = extraout_EAX;
  if (((side != 0) && (iVar1 == 1)) && (uVar2 = *(uint *)(timer_st + 4), (uVar2 & 0x80) != 0)) {
    timer_set_reg(1,uVar2 & 0xffffff7f);
    uVar2 = extraout_EAX_00;
  }
  return uVar2;
}


/* ==== timer_set_reg @ 004135d0 ==== */

void __cdecl timer_set_reg(int reg,ulong val)

{
  *(ulong *)(timer_regs + reg * 4) = val;
  timer_refresh_reg(reg);
  return;
}


/* ==== timer_reset @ 004135f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int timer_reset(int dev)

{
  uint *puVar1;
  uint uVar2;
  int extraout_EAX;
  
  timer_status = *(int *)(cur_sim + 8) + dev * 8;
  _timer_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  timer_regflags = *(undefined4 *)(timer_status + 4);
  _timer_stslot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  timer_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  timer_regs = *_timer_stslot;
  uVar2 = *(uint *)(timer_dev + 8);
  timer_st = timer_regs;
  *(uint *)(*(int *)(cur_dev + 0x18) + 0x5d4) = *(uint *)(*(int *)(cur_dev + 0x18) + 0x5d4) & ~uVar2
  ;
  puVar1 = (uint *)(*(int *)(cur_dev + 0x18) + 0x5d0);
  *puVar1 = *puVar1 & ~uVar2;
  timer_reset_regs();
  return extraout_EAX;
}


/* ==== timer_reset_regs @ 00413690 ==== */

void timer_reset_regs(void)

{
  timer_set_reg(1,0);
  timer_set_reg(0,0);
  *(undefined4 *)(timer_st + 0xc) = 0;
  *(undefined4 *)(timer_st + 0x24) = 0;
  *(undefined4 *)(timer_st + 0x28) = 0;
  *(undefined4 *)(timer_st + 0x18) = 0;
  *(undefined4 *)(timer_st + 8) = 0;
  *(undefined4 *)(timer_st + 0x20) = 0;
  *(undefined4 *)(timer_st + 0x1c) = 0;
  *(undefined4 *)(timer_st + 0x14) = 0;
  *(undefined4 *)(timer_st + 0x10) = 0;
  *timer_status = 0x26;
  return;
}


/* ==== timer_int_pending @ 00413710 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long timer_int_pending(int dev)

{
  timer_status = *(int *)(cur_sim + 8) + dev * 8;
  _timer_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  timer_regflags = *(undefined4 *)(timer_status + 4);
  _timer_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  timer_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  timer_regs = *_timer_stslot;
  timer_st = timer_regs;
  if ((*(int *)(timer_regs + 0x14) != 0) && (*(int *)(timer_regs + 0x18) != 0)) {
    return *(long *)(timer_dev + 0x20);
  }
  return -1;
}


/* ==== timer_int_ack @ 004137a0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int timer_int_ack(int dev,long vec)

{
  int extraout_EAX;
  int iVar1;
  
  timer_status = *(int *)(cur_sim + 8) + dev * 8;
  _timer_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  timer_regflags = *(undefined4 *)(timer_status + 4);
  _timer_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  iVar1 = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  timer_regs = *_timer_stslot;
  timer_st = timer_regs;
  timer_dev = iVar1;
  if (vec == *(int *)(iVar1 + 0x20)) {
    timer_set_reg(1,*(uint *)(timer_regs + 4) & 0xffffff7f);
    *(undefined4 *)(timer_st + 0x18) = 0;
    iVar1 = extraout_EAX;
  }
  return iVar1;
}


/* ==== timer_write_reg_core @ 00413840 ==== */

void __cdecl timer_write_reg_core(int reg,ulong val,int force)

{
  uint *puVar1;
  uint uVar2;
  
  puVar1 = (uint *)(timer_st + 0x10);
  uVar2 = *(uint *)(*(int *)(*(int *)(timer_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c);
  if (reg == 0) {
    *timer_regs = uVar2 & val;
  }
  else if (reg == 1) {
    uVar2 = (uVar2 & val ^ *(uint *)(timer_st + 4)) & 0x280 ^ uVar2 & val;
    *(uint *)(timer_st + 4) = uVar2;
    if ((((uVar2 & 1) != 0) && ((*puVar1 & 1) == 0)) || (force != 0)) {
      timer_start_mode(uVar2,*puVar1);
    }
    if ((uVar2 & 1) == 0) {
      *(undefined4 *)(timer_st + 0xc) = 0;
      *(undefined4 *)(timer_st + 0x10) = *(undefined4 *)(timer_st + 4);
    }
    if ((((uVar2 & 0x38) == 0) && ((uVar2 & 0x40) != 0)) && ((uVar2 & 0x100) != 0)) {
      if ((((uVar2 & 0x400) == 0) || (*(int *)(timer_st + 0x24) != 0)) &&
         (((uVar2 & 0x400) != 0 || (*(int *)(timer_st + 0x24) == 0)))) {
        timer_set_tio(0);
      }
      else {
        timer_set_tio(1);
      }
    }
  }
  else {
    timer_regs[reg] = uVar2 & val;
  }
  *(uint *)(timer_regflags + reg * 4) = *(uint *)(timer_regflags + reg * 4) | 0xa0000;
  if ((*(uint *)(timer_regflags + reg * 4) & 0x1800000) != 0) {
    io_out_periph_write((timer_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
  }
  return;
}


/* ==== timer_set_tio @ 00413980 ==== */

void __cdecl timer_set_tio(int level)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = *(uint *)(timer_dev + 8);
  *(uint *)(*(int *)(cur_dev + 0x18) + 0x5d4) = *(uint *)(*(int *)(cur_dev + 0x18) + 0x5d4) | uVar3;
  iVar1 = *(int *)(cur_dev + 0x18);
  if (level == 0) {
    uVar3 = *(uint *)(iVar1 + 0x5d0) & ~uVar3;
  }
  else {
    uVar3 = *(uint *)(iVar1 + 0x5d0) | uVar3;
  }
  *(uint *)(iVar1 + 0x5d0) = uVar3;
  uVar3 = *(uint *)(timer_st + 4);
  if (*(int *)(timer_st + 0x24) == level) {
    uVar2 = uVar3 & 0xfffffdff;
  }
  else {
    uVar2 = uVar3 | 0x200;
  }
  *(uint *)(timer_st + 4) = uVar2;
  if (uVar3 != *(uint *)(timer_st + 4)) {
    timer_refresh_reg(1);
  }
  return;
}


/* ==== timer_start_mode @ 00413a00 ==== */

void __cdecl timer_start_mode(ulong tcsr)

{
  uint uVar1;
  
  uVar1 = tcsr >> 3 & 7;
  switch(uVar1) {
  case 2:
    timer_st[8] = ~tcsr >> 2 & 1;
  default:
    timer_st[3] = 2;
    break;
  case 3:
    timer_st[3] = 0;
    break;
  case 4:
  case 5:
    timer_st[3] = 1;
  }
  timer_st[10] = 0;
  if (uVar1 != 4) {
    timer_st[2] = *timer_st;
  }
  if (uVar1 == 6) {
    timer_st[2] = *timer_st ^ 0xffffff;
    timer_set_reg(0,timer_st[2]);
  }
  timer_st[4] = timer_st[1];
  timer_st[9] = timer_st[1] >> 2 & 1;
  if ((uVar1 == 1) || (uVar1 == 2)) {
    timer_set_tio(timer_st[9]);
  }
  return;
}


/* ==== timer_refresh_reg @ 00413ae0 ==== */

void __cdecl timer_refresh_reg(int reg)

{
  int iVar1;
  
  if (reg < *(int *)(*(int *)(timer_dev + 0x2c) + 0x28)) {
    *(uint *)(timer_regflags + reg * 4) = *(uint *)(timer_regflags + reg * 4) | 0xa0000;
    *(uint *)(timer_regs + reg * 4) =
         *(uint *)(timer_regs + reg * 4) &
         *(uint *)(*(int *)(*(int *)(timer_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c);
    iVar1 = reg * 0x1c + *(int *)(*(int *)(timer_dev + 0x2c) + 0x2c);
    if ((*(byte *)(iVar1 + 0x10) & 0x60) != 0) {
      mem_trace_fetch(*(int *)(timer_dev + 0x1c) + *(int *)(iVar1 + 8));
    }
    if ((*(uint *)(timer_regflags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write((timer_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
    }
  }
  return;
}


/* ==== timer_read_reg_core @ 00413ba0 ==== */

void __cdecl timer_read_reg_core(int reg,ulong *out,int side)

{
  *out = *(ulong *)(timer_regs + reg * 4);
  return;
}


/* ==== timer_clock @ 00413bc0 ==== */

void timer_clock(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint mode;
  
  mode = (uint)timer_st[4] >> 3 & 7;
  if ((*(uint *)(timer_dev + 8) & *(uint *)(*(int *)(cur_dev + 0x18) + 0x5cc)) != 0) {
    uVar1 = timer_st[1];
    uVar2 = (uint)((*(uint *)(*(int *)(cur_dev + 0x18) + 0x5c8) & *(uint *)(timer_dev + 8)) != 0);
    if (mode == 0) {
      if ((uVar1 & 0x100) == 0) goto LAB_00413c10;
    }
    else if (2 < mode) {
LAB_00413c10:
      if (timer_st[9] == uVar2) {
        timer_st[1] = uVar1 & 0xfffffdff;
      }
      else {
        timer_st[1] = uVar1 | 0x200;
      }
      if (uVar1 != timer_st[1]) {
        timer_refresh_reg(1);
        timer_st[10] = 2 - (uint)(uVar2 != 0);
      }
    }
  }
  if (timer_st[3] == 0) {
    return;
  }
  if ((timer_st[10] != 0) && ((mode == 4 || (mode == 5)))) {
    if ((timer_st[3] == 1) && (iVar3 = timer_edge_match((uint)(timer_st[9] == 0)), iVar3 != 0)) {
      timer_st[3] = 2;
      if (mode == 4) {
        timer_st[2] = 0;
        return;
      }
      timer_st[2] = *timer_st;
    }
    else if ((timer_st[3] != 2) ||
            (((mode != 4 || (iVar3 = timer_edge_match(timer_st[9]), iVar3 == 0)) &&
             ((mode != 5 || (iVar3 = timer_edge_match((uint)(timer_st[9] == 0)), iVar3 == 0))))))
    goto LAB_00413d0a;
    timer_expire(mode);
  }
LAB_00413d0a:
  if ((*(int *)(timer_chipflags + 4) != 0) && (timer_st[3] == 2)) {
    switch(mode) {
    case 0:
    case 1:
    case 2:
      if (timer_st[2] == 0) {
        timer_expire(mode);
        return;
      }
      if ((mode == 1) && (timer_st[2] == *timer_st)) {
        timer_set_tio(timer_st[9]);
      }
      timer_st[2] = timer_st[2] + -1;
      return;
    case 4:
    case 5:
      timer_st[2] = timer_st[2] + 1U & 0xffffff;
      if (timer_st[7] != 0) {
        timer_set_reg(0,timer_st[2]);
        timer_st[7] = 0;
      }
      break;
    case 6:
      iVar3 = timer_edge_match((uint)(timer_st[9] == 0));
      if (iVar3 != 0) {
        timer_st[2] = timer_st[2] + 1U & 0xffffff;
        timer_set_reg(0,timer_st[2]);
        if (timer_st[2] == 0) {
          timer_expire(6);
          return;
        }
      }
      break;
    case 7:
      iVar3 = timer_edge_match((uint)(timer_st[9] == 0));
      if (iVar3 != 0) {
        if (timer_st[2] == 0) {
          timer_expire(7);
          return;
        }
        timer_st[2] = timer_st[2] + -1;
        return;
      }
    }
  }
  return;
}


/* ==== timer_edge_match @ 00413e60 ==== */

int __cdecl timer_edge_match(int level)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  iVar1 = *(int *)(timer_st + 0x28);
  if (iVar1 == 0) {
    return 0;
  }
  if (iVar1 == 1) {
    uVar2 = (uint)(level == 1);
  }
  else if (iVar1 == 2) {
    *(undefined4 *)(timer_st + 0x28) = 0;
    return (uint)(level == 0);
  }
  *(undefined4 *)(timer_st + 0x28) = 0;
  return uVar2;
}


/* ==== timer_expire @ 00413ea0 ==== */

void __cdecl timer_expire(int mode)

{
  timer_st[1] = timer_st[1] | 0x80;
  timer_refresh_reg(1);
  if ((*(byte *)(timer_st + 1) & 2) != 0) {
    timer_st[6] = 1;
  }
  switch(mode) {
  case 0:
  case 7:
    goto switchD_00413ed9_caseD_0;
  case 1:
    timer_set_tio((uint)(timer_st[9] == 0));
    timer_st[2] = *timer_st;
    return;
  case 2:
    timer_set_tio(timer_st[8]);
    timer_st[8] = timer_st[8] ^ 1;
switchD_00413ed9_caseD_0:
    timer_st[2] = *timer_st;
    return;
  default:
    return;
  case 4:
    timer_st[3] = 1;
    timer_set_reg(0,timer_st[2]);
    return;
  case 5:
    timer_st[7] = 1;
    return;
  }
}


