/* memacc.c - memory/register access engine: the core_vtable methods mem_reg_read, mem_reg_write,
 * mem_write_n, mem_region_of, the register-bank field packer and the OMR remap hooks
 * (SIM56000.EXE 6.3.0, module memacc 0x42c4c0-0x42e5c0; the insn_exec_h* handlers that follow
 * in the binary belong to the instruction engine).
 * Space ids: 0 P, 1 X, 2 Y, 3 L pair, 4 P alias; 0xd/0xe/0xf P regions, 0x12/0x13/0x14 X regions,
 * 0x17/0x18/0x19 Y regions, 0x1c memory mapped register bank (mdisk backed), 0x1d..0x11c registers
 * living in that bank (sub fields, see reg_field_pack), 3/9/10 pairs of spaces. */
#include "sim56000.h"

#define SELADD(cond, a, b) (((((cond) ? (unsigned long)(a) : 0UL) + (unsigned long)(b))) & MASK32)
#define SEL(cond, k)       ((cond) ? (unsigned long)(k) : 0UL)
#define B0 1UL
#define B1 2UL
#define B2 4UL
#define BIT(x) (((x) != 0) ? 1UL : 0UL)

/* small tables of the original (contiguous in the binary, split here at the object borders) */
static const unsigned long T28E0[4] = { 0, 1, 2, 3 };            /* 0x4c28e0; +4 = 0x4c28e4 */
static const unsigned long T28F0[6] = { 2, 3, 4, 5, 6, 7 };       /* 0x4c28f0; +4 = 0x4c28f4 */
static const unsigned long T2908[4] = { 1, 2, 3, 0 };
static const unsigned long T2918[4] = { 4, 5, 6, 7 };
static const unsigned long T2928[2] = { 2, 3 };
static const unsigned long T2930[8] = { 2, 1, 4, 2, 6, 3, 4, 2 };   /* parts per register (bank A) */
static const unsigned long T2950[4] = { 5, 3, 3, 2 };               /* parts per register (bank B) */
static const unsigned long T2960[4] = { 0xffffUL, 0x3ffffUL, 0xfffffUL, 0x3fffffUL };
static const unsigned long T2A70[4] = { 255, 511, 1023, 2047 };
static const unsigned long T2970[64] = {                            /* 0x4c2970 (43) + 0x4c2a1c (21) */
    32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
    131071UL, 262143UL, 65535UL, 131071UL, 32767, 65535UL, 32767, 65535UL,
    131071UL, 262143UL, 65535UL, 131071UL, 32767, 65535UL, 32767, 65535UL,
    65535UL, 131071UL, 32767, 65535UL, 16383, 32767, 16383, 32767,
    32767, 65535UL, 16383, 32767, 8191, 16383, 8191, 16383,
    131071UL, 262143UL, 65535UL,
    131071UL, 32767, 65535UL, 32767, 65535UL, 524287UL, 1048575UL, 262143UL,
    524287UL, 131071UL, 262143UL, 131071UL, 262143UL, 2097151UL, 4194303UL, 1048575UL,
    2097151UL, 524287UL, 1048575UL, 524287UL, 1048575UL
};

/* address of part idx of the register bank entry for register id, sub field val (the register bank
 * packs each register's parts at addresses derived from the AGU register number in a table) */
