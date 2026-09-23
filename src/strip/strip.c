/*
 * strip - remove symbol and line number information from DSP COFF
 *         absolute files
 *
 * Reconstructed from Motorola STRIP.EXE, "DSP COFF File Strip Utility"
 * Version 6.3 (CLAS56 v6.3, 1999); strip.c,v 1.23 1999/03/19.
 *
 * The file header, optional header, section headers and raw data are
 * copied; the symbol count and the relocation/line number counts of the
 * sections are cleared and raw data pointers are recomputed.  Like the
 * original, the headers are read with every 32-bit word reversed (the PC
 * byte order), edited as little-endian images and reversed again on output,
 * so the output is identical on any host.
 *
 * Deviations: the original called a Macintosh file type/creator stub
 * ("COFF"/"MPS ") for the output file; it does nothing elsewhere and is
 * omitted.  Temporary names come from tmpnam() with the directory part
 * removed ('/' is accepted as separator as well as '\\' and ':').
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>

#define FILHSZ  0x1c
#define SCNHSZ  0x34
#define OPTMAX  0x100

#define F_RELFLG        0x0001
#define F_LNNO          0x0004

#define LE32(p) ((unsigned long)(p)[0] | ((unsigned long)(p)[1] << 8) | \
                 ((unsigned long)(p)[2] << 16) | ((unsigned long)(p)[3] << 24))

static char *progname = "strip";
static char *optarg_;                   /* getopt argument */
static int optind_;                     /* getopt index */
static char *optnext;                   /* next option character */
static char *ifn, *ofn, *tfn;           /* input, output, temporary name */
static FILE *ifp, *ofp;
static int quiet;

static void put32(unsigned char *p, unsigned long v)
{
    p[0] = (unsigned char)(v & 0xff);
    p[1] = (unsigned char)((v >> 8) & 0xff);
    p[2] = (unsigned char)((v >> 16) & 0xff);
    p[3] = (unsigned char)((v >> 24) & 0xff);
}

static long s32(unsigned long v)
{
    v &= 0xffffffffUL;
    if (v & 0x80000000UL)
        return -(long)(~v & 0x7fffffffUL) - 1;
    return (long)v;
}

static void error(char *fmt, ...)
{
    va_list ap;
    int err;

    err = errno;
    fprintf(stderr, "%s: ", progname);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    if (err != 0) {
        errno = err;
        perror(progname);
    }
    if (ofn != NULL)
        remove(ofn);
    exit(1);
}

static void onsig(int sig)
{
    if (sig == SIGINT) {
        fprintf(stderr, "\n%s: Interrupted\n", progname);
        exit(1);
    } else if (sig == SIGSEGV) {
        fprintf(stderr, "%s: Fatal segmentation or protection fault; contact your tools vendor\n",
                progname);
        exit(1);
    }
}

static void usage(void)
{
    if (quiet)
        fprintf(stderr, "%s  %s\n%s\n", "DSP COFF File Strip Utility", "Version 6.3 ",
                "(C) Copyright Motorola, Inc. 1991-1996.  All rights reserved.");
    fprintf(stderr, "Usage:  %s [-q] files\n", progname);
    fprintf(stderr, "        q - do not display signon banner\n");
    exit(1);
}

/* is option letter c (any case) present anywhere on the command line? */
static char *findopt(int c, int argc, char **argv)
{
    char *p;
    int ch;

    for (;;) {
        do {
            argv++;
            if (--argc < 1)
                return NULL;
        } while (**argv != '-');
        for (p = *argv + 1; *p != '\0'; p++) {
            ch = isupper((unsigned char)*p) ? tolower((unsigned char)*p) : *p;
            if (ch == c)
                return *argv;
        }
    }
}

static int getopt_(int argc, char **argv, char *opts)
{
    int c;
    char *p;

    optarg_ = NULL;
    if (optnext == NULL || *optnext == '\0') {
        if (optind_ == 0)
            optind_ = 1;
        if (optind_ >= argc || argv[optind_][0] != '-' || argv[optind_][1] == '\0') {
            optarg_ = NULL;
            return -1;
        }
        if (strcmp(argv[optind_], "--") == 0) {
            optind_++;
            return -1;
        }
        optnext = argv[optind_] + 1;
        optind_++;
    }
    c = *optnext++;
    p = strchr(opts, c);
    if (p == NULL || c == ':') {
        fprintf(stderr, "%s: unknown option -%c\n", progname, c);
        return '?';
    }
    if (p[1] == ':') {
        if (*optnext == '\0') {
            if (optind_ >= argc) {
                fprintf(stderr, "%s: -%c argument missing\n", progname, c);
                return '?';
            }
            optarg_ = argv[optind_++];
        } else {
            optarg_ = optnext;
            optnext = NULL;
        }
    }
    return c;
}

