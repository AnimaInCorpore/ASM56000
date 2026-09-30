/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7, DSPLNK.EXE), arith.c
 * Original module: "$Id: arith.c,v 1.27 1995/02/21 22:24:24 tomc Exp $"
 * Reconstructed from 004058d0-00408bdf.
 *
 * Expression operators and value conversions.  An integer EXPR holds three
 * target words (hi, mid, lo), each masked with word_mask; a floating EXPR
 * (type EXPR_FLT) keeps its value in the port-only field fval (the original
 * overlays the double on hi/mid).  All word arithmetic is done in
 * unsigned long and masked to 32 bits where the original relies on
 * 32-bit wraparound.
 */
#include "dsplnk.h"

/* signed interpretation of a 32-bit value */
static long sx32(unsigned long v)
{
    v = M32(v);
    if (v & 0x80000000UL)
        return -(long)(~v & 0x7fffffffUL) - 1L;
    return (long)v;
}

/* x86 shifts use the count modulo 32 */
static unsigned long shl32(unsigned long v, long n)
{
    return M32(v << (int)(n & 31));
}

static unsigned long shr32(unsigned long v, long n)
{
    return M32(v) >> (int)(n & 31);
}

/* MSVC _ftol: truncate toward zero, low 32 bits of the 64-bit result */
static unsigned long ftol32(double t)
{
    double u;
    unsigned long r;

    if (t >= 0.0) {
        u = floor(t);
        if (u >= 4294967296.0)
            u = fmod(u, 4294967296.0);
        return (unsigned long)u;
    }
    u = floor(-t);
    if (u >= 4294967296.0)
        u = fmod(u, 4294967296.0);
    r = (unsigned long)u;
    return M32(0UL - r);
}

static void set_float_result(EXPR *a, double d)
{
    a->fval = d;
    a->type = EXPR_FLT;
    a->map = MS_N;
    a->space = MS_N;
    a->ctr = 0;
    a->attr = 0;
    a->size = EXPR_SIZE_FLT;
}

double value_to_double(EXPR *e);
int op_check_operands(EXPR *a, EXPR *b);
long value_truth(EXPR *e);
void op_compare(int op, EXPR *a, EXPR *b);
void bigint_divmod(unsigned long ah, unsigned long am, unsigned long al,
                   unsigned long bh, unsigned long bm, unsigned long bl,
                   unsigned long *qh, unsigned long *qm, unsigned long *ql,
                   unsigned long *rh, unsigned long *rm, unsigned long *rl);
int bigint_cmp3(unsigned long ah, unsigned long am, unsigned long al,
                unsigned long bh, unsigned long bm, unsigned long bl);
void bigint_from_words(unsigned long hi, unsigned long mid, unsigned long lo,
                       unsigned long *out);
void bigint_to_words(unsigned long *in, unsigned long *hi, unsigned long *mid,
                     unsigned long *lo);
void bigint_copy(unsigned long *src, unsigned long *dst, int n);
unsigned long bigint_div_digit(unsigned long *divisor, unsigned long *rem,
                               int n, unsigned long *work);
void bigint_mul_small(unsigned long digit, unsigned long *src,
                      unsigned long *dst, int n);
int bigint_cmp_ge(unsigned long *a, unsigned long *b, int n);
void bigint_sub(unsigned long *sub, unsigned long *acc, int n);
int bigint_limb_count(unsigned long *a);
void check_pcrel_range(unsigned long v, int bits, int align);
void check_signed_range(unsigned long v, int bits, int align);
void check_unsigned_range(unsigned long v, int bits, int align);
void check_szck_range(unsigned long v, int kind, int bits, int align);
int szck_kind(EXPR *e);
int szck_bits(EXPR *e);
int szck_align(EXPR *e);

/* 004058d0 */
EXPR *op_add(EXPR *a, EXPR *b)
{
    int sa, sb, c1, c2;
    unsigned long t;

    if (a->type == EXPR_INT && b->type == EXPR_INT) {
        if (in_brace && !op_check_operands(a, b))
            return NULL;
        sa = (a->lo & sign_bit) != 0;
        sb = (b->lo & sign_bit) != 0;
        c1 = ((sa && sb) || ((M32(a->lo + b->lo) & sign_bit) == 0 && (sa || sb)));
        a->lo = M32(a->lo + b->lo) & word_mask;
        t = M32(a->mid + b->mid + (unsigned long)c1);
        sa = (a->mid & sign_bit) != 0;
        sb = (b->mid & sign_bit) != 0;
        c2 = ((sa && sb) || ((t & sign_bit) == 0 && (sa || sb)));
        a->mid = t & word_mask;
        a->hi = M32(a->hi + b->hi + (unsigned long)c2) & word_mask;
        classify_value(a);
    } else if (!(a->flags & EXPR_REL) && !(b->flags & EXPR_REL)) {
        double da, db;
        da = value_to_double(a);
        db = value_to_double(b);
        set_float_result(a, db + da);
    } else {
        free_expr(a);
        free_expr(b);
        lnk_error1("Floating point not allowed in relative expression");
        a = NULL;
    }
    return a;
}

/* 00405b12 */
EXPR *op_sub(EXPR *a, EXPR *b)
{
    if (a->type == EXPR_INT && b->type == EXPR_INT) {
        negate_value(b);
        a = op_add(a, b);
    } else if (!(a->flags & EXPR_REL) && !(b->flags & EXPR_REL)) {
        double da, db;
        da = value_to_double(a);
        db = value_to_double(b);
        set_float_result(a, da - db);
    } else {
        free_expr(a);
        free_expr(b);
        lnk_error1("Floating point not allowed in relative expression");
        a = NULL;
    }
    return a;
}

