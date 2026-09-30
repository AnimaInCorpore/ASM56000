/*
 * abiops.c - DSPLNK.EXE (CLAS56 v6.3, DSP Linker 6.3.7), ABI expression
 * subsystem: the operator library called by the parser actions
 * (0x4356a0-0x435cff, glue stub 0x43a408).  Values are 32-bit patterns in
 * unsigned long; the signed operations convert with ABI_S32().  The original
 * 64-bit helpers (_allmul, _alldiv, _allrem) are done on 32-bit halves.
 */
#include "abi.h"

#define U32(x) ((unsigned long)(x) & 0xffffffffUL)

/* 43a408: the error hook of the operators; it does nothing (the message is
   dropped) */
void abi_expr_error_stub(char *msg)
{
    (void)msg;
}

/* 4356a0 */
unsigned long abi_op_add(unsigned long a, unsigned long b)
{
    return U32(a + b);
}

/* 4356ab */
unsigned long abi_op_sub(unsigned long a, unsigned long b)
{
    return U32(a - b);
}

/* 4356b6: low 32 bits of the product */
unsigned long abi_op_mul(unsigned long a, unsigned long b)
{
    unsigned long al, ah, bl, bh;

    a = U32(a);
    b = U32(b);
    al = a & 0xffffUL;
    ah = a >> 16;
    bl = b & 0xffffUL;
    bh = b >> 16;
    return U32(al * bl + (((ah * bl + al * bh) & 0xffffUL) << 16));
}

/* 4356c2 */
unsigned long abi_op_div(unsigned long a, unsigned long b)
{
    long sa, sb;

    if (U32(b) == 0) {
        abi_expr_error_stub("Divide by Zero\n");
        return 0;
    }
    sa = ABI_S32(a);
    sb = ABI_S32(b);
    return U32((unsigned long)(sa / sb));
}

/* 4356e5 */
unsigned long abi_op_mod(unsigned long a, unsigned long b)
{
    long sa, sb;

    if (U32(b) == 0) {
        abi_expr_error_stub("Divide by Zero\n");
        return 0;
    }
    sa = ABI_S32(a);
    sb = ABI_S32(b);
    return U32((unsigned long)(sa % sb));
}

/* ---- 64-bit helpers on (lo, hi) pairs --------------------------------- */
static ABI64 mk64(unsigned long lo, unsigned long hi)
{
    ABI64 r;

    r.lo = U32(lo);
    r.hi = U32(hi);
    return r;
}

/* 32x32 -> 64 unsigned product */
static ABI64 umul32(unsigned long a, unsigned long b)
{
    unsigned long al, ah, bl, bh, ll, lh, hl, hh, mid, lo, hi;

    al = a & 0xffffUL;
    ah = (a >> 16) & 0xffffUL;
    bl = b & 0xffffUL;
    bh = (b >> 16) & 0xffffUL;
    ll = al * bl;
    lh = al * bh;
    hl = ah * bl;
    hh = ah * bh;
    mid = (ll >> 16) + (lh & 0xffffUL) + (hl & 0xffffUL);
    lo = (ll & 0xffffUL) | ((mid & 0xffffUL) << 16);
    hi = hh + (lh >> 16) + (hl >> 16) + (mid >> 16);
    return mk64(lo, hi);
}

static int is_neg64(ABI64 a)
{
    return (a.hi & 0x80000000UL) != 0;
}

static ABI64 neg64(ABI64 a)
{
    ABI64 r;

    r.lo = U32(~a.lo + 1UL);
    r.hi = U32(~a.hi + (r.lo == 0 ? 1UL : 0UL));
    return r;
}

static int ucmp64(ABI64 a, ABI64 b)
{
    if (a.hi != b.hi)
        return a.hi < b.hi ? -1 : 1;
    if (a.lo != b.lo)
        return a.lo < b.lo ? -1 : 1;
    return 0;
}

