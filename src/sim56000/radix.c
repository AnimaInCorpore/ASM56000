/* radix.c - device thunks, radix/value formatting, access trace ring, dsp_alloc allocator
 * (SIM56000.EXE 6.3.0, module radix 0x456f60-0x458060).
 * The core_vtable slots 7..15 are NULL in every device type, so the unused thunks
 * dev_call_slot10..15 (never called in the original) return 0 here. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sim56000.h"

typedef long (*mem_read_fn)(long space, unsigned long addr, unsigned long *out);
typedef long (*mem_write_fn)(long space, unsigned long addr, unsigned long val);
typedef long (*mem_write_n_fn)(long space, unsigned long addr, unsigned long val, unsigned long count);
typedef long (*region_of_fn)(long space, unsigned long addr);
typedef long (*group_io_fn)(long grp, long a, long b, long c);
typedef unsigned long (*mode_hook_fn)(void);

/* the mode flag word of the current device type (the original may call a hook at cur_dtype+0x4e8) */
unsigned long dev_mode_word(void)
{
    return (unsigned long)cur_dtype->flags & MASK32;
}

/* argument for the fmt_tab printf formats: signed for %ld (radix 1), else the plain 32-bit pattern */
static long fmt_arg(unsigned long v, long radix)
{
    v &= MASK32;
    if (radix == 1 && (v & 0x80000000UL) != 0)
        return -(long)((~v & MASK32) + 1UL);
    return (long)v;
}

void dev_spaces_call_c(long a, long b, long c)
{
    long i;

    for (i = 0; i < cur_dtype->n_periph; i++)
        ((group_io_fn)cur_dtype->periph[i].def->io_write)(i, a, b, c);
}

void dev_spaces_call_8(long a, long *out, long c)
{
    long i;

    *out = 0;
    for (i = 0; i < cur_dtype->n_periph; i++)
        ((group_io_fn)cur_dtype->periph[i].def->io_read)(i, a, (long)out, c);
}

/* run fn with cur_dev/cur_dtype switched to device dev; 0 when there is no such device */
#define DEV_THUNK_BEGIN \
    struct dev_inst *save_dev = cur_dev; \
    struct dev_type *save_type = cur_dtype; \
    long r = 0; \
    cur_dev = dev_tab[dev]; \
    if (cur_dev != NULL) { \
        cur_dtype = chiptype_tab[cur_dev->type];
#define DEV_THUNK_END \
    } \
    cur_dtype = save_type; \
    cur_dev = save_dev; \
    return r;

long dev_call_slot1(long dev, long a, long b, long c)
{
    DEV_THUNK_BEGIN
    r = ((mem_write_fn)cur_dtype->vtable->mem_write)(a, b, c);
    DEV_THUNK_END
}

long dev_mem_read(long dev, long a, long b, long c)
{
    DEV_THUNK_BEGIN
    r = ((mem_read_fn)cur_dtype->vtable->mem_read)(a, b, (unsigned long *)c);
    DEV_THUNK_END
}

long dev_call_slot2(long dev, long a, long b, long c, long d)
{
    DEV_THUNK_BEGIN
    r = ((mem_write_n_fn)cur_dtype->vtable->mem_write_n)(a, b, c, d);
    DEV_THUNK_END
}

long dev_call_slot10(long dev, long a, long b, long c) { return 0; }
long dev_call_slot11(long dev, long a, long b, long c) { return 0; }
long dev_call_slot12(long dev, long a, long b, long c) { return 0; }
long dev_call_slot13(long dev, long a, long b, long c) { return 0; }
long dev_call_slot14(long dev, long a, long b, long c) { return 0; }
long dev_call_slot15(long dev, long a, long b, long c) { return 0; }

/* look up a memory space by name; returns 1 and its id in *pid */
long dev_find_space(long dev, char *name, long *pid)
{
    struct dev_inst *save_dev = cur_dev;
    struct dev_type *save_type = cur_dtype;
    long i;

    cur_dev = dev_tab[dev];
    if (cur_dev != NULL) {
        cur_dtype = chiptype_tab[cur_dev->type];
        for (i = 0; i < cur_dtype->n_map; i++) {
            if (stricmp_ci(name, (char *)cur_dtype->map[i].name) == 0) {
                *pid = cur_dtype->map[i].space;
                cur_dtype = save_type;
                cur_dev = save_dev;
                return 1;
            }
        }
    }
    cur_dtype = save_type;
    cur_dev = save_dev;
    return 0;
}

