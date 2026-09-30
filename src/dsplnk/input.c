/*
 * input.c - object module input of the DSP linker
 * (Motorola DSP Linker 6.3.7, DSPLNK.EXE of CLAS56 v6.3)
 * Original module: $Id: input.c,v 1.88 1999/04/16 20:42:20 russo Exp $
 *
 * Reads .cln object modules (pass 1: headers, symbols, section sizes;
 * pass 2: raw data, relocation, output symbol table), defines and
 * references symbols, selects the section/counter records.
 */
#include "dsplnk.h"

/* ---- module state (statics of the original input.c) ---------------- */
static long mem_model;                  /* 461134 first C_FILE x_ftype */
static long last_secno;                 /* 461138 */
static long last_rsecno;                /* 46113c */
static long first_ident = 1;            /* 456b34 ident record not yet written */
static long first_p = 1;                /* 456b38 no P extent seen yet */
static char buf_new;                    /* 461204 buffer number just advanced */
static char sec_byteaddr;               /* 461218 SA_BYTEADDR */
static char sec_bytepack;               /* 46121c SA_BYTEPACK */
static char sec_swapped;                /* 461220 SA_RUNLOAD */
static char sec_swapped_sticky;         /* 461224 */
static char xy_seen;                    /* 461258 */
static long buf_pending;                /* 4612bc autoaligned pad size */
static unsigned long buf_size;          /* 4612c0 buffer size, 0 = no buffer */
static long ovl_force;                  /* 4612d4 never set (dead) */
static unsigned long ctr_before;        /* 461d98 *run_ctr before the pass-1 advance */
static long ovl_offset;                 /* 461d9c aux ovloff */
static MODSEC *cur_msec;                /* 461dec */
static long val_mult;                   /* 461e54 counter multiplier per value */
static long words_per_val;              /* 461e58 */
static SECTREF *mod_sectref;            /* 461e64 = MODULE.sectref */
static SECTREF *cur_sectref2;           /* 461e94 */
static unsigned long reloc_next;        /* 461eb8 */
static unsigned long reloc_base;        /* 461ebc */

#define ADDL(lv, x)  ((lv) = (long)M32((unsigned long)(lv) + (unsigned long)(x)))
#define SUBL(lv, x)  ((lv) = (long)M32((unsigned long)(lv) - (unsigned long)(x)))

static int long_name(char *n)
{
    return n[0] == 0 && n[1] == 0 && n[2] == 0 && n[3] == 0;
}

/* signed view of a 32-bit value */
static long sx32(unsigned long v)
{
    v = M32(v);
    if (v & 0x80000000UL)
        return -(long)(M32(~v) + 1UL);
    return (long)v;
}

/* integer division helpers: the original traps (SIGFPE) on zero */
static long sdiv(long a, long b)
{
    if (b == 0)
        lnk_fatal1("Arithmetic exception");
    return a / b;
}

static unsigned long udiv(unsigned long a, unsigned long b)
{
    if (b == 0)
        lnk_fatal1("Arithmetic exception");
    return M32(a) / M32(b);
}

/* counter multiplier from the EMI class word (>>4 width, &0xf packing) */
static unsigned long mclass_mult(unsigned long c)
{
    long w;

    if ((c & 0xf) == 0)
        return 1;
    w = (long)(c >> 4);
    return (unsigned long)(w / (long)(c & 0xf) + (((c & 1) == 0) ? (w & 1) : 0));
}

static unsigned long space_mask(long ms)
{
    if (!opt_abc || ms == MS_E || ms == MS_D || (target_index == TGT_56800 && ms == MS_P))
        return ext_addr_mask;
    return addr_mask;
}

static void read_module_header(MODULE *mod);
static void check_module_version(MODULE *mod);
static void read_module_data(MODULE *mod);
static void read_module_relocs(MODULE *mod);
static int set_current_section(char *name, SYMSLOT *ent, MODULE *mod);
static int define_symbol(char *name, SYMSLOT *ent);
static void reference_symbol(char *name, SYMSLOT *ent);
static void relocate_section(SECTREF *sr, MODULE *mod);
static void store_value(EXPR *val, EXPR *val2, MODULE *mod, unsigned long *dest);
static void parse_sdi_expression(MODULE *mod, long relidx);
static void track_section_nesting(SYMSLOT *ent);
static void output_symbol(SYMSLOT *ent, MODULE *mod);
static void track_address_range(long nwords);
static void select_counters(unsigned long flags, MEMSPEC *spec, long addr);
static void alloc_module_tables(MODULE *mod);
static FILE *open_input_stream(char *name);
static long file_size(FILE *fp);
static SCNHDR *read_section_headers(unsigned long n);
static void open_next_input_file(void);

/* ==== 414110 ==== */
void process_input_files(void)
{
    INFILE *last;
    unsigned long isl;
    long n;

    last = NULL;
    n = 0;
    if (pass == 1) {
        /* (the dead no_argv_mode branch of the original is omitted) */
        while (++n <= cur_argc) {
            strcpy(namebuf, *cur_argv);
            cur_argv++;
            open_next_input_file();
            isl = cur_infile->flags;
            if ((isl & IF_LIBRARY) == 0)
                process_module(cur_infile->module);
            else
                scan_library();
            if (opt_v)
                fprintf(msg_fp, "%s: Closing %s file %s\n", progname,
                        (isl & IF_LIBRARY) ? "library" : "link", cur_infile->name);
            fclose(in_fp);
        }
    } else {
        if (obj_fp != NULL)
            obj_layout_offsets();
        for (cur_infile = infile_head; cur_infile != NULL; cur_infile = cur_infile->next) {
            isl = cur_infile->flags & IF_LIBRARY;
            if (opt_v)
                fprintf(msg_fp, "%s: Opening %s file %s\n", progname,
                        isl ? "library" : "link", cur_infile->name);
            in_fp = open_input_stream(cur_infile->name);
            if (in_fp == NULL) {
                if (isl == 0)
                    lnk_fatal1("Cannot open object file");
                else
                    lnk_fatal1("Cannot open library file");
            }
            set_file_buffer(in_fp, 0);
            if (isl == 0)
                process_module(cur_infile->module);
            else
                scan_library();
            if (opt_v)
                fprintf(msg_fp, "%s: Closing %s file %s\n", progname,
                        isl ? "library" : "link", cur_infile->name);
            fclose(in_fp);
            last = cur_infile;
        }
        cur_infile = last;
    }
}

/* ==== 4143b4 ==== */
static void open_next_input_file(void)
{
    int islib;
    INFILE *inf;
    long size;

    islib = is_library_arg();
    if (opt_t)
        str_lower(namebuf);
    if (opt_v)
        fprintf(msg_fp, "%s: Opening %s file %s\n", progname,
                islib ? "library" : "link", namebuf);
    in_fp = open_input_stream(namebuf);
    if (in_fp == NULL) {
        if (set_default_ext(islib ? ".clb" : ".cln") == NULL ||
            (in_fp = open_input_stream(namebuf)) == NULL) {
            if (!islib)
                lnk_cmdline_fatal2("Cannot open object file", namebuf);
            else
                lnk_cmdline_fatal2("Cannot open library file", namebuf);
        }
    }
    set_file_buffer(in_fp, 0);
    inf = (INFILE *)xmalloc((unsigned long)sizeof(INFILE));
    inf->name = (char *)xmalloc((unsigned long)strlen(namebuf) + 1);
    strcpy(inf->name, namebuf);
    inf->flags = islib ? IF_LIBRARY : 0;
    if (!islib) {
        size = file_size(in_fp);
        if (size < 0)
            lnk_fatal1("Cannot determine file size");
        inf->module = new_module(NULL, size, 0L);
        inf->members = NULL;
    } else {
        check_library_magic(inf->name);
        inf->members = NULL;
        inf->module = NULL;
    }
    inf->next = NULL;
    if (infile_head != NULL)
        cur_infile->next = inf;
    else
        infile_head = inf;
    cur_infile = inf;
}

/* ==== 4145bb ==== */
MODULE *new_module(char *name, long size, long offset)
{
    MODULE *m;

    m = (MODULE *)xmalloc((unsigned long)sizeof(MODULE));
    memset(m, 0, sizeof(MODULE));
    if (name == NULL) {
        m->name = NULL;
    } else {
        m->name = (char *)xmalloc((unsigned long)strlen(name) + 1);
        strcpy(m->name, name);
    }
    m->size = size;
    m->offset = offset;
    return m;
}

/* ==== 4146c6 ==== */
int process_module(MODULE *mod)
{
    SYMSLOT *ent;
    char *name;
    long i, sc;
    int ok, isold;
    long numaux;

    ok = 0;
    if (pass == 1) {
        read_module_header(mod);
        if (mod_sdi)
            read_module_relocs(mod);
        check_module_version(mod);
        alloc_module_tables(mod);
        if (opt_g && OBJ_OLD() && !cc_objects && (mod->fh.f_flags & F_LNNO) == 0)
            lnk_warning1("Incompatible debug format");
        for (i = 0; i < mod->fh.f_nsyms; i += ent->s.n_numaux + 1) {
            cur_symidx = i;
            ent = &mod->syms[i];
            if (long_name(ent->s.n_name)) {
                name = mod->strtab + name_off(ent->s.n_name);
            } else {
                name_swap(ent->s.n_name);
                name = ent->s.n_name;
            }
            sc = ent->s.n_sclass;
            if (sc == C_FILE && ent[1].a.x[5] != 0) {
                if (mem_model == 0)
                    mem_model = ent[1].a.x[5];
                else if (mem_model != ent[1].a.x[5])
                    lnk_warning1("Memory model mismatch - stack memory space definitions differ in modules");
                if (mem_model == 1)
                    stack_mspace = 2;
                else if (mem_model == 2)
                    stack_mspace = 1;
                else
                    stack_mspace = mem_model;
            }
            if (sc == A_FILE && mem_model != 0) {
                if (mem_model == 1)
                    stack_mspace = 2;
                else if (mem_model == 2)
                    stack_mspace = 1;
            }
            if ((sc == C_FILE || sc == A_FILE) && ent->s.n_type == 1) {
                buf_base = cur_buffer;
                ovl_base = cur_overlay;
                cur_file_ent = ent;
            }
            if (sc == C_BLOCK)
                block_depth += (name[1] != 'b') ? -1 : 1;
            if (sc == C_SDI && cur_alloc != NULL && cur_alloc->sdi != NULL)
                parse_sdi_expression(mod, ent->s.n_value);
            if (sc == C_STAT && ent->s.n_type == 0) {
                cur_scnum = ent->s.n_scnum;
                ok = set_current_section(name, ent, mod);
            } else if (ok) {
                isold = OBJ_OLD();
                if (isold ? (sc == C_EXT || (sc == C_STAT && block_depth == 0) || sc == C_HIDDEN ||
                             sc == C_LABEL || sc == A_GLOBAL || sc == A_XDEF || sc == A_XREF ||
                             sc == A_SLOCAL)
                          : (sc == C_EXT || (sc == C_STAT && block_depth == 0) || sc == A_GLOBAL ||
                             sc == A_XDEF || sc == A_XREF || sc == A_SLOCAL)) {
                    if (ent->s.n_scnum == 0)
                        reference_symbol(name, ent);
                    else
                        define_symbol(name, ent);
                }
            }
        }
        cur_scnum = -1;
        cur_symidx = 0;
        xref_purge();
    } else {
        check_module_version(mod);
        mod_secmap = mod->secmap;
        mod_sectref = mod->sectref;
        mod_buftab = mod->buftab;
        mod_ovltab = mod->ovltab;
        cur_overlay = 0;
        cur_buffer = 0;
        if (sec_nest != NULL)
            lnk_fatal1("Section nesting error");
        if ((mod->fh.f_flags & F_SDI) == 0 || opt_i)
            mod_sdi = 0;
        else
            mod_sdi = 1;
        if (!mod_sdi) {
            mod->lh.sditot = 0;
        } else {
            mod->sdibuf = (unsigned long *)xmalloc((unsigned long)(mod->lh.datasize + mod->lh.sditot) *
                                                   (unsigned long)sizeof(unsigned long));
            mod->sdiptr = mod->sdibuf;
        }
        obj_sditot += mod->lh.sditot;
        reloc_base = reloc_next;
        reloc_next = M32(reloc_next + (unsigned long)mod->lh.relocnt);
        read_module_data(mod);
        for (i = 0; i < mod->fh.f_nsyms; i += numaux + 1) {
            cur_symidx = i;
            ent = &mod->syms[i];
            /* the original steps by (signed char)n_numaux + 1, read before
               output_symbol rewrites n_numaux */
            numaux = ent->s.n_numaux & 0xff;
            if (numaux & 0x80)
                numaux -= 0x100;
            sc = ent->s.n_sclass;
            if ((sc == C_FILE || sc == A_FILE) && ent->s.n_type == 1) {
                buf_base = cur_buffer;
                ovl_base = cur_overlay;
                cur_file_ent = ent;
            }
            if (sc == C_SDI && cur_alloc != NULL && cur_alloc->sdi != NULL)
                cur_alloc->sdi->mod_count++;
            if (sc == A_SECT || sc == C_SECT) {
                track_section_nesting(ent);
            } else if (sc == C_STAT && ent->s.n_type == 0) {
                cur_scnum = ent->s.n_scnum;
                if (set_current_section(NULL, ent, mod))
                    relocate_section(&mod->sectref[ent->s.n_scnum - 1], mod);
            }
            if (!opt_z)
                output_symbol(ent, mod);
        }
        cur_scnum = -1;
        cur_symidx = 0;
        obj_write_module(mod);
    }
    return 1;
}

