/* decode.c - instruction word decoder: 110 class handlers filling the decoded instruction record
 * (SIM56000.EXE 6.3.0, module decode 0x41cfb0-0x41fb60; dec_c0_enddo 0x41ce50 also lives here).
 * The record DEC is an array of 48 long words: [0] mnemonic id, [1] cc marker, [2..] 4 operands and
 * 4 move slots of 5 words each {kind, value, aux1, aux2, aux3} (operands from word 2, moves from
 * word 22), [0x2a] aux field, [0x2b] flags, [0x2c] sign, [0x2e]/[0x2f] instruction and extension word.
 * Most handlers were translated mechanically from the Ghidra export by re/scripts/g2c_dec.py and
 * checked against the original with tests/sim56000/emu/diff_decode.py. */
#include "sim56000.h"

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wparentheses"     /* mechanically converted expressions keep the original operator order */
#endif

long dec_uses_extword = 0;             /* 0x4dbe78 */
long dec_extword = 0;                  /* 0x4dbe7c */
long dec_pc = 0;                       /* 0x4dbe80 */

/* stored words are 32-bit signed in the original */
#define S32(x) s32_of((unsigned long)(x))

static long s32_of(unsigned long v)
{
    v &= MASK32;
    if (v & 0x80000000UL)
        return -(long)((~v & MASK32) + 1UL);
    return (long)v;
}


/* ------------------------------------------------------------------ hand translated functions (Ghidra reused the parameter variables) */
void swap_ptrs(void **a, void **b)
{
    void *t = *b;

    *b = *a;
    *a = t;
}

static void swp(long **a, long **b)
{
    long *t = *b;

    *b = *a;
    *a = t;
}

/* 6-bit effective address field -> operand slot {kind, value, aux, aux} */
void dec_ea6(long *slot, unsigned long ea6)
{
    unsigned long u2 = ea6 & 7, u1 = (ea6 >> 3) & 7;

    if (u1 == 6) {
        if (u2 == 0)
            slot[0] = 9;
        else if (u2 == 4) {
            slot[0] = 10;
            slot[3] = 0;
        }
        slot[1] = 0;
        slot[2] = dec_extword;
        dec_uses_extword = 1;
        return;
    }
    slot[0] = (long)(u1 + 1);
    slot[1] = (long)(u2 + 0x21);
    slot[2] = 0;
}

void dec_c0_enddo(unsigned long opw, long *dec)
{
    unsigned long u3 = opw >> 8, u4 = u3 & 0xffff, u2 = (u4 >> 4) & 0x300, u1 = ((u3 & 0x60) | u2) >> 5;
    unsigned long ea_a = u3 & 0x1f, ea_b, flag = u3 & 0x4000;
    long *a = dec + 22, *b = dec + 27, *c = dec + 32, *d = dec + 37;

    dec_alu(opw, dec);
    if ((u3 & 0x18) == 0)
        ea_a |= 0x20;
    ea_b = u1;
    if (u2 == 0)
        ea_b = u1 | 0x20;
    if ((u3 & 0x80) == 0)
        swp(&a, &b);
    a[3] = 1;
    dec_ea6(a, ea_a);
    b[0] = 0xc;
    b[1] = d_4c0270[(u4 >> 10) & 3];
    if ((u3 & 4) == 0)
        ea_b |= 4;
    if (flag == 0)
        swp(&c, &d);
    c[3] = 2;
    dec_ea6(c, ea_b);
    d[0] = 0xc;
    d[1] = d_4c0280[(u4 >> 8) & 3];
}

void dec_c1_enddo(unsigned long opw, long *dec)
{
    unsigned long u1 = opw >> 8;
    long *a = dec + 22, *b = dec + 27;

    dec_alu(opw, dec);
    if ((u1 & 0x80) == 0)
        swp(&a, &b);
    a[3] = (u1 & 0x800) != 0 ? 2 : 1;
    dec_ea6(a, u1 & 0x3f);
    b[0] = 0xc;
    b[1] = d_4bfc80[((((u1 & 0xffff) >> 1) & 0x1800) | (u1 & 0x700)) >> 8];
}

void dec_c2_doforever(unsigned long opw, long *dec)
{
    unsigned long u1 = opw >> 8;
    long *a = dec + 22, *b = dec + 27;

    dec_alu(opw, dec);
    if ((u1 & 0x80) == 0)
        swp(&a, &b);
    a[3] = (u1 & 0x800) != 0 ? 2 : 1;
    a[0] = 9;
    a[2] = (long)(u1 & 0x3f);
    b[0] = 0xc;
    b[1] = d_4bfc80[((((u1 & 0xffff) >> 1) & 0x1800) | (u1 & 0x700)) >> 8];
}

void dec_c9_enddo(unsigned long opw, long *dec)
{
    unsigned long u1 = opw >> 8, u2 = ((u1 & 0x300) | (((u1 & 0xffff) >> 1) & 0x400)) >> 8;
    long *a = dec + 22, *b = dec + 27, *c = dec + 32, *d = dec + 37;

    dec_alu(opw, dec);
    if ((u1 & 0x80) == 0) {
        swp(&a, &b);
        swp(&c, &d);
    }
    a[3] = 1;
    dec_ea6(a, u1 & 0x3f);
    b[0] = 0xc;
    b[1] = d_4bff80[u2];
    c[3] = 2;
    dec_ea6(c, u1 & 0x3f);
    d[0] = 0xc;
    d[1] = d_4bffa0[u2];
}

void dec_c10_doforever(unsigned long opw, long *dec)
{
    unsigned long u1 = opw >> 8, u2 = ((u1 & 0x300) | (((u1 & 0xffff) >> 1) & 0x400)) >> 8;
    long *a = dec + 22, *b = dec + 27, *c = dec + 32, *d = dec + 37;

    dec_alu(opw, dec);
    if ((u1 & 0x80) == 0) {
        swp(&a, &b);
        swp(&c, &d);
    }
    a[3] = 1;
    a[0] = 9;
    a[2] = (long)(u1 & 0x3f);
    b[0] = 0xc;
    b[1] = d_4bff80[u2];
    c[3] = 2;
    c[0] = 9;
    c[2] = (long)(u1 & 0x3f);
    d[0] = 0xc;
    d[1] = d_4bffa0[u2];
}

void dec_c20_enddo(unsigned long opw, long *dec)
{
    unsigned long u2 = opw >> 8;
    long *a = dec + 32, *b = dec + 37;

    dec_alu(opw, dec);
    dec[22] = 0xc;
    dec[27] = 0xc;
    dec[23] = d_4c0000[((u2 & 0xffff) >> 11) & 1];
    dec[28] = (u2 & 0x400) != 0 ? 0x32 : 0x31;
    if ((u2 & 0x80) == 0)
        swp(&a, &b);
    a[3] = 2;
    dec_ea6(a, u2 & 0x3f);
    b[0] = 0xc;
    b[1] = d_4c0290[((u2 & 0xffff) >> 8) & 3];
}