/* 00405bff: operand check of '+' inside {...}; 1 ok, 0 error (both freed) */
int op_check_operands(EXPR *a, EXPR *b)
{
    int bad;

    if (((a->hi & sign_bit) == 0 || (b->hi & sign_bit) != 0) &&
        ((a->hi & sign_bit) != 0 || (b->hi & sign_bit) == 0) &&
        expr_as_int32(a) != 0 && expr_as_int32(b) != 0)
        bad = 0;
    else
        bad = 1;
    if (a->space != MS_N && b->space != MS_N) {
        if (opt_aec && merge_mem_space(a->space, b->space) == MS_BAD) {
            lnk_error1("Expression involves incompatible memory spaces");
            free_expr(b);
            free_expr(a);
            return 0;
        }
        if (!bad) {
            lnk_error1("Invalid address expression");
            free_expr(a);
            free_expr(b);
            return 0;
        }
        addr_cancel = 1;
    }
    if ((a->flags & EXPR_REL) && (b->flags & EXPR_REL)) {
        if (opt_aec && a->sect >= 0 && b->sect >= 0 && a->sect != b->sect) {
            lnk_error1("Relative terms from different sections not allowed");
            free_expr(a);
            free_expr(b);
            return 0;
        }
        if (!bad) {
            lnk_error1("Invalid relative expression");
            free_expr(a);
            free_expr(b);
            return 0;
        }
    }
    return 1;
}

/* sign fixup shared by mul/div/mod */
static void sign_fixup(int s, EXPR *a, EXPR *b)
{
    if (s == 1) {
        negate_value(a);
    } else if (s == 2) {
        negate_value(a);
        negate_value(b);
    } else if (s == 3) {
        negate_value(b);
    }
}

/* 00405dd4 */
EXPR *op_mul(EXPR *a, EXPR *b)
{
    int s, i, j;
    unsigned long la[BIGINT_LIMBS], lr[BIGINT_LIMBS], lb[BIGINT_LIMBS];
    unsigned long acc;

    if (a->type != EXPR_INT || b->type != EXPR_INT) {
        double da, db;
        da = value_to_double(a);
        db = value_to_double(b);
        set_float_result(a, db * da);
        return a;
    }
    for (i = 0; i < BIGINT_LIMBS; i++)
        la[i] = lr[i] = lb[i] = 0;
    s = (a->hi & sign_bit) != 0;
    if (s)
        negate_value(a);
    if (b->hi & sign_bit) {
        negate_value(b);
        s |= 2;
    }
    bigint_from_words(a->hi, a->mid, a->lo, la);
    bigint_from_words(b->hi, b->mid, b->lo, lb);
    bigint_from_words(0, 0, 0, lr);
    acc = 0;
    for (i = 0; i < fmt_dword; i++) {
        for (j = 0; j <= i; j++)
            acc = M32(acc + la[j] * lb[i - j]);
        lr[i] = acc & 0xff;
        acc >>= 8;
    }
    bigint_to_words(lr, &a->hi, &a->mid, &a->lo);
    sign_fixup(s, a, b);
    classify_value(a);
    return a;
}

/* 00406037 */
EXPR *op_div(EXPR *a, EXPR *b)
{
    int s;
    unsigned long rh, rm, rl;
    double db;

    if (a->type != EXPR_INT || b->type != EXPR_INT) {
        db = value_to_double(b);
        if (db != 0.0) {
            set_float_result(a, value_to_double(a) / db);
            return a;
        }
        free_expr(b);
        free_expr(a);
        lnk_error1("Divide by zero");
        return NULL;
    }
    if (b->hi == 0 && b->mid == 0 && b->lo == 0) {
        free_expr(b);
        free_expr(a);
        lnk_error1("Divide by zero");
        return NULL;
    }
    s = (a->hi & sign_bit) != 0;
    if (s)
        negate_value(a);
    if (b->hi & sign_bit) {
        negate_value(b);
        s |= 2;
    }
    bigint_divmod(a->hi, a->mid, a->lo, b->hi, b->mid, b->lo,
                  &a->hi, &a->mid, &a->lo, &rh, &rm, &rl);
    sign_fixup(s, a, b);
    classify_value(a);
    return a;
}

/* 00406230 */
EXPR *op_mod(EXPR *a, EXPR *b)
{
    int s;
    unsigned long qh, qm, ql;
    double db;

    if (a->type != EXPR_INT || b->type != EXPR_INT) {
        db = value_to_double(b);
        if (db != 0.0) {
            set_float_result(a, fmod(value_to_double(a), db));
            return a;
        }
        free_expr(b);
        free_expr(a);
        lnk_error1("Divide by zero");
        return NULL;
    }
    if (b->hi == 0 && b->mid == 0 && b->lo == 0) {
        free_expr(b);
        free_expr(a);
        lnk_error1("Divide by zero");
        return NULL;
    }
    s = 0;
    if (a->hi & sign_bit) {
        negate_value(a);
        s |= 1;
    }
    if (b->hi & sign_bit) {
        negate_value(b);
        s |= 2;
    }
    bigint_divmod(a->hi, a->mid, a->lo, b->hi, b->mid, b->lo,
                  &qh, &qm, &ql, &a->hi, &a->mid, &a->lo);
    sign_fixup(s, a, b);
    classify_value(a);
    return a;
}

static EXPR *float_op_error(EXPR *a, EXPR *b)
{
    free_expr(a);
    free_expr(b);
    lnk_error1("Illegal operator for floating point element");
    return NULL;
}

/* 00406439 */
EXPR *op_and(EXPR *a, EXPR *b)
{
    if (a->type != EXPR_INT || b->type != EXPR_INT)
        return float_op_error(a, b);
    a->hi &= b->hi;
    a->mid &= b->mid;
    a->lo &= b->lo;
    classify_value(a);
    return a;
}

