/* disfmt.c - disassembler formatters: one per opcode class, each builds the token list of the
 * instruction text and sets the effective-address state (dis_effect_flags, dis_sel_*, dis_val_*)
 * (SIM56000.EXE 6.3.0, module disfmt 0x41fb70-0x423ae0, plus dis_fmt_h41fb60 in front of it).
 * Mechanically converted from the Ghidra export by re/scripts/g2c_dis.py; verified against the
 * original by tests/sim56000/emu/diff_disfmt.py.  Token ids: see dis_token_strings; 0x3f "U" prefix,
 * 0x99 ",", 0x9a " ", negative ids are pseudo tokens (-2 hex of dis_hex_ea, -3 dis_hex_b, ...). */
#include "sim56000.h"

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wparentheses"
#endif

/* token words are 32-bit signed in the original */
static long S32(unsigned long v)
{
    v &= MASK32;
    if (v & 0x80000000UL)
        return -(long)((~v & MASK32) + 1UL);
    return (long)v;
}

long dis_fmt_h41fb60(unsigned long opw, long *tok)
{
    tok[0] = 0x3f;
    return 1;
}

long dis_fmt_h4212a0(unsigned long opw, long *tok, long sel);
long dis_fmt_h4213c0(unsigned long opw, long *tok, long sel);
long dis_fmt_h4214e0(unsigned long opw, long *tok, long sel);
long dis_fmt_h421670(unsigned long opw, long *tok, long sel);
long dis_fmt_h4217f0(unsigned long opw, long *tok, long sel);
long dis_fmt_h421970(unsigned long opw, long *tok, long sel);
long dis_fmt_h421ae0(unsigned long opw, long *tok, long sel);
long dis_fmt_h421c50(unsigned long opw, long *tok, long sel);
long dis_fmt_h423730(unsigned long opw, long *tok, long sel);
long dis_fmt_h4238a0(unsigned long opw, long *tok, long sel);

/* dis_fmt_c0 @ 0041fb70 */
long dis_fmt_c0(unsigned long opw,long *tok)
{
  long *piVar1;
  long bVar2;
  long iVar3;
  unsigned long uVar4;
  unsigned long uVar5;
  unsigned long uVar6;
  unsigned long uVar7;
  long *tok_00;
  unsigned long uVar8;
  
  bVar2 = 0;
  uVar6 = (opw >> 8);
  uVar7 = uVar6 & 0xffff;
  if (((uVar6 & 0xcf80) == 0xcf80) || ((uVar6 & 0xcf80) == 0xca80)) {
    bVar2 = 1;
  }
  if ((((opw & 0x80) != 0) || (d_4c0cf0[((opw & 0x7f))] != 0)) &&
     ((((((uVar6 & 0x8c80) == 0x8c80 && (((unsigned char)opw & 8) == 8)) ||
        (((uVar6 & 0xc300) == 0xc300 && (((unsigned char)opw & 8) == 8)))) ||
       (((uVar6 & 0x8c80) == 0x8880 && ((opw & 8) == 0)))) ||
      (((uVar6 & 0xc300) == 0xc200 && ((opw & 8) == 0)))))) {
    bVar2 = 1;
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
  dis_effect_flags = 6;
  dis_sel_b = uVar4 | 0x8000;
  if ((uVar6 & 0x80) == 0) {
    *piVar1 = S32(uVar5 + 0x91);
    piVar1[1] = 0x99;
    piVar1[2] = 0xf6;
    piVar1[3] = S32(uVar4 + 0xb0);
  }
  else {
    *piVar1 = 0xf6;
    piVar1[1] = S32(uVar4 + 0xb0);
    piVar1[2] = 0x99;
    piVar1[3] = S32(uVar5 + 0x91);
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
  dis_sel_c = (((0x80) << 8) | ((uVar7) & 0xff));
  if ((uVar6 & 0x4000) != 0) {
    piVar1[5] = 0xf7;
    piVar1[6] = S32(uVar7 + 0xb0);
    piVar1[7] = 0x99;
    piVar1[8] = S32(uVar8 + 0x95);
    return (long)(piVar1 - tok) + 9;
  }
  piVar1[5] = S32(uVar8 + 0x95);
  piVar1[6] = 0x99;
  piVar1[7] = 0xf7;
  piVar1[8] = S32(uVar7 + 0xb0);
  return (long)(piVar1 - tok) + 9;
}

/* dis_fmt_c1 @ 0041fd70 */
long dis_fmt_c1(unsigned long opw,long *tok)
{
  long iVar1;
  long *piVar2;
  long *piVar3;
  unsigned long uVar4;
  unsigned long uVar5;
  unsigned long uVar6;
  unsigned long uVar7;
  
  uVar6 = (opw >> 8);
  iVar1 = dis_ea_tokens(opw,tok);
  uVar4 = uVar6 & 0x3f;
  uVar7 = (uVar6 & 0xffff) >> 8 & 7;
  uVar5 = (uVar6 & 0x800 | 0x23000) >> 0xb;
  piVar2 = tok + iVar1;
  if ((uVar4 == 0x34) || (opw = 0, uVar4 == 0x30)) {
    opw = 0xfffffffc;
  }
  if (uVar4 == 0x34) {
    dis_effect_flags = 0;
  }
  else {
    dis_effect_flags = (-(uVar5 != 0x47) & 0xfffffffe) + 4;
  }
  dis_sel_b = uVar4 | 0x8000;
  dis_sel_c = dis_sel_b;
  if ((uVar6 & 0x80) != 0) {
    if (uVar4 != 0x34) {
      *piVar2 = S32(uVar5 + 0xb0);
      piVar2 = piVar2 + 1;
    }
    *piVar2 = S32(uVar4 + 0xb0);
    piVar2[1] = S32(opw);
    piVar2[2] = 0x99;
    piVar2[3] = S32(uVar7 + 0x6c);
    return (long)(piVar2 - tok) + 4;
  }
  *piVar2 = S32(uVar7 + 0x6c);
  piVar2[1] = 0x99;
  piVar3 = piVar2 + 2;
  if (uVar4 != 0x34) {
    *piVar3 = S32(uVar5 + 0xb0);
    piVar3 = piVar2 + 3;
    if (uVar4 != 0x34) {
      *piVar3 = S32(uVar4 + 0xb0);
      piVar2[4] = S32(opw);
      return (long)(piVar2 - tok) + 5;
    }
  }
  *piVar3 = 0x3f;
  return (long)(piVar3 - tok) + 1;
}

/* dis_fmt_c2 @ 0041feb0 */
long dis_fmt_c2(unsigned long opw,long *tok)
{
  long *piVar1;
  long iVar2;
  unsigned long uVar3;
  unsigned long uVar4;
  unsigned long uVar5;
  unsigned long v;
  
  uVar4 = (opw >> 8);
  v = uVar4 & 0x3f;
  fmt_hex_dollar(v,dis_hex_ea);
  uVar5 = (uVar4 & 0xffff) >> 8 & 7;
  iVar2 = dis_ea_tokens(opw,tok);
  uVar3 = (uVar4 & 0x800 | 0x23000) >> 0xb;
  piVar1 = tok + iVar2;
  dis_effect_flags = (-(uVar3 != 0x47) & 0xfffffffe) + 4;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  dis_val_b = v;
  dis_val_c = v;
  if ((uVar4 & 0x80) != 0) {
    *piVar1 = S32(uVar3 + 0xb0);
    piVar1[1] = 0xf0;
    piVar1[2] = -2;
    piVar1[3] = 0x99;
    piVar1[4] = S32(uVar5 + 0x6c);
    return (long)(piVar1 - tok) + 5;
  }
  *piVar1 = S32(uVar5 + 0x6c);
  piVar1[1] = 0x99;
  piVar1[2] = S32(uVar3 + 0xb0);
  piVar1[3] = 0xf0;
  piVar1[4] = -2;
  return (long)(piVar1 - tok) + 5;
}

/* dis_fmt_c3 @ 0041ffc0 */
long dis_fmt_c3(unsigned long opw,long *tok)
{
  long iVar1;
  long *piVar2;
  long *piVar3;
  unsigned long uVar4;
  unsigned long uVar5;
  unsigned long uVar6;
  unsigned long uVar7;
  
  uVar6 = (opw >> 8);
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
    dis_effect_flags = 0;
  }
  else {
    dis_effect_flags = (-(uVar5 != 0x46) & 2) + 2;
  }
  dis_sel_b = uVar4 | 0x8000;
  dis_sel_c = dis_sel_b;
  if ((uVar6 & 0x80) != 0) {
    if (uVar4 != 0x34) {
      *piVar2 = S32(uVar5 + 0xb0);
      piVar2 = piVar2 + 1;
    }
    *piVar2 = S32(uVar4 + 0xb0);
    piVar2[1] = S32(iVar1);
    piVar2[2] = 0x99;
    piVar2[3] = S32(uVar7 + 100);
    return (long)(piVar2 - tok) + 4;
  }
  *piVar2 = S32(uVar7 + 100);
  piVar2[1] = 0x99;
  piVar3 = piVar2 + 2;
  if (uVar4 != 0x34) {
    *piVar3 = S32(uVar5 + 0xb0);
    piVar3 = piVar2 + 3;
    if (uVar4 != 0x34) {
      *piVar3 = S32(uVar4 + 0xb0);
      piVar2[4] = S32(iVar1);
      return (long)(piVar2 - tok) + 5;
    }
  }
  *piVar3 = 0x3f;
  return (long)(piVar3 - tok) + 1;
}

/* dis_fmt_c4 @ 00420100 */
long dis_fmt_c4(unsigned long opw,long *tok)
{
  long *piVar1;
  long iVar2;
  unsigned long uVar3;
  unsigned long uVar4;
  unsigned long uVar5;
  unsigned long v;
  
  uVar4 = (opw >> 8);
  v = uVar4 & 0x3f;
  fmt_hex_dollar(v,dis_hex_ea);
  uVar5 = (uVar4 & 0xffff) >> 8 & 7;
  iVar2 = dis_ea_tokens(opw,tok);
  uVar3 = (uVar4 & 0x800 | 0x23000) >> 0xb;
  piVar1 = tok + iVar2;
  dis_effect_flags = (-(uVar3 != 0x47) & 0xfffffffe) + 4;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  dis_val_b = v;
  dis_val_c = v;
  if ((uVar4 & 0x80) != 0) {
    *piVar1 = S32(uVar3 + 0xb0);
    piVar1[1] = 0xf0;
    piVar1[2] = -2;
    piVar1[3] = 0x99;
    piVar1[4] = S32(uVar5 + 100);
    return (long)(piVar1 - tok) + 5;
  }
  *piVar1 = S32(uVar5 + 100);
  piVar1[1] = 0x99;
  piVar1[2] = S32(uVar3 + 0xb0);
  piVar1[3] = 0xf0;
  piVar1[4] = -2;
  return (long)(piVar1 - tok) + 5;
}

/* dis_fmt_c5 @ 00420210 */
long dis_fmt_c5(unsigned long opw,long *tok)
{
  long bVar1;
  long iVar2;
  long *piVar3;
  long *piVar4;
  unsigned long uVar5;
  unsigned long uVar6;
  unsigned long uVar7;
  long *tok_00;
  unsigned long uVar8;
  
  bVar1 = 0;
  uVar7 = (opw >> 8);
  if (((opw & 0x80) == 0) && (d_4c0cf0[((opw & 0x7f))] == 0)) goto LAB_004202b1;
  iVar2 = pm_is_short_ea(opw);
  if (iVar2 == 0) {
    if (((uVar7 & 0xf180) != 0x5180) || (((unsigned char)opw & 8) != 8)) {
      if ((uVar7 & 0xf180) != 0x5080) goto LAB_004202b1;
      goto joined_r0x004202aa;
    }
  }
  else if (((uVar7 & 0xf580) != 0x5580) || (((unsigned char)opw & 8) != 8)) {
    if ((uVar7 & 0xf580) != 0x5480) goto LAB_004202b1;
joined_r0x004202aa:
    if ((opw & 8) != 0) goto LAB_004202b1;
  }
  bVar1 = 1;
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
    dis_effect_flags = 0;
  }
  else {
    dis_effect_flags = (-(uVar6 != 0x46) & 2) + 2;
  }
  dis_sel_b = uVar5 | 0x8000;
  dis_sel_c = dis_sel_b;
  if ((uVar7 & 0x80) == 0) {
    *piVar3 = S32(uVar8 + 0x5c);
    piVar3[1] = 0x99;
    piVar4 = piVar3 + 2;
    if (uVar5 != 0x34) {
      *piVar4 = S32(uVar6 + 0xb0);
      piVar4 = piVar3 + 3;
      if (uVar5 != 0x34) {
        *piVar4 = S32(uVar5 + 0xb0);
        piVar3[4] = S32(iVar2);
        return (long)(piVar3 - tok) + 5;
      }
    }
    *piVar4 = 0x3f;
    return (long)(piVar4 - tok) + 1;
  }
  if (uVar5 != 0x34) {
    *piVar3 = S32(uVar6 + 0xb0);
    piVar3 = piVar3 + 1;
  }
  *piVar3 = S32(uVar5 + 0xb0);
  piVar3[1] = S32(iVar2);
  piVar3[2] = 0x99;
  piVar3[3] = S32(uVar8 + 0x5c);
  return (long)(piVar3 - tok) + 4;
}

