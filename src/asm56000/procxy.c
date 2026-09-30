/*
 * ASM56000.EXE (CLAS56 v6.3.0) - procxy.c 1.11: parallel data moves
 * (the X field and the Y field of an instruction line).
 *
 * do_xy() parses Op2Field (the X move) and Op3Field (the Y move) into four
 * operands: xs/xd (X field source/destination) and ys/yd (Y field), checks
 * them against the permission mask of the instruction and calls the
 * encode.c field encoders.  Return value 1 = ok, 0 = error (the caller
 * emits the words anyway).
 *
 * OPERAND words (see asm56000.h): [0] mode [1] space [2] fwd [3] force
 * [4] value [5] reg [6] sect.  *insn is the INSN record, word 0 = nwords.
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "asm56000.h"

#define optr CurInstrFieldMsg

#define MODE(o)  (((long *)(o))[0])
#define SPACE(o) (((long *)(o))[1])
#define FORCE(o) (((long *)(o))[3])
#define REG(o)   (((long *)(o))[5])
#define NWORDS(i) (((long *)(i))[0])

extern void fatal(char *msg);
extern char InLineReplay;
extern unsigned long ErrOnThisLine;
extern int do_check_end_range_err(int n);
extern char EmptyFieldText[];

#define FORCE_SHORT 0x2000000L

static long xy_pdst(unsigned long pm, void *insn, void *xs, void *xd);
static long xy_xsrc(unsigned long pm, void *insn, void *xs, void *xd,
                    void *ys, void *yd);
static long xy_ysrc(unsigned long pm, void *insn, void *xs, void *xd);
static long xy_lsrc(unsigned long pm, void *insn, void *xs, void *xd);
static long xy_psrc(unsigned long pm, void *insn, void *xs, void *xd);

/* 0042b12c: writing a control register sets hazard flags. */
int pseudo_check_move_class(int reg)
{
    switch (reg) {
    case 0x2b:
        HazardCur |= 0x288UL;
        return do_check_end_range_err(2) == 0;
    case 0x2c:
    case 0x2d:
        HazardCur |= 0x20cUL;
        return do_check_end_range_err(2) == 0;
    case 0x30:
        HazardCur |= 0x210UL;
        HazardCur |= 0x24cUL;
        return do_check_end_range_err(2) == 0;
    case 0x2e:
    case 0x2f:
        HazardCur |= 0x24cUL;
        return do_check_end_range_err(2) == 0;
    default:
        return 1;
    }
}

/* 0042b1e5: does the instruction allow this kind of parallel move? */
int pseudo_check_move_mask(unsigned long pm, unsigned long mask, void *insn)
{
    if ((pm & mask) == 0UL) {
        err("Instruction does not allow data movement specified");
        return 0;
    }
    if (insn != (void *)0) {
        if ((pm & 0x10UL) != 0UL)
            ((unsigned long *)insn)[1] = 0x40000UL;
        else if ((pm & 0x20UL) != 0UL)
            ((unsigned long *)insn)[1] = 0x70000UL;
    }
    return 1;
}

/* 0042b08d */
static int chk_xy_regs(long r1, long r2)
{
    switch (r1) {
    case 0xe: case 0xf: case 0x10: case 0x11:
        if (r2 < 0xe || r2 > 0x11)
            return 0;
        err("Invalid XY address register specification");
        return 1;
    case 0x12: case 0x13: case 0x14: case 0x15:
        if (r2 < 0x12 || r2 > 0x15)
            return 0;
        err("Invalid XY address register specification");
        return 1;
    default:
        return 0;
    }
}


/* register classes: destination register of an X move (dst reg id) */
#define IS_ALU_REG(r) ((r) >= 2 && (r) <= 0xd)

/* 00429b8a and friends need the encoders */

/* ------------------------------------------------------------------ */
/* 0042838d: X field "#short" source                                   */
static long xsrc_imm_short(unsigned long pm, void *insn, void *xs, void *xd,
                           void *ys, void *yd)
{
    if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
        return 0;
    if (!parse_operand(2UL, xd, 0x12, 0, 0, 0))
        return 0;
    switch (REG(xd)) {
    case 2: case 3: case 4: case 6:
        if (*Op3Field == '\0') {
            enc_pm_imm(insn, xs, xd);
        } else {
            optr = Op3Field;
            if (!parse_operand(1UL, ys, 1, 0, 0, 0))
                return 0;
            if (!parse_operand(0UL, yd, 2, 0, 0, 0))
                return 0;
            MODE(xs) = 9;
            if (FORCE(xs) != 0)
                warn("Cannot force short immediate with this parallel move");
            enc_pm_xr_w(insn, xs, xd, ys, yd);
        }
        break;
    case 5: case 7: case 8: case 9: case 10: case 0xb: case 0xc: case 0xd:
    case 0xe: case 0xf: case 0x10: case 0x11: case 0x12: case 0x13:
    case 0x14: case 0x15: case 0x16: case 0x17: case 0x18: case 0x19:
    case 0x1a: case 0x1b: case 0x1c: case 0x1d:
        if (!check_extra_operand())
            return 0;
        enc_pm_imm(insn, xs, xd);
        break;
    default:
        err("Illegal X field destination register specified");
        return 0;
    case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x30:
        pseudo_check_move_class((int)REG(xd));
        /* fall through */
    case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22: case 0x23:
    case 0x24: case 0x25: case 0x2a:
        if (!pseudo_check_move_mask(pm, 0x10UL, insn))
            return 0;
        if (!check_extra_operand())
            return 0;
        enc_movec_imm(insn, xs, xd);
        break;
    }
    return 1;
}

