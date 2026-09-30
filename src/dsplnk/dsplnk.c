/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), dsplnk.c
 * "$Id: dsplnk.c,v 1.46 1999/03/19 20:11:22 jay Exp $"
 * Reconstructed from DSPLNK.EXE 00401a20-00404c44.
 *
 * Main program: command line (DSPLNKOPT environment variable, -f command
 * files, the option parser dsp_getopt), the two link passes, the final
 * clean-up (finish_link), signals, target selection and default names.
 */
#include "dsplnk.h"

/* getopt state (461da8 / 461dac / 461db0 / 461130) */
static int optind_;
static char *optarg_;
static char *optarg2_;                  /* written, never read */
static char *optnext;

/* dead Mac/MPW "no argv" mode (4611f8 / 46c114): never set */
static char no_argv_mode_saved;
static long no_argv_list;

/* write-only copies of target table fields (461f68 461f94 461fa8..461fb0) */
static long tgt_dword_hexdig;
static long tgt_unk28;
static long tgt_unk30;
static long tgt_unk34;
static long tgt_unk38;

void lnk_usage(void);
void strip_ext_copy(char *src, char *dst);
void parse_cmdline_options(void);
char *find_opt_arg(int c, int argc, char **argv);
int find_opt_index(int c, int argc, char **argv);
void open_error_file_opt(char **argv, int idx);
void init_link_state_pass1(void);
void init_link_state_pass2(void);
char *default_base_name(int argc, char **argv);
void open_default_object_file(void);
int expand_dsplnkopt(int argc, char ***argvp);
int tokenize_env_options(char *s, STRNODE **tailp);
int read_command_file(char *name, STRNODE **tailp);
int dsp_getopt(int argc, char **argv, char *optstr);
int add_library_path(char *path);
void ensure_trailing_backslash(void);
void init_float_names(void);
long get_date_time_strings(char *date, char *time);

/* MSVC: "isupper(c) ? tolower(c) : c" */
static int lower(int c)
{
    c &= 0xff;
    return isupper(c) ? tolower(c) : c;
}

/* _isctype(c, 0x157) && c != ' ' in the C locale: a printable non-blank */
#define TOKCH(c)  ((c) > ' ' && (c) < 0x7f)

/* 00401a20 */
int main(int argc, char **argv)
{
    char *s, *p;
    char elfname[NAMEBUF_SIZE + 16];

    msg_fp = stderr;
    signal(SIGINT, lnk_signal_handler);
    signal(SIGSEGV, lnk_signal_handler);
    signal(SIGFPE, lnk_signal_handler);
    s = base_name(argv[0]);
    /* deviation: '/' also ends the directory part of the program name */
    if ((p = strrchr(s, '/')) != NULL)
        s = p + 1;
    if ((p = strrchr(s, '.')) != NULL)
        *p = '\0';
    if (getenv(env_name) != NULL || find_opt_arg('f', argc, argv) != NULL)
        argc = expand_dsplnkopt(argc, &argv);
    opt_c = find_opt_arg('c', argc, argv) != NULL;
    opt_q = find_opt_arg('q', argc, argv) != NULL;
    {
        int idx = find_opt_index('e', argc, argv);
        if (idx != 0)
            open_error_file_opt(argv, idx);
    }
    progname = s;
    sscanf(lnk_version, "%ld.%ld.%ld", &lnk_major, &lnk_minor, &lnk_rev);
    if (!opt_c && !opt_q)
        fprintf(msg_fp, "DSP %s  Version %s\n%s\n", lnk_name, lnk_version,
                lnk_copyright);
    if (!no_argv_mode && argc < 2)
        lnk_usage();
    link_time = get_date_time_strings(date_str, time_str);
    err_fp = stdout;
    base_fname = default_base_name(argc, argv);
    init_link_state_pass1();
    cur_argv = argv;
    cur_argc = argc;
    if (!no_argv_mode) {
        parse_cmdline_options();
        if (cur_argc == 0)
            lnk_cmdline_fatal1("Missing object filename");
    }
    if (opt_v)
        fprintf(msg_fp, "%s: Beginning pass 1\n", progname);
    process_input_files();
    fixup_relocate();
    init_link_state_pass2();
    cur_argv = argv;
    cur_argc = argc;
    if (!no_argv_mode)
        parse_cmdline_options();
    if (obj_fp == NULL)
        open_default_object_file();
    if (opt_v)
        fprintf(msg_fp, "%s: Beginning pass 2\n", progname);
    process_input_files();
    finish_link(0);
    if (target_magic == M_SC100 && !opt_i && opt_c && obj_name != NULL) {
        if (strcmp(obj_name, "-") == 0) {
            lnk_warning1("Object file redirected to stdout, no debug information will be created. Use -b<filename>.");
        } else {
            strip_ext_copy(obj_name, elfname);
            strcat(elfname, ".elf");
            if (opt_v)
                fprintf(msg_fp, "%s: Creating ELF debug information file: %s\n",
                        progname, elfname);
            if (coff_to_elf(obj_name, elfname) != 0)
                lnk_warning1("Failed to create debug information file");
        }
    }
    if (opt_wex)
        error_count += warning_count;
    if (opt_s)
        fprintf(stdout, "%s: errors: %ld warnings: %ld\n", progname,
                error_count, warning_count);
    exit((int)error_count);
    return (int)error_count;
}

