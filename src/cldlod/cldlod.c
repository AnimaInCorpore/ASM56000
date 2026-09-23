/*
 * cldlod - convert a DSP COFF load file (.cld) to a Motorola .lod file
 *
 * Reconstructed from Motorola CLDLOD.EXE, Version 6.3 (CLAS56 v6.3, 1999).
 *
 * The COFF file stores 32-bit big-endian words.  The original program read
 * the structures raw on the PC and reversed every 4-byte word (swapping the
 * 8 name characters back afterwards).  This version does the same byte
 * reversal and then decodes the resulting little-endian image, so strings
 * and names behave exactly as they did on the PC on any host.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>
#include <math.h>

#define FILHSZ  0x1c            /* file header */
#define SYMESZ  0x20            /* symbol table entry */
#define SCNHSZ  0x34            /* section header */
#define OPTMAX  0x100           /* largest optional header we keep */

#define F_RELFLG        0x0001  /* relocation info stripped: absolute file */
#define STYP_BLOCK      0x0400  /* block data section */

/* little-endian field of the byte-reversed image */
#define LE32(p) ((unsigned long)(p)[0] | ((unsigned long)(p)[1] << 8) | \
                 ((unsigned long)(p)[2] << 16) | ((unsigned long)(p)[3] << 24))

static FILE *ifile;

static unsigned char filhdr[FILHSZ];
static unsigned char aouthdr[OPTMAX];   /* optional header, absolute file */
static unsigned char lnkhdr[OPTMAX];    /* optional header, relocatable file */
static long nscns, nsyms, symptr, scnptr;
static int absfile;
static int dwidth, awidth;              /* digits of a data word, address */
static long strtablen;
static char *strtab;
static unsigned long f_magic;
static int cursym = 777;                /* memory space of last _SYMBOL line */

struct cmt {
    long scnum;                         /* section the comment belongs to */
    long offset;                        /* string table offset */
    struct cmt *next;
};
static struct cmt *cmtlist, *cmtnext;

/* memory space names of the _SYMBOL records, indexed by memory space */
static char *symspace[0x11d] = {
    "P", "X", "Y", "L", "N", "LAA", "LAB", "LBA", "LBB", "LE", "LI",
    "PA", "PB", "PE", "PI", "PR", "XA", "XB", "XE", "XI", "XR",
    "YA", "YB", "YE", "YI", "YR", "PT", "PF", "EM"
};
static char enames[256][5];             /* "E0" .. "E255" */

static long s32(unsigned long v)
{
    v &= 0xffffffffUL;
    if (v & 0x80000000UL)
        return -(long)(~v & 0x7fffffffUL) - 1;
    return (long)v;
}

static void onintr(int sig)
{
    (void)sig;
    exit(1);
}

static void error(char *fmt, ...)
{
    va_list ap;
    int err;

    err = errno;
    fprintf(stderr, "cldlod: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    if (err != 0) {
        errno = err;
        perror("cldlod");
    }
    exit(1);
}

static void out(char *fmt, ...)
{
    va_list ap;
    int n;

    va_start(ap, fmt);
    n = vfprintf(stdout, fmt, ap);
    va_end(ap);
    if (n < 0)
        error("cannot write to output file");
}

/* reverse every 32-bit word of a buffer */
static void swapw(unsigned char *p, unsigned long size, unsigned long n)
{
    unsigned char *end, c;

    end = p + ((size * n) & ~3UL);
    for (; p < end; p += 4) {
        c = p[0]; p[0] = p[3]; p[3] = c;
        c = p[1]; p[1] = p[2]; p[2] = c;
    }
}

/* fread and reverse the words, as the PC version did */
static size_t freads(void *buf, size_t size, size_t n, FILE *fp)
{
    size_t r;

    r = fread(buf, size, n, fp);
    swapw((unsigned char *)buf, (unsigned long)size, (unsigned long)n);
    return r;
}