static ABI64 usub64(ABI64 a, ABI64 b)
{
    ABI64 r;

    r.lo = U32(a.lo - b.lo);
    r.hi = U32(a.hi - b.hi - (a.lo < b.lo ? 1UL : 0UL));
    return r;
}

/* unsigned 64/64 division: quotient in *q, remainder in *r */
static void udivmod64(ABI64 a, ABI64 b, ABI64 *q, ABI64 *r)
{
    ABI64 quo, rem;
    int i;
    unsigned long bit;

    quo = mk64(0, 0);
    rem = mk64(0, 0);
    for (i = 63; i >= 0; i--) {
        rem.hi = U32((rem.hi << 1) | (rem.lo >> 31));
        rem.lo = U32(rem.lo << 1);
        bit = (i >= 32) ? ((a.hi >> (i - 32)) & 1UL) : ((a.lo >> i) & 1UL);
        rem.lo |= bit;
        if (ucmp64(rem, b) >= 0) {
            rem = usub64(rem, b);
            if (i >= 32)
                quo.hi |= 1UL << (i - 32);
            else
                quo.lo |= 1UL << i;
        }
    }
    *q = quo;
    *r = rem;
}

/* 43570a */
ABI64 abi_op_add64(unsigned long a_lo, unsigned long a_hi, unsigned long b_lo, unsigned long b_hi)
{
    unsigned long lo = U32(a_lo + b_lo);

    return mk64(lo, a_hi + b_hi + (lo < U32(a_lo) ? 1UL : 0UL));
}

/* 43571b */
ABI64 abi_op_sub64(unsigned long a_lo, unsigned long a_hi, unsigned long b_lo, unsigned long b_hi)
{
    return mk64(a_lo - b_lo, a_hi - b_hi - (U32(a_lo) < U32(b_lo) ? 1UL : 0UL));
}

/* 43572c: _allmul (low 64 bits of the product) */
ABI64 abi_op_mul64(unsigned long a_lo, unsigned long a_hi, unsigned long b_lo, unsigned long b_hi)
{
    ABI64 p;

    a_lo = U32(a_lo);
    a_hi = U32(a_hi);
    b_lo = U32(b_lo);
    b_hi = U32(b_hi);
    p = umul32(a_lo, b_lo);
    p.hi = U32(p.hi + abi_op_mul(a_lo, b_hi) + abi_op_mul(a_hi, b_lo));
    return p;
}

/* signed 64-bit divide / remainder shared by div64 / mod64 */
static void sdivmod64(ABI64 a, ABI64 b, ABI64 *q, ABI64 *r)
{
    int na = is_neg64(a), nb = is_neg64(b);

    if (na)
        a = neg64(a);
    if (nb)
        b = neg64(b);
    udivmod64(a, b, q, r);
    if (na != nb)
        *q = neg64(*q);
    if (na)
        *r = neg64(*r);
}

/* 435746: _alldiv */
ABI64 abi_op_div64(unsigned long a_lo, unsigned long a_hi, unsigned long b_lo, unsigned long b_hi)
{
    ABI64 q, r;

    if (U32(b_lo) == 0 && U32(b_hi) == 0) {
        abi_expr_error_stub("Divide by Zero\n");
        return mk64(0, 0);
    }
    sdivmod64(mk64(a_lo, a_hi), mk64(b_lo, b_hi), &q, &r);
    return q;
}

/* 43577d: _allrem */
ABI64 abi_op_mod64(unsigned long a_lo, unsigned long a_hi, unsigned long b_lo, unsigned long b_hi)
{
    ABI64 q, r;

    if (U32(b_lo) == 0 && U32(b_hi) == 0) {
        abi_expr_error_stub("Divide by Zero\n");
        return mk64(0, 0);
    }
    sdivmod64(mk64(a_lo, a_hi), mk64(b_lo, b_hi), &q, &r);
    return r;
}

/* 4357b4: logical shift right (l4_util.names calls it op_shl) */
unsigned long abi_op_shr(unsigned long a, unsigned long n)
{
    return U32(a) >> (n & 0x1f);
}

