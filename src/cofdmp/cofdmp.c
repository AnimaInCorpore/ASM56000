/*
 * cofdmp - dump the contents of a Motorola DSP COFF object file
 *
 * Reconstructed from Motorola COFDMP.EXE, "DSP COFF File Dump Utility
 * Version 6.3" (CLAS56 v6.3, 1999), module $Id: cofdmp.c,v 1.62 1999/03/19.
 *
 * The COFF file stores 32-bit big-endian words.  The original program read
 * the structures raw on the PC and reversed every 4-byte word (swapping the
 * 8 name characters back afterwards).  This version does the same byte
 * reversal and then decodes the resulting little-endian image, so strings,
 * names and the places where the original ran over the end of a name behave
 * exactly as they did on the PC, on any host.
 *
 * Deviations from the original (all without effect on the output):
 * - int values printed from the file are passed as long ("%ld" instead of
 *   "%d") so that 16-bit int hosts print them correctly;
 * - "% 4lu" is written "%4lu" (the space flag has no effect on an unsigned
 *   conversion, MSVC and ANSI agree);
 * - the MSVC asctime() is reimplemented (ANSI asctime pads the day of the
 *   month with a blank, MSVC with a zero);
 * - the Macintosh file type call made after opening the -d file is dropped.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define FILHSZ  0x1c            /* file header */
#define SCNHSZ  0x34            /* section header */
#define RELSZ   0x0c            /* relocation entry */
#define LINESZ  0x0c            /* line number entry */
#define SYMESZ  0x20            /* symbol table entry */
#define AUXESZ  0x20            /* auxiliary symbol table entry */

#define NMEMS   290             /* entries of the memory space name table */

/* little-endian field of the byte-reversed image */
#define LE32(p) ((unsigned long)(p)[0] | ((unsigned long)(p)[1] << 8) | \
                 ((unsigned long)(p)[2] << 16) | ((unsigned long)(p)[3] << 24))

static char *progname = "cofdmp";
static char *title = "DSP COFF File Dump Utility";
static char *version = "Version 6.3 ";
static char *copyright =
    "(C) Copyright Motorola, Inc. 1991-1996.  All rights reserved.";
static char *indent = "    ";

/* dump selection, all on unless an option selects some */
static char cflag = 1;          /* string table */
static char fflag = 1;          /* file header */
static char hflag = 1;          /* section headers */
static char lflag = 1;          /* line numbers */
static char oflag = 1;          /* optional header */
static char rflag = 1;          /* relocation entries */
static char sflag = 1;          /* section contents */
static char tflag = 1;          /* symbol table */
static char vflag;              /* dump symbolically */
static char qflag;              /* no signon banner */
static int xflag;               /* (undocumented) no file names, versions
                                   and dates: output for regression tests */

static FILE *ofile;             /* output */
static char *ofname;            /* -d file */
static FILE *ifile;             /* current input */
static char *ifname;

static int optind_;             /* getopt state */
static char *optarg_;
static char *nextchar;

static long nscns;
static int newlnk;              /* linker header is not the old 40-byte one */
static int sdihdr;              /* F_SDI: linker header has sditot */
static char *strtab;
static unsigned long ovlflags;  /* flags of the last section aux entry */
static char aryflag;            /* last symbol was an array */

/*
 * The original kept the optional header, the file header and the linker
 * header in consecutive static variables and read the optional header with
 * its length taken from the file.  An optional header longer than its
 * buffer therefore overwrote the variables behind it.  They are kept in one
 * image here (layout of the original's data from 0x413840) so that this
 * happens the same way; only the string table pointer at IM_STRPTR is not
 * taken over (the original would crash on a garbage pointer), and bytes
 * beyond the image are read and discarded (the original overwrote unknown
 * data there).
 */
#define IM_AOUT         0x00    /* optional header of an absolute file */
#define IM_ABSFILE      0x3c    /* F_RELFLG was set */
#define IM_FILHDR       0x40    /* file header */
#define IM_STRLEN       0x5c    /* string table length */
#define IM_LNKHDR       0x60    /* linker header of a relocatable file */
#define IM_NSYMS        0x98
#define IM_STRPTR       0x9c
#define IM_SYMPTR       0xa0
#define IM_SCNPTR       0xa4
#define IM_SIZE         0xa8

static unsigned char image[IM_SIZE];
#define aouthdr (image + IM_AOUT)
#define filhdr  (image + IM_FILHDR)
#define lnkhdr  (image + IM_LNKHDR)
static int absfile;
static long strtablen, nsyms, symptr, scnptr;

/* memory space names, indexed by memory space/mapping number */
static char *memname[NMEMS] = {
    "P:", "X:", "Y:", "L:", "", "LAA:", "LAB:", "LBA:", "LBB:", "LE:", "LI:",
    "PA:", "PB:", "PE:", "PI:", "PR:", "XA:", "XB:", "XE:", "XI:", "XR:",
    "YA:", "YB:", "YE:", "YI:", "YR:", "PT:", "PF:", "EMI:"
};
static char enames[256][6];             /* "E0:" .. "E255:" */

static char *types[22] = {
    "T_NULL", "T_ARG", "T_CHAR", "T_SHORT", "T_INT", "T_LONG", "T_FLOAT",
    "T_DOUBLE", "T_STRUCT", "T_UNION", "T_ENUM", "T_MOE", "T_UCHAR",
    "T_USHORT", "T_UINT", "T_ULONG", "T_FRAC", "T_UFRAC", "T_LFRAC",
    "T_ULFRAC", "T_ACCUM", "T_LACCUM"
};
static char *ftypes[2] = { "T_NULL", "T_MOD" };

static void error(char *fmt, ...);

static long s32(unsigned long v)
{
    v &= 0xffffffffUL;
    if (v & 0x80000000UL)
        return -(long)(~v & 0x7fffffffUL) - 1;
    return (long)v;
}

static unsigned long g32(unsigned char *p)
{
    return LE32(p);
}

static long gs32(unsigned char *p)
{
    return s32(LE32(p));
}

static void p32(unsigned char *p, unsigned long v)
{
    p[0] = (unsigned char)(v & 0xff);
    p[1] = (unsigned char)((v >> 8) & 0xff);
    p[2] = (unsigned char)((v >> 16) & 0xff);
    p[3] = (unsigned char)((v >> 24) & 0xff);
}

static void onsig(int sig)
{
    if (sig == SIGINT) {
        fprintf(stderr, "\n%s: Interrupted\n", progname);
        exit(1);
    } else if (sig == SIGSEGV) {
        fprintf(stderr,
            "%s: Fatal segmentation or protection fault; contact your tools vendor\n",
            progname);
        exit(1);
    }
}

