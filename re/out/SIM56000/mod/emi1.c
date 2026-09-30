/* ==== emi1_m_poke @ 00401a50 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int emi1_m_poke(int grp,int reg,ulong *val)

{
  int iVar1;
  
  _emi1_gruntime = *(int *)(cur_sim + 8) + grp * 8;
  _emi1_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  emi1_flags = *(undefined4 *)(_emi1_gruntime + 4);
  _emi1_regs_slot = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  emi1_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  emi1_regs = *_emi1_regs_slot;
  iVar1 = *(int *)(emi1_grp + 0x2c);
  if ((reg < *(int *)(iVar1 + 0x28)) &&
     ((*(byte *)(*(int *)(iVar1 + 0x2c) + 0x10 + reg * 0x1c) & 0x40) != 0)) {
    emi1_write_reg(reg,*val);
    emi1_touch_reg(reg);
    return 1;
  }
  if (reg < *(int *)(iVar1 + 0x24)) {
    *(ulong *)(emi1_regs + reg * 4) = *val;
  }
  emi1_touch_reg(reg);
  return 1;
}


/* ==== emi1_touch_reg @ 00401b20 ==== */

void __cdecl emi1_touch_reg(int reg)

{
  int iVar1;
  
  if (reg < *(int *)(*(int *)(emi1_grp + 0x2c) + 0x28)) {
    *(uint *)(emi1_flags + reg * 4) = *(uint *)(emi1_flags + reg * 4) | 0xa0000;
    *(uint *)(emi1_regs + reg * 4) =
         *(uint *)(emi1_regs + reg * 4) &
         *(uint *)(*(int *)(*(int *)(emi1_grp + 0x2c) + 0x2c) + 4 + reg * 0x1c);
    iVar1 = reg * 0x1c + *(int *)(*(int *)(emi1_grp + 0x2c) + 0x2c);
    if ((*(byte *)(iVar1 + 0x10) & 0x60) != 0) {
      mem_trace_fetch(*(int *)(emi1_grp + 0x1c) + *(int *)(iVar1 + 8));
    }
    if ((*(uint *)(emi1_flags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write((emi1_grp - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
    }
  }
  return;
}


/* ==== emi1_m_clock @ 00401be0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void emi1_m_clock(int grp,int dev)

{
  emi1_cpu_ctl = *(int *)(cur_dev + 0x40);
  if (*(int *)(emi1_cpu_ctl + 8) != 1) {
    _emi1_gruntime = *(int *)(cur_sim + 8) + grp * 8;
    _emi1_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
    emi1_flags = *(undefined4 *)(_emi1_gruntime + 4);
    _emi1_regs_slot = (undefined4 *)(*(int *)(cur_dev + 8) + grp * 4);
    emi1_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
    emi1_regs = *_emi1_regs_slot;
    emi1_clock(grp);
  }
  return;
}


/* ==== emi1_m_io_write @ 00401c70 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int emi1_m_io_write(int grp,ulong addr,ulong val)

{
  int reg;
  
  emi1_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  switch(addr - *(int *)(emi1_grp + 0x1c)) {
  case 0:
    reg = 0;
    break;
  case 1:
    reg = 1;
    break;
  case 2:
    reg = 8;
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
    reg = 9;
    break;
  case 7:
    reg = 7;
    break;
  default:
    if (addr != 0xffff) {
      return 0;
    }
    reg = 0xc;
    break;
  case 0xe:
    reg = 10;
  }
  _emi1_gruntime = *(int *)(cur_sim + 8) + grp * 8;
  _emi1_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  emi1_flags = *(undefined4 *)(_emi1_gruntime + 4);
  _emi1_regs_slot = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  emi1_regs = *_emi1_regs_slot;
  if (reg != 0xc) {
    emi1_write_reg(reg,val);
    return 0;
  }
  *(uint *)(emi1_regs + 0x30) = *(uint *)(emi1_grp + 0x28) & val;
  return 0;
}


/* ==== emi1_m_io_read @ 00401da0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int emi1_m_io_read(int grp,ulong addr,ulong *out,int side)

{
  int iVar1;
  int extraout_EAX;
  
  emi1_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  _emi1_regs_slot = (undefined4 *)(*(int *)(cur_dev + 8) + grp * 4);
  emi1_regs = *_emi1_regs_slot;
  iVar1 = addr - *(int *)(emi1_grp + 0x1c);
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
    goto switchD_00401de7_caseD_8;
  case 0xe:
    iVar1 = 10;
  }
  _emi1_gruntime = *(int *)(cur_sim + 8) + grp * 8;
  _emi1_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  emi1_flags = *(undefined4 *)(_emi1_gruntime + 4);
  emi1_read_reg(iVar1,out,side);
  iVar1 = extraout_EAX;
switchD_00401de7_caseD_8:
  return iVar1;
}


/* ==== emi1_m_reset @ 00401eb0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void emi1_m_reset(int grp)

{
  int iVar1;
  
  _emi1_gruntime = *(int *)(cur_sim + 8) + grp * 8;
  _emi1_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  emi1_flags = *(undefined4 *)(_emi1_gruntime + 4);
  _emi1_regs_slot = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  emi1_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  emi1_regs = *_emi1_regs_slot;
  iVar1 = *(int *)(cur_dev + 0x18) + *(int *)(emi1_grp + 4) * 0x128;
  *(undefined4 *)(iVar1 + 8) = 0x1fffff00;
  *(undefined4 *)(iVar1 + 0xc) = 0x1fffff00;
  *(undefined4 *)(emi1_regs + 0x28) = 0;
  *(undefined4 *)(emi1_regs + 0x14) = 0;
  *(undefined4 *)(emi1_regs + 4) = 0;
  *(undefined4 *)(emi1_regs + 0xc) = 0x7c1000;
  *(undefined4 *)(emi1_regs + 0x40) = 1;
  emi1_touch_reg(1);
  emi1_touch_reg(5);
  emi1_touch_reg(10);
  emi1_touch_reg(3);
  emi1_clear_pending();
  return;
}


/* ==== emi1_clear_pending @ 00401fa0 ==== */

void emi1_clear_pending(void)

{
  *(undefined4 *)(emi1_regs + 0x9c) = 0;
  *(undefined4 *)(emi1_regs + 0x98) = 0;
  return;
}


/* ==== emi1_m_irq_poll @ 00401fc0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int emi1_m_irq_poll(int grp)

{
  _emi1_regs_slot = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  emi1_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  emi1_regs = *_emi1_regs_slot;
  if (*(int *)(emi1_regs + 0x30) != 0) {
    if (*(int *)(emi1_regs + 0x34) != 0) {
      return *(int *)(emi1_grp + 0x20);
    }
    if (*(int *)(emi1_regs + 0x38) != 0) {
      return *(int *)(emi1_grp + 0x20) + 2;
    }
  }
  return -1;
}


/* ==== emi1_m_irq_ack @ 00402010 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void emi1_m_irq_ack(int grp,ulong vec)

{
  _emi1_regs_slot = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  emi1_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  emi1_regs = *_emi1_regs_slot;
  *(undefined4 *)(emi1_regs + ((vec != *(ulong *)(emi1_grp + 0x20)) + 0xd) * 4) = 0;
  return;
}


/* ==== emi1_write_reg @ 00402060 ==== */

void __cdecl emi1_write_reg(int reg,ulong val)

{
  uint ecsr;
  int iVar1;
  
  ecsr = *(uint *)(emi1_regs + 0xc);
  switch(reg) {
  case 1:
    *(ulong *)(emi1_regs + 0x14) = val & 0xffffff;
    *(undefined4 *)(emi1_regs + 4) = *(undefined4 *)(emi1_regs + 0x14);
    if (((ecsr & 0x800000) == 0) || ((ecsr & 0x20000) != 0)) break;
    if ((*(int *)(emi1_regs + 0x98) != 0) ||
       ((*(int *)(emi1_regs + 0x9c) != 0 || ((ecsr & 0x4000) != 0)))) {
      *(undefined4 *)(emi1_regs + 0x9c) = 1;
      break;
    }
    *(undefined4 *)(emi1_regs + 0x98) = 1;
    iVar1 = 0;
    goto LAB_004021ce;
  case 2:
    *(ulong *)(emi1_regs + 0x18) = val & 0xffffff;
    break;
  case 3:
    val = (ecsr ^ val) & 0xf000 ^ val;
    break;
  case 5:
    *(ulong *)(emi1_regs + 4) = val & 0xffffff;
    *(undefined4 *)(emi1_regs + 0x14) = *(undefined4 *)(emi1_regs + 4);
    if (((ecsr & 0x800000) == 0) || ((ecsr & 0x20000) != 0)) break;
    if ((*(int *)(emi1_regs + 0x98) != 0) ||
       ((*(int *)(emi1_regs + 0x9c) != 0 || ((ecsr & 0x4000) != 0)))) {
      *(undefined4 *)(emi1_regs + 0x9c) = 2;
      break;
    }
    *(undefined4 *)(emi1_regs + 0x98) = 2;
    iVar1 = 4;
LAB_004021ce:
    iVar1 = emi1_next_read_addr(ecsr,iVar1);
    *(int *)(emi1_regs + 0x88) = iVar1;
    break;
  case 6:
    *(ulong *)(emi1_regs + 8) = val & 0xffffff;
    break;
  case 8:
    *(ulong *)(emi1_regs + 0x24) = val & 0xffffff;
    if ((ecsr & 0x800000) == 0) break;
    if (((*(int *)(emi1_regs + 0x98) != 0) || (*(int *)(emi1_regs + 0x9c) != 0)) ||
       ((ecsr & 0x4000) != 0)) {
      *(undefined4 *)(emi1_regs + 0x9c) = 4;
LAB_00402260:
      *(uint *)(emi1_regs + 0xc) = *(uint *)(emi1_regs + 0xc) & 0xffffefff;
      emi1_touch_reg(3);
      break;
    }
    iVar1 = 0;
    *(undefined4 *)(emi1_regs + 0x8c) = *(undefined4 *)(emi1_regs + 0x24);
    *(undefined4 *)(emi1_regs + 0x98) = 4;
    goto LAB_0040223f;
  case 9:
    *(ulong *)(emi1_regs + 0x20) = val & 0xffffff;
    if ((ecsr & 0x800000) == 0) break;
    if (((*(int *)(emi1_regs + 0x98) != 0) || (*(int *)(emi1_regs + 0x9c) != 0)) ||
       ((ecsr & 0x4000) != 0)) {
      *(undefined4 *)(emi1_regs + 0x9c) = 8;
      goto LAB_00402260;
    }
    iVar1 = 4;
    *(undefined4 *)(emi1_regs + 0x8c) = *(undefined4 *)(emi1_regs + 0x20);
    *(undefined4 *)(emi1_regs + 0x98) = 8;
LAB_0040223f:
    iVar1 = emi1_next_write_addr(ecsr,iVar1);
    *(int *)(emi1_regs + 0x88) = iVar1;
  }
  *(uint *)(emi1_regs + reg * 4) =
       *(uint *)(*(int *)(*(int *)(emi1_grp + 0x2c) + 0x2c) + 4 + reg * 0x1c) & val;
  *(uint *)(emi1_flags + reg * 4) = *(uint *)(emi1_flags + reg * 4) | 0xa0000;
  if ((*(uint *)(emi1_flags + reg * 4) & 0x1800000) != 0) {
    io_out_periph_write((emi1_grp - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
  }
  return;
}


/* ==== emi1_read_reg @ 00402310 ==== */

void __cdecl emi1_read_reg(int reg,ulong *out,int side_effect)

{
  int iVar1;
  uint uVar2;
  
  *out = *(ulong *)(emi1_regs + reg * 4);
  if ((side_effect != 0) && (uVar2 = *(uint *)(emi1_regs + 0xc), reg != 1)) {
    if (reg == 2) {
      if (((uVar2 & 0x800000) != 0) && ((uVar2 & 0x20000) != 0)) {
        if ((*(int *)(emi1_regs + 0x98) == 0) &&
           ((*(int *)(emi1_regs + 0x9c) == 0 && ((uVar2 & 0x4000) == 0)))) {
          *(undefined4 *)(emi1_regs + 0x98) = 1;
          iVar1 = emi1_next_read_addr(uVar2,0);
          *(int *)(emi1_regs + 0x88) = iVar1;
        }
        else {
          *(undefined4 *)(emi1_regs + 0x9c) = 1;
        }
      }
      uVar2 = *(uint *)(emi1_regs + 0xc);
      if ((uVar2 & 0x4000) != 0) {
        *(undefined4 *)(emi1_regs + 0x18) = *(undefined4 *)(emi1_regs + 0x2c);
        *(undefined4 *)(emi1_regs + 8) = *(undefined4 *)(emi1_regs + 0x18);
        emi1_touch_reg(2);
        emi1_touch_reg(6);
        *(uint *)(emi1_regs + 0xc) = *(uint *)(emi1_regs + 0xc) & 0xffffbfff;
        emi1_touch_reg(3);
        return;
      }
    }
    else {
      if (reg != 6) {
        return;
      }
      if (((uVar2 & 0x800000) != 0) && ((uVar2 & 0x20000) != 0)) {
        if ((*(int *)(emi1_regs + 0x98) == 0) &&
           ((*(int *)(emi1_regs + 0x9c) == 0 && ((uVar2 & 0x4000) == 0)))) {
          *(undefined4 *)(emi1_regs + 0x98) = 2;
          iVar1 = emi1_next_read_addr(uVar2,4);
          *(int *)(emi1_regs + 0x88) = iVar1;
        }
        else {
          *(undefined4 *)(emi1_regs + 0x9c) = 2;
        }
      }
      uVar2 = *(uint *)(emi1_regs + 0xc);
      if ((uVar2 & 0x4000) != 0) {
        *(undefined4 *)(emi1_regs + 0x18) = *(undefined4 *)(emi1_regs + 0x2c);
        *(undefined4 *)(emi1_regs + 8) = *(undefined4 *)(emi1_regs + 0x18);
        emi1_touch_reg(2);
        emi1_touch_reg(6);
        *(uint *)(emi1_regs + 0xc) = *(uint *)(emi1_regs + 0xc) & 0xffffbfff;
        emi1_touch_reg(3);
        return;
      }
    }
    *(uint *)(emi1_regs + 0xc) = uVar2 & 0xffffdfff;
    emi1_touch_reg(3);
  }
  return;
}


/* ==== emi1_next_read_addr @ 004024b0 ==== */

int __cdecl emi1_next_read_addr(ulong ecsr,int idx)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(emi1_regs + idx * 4);
  iVar2 = *(int *)(emi1_regs + 0x14);
  if ((ecsr & 0x80) != 0) {
    *(uint *)(emi1_regs + idx * 4) = iVar1 + 1U & 0xffffff;
    emi1_touch_reg(idx);
  }
  return iVar1 - iVar2;
}


/* ==== emi1_next_write_addr @ 004024f0 ==== */

int __cdecl emi1_next_write_addr(ulong ecsr,int idx)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(emi1_regs + idx * 4);
  iVar2 = *(int *)(emi1_regs + 0x28);
  if ((ecsr & 0x100) != 0) {
    *(uint *)(emi1_regs + idx * 4) = iVar1 + 1U & 0xffffff;
    emi1_touch_reg(idx);
  }
  return iVar1 - iVar2;
}


/* ==== emi1_clock @ 00402530 ==== */

void __cdecl emi1_clock(int dev)

{
  uint *puVar1;
  ulong *pins;
  uint uVar2;
  ulong uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  ulong uVar7;
  uint uVar8;
  ulong local_4;
  
  uVar8 = *(uint *)(emi1_regs + 0xc);
  uVar5 = *(uint *)(emi1_regs + 0x1c);
  pins = (ulong *)(*(int *)(cur_dev + 0x18) + *(int *)(emi1_grp + 4) * 0x128);
  if (*(int *)(emi1_cpu_ctl + 0xc) == 0) {
    if ((uVar8 & 0x800000) == 0) {
      *(undefined4 *)(emi1_regs + 0x40) = 1;
      if (((uVar5 & 0xc00000) == 0) && ((uVar8 & 0x20) != 0)) {
        pins[2] = pins[2] | 0x3000000;
      }
      *(undefined4 *)(emi1_regs + 0x9c) = 0;
      *(undefined4 *)(emi1_regs + 0x98) = 0;
    }
  }
  else {
    *(undefined4 *)(emi1_regs + 0x40) = 0;
  }
  if ((*(int *)(emi1_cpu_ctl + 0xc) == 0) && (uVar6 = uVar8, (uVar8 & 0x800000) != 0))
  goto LAB_00402629;
  uVar2 = pins[2];
  uVar6 = uVar8 & 0xffff1fff | 0x1000;
  pins[2] = uVar2 | 0x18000000;
  pins[3] = pins[3] & 0xffffff00;
  if ((uVar8 & 0x38) == 0x18) {
    uVar3 = uVar2 | 0x1f800000;
LAB_00402606:
    pins[2] = uVar3;
  }
  else {
    if ((uVar8 & 0x38) == 0x10) {
      uVar3 = uVar2 | 0x1e000000;
      goto LAB_00402606;
    }
    if ((uVar8 & 0x20) == 0) {
      uVar3 = uVar2 | 0x1c000000;
      goto LAB_00402606;
    }
  }
  *(undefined4 *)(emi1_regs + 0x9c) = 0;
  *(undefined4 *)(emi1_regs + 0x98) = 0;
LAB_00402629:
  if (*(int *)(emi1_regs + 0x40) != 0) {
    if (*(int *)(emi1_regs + 0x4c) == 0) {
      if (*(int *)(emi1_regs + 0x48) != 0) {
        *(int *)(emi1_regs + 0x48) = *(int *)(emi1_regs + 0x48) + -1;
      }
      if ((((uVar6 & 0x20) != 0) || ((uVar6 & 0x38) == 0)) && ((uVar5 & 0x800000) != 0)) {
        if ((uVar5 & 0xc0000) == 0) {
          uVar8 = 0x3f;
        }
        else {
          uVar8 = -(uint)((uVar5 & 0x40000) != 0) & 7;
        }
        *(uint *)(emi1_regs + 0x4c) = uVar8;
        if (*(int *)(emi1_regs + 0x48) == 0) {
          *(undefined4 *)(emi1_regs + 0x84) = 1;
          *(uint *)(emi1_regs + 0x48) = (uVar5 & 0xff) + 1;
        }
      }
    }
    else {
      *(int *)(emi1_regs + 0x4c) = *(int *)(emi1_regs + 0x4c) + -1;
    }
  }
  if (((*(int *)(emi1_regs + 0x98) == 0) && (*(int *)(emi1_regs + 0x9c) == 0)) &&
     ((uVar6 & 0x4000) == 0)) {
    uVar6 = uVar6 & 0xffff7fff;
  }
  else {
    uVar6 = uVar6 | 0x8000;
  }
  if ((*(int *)(emi1_regs + 0x40) == 2) || (*(int *)(emi1_regs + 0x40) == 1)) {
    uVar8 = uVar6 & 0x20;
    if (((uVar8 != 0) || ((uVar6 & 0x38) == 0)) && ((uVar5 & 0x100000) != 0)) {
      *(undefined4 *)(emi1_regs + 0x48) = 0;
      *(undefined4 *)(emi1_regs + 0x4c) = 0;
      *(undefined4 *)(emi1_regs + 0x84) = 1;
      *(uint *)(emi1_regs + 0x1c) = uVar5 & 0xffefffff;
      emi1_touch_reg(7);
    }
    if (((*(int *)(emi1_regs + 0x9c) != 0) && (*(int *)(emi1_regs + 0x98) == 0)) &&
       ((uVar6 & 0x4000) == 0)) {
      *(int *)(emi1_regs + 0x98) = *(int *)(emi1_regs + 0x9c);
      *(undefined4 *)(emi1_regs + 0x9c) = 0;
      puVar1 = (uint *)(emi1_regs + 0x98);
      *(undefined4 *)(emi1_regs + 0x8c) = *(undefined4 *)(emi1_regs + 0x20);
      iVar4 = (-(uint)((*puVar1 & 5) != 0) & 0xfffffffc) + 4;
      if ((*(byte *)(emi1_regs + 0x98) & 3) == 0) {
        iVar4 = emi1_next_write_addr(uVar6,iVar4);
      }
      else {
        iVar4 = emi1_next_read_addr(uVar6,iVar4);
      }
      *(int *)(emi1_regs + 0x88) = iVar4;
    }
    if (*(int *)(emi1_regs + 0x84) == 0) {
      if (*(int *)(emi1_regs + 0x98) != 0) {
        *(undefined4 *)(emi1_regs + 0x60) = *(undefined4 *)(emi1_regs + 0x88);
        *(undefined4 *)(emi1_regs + 0x90) = *(undefined4 *)(emi1_regs + 0x60);
        *(uint *)(emi1_regs + 0x44) = uVar6;
        if ((uVar6 & 1) == 0) {
          *(undefined4 *)(emi1_regs + 0x6c) = 0xf;
          *(undefined4 *)(emi1_regs + 0x70) = 4;
        }
        else {
          *(undefined4 *)(emi1_regs + 0x6c) = 0xff;
          *(undefined4 *)(emi1_regs + 0x70) = 8;
        }
        if ((uVar6 & 0x40000) == 0) {
          *(undefined4 *)(emi1_regs + 0x54) = 3;
          *(undefined4 *)(emi1_regs + 0x50) = 1;
        }
        else {
          *(undefined4 *)(emi1_regs + 0x54) = 4;
          *(undefined4 *)(emi1_regs + 0x50) = 3;
        }
        iVar4 = (uVar6 & 7) * 4;
        *(undefined4 *)(emi1_regs + 0x58) = *(undefined4 *)(&emi1_timing_tab_a + iVar4);
        *(undefined4 *)(emi1_regs + 0x5c) = *(undefined4 *)(&emi1_timing_tab_b + iVar4);
        *(uint *)(emi1_regs + 100) =
             (-(uint)((*(uint *)(emi1_regs + 0x98) & 5) != 0) & 0xfffffffc) + 4;
        *(uint *)(emi1_regs + 0x78) = (uVar6 >> 0x13 & 0xf) + 1;
        if ((*(uint *)(emi1_regs + 0x98) & 3) == 0) {
          if ((*(uint *)(emi1_regs + 0x98) & 0xc) != 0) {
            uVar5 = uVar6 >> 1;
            *(uint *)(emi1_regs + 0x40) = (-(uint)(uVar8 != 0) & 0xfffffff3) + 0x1a;
            uVar6 = uVar6 | 0x1000;
            *(uint *)(emi1_regs + 0x2c) =
                 *(uint *)(emi1_regs + 0x8c) >>
                 ((byte)*(undefined4 *)(&emi1_timing_tab_c + (uVar5 & 3) * 4) & 0x1f);
            *(undefined4 *)(emi1_regs + 0x94) = *(undefined4 *)(emi1_regs + 0x2c);
          }
        }
        else {
          uVar3 = *(ulong *)(emi1_regs + 0x90);
          uVar7 = (*(uint *)(emi1_regs + 0x44) & 0x3f) + 0x1d;
          mem_trace_access(uVar7,uVar3,1,0);
          iVar4 = memmap_find(uVar7,uVar3);
          iVar4 = io_in_mem_read(iVar4,uVar3,&local_4);
          if (iVar4 != 0) {
            mem_reg_write(uVar7,uVar3,(ulong)&local_4);
          }
          *(uint *)(emi1_regs + 0x40) = (-(uint)(uVar8 != 0) & 0xffffffee) + 0x19;
          *(int *)(emi1_regs + 0x74) = 0x18 - *(int *)(emi1_regs + 0x70);
          *(undefined4 *)(emi1_regs + 0x2c) = 0;
        }
      }
    }
    else {
      *(undefined4 *)(emi1_regs + 0x40) = 3;
      *(undefined4 *)(emi1_regs + 0x84) = 0;
    }
  }
  switch(*(undefined4 *)(emi1_regs + 0x40)) {
  case 1:
    if ((uVar6 & 0x800000) != 0) {
      *(undefined4 *)(emi1_regs + 0x40) = 2;
    }
    break;
  case 2:
    pins[2] = pins[2] | 0x18000000;
    pins[3] = pins[3] & 0xffffff00;
    pins[1] = pins[1] & 0xffffff00;
    break;
  case 3:
    if ((uVar6 & 0x40000) == 0) {
      *(undefined4 *)(emi1_regs + 0x54) = 4;
      *(undefined4 *)(emi1_regs + 0x50) = 2;
    }
    else {
      *(undefined4 *)(emi1_regs + 0x54) = 6;
      *(undefined4 *)(emi1_regs + 0x50) = 4;
    }
    *(undefined4 *)(emi1_regs + 0x40) = 4;
    pins[2] = pins[2] & 0xfeffffff | 0x1e800000;
    break;
  case 4:
    *(undefined4 *)(emi1_regs + 0x40) = 5;
    pins[2] = pins[2] & 0xfdffffff;
    break;
  case 5:
    *(int *)(emi1_regs + 0x54) = *(int *)(emi1_regs + 0x54) + -1;
    if (*(int *)(emi1_regs + 0x54) == 0) {
      pins[2] = pins[2] | 0x3000000;
      *(undefined4 *)(emi1_regs + 0x40) = 6;
    }
    break;
  case 6:
    *(int *)(emi1_regs + 0x50) = *(int *)(emi1_regs + 0x50) + -1;
    if (*(int *)(emi1_regs + 0x50) == 0) {
      *(uint *)(emi1_regs + 0x40) = ((uVar6 & 0x800000) != 0) + 1;
    }
    break;
  case 7:
    emi1_col_addr(uVar6,*(ulong *)(emi1_regs + 0x60),pins,*(ulong *)(emi1_regs + 0x5c),0);
    *(ulong *)(emi1_regs + 0x7c) = pins[2] >> 8 & 0x7ff;
    pins[2] = pins[2] & 0xedffffff | 0x9000000;
    pins[1] = pins[1] & 0xffffff00;
    pins[3] = pins[3] & 0xffffff00;
    *(undefined4 *)(emi1_regs + 0x68) = *(undefined4 *)(emi1_regs + 0x54);
    *(undefined4 *)(emi1_regs + 0x40) = 8;
    break;
  case 8:
    pins[1] = pins[1] & 0xffffff00;
    pins[3] = pins[3] & 0xffffff00;
    *(int *)(emi1_regs + 0x68) = *(int *)(emi1_regs + 0x68) + -1;
    if (*(int *)(emi1_regs + 0x68) == 0) {
      emi1_col_addr(*(ulong *)(emi1_regs + 0x44),*(ulong *)(emi1_regs + 0x60),pins,
                    *(ulong *)(emi1_regs + 0x5c),1);
      *(ulong *)(emi1_regs + 0x80) = (pins[2] & 0x7ff00) << 3 | *(uint *)(emi1_regs + 0x7c);
      pins[2] = pins[2] & 0xfeffffff;
      *(undefined4 *)(emi1_regs + 0x40) = 9;
    }
    break;
  case 9:
    pins[1] = pins[1] | *(uint *)(emi1_regs + 0x6c);
    emi1_sample_dram_data(pins,dev);
    *(int *)(emi1_regs + 0x68) = *(int *)(emi1_regs + 0x54) + -2;
    *(undefined4 *)(emi1_regs + 0x40) = 10;
    break;
  case 10:
    *(int *)(emi1_regs + 0x68) = *(int *)(emi1_regs + 0x68) + -1;
    if (*(int *)(emi1_regs + 0x68) == 0) {
      pins[2] = pins[2] | 0x1000000;
      emi1_shift_in(pins);
      *(int *)(emi1_regs + 0x58) = *(int *)(emi1_regs + 0x58) + -1;
      if (*(int *)(emi1_regs + 0x58) == 0) {
        if ((uVar6 & 0x2000) == 0) {
          *(undefined4 *)(emi1_regs + 0x18) = *(undefined4 *)(emi1_regs + 0x2c);
          *(undefined4 *)(emi1_regs + 8) = *(undefined4 *)(emi1_regs + 0x18);
          emi1_touch_reg(2);
          emi1_touch_reg(6);
          uVar6 = uVar6 | 0x2000;
        }
        else {
          uVar6 = uVar6 | 0x4000;
        }
        pins[2] = pins[2] | 0x12000000;
        *(undefined4 *)(emi1_regs + 0x40) = 0xb;
      }
      else {
        *(int *)(emi1_regs + 0x5c) = *(int *)(emi1_regs + 0x5c) + 1;
        *(undefined4 *)(emi1_regs + 0x68) = 1;
        *(undefined4 *)(emi1_regs + 0x40) = 8;
      }
    }
    break;
  case 0xb:
    pins[1] = pins[1] & 0xffffff00;
    pins[3] = pins[3] & 0xffffff00;
    *(undefined4 *)(emi1_regs + 0x40) = 0xc;
    *(undefined4 *)(emi1_regs + 0x68) = *(undefined4 *)(emi1_regs + 0x50);
    break;
  case 0xc:
  case 0x11:
    *(int *)(emi1_regs + 0x68) = *(int *)(emi1_regs + 0x68) + -1;
    if (*(int *)(emi1_regs + 0x68) == 0) {
      *(undefined4 *)(emi1_regs + 0x40) = 2;
      *(undefined4 *)(emi1_regs + 0x98) = 0;
    }
    break;
  case 0xd:
    emi1_col_addr(uVar6,*(ulong *)(emi1_regs + 0x60),pins,*(ulong *)(emi1_regs + 0x5c),0);
    *(ulong *)(emi1_regs + 0x7c) = pins[2] >> 8 & 0x7ff;
    pins[2] = pins[2] & 0xf5ffffff | 0x11000000;
    pins[1] = pins[1] & 0xffffff00;
    pins[3] = pins[3] & 0xffffff00;
    *(undefined4 *)(emi1_regs + 0x68) = *(undefined4 *)(emi1_regs + 0x54);
    *(undefined4 *)(emi1_regs + 0x40) = 0xe;
    break;
  case 0xe:
    *(int *)(emi1_regs + 0x68) = *(int *)(emi1_regs + 0x68) + -1;
    if (*(int *)(emi1_regs + 0x68) == 0) {
      pins[3] = pins[3] | *(uint *)(emi1_regs + 0x6c);
      emi1_merge_shift_data(pins);
      emi1_col_addr(*(ulong *)(emi1_regs + 0x44),*(ulong *)(emi1_regs + 0x60),pins,
                    *(ulong *)(emi1_regs + 0x5c),1);
      *(ulong *)(emi1_regs + 0x80) = (pins[2] & 0x7ff00) << 3 | *(uint *)(emi1_regs + 0x7c);
      pins[2] = pins[2] & 0xfeffffff;
      *(int *)(emi1_regs + 0x68) = *(int *)(emi1_regs + 0x54) + -1;
      *(undefined4 *)(emi1_regs + 0x40) = 0xf;
    }
    break;
  case 0xf:
    *(int *)(emi1_regs + 0x68) = *(int *)(emi1_regs + 0x68) + -1;
    if (*(int *)(emi1_regs + 0x68) == 0) {
      pins[2] = pins[2] | 0x1000000;
      emi1_drive_dram_data(pins,dev);
      *(int *)(emi1_regs + 0x58) = *(int *)(emi1_regs + 0x58) + -1;
      if (*(int *)(emi1_regs + 0x58) == 0) {
        uVar3 = *(ulong *)(emi1_regs + 0x90);
        uVar7 = (*(uint *)(emi1_regs + 0x44) & 0x3f) + 0x1d;
        iVar4 = memmap_find(uVar7,uVar3);
        mem_trace_access(uVar7,uVar3,0,0);
        io_out_mem_write(iVar4,uVar3,*(ulong *)(emi1_regs + 0x94));
        pins[2] = pins[2] | 0xa000000;
        *(undefined4 *)(emi1_regs + 0x40) = 0x10;
      }
      else {
        *(uint *)(emi1_regs + 0x2c) =
             *(uint *)(emi1_regs + 0x2c) >> ((byte)*(undefined4 *)(emi1_regs + 0x70) & 0x1f);
        *(int *)(emi1_regs + 0x5c) = *(int *)(emi1_regs + 0x5c) + 1;
        *(undefined4 *)(emi1_regs + 0x68) = 1;
        *(undefined4 *)(emi1_regs + 0x40) = 0xe;
      }
    }
    break;
  case 0x10:
    pins[3] = pins[3] & 0xffffff00;
    *(undefined4 *)(emi1_regs + 0x40) = 0x11;
    *(undefined4 *)(emi1_regs + 0x68) = *(undefined4 *)(emi1_regs + 0x50);
    break;
  case 0x12:
    iVar4 = emi1_next_read_addr(*(ulong *)(emi1_regs + 0x44),*(int *)(emi1_regs + 100));
    *(int *)(emi1_regs + 0x60) = iVar4;
  case 0x19:
    emi1_row_addr(*(ulong *)(emi1_regs + 0x44),*(ulong *)(emi1_regs + 0x60),pins,
                  *(ulong *)(emi1_regs + 0x5c));
    *(uint *)(emi1_regs + 0x80) =
         ((-(uint)((*(uint *)(emi1_regs + 0x44) & 0x18) != 0) & 0x7800000) + 0x7fff00 & pins[2]) >>
         8;
    pins[2] = pins[2] | 0x18000000;
    pins[1] = pins[1] & 0xffffff00;
    pins[3] = pins[3] & 0xffffff00;
    *(undefined4 *)(emi1_regs + 0x40) = 0x13;
    break;
  case 0x13:
    pins[2] = pins[2] & 0xefffffff;
    pins[1] = pins[1] | *(uint *)(emi1_regs + 0x6c);
    emi1_sample_dram_data(pins,dev);
    *(int *)(emi1_regs + 0x68) = *(int *)(emi1_regs + 0x78) + 1;
    *(undefined4 *)(emi1_regs + 0x40) = 0x14;
    break;
  case 0x14:
    *(int *)(emi1_regs + 0x68) = *(int *)(emi1_regs + 0x68) + -1;
    if (*(int *)(emi1_regs + 0x68) == 0) {
      pins[2] = pins[2] | 0x10000000;
      pins[1] = pins[1] & 0xffffff00;
      emi1_shift_in(pins);
      *(int *)(emi1_regs + 0x58) = *(int *)(emi1_regs + 0x58) + -1;
      if (*(int *)(emi1_regs + 0x58) == 0) {
        if ((uVar6 & 0x2000) == 0) {
          *(undefined4 *)(emi1_regs + 0x18) = *(undefined4 *)(emi1_regs + 0x2c);
          *(undefined4 *)(emi1_regs + 8) = *(undefined4 *)(emi1_regs + 0x18);
          emi1_touch_reg(2);
          emi1_touch_reg(6);
          uVar6 = uVar6 | 0x2000;
        }
        else {
          uVar6 = uVar6 | 0x4000;
        }
        *(undefined4 *)(emi1_regs + 0x40) = 2;
        *(undefined4 *)(emi1_regs + 0x98) = 0;
      }
      else {
        *(int *)(emi1_regs + 0x5c) = *(int *)(emi1_regs + 0x5c) + 1;
        *(uint *)(emi1_regs + 0x40) =
             (-(uint)((*(uint *)(emi1_regs + 0x44) & 0x18) != 0) & 7) + 0x12;
      }
    }
    break;
  case 0x15:
    iVar4 = emi1_next_write_addr(uVar6,*(int *)(emi1_regs + 100));
    *(int *)(emi1_regs + 0x60) = iVar4;
  case 0x1a:
    emi1_row_addr(*(ulong *)(emi1_regs + 0x44),*(ulong *)(emi1_regs + 0x60),pins,
                  *(ulong *)(emi1_regs + 0x5c));
    *(uint *)(emi1_regs + 0x80) =
         ((-(uint)((*(uint *)(emi1_regs + 0x44) & 0x18) != 0) & 0x7800000) + 0x7fff00 & pins[2]) >>
         8;
    pins[2] = pins[2] | 0x18000000;
    pins[1] = pins[1] & 0xffffff00;
    pins[3] = pins[3] & 0xffffff00;
    *(undefined4 *)(emi1_regs + 0x40) = 0x16;
    break;
  case 0x16:
    pins[2] = pins[2] & 0xf7ffffff;
    *(undefined4 *)(emi1_regs + 0x40) = 0x17;
    break;
  case 0x17:
    pins[3] = pins[3] | *(uint *)(emi1_regs + 0x6c);
    emi1_merge_shift_data(pins);
    *(undefined4 *)(emi1_regs + 0x68) = *(undefined4 *)(emi1_regs + 0x78);
    *(undefined4 *)(emi1_regs + 0x40) = 0x18;
    break;
  case 0x18:
    *(int *)(emi1_regs + 0x68) = *(int *)(emi1_regs + 0x68) + -1;
    if (*(int *)(emi1_regs + 0x68) == 0) {
      pins[2] = pins[2] | 0x8000000;
      emi1_drive_dram_data(pins,dev);
      *(int *)(emi1_regs + 0x58) = *(int *)(emi1_regs + 0x58) + -1;
      if (*(int *)(emi1_regs + 0x58) == 0) {
        uVar3 = *(ulong *)(emi1_regs + 0x90);
        uVar7 = (*(uint *)(emi1_regs + 0x44) & 0x3f) + 0x1d;
        iVar4 = memmap_find(uVar7,uVar3);
        mem_trace_access(uVar7,uVar3,0,0);
        io_out_mem_write(iVar4,uVar3,*(ulong *)(emi1_regs + 0x94));
        *(undefined4 *)(emi1_regs + 0x40) = 2;
        *(undefined4 *)(emi1_regs + 0x98) = 0;
      }
      else {
        *(int *)(emi1_regs + 0x5c) = *(int *)(emi1_regs + 0x5c) + 1;
        *(uint *)(emi1_regs + 0x40) =
             (-(uint)((*(uint *)(emi1_regs + 0x44) & 0x18) != 0) & 5) + 0x15;
        *(uint *)(emi1_regs + 0x2c) =
             *(uint *)(emi1_regs + 0x2c) >> ((byte)*(undefined4 *)(emi1_regs + 0x70) & 0x1f);
      }
    }
  }
  *(undefined4 *)(emi1_regs + 0x34) = 0;
  *(undefined4 *)(emi1_regs + 0x38) = 0;
  if ((uVar6 & 0x400) == 0) {
    if (((uVar6 & 0x200) != 0) && ((uVar6 & 0x1000) != 0)) {
      *(undefined4 *)(emi1_regs + 0x34) = 1;
    }
  }
  else if ((uVar6 & 0x200) == 0) {
    if ((uVar6 & 0x2000) != 0) {
      *(undefined4 *)(emi1_regs + 0x38) = 1;
    }
  }
  else if ((uVar6 & 0x4000) != 0) {
    *(undefined4 *)(emi1_regs + 0x38) = 1;
  }
  if (uVar6 != *(uint *)(emi1_regs + 0xc)) {
    *(uint *)(emi1_regs + 0xc) = uVar6;
    emi1_touch_reg(3);
  }
  return;
}


/* ==== emi1_row_addr @ 00403330 ==== */

void __cdecl emi1_row_addr(ulong mode,ulong addr,void *pins,ulong ctl)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  uint uVar4;
  
  if ((mode & 0x38) == 0) {
    *(uint *)((int)pins + 8) =
         *(uint *)((int)pins + 8) & 0xff8000ff | (addr & 0x7fff | 0x48000) << 8;
    return;
  }
  uVar1 = 0;
  uVar4 = *(uint *)((int)pins + 8) & 0xf80000ff;
  *(uint *)((int)pins + 8) = uVar4;
  switch(mode & 0x1f) {
  case 8:
  case 0xb:
    *(ulong *)((int)pins + 8) = ((addr & 0x1ffff) << 1 | ctl & 1) << 8 | uVar4;
    return;
  case 9:
    *(ulong *)((int)pins + 8) = (addr & 0x3ffff) << 8 | uVar4;
    return;
  case 10:
  case 0xd:
  case 0xf:
    uVar3 = ctl & 0xff;
    uVar2 = (addr & 0xffff) << 2;
    uVar1 = uVar2;
    if ((ctl & 2) != 0) {
      uVar1 = uVar2 | 1;
      if ((ctl & 1) != 0) {
        *(uint *)((int)pins + 8) = (CONCAT31((int3)(uVar2 >> 8),(char)uVar1) | 2) << 8 | uVar4;
        return;
      }
      break;
    }
    goto LAB_004034df;
  case 0xc:
  case 0xe:
    uVar1 = (addr & 0x7fff) << 3;
    if ((ctl & 4) != 0) {
      uVar1 = uVar1 | 1;
    }
    if ((ctl & 2) != 0) {
      uVar1 = uVar1 | 2;
    }
    if ((ctl & 1) != 0) {
      *(uint *)((int)pins + 8) = (uVar1 | 4) << 8 | uVar4;
      return;
    }
    break;
  case 0x10:
  case 0x13:
    *(ulong *)((int)pins + 8) =
         (addr & 0x1ffff | (-(uint)((ctl & 1) != 0) & 0x20000) + 0x20000) << 8 | uVar4;
    return;
  case 0x11:
    *(ulong *)((int)pins + 8) =
         (addr >> 1 & 0x1ffff | (-(uint)((addr & 1) != 0) & 0x20000) + 0x20000) << 8 | uVar4;
    return;
  case 0x12:
  case 0x15:
  case 0x17:
    *(ulong *)((int)pins + 8) =
         ((addr & 0xffff) << 1 | (-(uint)((ctl & 2) != 0) & 0x20000) + 0x20000 | ctl & 1) << 8 |
         uVar4;
    return;
  case 0x14:
  case 0x16:
    uVar2 = (addr & 0x7fff) << 2;
    uVar1 = uVar2 | (-(uint)((ctl & 4) != 0) & 0x20000) + 0x20000;
    uVar3 = ctl;
    if ((ctl & 2) != 0) {
      uVar1 = CONCAT31((int3)(uVar1 >> 8),(char)uVar2) | 1;
    }
LAB_004034df:
    if ((uVar3 & 1) != 0) {
      *(uint *)((int)pins + 8) = (uVar1 | 2) << 8 | uVar4;
      return;
    }
    break;
  case 0x18:
  case 0x1b:
    if ((addr & 1) == 0) {
      *(ulong *)((int)pins + 8) =
           (addr >> 1 & 0x7fff | (-(uint)((ctl & 1) != 0) & 0x20000) + 0x38000) << 8 | uVar4;
      return;
    }
    *(ulong *)((int)pins + 8) =
         (addr >> 1 & 0x7fff | (-(uint)((ctl & 1) != 0) & 0x8000) + 0x68000) << 8 | uVar4;
    return;
  case 0x19:
    if ((addr & 2) == 0) {
      *(ulong *)((int)pins + 8) =
           (addr >> 2 & 0x7fff | (-(uint)((addr & 1) != 0) & 0x20000) + 0x38000) << 8 | uVar4;
      return;
    }
    *(ulong *)((int)pins + 8) =
         (addr >> 2 & 0x7fff | (-(uint)((addr & 1) != 0) & 0x8000) + 0x68000) << 8 | uVar4;
    return;
  case 0x1a:
  case 0x1d:
  case 0x1f:
    if ((ctl & 1) == 0) {
      *(ulong *)((int)pins + 8) =
           (addr & 0x7fff | (-(uint)((ctl & 2) != 0) & 0x20000) + 0x38000) << 8 | uVar4;
      return;
    }
    *(ulong *)((int)pins + 8) =
         (addr & 0x7fff | (-(uint)((ctl & 2) != 0) & 0x8000) + 0x68000) << 8 | uVar4;
    return;
  case 0x1c:
  case 0x1e:
    if ((ctl & 2) == 0) {
      uVar1 = (-(uint)((ctl & 4) != 0) & 0x20000) + 0x38000;
    }
    else {
      uVar1 = (-(uint)((ctl & 4) != 0) & 0x8000) + 0x68000;
    }
    uVar1 = (addr & 0x3fff) << 1 | ctl & 1 | uVar1;
  }
  *(uint *)((int)pins + 8) = uVar1 << 8 | uVar4;
  return;
}


/* ==== emi1_col_addr @ 004036c0 ==== */

void __cdecl emi1_col_addr(ulong mode,ulong addr,void *pins,ulong ctl,int col)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  uVar2 = *(uint *)((int)pins + 8) & 0xff0000ff | 0x4000000;
  *(uint *)((int)pins + 8) = uVar2;
  if (col == 0) {
    if ((mode & 0x10) != 0) {
      *(ulong *)((int)pins + 8) = (addr & ((mode & 8) << 7 | 0x3ff)) << 8 | uVar2;
      return;
    }
    uVar1 = addr & CONCAT31((int3)(((mode & 8) << 5) >> 8),0xff);
    goto switchD_004036f5_default;
  }
  switch(mode & 0x1f) {
  case 0:
  case 3:
    *(ulong *)((int)pins + 8) = (addr >> 7 & 0xfe | ctl & 1) << 8 | uVar2;
    return;
  case 1:
    *(ulong *)((int)pins + 8) = (addr >> 8 & 0xff) << 8 | uVar2;
    return;
  case 2:
  case 5:
  case 7:
    uVar1 = addr >> 6 & 0xfc;
    break;
  case 4:
  case 6:
    uVar1 = addr >> 5 & 0xf8;
    goto LAB_0040385f;
  case 8:
  case 0xb:
    *(ulong *)((int)pins + 8) = (addr >> 8 & 0x1fe | ctl & 1) << 8 | uVar2;
    return;
  case 9:
    *(ulong *)((int)pins + 8) = (addr >> 9 & 0x1ff) << 8 | uVar2;
    return;
  case 10:
  case 0xd:
  case 0xf:
    uVar1 = addr >> 7 & 0x1fc;
    break;
  case 0xc:
  case 0xe:
    uVar1 = addr >> 6 & 0x1f8;
    goto LAB_0040385f;
  case 0x10:
  case 0x13:
    *(ulong *)((int)pins + 8) = (ctl & 1 | addr >> 9 & 0x3fe) << 8 | uVar2;
    return;
  case 0x11:
    *(ulong *)((int)pins + 8) = (addr >> 10 & 0x3ff) << 8 | uVar2;
    return;
  case 0x12:
  case 0x15:
  case 0x17:
    uVar1 = addr >> 8 & 0x3fc;
    break;
  case 0x14:
  case 0x16:
    uVar1 = addr >> 7 & 0x3f8;
    goto LAB_0040385f;
  case 0x18:
  case 0x1b:
    *(ulong *)((int)pins + 8) = (addr >> 10 & 0x7fe | ctl & 1) << 8 | uVar2;
    return;
  case 0x19:
    *(ulong *)((int)pins + 8) = (addr >> 0xb & 0x7ff) << 8 | uVar2;
    return;
  case 0x1a:
  case 0x1d:
  case 0x1f:
    uVar1 = addr >> 9 & 0x7fc;
    break;
  case 0x1c:
  case 0x1e:
    uVar1 = addr >> 8 & 0x7f8;
LAB_0040385f:
    if ((ctl & 4) != 0) {
      uVar1 = uVar1 | 1;
    }
    if ((ctl & 2) != 0) {
      uVar1 = uVar1 | 2;
    }
    if ((ctl & 1) != 0) {
      *(uint *)((int)pins + 8) = (uVar1 | 4) << 8 | uVar2;
      return;
    }
  default:
    goto switchD_004036f5_default;
  }
  if ((ctl & 2) != 0) {
    uVar1 = uVar1 | 1;
  }
  if ((ctl & 1) != 0) {
    *(uint *)((int)pins + 8) = (uVar1 | 2) << 8 | uVar2;
    return;
  }
switchD_004036f5_default:
  *(uint *)((int)pins + 8) = uVar1 << 8 | uVar2;
  return;
}


/* ==== emi1_sample_dram_data @ 00403950 ==== */

void __cdecl emi1_sample_dram_data(ulong *pins,int dev)

{
  int iVar1;
  uint local_2c;
  ulong local_28 [2];
  ulong local_20;
  
  mdisk_read(*(int *)(cur_dev + 4),0x1c,*(ulong *)(emi1_regs + 0x80),&local_2c);
  iVar1 = io_in_pin_read(dev,local_28);
  if (iVar1 == 0) {
    iVar1 = io_in_timed_pin_read(dev,local_28);
    if (iVar1 == 0) goto LAB_004039ce;
  }
  local_2c = local_20;
  mdisk_write(*(int *)(cur_dev + 4),0x1c,*(ulong *)(emi1_regs + 0x80),local_20,0);
LAB_004039ce:
  mem_trace_access(0x1c,*(ulong *)(emi1_regs + 0x80),1,0);
  *pins = *pins & 0xffffff00 | local_2c & *(uint *)(emi1_regs + 0x6c);
  return;
}


/* ==== emi1_merge_shift_data @ 00403a10 ==== */

void __cdecl emi1_merge_shift_data(ulong *pins)

{
  uint uVar1;
  
  uVar1 = pins[2] & ~*(uint *)(emi1_regs + 0x6c);
  pins[2] = uVar1;
  pins[2] = *(uint *)(emi1_regs + 0x6c) & *(uint *)(emi1_regs + 0x2c) | uVar1;
  return;
}


/* ==== emi1_drive_dram_data @ 00403a40 ==== */

void __cdecl emi1_drive_dram_data(ulong *pins,int dev)

{
  pins = (ulong *)(*(uint *)(emi1_regs + 0x6c) & pins[2]);
  mdisk_write(*(int *)(cur_dev + 4),0x1c,*(ulong *)(emi1_regs + 0x80),(ulong)pins);
  io_out_pin_write(dev,(ulong *)&pins,0);
  mem_trace_access(0x1c,*(ulong *)(emi1_regs + 0x80),0,0);
  return;
}


/* ==== emi1_shift_in @ 00403ab0 ==== */

void __cdecl emi1_shift_in(ulong *pins)

{
  *(uint *)(emi1_regs + 0x2c) =
       (*(uint *)(emi1_regs + 0x6c) & *pins) << ((byte)*(undefined4 *)(emi1_regs + 0x74) & 0x1f) |
       *(uint *)(emi1_regs + 0x2c) >> ((byte)*(undefined4 *)(emi1_regs + 0x70) & 0x1f);
  return;
}