/* 004064c3 */
EXPR *op_or(EXPR *a, EXPR *b)
{
    if (a->type != EXPR_INT || b->type != EXPR_INT)
        return float_op_error(a, b);
    a->hi |= b->hi;
    a->mid |= b->mid;
    a->lo |= b->lo;
    classify_value(a);
    return a;
}

/* 0040654d */
EXPR *op_xor(EXPR *a, EXPR *b)
{
    if (a->type != EXPR_INT || b->type != EXPR_INT)
        return float_op_error(a, b);
    a->hi ^= b->hi;
    a->mid ^= b->mid;
    a->lo ^= b->lo;
    classify_value(a);
    return a;
}

static int shift_count_ok(EXPR *b, long *n)
{
    if (b->hi != 0 || b->mid != 0)
        return 0;
    *n = sx32(b->lo);
    return *n >= 0 && *n <= dword_bits;
}

/* 004065d7 */
EXPR *op_shl(EXPR *a, EXPR *b)
{
    long n;

    if (a->type != EXPR_INT || b->type != EXPR_INT)
        return float_op_error(a, b);
    if (!shift_count_ok(b, &n)) {
        free_expr(b);
        free_expr(a);
        lnk_error1("Invalid shift amount");
        return NULL;
    }
    while (n != 0) {
        a->hi = M32(a->hi << 1);
        if (a->mid & sign_bit)
            a->hi |= 1;
        a->mid = M32(a->mid << 1);
        if (a->lo & sign_bit)
            a->mid |= 1;
        a->lo = M32(a->lo << 1);
        n--;
    }
    classify_value(a);
    return a;
}

/* 00406706 */
EXPR *op_shr(EXPR *a, EXPR *b)
{
    long n;

    if (a->type != EXPR_INT || b->type != EXPR_INT)
        return float_op_error(a, b);
    if (!shift_count_ok(b, &n)) {
        free_expr(b);
        free_expr(a);
        lnk_error1("Invalid shift amount");
        return NULL;
    }
    while (n != 0) {
        n--;
        a->lo >>= 1;
        if (a->mid & 1)
            a->lo |= sign_bit;
        a->mid >>= 1;
        if (a->hi & 1)
            a->mid |= sign_bit;
        a->hi >>= 1;
        if (a->hi & (sign_bit >> 1))
            a->hi |= sign_bit;
    }
    classify_value(a);
    return a;
}

static void set_plain_int(EXPR *a, unsigned long v)
{
    a->lo = v;
    a->hi = 0;
    a->mid = 0;
    a->type = EXPR_INT;
    a->map = MS_N;
    a->space = MS_N;
    a->ctr = 0;
    a->attr = 0;
    a->size = fmt_word;
}

/* 0040685f */
EXPR *op_land(EXPR *a, EXPR *b)
{
    unsigned long v;

    v = (value_truth(a) != 0 && value_truth(b) != 0) ? 1UL : 0UL;
    set_plain_int(a, v);
    return a;
}

/* 004068f3 */
EXPR *op_lor(EXPR *a, EXPR *b)
{
    unsigned long v;

    v = (value_truth(a) == 0 && value_truth(b) == 0) ? 0UL : 1UL;
    set_plain_int(a, v);
    return a;
}

/* 00406987 .. 00406a09 */
EXPR *op_lt(EXPR *a, EXPR *b) { op_compare(OP_LT, a, b); return a; }
EXPR *op_gt(EXPR *a, EXPR *b) { op_compare(OP_GT, a, b); return a; }
EXPR *op_eq(EXPR *a, EXPR *b) { op_compare(OP_EQ, a, b); return a; }
EXPR *op_le(EXPR *a, EXPR *b) { op_compare(OP_LE, a, b); return a; }
EXPR *op_ge(EXPR *a, EXPR *b) { op_compare(OP_GE, a, b); return a; }
EXPR *op_ne(EXPR *a, EXPR *b) { op_compare(OP_NE, a, b); return a; }

/* alignment part of the range checks; returns the widened mask */
static unsigned long range_align(unsigned long v, unsigned long m, int align,
                                 char *wfmt, char *wmsg, char *lfmt, char *lmsg)
{
    char *buf;
    char *fmt;
    char *msg;

    fmt = NULL;
    msg = NULL;
    if (align == 'w') {
        m = M32(m << 1 | 1);
        if (v & 1) {
            fmt = wfmt;
            msg = wmsg;
        }
    } else if (align == 'l') {
        m = M32(m << 2 | 3);
        if (v & 3) {
            fmt = lfmt;
            msg = lmsg;
        }
    }
    if (msg != NULL) {
        if (sym_found == NULL) {
            lnk_error1(msg);
        } else {
            buf = (char *)xmalloc((unsigned long)strlen(sym_found->name) + 200UL);
            sprintf(buf, fmt, v, sym_found->name, sym_found->lo);
            lnk_error1(buf);
            xfree(buf);
        }
    }
    return m;
}

static unsigned long range_mask(int bits)
{
    unsigned long m;
    int i;

    m = 0;
    for (i = 0; i < bits; i++)
        m = M32(m << 1 | 1);
    return m;
}

/* 00406a23 */
void check_pcrel_range(unsigned long v, int bits, int align)
{
    unsigned long m, u;

    m = range_align(v, range_mask(bits), align,
        "Pc relative expression value (0x%lx) must be word aligned, last symbol referenced is: %s=0x%lx",
        "Pc relative expression value must be word aligned",
        "Pc relative expression value (0x%lx) must be long word aligned, last symbol referenced is: %s=0x%lx",
        "Pc relative expression value must be long word aligned");
    u = v & M32(~m);
    if (u != 0 && u != M32(~m))
        lnk_error1("Pc relative value out of range");
}

