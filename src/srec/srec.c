/*
 * srec - convert DSP COFF load files (.cld) or ASCII load files (.lod) to
 *        Motorola S-records
 *
 * Reconstructed from Motorola SREC.EXE, "DSP S-Record Conversion Utility"
 * Version 6.3 (CLAS56 v6.3, 1999).
 * Module revision: $Id: srec.c,v 1.49 1999/03/19 19:51:41 jay Exp $
 *
 * Every DSP word is written as a string of hex byte pairs; by default the
 * bytes of a word are reversed (low byte first), -r keeps them in order.
 * One output file per memory space (base.p, base.x, ...), -s puts all of
 * them into base.s and -m writes one file per byte lane (base.p2 .. base.p0).
 *
 * Notes on the reconstruction:
 * - The COFF file is big-endian; the header fields are decoded byte by byte
 *   (the original read raw structures and reversed each 32-bit word).
 * - All the state lives in globals exactly as in the original; several
 *   routines depend on the "current word size" (wsize) left behind by the
 *   previous one, and on values that carry over from one input file to the
 *   next.  That is kept on purpose, because it shows in the output.
 * - The original also had a Macintosh variant (file name list instead of
 *   argv, setting the file type of the outputs to 'TEXT'/'MPS '); the
 *   dead code for it is left out.
 * - Addresses are 32-bit values held in unsigned long and masked, so hosts
 *   with a 64-bit long give the same results.
 * - Where the original overran its buffers (very long START lines, an
 *   optional header longer than 64 + 0x420 bytes, block sections of more
 *   than 3 words, -m word size mismatches on the 56600) or used
 *   uninitialised data (base name for stdin input), this version stays
 *   within bounds; see the comments at those places.  A 56600 file with
 *   -p for another processor divides by zero like the original.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>

#define FILHSZ  0x1c            /* COFF file header */
#define SCNHSZ  0x34            /* COFF section header */
#define AOUTMAX 0x40            /* optional header bytes kept */

#define M32     0xffffffffUL

/* memory space ("lane") numbers used throughout */
#define MX      0
#define MY      1
#define ML      2
#define MP      3
#define ME      4
#define MD      5

/* one S-record output file; the original struct was 0x5c bytes with an
   80-byte data buffer (at most 64 hex characters are ever collected) */
struct srec {
    FILE *fp;
    long sum;                   /* checksum of the data bytes */
    char *ptr;                  /* end of the collected data */
    char data[0x50];
};

static char *progname = "srec";
static int lineno = 1;                  /* line of the .lod file */
static int s0len = 3;                   /* S0 record length byte */
static char memchars[] = "xylpedXYLPED";

static char banner1[] = "DSP S-Record Conversion Utility";
static char banner2[] = "Version 6.3 ";
static char banner3[] = "(C) Copyright Motorola, Inc. 1987-1996.  All rights reserved.";

static unsigned long magic;             /* COFF header of the last .cld file */
static long nscns, opthdr;
static unsigned long f_flags;
static unsigned char aouthdr[AOUTMAX];

/*
 * S0 record and the hex module name it is built from.  The original had
 * 0x420 and 0x200 bytes here; since the name is taken from the previous S0
 * record for every further .cld file (see make_s0), it grows with each input
 * file and would eventually overflow.  The buffers are larger here.
 */
static char s0name[0x1000];
static char s0rec[0x1000 + 0x20];

static char *optarg_;
static int optind_;
static char *nextchar;

static char *basename_;                 /* input file name without extension */
static FILE *ifp;
static int ftype;                       /* 1 = .lod, 2 = .cld, 0/-1 unknown */

static int sflag, mflag, rflag, uflag, bflag, wflag, lflag, qflag, xflag, cflag;

static char tok[0x208];                 /* token / first word (0x200 + slop) */
static char word2[0x200];               /* second word */
static char line[0x200];                /* START line, output line */
static char noaddr[1];                  /* empty END address */

static int lastseg;                     /* -s: segment of the last S0 record */
static long s0sum;                      /* sum of the module name characters */
static int machine;                     /* processor type, 0 = not yet known */
static int wsize;                       /* bytes in the current word */
static int esize;                       /* 56600 E memory word size */
static int psize;                       /* P (and L) memory word size */
static int e56600;                      /* 56600 section flag 0x4000 */
static int xysize;                      /* X/Y memory word size */
static int alen, alen1;                 /* S-record address bytes (+1) */
static unsigned long cmask, pmask, xymask, amask;
static int aopt, topt;                  /* -a and -t values */
static char *cfmt, *pfmt, *xyfmt, *afmt, *dfmt, *efmt;
static struct srec *srecs[6];
static int nrecs[6];                    /* files opened for each */
static unsigned long offset[6];         /* -o offsets per memory space */
static unsigned int hexv;               /* sscanf target of put_bytes */

/*
 * The original classified the characters of strings through MSVC's ctype
 * table indexed with the sign-extended char, so bytes 0x80-0xff read the
 * 256 bytes in front of the table (the program's own message strings).
 * These are those values; only the _SPACE (8) and _HEX (0x80) bits matter
 * (e.g. 0xe9 counts as white space in a START record).
 */
static unsigned short negctype[128] = {
    0x676e, 0x656c, 0x6f20, 0x7475, 0x7570, 0x2074, 0x6966, 0x656c,
    0x000a, 0x2020, 0x2020, 0x2020, 0x2020, 0x2074, 0x202d, 0x743c,
    0x656c, 0x3e6e, 0x7420, 0x7261, 0x6567, 0x2074, 0x6f77, 0x6472,
    0x6c20, 0x6e65, 0x7467, 0x0a68, 0x0000, 0x2020, 0x2020, 0x2020,
    0x2020, 0x2075, 0x202d, 0x6572, 0x6576, 0x7372, 0x2065, 0x6f77,
    0x6472, 0x2073, 0x6e69, 0x4c20, 0x6d20, 0x6d65, 0x726f, 0x0a79,
    0x0000, 0x2020, 0x2020, 0x2020, 0x2020, 0x2077, 0x202d, 0x6f77,
    0x6472, 0x6120, 0x6464, 0x6572, 0x7373, 0x6e69, 0x0a67, 0x0000,
    0x0000, 0x2020, 0x2020, 0x2020, 0x2020, 0x2078, 0x202d, 0x6f63,
    0x766e, 0x7265, 0x2074, 0x204c, 0x6572, 0x6f63, 0x6472, 0x2073,
    0x6f74, 0x5820, 0x6120, 0x646e, 0x5920, 0x000a, 0x0000, 0x7325,
    0x203a, 0x7461, 0x6c20, 0x6e69, 0x2065, 0x6425, 0x203a, 0x7325,
    0x000a, 0x7325, 0x203a, 0x7325, 0x000a, 0x7325, 0x203a, 0x7461,
    0x6c20, 0x6e69, 0x2065, 0x6425, 0x203a, 0x0000, 0x0000, 0x7325,
    0x203a, 0x0000, 0x0000, 0x000a, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0xf0ba, 0x0040, 0xf0ba, 0x0040, 0x0000
};