/* ==== 414d76 ==== */
static void read_module_header(MODULE *mod)
{
    unsigned long n;
    char *s;

    if (fseek(in_fp, mod->offset, SEEK_SET) != 0)
        lnk_fatal1("Cannot seek to start of object module");
    if (read_filhdr(&mod->fh, in_fp) != 1)
        lnk_fatal1("Cannot read file header from object module");
    if (cur_target == NULL ||
        ((mod->fh.f_magic == M_DSP56300 || mod->fh.f_magic == M_DSP56600) &&
         target_magic == M_DSP56000))
        set_target_cpu(mod->fh.f_magic);
    if (mod->fh.f_magic != target_magic &&
        ((target_magic != M_DSP56300 && target_magic != M_DSP56600) ||
         mod->fh.f_magic != M_DSP56000))
        lnk_fatal1("Invalid object file for target processor");
    if (mod->fh.f_flags & F_RELFLG)
        lnk_fatal1("File contains no relocation information");
    if (mod->fh.f_flags & F_CC)
        cc_objects = 1;
    if ((mod->fh.f_flags & F_SDI) == 0) {
        mod_sdi = 0;
    } else {
        sdi_seen = 1;
        if (!opt_i) {
            sdi_active = 1;
            mod_sdi = 1;
        }
    }
    switch (target_magic) {
    case M_DSP56000:
    case M_DSP96000:
        stack_mspace = 3;
        break;
    case M_DSP56100:
    case M_DSP56800:
    case M_SC100:
        stack_mspace = 1;
        break;
    case M_DSP56300:
    case M_DSP56600:
        stack_mspace = 2;
        break;
    default:
        stack_mspace = 2;
    }
    if (read_lnkhdr(&mod->lh, mod->fh.f_opthdr, in_fp) != 1)
        lnk_fatal1("Cannot read optional header from object module");
    n = (unsigned long)mod->fh.f_nscns;
    if (n != 0) {
        mod->scnhdr = read_section_headers(n);
        obj_nscns += (long)n;
    }
    n = (unsigned long)mod->fh.f_nsyms;
    if (n != 0) {
        if (fseek(in_fp, mod->fh.f_symptr + mod->offset, SEEK_SET) != 0)
            lnk_fatal1("Cannot seek to object module symbol table");
        mod->syms = read_symbol_entries(n);
        if (abi_modules == NULL)
            abi_modules = abimparr_create(5L, 5L, abi_mp_sym_free_with_arr);
        abi_mp_symtbl_dispatch(abi_modules, mod);
    }
    mod->strtab = read_string_table();
    if (!start_given && mod->lh.endstr > 3 && mod->strtab != NULL) {
        s = mod->strtab + mod->lh.endstr;
        start_name = (char *)xmalloc((unsigned long)strlen(s) + 1);
        strcpy(start_name, s);
        start_given = 1;
    }
}

/* ==== 41507a ==== */
static void check_module_version(MODULE *mod)
{
    if (mod->fh.f_opthdr == OBJ_LNKSZ_OLD) {
        obj_major = 4;
        obj_rev = 0;
        obj_minor = 0;
    } else {
        obj_major = mod->lh.majver;
        obj_minor = mod->lh.minver;
        obj_rev = mod->lh.revno;
    }
    out_major = obj_major;
    out_minor = obj_minor;
    out_rev = obj_rev;
    if (pass == 1 && opt_wvr) {
        if (lnk_major < obj_major)
            lnk_warning1("Object file major version number greater than linker major version number");
        else if (obj_major == lnk_major && lnk_minor < obj_minor)
            lnk_warning1("Object file minor version number greater than linker minor version number");
    }
}

/* ==== 41516a ==== */
static void read_module_data(MODULE *mod)
{
    unsigned long n;

    n = (unsigned long)mod->lh.datasize;
    if (n != 0) {
        if (fseek(in_fp, mod->scnhdr[0].s_scnptr + mod->offset, SEEK_SET) != 0)
            lnk_fatal1("Cannot seek to object module raw data");
        mod->raw = (unsigned long *)xmalloc(n * (unsigned long)sizeof(unsigned long));
        if (read_words(mod->raw, n, in_fp) != n)
            lnk_fatal1("Cannot read raw data from object module");
    }
    if (mod->reloc == NULL) {
        n = (unsigned long)mod->lh.relocnt;
        if (n != 0) {
            if (fseek(in_fp, mod->scnhdr[0].s_relptr + mod->offset, SEEK_SET) != 0)
                lnk_fatal1("Cannot seek to object module relocation entries");
            mod->reloc = (RELENT *)xmalloc(n * (unsigned long)sizeof(RELENT));
            if (read_relents(mod->reloc, n, in_fp) != n)
                lnk_fatal1("Cannot read relocation entries from object module");
        }
    }
    n = (unsigned long)mod->lh.lnocnt;
    if (n != 0) {
        if (fseek(in_fp, mod->scnhdr[0].s_lnnoptr + mod->offset, SEEK_SET) != 0)
            lnk_fatal1("Cannot seek to object module line number entries");
        mod->lines = (LINENO *)xmalloc(n * (unsigned long)sizeof(LINENO));
        if (read_linenos(mod->lines, n, in_fp) != n)
            lnk_fatal1("Cannot read line number entries from object module");
    }
}

/* ==== 415316 ==== */
static void read_module_relocs(MODULE *mod)
{
    unsigned long n;

    n = (unsigned long)mod->lh.relocnt;
    if (n != 0) {
        if (fseek(in_fp, mod->scnhdr[0].s_relptr + mod->offset, SEEK_SET) != 0)
            lnk_fatal1("Cannot seek to object module relocation entries");
        mod->reloc = (RELENT *)xmalloc(n * (unsigned long)sizeof(RELENT));
        if (read_relents(mod->reloc, n, in_fp) != n)
            lnk_fatal1("Cannot read relocation entries from object module");
    }
}

/* find the MODSEC of section number secno whose output section has the
   memory space and counter of spec (inline loop of the original) */
static MODSEC *find_msec(long secno, long mspace, long mcntr)
{
    MODSEC *m;

    for (m = mod_secmap[secno]; m != NULL; m = m->next)
        if (m->sec->node->spec.mspace == mspace && m->sec->node->spec.mcntr == mcntr)
            break;
    return m;
}

/* name of the first map entry of section number secno (the original
   dereferences it without a check) */
static char *msec_name(long secno)
{
    if (mod_secmap[secno] == NULL)
        lnk_fatal1("Section map lookup failure");
    return mod_secmap[secno]->sec->node->sname->name;
}

