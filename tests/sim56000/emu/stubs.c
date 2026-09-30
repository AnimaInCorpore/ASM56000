/* stubs.c - minimal environment so single SIM56000 translation units can be built into a shared
 * library and compared with the original executable running in the emulator (tests/sim56000/emu). */
#include <stdlib.h>
#include <string.h>
#include "sim56000.h"
#define W __attribute__((weak))

struct sim_state *cur_sim;
struct dev_type *cur_dtype;
struct dev_inst *cur_dev;
struct prof_ctx *prof_ctx;
struct dev_type **chiptype_tab;
struct dev_inst **dev_tab;
struct sim_state **dev_state_tab;
long max_devices = 1;
long cur_dev_index = 0;
long gui_mode[2] = { 0, 0 };
long text_rows = 25;
long mdisk_block_bytes = 0x400;
long macro_active, quit_on_error, on_error_active, last_error_code[3];
unsigned char status1_buf[256];
char *parm_errmsg;
unsigned long shr_fill_bit[2] = { 0x80000000UL, 0 };
long dec_split_16[4] = { 51712L, 15258, 0, 0 };
long dec_split_24[4] = { 10144256L, 59, 0, 1919973445L };
const char *fmt_tab_16[5], *fmt_tab_24[5], *fmt_tab_32[5];
const char *fmt_tab_16_nosym[5], *fmt_tab_24_nosym[5], *fmt_tab_32_nosym[5];

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