/* 00401dfe */
void lnk_usage(void)
{
    if (opt_c || opt_q)
        fprintf(msg_fp, "DSP %s  Version %s\n%s\n", lnk_name, lnk_version,
                lnk_copyright);
    fprintf(msg_fp, "Usage:  %s [-a] [-b[<objfil>]] [-e<a|w> <errfil>] [-f<argfil>] [-g] [-i] [-l<library>] [-m[<mapfil>]] [-n] [-o<mem>[<ctr>][<map>]:<origin>] [-p<lpath>] [-q] [-r[<memfil>]] [-u<symbol>] [-v] [-x<opt>[,<opt>...]] [-z] <lnkfil>...\n", progname);
    fprintf(msg_fp, "where:\n");
    fprintf(msg_fp, "  -a  auto-align buffers               -n  ignore symbol case\n");
    fprintf(msg_fp, "  -b  object file                      -o  memory origin\n");
    fprintf(msg_fp, "      <objfil>  object file name           <mem>  memory space\n");
    fprintf(msg_fp, "  -ea append to error file                 <ctr>  location counter\n");
    fprintf(msg_fp, "      <errfil>  error file name            <map>  memory mapping\n");
    fprintf(msg_fp, "  -ew write to error file                  <origin>  address\n");
    fprintf(msg_fp, "      <errfil>  error file name        -p  library path\n");
    fprintf(msg_fp, "  -f  command file                         <lpath>  library path name\n");
    fprintf(msg_fp, "      <argfil>  command file name      -q  suppress banner\n");
    fprintf(msg_fp, "  -g  debug mode                       -r  memory control file\n");
    fprintf(msg_fp, "  -i  incremental link                     <memfil>  control file name\n");
    fprintf(msg_fp, "  -l  library file                     -u  define symbol\n");
    fprintf(msg_fp, "      <library>  library file name         <symbol>  symbol name\n");
    fprintf(msg_fp, "  -m  map file                         -v  verbose mode\n");
    fprintf(msg_fp, "      <mapfil>  map file name          -x  linker option\n");
    fprintf(msg_fp, "                                           <opt>  linker option argument\n");
    fprintf(msg_fp, "  <lnkfil>  link input file name(s)    -z  strip absolute object\n");
    fprintf(msg_fp, "%s command environment variable:  %s\n", lnk_name, env_name);
    exit(-1);
}

/* 00401fe0: copy src to dst without the extension (last '.') */
void strip_ext_copy(char *src, char *dst)
{
    char *p;

    strcpy(dst, src);
    if ((p = strrchr(dst, '.')) != NULL)
        *p = '\0';
}

/* 00402017: one pass over the options of cur_argc/cur_argv; leaves
   cur_argc/cur_argv at the first input file. */
