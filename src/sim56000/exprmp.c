/* exprmp.c - numeric core of the expression evaluator: word normalisation, base-256 multi-precision
 * division (used for the decimal split of 48/96-bit values) and the conversions between DSP words
 * and doubles (SIM56000.EXE 6.3.0, module expr 0x45bc50-0x45d120).
 * Doubles are handled as real host doubles; the original bit-fiddles the x86 layout, so
 * dbl_unpack/dbl_pack give the IEEE 754 bit halves (hi, lo) portably. */
#include <math.h>
#include <string.h>
#include "sim56000.h"

unsigned long expr_mode = 0;           /* 0x5029dc */

/* ------------------------------------------------------------------ IEEE bit halves of a double */
/* The original stores doubles in x86 layout and reads/writes their two 32-bit halves directly.  The
 * host double is assumed to be an IEEE 754 binary64 (true for all target machines); its bytes are
 * accessed through an endianness probe, so NaN payloads and signs survive a round trip. */
static int dbl_little(void)
{
    static int little = -1;

    if (little < 0) {
        double one = 1.0;
        unsigned char *p = (unsigned char *)&one;

        little = p[7] == 0x3f;
    }
    return little;
}

void dbl_unpack(double d, unsigned long *hi, unsigned long *lo)
{
    unsigned char b[8];
    int i, l = dbl_little();

    memcpy(b, &d, 8);
    if (!l) {
        unsigned char t;

        for (i = 0; i < 4; i++) {
            t = b[i];
            b[i] = b[7 - i];
            b[7 - i] = t;
        }
    }
    *lo = ((unsigned long)b[3] << 24) | ((unsigned long)b[2] << 16) | ((unsigned long)b[1] << 8) | b[0];
    *hi = ((unsigned long)b[7] << 24) | ((unsigned long)b[6] << 16) | ((unsigned long)b[5] << 8) | b[4];
}

double dbl_pack(unsigned long hi, unsigned long lo)
{
    unsigned char b[8];
    double d;
    int i, l = dbl_little();

    b[0] = (unsigned char)lo; b[1] = (unsigned char)(lo >> 8);
    b[2] = (unsigned char)(lo >> 16); b[3] = (unsigned char)(lo >> 24);
    b[4] = (unsigned char)hi; b[5] = (unsigned char)(hi >> 8);
    b[6] = (unsigned char)(hi >> 16); b[7] = (unsigned char)(hi >> 24);
    if (!l) {
        unsigned char t;

        for (i = 0; i < 4; i++) {
            t = b[i];
            b[i] = b[7 - i];
            b[7 - i] = t;
        }
    }
    memcpy(&d, b, 8);
    return d;
}

static long s32(unsigned long v)
{
    v &= MASK32;
    if (v & 0x80000000UL)
        return -(long)((~v & MASK32) + 1UL);
    return (long)v;
}

/* truncate towards zero, low 32 bits (_ftol) */
static unsigned long ftol32(double t)
{
    if (t < 0.0)
        return (0UL - (unsigned long)(-t)) & MASK32;
    return (unsigned long)t & MASK32;
}

/* ------------------------------------------------------------------ node arithmetic helper */
void node_normalize(void *vnode)
{
    struct val *n = (struct val *)vnode;
    unsigned long m16 = (expr_mode & 0x10000000UL) != 0;
    unsigned long mask = m16 ? 0xffffUL : 0xffffffUL;
    unsigned long sh_mask = m16 ? 0xffffUL : 0xffUL;
    int sh = m16 ? 16 : 24;
    unsigned long t;

    t = n->lo;
    n->lo = t & mask;
    t = (n->hi + ((t >> sh) & sh_mask)) & MASK32;
    n->hi = t & mask;
    n->ext = ((((t >> sh) & sh_mask) + n->ext) & MASK32) &
             ((expr_mode & 0x1000000UL) != 0 ? 0x0fUL : 0xffUL);
}

/* ------------------------------------------------------------------ base-256 multi-precision helpers (limb arrays of 8) */
static const unsigned long mp_zero[3] = { 0, 0, 0 };

/* sign of a - b for 3-word values */
long mp_cmp(unsigned long *a, unsigned long *b)
{
    if (b[2] != a[2])
        return b[2] < a[2] ? 1 : -1;
    if (b[1] != a[1])
        return b[1] < a[1] ? 1 : -1;
    if (b[0] != a[0])
        return b[0] < a[0] ? 1 : -1;
    return 0;
}

