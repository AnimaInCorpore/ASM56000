/* ==== sci_iofile_parse @ 00416190 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sci_iofile_parse(char *text,void *state)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  char *pcVar5;
  bool bVar6;
  
  pbVar4 = &DAT_004b6ebc;
  pbVar2 = (byte *)text;
  do {
    bVar1 = *pbVar2;
    bVar6 = bVar1 < *pbVar4;
    if (bVar1 != *pbVar4) {
LAB_004161cb:
      iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
      goto LAB_004161d0;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar2[1];
    bVar6 = bVar1 < pbVar4[1];
    if (bVar1 != pbVar4[1]) goto LAB_004161cb;
    pbVar2 = pbVar2 + 2;
    pbVar4 = pbVar4 + 2;
  } while (bVar1 != 0);
  iVar3 = 0;
LAB_004161d0:
  if (iVar3 == 0) {
    *(undefined4 *)((int)state + 0x19c) = 0x8000;
    *(undefined4 *)((int)state + 0x188) = 0xfffffffe;
  }
  else {
    pcVar5 = s_break_004b901c;
    pbVar2 = (byte *)text;
    do {
      bVar1 = *pbVar2;
      bVar6 = bVar1 < (byte)*pcVar5;
      if (bVar1 != *pcVar5) {
LAB_00416219:
        iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_0041621e;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar6 = bVar1 < (byte)pcVar5[1];
      if (bVar1 != pcVar5[1]) goto LAB_00416219;
      pbVar2 = pbVar2 + 2;
      pcVar5 = pcVar5 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_0041621e:
    if (iVar3 == 0) {
      *(undefined4 *)((int)state + 0x19c) = 0x8000;
      *(undefined4 *)((int)state + 0x188) = 0xfffffffd;
    }
    else {
      io_parse_value(text,state,0x40000001);
    }
  }
  *(undefined4 *)(sci_st + 0x30) = *(undefined4 *)((int)state + 0x188);
  return 1;
}


/* ==== sci_iofile_format @ 00416260 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sci_iofile_format(void *rec,int arg2,char *out)

{
  if (*(int *)arg2 == -2) {
    *(undefined4 *)out = DAT_004b6ec4;
    out[4] = DAT_004b6ec8;
    return 1;
  }
  if (*(int *)arg2 == -3) {
    *(undefined4 *)out = s_BREAK_004b9024._0_4_;
    *(undefined2 *)(out + 4) = s_BREAK_004b9024._4_2_;
    return 1;
  }
  return 0;
}


/* ==== sci_write_reg @ 004162b0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sci_write_reg(int dev,int reg,ulong *val)

{
  int iVar1;
  
  sci_status = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd6c = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  sci_regflags = *(undefined4 *)(sci_status + 4);
  _DAT_004dbd68 = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  sci_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  sci_st = *_DAT_004dbd68;
  iVar1 = *(int *)(sci_dev + 0x2c);
  if ((reg < *(int *)(iVar1 + 0x28)) &&
     ((*(byte *)(*(int *)(iVar1 + 0x2c) + 0x10 + reg * 0x1c) & 0x40) != 0)) {
    sci_write_reg_core(reg,*val & 0xffffff);
    sci_refresh_reg(reg);
    return 1;
  }
  if (reg < *(int *)(iVar1 + 0x24)) {
    *(ulong *)(sci_st + reg * 4) = *val & 0xffffff;
  }
  sci_refresh_reg(reg);
  return 1;
}


/* ==== sci_tick @ 00416380 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void sci_tick(int dev)

{
  sci_status = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd6c = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  sci_regflags = *(undefined4 *)(sci_status + 4);
  _DAT_004dbd68 = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  sci_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  sci_st = *_DAT_004dbd68;
  sci_chipflags = *(int *)(cur_dev + 0x40);
  if ((*(int *)(sci_chipflags + 0xc) == 0) && (*(int *)(sci_chipflags + 8) != 1)) {
    sci_clock(dev,1);
  }
  return;
}


/* ==== sci_write_io @ 00416410 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sci_write_io(int dev,ulong addr,ulong val)

{
  int iVar1;
  
  sci_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  switch(addr - *(int *)(sci_dev + 0x1c)) {
  case 0:
    iVar1 = 1;
    break;
  default:
    if (addr == 0xffff) {
      iVar1 = 0x2c;
    }
    else {
      iVar1 = addr - *(ulong *)(sci_dev + 0x14);
      if (addr == *(ulong *)(sci_dev + 0x14)) {
        iVar1 = 0x2a;
      }
      else if (iVar1 == 2) {
        iVar1 = 0x2b;
      }
      else {
        if (iVar1 != 4) {
          return 0;
        }
        iVar1 = 0x2e;
      }
    }
    break;
  case 2:
    iVar1 = 0;
    break;
  case 3:
    iVar1 = 5;
    break;
  case 4:
    iVar1 = 4;
    break;
  case 5:
    iVar1 = 8;
    break;
  case 6:
    iVar1 = 9;
  }
  sci_status = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd6c = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  sci_regflags = *(undefined4 *)(sci_status + 4);
  _DAT_004dbd68 = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  sci_st = *_DAT_004dbd68;
  if ((iVar1 == 0x2b) || (iVar1 == 0x2e)) {
    *(uint *)(sci_st + iVar1 * 4) = *(uint *)(sci_dev + 8) & val;
    return *(int *)(sci_st + iVar1 * 4);
  }
  if (iVar1 != 0x2a) {
    if (iVar1 == 0x2c) {
      *(uint *)(sci_st + 0xb0) = *(uint *)(sci_dev + 0x28) & val;
      return 0;
    }
    sci_write_reg_core(iVar1,val);
    return 0;
  }
  *(uint *)(sci_st + 0xa8) = *(uint *)(sci_dev + 0x18) & val;
  if (*(int *)(sci_st + 0xa8) == 0) {
    sci_reset_state();
    return *(int *)(sci_st + 0xa8);
  }
  *(undefined4 *)(sci_st + 0xb4) = 1;
  return *(int *)(sci_st + 0xa8);
}


/* ==== sci_read_io @ 004165b0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sci_read_io(int dev,ulong addr,ulong *out,int side)

{
  uint uVar1;
  int extraout_EAX;
  int iVar2;
  
  sci_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  _DAT_004dbd68 = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  sci_st = *_DAT_004dbd68;
  uVar1 = addr - *(int *)(sci_dev + 0x1c);
  switch(uVar1) {
  case 0:
    iVar2 = 1;
    break;
  case 1:
    iVar2 = 3;
    break;
  case 2:
    iVar2 = 0;
    break;
  default:
    iVar2 = addr - *(ulong *)(sci_dev + 0x14);
    if (addr == *(ulong *)(sci_dev + 0x14)) {
      uVar1 = *(uint *)(sci_st + 0xa8) & *(uint *)(sci_dev + 0x18);
      *out = uVar1;
    }
    else {
      if (iVar2 == 2) {
        uVar1 = *(uint *)(sci_st + 0xac) & *(uint *)(sci_dev + 8);
        *out = uVar1;
        return uVar1;
      }
      if (iVar2 == 4) {
        uVar1 = *(uint *)(sci_st + 0xb8) & *(uint *)(sci_dev + 8);
        *out = uVar1;
        return uVar1;
      }
    }
    return uVar1;
  case 4:
    iVar2 = 2;
    break;
  case 5:
    iVar2 = 6;
    break;
  case 6:
    iVar2 = 7;
  }
  sci_status = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd6c = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  sci_regflags = *(undefined4 *)(sci_status + 4);
  sci_read_reg_core(iVar2,out,side);
  return extraout_EAX;
}


/* ==== sci_reset @ 004166e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sci_reset(int dev)

{
  int extraout_EAX;
  int iVar1;
  int in_stack_00000008;
  
  sci_status = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd6c = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  sci_regflags = *(undefined4 *)(sci_status + 4);
  _DAT_004dbd68 = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  sci_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  sci_st = *_DAT_004dbd68;
  sci_reset_state();
  iVar1 = 0;
  if (in_stack_00000008 != 0) {
    sci_reset_regs();
    iVar1 = extraout_EAX;
  }
  return iVar1;
}


/* ==== sci_reset_regs @ 00416760 ==== */