/* 0042859c: X field "#long" source */
static long xsrc_imm_long(unsigned long pm, void *insn, void *xs, void *xd,
                          void *ys, void *yd)
{
    if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
        return 0;
    if (!parse_operand(2UL, xd, 0x12, 0, 0, 0))
        return 0;
    switch (REG(xd)) {
    case 2: case 3: case 4: case 6:
        if (*Op3Field == '\0') {
            enc_pm_x_ea_w(insn, xs, xd);
        } else {
            optr = Op3Field;
            if (!parse_operand(1UL, ys, 1, 0, 0, 0))
                return 0;
            if (!parse_operand(0UL, yd, 2, 0, 0, 0))
                return 0;
            enc_pm_xr_w(insn, xs, xd, ys, yd);
        }
        break;
    case 5: case 7: case 8: case 9: case 10: case 0xb: case 0xc: case 0xd:
    case 0xe: case 0xf: case 0x10: case 0x11: case 0x12: case 0x13:
    case 0x14: case 0x15: case 0x16: case 0x17: case 0x18: case 0x19:
    case 0x1a: case 0x1b: case 0x1c: case 0x1d:
        if (!check_extra_operand())
            return 0;
        enc_pm_x_ea_w(insn, xs, xd);
        break;
    case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22: case 0x23:
    case 0x24: case 0x25:
        if (!pseudo_check_move_mask(pm, 0x10UL, insn))
            return 0;
        if (!check_extra_operand())
            return 0;
        enc_movec_ea2_w(insn, xs, xd);
        break;
    default:
        err("Illegal X field destination register specified");
        return 0;
    case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x30:
        pseudo_check_move_class((int)REG(xd));
        /* fall through */
    case 0x2a:
        if (!pseudo_check_move_mask(pm, 0x10UL, insn))
            return 0;
        if (!check_extra_operand())
            return 0;
        enc_movec_ea_w(insn, xs, xd);
        break;
    }
    return 1;
}

/* 004287cc: source register a/b/x/y/ab/ba/a10/b10 (L register) */
static long xsrc_lreg(unsigned long pm, void *insn, void *xs, void *xd)
{
    if (!pseudo_check_move_mask(pm, 1UL, (void *)0))
        return 0;
    if (!get_mem_space(xd, 3))
        return 0;
    if (!parse_operand(0UL, xd, 0, 1, 9, 0)) {
        NWORDS(insn) = (FORCE(xd) != FORCE_SHORT) + 1;
        return 0;
    }
    switch (MODE(xd)) {
    case 2: case 3: case 4: case 5: case 6:
        break;
    case 7: case 8: case 0xe:
        break;
    default:
        fatal("p_xyabba failure");
        return 0;
    case 0x10:
        if (!check_extra_operand())
            return 0;
        enc_pm_l_abs(insn, xs, xd);
        return 1;
    }
    if (!check_extra_operand()) {
        NWORDS(insn) = 2;
        return 0;
    }
    enc_pm_l_ea(insn, xs, xd);
    return 1;
}

/* 004288fe: source register y0 y1 a b (etc), destination X/Y memory or reg */
static long xdst_mem(unsigned long pm, void *insn, void *xs, void *xd,
                     void *ys, void *yd);

static long xsrc_x_a(unsigned long pm, void *insn, void *xs, void *xd,
                     void *ys, void *yd)
{
    /* 004288fe: sources a/b (reg ids 2, 3) */
    if (!get_mem_space(xd, 6))
        return 0;
    if (SPACE(xd) != 4)
        return xdst_mem(pm, insn, xs, xd, ys, yd);
    if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
        return 0;
    if (!parse_operand(2UL, xd, 0x12, 0, 0, 0))
        return 0;
    switch (REG(xd)) {
    case 2: case 3: case 5: case 7: case 8: case 9: case 10: case 0xb:
    case 0xc: case 0xd: case 0xe: case 0xf: case 0x10: case 0x11:
    case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x17:
    case 0x18: case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d:
        if (!check_extra_operand())
            return 0;
        enc_pm_reg(insn, xs, xd);
        break;
    case 4: case 6:
        if (*Op3Field == '\0') {
            enc_pm_reg(insn, xs, xd);
        } else {
            optr = Op3Field;
            if (!get_mem_space(ys, 8))
                return 0;
            if (SPACE(ys) == 4) {
                if (!pseudo_check_move_mask(pm, 1UL, (void *)0))
                    return 0;
                if (!parse_operand(1UL, ys, 4, 0, 0, 1)) {
                    NWORDS(insn) = 2;
                    return 0;
                }
                if (MODE(ys) == 9) {
                    if (!parse_operand(2UL, yd, 4, 0, 0, 0))
                        return 0;
                    enc_pm_ry_w(insn, xs, xd, ys, yd);
                } else {
                    if (!get_mem_space(yd, 2))
                        return 0;
                    if (!parse_operand(0UL, yd, 0, 1, 1, 0)) {
                        NWORDS(insn) = 2;
                        return 0;
                    }
                    enc_pm_ry(insn, xs, xd, ys, yd);
                }
            } else {
                if (!pseudo_check_move_mask(pm, 1UL, (void *)0))
                    return 0;
                if (!parse_operand(1UL, ys, 0, 1, 1, 0)) {
                    NWORDS(insn) = 2;
                    return 0;
                }
                if (!parse_operand(2UL, yd, 4, 0, 0, 0))
                    return 0;
                enc_pm_ry_w(insn, xs, xd, ys, yd);
            }
        }
        break;
    default:
        err("Illegal X field destination register specified");
        return 0;
    case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x30:
        pseudo_check_move_class((int)REG(xd));
        /* fall through */
    case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22: case 0x23:
    case 0x24: case 0x25: case 0x2a:
        if (!pseudo_check_move_mask(pm, 0x10UL, insn))
            return 0;
        if (!check_extra_operand())
            return 0;
        enc_movec_reg_w(insn, xs, xd);
        break;
    }
    return 1;
}