/* pm_is_short_ea @ 004203e0 */
long pm_is_short_ea(unsigned long opw)
{
  if (((opw & 0x80) == 0) && (d_4c0ef0[((opw & 0x7f))] != 0)) {
    return 1;
  }
  return 0;
}

/* dis_fmt_c6 @ 00420400 */
long dis_fmt_c6(unsigned long opw,long *tok)
{
  long *piVar1;
  long bVar2;
  long iVar3;
  unsigned long uVar4;
  unsigned long uVar5;
  long *tok_00;
  unsigned long uVar6;
  unsigned long v;
  
  uVar5 = (opw >> 8);
  bVar2 = 0;
  if (((opw & 0x80) == 0) && (d_4c0cf0[((opw & 0x7f))] == 0)) goto LAB_004204a2;
  iVar3 = pm_is_short_ea(opw);
  if (iVar3 == 0) {
    if (((uVar5 & 0xf180) != 0x5180) || (((unsigned char)opw & 8) != 8)) {
      if ((uVar5 & 0xf180) != 0x5080) goto LAB_004204a2;
      goto joined_r0x0042049b;
    }
  }
  else if (((uVar5 & 0xf580) != 0x5580) || (((unsigned char)opw & 8) != 8)) {
    if ((uVar5 & 0xf580) != 0x5480) goto LAB_004204a2;
joined_r0x0042049b:
    if ((opw & 8) != 0) goto LAB_004204a2;
  }
  bVar2 = 1;
LAB_004204a2:
  tok_00 = tok;
  if (bVar2) {
    *tok = 0x3f;
    tok_00 = tok + 1;
  }
  v = uVar5 & 0x3f;
  fmt_hex_dollar(v,dis_hex_ea);
  uVar6 = (uVar5 & 0xffff) >> 8 & 7;
  iVar3 = dis_ea_tokens(opw,tok_00);
  piVar1 = tok_00 + iVar3;
  uVar4 = (uVar5 & 0x800 | 0x23000) >> 0xb;
  dis_effect_flags = (-(uVar4 != 0x47) & 0xfffffffe) + 4;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  dis_val_b = v;
  dis_val_c = v;
  if ((uVar5 & 0x80) == 0) {
    *piVar1 = S32(uVar6 + 0x5c);
    piVar1[1] = 0x99;
    piVar1[2] = S32(uVar4 + 0xb0);
    piVar1[3] = 0xf0;
    piVar1[4] = -2;
    return (long)(piVar1 - tok) + 5;
  }
  *piVar1 = S32(uVar4 + 0xb0);
  piVar1[1] = 0xf0;
  piVar1[2] = -2;
  piVar1[3] = 0x99;
  piVar1[4] = S32(uVar6 + 0x5c);
  return (long)(piVar1 - tok) + 5;
}

/* dis_fmt_c7 @ 004205b0 */
long dis_fmt_c7(unsigned long opw,long *tok)
{
  long iVar1;
  long *piVar2;
  long *piVar3;
  unsigned long uVar4;
  unsigned long uVar5;
  unsigned long uVar6;
  unsigned long uVar7;
  
  uVar6 = (opw >> 8);
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
    dis_effect_flags = 0;
  }
  else {
    dis_effect_flags = (-(uVar5 != 0x46) & 2) + 2;
  }
  dis_sel_b = uVar4 | 0x8000;
  uVar7 = (uVar6 & 0xffff) >> 8 & 3;
  dis_sel_c = dis_sel_b;
  if ((uVar6 & 0x80) != 0) {
    if (uVar4 != 0x34) {
      *piVar2 = S32(uVar5 + 0xb0);
      piVar2 = piVar2 + 1;
    }
    *piVar2 = S32(uVar4 + 0xb0);
    piVar2[1] = S32(iVar1);
    piVar2[2] = 0x99;
    piVar2[3] = S32(uVar7 + 0x58);
    return (long)(piVar2 - tok) + 4;
  }
  *piVar2 = S32(uVar7 + 0x58);
  piVar2[1] = 0x99;
  piVar3 = piVar2 + 2;
  if (uVar4 != 0x34) {
    *piVar3 = S32(uVar5 + 0xb0);
    piVar3 = piVar2 + 3;
    if (uVar4 != 0x34) {
      *piVar3 = S32(uVar4 + 0xb0);
      piVar2[4] = S32(iVar1);
      return (long)(piVar2 - tok) + 5;
    }
  }
  *piVar3 = 0x3f;
  return (long)(piVar3 - tok) + 1;
}

/* dis_fmt_c8 @ 004206e0 */
long dis_fmt_c8(unsigned long opw,long *tok)
{
  long *piVar1;
  long iVar2;
  unsigned long uVar3;
  unsigned long uVar4;
  unsigned long uVar5;
  unsigned long v;
  
  uVar4 = (opw >> 8);
  v = uVar4 & 0x3f;
  fmt_hex_dollar(v,dis_hex_ea);
  uVar5 = (uVar4 & 0xffff) >> 8 & 3;
  iVar2 = dis_ea_tokens(opw,tok);
  uVar3 = (uVar4 & 0x800 | 0x23000) >> 0xb;
  piVar1 = tok + iVar2;
  dis_effect_flags = (-(uVar3 != 0x47) & 0xfffffffe) + 4;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  dis_val_b = v;
  dis_val_c = v;
  if ((uVar4 & 0x80) != 0) {
    *piVar1 = S32(uVar3 + 0xb0);
    piVar1[1] = 0xf0;
    piVar1[2] = -2;
    piVar1[3] = 0x99;
    piVar1[4] = S32(uVar5 + 0x58);
    return (long)(piVar1 - tok) + 5;
  }
  *piVar1 = S32(uVar5 + 0x58);
  piVar1[1] = 0x99;
  piVar1[2] = S32(uVar3 + 0xb0);
  piVar1[3] = 0xf0;
  piVar1[4] = -2;
  return (long)(piVar1 - tok) + 5;
}