/* undo the reversal of an 8-character in-line name */
static void fixname(unsigned char *p)
{
    if (LE32(p) != 0)
        swapw(p, 4, 2);
}

static void read_headers(void)
{
    long opthdr;
    size_t rdlen;

    if (freads(filhdr, FILHSZ, 1, ifile) != 1)
        error("cannot read file header");
    nscns = s32(LE32(filhdr + 4));
    nsyms = s32(LE32(filhdr + 16));
    symptr = s32(LE32(filhdr + 12));
    absfile = (LE32(filhdr + 24) & F_RELFLG) != 0;
    f_magic = LE32(filhdr);
    switch (f_magic) {
    case 0x2c5: dwidth = 6; awidth = 4; break;
    case 0x2c6: awidth = 8; dwidth = 8; break;
    case 0x2c7: awidth = 4; dwidth = 4; break;
    case 0x2c8: awidth = 6; dwidth = 6; break;
    case 0x2ca: dwidth = 6; awidth = 4; break;
    case 0x2c9: awidth = 4; dwidth = 4; break;
    case 0x2cb: dwidth = 4; awidth = 8; break;
    case 0x2cc: dwidth = 4; awidth = 8; break;
    default:
        error("Header has a bad magic number");
    }
    opthdr = s32(LE32(filhdr + 20));
    rdlen = (size_t)(opthdr > OPTMAX ? OPTMAX : opthdr);
    if (opthdr != 0) {
        if (!absfile) {
            if (freads(lnkhdr, rdlen, 1, ifile) != 1)
                error("cannot read linker file header");
            /*
             * The original read the linker header into a 40-byte buffer
             * followed by nsyms, the string table pointer and symptr.  The
             * linker header of a relocatable file is 56 bytes, so these were
             * always overwritten; keep that behaviour.
             */
            if (opthdr >= 0x2c)
                nsyms = s32(LE32(lnkhdr + 0x28));
            if (opthdr >= 0x34)
                symptr = s32(LE32(lnkhdr + 0x30));
        } else {
            if (freads(aouthdr, rdlen, 1, ifile) != 1)
                error("cannot read optional file header");
            /* same for an optional header longer than 60 bytes */
            if (opthdr >= 0x40)
                absfile = LE32(aouthdr + 0x3c) != 0;
            if (opthdr >= 0x44)
                dwidth = (int)s32(LE32(aouthdr + 0x40));
        }
    }
    scnptr = opthdr + FILHSZ;
}

static void read_strtab(void)
{
    long pos;
    unsigned char len[4];
    size_t r;

    pos = symptr + nsyms * SYMESZ;
    if (fseek(ifile, pos, SEEK_SET) != 0)
        error("cannot seek to string table length");
    r = freads(len, 4, 1, ifile);
    if (r != 1 && !feof(ifile))
        error("cannot read string table length");
    if (feof(ifile)) {
        strtablen = 0;
        return;
    }
    strtablen = s32(LE32(len));
    if (strtablen != 0) {
        strtablen -= 4;
        strtab = (char *)malloc((size_t)strtablen);
        if (strtab == NULL)
            error("cannot allocate string table");
        if (fseek(ifile, pos + 4, SEEK_SET) != 0)
            error("cannot seek to string table");
        if (fread(strtab, (size_t)strtablen, 1, ifile) != 1)
            error("cannot read string table");
    }
}

