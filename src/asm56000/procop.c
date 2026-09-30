/*
 * ASM56000.EXE (CLAS56 v6.3.0) - procop.c 1.22: per-instruction processing.
 *
 * proc_instr() is the instruction entry point: the mnemonic table entry
 * selects a handler by class, each handler parses the operand field(s)
 * with parse_operand() (amode.c), checks the DSP56000 restrictions and
 * calls the encoders of encode.c; do_xy() (procxy.c) then handles the
 * parallel move fields.  The opcode words are emitted whether or not the
 * handler reported an error.
 *
 * The INSN record is 0x50 bytes: word 0 = number of words, words 1 and 2
 * = opcode and extension word (see asm56000.h for the offsets).
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "asm56000.h"

#define optr CurInstrFieldMsg

#define MODE(o)  (((long *)(o))[0])
#define SPACE(o) (((long *)(o))[1])
#define FWD(o)   (((long *)(o))[2])
#define FORCE(o) (((long *)(o))[3])
#define VALUE(o) (((long *)(o))[4])
#define REG(o)   (((long *)(o))[5])
#define SECT(o)  (((long *)(o))[6])
#define CFORM(o) (*(char **)((char *)(o) + ASM56000_OP_CFORM))
#define NWORDS(i) (((unsigned long *)(i))[0])
#define WORD0(i)  (((unsigned long *)(i))[1])
#define WORD1(i)  (((unsigned long *)(i))[2])

#define FORCE_SHORT 0x2000000L
#define FORCE_IO    0x4000000L

typedef unsigned long OPERAND[10];
typedef unsigned long INSN[24];

extern void fatal(char *msg);
extern char InLineReplay;
extern unsigned long ErrOnThisLine;
extern void *DoStack;
extern unsigned long CpuVariant;
extern int CurrentSpace;
extern int do_xy(void *insn, unsigned long pm, void *xs, void *xd,
                 void *ys, void *yd);
extern int pseudo_check_move_class(int reg);

char EmptyFieldText[] = "";

static unsigned long LastWords[2];
static int LastCount;
static void (*EmitWord)(unsigned long, int);
int (*VectorCheckHook)(void);
static int XySwapToggle;
static int XySwapped;

struct instr_info {
    unsigned char iclass;
    unsigned char pm;
    unsigned long templ;
};

static struct instr_info InfoTab[142] = {
    {0x03,0x01,0x00000026UL},{0x24,0x01,0x00000021UL},{0x22,0x01,0x00000000UL},
    {0x01,0x01,0x00000012UL},{0x01,0x01,0x00000002UL},{0x04,0x02,0x00000000UL},
    {0x25,0x00,0x000000b8UL},{0x03,0x01,0x00000032UL},{0x03,0x01,0x00000022UL},
    {0x05,0x00,0x000b0000UL},{0x05,0x00,0x000a0000UL},{0x05,0x00,0x000a0020UL},
    {0x06,0x00,0x000b0020UL},{0x03,0x01,0x00000013UL},{0x07,0x01,0x00000005UL},
    {0x07,0x01,0x00000007UL},{0x29,0x00,0x00000200UL},{0x29,0x00,0x00000200UL},
    {0x29,0x00,0x00000200UL},{0x29,0x00,0x00000300UL},{0x29,0x00,0x00000308UL},
    {0x29,0x00,0x00000305UL},{0x29,0x00,0x0000030aUL},{0x29,0x00,0x0000030dUL},
    {0x29,0x00,0x00000301UL},{0x29,0x00,0x00000307UL},{0x29,0x00,0x00000300UL},
    {0x29,0x00,0x00000306UL},{0x29,0x00,0x0000030fUL},{0x29,0x00,0x00000308UL},
    {0x29,0x00,0x0000030eUL},{0x29,0x00,0x00000309UL},{0x29,0x00,0x0000030bUL},
    {0x29,0x00,0x00000302UL},{0x29,0x00,0x00000302UL},{0x29,0x00,0x00000304UL},
    {0x29,0x00,0x0000030cUL},{0x29,0x00,0x00000303UL},{0x02,0x00,0x0000000aUL},
    {0x08,0x00,0x00018040UL},{0x09,0x00,0x00060000UL},{0x0a,0x00,0x0000008cUL},
    {0x20,0x01,0x00000043UL},{0x0b,0x00,0x00000005UL},{0x02,0x00,0x00000008UL},
    {0x0e,0x00,0x000a0000UL},{0x0f,0x00,0x000a0080UL},{0x0e,0x00,0x000a8000UL},
    {0x0e,0x00,0x000a5000UL},{0x0e,0x00,0x000aa000UL},{0x0e,0x00,0x000ad000UL},
    {0x0e,0x00,0x000a1000UL},{0x0e,0x00,0x000a7000UL},{0x0e,0x00,0x000a0000UL},
    {0x0e,0x00,0x000a6000UL},{0x0e,0x00,0x000af000UL},{0x0e,0x00,0x000a8000UL},
    {0x0e,0x00,0x000ae000UL},{0x0e,0x00,0x000a9000UL},{0x0e,0x00,0x000ab000UL},
    {0x13,0x00,0x00080000UL},{0x0e,0x00,0x000a2000UL},{0x0e,0x00,0x000a2000UL},
    {0x0e,0x00,0x000a4000UL},{0x0e,0x00,0x000ac000UL},{0x0e,0x00,0x000a3000UL},
    {0x10,0x00,0x000b0000UL},{0x11,0x00,0x000b0080UL},{0x10,0x00,0x000b8000UL},
    {0x10,0x00,0x000b5000UL},{0x10,0x00,0x000ba000UL},{0x10,0x00,0x000bd000UL},
    {0x0f,0x00,0x000a00a0UL},{0x10,0x00,0x000b1000UL},{0x10,0x00,0x000b7000UL},
    {0x10,0x00,0x000b0000UL},{0x10,0x00,0x000b6000UL},{0x10,0x00,0x000bf000UL},
    {0x10,0x00,0x000b8000UL},{0x10,0x00,0x000be000UL},{0x10,0x00,0x000b9000UL},
    {0x10,0x00,0x000bb000UL},{0x10,0x00,0x000b2000UL},{0x10,0x00,0x000b2000UL},
    {0x10,0x00,0x000b4000UL},{0x10,0x00,0x000bc000UL},{0x10,0x00,0x000b3000UL},
    {0x12,0x00,0x00090000UL},{0x11,0x00,0x000b00a0UL},{0x14,0x00,0x00044010UL},
    {0x28,0x01,0x00000033UL},{0x28,0x01,0x00000023UL},{0x14,0x00,0x00044010UL},
    {0x15,0x02,0x00000082UL},{0x2a,0x02,0x00000083UL},{0x17,0x35,0x00000000UL},
    {0x16,0x10,0x00000000UL},{0x18,0x20,0x00000000UL},{0x19,0x00,0x00084000UL},
    {0x1a,0x02,0x00000080UL},{0x2b,0x02,0x00000081UL},{0x03,0x01,0x00000036UL},
    {0x1b,0x00,0x00000000UL},{0x1c,0x00,0x0001d815UL},{0x28,0x01,0x00000017UL},
    {0x04,0x02,0x00000040UL},{0x25,0x00,0x000000f8UL},{0x1d,0x00,0x00060020UL},
    {0x0c,0x00,0x00000084UL},{0x03,0x01,0x00000011UL},{0x28,0x01,0x00000037UL},
    {0x28,0x01,0x00000027UL},{0x1e,0x00,0x00000004UL},{0x1f,0x00,0x0000000cUL},
    {0x24,0x01,0x00000025UL},{0x0d,0x00,0x00000087UL},{0x22,0x01,0x00000004UL},
    {0x01,0x01,0x00000016UL},{0x01,0x01,0x00000006UL},{0x2c,0x00,0x00000006UL},
    {0x26,0x00,0x00020000UL},{0x26,0x00,0x00028000UL},{0x26,0x00,0x00025000UL},
    {0x26,0x00,0x0002a000UL},{0x26,0x00,0x0002d000UL},{0x23,0x01,0x00000001UL},
    {0x26,0x00,0x00021000UL},{0x26,0x00,0x00027000UL},{0x26,0x00,0x00020000UL},
    {0x26,0x00,0x00026000UL},{0x26,0x00,0x0002f000UL},{0x26,0x00,0x00028000UL},
    {0x26,0x00,0x0002e000UL},{0x26,0x00,0x00029000UL},{0x26,0x00,0x0002b000UL},
    {0x26,0x00,0x00022000UL},{0x26,0x00,0x00022000UL},{0x26,0x00,0x00024000UL},
    {0x26,0x00,0x0002c000UL},{0x26,0x00,0x00023000UL},{0x27,0x01,0x00000003UL},
    {0x0d,0x00,0x00000086UL}
};

/* ------------------------------------------------------------------ */
/* hooks to the driver                                                 */

