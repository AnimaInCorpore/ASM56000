/* devreg.c - SIM56000.EXE v6.3 (CLAS56), device registry and licence key generator (module devreg, 0x41c140-0x41c8a0):
 * device_install() adds a keyed device type (DSP68356, DSP56030) to the chip type table when the key for its name
 * matches; igrp_method_41c490() builds the statistics record of the instruction at an address for the profiler. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sim56000.h"
#include "simdata.h"
#include "simproto.h"

static unsigned long keygen_seed;
static char keygen_out[16];

/* the keyed device slots; `key` is stored in the second word block of the entry (12 bytes in the original) */
#define KEY_BUF(i) ((char *)&keyed_dev_table[i].w1)

long device_install(char *name, char *key)
{
    long slot, i, k;
    char *gen;

    if (name == NULL)
        return -1;
    slot = 0;
    while (slot < num_chiptypes) {
        if (chiptype_tab[slot] == NULL)
            break;
        if (strcmp(chiptype_tab[slot]->name, name) == 0)
            return slot;
        slot++;
    }
    if (slot == num_chiptypes)
        return -1;
    for (i = 0; ; i++) {
        if (strcmp(((struct dev_type *)keyed_dev_table[i].w0)->name, name) == 0) {
            gen = device_keygen(name);
            break;
        }
        if (i + 1 >= 2)
            return -1;
    }
    /* key[0..8]: the terminating zero of the generated key is compared as well */
    for (k = 0; k <= 8; k++)
        if (key[k] != gen[k])
            return -1;
    chiptype_tab[slot] = (struct dev_type *)keyed_dev_table[i].w0;
    strcpy(KEY_BUF(i), key);
    chiptype_tab[slot]->key = KEY_BUF(i);
    ((void **)itype_tab)[slot] = keyed_dev_aux[i];
    return slot;
}

/* (a * b) mod keygen_mod in 32 bit arithmetic, split at keygen_base */
unsigned long keygen_mulmod(unsigned long a, unsigned long b)
{
    unsigned long base = (unsigned long)keygen_base & MASK32;
    unsigned long mod = (unsigned long)keygen_mod & MASK32;
    unsigned long t;

    a &= MASK32;
    b &= MASK32;
    t = (((a / base) * (b % base) & MASK32) + ((b / base) * (a % base) & MASK32)) & MASK32;
    t = (((t % base) * base & MASK32) + ((b % base) * (a % base) & MASK32)) & MASK32;
    return t % mod;
}

void keygen_step(void)
{
    unsigned long r = keygen_mulmod(keygen_seed, (unsigned long)keygen_mult);

    keygen_seed = ((r + 1) & MASK32) % ((unsigned long)keygen_mod & MASK32);
}

/* 8 character key of a device name */
char *device_keygen(char *name)
{
    unsigned long len, i, shift, x, acc, v, n;
    long c;

    keygen_out[8] = 0;
    len = (unsigned long)strlen(name);
    keygen_seed = 0x12d715UL;
    acc = 0;
    shift = 0;
    for (i = 0; i < len; i++) {
        c = (unsigned char)name[i];
        if (c >= 0x80)
            c -= 256;
        if (c >= 0 && isupper(c))
            c = tolower(c);
        keygen_seed = (keygen_seed + (((unsigned long)c << (shift % 23)) & MASK32)) & MASK32;
        keygen_step();
        acc ^= keygen_seed;
        shift += 5;
    }
    acc >>= 8;
    for (n = 0; n < 8; n++) {
        do {
            keygen_step();
            x = keygen_seed;
            keygen_step();
            v = (acc ^ (keygen_seed >> 8) ^ (x >> 8)) & 0x7f;
        } while (!isalnum((int)v));
        if (isupper((int)v))
            v = (unsigned long)tolower((int)v);
        keygen_out[n] = (char)v;
        acc >>= 1;
    }
    return keygen_out;
}

/* statistics record of the instruction at (space, addr) as the profiler sees it; addr2 is the address of the
 * following instruction (used to detect not taken conditional branches) */
static long ccr_periph, ccr_reg = -1, omr_periph, omr_reg = -1;

void igrp_method_41c490(long dev, long space, unsigned long addr, unsigned long addr2, unsigned long *pstat)
{
    struct insn_stat *stat = (struct insn_stat *)pstat;
    unsigned long sr, omr, w8, w4, fl, flags[1];
    long dec[0x30];
    long k;

    if (profiler_hook == NULL)
        return;
    if (cur_sim->regs_cached == 0) {
        if (ccr_reg < 0)
            periph_find_reg(0, "sr", &ccr_periph, &ccr_reg);
        periph_call(dev, ccr_periph, ccr_reg, (long)&sr);
        if (omr_reg < 0)
            periph_find_reg(0, "omr", &omr_periph, &omr_reg);
        periph_call(dev, omr_periph, omr_reg, (long)&omr);
    } else {
        sr = cur_sim->sr_cache;
        omr = cur_sim->omr_cache;
    }
    stat->f0 = (long)addr;
    stat->ccr = (long)sr;
    stat->omr = (long)omr;
    dev_mem_read(dev, space, (long)addr, (long)&w8);
    dev_mem_read(dev, space, (long)(addr + 1), (long)&w4);
    k = memmap_find(space, addr);
    fl = cur_dtype->map[k].f24;
    k = memmap_find(0, 0);
    if ((fl & 0x10000000UL) != 0 && (cur_dtype->map[k].f24 & 0x4000000UL) != 0) {
        fl = (w8 & 0xffff) | ((w4 & 0xff) << 16);
        dev_mem_read(dev, space, (long)(addr + 2), (long)&w8);
        dev_mem_read(dev, space, (long)(addr + 3), (long)&w4);
        w4 = (w8 & 0xffff) | ((w4 & 3) << 16);
        w8 = fl;
    }
    dec[0x2e] = (long)w8;
    dec[0x2f] = (long)w4;
    flags[0] = 0;
    if (decode_insn(dec, (long)sr, (long)omr, flags) == 0 && addr == addr2)
        dec[0] = -1;
    insn_stat_classify(stat, dec);
    insn_stat_operands(stat, dec);
    stat->cc_true = (long)eval_cc(sr, stat->aux);
    k = stat->cat;
    if ((k == 0x2d || k == 0x2f || k == 0x2e || k == 0x30 || k == 0x11 || k == 0x12 || k == 0x13 || k == 0x15) &&
        addr2 == ((stat->flags & 4) != 0) + 1 + addr)
        stat->cc_true = 0;
    if (k == 0x23)
        cur_sim->flag_428 = 1;
}
