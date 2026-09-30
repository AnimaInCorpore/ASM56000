/* stubs.c - minimal environment so single SIM56000 translation units can be built into a shared
 * library and compared with the original executable running in the emulator (tests/sim56000/emu). */
#include <stdlib.h>
#include <string.h>
#include "sim56000.h"
#define W __attribute__((weak))

W struct sim_state *cur_sim;
W struct dev_type *cur_dtype;
W struct dev_inst *cur_dev;
W struct prof_ctx *prof_ctx;
W struct dev_type **chiptype_tab;
W struct dev_inst **dev_tab;
W struct sim_state **dev_state_tab;
W long max_devices = 1;
W long cur_dev_index = 0;
W long gui_mode[2] = { 0, 0 };
W long text_rows = 25;
W long mdisk_block_bytes = 0x400;
W long macro_active;
W long quit_on_error;
W long on_error_active;
W long last_error_code[3];
W unsigned char status1_buf[256];
W char *parm_errmsg;
W unsigned long shr_fill_bit[2] = { 0x80000000UL, 0 };
W long dec_split_16[4] = { 51712L, 15258, 0, 0 };
W long dec_split_24[4] = { 10144256L, 59, 0, 1919973445L };
W const char *fmt_tab_16[5];
W const char *fmt_tab_24[5];
W const char *fmt_tab_32[5];
W const char *fmt_tab_16_nosym[5];
W const char *fmt_tab_24_nosym[5];
W const char *fmt_tab_32_nosym[5];

W long memmap_find(long s, unsigned long a) { return 0; }
W long mdisk_read(long d, unsigned long s, unsigned long a, unsigned long *p) { return 1; }
W void mdisk_write(long d, unsigned long s, unsigned long a, unsigned long v) { }
W void dev_spaces_call_8(long a, long *o, long c) { }
W void dev_spaces_call_c(long a, long b, long c) { }
W long mdisk_spill(void) { return 0; }
W void out_text(char *l, long n) { }
W void screen_flush(void) { }
W void screen_write(long r, long c, char *s, long m) { }
W void cmd_execute(long d, char *l) { }
W void path_combine(char *d, char *n, char *e, char *o) { }
W long periph_find_reg(long d, char *n, long *p, long *r) { return 0; }
W long dbg_resolve_symbol(char *n, void *v) { return 0; }
W long dbg_parse_file_line(char *a, void *v, unsigned long *l) { return 0; }
W long mem_addr_check(long i, unsigned long a) { return 0; }
W void rangemap_set(void *m, unsigned long lo, unsigned long hi, long sz, long v) { }
W long rangemap_get(void *m, unsigned long a) { return 0; }
W char *fmt_float_exp(char *f, double *d) { return f; }
W void *prof_malloc(unsigned long n) { return calloc(1, n); }
W void *pool_alloc(void *p, unsigned long n) { return calloc(1, n); }
/* the real dsp_alloc/dsp_free are in radix.c; tests link that too when needed */

W void *dsp_alloc(unsigned long n, long z) { return z ? calloc(1, n) : malloc(n); }
W void dsp_free(void *p) { free(p); }

/* callbacks into the emulated original for functions that are not translated yet (set from Python) */
long (*cb_opclass_lookup)(unsigned long, unsigned long);
long (*cb_insn_validate)(unsigned long, unsigned long);
W long opclass_lookup(unsigned long opw, unsigned long cpu) { return cb_opclass_lookup ? cb_opclass_lookup(opw, cpu) : 0; }
W long insn_validate(unsigned long opw, unsigned long fam) { return cb_insn_validate ? cb_insn_validate(opw, fam) : 0; }
W void set_family(long f) { static struct dev_type dt; dt.family = f; cur_dtype = &dt; }

