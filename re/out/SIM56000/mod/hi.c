/* ==== hi_write_reg @ 0041a300 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl hi_write_reg(int dev,int reg,ulong *val)

{
  uint uVar1;
  uint uVar2;
  ulong val_00;
  
  uVar1 = *val;
  hi_status = *(int *)(cur_sim + 8) + dev * 8;
  val_00 = uVar1 & 0xffffff;
  _hi_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  hi_regflags = *(undefined4 *)(hi_status + 4);
  _hi_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  hi_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  hi_st = *_hi_stslot;
  switch(reg) {
  case 0:
    val_00 = val_00 & (-(uint)(*(uint *)(cur_dtype + 8) < 4) & 0xffffffe0) + 0xbf;
    if ((val_00 & 0x80) == 0) {
      hi_set_reg(3,*(uint *)(hi_st + 0xc) & 0xfffffffb);
    }
    else {
      hi_set_reg(3,*(uint *)(hi_st + 0xc) | 4);
    }
    break;
  case 5:
    if ((uVar1 & 0x80) != 0) {
      *(uint *)(hi_st + 0x38) = (uVar1 & 0xfb) >> 5 & 3;
      if ((uVar1 & 1) != 0) {
        hi_set_reg(6,*(uint *)(hi_st + 0x18) & 0xfffffffe);
        hi_set_reg(3,*(uint *)(hi_st + 0xc) | 2);
      }
      if ((uVar1 & 2) != 0) {
        hi_set_reg(6,*(uint *)(hi_st + 0x18) | 2);
        hi_set_reg(3,*(uint *)(hi_st + 0xc) & 0xfffffffe);
      }
    }
    *(uint *)(hi_st + 0xc) = *(uint *)(hi_st + 0xc) & 0xffffffe7;
    *(uint *)(hi_st + 0xc) = *(uint *)(hi_st + 0xc) | uVar1 & 0x18;
    hi_refresh_reg(3);
    if ((uVar1 & 0x60) == 0) {
      *(uint *)(hi_st + 0x18) = *(uint *)(hi_st + 0x18) & 0xffffffbf;
      uVar2 = *(uint *)(hi_st + 0xc) & 0xffffff7f;
    }
    else {
      *(uint *)(hi_st + 0x18) = *(uint *)(hi_st + 0x18) | 0x40;
      uVar2 = *(uint *)(hi_st + 0xc) | 0x80;
    }
    *(uint *)(hi_st + 0xc) = uVar2;
    val_00 = (ulong)((byte)(uVar1 & 0xfb) & 0x7f);
    hi_refresh_reg(6);
    break;
  case 7:
  case 8:
  case 9:
  case 0xb:
  case 0xd:
    val_00 = uVar1 & 0xff;
    break;
  case 0xc:
    *(undefined4 *)(hi_st + 0x48) = 1;
    val_00 = uVar1 & 0xff;
    *(uint *)(hi_st + 0x78) = (*(uint *)(hi_st + 0x34) | *(int *)(hi_st + 0x2c) << 8) << 8 | val_00;
  }
  if ((reg < *(int *)(*(int *)(hi_dev + 0x2c) + 0x28)) &&
     ((*(byte *)(*(int *)(*(int *)(hi_dev + 0x2c) + 0x2c) + 0x10 + reg * 0x1c) & 0x40) != 0)) {
    hi_write_reg_masked(reg,val_00);
    hi_refresh_reg(reg);
    return 1;
  }
  *(ulong *)(hi_st + reg * 4) = val_00;
  hi_refresh_reg(reg);
  return 1;
}


/* ==== hi_tick_a @ 0041a570 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void hi_tick_a(int dev)

{
  hi_status = *(int *)(cur_sim + 8) + dev * 8;
  _hi_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  hi_regflags = *(undefined4 *)(hi_status + 4);
  _hi_stslot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  hi_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  hi_st = *_hi_stslot;
  _DAT_004dbd9c = *(int *)(cur_dev + 0x40);
  if ((*(int *)(_DAT_004dbd9c + 0xc) == 0) && (*(int *)(_DAT_004dbd9c + 8) != 1)) {
    hi_clock_a(dev,1);
  }
  return;
}


/* ==== hi_tick_b @ 0041a600 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void hi_tick_b(int dev)

{
  hi_status = *(int *)(cur_sim + 8) + dev * 8;
  _hi_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  hi_regflags = *(undefined4 *)(hi_status + 4);
  _hi_stslot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  hi_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  hi_st = *_hi_stslot;
  _DAT_004dbd9c = *(int *)(cur_dev + 0x40);
  if ((*(int *)(_DAT_004dbd9c + 0xc) == 0) && (*(int *)(_DAT_004dbd9c + 8) != 1)) {
    hi_clock_b(dev,1);
  }
  return;
}


/* ==== hi_reset @ 0041a690 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int hi_reset(int dev)

{
  int extraout_EAX;
  int in_stack_00000008;
  
  hi_status = *(int *)(cur_sim + 8) + dev * 8;
  _hi_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  hi_regflags = *(undefined4 *)(hi_status + 4);
  _hi_stslot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  hi_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  hi_st = *_hi_stslot;
  hi_reset_state(in_stack_00000008);
  return extraout_EAX;
}


/* ==== hi_int_pending @ 0041a710 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long hi_int_pending(int dev)

{
  _hi_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  hi_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  hi_st = (uint *)*_hi_stslot;
  if (hi_st[0x16] != 0) {
    if (hi_st[0xf] != 0) {
      return (*hi_st & 0x3f) << 1;
    }
    if (hi_st[0x10] != 0) {
      return *(int *)(hi_dev + 0x20);
    }
    if (hi_st[0x11] != 0) {
      return *(int *)(hi_dev + 0x20) + 2;
    }
  }
  return -1;
}


/* ==== hi_int_ack @ 0041a770 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int hi_int_ack(int dev,long vec)

{
  uint *puVar1;
  int iVar2;
  
  _hi_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  hi_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  hi_st = (uint *)*_hi_stslot;
  hi_status = *(int *)(cur_sim + 8) + dev * 8;
  hi_regflags = *(undefined4 *)(hi_status + 4);
  if ((hi_st[0x1d] != 0) && (vec == (*hi_st & 0x3f) * 2)) {
    hi_set_reg(0,*hi_st & 0x3f);
    hi_set_reg(3,hi_st[3] & 0xfffffffb);
    puVar1 = hi_st;
    hi_st[0x1d] = 0;
    hi_st[0xf] = 0;
    return (int)puVar1;
  }
  iVar2 = (vec != *(int *)(hi_dev + 0x20)) + 0x10;
  hi_st[iVar2] = 0;
  return iVar2;
}


/* ==== hi_set_reg @ 0041a830 ==== */