struct do_node {
    unsigned long la;      /* loop address (last instruction) */
    unsigned long saved;
    unsigned long pc;
    struct do_node *next;
};

static int EndRangeReported;

/* 0041b685: an instruction that cannot appear in the last words of a DO
   loop; n = 0 last address ... 5 = last 6 words. */
int do_check_end_range_err(int n)
{
    struct do_node *top;
    char *save;
    int k;

    top = (struct do_node *)DoStack;
    if (top == (struct do_node *)0 || InLineReplay)
        return 0;
    if (EndRangeReported)
        return 1;
    for (k = n; k >= 0 && CurrentAddress != top->la - (unsigned long)k; --k)
        ;
    if (k >= 0) {
        EndRangeReported = 1;
        save = optr;
        optr = (char *)0;
        switch (n) {
        case 0: err("Instruction cannot appear at last address of a DO loop"); break;
        case 1: err("Instruction cannot appear within last 2 words of a DO loop"); break;
        case 2: err("Instruction cannot appear within last 3 words of a DO loop"); break;
        case 3: err("Instruction cannot appear within last 4 words of a DO loop"); break;
        case 4: err("Instruction cannot appear within last 5 words of a DO loop"); break;
        case 5: err("Instruction cannot appear within last 6 words of a DO loop"); break;
        default: fatal("Invalid DO loop range check");
        }
        optr = save;
    }
    return EndRangeReported;
}

/* 0041b43f: pop the loops that end with this instruction (the original
   re-assembles the loop body's last lines here; not reproduced) */
static void do_stack_unwind(unsigned long nwords)
{
    unsigned long pc;
    struct do_node *top;

    pc = CurrentAddress;
    if (nwords > 1UL)
        ++pc;
    while (DoStack != (void *)0 && ((struct do_node *)DoStack)->la <= pc) {
        top = (struct do_node *)DoStack;
        DoStack = (void *)top->next;
        xfree(top);
    }
}

static void reg_note(void)
{
    if (RegNoteHook != (void (*)(void))0)
        RegNoteHook();
}

/* the common "cannot happen right after a control register access" test:
   error when OPT RP is off (or in a replay / already in error), otherwise
   the driver inserts a NOP */
static int hazard_or_nop(char *msg)
{
    if (!get_opt_rp() || InLineReplay || ErrOnThisLine != 0UL) {
        err(msg);
        return 0;
    }
    reg_note();
    return 1;
}

static void free_cform(void *op)
{
    char **c;

    c = (char **)((char *)op + ASM56000_OP_CFORM);
    if (*c != (char *)0) {
        xfree(*c);
        *c = (char *)0;
    }
}

static void field_shift(void)
{
    Op3Field = Op2Field;
    Op2Field = Op1Field;
    Op1Field = EmptyFieldText;
}

/* 0041b8bc: the listing routines swap X and Y field when the Y move is
   written first */
static int lst_xy_needs_swap(void)
{
    char *t;
    char *p;

    XySwapToggle = XySwapToggle == 0;
    if (XySwapToggle == 0) {
        if (XySwapped != 0) {
            t = Op2Field;
            Op2Field = Op3Field;
            Op3Field = t;
            XySwapped = 0;
        }
        return 0;
    }
    if (*Op2Field == '\0' || *Op3Field == '\0')
        return XySwapped;
    if ((*Op2Field == '#' && Op3Field[1] != '\0' &&
         tolower((unsigned char)Op3Field[2]) == 'x') ||
        (*Op3Field == '#' && Op2Field[1] != '\0' &&
         tolower((unsigned char)Op2Field[2]) == 'y')) {
        t = Op2Field;
        Op2Field = Op3Field;
        Op3Field = t;
        XySwapped = 1;
    }
    if (XySwapped == 0) {
        for (p = Op2Field; *p != '\0'; ++p) {
            if (tolower((unsigned char)*p) == 'y' && p[1] == ':') {
                t = Op2Field;
                Op2Field = Op3Field;
                Op3Field = t;
                XySwapped = 1;
                break;
            }
        }
    }
    if (XySwapped == 0) {
        for (p = Op3Field; *p != '\0'; ++p) {
            if (tolower((unsigned char)*p) == 'x' && p[1] == ':') {
                t = Op2Field;
                Op2Field = Op3Field;
                Op3Field = t;
                XySwapped = 1;
                return 1;
            }
        }
    }
    return XySwapped;
}

/* 0041b339 */
static void do_line_reset(void)
{
    CtrlRegAccessed = 0;
    DestRegMask = 0UL;
    AregWrittenPrev = AregWritten;
    AregWritten = 0UL;
    LastSrcReg = 0L;
    HazardPrev = HazardCur;
    HazardCur = 0UL;
    EndRangeReported = 0;
    if (VectorCheckHook != (int (*)(void))0 && VectorCheckHook() &&
        (CurrentAddress & 1UL) == 0UL) {
        AregWrittenPrev = 0UL;
        HazardPrev = 0UL;
    }
}

