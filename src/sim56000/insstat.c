/* insstat.c - per-instruction statistics records, condition code evaluation, mnemonic names
 * (SIM56000.EXE 6.3.0, module insstat 0x41c750-0x41ce50).
 * A statistics record (struct insn_stat) is built from a decoded instruction record DEC
 * (long dec[], see decode.c) for the profiler / instruction group statistics. */
#include <string.h>
#include "sim56000.h"

/* the record for L: move operand pairs lives in static nodes (0x4dbdd8..0x4dbe6c in the original) */
static struct stat_link node_a, node_b;
static struct stat_op ops_a[2], ops_b[2];

void copy_operand4(long *dst, long *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
}

void insn_stat_classify(void *vstat, long *dec)
{
    struct insn_stat *stat = (struct insn_stat *)vstat;
    unsigned long w = (unsigned long)dec[0x2e] & MASK32, m;
    unsigned long f, d;

    stat->cat = dec[0];
    stat->aux = dec[0x2a];
    stat->word0 = dec[0x2e];
    stat->word1 = dec[0x2f];
    if ((w & 0xfe4080UL) == 0x84080UL || (w & 0xfe40c0UL) == 0x84040UL || (w & 0xfe40c0UL) == 0x84000UL ||
        (w & 0xff4080UL) == 0x74000UL || (w & 0xff4080UL) == 0x70080UL ||
        (w & 0xff40a0UL) == 0x44080UL || (w & 0xff40a0UL) == 0x44020UL || (w & 0xff8080UL) == 0x8000UL)
        stat->cat = 0x65;
    m = w & 0xff40a0UL;
    if ((w & 0xff00a0UL) == 0x500a0UL || m == 0x54020UL || m == 0x50020UL || m == 0x440a0UL)
        stat->cat = 99;
    if ((w & 0xff4080UL) == 0x74080UL || (w & 0xff4080UL) == 0x70000UL)
        stat->cat = 100;
    f = (unsigned long)stat->flags & MASK32;
    if (dec[1] == 0xd)
        f |= 8;
    else if (dec[1] == 0xe)
        f |= 0x10;
    if (dec[0x2c] == -1)
        f |= 0x20;
    d = (unsigned long)dec[0x2b] & MASK32;
    if (d & 4) f |= 0x40;
    if (d & 8) f |= 0x80;
    if (d & 0x100) f |= 0x400;
    if (d & 0x20) f |= 0x200;
    if (d & 0x80) f |= 0x100;
    if (d & 0x40) f |= 4;
    if (stat->cat == 0x27 || stat->cat == 0x29)
        f |= 2;
    stat->flags = (long)f;
}

/* copy the operands (and the L: move operand pairs) of a decoded instruction into the record */
void insn_stat_operands(void *vstat, long *dec)
{
    struct insn_stat *stat = (struct insn_stat *)vstat;
    long i, last = 0, any;
    struct stat_op *dst;

    for (i = 0; i < 4; i++) {
        copy_operand4(stat->op[i].w, dec + 2 + 5 * i);
        if (dec[2 + 5 * i] != 0)
            last = i + 1;
    }
    if ((dec[0x2b] & 0x80) == 0) {
        dst = stat->op + last;
        for (i = 0; i < 4; i++) {
            if (dec[22 + 5 * i] != 0) {
                if (dst < stat->op + 4)      /* (the original would run into the link field) */
                    copy_operand4(dst->w, dec + 22 + 5 * i);
                dst++;
            }
        }
    } else {
        any = dec[22] != 0 || dec[27] != 0 || dec[32] != 0 || dec[37] != 0;
        if (any) {
            if (stat->cat == 0x28) {
                copy_operand4(stat->op[2].w, dec + 22);
                copy_operand4(stat->op[3].w, dec + 27);
            } else {
                memset(&node_a, 0, sizeof node_a);
                memset(&node_b, 0, sizeof node_b);
                memset(ops_a, 0, sizeof ops_a);
                memset(ops_b, 0, sizeof ops_b);
                stat->link = &node_a;
                node_a.ops = ops_a;
                copy_operand4(ops_a[0].w, dec + 22);
                copy_operand4(ops_a[1].w, dec + 27);
                if (dec[32] != 0) {
                    node_a.next = &node_b;
                    node_b.ops = ops_b;
                    copy_operand4(ops_b[0].w, dec + 32);
                    copy_operand4(ops_b[1].w, dec + 37);
                }
            }
        }
    }
    switch (stat->cat) {
    case 8:
        stat->op[1].w[2]++;
        break;
    case 9:
        stat->op[0].w[2]++;
        break;
    case 10:
        stat->op[1].w[0] = 0xe;
        stat->op[1].w[2]++;
        break;
    case 0xb:
        stat->op[0].w[2]++;
        stat->op[0].w[0] = 0xe;
        break;
    case 0x16:
        if (stat->op[0].w[0] == 10)
            stat->op[0].w[0] = 0xe;
        break;
    case 0x2b:
    case 0x2c:
        if (stat->op[0].w[0] == 9)
            stat->op[0].w[0] = 0xe;
        break;
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
        stat->op[2].w[0] = 0xe;
        break;
    default:
        break;
    }
}