/* ==== 4153a6 ==== */
static int set_current_section(char *name, SYMSLOT *ent, MODULE *mod)
{
    SYMSLOT *aux2, *aux3, *oaux;
    long secno, rsecno, t, bufno, ovlno, ovlstr;
    unsigned long flags, fl2, rflags, f10000, blk, runmask, loadmask, n, a, r;
    unsigned long mult_run, mult_load;
    MEMSPEC spec;
    MODSEC *m;
    SECTION *s;
    SECTREF *sr;
    OVLENT *o;
    SDISTAT *st;
    SCNHDR *hdr;
    int isold;

    aux2 = ent + 2;
    aux3 = ent + 3;
    oaux = ent + 4;
    secno = aux2->a.x[0];
    rsecno = aux2->a.x[1];
    if (secno < 0 || rsecno < 0 || mod->lh.secnt < secno || mod->lh.secnt < rsecno)
        lnk_fatal1("Invalid section number data");
    isold = OBJ_OLD();
    if (isold) {
        spec.mmap = 4;
        spec.mspace = 4;
        spec.mcntr = 0;
        spec.mclass = 0;
        spec.mspace = mem_bits_space(aux2->a.x[2] & 0xf);
        spec.mmap = mem_bits_map(spec.mspace, aux2->a.x[2] & 0xf700);
        spec.mcntr = mem_bits_counter(aux2->a.x[2] & 0x30);
        flags = (unsigned long)aux2->a.x[3];
    } else {
        spec.mspace = aux2->a.x[3];
        spec.mmap = aux2->a.x[4];
        spec.mcntr = aux2->a.x[5];
        spec.mclass = aux2->a.x[6];
        flags = (unsigned long)aux2->a.x[2];
    }
    if (spec.mspace != 4 && spec.mmap == 4)
        spec.mmap = spec.mspace;
    if (name != NULL && sec_lookup_create(name, secno, &spec, 1) == NULL)
        return 0;
    if (flags & SA_RUNLOAD) {
        t = secno;
        secno = rsecno;
        rsecno = t;
    }
    m = find_msec(secno, spec.mspace, spec.mcntr);
    if (m == NULL) {
        sec_lookup_create(msec_name(secno), secno, &spec, 1);
        m = find_msec(secno, spec.mspace, spec.mcntr);
        if (m == NULL)
            lnk_fatal1("Section map lookup failure");
        else
            cur_msec = m;
    } else {
        cur_msec = m;
    }
    cur_section = cur_msec->sec;
    if (cur_section == NULL)
        lnk_fatal1("Cannot set current section");
    cur_secid = cur_section->node->sname->num;
    if (rsecno == secno) {
        cur_rmsec = cur_msec;
        cur_rsection = cur_section;
    } else {
        m = find_msec(rsecno, spec.mspace, spec.mcntr);
        if (m == NULL) {
            sec_lookup_create(msec_name(rsecno), rsecno, &spec, 1);
            m = find_msec(rsecno, spec.mspace, spec.mcntr);
            if (m == NULL)
                lnk_fatal1("Section map lookup failure");
            else
                cur_rmsec = m;
        } else {
            cur_rmsec = m;
        }
        cur_rsection = cur_rmsec->sec;
    }
    if (cur_rsection == NULL)
        lnk_fatal1("Current relocation section not available");
    cur_rsecid = cur_rsection->node->sname->num;
    cur_memreg = cur_rsection->node->memreg;
    cur_section->run = cur_rsection;
    cur_rsecno = rsecno;
    run_reloc = (flags & SA_RELOC) != 0;
    nested_secs = (flags & SA_NEST) != 0;
    sec_byteaddr = (flags & SA_BYTEADDR) != 0;
    sec_bytepack = (flags & SA_BYTEPACK) != 0;
    sec_swapped = (flags & SA_RUNLOAD) != 0;
    if (!sec_swapped_sticky || last_secno != secno || last_rsecno != rsecno)
        sec_swapped_sticky = (flags & SA_RUNLOAD) != 0;
    f10000 = flags & SA_10000;
    last_secno = secno;
    last_rsecno = rsecno;
    load_reloc = run_reloc;
    cur_rsection->node->flags |= flags & SA_40000;
    flags &= SA_CLEAR_MASK;
    load_aligned = 1;
    if (pass == 2) {
        if (!sec_swapped_sticky && cur_secid != cur_rsecid) {
            s = cur_section;
            m = cur_msec;
        } else {
            s = cur_rsection;
            m = cur_rmsec;
        }
        if (m->fsym != cur_file_ent) {
            m->base2 = M32(s->hi - s->lo);
            m->fsym = cur_file_ent;
        }
    }
    cur_sectref = mod_sectref + (ent->s.n_scnum - 1);
    cur_sectref2 = cur_sectref;
    sr = cur_sectref;
    if (sr == NULL)
        lnk_fatal1("Cannot set section counter");
    if (pass == 1) {
        sr->hdr = mod->scnhdr + (ent->s.n_scnum - 1);
        sr->sym = ent;
        obj_nlnno = M32(obj_nlnno + (unsigned long)sr->hdr->s_nlnno);
        if ((sr->hdr->s_flags & (STYP_PAD | STYP_BSS)) == 0) {
            obj_nwords = M32(obj_nwords + (unsigned long)sr->hdr->s_size);
            obj_nreloc = M32(obj_nreloc + (unsigned long)sr->hdr->s_nreloc);
        }
    }
    hdr = sr->hdr;
    if ((flags & SA_BUFFER) == 0) {
        if ((flags & SA_RELOC) != 0 && (hdr->s_flags & STYP_PAD) != 0) {
            t = (spec.mspace == MS_L) ? hdr->s_size / 2 : hdr->s_size;
            buf_pending = t;
            cur_rsection->node->bufsz = M32(cur_rsection->node->bufsz + (unsigned long)t);
            cur_rsection->node->bufsz_al = M32(cur_rsection->node->bufsz_al + (unsigned long)t);
        }
        buf_type = 0;
        buf_size = 0;
        oaux = aux3;
        fl2 = flags;
    } else {
        bufno = isold ? aux2->a.x[4] : aux3->a.x[0];
        if (bufno == cur_buffer) {
            buf_new = 0;
        } else {
            if (bufno != cur_buffer + 1) {
                if (pass == 1)
                    lnk_error1("Buffer out of order");
                return 0;
            }
            buf_new = 1;
            cur_buffer++;
            num_buffers++;
        }
        buf_seq++;
        if (isold) {
            buf_type = (unsigned long)aux2->a.x[5];
            buf_size = (unsigned long)aux2->a.x[6];
        } else {
            buf_type = (unsigned long)aux3->a.x[1];
            buf_size = (unsigned long)aux3->a.x[2];
        }
        load_aligned = (buf_type & 0x2000) == 0;
        if (!load_aligned || (cur_rsection->state & SS_NOLALIGN) == 0)
            cur_rsection->state |= buf_type & 0x2000;
        else
            lnk_warning1("Cannot deactivate load alignment in this section and counter");
        buf_type &= ~0x2000UL;
        rflags = cur_rsection->flags;
        fl2 = flags | (rflags & SA_20000);
        if ((flags & SA_RELOC) != 0 && buf_new) {
            cur_rsection->node->bufsz = M32(cur_rsection->node->bufsz + buf_size);
            cur_rsection->node->bufsz_al = M32(cur_rsection->node->bufsz_al + buf_size);
            if ((flags & SA_OVERLAY) != 0 && ((flags & SA_20000) != 0 || (rflags & SA_20000) != 0))
                lnk_error1("Autoaligned buffer not allowed in overlay");
        }
    }
    flags = fl2;
    if ((flags & SA_OVERLAY) == 0) {
        ovl_mem.mmap = 4;
        ovl_mem.mspace = 4;
    } else {
        ovlno = isold ? aux2->a.x[4] : oaux->a.x[4];
        if (ovlno == cur_overlay + 1) {
            cur_overlay++;
            num_overlays++;
        } else if (ovlno != cur_overlay) {
            if (pass == 1)
                lnk_error1("Overlay out of order");
            return 0;
        }
        if (isold) {
            ovl_mem.mmap = 4;
            ovl_mem.mspace = 4;
            ovl_mem.mcntr = 0;
            ovl_mem.mclass = 0;
            ovl_mem.mspace = mem_bits_space(aux2->a.x[5] & 0xf);
            ovl_mem.mmap = mem_bits_map(ovl_mem.mspace, aux2->a.x[5] & 0xf700);
            ovl_mem.mcntr = mem_bits_counter(aux2->a.x[5] & 0x30);
        } else {
            ovl_mem.mspace = oaux->a.x[0];
            ovl_mem.mmap = oaux->a.x[1];
            ovl_mem.mcntr = oaux->a.x[2];
            ovl_mem.mclass = oaux->a.x[3];
        }
        if (OBJ_PRE533())
            ovl_offset = 0;
        else
            ovl_offset = oaux->a.x[6];
        ovl_seq++;
        run_reloc = (flags & SA_OVLRELOC) != 0;
        flags &= ~SA_OVLRELOC;
        o = &mod_ovltab[cur_overlay];
        if (pass == 1) {
            if (o->sec == NULL) {
                o->module = cur_infile->module;
                o->grp = NULL;
                o->sec = NULL;
                o->lsec = cur_section;
                o->rsec = cur_rsection;
                ovlstr = isold ? aux2->a.x[6] : oaux->a.x[5];
                if (ovlstr < 0)
                    o->baseexpr = NULL;
                else
                    o->baseexpr = mod->strtab + ovlstr;
            }
            if (o->maxbuf < buf_size)
                o->maxbuf = buf_size;
        }
        if (pass == 2 && run_reloc && o->maxbuf != 0) {
            a = o->sec->lo;
            r = round_up_pow2(o->maxbuf);
            if (a != (M32(a - 1 + r) & M32(~(r - 1))))
                lnk_warning1("Overlay buffer not aligned");
            o->maxbuf = 0;
        }
    }
    select_counters(flags, &spec, hdr->s_paddr);
    blk = hdr->s_flags & STYP_BLOCK;
    obj_nlnno_file += hdr->s_nlnno;
    if (mod_sdi && run_spec.mspace == MS_P) {
        if (cur_alloc->sdi == NULL) {
            sdi_stats_new(cur_alloc);
        } else {
            st = cur_alloc->sdi;
            if (st->stamp != cur_infile->module) {
                st->mod_first = st->n;
                st->mod_count = 0;
                st->stamp = cur_infile->module;
            }
        }
    }
    mult_run = mclass_mult((unsigned long)run_spec.mclass);
    mult_load = mclass_mult((unsigned long)load_spec.mclass);
    runmask = space_mask(run_spec.mspace);
    loadmask = space_mask(load_spec.mspace);
    if (pass == 1) {
        if (blk == 0) {
            if (load_spec.mspace == MS_L)
                n = (unsigned long)(hdr->s_size / 2);
            else if (run_spec.mspace == MS_U || load_spec.mspace != MS_U)
                n = M32((unsigned long)hdr->s_size * mult_run);
            else
                n = (unsigned long)sdiv(sx32((unsigned long)hdr->s_size), word_bytes);
        } else {
            n = (unsigned long)hdr->s_vaddr;
            if (run_spec.mspace == MS_U || load_spec.mspace == MS_U)
                n = udiv(n, (unsigned long)hdr->s_size);
        }
        ctr_before = *run_ctr;
        if (run_ctr == load_ctr || !sec_byteaddr || blk == 0)
            *run_ctr = M32(*run_ctr + n);
        else
            *run_ctr = M32(*run_ctr + udiv(n, (unsigned long)word_bytes));
        *run_ctr &= runmask;
        if (run_ctr != load_ctr) {
            if (blk == 0) {
                if (load_spec.mspace == MS_L)
                    n = (unsigned long)(hdr->s_size / 2);
                else
                    n = M32((unsigned long)hdr->s_size * mult_load);
            } else {
                n = (unsigned long)hdr->s_vaddr;
                if (run_spec.mspace == MS_U || load_spec.mspace == MS_U)
                    n = udiv(n, (unsigned long)hdr->s_size);
            }
            if (!sec_byteaddr || load_spec.mspace == MS_E)
                *load_ctr = M32(*load_ctr + n);
            else
                *load_ctr = M32(*load_ctr + n * (unsigned long)word_bytes);
            *load_ctr &= loadmask;
            mod_ovltab[cur_overlay].sec->flags |= f10000;
        }
    } else {
        if (!opt_i) {
            if ((hdr->s_flags & STYP_DEBUG) == 0) {
                memset(hdr->s_name, 0, 8);
                if ((hdr->s_flags & STYP_PAD) == 0 && (hdr->s_flags & STYP_BSS) == 0)
                    strcpy(hdr->s_name, load_spec.mspace == MS_P ? ".txt" : ".dat");
                else
                    strcpy(hdr->s_name, ".bss");
                name_swap(hdr->s_name);
            } else if (long_name(hdr->s_name)) {
                set_name_off(hdr->s_name,
                             (unsigned long)obj_add_string(mod->strtab + name_off(hdr->s_name)));
            } else {
                name_swap(hdr->s_name);
            }
        } else if (long_name(hdr->s_name)) {
            set_name_off(hdr->s_name,
                         (unsigned long)obj_add_string(mod->strtab + name_off(hdr->s_name)));
        } else {
            name_swap(hdr->s_name);
        }
        hdr->s_paddr = (long)*load_ctr;
        if (blk == 0)
            hdr->s_vaddr = (long)*load_ctr;
        obj_nscns++;
    }
    return 1;
}

