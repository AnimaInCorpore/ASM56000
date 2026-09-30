/* ==== swap_ptrs @ 0041cfb0 ==== */

void __cdecl swap_ptrs(void **a,void **b)

{
  void *pvVar1;
  
  pvVar1 = *b;
  *b = *a;
  *a = pvVar1;
  return;
}


/* ==== dec_alu @ 0041cfd0 ==== */

void __cdecl dec_alu(ulong opw,void *dec)

{
  if ((char)opw != '\0') {
    dec_flag_nomove(dec);
    if ((opw & 0x80) != 0) {
      dec_alu_mpy(opw,dec);
      return;
    }
    dec_alu_dp(opw,dec);
  }
  return;
}


/* ==== dec_flag_nomove @ 0041d010 ==== */

void __cdecl dec_flag_nomove(void *dec)

{
  *(uint *)((int)dec + 0xac) = *(uint *)((int)dec + 0xac) | 0x20;
  return;
}


/* ==== dec_alu_dp @ 0041d020 ==== */

void __cdecl dec_alu_dp(ulong opw,void *dec)

{
  int iVar1;
  undefined4 *puVar2;
  
  *(undefined4 *)((int)dec + 8) = 0xc;
  iVar1 = *(int *)(&DAT_004bfd80 + (opw & 0x7f) * 4);
  *(int *)((int)dec + 0xc) = iVar1;
  puVar2 = (undefined4 *)((int)dec + 0x1c);
  if (iVar1 == 0) {
    puVar2 = (undefined4 *)((int)dec + 8);
  }
  *puVar2 = 0xc;
  puVar2[1] = *(undefined4 *)(&DAT_004c0000 + (opw >> 3 & 1) * 4);
  *(undefined4 *)dec = *(undefined4 *)(&DAT_004c0158 + ((opw >> 4 & 7) << 3 | opw & 7) * 4);
  return;
}


/* ==== dec_alu_mpy @ 0041d090 ==== */

void __cdecl dec_alu_mpy(ulong opw,void *dec)

{
  uint uVar1;
  
  uVar1 = opw >> 4 & 7;
  *(undefined4 *)((int)dec + 8) = 0xc;
  *(undefined4 *)((int)dec + 0xc) = *(undefined4 *)(&DAT_004c0098 + uVar1 * 4);
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c00d8 + uVar1 * 4);
  *(undefined4 *)((int)dec + 0x30) = 0xc;
  *(undefined4 *)((int)dec + 0x34) = *(undefined4 *)(&DAT_004c0000 + (opw >> 3 & 1) * 4);
  *(uint *)((int)dec + 0xb0) = (-(uint)((opw & 4) != 0) & 0xfffffffe) + 1;
  *(undefined4 *)dec = *(undefined4 *)(&DAT_004c0148 + (opw & 3) * 4);
  return;
}


/* ==== dec_ea6 @ 0041d100 ==== */

void __cdecl dec_ea6(long *slot,ulong ea6)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = ea6 & 7;
  uVar1 = ea6 >> 3 & 7;
  if (uVar1 == 6) {
    if (uVar2 == 0) {
      *slot = 9;
    }
    else if (uVar2 == 4) {
      *slot = 10;
      slot[3] = 0;
    }
    slot[1] = 0;
    slot[2] = dec_extword;
    dec_uses_extword = 1;
    return;
  }
  *slot = uVar1 + 1;
  slot[1] = uVar2 + 0x21;
  slot[2] = 0;
  return;
}


/* ==== dec_c1_enddo @ 0041d170 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c1_enddo(ulong opw,void *dec)

{
  ulong opw_00;
  void *dec_00;
  uint uVar1;
  
  dec_00 = dec;
  opw_00 = opw;
  uVar1 = opw >> 8;
  opw = (int)dec + 0x58;
  dec = (void *)((int)dec + 0x6c);
  dec_alu(opw_00,dec_00);
  if ((uVar1 & 0x80) == 0) {
    swap_ptrs((void **)&opw,&dec);
  }
  *(uint *)(opw + 0xc) = ((uVar1 & 0x800) != 0) + 1;
  dec_ea6((long *)opw,uVar1 & 0x3f);
  *(undefined4 *)dec = 0xc;
  *(undefined4 *)((int)dec + 4) =
       *(undefined4 *)(&DAT_004bfc80 + (((uVar1 & 0xffff) >> 1 & 0x1800 | uVar1 & 0x700) >> 8) * 4);
  return;
}


/* ==== dec_c2_doforever @ 0041d220 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c2_doforever(ulong opw,void *dec)

{
  ulong opw_00;
  void *dec_00;
  uint uVar1;
  
  dec_00 = dec;
  opw_00 = opw;
  uVar1 = opw >> 8;
  opw = (int)dec + 0x58;
  dec = (void *)((int)dec + 0x6c);
  dec_alu(opw_00,dec_00);
  if ((uVar1 & 0x80) == 0) {
    swap_ptrs((void **)&opw,&dec);
  }
  *(uint *)(opw + 0xc) = ((uVar1 & 0x800) != 0) + 1;
  *(undefined4 *)opw = 9;
  *(uint *)(opw + 8) = uVar1 & 0x3f;
  *(undefined4 *)dec = 0xc;
  *(undefined4 *)((int)dec + 4) =
       *(undefined4 *)(&DAT_004bfc80 + (((uVar1 & 0xffff) >> 1 & 0x1800 | uVar1 & 0x700) >> 8) * 4);
  return;
}


/* ==== dec_c9_enddo @ 0041d2d0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c9_enddo(ulong opw,void *dec)

{
  ulong opw_00;
  void *dec_00;
  uint uVar1;
  uint uVar2;
  long *plStack_8;
  undefined4 *puStack_4;
  
  dec_00 = dec;
  opw_00 = opw;
  uVar1 = opw >> 8;
  opw = (int)dec + 0x58;
  plStack_8 = (long *)((int)dec + 0x80);
  puStack_4 = (undefined4 *)((int)dec + 0x94);
  uVar2 = (uVar1 & 0x300 | (uVar1 & 0xffff) >> 1 & 0x400) >> 8;
  dec = (void *)((int)dec + 0x6c);
  dec_alu(opw_00,dec_00);
  if ((uVar1 & 0x80) == 0) {
    swap_ptrs((void **)&opw,&dec);
    swap_ptrs(&plStack_8,&puStack_4);
  }
  *(undefined4 *)(opw + 0xc) = 1;
  dec_ea6((long *)opw,uVar1 & 0x3f);
  *(undefined4 *)dec = 0xc;
  *(undefined4 *)((int)dec + 4) = *(undefined4 *)(&DAT_004bff80 + uVar2 * 4);
  plStack_8[3] = 2;
  dec_ea6(plStack_8,uVar1 & 0x3f);
  *puStack_4 = 0xc;
  puStack_4[1] = *(undefined4 *)(&DAT_004bffa0 + uVar2 * 4);
  return;
}


/* ==== dec_c10_doforever @ 0041d3d0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c10_doforever(ulong opw,void *dec)

{
  ulong opw_00;
  void *dec_00;
  uint uVar1;
  uint uVar2;
  undefined4 *puStack_8;
  undefined4 *puStack_4;
  
  dec_00 = dec;
  opw_00 = opw;
  uVar1 = opw >> 8;
  opw = (int)dec + 0x58;
  puStack_8 = (undefined4 *)((int)dec + 0x6c);
  puStack_4 = (undefined4 *)((int)dec + 0x94);
  uVar2 = (uVar1 & 0x300 | (uVar1 & 0xffff) >> 1 & 0x400) >> 8;
  dec = (void *)((int)dec + 0x80);
  dec_alu(opw_00,dec_00);
  if ((uVar1 & 0x80) == 0) {
    swap_ptrs((void **)&opw,&puStack_8);
    swap_ptrs(&dec,&puStack_4);
  }
  *(undefined4 *)(opw + 0xc) = 1;
  *(undefined4 *)opw = 9;
  *(uint *)(opw + 8) = uVar1 & 0x3f;
  *puStack_8 = 0xc;
  puStack_8[1] = *(undefined4 *)(&DAT_004bff80 + uVar2 * 4);
  *(undefined4 *)((int)dec + 0xc) = 2;
  *(undefined4 *)dec = 9;
  *(uint *)((int)dec + 8) = uVar1 & 0x3f;
  *puStack_4 = 0xc;
  puStack_4[1] = *(undefined4 *)(&DAT_004bffa0 + uVar2 * 4);
  return;
}


/* ==== dec_c11_pm @ 0041d4d0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c11_pm(ulong opw,void *dec)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = opw >> 8 & 0xff;
  uVar2 = (opw >> 8 & 0xffff) >> 8;
  uVar3 = uVar2 & 0x1f;
  if (((uVar2 & 0x18) == 0) || (((byte)uVar3 & 0x1e) == 0xe)) {
    uVar1 = uVar1 << 8;
  }
  dec_alu(opw,dec);
  *(undefined4 *)((int)dec + 0x58) = 10;
  *(uint *)((int)dec + 0x60) = uVar1;
  *(undefined4 *)((int)dec + 0x6c) = 0xc;
  *(undefined4 *)((int)dec + 0x70) = *(undefined4 *)(&DAT_004bfc80 + uVar3 * 4);
  return;
}


/* ==== dec_c15_pm @ 0041d530 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c15_pm(ulong opw,void *dec)

{
  dec_alu(opw,dec);
  *(undefined4 *)((int)dec + 0x58) = 0xc;
  *(undefined4 *)((int)dec + 0x5c) =
       *(undefined4 *)(&DAT_004bfc80 + ((opw >> 8 & 0xffff) >> 5 & 0x1f) * 4);
  *(undefined4 *)((int)dec + 0x6c) = 0xc;
  *(undefined4 *)((int)dec + 0x70) = *(undefined4 *)(&DAT_004bfc80 + (opw >> 8 & 0x1f) * 4);
  return;
}


/* ==== dec_pm_update @ 0041d580 ==== */

