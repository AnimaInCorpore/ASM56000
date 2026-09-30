/* asm.c - inline assembler / disassembler support
 * (SIM56000.EXE 6.3.0, module asm 0x4240d0-0x42c4c0; this file so far: the disassembler helpers
 * at the start of the module).
 * Token lists: the disassembler builds an instruction as a list of token ids (see dis_token_strings,
 * 0x99 "," 0x9a " "), with negative pseudo tokens for numbers taken from the dis_hex_* buffers. */
#include <stdio.h>
#include <string.h>
#include "sim56000.h"

unsigned long dis_effect_flags = 0;
unsigned long dis_sel_a = 0, dis_sel_b = 0, dis_sel_c = 0, dis_sel_d = 0, dis_sel_e = 0;
unsigned long dis_val_b = 0, dis_val_c = 0, dis_val_a = 0, dis_val_d = 0, dis_val_e = 0;
char dis_hex_ea[16], dis_hex_b[16], dis_hex_c[16];
long dis_cpu_level = 0;

/* token id per address mode of an effective address field (0x4c09d8..), part of dis_token_strings' tail in the data dump */
static const long ea_tok_tab[65] = {
    34, 60, 5, 61, 50, 15, 57, 16,
    3, 47, 4, 14, 55, 63, 56, 42,
    3, 2, 9, 30, 55, 52, 1, 49,
    3, 2, 8, 29, 55, 52, 39, 48,
    3, 60, 43, 20, 55, 15, 6, 16,
    3, 60, 43, 20, 55, 15, 6, 16,
    3, 60, 43, 20, 55, 15, 6, 16,
    3, 60, 43, 20, 55, 15, 6, 16,
    63,
};

/* reverse the 16 low bits */
void bitrev16(unsigned long v, unsigned long *out)
{
    unsigned long src = 0x8000UL, dst = 1, r = 0;
    int i;

    for (i = 0; i < 16; i++) {
        if ((v & src) != 0)
            r |= dst;
        dst <<= 1;
        src >>= 1;
    }
    *out = r;
}

void dis_reset(void)
{
    dis_sel_e = dis_sel_d = dis_sel_c = dis_sel_b = dis_sel_a = 0;
    dis_effect_flags = 0;
}

void hid_424130(unsigned long *insn, char *text, long a3, long a4, void *info)
{
    dis_cpu_level = 4;
    disassemble(insn, text, a3, a4, info);
}

void disassemble_l1(unsigned long *insn, char *text, long a3, long a4, void *info)
{
    dis_cpu_level = 1;
    disassemble(insn, text, a3, a4, info);
}

/* find needle in hay (first character via strchr, then strncmp); returns the needle length or 0 */
unsigned long str_find_token(char *hay, char *needle, char **pos)
{
    size_t len = strlen(needle);
    char *p = strchr(hay, needle[0]);

    if (p == NULL)
        return 0;
    do {
        if (strncmp(needle, p, len) == 0) {
            *pos = p;
            return (unsigned long)len;
        }
        p = strchr(p + 1, needle[0]);
    } while (p != NULL);
    return 0;
}

void fmt_hex_dollar(unsigned long v, char *out)
{
    sprintf(out, "$%lx", v & MASK32);
}

void fmt_hex24(unsigned long v, char *out)
{
    sprintf(out, "%lx", v & 0xffffffUL);
}

/* tokens of an effective address (parallel move field): "(rN)+nN" etc.; returns the token count */
long dis_ea_tokens(unsigned long opw, long *tok)
{
    unsigned long b = opw & 0xff, u8 = (b >> 4) & 7;
    long i2, i7, i9, t;
    long *p, *q;
    int first;

    if ((b >> 7) == 0) {
        if (b == 0xc || b == 4 || b == 8)
            i2 = 0x40;
        else
            i2 = (long)((opw & 7) + u8 * 8);
        t = ea_tok_tab[i2];
        i7 = d_4c0af0[b];
        i9 = 0;
        if (d_4c10f0[i2] != 0)
            i2 = ((b >> 3) & 1) != 0 ? 0xc : 0xb;
        else
            i2 = 0;
    } else {
        t = d_4c0ae0[opw & 3];
        i9 = d_4c1248[u8];
        i7 = d_4c1208[(((opw & 7) & 4) << 1) | u8];
        i2 = ((b >> 3) & 1) != 0 ? 0xc : 0xb;
    }
    tok[0] = t;
    first = 0;
    p = tok + 1;
    if (i7 != 0) {
        *p = 0x9a;
        first = 1;
        tok[2] = i7 + 0x57;
        p = tok + 3;
        if (i9 != 0 || i2 != 0) {
            *p = 0x99;
            p = tok + 4;
        }
    }
    if (i9 != 0) {
        q = p;
        if (!first) {
            *p = 0x9a;
            first = 1;
            q = p + 1;
        }
        *q = i9 + 0x57;
        p = q + 1;
        if (i2 == 0)
            goto done;
        *p = 0x99;
        p = q + 2;
    }
    if (i2 != 0) {
        if (!first) {
            *p = 0x9a;
            p++;
        }
        *p = i2 + 0x57;
        p++;
    }
done:
    *p = 0x9a;
    return (long)(p - tok) + 1;
}