/* ==== 416622 ==== */
static int define_symbol(char *name, SYMSLOT *ent)
{
    SYM sym;
    unsigned long flags, cls, fl2;
    int hasbuf, hasovl;
    SDISTAT *st;
    MODSEC *m;
    SECTION *s;

    hasbuf = buf_size != 0;
    hasovl = ovl_mem.mspace != 4;
    memset(&sym, 0, sizeof(sym));
    if (ent->s.n_sclass == A_XREF)
        return 1;
    if (cur_rsection == NULL)
        lnk_fatal1("Current relocation section not available");
    if (cur_rmsec == NULL)
        lnk_fatal1("Current relocation map not available");
    sym.name = name;
    flags = 0;
    sym.mem.mmap = 4;
    sym.mem.mspace = 4;
    sym.mem.mcntr = 0;
    sym.mem.mclass = 0;
    if (ent->s.n_scnum > 0 || (ent->s.n_type & 0x30) == DT_PTR) {
        sym.mem.mmap = ent->s.n_mem;
        sym.mem.mspace = map_to_space(sym.mem.mmap);
        if (sym.mem.mspace == MS_BAD) {
            lnk_error2("Invalid symbol memory mapping", name);
            return 0;
        }
        if (sym.mem.mspace != 4)
            flags = (run_reloc && ent->s.n_scnum >= 1) ? SYM_REL : 0;
    }
    if ((ent->s.n_type == T_FLOAT || ent->s.n_type == 7) && sym.mem.mspace == 4)
        flags |= SYM_FLOAT;
    else
        flags |= SYM_INT;
    if (ent->s.n_type == T_LONG && sym.mem.mspace == 4)
        flags |= SYM_LONG;
    if (OBJ_OLD()) {
        if (ent->s.n_sclass == C_EXT)
            cls = SYM_GLOBAL;
        else if (ent->s.n_sclass == A_GLOBAL)
            cls = SYM_GLOBAL;
        else if (ent->s.n_sclass == A_XDEF)
            cls = SYM_XDEF;
        else
            cls = (ent->s.n_sclass != C_HIDDEN) ? SYM_LOCAL : SYM_XDEF;
    } else if (ent->s.n_sclass == C_EXT) {
        cls = SYM_GLOBAL;
    } else if (ent->s.n_sclass == A_GLOBAL) {
        cls = SYM_GLOBAL;
    } else {
        cls = (ent->s.n_sclass != A_XDEF) ? SYM_LOCAL : SYM_XDEF;
    }
    flags |= cls;
    fl2 = flags | (hasbuf ? SYM_BUFFER : 0) | (hasovl ? SYM_OVERLAY : 0);
    if ((flags & SYM_FLOAT) == 0) {
        if ((flags & SYM_LONG) == 0 && ent->s.n_mem >= 0 && ent->s.n_mem < 0x124) {
            sym.fval = 0.0;
            sym.hi = 0;
            sym.lo = M32((unsigned long)ent->s.n_value);
            flags = fl2;
            if (target_index == TGT_56800 && sym.mem.mspace == MS_P) {
                sym.hi = ((sym.lo & M32(~word_mask)) >> ((unsigned)word_bits & 0x1f)) & 0xf;
                sym.lo &= word_mask;
                flags = fl2 | SYM_LONG;
            }
            if (target_index == TGT_SC100 && sym.mem.mspace == MS_P) {
                sym.hi = ((sym.lo & M32(~word_mask)) >> ((unsigned)word_bits & 0x1f)) & word_mask;
                flags |= SYM_LONG;
            }
        } else {
            sym.hi = M32((unsigned long)ent->s.n_mem);
            sym.lo = M32((unsigned long)ent->s.n_value);
            flags = fl2;
        }
    } else {
        flags = fl2;
        sym.fval = words_to_double(M32((unsigned long)ent->s.n_mem),
                                   M32((unsigned long)ent->s.n_value));
        sym.hi = M32((unsigned long)ent->s.n_mem);
    }
    sym.flags = flags;
    sym.sfval = sym.fval;
    sym.shi = sym.hi;
    sym.slo = sym.lo;
    sym.sunk_14 = sym.unk_14;
    sym.scnum = ent->s.n_scnum;
    sym.sdi_cnt = 0;
    if (mod_sdi && sym.mem.mspace == MS_P && (flags & SYM_REL) != 0) {
        st = cur_alloc->sdi;
        if (st != NULL && st->n != 0)
            sym.sdi_cnt = st->mod_first + st->mod_count;
        if (cur_rsection->node->ovl_last != NULL)
            sym.osec = cur_rsection->node->ovl_last;
    }
    sym.cls_off = cur_rsection->node->bufsz;
    sym.sec = cur_section;
    sym.rsec = cur_rsection;
    sym.smap = cur_rmsec;
    sym.buf = hasbuf ? &mod_buftab[cur_buffer] : NULL;
    sym.ovl = hasovl ? &mod_ovltab[cur_overlay] : NULL;
    sym.next = NULL;
    if (sym.mem.mspace != 4 && sym.mem.mspace != run_spec.mspace) {
        sym.mem.mcntr = run_spec.mcntr;
        m = find_msec(cur_rsecno, sym.mem.mspace, run_spec.mcntr);
        if (m == NULL) {
            s = sec_lookup_create(msec_name(cur_rsecno), cur_rsecno, &sym.mem, 1);
            sym.sec = s;
            m = find_msec(cur_rsecno, sym.mem.mspace, sym.mem.mcntr);
            sym.rsec = s;
            if (m == NULL)
                lnk_fatal1("Symbol map lookup failure");
            else
                sym.smap = m;
        } else {
            sym.smap = m;
            sym.sec = m->sec;
            sym.rsec = m->sec;
        }
    }
    sym_enter(&sym);
    return 1;
}

/* ==== 416bed ==== */
static void reference_symbol(char *name, SYMSLOT *ent)
{
    STRNODE *n;
    int is_xdef;

    is_xdef = ent->s.n_sclass == (OBJ_OLD() ? C_HIDDEN : A_XDEF);
    if (opt_mcm == 1 && is_xdef != 1 && ent->s.n_sclass == C_EXT)
        is_xdef = 1;
    if (cur_section == NULL)
        lnk_fatal1("Current section not available");
    xref_add(name, 0, is_xdef);
    if (is_xdef) {
        n = (STRNODE *)xmalloc((unsigned long)sizeof(STRNODE));
        n->str = (char *)xmalloc((unsigned long)strlen(name) + 1);
        strcpy(n->str, name);
        if (opt_n)
            str_lower(n->str);
        n->next = cur_section->node->sname->xrefs;
        cur_section->node->sname->xrefs = n;
    }
}

/* SDI adjustment of a relocated address; cursor is sdi->growth (relocs)
   or sdi->maxgrowth (line numbers) - the original uses these SDISTAT
   words +0x08/+0x0c as pass-2 read cursors */
static void sdi_adjust(SDISTAT *st, long *cursor, unsigned long key, int by_orig, long *val)
{
    long idx, g;
    SDIREC *rec;

    idx = (*cursor == st->n_saved) ? *cursor - 1 : *cursor;
    rec = st->recs + idx;
    g = rec->growth;
    if (*cursor == st->n_saved || (by_orig ? rec->orig : rec->addr) != key) {
        if (g != 0 && *cursor != 0)
            ADDL(*val, st->recs[*cursor - 1].growth);
    } else {
        if (g != 0 && (rec->flags & SDI_LONG) != 0)
            g--;
        ADDL(*val, g);
        (*cursor)++;
    }
}

