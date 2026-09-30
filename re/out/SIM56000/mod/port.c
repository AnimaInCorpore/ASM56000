/* ==== port_read_reg @ 004159b0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int port_read_reg(int dev,int reg,ulong *out)

{
  _DAT_004dbd4c = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  port_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  port_regs = *_DAT_004dbd4c;
  port_read_pins(dev,reg,out,0);
  return 1;
}


/* ==== port_write_reg @ 00415a00 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int port_write_reg(int dev,int reg,ulong *val)

{
  _DAT_004dbd54 = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd50 = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  port_regflags = *(undefined4 *)(_DAT_004dbd54 + 4);
  _DAT_004dbd4c = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  port_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  port_regs = *_DAT_004dbd4c;
  port_write_pins(dev,reg,*val);
  port_refresh_reg(reg);
  return 1;
}


/* ==== port_reset @ 00415a90 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int port_reset(int dev,int full)

{
  int extraout_EAX;
  int iVar1;
  
  _DAT_004dbd54 = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd50 = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  port_regflags = *(undefined4 *)(_DAT_004dbd54 + 4);
  _DAT_004dbd4c = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  port_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  port_regs = *_DAT_004dbd4c;
  iVar1 = 0;
  if (full != 0) {
    port_reset_regs();
    iVar1 = extraout_EAX;
  }
  return iVar1;
}


/* ==== port_reset_regs @ 00415b10 ==== */

void port_reset_regs(void)

{
  port_regs[2] = 0;
  port_regs[1] = 0;
  *port_regs = 0;
  port_refresh_reg(0);
  port_refresh_reg(1);
  port_refresh_reg(2);
  return;
}


/* ==== port_write_io @ 00415b50 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int port_write_io(int dev,ulong addr,ulong val)

{
  ulong uVar1;
  int iVar2;
  
  uVar1 = *(ulong *)(*(int *)(cur_dtype + 0x18) + 0x1c + dev * 0x48);
  iVar2 = addr - uVar1;
  if (addr == uVar1) {
    iVar2 = 0;
  }
  else if (iVar2 == 2) {
    iVar2 = 1;
  }
  else {
    if (iVar2 != 4) {
      return 0;
    }
    iVar2 = 2;
  }
  _DAT_004dbd54 = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd50 = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  port_regflags = *(undefined4 *)(_DAT_004dbd54 + 4);
  _DAT_004dbd4c = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  port_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  port_regs = *_DAT_004dbd4c;
  port_write_pins(dev,iVar2,val);
  return 0;
}


/* ==== port_read_io @ 00415c00 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int port_read_io(int dev,ulong addr,ulong *out,int side)

{
  int iVar1;
  int extraout_EAX;
  
  iVar1 = addr - *(int *)(*(int *)(cur_dtype + 0x18) + 0x1c + dev * 0x48);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else if (iVar1 == 2) {
    iVar1 = 1;
  }
  else {
    if (iVar1 + -4 != 0) {
      return iVar1 + -4;
    }
    iVar1 = 2;
  }
  _DAT_004dbd54 = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd50 = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  port_regflags = *(undefined4 *)(_DAT_004dbd54 + 4);
  _DAT_004dbd4c = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  port_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  port_regs = *_DAT_004dbd4c;
  port_read_pins(dev,iVar1,out,side);
  return extraout_EAX;
}


/* ==== port_write_io_c @ 00415cb0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int port_write_io_c(int dev,ulong addr,ulong val)

{
  ulong uVar1;
  int iVar2;
  
  uVar1 = *(ulong *)(*(int *)(cur_dtype + 0x18) + 0x1c + dev * 0x48);
  iVar2 = addr - uVar1;
  if (addr == uVar1) {
    iVar2 = 0;
  }
  else if (iVar2 == 1) {
    iVar2 = 1;
  }
  else {
    if (iVar2 != 2) {
      return 0;
    }
    iVar2 = 2;
  }
  _DAT_004dbd54 = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd50 = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  port_regflags = *(undefined4 *)(_DAT_004dbd54 + 4);
  _DAT_004dbd4c = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  port_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  port_regs = *_DAT_004dbd4c;
  port_write_pins(dev,iVar2,val);
  return 0;
}


/* ==== port_read_io_c @ 00415d60 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int port_read_io_c(int dev,ulong addr,ulong *out,int side)

{
  int iVar1;
  int extraout_EAX;
  
  iVar1 = addr - *(int *)(*(int *)(cur_dtype + 0x18) + 0x1c + dev * 0x48);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else if (iVar1 == 1) {
    iVar1 = 1;
  }
  else {
    if (iVar1 + -2 != 0) {
      return iVar1 + -2;
    }
    iVar1 = 2;
  }
  _DAT_004dbd54 = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd50 = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  port_regflags = *(undefined4 *)(_DAT_004dbd54 + 4);
  _DAT_004dbd4c = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  port_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  port_regs = *_DAT_004dbd4c;
  port_read_pins(dev,iVar1,out,side);
  return extraout_EAX;
}


/* ==== port_refresh_reg @ 00415e10 ==== */

void __cdecl port_refresh_reg(int reg)