unsigned long reg_field_pack(long id, unsigned long val, long idx)
{
    unsigned long u3 = (unsigned long)(id - 0x1d) & MASK32, u1, t, hi, r;
    long k;

    val &= MASK32;
    u1 = (val + (unsigned long)idx) & MASK32;
    hi = (val >> 8) & 0xffffffUL;
    if ((u3 & 0x40) != 0) {
        k = (long)((u3 >> 3) & 3);
        return ((u1 << (3 - k)) & 0xfffff800UL & MASK32) | (T2A70[k] & u1);
    }
    if ((u3 & 0x80) != 0) {
        switch (id) {
        case 0xa7: t = T28E0[idx + 1]; goto b_ca30;
        case 0xa8: return ((val * 2) | (unsigned long)idx) & MASK32;
        case 0xa9: t = T28F0[idx + 1]; goto b_ca4d;
        case 0xaa: t = T2908[idx]; goto b_cadc;
        default: return u1;
        case 0xaf: t = T28E0[idx + 1]; goto b_cb43;
        case 0xb0: return (SELADD(idx != 0, 0x20000, 0x20000)) | val;
        case 0xb1: t = T28F0[idx + 1]; goto b_cb7b;
        case 0xb2: t = T2908[idx]; goto b_cc1a;
        case 0xb7:
            t = T28E0[idx + 1];
            if ((t & B0) != 0)
                return val | SELADD((t & B1) != 0, 0xffff8000UL, 0x10000);
            goto tail_b;
        case 0xb8:
            if ((val & 1) != 0)
                return (val >> 1) | SELADD(idx != 0, 0xffff8000UL, 0x10000);
            return (val >> 1) | SELADD(idx != 0, 0xfffe0000UL, 0x40000);
        case 0xb9:
            t = T28F0[idx + 1];
            if ((t & B1) == 0)
                return BIT(t & B0) | ((val * 2) & MASK32) | SELADD((t & B2) != 0, 0xfffe0000UL, 0x40000);
            r = SELADD((t & B2) != 0, 0xffff8000UL, 0x10000);
            goto b_cdb7;
        case 0xba:
            t = T2908[idx];
            if ((t & B0) != 0)
                return val | SELADD((t & B1) != 0, 0xffff8000UL, 0x10000);
            goto tail_b;
        case 0xbf: t = T28E0[idx + 1]; goto b_cef9;
        case 0xc0: return SEL(idx != 0, 0x800) | (val & 0xff) | ((hi << 12) & MASK32);
        case 0xc1: t = T28F0[idx + 1]; goto b_ce59;
        case 0xc2: t = T2908[idx]; goto b_cef9;
        case 0xc7: t = T28E0[idx + 1]; goto b_d023;
        case 0xc8: return SEL(idx != 0, 0x800) | (((val & 0xfffffe00UL) << 3) & MASK32) | (val & 0x1ff);
        case 0xc9: t = T28F0[idx + 1]; goto b_cf80;
        case 0xca: t = T2908[idx]; goto b_d023;
        case 0xcf: t = T28E0[idx + 1]; goto b_d14f;
        case 0xd0: return SEL(idx != 0, 0x800) | (((val & 0xfffffc00UL) << 2) & MASK32) | (val & 0x3ff);
        case 0xd1: t = T28F0[idx + 1]; goto b_d0ac;
        case 0xd2: t = T2908[idx]; goto b_d14f;
        case 0xd7: t = T28E0[idx + 1]; goto b_d27c;
        case 0xd8: return SEL(idx != 0, 0x800) | (((val & 0xfffff800UL) << 1) & MASK32) | (val & 0x7ff);
        case 0xd9: t = T28F0[idx + 1]; goto b_d1c3;
        case 0xda: t = T2908[idx]; goto b_d27c;
        }
    tail_b:
        return val | SELADD((t & B1) != 0, 0xfffe0000UL, 0x40000);

    b_ca30:
        r = SEL(t & B0, 2);
        return r | BIT(t & B1) | ((val << 2) & MASK32);
    b_ca4d:
        return BIT(t & B2) | SEL(t & B1, 2) | SEL(t & B0, 4) | ((val << 3) & MASK32);
    b_cadc:
        return SEL(t & B0, 2) | BIT(t & B1) | ((val * 4) & MASK32);
    b_cb43:
        return BIT(t & B0) | SELADD((t & B1) != 0, 0x20000, 0x20000) | ((val * 2) & MASK32);
    b_cb7b:
        return BIT(t & B1) | SELADD((t & B2) != 0, 0x20000, 0x20000) | SEL(t & B0, 2) | ((val << 2) & MASK32);
    b_cc1a:
        return BIT(t & B0) | SELADD((t & B1) != 0, 0x20000, 0x20000) | ((val * 2) & MASK32);
    b_cdb7:
        return BIT(t & B0) | ((val * 2) & MASK32) | r;
    b_ce59:
        t = SEL(t & B0, 0x2000) | SEL(t & B1, 0x1000) | SEL(t & B2, 0x800);
        return t | (val & 0xff) | ((hi << 14) & MASK32);
    b_cef9:
        return SEL(t & B0, 0x1000) | SEL(t & B1, 0x800) | (val & 0xff) | ((hi << 13) & MASK32);
    b_cf80:
        t = SEL(t & B0, 0x2000) | SEL(t & B1, 0x1000) | SEL(t & B2, 0x800);
        return t | (((val & 0xfffffe00UL) << 5) & MASK32) | (val & 0x1ff);
    b_d023:
        return SEL(t & B0, 0x1000) | SEL(t & B1, 0x800) | (((val & 0xfffffe00UL) << 4) & MASK32) | (val & 0x1ff);
    b_d0ac:
        t = SEL(t & B0, 0x2000) | SEL(t & B1, 0x1000) | SEL(t & B2, 0x800);
        return t | (((val & 0xfffffc00UL) << 4) & MASK32) | (val & 0x3ff);
    b_d14f:
        return SEL(t & B0, 0x1000) | SEL(t & B1, 0x800) | (((val & 0xfffffc00UL) << 3) & MASK32) | (val & 0x3ff);
    b_d1c3:
        return SEL(t & B0, 0x2000) | SEL(t & B1, 0x1000) | SEL(t & B2, 0x800) |
               (((val & 0xfffff800UL) << 3) & MASK32) | (val & 0x7ff);
    b_d27c:
        return SEL(t & B0, 0x1000) | SEL(t & B1, 0x800) | (((val & 0xfffff800UL) << 2) & MASK32) | (val & 0x7ff);
    }

    switch (id) {
    case 0x1e: case 0x26: case 0x56:
        return val;
    default:
        return u1;
    case 0x25: case 0x28:
        return ((val * 2) | (unsigned long)idx) & MASK32;
    case 0x27: t = T28E0[idx]; goto a_ca30;
    case 0x29: t = T28F0[idx]; goto a_ca4d;
    case 0x2a: t = T2908[idx]; goto a_cadc;
    case 0x2b:
        t = T2918[idx];
        return SEL(t & B0, 4) | SEL(t & B1, 2) | BIT(t & B2) | ((val << 3) & MASK32);
    case 0x2c: t = T2928[idx]; goto a_cadc;
    case 0x2d: case 0x30:
        return SELADD(idx != 0, 0x20000, 0x20000) | val;
    case 0x2e:
        return (val >> 1) | SELADD((val & 1) != 0, 0x20000, 0x20000);
    case 0x2f: t = T28E0[idx]; goto a_cb43;
    case 0x31: t = T28F0[idx]; goto a_cb7b;
    case 0x32: t = T2908[idx]; goto a_cc1a;
    case 0x33:
        t = T2918[idx];
        r = SEL(t & B0, 2) | SELADD((t & B2) != 0, 0x20000, 0x20000);
        return r | BIT(t & B1) | ((val << 2) & MASK32);
    case 0x34: t = T2928[idx]; goto a_cc1a;
    case 0x35:
        if ((val & 1) != 0)
            return (val >> 1) | SELADD(idx != 0, 0x8000, 0x68000);
        goto a_cd00;
    case 0x36:
        if ((val & 1) != 0)
            return (val >> 2) | SELADD((val & 2) != 0, 0x8000, 0x68000);
        return (val >> 2) | SELADD((val & 2) != 0, 0x20000, 0x38000);
    case 0x37:
        t = T28E0[idx];
        if ((t & B0) != 0)
            return val | SELADD((t & B1) != 0, 0x8000, 0x68000);
        goto tail_a;
    case 0x38:
        if ((val & 1) != 0)
            return (val >> 1) | SELADD(idx != 0, 0x8000, 0x68000);
        goto a_cd00;
    case 0x39:
        t = T28F0[idx];
        if ((t & B1) != 0) {
            r = SELADD((t & B2) != 0, 0x8000, 0x68000);
            goto a_cdb7;
        }
        goto a_cda5;
    case 0x3a:
        t = T2908[idx];
        if ((t & B0) != 0)
            return val | SELADD((t & B1) != 0, 0x8000, 0x68000);
        goto tail_a;
    case 0x3b:
        t = T2918[idx];
        if ((t & B1) != 0) {
            r = SELADD((t & B2) != 0, 0x8000, 0x68000);
            goto a_cdb7;
        }
        goto a_cda5;
    case 0x3c:
        t = T2928[idx];
        if ((t & B0) != 0)
            return val | SELADD((t & B1) != 0, 0x8000, 0x68000);
        goto tail_a;
    case 0x3d: case 0x40:
        return SEL(idx != 0, 0x800) | (val & 0xff) | ((hi << 12) & MASK32);
    case 0x3e:
        return (val & 0xff) | ((hi << 11) & MASK32);
    case 0x3f: t = T28E0[idx]; goto a_cef9;
    case 0x41: t = T28F0[idx]; goto a_ce59;
    case 0x42: t = T2908[idx]; goto a_cef9;
    case 0x43:
        t = T2918[idx];
        r = t & B0;
        t = SEL(t & B1, 0x1000) | SEL(r != 0, 0x2000) | SEL(r != 0, 0x800);
        goto a_cedd;
    case 0x44: t = T2928[idx]; goto a_cef9;
    case 0x45: case 0x48:
        return SEL(idx != 0, 0x800) | (((val & 0xfffffe00UL) << 3) & MASK32) | (val & 0x1ff);
    case 0x46:
        return (((val & 0xfffffe00UL) << 2) & MASK32) | (val & 0x1ff);
    case 0x47: t = T28E0[idx]; goto a_d023;
    case 0x49: t = T28F0[idx]; goto a_cf80;
    case 0x4a: t = T2908[idx]; goto a_d023;
    case 0x4b:
        t = T2918[idx];
        r = t & B0;
        t = SEL(t & B1, 0x1000) | SEL(r != 0, 0x2000) | SEL(r != 0, 0x800);
        goto a_d004;
    case 0x4c: t = T2928[idx]; goto a_d023;
    case 0x4d: case 0x50:
        return SEL(idx != 0, 0x800) | (((val & 0xfffffc00UL) << 2) & MASK32) | (val & 0x3ff);
    case 0x4e:
        return (((val & 0xfffffc00UL) << 1) & MASK32) | (val & 0x3ff);
    case 0x4f: t = T28E0[idx]; goto a_d14f;
    case 0x51: t = T28F0[idx]; goto a_d0ac;
    case 0x52: t = T2908[idx]; goto a_d14f;
    case 0x53:
        t = T2918[idx];
        r = t & B0;
        t = SEL(t & B1, 0x1000) | SEL(r != 0, 0x2000) | SEL(r != 0, 0x800);
        goto a_d130;
    case 0x54: t = T2928[idx]; goto a_d14f;
    case 0x55: case 0x58:
        return SEL(idx != 0, 0x800) | (((val & 0xfffff800UL) << 1) & MASK32) | (val & 0x7ff);
    case 0x57: t = T28E0[idx]; goto a_d27c;
    case 0x59: t = T28F0[idx]; goto a_d1c3;
    case 0x5a: t = T2908[idx]; goto a_d27c;
    case 0x5b:
        t = T2918[idx];
        r = t & B0;
        return SEL(t & B1, 0x1000) | SEL(r != 0, 0x2000) | SEL(r != 0, 0x800) |
               (((val & 0xfffff800UL) << 3) & MASK32) | (val & 0x7ff);
    case 0x5c: t = T2928[idx]; goto a_d27c;
    }
tail_a:
    return val | SELADD((t & B1) != 0, 0x20000, 0x38000);

a_ca30:
    r = SEL(t & B0, 2);
    return r | BIT(t & B1) | ((val << 2) & MASK32);
a_ca4d:
    return BIT(t & B2) | SEL(t & B1, 2) | SEL(t & B0, 4) | ((val << 3) & MASK32);
a_cadc:
    return SEL(t & B0, 2) | BIT(t & B1) | ((val * 4) & MASK32);
a_cb43:
    return BIT(t & B0) | SELADD((t & B1) != 0, 0x20000, 0x20000) | ((val * 2) & MASK32);
a_cb7b:
    return BIT(t & B1) | SELADD((t & B2) != 0, 0x20000, 0x20000) | SEL(t & B0, 2) | ((val << 2) & MASK32);
a_cc1a:
    return BIT(t & B0) | SELADD((t & B1) != 0, 0x20000, 0x20000) | ((val * 2) & MASK32);
a_cd00:
    return (val >> 1) | SELADD(idx != 0, 0x20000, 0x38000);
a_cda5:
    r = SELADD((t & B2) != 0, 0x20000, 0x38000);
a_cdb7:
    return BIT(t & B0) | ((val * 2) & MASK32) | r;
a_ce59:
    t = SEL(t & B0, 0x2000) | SEL(t & B1, 0x1000) | SEL(t & B2, 0x800);
a_cedd:
    return t | (val & 0xff) | ((hi << 14) & MASK32);
a_cef9:
    return SEL(t & B0, 0x1000) | SEL(t & B1, 0x800) | (val & 0xff) | ((hi << 13) & MASK32);
a_cf80:
    t = SEL(t & B0, 0x2000) | SEL(t & B1, 0x1000) | SEL(t & B2, 0x800);
a_d004:
    return t | (((val & 0xfffffe00UL) << 5) & MASK32) | (val & 0x1ff);
a_d023:
    return SEL(t & B0, 0x1000) | SEL(t & B1, 0x800) | (((val & 0xfffffe00UL) << 4) & MASK32) | (val & 0x1ff);
a_d0ac:
    t = SEL(t & B0, 0x2000) | SEL(t & B1, 0x1000) | SEL(t & B2, 0x800);
a_d130:
    return t | (((val & 0xfffffc00UL) << 4) & MASK32) | (val & 0x3ff);
a_d14f:
    return SEL(t & B0, 0x1000) | SEL(t & B1, 0x800) | (((val & 0xfffffc00UL) << 3) & MASK32) | (val & 0x3ff);
a_d1c3:
    return SEL(t & B0, 0x2000) | SEL(t & B1, 0x1000) | SEL(t & B2, 0x800) |
           (((val & 0xfffff800UL) << 3) & MASK32) | (val & 0x7ff);
a_d27c:
    return SEL(t & B0, 0x1000) | SEL(t & B1, 0x800) | (((val & 0xfffff800UL) << 2) & MASK32) | (val & 0x7ff);
}