/* 00427d58 */
static void set_alu_reg(int which, int reg, unsigned long *word)
{
    unsigned long v;

    v = 0UL;
    if (which == 2) {
        v = reg != 2 ? 8UL : 0UL;
    } else {
        switch (reg) {
        case 0: v = 0x20UL; break;
        case 1: v = 0x30UL; break;
        case 2:
        case 3:
            v = *word & 7UL;
            if (v == 0UL || v == 4UL)
                v = 0x10UL;
            else if (v == 1UL || v == 5UL || v == 7UL)
                v = 0UL;
            break;
        case 4: v = 0x40UL; break;
        case 5: v = 0x50UL; break;
        case 6: v = 0x60UL; break;
        case 7: v = 0x70UL; break;
        default:
            fatal("Register selection failure");
        }
    }
    *word |= v;
}

/* 00427e5d */
static int mulreg(int s1, int s2, int d, unsigned long *word)
{
    unsigned long v;

    v = 0UL;
    switch (s1) {
    case 4:
        switch (s2) {
        case 4: break;
        case 5: v = 0x50UL; break;
        case 6: v = 0x20UL; break;
        case 7: v = 0x40UL; break;
        default: err("Invalid register combination"); return 0;
        }
        break;
    case 5:
        switch (s2) {
        case 4: v = 0x50UL; break;
        case 5: v = 0x10UL; break;
        case 6: v = 0x60UL; break;
        case 7: v = 0x30UL; break;
        default: err("Invalid register combination"); return 0;
        }
        break;
    case 6:
        if (s2 == 4) v = 0x20UL;
        else if (s2 == 5) v = 0x60UL;
        else if (s2 == 7) v = 0x70UL;
        else { err("Invalid register combination"); return 0; }
        break;
    case 7:
        if (s2 == 4) v = 0x40UL;
        else if (s2 == 5) v = 0x30UL;
        else if (s2 == 6) v = 0x70UL;
        else { err("Invalid register combination"); return 0; }
        break;
    default:
        fatal("mulreg failure");
        return 0;
    }
    if (d == 3)
        v |= 8UL;
    *word |= v;
    return 1;
}

/* ------------------------------------------------------------------ */
/* handlers                                                            */

/* 00425340 */
static int p_noarg(int iclass)
{
    int ok;

    ok = 1;
    optr = MnemField;
    switch (iclass) {
    case 0xb:
        ok = CpuVariant == 0UL;
        if (ok)
            err("Unrecognized mnemonic");
        ok = !ok;
        break;
    case 0xd:
    case 0x2c:
        ok = (HazardPrev & 1UL) != 0UL;
        if (ok)
            err("Cannot repeat this instruction");
        ok = !ok;
        if (iclass == 0x2c)
            break;
        /* fall through */
    case 0xc:
        if (do_check_end_range_err(0) != 0)
            ok = 0;
        break;
    case 0x29:
        if (CpuVariant < 2UL) {
            err("Unrecognized mnemonic");
            ok = 0;
        }
        break;
    default:
        break;
    }
    optr = Op1Field;
    field_shift();
    return ok;
}

/* 0042546b: rti / rts */
static int p_rts(int iclass)
{
    int ok;

    ok = 1;
    optr = MnemField;
    HazardCur |= 0x200UL;
    if ((HazardPrev & 1UL) == 0UL) {
        if ((HazardPrev & ((iclass != 0x1f ? 0x80UL : 0UL) + 0x40UL)) != 0UL) {
            if (!hazard_or_nop("Instruction cannot appear immediately after control register access"))
                ok = 0;
        }
    } else {
        err("Cannot repeat this instruction");
        ok = 0;
    }
    if (do_check_end_range_err(0) != 0)
        ok = 0;
    optr = Op1Field;
    field_shift();
    return ok;
}

/* 00425552 */
static int p_andi(void *insn)
{
    OPERAND imm;
    OPERAND dst;

    if (*optr == '#') {
        if (parse_operand(5UL, imm, 0, 0, 0, 3) &&
            parse_operand(0UL, dst, 0x13, 0, 0, 0)) {
            if (REG(dst) == 0x32L) {
                HazardCur |= 0x280UL;
            } else if (REG(dst) == 0x31L) {
                HazardCur |= 0x288UL;
                if (do_check_end_range_err(2) != 0) {
                    free_cform(imm);
                    return 0;
                }
            }
            enc_andi(insn, imm, dst);
            return 1;
        }
    } else {
        err("Immediate operand required");
    }
    return 0;
}

/* 0042562d */
static int p_and_or(void *insn)
{
    OPERAND s;
    OPERAND d;
    int ok;

    ok = 0;
    if (*optr == '#') {
        p_andi(insn);
    } else {
        ok = 1;
        if (WORD0(insn) == 0UL)
            WORD0(insn) = 0x46UL;
        else
            WORD0(insn) = 0x42UL;
        if (!parse_operand(1UL, s, 0xb, 0, 0, 0) ||
            !parse_operand(2UL, d, 0x18, 0, 0, 0)) {
            ok = 0;
        } else {
            set_alu_reg(1, (int)REG(s), &WORD0(insn));
            set_alu_reg(2, (int)REG(d), &WORD0(insn));
        }
    }
    return ok;
}

/* 004256e7 */
static int p_alu1(int iclass, void *insn)
{
    OPERAND d;

    if (iclass == 2 && CpuVariant < 2UL) {
        optr = MnemField;
        err("Unrecognized mnemonic");
        return 0;
    }
    if (!parse_operand(iclass != 0x27 ? 2UL : 0UL, d,
                       iclass != 0x28 ? 1 : 0x18, 0, 0, 0))
        return 0;
    if (iclass == 2)
        WORD0(insn) |= (unsigned long)(REG(d) != 2L);
    else
        set_alu_reg(2, (int)REG(d), &WORD0(insn));
    return 1;
}

/* 0042578d */
static int p_addl(void *insn)
{
    OPERAND s;
    OPERAND d;

    if (parse_operand(1UL, s, 1, 0, 0, 0) &&
        parse_operand(2UL, d, (REG(s) == 2L) + 0xd, 0, 0, 0)) {
        set_alu_reg(2, (int)REG(d), &WORD0(insn));
        return 1;
    }
    return 0;
}

/* 004257f4 */
static int p_eor_adc(int iclass, void *insn)
{
    OPERAND s;
    OPERAND d;

    if (!parse_operand(1UL, s, (iclass != 0x24) + 10, 0, 0, 0))
        return 0;
    set_alu_reg(1, (int)REG(s), &WORD0(insn));
    if (!parse_operand(2UL, d, iclass != 0x24 ? 0x18 : 1, 0, 0, 0))
        return 0;
    set_alu_reg(2, (int)REG(d), &WORD0(insn));
    return 1;
}

