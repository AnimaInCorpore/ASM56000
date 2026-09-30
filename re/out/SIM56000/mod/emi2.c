/* ==== emi2_m_poke @ 0040b280 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int emi2_m_poke(int grp,int reg,ulong *val)

{
  int iVar1;
  
  _emi2_gruntime = *(int *)(cur_sim + 8) + grp * 8;
  _emi2_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  emi2_flags = *(undefined4 *)(_emi2_gruntime + 4);
  _emi2_regs_slot = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  emi2_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  emi2_regs = *_emi2_regs_slot;
  iVar1 = *(int *)(emi2_grp + 0x2c);
  emi2_regs_alias = emi2_regs;
  if ((reg < *(int *)(iVar1 + 0x28)) &&
     ((*(byte *)(*(int *)(iVar1 + 0x2c) + 0x10 + reg * 0x1c) & 0x40) != 0)) {
    emi2_write_reg(reg,*val);
    emi2_touch_reg(reg);
    return 1;
  }
  if (reg < *(int *)(iVar1 + 0x24)) {
    *(ulong *)(emi2_regs + reg * 4) = *val;
  }
  emi2_touch_reg(reg);
  return 1;
}


/* ==== emi2_touch_reg @ 0040b350 ==== */

void __cdecl emi2_touch_reg(int reg)