/* 4357c1: shift left */
unsigned long abi_op_shl(unsigned long a, unsigned long n)
{
    return U32(a << (n & 0x1f));
}

/* 4357ce */
unsigned long abi_op_compl(unsigned long a)
{
    return U32(~a);
}

/* 4357d8 */
unsigned long abi_op_neg(unsigned long a)
{
    return U32(0UL - a);
}

/* 4357e2 */
unsigned long abi_op_lnot(unsigned long a)
{
    return U32(a) == 0;
}

/* 4357f0 */
unsigned long abi_op_land(unsigned long a, unsigned long b)
{
    return (U32(a) != 0 && U32(b) != 0) ? 1UL : 0UL;
}

/* 435817 */
unsigned long abi_op_lor(unsigned long a, unsigned long b)
{
    return (U32(a) == 0 && U32(b) == 0) ? 0UL : 1UL;
}

/* 43583e */
unsigned long abi_op_gt(unsigned long a, unsigned long b)
{
    return ABI_S32(a) > ABI_S32(b);
}

/* 435850 */
unsigned long abi_op_ge(unsigned long a, unsigned long b)
{
    return ABI_S32(a) >= ABI_S32(b);
}

/* 435862 */
unsigned long abi_op_lt(unsigned long a, unsigned long b)
{
    return ABI_S32(a) < ABI_S32(b);
}

/* 435874 */
unsigned long abi_op_le(unsigned long a, unsigned long b)
{
    return ABI_S32(a) <= ABI_S32(b);
}

/* 435886 */
unsigned long abi_op_eq(unsigned long a, unsigned long b)
{
    return U32(a) == U32(b);
}

/* 435898 */
unsigned long abi_op_ne(unsigned long a, unsigned long b)
{
    return U32(a) != U32(b);
}

/* 4358aa */
unsigned long abi_op_and(unsigned long a, unsigned long b)
{
    return U32(a & b);
}

/* 4358b5 */
unsigned long abi_op_or(unsigned long a, unsigned long b)
{
    return U32(a | b);
}

/* 4358c0 */
unsigned long abi_op_xor(unsigned long a, unsigned long b)
{
    return U32(a ^ b);
}

/* 4358cb */
unsigned long abi_op_cond(unsigned long cond, unsigned long a, unsigned long b)
{
    return U32(cond) == 0 ? U32(b) : U32(a);
}

/* 4358ea: assignment to an ABI scratch variable (created on first use) */
ABI64 abi_assign_op(SymArr *tab, char *name, int op, unsigned long v_lo, unsigned long v_hi)
{
    ABISYM *e;
    ABI64 r;

    r = mk64(0, 0);
    e = symtbl_find_by_name(tab, name);
    if (e == NULL) {
        e = abi_mp_sym_alloc(name, 0L, 0L, 3L);
        (*tab->add)(tab, e);
    }
    switch (op) {
    case 0x3d:
        r = mk64(v_lo, v_hi);
        e->lo = r.lo;
        e->hi = r.hi;
        break;
    case 0x101:
        r = abi_op_add64(e->lo, e->hi, v_lo, v_hi);
        e->lo = r.lo;
        e->hi = r.hi;
        break;
    case 0x102:
        r = abi_op_sub64(e->lo, e->hi, v_lo, v_hi);
        e->lo = r.lo;
        e->hi = r.hi;
        break;
    case 0x103:
        r = abi_op_mul64(e->lo, e->hi, v_lo, v_hi);
        e->lo = r.lo;
        e->hi = r.hi;
        break;
    case 0x104:
        r = abi_op_div64(e->lo, e->hi, v_lo, v_hi);
        e->lo = r.lo;
        e->hi = r.hi;
        break;
    case 0x105:
        r = abi_op_mod64(e->lo, e->hi, v_lo, v_hi);
        e->lo = r.lo;
        e->hi = r.hi;
        break;
    default:
        fprintf(stderr, "Not A Recognized Assign Operator! \n");
        exit(1);
    }
    return r;
}