void __cdecl hi_set_reg(int reg,ulong val)

{
  *(ulong *)(hi_st + reg * 4) = val;
  hi_refresh_reg(reg);
  return;
}


/* ==== hi_write_io @ 0041a850 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int hi_write_io(int dev,ulong addr,ulong val)

{
  int iVar1;
  uint uVar2;
  
  hi_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  if (addr == *(ulong *)(hi_dev + 0x1c)) {
    iVar1 = 1;
  }
  else if (addr - *(ulong *)(hi_dev + 0x1c) == 3) {
    iVar1 = 4;
  }
  else if (addr == 0xffff) {
    iVar1 = 0x16;
  }
  else {
    iVar1 = addr - *(ulong *)(hi_dev + 0x14);
    if (addr == *(ulong *)(hi_dev + 0x14)) {
      iVar1 = 0x17;
    }
    else if (iVar1 == 2) {
      iVar1 = 0x19;
    }
    else {
      if (iVar1 != 4) {
        return 0;
      }
      iVar1 = 0x18;
    }
  }
  hi_status = *(int *)(cur_sim + 8) + dev * 8;
  _hi_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  hi_regflags = *(undefined4 *)(hi_status + 4);
  _hi_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  hi_st = *_hi_stslot;
  if ((iVar1 != 0x19) && (iVar1 != 0x18)) {
    if (iVar1 == 0x17) {
      if (*(uint *)(cur_dtype + 8) < 4) {
        uVar2 = 0;
      }
      else {
        uVar2 = *(uint *)(hi_dev + 0x18) & *(uint *)(hi_dev + 0x18) * 2;
      }
      iVar1 = hi_find_pin_shift();
      *(uint *)(hi_st + 0x5c) = *(uint *)(hi_dev + 0x18) & val;
      *(uint *)(hi_st + 0x68) = uVar2 & val;
      if (*(int *)(hi_st + 0x5c) != 0) {
        return (-(uint)(*(int *)(hi_st + 0x68) != 0) & 0xffffc000) + 0x7fff << ((byte)iVar1 & 0x1f);
      }
    }
    else {
      if (iVar1 == 0x16) {
        *(uint *)(hi_st + 0x58) = *(uint *)(hi_dev + 0x28) & val;
        return 0;
      }
      hi_write_reg_masked(iVar1,val);
    }
    return 0;
  }
  *(uint *)(hi_st + iVar1 * 4) = *(uint *)(hi_dev + 8) & val;
  return *(int *)(hi_st + iVar1 * 4);
}


/* ==== hi_find_pin_shift @ 0041a9d0 ==== */

int hi_find_pin_shift(void)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 1;
  iVar1 = 0;
  do {
    if ((uVar2 & *(uint *)(hi_dev + 8)) != 0) break;
    iVar1 = iVar1 + 1;
    uVar2 = uVar2 << 1;
  } while (iVar1 < 0x18);
  *(int *)(hi_st + 0x6c) = iVar1;
  *(undefined4 *)(hi_st + 0x70) = 1;
  return iVar1;
}