/* dis_fmt_c9 @ 004207f0 */
long dis_fmt_c9(unsigned long opw,long *tok)
{
  long bVar1;
  long iVar2;
  long *plVar3;
  unsigned long uVar4;
  unsigned long uVar5;
  unsigned long uVar6;
  unsigned long uVar7;
  
  bVar1 = 0;
  uVar5 = (opw >> 8);
  if ((((opw & 0x80) != 0) || (d_4c0cf0[((opw & 0x7f))] != 0)) &&
     (((uVar6 = uVar5 & 0xff80, uVar6 == 0x4b80 || (uVar6 == 0x4a80)) ||
      ((((uVar6 == 0x4180 && (((unsigned char)opw & 8) == 8)) || ((uVar6 == 0x4080 && ((opw & 8) == 0)))) ||
       (((uVar6 == 0x4980 && (((unsigned char)opw & 8) == 8)) || ((uVar6 == 0x4880 && ((opw & 8) == 0))))))))
     )) {
    bVar1 = 1;
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
  dis_effect_flags = -(uVar6 != 0x34) & 8;
  dis_sel_b = uVar6 | 0x8000;
  uVar7 = ((uVar5 & 0xffff) >> 1 & 0x400 | uVar5 & 0x300) >> 8;
  if ((uVar5 & 0x80) != 0) {
    *plVar3 = 0xf8;
    plVar3[1] = S32(uVar6 + 0xb0);
    plVar3[2] = S32(uVar4);
    plVar3[3] = 0x99;
    plVar3[4] = S32(uVar7 + 0x84);
    return (long)(plVar3 - tok) + 5;
  }
  *plVar3 = S32(uVar7 + 0x84);
  plVar3[1] = 0x99;
  plVar3[2] = 0xf8;
  plVar3[3] = S32(uVar6 + 0xb0);
  plVar3[4] = S32(uVar4);
  return (long)(plVar3 - tok) + 5;
}

/* dis_fmt_c10 @ 00420980 */
long dis_fmt_c10(unsigned long opw,long *tok)
{
  long bVar1;
  long iVar2;
  unsigned long uVar3;
  long *plVar4;
  unsigned long uVar5;
  unsigned long v;
  
  uVar3 = (opw >> 8);
  bVar1 = 0;
  if ((((opw & 0x80) != 0) || (d_4c0cf0[((opw & 0x7f))] != 0)) &&
     (((uVar5 = uVar3 & 0xff80, uVar5 == 0x4b80 || (uVar5 == 0x4a80)) ||
      ((((uVar5 == 0x4180 && (((unsigned char)opw & 8) == 8)) || ((uVar5 == 0x4080 && ((opw & 8) == 0)))) ||
       (((uVar5 == 0x4980 && (((unsigned char)opw & 8) == 8)) || ((uVar5 == 0x4880 && ((opw & 8) == 0))))))))
     )) {
    bVar1 = 1;
  }
  plVar4 = tok;
  if (bVar1) {
    *tok = 0x3f;
    plVar4 = tok + 1;
  }
  v = uVar3 & 0x3f;
  fmt_hex_dollar(v,dis_hex_ea);
  uVar5 = ((uVar3 & 0xffff) >> 1 & 0x400 | uVar3 & 0x300) >> 8;
  iVar2 = dis_ea_tokens(opw,plVar4);
  plVar4 = plVar4 + iVar2;
  dis_effect_flags = 8;
  dis_sel_b = 0x100;
  dis_val_b = v;
  if ((uVar3 & 0x80) != 0) {
    *plVar4 = 0xf8;
    plVar4[1] = 0xf0;
    plVar4[2] = -2;
    plVar4[3] = 0x99;
    plVar4[4] = S32(uVar5 + 0x84);
    return (long)(plVar4 - tok) + 5;
  }
  *plVar4 = S32(uVar5 + 0x84);
  plVar4[1] = 0x99;
  plVar4[2] = 0xf8;
  plVar4[3] = 0xf0;
  plVar4[4] = -2;
  return (long)(plVar4 - tok) + 5;
}

/* dis_fmt_c11 @ 00420b00 */
long dis_fmt_c11(unsigned long opw,long *tok)
{
  long *plVar1;
  long iVar2;
  unsigned long uVar3;
  
  uVar3 = (opw >> 8);
  fmt_hex_dollar(uVar3 & 0xff,dis_hex_ea);
  iVar2 = dis_ea_tokens(opw,tok);
  plVar1 = tok + iVar2;
  *plVar1 = 0xf2;
  plVar1[1] = -2;
  plVar1[2] = 0x99;
  plVar1[3] = S32(((uVar3 & 0xffff) >> 8 & 7) + 0x6c);
  return (long)((plVar1 + 3) - tok) + 1;
}

/* dis_fmt_c12 @ 00420b80 */
long dis_fmt_c12(unsigned long opw,long *tok)
{
  long *plVar1;
  long iVar2;
  unsigned long uVar3;
  
  uVar3 = (opw >> 8);
  fmt_hex_dollar(uVar3 & 0xff,dis_hex_ea);
  iVar2 = dis_ea_tokens(opw,tok);
  plVar1 = tok + iVar2;
  *plVar1 = 0xf2;
  plVar1[1] = -2;
  plVar1[2] = 0x99;
  plVar1[3] = S32(((uVar3 & 0xffff) >> 8 & 7) + 100);
  return (long)((plVar1 + 3) - tok) + 1;
}

/* dis_fmt_c13 @ 00420c00 */
long dis_fmt_c13(unsigned long opw,long *tok)
{
  long bVar1;
  long iVar2;
  unsigned long uVar3;
  long *plVar4;
  
  uVar3 = (opw >> 8);
  bVar1 = 0;
  if (((opw & 0x80) == 0) && (d_4c0cf0[((opw & 0x7f))] == 0)) goto LAB_00420ca0;
  iVar2 = pm_is_short_ea(opw);
  if (iVar2 == 0) {
    if (((uVar3 & 0xf900) != 0x2900) || (((unsigned char)opw & 8) != 8)) {
      if ((uVar3 & 0xf900) != 0x2800) goto LAB_00420ca0;
      goto joined_r0x00420c96;
    }
  }
  else if (((uVar3 & 0xfd00) != 0x2d00) || (((unsigned char)opw & 8) != 8)) {
    if ((uVar3 & 0xfd00) != 0x2c00) goto LAB_00420ca0;
joined_r0x00420c96:
    if ((opw & 8) != 0) goto LAB_00420ca0;
  }
  bVar1 = 1;
LAB_00420ca0:
  plVar4 = tok;
  if (bVar1) {
    *tok = 0x3f;
    plVar4 = tok + 1;
  }
  fmt_hex_dollar(uVar3 & 0xff,dis_hex_ea);
  iVar2 = dis_ea_tokens(opw,plVar4);
  plVar4 = plVar4 + iVar2;
  *plVar4 = 0xf2;
  plVar4[1] = -2;
  plVar4[2] = 0x99;
  plVar4[3] = S32(((uVar3 & 0xffff) >> 8 & 7) + 0x5c);
  return (long)(plVar4 - tok) + 4;
}

/* dis_fmt_c14 @ 00420d10 */
long dis_fmt_c14(unsigned long opw,long *tok)
{
  long *plVar1;
  long iVar2;
  unsigned long uVar3;
  
  uVar3 = (opw >> 8);
  fmt_hex_dollar(uVar3 & 0xff,dis_hex_ea);
  iVar2 = dis_ea_tokens(opw,tok);
  plVar1 = tok + iVar2;
  *plVar1 = 0xf2;
  plVar1[1] = -2;
  plVar1[2] = 0x99;
  plVar1[3] = S32(((uVar3 & 0xffff) >> 8 & 3) + 0x58);
  return (long)((plVar1 + 3) - tok) + 1;
}

/* dis_fmt_c15 @ 00420d90 */
long dis_fmt_c15(unsigned long opw,long *tok)
{
  long *piVar1;
  long bVar2;
  long iVar3;
  unsigned long uVar4;
  long iVar5;
  long *tok_00;
  
  uVar4 = (opw >> 8);
  bVar2 = 0;
  if (((opw & 0x80) == 0) && (d_4c0cf0[((opw & 0x7f))] == 0)) goto LAB_00420e30;
  iVar3 = pm_is_short_ea(opw);
  if (iVar3 == 0) {
    if (((uVar4 & 0xfc19) != 0x2009) || (((unsigned char)opw & 8) != 8)) {
      if ((uVar4 & 0xfc19) != 0x2008) goto LAB_00420e30;
      goto joined_r0x00420e26;
    }
  }
  else if (((uVar4 & 0xfc1d) != 0x200d) || (((unsigned char)opw & 8) != 8)) {
    if ((uVar4 & 0xfc1d) != 0x200c) goto LAB_00420e30;
joined_r0x00420e26:
    if ((opw & 8) != 0) goto LAB_00420e30;
  }
  bVar2 = 1;
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
  *piVar1 = S32(iVar5 + 0x57);
  piVar1[1] = 0x99;
  piVar1[2] = S32(iVar3 + 0x57);
  return (long)(piVar1 - tok) + 3;
}

/* dis_fmt_c18 @ 00420eb0 */
long dis_fmt_c18(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_ea_tokens(opw,tok);
  tok[iVar1] = ((opw >> 8) & 0x3fU) + 0xb0;
  return (long)((tok + iVar1) - tok) + 1;
}

/* dis_fmt_c19 @ 00420ef0 */
long dis_fmt_c19(unsigned long opw,long *tok)
{
  long iVar1;
  long *plVar2;
  
  iVar1 = dis_ea_tokens(opw,tok);
  plVar2 = tok + iVar1;
  if ((((opw >> 8) & 0xffffU) != 0x2000) || ((opw & 0xffff) == 0))
  {
    *plVar2 = 0x8c;
    plVar2 = plVar2 + 1;
  }
  return (long)(plVar2 - tok);
}

/* dis_fmt_c20 @ 00420f50 */
long dis_fmt_c20(unsigned long opw,long *tok)
{
  long bVar1;
  long iVar2;
  long *piVar3;
  unsigned long uVar4;
  unsigned long uVar5;
  unsigned long uVar6;
  long *plVar7;
  
  bVar1 = 0;
  uVar5 = (opw >> 8);
  uVar6 = uVar5 & 0xffff;
  if ((((opw & 0x80) != 0) || (d_4c0cf0[((opw & 0x7f))] != 0)) &&
     ((((uVar5 & 0xf3c0) == 0x13c0 && (((unsigned char)opw & 8) == 8)) ||
      (((uVar5 & 0xf3c0) == 0x12c0 && ((opw & 8) == 0)))))) {
    bVar1 = 1;
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
  *plVar7 = S32((uVar6 >> 0xb & 1) + 0x62);
  plVar7[1] = 0x99;
  plVar7[2] = S32((uVar6 >> 10 & 1) + 0x58);
  plVar7[3] = 0x9a;
  uVar6 = uVar6 >> 8 & 3;
  piVar3 = plVar7 + 4;
  dis_effect_flags = -(uVar4 != 0x34) & 4;
  dis_sel_c = uVar4 | 0x8000;
  if ((uVar5 & 0x80) != 0) {
    if (uVar4 != 0x34) {
      *piVar3 = 0xf7;
      piVar3 = plVar7 + 5;
    }
    *piVar3 = S32(uVar4 + 0xb0);
    piVar3[1] = S32(iVar2);
    piVar3[2] = 0x99;
    piVar3[3] = S32(uVar6 + 0x95);
    return (long)(piVar3 - tok) + 4;
  }
  *piVar3 = S32(uVar6 + 0x95);
  plVar7[5] = 0x99;
  piVar3 = plVar7 + 6;
  if (uVar4 != 0x34) {
    *piVar3 = 0xf7;
    piVar3 = plVar7 + 7;
    if (uVar4 != 0x34) {
      *piVar3 = S32(uVar4 + 0xb0);
      plVar7[8] = S32(iVar2);
      return (long)(plVar7 - tok) + 9;
    }
  }
  *piVar3 = 0x3f;
  return (long)(piVar3 - tok) + 1;
}

/* dis_fmt_c21 @ 004210f0 */
long dis_fmt_c21(unsigned long opw,long *tok)
{
  long bVar1;
  long iVar2;
  long *piVar3;
  long *puVar4;
  unsigned long uVar5;
  unsigned long uVar6;
  unsigned long uVar7;
  unsigned long uVar8;
  long *tok_00;
  
  bVar1 = 0;
  uVar7 = (opw >> 8);
  uVar8 = uVar7 & 0xffff;
  if ((((opw & 0x80) != 0) || (d_4c0cf0[((opw & 0x7f))] != 0)) &&
     ((((uVar7 & 0xfcc0) == 0x1c80 && (((unsigned char)opw & 8) == 8)) ||
      (((uVar7 & 0xfcc0) == 0x1880 && ((opw & 8) == 0)))))) {
    bVar1 = 1;
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
  dis_effect_flags = -(uVar5 != 0x34) & 2;
  dis_sel_b = uVar5 | 0x8000;
  if ((uVar7 & 0x80) == 0) {
    *piVar3 = S32(uVar6 + 0x91);
    piVar3[1] = 0x99;
    puVar4 = (piVar3 + 2);
    if (uVar5 != 0x34) {
      *puVar4 = 0xf6;
      puVar4 = (piVar3 + 3);
      if (uVar5 != 0x34) {
        *puVar4 = S32(uVar5 + 0xb0);
        puVar4 = (piVar3 + 4);
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
    *piVar3 = S32(uVar5 + 0xb0);
    piVar3[1] = S32(opw);
    piVar3[2] = 0x99;
    puVar4 = (piVar3 + 3);
    opw = uVar6 + 0x91;
LAB_00421242:
    *puVar4 = S32(opw);
  }
  puVar4[1] = 0x9a;
  puVar4[2] = S32((uVar8 >> 9 & 1) + 0x62);
  puVar4[3] = 0x99;
  puVar4[4] = S32((uVar8 >> 8 & 1) + 0x5a);
  return (long)(puVar4 - tok) + 5;
}

/* dis_fmt_c22 @ 00421280 */
long dis_fmt_c22(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4212a0(opw,tok,0x18);
  return iVar1;
}

/* dis_fmt_h4212a0 @ 004212a0 */
long dis_fmt_h4212a0(unsigned long opw,long *tok, long sel)
{
  long *piVar1;
  
  fmt_hex_dollar(opw & 0xfff,dis_hex_ea);
  *tok = S32(sel);
  piVar1 = tok + 1;
  if ((sel == 0x18) || (sel == 0x15)) {
    *piVar1 = S32((((opw >> 8) & 0xffffU) >> 4 & 0xf) + 0x47);
    piVar1 = tok + 2;
  }
  *piVar1 = 0x9a;
  piVar1[1] = 0xf0;
  dis_sel_a = 0x100;
  dis_effect_flags = 1;
  dis_val_a = opw & 0xfff;
  piVar1[2] = -2;
  return (long)(piVar1 - tok) + 3;
}

/* dis_fmt_c23 @ 00421340 */
long dis_fmt_c23(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4212a0(opw,tok,0x15);
  return iVar1;
}

/* dis_fmt_c24 @ 00421360 */
long dis_fmt_c24(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4212a0(opw,tok,0x1b);
  return iVar1;
}

/* dis_fmt_c25 @ 00421380 */
long dis_fmt_c25(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4212a0(opw,tok,0x17);
  return iVar1;
}

/* dis_fmt_c26 @ 004213a0 */
long dis_fmt_c26(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4213c0(opw,tok,0x18);
  return iVar1;
}

/* dis_fmt_h4213c0 @ 004213c0 */
long dis_fmt_h4213c0(unsigned long opw,long *tok, long sel)
{
  long *piVar1;
  unsigned long uVar2;
  
  *tok = S32(sel);
  piVar1 = tok + 1;
  if ((sel == 0x15) || (sel == 0x18)) {
    *piVar1 = S32((opw & 0xf) + 0x47);
    piVar1 = tok + 2;
  }
  *piVar1 = 0x9a;
  uVar2 = (opw >> 8) & 0x3f;
  if (uVar2 == 0x34) {
    piVar1[1] = 0x3f;
  }
  else {
    piVar1[1] = S32(uVar2 + 0xb0);
  }
  piVar1[2] = S32((uVar2 != 0x30) - 1 & 0xfffffffc);
  dis_effect_flags = 1;
  dis_sel_a = (((0x80) << 8) | ((uVar2) & 0xff));
  return (long)(piVar1 - tok) + 3;
}

/* dis_fmt_c44 @ 00421460 */
long dis_fmt_c44(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4213c0(opw,tok,0x15);
  return iVar1;
}

/* dis_fmt_c27 @ 00421480 */
long dis_fmt_c27(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4213c0(opw,tok,0x1b);
  return iVar1;
}

/* dis_fmt_c45 @ 004214a0 */
long dis_fmt_c45(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4213c0(opw,tok,0x17);
  return iVar1;
}

/* dis_fmt_c32 @ 004214c0 */
long dis_fmt_c32(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4214e0(opw,tok,0x1c);
  return iVar1;
}

/* dis_fmt_h4214e0 @ 004214e0 */
long dis_fmt_h4214e0(unsigned long opw,long *tok, long sel)
{
  unsigned long v;
  
  *tok = S32(sel);
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  v = (opw >> 8) & 0x3fU | 0xffc0;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,dis_hex_ea);
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
  fmt_hex_dollar(v,dis_hex_b);
  tok[7] = -3;
  tok[8] = 0x99;
  tok[9] = -4;
  dis_sel_c = 0x100;
  dis_sel_b = 0x100;
  dis_effect_flags = (-((opw & 0x40) != 0) & 2) + 3;
  dis_val_c = v;
  dis_val_b = v;
  dis_sel_a = 0x2000;
  return 10;
}

/* dis_fmt_c33 @ 004215f0 */
long dis_fmt_c33(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4214e0(opw,tok,0x19);
  return iVar1;
}

/* dis_fmt_c50 @ 00421610 */
long dis_fmt_c50(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4214e0(opw,tok,0x1a);
  return iVar1;
}

/* dis_fmt_c51 @ 00421630 */
long dis_fmt_c51(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4214e0(opw,tok,0x16);
  return iVar1;
}

/* dis_fmt_c36 @ 00421650 */
long dis_fmt_c36(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421670(opw,tok,0x1c);
  return iVar1;
}

/* dis_fmt_h421670 @ 00421670 */
long dis_fmt_h421670(unsigned long opw,long *tok, long sel)
{
  long *piVar1;
  unsigned long uVar2;
  
  *tok = S32(sel);
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,dis_hex_ea);
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
  uVar2 = (opw >> 8) & 0x3f;
  piVar1 = tok + 6;
  if ((uVar2 == 0x34) || (uVar2 == 0x30)) {
    *piVar1 = 0x3f;
  }
  else {
    *piVar1 = S32(uVar2 + 0xb0);
    tok[7] = 0x99;
    piVar1 = tok + 8;
    *piVar1 = -4;
  }
  dis_sel_a = 0x2000;
  dis_sel_c = uVar2 | 0x8000;
  dis_sel_b = uVar2 | 0x8000;
  dis_effect_flags = (-((opw & 0x40) != 0) & 2) + 3;
  return (long)(piVar1 - tok) + 1;
}

/* dis_fmt_c37 @ 00421770 */
long dis_fmt_c37(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421670(opw,tok,0x19);
  return iVar1;
}

/* dis_fmt_c54 @ 00421790 */
long dis_fmt_c54(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421670(opw,tok,0x1a);
  return iVar1;
}

/* dis_fmt_c55 @ 004217b0 */
long dis_fmt_c55(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421670(opw,tok,0x16);
  return iVar1;
}

/* dis_fmt_c40 @ 004217d0 */
long dis_fmt_c40(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4217f0(opw,tok,0x1c);
  return iVar1;
}

/* dis_fmt_h4217f0 @ 004217f0 */
long dis_fmt_h4217f0(unsigned long opw,long *tok, long sel)
{
  unsigned long v;
  
  *tok = S32(sel);
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  v = (opw >> 8) & 0x3f;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,dis_hex_ea);
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
  fmt_hex_dollar(v,dis_hex_b);
  tok[7] = -3;
  tok[8] = 0x99;
  tok[9] = -4;
  dis_sel_c = 0x100;
  dis_sel_b = 0x100;
  dis_effect_flags = (-((opw & 0x40) != 0) & 2) + 3;
  dis_val_c = v;
  dis_val_b = v;
  dis_sel_a = 0x2000;
  return 10;
}

/* dis_fmt_c41 @ 004218f0 */
long dis_fmt_c41(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4217f0(opw,tok,0x19);
  return iVar1;
}

/* dis_fmt_c58 @ 00421910 */
long dis_fmt_c58(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4217f0(opw,tok,0x1a);
  return iVar1;
}

/* dis_fmt_c59 @ 00421930 */
long dis_fmt_c59(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4217f0(opw,tok,0x16);
  return iVar1;
}

/* dis_fmt_c34 @ 00421950 */
long dis_fmt_c34(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421970(opw,tok,0xd);
  return iVar1;
}

/* dis_fmt_h421970 @ 00421970 */
long dis_fmt_h421970(unsigned long opw,long *tok, long sel)
{
  unsigned long v;
  
  *tok = S32(sel);
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  v = (opw >> 8) & 0x3fU | 0xffc0;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,dis_hex_ea);
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
  fmt_hex_dollar(v,dis_hex_b);
  tok[7] = -3;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  dis_effect_flags = (-((opw & 0x40) != 0) & 2) + 2;
  dis_val_c = v;
  dis_val_b = v;
  return 8;
}

/* dis_fmt_c35 @ 00421a60 */
long dis_fmt_c35(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421970(opw,tok,10);
  return iVar1;
}

/* dis_fmt_c52 @ 00421a80 */
long dis_fmt_c52(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421970(opw,tok,0xc);
  return iVar1;
}

/* dis_fmt_c53 @ 00421aa0 */
long dis_fmt_c53(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421970(opw,tok,0xb);
  return iVar1;
}

/* dis_fmt_c38 @ 00421ac0 */
long dis_fmt_c38(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421ae0(opw,tok,0xd);
  return iVar1;
}

/* dis_fmt_h421ae0 @ 00421ae0 */
long dis_fmt_h421ae0(unsigned long opw,long *tok, long sel)
{
  unsigned long uVar1;
  
  *tok = S32(sel);
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,dis_hex_ea);
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
  uVar1 = (opw >> 8) & 0x3f;
  if (uVar1 == 0x34) {
    tok[6] = 0x3f;
  }
  else {
    tok[6] = S32(uVar1 + 0xb0);
  }
  tok[7] = S32((uVar1 != 0x30) - 1 & 0xfffffffc);
  dis_effect_flags = (-((opw & 0x40) != 0) & 2) + 2;
  dis_sel_b = 0x8000;
  dis_sel_c = 0x8000;
  return 8;
}