/* 00428cce: sources x0 x1 y0 y1 -- actually reg ids 4, 6 (x0, x1) */
static long xsrc_x0x1(unsigned long pm, void *insn, void *xs, void *xd,
                      void *ys, void *yd)
{
    (void)ys;
    (void)yd;
    if (!get_mem_space(xd, 9))
        return 0;
    if (SPACE(xd) != 4)
        return xdst_mem(pm, insn, xs, xd, ys, yd);
    if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
        return 0;
    if (!parse_operand(2UL, xd, 0x12, 0, 0, 0))
        return 0;
    switch (REG(xd)) {
    case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
    case 10: case 0xb: case 0xc: case 0xd: case 0xe: case 0xf: case 0x10:
    case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16:
    case 0x17: case 0x18: case 0x19: case 0x1a: case 0x1b: case 0x1c:
    case 0x1d:
        if (!check_extra_operand())
            return 0;
        enc_pm_reg(insn, xs, xd);
        return 1;
    case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22: case 0x23:
    case 0x24: case 0x25: case 0x2a:
        break;
    default:
        err("Illegal X field destination register specified");
        return 0;
    case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x30:
        pseudo_check_move_class((int)REG(xd));
        break;
    }
    if (!pseudo_check_move_mask(pm, 0x10UL, insn))
        return 0;
    if (!check_extra_operand())
        return 0;
    enc_movec_reg_w(insn, xs, xd);
    return 1;
}

