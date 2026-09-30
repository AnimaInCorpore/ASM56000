/* ==== core_m_peek @ 00403ae0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int core_m_peek(int dev,int reg,ulong *out)

{
  _core_regs_slot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  core_grp = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  core_regs = *_core_regs_slot;
  switch(reg) {
  case 0:
    *out = *(ulong *)(core_regs + 4);
    out[1] = *(ulong *)(core_regs + 8);
    out[2] = *(ulong *)(core_regs + 0xc);
    return 1;
  case 4:
    *out = *(ulong *)(core_regs + 0x14);
    out[1] = *(ulong *)(core_regs + 0x18);
    out[2] = *(ulong *)(core_regs + 0x1c);
    return 1;
  case 0x28:
    *out = *(ulong *)(core_regs + 0x2f8 + (*(uint *)(core_regs + 0x98) & 0xf) * 4);
    return 1;
  case 0x29:
    reg = (*(uint *)(core_regs + 0x98) & 0xf) + 0xd2;
    break;
  case 0x2a:
    *out = *(ulong *)(core_regs + 0xac);
    out[1] = *(ulong *)(core_regs + 0xb0);
    return 1;
  case 0x2d:
    *out = *(ulong *)(core_regs + 0xb8);
    out[1] = *(ulong *)(core_regs + 0xbc);
    return 1;
  }
  *out = *(ulong *)(core_regs + reg * 4);
  return 1;
}


/* ==== core_write_reg @ 00403c50 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl core_write_reg(int dev,int reg,ulong *val)

{
  int iVar1;
  code *pcVar2;
  uint val_00;
  uint uVar3;
  
  uVar3 = *val;
  _core_gruntime = *(int *)(cur_sim + 8) + dev * 8;
  val_00 = uVar3 & 0xffffff;
  _core_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  core_trace = cur_sim + 0x3fc0;
  core_flags = *(undefined4 *)(_core_gruntime + 4);
  _core_regs_slot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  core_grp = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  core_regs = *_core_regs_slot;
  core_ctl = *(int *)(cur_dev + 0x40);
  core_pins = *(undefined4 *)(cur_dev + 0x18);
  core_pins_gpio = *(int *)(cur_dev + 0x18) + 0x6f0;
  core_pins_addr = *(int *)(cur_dev + 0x18) + 0x128;
  core_pins_data = *(int *)(cur_dev + 0x18) + 0x4a0;
  switch(reg) {
  case 0:
    core_set_reg_quiet(1,val_00);
    core_set_reg_quiet(2,val[1]);
    core_set_reg(3,val[2]);
    return 1;
  case 4:
    core_set_reg_quiet(5,val_00);
    core_set_reg_quiet(6,val[1]);
    core_set_reg(7,val[2]);
    return 1;
  case 0x1c:
    if ((*(byte *)(cur_dtype + 8) & 8) != 0) {
      val_00 = val_00 | 4;
    }
    *(uint *)(core_regs + 700) = val_00;
    *(uint *)(core_regs + 0x1b0) = val_00;
    pcVar2 = *(code **)(*(int *)(cur_dtype + 0x28) + 0x10);
    if (pcVar2 != (code *)0x0) {
      (*pcVar2)(val_00);
    }
    break;
  case 0x1d:
    *(undefined4 *)(cur_sim + 0x24) = 0;
    val_00 = uVar3 & 0xffff;
    *(uint *)(cur_dev + 0x1c) = val_00;
    *(uint *)(core_regs + 0x144) = val_00;
    core_reset_pipeline();
    *(undefined4 *)(core_ctl + 0x10) = 0x101;
    break;
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
    *(uint *)(core_regs + 0x11c) = val_00;
    break;
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
    *(uint *)(core_regs + 0x120) = val_00;
    break;
  case 0x28:
    uVar3 = *(uint *)(core_regs + 0x98) & 0xf;
    if (uVar3 == 0) {
      return 1;
    }
    core_touch_reg(0x28);
    reg = uVar3 + 0xbe;
    break;
  case 0x29:
    uVar3 = *(uint *)(core_regs + 0x98) & 0xf;
    if (uVar3 == 0) {
      return 1;
    }
    core_touch_reg(0x29);
    reg = uVar3 + 0xd2;
    break;
  case 0x2a:
    core_set_reg_quiet(0x2b,val_00);
    core_set_reg(0x2c,val[1]);
    return 1;
  case 0x2d:
    core_set_reg_quiet(0x2e,val_00);
    core_set_reg(0x2f,val[1]);
    return 1;
  }
  if ((reg < *(int *)(*(int *)(core_grp + 0x2c) + 0x28)) &&
     (iVar1 = *(int *)(*(int *)(core_grp + 0x2c) + 0x2c) + reg * 0x1c,
     (*(byte *)(iVar1 + 0x10) & 0x40) != 0)) {
    dev_spaces_call_c(*(int *)(core_grp + 0x1c) + *(int *)(iVar1 + 8),*val,1);
    core_touch_reg(reg);
    return 1;
  }
  *(uint *)(core_regs + reg * 4) = val_00;
  core_touch_reg(reg);
  return 1;
}


/* ==== core_m_clock @ 00403f70 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void core_m_clock(int dev)

{
  core_trace = cur_sim + 0x3fc0;
  _core_gruntime = *(int *)(cur_sim + 8) + dev * 8;
  _core_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  core_flags = *(undefined4 *)(_core_gruntime + 4);
  _core_regs_slot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  core_grp = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  core_regs = *_core_regs_slot;
  core_ctl = *(undefined4 *)(cur_dev + 0x40);
  core_pins = *(undefined4 *)(cur_dev + 0x18);
  if ((*(uint *)(cur_dtype + 8) & 0x800) != 0) {
    core_pins_gpio = *(int *)(cur_dev + 0x18) + 0x6f0;
  }
  core_pins_addr = *(int *)(cur_dev + 0x18) + 0x128;
  core_pins_data = *(int *)(cur_dev + 0x18) + 0x4a0;
  core_clock(0);
  return;
}


/* ==== core_m_reset @ 00404040 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void core_m_reset(int dev,int a,int kind,long pinval)

{
  core_trace = cur_sim + 0x3fc0;
  _core_gruntime = *(int *)(cur_sim + 8) + dev * 8;
  _core_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  core_flags = *(undefined4 *)(_core_gruntime + 4);
  _core_regs_slot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  core_grp = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  core_regs = *_core_regs_slot;
  core_ctl = *(int **)(cur_dev + 0x40);
  if (-1 < kind) {
    *core_ctl = kind;
  }
  core_pins = *(undefined4 *)(cur_dev + 0x18);
  if ((*(uint *)(cur_dtype + 8) & 0x800) != 0) {
    core_pins_gpio = *(int *)(cur_dev + 0x18) + 0x6f0;
  }
  core_pins_addr = *(int *)(cur_dev + 0x18) + 0x128;
  core_pins_data = *(int *)(cur_dev + 0x18) + 0x4a0;
  if (a == 1) {
    core_reset();
  }
  core_reset_io(a);
  return;
}


/* ==== core_m_irq_ack @ 00404130 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int core_m_irq_ack(int dev,ulong vec)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  _core_regs_slot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  core_regs = *_core_regs_slot;
  iVar2 = core_regs;
  switch(vec) {
  case 2:
    *(undefined4 *)(core_regs + 0x408) = 0;
    return iVar2;
  case 4:
    *(undefined4 *)(core_regs + 0x40c) = 0;
    return iVar2;
  case 6:
    *(undefined4 *)(core_regs + 0x410) = 0;
    return iVar2;
  case 8:
    *(undefined4 *)(core_regs + 0x414) = 0;
    iVar2 = core_regs;
    *(undefined4 *)(core_regs + 0x2d0) = 0;
    return iVar2;
  case 10:
    *(undefined4 *)(core_regs + 0x418) = 0;
    *(undefined4 *)(core_regs + 0x2d4) = 0;
    return iVar2;
  case 0xc:
  case 0x1e:
    if ((*(byte *)(cur_dtype + 8) & 0x60) != 0) {
      iVar1 = *(int *)(*(int *)(cur_dtype + 0x18) + 0x224);
      iVar3 = (**(code **)(iVar1 + 0x18))(7);
      iVar2 = core_regs;
      if (iVar3 != -1) {
        (**(code **)(iVar1 + 0x1c))(7,0);
        iVar2 = core_regs;
      }
    }
    core_regs = iVar2;
    *(undefined4 *)(iVar2 + 0x400) = 0;
    return iVar2;
  case 0xe:
  case 0x3e:
    *(undefined4 *)(core_regs + 0x404) = 0;
    break;
  case 0x2c:
    *(undefined4 *)(core_regs + 0x444) = 0;
    *(undefined4 *)(core_regs + 0x42c) = 0;
    return iVar2;
  case 0x2e:
    *(undefined4 *)(core_regs + 0x448) = 0;
    iVar2 = core_regs;
    *(undefined4 *)(core_regs + 0x430) = 0;
    return iVar2;
  }
  return iVar2;
}


/* ==== core_set_reg @ 004042b0 ==== */

void __cdecl core_set_reg(int reg,ulong val)

{
  *(ulong *)(core_regs + reg * 4) = val;
  core_touch_reg(reg);
  return;
}


/* ==== core_set_reg_quiet @ 004042d0 ==== */

void __cdecl core_set_reg_quiet(int reg,ulong val)

{
  *(ulong *)(core_regs + reg * 4) = val;
  core_touch_reg_quiet(reg);
  return;
}


/* ==== core_m_io_write @ 004042f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int core_m_io_write(int dev,ulong addr,ulong val)

{
  int reg;
  
  switch(addr & 0xffff) {
  case 0xffe6:
    if ((*(byte *)(cur_dtype + 8) & 0x80) == 0) {
      return 0;
    }
    reg = 0x32;
    val = val ^ (*(uint *)(core_regs + 200) ^ val) & 0x100;
    break;
  case 0xffe7:
    if ((*(byte *)(cur_dtype + 8) & 0x80) == 0) {
      return 0;
    }
    reg = 0x33;
    break;
  default:
    goto switchD_00404319_caseD_ffe8;
  case 0xfffd:
    if ((*(uint *)(cur_dtype + 8) & 0x38ec) == 0) {
      return 0;
    }
    reg = 0x31;
    break;
  case 0xfffe:
    reg = 8;
    break;
  case 0xffff:
    reg = 9;
  }
  core_trace = cur_sim + 0x3fc0;
  _core_gruntime = *(int *)(cur_sim + 8) + dev * 8;
  _core_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  core_flags = *(undefined4 *)(_core_gruntime + 4);
  _core_regs_slot = (int *)(*(int *)(cur_dev + 8) + dev * 4);
  core_grp = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  core_regs = *_core_regs_slot;
  core_ctl = *(undefined4 *)(cur_dev + 0x40);
  core_pins = *(undefined4 *)(cur_dev + 0x18);
  if ((*(uint *)(cur_dtype + 8) & 0x800) != 0) {
    core_pins_gpio = *(int *)(cur_dev + 0x18) + 0x6f0;
  }
  core_pins_addr = *(int *)(cur_dev + 0x18) + 0x128;
  core_pins_data = *(int *)(cur_dev + 0x18) + 0x4a0;
  core_store_reg_masked(reg,val);
switchD_00404319_caseD_ffe8:
  return 0;
}


/* ==== core_m_io_read @ 00404480 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int core_m_io_read(int dev,ulong addr,ulong *out)

{
  int iVar1;
  int extraout_EAX;
  
  iVar1 = (addr & 0xffff) - 0xffe6;
  switch(addr & 0xffff) {
  case 0xffe6:
    if ((*(byte *)(cur_dtype + 8) & 0x80) == 0) {
      return iVar1;
    }
    iVar1 = 0x32;
    break;
  case 0xffe7:
    if ((*(byte *)(cur_dtype + 8) & 0x80) == 0) {
      return iVar1;
    }
    iVar1 = 0x33;
    break;
  default:
    goto switchD_004044a9_caseD_ffe8;
  case 0xfffd:
    if ((*(uint *)(cur_dtype + 8) & 0x38ec) == 0) {
      return iVar1;
    }
    iVar1 = 0x31;
    break;
  case 0xfffe:
    iVar1 = 8;
    break;
  case 0xffff:
    iVar1 = 9;
  }
  core_trace = cur_sim + 0x3fc0;
  _core_gruntime = *(int *)(cur_sim + 8) + dev * 8;
  _core_aux = *(undefined4 *)(*(int *)(cur_itype + 8) + dev * 4);
  core_flags = *(undefined4 *)(_core_gruntime + 4);
  _core_regs_slot = (undefined4 *)(*(int *)(cur_dev + 8) + dev * 4);
  core_grp = *(int *)(cur_dtype + 0x18) + dev * 0x48;
  core_regs = *_core_regs_slot;
  core_ctl = *(undefined4 *)(cur_dev + 0x40);
  core_pins = *(undefined4 *)(cur_dev + 0x18);
  if ((*(uint *)(cur_dtype + 8) & 0x800) != 0) {
    core_pins_gpio = *(int *)(cur_dev + 0x18) + 0x6f0;
  }
  core_pins_addr = *(int *)(cur_dev + 0x18) + 0x128;
  core_pins_data = *(int *)(cur_dev + 0x18) + 0x4a0;
  core_get_reg(iVar1,out);
  iVar1 = extraout_EAX;
switchD_004044a9_caseD_ffe8:
  return iVar1;
}


/* ==== core_store_reg_masked @ 004045f0 ==== */

void __cdecl core_store_reg_masked(int reg,ulong val)

{
  int iVar1;
  
  iVar1 = reg * 4;
  *(uint *)(core_regs + iVar1) =
       *(uint *)(*(int *)(*(int *)(core_grp + 0x2c) + 0x2c) + 4 + reg * 0x1c) & val;
  if ((reg == 0x1c) && ((*(byte *)(cur_dtype + 8) & 8) != 0)) {
    *(uint *)(core_regs + 0x70) = *(uint *)(core_regs + 0x70) | 4;
  }
  if ((*(uint *)(core_flags + iVar1) & 0x1800000) != 0) {
    io_out_periph_write((core_grp - *(int *)(cur_dtype + 0x18)) / 0x48,reg);
  }
  *(uint *)(core_flags + iVar1) = *(uint *)(core_flags + iVar1) | 0xa0000;
  return;
}


/* ==== core_touch_reg @ 00404690 ==== */

void __cdecl core_touch_reg(int reg)

{
  core_touch_reg_ex(reg,0);
  return;
}


/* ==== core_touch_reg_ex @ 004046a0 ==== */

void __cdecl core_touch_reg_ex(int reg,int quiet)

{
  uint *puVar1;
  uint uVar2;
  ulong addr;
  int a;
  int b;
  
  b = -1;
  if (quiet == 0) {
    switch(reg) {
    case 1:
    case 2:
    case 3:
      b = 0;
      break;
    case 5:
    case 6:
    case 7:
      b = 4;
      break;
    case 0x2b:
    case 0x2c:
      b = 0x2a;
      break;
    case 0x2e:
    case 0x2f:
      b = 0x2d;
    }
  }
  if (reg < *(int *)(*(int *)(core_grp + 0x2c) + 0x28)) {
    *(uint *)(core_flags + reg * 4) = *(uint *)(core_flags + reg * 4) | 0xa0000;
    puVar1 = (uint *)(core_regs + reg * 4);
    *puVar1 = *puVar1 & *(uint *)(*(int *)(*(int *)(core_grp + 0x2c) + 0x2c) + 4 + reg * 0x1c);
    switch(reg) {
    case 9:
      if ((*(byte *)(core_regs + 0x24) & 4) == 0) {
        *(undefined4 *)(core_regs + 0x2d0) = 0;
      }
      if ((*(byte *)(core_regs + 0x24) & 0x20) == 0) {
        *(undefined4 *)(core_regs + 0x2d4) = 0;
      }
      break;
    case 0x1d:
      *(uint *)(cur_dev + 0x44) = *(uint *)(cur_dev + 0x44) | 8;
      break;
    case 0x26:
      if ((*(byte *)(core_regs + 0x98) & 0x10) == 0) {
        *(undefined4 *)(core_regs + 0x2a0) = 0;
      }
      else if (*(int *)(core_regs + 0x2a0) == 0) {
        *(undefined4 *)(core_regs + 0x2a0) = 1;
        *(undefined4 *)(core_regs + 0x408) = 4;
      }
      break;
    case 0x32:
      uVar2 = *(uint *)(core_regs + reg * 4);
      if ((uVar2 & 1) == 0) {
        *(uint *)(core_regs + reg * 4) = uVar2 | 0x100;
      }
    }
    a = (core_grp - *(int *)(cur_dtype + 0x18)) / 0x48;
    if ((-1 < b) &&
       (*(uint *)(core_flags + b * 4) = *(uint *)(core_flags + b * 4) | 0xa0000,
       (*(uint *)(core_flags + b * 4) & 0x1800000) != 0)) {
      io_out_periph_write(a,b);
    }
    if ((*(uint *)(core_flags + reg * 4) & 0x1800000) != 0) {
      io_out_periph_write(a,reg);
    }
    addr = *(ulong *)(*(int *)(*(int *)(core_grp + 0x2c) + 0x2c) + 8 + reg * 0x1c);
    if (addr != 0) {
      mem_trace_fetch(addr);
    }
  }
  return;
}


/* ==== core_touch_reg_quiet @ 004048d0 ==== */

void __cdecl core_touch_reg_quiet(int reg)

{
  core_touch_reg_ex(reg,1);
  return;
}


/* ==== core_get_reg @ 004048e0 ==== */

void __cdecl core_get_reg(int reg,ulong *out)

{
  *out = *(ulong *)(core_regs + reg * 4);
  return;
}


/* ==== core_copy_reg @ 00404900 ==== */

void __cdecl core_copy_reg(int dst,int src)

{
  *(undefined4 *)(core_regs + dst * 4) = *(undefined4 *)(core_regs + src * 4);
  core_touch_reg(dst);
  return;
}


/* ==== core_copy_reg_quiet @ 00404920 ==== */

void __cdecl core_copy_reg_quiet(int dst,int src)

{
  *(undefined4 *)(core_regs + dst * 4) = *(undefined4 *)(core_regs + src * 4);
  core_touch_reg_quiet(dst);
  return;
}


/* ==== core_read_copy @ 00404940 ==== */

void __cdecl core_read_copy(ulong src,int dst)

{
  core_touch_read(src);
  *(undefined4 *)(core_regs + dst * 4) = *(undefined4 *)(core_regs + src * 4);
  return;
}


/* ==== core_touch_read @ 00404960 ==== */

void __cdecl core_touch_read(ulong reg)

{
  int a;
  ulong reg_00;
  int iVar1;
  
  reg_00 = reg;
  switch(reg) {
  case 1:
  case 2:
  case 3:
    *core_flags = *core_flags | 0x50000;
    break;
  case 5:
  case 6:
  case 7:
    core_flags[4] = core_flags[4] | 0x50000;
    break;
  case 0x2b:
  case 0x2c:
    core_flags[0x2a] = core_flags[0x2a] | 0x50000;
    break;
  case 0x2e:
  case 0x2f:
    core_flags[0x2d] = core_flags[0x2d] | 0x50000;
  }
  if (((int)reg < *(int *)(*(int *)(core_grp + 0x2c) + 0x28)) &&
     (core_flags[reg] = core_flags[reg] | 0x50000, (core_flags[reg] & 0x400000) != 0)) {
    a = (core_grp - *(int *)(cur_dtype + 0x18)) / 0x48;
    iVar1 = io_in_periph_read(a,reg,&reg);
    if (iVar1 != 0) {
      core_write_reg(a,reg_00,&reg);
    }
  }
  return;
}


/* ==== core_reset_io @ 00404a70 ==== */

void __cdecl core_reset_io(int hard)