void dec_c21_pm(unsigned long opw, long *dec)
{
    unsigned long u1 = opw >> 8, u2 = u1 & 0xffff;
    long *a = dec + 22, *b = dec + 27;

    dec_alu(opw, dec);
    if ((u1 & 0x80) == 0)
        swp(&a, &b);
    a[3] = 1;
    dec_ea6(a, u1 & 0x3f);
    b[0] = 0xc;
    b[1] = d_4c02a0[(u2 >> 10) & 3];
    dec[32] = 0xc;
    dec[33] = d_4c0000[(u2 >> 9) & 1];
    dec[37] = 0xc;
    dec[38] = ((u2 >> 8) & 1) != 0 ? 0x35 : 0x34;
}

void dec_c69_enddo(unsigned long opw, long *dec)
{
    unsigned long u2 = opw & 0x3f, u1 = opw >> 8;
    long *a = dec + 22, *b = dec + 27;

    if ((u1 & 0x80) == 0)
        swp(&a, &b);
    a[3] = 3;
    dec_ea6(a, u1 & 0x3f);
    b[0] = 0xc;
    b[1] = d_4bfc80[u2];
}

void dec_c70_doforever(unsigned long opw, long *dec)
{
    unsigned long u2 = opw & 0x3f, u1 = opw >> 8;
    long *a = dec + 22, *b = dec + 27;

    if ((u1 & 0x80) == 0)
        swp(&a, &b);
    a[3] = 3;
    a[0] = 9;
    a[2] = (long)(u1 & 0x3f);
    b[0] = 0xc;
    b[1] = d_4bfc80[u2];
}

void dec_c79_enddo(unsigned long opw, long *dec)
{
    unsigned long u3 = opw & 0x3f, u2 = opw >> 8, u4 = opw & 0x40;
    long *a = dec + 22, *b = dec + 27;

    if ((u2 & 0x80) == 0)
        swp(&a, &b);
    a[3] = u4 != 0 ? 2 : 1;
    dec_ea6(a, u2 & 0x3f);
    b[0] = 0xc;
    b[1] = d_4bfc80[u3];
}

void dec_c83_doforever(unsigned long opw, long *dec)
{
    unsigned long u3 = opw & 0x3f, u2 = opw >> 8, u4 = opw & 0x40;
    long *a = dec + 22, *b = dec + 27;

    if ((u2 & 0x80) == 0)
        swp(&a, &b);
    a[3] = u4 != 0 ? 2 : 1;
    a[0] = 9;
    a[2] = (long)(u2 & 0x3f);
    b[0] = 0xc;
    b[1] = d_4bfc80[u3];
}

void dec_c85_enddo(unsigned long opw, long *dec)
{
    unsigned long u2 = opw & 0x3f, u1 = opw >> 8;
    long *a = dec + 22, *b = dec + 27;

    if ((u1 & 0x80) == 0)
        swp(&a, &b);
    a[0] = 0xc;
    a[1] = d_4bfc80[u1 & 0x3f];
    b[0] = 0xc;
    b[1] = d_4bfc80[u2];
}

void dec_movep_ea(long *dec, long a2, long a3, long a4, long swap, unsigned long ea6)
{
    long *a = dec + 22, *b = dec + 27;

    if (swap != 0)
        swp(&a, &b);
    a[3] = a2;
    a[0] = 9;
    a[2] = a4;
    b[3] = a3;
    dec_ea6(b, ea6);
}

void dec_movep_reg(long *dec, long a2, long a3, long swap, long regsel)
{
    long *a = dec + 22, *b = dec + 27;

    if (swap != 0)
        swp(&a, &b);
    a[3] = a2;
    a[0] = 9;
    a[2] = a3;
    b[0] = 0xc;
    b[1] = d_4bfc80[regsel];
}

/* peripheral bit operations: 0xffc0 (X: io space) or 0xff80 (spacesel 1: low io space) */
void dec_bit_pp(unsigned long opw, long *dec, long spacesel)
{
    unsigned long u2 = 0xffc0UL | ((opw >> 8) & 0x3f);

    if (spacesel == 1)
        u2 = 0xff80UL | ((opw >> 8) & 0x3f);
    dec[22] = 10;
    dec[24] = (long)(opw & 0x1f);
    dec[30] = (opw & 0x40) != 0 ? 2 : 1;
    dec[27] = 9;
    dec[29] = (long)u2;
}

void dec_extract_reg(unsigned long opw, long *dec)
{
    dec_flag_nomove(dec);
    dec[2] = 0xc;
    dec[3] = d_4c0028[(opw >> 1) & 7];
    dec[7] = 0xc;
    dec[8] = d_4c0000[(opw >> 4) & 1];
    dec[12] = 0xc;
    dec[13] = d_4c0000[opw & 1];
    dec[0] = 0x42 + (long)((opw >> 7) & 1);
}

void dec_extract_imm(unsigned long opw, long *dec)
{
    dec_flag_nomove(dec);
    dec[2] = 10;
    dec[4] = dec_extword;
    dec[7] = 0xc;
    dec[8] = d_4c0000[(opw >> 4) & 1];
    dec[12] = 0xc;
    dec[13] = d_4c0000[opw & 1];
    dec[0] = 0x42 + (long)(((~opw) >> 7) & 1);
    dec_uses_extword = 1;
}

void dec_h41f650(unsigned long opw, long *dec)
{
    unsigned long u5 = opw >> 8, u3 = ((((opw >> 4) & 0x1f80) | (opw & 0x40)) >> 6), u6 = opw & 0xf;
    unsigned long u2 = opw & 0x10, u4 = opw & 0x20;
    long *a = dec + 22, *b = dec + 27;

    if (((opw >> 4) & 0x1000) != 0)
        u3 |= 0xffffffc0UL;
    if (u2 == 0)
        swp(&a, &b);
    a[0] = 0xd;
    a[3] = u4 != 0 ? 2 : 1;
    a[1] = d_4bfc80[(u5 & 7) | 0x10];
    a[2] = S32(u3);
    b[0] = 0xc;
    b[1] = d_4bfc80[u6];
}

void dec_h41f700(unsigned long opw, long *dec)
{
    unsigned long u3 = opw >> 8, u4 = opw & 0x3f, u2 = opw & 0x40;
    long *a = dec + 22, *b = dec + 27;

    if (u2 == 0)
        swp(&a, &b);
    a[0] = 0xd;
    a[3] = (u3 & 0x100) != 0 ? 2 : 1;
    a[1] = d_4bfc80[(u3 & 7) | 0x10];
    a[2] = dec_extword;
    dec_uses_extword = 1;
    b[0] = 0xc;
    b[1] = d_4bfc80[u4];
}

/* the decoded instruction record starts empty: mnemonic 0, operands 0, aux field 0x10 */
void dec_init(long *dec)
{
    int i;

    for (i = 0; i < 0x2a; i++)
        dec[i] = 0;
    dec[0x2a] = 0x10;
    dec[0x2b] = 0;
    dec[0x2c] = 0;
    dec[0x2d] = 0;
}

/* decode dec[0x2e] (word 0) and dec[0x2f] (extension word) into dec; returns 1 when valid */
long decode_insn(long *dec, long pc, long unused, unsigned long *flags)
{
    long cls, r;
    unsigned long opw = (unsigned long)dec[0x2e] & MASK32;

    cls = opclass_lookup(opw, (unsigned long)dec_cpu_level[0]);
    dec_pc = pc;
    dec_extword = dec[0x2f];
    dec_uses_extword = 0;
    dec_init(dec);
    r = insn_validate(opw, (unsigned long)cur_dtype->family);
    if (r != 0) {
        if (r != 7) {
            dec[0] = 0x19;
            return r == 0;
        }
        *flags |= 4;
    }
    ((void (*)(unsigned long, long *))dec_handlers[cls])(opw, dec);
    if ((dec[0x2b] & 0x20) != 0 || dec[0] == 0)
        dec[0x2b] |= 0x80;
    if (dec_uses_extword != 0)
        dec[0x2b] |= 0x40;
    return r == 0;
}

