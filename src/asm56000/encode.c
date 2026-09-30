/*
 * ASM56000.EXE (CLAS56 v6.3.0) - encode.c 1.13: opcode field encoders.
 *
 * Pure bit packing: every xxx_code(reg) maps a register id (or mode) to a
 * manual field value and calls fatal("<FIELD> encoding failure") otherwise;
 * every enc_* inserts fields into word 0 of the INSN record.  The last
 * encoders of the original module (enc_pm_ry_w ... qq_code) live in error.c
 * where the executable's address map put them.
 *
 * OPERAND words: [0] mode [1] space [2] fwd [3] force [4] value [5] reg
 * [6] sect; INSN words: [0] nwords [1] word0 [2] word1.
 */
#include <stdio.h>
#include <string.h>

#include "asm56000.h"

extern void fatal(char *msg);

#define WORDS(p)  ((unsigned long *)(p))
#define IW0(i)    (WORDS(i)[1])
#define OMODE(o)  ((int)WORDS(o)[0])
#define OSPACE(o) ((int)WORDS(o)[1])
#define OVALUE(o) (WORDS(o)[4])
#define OREG(o)   ((int)WORDS(o)[5])

static unsigned long get_word(void *p, unsigned offset)
{
    return *(unsigned long *)((char *)p + offset);
}

static void put_word(void *p, unsigned offset, unsigned long value)
{
    *(unsigned long *)((char *)p + offset) = value;
}

/* 004112e0 */
void set_ext_word(void *insn, void *op, int minus1)
{
    unsigned long mode;
    char *src;
    char *dst;
    unsigned long n;

    mode = get_word(op, ASM56000_OP_MODE);
    if (mode != 14UL && mode != 9UL)
        return;

    put_word(insn, ASM56000_INSN_WORD1, get_word(op, ASM56000_OP_VALUE));
    src = *(char **)((char *)op + ASM56000_OP_CFORM);
    if (src != (char *)0) {
        *(char **)((char *)insn + ASM56000_INSN_CFORM1) = src;
        *(char **)((char *)op + ASM56000_OP_CFORM) = (char *)0;
    }
    put_word(insn, ASM56000_INSN_NWORDS, 2UL);

    if (!minus1)
        return;
    if (get_word(insn, ASM56000_INSN_WORD1) != 0UL)
        put_word(insn, ASM56000_INSN_WORD1,
                 get_word(insn, ASM56000_INSN_WORD1) - 1UL);
    src = *(char **)((char *)insn + ASM56000_INSN_CFORM1);
    if (src != (char *)0) {
        n = (unsigned long)strlen(src);
        dst = (char *)xmalloc(n + 8UL);
        sprintf(dst, "%s-1", src);
        xfree(src);
        *(char **)((char *)insn + ASM56000_INSN_CFORM1) = dst;
    }
}

/* ------------------------------------------------------------------ */
/* field codes                                                         */

int ee_code(int reg)
{
    if (reg == 0x2a)
        return 2;
    if (reg == 0x31)
        return 0;
    if (reg == 0x32)
        return 1;
    fatal("EE encoding failure");
    return 0;
}

int d_code(int reg)
{
    if (reg == 2)
        return 0;
    if (reg == 3)
        return 1;
    fatal("D encoding failure");
    return 0;
}

int jjj_code(int reg)
{
    switch (reg) {
    case 2:
    case 3: return 0;
    case 4: return 4;
    case 5: return 5;
    case 6: return 6;
    case 7: return 7;
    default:
        fatal("DXY encoding failure");
        return 0;
    }
}

int rrr_code(int mode, int reg)
{
    if (mode == 14)
        return 0;
    if (mode == 9)
        return 4;
    if (reg >= 14 && reg <= 21)
        return reg - 14;
    fatal("RRR encoding failure");
    return 0;
}

int mmm_code(int mode)
{
    switch (mode) {
    case 2: return 4;
    case 3: return 3;
    case 4: return 2;
    case 5: return 1;
    case 6: return 0;
    case 7: return 5;
    case 8: return 7;
    case 9:
    case 14: return 6;
    default:
        fatal("MMM encoding failure");
        return 0;
    }
}

int s_code(int space)
{
    return space == 2;
}

int ccc_code(int reg)
{
    switch (reg) {
    case 0x2a: return 2;
    case 0x2b: return 1;
    case 0x2c: return 6;
    case 0x2d: return 7;
    case 0x2e: return 4;
    case 0x2f: return 5;
    case 0x30: return 3;
    default:
        fatal("CCC encoding failure");
        return 0;
    }
}