void sci_reset_regs(void)

{
  sci_set_reg(1,0);
  *(undefined4 *)(sci_st + 0x80) = 0;
  *(undefined4 *)(sci_st + 0x70) = 0;
  *(undefined4 *)(sci_st + 0xb8) = 0;
  *(undefined4 *)(sci_st + 0xac) = 0;
  *(undefined4 *)(sci_st + 0xa8) = 0;
  *(undefined4 *)(sci_st + 0x98) = 1;
  sci_set_reg(0,0);
  *(undefined4 *)(sci_st + 0x6c) = 0;
  *(undefined4 *)(sci_st + 0x44) = 0;
  *(undefined4 *)(sci_st + 0x34) = 0;
  *(undefined4 *)(sci_st + 0x48) = 0;
  *(undefined4 *)(sci_st + 0x4c) = 0;
  return;
}


/* ==== sci_set_reg @ 004167f0 ==== */

void __cdecl sci_set_reg(int reg,ulong val)

{
  *(ulong *)(sci_st + reg * 4) = val;
  sci_refresh_reg(reg);
  return;
}


/* ==== sci_int_pending @ 00416810 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long sci_int_pending(int dev)

{
  int iVar1;
  
  _DAT_004dbd68 = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  sci_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  sci_st = *_DAT_004dbd68;
  if (*(int *)(sci_st + 0xb0) != 0) {
    iVar1 = *(int *)(sci_dev + 0x20);
    if (*(int *)(sci_st + 0x5c) != 0) {
      return iVar1 + 2;
    }
    if (*(int *)(sci_st + 0x60) != 0) {
      return iVar1;
    }
    if (*(int *)(sci_st + 100) != 0) {
      return iVar1 + 4;
    }
    if (*(int *)(sci_st + 0x68) != 0) {
      return iVar1 + 6;
    }
    if (*(int *)(sci_st + 0x6c) != 0) {
      return iVar1 + 8;
    }
  }
  return -1;
}


/* ==== sci_int_ack @ 00416890 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sci_int_ack(int dev,long vec)

{
  int iVar1;
  
  _DAT_004dbd68 = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  sci_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  sci_st = *_DAT_004dbd68;
  iVar1 = vec - *(int *)(sci_dev + 0x20);
  if (vec == *(int *)(sci_dev + 0x20)) {
    *(undefined4 *)(sci_st + 0x60) = 0;
    return 0x18;
  }
  if (iVar1 == 2) {
    *(undefined4 *)(sci_st + 0x5c) = 0;
    return 0x17;
  }
  if (iVar1 == 4) {
    *(undefined4 *)(sci_st + 100) = 0;
    return 0x19;
  }
  iVar1 = (iVar1 != 6) + 0x1a;
  *(undefined4 *)(sci_st + iVar1 * 4) = 0;
  return iVar1;
}


/* ==== sci_write_reg_core @ 00416920 ==== */

void __cdecl sci_write_reg_core(int reg,ulong val)