{
  int iVar1;
  
  if (reg < *(int *)(*(int *)(port_dev + 0x2c) + 0x28)) {
    *(uint *)(port_regflags + reg * 4) = *(uint *)(port_regflags + reg * 4) | 0xa0000;
    *(uint *)(port_regs + reg * 4) =
         *(uint *)(port_regs + reg * 4) &
         *(uint *)(*(int *)(*(int *)(port_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c);
    iVar1 = reg * 0x1c + *(int *)(*(int *)(port_dev + 0x2c) + 0x2c);
    if ((*(byte *)(iVar1 + 0x10) & 0x60) != 0) {
      mem_trace_fetch(*(int *)(port_dev + 0x1c) + *(int *)(iVar1 + 8));
    }
    if ((*(uint *)(port_regflags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write((port_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
    }
  }
  return;
}


/* ==== port_write_pins @ 00415ed0 ==== */

void __cdecl port_write_pins(int dev,int reg,ulong val)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int local_c;
  uint uStack_4;
  
  uVar8 = 0;
  uVar7 = *(uint *)(*(int *)(*(int *)(port_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c);
  iVar1 = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  iVar2 = *(int *)(iVar1 + 4);
  iVar3 = *(int *)(*(int *)(*(int *)(iVar1 + 0x2c) + 0x2c) + 8 + reg * 0x1c);
  iVar1 = *(int *)(iVar1 + 0x1c);
  iVar9 = 0;
  if (0 < *(int *)(cur_dtype + 0x14)) {
    local_c = 0;
    iVar6 = cur_dtype;
    do {
      iVar4 = *(int *)(iVar6 + 0x18) + local_c;
      if ((*(int *)(iVar4 + 4) == iVar2) && (*(int *)(iVar4 + 0x18) != 0)) {
        uVar5 = (**(code **)(*(int *)(iVar4 + 0x2c) + 0xc))(iVar9,iVar3 + iVar1,val,1);
        uVar8 = uVar8 | uVar5;
        iVar6 = cur_dtype;
      }
      iVar9 = iVar9 + 1;
      local_c = local_c + 0x48;
    } while (iVar9 < *(int *)(iVar6 + 0x14));
  }
  iVar1 = *(int *)(cur_dev + 0x18) + iVar2 * 0x128;
  port_regs[reg] = uVar8;
  *(uint *)(port_regflags + reg * 4) = *(uint *)(port_regflags + reg * 4) | 0xa0000;
  uVar7 = uVar7 & ~*port_regs;
  if (uVar7 != 0) {
    uVar8 = port_regs[1] & uVar7;
    *(uint *)(iVar1 + 0xc) = ~uVar7 & *(uint *)(iVar1 + 0xc) | uVar8;
    *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) & ~uVar7;
    uStack_4 = port_regs[2] & uVar8;
    *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) | uStack_4;
    if (uVar8 != 0) {
      io_out_pin_write(dev,&uStack_4,0);
    }
    if ((*(uint *)(port_regflags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write((port_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
    }
  }
  return;
}


/* ==== port_read_pins @ 00416050 ==== */

void __cdecl port_read_pins(int dev,int reg,ulong *out,int fetch)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  ulong *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  ulong local_28 [2];
  uint local_20;
  
  puVar4 = out;
  if (reg != 2) {
    uVar11 = 0;
    iVar5 = *(int *)(cur_dtype + 0x18) + dev * 0x48;
    iVar2 = *(int *)(iVar5 + 4);
    iVar10 = 0;
    iVar3 = *(int *)(*(int *)(*(int *)(iVar5 + 0x2c) + 0x2c) + 8 + reg * 0x1c);
    iVar5 = *(int *)(iVar5 + 0x1c);
    if (0 < *(int *)(cur_dtype + 0x14)) {
      iVar8 = 0;
      iVar7 = cur_dtype;
      do {
        iVar6 = *(int *)(iVar7 + 0x18) + iVar8;
        if ((*(int *)(iVar6 + 4) == iVar2) && (*(int *)(iVar6 + 0x18) != 0)) {
          (**(code **)(*(int *)(iVar6 + 0x2c) + 8))(iVar10,iVar3 + iVar5,&reg,1);
          uVar11 = uVar11 | reg;
          iVar7 = cur_dtype;
        }
        iVar10 = iVar10 + 1;
        iVar8 = iVar8 + 0x48;
      } while (iVar10 < *(int *)(iVar7 + 0x14));
    }
    *out = uVar11;
    return;
  }
  uVar11 = *(uint *)(*(int *)(*(int *)(port_dev + 0x2c) + 0x2c) + 0x3c);
  uVar9 = (port_regs[1] | *port_regs) & uVar11;
  if (uVar9 == uVar11) {
    *out = port_regs[2];
    return;
  }
  *out = port_regs[2] & uVar9;
  puVar1 = (uint *)(*(int *)(cur_dev + 0x18) + *(int *)(port_dev + 4) * 0x128);
  if (fetch != 0) {
    iVar5 = io_in_pin_read(dev,local_28);
    if (iVar5 != 0) {
      puVar1[1] = uVar11;
      *puVar1 = local_20 & uVar11 | *puVar1 & ~uVar11;
    }
  }
  *puVar4 = *puVar4 | uVar11 & *puVar1 & ~uVar9;
  return;
}