static void usage(void)
{
    if (qflag)
        fprintf(stderr, "%s  %s\n%s\n", title, version, copyright);
    fprintf(stderr, "Usage:  %s [-cfhloqrstv] [-d <file>] files\n", progname);
    fprintf(stderr, "        c - dump string table\n");
    fprintf(stderr, "        d - dump to output file\n");
    fprintf(stderr, "        f - dump file header\n");
    fprintf(stderr, "        h - dump section headers\n");
    fprintf(stderr, "        l - dump line number information\n");
    fprintf(stderr, "        o - dump optional header\n");
    fprintf(stderr, "        q - do not display signon banner\n");
    fprintf(stderr, "        r - dump relocation information\n");
    fprintf(stderr, "        s - dump section contents\n");
    fprintf(stderr, "        t - dump symbol table\n");
    fprintf(stderr, "        v - dump symbolically\n");
    exit(1);
}

/* print to the output file */
static void out(FILE *fp, char *fmt, ...)
{
    va_list ap;
    int n;

    va_start(ap, fmt);
    n = vfprintf(fp, fmt, ap);
    va_end(ap);
    if (n < 0)
        error("cannot write to output file");
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
    exit(1);
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

/* look for option letter c anywhere in the option arguments */
static char *getflag(int c, int argc, char **argv)
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
            ch = *p;
            if (isupper((unsigned char)ch))
                ch = tolower((unsigned char)ch);
            if (ch == c)
                return *argv;
        }
    }
}

static int get_opt(int argc, char **argv, char *opts)
{
    int c;
    char *p;

    optarg_ = NULL;
    if (nextchar == NULL || *nextchar == '\0') {
        if (optind_ == 0)
            optind_ = 1;
        if (optind_ >= argc || argv[optind_][0] != '-' ||
            argv[optind_][1] == '\0') {
            optarg_ = NULL;
            return -1;
        }
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
        fprintf(stderr, "%s: unknown option -%c\n", progname, c);
        return '?';
    }
    if (p[1] == ':') {
        if (*nextchar == '\0') {
            if (optind_ >= argc) {
                fprintf(stderr, "%s: -%c argument missing\n", progname, c);
                return '?';
            }
            optarg_ = argv[optind_++];
        } else {
            optarg_ = nextchar;
            nextchar = NULL;
        }
    }
    return c;
}

static void clear_flags(void)
{
    tflag = sflag = rflag = oflag = lflag = hflag = fflag = cflag = 0;
}

/*
 * Read the optional header of length len at image offset off, emulating
 * the original's overrun into the variables that followed its buffer.
 */
static int read_opthdr(unsigned int off, unsigned long len)
{
    unsigned long room, n, sw;
    int ok;

    p32(image + IM_ABSFILE, (unsigned long)absfile);
    p32(image + IM_STRLEN, (unsigned long)strtablen);
    p32(image + IM_NSYMS, (unsigned long)nsyms);
    p32(image + IM_SYMPTR, (unsigned long)symptr);
    room = IM_SIZE - off;
    n = len < room ? len : room;
    ok = fread(image + off, 1, (size_t)n, ifile) == (size_t)n;
    for (; ok && n < len; n++)
        if (getc(ifile) == EOF)
            ok = 0;
    sw = len & ~3UL;
    swapw(image + off, sw < room ? sw : room, 1);
    absfile = g32(image + IM_ABSFILE) != 0;
    strtablen = gs32(image + IM_STRLEN);
    nsyms = gs32(image + IM_NSYMS);
    symptr = gs32(image + IM_SYMPTR);
    return ok;
}

static void read_headers(void)
{
    unsigned long magic, opthdr;

    if (freads(filhdr, FILHSZ, 1, ifile) != 1)
        error("cannot read file header");
    magic = g32(filhdr);
    if (magic != 0x2c5 && magic != 0x2c6 && magic != 0x2c7 && magic != 0x2c8 &&
        magic != 0x2c9 && magic != 0x2ca && magic != 0x2cb && magic != 0x2cc)
        error("invalid object file format");
    nscns = gs32(filhdr + 4);
    nsyms = gs32(filhdr + 16);
    symptr = gs32(filhdr + 12);
    absfile = (g32(filhdr + 24) & 1) != 0;
    opthdr = g32(filhdr + 20);
    newlnk = opthdr != 0x28;
    sdihdr = (g32(filhdr + 24) & 0x20000UL) != 0;
    if (opthdr != 0) {
        if (absfile) {
            if (!read_opthdr(IM_AOUT, opthdr))
                error("cannot read optional file header");
        } else {
            if (!read_opthdr(IM_LNKHDR, opthdr))
                error("cannot read linker file header");
        }
    }
    /* f_opthdr may have been overwritten by the optional header */
    scnptr = s32(g32(filhdr + 20) + FILHSZ);
}

/* a read into a buffer that could not be allocated (see read_strtab) */
static void read_failed(void)
{
#ifdef EINVAL
    errno = EINVAL;
#endif
    error("cannot read string table");
}

static void read_strtab(void)
{
    long pos;
    unsigned char len[4];
    size_t r, n;
    char *p;

    if (nsyms == 0)
        return;
    pos = s32((unsigned long)symptr + ((unsigned long)nsyms << 5));
    if (fseek(ifile, pos, SEEK_SET) != 0)
        error("cannot seek to string table length");
    r = freads(len, 4, 1, ifile);
    if (r != 1 && !feof(ifile))
        error("cannot read string table length");
    if (feof(ifile)) {
        strtablen = 0;
        return;
    }
    strtablen = gs32(len);
    if (strtablen == 0)
        return;
    strtablen = s32((unsigned long)strtablen - 4);      /* 32-bit int */
    if (strtablen < 0)
        error("invalid string table length");
    /*
     * One extra NUL so that a table without a final terminator cannot run
     * off the buffer (the original read whatever followed it).  The
     * original never freed a string table: a following file without
     * symbols still uses it, which is kept.
     */
    n = (size_t)strtablen + 1;
    p = (unsigned long)(n - 1) == (unsigned long)strtablen && n != 0 ?
        (char *)malloc(n) : NULL;
    if (fseek(ifile, s32((unsigned long)pos + 4), SEEK_SET) != 0)
        error("cannot seek to string table");
    /*
     * The original did not check malloc(); MSVC's fread() into the NULL
     * pointer then failed with EINVAL.  MSVC's fread() returns 0 for an
     * item size of 0, so an empty table (length word 4) fails as well.
     */
    if (p == NULL)
        read_failed();
    if (strtablen == 0 || fread(p, (size_t)strtablen, 1, ifile) != 1)
        error("cannot read string table");
    p[strtablen] = '\0';
    if (strtab != NULL)
        free(strtab);
    strtab = p;
}