/* address mask and part count of a register-bank register (id 0x1d..0x11c) */
static void reg_geometry(long id, unsigned long *addr, long *nparts, long *ret)
{
    unsigned long u = (unsigned long)(id - 0x1d);
    long n;

    n = (long)((u & 0x80) == 0 ? T2930[u & 7] : T2950[u & 3]);
    *nparts = n;
    if ((u & 0x40) == 0) {
        *addr &= T2970[u & 0x3f];
        *ret = (u & 0x3f) > 7 ? 1 : n;
    } else {
        *addr &= T2960[(u >> 3) & 3];
        *ret = n;
    }
}

/* read a word of the space (id 3/9/10: pairs) or of a register-bank register */
long mem_reg_read(long id, unsigned long addr, unsigned long *out)
{
    unsigned long mask, a, u2, u4, acc;
    long n, ret, i, r1, r2, ridx;
    unsigned long parts[6];
    struct mem_region *e;

    if (id < 0x1d || id > 0x11c) {
        if (id == 0x11d)
            mask = 0xffffffUL;
        else
            mask = id != 0x1c ? 0xffffUL : 0x7fffffUL;
        a = addr & mask;
        *out = 0;
        switch (id) {
        case 3:
            r1 = mem_reg_read(2, a, out);
            r2 = mem_reg_read(1, a, out + 1);
            return r1 & r2;
        case 4:
            id = 0;
            /* fall through */
        case 0: case 1: case 2:
            id = mem_region_of(id, a);
            break;
        case 9:
            r1 = mem_reg_read(0x17, a, out);
            r2 = mem_reg_read(0x12, a, out + 1);
            return r1 & r2;
        case 10:
            r1 = mem_reg_read(0x18, a, out);
            r2 = mem_reg_read(0x13, a, out + 1);
            return r1 & r2;
        default:
            break;
        }
        ridx = memmap_find(id, a);
        e = &cur_dtype->map[ridx];
        if (id == 0x12 || id == 0xd || id == 0x17 || id == 0x11d) {
            if ((cur_dtype->family & 0x3618) != 0) {
                *out = 5;
                return 1;
            }
            *out = cur_dev->pins[PIN_BLOCK_DATA].w[0];
            return mdisk_read(cur_dev->number, id, a, out);
        }
        if (id == 0x13 && (e->attr & 0x10000UL) != 0) {
            dev_spaces_call_8(a, (long *)out, 0);
            return 1;
        }
        if (id == 0x1c)
            return mdisk_read(cur_dev->number, 0x1c, a, out);
        if ((unsigned long)e->lo <= a && a <= (unsigned long)e->hi) {
            *out = cur_dev->mem[ridx].words[a - (unsigned long)e->lo];
            return 1;
        }
        return 0;
    }
    u2 = (unsigned long)(id - 0x1d);
    u4 = u2 & 1;
    a = addr;
    reg_geometry(id, &a, &n, &ret);
    for (i = 0; i < n; i++) {
        parts[i] = 0;
        mdisk_read(cur_dev->number, 0x1c, reg_field_pack(id, a, i), &parts[i]);
    }
    acc = 0;
    for (i = n - 1; i >= 0; i--)
        acc = ((acc << (u4 ? 8 : 4)) | ((u4 ? 0xffUL : 0xfUL) & parts[i])) & MASK32;
    if (u4 != 0 && (u2 & 0x80) != 0)
        acc >>= 4;
    *out = acc;
    return ret;
}