/* dec_alu @ 0041cfd0 */
void dec_alu(unsigned long opw, long *dec)
{
  if ((char)opw != '\0') {
    dec_flag_nomove(dec);
    if ((opw & 0x80) != 0) {
      dec_alu_mpy(opw,dec);
      return;
    }
    dec_alu_dp(opw,dec);
  }
}

/* dec_flag_nomove @ 0041d010 */
void dec_flag_nomove(long *dec)
{
  dec[43] = S32(dec[43] | 0x20);
}

/* dec_alu_dp @ 0041d020 */
void dec_alu_dp(unsigned long opw, long *dec)
{
  long iVar1;
  long *puVar2;
  
  dec[2] = 0xc;
  iVar1 = d_4bfd80[((opw & 0x7f))];
  dec[3] = S32(iVar1);
  puVar2 = (dec + 7);
  if (iVar1 == 0) {
    puVar2 = (dec + 2);
  }
  *puVar2 = 0xc;
  puVar2[1] = d_4c0000[((opw >> 3 & 1))];
  dec[0] = S32(d_4c0158[(((opw >> 4 & 7) << 3 | opw & 7))]);
}

/* dec_alu_mpy @ 0041d090 */
void dec_alu_mpy(unsigned long opw, long *dec)
{
  unsigned long uVar1;
  
  uVar1 = opw >> 4 & 7;
  dec[2] = 0xc;
  dec[3] = S32(d_4c0098[(uVar1)]);
  dec[7] = 0xc;
  dec[8] = S32(d_4c00d8[(uVar1)]);
  dec[12] = 0xc;
  dec[13] = S32(d_4c0000[((opw >> 3 & 1))]);
  dec[44] = S32((-((opw & 4) != 0) & 0xfffffffe) + 1);
  dec[0] = S32(d_4c0148[((opw & 3))]);
}

/* dec_c11_pm @ 0041d4d0 */
void dec_c11_pm(unsigned long opw, long *dec)
{
  unsigned long uVar1;
  unsigned long uVar2;
  unsigned long uVar3;
  
  uVar1 = opw >> 8 & 0xff;
  uVar2 = (opw >> 8 & 0xffff) >> 8;
  uVar3 = uVar2 & 0x1f;
  if (((uVar2 & 0x18) == 0) || (((unsigned char)uVar3 & 0x1e) == 0xe)) {
    uVar1 = uVar1 << 8;
  }
  dec_alu(opw,dec);
  dec[22] = 10;
  dec[24] = S32(uVar1);
  dec[27] = 0xc;
  dec[28] = S32(d_4bfc80[(uVar3)]);
}

/* dec_c15_pm @ 0041d530 */
void dec_c15_pm(unsigned long opw, long *dec)
{
  dec_alu(opw,dec);
  dec[22] = 0xc;
  dec[23] =
       d_4bfc80[(((opw >> 8 & 0xffff) >> 5 & 0x1f))];
  dec[27] = 0xc;
  dec[28] = S32(d_4bfc80[((opw >> 8 & 0x1f))]);
}

/* dec_pm_update @ 0041d580 */
void dec_pm_update(unsigned long opw, long *dec)
{
  dec_alu(opw,dec);
  dec_ea6((dec + 22),opw >> 8 & 0x3f);
}

/* dec_c19_pm @ 0041d5b0 */
void dec_c19_pm(unsigned long opw, long *dec)
{
  dec_alu(opw,dec);
}

/* dec_c22_pm @ 0041d770 */
void dec_c22_pm(unsigned long opw, long *dec)
{
  if ((opw & 0x20000) != 0) {
    dec[42] = S32(opw >> 0xc & 0xf);
  }
  dec[0] = S32((opw & 0x10000 | 0x40000) >> 0xe);
  dec[32] = 9;
  dec[34] = S32(opw & 0xfff);
}

/* dec_c26_pm @ 0041d7c0 */
void dec_c26_pm(unsigned long opw, long *dec)
{
  dec[0] = S32((opw & 0x10000 | 0x40000) >> 0xe);
  if ((opw & 0x20) != 0) {
    dec[42] = S32(opw & 0xf);
  }
  dec_ea6((dec + 32),opw >> 8 & 0x3f);
}

/* dec_c36_jsset @ 0041d810 */
void dec_c36_jsset(unsigned long opw, long *dec)
{
  dec_jbit_ea(opw,dec);
  dec[0] = 0x15;
}

/* dec_jbit_ea @ 0041d830 */
void dec_jbit_ea(unsigned long opw, long *dec)
{
  dec_bit_ea(opw,dec);
  dec[32] = 9;
  dec[34] = S32(dec_extword);
  dec_uses_extword = 1;
}

/* dec_bit_ea @ 0041d870 */
void dec_bit_ea(unsigned long opw, long *dec)
{
  dec[22] = 10;
  dec[24] = S32(opw & 0x1f);
  dec[30] = S32(((opw & 0x40) != 0) + 1);
  dec_ea6((dec + 27),opw >> 8 & 0x3f);
}

/* dec_c37_jsclr @ 0041d8b0 */
void dec_c37_jsclr(unsigned long opw, long *dec)
{
  dec_jbit_ea(opw,dec);
  dec[0] = 0x12;
}

/* dec_h41d8d0 @ 0041d8d0 */
void dec_h41d8d0(unsigned long opw, long *dec)
{
  dec_jbit_ea(opw,dec);
  dec[0] = 0x30;
}

/* dec_h41d8f0 @ 0041d8f0 */
void dec_h41d8f0(unsigned long opw, long *dec)
{
  dec_jbit_ea(opw,dec);
  dec[0] = 0x2e;
}

/* dec_c54_jset @ 0041d910 */
void dec_c54_jset(unsigned long opw, long *dec)
{
  dec_jbit_ea(opw,dec);
  dec[0] = 0x13;
}

/* dec_c55_jclr @ 0041d930 */
void dec_c55_jclr(unsigned long opw, long *dec)
{
  dec_jbit_ea(opw,dec);
  dec[0] = 0x11;
}

/* dec_h41d950 @ 0041d950 */
void dec_h41d950(unsigned long opw, long *dec)
{
  dec_jbit_ea(opw,dec);
  dec[0] = 0x2f;
}

/* dec_h41d970 @ 0041d970 */
void dec_h41d970(unsigned long opw, long *dec)
{
  dec_jbit_ea(opw,dec);
  dec[0] = 0x2d;
}

/* dec_c30_jsset @ 0041d990 */
void dec_c30_jsset(unsigned long opw, long *dec)
{
  dec_jbit_reg(opw,dec);
  dec[0] = 0x15;
}

/* dec_jbit_reg @ 0041d9b0 */
void dec_jbit_reg(unsigned long opw, long *dec)
{
  dec_bit_reg(opw,dec);
  dec[32] = 9;
  dec[34] = S32(dec_extword);
  dec_uses_extword = 1;
}

