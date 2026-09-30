/* miscx.c - decimal split helpers, allocator stubs, sim_error
 * (SIM56000.EXE 6.3.0, module miscx 0x45d120-0x45e5a0, first part). */
#include <stdio.h>
#include <string.h>
#include "sim56000.h"

/* split a 2/3-word value into its low and high 9-digit decimal halves: out[0] = value % 1e9, out[1] = value / 1e9 */
static void dec_parts(unsigned long mode, unsigned long *num, unsigned long *out)
{
    unsigned long q[3], r[3], base;
    unsigned long den[3];

    expr_mode = mode;
    base = (mode & 0x10000000UL) != 0 ? 0x10000UL : 0x1000000UL;
    den[0] = (unsigned long)((mode & 0x10000000UL) != 0 ? dec_split_16[0] : dec_split_24[0]);
    den[1] = (unsigned long)((mode & 0x10000000UL) != 0 ? dec_split_16[1] : dec_split_24[1]);
    den[2] = (unsigned long)((mode & 0x10000000UL) != 0 ? dec_split_16[2] : dec_split_24[2]);
    mp_divmod(num, den, q, r);
    out[0] = (base * r[1] + r[0]) & MASK32;
    out[1] = (base * q[1] + q[0]) & MASK32;
}

void val_to_dec_parts2(unsigned long mode, unsigned long *in, unsigned long *out)
{
    if ((mode & 0x80) != 0) {
        out[0] = in[0];
        out[1] = 0;
        return;
    }
    dec_parts(mode, in, out);
}

/* in[0], in[1] are the low and high word; 32-bit word devices (0x2000000) carry 24 + 24 + 16 bits */
void val_to_dec_parts(unsigned long mode, unsigned long *in, long *out)
{
    unsigned long num[3], res[2];

    if ((mode & 0x2000000UL) == 0) {
        num[2] = 0;
        num[0] = in[0];
        num[1] = in[1];
    } else {
        num[2] = in[1] >> 16;
        num[1] = ((in[1] & 0xffffUL) << 8) | (in[0] >> 24);
        num[0] = in[0] & 0xffffffUL;
    }
    dec_parts(mode, num, res);
    out[0] = (long)res[0];
    out[1] = (long)res[1];
}

void dsp_free_ext(void *p)
{
}

long ret_true(void)
{
    return 1;
}

long ret_false(void)
{
    return 0;
}

long ret_99(void)
{
    return 99;
}

/* report an error: message in braces to the console/log, and "quit ;on error" inside macros */
void sim_error(char *msg)
{
    char line[256 + 8];

    cur_sim->view_mode = 0;
    strncpy((char *)status1_buf, msg, 0xff);
    last_error_code[0] = -1L;
    sprintf(line, "{%s}", msg);
    out_text(line, 1);
    screen_flush();
    if (macro_active != 0 && quit_on_error != 0) {
        on_error_active = 1;
        cmd_execute(cur_dev_index, "quit ;on error");
    }
}
