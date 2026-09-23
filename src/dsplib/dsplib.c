/*
 * dsplib - DSP object module librarian
 *
 * Reconstructed from Motorola DSPLIB.EXE, "DSP Librarian Version 6.3"
 * (CLAS56 v6.3, 1998); $Id: dsplib.c,v 1.43 1998/09/10 21:43:24 jay Exp $.
 *
 * Command line:  dsplib -command library [files...]
 *   -a add, -c create, -d delete, -x extract, -l list, -r replace,
 *   -u update (replace or add at end; the default when module names are
 *   given), -v version, -q quiet, -ea/-ew <file> append/write error output
 *   to a file, -f <file> read further module names from a command file.
 *   Without any option and without module names the library is listed.
 *   Without any argument the librarian reads commands from stdin
 *   ("add lib mods...", "list lib", "quit", "help", ...; see help()).
 *   A library name without an extension gets ".clb" (".CLB" when the
 *   name has no lower case letter).
 *
 * Library file format: a plain concatenation of members, no library
 * header and no directory.  Every member is
 *     "!<H> <name> <size> <time>\r\n"  followed by <size> bytes
 * where <name> is the lower-cased base name of the module file, <size>
 * its length in bytes and <time> the time the member was put into the
 * library (time() of the librarian run, seconds since 1970, decimal) -
 * not the file's modification time.  The member bytes are copied
 * verbatim (they are DSP COFF objects, but the librarian never looks
 * inside them).  An older format "-h- <name> <size> <time>\r\n" followed
 * by <size> bytes and one pad byte is still read; members copied through
 * create/add/delete/replace/update are rewritten in the new format.
 *
 * Portability notes / deviations from the Win32 original:
 * - Only ANSI C.  _stat() (module size) is replaced by fopen/fseek/ftell,
 *   _mktemp() by an fopen() probe of "lb" + letter + 5 digits in the
 *   library directory (the original used the process id for the digits,
 *   so temporary file names differ), MoveFileA by rename(), gets() by a
 *   bounded getchar() loop.
 * - The interactive prompt "> " is printed only when stdin is a terminal
 *   (isatty); ANSI C cannot tell, so the prompt is printed only when
 *   compiled with -DDSPLIB_PROMPT.
 * - setargv.obj (wildcard expansion of command line arguments by the
 *   Win32 C runtime) is not reproduced; the shell has to expand them.
 * - The current time comes from now(): SOURCE_DATE_EPOCH when set, else
 *   time(NULL); time_t is assumed to count seconds since 1970.
 * - Where the original dereferences a null pointer on realistic input
 *   (-e as last argument; interactive update/replace without module
 *   names) the port explicitly calls the SIGSEGV handler, which prints
 *   the original's message.  printf("%s", NULL) prints "(null)" as MSVC.
 * - '/' separates directories as well as the original's '\\' and ':', so
 *   path names also work on Unix-like hosts (NeXT, MiNT).
 * - Buffers are bounded where the original overran them (input lines and
 *   header lines over 511 characters, more than 2000 module names);
 *   characters >= 0x80 are not letters/spaces here while the original
 *   indexed its ctype table with a negative value.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>
#include <time.h>

#define LINESZ  512             /* size of the original's line buffers */
#define MAXMODS 2000            /* size of the module "found" flag array */
#define BUFSZ   0x2000          /* copy/input/output buffer size */
#define MINBUF  0x200

/* commands */
#define C_ADD     1
#define C_CREATE  2
#define C_DELETE  3
#define C_EXTRACT 4
#define C_LIST    5
#define C_REPLACE 6
#define C_UPDATE  7
#define C_QUIT    8
#define C_HELP    9
#define C_VERSION 10

static char rcsid[] = "$Id: dsplib.c,v 1.43 1998/09/10 21:43:24 jay Exp $";

static char *optarg_;                   /* 00413040 */
static char *optarg2;                   /* 00413044 second argument (E::) */
static int optind_;                     /* 00413048 */
static char *optnext;                   /* 004136a0 */
static int cmd = C_UPDATE;              /* 0040f064 */
static char libname[LINESZ];            /* 00413050 */
static char *libfn = libname;           /* 0040f068 */
static int nmods;                       /* 00413250 */
static char **mods;                     /* 00413254 */
static int oldfmt;                      /* 00413258 last header was "-h-" */
static int errors;                      /* 0041325c */
static int quiet;                       /* 00413264 */
static char *tmpdir;                    /* 00413268 */
static char tmpname[LINESZ];            /* 00413270 also the -f file name */
static char libdir[LINESZ];             /* 00413470 */
static FILE *libfp, *modfp, *tmpfp;     /* 00413670/74/78 */
static char *copybuf;                   /* 0041367c */
static size_t copysize;                 /* 00413680 */
static char *inbuf;                     /* 00413684 */
static size_t insize;                   /* 00413688 */
static char *outbuf;                    /* 0041368c */
static size_t outsize;                  /* 00413690 */
static int interact;                    /* 00413698 */
static int interrupted;                 /* 0041369c */
static jmp_buf jmpbuf;                  /* 00413000 */
static char found[MAXMODS];             /* 00412820 */
static char tmptempl[16];               /* 00412ff0 */
static FILE *errfp;                     /* 0040f098 (stderr) */
static char *progname = "dsplib";       /* 0040f148 */