/* dec_bit_reg @ 0041d9f0 */
void dec_bit_reg(unsigned long opw, long *dec)
{
  dec[22] = 10;
  dec[24] = S32(opw & 0x1f);
  dec[27] = 0xc;
  dec[28] = S32(d_4bfc80[((opw >> 8 & 0x3f))]);
}

/* dec_c31_jsclr @ 0041da20 */
void dec_c31_jsclr(unsigned long opw, long *dec)
{
  dec_jbit_reg(opw,dec);
  dec[0] = 0x12;
}

/* dec_c48_jset @ 0041da40 */
void dec_c48_jset(unsigned long opw, long *dec)
{
  dec_jbit_reg(opw,dec);
  dec[0] = 0x13;
}

/* dec_c49_jclr @ 0041da60 */
void dec_c49_jclr(unsigned long opw, long *dec)
{
  dec_jbit_reg(opw,dec);
  dec[0] = 0x11;
}

/* dec_h41da80 @ 0041da80 */
void dec_h41da80(unsigned long opw, long *dec)
{
  dec_jbit_reg(opw,dec);
  dec[0] = 0x30;
}

/* dec_h41daa0 @ 0041daa0 */
void dec_h41daa0(unsigned long opw, long *dec)
{
  dec_jbit_reg(opw,dec);
  dec[0] = 0x2e;
}

/* dec_h41dac0 @ 0041dac0 */
void dec_h41dac0(unsigned long opw, long *dec)
{
  dec_jbit_reg(opw,dec);
  dec[0] = 0x2f;
}

/* dec_h41dae0 @ 0041dae0 */
void dec_h41dae0(unsigned long opw, long *dec)
{
  dec_jbit_reg(opw,dec);
  dec[0] = 0x2d;
}

/* dec_c40_jsset @ 0041db00 */
void dec_c40_jsset(unsigned long opw, long *dec)
{
  dec_jbit_aa(opw,dec);
  dec[0] = 0x15;
}

/* dec_jbit_aa @ 0041db20 */
void dec_jbit_aa(unsigned long opw, long *dec)
{
  dec_bit_aa(opw,dec);
  dec[32] = 9;
  dec[34] = S32(dec_extword);
  dec_uses_extword = 1;
}

/* dec_bit_aa @ 0041db60 */
void dec_bit_aa(unsigned long opw, long *dec)
{
  dec[22] = 10;
  dec[24] = S32(opw & 0x1f);
  dec[27] = 9;
  dec[30] = S32(((opw & 0x40) != 0) + 1);
  dec[29] = S32(opw >> 8 & 0x3f);
}

/* dec_c41_jsclr @ 0041dba0 */
void dec_c41_jsclr(unsigned long opw, long *dec)
{
  dec_jbit_aa(opw,dec);
  dec[0] = 0x12;
}

/* dec_c58_jset @ 0041dbc0 */
void dec_c58_jset(unsigned long opw, long *dec)
{
  dec_jbit_aa(opw,dec);
  dec[0] = 0x13;
}

/* dec_c59_jclr @ 0041dbe0 */
void dec_c59_jclr(unsigned long opw, long *dec)
{
  dec_jbit_aa(opw,dec);
  dec[0] = 0x11;
}

/* dec_h41dc00 @ 0041dc00 */
void dec_h41dc00(unsigned long opw, long *dec)
{
  dec_jbit_aa(opw,dec);
  dec[0] = 0x2f;
}

/* dec_h41dc20 @ 0041dc20 */
void dec_h41dc20(unsigned long opw, long *dec)
{
  dec_jbit_aa(opw,dec);
  dec[0] = 0x2d;
}

/* dec_h41dc40 @ 0041dc40 */
void dec_h41dc40(unsigned long opw, long *dec)
{
  dec_jbit_aa(opw,dec);
  dec[0] = 0x30;
}

/* dec_h41dc60 @ 0041dc60 */
void dec_h41dc60(unsigned long opw, long *dec)
{
  dec_jbit_aa(opw,dec);
  dec[0] = 0x2e;
}

/* dec_c32_jsset @ 0041dc80 */
void dec_c32_jsset(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,0);
  dec[0] = 0x15;
}

/* dec_jbit_pp @ 0041dca0 */
void dec_jbit_pp(unsigned long opw,long *dec,long spacesel)
{
  dec_bit_pp(opw,dec,spacesel);
  dec[32] = 9;
  dec[34] = S32(dec_extword);
  dec_uses_extword = 1;
}

/* dec_c33_jsclr @ 0041dd30 */
void dec_c33_jsclr(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,0);
  dec[0] = 0x12;
}

/* dec_c50_jset @ 0041dd50 */
void dec_c50_jset(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,0);
  dec[0] = 0x13;
}

/* dec_c51_jclr @ 0041dd70 */
void dec_c51_jclr(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,0);
  dec[0] = 0x11;
}

/* dec_h41dd90 @ 0041dd90 */
void dec_h41dd90(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,0);
  dec[0] = 0x2f;
}

/* dec_h41ddb0 @ 0041ddb0 */
void dec_h41ddb0(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,0);
  dec[0] = 0x2d;
}

/* dec_h41ddd0 @ 0041ddd0 */
void dec_h41ddd0(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,1);
  dec[0] = 0x13;
}

/* dec_h41ddf0 @ 0041ddf0 */
void dec_h41ddf0(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,1);
  dec[0] = 0x11;
}

/* dec_h41de10 @ 0041de10 */
void dec_h41de10(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,1);
  dec[0] = 0x2f;
}

/* dec_h41de30 @ 0041de30 */
void dec_h41de30(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,1);
  dec[0] = 0x2d;
}

/* dec_h41de50 @ 0041de50 */
void dec_h41de50(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,1);
  dec[0] = 0x15;
}

/* dec_h41de70 @ 0041de70 */
void dec_h41de70(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,1);
  dec[0] = 0x12;
}

/* dec_h41de90 @ 0041de90 */
void dec_h41de90(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,0);
  dec[0] = 0x30;
}

/* dec_h41deb0 @ 0041deb0 */
void dec_h41deb0(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,0);
  dec[0] = 0x2e;
}

/* dec_h41ded0 @ 0041ded0 */
void dec_h41ded0(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,1);
  dec[0] = 0x30;
}

/* dec_h41def0 @ 0041def0 */
void dec_h41def0(unsigned long opw, long *dec)
{
  dec_jbit_pp(opw,dec,1);
  dec[0] = 0x2e;
}

/* dec_c34_btst @ 0041df10 */
void dec_c34_btst(unsigned long opw, long *dec)
{
  dec_bit_pp(opw,dec,0);
  dec[0] = 6;
}

/* dec_c35_bchg @ 0041df30 */
void dec_c35_bchg(unsigned long opw, long *dec)
{
  dec_bit_pp(opw,dec,0);
  dec[0] = 2;
}

/* dec_c52_bset @ 0041df50 */
void dec_c52_bset(unsigned long opw, long *dec)
{
  dec_bit_pp(opw,dec,0);
  dec[0] = 5;
}

/* dec_c53_bclr @ 0041df70 */
void dec_c53_bclr(unsigned long opw, long *dec)
{
  dec_bit_pp(opw,dec,0);
  dec[0] = 3;
}