/* ==== hi_read_io @ 0041aa10 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int hi_read_io(int dev,ulong addr,ulong *out,int side)

{
  ulong uVar1;
  int iVar2;
  uint uVar3;
  int extraout_EAX;
  int iVar4;
  
  _hi_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  iVar2 = dev * 0x48;
  hi_dev = *(int *)(cur_dtype + 0x18) + iVar2;
  hi_st = *_hi_stslot;
  uVar1 = *(ulong *)(*(int *)(cur_dtype + 0x18) + 0x1c + iVar2);
  iVar4 = addr - uVar1;
  if (addr == uVar1) {
    iVar2 = 1;
  }
  else if (iVar4 == 1) {
    iVar2 = 3;
  }
  else {
    if (iVar4 != 3) {
      iVar4 = addr - *(ulong *)(hi_dev + 0x14);
      if (addr == *(ulong *)(hi_dev + 0x14)) {
        uVar3 = *(uint *)(hi_dev + 0x18);
        *out = *(uint *)(hi_st + 0x5c) & uVar3;
        return uVar3;
      }
      if (iVar4 == 2) {
        iVar2 = 0x19;
      }
      else {
        if (iVar4 != 4) {
          return iVar2;
        }
        iVar2 = 0x18;
      }
      uVar3 = *(uint *)(hi_st + iVar2 * 4) & *(uint *)(hi_dev + 8);
      *out = uVar3;
      return uVar3;
    }
    iVar2 = 2;
  }
  hi_status = *(int *)(cur_sim + 8) + dev * 8;
  _hi_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  hi_regflags = *(undefined4 *)(hi_status + 4);
  _DAT_004dbd9c = *(undefined4 *)(cur_dev + 0x40);
  hi_read_reg_core(iVar2,out,side);
  return extraout_EAX;
}


/* ==== hi_refresh_reg @ 0041ab20 ==== */

void __cdecl hi_refresh_reg(int reg)