/* string at string table offset off (checked by the caller) */
static char *strptr(long off)
{
    return strtab + (off - 4);
}

/*
 * Convert a time to broken-down UTC time.  This is the program's own
 * routine, not the library's gmtime/localtime: no time zone is applied.
 */
static struct tm tmbuf;
static int ydays[2] = { 365, 366 };
static int mdays[2][12] = {
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

static int isleap(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
}

static struct tm *cvt_time(long t)
{
    long days, rem;
    int year, leap, mon;

    days = t / 86400L;
    for (rem = t % 86400L; rem < 0; rem += 86400L)
        days--;
    for (; rem >= 86400L; rem -= 86400L)
        days++;
    tmbuf.tm_hour = (int)(rem / 3600);
    tmbuf.tm_min = (int)(rem % 3600 / 60);
    tmbuf.tm_sec = (int)(rem % 3600 % 60);
    tmbuf.tm_wday = (int)((days + 4) % 7);
    if (tmbuf.tm_wday < 0)
        tmbuf.tm_wday += 7;
    year = 1970;
    leap = 0;
    if (days < 0) {
        do {
            year--;
            leap = isleap(year);
            days += ydays[leap];
        } while (days < 0);
    } else {
        for (;;) {
            leap = isleap(year);
            if (days < ydays[leap])
                break;
            year++;
            days -= ydays[leap];
        }
    }
    tmbuf.tm_year = year - 1900;
    tmbuf.tm_yday = (int)days;
    for (mon = 0; days >= mdays[leap][mon]; mon++)
        days -= mdays[leap][mon];
    tmbuf.tm_mon = mon;
    tmbuf.tm_mday = (int)days + 1;
    tmbuf.tm_isdst = 0;
    return &tmbuf;
}

/* two decimal digits, as the MSVC runtime's asctime() writes them */
static char *put2(char *p, int v)
{
    p[0] = (char)(v / 10 + '0');
    p[1] = (char)(v % 10 + '0');
    return p + 2;
}

/* MSVC asctime(): "Wed Jan 02 02:03:55 1980\n" (day with leading zero) */
static char *ms_asctime(struct tm *tm)
{
    static char buf[26];
    static char *wday = "SunMonTueWedThuFriSat";
    static char *mon = "JanFebMarAprMayJunJulAugSepOctNovDec";
    char *p;

    memcpy(buf, wday + tm->tm_wday * 3, 3);
    buf[3] = ' ';
    memcpy(buf + 4, mon + tm->tm_mon * 3, 3);
    buf[7] = ' ';
    p = put2(buf + 8, tm->tm_mday);
    *p++ = ' ';
    p = put2(p, tm->tm_hour);
    *p++ = ':';
    p = put2(p, tm->tm_min);
    *p++ = ':';
    p = put2(p, tm->tm_sec);
    *p++ = ' ';
    p = put2(p, tm->tm_year / 100 + 19);
    p = put2(p, tm->tm_year % 100);
    p[0] = '\n';
    p[1] = '\0';
    return buf;
}

/* " FOR FILE name\n", or just "\n" with -x */
static void forfile(char *what)
{
    if (xflag)
        out(ofile, "\n");
    else
        out(ofile, what, ifname);
}

static void dump_file_header(void)
{
    unsigned long magic, flags;
    char *proc;

    out(ofile, "\nFILE HEADER");
    forfile(" FOR FILE %s\n");
    magic = g32(filhdr);
    out(ofile, "%s", indent);
    out(ofile, "f_magic  = 0%lo", magic);
    if (!vflag)
        out(ofile, "\n");
    else {
        proc = NULL;
        switch (magic) {
        case 0x2c5: proc = "DSP56000"; break;
        case 0x2c6: proc = "DSP96000"; break;
        case 0x2c7: proc = "DSP56100"; break;
        case 0x2c8: proc = "DSP56300"; break;
        case 0x2c9: proc = "DSP56800"; break;
        case 0x2ca: proc = "DSP56600"; break;
        case 0x2cb: proc = "100"; break;
        case 0x2cc: proc = "DSP56700"; break;
        }
        if (proc == NULL)
            out(ofile, "\n");
        else
            out(ofile, " [%s]\n", proc);
    }
    out(ofile, "%s", indent);
    out(ofile, "f_nscns  = %lu\n", g32(filhdr + 4));
    if (!vflag || xflag) {
        out(ofile, "%s", indent);
        out(ofile, "f_timdat = 0x%08lX\n", g32(filhdr + 8));
    } else {
        out(ofile, "%s", indent);
        out(ofile, "f_timdat = %s", ms_asctime(cvt_time(gs32(filhdr + 8))));
    }
    out(ofile, "%s", indent);
    out(ofile, "f_symptr = %ld\n", gs32(filhdr + 12));
    out(ofile, "%s", indent);
    out(ofile, "f_nsyms  = %ld\n", gs32(filhdr + 16));
    out(ofile, "%s", indent);
    out(ofile, "f_opthdr = %lu\n", g32(filhdr + 20));
    flags = g32(filhdr + 24);
    if (!vflag) {
        out(ofile, "%s", indent);
        out(ofile, "f_flags  = 0%lo (0x%lX)\n", flags, flags);
    } else {
        out(ofile, "%s", indent);
        out(ofile, "f_flags  = ");
        if (flags == 0)
            out(ofile, "NONE\n");
        else {
            if (flags & 1)
                out(ofile, "F_RELFLG ");
            if (flags & 2)
                out(ofile, "F_EXEC ");
            if (flags & 4)
                out(ofile, "F_LNNO ");
            if (flags & 8)
                out(ofile, "F_LSYMS ");
            if (flags & 0x10)
                out(ofile, "F_MINMAL ");
            if (flags & 0x20)
                out(ofile, "F_UPDATE ");
            if (flags & 0x10000UL)
                out(ofile, "F_CC ");
            if (flags & 0x20000UL)
                out(ofile, "F_SDI ");
            out(ofile, "\n");
        }
    }
}

static int memok(long mem)
{
    return mem >= 0 && mem < NMEMS;
}

/* one address field of the optional header: memory space, address */
static void aout_addr(char *numfmt, char *symfmt, int sym, int off)
{
    out(ofile, "%s", indent);
    if (sym)
        out(ofile, symfmt, memname[gs32(aouthdr + off + 4)], g32(aouthdr + off));
    else
        out(ofile, numfmt, g32(aouthdr + off + 4), g32(aouthdr + off));
}

static void dump_optional_header(void)
{
    long endstr;
    int sym;

    if (g32(filhdr + 20) == 0)
        return;
    if (absfile) {
        out(ofile, "\nOPTIONAL HEADER");
        forfile(" FOR FILE %s\n");
        out(ofile, "%s", indent);
        out(ofile, "magic      = 0%lo\n", g32(aouthdr));
        out(ofile, "%s", indent);
        out(ofile, "vstamp     = %ld\n", gs32(aouthdr + 4));
        out(ofile, "%s", indent);
        out(ofile, "tsize      = %ld\n", gs32(aouthdr + 8));
        out(ofile, "%s", indent);
        out(ofile, "dsize      = %ld\n", gs32(aouthdr + 12));
        out(ofile, "%s", indent);
        out(ofile, "bsize      = %ld\n", gs32(aouthdr + 16));
        sym = vflag && memok(gs32(aouthdr + 0x18)) &&
            memok(gs32(aouthdr + 0x20)) && memok(gs32(aouthdr + 0x28)) &&
            memok(gs32(aouthdr + 0x30)) && memok(gs32(aouthdr + 0x38));
        out(ofile, "%s", indent);
        if (sym)
            out(ofile, "entry      = %s0x%08lX\n",
                memname[gs32(aouthdr + 0x18)], g32(aouthdr + 0x14));
        else
            out(ofile, "entry      = 0x%08lX 0x%08lX\n",
                g32(aouthdr + 0x18), g32(aouthdr + 0x14));
        aout_addr("text_start = 0x%08lX 0x%08lX\n",
                  "text_start = %s0x%08lX\n", sym, 0x1c);
        aout_addr("data_start = 0x%08lX 0x%08lX\n",
                  "data_start = %s0x%08lX\n", sym, 0x24);
        aout_addr("text_end   = 0x%08lX 0x%08lX\n",
                  "text_end   = %s0x%08lX\n", sym, 0x2c);
        aout_addr("data_end   = 0x%08lX 0x%08lX\n",
                  "data_end   = %s0x%08lX\n", sym, 0x34);
    } else {
        out(ofile, "\nLINKER HEADER");
        forfile(" FOR FILE %s\n");
        out(ofile, "%s", indent);
        out(ofile, "modsize    = %ld\n", gs32(lnkhdr));
        out(ofile, "%s", indent);
        out(ofile, "datasize   = %ld\n", gs32(lnkhdr + 4));
        endstr = gs32(lnkhdr + 8);
        if (!vflag) {
            out(ofile, "%s", indent);
            out(ofile, "endstr     = %ld\n", endstr);
        } else if (endstr < 0) {
            out(ofile, "%s", indent);
            out(ofile, "endstr     = NONE\n");
        } else {
            if (endstr < 4 || endstr > strtablen)
                error("invalid string table offset for end expression string");
            out(ofile, "%s", indent);
            out(ofile, "endstr     = %s\n", strptr(endstr));
        }
        out(ofile, "%s", indent);
        out(ofile, "secnt      = %ld\n", gs32(lnkhdr + 0x0c));
        out(ofile, "%s", indent);
        out(ofile, "ctrcnt     = %ld\n", gs32(lnkhdr + 0x10));
        out(ofile, "%s", indent);
        out(ofile, "relocnt    = %ld\n", gs32(lnkhdr + 0x14));
        out(ofile, "%s", indent);
        out(ofile, "lnocnt     = %ld\n", gs32(lnkhdr + 0x18));
        out(ofile, "%s", indent);
        out(ofile, "bufcnt     = %ld\n", gs32(lnkhdr + 0x1c));
        out(ofile, "%s", indent);
        out(ofile, "ovlcnt     = %ld\n", gs32(lnkhdr + 0x20));
        if (newlnk) {
            out(ofile, "%s", indent);
            out(ofile, "majver     = %ld\n", xflag ? 0L : gs32(lnkhdr + 0x24));
            out(ofile, "%s", indent);
            out(ofile, "minver     = %ld\n", xflag ? 0L : gs32(lnkhdr + 0x28));
            out(ofile, "%s", indent);
            out(ofile, "revno      = %ld\n", xflag ? 0L : gs32(lnkhdr + 0x2c));
        }
        if (sdihdr) {
            out(ofile, "%s", indent);
            out(ofile, "sditot     = %ld\n", gs32(lnkhdr + 0x34));
        }
    }
}

static char *section_name(unsigned char *scn)
{
    long off;

    if (g32(scn) != 0)
        return (char *)scn;
    off = gs32(scn + 4);
    if (off < 4 || off > strtablen)
        error("invalid string table offset for section header name");
    return strptr(off);
}

static void dump_section_header(unsigned char *scn, long n)
{
    unsigned long flags;

    out(ofile, "\nSECTION HEADER FOR SECTION %s (%ld)", section_name(scn), n);
    forfile(" IN FILE %s\n");
    out(ofile, "%s", indent);
    flags = g32(scn + 0x30);
    if (!vflag || !memok(gs32(scn + 0x0c)) || !memok(gs32(scn + 0x14))) {
        out(ofile, "s_paddr   = 0x%08lX 0x%08lX\n", g32(scn + 0x0c), g32(scn + 8));
        out(ofile, "%s", indent);
        out(ofile, "s_vaddr   = 0x%08lX 0x%08lX\n", g32(scn + 0x14), g32(scn + 0x10));
    } else {
        out(ofile, "s_paddr   = %s0x%08lX\n", memname[gs32(scn + 0x0c)], g32(scn + 8));
        out(ofile, "%s", indent);
        if (flags & 0x400)
            out(ofile, "s_vaddr   = %ld\n", gs32(scn + 0x10));
        else
            out(ofile, "s_vaddr   = %s0x%08lX\n", memname[gs32(scn + 0x14)],
                g32(scn + 0x10));
    }
    out(ofile, "%s", indent);
    out(ofile, "s_size    = %ld\n", gs32(scn + 0x18));
    out(ofile, "%s", indent);
    out(ofile, "s_scnptr  = %ld\n", gs32(scn + 0x1c));
    out(ofile, "%s", indent);
    out(ofile, "s_relptr  = %ld\n", gs32(scn + 0x20));
    out(ofile, "%s", indent);
    out(ofile, "s_lnnoptr = %ld\n", gs32(scn + 0x24));
    out(ofile, "%s", indent);
    out(ofile, "s_nreloc  = %lu\n", g32(scn + 0x28));
    out(ofile, "%s", indent);
    out(ofile, "s_nlnno   = %lu\n", g32(scn + 0x2c));
    if (!vflag) {
        out(ofile, "%s", indent);
        out(ofile, "s_flags   = 0%lo (0x%lX)\n", flags, flags);
        return;
    }
    out(ofile, "%s", indent);
    out(ofile, "s_flags   = ");
    if (flags & 1)
        out(ofile, "STYP_DSECT ");
    else if (flags & 2)
        out(ofile, "STYP_NOLOAD ");
    else if (flags & 4)
        out(ofile, "STYP_GROUP ");
    else if (flags & 8)
        out(ofile, "STYP_PAD ");
    else if (flags & 0x10)
        out(ofile, "STYP_COPY ");
    else {
        out(ofile, "STYP_REG ");
        if (flags & 0x80)
            out(ofile, "STYP_BSS ");
        else if (flags & 0x20)
            out(ofile, "STYP_TEXT ");
        else if (flags & 0x40)
            out(ofile, "STYP_DATA ");
        if (flags & 0x400)
            out(ofile, "STYP_BLOCK ");
        if (flags & 0x800)
            out(ofile, "STYP_OVERLAY ");
        if (flags & 0x4000)
            out(ofile, "STYP_OVERLAYP ");
        if (flags & 0x1000)
            out(ofile, "STYP_MACRO ");
        if (flags & 0x2000)
            out(ofile, "STYP_BW ");
        if (flags & 0x100)
            out(ofile, "STYP_DEBUG ");
    }
    out(ofile, "\n");
}

static void dump_raw_data(unsigned char *scn, long n)
{
    char *name;
    long size, i;
    unsigned char *buf, *p;
    size_t nbytes;

    if (g32(scn + 0x1c) == 0 || g32(scn + 0x18) == 0)
        return;
    name = section_name(scn);
    out(ofile, "\nRAW DATA FOR SECTION %s (%ld)", name, n);
    forfile(" IN FILE %s\n");
    size = gs32(scn + 0x18);
    if (size < 0)
        error("invalid raw data size in section %s", name);
    /*
     * The original allocated size << 2 bytes without a check.  When that
     * failed, MSVC's fread() into the NULL pointer failed with EINVAL.  For
     * sizes of 0x40000000 and more the byte count wrapped around to a small
     * value, the read "succeeded" and the dump printed heap memory until
     * the program crashed; that is not reproduced, such sizes fail here
     * like an allocation failure.
     */
    buf = NULL;
    nbytes = (size_t)((unsigned long)size << 2);
    if ((unsigned long)size <= 0x3fffffffUL &&
        (unsigned long)nbytes == ((unsigned long)size << 2))
        buf = (unsigned char *)malloc(nbytes);
    if (fseek(ifile, gs32(scn + 0x1c), SEEK_SET) != 0)
        error("cannot seek to raw data in section %s", name);
    if (buf == NULL) {
#ifdef EINVAL
        errno = EINVAL;
#endif
        error("cannot read raw data in section %s", name);
    }
    if (freads(buf, (size_t)size, 4, ifile) != 4)
        error("cannot read raw data in section %s", name);
    out(ofile, "%s", indent);
    p = buf;
    for (i = 0; i < size; ) {
        out(ofile, "%08lX ", g32(p));
        p += 4;
        i++;
        if (i % 4 == 0 && i < size)
            out(ofile, "\n%s", indent);
    }
    out(ofile, "\n");
    free(buf);
}

static void dump_relocation(unsigned char *scn, long n)
{
    char *name;
    unsigned char r[RELSZ];
    long i, nreloc, sym;

    if (g32(scn + 0x20) == 0 || g32(scn + 0x28) == 0)
        return;
    name = section_name(scn);
    out(ofile, "\nRELOCATION ENTRIES FOR SECTION %s (%ld)", name, n);
    forfile(" IN FILE %s\n");
    if (fseek(ifile, gs32(scn + 0x20), SEEK_SET) != 0)
        error("cannot seek to relocation entries in section %s", name);
    nreloc = gs32(scn + 0x28);
    for (i = 0; i < nreloc; i++) {
        if (freads(r, RELSZ, 1, ifile) != 1)
            error("cannot read relocation entry %ld in section %s", i, name);
        out(ofile, "%s", indent);
        out(ofile, "r_vaddr = 0x%08lX  ", g32(r));
        sym = gs32(r + 4);
        if (!vflag)
            out(ofile, "r_symndx = %ld\n", sym);
        else {
            /* the linker keeps the symbol name's string table offset here */
            if (sym < 4 || sym > strtablen)
                error("invalid string table offset for relocation entry %ld in section %s",
                      i, name);
            out(ofile, "r_symndx = %s\n", strptr(sym));
        }
    }
}

static void dump_line_numbers(unsigned char *scn, long n)
{
    char *name;
    unsigned char l[LINESZ];
    long i, nlnno, mem;
    unsigned long lnno;

    if (g32(scn + 0x24) == 0 || g32(scn + 0x2c) == 0)
        return;
    name = section_name(scn);
    out(ofile, "\nLINE NUMBER ENTRIES FOR SECTION %s (%ld)", name, n);
    forfile(" IN FILE %s\n");
    if (fseek(ifile, gs32(scn + 0x24), SEEK_SET) != 0)
        error("cannot seek to line number entries in section %s", name);
    nlnno = gs32(scn + 0x2c);
    for (i = 0; i < nlnno; i++) {
        if (freads(l, LINESZ, 1, ifile) != 1)
            error("cannot read line number entry %ld in section %s", i, name);
        out(ofile, "%s", indent);
        lnno = g32(l + 8);
        out(ofile, "l_lnno = %4lu  ", lnno);
        mem = gs32(l + 4);
        if (lnno == 0)
            out(ofile, "l_symndx = %ld\n", gs32(l));
        else if (!vflag || !memok(mem))
            out(ofile, "l_paddr  = 0x%08lX 0x%08lX\n", g32(l + 4), g32(l));
        else
            out(ofile, "l_paddr  = %s0x%08lX\n", memname[mem], g32(l));
    }
}

static void dump_sections(void)
{
    unsigned char scn[SCNHSZ + 4];     /* +4: terminator for 8-char names
                                           running over the whole header */
    long i;

    memset(scn, 0, sizeof scn);
    for (i = 0; i < nscns; i++) {
        if (fseek(ifile, scnptr, SEEK_SET) != 0)
            error("cannot seek to section headers");
        if (freads(scn, SCNHSZ, 1, ifile) != 1)
            error("cannot read section headers");
        if (g32(scn) != 0)
            swapw(scn, 4, 2);
        scnptr = s32((unsigned long)scnptr + SCNHSZ);
        if (hflag)
            dump_section_header(scn, i + 1);
        if (sflag)
            dump_raw_data(scn, i + 1);
        if (rflag)
            dump_relocation(scn, i + 1);
        if (lflag)
            dump_line_numbers(scn, i + 1);
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

/*
 * Format a double like MSVC's "%-.6E": at least three exponent digits,
 * no sign for -0, and MSVC's spelling of infinities and NaNs.
 */
static char *fmt_double(unsigned long hi, unsigned long lo)
{
    static char buf[80];
    char *e, *sign;
    int n;

    sign = (hi & 0x80000000UL) ? "-" : "";
    if (((hi >> 20) & 0x7ff) == 0x7ff) {
        if ((hi & 0xfffffUL) == 0 && (lo & 0xffffffffUL) == 0)
            sprintf(buf, "%s1.#INF00E+000", sign);
        else if (hi & 0x80000000UL && (hi & 0xfffffUL) == 0x80000UL &&
                 (lo & 0xffffffffUL) == 0)
            sprintf(buf, "-1.#IND00E+000");
        else if (hi & 0x80000UL)
            sprintf(buf, "%s1.#QNAN0E+000", sign);
        else
            sprintf(buf, "%s1.#SNAN0E+000", sign);
        return buf;
    }
    if ((hi & 0x7fffffffUL) == 0 && (lo & 0xffffffffUL) == 0)
        hi = 0;                         /* MSVC prints -0 without the sign */
    sprintf(buf, "%-.6E", mkdouble(hi, lo));
    e = strchr(buf, 'E');
    if (e != NULL && (e[1] == '+' || e[1] == '-')) {
        n = (int)strlen(e + 2);
        if (n < 3) {
            memmove(e + 2 + (3 - n), e + 2, (size_t)n + 1);
            memset(e + 2, '0', (size_t)(3 - n));
        }
    }
    return buf;
}

static char *sclass_name(long sclass)
{
    switch (sclass) {
    case -1: return "C_EFCN";
    case 0: return "C_NULL";
    case 1: return "C_AUTO";
    case 2: return "C_EXT";
    case 3: return "C_STAT";
    case 4: return "C_REG";
    case 5: return "C_EXTDEF";
    case 6: return "C_LABEL";
    case 7: return "C_REG";             /* sic, should be C_ULABEL */
    case 8: return "C_MOS";
    case 9: return "C_ARG";
    case 10: return "C_STRTAG";
    case 11: return "C_MOU";
    case 12: return "C_UNTAG";
    case 13: return "C_TPDEF";
    case 14: return "C_USTATIC";
    case 15: return "C_ENTAG";
    case 16: return "C_MOE";
    case 17: return "C_REGPARM";
    case 18: return "C_FIELD";
    case 19: return "C_MEMREG";
    case 20: return "C_OPTIMIZED";
    case 100: return "C_BLOCK";
    case 101: return "C_FCN";
    case 102: return "C_EOS";
    case 103: return "C_FILE";
    case 104: return "C_LINE";
    case 105: return "C_ALIAS";
    case 106: return "C_HIDDEN";
    case 128: return "C_SECT";
    case 129: return "C_SDI";
    case 200: return "A_FILE";
    case 201: return "A_SECT";
    case 202: return "A_BLOCK";
    case 203: return "A_MACRO";
    case 210: return "A_GLOBAL";
    case 211: return "A_XDEF";
    case 212: return "A_XREF";
    case 213: return "A_SLOCAL";
    case 214: return "A_ULOCAL";
    case 215: return "A_MLOCAL";
    }
    return "<unknown>";
}

static void dump_symbol(unsigned char *sym, long symno)
{
    char *name, *cname, *sname;
    long sclass, scnum, mem, off;
    unsigned long type, t, base;
    int file;

    if (g32(sym) != 0) {
        swapw(sym, 4, 2);
        name = (char *)sym;
    } else {
        off = gs32(sym + 4);
        if (off < 4 || off > strtablen)
            error("invalid string table offset for symbol table entry %ld name",
                  symno);
        name = strptr(off);
    }
    out(ofile, "%-6ld  ", symno);
    /* an 8-character name runs on into n_value, as in the original */
    out(ofile, "n_name = %-16s  ", name);
    sclass = gs32(sym + 0x18);
    cname = sclass_name(sclass);
    type = g32(sym + 0x14);
    mem = gs32(sym + 0x0c);
    if (!vflag)
        out(ofile, "n_value = 0x%08lX 0x%08lX\n", g32(sym + 0x0c), g32(sym + 8));
    else if ((type & 0x1000fUL) == 6)
        out(ofile, "n_value = %s\n", fmt_double(g32(sym + 0x0c), g32(sym + 8)));
    else if ((type & 0x1000fUL) == 5)
        out(ofile, "n_value = 0x%08lX 0x%08lX\n", g32(sym + 0x0c), g32(sym + 8));
    else if (mem < 0 || mem >= 0x124 || mem == 4 || !memok(mem))
        out(ofile, "n_value = 0x%08lX\n", g32(sym + 8));
    else
        out(ofile, "n_value = %s0x%08lX\n", memname[mem], g32(sym + 8));
    out(ofile, "%s", indent);
    out(ofile, "%s", indent);
    scnum = gs32(sym + 0x10);
    if (scnum == -2)
        sname = "N_DEBUG";
    else if (scnum == -1)
        sname = "N_ABS";
    else if (scnum == 0)
        sname = "N_UNDEF";
    else
        sname = "";
    if (!vflag || *sname == '\0')
        out(ofile, "n_scnum = % 5ld  ", scnum);
    else
        out(ofile, "n_scnum = %s  ", sname);
    base = (type & 0xf) | ((type & 0x10000UL) >> 12);
    file = sclass == 0x67 || sclass == 200;
    if (!vflag || (file && base > 2) || (!file && base > 22))
        out(ofile, "n_type = 0%lo (0x%lX)  ", type, type);
    else {
        if ((file && base == 2) || (!file && base == 22)) {
            /*
             * The original checked the index against the table size with
             * <= and took the word behind the table (the size itself) as
             * a string pointer: it crashed in printf after "n_type = ".
             */
            out(ofile, "n_type = ");
            onsig(SIGSEGV);
        }
        out(ofile, "n_type = %s", file ? ftypes[base] : types[base]);
        for (t = type & 0xfffefff0UL; t != 0; t = (t >> 2) & 0xfffefff0UL) {
            if ((t & 0x30) == 0x20)
                out(ofile, ",DT_FCN");
            else if ((t & 0x30) == 0x10)
                out(ofile, ",DT_PTR");
            else if ((t & 0x30) == 0x30) {
                out(ofile, ",DT_ARY");
                aryflag = 1;
            }
        }
        out(ofile, "  ");
    }
    if (!vflag)
        out(ofile, "n_sclass = %ld  ", sclass);
    else
        out(ofile, "n_sclass = %s  ", cname);
    out(ofile, "n_numaux = %ld\n", gs32(sym + 0x1c));
}

/* -x: turn a DOS/VMS/Mac file name into a Unix-style one */
static void fix_path(char *s)
{
    int vms;
    char *p, *q;

    vms = 0;
    if (*s == ':' || *s == '[') {
        if (*s == '[')
            vms = 1;
        for (p = s, q = s + 1; *q != '\0'; p++, q++)
            *p = *q;
        *p = '\0';
    }
    for (p = s; *p != '\0'; p++) {
        if (*p == '\\' || *p == ':' || (*p == '.' && vms))
            *p = '/';
        else if (*p == ']') {
            vms = 0;
            *p = '/';
        }
    }
}

/* auxiliary entry j of a section symbol */
static void dump_section_aux(unsigned char *aux, long j)
{
    switch (j) {
    case 0:
        out(ofile, "scnlen = %6ld  ", gs32(aux));
        out(ofile, "nreloc = %4lu  ", g32(aux + 4));
        out(ofile, "nlinno = %4lu  ", g32(aux + 8));
        break;
    case 1:
        if (!newlnk) {
            out(ofile, "secno = %4ld  ", gs32(aux));
            out(ofile, "rsecno = %4ld  ", gs32(aux + 4));
            out(ofile, "mem = 0x%04lX  ", g32(aux + 8));
            out(ofile, "flags = 0x%08lX  ", g32(aux + 0x0c));
            if (g32(aux + 0x0c) & 0x6000) {
                out(ofile, "\n");
                out(ofile, "%s", indent);
                out(ofile, "%s", indent);
                if (g32(aux + 0x0c) & 0x2000) {
                    out(ofile, "bufcnt = %4ld  ", gs32(aux + 0x10));
                    out(ofile, "buftyp = 0x%04lX  ", g32(aux + 0x14));
                    out(ofile, "buflim = %6ld  ", gs32(aux + 0x18));
                } else if (g32(aux + 0x0c) & 0x4000) {
                    out(ofile, "ovlcnt = %4ld  ", gs32(aux + 0x10));
                    out(ofile, "ovlmem = 0x%04lX  ", g32(aux + 0x14));
                    out(ofile, "ovlstr = %6ld  ", gs32(aux + 0x18));
                }
            }
        } else {
            ovlflags = g32(aux + 8);
            out(ofile, "secno = %4ld  ", gs32(aux));
            out(ofile, "rsecno = %4ld  ", gs32(aux + 4));
            out(ofile, "flags = 0x%08lX  ", g32(aux + 8));
            out(ofile, "\n");
            out(ofile, "%s", indent);
            out(ofile, "%s", indent);
            out(ofile, "mspace = %4ld  ", gs32(aux + 0x0c));
            out(ofile, "mmap = %4ld  ", gs32(aux + 0x10));
            out(ofile, "mcntr = %4ld  ", gs32(aux + 0x14));
            out(ofile, "mclass = %4ld  ", gs32(aux + 0x18));
        }
        break;
    case 2:
        if (ovlflags & 0x2000) {
            out(ofile, "bufcnt = %4ld  ", gs32(aux));
            out(ofile, "buftyp = 0x%04lX  ", g32(aux + 4));
            out(ofile, "buflim = %6ld  ", gs32(aux + 8));
        } else if (ovlflags & 0x4000) {
            out(ofile, "ovlcnt = %4ld  ", gs32(aux + 0x10));
            out(ofile, "ovlstr = %6ld  ", gs32(aux + 0x14));
            out(ofile, "ovloff = 0x%08lX  ", g32(aux + 0x18));
            out(ofile, "\n");
            out(ofile, "%s", indent);
            out(ofile, "%s", indent);
            out(ofile, "ovlmem.mspace = %4ld  ", gs32(aux));
            out(ofile, "ovlmem.mmap = %4ld  ", gs32(aux + 4));
            out(ofile, "ovlmem.mcntr = %4ld  ", gs32(aux + 8));
            out(ofile, "ovlmem.mclass = %4ld  ", gs32(aux + 0x0c));
        }
        break;
    case 3:
        out(ofile, "ovlcnt = %4ld  ", gs32(aux + 0x10));
        out(ofile, "ovlstr = %6ld  ", gs32(aux + 0x14));
        out(ofile, "ovloff = 0x%08lX  ", g32(aux + 0x18));
        out(ofile, "\n");
        out(ofile, "%s", indent);
        out(ofile, "%s", indent);
        out(ofile, "ovlmem.mspace = %4ld  ", gs32(aux));
        out(ofile, "ovlmem.mmap = %4ld  ", gs32(aux + 4));
        out(ofile, "ovlmem.mcntr = %4ld  ", gs32(aux + 8));
        out(ofile, "ovlmem.mclass = %4ld  ", gs32(aux + 0x0c));
        break;
    }
}

static void dump_aux(unsigned char *sym, unsigned char *aux, long symno, long j)
{
    unsigned char *p;
    char *fname;
    long sclass, off, i;
    unsigned long type;

    out(ofile, "%-6ld  ", symno);
    if (!vflag) {
        swapw(aux, 1, AUXESZ);          /* back to file order */
        for (p = aux; p < aux + AUXESZ; p++) {
            out(ofile, "%1X", (*p >> 4) & 0xf);
            out(ofile, "%1X ", *p & 0xf);
        }
        out(ofile, "\n");
        return;
    }
    sclass = gs32(sym + 0x18);
    type = g32(sym + 0x14);
    if (sclass == 0x67 || sclass == 200) {
        if (g32(aux + 0x10) == 0) {
            swapw(aux, 1, 16);
            fname = (char *)aux;
        } else {
            off = gs32(aux + 0x10);
            if (g32(aux + 0x10) < 4 || off > strtablen)
                error("invalid string table offset for file name");
            fname = strptr(off);
        }
        if (xflag)
            fix_path(fname);            /* in place, also in the string table */
        out(ofile, "fname = %s  ", fname);
        if (g32(aux + 0x14) != 0)
            out(ofile, "x_ftype = 0x%04lX  ", g32(aux + 0x14));
    } else if (sclass == 3 && (type & 0x1000fUL) == 0)
        dump_section_aux(aux, j);
    else if (sclass == 10 || sclass == 12 || sclass == 15) {
        out(ofile, "size = %4lu  ", g32(aux + 8));
        out(ofile, "endndx = %6ld  ", gs32(aux + 0x10));
    } else if (sclass == 0x66) {
        out(ofile, "tagndx = %6ld  ", gs32(aux));
        out(ofile, "size = %4ld  ", gs32(aux + 8));
    } else if (sclass == 0x65 || sclass == 0x64) {
        out(ofile, "lnno = %4ld  ", gs32(aux + 4));
        out(ofile, "endndx = %6ld  ", gs32(aux + 0x10));
        if (sclass == 0x65 && g32(aux + 0x14) != 0)
            out(ofile, "x_type = 0x%04lX  ", g32(aux + 0x14));
    } else if (sclass == 0xc9) {
        out(ofile, "tagndx = %6ld  ", gs32(aux));
        out(ofile, "lnno = %4ld  ", gs32(aux + 4));
        out(ofile, "endndx = %6ld  ", gs32(aux + 0x10));
    } else if (sclass == 0xcb) {
        out(ofile, "lnno = %4ld  ", gs32(aux + 4));
        out(ofile, "endndx = %6ld  ", gs32(aux + 0x10));
    } else if (sclass == 0x12)
        out(ofile, "size = %4lu  ", g32(aux + 8));
    else if ((type & 0x30) == 0x20) {
        out(ofile, "tagndx = %6ld  ", gs32(aux));
        out(ofile, "fsize = %6ld  ", gs32(aux + 4));
        out(ofile, "lnnoptr = %6ld  ", gs32(aux + 0x0c));
        out(ofile, "endndx = %6ld  ", gs32(aux + 0x10));
    } else if (aryflag) {
        aryflag = 0;
        out(ofile, "tagndx = %6ld  ", gs32(aux));
        out(ofile, "lnno = %4ld  ", gs32(aux + 4));
        out(ofile, "size = %4lu  ", g32(aux + 8));
        for (i = 0; i < 4 && g32(aux + 0x0c + i * 4) != 0; i++)
            out(ofile, "dimen[%ld] = %4lu  ", i, g32(aux + 0x0c + i * 4));
    } else if (type == 8 || type == 9 || type == 10) {
        out(ofile, "tagndx = %6ld  ", gs32(aux));
        out(ofile, "size = %4ld", gs32(aux + 8));
    }
    out(ofile, "\n");
}

static void dump_symbols(void)
{
    unsigned char sym[SYMESZ + 4];      /* +4: terminator for 8-char names */
    unsigned char aux[AUXESZ];
    long i, j, numaux;

    if (symptr == 0 || nsyms == 0)
        return;
    out(ofile, "\nSYMBOL TABLE");
    forfile(" FOR FILE %s\n");
    if (fseek(ifile, symptr, SEEK_SET) != 0)
        error("cannot seek to symbol table");
    memset(sym, 0, sizeof sym);
    i = 0;
    while (i < nsyms) {
        if (freads(sym, SYMESZ, 1, ifile) != 1)
            error("cannot read symbol table entry %ld", i);
        dump_symbol(sym, i);
        numaux = gs32(sym + 0x1c);
        i++;
        for (j = 0; j < numaux; j++) {
            if (freads(aux, AUXESZ, 1, ifile) != 1)
                error("cannot read auxiliary entry %ld for symbol entry %ld", j, i);
            dump_aux(sym, aux, i, j);
            i++;
        }
    }
}

static void dump_string_table(void)
{
    long off;
    char *p;
    size_t n;

    if (strtablen == 0)
        return;
    out(ofile, "\nSTRING TABLE");
    forfile(" FOR FILE %s\n");
    out(ofile, "%-8ld%ld  (string table length)\n", 0L, strtablen);
    off = 4;
    p = strtab;
    do {
        out(ofile, "%-8ld%s\n", off, p);
        n = strlen(p);
        off += (long)n + 1;
        p += n + 1;
    } while (p < strtab + strtablen);
}

static void dump_file(void)
{
    read_headers();
    read_strtab();
    if (fflag)
        dump_file_header();
    if (oflag)
        dump_optional_header();
    if (hflag || rflag || lflag || sflag)
        dump_sections();
    if (tflag)
        dump_symbols();
    if (cflag)
        dump_string_table();
}

int main(int argc, char **argv)
{
    int c, i, cleared;

    for (i = 0; i < 256; i++) {
        sprintf(enames[i], "E%d:", i);
        memname[0x1d + i] = enames[i];
    }
    memname[0x11d] = "D:";
    memname[0x11e] = "P8:";
    memname[0x11f] = "U:";
    memname[0x120] = "U8:";
    memname[0x121] = "U16:";
    errno = 0;

    cleared = 0;
    signal(SIGINT, onsig);
    signal(SIGSEGV, onsig);
    qflag = getflag('q', argc, argv) != NULL;
    if (!qflag)
        fprintf(stderr, "%s  %s\n%s\n", title, version, copyright);
    while ((c = get_opt(argc, argv, "CcD:d:FfHhLlOoQqRrSsTtVvXx")) != -1) {
        if (!cleared && strchr("DdQqVvXx", c) == NULL) {
            clear_flags();
            cleared = 1;
        }
        if (isupper(c))
            c = tolower(c);
        switch (c) {
        case 'c': cflag = 1; break;
        case 'd': ofname = optarg_; break;
        case 'f': fflag = 1; break;
        case 'h': hflag = 1; break;
        case 'l': lflag = 1; break;
        case 'o': oflag = 1; break;
        case 'q': qflag = 1; break;
        case 'r': rflag = 1; break;
        case 's': sflag = 1; break;
        case 't': tflag = 1; break;
        case 'v': vflag = 1; break;
        case 'x': xflag = 1; break;
        default: usage(); break;
        }
    }
    if (ofname == NULL)
        ofile = stdout;
    else {
        ofile = fopen(ofname, "w");
        if (ofile == NULL)
            error("cannot open output file %s", ofname);
    }
    if (optind_ >= argc)
        usage();
    if (argv[optind_][0] == '-') {
        /* "-" (or anything after "--" starting with '-'): standard input */
        ifname = "stdin";
        ifile = stdin;
        dump_file();
    } else {
        while (optind_ < argc) {
            ifname = argv[optind_++];
            ifile = fopen(ifname, "rb");
            if (ifile == NULL)
                error("cannot open input file %s", ifname);
            dump_file();
            fclose(ifile);
        }
    }
    exit(0);
    return 0;
}