/* 00428e50: destination is X:/Y:/L: memory */
static long xdst_mem(unsigned long pm, void *insn, void *xs, void *xd,
                     void *ys, void *yd)
{
    long local;

    if (SPACE(xd) == 1) {
        if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
            return 0;
        if (!parse_operand(0UL, xd, 0, 1, 9, 0)) {
            NWORDS(insn) = (FORCE(xd) != FORCE_SHORT) + 1;
            return 0;
        }
        switch (MODE(xd)) {
        case 2: case 3: case 4: case 5:
            if (*Op3Field == '\0') {
                enc_pm_x_ea(insn, xs, xd);
            } else {
                if (!pseudo_check_move_mask(pm, 1UL, (void *)0))
                    return 0;
                optr = Op3Field;
                if (!get_mem_space(ys, 8))
                    return 0;
                if (SPACE(ys) == 4) {
                    if (!parse_operand(1UL, ys, CpuVariant == 0UL ? 4 : 0x17,
                                       0, 0, 0))
                        return 0;
                    switch (REG(ys)) {
                    case 2: case 3:
                        if (!get_mem_space(yd, 8))
                            return 0;
                        if (SPACE(yd) == 4) {
                            if (!parse_operand(0UL, yd, 2, 0, 0, 0))
                                return 0;
                            enc_pm_xr(insn, xs, xd, ys, yd);
                        } else {
                            if (!parse_operand(0UL, yd, 0, 2, 0, 0))
                                return 0;
                            if (chk_xy_regs(REG(xd), REG(yd)))
                                return 0;
                            enc_pm_xy(insn, xs, xd, ys, yd);
                        }
                        break;
                    case 4:
                        if (REG(xs) != 2 && REG(xs) != 3) {
                            err("Invalid addressing mode");
                            return 0;
                        }
                        if (!parse_operand(2UL, yd, (REG(xs) != 2) + 0xd, 0,
                                           0, 0))
                            return 0;
                        enc_pm_xr2(insn, xs, xd);
                        break;
                    case 5: case 7:
                        if (!get_mem_space(yd, 2))
                            return 0;
                        if (!parse_operand(0UL, yd, 0, 2, 0, 0))
                            return 0;
                        if (chk_xy_regs(REG(xd), REG(yd)))
                            return 0;
                        enc_pm_xy(insn, xs, xd, ys, yd);
                        break;
                    default:
                        break;
                    }
                } else {
                    if (!parse_operand(1UL, ys, 0, 2, 0, 0))
                        return 0;
                    if (chk_xy_regs(REG(xd), REG(ys)))
                        return 0;
                    if (!parse_operand(2UL, yd, 4, 0, 0, 0))
                        return 0;
                    enc_pm_xy_wy(insn, xs, xd, ys, yd);
                }
            }
            break;
        case 7: case 8:
        case 6:
            if (*Op3Field == '\0') {
                enc_pm_x_ea(insn, xs, xd);
            } else {
                if (!pseudo_check_move_mask(pm, 1UL, (void *)0))
                    return 0;
                optr = Op3Field;
                if (!parse_operand(1UL, ys, CpuVariant == 0UL ? 1 : 0x16,
                                   0, 0, 0))
                    return 0;
                if (REG(ys) == 4)
                    local = (REG(xs) != 2) + 0xd;
                else
                    local = 2;
                if (!parse_operand(0UL, yd, (int)local, 0, 0, 0))
                    return 0;
                if (REG(ys) == 4) {
                    if (REG(xs) != 2 && REG(xs) != 3) {
                        err("Invalid addressing mode");
                        return 0;
                    }
                    enc_pm_xr2(insn, xs, xd);
                } else {
                    enc_pm_xr(insn, xs, xd, ys, yd);
                }
            }
            break;
        default:
            fatal("xdst_mem failure");
            break;
        case 0xe:
            if (*Op3Field == '\0') {
                enc_pm_x_ea(insn, xs, xd);
            } else {
                if (!pseudo_check_move_mask(pm, 1UL, (void *)0))
                    return 0;
                optr = Op3Field;
                if (!parse_operand(1UL, ys, 1, 0, 0, 0))
                    return 0;
                if (!parse_operand(0UL, yd, 2, 0, 0, 0))
                    return 0;
                enc_pm_xr(insn, xs, xd, ys, yd);
            }
            break;
        case 0x10:
            if (*Op3Field == '\0') {
                enc_pm_x_abs(insn, xs, xd);
            } else {
                MODE(xd) = 0xe;
                if (FORCE(xd) != 0)
                    warn("Short absolute address cannot be forced - long substituted");
                if (!pseudo_check_move_mask(pm, 1UL, (void *)0))
                    return 0;
                optr = Op3Field;
                if (!parse_operand(1UL, ys, 1, 0, 0, 0))
                    return 0;
                if (!parse_operand(0UL, yd, 2, 0, 0, 0))
                    return 0;
                enc_pm_xr(insn, xs, xd, ys, yd);
            }
            break;
        }
    } else if (SPACE(xd) == 2) {
        if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
            return 0;
        if (!parse_operand(0UL, xd, 0, 1, 9, 0)) {
            NWORDS(insn) = (FORCE(xd) != FORCE_SHORT) + 1;
            return 0;
        }
        if (!check_extra_operand()) {
            NWORDS(insn) = 2;
            return 0;
        }
        Op3Field = Op2Field;
        Op2Field = EmptyFieldText;
        if (MODE(xd) == 0x10) {
            enc_pm_y_abs(insn, xs, xd);
        } else {
            enc_pm_y_ea(insn, xs, xd);
        }
    } else {
        if (SPACE(xd) != 3) {
            if (SPACE(xd) == 0)
                return xy_pdst(pm, insn, xs, xd);
            err("Illegal X field destination specified");
            return 0;
        }
        if (!pseudo_check_move_mask(pm, 1UL, (void *)0))
            return 0;
        if (!parse_operand(0UL, xd, 0, 1, 9, 0)) {
            NWORDS(insn) = (FORCE(xd) != FORCE_SHORT) + 1;
            return 0;
        }
        switch (MODE(xd)) {
        case 7: case 8: case 0xe:
        case 2: case 3: case 4: case 5: case 6:
            if (!check_extra_operand()) {
                NWORDS(insn) = 2;
                return 0;
            }
            enc_pm_l_ea(insn, xs, xd);
            break;
        case 0x10:
            if (!check_extra_operand())
                return 0;
            enc_pm_l_abs(insn, xs, xd);
            break;
        default:
            break;
        }
    }
    return 1;
}

/* 00429729: source registers 5..0x1d (y0 y1 x1 ...) */
static long xsrc_reg(unsigned long pm, void *insn, void *xs, void *xd,
                     void *ys, void *yd)
{
    if (!get_mem_space(xd, 9))
        return 0;
    if (SPACE(xd) == 4) {
        if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
            return 0;
        if (!parse_operand(2UL, xd, 0x12, 0, 0, 0))
            return 0;
        switch (REG(xd)) {
        case 2: case 3:
            if (*Op3Field == '\0') {
                enc_pm_reg(insn, xs, xd);
            } else {
                if (!pseudo_check_move_mask(pm, 1UL, (void *)0))
                    return 0;
                if (CpuVariant == 0UL || REG(xs) != 5) {
                    err("Invalid addressing mode");
                    return 0;
                }
                optr = Op3Field;
                if (!parse_operand(1UL, ys, (REG(xd) != 2) + 0xd, 0, 0, 0))
                    return 0;
                if (!get_mem_space(yd, 2))
                    return 0;
                if (!parse_operand(0UL, yd, 0, 1, 0, 0))
                    return 0;
                enc_pm_xr2(insn, ys, yd);
            }
            break;
        case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 0xb:
        case 0xc: case 0xd: case 0xe: case 0xf: case 0x10: case 0x11:
        case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x17:
        case 0x18: case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d:
            if (!check_extra_operand())
                return 0;
            enc_pm_reg(insn, xs, xd);
            break;
        default:
            err("Illegal X field destination register specified");
            return 0;
        case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x30:
            pseudo_check_move_class((int)REG(xd));
            /* fall through */
        case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22: case 0x23:
        case 0x24: case 0x25: case 0x2a:
            if (!pseudo_check_move_mask(pm, 0x10UL, insn))
                return 0;
            if (!check_extra_operand())
                return 0;
            enc_movec_reg_w(insn, xs, xd);
            break;
        }
    } else if (SPACE(xd) == 1) {
        if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
            return 0;
        if (!parse_operand(0UL, xd, 0, 1, 9, 0)) {
            NWORDS(insn) = (FORCE(xd) != FORCE_SHORT) + 1;
            return 0;
        }
        if (!check_extra_operand()) {
            NWORDS(insn) = 2;
            return 0;
        }
        if (MODE(xd) == 0x10) {
            enc_pm_x_abs(insn, xs, xd);
        } else {
            enc_pm_x_ea(insn, xs, xd);
        }
    } else {
        if (SPACE(xd) != 2) {
            if (SPACE(xd) == 0)
                return xy_pdst(pm, insn, xs, xd);
            err("Illegal X field destination specified");
            return 0;
        }
        if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
            return 0;
        if (!parse_operand(0UL, xd, 0, 1, 9, 0)) {
            NWORDS(insn) = (FORCE(xd) != FORCE_SHORT) + 1;
            return 0;
        }
        if (!check_extra_operand()) {
            NWORDS(insn) = 2;
            return 0;
        }
        Op3Field = Op2Field;
        Op2Field = EmptyFieldText;
        if (MODE(xd) == 0x10) {
            enc_pm_y_abs(insn, xs, xd);
        } else {
            enc_pm_y_ea(insn, xs, xd);
        }
    }
    return 1;
}

