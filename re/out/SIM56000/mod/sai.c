/* ==== pin_drive_update @ 0040fba0 ==== */

void __cdecl pin_drive_update(ulong ctl,int mode,void *pingrp,ulong mask)

{
  uint uVar1;
  
  uVar1 = *(uint *)((int)pingrp + 8) | mask;
  *(uint *)((int)pingrp + 0xc) = *(uint *)((int)pingrp + 0xc) | mask;
  *(uint *)((int)pingrp + 8) = uVar1;
  if (mode == 0x180) {
    if ((ctl & 0x80000) != 0) {
      if ((ctl & 0x8000) != 0) {
        return;
      }
      *(ulong *)((int)pingrp + 8) = ~mask & uVar1;
      return;
    }
  }
  else {
    if (mode == 0x80) {
      if ((ctl & 0x80000) != 0) {
        return;
      }
      *(ulong *)((int)pingrp + 8) = ~mask & uVar1;
      return;
    }
    if (mode != 0x100) {
      return;
    }
    if ((ctl & 0x8000) != 0) {
      return;
    }
  }
  *(ulong *)((int)pingrp + 8) = ~mask & uVar1;
  return;
}


/* ==== sai_iofile_parse @ 0040fc20 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sai_iofile_parse(char *text,void *state)

{
  undefined4 uVar1;
  char cVar2;
  undefined3 extraout_var;
  
  io_parse_value(text,state,0x4000001);
  uVar1 = *(undefined4 *)((int)state + 0x188);
  cVar2 = strchr(text,0x3a);
  if (CONCAT31(extraout_var,cVar2) != 0) {
    text = (char *)(CONCAT31(extraout_var,cVar2) + 1);
  }
  io_parse_value(text,state,0x4000001);
  *(undefined4 *)((int)state + 0x18c) = *(undefined4 *)((int)state + 0x188);
  *(undefined4 *)((int)state + 0x188) = uVar1;
  return 1;
}


/* ==== sai_iofile_format @ 0040fc80 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sai_iofile_format(void *rec,int arg2,char *out)

{
  uint uVar1;
  char *fmt;
  undefined4 uStack_78;
  undefined4 uStack_74;
  uint uStack_70;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  uint uStack_48;
  undefined4 uStack_28;
  undefined4 uStack_24;
  uint uStack_20;
  
  uVar1 = *(uint *)(sai_st + 0x10);
  uStack_20 = *(uint *)arg2;
  uStack_48 = *(uint *)(arg2 + 4);
  uStack_70 = *(uint *)(arg2 + 8);
  if ((uVar1 & 0x20) == 0) {
    if ((uVar1 & 0x10) == 0) {
      uStack_20 = uStack_20 >> 8;
      uStack_48 = uStack_48 >> 8;
      uStack_70 = uStack_70 >> 8;
    }
  }
  else if ((uVar1 & 0x40) == (uVar1 >> 4 & 0x40)) {
    uStack_70 = uStack_70 << 8;
    uVar1 = uStack_20 << 8;
    if ((uStack_20 << 8 & 0x100) != 0) {
      uVar1 = CONCAT31((int3)uStack_20,0xff);
    }
    uStack_20 = uVar1;
    uVar1 = uStack_48 << 8;
    if ((uStack_48 << 8 & 0x100) != 0) {
      uVar1 = CONCAT31((int3)uStack_48,0xff);
    }
    uStack_48 = uVar1;
    if ((uStack_70 & 0x100) != 0) {
      uStack_70 = uStack_70 | 0xff;
    }
  }
  else {
    if ((uStack_20 & 0x800000) != 0) {
      uStack_20 = uStack_20 | 0xff000000;
    }
    if ((uStack_48 & 0x800000) != 0) {
      uStack_48 = uStack_48 | 0xff000000;
    }
    if ((uStack_70 & 0x800000) != 0) {
      uStack_70 = uStack_70 | 0xff000000;
    }
  }
  switch(*(undefined4 *)((int)rec + 0x1d4)) {
  case 0:
    fmt = (char *)0x4b6674;
    break;
  case 1:
    word_to_frac(*(ulong *)(cur_dtype + 0xc),&uStack_28);
    word_to_frac(*(ulong *)(cur_dtype + 0xc),&uStack_50);
    word_to_frac(*(ulong *)(cur_dtype + 0xc),&uStack_78);
    sprintf(out,s__f__f__f_004b6668,uStack_28,uStack_24,uStack_50,uStack_4c,uStack_78,uStack_74);
    return 1;
  case 2:
  case 3:
    sprintf(out,s__01lx__01lx__01lx_004b6654,uStack_20,uStack_48,uStack_70);
    return 1;
  case 4:
    fmt = (char *)0x4b6640;
    break;
  default:
    goto switchD_0040fd2c_default;
  }
  sprintf(out,fmt,uStack_20,uStack_48,uStack_70);
switchD_0040fd2c_default:
  return 1;
}


/* ==== sai_load_input @ 0040fe30 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl sai_load_input(int dev,void *rec)

{
  uint uVar1;
  
  _sai_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  sai_st = *_sai_stslot;
  uVar1 = *(uint *)(sai_st + 4);
  *(undefined4 *)(sai_st + 0x1b8) = *(undefined4 *)((int)rec + 8);
  *(undefined4 *)(sai_st + 0x1bc) = *(undefined4 *)((int)rec + 0xc);
  if ((uVar1 & 0x30) == 0) {
    *(int *)(sai_st + 0x1b8) = *(int *)(sai_st + 0x1b8) << 8;
    *(int *)(sai_st + 0x1bc) = *(int *)(sai_st + 0x1bc) << 8;
  }
  *(undefined4 *)(sai_st + 0x17c) = 1;
  return;
}


/* ==== sai_write_reg @ 0040feb0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sai_write_reg(int dev,int reg,ulong *val)

{
  int iVar1;
  
  sai_status = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbcbc = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  sai_regflags = *(undefined4 *)(sai_status + 4);
  _sai_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  sai_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  sai_st = *_sai_stslot;
  iVar1 = *(int *)(sai_dev + 0x2c);
  if ((reg < *(int *)(iVar1 + 0x28)) &&
     ((*(byte *)(*(int *)(iVar1 + 0x2c) + 0x10 + reg * 0x1c) & 0x40) != 0)) {
    sai_write_reg_core(reg,*val);
    sai_refresh_reg(reg);
    return 1;
  }
  if (reg < *(int *)(iVar1 + 0x24)) {
    *(ulong *)(sai_st + reg * 4) = *val;
  }
  sai_refresh_reg(reg);
  return 1;
}


/* ==== sai_tick @ 0040ff80 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void sai_tick(int dev)

{
  sai_status = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbcbc = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  sai_regflags = *(undefined4 *)(sai_status + 4);
  _sai_stslot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  sai_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  sai_st = *_sai_stslot;
  sai_chipflags = *(int *)(cur_dev + 0x40);
  if ((*(int *)(sai_chipflags + 0xc) == 0) && (*(int *)(sai_chipflags + 8) != 1)) {
    sai_clock(dev);
  }
  return;
}


/* ==== sai_write_io @ 00410010 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sai_write_io(int dev,ulong addr,ulong val)

{
  int reg;
  
  sai_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  switch(addr - *(int *)(sai_dev + 0x1c)) {
  case 0:
    reg = 0;
    break;
  case 1:
    reg = 1;
    break;
  case 2:
    reg = 2;
    break;
  case 3:
    reg = 3;
    break;
  case 4:
    reg = 4;
    break;
  case 5:
    reg = 5;
    break;
  case 6:
    reg = 6;
    break;
  case 7:
    reg = 7;
    break;
  default:
    if (addr != 0xffff) {
      return 0;
    }
    reg = 8;
  }
  sai_status = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbcbc = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  sai_regflags = *(undefined4 *)(sai_status + 4);
  _sai_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  sai_st = *_sai_stslot;
  if (reg != 8) {
    sai_write_reg_core(reg,val);
    return 0;
  }
  *(uint *)(sai_st + 0x20) = *(uint *)(sai_dev + 0x28) & val;
  return 0;
}


/* ==== sai_read_io @ 00410110 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sai_read_io(int dev,ulong addr,ulong *out,int side)

{
  int iVar1;
  int extraout_EAX;
  
  sai_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  _sai_stslot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  sai_st = *_sai_stslot;
  iVar1 = addr - *(int *)(sai_dev + 0x1c);
  switch(iVar1) {
  case 0:
    iVar1 = 0;
    break;
  case 1:
    iVar1 = 1;
    break;
  case 2:
    iVar1 = 2;
    break;
  case 3:
    iVar1 = 3;
    break;
  case 4:
    iVar1 = 4;
    break;
  case 5:
    iVar1 = 5;
    break;
  case 6:
    iVar1 = 6;
    break;
  case 7:
    iVar1 = 7;
    break;
  default:
    goto switchD_00410153_default;
  }
  sai_status = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbcbc = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  sai_regflags = *(undefined4 *)(sai_status + 4);
  sai_read_reg_core(iVar1,out,side);
  iVar1 = extraout_EAX;
switchD_00410153_default:
  return iVar1;
}


/* ==== sai_reset @ 004101f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sai_reset(int dev)

{
  int extraout_EAX;
  int iVar1;
  int in_stack_00000008;
  
  sai_status = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbcbc = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  sai_regflags = *(undefined4 *)(sai_status + 4);
  _sai_stslot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  sai_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  sai_st = *_sai_stslot;
  iVar1 = 0;
  if (in_stack_00000008 != 0) {
    sai_reset_regs();
    iVar1 = extraout_EAX;
  }
  return iVar1;
}


/* ==== sai_reset_regs @ 00410270 ==== */