void parse_cmdline_options(void)
{
    int c, done, nidx, dflt;
    char *objcopy, *mapcopy, *dot;
    char **ap;
    MEMSPEC spec;
    MEMREG *mr;
    int vl;

    dot = NULL;
    done = 0;
    objcopy = NULL;
    mapcopy = NULL;
    dsp_getopt(0, NULL, NULL);
    nidx = optind_;
    for (;;) {
        optind_ = nidx;
        if (done)
            break;
        c = dsp_getopt((int)cur_argc, cur_argv, optstring);
        if (c == -1)
            break;
        nidx = optind_;
        switch (lower(c)) {
        case 'a':
            if (!opt_i)
                opt_a = 1;
            break;
        case 'b':
            if (optarg_ == NULL && opt_i)
                lnk_cmdline_fatal1("Default object file not allowed in incremental link");
            if (pass == 1)
                break;
            if (obj_fp != NULL) {
                lnk_cmdline_warn1("Duplicate object file specified - ignored");
                break;
            }
            dflt = optarg_ == NULL;
            if (dflt)
                optarg_ = base_fname;
            strcpy(namebuf, optarg_);
            if (dflt)
                set_default_ext(".cld");
            objcopy = (char *)xmalloc((unsigned long)strlen(namebuf) + 1);
            strcpy(objcopy, namebuf);
            obj_name = objcopy;
            if (strcmp(namebuf, "-") == 0) {
                obj_fp = stdout;
            } else {
                obj_fp = fopen(namebuf, "wb");
                if (obj_fp == NULL)
                    lnk_cmdline_fatal2("Cannot open object file", namebuf);
            }
            set_file_type(namebuf, "COFF", "MPS ");
            break;
        case 'c':
        case 'e':
        case 'f':
        case 'q':
            break;
        case 'g':
            opt_g = 1;
            break;
        case 'i':
            opt_i = 1;
            break;
        case 'l':
            if (pass != 2) {
                done = 1;
                nidx = optind_ - 1;
                if (cur_argv[optind_ - 1][0] != '-')
                    nidx = optind_ - 2;
            }
            break;
        case 'm':
            if (pass == 1)
                break;
            if (map_fp != NULL) {
                lnk_cmdline_warn1("Duplicate map file specified - ignored");
                break;
            }
            dflt = optarg_ == NULL;
            if (dflt)
                optarg_ = base_fname;
            strcpy(namebuf, optarg_);
            if (dflt)
                set_default_ext(".map");
            if (opt_t)
                str_lower(namebuf);
            strcpy(title_name, namebuf);
            mapcopy = (char *)xmalloc((unsigned long)strlen(namebuf) + 1);
            strcpy(mapcopy, namebuf);
            if (strcmp(namebuf, "-") == 0) {
                map_fp = stdout;
            } else {
                map_fp = fopen(namebuf, "w");
                if (map_fp == NULL)
                    lnk_cmdline_fatal2("Cannot open map file", namebuf);
            }
            set_file_type(namebuf, "TEXT", "MPS ");
            break;
        case 'n':
            opt_n = 1;
            break;
        case 'o':
            input_cursor = optarg_;
            if (get_mem_spec(&spec)) {
                if (*input_cursor == '$')
                    input_cursor++;
                mr = memreg_get(region_head, &spec, 0);
                sscanf(input_cursor, "%lx", &mr->base);
                mr->flags2 |= MR2_BASE;
            }
            break;
        case 'p':
            if (pass != 2) {
                suppress_errors = 1;
                add_library_path(optarg_);
                suppress_errors = 0;
            }
            break;
        case 'r':
            if (pass == 2)
                break;
            if (ctl_fp != NULL) {
                lnk_cmdline_warn1("Duplicate memory control file specified - ignored");
                break;
            }
            dflt = optarg_ == NULL;
            if (dflt)
                optarg_ = base_fname;
            strcpy(namebuf, optarg_);
            if (dflt) {
                set_default_ext(".ctl");
                dot = strrchr(namebuf, '.');
            }
            strcpy(title_name, namebuf);
            ctl_fp = fopen(namebuf, "r");
            if (ctl_fp == NULL && dflt && dot != NULL) {
                *dot = '\0';
                set_default_ext(".mem");
                ctl_fp = fopen(namebuf, "r");
            }
            if (ctl_fp == NULL)
                lnk_cmdline_fatal2("Cannot open memory control file", namebuf);
            break;
        case 's':
            opt_s = 1;
            break;
        case 't':
            opt_t = 1;
            break;
        case 'u':
            if (pass != 2)
                xref_add(optarg_, 1, 0);
            break;
        case 'v':
            opt_v = 1;
            if (optarg_ != NULL) {
                vl = (int)verbose_level;
                if (sscanf(optarg_, "%d", &vl) == 1)   /* "%d" into a long (MSVC) */
                    verbose_level = vl;
            }
            break;
        case 'x':
            suppress_errors = 1;
            if (set_x_options(optarg_) == 0)
                lnk_cmdline_fatal2("Illegal command line -X option argument", optarg_);
            suppress_errors = 0;
            break;
        case 'z':
            opt_z = 1;
            break;
        default:
            lnk_cmdline_fatal1("Illegal command line option");
            break;
        }
    }
    cur_argc -= optind_;
    cur_argv += optind_;
    if (opt_g && opt_z) {
        lnk_cmdline_warn1("Options for both debug and strip specified - strip ignored");
        opt_z = 0;
    }
    if (opt_i && opt_z) {
        lnk_cmdline_warn1("Strip not valid with incremental link - ignored");
        opt_z = 0;
    }
    if (opt_i && opt_a) {
        lnk_cmdline_warn1("Align not valid with incremental link - ignored");
        opt_a = 0;
    }
    if (objcopy != NULL || mapcopy != NULL) {
        for (ap = cur_argv; *ap != NULL; ap++) {
            if (objcopy != NULL && strcmp(objcopy, *ap) == 0)
                lnk_cmdline_fatal2("Object file name same as executable file name", objcopy);
            if (mapcopy != NULL && strcmp(mapcopy, *ap) == 0)
                lnk_cmdline_fatal2("Object file name same as map file name", mapcopy);
        }
        if (mapcopy != NULL)
            xfree(mapcopy);
    }
}