{
  int iVar1;
  
  if (reg < *(int *)(*(int *)(emi2_grp + 0x2c) + 0x28)) {
    *(uint *)(emi2_flags + reg * 4) = *(uint *)(emi2_flags + reg * 4) | 0xa0000;
    *(uint *)(emi2_regs + reg * 4) =
         *(uint *)(emi2_regs + reg * 4) &
         *(uint *)(*(int *)(*(int *)(emi2_grp + 0x2c) + 0x2c) + 4 + reg * 0x1c);
    iVar1 = reg * 0x1c + *(int *)(*(int *)(emi2_grp + 0x2c) + 0x2c);
    if ((*(byte *)(iVar1 + 0x10) & 0x60) != 0) {
      mem_trace_fetch(*(int *)(emi2_grp + 0x1c) + *(int *)(iVar1 + 8));
    }
    if ((*(uint *)(emi2_flags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write((emi2_grp - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
    }
  }
  return;
}


/* ==== emi2_m_clock @ 0040b410 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void emi2_m_clock(int grp,int dev)

{
  emi2_cpu_ctl = *(int *)(cur_dev + 0x40);
  if (*(int *)(emi2_cpu_ctl + 8) != 1) {
    _emi2_gruntime = *(int *)(cur_sim + 8) + grp * 8;
    _emi2_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
    emi2_flags = *(undefined4 *)(_emi2_gruntime + 4);
    _emi2_regs_slot = (undefined4 *)(*(int *)(cur_dev + 8) + grp * 4);
    emi2_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
    emi2_regs = *_emi2_regs_slot;
    emi2_regs_alias = emi2_regs;
    emi2_clock(grp);
  }
  return;
}


/* ==== emi2_m_io_write @ 0040b4a0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int emi2_m_io_write(int grp,ulong addr,ulong val)

{
  int reg;
  
  emi2_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  switch(addr - *(int *)(emi2_grp + 0x1c)) {
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
  _emi2_gruntime = *(int *)(cur_sim + 8) + grp * 8;
  _emi2_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  emi2_flags = *(undefined4 *)(_emi2_gruntime + 4);
  _emi2_regs_slot = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  emi2_regs = *_emi2_regs_slot;
  emi2_regs_alias = emi2_regs;
  if (reg != 0xc) {
    emi2_write_reg(reg,val);
    return 0;
  }
  *(uint *)(emi2_regs + 0x30) = *(uint *)(emi2_grp + 0x28) & val;
  return 0;
}


/* ==== emi2_m_io_read @ 0040b5d0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int emi2_m_io_read(int grp,ulong addr,ulong *out,int side)

{
  int iVar1;
  int extraout_EAX;
  
  emi2_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  _emi2_regs_slot = (undefined4 *)(*(int *)(cur_dev + 8) + grp * 4);
  emi2_regs = *_emi2_regs_slot;
  iVar1 = addr - *(int *)(emi2_grp + 0x1c);
  emi2_regs_alias = emi2_regs;
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
    goto switchD_0040b61f_caseD_8;
  case 0xe:
    iVar1 = 10;
  }
  _emi2_gruntime = *(int *)(cur_sim + 8) + grp * 8;
  _emi2_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  emi2_flags = *(undefined4 *)(_emi2_gruntime + 4);
  emi2_read_reg(iVar1,out,side);
  iVar1 = extraout_EAX;
switchD_0040b61f_caseD_8:
  return iVar1;
}


/* ==== emi2_m_reset @ 0040b6e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void emi2_m_reset(int grp)

{
  int iVar1;
  
  _emi2_gruntime = *(int *)(cur_sim + 8) + grp * 8;
  _emi2_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + grp * 4);
  emi2_flags = *(undefined4 *)(_emi2_gruntime + 4);
  _emi2_regs_slot = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  emi2_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  emi2_regs = *_emi2_regs_slot;
  iVar1 = *(int *)(cur_dev + 0x18) + *(int *)(emi2_grp + 4) * 0x128;
  emi2_regs_alias = emi2_regs;
  *(undefined4 *)(iVar1 + 8) = 0x1fffff00;
  *(undefined4 *)(iVar1 + 0xc) = 0x1fffff00;
  *(undefined4 *)(emi2_regs_alias + 0x28) = 0;
  *(undefined4 *)(emi2_regs_alias + 0x14) = 0;
  *(undefined4 *)(emi2_regs_alias + 4) = 0;
  *(undefined4 *)(emi2_regs_alias + 0xc) = 0x7c1000;
  *(undefined4 *)(emi2_regs_alias + 0x4c) = 1;
  emi2_touch_reg(1);
  emi2_touch_reg(5);
  emi2_touch_reg(10);
  emi2_touch_reg(3);
  emi2_clear_pending();
  return;
}


/* ==== emi2_clear_pending @ 0040b7d0 ==== */

void emi2_clear_pending(void)

{
  *(undefined4 *)(emi2_regs_alias + 0x48) = 0;
  *(undefined4 *)(emi2_regs_alias + 0x44) = 0;
  return;
}


/* ==== emi2_m_irq_poll @ 0040b7f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int emi2_m_irq_poll(int grp)

{
  int iVar1;
  
  _emi2_regs_slot = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  emi2_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  emi2_regs = *_emi2_regs_slot;
  emi2_regs_alias = emi2_regs;
  if (*(int *)(emi2_regs + 0x30) != 0) {
    iVar1 = *(int *)(emi2_grp + 0x20);
    if (*(int *)(emi2_regs + 0x3c) != 0) {
      return iVar1 + 4;
    }
    if (*(int *)(emi2_regs + 0x40) != 0) {
      return iVar1 + 6;
    }
    if (*(int *)(emi2_regs + 0x34) != 0) {
      return iVar1;
    }
    if (*(int *)(emi2_regs + 0x38) != 0) {
      return iVar1 + 2;
    }
  }
  return -1;
}


/* ==== emi2_m_irq_ack @ 0040b860 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void emi2_m_irq_ack(int grp,ulong vec)

{
  _emi2_regs_slot = (int *)(*(int *)(cur_dev + 8) + grp * 4);
  emi2_grp = *(int *)(cur_dtype + 0x18) + grp * 0x48;
  emi2_regs = *_emi2_regs_slot;
  emi2_regs_alias = emi2_regs;
  switch(vec - *(int *)(emi2_grp + 0x20)) {
  case 0:
    *(undefined4 *)(emi2_regs + 0x34) = 0;
    return;
  case 2:
    *(undefined4 *)(emi2_regs + 0x38) = 0;
    return;
  case 4:
    *(undefined4 *)(emi2_regs + 0x3c) = 0;
    return;
  case 6:
    *(undefined4 *)(emi2_regs + 0x40) = 0;
  }
  return;
}


/* ==== emi2_write_reg @ 0040b900 ==== */

void __cdecl emi2_write_reg(int reg,ulong val)

{
  uint ecsr;
  int iVar1;
  
  ecsr = *(uint *)(emi2_regs_alias + 0xc);
  switch(reg) {
  case 1:
    *(ulong *)(emi2_regs_alias + 0x14) = val & 0xffffff;
    *(undefined4 *)(emi2_regs_alias + 4) = *(undefined4 *)(emi2_regs_alias + 0x14);
    if (((ecsr & 0x800000) == 0) || ((ecsr & 0x20000) != 0)) break;
    if ((*(int *)(emi2_regs_alias + 0x44) != 0) ||
       ((*(int *)(emi2_regs_alias + 0x48) != 0 || ((ecsr & 0x4000) != 0)))) {
      *(undefined4 *)(emi2_regs_alias + 0x48) = 1;
      break;
    }
    *(undefined4 *)(emi2_regs_alias + 0x44) = 1;
    iVar1 = 0;
    goto LAB_0040ba4d;
  case 2:
    *(ulong *)(emi2_regs_alias + 0x18) = val & 0xffffff;
    break;
  case 3:
    val = (ecsr ^ val) & 0xf000 ^ val;
    break;
  case 5:
    *(ulong *)(emi2_regs_alias + 4) = val & 0xffffff;
    *(undefined4 *)(emi2_regs_alias + 0x14) = *(undefined4 *)(emi2_regs_alias + 4);
    if (((ecsr & 0x800000) == 0) || ((ecsr & 0x20000) != 0)) break;
    if ((*(int *)(emi2_regs_alias + 0x44) != 0) ||
       ((*(int *)(emi2_regs_alias + 0x48) != 0 || ((ecsr & 0x4000) != 0)))) {
      *(undefined4 *)(emi2_regs + 0x48) = 2;
      break;
    }
    *(undefined4 *)(emi2_regs_alias + 0x44) = 2;
    iVar1 = 4;
LAB_0040ba4d:
    iVar1 = emi2_next_read_addr(ecsr,iVar1);
    *(int *)(emi2_regs_alias + 0x94) = iVar1;
    break;
  case 6:
    *(ulong *)(emi2_regs_alias + 8) = val & 0xffffff;
    break;
  case 8:
    *(ulong *)(emi2_regs_alias + 0x24) = val & 0xffffff;
    if ((ecsr & 0x800000) == 0) break;
    if (((*(int *)(emi2_regs_alias + 0x44) != 0) || (*(int *)(emi2_regs_alias + 0x48) != 0)) ||
       ((ecsr & 0x4000) != 0)) {
      *(undefined4 *)(emi2_regs_alias + 0x48) = 4;
LAB_0040bad3:
      *(uint *)(emi2_regs_alias + 0xc) = *(uint *)(emi2_regs_alias + 0xc) & 0xffffefff;
      emi2_touch_reg(3);
      break;
    }
    iVar1 = 0;
    *(undefined4 *)(emi2_regs_alias + 0x98) = *(undefined4 *)(emi2_regs_alias + 0x24);
    *(undefined4 *)(emi2_regs_alias + 0x44) = 4;
    goto LAB_0040bab5;
  case 9:
    *(ulong *)(emi2_regs_alias + 0x20) = val & 0xffffff;
    if ((ecsr & 0x800000) == 0) break;
    if (((*(int *)(emi2_regs_alias + 0x44) != 0) || (*(int *)(emi2_regs_alias + 0x48) != 0)) ||
       ((ecsr & 0x4000) != 0)) {
      *(undefined4 *)(emi2_regs_alias + 0x48) = 8;
      goto LAB_0040bad3;
    }
    iVar1 = 4;
    *(undefined4 *)(emi2_regs_alias + 0x98) = *(undefined4 *)(emi2_regs_alias + 0x20);
    *(undefined4 *)(emi2_regs_alias + 0x44) = 8;
LAB_0040bab5:
    iVar1 = emi2_next_write_addr(ecsr,iVar1);
    *(int *)(emi2_regs_alias + 0x94) = iVar1;
  }
  *(uint *)(emi2_regs + reg * 4) =
       *(uint *)(*(int *)(*(int *)(emi2_grp + 0x2c) + 0x2c) + 4 + reg * 0x1c) & val;
  *(uint *)(emi2_flags + reg * 4) = *(uint *)(emi2_flags + reg * 4) | 0xa0000;
  if ((*(uint *)(emi2_flags + reg * 4) & 0x1800000) != 0) {
    io_out_periph_write((emi2_grp - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
  }
  if ((*(uint *)(emi2_flags + reg * 4) & 0x1800000) != 0) {
    io_out_periph_write((emi2_grp - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
  }
  return;
}


/* ==== emi2_read_reg @ 0040bbc0 ==== */

void __cdecl emi2_read_reg(int reg,ulong *out,int side_effect)

{
  int iVar1;
  uint uVar2;
  
  *out = *(ulong *)(emi2_regs + reg * 4);
  if ((side_effect != 0) && (uVar2 = *(uint *)(emi2_regs_alias + 0xc), reg != 1)) {
    if (reg == 2) {
      if (((uVar2 & 0x800000) != 0) && ((uVar2 & 0x20000) != 0)) {
        if ((*(int *)(emi2_regs_alias + 0x44) == 0) &&
           ((*(int *)(emi2_regs_alias + 0x48) == 0 && ((uVar2 & 0x4000) == 0)))) {
          *(undefined4 *)(emi2_regs_alias + 0x44) = 1;
          iVar1 = emi2_next_read_addr(uVar2,0);
          *(int *)(emi2_regs_alias + 0x94) = iVar1;
        }
        else {
          *(undefined4 *)(emi2_regs_alias + 0x48) = 1;
        }
      }
      uVar2 = *(uint *)(emi2_regs_alias + 0xc);
      if ((uVar2 & 0x4000) != 0) {
        *(undefined4 *)(emi2_regs_alias + 0x18) = *(undefined4 *)(emi2_regs_alias + 0x2c);
        *(undefined4 *)(emi2_regs_alias + 8) = *(undefined4 *)(emi2_regs_alias + 0x18);
        emi2_touch_reg(2);
        emi2_touch_reg(6);
        *(uint *)(emi2_regs_alias + 0xc) = *(uint *)(emi2_regs_alias + 0xc) & 0xffffbfff;
        emi2_touch_reg(3);
        return;
      }
    }
    else {
      if (reg != 6) {
        return;
      }
      if (((uVar2 & 0x800000) != 0) && ((uVar2 & 0x20000) != 0)) {
        if ((*(int *)(emi2_regs_alias + 0x44) == 0) &&
           ((*(int *)(emi2_regs_alias + 0x48) == 0 && ((uVar2 & 0x4000) == 0)))) {
          *(undefined4 *)(emi2_regs_alias + 0x44) = 2;
          iVar1 = emi2_next_read_addr(uVar2,4);
          *(int *)(emi2_regs_alias + 0x94) = iVar1;
        }
        else {
          *(undefined4 *)(emi2_regs_alias + 0x48) = 2;
        }
      }
      uVar2 = *(uint *)(emi2_regs_alias + 0xc);
      if ((uVar2 & 0x4000) != 0) {
        *(undefined4 *)(emi2_regs_alias + 0x18) = *(undefined4 *)(emi2_regs_alias + 0x2c);
        *(undefined4 *)(emi2_regs_alias + 8) = *(undefined4 *)(emi2_regs_alias + 0x18);
        emi2_touch_reg(2);
        emi2_touch_reg(6);
        *(uint *)(emi2_regs_alias + 0xc) = *(uint *)(emi2_regs_alias + 0xc) & 0xffffbfff;
        emi2_touch_reg(3);
        return;
      }
    }
    *(uint *)(emi2_regs_alias + 0xc) = uVar2 & 0xffffdfff;
    emi2_touch_reg(3);
  }
  return;
}


/* ==== emi2_next_read_addr @ 0040bd40 ==== */

int __cdecl emi2_next_read_addr(ulong ecsr,int idx)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(emi2_regs_alias + 0x14);
  iVar2 = *(int *)(emi2_regs + idx * 4);
  if ((ecsr & 0x80) != 0) {
    if ((*(uint *)(emi2_regs_alias + 0xc) & 0x800) != 0) {
      emi2_check_wrap(ecsr,idx);
    }
    *(uint *)(emi2_regs + idx * 4) = *(int *)(emi2_regs + idx * 4) + 1U & 0xffffff;
    emi2_touch_reg(idx);
  }
  return iVar2 - iVar1;
}


/* ==== emi2_check_wrap @ 0040bda0 ==== */

void __cdecl emi2_check_wrap(ulong ecsr,int idx)

{
  byte bVar1;
  uint uVar2;
  
  uVar2 = ecsr >> 3 & 0xf;
  switch(uVar2) {
  case 8:
  case 9:
  case 10:
  case 0xb:
    goto switchD_0040bdd8_caseD_8;
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
    bVar1 = (byte)*(undefined4 *)(&emi2_burst_bits_tab2 + uVar2 * 4);
    break;
  default:
    bVar1 = (byte)*(undefined4 *)
                   (&emi2_burst_bits_tab + ((ecsr & 7 | ecsr >> 0xd & 8) + uVar2 * 8) * 4);
  }
  uVar2 = ~(-1 << (bVar1 & 0x1f));
  if ((*(uint *)(emi2_regs + idx * 4) & uVar2) == uVar2) {
    if (idx == 0) {
      *(undefined4 *)(emi2_regs_alias + 0x3c) = 1;
      return;
    }
    *(undefined4 *)(emi2_regs_alias + 0x40) = 1;
  }
switchD_0040bdd8_caseD_8:
  return;
}


/* ==== emi2_next_write_addr @ 0040be40 ==== */

int __cdecl emi2_next_write_addr(ulong ecsr,int idx)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(emi2_regs_alias + 0x28);
  iVar2 = *(int *)(emi2_regs + idx * 4);
  if ((ecsr & 0x100) != 0) {
    if ((*(uint *)(emi2_regs_alias + 0xc) & 0x800) != 0) {
      emi2_check_wrap(ecsr,idx);
    }
    *(uint *)(emi2_regs + idx * 4) = *(int *)(emi2_regs + idx * 4) + 1U & 0xffffff;
    emi2_touch_reg(idx);
  }
  return iVar2 - iVar1;
}


/* ==== emi2_clock @ 0040bea0 ==== */

void __cdecl emi2_clock(int dev)

{
  uint *puVar1;
  ulong *pins;
  uint uVar2;
  uint uVar3;
  ulong uVar4;
  ulong uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  ulong local_4;
  
  uVar8 = *(uint *)(emi2_regs_alias + 0xc);
  uVar2 = *(uint *)(emi2_regs_alias + 0x1c);
  pins = (ulong *)(*(int *)(cur_dev + 0x18) + *(int *)(emi2_grp + 4) * 0x128);
  if (*(int *)(emi2_cpu_ctl + 0xc) == 0) {
    if ((uVar8 & 0x800000) == 0) {
      *(undefined4 *)(emi2_regs_alias + 0x4c) = 1;
      if (((uVar2 & 0xc00000) == 0) && ((uVar8 & 0x20) != 0)) {
        pins[2] = pins[2] | 0x3000000;
      }
      *(undefined4 *)(emi2_regs_alias + 0x48) = 0;
      *(undefined4 *)(emi2_regs_alias + 0x44) = 0;
    }
  }
  else {
    *(undefined4 *)(emi2_regs_alias + 0x4c) = 0;
  }
  if ((*(int *)(emi2_cpu_ctl + 0xc) != 0) || (uVar7 = uVar8, (uVar8 & 0x800000) == 0)) {
    uVar3 = pins[2];
    uVar7 = uVar8 & 0xffff1fff | 0x1000;
    pins[2] = uVar3 | 0x18000000;
    pins[3] = pins[3] & 0xffffff00;
    if ((uVar8 & 0x78) == 0x18) {
      uVar5 = uVar3 | 0x1f800000;
LAB_0040bf6c:
      pins[2] = uVar5;
    }
    else {
      if ((uVar8 & 0x78) == 0x10) {
        uVar5 = uVar3 | 0x1e000000;
        goto LAB_0040bf6c;
      }
      if ((uVar8 & 0x20) == 0) {
        uVar5 = uVar3 | 0x1c000000;
        goto LAB_0040bf6c;
      }
    }
    *(undefined4 *)(emi2_regs_alias + 0x48) = 0;
    *(undefined4 *)(emi2_regs_alias + 0x44) = 0;
  }
  if (*(int *)(emi2_regs_alias + 0x4c) != 0) {
    if (*(int *)(emi2_regs_alias + 0x58) == 0) {
      if (*(int *)(emi2_regs_alias + 0x54) != 0) {
        *(int *)(emi2_regs_alias + 0x54) = *(int *)(emi2_regs_alias + 0x54) + -1;
      }
      if ((((uVar7 & 0x20) != 0) || ((uVar7 & 0x38) == 0)) && ((uVar2 & 0x800000) != 0)) {
        if ((uVar2 & 0xc0000) == 0) {
          uVar8 = 0x3f;
        }
        else {
          uVar8 = -(uint)((uVar2 & 0x40000) != 0) & 7;
        }
        *(uint *)(emi2_regs_alias + 0x58) = uVar8;
        if (*(int *)(emi2_regs_alias + 0x54) == 0) {
          *(undefined4 *)(emi2_regs_alias + 0x90) = 1;
          *(uint *)(emi2_regs_alias + 0x54) = (uVar2 & 0xff) + 1;
        }
      }
    }
    else {
      *(int *)(emi2_regs_alias + 0x58) = *(int *)(emi2_regs_alias + 0x58) + -1;
    }
  }
  if ((*(int *)(emi2_regs_alias + 0x44) == 0) && (*(int *)(emi2_regs_alias + 0x48) == 0)) {
    uVar7 = uVar7 & 0xffff7fff;
  }
  else {
    uVar7 = uVar7 | 0x8000;
  }
  if ((*(int *)(emi2_regs_alias + 0x4c) == 2) || (*(int *)(emi2_regs_alias + 0x4c) == 1)) {
    uVar8 = uVar7 & 0x20;
    if (((uVar8 != 0) || ((uVar7 & 0x38) == 0)) && ((uVar2 & 0x100000) != 0)) {
      *(undefined4 *)(emi2_regs_alias + 0x54) = 0;
      *(undefined4 *)(emi2_regs_alias + 0x58) = 0;
      *(undefined4 *)(emi2_regs_alias + 0x90) = 1;
      *(uint *)(emi2_regs_alias + 0x1c) = uVar2 & 0xffefffff;
      emi2_touch_reg(7);
    }
    if (((*(int *)(emi2_regs_alias + 0x48) != 0) && (*(int *)(emi2_regs_alias + 0x44) == 0)) &&
       ((uVar7 & 0x4000) == 0)) {
      *(int *)(emi2_regs_alias + 0x44) = *(int *)(emi2_regs_alias + 0x48);
      *(undefined4 *)(emi2_regs_alias + 0x48) = 0;
      puVar1 = (uint *)(emi2_regs_alias + 0x44);
      *(undefined4 *)(emi2_regs_alias + 0x98) = *(undefined4 *)(emi2_regs_alias + 0x20);
      iVar6 = (-(uint)((*puVar1 & 5) != 0) & 0xfffffffc) + 4;
      if ((*(byte *)(emi2_regs_alias + 0x44) & 3) == 0) {
        iVar6 = emi2_next_write_addr(uVar7,iVar6);
      }
      else {
        iVar6 = emi2_next_read_addr(uVar7,iVar6);
      }
      *(int *)(emi2_regs_alias + 0x94) = iVar6;
    }
    if (*(int *)(emi2_regs_alias + 0x90) == 0) {
      if (*(int *)(emi2_regs_alias + 0x44) != 0) {
        *(undefined4 *)(emi2_regs_alias + 0x6c) = *(undefined4 *)(emi2_regs_alias + 0x94);
        *(undefined4 *)(emi2_regs_alias + 0x9c) = *(undefined4 *)(emi2_regs_alias + 0x6c);
        *(uint *)(emi2_regs_alias + 0x50) = uVar7;
        if ((uVar7 & 1) == 0) {
          *(undefined4 *)(emi2_regs_alias + 0x78) = 0xf;
          *(undefined4 *)(emi2_regs_alias + 0x7c) = 4;
        }
        else {
          *(undefined4 *)(emi2_regs_alias + 0x78) = 0xff;
          *(undefined4 *)(emi2_regs_alias + 0x7c) = 8;
        }
        if ((uVar7 & 0x40000) == 0) {
          *(undefined4 *)(emi2_regs_alias + 0x60) = 3;
          *(undefined4 *)(emi2_regs_alias + 0x5c) = 1;
        }
        else {
          *(undefined4 *)(emi2_regs_alias + 0x60) = 4;
          *(undefined4 *)(emi2_regs_alias + 0x5c) = 3;
        }
        iVar6 = (uVar7 >> 0xd & 8 | uVar7 & 7) * 4;
        *(undefined4 *)(emi2_regs_alias + 100) = *(undefined4 *)(&DAT_004b46e0 + iVar6);
        *(undefined4 *)(emi2_regs_alias + 0x68) = *(undefined4 *)(&DAT_004b4720 + iVar6);
        *(uint *)(emi2_regs_alias + 0x70) =
             (-(uint)((*(uint *)(emi2_regs_alias + 0x44) & 5) != 0) & 0xfffffffc) + 4;
        *(uint *)(emi2_regs_alias + 0x84) = (uVar7 >> 0x13 & 0xf) + 1;
        if ((*(uint *)(emi2_regs_alias + 0x44) & 3) == 0) {
          if ((*(uint *)(emi2_regs_alias + 0x44) & 0xc) != 0) {
            *(uint *)(emi2_regs_alias + 0x4c) = (-(uint)(uVar8 != 0) & 0xfffffff6) + 0x19;
            uVar7 = uVar7 | 0x1000;
            *(uint *)(emi2_regs_alias + 0x2c) =
                 *(uint *)(emi2_regs_alias + 0x98) >>
                 ((byte)*(undefined4 *)(&DAT_004b4760 + iVar6) & 0x1f);
            *(undefined4 *)(emi2_regs_alias + 0xa0) = *(undefined4 *)(emi2_regs_alias + 0x2c);
          }
        }
        else {
          uVar4 = *(ulong *)(emi2_regs_alias + 0x9c);
          uVar5 = (*(uint *)(emi2_regs_alias + 0x50) & 0x7f) + 0x1d +
                  (*(uint *)(emi2_regs_alias + 0x50) >> 9 & 0x80);
          mem_trace_access(uVar5,uVar4,1,0);
          iVar6 = memmap_find(uVar5,uVar4);
          iVar6 = io_in_mem_read(iVar6,uVar4,&local_4);
          if (iVar6 != 0) {
            mem_reg_write(uVar5,uVar4,(ulong)&local_4);
          }
          *(uint *)(emi2_regs_alias + 0x4c) = (-(uint)(uVar8 != 0) & 0xfffffff3) + 0x15;
          *(int *)(emi2_regs_alias + 0x80) = 0x18 - *(int *)(emi2_regs_alias + 0x7c);
          *(undefined4 *)(emi2_regs_alias + 0x2c) = 0;
        }
      }
    }
    else {
      *(undefined4 *)(emi2_regs_alias + 0x4c) = 3;
      *(undefined4 *)(emi2_regs_alias + 0x90) = 0;
    }
  }
  switch(*(undefined4 *)(emi2_regs_alias + 0x4c)) {
  case 1:
    if ((uVar7 & 0x800000) != 0) {
      *(undefined4 *)(emi2_regs_alias + 0x4c) = 2;
    }
    break;
  case 2:
    pins[2] = pins[2] | 0x18000000;
    pins[3] = pins[3] & 0xffffff00;
    pins[1] = pins[1] & 0xffffff00;
    break;
  case 3:
    if ((uVar7 & 0x40000) == 0) {
      *(undefined4 *)(emi2_regs_alias + 0x60) = 4;
      *(undefined4 *)(emi2_regs_alias + 0x5c) = 2;
    }
    else {
      *(undefined4 *)(emi2_regs_alias + 0x60) = 6;
      *(undefined4 *)(emi2_regs_alias + 0x5c) = 4;
    }
    *(undefined4 *)(emi2_regs_alias + 0x4c) = 4;
    pins[2] = pins[2] & 0xfeffffff | 0x1e800000;
    break;
  case 4:
    *(undefined4 *)(emi2_regs_alias + 0x4c) = 5;
    pins[2] = pins[2] & 0xfdffffff;
    break;
  case 5:
    *(int *)(emi2_regs_alias + 0x60) = *(int *)(emi2_regs_alias + 0x60) + -1;
    if (*(int *)(emi2_regs_alias + 0x60) == 0) {
      pins[2] = pins[2] | 0x3000000;
      *(undefined4 *)(emi2_regs_alias + 0x4c) = 6;
    }
    break;
  case 6:
    *(int *)(emi2_regs_alias + 0x5c) = *(int *)(emi2_regs_alias + 0x5c) + -1;
    if (*(int *)(emi2_regs_alias + 0x5c) == 0) {
      *(uint *)(emi2_regs_alias + 0x4c) = ((uVar7 & 0x800000) != 0) + 1;
    }
    break;
  case 7:
    iVar6 = emi2_next_read_addr(uVar7,*(int *)(emi2_regs_alias + 0x70));
    *(int *)(emi2_regs_alias + 0x6c) = iVar6;
  case 8:
    emi2_col_addr(uVar7,*(ulong *)(emi2_regs_alias + 0x6c),pins,*(ulong *)(emi2_regs_alias + 0x68),0
                 );
    *(ulong *)(emi2_regs_alias + 0x88) = pins[2] >> 8 & 0x7ff;
    pins[2] = pins[2] & 0xedffffff | 0x9000000;
    pins[1] = pins[1] & 0xffffff00;
    pins[3] = pins[3] & 0xffffff00;
    *(undefined4 *)(emi2_regs_alias + 0x74) = *(undefined4 *)(emi2_regs_alias + 0x60);
    *(undefined4 *)(emi2_regs_alias + 0x4c) = 9;
    break;
  case 9:
    pins[1] = pins[1] & 0xffffff00;
    pins[3] = pins[3] & 0xffffff00;
    *(int *)(emi2_regs_alias + 0x74) = *(int *)(emi2_regs_alias + 0x74) + -1;
    if (*(int *)(emi2_regs_alias + 0x74) == 0) {
      emi2_col_addr(*(ulong *)(emi2_regs_alias + 0x50),*(ulong *)(emi2_regs_alias + 0x6c),pins,
                    *(ulong *)(emi2_regs_alias + 0x68),1);
      *(ulong *)(emi2_regs_alias + 0x8c) =
           (pins[2] & 0x7ff00) << 3 | *(uint *)(emi2_regs_alias + 0x88);
      pins[2] = pins[2] & 0xfeffffff;
      *(undefined4 *)(emi2_regs_alias + 0x4c) = 10;
    }
    break;
  case 10:
    pins[1] = pins[1] | *(uint *)(emi2_regs_alias + 0x78);
    emi2_sample_dram_data(pins,dev);
    *(int *)(emi2_regs_alias + 0x74) = *(int *)(emi2_regs_alias + 0x60) + -2;
    *(undefined4 *)(emi2_regs_alias + 0x4c) = 0xb;
    break;
  case 0xb:
    *(int *)(emi2_regs_alias + 0x74) = *(int *)(emi2_regs_alias + 0x74) + -1;
    if (*(int *)(emi2_regs_alias + 0x74) == 0) {
      pins[2] = pins[2] | 0x1000000;
      emi2_shift_in(pins);
      if (((byte)uVar7 & 0x60) == 0x60) {
        pins[2] = pins[2] | 0x12000000;
        *(undefined4 *)(emi2_regs_alias + 0x4c) = 0xc;
      }
      else {
        *(int *)(emi2_regs_alias + 100) = *(int *)(emi2_regs_alias + 100) + -1;
        if (*(int *)(emi2_regs_alias + 100) == 0) {
          if ((uVar7 & 0x2000) == 0) {
            *(undefined4 *)(emi2_regs_alias + 0x18) = *(undefined4 *)(emi2_regs_alias + 0x2c);
            *(undefined4 *)(emi2_regs_alias + 8) = *(undefined4 *)(emi2_regs_alias + 0x18);
            emi2_touch_reg(2);
            emi2_touch_reg(6);
            uVar7 = uVar7 | 0x2000;
          }
          else {
            uVar7 = uVar7 | 0x4000;
          }
          pins[2] = pins[2] | 0x12000000;
          *(undefined4 *)(emi2_regs_alias + 0x4c) = 0xc;
        }
        else {
          *(int *)(emi2_regs_alias + 0x68) = *(int *)(emi2_regs_alias + 0x68) + 1;
          *(undefined4 *)(emi2_regs_alias + 0x74) = 1;
          *(undefined4 *)(emi2_regs_alias + 0x4c) = 9;
        }
      }
    }
    break;
  case 0xc:
    pins[1] = pins[1] & 0xffffff00;
    pins[3] = pins[3] & 0xffffff00;
    *(undefined4 *)(emi2_regs_alias + 0x4c) = 0xd;
    *(undefined4 *)(emi2_regs_alias + 0x74) = *(undefined4 *)(emi2_regs_alias + 0x5c);
    break;
  case 0xd:
    *(int *)(emi2_regs_alias + 0x74) = *(int *)(emi2_regs_alias + 0x74) + -1;
    if (*(int *)(emi2_regs_alias + 0x74) != 0) break;
    if (((byte)uVar7 & 0x60) == 0x60) {
      *(int *)(emi2_regs_alias + 100) = *(int *)(emi2_regs_alias + 100) + -1;
      if (*(int *)(emi2_regs_alias + 100) != 0) {
        *(undefined4 *)(emi2_regs_alias + 0x4c) = 7;
        break;
      }
      if ((uVar7 & 0x2000) == 0) goto LAB_0040ca8e;
      uVar7 = uVar7 | 0x4000;
    }
    goto LAB_0040cabb;
  case 0xe:
    iVar6 = emi2_next_write_addr(uVar7,*(int *)(emi2_regs_alias + 0x70));
    *(int *)(emi2_regs_alias + 0x6c) = iVar6;
  case 0xf:
    emi2_col_addr(uVar7,*(ulong *)(emi2_regs_alias + 0x6c),pins,*(ulong *)(emi2_regs_alias + 0x68),0
                 );
    *(ulong *)(emi2_regs_alias + 0x88) = pins[2] >> 8 & 0x7ff;
    pins[2] = pins[2] & 0xf5ffffff | 0x11000000;
    pins[1] = pins[1] & 0xffffff00;
    pins[3] = pins[3] & 0xffffff00;
    *(undefined4 *)(emi2_regs_alias + 0x74) = *(undefined4 *)(emi2_regs_alias + 0x60);
    *(undefined4 *)(emi2_regs_alias + 0x4c) = 0x10;
    break;
  case 0x10:
    *(int *)(emi2_regs_alias + 0x74) = *(int *)(emi2_regs_alias + 0x74) + -1;
    if (*(int *)(emi2_regs_alias + 0x74) == 0) {
      pins[3] = pins[3] | *(uint *)(emi2_regs_alias + 0x78);
      emi2_merge_shift_data(pins);
      emi2_col_addr(*(ulong *)(emi2_regs_alias + 0x50),*(ulong *)(emi2_regs_alias + 0x6c),pins,
                    *(ulong *)(emi2_regs_alias + 0x68),1);
      *(ulong *)(emi2_regs_alias + 0x8c) =
           (pins[2] & 0x7ff00) << 3 | *(uint *)(emi2_regs_alias + 0x88);
      pins[2] = pins[2] & 0xfeffffff;
      *(int *)(emi2_regs_alias + 0x74) = *(int *)(emi2_regs_alias + 0x60) + -1;
      *(undefined4 *)(emi2_regs_alias + 0x4c) = 0x11;
    }
    break;
  case 0x11:
    *(int *)(emi2_regs_alias + 0x74) = *(int *)(emi2_regs_alias + 0x74) + -1;
    if (*(int *)(emi2_regs_alias + 0x74) == 0) {
      pins[2] = pins[2] | 0x1000000;
      emi2_drive_dram_data(pins,dev);
      if (*(int *)(emi2_regs_alias + 100) == 1) {
        uVar4 = *(ulong *)(emi2_regs_alias + 0x9c);
        uVar5 = (*(uint *)(emi2_regs_alias + 0x50) & 0x7f) + 0x1d +
                (*(uint *)(emi2_regs_alias + 0x50) >> 9 & 0x80);
        iVar6 = memmap_find(uVar5,uVar4);
        mem_trace_access(uVar5,uVar4,0,0);
        io_out_mem_write(iVar6,uVar4,*(ulong *)(emi2_regs_alias + 0xa0));
      }
      if (((byte)*(undefined4 *)(emi2_regs_alias + 0x50) & 0x60) == 0x60) {
        pins[2] = pins[2] | 0xa000000;
        *(undefined4 *)(emi2_regs_alias + 0x4c) = 0x12;
      }
      else {
        *(int *)(emi2_regs_alias + 100) = *(int *)(emi2_regs_alias + 100) + -1;
        if (*(int *)(emi2_regs_alias + 100) == 0) {
          pins[2] = pins[2] | 0xa000000;
          *(undefined4 *)(emi2_regs_alias + 0x4c) = 0x12;
        }
        else {
          *(uint *)(emi2_regs_alias + 0x2c) =
               *(uint *)(emi2_regs_alias + 0x2c) >>
               ((byte)*(undefined4 *)(emi2_regs_alias + 0x7c) & 0x1f);
          *(int *)(emi2_regs_alias + 0x68) = *(int *)(emi2_regs_alias + 0x68) + 1;
          *(undefined4 *)(emi2_regs_alias + 0x74) = 1;
          *(undefined4 *)(emi2_regs_alias + 0x4c) = 0x10;
        }
      }
    }
    break;
  case 0x12:
    pins[3] = pins[3] & 0xffffff00;
    *(undefined4 *)(emi2_regs_alias + 0x4c) = 0x13;
    *(undefined4 *)(emi2_regs_alias + 0x74) = *(undefined4 *)(emi2_regs_alias + 0x5c);
    break;
  case 0x13:
    *(int *)(emi2_regs_alias + 0x74) = *(int *)(emi2_regs_alias + 0x74) + -1;
    if (*(int *)(emi2_regs_alias + 0x74) != 0) break;
    if ((((byte)*(undefined4 *)(emi2_regs_alias + 0x50) & 0x60) == 0x60) &&
       (*(int *)(emi2_regs_alias + 100) = *(int *)(emi2_regs_alias + 100) + -1,
       *(int *)(emi2_regs_alias + 100) != 0)) {
      *(undefined4 *)(emi2_regs_alias + 0x4c) = 0xe;
      goto LAB_0040cca1;
    }
    goto LAB_0040cabb;
  case 0x14:
    iVar6 = emi2_next_read_addr(*(ulong *)(emi2_regs_alias + 0x50),*(int *)(emi2_regs_alias + 0x70))
    ;
    *(int *)(emi2_regs_alias + 0x6c) = iVar6;
  case 0x15:
    emi2_row_addr(*(ulong *)(emi2_regs_alias + 0x50),*(ulong *)(emi2_regs_alias + 0x6c),pins,
                  *(ulong *)(emi2_regs_alias + 0x68));
    *(uint *)(emi2_regs_alias + 0x8c) =
         ((-(uint)((*(uint *)(emi2_regs_alias + 0x50) & 0x18) != 0) & 0x7800000) + 0x7fff00 &
         pins[2]) >> 8;
    pins[2] = pins[2] | 0x18000000;
    pins[1] = pins[1] & 0xffffff00;
    pins[3] = pins[3] & 0xffffff00;
    *(undefined4 *)(emi2_regs_alias + 0x4c) = 0x16;
    break;
  case 0x16:
    pins[2] = pins[2] & 0xefffffff;
    pins[1] = pins[1] | *(uint *)(emi2_regs_alias + 0x78);
    emi2_sample_dram_data(pins,dev);
    *(int *)(emi2_regs_alias + 0x74) = *(int *)(emi2_regs_alias + 0x84) + 1;
    *(undefined4 *)(emi2_regs_alias + 0x4c) = 0x17;
    break;
  case 0x17:
    *(int *)(emi2_regs_alias + 0x74) = *(int *)(emi2_regs_alias + 0x74) + -1;
    if (*(int *)(emi2_regs_alias + 0x74) != 0) break;
    pins[2] = pins[2] | 0x10000000;
    pins[1] = pins[1] & 0xffffff00;
    emi2_shift_in(pins);
    *(int *)(emi2_regs_alias + 100) = *(int *)(emi2_regs_alias + 100) + -1;
    if (*(int *)(emi2_regs_alias + 100) != 0) {
      *(int *)(emi2_regs_alias + 0x68) = *(int *)(emi2_regs_alias + 0x68) + 1;
      *(uint *)(emi2_regs_alias + 0x4c) = ((*(uint *)(emi2_regs_alias + 0x50) & 0x18) != 0) + 0x14;
      break;
    }
    if ((uVar7 & 0x2000) == 0) {
LAB_0040ca8e:
      *(undefined4 *)(emi2_regs_alias + 0x18) = *(undefined4 *)(emi2_regs_alias + 0x2c);
      *(undefined4 *)(emi2_regs_alias + 8) = *(undefined4 *)(emi2_regs_alias + 0x18);
      emi2_touch_reg(2);
      emi2_touch_reg(6);
      uVar7 = uVar7 | 0x2000;
    }
    else {
      uVar7 = uVar7 | 0x4000;
    }
LAB_0040cabb:
    *(undefined4 *)(emi2_regs_alias + 0x4c) = 2;
    *(undefined4 *)(emi2_regs_alias + 0x44) = 0;
    break;
  case 0x18:
    iVar6 = emi2_next_write_addr(uVar7,*(int *)(emi2_regs_alias + 0x70));
    *(int *)(emi2_regs_alias + 0x6c) = iVar6;
  case 0x19:
    emi2_row_addr(*(ulong *)(emi2_regs_alias + 0x50),*(ulong *)(emi2_regs_alias + 0x6c),pins,
                  *(ulong *)(emi2_regs_alias + 0x68));
    *(uint *)(emi2_regs_alias + 0x8c) =
         ((-(uint)((*(uint *)(emi2_regs_alias + 0x50) & 0x18) != 0) & 0x7800000) + 0x7fff00 &
         pins[2]) >> 8;
    pins[2] = pins[2] | 0x18000000;
    pins[1] = pins[1] & 0xffffff00;
    pins[3] = pins[3] & 0xffffff00;
    *(undefined4 *)(emi2_regs_alias + 0x4c) = 0x1a;
    break;
  case 0x1a:
    pins[2] = pins[2] & 0xf7ffffff;
    *(undefined4 *)(emi2_regs_alias + 0x4c) = 0x1b;
    break;
  case 0x1b:
    pins[3] = pins[3] | *(uint *)(emi2_regs_alias + 0x78);
    emi2_merge_shift_data(pins);
    *(undefined4 *)(emi2_regs_alias + 0x74) = *(undefined4 *)(emi2_regs_alias + 0x84);
    *(undefined4 *)(emi2_regs_alias + 0x4c) = 0x1c;
    break;
  case 0x1c:
    *(int *)(emi2_regs_alias + 0x74) = *(int *)(emi2_regs_alias + 0x74) + -1;
    if (*(int *)(emi2_regs_alias + 0x74) != 0) break;
    pins[2] = pins[2] | 0x8000000;
    emi2_drive_dram_data(pins,dev);
    *(int *)(emi2_regs_alias + 100) = *(int *)(emi2_regs_alias + 100) + -1;
    if (*(int *)(emi2_regs_alias + 100) == 0) {
      uVar4 = *(ulong *)(emi2_regs_alias + 0x9c);
      uVar5 = (*(uint *)(emi2_regs_alias + 0x50) & 0x7f) + 0x1d +
              (*(uint *)(emi2_regs_alias + 0x50) >> 9 & 0x80);
      iVar6 = memmap_find(uVar5,uVar4);
      mem_trace_access(uVar5,uVar4,0,0);
      io_out_mem_write(iVar6,uVar4,*(ulong *)(emi2_regs_alias + 0xa0));
      *(undefined4 *)(emi2_regs_alias + 0x4c) = 2;
      *(undefined4 *)(emi2_regs_alias + 0x44) = 0;
      break;
    }
    *(int *)(emi2_regs_alias + 0x68) = *(int *)(emi2_regs_alias + 0x68) + 1;
    *(uint *)(emi2_regs_alias + 0x4c) = ((*(uint *)(emi2_regs_alias + 0x50) & 0x18) != 0) + 0x18;
LAB_0040cca1:
    *(uint *)(emi2_regs_alias + 0x2c) =
         *(uint *)(emi2_regs_alias + 0x2c) >> ((byte)*(undefined4 *)(emi2_regs_alias + 0x7c) & 0x1f)
    ;
  }
  *(undefined4 *)(emi2_regs_alias + 0x34) = 0;
  *(undefined4 *)(emi2_regs_alias + 0x38) = 0;
  if ((uVar7 & 0x400) == 0) {
    if (((uVar7 & 0x200) != 0) && ((uVar7 & 0x1000) != 0)) {
      *(undefined4 *)(emi2_regs_alias + 0x34) = 1;
    }
  }
  else if ((uVar7 & 0x200) == 0) {
    if ((uVar7 & 0x2000) != 0) {
      *(undefined4 *)(emi2_regs_alias + 0x38) = 1;
    }
  }
  else if ((uVar7 & 0x4000) != 0) {
    *(undefined4 *)(emi2_regs_alias + 0x38) = 1;
  }
  if (uVar7 != *(uint *)(emi2_regs_alias + 0xc)) {
    *(uint *)(emi2_regs_alias + 0xc) = uVar7;
    emi2_touch_reg(3);
  }
  return;
}


/* ==== emi2_row_addr @ 0040cda0 ==== */

void __cdecl emi2_row_addr(ulong mode,ulong addr,void *pins,ulong ctl)

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
    goto LAB_0040cf4f;
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
LAB_0040cf4f:
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


/* ==== emi2_col_addr @ 0040d130 ==== */

void __cdecl emi2_col_addr(ulong mode,ulong addr,void *pins,ulong ctl,int col)

{
  uint uVar1;
  sbyte sVar2;
  uint uVar3;
  
  uVar1 = 0;
  uVar3 = *(uint *)((int)pins + 8) & 0xff0000ff | 0x4000000;
  *(uint *)((int)pins + 8) = uVar3;
  if (((byte)mode & 0x60) == 0x60) {
    sVar2 = ((byte)(mode >> 3) & 3) + 8;
    if (col == 0) {
      *(ulong *)((int)pins + 8) = (~(-1 << sVar2) & addr) << 8 | uVar3;
      return;
    }
    *(ulong *)((int)pins + 8) = (addr >> sVar2 & ~(-1 << sVar2)) << 8 | uVar3;
    return;
  }
  if (col == 0) {
    if ((mode & 0x10) != 0) {
      *(ulong *)((int)pins + 8) = (addr & ((mode & 8) << 7 | 0x3ff)) << 8 | uVar3;
      return;
    }
    uVar1 = addr & CONCAT31((int3)(((mode & 8) << 5) >> 8),0xff);
    goto switchD_0040d1b3_default;
  }
  switch(mode & 0x1f) {
  case 0:
  case 3:
    *(ulong *)((int)pins + 8) = (addr >> 7 & 0xfe | ctl & 1) << 8 | uVar3;
    return;
  case 1:
    *(ulong *)((int)pins + 8) = (addr >> 8 & 0xff) << 8 | uVar3;
    return;
  case 2:
  case 5:
  case 7:
    uVar1 = addr >> 6 & 0xfc;
    break;
  case 4:
  case 6:
    uVar1 = addr >> 5 & 0xf8;
    goto LAB_0040d327;
  case 8:
  case 0xb:
    *(ulong *)((int)pins + 8) = (ctl & 1 | addr >> 8 & 0x1fe) << 8 | uVar3;
    return;
  case 9:
    *(ulong *)((int)pins + 8) = (addr >> 9 & 0x1ff) << 8 | uVar3;
    return;
  case 10:
  case 0xd:
  case 0xf:
    uVar1 = addr >> 7 & 0x1fc;
    break;
  case 0xc:
  case 0xe:
    uVar1 = addr >> 6 & 0x1f8;
    goto LAB_0040d327;
  case 0x10:
  case 0x13:
    *(ulong *)((int)pins + 8) = (ctl & 1 | addr >> 9 & 0x3fe) << 8 | uVar3;
    return;
  case 0x11:
    *(ulong *)((int)pins + 8) = (addr >> 10 & 0x3ff) << 8 | uVar3;
    return;
  case 0x12:
  case 0x15:
  case 0x17:
    uVar1 = addr >> 8 & 0x3fc;
    break;
  case 0x14:
  case 0x16:
    uVar1 = addr >> 7 & 0x3f8;
    goto LAB_0040d327;
  case 0x18:
  case 0x1b:
    *(ulong *)((int)pins + 8) = (addr >> 10 & 0x7fe | ctl & 1) << 8 | uVar3;
    return;
  case 0x19:
    *(ulong *)((int)pins + 8) = (addr >> 0xb & 0x7ff) << 8 | uVar3;
    return;
  case 0x1a:
  case 0x1d:
  case 0x1f:
    uVar1 = addr >> 9 & 0x7fc;
    break;
  case 0x1c:
  case 0x1e:
    uVar1 = addr >> 8 & 0x7f8;
LAB_0040d327:
    if ((ctl & 4) != 0) {
      uVar1 = uVar1 | 1;
    }
    if ((ctl & 2) != 0) {
      uVar1 = uVar1 | 2;
    }
    if ((ctl & 1) != 0) {
      *(uint *)((int)pins + 8) = (uVar1 | 4) << 8 | uVar3;
      return;
    }
  default:
    goto switchD_0040d1b3_default;
  }
  if ((ctl & 2) != 0) {
    uVar1 = uVar1 | 1;
  }
  if ((ctl & 1) != 0) {
    *(uint *)((int)pins + 8) = (uVar1 | 2) << 8 | uVar3;
    return;
  }
switchD_0040d1b3_default:
  *(uint *)((int)pins + 8) = uVar1 << 8 | uVar3;
  return;
}


/* ==== emi2_sample_dram_data @ 0040d410 ==== */

void __cdecl emi2_sample_dram_data(ulong *pins,int dev)

{
  int iVar1;
  uint local_2c;
  ulong local_28 [2];
  ulong local_20;
  
  mdisk_read(*(int *)(cur_dev + 4),0x1c,*(ulong *)(emi2_regs_alias + 0x8c),&local_2c);
  iVar1 = io_in_pin_read(dev,local_28);
  if (iVar1 == 0) {
    iVar1 = io_in_timed_pin_read(dev,local_28);
    if (iVar1 == 0) goto LAB_0040d48e;
  }
  local_2c = local_20;
  mdisk_write(*(int *)(cur_dev + 4),0x1c,*(ulong *)(emi2_regs_alias + 0x8c),local_20,0);
LAB_0040d48e:
  mem_trace_access(0x1c,*(ulong *)(emi2_regs_alias + 0x8c),1,0);
  *pins = *pins & 0xffffff00 | local_2c & *(uint *)(emi2_regs_alias + 0x78);
  return;
}


/* ==== emi2_merge_shift_data @ 0040d4d0 ==== */

void __cdecl emi2_merge_shift_data(ulong *pins)

{
  uint uVar1;
  
  uVar1 = pins[2] & ~*(uint *)(emi2_regs_alias + 0x78);
  pins[2] = uVar1;
  pins[2] = *(uint *)(emi2_regs_alias + 0x78) & *(uint *)(emi2_regs_alias + 0x2c) | uVar1;
  return;
}


/* ==== emi2_drive_dram_data @ 0040d500 ==== */

void __cdecl emi2_drive_dram_data(ulong *pins,int dev)

{
  pins = (ulong *)(pins[2] & *(uint *)(emi2_regs_alias + 0x78));
  mdisk_write(*(int *)(cur_dev + 4),0x1c,*(ulong *)(emi2_regs_alias + 0x8c),(ulong)pins);
  io_out_pin_write(dev,(ulong *)&pins,0);
  mem_trace_access(0x1c,*(ulong *)(emi2_regs_alias + 0x8c),0,0);
  return;
}


/* ==== emi2_shift_in @ 0040d570 ==== */

void __cdecl emi2_shift_in(ulong *pins)

{
  *(uint *)(emi2_regs_alias + 0x2c) =
       (*(uint *)(emi2_regs_alias + 0x78) & *pins) <<
       ((byte)*(undefined4 *)(emi2_regs_alias + 0x80) & 0x1f) |
       *(uint *)(emi2_regs_alias + 0x2c) >> ((byte)*(undefined4 *)(emi2_regs_alias + 0x7c) & 0x1f);
  return;
}