void sai_reset_regs(void)

{
  sai_st[4] = 0;
  sai_st[1] = 0;
  *sai_st = 0;
  sai_refresh_reg(0);
  sai_refresh_reg(1);
  sai_refresh_reg(4);
  sai_st[0xc] = 0;
  sai_st[0xe] = 0;
  sai_st[10] = 0;
  sai_st[0xb] = 0;
  sai_st[0xd] = 0;
  sai_st[9] = 0;
  sai_st[0xf] = 0;
  sai_st[0x10] = 0;
  *sai_status = 0x24;
  return;
}


/* ==== sai_int_pending @ 00410300 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long sai_int_pending(int dev)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  _sai_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  sai_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  sai_st = *_sai_stslot;
  if (*(int *)(sai_st + 0x20) == 0) {
    return -1;
  }
  iVar1 = *(int *)(sai_dev + 0x20);
  if ((*(uint *)(cur_dtype + 8) & 0x3610) == 0) {
    if (*(int *)(sai_st + 0x24) != 0) {
      return iVar1 + 10;
    }
    if (*(int *)(sai_st + 0x34) != 0) {
      return iVar1 + 8;
    }
    if (*(int *)(sai_st + 0x2c) != 0) {
      return iVar1 + 6;
    }
    if (*(int *)(sai_st + 0x28) != 0) {
      return iVar1 + 4;
    }
    if (*(int *)(sai_st + 0x38) != 0) {
      return iVar1 + 2;
    }
    if (*(int *)(sai_st + 0x30) != 0) {
      return iVar1;
    }
  }
  else {
    uVar2 = -(uint)((*(uint *)(sai_st + 4) & 0x1000) != 0) & 0x30;
    uVar3 = -(uint)((*(uint *)(sai_st + 0x10) & 0x1000) != 0) & 0x30;
    if (*(int *)(sai_st + 0x24) != 0) {
      return iVar1 + 10 + uVar2;
    }
    if (*(int *)(sai_st + 0x34) != 0) {
      return iVar1 + 8 + uVar2;
    }
    if (*(int *)(sai_st + 0x2c) != 0) {
      return iVar1 + 6 + uVar2;
    }
    if (*(int *)(sai_st + 0x28) != 0) {
      return iVar1 + 4 + uVar3;
    }
    if (*(int *)(sai_st + 0x38) != 0) {
      return iVar1 + 2 + uVar3;
    }
    if (*(int *)(sai_st + 0x30) != 0) {
      return iVar1 + uVar3;
    }
  }
  return -1;
}


/* ==== sai_int_ack @ 00410410 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sai_int_ack(int dev,long vec)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  _sai_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  sai_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  sai_st = *_sai_stslot;
  uVar1 = vec - *(int *)(sai_dev + 0x20);
  if ((*(uint *)(cur_dtype + 8) & 0x3610) == 0) {
    if (vec == *(int *)(sai_dev + 0x20)) {
      *(undefined4 *)(sai_st + 0x30) = 0;
      return 0xc;
    }
    if (uVar1 == 2) {
      *(undefined4 *)(sai_st + 0x38) = 0;
      return 0xe;
    }
    if (uVar1 == 4) {
      *(undefined4 *)(sai_st + 0x28) = 0;
      return 10;
    }
    if (uVar1 == 6) {
      *(undefined4 *)(sai_st + 0x2c) = 0;
      return 0xb;
    }
    iVar2 = (-(uint)(uVar1 != 8) & 0xfffffffc) + 0xd;
    *(undefined4 *)(sai_st + iVar2 * 4) = 0;
    return iVar2;
  }
  uVar4 = -(uint)((*(uint *)(sai_st + 4) & 0x1000) != 0) & 0x30;
  uVar3 = -(uint)((*(uint *)(sai_st + 0x10) & 0x1000) != 0) & 0x30;
  if (uVar1 == uVar3) {
    *(undefined4 *)(sai_st + 0x30) = 0;
    return 0xc;
  }
  if (uVar1 == uVar3 + 2) {
    *(undefined4 *)(sai_st + 0x38) = 0;
    return 0xe;
  }
  if (uVar1 == uVar3 + 4) {
    *(undefined4 *)(sai_st + 0x28) = 0;
    return 10;
  }
  if (uVar1 == uVar4 + 6) {
    *(undefined4 *)(sai_st + 0x2c) = 0;
    return 0xb;
  }
  iVar2 = (-(uint)(uVar1 != uVar4 + 8) & 0xfffffffc) + 0xd;
  *(undefined4 *)(sai_st + iVar2 * 4) = 0;
  return iVar2;
}


/* ==== sai_write_reg_core @ 00410550 ==== */

void __cdecl sai_write_reg_core(int reg,ulong val)