/* _START record: module name line from the .cmt symbol of section -1 */
static void do_start(void)
{
    unsigned char sym[SYMESZ];
    long i, off, pos;
    char *p, *q;

    off = -0x2c5;
    if (fseek(ifile, symptr, SEEK_SET) != 0)
        error("cannot seek to symbol table");
    for (i = 0; i < nsyms; i++) {
        if (freads(sym, SYMESZ, 1, ifile) != 1)
            error("cannot read symbol table entry %d", (int)i);
        fixname(sym);
        if (strcmp((char *)sym, ".cmt") == 0 && s32(LE32(sym + 16)) == -1 &&
            LE32(sym + 24) == 0 && LE32(sym + 20) == 0) {
            off = s32(LE32(sym + 8));
            break;
        }
    }
    out("_START ");
    if (off < 0 || strtablen == 0) {
        out("\n\n");
        return;
    }
    p = strtab;
    pos = 4;
    do {
        size_t n;

        if (pos == off)
            break;
        n = strlen(p);
        pos += (long)n + 1;
        p += n + 1;
    } while (p < strtab + strtablen);
    q = strchr(p, ';');
    if (q == NULL)
        out("%s\n\n", p);
    else {
        *q = '\0';
        out("%s\n", p);
        *q = ';';
        out("%s\n", q);
    }
}

/* collect the .cmt comment symbols that belong to sections */
static void read_comments(void)
{
    unsigned char sym[SYMESZ], aux[SYMESZ];
    struct cmt *c, *last;
    long i, j, numaux, symno;

    if (fseek(ifile, symptr, SEEK_SET) != 0)
        error("cannot seek to symbol table");
    last = NULL;
    i = 0;
    while (i < nsyms) {
        if (freads(sym, SYMESZ, 1, ifile) != 1)
            error("cannot read symbol table entry %d", (int)i);
        fixname(sym);
        if (strcmp((char *)sym, ".cmt") == 0 && s32(LE32(sym + 16)) != -1 &&
            LE32(sym + 24) == 0 && LE32(sym + 20) == 0) {
            c = (struct cmt *)malloc(sizeof(struct cmt));
            if (c == NULL)
                error("cannot allocate comment record");
            c->scnum = s32(LE32(sym + 16));
            c->offset = s32(LE32(sym + 8));
            c->next = NULL;
            if (cmtlist == NULL)
                cmtlist = c;
            else
                last->next = c;
            last = c;
        }
        numaux = s32(LE32(sym + 28));
        symno = i;
        for (j = 0, i++; j < numaux; j++, i++)
            if (freads(aux, SYMESZ, 1, ifile) != 1)
                error("cannot read auxiliary entry %d for symbol entry %d",
                      (int)j, (int)symno);
    }
    cmtnext = cmtlist;
}

/* emit the comments of all sections up to scn (the original loops forever
   on a comment with a section number <= 0; that is kept) */
static void do_comments(long scn)
{
    while (cmtnext != NULL && cmtnext->scnum <= scn) {
        if (cmtnext->scnum > 0) {
            out("_COMMENT\n");
            if ((unsigned long)cmtnext->offset < 4 || cmtnext->offset > strtablen)
                error("invalid string table offset for comment");
            out("%s\n", strtab - 4 + cmtnext->offset);
            cmtnext = cmtnext->next;
        }
    }
}

static char *scn_name(unsigned char *scn)
{
    long off;

    if (LE32(scn) != 0)
        return (char *)scn;
    off = s32(LE32(scn + 4));
    if ((unsigned long)off < 4 || off > strtablen)
        error("invalid string table offset for section header name");
    return strtab - 4 + off;
}