{
  if (hard != 0) {
    dev_spaces_call_c(0xffff,0,1);
    *(undefined4 *)(core_regs + 0x414) = 0;
  }
  *(undefined4 *)(core_regs + 0x418) = 0;
  *(undefined4 *)(core_regs + 0x444) = 0;
  *(undefined4 *)(core_regs + 0x448) = 0;
  *(undefined4 *)(core_ctl + 4) = 0;
  return;
}


/* ==== core_reset @ 00404ad0 ==== */

void core_reset(void)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  if ((*(uint *)(cur_dtype + 8) & 0x210) != 0) {
    iVar2 = memmap_find(0xe,0);
    iVar3 = memmap_find(0x18,0x400);
    *(undefined4 *)(iVar2 * 0x10 + 8 + *(int *)(cur_dev + 0xc)) =
         *(undefined4 *)(iVar3 * 0x10 + 8 + *(int *)(cur_dev + 0xc));
  }
  uVar4 = *(uint *)(cur_dtype + 8);
  if ((uVar4 & 0x38ec) != 0) {
    if ((uVar4 & 0xe0) == 0) {
      if ((uVar4 & 4) == 0) {
        if ((uVar4 & 0x800) == 0) {
          uVar4 = 499;
        }
        else {
          uVar4 = (*core_pins & 0x2000000 | 0xd80) >> 7;
        }
      }
      else {
        uVar4 = *core_pins >> 7 & 0x40000;
      }
    }
    else {
      uVar4 = 0;
    }
    core_set_reg(0x31,uVar4);
  }
  if ((*(byte *)(cur_dtype + 8) & 0x80) != 0) {
    core_set_reg(0x33,0);
    core_set_reg(0x32,0x100);
    *(undefined4 *)(core_regs + 0xf0) = 0;
    *(undefined4 *)(core_regs + 0xfc) = 0;
  }
  core_set_reg(0xc,0xffff);
  core_set_reg(0xd,0xffff);
  core_set_reg(0xe,0xffff);
  core_set_reg(0xf,0xffff);
  core_set_reg(0x10,0xffff);
  core_set_reg(0x11,0xffff);
  core_set_reg(0x12,0xffff);
  core_set_reg(0x13,0xffff);
  core_set_reg(0x27,0x300);
  dev_spaces_call_c(0xfffe,0xffff,1);
  uVar4 = *core_ctl & 3;
  if (((*core_ctl & 4) != 0) && (3 < *(uint *)(cur_dtype + 8))) {
    uVar4 = (uint)(byte)((byte)uVar4 | 0x10);
  }
  if ((*(byte *)(cur_dtype + 8) & 8) != 0) {
    uVar4 = uVar4 | 4;
  }
  *(uint *)(core_regs + 0x1b0) = uVar4;
  *(uint *)(core_regs + 0x70) = uVar4;
  *(uint *)(core_regs + 700) = uVar4;
  pcVar1 = *(code **)(*(int *)(cur_dtype + 0x28) + 0x10);
  if (pcVar1 != (code *)0x0) {
    (*pcVar1)(uVar4);
  }
  *(undefined4 *)(core_regs + 0x404) = 0;
  *(undefined4 *)(core_regs + 0x408) = 0;
  *(undefined4 *)(core_regs + 0x410) = 0;
  *(undefined4 *)(core_regs + 0x400) = 0;
  *(undefined4 *)(core_regs + 0x288) = 0;
  *(undefined4 *)(core_regs + 0x40c) = 0;
  if ((*(uint *)(cur_dtype + 8) & 0x3678) == 0) {
    iVar2 = (-(uint)(((byte)*(undefined4 *)(core_regs + 0x70) & 0x13) != 2) & 0xffff2000) + 0xe000;
  }
  else {
    iVar2 = 0;
  }
  *(int *)(core_regs + 0x16c) = iVar2;
  *(int *)(core_regs + 0x170) = iVar2;
  *(int *)(core_regs + 0x144) = iVar2;
  core_set_reg(0x1d,*(ulong *)(core_regs + 0x144));
  *(uint *)(core_flags + 0x70) = *(uint *)(core_flags + 0x70) | 0xa0000;
  *(undefined4 *)(cur_dev + 0x1c) = *(undefined4 *)(core_regs + 0x74);
  *(undefined4 *)(core_regs + 0x1e4) = 0;
  core_set_reg(0x26,0);
  core_pins[3] = core_pins[3] & 0xfffd07ff;
  *(undefined4 *)(core_pins_addr + 4) = 0;
  *(undefined4 *)(core_pins_data + 4) = 0;
  *(undefined4 *)(core_pins_addr + 0xc) = 0;
  *(undefined4 *)(core_pins_data + 0xc) = 0;
  core_pins[2] = core_pins[2] & 0xfffffdff;
  core_pins[2] = core_pins[2] | 0x106fa00;
  if ((*(uint *)(cur_dtype + 8) & 0x800) != 0) {
    *(uint *)(core_pins_gpio + 0xc) = *(uint *)(core_pins_gpio + 0xc) & 0xffffffd8;
    *(uint *)(core_pins_gpio + 8) = *(uint *)(core_pins_gpio + 8) | 0x27;
  }
  if ((*(byte *)(cur_dtype + 8) & 0x60) != 0) {
    core_pins[3] = core_pins[3] | 0x400000;
    core_pins[2] = core_pins[2] | 0x400000;
  }
  core_reset_pipeline();
  return;
}


/* ==== core_reset_pipeline @ 00404e30 ==== */

void core_reset_pipeline(void)

{
  *(undefined4 *)(core_regs + 0x244) = 0;
  *(undefined4 *)(core_regs + 0x3e0) = 0;
  *(undefined4 *)(core_regs + 0x2ac) = 0;
  *(undefined4 *)(core_regs + 0x26c) = 0;
  *(undefined4 *)(core_regs + 0x24c) = 0;
  *(undefined4 *)(core_regs + 0x2a8) = 0;
  *(undefined4 *)(core_regs + 0x2a4) = 0;
  *(undefined4 *)(core_regs + 0x2b0) = 0;
  *(undefined4 *)(core_regs + 0x3dc) = 0;
  *(undefined4 *)(core_regs + 0x224) = 0;
  *(undefined4 *)(core_regs + 0x2f4) = 0;
  *(undefined4 *)(core_regs + 0x264) = 0;
  *(undefined4 *)(core_ctl + 0xc) = 0;
  *(undefined4 *)(core_regs + 0x428) = 0;
  *(undefined4 *)(core_regs + 0x1dc) = 0;
  *(undefined4 *)(core_regs + 0x3d4) = 0;
  *(undefined4 *)(core_regs + 0x3d0) = 0;
  *(undefined4 *)(core_regs + 0x3d8) = 0;
  *(undefined4 *)(core_regs + 0x170) = *(undefined4 *)(core_regs + 0x144);
  *(undefined4 *)(core_regs + 0x1a4) = *(undefined4 *)(core_regs + 0x170);
  *(undefined4 *)(cur_dev + 0x1c) = *(undefined4 *)(core_regs + 0x1a4);
  *(undefined4 *)(core_regs + 0x16c) = *(undefined4 *)(cur_dev + 0x1c);
  *(undefined4 *)(core_regs + 0x274) = 1;
  *(undefined4 *)(core_regs + 0x250) = 1;
  *(undefined4 *)(core_regs + 0x234) = 1;
  *(uint *)(core_regs + 0x22c) = (uint)(*(int *)(core_regs + 0x144) == *(int *)(core_regs + 0x28));
  *(undefined4 *)(core_regs + 0x150) = 0;
  *(undefined4 *)(core_regs + 0xdc) = 0;
  core_fetch_decode();
  core_decode_ctl();
  *(undefined4 *)(core_regs + 0x1e0) = 0;
  *(undefined4 *)(core_ctl + 0x10) = 0x101;
  *(undefined4 *)(core_ctl + 8) = 0;
  *(undefined4 *)(core_regs + 0x248) = 2;
  *(undefined4 *)(cur_dev + 0x20) = 0;
  *(undefined4 *)(cur_dev + 0x24) = 0;
  *core_trace = 0;
  return;
}


/* ==== core_fetch_decode @ 00405000 ==== */

void core_fetch_decode(void)

{
  int iVar1;
  ulong uVar2;
  uint uVar3;
  undefined4 *local_8;
  undefined4 *local_4;
  
  if (*(int *)(core_regs + 0x274) != 0) {
    if (*(int *)(core_regs + 0x74) != *(int *)(core_regs + 0x16c)) {
      core_touch_reg(0x1d);
    }
    *(undefined4 *)(cur_dev + 0x1c) = *(undefined4 *)(core_regs + 0x16c);
    *(undefined4 *)(core_regs + 0x74) = *(undefined4 *)(cur_dev + 0x1c);
    io_out_insn_trace(core_trace[1]);
    if ((*(int *)(core_regs + 0x250) != 0) || (*(int *)(core_regs + 0x254) != 0)) {
      *core_trace = *core_trace + 1;
      core_trace[1] = core_trace[1] + 1;
      if (history_size <= core_trace[1]) {
        core_trace[1] = 0;
      }
      *(undefined4 *)(core_trace[2] + 4 + core_trace[1] * 0x2c) = *(undefined4 *)(core_regs + 0xdc);
      *(undefined4 *)(core_trace[2] + core_trace[1] * 0x2c) = *(undefined4 *)(core_regs + 0x74);
      *(undefined4 *)(core_regs + 0x1e0) = 1;
    }
    iVar1 = insn_validate(*(ulong *)(core_regs + 0xdc),*(ulong *)(cur_dtype + 8));
    if ((iVar1 != 0) && (*(uint *)(cur_dev + 0x44) = *(uint *)(cur_dev + 0x44) | 4, iVar1 != 2)) {
      *(undefined4 *)(core_regs + 0xdc) = 0;
      *(undefined4 *)(core_regs + 0x150) = 0;
    }
    *(undefined4 *)(core_regs + 0x188) = *(undefined4 *)(core_regs + 0xdc);
    *(undefined4 *)(core_regs + 0x184) = *(undefined4 *)(core_regs + 0x188);
    *(undefined4 *)(core_regs + 0x18c) = *(undefined4 *)(core_regs + 0x184);
    *(undefined4 *)(core_regs + 0x214) = *(undefined4 *)(core_regs + 0xdc);
    *(uint *)(core_regs + 0x2cc) = *(uint *)(core_regs + 0x214) & 0x1f;
    *(uint *)(core_regs + 0x2c8) = *(uint *)(core_regs + 0x214) >> 5 & 1;
    if ((*(uint *)(core_regs + 0xdc) & 0x10000) != 0) {
      *(uint *)(core_regs + 0x2c8) = *(uint *)(core_regs + 0x2c8) | 2;
    }
    insn_ea_class(*(ulong *)(core_regs + 0xdc),*(long *)(core_regs + 0x264),
                  (ulong *)(core_regs + 0x2b4),*(ulong *)(cur_dtype + 8));
    uVar3 = *(uint *)(core_regs + 0x2b4) & 0x7000;
    if (uVar3 == 0x1000) {
      uVar3 = *(uint *)(core_regs + 0xdc) & 0x3f | 0xffc0;
    }
    else if (uVar3 == 0x2000) {
      uVar3 = *(uint *)(core_regs + 0xdc) & 0xfff;
    }
    else if (uVar3 == 0x4000) {
      uVar3 = (*(uint *)(core_regs + 0xdc) & 0x3f00 | 0xffc000) >> 8;
    }
    else {
      uVar3 = *(uint *)(core_regs + 0xdc) >> 8 & 0x3f;
    }
    *(uint *)(core_regs + 0x160) = uVar3;
    *(undefined4 *)(core_regs + 0x164) = *(undefined4 *)(core_regs + 0x160);
  }
  uVar2 = insn_class_code(*(ulong *)(core_regs + 0x184),*(long *)(core_regs + 0x264),
                          *(long *)(core_regs + 0x2a4),*(ulong *)(cur_dtype + 8));
  *(ulong *)(core_regs + 0x1d0) = uVar2;
  insn_move_info(*(ulong *)(core_regs + 0x18c),*(long *)(core_regs + 0x264),
                 *(long *)(core_regs + 0x2b0),&local_4,*(ulong *)(cur_dtype + 8));
  *(undefined4 *)(core_regs + 0x218) = *local_4;
  *(undefined4 *)(core_regs + 0x21c) = local_4[1];
  if (*(int *)(core_regs + 0x428) != 0) {
    *(uint *)(core_regs + 0x21c) = *(uint *)(core_regs + 0x21c) & 0xfffffcf7;
  }
  if (*(int *)(core_regs + 0x23c) != 0) {
    *(uint *)(core_regs + 0x21c) = *(uint *)(core_regs + 0x21c) & 0xfffffcff;
  }
  *(undefined4 *)(core_regs + 0x220) = local_4[2];
  insn_exec_info(*(ulong *)(cur_dtype + 8),*(ulong *)(core_regs + 0x188),
                 *(long *)(core_regs + 0x264),*(long *)(core_regs + 0x2a8),&local_8);
  *(undefined4 *)(core_regs + 0x200) = *local_8;
  *(undefined4 *)(core_regs + 0x1fc) = local_8[1];
  *(undefined4 *)(core_regs + 0x208) = local_8[2];
  *(undefined4 *)(core_regs + 0x204) = local_8[3];
  *(undefined4 *)(core_regs + 500) = local_8[4];
  *(undefined4 *)(core_regs + 0x1ec) = local_8[5];
  *(undefined4 *)(core_regs + 0x1f0) = local_8[7];
  *(undefined4 *)(core_regs + 0x1f8) = local_8[6];
  return;
}


/* ==== core_decode_ctl @ 00405440 ==== */

void core_decode_ctl(void)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  if ((*(int *)(core_regs + 0x1dc) != 0) && (*(int *)(core_regs + 0x2c8) == 3)) {
    *(undefined4 *)(core_regs + 500) = 0;
    *(undefined4 *)(core_regs + 0x1dc) = 0;
  }
  if (*(int *)(core_regs + 0x1b0) != *(int *)(core_regs + 700)) {
    pcVar1 = *(code **)(*(int *)(cur_dtype + 0x28) + 0x10);
    if (pcVar1 != (code *)0x0) {
      (*pcVar1)(*(int *)(core_regs + 700));
    }
    *(undefined4 *)(core_regs + 0x1b0) = *(undefined4 *)(core_regs + 700);
  }
  *(undefined4 *)(core_regs + 700) = *(undefined4 *)(core_regs + 0x70);
  *(undefined4 *)(core_regs + 1000) = 0;
  iVar2 = mem_region_of(1,*(ulong *)(core_regs + 0x13c));
  *(int *)(core_regs + 0x3ec) = iVar2;
  if (*(int *)(core_regs + 0x3ec) != 0x12) {
    *(uint *)(core_regs + 1000) = *(uint *)(core_regs + 1000) | 1;
  }
  iVar2 = mem_region_of(2,*(ulong *)(core_regs + 0x140));
  *(int *)(core_regs + 0x3f0) = iVar2;
  if (*(int *)(core_regs + 0x3f0) != 0x17) {
    *(uint *)(core_regs + 1000) = *(uint *)(core_regs + 1000) | 2;
  }
  iVar2 = mem_region_of(0,*(ulong *)(core_regs + 0x144));
  *(int *)(core_regs + 0x3f4) = iVar2;
  if (*(int *)(core_regs + 0x3f4) != 0xd) {
    *(uint *)(core_regs + 1000) = *(uint *)(core_regs + 1000) | 4;
  }
  if (((*(uint *)(core_regs + 500) & 0x30) == 0) || ((*(byte *)(core_regs + 1000) & 1) != 0)) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  *(undefined4 *)(core_regs + 0x39c) = uVar3;
  if (((*(uint *)(core_regs + 500) & 0xc) == 0) || ((*(byte *)(core_regs + 1000) & 2) != 0)) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  *(undefined4 *)(core_regs + 0x3a0) = uVar3;
  if ((((((*(byte *)(core_regs + 0x21c) & 8) == 0) && ((*(uint *)(core_regs + 500) & 2) == 0)) &&
       (*(int *)(core_regs + 0x24c) == 0)) && ((*(uint *)(core_regs + 500) & 1) == 0)) ||
     ((*(byte *)(core_regs + 1000) & 4) != 0)) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  *(undefined4 *)(core_regs + 0x398) = uVar3;
  *(undefined4 *)(core_regs + 0x3bc) = 0;
  *(undefined4 *)(core_regs + 0x3b8) = 0;
  if (((*(byte *)(core_regs + 500) & 0x20) != 0) && (*(int *)(core_regs + 0x39c) == 0)) {
    *(uint *)(core_regs + 0x3b8) = *(uint *)(core_regs + 0x3b8) | 1;
  }
  if (((*(byte *)(core_regs + 500) & 8) != 0) && (*(int *)(core_regs + 0x3a0) == 0)) {
    *(uint *)(core_regs + 0x3b8) = *(uint *)(core_regs + 0x3b8) | 2;
  }
  if (((((*(byte *)(core_regs + 0x21c) & 8) != 0) || ((*(byte *)(core_regs + 500) & 2) != 0)) ||
      (*(int *)(core_regs + 0x24c) != 0)) && (*(int *)(core_regs + 0x398) == 0)) {
    *(uint *)(core_regs + 0x3b8) = *(uint *)(core_regs + 0x3b8) | 4;
  }
  if (((*(byte *)(core_regs + 500) & 0x10) != 0) && (*(int *)(core_regs + 0x39c) == 0)) {
    *(uint *)(core_regs + 0x3bc) = *(uint *)(core_regs + 0x3bc) | 1;
  }
  if (((*(byte *)(core_regs + 500) & 4) != 0) && (*(int *)(core_regs + 0x3a0) == 0)) {
    *(uint *)(core_regs + 0x3bc) = *(uint *)(core_regs + 0x3bc) | 2;
  }
  if (((*(byte *)(core_regs + 500) & 1) != 0) && (*(int *)(core_regs + 0x398) == 0)) {
    *(uint *)(core_regs + 0x3bc) = *(uint *)(core_regs + 0x3bc) | 4;
  }
  uVar4 = *(uint *)(core_regs + 0x1fc);
  if ((uVar4 & 0x80) == 0) {
    uVar4 = uVar4 & 0x3f;
    goto LAB_00405807;
  }
  switch(uVar4 & 0x7f) {
  case 1:
    *(uint *)(core_regs + 0x290) = *(uint *)(core_regs + 0x188) >> 0x10 & 0xc;
    *(uint *)(core_regs + 0x290) =
         (*(uint *)(core_regs + 0x290) | 0x10) >> 2 | *(uint *)(core_regs + 0x290);
    goto LAB_00405812;
  case 2:
    uVar4 = (*(uint *)(core_regs + 0x188) & 0x40000 | 0x100000) >> 0x12;
    break;
  default:
    if ((*(byte *)(core_regs + 0x200) & 0x40) == 0) goto LAB_00405812;
    uVar4 = *(uint *)(core_regs + 0x188) & 7 | 0x10;
    break;
  case 4:
    *(uint *)(core_regs + 0x290) = *(uint *)(core_regs + 0x188) >> 0x10 & 0x3f;
    *(uint *)(core_regs + 0x290) =
         *(uint *)(core_regs + 0x290) & 7 | *(uint *)(core_regs + 0x290) >> 1 & 0x18;
    goto LAB_00405812;
  case 8:
    uVar4 = *(uint *)(core_regs + 0x188) >> 0x10 & 0x1f;
    break;
  case 0x10:
    uVar4 = *(uint *)(core_regs + 0x188) >> 8 & 0x1f;
    break;
  case 0x20:
    uVar4 = *(uint *)(core_regs + 0x188) >> 8 & 0x3f;
    break;
  case 0x40:
    uVar4 = *(uint *)(core_regs + 0x188) & 0x3f;
  }
LAB_00405807:
  *(uint *)(core_regs + 0x290) = uVar4;