int dd_code(int reg)
{
    switch (reg) {
    case 4: return 0;
    case 5: return 2;
    case 6: return 1;
    case 7: return 3;
    default:
        fatal("DD encoding failure");
        return 0;
    }
}

int ddd_code(int reg)
{
    switch (reg) {
    case 2: return 6;
    case 3: return 7;
    case 8: return 0;
    case 9: return 1;
    case 10: return 4;
    case 11: return 5;
    case 12: return 2;
    case 13: return 3;
    default:
        fatal("DDD encoding failure");
        return 0;
    }
}

int fff_code(int reg)
{
    if (reg >= 0x1e && reg <= 0x25)
        return reg - 0x1e;
    fatal("FFF encoding failure");
    return 0;
}

int nnn_code(int reg)
{
    if (reg >= 0x16 && reg <= 0x1d)
        return reg - 0x16;
    fatal("NNN encoding failure");
    return 0;
}

int ddddd_code(int reg)
{
    switch (reg) {
    case 2: case 3: case 8: case 9: case 10: case 11: case 12: case 13:
        return ddd_code(reg) + 8;
    case 4: case 5: case 6: case 7:
        return dd_code(reg) + 4;
    case 0xe: case 0xf: case 0x10: case 0x11: case 0x12: case 0x13:
    case 0x14: case 0x15:
        return rrr_code(0, reg) + 0x10;
    case 0x16: case 0x17: case 0x18: case 0x19: case 0x1a: case 0x1b:
    case 0x1c: case 0x1d:
        return nnn_code(reg) + 0x18;
    default:
        fatal("DDDDD encoding failure");
        return 0;
    }
}

int d6_code(int reg)
{
    if (reg >= 2 && reg <= 0x1d)
        return ddddd_code(reg);
    if (reg >= 0x1e && reg <= 0x25)
        return fff_code(reg) + 0x20;
    if (reg >= 0x2a && reg <= 0x30)
        return ccc_code(reg) + 0x38;
    fatal("D6 encoding failure");
    return 0;
}

int xx_code(int reg)
{
    switch (reg) {
    case 2: return 2;
    case 3: return 3;
    case 4: return 0;
    case 6: return 1;
    default:
        fatal("XX encoding failure");
        return 0;
    }
}

int yy_code(int reg)
{
    switch (reg) {
    case 2: return 2;
    case 3: return 3;
    case 5: return 0;
    case 7: return 1;
    default:
        fatal("YY encoding failure");
        return 0;
    }
}

int x_code(int reg)
{
    if (reg == 4)
        return 0;
    if (reg == 6)
        return 1;
    fatal("X encoding failure");
    return 0;
}

/* ------------------------------------------------------------------ */
/* ALU and control instruction encoders                                */

#define IB(w, v, pos, width) \
    insert_bits((unsigned long)(w), (unsigned long)(v), (pos), (width))

void enc_andi(void *insn, void *imm, void *dst)
{
    unsigned long w;

    w = IB(IW0(insn) | 0xb8UL, ee_code(OREG(dst)), 0, 2);
    IW0(insn) = w;
    encode_field(insn, imm, 8, 8);
}

void enc_div(void *insn, void *src, void *dst)
{
    unsigned long w;

    w = IB(IW0(insn), d_code(OREG(dst)), 3, 1);
    w = IB(w, jjj_code(OREG(src)), 4, 2);
    IW0(insn) = w;
}

void enc_norm(void *insn, void *src, void *dst)
{
    unsigned long w;

    w = IB(IW0(insn), d_code(OREG(dst)), 3, 1);
    w = IB(w, rrr_code(OMODE(src), OREG(src)), 8, 3);
    IW0(insn) = w;
}

void enc_loop_ea(void *insn, void *op)
{
    unsigned long w;

    w = IB(IW0(insn), s_code(OSPACE(op)), 6, 1);
    w = IB(w, rrr_code(OMODE(op), OREG(op)), 8, 3);
    w = IB(w, mmm_code(OMODE(op)), 11, 3);
    w = IB(w, 1, 14, 1);
    IW0(insn) = w;
}

void enc_loop_abs(void *insn, void *op)
{
    IW0(insn) = IB(IW0(insn), s_code(OSPACE(op)), 6, 1);
    encode_field(insn, op, 8, 6);
}

void enc_loop_reg(void *insn, void *op)
{
    unsigned long w;

    w = IB(IW0(insn), d6_code(OREG(op)), 8, 6);
    w = IB(w, 3, 14, 2);
    IW0(insn) = w;
}