/* evaluate condition code cc (0..15: cc ge ne pl nn ec lc gt cs lt eq mi nr es ls le) on a CCR value */
unsigned long eval_cc(unsigned long ccr, long cc)
{
    ccr &= MASK32;
    switch (cc) {
    case 0: return ~ccr & 1;
    case 1:
        if ((ccr & 8) == 0 && (ccr & 2) == 0) return 1;
        if ((ccr & 8) != 0 && (ccr & 2) != 0) return 1;
        break;
    case 2: return (~ccr >> 2) & 1;
    case 3: return (~ccr >> 3) & 1;
    case 4:
        if ((ccr & 4) == 0 && (ccr & 0x30) != 0) return 1;
        break;
    case 5: return (~ccr >> 5) & 1;
    case 6: return (~ccr >> 6) & 1;
    case 7:
        if ((ccr & 4) != 0) return 0;
        if ((ccr & 2) == 0 && (ccr & 8) == 0) return 1;
        if ((ccr & 2) != 0 && (ccr & 8) != 0) return 1;
        break;
    case 8: return ccr & 1;
    case 9:
        if ((ccr & 2) == 0 && (ccr & 8) != 0) return 1;
        if ((ccr & 2) != 0 && (ccr & 8) == 0) return 1;
        break;
    case 10: return (ccr >> 2) & 1;
    case 0xb: return (ccr >> 3) & 1;
    case 0xc:
        if ((ccr & 4) != 0) return 1;
        if ((ccr & 0x30) == 0) return 1;
        return 0;
    case 0xd: return (ccr >> 5) & 1;
    case 0xe: return (ccr >> 6) & 1;
    case 0xf:
        if ((ccr & 4) != 0) return 1;
        if ((ccr & 2) == 0 && (ccr & 8) != 0) return 1;
        if ((ccr & 2) != 0 && (ccr & 8) == 0) return 1;
        break;
    default:
        return 1;
    }
    return 0;
}

char *mnemonic_name(long id)
{
    if (mnemonic_names[0][0] == 'n')
        mnemonic_names[0] = "move";
    if (id < 0x5f)
        return (char *)mnemonic_names[id];
    if (id < 0x66)
        return (char *)mnemonic_names[id + 1];
    return NULL;
}

long operand_is_xy_pair(long *a, long *b)
{
    if (a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == 1 && b[3] == 2)
        return 0;
    return 1;
}

/* class of an L: move pair (2 X/Y moves into a register pair) */
long stat_lmove_class(void *vstat, long *class_out, long *flag)
{
    struct insn_stat *stat = (struct insn_stat *)vstat;
    long *a, *b;
    long v1;
    unsigned long v2, code;

    if (stat->link == NULL || stat->link->next == NULL)
        return 1;
    b = stat->link->next->ops->w;
    a = stat->link->ops->w;
    if (operand_is_xy_pair(a, b) == 0) {
        *flag = 0;
        v1 = a[8];
        v2 = (unsigned long)b[8];
    } else {
        if (operand_is_xy_pair(a + 7, b + 7) != 0)
            return 1;
        *flag = 1;
        v1 = a[1];
        v2 = (unsigned long)b[1];
    }
    code = (((unsigned long)v1 << 16) | v2) & MASK32;
    if (code < 0x350035UL) {
        if (code == 0x350034UL) {
            *class_out = 0x54;
            return 0;
        }
        if (code == 0x320031UL) {
            *class_out = 0x53;
            return 0;
        }
    } else if (code == 0x59005bUL)
        *class_out = 0x4e;
    else if (code == 0x5a005cUL) {
        *class_out = 0x4f;
        return 0;
    }
    return 0;
}
