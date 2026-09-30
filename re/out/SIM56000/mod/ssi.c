/* ==== iofmt_idle_parse @ 00418010 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int iofmt_idle_parse(char *text,void *state)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  bool bVar4;
  
  pbVar3 = &DAT_004b6ebc;
  do {
    bVar1 = *text;
    bVar4 = bVar1 < *pbVar3;
    if (bVar1 != *pbVar3) {
LAB_00418048:
      iVar2 = (1 - (uint)bVar4) - (uint)(bVar4 != 0);
      goto LAB_0041804d;
    }
    if (bVar1 == 0) break;
    bVar1 = text[1];
    bVar4 = bVar1 < pbVar3[1];
    if (bVar1 != pbVar3[1]) goto LAB_00418048;
    text = text + 2;
    pbVar3 = pbVar3 + 2;
  } while (bVar1 != 0);
  iVar2 = 0;
LAB_0041804d:
  if (iVar2 == 0) {
    *(undefined4 *)((int)state + 0x19c) = 0x8000;
    *(undefined4 *)((int)state + 0x188) = 0xfffffffe;
    return 1;
  }
  return 0;
}


/* ==== ssi_write_reg @ 00418080 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int ssi_write_reg(int dev,int reg,ulong *val)

{
  int iVar1;
  
  ssi_status = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd90 = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  ssi_regflags = *(undefined4 *)(ssi_status + 4);
  _DAT_004dbd8c = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  ssi_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  ssi_st = *_DAT_004dbd8c;
  iVar1 = *(int *)(ssi_dev + 0x2c);
  if ((reg < *(int *)(iVar1 + 0x28)) &&
     ((*(byte *)(*(int *)(iVar1 + 0x2c) + 0x10 + reg * 0x1c) & 0x40) != 0)) {
    ssi_write_reg_core(reg,*val);
    ssi_refresh_reg(reg);
    return 1;
  }
  if (reg < *(int *)(iVar1 + 0x24)) {
    *(ulong *)(ssi_st + reg * 4) = *val;
  }
  ssi_refresh_reg(reg);
  return 1;
}


/* ==== ssi_tick @ 00418150 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ssi_tick(int dev)

{
  ssi_status = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd90 = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  ssi_regflags = *(undefined4 *)(ssi_status + 4);
  _DAT_004dbd8c = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  ssi_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  ssi_st = *_DAT_004dbd8c;
  DAT_004dbd7c = *(int *)(cur_dev + 0x40);
  if ((*(int *)(DAT_004dbd7c + 0xc) == 0) && (*(int *)(DAT_004dbd7c + 8) != 1)) {
    ssi_clock(dev,1);
  }
  return;
}


/* ==== ssi_write_io @ 004181e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int ssi_write_io(int dev,ulong addr,ulong val)

{
  int iVar1;
  
  ssi_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  switch(addr - *(int *)(ssi_dev + 0x1c)) {
  case 0:
    iVar1 = 0;
    break;
  case 1:
    iVar1 = 1;
    break;
  case 2:
    iVar1 = 4;
    break;
  case 3:
    iVar1 = 5;
    break;
  default:
    if (addr == 0xffff) {
      iVar1 = 0x4d;
    }
    else {
      iVar1 = addr - *(ulong *)(ssi_dev + 0x14);
      if (addr == *(ulong *)(ssi_dev + 0x14)) {
        iVar1 = 0x10;
      }
      else if (iVar1 == 2) {
        iVar1 = 0x42;
      }
      else {
        if (iVar1 != 4) {
          return 0;
        }
        iVar1 = 0x33;
      }
    }
  }
  ssi_status = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd90 = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  ssi_regflags = *(undefined4 *)(ssi_status + 4);
  _DAT_004dbd8c = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  ssi_st = *_DAT_004dbd8c;
  if ((iVar1 == 0x42) || (iVar1 == 0x33)) {
    *(uint *)(ssi_st + iVar1 * 4) = *(uint *)(ssi_dev + 8) & val;
    return *(int *)(ssi_st + iVar1 * 4);
  }
  if (iVar1 == 0x10) {
    *(uint *)(ssi_st + 0x40) = *(uint *)(ssi_dev + 0x18) & val;
    if (*(int *)(ssi_st + 0x40) == 0) {
      ssi_reset_state();
    }
    return *(int *)(ssi_st + 0x40);
  }
  if (iVar1 != 0x4d) {
    ssi_write_reg_core(iVar1,val);
    return 0;
  }
  *(uint *)(ssi_st + 0x134) = *(uint *)(ssi_dev + 0x28) & val;
  return 0;
}


/* ==== ssi_read_io @ 00418340 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int ssi_read_io(int dev,ulong addr,ulong *out,int side)

{
  int iVar1;
  int extraout_EAX;
  uint uVar2;
  int iVar3;
  
  _DAT_004dbd8c = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  iVar1 = dev * 0x48;
  ssi_dev = *(int *)(cur_dtype + 0x18) + iVar1;
  ssi_st = *_DAT_004dbd8c;
  switch(addr - *(int *)(*(int *)(cur_dtype + 0x18) + 0x1c + iVar1)) {
  case 0:
    iVar1 = 0;
    break;
  case 1:
    iVar1 = 1;
    break;
  case 2:
    iVar1 = 3;
    break;
  case 3:
    iVar1 = 2;
    break;
  default:
    iVar3 = addr - *(ulong *)(ssi_dev + 0x14);
    if (addr == *(ulong *)(ssi_dev + 0x14)) {
      uVar2 = *(uint *)(ssi_dev + 0x18);
      *out = *(uint *)(ssi_st + 0x40) & uVar2;
      return uVar2;
    }
    if (iVar3 == 2) {
      iVar1 = 0x42;
    }
    else {
      if (iVar3 != 4) {
        return iVar1;
      }
      iVar1 = 0x33;
    }
    uVar2 = *(uint *)(ssi_st + iVar1 * 4) & *(uint *)(ssi_dev + 8);
    *out = uVar2;
    return uVar2;
  }
  ssi_status = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd90 = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  ssi_regflags = *(undefined4 *)(ssi_status + 4);
  ssi_read_reg_core(iVar1,out,side);
  return extraout_EAX;
}


/* ==== ssi_reset @ 00418460 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int ssi_reset(int dev)

{
  int extraout_EAX;
  int iVar1;
  int in_stack_00000008;
  
  ssi_status = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd90 = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  ssi_regflags = *(undefined4 *)(ssi_status + 4);
  _DAT_004dbd8c = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  ssi_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  ssi_st = *_DAT_004dbd8c;
  ssi_reset_state();
  iVar1 = 0;
  if (in_stack_00000008 != 0) {
    ssi_reset_regs();
    iVar1 = extraout_EAX;
  }
  return iVar1;
}


/* ==== ssi_reset_regs @ 004184e0 ==== */