void mp_unpack(unsigned long *val, unsigned long *limbs)
{
    if ((expr_mode & 0x10000000UL) == 0) {
        limbs[7] = 0;
        limbs[6] = val[2] & 0xff;
        limbs[5] = (val[1] >> 16) & 0xff;
        limbs[4] = (val[1] >> 8) & 0xff;
        limbs[3] = val[1] & 0xff;
        limbs[2] = (val[0] >> 16) & 0xff;
    } else {
        limbs[7] = 0;
        limbs[6] = 0;
        limbs[5] = 0;
        limbs[4] = val[2] & 0xff;
        limbs[3] = (val[1] >> 8) & 0xff;
        limbs[2] = val[1] & 0xff;
    }
    limbs[1] = (val[0] >> 8) & 0xff;
    limbs[0] = val[0] & 0xff;
}

void mp_pack(unsigned long *limbs, unsigned long *val)
{
    if ((expr_mode & 0x10000000UL) != 0) {
        val[2] = limbs[4];
        val[1] = limbs[2] | (limbs[3] << 8);
        val[0] = limbs[0] | (limbs[1] << 8);
        return;
    }
    val[2] = limbs[6];
    val[1] = limbs[3] | (limbs[4] << 8) | (limbs[5] << 16);
    val[0] = limbs[0] | (limbs[1] << 8) | (limbs[2] << 16);
}

/* dst[k] = src[k] for k = n-1 .. 0 (walking downwards, so overlapping shifts up work) */
void mp_copy_limbs(unsigned long *src, unsigned long *dst, long n)
{
    long k;

    for (k = n - 1; k >= 0; k--)
        dst[k] = src[k];
}

void mp_mul_digit(unsigned long d, unsigned long *a, unsigned long *out, long n)
{
    unsigned long acc = 0;
    long i;

    for (i = 0; i < n; i++) {
        acc = (acc + a[i] * d) & MASK32;
        out[i] = acc & 0xff;
        acc >>= 8;
    }
}

/* 1 when b >= a (no final borrow of b - a) */
long mp_ge(unsigned long *a, unsigned long *b, long n)
{
    long borrow = 0, i;

    for (i = 0; i < n; i++)
        borrow = ((long)b[i] - borrow - (long)a[i]) < 0;
    return borrow == 0;
}

/* b -= a */
void mp_sub(unsigned long *a, unsigned long *b, long n)
{
    long borrow = 0, i, t;

    for (i = 0; i < n; i++) {
        t = ((long)b[i] - (long)a[i]) - borrow;
        b[i] = (unsigned long)t & 0xff;
        borrow = t < 0;
    }
}

/* number of limbs used: index of the highest non-zero limb + 2 (1 for zero) */
long mp_len(unsigned long *limbs)
{
    long i = 6;

    while (i >= 0 && limbs[i] == 0)
        i--;
    return i + 2;
}

/* one quotient digit of rem / den (n limbs); rem is reduced */
unsigned long mp_div_digit(unsigned long *den, unsigned long *rem, long n, unsigned long *tmp)
{
    long i = n - 1;
    unsigned long q, d;

    while (den[i] == 0) {
        if (--i < 0)
            return 0;
    }
    q = rem[i] / den[i];
    do {
        mp_mul_digit(q, den, tmp, n);
        q = (q - 1) & MASK32;
    } while (mp_ge(tmp, rem, n) == 0);
    do {
        d = q;
        mp_mul_digit((d + 1) & MASK32, den, tmp, n);
        q = (d + 1) & MASK32;
    } while (mp_ge(tmp, rem, n) != 0);
    mp_mul_digit(d, den, tmp, n);
    mp_sub(tmp, rem, n);
    return d;
}

void mp_divmod(unsigned long *num, unsigned long *den, unsigned long *quot, unsigned long *rem)
{
    unsigned long q[8], r[8], tmp[8], n[8], dn[8];
    long lden, i;

    if (mp_cmp(den, num) < 1) {
        mp_unpack((unsigned long *)mp_zero, q);
        mp_unpack((unsigned long *)mp_zero, r);
        mp_unpack((unsigned long *)mp_zero, tmp);
        mp_unpack(num, n);
        mp_unpack(den, dn);
        lden = mp_len(dn);
        for (i = mp_len(n) - 2; i >= 0; i--) {
            mp_copy_limbs(r, r + 1, lden - 1);
            r[0] = n[i];
            q[i] = mp_div_digit(dn, r, lden, tmp);
        }
        mp_pack(q, quot);
        mp_pack(r, rem);
        return;
    }
    rem[0] = num[0];
    rem[1] = num[1];
    rem[2] = num[2];
    quot[0] = quot[1] = quot[2] = 0;
}

