/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), object.c
 * Original module: $Id: object.c,v 1.32 1997/02/21 19:40:51 lauren Exp $
 * Reconstructed from DSPLNK.EXE 00427710-00429a31: writing the linked COFF
 * output (absolute .cld or incremental .cln): headers, section headers, raw
 * data, relocations, line numbers, symbol table and string table.  All
 * records are written big-endian through the util.c codecs; the name word
 * swaps of the original (swap_words(name,4,2)) are kept as name_swap().
 */
#include "dsplnk.h"

static unsigned long obj_scnptr;    /* 461e9c next section header offset */
static unsigned long obj_rawptr0;   /* 461ea0 */
static unsigned long obj_rawptr;    /* 461ea4 next raw data offset */
static unsigned long obj_relptr0;   /* 461eac */
static unsigned long obj_relptr;    /* 461eb0 */
static LINENO *obj_lnnobuf;         /* 461ecc buffered line numbers */
static long obj_nlnnobuf;           /* 461ed0 */
static unsigned long obj_symptr;    /* 461ed4 */
static long obj_nsyms;              /* 461ed8 */
static SYMSLOT *obj_syms;           /* 461edc */
static long obj_symcap;             /* 461ee0 */
static unsigned long obj_strptr;    /* 461ee4 */
static char *obj_strtab;            /* 461ee8 */
static long obj_strcap;             /* 461eec */
static FILHDR obj_fhdr;             /* 46c120 */
static AOUTHDR obj_aouthdr;         /* 46c2a0 */

static void obj_write_headers(void);
static void obj_write_textdata_hdrs(void);
static void obj_write_linenos(void);
static void obj_write_symtab(void);
static void obj_build_symtab(void);
static void obj_reorder_symtab(void);
static void obj_link_symbol_tags(long lo, long tlo, long hi, long thi,
                                 SYMSLOT *src, SYMSLOT *dst);
static void obj_patch_symtab_links(void);
static void obj_add_end_syms(void);
static void obj_write_strtab(void);
static void obj_write_set_syms(void);

#define IS_TAG(sc)   ((sc) == C_STRTAG || (sc) == C_UNTAG || (sc) == C_ENTAG)
#define IS_FUNC(t)   (((t) & 0x30L) == 0x20L)

/* storage classes treated as "global" (C_HIDDEN only for objects < 4.2) */
static int is_global_class(long sc)
{
    if (sc == C_EXT || sc == A_GLOBAL || sc == A_XDEF)
        return 1;
    return OBJ_OLD() && sc == C_HIDDEN;
}

/* +1 for ".bf"/".bb", -1 for ".ef"/".eb" */
static long block_step(SYMSLOT *e)
{
    return e->s.n_name[1] == 'b' ? 1L : -1L;
}

static int name_inline(SYMSLOT *e)
{
    return e->s.n_name[0] != 0 || e->s.n_name[1] != 0 ||
           e->s.n_name[2] != 0 || e->s.n_name[3] != 0;
}

/* 00427710: start of pass 2 - file offsets from the pass-1 totals */
void obj_layout_offsets(void)
{
    long n;

    n = obj_nscns;
    if (!opt_i) {
        obj_nscns = 2;
        obj_scnptr = OBJ_SCN0_ABS;
        obj_rawptr = M32((unsigned long)(n - 2) * OBJ_SCNSZ + OBJ_SCN0_ABS);
    } else {
        obj_nscns = 0;
        obj_scnptr = OBJ_SCN0_INC;
        obj_rawptr = M32((unsigned long)n * OBJ_SCNSZ + OBJ_SCN0_INC);
    }
    obj_relptr0 = M32(obj_rawptr + (obj_nwords + (unsigned long)sdi_total) * 4);
    obj_lnnoptr0 = M32(obj_relptr0 + (opt_i ? obj_nreloc * OBJ_RELSZ : 0));
    obj_symptr = M32(obj_lnnoptr0 + (opt_g ? obj_nlnno * OBJ_LNNOSZ : 0));
    obj_rawptr0 = obj_rawptr;
    obj_relptr = obj_relptr0;
    obj_lnnoptr = obj_lnnoptr0;
    if (obj_fp != NULL) {
        if (fseek(obj_fp, (long)obj_rawptr, SEEK_SET) != 0)
            lnk_fatal1("Cannot seek to start of object data");
    }
}

/* 0042785f: finish the object file */
void obj_write_file(void)
{
    EXPR *e;

    if (obj_fp == NULL)
        return;
    if (!opt_i) {
        obj_write_textdata_hdrs();
        if (num_set_syms != 0)
            obj_write_set_syms();
    }
    obj_write_symtab();
    if (opt_g)
        obj_write_linenos();
    if (start_name == NULL) {
        if (opt_i)
            obj_lnkhdr.endstr = -1;
    } else {
        input_cursor = start_name;
        e = eval_int();
        if (e != NULL) {
            start_addr = expr_as_int32(e);
            start_mem = e->space;
            free_expr(e);
        }
        if (opt_i)
            obj_lnkhdr.endstr = obj_add_string(start_name);
        xfree(start_name);          /* the original leaves start_name dangling */
    }
    obj_write_strtab();
    obj_write_headers();
}