static long sar(long v, int n)
{
    if (v >= 0L)
        return v >> n;
    return ~((~v) >> n);
}

void enc_loop_imm(void *insn, void *op)
{
    unsigned long w;
    char *cform;
    char text[32];
    char shifted[1100];
    char *e1;
    char *e2;

    w = IB(IW0(insn), 1, 7, 1);
    cform = *(char **)((char *)op + ASM56000_OP_CFORM);
    if (cform == (char *)0) {
        w = IB(w, sar((long)OVALUE(op), 8), 0, 4);
        w = IB(w, OVALUE(op), 8, 8);
        IW0(insn) = w;
    } else {
        sprintf(text, "$%06lx", w);
        strcpy(text, str_upper(text));
        sprintf(shifted, "(%s>>8)", cform);
        e1 = insert_bits_expr(text, shifted, 0, 4);
        e2 = insert_bits_expr(e1, cform, 8, 8);
        *(char **)((char *)insn + ASM56000_INSN_CFORM0) = e2;
        xfree(e1);
        xfree(cform);
        *(char **)((char *)op + ASM56000_OP_CFORM) = (char *)0;
    }
}

void enc_do_ea(void *insn, void *op, void *target)
{
    enc_loop_ea(insn, op);
    set_ext_word(insn, target, 1);
}

void enc_do_abs(void *insn, void *op, void *target)
{
    enc_loop_abs(insn, op);
    set_ext_word(insn, target, 1);
}

void enc_do_reg(void *insn, void *op, void *target)
{
    enc_loop_reg(insn, op);
    set_ext_word(insn, target, 1);
}

void enc_do_imm(void *insn, void *op, void *target)
{
    enc_loop_imm(insn, op);
    set_ext_word(insn, target, 1);
}

void enc_jmp_abs(void *insn, void *op)
{
    IW0(insn) = IB(IW0(insn), 1, 0x12, 1);
    encode_field(insn, op, 0, 12);
}

void enc_jmp_ea(void *insn, void *op)
{
    unsigned long w;

    w = IB(IW0(insn), 1, 7, 1);
    w = IB(w, rrr_code(OMODE(op), OREG(op)), 8, 3);
    w = IB(w, mmm_code(OMODE(op)), 11, 3);
    w = IB(w, 3, 14, 2);
    w = IB(w, 1, 0x11, 1);
    IW0(insn) = w;
    set_ext_word(insn, op, 0);
}

void enc_jcc_abs(void *insn, void *op)
{
    IW0(insn) = IB(IW0(insn), 1, 0x12, 1);
    encode_field(insn, op, 0, 12);
}

void enc_jcc_ea(void *insn, void *op)
{
    unsigned long w;

    w = IB(IW0(insn) | ((IW0(insn) >> 12) & 0xfUL), 5, 5, 3);
    w = IB(w, rrr_code(OMODE(op), OREG(op)), 8, 3);
    w = IB(w, mmm_code(OMODE(op)), 11, 3);
    w = IB(w, 3, 14, 2);
    IW0(insn) = w;
    set_ext_word(insn, op, 0);
}

void enc_tcc_r(void *insn, void *s1, void *d1, void *s2, void *d2)
{
    unsigned long w;

    w = IB(IW0(insn), rrr_code(OMODE(d2), OREG(d2)), 0, 3);
    w = IB(w, d_code(OREG(d1)), 3, 1);
    w = IB(w, jjj_code(OREG(s1)), 4, 3);
    w = IB(w, rrr_code(OMODE(s2), OREG(s2)), 8, 3);
    w = IB(w, 1, 0x10, 1);
    IW0(insn) = w;
}

void enc_tcc(void *insn, void *s1, void *d1)
{
    unsigned long w;

    w = IB(IW0(insn), d_code(OREG(d1)), 3, 1);
    w = IB(w, jjj_code(OREG(s1)), 4, 3);
    IW0(insn) = w;
}

/* ------------------------------------------------------------------ */
/* bit instructions                                                    */

void enc_bit_ea(void *insn, void *bitno, void *op)
{
    unsigned long w;

    w = IB(IW0(insn), s_code(OSPACE(op)), 6, 1);
    w = IB(w, rrr_code(OMODE(op), OREG(op)), 8, 3);
    w = IB(w, mmm_code(OMODE(op)), 11, 3);
    w = IB(w, 1, 14, 1);
    IW0(insn) = w;
    encode_field(insn, bitno, 0, 5);
    set_ext_word(insn, op, 0);
}