/* dec_c38_btst @ 0041df90 */
void dec_c38_btst(unsigned long opw, long *dec)
{
  dec_bit_ea(opw,dec);
  dec[0] = 6;
}

/* dec_c39_bchg @ 0041dfb0 */
void dec_c39_bchg(unsigned long opw, long *dec)
{
  dec_bit_ea(opw,dec);
  dec[0] = 2;
}

/* dec_c56_bset @ 0041dfd0 */
void dec_c56_bset(unsigned long opw, long *dec)
{
  dec_bit_ea(opw,dec);
  dec[0] = 5;
}

/* dec_c57_bclr @ 0041dff0 */
void dec_c57_bclr(unsigned long opw, long *dec)
{
  dec_bit_ea(opw,dec);
  dec[0] = 3;
}

/* dec_c42_btst @ 0041e010 */
void dec_c42_btst(unsigned long opw, long *dec)
{
  dec_bit_aa(opw,dec);
  dec[0] = 6;
}

/* dec_c43_bchg @ 0041e030 */
void dec_c43_bchg(unsigned long opw, long *dec)
{
  dec_bit_aa(opw,dec);
  dec[0] = 2;
}

/* dec_c60_bset @ 0041e050 */
void dec_c60_bset(unsigned long opw, long *dec)
{
  dec_bit_aa(opw,dec);
  dec[0] = 5;
}

/* dec_c61_bclr @ 0041e070 */
void dec_c61_bclr(unsigned long opw, long *dec)
{
  dec_bit_aa(opw,dec);
  dec[0] = 3;
}

/* dec_c65_pm @ 0041e090 */
void dec_c65_pm(unsigned long opw, long *dec)
{
  unsigned long uVar1;
  
  uVar1 = opw >> 8;
  dec_movep_ea(dec,((uVar1 & 0x100) != 0) + 1,((opw & 0x40) != 0) + 1,opw & 0x3f | 0xffc0,
               uVar1 & 0x80,uVar1 & 0x3f);
}

/* dec_h41e150 @ 0041e150 */
void dec_h41e150(unsigned long opw, long *dec)
{
  dec_movep_ea(dec,((opw & 0x80) != 0) + 1,((opw & 0x40) != 0) + 1,
               opw & 0x3f | 0xff80,opw >> 8 & 0x80,opw >> 8 & 0x3f);
}

/* dec_c66_pm @ 0041e1a0 */
void dec_c66_pm(unsigned long opw, long *dec)
{
  unsigned long uVar1;
  
  uVar1 = opw >> 8;
  dec_movep_ea(dec,((uVar1 & 0x100) != 0) + 1,3,opw & 0x3f | 0xffc0,uVar1 & 0x80,uVar1 & 0x3f);
}

/* dec_h41e1f0 @ 0041e1f0 */
void dec_h41e1f0(unsigned long opw, long *dec)
{
  dec_movep_ea(dec,((opw & 0x40) != 0) + 1,3,opw & 0x3f | 0xff80,opw >> 8 & 0x40,
               opw >> 8 & 0x3f);
}

/* dec_c67_pm @ 0041e230 */
void dec_c67_pm(unsigned long opw, long *dec)
{
  unsigned long uVar1;
  
  uVar1 = opw >> 8;
  dec_movep_reg(dec,((uVar1 & 0x100) != 0) + 1,opw & 0x3f | 0xffc0,uVar1 & 0x80,uVar1 & 0x3f);
}

/* dec_h41e2f0 @ 0041e2f0 */
void dec_h41e2f0(unsigned long opw, long *dec)
{
  if ((opw & 0x80) == 0) {
    dec[42] = S32(opw & 0xf);
  }
  dec[0] = S32(0x2c - ((opw & 0x40) != 0));
  dec[32] = 0xc;
  dec[33] = S32(d_4bfc80[((opw >> 8 & 7 | 0x10))]);
}

/* dec_h41e340 @ 0041e340 */
void dec_h41e340(unsigned long opw, long *dec)
{
  if ((opw & 0x80) == 0) {
    dec[42] = S32(opw & 0xf);
  }
  dec[0] = S32(0x2c - ((opw & 0x40) != 0));
  dec[32] = 9;
  dec[34] = S32(dec_extword);
  dec_uses_extword = 1;
}

/* dec_h41e390 @ 0041e390 */
void dec_h41e390(unsigned long opw, long *dec)
{
  unsigned long uVar1;
  unsigned long uVar2;
  
  uVar1 = opw >> 1 & 0x1e0;
  uVar2 = uVar1 | opw & 0x1f;
  if ((opw & 0x800) == 0) {
    dec[42] = S32(opw >> 0xc & 0xf);
  }
  dec[0] = S32(0x2c - ((opw & 0x400) != 0));
  dec[32] = 9;
  if ((char)(uVar1 >> 8) != '\0') {
    uVar2 = uVar2 | 0xffffff00;
  }
  dec[34] = S32(uVar2);
}

/* dec_h41e3f0 @ 0041e3f0 */
void dec_h41e3f0(unsigned long opw, long *dec)
{
  dec_movep_reg(dec,((opw & 0x20) != 0) + 1,(opw & 0x40 | 0x1ff00) >> 1 | opw & 0x1f
                ,opw >> 8 & 0x80,opw >> 8 & 0x3f);
}

/* dec_c75_rep @ 0041e540 */
void dec_c75_rep(unsigned long opw, long *dec)
{
  dec[22] = 10;
  dec[24] = S32(opw >> 8 & 0xff | (opw & 0xf) << 8);
  dec[0] = 0x23;
}

/* dec_c71_rep @ 0041e570 */
void dec_c71_rep(unsigned long opw, long *dec)
{
  dec[22] = 0xc;
  dec[23] = S32(d_4bfc80[((opw >> 8 & 0x3f))]);
  dec[0] = 0x23;
}

/* dec_c73_rep @ 0041e5a0 */
void dec_c73_rep(unsigned long opw, long *dec)
{
  dec[25] = S32(((opw & 0x40) != 0) + 1);
  dec_ea6((dec + 22),opw >> 8 & 0x3f);
  dec[0] = 0x23;
}

/* dec_c77_rep @ 0041e5e0 */
void dec_c77_rep(unsigned long opw, long *dec)
{
  dec[22] = 9;
  dec[25] = S32(((opw & 0x40) != 0) + 1);
  dec[24] = S32(opw >> 8 & 0x3f);
  dec[0] = 0x23;
}

/* dec_do_imm @ 0041e610 */
void dec_do_imm(unsigned long opw, long *dec)
{
  dec[22] = 10;
  dec[24] = S32(opw >> 8 & 0xff | (opw & 0xf) << 8);
  dec[27] = 9;
  dec[29] = S32(dec_extword);
  dec_uses_extword = 1;
  dec[0] = 8;
}

/* dec_do_reg @ 0041e650 */
void dec_do_reg(unsigned long opw, long *dec)
{
  dec[22] = 0xc;
  dec[23] = S32(d_4bfc80[((opw >> 8 & 0x3f))]);
  dec[27] = 9;
  dec[29] = S32(dec_extword);
  dec_uses_extword = 1;
  dec[0] = 8;
}