static int cspace(char ch)
{
    int c = (unsigned char)ch;

    return c & 0x80 ? (negctype[c - 0x80] & 8) != 0 : isspace(c);
}

static int cxdigit(char ch)
{
    int c = (unsigned char)ch;

    return c & 0x80 ? (negctype[c - 0x80] & 0x80) != 0 : isxdigit(c);
}

static unsigned long be32(unsigned char *p)
{
    return ((unsigned long)p[0] << 24) | ((unsigned long)p[1] << 16) |
           ((unsigned long)p[2] << 8) | (unsigned long)p[3];
}

static long s32(unsigned long v)
{
    v &= M32;
    if (v & 0x80000000UL)
        return -(long)(~v & 0x7fffffffUL) - 1;
    return (long)v;
}

static void usage(void)
{
    if (qflag)
        fprintf(stderr, "%s  %s\n%s\n", banner1, banner2, banner3);
    fprintf(stderr, "Usage:  %s [-blmqrsuwx] [-a <alen>] [-o <mem>:<offset>] [-p <procno>] [-t <tlen>] <input file ... >\n", progname);
    fprintf(stderr, "        a - <alen> S-record address length\n");
    fprintf(stderr, "        b - byte addressing\n");
    fprintf(stderr, "        c - truncate words to bytes\n");
    fprintf(stderr, "        l - long (double-word) addressing\n");
    fprintf(stderr, "        m - multiple output files\n");
    fprintf(stderr, "        o - add <offset> to <mem> addresses\n");
    fprintf(stderr, "        p - <procno> load file format\n");
    fprintf(stderr, "        q - do not display signon banner\n");
    fprintf(stderr, "        r - reverse bytes in word\n");
    fprintf(stderr, "        s - single output file\n");
    fprintf(stderr, "        t - <tlen> target word length\n");
    fprintf(stderr, "        u - reverse words in L memory\n");
    fprintf(stderr, "        w - word addressing\n");
    fprintf(stderr, "        x - convert L records to X and Y\n");
    exit(-1);
}

static void error(char *msg)
{
    if (ftype == 1)
        fprintf(stderr, "%s: at line %d: %s\n", progname, lineno, msg);
    else
        fprintf(stderr, "%s: %s\n", progname, msg);
    exit(-1);
}

static void error2(char *fmt, char *arg)
{
    if (ftype == 1)
        fprintf(stderr, "%s: at line %d: ", progname, lineno);
    else
        fprintf(stderr, "%s: ", progname);
    fprintf(stderr, fmt, arg);
    fprintf(stderr, "\n");
    exit(-1);
}

static void onsig(int sig)
{
    if (sig == SIGINT) {
        fprintf(stderr, "\n%s: Interrupted\n", progname);
        exit(-1);
    } else if (sig == SIGSEGV) {
        fprintf(stderr, "%s: Fatal segmentation or protection fault; contact your tools vendor\n", progname);
        exit(-1);
    }
}

/* ---------------------------------------------------------------- helpers */

/*
 * File name part of a path.  DOS separators only, as in the original: this
 * decides where set_ext() puts the extension, so it is kept for file names.
 */
static char *basename(char *path)
{
    size_t i;

    if (path == NULL)
        return NULL;
    i = strlen(path);
    for (;;) {
        if (path[i] == '\\' || path[i] == ':')
            return path + i + 1;
        if (i == 0)
            return path;
        i--;
    }
}

static char *upcase(char *s)
{
    char *p;

    for (p = s; *p != '\0'; p++)
        if (islower((unsigned char)*p))
            *p = (char)toupper((unsigned char)*p);
    return s;
}

/* token consists of hex digits only (an empty one passes as well) */
static int all_hex(void)
{
    char *p;

    for (p = tok; *p != '\0'; p++)
        if (!cxdigit(*p))
            break;
    return *p == '\0';
}

/*
 * sscanf("%lx") of a checked hex token, wrapping at 32 bits like MSVC.  A
 * token starting with byte 0xfb or 0xfd passes all_hex() but converts
 * nothing; the original then used an uninitialised local, 0 is used here.
 */
static unsigned long hexval(char *s)
{
    unsigned long v = 0;
    int c;

    for (; (c = (unsigned char)*s) != '\0' && isxdigit(c); s++)
        v = ((v << 4) + (unsigned long)(isdigit(c) ? c - '0' : toupper(c) - 'A' + 10)) & M32;
    return v;
}

static int bytesum(unsigned long v)
{
    int i, sum = 0;

    for (i = 0; i < 4; i++) {
        sum += (int)(v & 0xff);
        v >>= 8;
    }
    return sum;
}

/* 1 for *.lod, 2 for *.cld, 0 without extension, -1 for anything else */
static int file_type(char *name)
{
    char *base, *ext, buf[8];
    int i;

    base = basename(name);
    if (base == NULL || (ext = strrchr(base, '.')) == NULL)
        return 0;
    for (i = 0; i < 4; i++) {
        /* the original copied 4 bytes regardless; bytes after the end of
           the name never decide the comparison below */
        buf[i] = ext[i];
        if (isupper((unsigned char)buf[i]))
            buf[i] = (char)tolower((unsigned char)buf[i]);
        if (ext[i] == '\0')
            break;
    }
    for (; i < 4; i++)
        buf[i] = '\0';
    buf[4] = '\0';
    if (strncmp(buf, ".lod", 4) == 0)
        return 1;
    if (strncmp(buf, ".cld", 4) == 0)
        return 2;
    return -1;
}

/* replace (or append) the extension of name */
static char *set_ext(char *name, char *ext)
{
    char *base, *p;
    size_t len;

    base = basename(name);
    len = strlen(name);
    p = strrchr(name, '.');
    if (p == NULL || p < base)
        p = name + len;
    if (strncmp(p, ext, 4) != 0) {
        strcpy(p, ext);
        return p;
    }
    return NULL;
}

/* is there a -...q... among the arguments (checked before getopt runs) */
static char *find_opt(int c, int argc, char **argv)
{
    char *p;
    int ch;

    for (;;) {
        argv++;
        if (--argc < 1)
            return NULL;
        if (**argv != '-')
            continue;
        for (p = *argv + 1; *p != '\0'; p++) {
            ch = (unsigned char)*p;
            if (isupper(ch))
                ch = tolower(ch);
            if (ch == c)
                return *argv;
        }
    }
}

static int getopt_(int argc, char **argv, char *opts)
{
    char c, *p;

    optarg_ = NULL;
    if (nextchar == NULL || *nextchar == '\0') {
        if (optind_ == 0)
            optind_++;
        if (optind_ >= argc || argv[optind_][0] != '-' || argv[optind_][1] == '\0')
            return -1;
        if (strcmp(argv[optind_], "--") == 0) {
            optind_++;
            return -1;
        }
        nextchar = argv[optind_] + 1;
        optind_++;
    }
    c = *nextchar++;
    p = strchr(opts, c);
    if (p == NULL || c == ':') {
        fprintf(stderr, "%s: unknown option -%c\n", argv[0], c);
        return '?';
    }
    if (p[1] == ':') {
        if (*nextchar != '\0') {
            optarg_ = nextchar;
            nextchar = NULL;
        } else if (optind_ < argc) {
            optarg_ = argv[optind_];
            optind_++;
        } else {
            fprintf(stderr, "%s: -%c argument missing\n", argv[0], c);
            return '?';
        }
    }
    return c;
}

