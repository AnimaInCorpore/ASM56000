/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), lib.c
 * "$Id: lib.c,v 1.16 1995/12/04 16:17:41 surekha Exp $"
 * Reconstructed from DSPLNK.EXE 0041c470-0041d3e7.
 *
 * Library scanning.  A library is "!<H>" followed by members, each a
 * header line "!<H> name size time" (CR/LF) and a COFF object of size
 * bytes.  Pass 1 pulls every member that defines a still unresolved
 * external (rescanning while new externals appear); pass 2 processes the
 * pulled members again.
 */
#include "dsplnk.h"

#define LIBLINE_SIZE 512

void init_dup_globals_list(void);
void scan_library_members(void);
int process_library_member(char *name, long pos, long size);
void add_dup_global_name(char *name);
int dup_global_seen(char *name);
SYM *next_pullable_symbol(void);
int stage_member_section(char *name, long secno, MEMSPEC *spec);
int read_library_header_line(FILE *fp, char *buf);

static STRNODE *dup_head;               /* 4611bc duplicate global names */
static STRNODE *dup_tail;               /* 4611b8 */
static long lib_scan2;                  /* 461148 0: first member scan, 1: match scan */
static SYM lib_sym;                     /* 461150 staging record of next_pullable_symbol */
static SYMSLOT *lib_syms;               /* 461e6c member symbol table */
static unsigned long lib_nsyms;         /* 461e70 */
static unsigned long lib_symidx;        /* 461e74 */
static char *lib_strtab;                /* 461e78 */

/* fake section chain (46c1a0 / 46c1c0 / 46c240): lib_sym.sec->node->
   sname->name is the member section the symbol belongs to */
static SECNAME lib_secname;
static SECNODE lib_cls;
static SECTION lib_sec;

/* port: NUL-terminated copies of inline (<= 8 byte) names; the original
   points into the symbol slots */
static char lib_symname[9];
static char lib_secname_buf[9];

/* 0041c470 */
void free_dup_globals_list(void)
{
    STRNODE *n, *next;

    n = dup_head;
    while (n != NULL) {
        next = n->next;
        if (n->str == NULL) {
            xfree(n);
            return;
        }
        xfree(n->str);
        xfree(n);
        n = next;
    }
}

/* 0041c4cf: namebuf is "-l<name>" or "-l" (name in the next argument):
   namebuf := name, 1; else 0 */
int is_library_arg(void)
{
    int c;
    char *s, *d;

    if (!no_argv_mode && namebuf[0] == '-') {
        c = namebuf[1] & 0xff;
        if (isupper(c))
            c = tolower(c);
        if (c == 'l') {
            if (namebuf[2] == '\0') {
                s = *cur_argv++;
                if (s == NULL)          /* the original dereferences NULL */
                    lnk_signal_handler(SIGSEGV);
                strcpy(namebuf, s);
                cur_argc--;
            } else {
                d = namebuf;
                for (s = namebuf + 2; *s != '\0'; s++)
                    *d++ = *s;
                *d = '\0';
            }
            return 1;
        }
    }
    return 0;
}

/* 0041c5ec: the library must start with "!<H>" */
void check_library_magic(char *libname)
{
    size_t i, len;
    int c;

    len = strlen(lib_magic);
    for (i = 0; i < len; i++) {
        c = getc(in_fp);
        if (c != (int)(signed char)lib_magic[i] || c == EOF)
            break;
    }
    if (i != len)
        lnk_cmdline_fatal2("Invalid library file", libname);
    if (fseek(in_fp, 0L, SEEK_SET) != 0)
        lnk_cmdline_fatal1("Seek failure");
}

/* 0041c6d7 */
void scan_library(void)
{
    long unresolved;
    MODULE *m;

    if (pass == 1) {
        init_dup_globals_list();
        cur_section = &lib_sec;
        unresolved = num_xrefs - num_xrefs_done;
        while (unresolved != 0 && lib_rescan) {
            lib_rescan = 0;
            if (fseek(in_fp, 0L, SEEK_SET) != 0)
                lnk_fatal1("Seek failure");
            scan_library_members();
            unresolved = num_xrefs - num_xrefs_done;
        }
        lib_rescan = unresolved != 0;
    } else {
        for (m = cur_infile->members; m != NULL; m = m->next) {
            cur_infile->module = m;
            process_module(m);
        }
    }
}

/* 0041c7a2: new list with an empty sentinel (the previous list leaks) */
void init_dup_globals_list(void)
{
    dup_tail = (STRNODE *)xmalloc(sizeof(STRNODE));
    dup_head = dup_tail;
    dup_tail->str = NULL;
    dup_tail->next = NULL;
}

/* seek to the end of the member at pos */
static void skip_member(long pos, long size)
{
    if (fseek(in_fp, pos, SEEK_SET) != 0 || fseek(in_fp, size, SEEK_CUR) != 0)
        lnk_fatal1("Seek failure");
}

