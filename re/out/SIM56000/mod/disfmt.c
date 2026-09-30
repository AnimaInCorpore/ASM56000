/* ==== dis_fmt_c0 @ 0041fb70 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_c0(ulong opw,long *tok)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  long *tok_00;
  uint uVar8;
  
  bVar2 = false;
  uVar6 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  uVar7 = uVar6 & 0xffff;
  if (((uVar6 & 0xcf80) == 0xcf80) || ((uVar6 & 0xcf80) == 0xca80)) {
    bVar2 = true;
  }
  if ((((opw & 0x80) != 0) || (*(int *)(&DAT_004c0cf0 + (opw & 0x7f) * 4) != 0)) &&
     ((((((uVar6 & 0x8c80) == 0x8c80 && (((byte)opw & 8) == 8)) ||
        (((uVar6 & 0xc300) == 0xc300 && (((byte)opw & 8) == 8)))) ||
       (((uVar6 & 0x8c80) == 0x8880 && ((opw & 8) == 0)))) ||
      (((uVar6 & 0xc300) == 0xc200 && ((opw & 8) == 0)))))) {
    bVar2 = true;
  }
  tok_00 = tok;
  if (bVar2) {
    *tok = 0x3f;
    tok_00 = tok + 1;
  }
  iVar3 = dis_ea_tokens(opw,tok_00);
  piVar1 = tok_00 + iVar3;
  uVar4 = uVar6 & 0x1f;
  uVar5 = uVar7 >> 10 & 3;
  uVar8 = uVar7 >> 8 & 3;
  if ((uVar6 & 0x18) == 0) {
    uVar4 = uVar4 | 0x20;
  }
  _dis_effect_flags = 6;
  dis_sel_b = uVar4 | 0x8000;
  if ((uVar6 & 0x80) == 0) {
    *piVar1 = uVar5 + 0x91;
    piVar1[1] = 0x99;
    piVar1[2] = 0xf6;
    piVar1[3] = uVar4 + 0xb0;
  }
  else {
    *piVar1 = 0xf6;
    piVar1[1] = uVar4 + 0xb0;
    piVar1[2] = 0x99;
    piVar1[3] = uVar5 + 0x91;
  }
  piVar1[4] = 0x9a;
  uVar4 = uVar7 >> 9 & 0x18;
  if (uVar4 == 0) {
    uVar4 = 0x20;
  }
  uVar7 = uVar7 >> 5 & 3;
  if ((uVar6 & 4) == 0) {
    uVar7 = uVar7 | 4;
  }
  uVar7 = uVar7 | uVar4;
  dis_sel_c = (uint)CONCAT11(0x80,(char)uVar7);
  if ((uVar6 & 0x4000) != 0) {
    piVar1[5] = 0xf7;
    piVar1[6] = uVar7 + 0xb0;
    piVar1[7] = 0x99;
    piVar1[8] = uVar8 + 0x95;
    return (int)piVar1 + (0x24 - (int)tok) >> 2;
  }
  piVar1[5] = uVar8 + 0x95;
  piVar1[6] = 0x99;
  piVar1[7] = 0xf7;
  piVar1[8] = uVar7 + 0xb0;
  return (int)piVar1 + (0x24 - (int)tok) >> 2;
}


/* ==== dis_fmt_c1 @ 0041fd70 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c1(ulong opw,long *tok)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar6 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  iVar1 = dis_ea_tokens(opw,tok);
  uVar4 = uVar6 & 0x3f;
  uVar7 = (uVar6 & 0xffff) >> 8 & 7;
  uVar5 = (uVar6 & 0x800 | 0x23000) >> 0xb;
  piVar2 = tok + iVar1;
  if ((uVar4 == 0x34) || (opw = 0, uVar4 == 0x30)) {
    opw = 0xfffffffc;
  }
  if (uVar4 == 0x34) {
    _dis_effect_flags = 0;
  }
  else {
    _dis_effect_flags = (-(uint)(uVar5 != 0x47) & 0xfffffffe) + 4;
  }
  dis_sel_b = uVar4 | 0x8000;
  dis_sel_c = dis_sel_b;
  if ((uVar6 & 0x80) != 0) {
    if (uVar4 != 0x34) {
      *piVar2 = uVar5 + 0xb0;
      piVar2 = piVar2 + 1;
    }
    *piVar2 = uVar4 + 0xb0;
    piVar2[1] = opw;
    piVar2[2] = 0x99;
    piVar2[3] = uVar7 + 0x6c;
    return (int)piVar2 + (0x10 - (int)tok) >> 2;
  }
  *piVar2 = uVar7 + 0x6c;
  piVar2[1] = 0x99;
  piVar3 = piVar2 + 2;
  if (uVar4 != 0x34) {
    *piVar3 = uVar5 + 0xb0;
    piVar3 = piVar2 + 3;
    if (uVar4 != 0x34) {
      *piVar3 = uVar4 + 0xb0;
      piVar2[4] = opw;
      return (int)piVar2 + (0x14 - (int)tok) >> 2;
    }
  }
  *piVar3 = 0x3f;
  return (int)piVar3 + (4 - (int)tok) >> 2;
}


/* ==== dis_fmt_c2 @ 0041feb0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c2(ulong opw,long *tok)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint v;
  
  uVar4 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  v = uVar4 & 0x3f;
  fmt_hex_dollar(v,&dis_hex_ea);
  uVar5 = (uVar4 & 0xffff) >> 8 & 7;
  iVar2 = dis_ea_tokens(opw,tok);
  uVar3 = (uVar4 & 0x800 | 0x23000) >> 0xb;
  piVar1 = tok + iVar2;
  _dis_effect_flags = (-(uint)(uVar3 != 0x47) & 0xfffffffe) + 4;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  dis_val_b = v;
  DAT_004dbebc = v;
  if ((uVar4 & 0x80) != 0) {
    *piVar1 = uVar3 + 0xb0;
    piVar1[1] = 0xf0;
    piVar1[2] = -2;
    piVar1[3] = 0x99;
    piVar1[4] = uVar5 + 0x6c;
    return (int)piVar1 + (0x14 - (int)tok) >> 2;
  }
  *piVar1 = uVar5 + 0x6c;
  piVar1[1] = 0x99;
  piVar1[2] = uVar3 + 0xb0;
  piVar1[3] = 0xf0;
  piVar1[4] = -2;
  return (int)piVar1 + (0x14 - (int)tok) >> 2;
}


/* ==== dis_fmt_c3 @ 0041ffc0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c3(ulong opw,long *tok)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar6 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  iVar1 = dis_ea_tokens(opw,tok);
  uVar4 = uVar6 & 0x3f;
  uVar5 = (uVar6 & 0x800 | 0x23000) >> 0xb;
  piVar2 = tok + iVar1;
  if ((uVar4 == 0x34) || (uVar4 == 0x30)) {
    iVar1 = -4;
  }
  else {
    iVar1 = 0;
  }
  uVar7 = (uVar6 & 0xffff) >> 8 & 7;
  if (uVar4 == 0x34) {
    _dis_effect_flags = 0;
  }
  else {
    _dis_effect_flags = (-(uint)(uVar5 != 0x46) & 2) + 2;
  }
  dis_sel_b = uVar4 | 0x8000;
  dis_sel_c = dis_sel_b;
  if ((uVar6 & 0x80) != 0) {
    if (uVar4 != 0x34) {
      *piVar2 = uVar5 + 0xb0;
      piVar2 = piVar2 + 1;
    }
    *piVar2 = uVar4 + 0xb0;
    piVar2[1] = iVar1;
    piVar2[2] = 0x99;
    piVar2[3] = uVar7 + 100;
    return (int)piVar2 + (0x10 - (int)tok) >> 2;
  }
  *piVar2 = uVar7 + 100;
  piVar2[1] = 0x99;
  piVar3 = piVar2 + 2;
  if (uVar4 != 0x34) {
    *piVar3 = uVar5 + 0xb0;
    piVar3 = piVar2 + 3;
    if (uVar4 != 0x34) {
      *piVar3 = uVar4 + 0xb0;
      piVar2[4] = iVar1;
      return (int)piVar2 + (0x14 - (int)tok) >> 2;
    }
  }
  *piVar3 = 0x3f;
  return (int)piVar3 + (4 - (int)tok) >> 2;
}


/* ==== dis_fmt_c4 @ 00420100 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c4(ulong opw,long *tok)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint v;
  
  uVar4 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  v = uVar4 & 0x3f;
  fmt_hex_dollar(v,&dis_hex_ea);
  uVar5 = (uVar4 & 0xffff) >> 8 & 7;
  iVar2 = dis_ea_tokens(opw,tok);
  uVar3 = (uVar4 & 0x800 | 0x23000) >> 0xb;
  piVar1 = tok + iVar2;
  _dis_effect_flags = (-(uint)(uVar3 != 0x47) & 0xfffffffe) + 4;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  dis_val_b = v;
  DAT_004dbebc = v;
  if ((uVar4 & 0x80) != 0) {
    *piVar1 = uVar3 + 0xb0;
    piVar1[1] = 0xf0;
    piVar1[2] = -2;
    piVar1[3] = 0x99;
    piVar1[4] = uVar5 + 100;
    return (int)piVar1 + (0x14 - (int)tok) >> 2;
  }
  *piVar1 = uVar5 + 100;
  piVar1[1] = 0x99;
  piVar1[2] = uVar3 + 0xb0;
  piVar1[3] = 0xf0;
  piVar1[4] = -2;
  return (int)piVar1 + (0x14 - (int)tok) >> 2;
}


/* ==== dis_fmt_c5 @ 00420210 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_c5(ulong opw,long *tok)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  long *tok_00;
  uint uVar8;
  
  bVar1 = false;
  uVar7 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  if (((opw & 0x80) == 0) && (*(int *)(&DAT_004c0cf0 + (opw & 0x7f) * 4) == 0)) goto LAB_004202b1;
  iVar2 = pm_is_short_ea(opw);
  if (iVar2 == 0) {
    if (((uVar7 & 0xf180) != 0x5180) || (((byte)opw & 8) != 8)) {
      if ((uVar7 & 0xf180) != 0x5080) goto LAB_004202b1;
      goto joined_r0x004202aa;
    }
  }
  else if (((uVar7 & 0xf580) != 0x5580) || (((byte)opw & 8) != 8)) {
    if ((uVar7 & 0xf580) != 0x5480) goto LAB_004202b1;
joined_r0x004202aa:
    if ((opw & 8) != 0) goto LAB_004202b1;
  }
  bVar1 = true;
LAB_004202b1:
  tok_00 = tok;
  if (bVar1) {
    *tok = 0x3f;
    tok_00 = tok + 1;
  }
  iVar2 = dis_ea_tokens(opw,tok_00);
  uVar5 = uVar7 & 0x3f;
  uVar6 = (uVar7 & 0x800 | 0x23000) >> 0xb;
  piVar3 = tok_00 + iVar2;
  if ((uVar5 == 0x34) || (uVar5 == 0x30)) {
    iVar2 = -4;
  }
  else {
    iVar2 = 0;
  }
  uVar8 = (uVar7 & 0xffff) >> 8 & 7;
  if (uVar5 == 0x34) {
    _dis_effect_flags = 0;
  }
  else {
    _dis_effect_flags = (-(uint)(uVar6 != 0x46) & 2) + 2;
  }
  dis_sel_b = uVar5 | 0x8000;
  dis_sel_c = dis_sel_b;
  if ((uVar7 & 0x80) == 0) {
    *piVar3 = uVar8 + 0x5c;
    piVar3[1] = 0x99;
    piVar4 = piVar3 + 2;
    if (uVar5 != 0x34) {
      *piVar4 = uVar6 + 0xb0;
      piVar4 = piVar3 + 3;
      if (uVar5 != 0x34) {
        *piVar4 = uVar5 + 0xb0;
        piVar3[4] = iVar2;
        return (int)piVar3 + (0x14 - (int)tok) >> 2;
      }
    }
    *piVar4 = 0x3f;
    return (int)piVar4 + (4 - (int)tok) >> 2;
  }
  if (uVar5 != 0x34) {
    *piVar3 = uVar6 + 0xb0;
    piVar3 = piVar3 + 1;
  }
  *piVar3 = uVar5 + 0xb0;
  piVar3[1] = iVar2;
  piVar3[2] = 0x99;
  piVar3[3] = uVar8 + 0x5c;
  return (int)piVar3 + (0x10 - (int)tok) >> 2;
}


/* ==== pm_is_short_ea @ 004203e0 ==== */

