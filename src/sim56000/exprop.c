/* exprop.c - expression evaluator: operators, precedence climbing, entry points
 * (SIM56000.EXE 6.3.0, module expr 0x459250-0x45c180, without parse_primary).
 * Expression values are struct val nodes; the "32" variants are used for IEEE-float
 * devices (mode word bit 0x80), where a node is one or more full 32-bit words.
 * Errors set asm_result[0] = -1 and the message pointers and make the functions
 * return 0 / NULL. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sim56000.h"

char *optr = NULL;                     /* 0x5029e0 */
long asm_result[3] = { 0, 0, 0 };      /* 0x5059e0 */
char *expr_err_msg = NULL;             /* 0x5059f0 */

#define ISFLOAT(n)   (((n)->flags & 0x200UL) != 0)
#define ERR_FLOAT_OP "Illegal operator for floating point element"

static long sx32(unsigned long v)
{
    v &= MASK32;
    if (v & 0x80000000UL)
        return -(long)((~v & MASK32) + 1UL);
    return (long)v;
}

static unsigned long ux32(long v)
{
    return (unsigned long)v & MASK32;
}

/* sign bit of the accumulator extension byte (0x80, or 0x08 with 4 extension bits) */
static unsigned long ext_sign(void)
{
    return (expr_mode & 0x1000000UL) != 0 ? 0x08UL : 0x80UL;
}

static int is_nan(double d)
{
    return d != d;
}

/* the x87 compare of the original treats an unordered result (NaN) as "equal" */
static int is_zero(double d)
{
    return d == 0.0 || is_nan(d);
}

/* ------------------------------------------------------------------ errors and small helpers */
void expr_error(char *msg)
{
    asm_result[0] = -1L;
    parm_errmsg = msg;
    expr_err_msg = msg;
}

void expr_error2(char *prefix, char *msg)
{
    sprintf((char *)status1_buf, "%s: %s", prefix, msg);
    parm_errmsg = (char *)status1_buf;
    expr_err_msg = (char *)status1_buf;
    asm_result[0] = -1L;
}

long stricmp_ci2(char *a, char *b)
{
    return stricmp_ci(a, b);
}

void node_free(void *node)
{
    if (node != NULL)
        dsp_free(node);
}

void parse_float(void *vnode)
{
    struct val *n = (struct val *)vnode;
    char *end;

    n->d = 0.0;
    n->d = strtod(optr, &end);
    optr = end;
}

/* 1-based position of c in set, 0 if absent */
long str_index1(long c, char *set)
{
    char *p;

    for (p = set; *p != '\0'; p++) {
        if (*p == (char)c)
            return (long)(p - set) + 1;
    }
    return 0;
}

/* ------------------------------------------------------------------ integer <-> double views of a node */
void node_to_double(unsigned long mode, void *vnode)
{
    struct val *n = (struct val *)vnode;

    expr_mode = mode;
    if ((n->flags & 4) != 0)
        long_to_frac(n);
    else if ((n->flags & 2) != 0)
        dword_to_frac(mode, n);
    else
        word_to_frac(mode, n);
}

double node_get_double(unsigned long mode, void *vnode)
{
    struct val *n = (struct val *)vnode;

    expr_mode = mode;
    if (!ISFLOAT(n))
        node_to_double(mode, n);
    return n->d;
}

void node_from_double(unsigned long mode, void *vnode)
{
    struct val *n = (struct val *)vnode;
    unsigned long hi, lo, sign;

    expr_mode = mode;
    if ((n->flags & 4) != 0) {
        frac_to_long(n);
        return;
    }
    if ((n->flags & 2) == 0) {
        frac_to_word(mode, n);
        return;
    }
    if ((mode & 0x80) != 0) {
        dbl_unpack(n->d, &hi, &lo);
        n->lo = lo;
        n->hi = hi;
        return;
    }
    frac_to_dword(mode, n);
    sign = (expr_mode & 0x10000000UL) != 0 ? 0x8000UL : 0x800000UL;
    if ((n->hi & sign) != 0)
        n->ext = (expr_mode & 0x1000000UL) != 0 ? 0x0fUL : 0xffUL;
}