{
  switch(reg) {
  default:
    goto switchD_00410565_caseD_0;
  case 1:
    if ((val & 3) == 0) {
      *sai_status = 0x24;
      *(uint *)(sai_st + 4) = *(uint *)(sai_st + 4) & 0xffff3fff;
      *(undefined4 *)(sai_st + 0x9c) = 0;
    }
    else {
      *sai_status = 0x25;
    }
    if ((val & 1) == 0) {
      *(undefined4 *)(sai_st + 0x94) = 0;
    }
    if ((val & 2) == 0) {
      *(undefined4 *)(sai_st + 0x98) = 0;
    }
    val = (*(uint *)(sai_st + 4) ^ val) & 0xc000 ^ val;
    goto LAB_004106e0;
  case 4:
    val = (*(uint *)(sai_st + 0x10) ^ val) & 0xc000 ^ val;
    goto LAB_004106e0;
  case 5:
    if (*(int *)(sai_st + 0x13c) != 0) goto LAB_004106e0;
    *(uint *)(sai_st + 0xec) = *(uint *)(sai_st + 0xec) & 0xfffffffe;
    *(uint *)(sai_st + 0xec) = *(uint *)(sai_st + 0xec) & *(uint *)(sai_st + 0x10) & 7;
    break;
  case 6:
    if (*(int *)(sai_st + 0x13c) != 0) goto LAB_004106e0;
    *(uint *)(sai_st + 0xec) = *(uint *)(sai_st + 0xec) & 0xfffffffd;
    *(uint *)(sai_st + 0xec) = *(uint *)(sai_st + 0xec) & *(uint *)(sai_st + 0x10) & 7;
    break;
  case 7:
    if (*(int *)(sai_st + 0x13c) != 0) goto LAB_004106e0;
    *(uint *)(sai_st + 0xec) = *(uint *)(sai_st + 0xec) & 0xfffffffb;
    *(uint *)(sai_st + 0xec) = *(uint *)(sai_st + 0xec) & *(uint *)(sai_st + 0x10) & 7;
    if (*(int *)(sai_st + 0xec) != 0) goto LAB_004106e0;
    goto LAB_004106c8;
  }
  if (*(int *)(sai_st + 0xec) == 0) {
LAB_004106c8:
    *(uint *)(sai_st + 0x10) = *(uint *)(sai_st + 0x10) & 0xffff3fff;
    sai_refresh_reg(4);
switchD_00410565_caseD_0:
  }
LAB_004106e0:
  *(uint *)(sai_st + reg * 4) =
       *(uint *)(*(int *)(*(int *)(sai_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c) & val;
  *(uint *)(sai_regflags + reg * 4) = *(uint *)(sai_regflags + reg * 4) | 0xa0000;
  if ((*(uint *)(sai_regflags + reg * 4) & 0x1800000) != 0) {
    io_out_periph_write((sai_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
  }
  return;
}


/* ==== sai_refresh_reg @ 00410770 ==== */

void __cdecl sai_refresh_reg(int reg)

{
  int iVar1;
  
  if (reg < *(int *)(*(int *)(sai_dev + 0x2c) + 0x28)) {
    *(uint *)(sai_regflags + reg * 4) = *(uint *)(sai_regflags + reg * 4) | 0xa0000;
    *(uint *)(sai_st + reg * 4) =
         *(uint *)(sai_st + reg * 4) &
         *(uint *)(*(int *)(*(int *)(sai_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c);
    iVar1 = reg * 0x1c + *(int *)(*(int *)(sai_dev + 0x2c) + 0x2c);
    if ((*(byte *)(iVar1 + 0x10) & 0x60) != 0) {
      mem_trace_fetch(*(int *)(sai_dev + 0x1c) + *(int *)(iVar1 + 8));
    }
    if ((*(uint *)(sai_regflags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write((sai_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
    }
  }
  return;
}


/* ==== sai_read_reg_core @ 00410830 ==== */

void __cdecl sai_read_reg_core(int reg,ulong *out,int side)

{
  int iVar1;
  
  *out = *(ulong *)(sai_st + reg * 4);
  if (side == 0) {
    return;
  }
  switch(reg) {
  case 1:
    *(undefined4 *)(sai_st + 0x9c) = 0;
    return;
  case 2:
    if (*(int *)(sai_st + 0x9c) != 0) {
      return;
    }
    *(undefined4 *)(sai_st + 0x94) = 0;
    iVar1 = *(int *)(sai_st + 0x98);
    break;
  case 3:
    if (*(int *)(sai_st + 0x9c) != 0) {
      return;
    }
    *(undefined4 *)(sai_st + 0x98) = 0;
    iVar1 = *(int *)(sai_st + 0x94);
    break;
  case 4:
    *(undefined4 *)(sai_st + 0x13c) = 0;
  default:
    goto switchD_00410853_default;
  }
  if (iVar1 == 0) {
    *(uint *)(sai_st + 4) = *(uint *)(sai_st + 4) & 0xffff3fff;
    sai_refresh_reg(1);
    return;
  }
switchD_00410853_default:
  return;
}


/* ==== sai_clock @ 004108e0 ==== */

void __cdecl sai_clock(int dev)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  uint uVar26;
  uint local_7c;
  uint local_74;
  ulong local_28 [10];
  
  uVar12 = sai_st[4];
  uVar23 = *(uint *)(sai_dev + 8);
  local_7c = sai_st[1];
  uVar23 = uVar23 & (uVar23 - 1 ^ uVar23);
  uVar19 = uVar23 * 2;
  uVar5 = uVar23 << 4;
  uVar6 = uVar23 << 6;
  uVar7 = uVar23 << 7;
  uVar8 = uVar23 << 8;
  uVar24 = uVar23 << 5;
  puVar1 = (uint *)(*(int *)(cur_dev + 0x18) + *(int *)(sai_dev + 4) * 0x128);
  uVar2 = *puVar1;
  uVar20 = uVar23 * 4 & uVar2;
  uVar21 = uVar23 * 8 & uVar2;
  uVar25 = uVar24 & uVar2;
  uVar22 = uVar19 & uVar2;
  uVar9 = uVar12 & 8;
  uVar13 = uVar12 & 0x100;
  uVar26 = local_7c & 8;
  uVar14 = local_7c & 1;
  uVar15 = local_7c & 2;
  uVar18 = local_7c & 0x100;
  uVar16 = local_7c >> 6 & 1;
  uVar17 = local_7c & 0x200;
  sai_st[0x19] = local_7c >> 10 & 1;
  if ((((uVar14 == 0) && (uVar15 == 0)) || (*(int *)(sai_chipflags + 0xc) != 0)) ||
     (*(int *)(sai_chipflags + 8) == 1)) {
    uVar10 = 1;
  }
  else {
    uVar10 = 0;
  }
  sai_st[0x1b] = uVar10;
  if (sai_st[0x1b] != 0) {
    sai_st[0x1a] = 0;
    sai_st[0x1f] = 0;
    sai_st[0x1e] = 0;
    sai_st[0x1c] = 0;
    sai_st[0x5f] = 0;
    sai_st[0x1d] = 1;
    local_7c = local_7c & 0xffff3fff;
    if (local_7c != sai_st[1]) {
      sai_refresh_reg(1);
    }
  }
  if (uVar26 == 0 && uVar9 == 0) {
    sai_st[0x10] = 0;
    sai_st[0xf] = 0;
  }
  else {
    if (sai_st[0xf] != 0) {
      sai_st[0xf] = sai_st[0xf] - 1;
    }
    if (sai_st[0xf] == 0) {
      uVar3 = *sai_st;
      sai_st[0xf] = (uVar3 & 0xff) + 1;
      if ((uVar3 & 0x100) == 0) {
        sai_st[0xf] = sai_st[0xf] << 3;
      }
      sai_st[0x10] = (uint)(sai_st[0x10] == 0);
    }
  }
  if ((uVar14 == 0) && (uVar15 == 0)) {
    uVar22 = 0;
  }
  else if (uVar26 == 0) {
    if (uVar18 != 0) {
      uVar22 = (uint)(uVar22 == 0);
    }
  }
  else {
    uVar22 = sai_st[0x10];
  }
  if ((uVar10 == 0) && (uVar26 != 0)) {
    if (uVar18 == 0) {
LAB_00410b33:
      if (uVar22 != 0) {
LAB_00410b4d:
        puVar1[2] = puVar1[2] | uVar19;
        uVar19 = puVar1[3] | uVar19;
        goto LAB_00410b73;
      }
    }
    else if (uVar22 == 0) {
      if (uVar18 == 0) goto LAB_00410b33;
      goto LAB_00410b4d;
    }
    puVar1[2] = puVar1[2] & ~uVar19;
    uVar19 = puVar1[3] | uVar19;
  }
  else {
    uVar19 = puVar1[3] & ~uVar19;
  }
LAB_00410b73:
  puVar1[3] = uVar19;
  if (uVar10 == 0) {
    if (uVar22 != 0) {
      sai_st[0x13] = 1;
    }
  }
  else {
    sai_st[0x13] = 0;
  }
  if (sai_st[0x13] == 0) {
    sai_st[0x15] = 0;
    sai_st[0x48] = 0;
    sai_st[0x4a] = 0;
    sai_st[0x49] = 1;
    sai_st[0x2f] = 1;
    sai_st[0x22] = 2;
    sai_st[0x14] = 2;
  }
  else {
    sai_st[0x15] = (uint)(uVar22 == 0);
    sai_st[0x2f] = (uint)(uVar22 != 0);
  }
  if (sai_st[0x15] != sai_st[0x48]) {
    uVar22 = sai_st[0x4a];
    if (uVar22 == 0) {
      sai_st[0x4a] = 1;
      sai_st[0x14] = 4;
      sai_tx_decode_terms();
    }
    else if (uVar22 == 1) {
      if (sai_st[0x51] == 0) {
        sai_st[0x4a] = 2;
        sai_st[0x14] = 8;
      }
      else {
LAB_00410ca8:
        sai_st[0x4a] = 0;
        sai_st[0x14] = 2;
      }
    }
    else if (uVar22 == 2) {
      sai_st[0x4a] = 3;
      sai_st[0x14] = 1;
      sai_tx_terms_to_flags();
    }
    else if (uVar22 == 3) goto LAB_00410ca8;
  }
  uVar22 = local_7c & 0x30;
  if (sai_st[0x2f] != 0) {
    if (sai_st[0x49] == 0) {
      if (uVar16 == 0) {
        sai_st[0x11] = sai_st[0x11] << 1;
        if (uVar20 != 0) {
          sai_st[0x11] = sai_st[0x11] | (-(uint)(uVar22 != 0) & 0xffffff01) + 0x100;
        }
      }
      else {
        sai_st[0x11] = sai_st[0x11] >> 1;
        if (uVar20 != 0) {
          sai_st[0x11] = sai_st[0x11] | 0x800000;
        }
        if (uVar22 == 0) {
          sai_st[0x11] = sai_st[0x11] & 0xffffff00;
        }
      }
    }
    if ((sai_st[0x2f] != 0) && (sai_st[0x49] == 0)) {
      if (uVar16 == 0) {
        sai_st[0x12] = sai_st[0x12] << 1;
        if (uVar21 != 0) {
          sai_st[0x12] = sai_st[0x12] | (-(uint)(uVar22 != 0) & 0xffffff01) + 0x100;
        }
      }
      else {
        sai_st[0x12] = sai_st[0x12] >> 1;
        if (uVar21 != 0) {
          sai_st[0x12] = sai_st[0x12] | 0x800000;
        }
        if (uVar22 == 0) {
          sai_st[0x12] = sai_st[0x12] & 0xffffff00;
        }
      }
    }
  }
  if (uVar10 == 0) {
    if (((sai_st[0x52] == 0) && (sai_st[0x1c] != 0)) && (sai_st[0x21] == 0)) {
      sai_st[0x52] = 1;
    }
    if (sai_st[0x52] == 1) {
      if ((sai_st[0x14] == 4) && (sai_st[0x22] != 4)) {
        sai_st[0x20] = 1;
        sai_st[0x52] = 3;
      }
    }
    else if (sai_st[0x52] == 3) {
      sai_st[0x52] = 0;
      sai_st[0x20] = 0;
    }
  }
  else {
    sai_st[0x52] = 0;
    sai_st[0x20] = 0;
    sai_st[0x21] = 0;
  }
  if (uVar10 != 0) {
    sai_st[0x23] = 0;
  }
  if ((sai_st[0x20] != 0) && (sai_st[0x24] == 0)) {
    sai_st[1] = sai_st[1] | (-(uint)(sai_st[0x23] != 0) & 0x4000) + 0x4000;
    iVar11 = io_in_pin_read(dev,local_28);
    if (iVar11 != 0) {
      sai_load_input(dev,local_28);
    }
    if (sai_st[0x5f] != 0) {
      sai_st[0x11] = sai_st[0x6e];
      sai_st[0x12] = sai_st[0x6f];
    }
    sai_refresh_reg(1);
    sai_st[2] = sai_st[0x11] & 0xffffff;
    sai_refresh_reg(2);
    sai_refresh_reg(3);
    sai_st[3] = sai_st[0x12] & 0xffffff;
    sai_st[0x23] = (uint)(sai_st[0x23] == 0);
    if (((sai_st[1] ^ local_7c) & 0xc000) != 0) {
      if (uVar14 != 0) {
        sai_st[0x25] = 1;
      }
      if (uVar15 != 0) {
        sai_st[0x26] = 1;
      }
      if ((sai_st[1] & 0xc000) == 0xc000) {
        sai_st[0x27] = 1;
      }
    }
  }
  if (sai_st[0x28] == 0) {
    if (sai_st[0x1d] != 0) {
      sai_st[0x2a] = ~local_7c >> 7 & 1;
    }
    if (sai_st[0x1e] != 0) {
      if ((uVar26 == 0) || (uVar17 != 0)) {
        sai_st[0x2a] = (uint)(sai_st[0x2a] == 0);
        sai_st[0x28] = 2;
      }
      else {
        sai_st[0x28] = 1;
      }
    }
  }
  if (((sai_st[0x28] == 1) && (sai_st[0x14] == 4)) && (sai_st[0x22] != 4)) {
    sai_st[0x2a] = (uint)(sai_st[0x2a] == 0);
    sai_st[0x28] = 2;
  }
  if (((sai_st[0x28] == 2) && (sai_st[0x14] == 4)) && (sai_st[0x22] != 4)) {
    sai_st[0x28] = 3;
  }
  if (((sai_st[0x28] == 3) && (sai_st[0x14] == 1)) && (sai_st[0x22] != 1)) {
    sai_st[0x28] = 0;
  }
  if (uVar10 == 0) {
    if (uVar26 == 0) {
      puVar1[3] = puVar1[3] & ~uVar23;
      sai_st[0x2b] = (uint)((uVar23 & uVar2) != 0);
    }
    else {
      sai_st[0x2b] = sai_st[0x2a];
      if (sai_st[0x2a] == 0) {
        puVar1[2] = puVar1[2] & ~uVar23;
        puVar1[3] = puVar1[3] | uVar23;
      }
      else {
        puVar1[2] = puVar1[2] | uVar23;
        puVar1[3] = puVar1[3] | uVar23;
      }
    }
  }
  else {
    puVar1[3] = puVar1[3] & ~uVar23;
    if ((local_7c & 0x80) == 0) {
      puVar1[2] = puVar1[2] | uVar23;
    }
    else {
      puVar1[2] = puVar1[2] & ~uVar23;
    }
    if (uVar26 == 0) {
      sai_st[0x2d] = (uint)((uVar23 & uVar2) != 0);
      sai_st[0x53] = sai_st[0x2d];
      sai_st[0x2b] = sai_st[0x53];
    }
  }
  if (sai_st[0x2e] == 0) {
    if (uVar17 == 0) {
      if ((sai_st[0x15] != 0) && (sai_st[0x48] == 0)) {
        sai_st[0x53] = sai_st[0x2b];
        sai_st[0x2e] = 1;
      }
    }
    else if ((sai_st[0x14] == 4) && (sai_st[0x22] != 4)) {
      sai_st[0x53] = sai_st[0x2b];
      sai_st[0x2e] = 3;
    }
  }
  if (((sai_st[0x2e] == 1) && (sai_st[0x14] == 2)) && (sai_st[0x22] != 2)) {
    sai_st[0x2d] = sai_st[0x53];
    sai_st[0x2e] = 0;
  }
  if (((sai_st[0x2e] == 3) && (sai_st[0x2f] != 0)) && (sai_st[0x49] == 0)) {
    sai_st[0x2d] = sai_st[0x53];
    sai_st[0x2e] = 0;
  }
  if (((sai_st[0x14] == 1) && (sai_st[0x22] != 1)) &&
     ((sai_st[0x1f] != 0 && ((sai_st[0x2a] == sai_st[0x2b] || (sai_st[0x2d] == sai_st[0x2b])))))) {
    sai_st[0x51] = 1;
  }
  if ((((sai_st[0x4c] == 0) && (sai_st[0x1f] != 0)) && (sai_st[0x2a] != sai_st[0x2b])) &&
     (sai_st[0x2d] != sai_st[0x2b])) {
    if (uVar17 == 0) {
      sai_st[0x51] = 0;
    }
    else {
      sai_st[0x4c] = 1;
    }
  }
  if (((sai_st[0x4c] == 1) && (sai_st[0x14] == 2)) && (sai_st[0x22] != 2)) {
    sai_st[0x51] = 0;
    sai_st[0x4c] = 0;
  }
  if (uVar10 != 0) {
    sai_st[0x51] = 0;
    sai_st[0x4a] = 0;
    sai_st[0x2e] = 0;
    sai_st[0x28] = 0;
    sai_st[0x4c] = 0;
    sai_st[0x29] = 0;
  }
  sai_st[0x21] = sai_st[0x1c];
  sai_st[0x24] = sai_st[0x20];
  sai_st[0x22] = sai_st[0x14];
  sai_st[0x48] = sai_st[0x15];
  sai_st[0x49] = sai_st[0x2f];
  uVar22 = uVar12 & 2;
  uVar23 = uVar12 & 1;
  uVar15 = uVar12 >> 6 & 1;
  uVar16 = uVar12 & 0x30;
  uVar14 = uVar12 & 0x200;
  uVar19 = uVar12 & 4;
  if ((((uVar23 == 0) && (uVar22 == 0)) && (uVar19 == 0)) ||
     ((*(int *)(sai_chipflags + 0xc) != 0 || (*(int *)(sai_chipflags + 8) == 1)))) {
    bVar4 = true;
    uVar17 = 1;
  }
  else {
    uVar17 = 0;
    bVar4 = false;
  }
  sai_st[0x30] = uVar17;
  local_74 = uVar12;
  if (uVar17 != 0) {
    local_74 = uVar12 & 0xffff3fff;
    sai_st[0x47] = 0;
    sai_st[0x46] = 0;
    sai_st[0x45] = 0;
    sai_st[0x40] = 0;
    sai_st[0x3d] = 0;
    sai_st[0x3c] = 0;
    sai_st[0x44] = 0;
    sai_st[0x43] = 0;
    sai_st[0x41] = 0;
    sai_st[0x42] = 1;
    if (local_74 != sai_st[4]) {
      sai_refresh_reg(4);
    }
  }
  if ((uVar12 & 7) == 0) {
    uVar25 = 0;
  }
  else if (uVar9 == 0) {
    if (uVar13 != 0) {
      uVar25 = (uint)(uVar25 == 0);
    }
  }
  else {
    uVar25 = sai_st[0x10];
  }
  if ((bVar4) || (uVar9 == 0)) {
    puVar1[3] = puVar1[3] & ~uVar24;
  }
  else {
    if (uVar13 == 0) {
LAB_00411488:
      if (uVar25 != 0) {
LAB_004114a4:
        puVar1[2] = puVar1[2] | uVar24;
        puVar1[3] = puVar1[3] | uVar24;
        goto LAB_004114c1;
      }
    }
    else if (uVar25 == 0) {
      if (uVar13 == 0) goto LAB_00411488;
      goto LAB_004114a4;
    }
    puVar1[2] = puVar1[2] & ~uVar24;
    puVar1[3] = puVar1[3] | uVar24;
  }
LAB_004114c1:
  if (bVar4) {
    sai_st[0x34] = 0;
  }
  else if (uVar25 != 0) {
    sai_st[0x34] = 1;
  }
  if (sai_st[0x34] == 0) {
    sai_st[0x36] = 0;
    sai_st[0x37] = 0;
    sai_st[0x3a] = 0;
    sai_st[0x39] = 1;
    sai_st[0x38] = 1;
    sai_st[0x5c] = 2;
    sai_st[0x5a] = 2;
  }
  else {
    sai_st[0x36] = (uint)(uVar25 == 0);
    sai_st[0x38] = uVar25;
  }
  sai_st[0x50] = uVar12 >> 10 & 1;
  if (sai_st[0x37] != sai_st[0x36]) {
    uVar25 = sai_st[0x3a];
    if (uVar25 == 0) {
      sai_st[0x3a] = 1;
      sai_st[0x5a] = 4;
      sai_rx_decode_terms();
    }
    else if (uVar25 == 1) {
      if (sai_st[0x60] == 0) {
        sai_st[0x3a] = 2;
        sai_st[0x5a] = 8;
      }
      else {
LAB_00411620:
        sai_st[0x3a] = 0;
        sai_st[0x5a] = 2;
      }
    }
    else if (uVar25 == 2) {
      sai_st[0x3a] = 3;
      sai_st[0x5a] = 1;
      sai_rx_terms_to_flags();
    }
    else if (uVar25 == 3) goto LAB_00411620;
  }
  if (bVar4) {
    sai_st[0x55] = 0;
    sai_st[0x4b] = 0;
  }
  else {
    if (((sai_st[0x4b] == 0) && (sai_st[0x41] != 0)) && (sai_st[0x5b] == 0)) {
      sai_st[0x4b] = 1;
    }
    if (sai_st[0x4b] == 1) {
      if ((sai_st[0x5a] == 2) && (sai_st[0x5c] != 2)) {
        sai_st[0x4b] = 2;
        sai_st[0x55] = 1;
      }
    }
    else if (sai_st[0x4b] == 2) {
      sai_st[0x4b] = 0;
      sai_st[0x55] = 0;
    }
  }
  if ((sai_st[0x55] != 0) && (sai_st[0x35] == 0)) {
    io_out_pin_write(dev,sai_st + 5,-1);
    sai_st[0x31] = sai_st[5];
    sai_st[0x32] = sai_st[6];
    sai_st[0x33] = sai_st[7];
  }
  if ((sai_st[0x36] != 0) && (sai_st[0x37] == 0)) {
    if (uVar15 == 0) {
      uVar25 = 0x800000;
    }
    else {
      uVar25 = (-(uint)(uVar16 != 0) & 0xffffff01) + 0x100;
    }
    sai_st[0x56] = sai_st[0x31] & uVar25;
    if (uVar15 == 0) {
      uVar25 = 0x800000;
    }
    else {
      uVar25 = (-(uint)(uVar16 != 0) & 0xffffff01) + 0x100;
    }
    sai_st[0x57] = sai_st[0x32] & uVar25;
    if (uVar15 == 0) {
      uVar25 = 0x800000;
    }
    else {
      uVar25 = (-(uint)(uVar16 != 0) & 0xffffff01) + 0x100;
    }
    sai_st[0x58] = sai_st[0x33] & uVar25;
  }
  if (((sai_st[0x38] != 0) && (sai_st[0x39] == 0)) && (sai_st[0x66] != 0)) {
    if (uVar15 == 0) {
      sai_st[0x31] = sai_st[0x31] << 1;
      if ((sai_st[0x31] & 2) != 0) {
        sai_st[0x31] = sai_st[0x31] | 1;
      }
      sai_st[0x32] = sai_st[0x32] << 1;
      if ((sai_st[0x32] & 2) != 0) {
        sai_st[0x32] = sai_st[0x32] | 1;
      }
      sai_st[0x33] = sai_st[0x33] << 1;
      if ((sai_st[0x33] & 2) != 0) {
        sai_st[0x33] = sai_st[0x33] | 1;
      }
    }
    else {
      sai_st[0x31] = sai_st[0x31] >> 1;
      uVar25 = sai_st[0x31];
      if ((uVar25 & 0x400000) == 0) {
        uVar25 = uVar25 & 0xff7fffff;
      }
      else {
        uVar25 = uVar25 | 0x800000;
      }
      sai_st[0x31] = uVar25;
      sai_st[0x32] = sai_st[0x32] >> 1;
      uVar25 = sai_st[0x32];
      if ((uVar25 & 0x400000) == 0) {
        uVar25 = uVar25 & 0xff7fffff;
      }
      else {
        uVar25 = uVar25 | 0x800000;
      }
      sai_st[0x32] = uVar25;
      sai_st[0x33] = sai_st[0x33] >> 1;
      uVar25 = sai_st[0x33];
      if ((uVar25 & 0x400000) == 0) {
        uVar25 = uVar25 & 0xff7fffff;
      }
      else {
        uVar25 = uVar25 | 0x800000;
      }
      sai_st[0x33] = uVar25;
    }
  }
  if (bVar4) {
    sai_st[0x5d] = 1;
  }
  if ((sai_st[0x55] != 0) && (sai_st[0x35] == 0)) {
    if ((local_74 & 0xc000) == 0xc000) {
      sai_st[0x4f] = 1;
    }
    sai_st[0x3b] = local_74 & 7;
    sai_st[4] = sai_st[4] | (-(uint)(sai_st[0x5d] != 0) & 0x4000) + 0x4000;
    sai_refresh_reg(4);
    sai_st[0x5d] = (uint)(sai_st[0x5d] == 0);
  }
  if (sai_st[0x4d] == 0) {
    if (sai_st[0x42] != 0) {
      sai_st[0x5e] = ~local_74 >> 7 & 1;
    }
    if (sai_st[0x43] != 0) {
      if ((uVar9 == 0) || (uVar14 != 0)) {
        sai_st[0x5e] = (uint)(sai_st[0x5e] == 0);
        sai_st[0x4d] = 2;
      }
      else {
        sai_st[0x4d] = 1;
      }
    }
  }
  if (((sai_st[0x4d] == 1) && (sai_st[0x5a] == 4)) && (sai_st[0x5c] != 4)) {
    sai_st[0x5e] = (uint)(sai_st[0x5e] == 0);
    sai_st[0x4d] = 2;
  }
  if (((sai_st[0x4d] == 2) && (sai_st[0x5a] == 4)) && (sai_st[0x5c] != 4)) {
    sai_st[0x4d] = 3;
  }
  if (((sai_st[0x4d] == 3) && (sai_st[0x5a] == 1)) && (sai_st[0x5c] != 1)) {
    sai_st[0x4d] = 0;
  }
  if (bVar4) {
    puVar1[3] = puVar1[3] & ~uVar5;
    if ((local_74 & 0x80) == 0) {
      puVar1[2] = puVar1[2] | uVar5;
    }
    else {
      puVar1[2] = puVar1[2] & ~uVar5;
    }
    if (uVar9 == 0) {
      sai_st[99] = (uint)((uVar5 & uVar2) != 0);
      sai_st[0x62] = sai_st[99];
      sai_st[0x61] = sai_st[0x62];
    }
  }
  else if (uVar9 == 0) {
    puVar1[3] = puVar1[3] & ~uVar5;
    sai_st[0x61] = (uint)((uVar5 & uVar2) != 0);
  }
  else {
    sai_st[0x61] = sai_st[0x5e];
    if (sai_st[0x5e] == 0) {
      puVar1[2] = puVar1[2] & ~uVar5;
      puVar1[3] = puVar1[3] | uVar5;
    }
    else {
      puVar1[2] = puVar1[2] | uVar5;
      puVar1[3] = puVar1[3] | uVar5;
    }
  }
  if (sai_st[0x4e] == 0) {
    if (uVar14 == 0) {
      if ((sai_st[0x36] != 0) && (sai_st[0x37] == 0)) {
        sai_st[0x62] = sai_st[0x61];
        sai_st[0x4e] = 1;
      }
    }
    else if ((sai_st[0x5a] == 4) && (sai_st[0x5c] != 4)) {
      sai_st[0x62] = sai_st[0x61];
      sai_st[0x4e] = 3;
    }
  }
  if (((sai_st[0x4e] == 1) && (sai_st[0x5a] == 2)) && (sai_st[0x5c] != 2)) {
    sai_st[99] = sai_st[0x62];
    sai_st[0x4e] = 0;
  }
  if (((sai_st[0x4e] == 3) && (sai_st[0x38] != 0)) && (sai_st[0x39] == 0)) {
    sai_st[99] = sai_st[0x62];
    sai_st[0x4e] = 0;
  }
  if (((sai_st[0x5a] == 1) && (sai_st[0x5c] != 1)) &&
     ((sai_st[0x44] != 0 && ((sai_st[0x5e] == sai_st[0x61] || (sai_st[99] == sai_st[0x61])))))) {
    sai_st[0x60] = 1;
  }
  if ((((sai_st[100] == 0) && (sai_st[0x44] != 0)) && (sai_st[0x5e] != sai_st[0x61])) &&
     (sai_st[99] != sai_st[0x61])) {
    if (uVar14 == 0) {
      sai_st[0x60] = 0;
    }
    else {
      sai_st[100] = 1;
    }
  }
  if (((sai_st[100] == 1) && (sai_st[0x5a] == 2)) && (sai_st[0x5c] != 2)) {
    sai_st[0x60] = 0;
    sai_st[100] = 0;
  }
  if (bVar4) {
    sai_st[0x60] = 0;
    sai_st[0x66] = 0;
    sai_st[0x4e] = 0;
    sai_st[0x4d] = 0;
    sai_st[0x6b] = 0;
    sai_st[0x67] = 0;
    sai_st[100] = 0;
  }
  if (((sai_st[0x67] == 0) && (sai_st[0x5a] == 1)) && (sai_st[0x5c] != 1)) {
    if (sai_st[0x46] != 0) {
      sai_st[0x66] = 0;
    }
    if (sai_st[0x47] != 0) {
      sai_st[0x67] = 1;
    }
  }
  if (((sai_st[0x67] == 1) && (sai_st[0x5a] == 4)) && (sai_st[0x5c] != 4)) {
    if (sai_st[0x60] == 0) {
      if (!bVar4) {
        sai_st[0x66] = 1;
      }
      sai_st[0x67] = 0;
    }
    else {
      sai_st[0x67] = 2;
    }
  }
  if ((sai_st[0x67] == 2) && (sai_st[0x60] == 0)) {
    if (sai_st[0x5a] == 4) {
      if (!bVar4) {
        sai_st[0x66] = 1;
      }
      sai_st[0x67] = 0;
    }
    else {
      sai_st[0x67] = 3;
    }
  }
  if ((sai_st[0x67] == 3) && (sai_st[0x5a] == 4)) {
    if (!bVar4) {
      sai_st[0x66] = 1;
    }
    sai_st[0x67] = 0;
  }
  puVar1[3] = puVar1[3] | uVar7 | uVar6;
  puVar1[3] = puVar1[3] | uVar8;
  if ((sai_st[0x56] == 0) && (sai_st[0x68] != 0)) {
    uVar6 = puVar1[2] & ~uVar6;
  }
  else {
    uVar6 = puVar1[2] | uVar6;
  }
  puVar1[2] = uVar6;
  if ((sai_st[0x57] == 0) && (sai_st[0x69] != 0)) {
    uVar7 = puVar1[2] & ~uVar7;
  }
  else {
    uVar7 = puVar1[2] | uVar7;
  }
  puVar1[2] = uVar7;
  if ((sai_st[0x58] == 0) && (sai_st[0x6a] != 0)) {
    uVar8 = puVar1[2] & ~uVar8;
  }
  else {
    uVar8 = puVar1[2] | uVar8;
  }
  puVar1[2] = uVar8;
  if ((bVar4) || (uVar23 == 0)) {
    sai_st[0x68] = 0;
  }
  if ((bVar4) || (uVar22 == 0)) {
    sai_st[0x69] = 0;
  }
  if ((bVar4) || (uVar19 == 0)) {
    sai_st[0x6a] = 0;
  }
  if ((((sai_st[0x6b] == 0) && (!bVar4)) && (sai_st[0x45] != 0)) &&
     ((sai_st[0x6c] == 0 && ((uVar12 & 7) != 0)))) {
    sai_st[0x6b] = 1;
  }
  if (((sai_st[0x6b] == 1) && (sai_st[0x5a] == 4)) && (sai_st[0x5c] != 4)) {
    if ((uVar9 != 0) || (sai_st[0x60] == 0)) {
      if (uVar23 != 0) {
        sai_st[0x68] = 1;
      }
      if (uVar22 != 0) {
        sai_st[0x69] = 1;
      }
      if (uVar19 != 0) {
        sai_st[0x6a] = 1;
      }
      if (sai_st[0x60] == 0) {
        sai_st[0x6b] = 0;
        goto LAB_0041205d;
      }
    }
    sai_st[0x6a] = 0;
    sai_st[0x69] = 0;
    sai_st[0x68] = 0;
    sai_st[0x6b] = 3;
  }
LAB_0041205d:
  if ((sai_st[0x6b] == 3) && (sai_st[0x60] == 0)) {
    if (sai_st[0x5a] == 4) {
      if (uVar23 != 0) {
        sai_st[0x68] = 1;
      }
      if (uVar22 != 0) {
        sai_st[0x69] = 1;
      }
      if (uVar19 != 0) {
        sai_st[0x6a] = 1;
      }
      sai_st[0x6b] = 0;
    }
    else {
      sai_st[0x6b] = 4;
    }
  }
  if ((sai_st[0x6b] == 4) && (sai_st[0x5a] == 4)) {
    if (uVar23 != 0) {
      sai_st[0x68] = 1;
    }
    if (uVar22 != 0) {
      sai_st[0x69] = 1;
    }
    if (uVar19 != 0) {
      sai_st[0x6a] = 1;
    }
    sai_st[0x6b] = 0;
  }
  sai_st[0x5c] = sai_st[0x5a];
  sai_st[0x37] = sai_st[0x36];
  sai_st[0x39] = sai_st[0x38];
  sai_st[0x5b] = sai_st[0x41];
  sai_st[0x35] = sai_st[0x55];
  sai_st[0x6c] = sai_st[0x45];
  local_7c = local_7c & 0x800;
  if ((local_7c == 0) || ((sai_st[1] & 0xc000) != 0xc000)) {
    uVar12 = 0;
  }
  else {
    uVar12 = 1;
  }
  sai_st[9] = uVar12;
  if ((local_7c == 0) || ((sai_st[1] & 0xc000) != 0x4000)) {
    uVar12 = 0;
  }
  else {
    uVar12 = 1;
  }
  sai_st[0xb] = uVar12;
  if ((local_7c == 0) || ((sai_st[1] & 0xc000) != 0x8000)) {
    uVar12 = 0;
  }
  else {
    uVar12 = 1;
  }
  sai_st[0xd] = uVar12;
  local_74 = local_74 & 0x800;
  if ((local_74 == 0) || ((sai_st[4] & 0xc000) != 0xc000)) {
    uVar12 = 0;
  }
  else {
    uVar12 = 1;
  }
  sai_st[10] = uVar12;
  if ((local_74 == 0) || ((sai_st[4] & 0xc000) != 0x4000)) {
    uVar12 = 0;
  }
  else {
    uVar12 = 1;
  }
  sai_st[0xc] = uVar12;
  if ((local_74 != 0) && ((sai_st[4] & 0xc000) == 0x8000)) {
    sai_st[0xe] = 1;
    return;
  }
  sai_st[0xe] = 0;
  return;
}


/* ==== sai_rx_decode_terms @ 004122e0 ==== */

void sai_rx_decode_terms(void)

{
  *(undefined4 *)(sai_st + 0xfc) = 0;
  *(undefined4 *)(sai_st + 0xf8) = 0;
  *(undefined4 *)(sai_st + 0xf4) = 0;
  *(undefined4 *)(sai_st + 0xf0) = 0;
  if ((*(byte *)(sai_st + 0x100) & 0x10) != 0) {
    *(uint *)(sai_st + 0xf4) = *(uint *)(sai_st + 0xf4) | 1;
  }
  if ((*(byte *)(sai_st + 0x100) & 8) != 0) {
    *(uint *)(sai_st + 0xf4) = *(uint *)(sai_st + 0xf4) | 2;
  }
  if ((*(byte *)(sai_st + 0x100) & 4) != 0) {
    *(uint *)(sai_st + 0xf4) = *(uint *)(sai_st + 0xf4) | 4;
  }
  if ((*(byte *)(sai_st + 0x100) & 2) != 0) {
    *(uint *)(sai_st + 0xf4) = *(uint *)(sai_st + 0xf4) | 8;
  }
  if ((*(byte *)(sai_st + 0x100) & 1) != 0) {
    *(uint *)(sai_st + 0xf4) = *(uint *)(sai_st + 0xf4) | 0x10;
  }
  if ((*(byte *)(sai_st + 0x10) & 0x20) != 0) {
    *(uint *)(sai_st + 0xf4) = *(uint *)(sai_st + 0xf4) | 0x20;
  }
  if ((*(byte *)(sai_st + 0x10) & 0x10) != 0) {
    *(uint *)(sai_st + 0xf4) = *(uint *)(sai_st + 0xf4) | 0x40;
  }
  if ((*(byte *)(sai_st + 0x10) & 8) != 0) {
    *(uint *)(sai_st + 0xf4) = *(uint *)(sai_st + 0xf4) | 0x80;
  }
  if (*(int *)(sai_st + 0x140) != 0) {
    *(uint *)(sai_st + 0xf4) = *(uint *)(sai_st + 0xf4) | 0x100;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x9f) == 0x80) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 1;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x1f) == 0x10) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 2;
  }
  if ((*(byte *)(sai_st + 0xf4) & 0x9f) == 0) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 4;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x3f) == 0x18) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 8;
  }
  if ((*(uint *)(sai_st + 0xf4) & 0x17f) == 0x38) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x10;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x3f) == 8) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x20;
  }
  if ((*(uint *)(sai_st + 0xf4) & 0x17f) == 0x28) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x40;
  }
  if ((*(uint *)(sai_st + 0xf4) & 0x17f) == 0x138) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x80;
  }
  if ((*(uint *)(sai_st + 0xf4) & 0x13f) == 0x128) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x100;
  }
  if ((*(uint *)(sai_st + 0xf4) & 0x19f) == 0x1c) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x200;
  }
  if ((*(uint *)(sai_st + 0xf4) & 0x19f) == 0x9c) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x400;
  }
  if ((*(uint *)(sai_st + 0xf4) & 0x11f) == 0x11c) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x800;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0xbf) == 0x89) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x1000;
  }
  if ((*(uint *)(sai_st + 0xf4) & 0x1ff) == 0x1a9) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x2000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0xbf) == 9) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x4000;
  }
  if ((*(uint *)(sai_st + 0xf4) & 0x1ff) == 0x129) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x8000;
  }
  if ((*(uint *)(sai_st + 0xf4) & 0x17f) == 0x29) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x10000;
  }
  if (*(char *)(sai_st + 0xf4) == -0x72) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x20000;
  }
  if (*(char *)(sai_st + 0xf4) == '\x0e') {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x40000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x1f) == 4) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x80000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x1f) == 0x14) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x100000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x1f) == 0xc) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x200000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x1f) == 2) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x400000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x1f) == 0x12) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x800000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x1f) == 10) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x1000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x1f) == 0x1a) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x2000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x1f) == 6) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x4000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x1f) == 0x16) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x8000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x7f) == 0x2e) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x10000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x1f) == 0x1e) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x20000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x1f) == 1) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x40000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x1f) == 0x11) {
    *(uint *)(sai_st + 0xf8) = *(uint *)(sai_st + 0xf8) | 0x80000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x7f) == 0x4e) {
    *(uint *)(sai_st + 0xfc) = *(uint *)(sai_st + 0xfc) | 1;
  }
  if (((byte)*(undefined4 *)(sai_st + 0xf4) & 0x3f) == 0x10) {
    *(uint *)(sai_st + 0xfc) = *(uint *)(sai_st + 0xfc) | 2;
  }
  if ((*(uint *)(sai_st + 0xf4) & 0x17f) == 0x30) {
    *(uint *)(sai_st + 0xfc) = *(uint *)(sai_st + 0xfc) | 4;
  }
  if ((*(byte *)(sai_st + 0xf4) & 0xbf) == 0) {
    *(uint *)(sai_st + 0xfc) = *(uint *)(sai_st + 0xfc) | 8;
  }
  if ((*(uint *)(sai_st + 0xf4) & 0x1ff) == 0x20) {
    *(uint *)(sai_st + 0xfc) = *(uint *)(sai_st + 0xfc) | 0x10;
  }
  if ((*(uint *)(sai_st + 0xf4) & 0x11f) == 0x10c) {
    *(uint *)(sai_st + 0xfc) = *(uint *)(sai_st + 0xfc) | 0x20;
  }
  if ((*(uint *)(sai_st + 0xf8) & 0xe0000000) != 0) {
    *(uint *)(sai_st + 0xf0) = *(uint *)(sai_st + 0xf0) | 1;
  }
  if (((*(uint *)(sai_st + 0xf8) & 0x1fc00878) != 0) || ((*(byte *)(sai_st + 0xfc) & 1) != 0)) {
    *(uint *)(sai_st + 0xf0) = *(uint *)(sai_st + 0xf0) | 2;
  }
  if (((*(uint *)(sai_st + 0xf8) & 0x1e390180) != 0) || ((*(byte *)(sai_st + 0xfc) & 1) != 0)) {
    *(uint *)(sai_st + 0xf0) = *(uint *)(sai_st + 0xf0) | 4;
  }
  if (((*(uint *)(sai_st + 0xf8) & 0x99b6f606) != 0) || ((*(byte *)(sai_st + 0xfc) & 1) != 0)) {
    *(uint *)(sai_st + 0xf0) = *(uint *)(sai_st + 0xf0) | 8;
  }
  if (((*(uint *)(sai_st + 0xf8) & 0x556cc205) != 0) || ((*(byte *)(sai_st + 0xfc) & 1) != 0)) {
    *(uint *)(sai_st + 0xf0) = *(uint *)(sai_st + 0xf0) | 0x10;
  }
  if ((*(uint *)(sai_st + 0xf8) & 0x6f606) != 0) {
    *(uint *)(sai_st + 0xf0) = *(uint *)(sai_st + 0xf0) | 0x20;
  }
  if ((*(byte *)(sai_st + 0xf8) & 1) != 0) {
    *(uint *)(sai_st + 0xf0) = *(uint *)(sai_st + 0xf0) | 0x40;
  }
  if ((*(uint *)(sai_st + 0xf8) & 0x2349a) != 0) {
    *(uint *)(sai_st + 0xf0) = *(uint *)(sai_st + 0xf0) | 0x80;
  }
  if ((*(uint *)(sai_st + 0xf8) & 0x4c204) != 0) {
    *(uint *)(sai_st + 0xf0) = *(uint *)(sai_st + 0xf0) | 0x100;
  }
  if ((*(uint *)(sai_st + 0xf8) & 0x4c206) != 0) {
    *(uint *)(sai_st + 0xf0) = *(uint *)(sai_st + 0xf0) | 0x200;
  }
  if ((*(uint *)(sai_st + 0xf8) & 0x6f600) != 0) {
    *(uint *)(sai_st + 0xf0) = *(uint *)(sai_st + 0xf0) | 0x400;
  }
  if (((*(uint *)(sai_st + 0xf8) & 0x65600) != 0) || ((*(byte *)(sai_st + 0xfc) & 0x3e) != 0)) {
    *(uint *)(sai_st + 0xf0) = *(uint *)(sai_st + 0xf0) | 0x800;
  }
  return;
}