long mem_write_n(long id, unsigned long addr, unsigned long count, unsigned long *val)
{
    static const long size[8] = { 2, 1, 4, 2, 6, 3, 4, 2 };      /* 0x4c2a90.. */
    long step = (id >= 0x1d && id <= 0x24) ? size[id - 0x1d] : 1;
    unsigned long done = 0;

    if (count != 0) {
        do {
            mem_reg_write(id, addr, val);
            done += (unsigned long)step;
            addr += (unsigned long)step;
        } while (done < count);
    }
    return step;
}

static int in_region(struct mem_region *e, unsigned long a)
{
    return (unsigned long)e->lo <= a && a <= (unsigned long)e->hi;
}

/* which memory region (0xd.. P, 0x12.. X, 0x17.. Y) of the space an address falls in; depends on
 * the operating mode (OMR) and on the device family */
long mem_region_of(long space, unsigned long addr)
{
    unsigned long fam = (unsigned long)cur_dtype->family;
    unsigned long omr = cur_dev->regs[0][0x1b0 / 4];
    unsigned long m3 = omr & 3, m4 = omr & 4, lim1, lim2;
    struct mem_region *map = cur_dtype->map;
    struct mem_block *mem = cur_dev->mem;
    long i;

    if ((fam & 0x3400UL) == 0) {
        if ((fam & 0x210UL) != 0) {
            lim1 = lim2 = 0;
            if ((fam & 0x10UL) != 0) {
                lim1 = 0xf00;
                lim2 = 0x600;
            }
            if ((fam & 0x200UL) != 0) {
                lim1 = 0x1900;
                lim2 = 0x500;
            }
            switch (space) {
            case 0:
            case 4:
                if (m4 == 0)
                    return addr < lim1 ? 0xf : 0xd;
                if (addr > 0x3ff && addr < lim2)
                    return 0xd;
                i = memmap_find(0xe, addr);
                if (in_region(&map[i], addr))
                    return 0xe;
                i = memmap_find(0xf, addr);
                if (addr < (unsigned long)map[i].lo)
                    return 0xd;
                if ((unsigned long)map[i].hi < addr)
                    return 0xd;
                return 0xf;
            case 1:
                m4 = 1;
                break;
            case 2:
                if (m4 == 0 || addr < 0x400 || addr > 0x7ff) {
                    i = memmap_find(0x18, addr);
                    if (in_region(&map[i], addr))
                        return 0x18;
                    i = memmap_find(0x19, addr);
                    if (in_region(&map[i], addr))
                        return 0x19;
                }
                return 0x17;
            case 3:
                break;
            default:
                return space;
            }
        }
        switch (space) {
        case 0:
        case 4:
            if ((((fam & 0x100UL) != 0 && (m3 == 3 || m3 == 2)) || m3 == 1 ||
                 (fam > 3 && (omr & 0x10UL) != 0)) &&
                memmap_find(0xf, addr) != 0 &&
                addr <= (unsigned long)map[memmap_find(0xf, addr)].hi)
                return 0xf;
            if (m3 != 3 && addr <= (unsigned long)map[memmap_find(0xe, addr)].hi)
                return 0xe;
            return 0xd;
        case 1:
            i = memmap_find(0x13, addr);
            if (in_region(&map[i], addr))
                return 0x13;
            if (m4 != 0 && addr <= (unsigned long)map[memmap_find(0x14, addr)].hi)
                return 0x14;
            return 0x12;
        case 2:
            if ((omr & 8UL) == 0 || fam < 4) {
                i = memmap_find(0x18, addr);
                if (addr <= (unsigned long)map[i].hi)
                    return 0x18;
                if (m4 != 0 && addr <= (unsigned long)map[memmap_find(0x19, addr)].hi)
                    return 0x19;
            }
            return 0x17;
        default:
            return space;
        }
    }
    switch (space) {
    case 0:
    case 4:
        i = memmap_find(0xe, addr);
        if (in_region(&map[i], addr) && mem[i].disabled == 0)
            return 0xe;
        i = memmap_find(0xf, addr);
        if (in_region(&map[i], addr) && mem[i].disabled == 0)
            return 0xf;
        return 0xd;
    case 1:
        i = memmap_find(0x13, addr);
        if (in_region(&map[i], addr) && mem[i].disabled == 0)
            return 0x13;
        i = memmap_find(0x14, addr);
        if (in_region(&map[i], addr) && mem[i].disabled == 0)
            return 0x14;
        return 0x12;
    case 2:
        i = memmap_find(0x18, addr);
        if (in_region(&map[i], addr) && mem[i].disabled == 0)
            return 0x18;
        i = memmap_find(0x19, addr);
        if (in_region(&map[i], addr) && mem[i].disabled == 0)
            return 0x19;
        return 0x17;
    case 3:                            /* re-dispatches to the modal switch: default */
        return space;
    default:
        return space;
    }
}