/* 00429b8a: source is a modifier register (m0-m7) */
static long xsrc_mreg(unsigned long pm, void *insn, void *xs, void *xd)
{
    if (!check_extra_operand())
        return 0;
    if (!get_mem_space(xd, 9))
        return 0;
    if (SPACE(xd) == 4) {
        if (!pseudo_check_move_mask(pm, 0x10UL, insn))
            return 0;
        if (!parse_operand(2UL, xd, 0x12, 0, 0, 0))
            return 0;
        enc_movec_reg(insn, xs, xd);
    } else {
        if (SPACE(xd) != 1 && SPACE(xd) != 2) {
            if (SPACE(xd) == 0)
                return xy_pdst(pm, insn, xs, xd);
            err("Illegal X field destination specified");
            return 0;
        }
        if (!pseudo_check_move_mask(pm, 0x10UL, insn))
            return 0;
        if (!parse_operand(0UL, xd, 0, 1, 9, 0)) {
            NWORDS(insn) = (FORCE(xd) != FORCE_SHORT) + 1;
            return 0;
        }
        if (MODE(xd) == 0x10) {
            enc_movec_abs(insn, xs, xd);
        } else {
            enc_movec_ea2(insn, xs, xd);
        }
        if (SPACE(xd) == 2) {
            Op3Field = Op2Field;
            Op2Field = EmptyFieldText;
        }
    }
    return 1;
}

/* 00429d39: source is a control register (omr sr la lc ssh ssl sp mr ccr) */
static long xsrc_ctlreg(unsigned long pm, void *insn, void *xs, void *xd)
{
    int local;

    local = 0;
    if (REG(xs) == 0x2e) {
        HazardCur |= 0x24cUL;
        local = do_check_end_range_err(2);
    }
    if (local == 0 && REG(xs) == 0x2c)
        do_check_end_range_err(1);
    if ((REG(xs) == 0x2e || REG(xs) == 0x2f) && (HazardPrev & 0x10UL) != 0UL) {
        if (!get_opt_rp() || InLineReplay || ErrOnThisLine != 0UL)
            err("Move from SSH or SSL cannot follow update of SP");
        else if (RegNoteHook != (void (*)(void))0)
            RegNoteHook();
    }
    if (!check_extra_operand())
        return 0;
    if (!get_mem_space(xd, 9))
        return 0;
    if (SPACE(xd) == 4) {
        if (!pseudo_check_move_mask(pm, 0x10UL, insn))
            return 0;
        if (!parse_operand(2UL, xd, 0x12, 0, 0, 0))
            return 0;
        if (REG(xs) == 0x2e && REG(xd) == 0x2e) {
            err("SSH cannot be both source and destination register");
            return 0;
        }
        enc_movec_reg(insn, xs, xd);
    } else if (SPACE(xd) == 1 || SPACE(xd) == 2) {
        if (!pseudo_check_move_mask(pm, 0x10UL, insn))
            return 0;
        if (!parse_operand(0UL, xd, 0, 1, 9, 0)) {
            NWORDS(insn) = (FORCE(xd) != FORCE_SHORT) + 1;
            return 0;
        }
        if (MODE(xd) == 0x10) {
            enc_movec_abs(insn, xs, xd);
        } else {
            enc_movec_ea(insn, xs, xd);
        }
        if (SPACE(xd) == 2) {
            Op3Field = Op2Field;
            Op2Field = EmptyFieldText;
        }
    } else {
        if (SPACE(xd) != 0) {
            err("Illegal X field destination specified");
            return 0;
        }
        if (!xy_pdst(pm, insn, xs, xd))
            return 0;
    }
    return 1;
}

/* 00429fb4: destination is P: memory (MOVEM) */
static long xy_pdst(unsigned long pm, void *insn, void *xs, void *xd)
{
    if (!pseudo_check_move_mask(pm, 0x20UL, insn))
        return 0;
    if (!parse_operand(0UL, xd, 0, 1, 9, 0)) {
        NWORDS(insn) = (FORCE(xd) != FORCE_SHORT) + 1;
        return 0;
    }
    if (!check_extra_operand()) {
        NWORDS(insn) = 2;
        return 0;
    }
    if (MODE(xd) == 0x10)
        enc_movem_abs(insn, xs, xd);
    else
        enc_movem_ea(insn, xs, xd);
    return 1;
}