/* dis_fmt_c39 @ 00421bd0 */
long dis_fmt_c39(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421ae0(opw,tok,10);
  return iVar1;
}

/* dis_fmt_c56 @ 00421bf0 */
long dis_fmt_c56(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421ae0(opw,tok,0xc);
  return iVar1;
}

/* dis_fmt_c57 @ 00421c10 */
long dis_fmt_c57(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421ae0(opw,tok,0xb);
  return iVar1;
}

/* dis_fmt_c42 @ 00421c30 */
long dis_fmt_c42(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421c50(opw,tok,0xd);
  return iVar1;
}

/* dis_fmt_h421c50 @ 00421c50 */
long dis_fmt_h421c50(unsigned long opw,long *tok, long sel)
{
  unsigned long v;
  
  *tok = S32(sel);
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  v = (opw >> 8) & 0x3f;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,dis_hex_ea);
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
  fmt_hex_dollar(v,dis_hex_b);
  tok[7] = -3;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  dis_effect_flags = (-((opw & 0x40) != 0) & 2) + 2;
  dis_val_c = v;
  dis_val_b = v;
  return 8;
}

/* dis_fmt_c43 @ 00421d30 */
long dis_fmt_c43(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421c50(opw,tok,10);
  return iVar1;
}

/* dis_fmt_c60 @ 00421d50 */
long dis_fmt_c60(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421c50(opw,tok,0xc);
  return iVar1;
}

