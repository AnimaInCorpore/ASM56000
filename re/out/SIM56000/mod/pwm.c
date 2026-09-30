/* ==== iofmt_idle_format @ 00413f70 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int iofmt_idle_format(int arg1,long *word,char *out)

{
  if (*word == -2) {
    *(undefined4 *)out = DAT_004b6ec4;
    out[4] = DAT_004b6ec8;
    return 1;
  }
  return 0;
}


/* ==== pwm_write_reg @ 00413fa0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pwm_write_reg(int dev,int reg,ulong *val)

{
  int iVar1;
  
  pwm_status = *(int *)(cur_sim + 8) + dev * 8;
  _pwm_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  pwm_regflags = *(undefined4 *)(pwm_status + 4);
  _pwm_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  pwm_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  pwm_regs = *_pwm_stslot;
  iVar1 = *(int *)(pwm_dev + 0x2c);
  pwm_st = pwm_regs;
  if ((reg < *(int *)(iVar1 + 0x28)) &&
     ((*(byte *)(*(int *)(iVar1 + 0x2c) + 0x10 + reg * 0x1c) & 0x40) != 0)) {
    pwm_write_reg_core(reg,*val,1);
    pwm_refresh_reg(reg);
    return 1;
  }
  if (reg < *(int *)(iVar1 + 0x24)) {
    *(ulong *)(pwm_regs + reg * 4) = *val;
  }
  pwm_refresh_reg(reg);
  return 1;
}


/* ==== pwm_tick @ 00414070 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void pwm_tick(int dev)

{
  pwm_status = *(int *)(cur_sim + 8) + dev * 8;
  _pwm_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  pwm_regflags = *(undefined4 *)(pwm_status + 4);
  _pwm_stslot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  pwm_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  pwm_regs = *_pwm_stslot;
  pwm_chipflags = *(int *)(cur_dev + 0x40);
  pwm_st = pwm_regs;
  if ((*(int *)(pwm_chipflags + 0xc) == 0) && (*(int *)(pwm_chipflags + 8) != 1)) {
    pwm_clock(dev);
  }
  return;
}


/* ==== pwm_write_io @ 00414100 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pwm_write_io(int dev,ulong addr,ulong val)

{
  int iVar1;
  
  pwm_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  iVar1 = addr - *(int *)(pwm_dev + 0x1c);
  if ((iVar1 < 0) || (8 < iVar1)) {
    if (addr != 0xffff) {
      return 0;
    }
    iVar1 = 9;
  }
  else {
    iVar1 = *(int *)(&DAT_004b6b00 + iVar1 * 4);
  }
  pwm_status = *(int *)(cur_sim + 8) + dev * 8;
  _pwm_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  pwm_regflags = *(undefined4 *)(pwm_status + 4);
  _pwm_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  pwm_regs = *_pwm_stslot;
  pwm_st = pwm_regs;
  if (iVar1 != 9) {
    pwm_write_reg_core(iVar1,val,0);
    return 0;
  }
  *(uint *)(pwm_regs + 0x24) =
       (uint)((*(uint *)(*(int *)(cur_dtype + 0x18) + 0x28 + dev * 0x48) & val) != 0);
  return 0;
}


/* ==== pwm_read_io @ 004141d0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pwm_read_io(int dev,ulong addr,ulong *out,int side)

{
  uint uVar1;
  
  _pwm_stslot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  pwm_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  pwm_regs = *_pwm_stslot;
  uVar1 = addr - *(int *)(pwm_dev + 0x1c);
  pwm_st = pwm_regs;
  if (uVar1 < 9) {
    pwm_status = *(int *)(cur_sim + 8) + dev * 8;
    _pwm_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
    pwm_regflags = *(undefined4 *)(pwm_status + 4);
    uVar1 = pwm_read_reg_core(*(int *)(&DAT_004b6b00 + uVar1 * 4),out,side);
  }
  return uVar1;
}


/* ==== pwm_reset @ 00414270 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pwm_reset(int dev)

{
  int extraout_EAX;
  
  pwm_status = *(int *)(cur_sim + 8) + dev * 8;
  _pwm_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  pwm_regflags = *(undefined4 *)(pwm_status + 4);
  _pwm_stslot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  pwm_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  pwm_regs = *_pwm_stslot;
  pwm_st = pwm_regs;
  pwm_reset_regs();
  return extraout_EAX;
}


/* ==== pwm_reset_regs @ 004142f0 ==== */