/* 00425883 */
static int p_alu2(int iclass, void *insn)
{
    OPERAND s;
    OPERAND d;
    int dclass;

    if (!parse_operand(1UL, s, iclass != 0x22 ? 0xf : 0x15, 0, 0, 0))
        return 0;
    set_alu_reg(1, (int)REG(s), &WORD0(insn));
    if (REG(s) == 2L)
        dclass = 0xe;
    else
        dclass = REG(s) != 3L ? 1 : 0xd;
    if (!parse_operand(iclass != 7 ? 2UL : 0UL, d, dclass, 0, 0, 0))
        return 0;
    set_alu_reg(2, (int)REG(d), &WORD0(insn));
    return 1;
}

/* 00425945 */
static int p_norm(void *insn)
{
    OPERAND r;
    OPERAND d;
    unsigned long bit;

    if (parse_operand(1UL, r, 0x10, 0, 0, 0) &&
        parse_operand(0UL, d, 1, 0, 0, 0)) {
        bit = 1UL << (unsigned)((REG(r) - 0xe) & 31);
        if ((AregWrittenPrev & bit) != 0UL &&
            CurrentAddress == AregWritePc + (unsigned long)PrevInstrWords)
            hazard_or_nop("Contents of register written in previous instruction not available");
        enc_norm(insn, r, d);
        return 1;
    }
    return 0;
}

/* 00425a05 */
static int p_lua(void *insn)
{
    OPERAND ea;
    OPERAND d;

    if (parse_operand(1UL, ea, 0, 3, 0, 0) &&
        parse_operand(2UL, d, 0x14, 0, 0, 0)) {
        enc_lua(insn, ea, d);
        return 1;
    }
    return 0;
}

/* 00425a60 */
static int p_div(void *insn)
{
    OPERAND s;
    OPERAND d;

    if (parse_operand(1UL, s, 0xb, 0, 0, 0) &&
        parse_operand(0UL, d, 1, 0, 0, 0)) {
        enc_div(insn, s, d);
        return 1;
    }
    return 0;
}

/* 00425abb: bchg bclr bset btst */
static int p_bitop(int iclass, void *insn)
{
    OPERAND bitno;
    OPERAND op;
    int ok;

    ok = 1;
    if (!parse_operand(5UL, bitno, 0, 0, 0, 4)) {
        ok = 0;
        skip_symbol();
    }
    if (!get_mem_space(op, CpuVariant == 0UL ? 5 : 7)) {
        free_cform(bitno);
        return 0;
    }
    if (SPACE(op) == 4) {
        if (!parse_operand(0UL, op, 0x11, 0, 0, 0)) {
            free_cform(bitno);
            return 0;
        }
        if (iclass == 6) {
            if (REG(op) == 0x2eL && do_check_end_range_err(2) != 0)
                ok = 0;
        } else if (!pseudo_check_move_class((int)REG(op))) {
            ok = 0;
        }
        if (ok == 0) {
            free_cform(bitno);
            return 0;
        }
        enc_bit_reg(insn, bitno, op);
    } else {
        if (!parse_operand(0UL, op, 0, 1, 6, 0)) {
            NWORDS(insn) = (FORCE(op) == FORCE_SHORT ||
                            FORCE(op) == FORCE_IO) ? 1UL : 2UL;
            free_cform(bitno);
            return 0;
        }
        if (ok == 0) {
            NWORDS(insn) = 2UL;
            free_cform(bitno);
            return 0;
        }
        switch (MODE(op)) {
        case 0x10:
            enc_bit_abs(insn, bitno, op);
            break;
        case 0x11:
            enc_bit_pp(insn, bitno, op);
            break;
        default:
            enc_bit_ea(insn, bitno, op);
            break;
        }
    }
    return ok;
}

/* the DO / REP loop-count source parsing shared by p_do and p_rep */

/* 00425d15 */
static int p_do(void *insn)
{
    OPERAND src;
    OPERAND target;
    int ok;

    ok = 1;
    optr = MnemField;
    HazardCur |= 0x200UL;
    if ((HazardPrev & 1UL) == 0UL) {
        if ((HazardPrev & 4UL) != 0UL) {
            if (!hazard_or_nop("Instruction cannot appear immediately after control register access"))
                ok = 0;
        }
    } else {
        err("Cannot repeat this instruction");
        HazardPrev &= ~1UL;
        ok = 0;
    }
    if (do_check_end_range_err(2) != 0)
        ok = 0;
    optr = Op1Field;
    NWORDS(insn) = 2UL;
    SPACE(target) = 4;
    if (!get_mem_space(src, 7))
        return 0;
    if (SPACE(src) == 4) {
        if (!parse_operand(1UL, src, 0x11, 0, 0, 2)) {
            ok = 0;
            skip_symbol();
        }
        if (MODE(src) == 1L && REG(src) == 0x2eL) {
            err("Illegal use of SSH as loop count operand");
            free_cform(src);
            return 0;
        }
        if (!parse_operand(4UL, target, 0, 0, 1, 0)) {
            free_cform(src);
            return 0;
        }
        if (OptMsw && merge_mem_space((unsigned long)SPACE(target), 0UL) ==
            0xa2c2aUL)
            warn("Absolute address involves incompatible memory spaces");
        if (ok == 0) {
            free_cform(src);
            return 0;
        }
        if (MODE(src) == 10L)
            enc_do_imm(insn, src, target);
        else
            enc_do_reg(insn, src, target);
    } else {
        if (!parse_operand(1UL, src, 0, 1, 4, 0)) {
            ok = 0;
            skip_symbol();
        }
        if (!parse_operand(4UL, target, 0, 0, 1, 0)) {
            free_cform(src);
            return 0;
        }
        if (OptMsw && merge_mem_space((unsigned long)SPACE(target), 0UL) ==
            0xa2c2aUL)
            warn("Absolute address involves incompatible memory spaces");
        if (ok == 0) {
            free_cform(src);
            return 0;
        }
        if (MODE(src) == 0x10L)
            enc_do_abs(insn, src, target);
        else
            enc_do_ea(insn, src, target);
    }
    if (Pass == 2UL && !InLineReplay) {
        optr = (char *)0;
        if (CurrentAddress + 1UL < WORD1(insn)) {
            if (DoStack == (void *)0 ||
                WORD1(insn) < ((struct do_node *)DoStack)->la) {
                struct do_node *node;

                node = (struct do_node *)xmalloc(sizeof(struct do_node));
                node->la = WORD1(insn);
                node->saved = 0UL;
                node->pc = 0UL;
                node->next = (struct do_node *)DoStack;
                HazardCur |= 0x100UL;
                DoStack = (void *)node;
            } else {
                warn("Improper nesting of DO loops");
                ok = 0;
            }
        } else {
            err("Negative or empty DO loop not allowed");
            ok = 0;
        }
    }
    return ok;
}