LAB_00405812:
  uVar4 = *(uint *)(core_regs + 0x204);
  if ((uVar4 & 0x10) == 0) {
    if ((*(uint *)(core_regs + 0x2b4) & 0x200) == 0) {
      *(uint *)(core_regs + 0x298) = uVar4 & 0xf;
    }
    else {
      *(undefined4 *)(core_regs + 0x298) = 0;
    }
  }
  else {
    uVar4 = uVar4 & 7;
    if (uVar4 == 1) {
      *(uint *)(core_regs + 0x298) = *(uint *)(core_regs + 0x188) >> 0x10 & 3;
      *(uint *)(core_regs + 0x298) =
           *(uint *)(core_regs + 0x298) * 4 | *(uint *)(core_regs + 0x298) | 6;
    }
    else if (uVar4 == 2) {
      *(uint *)(core_regs + 0x298) = (*(uint *)(core_regs + 0x188) & 0x10000 | 0x60000) >> 0x10;
    }
    else if ((uVar4 == 4) &&
            (*(uint *)(core_regs + 0x298) = *(uint *)(core_regs + 0x188) >> 0x10 & 7,
            (*(uint *)(core_regs + 0x188) & 0x100000) != 0)) {
      *(uint *)(core_regs + 0x298) = *(uint *)(core_regs + 0x298) | 8;
    }
  }
  *(undefined4 *)(core_regs + 0x270) = 0;
  if (*(int *)(core_regs + 0x29c) != 0) {
    *(uint *)(core_regs + 0x270) = *(uint *)(core_regs + 0x270) | 2;
  }
  if (*(int *)(core_regs + 0x298) != 0) {
    *(uint *)(core_regs + 0x270) = *(uint *)(core_regs + 0x270) | 0x10;
  }
  if (((*(byte *)(core_regs + 0x1ec) & 1) != 0) || ((*(byte *)(core_regs + 0x294) & 0x30) != 0)) {
    *(uint *)(core_regs + 0x270) = *(uint *)(core_regs + 0x270) | 4;
  }
  if ((*(byte *)(core_regs + 0x290) & 0x30) != 0) {
    *(uint *)(core_regs + 0x270) = *(uint *)(core_regs + 0x270) | 0x20;
  }
  if ((*(uint *)(core_regs + 0x294) != 0) && ((*(uint *)(core_regs + 0x294) & 0x30) == 0)) {
    *(uint *)(core_regs + 0x270) = *(uint *)(core_regs + 0x270) | 1;
  }
  if ((*(int *)(core_regs + 0x290) != 0) && ((*(uint *)(core_regs + 0x270) & 0x20) == 0)) {
    *(uint *)(core_regs + 0x270) = *(uint *)(core_regs + 0x270) | 8;
  }
  if ((*(byte *)(core_regs + 500) & 2) != 0) {
    *(uint *)(core_regs + 0x270) = *(uint *)(core_regs + 0x270) | 0x40;
  }
  if ((*(byte *)(core_regs + 500) & 1) != 0) {
    *(uint *)(core_regs + 0x270) = *(uint *)(core_regs + 0x270) | 0x80;
  }
  uVar4 = *(uint *)(core_regs + 0x270);
  if (((uVar4 & 4) != 0) && ((uVar4 & 0x20) == 0)) {
    *(uint *)(core_regs + 0x270) = uVar4 | 0x100;
  }
  uVar4 = *(uint *)(core_regs + 0x270);
  if (((uVar4 & 0x20) != 0) && ((uVar4 & 4) == 0)) {
    *(uint *)(core_regs + 0x270) = uVar4 | 0x200;
  }
  if (((*(byte *)(core_regs + 500) & 8) != 0) && ((*(uint *)(core_regs + 0x270) & 0x10) == 0)) {
    *(uint *)(core_regs + 0x270) = *(uint *)(core_regs + 0x270) | 0x400;
  }
  if ((((*(byte *)(core_regs + 500) & 4) != 0) ||
      (((*(uint *)(core_regs + 0x270) & 0x10) != 0 && ((*(uint *)(core_regs + 0x270) & 4) != 0))))
     && ((*(uint *)(core_regs + 0x270) & 2) == 0)) {
    *(uint *)(core_regs + 0x270) = *(uint *)(core_regs + 0x270) | 0x800;
  }
  uVar4 = *(uint *)(core_regs + 0x270);
  if ((((uVar4 & 1) != 0) || ((*(byte *)(core_regs + 500) & 0x20) != 0)) && ((uVar4 & 8) == 0)) {
    *(uint *)(core_regs + 0x270) = uVar4 | 0x1000;
  }
  uVar4 = *(uint *)(core_regs + 0x270);
  if ((((*(uint *)(core_regs + 500) & 0x10) != 0 || (uVar4 & 8) != 0) && ((uVar4 & 1) == 0)) &&
     ((*(uint *)(core_regs + 500) & 0x20) == 0)) {
    *(uint *)(core_regs + 0x270) = uVar4 | 0x2000;
  }
  if ((*(uint *)(core_regs + 0x218) & 0x800) != 0) {
    *(undefined4 *)(core_regs + 0x1dc) = 1;
  }
  return;
}


/* ==== core_clock @ 00405b40 ==== */

void __cdecl core_clock(int phase_step)