void __cdecl dec_pm_update(ulong opw,void *dec)

{
  dec_alu(opw,dec);
  dec_ea6((long *)((int)dec + 0x58),opw >> 8 & 0x3f);
  return;
}


/* ==== dec_c19_pm @ 0041d5b0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c19_pm(ulong opw,void *dec)

{
  dec_alu(opw,dec);
  return;
}


/* ==== dec_c20_enddo @ 0041d5d0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c20_enddo(ulong opw,void *dec)

{
  undefined4 uVar1;
  ulong opw_00;
  void *dec_00;
  uint uVar2;
  
  dec_00 = dec;
  opw_00 = opw;
  uVar2 = opw >> 8;
  opw = (int)dec + 0x80;
  dec = (void *)((int)dec + 0x94);
  dec_alu(opw_00,dec_00);
  *(undefined4 *)((int)dec_00 + 0x58) = 0xc;
  uVar1 = *(undefined4 *)(&DAT_004c0000 + ((uVar2 & 0xffff) >> 0xb & 1) * 4);
  *(undefined4 *)((int)dec_00 + 0x6c) = 0xc;
  *(undefined4 *)((int)dec_00 + 0x5c) = uVar1;
  *(uint *)((int)dec_00 + 0x70) = ((uVar2 & 0x400) != 0) + 0x31;
  if ((uVar2 & 0x80) == 0) {
    swap_ptrs((void **)&opw,&dec);
  }
  *(undefined4 *)(opw + 0xc) = 2;
  dec_ea6((long *)opw,uVar2 & 0x3f);
  *(undefined4 *)dec = 0xc;
  *(undefined4 *)((int)dec + 4) = *(undefined4 *)(&DAT_004c0290 + ((uVar2 & 0xffff) >> 8 & 3) * 4);
  return;
}


/* ==== dec_c21_pm @ 0041d690 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c21_pm(ulong opw,void *dec)

{
  ulong opw_00;
  void *dec_00;
  uint uVar1;
  uint uVar2;
  
  dec_00 = dec;
  opw_00 = opw;
  uVar1 = opw >> 8;
  uVar2 = uVar1 & 0xffff;
  opw = (int)dec + 0x58;
  dec = (void *)((int)dec + 0x6c);
  dec_alu(opw_00,dec_00);
  if ((uVar1 & 0x80) == 0) {
    swap_ptrs((void **)&opw,&dec);
  }
  *(undefined4 *)(opw + 0xc) = 1;
  dec_ea6((long *)opw,uVar1 & 0x3f);
  *(undefined4 *)dec = 0xc;
  *(undefined4 *)((int)dec + 4) = *(undefined4 *)(&DAT_004c02a0 + (uVar2 >> 10 & 3) * 4);
  *(undefined4 *)((int)dec_00 + 0x80) = 0xc;
  *(undefined4 *)((int)dec_00 + 0x84) = *(undefined4 *)(&DAT_004c0000 + (uVar2 >> 9 & 1) * 4);
  *(undefined4 *)((int)dec_00 + 0x94) = 0xc;
  *(uint *)((int)dec_00 + 0x98) = ((uVar2 >> 8 & 1) != 0) + 0x34;
  return;
}


/* ==== dec_c22_pm @ 0041d770 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c22_pm(ulong opw,void *dec)

{
  if ((opw & 0x20000) != 0) {
    *(ulong *)((int)dec + 0xa8) = opw >> 0xc & 0xf;
  }
  *(ulong *)dec = (opw & 0x10000 | 0x40000) >> 0xe;
  *(undefined4 *)((int)dec + 0x80) = 9;
  *(ulong *)((int)dec + 0x88) = opw & 0xfff;
  return;
}


/* ==== dec_c26_pm @ 0041d7c0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c26_pm(ulong opw,void *dec)

{
  *(ulong *)dec = (opw & 0x10000 | 0x40000) >> 0xe;
  if ((opw & 0x20) != 0) {
    *(ulong *)((int)dec + 0xa8) = opw & 0xf;
  }
  dec_ea6((long *)((int)dec + 0x80),opw >> 8 & 0x3f);
  return;
}


/* ==== dec_c36_jsset @ 0041d810 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c36_jsset(ulong opw,void *dec)

{
  dec_jbit_ea(opw,dec);
  *(undefined4 *)dec = 0x15;
  return;
}


/* ==== dec_jbit_ea @ 0041d830 ==== */

void __cdecl dec_jbit_ea(ulong opw,void *dec)

{
  dec_bit_ea(opw,dec);
  *(undefined4 *)((int)dec + 0x80) = 9;
  *(undefined4 *)((int)dec + 0x88) = dec_extword;
  dec_uses_extword = 1;
  return;
}


/* ==== dec_bit_ea @ 0041d870 ==== */

void __cdecl dec_bit_ea(ulong opw,void *dec)

{
  *(undefined4 *)((int)dec + 0x58) = 10;
  *(ulong *)((int)dec + 0x60) = opw & 0x1f;
  *(uint *)((int)dec + 0x78) = ((opw & 0x40) != 0) + 1;
  dec_ea6((long *)((int)dec + 0x6c),opw >> 8 & 0x3f);
  return;
}


/* ==== dec_c37_jsclr @ 0041d8b0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c37_jsclr(ulong opw,void *dec)

{
  dec_jbit_ea(opw,dec);
  *(undefined4 *)dec = 0x12;
  return;
}


/* ==== dec_h41d8d0 @ 0041d8d0 ==== */

void dec_h41d8d0(ulong param_1,undefined4 *param_2)

{
  dec_jbit_ea(param_1,param_2);
  *param_2 = 0x30;
  return;
}


/* ==== dec_h41d8f0 @ 0041d8f0 ==== */

void dec_h41d8f0(ulong param_1,undefined4 *param_2)

{
  dec_jbit_ea(param_1,param_2);
  *param_2 = 0x2e;
  return;
}


/* ==== dec_c54_jset @ 0041d910 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c54_jset(ulong opw,void *dec)

{
  dec_jbit_ea(opw,dec);
  *(undefined4 *)dec = 0x13;
  return;
}


/* ==== dec_c55_jclr @ 0041d930 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c55_jclr(ulong opw,void *dec)

{
  dec_jbit_ea(opw,dec);
  *(undefined4 *)dec = 0x11;
  return;
}


/* ==== dec_h41d950 @ 0041d950 ==== */

void dec_h41d950(ulong param_1,undefined4 *param_2)

{
  dec_jbit_ea(param_1,param_2);
  *param_2 = 0x2f;
  return;
}


/* ==== dec_h41d970 @ 0041d970 ==== */

void dec_h41d970(ulong param_1,undefined4 *param_2)

{
  dec_jbit_ea(param_1,param_2);
  *param_2 = 0x2d;
  return;
}


/* ==== dec_c30_jsset @ 0041d990 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c30_jsset(ulong opw,void *dec)

{
  dec_jbit_reg(opw,dec);
  *(undefined4 *)dec = 0x15;
  return;
}


/* ==== dec_jbit_reg @ 0041d9b0 ==== */

void __cdecl dec_jbit_reg(ulong opw,void *dec)

{
  dec_bit_reg(opw,dec);
  *(undefined4 *)((int)dec + 0x80) = 9;
  *(undefined4 *)((int)dec + 0x88) = dec_extword;
  dec_uses_extword = 1;
  return;
}


/* ==== dec_bit_reg @ 0041d9f0 ==== */

void __cdecl dec_bit_reg(ulong opw,void *dec)

{
  *(undefined4 *)((int)dec + 0x58) = 10;
  *(ulong *)((int)dec + 0x60) = opw & 0x1f;
  *(undefined4 *)((int)dec + 0x6c) = 0xc;
  *(undefined4 *)((int)dec + 0x70) = *(undefined4 *)(&DAT_004bfc80 + (opw >> 8 & 0x3f) * 4);
  return;
}


/* ==== dec_c31_jsclr @ 0041da20 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c31_jsclr(ulong opw,void *dec)

{
  dec_jbit_reg(opw,dec);
  *(undefined4 *)dec = 0x12;
  return;
}


/* ==== dec_c48_jset @ 0041da40 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c48_jset(ulong opw,void *dec)

{
  dec_jbit_reg(opw,dec);
  *(undefined4 *)dec = 0x13;
  return;
}


/* ==== dec_c49_jclr @ 0041da60 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c49_jclr(ulong opw,void *dec)

{
  dec_jbit_reg(opw,dec);
  *(undefined4 *)dec = 0x11;
  return;
}


/* ==== dec_h41da80 @ 0041da80 ==== */