/* 00406b7c */
void check_signed_range(unsigned long v, int bits, int align)
{
    unsigned long m, u;

    m = range_align(v, range_mask(bits), align,
        "Signed expression value (0x%lx) must be word aligned, last symbol referenced is: %s=0x%lx",
        "Signed expression value must be word aligned",
        "Signed expression value (0x%lx) must be long word aligned, last symbol referenced is: %s=0x%lx",
        "Signed expression value must be long word aligned");
    u = v & M32(~m);
    if (u != 0 && u != M32(~m))
        lnk_error1("Signed value out of range");
}

/* 00406cd5 */
void check_unsigned_range(unsigned long v, int bits, int align)
{
    unsigned long m;

    m = range_align(v, range_mask(bits), align,
        "Unsigned expression value (0x%lx) must be word aligned, last symbol referenced is: %s=0x%lx",
        "Unsigned value must be word aligned",
        "Unsigned expression value (0x%lx) must be long word aligned, last symbol referenced is: %s=0x%lx",
        "Unsigned value must be long word aligned");
    if ((v & M32(~m)) != 0)
        lnk_error1("Unsigned value out of range");
}

/* 00406e26 */
void check_szck_range(unsigned long v, int kind, int bits, int align)
{
    switch (kind & 0xff) {
    case 'a':
    case 'u':
        check_unsigned_range(v, bits, align);
        break;
    case 'p':
        if (v < io_base)
            lnk_error1("Invalid IO address");
        break;
    case 'r':
        check_pcrel_range(v, bits, align);
        break;
    case 's':
        check_signed_range(v, bits, align);
        break;
    }
}

/* 00406edd: the '#' operator (operand bit size check) */
EXPR *op_size_check(EXPR *val, EXPR *code)
{
    char *msg;
    long c;
    unsigned long v;
    long sv;
    int kind, bits, align;

    msg = NULL;
    if (opt_i) {
        if (val->flags & EXPR_REL)
            return val;
        if (val->sect < 0)
            return val;
    }
    c = sx32(expr_as_int32(code));
    if (val->type == EXPR_INT) {
        if (val->size == fmt_dword || val->mid == word_mask || val->space == MS_N)
            v = expr_as_int32(val);
        else
            v = val->lo;
    } else if (target_index == TGT_96000) {
        v = float_bits(val->fval);
    } else {
        float_to_fixed_frac(val->fval, fmt_word, val);
        v = val->lo;
    }
    if (code->type == EXPR_SZCK) {
        kind = szck_kind(code);
        bits = szck_bits(code);
        align = szck_align(code);
        check_szck_range(v, kind, bits, align);
        goto done;
    }
    sv = sx32(v);
    if (c < -0x57) {
        if (c == -0x58) {
            if ((sv < -0x80 || sv > 0x7f) && (sv < 0xff80L || sv > 0xffffL))
                msg = "Offset value too large";
        } else if (c == -0x5eb) {
            if ((sv < -0x4000 || sv > 0x3fff) && v < 0xffffc000UL)
                msg = "Offset value too large";
        } else {
            lnk_fatal1("Invalid operand bit size");
        }
        goto done;
    }
    switch (c) {
    case 1:
        if (v >= (unsigned long)dword_bits)
            msg = "Immediate value too large";
        break;
    case 2:
        if (v & 1)
            msg = "Immediate value must be even";
        break;
    case 5:
        if (v > 0x1f)
            msg = "Address value too large";
        break;
    case 6:
        if (v > 0x3f)
            msg = "Address or immediate value too large";
        break;
    case 7:
        if (v > 0x7f)
            msg = "Address, immediate, or offset value too large";
        break;
    case 8:
        if (target_index == TGT_56000 && (v & 0xffff) == 0) {
            v = (v >> 16) & 0xff;
            val->lo = v;
        }
        if (v > 0xff)
            msg = "Address or immediate value too large";
        break;
    case 0xc:
        if (v > 0xfff)
            msg = "Address or immediate value too large";
        break;
    case 0xd:
        if (v > 0x1fff)
            msg = "Address or immediate value too large";
        break;
    case 0x13:
        if (v > 0x7ffffUL)
            msg = "Address or immediate value too large";
        break;
    case 0x43:
        if (v & sign_bit)
            v = M32(v | ~(sign_bit - 1));
        sv = sx32(v);
        if (sv < -0x40 || sv > 0x3f)
            msg = "Displacement value too large";
        break;
    case 0x45:
        if (v & sign_bit)
            v = M32(v | ~(sign_bit - 1));
        sv = sx32(v);
        if (sv < -0x100 || sv > 0xff)
            msg = "Offset value too large";
        break;
    case 0x4c:
        if ((v < io_base2 || v > addr_mask) && (v < io_base2_neg || v > io_short2_max))
            msg = "Invalid I/O address";
        break;
    case 0x55:
    case 0x56:
    case 0x57:
        if ((v < io_base || v > addr_mask) && (v < io_base_neg || v > io_short_max))
            msg = "Invalid I/O address";
        break;
    case 100:
        if (v == 0)
            msg = "Invalid address or immediate value";
        break;
    case 0x65:
        if (v < 0x80) {
            if (v == 0x40)
                msg = "Invalid address value";
        } else {
            msg = "Address, immediate, or offset value too large";
        }
        break;
    case 0x66:
        if ((v < io_base || v > addr_mask) && (v < io_base_neg || v > io_short_max))
            msg = "Invalid I/O address";
        else if (v == 0x40)
            msg = "Invalid address value";
        break;
    case 0x69:
        if (v < 0x20) {
            if (v == 0)
                msg = "Invalid immediate value";
        } else {
            msg = "Immediate value too large";
        }
        break;
    case 0x6a:
        if (v < 0x40) {
            if (v == 0)
                msg = "Invalid immediate value";
        } else {
            msg = "Immediate value too large";
        }
        break;
    case -0x4d:
        if ((sv < -0x40 || sv > 0x3f) && (sv < 0x7ffc0L || sv > 0x7ffffL))
            msg = "Offset value too large";
        break;
    case -0x37:
        if ((sv < -0x20 || sv > 0x1f) && (sv < 0xffe0L || sv > 0xffffL))
            msg = "Offset value too large";
        break;
    case -0x13:
        if (v > 0x7ffffUL)
            msg = "Address value too large";
        if ((v & M32(~word_mask)) != (*run_ctr & M32(~word_mask)))
            msg = "Subroutine address not on current page";
        val->lo = v;
        break;
    case -0x10:
        if (sv < -0x8000L || sv > 0x7fffL)
            msg = "Immediate value too large";
        break;
    case -0xf:
        if (sv < -0x4000 || sv > 0x3fff)
            msg = "Offset or immediate value too large";
        break;
    case -7:
        if (sv < -0x80 || sv > 0x7f)
            msg = "Offset or immediate value too large";
        break;
    case -6:
        if (sv < -0x40 || sv > 0x3f)
            msg = "Offset value too large";
        break;
    case -5:
        if (sv < -0x20 || sv > 0x1f)
            msg = "Offset value too large";
        break;
    case -2:
        if (v == 0 || sv < -0x3f)
            msg = "Invalid offset value";
        break;
    case -1:
    case 0:
        break;
    default:
        lnk_fatal1("Invalid operand bit size");
        break;
    }
done:
    if (msg != NULL) {
        lnk_error1(msg);
        free_expr(val);
        free_expr(code);
        val = NULL;
    }
    return val;
}