{
  int iVar1;
  uint *puVar2;
  undefined4 uVar3;
  uint uVar4;
  ulong uVar5;
  int in_stack_00000010;
  undefined4 va0;
  
  if (*(int *)(core_ctl + 8) == 1) {
    chip_reset_regs(1,**(long **)(cur_dev + 0x40));
    core_sample_pins();
    *(uint *)(cur_dev + 0x44) = *(uint *)(cur_dev + 0x44) | 1;
    return;
  }
  if ((*(int *)((int)core_regs + 0xfc) != 0) &&
     (*(int *)((int)core_regs + 0xfc) = *(int *)((int)core_regs + 0xfc) + -1,
     *(int *)((int)core_regs + 0xfc) == 0)) {
    *(undefined4 *)((int)core_regs + 0xf4) = *(undefined4 *)((int)core_regs + 0xf8);
    *(uint *)((int)core_regs + 200) = *(uint *)((int)core_regs + 200) | 0x100;
    core_touch_reg(0x32);
  }
  if ((*(int *)((int)core_regs + 0xf0) != 0) &&
     (*(int *)((int)core_regs + 0xf0) = *(int *)((int)core_regs + 0xf0) + -1,
     *(int *)((int)core_regs + 0xf0) == 0)) {
    *(uint *)((int)core_regs + 200) = *(uint *)((int)core_regs + 200) | 0x100;
    core_touch_reg(0x32);
  }
  iVar1 = *(int *)(core_ctl + 0x10);
  if (0x108 < iVar1) {
    if (iVar1 < 0x100203) {
      if (iVar1 == 0x100202) {
        if ((3 < *(uint *)(cur_dtype + 8)) && (*(uint *)(cur_dtype + 8) != 0x80)) {
          core_pins[2] = core_pins[2] & 0xfffbffff;
        }
        *(undefined4 *)(core_ctl + 0x10) = 0x102;
        core_sample_pins();
        return;
      }
      if (iVar1 != 0x118) goto switchD_004070b6_caseD_100205;
      goto LAB_004068e0;
    }
    switch(iVar1) {
    case 0x100204:
      goto switchD_004070b6_caseD_100204;
    default:
      goto switchD_004070b6_caseD_100205;
    case 0x100210:
      *(undefined4 *)(core_ctl + 0x10) = 0x118;
      core_sample_pins();
      return;
    case 0x100220:
      goto switchD_004070b6_caseD_100220;
    case 0x100280:
      *(uint *)(cur_dev + 0x44) = *(uint *)(cur_dev + 0x44) | 1;
      *(undefined4 *)(core_ctl + 0x10) = 0x108;
      core_sample_pins();
      return;
    }
  }
  if (iVar1 != 0x108) {
    if (iVar1 == 0x101) {
      if (*(int *)((int)core_regs + 0x2f4) == 0) {
        if ((*(byte *)((int)core_regs + 0x2b4) & 0x10) != 0) {
          chip_reset_regs(2,-1);
        }
        if ((*(uint *)((int)core_regs + 0x2b4) & 0x80) != 0) {
          if ((*(uint *)((int)core_regs + 0x2b4) & 0x8000) == 0) {
            *(undefined4 *)((int)core_regs + 0x410) = 4;
          }
          else {
            *(undefined4 *)((int)core_regs + 0x404) = 4;
          }
        }
        *(undefined4 *)((int)core_regs + 0x280) = *(undefined4 *)((int)core_regs + 0x27c);
        if (*(int *)((int)core_regs + 0x284) != 0) {
          *(undefined4 *)((int)core_regs + 0x288) = 1;
        }
        if ((*(int *)((int)core_regs + 0x278) != 0) && (*(int *)((int)core_regs + 0x284) == 0)) {
          *(undefined4 *)((int)core_regs + 0x288) = 0;
        }
        if ((*(uint *)((int)core_regs + 0x2b4) & 0x200) == 0) {
          uVar4 = 0;
        }
        else {
          uVar5 = core_cc_test(*(int *)((int)core_regs + 0x1d4));
          uVar4 = (uint)(uVar5 == 0);
        }
        *(uint *)((int)core_regs + 0x268) = uVar4;
        if ((3 < *(uint *)(cur_dtype + 8)) &&
           ((uVar4 = *(uint *)((int)core_regs + 0xdc), uVar4 == 0x200 ||
            (((uVar4 & 0xfffff0) == 0x300 && (uVar5 = core_cc_test(uVar4 & 0xf), uVar5 != 0)))))) {
          *(uint *)(cur_dev + 0x44) = *(uint *)(cur_dev + 0x44) | 0x10;
        }
        if (*(int *)((int)core_regs + 0x268) == 0) {
          if (((*(byte *)((int)core_regs + 0x270) & 1) != 0) &&
             (core_read_to_bus(*(ulong *)(&regsel_tab + *(int *)((int)core_regs + 0x294) * 4),0x52),
             (*(uint *)((int)core_regs + 0x270) & 0x1000) != 0)) {
            *(undefined4 *)((int)core_regs + 0x180) = *(undefined4 *)((int)core_regs + 0x148);
          }
          if ((*(byte *)((int)core_regs + 0x270) & 2) != 0) {
            core_read_to_bus(*(ulong *)(&regsel_tab + *(int *)((int)core_regs + 0x29c) * 4),0x53);
          }
          if ((*(byte *)((int)core_regs + 0x270) & 4) != 0) {
            if ((*(byte *)((int)core_regs + 0x1ec) & 1) == 0) {
              core_read_to_bus(*(ulong *)(&regsel_tab + *(int *)((int)core_regs + 0x294) * 4),0x55);
            }
            else {
              *(undefined4 *)((int)core_regs + 0x154) = *(undefined4 *)((int)core_regs + 0x1ac);
              if ((*(byte *)((int)core_regs + 0x2b4) & 0x20) != 0) {
                *(uint *)((int)core_regs + 0x154) =
                     *(uint *)((int)core_regs + 0x154) |
                     *(uint *)((int)core_regs +
                              *(int *)(&regsel_tab + *(int *)((int)core_regs + 0x290) * 4) * 4);
              }
              if ((*(byte *)((int)core_regs + 0x2b4) & 0x40) != 0) {
                *(uint *)((int)core_regs + 0x154) =
                     *(uint *)((int)core_regs + 0x154) &
                     *(uint *)((int)core_regs +
                              *(int *)(&regsel_tab + *(int *)((int)core_regs + 0x290) * 4) * 4);
              }
            }
            if ((*(uint *)((int)core_regs + 0x270) & 0x100) != 0) {
              *(undefined4 *)((int)core_regs + 0x180) = *(undefined4 *)((int)core_regs + 0x154);
            }
          }
          if ((*(uint *)((int)core_regs + 0x2b4) & 0x200) != 0) {
            alu_decode((*(uint *)((int)core_regs + 0x214) & 0x300f8) + 1,
                       (long *)((int)core_regs + 0x1b8));
            alu_execute(core_regs);
          }
        }
        if (((*(byte *)((int)core_regs + 0x218) & 8) != 0) &&
           ((*(uint *)((int)core_regs + 0x2b4) & 0x800) == 0)) {
          alu_decode(*(ulong *)((int)core_regs + 0x214),(long *)((int)core_regs + 0x1b8));
          alu_execute(core_regs);
        }
        if (*(int *)((int)core_regs + 0x1d8) != 0) {
          if ((*(uint *)((int)core_regs + 0x2b4) & 0x800) == 0) {
            uVar4 = *(uint *)((int)core_regs + 0x1d0) & 8;
            core_agu_writeback(*(ulong *)((int)core_regs + 0x20c),uVar4);
            if ((*(uint *)((int)core_regs + 0x184) & 0x800000) != 0) {
              core_agu_writeback(*(ulong *)((int)core_regs + 0x210),uVar4);
            }
          }
          else {
            alu_shift1(core_regs);
          }
        }
        if ((*(byte *)((int)core_regs + 0x21c) & 0x20) != 0) {
          *(undefined4 *)((int)core_regs + 0x168) = *(undefined4 *)((int)core_regs + 0x170);
          *(undefined4 *)((int)core_regs + 0x1a8) = *(undefined4 *)((int)core_regs + 0x150);
        }
        if ((*(byte *)((int)core_regs + 0x21c) & 0x40) != 0) {
          *(undefined4 *)((int)core_regs + 0x428) = 1;
        }
        if ((*(uint *)((int)core_regs + 0x21c) & 0x2000) != 0) {
          core_ss_dec();
        }
      }
    }
    else if (iVar1 != 0x102) {
      core_sample_pins();
      return;
    }
    *(undefined4 *)(core_pins_data + 0xc) = 0;
    *(undefined4 *)(core_pins_data + 4) = 0;
    if ((*(uint *)(cur_dtype + 8) & 0x40) == 0) {
      if (((core_pins[2] & 0x200) == 0) &&
         (((*(uint *)(cur_dtype + 8) & 3) == 0 || ((*(byte *)((int)core_regs + 0x1b0) & 0x80) == 0))
         )) {
        uVar3 = 1;
      }
      else {
        uVar3 = 0;
      }
      *(undefined4 *)((int)core_regs + 0x2f0) = uVar3;
    }
    else {
      *(undefined4 *)((int)core_regs + 0x2f0) = 0;
    }
    if ((*(uint *)(cur_dtype + 8) & 0x800) != 0) {
      if (((*core_pins_gpio & 8) != 0) || ((*core_pins_gpio & 0x40) == 0)) {
        core_pins_gpio[2] = core_pins_gpio[2] | 0x25;
        core_pins_gpio[3] = core_pins_gpio[3] & 0xffffffda;
        core_pins[3] = core_pins[3] & 0xffffcfff;
        core_pins[2] = core_pins[2] | 0x3000;
      }
      if (((*(int *)((int)core_regs + 0x39c) == 0) && (*(int *)((int)core_regs + 0x3a0) == 0)) &&
         (*(int *)((int)core_regs + 0x398) == 0)) {
        core_pins_gpio[3] = core_pins_gpio[3] & 0xfffffffd;
        core_pins_gpio[2] = core_pins_gpio[2] | 2;
      }
      else {
        core_pins[2] = core_pins[2] & 0xfffbffff;
        core_pins_gpio[3] = core_pins_gpio[3] | 2;
        core_pins_gpio[2] = core_pins_gpio[2] & 0xfffffffd;
        if (((*core_pins_gpio & 8) == 0) && ((*core_pins_gpio & 0x40) != 0)) {
          core_pins_gpio[3] = core_pins_gpio[3] | 0x25;
          core_pins_gpio[2] = core_pins_gpio[2] & 0xffffffdb;
          core_pins[3] = core_pins[3] | 0x3000;
        }
        else {
          *(undefined4 *)((int)core_regs + 0x2f0) = 1;
        }
      }
    }
    iVar1 = *(int *)((int)core_regs + 0x398);
    if ((((iVar1 == 0) ||
         ((*(int *)((int)core_regs + 0x3a0) == 0 &&
          ((iVar1 == 0 || (*(int *)((int)core_regs + 0x39c) == 0)))))) &&
        ((*(int *)((int)core_regs + 0x39c) == 0 || (*(int *)((int)core_regs + 0x3a0) == 0)))) &&
       ((*(int *)((int)core_regs + 0x2f0) == 0 ||
        (((*(int *)((int)core_regs + 0x39c) == 0 && (*(int *)((int)core_regs + 0x3a0) == 0)) &&
         (iVar1 == 0)))))) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
    *(undefined4 *)((int)core_regs + 0x2f4) = uVar3;
    if ((*(int *)((int)core_regs + 0x2f4) == 0) || (*(int *)((int)core_regs + 0x2f0) == 0)) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
    *(undefined4 *)((int)core_regs + 0x2c4) = uVar3;
    if (*(int *)((int)core_regs + 0x2f4) != 0) {
      io_out_note(&DAT_004b3428);
    }
    if (*(int *)((int)core_regs + 0x2c4) != 0) {
      if (*(int *)(cur_dev + 0x48) == 0) {
        if (phase_step != 0) {
          *(undefined4 *)(core_ctl + 0x10) = 0x100202;
          core_sample_pins();
          return;
        }
        *(undefined4 *)(core_ctl + 0x10) = 0x102;
        if ((3 < *(uint *)(cur_dtype + 8)) && (*(uint *)(cur_dtype + 8) != 0x80)) {
          core_pins[2] = core_pins[2] & 0xfffbffff;
          core_sample_pins();
          return;
        }
        goto switchD_004070b6_caseD_100205;
      }
      *(undefined4 *)((int)core_regs + 0x2c4) = 0;
      *(undefined4 *)((int)core_regs + 0x2f4) = 0;
    }
    *(undefined4 *)((int)core_regs + 0x3b4) = *(undefined4 *)((int)core_regs + 0x39c);
    if ((*(int *)((int)core_regs + 0x3a0) == 0) || (*(int *)((int)core_regs + 0x39c) != 0)) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
    *(undefined4 *)((int)core_regs + 0x3b0) = uVar3;
    if (((*(int *)((int)core_regs + 0x398) == 0) || (*(int *)((int)core_regs + 0x39c) != 0)) ||
       (*(int *)((int)core_regs + 0x3a0) != 0)) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
    *(undefined4 *)((int)core_regs + 0x3a4) = uVar3;
    if ((((*(int *)((int)core_regs + 0x3b4) == 0) || ((*(byte *)((int)core_regs + 500) & 0x20) == 0)
         ) && ((*(int *)((int)core_regs + 0x3b0) == 0 ||
               ((*(byte *)((int)core_regs + 500) & 8) == 0)))) &&
       ((*(int *)((int)core_regs + 0x3a4) == 0 ||
        (((*(byte *)((int)core_regs + 0x21c) & 8) == 0 &&
         ((*(byte *)((int)core_regs + 500) & 2) == 0)))))) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
    *(undefined4 *)((int)core_regs + 0x3a8) = uVar3;
    if ((((*(int *)((int)core_regs + 0x3b4) == 0) || ((*(byte *)((int)core_regs + 500) & 0x10) == 0)
         ) && ((*(int *)((int)core_regs + 0x3b0) == 0 ||
               ((*(byte *)((int)core_regs + 500) & 4) == 0)))) &&
       ((*(int *)((int)core_regs + 0x3a4) == 0 || ((*(byte *)((int)core_regs + 500) & 1) == 0)))) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
    *(undefined4 *)((int)core_regs + 0x3ac) = uVar3;
    if ((*(int *)((int)core_regs + 0x3a8) == 0) && (*(int *)((int)core_regs + 0x3ac) == 0)) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
    *(undefined4 *)((int)core_regs + 0x1e4) = uVar3;
    if (*(int *)((int)core_regs + 0x1e4) != 0) {
      if (((*(uint *)(cur_dtype + 8) & 3) == 0) || ((*(byte *)((int)core_regs + 0x1b0) & 0x80) == 0)
         ) {
        if ((3 < *(uint *)(cur_dtype + 8)) &&
           ((core_pins[2] = core_pins[2] & 0xfffdffff, (*(byte *)(cur_dtype + 8) & 0x80) != 0 &&
            ((*(byte *)((int)core_regs + 200) & 0x80) == 0)))) {
          uVar4 = core_pins[2] & 0xfeffffff;
          goto LAB_00406383;
        }
      }
      else {
        core_pins[3] = core_pins[3] | 0x200;
        uVar4 = core_pins[2] & 0xfffffdff;
LAB_00406383:
        core_pins[2] = uVar4;
      }
      if ((*(uint *)(cur_dtype + 8) & 0x800) != 0) {
        core_pins_gpio[3] = core_pins_gpio[3] | 0x20;
        core_pins_gpio[2] = core_pins_gpio[2] & 0xffffffdf;
      }
    }
    if ((*(uint *)(cur_dtype + 8) & 0x3618) == 0) {
      if ((*(uint *)(cur_dtype + 8) & 0x800) != 0) {
        core_pins_gpio[2] = core_pins_gpio[2] | 1;
      }
      if (*(int *)((int)core_regs + 0x3b4) == 0) {
        if (*(int *)((int)core_regs + 0x3b0) == 0) {
          if (*(int *)((int)core_regs + 0x3a4) != 0) {
            core_pins[2] = core_pins[2] | 0x7800;
            if ((*(int *)((int)core_regs + 0x24c) != 0) ||
               (uVar4 = 0xffff7fff, *(int *)((int)core_regs + 0x3cc) != 0)) {
              uVar4 = 0xffff77ff;
            }
            core_pins[2] = core_pins[2] & uVar4;
            *(undefined4 *)(core_pins_addr + 0xc) = 0xffff;
            *(undefined4 *)(core_pins_addr + 8) = *(undefined4 *)((int)core_regs + 0x144);
            io_out_reg_write(1,(ulong *)((int)core_regs + 0x144),0);
            *(uint *)((int)core_regs + 0x3c0) = *(uint *)((int)core_regs + 0x20) >> 4 & 0xf;
            uVar3 = *(undefined4 *)((int)core_regs + 0x144);
            va0 = 0xd;
            goto LAB_00406633;
          }
          if ((*(uint *)(cur_dtype + 8) & 0x800) != 0) {
            core_pins_gpio[2] = core_pins_gpio[2] | 0x20;
            core_pins_gpio[3] = core_pins_gpio[3] & 0xffffffdf;
          }
          core_pins[2] = core_pins[2] | 0x2f800;
          if ((*(byte *)(cur_dtype + 8) & 0x60) != 0) {
            core_pins[2] = core_pins[2] | 0x400000;
          }
          *(undefined4 *)((int)core_regs + 0x3c0) = 0;
        }
        else {
          core_pins[2] = core_pins[2] | 0xf000;
          core_pins[2] = core_pins[2] & 0xffffb7ff;
          *(undefined4 *)(core_pins_addr + 0xc) = 0xffff;
          *(undefined4 *)(core_pins_addr + 8) = *(undefined4 *)((int)core_regs + 0x140);
          io_out_reg_write(1,(ulong *)((int)core_regs + 0x140),0);
          if (*(uint *)((int)core_regs + 0x140) < 0xffc0) {
            *(uint *)((int)core_regs + 0x3c0) = *(uint *)((int)core_regs + 0x20) >> 8 & 0xf;
          }
          else {
            if ((*(byte *)(cur_dtype + 8) & 0x60) != 0) {
              core_pins[2] = core_pins[2] & 0xffbfffff;
            }
            *(uint *)((int)core_regs + 0x3c0) = *(uint *)((int)core_regs + 0x20) & 0xf;
          }
          iVar1 = core_ext_addr_match(0x12,*(ulong *)((int)core_regs + 0x13c));
          if (iVar1 != 0) {
            *(undefined4 *)((int)core_regs + 0x3c0) = 0;
          }
          dsp_free_ext(*(void **)(cur_dev + 4),0x17,*(undefined4 *)((int)core_regs + 0x140));
        }
      }
      else {
        core_pins[2] = core_pins[2] | 0xf800;
        core_pins[2] = core_pins[2] & 0xffffbfff;
        *(undefined4 *)(core_pins_addr + 0xc) = 0xffff;
        *(undefined4 *)(core_pins_addr + 8) = *(undefined4 *)((int)core_regs + 0x13c);
        io_out_reg_write(1,(ulong *)((int)core_regs + 0x13c),0);
        *(uint *)((int)core_regs + 0x3c0) = *(uint *)((int)core_regs + 0x20) >> 0xc;
        iVar1 = core_ext_addr_match(0x12,*(ulong *)((int)core_regs + 0x13c));
        if (iVar1 != 0) {
          *(undefined4 *)((int)core_regs + 0x3c0) = 0;
        }
        uVar3 = *(undefined4 *)((int)core_regs + 0x13c);
        va0 = 0x12;
LAB_00406633:
        dsp_free_ext(*(void **)(cur_dev + 4),va0,uVar3);
      }
    }
    if (in_stack_00000010 != 0) {
      *(undefined4 *)(core_ctl + 0x10) = 0x100204;
      core_sample_pins();
      return;
    }
switchD_004070b6_caseD_100204:
    if ((*(uint *)(cur_dtype + 8) & 0x3618) == 0) {
      if (*(int *)((int)core_regs + 0x3ac) == 0) {
        if (*(int *)((int)core_regs + 0x3a8) != 0) {
          uVar4 = core_pins[2] & 0xffffdfff;
          puVar2 = core_pins;
          goto LAB_00407152;
        }
      }
      else {
        core_pins[2] = core_pins[2] & 0xffffefff;
        if ((*(uint *)(cur_dtype + 8) & 0x800) != 0) {
          uVar4 = core_pins_gpio[2] & 0xfffffffe;
          puVar2 = core_pins_gpio;
LAB_00407152:
          puVar2[2] = uVar4;
        }
      }
      if (((*(uint *)(cur_dtype + 8) < 4) || (*(uint *)(cur_dtype + 8) == 0x80)) ||
         ((*(int *)((int)core_regs + 0x3ac) == 0 && (*(int *)((int)core_regs + 0x3a8) == 0)))) {
        core_pins[2] = core_pins[2] | 0x40000;
      }
      else {
        core_pins[2] = core_pins[2] & 0xfffbffff;
      }
    }
    if (*(int *)((int)core_regs + 0x2f4) != 0) goto LAB_004074d1;
    if (*(int *)((int)core_regs + 0x3d8) != 0) {
      switch(*(undefined4 *)((int)core_regs + 0x2ac)) {
      case 0:
        if (*(int *)((int)core_regs + 0x3e0) != 0) {
          if (*(int *)((int)core_regs + 0x40c) == 0) {
            *(undefined4 *)((int)core_regs + 0x228) = 0x67;
          }
          else if (((*(byte *)((int)core_regs + 0x25c) & 2) == 0) ||
                  (*(int *)((int)core_regs + 0x228) != 0x68)) {
            *(undefined4 *)((int)core_regs + 0x228) = 0x69;
            *(undefined4 *)((int)core_regs + 0x3d0) = 1;
            break;
          }
          *(undefined4 *)((int)core_regs + 0x3d0) = 1;
        }
        break;
      case 1:
        if (*(int *)((int)core_regs + 0x26c) == 0) {
          *(undefined4 *)((int)core_regs + 0x3d4) = 0;
          *(undefined4 *)((int)core_regs + 0x3d0) = 0;
        }
        else if (*(int *)((int)core_regs + 0x240) != 0) {
          *(undefined4 *)((int)core_regs + 0x3d0) = 2;
        }
        break;
      case 2:
        if (*(int *)((int)core_regs + 0x3e0) != 0) {
          *(undefined4 *)((int)core_regs + 0x3d0) = 4;
        }
        break;
      case 4:
        if (*(int *)((int)core_regs + 0x3e0) != 0) {
          *(undefined4 *)((int)core_regs + 0x3d0) = 0xc;
        }
        break;
      case 8:
switchD_004071dd_caseD_8:
        *(undefined4 *)((int)core_regs + 0x3d0) = 8;
        break;
      case 0xc:
        if (*(int *)((int)core_regs + 0x3e0) != 0) goto switchD_004071dd_caseD_8;
      }
    }
    *(undefined4 *)((int)core_regs + 0x424) = 0;
    *(int *)((int)core_regs + 0x25c) = *(int *)((int)core_regs + 0x25c) << 1;
    if ((*(uint *)((int)core_regs + 0x218) & 0x200) == 0) {
      *(undefined4 *)((int)core_regs + 0x234) = 1;
    }
    else {
      *(uint *)((int)core_regs + 0x25c) = *(uint *)((int)core_regs + 0x25c) | 1;
      if ((*(uint *)((int)core_regs + 0x218) & 0x80) == 0) {
        if ((*(uint *)((int)core_regs + 0x218) & 0x400) == 0) {
          uVar5 = core_cc_test(*(int *)((int)core_regs + 0x1d4));
        }
        else if ((*(byte *)((int)core_regs + 0x2c8) & 1) == 0) {
          uVar5 = core_bit_test_not();
        }
        else {
          uVar5 = core_bit_test();
        }
        *(ulong *)((int)core_regs + 0x234) = uVar5;
      }
      else {
        *(undefined4 *)((int)core_regs + 0x234) = 1;
      }
      if (*(int *)((int)core_regs + 0x234) != 0) {
        *(undefined4 *)((int)core_regs + 0x424) = 1;
        *(undefined4 *)(cur_sim + 0x18) = 1;
        *(uint *)((int)core_regs + 0x218) = *(uint *)((int)core_regs + 0x218) | 0x20;
        if ((*(int *)((int)core_regs + 0x234) != 0) &&
           ((*(byte *)((int)core_regs + 0x2c8) & 2) != 0)) {
          *(undefined4 *)((int)core_regs + 0x28c) = 1;
          goto LAB_004073a0;
        }
      }
      *(undefined4 *)((int)core_regs + 0x28c) = 0;
    }
LAB_004073a0:
    if ((((*(byte *)((int)core_regs + 0x218) & 0x20) != 0) &&
        (*(int *)((int)core_regs + 0x428) == 0)) || (*(int *)((int)core_regs + 0x424) != 0)) {
      *(uint *)((int)core_regs + 0x22c) =
           (uint)(*(int *)((int)core_regs + 0x144) == *(int *)((int)core_regs + 0x28));
      *(uint *)((int)core_regs + 0x230) = (uint)(*(int *)((int)core_regs + 0x2c) == 1);
      if ((((*(uint *)((int)core_regs + 0x9c) & 0x8000) == 0) ||
          (*(int *)((int)core_regs + 0x22c) == 0)) || (*(int *)((int)core_regs + 0x230) == 0)) {
        uVar3 = 0;
      }
      else {
        uVar3 = 1;
      }
      *(undefined4 *)((int)core_regs + 0x238) = uVar3;
      if ((((*(uint *)((int)core_regs + 0x9c) & 0x8000) == 0) ||
          (*(int *)((int)core_regs + 0x22c) == 0)) || (*(int *)((int)core_regs + 0x230) != 0)) {
        uVar3 = 0;
      }
      else {
        uVar3 = 1;
      }
      *(undefined4 *)((int)core_regs + 600) = uVar3;
    }
    if ((*(int *)((int)core_regs + 0x428) != 0) && (*(int *)((int)core_regs + 0x274) != 0)) {
      if (*(int *)((int)core_regs + 0x2c) == 1) {
        *(undefined4 *)((int)core_regs + 0x23c) = 1;
        *(undefined4 *)((int)core_regs + 0x428) = 0;
        uVar5 = *(ulong *)((int)core_regs + 0x1b4);
      }
      else {
        uVar5 = *(int *)((int)core_regs + 0x2c) - 1;
      }
      core_set_reg(0xb,uVar5);
    }
    core_fetch_decode();
    if (((((*(byte *)((int)core_regs + 0x21c) & 0x40) == 0) &&
         (*(int *)((int)core_regs + 0x27c) != 0)) && ((*(byte *)((int)core_regs + 0x218) & 2) == 0))
       && ((*(int *)((int)core_regs + 0x23c) == 0 && (*(int *)((int)core_regs + 0x428) == 0)))) {
      *(undefined4 *)((int)core_regs + 600) = 0;
      *(undefined4 *)((int)core_regs + 0x238) = 0;
    }
LAB_004074d1:
    *(undefined4 *)(core_ctl + 0x10) = 0x108;
    core_sample_pins();
    return;
  }
  if (*(int *)((int)core_regs + 0x3ac) == 0) {
    *(undefined4 *)(core_pins_data + 0xc) = 0;
  }
  else {
    *(undefined4 *)(core_pins_data + 4) = 0;
    *(undefined4 *)(core_pins_data + 0xc) = 0xffffff;
    if (*(int *)((int)core_regs + 0x3b4) == 0) {
      if (*(int *)((int)core_regs + 0x3b0) == 0) {
        core_mem_write(0xd,*(ulong *)((int)core_regs + 0x144),(ulong *)((int)core_regs + 0x150),0x80
                      );
      }
      else {
        core_mem_write(0x17,*(ulong *)((int)core_regs + 0x140),(ulong *)((int)core_regs + 0x14c),
                       0x800);
      }
    }
    else {
      core_mem_write(0x12,*(ulong *)((int)core_regs + 0x13c),(ulong *)((int)core_regs + 0x148),
                     0x2000);
    }
  }
  if (*(int *)((int)core_regs + 0x2b0) == 0xe) {
    if ((*(uint *)((int)core_regs + 0x2b4) & 2) == 0) {
      if ((*(uint *)((int)core_regs + 0x2b4) & 1) != 0) {
        if (*(int *)(core_ctl + 0xc) == 0) {
          *(undefined4 *)(core_ctl + 0xc) = 1;
          chip_reset_regs(0,-1);
          if (phase_step != 0) {
            *(undefined4 *)(core_ctl + 0x10) = 0x100280;
            core_sample_pins();
            return;
          }
          *(undefined4 *)(core_ctl + 0x10) = 0x108;
          *(uint *)(cur_dev + 0x44) = *(uint *)(cur_dev + 0x44) | 1;
          core_sample_pins();
          return;
        }
        if (*(int *)((int)core_regs + 0x2e4) != 0) {
          if (phase_step != 0) {
            *(undefined4 *)(core_ctl + 0x10) = 0x100280;
            core_sample_pins();
            return;
          }
          *(undefined4 *)(core_ctl + 0x10) = 0x108;
          *(uint *)(cur_dev + 0x44) = *(uint *)(cur_dev + 0x44) | 1;
          core_sample_pins();
          return;
        }
        *(undefined4 *)(core_ctl + 0xc) = 0;
        *(undefined4 *)((int)core_regs + 0x2d4) = 0;
        *(undefined4 *)((int)core_regs + 0x430) = 0;
        *(undefined4 *)((int)core_regs + 0x42c) = 0;
        *(undefined4 *)((int)core_regs + 0x448) = 0;
        *(undefined4 *)((int)core_regs + 0x444) = 0;
        *(undefined4 *)((int)core_regs + 0x418) = 0;
        *(undefined4 *)((int)core_regs + 0x400) = 0;
      }
    }
    else {
      iVar1 = core_irq_arbitrate();
      if (iVar1 == 0) {
        if (phase_step != 0) {
          *(undefined4 *)(core_ctl + 0x10) = 0x100280;
          core_sample_pins();
          return;
        }
        *(uint *)(cur_dev + 0x44) = *(uint *)(cur_dev + 0x44) | 1;
        *(undefined4 *)(core_ctl + 0x10) = 0x108;
        core_sample_pins();
        return;
      }
    }
  }
LAB_004068e0:
  if (*(int *)((int)core_regs + 0x3c0) != 0) {
    io_out_note(&DAT_004b3424);
    *(int *)((int)core_regs + 0x3c0) = *(int *)((int)core_regs + 0x3c0) + -1;
LAB_0040696d:
    *(uint *)(core_ctl + 0x10) = (-(uint)(phase_step != 0) & 0x1000f8) + 0x118;
    core_sample_pins();
    return;
  }
  uVar4 = *(uint *)(cur_dtype + 8);
  if (((((((uVar4 & 3) != 0) && ((*(byte *)((int)core_regs + 0x1b0) & 0x80) != 0)) &&
        ((*(int *)((int)core_regs + 0x1e4) != 0 && ((*core_pins & 0x400) == 0)))) ||
       (((3 < uVar4 && ((uVar4 & 0x40) == 0)) && ((*core_pins & 0x10000) == 0)))) ||
      ((((uVar4 & 0x800) != 0 && ((core_pins[2] & 0x8000) != 0)) && ((*core_pins_gpio & 0x10) != 0))
      )) && (*(int *)(cur_dev + 0x48) == 0)) {
    io_out_note(&DAT_004b3424);
    goto LAB_0040696d;
  }
  if (*(int *)((int)core_regs + 0x2f4) != 0) goto LAB_00407047;
  if (*(int *)((int)core_regs + 0x3d8) == 0) {
    iVar1 = core_irq_arbitrate();
    *(int *)((int)core_regs + 0x3c8) = iVar1;
  }
  if ((*(byte *)((int)core_regs + 0x25c) & 1) != 0) {
    *(uint *)((int)core_regs + 0x228) = 0x69 - (uint)(*(int *)((int)core_regs + 0x234) != 0);
  }
  *(uint *)((int)core_regs + 0x27c) = *(uint *)((int)core_regs + 0x9c) & 0x2000;
  if (*(int *)((int)core_regs + 0x3dc) == 0) {
    if (((*(uint *)((int)core_regs + 0x21c) & 0x100) != 0) &&
       (*(int *)((int)core_regs + 0x234) != 0)) {
      *(uint *)((int)core_regs + 0x19c) = *(int *)((int)core_regs + 0x144) + 1U & 0xffff;
    }
    if ((*(uint *)((int)core_regs + 0x21c) & 0x200) != 0) {
      *(undefined4 *)((int)core_regs + 0x1a4) = *(undefined4 *)((int)core_regs + 0x144);
      *(undefined4 *)((int)core_regs + 0x74) = *(undefined4 *)((int)core_regs + 0x1a4);
      core_touch_reg(0x1d);
    }
  }
  *(undefined4 *)((int)core_regs + 0x1d8) = *(undefined4 *)((int)core_regs + 0x274);
  if (*(int *)((int)core_regs + 0x274) == 0) {
    if ((*(uint *)((int)core_regs + 0x184) & 0x800000) == 0) {
      uVar4 = *(uint *)((int)core_regs + 0x20c) >> 3;
      if (uVar4 == 6) {
        *(undefined4 *)((int)core_regs + 0x134) = *(undefined4 *)((int)core_regs + 0x164);
        *(undefined4 *)((int)core_regs + 0x138) = *(undefined4 *)((int)core_regs + 0x160);
      }
      if ((*(byte *)((int)core_regs + 0x20c) & 4) == 0) {
        *(undefined4 *)((int)core_regs + 0x138) = *(undefined4 *)((int)core_regs + 0x160);
      }
      else {
        *(undefined4 *)((int)core_regs + 0x134) = *(undefined4 *)((int)core_regs + 0x164);
      }
      if ((uVar4 == 5) || (uVar4 == 7)) {
        if ((*(byte *)((int)core_regs + 0x20c) & 4) == 0) {
          *(undefined4 *)((int)core_regs + 0x134) = *(undefined4 *)((int)core_regs + 0x164);
        }
        else {
          *(undefined4 *)((int)core_regs + 0x138) = *(undefined4 *)((int)core_regs + 0x160);
        }
      }
    }
  }
  else {
    uVar4 = *(uint *)((int)core_regs + 0xdc);
    if ((*(uint *)((int)core_regs + 0x218) & 0x100) != 0) {
      uVar4 = uVar4 >> 0xc;
    }
    *(uint *)((int)core_regs + 0x1d4) = uVar4 & 0xf;
    *(uint *)((int)core_regs + 0x20c) = *(uint *)((int)core_regs + 0xdc) >> 8 & 0x3f;
    if (((*(uint *)((int)core_regs + 0x2b4) & 0x800) == 0) &&
       (((*(byte *)((int)core_regs + 0x1d0) & 8) != 0 ||
        ((*(uint *)((int)core_regs + 0xdc) & 0xff60b0) == 0x44010)))) {
      iVar1 = 1;
    }
    else {
      iVar1 = 0;
    }
    if ((*(uint *)((int)core_regs + 0xdc) & 0x800000) == 0) {
      *(undefined4 *)((int)core_regs + 0x134) = *(undefined4 *)((int)core_regs + 0x164);
      *(undefined4 *)((int)core_regs + 0x138) = *(undefined4 *)((int)core_regs + 0x160);
      core_agu_setup(*(ulong *)((int)core_regs + 0x20c),iVar1);
    }
    else {
      uVar4 = *(uint *)((int)core_regs + 0x20c);
      if ((uVar4 & 0x18) == 0) {
        uVar4 = uVar4 | 0x20;
      }
      else {
        uVar4 = uVar4 & 0x1f;
      }
      *(uint *)((int)core_regs + 0x20c) = uVar4;
      *(uint *)((int)core_regs + 0x210) = *(uint *)((int)core_regs + 0xdc) >> 0xd & 3;
      *(uint *)((int)core_regs + 0x210) =
           *(uint *)((int)core_regs + 0x210) | *(uint *)((int)core_regs + 0xdc) >> 0x11 & 0x18;
      if ((*(uint *)((int)core_regs + 0x210) & 0x18) == 0) {
        *(uint *)((int)core_regs + 0x210) = *(uint *)((int)core_regs + 0x210) | 0x20;
      }
      if ((*(byte *)((int)core_regs + 0x20c) & 4) == 0) {
        *(uint *)((int)core_regs + 0x210) = *(uint *)((int)core_regs + 0x210) | 4;
      }
      core_agu_setup(*(ulong *)((int)core_regs + 0x20c),iVar1);
      core_agu_setup(*(ulong *)((int)core_regs + 0x210),iVar1);
    }
  }
  uVar4 = *(uint *)((int)core_regs + 0x200);
  if ((uVar4 & 0x80) == 0) {
    *(uint *)((int)core_regs + 0x294) = uVar4 & 0x3f;
    goto switchD_00406cb4_caseD_3;
  }
  switch(uVar4 & 0x7f) {
  case 1:
    *(uint *)((int)core_regs + 0x294) = *(uint *)((int)core_regs + 0xdc) >> 0x10 & 0xc;
    *(uint *)((int)core_regs + 0x294) =
         (*(uint *)((int)core_regs + 0x294) | 0x10) >> 2 | *(uint *)((int)core_regs + 0x294);
    break;
  case 2:
    *(uint *)((int)core_regs + 0x294) =
         (*(uint *)((int)core_regs + 0xdc) & 0x80000 | 0x700000) >> 0x13;
    break;
  case 4:
    *(uint *)((int)core_regs + 0x294) = *(uint *)((int)core_regs + 0xdc) >> 0x10 & 0x3f;
    *(uint *)((int)core_regs + 0x294) =
         *(uint *)((int)core_regs + 0x294) & 7 | *(uint *)((int)core_regs + 0x294) >> 1 & 0x18;
    break;
  case 8:
    *(uint *)((int)core_regs + 0x294) = *(uint *)((int)core_regs + 0xdc) >> 0xd & 0x1f;
    break;
  case 0x10:
    uVar4 = *(uint *)((int)core_regs + 0xdc) >> 8 & 0x3f;
    goto LAB_00406d82;
  case 0x20:
    *(uint *)((int)core_regs + 0x294) = *(uint *)((int)core_regs + 0xdc) & 0x3f;
    break;
  case 0x40:
    uVar4 = (uint)((byte)((uint)*(undefined4 *)((int)core_regs + 0xdc) >> 8) & 7 | 0x10);
LAB_00406d82:
    *(uint *)((int)core_regs + 0x294) = uVar4;
  }
switchD_00406cb4_caseD_3:
  uVar4 = *(uint *)((int)core_regs + 0x208);
  if ((uVar4 & 0x10) == 0) {
    if ((*(uint *)((int)core_regs + 0x2b4) & 0x200) == 0) {
      *(uint *)((int)core_regs + 0x29c) = uVar4 & 0xf;
    }
    else {
      *(undefined4 *)((int)core_regs + 0x29c) = 0;
    }
  }
  else {
    uVar4 = uVar4 & 7;
    if (uVar4 == 1) {
      *(uint *)((int)core_regs + 0x29c) = *(uint *)((int)core_regs + 0xdc) >> 0x10 & 3;
      *(uint *)((int)core_regs + 0x29c) =
           *(uint *)((int)core_regs + 0x29c) * 4 | *(uint *)((int)core_regs + 0x29c) | 6;
    }
    else if (uVar4 == 2) {
      *(uint *)((int)core_regs + 0x29c) =
           (*(uint *)((int)core_regs + 0xdc) & 0x20000 | 0x1c0000) >> 0x11;
    }
    else if ((uVar4 == 4) &&
            (*(uint *)((int)core_regs + 0x29c) = *(uint *)((int)core_regs + 0xdc) >> 0x10 & 7,
            (*(uint *)((int)core_regs + 0xdc) & 0x100000) != 0)) {
      *(uint *)((int)core_regs + 0x29c) = *(uint *)((int)core_regs + 0x29c) | 8;
    }
  }
  if ((*(uint *)((int)core_regs + 0x1ec) & 1) == 0) goto switchD_00406e6e_caseD_6;
  switch(*(uint *)((int)core_regs + 0x1ec) & 0x3e) {
  case 2:
    *(uint *)((int)core_regs + 0x1ac) = *(uint *)((int)core_regs + 0xdc) & 0xff00;
    switch(*(uint *)((int)core_regs + 0xdc) & 0x43) {
    case 0:
      uVar4 = *(uint *)((int)core_regs + 0x1ac) | 0xff00ff;
      goto LAB_00406f17;
    case 1:
    case 2:
      uVar4 = *(uint *)((int)core_regs + 0x1ac) | 0xffff00ff;
      break;
    default:
      goto switchD_00406e6e_caseD_6;
    case 0x41:
    case 0x42:
      uVar4 = *(uint *)((int)core_regs + 0x1ac);
    }
    uVar4 = uVar4 >> 8;
    goto LAB_00406f17;
  case 4:
    *(uint *)((int)core_regs + 0x1ac) =
         *(uint *)((int)core_regs + 0xdc) >> 8 & 0xff |
         (*(uint *)((int)core_regs + 0xdc) & 0xf) << 8;
    break;
  case 8:
    uVar4 = *(uint *)((int)core_regs + 0x150);
    goto LAB_00406f17;
  case 0x10:
    *(uint *)((int)core_regs + 0x1ac) = (*(uint *)((int)core_regs + 0xdc) & 0xff00) << 8;
    break;
  case 0x20:
    uVar4 = (uint)*(byte *)((int)core_regs + 0xdd);
LAB_00406f17:
    *(uint *)((int)core_regs + 0x1ac) = uVar4;
  }
switchD_00406e6e_caseD_6:
  *(undefined4 *)((int)core_regs + 0x178) = *(undefined4 *)((int)core_regs + 0x13c);
  *(undefined4 *)((int)core_regs + 0x17c) = *(undefined4 *)((int)core_regs + 0x140);
  *(undefined4 *)((int)core_regs + 0x174) = *(undefined4 *)((int)core_regs + 0x144);
  if ((*(uint *)((int)core_regs + 0x1d0) & 0x2000) != 0) {
    *(undefined4 *)((int)core_regs + 0x178) = *(undefined4 *)((int)core_regs + 0x138);
  }
  if ((*(uint *)((int)core_regs + 0x1d0) & 0x1000) != 0) {
    *(undefined4 *)((int)core_regs + 0x17c) = *(undefined4 *)((int)core_regs + 0x138);
  }
  if ((*(uint *)((int)core_regs + 0x1d0) & 0x800) != 0) {
    *(undefined4 *)((int)core_regs + 0x174) = *(undefined4 *)((int)core_regs + 0x138);
  }
  if ((*(uint *)((int)core_regs + 0x1d0) & 0x400) != 0) {
    *(undefined4 *)((int)core_regs + 0x178) = *(undefined4 *)((int)core_regs + 0x134);
  }
  if ((*(uint *)((int)core_regs + 0x1d0) & 0x200) != 0) {
    *(undefined4 *)((int)core_regs + 0x17c) = *(undefined4 *)((int)core_regs + 0x134);
  }
  if ((*(uint *)((int)core_regs + 0x1d0) & 0x100) != 0) {
    *(undefined4 *)((int)core_regs + 0x174) = *(undefined4 *)((int)core_regs + 0x134);
  }
  if ((*(byte *)((int)core_regs + 0x1d0) & 0x80) != 0) {
    *(undefined4 *)((int)core_regs + 0x160) = *(undefined4 *)((int)core_regs + 0x120);
  }
  if ((*(byte *)((int)core_regs + 0x1d0) & 0x40) != 0) {
    *(undefined4 *)((int)core_regs + 0x164) = *(undefined4 *)((int)core_regs + 0x11c);
  }
  if ((*(uint *)((int)core_regs + 0x21c) & 0x400) != 0) {
    *(undefined4 *)((int)core_regs + 0x1a0) = *(undefined4 *)((int)core_regs + 0x174);
  }
LAB_00407047:
  if (phase_step != 0) {
    *(undefined4 *)(core_ctl + 0x10) = 0x100220;
    core_sample_pins();
    return;
  }
switchD_004070b6_caseD_100220:
  if (*(int *)((int)core_regs + 0x3a8) != 0) {
    *(undefined4 *)(core_pins_data + 0xc) = 0;
    *(undefined4 *)(core_pins_data + 4) = 0xffffff;
    if (*(int *)((int)core_regs + 0x3b4) == 0) {
      if (*(int *)((int)core_regs + 0x3b0) == 0) {
        if (*(int *)((int)core_regs + 0x24c) != 0) {
          *(undefined4 *)((int)core_regs + 0x234) = 1;
        }
        if (*(int *)((int)core_regs + 0x234) != 0) {
          *(undefined4 *)((int)core_regs + 0x170) = *(undefined4 *)((int)core_regs + 0x144);
        }
        core_mem_read(0xd,*(ulong *)((int)core_regs + 0x144),(ulong *)((int)core_regs + 0x150),0x40)
        ;
        iVar1 = *(int *)((int)core_regs + 0x1e0);
        *(int *)((int)core_regs + 0x1e0) = iVar1 + 1;
        if (iVar1 == 1) {
          *(undefined4 *)(core_trace[2] + 8 + core_trace[1] * 0x2c) =
               *(undefined4 *)((int)core_regs + 0x150);
        }
        if (*(int *)((int)core_regs + 0x3cc) != 0) {
          *(undefined4 *)((int)core_regs + 0x3cc) = 0;
          core_irq_ack();
        }
      }
      else {
        core_mem_read(0x17,*(ulong *)((int)core_regs + 0x140),(ulong *)((int)core_regs + 0x14c),
                      0x400);
      }
    }
    else {
      core_mem_read(0x12,*(ulong *)((int)core_regs + 0x13c),(ulong *)((int)core_regs + 0x148),0x1000
                   );
    }
  }
  if ((*(uint *)(cur_dtype + 8) & 0x3618) == 0) {
    if ((*(int *)((int)core_regs + 0x3a8) != 0) || (*(int *)((int)core_regs + 0x3ac) != 0)) {
      if ((core_pins[2] & 0x4000) == 0) {
        iVar1 = (-(uint)((core_pins[2] & 0x800) != 0) & 0xfffffffb) + 0x17;
      }
      else {
        iVar1 = 0xd;
      }
      dsp_free_ext(*(void **)(cur_dev + 4),iVar1,*(undefined4 *)(core_pins_addr + 8));
    }
    core_pins[2] = core_pins[2] | 0x23000;
    if ((*(uint *)(cur_dtype + 8) & 0x800) != 0) {
      core_pins_gpio[2] = core_pins_gpio[2] | 0x21;
    }
  }
  if (*(int *)((int)core_regs + 0x2f4) == 0) {
    if ((*(byte *)((int)core_regs + 0x3b8) & 1) != 0) {
      core_mem_read(*(ulong *)((int)core_regs + 0x3ec),*(ulong *)((int)core_regs + 0x13c),
                    (ulong *)((int)core_regs + 0x148),0x1000);
    }
    if ((*(byte *)((int)core_regs + 0x3bc) & 1) != 0) {
      core_mem_write(*(ulong *)((int)core_regs + 0x3ec),*(ulong *)((int)core_regs + 0x13c),
                     (ulong *)((int)core_regs + 0x148),0x2000);
    }
    if ((*(byte *)((int)core_regs + 0x3b8) & 2) != 0) {
      core_mem_read(*(ulong *)((int)core_regs + 0x3f0),*(ulong *)((int)core_regs + 0x140),
                    (ulong *)((int)core_regs + 0x14c),0x400);
    }
    if ((*(byte *)((int)core_regs + 0x3bc) & 2) != 0) {
      core_mem_write(*(ulong *)((int)core_regs + 0x3f0),*(ulong *)((int)core_regs + 0x140),
                     (ulong *)((int)core_regs + 0x14c),0x800);
    }
    if ((*(byte *)((int)core_regs + 0x3b8) & 4) != 0) {
      if (*(int *)((int)core_regs + 0x24c) != 0) {
        *(undefined4 *)((int)core_regs + 0x234) = 1;
      }
      if (*(int *)((int)core_regs + 0x234) != 0) {
        *(undefined4 *)((int)core_regs + 0x170) = *(undefined4 *)((int)core_regs + 0x144);
      }
      core_mem_read(*(ulong *)((int)core_regs + 0x3f4),*(ulong *)((int)core_regs + 0x144),
                    (ulong *)((int)core_regs + 0x150),0x40);
      iVar1 = *(int *)((int)core_regs + 0x1e0);
      *(int *)((int)core_regs + 0x1e0) = iVar1 + 1;
      if (iVar1 == 1) {
        *(undefined4 *)(core_trace[2] + 8 + core_trace[1] * 0x2c) =
             *(undefined4 *)((int)core_regs + 0x150);
      }
      if (*(int *)((int)core_regs + 0x3cc) != 0) {
        *(undefined4 *)((int)core_regs + 0x3cc) = 0;
        core_irq_ack();
      }
    }
    if ((*(byte *)((int)core_regs + 0x3bc) & 4) != 0) {
      core_mem_write(0xe,*(ulong *)((int)core_regs + 0x144),(ulong *)((int)core_regs + 0x150),0x80);
    }
    if ((*(int *)((int)core_regs + 0x1dc) != 0) &&
       (core_bit_op(), (*(byte *)((int)core_regs + 0x270) & 5) != 0)) {
      *(undefined4 *)((int)core_regs + 0x1dc) = 0;
    }
    if (*(int *)((int)core_regs + 0x2f4) != 0) goto LAB_004081d8;
    if (*(int *)((int)core_regs + 0x268) == 0) {
      if ((*(uint *)((int)core_regs + 0x270) & 0x20) != 0) {
        if ((*(uint *)((int)core_regs + 0x270) & 0x200) != 0) {
          *(undefined4 *)((int)core_regs + 0x154) = *(undefined4 *)((int)core_regs + 0x180);
        }
        core_write_from_bus(*(int *)(&regsel_tab + *(int *)((int)core_regs + 0x290) * 4),0x55);
      }
      if ((*(uint *)((int)core_regs + 0x270) & 8) != 0) {
        if ((*(uint *)((int)core_regs + 0x270) & 0x2000) != 0) {
          *(undefined4 *)((int)core_regs + 0x148) = *(undefined4 *)((int)core_regs + 0x180);
        }
        core_write_from_bus(*(int *)(&regsel_tab + *(int *)((int)core_regs + 0x290) * 4),0x52);
      }
      if ((*(uint *)((int)core_regs + 0x270) & 0x10) != 0) {
        if ((*(uint *)((int)core_regs + 0x270) & 0x800) != 0) {
          *(undefined4 *)((int)core_regs + 0x14c) = *(undefined4 *)((int)core_regs + 0x180);
        }
        core_write_from_bus(*(int *)(&regsel_tab + *(int *)((int)core_regs + 0x298) * 4),0x53);
      }
    }
    if (*(int *)((int)core_regs + 0x1bc) == 1) {
      *(undefined4 *)((int)core_regs + 0x1bc) = 2;
      alu_execute(core_regs);
    }
    *(undefined4 *)((int)core_regs + 0x13c) = *(undefined4 *)((int)core_regs + 0x178);
    *(undefined4 *)((int)core_regs + 0x140) = *(undefined4 *)((int)core_regs + 0x17c);
    *(undefined4 *)((int)core_regs + 0x144) = *(undefined4 *)((int)core_regs + 0x174);
    if ((*(byte *)((int)core_regs + 0x1d0) & 0x20) != 0) {
      *(undefined4 *)((int)core_regs + 0x160) = *(undefined4 *)((int)core_regs + 0x150);
    }
    if ((*(byte *)((int)core_regs + 0x1d0) & 0x10) != 0) {
      *(undefined4 *)((int)core_regs + 0x164) = *(undefined4 *)((int)core_regs + 0x150);
    }
    if ((*(uint *)((int)core_regs + 0x21c) & 0x4000) != 0) {
      core_ss_push(10,0xb);
    }
    if ((*(byte *)((int)core_regs + 0x218) & 1) != 0) {
      core_ss_push(0x67,0x27);
      core_set_reg(10,*(ulong *)((int)core_regs + 0x144));
      core_set_reg(0x27,*(uint *)((int)core_regs + 0x9c) | 0x8000);
    }
    if (*(int *)((int)core_regs + 0x28c) != 0) {
      *(undefined4 *)((int)core_regs + 0x28c) = 0;
      core_ss_push(0x69,0x27);
      if ((*(byte *)((int)core_regs + 0x3d0) & 4) != 0) {
        core_set_reg(0x27,*(uint *)((int)core_regs + 0x9c) & 0x7f);
        if (*(uint *)((int)core_regs + 0x2e0) < 4) {
          uVar4 = (*(uint *)((int)core_regs + 0x2e0) & 3) << 8;
        }
        else {
          uVar4 = 0x300;
        }
        *(uint *)((int)core_regs + 0x9c) = *(uint *)((int)core_regs + 0x9c) | uVar4;
      }
    }
    if (*(int *)((int)core_regs + 0x2f4) != 0) goto LAB_004081d8;
    if ((*(int *)((int)core_regs + 0x27c) == 0) || (*(int *)((int)core_regs + 0x280) != 0)) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
    *(undefined4 *)((int)core_regs + 0x284) = uVar3;
    if ((((*(byte *)((int)core_regs + 0x218) & 0x40) == 0) || (*(int *)((int)core_regs + 600) == 0))
       || (*(int *)((int)core_regs + 0x428) != 0)) {
      if ((*(byte *)((int)core_regs + 0x21c) & 0x80) != 0) {
        *(undefined4 *)((int)core_regs + 0x144) = *(undefined4 *)((int)core_regs + 0x19c);
      }
    }
    else if (((*(int *)((int)core_regs + 0x264) == 0) ||
             ((*(byte *)((int)core_regs + 0x25c) & 1) == 0)) ||
            (*(int *)((int)core_regs + 0x228) != 0x69)) {
      core_ss_pop(0x51,0x57);
      core_set_reg(0xb,*(int *)((int)core_regs + 0x2c) - 1);
      *(undefined4 *)((int)core_regs + 0x228) = 0x66;
    }
    if ((((((*(byte *)((int)core_regs + 0x218) & 0x40) != 0) ||
          (*(int *)((int)core_regs + 0x23c) != 0)) &&
         ((*(int *)((int)core_regs + 0x238) != 0 && (*(int *)((int)core_regs + 0x428) == 0)))) ||
        ((*(uint *)((int)core_regs + 0x2b4) & 0x100) != 0)) &&
       (((*(int *)((int)core_regs + 0x264) == 0 || ((*(byte *)((int)core_regs + 0x25c) & 1) == 0))
        || (*(int *)((int)core_regs + 0x228) != 0x69)))) {
      core_do_loop_end();
    }
    if ((*(uint *)((int)core_regs + 0x21c) & 0x2000) != 0) {
      if (*(int *)((int)core_regs + 0xdc) == 4) {
        iVar1 = 0x27;
      }
      else {
        iVar1 = 0x56;
      }
      core_ss_pop(0x51,iVar1);
      *(undefined4 *)((int)core_regs + 0x228) = 0x66;
    }
    if (((*(byte *)((int)core_regs + 0x218) & 4) != 0) &&
       ((*(byte *)((int)core_regs + 0x2b4) & 0x83) != 0)) {
      *(undefined4 *)((int)core_regs + 0x228) = 0x69;
    }
    if ((*(int *)((int)core_regs + 0x264) == 0) || ((*(byte *)((int)core_regs + 0x21c) & 3) != 0)) {
      *(undefined4 *)((int)core_regs + 0x260) = 0;
    }
    else {
      iVar1 = core_trace[1];
      if (core_trace[1] == 0) {
        iVar1 = history_size;
      }
      core_trace[1] = iVar1 + -1;
      *core_trace = *core_trace + -1;
      *(undefined4 *)((int)core_regs + 0x228) = 0x69;
      *(uint *)((int)core_regs + 0x21c) = *(uint *)((int)core_regs + 0x21c) | 0xc;
      *(undefined4 *)((int)core_regs + 0x1d8) = 0;
      *(undefined4 *)((int)core_regs + 0x260) = 1;
    }
    if (((*(uint *)((int)core_regs + 0x218) & 0x2000) == 0) &&
       (*(int *)((int)core_regs + 0x428) == 0)) {
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
    *(undefined4 *)((int)core_regs + 0x26c) = uVar3;
    if (((*(int *)((int)core_regs + 0x260) == 0) && ((*(byte *)((int)core_regs + 0x21c) & 8) == 0))
       || ((*(uint *)((int)core_regs + 0x218) & 0x4000) != 0)) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
    *(undefined4 *)((int)core_regs + 0x240) = uVar3;
    *(uint *)((int)core_regs + 0x274) = *(uint *)((int)core_regs + 0x21c) & 4;
    *(uint *)((int)core_regs + 0x254) = *(uint *)((int)core_regs + 0x21c) & 0x40;
    if (((*(int *)((int)core_regs + 0x274) == 0) || (*(int *)((int)core_regs + 0x428) != 0)) ||
       (*(int *)((int)core_regs + 0x254) != 0)) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
    *(undefined4 *)((int)core_regs + 0x250) = uVar3;
    if ((*(uint *)((int)core_regs + 0x3d0) & 1) == 0) {
      if ((*(uint *)((int)core_regs + 0x3d0) & 2) == 0) {
        if (((*(uint *)((int)core_regs + 0x218) & 0x200) != 0) ||
           ((*(byte *)((int)core_regs + 0x21c) & 0x80) != 0)) {
LAB_00407eac:
          *(undefined4 *)((int)core_regs + 0x3dc) = 0;
        }
      }
      else {
        *(undefined4 *)((int)core_regs + 0x264) = 0;
        *(undefined4 *)((int)core_regs + 0x24c) = 0;
        if (((*(int *)((int)core_regs + 0x250) != 0) ||
            ((*(uint *)((int)core_regs + 0x218) & 0x1000) != 0)) &&
           ((*(byte *)((int)core_regs + 500) & 3) == 0)) {
          if ((*(int *)((int)core_regs + 0x224) == 0) ||
             ((*(byte *)((int)core_regs + 0x25c) & 1) != 0)) {
            *(undefined4 *)((int)core_regs + 0x194) =
                 *(undefined4 *)((int)core_regs + *(int *)((int)core_regs + 0x228) * 4);
          }
          else {
            *(undefined4 *)((int)core_regs + 0x224) = 0;
          }
          *(int *)((int)core_regs + 0x144) = *(int *)((int)core_regs + 0x3e4) + 1;
          *(undefined4 *)((int)core_regs + 0x3cc) = 1;
          *(undefined4 *)((int)core_regs + 0x1a4) = *(undefined4 *)((int)core_regs + 0x194);
          *(undefined4 *)((int)core_regs + 0x19c) = *(undefined4 *)((int)core_regs + 0x1a4);
          if ((*(uint *)((int)core_regs + 0x218) & 0x200) != 0) goto LAB_00407eac;
        }
      }
    }
    else if (*(int *)((int)core_regs + 0x26c) == 0) {
      *(undefined4 *)((int)core_regs + 0x3d4) = 0;
      *(undefined4 *)((int)core_regs + 0x3d0) = 0;
      *(undefined4 *)((int)core_regs + 0x3dc) = 0;
      *(undefined4 *)((int)core_regs + 0x3d8) = 0;
      *(undefined4 *)((int)core_regs + 0x224) = 0;
    }
    else if (*(int *)((int)core_regs + 0x240) != 0) {
      if (*(int *)((int)core_regs + 0x228) == 0x66) {
        *(undefined4 *)((int)core_regs + 0x194) = *(undefined4 *)((int)core_regs + 0x198);
        *(undefined4 *)((int)core_regs + 0x224) = 1;
      }
      else {
        *(undefined4 *)((int)core_regs + 0x224) = 0;
      }
      *(undefined4 *)((int)core_regs + 0x260) = 1;
      *(undefined4 *)((int)core_regs + 0x264) = 1;
      *(undefined4 *)((int)core_regs + 0x144) = *(undefined4 *)((int)core_regs + 0x3e4);
      *(undefined4 *)((int)core_regs + 0x24c) = 1;
      *(undefined4 *)((int)core_regs + 0x3dc) = 1;
    }
    if ((((*(int *)((int)core_regs + 0x288) == 0) || ((*(uint *)((int)core_regs + 0x21c) & 4) == 0))
        || (*(int *)((int)core_regs + 0x428) != 0)) ||
       ((*(int *)((int)core_regs + 0x23c) != 0 || ((*(uint *)((int)core_regs + 0x21c) & 0x40) != 0))
       )) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
    *(undefined4 *)((int)core_regs + 0x278) = uVar3;
    if (*(int *)((int)core_regs + 0x278) != 0) {
      *(undefined4 *)((int)core_regs + 0x3d4) = 0;
      *(undefined4 *)((int)core_regs + 0x3d0) = 0;
      *(undefined4 *)((int)core_regs + 0x3d8) = 0;
      *(undefined4 *)((int)core_regs + 0x274) = 0;
      *(undefined4 *)((int)core_regs + 0x250) = 0;
    }
    if (*(int *)((int)core_regs + 0x274) == 0) {
      *(uint *)((int)core_regs + 0x2a4) = *(uint *)((int)core_regs + 0x1d0) >> 1 & 3;
      *(undefined4 *)((int)core_regs + 0x2a8) = *(undefined4 *)((int)core_regs + 0x1f8);
      if (*(int *)((int)core_regs + 0x278) == 0) {
        uVar4 = *(uint *)((int)core_regs + 0x220) & 0xf;
      }
      else {
        uVar4 = 0xc;
      }
      *(uint *)((int)core_regs + 0x2b0) = uVar4;
      if ((*(byte *)((int)core_regs + 0x1d0) & 1) != 0) {
        *(uint *)((int)core_regs + 0x184) = *(uint *)((int)core_regs + 0x184) & 0xffdfff;
      }
      if (*(int *)((int)core_regs + 0x1f0) != 0) {
        *(uint *)((int)core_regs + 0x188) = *(uint *)((int)core_regs + 0x188) & 0xffdfff;
      }
      if ((*(byte *)((int)core_regs + 0x220) & 0x10) != 0) {
        *(uint *)((int)core_regs + 0x18c) = *(uint *)((int)core_regs + 0x18c) & 0xffdfff;
      }
    }
    else {
      *(undefined4 *)((int)core_regs + 0x2a4) = 0;
      *(undefined4 *)((int)core_regs + 0x2a8) = 0;
      *(undefined4 *)((int)core_regs + 0x2b0) = 0;
    }
    if (((*(byte *)((int)core_regs + 0x21c) & 0x10) != 0) ||
       ((*(int *)((int)core_regs + 0x23c) != 0 && (*(int *)((int)core_regs + 0x274) != 0)))) {
      if (*(int *)((int)core_regs + 0x23c) != 0) {
        *(undefined4 *)((int)core_regs + 0x250) = 1;
        *(undefined4 *)((int)core_regs + 0x23c) = 0;
      }
      *(undefined4 *)((int)core_regs + 0x170) = *(undefined4 *)((int)core_regs + 0x168);
      *(undefined4 *)((int)core_regs + 0x150) = *(undefined4 *)((int)core_regs + 0x1a8);
    }
    if (*(int *)((int)core_regs + 0x250) != 0) {
      *(undefined4 *)((int)core_regs + 0xdc) = *(undefined4 *)((int)core_regs + 0x150);
      *(undefined4 *)((int)core_regs + 0x16c) = *(undefined4 *)((int)core_regs + 0x170);
    }
    if (*(int *)((int)core_regs + 0x254) != 0) {
      *(undefined4 *)((int)core_regs + 0xdc) = *(undefined4 *)((int)core_regs + 0x1a8);
      *(undefined4 *)((int)core_regs + 0x16c) = *(undefined4 *)((int)core_regs + 0x168);
    }
    if ((*(byte *)((int)core_regs + 0x218) & 0x10) != 0) {
      *(undefined4 *)((int)core_regs + 0x1b4) = *(undefined4 *)((int)core_regs + 0x2c);
    }
    if ((*(int *)((int)core_regs + 0x250) == 0) &&
       ((*(uint *)((int)core_regs + 0x218) & 0x1000) == 0)) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
    *(undefined4 *)((int)core_regs + 0x244) = uVar3;
    if ((*(int *)((int)core_regs + 0x244) == 0) &&
       (((*(byte *)((int)core_regs + 0x218) & 2) == 0 ||
        ((*(byte *)((int)core_regs + 0x3d0) & 4) == 0)))) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
    *(undefined4 *)((int)core_regs + 0x3e0) = uVar3;
    if (((*(int *)((int)core_regs + 0x244) != 0) && (*(int *)((int)core_regs + 0x3d8) == 0)) &&
       (*(int *)((int)core_regs + 0x3c8) != 0)) {
      *(undefined4 *)((int)core_regs + 0x3d8) = 1;
      *(undefined4 *)((int)core_regs + 0x3d4) = 0;
      *(undefined4 *)((int)core_regs + 0x3d0) = 0;
    }
    if (((*(byte *)((int)core_regs + 0x2b4) & 0x83) != 0) && (*(int *)((int)core_regs + 0x1d8) != 0)
       ) {
      *(undefined4 *)((int)core_regs + 0x3d4) = 0;
      *(undefined4 *)((int)core_regs + 0x3d0) = 0;
      *(undefined4 *)((int)core_regs + 0x3d8) = 0;
    }
    if (((*(int *)((int)core_regs + 0x3d8) != 0) && (*(int *)((int)core_regs + 0x244) != 0)) &&
       (*(int *)((int)core_regs + 0x3d4) = *(int *)((int)core_regs + 0x3d4) + 1,
       *(int *)((int)core_regs + 0x3d4) == 6)) {
      *(undefined4 *)((int)core_regs + 0x3d0) = 0;
      *(undefined4 *)((int)core_regs + 0x3d4) = 0;
      *(undefined4 *)((int)core_regs + 0x3d8) = 0;
    }
    *(undefined4 *)((int)core_regs + 0x2ac) = *(undefined4 *)((int)core_regs + 0x3d0);
    core_decode_ctl();
  }
  else {
LAB_004081d8:
    if (*(int *)((int)core_regs + 0x3b4) == 0) {
      *(undefined4 *)((int)core_regs + 0x3a0) = 0;
      *(undefined4 *)((int)core_regs + 0x3b0) = 0;
    }
    else {
      *(undefined4 *)((int)core_regs + 0x39c) = 0;
      *(undefined4 *)((int)core_regs + 0x3b4) = 0;
    }
  }
  if ((*(uint *)(cur_dtype + 8) & 0x800) != 0) {
    core_pins_gpio[2] = core_pins_gpio[2] | 0x20;
  }
  if (*(uint *)(cur_dtype + 8) < 4) {
    if (((*(uint *)(cur_dtype + 8) & 3) != 0) && ((*(byte *)((int)core_regs + 0x1b0) & 0x80) != 0))
    {
      uVar4 = core_pins[2] | 0x200;
      goto LAB_00408283;
    }
  }
  else {
    core_pins[2] = core_pins[2] | 0x20000;
    if (((*(byte *)(cur_dtype + 8) & 0x80) != 0) && ((*(byte *)((int)core_regs + 200) & 0x80) == 0))
    {
      uVar4 = core_pins[2] | 0xfeffffff;
LAB_00408283:
      core_pins[2] = uVar4;
    }
  }
  if (*(int *)((int)core_regs + 0x1dc) == 0) {
    *(undefined4 *)((int)core_regs + 0x1e4) = 0;
  }
  *(undefined4 *)(core_ctl + 0x10) = 0x101;
  if ((*(int *)((int)core_regs + 0x2f4) == 0) && (*(int *)((int)core_regs + 0x1d8) != 0)) {
    if (*(int *)((int)core_regs + 0x428) == 1) {
      *(uint *)(cur_dev + 0x44) = *(uint *)(cur_dev + 0x44) | 2;
    }
    else {
      if (*(int *)((int)core_regs + 0x248) != 0) {
        *(int *)((int)core_regs + 0x248) = *(int *)((int)core_regs + 0x248) + -1;
        core_sample_pins();
        return;
      }
      *(uint *)(cur_dev + 0x44) = *(uint *)(cur_dev + 0x44) | 1;
    }
    *(int *)(cur_dev + 0x24) = *(int *)(cur_dev + 0x24) + 1;
  }
switchD_004070b6_caseD_100205:
  core_sample_pins();
  return;
}


/* ==== core_sample_pins @ 00408510 ==== */

void core_sample_pins(void)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = *core_pins;
  if ((*(byte *)(cur_dtype + 8) & 0x80) != 0) {
    if ((*(byte *)(core_regs + 200) & 0x80) == 0) {
      if ((uVar5 & 0x800000) == 0) {
        uVar5 = uVar5 & 0xfffeffff | 0x400;
      }
      else {
        uVar5 = uVar5 | 0x10400;
      }
    }
    else if ((uVar5 & 0x800000) == 0) {
      uVar5 = uVar5 & 0xfffffbff | 0x10000;
    }
    else {
      uVar5 = uVar5 | 0x10400;
    }
    *core_pins = uVar5;
  }
  if ((*(byte *)(cur_dtype + 8) & 0x80) != 0) {
    uVar2 = *(uint *)(core_regs + 0xd0);
    if (((uVar2 & 0x10) != 0) && (uVar5 = uVar5 & 0xfffffffb, (uVar2 & 1) != 0)) {
      uVar5 = uVar5 | 4;
    }
    uVar4 = ~uVar5;
    uVar1 = **(uint **)(cur_dev + 0x40);
    if ((uVar2 & 0x20) != 0) {
      uVar5 = uVar5 & 0xfffffffe;
      uVar1 = uVar1 & 0xfffffffe;
      if ((uVar2 & 2) != 0) {
        uVar5 = uVar5 | 1;
        uVar1 = uVar1 | 1;
      }
    }
    if ((uVar2 & 0x40) != 0) {
      uVar5 = uVar5 & 0xfffffffd;
      uVar1 = uVar1 & 0xfffffffd;
      if ((uVar2 & 4) != 0) {
        uVar5 = uVar5 | 2;
        uVar1 = uVar1 | 2;
      }
    }
    if ((uVar2 & 0x80) != 0) {
      uVar5 = uVar5 & 0xfffffff7;
      uVar1 = uVar1 & 0xfffffffb;
      if ((uVar2 & 8) != 0) {
        uVar5 = uVar5 | 8;
        uVar1 = uVar1 | 4;
      }
    }
    if ((uVar4 >> 2 & 1) != 0) {
      **(uint **)(cur_dev + 0x40) = uVar1;
    }
  }
  *(uint *)(core_regs + 0x2e4) = uVar5 & 1;
  *(uint *)(core_regs + 0x2e8) = uVar5 & 2;
  *(uint *)(core_regs + 0x43c) = uVar5 & 0x100000;
  *(uint *)(core_regs + 0x440) = uVar5 & 0x200000;
  if (*(int *)(core_regs + 0x2e4) == 0) {
    if ((*(int *)(core_regs + 0x2d8) != 0) && ((*(byte *)(core_regs + 0x24) & 4) != 0)) {
      *(undefined4 *)(core_regs + 0x2d0) = 1;
    }
    if (*(int *)(core_regs + 0x2e4) != 0) goto LAB_00408667;
LAB_00408679:
    uVar3 = 0;
  }
  else {
LAB_00408667:
    if (((*(byte *)(core_regs + 0x24) & 4) == 0) || (*(int *)(core_regs + 0x2d0) != 0))
    goto LAB_00408679;
    uVar3 = 1;
  }
  *(undefined4 *)(core_regs + 0x2d8) = uVar3;
  if ((*(uint *)(cur_dtype + 8) & 0x60) == 0) {
    if (*(uint *)(cur_dtype + 8) < 4) {
      if ((core_pins[1] & 2) == 0) {
        if (*(uint *)(core_regs + 0x2e8) < 5) {
          *(undefined4 *)(core_regs + 0x2e8) = 10;
          *(undefined4 *)(core_regs + 0x400) = 4;
        }
      }
      else {
        *(uint *)(core_regs + 0x2e8) = uVar5 >> 1 & 1;
      }
    }
    else {
      if ((uVar5 & 8) == 0) {
        if (*(int *)(core_regs + 0x2b8) != 0) {
          *(undefined4 *)(core_regs + 0x400) = 4;
        }
        *(undefined4 *)(core_regs + 0x2b8) = 0;
      }
      else {
        *(undefined4 *)(core_regs + 0x2b8) = 1;
      }
      *(uint *)(core_regs + 0x2e8) = uVar5 >> 1 & 1;
    }
  }
  else {
    if (((uVar5 & 8) == 0) ||
       (uVar2 = (**(code **)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x224) + 0x18))(7),
       uVar2 < 0x80000000)) {
      if (*(int *)(core_regs + 0x2b8) != 0) {
        *(undefined4 *)(core_regs + 0x400) = 4;
      }
      *(undefined4 *)(core_regs + 0x2b8) = 0;
    }
    else {
      *(undefined4 *)(core_regs + 0x2b8) = 1;
    }
    *(uint *)(core_regs + 0x2e8) = uVar5 >> 1 & 1;
    *(uint *)(core_regs + 0x43c) = uVar5 >> 0x14 & 1;
    *(uint *)(core_regs + 0x440) = uVar5 >> 0x15 & 1;
  }
  if (*(int *)(core_regs + 0x2e8) == 0) {
    if ((*(int *)(core_regs + 0x2dc) != 0) && ((*(byte *)(core_regs + 0x24) & 0x20) != 0)) {
      *(undefined4 *)(core_regs + 0x2d4) = 1;
    }
    if (*(int *)(core_regs + 0x2e8) != 0) goto LAB_004087c8;
LAB_004087da:
    uVar3 = 0;
  }
  else {
LAB_004087c8:
    if (((*(byte *)(core_regs + 0x24) & 0x20) == 0) || (*(int *)(core_regs + 0x2d4) != 0))
    goto LAB_004087da;
    uVar3 = 1;
  }
  *(undefined4 *)(core_regs + 0x2dc) = uVar3;
  if ((*(byte *)(cur_dtype + 8) & 0x60) == 0) goto LAB_00408866;
  if (*(int *)(core_regs + 0x43c) == 0) {
    if (*(int *)(core_regs + 0x434) != 0) {
      *(undefined4 *)(core_regs + 0x42c) = 1;
    }
    if (*(int *)(core_regs + 0x43c) != 0) goto LAB_00408816;
LAB_00408822:
    uVar3 = 0;
  }
  else {
LAB_00408816:
    if (*(int *)(core_regs + 0x42c) != 0) goto LAB_00408822;
    uVar3 = 1;
  }
  *(undefined4 *)(core_regs + 0x434) = uVar3;
  if (*(int *)(core_regs + 0x440) == 0) {
    if (*(int *)(core_regs + 0x438) != 0) {
      *(undefined4 *)(core_regs + 0x430) = 1;
    }
    if (*(int *)(core_regs + 0x440) != 0) goto LAB_00408852;
LAB_0040885e:
    uVar3 = 0;
  }
  else {
LAB_00408852:
    if (*(int *)(core_regs + 0x430) != 0) goto LAB_0040885e;
    uVar3 = 1;
  }
  *(undefined4 *)(core_regs + 0x438) = uVar3;