void ssi_reset_regs(void)

{
  ssi_set_reg(1,0);
  ssi_set_reg(0,0);
  *(undefined4 *)(ssi_st + 0x144) = 0;
  *(undefined4 *)(ssi_st + 0x140) = 0;
  *(undefined4 *)(ssi_st + 0x13c) = 0;
  *(undefined4 *)(ssi_st + 0x138) = 0;
  *(undefined4 *)(ssi_st + 0x40) = 0;
  *(undefined4 *)(ssi_st + 0xcc) = 0;
  *(undefined4 *)(ssi_st + 0x108) = 0;
  *(undefined4 *)(ssi_st + 0xc0) = 0;
  *(undefined4 *)(ssi_st + 0xe4) = 0;
  *(undefined4 *)(ssi_st + 0xbc) = 0;
  return;
}


/* ==== ssi_set_reg @ 00418570 ==== */

void __cdecl ssi_set_reg(int reg,ulong val)

{
  *(ulong *)(ssi_st + reg * 4) = val;
  ssi_refresh_reg(reg);
  return;
}


/* ==== ssi_int_pending @ 00418590 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long ssi_int_pending(int dev)

{
  int iVar1;
  
  _DAT_004dbd8c = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  ssi_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  ssi_st = *_DAT_004dbd8c;
  if (*(int *)(ssi_st + 0x134) != 0) {
    iVar1 = *(int *)(ssi_dev + 0x20);
    if (*(int *)(ssi_st + 0x138) != 0) {
      return iVar1 + 2;
    }
    if (*(int *)(ssi_st + 0x13c) != 0) {
      return iVar1;
    }
    if (*(int *)(ssi_st + 0x140) != 0) {
      return iVar1 + 6;
    }
    if (*(int *)(ssi_st + 0x144) != 0) {
      return iVar1 + 4;
    }
  }
  return -1;
}


/* ==== ssi_int_ack @ 00418610 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int ssi_int_ack(int dev,long vec)

{
  int iVar1;
  
  _DAT_004dbd8c = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  ssi_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  ssi_st = *_DAT_004dbd8c;
  iVar1 = vec - *(int *)(ssi_dev + 0x20);
  if (vec == *(int *)(ssi_dev + 0x20)) {
    *(undefined4 *)(ssi_st + 0x13c) = 0;
    return 0x4f;
  }
  if (iVar1 == 2) {
    *(undefined4 *)(ssi_st + 0x138) = 0;
    return 0x4e;
  }
  iVar1 = (iVar1 == 4) + 0x50;
  *(undefined4 *)(ssi_st + iVar1 * 4) = 0;
  return iVar1;
}


/* ==== ssi_write_reg_core @ 00418690 ==== */

void __cdecl ssi_write_reg_core(int reg,ulong val)

