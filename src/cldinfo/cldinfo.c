/*
 * cldinfo - print memory usage of a DSP COFF absolute load file
 *
 * Reconstructed from Motorola CLDINFO.EXE, Version 6.3 (CLAS56 v6.3, 1999).
 *
 * The object file is a Motorola DSP COFF file.  All header fields are 32-bit
 * big-endian words; section names are 8 plain characters.  The original
 * program read the headers as raw structures and byte-swapped them on the
 * little-endian PC; this version decodes the bytes explicitly so it gives the
 * same results on any host.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILHSZ  0x1c            /* file header size */
#define AOUTSZ  0x3c            /* optional (a.out) header size */
#define SCNHSZ  0x34            /* section header size */

#define F_MAGIC_LO      0x2c5   /* first and last valid f_magic values */
#define F_MAGIC_HI      0x2cc

#define STYP_BLOCK      0x400   /* size of section is taken from s_vaddr */

/* memory space classes */
#define MS_P    0
#define MS_X    1
#define MS_Y    2
#define MS_L    3
#define MS_EM_LO 0x1c
#define MS_EM_HI 0x11c
#define MS_DM   0x11d
#define MS_U    0x11f

static unsigned long secbuf_len;        /* longs allocated in secbuf */
static unsigned char *secbuf;           /* section raw data */
static int no_aouthdr;                  /* file has no optional header */
static long psize, xsize, ysize, start_addr, emsize, dmsize, usize;

static void read_section_contents(FILE *fp);

/* fetch a big-endian 32-bit word */
static long get32(const unsigned char *p)
{
    unsigned long v;

    v = ((unsigned long)p[0] << 24) | ((unsigned long)p[1] << 16) |
        ((unsigned long)p[2] << 8) | (unsigned long)p[3];
    if (v & 0x80000000UL)
        return -(long)(~v & 0x7fffffffUL) - 1;
    return (long)v;
}

static void get_sizes(FILE *fp, long *x, long *y, long *p, long *start,
                      long *em, long *dm, long *u)
{
    read_section_contents(fp);
    *x = xsize;
    *p = psize;
    *y = ysize;
    *em = emsize;
    *dm = dmsize;
    *u = usize;
    if (!no_aouthdr)
        *start = start_addr;
}

/* read the file header, return number of symbols */
static long read_file_hdr(FILE *fp, unsigned char *hdr)
{
    long magic;

    fseek(fp, 0L, SEEK_SET);
    if (fread(hdr, FILHSZ, 1, fp) != 1) {
        perror("read_file_hdr");
        exit(-2);
    }
    magic = get32(hdr);
    if (magic < F_MAGIC_LO || magic > F_MAGIC_HI) {
        fprintf(stderr, "read_file_hdr() failure\n");
        exit(-2);
        return 0;
    }
    return get32(hdr + 16);
}

static int read_aout_hdr(FILE *fp, unsigned char *buf, unsigned size)
{
    fseek(fp, (long)FILHSZ, SEEK_SET);
    if (size != AOUTSZ) {
        fprintf(stderr, "read_aout_hdr() failure\n");
        exit(-3);
    }
    if (fread(buf, size, 1, fp) != 1) {
        perror("read_aout_hdr");
        exit(-3);
    }
    return 0;
}

/* collapse a memory space/mapping code into its memory class */
static long mem_class(long mem)
{
    if (mem > 0xf) {
        if (mem > 0x19) {
            if (mem == 0x11e)
                return MS_P;
            if (mem > 0x11f && mem <= 0x121)
                return MS_U;
            return mem;
        }
        if (mem >= 0x15)
            return MS_Y;
        return MS_X;
    }
    if (mem >= 0xb)
        return MS_P;
    if (mem >= 5)
        return MS_L;
    return mem;
}

static void read_section_contents(FILE *fp)
{
    unsigned char fhdr[FILHSZ];
    unsigned char ahdr[AOUTSZ];
    unsigned char shdr[SCNHSZ];
    long nscns, opthdr, i;
    long mem, cls, size, vsize, scnptr, flags, n;

    read_file_hdr(fp, fhdr);
    nscns = get32(fhdr + 4);
    opthdr = get32(fhdr + 20);
    if (opthdr == AOUTSZ)
        read_aout_hdr(fp, ahdr, AOUTSZ);
    else
        no_aouthdr = 1;

    for (i = 0; i < nscns; i++) {
        if (fseek(fp, FILHSZ + opthdr + i * SCNHSZ, SEEK_SET) != 0) {
            perror("read_section_contents 1");
            exit(-5);
        }
        if (fread(shdr, SCNHSZ, 1, fp) != 1) {
            perror("read_section_contents 2");
            exit(-5);
        }
        if (strncmp((char *)shdr, ".text", 8) == 0 ||
            strncmp((char *)shdr, ".data", 8) == 0)
            continue;

        mem = get32(shdr + 12);
        vsize = get32(shdr + 16);
        size = get32(shdr + 24);
        scnptr = get32(shdr + 28);
        flags = get32(shdr + 48);

        /* the contents are loaded although only the sizes are reported */
        if ((long)secbuf_len < size) {
            if (secbuf != NULL)
                free(secbuf);
            secbuf = (unsigned char *)malloc((size_t)(size << 2));
            if (secbuf == NULL) {
                perror("malloc error");
                exit(-5);
            }
            secbuf_len = size;
        }
        if (fseek(fp, scnptr, SEEK_SET) != 0) {
            perror("read_section_contents 3");
            exit(-5);
        }
        if (size != 0 && fread(secbuf, (size_t)(size << 2), 1, fp) != 1) {
            perror("read_section_contents 4");
            exit(-5);
        }

        cls = mem_class(mem);
        n = (flags & STYP_BLOCK) ? vsize : size;
        if (cls == MS_L) {
            /* the original halves the raw size only for normal sections */
            if (!(flags & STYP_BLOCK))
                n = size >> 1;
            xsize += n;
            ysize += n;
        } else if (cls == MS_Y)
            ysize += n;
        else if (cls == MS_P)
            psize += n;
        else if (cls == MS_X)
            xsize += n;
        else if (cls == MS_DM)
            dmsize += n;
        else if (cls >= MS_EM_LO && cls <= MS_EM_HI)
            emsize += n;
        else if (cls == MS_U)
            usize += n;
    }

    if (!no_aouthdr)
        start_addr = get32(ahdr + 20);
    if (secbuf != NULL) {
        free(secbuf);
        secbuf_len = 0;
        secbuf = NULL;
    }
}

int main(int argc, char **argv)
{
    FILE *fp;
    long x, y, p, start, em, dm, u;

    fp = NULL;
    start = 0;
    if (argc != 2) {
        fprintf(stderr, "Version 6.3 usage: cldinfo file\n");
        exit(-1);
    }
    fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        perror("cldinfo");
        exit(-2);
    }
    get_sizes(fp, &x, &y, &p, &start, &em, &dm, &u);
    fclose(fp);
    fprintf(stdout, "filename: %s\n", argv[1]);
    if (no_aouthdr)
        fprintf(stdout,
            "\txsize: %ld, ysize: %ld, psize: %ld, emsize: %ld, dmsize: %ld, usize: %ld\n",
            x, y, p, em, dm, u);
    else
        fprintf(stdout,
            "\txsize: %ld, ysize: %ld, psize: %ld, emsize: %ld, dmsize: %ld, usize: %ld, start addr: %lx\n",
            x, y, p, em, dm, u, start);
    exit(0);
    return 0;
}
