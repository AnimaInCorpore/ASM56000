/* exprprim.c - expression evaluator: primary expressions
 * (SIM56000.EXE 6.3.0, module expr, parse_primary 0x459a70-0x45a7b0).
 * A primary is a sign/complement/paren form, a "space:address" memory reference, a register,
 * a symbol (with optional +/- offset), '*' (current value), or a constant in binary (%),
 * hex ($), decimal (`) or, by default radix, plain digits or a float.  The control flow of the
 * original (one big function with shared exits) is kept, using labels. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sim56000.h"

typedef long (*mem_read_fn)(long space, unsigned long addr, unsigned long *out);
typedef long (*peek_fn)(long grp, long reg, unsigned long *out);

static int is_alpha(int c) { return isalpha((unsigned char)c) != 0; }
static int is_alnum(int c) { return isalnum((unsigned char)c) != 0; }

void *parse_primary(void)
{
    struct val *value, *node;
    char c1, c, *p17, *p18, *p19, saved;
    unsigned long sign, wmask, wbits, emask, attr, mask, addr, digits, t, hi4, sh;
    long radix, len, i, j, found, grp, reg, sp;
    unsigned long buf[2];
    struct group_def *def;
    struct mem_region *map;

    while (*optr == ' ' || *optr == '\t')
        optr++;
    c1 = *optr;
    if (c1 == '+') {
        optr++;
        return parse_primary();
    }
    if (c1 == '-') {
        optr++;
        node = (struct val *)parse_primary();
        if (node == NULL)
            return NULL;
        if ((expr_mode & 0x80) != 0)
            node_neg32(node);
        else
            node_neg(node);
        return node;
    }
    if (c1 == '~') {
        optr++;
        node = (struct val *)parse_primary();
        if (node == NULL)
            return NULL;
        if ((expr_mode & 0x80) == 0) {
            if (node_not(node) != 0)
                return node;
            node_free(node);
            return NULL;
        }
        node_not32(node);
        return node;
    }
    if (c1 == '!') {
        optr++;
        node = (struct val *)parse_primary();
        if (node == NULL)
            return NULL;
        if ((expr_mode & 0x80) != 0)
            node_lnot32(node);
        else
            node_lnot(node);
        return node;
    }
    if (c1 == '(') {
        optr++;
        node = (struct val *)parse_expr();
        if (node == NULL)
            return NULL;
        if (*optr != ')') {
            node_free(node);
            expr_error("Missing ')' in expression");
            return NULL;
        }
        optr++;
        return node;
    }

    /* word size of the device */
    if ((expr_mode & 0x10000000UL) == 0) {
        if ((expr_mode & 0x4000000UL) == 0) {
            sign = 0x80000000UL; wmask = MASK32; wbits = 0x20;
        } else {
            sign = 0x800000UL; wmask = 0xffffffUL; wbits = 0x18;
        }
        emask = 0xff;
    } else {
        sign = 0x8000UL; wmask = 0xffffUL; wbits = 0x10;
        emask = (expr_mode & 0x1000000UL) != 0 ? 0x0fUL : 0xffUL;
    }

    /* "space:address" - a memory space name of up to 4 characters followed by ':' */
    p17 = optr + 1;
    if (optr[1] == ':')
        goto space;
    if (optr[1] != '\0') {
        p17 = optr + 2;
        if (optr[2] == ':')
            goto space;
        if (optr[2] != '\0') {
            p17 = optr + 3;
            if (optr[3] == ':')
                goto space;
            if (optr[3] != '\0') {
                p17 = optr + 4;
                if (optr[4] == ':')
                    goto space;
            }
        }
    }
    goto after_space;