void pwm_reset_regs(void)

{
  uint *puVar1;
  int iVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  char cVar6;
  
  pwm_set_reg(0,0);
  pwm_set_reg(1,0);
  pwm_set_reg(2,0);
  pwm_set_reg(3,0x1c00);
  pwm_set_reg(4,0);
  pwm_set_reg(5,0);
  pwm_set_reg(6,0);
  pwm_set_reg(7,0x3000);
  pwm_set_reg(8,0);
  *(undefined4 *)(pwm_st + 0x24) = 0;
  *(undefined4 *)(pwm_st + 0x17c) = 0;
  *(undefined4 *)(pwm_st + 0x168) = 0;
  *(undefined4 *)(pwm_st + 0x164) = 0;
  *(undefined4 *)(pwm_st + 0x178) = 1;
  bVar4 = 0;
  *(undefined4 *)(pwm_st + 0x174) = 1;
  iVar5 = 0;
  do {
    iVar2 = pwm_st + 0x28 + iVar5;
    iVar5 = iVar5 + 0x3c;
    *(undefined4 *)(iVar2 + 0x28) = 0;
    *(int *)(iVar2 + 0x2c) = 0x20 << (bVar4 & 0x1f);
    *(int *)(iVar2 + 0x30) = 0x100 << (bVar4 & 0x1f);
    bVar3 = bVar4 & 0x1f;
    bVar4 = bVar4 + 1;
    *(int *)(iVar2 + 0x34) = 4 << bVar3;
  } while (iVar5 < 0xb4);
  cVar6 = '\x03';
  iVar5 = 0xb4;
  do {
    iVar2 = pwm_st;
    *(undefined4 *)(pwm_st + 0x50 + iVar5) = 1;
    *(undefined4 *)(iVar2 + 0x5c + iVar5) = 0x1000;
    iVar2 = iVar2 + iVar5;
    bVar4 = cVar6 - 3;
    iVar5 = iVar5 + 0x3c;
    cVar6 = cVar6 + '\x01';
    *(int *)(iVar2 + 0x54) = 0x2000 << (bVar4 & 0x1f);
  } while (iVar5 < 300);
  iVar5 = 0;
  do {
    iVar2 = pwm_st;
    *(undefined4 *)(pwm_st + 0x28 + iVar5) = 0;
    *(undefined4 *)(iVar2 + 0x2c + iVar5) = 0;
    *(undefined4 *)(iVar2 + 0x38 + iVar5) = 0;
    iVar2 = iVar2 + 0x28 + iVar5;
    iVar5 = iVar5 + 0x3c;
    *(undefined4 *)(iVar2 + 0x18) = 0xffffffff;
    *(undefined4 *)(iVar2 + 0x1c) = 1;
    *(undefined4 *)(iVar2 + 0x20) = 0;
    *(undefined4 *)(iVar2 + 0x24) = 0;
    *(undefined4 *)(iVar2 + 0x38) = 0;
  } while (iVar5 < 300);
  *pwm_status = 0x26;
  *(uint *)(*(int *)(cur_dev + 0x18) + 0x5d4) = *(uint *)(*(int *)(cur_dev + 0x18) + 0x5d4) | 0x67e0
  ;
  puVar1 = (uint *)(*(int *)(cur_dev + 0x18) + 0x5d0);
  *puVar1 = *puVar1 | 0x67e0;
  return;
}


/* ==== pwm_set_reg @ 004144a0 ==== */

void __cdecl pwm_set_reg(int reg,ulong val)

{
  *(ulong *)(pwm_regs + reg * 4) = val;
  pwm_refresh_reg(reg);
  return;
}