/* ==== sai_rx_terms_to_flags @ 00412b20 ==== */

void sai_rx_terms_to_flags(void)

{
  *(undefined4 *)(sai_st + 0x100) = 0;
  if ((*(byte *)(sai_st + 0xf0) & 1) != 0) {
    *(uint *)(sai_st + 0x100) = *(uint *)(sai_st + 0x100) | 0x10;
  }
  if ((*(byte *)(sai_st + 0xf0) & 2) != 0) {
    *(uint *)(sai_st + 0x100) = *(uint *)(sai_st + 0x100) | 8;
  }
  if ((*(byte *)(sai_st + 0xf0) & 4) != 0) {
    *(uint *)(sai_st + 0x100) = *(uint *)(sai_st + 0x100) | 4;
  }
  if ((*(byte *)(sai_st + 0xf0) & 8) != 0) {
    *(uint *)(sai_st + 0x100) = *(uint *)(sai_st + 0x100) | 2;
  }
  if ((*(byte *)(sai_st + 0xf0) & 0x10) != 0) {
    *(uint *)(sai_st + 0x100) = *(uint *)(sai_st + 0x100) | 1;
  }
  *(uint *)(sai_st + 0x104) = *(uint *)(sai_st + 0xf0) & 0x20;
  *(uint *)(sai_st + 0x108) = *(uint *)(sai_st + 0xf0) & 0x40;
  *(uint *)(sai_st + 0x10c) = *(uint *)(sai_st + 0xf0) & 0x80;
  *(uint *)(sai_st + 0x110) = *(uint *)(sai_st + 0xf0) & 0x100;
  *(uint *)(sai_st + 0x114) = *(uint *)(sai_st + 0xf0) & 0x200;
  *(uint *)(sai_st + 0x118) = *(uint *)(sai_st + 0xf0) & 0x400;
  *(uint *)(sai_st + 0x11c) = *(uint *)(sai_st + 0xf0) & 0x800;
  return;
}