static char magic[] = "!<H>";           /* 0040f070 */
static char oldmagic[] = "-h-";         /* 0040f06c */
static char prompt[] = "> ";            /* 0040f078 */
static char defext[] = ".clb";          /* 0040f090 */

static struct cmdtab {                  /* 0040f0a0 */
    char *name;
    int minlen;
    int code;
} cmds[] = {
    { "?", 1, C_HELP },
    { "add", 1, C_ADD },
    { "create", 1, C_CREATE },
    { "delete", 1, C_DELETE },
    { "exit", 3, C_QUIT },
    { "extract", 3, C_EXTRACT },
    { "help", 1, C_HELP },
    { "list", 1, C_LIST },
    { "quit", 1, C_QUIT },
    { "replace", 1, C_REPLACE },
    { "update", 1, C_UPDATE },
    { "version", 1, C_VERSION },
    { "xtract", 1, C_EXTRACT }
};
static int ncmds = sizeof(cmds) / sizeof(cmds[0]);      /* 0040f13c */

struct arg {                            /* saved argument list */
    char *s;
    struct arg *next;
};

static void update_lib(void);
static void delete_lib(void);
static void extract_lib(void);
static void list_lib(void);
static void copy_lib(FILE *in, FILE *out);
static void add_module(char *name, FILE *out);
static void rename_lib(char *from, char *to);
static int swap_rename(char *from, char *to);
static void copy_file(FILE *in, FILE *out);
static void copy_bytes(FILE *in, FILE *out, long n);
static void check_dups(void);
static FILE *open_file(char *name, char *mode, int buffered);
static char *make_header(char *name, char *buf);
static char *read_header(FILE *fp, char *buf);
static void write_header(FILE *fp, char *s);
static void list_module(char *line);
static int find_module(char *name);
static void report_missing(void);
static void default_ext(char *name, char *ext);
static char *basename_(char *path);
static char *strlower(char *s);
static void onsig(int sig);
static int parse_cmd(char *line);
static int lookup_cmd(char *word);
static int cmdfile_args(int argc, char ***argvp);
static int read_cmdfile(char *name, struct arg **tailp);
static char *findopt(int c, int argc, char **argv);
static int findopt_idx(int c, int argc, char **argv);
static void set_errfile(char **argv, int idx);
static int getopt_(int argc, char **argv, char *opts);
static char *make_tmpname(char *buf);
static void usage(void);
static void signon(void);
static void help(void);
static char *xmalloc(size_t n);
static void error0(char *msg);
static void error(char *fmt, char *arg);
static void fatal0(char *msg);
static void cleanup(void);
static void fatal(char *fmt, char *arg);

/* MSVC prints "(null)" for a null %s argument */
static char *nn(char *s)
{
    return s != NULL ? s : "(null)";
}

/* the current time: SOURCE_DATE_EPOCH if set (for reproducible tests) */
static long now(void)
{
    char *s, *end;
    long t;

    s = getenv("SOURCE_DATE_EPOCH");
    if (s != NULL && *s != '\0') {
        t = strtol(s, &end, 10);
        if (*end == '\0')
            return t;
    }
    return (long)time(NULL);
}

/* 0040157b */
static void init_globals(void)
{
    optarg_ = NULL;
    optarg2 = NULL;
    optind_ = 0;
    cmd = C_UPDATE;
    libname[0] = '\0';
    libfn = libname;
    nmods = 0;
    mods = NULL;
    oldfmt = 0;
    errors = 0;
    quiet = 0;
    libdir[0] = '\0';
    interact = 0;
    interrupted = 0;
}

/* gets() replacement; the original overran its 512 byte buffer */
static char *getline_(char *buf)
{
    int c;
    char *p;

    p = buf;
    while ((c = getchar()) != '\n') {
        if (c == EOF) {
            if (p == buf)
                return NULL;
            break;
        }
        if (p < buf + LINESZ - 1)
            *p++ = (char)c;
    }
    *p = '\0';
    return buf;
}

/* 00401610 - read commands from stdin */
static void interactive(void)
{
    char line[LINESZ];

    interact = 1;
    setjmp(jmpbuf);
    for (;;) {
        cmd = C_UPDATE;
        tmpname[0] = '\0';
        libname[0] = tmpname[0];
        libfn = libname;
        mods = NULL;
        errors = 0;
        nmods = errors;
        check_dups();
#ifdef DSPLIB_PROMPT
        /* original: only if isatty(fileno(stdin)) */
        fprintf(stdout, "%s", prompt);
        fflush(stdout);
#else
        (void)prompt;
#endif
        if (getline_(line) == NULL)
            exit(0);
        cmd = parse_cmd(line);
        switch (cmd) {
        case C_ADD:
        case C_CREATE:
        case C_REPLACE:
        case C_UPDATE:
            update_lib();
            break;
        case C_DELETE:
            delete_lib();
            break;
        case C_EXTRACT:
            extract_lib();
            break;
        case C_LIST:
            list_lib();
            break;
        case C_QUIT:
            exit(0);
        case C_HELP:
            help();
            break;
        case C_VERSION:
            signon();
            break;
        }
    }
}