/* 00427941: file header and optional (abs) or linker (incremental) header */
static void obj_write_headers(void)
{
    long minv;

    if (fseek(obj_fp, 0L, SEEK_SET) != 0)
        lnk_fatal1("Cannot seek to start of object file");
    obj_fhdr.f_magic = target_magic;
    obj_fhdr.f_nscns = obj_nscns;
    obj_fhdr.f_timdat = opt_t ? 0 : link_time;
    obj_fhdr.f_symptr = (long)obj_symptr;
    obj_fhdr.f_nsyms = obj_nsyms;
    obj_fhdr.f_opthdr = opt_i ? OBJ_LNKSZ : OBJ_AOUTSZ;
    obj_fhdr.f_flags = 0;
    if (!opt_i) {
        obj_fhdr.f_flags = F_RELFLG;
        if (error_count == 0)
            obj_fhdr.f_flags = F_RELFLG | F_EXEC;
    } else if (sdi_seen) {
        obj_fhdr.f_flags = F_SDI;
    }
    if (!opt_g)
        obj_fhdr.f_flags |= F_LNNO;
    if (opt_c)
        obj_fhdr.f_flags |= F_CC;
    if (write_filhdr(&obj_fhdr, obj_fp) != 1)
        lnk_fatal1("Cannot write file header to object file");
    if (!opt_i) {
        obj_aouthdr.magic = 0;
        obj_aouthdr.vstamp = 0;
        obj_aouthdr.tsize = (long)M32(text_hi - text_lo);
        obj_aouthdr.dsize = (long)M32(data_hi - data_lo);
        obj_aouthdr.bsize = 0;
        if (!start_given) {
            obj_aouthdr.entry = (long)text_lo;
            obj_aouthdr.entry_mem = text_lo_mem != 4 ? text_lo_mem : 0;
        } else {
            obj_aouthdr.entry = (long)start_addr;
            obj_aouthdr.entry_mem = start_mem != 4 ? start_mem : 0;
        }
        obj_aouthdr.text_start = (long)text_lo;
        obj_aouthdr.text_start_mem = text_lo_mem != 4 ? text_lo_mem : 0;
        obj_aouthdr.data_start = (long)data_lo;
        obj_aouthdr.data_start_mem = data_lo_mem == 4 ? 1 : data_lo_mem;
        obj_aouthdr.text_end = (long)text_hi;
        obj_aouthdr.text_end_mem = text_hi_mem != 4 ? text_hi_mem : 0;
        obj_aouthdr.data_end = (long)data_hi;
        obj_aouthdr.data_end_mem = data_hi_mem == 4 ? 1 : data_hi_mem;
        if (write_aouthdr(&obj_aouthdr, obj_fp) != 1)
            lnk_fatal1("Cannot write optional header to object file");
    } else {
        obj_lnkhdr.modsize = (long)M32(OBJ_SCN0_INC
                                       + (unsigned long)obj_nscns * OBJ_SCNSZ
                                       + obj_nwords * 4
                                       + obj_nreloc * OBJ_RELSZ
                                       + obj_nlnno * OBJ_LNNOSZ
                                       + (unsigned long)obj_nsyms * OBJ_SYMSZ
                                       + (unsigned long)(obj_strsize > 4 ? obj_strsize : 0));
        obj_lnkhdr.datasize = (long)obj_nwords;
        obj_lnkhdr.secnt = num_secs;
        obj_lnkhdr.ctrcnt = obj_nscns;
        obj_lnkhdr.relocnt = (long)obj_nreloc;
        obj_lnkhdr.lnocnt = (long)obj_nlnno;
        obj_lnkhdr.bufcnt = buf_seq;
        obj_lnkhdr.ovlcnt = num_overlays;
        obj_lnkhdr.majver = out_major < lnk_major ? lnk_major : out_major;
        if (lnk_major < out_major || lnk_minor <= out_minor)
            minv = out_minor;
        else
            minv = lnk_minor;
        obj_lnkhdr.minver = minv;
        obj_lnkhdr.revno = out_rev;
        obj_lnkhdr.unused = 0;
        obj_lnkhdr.sditot = obj_sditot;
        if (write_lnkhdr(&obj_lnkhdr, obj_fp) != 1)
            lnk_fatal1("Cannot write optional header to object file");
    }
}