/* dis_fmt_c61 @ 00421d70 */
long dis_fmt_c61(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h421c50(opw,tok,0xb);
  return iVar1;
}

/* dis_fmt_c65 @ 00421d90 */
long dis_fmt_c65(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  unsigned long v;
  long *puVar2;
  long *piVar3;
  unsigned long uVar4;
  unsigned long uVar5;
  unsigned long uVar6;
  unsigned long uVar7;
  
  uVar1 = opw;
  uVar4 = (opw >> 8);
  uVar5 = uVar4 & 0x3f;
  uVar7 = (opw & 0xff) >> 6 | 0x46;
  uVar6 = (uVar4 & 0x100 | 0x4600) >> 8;
  if ((uVar5 == 0x34) || (opw = 0, uVar5 == 0x30)) {
    opw = 0xfffffffc;
  }
  v = uVar1 & 0x3f | 0xffc0;
  fmt_hex_dollar(v,dis_hex_ea);
  *tok = 0x24;
  tok[1] = 0x9a;
  piVar3 = tok + 2;
  if ((uVar4 & 0x80) != 0) {
    if (uVar5 != 0x34) {
      *piVar3 = S32(uVar7 + 0xb0);
      piVar3 = tok + 3;
    }
    *piVar3 = S32(uVar5 + 0xb0);
    piVar3[1] = S32(opw);
    piVar3[2] = 0x99;
    piVar3[3] = S32(uVar6 + 0xb0);
    piVar3[4] = 0xf1;
    piVar3[5] = -2;
    puVar2 = (piVar3 + 6);
    if (uVar5 == 0x34) {
      dis_effect_flags = 0;
    }
    else {
      dis_effect_flags = (-(uVar7 != 0x47) & 0x10) + 0x10;
    }
    dis_effect_flags = (-(uVar6 != 0x47) & 0xfffffffe) + 4 | dis_effect_flags;
    goto LAB_00421f1a;
  }
  *piVar3 = S32(uVar6 + 0xb0);
  tok[3] = 0xf1;
  tok[4] = -2;
  tok[5] = 0x99;
  puVar2 = (tok + 6);
  if (uVar5 == 0x34) {
LAB_00421e65:
    *puVar2 = 0x3f;
  }
  else {
    *puVar2 = S32(uVar7 + 0xb0);
    puVar2 = (tok + 7);
    if (uVar5 == 0x34) goto LAB_00421e65;
    *puVar2 = S32(uVar5 + 0xb0);
    puVar2 = (tok + 8);
    *puVar2 = S32(opw);
  }
  puVar2 = puVar2 + 1;
  dis_effect_flags =
       (-(uVar7 != 0x47) & 0x10) + 0x10 | (-(uVar6 != 0x47) & 0xfffffffe) + 4;
LAB_00421f1a:
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  dis_sel_e = uVar5 | 0x8000;
  dis_sel_d = uVar5 | 0x8000;
  dis_val_c = v;
  dis_val_b = v;
  return (long)(puVar2 - tok);
}