/* 004075f2: kind character of an @SZCK('kNNa') string */
int szck_kind(EXPR *e)
{
    int k;

    k = 0;      /* original: uninitialised */
    if (e->size == 2)
        k = (int)((e->lo >> 8) & 0xff);
    else if (e->size == 3)
        k = (int)((e->lo >> 16) & 0xff);
    else if (e->size == 4)
        k = (int)((e->mid >> 8) & 0xff);
    else
        lnk_error1("Error in size check function argument in relocation expression");
    return k;
}

/* 00407664: bit count digits of the @SZCK string */
int szck_bits(EXPR *e)
{
    char d[3];
    int c;

    d[0] = d[1] = d[2] = 0;     /* original: uninitialised on error */
    if (e->size == 2) {
        d[0] = (char)(e->lo & 0xff);
        d[1] = 0;
    } else if (e->size == 3) {
        c = (int)(e->lo & 0xff);
        if (c == 'w' || c == 'l') {
            d[1] = 0;
        } else {
            d[1] = (char)c;
            d[2] = 0;
        }
        d[0] = (char)((e->lo >> 8) & 0xff);
    } else if (e->size == 4) {
        d[0] = (char)(e->mid & 0xff);
        d[1] = (char)((e->lo >> 8) & 0xff);
        d[2] = 0;
    } else {
        lnk_error1("Error in size check function argument in relocation expression");
    }
    return atoi(d);
}

/* 00407744: alignment character of the @SZCK string */
int szck_align(EXPR *e)
{
    int c;

    if (e->size == 2)
        return ' ';
    if (e->size < 3 || e->size > 4) {
        lnk_error1("Error in size check function argument in relocation expression");
        return ' ';     /* original: garbage */
    }
    c = (int)(e->lo & 0xff);
    if (c == 'w' || c == 'l')
        return c;
    return ' ';
}

/* 004077a5: the '@' operator */
EXPR *op_space(EXPR *a, EXPR *b)
{
    if (b->type == EXPR_INT) {
        b->space = index_mem_space((int)b->lo);
        if (opt_aec && merge_mem_space(a->space, b->space) == MS_BAD) {
            lnk_error1("Expression involves incompatible memory spaces");
            free_expr(b);
            free_expr(a);
            a = NULL;
        }
    } else {
        free_expr(a);
        free_expr(b);
        lnk_error1("Invalid relative expression");
        a = NULL;
    }
    return a;
}

/* 00407848: the ':' operator (mapping and counter suffix) */
EXPR *op_mapping(EXPR *a, EXPR *b)
{
    if (b->type == EXPR_INT) {
        if (OBJ_OLD() || colon_short) {
            a->ctr = (long)(b->lo & 0xf);
            b->lo >>= 4;
            a->map = index_mem_space((int)(b->lo & 0xf));
            a->space = a->map;
        } else {
            a->ctr = (long)(b->lo & 0xffff);
            b->lo >>= 16;
            a->map = (long)(b->lo & 0xffff);
            a->space = map_to_space(a->map);
        }
    } else {
        free_expr(a);
        free_expr(b);
        lnk_error1("Invalid relative expression");
        a = NULL;
    }
    return a;
}

/* 0040793a: the '!' operator (source line) */
EXPR *op_line(EXPR *a, EXPR *b)
{
    if (a->type == EXPR_INT) {
        *a = *b;
    } else {
        free_expr(a);
        free_expr(b);
        lnk_error1("Invalid source line number");
        a = NULL;
    }
    return a;
}

/* 00407988: folds mid into lo for targets with words < 32 bits (in place) */
unsigned long expr_as_int32(EXPR *e)
{
    if (word_bytes < 4)
        e->lo = M32(e->lo | shl32(e->mid, word_bits));
    return e->lo;
}

/* 004079b8 */
void negate_value(EXPR *e)
{
    if (e->type == EXPR_FLT) {
        e->fval = -e->fval;
    } else {
        complement_value(e);
        if (e->lo == word_mask) {
            if (e->mid == word_mask)
                e->hi = M32(e->hi + 1) & word_mask;
            e->mid = M32(e->mid + 1) & word_mask;
        }
        e->lo = M32(e->lo + 1) & word_mask;
    }
}

