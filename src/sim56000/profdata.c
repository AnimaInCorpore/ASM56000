/* Motorola SIM56000.EXE 6.3.0, profiler data module, 0x46b090-0x46c000.
 * Allocation and basic record helpers; profiler reports/records are pending.
 */
#include "sim56000.h"

struct prof_ctx *prof_ctx;
jmp_buf prof_jmpbuf;

long prof_list_count(void *tree)
{
    return tree == NULL ? -1 : ((struct avl_tree *)tree)->count;
}

void *prof_malloc(unsigned long n)
{
    void *p;
    p = dsp_alloc(n, 1);
    if (p == NULL) {
        prof_ctx->flags |= PROF_FL_NO_FILE;
        longjmp(prof_jmpbuf, 1);
    }
    return p;
}

void prof_swap32(void *buf, unsigned long nbytes)
{
    unsigned char *p;
    unsigned char byte;
    unsigned long n;
    p = (unsigned char *)buf;
    for (n = nbytes / 4; n != 0; --n) {
        byte = p[0]; p[0] = p[3]; p[3] = byte;
        byte = p[1]; p[1] = p[2]; p[2] = byte;
        p += 4;
    }
}

long prof_cmp_ulong(void *a, void *b)
{
    unsigned long item, key;
    item = *(unsigned long *)a & MASK32;
    key = *(unsigned long *)b & MASK32;
    return key < item ? 0 : key == item ? 1 : 2;
}