long stricmp_ci(char *a, char *b)
{
    signed char c1, c2;

    do {
        c1 = (signed char)*a++;
        c2 = (signed char)*b++;
        if (c1 != c2) {
            if (isupper((unsigned char)c1))
                c1 = (signed char)tolower((unsigned char)c1);
            if (isupper((unsigned char)c2))
                c2 = (signed char)tolower((unsigned char)c2);
        }
    } while (c1 != 0 && c2 != 0 && c1 == c2);
    return (long)c1 - (long)c2;
}

/* record val for [addr..] in the tag map of every region that shares the class of space_idx */
void space_notify(long space_idx, unsigned long addr, unsigned long val, long arg)
{
    unsigned long cls = cur_dtype->map[space_idx].cls;
    long j;

    for (j = 0; j < cur_dtype->n_map; j++) {
        unsigned long c = cur_dtype->map[j].cls;

        if ((c & cls) == c && (c & 0xffUL) == (cls & 0xffUL))
            rangemap_set(&cur_sim->rstat[j].map8, addr, val, cur_dtype->map[j].size_m1, arg);
    }
}

long mem_addr_check(long space_idx, unsigned long addr)
{
    long sp, idx;

    sp = ((region_of_fn)cur_dtype->vtable->region_of)(cur_dtype->map[space_idx].space, addr);
    idx = memmap_find(sp, addr);
    if (idx == -1)
        return 0;
    return rangemap_get(&cur_sim->rstat[idx].map8, addr);
}

void fmt_addr(unsigned long addr, char *buf)
{
    unsigned long mode = dev_mode_word();
    const char *fmt;
    unsigned long mask;

    if ((mode & 0xc00) != 0)
        fmt = "%04lx";
    else if ((mode & 0x200) != 0)
        fmt = "%06lx";
    else
        fmt = (mode & 8) != 0 ? "%04lx" : "%08lx";
    mask = (mode & 0x800) != 0 ? 0xffffUL : MASK32;
    sprintf(buf, fmt, addr & mask);
}

/* sign bit of the word size selected by the region attribute bits 26..31 */
static unsigned long attr_sign_bit(unsigned long attr)
{
    if (attr & 0x80000000UL) return 8UL;
    if (attr & 0x40000000UL) return 0x80UL;
    if (attr & 0x20000000UL) return 0x800UL;
    if (attr & 0x10000000UL) return 0x8000UL;
    if (attr & 0x08000000UL) return 0x80000UL;
    if (attr & 0x04000000UL) return 0x800000UL;
    return 0x80000000UL;
}

static void bin_digits(char *out, unsigned long value, long nbits)
{
    long i;

    for (i = 0; i < nbits; i++)
        out[i] = ((value & (1UL << (nbits - 1 - i))) != 0) + '0';
}

static long word_bits(unsigned long mode)
{
    if (mode & 0x10000000UL)
        return 16;
    return (mode & 0x2000000UL) != 0 ? 32 : 24;
}