space:
    *p17 = '\0';
    map = cur_dtype->map;
    for (j = 0; j < cur_dtype->n_map; j++) {
        if (stricmp_ci2(optr, (char *)map[j].name) != 0)
            continue;
        attr = map[j].f24 & 0xff400003UL;
        mask = (unsigned long)map[j].size_m1;
        if ((expr_mode & 0x800) != 0)
            mask &= 0xffffUL;
        *p17 = ':';
        optr = p17 + 1;
        node = (struct val *)parse_primary();
        if (node == NULL)
            return NULL;
        addr = node->lo;
        node->idx = j;
        if ((expr_mode & 0x10000000UL) == 0) {
            if ((expr_mode & 0x4000000UL) != 0)
                addr |= (node->hi << 24) & MASK32;
        } else
            addr |= (node->hi << 16) & MASK32;
        addr &= mask;
        buf[0] = buf[1] = 0;
        ((mem_read_fn)cur_dtype->vtable->mem_read)(map[j].space, addr, buf);   /* slot 11 is NULL */
        node->lo = buf[0];
        node->hi = buf[1];
        node->addr = addr;
        node->flags = attr | 0x4100UL;
        node->id = (unsigned long)map[j].space;
        if (mem_addr_check(j, addr) != 2)
            return node;
        if ((node->flags & 2) != 0 && (expr_mode & 0x1000) != 0) {
            node->lo = ((node->lo & 0xffffUL) | (node->hi << 16)) & MASK32;
            node->hi >>= 8;
        }
        node->d = node_get_double(expr_mode, node);
        node->flags = attr | 0x4200UL;
        return node;
    }
    *p17 = ':';

after_space:
    value = (struct val *)dsp_alloc(sizeof(struct val), 1);
    if (value == NULL)
        return NULL;
    value->flags = 0x101;
    p17 = optr;
    found = 0;                         /* set when a "reg:" prefix was seen */
    if ((expr_mode & 0x10000) == 0) {
        if ((optr[0] == 'r' || optr[0] == 'R') && (optr[1] == 'e' || optr[1] == 'E') &&
            (optr[2] == 'g' || optr[2] == 'G') && optr[3] == ':') {
            optr += 4;
            found = 1;
        }
        p17 = optr;
        if (is_alpha(*optr) || *optr == '_') {
            len = 0;
            for (;;) {
                c = p17[len];
                if (c != '_' && c != '.' && !is_alnum(c))
                    break;
                len++;
            }
            if (len > 0) {
                p17[len] = '\0';
                sp = periph_find_reg(cur_dev->number, optr, &grp, &reg);
                p17[len] = c;
                if (sp != 0) {
                    def = cur_dtype->periph[grp].def;
                    buf[0] = buf[1] = 0;
                    ((peek_fn)def->peek)(grp, reg, buf);
                    value->lo = buf[0];
                    value->hi = buf[1];
                    t = def->regs[reg].flags;
                    attr = t & 0xfffc0007UL;
                    if ((expr_mode & 0x14000000UL) != 0 && (t & 1) != 0 && (t & 0x2000000UL) != 0) {
                        attr = 0x2000002UL;
                        node_normalize(value);
                    }
                    value->flags = (attr & 0xffff0000UL) | 0x100UL | (attr & 0xffUL);
                    t = cur_sim->regflags[grp].flags[reg];
                    if ((t & 0x2000000UL) == 0) {
                        if ((t & 0x2000) != 0) {
                            node_get_double(expr_mode, value);
                            value->flags |= 0x200UL;
                        }
                    } else
                        value->flags |= 0x2000UL;
                    optr += len;
                    return value;
                }
            }
            p17 = optr;
        }
        if (found) {
            node_free(value);
            expr_error("Invalid register name");
            return NULL;
        }
    }

    /* symbols: after '@', or when debug symbols are loaded */
    p18 = p17;
    if (*p17 == '@') {
        p18 = p17 + 1;
        goto scan_symbol;
    }
    if (cur_sim->dbg != NULL && cur_sim->dbg->nsyms != 0) {
        if (is_alpha(*p18) || *p18 == '_')
            goto scan_symbol;
    }
    goto numbers;