/* 0041c7d9: one pass over the members */
void scan_library_members(void)
{
    char line[LIBLINE_SIZE];
    char name[LIBLINE_SIZE];
    long size, pos;
    FILHDR fh;
    LNKHDR lh;

    name[0] = '\0';
    size = 0;
    while (num_xrefs != 0 && read_library_header_line(in_fp, line)) {
        sscanf(line, "%*s %s %ld", name, &size);
        pos = ftell(in_fp);
        if (pos < 0)
            lnk_fatal1("Offset failure");
        if (read_filhdr(&fh, in_fp) != 1)
            lnk_fatal1("Cannot read file header from library module");
        if (cur_target == NULL ||
            ((fh.f_magic == M_DSP56300 || fh.f_magic == M_DSP56600) &&
             target_magic == M_DSP56000))
            set_target_cpu(fh.f_magic);
        if ((fh.f_magic == target_magic ||
             ((target_magic == M_DSP56300 || target_magic == M_DSP56600) &&
              fh.f_magic == M_DSP56000)) &&
            (fh.f_flags & F_RELFLG) == 0) {
            if (read_lnkhdr(&lh, fh.f_opthdr, in_fp) != 1)
                lnk_fatal1("Cannot read optional header from library module");
            if (fh.f_opthdr == OBJ_LNKSZ_OLD) {
                obj_major = 4;
                obj_rev = 0;
                obj_minor = 0;
            } else {
                obj_major = lh.majver;
                obj_minor = lh.minver;
                obj_rev = lh.revno;
            }
            if (fh.f_nsyms == 0) {
                skip_member(pos, size);
            } else {
                if (fseek(in_fp, fh.f_symptr + pos, SEEK_SET) != 0)
                    lnk_fatal1("Cannot seek to library module symbol table");
                lib_syms = read_symbol_entries((unsigned long)fh.f_nsyms);
                lib_nsyms = (unsigned long)fh.f_nsyms;
                lib_symidx = 0;
                lib_strtab = read_string_table();
                process_library_member(name, pos, size);
                skip_member(pos, size);
            }
        } else {
            skip_member(pos, size);
        }
    }
}

/* 0041ca95: pull the member if it defines an unresolved external;
   returns process_module's result, 0 if not pulled */
int process_library_member(char *name, long pos, long size)
{
    char msg[LIBLINE_SIZE + 600];       /* original: 100 bytes */
    unsigned long save_n, save_idx;
    SYM *s;
    XREF *x;
    MODULE *mod;
    char *sn, *xn;

    save_n = lib_nsyms;
    save_idx = lib_symidx;
    lib_scan2 = 0;
    while ((s = next_pullable_symbol()) != NULL) {
        if (opt_wdg == 1 && (s->flags & SYM_GLOBAL) != 0) {
            if (dup_global_seen(s->name) == 1) {
                sprintf(msg, "Found duplicate global symbol: %s in library module %s",
                        s->name, name);
                lnk_warning1(msg);
            } else {
                add_dup_global_name(s->name);
            }
        }
    }
    lib_scan2 = 1;
    lib_nsyms = save_n;
    lib_symidx = save_idx;
    s = NULL;
    while ((s = next_pullable_symbol()) != NULL) {
        x = xref_lookup(s->name);
        if (x == NULL || (x->flags & XREF_DONE) != 0)
            continue;
        sn = s->sec->node->sname->name;
        xn = x->sec == NULL ? global_secname : x->sec->node->sname->name;
        if (sn != NULL && xn != NULL && strcmp(sn, xn) == 0)
            break;
        if (((s->flags & SYM_XDEF) != 0 && (x->flags & XREF_XREF) != 0) ||
            (s->flags & SYM_GLOBAL) != 0)
            break;
    }
    xfree(lib_syms);
    lib_syms = NULL;
    if (lib_strtab != NULL)
        xfree(lib_strtab);
    lib_strtab = NULL;
    lib_symidx = 0;
    lib_nsyms = 0;
    if (s == NULL) {
        skip_member(pos, size);
        return 0;
    }
    if (fseek(in_fp, pos, SEEK_SET) != 0)
        lnk_fatal1("Seek failure");
    mod = new_module(name, size, pos);
    if (cur_infile->members == NULL) {
        cur_infile->module = mod;
        cur_infile->members = mod;
    } else {
        cur_infile->module->next = mod;
        cur_infile->module = mod;
    }
    return process_module(mod);
}

/* 0041cd73 */
void add_dup_global_name(char *name)
{
    if (dup_tail->str == NULL) {
        dup_tail->str = (char *)xmalloc((unsigned long)strlen(name) + 1);
        strcpy(dup_tail->str, name);
    } else {
        dup_tail->next = (STRNODE *)xmalloc(sizeof(STRNODE));
        dup_tail = dup_tail->next;
        dup_tail->str = (char *)xmalloc((unsigned long)strlen(name) + 1);
        strcpy(dup_tail->str, name);
        dup_tail->next = NULL;
    }
}