/* 00407a61 */
void complement_value(EXPR *e)
{
    e->hi = ~e->hi & word_mask;
    e->mid = ~e->mid & word_mask;
    e->lo = ~e->lo & word_mask;
}

/* 00407aa0 */
void op_not(EXPR *e)
{
    unsigned long v;

    v = value_truth(e) == 0 ? 1UL : 0UL;
    e->lo = v;
    e->hi = 0;
    e->mid = 0;
    e->type = EXPR_INT;
    e->map = MS_N;
    e->space = MS_N;
    e->ctr = 0;
    e->attr = 0;
}

/* 00407b01: 0 zero, -1 negative, 1 positive */
long value_truth(EXPR *e)
{
    long r;

    if (e->type == EXPR_FLT) {
        r = e->fval != 0.0;
        if (r != 0 && e->fval < 0.0)
            r = -1;
    } else {
        r = (e->hi == 0 && e->mid == 0 && e->lo == 0) ? 0 : 1;
        if (r != 0 && (e->hi & sign_bit))
            r = -1;
    }
    return r;
}

/* 00407baf */
void op_compare(int op, EXPR *a, EXPR *b)
{
    long r;
    unsigned long v;

    if (a->type == EXPR_INT && b->type == EXPR_INT) {
        if (a->hi < b->hi)
            r = -1;
        else if (b->hi < a->hi)
            r = 1;
        else if (a->mid < b->mid)
            r = -1;
        else if (b->mid < a->mid)
            r = 1;
        else if (a->lo < b->lo)
            r = -1;
        else if (b->lo < a->lo)
            r = 1;
        else
            r = 0;
        if (r != 0 &&
            (((a->hi & sign_bit) != 0 && (b->hi & sign_bit) == 0) ||
             ((a->hi & sign_bit) == 0 && (b->hi & sign_bit) != 0)))
            r = -r;
    } else {
        double da, db;
        da = value_to_double(a);
        db = value_to_double(b);
        if (db <= da) {
            if (da <= db)
                r = 0;
            else
                r = 1;
        } else {
            r = -1;
        }
    }
    v = 0;
    switch (op) {
    case OP_LT:
        v = r == -1;
        break;
    case OP_GT:
        v = r == 1;
        break;
    case OP_EQ:
        v = r == 0;
        break;
    case OP_LE:
        v = r != 1;
        break;
    case OP_GE:
        v = r != -1;
        break;
    case OP_NE:
        v = r != 0;
        break;
    default:
        lnk_fatal1("Compare select failure");
        v = M32(r);
        break;
    }
    set_plain_int(a, v);
}

/* 00407df5: unsigned 3-word division in base-256 limbs */
void bigint_divmod(unsigned long ah, unsigned long am, unsigned long al,
                   unsigned long bh, unsigned long bm, unsigned long bl,
                   unsigned long *qh, unsigned long *qm, unsigned long *ql,
                   unsigned long *rh, unsigned long *rm, unsigned long *rl)
{
    unsigned long lb[BIGINT_LIMBS];
    unsigned long rem[BIGINT_LIMBS];
    unsigned long q[BIGINT_LIMBS];
    unsigned long la[BIGINT_LIMBS];
    unsigned long work[BIGINT_LIMBS];
    int n, i;

    if (bigint_cmp3(bh, bm, bl, ah, am, al) < 1) {
        for (i = 0; i < BIGINT_LIMBS; i++)
            lb[i] = rem[i] = q[i] = la[i] = work[i] = 0;
        bigint_from_words(0, 0, 0, q);
        bigint_from_words(0, 0, 0, rem);
        bigint_from_words(0, 0, 0, work);
        bigint_from_words(ah, am, al, la);
        bigint_from_words(bh, bm, bl, lb);
        n = bigint_limb_count(lb);
        for (i = bigint_limb_count(la) - 2; i >= 0; i--) {
            bigint_copy(rem, rem + 1, n - 1);
            rem[0] = la[i];
            q[i] = bigint_div_digit(lb, rem, n, work);
        }
        bigint_to_words(q, qh, qm, ql);
        bigint_to_words(rem, rh, rm, rl);
    } else {
        *rh = ah;
        *rm = am;
        *rl = al;
        *ql = 0;
        *qm = 0;
        *qh = 0;
    }
}

/* 00407f95 */
int bigint_cmp3(unsigned long ah, unsigned long am, unsigned long al,
                unsigned long bh, unsigned long bm, unsigned long bl)
{
    if (ah != bh)
        return bh < ah ? 1 : -1;
    if (am != bm)
        return bm < am ? 1 : -1;
    if (al != bl)
        return bl < al ? 1 : -1;
    return 0;
}

/* 00407ff8 */
void bigint_from_words(unsigned long hi, unsigned long mid, unsigned long lo,
                       unsigned long *out)
{
    int i, n;

    n = (int)word_bytes;
    out[0] = lo & 0xff;
    out[n] = mid & 0xff;
    out[n * 2] = hi & 0xff;
    for (i = 1; i < n; i++) {
        lo >>= 8;
        out[i] = lo & 0xff;
        mid >>= 8;
        out[i + n] = mid & 0xff;
        hi >>= 8;
        out[i + n * 2] = hi & 0xff;
    }
    out[12] = 0;
}

/* 004080bf */
void bigint_to_words(unsigned long *in, unsigned long *hi, unsigned long *mid,
                     unsigned long *lo)
{
    int i, n;

    n = (int)word_bytes;
    *lo = 0;
    *mid = 0;
    *hi = 0;
    i = n;
    while (--i > 0) {
        *hi = M32((*hi | in[i + n * 2]) << 8);
        *mid = M32((*mid | in[i + n]) << 8);
        *lo = M32((*lo | in[i]) << 8);
    }
    *hi = M32(*hi | in[n * 2]);
    *mid = M32(*mid | in[n]);
    *lo = M32(*lo | in[0]);
}