/* ------------------------------------------------------------------ 96-bit operators (mode without 0x80) */
long op_add(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    double da, db;

    if (!ISFLOAT(a) && !ISFLOAT(b)) {
        a->lo = (a->lo + b->lo) & MASK32;
        a->ext = (a->ext + b->ext) & MASK32;
        a->hi = (a->hi + b->hi) & MASK32;
        node_normalize(a);
        return 1;
    }
    da = node_get_double(expr_mode, a);
    db = node_get_double(expr_mode, b);
    a->flags |= 0x200UL;
    a->d = db + da;
    return 1;
}

long op_sub(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    double da, db;

    if (!ISFLOAT(a) && !ISFLOAT(b)) {
        node_neg(b);
        op_add(a, b);
        node_neg(b);
        return 1;
    }
    da = node_get_double(expr_mode, a);
    db = node_get_double(expr_mode, b);
    a->d = da - db;
    a->flags |= 0x200UL;
    return 1;
}

static void get3(struct val *n, unsigned long *w)
{
    w[0] = n->lo;
    w[1] = n->hi;
    w[2] = n->ext;
}

static void set3(struct val *n, unsigned long *w)
{
    n->lo = w[0];
    n->hi = w[1];
    n->ext = w[2];
}

long op_mul(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    unsigned long la[8], lb[8], lr[8], w[3], acc, sgn;
    int neg = 0, k, j;
    double da, db;

    if (!ISFLOAT(a) && !ISFLOAT(b)) {
        sgn = ext_sign();
        if ((sgn & a->ext) != 0) {
            neg = 1;
            node_neg(a);
        }
        if ((b->ext & sgn) != 0) {
            node_neg(b);
            neg |= 2;
        }
        get3(a, w);
        mp_unpack(w, la);
        get3(b, w);
        mp_unpack(w, lb);
        acc = 0;
        for (k = 0; k < 7; k++) {
            for (j = 0; j <= k; j++)
                acc = (acc + la[j] * lb[k - j]) & MASK32;
            lr[k] = acc & 0xff;
            acc >>= 8;
        }
        lr[7] = 0;
        mp_pack(lr, w);
        set3(a, w);
        if (neg == 1)
            node_neg(a);
        else if (neg == 2) {
            node_neg(a);
            node_neg(b);
        } else if (neg == 3)
            node_neg(b);
        a->flags |= b->flags;
        return 1;
    }
    db = node_get_double(expr_mode, b);
    da = node_get_double(expr_mode, a);
    a->flags |= 0x200UL;
    a->d = da * db;
    return 1;
}

long op_div(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    unsigned long q[3], r[3], na[3], nb[3], sgn;
    int neg = 0;
    double da, db;

    if (ISFLOAT(a) || ISFLOAT(b)) {
        db = node_get_double(expr_mode, b);
        if (is_zero(db)) {
            expr_error("Divide by 0");
            return 0;
        }
        da = node_get_double(expr_mode, a);
        a->flags |= 0x200UL;
        a->d = da / db;
        return 1;
    }
    if (b->ext == 0 && b->hi == 0 && b->lo == 0) {
        expr_error("Divide by 0");
        return 0;
    }
    sgn = ext_sign();
    if ((a->ext & sgn) != 0) {
        neg = 1;
        node_neg(a);
    }
    if ((b->ext & sgn) != 0) {
        node_neg(b);
        neg |= 2;
    }
    get3(a, na);
    get3(b, nb);
    mp_divmod(na, nb, q, r);
    set3(a, q);
    if (neg == 1)
        node_neg(a);
    else if (neg == 2) {
        node_neg(a);
        node_neg(b);
    } else if (neg == 3)
        node_neg(b);
    return 1;
}