/* ------------------------------------------------------------------ IEEE single <-> double */
void ieee_single_to_double(unsigned long f, double *d)
{
    unsigned long sign = f & 0x80000000UL, hi, lo, u, e;

    f &= MASK32;
    if ((f & 0x7fffffffUL) == 0) {
        *d = dbl_pack(sign, 0);
        return;
    }
    if ((f & 0x7f800000UL) != 0x7f800000UL) {
        if ((f & 0x7f800000UL) != 0) {
            hi = ((f >> 3) & 0x7ffffffUL) |
                 (((f & 0x40000000UL) != 0 ? 0x8000000UL : 0UL) + 0x38000000UL) | sign;
            lo = (f << 29) & MASK32;
            *d = dbl_pack(hi, lo);
            return;
        }
        e = 0x38000000UL;                /* denormal single: normalise */
        for (u = f & 0x7fffffUL; u < 0x400000UL; u <<= 1)
            e -= 0x100000UL;
        hi = (((u & 0x3fffffUL) >> 2) | sign | e) & MASK32;
        lo = (u << 30) & MASK32;
        *d = dbl_pack(hi, lo);
        return;
    }
    hi = ((f >> 3) | sign | 0x7ff00000UL) & MASK32;
    lo = (f << 29) & MASK32;
    *d = dbl_pack(hi, lo);
}

/* v->d -> IEEE single bits in v->lo */
void double_to_ieee_single(void *vnode)
{
    struct val *v = (struct val *)vnode;
    unsigned long hi, lo, e, sign, r;

    dbl_unpack(v->d, &hi, &lo);
    e = (hi >> 20) & 0x7ff;
    sign = hi & 0x80000000UL;
    if (e == 0x7ff) {
        v->lo = ((((hi & 0xfffffUL) | 0xff00000UL) << 3) | (lo >> 29) | sign) & MASK32;
        return;
    }
    if (e < 0x36a) {
        v->lo = sign;
        return;
    }
    if (e > 0x47e) {
        v->lo = sign | 0x7f800000UL;
        return;
    }
    if (e < 0x381) {
        v->lo = (((((hi & 0xfffffUL) | 0x100000UL) << 3) | (lo >> 29)) >> ((0x81UL - e) & 0x1f)) | sign;
        return;
    }
    r = (((hi & 0xfffffUL) << 3) | (lo >> 29) | ((e + 0x80) * 0x800000UL) | sign) & MASK32;
    if (0xfffffffUL < (lo & 0x1fffffffUL) && (lo & 0x2fffffffUL) != 0)
        r = (r + 1) & MASK32;
    v->lo = r;
}

/* ------------------------------------------------------------------ word <-> fraction */
/* largest positive value of the word size selected by the size bits in flags */
static unsigned long frac_max(unsigned long flags, unsigned long mode)
{
    if (flags & 0x80000000UL) return 7UL;
    if (flags & 0x40000000UL) return 0x7fUL;
    if (flags & 0x20000000UL) return 0x7ffUL;
    if ((flags & 0x10000000UL) == 0 && (mode & 0x1000UL) == 0) {
        if (flags & 0x8000000UL) return 0x7ffffUL;
        if (flags & 0x4000000UL) return 0x7fffffUL;
        if (flags & 0x2000000UL) return 0x7fffffffUL;
        return (mode & 0x10000000UL) != 0 ? 0x7fffUL : 0x7fffffUL;
    }
    return 0x7fffUL;
}

void word_to_frac(unsigned long mode, void *vnode)
{
    struct val *n = (struct val *)vnode;
    unsigned long u, u1, w;

    if ((expr_mode & 0x80) != 0) {       /* (sic) the original tests the previous mode word */
        ieee_single_to_double(n->lo, &n->d);
        return;
    }
    expr_mode = mode;
    u = frac_max(n->flags, mode);
    u1 = u + 1;
    w = ((u1 | u) & n->lo) & MASK32;
    if ((w & u1) != 0)
        w = (w | ~u) & MASK32;
    n->d = (double)s32(w) / (double)u1;
}