/* read the word at space:addr and format it in the given radix (0 bin, 1 dec, 2 frac, 3 hex, 4 unsigned) */
long fmt_read_word(long space, unsigned long addr, long radix, char *out, char *nanfmt)
{
    struct val node;
    unsigned long buf[2];
    long dec[2];
    long r, idx;
    unsigned long attr, mode, sign;
    const char *fmt;
    char *s;

    buf[0] = buf[1] = 0;
    r = ((mem_read_fn)cur_dtype->vtable->mem_read)(space, addr, buf);   /* slot 11 is NULL */
    idx = memmap_find(space, addr);
    attr = cur_dtype->map[idx].f24;
    memset(&node, 0, sizeof node);
    node.flags = (attr & 0xff400003UL) | 0x100UL;
    mode = dev_mode_word();
    node.lo = buf[0];
    node.hi = buf[1];

    if ((attr & 2) == 0) {
        if (radix != 2) {
            if (radix == 1) {
                sign = attr_sign_bit(attr);
                if ((sign & buf[0]) != 0)
                    buf[0] = (buf[0] | ~(sign - 1)) & MASK32;
            }
            if (attr & 0xf0000000UL)
                fmt = fmt_tab_16[radix];
            else if (attr & 0x0c000000UL)
                fmt = fmt_tab_24[radix];
            else
                fmt = fmt_tab_32[radix];
            sprintf(out, fmt, fmt_arg(buf[0], radix));
            return r;
        }
        node.lo = buf[0];
        word_to_frac(mode, &node);
        if ((mode & 0x80) == 0) {
            sprintf(out, "%10.7f", node.d);
            return r;
        }
        if (nanfmt == NULL)
            nanfmt = "%14.14s";
    } else {
        if (radix != 2) {
            if (radix != 1 && radix != 4) {
                if ((mode & 0x80) == 0)
                    fmt = (mode & 0x10000000UL) != 0 ? "$%04lx%04lx" : "$%06lx%06lx";
                else
                    fmt = "$%08lx%08lx";
                sprintf(out, fmt, (unsigned long)buf[1], (unsigned long)buf[0]);
                return r;
            }
            val_to_dec_parts(mode, buf, dec);
            sprintf(out, "%06lu%09lu", (unsigned long)dec[1], (unsigned long)dec[0]);
            return r;
        }
        if ((mode & 0x1000) != 0) {
            buf[0] = ((buf[0] & 0xffffUL) | (buf[1] << 16)) & MASK32;
            buf[1] = buf[1] >> 8;
        }
        node.lo = buf[0];
        node.hi = buf[1];
        dword_to_frac(mode, &node);
        if ((mode & 0x80) == 0) {
            sprintf(out, "%18.15f", node.d);
            return r;
        }
        if (nanfmt == NULL)
            nanfmt = "%25.25s";
    }
    s = fmt_float_exp(nanfmt, &node.d);
    strcpy(out, s);
    return r;
}

/* format a given value (double word regions are read from memory) */
void fmt_word(long space_idx, long addr, long radix, char *out, unsigned long value)
{
    struct val node;
    unsigned long buf[2];
    long dec[2];
    long nbits;
    unsigned long attr, mode, sign, lo, hi;
    const char *fmt;
    char *s;

    attr = cur_dtype->map[space_idx].f24;
    memset(&node, 0, sizeof node);
    node.flags = (attr & 0xff400003UL) | 0x100UL;
    mode = dev_mode_word();
    buf[0] = buf[1] = 0;

    if ((attr & 2) == 0) {
        lo = value;
        node.lo = value;
        if (radix == 2) {
            word_to_frac(mode, &node);
            if ((mode & 0x80) == 0) {
                sprintf(out, "%10.7f", node.d);
                return;
            }
            s = fmt_float_exp("%15.15s", &node.d);
            sprintf(out, "%s", s);
            return;
        }
        if (radix == 0) {
            nbits = word_bits(mode);
            bin_digits(out, value, nbits);
            out[nbits] = '\0';
            return;
        }
        if (radix == 1) {
            sign = attr_sign_bit(attr);
            if ((value & sign) != 0)
                lo = (~(sign - 1) | value) & MASK32;
        }
        if (mode & 0x10000000UL)
            fmt = fmt_tab_16_nosym[radix];
        else if (mode & 0x4000000UL)
            fmt = fmt_tab_24_nosym[radix];
        else
            fmt = fmt_tab_32_nosym[radix];
        sprintf(out, fmt, fmt_arg(lo, radix));
        return;
    }
    ((mem_read_fn)cur_dtype->vtable->mem_read)(cur_dtype->map[space_idx].space, (unsigned long)addr, buf);
    lo = buf[0];
    hi = buf[1];
    if (radix == 2) {
        node.lo = lo;
        node.hi = hi;
        dword_to_frac(mode, &node);
        if ((mode & 0x80) == 0) {
            sprintf(out, "%18.15f", node.d);
            return;
        }
        s = fmt_float_exp("%18.18s", &node.d);
        sprintf(out, "%s", s);
        return;
    }
    if (radix != 1) {
        if (radix != 0) {
            fmt = (mode & 0x4000000UL) != 0 ? "$%06lx%06lx" : "$%08lx%08lx";
            sprintf(out, fmt, hi, lo);
            return;
        }
        nbits = word_bits(mode);
        bin_digits(out, hi, nbits);
        bin_digits(out + nbits, lo, nbits);
        out[nbits * 2] = '\0';
        return;
    }
    val_to_dec_parts(mode, buf, dec);
    sprintf(out, "%06ld%09ld", dec[1], dec[0]);
}