long op_mod(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    unsigned long q[3], r[3], na[3], nb[3];
    double da, db;

    if (ISFLOAT(a) || ISFLOAT(b)) {
        db = node_get_double(expr_mode, b);
        if (is_zero(db)) {
            expr_error("Divide by 0");
            return 0;
        }
        da = node_get_double(expr_mode, a);
        a->d = fmod(da, db);
        a->flags |= 0x200UL;
        return 1;
    }
    if (b->ext == 0 && b->hi == 0 && b->lo == 0) {
        expr_error("Divide by 0");
        return 0;
    }
    get3(a, na);
    get3(b, nb);
    mp_divmod(na, nb, q, r);
    set3(a, r);
    return 1;
}

long op_or(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;

    if (!ISFLOAT(a) && !ISFLOAT(b)) {
        a->ext |= b->ext;
        a->hi |= b->hi;
        a->lo |= b->lo;
        a->flags |= b->flags;
        return 1;
    }
    expr_error(ERR_FLOAT_OP);
    return 0;
}

long op_and(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;

    if (!ISFLOAT(a) && !ISFLOAT(b)) {
        a->ext &= b->ext;
        a->hi &= b->hi;
        a->lo &= b->lo;
        a->flags |= b->flags;
        return 1;
    }
    expr_error(ERR_FLOAT_OP);
    return 0;
}

long op_xor(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;

    if (!ISFLOAT(a) && !ISFLOAT(b)) {
        a->ext ^= b->ext;
        a->hi ^= b->hi;
        a->lo ^= b->lo;
        a->flags |= b->flags;
        return 1;
    }
    expr_error(ERR_FLOAT_OP);
    return 0;
}

/* largest shift count: 48 bits for 16-bit words, 56 otherwise */
static long max_shift(void)
{
    return (expr_mode & 0x10000000UL) != 0 ? 0x30 : 0x38;
}

long op_shl(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    long n;

    if (ISFLOAT(a) || ISFLOAT(b)) {
        expr_error(ERR_FLOAT_OP);
        return 0;
    }
    n = sx32(node_word(b));
    if (n >= 0 && n <= max_shift()) {
        for (; n > 0; n--) {
            a->lo = (a->lo << 1) & MASK32;
            a->ext = (a->ext << 1) & MASK32;
            a->hi = (a->hi << 1) & MASK32;
            node_normalize(a);
        }
        return 1;
    }
    expr_error("Invalid shift amount");
    return 0;
}

long op_shr(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    unsigned long top = (expr_mode & 0x10000000UL) != 0 ? 0x8000UL : 0x800000UL;
    unsigned long sgn, e;
    long n;

    if (ISFLOAT(a) || ISFLOAT(b)) {
        expr_error(ERR_FLOAT_OP);
        return 0;
    }
    n = sx32(node_word(b));
    if (n >= 0 && n <= max_shift()) {
        sgn = ext_sign();
        for (; n > 0; n--) {
            a->lo >>= 1;
            if ((a->hi & 1) != 0)
                a->lo = top | a->lo;
            e = a->ext;
            a->hi >>= 1;
            if ((e & 1) != 0)
                a->hi = top | a->hi;
            a->ext = e >> 1;
            if ((e & sgn) != 0)
                a->ext = sgn | (e >> 1);
        }
        return 1;
    }
    expr_error("Invalid shift amount");
    return 0;
}

static void set_bool(struct val *a, int v)
{
    a->lo = v != 0;
    a->hi = 0;
    a->ext = 0;
    a->flags = 0x2101UL;
}

long op_land(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;

    set_bool(a, node_sign(a) != 0 && node_sign(b) != 0);
    return 1;
}

long op_lor(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;

    set_bool(a, node_sign(a) != 0 || node_sign(b) != 0);
    return 1;
}

/* ------------------------------------------------------------------ unary operators */
void node_neg(void *vnode)
{
    struct val *n = (struct val *)vnode;

    if (ISFLOAT(n)) {
        n->d = -n->d;
        return;
    }
    node_not(n);
    n->lo = (n->lo + 1) & MASK32;
    node_normalize(n);
}