/* 004081ab: copies n limbs top-down (dst = src + 1 overlap intended) */
void bigint_copy(unsigned long *src, unsigned long *dst, int n)
{
    while (--n >= 0)
        dst[n] = src[n];
}

/* 004081d5: one quotient digit; rem -= digit * divisor */
unsigned long bigint_div_digit(unsigned long *divisor, unsigned long *rem,
                               int n, unsigned long *work)
{
    int c;
    unsigned long q, t;
    int ge;

    c = n - 1;
    do {
        if (divisor[c] != 0) {
            q = rem[c] / divisor[c];
            do {
                bigint_mul_small(q, divisor, work, n);
                q = M32(q - 1);
                ge = bigint_cmp_ge(work, rem, n);
                t = q;
            } while (!ge);
            do {
                q = t;
                bigint_mul_small(M32(q + 1), divisor, work, n);
                ge = bigint_cmp_ge(work, rem, n);
                t = M32(q + 1);
            } while (ge);
            bigint_mul_small(q, divisor, work, n);
            bigint_sub(work, rem, n);
            return q;
        }
        c--;
    } while (c >= 0);
    return 0;
}

/* 004082d5 */
void bigint_mul_small(unsigned long digit, unsigned long *src,
                      unsigned long *dst, int n)
{
    unsigned long acc;
    int i;

    acc = 0;
    for (i = 0; i < n; i++) {
        acc = M32(acc + digit * src[i]);
        dst[i] = acc & 0xff;
        acc >>= 8;
    }
}

/* 00408331: returns b >= a */
int bigint_cmp_ge(unsigned long *a, unsigned long *b, int n)
{
    unsigned long borrow;
    int i;

    borrow = 0;
    for (i = 0; i < n; i++)
        borrow = sx32(M32(b[i] - a[i] - borrow)) < 0 ? 1UL : 0UL;
    return borrow == 0;
}

/* 0040838d: acc -= sub */
void bigint_sub(unsigned long *sub, unsigned long *acc, int n)
{
    unsigned long t;
    int i;

    t = 0;
    for (i = 0; i < n; i++) {
        t = M32(acc[i] - sub[i] - t);
        acc[i] = t & 0xff;
        t = sx32(t) < 0 ? 1UL : 0UL;
    }
}

/* 004083f1 */
int bigint_limb_count(unsigned long *a)
{
    int i;

    for (i = (int)fmt_dword + 1; i >= 0 && a[i] == 0; i--)
        ;
    return i + 2;
}

/* 00408429 */
double value_to_double(EXPR *e)
{
    if (e->type == EXPR_FLT)
        return e->fval;
    if (e->size == fmt_word)
        return int_to_double(e->lo);
    if (e->size == fmt_dword)
        return long_to_double(e->mid, e->lo);
    return 0.0;
}

/* 0040848c: one-word two's complement value */
double int_to_double(unsigned long v)
{
    int neg;
    double d;

    neg = (v & sign_bit) != 0;
    if (neg)
        v = M32((~v & word_mask) + 1);
    d = (double)M32(v);
    if (neg)
        d = -d;
    return d;
}

/* 004084f1: two-word two's complement value */
double long_to_double(unsigned long hi, unsigned long lo)
{
    int neg;
    unsigned long t, carry;
    double d;

    neg = 0;
    carry = 0;
    if (hi == 0 && lo == 0)
        return 0.0;
    if (hi & sign_bit) {
        neg = 1;
        t = M32((~lo & word_mask) + 1);
        if (word_bytes < 4)
            carry = (shr32(t, word_bits) & 1) != 0;
        lo = t & word_mask;
        hi = M32((~hi & word_mask) + carry) & word_mask;
    }
    d = (double)M32(hi) * (double)sign_bit * 2.0 + (double)M32(lo);
    if (neg)
        d = -d;
    return d;
}

/* 00408616: floating value -> fractional integer EXPR of width fmt */
void float_to_fixed_frac(double v, long fmt, EXPR *out)
{
    unsigned long m, s, hw, lw;

    m = opt_sbm ? 0xffffUL : word_mask;
    s = opt_sbm ? 0x8000UL : sign_bit;
    out->lo = 0;
    out->mid = 0;
    out->hi = 0;
    if (fmt == fmt_word) {
        out->lo = double_to_frac(v);
        if (out->lo & s) {
            out->hi = m;
            out->mid = m;
        }
    } else {
        double_to_frac2(v, &hw, &lw);
        out->mid = hw;
        out->lo = lw;
        if (out->hi & s)
            out->hi = m;
    }
    if (out->mid == 0 || out->mid == m)
        out->size = fmt_word;
    else
        out->size = fmt_dword;
    out->type = EXPR_INT;
}

/* rounding conversion shared by double_to_frac and double_to_frac_n */
static unsigned long frac_round(double v, unsigned long scale, unsigned long mask)
{
    double t;
    unsigned long r, lim;

    if (v >= 0.0)
        t = v * (double)scale + 0.5;
    else
        t = v * (double)scale + -0.5;
    r = ftol32(t);
    if (t - (double)sx32(r) == 0.0)
        r &= 0xfffffffeUL;
    lim = M32(~scale) & mask;
    if (sx32(lim) < sx32(r))
        r = lim;
    return r & mask;
}