/* 00427d54: absolute file: the ".text" and ".data" section headers */
static void obj_write_textdata_hdrs(void)
{
    SCNHDR h[2];

    memset(h, 0, sizeof h);
    strcpy(h[0].s_name, ".text");
    name_swap(h[0].s_name);
    h[0].s_paddr = (long)text_lo;
    h[0].s_pmem = text_lo_mem != 4 ? text_lo_mem : 0;
    h[0].s_vaddr = (long)text_lo;
    h[0].s_vmem = h[0].s_pmem;
    h[0].s_size = (long)M32(text_hi - text_lo);
    h[0].s_scnptr = 0;
    h[0].s_relptr = (long)obj_relptr0;
    h[0].s_lnnoptr = (long)obj_lnnoptr0;
    h[0].s_nreloc = 0;
    h[0].s_nlnno = opt_g ? (long)obj_nlnno : 0;
    h[0].s_flags = STYP_TEXT;
    strcpy(h[1].s_name, ".data");
    name_swap(h[1].s_name);
    h[1].s_paddr = (long)data_lo;
    h[1].s_pmem = data_lo_mem == 4 ? 1 : data_lo_mem;
    h[1].s_vaddr = (long)data_lo;
    h[1].s_vmem = h[1].s_pmem;
    h[1].s_size = (long)M32(data_hi - data_lo);
    h[1].s_scnptr = 0;
    h[1].s_relptr = (long)obj_relptr0;
    h[1].s_lnnoptr = 0;
    h[1].s_nreloc = 0;
    h[1].s_nlnno = 0;
    h[1].s_flags = STYP_DATA;
    if (fseek(obj_fp, (long)OBJ_TEXTDATA_OFF, SEEK_SET) != 0)
        lnk_fatal1("Cannot seek to start of section headers");
    if (write_scnhdrs(h, 2, obj_fp) != 2)
        lnk_fatal1("Cannot write .text/.data headers to object file");
}

/* 00427ebb: end of pass 2 of a module: its section headers, raw data,
   relocations (incremental only) and buffered line numbers (-g) */
void obj_write_module(MODULE *m)
{
    SCNHDR *h;
    unsigned long n;
    unsigned long cnt;
    unsigned long rcnt;             /* 16-bit counters in the original */
    unsigned long lcnt;
    int pad;
    int bss;

    cnt = 0;
    rcnt = 0;
    lcnt = 0;
    n = (unsigned long)m->fh.f_nscns;
    if (n != 0) {
        for (h = m->scnhdr; h < m->scnhdr + n; h++) {
            pad = (h->s_flags & STYP_PAD) != 0;
            bss = (h->s_flags & STYP_BSS) != 0;
            if (pad || bss) {
                h->s_scnptr = 0;
            } else {
                h->s_scnptr = (long)M32(obj_rawptr + cnt * 4);
                cnt = M32(cnt + (unsigned long)h->s_size);
            }
            if (pad || bss) {
                h->s_relptr = 0;
                h->s_nreloc = 0;
            } else if (!opt_i) {
                h->s_relptr = (long)obj_relptr;
                h->s_nreloc = 0;
            } else {
                h->s_relptr = (long)M32(obj_relptr + rcnt * OBJ_RELSZ);
                rcnt = (rcnt + ((unsigned long)h->s_nreloc & 0xffffUL)) & 0xffffUL;
            }
            if (pad) {
                h->s_lnnoptr = 0;
                h->s_nlnno = 0;
            } else if (!opt_g) {
                h->s_lnnoptr = (long)obj_lnnoptr;
                h->s_nlnno = 0;
            } else {
                h->s_lnnoptr = (long)M32(obj_lnnoptr + lcnt * OBJ_LNNOSZ);
                lcnt = (lcnt + ((unsigned long)h->s_nlnno & 0xffffUL)) & 0xffffUL;
            }
        }
        if (fseek(obj_fp, (long)obj_scnptr, SEEK_SET) != 0)
            lnk_fatal1("Cannot seek to object module section headers");
        if (write_scnhdrs(m->scnhdr, n, obj_fp) != n)
            lnk_fatal1("Cannot write section headers to object module");
        xfree(m->scnhdr);
        m->scnhdr = NULL;
        obj_scnptr = M32(obj_scnptr + n * OBJ_SCNSZ);
    }
    n = (unsigned long)m->lh.datasize;
    if (n != 0) {
        if (fseek(obj_fp, (long)obj_rawptr, SEEK_SET) != 0)
            lnk_fatal1("Cannot seek to object module raw data");
        if (write_words(mod_sdi ? m->sdibuf : m->raw, n, obj_fp) != n)
            lnk_fatal1("Cannot write raw data to object module");
        xfree(m->raw);
        m->raw = NULL;
        if (m->sdibuf != NULL) {
            xfree(m->sdibuf);
            m->sdibuf = NULL;
        }
        obj_rawptr = M32(obj_rawptr + n * 4);
    }
    n = (unsigned long)m->lh.relocnt;
    if (n != 0) {
        if (opt_i) {
            if (fseek(obj_fp, (long)obj_relptr, SEEK_SET) != 0)
                lnk_fatal1("Cannot seek to object module relocation entries");
            if (write_relents(m->reloc, n, obj_fp) != n)
                lnk_fatal1("Cannot write relocation entries to object module");
            obj_relptr = M32(obj_relptr + n * OBJ_RELSZ);
        }
        xfree(m->reloc);
        m->reloc = NULL;
    }
    n = (unsigned long)m->lh.lnocnt;
    if (n != 0) {
        if (opt_g) {
            if (obj_nlnnobuf == 0)
                obj_lnnobuf = (LINENO *)xmalloc(n * sizeof(LINENO));
            else
                obj_lnnobuf = (LINENO *)xrealloc(obj_lnnobuf,
                              ((unsigned long)obj_nlnnobuf + n) * sizeof(LINENO));
            memcpy(obj_lnnobuf + obj_nlnnobuf, m->lines, (size_t)(n * sizeof(LINENO)));
            obj_nlnnobuf += (long)n;
            obj_lnnoptr = M32(obj_lnnoptr + n * OBJ_LNNOSZ);
        }
        xfree(m->lines);
        m->lines = NULL;
    }
}

