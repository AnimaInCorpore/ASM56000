/* ==== shi_m_poke @ 0040d5a0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int shi_m_poke(int grp,int reg,ulong *val)

{
  int iVar1;
  
  _DAT_004dbca4 = *(int *)(cur_sim + 8) + grp * 8;
  _DAT_004dbca0 = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  shi_flags = *(undefined4 *)(_DAT_004dbca4 + 4);
  _DAT_004dbc9c = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  shi_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  shi_regs = *_DAT_004dbc9c;
  iVar1 = *(int *)(shi_grp + 0x2c);
  if ((reg < *(int *)(iVar1 + 0x28)) &&
     ((*(byte *)(*(int *)(iVar1 + 0x2c) + 0x10 + reg * 0x1c) & 0x40) != 0)) {
    shi_write_reg(reg,*val);
    shi_touch_reg(reg);
    return 1;
  }
  if (reg < *(int *)(iVar1 + 0x24)) {
    *(ulong *)(shi_regs + reg * 4) = *val;
  }
  shi_touch_reg(reg);
  return 1;
}


/* ==== shi_m_clock @ 0040d670 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void shi_m_clock(int grp)

{
  _DAT_004dbca4 = *(int *)(cur_sim + 8) + grp * 8;
  _DAT_004dbca0 = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  shi_flags = *(undefined4 *)(_DAT_004dbca4 + 4);
  _DAT_004dbc9c = (undefined4 *)(*(int *)(cur_dev + 8) + grp * 4);
  shi_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  shi_regs = *_DAT_004dbc9c;
  shi_cpu_ctl = *(undefined4 *)(cur_dev + 0x40);
  shi_clock(grp);
  return;
}


/* ==== shi_m_io_write @ 0040d6f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int shi_m_io_write(int grp,ulong addr,ulong val)

{
  int reg;
  
  shi_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  switch(addr - *(int *)(shi_grp + 0x1c)) {
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
    reg = 4;
    break;
  default:
    if (addr != 0xffff) {
      return 0;
    }
    reg = 0xd;
  }
  _DAT_004dbca4 = *(int *)(cur_sim + 8) + grp * 8;
  _DAT_004dbca0 = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  shi_flags = *(undefined4 *)(_DAT_004dbca4 + 4);
  _DAT_004dbc9c = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  shi_regs = *_DAT_004dbc9c;
  if (reg != 0xd) {
    shi_write_reg(reg,val);
    return 0;
  }
  *(uint *)(shi_regs + 0x34) = *(uint *)(shi_grp + 0x28) & val;
  return 0;
}


/* ==== shi_m_io_read @ 0040d7d0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int shi_m_io_read(int grp,ulong addr,ulong *out,int side)

{
  int iVar1;
  int extraout_EAX;
  
  shi_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  _DAT_004dbc9c = (undefined4 *)(*(int *)(cur_dev + 8) + grp * 4);
  shi_regs = *_DAT_004dbc9c;
  iVar1 = addr - *(int *)(shi_grp + 0x1c);
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
  default:
    goto switchD_0040d813_default;
  }
  _DAT_004dbca4 = *(int *)(cur_sim + 8) + grp * 8;
  _DAT_004dbca0 = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  shi_flags = *(undefined4 *)(_DAT_004dbca4 + 4);
  shi_read_reg(iVar1,out,side);
  iVar1 = extraout_EAX;
switchD_0040d813_default:
  return iVar1;
}


/* ==== shi_m_reset @ 0040d890 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void shi_m_reset(int grp)

{
  _DAT_004dbca4 = *(int *)(cur_sim + 8) + grp * 8;
  _DAT_004dbca0 = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  shi_flags = *(undefined4 *)(_DAT_004dbca4 + 4);
  _DAT_004dbc9c = (undefined4 *)(*(int *)(cur_dev + 8) + grp * 4);
  shi_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  shi_regs = *_DAT_004dbc9c;
  shi_reset_regs();
  return;
}


/* ==== shi_reset_regs @ 0040d900 ==== */

void shi_reset_regs(void)

{
  shi_regs[0xc] = 0;
  shi_regs[0xb] = 0;
  shi_regs[10] = 0;
  shi_regs[8] = 0;
  shi_regs[7] = 0;
  shi_regs[6] = 0;
  shi_regs[0x1a] = 0;
  shi_regs[0x1b] = 0;
  shi_regs[0x19] = 0;
  shi_regs[0x1c] = 0;
  *shi_regs = 1;
  shi_regs[1] = 0x8200;
  shi_regs[2] = 0x800000;
  shi_touch_reg(1);
  shi_touch_reg(2);
  shi_touch_reg(0);
  return;
}


/* ==== shi_m_irq_poll @ 0040d9a0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int shi_m_irq_poll(int grp)

{
  int iVar1;
  
  _DAT_004dbc9c = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  shi_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  shi_regs = *_DAT_004dbc9c;
  if (*(int *)(shi_regs + 0x34) != 0) {
    iVar1 = *(int *)(shi_grp + 0x20);
    if (*(int *)(shi_regs + 0x30) != 0) {
      return iVar1 + 0xc;
    }
    if (*(int *)(shi_regs + 0x2c) != 0) {
      return iVar1 + 10;
    }
    if (*(int *)(shi_regs + 0x1c) != 0) {
      return iVar1 + 2;
    }
    if (*(int *)(shi_regs + 0x28) != 0) {
      return iVar1 + 8;
    }
    if (*(int *)(shi_regs + 0x18) != 0) {
      return iVar1;
    }
    if (*(int *)(shi_regs + 0x20) != 0) {
      return iVar1 + 4;
    }
  }
  return -1;
}


/* ==== shi_m_irq_ack @ 0040da20 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void shi_m_irq_ack(int grp,ulong vec)

{
  int iVar1;
  
  _DAT_004dbc9c = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  shi_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  shi_regs = *_DAT_004dbc9c;
  iVar1 = vec - *(ulong *)(shi_grp + 0x20);
  if (vec == *(ulong *)(shi_grp + 0x20)) {
    *(undefined4 *)(shi_regs + 0x18) = 0;
    return;
  }
  if (iVar1 == 2) {
    *(undefined4 *)(shi_regs + 0x1c) = 0;
    return;
  }
  if (iVar1 == 4) {
    *(undefined4 *)(shi_regs + 0x20) = 0;
    return;
  }
  if (iVar1 == 8) {
    *(undefined4 *)(shi_regs + 0x28) = 0;
    return;
  }
  *(undefined4 *)(shi_regs + ((iVar1 != 10) + 0xb) * 4) = 0;
  return;
}


/* ==== shi_write_reg @ 0040dac0 ==== */