/* 0042a7d2: X source memory, acc destination with a Y field */
static long xy_xsrc_acc(unsigned long pm, void *insn, void *xs, void *xd,
                        void *ys, void *yd)
{
    if (*Op3Field == '\0') {
        if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
            return 0;
        enc_pm_x_ea_w(insn, xs, xd);
        return 1;
    }
    if (!pseudo_check_move_mask(pm, 1UL, (void *)0))
        return 0;
    optr = Op3Field;
    if (!get_mem_space(ys, 8))
        return 0;
    if (SPACE(ys) == 4) {
        if (!parse_operand(1UL, ys, 4, 0, 0, 0))
            return 0;
        switch (REG(ys)) {
        case 2: case 3:
            if (!get_mem_space(yd, 8))
                return 0;
            if (SPACE(yd) == 4) {
                if (!parse_operand(0UL, yd, 2, 0, 0, 0))
                    return 0;
                enc_pm_xr_w(insn, xs, xd, ys, yd);
            } else {
                if (!parse_operand(0UL, yd, 0, 2, 0, 0))
                    return 0;
                if (chk_xy_regs(REG(xs), REG(yd)))
                    return 0;
                enc_pm_xy_wx(insn, xs, xd, ys, yd);
            }
            break;
        case 5: case 7:
            if (!get_mem_space(yd, 2))
                return 0;
            if (!parse_operand(0UL, yd, 0, 2, 0, 0))
                return 0;
            if (chk_xy_regs(REG(xs), REG(yd)))
                return 0;
            enc_pm_xy_wx(insn, xs, xd, ys, yd);
            break;
        default:
            break;
        }
    } else {
        if (!parse_operand(1UL, ys, 0, 2, 0, 0))
            return 0;
        if (chk_xy_regs(REG(xs), REG(ys)))
            return 0;
        if (!parse_operand(2UL, yd, 4, 0, 0, 0))
            return 0;
        enc_pm_xy_wxy(insn, xs, xd, ys, yd);
    }
    return 1;
}

/* 0042a096: source is X: memory */
static long xy_xsrc(unsigned long pm, void *insn, void *xs, void *xd,
                    void *ys, void *yd)
{
    switch (MODE(xs)) {
    case 2: case 3: case 4: case 5:
        if (!get_mem_space(xd, 0))
            return 0;
        if (SPACE(xd) == 4) {
            if (!parse_operand(2UL, xd, 0x12, 0, 0, 0))
                return 0;
            switch (REG(xd)) {
            case 2: case 3: case 4: case 6:
                if (!xy_xsrc_acc(pm, insn, xs, xd, ys, yd))
                    return 0;
                break;
            case 0xe: case 0xf: case 0x10: case 0x11: case 0x12: case 0x13:
            case 0x14: case 0x15:
                if (MODE(xs) != 2 && REG(xs) == REG(xd))
                    warn("Post-update operation will not occur on destination register");
                /* fall through */
            case 5: case 7: case 8: case 9: case 10: case 0xb: case 0xc:
            case 0xd: case 0x16: case 0x17: case 0x18: case 0x19: case 0x1a:
            case 0x1b: case 0x1c: case 0x1d:
                if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
                    return 0;
                if (!check_extra_operand())
                    return 0;
                enc_pm_x_ea_w(insn, xs, xd);
                break;
            case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22:
            case 0x23: case 0x24: case 0x25:
                if (!pseudo_check_move_mask(pm, 0x10UL, insn))
                    return 0;
                if (!check_extra_operand())
                    return 0;
                enc_movec_ea2_w(insn, xs, xd);
                break;
            default:
                err("Illegal X field destination register specified");
                return 0;
            case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f:
            case 0x30:
                pseudo_check_move_class((int)REG(xd));
                /* fall through */
            case 0x2a:
                if (!pseudo_check_move_mask(pm, 0x10UL, insn))
                    return 0;
                if (!check_extra_operand())
                    return 0;
                enc_movec_ea_w(insn, xs, xd);
                break;
            }
        }
        break;
    case 7: case 8: case 0xe:
    case 6:
        if (!parse_operand(2UL, xd, 0x12, 0, 0, 0))
            return 0;
        switch (REG(xd)) {
        case 2: case 3: case 4: case 6:
            if (*Op3Field == '\0') {
                if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
                    return 0;
                enc_pm_x_ea_w(insn, xs, xd);
            } else {
                if (!pseudo_check_move_mask(pm, 1UL, (void *)0))
                    return 0;
                optr = Op3Field;
                if (!parse_operand(1UL, ys, 1, 0, 0, 0))
                    return 0;
                if (!parse_operand(0UL, yd, 2, 0, 0, 0))
                    return 0;
                enc_pm_xr_w(insn, xs, xd, ys, yd);
            }
            break;
        case 0xe: case 0xf: case 0x10: case 0x11: case 0x12: case 0x13:
        case 0x14: case 0x15:
            if (MODE(xs) == 6 && REG(xs) == REG(xd))
                warn("Post-update operation will not occur on destination register");
            /* fall through */
        case 5: case 7: case 8: case 9: case 10: case 0xb: case 0xc:
        case 0xd: case 0x16: case 0x17: case 0x18: case 0x19: case 0x1a:
        case 0x1b: case 0x1c: case 0x1d:
            if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
                return 0;
            if (!check_extra_operand())
                return 0;
            enc_pm_x_ea_w(insn, xs, xd);
            break;
        case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22: case 0x23:
        case 0x24: case 0x25:
            if (!pseudo_check_move_mask(pm, 0x10UL, insn))
                return 0;
            if (!check_extra_operand())
                return 0;
            enc_movec_ea2_w(insn, xs, xd);
            break;
        default:
            err("Illegal X field destination register specified");
            return 0;
        case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x30:
            pseudo_check_move_class((int)REG(xd));
            /* fall through */
        case 0x2a:
            if (!pseudo_check_move_mask(pm, 0x10UL, insn))
                return 0;
            if (!check_extra_operand())
                return 0;
            enc_movec_ea_w(insn, xs, xd);
            break;
        }
        break;
    case 0x10:
        if (!parse_operand(2UL, xd, 0x12, 0, 0, 0))
            return 0;
        switch (REG(xd)) {
        case 2: case 3: case 4: case 6:
            if (*Op3Field == '\0') {
                if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
                    return 0;
                enc_pm_x_abs_w(insn, xs, xd);
            } else {
                if (!pseudo_check_move_mask(pm, 1UL, (void *)0))
                    return 0;
                optr = Op3Field;
                if (!parse_operand(1UL, ys, 1, 0, 0, 0))
                    return 0;
                if (!parse_operand(0UL, yd, 2, 0, 0, 0))
                    return 0;
                if (FORCE(xs) != 0)
                    warn("Short absolute address cannot be forced - long substituted");
                MODE(xs) = 0xe;
                enc_pm_xr_w(insn, xs, xd, ys, yd);
            }
            break;
        case 5: case 7: case 8: case 9: case 10: case 0xb: case 0xc:
        case 0xd: case 0xe: case 0xf: case 0x10: case 0x11: case 0x12:
        case 0x13: case 0x14: case 0x15: case 0x16: case 0x17: case 0x18:
        case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d:
            if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
                return 0;
            if (!check_extra_operand())
                return 0;
            enc_pm_x_abs_w(insn, xs, xd);
            break;
        default:
            err("Illegal X field destination register specified");
            return 0;
        case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x30:
            pseudo_check_move_class((int)REG(xd));
            /* fall through */
        case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22: case 0x23:
        case 0x24: case 0x25: case 0x2a:
            if (!pseudo_check_move_mask(pm, 0x10UL, insn))
                return 0;
            if (!check_extra_operand())
                return 0;
            enc_movec_abs_w(insn, xs, xd);
            break;
        }
        break;
    default:
        break;
    }
    return 1;
}