/* ==== 416cf8 ==== */
static void relocate_section(SECTREF *sr, MODULE *mod)
{
    unsigned long lclass, lo, base, base_raw, bufal, rflags, old, nblk;
    unsigned long mult_run, mult_load, runmask, loadmask, lines_idx, nlno;
    unsigned long relidx;
    long rawidx, nwords, i, size, form;
    SDISTAT *st;
    int hs, lspace_l;
    RELENT *rel, *relstart, *r;
    LINENO *ln, *lnstart;
    SCNHDR *hdr;
    SDIREC *rec;
    EXPR *e, *e2;
    unsigned long *p;
    long g;

    hdr = sr->hdr;
    lclass = (unsigned long)load_spec.mclass;
    relstart = NULL;
    if (cur_rsection == NULL)
        lnk_fatal1("Current relocation section not available");
    if (cur_rmsec == NULL)
        lnk_fatal1("Current relocation map not available");
    lo = cur_rsection->lo;
    base = cur_rmsec->base;
    base_raw = cur_rmsec->base_raw;
    bufal = cur_rsection->node->bufsz_al;
    rflags = cur_rsection->flags;
    st = cur_alloc->sdi;
    hs = mod_sdi && st != NULL && st->n_saved != 0;
    nblk = 1;
    if ((hdr->s_flags & STYP_BLOCK) != 0) {
        if (!sec_byteaddr)
            nblk = (unsigned long)hdr->s_vaddr;
        else
            nblk = udiv((unsigned long)hdr->s_vaddr, (unsigned long)word_bytes);
        if ((sec_bytepack && run_ctr != load_ctr) ||
            run_spec.mspace == MS_U || load_spec.mspace == MS_U)
            nblk = udiv(nblk, (unsigned long)hdr->s_size);
    }
    mult_run = mclass_mult((unsigned long)run_spec.mclass);
    mult_load = mclass_mult(lclass);
    runmask = space_mask(run_spec.mspace);
    loadmask = space_mask(load_spec.mspace);
    words_per_val = 1;

    /* relocation entries */
    if (hdr->s_nreloc != 0) {
        relidx = M32((unsigned long)hdr->s_relptr - (unsigned long)mod->scnhdr[0].s_relptr) / 12;
        relstart = mod->reloc + relidx;
        for (r = relstart; r < relstart + hdr->s_nreloc; r++) {
            if (!opt_i) {
                if (load_reloc) {
                    old = M32((unsigned long)r->r_vaddr);
                    ADDL(r->r_vaddr, lo);
                    if ((rflags & SF_ALIGNED) == 0)
                        ADDL(r->r_vaddr, base);
                    else if ((rflags & SF_BUF) == 0)
                        ADDL(r->r_vaddr, base_raw - bufal);
                    else
                        SUBL(r->r_vaddr, mod_buftab[cur_buffer].addr);
                    if (run_ctr == load_ctr)
                        ADDL(r->r_vaddr, cur_rsection->node->sdigrow);
                    else
                        ADDL(r->r_vaddr, mod_ovltab[cur_overlay].sdioff);
                    if (hs && (cur_alloc->flags & SF_BUF) == 0)
                        sdi_adjust(st, &st->growth, old, 1, &r->r_vaddr);
                }
            } else {
                r->r_symndx = obj_add_string(mod->strtab + r->r_symndx);
                if (load_reloc)
                    ADDL(r->r_vaddr, base);
            }
        }
    }

    /* line numbers */
    if (opt_g && run_reloc && hdr->s_nlnno != 0) {
        lines_idx = M32((unsigned long)hdr->s_lnnoptr - (unsigned long)mod->scnhdr[0].s_lnnoptr) / 12;
        nlno = (unsigned long)mod->lh.lnocnt;
        lnstart = mod->lines + lines_idx;
        for (ln = lnstart; ln < lnstart + hdr->s_nlnno && lines_idx <= nlno; ln++) {
            if (ln->l_lnno == 0)
                continue;
            if (!opt_i) {
                if (ovl_mem.mspace == 4) {
                    ADDL(ln->l_addr, lo);
                    if ((rflags & SF_ALIGNED) == 0)
                        ADDL(ln->l_addr, base);
                    else if ((rflags & SF_BUF) == 0)
                        ADDL(ln->l_addr, base_raw - bufal);
                    else
                        SUBL(ln->l_addr, mod_buftab[cur_buffer].addr);
                    ADDL(ln->l_addr, cur_rsection->node->sdigrow);
                } else {
                    ADDL(ln->l_addr, mod_ovltab[cur_overlay].grp->lo);
                }
            } else if (ovl_mem.mspace == 4) {
                ADDL(ln->l_addr, base);
            }
            if (hs && (cur_alloc->flags & SF_BUF) == 0)
                sdi_adjust(st, &st->maxgrowth, M32((unsigned long)ln->l_addr), 0, &ln->l_addr);
        }
    }

    if (hdr->s_size == 0) {
        two_words = 0;
        return;
    }
    lspace_l = load_spec.mspace == MS_L;
    if (hdr->s_scnptr == 0) {
        /* no raw data: advance the counters only */
        if (!sec_byteaddr)
            nwords = hdr->s_size;
        else
            nwords = sdiv(sx32((unsigned long)hdr->s_size), word_bytes);
        nblk = (unsigned long)nwords;
        if (load_spec.mspace == MS_L)
            nblk = M32(nblk) >> 1;
        nblk = udiv(nblk, mult_load);
        track_address_range((long)M32(nblk * mult_run));
        *run_ctr = M32(*run_ctr + nblk * mult_run);
        *run_ctr &= runmask;
        if (run_ctr == load_ctr)
            return;
        if (!sec_byteaddr)
            *load_ctr = M32(*load_ctr + nblk * mult_load);
        else
            *load_ctr = M32(*load_ctr + nblk * (unsigned long)word_bytes);
        *load_ctr &= loadmask;
        return;
    }
    if (hdr->s_nreloc == 0) {
        rel = NULL;
    } else {
        rel = mod->reloc + M32((unsigned long)hdr->s_relptr -
                               (unsigned long)mod->scnhdr[0].s_relptr) / 12;
        relstart = rel;
    }
    rawidx = sx32(M32((unsigned long)hdr->s_scnptr - (unsigned long)mod->scnhdr[0].s_scnptr));
    rawidx = (rawidx >= 0) ? rawidx / 4 : -(-rawidx / 4);       /* rounded toward zero */
    size = hdr->s_size;
    for (i = 0; i < size; i += lspace_l + words_per_val) {
        p = mod->raw + rawidx + i;
        two_words = 0;
        e2 = NULL;
        e = NULL;
        if (run_spec.mspace == MS_U || load_spec.mspace != MS_U)
            words_per_val = 1;
        else
            words_per_val = word_bytes;
        val_mult = 1;
        addr_bytes = words_per_val;
        if (!opt_i && rel != NULL && *load_ctr == M32((unsigned long)rel->r_vaddr)) {
            if (hs && st->recs != NULL) {
                rec = st->recs + ((st->n == st->n_saved) ? st->n - 1 : st->n);
                g = rec->growth;
                if (g != 0 && (rec->flags & SDI_LONG) != 0)
                    g--;
                if (M32(rec->addr + (unsigned long)g) == *run_ctr) {
                    form = sdi_next_form();
                    input_cursor = rec->text;
                    if (form == 2) {
                        two_words = 1;
                        e = eval_expr();
                        input_cursor++;
                        if (e != NULL && (e2 = eval_expr()) == NULL) {
                            free_expr(e);
                            e = NULL;
                        }
                    } else if (form == 1) {
                        input_cursor += rec->alt1;
                        e = eval_expr();
                    } else {
                        input_cursor += (rec->alt2 == 0) ? rec->alt1 : rec->alt2;
                        e = eval_expr();
                    }
                } else {
                    input_cursor = mod->strtab + rel->r_symndx;
                    e = eval_expr();
                }
            } else {
                input_cursor = mod->strtab + rel->r_symndx;
                /* the original passes the raw word pointer as 2nd argument */
                e = abi_expr_eval_impl(mod, 0L, input_cursor);
                if (e == NULL)
                    e = eval_expr();
            }
            if (e != NULL)
                store_value(e, e2, mod, p);
            rel++;
            if (rel >= relstart + hdr->s_nreloc)
                rel = NULL;
        } else if (mod_sdi) {
            *mod->sdiptr++ = *p;
            if (run_spec.mspace == MS_L)
                *mod->sdiptr++ = p[1];
        }
        if (e != NULL)
            free_expr(e);
        if (e2 != NULL)
            free_expr(e2);
        if (two_words)
            nblk++;
        track_address_range((long)M32(nblk * (unsigned long)words_per_val));
        *run_ctr = M32(*run_ctr + nblk * mult_run * (unsigned long)val_mult);
        *run_ctr &= runmask;
        if (run_ctr != load_ctr) {
            if (!sec_byteaddr)
                *load_ctr = M32(*load_ctr + nblk * mult_load * (unsigned long)words_per_val);
            else
                *load_ctr = M32(*load_ctr + nblk * (unsigned long)word_bytes *
                                (unsigned long)words_per_val);
            *load_ctr &= loadmask;
        }
        if (two_words)
            nblk--;
    }
    two_words = 0;
}

/* ==== 417a64 ==== */
static void store_value(EXPR *val, EXPR *val2, MODULE *mod, unsigned long *dest)
{
    unsigned long v, mask, hiw;
    long rw, lw, i, sh;
    unsigned long *d;

    v = 0;
    if ((!sec_bytepack || run_ctr == load_ctr) &&
        ((target_index != TGT_56300 && target_index != TGT_56600) ||
         (run_spec.mspace != MS_U && load_spec.mspace != MS_U))) {
        if (run_spec.mspace == MS_L) {
            if (val->type == EXPR_INT) {
                if (!mod_sdi) {
                    if (target_index == TGT_56600 && val->map == 0x1e) {
                        dest[0] = M32(val->lo) & 0xffff;
                        dest[1] = M32(val->lo) >> 16;
                    } else {
                        dest[0] = val->lo & word_mask;
                        dest[1] = (val->space == 4) ? (val->mid & word_mask) : 0;
                    }
                } else {
                    *mod->sdiptr++ = val->lo & word_mask;
                    hiw = (val->space == 4) ? (val->mid & word_mask) : 0;
                    *mod->sdiptr++ = hiw;
                }
            } else if (target_index == TGT_96000) {
                if (!mod_sdi) {
                    double_to_words(val->fval, dest, dest + 1);
                } else {
                    double_to_words(val->fval, mod->sdiptr, mod->sdiptr + 1);
                    mod->sdiptr += 2;
                }
            } else {
                float_to_fixed_frac(val->fval, fmt_dword, val);
                if (!mod_sdi) {
                    dest[0] = val->lo & word_mask;
                    dest[1] = val->mid & word_mask;
                } else {
                    *mod->sdiptr++ = val->lo & word_mask;
                    *mod->sdiptr++ = val->mid & word_mask;
                }
            }
        } else {
            rw = (long)((unsigned long)run_spec.mclass >> 4);
            lw = (long)((unsigned long)load_spec.mclass >> 4);
            if (val->type == EXPR_INT) {
                v = M32(val->lo);
                if (target_index == TGT_56000 || target_index == TGT_56600) {
                    if (target_index == TGT_56600 && run_spec.mmap == 0x1e) {
                        if (v > 0xff && ((v & 0x80) == 0 || (v & 0xffffff00UL) != 0xffffff00UL))
                            lnk_warning1("EMI 8-bit memory value truncated");
                        v &= 0xff;
                    } else if (target_index == TGT_56600 &&
                               (run_spec.mspace == MS_X || run_spec.mspace == MS_Y)) {
                        if (v > 0xffff && ((v & 0x8000) == 0 || (v & 0xffff0000UL) != 0xffff0000UL))
                            lnk_warning1("X or Y 16-bit memory value truncated");
                        v &= 0xffff;
                    } else if (target_index == TGT_56600 && run_spec.mspace == MS_P) {
                        if (v > 0xffffffUL &&
                            ((v & 0x800000UL) == 0 || (v & 0xff000000UL) != 0xff000000UL))
                            lnk_warning1("P 24-bit memory value truncated");
                        v &= 0xffffffUL;
                    } else if (run_spec.mclass != 0 || load_spec.mclass != 0) {
                        if (rw == 2 || lw == 2) {
                            if (sx32(v) < -0x80L || sx32(v) > 0x7fL)
                                lnk_warning1("EMI 8-bit memory value truncated");
                            v &= 0xff;
                        } else if (rw == 3 || lw == 3) {
                            if (sx32(v) < -0x800L || sx32(v) > 0x7ffL)
                                lnk_warning1("EMI 12-bit memory value truncated");
                            v &= 0xfff;
                        } else if (rw == 4 || lw == 4) {
                            if (sx32(v) < -0x8000L || sx32(v) > 0x7fffL) {
                                if (target_index == TGT_56000)
                                    lnk_warning1("EMI 16-bit memory value truncated");
                                else
                                    lnk_warning1("X or Y 16 bit memory value truncated");
                            }
                            v &= 0xffff;
                        } else if (rw == 5 || lw == 5) {
                            if (sx32(v) < -0x80000L || sx32(v) > 0x7ffffL)
                                lnk_warning1("EMI 20-bit memory value truncated");
                            v &= 0xfffffUL;
                        }
                    }
                }
            } else if (target_index == TGT_96000) {
                v = float_bits(val->fval);
            } else if (target_index == TGT_56000 || target_index == TGT_56600) {
                if (target_index == TGT_56600 && run_spec.mmap == 0x1e)
                    v = double_to_frac_n(val->fval, 0xffUL);
                else if (target_index == TGT_56600 &&
                         (run_spec.mspace == MS_P || run_spec.mspace == MS_X ||
                          run_spec.mspace == MS_Y))
                    v = double_to_frac_n(val->fval, 0xffffUL);
                else if (run_spec.mclass == 0 && load_spec.mclass == 0)
                    v = double_to_frac(val->fval);
                else if (rw == 2 || lw == 2)
                    v = double_to_frac_n(val->fval, 0xffUL);
                else if (rw == 3 || lw == 3)
                    v = double_to_frac_n(val->fval, 0xfffUL);
                else if (rw == 4 || lw == 4)
                    v = double_to_frac_n(val->fval, 0xffffUL);
                else if (rw == 5 || lw == 5)
                    v = double_to_frac_n(val->fval, 0xfffffUL);
            } else {
                float_to_fixed_frac(val->fval, fmt_word, val);
                v = val->lo;
            }
            switch (lw) {
            case 2:
                mask = 0xff;
                break;
            case 3:
                mask = 0xfff;
                break;
            case 4:
                mask = 0xffff;
                break;
            case 5:
                mask = 0xfffffUL;
                break;
            default:
                mask = word_mask;
            }
            if (target_index == TGT_56600) {
                if (run_spec.mspace == MS_P)
                    mask = word_mask;
                else if (run_spec.mspace == MS_X || run_spec.mspace == MS_Y)
                    mask = 0xffff;
                else if (run_spec.mmap == 0x1e)
                    mask = 0xff;
            }
            if (!mod_sdi) {
                *dest = v & mask;
            } else {
                *mod->sdiptr++ = v & mask;
                if (two_words) {
                    *mod->sdiptr++ = val2->lo & mask;
                    mod->lh.datasize++;
                }
            }
        }
    } else {
        if (run_spec.mspace == MS_U)
            val_mult = addr_bytes;
        if ((sec_bytepack && run_ctr != load_ctr) ||
            run_spec.mspace == MS_U || load_spec.mspace == MS_U) {
            d = mod_sdi ? mod->sdiptr : dest;
            words_per_val = addr_bytes;
            v = M32(val->lo);
            for (i = 0; i < words_per_val; i++) {
                if (!sec_bytepack || run_ctr == load_ctr)
                    sh = words_per_val - i - 1;
                else
                    sh = i;
                *d++ = (v >> ((unsigned)(sh << 3) & 0x1f)) & 0xff;
                if (mod_sdi)
                    mod->sdiptr++;
            }
        }
    }
}