/* 00402871: only used by the dead no-argv mode */
long peek_long(long *p)
{
    return *p;
}

/* 0040287b: first argv[i] (i >= 1) of the form "-X" with lower(X) == c */
char *find_opt_arg(int c, int argc, char **argv)
{
    if (no_argv_mode)
        return NULL;
    for (;;) {
        do {
            argv++;
            if (--argc < 1)
                return NULL;
        } while ((*argv)[0] != '-');
        if (lower((*argv)[1]) == c)
            return *argv;
    }
}

/* 0040294c: same, returning the index (0: none) */
int find_opt_index(int c, int argc, char **argv)
{
    int i;

    i = 1;
    for (;;) {
        argv++;
        if (--argc < 1)
            return 0;
        if ((*argv)[0] == '-' && lower((*argv)[1]) == c)
            return i;
        i++;
    }
}

/* 00402a24: -ea / -ew <file> */
void open_error_file_opt(char **argv, int idx)
{
    char mode[4];
    char *name;

    mode[0] = argv[idx][2];
    mode[1] = '\0';
    mode[0] = (char)lower(mode[0]);
    if (mode[0] != 'a' && mode[0] != 'w')
        lnk_cmdline_fatal1("Illegal command line -E option");
    if (argv[idx][3] != '\0')
        lnk_cmdline_fatal1("Invalid syntax for command line -E option");
    name = argv[idx + 1];
    if (name == NULL)                   /* the original dereferences NULL */
        lnk_signal_handler(SIGSEGV);
    if (*name == '-')
        lnk_cmdline_fatal1("Missing argument for command line -E option");
    if (msg_fp != NULL && msg_fp != stderr)
        fclose(msg_fp);
    msg_fp = fopen(name, mode);
    if (msg_fp == NULL) {
        msg_fp = stderr;
        lnk_cmdline_fatal1("Cannot open error file");
    }
}

/* 00402b44 */
void init_link_state_pass1(void)
{
    cur_infile = infile_head;
    warning_count = 0;
    error_count = 0;
    cur_scnum = -1;
    cur_symidx = 0;
    ctl_lineno = 0;
    obj_nscns = opt_i ? 0 : 2;
    ovl_seq = 0;
    num_overlays = 0;
    buf_seq = 0;
    num_buffers = 0;
    num_secs = 0;
    sec_num_seed = 0;
    out_nsdi = 0;
    radix = 10;
    nested_secs = 1;
    opt_rsc = 1;
    opt_aec = 1;
    opt_abc = 1;
    opt_wex = 0;
    opt_isw = 0;
    opt_osp = 0;
    opt_csl = 0;
    opt_ff = 0;
    opt_svo = 0;
    opt_ro = 0;
    opt_ovlp = 0;
    opt_eso = 0;
    opt_asc = 0;
    opt_wvr = 1;
    obj_fext_cur = NULL;
    obj_nlnno_file = 0;
    region_head = region_get(default_region);
    cur_region = region_head;
    init_float_names();
    pass = 1;
}

/* 00402cd2 */
void init_link_state_pass2(void)
{
    no_argv_mode = no_argv_mode_saved;
    cur_infile = infile_head;
    cur_scnum = -1;
    cur_symidx = 0;
    ctl_lineno = 0;
    map_pageno = 1;
    cur_rsection = NULL;
    cur_section = NULL;
    load_spec.mspace = 0;
    run_spec.mspace = 0;
    ovl_seq = 0;
    num_overlays = 0;
    buf_seq = 0;
    num_buffers = 0;
    sec_num_seed = 0;
    out_nsdi = 0;
    radix = 10;
    nested_secs = 1;
    opt_rsc = 1;
    opt_aec = 1;
    opt_abc = 1;
    opt_wex = 0;
    opt_isw = 0;
    opt_osp = 0;
    opt_csl = 0;
    opt_ff = 0;
    opt_svo = 0;
    opt_ro = 0;
    opt_ovlp = 0;
    opt_eso = 0;
    opt_asc = 0;
    opt_wvr = 1;
    obj_fext_cur = obj_fext_head;
    obj_nlnno_file = 0;
    pass = 2;
}

/* 00402e52: start address, unresolved externals, object and map output,
   clean-up.  abort != 0 skips the writers (main passes 0). */