/* 00426106 */
static int p_enddo(void)
{
    int ok;

    optr = MnemField;
    HazardCur |= 0x200UL;
    ok = (HazardPrev & 1UL) != 0UL;
    if (ok)
        err("Cannot repeat this instruction");
    ok = !ok;
    if ((HazardPrev & 8UL) != 0UL) {
        if (!hazard_or_nop("Instruction cannot appear immediately after control register access"))
            ok = 0;
    }
    optr = Op1Field;
    field_shift();
    return ok;
}

/* 004261da */
static int p_rep(void *insn)
{
    OPERAND src;
    int ok;

    optr = MnemField;
    HazardCur |= 1UL;
    ok = (HazardPrev & 1UL) != 0UL;
    if (ok)
        err("Cannot repeat this instruction");
    ok = !ok;
    if (do_check_end_range_err(0) != 0)
        ok = 0;
    optr = Op1Field;
    if (!get_mem_space(src, 7)) {
        ok = 0;
    } else if (SPACE(src) == 4) {
        if (!parse_operand(0UL, src, 0x11, 0, 0, 2)) {
            ok = 0;
        } else if (MODE(src) == 1L) {
            enc_loop_reg(insn, src);
        } else if (MODE(src) == 10L) {
            enc_loop_imm(insn, src);
        }
    } else {
        if (!parse_operand(0UL, src, 0, 1, 4, 0)) {
            ok = 0;
        } else if (MODE(src) == 0x10L) {
            enc_loop_abs(insn, src);
        } else {
            enc_loop_ea(insn, src);
        }
    }
    return ok;
}

/* ------------------------------------------------------------------ */
/* jumps.  The span-dependent-instruction optimiser (sdi.c) is not part
   of this reconstruction: the long/short choice is made from the
   operand and the address of the jump.                                 */

static int fields_use_xref(void)
{
    char *fields[2];
    char name[128];
    char *p;
    int f;
    int n;

    if (AbsoluteMode)
        return 0;
    fields[0] = Op1Field;
    fields[1] = Op2Field;
    for (f = 0; f < 2; ++f) {
        p = fields[f];
        while (p != (char *)0 && *p != '\0') {
            if (isalpha((unsigned char)*p) || *p == '_') {
                n = 0;
                while ((isalnum((unsigned char)*p) || *p == '_' ||
                        *p == '.') && n < 127)
                    name[n++] = *p++;
                name[n] = '\0';
                if (sec_is_xref(name))
                    return 1;
            } else
                ++p;
        }
    }
    return 0;
}

/* 00426305 / 0042666f: jcc jmp jscc jsr */
static int p_jump(unsigned long id, int iclass, void *insn)
{
    OPERAND op;
    int ok;
    int is_sub;

    is_sub = iclass == 0x10 || iclass == 0x12;
    ok = 1;
    optr = MnemField;
    if (do_check_end_range_err(0) != 0)
        ok = 0;
    if ((HazardPrev & 1UL) != 0UL) {
        err("Cannot repeat this instruction");
        HazardPrev &= ~1UL;
        ok = 0;
    }
    optr = Op1Field;
    SPACE(op) = 4;
    if (!parse_operand(is_sub ? 4UL : 0UL, op, 0x10, 1, 5, 0)) {
        NWORDS(insn) = (FORCE(op) != FORCE_SHORT) + 1UL;
        return 0;
    }
    if (OptMsw && merge_mem_space((unsigned long)SPACE(op), 0UL) == 0xa2c2aUL)
        warn("Absolute address involves incompatible memory spaces");
    if (MODE(op) == 1L) {
        MODE(op) = 2;
        check_areg_stall((int)REG(op), 2);
    }
    if (is_sub && Pass == 2UL && DoStack != (void *)0 &&
        ((unsigned long *)DoStack)[0] == (unsigned long)VALUE(op) &&
        (MODE(op) == 0xf || MODE(op) == 0xe)) {
        err("Subroutine jump to loop address not allowed");
        ok = 0;
    }
    if (id == 83UL && Op1Field != (char *)0 && strcmp(Op1Field, "*") == 0) {
        WORD0(insn) = 0xf2000UL | ((unsigned long)VALUE(op) & 0xffffUL);
        return ok;
    }
    if (Pass == 2UL && ((unsigned long *)op)[7] != 0UL &&
        !fields_use_xref() && (MODE(op) == 0xfL || MODE(op) == 0xeL)) {
        /* an unresolved absolute jump still occupies its extension word */
        NWORDS(insn) = 2UL;
        return ok;
    }
    if (id == 60UL) {
        if (MODE(op) == 0xfL &&
            (FORCE(op) == FORCE_SHORT || Op1Field == (char *)0 ||
             !isalpha((unsigned char)Op1Field[0]) ||
             (unsigned long)VALUE(op) <= CurrentAddress)) {
            enc_jmp_abs(insn, op);
        } else {
            if (MODE(op) == 0xfL)
                MODE(op) = 0xe;
            enc_jmp_ea(insn, op);
        }
    } else if (id == 87UL) {
        if (MODE(op) == 0xfL)
            enc_jmp_abs(insn, op);
        else
            enc_jmp_ea(insn, op);
    } else if (id >= 66UL && id <= 86UL) {
        if (MODE(op) == 0xfL)
            MODE(op) = 0xe;
        enc_jcc_ea(insn, op);
    } else if (MODE(op) == 0xfL) {
        enc_jcc_abs(insn, op);
    } else {
        enc_jcc_ea(insn, op);
    }
    if (id == 62UL && Op1Field != (char *)0 && strcmp(Op1Field, "*") == 0)
        WORD0(insn) |= 0x2000UL;
    return ok;
}

