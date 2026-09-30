/* disasm.c - disassembler driver: token list -> text, effective address calculation for the display
 * (SIM56000.EXE 6.3.0, module disasm 0x423b10-0x4240d0). */
#include <string.h>
#include "sim56000.h"

/* text of an instruction (word 0 = insn[0], extension/pc word = insn[1]); returns the number of words
 * (2 when a $address token was used, 0 for "dc <word>" of an undefined opcode) */
long disassemble(unsigned long *insn, char *text, long a3, long a4, void *vinfo)
{
    struct dis_info *info = (struct dis_info *)vinfo;
    const char * const *names = (const char * const *)dis_token_strings;
    char buf[100];
    long tok[30];
    long n, cls, i, id, words = 1;
    unsigned long v;
    char *pos;
    const char *s;

    dis_reset();
    buf[0] = '\0';
    cls = opclass_lookup(insn[0], (unsigned long)dis_cpu_level);
    n = ((long (*)(unsigned long, long *))dis_fmt_handlers[cls])(insn[0], tok);
    for (i = 0; i < n; i++) {
        id = tok[i];
        if (id == 0)
            continue;
        if (id == -2)
            s = dis_hex_ea;
        else if (id == -3)
            s = dis_hex_b;
        else if (id == -4 || id == -5) {
            v = id == -4 ? insn[1] : (insn[1] + 1) & 0xffffUL;
            fmt_hex24(v, dis_hex_c);
            strcat(buf, "$");
            strcat(buf, dis_hex_c);
            words = 2;
            continue;
        } else
            s = names[id];
        strcat(buf, s);
    }
    if (str_find_token(buf, "U", &pos) != 0) {          /* undefined opcode */
        strcpy(buf, "dc ");
        fmt_hex24(insn[0], dis_hex_c);
        strcat(buf, "$");
        strcat(buf, dis_hex_c);
        words = 0;
    }
    strcpy(text, buf);
    if (info != NULL) {
        info->nwords = words;
        dis_move_addrs(info, insn[1]);
    }
    return words;
}

/* compute the addresses touched by the instruction's moves */
void dis_move_addrs(void *vinfo, unsigned long pc)
{
    struct dis_info *info = (struct dis_info *)vinfo;

    info->flags = dis_effect_flags;
    if ((dis_effect_flags & 2) != 0)
        dis_ea_addr(info, pc, dis_sel_b, dis_val_b, &info->ea_b);
    if ((dis_effect_flags & 4) != 0)
        dis_ea_addr(info, pc, dis_sel_c, dis_val_c, &info->ea_c);
    if ((dis_effect_flags & 1) != 0)
        dis_ea_addr(info, pc, dis_sel_a, dis_val_a, &info->ea_a);
    if ((dis_effect_flags & 8) != 0)
        dis_ea_addr(info, pc, dis_sel_b, dis_val_b, &info->ea_b);
    if ((dis_effect_flags & 0x20) != 0)
        dis_ea_addr(info, pc, dis_sel_d, dis_val_d, &info->ea_c);
    if ((dis_effect_flags & 0x10) != 0)
        dis_ea_addr(info, pc, dis_sel_e, dis_val_e, &info->ea_b);
}

/* effective address selected by sel (register/mode bits) with the AGU registers in info */
void dis_ea_addr(void *vinfo, unsigned long pc, unsigned long sel, unsigned long defval, unsigned long *out)
{
    struct dis_info *info = (struct dis_info *)vinfo;
    unsigned long u = sel & 7, rn = info->rn[u], nn = info->nn[u], mn = info->mn[u], u1;

    *out = defval;
    if (sel == 0x100)
        return;
    if (sel == 0x2000) {
        *out = pc;
        return;
    }
    if (sel == 0x4000) {
        *out = pc + 1;
        return;
    }
    if ((sel & 0x8000UL) == 0) {
        if ((sel & 0x10000UL) != 0) {
            u1 = (sel >> 3) & 3;
            if (u1 != 1)
                nn = 1;
            if (u1 != 0 && u1 != 2) {
                dis_agu_addr(rn, nn, mn, 0, out);
                return;
            }
            dis_agu_addr(rn, nn, mn, 1, out);
        }
    } else {
        u1 = sel & 0x3c;
        if (u1 == 0x30 || u1 == 0x34) {
            *out = pc;
            return;
        }
        u1 >>= 3;
        if (u1 < 5) {
            *out = rn;
            return;
        }
        if (u1 == 5) {
            dis_agu_addr(rn, nn, mn, 0, out);
            return;
        }
        if (u1 == 7)
            dis_agu_addr(rn, 1, mn, 1, out);
    }
}

/* rn + nn (or rn - nn) with the modifier register's modulo / bit-reverse addressing */
void dis_agu_addr(unsigned long rn, unsigned long nn, unsigned long mn, long negate, unsigned long *out)
{
    unsigned long v = nn, u2, u3, u4, u5, tmp;
    long neg = negate;
    int wrap;

    if (negate != 0)
        v = nn ^ 0xffffUL;
    wrap = (mn & 0xc000UL) == 0x8000UL && dis_cpu_level > 3;
    if ((mn & 0x8000UL) != 0 && !wrap) {
        *out = (v + (unsigned long)neg + rn) & 0xffffUL;
        return;
    }
    if (mn == 0) {                     /* bit reverse addressing */
        bitrev16(rn, &rn);
        bitrev16(v, &nn);
        bitrev16(nn + rn + (unsigned long)neg, &tmp);
        *out = tmp;
        return;
    }
    u3 = 0x4000;
    u2 = mn & 0x4000UL;
    while (u2 == 0) {
        u3 >>= 1;
        u2 = mn & u3;
    }
    u2 = (v + (unsigned long)neg + rn) & 0xffffUL;
    if (!wrap) {
        u3 = u3 * 2 - 1;
        wrap = (u3 & v) + (unsigned long)neg + (u3 & rn) <= u3;
        u5 = (v >> 15) & 1;
        if (u5 == 0)
            mn ^= 0xffffUL;
        u4 = (u2 + u5 + mn) & 0xffffUL;
        if (u5 == 0) {
            if (u3 < (u3 & mn) + (u3 & u2) || !wrap)
                u2 = u4;
            *out = u2;
            return;
        }
        if (wrap)
            u2 = u4;
        *out = u2;
        return;
    }
    *out = ((u2 & mn & 0x7fffUL) | (~(mn & 0x7fffUL) & rn)) & MASK32;
}