void finish_link(int abort)
{
    EXPR *e;

    abi_free_all();
    if (start_name == NULL) {
        if (opt_i)
            obj_lnkhdr.endstr = -1;
    } else {
        cur_infile = NULL;
        input_cursor = start_name;
        e = eval_int();
        if (e != NULL) {
            start_addr = expr_as_int32(e);
            start_mem = e->space;
        }
        if (opt_i)
            obj_lnkhdr.endstr = obj_add_string(start_name);
    }
    cur_infile = NULL;
    if (!opt_i && num_xrefs != 0) {
        error_count += num_xrefs;
        map_unresolved_stderr();
    }
    fixup_check_secsizes();
    if (obj_fp != NULL) {
        if (!abort)
            obj_write_file();
        if (obj_fp != stdout) {
            fclose(obj_fp);
            obj_fp = NULL;
        }
        if ((error_count != 0 || (opt_wex && warning_count != 0)) &&
            obj_name != NULL && !opt_svo) {
            remove(obj_name);
            xfree(obj_name);
            obj_name = NULL;
        }
    }
    free_section_xrefs();
    free_module_tables();
    if (opt_ovlp && !abort)
        map_check_overlap();
    if (map_fp != NULL) {
        if (!abort)
            map_write();
        if (map_fp != stdout) {
            fclose(map_fp);
            map_fp = NULL;
        }
    }
    free_sort_arrays();
    free_memmaps();
    free_sections();
    sym_free_all();
    xref_free_all();
    free_input_files();
    free_dup_globals_list();
}

/* 0040303c: SIGINT, SIGFPE, SIGSEGV */
void lnk_signal_handler(int sig)
{
    if (sig == SIGINT) {
        if (!opt_c)
            fprintf(msg_fp, "\n%s: Interrupted\n", progname);
        if (opt_wex)
            error_count += warning_count;
        exit(error_count == 0 ? -1 : (int)error_count);
    } else if (sig == SIGFPE) {
        signal(SIGFPE, lnk_signal_handler);
        if (in_eval) {
            lnk_error1("Arithmetic exception");
            longjmp(eval_jmpbuf, -1);
        }
        lnk_fatal1("Arithmetic exception");
    } else if (sig == SIGSEGV) {
        fprintf(msg_fp, "%s: Fatal segmentation or protection fault; contact your tools vendor\n",
                progname);
        if (opt_wex)
            error_count += warning_count;
        exit(error_count == 0 ? -1 : (int)error_count);
    }
}

/* 00403172: base name (no directory, no extension) of the first -l library
   or else of the first input file; runs dsp_getopt over all options first. */
char *default_base_name(int argc, char **argv)
{
    int c, lib, idx;
    char *p, *s, *dst, *dot;

    lib = 0;
    dsp_getopt(0, NULL, NULL);
    for (;;) {
        c = dsp_getopt(argc, argv, optstring);
        if (c == -1)
            break;
        if (lower(c) == 'l') {
            lib = 1;
            break;
        }
    }
    idx = lib ? optind_ - 1 : optind_;
    if (argc - idx < 1)
        lnk_cmdline_fatal1("Cannot open object file");
    p = lib ? argv[optind_ - 1] : argv[optind_];
    if (*p == '-')
        p += 2;
    s = base_name(p);
    dst = (char *)xmalloc((unsigned long)strlen(s) + 1);
    strcpy(dst, s);
    dot = strrchr(dst, '.');
    if (dot != NULL && dot != dst)
        *dot = '\0';
    return dst;
}

/* 004032e9: replace or append the extension of namebuf; returns where the
   extension was written, NULL if it already was ext */
char *set_default_ext(char *ext)
{
    char *base, *dot;
    size_t len;

    base = base_name(namebuf);
    len = strlen(namebuf);
    dot = strrchr(namebuf, '.');
    if (dot == NULL || dot < base)
        dot = namebuf + len;
    if (strcmp(dot, ext) == 0)
        return NULL;
    strcpy(dot, ext);
    return dot;
}

/* 00403385: pass 2 without -b: <base>.cld */
void open_default_object_file(void)
{
    if (opt_i)
        lnk_cmdline_fatal1("Default object file not allowed in incremental link");
    strcpy(namebuf, base_fname);
    set_default_ext(".cld");
    obj_name = (char *)xmalloc((unsigned long)strlen(namebuf) + 1);
    strcpy(obj_name, namebuf);
    obj_fp = fopen(namebuf, "wb");
    if (obj_fp == NULL)
        lnk_cmdline_fatal2("Cannot open object file", namebuf);
    set_file_type(namebuf, "COFF", "MPS ");
}

static STRNODE *new_strnode(char *str)
{
    STRNODE *n;

    n = (STRNODE *)xmalloc(sizeof(STRNODE));
    n->str = str;
    n->next = NULL;
    return n;
}