/* 004282de: the buffered line numbers (obj_nlnno entries, as the original) */
static void obj_write_linenos(void)
{
    if (obj_nlnno != 0) {
        if (fseek(obj_fp, (long)obj_lnnoptr0, SEEK_SET) != 0)
            lnk_fatal1("Cannot seek to start of line number entries");
        if (write_linenos(obj_lnnobuf, obj_nlnno, obj_fp) != obj_nlnno)
            lnk_fatal1("Cannot write line number entries to object file");
        xfree(obj_lnnobuf);
        obj_lnnobuf = NULL;
    }
}

/* 00428356: symbol table */
static void obj_write_symtab(void)
{
    long i;

    if (obj_nsyms == 0)
        return;
    if (!opt_i) {
        obj_build_symtab();
        obj_reorder_symtab();
        obj_add_end_syms();
        obj_patch_symtab_links();
    }
    for (i = 0; i < obj_nsyms; i += obj_syms[i].s.n_numaux + 1) {
        if (name_inline(&obj_syms[i]))
            name_swap(obj_syms[i].s.n_name);
    }
    if (fseek(obj_fp, (long)obj_symptr, SEEK_SET) != 0)
        lnk_fatal1("Cannot seek to start of symbol table");
    if (write_symslots(obj_syms, (unsigned long)obj_nsyms, obj_fp) !=
        (unsigned long)obj_nsyms)
        lnk_fatal1("Cannot write symbols to object file");
    xfree(obj_syms);
    obj_syms = NULL;
}

/* 00428449: .text/.data extents of every input file into its section symbols */
static void obj_build_symtab(void)
{
    FILEEXT *f;
    FILEEXT *next;
    long i;

    f = obj_fext_head;
    while (f != NULL) {
        i = f->symidx;
        obj_syms[i].s.n_value = (long)f->text_lo;
        obj_syms[i].s.n_mem = f->text_mem.mmap;
        obj_syms[i + 1].a.x[0] = (long)M32(f->text_hi - f->text_lo);
        obj_syms[i + 2].s.n_value = (long)f->data_lo;
        obj_syms[i + 2].s.n_mem = f->data_mem.mmap;
        obj_syms[i + 3].a.x[0] = (long)M32(f->data_hi - f->data_lo);
        next = f->next;
        xfree(f);
        f = next;
    }
    obj_fext_cur = NULL;
    obj_fext_head = NULL;
}

/* Slots of the old array read as main entries.  The original steps over a
   skipped global without its aux entries (see obj_reorder_symtab), so aux
   slots may be read as main entries there: their words 5/6/7 then act as
   n_type/n_sclass/n_numaux. */
static char *reo_isaux;

static long ent_sclass(SYMSLOT *t, long i)
{
    return (reo_isaux != NULL && reo_isaux[i]) ? t[i].a.x[6] : t[i].s.n_sclass;
}

static long ent_type(SYMSLOT *t, long i)
{
    return (reo_isaux != NULL && reo_isaux[i]) ? t[i].a.x[5] : t[i].s.n_type;
}

static long ent_numaux(SYMSLOT *t, long i)
{
    return (reo_isaux != NULL && reo_isaux[i]) ? t[i].a.x[7] : t[i].s.n_numaux;
}

static long ent_step(SYMSLOT *t, long i)
{
    if (reo_isaux != NULL && reo_isaux[i])
        return ((t[i].a.x[0] >> 8) & 0xff) == 'b' ? 1L : -1L;
    return block_step(&t[i]);
}