LAB_00408866:
  *(uint *)(core_regs + 0x2ec) = ~uVar5 >> 2 & 1;
  if (*(int *)(core_regs + 0x2ec) != 0) {
    *(undefined4 *)(core_ctl + 8) = 1;
  }
  uVar5 = *(uint *)(cur_dtype + 8);
  if (((uVar5 & 3) == 0) || ((*(byte *)(core_regs + 0x1b0) & 0x80) == 0)) {
    if ((((uVar5 & 0x40) == 0) && ((*core_pins & 0x400) != 0)) || (*(int *)(core_regs + 0x1e4) != 0)
       ) {
      if ((((uVar5 & 0x40) == 0) &&
          (core_pins[2] = core_pins[2] | 0x200, (*(byte *)(cur_dtype + 8) & 0x80) != 0)) &&
         ((*(byte *)(core_regs + 200) & 0x80) != 0)) {
        core_pins[2] = core_pins[2] | 0x1000000;
      }
      if (*(int *)(core_regs + 0x2ec) == 0) {
        core_pins[3] = core_pins[3] | 0x102fa00;
      }
    }
    else {
      if ((uVar5 & 0x60) != 0) {
        core_pins[2] = core_pins[2] | 0x400000;
      }
      if ((*(byte *)(cur_dtype + 8) & 0x40) == 0) {
        core_pins[2] = core_pins[2] & 0xfefffdff;
      }
      core_pins[3] = core_pins[3] & 0xfffd07ff;
      if ((*(uint *)(cur_dtype + 8) & 0x800) != 0) {
        *(uint *)(core_pins_gpio + 0xc) = *(uint *)(core_pins_gpio + 0xc) & 0xffffffde;
        *(uint *)(core_pins_gpio + 8) = *(uint *)(core_pins_gpio + 8) | 0x21;
      }
      *(undefined4 *)(core_pins_addr + 4) = 0;
      *(undefined4 *)(core_pins_data + 4) = 0;
      *(undefined4 *)(core_pins_addr + 0xc) = 0;
      *(undefined4 *)(core_pins_data + 0xc) = 0;
    }
  }
  if ((*(uint *)(cur_dtype + 8) & 0x800) != 0) {
    uVar5 = *core_pins;
    core_pins[3] = core_pins[3] | 0x40000000;
    if ((uVar5 & 0x20000000) != *(uint *)(core_regs + 0x100)) {
      *(uint *)(core_regs + 0x100) = uVar5 & 0x20000000;
      if (0x12 < *(uint *)(core_regs + 0x104)) {
        *(undefined4 *)(core_regs + 0x104) = 0;
        core_pins[2] = core_pins[2] ^ 0x40000000;
        return;
      }
      *(uint *)(core_regs + 0x104) = *(uint *)(core_regs + 0x104) + 1;
    }
  }
  return;
}