/* dec_do_ea @ 0041e690 */
void dec_do_ea(unsigned long opw, long *dec)
{
  dec[25] = S32(((opw & 0x40) != 0) + 1);
  dec_ea6((dec + 22),opw >> 8 & 0x3f);
  dec[27] = 9;
  dec[29] = S32(dec_extword);
  dec_uses_extword = 1;
  dec[0] = 8;
}

/* dec_do_aa @ 0041e6e0 */
void dec_do_aa(unsigned long opw, long *dec)
{
  dec[22] = 9;
  dec[25] = S32(((opw & 0x40) != 0) + 1);
  dec[24] = S32(opw >> 8 & 0x3f);
  dec[27] = 9;
  dec[29] = S32(dec_extword);
  dec_uses_extword = 1;
  dec[0] = 8;
}

/* dec_c81_pm @ 0041e730 */
void dec_c81_pm(unsigned long opw, long *dec)
{
  dec[22] = 10;
  dec[24] = S32(opw >> 8 & 0xff);
  dec[27] = 0xc;
  dec[28] = S32(d_4bfc80[((opw & 0x3f))]);
}

/* dec_c87_lua @ 0041e900 */
void dec_c87_lua(unsigned long opw, long *dec)
{
  dec_ea6((dec + 22),opw >> 8 & 0x3f);
  dec[26] = 1;
  dec[27] = 0xc;
  dec[28] = S32(d_4bfc80[((opw & 0x3f))]);
  dec[0] = 0x17;
}

/* dec_tcc @ 0041e950 */
void dec_tcc(unsigned long opw, long *dec)
{
  long iVar1;
  
  dec_flag_nomove(dec);
  dec[2] = 0xc;
  dec[3] = S32(d_4bffc0[((opw >> 4 & 7))]);
  dec[7] = 0xc;
  iVar1 = d_4c0000[((opw >> 3 & 1))];
  dec[8] = S32(iVar1);
  if (dec[3] == iVar1) {
    dec[3] = 5;
  }
  if ((opw & 0x10000) != 0) {
    dec[22] = 0xc;
    dec[23] = S32(d_4bfc80[((opw >> 8 & 7 | 0x10))]);
    dec[27] = 0xc;
    dec[28] = S32(d_4bfc80[((opw & 7 | 0x10))]);
  }
  dec[0] = 0x28;
  dec[42] = S32(opw >> 0xc & 0xf);
}

/* dec_div @ 0041ea00 */
void dec_div(unsigned long opw, long *dec)
{
  dec_flag_nomove(dec);
  dec[2] = 0xc;
  dec[3] = S32(d_4c0008[((opw >> 4 & 3))]);
  dec[7] = 0xc;
  dec[8] = S32(d_4c0000[((opw >> 3 & 1))]);
  dec[0] = 0x3f;
}

/* dec_incdec @ 0041ea50 */
void dec_incdec(unsigned long opw, long *dec)
{
  dec_flag_nomove(dec);
  dec[2] = 0xc;
  dec[3] = S32(d_4c0000[((opw & 1))]);
  dec[0] = S32((-((opw & 2) != 0) & 0xfffffffa) + 0x44);
}

/* dec_shift_imm @ 0041ea90 */
void dec_shift_imm(unsigned long opw, long *dec)
{
  dec_flag_nomove(dec);
  dec[2] = 10;
  dec[4] = S32(opw >> 1 & 0x3f);
  dec[7] = 0xc;
  dec[8] = S32(d_4c0000[((opw >> 7 & 1))]);
  dec[12] = 0xc;
  dec[13] = S32(d_4c0000[((opw & 1))]);
  dec[0] = S32(0x38 - ((opw & 0x100) != 0));
}

/* dec_shift_reg @ 0041eaf0 */
void dec_shift_reg(unsigned long opw, long *dec)
{
  dec_flag_nomove(dec);
  dec[2] = 0xc;
  dec[3] = S32(d_4c0028[((opw >> 1 & 7))]);
  dec[7] = 0xc;
  dec[8] = S32(d_4c0000[((opw >> 4 & 1))]);
  dec[12] = 0xc;
  dec[13] = S32(d_4c0000[((opw & 1))]);
  dec[0] = S32(((opw & 0x20) != 0) + 0x37);
}

/* dec_lsl_lsr_imm @ 0041eb60 */
void dec_lsl_lsr_imm(unsigned long opw, long *dec)
{
  dec_flag_nomove(dec);
  dec[2] = 10;
  dec[4] = S32(opw >> 1 & 0x1f);
  dec[7] = 0xc;
  dec[8] = S32(d_4c0000[((opw & 1))]);
  dec[0] = S32((opw & 0x40 | 0x1180) >> 6);
}

/* dec_lsl_lsr_reg @ 0041ebb0 */
void dec_lsl_lsr_reg(unsigned long opw, long *dec)
{
  dec_flag_nomove(dec);
  dec[2] = 0xc;
  dec[3] = S32(d_4c0028[((opw >> 1 & 7))]);
  dec[7] = 0xc;
  dec[8] = S32(d_4c0000[((opw & 1))]);
  dec[0] = S32((opw & 0x20 | 0x8c0) >> 5);
}

/* dec_insert_reg @ 0041ec70 */
void dec_insert_reg(unsigned long opw, long *dec)
{
  dec_flag_nomove(dec);
  dec[2] = 0xc;
  dec[3] = S32(d_4c0028[((opw >> 1 & 7))]);
  dec[7] = 0xc;
  dec[8] = S32(d_4c0048[((opw >> 4 & 7))]);
  dec[12] = 0xc;
  dec[13] = S32(d_4c0000[((opw & 1))]);
  dec[0] = 0x45;
}

/* dec_normf_merge @ 0041ecd0 */
void dec_normf_merge(unsigned long opw, long *dec)
{
  dec_flag_nomove(dec);
  dec[2] = 0xc;
  dec[3] = S32(d_4c0028[((opw >> 1 & 7))]);
  dec[7] = 0xc;
  dec[8] = S32(d_4c0000[((opw & 1))]);
  dec[0] = S32((-((opw & 0x80) != 0) & 0xfffffffa) + 0x53);
}

/* dec_clb @ 0041ed20 */
void dec_clb(unsigned long opw, long *dec)
{
  dec_flag_nomove(dec);
  dec[2] = 0xc;
  dec[3] = S32(d_4c0000[((opw >> 1 & 1))]);
  dec[7] = 0xc;
  dec[8] = S32(d_4c0000[((opw & 1))]);
  dec[0] = 0x39;
}

/* dec_alu_imm_short @ 0041ed70 */
void dec_alu_imm_short(unsigned long opw, long *dec)
{
  dec_flag_nomove(dec);
  dec[2] = 10;
  dec[4] = S32(opw >> 8 & 0x3f);
  dec[7] = 0xc;
  dec[8] = S32(d_4c0000[((opw >> 3 & 1))]);
  dec[0] = S32(d_4c0118[((opw & 7))]);
}

/* dec_alu_imm_long @ 0041edc0 */
void dec_alu_imm_long(unsigned long opw, long *dec)
{
  dec_flag_nomove(dec);
  dec[2] = 10;
  dec[4] = S32(dec_extword);
  dec[7] = 0xc;
  dec[8] = S32(d_4c0000[((opw >> 3 & 1))]);
  dec[0] = S32(d_4c0118[((opw & 7))]);
  dec_uses_extword = 1;
}