/* 0040343e: argv[0], the DSPLNKOPT tokens, then argv[1..] with -f command
   files expanded; *argvp gets the new (NULL-terminated) vector */
int expand_dsplnkopt(int argc, char ***argvp)
{
    STRNODE *head, *tail, *n, *next;
    char **nargv;
    char *p, *env, *copy;
    int count, i;

    head = new_strnode((*argvp)[0]);
    count = 1;
    tail = head;
    env = getenv(env_name);
    if (env != NULL) {
        /* the original tokenizes the environment string in place */
        copy = (char *)xmalloc((unsigned long)strlen(env) + 1);
        strcpy(copy, env);
        count += tokenize_env_options(copy, &tail);
        xfree(copy);
    }
    if (!no_argv_mode) {
        for (i = 1; i < argc; i++) {
            p = (*argvp)[i];
            if (p[0] == '-' && lower(p[1]) == 'f') {
                if (p[2] == '\0') {
                    i++;
                    if (i >= argc)
                        lnk_cmdline_fatal2("Missing command line option argument", "-F");
                    p = (*argvp)[i];
                    if (p == NULL || *p == '\0' || *p == '-')
                        lnk_cmdline_fatal2("Missing command line option argument", "-F");
                } else {
                    p += 2;
                }
                count += read_command_file(p, &tail);
            } else {
                n = new_strnode(p);
                tail->next = n;
                count++;
                tail = n;
            }
        }
    } else {
        count += read_command_file(namebuf, &tail);
    }
    nargv = (char **)xmalloc((unsigned long)count * sizeof(char *) + sizeof(char *));
    n = head;
    for (i = 0; i < count; i++) {
        nargv[i] = n->str;
        next = n->next;
        xfree(n);
        n = next;
    }
    nargv[i] = NULL;
    *argvp = nargv;
    return count;
}

static void append_token(char *tok, STRNODE **tailp)
{
    STRNODE *n;

    n = (STRNODE *)xmalloc(sizeof(STRNODE));
    n->str = (char *)xmalloc((unsigned long)strlen(tok) + 2);
    strcpy(n->str, tok);
    n->next = NULL;
    (*tailp)->next = n;
    *tailp = n;
}

/* 004036b4: split s (modified temporarily) into tokens; -f files expanded */
int tokenize_env_options(char *s, STRNODE **tailp)
{
    int count;
    char save;
    char *p, *tok, *arg;

    count = 0;
    p = s;
    while (*p != '\0') {
        while (*p != '\0' && !TOKCH((unsigned char)*p))
            p++;
        tok = p;
        while (*p != '\0' && TOKCH((unsigned char)*p))
            p++;
        save = *p;
        *p = '\0';
        if (tok[0] == '-' && lower(tok[1]) == 'f') {
            if (tok[2] == '\0') {
                *p = save;
                while (*p != '\0' && !TOKCH((unsigned char)*p))
                    p++;
                arg = p;
                while (*p != '\0' && TOKCH((unsigned char)*p))
                    p++;
                save = *p;
                *p = '\0';
                if (*arg == '\0' || *arg == '-')
                    lnk_cmdline_fatal2("Missing command line option argument", "-F");
                tok = arg;
            } else {
                tok += 2;
            }
            count += read_command_file(tok, tailp);
            *p = save;
            continue;
        }
        if (*tok != '\0') {
            append_token(tok, tailp);
            count++;
        }
        *p = save;
    }
    return count;
}

#define CMDTOK_SIZE 512

/* read one token starting with c into buf (original: no bounds check) */
static void read_cmd_token(FILE *fp, int c, char *buf)
{
    int n;

    n = 0;
    buf[n++] = (char)c;
    for (;;) {
        c = getc(fp);
        if (c == EOF || !TOKCH(c))
            break;
        if (n < CMDTOK_SIZE - 1)
            buf[n++] = (char)c;
    }
    buf[n] = '\0';
}

/* 004039e5: tokens of a command file; ';' starts a comment to the end of
   the line; nested -f */