void dec_h41da80(ulong param_1,undefined4 *param_2)

{
  dec_jbit_reg(param_1,param_2);
  *param_2 = 0x30;
  return;
}


/* ==== dec_h41daa0 @ 0041daa0 ==== */

void dec_h41daa0(ulong param_1,undefined4 *param_2)

{
  dec_jbit_reg(param_1,param_2);
  *param_2 = 0x2e;
  return;
}


/* ==== dec_h41dac0 @ 0041dac0 ==== */

void dec_h41dac0(ulong param_1,undefined4 *param_2)

{
  dec_jbit_reg(param_1,param_2);
  *param_2 = 0x2f;
  return;
}


/* ==== dec_h41dae0 @ 0041dae0 ==== */

void dec_h41dae0(ulong param_1,undefined4 *param_2)

{
  dec_jbit_reg(param_1,param_2);
  *param_2 = 0x2d;
  return;
}


/* ==== dec_c40_jsset @ 0041db00 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c40_jsset(ulong opw,void *dec)

{
  dec_jbit_aa(opw,dec);
  *(undefined4 *)dec = 0x15;
  return;
}


/* ==== dec_jbit_aa @ 0041db20 ==== */

void __cdecl dec_jbit_aa(ulong opw,void *dec)

{
  dec_bit_aa(opw,dec);
  *(undefined4 *)((int)dec + 0x80) = 9;
  *(undefined4 *)((int)dec + 0x88) = dec_extword;
  dec_uses_extword = 1;
  return;
}


/* ==== dec_bit_aa @ 0041db60 ==== */

void __cdecl dec_bit_aa(ulong opw,void *dec)

{
  *(undefined4 *)((int)dec + 0x58) = 10;
  *(ulong *)((int)dec + 0x60) = opw & 0x1f;
  *(undefined4 *)((int)dec + 0x6c) = 9;
  *(uint *)((int)dec + 0x78) = ((opw & 0x40) != 0) + 1;
  *(ulong *)((int)dec + 0x74) = opw >> 8 & 0x3f;
  return;
}


/* ==== dec_c41_jsclr @ 0041dba0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c41_jsclr(ulong opw,void *dec)

{
  dec_jbit_aa(opw,dec);
  *(undefined4 *)dec = 0x12;
  return;
}


/* ==== dec_c58_jset @ 0041dbc0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c58_jset(ulong opw,void *dec)

{
  dec_jbit_aa(opw,dec);
  *(undefined4 *)dec = 0x13;
  return;
}


/* ==== dec_c59_jclr @ 0041dbe0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c59_jclr(ulong opw,void *dec)

{
  dec_jbit_aa(opw,dec);
  *(undefined4 *)dec = 0x11;
  return;
}


/* ==== dec_h41dc00 @ 0041dc00 ==== */

void dec_h41dc00(ulong param_1,undefined4 *param_2)

{
  dec_jbit_aa(param_1,param_2);
  *param_2 = 0x2f;
  return;
}


/* ==== dec_h41dc20 @ 0041dc20 ==== */

void dec_h41dc20(ulong param_1,undefined4 *param_2)

{
  dec_jbit_aa(param_1,param_2);
  *param_2 = 0x2d;
  return;
}


/* ==== dec_h41dc40 @ 0041dc40 ==== */

void dec_h41dc40(ulong param_1,undefined4 *param_2)

{
  dec_jbit_aa(param_1,param_2);
  *param_2 = 0x30;
  return;
}


/* ==== dec_h41dc60 @ 0041dc60 ==== */

void dec_h41dc60(ulong param_1,undefined4 *param_2)

{
  dec_jbit_aa(param_1,param_2);
  *param_2 = 0x2e;
  return;
}


/* ==== dec_c32_jsset @ 0041dc80 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c32_jsset(ulong opw,void *dec)

{
  dec_jbit_pp(opw,dec,0);
  *(undefined4 *)dec = 0x15;
  return;
}


/* ==== dec_jbit_pp @ 0041dca0 ==== */

void __cdecl dec_jbit_pp(ulong opw,void *dec,long spacesel)

{
  dec_bit_pp(opw,dec,spacesel);
  *(undefined4 *)((int)dec + 0x80) = 9;
  *(undefined4 *)((int)dec + 0x88) = dec_extword;
  dec_uses_extword = 1;
  return;
}


/* ==== dec_bit_pp @ 0041dce0 ==== */

void __cdecl dec_bit_pp(ulong opw,void *dec,long spacesel)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = opw & 0x3f00 | 0xffc000;
  uVar2 = uVar1 >> 8;
  if (spacesel == 1) {
    uVar2 = CONCAT21(0xff,(char)(uVar1 >> 8)) & 0xffffffbf;
  }
  *(undefined4 *)((int)dec + 0x58) = 10;
  *(ulong *)((int)dec + 0x60) = opw & 0x1f;
  *(uint *)((int)dec + 0x78) = ((opw & 0x40) != 0) + 1;
  *(undefined4 *)((int)dec + 0x6c) = 9;
  *(uint *)((int)dec + 0x74) = uVar2;
  return;
}


/* ==== dec_c33_jsclr @ 0041dd30 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c33_jsclr(ulong opw,void *dec)

{
  dec_jbit_pp(opw,dec,0);
  *(undefined4 *)dec = 0x12;
  return;
}


/* ==== dec_c50_jset @ 0041dd50 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c50_jset(ulong opw,void *dec)

{
  dec_jbit_pp(opw,dec,0);
  *(undefined4 *)dec = 0x13;
  return;
}


/* ==== dec_c51_jclr @ 0041dd70 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c51_jclr(ulong opw,void *dec)

{
  dec_jbit_pp(opw,dec,0);
  *(undefined4 *)dec = 0x11;
  return;
}


/* ==== dec_h41dd90 @ 0041dd90 ==== */

void dec_h41dd90(ulong param_1,undefined4 *param_2)

{
  dec_jbit_pp(param_1,param_2,0);
  *param_2 = 0x2f;
  return;
}


/* ==== dec_h41ddb0 @ 0041ddb0 ==== */

void dec_h41ddb0(ulong param_1,undefined4 *param_2)

{
  dec_jbit_pp(param_1,param_2,0);
  *param_2 = 0x2d;
  return;
}


/* ==== dec_h41ddd0 @ 0041ddd0 ==== */

void dec_h41ddd0(ulong param_1,undefined4 *param_2)

{
  dec_jbit_pp(param_1,param_2,1);
  *param_2 = 0x13;
  return;
}


/* ==== dec_h41ddf0 @ 0041ddf0 ==== */

void dec_h41ddf0(ulong param_1,undefined4 *param_2)

{
  dec_jbit_pp(param_1,param_2,1);
  *param_2 = 0x11;
  return;
}


/* ==== dec_h41de10 @ 0041de10 ==== */

void dec_h41de10(ulong param_1,undefined4 *param_2)

{
  dec_jbit_pp(param_1,param_2,1);
  *param_2 = 0x2f;
  return;
}


/* ==== dec_h41de30 @ 0041de30 ==== */

void dec_h41de30(ulong param_1,undefined4 *param_2)

{
  dec_jbit_pp(param_1,param_2,1);
  *param_2 = 0x2d;
  return;
}


/* ==== dec_h41de50 @ 0041de50 ==== */

void dec_h41de50(ulong param_1,undefined4 *param_2)

{
  dec_jbit_pp(param_1,param_2,1);
  *param_2 = 0x15;
  return;
}


/* ==== dec_h41de70 @ 0041de70 ==== */

void dec_h41de70(ulong param_1,undefined4 *param_2)

{
  dec_jbit_pp(param_1,param_2,1);
  *param_2 = 0x12;
  return;
}


/* ==== dec_h41de90 @ 0041de90 ==== */

void dec_h41de90(ulong param_1,undefined4 *param_2)

{
  dec_jbit_pp(param_1,param_2,0);
  *param_2 = 0x30;
  return;
}


/* ==== dec_h41deb0 @ 0041deb0 ==== */

void dec_h41deb0(ulong param_1,undefined4 *param_2)

{
  dec_jbit_pp(param_1,param_2,0);
  *param_2 = 0x2e;
  return;
}


/* ==== dec_h41ded0 @ 0041ded0 ==== */

void dec_h41ded0(ulong param_1,undefined4 *param_2)

{
  dec_jbit_pp(param_1,param_2,1);
  *param_2 = 0x30;
  return;
}


/* ==== dec_h41def0 @ 0041def0 ==== */

void dec_h41def0(ulong param_1,undefined4 *param_2)

{
  dec_jbit_pp(param_1,param_2,1);
  *param_2 = 0x2e;
  return;
}