/* ==== core_cc_test @ 00408a30 ==== */

ulong __cdecl core_cc_test(int cc)

{
  ulong uVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(core_regs + 0x9c);
  uVar1 = 0;
  switch(cc) {
  case 0:
    return ~uVar2 & 1;
  case 1:
    if (((uVar2 & 8) != 0) || ((uVar2 & 2) != 0)) {
      if ((uVar2 & 8) == 0) {
        return 0;
      }
      if ((uVar2 & 2) == 0) {
        return 0;
      }
    }
    break;
  case 2:
    return ~uVar2 >> 2 & 1;
  case 3:
    return ~uVar2 >> 3 & 1;
  case 4:
    if ((uVar2 & 4) != 0) {
      return 0;
    }
    if ((uVar2 & 0x30) == 0) {
      return 0;
    }
    break;
  case 5:
    return ~uVar2 >> 5 & 1;
  case 6:
    return ~uVar2 >> 6 & 1;
  case 7:
    if ((uVar2 & 4) != 0) {
      return 0;
    }
    if (((uVar2 & 2) != 0) || ((uVar2 & 8) != 0)) {
      if ((uVar2 & 2) == 0) {
        return 0;
      }
      if ((uVar2 & 8) == 0) {
        return 0;
      }
    }
    break;
  case 9:
joined_r0x00408b27:
    if ((((uVar2 & 2) != 0) || ((uVar2 & 8) == 0)) && (((uVar2 & 2) == 0 || ((uVar2 & 8) != 0)))) {
      return 0;
    }
    break;
  case 10:
    return uVar2 >> 2 & 1;
  case 0xb:
    return uVar2 >> 3 & 1;
  case 0xc:
    if (((uVar2 & 4) == 0) && ((uVar2 & 0x30) != 0)) {
      return 0;
    }
    break;
  case 0xd:
    return uVar2 >> 5 & 1;
  case 0xe:
    uVar2 = uVar2 >> 6;
  case 8:
    return uVar2 & 1;
  case 0xf:
    if ((uVar2 & 4) == 0) goto joined_r0x00408b27;
    break;
  default:
    goto switchD_00408a4a_default;
  }
  uVar1 = 1;
switchD_00408a4a_default:
  return uVar1;
}


