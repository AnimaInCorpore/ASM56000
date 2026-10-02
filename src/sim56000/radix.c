/* Motorola SIM56000.EXE 6.3.0, radix module, 0x457e00-0x457fb0.
 * Allocation wrappers; device thunks, formatting and trace helpers are pending.
 */
#include <stdlib.h>
#include <string.h>
#include "sim56000.h"

static void allocation_error(char *message)
{
    struct sim_state *saved_sim;
    struct dev_inst *saved_dev;
    saved_sim = cur_sim;
    saved_dev = cur_dev;
    cur_sim = dev_state_tab[cur_dev_index];
    cur_dev = dev_tab[cur_dev_index];
    out_text(message, 1);
    cur_sim = saved_sim;
    cur_dev = saved_dev;
}

void *dsp_alloc(unsigned long size, long zero)
{
    void *p;
    if (gui_mode[0] != 0)
        return NULL;
    /* Avoid truncating a large request on a host with 16-bit size_t. */
    p = size <= (unsigned long)((size_t)-1) ? malloc((size_t)size) : NULL;
    while (p == NULL) {
        if (mdisk_spill() == 0) {
            allocation_error("Insufficient memory: dsp_alloc");
            return NULL;
        }
        p = size <= (unsigned long)((size_t)-1) ? malloc((size_t)size) : NULL;
    }
    if (zero != 0)
        memset(p, 0, (size_t)size);
    return p;
}

void dsp_free(void *p)
{
    if (gui_mode[0] != 0)
        dsp_free_ext(p);
    else
        free(p);
}

void *dsp_realloc(void *p, unsigned long size)
{
    void *result;
    if (gui_mode[0] != 0)
        return NULL;
    result = size <= (unsigned long)((size_t)-1) ?
             realloc(p, (size_t)size) : NULL;
    while (result == NULL) {
        if (mdisk_spill() == 0) {
            allocation_error("Insufficient memory: dsp_realloc");
            return NULL;
        }
        result = size <= (unsigned long)((size_t)-1) ?
                 realloc(p, (size_t)size) : NULL;
    }
    return result;
}