/* ==== sai_tx_decode_terms @ 00412c70 ==== */

void sai_tx_decode_terms(void)

{
  *(undefined4 *)(sai_st + 0x60) = 0;
  *(undefined4 *)(sai_st + 0x5c) = 0;
  *(undefined4 *)(sai_st + 0x58) = 0;
  *(undefined4 *)(sai_st + 0x68) = 0;
  if ((*(byte *)(sai_st + 0xa4) & 0x10) != 0) {
    *(uint *)(sai_st + 0x58) = *(uint *)(sai_st + 0x58) | 1;
  }
  if ((*(byte *)(sai_st + 0xa4) & 8) != 0) {
    *(uint *)(sai_st + 0x58) = *(uint *)(sai_st + 0x58) | 2;
  }
  if ((*(byte *)(sai_st + 0xa4) & 4) != 0) {
    *(uint *)(sai_st + 0x58) = *(uint *)(sai_st + 0x58) | 4;
  }
  if ((*(byte *)(sai_st + 0xa4) & 2) != 0) {
    *(uint *)(sai_st + 0x58) = *(uint *)(sai_st + 0x58) | 8;
  }
  if ((*(byte *)(sai_st + 0xa4) & 1) != 0) {
    *(uint *)(sai_st + 0x58) = *(uint *)(sai_st + 0x58) | 0x10;
  }
  if ((*(byte *)(sai_st + 4) & 0x20) != 0) {
    *(uint *)(sai_st + 0x58) = *(uint *)(sai_st + 0x58) | 0x20;
  }
  if ((*(byte *)(sai_st + 4) & 0x10) != 0) {
    *(uint *)(sai_st + 0x58) = *(uint *)(sai_st + 0x58) | 0x40;
  }
  if ((*(byte *)(sai_st + 4) & 8) != 0) {
    *(uint *)(sai_st + 0x58) = *(uint *)(sai_st + 0x58) | 0x80;
  }
  if (*(int *)(sai_st + 100) != 0) {
    *(uint *)(sai_st + 0x58) = *(uint *)(sai_st + 0x58) | 0x100;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x9f) == 0x80) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 1;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x1f) == 0x10) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 2;
  }
  if ((*(byte *)(sai_st + 0x58) & 0x9f) == 0) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 4;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x3f) == 0x18) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 8;
  }
  if ((*(uint *)(sai_st + 0x58) & 0x17f) == 0x38) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x10;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x3f) == 8) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x20;
  }
  if ((*(uint *)(sai_st + 0x58) & 0x17f) == 0x28) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x40;
  }
  if ((*(uint *)(sai_st + 0x58) & 0x17f) == 0x138) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x80;
  }
  if ((*(uint *)(sai_st + 0x58) & 0x17f) == 0x128) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x100;
  }
  if ((*(uint *)(sai_st + 0x58) & 0x19f) == 0x1c) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x200;
  }
  if ((*(uint *)(sai_st + 0x58) & 0x19f) == 0x9c) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x400;
  }
  if ((*(uint *)(sai_st + 0x58) & 0x11f) == 0x11c) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x800;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0xbf) == 0x89) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x1000;
  }
  if ((*(uint *)(sai_st + 0x58) & 0x1ff) == 0x1a9) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x2000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0xbf) == 9) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x4000;
  }
  if ((*(uint *)(sai_st + 0x58) & 0x1ff) == 0x129) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x8000;
  }
  if ((*(uint *)(sai_st + 0x58) & 0x17f) == 0x29) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x10000;
  }
  if (*(char *)(sai_st + 0x58) == -0x72) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x20000;
  }
  if (*(char *)(sai_st + 0x58) == '\x0e') {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x40000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x1f) == 4) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x80000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x1f) == 0x14) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x100000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x1f) == 0xc) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x200000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x1f) == 2) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x400000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x1f) == 0x12) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x800000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x1f) == 10) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x1000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x1f) == 0x1a) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x2000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x1f) == 6) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x4000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x1f) == 0x16) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x8000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x7f) == 0x2e) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x10000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x1f) == 0x1e) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x20000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x1f) == 1) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x40000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x1f) == 0x11) {
    *(uint *)(sai_st + 0x5c) = *(uint *)(sai_st + 0x5c) | 0x80000000;
  }
  if (((byte)*(undefined4 *)(sai_st + 0x58) & 0x7f) == 0x4e) {
    *(undefined4 *)(sai_st + 0x60) = 1;
  }
  if ((*(byte *)(sai_st + 0x5f) & 0xe0) != 0) {
    *(uint *)(sai_st + 0x68) = *(uint *)(sai_st + 0x68) | 1;
  }
  if (((*(uint *)(sai_st + 0x5c) & 0x1fc00878) != 0) || (*(int *)(sai_st + 0x60) != 0)) {
    *(uint *)(sai_st + 0x68) = *(uint *)(sai_st + 0x68) | 2;
  }
  if (((*(uint *)(sai_st + 0x5c) & 0x1e390180) != 0) || (*(int *)(sai_st + 0x60) != 0)) {
    *(uint *)(sai_st + 0x68) = *(uint *)(sai_st + 0x68) | 4;
  }
  if (((*(uint *)(sai_st + 0x5c) & 0x99b6f606) != 0) || (*(int *)(sai_st + 0x60) != 0)) {
    *(uint *)(sai_st + 0x68) = *(uint *)(sai_st + 0x68) | 8;
  }
  if (((*(uint *)(sai_st + 0x5c) & 0x556cc205) != 0) || (*(int *)(sai_st + 0x60) != 0)) {
    *(uint *)(sai_st + 0x68) = *(uint *)(sai_st + 0x68) | 0x10;
  }
  if ((*(uint *)(sai_st + 0x5c) & 0x7f000) != 0) {
    *(uint *)(sai_st + 0x68) = *(uint *)(sai_st + 0x68) | 0x20;
  }
  if ((*(byte *)(sai_st + 0x5c) & 1) != 0) {
    *(uint *)(sai_st + 0x68) = *(uint *)(sai_st + 0x68) | 0x40;
  }
  if ((*(uint *)(sai_st + 0x5c) & 0x2349a) != 0) {
    *(uint *)(sai_st + 0x68) = *(uint *)(sai_st + 0x68) | 0x80;
  }
  if ((*(uint *)(sai_st + 0x5c) & 0x4c204) != 0) {
    *(uint *)(sai_st + 0x68) = *(uint *)(sai_st + 0x68) | 0x100;
  }
  return;
}