scan_symbol:
    i = 0;
    for (;;) {
        c = p18[i];
        if (c != '_' && !is_alnum(c) && (c != '.' || p18[i + 1] == '.'))
            break;
        i++;
    }
    if (c == '@') {
        do {
            do {
                c = p18[i + 1];
                i++;
            } while (c == '_');
        } while (is_alnum(c));
    }
    if (i <= 0)
        goto numbers;
    p19 = p18 + i;
    saved = *p19;
    *p19 = '\0';
    found = dbg_resolve_symbol(p18, value) != 0;
    if (!found) {
        unsigned long line;

        found = dbg_parse_file_line(p18, value, &line) != 0;
    }
    *p19 = saved;
    p17 = optr;
    if (!found)
        goto numbers;
    if (value->id == 4) {
        value->lo = value->addr;
        if ((value->lo & sign) != 0)
            value->lo = (~wmask | value->lo) & MASK32;
        value->flags = (expr_mode & 0x16100000UL) | 0x101UL;
        optr = p19;
        return value;
    }
    j = memmap_find((long)value->id, value->addr);
    value->idx = j;
    attr = cur_dtype->map[j].f24 & 0xff400003UL;
    mask = ~(unsigned long)cur_dtype->map[j].size_m1 & MASK32;
    optr = p19;
    if (saved == '+' || saved == '-') {
        optr = p19 + 1;
        node = (struct val *)parse_primary();
        if (node == NULL) {
            node_free(value);
            expr_error("Address offset expected");
            return NULL;
        }
        if (saved == '+')
            value->addr = (value->addr + node->lo) & MASK32;
        else
            value->addr = (value->addr - node->lo) & MASK32;
        node_free(node);
    }
    addr = value->addr;
    t = mask & addr;
    if (t != 0 && t != mask) {
        node_free(value);
        expr_error("Address too large");
        return NULL;
    }
    value->lo = addr;
    value->flags = (attr & 0xffff0000UL) | 0x4100UL | (attr & 0xffUL);
    if (mem_addr_check(j, addr) != 2)
        return value;
    if ((value->flags & 2) != 0 && (expr_mode & 0x1000) != 0) {
        value->lo = ((value->lo & 0xffffUL) | (value->hi << 16)) & MASK32;
        value->hi >>= 8;
    }
    value->d = node_get_double(expr_mode, value);
    value->flags = attr | 0x4200UL;
    return value;

numbers:
    c = *p17;
    digits = 0;
    if (c == '*') {
        optr = p17 + 1;
        value->lo = (unsigned long)cur_sim->version_word & MASK32;
        return value;
    }
    radix = cur_sim->default_radix;
    p18 = p17;
    if (c1 == '%' || radix == 0) {
        if (c1 == '%') {
            p18 = p17 + 1;
            optr = p18;
        }
        c = *p18;
        if (c != '0' && c != '1')
            goto not_binary;
        while (*p18 == '0' || *p18 == '1') {
            t = value->ext;
            digits++;
            value->ext = (t << 1) & MASK32;
            if ((value->hi & sign) != 0)
                value->ext = ((t << 1) | 1) & MASK32;
            t = (value->hi * 2) & MASK32;
            value->hi = t;
            if ((value->lo & sign) != 0)
                value->hi = t | 1;
            value->lo = ((unsigned long)(*optr - '0') + value->lo * 2) & MASK32;
            p18 = ++optr;
        }
        if (*p18 == '.' && c1 != '%')
            goto make_float;
        if (digits == 0) {
            node_free(value);
            expr_error("Binary constant expected");
            return NULL;
        }
        goto classify;
    }

not_binary:
    if (c1 == '$') {
        p18 = p18 + 1;
        optr = p18;
        goto hex;
    }
    if (radix == 3)
        goto hex;
    goto after_hex;