static void do_section(unsigned char *scn)
{
    long mem, size, flags, i;
    unsigned long addr, blksize;
    char *name, *space;
    unsigned char *raw, *p;
    char ebuf[8];

    if (LE32(scn + 28) == 0 || LE32(scn + 24) == 0)
        return;
    mem = s32(LE32(scn + 12));
    name = scn_name(scn);
    flags = s32(LE32(scn + 48));
    size = s32(LE32(scn + 24));
    addr = LE32(scn + 8);
    blksize = LE32(scn + 16);

    space = NULL;
    switch (mem) {
    case 0: space = "P"; break;
    case 1: space = "X"; break;
    case 2: space = "Y"; break;
    case 3: space = "L"; break;
    case 5: space = "LAA"; break;
    case 6: space = "LAB"; break;
    case 7: space = "LBA"; break;
    case 8: space = "LBB"; break;
    case 9: space = "LE"; break;
    case 10: space = "LI"; break;
    case 11: space = "PA"; break;
    case 12: space = "PB"; break;
    case 13: space = "PE"; break;
    case 14: space = "PI"; break;
    case 15: space = "PR"; break;
    case 16: space = "XA"; break;
    case 17: space = "XB"; break;
    case 18: space = "XE"; break;
    case 19: space = "XI"; break;
    case 20: space = "XR"; break;
    case 21: space = "YA"; break;
    case 22: space = "YB"; break;
    case 23: space = "YE"; break;
    case 24: space = "YI"; break;
    case 25: space = "YR"; break;
    case 0x1c: space = "EM"; break;
    case 0x11d: space = "DM"; break;
    }
    if (space == NULL) {
        if (f_magic == 0x2ca && mem == 0x1e && (flags & 0x800) && !(flags & 0x4000))
            mem = 0x1d;
        if (mem < 0x1d || mem > 0x11c)
            space = "<ERROR>";
        else {
            sprintf(ebuf, "E%d", (int)(mem - 0x1d));
            space = ebuf;
        }
    }

    raw = (unsigned char *)malloc((size_t)size * 4);
    if (raw == NULL)
        error("cannot allocate raw data for section %s", name);
    if (fseek(ifile, s32(LE32(scn + 28)), SEEK_SET) != 0)
        error("cannot seek to raw data in section %s", name);
    if (freads(raw, (size_t)size, 4, ifile) != 4)
        error("cannot read raw data in section %s", name);

    p = raw;
    if (!(flags & STYP_BLOCK)) {
        out("_DATA %s %01.*lX\n", space, awidth, addr);
        i = 0;
        while (i < size) {
            if (*space == 'L') {
                out("%01.*lX %01.*lX ", dwidth, LE32(p + 4), dwidth, LE32(p));
                p += 8;
                i += 2;
            } else {
                out("%01.*lX ", dwidth, LE32(p));
                p += 4;
                i++;
            }
            if (i % 8 == 0 && i < size)
                out("\n");
        }
        out("\n");
    } else if (*space == 'L') {
        out("_BLOCKDATA Y %01.*lX %01.*lX %01.*lX\n", awidth, addr, awidth, blksize,
            dwidth, LE32(p));
        out("_BLOCKDATA X %01.*lX %01.*lX %01.*lX\n", awidth, addr, awidth, blksize,
            dwidth, LE32(p + 4));
    } else
        out("_BLOCKDATA %s %01.*lX %01.*lX %01.*lX\n", space, awidth, addr,
            awidth, blksize, dwidth, LE32(p));
}

static void do_sections(void)
{
    unsigned char scn[SCNHSZ];
    long i;

    for (i = 0; i < nscns; i++) {
        if (fseek(ifile, scnptr, SEEK_SET) != 0)
            error("cannot seek to section headers");
        if (freads(scn, SCNHSZ, 1, ifile) != 1)
            error("cannot read section headers");
        fixname(scn);
        scnptr += SCNHSZ;
        do_comments(i + 1);
        do_section(scn);
    }
}

/* build an IEEE double from its two 32-bit halves without host tricks */
static double mkdouble(unsigned long hi, unsigned long lo)
{
    int exp;
    double m;

    exp = (int)((hi >> 20) & 0x7ff);
    m = (double)(hi & 0xfffffUL) * 4294967296.0 + (double)(lo & 0xffffffffUL);
    if (exp == 0) {
        m = m / 4503599627370496.0;             /* denormal: 0.f * 2^-1022 */
        exp = 1;
    } else
        m = 1.0 + m / 4503599627370496.0;       /* 1.f, f scaled by 2^-52 */
    m = ldexp(m, exp - 1023);
    return (hi & 0x80000000UL) ? -m : m;
}

