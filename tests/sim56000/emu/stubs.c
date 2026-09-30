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