/* 0040178b - create, add, replace, update */
static void update_lib(void)
{
    FILE *fp;
    int i;

    if (make_tmpname(tmpname) == NULL)
        fatal0("cannot create temporary file name");
    tmpfp = open_file(tmpname, "wb", 1);
    if (tmpfp == NULL)
        fatal("cannot open temporary file %s", tmpname);
    if (cmd == C_CREATE) {
        /* the stream is left open, as in the original */
        fp = open_file(libfn, "rb", 0);
        if (fp != NULL)
            fatal("library file %s already exists", libfn);
    } else {
        if (cmd == C_ADD && nmods <= 0)
            fatal0("add requires explicit module names");
        libfp = open_file(libfn, "rb", 1);
        if (libfp == NULL)
            fatal("cannot open library file %s", libfn);
        copy_lib(libfp, tmpfp);
        fclose(libfp);
        libfp = NULL;
    }
    for (i = 0; i < nmods; i++) {
        if (i < MAXMODS && found[i]) {
            if (cmd == C_ADD)
                error("%s already in library", mods[i]);
        } else if (cmd == C_REPLACE) {
            error("%s not in library", mods[i]);
        } else {
            add_module(mods[i], tmpfp);
            if (i < MAXMODS)
                found[i] = 1;
        }
    }
    fclose(tmpfp);
    tmpfp = NULL;
    if (errors == 0)
        rename_lib(tmpname, libfn);
    else
        fatal("fatal errors - %s not altered", libfn);
}

/* 00401991 */
static void delete_lib(void)
{
    if (nmods <= 0)
        fatal0("delete requires explicit module names");
    libfp = open_file(libfn, "rb", 1);
    if (libfp == NULL)
        fatal("cannot open library file %s", libfn);
    if (make_tmpname(tmpname) == NULL)
        fatal0("cannot create temporary file name");
    tmpfp = open_file(tmpname, "wb", 1);
    if (tmpfp == NULL)
        fatal("cannot open temporary file %s", tmpname);
    copy_lib(libfp, tmpfp);
    report_missing();
    fclose(libfp);
    fclose(tmpfp);
    tmpfp = NULL;
    libfp = tmpfp;
    if (errors == 0)
        rename_lib(tmpname, libfn);
    else
        fatal("fatal errors - %s not altered", libfn);
}

/* 00401ab4 */
static void extract_lib(void)
{
    char name[LINESZ], line[LINESZ];
    long size;

    libfp = open_file(libfn, "rb", 1);
    if (libfp == NULL)
        fatal("cannot open library file %s", libfn);
    /* the original leaves both unset before the first header */
    name[0] = '\0';
    size = 0;
    while (read_header(libfp, line) != NULL) {
        sscanf(line, "%*s %s %ld", name, &size);
        if (find_module(name) == 0) {
            fseek(libfp, size + oldfmt, SEEK_CUR);
            continue;
        }
        modfp = open_file(name, "wb", 0);
        if (modfp == NULL) {
            error("cannot open module file %s", name);
            fseek(libfp, size + oldfmt, SEEK_CUR);
            continue;
        }
        copy_bytes(libfp, modfp, size);
        if (oldfmt)
            getc(libfp);
        fclose(modfp);
        modfp = NULL;
    }
    fclose(libfp);
    libfp = NULL;
    report_missing();
}

/* 00401c78 */
static void list_lib(void)
{
    char name[LINESZ], line[LINESZ];
    long size;

    libfp = open_file(libfn, "rb", 1);
    if (libfp == NULL)
        fatal("cannot open library file %s", libfn);
    name[0] = '\0';
    size = 0;
    while (read_header(libfp, line) != NULL) {
        sscanf(line, "%*s %s %ld", name, &size);
        if (find_module(name) != 0)
            list_module(line);
        fseek(libfp, size + oldfmt, SEEK_CUR);
    }
    fclose(libfp);
    libfp = NULL;
    report_missing();
}

/* 00401d51 - copy the library, replacing or dropping named members */
static void copy_lib(FILE *in, FILE *out)
{
    char name[LINESZ], line[LINESZ];
    long size;
    int idx;

    name[0] = '\0';
    size = 0;
    while (read_header(in, line) != NULL) {
        sscanf(line, "%*s %s %ld", name, &size);
        idx = find_module(name);
        if (idx != 0) {
            if (cmd != C_DELETE) {
                /* no module vector in interactive mode: null dereference */
                if (mods == NULL)
                    onsig(SIGSEGV);
                add_module(mods[idx - 1], out);
            }
            fseek(in, size + oldfmt, SEEK_CUR);
            continue;
        }
        if (oldfmt) {
            sprintf(name, "%s%s", magic, line + strlen(oldmagic));
            strcpy(line, name);
        }
        write_header(out, line);
        copy_bytes(in, out, size);
        if (oldfmt)
            getc(in);
    }
}

/* 00401ebe - append a module file as a new member */
static void add_module(char *name, FILE *out)
{
    char hdr[LINESZ];

    modfp = name != NULL ? open_file(name, "rb", 0) : NULL;
    if (modfp == NULL)
        error("cannot open module file %s", nn(name));
    if (errors == 0) {
        make_header(name, hdr);
        write_header(out, hdr);
        copy_file(modfp, out);
        fclose(modfp);
        modfp = NULL;
    }
}