/* ==== core_ss_dec @ 00408b80 ==== */

void core_ss_dec(void)

{
  uint uVar1;
  
  uVar1 = *(uint *)(core_regs + 0x98);
  if ((uVar1 & 0x10) == 0) {
    uVar1 = (uVar1 & 0xf) - 1;
  }
  else {
    uVar1 = uVar1 & 0x30 | uVar1 - 1 & 0xf;
  }
  *(uint *)(core_regs + 0x98) = uVar1;
  core_touch_reg(0x26);
  core_touch_reg(0x28);
  core_touch_reg(0x29);
  return;
}


/* ==== core_ss_push @ 00408bd0 ==== */

void __cdecl core_ss_push(int ssh_src,int ssl_src)

{
  uint uVar1;
  
  if (ssh_src != 0x56) {
    uVar1 = *(uint *)(core_regs + 0x98);
    if ((uVar1 & 0x10) == 0) {
      uVar1 = (uVar1 & 0xf) + 1;
    }
    else {
      uVar1 = uVar1 & 0x30 | uVar1 + 1 & 0xf;
    }
    *(uint *)(core_regs + 0x98) = uVar1;
    core_touch_reg(0x26);
  }
  uVar1 = *(uint *)(core_regs + 0x98) & 0xf;
  if (ssh_src != 0x56) {
    if (uVar1 != 0) {
      *(uint *)(core_regs + 0x2f8 + uVar1 * 4) = *(uint *)(core_regs + ssh_src * 4) & 0xffff;
    }
    core_touch_reg(0x28);
  }
  if (ssl_src != 0x56) {
    if (uVar1 != 0) {
      *(uint *)(core_regs + 0x348 + uVar1 * 4) = *(uint *)(core_regs + ssl_src * 4) & 0xffff;
    }
    core_touch_reg(0x29);
  }
  return;
}


/* ==== core_ss_pop @ 00408c70 ==== */

void __cdecl core_ss_pop(int ssh_dst,int ssl_dst)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(core_regs + 0x98) & 0xf;
  iVar1 = ssh_dst * 4;
  if (uVar2 == 0) {
    *(undefined4 *)(core_regs + iVar1) = 0;
    *(undefined4 *)(core_regs + ssl_dst * 4) = 0;
  }
  else {
    *(undefined4 *)(core_regs + iVar1) = *(undefined4 *)(core_regs + 0x2f8 + uVar2 * 4);
    *(undefined4 *)(core_regs + ssl_dst * 4) = *(undefined4 *)(core_regs + 0x348 + uVar2 * 4);
  }
  core_touch_reg(ssl_dst);
  *(uint *)(core_flags + 0xa4) = *(uint *)(core_flags + 0xa4) | 0x50000;
  *(uint *)(core_flags + 0xa0) = *(uint *)(core_flags + 0xa0) | 0x50000;
  if (ssh_dst != 0x56) {
    core_touch_reg(ssh_dst);
  }
  *(undefined4 *)(core_regs + 0x198) = *(undefined4 *)(core_regs + iVar1);
  return;
}


/* ==== core_read_to_bus @ 00408d20 ==== */

void __cdecl core_read_to_bus(ulong src,int dst)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ulong src_00;
  
  if (src == 0x28) {
    core_ss_pop(dst,0x56);
    core_ss_dec();
    return;
  }
  if (src == 0x29) {
    core_ss_pop(0x56,dst);
    return;
  }
  if ((((src != 300) && (src != 0x12d)) && (src != 0x12a)) && (src != 299)) {
    if ((int)src < 0) {
      return;
    }
    core_read_copy(src,dst);
    if ((src != 3) && (src != 7)) {
      return;
    }
    uVar2 = *(uint *)(core_regs + dst * 4);
    if ((uVar2 & 0x80) == 0) {
      return;
    }
    *(uint *)(core_regs + dst * 4) = uVar2 | 0xffff00;
    return;
  }
  switch(src - 0x12a) {
  case 0:
    if (dst == 0x52) {
      return;
    }
  case 2:
    core_read_copy(3,0x128);
    core_read_copy(2,0x127);
    src_00 = 1;
    break;
  case 1:
    if (dst == 0x52) {
      return;
    }
  case 3:
    core_read_copy(7,0x128);
    core_read_copy(6,0x127);
    src_00 = 5;
    break;
  default:
    goto switchD_00408dd0_default;
  }
  core_read_copy(src_00,0x126);
  switch(src - 0x12a) {
  case 0:
  case 1:
    break;
  case 2:
  case 3:
    if ((dst == 0x52) || (dst == 0x53)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    uVar2 = *(uint *)(core_regs + 0x9c) & 0xc00;
    if (uVar2 == 0x400) {
      uVar3 = *(uint *)(core_regs + 0x49c) >> 1;
      if (((byte)*(uint *)(core_regs + 0x4a0) & 1) == 1) {
        uVar3 = uVar3 | 0x800000;
      }
      uVar2 = *(uint *)(core_regs + 0x4a0) >> 1;
      if ((uVar2 & 0x40) != 0) {
        uVar2 = uVar2 | 0x180;
      }
    }
    else {
      uVar3 = *(uint *)(core_regs + 0x49c);
      if (uVar2 == 0x800) {
        uVar3 = uVar3 * 2;
        if (0x7fffff < *(uint *)(core_regs + 0x498)) {
          uVar3 = uVar3 + 1;
        }
        uVar2 = *(int *)(core_regs + 0x4a0) * 2;
        if (0xffffff < uVar3) {
          uVar2 = uVar2 + 1;
          uVar3 = uVar3 & 0xffffff;
        }
      }
      else {
        uVar2 = *(uint *)(core_regs + 0x4a0);
        if ((uVar2 & 0x80) != 0) {
          uVar2 = uVar2 | 0x100;
        }
      }
    }
    if (((bVar1) && (3 < *(uint *)(cur_dtype + 8))) &&
       (((uVar3 & 0x600000) == 0x400000 || ((uVar3 & 0x600000) == 0x200000)))) {
      core_set_reg(0x27,*(uint *)(core_regs + 0x9c) | 0x80);
    }
    if (uVar2 == 0) {
      if (uVar3 < 0x800000) goto LAB_00408f98;
      uVar3 = 0x7fffff;
      uVar2 = *(uint *)(core_regs + 0x9c) | 0x40;
    }
    else if (uVar2 == 0x1ff) {
      if (0x7fffff < uVar3) goto LAB_00408f98;
      uVar3 = 0x800000;
      uVar2 = *(uint *)(core_regs + 0x9c) | 0x40;
    }
    else {
      uVar3 = (0xff < (int)uVar2) + 0x7fffff;
      uVar2 = *(uint *)(core_regs + 0x9c) | 0x40;
    }
    core_set_reg(0x27,uVar2);
LAB_00408f98:
    core_set_reg(dst,uVar3 & 0xffffff);
    return;
  default:
    goto switchD_00408dd0_default;
  }
  uVar2 = *(uint *)(core_regs + 0x9c) & 0xc00;
  if (uVar2 == 0x400) {
    uVar2 = *(uint *)(core_regs + 0x49c) >> 1;
    uVar3 = *(uint *)(core_regs + 0x498) >> 1;
    if (((byte)*(uint *)(core_regs + 0x4a0) & 1) == 1) {
      uVar2 = uVar2 | 0x800000;
    }
    if (((byte)*(uint *)(core_regs + 0x49c) & 1) == 1) {
      uVar3 = uVar3 | 0x800000;
    }
    uVar4 = *(uint *)(core_regs + 0x4a0) >> 1;
    if ((uVar4 & 0x40) != 0) {
      uVar4 = uVar4 | 0x180;
    }
  }
  else if (uVar2 == 0x800) {
    uVar2 = *(int *)(core_regs + 0x49c) * 2;
    uVar3 = *(uint *)(core_regs + 0x498) * 2 & 0xffffff;
    if (0x7fffff < *(uint *)(core_regs + 0x498)) {
      uVar2 = uVar2 + 1;
    }
    uVar4 = *(int *)(core_regs + 0x4a0) * 2;
    if (0xffffff < uVar2) {
      uVar4 = uVar4 + 1;
      uVar2 = uVar2 & 0xffffff;
    }
  }
  else {
    uVar4 = *(uint *)(core_regs + 0x4a0);
    uVar2 = *(uint *)(core_regs + 0x49c);
    uVar3 = *(uint *)(core_regs + 0x498);
    if ((uVar4 & 0x80) != 0) {
      uVar4 = uVar4 | 0x100;
    }
  }
  if ((3 < *(uint *)(cur_dtype + 8)) &&
     (((uVar2 & 0x600000) == 0x400000 || ((uVar2 & 0x600000) == 0x200000)))) {
    core_set_reg(0x27,*(uint *)(core_regs + 0x9c) | 0x80);
  }
  if (uVar4 == 0) {
    if (0x7fffff < uVar2) {
      uVar2 = 0x7fffff;
      uVar4 = *(uint *)(core_regs + 0x9c) | 0x40;
      uVar3 = 0xffffff;
      goto LAB_0040911c;
    }
  }
  else {
    if (uVar4 == 0x1ff) {
      if (0x7fffff < uVar2) goto LAB_00409126;
      uVar3 = 0;
      uVar4 = *(uint *)(core_regs + 0x9c) | 0x40;
      uVar2 = 0x800000;
    }
    else if ((int)uVar4 < 0x100) {
      uVar2 = 0x7fffff;
      uVar4 = *(uint *)(core_regs + 0x9c) | 0x40;
      uVar3 = 0xffffff;
    }
    else {
      uVar3 = 0;
      uVar4 = *(uint *)(core_regs + 0x9c) | 0x40;
      uVar2 = 0x800000;
    }
LAB_0040911c:
    core_set_reg(0x27,uVar4);
  }
LAB_00409126:
  core_set_reg(0x52,uVar2 & 0xffffff);
  core_set_reg(0x53,uVar3 & 0xffffff);
switchD_00408dd0_default:
  return;
}


/* ==== core_agu_setup @ 00409170 ==== */

void __cdecl core_agu_setup(ulong ea,int latch)

{
  uint mode;
  int dst;
  int dst_00;
  uint rn;
  int dst_01;
  
  if ((ea != 0x34) && (ea != 0x30)) {
    rn = ea & 7;
    mode = ea >> 3 & 7;
    if (rn < 4) {
      dst_01 = 0x4b;
      dst_00 = 0x49;
      dst = 0x4d;
    }
    else {
      dst_01 = 0x4c;
      dst_00 = 0x4a;
      dst = 0x4e;
    }
    if (latch != 0) {
      core_read_copy(rn + 0x1e,dst);
      core_read_copy(rn + 0xc,dst_00);
      core_read_copy(rn + 0x14,dst_01);
      core_agu_calc(mode,rn);
      return;
    }
    *(undefined4 *)(core_regs + dst * 4) = *(undefined4 *)(core_regs + 0x78 + rn * 4);
    *(undefined4 *)(core_regs + dst_00 * 4) = *(undefined4 *)(core_regs + 0x30 + rn * 4);
    *(undefined4 *)(core_regs + dst_01 * 4) = *(undefined4 *)(core_regs + 0x50 + rn * 4);
    core_agu_calc(mode,rn);
  }
  return;
}


/* ==== core_agu_calc @ 00409230 ==== */

void __cdecl core_agu_calc(ulong mode,ulong rn)

{
  uint uVar1;
  ulong uVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint v;
  uint uVar10;
  bool bVar11;
  int local_4;
  
  if (rn < 4) {
    local_4 = 0x47;
    iVar3 = 0x4b;
    iVar8 = 0x49;
    iVar6 = 0x4d;
  }
  else {
    local_4 = 0x48;
    iVar3 = 0x4c;
    iVar8 = 0x4a;
    iVar6 = 0x4e;
  }
  uVar10 = *(uint *)(core_regs + iVar6 * 4);
  switch(mode) {
  case 0:
    rn = 1;
    v = *(uint *)(core_regs + iVar3 * 4);
    goto LAB_004092b2;
  case 1:
  case 5:
    v = *(uint *)(core_regs + iVar3 * 4);
    break;
  case 2:
  case 7:
    v = 1;
    rn = 1;
    goto LAB_004092b2;
  case 3:
    v = 1;
    break;
  default:
    v = 0;
  }
  rn = 0;
LAB_004092b2:
  uVar2 = rn;
  uVar7 = *(uint *)(core_regs + iVar8 * 4);
  if (uVar7 == 0) {
    bit_reverse16(uVar10,&mode);
    if (uVar2 != 0) {
      v = v ^ 0xffff;
    }
    bit_reverse16(v,&rn);
    bit_reverse16(uVar2 + rn + mode,(ulong *)(core_regs + local_4 * 4));
    return;
  }
  if (rn != 0) {
    v = v ^ 0xffff;
  }
  if ((*(uint *)(cur_dtype + 8) < 4) || ((uVar7 & 0xc000) != 0x8000)) {
    bVar11 = false;
  }
  else {
    bVar11 = true;
  }
  iVar3 = 0xf - (uint)bVar11;
  puVar4 = &bit_mask_tab + iVar3;
  uVar9 = (&bit_mask_tab)[iVar3];
  while ((uVar9 & uVar7) == 0) {
    puVar4 = puVar4 + -1;
    iVar3 = iVar3 + -1;
    uVar9 = *puVar4;
  }
  uVar9 = rn + v + uVar10 & 0xffff;
  if (!bVar11) {
    uVar1 = *(uint *)(&agu_wrap_mask_tab + iVar3 * 4);
    uVar5 = v >> 0xf & 1;
    bVar11 = uVar1 < (uVar1 & uVar10) + rn + (uVar1 & v);
    if (uVar5 == 0) {
      uVar7 = uVar7 ^ 0xffff;
    }
    uVar10 = uVar5 + uVar9 + uVar7 & 0xffff;
    if (uVar5 == 0) {
      if ((int)uVar1 < (int)((uVar1 & uVar7) + uVar5 + (uVar1 & uVar9)) || bVar11) {
        uVar9 = uVar10;
      }
      *(uint *)(core_regs + local_4 * 4) = uVar9;
      return;
    }
    if (!bVar11) {
      uVar9 = uVar10;
    }
    *(uint *)(core_regs + local_4 * 4) = uVar9;
    return;
  }
  *(uint *)(core_regs + local_4 * 4) = uVar7 & 0x7fff & uVar9 | uVar10 & ~(uVar7 & 0x7fff);
  return;
}