{
  *(uint *)(ssi_st + reg * 4) =
       *(uint *)(*(int *)(*(int *)(ssi_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c) & val;
  *(uint *)(ssi_regflags + reg * 4) = *(uint *)(ssi_regflags + reg * 4) | 0xa0000;
  if (reg == 1) {
    if (*(int *)(ssi_st + 0x40) == 0) {
      ssi_reset_state();
    }
    if ((val & 0x2000) == 0) {
      *(undefined4 *)(ssi_st + 0x84) = 0;
    }
    if ((val & 0x1000) == 0) {
      *(undefined4 *)(ssi_st + 0x100) = 0;
    }
  }
  else {
    if (reg == 4) {
      *(undefined4 *)(ssi_st + 0xdc) = 1;
    }
    else if (reg != 5) goto LAB_00418778;
    if (*(int *)(ssi_st + 0x54) == 1) {
      *(undefined4 *)(ssi_st + 0x54) = 0;
      *(uint *)(ssi_st + 0xc) = *(uint *)(ssi_st + 0xc) & 0xffffffef;
    }
    ssi_set_reg(3,*(uint *)(ssi_st + 0xc) & 0xffffffbf);
    if (*(int *)(ssi_st + 0x40) == 0) {
      ssi_reset_state();
    }
  }
LAB_00418778:
  if ((*(uint *)(ssi_regflags + reg * 4) & 0x1800000) != 0) {
    io_out_periph_write((ssi_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
  }
  return;
}


/* ==== ssi_refresh_reg @ 004187c0 ==== */

void __cdecl ssi_refresh_reg(int reg)

{
  int iVar1;
  
  if (reg < *(int *)(*(int *)(ssi_dev + 0x2c) + 0x28)) {
    *(uint *)(ssi_regflags + reg * 4) = *(uint *)(ssi_regflags + reg * 4) | 0xa0000;
    *(uint *)(ssi_st + reg * 4) =
         *(uint *)(ssi_st + reg * 4) &
         *(uint *)(*(int *)(*(int *)(ssi_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c);
    iVar1 = reg * 0x1c + *(int *)(*(int *)(ssi_dev + 0x2c) + 0x2c);
    if ((*(byte *)(iVar1 + 0x10) & 0x60) != 0) {
      mem_trace_fetch(*(int *)(ssi_dev + 0x1c) + *(int *)(iVar1 + 8));
    }
    if ((*(uint *)(ssi_regflags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write((ssi_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
    }
  }
  return;
}


/* ==== ssi_read_reg_core @ 00418880 ==== */

void __cdecl ssi_read_reg_core(int reg,ulong *out,int side)

{
  *out = *(ulong *)(ssi_st + reg * 4);
  if (reg == 2) {
    if ((side != 0) && (*(int *)(ssi_st + 0x40) != 0)) {
      if (*(int *)(ssi_st + 0x50) != 0) {
        *(uint *)(ssi_st + 0xc) = *(uint *)(ssi_st + 0xc) & 0xffffffdf;
        *(undefined4 *)(ssi_st + 0x50) = 0;
      }
      *(uint *)(ssi_st + 0xc) = *(uint *)(ssi_st + 0xc) & 0xffffff7f;
    }
  }
  else if (((reg == 3) && (side != 0)) && (*(int *)(ssi_st + 0x40) != 0)) {
    if ((*(byte *)(ssi_st + 0xc) & 0x20) != 0) {
      *(undefined4 *)(ssi_st + 0x50) = 1;
    }
    if ((*(byte *)(ssi_st + 0xc) & 0x10) != 0) {
      *(undefined4 *)(ssi_st + 0x54) = 1;
      return;
    }
  }
  return;
}


/* ==== ssi_reset_state @ 00418910 ==== */

void ssi_reset_state(void)

{
  ssi_set_reg(3,0x40);
  *(undefined4 *)(ssi_st + 0x38) = 0xfffffffe;
  *(undefined4 *)(ssi_st + 0x34) = 0xfffffffe;
  *(undefined4 *)(ssi_st + 0x98) = 1;
  *(undefined4 *)(ssi_st + 0x114) = 1;
  *(undefined4 *)(ssi_st + 0xd0) = 3;
  *(undefined4 *)(ssi_st + 0xe0) = 3;
  *(undefined4 *)(ssi_st + 0x24) = 0;
  *(undefined4 *)(ssi_st + 0xa4) = 0;
  *(undefined4 *)(ssi_st + 0xc4) = 0;
  *(undefined4 *)(ssi_st + 0xd4) = 0;
  *(undefined4 *)(ssi_st + 0x118) = 0;
  *(undefined4 *)(ssi_st + 0xdc) = 0;
  *(undefined4 *)(ssi_st + 0x110) = 0;
  *(undefined4 *)(ssi_st + 0xb4) = 0;
  *(undefined4 *)(ssi_st + 0x58) = 0;
  *(undefined4 *)(ssi_st + 0xac) = 0;
  *(undefined4 *)(ssi_st + 0xa8) = 0;
  *(undefined4 *)(ssi_st + 0xb0) = 0;
  *(undefined4 *)(ssi_st + 0x120) = 0;
  *(undefined4 *)(ssi_st + 0x5c) = 0;
  *(undefined4 *)(ssi_st + 0x128) = 0;
  *(undefined4 *)(ssi_st + 0x124) = 0;
  *(undefined4 *)(ssi_st + 300) = 0;
  *(undefined4 *)(ssi_st + 0x94) = 0;
  *(undefined4 *)(ssi_st + 0x10c) = 0;
  *(undefined4 *)(ssi_st + 0xa0) = 0;
  *(undefined4 *)(ssi_st + 0x84) = 0;
  *(undefined4 *)(ssi_st + 0x88) = 0;
  *(undefined4 *)(ssi_st + 0x100) = 0;
  *(undefined4 *)(ssi_st + 0x104) = 0;
  *(undefined4 *)(ssi_st + 0x9c) = 1;
  *(undefined4 *)(ssi_st + 0x11c) = 1;
  *(undefined4 *)(ssi_st + 0xb8) = 1;
  *(undefined4 *)(ssi_st + 0x130) = 1;
  *(undefined4 *)(ssi_st + 0x8c) = 1;
  *(uint *)(ssi_st + 0x14c) = ~*(uint *)(ssi_st + 4) >> 10 & 1;
  *(undefined4 *)(ssi_st + 0x148) = *(undefined4 *)(ssi_st + 0x14c);
  *(undefined4 *)(ssi_st + 0x138) = 0;
  *(undefined4 *)(ssi_st + 0x140) = 0;
  *(undefined4 *)(ssi_st + 200) = 0x14;
  *(undefined4 *)(ssi_st + 0xd8) = 0x14;
  return;
}


/* ==== ssi_clock @ 00418b20 ==== */

void __cdecl ssi_clock(int dev,int feed_input)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  bool bVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  char cVar16;
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
  uint uVar27;
  uint uVar28;
  uint local_a0;
  int local_90;
  uint local_64;
  uint local_4c;
  uint local_48;
  uint local_38;
  ulong local_28 [2];
  uint local_20;
  
  uVar25 = 0;
  uVar17 = *ssi_st;
  ssi_st[0x30] = ssi_st[0x30] | 2;
  if ((feed_input != 0) && (*(int *)(DAT_004dbd7c + 4) != 0)) {
    if (ssi_st[0x2f] == 0) {
      ssi_st[0x2f] = -(uint)((uVar17 & 0x8000) != 0) & 7;
      if (ssi_st[0x39] == 0) {
        ssi_st[0x39] = uVar17 & 0xff;
        ssi_st[0x30] = ~ssi_st[0x30] & 1;
      }
      else {
        ssi_st[0x39] = ssi_st[0x39] - 1;
      }
    }
    else {
      ssi_st[0x2f] = ssi_st[0x2f] - 1;
    }
  }
  uVar2 = ssi_st[0x10];
  uVar3 = ssi_st[1];
  local_a0 = ssi_st[3];
  if (uVar2 == 0) {
    if ((((ssi_st[0x4d] == 0) || ((uVar3 & 0x4000) == 0)) || ((local_a0 & 0x40) == 0)) ||
       ((local_a0 & 0x10) != 0)) {
      uVar17 = 0;
    }
    else {
      uVar17 = 1;
    }
    ssi_st[0x51] = uVar17;
    if (((ssi_st[0x4d] == 0) || ((uVar3 & 0x8000) == 0)) ||
       (((local_a0 & 0x80) == 0 || ((local_a0 & 0x20) != 0)))) {
      uVar17 = 0;
    }
    else {
      uVar17 = 1;
    }
    ssi_st[0x4f] = uVar17;
    *ssi_status = *ssi_status & 0xfffffffe;
    return;
  }
  uVar27 = uVar3 & 0x800;
  uVar26 = uVar3 & 0x100;
  local_64 = 0;
  *ssi_status = *ssi_status | 1;
  uVar9 = uVar3 & 0x400;
  uVar18 = 0;
  uVar10 = uVar3 & 0x200;
  local_4c = 0;
  local_38 = 0;
  local_48 = uVar26;
  if ((uVar3 & 0x80) != 0) {
    local_48 = (uint)(uVar26 == 0);
  }
  uVar11 = uVar3 & 4;
  uVar12 = uVar3 & 8;
  uVar19 = uVar3 & 0x20;
  uVar13 = uVar17 >> 8 & 0x1f;
  if (uVar9 == 0) {
    if ((uVar3 & 0x10) == 0) {
      local_90 = (uVar27 != 0) + 3;
    }
    else {
      if (uVar27 != 0) {
        uVar14 = -(uint)(uVar13 != 0) & 0xfffffffb;
        goto LAB_00418d23;
      }
      local_90 = 1;
    }
  }
  else if (uVar19 == 0) {
    local_90 = 5;
  }
  else if (uVar27 == 0) {
    local_90 = 0x3d;
  }
  else {
    uVar14 = -(uint)(uVar13 != 0) & 0x37;
LAB_00418d23:
    local_90 = uVar14 + 7;
  }
  uVar28 = *(uint *)(ssi_dev + 8);
  uVar28 = uVar28 & (uVar28 - 1 ^ uVar28);
  uVar6 = uVar28 * 2;
  uVar14 = uVar28 * 4;
  uVar20 = uVar28 << 5;
  uVar21 = uVar28 * 8 & uVar2;
  uVar22 = uVar6 & uVar2;
  uVar23 = uVar2 & uVar28;
  puVar1 = (uint *)(*(int *)(cur_dev + 0x18) + *(int *)(ssi_dev + 4) * 0x128);
  uVar4 = ssi_st[0x30];
  uVar24 = uVar4 & 1;
  if ((uVar2 & uVar28 << 4) != 0) {
    local_38 = uVar28 << 4 & *puVar1;
  }
  if (uVar23 != 0) {
    local_4c = uVar28 & *puVar1;
  }
  if (uVar22 != 0) {
    local_64 = uVar6 & *puVar1;
  }
  if ((uVar14 & uVar2) != 0) {
    uVar18 = uVar14 & *puVar1;
  }
  if (uVar21 != 0) {
    uVar25 = uVar28 * 8 & *puVar1;
  }
  uVar5 = ssi_st[0x45];
  if (uVar5 == 1) {
    if (uVar24 != 0) {
      ssi_st[0x45] = 2;
    }
  }
  else if (uVar5 == 2) {
    if (uVar4 == 1) {
      ssi_st[0x45] = 3;
    }
  }
  else if (uVar5 == 3) {
    ssi_st[0x45] = 0;
  }
  if ((uVar19 != 0) || (ssi_st[0x45] != 0)) {
    uVar25 = uVar24;
  }
  if (ssi_st[0x4c] != 0) goto LAB_00419503;
  if ((uVar25 == 0) || (ssi_st[0x35] != 0)) {
    bVar7 = false;
  }
  else {
    bVar7 = true;
  }
  if ((uVar25 == 0) && (ssi_st[0x35] != 0)) {
    bVar8 = true;
  }
  else {
    bVar8 = false;
  }
  ssi_st[0x35] = uVar25;
  ssi_st[0x36] = ssi_st[0x36] | 0x10;
  if ((bVar7) && (ssi_st[0x36] = (-(uint)(ssi_st[0x43] != 0) & 0xfffffffe) + 2, local_48 != 0)) {
    ssi_st[0x17] = ssi_st[9];
  }
  if ((local_90 == 3) || (local_90 == 4)) {
    ssi_st[0x49] = uVar18;
    if ((ssi_st[0x49] != 0) && ((local_48 == 0 && (ssi_st[0x4b] == 0)))) {
      ssi_st[0x17] = 1;
      ssi_st[0x48] = 1;
      ssi_st[0x4b] = ssi_st[0x49];
    }
    if (bVar8) {
      if (((local_48 != 0) && (ssi_st[0x49] != 0)) && (ssi_st[0x4b] == 0)) {
        ssi_st[9] = 1;
        ssi_st[0x48] = 1;
      }
      ssi_st[0x4b] = ssi_st[0x49];
    }
    else if (ssi_st[0x36] == 0) {
      ssi_st[9] = 0;
      ssi_st[0x17] = 0;
    }
  }
  if (bVar8) {
    ssi_st[0x36] = (-(uint)((ssi_st[0x36] & 2) != 0) & 3) + 1;
    if (ssi_st[0x43] == 0) {
      if ((((ssi_st[0x38] != 0) || ((local_90 != 3 && (local_90 != 4)))) || (ssi_st[0x17] != 0)) ||
         (ssi_st[0x47] == 0)) {
        ssi_st[0x43] = 1;
      }
    }
    else {
      ssi_st[0x43] = 0;
    }
  }
  if (((((ssi_st[0x48] == 0) || (ssi_st[0x38] != 0)) || ((local_90 != 3 && (ssi_st[0x47] == 0)))) ||
      ((ssi_st[0x44] != 0 || (ssi_st[0x41] == 0)))) ||
     (((ssi_st[0x36] & 2) == 0 && (ssi_st[0x36] != 4)))) {
    uVar18 = 0;
  }
  else {
    uVar18 = 1;
  }
  ssi_st[0x48] = uVar18;
  if (ssi_st[0x36] != 0) goto switchD_0041909d_default;
  switch(ssi_st[0x38]) {
  case 0:
    ssi_st[0x38] = 2;
    goto switchD_0041909d_default;
  case 1:
    if (local_90 == 5) {
      uVar18 = 3;
    }
    else {
LAB_004190d6:
      uVar18 = (local_90 != 7) - 1 & 4;
    }
    break;
  case 2:
    uVar18 = (ssi_st[0x3d] != 0) + 1;
    break;
  case 3:
    if (local_90 != 5) goto LAB_004190d6;
    uVar18 = 2;
    break;
  case 4:
    if ((ssi_st[0x3f] == 0) && (ssi_st[0x41] != 0)) {
      uVar18 = 0;
    }
    else {
      uVar18 = 4;
    }
    break;
  default:
    goto switchD_0041909d_default;
  }
  ssi_st[0x38] = uVar18;
switchD_0041909d_default:
  if (ssi_st[0x38] == 0) {
    if (((ssi_st[0x36] == 0) && (local_48 != 0)) && (ssi_st[0x47] != 0)) {
      ssi_st[0x4a] = 1;
    }
    else if (ssi_st[0x36] == 2) {
      if (ssi_st[0x47] == 0) {
        ssi_st[0x4a] = 0;
      }
      else {
        ssi_st[0x4a] = (uint)(local_48 == 0);
      }
    }
  }
  else if (ssi_st[0x38] == 4) {
    ssi_st[0x4a] = 0;
  }
  if ((local_90 != 3) && (local_90 != 4)) {
    ssi_st[0x49] = ssi_st[0x4a];
    if ((ssi_st[0x49] != 0) && ((local_48 == 0 && (ssi_st[0x4b] == 0)))) {
      ssi_st[0x17] = 1;
      ssi_st[0x4b] = ssi_st[0x49];
    }
    if (bVar8) {
      if (((local_48 != 0) && (ssi_st[0x49] != 0)) && (ssi_st[0x4b] == 0)) {
        ssi_st[9] = 1;
      }
      ssi_st[0x4b] = ssi_st[0x49];
    }
    else if (ssi_st[0x36] == 0) {
      ssi_st[9] = 0;
      ssi_st[0x17] = 0;
    }
  }
  uVar18 = ssi_st[0x36];
  if ((((uVar18 == 1) && ((ssi_st[0x38] == 0 || (ssi_st[0x38] == 4)))) ||
      ((uVar18 == 2 && ((ssi_st[0x38] == 3 && (local_90 == 5)))))) ||
     (((uVar18 == 4 && (ssi_st[0x38] == 0)) &&
      ((((local_90 == 3 || (local_90 == 4)) && (ssi_st[0x17] == 0)) && (ssi_st[0x47] != 0)))))) {
    ssi_st[0x3f] = local_a0 & 0x40;
    if (ssi_st[0x47] != 0) {
      ssi_st[0x40] = uVar3 & 0x1000;
    }
    ssi_st[0x41] = ssi_st[0x40];
    ssi_st[0x3e] = uVar17 >> 0xd & 3;
    ssi_st[0x3b] = uVar13;
    ssi_st[0xb] = ssi_st[5];
    ssi_st[0x44] = ssi_st[0x37];
    ssi_st[0x1a] = uVar3 & 1;
    ssi_st[0x1b] = uVar3 & 2;
  }
  if (ssi_st[0x36] == 2) {
    if ((ssi_st[0x38] == 0) || ((ssi_st[0x38] == 3 && (local_90 == 5)))) {
      ssi_st[0x3c] = ssi_st[0x3e];
      ssi_st[0x3d] = *(uint *)(&DAT_004b9360 + ssi_st[0x3e] * 4);
    }
    if ((ssi_st[0x38] == 0) && (ssi_st[0x47] != 0)) {
      ssi_st[0x3a] = ssi_st[0x3b] + 1;
    }
  }
  else if (ssi_st[0x36] == 4) {
    if (ssi_st[0x38] == 2) {
      ssi_st[0x3d] = ssi_st[0x3d] - 1;
    }
    else if (ssi_st[0x38] == 1) {
      ssi_st[0x3a] = ssi_st[0x3a] - 1;
      if (((ssi_st[0x3a] == 0) || (local_90 == 7)) || (local_90 == 5)) {
        ssi_st[0x47] = 1;
      }
      else {
        ssi_st[0x47] = 0;
      }
    }
  }
  if ((ssi_st[0x36] == 1) && (uVar9 != 0)) {
    if (ssi_st[0x38] == 0) {
      if (ssi_st[0x47] == 0) {
        if (local_90 == 0x3d) goto LAB_004193af;
      }
      else {
        ssi_st[0x52] = 1;
      }
    }
    else if (ssi_st[0x38] == 4) {
LAB_004193af:
      ssi_st[0x52] = 0;
    }
  }
  if (ssi_st[0x36] == 2) {
    uVar18 = ssi_st[0x38];
    if (uVar18 == 0) {
      if (((ssi_st[0x41] == 0) || (ssi_st[0x44] != 0)) ||
         (((local_90 == 1 || ((local_90 == 3 || (local_90 == 0x3d)))) && (ssi_st[0x47] == 0)))) {
        ssi_st[0x46] = 0;
      }
      if ((ssi_st[0x44] == 0) && (ssi_st[0x41] != 0)) {
        if (ssi_st[0x47] == 0) {
          if (uVar27 != 0) goto LAB_00419490;
        }
        else if ((local_90 == 3) || (local_90 == 4)) {
          ssi_st[0x46] = (uint)(ssi_st[0x17] != 0);
        }
        else {
LAB_00419490:
          ssi_st[0x46] = 1;
        }
      }
      ssi_st[0xc] = -(uint)(ssi_st[0x46] != 0) & 0x800000;
    }
    else if (uVar18 == 3) {
      if (((local_90 == 5) && (ssi_st[0x41] != 0)) && (ssi_st[0x44] == 0)) {
        ssi_st[0x46] = 1;
        ssi_st[0xc] = 0x800000;
      }
      else {
        ssi_st[0xc] = 0;
      }
    }
    else if (uVar18 == 4) {
      ssi_st[0x46] = 0;
      ssi_st[0xc] = 0;
    }
  }
  if (ssi_st[0x48] != 0) {
    ssi_st[0x46] = 1;
    ssi_st[0xc] = 0x800000;
  }
  if ((ssi_st[0x36] == 1) && (ssi_st[0x38] == 3)) {
    ssi_st[0x46] = 0;
    ssi_st[0xc] = 0;
  }
LAB_00419503:
  if ((uVar20 & uVar2) != 0) {
    if (ssi_st[0x46] == 0) {
      puVar1[3] = puVar1[3] & ~uVar20;
    }
    else if (((ssi_st[0x36] == 0) || (ssi_st[0x36] == 2)) || (ssi_st[0x48] != 0)) {
      if (ssi_st[0xc] == 0x800000) {
        ssi_st[0xe] = (*(uint *)(&DAT_004b9320 + ssi_st[0x3c] * 4) & ssi_st[0xb]) >>
                      ((byte)*(undefined4 *)(&DAT_004b9350 + ssi_st[0x3c] * 4) & 0x1f);
        ssi_st[0xf] = *(uint *)(&DAT_004b9330 + ssi_st[0x3c] * 4);
        io_out_pin_write(dev,ssi_st + 0xe,0);
      }
      puVar1[3] = puVar1[3] | uVar20;
      if ((uVar3 & 0x40) == 0) {
        uVar18 = ssi_st[0xc];
      }
      else {
        uVar18 = ssi_st[0xf];
      }
      if ((ssi_st[0xb] & uVar18) == 0) {
        puVar1[2] = puVar1[2] & ~uVar20;
      }
      else {
        puVar1[2] = puVar1[2] | uVar20;
      }
    }
  }
  if (((ssi_st[0x36] == 1) && ((ssi_st[0x38] == 1 || (ssi_st[0x38] == 2)))) || (ssi_st[0x36] == 4))
  {
    ssi_st[0xf] = ssi_st[0xf] << 1;
    ssi_st[0xc] = ssi_st[0xc] >> 1;
  }
  if ((ssi_st[0x36] == 4) && (ssi_st[0x41] != 0)) {
    if (ssi_st[0x38] == 0) {
      if (ssi_st[0x47] == 0) {
LAB_0041966f:
        if (((local_90 != 2) && (local_90 != 4)) && (local_90 != 0x3e)) goto LAB_0041967e;
      }
      else if (((local_90 == 3) || (local_90 == 4)) && (ssi_st[0x17] == 0)) {
        if (ssi_st[0x47] != 0) goto LAB_0041967e;
        goto LAB_0041966f;
      }
    }
    else {
LAB_0041967e:
      if ((ssi_st[0x38] != 3) || (local_90 != 5)) goto LAB_004196ce;
    }
    if (ssi_st[0x3f] != 0) {
      local_a0 = local_a0 | 0x10;
    }
    if (ssi_st[0x47] == 0) {
      local_a0 = local_a0 & 0xfffffffb | 0x40;
    }
    else {
      local_a0 = local_a0 | 0x44;
    }
    ssi_st[0x37] = 0;
    ssi_st[0x44] = 0;
  }
LAB_004196ce:
  if (((uVar10 != 0) && (ssi_st[0x36] == 2)) &&
     (((ssi_st[0x38] == 3 && (local_90 == 5)) ||
      ((ssi_st[0x38] == 0 &&
       ((((ssi_st[0x47] != 0 || (local_90 == 2)) || (local_90 == 0x3e)) || (local_90 == 4)))))))) {
    if (uVar23 != 0) {
      if (uVar11 == 0) {
        puVar1[3] = puVar1[3] & ~uVar28;
      }
      else {
        puVar1[3] = puVar1[3] | uVar28;
        if (ssi_st[0x1a] == 0) {
          puVar1[2] = puVar1[2] & ~uVar28;
        }
        else {
          puVar1[2] = puVar1[2] | uVar28;
        }
      }
    }
    if (uVar22 != 0) {
      if (uVar12 == 0) {
        puVar1[3] = puVar1[3] & ~uVar6;
      }
      else {
        puVar1[3] = puVar1[3] | uVar6;
        if (ssi_st[0x1b] == 0) {
          puVar1[2] = puVar1[2] & ~uVar6;
        }
        else {
          puVar1[2] = puVar1[2] | uVar6;
        }
      }
    }
  }
  if (uVar21 != 0) {
    if (uVar19 == 0) {
      puVar1[3] = puVar1[3] & ~(uVar28 * 8);
    }
    else {
      uVar18 = uVar28 << 3;
      puVar1[3] = puVar1[3] | uVar18;
      if (uVar24 == 0) {
        puVar1[2] = puVar1[2] & ~uVar18;
      }
      else {
        puVar1[2] = puVar1[2] | uVar18;
      }
      if (ssi_st[0x52] == 0) {
        puVar1[2] = puVar1[2] & ~uVar18;
      }
    }
  }
  if (((ssi_st[0x4d] == 0) || ((uVar3 & 0x4000) == 0)) ||
     (((local_a0 & 0x40) == 0 || ((local_a0 & 0x10) == 0)))) {
    uVar18 = 0;
  }
  else {
    uVar18 = 1;
  }
  ssi_st[0x50] = uVar18;
  if (((ssi_st[0x4d] == 0) || ((uVar3 & 0x4000) == 0)) ||
     (((local_a0 & 0x40) == 0 || ((local_a0 & 0x10) != 0)))) {
    uVar18 = 0;
  }
  else {
    uVar18 = 1;
  }
  ssi_st[0x51] = uVar18;
  if (uVar9 == 0) {
    if ((uVar12 == 0) || (uVar10 != 0)) {
      cVar16 = (uVar27 != 0) + '\x03';
    }
    else {
      cVar16 = (uVar27 != 0) + '\x01';
    }
  }
  else if ((uVar11 == 0) || (uVar10 != 0)) {
    cVar16 = '\x05';
  }
  else {
    cVar16 = (uVar27 != 0) + '=';
  }
  uVar18 = ssi_st[0x26];
  if (uVar18 == 1) {
    if (uVar24 != 0) {
      ssi_st[0x26] = 2;
    }
  }
  else if (uVar18 == 2) {
    if (uVar4 == 1) {
      ssi_st[0x26] = 3;
    }
  }
  else if (uVar18 == 3) {
    ssi_st[0x26] = 0;
  }
  uVar18 = uVar24;
  if (ssi_st[0x26] == 0) {
    if (uVar10 == 0) {
      if (uVar11 == 0) {
        uVar18 = local_4c;
      }
    }
    else {
      uVar18 = uVar25;
      if (uVar19 != 0) {
        uVar18 = puVar1[2] & uVar28 << 3;
      }
    }
  }
  if (ssi_st[0x2e] != 0) goto LAB_0041a097;
  if ((uVar18 == 0) || (ssi_st[0x31] != 0)) {
    bVar7 = false;
  }
  else {
    bVar7 = true;
  }
  if ((uVar18 == 0) && (ssi_st[0x31] != 0)) {
    bVar8 = true;
  }
  else {
    bVar8 = false;
  }
  ssi_st[0x31] = uVar18;
  ssi_st[0x32] = ssi_st[0x32] | 0x10;
  if ((bVar7) && (ssi_st[0x32] = (-(uint)(ssi_st[0x25] != 0) & 0xfffffffe) + 2, uVar26 != 0)) {
    ssi_st[0x16] = ssi_st[0x29];
  }
  if (uVar10 == 0) {
    if ((cVar16 == '\x03') || (cVar16 == '\x04')) {
      ssi_st[0x2a] = local_64;
      if ((ssi_st[0x2a] != 0) && ((uVar26 == 0 && (ssi_st[0x2c] == 0)))) {
        ssi_st[0x16] = 1;
        ssi_st[0x2c] = ssi_st[0x2a];
      }
      if (bVar8) {
        if (((uVar26 != 0) && (ssi_st[0x2a] != 0)) && (ssi_st[0x2c] == 0)) {
          ssi_st[0x29] = 1;
        }
        ssi_st[0x2c] = ssi_st[0x2a];
      }
      else if (ssi_st[0x32] == 0) {
        ssi_st[0x29] = 0;
        ssi_st[0x16] = 0;
      }
    }
  }
  else {
    ssi_st[0x2a] = ssi_st[0x49];
    ssi_st[0x2c] = ssi_st[0x4b];
    if (uVar26 == 0) {
      ssi_st[0x16] = ssi_st[0x17];
    }
    else {
      ssi_st[0x29] = ssi_st[9];
    }
  }
  if (bVar8) {
    ssi_st[0x32] = (-(uint)((ssi_st[0x32] & 2) != 0) & 3) + 1;
    if (ssi_st[0x25] == 0) {
      if ((((ssi_st[0x34] != 0) || ((cVar16 != '\x03' && (cVar16 != '\x04')))) ||
          (ssi_st[0x16] != 0)) || (ssi_st[0x27] == 0)) {
        ssi_st[0x25] = 1;
      }
    }
    else {
      ssi_st[0x25] = 0;
    }
  }
  if (ssi_st[0x32] != 0) goto switchD_00419b5f_default;
  switch(ssi_st[0x34]) {
  case 0:
    ssi_st[0x34] = 2;
    goto switchD_00419b5f_default;
  case 1:
    uVar19 = (cVar16 != '\x05') - 1 & 3;
    break;
  case 2:
    uVar19 = (ssi_st[0x1f] != 0) + 1;
    break;
  case 3:
    uVar19 = (cVar16 != '\x05') - 1 & 2;
    break;
  default:
    goto switchD_00419b5f_default;
  }
  ssi_st[0x34] = uVar19;
switchD_00419b5f_default:
  if (ssi_st[0x34] == 0) {
    if (((ssi_st[0x32] == 0) && (uVar26 != 0)) && (ssi_st[0x27] != 0)) {
      ssi_st[0x2b] = 1;
    }
    else if (ssi_st[0x32] == 2) {
      if (ssi_st[0x27] == 0) {
        uVar19 = 0;
      }
      else {
        uVar19 = (uint)(uVar26 == 0);
      }
      ssi_st[0x2b] = uVar19;
      if (((uVar13 == 0) && (uVar26 == 0)) && ((cVar16 == '=' || (cVar16 == '>')))) {
        ssi_st[0x2c] = 0;
      }
    }
  }
  if (((uVar10 == 0) && (cVar16 != '\x03')) && (cVar16 != '\x04')) {
    ssi_st[0x2a] = ssi_st[0x2b];
    if (((ssi_st[0x2a] != 0) && (uVar26 == 0)) && (ssi_st[0x2c] == 0)) {
      ssi_st[0x16] = 1;
      ssi_st[0x2c] = ssi_st[0x2a];
    }
    if (bVar8) {
      if (((uVar26 != 0) && (ssi_st[0x2a] != 0)) && (ssi_st[0x2c] == 0)) {
        ssi_st[0x29] = 1;
      }
      ssi_st[0x2c] = ssi_st[0x2a];
    }
    else if (ssi_st[0x32] == 0) {
      ssi_st[0x29] = 0;
      ssi_st[0x16] = 0;
    }
  }
  if ((ssi_st[0x22] != 0) && (ssi_st[0x32] == 4)) {
    if ((ssi_st[0x27] != 0) && ((ssi_st[0x34] == 0 && (ssi_st[0x16] != 0)))) {
      ssi_st[0x2d] = 1;
    }
    if ((ssi_st[0x34] == 1) && (((ssi_st[0x2d] != 0 || (uVar27 != 0)) || (cVar16 == '\x05')))) {
      ssi_st[0x28] = 1;
    }
  }
  uVar26 = ssi_st[0x32];
  if ((((uVar26 == 1) && (ssi_st[0x34] == 0)) ||
      ((uVar26 == 2 && ((ssi_st[0x34] == 3 && (cVar16 == '\x05')))))) ||
     ((uVar26 == 4 &&
      ((ssi_st[0x34] == 0 &&
       ((((cVar16 == '\x03' || (cVar16 == '\x04')) && (ssi_st[0x16] == 0)) && (ssi_st[0x27] != 0))))
      )))) {
    if (ssi_st[0x27] != 0) {
      ssi_st[0x21] = uVar3 & 0x2000;
    }
    ssi_st[0x22] = ssi_st[0x21];
    ssi_st[0x20] = uVar17 >> 0xd & 3;
    ssi_st[0x1d] = uVar13;
  }
  if (ssi_st[0x32] == 2) {
    if ((ssi_st[0x34] == 0) || (ssi_st[0x34] == 3)) {
      ssi_st[0x1e] = ssi_st[0x20];
      ssi_st[0x1f] = *(uint *)(&DAT_004b9360 + ssi_st[0x20] * 4);
    }
    if ((ssi_st[0x34] == 0) && (ssi_st[0x27] != 0)) {
      ssi_st[0x1c] = ssi_st[0x1d] + 1;
    }
  }
  else if (ssi_st[0x32] == 4) {
    if (ssi_st[0x34] == 2) {
      ssi_st[0x1f] = ssi_st[0x1f] - 1;
    }
    else if (ssi_st[0x34] == 1) {
      ssi_st[0x1c] = ssi_st[0x1c] - 1;
      ssi_st[0x27] = (uint)(ssi_st[0x1c] == 0);
    }
  }
  if (((ssi_st[0x32] == 1) && (uVar9 != 0)) && (ssi_st[0x34] == 0)) {
    if (ssi_st[0x27] != 0) {
      ssi_st[0x53] = 1;
    }
    if (((ssi_st[0x34] == 0) && (cVar16 == '=')) && (ssi_st[0x27] == 0)) {
      ssi_st[0x53] = 0;
    }
  }
  if ((bVar8) && (ssi_st[0xd] = ssi_st[0xd] << 1, local_38 != 0)) {
    ssi_st[0xd] = ssi_st[0xd] | 1;
  }
  if ((ssi_st[0x32] == 4) && ((ssi_st[0x34] == 0 || (ssi_st[0x34] == 3)))) {
    if (uVar10 == 0) {
      ssi_st[0x19] = 0;
      ssi_st[0x18] = 0;
    }
    else {
      ssi_st[0x18] = ~-(uint)(uVar11 != 0) & local_4c;
      ssi_st[0x19] = ~-(uint)(uVar12 != 0) & local_64;
    }
  }
  if (((ssi_st[0x32] == 1) && (ssi_st[0x28] != 0)) &&
     ((ssi_st[0x34] == 0 || ((ssi_st[0x34] == 3 && (cVar16 == '\x05')))))) {
    if ((ssi_st[0x2d] == 0) && (cVar16 != '\x05')) {
      uVar17 = local_a0 & 0xfffffff7;
    }
    else {
      uVar17 = local_a0 | 8;
    }
    if ((uVar17 & 0x80) == 0) {
      local_a0 = uVar17 & 0xfffffffc | 0x80;
      if (ssi_st[0x18] != 0) {
        local_a0 = uVar17 & 0xfffffffc | 0x81;
      }
      if (ssi_st[0x19] != 0) {
        local_a0 = local_a0 | 2;
      }
      iVar15 = io_in_pin_read(dev,local_28);
      if ((iVar15 != 0) || (iVar15 = io_in_timed_pin_read(dev,local_28), iVar15 != 0)) {
        ssi_st[10] = local_20;
        ssi_st[0xd] = ssi_st[10];
      }
      if (ssi_st[0xd] == 0xfffffffe) {
        ssi_st[2] = 0;
      }
      else {
        ssi_st[2] = (*(uint *)(&DAT_004b9340 + ssi_st[0x1e] * 4) & ssi_st[0xd]) <<
                    ((byte)*(undefined4 *)(&DAT_004b9350 + ssi_st[0x1e] * 4) & 0x1f);
        if ((uVar3 & 0x40) != 0) {
          uVar26 = 0;
          uVar9 = 0x800000;
          uVar17 = *(uint *)(&DAT_004b9330 + ssi_st[0x1e] * 4);
          iVar15 = *(int *)(&DAT_004b9370 + ssi_st[0x1e] * 4);
          if (iVar15 != 0) {
            do {
              if ((ssi_st[2] & uVar9) != 0) {
                uVar26 = uVar26 | uVar17;
              }
              uVar9 = uVar9 >> 1;
              uVar17 = uVar17 << 1;
              iVar15 = iVar15 + -1;
            } while (iVar15 != 0);
          }
          ssi_st[2] = uVar26;
        }
      }
      ssi_refresh_reg(2);
    }
    else {
      local_a0 = uVar17 | 0x20;
    }
    ssi_st[0x2d] = 0;
    ssi_st[0x28] = 0;
  }
LAB_0041a097:
  if ((((ssi_st[0x4d] == 0) || ((uVar3 & 0x8000) == 0)) || ((local_a0 & 0x80) == 0)) ||
     ((local_a0 & 0x20) == 0)) {
    uVar17 = 0;
  }
  else {
    uVar17 = 1;
  }
  ssi_st[0x4e] = uVar17;
  if (((ssi_st[0x4d] == 0) || ((uVar3 & 0x8000) == 0)) ||
     (((local_a0 & 0x80) == 0 || ((local_a0 & 0x20) != 0)))) {
    uVar17 = 0;
  }
  else {
    uVar17 = 1;
  }
  ssi_st[0x4f] = uVar17;
  if ((uVar14 & uVar2) != 0) {
    if ((uVar3 & 0x10) == 0) {
      puVar1[3] = puVar1[3] & ~uVar14;
    }
    else {
      puVar1[3] = puVar1[3] | uVar14;
      if (ssi_st[0x49] == 0) {
        puVar1[2] = puVar1[2] & ~uVar14;
      }
      else {
        puVar1[2] = puVar1[2] | uVar14;
      }
    }
  }
  if (uVar10 == 0) {
    if (uVar23 != 0) {
      if (uVar11 == 0) {
        puVar1[3] = puVar1[3] & ~uVar28;
      }
      else {
        puVar1[3] = puVar1[3] | uVar28;
        if (uVar24 == 0) {
          puVar1[2] = puVar1[2] & ~uVar28;
        }
        else {
          puVar1[2] = puVar1[2] | uVar28;
        }
        if (ssi_st[0x53] == 0) {
          puVar1[2] = puVar1[2] & ~uVar28;
        }
      }
    }
    if (uVar22 != 0) {
      if (uVar12 == 0) {
        puVar1[3] = puVar1[3] & ~uVar6;
      }
      else {
        puVar1[3] = puVar1[3] | uVar6;
        if (ssi_st[0x2a] == 0) {
          puVar1[2] = puVar1[2] & ~uVar6;
        }
        else {
          puVar1[2] = puVar1[2] | uVar6;
        }
      }
    }
  }
  if (local_a0 != ssi_st[3]) {
    ssi_set_reg(3,local_a0);
  }
  ssi_st[0x23] = 0;
  ssi_st[0x48] = 0;
  if ((ssi_st[0x45] == 0) && (uVar25 == 0)) {
    ssi_st[0x4c] = 0;
  }
  if ((ssi_st[0x26] == 0) && (uVar18 == 0)) {
    ssi_st[0x2e] = 0;
  }
  return;
}