/* write a word (val[0], 24 bits; pairs use val[1]) to a space or register-bank register */
long mem_reg_write(long id, unsigned long addr, unsigned long *val)
{
    unsigned long v = val[0] & 0xffffffUL, mask, a, u4, u2;
    long n, ret, i, ridx;
    unsigned long parts[6];
    struct mem_region *e;

    if (id < 0x1d || id > 0x11c) {
        if (id == 0x11d)
            mask = 0xffffffUL;
        else
            mask = id != 0x1c ? 0xffffUL : 0x7fffffUL;
        a = addr & mask;
        switch (id) {
        case 3:
            mem_reg_write(2, a, val);
            mem_reg_write(1, a, val + 1);
            return 1;
        case 4:
            id = 0;
            /* fall through */
        case 0: case 1: case 2:
            id = mem_region_of(id, a);
            break;
        case 9:
            mem_reg_write(0x17, a, val);
            mem_reg_write(0x12, a, val + 1);
            return 1;
        case 10:
            mem_reg_write(0x18, a, val);
            mem_reg_write(0x13, a, val + 1);
            return 1;
        default:
            break;
        }
        ridx = memmap_find(id, a);
        e = &cur_dtype->map[ridx];
        if (id == 0x1c) {
            mdisk_write(cur_dev->number, 0x1c, a, v);
            return 1;
        }
        if (id == 0x12 || id == 0xd || id == 0x17 || id == 0x11d) {
            if ((cur_dtype->family & 0x3618) != 0)
                return 1;
            mdisk_write(cur_dev->number, id, a, v);
            return 1;
        }
        if (id == 0x13 && (e->attr & 0x10000UL) != 0) {
            dev_spaces_call_c(a, (long)val[0], 0);
            return 1;
        }
        if ((e->attr & 0x800000UL) == 0 && in_region(e, a))
            cur_dev->mem[ridx].words[a - (unsigned long)e->lo] = v;
        return 1;
    }
    u2 = (unsigned long)(id - 0x1d);
    u4 = u2 & 1;
    a = addr;
    reg_geometry(id, &a, &n, &ret);
    if (u4 != 0 && (u2 & 0x80) != 0)
        v = (v << 4) & MASK32;
    for (i = 0; i < n; i++) {
        parts[i] = (u4 ? 0xffUL : 0xfUL) & v;
        v >>= u4 ? 8 : 4;
    }
    for (i = 0; i < n; i++)
        mdisk_write(cur_dev->number, 0x1c, reg_field_pack(id, a, i), parts[i]);
    return ret;
}

