/* ==== dax_m_poke @ 0040a0a0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dax_m_poke(int grp,int reg,ulong *val)

{
  int iVar1;
  
  _dax_gruntime = *(int *)(cur_sim + 8) + grp * 8;
  _dax_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  dax_flags = *(undefined4 *)(_dax_gruntime + 4);
  _dax_regs_slot = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  dax_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  dax_regs = *_dax_regs_slot;
  iVar1 = *(int *)(dax_grp + 0x2c);
  if ((reg < *(int *)(iVar1 + 0x28)) &&
     ((*(byte *)(*(int *)(iVar1 + 0x2c) + 0x10 + reg * 0x1c) & 0x40) != 0)) {
    dax_write_reg(reg,*val);
    dax_touch_reg(reg);
    return 1;
  }
  if (reg < *(int *)(iVar1 + 0x24)) {
    *(ulong *)(dax_regs + reg * 4) = *val;
  }
  dax_touch_reg(reg);
  return 1;
}


/* ==== dax_m_clock @ 0040a170 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dax_m_clock(int grp)

{
  _dax_gruntime = *(int *)(cur_sim + 8) + grp * 8;
  _dax_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  dax_flags = *(undefined4 *)(_dax_gruntime + 4);
  _dax_regs_slot = (undefined4 *)(*(int *)(cur_dev + 8) + grp * 4);
  dax_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  dax_regs = *_dax_regs_slot;
  dax_cpu_ctl = *(undefined4 *)(cur_dev + 0x40);
  dax_clock(grp);
  return;
}


/* ==== dax_m_io_write @ 0040a1f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dax_m_io_write(int grp,ulong addr,ulong val)

{
  int iVar1;
  uint reg;
  
  dax_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  _dax_regs_slot = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  dax_regs = *_dax_regs_slot;
  iVar1 = addr - *(ulong *)(dax_grp + 0x1c);
  if (addr == *(ulong *)(dax_grp + 0x1c)) {
    reg = (uint)(*(int *)(dax_regs + 0x38) != 0);
  }
  else if (iVar1 == 2) {
    reg = 2;
  }
  else if (iVar1 == 3) {
    reg = 3;
  }
  else {
    if (addr != 0xffff) {
      return 0;
    }
    reg = 0xd;
  }
  _dax_gruntime = *(int *)(cur_sim + 8) + grp * 8;
  _dax_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  dax_flags = *(undefined4 *)(_dax_gruntime + 4);
  if (reg != 0xd) {
    dax_write_reg(reg,val);
    return 0;
  }
  *(uint *)(dax_regs + 0x34) = *(uint *)(dax_grp + 0x28) & val;
  return 0;
}


/* ==== dax_m_io_read @ 0040a2d0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dax_m_io_read(int grp,ulong addr,ulong *out,int side)

{
  int iVar1;
  uint reg;
  int extraout_EAX;
  
  dax_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  _dax_regs_slot = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  dax_regs = *_dax_regs_slot;
  iVar1 = addr - *(int *)(dax_grp + 0x1c);
  if (iVar1 == 0) {
    reg = ~*(uint *)(dax_regs + 0xc) & 1;
  }
  else if (iVar1 == 2) {
    reg = 2;
  }
  else {
    if (iVar1 + -3 != 0) {
      return iVar1 + -3;
    }
    reg = 3;
  }
  _dax_gruntime = *(int *)(cur_sim + 8) + grp * 8;
  _dax_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  dax_flags = *(undefined4 *)(_dax_gruntime + 4);
  dax_read_reg(reg,out,side);
  return extraout_EAX;
}


/* ==== dax_m_reset @ 0040a380 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dax_m_reset(int grp)

{
  _dax_gruntime = *(int *)(cur_sim + 8) + grp * 8;
  _dax_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  dax_flags = *(undefined4 *)(_dax_gruntime + 4);
  _dax_regs_slot = (undefined4 *)(*(int *)(cur_dev + 8) + grp * 4);
  dax_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  dax_regs = *_dax_regs_slot;
  dax_reset_regs();
  return;
}


/* ==== dax_reset_regs @ 0040a3f0 ==== */

void dax_reset_regs(void)

{
  *(undefined4 *)(dax_regs + 100) = 0;
  *(undefined4 *)(dax_regs + 0x30) = 0;
  *(undefined4 *)(dax_regs + 0xc) = 0;
  *(undefined4 *)(dax_regs + 0x2c) = 0;
  *(undefined4 *)(dax_regs + 0x28) = 0;
  *(undefined4 *)(dax_regs + 0x54) = 0;
  *(undefined4 *)(dax_regs + 0x48) = 0;
  *(undefined4 *)(dax_regs + 0x38) = 0;
  *(uint *)(dax_regs + 8) = *(uint *)(dax_regs + 8) & 0xfc00;
  dax_touch_reg(2);
  dax_touch_reg(3);
  return;
}