/* log of the calls into the (untranslated) core register helpers, compared with the emulated original */
long call_log[4096][3];
long call_n;
W void core_touch_reg(long r) { if (call_n < 4096) { call_log[call_n][0] = 1; call_log[call_n][1] = r; call_log[call_n][2] = 0; call_n++; } }
W void core_copy_reg(long a, long b) { if (call_n < 4096) { call_log[call_n][0] = 2; call_log[call_n][1] = a; call_log[call_n][2] = b; call_n++; } }
W void core_copy_reg_quiet(long a, long b) { if (call_n < 4096) { call_log[call_n][0] = 3; call_log[call_n][1] = a; call_log[call_n][2] = b; call_n++; } }
W void core_read_copy(unsigned long a, long b) { if (call_n < 4096) { call_log[call_n][0] = 4; call_log[call_n][1] = (long)a; call_log[call_n][2] = b; call_n++; } }

/* peripheral reset test support: build cur_dev/cur_sim/cur_dtype for chip type `t` filled from rnd[] and dump the words
 * periph_reset may touch */
static unsigned long *tst_rnd;
static long tst_pos;
static unsigned long tst_next(void) { return tst_rnd[tst_pos++]; }
long tst_periph_setup(long t, unsigned long *rnd, long dump_only, unsigned long *out)
{
    static struct dev_inst dev;
    static struct sim_state sim;
    long i, j, n = 0;
    tst_rnd = rnd; tst_pos = 0;
    cur_dtype = chiptype_tab[t];
    cur_dev = &dev; cur_sim = &sim;
    if (!dump_only) {
        dev.flags = (long)(tst_next() & 0xffffffffUL);
        sim.var24 = (long)(tst_next() & 0xffffffffUL);
        sim.rstat = (struct region_stat *)calloc((size_t)cur_dtype->n_map, sizeof(struct region_stat));
        sim.regflags = (struct grp_rt *)calloc((size_t)cur_dtype->n_periph, sizeof(struct grp_rt));
        for (i = 0; i < cur_dtype->n_map; i++) {
            sim.rstat[i].rd.total = (long)(tst_next() & 0xffffffffUL);
            sim.rstat[i].wr.total = (long)(tst_next() & 0xffffffffUL);
        }
        for (i = 0; i < cur_dtype->n_periph; i++) {
            long nreg = cur_dtype->periph[i].def->nreg;
            sim.regflags[i].flags = (unsigned long *)calloc((size_t)nreg + 1, sizeof(unsigned long));
            for (j = 0; j < nreg; j++)
                sim.regflags[i].flags[j] = tst_next() & 0xffffffffUL;
        }
        return 0;
    }
    out[n++] = (unsigned long)dev.flags & 0xffffffffUL;
    out[n++] = (unsigned long)sim.var24 & 0xffffffffUL;
    for (i = 0; i < cur_dtype->n_map; i++) {
        out[n++] = (unsigned long)sim.rstat[i].rd.total & 0xffffffffUL;
        out[n++] = (unsigned long)sim.rstat[i].wr.total & 0xffffffffUL;
    }
    for (i = 0; i < cur_dtype->n_periph; i++)
        for (j = 0; j < cur_dtype->periph[i].def->nreg; j++)
            out[n++] = sim.regflags[i].flags[j] & 0xffffffffUL;
    return n;
}

/* profiler counter access for the igrp tests */
void tst_prof_new(void) { static struct prof_ctx p; memset(&p, 0, sizeof p); prof_ctx = &p; }
void tst_prof_set_on(long k, long v) { prof_ctx->kind_on[k] = v; }
long tst_prof_dump(long *out)
{
    long n = 0, k, g, m;
    for (k = 0; k < 0x67; k++) { out[n++] = prof_ctx->kind_on[k]; out[n++] = prof_ctx->cnt_plain[k]; out[n++] = prof_ctx->cnt_pm1[k]; out[n++] = prof_ctx->cnt_pm2[k]; }
    for (k = 0; k < 6; k++) out[n++] = prof_ctx->cnt_pm[k];
    for (g = 0; g < 9; g++) for (m = 0; m < 16; m++) out[n++] = prof_ctx->grp[g][m];
    return n;
}