long node_not(void *vnode)
{
    struct val *n = (struct val *)vnode;
    unsigned long m24;

    if (ISFLOAT(n)) {
        expr_error("Cannot apply '~' operator to floating point value");
        return 0;
    }
    m24 = (expr_mode & 0x10000000UL) != 0 ? 0xffffUL : 0xffffffUL;
    n->ext = ((expr_mode & 0x1000000UL) != 0 ? 0x0fUL : 0xffUL) & ~n->ext;
    n->hi = m24 & ~n->hi;
    n->lo = m24 & ~n->lo;
    return 1;
}

void node_lnot(void *vnode)
{
    struct val *n = (struct val *)vnode;
    long s = node_sign(n);

    set_bool(n, s == 0);
}

long node_sign(void *vnode)
{
    struct val *n = (struct val *)vnode;

    if (!ISFLOAT(n)) {
        long r = (n->ext != 0 || n->hi != 0 || n->lo != 0);

        if (r != 0 && (n->ext & ext_sign()) != 0)
            r = -1;
        return r;
    }
    if (n->d != 0.0 && n->d < 0.0)
        return -1;
    return n->d != 0.0;
}

/* ------------------------------------------------------------------ 32-bit-word (IEEE float device) operators */
/* both operands plain single words: integer arithmetic is possible */
static int both_int32(struct val *a, struct val *b)
{
    return !ISFLOAT(a) && ((a->flags | b->flags) & 6UL) == 0 && !ISFLOAT(b);
}

long op_add32(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    double da, db;

    if (both_int32(a, b)) {
        a->lo = (a->lo + b->lo) & MASK32;
        return 1;
    }
    db = node_get_double(expr_mode, b);
    da = node_get_double(expr_mode, a);
    a->flags |= 0x200UL;
    a->d = da + db;
    return 1;
}

long op_sub32(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    double da, db;

    if (both_int32(a, b)) {
        node_neg32(b);
        op_add32(a, b);
        node_neg32(b);
        return 1;
    }
    da = node_get_double(expr_mode, a);
    db = node_get_double(expr_mode, b);
    a->d = da - db;
    a->flags |= 0x200UL;
    return 1;
}

long op_mul32(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    double da, db;

    if (both_int32(a, b)) {
        a->lo = (b->lo * a->lo) & MASK32;
        return 1;
    }
    da = node_get_double(expr_mode, a);
    db = node_get_double(expr_mode, b);
    a->flags |= 0x200UL;
    a->d = db * da;
    return 1;
}

long op_div32(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    double da, db;

    if (both_int32(a, b)) {
        if (b->lo == 0) {
            expr_error("Divide by 0");
            return 0;
        }
        a->lo = ux32(sx32(a->lo) / sx32(b->lo));
        return 1;
    }
    db = node_get_double(expr_mode, b);
    if (is_zero(db)) {
        expr_error("Divide by 0");
        return 0;
    }
    da = node_get_double(expr_mode, a);
    a->flags |= 0x200UL;
    a->d = da / db;
    return 1;
}

long op_mod32(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    double da, db;

    if (both_int32(a, b)) {
        if (b->lo == 0) {
            expr_error("Divide by 0");
            return 0;
        }
        a->lo = ux32(sx32(a->lo) % sx32(b->lo));
        return 1;
    }
    db = node_get_double(expr_mode, b);
    if (is_zero(db)) {
        expr_error("Divide by 0");
        return 0;
    }
    da = node_get_double(expr_mode, a);
    a->d = fmod(da, db);
    a->flags |= 0x200UL;
    return 1;
}

long op_or32(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;

    a->ext |= b->ext;
    a->hi |= b->hi;
    a->lo |= b->lo;
    a->flags = ((b->flags | a->flags) & ~0x200UL) | 0x100UL;
    return 1;
}