/* ==== dax_m_irq_poll @ 0040a460 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dax_m_irq_poll(int grp)

{
  int iVar1;
  
  _dax_regs_slot = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  dax_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  dax_regs = *_dax_regs_slot;
  if (*(int *)(dax_regs + 0x34) != 0) {
    iVar1 = *(int *)(dax_grp + 0x20);
    if (*(int *)(dax_regs + 0x28) != 0) {
      return iVar1;
    }
    if (*(int *)(dax_regs + 0x2c) != 0) {
      return iVar1 + 2;
    }
    if (*(int *)(dax_regs + 0x30) != 0) {
      return iVar1 + 6;
    }
  }
  return -1;
}


/* ==== dax_m_irq_ack @ 0040a4c0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dax_m_irq_ack(int grp,ulong vec)

{
  _dax_regs_slot = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  dax_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  dax_regs = *_dax_regs_slot;
  if (vec == *(ulong *)(dax_grp + 0x20)) {
    *(undefined4 *)(dax_regs + 0x28) = 0;
    return;
  }
  *(undefined4 *)(dax_regs + ((vec - *(ulong *)(dax_grp + 0x20) != 2) + 0xb) * 4) = 0;
  return;
}


/* ==== dax_write_reg @ 0040a530 ==== */

void __cdecl dax_write_reg(int reg,ulong val)