/* copy entry *si and its aux entries to *dp; *si ends on the last aux */
static void copy_entry(SYMSLOT *src, long *si, SYMSLOT **dp)
{
    long k;
    long na;

    na = ent_numaux(src, *si);
    *(*dp)++ = src[*si];
    for (k = 0; k < na; k++) {
        (*si)++;
        *(*dp)++ = src[*si];
    }
}

/* 00428524: absolute file: per C_FILE group the file entry, its local
   entries, its file-level statics; the globals at the end */
static void obj_reorder_symtab(void)
{
    SYMSLOT *nw;
    SYMSLOT *old;
    SYMSLOT *dst;
    long i;
    long j;
    long k;
    long last;
    long fstart;
    long fnew;
    long nend;
    long fdepth;
    long bdepth;
    long sc;
    long ty;

    fdepth = 0;
    bdepth = 0;
    old = obj_syms;
    nw = (SYMSLOT *)xmalloc(((unsigned long)obj_nsyms + 2) * sizeof(SYMSLOT));
    reo_isaux = (char *)xmalloc((unsigned long)obj_nsyms + 1);
    memset(reo_isaux, 0, (size_t)obj_nsyms + 1);
    for (i = 0; i < obj_nsyms; i++) {
        for (k = old[i].s.n_numaux; k > 0 && i + 1 < obj_nsyms; k--)
            reo_isaux[++i] = 1;
    }
    dst = nw;
    i = 0;
    while (i < obj_nsyms) {
        sc = ent_sclass(old, i);
        ty = ent_type(old, i);
        if (sc == C_FILE || sc == A_FILE) {
            fstart = i;
            fnew = (long)(dst - nw);
            copy_entry(old, &i, &dst);
            last = i;
            while ((i = last + 1) < obj_nsyms) {
                sc = ent_sclass(old, i);
                ty = ent_type(old, i);
                if (sc == C_FCN)
                    fdepth += ent_step(old, i);
                if (sc == C_BLOCK)
                    bdepth += ent_step(old, i);
                if (sc == C_FILE || sc == A_FILE)
                    break;
                if (IS_FUNC(ty) ||
                    ((sc != C_STAT || ((fdepth != 0 || bdepth != 0) && ty != 0)) &&
                     !is_global_class(sc))) {
                    copy_entry(old, &i, &dst);
                    last = i;
                } else {
                    last = i + ent_numaux(old, i);
                }
            }
            for (j = fstart; j < i; j++) {
                sc = ent_sclass(old, j);
                ty = ent_type(old, j);
                if (sc == C_FCN)
                    fdepth += ent_step(old, j);
                if (sc == C_BLOCK)
                    bdepth += ent_step(old, j);
                if (sc == C_STAT && ((fdepth == 0 && bdepth == 0) || ty == 0) &&
                    !IS_FUNC(ty))
                    copy_entry(old, &j, &dst);
                else
                    j += ent_numaux(old, j);
            }
            nend = (long)(dst - nw);
            obj_link_symbol_tags(fnew, fnew, nend, nend, nw, nw);
            obj_link_symbol_tags(fstart, fnew, i, nend, old, nw);
            i = last;
        } else if (IS_FUNC(ty) || !is_global_class(sc)) {
            copy_entry(old, &i, &dst);
        }
        i++;                        /* sic: a skipped global's aux entries are not skipped */
    }
    for (i = 0; i < obj_nsyms; i++) {
        sc = ent_sclass(old, i);
        ty = ent_type(old, i);
        if (is_global_class(sc) && !IS_FUNC(ty))
            copy_entry(old, &i, &dst);
        else
            i += ent_numaux(old, i);
    }
    xfree(reo_isaux);
    reo_isaux = NULL;
    xfree(obj_syms);
    obj_syms = nw;
}

/* 00428bc4: aux tag indices of entries [lo,hi) of src -> index of the
   matching tag entry in [tlo,thi) of dst */