/* ==== dec_c34_btst @ 0041df10 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c34_btst(ulong opw,void *dec)

{
  dec_bit_pp(opw,dec,0);
  *(undefined4 *)dec = 6;
  return;
}


/* ==== dec_c35_bchg @ 0041df30 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c35_bchg(ulong opw,void *dec)

{
  dec_bit_pp(opw,dec,0);
  *(undefined4 *)dec = 2;
  return;
}


/* ==== dec_c52_bset @ 0041df50 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c52_bset(ulong opw,void *dec)

{
  dec_bit_pp(opw,dec,0);
  *(undefined4 *)dec = 5;
  return;
}


/* ==== dec_c53_bclr @ 0041df70 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c53_bclr(ulong opw,void *dec)

{
  dec_bit_pp(opw,dec,0);
  *(undefined4 *)dec = 3;
  return;
}


/* ==== dec_c38_btst @ 0041df90 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c38_btst(ulong opw,void *dec)

{
  dec_bit_ea(opw,dec);
  *(undefined4 *)dec = 6;
  return;
}


/* ==== dec_c39_bchg @ 0041dfb0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c39_bchg(ulong opw,void *dec)

{
  dec_bit_ea(opw,dec);
  *(undefined4 *)dec = 2;
  return;
}


/* ==== dec_c56_bset @ 0041dfd0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c56_bset(ulong opw,void *dec)

{
  dec_bit_ea(opw,dec);
  *(undefined4 *)dec = 5;
  return;
}


/* ==== dec_c57_bclr @ 0041dff0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c57_bclr(ulong opw,void *dec)

{
  dec_bit_ea(opw,dec);
  *(undefined4 *)dec = 3;
  return;
}


/* ==== dec_c42_btst @ 0041e010 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c42_btst(ulong opw,void *dec)

{
  dec_bit_aa(opw,dec);
  *(undefined4 *)dec = 6;
  return;
}


/* ==== dec_c43_bchg @ 0041e030 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c43_bchg(ulong opw,void *dec)

{
  dec_bit_aa(opw,dec);
  *(undefined4 *)dec = 2;
  return;
}


/* ==== dec_c60_bset @ 0041e050 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c60_bset(ulong opw,void *dec)

{
  dec_bit_aa(opw,dec);
  *(undefined4 *)dec = 5;
  return;
}


/* ==== dec_c61_bclr @ 0041e070 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c61_bclr(ulong opw,void *dec)

{
  dec_bit_aa(opw,dec);
  *(undefined4 *)dec = 3;
  return;
}


/* ==== dec_c65_pm @ 0041e090 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c65_pm(ulong opw,void *dec)

{
  uint uVar1;
  
  uVar1 = opw >> 8;
  dec_movep_ea(dec,((uVar1 & 0x100) != 0) + 1,((opw & 0x40) != 0) + 1,opw & 0x3f | 0xffc0,
               uVar1 & 0x80,uVar1 & 0x3f);
  return;
}


/* ==== dec_movep_ea @ 0041e0e0 ==== */

void __cdecl dec_movep_ea(void *dec,long a2,long a3,long a4,long swap,ulong ea6)

{
  void *pvVar1;
  long *local_4;
  
  pvVar1 = (void *)((int)dec + 0x58);
  local_4 = (long *)((int)dec + 0x6c);
  dec = pvVar1;
  if (swap != 0) {
    swap_ptrs(&dec,&local_4);
  }
  *(long *)((int)dec + 0xc) = a2;
  *(undefined4 *)dec = 9;
  *(long *)((int)dec + 8) = a4;
  local_4[3] = a3;
  dec_ea6(local_4,ea6);
  return;
}


/* ==== dec_h41e150 @ 0041e150 ==== */

void dec_h41e150(uint param_1,void *param_2)

{
  dec_movep_ea(param_2,((param_1 & 0x80) != 0) + 1,((param_1 & 0x40) != 0) + 1,
               param_1 & 0x3f | 0xff80,param_1 >> 8 & 0x80,param_1 >> 8 & 0x3f);
  return;
}


/* ==== dec_c66_pm @ 0041e1a0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c66_pm(ulong opw,void *dec)

{
  uint uVar1;
  
  uVar1 = opw >> 8;
  dec_movep_ea(dec,((uVar1 & 0x100) != 0) + 1,3,opw & 0x3f | 0xffc0,uVar1 & 0x80,uVar1 & 0x3f);
  return;
}


/* ==== dec_h41e1f0 @ 0041e1f0 ==== */

void dec_h41e1f0(uint param_1,void *param_2)

{
  dec_movep_ea(param_2,((param_1 & 0x40) != 0) + 1,3,param_1 & 0x3f | 0xff80,param_1 >> 8 & 0x40,
               param_1 >> 8 & 0x3f);
  return;
}


/* ==== dec_c67_pm @ 0041e230 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c67_pm(ulong opw,void *dec)

{
  uint uVar1;
  
  uVar1 = opw >> 8;
  dec_movep_reg(dec,((uVar1 & 0x100) != 0) + 1,opw & 0x3f | 0xffc0,uVar1 & 0x80,uVar1 & 0x3f);
  return;
}


/* ==== dec_movep_reg @ 0041e280 ==== */

void __cdecl dec_movep_reg(void *dec,long a2,long a3,long swap,long regsel)

{
  void *pvVar1;
  undefined4 *local_4;
  
  pvVar1 = (void *)((int)dec + 0x58);
  local_4 = (undefined4 *)((int)dec + 0x6c);
  dec = pvVar1;
  if (swap != 0) {
    swap_ptrs(&dec,&local_4);
  }
  *(long *)((int)dec + 0xc) = a2;
  *(undefined4 *)dec = 9;
  *(long *)((int)dec + 8) = a3;
  *local_4 = 0xc;
  local_4[1] = *(undefined4 *)(&DAT_004bfc80 + regsel * 4);
  return;
}


/* ==== dec_h41e2f0 @ 0041e2f0 ==== */

void dec_h41e2f0(uint param_1,int *param_2)

{
  if ((param_1 & 0x80) == 0) {
    param_2[0x2a] = param_1 & 0xf;
  }
  *param_2 = 0x2c - (uint)((param_1 & 0x40) != 0);
  param_2[0x20] = 0xc;
  param_2[0x21] = *(int *)(&DAT_004bfc80 + (param_1 >> 8 & 7 | 0x10) * 4);
  return;
}


/* ==== dec_h41e340 @ 0041e340 ==== */

void dec_h41e340(uint param_1,int *param_2)

{
  if ((param_1 & 0x80) == 0) {
    param_2[0x2a] = param_1 & 0xf;
  }
  *param_2 = 0x2c - (uint)((param_1 & 0x40) != 0);
  param_2[0x20] = 9;
  param_2[0x22] = dec_extword;
  dec_uses_extword = 1;
  return;
}


/* ==== dec_h41e390 @ 0041e390 ==== */

void dec_h41e390(uint param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = param_1 >> 1 & 0x1e0;
  uVar2 = uVar1 | param_1 & 0x1f;
  if ((param_1 & 0x800) == 0) {
    param_2[0x2a] = param_1 >> 0xc & 0xf;
  }
  *param_2 = 0x2c - (uint)((param_1 & 0x400) != 0);
  param_2[0x20] = 9;
  if ((char)(uVar1 >> 8) != '\0') {
    uVar2 = uVar2 | 0xffffff00;
  }
  param_2[0x22] = uVar2;
  return;
}


/* ==== dec_h41e3f0 @ 0041e3f0 ==== */

void dec_h41e3f0(uint param_1,void *param_2)

{
  dec_movep_reg(param_2,((param_1 & 0x20) != 0) + 1,(param_1 & 0x40 | 0x1ff00) >> 1 | param_1 & 0x1f
                ,param_1 >> 8 & 0x80,param_1 >> 8 & 0x3f);
  return;
}


/* ==== dec_c69_enddo @ 0041e440 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c69_enddo(ulong opw,void *dec)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = opw & 0x3f;
  uVar1 = opw >> 8;
  opw = (int)dec + 0x58;
  dec = (void *)((int)dec + 0x6c);
  if ((uVar1 & 0x80) == 0) {
    swap_ptrs((void **)&opw,&dec);
  }
  *(undefined4 *)(opw + 0xc) = 3;
  dec_ea6((long *)opw,uVar1 & 0x3f);
  *(undefined4 *)dec = 0xc;
  *(undefined4 *)((int)dec + 4) = *(undefined4 *)(&DAT_004bfc80 + uVar2 * 4);
  return;
}


/* ==== dec_c70_doforever @ 0041e4c0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c70_doforever(ulong opw,void *dec)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = opw & 0x3f;
  uVar1 = opw >> 8;
  opw = (int)dec + 0x58;
  dec = (void *)((int)dec + 0x6c);
  if ((uVar1 & 0x80) == 0) {
    swap_ptrs((void **)&opw,&dec);
  }
  *(undefined4 *)(opw + 0xc) = 3;
  *(undefined4 *)opw = 9;
  *(uint *)(opw + 8) = uVar1 & 0x3f;
  *(undefined4 *)dec = 0xc;
  *(undefined4 *)((int)dec + 4) = *(undefined4 *)(&DAT_004bfc80 + uVar2 * 4);
  return;
}


/* ==== dec_c75_rep @ 0041e540 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c75_rep(ulong opw,void *dec)

{
  *(undefined4 *)((int)dec + 0x58) = 10;
  *(ulong *)((int)dec + 0x60) = opw >> 8 & 0xff | (opw & 0xf) << 8;
  *(undefined4 *)dec = 0x23;
  return;
}


/* ==== dec_c71_rep @ 0041e570 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c71_rep(ulong opw,void *dec)

{
  *(undefined4 *)((int)dec + 0x58) = 0xc;
  *(undefined4 *)((int)dec + 0x5c) = *(undefined4 *)(&DAT_004bfc80 + (opw >> 8 & 0x3f) * 4);
  *(undefined4 *)dec = 0x23;
  return;
}


/* ==== dec_c73_rep @ 0041e5a0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c73_rep(ulong opw,void *dec)

{
  *(uint *)((int)dec + 100) = ((opw & 0x40) != 0) + 1;
  dec_ea6((long *)((int)dec + 0x58),opw >> 8 & 0x3f);
  *(undefined4 *)dec = 0x23;
  return;
}


/* ==== dec_c77_rep @ 0041e5e0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c77_rep(ulong opw,void *dec)

{
  *(undefined4 *)((int)dec + 0x58) = 9;
  *(uint *)((int)dec + 100) = ((opw & 0x40) != 0) + 1;
  *(ulong *)((int)dec + 0x60) = opw >> 8 & 0x3f;
  *(undefined4 *)dec = 0x23;
  return;
}


/* ==== dec_do_imm @ 0041e610 ==== */