/* dis_fmt_c66 @ 00421f60 */
long dis_fmt_c66(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  long *piVar2;
  long *puVar3;
  unsigned long v;
  unsigned long uVar4;
  unsigned long uVar5;
  unsigned long uVar6;
  
  uVar1 = opw;
  uVar4 = (opw >> 8);
  uVar6 = uVar4 & 0x3f;
  uVar5 = (uVar4 & 0x100 | 0x4600) >> 8;
  if ((uVar6 == 0x34) || (opw = 0, uVar6 == 0x30)) {
    opw = 0xfffffffc;
  }
  v = uVar1 & 0x3f | 0xffc0;
  fmt_hex_dollar(v,dis_hex_ea);
  *tok = 0x24;
  tok[1] = 0x9a;
  piVar2 = tok + 2;
  if ((uVar4 & 0x80) == 0) {
    *piVar2 = S32(uVar5 + 0xb0);
    tok[3] = 0xf1;
    tok[4] = -2;
    tok[5] = 0x99;
    puVar3 = (tok + 6);
    if (uVar6 != 0x34) {
      *puVar3 = 0xf9;
      puVar3 = (tok + 7);
      if (uVar6 != 0x34) {
        *puVar3 = S32(uVar6 + 0xb0);
        puVar3 = (tok + 8);
        *puVar3 = S32(opw);
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
    *piVar2 = S32(uVar6 + 0xb0);
    piVar2[1] = S32(opw);
    piVar2[2] = 0x99;
    piVar2[3] = S32(uVar5 + 0xb0);
    piVar2[4] = 0xf1;
    puVar3 = (piVar2 + 5);
    *puVar3 = 0xfffffffe;
  }
LAB_00422081:
  dis_val_c = v;
  dis_sel_a = uVar6 | 0x8000;
  dis_effect_flags = (-(uVar5 != 0x47) & 0xfffffffe) + 4 | (uVar6 != 0x34);
  dis_val_b = v;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  return (long)(puVar3 - tok) + 1;
}

/* dis_fmt_c67 @ 004220e0 */
long dis_fmt_c67(unsigned long opw,long *tok)
{
  unsigned long v;
  long iVar1;
  unsigned long uVar2;
  unsigned long uVar3;
  unsigned long uVar4;
  
  uVar3 = (opw >> 8);
  v = opw & 0x3f | 0xffc0;
  uVar4 = (uVar3 & 0x100 | 0x4600) >> 8;
  fmt_hex_dollar(v,dis_hex_ea);
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
    tok[2] = S32(uVar4 + 0xb0);
    tok[3] = 0xf1;
    tok[4] = -2;
    tok[5] = 0x99;
    tok[6] = S32(iVar1 + 0x57);
  }
  else {
    tok[2] = S32(iVar1 + 0x57);
    tok[3] = 0x99;
    tok[4] = S32(uVar4 + 0xb0);
    tok[5] = 0xf1;
    tok[6] = -2;
  }
  dis_val_c = v;
  dis_val_b = v;
  dis_effect_flags = (-(uVar4 != 0x47) & 0xfffffffe) + 4;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  return 7;
}

/* dis_fmt_c69 @ 00422220 */
long dis_fmt_c69(unsigned long opw,long *tok)
{
  long *plVar1;
  unsigned long uVar2;
  unsigned long uVar3;
  unsigned long uVar4;
  long iVar5;
  unsigned long uVar6;
  
  uVar3 = (long)(((long)opw >> 0x1f & 0xffU) + opw) >> 8;
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
    plVar1[2] = S32(iVar5 + 0x57);
    plVar1[3] = 0x99;
    plVar1[4] = 0xf9;
    plVar1[5] = S32(uVar2 + 0xb0);
    plVar1[6] = S32(uVar4);
  }
  else {
    plVar1[2] = 0xf9;
    plVar1[3] = S32(uVar2 + 0xb0);
    plVar1[4] = S32(uVar4);
    plVar1[5] = 0x99;
    plVar1[6] = S32(iVar5 + 0x57);
  }
  dis_effect_flags = 1;
  dis_sel_a = (((0x80) << 8) | ((uVar2) & 0xff));
  return (long)(plVar1 - tok) + 7;
}

/* dis_fmt_c70 @ 00422330 */
long dis_fmt_c70(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  unsigned long uVar2;
  long iVar3;
  unsigned long v;
  
  uVar2 = (opw >> 8);
  v = uVar2 & 0x3f;
  fmt_hex_dollar(v,dis_hex_ea);
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
    tok[2] = S32(iVar3 + 0x57);
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
    tok[6] = S32(iVar3 + 0x57);
  }
  dis_val_a = v;
  dis_effect_flags = 1;
  dis_sel_a = 0x100;
  return 7;
}

/* dis_fmt_c75 @ 00422440 */
long dis_fmt_c75(unsigned long opw,long *tok)
{
  fmt_hex_dollar((opw & 0xf) << 8 | (opw >> 8) & 0xffU,dis_hex_ea
                );
  *tok = 0x2d;
  tok[1] = 0x9a;
  tok[2] = 0xf3;
  tok[3] = -2;
  return 4;
}

/* dis_fmt_c71 @ 004224a0 */
long dis_fmt_c71(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  unsigned long uVar2;
  
  *tok = 0x2d;
  uVar1 = (opw >> 8);
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
    tok[2] = S32((uVar1 & 0x2f) + 0x54);
    return 3;
  }
  tok[2] = S32((uVar1 & 0x3f) + 0x54);
  return 3;
}

/* dis_fmt_c73 @ 00422560 */
long dis_fmt_c73(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  unsigned long uVar2;
  long *puVar3;
  
  *tok = 0x2d;
  tok[1] = 0x9a;
  uVar1 = (opw >> 8) & 0x3f;
  puVar3 = (tok + 2);
  uVar2 = (opw & 0xff) >> 6 | 0xf6;
  if ((uVar1 == 0x30) || (uVar1 == 0x34)) {
    *puVar3 = 0x3f;
  }
  else {
    *puVar3 = S32(uVar2);
    puVar3 = (tok + 3);
    *puVar3 = S32(uVar1 + 0xb0);
  }
  dis_sel_b = (((0x80) << 8) | ((uVar1) & 0xff));
  dis_sel_c = dis_sel_b;
  dis_effect_flags = (-(uVar2 != 0xf7) & 0xfffffffe) + 4;
  return (long)(puVar3 - tok) + 1;
}

/* dis_fmt_c77 @ 004225f0 */
long dis_fmt_c77(unsigned long opw,long *tok)
{
  unsigned long v;
  
  *tok = 0x2d;
  tok[1] = 0x9a;
  v = (opw >> 8) & 0x3f;
  if ((opw & 0x40) == 0) {
    tok[2] = 0xf6;
  }
  else {
    tok[2] = 0xf7;
  }
  tok[3] = 0xf0;
  fmt_hex_dollar(v,dis_hex_ea);
  tok[4] = -2;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  dis_effect_flags = (-((opw & 0x40) != 0) & 2) + 2;
  dis_val_c = v;
  dis_val_b = v;
  return 5;
}

/* dis_fmt_c76 @ 004226a0 */
long dis_fmt_c76(unsigned long opw,long *tok)
{
  fmt_hex_dollar((opw & 0xf) << 8 | (opw >> 8) & 0xffU,dis_hex_ea
                );
  *tok = 0x12;
  tok[1] = 0x9a;
  tok[2] = 0xf3;
  tok[3] = -2;
  tok[4] = 0x99;
  tok[5] = -5;
  dis_sel_a = 0x4000;
  dis_effect_flags = 1;
  return 6;
}

/* dis_fmt_c72 @ 00422730 */
long dis_fmt_c72(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  unsigned long uVar2;
  long iVar3;
  unsigned long uVar4;
  
  *tok = 0x12;
  uVar1 = (opw >> 8);
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
  tok[2] = S32(iVar3 + 0x57);
  tok[3] = 0x99;
  tok[4] = -5;
  dis_sel_a = 0x4000;
  dis_effect_flags = 1;
  return 5;
}

/* dis_fmt_c74 @ 004227e0 */
long dis_fmt_c74(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  long *piVar2;
  
  *tok = 0x12;
  tok[1] = 0x9a;
  piVar2 = tok + 2;
  uVar1 = (opw >> 8) & 0x3f;
  if ((uVar1 == 0x30) || (uVar1 == 0x34)) {
    *piVar2 = 0x3f;
  }
  else {
    *piVar2 = S32(((opw & 0x40) != 0) + 0xf6);
    tok[3] = S32(uVar1 + 0xb0);
    tok[4] = 0x99;
    piVar2 = tok + 5;
    *piVar2 = -5;
  }
  dis_sel_a = 0x4000;
  dis_sel_c = (((0x80) << 8) | ((uVar1) & 0xff));
  dis_sel_b = dis_sel_c;
  dis_effect_flags = (-((opw & 0x40) != 0) & 2) + 3;
  return (long)(piVar2 - tok) + 1;
}

/* dis_fmt_c78 @ 00422890 */
long dis_fmt_c78(unsigned long opw,long *tok)
{
  unsigned long v;
  
  *tok = 0x12;
  tok[1] = 0x9a;
  v = (opw >> 8) & 0x3f;
  if ((opw & 0x40) == 0) {
    tok[2] = 0xf6;
  }
  else {
    tok[2] = 0xf7;
  }
  tok[3] = 0xf0;
  fmt_hex_dollar(v,dis_hex_ea);
  tok[4] = -2;
  tok[5] = 0x99;
  tok[6] = -5;
  dis_sel_c = 0x100;
  dis_sel_b = 0x100;
  dis_effect_flags = (-((opw & 0x40) != 0) & 2) + 3;
  dis_val_c = v;
  dis_val_b = v;
  dis_sel_a = 0x4000;
  return 7;
}

/* dis_fmt_c82 @ 00422960 */
long dis_fmt_c82(unsigned long opw,long *tok)
{
  fmt_hex_dollar((opw >> 8) & 0xff,dis_hex_ea);
  *tok = 0x22;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  tok[3] = -2;
  tok[4] = 0x99;
  tok[5] = S32((opw & 7) + 0x74);
  return 6;
}