/* ==== pwm_int_pending @ 004144c0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long pwm_int_pending(int dev)

{
  int iVar1;
  int *piVar2;
  
  pwm_status = *(int *)(cur_sim + 8) + dev * 8;
  _pwm_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  pwm_regflags = *(undefined4 *)(pwm_status + 4);
  _pwm_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  pwm_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  pwm_regs = *_pwm_stslot;
  pwm_st = pwm_regs;
  if (*(int *)(pwm_regs + 0x24) == 0) {
    return -1;
  }
  if (*(int *)(pwm_regs + 0x17c) != 0) {
    return *(int *)(pwm_dev + 0x20) + 10;
  }
  iVar1 = 0;
  piVar2 = (int *)(pwm_regs + 0x4c);
  do {
    if (*piVar2 != 0) {
      return *(int *)(pwm_dev + 0x20) + iVar1 * 2;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 0xf;
  } while (iVar1 < 5);
  return -1;
}


/* ==== pwm_int_ack @ 00414570 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pwm_int_ack(int dev,long vec)

{
  int iVar1;
  int iVar2;
  
  pwm_status = *(int *)(cur_sim + 8) + dev * 8;
  _pwm_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  pwm_regflags = *(undefined4 *)(pwm_status + 4);
  _pwm_stslot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  pwm_dev = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  pwm_regs = *_pwm_stslot;
  iVar1 = vec - *(int *)(pwm_dev + 0x20);
  pwm_st = pwm_regs;
  switch(iVar1) {
  case 0:
  case 2:
  case 4:
  case 6:
  case 8:
    iVar2 = iVar1 / 2;
    iVar1 = iVar2 * 3;
    *(undefined4 *)(pwm_regs + 0x4c + iVar2 * 0x3c) = 0;
    break;
  case 10:
    *(undefined4 *)(pwm_regs + 0x17c) = 0;
    return iVar1;
  }
  return iVar1;
}


/* ==== pwm_write_reg_core @ 00414640 ==== */