unsigned long frac_to_word(unsigned long mode, void *vnode)
{
    struct val *n = (struct val *)vnode;
    unsigned long u, u1, mask, r;
    double x, t;

    if ((mode & 0x80) != 0) {
        double_to_ieee_single(n);
        return n->lo;
    }
    expr_mode = mode;
    u = frac_max(n->flags, mode);
    u1 = u + 1;
    mask = u1 | u;
    x = n->d;
    if (!(x > -1.0))
        r = u1;
    else if (!(x < 1.0))
        r = u;
    else {
        t = x * (double)u1 + (x < 0.0 ? -0.5 : 0.5);
        r = ftol32(t);
        if (t - (double)s32(r) == 0.0)
            r &= 0xfffffffeUL;
        if (s32(r) > s32(u))
            r = u;
    }
    r &= mask;
    n->lo = r;
    if ((r & u1) != 0) {
        n->ext = (expr_mode & 0x1000000UL) != 0 ? 0x0fUL : 0xffUL;
        n->hi = mask;
        return mask & (r | (~mask & MASK32));
    }
    n->ext = 0;
    n->hi = 0;
    return mask & r;
}

void dword_to_frac(unsigned long mode, void *vnode)
{
    struct val *n = (struct val *)vnode;
    unsigned long m16 = (mode & 0x10000000UL) != 0;
    unsigned long base, m24, u, u1, hi, lo, both;
    int positive;
    double d;

    if ((mode & 0x80) != 0) {
        /* the double already sits in the two words: hi:lo bits */
        n->d = dbl_pack(n->hi, n->lo);
        return;
    }
    base = m16 ? 0x10000UL : 0x1000000UL;
    expr_mode = mode;
    m24 = m16 ? 0xffffUL : 0xffffffUL;
    u = (mode & 0x1000UL) == 0 ? (m16 ? 0x7fffUL : 0x7fffffUL) : 0x7fUL;
    u1 = u + 1;
    hi = n->hi;
    lo = n->lo;
    both = u | u1;
    positive = (u1 & hi) == 0;
    if (positive)
        hi &= both;
    else {
        lo = ((~lo & m24) + 1) & MASK32;
        hi = ((~hi & both) + ((base & lo) != 0)) & MASK32;
    }
    d = (double)hi / (double)u1 + (double)(lo & m24) / ((double)base * (double)u1);
    n->d = positive ? d : -d;
}

void long_to_frac(void *vnode)
{
    struct val *n = (struct val *)vnode;
    unsigned long flag9 = expr_mode & 0x10001000UL;
    unsigned long v2 = flag9 != 0 ? 0xff010000UL : 0UL;
    unsigned long v3 = (v2 + 0xffffffUL) & MASK32;
    unsigned long v7 = ((v3 * 0x100UL) | v3) & MASK32;
    unsigned long ext = n->ext, hi = n->hi, lo = n->lo, mid = hi;
    unsigned long acc8 = expr_mode & 0x1000000UL;
    unsigned long sign, sh, den;
    double d;

    if ((expr_mode & 0x80) != 0) {
        ext_to_double(n);
        return;
    }
    if ((expr_mode & 0x1000UL) != 0) {
        mid = (lo >> 16) | ((hi & 0xff) << 8);
        ext = hi >> 8;
        lo &= 0xffff;
    }
    sign = acc8 != 0 ? 0x08UL : 0x80UL;
    d = acc8 == 0 ? -256.0 : -16.0;
    if (ext != sign || mid != 0 || lo != 0) {
        sign &= ext;
        sh = flag9 != 0 ? 16 : 24;
        mid = (mid | (ext << sh)) & MASK32;
        if (sign == 0)
            lo &= v3;
        else {
            if (acc8 != 0)
                mid |= 0xf00000UL;
            if (lo == 0)
                mid = ((~mid & v7) + 1) & MASK32;
            else {
                lo = ((~lo & v3) + 1) & MASK32;
                mid = ~mid & v7;
            }
        }
        den = flag9 != 0 ? 0x8000UL : 0x800000UL;
        d = (double)mid / (double)den +
            (double)lo / ((double)((v2 + 0x1000000UL) & MASK32) * (double)den);
        if (sign != 0)
            d = -d;
    }
    n->d = d;
}

void ext_to_double(void *vnode)
{
    struct val *v = (struct val *)vnode;
    unsigned long ext = v->ext, hi = v->hi, s;

    if ((ext & 0x40000000UL) != 0) {
        s = ext & 0x7f;
        if ((ext & 0x400) != 0)
            s = (s | 0x80) & 0xff;
        ieee_single_to_double(((s << 23) | (ext & 0x80000000UL) | ((hi >> 8) & 0x7fffffUL)) & MASK32, &v->d);
        return;
    }
    v->d = dbl_pack(((hi >> 11) & 0xfffffUL) | (ext & 0x80000000UL) | ((ext & 0x7ff) << 20),
                    ((hi << 21) | (v->lo >> 11)) & MASK32);
}