{
  if (reg == 0) {
    *(undefined4 *)(dax_regs + 0x38) = 1;
  }
  else if (reg == 1) {
    if ((*(uint *)(dax_regs + 0xc) & 9) != 0) {
      *(uint *)(dax_regs + 0xc) = *(uint *)(dax_regs + 0xc) & 0xfffffff6;
      dax_touch_reg(3);
    }
    if (((*(byte *)(dax_regs + 0xc) & 4) != 0) && (*(int *)(dax_regs + 0x50) != 0)) {
      *(undefined4 *)(dax_regs + 0x50) = 0;
      *(uint *)(dax_regs + 0xc) = *(uint *)(dax_regs + 0xc) & 0xfffffffb;
      dax_touch_reg(3);
    }
  }
  else if (reg == 2) {
    if (((*(uint *)(dax_regs + reg * 4) & 1) != 0) && ((val & 1) == 0)) {
      *(ulong *)(dax_regs + 0x40) = val >> 2 & 1;
    }
    if ((val & 4) == 0) {
      *(undefined4 *)(dax_regs + 0x40) = 0;
    }
  }
  *(uint *)(dax_regs + reg * 4) =
       *(uint *)(*(int *)(*(int *)(dax_grp + 0x2c) + 0x2c) + 4 + reg * 0x1c) & val;
  *(uint *)(dax_flags + reg * 4) = *(uint *)(dax_flags + reg * 4) | 0xa0000;
  if ((*(uint *)(dax_flags + reg * 4) & 0x1800000) != 0) {
    io_out_periph_write((dax_grp - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
  }
  return;
}


/* ==== dax_touch_reg @ 0040a640 ==== */

void __cdecl dax_touch_reg(int reg)

{
  int iVar1;
  
  if (reg < *(int *)(*(int *)(dax_grp + 0x2c) + 0x28)) {
    *(uint *)(dax_flags + reg * 4) = *(uint *)(dax_flags + reg * 4) | 0xa0000;
    *(uint *)(dax_regs + reg * 4) =
         *(uint *)(dax_regs + reg * 4) &
         *(uint *)(*(int *)(*(int *)(dax_grp + 0x2c) + 0x2c) + 4 + reg * 0x1c);
    iVar1 = reg * 0x1c + *(int *)(*(int *)(dax_grp + 0x2c) + 0x2c);
    if ((*(byte *)(iVar1 + 0x10) & 0x60) != 0) {
      mem_trace_fetch(*(int *)(dax_grp + 0x1c) + *(int *)(iVar1 + 8));
    }
    if ((*(uint *)(dax_flags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write((dax_grp - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
    }
  }
  return;
}


/* ==== dax_read_reg @ 0040a700 ==== */

void __cdecl dax_read_reg(int reg,ulong *out,int side_effect)

{
  *out = *(ulong *)(dax_regs + reg * 4);
  if (((side_effect != 0) && (reg == 3)) && ((*(byte *)(dax_regs + 0xc) & 4) != 0)) {
    *(undefined4 *)(dax_regs + 0x50) = 1;
  }
  return;
}


/* ==== dax_clock @ 0040a740 ==== */

void __cdecl dax_clock(int dev)

{
  uint *puVar1;
  uint uVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  bool bVar8;
  uint local_14;
  
  if ((*(int *)(dax_cpu_ctl + 0xc) == 0) && (*(int *)(dax_cpu_ctl + 8) != 1)) {
    bVar8 = false;
  }
  else {
    bVar8 = true;
  }
  uVar4 = *(uint *)(dax_grp + 8);
  uVar4 = uVar4 & (uVar4 - 1 ^ uVar4);
  uVar2 = uVar4 * 2;
  puVar1 = (uint *)(*(int *)(cur_dev + 0x18) + *(int *)(dax_grp + 4) * 0x128);
  puVar1[3] = (uVar2 | *(uint *)(*(int *)(cur_dev + 0x18) + 0xc + *(int *)(dax_grp + 4) * 0x128)) &
              ~uVar4;
  if (bVar8) {
    if (dax_regs[0x16] != 0) {
      return;
    }
    puVar1[2] = puVar1[2] | uVar2;
    dax_regs[0x16] = 1;
    dax_reset_regs();
    return;
  }
  dax_regs[0x16] = 0;
  uVar7 = dax_regs[2];
  local_14 = dax_regs[3];
  if (((uVar7 & 1) == 0) && (dax_regs[0x10] == 0)) {
    bVar8 = false;
  }
  else {
    bVar8 = true;
  }
  if (!bVar8) {
    puVar1[2] = puVar1[2] | uVar2;
    dax_regs[0x12] = 0;
    goto LAB_0040ac70;
  }
  if ((uVar7 & 0x18) == 0) {
    uVar4 = dax_regs[0x18];
    uVar5 = *(uint *)(dax_cpu_ctl + 4) & 1;
    dax_regs[0x18] = uVar5;
    bVar8 = uVar5 != uVar4;
    uVar4 = 7;
  }
  else {
    if (((uVar4 & *puVar1) == 0) || (dax_regs[0x11] != 0)) {
      bVar8 = false;
    }
    else {
      bVar8 = true;
    }
    dax_regs[0x11] = uVar4 & *puVar1;
    if ((uVar7 & 8) == 0) {
      uVar4 = 2;
    }
    else {
      uVar4 = (uint)(byte)(((byte)uVar7 & 0x10 | 8) >> 3);
    }
  }
  if (bVar8) {
    bVar8 = dax_regs[0x12] == 0;
    if (!bVar8) {
      uVar4 = dax_regs[0x12] - 1;
    }
    dax_regs[0x12] = uVar4;
  }
  else {
    bVar8 = false;
  }
  if (!bVar8) goto LAB_0040ac51;
  bVar8 = false;
  uVar5 = 0;
  bVar3 = false;
  uVar4 = dax_regs[0x19];
  switch(uVar4) {
  case 0:
    uVar4 = 1;
    uVar5 = 1;
    local_14 = local_14 & 0xfffffff7 | 0x10;
    bVar8 = true;
    break;
  case 1:
    uVar4 = 2;
    break;
  case 2:
    uVar4 = 3;
    break;
  case 3:
    uVar4 = 4;
    uVar5 = 1;
    break;
  case 4:
    uVar4 = 5;
    uVar5 = 1;
    break;
  case 5:
    uVar4 = 6;
    uVar5 = 1;
    break;
  case 6:
    uVar4 = 7;
    break;
  case 7:
    uVar4 = 0x10;
    break;
  case 8:
    uVar5 = 1;
    uVar4 = 9;
    bVar8 = true;
    break;
  case 9:
    uVar4 = 10;
    break;
  case 10:
    uVar4 = 0xb;
    break;
  case 0xb:
    uVar4 = 0xc;
    uVar5 = 1;
    break;
  case 0xc:
    uVar4 = 0xd;
    break;
  case 0xd:
    uVar4 = 0xe;
    break;
  case 0xe:
    uVar4 = 0xf;
    uVar5 = 1;
    break;
  case 0xf:
    uVar4 = 0x10;
    uVar5 = 1;
    break;
  case 0x10:
    uVar4 = 0x11;
    uVar5 = 1;
    break;
  case 0x11:
    uVar5 = dax_regs[5] & 1;
    dax_regs[6] = dax_regs[6] ^ uVar5;
    if (dax_regs[9] == 0) {
      uVar4 = 0x12;
    }
    else {
      uVar4 = 0x10;
      dax_regs[9] = dax_regs[9] + -1;
LAB_0040aa99:
      dax_regs[5] = (uint)dax_regs[5] >> 1;
    }
    break;
  case 0x12:
    uVar4 = 0x13;
    uVar5 = 1;
    break;
  case 0x13:
    uVar4 = 0x14;
    goto LAB_0040aad6;
  case 0x14:
    uVar5 = 1;
    uVar4 = 0x15;
    bVar3 = true;
    break;
  case 0x15:
    uVar4 = 0x16;
    break;
  case 0x16:
    uVar4 = 0x17;
    break;
  case 0x17:
    uVar4 = 0x18;
    uVar5 = 1;
    break;
  case 0x18:
    uVar4 = 0x19;
    break;
  case 0x19:
    uVar4 = 0x1a;
    uVar5 = 1;
    break;
  case 0x1a:
    uVar4 = 0x1b;
    uVar5 = 1;
    break;
  case 0x1b:
    uVar4 = 0x1c;
    break;
  case 0x1c:
    uVar4 = 0x1d;
    uVar5 = 1;
    break;
  case 0x1d:
    uVar5 = dax_regs[5] & 1;
    dax_regs[6] = dax_regs[6] ^ uVar5;
    if (dax_regs[9] != 0) {
      uVar4 = 0x1c;
      dax_regs[9] = dax_regs[9] + -1;
      goto LAB_0040aa99;
    }
    uVar4 = 0x1e;
    break;
  case 0x1e:
    uVar4 = 0x1f;
    uVar5 = 1;
    break;
  case 0x1f:
    if (dax_regs[0x10] == 0) {
      uVar4 = -(uint)(dax_regs[0x15] != 0) & 8;
    }
    else {
      uVar4 = 0x20;
    }
LAB_0040aad6:
    uVar5 = dax_regs[6];
    break;
  case 0x20:
    dax_regs[0x10] = 0;
    local_14 = local_14 & 0xffffffef;
    uVar4 = 0;
  }
  if (bVar8) {
    dax_regs[9] = 0x1a;
    dax_regs[5] = *dax_regs;
    if ((uVar7 & 0x400) != 0) {
      dax_regs[5] = dax_regs[5] | 0x1000000;
    }
    if ((uVar7 & 0x800) != 0) {
      dax_regs[5] = dax_regs[5] | 0x2000000;
    }
    if ((uVar7 & 0x1000) != 0) {
      dax_regs[5] = dax_regs[5] | 0x4000000;
    }
    io_out_pin_write(dev,dax_regs + 5,0);
    dax_regs[4] = dax_regs[1];
    dax_regs[7] = uVar7;
    dax_regs[0xe] = 0;
    if ((local_14 & 1) == 0) {
      local_14 = local_14 | 1;
    }
    else {
      local_14 = local_14 | 4;
    }
    if (dax_regs[0x15] == 0xbf) {
      dax_regs[0x15] = 0;
      local_14 = local_14 | 8;
    }
    else {
      dax_regs[0x15] = dax_regs[0x15] + 1;
    }
    dax_regs[6] = 0;
  }
  if (bVar3) {
    dax_regs[6] = 0;
    dax_regs[9] = 0x1a;
    dax_regs[5] = dax_regs[4];
    if ((dax_regs[7] & 0x2000) != 0) {
      dax_regs[5] = dax_regs[5] | 0x1000000;
    }
    if ((dax_regs[7] & 0x4000) != 0) {
      dax_regs[5] = dax_regs[5] | 0x2000000;
    }
    if ((dax_regs[7] & 0x8000) != 0) {
      dax_regs[5] = dax_regs[5] | 0x4000000;
    }
    io_out_pin_write(dev,dax_regs + 5,0);
  }
  dax_regs[0x19] = uVar4;
  if (uVar5 != 0) {
    puVar1[2] = puVar1[2] ^ uVar2;
  }
LAB_0040ac51:
  if (local_14 != dax_regs[3]) {
    dax_regs[3] = local_14;
    dax_touch_reg(3);
  }
LAB_0040ac70:
  uVar7 = uVar7 & 2;
  if ((uVar7 == 0) || ((local_14 & 1) == 0)) {
    uVar6 = 0;
  }
  else {
    uVar6 = 1;
  }
  dax_regs[0xc] = uVar6;
  if ((uVar7 == 0) || ((local_14 & 4) == 0)) {
    uVar6 = 0;
  }
  else {
    uVar6 = 1;
  }
  dax_regs[10] = uVar6;
  if ((uVar7 != 0) && ((local_14 & 8) != 0)) {
    dax_regs[0xb] = 1;
    return;
  }
  dax_regs[0xb] = 0;
  return;
}