void __cdecl dec_do_imm(ulong opw,void *dec)

{
  *(undefined4 *)((int)dec + 0x58) = 10;
  *(ulong *)((int)dec + 0x60) = opw >> 8 & 0xff | (opw & 0xf) << 8;
  *(undefined4 *)((int)dec + 0x6c) = 9;
  *(undefined4 *)((int)dec + 0x74) = dec_extword;
  dec_uses_extword = 1;
  *(undefined4 *)dec = 8;
  return;
}


/* ==== dec_do_reg @ 0041e650 ==== */

void __cdecl dec_do_reg(ulong opw,void *dec)

{
  *(undefined4 *)((int)dec + 0x58) = 0xc;
  *(undefined4 *)((int)dec + 0x5c) = *(undefined4 *)(&DAT_004bfc80 + (opw >> 8 & 0x3f) * 4);
  *(undefined4 *)((int)dec + 0x6c) = 9;
  *(undefined4 *)((int)dec + 0x74) = dec_extword;
  dec_uses_extword = 1;
  *(undefined4 *)dec = 8;
  return;
}


/* ==== dec_do_ea @ 0041e690 ==== */

void __cdecl dec_do_ea(ulong opw,void *dec)

{
  *(uint *)((int)dec + 100) = ((opw & 0x40) != 0) + 1;
  dec_ea6((long *)((int)dec + 0x58),opw >> 8 & 0x3f);
  *(undefined4 *)((int)dec + 0x6c) = 9;
  *(undefined4 *)((int)dec + 0x74) = dec_extword;
  dec_uses_extword = 1;
  *(undefined4 *)dec = 8;
  return;
}


/* ==== dec_do_aa @ 0041e6e0 ==== */

void __cdecl dec_do_aa(ulong opw,void *dec)

{
  *(undefined4 *)((int)dec + 0x58) = 9;
  *(uint *)((int)dec + 100) = ((opw & 0x40) != 0) + 1;
  *(ulong *)((int)dec + 0x60) = opw >> 8 & 0x3f;
  *(undefined4 *)((int)dec + 0x6c) = 9;
  *(undefined4 *)((int)dec + 0x74) = dec_extword;
  dec_uses_extword = 1;
  *(undefined4 *)dec = 8;
  return;
}


/* ==== dec_c81_pm @ 0041e730 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c81_pm(ulong opw,void *dec)

{
  *(undefined4 *)((int)dec + 0x58) = 10;
  *(ulong *)((int)dec + 0x60) = opw >> 8 & 0xff;
  *(undefined4 *)((int)dec + 0x6c) = 0xc;
  *(undefined4 *)((int)dec + 0x70) = *(undefined4 *)(&DAT_004bfc80 + (opw & 0x3f) * 4);
  return;
}


/* ==== dec_c79_enddo @ 0041e760 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c79_enddo(ulong opw,void *dec)

{
  ulong uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = opw & 0x3f;
  uVar2 = opw >> 8;
  uVar1 = (int)dec + 0x58;
  uVar4 = opw & 0x40;
  dec = (void *)((int)dec + 0x6c);
  opw = uVar1;
  if ((uVar2 & 0x80) == 0) {
    swap_ptrs((void **)&opw,&dec);
  }
  *(uint *)(opw + 0xc) = (uVar4 != 0) + 1;
  dec_ea6((long *)opw,uVar2 & 0x3f);
  *(undefined4 *)dec = 0xc;
  *(undefined4 *)((int)dec + 4) = *(undefined4 *)(&DAT_004bfc80 + uVar3 * 4);
  return;
}


/* ==== dec_c83_doforever @ 0041e7f0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c83_doforever(ulong opw,void *dec)

{
  ulong uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = opw & 0x3f;
  uVar2 = opw >> 8;
  uVar1 = (int)dec + 0x58;
  uVar4 = opw & 0x40;
  dec = (void *)((int)dec + 0x6c);
  opw = uVar1;
  if ((uVar2 & 0x80) == 0) {
    swap_ptrs((void **)&opw,&dec);
  }
  *(uint *)(opw + 0xc) = (uVar4 != 0) + 1;
  *(undefined4 *)opw = 9;
  *(uint *)(opw + 8) = uVar2 & 0x3f;
  *(undefined4 *)dec = 0xc;
  *(undefined4 *)((int)dec + 4) = *(undefined4 *)(&DAT_004bfc80 + uVar3 * 4);
  return;
}


/* ==== dec_c85_enddo @ 0041e880 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c85_enddo(ulong opw,void *dec)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = opw & 0x3f;
  uVar1 = opw >> 8;
  opw = (int)dec + 0x58;
  dec = (void *)((int)dec + 0x6c);
  if ((uVar1 & 0x80) == 0) {
    swap_ptrs((void **)&opw,&dec);
  }
  *(undefined4 *)opw = 0xc;
  *(undefined4 *)(opw + 4) = *(undefined4 *)(&DAT_004bfc80 + (uVar1 & 0x3f) * 4);
  *(undefined4 *)dec = 0xc;
  *(undefined4 *)((int)dec + 4) = *(undefined4 *)(&DAT_004bfc80 + uVar2 * 4);
  return;
}


/* ==== dec_c87_lua @ 0041e900 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c87_lua(ulong opw,void *dec)

{
  dec_ea6((long *)((int)dec + 0x58),opw >> 8 & 0x3f);
  *(undefined4 *)((int)dec + 0x68) = 1;
  *(undefined4 *)((int)dec + 0x6c) = 0xc;
  *(undefined4 *)((int)dec + 0x70) = *(undefined4 *)(&DAT_004bfc80 + (opw & 0x3f) * 4);
  *(undefined4 *)dec = 0x17;
  return;
}


/* ==== dec_tcc @ 0041e950 ==== */

void __cdecl dec_tcc(ulong opw,void *dec)

{
  int iVar1;
  
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 0xc;
  *(undefined4 *)((int)dec + 0xc) = *(undefined4 *)(&DAT_004bffc0 + (opw >> 4 & 7) * 4);
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  iVar1 = *(int *)(&DAT_004c0000 + (opw >> 3 & 1) * 4);
  *(int *)((int)dec + 0x20) = iVar1;
  if (*(int *)((int)dec + 0xc) == iVar1) {
    *(undefined4 *)((int)dec + 0xc) = 5;
  }
  if ((opw & 0x10000) != 0) {
    *(undefined4 *)((int)dec + 0x58) = 0xc;
    *(undefined4 *)((int)dec + 0x5c) = *(undefined4 *)(&DAT_004bfc80 + (opw >> 8 & 7 | 0x10) * 4);
    *(undefined4 *)((int)dec + 0x6c) = 0xc;
    *(undefined4 *)((int)dec + 0x70) = *(undefined4 *)(&DAT_004bfc80 + (opw & 7 | 0x10) * 4);
  }
  *(undefined4 *)dec = 0x28;
  *(ulong *)((int)dec + 0xa8) = opw >> 0xc & 0xf;
  return;
}


/* ==== dec_div @ 0041ea00 ==== */

void __cdecl dec_div(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 0xc;
  *(undefined4 *)((int)dec + 0xc) = *(undefined4 *)(&DAT_004c0008 + (opw >> 4 & 3) * 4);
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c0000 + (opw >> 3 & 1) * 4);
  *(undefined4 *)dec = 0x3f;
  return;
}


/* ==== dec_incdec @ 0041ea50 ==== */

void __cdecl dec_incdec(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 0xc;
  *(undefined4 *)((int)dec + 0xc) = *(undefined4 *)(&DAT_004c0000 + (opw & 1) * 4);
  *(uint *)dec = (-(uint)((opw & 2) != 0) & 0xfffffffa) + 0x44;
  return;
}


/* ==== dec_shift_imm @ 0041ea90 ==== */

void __cdecl dec_shift_imm(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 10;
  *(ulong *)((int)dec + 0x10) = opw >> 1 & 0x3f;
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c0000 + (opw >> 7 & 1) * 4);
  *(undefined4 *)((int)dec + 0x30) = 0xc;
  *(undefined4 *)((int)dec + 0x34) = *(undefined4 *)(&DAT_004c0000 + (opw & 1) * 4);
  *(uint *)dec = 0x38 - (uint)((opw & 0x100) != 0);
  return;
}


/* ==== dec_shift_reg @ 0041eaf0 ==== */