/* print like MSVC's %-.6E: always at least three exponent digits */
static void out_double(double d)
{
    char buf[64], *e;
    int n;

    sprintf(buf, "%-.6E", d);
    e = strchr(buf, 'E');
    if (e != NULL && (e[1] == '+' || e[1] == '-')) {
        n = (int)strlen(e + 2);
        if (n < 3) {
            memmove(e + 2 + (3 - n), e + 2, (size_t)n + 1);
            memset(e + 2, '0', (size_t)(3 - n));
        }
    }
    out("%s\n", buf);
}

static void do_symbol(unsigned char *sym)
{
    char *name, kind;
    long scnum, sclass, mem;
    unsigned long type, base;
    int prev;

    kind = 'I';
    if (LE32(sym) == 0) {
        long off = s32(LE32(sym + 4));

        if ((unsigned long)off < 4 || off > strtablen)
            error("invalid string table offset for symbol table entry %d name", 0);
        name = strtab - 4 + off;
    } else {
        swapw(sym, 4, 2);
        name = (char *)sym;
    }
    if (*name == '.')
        return;

    scnum = s32(LE32(sym + 16));
    type = LE32(sym + 20);
    sclass = s32(LE32(sym + 24));
    if ((type & 0x30) != 0x20) {
        if (!((sclass >= -1 && sclass <= 20) || (sclass >= 100 && sclass <= 106))) {
            base = type & 0x1000fUL;
            if (base >= 6 && base <= 7)
                kind = 'F';
        }
    }
    if ((strcmp(name, "etext") == 0 && scnum == -1 && type == 0 && sclass == 2) ||
        (strcmp(name, "end") == 0 && scnum == -1 && type == 0 && sclass == 2))
        return;

    prev = cursym;
    if (scnum < 1 && (type & 0x30) != 0x10)
        mem = 4;
    else
        mem = s32(LE32(sym + 12));
    if (mem >= 0 && mem < 0x11d) {
        cursym = (int)mem;
        if (prev != cursym)
            out("_SYMBOL %s\n", symspace[cursym]);
        out("%-19s  %c ", name, kind);
        if (kind == 'F')
            out_double(mkdouble(LE32(sym + 12), LE32(sym + 8)));
        else
            out("%01.*lX\n", dwidth, LE32(sym + 8));
    }
}

static void do_symbols(void)
{
    unsigned char sym[SYMESZ], aux[SYMESZ];
    long i, j, numaux, symno;

    if (fseek(ifile, symptr, SEEK_SET) != 0)
        error("cannot seek to symbol table");
    i = 0;
    while (i < nsyms) {
        if (freads(sym, SYMESZ, 1, ifile) != 1)
            error("cannot read symbol table entry %d", (int)i);
        do_symbol(sym);
        numaux = s32(LE32(sym + 28));
        symno = i;
        for (j = 0, i++; j < numaux; j++, i++)
            if (freads(aux, SYMESZ, 1, ifile) != 1)
                error("cannot read auxiliary entry %d for symbol entry %d",
                      (int)j, (int)symno);
    }
}

static void cldlod(void)
{
    read_headers();
    if (symptr != 0 && nsyms != 0) {
        read_strtab();
        do_start();
        read_comments();
    }
    do_sections();
    if (symptr != 0 && nsyms != 0)
        do_symbols();
    out("\n_END %01.*lX\n", awidth, LE32(aouthdr + 20));
}

int main(int argc, char **argv)
{
    int i;

    for (i = 0; i < 256; i++)
        sprintf(enames[i], "E%d", i);
    enames[9][2] = ' ';                 /* the original table has "E9 " */
    enames[9][3] = '\0';
    for (i = 0; i < 256; i++)
        symspace[0x1d + i] = enames[i];

    signal(SIGINT, onintr);
    if (argc != 2) {
        fprintf(stderr, "Version 6.3 usage: cldlod cldfile > lodfile\n");
        exit(-1);
    }
    ifile = fopen(argv[1], "rb");
    if (ifile == NULL)
        error("cannot open input file %s", argv[1]);
    cldlod();
    fclose(ifile);
    exit(0);
    return 0;
}