/* 00401f58 */
static void rename_lib(char *from, char *to)
{
    if (rename(from, to) != 0 && swap_rename(from, to) != 0)
        fatal("cannot rename %s", from);
    remove(from);
}

/* 00401fa2 - rename when the target exists (MoveFileA does not replace) */
static int swap_rename(char *from, char *to)
{
    char save[LINESZ];

    if (rename(from, to) == 0)
        return 0;
    if (make_tmpname(save) == NULL)
        fatal0("cannot create temporary file name");
    if (rename(to, save) != 0)
        return -1;
    if (rename(from, to) != 0) {
        if (rename(save, to) != 0)
            fatal("cannot rename %s", save);
        return -1;
    }
    remove(save);
    return 0;
}

/* 0040205b - copy a whole file */
static void copy_file(FILE *in, FILE *out)
{
    size_t n;

    clearerr(in);
    while ((n = fread(copybuf, 1, copysize, in)) > 0) {
        if (fwrite(copybuf, 1, n, out) != n)
            fatal0("error writing file");
    }
    if (ferror(in) && !feof(in))
        fatal0("error reading file");
}

/* 004020e6 - copy n bytes */
static void copy_bytes(FILE *in, FILE *out, long n)
{
    long blocks, i;
    size_t rest;

    /* a negative size (corrupt header) makes the original misbehave */
    if (n < 0)
        n = 0;
    blocks = n / (long)copysize;
    rest = (size_t)(n % (long)copysize);
    for (i = 0; i < blocks; i++) {
        if (fread(copybuf, 1, copysize, in) != copysize ||
            fwrite(copybuf, 1, copysize, out) != copysize)
            fatal0("file I/O error");
    }
    if (fread(copybuf, 1, rest, in) != rest ||
        fwrite(copybuf, 1, rest, out) != rest)
        fatal0("file I/O error");
}

/* 004021c2 */
static void check_dups(void)
{
    int i, j;

    for (i = 0; i < MAXMODS; i++)
        found[i] = 0;
    for (i = 0; i < nmods - 1; i++)
        for (j = i + 1; j < nmods; j++)
            if (strcmp(mods[i], mods[j]) == 0)
                error("duplicate module name %s", mods[i]);
}

/* 00402334 - set Macintosh file type/creator; a no-op elsewhere */
static int set_file_type(char *name, char *type, char *creator)
{
    (void)name;
    (void)type;
    (void)creator;
    return 1;
}

/* 00402275 */
static FILE *open_file(char *name, char *mode, int buffered)
{
    FILE *fp;

    fp = fopen(name, mode);
    if (fp == NULL)
        return NULL;
    if (buffered) {
        if (strcmp(mode, "rb") == 0)
            setvbuf(fp, inbuf, _IOFBF, insize);
        else if (strcmp(mode, "wb") == 0)
            setvbuf(fp, outbuf, _IOFBF, outsize);
    }
    if (strcmp(mode, "wb") == 0)
        set_file_type(name, "COFF", "MPS ");
    return fp;
}

/* size of a file; replaces _stat() */
static long file_size(char *name)
{
    FILE *fp;
    long n;

    fp = fopen(name, "rb");
    if (fp == NULL)
        return -1L;
    if (fseek(fp, 0L, SEEK_END) != 0)
        n = -1L;
    else
        n = ftell(fp);
    fclose(fp);
    return n;
}

/* 0040233e - member header for a module file; lower-cases the base name
 * of name in place and cuts it at ';' (VMS version) */
static char *make_header(char *name, char *buf)
{
    long size, t;
    char *base, *p;

    size = file_size(name);
    if (size < 0)
        fatal("cannot stat module %s", name);
    base = strlower(basename_(name));
    p = strrchr(base, ';');
    if (p != NULL)
        *p = '\0';
    t = now();
    sprintf(buf, "%s %s %ld %ld", magic, base, size, t);
    return buf;
}

/* 004023e3 - read a member header line; NULL at end of library */
static char *read_header(FILE *fp, char *buf)
{
    int c, c2;
    char *p;

    clearerr(fp);
    p = buf;
    for (;;) {
        c = getc(fp);
        if (c == EOF || p - buf >= 4)
            break;
        *p++ = (char)c;
    }
    if (feof(fp))
        return NULL;
    *p++ = (char)c;
    *p = '\0';
    if (strncmp(buf, magic, 4) == 0)
        oldfmt = 0;
    else if (strncmp(buf, oldmagic, 3) == 0)
        oldfmt = 1;
    else
        fatal0("improper module header format");
    for (;;) {
        c = getc(fp);
        if (c == EOF || c == '\r' || c == '\n')
            break;
        if (p < buf + LINESZ - 1)
            *p++ = (char)c;
    }
    *p = '\0';
    if (feof(fp))
        return NULL;
    if (ferror(fp))
        fatal0("cannot read module header");
    if (c == '\r') {
        c2 = getc(fp);
        if (c2 != EOF && c2 != '\n')
            ungetc(c2, fp);
    }
    return buf;
}

/* 0040260a */
static void write_header(FILE *fp, char *s)
{
    for (; *s != '\0'; s++)
        if (putc(*s, fp) == EOF)
            fatal0("cannot write header to library file");
    if (putc('\r', fp) == EOF)
        fatal0("cannot write header to library file");
    if (putc('\n', fp) == EOF)
        fatal0("cannot write header to library file");
}