/* ------------------------------------------------------- processor setup */

static int set_machine(char *name)
{
    int type = 0;

    if (strcmp(name, "56000") == 0) {
        type = 1;
        xysize = psize = wsize = 3;
        alen = 2;
        pmask = xymask = cmask = 0xffffffUL;
        amask = 0xffffUL;
        pfmt = xyfmt = cfmt = "%06lx";
        afmt = "%04lx";
        dfmt = "S1%02lx%04lx%s%02x\n";
        efmt = "S9%02lx%s%02x\n";
    } else if (strcmp(name, "96000") == 0) {
        type = 2;
        xysize = psize = wsize = 4;
        alen = 4;
        pmask = xymask = cmask = 0xffffffffUL;
        amask = 0xffffffffUL;
        pfmt = xyfmt = cfmt = "%08lx";
        afmt = "%08lx";
        dfmt = "S3%02lx%08lx%s%02x\n";
        efmt = "S7%02lx%s%02x\n";
    } else if (strcmp(name, "100") == 0) {
        type = 7;
        xysize = psize = wsize = 2;
        alen = 4;
        pmask = xymask = cmask = 0xffffUL;
        amask = 0xffffffffUL;
        pfmt = xyfmt = cfmt = "%04lx";
        afmt = "%08lx";
        dfmt = "S3%02lx%08lx%s%02x\n";
        efmt = "S9%02lx%s%02x\n";       /* sic: S9, not S7 */
    } else if (strcmp(name, "56700") == 0) {
        type = 8;
        xysize = psize = wsize = 2;
        alen = 4;
        pmask = xymask = cmask = 0xffffUL;
        amask = 0xffffffffUL;
        pfmt = xyfmt = cfmt = "%04lx";
        afmt = "%08lx";
        dfmt = "S3%02lx%08lx%s%02x\n";
        efmt = "S9%02lx%s%02x\n";       /* sic */
    } else if (strcmp(name, "5616") == 0 || strcmp(name, "56100") == 0) {
        type = 3;
        xysize = psize = wsize = 2;
        alen = 2;
        pmask = xymask = cmask = 0xffffUL;
        amask = 0xffffUL;
        pfmt = xyfmt = cfmt = "%04lx";
        afmt = "%04lx";
        dfmt = "S1%02lx%04lx%s%02x\n";
        efmt = "S9%02lx%s%02x\n";
    } else if (strcmp(name, "56300") == 0) {
        type = 4;
        xysize = psize = wsize = 3;
        alen = 3;
        pmask = xymask = cmask = 0xffffffUL;
        amask = 0xffffffUL;
        pfmt = xyfmt = cfmt = "%06lx";
        afmt = "%06lx";
        dfmt = "S2%02lx%06lx%s%02x\n";
        efmt = "S8%02lx%s%02x\n";
    } else if (strcmp(name, "56800") == 0) {
        type = 5;
        xysize = psize = wsize = 2;
        alen = 3;                       /* sic: 3, with 16-bit formats */
        pmask = xymask = cmask = 0xffffUL;
        amask = 0xffffUL;
        pfmt = xyfmt = cfmt = "%04lx";
        afmt = "%04lx";
        dfmt = "S1%02lx%04lx%s%02x\n";
        efmt = "S9%02lx%s%02x\n";
    } else if (strcmp(name, "56600") == 0) {
        type = 6;
        esize = 1;
        xysize = wsize = 2;
        psize = 3;
        alen = 3;
        xymask = cmask = 0xffffUL;
        pmask = 0xffffffUL;
        amask = 0xffffUL;
        xyfmt = cfmt = "%04lx";
        pfmt = "%06lx";
        afmt = "%04lx";
        dfmt = "S1%02lx%04lx%s%02x\n";
        efmt = "S9%02lx%s%02x\n";
    }
    if (aopt == 2) {
        alen = aopt;
        amask = 0xffffUL;
        afmt = "%04lx";
        dfmt = "S1%02lx%04lx%s%02x\n";
        efmt = "S9%02lx%s%02x\n";
    } else if (aopt == 3) {
        alen = aopt;
        amask = 0xffffffUL;
        afmt = "%06lx";
        dfmt = "S2%02lx%06lx%s%02x\n";
        efmt = "S8%02lx%s%02x\n";
    } else if (aopt == 4) {
        alen = aopt;
        amask = 0xffffffffUL;
        afmt = "%08lx";
        dfmt = "S3%02lx%08lx%s%02x\n";
        efmt = "S7%02lx%s%02x\n";
    }
    if (topt == 2) {
        psize = xysize = wsize = topt;
        pmask = xymask = cmask = 0xffffUL;
        pfmt = xyfmt = cfmt = "%04lx";
    } else if (topt == 3) {
        psize = xysize = wsize = topt;
        pmask = xymask = cmask = 0xffffffUL;
        pfmt = xyfmt = cfmt = "%06lx";
    } else if (topt == 4) {
        psize = xysize = wsize = topt;
        pmask = xymask = cmask = 0xffffffffUL;
        pfmt = xyfmt = cfmt = "%08lx";
    }
    alen1 = alen + 1;
    return type;
}

/* without -a the address length follows each address */
static void set_alen(unsigned long addr)
{
    if (addr < 0x10000UL) {
        if (alen != 2) {
            alen = 2;
            amask = 0xffffUL;
            afmt = "%04lx";
            dfmt = "S1%02lx%04lx%s%02x\n";
            efmt = "S9%02lx%s%02x\n";
        }
    } else if (addr < 0x1000000UL) {
        if (alen != 3) {
            alen = 3;
            amask = 0xffffffUL;
            afmt = "%06lx";
            dfmt = "S2%02lx%06lx%s%02x\n";
            efmt = "S8%02lx%s%02x\n";
        }
    } else {
        if (alen != 4) {
            alen = 4;
            amask = 0xffffffffUL;
            afmt = "%08lx";
            dfmt = "S3%02lx%08lx%s%02x\n";
            efmt = "S7%02lx%s%02x\n";
        }
    }
    alen1 = alen + 1;
}

/* COFF memory space to lane */
static int cld_space(long mem)
{
    if (mem >= 0x1c && mem < 0x11d)
        return machine == 1 || machine == 4 || machine == 6 ? ME : -1;
    switch (mem) {
    case 0: case 0xb: case 0xc: case 0xd: case 0xe: case 0xf:
        return MP;
    case 1: case 0x12: case 0x13: case 0x14:
        return MX;
    case 2: case 0x17: case 0x18: case 0x19:
        return machine == 1 || machine == 4 || machine == 6 || machine == 2 ? MY : -1;
    case 3: case 9: case 10:
        return machine == 1 || machine == 4 || machine == 6 || machine == 2 ? ML : -1;
    case 4:
        return MX;
    case 5: case 6: case 7: case 8:
        return machine == 2 ? ML : -1;
    case 0x10: case 0x11:
        return machine == 2 ? MX : -1;
    case 0x15: case 0x16:
        return machine == 2 ? MY : -1;
    case 0x11d:
        return machine == 1 ? MD : -1;
    }
    return -1;
}