/* file name part of a path */
static char *basename_(char *path)
{
    char *p;

    if (path == NULL)
        return NULL;
    for (p = path + strlen(path); p >= path && *p != '\\' && *p != ':' && *p != '/'; p--)
        ;
    if (p >= path)
        path = p + 1;
    return path;
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

static size_t freads(void *buf, size_t size, size_t n, FILE *fp)
{
    size_t r;

    r = fread(buf, size, n, fp);
    swapw((unsigned char *)buf, (unsigned long)size, (unsigned long)n);
    return r;
}

static size_t fwrites(void *buf, size_t size, size_t n, FILE *fp)
{
    swapw((unsigned char *)buf, (unsigned long)size, (unsigned long)n);
    return fwrite(buf, size, n, fp);
}

static void strip(void)
{
    unsigned char fhdr[FILHSZ], opt[OPTMAX];
    unsigned char *oldscn, *newscn, *s, *raw;
    unsigned long flags;
    long opthdr, nscns, pos, size, i;

    if (freads(fhdr, FILHSZ, 1, ifp) != 1)
        error("cannot read file header");
    errno = 0;
    flags = LE32(fhdr + 24);
    if (!(flags & F_RELFLG))
        error("invalid object file type");
    if (LE32(fhdr + 16) == 0)
        error("%s: already stripped", ifn);
    put32(fhdr + 24, flags | F_LNNO);
    put32(fhdr + 16, 0L);
    opthdr = s32(LE32(fhdr + 20));
    nscns = s32(LE32(fhdr + 4));
    if (fwrites(fhdr, FILHSZ, 1, ofp) != 1)
        error("cannot write file header");
    if (opthdr != 0) {
        if (opthdr > OPTMAX)
            error("cannot read optional header");
        if (freads(opt, (size_t)opthdr, 1, ifp) != 1)
            error("cannot read optional header");
        if (fwrites(opt, (size_t)opthdr, 1, ofp) != 1)
            error("cannot read optional header");
    }

    oldscn = (unsigned char *)malloc((size_t)(nscns * SCNHSZ));
    if (oldscn == NULL)
        error("cannot allocate section headers");
    newscn = (unsigned char *)malloc((size_t)(nscns * SCNHSZ));
    if (newscn == NULL)
        error("cannot allocate new section headers");
    if (fseek(ifp, opthdr + FILHSZ, SEEK_SET) != 0)
        error("cannot seek to section headers");
    if (freads(oldscn, (size_t)(nscns * SCNHSZ), 1, ifp) != 1)
        error("cannot read section headers");
    memcpy(newscn, oldscn, (size_t)(nscns * SCNHSZ));

    pos = opthdr + FILHSZ + nscns * SCNHSZ;
    for (i = 0, s = newscn; i < nscns; i++, s += SCNHSZ) {
        if (LE32(s + 0x1c) != 0) {              /* s_scnptr */
            put32(s + 0x1c, (unsigned long)pos);
            pos += s32(LE32(s + 0x18)) * 4;     /* s_size in words */
        }
        put32(s + 0x28, 0L);                    /* s_nreloc */
        put32(s + 0x2c, 0L);                    /* s_nlnno */
    }
    if (fwrites(newscn, (size_t)(nscns * SCNHSZ), 1, ofp) != 1)
        error("cannot write section headers");
    free(newscn);

    for (i = 0, s = oldscn; i < nscns; i++, s += SCNHSZ) {
        size = s32(LE32(s + 0x18));
        if (LE32(s + 0x1c) == 0 || size == 0)
            continue;
        raw = (unsigned char *)malloc((size_t)size * 4);
        if (raw == NULL)
            error("cannot allocate raw data");
        if (fseek(ifp, s32(LE32(s + 0x1c)), SEEK_SET) != 0)
            error("cannot seek to raw data");
        if (freads(raw, (size_t)size, 4, ifp) != 4)
            error("cannot read raw data ");
        if (fwrites(raw, (size_t)size, 4, ofp) != 4)
            error("cannot write raw data");
        free(raw);
    }
    free(oldscn);
}

int main(int argc, char **argv)
{
    char obuf[L_tmpnam], tbuf[L_tmpnam];
    int c;

    signal(SIGINT, onsig);
    signal(SIGSEGV, onsig);
    quiet = findopt('q', argc, argv) != NULL;
    if (!quiet)
        fprintf(stderr, "%s  %s\n%s\n", "DSP COFF File Strip Utility", "Version 6.3 ",
                "(C) Copyright Motorola, Inc. 1991-1996.  All rights reserved.");
    while ((c = getopt_(argc, argv, "Qq")) != -1) {
        if (isupper(c))
            c = tolower(c);
        if (c == 'q')
            quiet = 1;
        else
            usage();
    }
    if (optind_ >= argc)
        usage();

    if (argv[optind_][0] == '-') {
        /* filter mode: stdin to stdout (text mode streams on some hosts) */
        ifn = "stdin";
        ifp = stdin;
        ofp = stdout;
        /* the original set the output name to "stdout", so an error removed
           a file of that name from the current directory; not repeated */
        ofn = NULL;
        strip();
    } else {
        while (optind_ < argc) {
            ifn = argv[optind_++];
            ifp = fopen(ifn, "rb");
            if (ifp == NULL)
                error("cannot open input file %s", ifn);
            ofn = basename_(tmpnam(obuf));
            if (ofn == NULL)
                error("cannot create output file name");
            ofp = fopen(ofn, "wb");
            if (ofp == NULL)
                error("cannot open output file %s", ofn);
            strip();
            fclose(ifp);
            fclose(ofp);
            tfn = basename_(tmpnam(tbuf));
            if (tfn == NULL)
                error("cannot create temporary file name");
            if (rename(ifn, tfn) != 0)
                error("cannot rename input file %s", ifn);
            if (rename(ofn, ifn) != 0) {
                if (rename(tfn, ifn) != 0)
                    error("cannot undo rename of %s to %s", ifn, tfn);
                error("cannot rename output file %s", ofn);
            }
            if (remove(tfn) != 0)
                error("cannot remove renamed input file %s", tfn);
        }
    }
    exit(0);
    return 0;
}