/* 0042aa80: source is Y: memory */
static long xy_ysrc(unsigned long pm, void *insn, void *xs, void *xd)
{
    if (!check_extra_operand())
        return 0;
    Op3Field = Op2Field;
    Op2Field = EmptyFieldText;
    switch (MODE(xs)) {
    case 7: case 8: case 0xe:
    case 2: case 3: case 4: case 5: case 6:
        if (!parse_operand(2UL, xd, 0x12, 0, 0, 0))
            return 0;
        switch (REG(xd)) {
        case 0xe: case 0xf: case 0x10: case 0x11: case 0x12: case 0x13:
        case 0x14: case 0x15:
            if ((MODE(xs) == 3 || MODE(xs) == 5 || MODE(xs) == 4 ||
                 MODE(xs) == 6) && REG(xs) == REG(xd))
                warn("Post-update operation will not occur on destination register");
            /* fall through */
        case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        case 10: case 0xb: case 0xc: case 0xd: case 0x16: case 0x17:
        case 0x18: case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d:
            if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
                return 0;
            enc_pm_y_ea_w(insn, xs, xd);
            break;
        case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22: case 0x23:
        case 0x24: case 0x25:
            if (!pseudo_check_move_mask(pm, 0x10UL, insn))
                return 0;
            enc_movec_ea2_w(insn, xs, xd);
            break;
        default:
            err("Illegal X field destination register specified");
            return 0;
        case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x30:
            pseudo_check_move_class((int)REG(xd));
            /* fall through */
        case 0x2a:
            if (!pseudo_check_move_mask(pm, 0x10UL, insn))
                return 0;
            enc_movec_ea_w(insn, xs, xd);
            break;
        }
        break;
    case 0x10:
        if (!parse_operand(2UL, xd, 0x12, 0, 0, 0))
            return 0;
        switch (REG(xd)) {
        case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        case 10: case 0xb: case 0xc: case 0xd: case 0xe: case 0xf:
        case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15:
        case 0x16: case 0x17: case 0x18: case 0x19: case 0x1a: case 0x1b:
        case 0x1c: case 0x1d:
            if (!pseudo_check_move_mask(pm, 0x11UL, (void *)0))
                return 0;
            enc_pm_y_abs_w(insn, xs, xd);
            break;
        default:
            err("Illegal X field destination register specified");
            return 0;
        case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x30:
            pseudo_check_move_class((int)REG(xd));
            /* fall through */
        case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22: case 0x23:
        case 0x24: case 0x25: case 0x2a:
            if (!pseudo_check_move_mask(pm, 0x10UL, insn))
                return 0;
            enc_movec_abs_w(insn, xs, xd);
            break;
        }
        break;
    default:
        break;
    }
    return 1;
}