void __cdecl dec_shift_reg(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 0xc;
  *(undefined4 *)((int)dec + 0xc) = *(undefined4 *)(&DAT_004c0028 + (opw >> 1 & 7) * 4);
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c0000 + (opw >> 4 & 1) * 4);
  *(undefined4 *)((int)dec + 0x30) = 0xc;
  *(undefined4 *)((int)dec + 0x34) = *(undefined4 *)(&DAT_004c0000 + (opw & 1) * 4);
  *(uint *)dec = ((opw & 0x20) != 0) + 0x37;
  return;
}


/* ==== dec_lsl_lsr_imm @ 0041eb60 ==== */

void __cdecl dec_lsl_lsr_imm(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 10;
  *(ulong *)((int)dec + 0x10) = opw >> 1 & 0x1f;
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c0000 + (opw & 1) * 4);
  *(ulong *)dec = (opw & 0x40 | 0x1180) >> 6;
  return;
}


/* ==== dec_lsl_lsr_reg @ 0041ebb0 ==== */

void __cdecl dec_lsl_lsr_reg(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 0xc;
  *(undefined4 *)((int)dec + 0xc) = *(undefined4 *)(&DAT_004c0028 + (opw >> 1 & 7) * 4);
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c0000 + (opw & 1) * 4);
  *(ulong *)dec = (opw & 0x20 | 0x8c0) >> 5;
  return;
}


/* ==== dec_extract_reg @ 0041ec00 ==== */

void __cdecl dec_extract_reg(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 0xc;
  *(undefined4 *)((int)dec + 0xc) = *(undefined4 *)(&DAT_004c0028 + (opw >> 1 & 7) * 4);
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c0000 + (opw >> 4 & 1) * 4);
  *(undefined4 *)((int)dec + 0x30) = 0xc;
  *(undefined4 *)((int)dec + 0x34) = *(undefined4 *)(&DAT_004c0000 + (opw & 1) * 4);
  *(uint *)dec = (uint)(ushort)(CONCAT11(0x21,(byte)opw & 0x80) >> 7);
  return;
}


/* ==== dec_insert_reg @ 0041ec70 ==== */

void __cdecl dec_insert_reg(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 0xc;
  *(undefined4 *)((int)dec + 0xc) = *(undefined4 *)(&DAT_004c0028 + (opw >> 1 & 7) * 4);
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c0048 + (opw >> 4 & 7) * 4);
  *(undefined4 *)((int)dec + 0x30) = 0xc;
  *(undefined4 *)((int)dec + 0x34) = *(undefined4 *)(&DAT_004c0000 + (opw & 1) * 4);
  *(undefined4 *)dec = 0x45;
  return;
}


/* ==== dec_normf_merge @ 0041ecd0 ==== */

void __cdecl dec_normf_merge(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 0xc;
  *(undefined4 *)((int)dec + 0xc) = *(undefined4 *)(&DAT_004c0028 + (opw >> 1 & 7) * 4);
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c0000 + (opw & 1) * 4);
  *(uint *)dec = (-(uint)((opw & 0x80) != 0) & 0xfffffffa) + 0x53;
  return;
}


/* ==== dec_clb @ 0041ed20 ==== */

void __cdecl dec_clb(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 0xc;
  *(undefined4 *)((int)dec + 0xc) = *(undefined4 *)(&DAT_004c0000 + (opw >> 1 & 1) * 4);
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c0000 + (opw & 1) * 4);
  *(undefined4 *)dec = 0x39;
  return;
}


/* ==== dec_alu_imm_short @ 0041ed70 ==== */

void __cdecl dec_alu_imm_short(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 10;
  *(ulong *)((int)dec + 0x10) = opw >> 8 & 0x3f;
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c0000 + (opw >> 3 & 1) * 4);
  *(undefined4 *)dec = *(undefined4 *)(&DAT_004c0118 + (opw & 7) * 4);
  return;
}


/* ==== dec_alu_imm_long @ 0041edc0 ==== */

void __cdecl dec_alu_imm_long(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 10;
  *(undefined4 *)((int)dec + 0x10) = dec_extword;
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c0000 + (opw >> 3 & 1) * 4);
  *(undefined4 *)dec = *(undefined4 *)(&DAT_004c0118 + (opw & 7) * 4);
  dec_uses_extword = 1;
  return;
}


/* ==== dec_cmpu @ 0041ee20 ==== */

void __cdecl dec_cmpu(ulong opw,void *dec)

{
  int iVar1;
  
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 0xc;
  *(undefined4 *)((int)dec + 0xc) = *(undefined4 *)(&DAT_004c0068 + (opw >> 1 & 7) * 4);
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  iVar1 = *(int *)(&DAT_004c0000 + (opw & 1) * 4);
  *(int *)((int)dec + 0x20) = iVar1;
  if (*(int *)((int)dec + 0xc) == iVar1) {
    *(undefined4 *)((int)dec + 0xc) = 5;
  }
  *(undefined4 *)dec = 0x3d;
  return;
}


/* ==== dec_mpy_reg @ 0041ee80 ==== */

void __cdecl dec_mpy_reg(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 0xc;
  *(undefined4 *)((int)dec + 0xc) = *(undefined4 *)(&DAT_004bffe0 + (opw >> 4 & 3) * 4);
  *(undefined4 *)((int)dec + 0x1c) = 10;
  *(ulong *)((int)dec + 0x24) = opw >> 8 & 0x1f;
  *(undefined4 *)((int)dec + 0x30) = 0xc;
  *(undefined4 *)((int)dec + 0x34) = *(undefined4 *)(&DAT_004c0000 + (opw >> 3 & 1) * 4);
  *(undefined4 *)dec = *(undefined4 *)(&DAT_004c0148 + (opw & 3) * 4);
  *(uint *)((int)dec + 0xb0) = (-(uint)((opw & 4) != 0) & 0xfffffffe) + 1;
  return;
}


/* ==== dec_mac_su @ 0041ef00 ==== */

void __cdecl dec_mac_su(ulong opw,void *dec)

{
  int iVar1;
  
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 0xc;
  *(undefined4 *)((int)dec + 0xc) = *(undefined4 *)(&DAT_004c0098 + (opw & 0xf) * 4);
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c00d8 + (opw & 0xf) * 4);
  *(undefined4 *)((int)dec + 0x30) = 0xc;
  *(undefined4 *)((int)dec + 0x34) = *(undefined4 *)(&DAT_004c0000 + (opw >> 5 & 1) * 4);
  if ((opw & 0x200) == 0) {
    iVar1 = 0x40;
  }
  else {
    iVar1 = (-(uint)((opw & 0x100) != 0) & 6) + 0x48;
  }
  *(int *)dec = iVar1;
  *(uint *)((int)dec + 0xb0) = (-(uint)((opw >> 4 & 1) != 0) & 0xfffffffe) + 1;
  *(uint *)((int)dec + 0xac) =
       *(uint *)((int)dec + 0xac) |
       *(uint *)(&DAT_004c0088 + (((opw & 0x100 | opw >> 1 & 0x100) >> 1 | opw & 0x40) >> 6) * 4);
  return;
}


/* ==== dec_mpyi @ 0041efc0 ==== */

void __cdecl dec_mpyi(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 10;
  *(undefined4 *)((int)dec + 0x10) = dec_extword;
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004bfff0 + (opw >> 4 & 3) * 4);
  *(undefined4 *)((int)dec + 0x30) = 0xc;
  *(undefined4 *)((int)dec + 0x34) = *(undefined4 *)(&DAT_004c0000 + (opw >> 3 & 1) * 4);
  *(undefined4 *)dec = *(undefined4 *)(&DAT_004c0138 + (opw & 3) * 4);
  *(uint *)((int)dec + 0xb0) = (-(uint)((opw & 4) != 0) & 0xfffffffe) + 1;
  dec_uses_extword = 1;
  return;
}


/* ==== dec_extract_imm @ 0041f040 ==== */

void __cdecl dec_extract_imm(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 10;
  *(undefined4 *)((int)dec + 0x10) = dec_extword;
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c0000 + (opw >> 4 & 1) * 4);
  *(undefined4 *)((int)dec + 0x30) = 0xc;
  *(undefined4 *)((int)dec + 0x34) = *(undefined4 *)(&DAT_004c0000 + (opw & 1) * 4);
  *(uint *)dec = (uint)(ushort)(CONCAT11(0x21,~(byte)opw & 0x80) >> 7);
  dec_uses_extword = 1;
  return;
}


/* ==== dec_insert_imm @ 0041f0b0 ==== */

void __cdecl dec_insert_imm(ulong opw,void *dec)

{
  dec_flag_nomove(dec);
  *(undefined4 *)((int)dec + 8) = 10;
  *(undefined4 *)((int)dec + 0x10) = dec_extword;
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c0048 + (opw >> 4 & 7) * 4);
  *(undefined4 *)((int)dec + 0x30) = 0xc;
  *(undefined4 *)((int)dec + 0x34) = *(undefined4 *)(&DAT_004c0000 + (opw & 1) * 4);
  *(undefined4 *)dec = 0x45;
  dec_uses_extword = 1;
  return;
}