{
  uint uVar1;
  
  switch(reg) {
  default:
    goto switchD_00416936_caseD_0;
  case 1:
    if ((val & 0x400) == 0) {
      *(undefined4 *)(sci_st + 0x68) = 0;
    }
    else if (((*(uint *)(sci_st + 4) & 0x400) == 0) && ((*(byte *)(sci_st + 0xc) & 8) != 0)) {
      *(undefined4 *)(sci_st + 0x68) = 1;
    }
    if (((val & 0x10) != 0) && ((*(byte *)(sci_st + 4) & 0x10) == 0)) {
      *(undefined4 *)(sci_st + 0x9c) = 1;
    }
    goto switchD_00416936_caseD_0;
  case 5:
    *(uint *)(sci_regflags + 0x10) = *(uint *)(sci_regflags + 0x10) | 0xa0000;
    *(ulong *)(sci_st + 0x10) = val;
    *(undefined4 *)(sci_st + 0x78) = 1;
    uVar1 = *(uint *)(sci_st + 0xc);
    break;
  case 9:
    val = val >> 8;
  case 8:
    val = val >> 8;
    reg = 4;
  case 4:
    uVar1 = *(uint *)(sci_st + 0xc);
  }
  sci_set_reg(3,uVar1 & 0xfffffffc);
switchD_00416936_caseD_0:
  *(uint *)(sci_st + reg * 4) =
       *(uint *)(*(int *)(*(int *)(sci_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c) & val;
  if (*(int *)(sci_st + 0xa8) == 0) {
    sci_reset_state();
  }
  *(uint *)(sci_regflags + reg * 4) = *(uint *)(sci_regflags + reg * 4) | 0xa0000;
  if ((*(uint *)(sci_regflags + reg * 4) & 0x1800000) != 0) {
    io_out_periph_write((sci_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
  }
  return;
}


/* ==== sci_refresh_reg @ 00416a90 ==== */

void __cdecl sci_refresh_reg(int reg)

{
  int iVar1;
  
  if (reg < *(int *)(*(int *)(sci_dev + 0x2c) + 0x28)) {
    *(uint *)(sci_regflags + reg * 4) = *(uint *)(sci_regflags + reg * 4) | 0xa0000;
    *(uint *)(sci_st + reg * 4) =
         *(uint *)(sci_st + reg * 4) &
         *(uint *)(*(int *)(*(int *)(sci_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c);
    iVar1 = reg * 0x1c + *(int *)(*(int *)(sci_dev + 0x2c) + 0x2c);
    if ((*(byte *)(iVar1 + 0x10) & 0x60) != 0) {
      mem_trace_fetch(*(int *)(sci_dev + 0x1c) + *(int *)(iVar1 + 8));
    }
    if ((*(uint *)(sci_regflags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write((sci_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
    }
  }
  return;
}


/* ==== sci_read_reg_core @ 00416b50 ==== */

void __cdecl sci_read_reg_core(int reg,ulong *out,int side)

{
  sbyte sVar1;
  char cVar2;
  
  cVar2 = '\0';
  sVar1 = 0;
  *out = *(ulong *)(sci_st + reg * 4);
  switch(reg) {
  case 3:
    *out = *(uint *)(sci_st + 0xc) & 0xff;
    if (side == 1) {
      *(undefined4 *)(sci_st + 0x7c) = 1;
    }
    if (*(int *)(sci_st + 0xa8) == 0) {
      sci_reset_state();
      return;
    }
    break;
  case 5:
    *out = 0;
    return;
  case 7:
    cVar2 = '\b';
  case 6:
    sVar1 = cVar2 + 8;
  case 2:
    *out = *(int *)(sci_st + 8) << sVar1;
    if ((side == 1) &&
       (sci_set_reg(3,*(uint *)(sci_st + 0xc) & 0xfffffffb), *(int *)(sci_st + 0x7c) == 1)) {
      *(uint *)(sci_st + 0xc) = *(uint *)(sci_st + 0xc) & 0xffffff8f;
      *(undefined4 *)(sci_st + 0x7c) = 0;
    }
    if (*(int *)(sci_st + 0xa8) == 0) {
      sci_reset_state();
    }
  }
  return;
}


/* ==== sci_reset_state @ 00416c50 ==== */

void sci_reset_state(void)

{
  sci_set_reg(3,3);
  *(uint *)(sci_st + 100) = *(uint *)(sci_st + 4) >> 0xc & 1;
  *(undefined4 *)(sci_st + 0x5c) = 0;
  *(undefined4 *)(sci_st + 0x60) = 0;
  *(undefined4 *)(sci_st + 0x68) = 0;
  *(undefined4 *)(sci_st + 0xa0) = 1;
  *(undefined4 *)(sci_st + 0x98) = 0;
  *(undefined4 *)(sci_st + 0x9c) = 0;
  *(undefined4 *)(sci_st + 0x50) = 0;
  *(undefined4 *)(sci_st + 0xbc) = 0;
  *(undefined4 *)(sci_st + 0x2c) = 0xfffffffe;
  *sci_status = 0x26;
  *(undefined4 *)(sci_st + 0x38) = 0;
  *(undefined4 *)(sci_st + 0x3c) = 0;
  *(undefined4 *)(sci_st + 0x40) = 0;
  *(undefined4 *)(sci_st + 0xc0) = 0xfffffffe;
  *(undefined4 *)(sci_st + 0x94) = 1;
  return;
}


/* ==== sci_clock @ 00416d20 ==== */

void __cdecl sci_clock(int dev,int feed_input)

{
  uint *puVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  bool bVar13;
  ulong local_68;
  uint local_64;
  ulong local_60;
  uint local_5c;
  int local_58;
  uint local_54;
  uint local_50;
  ulong local_4c;
  uint local_48;
  int local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  ulong local_28 [2];
  ulong local_20;
  
  uVar7 = 1;
  local_4c = 1;
  uVar6 = sci_st[1];
  if (((uVar6 & 0x1000) == 0) || ((sci_st[3] & 2) == 0)) {
    uVar7 = 0;
  }
  sci_st[0x19] = uVar7;
  local_30 = uVar6 & 0x400;
  if (local_30 == 0) {
    sci_st[0x1a] = 0;
  }
  local_2c = uVar6 & 0x800;
  if (local_2c == 0) {
    sci_st[0x18] = 0;
    sci_st[0x17] = 0;
  }
  uVar7 = uVar6 & 0x2000;
  if (uVar7 == 0) {
    sci_st[0x1b] = 0;
  }
  local_48 = sci_st[0x2a];
  if ((local_48 == 0) && (uVar7 == 0)) {
    return;
  }
  local_54 = *sci_st;
  local_44 = 0;
  bVar3 = false;
  local_5c = 0;
  local_40 = 0;
  local_50 = 0;
  if ((feed_input != 0) && (*(int *)(sci_chipflags + 4) != 0)) {
    if (sci_st[0x11] == 0) {
      sci_st[0x11] = local_54 & 0xfff;
      sci_st[0x12] = sci_st[0x12] + 1;
      if (((local_54 & 0x2000) == 0) || (sci_st[0x12] == 8)) {
        sci_st[0x12] = 0;
        sci_st[0x13] = sci_st[0x13] + 1;
        if ((3 < *(uint *)(cur_dtype + 8)) && ((uVar7 != 0 && ((uVar6 & 0x4000) != 0)))) {
          sci_st[0x1b] = 1;
        }
        if ((sci_st[0x13] & 1) == 0) {
          local_44 = 1;
        }
        else {
          bVar3 = true;
          sci_st[0xd] = sci_st[0xd] + 1 & 0xffffff;
          local_5c = sci_st[0xd];
          if ((uVar7 != 0) && ((local_5c & 0xf) == 0)) {
            sci_st[0x1b] = 1;
          }
        }
      }
    }
    else {
      sci_st[0x11] = sci_st[0x11] - 1 & 0xfff;
    }
  }
  if (local_48 == 0) {
    return;
  }
  uVar7 = *(uint *)(sci_dev + 8);
  uVar7 = uVar7 & (uVar7 - 1 ^ uVar7);
  uVar9 = uVar7 * 2;
  local_64 = uVar7 * 4;
  uVar10 = uVar7 << (-((*(uint *)(cur_dtype + 8) & 0x880) != 0) & 7U) + 2;
  sci_pins = (uint *)(*(int *)(cur_dev + 0x18) + 0x94 + *(int *)(sci_dev + 4) * 0x128);
  puVar1 = (uint *)(*(int *)(cur_dev + 0x18) + *(int *)(sci_dev + 4) * 0x128);
  local_34 = uVar9 & local_48;
  local_48 = local_64 & local_48;
  sci_pins2 = sci_pins;
  if (((sci_st[0x2d] != 0) && (sci_st[0x2d] = 0, local_48 != 0)) &&
     (uVar8 = puVar1[2], (uVar8 & uVar10) == 0)) {
    if ((sci_st[1] & 0x8000) == 0) {
      uVar8 = uVar10 | uVar8;
    }
    else {
      uVar8 = ~uVar10 & uVar8;
    }
    puVar1[2] = uVar8;
  }
  local_3c = local_54 & 0x8000;
  if (local_3c == 0) {
    bVar13 = false;
    local_58 = 0;
  }
  else {
    uVar8 = uVar10 & *puVar1;
    uVar11 = uVar10 & *sci_pins;
    if ((uVar6 & 0x8000) != 0) {
      uVar11 = (uint)(uVar11 == 0);
      uVar8 = (uint)(uVar8 == 0);
    }
    if (((uVar8 == 0) || (uVar11 != 0)) ||
       (((puVar1[1] & uVar10) == 0 || (bVar13 = true, (sci_pins[1] & uVar10) == 0)))) {
      bVar13 = false;
    }
    if (((uVar8 != 0) || (uVar11 == 0)) ||
       (((puVar1[1] & uVar10) == 0 || (local_58 = 1, (sci_pins[1] & uVar10) == 0)))) {
      local_58 = 0;
    }
    if (bVar13) {
      sci_st[0x2f] = sci_st[0x2f] + 1;
      local_40 = sci_st[0x2f];
    }
  }
  local_38 = local_54 & 0x4000;
  if (local_38 == 0) {
    bVar4 = false;
  }
  else {
    uVar8 = local_64 & *puVar1;
    uVar11 = local_64 & *sci_pins2;
    if ((uVar6 & 0x8000) != 0) {
      uVar11 = (uint)(uVar11 == 0);
      uVar8 = (uint)(uVar8 == 0);
    }
    if ((((uVar8 == 0) || (uVar11 != 0)) || ((puVar1[1] & local_64) == 0)) ||
       ((sci_pins2[1] & local_64) == 0)) {
      bVar4 = false;
    }
    else {
      bVar4 = true;
    }
    if (bVar4) {
      sci_st[0x14] = sci_st[0x14] + 1;
      local_50 = sci_st[0x14];
    }
  }
  bVar2 = false;
  uVar8 = uVar6 & 7;
  if ((uVar6 & 0x200) == 0) {
    sci_st[0x26] = 1;
  }
  else {
    if (sci_st[0x20] == 0) {
      sci_st[0xf] = 0;
      sci_set_reg(3,sci_st[3] | 3);
      sci_st[0x28] = 1;
      sci_st[0x26] = 1;
      sci_st[0x20] = 1;
      if (local_34 != 0) {
        puVar1[2] = puVar1[2] | uVar9;
        puVar1[3] = puVar1[3] | uVar9;
      }
      sci_st[0x30] = 0xfffffffe;
    }
    if (sci_st[0x25] != 0) {
      if (local_34 != 0) {
        puVar1[2] = puVar1[2] | uVar9;
        puVar1[3] = puVar1[3] | uVar9;
      }
      sci_st[0x30] = 0xfffffffe;
    }
  }
  if (((uVar8 == 0) && (local_3c != 0)) && ((local_58 != 0 && ((sci_st[3] & 2) != 0)))) {
    iVar12 = 1;
  }
  else {
    iVar12 = 0;
  }
  if (sci_st[0x20] != 0) {
    if (sci_st[0x28] != 0) {
      if ((((uVar6 & 0x10) != 0) && (uVar8 != 0)) && (sci_st[0x16] == 0xfffffffd)) {
        sci_st[0x27] = 1;
      }
      iVar5 = sci_tx_abort_if_disabled();
      if (iVar5 == 0) {
        sci_tx_frame_done(iVar12,dev);
      }
    }
    if (sci_st[0x20] != 0) {
      if (local_3c == 0) {
        if (uVar8 < 2) {
          if ((bVar3) && ((sci_st[0xd] & 1) == 0)) {
            uVar11 = sci_st[0x28];
            goto joined_r0x00417284;
          }
        }
        else if ((bVar3) && ((sci_st[0xd] & 0xf) == 0)) {
LAB_00417286:
          bVar2 = true;
        }
      }
      else if (uVar8 < 2) {
        if (local_58 != 0) {
          uVar11 = sci_st[0x28];
          goto joined_r0x00417284;
        }
      }
      else if (bVar13) {
        uVar11 = local_40 & 0xf;
joined_r0x00417284:
        if (uVar11 == 0) goto LAB_00417286;
      }
    }
  }
  if ((bVar2) && (sci_st[0x28] == 0)) {
    if ((sci_st[sci_st[0xf] + 0x30] == 0xfffffffe) &&
       ((iVar5 = sci_tx_abort_if_disabled(), iVar5 == 0 &&
        (iVar12 = sci_tx_frame_done(iVar12,dev), iVar12 == 0)))) {
      puVar1[2] = puVar1[2] | uVar9;
      sci_st[0x28] = 1;
    }
    else {
      if (sci_st[sci_st[0xf] + 0x30] == 0) {
        uVar9 = puVar1[2] & ~uVar9;
      }
      else {
        uVar9 = puVar1[2] | uVar9;
      }
      puVar1[2] = uVar9;
      sci_st[0xf] = sci_st[0xf] + 1;
    }
  }
  uVar9 = uVar10 | local_64;
  if ((local_48 != 0) && ((bVar3 || (local_44 != 0)))) {
    if ((local_54 & 0xc000) == 0) {
      if (uVar8 == 0) {
        if (local_44 != 0) {
          puVar1[3] = puVar1[3] | uVar9;
          if (sci_st[0x28] != 0) goto LAB_00417419;
          if (sci_st[0xf] != 0) {
            uVar11 = puVar1[2];
            if ((uVar11 & uVar10) == 0) {
              if ((uVar6 & 0x8000) != 0) goto LAB_00417464;
              puVar1[2] = uVar9 | uVar11;
            }
            else if ((uVar6 & 0x8000) == 0) {
LAB_00417464:
              puVar1[2] = ~uVar9 & uVar11;
            }
            else {
              puVar1[2] = uVar9 | uVar11;
            }
          }
        }
      }
      else {
        puVar1[3] = puVar1[3] | uVar9;
        if ((local_54 & 0x1000) == 0) {
          if ((sci_st[0xd] & 0xf) == 0) {
            if ((uVar6 & 0x8000) == 0) {
LAB_004173cc:
              puVar1[2] = puVar1[2] & ~uVar9;
            }
            else {
              puVar1[2] = puVar1[2] | uVar9;
            }
          }
          else if ((sci_st[0xd] & 7) == 0) {
            if ((uVar6 & 0x8000) != 0) goto LAB_004173cc;
            puVar1[2] = puVar1[2] | uVar9;
          }
        }
        else {
          if (bVar3) {
LAB_00417419:
            if ((uVar6 & 0x8000) == 0) {
              puVar1[2] = puVar1[2] | uVar9;
              goto LAB_00417491;
            }
          }
          else if ((uVar6 & 0x8000) != 0) {
            puVar1[2] = puVar1[2] | uVar9;
            goto LAB_00417491;
          }
          puVar1[2] = puVar1[2] & ~uVar9;
        }
      }
    }
    else {
      puVar1[3] = puVar1[3] & ~uVar9;
    }
  }
LAB_00417491:
  local_48 = uVar6 & 0x100;
  if ((local_48 != 0) && (sci_st[0x1c] == 0)) {
    sci_st[0xb] = 0xfffffffe;
    if (local_38 == 0) {
      uVar9 = sci_st[0xd];
    }
    else {
      uVar9 = sci_st[0x14];
    }
    sci_st[0x10] = uVar9;
    sci_st[0xe] = 0;
    sci_st[0x1c] = 1;
    *sci_status = 0x27;
  }
  if (sci_st[0x25] != 0) {
    sci_st[0xb] = 0xfffffffe;
    if (local_38 == 0) {
      uVar9 = sci_st[0xd];
    }
    else {
      uVar9 = sci_st[0x14];
    }
    sci_st[0x10] = uVar9;
    sci_st[0xe] = 0;
    *sci_status = 0x26;
    sci_st[0x25] = 0;
  }
  if (sci_st[0x1c] == 0) goto LAB_00417a6b;
  *sci_status = *sci_status | 1;
  bVar13 = false;
  if (local_38 == 0) {
    if (bVar3) {
      if (1 < uVar8) {
        if ((sci_st[0xb] == 0xfffffffd) && (((*sci_status & 0x10) != 0 || ((*puVar1 & uVar7) != 0)))
           ) {
          sci_st[0xb] = 0xfffffffe;
        }
        if ((sci_st[0xb] == 0xfffffffe) &&
           (((*sci_status & 0x10) != 0 || (((*puVar1 & uVar7) == 0 && ((puVar1[1] & uVar7) != 0)))))
           ) {
          sci_st[0xe] = 0;
          sci_st[0x10] = local_5c;
          sci_st[0xb] = 0;
          *sci_status = *sci_status & 0xffffffef;
        }
        uVar9 = local_5c;
        if ((uint)(*(int *)(&sci_mode_bits_tab + uVar8 * 4) << 4) <= local_5c - sci_st[0x10]) {
          *sci_status = *sci_status & 0xfffffff7;
        }
        goto LAB_004176f7;
      }
      if ((local_5c & 1) != 0) {
        if (sci_st[0xb] != 0xfffffffe) goto LAB_0041774c;
        if ((sci_st[0x28] == 0) && (sci_st[0xf] != 0)) {
          sci_st[0xb] = 0;
          sci_st[0xe] = 0;
          *sci_status = *sci_status & 0xffffffef;
          bVar13 = true;
        }
      }
    }
  }
  else if (bVar4) {
    if (uVar8 < 2) {
      if (sci_st[0xb] == 0xfffffffe) {
        sci_st[0xe] = 0;
        sci_st[0xb] = 0;
        *sci_status = *sci_status & 0xffffffef;
        bVar13 = true;
      }
      else {
LAB_0041774c:
        bVar13 = true;
      }
    }
    else {
      if ((sci_st[0xb] == 0xfffffffd) && (((*sci_status & 0x10) != 0 || ((*puVar1 & uVar7) != 0))))
      {
        sci_st[0xb] = 0xfffffffe;
      }
      if ((sci_st[0xb] == 0xfffffffe) &&
         (((*sci_status & 0x10) != 0 || (((*puVar1 & uVar7) == 0 && ((puVar1[1] & uVar7) != 0))))))
      {
        sci_st[0xe] = 0;
        sci_st[0x10] = local_50;
        sci_st[0xb] = 0;
        *sci_status = *sci_status & 0xffffffef;
      }
      uVar9 = local_50;
      if ((uint)(*(int *)(&sci_mode_bits_tab + uVar8 * 4) << 4) <= local_50 - sci_st[0x10]) {
        *sci_status = *sci_status & 0xfffffff7;
      }
LAB_004176f7:
      bVar13 = ((char)uVar9 - (char)sci_st[0x10] & 0xfU) == 8;
    }
  }
  if (bVar13) {
    uVar9 = sci_st[0xb];
    if (((uVar9 != 0xfffffffe) && (uVar9 != 0xfffffffd)) && ((*sci_status & 8) == 0)) {
      sci_st[0xb] = uVar9 * 2;
      if ((uVar7 & *puVar1) == 0) {
        if ((sci_st[3] & 8) != 0) {
          sci_set_reg(3,sci_st[3] & 0xfffffff7);
        }
      }
      else {
        sci_st[0xb] = sci_st[0xb] | 1;
      }
    }
    if ((sci_st[0xb] == 0xfffffffd) && ((sci_st[3] & 8) != 0)) {
      sci_set_reg(3,sci_st[3] & 0xfffffff7);
    }
    sci_st[0xe] = sci_st[0xe] + 1;
    if (*(int *)(&sci_mode_bits_tab + uVar8 * 4) <= (int)sci_st[0xe]) {
      if ((*sci_status & 8) == 0) {
        iVar12 = io_in_pin_read(dev,local_28);
        if (iVar12 != 0) goto LAB_00417843;
      }
      else {
        if (uVar8 == 0) {
          *sci_status = *sci_status & 0xfffffff7;
        }
        local_20 = sci_st[0xc];
LAB_00417843:
        sci_encode_frame(local_20,sci_st + 0xb);
      }
      if (sci_st[0xb] == 0xfffffffe) {
        bVar3 = true;
        if (((sci_st[3] & 8) == 0) && (sci_set_reg(3,sci_st[3] | 8), local_30 != 0)) {
          sci_st[0x1a] = 1;
        }
      }
      else {
        if ((sci_st[3] & 8) != 0) {
          sci_set_reg(3,sci_st[3] & 0xfffffff7);
        }
        bVar3 = false;
        if (sci_st[0xb] == 0xfffffffd) {
          local_4c = 0;
          local_60 = 0;
          local_68 = 0;
        }
        else {
          sci_decode_frame(&local_68,&local_60,&local_4c);
        }
      }
      if (((uVar6 & 0x40) == 0) || (uVar8 == 0)) {
LAB_00417900:
        bVar13 = true;
      }
      else {
        bVar13 = bVar3;
        if ((uVar6 & 0x20) != 0) {
          if (uVar8 == 6) {
            if (!bVar3) {
              if (local_60 != 0) goto LAB_00417900;
              bVar13 = false;
              goto LAB_00417905;
            }
          }
          else if ((!bVar3) && ((local_68 & 0x80) != 0)) goto LAB_00417900;
          bVar13 = false;
        }
      }
LAB_00417905:
      if (bVar13) {
        if ((uVar6 & 0x40) != 0) {
          sci_set_reg(1,sci_st[1] & 0xffffffbf);
        }
        if (!bVar3) {
          uVar6 = sci_st[3];
          if ((uVar6 & 4) == 0) {
            if ((uVar6 & 0x40) == 0) {
              sci_set_reg(2,local_68);
              sci_set_reg(3,sci_st[3] | 4);
              iVar12 = 0;
              for (; 0 < (int)local_68; local_68 = (int)local_68 / 2) {
                if ((local_68 & 1) != 0) {
                  iVar12 = iVar12 + 1;
                }
              }
              uVar6 = iVar12 + local_60 & 1;
              if (((uVar8 == 4) && (uVar6 != 0)) || ((uVar8 == 5 && (uVar6 == 0)))) {
                sci_st[3] = sci_st[3] | 0x20;
              }
              if ((uVar8 == 6) && (local_60 != 0)) {
                uVar6 = sci_st[3] | 0x80;
              }
              else {
                uVar6 = sci_st[3] & 0xffffff7f;
              }
              sci_st[3] = uVar6;
              if ((uVar8 != 0) && (local_4c == 0)) {
                sci_st[3] = sci_st[3] | 0x40;
                sci_st[0xb] = 0xfffffffd;
              }
            }
          }
          else {
            sci_set_reg(3,uVar6 | 0x10);
            sci_st[3] = sci_st[3] & 0xffffff9f;
          }
        }
      }
      sci_st[0xe] = 0;
      if (sci_st[0xb] != 0xfffffffe) {
        if ((sci_st[0xb] == 0) && (uVar8 != 0)) {
          sci_st[0xb] = 0xfffffffd;
        }
        if (sci_st[0xb] != 0xfffffffd) {
          sci_st[0xb] = 0xfffffffe;
        }
      }
    }
  }
  if ((local_48 == 0) && ((sci_st[0xb] == 0xfffffffe || (sci_st[0xb] == 0xfffffffd)))) {
    sci_st[0x1c] = 0;
    *sci_status = *sci_status & 0xfffffffe;
  }
LAB_00417a6b:
  if ((local_2c != 0) && ((sci_st[3] & 4) != 0)) {
    if ((sci_st[3] & 0x70) != 0) {
      sci_st[0x17] = 1;
      return;
    }
    sci_st[0x18] = 1;
    return;
  }
  sci_st[0x18] = 0;
  sci_st[0x17] = 0;
  return;
}


/* ==== sci_tx_abort_if_disabled @ 00417ad0 ==== */

int sci_tx_abort_if_disabled(void)

{
  if ((*(uint *)(sci_st + 4) & 0x200) == 0) {
    *(undefined4 *)(sci_st + 0x80) = 0;
    *(undefined4 *)(sci_st + 0xa0) = 1;
    sci_set_reg(3,*(uint *)(sci_st + 0xc) & 0xfffffffc);
    return 1;
  }
  return 0;
}


/* ==== sci_tx_frame_done @ 00417b20 ==== */

int __cdecl sci_tx_frame_done(int rx_idle,int dev)

{
  uint uVar1;
  bool bVar2;
  uint uVar3;
  
  uVar3 = *(uint *)(sci_st + 4) & 7;
  bVar2 = false;
  if (((*(int *)(sci_st + 0x98) == 0) || ((*(uint *)(sci_st + 4) & 0x200) == 0)) || (uVar3 == 0)) {
    if ((*(int *)(sci_st + 0x9c) == 0) || (uVar3 == 0)) {
      uVar1 = *(uint *)(sci_st + 0xc);
      if (((uVar1 & 2) != 0) && (rx_idle == 0)) {
        if ((uVar1 & 1) == 0) {
          sci_set_reg(3,uVar1 | 1);
        }
        *(undefined4 *)(sci_st + 0x58) = 0xfffffffe;
        goto LAB_00417cad;
      }
      *(uint *)(sci_st + 0x84) = (uint)(*(int *)(sci_st + 0x58) == -3);
      if (rx_idle == 0) {
        *(uint *)(sci_st + 0x58) = *(uint *)(sci_st + 0x10) & 0xff;
      }
      if (uVar3 == 4) {
        *(undefined4 *)(sci_st + 0x90) = 2;
      }
      else if (uVar3 == 5) {
        *(undefined4 *)(sci_st + 0x90) = 3;
      }
      else if (uVar3 == 6) {
        if (*(int *)(sci_st + 0x78) == 0) {
          *(undefined4 *)(sci_st + 0x90) = 0;
        }
        else {
          *(undefined4 *)(sci_st + 0x78) = 0;
          *(undefined4 *)(sci_st + 0x90) = 1;
          *(uint *)(sci_st + 0x58) = *(uint *)(sci_st + 0x58) | 0x100;
        }
      }
      else {
        *(undefined4 *)(sci_st + 0x90) = 4;
      }
      bVar2 = true;
      if (rx_idle != 0) goto LAB_00417cad;
      *(uint *)(sci_st + 0xc) = *(uint *)(sci_st + 0xc) & 0xfffffffe;
      uVar3 = *(uint *)(sci_st + 0xc) | 2;
    }
    else {
      *(undefined4 *)(sci_st + 0x58) = 0xfffffffd;
      bVar2 = true;
      *(undefined4 *)(sci_st + 0x9c) = 0;
      if ((*(uint *)(sci_st + 0xc) & 1) == 0) goto LAB_00417cad;
      uVar3 = *(uint *)(sci_st + 0xc) & 0xfffffffe;
    }
  }
  else {
    *(undefined4 *)(sci_st + 0x58) = 0xfffffffe;
    bVar2 = true;
    *(undefined4 *)(sci_st + 0x98) = 0;
    if ((*(uint *)(sci_st + 0xc) & 1) == 0) goto LAB_00417cad;
    uVar3 = *(uint *)(sci_st + 0xc) & 0xfffffffe;
  }
  bVar2 = true;
  sci_set_reg(3,uVar3);
LAB_00417cad:
  if (bVar2) {
    sci_build_frame_bits();
    *(undefined4 *)(sci_st + 0xa0) = 0;
    *(undefined4 *)(sci_st + 0x3c) = 0;
    io_out_pin_write(dev,(ulong *)(sci_st + 0x58),0);
    return 1;
  }
  return 0;
}


/* ==== sci_build_frame_bits @ 00417d00 ==== */

void sci_build_frame_bits(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  bool bVar10;
  
  uVar8 = *(uint *)(sci_st + 0x58);
  uVar6 = *(uint *)(sci_st + 4) & 7;
  if (uVar8 == 0xfffffffe) {
    iVar1 = 0;
    if (0 < *(int *)(&sci_mode_nbits_tab + uVar6 * 4)) {
      iVar2 = 0xc0;
      do {
        *(undefined4 *)(sci_st + iVar2) = 1;
        iVar1 = iVar1 + 1;
        iVar2 = iVar2 + 4;
      } while (iVar1 < *(int *)(&sci_mode_nbits_tab + uVar6 * 4));
      *(undefined4 *)(sci_st + 0xc0 + iVar1 * 4) = 0xfffffffe;
      return;
    }
    goto LAB_00417eac;
  }
  if (uVar8 == 0xfffffffd) {
    iVar1 = 0;
    if (0 < *(int *)(&sci_mode_nbits_tab + uVar6 * 4)) {
      iVar2 = 0xc0;
      do {
        *(undefined4 *)(sci_st + iVar2) = 0;
        iVar1 = iVar1 + 1;
        iVar2 = iVar2 + 4;
      } while (iVar1 < *(int *)(&sci_mode_nbits_tab + uVar6 * 4));
      *(undefined4 *)(sci_st + 0xc0 + iVar1 * 4) = 0xfffffffe;
      return;
    }
    goto LAB_00417eac;
  }
  iVar2 = 0;
  if (uVar6 != 0) {
    bVar10 = *(int *)(sci_st + 0x84) != 0;
    if (bVar10) {
      *(undefined4 *)(sci_st + 0xc0) = 1;
    }
    uVar9 = (uint)bVar10;
    *(undefined4 *)(sci_st + 0xc0 + uVar9 * 4) = 0;
    iVar2 = uVar9 + 1;
  }
  uVar9 = uVar8 & 0xff;
  if ((*(byte *)(sci_st + 4) & 8) != 0) {
    uVar7 = 1;
    uVar3 = 0x80;
    uVar9 = 0;
    do {
      if ((uVar3 & uVar8 & 0xff) != 0) {
        uVar9 = uVar9 | uVar7;
      }
      uVar3 = (int)uVar3 >> 1;
      uVar7 = uVar7 << 1;
    } while (uVar3 != 0);
  }
  iVar5 = 8;
  uVar3 = 0;
  iVar4 = iVar2 * 4 + 0xc0;
  uVar8 = 1;
  iVar1 = iVar2 + 8;
  do {
    *(uint *)(sci_st + iVar4) = (uint)((uVar9 & uVar8) != 0);
    if (*(int *)(sci_st + iVar4) != 0) {
      uVar3 = uVar3 + 1;
    }
    uVar8 = uVar8 << 1;
    iVar4 = iVar4 + 4;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  switch(*(undefined4 *)(sci_st + 0x90)) {
  case 0:
    *(undefined4 *)(sci_st + 0xc0 + iVar1 * 4) = 0;
    break;
  case 1:
    *(undefined4 *)(sci_st + 0xc0 + iVar1 * 4) = 1;
    break;
  case 3:
    uVar3 = ~uVar3;
  case 2:
    *(uint *)(sci_st + 0xc0 + iVar1 * 4) = uVar3 & 1;
    break;
  default:
    goto switchD_00417e5d_default;
  }
  iVar1 = iVar2 + 9;
switchD_00417e5d_default:
  if (1 < uVar6) {
    *(undefined4 *)(sci_st + 0xc0 + iVar1 * 4) = 1;
    iVar1 = iVar1 + 1;
  }
LAB_00417eac:
  *(undefined4 *)(sci_st + 0xc0 + iVar1 * 4) = 0xfffffffe;
  return;
}


/* ==== sci_decode_frame @ 00417ed0 ==== */

void __cdecl sci_decode_frame(ulong *data,ulong *parity,ulong *stop)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  uVar1 = *(uint *)(sci_st + 0x2c);
  *stop = uVar1 & 1;
  *parity = uVar1 >> 1 & 1;
  uVar3 = *(uint *)(sci_st + 4) & 7;
  if (uVar3 != 0) {
    uVar1 = (int)uVar1 >> 1;
  }
  if (2 < uVar3) {
    uVar1 = (int)uVar1 >> 1;
  }
  uVar3 = 0;
  iVar4 = 8;
  do {
    uVar3 = uVar3 << 1;
    if ((uVar1 & 1) != 0) {
      uVar3 = uVar3 | 1;
    }
    uVar1 = (int)uVar1 >> 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  uVar1 = uVar3;
  if ((*(uint *)(sci_st + 4) & 8) != 0) {
    uVar5 = 1;
    uVar2 = 0x80;
    uVar1 = 0;
    do {
      if ((uVar3 & uVar2) != 0) {
        uVar1 = uVar1 | uVar5;
      }
      uVar2 = (int)uVar2 >> 1;
      uVar5 = uVar5 << 1;
    } while (uVar2 != 0);
  }
  *data = uVar1;
  return;
}


/* ==== sci_encode_frame @ 00417f50 ==== */

void __cdecl sci_encode_frame(ulong word,ulong *frame)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  ulong uVar6;
  
  uVar4 = *(uint *)(sci_st + 4) & 7;
  if ((word != 0xfffffffd) && (word != 0xfffffffe)) {
    if ((uVar4 == 0) || (*(int *)(sci_st + 0x2c) != -3)) {
      iVar2 = 0;
    }
    else {
      iVar2 = 1;
    }
    uVar3 = iVar2 << 1;
    uVar6 = word;
    if ((*(uint *)(sci_st + 4) & 8) != 0) {
      uVar5 = 1;
      uVar1 = 0x80;
      uVar6 = 0;
      do {
        if ((word & uVar1) != 0) {
          uVar6 = uVar6 | uVar5;
        }
        uVar1 = (int)uVar1 >> 1;
        uVar5 = uVar5 << 1;
      } while (uVar1 != 0);
    }
    uVar1 = 0;
    iVar2 = 8;
    do {
      uVar3 = uVar3 * 2 | uVar6 & 1;
      if ((uVar6 & 1) != 0) {
        uVar1 = uVar1 + 1;
      }
      uVar6 = (int)uVar6 >> 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if (uVar4 == 4) {
      uVar3 = uVar3 * 2 | uVar1 & 1;
    }
    else if (uVar4 == 5) {
      uVar3 = uVar3 * 2 | (uint)((uVar1 & 1) == 0);
    }
    else if (uVar4 == 6) {
      uVar3 = uVar6 & 1 | uVar3 * 2;
    }
    if (uVar4 != 0) {
      uVar3 = uVar3 * 2 | 1;
    }
    *frame = uVar3;
    return;
  }
  *frame = word;
  return;
}