/* ==== 41839c ==== */
static void parse_sdi_expression(MODULE *mod, long relidx)
{
    RELENT *rel;
    int is2;
    char *p, *q, *dst;
    unsigned long n;
    long a, b, c, d, f;
    EXPR *e;
    char ch;
    unsigned long base;

    rel = mod->reloc + relidx;
    input_cursor = mod->strtab + rel->r_symndx;
    if (strncmp(input_cursor, "@SDI", 4) != 0)
        lnk_fatal1("Invalid @SDI expression");
    p = input_cursor + 4;
    is2 = 0;
    if (*p == '(') {
        input_cursor += 5;
    } else if (*p == '2') {
        input_cursor += 6;
        is2 = 1;
    } else {
        input_cursor = p;
        lnk_fatal1("Invalid @SDI expression");
    }
    p = input_cursor;
    q = input_cursor;
    if (!isalpha((unsigned char)*input_cursor)) {
        q = strchr(p, '@');
        if (q == NULL)
            lnk_fatal1("Invalid @SDI expression");
        q = strchr(q, ')');
        if (q == NULL)
            lnk_fatal1("Invalid @SDI expression");
    }
    p = strchr(q, ',');
    if (p == NULL)
        lnk_fatal1("Invalid @SDI expression");
    n = (unsigned long)(p - input_cursor);
    dst = (char *)xmalloc(n + 1);
    strncpy(dst, input_cursor, (size_t)n);
    dst[n] = '\0';
    input_cursor = p + 1;
    if (*p != ',')
        lnk_fatal1("Invalid @SDI expression");
    a = 0;
    e = eval_expr();
    if (e != NULL)
        a = sx32(e->lo);
    ch = *input_cursor++;
    if (ch != ',')
        lnk_fatal1("Invalid @SDI expression");
    b = 0;
    e = eval_expr();
    if (e != NULL)
        b = sx32(e->lo);
    ch = *input_cursor++;
    if (ch != ',')
        lnk_fatal1("Invalid @SDI expression");
    c = 0;
    e = eval_expr();
    if (e != NULL)
        c = sx32(e->lo);
    ch = *input_cursor++;
    if (ch != ',')
        lnk_fatal1("Invalid @SDI expression");
    d = 0;
    e = eval_expr();
    if (e != NULL)
        d = sx32(e->lo);
    f = 0;
    if (is2) {
        ch = *input_cursor++;
        if (ch != ',')
            lnk_fatal1("Invalid @SDI expression");
        e = eval_expr();
        if (e != NULL)
            f = sx32(e->lo);
    }
    base = ctr_before;
    if (run_ctr != load_ctr)
        base = (unsigned long)ovl_offset;
    sdi_add(M32(base + ((unsigned long)rel->r_vaddr - (unsigned long)cur_sectref2->hdr->s_paddr)),
            M32((unsigned long)rel->r_vaddr), dst, b, c, (unsigned long)a, d, f);
    cur_alloc->sdi->mod_count++;
}

/* ==== 41874a ==== */
static void track_section_nesting(SYMSLOT *ent)
{
    SECNEST *n;
    int isold;

    isold = OBJ_OLD();
    if ((isold ? ent->s.n_mem : ent->s.n_value) == 0) {
        if (sec_nest == NULL)
            lnk_fatal1("Section nesting error");
        n = sec_nest;
        sec_nest = sec_nest->next;
        xfree(n);
    } else {
        n = (SECNEST *)xmalloc((unsigned long)sizeof(SECNEST));
        n->id = isold ? ent->s.n_value : ent[1].a.x[0];
        n->next = sec_nest;
        sec_nest = n;
    }
}

/* ==== 41882a ==== */
static void output_symbol(SYMSLOT *ent, MODULE *mod)
{
    SYMSLOT *aux1, *aux2, *aux3, *aux4;
    SYMSLOT laux1, laux2, laux3;
    SECTREF *sr;
    MODSEC *ms;
    SECTION *rs;
    SDISTAT *st, *ost;
    long sp, sc, len;
    int is_sec, is_cmt, isold, hs;
    char *p;

    aux1 = ent + 1;
    aux2 = ent + 2;
    aux3 = ent + 3;
    aux4 = ent + 4;
    sr = NULL;
    rs = NULL;
    sc = ent->s.n_sclass;
    if (!(opt_i ||
          (ent->s.n_scnum != 0 &&
           (opt_g || (sc != C_SECT && sc != A_SECT && sc != A_MACRO && sc != A_ULOCAL &&
                      sc != A_MLOCAL)))))
        return;
    isold = OBJ_OLD();
    if (ent->s.n_scnum > 0)
        sr = mod_sectref + (ent->s.n_scnum - 1);
    if (ent->s.n_sclass == C_FILE || ent->s.n_sclass == A_FILE) {
        if (!opt_i)
            ent->s.n_type = 0;
        if (aux1->a.x[4] != 0)
            aux1->a.x[4] = obj_add_string(mod->strtab + aux1->a.x[4]);
    }
    if (isold) {
        if (ent->s.n_sclass == C_EXT) {
            if (!cc_objects)
                ent->s.n_sclass = A_GLOBAL;
        } else if (ent->s.n_sclass == C_LABEL) {
            ent->s.n_sclass = A_SLOCAL;
        } else if (ent->s.n_sclass == C_HIDDEN) {
            ent->s.n_sclass = A_XDEF;
        }
    }
    if (ent->s.n_sclass == C_SECT) {
        ent->s.n_sclass = A_SECT;
        if (ent->s.n_mem == 0)
            ent->s.n_value = 0;
        else
            ent->s.n_value = obj_add_string(cur_section->node->sname->name);
        ent->s.n_mem = 0;
        ent->s.n_numaux = 1;
        memset(&laux1, 0, sizeof(laux1));
        aux1 = &laux1;
        laux1.a.x[0] = cur_section->node->sname->num;
        laux1.a.x[1] = 0;
    } else if (ent->s.n_sclass == A_SECT) {
        if (ent->s.n_value != 0)
            ent->s.n_value = obj_add_string(mod->strtab + ent->s.n_value);
        aux1->a.x[0] = cur_section->node->sname->num;
    }
    is_sec = ent->s.n_sclass == C_STAT && ent->s.n_type == 0;
    if (is_sec) {
        if (!opt_g)
            aux1->a.x[2] = 0;
        if (!opt_i) {
            if (sr == NULL)
                lnk_fatal1("No current counter map");
            memset(ent->s.n_name, 0, 8);
            if ((sr->hdr->s_flags & STYP_PAD) == 0 && (sr->hdr->s_flags & STYP_BSS) == 0)
                p = (load_spec.mspace == MS_P) ? ".txt" : ".dat";
            else
                p = ".bss";
            strcpy(ent->s.n_name, p);
            ent->s.n_numaux = 1;
            aux1->a.x[1] = 0;
            sr->hdr->s_pmem = load_spec.mmap;
            ent->s.n_mem = load_spec.mmap;
            if ((sr->hdr->s_flags & STYP_BLOCK) == 0)
                sr->hdr->s_vmem = load_spec.mmap;
            if ((sr->hdr->s_flags & STYP_PAD) != 0 && (cur_rsection->flags & SF_ALIGNED) != 0) {
                sr->hdr->s_vmem = 4;
                sr->hdr->s_pmem = 4;
                sr->hdr->s_vaddr = 0;
                sr->hdr->s_paddr = 0;
                sr->hdr->s_size = 0;
            }
        } else {
            if (cur_rmsec == NULL)
                lnk_fatal1("Current relocation map not available");
            ADDL(ent->s.n_value, cur_rmsec->base);
            aux2->a.x[0] = sec_swapped ? cur_section->run->node->sname->num
                                       : cur_section->node->sname->num;
            aux2->a.x[1] = sec_swapped ? cur_section->node->sname->num
                                       : cur_section->run->node->sname->num;
            if (isold) {
                memset(&laux2, 0, sizeof(laux2));
                memset(&laux3, 0, sizeof(laux3));
                laux2.a.x[0] = aux2->a.x[0];
                laux2.a.x[1] = aux2->a.x[1];
                laux2.a.x[2] = aux2->a.x[3];
                laux2.a.x[3] = mem_bits_space(aux2->a.x[2] & 0xf);
                laux2.a.x[4] = mem_bits_map(laux2.a.x[3], aux2->a.x[2] & 0xf700);
                laux2.a.x[5] = mem_bits_counter(aux2->a.x[2] & 0x30);
                if (buf_size == 0) {
                    if (ovl_mem.mspace != 4) {
                        laux2.a.x[2] |= (long)(mod_ovltab[cur_overlay].sec->flags & SF_OVLNEW);
                        laux3.a.x[0] = ovl_mem.mspace;
                        laux3.a.x[1] = ovl_mem.mmap;
                        laux3.a.x[2] = ovl_mem.mcntr;
                        laux3.a.x[3] = ovl_mem.mclass;
                        laux3.a.x[4] = num_overlays;
                        if (aux2->a.x[6] < 0)
                            laux3.a.x[5] = aux2->a.x[6];
                        else
                            laux3.a.x[5] = obj_add_string(mod->strtab + aux2->a.x[6]);
                        ent->s.n_numaux = 3;
                    }
                } else {
                    laux3.a.x[0] = num_buffers;
                    laux3.a.x[1] = aux2->a.x[5];
                    laux3.a.x[2] = aux2->a.x[6];
                    ent->s.n_numaux = 3;
                }
            } else {
                if (buf_size != 0)
                    aux3->a.x[0] = num_buffers;
                if (buf_size == 0 && ovl_mem.mspace != 4) {
                    aux2->a.x[2] |= (long)(mod_ovltab[cur_overlay].sec->flags & SF_OVLNEW);
                    aux3->a.x[4] = num_overlays;
                    if (aux3->a.x[5] >= 0)
                        aux3->a.x[5] = obj_add_string(mod->strtab + aux3->a.x[5]);
                }
                if (buf_size != 0 && ovl_mem.mspace != 4) {
                    aux2->a.x[2] |= (long)(mod_ovltab[cur_overlay].sec->flags & SF_OVLNEW);
                    aux4->a.x[4] = num_overlays;
                    if (aux4->a.x[5] >= 0)
                        aux4->a.x[5] = obj_add_string(mod->strtab + aux4->a.x[5]);
                }
            }
        }
    }
    if ((ent->s.n_type & 0x30) == 0x20 && ent->s.n_scnum > 0 && mod->lines != NULL)
        aux1->a.x[3] = (long)M32(M32(obj_lnnoptr - obj_lnnoptr0) / 12 +
                                 (unsigned long)aux1->a.x[3]);
    if (long_name(ent->s.n_name)) {
        if (!is_sec || sr == NULL)
            set_name_off(ent->s.n_name,
                         (unsigned long)obj_add_string(mod->strtab + name_off(ent->s.n_name)));
        else
            set_name_off(ent->s.n_name, name_off(sr->hdr->s_name));
    }
    is_cmt = ent->s.n_sclass == C_NULL && ent->s.n_type == 0 && !long_name(ent->s.n_name) &&
             strncmp(ent->s.n_name, ".cmt", 8) == 0;
    if (is_cmt)
        ent->s.n_value = obj_add_string(mod->strtab + ent->s.n_value);
    if (ent->s.n_sclass == A_MACRO && ent->s.n_value != 0)
        ent->s.n_value = obj_add_string(mod->strtab + ent->s.n_value);
    if (ent->s.n_sclass == C_SDI) {
        if (!opt_i)
            return;
        out_nsdi++;
        ADDL(ent->s.n_value, reloc_base);
    }
    if (ent->s.n_scnum > 0) {
        sp = map_to_space(ent->s.n_mem);
        if (sp == 4 || sp == run_spec.mspace || ovl_mem.mspace != 4) {
            ms = cur_rmsec;
            rs = cur_rsection;
        } else {
            for (ms = mod_secmap[cur_rsecno]; ms != NULL; ms = ms->next)
                if (ms->sec->node->spec.mspace == sp && ms->sec->node->spec.mcntr == run_spec.mcntr)
                    break;
            if (ms == NULL)
                lnk_fatal1("Symbol map lookup failure");
            else
                rs = ms->sec;
        }
        if (rs == NULL)
            lnk_fatal1("Current relocation section not available");
        if (ms == NULL)
            lnk_fatal1("Current relocation map not available");
        ent->s.n_scnum = obj_nscns;
        st = cur_alloc->sdi;
        hs = mod_sdi && st != NULL && st->n_saved != 0;
        if (opt_i && load_reloc && !is_cmt && !is_sec && sp != 4 && ovl_mem.mspace == 4)
            ADDL(ent->s.n_value, ms->base);
        if (!opt_i && !is_cmt && !is_sec && run_reloc && sp != 4 && ovl_mem.mspace != 4) {
            ADDL(ent->s.n_value, mod_ovltab[cur_overlay].grp->lo);
            if (hs && st->recs != NULL && (st->mod_first != 0 || st->mod_count != 0) &&
                sp == MS_P && run_reloc && ent->s.n_scnum > 0)
                ADDL(ent->s.n_value, st->recs[st->mod_first - 1 + st->mod_count].growth);
        }
        if (!opt_i && !is_cmt && load_reloc && sp != 4 && (ovl_mem.mspace == 4 || is_sec)) {
            ADDL(ent->s.n_value, rs->lo);
            if ((rs->flags & SF_ALIGNED) == 0) {
                ADDL(ent->s.n_value, ms->base);
            } else if ((rs->flags & SF_BUF) == 0) {
                ADDL(ent->s.n_value, ms->base_raw - rs->node->bufsz);
                if (is_sec && (sr->hdr->s_flags & STYP_PAD) != 0) {
                    ent->s.n_mem = 4;
                    ent->s.n_value = 0;
                }
            } else {
                SUBL(ent->s.n_value, mod_buftab[cur_buffer].addr);
            }
            if (hs && st->recs != NULL && (st->mod_first != 0 || st->mod_count != 0) &&
                sp == MS_P && run_reloc && ent->s.n_scnum > 0 && (rs->flags & SF_BUF) == 0)
                ADDL(ent->s.n_value, st->recs[st->mod_first - 1 + st->mod_count].growth);
            if (rs->node->ovl_last != NULL && (ost = rs->node->ovl_last->sdi) != NULL &&
                ost->n_saved != 0 && ost->recs != NULL)
                ADDL(ent->s.n_value, ost->recs[ost->n_saved - 1].growth);
        }
    }
    obj_add_syment(ent);
    if (ent->s.n_numaux > 0)
        obj_add_syment(aux1);
    if (ent->s.n_numaux > 1)
        obj_add_syment(isold ? &laux2 : aux2);
    if (ent->s.n_numaux > 2)
        obj_add_syment(isold ? &laux3 : aux3);
    if (ent->s.n_numaux > 3)
        obj_add_syment(aux4);
    if (ent->s.n_sclass == C_FILE || ent->s.n_sclass == A_FILE) {
        if (first_ident && (first_ident = 0, ident_name != NULL) && ident_name != ident_none) {
            strcpy(namebuf, ident_name);
            len = (long)strlen(namebuf);
            namebuf[len] = ' ';
            p = namebuf + len + 1;
            sprintf(p, "%04lX %04lX %04lX ", M32(ident_ver), M32(ident_rev), M32(error_count));
            p += strlen(p);
            sprintf(p, "%s %s", target_name, opt_t ? "XXXX" : lnk_version);
            if (ident_comment != NULL) {
                p += strlen(p);
                if (strlen(ident_comment) > 0x48)
                    ident_comment[0x48] = '\0';
                sprintf(p, " %s", ident_comment);
            }
            obj_add_comment(namebuf, -1L);
        }
        obj_add_file_secsyms();
    }
}