/* ==== dec_c91_norm @ 0041f110 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c91_norm(ulong opw,void *dec)

{
  *(undefined4 *)((int)dec + 8) = 0xc;
  *(undefined4 *)((int)dec + 0xc) =
       *(undefined4 *)(&DAT_004bfc80 + (uint)((byte)(opw >> 8) & 7 | 0x10) * 4);
  *(undefined4 *)((int)dec + 0x1c) = 0xc;
  *(undefined4 *)((int)dec + 0x20) = *(undefined4 *)(&DAT_004c0000 + (opw >> 3 & 1) * 4);
  dec_flag_nomove(dec);
  *(undefined4 *)dec = 0x1a;
  return;
}


/* ==== dec_c95_ori @ 0041f160 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c95_ori(ulong opw,void *dec)

{
  *(undefined4 *)((int)dec + 0x58) = 10;
  *(ulong *)((int)dec + 0x60) = opw >> 8 & 0xff;
  *(undefined4 *)((int)dec + 0x6c) = 0xc;
  *(undefined4 *)((int)dec + 0x70) = *(undefined4 *)(&DAT_004c0018 + (opw & 3) * 4);
  *(undefined4 *)dec = 0x1b;
  return;
}


/* ==== dec_c96_andi @ 0041f1a0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c96_andi(ulong opw,void *dec)

{
  *(undefined4 *)((int)dec + 0x58) = 10;
  *(ulong *)((int)dec + 0x60) = opw >> 8 & 0xff;
  *(undefined4 *)((int)dec + 0x6c) = 0xc;
  *(undefined4 *)((int)dec + 0x70) = *(undefined4 *)(&DAT_004c0018 + (opw & 3) * 4);
  *(undefined4 *)dec = 1;
  return;
}


/* ==== dec_c97_enddo @ 0041f1e0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c97_enddo(ulong opw,void *dec)

{
  *(undefined4 *)dec = 0xc;
  return;
}


/* ==== dec_c98_stop @ 0041f1f0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c98_stop(ulong opw,void *dec)

{
  *(undefined4 *)dec = 0x27;
  return;
}


/* ==== dec_c99_wait @ 0041f200 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c99_wait(ulong opw,void *dec)

{
  *(undefined4 *)dec = 0x29;
  return;
}


/* ==== dec_c100_reset @ 0041f210 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c100_reset(ulong opw,void *dec)

{
  *(undefined4 *)dec = 0x24;
  return;
}


/* ==== dec_c104_trap @ 0041f220 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c104_trap(ulong opw,void *dec)

{
  *(undefined4 *)dec = 0x2a;
  return;
}


/* ==== dec_c107_nop @ 0041f230 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c107_nop(ulong opw,void *dec)

{
  *(undefined4 *)dec = 0x19;
  return;
}


/* ==== dec_c106_rti @ 0041f240 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c106_rti(ulong opw,void *dec)

{
  *(undefined4 *)dec = 0x25;
  return;
}


/* ==== dec_c101_rts @ 0041f250 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c101_rts(ulong opw,void *dec)

{
  *(undefined4 *)dec = 0x26;
  return;
}


/* ==== dec_c63_pm @ 0041f260 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c63_pm(ulong opw,void *dec)

{
  uint uVar1;
  
  uVar1 = (opw >> 8 & 0x100 | 0x40) >> 6;
  dec_alu(opw,dec);
  *(undefined4 *)((int)dec + 0x58) = 0xc;
  *(uint *)((int)dec + 0x5c) = uVar1;
  *(undefined4 *)((int)dec + 0x78) = 1;
  dec_ea6((long *)((int)dec + 0x6c),opw >> 8 & 0x3f);
  *(undefined4 *)((int)dec + 0x80) = 0xc;
  *(undefined4 *)((int)dec + 0x84) = 0x31;
  *(undefined4 *)((int)dec + 0x94) = 0xc;
  *(uint *)((int)dec + 0x98) = uVar1;
  return;
}


/* ==== dec_c62_pm @ 0041f2e0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c62_pm(ulong opw,void *dec)

{
  uint uVar1;
  
  uVar1 = (opw >> 8 & 0x100 | 0x40) >> 6;
  dec_alu(opw,dec);
  *(undefined4 *)((int)dec + 0x58) = 0xc;
  *(undefined4 *)((int)dec + 0x5c) = 0x34;
  *(undefined4 *)((int)dec + 0x6c) = 0xc;
  *(uint *)((int)dec + 0x70) = uVar1;
  *(undefined4 *)((int)dec + 0x80) = 0xc;
  *(uint *)((int)dec + 0x84) = uVar1;
  *(undefined4 *)((int)dec + 0xa0) = 2;
  dec_ea6((long *)((int)dec + 0x94),opw >> 8 & 0x3f);
  return;
}


/* ==== dec_c28_btst @ 0041f350 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c28_btst(ulong opw,void *dec)

{
  dec_bit_reg(opw,dec);
  *(undefined4 *)dec = 6;
  return;
}


/* ==== dec_c29_bchg @ 0041f370 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c29_bchg(ulong opw,void *dec)

{
  dec_bit_reg(opw,dec);
  *(undefined4 *)dec = 2;
  return;
}


/* ==== dec_c46_bset @ 0041f390 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c46_bset(ulong opw,void *dec)

{
  dec_bit_reg(opw,dec);
  *(undefined4 *)dec = 5;
  return;
}


/* ==== dec_c47_bclr @ 0041f3b0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c47_bclr(ulong opw,void *dec)

{
  dec_bit_reg(opw,dec);
  *(undefined4 *)dec = 3;
  return;
}


/* ==== dec_c93_debug @ 0041f3d0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c93_debug(ulong opw,void *dec)

{
  if ((opw & 0x100) != 0) {
    *(ulong *)((int)dec + 0xa8) = opw & 0xf;
  }
  *(undefined4 *)dec = 7;
  return;
}


/* ==== dec_c105_illegal @ 0041f3f0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c105_illegal(ulong opw,void *dec)

{
  *(undefined4 *)dec = 0xf;
  return;
}


/* ==== dec_h41f400 @ 0041f400 ==== */

void dec_h41f400(ulong param_1,undefined4 *param_2)

{
  dec_do_ea(param_1,param_2);
  *param_2 = 10;
  return;
}


/* ==== dec_h41f420 @ 0041f420 ==== */

void dec_h41f420(ulong param_1,undefined4 *param_2)

{
  dec_do_imm(param_1,param_2);
  *param_2 = 10;
  return;
}


/* ==== dec_h41f440 @ 0041f440 ==== */

void dec_h41f440(ulong param_1,undefined4 *param_2)

{
  dec_do_aa(param_1,param_2);
  *param_2 = 10;
  return;
}


/* ==== dec_h41f460 @ 0041f460 ==== */

void dec_h41f460(ulong param_1,undefined4 *param_2)

{
  dec_do_reg(param_1,param_2);
  *param_2 = 10;
  return;
}


/* ==== dec_h41f480 @ 0041f480 ==== */

void dec_h41f480(uint param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = (param_1 >> 3 & 0x700 | param_1 & 0xf0) >> 4;
  if ((param_1 >> 3 & 0x400) != 0) {
    uVar2 = uVar2 | 0xffffffc0;
  }
  param_2[0x16] = 0xd;
  uVar1 = *(undefined4 *)(&DAT_004bfc80 + (param_1 >> 8 & 7 | 0x10) * 4);
  param_2[0x18] = uVar2;
  param_2[0x17] = uVar1;
  param_2[0x1b] = 0xc;
  param_2[0x1c] = *(undefined4 *)(&DAT_004bfc80 + (param_1 & 0xf | 0x10) * 4);
  *param_2 = 0x17;
  return;
}


/* ==== dec_h41f4f0 @ 0041f4f0 ==== */

void dec_h41f4f0(uint param_1,undefined4 *param_2)

{
  param_2[0x16] = 0xc;
  param_2[0x17] = *(undefined4 *)(&DAT_004bfc80 + ((param_1 & 0x700 | 0x1000) >> 8) * 4);
  param_2[0x1b] = 0xc;
  param_2[0x1c] = *(undefined4 *)(&DAT_004bfc80 + (param_1 & 0x3f) * 4);
  *param_2 = 0x16;
  return;
}


/* ==== dec_h41f540 @ 0041f540 ==== */

void dec_h41f540(uint param_1,undefined4 *param_2)

{
  param_2[0x16] = 10;
  param_2[0x18] = dec_extword;
  dec_uses_extword = 1;
  param_2[0x1b] = 0xc;
  param_2[0x1c] = *(undefined4 *)(&DAT_004bfc80 + (param_1 & 0x3f) * 4);
  *param_2 = 0x16;
  return;
}


/* ==== dec_h41f580 @ 0041f580 ==== */

void dec_h41f580(uint param_1,undefined4 *param_2)

{
  param_1 = param_1 & 3;
  if (param_1 == 1) {
    *param_2 = 0x1d;
  }
  else {
    if (param_1 == 2) {
      *param_2 = 0x1e;
      param_2[0x2b] = param_2[0x2b] | 0x100;
      return;
    }
    if (param_1 == 3) {
      *param_2 = 0x1c;
      param_2[0x2b] = param_2[0x2b] | 0x100;
      return;
    }
  }
  param_2[0x2b] = param_2[0x2b] | 0x100;
  return;
}


/* ==== dec_h41f5e0 @ 0041f5e0 ==== */

void dec_h41f5e0(uint param_1,int *param_2)