/* 0042adb6: source is L: memory */
static long xy_lsrc(unsigned long pm, void *insn, void *xs, void *xd)
{
    if (!check_extra_operand())
        return 0;
    if (!pseudo_check_move_mask(pm, 1UL, (void *)0))
        return 0;
    if (MODE(xs) == 0x10) {
        if (!parse_operand(2UL, xd, 5, 0, 0, 0))
            return 0;
        enc_pm_l_abs_w(insn, xs, xd);
    } else {
        if (!parse_operand(2UL, xd, 5, 0, 0, 0))
            return 0;
        enc_pm_l_ea_w(insn, xs, xd);
    }
    return 1;
}

/* 0042ae87: source is P: memory (MOVEM) */
static long xy_psrc(unsigned long pm, void *insn, void *xs, void *xd)
{
    if (!check_extra_operand())
        return 0;
    if (!pseudo_check_move_mask(pm, 0x20UL, insn))
        return 0;
    switch (MODE(xs)) {
    case 2: case 3: case 4: case 5: case 6: case 0x10:
    case 7: case 8: case 0xe:
        break;
    default:
        return 1;
    }
    if (!parse_operand(2UL, xd, 0x12, 0, 0, 0))
        return 0;
    switch (REG(xd)) {
    case 0xe: case 0xf: case 0x10: case 0x11: case 0x12: case 0x13:
    case 0x14: case 0x15:
        if ((MODE(xs) == 3 || MODE(xs) == 5 || MODE(xs) == 4 ||
             MODE(xs) == 6) && REG(xs) == REG(xd))
            warn("Post-update operation will not occur on destination register");
        /* fall through */
    case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
    case 10: case 0xb: case 0xc: case 0xd: case 0x16: case 0x17:
    case 0x18: case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d:
    case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22: case 0x23:
    case 0x24: case 0x25: case 0x2a:
        if (MODE(xs) == 0x10)
            enc_movem_abs_w(insn, xs, xd);
        else
            enc_movem_ea_w(insn, xs, xd);
        break;
    default:
        err("Illegal X field destination register specified");
        return 0;
    case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x30:
        pseudo_check_move_class((int)REG(xd));
        if (MODE(xs) == 0x10)
            enc_movem_abs_w(insn, xs, xd);
        else
            enc_movem_ea_w(insn, xs, xd);
        break;
    }
    return 1;
}

/* 00428040 */
int do_xy(void *insn, unsigned long pm, void *xs, void *xd, void *ys,
          void *yd)
{
    long r;

    optr = Op2Field;
    if (!get_mem_space(xs, 6))
        return 0;
    if (SPACE(xs) == 4) {
        if (!parse_xfield_src(xs)) {
            NWORDS(insn) = 2;
            return 0;
        }
        if (MODE(xs) > 2 && MODE(xs) < 7) {
            if (!check_extra_operand())
                return 0;
            enc_pm_update(insn, xs);
            return 1;
        }
        if ((MODE(xs) > 1 && MODE(xs) < 9) ||
            (MODE(xs) > 0xd && MODE(xs) < 0x11)) {
            err("Missing memory space specifier");
            NWORDS(insn) = 2;
            return 0;
        }
        if (MODE(xs) == 0xb)
            return (int)xsrc_imm_short(pm, insn, xs, xd, ys, yd);
        if (MODE(xs) == 9)
            return (int)xsrc_imm_long(pm, insn, xs, xd, ys, yd);
        switch (REG(xs)) {
        case 0: case 1: case 0x26: case 0x27: case 0x28: case 0x29:
            r = xsrc_lreg(pm, insn, xs, xd);
            break;
        case 2: case 3:
            r = xsrc_x_a(pm, insn, xs, xd, ys, yd);
            break;
        case 4: case 6:
            r = xsrc_x0x1(pm, insn, xs, xd, ys, yd);
            break;
        case 5: case 7: case 8: case 9: case 10: case 0xb: case 0xc:
        case 0xd: case 0xe: case 0xf: case 0x10: case 0x11: case 0x12:
        case 0x13: case 0x14: case 0x15: case 0x16: case 0x17: case 0x18:
        case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d:
            r = xsrc_reg(pm, insn, xs, xd, ys, yd);
            break;
        case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22: case 0x23:
        case 0x24: case 0x25:
            r = xsrc_mreg(pm, insn, xs, xd);
            break;
        case 0x2a: case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f:
        case 0x30:
            r = xsrc_ctlreg(pm, insn, xs, xd);
            break;
        default:
            goto memory_source;
        }
        return (int)r;
    }
memory_source:
    if (!parse_operand(1UL, xs, 0, 1, 9, 0)) {
        NWORDS(insn) = (FORCE(xs) != FORCE_SHORT) + 1;
        return 0;
    }
    switch (SPACE(xs)) {
    case 0:
        return (int)xy_psrc(pm, insn, xs, xd);
    case 1:
        return (int)xy_xsrc(pm, insn, xs, xd, ys, yd);
    case 2:
        return (int)xy_ysrc(pm, insn, xs, xd);
    case 3:
        return (int)xy_lsrc(pm, insn, xs, xd);
    default:
        fatal("do_xy memory space select failure");
        return 0;
    }
}