int __cdecl pm_is_short_ea(ulong opw)

{
  if (((opw & 0x80) == 0) && (*(int *)(&DAT_004c0ef0 + (opw & 0x7f) * 4) != 0)) {
    return 1;
  }
  return 0;
}


/* ==== dis_fmt_c6 @ 00420400 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c6(ulong opw,long *tok)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  long *tok_00;
  uint uVar6;
  uint v;
  
  uVar5 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  bVar2 = false;
  if (((opw & 0x80) == 0) && (*(int *)(&DAT_004c0cf0 + (opw & 0x7f) * 4) == 0)) goto LAB_004204a2;
  iVar3 = pm_is_short_ea(opw);
  if (iVar3 == 0) {
    if (((uVar5 & 0xf180) != 0x5180) || (((byte)opw & 8) != 8)) {
      if ((uVar5 & 0xf180) != 0x5080) goto LAB_004204a2;
      goto joined_r0x0042049b;
    }
  }
  else if (((uVar5 & 0xf580) != 0x5580) || (((byte)opw & 8) != 8)) {
    if ((uVar5 & 0xf580) != 0x5480) goto LAB_004204a2;
joined_r0x0042049b:
    if ((opw & 8) != 0) goto LAB_004204a2;
  }
  bVar2 = true;
LAB_004204a2:
  tok_00 = tok;
  if (bVar2) {
    *tok = 0x3f;
    tok_00 = tok + 1;
  }
  v = uVar5 & 0x3f;
  fmt_hex_dollar(v,&dis_hex_ea);
  uVar6 = (uVar5 & 0xffff) >> 8 & 7;
  iVar3 = dis_ea_tokens(opw,tok_00);
  piVar1 = tok_00 + iVar3;
  uVar4 = (uVar5 & 0x800 | 0x23000) >> 0xb;
  _dis_effect_flags = (-(uint)(uVar4 != 0x47) & 0xfffffffe) + 4;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  dis_val_b = v;
  DAT_004dbebc = v;
  if ((uVar5 & 0x80) == 0) {
    *piVar1 = uVar6 + 0x5c;
    piVar1[1] = 0x99;
    piVar1[2] = uVar4 + 0xb0;
    piVar1[3] = 0xf0;
    piVar1[4] = -2;
    return (int)piVar1 + (0x14 - (int)tok) >> 2;
  }
  *piVar1 = uVar4 + 0xb0;
  piVar1[1] = 0xf0;
  piVar1[2] = -2;
  piVar1[3] = 0x99;
  piVar1[4] = uVar6 + 0x5c;
  return (int)piVar1 + (0x14 - (int)tok) >> 2;
}


/* ==== dis_fmt_c7 @ 004205b0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c7(ulong opw,long *tok)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar6 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  iVar1 = dis_ea_tokens(opw,tok);
  uVar4 = uVar6 & 0x3f;
  uVar5 = (uVar6 & 0x800 | 0x23000) >> 0xb;
  piVar2 = tok + iVar1;
  if ((uVar4 == 0x34) || (uVar4 == 0x30)) {
    iVar1 = -4;
  }
  else {
    iVar1 = 0;
  }
  if (uVar4 == 0x34) {
    _dis_effect_flags = 0;
  }
  else {
    _dis_effect_flags = (-(uint)(uVar5 != 0x46) & 2) + 2;
  }
  dis_sel_b = uVar4 | 0x8000;
  uVar7 = (uVar6 & 0xffff) >> 8 & 3;
  dis_sel_c = dis_sel_b;
  if ((uVar6 & 0x80) != 0) {
    if (uVar4 != 0x34) {
      *piVar2 = uVar5 + 0xb0;
      piVar2 = piVar2 + 1;
    }
    *piVar2 = uVar4 + 0xb0;
    piVar2[1] = iVar1;
    piVar2[2] = 0x99;
    piVar2[3] = uVar7 + 0x58;
    return (int)piVar2 + (0x10 - (int)tok) >> 2;
  }
  *piVar2 = uVar7 + 0x58;
  piVar2[1] = 0x99;
  piVar3 = piVar2 + 2;
  if (uVar4 != 0x34) {
    *piVar3 = uVar5 + 0xb0;
    piVar3 = piVar2 + 3;
    if (uVar4 != 0x34) {
      *piVar3 = uVar4 + 0xb0;
      piVar2[4] = iVar1;
      return (int)piVar2 + (0x14 - (int)tok) >> 2;
    }
  }
  *piVar3 = 0x3f;
  return (int)piVar3 + (4 - (int)tok) >> 2;
}


/* ==== dis_fmt_c8 @ 004206e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c8(ulong opw,long *tok)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint v;
  
  uVar4 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  v = uVar4 & 0x3f;
  fmt_hex_dollar(v,&dis_hex_ea);
  uVar5 = (uVar4 & 0xffff) >> 8 & 3;
  iVar2 = dis_ea_tokens(opw,tok);
  uVar3 = (uVar4 & 0x800 | 0x23000) >> 0xb;
  piVar1 = tok + iVar2;
  _dis_effect_flags = (-(uint)(uVar3 != 0x47) & 0xfffffffe) + 4;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  dis_val_b = v;
  DAT_004dbebc = v;
  if ((uVar4 & 0x80) != 0) {
    *piVar1 = uVar3 + 0xb0;
    piVar1[1] = 0xf0;
    piVar1[2] = -2;
    piVar1[3] = 0x99;
    piVar1[4] = uVar5 + 0x58;
    return (int)piVar1 + (0x14 - (int)tok) >> 2;
  }
  *piVar1 = uVar5 + 0x58;
  piVar1[1] = 0x99;
  piVar1[2] = uVar3 + 0xb0;
  piVar1[3] = 0xf0;
  piVar1[4] = -2;
  return (int)piVar1 + (0x14 - (int)tok) >> 2;
}


/* ==== dis_fmt_c9 @ 004207f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_c9(ulong opw,long *tok)

{
  bool bVar1;
  int iVar2;
  long *plVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  bVar1 = false;
  uVar5 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  if ((((opw & 0x80) != 0) || (*(int *)(&DAT_004c0cf0 + (opw & 0x7f) * 4) != 0)) &&
     (((uVar6 = uVar5 & 0xff80, uVar6 == 0x4b80 || (uVar6 == 0x4a80)) ||
      ((((uVar6 == 0x4180 && (((byte)opw & 8) == 8)) || ((uVar6 == 0x4080 && ((opw & 8) == 0)))) ||
       (((uVar6 == 0x4980 && (((byte)opw & 8) == 8)) || ((uVar6 == 0x4880 && ((opw & 8) == 0))))))))
     )) {
    bVar1 = true;
  }
  plVar3 = tok;
  if (bVar1) {
    *tok = 0x3f;
    plVar3 = tok + 1;
  }
  iVar2 = dis_ea_tokens(opw,plVar3);
  uVar6 = uVar5 & 0x3f;
  plVar3 = plVar3 + iVar2;
  if (uVar6 == 0x34) {
    *plVar3 = 0x3f;
    plVar3 = plVar3 + 1;
  }
  uVar4 = (uVar6 != 0x30) - 1 & 0xfffffffc;
  _dis_effect_flags = -(uint)(uVar6 != 0x34) & 8;
  dis_sel_b = uVar6 | 0x8000;
  uVar7 = ((uVar5 & 0xffff) >> 1 & 0x400 | uVar5 & 0x300) >> 8;
  if ((uVar5 & 0x80) != 0) {
    *plVar3 = 0xf8;
    plVar3[1] = uVar6 + 0xb0;
    plVar3[2] = uVar4;
    plVar3[3] = 0x99;
    plVar3[4] = uVar7 + 0x84;
    return (int)plVar3 + (0x14 - (int)tok) >> 2;
  }
  *plVar3 = uVar7 + 0x84;
  plVar3[1] = 0x99;
  plVar3[2] = 0xf8;
  plVar3[3] = uVar6 + 0xb0;
  plVar3[4] = uVar4;
  return (int)plVar3 + (0x14 - (int)tok) >> 2;
}


/* ==== dis_fmt_c10 @ 00420980 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_c10(ulong opw,long *tok)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  long *plVar4;
  uint uVar5;
  uint v;
  
  uVar3 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  bVar1 = false;
  if ((((opw & 0x80) != 0) || (*(int *)(&DAT_004c0cf0 + (opw & 0x7f) * 4) != 0)) &&
     (((uVar5 = uVar3 & 0xff80, uVar5 == 0x4b80 || (uVar5 == 0x4a80)) ||
      ((((uVar5 == 0x4180 && (((byte)opw & 8) == 8)) || ((uVar5 == 0x4080 && ((opw & 8) == 0)))) ||
       (((uVar5 == 0x4980 && (((byte)opw & 8) == 8)) || ((uVar5 == 0x4880 && ((opw & 8) == 0))))))))
     )) {
    bVar1 = true;
  }
  plVar4 = tok;
  if (bVar1) {
    *tok = 0x3f;
    plVar4 = tok + 1;
  }
  v = uVar3 & 0x3f;
  fmt_hex_dollar(v,&dis_hex_ea);
  uVar5 = ((uVar3 & 0xffff) >> 1 & 0x400 | uVar3 & 0x300) >> 8;
  iVar2 = dis_ea_tokens(opw,plVar4);
  plVar4 = plVar4 + iVar2;
  _dis_effect_flags = 8;
  dis_sel_b = 0x100;
  dis_val_b = v;
  if ((uVar3 & 0x80) != 0) {
    *plVar4 = 0xf8;
    plVar4[1] = 0xf0;
    plVar4[2] = -2;
    plVar4[3] = 0x99;
    plVar4[4] = uVar5 + 0x84;
    return (int)plVar4 + (0x14 - (int)tok) >> 2;
  }
  *plVar4 = uVar5 + 0x84;
  plVar4[1] = 0x99;
  plVar4[2] = 0xf8;
  plVar4[3] = 0xf0;
  plVar4[4] = -2;
  return (int)plVar4 + (0x14 - (int)tok) >> 2;
}


/* ==== dis_fmt_c11 @ 00420b00 ==== */