long op_and32(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;

    a->ext &= b->ext;
    a->hi &= b->hi;
    a->lo &= b->lo;
    a->flags = ((b->flags | a->flags) & ~0x200UL) | 0x100UL;
    return 1;
}

long op_xor32(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;

    a->ext ^= b->ext;
    a->hi ^= b->hi;
    a->lo ^= b->lo;
    a->flags = ((b->flags | a->flags) & ~0x200UL) | 0x100UL;
    return 1;
}

long op_shl32(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    long n = sx32(b->lo);

    if (n >= 0 && n < 0x61) {
        for (; n > 0; n--) {
            a->ext = (a->ext * 2) & MASK32;
            if ((a->hi & 0x80000000UL) != 0)
                a->ext = (a->ext + 1) & MASK32;
            a->hi = (a->hi * 2) & MASK32;
            if ((a->lo & 0x80000000UL) != 0)
                a->hi = (a->hi + 1) & MASK32;
            a->lo = (a->lo * 2) & MASK32;
        }
        a->flags = (a->flags & ~0x200UL) | 0x100UL;
        return 1;
    }
    expr_error("Invalid shift amount");
    return 0;
}

long op_shr32(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    long n = sx32(b->lo);
    unsigned long fill = shr_fill_bit[0] & MASK32;

    if (n >= 0 && n < 0x61) {
        for (; n > 0; n--) {
            a->lo >>= 1;
            if ((a->hi & 1) != 0)
                a->lo = fill | a->lo;
            a->hi >>= 1;
            if ((a->ext & 1) != 0)
                a->hi = fill | a->hi;
            a->ext >>= 1;
            if ((a->ext & 0x40000000UL) != 0)
                a->ext = fill | a->ext;
        }
        a->flags = (a->flags & ~0x200UL) | 0x100UL;
        return 1;
    }
    expr_error("Invalid shift amount");
    return 0;
}

long op_land32(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;

    set_bool(a, node_sign32(a) != 0 && node_sign32(b) != 0);
    return 1;
}

long op_lor32(void *va, void *vb)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;

    set_bool(a, node_sign32(a) != 0 || node_sign32(b) != 0);
    return 1;
}

/* make sure a double/long node also has its double view, for the 32-bit-word operators */
static void ensure_double32(struct val *n)
{
    if ((n->flags & 6UL) != 0 && !ISFLOAT(n)) {
        node_get_double(expr_mode, n);
        n->flags |= 0x200UL;
    }
}

void node_neg32(void *vnode)
{
    struct val *n = (struct val *)vnode;
    unsigned long hi;

    ensure_double32(n);
    if (ISFLOAT(n)) {
        n->d = -n->d;
        return;
    }
    hi = n->hi;
    n->hi = ~hi & MASK32;
    if (n->lo == 0) {
        n->hi = (~hi + 1) & MASK32;
        return;
    }
    n->lo = (0UL - n->lo) & MASK32;
}

long node_not32(void *vnode)
{
    struct val *n = (struct val *)vnode;

    n->hi = ~n->hi & MASK32;
    n->ext = ~n->ext & MASK32;
    n->lo = ~n->lo & MASK32;
    n->flags = (n->flags & ~0x200UL) | 0x100UL;
    return 1;
}

void node_lnot32(void *vnode)
{
    struct val *n = (struct val *)vnode;
    long s = node_sign32(n);

    set_bool(n, s == 0);
}

long node_sign32(void *vnode)
{
    struct val *n = (struct val *)vnode;
    unsigned long hi, lo;
    long r;

    ensure_double32(n);
    if (!ISFLOAT(n)) {
        r = (n->ext != 0 || n->hi != 0 || n->lo != 0);
        if (r != 0 && (n->ext & 0x80000000UL) != 0)
            r = -1;
        return r;
    }
    dbl_unpack(n->d, &hi, &lo);
    r = !(lo == 0 && (hi & 0x7fffffffUL) == 0);
    if (r != 0 && (hi & 0x80000000UL) != 0)
        return -1;
    return r;
}