hex:
    sh = wbits - 4;
    p19 = p18;                         /* start of the digits */
    j = str_index1(*p18, "0123456789abcdefABCDEF");
    p18 = optr;
    while (j != 0) {
        if (j > 0x10)
            j -= 6;
        digits += 4;
        hi4 = (value->hi << 4) & MASK32;
        value->ext = (((value->hi >> sh) & 0xf) | (value->ext << 4)) & MASK32;
        value->hi = (((value->lo >> sh) & 0xf) | hi4) & MASK32;
        value->lo = ((unsigned long)(j - 1) | (value->lo << 4)) & MASK32;
        optr++;
        j = str_index1(*optr, "0123456789abcdefABCDEF");
        p18 = optr;
    }
    c = *p18;
    if (c == '.' && c1 != '$') {
        p17 = p19;
        goto make_float;
    }
    if (digits != 0)
        goto classify;
    if (c1 != '`') {
        node_free(value);
        expr_error("Hex constant expected");
        return NULL;
    }

after_hex:
    if (c1 == '`') {
        p18 = p18 + 1;
        optr = p18;
        goto decimal;
    }
    if (radix == 1 || radix == 2 || radix == 4)
        goto decimal;
    goto not_number;

decimal:
    c = *p18;
    if (c > '/' && c < ':') {
        unsigned long spill = 0, e0;

        p19 = p18;
        do {
            if (c > '9')
                break;
            spill = (spill * 10) & MASK32;
            value->lo = ((unsigned long)(c - '0') + value->lo * 10) & MASK32;
            optr++;
            e0 = value->ext;
            t = (value->lo);
            value->hi = (value->hi * 10) & MASK32;
            value->ext = (e0 * 10) & MASK32;
            if (t > 0xfffffffUL) {
                value->hi = ((t >> 28) + value->hi) & MASK32;
                value->lo = t & 0xfffffffUL;
            }
            t = value->hi;
            if (t > 0xfffffffUL) {
                value->ext = ((t >> 28) + e0 * 10) & MASK32;
                value->hi = t & 0xfffffffUL;
            }
            t = value->ext;
            if (t > 0xfffffffUL) {
                spill = (spill + (t >> 28)) & MASK32;
                value->ext = t & 0xfffffffUL;
            }
            c = *optr;
            p19 = optr;
        } while (c > '/');
        p17 = p18;
        if (*p19 == '.' || *p19 == 'e')
            goto make_float;
        /* repack the base-2^28 limbs (lo, hi, ext, spill) into the device's word layout */
        if ((expr_mode & 0x10000000UL) == 0) {
            t = value->hi;
            if ((expr_mode & 0x4000000UL) == 0) {
                value->lo = (value->lo | (t << 28)) & MASK32;
                value->hi = ((value->ext << 24) | (t >> 4)) & MASK32;
                value->ext = ((spill << 20) | (value->ext >> 8)) & MASK32;
            } else {
                value->ext = (t >> 20) & emask;
                value->hi = (((t & 0xfffffUL) << 4) | ((value->lo >> 24) & 0xf)) & MASK32;
                value->lo &= 0xffffffUL;
            }
        } else {
            value->ext = (value->hi >> 4) & emask;
            value->hi = (((value->lo >> 16) & 0xfff) | ((value->hi & 0xf) << 12)) & MASK32;
            value->lo &= 0xffffUL;
        }
        if (value->ext == 0) {
            if (value->hi == 0)
                return value;
            value->flags = (value->flags & ~5UL) | 2UL;
            return value;
        }
        value->flags = (value->flags & ~3UL) | 4UL;
        return value;
    }

not_number:
    c = *p18;
    if (c != '.' || str_index1(p18[1], "0123456789") == 0) {
        node_free(value);
        expr_error("Invalid expression");
        return NULL;
    }
    p17 = optr;

make_float:
    optr = p17;
    parse_float(value);
    value->flags = 0x204UL;
    return value;

classify:
    if (digits <= wbits)
        return value;
    if (wbits < digits - wbits)
        value->flags = (value->flags & ~3UL) | 4UL;
    else
        value->flags = (value->flags & ~5UL) | 2UL;
    value->lo &= wmask;
    value->hi &= wmask;
    return value;
}