/* Alias one memory block onto another and enable one of the two, the ROM/RAM mode switch of the
 * 56009/56011/56012 devices. */
static void omr_alias(long sa, unsigned long aa, long sb, unsigned long ab, unsigned long dis_a, unsigned long dis_b)
{
    struct mem_block *mem = cur_dev->mem;
    long a = memmap_find(sa, aa), b = memmap_find(sb, ab);

    mem[a].words = mem[b].words;
    mem[a].disabled = (long)dis_a;
    mem[b].disabled = (long)dis_b;
}

static void omr_remap(unsigned long omr, unsigned long a1, unsigned long b1, unsigned long a2,
                      unsigned long a3, unsigned long b3)
{
    unsigned long d1 = (omr & 8) == 0, d2 = (omr & 8) != 0;

    cur_dev->mem[memmap_find(0xe, 0)].disabled = (omr & 0x13) != 0;
    omr_alias(0xe, a1, 0x13, b1, d1, d2);
    omr_alias(0xe, a2, 0x18, 0xe00, d1, d2);
    omr_alias(0xe, a3, 0x13, b3, (omr & 4) == 0, (omr & 4) != 0);
}

void omr_remap_56009(unsigned long omr)
{
    omr_remap(omr, 0x200, 0xf00, 0x500, 0x800, 0xc00);
}