/* ------------------------------------------------------------------ comparison */
static void compare_result(struct val *a, long op, long c, int is32)
{
    switch (op) {
    case 0xb: a->lo = c == -1; break;
    case 0xc: a->lo = c == 1; break;
    case 0xd:
    case 0x13: a->lo = c == 0; break;
    case 0xe: a->lo = is32 ? (c == 0 || c == -1) : (c != 1); break;
    case 0xf: a->lo = is32 ? (c == 0 || c == 1) : (c != -1); break;
    case 0x10: a->lo = is32 ? (c != 0) : (c != 0); break;
    default: break;
    }
    a->flags = 0x2101UL;
    a->hi = 0;
    a->ext = 0;
}

long op_compare(void *va, void *vb, long op)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    int aint = !ISFLOAT(a), bint = !ISFLOAT(b);
    unsigned long sgn = ext_sign();
    int aneg, bneg;
    long c;
    double da, db;

    aneg = aint ? (a->ext & sgn) != 0 : a->d < 0.0;
    bneg = bint ? (b->ext & sgn) != 0 : b->d < 0.0;
    c = aneg ? -1 : 1;
    if (aneg == bneg) {
        if (!aint || !bint) {
            db = node_get_double(expr_mode, b);
            da = node_get_double(expr_mode, a);
            if (!(da > db))                    /* (x87: NaN counts as "less or equal") */
                c = da >= db ? 0 : -1;               /* (x87: unordered counts as "less") */
            else
                c = 1;
        } else {
            unsigned long t;

            if ((expr_mode & 0x10000000UL) != 0 && (expr_mode & 0x4000000UL) != 0) {
                if ((b->flags & 0x4000UL) != 0) {
                    t = a->hi;
                    a->hi = 0;
                    a->lo = (a->lo & 0xffffUL) | ((t & 0xff) << 16);
                }
                if ((a->flags & 0x4000UL) != 0) {
                    t = b->hi;
                    b->hi = 0;
                    b->lo = (b->lo & 0xffffUL) | ((t & 0xff) << 16);
                }
            }
            if (a->ext == b->ext) {
                if (a->hi == b->hi) {
                    if (a->lo == b->lo)
                        c = 0;
                    else if (a->lo < b->lo)
                        c = -c;
                } else if (a->hi < b->hi)
                    c = -c;
            } else if (a->ext < b->ext)
                c = -c;
        }
    }
    compare_result(a, op, c, 0);
    return 1;
}

long op_compare32(void *va, void *vb, long op)
{
    struct val *a = (struct val *)va, *b = (struct val *)vb;
    int af = (a->flags & 0x206UL) != 0, bf = (b->flags & 0x206UL) != 0;
    double da = 0.0, db = 0.0;
    unsigned long ah, bh, ahi, alo, bhi, blo;
    long c;

    if (af) {
        da = node_get_double(expr_mode, a);
        dbl_unpack(a->d, &ahi, &alo);
        ah = ahi;
    } else
        ah = a->lo;
    if (bf) {
        db = node_get_double(expr_mode, b);
        dbl_unpack(b->d, &bhi, &blo);
        bh = bhi;
    } else
        bh = b->lo;
    c = (ah & 0x80000000UL) != 0 ? -1 : 1;
    if (((ah & 0x80000000UL) != 0) == ((bh & 0x80000000UL) != 0)) {
        if (af || bf) {
            if (!bf)
                db = node_get_double(expr_mode, b);
            if (!af)
                da = node_get_double(expr_mode, a);
            if (is_nan(da) && is_nan(db))
                c = 0;
            else if (da == db && ((a->d < 0.0) == (b->d < 0.0)))
                c = 0;
            else if (is_nan(da) || is_nan(db))
                c = 2;
            else if (da <= db)
                c = db <= da ? 0 : -1;
            else
                c = 1;
        } else if (a->lo != b->lo) {
            if (a->lo < b->lo)
                c = -c;
        } else
            c = 0;
    }
    compare_result(a, op, c, 1);
    return 1;
}