/* .lod memory space letter (first character only) to lane */
static int lod_space(void)
{
    switch (tok[0]) {
    case 'D': case 'd': return MD;
    case 'E': case 'e': return ME;
    case 'L': case 'l': return ML;
    case 'P': case 'p': return MP;
    case 'X': case 'x': return MX;
    case 'Y': case 'y': return MY;
    }
    return -1;
}

static int space_char(int lane)
{
    switch (lane) {
    case MX: return 'x';
    case MY: return 'y';
    case ML: return 'l';
    case MP: return 'p';
    case ME: return 'e';
    case MD: return 'd';
    }
    return 0;
}

/* --------------------------------------------------------- S-record output */

/* build the S0 record; n is the -s segment (memory space + 1) or 0 */
static void make_s0(int n)
{
    if (n == 0) {
        /* sic: for every further .cld file (and in -s mode) this copies the
           previous S0 record, which then becomes part of the new one */
        strncpy(s0name, s0rec, sizeof(s0name) - 1);
        s0name[sizeof(s0name) - 1] = 0;
    }
    sprintf(s0rec, "S0%02x%04x%s%02x\n", s0len, n, s0name,
            (int)(~(s0sum + s0len + n) & 0xff));
    upcase(s0rec);
}

static void open_output(int lane)
{
    struct srec *s;
    char *fname = NULL, *end = NULL;
    int n, c;

    if (lane == ME)
        wsize = esize;
    else
        wsize = lane == MP ? psize : xysize;
    n = mflag ? wsize : 1;
    /*
     * With -m the number of files follows the word size of the space at
     * open time, but the loops that use them take the current word size,
     * which is larger for the 56600 (P words with X/Y/E files, X/Y words
     * of 0x4000 sections).  The original then ran over its heap block and
     * usually crashed; the spare entries here (at least 4, the largest word
     * size) keep that harmless, and writing to one of them reports the
     * crash as the original's SIGSEGV handler did.
     */
    s = (struct srec *)calloc(n > 4 ? (size_t)n : 4, sizeof(struct srec));
    nrecs[lane] = n;
    if (s == NULL)
        error("cannot allocate S-record structure");
    srecs[lane] = s;
    if (basename_ != NULL) {
        c = sflag ? 's' : space_char(lane);
        fname = (char *)malloc(strlen(basename_) + 8);
        if (fname == NULL)
            error("cannot allocate S-record structure");
        sprintf(fname, "%s.%c", basename_, c);
        end = fname + strlen(fname);
    }
    if (!mflag) {
        if (basename_ == NULL)
            s->fp = stdout;
        else {
            s->fp = fopen(fname, "w");
            if (s->fp == NULL)
                error2("cannot open output file %s", fname);
        }
        if (!sflag && fputs(s0rec, s->fp) == EOF)
            error("cannot write S0 record");
    } else {
        for (n = wsize - 1; n >= 0; n--, s++) {
            if (basename_ == NULL)
                s->fp = stdout;
            else {
                end[0] = (char)(n + '0');
                end[1] = '\0';
                s->fp = fopen(fname, "w");
                if (s->fp == NULL)
                    error2("cannot open output file %s", fname);
            }
            if (fputs(s0rec, s->fp) == EOF)
                error("cannot write S0 record");
        }
    }
    free(fname);
}

/* -s: a new S0 record with the segment number whenever the space changes */
static void new_segment(int lane)
{
    int seg = lane + 1;

    if (lastseg != seg) {
        make_s0(seg);
        if (fputs(s0rec, srecs[0]->fp) == EOF)
            error("cannot write S0 record");
        lastseg = seg;
    }
}

/* the bytes are reversed unless -r (or -m) is given */
static void swap_bytes(char *p, int lane)
{
    char c;

    wsize = (lane == MP || e56600) ? psize : xysize;
    if (wsize == 2) {
        c = p[0]; p[0] = p[2]; p[2] = c;
        c = p[1]; p[1] = p[3]; p[3] = c;
    } else if (wsize == 4) {
        c = p[0]; p[0] = p[6]; p[6] = c;
        c = p[1]; p[1] = p[7]; p[7] = c;
        c = p[2]; p[2] = p[4]; p[4] = c;
        c = p[3]; p[3] = p[5]; p[5] = c;
    } else {
        c = p[0]; p[0] = p[4]; p[4] = c;
        c = p[1]; p[1] = p[5]; p[5] = c;
    }
}

/*
 * Append the bytes of a hex word to the record(s) of srecs[idx].  Note the
 * word size is taken from idx, which is 0 in -s mode (so P words of the
 * 56600 lose a byte there); the callers go on using the wsize set here.
 */
static void put_bytes(int idx, char *hex)
{
    struct srec *s;
    char *q;
    int i;

    wsize = (idx == MP || e56600) ? psize : xysize;
    s = srecs[idx];
    for (i = 0; i < wsize; i++) {
        if (!cflag || i >= wsize - 1) {
            q = s->ptr;
            q[0] = hex[0];
            q[1] = hex[1];
            q[2] = '\0';
            /* a failing conversion adds the previous value, as the
               uninitialised local of the original most likely did */
            sscanf(s->ptr, "%x", &hexv);
            s->sum += (long)hexv;
            s->ptr = q + 2;
        }
        hex += 2;
        if (mflag)
            s++;
    }
}

static void reset_records(int idx)
{
    struct srec *s;
    int i;

    for (i = 0, s = srecs[idx]; i < (mflag ? wsize : 1); i++, s++) {
        s->sum = 0;
        s->ptr = s->data;
    }
}

static void put_record(int idx, unsigned long addr, unsigned int count)
{
    struct srec *s;
    int i;

    if (aopt == 0)
        set_alen(addr);
    count += (unsigned int)alen1;
    wsize = (idx == MP || e56600) ? psize : xysize;
    for (i = 0, s = srecs[idx]; i < (mflag ? wsize : 1); i++, s++) {
        if (i >= nrecs[idx])
            onsig(SIGSEGV);
        s->sum += bytesum(addr & amask);
        sprintf(line, dfmt, (unsigned long)count, addr & amask, s->data,
                (int)(~(s->sum + (long)count) & 0xff));
        if (fputs(upcase(line), s->fp) == EOF)
            error("cannot write start S-record");
        s->sum = 0;
        s->ptr = s->data;
    }
}

/* address increment after a record of count bytes */
static unsigned long advance(unsigned long addr, unsigned int count,
                             unsigned int div, int ldouble)
{
    if (!bflag && !mflag && !cflag) {
        if (lflag && ldouble)
            addr += (count / div) >> 1;
        else
            addr += count / div;
    } else
        addr += count;
    return addr & M32;
}

static unsigned int step(int lane)
{
    if (lane == ML)
        return !mflag && !cflag ? (unsigned int)wsize * 2 : 2;
    return !mflag && !cflag ? (unsigned int)wsize : 1;
}