/* 00402762 */
static void list_module(char *line)
{
    char name[LINESZ];
    long size, t;
    time_t tt;
    struct tm *tm;

    name[0] = '\0';
    size = 0;
    t = 0;
    sscanf(line, "%*s %s %ld %ld", name, &size, &t);
    tt = (time_t)t;
    tm = localtime(&tt);
    if (tm == NULL)                     /* MSVC: NULL for t < 0 */
        onsig(SIGSEGV);
    fprintf(stdout, "%-*s %10ld    %02d/%02d/%02d    %02d:%02d:%02d\n", 15,
            name, size, tm->tm_mon + 1, tm->tm_mday, tm->tm_year,
            tm->tm_hour, tm->tm_min, tm->tm_sec);
}

/* 004027e9 - index + 1 of the module named name, 1 if none were named */
static int find_module(char *name)
{
    char base[LINESZ];
    int i, idx;

    idx = 0;
    if (nmods <= 0)
        return 1;
    for (i = 0; idx == 0 && i < nmods; i++) {
        strcpy(base, basename_(mods[i]));
        if (strcmp(name, base) == 0) {
            if (i < MAXMODS)
                found[i] = 1;
            idx = i + 1;
        }
    }
    return idx;
}

/* 004028b4 */
static void report_missing(void)
{
    int i;

    for (i = 0; i < nmods; i++)
        if (i >= MAXMODS || !found[i])
            error("%s not in library", mods[i]);
}

/* 00402903 - append ext if the base name has no '.'; upper case unless
 * the name contains a lower case letter */
static void default_ext(char *name, char *ext)
{
    int lower;
    char *base, *end, *p;
    char e[8];

    lower = 0;
    (void)strlen(ext);
    base = basename_(name);
    end = name + strlen(name);
    p = strrchr(name, '.');
    if (p != NULL && p >= base)
        return;
    strncpy(e, ext, 5);
    for (p = base; *p != '\0'; p++)
        if (islower((unsigned char)*p)) {
            lower = 1;
            break;
        }
    if (!lower)
        for (p = e; *p != '\0'; p++)
            if (islower((unsigned char)*p))
                *p = (char)toupper((unsigned char)*p);
    strcpy(end, e);
}

/* 00402a70 - part after the last '\' or ':' */
static char *basename_(char *path)
{
    long i;

    if (path == NULL)
        return NULL;
    for (i = (long)strlen(path);
         i >= 0 && path[i] != '\\' && path[i] != ':' && path[i] != '/'; i--)
        ;
    if (i >= 0)
        return path + i + 1;
    return path;
}

/* 00402ae7 */
static char *strlower(char *s)
{
    char *p;

    for (p = s; *p != '\0'; p++)
        if (isupper((unsigned char)*p))
            *p = (char)tolower((unsigned char)*p);
    return s;
}

/* 00402b62 */
static void onsig(int sig)
{
    if (sig == SIGINT) {
        interrupted = 1;
        fatal0("interrupted");
    } else {
        if (sig == SIGSEGV)
            fprintf(errfp,
                "%s: fatal segmentation or protection fault; contact your tools vendor\n",
                progname);
        exit(1);
    }
}

/* 00402bbc - parse an interactive command line, return the command */
static int parse_cmd(char *line)
{
    char word[LINESZ];
    char *s, *p, c;
    int code;
    struct node {
        char *name;
        struct node *next;
    } head, *tail, *n, *next;
    char **v;

    for (s = line; *s != '\0'; s++)
        if (!isspace((unsigned char)*s))
            break;
    if (*s == '\0')
        return 0;
    p = word;
    for (; *s != '\0'; s++) {
        if (isspace((unsigned char)*s))
            break;
        *p++ = isupper((unsigned char)*s) ? (char)tolower((unsigned char)*s) : *s;
    }
    *p = '\0';
    code = lookup_cmd(word);
    if (code == 0)
        return 0;
    for (; *s != '\0'; s++)
        if (!isspace((unsigned char)*s))
            break;
    if (*s == '\0') {
        if (code < C_QUIT || code > C_VERSION) {
            error0("command requires library name");
            code = 0;
        }
        return code;
    }
    p = libname;
    for (; *s != '\0'; s++) {
        if (isspace((unsigned char)*s))
            break;
        *p++ = *s;
    }
    *p = '\0';
    default_ext(libname, defext);
    p = basename_(libname);
    if (p != NULL && p != libname) {
        c = *p;
        *p = '\0';
        strcpy(libdir, libname);
        *p = c;
    }
    head.next = NULL;
    tail = &head;
    nmods = 0;
    for (;;) {
        for (; *s != '\0'; s++)
            if (!isspace((unsigned char)*s))
                break;
        if (*s == '\0')
            break;
        p = word;
        for (; *s != '\0'; s++) {
            if (isspace((unsigned char)*s))
                break;
            *p++ = *s;
        }
        *p = '\0';
        n = (struct node *)xmalloc(sizeof(struct node));
        if (n == NULL)
            fatal0("cannot allocate module structure");
        p = xmalloc(strlen(word) + 1);
        if (p == NULL)
            fatal0("cannot allocate module structure");
        strcpy(p, word);
        n->name = p;
        tail->next = n;
        tail = n;
        n->next = NULL;
        nmods++;
    }
    if (nmods == 0) {
        mods = NULL;
    } else {
        mods = (char **)xmalloc((size_t)nmods * sizeof(char *));
        if (mods == NULL)
            fatal0("cannot allocate module vector");
        v = mods;
        for (n = head.next; n != NULL; n = next) {
            *v++ = strlower(n->name);
            next = n->next;
            free(n);
        }
    }
    return code;
}