void enc_bit_reg(void *insn, void *bitno, void *op)
{
    unsigned long w;

    w = IB(IW0(insn), 0x301, 6, 10);
    w = IB(w, d6_code(OREG(op)), 8, 6);
    IW0(insn) = w;
    encode_field(insn, bitno, 0, 5);
}

void enc_bit_abs(void *insn, void *bitno, void *op)
{
    unsigned long w;
    char text[32];
    char *b_cform;
    char *o_cform;
    char *e1;
    char *e2;

    w = IB(IW0(insn), s_code(OSPACE(op)), 6, 1);
    b_cform = *(char **)((char *)bitno + ASM56000_OP_CFORM);
    o_cform = *(char **)((char *)op + ASM56000_OP_CFORM);
    if (b_cform == (char *)0)
        w = IB(w, OVALUE(bitno), 0, 5);
    if (o_cform == (char *)0)
        w = IB(w, OVALUE(op), 8, 6);
    IW0(insn) = w;
    sprintf(text, "$%06lx", w);
    strcpy(text, str_upper(text));
    if (b_cform != (char *)0 && o_cform == (char *)0) {
        e1 = insert_bits_expr(text, b_cform, 0, 5);
        *(char **)((char *)insn + ASM56000_INSN_CFORM0) = e1;
        xfree(b_cform);
    } else if (o_cform != (char *)0 && b_cform == (char *)0) {
        e1 = insert_bits_expr(text, o_cform, 8, 6);
        *(char **)((char *)insn + ASM56000_INSN_CFORM0) = e1;
        xfree(o_cform);
    } else if (b_cform != (char *)0 && o_cform != (char *)0) {
        e1 = insert_bits_expr(text, b_cform, 0, 5);
        e2 = insert_bits_expr(e1, o_cform, 8, 6);
        *(char **)((char *)insn + ASM56000_INSN_CFORM0) = e2;
        xfree(b_cform);
        xfree(o_cform);
        xfree(e1);
    }
    *(char **)((char *)bitno + ASM56000_OP_CFORM) = (char *)0;
    *(char **)((char *)op + ASM56000_OP_CFORM) = (char *)0;
}

void enc_bit_pp(void *insn, void *bitno, void *op)
{
    IW0(insn) = IB(IW0(insn), 1, 0xf, 1);
    enc_bit_abs(insn, bitno, op);
}

void enc_jbit_ea(void *insn, void *bitno, void *op, void *target)
{
    enc_bit_ea(insn, bitno, op);
    set_ext_word(insn, target, 0);
}

void enc_jbit_reg(void *insn, void *bitno, void *op, void *target)
{
    unsigned long w;

    w = IB(IW0(insn), 0x180, 7, 9);
    w = IB(w, d6_code(OREG(op)), 8, 6);
    IW0(insn) = w;
    encode_field(insn, bitno, 0, 5);
    set_ext_word(insn, target, 0);
}

void enc_jbit_abs(void *insn, void *bitno, void *op, void *target)
{
    enc_bit_abs(insn, bitno, op);
    set_ext_word(insn, target, 0);
}

void enc_jbit_pp(void *insn, void *bitno, void *op, void *target)
{
    enc_bit_pp(insn, bitno, op);
    set_ext_word(insn, target, 0);
}

/* ------------------------------------------------------------------ */
/* MOVEP / MOVEC                                                       */

void enc_movep_reg(void *insn, void *pp, void *reg)
{
    unsigned long w;

    w = IB(IW0(insn), d6_code(OREG(reg)), 8, 6);
    w = IB(w, s_code(OSPACE(pp)), 0x10, 1);
    IW0(insn) = w;
    encode_field(insn, pp, 0, 6);
}

void enc_movep_mem(void *insn, void *pp, void *mem)
{
    unsigned long w;

    w = IB(IW0(insn), s_code(OSPACE(pp)), 0x10, 1);
    if (OSPACE(mem) == 0) {
        w = IB(w, 1, 6, 1);
    } else {
        w = IB(w, s_code(OSPACE(mem)), 6, 1);
        w = IB(w, 1, 7, 1);
    }
    w = IB(w, rrr_code(OMODE(mem), OREG(mem)), 8, 3);
    w = IB(w, mmm_code(OMODE(mem)), 11, 3);
    IW0(insn) = w;
    encode_field(insn, pp, 0, 6);
    set_ext_word(insn, mem, 0);
}