static void obj_link_symbol_tags(long lo, long tlo, long hi, long thi,
                                 SYMSLOT *src, SYMSLOT *dst)
{
    SYMSLOT *e;
    SYMSLOT *d;
    long k;
    long t;
    unsigned long off;
    char nm[9];

    for (k = lo; k < hi; k++) {
        e = &src[k];
        if (lo == tlo || (is_global_class(e->s.n_sclass) && !IS_FUNC(e->s.n_type))) {
            if (!IS_TAG(e->s.n_sclass) && e->s.n_numaux > 0 && src[k + 1].a.x[0] != 0 &&
                ((e->s.n_type & 0x1000fL) == 8 || (e->s.n_type & 0x1000fL) == 9 ||
                 (e->s.n_type & 0x1000fL) == 10 || e->s.n_sclass == C_EOS)) {
                for (t = tlo; t < thi; t++) {
                    d = &dst[t];
                    if (IS_TAG(d->s.n_sclass) &&
                        (e->s.n_sclass == C_EOS ||
                         (d->s.n_type & 0x1000fL) == (e->s.n_type & 0x1000fL))) {
                        if (dst[t + 1].a.x[0] == src[k + 1].a.x[0]) {
                            src[k + 1].a.x[0] = t;
                            break;
                        }
                    }
                    t += d->s.n_numaux;
                }
                if (t >= thi) {
                    if (name_inline(e)) {
                        memcpy(nm, e->s.n_name, 8);
                        nm[8] = '\0';
                        lnk_error2("Symbol tag mismatch", nm);
                    } else {
                        off = name_off(e->s.n_name);
                        if (off < 5 || off >= (unsigned long)obj_strcap || obj_strtab == NULL)
                            lnk_error1("Symbol tag mismatch");
                        else
                            lnk_error2("Symbol tag mismatch", obj_strtab + off);
                    }
                }
            }
        }
        k += e->s.n_numaux;
    }
}

/* 00428e67: absolute file after reordering: C_FILE chain, endndx chains,
   function sizes and line number pointers */
static void obj_patch_symtab_links(void)
{
    SYMSLOT *e;
    long i;
    long k;
    long fstat;                     /* first file-level static of the file */
    long fglob;                     /* first global */
    long prevsec;
    long fdepth;
    long bdepth;
    long fil;                       /* entry indices, -1 = none */
    long newfil;
    long fcn;
    long bf;
    long bb;
    long sect;
    long mac;
    long tag;
    long sc;
    long ty;

    fstat = -1;
    fglob = -1;
    prevsec = -1;
    fdepth = 0;
    bdepth = 0;
    fil = -1;
    fcn = -1;
    bf = -1;
    bb = -1;
    sect = -1;
    mac = -1;
    tag = -1;
    if (obj_nsyms == 0)
        return;
#define AUX(ix) (obj_syms[(ix) + 1].a)
    for (i = 0; i < obj_nsyms; i += obj_syms[i].s.n_numaux + 1) {
        e = &obj_syms[i];
        sc = e->s.n_sclass;
        ty = e->s.n_type;
        if (sc == C_FCN)
            fdepth += block_step(e);
        if (sc == C_BLOCK)
            bdepth += block_step(e);
        if (sc == C_FILE || sc == A_FILE) {
            if (fcn >= 0)  AUX(fcn).x[4] = fstat;
            if (bf >= 0)   AUX(bf).x[4] = fstat;
            if (bb >= 0)   AUX(bb).x[4] = fstat;
            if (sect >= 0) AUX(sect).x[4] = fstat;
            if (mac >= 0)  AUX(mac).x[4] = fstat;
            if (tag >= 0)  AUX(tag).x[4] = fstat;
            fstat = -1;
            newfil = i;
            if (fil >= 0)
                obj_syms[fil].s.n_value = i;
        } else {
            newfil = fil;
            if (sc == C_FCN) {
                if (e->s.n_name[1] == 'b') {
                    if (bf >= 0)
                        AUX(bf).x[4] = i;
                    bf = i;
                }
            } else if (sc == C_BLOCK && e->s.n_name[1] == 'b') {
                if (bb >= 0)
                    AUX(bb).x[4] = i;
                bb = i;
            } else if (sc == C_EFCN) {
                if (fcn < 0) {
                    lnk_error1("No previous function declaration");
                    raise(SIGSEGV);     /* the original writes through NULL */
                    return;
                }
                AUX(fcn).x[1] = (long)M32((unsigned long)e->s.n_value -
                                          (unsigned long)obj_syms[fcn].s.n_value);
            } else if (sc == A_SECT) {
                if (sect >= 0)
                    AUX(sect).x[4] = i;
                sect = i;
            } else if (sc == A_MACRO) {
                if (mac >= 0)
                    AUX(mac).x[4] = i;
                mac = i;
            } else if (sc == C_STAT && fdepth == 0 && bdepth == 0 && !IS_FUNC(ty)) {
                if (fstat < 0)
                    fstat = i;
                if (opt_i && ty == 0) {
                    if (prevsec > 0)
                        AUX(i).x[4] = prevsec;
                    prevsec = i;
                }
            }
        }
        fil = newfil;
        if (IS_FUNC(ty) && e->s.n_scnum > 0) {
            if (obj_lnnobuf != NULL) {
                k = AUX(i).x[3];
                if (cc_objects)
                    obj_lnnobuf[k].l_addr = i;
                AUX(i).x[3] = (long)M32(obj_lnnoptr0 + (unsigned long)k * OBJ_LNNOSZ);
            }
            if (fcn >= 0)
                AUX(fcn).x[4] = i;
            fcn = i;
        }
        if (IS_TAG(sc)) {
            if (tag >= 0)
                AUX(tag).x[4] = i;
            tag = i;
        }
        if (fglob < 0 && (sc == C_EXT || sc == A_GLOBAL) && e->s.n_scnum != 0 &&
            !IS_FUNC(ty))
            fglob = i;
    }
    for (i = 0; i < obj_nsyms; i += obj_syms[i].s.n_numaux + 1) {
        sc = obj_syms[i].s.n_sclass;
        if (IS_TAG(sc))
            AUX(i).x[0] = 0;
        else if (!opt_i && sc == C_STAT && obj_syms[i].s.n_type == 0)
            AUX(i).x[4] = 0;
    }
    if (fcn >= 0)  AUX(fcn).x[4] = fstat;
    if (bf >= 0)   AUX(bf).x[4] = fstat;
    if (bb >= 0)   AUX(bb).x[4] = fstat;
    if (sect >= 0) AUX(sect).x[4] = fstat;
    if (mac >= 0)  AUX(mac).x[4] = fstat;
    if (tag >= 0)  AUX(tag).x[4] = fstat;
    if (fil >= 0)
        obj_syms[fil].s.n_value = fglob;
#undef AUX
}