/* 004031c3 */
static int lookup_cmd(char *word)
{
    size_t len;
    int i;

    len = strlen(word);
    for (i = 0;; i++) {
        if (i >= ncmds) {
            error("invalid command %s", word);
            return 0;
        }
        if (strncmp(word, cmds[i].name, len) == 0)
            break;
    }
    if ((long)cmds[i].minlen <= (long)len)
        return cmds[i].code;
    error("ambiguous command %s", word);
    return 0;
}

/* 00403263 - append the names in the -f command file to argv */
static int cmdfile_args(int argc, char ***argvp)
{
    struct arg *first, *last, *a, *next;
    char **v;
    int n, i;

    first = (struct arg *)xmalloc(sizeof(struct arg));
    if (first == NULL)
        fatal0("cannot save command file arguments");
    first->s = (*argvp)[0];
    first->next = NULL;
    n = 1;
    last = first;
    for (i = 1; i < argc; i++) {
        a = (struct arg *)xmalloc(sizeof(struct arg));
        if (a == NULL)
            fatal0("cannot save command file arguments");
        a->s = (*argvp)[i];
        a->next = NULL;
        last->next = a;
        last = a;
        n++;
    }
    if (tmpname[0] != '\0')
        n += read_cmdfile(tmpname, &last);
    v = (char **)xmalloc(((size_t)n + 1) * sizeof(char *));
    if (v == NULL)
        fatal0("cannot allocate argument vector");
    a = first;
    for (i = 0; i < n; i++) {
        v[i] = a->s;
        next = a->next;
        free(a);
        a = next;
    }
    v[i] = NULL;
    *argvp = v;
    return n;
}

/* 004033d4 - read white space separated names; ';' starts a comment */
static int read_cmdfile(char *name, struct arg **tail)
{
    FILE *fp;
    struct arg *a;
    int count, c, len;
    char word[LINESZ];
    char *p;

    count = 0;
    fp = fopen(name, "r");
    if (fp == NULL)
        fatal("cannot open command file", name);
    while (!feof(fp)) {
        do {
            c = getc(fp);
            if (c == EOF)
                break;
        } while (!isprint(c) || c == ' ');
        if (feof(fp))
            break;
        if (c == ';') {
            do
                c = getc(fp);
            while (c != EOF && c != '\n');
            continue;
        }
        word[0] = (char)c;
        p = word + 1;
        len = 1;
        for (;;) {
            c = getc(fp);
            if (c == EOF || !isprint(c) || c == ' ')
                break;
            if (p < word + LINESZ - 1) {
                *p++ = (char)c;
                len++;
            }
        }
        *p = '\0';
        if (word[0] != '\0') {
            a = (struct arg *)xmalloc(sizeof(struct arg));
            if (a == NULL)
                fatal0("cannot save command file arguments");
            a->s = xmalloc((size_t)len + 1);
            if (a->s == NULL)
                fatal0("cannot save command file arguments");
            strcpy(a->s, word);
            a->next = NULL;
            (*tail)->next = a;
            *tail = a;
            count++;
        }
        word[0] = '\0';
    }
    fclose(fp);
    return count;
}

/* 00403777 - is option letter c (any case) anywhere in a '-' argument? */
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

/* 00403853 - index of the first argument "-c..." (any case) */
static int findopt_idx(int c, int argc, char **argv)
{
    int i;
    char ch;

    i = 1;
    for (;;) {
        argv++;
        if (--argc < 1)
            return 0;
        if (**argv == '-') {
            ch = (*argv)[1];
            if (isupper((unsigned char)ch))
                ch = (char)tolower((unsigned char)ch);
            if (ch == c)
                return i;
        }
        i++;
    }
}

/* 0040391d - -ea/-ew <file> */
static void set_errfile(char **argv, int idx)
{
    char mode[4];
    char *name;

    mode[0] = argv[idx][2];
    mode[1] = '\0';
    if (isupper((unsigned char)mode[0]))
        mode[0] = (char)tolower((unsigned char)mode[0]);
    if (mode[0] != 'a' && mode[0] != 'w')
        fatal0("Illegal command line -e option");
    if (argv[idx][3] != '\0')
        fatal0("Invalid syntax for command line -e option");
    name = argv[idx + 1];
    if (name == NULL)                   /* original dereferences it */
        onsig(SIGSEGV);
    if (*name == '-')
        fatal0("Missing argument for command line -e option");
    if (errfp != NULL && errfp != stderr)
        fclose(errfp);
    errfp = fopen(name, mode);
    if (errfp == NULL) {
        errfp = stderr;
        fatal0("Cannot open error file");
    }
}