void __cdecl pwm_write_reg_core(int reg,ulong val)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  int iVar6;
  
  uVar3 = val & *(uint *)(*(int *)(*(int *)(pwm_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c);
  switch(reg) {
  case 0:
  case 1:
  case 2:
    uVar2 = uVar3 >> 8;
    *(uint *)(pwm_st + 0x38 + reg * 0x3c) = uVar3 >> 0x17 & 1;
    if ((uVar2 & 0x8000) != 0) {
      uVar2 = ~uVar2 + 1 & 0xffff;
    }
    *(uint *)(pwm_st + 0x2c + reg * 0x3c) = uVar2;
    pwm_set_reg(3,~*(uint *)(&DAT_004b68a0 + reg * 4) & *(uint *)(pwm_st + 0xc));
    *(uint *)(pwm_regs + reg * 4) = uVar3;
    break;
  case 3:
    uVar3 = uVar3 ^ (uVar3 ^ *(uint *)(pwm_st + 0xc)) & 0xfc00;
    *(uint *)(pwm_st + 0xc) = uVar3;
    *(undefined4 *)(pwm_st + 0x174) = *(undefined4 *)(&pwm_prescale_tab + (uVar3 >> 4 & 7) * 4);
    break;
  case 4:
    iVar6 = 0;
    iVar5 = 0;
    do {
      *(uint *)(pwm_st + 0x44 + iVar6) =
           (uint)((*(uint *)((int)&DAT_004b6858 + iVar5) & uVar3) == 0);
      if ((uVar3 & *(uint *)((int)&DAT_004b6870 + iVar5)) == 0) {
        pwm_set_reg(3,~*(uint *)((int)&DAT_004b68b8 + iVar5) & *(uint *)(pwm_st + 0xc));
      }
      else {
        puVar1 = (undefined4 *)(pwm_st + 0x28 + iVar6);
        if (*(int *)(pwm_st + 0x28 + iVar6) == 0) {
          if (*(int *)(pwm_st + 0x44 + iVar6) == 0) {
            pwm_chan_reload(puVar1);
          }
          else {
            *puVar1 = 2;
          }
        }
      }
      iVar5 = iVar5 + 4;
      iVar6 = iVar6 + 0x3c;
    } while (iVar5 < 0xc);
    *(uint *)(pwm_st + 0x10) = uVar3;
    break;
  case 5:
  case 6:
    *(uint *)(pwm_st + -0x4c + reg * 0x3c) = uVar3 >> 8 & 0x7fff;
    pwm_set_reg(7,~*(uint *)(&DAT_004b6898 + reg * 4) & *(uint *)(pwm_st + 0x1c));
    *(uint *)(pwm_regs + reg * 4) = uVar3;
    break;
  case 7:
    uVar3 = uVar3 ^ (uVar3 ^ *(uint *)(pwm_st + 0x1c)) & 0xf000;
    *(uint *)(pwm_st + 0x1c) = uVar3;
    *(undefined4 *)(pwm_st + 0x178) = *(undefined4 *)(&pwm_prescale_tab + (uVar3 >> 4 & 7) * 4);
    break;
  case 8:
    iVar5 = 0xb4;
    puVar4 = &DAT_004b68c4;
    iVar6 = 0;
    do {
      *(uint *)(pwm_st + 0x44 + iVar5) =
           (uint)((*(uint *)((int)&DAT_004b6864 + iVar6) & uVar3) == 0);
      if ((uVar3 & *(uint *)((int)&DAT_004b687c + iVar6)) == 0) {
        pwm_set_reg(7,*(uint *)(pwm_st + 0x1c) & ~*puVar4);
      }
      else {
        puVar1 = (undefined4 *)(pwm_st + 0x28 + iVar5);
        if (*(int *)(pwm_st + 0x28 + iVar5) == 0) {
          if (*(int *)(pwm_st + 0x44 + iVar5) == 0) {
            pwm_chan_reload(puVar1);
          }
          else {
            *puVar1 = 2;
          }
        }
      }
      iVar6 = iVar6 + 4;
      puVar4 = puVar4 + 1;
      iVar5 = iVar5 + 0x3c;
    } while (iVar6 < 8);
    *(uint *)(pwm_st + 0x20) = uVar3;
    break;
  default:
    *(uint *)(pwm_regs + reg * 4) = uVar3;
  }
  *(uint *)(pwm_regflags + reg * 4) = *(uint *)(pwm_regflags + reg * 4) | 0xa0000;
  if ((*(uint *)(pwm_regflags + reg * 4) & 0x1800000) != 0) {
    io_out_periph_write((pwm_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
  }
  return;
}


/* ==== pwm_chan_reload @ 00414920 ==== */

void __cdecl pwm_chan_reload(void *chan)

{
  int iVar1;
  
  iVar1 = *(int *)(pwm_st + 0x174 + *(int *)((int)chan + 0x28) * 4);
  *(undefined4 *)chan = 1;
  *(uint *)((int)chan + 0xc) = ~(iVar1 - 1U) & *(uint *)((int)chan + 4);
  *(undefined4 *)((int)chan + 0x14) = *(undefined4 *)((int)chan + 0x10);
  *(undefined4 *)((int)chan + 8) = 0;
  *(undefined4 *)((int)chan + 0x20) = 0;
  return;
}


/* ==== pwm_refresh_reg @ 00414960 ==== */

void __cdecl pwm_refresh_reg(int reg)

{
  int iVar1;
  
  if (reg < *(int *)(*(int *)(pwm_dev + 0x2c) + 0x28)) {
    *(uint *)(pwm_regflags + reg * 4) = *(uint *)(pwm_regflags + reg * 4) | 0xa0000;
    *(uint *)(pwm_regs + reg * 4) =
         *(uint *)(pwm_regs + reg * 4) &
         *(uint *)(*(int *)(*(int *)(pwm_dev + 0x2c) + 0x2c) + 4 + reg * 0x1c);
    iVar1 = reg * 0x1c + *(int *)(*(int *)(pwm_dev + 0x2c) + 0x2c);
    if ((*(byte *)(iVar1 + 0x10) & 0x60) != 0) {
      mem_trace_fetch(*(int *)(pwm_dev + 0x1c) + *(int *)(iVar1 + 8));
    }
    if ((*(uint *)(pwm_regflags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write((pwm_dev - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
    }
  }
  return;
}


/* ==== pwm_read_reg_core @ 00414a20 ==== */

void __cdecl pwm_read_reg_core(int reg,ulong *out)

{
  *out = *(ulong *)(pwm_regs + reg * 4);
  return;
}


/* ==== pwm_clock @ 00414a40 ==== */

void pwm_clock(void)

{
  undefined4 *chan;
  int iVar1;
  int iVar2;
  int iVar3;
  int local_c;
  int local_8 [2];
  
  pwm_prescale_step(local_8);
  iVar3 = 0;
  if (*(int *)(pwm_chipflags + 4) != 0) {
    local_c = 0;
    do {
      iVar2 = *(int *)(pwm_st + 0x28 + local_c);
      chan = (undefined4 *)(pwm_st + 0x28 + local_c);
      if (iVar2 != 0) {
        iVar1 = chan[10];
        if ((chan[8] == 1) && (*(int *)(pwm_st + 0x16c + iVar1 * 4) == 1)) {
          if (iVar2 == 1) {
            iVar2 = (-(uint)(iVar1 != 0) & 4) + 3;
            pwm_set_reg(iVar2,*(uint *)((int)&DAT_004b68b8 + iVar3) |
                              *(uint *)(pwm_regs + iVar2 * 4));
            if (((iVar1 == 0) && ((*(uint *)(pwm_st + 0x10) & 0x8000) != 0)) ||
               ((iVar1 == 1 && ((*(uint *)(pwm_st + 0x20) & 0x8000) != 0)))) {
              *(undefined4 *)(pwm_st + 0x17c) = 1;
            }
            if ((iVar1 == 0) && (chan[4] != chan[5])) {
              if (chan[5] == 1) {
                chan[0xe] = chan[0xc];
                pwm_chan_reload(chan);
                goto LAB_00414bf7;
              }
              chan[0xe] = chan[0xb];
            }
          }
          pwm_chan_reload(chan);
        }
        else if (((iVar2 == 1) || ((chan[7] == 0 && (iVar2 == 2)))) && (local_8[iVar1] == 1)) {
          if (chan[2] == 0) {
            iVar2 = (-(uint)(iVar1 != 0) & 4) + 3;
            pwm_set_reg(iVar2,*(uint *)(&DAT_004b68a0 + iVar3) | *(uint *)(pwm_regs + iVar2 * 4));
            if ((*(uint *)(pwm_regs + ((-(uint)(iVar1 != 0) & 4) + 4) * 4) &
                *(uint *)(iVar3 + 0x4b6888)) != 0) {
              chan[9] = 1;
            }
            if (chan[0xe] != 0) {
              pwm_drive_int(chan,1,chan[0xe]);
              chan[0xe] = 0;
            }
            if (chan[3] == 0) {
LAB_00414bd7:
              *chan = 2;
            }
            else {
              pwm_drive_int(chan,0,0);
            }
          }
          else if (chan[2] == chan[3]) {
            pwm_drive_int(chan,1,0);
            goto LAB_00414bd7;
          }
          chan[2] = *(int *)(pwm_st + 0x174 + iVar1 * 4) + chan[2] & 0x7fff;
        }
      }
LAB_00414bf7:
      iVar3 = iVar3 + 4;
      local_c = local_c + 0x3c;
    } while (iVar3 < 0x14);
  }
  return;
}


/* ==== pwm_drive_int @ 00414c20 ==== */

void __cdecl pwm_drive_int(void *chan,int level,ulong bits)

{
  int iVar1;
  bool bVar2;
  
  if (bits == 0) {
    if ((*(int *)((int)chan + 0x28) == 1) || (*(int *)((int)chan + 0x14) != 1)) {
      bits = *(uint *)((int)chan + 0x2c);
    }
    else {
      bits = *(uint *)((int)chan + 0x30);
    }
  }
  bVar2 = level == 0;
  if ((*(int *)((int)chan + 0x28) == 0) &&
     ((*(uint *)(pwm_st + 0x10) &
      *(uint *)(&DAT_004b68d0 + (((int)chan + (-0x28 - pwm_st)) / 0x3c) * 4)) != 0)) {
    bVar2 = !bVar2;
  }
  iVar1 = *(int *)(cur_dev + 0x18);
  if (bVar2) {
    *(uint *)(iVar1 + 0x5d0) = *(uint *)(iVar1 + 0x5d0) & ~bits;
  }
  else {
    *(uint *)(iVar1 + 0x5d0) = *(uint *)(iVar1 + 0x5d0) | bits;
  }
  *(uint *)(*(int *)(cur_dev + 0x18) + 0x5d4) = *(uint *)(*(int *)(cur_dev + 0x18) + 0x5d4) | bits;
  return;
}


/* ==== pwm_prescale_step @ 00414cd0 ==== */

void __cdecl pwm_prescale_step(int *carry2)

{
  int *piVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  if (((*(byte *)(*(int *)(cur_dev + 0x18) + 0x5cc) & 2) != 0) &&
     (uVar4 = *(uint *)(*(int *)(cur_dev + 0x18) + 0x5c8) >> 1 & 1,
     uVar4 != *(uint *)(pwm_st + 0x15c))) {
    *(uint *)(pwm_st + 0x154) = 2 - (uint)(uVar4 != 0);
    *(uint *)(pwm_st + 0x15c) = uVar4;
  }
  if (((*(uint *)(*(int *)(cur_dev + 0x18) + 0x5cc) & 0x800) != 0) &&
     (uVar4 = *(uint *)(*(int *)(cur_dev + 0x18) + 0x5c8) >> 0xb & 1,
     uVar4 != *(uint *)(pwm_st + 0x160))) {
    *(uint *)(pwm_st + 0x158) = 2 - (uint)(uVar4 != 0);
    *(uint *)(pwm_st + 0x160) = uVar4;
  }
  iVar5 = 0;
  iVar2 = pwm_st;
  do {
    if (*(int *)(iVar2 + 0x28 + iVar5) != 0) {
      if (*(int *)(iVar2 + 0x44 + iVar5) == 1) {
        uVar4 = *(uint *)(iVar2 + 0x5c + iVar5);
        if ((*(uint *)(*(int *)(cur_dev + 0x18) + 0x5cc) & uVar4) != 0) {
          uVar4 = (uint)((*(uint *)(*(int *)(cur_dev + 0x18) + 0x5c8) & uVar4) != 0);
          if (-*(int *)(iVar2 + 0x40 + iVar5) != -uVar4) {
            *(uint *)(iVar2 + 0x40 + iVar5) = uVar4;
            *(uint *)(iVar2 + 0x48 + iVar5) = 2 - (uint)(uVar4 != 0);
            iVar2 = pwm_st;
          }
        }
      }
      else if ((*(int *)(iVar2 + 0x174 + *(int *)(iVar2 + 0x50 + iVar5) * 4) +
                *(int *)(iVar2 + 0x30 + iVar5) & 0x7fffU) == 0) {
        *(undefined4 *)(iVar2 + 0x48 + iVar5) = 1;
        iVar2 = pwm_st;
      }
    }
    iVar5 = iVar5 + 0x3c;
  } while (iVar5 < 300);
  iVar5 = 0;
  do {
    if (iVar5 == 0) {
      uVar4 = *(uint *)(iVar2 + 0xc);
    }
    else {
      uVar4 = *(uint *)(iVar2 + 0x1c);
    }
    carry2[iVar5] = 0;
    if ((((uVar4 & 8) == 0) || (*(int *)(pwm_chipflags + 4) != 0)) &&
       (((uVar4 & 8) != 0 || (*(int *)(pwm_st + 0x154 + iVar5 * 4) == 1)))) {
      if (iVar5 == 0) {
        bVar3 = (byte)*(undefined4 *)(pwm_st + 0xc);
      }
      else {
        bVar3 = (byte)*(undefined4 *)(pwm_st + 0x1c);
      }
      iVar2 = *(int *)(pwm_st + 0x164 + iVar5 * 4);
      iVar6 = (1 << (bVar3 & 7)) + -1;
      if (iVar2 == 0) {
        *(undefined4 *)(pwm_st + 0x16c + iVar5 * 4) = 1;
        carry2[iVar5] = 1;
        *(int *)(pwm_st + 0x164 + iVar5 * 4) = iVar6;
      }
      else {
        if (iVar2 * 2 == iVar6) {
          *(undefined4 *)(pwm_st + 0x16c + iVar5 * 4) = 2;
          carry2[iVar5] = 2;
        }
        piVar1 = (int *)(pwm_st + 0x164 + iVar5 * 4);
        *piVar1 = *piVar1 + -1;
      }
    }
    iVar5 = iVar5 + 1;
    iVar2 = pwm_st;
  } while (iVar5 < 2);
  return;
}