/* ==== sai_tx_terms_to_flags @ 004131d0 ==== */

void sai_tx_terms_to_flags(void)

{
  *(undefined4 *)(sai_st + 0xa4) = 0;
  if ((*(byte *)(sai_st + 0x68) & 1) != 0) {
    *(uint *)(sai_st + 0xa4) = *(uint *)(sai_st + 0xa4) | 0x10;
  }
  if ((*(byte *)(sai_st + 0x68) & 2) != 0) {
    *(uint *)(sai_st + 0xa4) = *(uint *)(sai_st + 0xa4) | 8;
  }
  if ((*(byte *)(sai_st + 0x68) & 4) != 0) {
    *(uint *)(sai_st + 0xa4) = *(uint *)(sai_st + 0xa4) | 4;
  }
  if ((*(byte *)(sai_st + 0x68) & 8) != 0) {
    *(uint *)(sai_st + 0xa4) = *(uint *)(sai_st + 0xa4) | 2;
  }
  if ((*(byte *)(sai_st + 0x68) & 0x10) != 0) {
    *(uint *)(sai_st + 0xa4) = *(uint *)(sai_st + 0xa4) | 1;
  }
  *(uint *)(sai_st + 0x70) = *(uint *)(sai_st + 0x68) & 0x20;
  *(uint *)(sai_st + 0x74) = *(uint *)(sai_st + 0x68) & 0x40;
  *(uint *)(sai_st + 0x78) = *(uint *)(sai_st + 0x68) & 0x80;
  *(uint *)(sai_st + 0x7c) = *(uint *)(sai_st + 0x68) & 0x100;
  return;
}