/* 0042930e: "etext" and "end" */
static void obj_add_end_syms(void)
{
    clear_coff_sym();
    strcpy(obj_symbuf.s.n_name, "etext");
    obj_symbuf.s.n_value = (long)text_hi;
    obj_symbuf.s.n_mem = 0;
    obj_symbuf.s.n_scnum = -1;
    obj_symbuf.s.n_sclass = C_EXT;
    obj_symbuf.s.n_numaux = 0;
    obj_add_syment(&obj_symbuf);
    memset(obj_symbuf.s.n_name, 0, 8);
    strcpy(obj_symbuf.s.n_name, "end");
    obj_add_syment(&obj_symbuf);
}

/* 00429399: string table (length word big-endian) */
static void obj_write_strtab(void)
{
    obj_strptr = M32(obj_symptr + (unsigned long)obj_nsyms * OBJ_SYMSZ);
    if (obj_strtab != NULL) {
        if (fseek(obj_fp, (long)obj_strptr, SEEK_SET) != 0)
            lnk_fatal1("Cannot seek to start of string table");
        put_be32((unsigned char *)obj_strtab, (unsigned long)obj_strsize);
        if (fwrite(obj_strtab, 1, (size_t)obj_strsize, obj_fp) != (size_t)obj_strsize)
            lnk_fatal1("Cannot write string table to object file");
        xfree(obj_strtab);
        obj_strtab = NULL;
    }
}

/* 0042944b: absolute file: after a copied C_FILE entry, ".text" and ".data"
   section symbols (filled by obj_build_symtab) and a new FILEEXT */
void obj_add_file_secsyms(void)
{
    FILEEXT *f;

    if (opt_i)
        return;
    f = (FILEEXT *)xmalloc(sizeof(FILEEXT));
    if (obj_fext_cur != NULL)
        obj_fext_cur->next = f;
    else
        obj_fext_head = f;
    obj_fext_cur = f;
    f->text_lo = 0;
    f->text_hi = 0;
    f->text_mem.mspace = 4;
    f->text_mem.mmap = 4;
    f->text_mem.mcntr = 0;
    f->text_mem.mclass = 0;
    f->data_lo = 0;
    f->data_hi = 0;
    f->data_mem.mspace = 4;
    f->data_mem.mmap = 4;
    f->data_mem.mcntr = 0;
    f->data_mem.mclass = 0;
    f->symidx = -1;
    f->next = NULL;
    clear_coff_sym();
    strcpy(obj_symbuf.s.n_name, ".text");
    obj_symbuf.s.n_value = 0;
    obj_symbuf.s.n_mem = 4;
    obj_symbuf.s.n_scnum = 1;
    obj_symbuf.s.n_sclass = C_STAT;
    obj_symbuf.s.n_numaux = 1;
    obj_fext_cur->symidx = obj_add_syment(&obj_symbuf);
    obj_auxbuf.a.x[0] = 0;
    obj_auxbuf.a.x[1] = 0;
    obj_auxbuf.a.x[2] = obj_nlnno_file;
    obj_add_syment(&obj_auxbuf);
    strcpy(obj_symbuf.s.n_name, ".data");
    obj_symbuf.s.n_value = 0;
    obj_symbuf.s.n_mem = 4;
    obj_symbuf.s.n_scnum = 2;
    obj_symbuf.s.n_sclass = C_STAT;
    obj_symbuf.s.n_numaux = 1;
    obj_add_syment(&obj_symbuf);
    obj_auxbuf.a.x[0] = 0;
    obj_auxbuf.a.x[2] = 0;
    obj_auxbuf.a.x[1] = 0;
    obj_add_syment(&obj_auxbuf);
    obj_nlnno_file = 0;
}