/* the end records of all open files, then close them */
static void end_records(int cnt, char *addrstr, int sum, int perspace)
{
    struct srec *s;
    int i, j;

    for (i = 0; i < (sflag ? 1 : 6); i++) {
        if (srecs[i] == NULL)
            continue;
        if (perspace)
            wsize = (i == MP || e56600) ? psize : xysize;
        s = sflag ? srecs[0] : srecs[i];
        for (j = 0; j < (mflag ? wsize : 1); j++, s++) {
            if (j >= nrecs[sflag ? 0 : i])
                onsig(SIGSEGV);         /* see open_output */
            sprintf(line, efmt, (unsigned long)cnt, addrstr, (int)(~(sum + cnt) & 0xff));
            if (fputs(upcase(line), s->fp) == EOF)
                error("cannot write end S-record");
            fclose(s->fp);
        }
        free(srecs[i]);
        srecs[i] = NULL;
    }
}


/* ------------------------------------------------------------ COFF input */

static unsigned char filhdr[FILHSZ];

static void read_cld_header(FILE *fp)
{
    char *name = NULL;
    long n;

    if (fread(filhdr, FILHSZ, 1, fp) != 1)
        error("cannot read file header");
    magic = be32(filhdr);
    nscns = s32(be32(filhdr + 4));
    opthdr = s32(be32(filhdr + 20));
    f_flags = be32(filhdr + 24);
    if (!(f_flags & 1))
        error("invalid object file type");
    switch (magic) {
    case 0x2c5: name = "56000"; break;
    case 0x2c6: name = "96000"; break;
    case 0x2c7: name = "56100"; break;
    case 0x2c8: name = "56300"; break;
    case 0x2c9: name = "56800"; break;
    case 0x2ca: name = "56600"; break;
    case 0x2cb: name = "100"; break;
    case 0x2cc: name = "56700"; break;
    default: error("invalid machine type");
    }
    /* the machine type of the first input file stays in force */
    if (machine == 0 && (machine = set_machine(name)) == 0)
        error("invalid machine type");
    if (opthdr != 0) {
        /*
         * The original read the whole optional header into a 64-byte
         * buffer (followed by the S0 name buffer, which is rebuilt just
         * below); only the entry point at offset 0x14 is used.
         */
        if (opthdr < 0)
            error("cannot read optional header");
        n = opthdr < AOUTMAX ? opthdr : AOUTMAX;
        if (fread(aouthdr, (size_t)n, 1, fp) != 1)
            error("cannot read optional header");
        for (n = opthdr - n; n > 0; n--)
            if (getc(fp) == EOF)
                error("cannot read optional header");
    }
    make_s0(0);
    if (sflag)
        open_output(0);
}

/*
 * A data section.  mem is the space of the section, lane the space written
 * (they differ for L memory split by -x: lane X gets the odd words, lane Y
 * the even ones, swapped by -u).
 */
static void cld_data(unsigned char *scn, int secno, int mem, int lane)
{
    unsigned char *raw, *p;
    unsigned long addr, bytes;
    unsigned int count = 0, div;
    char secname[16];
    long n, i;
    int idx = lane, sel;

    sel = uflag ? lane != 0 : lane == 0;
    if (sflag) {
        idx = 0;
        new_segment(lane);
    } else if (srecs[lane] == NULL)
        open_output(lane);
    addr = (be32(scn + 8) + offset[lane]) & M32;
    e56600 = magic == 0x2ca && (be32(scn + 0x30) & 0x4000) ? 1 : 0;
    wsize = (lane == MP || e56600) ? psize : xysize;
    div = (unsigned int)(magic == 0x2ca && lane == ME ? esize : wsize);
    if (!mflag && bflag)
        addr = (addr * div) & M32;
    if (lflag && lane == ML && bflag)
        addr = (addr << 1) & M32;
    sprintf(secname, "%d", secno);
    n = s32(be32(scn + 0x18));
    bytes = ((unsigned long)n * 4) & M32;
    raw = NULL;
    if ((size_t)bytes == bytes)
        raw = (unsigned char *)malloc(bytes ? (size_t)bytes : 1);
    if (raw == NULL)
        error2("cannot allocate data block for section %s", secname);
    if (fseek(ifp, s32(be32(scn + 0x1c)), SEEK_SET) != 0)
        error2("cannot seek to raw data in section %s", secname);
    if (n <= 0 || fread(raw, 4, (size_t)n, ifp) != (size_t)n)
        error2("cannot read raw data in section %s", secname);
    wsize = (lane == MP || e56600) ? psize : xysize;
    reset_records(idx);
    p = raw;
    for (i = 0; i < n; i++) {
        if (mem != lane && ((i ^ sel) & 1)) {
            p += 4;
            continue;
        }
        cmask = (lane == MP || e56600) ? pmask : xymask;
        cfmt = (lane == MP || e56600) ? pfmt : xyfmt;
        sprintf(tok, cfmt, be32(p) & cmask);
        p += 4;
        upcase(tok);
        wsize = (lane == MP || e56600) ? psize : xysize;
        if (strlen(tok) != (size_t)wsize * 2)
            error("improper number of bytes in word");
        if (!rflag && !mflag)
            swap_bytes(tok, lane);
        if (lane == ML) {
            /* an odd word count would read past the data in the original */
            sprintf(word2, cfmt, (i + 1 < n ? be32(p) : 0UL) & cmask);
            p += 4;
            upcase(word2);
            if (strlen(word2) != (size_t)wsize * 2)
                error("improper number of bytes in word");
            if (!rflag && !mflag)
                swap_bytes(word2, lane);
            i++;
        } else
            strcpy(word2, tok);
        put_bytes(idx, uflag ? tok : word2);
        if (lane == ML)
            put_bytes(idx, uflag ? word2 : tok);
        count += step(lane);            /* wsize as left by put_bytes */
        if (!(count & 1) && count >= 0x1e) {
            put_record(idx, addr, count);
            addr = advance(addr, count, div, lane == ML);
            count = 0;
        }
    }
    free(raw);
    if (srecs[idx]->ptr != srecs[idx]->data)
        put_record(idx, addr, count);
}

/*
 * A block data section (bsc): the section holds one word (two for L) that
 * is repeated s_size times.  The original read the raw data into a 3-word
 * local whose third word is the address, so a 3-word section overwrote the
 * address (kept) and longer ones overran the stack (extra words ignored).
 */