/* dis_fmt_c80 @ 004229d0 */
long dis_fmt_c80(unsigned long opw,long *tok)
{
  long *piVar1;
  unsigned long uVar2;
  unsigned long uVar3;
  long iVar4;
  unsigned long uVar5;
  
  uVar3 = (long)(((long)opw >> 0x1f & 0xffU) + opw) >> 8;
  iVar4 = 0;
  uVar2 = uVar3 & 0x3f;
  uVar5 = (opw & 0xff) >> 6 | 0x46;
  if (uVar2 == 0x34) {
    dis_effect_flags = 0;
  }
  else {
    dis_effect_flags = (-(uVar5 != 0x46) & 2) + 2;
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
      *piVar1 = S32(uVar5 + 0xb0);
      piVar1 = tok + 3;
    }
    *piVar1 = S32(uVar2 + 0xb0);
    piVar1[1] = S32(iVar4);
    piVar1[2] = 0x99;
    piVar1[3] = S32((opw & 7) + 0x74);
    return (long)(piVar1 - tok) + 4;
  }
  *piVar1 = S32((opw & 7) + 0x74);
  tok[3] = 0x99;
  piVar1 = tok + 4;
  if (uVar2 != 0x34) {
    *piVar1 = S32(uVar5 + 0xb0);
    piVar1 = tok + 5;
    if (uVar2 != 0x34) {
      *piVar1 = S32(uVar2 + 0xb0);
      tok[6] = S32(iVar4);
      return 7;
    }
  }
  *piVar1 = 0x3f;
  return (long)(piVar1 - tok) + 1;
}

/* dis_fmt_c84 @ 00422b00 */
long dis_fmt_c84(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  unsigned long uVar2;
  unsigned long v;
  
  uVar1 = (opw >> 8);
  v = uVar1 & 0x3f;
  fmt_hex_dollar(v,dis_hex_ea);
  uVar2 = (opw & 0xff) >> 6 | 0x46;
  *tok = 0x22;
  tok[1] = 0x9a;
  dis_effect_flags = (-(uVar2 != 0x47) & 0xfffffffe) + 4;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  dis_val_b = v;
  dis_val_c = v;
  if ((uVar1 & 0x80) != 0) {
    tok[2] = S32(uVar2 + 0xb0);
    tok[3] = 0xf0;
    tok[4] = -2;
    tok[5] = 0x99;
    tok[6] = S32((opw & 7) + 0x74);
    return 7;
  }
  tok[2] = S32((opw & 7) + 0x74);
  tok[3] = 0x99;
  tok[4] = S32(uVar2 + 0xb0);
  tok[5] = 0xf0;
  tok[6] = -2;
  return 7;
}

/* dis_fmt_c81 @ 00422c10 */
long dis_fmt_c81(unsigned long opw,long *tok)
{
  fmt_hex_dollar((opw >> 8) & 0xff,dis_hex_ea);
  *tok = 0x22;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  tok[3] = -2;
  tok[4] = 0x99;
  tok[5] = S32((opw & 7) + 0x7c);
  return 6;
}

/* dis_fmt_c79 @ 00422c80 */
long dis_fmt_c79(unsigned long opw,long *tok)
{
  long *piVar1;
  unsigned long uVar2;
  unsigned long uVar3;
  long iVar4;
  unsigned long uVar5;
  
  uVar3 = (long)(((long)opw >> 0x1f & 0xffU) + opw) >> 8;
  uVar2 = uVar3 & 0x3f;
  uVar5 = (opw & 0xff) >> 6 | 0x46;
  if ((uVar2 == 0x34) || (uVar2 == 0x30)) {
    iVar4 = -4;
  }
  else {
    iVar4 = 0;
  }
  if (uVar2 == 0x34) {
    dis_effect_flags = 0;
  }
  else {
    dis_effect_flags = (-(uVar5 != 0x47) & 0xfffffffe) + 4;
  }
  dis_sel_b = uVar2 | 0x8000;
  dis_sel_c = dis_sel_b;
  *tok = 0x22;
  tok[1] = 0x9a;
  piVar1 = tok + 2;
  if ((uVar3 & 0x80) != 0) {
    if (uVar2 != 0x34) {
      *piVar1 = S32(uVar5 + 0xb0);
      piVar1 = tok + 3;
    }
    *piVar1 = S32(uVar2 + 0xb0);
    piVar1[1] = S32(iVar4);
    piVar1[2] = 0x99;
    piVar1[3] = S32((opw & 7) + 0x7c);
    return (long)(piVar1 - tok) + 4;
  }
  *piVar1 = S32((opw & 7) + 0x7c);
  tok[3] = 0x99;
  piVar1 = tok + 4;
  if (uVar2 != 0x34) {
    *piVar1 = S32(uVar5 + 0xb0);
    piVar1 = tok + 5;
    if (uVar2 != 0x34) {
      *piVar1 = S32(uVar2 + 0xb0);
      tok[6] = S32(iVar4);
      return 7;
    }
  }
  *piVar1 = 0x3f;
  return (long)(piVar1 - tok) + 1;
}

/* dis_fmt_c83 @ 00422dc0 */
long dis_fmt_c83(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  unsigned long uVar2;
  unsigned long v;
  
  uVar1 = (opw >> 8);
  v = uVar1 & 0x3f;
  fmt_hex_dollar(v,dis_hex_ea);
  uVar2 = (opw & 0xff) >> 6 | 0x46;
  *tok = 0x22;
  tok[1] = 0x9a;
  if ((uVar1 & 0x80) == 0) {
    tok[2] = S32((opw & 7) + 0x7c);
    tok[3] = 0x99;
    tok[4] = S32(uVar2 + 0xb0);
    tok[5] = 0xf0;
    tok[6] = -2;
  }
  else {
    tok[2] = S32(uVar2 + 0xb0);
    tok[3] = 0xf0;
    tok[4] = -2;
    tok[5] = 0x99;
    tok[6] = S32((opw & 7) + 0x7c);
  }
  dis_val_c = v;
  dis_val_b = v;
  dis_effect_flags = (-(uVar2 != 0x47) & 0xfffffffe) + 4;
  dis_sel_b = 0x100;
  dis_sel_c = 0x100;
  return 7;
}

/* dis_fmt_c86 @ 00422ec0 */
long dis_fmt_c86(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  long iVar2;
  unsigned long uVar3;
  
  uVar1 = (opw >> 8);
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
    tok[2] = S32(iVar2 + 0x57);
    tok[3] = 0x99;
    tok[4] = S32((opw & 7) + 0x74);
    return 5;
  }
  tok[2] = S32((opw & 7) + 0x74);
  tok[3] = 0x99;
  tok[4] = S32(iVar2 + 0x57);
  return 5;
}

/* dis_fmt_c85 @ 00422f80 */
long dis_fmt_c85(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  unsigned long uVar2;
  unsigned long uVar3;
  long iVar4;
  unsigned long uVar5;
  
  uVar2 = opw & 7;
  uVar3 = (long)(((long)opw >> 0x1f & 0xffU) + opw) >> 8;
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
    tok[2] = S32(iVar4 + 0x57);
    tok[3] = 0x99;
    tok[4] = S32(uVar2 + 0x7c);
    return 5;
  }
  tok[2] = S32(uVar2 + 0x7c);
  tok[3] = 0x99;
  tok[4] = S32(iVar4 + 0x57);
  return 5;
}

/* dis_fmt_c88 @ 00423050 */
long dis_fmt_c88(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  
  uVar1 = (opw >> 8) & 0x3f;
  *tok = 0x1f;
  tok[1] = 0x9a;
  tok[2] = S32(uVar1 + 0xb0);
  tok[3] = 0x99;
  tok[4] = S32((opw & 7) + 100);
  dis_effect_flags = 1;
  dis_sel_a = uVar1 | 0x10000;
  return 5;
}

/* dis_fmt_c87 @ 004230c0 */
long dis_fmt_c87(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  
  uVar1 = (opw >> 8) & 0x3f;
  *tok = 0x1f;
  tok[1] = 0x9a;
  tok[2] = S32(uVar1 + 0xb0);
  tok[3] = 0x99;
  tok[4] = S32((opw & 7) + 0x6c);
  dis_effect_flags = 1;
  dis_sel_a = uVar1 | 0x10000;
  return 5;
}

/* dis_fmt_c89 @ 00423130 */
long dis_fmt_c89(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  unsigned long uVar2;
  unsigned long uVar3;
  
  uVar2 = (opw >> 8);
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
  tok[1] = S32(((uVar2 & 0xffff) >> 4 & 0xf) + 0x47);
  tok[2] = 0x9a;
  tok[3] = S32(uVar1 + 0xa0);
  tok[4] = 0x99;
  tok[5] = S32(uVar3 + 0x62);
  tok[6] = 0x9a;
  tok[7] = S32((uVar2 & 7) + 100);
  tok[8] = 0x99;
  tok[9] = S32((opw & 7) + 100);
  return 10;
}

/* dis_fmt_c90 @ 00423210 */
long dis_fmt_c90(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  unsigned long uVar2;
  
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
  tok[1] = S32((((opw >> 8) & 0xffffU) >> 4 & 0xf) + 0x47);
  tok[2] = 0x9a;
  tok[3] = S32(uVar1 + 0xa0);
  tok[4] = 0x99;
  tok[5] = S32(uVar2 + 0x62);
  return 6;
}

/* dis_fmt_c91 @ 004232b0 */
long dis_fmt_c91(unsigned long opw,long *tok)
{
  *tok = 0x29;
  tok[1] = 0x9a;
  tok[2] = S32(((opw >> 8) & 7U) + 100);
  tok[3] = 0x99;
  tok[4] = S32((opw >> 3 & 1) + 0x62);
  return 5;
}

/* dis_fmt_c92 @ 00423310 */
long dis_fmt_c92(unsigned long opw,long *tok)
{
  *tok = 0x11;
  tok[1] = 0x9a;
  tok[2] = S32(((opw & 0xffff) >> 4 & 7) + 0xa0);
  tok[3] = 0x99;
  tok[4] = S32(((opw & 0xffff) >> 3 & 1) + 0x62);
  return 5;
}

