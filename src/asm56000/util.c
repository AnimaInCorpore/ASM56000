/*
 * ASM56000 assembler utility layer: allocation, bit fields, and relocation
 * expression construction.
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "asm56000.h"

extern void fatal(char *msg);

static char LowerBuf[24];
static char UpperBuf[32];

static unsigned long field_mask(int width)
{
    if (width <= 0)
        return 0UL;
    if (width >= 32)
        return 0xffffffffUL;
    return (1UL << width) - 1UL;
}

void *xmalloc(unsigned long size)
{
    void *p;

    p = malloc(size);
    if (p == (void *)0) {
        fatal("Out of memory - assembly aborted");
        return (void *)0;
    }
    return p;
}

void *xrealloc(void *p, unsigned long size)
{
    void *q;

    q = realloc(p, size);
    if (q == (void *)0) {
        fatal("Out of memory - assembly aborted");
        return (void *)0;
    }
    return q;
}

void xfree(void *p)
{
    if (p != (void *)0)
        free(p);
}

char *str_dupcat(char *s, ...)
{
    va_list ap;
    char *part;
    char *out;
    unsigned long length;
    unsigned long add;

    if (s == (char *)0)
        s = "";
    length = (unsigned long)strlen(s);
    out = (char *)xmalloc(length + 1UL);
    strcpy(out, s);

    va_start(ap, s);
    for (;;) {
        part = va_arg(ap, char *);
        if (part == (char *)0)
            break;
        add = (unsigned long)strlen(part);
        out = (char *)xrealloc(out, length + add + 1UL);
        strcpy(out + length, part);
        length += add;
    }
    va_end(ap);
    return out;
}

void *tab_search(void *key, void *base, int count, int size,
                 int (*cmp)(void *, void *))
{
    int lo;
    int hi;
    int mid;
    char *entry;
    int order;

    if (base == (void *)0 || count <= 0 || size <= 0 || cmp == 0)
        return (void *)0;
    lo = 0;
    hi = count - 1;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        entry = (char *)base + (unsigned long)mid * (unsigned long)size;
        order = (*cmp)(key, (void *)entry);
        if (order == 0)
            return (void *)entry;
        if (order < 0)
            hi = mid - 1;
        else
            lo = mid + 1;
    }
    return (void *)0;
}

void *tab_search_pos(void *key, void *base, int count, int size,
                     int (*cmp)(void *, void *))
{
    int lo;
    int hi;
    int mid;
    int order;
    char *entry;

    if (base == (void *)0 || size <= 0 || cmp == 0)
        return (void *)0;
    if (count < 0)
        count = 0;
    lo = 0;
    hi = count;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        entry = (char *)base + (unsigned long)mid * (unsigned long)size;
        order = (*cmp)(key, (void *)entry);
        if (order <= 0)
            hi = mid;
        else
            lo = mid + 1;
    }
    return (void *)((char *)base + (unsigned long)lo * (unsigned long)size);
}

unsigned long hash_name(char *s)
{
    unsigned long h;
    unsigned long g;
    signed char ch;

    h = 0UL;
    if (s == (char *)0)
        return 0UL;
    while (*s != '\0') {
        ch = (signed char)*s++;
        h = ((h << 4) + (long)ch) & 0xffffffffUL;
        g = h & 0xf0000000UL;
        if (g != 0UL)
            h = (h ^ (g >> 24) ^ g) & 0xffffffffUL;
    }
    return h % 1009UL;
}

char *base_name(char *path)
{
    char *p;

    if (path == (char *)0)
        return (char *)0;
    p = path + strlen(path);
    while (p != path) {
        --p;
        if (*p == '\\' || *p == '/' || *p == ':')
            return p + 1;
    }
    return path;
}

char *str_lower_copy(char *s)
{
    unsigned long i;
    int c;

    if (s == (char *)0) {
        LowerBuf[0] = '\0';
        return LowerBuf;
    }
    i = 0UL;
    while (s[i] != '\0' && i + 1UL < sizeof(LowerBuf)) {
        c = (unsigned char)s[i];
        if (c >= 'A' && c <= 'Z')
            c += 'a' - 'A';
        LowerBuf[i] = (char)c;
        ++i;
    }
    LowerBuf[i] = '\0';
    return LowerBuf;
}

char *str_upper(char *s)
{
    unsigned long i;
    int c;

    if (s == (char *)0)
        return s;
    for (i = 0UL; s[i] != '\0'; ++i) {
        c = (unsigned char)s[i];
        if (c >= 'a' && c <= 'z')
            s[i] = (char)(c - ('a' - 'A'));
    }
    return s;
}

char *str_lower(char *s)
{
    unsigned long i;
    int c;

    if (s == (char *)0)
        return s;
    for (i = 0UL; s[i] != '\0'; ++i) {
        c = (unsigned char)s[i];
        if (c >= 'A' && c <= 'Z')
            s[i] = (char)(c + ('a' - 'A'));
    }
    return s;
}

char *str_upper_copy(char *s)
{
    unsigned long i;
    int c;

    if (s == (char *)0) {
        UpperBuf[0] = '\0';
        return UpperBuf;
    }
    i = 0UL;
    while (s[i] != '\0' && i + 1UL < sizeof(UpperBuf)) {
        c = (unsigned char)s[i];
        if (c >= 'a' && c <= 'z')
            c -= 'a' - 'A';
        UpperBuf[i] = (char)c;
        ++i;
    }
    UpperBuf[i] = '\0';
    return UpperBuf;
}

unsigned long insert_bits(unsigned long word, unsigned long val,
                          int pos, int width)
{
    unsigned long mask;

    word &= 0xffffffffUL;
    val &= 0xffffffffUL;
    if (pos < 0 || pos >= 32 || width <= 0)
        return word;
    if (width > 32 - pos)
        width = 32 - pos;
    mask = field_mask(width);
    return (word & ~(mask << pos)) | ((val & mask) << pos);
}

char *insert_bits_expr(char *word, char *val, int pos, int width)
{
    char local[1024];
    unsigned long n;
    char *dst;

    if (word == (char *)0)
        word = "0";
    if (val == (char *)0)
        val = "0";
    if (pos == 0) {
        sprintf(local, "((%s&(~0<<%d))|(%s&~(~0<<%d)))",
                word, width, val, width);
    } else {
        sprintf(local,
                "((%s&~(~(~0<<%d)<<%d))|((%s&~(~0<<%d))<<%d))",
                word, width, pos, val, width, pos);
    }
    n = (unsigned long)strlen(local);
    dst = (char *)xmalloc(n + 1UL);
    if (dst != (char *)0)
        strcpy(dst, local);
    return dst;
}

void encode_field(void *code, void *op, int pos, int width)
{
    unsigned long word;
    char word_text[32];
    char *expr;
    char **cform;

    cform = (char **)((char *)op + ASM56000_OP_CFORM);
    word = *(unsigned long *)((char *)code + ASM56000_INSN_WORD0);
    if (*cform == (char *)0) {
        word = insert_bits(word,
                           *(unsigned long *)((char *)op + ASM56000_OP_VALUE),
                           pos, width);
        *(unsigned long *)((char *)code + ASM56000_INSN_WORD0) = word;
        return;
    }

    sprintf(word_text, "$%0*lX", 6, word);
    expr = insert_bits_expr(word_text, *cform, pos, width);
    *(char **)((char *)code + ASM56000_INSN_CFORM0) = expr;
    xfree(*cform);
    *cform = (char *)0;
}

unsigned long insert_bits2(unsigned long word, unsigned long val,
                            unsigned long mask1, int shift1, int pos1,
                            int width1, unsigned long mask2, int shift2,
                            int pos2, int width2)
{
    unsigned long f1;
    unsigned long f2;
    unsigned long clear;

    f1 = field_mask(width1);
    f2 = field_mask(width2);
    word &= 0xffffffffUL;
    val &= 0xffffffffUL;
    if (pos1 >= 0 && pos1 < 32 && width1 > 0) {
        if (width1 > 32 - pos1)
            width1 = 32 - pos1;
        f1 = field_mask(width1);
    } else {
        f1 = 0UL;
    }
    if (pos2 >= 0 && pos2 < 32 && width2 > 0) {
        if (width2 > 32 - pos2)
            width2 = 32 - pos2;
        f2 = field_mask(width2);
    } else {
        f2 = 0UL;
    }
    clear = 0UL;
    if (f1 != 0UL)
        clear |= f1 << pos1;
    if (f2 != 0UL)
        clear |= f2 << pos2;
    word &= ~clear;
    if (f1 != 0UL)
        word |= (((val & mask1) >> shift1) & f1) << pos1;
    if (f2 != 0UL)
        word |= (((val & mask2) >> shift2) & f2) << pos2;
    return word;
}

char *insert_bits2_expr(char *word, char *val,
                        unsigned long mask1, int shift1, int pos1,
                        int width1, unsigned long mask2, int shift2,
                        int pos2, int width2)
{
    char local[1024];
    unsigned long n;
    char *dst;

    if (word == (char *)0)
        word = "0";
    if (val == (char *)0)
        val = "0";
    sprintf(local,
            "((%s&~((~(~0<<%d)<<%d)|(~(~0<<%d)<<%d)))|"
            "(((((%s&$%lX)>>%d)&~(~0<<%d))<<%d)|"
            "((((%s&$%lX)>>%d)&~(~0<<%d))<<%d)))",
            word, width1, pos1, width2, pos2,
            val, mask1, shift1, width1, pos1,
            val, mask2, shift2, width2, pos2);
    n = (unsigned long)strlen(local);
    dst = (char *)xmalloc(n + 1UL);
    if (dst != (char *)0)
        strcpy(dst, local);
    return dst;
}

void encode_field2(void *code, void *op,
                   unsigned long mask1, int shift1, int pos1, int width1,
                   unsigned long mask2, int shift2, int pos2, int width2)
{
    unsigned long word;
    char word_text[32];
    char *expr;
    char **cform;

    cform = (char **)((char *)op + ASM56000_OP_CFORM);
    word = *(unsigned long *)((char *)code + ASM56000_INSN_WORD0);
    if (*cform == (char *)0) {
        word = insert_bits2(word,
                            *(unsigned long *)((char *)op + ASM56000_OP_VALUE),
                            mask1, shift1, pos1, width1,
                            mask2, shift2, pos2, width2);
        *(unsigned long *)((char *)code + ASM56000_INSN_WORD0) = word;
        return;
    }

    sprintf(word_text, "$%06lX", word);
    expr = insert_bits2_expr(word_text, *cform,
                             mask1, shift1, pos1, width1,
                             mask2, shift2, pos2, width2);
    *(char **)((char *)code + ASM56000_INSN_CFORM0) = expr;
    xfree(*cform);
    *cform = (char *)0;
}