void omr_remap_56011(unsigned long omr)
{
    omr_remap(omr, 0x200, 0xd00, 0x500, 0x800, 0xa00);
}

void omr_remap_56012(unsigned long omr)
{
    omr_remap(omr, 0x100, 0xd00, 0x400, 0x700, 0xa00);
}

/* Read check of a register bank register (slot 5): assembles the 24-bit value from its parts,
 * continuing at the following addresses until 24 bits are filled; flag != 0 reads 3 bytes of a space. */
long reg_write_check(long id, unsigned long addr, unsigned long *val, long flag)
{
    unsigned long u4, u2, acc, tmp[3], a;
    long n, step, i, bits, shift, count, orig = id, and_;
    unsigned long parts[6];

    if (id < 0x1d || id > 0x11c) {
        if (flag == 0)
            return mem_reg_read(id, addr, val);
        and_ = 3;
        acc = 0;
        for (i = 2; i >= 0; i--) {
            tmp[0] = tmp[1] = 0;
            and_ &= mem_reg_read(id, (unsigned long)i + addr, tmp);
            acc = ((acc << 8) | (tmp[0] & 0xff)) & MASK32;
        }
        val[0] = acc;
        return and_ != 0 ? 3 : 0;
    }
    u4 = (unsigned long)(id - 0x1d);
    u2 = u4 & 1;
    a = addr;
    reg_geometry(id, &a, &n, &step);
    for (i = 0; i < n; i++) {
        parts[i] = 0;
        mdisk_read(cur_dev->number, 0x1c, reg_field_pack(id, a, i), &parts[i]);
    }
    shift = u2 != 0 ? 8 : 4;
    bits = 0;
    acc = 0;
    if (n > 0) {
        bits = shift * n;
        for (i = n - 1; i >= 0; i--)
            acc = ((acc << shift) | ((u2 ? 0xffUL : 0xfUL) & parts[i])) & MASK32;
    }
    count = step;
    if (u2 != 0 && (u4 & 0x80) != 0) {
        acc >>= 4;
        bits -= 4;
    }
    i = bits;                          /* bit position of the next chunk */
    while (i < 0x18) {
        a = (a + (unsigned long)step) & MASK32;
        tmp[0] = tmp[1] = 0;
        mem_reg_read(orig, a, tmp);
        acc |= (tmp[0] << (i & 0x1f)) & MASK32;
        count += step;
        i += bits;
    }
    val[0] = acc & 0xffffffUL;
    return count;
}