static void cld_block(unsigned char *scn, int secno, int mem, int lane)
{
    unsigned char b[4];
    unsigned long w[3], addr;
    unsigned int count = 0, div;
    char secname[16];
    long n, nblk, i;
    int idx = lane, sel = 0;

    if (sflag) {
        idx = 0;
        new_segment(lane);
    } else if (srecs[lane] == NULL)
        open_output(lane);
    addr = (be32(scn + 8) + offset[lane]) & M32;
    e56600 = magic == 0x2ca && (be32(scn + 0x30) & 0x4000) ? 1 : 0;
    wsize = (lane == MP || e56600) ? psize : xysize;
    div = (unsigned int)(magic == 0x2ca && lane == ME ? esize : wsize);
    if (!mflag && bflag)
        addr = (addr * div) & M32;
    if (lflag && lane == ML && bflag)
        addr = (addr << 1) & M32;
    nblk = s32(be32(scn + 0x10));
    sprintf(secname, "%d", secno);
    if (fseek(ifp, s32(be32(scn + 0x1c)), SEEK_SET) != 0)
        error2("cannot seek to raw data in section %s", secname);
    n = s32(be32(scn + 0x18));
    w[0] = w[1] = 0;
    w[2] = addr;
    if (n <= 0)
        error2("cannot read raw data in section %s", secname);
    for (i = 0; i < n; i++) {
        if (fread(b, 4, 1, ifp) != 1)
            error2("cannot read raw data in section %s", secname);
        if (i < 3)
            w[i] = be32(b);
    }
    addr = w[2];
    if (mem != lane)
        /* sic: the opposite choice of cld_data, X gets the first word */
        sel = uflag ? lane == 0 : lane != 0;
    cmask = (lane == MP || e56600) ? pmask : xymask;
    cfmt = (lane == MP || e56600) ? pfmt : xyfmt;
    sprintf(tok, cfmt, w[sel] & cmask);
    upcase(tok);
    wsize = (lane == MP || e56600) ? psize : xysize;
    if (strlen(tok) != (size_t)wsize * 2)
        error("improper number of bytes in word");
    if (!rflag && !mflag)
        swap_bytes(tok, lane);
    if (lane == ML) {
        sprintf(word2, cfmt, w[1] & cmask);
        upcase(word2);
        if (strlen(word2) != (size_t)wsize * 2)
            error("improper number of bytes in word");
        if (!rflag && !mflag)
            swap_bytes(word2, lane);
    } else
        strcpy(word2, tok);
    wsize = (lane == MP || e56600) ? psize : xysize;
    reset_records(idx);
    for (i = 0; i < nblk; i++) {
        put_bytes(idx, uflag ? tok : word2);
        if (lane == ML)
            put_bytes(idx, uflag ? word2 : tok);
        wsize = (lane == MP || e56600) ? psize : xysize;
        div = (unsigned int)(magic == 0x2ca && lane == ME ? esize : wsize);
        count += step(lane);
        if (!(count & 1) && count >= 0x1e) {
            put_record(idx, addr, count);
            /* sic: -l looks at mem here, at lane everywhere else */
            addr = advance(addr, count, div, mem == ML);
            count = 0;
        }
    }
    if (srecs[idx]->ptr != srecs[idx]->data)
        put_record(idx, addr, count);
}

/*
 * End records.  The address string, its checksum and the length byte are
 * taken before set_alen() adapts the record type to the entry address.
 */
static void cld_end(void)
{
    unsigned long addr;
    int sum, cnt;

    addr = (be32(aouthdr + 0x14) + offset[MP]) & M32;
    wsize = psize;
    if (!mflag && bflag)
        addr = (addr * (unsigned long)wsize) & M32;
    sprintf(tok, afmt, addr & amask);
    sum = bytesum(addr & amask);
    cnt = alen1;
    if (aopt == 0)
        set_alen(addr);
    /* one record per -m file of the P word size, for every space */
    end_records(cnt, tok, sum, 0);
}

static void do_cld(FILE *fp)
{
    void (*fn)(unsigned char *, int, int, int);
    unsigned char *hdrs, *p;
    unsigned long bytes;
    long n, i;
    int lane;

    read_cld_header(fp);
    n = nscns;
    bytes = ((unsigned long)n * SCNHSZ) & M32;
    hdrs = NULL;
    if ((size_t)bytes == bytes)
        hdrs = (unsigned char *)malloc(bytes ? (size_t)bytes : 1);
    if (hdrs == NULL)
        error("cannot allocate section headers");
    if (fseek(fp, opthdr + FILHSZ, SEEK_SET) != 0)
        error("cannot seek to section headers");
    if (bytes == 0 || fread(hdrs, (size_t)bytes, 1, fp) != 1)
        error("cannot read section headers");
    for (i = 1, p = hdrs; i <= n; i++, p += SCNHSZ) {
        if (be32(p + 0x1c) == 0 || be32(p + 0x18) == 0)
            continue;
        lane = cld_space(s32(be32(p + 0xc)));
        if (lane < 0)
            error("invalid memory space specifier");
        fn = be32(p + 0x30) & 0x400 ? cld_block : cld_data;
        if (lane == ML && xflag) {
            fn(p, (int)i, ML, MX);
            fn(p, (int)i, ML, MY);
        } else
            fn(p, (int)i, lane, lane);
    }
    free(hdrs);
    cld_end();
}

/* ------------------------------------------------------------- .lod input */

/* next whitespace-separated token into tok: 1 if it starts with '_',
   0 otherwise, -1 at end of file */
static int get_token(void)
{
    char *p;
    int c;

    while ((c = getc(ifp)) != EOF) {
        if (!isspace(c))
            break;
        if (c == '\n')
            lineno++;
    }
    if (c == EOF)
        return -1;
    tok[0] = (char)c;
    p = tok + 1;
    while ((c = getc(ifp)) != EOF) {
        if (isspace(c))
            break;
        if (p - tok > 0x1fd) {
            /* sic: the character is stored and also pushed back below */
            *p++ = (char)c;
            break;
        }
        *p++ = (char)c;
    }
    *p = '\0';
    if (c != EOF)
        ungetc(c, ifp);
    return tok[0] == '_';
}

/* skip to the end of the line and read the next line into tok */
static int get_line(void)
{
    char *p;
    int c;

    do {
        c = getc(ifp);
        if (c == EOF || c == '\n')
            break;
    } while (isspace(c));
    if (c == EOF || c != '\n')
        return -1;
    lineno++;
    p = tok;
    for (;;) {
        c = getc(ifp);
        if (c == EOF || c == '\n')
            break;
        if (p - tok > 0x1fd) {
            *p++ = (char)c;
            break;
        }
        *p++ = (char)c;
    }
    if (c == '\n')
        lineno++;
    *p = '\0';
    return 0;
}

/* rest of the START line into line (the original had no length check) */
static int get_rest(void)
{
    char *p = line;
    int c;

    for (;;) {
        c = getc(ifp);
        if (c == EOF || c == '\n')
            break;
        if (p < line + sizeof(line) - 1)
            *p++ = (char)c;
    }
    if (c == EOF)
        return -1;
    *p = '\0';
    ungetc('\n', ifp);
    return 0;
}

/* next field of a string into tok; NULL if there is none */
static char *next_field(char *p)
{
    char *q;

    for (; *p != '\0'; p++)
        if (!cspace(*p))
            break;
    if (*p == '\0')
        return NULL;
    q = tok;
    for (; *p != '\0'; p++) {
        if (cspace(*p))
            break;
        *q++ = *p;
    }
    *q = '\0';
    return p;
}

static int lod_rectype(void)
{
    int r = 0;

    while (tok[0] != '_') {
        r = get_token();
        if (r != 0)
            break;
    }
    if (r < 0)
        return r;
    upcase(tok + 1);
    if (strcmp(tok + 1, "DATA") == 0)
        return 3;
    if (strcmp(tok + 1, "BLOCKDATA") == 0)
        return 4;
    if (strcmp(tok + 1, "START") == 0)
        return 1;
    if (strcmp(tok + 1, "END") == 0)
        return 2;
    if (strcmp(tok + 1, "SYMBOL") == 0)
        return 5;
    if (strcmp(tok + 1, "COMMENT") == 0)
        return 6;
    return 0;
}