/* ------------------------------------------------------------------ operator scanning and precedence */
long peek_binop(void)
{
    char c, c1;

    while (*optr == ' ' || *optr == '\t')
        optr++;
    c = *optr;
    c1 = c == '\0' ? ' ' : optr[1];
    switch (c) {
    case '!': return c1 == '=' ? 0x10 : 0;
    case '%': return 7;
    case '&': return c1 != '&' ? 6 : 0x11;
    case '*': return 3;
    case '+': return c1 != '+' ? 1 : 0;
    case '-': return 2;
    case '/': return 4;
    case '<':
        if (c1 == '<')
            return 9;
        return c1 != '=' ? 0xb : 0xe;
    case '=': return c1 != '=' ? 0x13 : 0xd;
    case '>':
        if (c1 == '>')
            return 10;
        return c1 != '=' ? 0xc : 0xf;
    case '^': return 8;
    case '|': return c1 != '|' ? 5 : 0x12;
    default: return 0;
    }
}

/* lower number = binds tighter */
long binop_prec(long op)
{
    if (op == 3 || op == 4 || op == 7)
        return 1;
    if (op == 1 || op == 2)
        return 2;
    if (op == 9 || op == 10)
        return 3;
    if (op == 0xb || op == 0xc || op == 0xe || op == 0xf)
        return 4;
    if (op != 0xd && op != 0x13 && op != 0x10) {
        if (op == 6) return 6;
        if (op == 8) return 7;
        if (op == 5) return 8;
        if (op == 0x11) return 9;
        return op == 0x12 ? 10 : 0;
    }
    return 5;
}

static long apply_op(long op, struct val *lhs, struct val *b)
{
    int f32 = (expr_mode & 0x80) != 0;

    switch (op) {
    case 1: return f32 ? op_add32(lhs, b) : op_add(lhs, b);
    case 2: return f32 ? op_sub32(lhs, b) : op_sub(lhs, b);
    case 3: return f32 ? op_mul32(lhs, b) : op_mul(lhs, b);
    case 4: return f32 ? op_div32(lhs, b) : op_div(lhs, b);
    case 5: return f32 ? op_or32(lhs, b) : op_or(lhs, b);
    case 6: return f32 ? op_and32(lhs, b) : op_and(lhs, b);
    case 7: return f32 ? op_mod32(lhs, b) : op_mod(lhs, b);
    case 8: return f32 ? op_xor32(lhs, b) : op_xor(lhs, b);
    case 9: return f32 ? op_shl32(lhs, b) : op_shl(lhs, b);
    case 10: return f32 ? op_shr32(lhs, b) : op_shr(lhs, b);
    case 0xb: case 0xc: case 0xd: case 0xe: case 0xf: case 0x10: case 0x13:
        return f32 ? op_compare32(lhs, b, op) : op_compare(lhs, b, op);
    case 0x11: return f32 ? op_land32(lhs, b) : op_land(lhs, b);
    case 0x12: return f32 ? op_lor32(lhs, b) : op_lor(lhs, b);
    default: return 0;
    }
}

/* operator precedence climbing; consumes operators with precedence < minprec, returns lhs or NULL */
void *parse_binop_rhs(void *vlhs, long minprec)
{
    struct val *lhs = (struct val *)vlhs, *b;
    long op, prec, next, ok = 0;

    op = peek_binop();
    if (op == 0)
        return lhs;
    while ((prec = binop_prec(op)) < minprec) {
        if (op == 10 || op == 9 || op == 0xd || op == 0xe || op == 0xf || op == 0x10 ||
            op == 0x11 || op == 0x12)
            optr += 2;
        else
            optr += 1;
        b = (struct val *)parse_primary();
        if (b == NULL) {
            node_free(lhs);
            return NULL;
        }
        next = peek_binop();
        if (next != 0 && binop_prec(next) < prec) {
            b = (struct val *)parse_binop_rhs(b, prec);
            if (b == NULL) {
                node_free(lhs);
                return NULL;
            }
        }
        ok = apply_op(op, lhs, b);
        if (ok == 0) {
            node_free(b);
            node_free(lhs);
            return NULL;
        }
        node_free(b);
        op = peek_binop();
        if (op == 0)
            return lhs;
    }
    return lhs;
}