/* 00408739 */
unsigned long double_to_frac(double v)
{
    unsigned long s, m;

    if (opt_sbm) {
        m = 0xffff;
        s = 0x8000;
    } else {
        s = sign_bit;
        m = word_mask;
    }
    if (v < -1.0) {
        lnk_warning1("Expression value outside fractional domain");
        return opt_sbm ? 0xffff8000UL : frac_min;
    }
    if (!(v < 1.0)) {
        lnk_warning1("Expression value outside fractional domain");
        return opt_sbm ? 0x7fffUL : frac_max;
    }
    return frac_round(v, s, m);
}

/* 004088a3 */
unsigned long double_to_frac_n(double v, unsigned long mask)
{
    unsigned long s;

    if (mask == 0xff)
        s = 0x80;
    else if (mask == 0xfff)
        s = 0x800;
    else if (mask == 0xffff)
        s = 0x8000;
    else if (mask == 0xfffffUL)
        s = 0x80000UL;
    else
        s = sign_bit;
    if (v < -1.0) {
        lnk_warning1("Expression value outside fractional domain");
        return frac_min;
    }
    if (!(v < 1.0)) {
        lnk_warning1("Expression value outside fractional domain");
        return frac_max;
    }
    return frac_round(v, s, mask);
}

/* 004089f9: two-word fraction, truncating */
void double_to_frac2(double v, unsigned long *hi, unsigned long *lo)
{
    unsigned long m, s, h, l, borrow;
    int neg;
    double t, frac;

    m = opt_sbm ? 0xffffUL : word_mask;
    s = opt_sbm ? 0x8000UL : sign_bit;
    if (v < -1.0) {
        lnk_warning1("Expression value outside fractional domain");
        *hi = s;
        *lo = 0;
        return;
    }
    if (!(v < 1.0)) {
        lnk_warning1("Expression value outside fractional domain");
        *hi = m >> 1;
        *lo = m;
        return;
    }
    neg = v < 0.0;
    if (neg)
        v = -v;
    t = v * (double)s;
    h = ftol32(t);
    frac = t - (double)sx32(h);
    l = ftol32((double)M32(s << 1) * frac) & m;
    if (neg) {
        borrow = l == 0;
        l = borrow ? 0 : (~l & m);
        h = M32(~h + borrow);
    }
    *hi = h & m;
    *lo = l;
}

/* ---- portable IEEE encoding (replaces the raw bit moves) ------------- */

/* 00408b90: IEEE single precision bits of (float)v */
unsigned long float_bits(double v)
{
    unsigned long sign, frac;
    double a, m;
    int ex;
    long e;

    if (v != v)
        return 0xffc00000UL;
    sign = 0;
    a = v;
    if (a < 0.0) {
        sign = 0x80000000UL;
        a = -a;
    }
    if (a == 0.0)
        return sign;
    /* round to single precision (nearest even) */
    if (a >= ldexp(1.0, 128) - ldexp(1.0, 103))
        return sign | 0x7f800000UL;
    m = frexp(a, &ex);                  /* a = m * 2^ex, 0.5 <= m < 1 */
    e = (long)ex + 126;                 /* biased exponent */
    if (e >= 1) {
        double f, fl;
        f = ldexp(m, 24);               /* [2^23, 2^24) */
        fl = floor(f);
        if (f - fl > 0.5 || (f - fl == 0.5 && fmod(fl, 2.0) != 0.0))
            fl += 1.0;
        if (fl >= 16777216.0) {
            fl = 8388608.0;
            e++;
            if (e >= 255)
                return sign | 0x7f800000UL;
        }
        frac = (unsigned long)(fl - 8388608.0);
        return sign | ((unsigned long)e << 23) | frac;
    } else {
        double f, fl;
        f = ldexp(m, ex + 149);         /* denormal: units of 2^-149 */
        fl = floor(f);
        if (f - fl > 0.5 || (f - fl == 0.5 && fmod(fl, 2.0) != 0.0))
            fl += 1.0;
        return sign | (unsigned long)fl;    /* 0x800000 rounds to the smallest normal */
    }
}

/* 00408ba1: IEEE double from its high and low 32-bit words */
double words_to_double(unsigned long hi, unsigned long lo)
{
    long e;
    double f, d;

    hi = M32(hi);
    lo = M32(lo);
    e = (long)((hi >> 20) & 0x7ff);
    f = (double)(hi & 0xfffffUL) * 4294967296.0 + (double)lo;
    if (e == 0x7ff) {
        if (f == 0.0)
            d = HUGE_VAL;
        else {
            d = HUGE_VAL;
            d = d - d;      /* NaN */
        }
    } else if (e == 0) {
        d = ldexp(f, -1074);
    } else {
        d = ldexp(f + 4503599627370496.0, (int)(e - 1075));
    }
    if (hi & 0x80000000UL)
        d = -d;
    return d;
}

/* 00408bba: *hi = high 32-bit word, *lo = low word of the IEEE double d */
void double_to_words(double d, unsigned long *hi, unsigned long *lo)
{
    unsigned long sign;
    double a, m, f;
    int ex;
    long e;

    if (d != d) {
        *hi = 0xfff80000UL;     /* x87 default NaN */
        *lo = 0;
        return;
    }
    sign = 0;
    a = d;
    if (a < 0.0) {
        sign = 0x80000000UL;
        a = -a;
    }
    if (a == 0.0) {
        *hi = sign;
        *lo = 0;
        return;
    }
    if (a > DBL_MAX) {
        *hi = sign | 0x7ff00000UL;
        *lo = 0;
        return;
    }
    m = frexp(a, &ex);
    e = (long)ex + 1022;
    if (e >= 1) {
        f = ldexp(m, 53) - 4503599627370496.0;
    } else {
        f = ldexp(m, ex + 1074);
        e = 0;
    }
    *hi = sign | ((unsigned long)e << 20) | (unsigned long)floor(f / 4294967296.0);
    *lo = (unsigned long)fmod(f, 4294967296.0);
}