/*
 * _START name n n n DSPxxxxx version, followed by a comment line.  Without
 * a START record the processor defaults to the 56000.  (An unknown '_'
 * record ahead of it makes the original loop forever; so does this.)
 */
static int lod_start(FILE *fp)
{
    char *p, *h, *q;
    int r, dflt = 0;

    h = s0rec;
    do
        r = lod_rectype();
    while (r <= 0 && r != -1);
    if (r == -1)
        return 0;
    if (r != 1) {
        if (machine == 0 && (machine = set_machine("56000")) == 0)
            error("cannot initialize machine type");
        make_s0(0);
        if (sflag)
            open_output(0);
        return 1;
    }
    if (get_rest() < 0)
        error("invalid START record");
    p = next_field(line);
    if (p == NULL)
        error("invalid START record");
    if (fp == stdin) {
        /* sic: the extension goes onto the module name and the '.' is
           searched in the (never filled) output base name */
        set_ext(tok, ".lod");
        q = strrchr(basename_, '.');
        if (q != NULL)
            *q = '\0';
    }
    for (q = tok; *q != '\0'; q++) {
        if (*q & 0x80)                  /* "%02x" of a negative char */
            sprintf(h, "ffffff%02x", (unsigned char)*q);
        else
            sprintf(h, "%02x", *q);
        s0sum += (unsigned char)*q;
        h += 2;                         /* sic: also for 8-digit values */
        s0len++;
    }
    make_s0(0);
    if ((p = next_field(p)) == NULL || (p = next_field(p)) == NULL ||
        (p = next_field(p)) == NULL)
        dflt = 1;
    if (dflt) {
        if (machine == 0 && (machine = set_machine("56000")) == 0)
            error("cannot initialize machine type");
    } else {
        if ((p = next_field(p)) == NULL)
            error("invalid START record");
        if (strncmp(tok, "DSP", 3) != 0)
            error("invalid START record");
        if (machine == 0 && (machine = set_machine(tok + 3)) == 0)
            error("invalid machine type");
        if ((p = next_field(p)) == NULL)
            error("invalid START record");
    }
    if (get_line() < 0)
        error("invalid START record");
    if (sflag)
        open_output(0);
    return 1;
}

/* _DATA <mem> <addr> followed by data words (pairs for L memory) */
static void lod_data(int mem, int lane)
{
    unsigned long addr, v;
    unsigned int count = 0, div;
    long i;
    int idx = lane, sel;

    sel = uflag ? lane != 0 : lane == 0;
    if (sflag) {
        idx = 0;
        new_segment(lane);
    } else if (srecs[lane] == NULL)
        open_output(lane);
    if (get_token() < 0)
        error("invalid DATA record");
    if (!all_hex())
        error("invalid address value");
    addr = (hexval(tok) + offset[lane]) & M32;
    /* e56600 and magic are whatever the last .cld file left */
    wsize = (lane == MP || e56600) ? psize : xysize;
    div = (unsigned int)(magic == 0x2ca && lane == ME ? esize : wsize);
    if (!mflag && bflag)
        addr = (addr * div) & M32;
    if (lflag && lane == ML && bflag)
        addr = (addr << 1) & M32;
    reset_records(idx);
    for (i = 0; get_token() == 0; i++) {
        /* sic: X is the first word of a pair here, so -x swaps X and Y
           compared to .cld input */
        if (mem != lane && ((i ^ sel) & 1))
            continue;
        if (!all_hex())
            error("invalid data value");
        v = hexval(tok);
        cmask = (lane == MP || e56600) ? pmask : xymask;
        cfmt = (lane == MP || e56600) ? pfmt : xyfmt;
        sprintf(tok, cfmt, v & cmask);
        upcase(tok);
        wsize = (lane == MP || e56600) ? psize : xysize;
        div = (unsigned int)(magic == 0x2ca && lane == ME ? esize : wsize);
        if (strlen(tok) != (size_t)wsize * 2)
            error("improper number of bytes in word");
        if (!rflag && !mflag)
            swap_bytes(tok, lane);
        strcpy(word2, tok);
        if (lane == ML) {
            if (get_token() != 0)
                error("data synchronization error");
            if (!all_hex())
                error("invalid data value");
            v = hexval(tok);
            sprintf(tok, cfmt, v & cmask);
            upcase(tok);
            if (strlen(tok) != (size_t)wsize * 2)
                error("improper number of bytes in word");
            if (!rflag && !mflag)
                swap_bytes(tok, lane);
        }
        put_bytes(idx, uflag ? tok : word2);
        if (lane == ML)
            put_bytes(idx, uflag ? word2 : tok);
        count += step(lane);
        if (!(count & 1) && count >= 0x1e) {
            put_record(idx, addr, count);
            addr = advance(addr, count, div, lane == ML);
            count = 0;
        }
    }
    if (srecs[idx]->ptr != srecs[idx]->data)
        put_record(idx, addr, count);
}

/* _BLOCKDATA <mem> <addr> <count> <value> */
static void lod_block(int mem, int lane)
{
    unsigned long addr, v;
    unsigned int count = 0, div;
    long n, i;
    int idx = lane;

    (void)mem;
    if (sflag) {
        idx = 0;
        new_segment(lane);
    } else if (srecs[lane] == NULL)
        open_output(lane);
    if (get_token() < 0)
        error("invalid BLOCKDATA record");
    if (!all_hex())
        error("invalid address value");
    addr = (hexval(tok) + offset[lane]) & M32;
    wsize = (lane == MP || e56600) ? psize : xysize;
    div = (unsigned int)(magic == 0x2ca && lane == ME ? esize : wsize);
    if (!mflag && bflag)
        addr = (addr * div) & M32;
    if (lflag && lane == ML && bflag)
        addr = (addr << 1) & M32;
    if (get_token() < 0)
        error("invalid BLOCKDATA record");
    if (!all_hex())
        error("invalid count value");
    n = s32(hexval(tok));               /* sscanf("%x") into an int */
    if (get_token() < 0)
        error("invalid BLOCKDATA record");
    if (!all_hex())
        error("invalid data value");
    v = hexval(tok);
    cmask = (lane == MP || e56600) ? pmask : xymask;
    cfmt = (lane == MP || e56600) ? pfmt : xyfmt;
    sprintf(tok, cfmt, v & cmask);
    upcase(tok);
    wsize = (lane == MP || e56600) ? psize : xysize;
    if (strlen(tok) != (size_t)wsize * 2)
        error("improper number of bytes in word");
    if (!all_hex())
        error("invalid data value");
    if (!rflag && !mflag)
        swap_bytes(tok, lane);
    reset_records(idx);
    wsize = (lane == MP || e56600) ? psize : xysize;
    div = (unsigned int)(magic == 0x2ca && lane == ME ? esize : wsize);
    for (i = 0; i < n; i++) {
        put_bytes(idx, tok);
        count += !mflag && !cflag ? (unsigned int)wsize : 1;
        if (!(count & 1) && count >= 0x1e) {
            put_record(idx, addr, count);
            addr = advance(addr, count, div, lane == ML);
            count = 0;
        }
    }
    if (srecs[idx]->ptr != srecs[idx]->data)
        put_record(idx, addr, count);
}