/* 00426a45: jclr jset jsclr jsset */
static int p_jbit(int iclass, void *insn)
{
    OPERAND bitno;
    OPERAND op;
    OPERAND target;
    int ok;

    ok = 1;
    optr = MnemField;
    if ((HazardPrev & 1UL) != 0UL) {
        err("Cannot repeat this instruction");
        HazardPrev &= ~1UL;
        ok = 0;
    }
    optr = Op1Field;
    NWORDS(insn) = 2UL;
    if (!parse_operand(5UL, bitno, 0, 0, 0, 4)) {
        ok = 0;
        skip_symbol();
    }
    if (!get_mem_space(op, CpuVariant == 0UL ? 5 : 7)) {
        free_cform(bitno);
        return 0;
    }
    if (SPACE(op) == 4) {
        if (!parse_operand(1UL, op, 0x11, 0, 0, 0)) {
            ok = 0;
            skip_symbol();
        }
        if (REG(op) == 0x2eL && do_check_end_range_err(2) != 0)
            ok = 0;
    } else {
        if (!parse_operand(1UL, op, 0, 1, 7, 0)) {
            ok = 0;
            skip_symbol();
        }
    }
    SPACE(target) = 4;
    if (!parse_operand(0UL, target, 0, 0, 1, 0)) {
        free_cform(bitno);
        free_cform(op);
        return 0;
    }
    if (OptMsw && merge_mem_space((unsigned long)SPACE(target), 0UL) ==
        0xa2c2aUL)
        warn("Absolute address involves incompatible memory spaces");
    if (ok == 0) {
        free_cform(bitno);
        free_cform(op);
        free_cform(target);
        return 0;
    }
    if (Pass == 2UL && iclass == 0x11 && DoStack != (void *)0 &&
        ((unsigned long *)DoStack)[0] == (unsigned long)VALUE(target)) {
        err("Subroutine jump to loop address not allowed");
        free_cform(bitno);
        free_cform(op);
        free_cform(target);
        return 0;
    }
    if ((REG(op) == 0x2eL || REG(op) == 0x2fL) &&
        (HazardPrev & 0x10UL) != 0UL)
        hazard_or_nop("Jump based on SSH or SSL cannot follow update of SP");
    if (MODE(op) == 1L)
        enc_jbit_reg(insn, bitno, op, target);
    else if (MODE(op) == 0x10L)
        enc_jbit_abs(insn, bitno, op, target);
    else if (MODE(op) == 0x11L)
        enc_jbit_pp(insn, bitno, op, target);
    else
        enc_jbit_ea(insn, bitno, op, target);
    return ok;
}

/* 00426dc3 */
static int p_tcc(void *insn)
{
    OPERAND s1;
    OPERAND d1;
    OPERAND s2;
    OPERAND d2;
    int dclass;

    if (!parse_operand(1UL, s1, 0xf, 0, 0, 0))
        return 0;
    if (REG(s1) == 2L)
        dclass = 0xe;
    else
        dclass = REG(s1) != 3L ? 1 : 0xd;
    if (!parse_operand(0UL, d1, dclass, 0, 0, 0))
        return 0;
    if (*Op2Field == '\0') {
        enc_tcc(insn, s1, d1);
        return 1;
    }
    if (!check_extra_operand())
        return 0;
    optr = Op2Field;
    if (!parse_operand(1UL, s2, 0x10, 0, 0, 0))
        return 0;
    if (!parse_operand(2UL, d2, 0x10, 0, 0, 0))
        return 1;
    enc_tcc_r(insn, s1, d1, s2, d2);
    return 1;
}

/* 00426ee5: mac macr mpy mpyr */
static int p_mul(int iclass, void *insn)
{
    OPERAND s1;
    OPERAND s2;
    OPERAND d;
    int neg;

    neg = 0;
    if (*optr == '+') {
        ++optr;
    } else if (*optr == '-') {
        ++optr;
        neg = 1;
    }
    if (!parse_operand(1UL, s1, 0xb, 0, 0, 0) ||
        !parse_operand(5UL, s2, 0xb, 0, 0, 4) ||
        !parse_operand(2UL, d, 1, 0, 0, 0))
        return 0;
    if (MODE(s2) == 1L) {
        if (neg)
            WORD0(insn) |= 4UL;
        mulreg((int)REG(s1), (int)REG(s2), (int)REG(d), &WORD0(insn));
        return 1;
    }
    if (FWD(s2) == 0L && (!AbsoluteMode || SECT(s2) >= 0L)) {
        err("Invalid shift amount");
        free_cform(s2);
        return 0;
    }
    switch (iclass) {
    case 0x15: WORD0(insn) = 0x100c2UL; break;
    default:
        fatal("Invalid instruction class");
        break;
    case 0x1a: WORD0(insn) = 0x100c0UL; break;
    case 0x2a: WORD0(insn) = 0x100c3UL; break;
    case 0x2b: WORD0(insn) = 0x100c1UL; break;
    }
    if (neg)
        WORD0(insn) |= 4UL;
    enc_mul_imm(insn, s1, s2, d);
    return 0;
}

/* 004270d6: move movec movem */
static int p_move(void)
{
    char *op1;
    int ok;

    ok = check_extra_operand();
    op1 = Op1Field;
    if (!ok)
        return 0;
    field_shift();
    if (*op1 == '\0') {
        err("Not enough fields specified for instruction");
        return 0;
    }
    return 1;
}

#define OUTR(v) \
    (((unsigned long)(v) < 0xffc0UL || (unsigned long)(v) > 0xffffUL) && \
     ((unsigned long)(v) < 0x40UL || (unsigned long)(v) > 0x7fUL))