{
  int iVar1;
  
  if (reg < *(int *)(*(int *)(hi_dev + 0x2c) + 0x28)) {
    *(uint *)(hi_regflags + reg * 4) = *(uint *)(hi_regflags + reg * 4) | 0xa0000;
    *(uint *)(hi_st + reg * 4) =
         *(uint *)(hi_st + reg * 4) &
         *(uint *)(*(int *)(*(int *)(hi_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c);
    iVar1 = reg * 0x1c + *(int *)(*(int *)(hi_dev + 0x2c) + 0x2c);
    if ((*(byte *)(iVar1 + 0x10) & 0x60) != 0) {
      mem_trace_fetch(*(int *)(hi_dev + 0x1c) + *(int *)(iVar1 + 8));
    }
    if ((*(uint *)(hi_regflags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write((hi_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
    }
  }
  return;
}


/* ==== hi_write_reg_masked @ 0041abe0 ==== */

void __cdecl hi_write_reg_masked(int reg,ulong val)

{
  uint uVar1;
  
  uVar1 = *(uint *)(*(int *)(*(int *)(hi_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c) & val;
  if (reg == 1) {
    *(uint *)(hi_st + 0x18) = *(uint *)(hi_st + 0x18) & 0xffffffe7;
    *(uint *)(hi_st + 0x18) = *(uint *)(hi_st + 0x18) | uVar1 & 0x18;
    *(uint *)(hi_regflags + 0x18) = *(uint *)(hi_regflags + 0x18) | 0xa0000;
  }
  else if (reg == 4) {
    *(uint *)(hi_st + 0xc) = *(uint *)(hi_st + 0xc) & 0xfffffffd;
    hi_refresh_reg(3);
  }
  *(uint *)(hi_st + reg * 4) = uVar1;
  *(uint *)(hi_regflags + reg * 4) = *(uint *)(hi_regflags + reg * 4) | 0xa0000;
  if ((*(uint *)(hi_regflags + reg * 4) & 0x1800000) != 0) {
    io_out_periph_write((hi_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
  }
  return;
}


/* ==== hi_read_reg_core @ 0041acb0 ==== */

void __cdecl hi_read_reg_core(int reg,ulong *out,int side)

{
  *out = *(ulong *)(hi_st + reg * 4);
  if ((reg == 2) && (side != 0)) {
    *(uint *)(hi_st + 0xc) = *(uint *)(hi_st + 0xc) & 0xfffffffe;
    if ((*(uint *)(hi_st + 0x18) & 2) != 0) {
      hi_set_reg(6,*(uint *)(hi_st + 0x18) | 4);
    }
  }
  return;
}


/* ==== hi_reset_state @ 0041ad00 ==== */

void __cdecl hi_reset_state(int full)

{
  hi_set_reg(3,2);
  if (full != 0) {
    hi_set_reg(1,0);
    *(undefined4 *)(hi_st + 0x5c) = 0;
    *(undefined4 *)(hi_st + 0x60) = 0;
    *(undefined4 *)(hi_st + 100) = 0;
  }
  hi_set_reg(0,(*(uint *)(hi_dev + 0x20) | 4) >> 1);
  hi_set_reg(5,0);
  hi_set_reg(6,6);
  hi_set_reg(7,0xf);
  *(undefined4 *)(hi_st + 0x40) = 0;
  *(undefined4 *)(hi_st + 0x44) = 0;
  *(undefined4 *)(hi_st + 0x3c) = 0;
  *(undefined4 *)(hi_st + 0x74) = 0;
  *(undefined4 *)(hi_st + 0x38) = 0;
  *(undefined4 *)(hi_st + 0x48) = 0;
  return;
}


/* ==== hi_clock_a @ 0041adb0 ==== */

void __cdecl hi_clock_a(int dev,int feed_input)

{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  byte bVar5;
  uint uVar6;
  ulong val;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  int local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  ulong local_28 [2];
  uint local_20;
  
  local_60 = 0;
  if (hi_st[0x17] == 0) {
    if (hi_st[0x15] != 0) {
      hi_st[0x15] = 0;
      *hi_status = *hi_status & 0xfffffffe;
      hi_reset_state(0);
    }
    goto LAB_0041b6a8;
  }
  if (hi_st[0x1c] == 0) {
    local_68 = hi_find_pin_shift();
  }
  else {
    local_68 = hi_st[0x1b];
  }
  bVar5 = (byte)local_68;
  local_5c = 0xff << (bVar5 & 0x1f);
  local_38 = 0x2000 << (bVar5 & 0x1f);
  uVar7 = 0x800 << (bVar5 & 0x1f);
  local_40 = ~local_5c;
  local_4c = 0x1000 << (bVar5 & 0x1f);
  uVar9 = 0x4000 << (bVar5 & 0x1f);
  uVar8 = 0x700 << (bVar5 & 0x1f) | uVar7 | local_4c | uVar9;
  local_30 = *(uint *)(hi_dev + 8);
  local_50 = ~local_30;
  local_44 = (uint)(hi_st[0x1a] != 0);
  hi_pins = (uint *)(*(int *)(cur_dev + 0x18) + *(int *)(hi_dev + 4) * 0x128);
  ssi_pins = (uint *)(*(int *)(cur_dev + 0x18) + 0x94 + *(int *)(hi_dev + 4) * 0x128);
  local_6c = hi_pins[2] & local_5c;
  local_48 = hi_st[5];
  uVar6 = hi_st[6];
  local_2c = uVar6 & 0x40;
  local_64 = uVar6 & 0x80;
  if (feed_input != 0) {
    if (hi_st[0x15] == 0) {
      *hi_status = *hi_status | 1;
      hi_st[0x15] = hi_st[0x17];
      hi_pins[2] = hi_pins[2] & local_50;
      if (local_44 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = hi_pins[2] & uVar9;
      }
      hi_pins[2] = hi_pins[2] | local_38 | uVar3;
      hi_pins[3] = hi_pins[3] & local_50;
      if (local_44 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = hi_pins[3] & uVar9;
      }
      local_60 = 1;
      hi_pins[3] = hi_pins[3] | local_38 | uVar3;
    }
    iVar4 = io_in_pin_read(dev,local_28);
    if (iVar4 != 0) {
      local_70 = local_20;
      local_20 = local_20 << ((byte)local_68 & 0x1f);
      *hi_pins = *hi_pins & local_50;
      if (local_44 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = uVar9 & *hi_pins;
      }
      *hi_pins = *hi_pins | local_20 | uVar3;
      hi_pins[1] = hi_pins[1] & local_50;
      if (((local_20 & (uVar7 | local_4c)) == 0) && ((local_20 & uVar9) != 0)) {
        uVar8 = local_5c | uVar8;
      }
      hi_pins[1] = hi_pins[1] | uVar8;
    }
  }
  uVar8 = local_30 & *hi_pins;
  bVar5 = (byte)local_68;
  uVar3 = (int)uVar8 >> (bVar5 + 8 & 0x1f) & 7;
  local_3c = uVar9 & uVar8;
  if ((local_3c != 0) || (local_44 = 1, (*ssi_pins & uVar9) == 0)) {
    local_44 = 0;
  }
  if ((local_3c == 0) || (local_54 = 1, (*ssi_pins & uVar9) != 0)) {
    local_54 = 0;
  }
  local_58 = local_4c & uVar8;
  if ((local_58 == 0) || ((*ssi_pins & local_4c) != 0)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  local_34 = uVar7 & uVar8;
  if (local_58 == 0) {
LAB_0041b0a4:
    if ((*ssi_pins & local_4c) == 0) {
LAB_0041b0ba:
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    if (local_34 == 0) {
      if (bVar2) {
        if (uVar3 == 7) {
          hi_st[6] = hi_st[6] & 0xfffffffd;
          hi_refresh_reg(6);
          uVar6 = hi_st[6];
        }
      }
      else if (bVar1) {
        local_70 = (local_5c & uVar8) >> (bVar5 & 0x1f);
        hi_write_reg(dev,*(int *)(&hi_cmd_reg_tab + uVar3 * 4),&local_70);
        uVar6 = hi_st[6];
        hi_pins[3] = hi_pins[3] & local_40;
        goto LAB_0041b24e;
      }
      goto LAB_0041b24a;
    }
    if (!bVar2) {
      if (bVar1) {
        hi_pins[3] = hi_pins[3] & local_40;
      }
      goto LAB_0041b24a;
    }
    switch(uVar3) {
    case 0:
      local_70 = local_48;
      hi_regflags[5] = hi_regflags[5] | 0x50000;
      break;
    case 1:
      local_70 = *hi_st;
      *hi_regflags = *hi_regflags | 0x50000;
      break;
    case 2:
      uVar6 = uVar6 ^ (hi_st[1] ^ uVar6) & 0x18;
      hi_regflags[6] = hi_regflags[6] | 0x50000;
      local_70 = uVar6;
      break;
    case 3:
      local_70 = hi_st[7];
      hi_regflags[7] = hi_regflags[7] | 0x50000;
      break;
    case 4:
    case 5:
      local_70 = hi_st[8];
      hi_regflags[8] = hi_regflags[8] | 0x50000;
      break;
    case 6:
      local_70 = hi_st[10];
      hi_regflags[10] = hi_regflags[10] | 0x50000;
      break;
    case 7:
      local_70 = hi_st[9];
      uVar6 = uVar6 & 0xfffffffe;
      hi_regflags[9] = hi_regflags[9] | 0x50000;
    }
    local_6c = local_70 << (bVar5 & 0x1f);
    hi_pins[3] = hi_pins[3] | local_5c;
  }
  else {
    if (bVar1) {
      if (local_58 == 0) goto LAB_0041b0a4;
      goto LAB_0041b0ba;
    }
LAB_0041b24a:
    bVar5 = (byte)local_68;
  }
LAB_0041b24e:
  uVar8 = local_2c;
  if (local_2c == 0) {
LAB_0041b26e:
    if (local_58 != 0) {
LAB_0041b27a:
      if (((hi_st[3] & 2) == 0) && ((uVar6 & 1) == 0)) {
        local_2c = hi_st[4];
        hi_regflags[4] = hi_regflags[4] | 0x50000;
        hi_st[8] = local_2c >> 0x10 & 0xff;
        hi_st[10] = local_2c >> 8 & 0xff;
        hi_st[9] = local_2c & 0xff;
        hi_refresh_reg(8);
        hi_refresh_reg(10);
        hi_refresh_reg(9);
        hi_set_reg(3,hi_st[3] | 2);
        uVar6 = uVar6 | 1;
      }
    }
  }
  else {
    if ((local_3c != 0) && (local_58 != 0)) goto LAB_0041b27a;
    if (local_2c == 0) goto LAB_0041b26e;
  }
  if ((((feed_input != 0) && ((uVar6 & 2) == 0)) && ((hi_st[3] & 1) == 0)) && (hi_st[0x12] != 0)) {
    hi_st[2] = hi_st[0x1e];
    hi_st[0x12] = 0;
    hi_refresh_reg(2);
    uVar6 = uVar6 | 2;
    hi_regflags[0xb] = hi_regflags[0xb] | 0x50000;
    hi_regflags[0xc] = hi_regflags[0xc] | 0x50000;
    hi_st[3] = hi_st[3] | 1;
    hi_refresh_reg(3);
  }
  uVar7 = local_64;
  if (uVar8 == 0) {
    if ((((local_48 & 1) == 0) || ((uVar6 & 1) == 0)) &&
       (((uVar6 & 2) == 0 || ((local_48 & 2) == 0)))) {
      if (local_64 == 0) goto LAB_0041b5e9;
      uVar6 = uVar6 & 0xffffff7f;
      uVar7 = 0;
LAB_0041b3cb:
      local_60 = 1;
      if (uVar7 == 0) goto LAB_0041b5e9;
    }
    else if (local_64 == 0) {
      uVar7 = 1;
      uVar6 = uVar6 | 0x80;
      goto LAB_0041b3cb;
    }
    if (local_34 != 0) {
      if (local_44 == 0) {
        if (local_54 != 0) {
          hi_pins[3] = hi_pins[3] & local_40;
        }
      }
      else {
        local_6c = hi_st[7] << (bVar5 & 0x1f);
        hi_pins[3] = hi_pins[3] | local_5c;
      }
    }
LAB_0041b5e9:
    if (((uVar6 & 2) == 0) || ((hi_st[3] & 1) != 0)) goto LAB_0041b5f9;
    val = uVar6 | 4;
  }
  else {
    if (local_58 == 0) goto LAB_0041b5e9;
    if ((local_48 & 3) != 2) {
      if ((local_48 & 3) == 1) {
        if (local_44 == 0) {
          if (local_54 != 0) {
            hi_pins[3] = hi_pins[3] & local_40;
            if (hi_st[0xe] == 3) {
              uVar6 = uVar6 & 0xfffffffe;
              hi_st[0xe] = (int)local_48 >> 5 & 3;
            }
            else {
              hi_st[0xe] = hi_st[0xe] + 1;
            }
          }
        }
        else {
          if (hi_st[0xe] == 3) {
            iVar4 = 9;
          }
          else {
            iVar4 = (-(uint)(hi_st[0xe] != 2) & 0xfffffffe) + 10;
          }
          local_6c = hi_st[iVar4] << (bVar5 & 0x1f);
          local_60 = 1;
          hi_regflags[iVar4] = hi_regflags[iVar4] | 0x50000;
          uVar6 = uVar6 & 0xffffff7f;
          hi_pins[3] = hi_pins[3] | local_5c;
          uVar7 = 0;
        }
        if (local_3c != 0) {
          uVar8 = uVar6 & 1;
          goto LAB_0041b5d5;
        }
      }
      goto LAB_0041b5e9;
    }
    if (local_44 == 0) {
      if (local_54 != 0) {
        if (hi_st[0xe] == 3) {
          iVar4 = 0xc;
        }
        else {
          iVar4 = (-(uint)(hi_st[0xe] != 2) & 0xfffffffe) + 0xd;
        }
        hi_st[iVar4] = (local_5c & *hi_pins) >> (bVar5 & 0x1f);
        hi_refresh_reg(iVar4);
        uVar7 = local_64;
        if (hi_st[0xe] == 3) {
          uVar6 = uVar6 & 0xfffffffd;
          hi_st[0xe] = (int)local_48 >> 5 & 3;
          hi_st[0x12] = 1;
          hi_st[0x1e] = (hi_st[0xd] | hi_st[0xb] << 8) << 8 | hi_st[0xc];
        }
        else {
          hi_st[0xe] = hi_st[0xe] + 1;
        }
      }
    }
    else {
      uVar6 = uVar6 & 0xffffff7f;
      uVar7 = 0;
    }
    uVar8 = local_54;
    if ((uVar6 & 2) != 0) {
LAB_0041b5d5:
      if (uVar8 != 0) {
        uVar6 = uVar6 | 0x80;
        local_60 = 1;
        uVar7 = 1;
      }
      goto LAB_0041b5e9;
    }
LAB_0041b5f9:
    val = uVar6 & 0xfffffffb;
  }
  if (val != hi_st[6]) {
    hi_set_reg(6,val);
  }
  if (uVar7 == 0) {
    local_6c = local_6c | local_38;
  }
  hi_pins[2] = hi_pins[2] & local_50;
  hi_pins[2] = hi_pins[2] | local_6c;
  if ((local_60 != 0) || (local_6c != (ssi_pins[2] & local_30))) {
    local_6c = local_6c >> (bVar5 & 0x1f);
    io_out_pin_write(dev,&local_6c,-1);
  }
LAB_0041b6a8:
  if (((hi_st[0x16] == 0) || ((hi_st[1] & 2) == 0)) || ((hi_st[3] & 2) == 0)) {
    uVar6 = 0;
  }
  else {
    uVar6 = 1;
  }
  hi_st[0x11] = uVar6;
  if (((hi_st[0x16] == 0) || ((hi_st[1] & 1) == 0)) || ((hi_st[3] & 1) == 0)) {
    uVar6 = 0;
  }
  else {
    uVar6 = 1;
  }
  hi_st[0x10] = uVar6;
  if (feed_input != 0) {
    if (((hi_st[0x16] == 0) || ((hi_st[1] & 4) == 0)) || ((hi_st[3] & 4) == 0)) {
      uVar6 = 0;
    }
    else {
      uVar6 = 1;
    }
    hi_st[0xf] = uVar6;
    hi_st[0x1d] = hi_st[0x1d] | hi_st[0xf];
  }
  return;
}


/* ==== hi_clock_b @ 0041b760 ==== */

void __cdecl hi_clock_b(int dev,int feed_input)

{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  byte bVar5;
  ulong val;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  int local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  ulong local_28 [2];
  uint local_20;
  
  local_58 = 0;
  if (hi_st[0x17] == 0) {
    if (hi_st[0x15] != 0) {
      hi_st[0x15] = 0;
      *hi_status = *hi_status & 0xfffffffe;
      hi_reset_state(0);
    }
    goto LAB_0041bf73;
  }
  if (hi_st[0x1c] == 0) {
    local_68 = hi_find_pin_shift();
  }
  else {
    local_68 = hi_st[0x1b];
  }
  bVar5 = (byte)local_68;
  local_5c = 0xff << (bVar5 & 0x1f);
  local_38 = 0x2000 << (bVar5 & 0x1f);
  local_4c = ~local_5c;
  uVar7 = 0x1000 << (bVar5 & 0x1f);
  uVar6 = 0x800 << (bVar5 & 0x1f);
  local_54 = 0x8000 << (bVar5 & 0x1f);
  uVar9 = 0x4000 << (bVar5 & 0x1f);
  local_30 = *(uint *)(hi_dev + 8);
  uVar8 = 0x700 << (bVar5 & 0x1f) | uVar7 | uVar6 | local_54 | uVar9;
  local_48 = ~local_30;
  local_40 = (uint)(hi_st[0x1a] != 0);
  hi_pins = (uint *)(*(int *)(cur_dev + 0x18) + *(int *)(hi_dev + 4) * 0x128);
  ssi_pins = (uint *)(*(int *)(cur_dev + 0x18) + 0x94 + *(int *)(hi_dev + 4) * 0x128);
  local_64 = hi_pins[2] & local_5c;
  local_44 = hi_st[5];
  local_70 = hi_st[6];
  local_2c = local_70 & 0x40;
  local_60 = local_70 & 0x80;
  if (feed_input != 0) {
    if (hi_st[0x15] == 0) {
      *hi_status = *hi_status | 1;
      hi_st[0x15] = hi_st[0x17];
      hi_pins[2] = hi_pins[2] & local_48;
      if (local_40 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = hi_pins[2] & uVar9;
      }
      hi_pins[2] = hi_pins[2] | local_38 | uVar3;
      hi_pins[3] = hi_pins[3] & local_48;
      if (local_40 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = hi_pins[3] & uVar9;
      }
      local_58 = 1;
      hi_pins[3] = hi_pins[3] | local_38 | uVar3;
    }
    iVar4 = io_in_pin_read(dev,local_28);
    if (iVar4 != 0) {
      local_6c = local_20;
      local_20 = local_20 << ((byte)local_68 & 0x1f);
      *hi_pins = *hi_pins & local_48;
      if (local_40 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = uVar9 & *hi_pins;
      }
      *hi_pins = *hi_pins | local_20 | uVar3;
      hi_pins[1] = hi_pins[1] & local_48;
      if (((local_20 & (uVar7 | local_54)) == 0) && ((local_20 & uVar9) != 0)) {
        uVar8 = local_5c | uVar8;
      }
      hi_pins[1] = hi_pins[1] | uVar8;
    }
  }
  uVar8 = local_30 & *hi_pins;
  bVar5 = (byte)local_68;
  uVar3 = (int)uVar8 >> (bVar5 + 8 & 0x1f) & 7;
  local_3c = uVar9 & uVar8;
  if ((local_3c != 0) || (local_40 = 1, (*ssi_pins & uVar9) == 0)) {
    local_40 = 0;
  }
  if ((local_3c == 0) || (local_50 = 1, (*ssi_pins & uVar9) != 0)) {
    local_50 = 0;
  }
  local_34 = uVar7 & uVar8;
  uVar6 = uVar6 & uVar8;
  if (((uVar8 & local_54) == 0) && ((local_34 == 0 || (uVar6 == 0)))) {
    bVar1 = false;
    local_54 = 0;
  }
  else {
    local_54 = 1;
    bVar1 = true;
  }
  if ((bVar1) && (hi_st[0x1f] == 0)) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  if ((bVar1) || (hi_st[0x1f] == 0)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  hi_st[0x1f] = local_54;
  if ((local_54 == 0) || (bVar2)) {
    if (local_34 == 0) {
      if (bVar1) {
        if (uVar3 == 7) {
          hi_st[6] = hi_st[6] & 0xfffffffd;
          hi_refresh_reg(6);
          local_70 = hi_st[6];
        }
      }
      else if (bVar2) {
        local_6c = (local_5c & uVar8) >> (bVar5 & 0x1f);
        hi_write_reg(dev,*(int *)(&DAT_004ba798 + uVar3 * 4),&local_6c);
        local_70 = hi_st[6];
        goto LAB_0041baf4;
      }
    }
    else if (uVar6 == 0) {
      if (bVar1) {
        switch(uVar3) {
        case 0:
          local_6c = local_44;
          hi_regflags[5] = hi_regflags[5] | 0x50000;
          break;
        case 1:
          local_6c = *hi_st;
          *hi_regflags = *hi_regflags | 0x50000;
          break;
        case 2:
          local_70 = local_70 ^ (hi_st[1] ^ local_70) & 0x18;
          hi_regflags[6] = hi_regflags[6] | 0x50000;
          local_6c = local_70;
          break;
        case 3:
          local_6c = hi_st[7];
          hi_regflags[7] = hi_regflags[7] | 0x50000;
          break;
        case 4:
        case 5:
          local_6c = hi_st[8];
          hi_regflags[8] = hi_regflags[8] | 0x50000;
          break;
        case 6:
          local_6c = hi_st[10];
          hi_regflags[10] = hi_regflags[10] | 0x50000;
          break;
        case 7:
          local_6c = hi_st[9];
          hi_regflags[9] = hi_regflags[9] | 0x50000;
          local_70 = local_70 & 0xfffffffe;
        }
        local_64 = local_6c << (bVar5 & 0x1f);
        hi_pins[3] = hi_pins[3] | local_5c;
      }
      else if (bVar2) {
        hi_pins[3] = hi_pins[3] & local_4c;
      }
    }
    else {
LAB_0041baf4:
      hi_pins[3] = hi_pins[3] & local_4c;
    }
  }
  uVar6 = local_2c;
  uVar8 = local_54;
  if (((((local_2c != 0) && (local_3c != 0)) && (local_54 != 0)) ||
      ((local_2c == 0 && (local_54 != 0)))) && (((hi_st[3] & 2) == 0 && ((local_70 & 1) == 0)))) {
    local_2c = hi_st[4];
    hi_regflags[4] = hi_regflags[4] | 0x50000;
    hi_st[8] = local_2c >> 0x10 & 0xff;
    hi_st[10] = local_2c >> 8 & 0xff;
    hi_st[9] = local_2c & 0xff;
    hi_refresh_reg(8);
    hi_refresh_reg(10);
    hi_refresh_reg(9);
    hi_set_reg(3,hi_st[3] | 2);
    local_70 = local_70 | 1;
  }
  if (((feed_input != 0) && ((local_70 & 2) == 0)) && (((hi_st[3] & 1) == 0 && (hi_st[0x12] != 0))))
  {
    hi_st[2] = hi_st[0x1e];
    hi_st[0x12] = 0;
    hi_refresh_reg(2);
    local_70 = local_70 | 2;
    hi_regflags[0xb] = hi_regflags[0xb] | 0x50000;
    hi_regflags[0xc] = hi_regflags[0xc] | 0x50000;
    hi_st[3] = hi_st[3] | 1;
    hi_refresh_reg(3);
  }
  bVar5 = (byte)local_68;
  uVar7 = local_60;
  if (uVar6 == 0) {
    if ((((local_44 & 1) == 0) || ((local_70 & 1) == 0)) &&
       (((local_70 & 2) == 0 || ((local_44 & 2) == 0)))) {
      if (local_60 == 0) goto LAB_0041bea6;
      local_70 = local_70 & 0xffffff7f;
      uVar7 = 0;
LAB_0041bc8a:
      local_58 = 1;
      if (uVar7 == 0) goto LAB_0041bea6;
    }
    else if (local_60 == 0) {
      uVar7 = 1;
      local_70 = local_70 | 0x80;
      goto LAB_0041bc8a;
    }
    if (local_34 != 0) {
      if (local_40 == 0) {
        if (local_50 != 0) {
          hi_pins[3] = hi_pins[3] & local_4c;
        }
      }
      else {
        local_64 = hi_st[7] << (bVar5 & 0x1f);
        hi_pins[3] = hi_pins[3] | local_5c;
      }
    }
LAB_0041bea6:
    if (((local_70 & 2) == 0) || ((hi_st[3] & 1) != 0)) goto LAB_0041bebb;
    val = local_70 | 4;
  }
  else {
    if (uVar8 == 0) goto LAB_0041bea6;
    if ((local_44 & 3) != 2) {
      if ((local_44 & 3) == 1) {
        if (local_40 == 0) {
          if (local_50 != 0) {
            hi_pins[3] = hi_pins[3] & local_4c;
            if (hi_st[0xe] == 3) {
              local_70 = local_70 & 0xfffffffe;
              hi_st[0xe] = (int)local_44 >> 5 & 3;
            }
            else {
              hi_st[0xe] = hi_st[0xe] + 1;
            }
          }
        }
        else {
          if (hi_st[0xe] == 3) {
            iVar4 = 9;
          }
          else {
            iVar4 = (-(uint)(hi_st[0xe] != 2) & 0xfffffffe) + 10;
          }
          local_58 = 1;
          local_64 = hi_st[iVar4] << (bVar5 & 0x1f);
          hi_regflags[iVar4] = hi_regflags[iVar4] | 0x50000;
          local_70 = local_70 & 0xffffff7f;
          hi_pins[3] = hi_pins[3] | local_5c;
          uVar7 = 0;
        }
        if (local_3c != 0) {
          uVar8 = local_70 & 1;
          goto LAB_0041be92;
        }
      }
      goto LAB_0041bea6;
    }
    if (local_40 == 0) {
      if (local_50 != 0) {
        if (hi_st[0xe] == 3) {
          iVar4 = 0xc;
        }
        else {
          iVar4 = (-(uint)(hi_st[0xe] != 2) & 0xfffffffe) + 0xd;
        }
        hi_st[iVar4] = (local_5c & *hi_pins) >> (bVar5 & 0x1f);
        hi_refresh_reg(iVar4);
        uVar7 = local_60;
        if (hi_st[0xe] == 3) {
          hi_st[0xe] = (int)local_44 >> 5 & 3;
          local_70 = local_70 & 0xfffffffd;
          hi_st[0x12] = 1;
          hi_st[0x1e] = (hi_st[0xd] | hi_st[0xb] << 8) << 8 | hi_st[0xc];
        }
        else {
          hi_st[0xe] = hi_st[0xe] + 1;
        }
      }
    }
    else {
      local_70 = local_70 & 0xffffff7f;
      uVar7 = 0;
    }
    uVar8 = local_50;
    if ((local_70 & 2) != 0) {
LAB_0041be92:
      if (uVar8 != 0) {
        local_70 = local_70 | 0x80;
        local_58 = 1;
        uVar7 = 1;
      }
      goto LAB_0041bea6;
    }
LAB_0041bebb:
    val = local_70 & 0xfffffffb;
  }
  if (val != hi_st[6]) {
    hi_set_reg(6,val);
  }
  if (uVar7 == 0) {
    local_64 = local_64 | local_38;
  }
  hi_pins[2] = hi_pins[2] & local_48;
  hi_pins[2] = hi_pins[2] | local_64;
  if ((local_58 != 0) || (local_64 != (ssi_pins[2] & local_30))) {
    local_64 = local_64 >> ((byte)local_68 & 0x1f);
    io_out_pin_write(dev,&local_64,-1);
  }
LAB_0041bf73:
  if (((hi_st[0x16] == 0) || ((hi_st[1] & 2) == 0)) || ((hi_st[3] & 2) == 0)) {
    uVar8 = 0;
  }
  else {
    uVar8 = 1;
  }
  hi_st[0x11] = uVar8;
  if (((hi_st[0x16] == 0) || ((hi_st[1] & 1) == 0)) || ((hi_st[3] & 1) == 0)) {
    uVar8 = 0;
  }
  else {
    uVar8 = 1;
  }
  hi_st[0x10] = uVar8;
  if (feed_input != 0) {
    if (((hi_st[0x16] == 0) || ((hi_st[1] & 4) == 0)) || ((hi_st[3] & 4) == 0)) {
      uVar8 = 0;
    }
    else {
      uVar8 = 1;
    }
    hi_st[0xf] = uVar8;
    hi_st[0x1d] = hi_st[0x1d] | hi_st[0xf];
  }
  return;
}