void *parse_expr(void)
{
    void *lhs = parse_primary();

    if (lhs == NULL)
        return NULL;
    return parse_binop_rhs(lhs, 0xb);
}

/* ------------------------------------------------------------------ entry points */
unsigned long node_word(void *vnode)
{
    struct val *n = (struct val *)vnode;
    unsigned long w = n->lo;

    if ((expr_mode & 0x14000000UL) != 0)
        w |= (n->hi << ((expr_mode & 0x10000000UL) != 0 ? 16 : 24)) & MASK32;
    return w & MASK32;
}

void *eval_expr(unsigned long mode)
{
    struct val *node;
    char c;

    expr_mode = mode;
    if (optr == NULL) {
        expr_error("sv_optr pointing to NULL address");
        return NULL;
    }
    while (*optr == ' ' || *optr == '\t')
        optr++;
    if (*optr == '\0') {
        expr_error("Missing expression");
        return NULL;
    }
    node = (struct val *)parse_expr();
    c = *optr;
    if (c != '\0' && c != ',' && c != ')' && c != ';') {
        expr_error("Extra characters beyond expression");
        node_free(node);
        return NULL;
    }
    return node;
}

void *eval_int_addr(unsigned long mode)
{
    struct val *node;
    unsigned long mask, w, sel = 0;

    expr_mode = mode;
    if ((mode & 0x400) == 0)
        mask = (mode & 0x200) == 0 ? ((mode & 8) != 0 ? 0xffff0000UL : 0UL) : 0xff000000UL;
    else
        mask = 0xfff80000UL;
    if (*optr == '<') {
        optr++;
        sel = 0x20;
        if (*optr == '<') {
            sel = 0x40;
            optr++;
        }
    } else if (*optr == '>') {
        sel = 0x10;
        optr++;
    }
    node = (struct val *)eval_expr(mode);
    if (node != NULL) {
        if (ISFLOAT(node)) {
            node_free(node);
            expr_error("Expression result must be integer");
            return NULL;
        }
        w = node_word(node);
        if ((mask & w) != 0 && (mask & w) != mask) {
            node_free(node);
            expr_error("Expression result too large");
            return NULL;
        }
        node->flags |= sel;
    }
    return node;
}

void *eval_int_masked(unsigned long mode, unsigned long mask)
{
    struct val *node;
    unsigned long t;

    expr_mode = mode;
    node = (struct val *)eval_expr(mode);
    if (node != NULL) {
        if (ISFLOAT(node)) {
            node_free(node);
            expr_error("Expression result must be integer");
            return NULL;
        }
        t = node_word(node) & ~mask & MASK32;
        if (t != 0 && t != (~mask & MASK32)) {
            node_free(node);
            expr_error("Expression result too large");
            return NULL;
        }
    }
    return node;
}

void *eval_data_word(unsigned long mode)
{
    struct val *node;
    unsigned long mask, w, sel = 0;

    expr_mode = mode;
    if ((mode & 0x10000000UL) == 0)
        mask = (mode & 0x4000000UL) != 0 ? 0xff000000UL : 0UL;
    else
        mask = 0xffff0000UL;
    if (*optr == '<') {
        sel = 0x20;
        optr++;
    } else if (*optr == '>') {
        sel = 0x10;
        optr++;
    }
    node = (struct val *)eval_expr(mode);
    if (node != NULL) {
        if ((node->flags & 0x100UL) != 0) {
            w = node_word(node);
            if ((w & mask) != 0 && (w & mask) != mask) {
                node_free(node);
                expr_error("Expression result too large");
                return NULL;
            }
        }
        node->flags |= sel;
    }
    return node;
}