/* ==== 41976c ==== */
static void track_address_range(long nwords)
{
    unsigned long start, end, lim;
    long lspace, lmap, lcntr, lclass;

    lclass = load_spec.mclass;
    lcntr = load_spec.mcntr;
    lmap = load_spec.mmap;
    lspace = load_spec.mspace;
    start = *load_ctr;
    lim = space_mask(load_spec.mspace);
    end = M32(start + (unsigned long)nwords);
    if (load_spec.mspace == MS_P) {
        if (obj_fext_cur != NULL) {
            if (obj_fext_cur->text_hi == 0 || start < obj_fext_cur->text_lo) {
                obj_fext_cur->text_lo = start;
                obj_fext_cur->text_mem.mspace = 0;
                obj_fext_cur->text_mem.mmap = lmap;
                obj_fext_cur->text_mem.mcntr = lcntr;
                obj_fext_cur->text_mem.mclass = lclass;
            }
            if (obj_fext_cur->text_hi < end)
                obj_fext_cur->text_hi = end;
        }
        if (first_p || start < text_lo) {
            text_lo_mem = lmap;
            first_p = 0;
            text_lo = start;
        }
        if (text_hi < end) {
            text_hi = (lim < end) ? lim : end;
            text_hi_mem = lmap;
        }
    } else {
        if (obj_fext_cur != NULL) {
            if (obj_fext_cur->data_hi == 0 || start < obj_fext_cur->data_lo) {
                obj_fext_cur->data_lo = start;
                obj_fext_cur->data_mem.mspace = lspace;
                obj_fext_cur->data_mem.mmap = lmap;
                obj_fext_cur->data_mem.mcntr = lcntr;
                obj_fext_cur->data_mem.mclass = lclass;
            }
            if (obj_fext_cur->data_hi < end)
                obj_fext_cur->data_hi = end;
        }
        if (!xy_seen) {
            data_lo_mem = lmap;
            xy_seen = 1;
            data_lo = start;
        } else if (start < data_lo) {
            data_lo_mem = lmap;
            data_lo = start;
        }
        if (data_hi < end) {
            if (lim < end)
                end = lim;
            data_hi = end;
            data_hi_mem = lmap;
        }
    }
}

/* ==== 41999e ==== */
static void select_counters(unsigned long flags, MEMSPEC *spec, long addr)
{
    unsigned long rflags;
    SECTION *s, *b;
    SDISTAT *st;
    unsigned long a;

    a = M32((unsigned long)addr);
    b = NULL;
    if ((flags & SA_RELOC) == 0)
        s = find_section_record(flags, a);
    else
        s = cur_section->run;
    cur_alloc = s;
    cur_rsection = s;
    if ((flags & SA_OVERLAY) != 0) {
        cur_alloc = get_overlay_record();
        s = cur_alloc;
    }
    if ((flags & SA_BUFFER) != 0) {
        b = find_buffer_record(flags, a);
        if ((flags & SA_RELOC) != 0 && (flags & SA_20000) != 0) {
            s = b;
            cur_rsection = s;
        }
    }
    if (s == NULL && b == NULL)
        lnk_fatal1("Invalid data block type");
    rflags = cur_rsection->flags;
    if ((flags & SA_OVERLAY) == 0) {
        run_spec.mspace = spec->mspace;
        load_spec.mmap = spec->mmap;
        run_spec.mcntr = spec->mcntr;
        run_spec.mclass = spec->mclass;
        if (spec->mspace == spec->mmap && spec->mspace != MS_E) {
            if ((cur_rsection->node->flags & SN_REMAP) == 0) {
                if (cur_memreg != NULL && (cur_memreg->flags & MR_REMAP) != 0)
                    load_spec.mmap = cur_memreg->spec.mmap;
            } else {
                load_spec.mmap = cur_rsection->node->spec.mmap;
            }
        }
        run_ctr = &cur_rsection->hi;
        run_spec.mmap = load_spec.mmap;
        load_spec.mspace = run_spec.mspace;
        load_spec.mcntr = run_spec.mcntr;
        load_spec.mclass = run_spec.mclass;
        load_ctr = run_ctr;
        if ((rflags & SF_REL) == 0) {
            if (cur_rsection->hi != a) {
                cur_rsection->lo = a;
                *run_ctr = a;
            }
        } else if ((rflags & SF_ALIGNED) == 0) {
            *run_ctr = M32(a + cur_rmsec->base);
            if (pass == 2 && !opt_i)
                *run_ctr = M32(*run_ctr + cur_rsection->lo);
        } else if ((rflags & SF_BUF) == 0) {
            *run_ctr = M32(a + cur_rmsec->base_raw - cur_rsection->node->bufsz_al);
            if (pass == 2 && !opt_i)
                *run_ctr = M32(*run_ctr + cur_rsection->lo);
        }
        if (pass == 2 && (rflags & SF_REL) != 0 && (rflags & SF_BUF) == 0) {
            *load_ctr = M32(*load_ctr + cur_rsection->node->sdigrow);
            if (mod_sdi && cur_alloc->sdi != NULL) {
                st = cur_alloc->sdi;
                if (st->n != 0)
                    *run_ctr = M32(*run_ctr + (unsigned long)st->recs[st->n - 1].growth);
            }
        }
    } else {
        load_spec.mspace = spec->mspace;
        load_spec.mmap = spec->mmap;
        load_spec.mcntr = spec->mcntr;
        load_spec.mclass = spec->mclass;
        run_spec.mspace = ovl_mem.mspace;
        run_spec.mmap = ovl_mem.mmap;
        run_spec.mcntr = ovl_mem.mcntr;
        run_spec.mclass = ovl_mem.mclass;
        if (target_index == TGT_56600) {
            if (ovl_mem.mspace == MS_P) {
                if (load_spec.mspace == MS_X || load_spec.mspace == MS_Y)
                    load_spec.mclass = 0x42;
                if (load_spec.mmap == 0x1e)
                    load_spec.mclass = 0x62;
            }
            if ((ovl_mem.mspace == MS_X || ovl_mem.mspace == MS_Y) && load_spec.mmap == 0x1e)
                load_spec.mclass = 0x21;
        }
        if (spec->mspace == spec->mmap && spec->mspace != MS_E) {
            if ((cur_rsection->node->flags & SN_REMAP) == 0) {
                if (cur_memreg != NULL && (cur_memreg->flags & MR_REMAP) != 0)
                    load_spec.mmap = cur_memreg->spec.mmap;
            } else {
                load_spec.mmap = cur_rsection->node->spec.mmap;
            }
        }
        run_ctr = &s->hi;
        load_ctr = &cur_rsection->hi;
        if ((rflags & SF_REL) == 0) {
            if (cur_rsection->hi != a) {
                cur_rsection->lo = a;
                *load_ctr = a;
            }
        } else {
            *load_ctr = M32(a + (load_aligned ? cur_rmsec->base : cur_rmsec->base_raw));
            if (pass == 2 && !opt_i) {
                *load_ctr = M32(*load_ctr + cur_rsection->lo);
                if ((rflags & SF_BUF) == 0)
                    *load_ctr = M32(*load_ctr + cur_rsection->node->sdigrow);
            }
        }
    }
}