int __cdecl dis_fmt_c11(ulong opw,long *tok)

{
  long *plVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  fmt_hex_dollar(uVar3 & 0xff,&dis_hex_ea);
  iVar2 = dis_ea_tokens(opw,tok);
  plVar1 = tok + iVar2;
  *plVar1 = 0xf2;
  plVar1[1] = -2;
  plVar1[2] = 0x99;
  plVar1[3] = ((uVar3 & 0xffff) >> 8 & 7) + 0x6c;
  return (int)(plVar1 + 3) + (4 - (int)tok) >> 2;
}


/* ==== dis_fmt_c12 @ 00420b80 ==== */

int __cdecl dis_fmt_c12(ulong opw,long *tok)

{
  long *plVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  fmt_hex_dollar(uVar3 & 0xff,&dis_hex_ea);
  iVar2 = dis_ea_tokens(opw,tok);
  plVar1 = tok + iVar2;
  *plVar1 = 0xf2;
  plVar1[1] = -2;
  plVar1[2] = 0x99;
  plVar1[3] = ((uVar3 & 0xffff) >> 8 & 7) + 100;
  return (int)(plVar1 + 3) + (4 - (int)tok) >> 2;
}


/* ==== dis_fmt_c13 @ 00420c00 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c13(ulong opw,long *tok)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  long *plVar4;
  
  uVar3 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  bVar1 = false;
  if (((opw & 0x80) == 0) && (*(int *)(&DAT_004c0cf0 + (opw & 0x7f) * 4) == 0)) goto LAB_00420ca0;
  iVar2 = pm_is_short_ea(opw);
  if (iVar2 == 0) {
    if (((uVar3 & 0xf900) != 0x2900) || (((byte)opw & 8) != 8)) {
      if ((uVar3 & 0xf900) != 0x2800) goto LAB_00420ca0;
      goto joined_r0x00420c96;
    }
  }
  else if (((uVar3 & 0xfd00) != 0x2d00) || (((byte)opw & 8) != 8)) {
    if ((uVar3 & 0xfd00) != 0x2c00) goto LAB_00420ca0;
joined_r0x00420c96:
    if ((opw & 8) != 0) goto LAB_00420ca0;
  }
  bVar1 = true;
LAB_00420ca0:
  plVar4 = tok;
  if (bVar1) {
    *tok = 0x3f;
    plVar4 = tok + 1;
  }
  fmt_hex_dollar(uVar3 & 0xff,&dis_hex_ea);
  iVar2 = dis_ea_tokens(opw,plVar4);
  plVar4 = plVar4 + iVar2;
  *plVar4 = 0xf2;
  plVar4[1] = -2;
  plVar4[2] = 0x99;
  plVar4[3] = ((uVar3 & 0xffff) >> 8 & 7) + 0x5c;
  return (int)plVar4 + (0x10 - (int)tok) >> 2;
}


/* ==== dis_fmt_c14 @ 00420d10 ==== */

int __cdecl dis_fmt_c14(ulong opw,long *tok)

{
  long *plVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  fmt_hex_dollar(uVar3 & 0xff,&dis_hex_ea);
  iVar2 = dis_ea_tokens(opw,tok);
  plVar1 = tok + iVar2;
  *plVar1 = 0xf2;
  plVar1[1] = -2;
  plVar1[2] = 0x99;
  plVar1[3] = ((uVar3 & 0xffff) >> 8 & 3) + 0x58;
  return (int)(plVar1 + 3) + (4 - (int)tok) >> 2;
}


/* ==== dis_fmt_c15 @ 00420d90 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c15(ulong opw,long *tok)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  long *tok_00;
  
  uVar4 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  bVar2 = false;
  if (((opw & 0x80) == 0) && (*(int *)(&DAT_004c0cf0 + (opw & 0x7f) * 4) == 0)) goto LAB_00420e30;
  iVar3 = pm_is_short_ea(opw);
  if (iVar3 == 0) {
    if (((uVar4 & 0xfc19) != 0x2009) || (((byte)opw & 8) != 8)) {
      if ((uVar4 & 0xfc19) != 0x2008) goto LAB_00420e30;
      goto joined_r0x00420e26;
    }
  }
  else if (((uVar4 & 0xfc1d) != 0x200d) || (((byte)opw & 8) != 8)) {
    if ((uVar4 & 0xfc1d) != 0x200c) goto LAB_00420e30;
joined_r0x00420e26:
    if ((opw & 8) != 0) goto LAB_00420e30;
  }
  bVar2 = true;
LAB_00420e30:
  tok_00 = tok;
  if (bVar2) {
    *tok = 0x3f;
    tok_00 = tok + 1;
  }
  iVar3 = dis_ea_tokens(opw,tok_00);
  piVar1 = tok_00 + iVar3;
  if ((uVar4 & 0x1f) < 4) {
    iVar3 = 0x35;
  }
  else {
    iVar3 = (uVar4 & 0x1f) - 3;
  }
  uVar4 = (uVar4 & 0xffff) >> 5 & 0x1f;
  if (uVar4 < 4) {
    iVar5 = 0x35;
  }
  else {
    iVar5 = uVar4 - 3;
  }
  *piVar1 = iVar5 + 0x57;
  piVar1[1] = 0x99;
  piVar1[2] = iVar3 + 0x57;
  return (int)piVar1 + (0xc - (int)tok) >> 2;
}


/* ==== dis_fmt_c18 @ 00420eb0 ==== */