void enc_movep_reg_w(void *insn, void *reg, void *pp)
{
    IW0(insn) = IB(IW0(insn), 1, 0xf, 1);
    enc_movep_reg(insn, pp, reg);
}

void enc_movep_mem_w(void *insn, void *mem, void *pp)
{
    IW0(insn) = IB(IW0(insn), 1, 0xf, 1);
    enc_movep_mem(insn, pp, mem);
}

void enc_movec_ea(void *insn, void *creg, void *mem)
{
    unsigned long w;

    w = IB(IW0(insn) | 0x40000UL, d6_code(OREG(creg)), 0, 6);
    w = IB(w, s_code(OSPACE(mem)), 6, 1);
    w = IB(w, rrr_code(OMODE(mem), OREG(mem)), 8, 3);
    w = IB(w, mmm_code(OMODE(mem)), 11, 3);
    w = IB(w, 1, 14, 1);
    w = IB(w, 1, 0x10, 1);
    IW0(insn) = w;
    set_ext_word(insn, mem, 0);
}

void enc_movec_ea_w(void *insn, void *mem, void *creg)
{
    IW0(insn) = IB(IW0(insn), 1, 0xf, 1);
    enc_movec_ea(insn, creg, mem);
}

void enc_movec_imm(void *insn, void *imm, void *creg)
{
    unsigned long w;

    w = IB(IW0(insn) | 0x40000UL, d6_code(OREG(creg)), 0, 6);
    w = IB(w, 1, 7, 1);
    w = IB(w, 1, 0x10, 1);
    IW0(insn) = w;
    encode_field(insn, imm, 8, 8);
}

void enc_movec_reg(void *insn, void *creg, void *reg)
{
    unsigned long w;

    w = IB(IW0(insn) | 0x40000UL, d6_code(OREG(creg)), 0, 6);
    w = IB(w, 1, 7, 1);
    w = IB(w, d6_code(OREG(reg)), 8, 6);
    w = IB(w, 1, 14, 1);
    IW0(insn) = w;
}

void enc_movec_reg_w(void *insn, void *reg, void *creg)
{
    IW0(insn) = IB(IW0(insn), 1, 0xf, 1);
    enc_movec_reg(insn, creg, reg);
}

void enc_movec_abs(void *insn, void *creg, void *abs)
{
    unsigned long w;

    w = IB(IW0(insn) | 0x40000UL, d6_code(OREG(creg)), 0, 6);
    w = IB(w, s_code(OSPACE(abs)), 6, 1);
    w = IB(w, 1, 0x10, 1);
    IW0(insn) = w;
    encode_field(insn, abs, 8, 6);
}

void enc_movec_abs_w(void *insn, void *abs, void *creg)
{
    IW0(insn) = IB(IW0(insn), 1, 0xf, 1);
    enc_movec_abs(insn, creg, abs);
}

void enc_movec_ea2(void *insn, void *creg, void *mem)
{
    unsigned long w;

    w = IB(IW0(insn) | 0x40000UL, d6_code(OREG(creg)), 0, 6);
    w = IB(w, s_code(OSPACE(mem)), 6, 1);
    w = IB(w, rrr_code(OMODE(mem), OREG(mem)), 8, 3);
    w = IB(w, mmm_code(OMODE(mem)), 11, 3);
    w = IB(w, 1, 14, 1);
    w = IB(w, 1, 0x10, 1);
    IW0(insn) = w;
    set_ext_word(insn, mem, 0);
}

void enc_movec_ea2_w(void *insn, void *mem, void *creg)
{
    IW0(insn) = IB(IW0(insn), 1, 0xf, 1);
    enc_movec_ea2(insn, creg, mem);
}

/* ------------------------------------------------------------------ */
/* parallel moves                                                      */

void enc_pm_xy(void *insn, void *xreg, void *xmem, void *yreg, void *ymem)
{
    unsigned long w;

    w = IB(IW0(insn), rrr_code(OMODE(xmem), OREG(xmem)), 8, 3);
    w = IB(w, mmm_code(OMODE(xmem)), 11, 2);
    w = IB(w, rrr_code(OMODE(ymem), OREG(ymem)), 13, 2);
    w = IB(w, yy_code(OREG(yreg)), 16, 2);
    w = IB(w, xx_code(OREG(xreg)), 18, 2);
    w = IB(w, mmm_code(OMODE(ymem)), 20, 2);
    w = IB(w, 1, 0x17, 1);
    IW0(insn) = w;
}