/* ==== 419ece ==== */
SECTION *find_section_record(unsigned long flags, unsigned long addr)
{
    SECTION *p, *prev;

    p = cur_section->node->abss;
    prev = NULL;
    for (; p != NULL; prev = p, p = p->next)
        if ((p->state & SS_ACTIVE) == 0 || p->hi == addr)
            break;
    if (p == NULL) {
        if (pass == 2)
            lnk_fatal1("Cannot find section record");
        p = sec_alloc(cur_section->node, 0UL);
        p->index = 0;
        p->flags = flags & 0xfffd9fffUL;
        p->run = cur_section;
        if (prev == NULL) {
            p->next = p->node->abss;
            p->node->abss = p;
        } else {
            p->next = prev->next;
            prev->next = p;
        }
        p->node->nabss++;
        num_secs++;
    }
    p->state |= SS_ACTIVE;
    return p;
}

/* ==== 419ff9 ==== */
SECTION *find_buffer_record(unsigned long flags, unsigned long addr)
{
    SECTION *p, *prev;
    SECNODE *node;
    unsigned long mask;
    int found;

    found = 0;
    if (!run_reloc)
        flags &= ~SF_REL;
    else
        flags |= SF_REL;
    if (mod_buftab[cur_buffer].sec == NULL) {
        prev = NULL;
        for (p = cur_rsection->node->bufs; p != NULL; p = p->next) {
            if ((flags & SF_MATCH) == (p->flags & SF_MATCH) &&
                ((p->state & SS_ACTIVE) == 0 || ((p->flags & SF_REL) == 0 && p->hi == addr))) {
                found = 1;
                break;
            }
            prev = p;
        }
        if (!found) {
            if (pass == 2)
                lnk_fatal1("Cannot find section record");
            if ((flags & SF_OVL) == 0)
                node = cur_rsection->node;
            else
                node = mod_ovltab[cur_overlay].sec->node;
            p = sec_alloc(node, SF_BUF);
            p->index = buf_seq;
            p->flags = flags;
            p->lo = 0;
            p->align = buf_size;
            p->hi = buf_size;
            p->bufaddr = addr;
            p->bufspan = M32((unsigned long)buf_pending + buf_size);
            p->run = cur_rsection;
            if (prev == NULL) {
                p->next = p->node->bufs;
                p->node->bufs = p;
            } else {
                p->next = prev->next;
                prev->next = p;
            }
            p->node->nbufs++;
            num_secs++;
        }
        buf_pending = 0;
        p->state |= buf_type | SS_ACTIVE;
        mod_buftab[cur_buffer].sec = p;
        mod_buftab[cur_buffer].addr = addr;
        if (run_reloc && pass == 1) {
            mask = (p->node->spec.mmap == 0x1e) ? ext_addr_mask : addr_mask;
            cur_rmsec->base = buf_align(cur_rmsec->base, buf_size, mask);
            cur_rsection->node->bufsz_al = M32(cur_rsection->node->bufsz +
                                               (cur_rmsec->base - cur_rmsec->base_raw));
            if (cur_rsection->align < buf_size)
                cur_rsection->align = buf_size;
        }
    } else {
        p = mod_buftab[cur_buffer].sec;
        if (buf_new) {
            if ((flags & SF_REL) == 0 || (flags & SF_ALIGNED) == 0) {
                if ((flags & SF_OVL) == 0) {
                    p->lo = addr;
                    if (run_reloc)
                        p->lo = M32(p->lo + cur_rsection->lo + cur_rmsec->base);
                } else {
                    p->lo = mod_ovltab[cur_overlay].sec->hi;
                }
                p->hi = M32(p->lo + buf_size);
            }
        }
        buf_pending = 0;
        if (run_reloc && pass == 2 && (cur_rsection->flags & SF_ALIGNED) == 0) {
            mask = (p->node->spec.mmap == 0x1e) ? ext_addr_mask : addr_mask;
            cur_rmsec->base2 = buf_align(cur_rmsec->base2, buf_size, mask);
        }
        if ((flags & SF_REL) == 0 || (flags & SF_ALIGNED) == 0)
            p = cur_rsection;
    }
    return p;
}

/* ==== 41a425 ==== */
SECTION *get_overlay_record(void)
{
    SECTION *s, *p;
    SECNODE *node;
    long idx;

    if (ovl_force == 0 && mod_ovltab[cur_overlay].sec == NULL) {
        s = sec_lookup_create(cur_rsection->node->sname->name, cur_rsection->node->sname->num,
                              &ovl_mem, 0);
        node = s->node;
        p = sec_alloc(node, SF_OVL);
        p->index = num_overlays;
        p->flags = run_reloc ? (SF_OVL | SF_REL) : SF_OVL;
        p->ovl = &mod_ovltab[cur_overlay];
        p->run = cur_rsection;
        p->next = node->ovls;
        node->ovls = p;
        node->novls++;
        num_secs++;
        if (cur_infile->module != node->ovl_stamp) {
            node->ovl_stamp = cur_infile->module;
            p->flags |= SF_OVLNEW;
        }
        if (run_reloc)
            cur_rsection->node->ovl_last = p;
        mod_ovltab[cur_overlay].grp = p;
        mod_ovltab[cur_overlay].sec = p;
    } else {
        idx = (ovl_force == 0) ? cur_overlay : ovl_force;
        p = mod_ovltab[idx].sec;
        run_reloc = (p->flags & SF_REL) != 0;
        ovl_force = 0;
    }
    return p;
}

/* ==== 41a5e0 ==== */
static void alloc_module_tables(MODULE *mod)
{
    long i;

    mod->secmap = (MODSEC **)xmalloc((unsigned long)mod->lh.secnt * (unsigned long)sizeof(MODSEC *));
    mod_secmap = mod->secmap;
    for (i = 0; i < mod->lh.secnt; i++)
        mod_secmap[i] = NULL;
    mod->sectref = (SECTREF *)xmalloc((unsigned long)mod->lh.ctrcnt * (unsigned long)sizeof(SECTREF));
    mod_sectref = mod->sectref;
    for (i = 0; i < mod->lh.ctrcnt; i++) {
        mod_sectref[i].hdr = NULL;
        mod_sectref[i].sym = NULL;
    }
    mod->buftab = (BUFREF *)xmalloc((unsigned long)(mod->lh.bufcnt + 1) * (unsigned long)sizeof(BUFREF));
    mod_buftab = mod->buftab;
    for (i = 0; i <= mod->lh.bufcnt; i++) {
        mod_buftab[i].sec = NULL;
        mod_buftab[i].addr = 0;
    }
    cur_buffer = 0;
    mod->ovltab = (OVLENT *)xmalloc((unsigned long)(mod->lh.ovlcnt + 1) * (unsigned long)sizeof(OVLENT));
    mod_ovltab = mod->ovltab;
    for (i = 0; i <= mod->lh.ovlcnt; i++) {
        mod_ovltab[i].module = NULL;
        mod_ovltab[i].grp = NULL;
        mod_ovltab[i].rsec = NULL;
        mod_ovltab[i].lsec = NULL;
        mod_ovltab[i].sec = NULL;
        mod_ovltab[i].maxbuf = 0;
        mod_ovltab[i].sdioff = 0;
        mod_ovltab[i].marker = NULL;
        mod_ovltab[i].baseexpr = NULL;
    }
    cur_overlay = 0;
}

/* ==== 41a815 ==== */
static FILE *open_input_stream(char *name)
{
    FILE *fp;
    STRNODE *n;
    char buf[2 * NAMEBUF_SIZE];     /* original: 512 bytes, unchecked */

    fp = fopen(name, "rb");
    if (fp == NULL) {
        for (n = libpath_head; n != NULL; n = n->next) {
            strcpy(buf, n->str);
            strcat(buf, name);
            fp = fopen(buf, "rb");
            if (fp != NULL)
                return fp;
            fp = NULL;
        }
    }
    return fp;
}

/* ==== 41a8c0: fstat st_size in the original ==== */
static long file_size(FILE *fp)
{
    long pos, size;

    pos = ftell(fp);
    if (pos < 0 || fseek(fp, 0L, SEEK_END) != 0)
        return -1;
    size = ftell(fp);
    if (fseek(fp, pos, SEEK_SET) != 0)
        return -1;
    return size;
}

/* ==== 41a8ef ==== */
static SCNHDR *read_section_headers(unsigned long n)
{
    SCNHDR *s;

    s = (SCNHDR *)xmalloc(n * (unsigned long)sizeof(SCNHDR));
    if (read_scnhdrs(s, n, in_fp) != n)
        lnk_fatal1("Cannot read object module section headers");
    return s;
}

/* ==== 41a937 ==== */
SYMSLOT *read_symbol_entries(unsigned long n)
{
    SYMSLOT *s;

    s = (SYMSLOT *)xmalloc(n * (unsigned long)sizeof(SYMSLOT));
    if (read_symslots(s, n, in_fp) != n)
        lnk_fatal1("Cannot read object module symbol entries");
    return s;
}

/* ==== 41a97f ====
   The buffer holds the 4-byte length word followed by the strings, so
   string table offsets index it directly.  The original keeps the length
   in host order; the port stores it big-endian (nobody reads it). */
char *read_string_table(void)
{
    unsigned char b[4];
    unsigned long len;
    char *buf;

    len = 0;
    if (fread(b, 1, 4, in_fp) != 4) {
        if (feof(in_fp) || len == 0)
            return NULL;
        lnk_fatal1("Cannot read module string table size");
    }
    len = get_be32(b);
    if (len < 4)
        lnk_fatal1("Cannot read object module string table");
    buf = (char *)xmalloc(len);
    if (fread(buf + 4, 1, (size_t)(len - 4), in_fp) != (size_t)(len - 4))
        lnk_fatal1("Cannot read object module string table");
    put_be32((unsigned char *)buf, len);
    return buf;
}