int read_command_file(char *name, STRNODE **tailp)
{
    FILE *fp;
    int count, c;
    char buf[CMDTOK_SIZE];
    char *arg;

    count = 0;
    fp = fopen(name, "r");
    if (fp == NULL)
        lnk_cmdline_fatal2("Cannot open command file", name);
    for (;;) {
        if (feof(fp))
            break;
        do {
            c = getc(fp);
        } while (c != EOF && !TOKCH(c));
        if (feof(fp))
            break;
        if (c == ';') {
            do {
                c = getc(fp);
            } while (c != EOF && c != '\n');
            continue;
        }
        read_cmd_token(fp, c, buf);
        if (buf[0] == '-' && lower(buf[1]) == 'f') {
            if (buf[2] == '\0') {
                do {
                    c = getc(fp);
                } while (c != EOF && !TOKCH(c));
                if (feof(fp))
                    lnk_cmdline_fatal2("Missing command line option argument", "-F");
                if (c == ';') {
                    do {
                        c = getc(fp);
                    } while (c != EOF && c != '\n');
                    continue;
                }
                read_cmd_token(fp, c, buf);
                if (buf[0] == '\0' || buf[0] == '-')
                    lnk_cmdline_fatal2("Missing command line option argument", "-F");
                arg = buf;
            } else {
                arg = buf + 2;
            }
            count += read_command_file(arg, tailp);
            continue;
        }
        if (buf[0] != '\0') {
            append_token(buf, tailp);
            count++;
        }
    }
    fclose(fp);
    return count;
}

/* 004040eb: getopt.  "x:" argument required, "x::" plus a second argument
   (optarg2), "x?" optional argument: attached, or the next argv if it is
   exactly "-", or the next argv if it does not start with '-' while the one
   after it starts with '-' and is not -l.  (0, NULL, NULL) resets. */