/* dec_cmpu @ 0041ee20 */
void dec_cmpu(unsigned long opw, long *dec)
{
  long iVar1;
  
  dec_flag_nomove(dec);
  dec[2] = 0xc;
  dec[3] = S32(d_4c0068);
  dec[7] = 0xc;
  iVar1 = d_4c0000[((opw & 1))];
  dec[8] = S32(iVar1);
  if (dec[3] == iVar1) {
    dec[3] = 5;
  }
  dec[0] = 0x3d;
}

/* dec_mpy_reg @ 0041ee80 */
void dec_mpy_reg(unsigned long opw, long *dec)
{
  dec_flag_nomove(dec);
  dec[2] = 0xc;
  dec[3] = S32(d_4bffe0[((opw >> 4 & 3))]);
  dec[7] = 10;
  dec[9] = S32(opw >> 8 & 0x1f);
  dec[12] = 0xc;
  dec[13] = S32(d_4c0000[((opw >> 3 & 1))]);
  dec[0] = S32(d_4c0148[((opw & 3))]);
  dec[44] = S32((-((opw & 4) != 0) & 0xfffffffe) + 1);
}

/* dec_mac_su @ 0041ef00 */
void dec_mac_su(unsigned long opw, long *dec)
{
  long iVar1;
  
  dec_flag_nomove(dec);
  dec[2] = 0xc;
  dec[3] = S32(d_4c0098[((opw & 0xf))]);
  dec[7] = 0xc;
  dec[8] = S32(d_4c00d8[((opw & 0xf))]);
  dec[12] = 0xc;
  dec[13] = S32(d_4c0000[((opw >> 5 & 1))]);
  if ((opw & 0x200) == 0) {
    iVar1 = 0x40;
  }
  else {
    iVar1 = (-((opw & 0x100) != 0) & 6) + 0x48;
  }
  dec[0] = S32(iVar1);
  dec[44] = S32((-((opw >> 4 & 1) != 0) & 0xfffffffe) + 1);
  dec[43] =
       dec[43] |
       d_4c0088[((((opw & 0x100 | opw >> 1 & 0x100) >> 1 | opw & 0x40) >> 6))];
}

/* dec_mpyi @ 0041efc0 */
void dec_mpyi(unsigned long opw, long *dec)
{
  dec_flag_nomove(dec);
  dec[2] = 10;
  dec[4] = S32(dec_extword);
  dec[7] = 0xc;
  dec[8] = S32(d_4bfff0[((opw >> 4 & 3))]);
  dec[12] = 0xc;
  dec[13] = S32(d_4c0000[((opw >> 3 & 1))]);
  dec[0] = S32(d_4c0138[((opw & 3))]);
  dec[44] = S32((-((opw & 4) != 0) & 0xfffffffe) + 1);
  dec_uses_extword = 1;
}

/* dec_insert_imm @ 0041f0b0 */
void dec_insert_imm(unsigned long opw, long *dec)
{
  dec_flag_nomove(dec);
  dec[2] = 10;
  dec[4] = S32(dec_extword);
  dec[7] = 0xc;
  dec[8] = S32(d_4c0048[((opw >> 4 & 7))]);
  dec[12] = 0xc;
  dec[13] = S32(d_4c0000[((opw & 1))]);
  dec[0] = 0x45;
  dec_uses_extword = 1;
}

/* dec_c91_norm @ 0041f110 */
void dec_c91_norm(unsigned long opw, long *dec)
{
  dec[2] = 0xc;
  dec[3] =
       d_4bfc80[(((unsigned char)(opw >> 8) & 7 | 0x10))];
  dec[7] = 0xc;
  dec[8] = S32(d_4c0000[((opw >> 3 & 1))]);
  dec_flag_nomove(dec);
  dec[0] = 0x1a;
}

/* dec_c95_ori @ 0041f160 */
void dec_c95_ori(unsigned long opw, long *dec)
{
  dec[22] = 10;
  dec[24] = S32(opw >> 8 & 0xff);
  dec[27] = 0xc;
  dec[28] = S32(d_4c0018[((opw & 3))]);
  dec[0] = 0x1b;
}

/* dec_c96_andi @ 0041f1a0 */
void dec_c96_andi(unsigned long opw, long *dec)
{
  dec[22] = 10;
  dec[24] = S32(opw >> 8 & 0xff);
  dec[27] = 0xc;
  dec[28] = S32(d_4c0018[((opw & 3))]);
  dec[0] = 1;
}

/* dec_c97_enddo @ 0041f1e0 */
void dec_c97_enddo(unsigned long opw, long *dec)
{
  dec[0] = 0xc;
}

/* dec_c98_stop @ 0041f1f0 */
void dec_c98_stop(unsigned long opw, long *dec)
{
  dec[0] = 0x27;
}

/* dec_c99_wait @ 0041f200 */
void dec_c99_wait(unsigned long opw, long *dec)
{
  dec[0] = 0x29;
}

/* dec_c100_reset @ 0041f210 */
void dec_c100_reset(unsigned long opw, long *dec)
{
  dec[0] = 0x24;
}

/* dec_c104_trap @ 0041f220 */
void dec_c104_trap(unsigned long opw, long *dec)
{
  dec[0] = 0x2a;
}

/* dec_c107_nop @ 0041f230 */
void dec_c107_nop(unsigned long opw, long *dec)
{
  dec[0] = 0x19;
}

/* dec_c106_rti @ 0041f240 */
void dec_c106_rti(unsigned long opw, long *dec)
{
  dec[0] = 0x25;
}

/* dec_c101_rts @ 0041f250 */
void dec_c101_rts(unsigned long opw, long *dec)
{
  dec[0] = 0x26;
}

/* dec_c63_pm @ 0041f260 */
void dec_c63_pm(unsigned long opw, long *dec)
{
  unsigned long uVar1;
  
  uVar1 = (opw >> 8 & 0x100 | 0x40) >> 6;
  dec_alu(opw,dec);
  dec[22] = 0xc;
  dec[23] = S32(uVar1);
  dec[30] = 1;
  dec_ea6((dec + 27),opw >> 8 & 0x3f);
  dec[32] = 0xc;
  dec[33] = 0x31;
  dec[37] = 0xc;
  dec[38] = S32(uVar1);
}

/* dec_c62_pm @ 0041f2e0 */
void dec_c62_pm(unsigned long opw, long *dec)
{
  unsigned long uVar1;
  
  uVar1 = (opw >> 8 & 0x100 | 0x40) >> 6;
  dec_alu(opw,dec);
  dec[22] = 0xc;
  dec[23] = 0x34;
  dec[27] = 0xc;
  dec[28] = S32(uVar1);
  dec[32] = 0xc;
  dec[33] = S32(uVar1);
  dec[40] = 2;
  dec_ea6((dec + 37),opw >> 8 & 0x3f);
}

/* dec_c28_btst @ 0041f350 */
void dec_c28_btst(unsigned long opw, long *dec)
{
  dec_bit_reg(opw,dec);
  dec[0] = 6;
}

/* dec_c29_bchg @ 0041f370 */
void dec_c29_bchg(unsigned long opw, long *dec)
{
  dec_bit_reg(opw,dec);
  dec[0] = 2;
}