/* Write check of a register bank register (slot 6): splits val[0] into parts, writes them and the
 * remaining higher chunks to the following addresses; flag != 0 writes 3 bytes of a space. */
long reg_read_check(long id, unsigned long addr, unsigned long *val, long flag)
{
    unsigned long v = val[0] & 0xffffffUL, u5, u28, u24, a, x;
    long n, step, i, shift, bits, count;
    unsigned long parts[6], buf[2];

    if (id > 0x1c && id < 0x11d) {
        u5 = (unsigned long)(id - 0x1d);
        u28 = u5 & 1;
        u24 = u5 & 0x80;
        a = addr;
        reg_geometry(id, &a, &n, &step);
        shift = u28 != 0 ? 8 : 4;
        x = v;
        if (u28 != 0 && u24 != 0)
            x = (v << 4) & MASK32;
        bits = 0;
        if (n > 0) {
            bits = shift * n;
            for (i = 0; i < n; i++) {
                parts[i] = (u28 ? 0xffUL : 0xfUL) & x;
                x >>= shift;
            }
        }
        for (i = 0; i < n; i++)
            mdisk_write(cur_dev->number, 0x1c, reg_field_pack(id, a, i), parts[i]);
        count = step;
        shift = bits;
        if (u28 != 0 && u24 != 0) {
            bits -= 4;
            shift = bits;
        }
        while (bits < 0x18) {
            a = (a + (unsigned long)step) & MASK32;
            v >>= (shift & 0x1f);
            buf[0] = v;
            buf[1] = val[1];
            mem_reg_write(id, a, buf);
            bits += shift;
            count += step;
        }
        return count;
    }
    if (flag == 0) {
        buf[0] = v;
        buf[1] = val[1];
        return mem_reg_write(id, addr, buf);
    }
    {
        long r1, r2, r3;

        buf[0] = val[0] & 0xff;
        buf[1] = 0;
        r1 = mem_reg_write(id, addr, buf);
        buf[0] = (v >> 8) & 0xff;
        r2 = mem_reg_write(id, addr + 1, buf);
        buf[0] = (v >> 16) & 0xff;
        r3 = mem_reg_write(id, addr + 2, buf);
        return (r1 & r2 & r3) != 0 ? 3 : 0;
    }
}