{
  *param_2 = (~param_1 & 1 | 0x10) << 1;
  param_2[0x2b] = param_2[0x2b] | 0x100;
  param_2[0x16] = 9;
  param_2[0x18] = dec_extword;
  dec_uses_extword = 1;
  return;
}


/* ==== dec_h41f620 @ 0041f620 ==== */

void dec_h41f620(uint param_1,int *param_2)

{
  param_2[0x2a] = param_1 & 0xf;
  *param_2 = (-(uint)((param_1 & 0x200) != 0) & 0xffffffda) + 0x2a;
  return;
}


/* ==== dec_h41f650 @ 0041f650 ==== */

void dec_h41f650(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar5 = (uint)param_1 >> 8;
  uVar3 = ((uint)param_1 >> 4 & 0x1f80 | (uint)param_1 & 0x40) >> 6;
  puVar1 = (undefined4 *)((int)param_2 + 0x58);
  uVar6 = (uint)param_1 & 0xf;
  uVar2 = (uint)param_1 & 0x10;
  uVar4 = (uint)param_1 & 0x20;
  param_2 = (undefined4 *)((int)param_2 + 0x6c);
  if (((uint)param_1 >> 4 & 0x1000) != 0) {
    uVar3 = uVar3 | 0xffffffc0;
  }
  param_1 = puVar1;
  if (uVar2 == 0) {
    swap_ptrs(&param_1,&param_2);
  }
  *param_1 = 0xd;
  param_1[3] = (uVar4 != 0) + 1;
  param_1[1] = *(undefined4 *)(&DAT_004bfc80 + (uVar5 & 7 | 0x10) * 4);
  param_1[2] = uVar3;
  *param_2 = 0xc;
  param_2[1] = *(undefined4 *)(&DAT_004bfc80 + uVar6 * 4);
  return;
}


/* ==== dec_h41f700 @ 0041f700 ==== */

void dec_h41f700(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = (uint)param_1 >> 8;
  puVar1 = (undefined4 *)((int)param_2 + 0x58);
  uVar4 = (uint)param_1 & 0x3f;
  param_2 = (undefined4 *)((int)param_2 + 0x6c);
  uVar2 = (uint)param_1 & 0x40;
  param_1 = puVar1;
  if (uVar2 == 0) {
    swap_ptrs(&param_1,&param_2);
  }
  *param_1 = 0xd;
  param_1[3] = ((uVar3 & 0x100) != 0) + 1;
  param_1[1] = *(undefined4 *)(&DAT_004bfc80 + (uVar3 & 7 | 0x10) * 4);
  param_1[2] = dec_extword;
  dec_uses_extword = 1;
  *param_2 = 0xc;
  param_2[1] = *(undefined4 *)(&DAT_004bfc80 + uVar4 * 4);
  return;
}


/* ==== dec_h41f7b0 @ 0041f7b0 ==== */

void dec_h41f7b0(uint param_1,int *param_2)

{
  *param_2 = (-(uint)((param_1 & 0x10000) != 0) & 0xfffffffe) + 0x21;
  param_2[0x2b] = param_2[0x2b] | 0x100;
  dec_ea6(param_2 + 0x16,param_1 >> 8 & 0x3f);
  return;
}


/* ==== dec_h41f7f0 @ 0041f7f0 ==== */

void dec_h41f7f0(uint param_1,undefined4 *param_2)

{
  param_2[0x16] = 0xc;
  param_2[0x17] = *(undefined4 *)(&DAT_004bfc80 + ((param_1 & 0x700 | 0x1000) >> 8) * 4);
  param_2[0x1b] = 0xc;
  param_2[0x1c] = *(undefined4 *)(&DAT_004bfc80 + (param_1 & 7 | 0x10) * 4);
  *param_2 = 0x28;
  param_2[0x2a] = param_1 >> 0xc & 0xf;
  return;
}


/* ==== dec_alu_cc @ 0041f850 ==== */

void __cdecl dec_alu_cc(ulong opw,void *dec)

{
  dec_alu(opw,dec);
  *(ulong *)((int)dec + 0xa8) = opw >> 8 & 0xf;
  *(uint *)((int)dec + 4) = ((opw & 0x1000) != 0) + 0xd;
  return;
}


/* ==== dec_h41f890 @ 0041f890 ==== */

void dec_h41f890(ulong param_1,undefined4 *param_2)

{
  dec_bit_pp(param_1,param_2,1);
  *param_2 = 6;
  return;
}


/* ==== dec_h41f8b0 @ 0041f8b0 ==== */

void dec_h41f8b0(ulong param_1,undefined4 *param_2)

{
  dec_bit_pp(param_1,param_2,1);
  *param_2 = 2;
  return;
}


/* ==== dec_h41f8d0 @ 0041f8d0 ==== */

void dec_h41f8d0(ulong param_1,undefined4 *param_2)

{
  dec_bit_pp(param_1,param_2,1);
  *param_2 = 5;
  return;
}


/* ==== dec_h41f8f0 @ 0041f8f0 ==== */

void dec_h41f8f0(ulong param_1,undefined4 *param_2)

{
  dec_bit_pp(param_1,param_2,1);
  *param_2 = 3;
  return;
}


/* ==== dec_h41f910 @ 0041f910 ==== */

void dec_h41f910(uint param_1,uint *param_2)

{
  param_2[0x16] = 9;
  param_2[0x18] = dec_extword;
  dec_uses_extword = 1;
  *param_2 = (~param_1 & 1) << 1 | 9;
  return;
}


/* ==== dec_h41f940 @ 0041f940 ==== */

void dec_h41f940(uint param_1,undefined4 *param_2)

{
  uint uVar1;
  uint ea6;
  
  param_2[0x1e] = 1;
  uVar1 = (param_1 >> 8 & 0xffff) >> 8 & 1;
  ea6 = param_1 >> 8 & 0x3f;
  dec_ea6(param_2 + 0x1b,ea6);
  param_2[0x16] = 0xc;
  param_2[0x17] = *(undefined4 *)(&DAT_004c0000 + uVar1 * 4);
  param_2[0x28] = 2;
  dec_ea6(param_2 + 0x25,ea6);
  param_2[0x20] = 0xc;
  param_2[0x22] = (uint)((param_1 & 0x10) != 0);
  param_2[0x21] = *(undefined4 *)(&DAT_004c0000 + uVar1 * 4);
  param_2[0x2c] = param_1 & 0x10;
  *param_2 = 0x18;
  return;
}


/* ==== decode_insn @ 0041f9e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl decode_insn(void *dec,long pc,long unused,ulong *flags)

{
  int iVar1;
  int iVar2;
  
  iVar1 = opclass_lookup(*(ulong *)((int)dec + 0xb8),dec_cpu_level);
  _dec_pc = pc;
  dec_extword = *(undefined4 *)((int)dec + 0xbc);
  dec_uses_extword = 0;
  dec_init(dec);
  iVar2 = insn_validate(*(ulong *)((int)dec + 0xb8),*(ulong *)(cur_dtype + 8));
  if (iVar2 != 0) {
    if (iVar2 != 7) {
      *(undefined4 *)dec = 0x19;
      return (uint)(iVar2 == 0);
    }
    *flags = *flags | 4;
  }
  (*(code *)(&dec_handlers)[iVar1])(*(undefined4 *)((int)dec + 0xb8),dec);
  if (((*(uint *)((int)dec + 0xac) & 0x20) != 0) || (*(int *)dec == 0)) {
    *(uint *)((int)dec + 0xac) = *(uint *)((int)dec + 0xac) | 0x80;
  }
  if (dec_uses_extword != 0) {
    *(uint *)((int)dec + 0xac) = *(uint *)((int)dec + 0xac) | 0x40;
  }
  return (uint)(iVar2 == 0);
}


/* ==== dec_init @ 0041fab0 ==== */

void __cdecl dec_init(void *dec)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  *(undefined4 *)dec = 0;
  *(undefined4 *)((int)dec + 4) = 0;
  puVar2 = &DAT_00492000;
  puVar3 = (undefined4 *)((int)dec + 8);
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = &DAT_00492000;
  puVar3 = (undefined4 *)((int)dec + 0x1c);
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = &DAT_00492000;
  puVar3 = (undefined4 *)((int)dec + 0x30);
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = &DAT_00492000;
  puVar3 = (undefined4 *)((int)dec + 0x44);
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = &DAT_00492000;
  puVar3 = (undefined4 *)((int)dec + 0x58);
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = &DAT_00492000;
  puVar3 = (undefined4 *)((int)dec + 0x6c);
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = &DAT_00492000;
  puVar3 = (undefined4 *)((int)dec + 0x80);
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = &DAT_00492000;
  puVar3 = (undefined4 *)((int)dec + 0x94);
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  *(undefined4 *)((int)dec + 0xa8) = 0x10;
  *(undefined4 *)((int)dec + 0xac) = 0;
  *(undefined4 *)((int)dec + 0xb0) = 0;
  *(undefined4 *)((int)dec + 0xb4) = 0;
  return;
}


/* ==== dis_fmt_h41fb60 @ 0041fb60 ==== */

undefined4 dis_fmt_h41fb60(undefined4 param_1,undefined4 *param_2)

{
  *param_2 = 0x3f;
  return 1;
}