/* dec_c46_bset @ 0041f390 */
void dec_c46_bset(unsigned long opw, long *dec)
{
  dec_bit_reg(opw,dec);
  dec[0] = 5;
}

/* dec_c47_bclr @ 0041f3b0 */
void dec_c47_bclr(unsigned long opw, long *dec)
{
  dec_bit_reg(opw,dec);
  dec[0] = 3;
}

/* dec_c93_debug @ 0041f3d0 */
void dec_c93_debug(unsigned long opw, long *dec)
{
  if ((opw & 0x100) != 0) {
    dec[42] = S32(opw & 0xf);
  }
  dec[0] = 7;
}

/* dec_c105_illegal @ 0041f3f0 */
void dec_c105_illegal(unsigned long opw, long *dec)
{
  dec[0] = 0xf;
}

/* dec_h41f400 @ 0041f400 */
void dec_h41f400(unsigned long opw, long *dec)
{
  dec_do_ea(opw,dec);
  dec[0] = 10;
}

/* dec_h41f420 @ 0041f420 */
void dec_h41f420(unsigned long opw, long *dec)
{
  dec_do_imm(opw,dec);
  dec[0] = 10;
}

/* dec_h41f440 @ 0041f440 */
void dec_h41f440(unsigned long opw, long *dec)
{
  dec_do_aa(opw,dec);
  dec[0] = 10;
}

/* dec_h41f460 @ 0041f460 */
void dec_h41f460(unsigned long opw, long *dec)
{
  dec_do_reg(opw,dec);
  dec[0] = 10;
}

/* dec_h41f480 @ 0041f480 */
void dec_h41f480(unsigned long opw, long *dec)
{
  long uVar1;
  unsigned long uVar2;
  
  uVar2 = (opw >> 3 & 0x700 | opw & 0xf0) >> 4;
  if ((opw >> 3 & 0x400) != 0) {
    uVar2 = uVar2 | 0xffffffc0;
  }
  dec[22] = 0xd;
  uVar1 = d_4bfc80[((opw >> 8 & 7 | 0x10))];
  dec[24] = S32(uVar2);
  dec[23] = S32(uVar1);
  dec[27] = 0xc;
  dec[28] = S32(d_4bfc80[((opw & 0xf | 0x10))]);
  dec[0] = 0x17;
}

/* dec_h41f4f0 @ 0041f4f0 */
void dec_h41f4f0(unsigned long opw, long *dec)
{
  dec[22] = 0xc;
  dec[23] = S32(d_4bfc80[(((opw & 0x700 | 0x1000) >> 8))]);
  dec[27] = 0xc;
  dec[28] = S32(d_4bfc80[((opw & 0x3f))]);
  dec[0] = 0x16;
}

/* dec_h41f540 @ 0041f540 */
void dec_h41f540(unsigned long opw, long *dec)
{
  dec[22] = 10;
  dec[24] = S32(dec_extword);
  dec_uses_extword = 1;
  dec[27] = 0xc;
  dec[28] = S32(d_4bfc80[((opw & 0x3f))]);
  dec[0] = 0x16;
}

/* dec_h41f580 @ 0041f580 */
void dec_h41f580(unsigned long opw, long *dec)
{
  opw = opw & 3;
  if (opw == 1) {
    dec[0] = 0x1d;
  }
  else {
    if (opw == 2) {
      dec[0] = 0x1e;
      dec[43] = S32(dec[43] | 0x100);
      return;
    }
    if (opw == 3) {
      dec[0] = 0x1c;
      dec[43] = S32(dec[43] | 0x100);
      return;
    }
  }
  dec[43] = S32(dec[43] | 0x100);
}

/* dec_h41f5e0 @ 0041f5e0 */
void dec_h41f5e0(unsigned long opw, long *dec)
{
  dec[0] = S32((~opw & 1 | 0x10) << 1);
  dec[43] = S32(dec[43] | 0x100);
  dec[22] = 9;
  dec[24] = S32(dec_extword);
  dec_uses_extword = 1;
}

/* dec_h41f620 @ 0041f620 */
void dec_h41f620(unsigned long opw, long *dec)
{
  dec[42] = S32(opw & 0xf);
  dec[0] = S32((-((opw & 0x200) != 0) & 0xffffffda) + 0x2a);
}

/* dec_h41f7b0 @ 0041f7b0 */
void dec_h41f7b0(unsigned long opw, long *dec)
{
  dec[0] = S32((-((opw & 0x10000) != 0) & 0xfffffffe) + 0x21);
  dec[43] = S32(dec[43] | 0x100);
  dec_ea6(dec + 0x16,opw >> 8 & 0x3f);
}

/* dec_h41f7f0 @ 0041f7f0 */
void dec_h41f7f0(unsigned long opw, long *dec)
{
  dec[22] = 0xc;
  dec[23] = S32(d_4bfc80[(((opw & 0x700 | 0x1000) >> 8))]);
  dec[27] = 0xc;
  dec[28] = S32(d_4bfc80[((opw & 7 | 0x10))]);
  dec[0] = 0x28;
  dec[42] = S32(opw >> 0xc & 0xf);
}

/* dec_alu_cc @ 0041f850 */
void dec_alu_cc(unsigned long opw, long *dec)
{
  dec_alu(opw,dec);
  dec[42] = S32(opw >> 8 & 0xf);
  dec[1] = S32(((opw & 0x1000) != 0) + 0xd);
}

/* dec_h41f890 @ 0041f890 */
void dec_h41f890(unsigned long opw, long *dec)
{
  dec_bit_pp(opw,dec,1);
  dec[0] = 6;
}

/* dec_h41f8b0 @ 0041f8b0 */
void dec_h41f8b0(unsigned long opw, long *dec)
{
  dec_bit_pp(opw,dec,1);
  dec[0] = 2;
}

/* dec_h41f8d0 @ 0041f8d0 */
void dec_h41f8d0(unsigned long opw, long *dec)
{
  dec_bit_pp(opw,dec,1);
  dec[0] = 5;
}

/* dec_h41f8f0 @ 0041f8f0 */
void dec_h41f8f0(unsigned long opw, long *dec)
{
  dec_bit_pp(opw,dec,1);
  dec[0] = 3;
}

/* dec_h41f910 @ 0041f910 */
void dec_h41f910(unsigned long opw,unsigned long *dec)
{
  dec[22] = 9;
  dec[24] = S32(dec_extword);
  dec_uses_extword = 1;
  dec[0] = S32((~opw & 1) << 1 | 9);
}

/* dec_h41f940 @ 0041f940 */
void dec_h41f940(unsigned long opw, long *dec)
{
  unsigned long uVar1;
  unsigned long ea6;
  
  dec[30] = 1;
  uVar1 = (opw >> 8 & 0xffff) >> 8 & 1;
  ea6 = opw >> 8 & 0x3f;
  dec_ea6(dec + 0x1b,ea6);
  dec[22] = 0xc;
  dec[23] = S32(d_4c0000[(uVar1)]);
  dec[40] = 2;
  dec_ea6(dec + 0x25,ea6);
  dec[32] = 0xc;
  dec[34] = S32(((opw & 0x10) != 0));
  dec[33] = S32(d_4c0000[(uVar1)]);
  dec[44] = S32(opw & 0x10);
  dec[0] = 0x18;
}