/* ==== bit_reverse16 @ 00409440 ==== */

void __cdecl bit_reverse16(ulong v,ulong *out)

{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  
  uVar3 = 0;
  puVar2 = &bit_mask_tab;
  puVar1 = &DAT_004aab54;
  do {
    if ((*puVar2 & v) != 0) {
      uVar3 = uVar3 | *puVar1;
    }
    puVar1 = puVar1 + -1;
    puVar2 = puVar2 + 1;
  } while (0x4aab14 < (int)puVar1);
  *out = uVar3;
  return;
}


/* ==== core_agu_writeback @ 00409470 ==== */

void __cdecl core_agu_writeback(ulong ea,int flag)

{
  uint uVar1;
  
  if ((ea != 0x34) && (ea != 0x30)) {
    uVar1 = ea >> 3 & 7;
    if ((flag != 0) && ((uVar1 < 4 || (uVar1 == 7)))) {
      core_copy_reg((ea & 7) + 0x1e,0x48 - (uint)((ea & 7) < 4));
    }
  }
  return;
}


/* ==== core_ext_addr_match @ 004094c0 ==== */

int __cdecl core_ext_addr_match(int space,ulong addr)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = 0;
  if ((*(byte *)(cur_dtype + 8) & 0x80) != 0) {
    uVar1 = *(uint *)(core_regs + 200);
    uVar3 = (uVar1 & 0x1e) << 0xb;
    if ((((uVar1 & 1) != 0) &&
        ((((uVar1 & 0x20) == 0 || ((space == 0x12 && ((uVar1 & 0x2000) != 0)))) ||
         ((space == 0x17 && ((uVar1 & 0x2000) == 0)))))) &&
       ((uVar3 & addr) == (uVar3 & (uVar1 & 0x1e00) << 3))) {
      iVar2 = 1;
    }
  }
  return iVar2;
}


/* ==== core_mem_write @ 00409530 ==== */

void __cdecl core_mem_write(ulong space,ulong addr,ulong *data,ulong strobe)

{
  int iVar1;
  int space_00;
  int iVar2;
  ulong addr_00;
  
  addr_00 = addr;
  space_00 = memmap_find(space,addr);
  iVar1 = *(int *)(cur_dev + 0xc);
  iVar2 = *(int *)(cur_dtype + 0x20) + space_00 * 0x2c;
  if ((*(uint *)(core_regs + 0x270) & strobe) != 0) {
    *data = *(ulong *)(core_regs + 0x180);
  }
  addr = *data;
  switch(space) {
  case 0x12:
  case 0x17:
    iVar2 = core_ext_addr_match(space,addr_00);
    if (iVar2 != 0) {
      addr_00 = core_ext_addr(addr_00);
      space = 0x11d;
      space_00 = memmap_find(0x11d,addr_00);
      if ((*(uint *)(core_regs + 200) & 0x100) != 0) {
        core_touch_read(0x33);
        core_touch_read(0x36);
        *(undefined4 *)(core_regs + 0xf0) = *(undefined4 *)(core_regs + 0xd8);
        if (*(int *)(core_regs + 0xf0) == 0) {
          *(undefined4 *)(core_regs + 0xfc) = 1;
        }
        *(uint *)(core_regs + 200) = *(uint *)(core_regs + 200) & 0xfffffeff;
        core_touch_reg(0x32);
      }
    }
  case 0xd:
    if ((*(uint *)(cur_dtype + 8) & 0x3618) == 0) {
      mdisk_write(*(int *)(cur_dev + 4),space,addr_00,addr);
      *(ulong *)(core_pins_data + 8) = addr;
      io_out_reg_write(4,&addr,0);
    }
    break;
  case 0x13:
    if ((*(uint *)(iVar2 + 0x18) & 0x10000) != 0) {
      dev_spaces_call_c(addr_00,addr,1);
      break;
    }
  case 0xe:
  case 0x18:
    if ((*(byte *)(iVar2 + 0x18) & 8) == 0) {
      *(ulong *)(*(int *)(space_00 * 0x10 + iVar1 + 8) + (addr_00 - *(int *)(iVar2 + 0xc)) * 4) =
           addr;
    }
  }
  mem_trace_access(space,addr_00,0,0);
  *(undefined4 *)(core_regs + 0x1dc) = 0;
  io_out_mem_write(space_00,addr_00,addr);
  if (profiler_hook != (undefined *)0x0) {
    ref_record(space,addr_00,addr,1,0);
  }
  return;
}


/* ==== core_ext_addr @ 00409730 ==== */

ulong __cdecl core_ext_addr(ulong addr)

{
  return (*(uint *)(core_regs + 0xcc) & 0xff00) << 8 | addr & 0xffff;
}


/* ==== core_irq_arbitrate @ 00409750 ==== */

int core_irq_arbitrate(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int local_14;
  int local_10;
  int local_c;
  
  iVar1 = *(int *)(cur_dtype + 0x14);
  uVar8 = 0;
  local_10 = 0;
  iVar5 = core_irq_scan();
  if (-1 < iVar5) {
    local_10 = iVar5;
    if (iVar5 == 8) {
      uVar8 = *(uint *)(core_regs + 0x41c);
    }
    else if (iVar5 == 0x2c) {
      uVar8 = *(uint *)(core_regs + 0x44c);
    }
    else if (iVar5 == 0x2e) {
      uVar8 = *(uint *)(core_regs + 0x450);
    }
    else if (iVar5 == 10) {
      uVar8 = *(uint *)(core_regs + 0x420);
    }
    else {
      uVar8 = 4;
    }
  }
  local_c = 0;
  uVar2 = *(uint *)(core_regs + 0x24);
  iVar5 = 1;
  if (1 < iVar1) {
    local_14 = 0x48;
    do {
      uVar3 = *(uint *)(*(int *)(cur_dtype + 0x18) + 0x28 + local_14);
      if ((uVar3 != 0) &&
         (iVar6 = (**(code **)(*(int *)(*(int *)(cur_dtype + 0x18) + local_14 + 0x2c) + 0x18))
                            (iVar5), -1 < iVar6)) {
        uVar7 = uVar3;
        for (uVar4 = uVar3 >> 1 & uVar3; uVar4 != 0; uVar4 = uVar4 & uVar4 >> 1) {
          uVar7 = uVar4;
        }
        uVar7 = (uVar3 & uVar2) / uVar7;
        if (uVar8 < uVar7) {
          uVar8 = uVar7;
          local_10 = iVar6;
          local_c = iVar5;
        }
      }
      iVar5 = iVar5 + 1;
      local_14 = local_14 + 0x48;
    } while (iVar5 < iVar1);
  }
  if ((uVar8 != 0) && ((int)(*(uint *)(core_regs + 0x9c) >> 8 & 3) < (int)uVar8)) {
    *(uint *)(core_regs + 0x2e0) = uVar8;
    *(int *)(core_regs + 0x3e4) = local_10;
    *(int *)(core_regs + 0x3c4) = local_c;
    return 1;
  }
  return 0;
}


/* ==== core_irq_scan @ 004098a0 ==== */

int core_irq_scan(void)

{
  uint uVar1;
  undefined4 uVar2;
  
  if (*(int *)(core_regs + 0x278) != 0) {
    *(undefined4 *)(core_regs + 0x40c) = 4;
  }
  *(uint *)(core_regs + 0x41c) = *(uint *)(core_regs + 0x24) & 3;
  if ((*(byte *)(core_regs + 0x24) & 4) == 0) {
    if (*(int *)(core_regs + 0x2e4) == 0) {
LAB_004098f7:
      uVar2 = *(undefined4 *)(core_regs + 0x41c);
    }
    else {
      uVar2 = 0;
    }
    *(undefined4 *)(core_regs + 0x414) = uVar2;
  }
  else if ((*(int *)(core_regs + 0x414) != 0) || (*(int *)(core_regs + 0x2d0) != 0))
  goto LAB_004098f7;
  *(uint *)(core_regs + 0x420) = *(uint *)(core_regs + 0x24) >> 3 & 3;
  if ((*(byte *)(core_regs + 0x24) & 0x20) == 0) {
    if (*(int *)(core_regs + 0x2e8) == 0) goto LAB_00409944;
    uVar2 = 0;
  }
  else {
    if ((*(int *)(core_regs + 0x418) == 0) && (*(int *)(core_regs + 0x2d4) == 0)) goto LAB_00409955;
LAB_00409944:
    uVar2 = *(undefined4 *)(core_regs + 0x420);
  }
  *(undefined4 *)(core_regs + 0x418) = uVar2;
LAB_00409955:
  if ((*(byte *)(cur_dtype + 8) & 0x60) == 0) {
    if (*(int *)(core_regs + 0x404) != 0) {
      return 0x3e;
    }
    if (*(int *)(core_regs + 0x400) != 0) {
      return 0x1e;
    }
    if (*(int *)(core_regs + 0x408) != 0) {
      return 2;
    }
    if (*(int *)(core_regs + 0x40c) != 0) {
      return 4;
    }
    if (*(int *)(core_regs + 0x410) != 0) {
      return 6;
    }
    if ((*(uint *)(core_regs + 0x414) != 0) &&
       (*(uint *)(core_regs + 0x418) <= *(uint *)(core_regs + 0x414))) {
      return 8;
    }
    return (-(uint)(*(int *)(core_regs + 0x418) != 0) & 0xb) - 1;
  }
  if ((*(int *)(core_regs + 0x444) != 0) || (*(int *)(core_regs + 0x42c) != 0)) {
    *(uint *)(core_regs + 0x44c) = *(uint *)(core_regs + 0x24) >> 6 & 3;
    *(undefined4 *)(core_regs + 0x444) = *(undefined4 *)(core_regs + 0x44c);
  }
  if ((*(int *)(core_regs + 0x448) != 0) || (*(int *)(core_regs + 0x430) != 0)) {
    *(uint *)(core_regs + 0x450) = *(uint *)(core_regs + 0x24) >> 8 & 3;
    *(undefined4 *)(core_regs + 0x448) = *(undefined4 *)(core_regs + 0x450);
  }
  if (*(int *)(core_regs + 0x404) != 0) {
    return 0x3e;
  }
  if (*(int *)(core_regs + 0x400) != 0) {
    return 0x1e;
  }
  if (*(int *)(core_regs + 0x408) != 0) {
    return 2;
  }
  if (*(int *)(core_regs + 0x40c) != 0) {
    return 4;
  }
  if (*(int *)(core_regs + 0x410) != 0) {
    return 6;
  }
  uVar1 = *(uint *)(core_regs + 0x414);
  if ((((uVar1 != 0) && (*(uint *)(core_regs + 0x418) <= uVar1)) &&
      (*(uint *)(core_regs + 0x444) <= uVar1)) && (*(uint *)(core_regs + 0x448) <= uVar1)) {
    return 8;
  }
  uVar1 = *(uint *)(core_regs + 0x418);
  if (((uVar1 != 0) && (*(uint *)(core_regs + 0x444) <= uVar1)) &&
     (*(uint *)(core_regs + 0x448) <= uVar1)) {
    return 10;
  }
  if ((*(uint *)(core_regs + 0x444) != 0) &&
     (*(uint *)(core_regs + 0x448) <= *(uint *)(core_regs + 0x444))) {
    return 0x2c;
  }
  return (-(uint)(*(int *)(core_regs + 0x448) != 0) & 0x2f) - 1;
}


/* ==== core_irq_ack @ 00409b10 ==== */

void core_irq_ack(void)

{
  (**(code **)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + *(int *)(core_regs + 0x3c4) * 0x48) +
              0x1c))(*(int *)(core_regs + 0x3c4),*(uint *)(core_regs + 0x3e4) & 0xfffffffe);
  return;
}


/* ==== core_mem_read @ 00409b40 ==== */

void __cdecl core_mem_read(ulong space,ulong addr,ulong *data,ulong strobe)

{
  int iVar1;
  int iVar2;
  int iVar3;
  ulong addr_00;
  ulong space_00;
  
  addr_00 = addr;
  space_00 = space;
  iVar2 = memmap_find(space,addr);
  space = 0;
  iVar1 = *(int *)(cur_dtype + 0x20) + iVar2 * 0x2c;
  switch(space_00) {
  case 0x12:
  case 0x17:
    iVar3 = core_ext_addr_match(space_00,addr_00);
    if (iVar3 != 0) {
      addr_00 = core_ext_addr(addr_00);
      space_00 = 0x11d;
      iVar2 = memmap_find(0x11d,addr_00);
      if ((*(uint *)(core_regs + 200) & 0x100) == 0) {
        space = 1;
      }
      else {
        space = 2;
        *(uint *)(core_regs + 200) = *(uint *)(core_regs + 200) & 0xfffffeff;
        core_touch_reg(0x32);
        core_touch_read(0x33);
        core_touch_read(0x35);
        *(undefined4 *)(core_regs + 0xfc) = *(undefined4 *)(core_regs + 0xd4);
        if (*(int *)(core_regs + 0xfc) == 0) {
          *(undefined4 *)(core_regs + 0xfc) = 1;
        }
      }
    }
  case 0xd:
    if ((*(uint *)(cur_dtype + 8) & 0x3618) == 0) {
      addr = *core_pins_data;
      mdisk_read(*(int *)(cur_dev + 4),space_00,addr_00,&addr,1);
      iVar3 = io_in_reg_read(4,&addr);
      if (iVar3 != 0) {
        mem_reg_write(space_00,addr_00,(ulong)&addr);
      }
    }
    else {
      addr = 5;
    }
    break;
  case 0x13:
    if ((*(uint *)(iVar1 + 0x18) & 0x10000) != 0) {
      dev_spaces_call_8(addr_00,(long *)&addr,1);
      break;
    }
  default:
    addr = *(ulong *)(*(int *)(iVar2 * 0x10 + *(int *)(cur_dev + 0xc) + 8) +
                     (addr_00 - *(int *)(iVar1 + 0xc)) * 4);
  }
  iVar2 = io_in_mem_read(iVar2,addr_00,&addr);
  if (iVar2 != 0) {
    mem_reg_write(space_00,addr_00,(ulong)&addr);
  }
  if (space == 2) {
    *(ulong *)(core_regs + 0xf8) = addr;
  }
  if (space != 0) {
    addr = *(ulong *)(core_regs + 0xf4);
  }
  if (((*(uint *)(cur_dtype + 8) & 0x3618) == 0) && ((*(uint *)(iVar1 + 8) & 0xa800000) != 0)) {
    *core_pins_data = addr;
  }
  mem_trace_access(space_00,addr_00,1,0);
  if (*(int *)(core_regs + 0x234) != 0) {
    *data = addr;
  }
  if ((strobe & *(uint *)(core_regs + 0x270)) != 0) {
    *(ulong *)(core_regs + 0x180) = addr;
  }
  if (profiler_hook != (undefined *)0x0) {
    ref_record(space_00,addr_00,*data,0,0);
  }
  return;
}


/* ==== core_write_from_bus @ 00409dd0 ==== */

void __cdecl core_write_from_bus(int src,int dst)

{
  uint uVar1;
  
  if (src < 0) {
    return;
  }
  if (src == 0x28) {
    core_ss_push(dst,0x56);
    return;
  }
  if (src == 0x29) {
    core_ss_push(0x56,dst);
    return;
  }
  if (src != 0x12a) {
    if (src == 299) {
      if (dst == 0x53) {
        core_copy_reg_quiet(5,0x53);
        return;
      }
      uVar1 = *(uint *)(core_regs + dst * 4);
    }
    else {
      if (src == 300) {
        uVar1 = *(uint *)(core_regs + dst * 4);
        goto LAB_00409e9d;
      }
      if (src != 0x12d) {
        core_copy_reg(src,dst);
        return;
      }
      uVar1 = *(uint *)(core_regs + dst * 4);
    }
    core_set_reg_quiet(7,-(uint)((uVar1 & 0x800000) != 0) & 0xff);
    core_copy_reg_quiet(6,dst);
    core_set_reg(5,0);
    return;
  }
  if (dst == 0x53) {
    core_copy_reg_quiet(1,0x53);
    return;
  }
  uVar1 = *(uint *)(core_regs + dst * 4);
LAB_00409e9d:
  core_set_reg_quiet(3,-(uint)((uVar1 & 0x800000) != 0) & 0xff);
  core_copy_reg_quiet(2,dst);
  core_set_reg(1,0);
  return;
}


/* ==== core_do_loop_end @ 00409f20 ==== */

void core_do_loop_end(void)

{
  core_ss_pop(0x57,0x56);
  core_ss_dec();
  *(uint *)(core_regs + 0x9c) = *(uint *)(core_regs + 0x9c) & 0xffff7fff;
  *(uint *)(core_regs + 0x9c) = *(uint *)(core_regs + 0x9c) | *(uint *)(core_regs + 0x158) & 0x8000;
  core_touch_reg(0x27);
  core_ss_pop(10,0xb);
  core_ss_dec();
  core_touch_reg(0xb);
  core_touch_reg(10);
  return;
}


/* ==== core_bit_test @ 00409fa0 ==== */

int core_bit_test(void)

{
  return (uint)(((&bit_mask_tab)[*(int *)(core_regs + 0x2cc)] & *(uint *)(core_regs + 0x180)) != 0);
}


/* ==== core_bit_test_not @ 00409fd0 ==== */

int core_bit_test_not(void)

{
  return (uint)(((&bit_mask_tab)[*(int *)(core_regs + 0x2cc)] & *(uint *)(core_regs + 0x180)) == 0);
}


/* ==== core_bit_op @ 0040a000 ==== */

void core_bit_op(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = core_bit_test();
  if (iVar2 == 0) {
    uVar3 = *(uint *)(core_regs + 0x9c) & 0xfffe;
  }
  else {
    uVar3 = *(uint *)(core_regs + 0x9c) | 1;
  }
  *(uint *)(core_regs + 0x9c) = uVar3;
  core_touch_reg(0x27);
  iVar1 = *(int *)(core_regs + 0x2c8);
  if (iVar1 == 0) {
    uVar3 = (&bit_mask_tab)[*(int *)(core_regs + 0x2cc)];
  }
  else {
    if (iVar1 == 1) {
      *(uint *)(core_regs + 0x180) =
           *(uint *)(core_regs + 0x180) | (&bit_mask_tab)[*(int *)(core_regs + 0x2cc)];
      return;
    }
    if (iVar1 != 2) {
      return;
    }
    uVar3 = (&bit_mask_tab)[*(int *)(core_regs + 0x2cc)];
    if (iVar2 == 0) {
      *(uint *)(core_regs + 0x180) = *(uint *)(core_regs + 0x180) | uVar3;
      return;
    }
  }
  *(uint *)(core_regs + 0x180) = *(uint *)(core_regs + 0x180) & ~uVar3;
  return;
}