int dsp_getopt(int argc, char **argv, char *optstr)
{
    char buf[8];
    char *p;
    int c;

    if (argc == 0 && argv == NULL && optstr == NULL) {
        optind_ = 0;
        optnext = NULL;
    }
    optarg_ = NULL;
    optarg2_ = NULL;
    if (optnext == NULL || *optnext == '\0') {
        if (optind_ == 0)
            optind_ = 1;
        if (optind_ >= argc || argv[optind_][0] != '-' || argv[optind_][1] == '\0') {
            optarg_ = NULL;
            optarg2_ = NULL;
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
    p = strchr(optstr, c);
    if (p == NULL || c == ':' || c == '?') {
        sprintf(buf, "-%c", c);
        lnk_cmdline_fatal2("Illegal command line option", buf);
    }
    p++;
    if (*p == ':') {
        if (*optnext == '\0') {
            if (optind_ < argc) {
                optarg_ = argv[optind_++];
            } else {
                sprintf(buf, "-%c", c);
                lnk_cmdline_fatal2("Missing command line option argument", buf);
            }
        } else {
            optarg_ = optnext;
            optnext = NULL;
        }
        p++;
        if (*p == ':') {
            if (optind_ < argc) {
                optarg2_ = argv[optind_++];
            } else {
                sprintf(buf, "-%c", c);
                lnk_cmdline_fatal2("Missing command line option argument", buf);
            }
        }
    } else if (*p == '?') {
        if (*optnext == '\0') {
            if (optind_ < argc) {
                if (argv[optind_][0] == '-') {
                    if (argv[optind_][1] == '\0')
                        optarg_ = argv[optind_++];
                } else if (optind_ + 1 < argc && argv[optind_ + 1][0] == '-') {
                    if (lower(argv[optind_ + 1][1]) != 'l')
                        optarg_ = argv[optind_++];
                }
            }
        } else {
            optarg_ = optnext;
            optnext = NULL;
        }
    }
    (void)optarg2_;
    return c;
}

/* 004044bd: -p: append path + '\\' to the library path list (pass 1) */
int add_library_path(char *path)
{
    STRNODE *n;

    if (pass != 2) {
        strcpy(namebuf, path);
        ensure_trailing_backslash();
        n = (STRNODE *)xmalloc(sizeof(STRNODE));
        n->str = (char *)xmalloc((unsigned long)strlen(namebuf) + 1);
        n->next = NULL;
        strcpy(n->str, namebuf);
        if (libpath_head == NULL)
            libpath_head = n;
        else
            libpath_tail->next = n;
        libpath_tail = n;
    }
    return 1;
}

/* 0040456e: namebuf += '\\' unless it ends in '\\' or ':' (deviation: or
   '/', so that Unix style paths keep working) */
void ensure_trailing_backslash(void)
{
    size_t len;
    char *p;

    len = strlen(namebuf);
    if (len > 0) {
        p = namebuf + len - 1;
        if (*p != '\\' && *p != ':' && *p != '/') {
            p = namebuf + len;
            *p = '\\';
        }
        p[1] = '\0';
    }
}

/* 004045d0: select the target by COFF magic */
void set_target_cpu(unsigned long magic)
{
    TARGET *t;
    MEMREG *mr;

    for (t = target_tab; t->name != NULL && magic != t->magic; t++)
        ;
    if (t->name == NULL)
        lnk_fatal1("Invalid object file for target processor");
    target_index = (long)(t - target_tab);
    cur_target = &target_tab[target_index];
    target_name = cur_target->name;
    target_magic = t->magic;
    word_bytes = t->word_bytes;
    word_hexdig = word_bytes << 1;
    dword_hexdig = word_bytes << 2;
    word_bits = word_bytes << 3;
    dword_bits = word_bytes << 4;
    fmt_dword = word_bytes << 1;
    word_mask = t->word_mask;
    sign_bit = t->sign_bit;
    tgt_unk24 = t->unk_24;
    tgt_unk28 = t->unk_28;
    addr_mask = t->addr_mask;
    ext_addr_mask = t->ext_addr_mask;
    io_base = t->io_base;
    io_base_neg = M32(~io_base + 1);
    io_short_max = M32((~io_base) * 2 + 1) & addr_mask;
    io_base2_neg = M32(~io_base2 + 1);
    io_short2_max = M32((~io_base2) * 2 + 1) & addr_mask;
    word_digits = t->word_digits;
    tgt_unk30 = t->unk_30;
    tgt_unk34 = t->unk_34;
    tgt_unk38 = t->unk_38;
    word_fmt = t->word_fmt;
    value_fmt = t->value_fmt;
    addr_fmt = t->addr_fmt;
    frac_max = M32(~sign_bit) & word_mask;
    frac_min = M32(~frac_max);
    fmt_word = word_bytes;
    tgt_dword_hexdig = word_hexdig;
    if (region_head != NULL) {
        for (mr = region_head->mems; mr != NULL; mr = mr->next)
            mr->high = mr->spec.mspace == MS_E ? ext_addr_mask : addr_mask;
    }
    if (target_index == TGT_56600)
        opt_sbm = 1;
    (void)tgt_unk28; (void)tgt_unk30; (void)tgt_unk34; (void)tgt_unk38;
    (void)tgt_dword_hexdig; (void)no_argv_list;
}

/* enter one predefined float symbol; hi/lo are the IEEE double words */
static void float_sym(SYM *t, char *name, unsigned long hi, unsigned long lo)
{
    char *copy;

    copy = (char *)xmalloc((unsigned long)strlen(name) + 1);
    t->name = strcpy(copy, name);
    t->fval = words_to_double(hi, lo);
    sym_enter(t);
    xfree(copy);
}

/* 00404859: Inf, -Inf, Nan, -Nan, Huge, -Huge, Tiny, -Tiny.  The words are
   carried over from one symbol to the next and the "negative" ones only
   keep the sign bit of the previous high word, so -Inf/-Huge are 0.0 and
   -Nan/Tiny/-Tiny the smallest denormal (sic). */
void init_float_names(void)
{
    SYM t;
    unsigned long hi, lo;

    memset(&t, 0, sizeof t);
    t.flags = SYM_GLOBAL | SYM_FLOAT;
    t.mem.mspace = 4;
    t.mem.mmap = 4;
    t.mem.mcntr = 0;
    t.mem.mclass = 0;
    t.scnum = 0;
    t.sec = NULL;
    t.rsec = NULL;
    t.smap = NULL;
    t.buf = NULL;
    t.ovl = NULL;
    t.next = NULL;
    hi = 0x7ff00000UL; lo = 0;
    float_sym(&t, "Inf", hi, lo);
    hi &= 0x80000000UL;
    float_sym(&t, "-Inf", hi, lo);
    hi = 0x7ff00000UL; lo = 1;
    float_sym(&t, "Nan", hi, lo);
    hi &= 0x80000000UL;
    float_sym(&t, "-Nan", hi, lo);
    hi = 0x7ff00000UL; lo = 0;
    float_sym(&t, "Huge", hi, lo);
    hi &= 0x80000000UL;
    float_sym(&t, "-Huge", hi, lo);
    hi = 0; lo = 1;
    float_sym(&t, "Tiny", hi, lo);
    hi &= 0x80000000UL;
    float_sym(&t, "-Tiny", hi, lo);
}

/* 00404bba: map header date ("%02d-%02d-%02d" of tm_year (sic, 3 digits
   after 1999), month, day) and time; returns tm_to_secs(local time) */
long get_date_time_strings(char *date, char *time_s)
{
    time_t now;
    struct tm *tm;
    char *env;

    env = getenv("SOURCE_DATE_EPOCH");
    if (env != NULL)
        now = (time_t)strtol(env, NULL, 10);
    else
        now = time(NULL);
    tm = localtime(&now);
    sprintf(date, "%02d-%02d-%02d", tm->tm_year, tm->tm_mon + 1, tm->tm_mday);
    sprintf(time_s, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
    return tm_to_secs(tm);
}

/* 00404c3a: Macintosh file type/creator stub */
int set_file_type(char *name, char *type, char *creator)
{
    (void)name; (void)type; (void)creator;
    return 1;
}