/* _END [addr], or the end of the file */
static void lod_end(void)
{
    unsigned long addr;
    int r, sum = 0, cnt = 1;

    r = get_token();
    if (r > 0)
        error("invalid END record");
    if (r == 0) {
        if (!all_hex())
            error("invalid address value");
        addr = (hexval(tok) + offset[MP]) & M32;
        wsize = psize;
        if (!mflag && bflag)
            addr = (addr * (unsigned long)wsize) & M32;
        sprintf(tok, afmt, addr & amask);
        sum = bytesum(addr & amask);
        cnt = alen1;
        if (aopt == 0)
            set_alen(addr);
    }
    end_records(cnt, r == 0 ? tok : noaddr, sum, 1);
}

static void do_lod(FILE *fp)
{
    void (*fn)(int, int);
    long pos;
    int r, lane;

    if (!lod_start(fp))
        error("no START record");
    for (;;) {
        if (feof(fp)) {
            lod_end();
            return;
        }
        r = lod_rectype();
        switch (r) {
        case 1:
            error("duplicate START record");
            break;
        case 2:
            lod_end();
            return;
        case 3:
        case 4:
            fn = r == 3 ? lod_data : lod_block;
            if (get_token() < 0)
                error("invalid DATA/BLOCKDATA record");
            lane = lod_space();
            if (lane < 0)
                error("invalid memory space specifier");
            if (lane == ML && xflag) {
                pos = ftell(ifp);
                fn(ML, MX);
                if (fseek(ifp, pos, SEEK_SET) != 0)
                    error("cannot reset data pointer in L memory");
                fn(ML, MY);
            } else
                fn(lane, lane);
            break;
        case 5:
            tok[0] = '\0';              /* skip the symbol lines */
            break;
        case 6:
            get_line();
            break;
        default:
            if (!feof(fp))
                error("invalid record type");
        }
    }
}

/* ------------------------------------------------------------------ main */

/* open name as given, else with .cld, else with .lod appended */
static int open_input(char *name)
{
    char orig[0x200];
    int type;

    /* the original copied into a 512-byte local without a check */
    strncpy(orig, name, sizeof(orig) - 1);
    orig[sizeof(orig) - 1] = '\0';
    type = file_type(name);
    ifp = fopen(name, type == 1 ? "r" : "rb");
    if (ifp != NULL)
        return type;
    /* sic: ftype still belongs to the previous input file */
    if (ftype != 0)
        error2("cannot open input file %s", orig);
    set_ext(name, ".cld");
    ifp = fopen(name, "rb");
    if (ifp != NULL)
        return 2;
    set_ext(name, ".lod");
    ifp = fopen(name, "r");
    if (ifp != NULL)
        return 1;
    error2("cannot open input file %s", orig);
    return 0;
}

static void convert(FILE *fp)
{
    int c;

    if (ftype == 2)
        do_cld(fp);
    else if (ftype == 1)
        do_lod(fp);
    else {
        /* unknown type: a COFF file has a NUL byte before any '_' */
        do
            c = getc(fp);
        while (c != EOF && c != '_' && c != 0);
        rewind(fp);
        if (c == EOF)
            error("invalid object file type");
        if (c == 0)
            do_cld(fp);
        else
            do_lod(fp);
    }
}

int main(int argc, char **argv)
{
    char *p, *procno = NULL, *name;
    int c;

    signal(SIGINT, onsig);
    signal(SIGSEGV, onsig);
    p = basename(argv[0]);
    if (p == NULL)
        p = progname;
    else {
        /* deviation: '/' also ends the directory part of the program name,
           else "./srec" on Unix would give an empty name */
        if ((name = strrchr(p, '/')) != NULL)
            p = name + 1;
        if ((name = strrchr(p, '.')) != NULL)
            *name = '\0';               /* also cuts argv[0] itself */
    }
    qflag = find_opt('q', argc, argv) != NULL;
    progname = p;
    if (!qflag)
        fprintf(stderr, "%s  %s\n%s\n", banner1, banner2, banner3);

    optarg_ = NULL;
    optind_ = 0;
    while ((c = getopt_(argc, argv, "A:a:BbCcLlMmO:o:P:p:QqRrSsT:t:UuW?w?Xx")) != -1) {
        if (c >= 0 && isupper(c))
            c = tolower(c);
        switch (c) {
        case 'a':
            if (sscanf(optarg_, "%d", &aopt) == 0)
                usage();
            break;
        case 'b':
            bflag = 1;
            break;
        case 'c':
            cflag = 1;
            break;
        case 'l':
            lflag = 1;
            break;
        case 'm':
            mflag = 1;
            break;
        case 'o':
            /* an empty argument made the original look past its end; it
               is refused here */
            p = *optarg_ != '\0' ? strchr(memchars, *optarg_) : NULL;
            if (p == NULL || optarg_[1] != ':')
                usage();
            if (isupper((unsigned char)*p))
                p -= 6;
            if (sscanf(optarg_ + 2, "%lx", &offset[p - memchars]) == 0)
                usage();
            break;
        case 'p':
            procno = optarg_;
            break;
        case 'q':
            qflag = 1;
            break;
        case 'r':
            rflag = 1;
            break;
        case 's':
            sflag = 1;
            break;
        case 't':
            if (sscanf(optarg_, "%d", &topt) == 0)
                usage();
            break;
        case 'u':
            uflag = 1;
            break;
        case 'w':
            wflag = 1;
            break;
        case 'x':
            xflag = 1;
            break;
        default:
            usage();
        }
    }
    argc -= optind_;
    argv += optind_;
    if (argc < 1 || (sflag && mflag) || (cflag && mflag) || (bflag && wflag))
        usage();

    if (procno != NULL && (machine = set_machine(procno)) == 0)
        error("invalid machine type");
    if (aopt != 0 && (aopt < 2 || aopt > 4))
        error("invalid -a command line argument");
    if (topt != 0 && (topt < 2 || topt > 4))
        error("invalid -t command line argument");
    if (lflag && xflag)
        lflag = 0;

    for (; argc > 0; argc--, argv++) {
        name = *argv;
        if (strcmp(name, "-") == 0) {
            basename_ = (char *)malloc(0x200);
            if (basename_ == NULL)
                error("cannot allocate file name");
            /* uninitialised in the original, so the output file names were
               garbage; an empty base name is used here */
            basename_[0] = '\0';
            ifp = stdin;
            convert(stdin);
        } else {
            basename_ = (char *)malloc(strlen(name) + 5);
            if (basename_ == NULL)
                error("cannot allocate file name");
            strcpy(basename_, name);
            ftype = open_input(basename_);
            p = strrchr(basename_, '.');
            if (p != NULL)
                *p = '\0';
            convert(ifp);
            fclose(ifp);
        }
        free(basename_);
    }
    exit(0);
    return 0;
}