/* 0041ce1b */
int dup_global_seen(char *name)
{
    STRNODE *n;

    for (n = dup_head; n != NULL && n->str != NULL; n = n->next)
        if (strcmp(n->str, name) == 0)
            return 1;
    return 0;
}

/* 0041ce63: next defining symbol of the member (the static lib_sym) or
   NULL; section symbols stage the fake section and the run/load specs */
SYM *next_pullable_symbol(void)
{
    SYMSLOT *e, *aux;
    char *name;
    long sclass, secno;
    unsigned long f;
    MEMSPEC spec;
    int old;

    memset(&lib_sym, 0, sizeof lib_sym);
    for (;;) {
        if (lib_symidx >= lib_nsyms)
            return NULL;
        e = lib_syms + lib_symidx;
        if (e->s.n_name[0] == 0 && e->s.n_name[1] == 0 &&
            e->s.n_name[2] == 0 && e->s.n_name[3] == 0) {
            name = lib_strtab + name_off(e->s.n_name);
        } else {
            if (lib_scan2 == 0)
                name_swap(e->s.n_name);
            memcpy(lib_symname, e->s.n_name, 8);
            lib_symname[8] = '\0';
            name = lib_symname;
        }
        sclass = e->s.n_sclass;
        old = OBJ_OLD();
        f = 0;
        if (sclass == C_STAT && e->s.n_type == 0) {
            aux = e + 2;
            if (old) {
                secno = aux->a.x[0];
                spec.mspace = 4;
                spec.mmap = 4;
                spec.mcntr = 0;
                spec.mclass = 0;
                spec.mspace = mem_bits_space(aux->a.x[2] & 0xf);
                spec.mmap = spec.mspace;
            } else {
                secno = aux->a.x[0];
                spec.mspace = aux->a.x[3];
                spec.mmap = aux->a.x[4];
                spec.mcntr = aux->a.x[5];
                spec.mclass = aux->a.x[6];
            }
            if (name == lib_symname) {
                strcpy(lib_secname_buf, lib_symname);
                name = lib_secname_buf;
            }
            stage_member_section(name, secno, &spec);
            load_spec = spec;
            run_spec = spec;
        } else if (old) {
            if ((sclass == C_EXT || (sclass == C_STAT && block_depth == 0) ||
                 sclass == C_HIDDEN || sclass == C_LABEL || sclass == A_GLOBAL ||
                 sclass == A_XDEF || sclass == A_SLOCAL) && e->s.n_scnum != 0) {
                if (sclass == C_EXT || sclass == A_GLOBAL)
                    f = SYM_GLOBAL;
                else if (sclass == A_XDEF || sclass == C_HIDDEN)
                    f = SYM_XDEF;
                lib_sym.sec = &lib_sec;
                lib_sym.name = name;
                lib_sym.flags |= f;
                lib_symidx += 1 + (unsigned long)e->s.n_numaux;
                return &lib_sym;
            }
        } else if ((sclass == C_EXT || (sclass == C_STAT && block_depth == 0) ||
                    sclass == A_GLOBAL || sclass == A_XDEF || sclass == A_SLOCAL) &&
                   e->s.n_scnum != 0) {
            if (sclass == C_EXT || sclass == A_GLOBAL)
                f = SYM_GLOBAL;
            else if (sclass == A_XDEF)
                f = SYM_XDEF;
            lib_sym.sec = &lib_sec;
            lib_sym.name = name;
            lib_sym.flags |= f;
            lib_symidx += 1 + (unsigned long)e->s.n_numaux;
            return &lib_sym;
        }
        lib_symidx += 1 + (unsigned long)e->s.n_numaux;
    }
}

/* 0041d20a: fill the fake section chain (pass 1 only) */
int stage_member_section(char *name, long secno, MEMSPEC *spec)
{
    if (pass != 2) {
        lib_secname.name = name;
        lib_secname.num = secno;
        lib_secname.nodes = &lib_cls;
        lib_cls.sname = &lib_secname;
        lib_cls.spec = *spec;
        lib_cls.secs = &lib_sec;
        lib_cls.nsecs = 1;
        lib_sec.node = &lib_cls;
    }
    return pass != 2;
}

/* 0041d288: one member header line (to CR, LF, CR/LF or EOF); 0 at EOF */
int read_library_header_line(FILE *fp, char *buf)
{
    int c, c2, n;

    clearerr(fp);
    n = 0;
    for (;;) {
        c = getc(fp);
        if (c == EOF || c == '\r' || c == '\n')
            break;
        if (n < LIBLINE_SIZE - 1)       /* original: no bounds check */
            buf[n++] = (char)c;
    }
    buf[n] = '\0';
    if (feof(fp))
        return 0;
    if (ferror(fp))
        lnk_fatal1("Invalid library module header");
    if (c == '\r') {
        c2 = getc(fp);
        if (c2 != EOF && c2 != '\n')
            ungetc(c2, fp);
    }
    if (strncmp(buf, lib_magic, (size_t)lib_magic_len) != 0)
        lnk_fatal1("Invalid library module header format");
    return 1;
}