/* 0042712b: movep */
static int p_movep(void *insn)
{
    OPERAND a;
    OPERAND b;
    char *msg;
    char *first;
    int ok;
    int space_b_mask;
    int forced_a;
    int forced_b;
    long vala;
    long valb;

    first = Op1Field;
    ok = 0;
    space_b_mask = 5;
    if (*Op2Field != '\0') {
        err("Too many fields specified for instruction");
        err("Possible invalid white space between operands or arguments");
        return 0;
    }
    field_shift();
    if (*first == '\0') {
        err("Not enough fields specified for instruction");
        return 0;
    }
    msg = "I/O short addressing must be used for either source or destination";
    if (!get_mem_space(a, 9))
        return 0;
    if (SPACE(a) == 0L) {
        msg = "I/O short addressing must be used for destination operand";
        forced_a = parse_operand(1UL, a, 0, 1, 1, 0);
    } else if (SPACE(a) == 4L) {
        msg = "I/O short addressing must be used for destination operand";
        forced_a = parse_operand(1UL, a, 0x11, 0, 0, 1);
    } else {
        space_b_mask = 9;
        forced_a = parse_operand(1UL, a, 0, 1, 8, 0);
    }
    if (!forced_a) {
        NWORDS(insn) = 2UL;
        ok = 1;
        skip_symbol();
    }
    if (!get_mem_space(b, space_b_mask))
        return 0;
    if (!(SPACE(a) == 1L || SPACE(a) == 2L || SPACE(b) == 1L ||
          SPACE(b) == 2L)) {
        err("Either source or destination memory space must be X or Y");
        free_cform(a);
        free_cform(b);
        return 0;
    }
    if (SPACE(b) == 0L) {
        msg = "I/O short addressing must be used for source operand";
        forced_b = parse_operand(2UL, b, 0, 1, 1, 0);
    } else if (SPACE(b) == 4L) {
        msg = "I/O short addressing must be used for source operand";
        forced_b = parse_operand(2UL, b, 0x11, 0, 0, 0);
    } else {
        forced_b = parse_operand(2UL, b, 0, 1, 8, 0);
    }
    if (!forced_b) {
        NWORDS(insn) = 2UL;
        free_cform(a);
        free_cform(b);
        return 0;
    }
    if (ok != 0) {
        free_cform(a);
        free_cform(b);
        return 0;
    }
    if (SPACE(a) != 1L && SPACE(b) != 1L)
        NWORDS(insn) = 2UL;
    if (DoStack != (void *)0 &&
        (REG(b) == 0x2eL || (REG(a) > 0x2aL && REG(a) < 0x31L)))
        do_check_end_range_err(2);
    if ((REG(b) == 0x2eL || REG(b) == 0x2fL) && (HazardPrev & 0x10UL) != 0UL)
        hazard_or_nop("Move from SSH or SSL cannot follow update of SP");
    if (REG(b) == 0x2eL)
        HazardCur |= 0x24cUL;
    switch (REG(a)) {
    case 0x2b: HazardCur |= 0x288UL; break;
    case 0x2c:
    case 0x2d: HazardCur |= 0x20cUL; break;
    case 0x30: HazardCur |= 0x210UL;
        /* fall through */
    case 0x2e:
    case 0x2f: HazardCur |= 0x24cUL; break;
    default: break;
    }
    if (CpuVariant > 1UL && REG(a) > 0xdL && REG(a) < 0x26L)
        AregWritten = 0UL;
    vala = VALUE(a);
    valb = VALUE(b);
    forced_a = FORCE(a) != 0L;
    forced_b = FORCE(b) != 0L;
    if (MODE(a) == 0x11L && MODE(b) == 0x11L) {
        if (!forced_a || !forced_b) {
            if (!forced_a) {
                if (!forced_b) {
                    if (SPACE(a) == 0L)
                        MODE(a) = 0xe;
                    else
                        MODE(b) = 0xe;
                } else {
                    MODE(a) = 0xe;
                }
            } else {
                MODE(b) = 0xe;
            }
        } else {
            warn("Cannot force short addressing for source and destination");
            MODE(b) = 0xe;
        }
    } else if (MODE(a) != 0x11L && MODE(b) != 0x11L) {
        if (MODE(a) != 0xeL && MODE(b) != 0xeL) {
            err(msg);
            free_cform(a);
            free_cform(b);
            return 0;
        }
        if (MODE(a) == 0xeL && MODE(b) == 0xeL) {
            if (forced_a && forced_b) {
                err(msg);
                free_cform(a);
                free_cform(b);
                return 0;
            }
            if (!forced_a) {
                if (!forced_b) {
                    if (SPACE(a) == 0L) {
                        if (!InLineReplay && OUTR(valb)) {
                            err(msg);
                            free_cform(a);
                            free_cform(b);
                            return 0;
                        }
                        MODE(b) = 0x11;
                    } else if (SPACE(b) == 0L) {
                        if (!InLineReplay && OUTR(vala)) {
                            err(msg);
                            free_cform(a);
                            free_cform(b);
                            return 0;
                        }
                        MODE(a) = 0x11;
                    } else {
                        MODE(a) = 0x11;
                        if (Pass == 2UL && !InLineReplay && OUTR(vala)) {
                            if (OUTR(valb)) {
                                err(msg);
                                free_cform(a);
                                free_cform(b);
                                return 0;
                            }
                            MODE(b) = 0x11;
                            MODE(a) = 0xe;
                            if ((unsigned long)valb > 0x3fUL &&
                                (unsigned long)valb < 0x80UL)
                                warn("Destination operand assumed I/O short");
                            if ((unsigned long)vala > 0x3fUL &&
                                (unsigned long)vala < 0x80UL &&
                                FORCE(a) != FORCE_IO)
                                warn("Source operand assumed I/O short");
                        }
                    }
                } else {
                    MODE(a) = 0x11;
                    if (SPACE(a) == 0L ||
                        (Pass == 2UL && !InLineReplay && OUTR(vala))) {
                        err(msg);
                        free_cform(a);
                        free_cform(b);
                        return 0;
                    }
                    if ((unsigned long)vala > 0x3fUL &&
                        (unsigned long)vala < 0x80UL)
                        warn("Source operand assumed I/O short");
                }
            } else {
                MODE(b) = 0x11;
                if (SPACE(b) == 0L ||
                    (Pass == 2UL && !InLineReplay && OUTR(valb))) {
                    err(msg);
                    free_cform(a);
                    free_cform(b);
                    return 0;
                }
                if ((unsigned long)valb > 0x3fUL &&
                    (unsigned long)valb < 0x80UL && FORCE(b) != FORCE_IO)
                    warn("Destination operand assumed I/O short");
            }
        } else if (MODE(a) == 0xeL) {
            if (forced_a || SPACE(a) == 0L) {
                err(msg);
                free_cform(a);
                free_cform(b);
                return 0;
            }
            MODE(a) = 0x11;
            if (Pass == 2UL && !InLineReplay && OUTR(vala)) {
                err(msg);
                free_cform(a);
                free_cform(b);
                return 0;
            }
            if ((unsigned long)vala > 0x3fUL && (unsigned long)vala < 0x80UL)
                warn("Source operand assumed I/O short");
        } else if (MODE(b) == 0xeL) {
            if (forced_b || SPACE(b) == 0L) {
                free_cform(a);
                free_cform(b);
                err(msg);
                return 0;
            }
            MODE(b) = 0x11;
            if (Pass == 2UL && !InLineReplay && OUTR(valb)) {
                err(msg);
                free_cform(a);
                free_cform(b);
                return 0;
            }
            if ((unsigned long)valb > 0x3fUL && (unsigned long)valb < 0x80UL)
                warn("Destination operand assumed I/O short");
        }
    }
    if (MODE(a) == 9L || MODE(a) == 0xeL || MODE(b) == 0xeL)
        NWORDS(insn) = 2UL;
    else
        NWORDS(insn) = 1UL;
    if (MODE(a) == 0x11L) {
        if (MODE(b) == 1L)
            enc_movep_reg(insn, a, b);
        else
            enc_movep_mem(insn, a, b);
    } else if (MODE(a) == 1L) {
        enc_movep_reg_w(insn, a, b);
    } else {
        enc_movep_mem_w(insn, a, b);
    }
    (void)first;
    return 1;
}

/* ------------------------------------------------------------------ */
/* proc_instr                                                          */

static void save_fields(char **f)
{
    f[0] = LabelField;
    f[1] = MnemField;
    f[2] = Op1Field;
    f[3] = Op2Field;
    f[4] = Op3Field;
    f[5] = Op4Field;
}

static void restore_fields(char **f)
{
    LabelField = f[0];
    MnemField = f[1];
    Op1Field = f[2];
    Op2Field = f[3];
    Op3Field = f[4];
    Op4Field = f[5];
}