/* 00403a3d - getopt; "x:" one argument, "x::" two, "x?" optional */
static int getopt_(int argc, char **argv, char *opts)
{
    char c;
    char *p;

    if (argc == 0 && argv == NULL && opts == NULL) {
        optind_ = 0;
        optnext = NULL;
        return -1;
    }
    optarg_ = NULL;
    optarg2 = NULL;
    if (optnext == NULL || *optnext == '\0') {
        if (optind_ == 0)
            optind_++;
        if (optind_ >= argc || argv[optind_][0] != '-' || argv[optind_][1] == '\0') {
            optarg_ = NULL;
            optarg2 = NULL;
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
    if (p == NULL || c == ':' || c == '?') {
        fprintf(errfp, "%s: unknown option -%c\n", argv[0], (int)c);
        return '?';
    }
    if (p[1] == ':') {
        if (*optnext == '\0') {
            if (optind_ >= argc) {
                fprintf(errfp, "%s: -%c argument missing\n", argv[0], (int)c);
                return '?';
            }
            optarg_ = argv[optind_++];
        } else {
            optarg_ = optnext;
            optnext = NULL;
        }
        if (p[2] == ':') {
            if (optind_ >= argc) {
                fprintf(errfp, "%s: -%c argument missing\n", argv[0], (int)c);
                return '?';
            }
            optarg2 = argv[optind_++];
        }
    } else if (p[1] == '?') {
        if (*optnext == '\0') {
            if (optind_ < argc) {
                if (argv[optind_][0] == '-') {
                    if (argv[optind_][1] == '\0')
                        optarg_ = argv[optind_++];
                } else if (optind_ + 1 < argc && argv[optind_ + 1][0] == '-') {
                    optarg_ = argv[optind_++];
                }
            }
        } else {
            optarg_ = optnext;
            optnext = NULL;
        }
    }
    return (int)c;
}

/* _mktemp() replacement: the XXXXXX become a letter and five digits
 * (MSVC: the process id); the letter is advanced while the name exists */
static char *mktemp_(char *templ)
{
    char *x;
    unsigned long num;
    int i;
    FILE *fp;

    x = templ + strlen(templ);
    for (i = 0; i < 6; i++)
        if (x <= templ || x[-1] != 'X')
            return NULL;
        else
            x--;
    num = (unsigned long)time(NULL) % 100000UL;
    for (i = 5; i >= 1; i--) {
        x[i] = (char)('0' + (int)(num % 10));
        num /= 10;
    }
    for (x[0] = 'a'; x[0] <= 'z'; x[0]++) {
        fp = fopen(templ, "rb");
        if (fp == NULL)
            return templ;
        fclose(fp);
    }
    return NULL;
}

/* 00403d88 - temporary file name in the library's directory */
static char *make_tmpname(char *buf)
{
    char *p;

    strcpy(tmptempl, "lbXXXXXX");
    strcpy(buf, tmpdir);
    for (p = buf; *p != '\0'; p++)
        ;
    if (p > buf)
        p--;
    if (*p != '\0' && *p != ':' && *p != '\\' && *p != '/')
        *++p = '\\';
    if (p > buf)
        *++p = '\0';
    if (mktemp_(strcat(buf, tmptempl)) == NULL)
        fatal0("cannot create temporary file name");
    return buf;
}

/* 00403e56 */
static void usage(void)
{
    fprintf(errfp, "Usage:  %s -command library [files...]\n", progname);
    fprintf(errfp, "where -command is one of the following:\n");
    fprintf(errfp, "  -a            add named modules to library\n");
    fprintf(errfp, "  -c            create library with named modules\n");
    fprintf(errfp, "  -d            delete named modules from library\n");
    fprintf(errfp, "  -ea <errfil>  append to error file\n");
    fprintf(errfp, "  -ew <errfil>  write to error file\n");
    fprintf(errfp, "  -f  <cmdfil>  get module names from file\n");
    fprintf(errfp, "  -l            list library module info\n");
    fprintf(errfp, "  -q            do not display signon banner\n");
    fprintf(errfp, "  -r            replace named modules in library\n");
    fprintf(errfp, "  -u            update named modules or add at end\n");
    fprintf(errfp, "  -v            display librarian version\n");
    fprintf(errfp, "  -x            extract named modules from library\n");
    exit(1);
}

/* 00403f7f */
static void signon(void)
{
    if (!quiet)
        fprintf(errfp, "%s  Version %s\n%s\n", "DSP Librarian", "6.3",
                "(C) Copyright Motorola, Inc. 1987-1996.  All rights reserved.");
}

/* 00403faf */
static void help(void)
{
    fprintf(stdout, "Usage: command library [files...]\n");
    fprintf(stdout, "where  command is one of the following:\n");
    fprintf(stdout, "    add     - add named modules to library\n");
    fprintf(stdout, "    create  - create library with named modules\n");
    fprintf(stdout, "    delete  - delete named modules from library\n");
    fprintf(stdout, "    extract - extract named modules from library\n");
    fprintf(stdout, "    help    - display this message\n");
    fprintf(stdout, "    list    - list library module info\n");
    fprintf(stdout, "    quit    - exit librarian\n");
    fprintf(stdout, "    replace - replace named modules in library\n");
    fprintf(stdout, "    update  - update named modules or add at end\n");
    fprintf(stdout, "    version - display librarian version\n");
}

/* 0040408c */
static char *xmalloc(size_t n)
{
    char *p;

    p = (char *)malloc(n);
    if (p == NULL)
        fatal0("out of memory - librarian aborted");
    return p;
}

/* 004040b9 */
static void error0(char *msg)
{
    errors++;
    if (!interact)
        fprintf(errfp, "%s: ", progname);
    fprintf(errfp, "%s\n", msg);
}

/* 00404107 */
static void error(char *fmt, char *arg)
{
    errors++;
    if (!interact)
        fprintf(errfp, "%s: ", progname);
    fprintf(errfp, fmt, arg);
    fprintf(errfp, "\n");
}

/* 00404167 */
static void fatal0(char *msg)
{
    cleanup();
    error0(msg);
    if (interact && !interrupted)
        longjmp(jmpbuf, -1);
    exit(1);
}

/* 004041a8 - the original does not clear the pointers (a later cleanup
 * fcloses them again, which MSVC tolerates); they are cleared here */
static void cleanup(void)
{
    if (libfp != NULL) {
        fclose(libfp);
        libfp = NULL;
    }
    if (modfp != NULL) {
        fclose(modfp);
        modfp = NULL;
    }
    if (tmpfp != NULL) {
        fclose(tmpfp);
        tmpfp = NULL;
    }
    /* also removes the -f command file when no temporary name was made */
    remove(tmpname);
}

/* 0040420a */
static void fatal(char *fmt, char *arg)
{
    cleanup();
    error(fmt, arg);
    if (interact && !interrupted)
        longjmp(jmpbuf, -1);
    exit(1);
}

/* 00401010 */
int main(int argc, char **argv)
{
    int noopts, c, idx;
    char *name, *p, save;

    (void)rcsid;
    errfp = stderr;
    noopts = 1;
    init_globals();
    signal(SIGINT, onsig);
    signal(SIGSEGV, onsig);
    name = basename_(argc > 0 ? argv[0] : NULL);
    if (name == NULL)
        name = "dsplib";
    p = strrchr(name, '.');
    if (p != NULL)
        *p = '\0';
    quiet = findopt('q', argc, argv) != NULL;
    idx = findopt_idx('e', argc, argv);
    if (idx != 0)
        set_errfile(argv, idx);
    progname = name;
    signon();
    tmpdir = libdir;
    if (copybuf == NULL) {
        for (copysize = BUFSZ; copysize >= MINBUF; copysize >>= 1)
            if ((copybuf = xmalloc(copysize)) != NULL)
                break;
        if (copysize < MINBUF)
            fatal0("cannot allocate copy buffer");
    }
    if (inbuf == NULL) {
        for (insize = BUFSZ; insize >= MINBUF; insize >>= 1)
            if ((inbuf = xmalloc(insize)) != NULL)
                break;
        if (insize < MINBUF)
            fatal0("cannot allocate input buffer");
    }
    if (outbuf == NULL) {
        for (outsize = BUFSZ; outsize >= MINBUF; outsize >>= 1)
            if ((outbuf = xmalloc(outsize)) != NULL)
                break;
        if (outsize < MINBUF)
            fatal0("cannot allocate output buffer");
    }
    /* (the original's Macintosh mode flag 00413694 is always 0) */
    if (argc < 2)
        interactive();
    optarg_ = NULL;
    optarg2 = NULL;
    optind_ = 0;
    if (argc < 2)
        usage();
    while ((c = getopt_(argc, argv, "AaCcDdE::e::F:f:LlQqRrUuVvXx?")) != -1) {
        if (isupper(c))
            c = tolower(c);
        noopts = 0;
        switch (c) {
        case '?':
            usage();
            break;
        default:
            cmd = C_UPDATE;
            noopts = 1;
            break;
        case 'a':
            cmd = C_ADD;
            break;
        case 'c':
            cmd = C_CREATE;
            break;
        case 'd':
            cmd = C_DELETE;
            break;
        case 'e':
            break;
        case 'f':
            strcpy(tmpname, optarg_);
            if (tmpname[0] != '\0')
                argc = cmdfile_args(argc, &argv);
            break;
        case 'l':
            cmd = C_LIST;
            break;
        case 'q':
            quiet = 1;
            break;
        case 'r':
            cmd = C_REPLACE;
            break;
        case 'u':
            cmd = C_UPDATE;
            break;
        case 'v':
            exit(0);
            break;
        case 'x':
            cmd = C_EXTRACT;
            break;
        }
    }
    if (optind_ >= argc)
        usage();
    strcpy(libname, argv[optind_++]);
    default_ext(libname, defext);
    p = basename_(libname);
    if (p != NULL && p != libname) {
        save = *p;
        *p = '\0';
        strcpy(libdir, libname);
        *p = save;
    }
    nmods = argc - optind_;
    mods = argv + optind_;
    check_dups();
    if (noopts && nmods <= 0)
        cmd = C_LIST;
    switch (cmd) {
    case C_ADD:
    case C_CREATE:
    case C_REPLACE:
    case C_UPDATE:
        update_lib();
        break;
    case C_DELETE:
        delete_lib();
        break;
    case C_EXTRACT:
        extract_lib();
        break;
    case C_LIST:
        list_lib();
        break;
    default:
        update_lib();
    }
    exit(0);
    return 0;
}