/* 00429641: append a symbol slot (stored only in pass 2 with an object
   file, always counted); returns its index */
long obj_add_syment(SYMSLOT *e)
{
    if (pass == 2 && obj_fp != NULL) {
        if (obj_symcap == 0) {
            obj_symcap = 0x1000;
            obj_syms = (SYMSLOT *)xmalloc((unsigned long)obj_symcap * sizeof(SYMSLOT));
        } else if (obj_symcap <= obj_nsyms) {
            if (obj_symcap < 0x40000L)
                obj_symcap <<= 1;
            else
                obj_symcap += 0x40000L;
            obj_syms = (SYMSLOT *)xrealloc(obj_syms,
                                           (unsigned long)obj_symcap * sizeof(SYMSLOT));
        }
        obj_syms[obj_nsyms] = *e;
    }
    return obj_nsyms++;
}

/* 00429716: append a string to the string table; returns its offset */
long obj_add_string(char *s)
{
    long off;
    long len;

    len = (long)strlen(s) + 1;
    off = obj_strsize;
    if (pass == 2 && obj_fp != NULL) {
        if (obj_strcap == 0) {
            obj_strcap = 0x1000;
            obj_strtab = (char *)xmalloc((unsigned long)obj_strcap);
        } else if (obj_strcap <= obj_strsize + len) {
            if (obj_strcap < 0x40000L)
                obj_strcap <<= 1;
            else
                obj_strcap += 0x40000L;
            obj_strtab = (char *)xrealloc(obj_strtab, (unsigned long)obj_strcap);
        }
        /* port: the original grows only once (and not at all on the first
           call); keep growing so an overlong string cannot overflow */
        while (obj_strcap <= obj_strsize + len) {
            if (obj_strcap < 0x40000L)
                obj_strcap <<= 1;
            else
                obj_strcap += 0x40000L;
            obj_strtab = (char *)xrealloc(obj_strtab, (unsigned long)obj_strcap);
        }
        strcpy(obj_strtab + obj_strsize, s);
        obj_strtab[obj_strsize + len] = '\0';
    }
    obj_strsize += len;
    return off;
}

/* 00429811: ".cmt" comment symbol */
void obj_add_comment(char *text, long scnum)
{
    if (pass == 2 && obj_fp != NULL) {
        clear_coff_sym();
        strcpy(obj_symbuf.s.n_name, ".cmt");
        obj_symbuf.s.n_value = obj_add_string(text);
        obj_symbuf.s.n_mem = 4;
        obj_symbuf.s.n_scnum = scnum;
        obj_add_syment(&obj_symbuf);
    }
}

/* 00429870: absolute file: the symbols of memory control SET/SYMBOL records */
static void obj_write_set_syms(void)
{
    SYM *s;
    long i;
    unsigned long hi;
    unsigned long lo;

    for (i = 0; i < HASHSIZE; i++) {
        for (s = sym_hash[i]; s != NULL; s = s->next) {
            if ((s->flags & SYM_OUTPUT) == 0)
                continue;
            clear_coff_sym();
            if (strlen(s->name) < 8)
                strcpy(obj_symbuf.s.n_name, s->name);
            else
                set_name_off(obj_symbuf.s.n_name, (unsigned long)obj_add_string(s->name));
            if (s->mem.mspace == MS_N) {
                if ((s->flags & SYM_FLOAT) == 0) {
                    obj_symbuf.s.n_mem = s->hi != 0 ? (long)s->hi : 4;
                    obj_symbuf.s.n_value = (long)s->lo;
                } else {
                    double_to_words(s->fval, &hi, &lo);
                    obj_symbuf.s.n_mem = (long)hi;
                    obj_symbuf.s.n_value = (long)lo;
                }
            } else {
                obj_symbuf.s.n_mem = s->mem.mmap;
                obj_symbuf.s.n_value = (long)s->lo;
            }
            obj_symbuf.s.n_scnum = -1;
            if ((s->flags & SYM_FLOAT) == 0)
                obj_symbuf.s.n_type = (s->flags & SYM_LONG) ? T_LONG : T_INT;
            else
                obj_symbuf.s.n_type = T_FLOAT;
            obj_symbuf.s.n_sclass = cc_objects ? C_EXT : A_GLOBAL;
            if (s->mem.mspace != MS_N)
                obj_symbuf.s.n_type |= DT_PTR;
            obj_add_syment(&obj_symbuf);
            if (obj_symbuf.s.n_numaux > 0)
                obj_add_syment(&obj_auxbuf);
        }
    }
}