void enc_pm_xy_wx(void *insn, void *xmem, void *xreg, void *yreg, void *ymem)
{
    IW0(insn) = IB(IW0(insn), 1, 0xf, 1);
    enc_pm_xy(insn, xreg, xmem, yreg, ymem);
}

void enc_pm_xy_wy(void *insn, void *xreg, void *xmem, void *ymem, void *yreg)
{
    IW0(insn) = IB(IW0(insn), 1, 0x16, 1);
    enc_pm_xy(insn, xreg, xmem, yreg, ymem);
}

void enc_pm_xy_wxy(void *insn, void *xmem, void *xreg, void *ymem, void *yreg)
{
    unsigned long w;

    w = IB(IW0(insn), 1, 0xf, 1);
    w = IB(w, 1, 0x16, 1);
    IW0(insn) = w;
    enc_pm_xy(insn, xreg, xmem, yreg, ymem);
}

void enc_pm_xr2(void *insn, void *acc, void *mem)
{
    unsigned long w;

    w = IB(IW0(insn), rrr_code(OMODE(mem), OREG(mem)), 8, 3);
    w = IB(w, mmm_code(OMODE(mem)), 11, 3);
    w = IB(w, s_code(OSPACE(mem)), 0xf, 1);
    w = IB(w, d_code(OREG(acc)), 0x10, 1);
    w = IB(w, 1, 0x13, 1);
    IW0(insn) = w;
}

void enc_pm_x_ea(void *insn, void *reg, void *mem)
{
    unsigned long w;
    unsigned long code;

    w = IB(IW0(insn), rrr_code(OMODE(mem), OREG(mem)), 8, 3);
    w = IB(w, mmm_code(OMODE(mem)), 11, 3);
    w = IB(w, 1, 14, 1);
    code = (unsigned long)ddddd_code(OREG(reg));
    w = IB(w, code, 0x10, 3);
    w = IB(w, (long)code >> 3, 0x14, 2);
    w = IB(w, 1, 0x16, 1);
    IW0(insn) = w;
    set_ext_word(insn, mem, 0);
}

void enc_pm_x_ea_w(void *insn, void *mem, void *reg)
{
    IW0(insn) = IB(IW0(insn), 1, 0xf, 1);
    enc_pm_x_ea(insn, reg, mem);
}

void enc_pm_y_ea(void *insn, void *reg, void *mem)
{
    IW0(insn) = IB(IW0(insn), 1, 0x13, 1);
    enc_pm_x_ea(insn, reg, mem);
}

void enc_pm_y_ea_w(void *insn, void *mem, void *reg)
{
    IW0(insn) = IB(IW0(insn), 1, 0xf, 1);
    enc_pm_y_ea(insn, reg, mem);
}

void enc_pm_x_abs(void *insn, void *reg, void *abs)
{
    unsigned long w;
    unsigned long code;

    code = (unsigned long)ddddd_code(OREG(reg));
    w = IB(IW0(insn), code, 0x10, 3);
    w = IB(w, (long)code >> 3, 0x14, 2);
    w = IB(w, 1, 0x16, 1);
    IW0(insn) = w;
    encode_field(insn, abs, 8, 6);
}

void enc_pm_x_abs_w(void *insn, void *abs, void *reg)
{
    IW0(insn) = IB(IW0(insn), 1, 0xf, 1);
    enc_pm_x_abs(insn, reg, abs);
}

void enc_pm_y_abs(void *insn, void *reg, void *abs)
{
    IW0(insn) = IB(IW0(insn), 1, 0x13, 1);
    enc_pm_x_abs(insn, reg, abs);
}

void enc_pm_y_abs_w(void *insn, void *abs, void *reg)
{
    IW0(insn) = IB(IW0(insn), 1, 0xf, 1);
    enc_pm_y_abs(insn, reg, abs);
}

void enc_pm_ry(void *insn, void *s1, void *d1, void *yreg, void *ymem)
{
    unsigned long w;

    w = IB(IW0(insn), rrr_code(OMODE(ymem), OREG(ymem)), 8, 3);
    w = IB(w, mmm_code(OMODE(ymem)), 11, 3);
    w = IB(w, 1, 14, 1);
    w = IB(w, yy_code(OREG(yreg)), 0x10, 2);
    w = IB(w, x_code(OREG(d1)), 0x12, 1);
    w = IB(w, d_code(OREG(s1)), 0x13, 1);
    w = IB(w, 1, 0x14, 1);
    IW0(insn) = w;
    set_ext_word(insn, ymem, 0);
}
