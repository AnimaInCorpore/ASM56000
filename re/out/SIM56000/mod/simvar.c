/* ==== simvar_read_reg @ 004155b0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int simvar_read_reg(int dev,int reg,ulong *out)

{
  switch(reg) {
  case 0:
    *out = *(ulong *)(cur_sim + 0x15c);
    return 1;
  case 1:
    *out = *(ulong *)(cur_sim + 0x160);
    return 1;
  case 2:
    *out = *(ulong *)(cur_sim + 0x164);
    return 1;
  case 3:
    *out = *(ulong *)(cur_sim + 0x168);
    return 1;
  case 4:
    *out = *(ulong *)(cur_dev + 0x20);
    return 1;
  case 5:
    *out = *(ulong *)(cur_sim + 0x1c);
    return 1;
  case 6:
    *out = *(ulong *)(cur_dev + 0x24);
    return 1;
  case 7:
    *out = *(ulong *)(cur_sim + 0x18);
    return 1;
  case 8:
    *out = *(ulong *)(*(int *)(cur_dev + 0x40) + 0xc);
  }
  return 1;
}


/* ==== simvar_write_reg @ 004156a0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int simvar_write_reg(int dev,int reg,ulong *val)

{
  uint uVar1;
  
  _DAT_004dbd3c = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd38 = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  simvar_regflags = *(undefined4 *)(_DAT_004dbd3c + 4);
  _DAT_004dbd34 = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  simvar_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  simvar_regs = *_DAT_004dbd34;
  DAT_004dbd24 = *(undefined4 *)(cur_dev + 0x40);
  uVar1 = val[1] << 0x18 | *val;
  *(uint *)(simvar_regs + reg * 4) = uVar1;
  switch(reg) {
  case 0:
    *(uint *)(cur_sim + 0x15c) = uVar1;
    simvar_refresh_reg(reg);
    return 1;
  case 1:
    *(uint *)(cur_sim + 0x160) = uVar1;
    simvar_refresh_reg(reg);
    return 1;
  case 2:
    *(uint *)(cur_sim + 0x164) = uVar1;
    simvar_refresh_reg(reg);
    return 1;
  case 3:
    *(uint *)(cur_sim + 0x168) = uVar1;
    break;
  case 4:
    *(uint *)(cur_dev + 0x20) = uVar1;
    simvar_refresh_reg(reg);
    return 1;
  case 6:
    *(uint *)(cur_dev + 0x24) = uVar1;
    simvar_refresh_reg(reg);
    return 1;
  }
  simvar_refresh_reg(reg);
  return 1;
}


/* ==== simvar_write_io @ 004157f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int simvar_write_io(int dev,ulong addr,ulong val)

{
  int *extraout_EAX;
  int *piVar1;
  
  _DAT_004dbd3c = *(int *)(cur_sim + 8) + dev * 8;
  _DAT_004dbd38 = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  simvar_regflags = *(undefined4 *)(_DAT_004dbd3c + 4);
  _DAT_004dbd34 = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  simvar_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  simvar_regs = (int *)*_DAT_004dbd34;
  DAT_004dbd24 = *(int *)(cur_dev + 0x40);
  simvar_refresh_reg(4);
  *(uint *)(DAT_004dbd24 + 4) = *(uint *)(DAT_004dbd24 + 4) ^ 1;
  if (*(int *)(cur_dev + 0x24) != simvar_regs[6]) {
    simvar_regs[6] = *(int *)(cur_dev + 0x24);
    simvar_refresh_reg(6);
  }
  if (*(int *)(cur_sim + 0x15c) != *simvar_regs) {
    *simvar_regs = *(int *)(cur_sim + 0x15c);
    simvar_refresh_reg(0);
  }
  if (*(int *)(cur_sim + 0x160) != simvar_regs[1]) {
    simvar_regs[1] = *(int *)(cur_sim + 0x160);
    simvar_refresh_reg(1);
  }
  if (*(int *)(cur_sim + 0x164) != simvar_regs[2]) {
    simvar_regs[2] = *(int *)(cur_sim + 0x164);
    simvar_refresh_reg(2);
  }
  piVar1 = simvar_regs;
  if (*(int *)(cur_sim + 0x168) != simvar_regs[3]) {
    simvar_regs[3] = *(int *)(cur_sim + 0x168);
    simvar_refresh_reg(3);
    piVar1 = extraout_EAX;
  }
  return (int)piVar1;
}


/* ==== simvar_refresh_reg @ 00415930 ==== */

void __cdecl simvar_refresh_reg(int reg)

{
  if (reg < *(int *)(*(int *)(simvar_dev + 0x2c) + 0x28)) {
    *(uint *)(simvar_regs + reg * 4) =
         *(uint *)(simvar_regs + reg * 4) &
         *(uint *)(*(int *)(*(int *)(simvar_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c);
    *(uint *)(simvar_regflags + reg * 4) = *(uint *)(simvar_regflags + reg * 4) | 0xa0000;
    if ((*(uint *)(simvar_regflags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write((simvar_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
    }
  }
  return;
}