void __cdecl shi_write_reg(int reg,ulong val)

{
  ulong uVar1;
  
  uVar1 = val;
  if (reg != 0) {
    if (reg == 1) {
      if ((val & 0x200000) != 0) {
        *(uint *)(shi_regs + 4) = *(uint *)(shi_regs + 4) & 0xffdfffff;
      }
      if (((val & 2) == 0) || ((val & 0x40) == 0)) {
        *(uint *)(shi_regs + 4) = *(uint *)(shi_regs + 4) | 0x200;
      }
      uVar1 = val & 0xff453fff | *(uint *)(shi_regs + 4) & 0xbac200;
      if ((-(uint)((val & 0x20) != 0) & 0xfffffff7) + 10 <= *(uint *)(shi_regs + 100)) {
        uVar1 = uVar1 | 0x80000;
      }
    }
    else if (reg == 4) {
      *(uint *)(shi_regs + 4) = *(uint *)(shi_regs + 4) & 0xffff7fff;
      shi_touch_reg(1);
    }
  }
  *(uint *)(shi_regs + reg * 4) =
       *(uint *)(*(int *)(*(int *)(shi_grp + 0x2c) + 0x2c) + 4 + reg * 0x1c) & uVar1;
  *(uint *)(shi_flags + reg * 4) = *(uint *)(shi_flags + reg * 4) | 0xa0000;
  if ((*(uint *)(shi_flags + reg * 4) & 0x1800000) != 0) {
    io_out_periph_write((shi_grp - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
  }
  return;
}


/* ==== shi_touch_reg @ 0040dbc0 ==== */

void __cdecl shi_touch_reg(int reg)

{
  int iVar1;
  
  if (reg < *(int *)(*(int *)(shi_grp + 0x2c) + 0x28)) {
    *(uint *)(shi_flags + reg * 4) = *(uint *)(shi_flags + reg * 4) | 0xa0000;
    *(uint *)(shi_regs + reg * 4) =
         *(uint *)(shi_regs + reg * 4) &
         *(uint *)(*(int *)(*(int *)(shi_grp + 0x2c) + 0x2c) + 4 + reg * 0x1c);
    iVar1 = reg * 0x1c + *(int *)(*(int *)(shi_grp + 0x2c) + 0x2c);
    if ((*(byte *)(iVar1 + 0x10) & 0x60) != 0) {
      mem_trace_fetch(*(int *)(shi_grp + 0x1c) + *(int *)(iVar1 + 8));
    }
    if ((*(uint *)(shi_flags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write((shi_grp - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
    }
  }
  return;
}


/* ==== shi_read_reg @ 0040dc80 ==== */

void __cdecl shi_read_reg(int reg,ulong *out,int side_effect)

{
  int iVar1;
  uint uVar2;
  
  *out = *(ulong *)(shi_regs + reg * 4);
  if (side_effect != 0) {
    uVar2 = *(uint *)(shi_regs + 4);
    if (reg != 0) {
      if (reg == 1) {
        *(uint *)(shi_regs + 0x80) = uVar2 & 0x100000;
      }
      else if (reg == 3) {
        *out = *(ulong *)(shi_regs + 0x3c);
        if (((uVar2 & 0x100000) != 0) && (*(int *)(shi_regs + 0x80) != 0)) {
          *(undefined4 *)(shi_regs + 0x80) = 0;
          uVar2 = uVar2 & 0xffefffff;
        }
        if (*(uint *)(shi_regs + 100) != 0) {
          if (1 < *(uint *)(shi_regs + 100)) {
            iVar1 = 0x3c;
            do {
              *(undefined4 *)(shi_regs + iVar1) = *(undefined4 *)(shi_regs + 4 + iVar1);
              iVar1 = iVar1 + 4;
            } while (iVar1 < 0x60);
          }
          *(int *)(shi_regs + 100) = *(int *)(shi_regs + 100) + -1;
          if (*(uint *)(shi_regs + 100) < (-(uint)((uVar2 & 0x20) != 0) & 9) + 1) {
            uVar2 = uVar2 & 0xfff7ffff;
          }
          if (*(uint *)(shi_regs + 100) == 0) {
            uVar2 = uVar2 & 0xfffdffff;
          }
          *(undefined4 *)(shi_regs + 0xc) = *(undefined4 *)(shi_regs + 0x3c);
        }
        if (uVar2 != *(uint *)(shi_regs + 4)) {
          *(uint *)(shi_regs + 4) = uVar2;
          shi_touch_reg(1);
          return;
        }
      }
    }
  }
  return;
}


/* ==== shi_clock @ 0040dd80 ==== */

void __cdecl shi_clock(int dev)

{
  uint *pingrp;
  uint uVar1;
  bool bVar2;
  uint mask;
  uint uVar3;
  int iVar4;
  uint uVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint local_6c;
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
  
  local_44 = shi_regs[0x1d];
  local_6c = shi_regs[1];
  local_50 = *shi_regs;
  local_2c = shi_regs[2];
  local_30 = local_6c & 2;
  local_3c = local_6c & 0x40;
  uVar9 = local_6c & 0x180;
  local_38 = local_6c & 1;
  uVar7 = *(uint *)(shi_grp + 8);
  if (((local_38 == 0) || (*(int *)(shi_cpu_ctl + 0xc) != 0)) || (*(int *)(shi_cpu_ctl + 8) == 1)) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  if (bVar2) {
    shi_regs[0x19] = 0;
    local_6c = local_6c & 0xff9fffff | 0x8200;
  }
  uVar7 = uVar7 & (uVar7 - 1 ^ uVar7);
  mask = uVar7 << 4;
  uVar3 = uVar7 * 4;
  uVar10 = uVar7 * 8;
  pingrp = (uint *)(*(int *)(cur_dev + 0x18) + *(int *)(shi_grp + 4) * 0x128);
  local_34 = *pingrp;
  local_40 = uVar7 & local_34;
  local_58 = uVar7 * 2 & local_34;
  local_4c = uVar3 & local_34;
  local_54 = uVar10 & local_34;
  local_34 = mask & local_34;
  if (local_38 == 0) {
    pingrp[3] = pingrp[3] & ~uVar7;
  }
  if (local_3c == 0) {
    local_48 = (uint)(local_54 != 0);
  }
  else {
    if (shi_regs[0x1a] != 0) {
      shi_regs[0x1a] = shi_regs[0x1a] - 1;
    }
    if (shi_regs[0x1a] == 0) {
      shi_regs[0x1a] = (local_50 >> 3) + 1 << ((-((local_50 & 4) != 0) & 0xfdU) + 4 & 0x1f);
      shi_regs[0x1b] = (uint)(shi_regs[0x1b] == 0);
    }
    local_48 = shi_regs[0x1b];
  }
  uVar5 = local_48 ^ shi_regs[0x1e];
  shi_regs[0x1e] = local_48;
  if ((local_3c != 0) || (uVar9 == 0)) {
    pingrp[3] = pingrp[3] & ~mask;
  }
  if (local_38 == 0) {
LAB_0040f841:
    shi_regs[0x1c] = 0;
    uVar8 = local_6c;
    goto switchD_0040df7f_caseD_10;
  }
  if (local_3c == 0) {
    if (local_30 != 0) {
      if ((local_48 != 0) && (uVar5 == 0)) {
        if ((local_4c == 0) || (shi_regs[0x24] != 0)) {
          if ((shi_regs[0x24] != 0) && (local_4c == 0)) {
            shi_regs[0x1c] = 1;
            local_6c = local_6c | 0x400000;
          }
        }
        else {
          shi_regs[0x1c] = 0;
          local_6c = local_6c & 0xffbfffff;
        }
      }
      uVar8 = local_6c;
      switch(shi_regs[0x1c]) {
      case 0:
        pingrp[3] = pingrp[3] & ~uVar3;
        if (uVar9 != 0) {
          pin_drive_update(local_6c,uVar9,pingrp,mask);
          shi_regs[0x24] = local_4c;
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 1:
        if (local_54 == 0) {
          shi_regs[0x1f] = 8;
          shi_regs[0x1c] = 2;
          shi_regs[0x24] = local_4c;
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 2:
        if (local_54 != 0) {
          pingrp[2] = pingrp[2] | mask;
          shi_regs[5] = shi_regs[5] << 1;
          if (local_4c != 0) {
            shi_regs[5] = shi_regs[5] | 1;
          }
          shi_regs[0x1f] = shi_regs[0x1f] - 1;
          shi_regs[0x1c] = 4 - (shi_regs[0x1f] != 0);
          shi_regs[0x24] = local_4c;
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 3:
        if (local_54 == 0) {
          shi_regs[0x1c] = 2;
          shi_regs[0x24] = local_4c;
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 4:
        if (local_54 == 0) {
          uVar7 = local_2c >> 0x11;
          if (local_58 != 0) {
            uVar7 = uVar7 | 2;
          }
          if (local_40 != 0) {
            uVar7 = uVar7 | 1;
          }
          pingrp[3] = pingrp[3] | uVar3;
          iVar4 = io_in_pin_read(dev,local_28);
          if ((iVar4 != 0) || (iVar4 = io_in_timed_pin_read(dev,local_28), iVar4 != 0)) {
            shi_regs[5] = local_20;
          }
          if ((shi_regs[5] >> 1 & 0x7f) == uVar7) {
            pingrp[2] = pingrp[2] & ~uVar3;
            shi_regs[0x21] = shi_regs[5] & 1;
            pingrp[2] = pingrp[2] & ~mask;
            shi_regs[0x1c] = 5;
            shi_regs[0x24] = local_4c;
          }
          else {
            shi_regs[0x1c] = 0x12;
            shi_regs[0x24] = local_4c;
          }
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 5:
        if (local_54 != 0) {
          shi_regs[0x1c] = (-(uint)(shi_regs[0x21] != 0) & 6) + 6;
          if ((local_6c & 8) == 0) {
            uVar7 = ((local_6c & 4) != 0) + 1;
          }
          else {
            uVar7 = 3;
          }
          shi_regs[0x22] = uVar7;
          shi_regs[0x25] = 1;
          shi_regs[0x24] = local_4c;
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 6:
        if ((uVar9 != 0) && (shi_regs[0x25] != 0)) {
          pin_drive_update(local_6c,uVar9,pingrp,mask);
        }
        if (local_54 == 0) {
          pingrp[3] = pingrp[3] & ~uVar3;
          pingrp[2] = pingrp[2] | uVar3;
          shi_regs[0x1f] = 8;
          shi_regs[0x1c] = 7;
          shi_regs[0x24] = local_4c;
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 7:
        if (local_54 != 0) {
          shi_regs[0x25] = 0;
          pingrp[2] = pingrp[2] | mask;
          shi_regs[5] = shi_regs[5] << 1;
          if (local_4c != 0) {
            shi_regs[5] = shi_regs[5] | 1;
          }
          shi_regs[0x1f] = shi_regs[0x1f] - 1;
          if (shi_regs[0x1f] == 0) {
            shi_regs[0x22] = shi_regs[0x22] - 1;
            if (shi_regs[0x22] == 0) {
              iVar4 = io_in_pin_read(dev,local_28);
              if ((iVar4 != 0) || (iVar4 = io_in_timed_pin_read(dev,local_28), iVar4 != 0)) {
                shi_regs[5] = local_20;
              }
              if ((local_6c & 8) == 0) {
                bVar6 = (-((local_6c & 4) != 0) & 0xf8U) + 0x10;
              }
              else {
                bVar6 = 0;
              }
              shi_regs[5] = shi_regs[5] << (bVar6 & 0x1f) & 0xffffff;
              if ((local_6c & 0x80000) == 0) {
                if (shi_regs[0x19] == 0) {
                  shi_regs[3] = shi_regs[5];
                  shi_touch_reg(3);
                }
                uVar7 = local_6c | 0x20000;
                shi_regs[shi_regs[0x19] + 0xf] = shi_regs[5];
                shi_regs[0x19] = shi_regs[0x19] + 1;
                if (shi_regs[0x19] < (-(uint)((local_6c & 0x20) != 0) & 9) + 1) {
                  local_6c = uVar7;
                  if (uVar9 != 0) {
                    pin_drive_update(uVar7,uVar9,pingrp,mask);
                  }
                }
                else {
                  local_6c = local_6c | 0xa0000;
                }
                shi_regs[0x1c] = 9;
              }
              else {
                local_6c = local_6c | 0x100000;
                shi_regs[0x1c] = 0xb;
              }
              if ((local_6c & 8) == 0) {
                uVar7 = ((local_6c & 4) != 0) + 1;
              }
              else {
                uVar7 = 3;
              }
              shi_regs[0x22] = uVar7;
              shi_regs[0x25] = 1;
              shi_regs[0x24] = local_4c;
              uVar8 = local_6c;
            }
            else {
              shi_regs[0x1c] = 9;
              shi_regs[0x24] = local_4c;
            }
          }
          else {
            shi_regs[0x1c] = 8;
            shi_regs[0x24] = local_4c;
          }
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 8:
        if (local_54 == 0) {
          shi_regs[0x1c] = 7;
          shi_regs[0x24] = local_4c;
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 9:
        if ((uVar9 != 0) && (shi_regs[0x25] != 0)) {
          pin_drive_update(local_6c,uVar9,pingrp,mask);
        }
        if (local_54 == 0) {
          pingrp[3] = pingrp[3] | uVar3;
          pingrp[2] = pingrp[2] & ~uVar3;
          shi_regs[0x1c] = 10;
          shi_regs[0x24] = local_4c;
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 10:
        if ((uVar9 != 0) && (shi_regs[0x25] != 0)) {
          pin_drive_update(local_6c,uVar9,pingrp,mask);
        }
        if (local_54 != 0) {
          shi_regs[0x1c] = 6;
          shi_regs[0x24] = local_4c;
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 0xb:
        if (local_54 == 0) {
          pingrp[3] = pingrp[3] | uVar3;
          pingrp[2] = pingrp[2] | uVar3;
          shi_regs[0x1c] = 10;
          shi_regs[0x24] = local_4c;
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 0xc:
        if (uVar9 != 0) {
          pin_drive_update(local_6c,uVar9,pingrp,mask);
        }
        if (local_54 == 0) {
          if ((local_6c & 0x8000) == 0) {
            uVar8 = local_6c | 0x8000;
          }
          else {
            uVar8 = local_6c | 0x4000;
            shi_regs[0x1c] = 0;
          }
          shi_regs[5] = shi_regs[4];
          if ((uVar8 & 8) == 0) {
            bVar6 = (-((uVar8 & 4) != 0) & 0xf8U) + 0x10;
          }
          else {
            bVar6 = 0;
          }
          local_5c = shi_regs[5] >> (bVar6 & 0x1f);
          io_out_pin_write(dev,&local_5c,0);
          if ((shi_regs[5] & 0x800000) == 0) {
            pingrp[2] = pingrp[2] & ~uVar3;
          }
          else {
            pingrp[2] = pingrp[2] | uVar3;
          }
          pingrp[3] = pingrp[3] | uVar3;
          shi_regs[0x1f] = 8;
          if ((uVar8 & 8) == 0) {
            uVar7 = ((uVar8 & 4) != 0) + 1;
          }
          else {
            uVar7 = 3;
          }
          shi_regs[0x22] = uVar7;
          shi_regs[0x1c] = 0xd;
          shi_regs[0x24] = local_4c;
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 0xd:
        if (local_54 != 0) {
          shi_regs[0x1f] = shi_regs[0x1f] - 1;
          shi_regs[0x1c] = 0xf - (shi_regs[0x1f] != 0);
          shi_regs[0x24] = local_4c;
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 0xe:
        if (local_54 == 0) {
          pingrp[2] = pingrp[2] | mask;
          shi_regs[5] = shi_regs[5] << 1;
          if ((shi_regs[5] & 0x800000) == 0) {
            uVar7 = pingrp[2] & ~uVar3;
          }
          else {
            uVar7 = pingrp[2] | uVar3;
          }
          pingrp[2] = uVar7;
          pingrp[3] = pingrp[3] | uVar3;
          shi_regs[0x1c] = 0xd;
          shi_regs[0x24] = local_4c;
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 0xf:
        if (local_54 == 0) {
          pingrp[3] = pingrp[3] & ~uVar3;
          pingrp[2] = pingrp[2] | uVar3;
          shi_regs[0x1c] = 0x10;
          shi_regs[0x24] = local_4c;
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 0x10:
        if (local_54 != 0) {
          if (local_4c == 0) {
            shi_regs[0x22] = shi_regs[0x22] - 1;
            shi_regs[0x1c] = (-(uint)(shi_regs[0x22] != 0) & 5) + 0xc;
            shi_regs[0x24] = 0;
          }
          else {
            shi_regs[0x1c] = 0;
            shi_regs[0x24] = local_4c;
          }
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 0x11:
        if (local_54 == 0) {
          shi_regs[0x1f] = 8;
          shi_regs[0x1c] = 0xd;
          shi_regs[5] = shi_regs[5] << 1;
          if ((shi_regs[5] & 0x800000) == 0) {
            pingrp[2] = pingrp[2] & ~uVar3;
            pingrp[3] = pingrp[3] | uVar3;
            shi_regs[0x24] = local_4c;
          }
          else {
            pingrp[2] = pingrp[2] | uVar3;
            pingrp[3] = pingrp[3] | uVar3;
            shi_regs[0x24] = local_4c;
          }
          goto switchD_0040df7f_caseD_10;
        }
        break;
      case 0x12:
        pingrp[3] = pingrp[3] & ~uVar3;
        shi_regs[0x24] = local_4c;
        goto switchD_0040df7f_caseD_10;
      }
      goto switchD_0040e967_default;
    }
    if (local_58 == 0) {
      local_6c = local_6c | 0x400000;
    }
    else {
      local_6c = local_6c & 0xffbfffff;
    }
    uVar1 = shi_regs[0x1c];
    uVar8 = local_6c;
    if ((local_50 & 1) != 0) {
      if (((uVar1 == 1) || (uVar1 == 2)) && (local_58 != 0)) {
        shi_regs[0x1c] = 3;
      }
      switch(shi_regs[0x1c]) {
      case 0:
        pingrp[3] = (uVar3 | pingrp[3]) & ~(uVar10 | uVar7);
        if ((shi_regs[0x1c] == 0) && ((local_6c & 0x8000) == 0)) {
          local_6c = local_6c | 0x8000;
          shi_regs[5] = shi_regs[4];
          shi_regs[0x1c] = 0x12;
        }
        break;
      case 1:
        if (uVar5 == 0) goto switchD_0040e967_default;
        shi_regs[5] = shi_regs[5] << 1;
        if (local_40 != 0) {
          shi_regs[5] = shi_regs[5] | 1;
        }
        shi_regs[0x1f] = shi_regs[0x1f] - 1;
        if (shi_regs[0x1f] != 0) goto LAB_0040f424;
        goto LAB_0040f6c8;
      case 2:
        if (uVar5 == 0) goto switchD_0040e967_default;
        uVar7 = shi_regs[5];
        goto LAB_0040f458;
      case 3:
        goto switchD_0040f277_caseD_3;
      default:
        goto switchD_0040e967_default;
      case 0x12:
      }
      if (uVar9 != 0) {
        pingrp[3] = pingrp[3] | mask;
        if ((((uVar9 == 0x100) && (shi_regs[0x1c] != 0)) ||
            ((uVar9 == 0x80 && ((local_6c & 0x80000) == 0)))) ||
           (((uVar9 == 0x180 && ((local_6c & 0x80000) == 0)) && (shi_regs[0x1c] != 0)))) {
          pingrp[2] = pingrp[2] & ~mask;
        }
        else {
          pingrp[2] = pingrp[2] | mask;
        }
      }
      uVar8 = local_6c;
      if (((local_58 == 0) && (uVar5 != 0)) && ((local_50 >> 1 & 1) != local_48)) {
        if (uVar9 != 0) {
          pingrp[2] = pingrp[2] | mask;
        }
        if ((local_6c & 8) == 0) {
          bVar6 = (-((local_6c & 4) != 0) & 0xf8U) + 0x10;
        }
        else {
          bVar6 = 0;
        }
        local_5c = shi_regs[5] >> (bVar6 & 0x1f);
        io_out_pin_write(dev,&local_5c,0);
        shi_regs[0x1d] = local_6c;
        if ((local_6c & 8) == 0) {
          uVar7 = (-(uint)((local_6c & 4) != 0) & 8) + 8;
        }
        else {
          uVar7 = 0x18;
        }
        shi_regs[0x1f] = uVar7;
        if (shi_regs[0x1c] == 0) {
          local_6c = local_6c | 0x4000;
        }
        uVar7 = shi_regs[5];
LAB_0040f458:
        uVar8 = local_6c;
        if ((uVar7 & 0x800000) == 0) {
          pingrp[2] = pingrp[2] & ~uVar3;
          shi_regs[0x1c] = 1;
          shi_regs[0x24] = local_4c;
        }
        else {
          pingrp[2] = pingrp[2] | uVar3;
          shi_regs[0x1c] = 1;
          shi_regs[0x24] = local_4c;
        }
        goto switchD_0040df7f_caseD_10;
      }
      goto switchD_0040e967_default;
    }
    switch(uVar1) {
    case 0:
      pingrp[3] = (uVar3 | pingrp[3]) & ~(uVar10 | uVar7);
      if ((local_58 != 0) && ((local_6c & 0x8000) == 0)) {
        shi_regs[5] = shi_regs[4];
        local_6c = local_6c | 0x8000;
        shi_regs[0x1c] = 4;
      }
    case 4:
    case 5:
      if (uVar9 != 0) {
        pingrp[3] = pingrp[3] | mask;
        if ((((uVar9 == 0x100) && (shi_regs[0x1c] != 0)) ||
            ((uVar9 == 0x80 && ((local_6c & 0x80000) == 0)))) ||
           (((uVar9 == 0x180 && ((local_6c & 0x80000) == 0)) && (shi_regs[0x1c] != 0)))) {
          uVar7 = pingrp[2] & ~mask;
        }
        else {
          uVar7 = pingrp[2] | mask;
        }
        pingrp[2] = uVar7;
      }
      uVar8 = local_6c;
      if (shi_regs[0x1c] == 4) {
        if (local_58 != 0) break;
        if ((shi_regs[5] & 0x800000) == 0) {
          uVar3 = pingrp[2] & ~uVar3;
        }
        else {
          uVar3 = pingrp[2] | uVar3;
        }
        pingrp[2] = uVar3;
        shi_regs[0x1c] = 5;
      }
      if (((local_58 == 0) && (uVar5 != 0)) && ((local_50 >> 1 & 1) != local_48)) {
        if (uVar9 != 0) {
          pingrp[2] = pingrp[2] | mask;
        }
        if ((local_6c & 8) == 0) {
          bVar6 = (-((local_6c & 4) != 0) & 0xf8U) + 0x10;
        }
        else {
          bVar6 = 0;
        }
        local_5c = shi_regs[5] >> (bVar6 & 0x1f);
        io_out_pin_write(dev,&local_5c,0);
        shi_regs[0x1d] = local_6c;
        if ((local_6c & 8) == 0) {
          uVar7 = (-(uint)((local_6c & 4) != 0) & 8) + 8;
        }
        else {
          uVar7 = 0x18;
        }
        shi_regs[0x1f] = uVar7;
        if (shi_regs[0x1c] != 5) {
          local_6c = local_6c | 0x4000;
        }
        shi_regs[0x1c] = 1;
switchD_0040f4b5_caseD_1:
        if (local_58 == 0) {
          uVar8 = local_6c;
          if (uVar5 == 0) break;
          shi_regs[5] = shi_regs[5] << 1;
          if (local_40 != 0) {
            shi_regs[5] = shi_regs[5] | 1;
          }
          shi_regs[0x1f] = shi_regs[0x1f] - 1;
          if (shi_regs[0x1f] != 0) {
LAB_0040f424:
            shi_regs[0x1c] = 2;
            shi_regs[0x24] = local_4c;
            uVar8 = local_6c;
            goto switchD_0040df7f_caseD_10;
          }
          shi_regs[0x1c] = 3;
        }
switchD_0040f277_caseD_3:
LAB_0040f6c8:
        shi_regs[0x1c] = 0;
        iVar4 = io_in_pin_read(dev,local_28);
        if ((iVar4 != 0) || (iVar4 = io_in_timed_pin_read(dev,local_28), iVar4 != 0)) {
          shi_regs[5] = local_20;
        }
        if ((local_44 & 8) == 0) {
          bVar6 = (-((local_44 & 4) != 0) & 0xf8U) + 0x10;
        }
        else {
          bVar6 = 0;
        }
        shi_regs[5] = shi_regs[5] << (bVar6 & 0x1f) & 0xffffff;
        if ((local_6c & 0x80000) != 0) {
          shi_regs[0x24] = local_4c;
          uVar8 = local_6c | 0x100000;
          goto switchD_0040df7f_caseD_10;
        }
        if (shi_regs[0x19] == 0) {
          shi_regs[3] = shi_regs[5];
          shi_touch_reg(3);
        }
        shi_regs[shi_regs[0x19] + 0xf] = shi_regs[5];
        shi_regs[0x19] = shi_regs[0x19] + 1;
        uVar8 = local_6c | 0x20000;
        if ((-(uint)((local_6c & 0x20) != 0) & 9) + 1 <= shi_regs[0x19]) {
          shi_regs[0x24] = local_4c;
          uVar8 = local_6c | 0xa0000;
          goto switchD_0040df7f_caseD_10;
        }
      }
      break;
    case 1:
      goto switchD_0040f4b5_caseD_1;
    case 2:
      if (local_58 != 0) {
        shi_regs[0x1c] = 3;
        shi_regs[0x24] = local_4c;
        goto switchD_0040df7f_caseD_10;
      }
      if (uVar5 != 0) {
        if ((shi_regs[5] & 0x800000) == 0) {
          uVar3 = pingrp[2] & ~uVar3;
        }
        else {
          uVar3 = pingrp[2] | uVar3;
        }
        pingrp[2] = uVar3;
        shi_regs[0x1c] = 1;
      }
      break;
    case 3:
      goto switchD_0040f277_caseD_3;
    }
switchD_0040e967_default:
    local_6c = uVar8;
    shi_regs[0x24] = local_4c;
    uVar8 = local_6c;
    goto switchD_0040df7f_caseD_10;
  }
  if (local_30 != 0) {
    uVar8 = local_6c & 0xffbfffff;
    switch(shi_regs[0x1c]) {
    case 1:
      if (uVar5 != 0) {
        pingrp[3] = pingrp[3] | uVar3;
        pingrp[2] = pingrp[2] & ~uVar3;
        shi_regs[0x1c] = 2;
        shi_regs[0x1a] = shi_regs[0x1a] >> 1;
      }
      break;
    case 2:
      if (uVar5 != 0) {
        pingrp[2] = pingrp[2] & ~uVar10;
        shi_regs[0x1a] = shi_regs[0x1a] >> 1;
        shi_regs[0x1c] = (-(uint)(shi_regs[0x1f] != 0) & 0xfffffffe) + 5;
      }
      break;
    case 3:
      if (uVar5 != 0) {
        pingrp[3] = pingrp[3] | uVar3;
        if ((shi_regs[5] & 0x800000) == 0) {
          uVar3 = pingrp[2] & ~uVar3;
        }
        else {
          uVar3 = pingrp[2] | uVar3;
        }
        pingrp[2] = uVar3;
        shi_regs[5] = shi_regs[5] << 1;
        shi_regs[0x1f] = shi_regs[0x1f] - 1;
        shi_regs[0x1c] = 4;
        shi_regs[0x1a] = shi_regs[0x1a] >> 1;
      }
      break;
    case 4:
      if (uVar5 != 0) {
        pingrp[2] = pingrp[2] | uVar10;
        shi_regs[0x1c] = 2;
      }
      break;
    case 5:
      if (uVar5 != 0) {
        pingrp[2] = pingrp[2] | uVar3;
        pingrp[3] = pingrp[3] & ~uVar3;
        shi_regs[0x1a] = shi_regs[0x1a] >> 1;
        shi_regs[0x1c] = 6;
      }
      break;
    case 6:
      if (uVar5 != 0) {
        pingrp[2] = pingrp[2] | uVar10;
        if (local_4c == 0) {
          shi_regs[0x1c] = 7;
        }
        else {
          shi_regs[0x1c] = 0xc;
          uVar8 = uVar8 | 0x200000;
        }
      }
      break;
    case 7:
      if (uVar5 == 0) break;
      if (shi_regs[0x23] == 0) {
        shi_regs[0x22] = shi_regs[0x22] - 1;
        if (shi_regs[0x22] != 0) {
          pingrp[2] = pingrp[2] & ~uVar10;
          shi_regs[0x1f] = 8;
          if (shi_regs[0x21] == 0) {
            shi_regs[0x1a] = shi_regs[0x1a] >> 1;
            shi_regs[0x1c] = 3;
          }
          else {
            shi_regs[0x1c] = 8;
          }
          break;
        }
        uVar7 = uVar8;
        if (shi_regs[0x21] != 0) {
          iVar4 = io_in_pin_read(dev,local_28);
          if ((iVar4 != 0) || (iVar4 = io_in_timed_pin_read(dev,local_28), iVar4 != 0)) {
            shi_regs[5] = local_20;
          }
          if ((local_44 & 8) == 0) {
            bVar6 = (-((local_44 & 4) != 0) & 0xf8U) + 0x10;
          }
          else {
            bVar6 = 0;
          }
          local_30 = shi_regs[5];
          shi_regs[5] = local_30 << (bVar6 & 0x1f) & 0xffffff;
          if ((local_6c & 0x80000) != 0) {
            shi_regs[0x1c] = 0;
            uVar8 = uVar8 | 0x100000;
            goto switchD_0040df7f_caseD_0;
          }
          if (shi_regs[0x19] == 0) {
            shi_regs[3] = shi_regs[5];
            shi_touch_reg(3);
          }
          shi_regs[shi_regs[0x19] + 0xf] = shi_regs[5];
          shi_regs[0x19] = shi_regs[0x19] + 1;
          uVar7 = uVar8 | 0x20000;
          if ((-(uint)((local_6c & 0x20) != 0) & 9) + 1 <= shi_regs[0x19]) {
            uVar7 = uVar8 | 0xa0000;
          }
        }
        local_6c = uVar7;
        shi_regs[0x1c] = 0;
        uVar8 = local_6c;
      }
      else {
        shi_regs[0x1c] = 0;
      }
    case 0:
switchD_0040df7f_caseD_0:
      local_6c = uVar8;
      uVar8 = local_6c;
      if (((uVar9 == 0) || (local_34 == 0)) && ((local_6c & 0x8000) == 0)) {
        shi_regs[0x1d] = local_6c;
        shi_regs[5] = shi_regs[4];
        shi_regs[0x1a] = (local_50 >> 3) + 1 << ((-((local_50 & 4) != 0) & 0xfdU) + 4 & 0x1f);
        if ((local_6c & 0x200) == 0) {
          pingrp[2] = pingrp[2] & ~uVar10;
          shi_regs[0x23] = 0;
          if ((local_6c & 8) == 0) {
            uVar7 = ((local_6c & 4) != 0) + 1;
          }
          else {
            uVar7 = 3;
          }
          shi_regs[0x22] = uVar7;
          uVar8 = local_6c | 0x8000;
          if (shi_regs[0x21] == 0) {
            if ((local_6c & 8) == 0) {
              bVar6 = (-((local_6c & 4) != 0) & 0xf8U) + 0x10;
            }
            else {
              bVar6 = 0;
            }
            local_5c = shi_regs[5] >> (bVar6 & 0x1f);
            io_out_pin_write(dev,&local_5c,0);
            pingrp[3] = pingrp[3] | uVar3 | uVar10;
            shi_regs[0x1a] = shi_regs[0x1a] >> 1;
            shi_regs[0x1c] = 3;
            shi_regs[0x1f] = 8;
          }
          else {
            pingrp[3] = ~uVar3 & pingrp[3] | uVar10;
            shi_regs[0x1c] = 8;
            shi_regs[0x1f] = 8;
          }
        }
        else {
          shi_regs[0x1a] = shi_regs[0x1a] >> 1;
          shi_regs[0x21] = shi_regs[5] & 0x10000;
          pingrp[3] = pingrp[3] | uVar3 | uVar10;
          pingrp[2] = (uVar3 | uVar10 | pingrp[2]) & ~uVar3;
          shi_regs[0x23] = 1;
          local_5c = shi_regs[5] >> 0x10;
          io_out_pin_write(dev,&local_5c,0);
          shi_regs[0x1c] = 0x13;
          shi_regs[0x1f] = 8;
          uVar8 = local_6c & 0xfffffdff | 0x8000;
        }
      }
      break;
    case 8:
      if (uVar5 != 0) {
        pingrp[2] = pingrp[2] | uVar10;
        shi_regs[5] = shi_regs[5] << 1;
        if (local_4c != 0) {
          shi_regs[5] = shi_regs[5] | 1;
        }
        shi_regs[0x1f] = shi_regs[0x1f] - 1;
        shi_regs[0x1c] = 9;
      }
      break;
    case 9:
      if (uVar5 != 0) {
        pingrp[2] = pingrp[2] & ~uVar10;
        if (shi_regs[0x1f] == 0) {
          shi_regs[0x1b] = shi_regs[0x1b] >> 1;
          shi_regs[0x1c] = 10;
        }
        else {
          shi_regs[0x1c] = 8;
        }
      }
      break;
    case 10:
      if (uVar5 != 0) {
        pingrp[3] = pingrp[3] | uVar3;
        if ((local_6c & 0x200) == 0) {
          uVar3 = pingrp[2] & ~uVar3;
        }
        else {
          uVar3 = pingrp[2] | uVar3;
        }
        pingrp[2] = uVar3;
        shi_regs[0x1b] = shi_regs[0x1b] >> 1;
        shi_regs[0x1c] = 0xb;
      }
      break;
    case 0xb:
      if (uVar5 != 0) {
        pingrp[2] = pingrp[2] | uVar10;
        shi_regs[0x1c] = 7;
      }
      break;
    case 0xc:
      if (uVar5 != 0) {
        pingrp[2] = pingrp[2] & ~uVar10;
        shi_regs[0x1c] = 0xd;
        shi_regs[0x1b] = shi_regs[0x1b] >> 1;
      }
      break;
    case 0xd:
      if (uVar5 != 0) {
        pingrp[3] = pingrp[3] | uVar3;
        pingrp[2] = pingrp[2] & ~uVar3;
        shi_regs[0x1c] = 0xe;
        shi_regs[0x1b] = shi_regs[0x1b] >> 1;
      }
      break;
    case 0xe:
      if (uVar5 != 0) {
        pingrp[2] = pingrp[2] | uVar10;
        shi_regs[0x1b] = shi_regs[0x1b] >> 1;
        shi_regs[0x1b] = shi_regs[0x1b] - 1;
        shi_regs[0x1c] = 0xf;
      }
      break;
    case 0xf:
      local_6c = uVar8;
      if (uVar5 == 0) break;
      goto LAB_0040f841;
    case 0x13:
      if (uVar5 != 0) {
        pingrp[3] = pingrp[3] | uVar3;
        pingrp[2] = pingrp[2] | uVar3;
        shi_regs[0x1c] = 0x14;
        shi_regs[0x1a] = shi_regs[0x1a] >> 1;
      }
      break;
    case 0x14:
      if (uVar5 != 0) {
        pingrp[2] = pingrp[2] & ~uVar10;
        shi_regs[0x1c] = 0x15;
      }
      break;
    case 0x15:
      if (uVar5 != 0) {
        pingrp[2] = pingrp[2] | uVar10;
        shi_regs[0x1c] = 1;
        shi_regs[0x1a] = shi_regs[0x1a] >> 1;
      }
    }
    goto switchD_0040df7f_caseD_10;
  }
  if (local_58 == 0) {
    local_6c = local_6c | 0x200000;
  }
  uVar8 = local_6c;
  switch(shi_regs[0x1c]) {
  case 0:
    goto switchD_0040e58a_caseD_0;
  case 1:
    if (uVar5 != 0) {
      pingrp[2] = pingrp[2] ^ uVar10;
      shi_regs[5] = shi_regs[5] << 1;
      if (local_4c != 0) {
        shi_regs[5] = shi_regs[5] | 1;
      }
      shi_regs[0x1f] = shi_regs[0x1f] - 1;
      if (shi_regs[0x1f] == 0) {
        shi_regs[0x1c] = 3;
        iVar4 = io_in_pin_read(dev,local_28);
        if ((iVar4 != 0) || (iVar4 = io_in_timed_pin_read(dev,local_28), iVar4 != 0)) {
          shi_regs[5] = local_20;
        }
        if ((local_44 & 8) == 0) {
          bVar6 = (-((local_44 & 4) != 0) & 0xf8U) + 0x10;
        }
        else {
          bVar6 = 0;
        }
        shi_regs[5] = shi_regs[5] << (bVar6 & 0x1f) & 0xffffff;
        if ((local_6c & 0x80000) == 0) {
          if (shi_regs[0x19] == 0) {
            shi_regs[3] = shi_regs[5];
            shi_touch_reg(3);
          }
          shi_regs[shi_regs[0x19] + 0xf] = shi_regs[5];
          shi_regs[0x19] = shi_regs[0x19] + 1;
          uVar8 = local_6c | 0x20000;
          if ((-(uint)((local_6c & 0x20) != 0) & 9) + 1 <= shi_regs[0x19]) {
            uVar8 = local_6c | 0xa0000;
          }
        }
        else {
          uVar8 = local_6c | 0x100000;
        }
      }
      else {
        shi_regs[0x1c] = 2;
      }
    }
    break;
  case 2:
    if (uVar5 != 0) {
      uVar10 = pingrp[2] ^ uVar10;
      pingrp[2] = uVar10;
      if ((shi_regs[5] & 0x800000) == 0) {
        uVar7 = ~uVar7 & uVar10;
      }
      else {
        uVar7 = uVar7 | uVar10;
      }
      pingrp[2] = uVar7;
      shi_regs[0x1c] = 1;
    }
    break;
  case 3:
    if (uVar5 == 0) break;
    if ((local_50 & 1) == 0) {
      local_6c = local_6c | 0x8000;
      pingrp[2] = pingrp[2] ^ uVar10;
    }
    shi_regs[0x1c] = 0;
switchD_0040e58a_caseD_0:
    if (local_58 == 0) {
      uVar8 = local_6c & 0xffffffbf | 0x200000;
      break;
    }
switchD_0040e58a_caseD_4:
    pingrp[3] = (uVar10 | uVar7 | pingrp[3]) & ~(uVar3 | mask);
    if ((local_50 & 2) == 0) {
      pingrp[2] = pingrp[2] & ~uVar10;
    }
    else {
      pingrp[2] = pingrp[2] | uVar10;
    }
    if ((local_6c & 0x8000) == 0) {
      if ((shi_regs[0x1c] == 0) && (shi_regs[0x1c] = 4, (local_50 & 1) != 0)) {
        local_6c = local_6c | 0x8000;
      }
      if ((local_6c & 0x8000) != 0) goto LAB_0040e625;
LAB_0040e638:
      uVar8 = local_6c | 0x400000;
    }
    else {
LAB_0040e625:
      if (shi_regs[0x1c] == 4) goto LAB_0040e638;
      uVar8 = local_6c & 0xffbfffff;
    }
    if (((uVar9 == 0) || (local_34 == 0)) && (shi_regs[0x1c] == 4)) {
      shi_regs[0x1d] = uVar8;
      shi_regs[5] = shi_regs[4];
      if ((uVar8 & 8) == 0) {
        bVar6 = (-((uVar8 & 4) != 0) & 0xf8U) + 0x10;
      }
      else {
        bVar6 = 0;
      }
      local_5c = shi_regs[5] >> (bVar6 & 0x1f);
      io_out_pin_write(dev,&local_5c,0);
      shi_regs[0x1a] = (local_50 >> 3) + 1 << ((-((local_50 & 4) != 0) & 0xfdU) + 4 & 0x1f);
      shi_regs[0x1c] = 1;
      pingrp[3] = pingrp[3] | uVar7;
      if ((local_50 & 1) != 0) {
        pingrp[2] = pingrp[2] ^ uVar10;
      }
      if ((shi_regs[5] & 0x800000) == 0) {
        uVar7 = pingrp[2] & ~uVar7;
      }
      else {
        uVar7 = pingrp[2] | uVar7;
      }
      pingrp[2] = uVar7;
      if ((uVar8 & 8) == 0) {
        shi_regs[0x1f] = (-(uint)((uVar8 & 4) != 0) & 8) + 8;
      }
      else {
        shi_regs[0x1f] = 0x18;
      }
    }
    break;
  case 4:
    goto switchD_0040e58a_caseD_4;
  }
switchD_0040df7f_caseD_10:
  local_6c = uVar8;
  if (((local_6c & 0x8000) == 0) || ((local_6c & 0x800) == 0)) {
    uVar7 = 0;
  }
  else {
    uVar7 = 1;
  }
  shi_regs[6] = uVar7;
  if (((local_6c & 0x200000) == 0) || ((local_6c & 0x400) == 0)) {
    uVar7 = 0;
  }
  else {
    uVar7 = 1;
  }
  shi_regs[0xc] = uVar7;
  uVar7 = local_6c & 0x100000;
  if ((uVar7 == 0) || ((local_6c & 0x1000) == 0)) {
    uVar9 = 0;
  }
  else {
    uVar9 = 1;
  }
  shi_regs[0xb] = uVar9;
  if ((((local_6c & 0x20000) == 0) || ((local_6c & 0x3000) != 0x1000)) || (uVar7 != 0)) {
    uVar9 = 0;
  }
  else {
    uVar9 = 1;
  }
  shi_regs[8] = uVar9;
  if ((((local_6c & 0x80000) == 0) || ((local_6c & 0x3000) != 0x3000)) || (uVar7 != 0)) {
    uVar7 = 0;
  }
  else {
    uVar7 = 1;
  }
  shi_regs[10] = uVar7;
  if (local_6c != shi_regs[1]) {
    shi_regs[1] = local_6c;
    shi_touch_reg(1);
  }
  return;
}