/* dis_fmt_c95 @ 00423370 */
long dis_fmt_c95(unsigned long opw,long *tok)
{
  fmt_hex_dollar((opw >> 8) & 0xff,dis_hex_ea);
  *tok = 0x2c;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  tok[3] = -2;
  tok[4] = 0x99;
  tok[5] = S32((opw & 3) + 0x9c);
  return 6;
}

/* dis_fmt_c96 @ 004233e0 */
long dis_fmt_c96(unsigned long opw,long *tok)
{
  fmt_hex_dollar((opw >> 8) & 0xff,dis_hex_ea);
  *tok = 7;
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  tok[3] = -2;
  tok[4] = 0x99;
  tok[5] = S32((opw & 3) + 0x9c);
  return 6;
}

/* dis_fmt_c97 @ 00423450 */
long dis_fmt_c97(unsigned long opw,long *tok)
{
  *tok = 0x13;
  return 1;
}

/* dis_fmt_c98 @ 00423460 */
long dis_fmt_c98(unsigned long opw,long *tok)
{
  *tok = 0x36;
  return 1;
}

/* dis_fmt_c99 @ 00423470 */
long dis_fmt_c99(unsigned long opw,long *tok)
{
  *tok = 0x3e;
  return 1;
}

/* dis_fmt_c100 @ 00423480 */
long dis_fmt_c100(unsigned long opw,long *tok)
{
  *tok = 0x2e;
  return 1;
}

/* dis_fmt_c104 @ 00423490 */
long dis_fmt_c104(unsigned long opw,long *tok)
{
  *tok = 0x3a;
  return 1;
}

/* dis_fmt_c107 @ 004234a0 */
long dis_fmt_c107(unsigned long opw,long *tok)
{
  *tok = 0x28;
  return 1;
}

/* dis_fmt_c106 @ 004234b0 */
long dis_fmt_c106(unsigned long opw,long *tok)
{
  *tok = 0x32;
  return 1;
}

/* dis_fmt_c101 @ 004234c0 */
long dis_fmt_c101(unsigned long opw,long *tok)
{
  *tok = 0x33;
  return 1;
}

/* dis_fmt_c68 @ 004234d0 */
long dis_fmt_c68(unsigned long opw,long *tok)
{
  long *piVar1;
  long bVar2;
  long iVar3;
  long *tok_00;
  unsigned long uVar4;
  unsigned long uVar5;
  
  uVar4 = (opw >> 8);
  bVar2 = 0;
  uVar5 = uVar4 & 0x3f;
  if ((uVar5 == 0x34) || (uVar5 == 0x30)) {
    bVar2 = 1;
  }
  if (((opw & 0x80) != 0) || (d_4c0cf0[((opw & 0x7f))] != 0)) {
    if ((opw & 0xf4008) == 0x80000) {
      bVar2 = 1;
    }
    if ((opw & 0xf4008) == 0x90008) {
      bVar2 = 1;
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
  *piVar1 = S32(iVar3);
  piVar1[1] = 0x99;
  piVar1[2] = 0xf6;
  piVar1[3] = S32(uVar5 + 0xb0);
  piVar1[4] = 0x9a;
  piVar1[5] = 0x58;
  piVar1[6] = 0x99;
  piVar1[7] = S32(iVar3);
  dis_sel_b = uVar5 | 0x8000;
  dis_effect_flags = 2;
  return (long)(piVar1 - tok) + 8;
}

/* dis_fmt_c63 @ 004235d0 */
long dis_fmt_c63(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_c68(opw,tok);
  return iVar1;
}

/* dis_fmt_c64 @ 004235f0 */
long dis_fmt_c64(unsigned long opw,long *tok)
{
  long bVar1;
  long iVar2;
  long *plVar3;
  unsigned long uVar4;
  unsigned long uVar5;
  
  uVar4 = (opw >> 8);
  bVar1 = 0;
  uVar5 = uVar4 & 0x3f;
  if ((uVar5 == 0x34) || (uVar5 == 0x30)) {
    bVar1 = 1;
  }
  if (((opw & 0x80) != 0) || (d_4c0cf0[((opw & 0x7f))] != 0)) {
    if ((opw & 0xf4008) == 0x80000) {
      bVar1 = 1;
    }
    if ((opw & 0xf4008) == 0x90008) {
      bVar1 = 1;
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
  plVar3[2] = S32(iVar2);
  plVar3[3] = 0x9a;
  plVar3[4] = S32(iVar2);
  plVar3[5] = 0x99;
  plVar3[6] = 0xf7;
  plVar3[7] = S32(uVar5 + 0xb0);
  dis_sel_c = uVar5 | 0x8000;
  dis_effect_flags = 4;
  return (long)(plVar3 - tok) + 8;
}

/* dis_fmt_c62 @ 004236f0 */
long dis_fmt_c62(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_c64(opw,tok);
  return iVar1;
}

/* dis_fmt_c30 @ 00423710 */
long dis_fmt_c30(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h423730(opw,tok,0x1c);
  return iVar1;
}

/* dis_fmt_h423730 @ 00423730 */
long dis_fmt_h423730(unsigned long opw,long *tok, long sel)
{
  unsigned long uVar1;
  unsigned long uVar2;
  long iVar3;
  
  uVar1 = (opw >> 8);
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
  *tok = S32(sel);
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,dis_hex_ea);
    tok[3] = -2;
  }
  else {
    tok[3] = 0x3f;
  }
  tok[4] = 0x99;
  tok[5] = S32(iVar3 + 0x57);
  tok[6] = 0x99;
  tok[7] = -4;
  dis_sel_a = 0x2000;
  dis_effect_flags = 1;
  return 8;
}

/* dis_fmt_c31 @ 00423820 */
long dis_fmt_c31(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h423730(opw,tok,0x19);
  return iVar1;
}

/* dis_fmt_c48 @ 00423840 */
long dis_fmt_c48(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h423730(opw,tok,0x1a);
  return iVar1;
}

/* dis_fmt_c49 @ 00423860 */
long dis_fmt_c49(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h423730(opw,tok,0x16);
  return iVar1;
}

/* dis_fmt_c28 @ 00423880 */
long dis_fmt_c28(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4238a0(opw,tok,0xd);
  return iVar1;
}

/* dis_fmt_h4238a0 @ 004238a0 */
long dis_fmt_h4238a0(unsigned long opw,long *tok, long sel)
{
  unsigned long uVar1;
  unsigned long uVar2;
  long iVar3;
  
  uVar1 = (opw >> 8);
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
  *tok = S32(sel);
  tok[1] = 0x9a;
  tok[2] = 0xf2;
  if ((opw & 0x1f) < 0x18) {
    fmt_hex_dollar(opw & 0x1f,dis_hex_ea);
    tok[3] = -2;
  }
  else {
    tok[3] = 0x3f;
  }
  tok[4] = 0x99;
  tok[5] = S32(iVar3 + 0x57);
  return 6;
}

/* dis_fmt_c29 @ 00423960 */
long dis_fmt_c29(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4238a0(opw,tok,10);
  return iVar1;
}

/* dis_fmt_c46 @ 00423980 */
long dis_fmt_c46(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4238a0(opw,tok,0xc);
  return iVar1;
}

/* dis_fmt_c47 @ 004239a0 */
long dis_fmt_c47(unsigned long opw,long *tok)
{
  long iVar1;
  
  iVar1 = dis_fmt_h4238a0(opw,tok,0xb);
  return iVar1;
}

/* dis_fmt_c93 @ 004239c0 */
long dis_fmt_c93(unsigned long opw,long *tok)
{
  long *piVar1;
  
  *tok = 0x43;
  piVar1 = tok + 1;
  if ((opw & 0x100) != 0) {
    *piVar1 = S32((opw & 0xf) + 0x47);
    piVar1 = tok + 2;
  }
  *piVar1 = 0x9a;
  return (long)(piVar1 - tok) + 1;
}

/* dis_fmt_c105 @ 004239f0 */
long dis_fmt_c105(unsigned long opw,long *tok)
{
  *tok = 0x40;
  return 1;
}

/* dis_fmt_c102 @ 00423a00 */
long dis_fmt_c102(unsigned long opw,long *tok)
{
  *tok = S32(((opw & 2) != 0) + 0x41);
  tok[1] = 0x9a;
  tok[2] = S32((opw & 1) + 0x62);
  return 3;
}

/* dis_fmt_c109 @ 00423a40 */
long dis_fmt_c109(unsigned long opw,long *tok)
{
  unsigned long uVar1;
  long iVar2;
  
  *tok = S32(d_4c1268[((opw & 3))]);
  tok[1] = 0x9a;
  uVar1 = (long)opw >> 4 & 3;
  if ((opw & 4) == 0) {
    iVar2 = d_4c1278[(uVar1)];
  }
  else {
    iVar2 = d_4c1288[(uVar1)];
  }
  tok[2] = S32(iVar2 + 0x57);
  tok[3] = 0x99;
  tok[4] = 0xf2;
  fmt_hex_dollar((long)opw >> 8 & 0x1f,dis_hex_ea);
  tok[5] = -2;
  tok[6] = 0x99;
  tok[7] = S32((opw >> 3 & 1) + 0x62);
  return 8;
}

/* hid_423ae0 @ 00423ae0 */
void hid_423ae0(unsigned long *opw,char *tok,long param_3,long param_4,void *param_5)
{
  dis_cpu_level = 8;
  disassemble(opw,tok,param_3,param_4,param_5);
  return;
}