int __cdecl dis_fmt_c18(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_ea_tokens(opw,tok);
  tok[iVar1] = ((int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0x3fU) + 0xb0;
  return (int)(tok + iVar1) + (4 - (int)tok) >> 2;
}


/* ==== dis_fmt_c19 @ 00420ef0 ==== */

int __cdecl dis_fmt_c19(ulong opw,long *tok)

{
  int iVar1;
  long *plVar2;
  
  iVar1 = dis_ea_tokens(opw,tok);
  plVar2 = tok + iVar1;
  if ((((int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0xffffU) != 0x2000) || ((opw & 0xffff) == 0))
  {
    *plVar2 = 0x8c;
    plVar2 = plVar2 + 1;
  }
  return (int)plVar2 - (int)tok >> 2;
}


/* ==== dis_fmt_c20 @ 00420f50 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_c20(ulong opw,long *tok)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  long *plVar7;
  
  bVar1 = false;
  uVar5 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  uVar6 = uVar5 & 0xffff;
  if ((((opw & 0x80) != 0) || (*(int *)(&DAT_004c0cf0 + (opw & 0x7f) * 4) != 0)) &&
     ((((uVar5 & 0xf3c0) == 0x13c0 && (((byte)opw & 8) == 8)) ||
      (((uVar5 & 0xf3c0) == 0x12c0 && ((opw & 8) == 0)))))) {
    bVar1 = true;
  }
  plVar7 = tok;
  if (bVar1) {
    *tok = 0x3f;
    plVar7 = tok + 1;
  }
  iVar2 = dis_ea_tokens(opw,plVar7);
  uVar4 = uVar5 & 0x3f;
  plVar7 = plVar7 + iVar2;
  if ((uVar4 == 0x34) || (uVar4 == 0x30)) {
    iVar2 = -4;
  }
  else {
    iVar2 = 0;
  }
  *plVar7 = (uVar6 >> 0xb & 1) + 0x62;
  plVar7[1] = 0x99;
  plVar7[2] = (uVar6 >> 10 & 1) + 0x58;
  plVar7[3] = 0x9a;
  uVar6 = uVar6 >> 8 & 3;
  piVar3 = plVar7 + 4;
  _dis_effect_flags = -(uint)(uVar4 != 0x34) & 4;
  dis_sel_c = uVar4 | 0x8000;
  if ((uVar5 & 0x80) != 0) {
    if (uVar4 != 0x34) {
      *piVar3 = 0xf7;
      piVar3 = plVar7 + 5;
    }
    *piVar3 = uVar4 + 0xb0;
    piVar3[1] = iVar2;
    piVar3[2] = 0x99;
    piVar3[3] = uVar6 + 0x95;
    return (int)piVar3 + (0x10 - (int)tok) >> 2;
  }
  *piVar3 = uVar6 + 0x95;
  plVar7[5] = 0x99;
  piVar3 = plVar7 + 6;
  if (uVar4 != 0x34) {
    *piVar3 = 0xf7;
    piVar3 = plVar7 + 7;
    if (uVar4 != 0x34) {
      *piVar3 = uVar4 + 0xb0;
      plVar7[8] = iVar2;
      return (int)plVar7 + (0x24 - (int)tok) >> 2;
    }
  }
  *piVar3 = 0x3f;
  return (int)piVar3 + (4 - (int)tok) >> 2;
}


/* ==== dis_fmt_c21 @ 004210f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_c21(ulong opw,long *tok)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  ulong *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  long *tok_00;
  
  bVar1 = false;
  uVar7 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  uVar8 = uVar7 & 0xffff;
  if ((((opw & 0x80) != 0) || (*(int *)(&DAT_004c0cf0 + (opw & 0x7f) * 4) != 0)) &&
     ((((uVar7 & 0xfcc0) == 0x1c80 && (((byte)opw & 8) == 8)) ||
      (((uVar7 & 0xfcc0) == 0x1880 && ((opw & 8) == 0)))))) {
    bVar1 = true;
  }
  tok_00 = tok;
  if (bVar1) {
    *tok = 0x3f;
    tok_00 = tok + 1;
  }
  iVar2 = dis_ea_tokens(opw,tok_00);
  uVar5 = uVar7 & 0x3f;
  piVar3 = tok_00 + iVar2;
  if ((uVar5 == 0x34) || (opw = 0, uVar5 == 0x30)) {
    opw = 0xfffffffc;
  }
  uVar6 = uVar8 >> 10 & 3;
  _dis_effect_flags = -(uint)(uVar5 != 0x34) & 2;
  dis_sel_b = uVar5 | 0x8000;
  if ((uVar7 & 0x80) == 0) {
    *piVar3 = uVar6 + 0x91;
    piVar3[1] = 0x99;
    puVar4 = (ulong *)(piVar3 + 2);
    if (uVar5 != 0x34) {
      *puVar4 = 0xf6;
      puVar4 = (ulong *)(piVar3 + 3);
      if (uVar5 != 0x34) {
        *puVar4 = uVar5 + 0xb0;
        puVar4 = (ulong *)(piVar3 + 4);
        goto LAB_00421242;
      }
    }
    *puVar4 = 0x3f;
  }
  else {
    if (uVar5 != 0x34) {
      *piVar3 = 0xf6;
      piVar3 = piVar3 + 1;
    }
    *piVar3 = uVar5 + 0xb0;
    piVar3[1] = opw;
    piVar3[2] = 0x99;
    puVar4 = (ulong *)(piVar3 + 3);
    opw = uVar6 + 0x91;
LAB_00421242:
    *puVar4 = opw;
  }
  puVar4[1] = 0x9a;
  puVar4[2] = (uVar8 >> 9 & 1) + 0x62;
  puVar4[3] = 0x99;
  puVar4[4] = (uVar8 >> 8 & 1) + 0x5a;
  return (int)puVar4 + (0x14 - (int)tok) >> 2;
}


/* ==== dis_fmt_c22 @ 00421280 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c22(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4212a0(opw,tok,0x18);
  return iVar1;
}


/* ==== dis_fmt_h4212a0 @ 004212a0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_h4212a0(ulong opw,long *tok)

{
  int *piVar1;
  int in_stack_0000000c;
  
  fmt_hex_dollar(opw & 0xfff,&dis_hex_ea);
  *tok = in_stack_0000000c;
  piVar1 = tok + 1;
  if ((in_stack_0000000c == 0x18) || (in_stack_0000000c == 0x15)) {
    *piVar1 = (((int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0xffffU) >> 4 & 0xf) + 0x47;
    piVar1 = tok + 2;
  }
  *piVar1 = 0x9a;
  piVar1[1] = 0xf0;
  dis_sel_a = 0x100;
  _dis_effect_flags = 1;
  DAT_004dbec0 = opw & 0xfff;
  piVar1[2] = -2;
  return (int)piVar1 + (0xc - (int)tok) >> 2;
}


/* ==== dis_fmt_c23 @ 00421340 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c23(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4212a0(opw,tok,0x15);
  return iVar1;
}


/* ==== dis_fmt_c24 @ 00421360 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c24(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4212a0(opw,tok,0x1b);
  return iVar1;
}


/* ==== dis_fmt_c25 @ 00421380 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c25(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4212a0(opw,tok,0x17);
  return iVar1;
}


/* ==== dis_fmt_c26 @ 004213a0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c26(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4213c0(opw,tok,0x18);
  return iVar1;
}


/* ==== dis_fmt_h4213c0 @ 004213c0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_h4213c0(ulong opw,long *tok)

{
  int *piVar1;
  uint uVar2;
  int in_stack_0000000c;
  
  *tok = in_stack_0000000c;
  piVar1 = tok + 1;
  if ((in_stack_0000000c == 0x15) || (in_stack_0000000c == 0x18)) {
    *piVar1 = (opw & 0xf) + 0x47;
    piVar1 = tok + 2;
  }
  *piVar1 = 0x9a;
  uVar2 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0x3f;
  if (uVar2 == 0x34) {
    piVar1[1] = 0x3f;
  }
  else {
    piVar1[1] = uVar2 + 0xb0;
  }
  piVar1[2] = (uVar2 != 0x30) - 1 & 0xfffffffc;
  _dis_effect_flags = 1;
  dis_sel_a = (uint)CONCAT11(0x80,(char)uVar2);
  return (int)piVar1 + (0xc - (int)tok) >> 2;
}


/* ==== dis_fmt_c44 @ 00421460 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c44(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4213c0(opw,tok,0x15);
  return iVar1;
}


/* ==== dis_fmt_c27 @ 00421480 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c27(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4213c0(opw,tok,0x1b);
  return iVar1;
}


/* ==== dis_fmt_c45 @ 004214a0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c45(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4213c0(opw,tok,0x17);
  return iVar1;
}


/* ==== dis_fmt_c32 @ 004214c0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c32(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4214e0(opw,tok,0x1c);
  return iVar1;
}


/* ==== dis_fmt_h4214e0 @ 004214e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_h4214e0(ulong opw,long *tok)

{
  uint v;
  long in_stack_0000000c;
  
  *tok = in_stack_0000000c;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  v = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0x3fU | 0xffc0;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,&dis_hex_ea);
    tok[3] = -2;
  }
  else {
    tok[3] = 0x3f;
  }
  tok[4] = 0x99;
  if ((opw & 0x40) == 0) {
    tok[5] = 0xf6;
  }
  else {
    tok[5] = 0xf7;
  }
  tok[6] = 0xf1;
  fmt_hex_dollar(v,&dis_hex_b);
  tok[7] = -3;
  tok[8] = 0x99;
  tok[9] = -4;
  dis_sel_c = 0x100;
  dis_sel_b = 0x100;
  _dis_effect_flags = (-(uint)((opw & 0x40) != 0) & 2) + 3;
  DAT_004dbebc = v;
  dis_val_b = v;
  dis_sel_a = 0x2000;
  return 10;
}


/* ==== dis_fmt_c33 @ 004215f0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c33(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4214e0(opw,tok,0x19);
  return iVar1;
}


/* ==== dis_fmt_c50 @ 00421610 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c50(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4214e0(opw,tok,0x1a);
  return iVar1;
}


/* ==== dis_fmt_c51 @ 00421630 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c51(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4214e0(opw,tok,0x16);
  return iVar1;
}


/* ==== dis_fmt_c36 @ 00421650 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c36(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421670(opw,tok,0x1c);
  return iVar1;
}


/* ==== dis_fmt_h421670 @ 00421670 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_h421670(ulong opw,long *tok)

{
  int *piVar1;
  uint uVar2;
  long in_stack_0000000c;
  
  *tok = in_stack_0000000c;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,&dis_hex_ea);
    tok[3] = -2;
  }
  else {
    tok[3] = 0x3f;
  }
  tok[4] = 0x99;
  if ((opw & 0x40) == 0) {
    tok[5] = 0xf6;
  }
  else {
    tok[5] = 0xf7;
  }
  uVar2 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0x3f;
  piVar1 = tok + 6;
  if ((uVar2 == 0x34) || (uVar2 == 0x30)) {
    *piVar1 = 0x3f;
  }
  else {
    *piVar1 = uVar2 + 0xb0;
    tok[7] = 0x99;
    piVar1 = tok + 8;
    *piVar1 = -4;
  }
  dis_sel_a = 0x2000;
  dis_sel_c = uVar2 | 0x8000;
  dis_sel_b = uVar2 | 0x8000;
  _dis_effect_flags = (-(uint)((opw & 0x40) != 0) & 2) + 3;
  return (int)piVar1 + (4 - (int)tok) >> 2;
}


/* ==== dis_fmt_c37 @ 00421770 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c37(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421670(opw,tok,0x19);
  return iVar1;
}


/* ==== dis_fmt_c54 @ 00421790 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c54(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421670(opw,tok,0x1a);
  return iVar1;
}


/* ==== dis_fmt_c55 @ 004217b0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c55(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421670(opw,tok,0x16);
  return iVar1;
}


/* ==== dis_fmt_c40 @ 004217d0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c40(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4217f0(opw,tok,0x1c);
  return iVar1;
}


/* ==== dis_fmt_h4217f0 @ 004217f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_h4217f0(ulong opw,long *tok)

{
  uint v;
  long in_stack_0000000c;
  
  *tok = in_stack_0000000c;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  v = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0x3f;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,&dis_hex_ea);
    tok[3] = -2;
  }
  else {
    tok[3] = 0x3f;
  }
  tok[4] = 0x99;
  if ((opw & 0x40) == 0) {
    tok[5] = 0xf6;
  }
  else {
    tok[5] = 0xf7;
  }
  tok[6] = 0xf0;
  fmt_hex_dollar(v,&dis_hex_b);
  tok[7] = -3;
  tok[8] = 0x99;
  tok[9] = -4;
  dis_sel_c = 0x100;
  dis_sel_b = 0x100;
  _dis_effect_flags = (-(uint)((opw & 0x40) != 0) & 2) + 3;
  DAT_004dbebc = v;
  dis_val_b = v;
  dis_sel_a = 0x2000;
  return 10;
}


/* ==== dis_fmt_c41 @ 004218f0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c41(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4217f0(opw,tok,0x19);
  return iVar1;
}


/* ==== dis_fmt_c58 @ 00421910 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c58(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4217f0(opw,tok,0x1a);
  return iVar1;
}


/* ==== dis_fmt_c59 @ 00421930 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c59(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4217f0(opw,tok,0x16);
  return iVar1;
}


/* ==== dis_fmt_c34 @ 00421950 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c34(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421970(opw,tok,0xd);
  return iVar1;
}


/* ==== dis_fmt_h421970 @ 00421970 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_h421970(ulong opw,long *tok)

{
  uint v;
  long in_stack_0000000c;
  
  *tok = in_stack_0000000c;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  v = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0x3fU | 0xffc0;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,&dis_hex_ea);
    tok[3] = -2;
  }
  else {
    tok[3] = 0x3f;
  }
  tok[4] = 0x99;
  if ((opw & 0x40) == 0) {
    tok[5] = 0xf6;
  }
  else {
    tok[5] = 0xf7;
  }
  tok[6] = 0xf1;
  fmt_hex_dollar(v,&dis_hex_b);
  tok[7] = -3;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  _dis_effect_flags = (-(uint)((opw & 0x40) != 0) & 2) + 2;
  DAT_004dbebc = v;
  dis_val_b = v;
  return 8;
}


/* ==== dis_fmt_c35 @ 00421a60 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c35(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421970(opw,tok,10);
  return iVar1;
}


/* ==== dis_fmt_c52 @ 00421a80 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c52(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421970(opw,tok,0xc);
  return iVar1;
}


/* ==== dis_fmt_c53 @ 00421aa0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c53(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421970(opw,tok,0xb);
  return iVar1;
}


/* ==== dis_fmt_c38 @ 00421ac0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c38(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421ae0(opw,tok,0xd);
  return iVar1;
}


/* ==== dis_fmt_h421ae0 @ 00421ae0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_h421ae0(ulong opw,long *tok)

{
  uint uVar1;
  long in_stack_0000000c;
  
  *tok = in_stack_0000000c;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,&dis_hex_ea);
    tok[3] = -2;
  }
  else {
    tok[3] = 0x3f;
  }
  tok[4] = 0x99;
  if ((opw & 0x40) == 0) {
    tok[5] = 0xf6;
  }
  else {
    tok[5] = 0xf7;
  }
  uVar1 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0x3f;
  if (uVar1 == 0x34) {
    tok[6] = 0x3f;
  }
  else {
    tok[6] = uVar1 + 0xb0;
  }
  tok[7] = (uVar1 != 0x30) - 1 & 0xfffffffc;
  _dis_effect_flags = (-(uint)((opw & 0x40) != 0) & 2) + 2;
  dis_sel_b = 0x8000;
  dis_sel_c = 0x8000;
  return 8;
}


/* ==== dis_fmt_c39 @ 00421bd0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c39(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421ae0(opw,tok,10);
  return iVar1;
}


/* ==== dis_fmt_c56 @ 00421bf0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c56(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421ae0(opw,tok,0xc);
  return iVar1;
}


/* ==== dis_fmt_c57 @ 00421c10 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c57(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421ae0(opw,tok,0xb);
  return iVar1;
}


/* ==== dis_fmt_c42 @ 00421c30 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c42(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421c50(opw,tok,0xd);
  return iVar1;
}


/* ==== dis_fmt_h421c50 @ 00421c50 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_h421c50(ulong opw,long *tok)

{
  uint v;
  long in_stack_0000000c;
  
  *tok = in_stack_0000000c;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  v = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0x3f;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,&dis_hex_ea);
    tok[3] = -2;
  }
  else {
    tok[3] = 0x3f;
  }
  tok[4] = 0x99;
  if ((opw & 0x40) == 0) {
    tok[5] = 0xf6;
  }
  else {
    tok[5] = 0xf7;
  }
  tok[6] = 0xf0;
  fmt_hex_dollar(v,&dis_hex_b);
  tok[7] = -3;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  _dis_effect_flags = (-(uint)((opw & 0x40) != 0) & 2) + 2;
  DAT_004dbebc = v;
  dis_val_b = v;
  return 8;
}


/* ==== dis_fmt_c43 @ 00421d30 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c43(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421c50(opw,tok,10);
  return iVar1;
}


/* ==== dis_fmt_c60 @ 00421d50 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c60(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421c50(opw,tok,0xc);
  return iVar1;
}


/* ==== dis_fmt_c61 @ 00421d70 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c61(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h421c50(opw,tok,0xb);
  return iVar1;
}


/* ==== dis_fmt_c65 @ 00421d90 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_c65(ulong opw,long *tok)

{
  ulong uVar1;
  uint v;
  ulong *puVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar1 = opw;
  uVar4 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  uVar5 = uVar4 & 0x3f;
  uVar7 = (opw & 0xff) >> 6 | 0x46;
  uVar6 = (uVar4 & 0x100 | 0x4600) >> 8;
  if ((uVar5 == 0x34) || (opw = 0, uVar5 == 0x30)) {
    opw = 0xfffffffc;
  }
  v = uVar1 & 0x3f | 0xffc0;
  fmt_hex_dollar(v,&dis_hex_ea);
  *tok = 0x24;
  tok[1] = 0x9a;
  piVar3 = tok + 2;
  if ((uVar4 & 0x80) != 0) {
    if (uVar5 != 0x34) {
      *piVar3 = uVar7 + 0xb0;
      piVar3 = tok + 3;
    }
    *piVar3 = uVar5 + 0xb0;
    piVar3[1] = opw;
    piVar3[2] = 0x99;
    piVar3[3] = uVar6 + 0xb0;
    piVar3[4] = 0xf1;
    piVar3[5] = -2;
    puVar2 = (ulong *)(piVar3 + 6);
    if (uVar5 == 0x34) {
      _dis_effect_flags = 0;
    }
    else {
      _dis_effect_flags = (-(uint)(uVar7 != 0x47) & 0x10) + 0x10;
    }
    _dis_effect_flags = (-(uint)(uVar6 != 0x47) & 0xfffffffe) + 4 | _dis_effect_flags;
    goto LAB_00421f1a;
  }
  *piVar3 = uVar6 + 0xb0;
  tok[3] = 0xf1;
  tok[4] = -2;
  tok[5] = 0x99;
  puVar2 = (ulong *)(tok + 6);
  if (uVar5 == 0x34) {
LAB_00421e65:
    *puVar2 = 0x3f;
  }
  else {
    *puVar2 = uVar7 + 0xb0;
    puVar2 = (ulong *)(tok + 7);
    if (uVar5 == 0x34) goto LAB_00421e65;
    *puVar2 = uVar5 + 0xb0;
    puVar2 = (ulong *)(tok + 8);
    *puVar2 = opw;
  }
  puVar2 = puVar2 + 1;
  _dis_effect_flags =
       (-(uint)(uVar7 != 0x47) & 0x10) + 0x10 | (-(uint)(uVar6 != 0x47) & 0xfffffffe) + 4;
LAB_00421f1a:
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  dis_sel_e = uVar5 | 0x8000;
  dis_sel_d = uVar5 | 0x8000;
  DAT_004dbebc = v;
  dis_val_b = v;
  return (int)puVar2 - (int)tok >> 2;
}


/* ==== dis_fmt_c66 @ 00421f60 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c66(ulong opw,long *tok)

{
  ulong uVar1;
  int *piVar2;
  ulong *puVar3;
  uint v;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar1 = opw;
  uVar4 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  uVar6 = uVar4 & 0x3f;
  uVar5 = (uVar4 & 0x100 | 0x4600) >> 8;
  if ((uVar6 == 0x34) || (opw = 0, uVar6 == 0x30)) {
    opw = 0xfffffffc;
  }
  v = uVar1 & 0x3f | 0xffc0;
  fmt_hex_dollar(v,&dis_hex_ea);
  *tok = 0x24;
  tok[1] = 0x9a;
  piVar2 = tok + 2;
  if ((uVar4 & 0x80) == 0) {
    *piVar2 = uVar5 + 0xb0;
    tok[3] = 0xf1;
    tok[4] = -2;
    tok[5] = 0x99;
    puVar3 = (ulong *)(tok + 6);
    if (uVar6 != 0x34) {
      *puVar3 = 0xf9;
      puVar3 = (ulong *)(tok + 7);
      if (uVar6 != 0x34) {
        *puVar3 = uVar6 + 0xb0;
        puVar3 = (ulong *)(tok + 8);
        *puVar3 = opw;
        goto LAB_00422081;
      }
    }
    *puVar3 = 0x3f;
  }
  else {
    if (uVar6 != 0x34) {
      *piVar2 = 0xf9;
      piVar2 = tok + 3;
    }
    *piVar2 = uVar6 + 0xb0;
    piVar2[1] = opw;
    piVar2[2] = 0x99;
    piVar2[3] = uVar5 + 0xb0;
    piVar2[4] = 0xf1;
    puVar3 = (ulong *)(piVar2 + 5);
    *puVar3 = 0xfffffffe;
  }
LAB_00422081:
  DAT_004dbebc = v;
  dis_sel_a = uVar6 | 0x8000;
  _dis_effect_flags = (-(uint)(uVar5 != 0x47) & 0xfffffffe) + 4 | (uint)(uVar6 != 0x34);
  dis_val_b = v;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  return (int)puVar3 + (4 - (int)tok) >> 2;
}


/* ==== dis_fmt_c67 @ 004220e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c67(ulong opw,long *tok)

{
  uint v;
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  v = opw & 0x3f | 0xffc0;
  uVar4 = (uVar3 & 0x100 | 0x4600) >> 8;
  fmt_hex_dollar(v,&dis_hex_ea);
  iVar1 = 0;
  if ((uVar3 & 0x3f) < 4) {
    iVar1 = 0x35;
  }
  uVar2 = uVar3 & 0x38;
  if (uVar2 == 0x28) {
    iVar1 = 0x35;
  }
  if (uVar2 == 0x30) {
    iVar1 = 0x35;
  }
  if (uVar2 == 0x38) {
    iVar1 = (uVar3 & 0x2f) - 3;
  }
  if (iVar1 == 0) {
    iVar1 = (uVar3 & 0x3f) - 3;
  }
  *tok = 0x24;
  tok[1] = 0x9a;
  if ((uVar3 & 0x80) == 0) {
    tok[2] = uVar4 + 0xb0;
    tok[3] = 0xf1;
    tok[4] = -2;
    tok[5] = 0x99;
    tok[6] = iVar1 + 0x57;
  }
  else {
    tok[2] = iVar1 + 0x57;
    tok[3] = 0x99;
    tok[4] = uVar4 + 0xb0;
    tok[5] = 0xf1;
    tok[6] = -2;
  }
  DAT_004dbebc = v;
  dis_val_b = v;
  _dis_effect_flags = (-(uint)(uVar4 != 0x47) & 0xfffffffe) + 4;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  return 7;
}


/* ==== dis_fmt_c69 @ 00422220 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c69(ulong opw,long *tok)

{
  long *plVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  
  uVar3 = (int)(((int)opw >> 0x1f & 0xffU) + opw) >> 8;
  uVar2 = uVar3 & 0x3f;
  uVar4 = (uVar2 != 0x30) - 1 & 0xfffffffc;
  plVar1 = tok;
  if (uVar2 == 0x34) {
    *tok = 0x3f;
    plVar1 = tok + 1;
  }
  if ((opw & 0x3f) < 4) {
    iVar5 = 0x35;
  }
  else {
    uVar6 = opw & 0x38;
    if (uVar6 == 0x28) {
      iVar5 = 0x35;
    }
    else if (uVar6 == 0x30) {
      iVar5 = 0x35;
    }
    else if (uVar6 == 0x38) {
      iVar5 = (opw & 0x2f) - 3;
    }
    else {
      iVar5 = (opw & 0x3f) - 3;
    }
  }
  *plVar1 = 0x22;
  plVar1[1] = 0x9a;
  if ((uVar3 & 0x80) == 0) {
    plVar1[2] = iVar5 + 0x57;
    plVar1[3] = 0x99;
    plVar1[4] = 0xf9;
    plVar1[5] = uVar2 + 0xb0;
    plVar1[6] = uVar4;
  }
  else {
    plVar1[2] = 0xf9;
    plVar1[3] = uVar2 + 0xb0;
    plVar1[4] = uVar4;
    plVar1[5] = 0x99;
    plVar1[6] = iVar5 + 0x57;
  }
  _dis_effect_flags = 1;
  dis_sel_a = (uint)CONCAT11(0x80,(char)uVar2);
  return (int)plVar1 + (0x1c - (int)tok) >> 2;
}


/* ==== dis_fmt_c70 @ 00422330 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c70(ulong opw,long *tok)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint v;
  
  uVar2 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  v = uVar2 & 0x3f;
  fmt_hex_dollar(v,&dis_hex_ea);
  if ((opw & 0x3f) < 4) {
    iVar3 = 0x35;
  }
  else {
    uVar1 = opw & 0x38;
    if (uVar1 == 0x28) {
      iVar3 = 0x35;
    }
    else if (uVar1 == 0x30) {
      iVar3 = 0x35;
    }
    else if (uVar1 == 0x38) {
      iVar3 = (opw & 0x2f) - 3;
    }
    else {
      iVar3 = (opw & 0x3f) - 3;
    }
  }
  *tok = 0x22;
  tok[1] = 0x9a;
  if ((uVar2 & 0x80) == 0) {
    tok[2] = iVar3 + 0x57;
    tok[3] = 0x99;
    tok[4] = 0xf9;
    tok[5] = 0xf0;
    tok[6] = -2;
  }
  else {
    tok[2] = 0xf9;
    tok[3] = 0xf0;
    tok[4] = -2;
    tok[5] = 0x99;
    tok[6] = iVar3 + 0x57;
  }
  DAT_004dbec0 = v;
  _dis_effect_flags = 1;
  dis_sel_a = 0x100;
  return 7;
}


/* ==== dis_fmt_c75 @ 00422440 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c75(ulong opw,long *tok)

{
  fmt_hex_dollar((opw & 0xf) << 8 | (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0xffU,&dis_hex_ea
                );
  *tok = 0x2d;
  tok[1] = 0x9a;
  tok[2] = 0xf3;
  tok[3] = -2;
  return 4;
}


/* ==== dis_fmt_c71 @ 004224a0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c71(ulong opw,long *tok)

{
  uint uVar1;
  uint uVar2;
  
  *tok = 0x2d;
  uVar1 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  tok[1] = 0x9a;
  if ((uVar1 & 0x3f) < 4) {
    tok[2] = 0x8c;
    return 3;
  }
  uVar2 = uVar1 & 0x38;
  if (uVar2 == 0x28) {
    tok[2] = 0x8c;
    return 3;
  }
  if (uVar2 == 0x30) {
    tok[2] = 0x8c;
    return 3;
  }
  if (uVar2 == 0x38) {
    tok[2] = (uVar1 & 0x2f) + 0x54;
    return 3;
  }
  tok[2] = (uVar1 & 0x3f) + 0x54;
  return 3;
}


/* ==== dis_fmt_c73 @ 00422560 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c73(ulong opw,long *tok)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  
  *tok = 0x2d;
  tok[1] = 0x9a;
  uVar1 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0x3f;
  puVar3 = (uint *)(tok + 2);
  uVar2 = (opw & 0xff) >> 6 | 0xf6;
  if ((uVar1 == 0x30) || (uVar1 == 0x34)) {
    *puVar3 = 0x3f;
  }
  else {
    *puVar3 = uVar2;
    puVar3 = (uint *)(tok + 3);
    *puVar3 = uVar1 + 0xb0;
  }
  dis_sel_b = (uint)CONCAT11(0x80,(char)uVar1);
  dis_sel_c = dis_sel_b;
  _dis_effect_flags = (-(uint)(uVar2 != 0xf7) & 0xfffffffe) + 4;
  return (int)puVar3 + (4 - (int)tok) >> 2;
}


/* ==== dis_fmt_c77 @ 004225f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c77(ulong opw,long *tok)

{
  uint v;
  
  *tok = 0x2d;
  tok[1] = 0x9a;
  v = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0x3f;
  if ((opw & 0x40) == 0) {
    tok[2] = 0xf6;
  }
  else {
    tok[2] = 0xf7;
  }
  tok[3] = 0xf0;
  fmt_hex_dollar(v,&dis_hex_ea);
  tok[4] = -2;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  _dis_effect_flags = (-(uint)((opw & 0x40) != 0) & 2) + 2;
  DAT_004dbebc = v;
  dis_val_b = v;
  return 5;
}


/* ==== dis_fmt_c76 @ 004226a0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c76(ulong opw,long *tok)

{
  fmt_hex_dollar((opw & 0xf) << 8 | (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0xffU,&dis_hex_ea
                );
  *tok = 0x12;
  tok[1] = 0x9a;
  tok[2] = 0xf3;
  tok[3] = -2;
  tok[4] = 0x99;
  tok[5] = -5;
  dis_sel_a = 0x4000;
  _dis_effect_flags = 1;
  return 6;
}


/* ==== dis_fmt_c72 @ 00422730 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c72(ulong opw,long *tok)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  *tok = 0x12;
  uVar1 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  tok[1] = 0x9a;
  uVar2 = uVar1 & 0x3f;
  if (uVar2 < 4) {
    iVar3 = 0x35;
  }
  else {
    uVar4 = uVar1 & 0x38;
    if (uVar4 == 0x28) {
      iVar3 = 0x35;
    }
    else if (uVar4 == 0x30) {
      iVar3 = 0x35;
    }
    else if (uVar4 == 0x38) {
      iVar3 = (uVar1 & 0x2f) - 3;
    }
    else {
      iVar3 = uVar2 - 3;
    }
  }
  if (uVar2 == 0x3c) {
    iVar3 = 0x35;
  }
  tok[2] = iVar3 + 0x57;
  tok[3] = 0x99;
  tok[4] = -5;
  dis_sel_a = 0x4000;
  _dis_effect_flags = 1;
  return 5;
}


/* ==== dis_fmt_c74 @ 004227e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c74(ulong opw,long *tok)

{
  uint uVar1;
  int *piVar2;
  
  *tok = 0x12;
  tok[1] = 0x9a;
  piVar2 = tok + 2;
  uVar1 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0x3f;
  if ((uVar1 == 0x30) || (uVar1 == 0x34)) {
    *piVar2 = 0x3f;
  }
  else {
    *piVar2 = ((opw & 0x40) != 0) + 0xf6;
    tok[3] = uVar1 + 0xb0;
    tok[4] = 0x99;
    piVar2 = tok + 5;
    *piVar2 = -5;
  }
  dis_sel_a = 0x4000;
  dis_sel_c = (uint)CONCAT11(0x80,(char)uVar1);
  dis_sel_b = dis_sel_c;
  _dis_effect_flags = (-(uint)((opw & 0x40) != 0) & 2) + 3;
  return (int)piVar2 + (4 - (int)tok) >> 2;
}


/* ==== dis_fmt_c78 @ 00422890 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c78(ulong opw,long *tok)

{
  uint v;
  
  *tok = 0x12;
  tok[1] = 0x9a;
  v = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0x3f;
  if ((opw & 0x40) == 0) {
    tok[2] = 0xf6;
  }
  else {
    tok[2] = 0xf7;
  }
  tok[3] = 0xf0;
  fmt_hex_dollar(v,&dis_hex_ea);
  tok[4] = -2;
  tok[5] = 0x99;
  tok[6] = -5;
  dis_sel_c = 0x100;
  dis_sel_b = 0x100;
  _dis_effect_flags = (-(uint)((opw & 0x40) != 0) & 2) + 3;
  DAT_004dbebc = v;
  dis_val_b = v;
  dis_sel_a = 0x4000;
  return 7;
}


/* ==== dis_fmt_c82 @ 00422960 ==== */

int __cdecl dis_fmt_c82(ulong opw,long *tok)

{
  fmt_hex_dollar((int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0xff,&dis_hex_ea);
  *tok = 0x22;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  tok[3] = -2;
  tok[4] = 0x99;
  tok[5] = (opw & 7) + 0x74;
  return 6;
}


/* ==== dis_fmt_c80 @ 004229d0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c80(ulong opw,long *tok)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  uVar3 = (int)(((int)opw >> 0x1f & 0xffU) + opw) >> 8;
  iVar4 = 0;
  uVar2 = uVar3 & 0x3f;
  uVar5 = (opw & 0xff) >> 6 | 0x46;
  if (uVar2 == 0x34) {
    _dis_effect_flags = 0;
  }
  else {
    _dis_effect_flags = (-(uint)(uVar5 != 0x46) & 2) + 2;
  }
  dis_sel_b = uVar2 | 0x8000;
  if ((uVar2 == 0x34) || (uVar2 == 0x30)) {
    iVar4 = -4;
  }
  dis_sel_c = dis_sel_b;
  *tok = 0x22;
  tok[1] = 0x9a;
  piVar1 = tok + 2;
  if ((uVar3 & 0x80) != 0) {
    if (uVar2 != 0x34) {
      *piVar1 = uVar5 + 0xb0;
      piVar1 = tok + 3;
    }
    *piVar1 = uVar2 + 0xb0;
    piVar1[1] = iVar4;
    piVar1[2] = 0x99;
    piVar1[3] = (opw & 7) + 0x74;
    return (int)piVar1 + (0x10 - (int)tok) >> 2;
  }
  *piVar1 = (opw & 7) + 0x74;
  tok[3] = 0x99;
  piVar1 = tok + 4;
  if (uVar2 != 0x34) {
    *piVar1 = uVar5 + 0xb0;
    piVar1 = tok + 5;
    if (uVar2 != 0x34) {
      *piVar1 = uVar2 + 0xb0;
      tok[6] = iVar4;
      return 7;
    }
  }
  *piVar1 = 0x3f;
  return (int)piVar1 + (4 - (int)tok) >> 2;
}


/* ==== dis_fmt_c84 @ 00422b00 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_c84(ulong opw,long *tok)

{
  uint uVar1;
  uint uVar2;
  uint v;
  
  uVar1 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  v = uVar1 & 0x3f;
  fmt_hex_dollar(v,&dis_hex_ea);
  uVar2 = (opw & 0xff) >> 6 | 0x46;
  *tok = 0x22;
  tok[1] = 0x9a;
  _dis_effect_flags = (-(uint)(uVar2 != 0x47) & 0xfffffffe) + 4;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  dis_val_b = v;
  DAT_004dbebc = v;
  if ((uVar1 & 0x80) != 0) {
    tok[2] = uVar2 + 0xb0;
    tok[3] = 0xf0;
    tok[4] = -2;
    tok[5] = 0x99;
    tok[6] = (opw & 7) + 0x74;
    return 7;
  }
  tok[2] = (opw & 7) + 0x74;
  tok[3] = 0x99;
  tok[4] = uVar2 + 0xb0;
  tok[5] = 0xf0;
  tok[6] = -2;
  return 7;
}


/* ==== dis_fmt_c81 @ 00422c10 ==== */

int __cdecl dis_fmt_c81(ulong opw,long *tok)

{
  fmt_hex_dollar((int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0xff,&dis_hex_ea);
  *tok = 0x22;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  tok[3] = -2;
  tok[4] = 0x99;
  tok[5] = (opw & 7) + 0x7c;
  return 6;
}


/* ==== dis_fmt_c79 @ 00422c80 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c79(ulong opw,long *tok)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  uVar3 = (int)(((int)opw >> 0x1f & 0xffU) + opw) >> 8;
  uVar2 = uVar3 & 0x3f;
  uVar5 = (opw & 0xff) >> 6 | 0x46;
  if ((uVar2 == 0x34) || (uVar2 == 0x30)) {
    iVar4 = -4;
  }
  else {
    iVar4 = 0;
  }
  if (uVar2 == 0x34) {
    _dis_effect_flags = 0;
  }
  else {
    _dis_effect_flags = (-(uint)(uVar5 != 0x47) & 0xfffffffe) + 4;
  }
  dis_sel_b = uVar2 | 0x8000;
  dis_sel_c = dis_sel_b;
  *tok = 0x22;
  tok[1] = 0x9a;
  piVar1 = tok + 2;
  if ((uVar3 & 0x80) != 0) {
    if (uVar2 != 0x34) {
      *piVar1 = uVar5 + 0xb0;
      piVar1 = tok + 3;
    }
    *piVar1 = uVar2 + 0xb0;
    piVar1[1] = iVar4;
    piVar1[2] = 0x99;
    piVar1[3] = (opw & 7) + 0x7c;
    return (int)piVar1 + (0x10 - (int)tok) >> 2;
  }
  *piVar1 = (opw & 7) + 0x7c;
  tok[3] = 0x99;
  piVar1 = tok + 4;
  if (uVar2 != 0x34) {
    *piVar1 = uVar5 + 0xb0;
    piVar1 = tok + 5;
    if (uVar2 != 0x34) {
      *piVar1 = uVar2 + 0xb0;
      tok[6] = iVar4;
      return 7;
    }
  }
  *piVar1 = 0x3f;
  return (int)piVar1 + (4 - (int)tok) >> 2;
}


/* ==== dis_fmt_c83 @ 00422dc0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c83(ulong opw,long *tok)

{
  uint uVar1;
  uint uVar2;
  uint v;
  
  uVar1 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  v = uVar1 & 0x3f;
  fmt_hex_dollar(v,&dis_hex_ea);
  uVar2 = (opw & 0xff) >> 6 | 0x46;
  *tok = 0x22;
  tok[1] = 0x9a;
  if ((uVar1 & 0x80) == 0) {
    tok[2] = (opw & 7) + 0x7c;
    tok[3] = 0x99;
    tok[4] = uVar2 + 0xb0;
    tok[5] = 0xf0;
    tok[6] = -2;
  }
  else {
    tok[2] = uVar2 + 0xb0;
    tok[3] = 0xf0;
    tok[4] = -2;
    tok[5] = 0x99;
    tok[6] = (opw & 7) + 0x7c;
  }
  DAT_004dbebc = v;
  dis_val_b = v;
  _dis_effect_flags = (-(uint)(uVar2 != 0x47) & 0xfffffffe) + 4;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  return 7;
}


/* ==== dis_fmt_c86 @ 00422ec0 ==== */

int __cdecl dis_fmt_c86(ulong opw,long *tok)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  if ((uVar1 & 0x3f) < 4) {
    iVar2 = 0x35;
  }
  else {
    uVar3 = uVar1 & 0x38;
    if (uVar3 == 0x28) {
      iVar2 = 0x35;
    }
    else if (uVar3 == 0x30) {
      iVar2 = 0x35;
    }
    else if (uVar3 == 0x38) {
      iVar2 = (uVar1 & 0x2f) - 3;
    }
    else {
      iVar2 = (uVar1 & 0x3f) - 3;
    }
  }
  *tok = 0x22;
  tok[1] = 0x9a;
  if ((uVar1 & 0x80) != 0) {
    tok[2] = iVar2 + 0x57;
    tok[3] = 0x99;
    tok[4] = (opw & 7) + 0x74;
    return 5;
  }
  tok[2] = (opw & 7) + 0x74;
  tok[3] = 0x99;
  tok[4] = iVar2 + 0x57;
  return 5;
}


/* ==== dis_fmt_c85 @ 00422f80 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c85(ulong opw,long *tok)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  uVar2 = opw & 7;
  uVar3 = (int)(((int)opw >> 0x1f & 0xffU) + opw) >> 8;
  uVar1 = uVar3 & 0x3f;
  if (uVar1 < 4) {
    iVar4 = 0x35;
  }
  else {
    uVar5 = uVar3 & 0x38;
    if (uVar5 == 0x28) {
      iVar4 = 0x35;
    }
    else if (uVar5 == 0x30) {
      iVar4 = 0x35;
    }
    else if (uVar5 == 0x38) {
      iVar4 = (uVar3 & 0x2f) - 3;
    }
    else {
      iVar4 = uVar1 - 3;
    }
  }
  if ((uVar2 == 4) && (uVar1 == 0x3c)) {
    iVar4 = 0x35;
  }
  *tok = 0x22;
  tok[1] = 0x9a;
  if ((uVar3 & 0x80) != 0) {
    tok[2] = iVar4 + 0x57;
    tok[3] = 0x99;
    tok[4] = uVar2 + 0x7c;
    return 5;
  }
  tok[2] = uVar2 + 0x7c;
  tok[3] = 0x99;
  tok[4] = iVar4 + 0x57;
  return 5;
}


/* ==== dis_fmt_c88 @ 00423050 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_c88(ulong opw,long *tok)

{
  uint uVar1;
  
  uVar1 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0x3f;
  *tok = 0x1f;
  tok[1] = 0x9a;
  tok[2] = uVar1 + 0xb0;
  tok[3] = 0x99;
  tok[4] = (opw & 7) + 100;
  _dis_effect_flags = 1;
  dis_sel_a = uVar1 | 0x10000;
  return 5;
}


/* ==== dis_fmt_c87 @ 004230c0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_c87(ulong opw,long *tok)

{
  uint uVar1;
  
  uVar1 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0x3f;
  *tok = 0x1f;
  tok[1] = 0x9a;
  tok[2] = uVar1 + 0xb0;
  tok[3] = 0x99;
  tok[4] = (opw & 7) + 0x6c;
  _dis_effect_flags = 1;
  dis_sel_a = uVar1 | 0x10000;
  return 5;
}


/* ==== dis_fmt_c89 @ 00423130 ==== */

int __cdecl dis_fmt_c89(ulong opw,long *tok)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  uVar1 = (opw & 0xffff) >> 4 & 7;
  uVar3 = (opw & 0xffff) >> 3 & 1;
  if ((uVar1 < 4) && (uVar1 != 0)) {
    *tok = 0x3f;
    return 1;
  }
  if (uVar3 != 0) {
    uVar1 = uVar1 | 8;
  }
  *tok = 0x3b;
  tok[1] = ((uVar2 & 0xffff) >> 4 & 0xf) + 0x47;
  tok[2] = 0x9a;
  tok[3] = uVar1 + 0xa0;
  tok[4] = 0x99;
  tok[5] = uVar3 + 0x62;
  tok[6] = 0x9a;
  tok[7] = (uVar2 & 7) + 100;
  tok[8] = 0x99;
  tok[9] = (opw & 7) + 100;
  return 10;
}


/* ==== dis_fmt_c90 @ 00423210 ==== */

int __cdecl dis_fmt_c90(ulong opw,long *tok)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (opw & 0xffff) >> 4 & 7;
  uVar2 = (opw & 0xffff) >> 3 & 1;
  if ((uVar1 < 4) && (uVar1 != 0)) {
    *tok = 0x3f;
    return 1;
  }
  if (uVar2 != 0) {
    uVar1 = uVar1 | 8;
  }
  *tok = 0x3b;
  tok[1] = (((int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0xffffU) >> 4 & 0xf) + 0x47;
  tok[2] = 0x9a;
  tok[3] = uVar1 + 0xa0;
  tok[4] = 0x99;
  tok[5] = uVar2 + 0x62;
  return 6;
}


/* ==== dis_fmt_c91 @ 004232b0 ==== */

int __cdecl dis_fmt_c91(ulong opw,long *tok)

{
  *tok = 0x29;
  tok[1] = 0x9a;
  tok[2] = ((int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 7U) + 100;
  tok[3] = 0x99;
  tok[4] = (opw >> 3 & 1) + 0x62;
  return 5;
}


/* ==== dis_fmt_c92 @ 00423310 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c92(ulong opw,long *tok)

{
  *tok = 0x11;
  tok[1] = 0x9a;
  tok[2] = ((opw & 0xffff) >> 4 & 7) + 0xa0;
  tok[3] = 0x99;
  tok[4] = ((opw & 0xffff) >> 3 & 1) + 0x62;
  return 5;
}


/* ==== dis_fmt_c95 @ 00423370 ==== */

int __cdecl dis_fmt_c95(ulong opw,long *tok)

{
  fmt_hex_dollar((int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0xff,&dis_hex_ea);
  *tok = 0x2c;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  tok[3] = -2;
  tok[4] = 0x99;
  tok[5] = (opw & 3) + 0x9c;
  return 6;
}


/* ==== dis_fmt_c96 @ 004233e0 ==== */

int __cdecl dis_fmt_c96(ulong opw,long *tok)

{
  fmt_hex_dollar((int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8 & 0xff,&dis_hex_ea);
  *tok = 7;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  tok[3] = -2;
  tok[4] = 0x99;
  tok[5] = (opw & 3) + 0x9c;
  return 6;
}


/* ==== dis_fmt_c97 @ 00423450 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c97(ulong opw,long *tok)

{
  *tok = 0x13;
  return 1;
}


/* ==== dis_fmt_c98 @ 00423460 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c98(ulong opw,long *tok)

{
  *tok = 0x36;
  return 1;
}


/* ==== dis_fmt_c99 @ 00423470 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c99(ulong opw,long *tok)

{
  *tok = 0x3e;
  return 1;
}


/* ==== dis_fmt_c100 @ 00423480 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c100(ulong opw,long *tok)

{
  *tok = 0x2e;
  return 1;
}


/* ==== dis_fmt_c104 @ 00423490 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c104(ulong opw,long *tok)

{
  *tok = 0x3a;
  return 1;
}


/* ==== dis_fmt_c107 @ 004234a0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c107(ulong opw,long *tok)

{
  *tok = 0x28;
  return 1;
}


/* ==== dis_fmt_c106 @ 004234b0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c106(ulong opw,long *tok)

{
  *tok = 0x32;
  return 1;
}


/* ==== dis_fmt_c101 @ 004234c0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c101(ulong opw,long *tok)

{
  *tok = 0x33;
  return 1;
}


/* ==== dis_fmt_c68 @ 004234d0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_c68(ulong opw,long *tok)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  long *tok_00;
  uint uVar4;
  uint uVar5;
  
  uVar4 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  bVar2 = false;
  uVar5 = uVar4 & 0x3f;
  if ((uVar5 == 0x34) || (uVar5 == 0x30)) {
    bVar2 = true;
  }
  if (((opw & 0x80) != 0) || (*(int *)(&DAT_004c0cf0 + (opw & 0x7f) * 4) != 0)) {
    if ((opw & 0xf4008) == 0x80000) {
      bVar2 = true;
    }
    if ((opw & 0xf4008) == 0x90008) {
      bVar2 = true;
    }
  }
  tok_00 = tok;
  if (bVar2) {
    *tok = 0x3f;
    tok_00 = tok + 1;
  }
  iVar3 = dis_ea_tokens(opw,tok_00);
  piVar1 = tok_00 + iVar3;
  iVar3 = ((uVar4 & 0xffff) >> 8 & 1) + 0x62;
  *piVar1 = iVar3;
  piVar1[1] = 0x99;
  piVar1[2] = 0xf6;
  piVar1[3] = uVar5 + 0xb0;
  piVar1[4] = 0x9a;
  piVar1[5] = 0x58;
  piVar1[6] = 0x99;
  piVar1[7] = iVar3;
  dis_sel_b = uVar5 | 0x8000;
  _dis_effect_flags = 2;
  return (int)piVar1 + (0x20 - (int)tok) >> 2;
}


/* ==== dis_fmt_c63 @ 004235d0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c63(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_c68(opw,tok);
  return iVar1;
}


/* ==== dis_fmt_c64 @ 004235f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_c64(ulong opw,long *tok)

{
  bool bVar1;
  int iVar2;
  long *plVar3;
  uint uVar4;
  uint uVar5;
  
  uVar4 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  bVar1 = false;
  uVar5 = uVar4 & 0x3f;
  if ((uVar5 == 0x34) || (uVar5 == 0x30)) {
    bVar1 = true;
  }
  if (((opw & 0x80) != 0) || (*(int *)(&DAT_004c0cf0 + (opw & 0x7f) * 4) != 0)) {
    if ((opw & 0xf4008) == 0x80000) {
      bVar1 = true;
    }
    if ((opw & 0xf4008) == 0x90008) {
      bVar1 = true;
    }
  }
  plVar3 = tok;
  if (bVar1) {
    *tok = 0x3f;
    plVar3 = tok + 1;
  }
  iVar2 = dis_ea_tokens(opw,plVar3);
  plVar3 = plVar3 + iVar2;
  *plVar3 = 0x5a;
  plVar3[1] = 0x99;
  iVar2 = ((uVar4 & 0xffff) >> 8 & 1) + 0x62;
  plVar3[2] = iVar2;
  plVar3[3] = 0x9a;
  plVar3[4] = iVar2;
  plVar3[5] = 0x99;
  plVar3[6] = 0xf7;
  plVar3[7] = uVar5 + 0xb0;
  dis_sel_c = uVar5 | 0x8000;
  _dis_effect_flags = 4;
  return (int)plVar3 + (0x20 - (int)tok) >> 2;
}


/* ==== dis_fmt_c62 @ 004236f0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c62(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_c64(opw,tok);
  return iVar1;
}


/* ==== dis_fmt_c30 @ 00423710 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c30(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h423730(opw,tok,0x1c);
  return iVar1;
}


/* ==== dis_fmt_h423730 @ 00423730 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dis_fmt_h423730(ulong opw,long *tok)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  long in_stack_0000000c;
  
  uVar1 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  if ((uVar1 & 0x3f) < 4) {
    iVar3 = 0x35;
  }
  else {
    uVar2 = uVar1 & 0x38;
    if (uVar2 == 0x28) {
      iVar3 = 0x35;
    }
    else if (uVar2 == 0x30) {
      iVar3 = 0x35;
    }
    else if (uVar2 == 0x38) {
      iVar3 = (uVar1 & 0x2f) - 3;
    }
    else {
      iVar3 = (uVar1 & 0x3f) - 3;
    }
  }
  *tok = in_stack_0000000c;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,&dis_hex_ea);
    tok[3] = -2;
  }
  else {
    tok[3] = 0x3f;
  }
  tok[4] = 0x99;
  tok[5] = iVar3 + 0x57;
  tok[6] = 0x99;
  tok[7] = -4;
  dis_sel_a = 0x2000;
  _dis_effect_flags = 1;
  return 8;
}


/* ==== dis_fmt_c31 @ 00423820 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c31(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h423730(opw,tok,0x19);
  return iVar1;
}


/* ==== dis_fmt_c48 @ 00423840 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c48(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h423730(opw,tok,0x1a);
  return iVar1;
}


/* ==== dis_fmt_c49 @ 00423860 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c49(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h423730(opw,tok,0x16);
  return iVar1;
}


/* ==== dis_fmt_c28 @ 00423880 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c28(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4238a0(opw,tok,0xd);
  return iVar1;
}


/* ==== dis_fmt_h4238a0 @ 004238a0 ==== */

int __cdecl dis_fmt_h4238a0(ulong opw,long *tok)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  long in_stack_0000000c;
  
  uVar1 = (int)(opw + ((int)opw >> 0x1f & 0xffU)) >> 8;
  if ((uVar1 & 0x3f) < 4) {
    iVar3 = 0x35;
  }
  else {
    uVar2 = uVar1 & 0x38;
    if (uVar2 == 0x28) {
      iVar3 = 0x35;
    }
    else if (uVar2 == 0x30) {
      iVar3 = 0x35;
    }
    else if (uVar2 == 0x38) {
      iVar3 = (uVar1 & 0x2f) - 3;
    }
    else {
      iVar3 = (uVar1 & 0x3f) - 3;
    }
  }
  *tok = in_stack_0000000c;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,&dis_hex_ea);
    tok[3] = -2;
  }
  else {
    tok[3] = 0x3f;
  }
  tok[4] = 0x99;
  tok[5] = iVar3 + 0x57;
  return 6;
}


/* ==== dis_fmt_c29 @ 00423960 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c29(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4238a0(opw,tok,10);
  return iVar1;
}


/* ==== dis_fmt_c46 @ 00423980 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c46(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4238a0(opw,tok,0xc);
  return iVar1;
}


/* ==== dis_fmt_c47 @ 004239a0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c47(ulong opw,long *tok)

{
  int iVar1;
  
  iVar1 = dis_fmt_h4238a0(opw,tok,0xb);
  return iVar1;
}


/* ==== dis_fmt_c93 @ 004239c0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c93(ulong opw,long *tok)

{
  int *piVar1;
  
  *tok = 0x43;
  piVar1 = tok + 1;
  if ((opw & 0x100) != 0) {
    *piVar1 = (opw & 0xf) + 0x47;
    piVar1 = tok + 2;
  }
  *piVar1 = 0x9a;
  return (int)piVar1 + (4 - (int)tok) >> 2;
}


/* ==== dis_fmt_c105 @ 004239f0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c105(ulong opw,long *tok)

{
  *tok = 0x40;
  return 1;
}


/* ==== dis_fmt_c102 @ 00423a00 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c102(ulong opw,long *tok)

{
  *tok = ((opw & 2) != 0) + 0x41;
  tok[1] = 0x9a;
  tok[2] = (opw & 1) + 0x62;
  return 3;
}


/* ==== dis_fmt_c109 @ 00423a40 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int dis_fmt_c109(ulong opw,long *tok)

{
  uint uVar1;
  int iVar2;
  
  *tok = *(long *)(&DAT_004c1268 + (opw & 3) * 4);
  tok[1] = 0x9a;
  uVar1 = (int)opw >> 4 & 3;
  if ((opw & 4) == 0) {
    iVar2 = *(int *)(&DAT_004c1278 + uVar1 * 4);
  }
  else {
    iVar2 = *(int *)(&DAT_004c1288 + uVar1 * 4);
  }
  tok[2] = iVar2 + 0x57;
  tok[3] = 0x99;
  tok[4] = 0xf2;
  fmt_hex_dollar((int)opw >> 8 & 0x1f,&dis_hex_ea);
  tok[5] = -2;
  tok[6] = 0x99;
  tok[7] = (opw >> 3 & 1) + 0x62;
  return 8;
}


/* ==== hid_423ae0 @ 00423ae0 ==== */

void hid_423ae0(ulong *param_1,char *param_2,long param_3,long param_4,void *param_5)

{
  dis_cpu_level = 8;
  disassemble(param_1,param_2,param_3,param_4,param_5);
  return;
}