/* Relocation string of the instruction word being emitted (valid inside the
   emit callback). */
static char *EmitReloc;

char *asm56000_emit_reloc(void)
{
    return EmitReloc;
}

static void finish_insn(unsigned long *insn)
{
    int i;
    unsigned long n;

    n = NWORDS(insn);
    if (n < 1UL)
        n = 1UL;
    if (n > 2UL)
        n = 2UL;
    LastCount = (int)n;
    for (i = 0; i < LastCount; ++i) {
        LastWords[i] = (i == 0 ? WORD0(insn) : WORD1(insn)) & 0xffffffUL;
        EmitReloc = *(char **)((char *)insn + (i == 0 ?
                                               ASM56000_INSN_CFORM0 :
                                               ASM56000_INSN_CFORM1));
        if (EmitWord != (void (*)(unsigned long, int))0)
            EmitWord(LastWords[i], i);
        EmitReloc = (char *)0;
    }
    for (; i < 2; ++i)
        LastWords[i] = 0UL;
    xfree(*(char **)((char *)insn + ASM56000_INSN_CFORM0));
    xfree(*(char **)((char *)insn + ASM56000_INSN_CFORM1));
}

static int proc_instr_id(unsigned long id)
{
    INSN insn;
    OPERAND xs;
    OPERAND xd;
    OPERAND ys;
    OPERAND yd;
    char *saved_fields[6];
    int iclass;
    int result;
    unsigned long pm;
    int saved_multiple;
    int i;

    iclass = InfoTab[id].iclass;
    result = 1;
    for (i = 0; i < 24; ++i)
        insn[i] = 0UL;
    for (i = 0; i < 10; ++i)
        xs[i] = xd[i] = ys[i] = yd[i] = 0UL;
    if (!(CurrentSpace == 0 || (CurrentSpace >= 13 && CurrentSpace <= 15))) {
        err("Runtime space must be P");
        LastCount = 0;
        LastWords[0] = LastWords[1] = 0UL;
        return 0;
    }
    saved_multiple = ErrMultiple;
    ErrMultiple = 1;
    save_fields(saved_fields);
    do_line_reset();
    NWORDS(insn) = 1UL;
    WORD0(insn) = InfoTab[id].templ;
    WORD1(insn) = 0UL;
    optr = Op1Field;
    switch (iclass) {
    case 1: result = p_addl(insn); break;
    case 2: case 3: case 0x27: case 0x28:
        result = p_alu1(iclass, insn); break;
    case 4: result = p_and_or(insn); break;
    case 5: case 6: result = p_bitop(iclass, insn); break;
    case 7: case 0x22: case 0x23: result = p_alu2(iclass, insn); break;
    case 8: result = p_div(insn); break;
    case 9: result = p_do(insn); break;
    case 10: result = p_enddo(); break;
    case 0xb: case 0xc: case 0xd: case 0x1b: case 0x29: case 0x2c:
        result = p_noarg(iclass); break;
    case 0xe: case 0x13: case 0x10: case 0x12:
        result = p_jump(id, iclass, insn); break;
    case 0xf: case 0x11: result = p_jbit(iclass, insn); break;
    case 0x14: result = p_lua(insn); break;
    case 0x15: case 0x1a: case 0x2a: case 0x2b:
        result = p_mul(iclass, insn); break;
    case 0x16: case 0x17: case 0x18: result = p_move(); break;
    case 0x19: result = p_movep(insn); break;
    case 0x1c: result = p_norm(insn); break;
    case 0x1d: result = p_rep(insn); break;
    case 0x1e: case 0x1f: result = p_rts(iclass); break;
    case 0x20: case 0x24: result = p_eor_adc(iclass, insn); break;
    case 0x25: result = p_andi(insn); break;
    case 0x26: result = p_tcc(insn); break;
    default:
        fatal("Error in mnemonic table");
        break;
    }
    if (InfoTab[id].pm == 2) {
        pm = (unsigned long)result;
        result = 1;
    } else {
        pm = InfoTab[id].pm;
    }
    if (pm == 0UL) {
        if (*Op2Field != '\0' && iclass != 0x19 && iclass != 0x26) {
            err("Too many fields specified for instruction");
            err("Possible invalid white space between operands or arguments");
            result = 0;
        }
    } else if (*Op2Field == '\0') {
        WORD0(insn) |= 0x200000UL;
    } else {
        if (Op4Field != (char *)0 && *Op4Field != '\0' && *Op4Field != ';') {
            err("Too many fields specified for instruction");
            err("Possible invalid white space between operands or arguments");
        }
        SPACE(xs) = 4;
        SPACE(xd) = 4;
        SPACE(ys) = 4;
        SPACE(yd) = 4;
        lst_xy_needs_swap();
        result = do_xy(insn, pm, xs, xd, ys, yd);
        lst_xy_needs_swap();
        if (iclass == 0x16 && !CtrlRegAccessed)
            warn("No control registers accessed - using MOVE encoding");
        if (iclass == 0x18 && SPACE(xs) != 0L && SPACE(xd) != 0L)
            warn("P space not accessed - using MOVE encoding");
    }
    PrevInstrWords = (long)NWORDS(insn);
    if (DoStack != (void *)0)
        do_stack_unwind(NWORDS(insn));
    if (VectorCheckHook != (int (*)(void))0 && VectorCheckHook() &&
        (HazardCur & 0x200UL) != 0UL) {
        optr = MnemField;
        warn("Instruction cannot appear in interrupt vector locations");
    }
    if (NWORDS(insn) == 2UL) {
        if ((HazardPrev & 1UL) != 0UL) {
            optr = MnemField;
            err("Cannot repeat two-word instruction");
            result = 0;
        }
        if (do_check_end_range_err(0) != 0)
            result = 0;
    }
    finish_insn(insn);
    free_cform(xs);
    free_cform(xd);
    free_cform(ys);
    free_cform(yd);
    ErrMultiple = saved_multiple;
    return result;
}

int proc_instr(void *ientry)
{
    unsigned long id;

    id = table_entry_id(ientry);
    if (id == 0xffffffffUL || id >= 142UL)
        return 0;
    return proc_instr_id(id);
}

int proc_instr_name(char *name)
{
    void *entry;

    entry = find_mnemonic(name, 0);
    if (entry == (void *)0)
        return 0;
    return proc_instr(entry);
}

void asm56000_set_emit_callback(void (*callback)(unsigned long word, int index))
{
    EmitWord = callback;
}

unsigned long asm56000_last_word(int index)
{
    if (index < 0 || index >= 2)
        return 0UL;
    return LastWords[index];
}

void asm56000_set_last_word(int index, unsigned long word)
{
    if (index < 0 || index >= 2)
        return;
    LastWords[index] = word & 0xffffffUL;
}

int asm56000_last_count(void)
{
    return LastCount;
}
