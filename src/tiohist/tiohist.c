/*
 * tiohist - cycle, instruction and block entry histograms from a simulator
 *           trace ("tio") file and a list of block start addresses
 *
 * Reconstructed from Motorola TIOHIST.EXE, Version 6.3 (CLAS56 v6.3, 1999).
 *
 * The trace file holds one line per executed instruction, starting with
 * "<cycle count> P:$<address>".  The block file holds hexadecimal block
 * start addresses.  Counters are 32-bit unsigned quantities as in the
 * original; they are kept masked so hosts with a 64-bit long agree.
 */

#include <stdio.h>
#include <stdlib.h>

#define M32(x)  ((x) & 0xffffffffUL)

struct block {
    unsigned long addr;         /* block start address */
    unsigned long cycles;       /* cycles spent in block */
    unsigned long count;        /* instructions executed in block */
    unsigned long entries;      /* times the block was entered */
};

static char bar[] = "-------------------------------------------------------------";
static unsigned long barlen = sizeof(bar) - 1;

static struct block blk;        /* record read from the block file */

/* signed view of a 32-bit counter, for the %ld output of the original */
static long s32(unsigned long v)
{
    v = M32(v);
    if (v & 0x80000000UL)
        return -(long)(~v & 0x7fffffffUL) - 1;
    return (long)v;
}

static int blkcmp(const void *a, const void *b)
{
    return (int)s32(((const struct block *)a)->addr -
                    ((const struct block *)b)->addr);
}

static void histogram(char *title, int n, struct block *tab,
                      unsigned long max, int which)
{
    int i;
    unsigned long v;

    if (max == 0)
        max = 1;
    printf("\n%s", title);
    printf("\nblock     count");
    printf("\n--------- --------\n");
    for (i = 0; i < n; i++) {
        if (which == 0)
            v = tab[i].cycles;
        else if (which == 1)
            v = tab[i].count;
        else
            v = tab[i].entries;
        printf("$%08lx %08ld %s\n", tab[i].addr, s32(v),
               bar + (barlen - M32(v * barlen) / max));
    }
}

static void tiohist(FILE *tio, FILE *blocks)
{
    struct block *tab;
    int alloc, n, i, cur, c;
    unsigned long cycle, last, pc, max;

    tab = (struct block *)malloc(100 * sizeof(struct block));
    if (tab == NULL) {
        perror("tiohist");
        exit(-1);
    } else
        alloc = 100;

    for (n = 0; fscanf(blocks, " %lx", &blk.addr) == 1; n++) {
        if (n >= alloc) {
            tab = (struct block *)realloc(tab, (alloc + 100) * sizeof(struct block));
            if (tab == NULL) {
                perror("tiohist");
                exit(-1);
            } else
                alloc += 100;
        }
        tab[n] = blk;
    }
    if (n != 0)
        qsort(tab, n, sizeof(struct block), blkcmp);

    last = 0;
    cur = -1;
    while (fscanf(tio, " %lu P:$%lx", &cycle, &pc) == 2) {
        for (i = cur < 0 ? 0 : cur; i >= 0 && pc < tab[i].addr; i--)
            ;
        while (i < n - 1 && tab[i + 1].addr <= pc)
            i++;
        if (i >= 0) {
            if (i != cur)
                tab[i].entries = M32(tab[i].entries + 1);
            tab[i].count = M32(tab[i].count + 1);
            tab[i].cycles = M32(tab[i].cycles + (cycle - last));
        }
        last = cycle;
        cur = i;
        do
            c = getc(tio);
        while (c != '\n' && c != EOF);
    }

    max = 0;
    for (i = 0; i < n; i++)
        if (tab[i].cycles > max)
            max = tab[i].cycles;
    histogram("_______Cycle Count Histogram__________", n, tab, max, 0);
    max = 0;
    for (i = 0; i < n; i++)
        if (tab[i].count > max)
            max = tab[i].count;
    histogram("_______Instruction Count Histogram__________", n, tab, max, 1);
    max = 0;
    for (i = 0; i < n; i++)
        if (tab[i].entries > max)
            max = tab[i].entries;
    histogram("_______Block Entry Count Histogram__________", n, tab, max, 2);
}

int main(int argc, char **argv)
{
    FILE *tio, *blocks;

    if (argc != 3) {
        fprintf(stderr, "Version 6.3 usage: tiohist tiofile blockfile > outputfile\n");
        exit(-1);
    }
    tio = fopen(argv[1], "r");
    if (tio == NULL) {
        perror("tiohist");
        exit(-1);
    }
    blocks = fopen(argv[2], "r");
    if (blocks == NULL) {
        perror("tiohist");
        exit(-1);
    }
    tiohist(tio, blocks);
    fclose(blocks);
    fclose(tio);
    exit(0);
    return 0;
}