/* record an access in the read or write ring of every region that contains addr */
void mem_trace_access(unsigned long space, unsigned long addr, long is_write, long value)
{
    unsigned long mode = dev_mode_word();
    unsigned long mask = (mode & 0x800) != 0 ? 0xffffUL : MASK32;
    unsigned long a = addr & mask, cls;
    long idx, j, n;
    struct access_ring *ring;

    idx = memmap_find(space, a);
    cls = cur_dtype->map[idx].cls;
    for (j = 0; j < cur_dtype->n_map; j++) {
        struct mem_region *m = &cur_dtype->map[j];

        if ((m->cls & cls) == cls && (m->cls & 0xffUL) == (cls & 0xffUL) &&
            (((unsigned long)m->lo) & mask) <= a && a <= (((unsigned long)m->hi) & mask)) {
            ring = is_write == 0 ? &cur_sim->rstat[j].rd : &cur_sim->rstat[j].wr;
            n = ring->idx;
            ring->total++;
            ring->count++;
            ring->idx = n + 1;
            if (n + 1 > 15)
                ring->idx = 0;
            ring->addr[ring->idx] = a;
            ring->val[ring->idx] = (unsigned long)value & MASK32;
        }
    }
}

void mem_trace_fetch(unsigned long addr)
{
    mem_trace_access(0x13, addr, 0, 0);
}

static void restore_msg(char *msg)
{
    struct sim_state *save_sim = cur_sim;
    struct dev_inst *save_dev = cur_dev;

    cur_sim = dev_state_tab[cur_dev_index];
    cur_dev = dev_tab[cur_dev_index];
    out_text(msg, 1);
    cur_sim = save_sim;
    cur_dev = save_dev;
}

void *dsp_alloc(unsigned long size, long zero)
{
    void *p;

    if (gui_mode[0] != 0)
        return NULL;
    p = malloc((size_t)size);
    while (p == NULL) {
        if (mdisk_spill() == 0) {
            restore_msg("Insufficient memory: dsp_alloc");
            return NULL;
        }
        p = malloc((size_t)size);
    }
    if (zero != 0)
        memset(p, 0, (size_t)size);
    return p;
}

void dsp_free(void *p)
{
    if (gui_mode[0] != 0) {
        dsp_free_ext(p);
        return;
    }
    free(p);
}

void *dsp_realloc(void *p, unsigned long size)
{
    void *q;

    if (gui_mode[0] != 0)
        return NULL;
    q = realloc(p, (size_t)size);
    while (q == NULL) {
        if (mdisk_spill() == 0) {
            restore_msg("Insufficient memory: dsp_realloc");
            return NULL;
        }
        q = realloc(p, (size_t)size);
    }
    return q;
}

/* free all block lists of all mdisk regions of a device */
void mdisk_free_all(long dev)
{
    long i;
    struct mdisk_node *first, *p, *next;
    struct mem_block *mb;

    cur_dev = dev_tab[dev];
    cur_dtype = chiptype_tab[cur_dev->type];
    mb = cur_dev->mem;
    if (mb == NULL)
        return;
    for (i = 0; i < cur_dtype->n_map; i++) {
        if ((cur_dtype->map[i].attr & REGION_MDISK) != 0) {
            first = mb[i].md.cursor;
            p = first;
            if (first != NULL) {
                do {
                    next = p->next;
                    if (p->state == MD_RESIDENT)
                        dsp_free(p->u.block);
                    dsp_free(p);
                    p = next;
                } while (next != first);
            }
            mb[i].md.prev_cursor = NULL;
            mb[i].md.cursor = NULL;
        }
    }
}