void double_to_ext(void *vnode)
{
    struct val *v = (struct val *)vnode;
    unsigned long hi, lo, e, s;

    dbl_unpack(v->d, &hi, &lo);
    v->lo = 0;
    e = (hi >> 20) & 0x7ff;
    s = (hi & 0x80000000UL) | e;
    v->hi = (((hi & 0xfffffUL) << 11) | (lo >> 21)) & MASK32;
    v->ext = s;
    if (e == 0) {
        if (v->hi != 0)
            v->ext = s | 0x20000000UL;
    } else
        v->hi |= 0x80000000UL;
}

void frac_to_dword(unsigned long mode, void *vnode)
{
    struct val *n = (struct val *)vnode;
    unsigned long f = mode & 0x10001000UL;
    unsigned long m24 = f != 0 ? 0xffffUL : 0xffffffUL;
    unsigned long unit = f != 0 ? 0x8000UL : 0x800000UL;
    unsigned long maxp = f != 0 ? 0x7fffUL : 0x7fffffUL;
    unsigned long ip, lo, c;
    double x = n->d, a, t;
    int neg;

    if (!(x > -1.0)) {
        n->hi = (mode & 0x1000UL) != 0 ? 0x80UL : unit;
        n->lo = 0;
        return;
    }
    if (!(x < 1.0)) {
        if ((mode & 0x1000UL) != 0) {
            n->hi = 0x7fUL;
            n->lo = 0xffffffUL;
        } else {
            n->hi = maxp;
            n->lo = m24;
        }
        return;
    }
    neg = x < 0.0;
    a = neg ? -x : x;
    t = a * (double)unit;
    ip = ftol32(t);
    lo = ftol32((t - (double)s32(ip)) * (double)(m24 + 1)) & m24;
    if (neg) {
        c = lo == 0;
        lo = c ? 0 : (~lo & m24);
        ip = (~ip + c) & MASK32;
    }
    if ((mode & 0x1000UL) != 0) {
        n->hi = (ip >> 8) & 0xff;
        n->lo = (lo & 0xffffffUL) | ((ip & 0xff) << 16);
        return;
    }
    n->lo = lo;
    n->hi = m24 & ip;
}

void frac_to_long(void *vnode)
{
    struct val *n = (struct val *)vnode;
    unsigned long f = expr_mode & 0x10001000UL;
    unsigned long m24 = f != 0 ? 0xffffUL : 0xffffffUL;
    unsigned long unit = f != 0 ? 0x8000UL : 0x800000UL;
    unsigned long acc8 = expr_mode & 0x1000000UL;
    unsigned long sgn = acc8 != 0 ? 0x08UL : 0x80UL;
    unsigned long ip, lo, c, sh;
    double x = n->d, dlim = acc8 != 0 ? 16.0 : 256.0, a, t;
    int neg;

    if ((expr_mode & 0x80) != 0) {
        double_to_ext(n);
        return;
    }
    if (!(x > -dlim)) {
        if ((expr_mode & 0x1000UL) == 0) {
            n->ext = sgn;
            n->lo = 0;
            n->hi = 0;
            return;
        }
        n->hi = 0x8000UL;
        n->ext = 0;
        n->lo = 0;
        return;
    }
    if (!(x < dlim)) {
        if ((expr_mode & 0x1000UL) == 0) {
            n->lo = m24;
            n->ext = sgn - 1;
            n->hi = m24;
            return;
        }
        n->ext = 0;
        n->hi = 0xffffUL;
        n->lo = 0xffffffUL;
        return;
    }
    neg = x < 0.0;
    a = neg ? -x : x;
    t = a * (double)unit;
    ip = ftol32(t);
    lo = ftol32((t - (double)s32(ip)) * (double)(m24 + 1)) & m24;
    if (neg) {
        c = lo == 0;
        lo = c ? 0 : (~lo & m24);
        ip = (~ip + c) & MASK32;
    }
    if ((expr_mode & 0x1000UL) != 0) {
        n->hi = ((unsigned long)(s32(ip) >> 8)) & 0xffff;
        n->lo = ((ip & 0xff) << 16) | lo;
        n->ext = 0;
        return;
    }
    n->lo = lo;
    n->hi = m24 & ip;
    sh = (expr_mode & 0x10000000UL) == 0 ? 24 : 16;
    n->ext = (unsigned long)(s32(ip) >> sh) & (acc8 != 0 ? 0x0fUL : 0xffUL);
}
