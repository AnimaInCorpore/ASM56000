/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), symtab.c
 * $Id: symtab.c,v 1.34 1997/07/03 22:15:31 lauren Exp $
 * Reconstructed from 0042bc50-0042d9fd.
 *
 * Section name / output section / section piece tables, regions and their
 * memory records, the global symbol hash table, the external reference
 * table, the end-of-link free routines and the keyword table lookups.
 *
 * Every lookup keeps its "last visited" node in a static cursor which the
 * following insert uses as the insertion point (chain order is output
 * visible: symbol tables and map listings are written in chain order).
 */
#include "dsplnk.h"

#define FOLDBUF 516                 /* uint[129] stack buffers of the original */

static SECNAME *secname_last;       /* 461e84 */
static SYM *sym_last;               /* 461e88 */
static XREF *xref_last;             /* 461e8c */

/* copy and fold (-n) a name into buf; returns the name to use */
static char *fold_name(char *name, char *buf)
{
    if (opt_n) {
        strcpy(buf, name);
        str_lower(buf);
        return buf;
    }
    return name;
}

static int same_name(char *a, char *b)
{
    return *a == *b && strcmp(a, b) == 0;
}

/* ---------------------------------------------------------------------- */

/* find the primary piece of section (name, spec); create it if missing.
   add_map: also record it in the module section map at index secno. */
SECTION *sec_lookup_create(char *name, long secno, MEMSPEC *spec, int add_map)
{
    MODSEC *ms, *m;
    SECTION *sec;
    SECNAME *sn;
    SECNODE *node;
    unsigned long v;

    ms = NULL;
    if (add_map) {
        ms = mod_secmap[secno];
        while (ms != NULL &&
               (ms->sec == NULL || ms->sec->node->spec.mspace != spec->mspace ||
                ms->sec->node->spec.mcntr != spec->mcntr))
            ms = ms->next;
    }
    sec = sec_find(name, spec);
    if (sec == NULL) {
        if (ms != NULL)
            lnk_fatal1("Invalid section number");
        if (secno == 0 && (*name != global_secname[0] || strcmp(name, global_secname) != 0))
            lnk_fatal1("Invalid global section");
        sn = secname_new(name, secno);
        node = secnode_get(sn, spec);
        sec = sec_alloc(node, SF_REL);
        sec->next = node->secs;
        node->secs = sec;
        if (add_map) {
            m = (MODSEC *)xmalloc(sizeof(MODSEC));
            m->sec = sec;
            m->base2 = 0;
            m->base_raw = 0;
            m->base = 0;
            m->fsym = cur_file_ent;
            m->next = mod_secmap[secno];
            mod_secmap[secno] = m;
        }
        node->nsecs++;
        num_secs++;
    } else if (ms == NULL && add_map) {
        m = (MODSEC *)xmalloc(sizeof(MODSEC));
        m->sec = sec;
        v = sec->hi;
        if (v < sec->lo)
            v = sec->lo;
        m->base2 = v;
        m->base_raw = v;
        m->base = v;
        m->fsym = cur_file_ent;
        m->next = mod_secmap[secno];
        mod_secmap[secno] = m;
    }
    return sec;
}

SECTION *sec_alloc(SECNODE *node, unsigned long flags)
{
    SECTION *s;

    s = (SECTION *)xmalloc(sizeof(SECTION));
    memset(s, 0, sizeof(SECTION));
    s->node = node;
    s->index = 0;
    s->flags = flags;
    s->sdi = NULL;
    s->ovl = NULL;
    s->msyms = NULL;
    s->next = NULL;
    s->run = s;
    return s;
}

SECTION *sec_find(char *name, MEMSPEC *spec)
{
    char buf[FOLDBUF];
    SECNAME *sn;
    SECNODE *node;

    name = fold_name(name, buf);
    sn = sec_hash[hash_name(name)];
    secname_last = sn;
    for (;;) {
        if (sn == NULL)
            return NULL;
        secname_last = sn;
        if (same_name(name, sn->name))
            break;
        sn = sn->hnext;
    }
    for (node = sn->nodes; node != NULL; node = node->next)
        if (node->spec.mspace == spec->mspace && node->spec.mcntr == spec->mcntr)
            return node->secs;
    return NULL;
}

/* returns the entry the preceding lookup stopped at when it has this name,
   else a new entry linked after it (or as the bucket head) */
SECNAME *secname_new(char *name, long num)
{
    char buf[FOLDBUF];
    SECNAME *sn;

    name = fold_name(name, buf);
    if (secname_last != NULL && same_name(name, secname_last->name))
        return secname_last;
    sn = (SECNAME *)xmalloc(sizeof(SECNAME));
    sn->name = (char *)xmalloc((unsigned long)strlen(name) + 1);
    strcpy(sn->name, name);
    if (num < 1)
        sn->num = num;
    else
        sn->num = ++sec_num_seed;
    sn->nodes = NULL;
    sn->xrefs = NULL;
    sn->hnext = NULL;
    if (secname_last == NULL) {
        sec_hash[hash_name(name)] = sn;
    } else if (secname_last->hnext == NULL) {
        secname_last->hnext = sn;
    } else {
        sn->hnext = secname_last->hnext;
        secname_last->hnext = sn;
    }
    return sn;
}

SECNAME *secname_lookup(char *name)
{
    char buf[FOLDBUF];
    SECNAME *sn;

    name = fold_name(name, buf);
    sn = sec_hash[hash_name(name)];
    secname_last = sn;
    for (;;) {
        if (sn == NULL)
            return NULL;
        secname_last = sn;
        if (same_name(name, sn->name))
            return sn;
        sn = sn->hnext;
    }
}

SECNODE *secnode_get(SECNAME *sn, MEMSPEC *spec)
{
    SECNODE *n;

    n = secnode_find(sn, spec);
    if (n == NULL) {
        n = (SECNODE *)xmalloc(sizeof(SECNODE));
        memset(n, 0, sizeof(SECNODE));
        n->sname = sn;
        n->spec = *spec;
        n->flags = 0;
        n->secs = NULL;
        n->abss = NULL;
        n->bufs = NULL;
        n->ovls = NULL;
        n->nsecs = n->nabss = n->nbufs = n->novls = 0;
        n->bufsz = n->bufsz_al = n->sv_bufsz = n->sv_bufsz_al = 0;
        n->sbalign = n->totlen = n->totovl = n->totsize = n->sdigrow = 0;
        n->secsize = 0;
        n->secpct = 0.0;
        n->ovl_last = NULL;
        n->ovl_stamp = NULL;
        n->memreg = NULL;
        n->next = sn->nodes;
        sn->nodes = n;
    }
    return n;
}

SECNODE *secnode_find(SECNAME *sn, MEMSPEC *spec)
{
    SECNODE *n;

    for (n = sn->nodes; n != NULL; n = n->next)
        if (n->spec.mspace == spec->mspace && n->spec.mcntr == spec->mcntr)
            break;
    return n;
}

REGION *region_get(char *name)
{
    REGION *r;

    r = region_find(name);
    if (r == NULL) {
        r = (REGION *)xmalloc(sizeof(REGION));
        r->name = (char *)xmalloc((unsigned long)strlen(name) + 1);
        strcpy(r->name, name);
        if (opt_n)
            str_lower(r->name);
        r->nmem = 0;
        r->mems = NULL;
        r->next = NULL;
        if (region_last != NULL)
            region_last->next = r;
        else
            region_head = r;
    }
    return r;
}

REGION *region_find(char *name)
{
    char buf[FOLDBUF];
    REGION *r;

    name = fold_name(name, buf);
    region_last = region_head;
    for (r = region_head; r != NULL; r = r->next) {
        region_last = r;
        if (same_name(name, r->name))
            return r;
    }
    return NULL;
}

MEMREG *memreg_get(REGION *rg, MEMSPEC *spec, int remap)
{
    MEMREG *m;

    m = memreg_find(rg, spec);
    if (m == NULL) {
        m = memreg_new(rg, spec);
        m->next = rg->mems;
        rg->mems = m;
        rg->nmem++;
    } else if (remap) {
        if ((m->flags & MR_REMAP) != 0 && !sdi_active)
            lnk_warning1("Remapping region");
        m->flags |= MR_REMAP;
        m->spec.mmap = spec->mmap;
    }
    return m;
}

MEMREG *memreg_new(REGION *rg, MEMSPEC *spec)
{
    MEMREG *m;

    m = (MEMREG *)xmalloc(sizeof(MEMREG));
    m->region = rg;
    m->flags2 = 0;
    m->flags = 0;
    m->spec = *spec;
    m->ovlcur = 0;
    m->balign = 0;
    m->size = 0;
    m->base = 0;
    if (spec->mspace == MS_E) {
        if (spec->mmap == MS_E)
            m->high = ext_addr_mask;
        else if (target_index == TGT_56600)
            m->high = ext_addr_mask;
        else if (spec->mmap >= MM_E0 && spec->mmap < MM_E0 + 256)
            m->high = EMI_MAX_ADDR(spec->mmap);
        else
            m->high = ext_addr_mask;        /* original reads beyond the table */
    } else {
        m->high = addr_mask;
    }
    m->secs = NULL;
    m->nsecs = 0;
    m->next = NULL;
    return m;
}

MEMREG *memreg_find(REGION *rg, MEMSPEC *spec)
{
    MEMREG *m;

    for (m = rg->mems; m != NULL; m = m->next)
        if (m->spec.mspace == spec->mspace && m->spec.mcntr == spec->mcntr)
            return m;
    return NULL;
}

/* ---------------------------------------------------------------------- */

/* enter a symbol (copy of the template, own name copy) unless a
   conflicting definition exists */
SYM *sym_enter(SYM *tmpl)
{
    SYM *old, *s;

    old = sym_lookup(tmpl->name, 1);
    if (old != NULL) {
        if (old->sec == NULL) {
            lnk_error2("Duplicate special symbol", tmpl->name);
            return old;
        }
        if (tmpl->sec == old->sec) {
            if (old->sec != NULL && old->sec->node->sname->num != 0) {
                lnk_error2("Duplicate local symbol", tmpl->name);
                return old;
            }
            lnk_error2("Duplicate global symbol", tmpl->name);
            return old;
        }
        if ((tmpl->flags & SYM_XDEF) != 0 && (old->flags & SYM_XDEF) != 0) {
            if (cur_infile == NULL)
                return old;
            if ((cur_infile->flags & IF_LIBRARY) != 0)
                return old;
            lnk_warning2("Duplicate XDEF symbol", tmpl->name);
            return old;
        }
        if ((tmpl->flags & SYM_GLOBAL) != 0 && (old->flags & SYM_GLOBAL) != 0) {
            if (cur_infile == NULL)
                return old;
            if ((cur_infile->flags & IF_LIBRARY) != 0)
                return old;
            lnk_warning2("Duplicate global symbol", tmpl->name);
            return old;
        }
    }
    s = (SYM *)xmalloc(sizeof(SYM));
    *s = *tmpl;
    s->name = (char *)xmalloc((unsigned long)strlen(tmpl->name) + 1);
    strcpy(s->name, tmpl->name);
    if (opt_n)
        str_lower(s->name);
    num_syms++;
    if (sym_last == NULL) {
        sym_hash[hash_name(s->name)] = s;
    } else {
        s->next = sym_last->next;
        sym_last->next = s;
    }
    return s;
}

/* find the visible definition of a global symbol: same section name, else
   an enclosing (nested) section, else an XDEF one, else a GLOBAL one */
SYM *sym_lookup(char *name, int defining)
{
    char buf[FOLDBUF];
    SYM *s, *glob, *nest, *xdef;
    SECNEST *stk;
    MODSEC *ms;

    glob = NULL;
    nest = NULL;
    xdef = NULL;
    name = fold_name(name, buf);
    sym_last = sym_hash[hash_name(name)];
    for (s = sym_last; s != NULL; s = s->next) {
        sym_last = s;
        if (!same_name(name, s->name))
            continue;
        if (cur_section != NULL && s->sec != NULL &&
            s->sec->node->sname == cur_section->node->sname)
            break;
        if (nested_secs && sec_nest != NULL && nest == NULL &&
            cur_infile != NULL && !defining) {
            for (stk = sec_nest; stk != NULL; stk = stk->next) {
                if (s->sec == NULL)
                    continue;
                ms = mod_secmap[stk->id];
                if (ms != NULL && s->sec->node->sname == ms->sec->node->sname) {
                    nest = s;
                    break;
                }
            }
        }
        if (xdef == NULL && (s->flags & SYM_XDEF) != 0 &&
            (defining || sec_has_xref(name)))
            xdef = s;
        if (glob == NULL && (s->flags & SYM_GLOBAL) != 0)
            glob = s;
    }
    if (s == NULL) {
        if (nest != NULL)
            s = nest;
        else if (xdef != NULL)
            s = xdef;
        else if (glob != NULL)
            s = glob;
    }
    sym_found = s;
    return s;
}

/* record an external reference; force: command line (-u) */
XREF *xref_add(char *name, int force, int is_xref)
{
    XREF *x;

    if (!is_xref && !force)
        is_xref = sec_has_xref(name);
    x = xref_lookup(name);
    if (x == NULL || force || x->module == NULL || cur_infile == NULL ||
        x->module != cur_infile->module || x->sec == NULL || cur_section == NULL ||
        x->sec->node->sname != cur_section->node->sname) {
        x = (XREF *)xmalloc(sizeof(XREF));
        x->name = (char *)xmalloc((unsigned long)strlen(name) + 1);
        strcpy(x->name, name);
        if (opt_n)
            str_lower(x->name);
        x->flags = is_xref ? XREF_XREF : XREF_GLOBAL;
        if (!force) {
            x->infile = cur_infile;
            x->module = cur_infile == NULL ? NULL : cur_infile->module;
            x->sec = cur_section;
        } else {
            x->infile = NULL;
            x->module = NULL;
            x->sec = NULL;
        }
        x->next = NULL;
        if (xref_last == NULL) {
            xref_hash[hash_name(x->name)] = x;
            x->prev = NULL;
        } else {
            x->next = xref_last->next;
            xref_last->next = x;
            x->prev = xref_last;
            if (x->next != NULL)
                x->next->prev = x;
        }
        num_xrefs++;
        lib_rescan = 1;
    } else if (is_xref && (x->flags & XREF_GLOBAL) != 0) {
        x->flags &= ~XREF_GLOBAL;
        x->flags |= XREF_XREF;
    }
    return x;
}

/* same section name and same input file -> that node; else the last node
   with the same section name; else the last other node */
XREF *xref_lookup(char *name)
{
    char buf[FOLDBUF];
    XREF *x, *other, *samesec;
    int same;

    name = fold_name(name, buf);
    other = NULL;
    samesec = NULL;
    xref_last = xref_hash[hash_name(name)];
    for (x = xref_last; x != NULL; x = x->next) {
        xref_last = x;
        if (!same_name(name, x->name))
            continue;
        same = x->sec != NULL && cur_section != NULL &&
               x->sec->node->sname == cur_section->node->sname;
        if (same && x->infile != NULL && cur_infile != NULL && cur_infile == x->infile)
            break;
        if (!same)
            other = x;
        else
            samesec = x;
    }
    if (x == NULL) {
        if (samesec != NULL)
            x = samesec;
        else if (other != NULL)
            x = other;
    }
    return x;
}

/* drop references that a symbol definition now satisfies */
void xref_purge(void)
{
    long i;
    XREF *x, *next;
    SYM *s;
    int glob;

    for (i = 0; i < HASHSIZE; i++) {
        x = xref_hash[i];
        while (x != NULL) {
            next = NULL;
            glob = 0;
            for (s = sym_hash[hash_name(x->name)]; s != NULL; s = s->next) {
                if (!same_name(s->name, x->name))
                    continue;
                if ((s->flags & SYM_GLOBAL) != 0)
                    glob = 1;
                if ((s->flags & 0xc0 & x->flags) != 0 ||
                    (s->sec != NULL && x->sec != NULL &&
                     s->sec->node->sname == x->sec->node->sname)) {
                    next = x->next;
                    glob = 0;
                    xref_remove(x);
                    x = NULL;
                    break;
                }
            }
            if (next == NULL && x != NULL && glob) {
                next = x->next;
                xref_remove(x);
                x = NULL;
            }
            if (next != NULL)
                x = next;
            else if (x != NULL)
                x = x->next;
            else
                x = NULL;
        }
    }
}

void xref_remove(XREF *x)
{
    unsigned long h;

    h = hash_name(x->name);
    if (!opt_i || (x->flags & XREF_XREF) == 0) {
        if (x->prev == NULL)
            xref_hash[h] = x->next;
        else
            x->prev->next = x->next;
        if (x->next != NULL)
            x->next->prev = x->prev;
        if (x->prev == NULL && x->next == NULL)
            xref_hash[h] = NULL;
        xfree(x->name);
        xfree(x);
        num_xrefs--;
    } else {
        x->flags |= XREF_DONE;
        num_xrefs_done++;
    }
}

/* ---------------------------------------------------------------------- */

void free_sort_arrays(void)
{
    if (map_secs != NULL) {
        xfree(map_secs);
        map_secs = NULL;
    }
    if (map_syms != NULL) {
        xfree(map_syms);
        map_syms = NULL;
    }
    if (map_xrefs != NULL) {
        xfree(map_xrefs);
        map_xrefs = NULL;
    }
}

void free_memmaps(void)
{
    REGION *r, *rn;
    MEMREG *m, *mn;
    SECREF *sr, *srn;

    r = region_head;
    while (r != NULL) {
        if (r->name != NULL)
            xfree(r->name);
        m = r->mems;
        while (m != NULL) {
            sr = m->secs;
            while (sr != NULL) {
                srn = sr->next;
                xfree(sr);
                sr = srn;
            }
            mn = m->next;
            xfree(m);
            m = mn;
        }
        rn = r->next;
        xfree(r);
        r = rn;
    }
    region_last = NULL;
}

static void free_piece_list(SECTION *s, int sdi)
{
    SECTION *n;

    while (s != NULL) {
        if (sdi)
            sdi_free(s);
        n = s->next;
        xfree(s);
        s = n;
    }
}

void free_sections(void)
{
    long i;
    SECNAME *sn, *snn;
    SECNODE *node, *nn;
    STRNODE *x, *xn;

    for (i = 0; i < HASHSIZE; i++) {
        sn = sec_hash[i];
        if (sn == NULL)
            continue;
        sec_hash[i] = NULL;
        while (sn != NULL) {
            xfree(sn->name);
            node = sn->nodes;
            while (node != NULL) {
                free_piece_list(node->secs, 1);
                free_piece_list(node->abss, 0);
                free_piece_list(node->bufs, 0);
                free_piece_list(node->ovls, 1);
                nn = node->next;
                xfree(node);
                node = nn;
            }
            x = sn->xrefs;
            while (x != NULL) {
                xn = x->next;
                xfree(x);
                x = xn;
            }
            snn = sn->hnext;
            xfree(sn);
            sn = snn;
        }
    }
    secname_last = NULL;
    num_secs = 0;
}

void sym_free_all(void)
{
    long i;
    SYM *s, *n;

    for (i = 0; i < HASHSIZE; i++) {
        s = sym_hash[i];
        if (s == NULL)
            continue;
        sym_hash[i] = NULL;
        while (s != NULL) {
            if (s->name != NULL)
                xfree(s->name);
            n = s->next;
            xfree(s);
            s = n;
        }
    }
    sym_last = NULL;
    num_syms = 0;
}

void xref_free_all(void)
{
    long i;
    XREF *x, *n;

    for (i = 0; i < HASHSIZE; i++) {
        x = xref_hash[i];
        if (x == NULL)
            continue;
        xref_hash[i] = NULL;
        while (x != NULL) {
            if (x->name != NULL)
                xfree(x->name);
            n = x->next;
            xfree(x);
            x = n;
        }
    }
    xref_last = NULL;
    num_xrefs = 0;
}

void free_section_xrefs(void)
{
    long i;
    SECNAME *sn;
    STRNODE *x, *n;

    for (i = 0; i < HASHSIZE; i++) {
        for (sn = sec_hash[i]; sn != NULL; sn = sn->hnext) {
            x = sn->xrefs;
            while (x != NULL) {
                xfree(x->str);
                n = x->next;
                xfree(x);
                x = n;
            }
            sn->xrefs = NULL;
        }
    }
}

void free_module_tables(void)
{
    INFILE *f;
    MODULE *m;
    MODSEC *ms, *n;
    long i;

    for (f = infile_head; f != NULL; f = f->next) {
        for (m = f->members != NULL ? f->members : f->module; m != NULL; m = m->next) {
            if (m->secmap != NULL) {
                for (i = 0; i < m->lh.secnt; i++) {
                    ms = m->secmap[i];
                    while (ms != NULL) {
                        n = ms->next;
                        xfree(ms);
                        ms = n;
                    }
                }
                xfree(m->secmap);
                m->secmap = NULL;
            }
            if (m->buftab != NULL) {
                xfree(m->buftab);
                m->buftab = NULL;
            }
            if (m->sectref != NULL) {
                xfree(m->sectref);
                m->sectref = NULL;
            }
            if (m->ovltab != NULL) {
                xfree(m->ovltab);
                m->ovltab = NULL;
            }
            if (m->syms != NULL) {
                xfree(m->syms);
                m->syms = NULL;
            }
            if (m->strtab != NULL) {
                xfree(m->strtab);
                m->strtab = NULL;
            }
        }
    }
}

void free_input_files(void)
{
    INFILE *f, *fn;
    MODULE *m, *mn;

    f = infile_head;
    while (f != NULL) {
        if (f->name != NULL)
            xfree(f->name);
        m = f->members != NULL ? f->members : f->module;
        while (m != NULL) {
            if (m->name != NULL)
                xfree(m->name);
            mn = m->next;
            xfree(m);
            m = mn;
        }
        fn = f->next;
        xfree(f);
        f = fn;
    }
    cur_infile = NULL;
}

void free_ranges(RANGE *r)
{
    RANGE *n;

    while (r != NULL) {
        n = r->next;
        xfree(r);
        r = n;
    }
}

void free_ctr_groups(void)
{
    CTRGROUP *g, *n;
    int i;

    g = ctr_groups;
    while (g != NULL) {
        for (i = 0; i < NMEMIDX; i++)
            if (g->lists[i] != NULL)
                free_ranges(g->lists[i]);
        n = g->next;
        xfree(g);
        g = n;
    }
    for (i = 0; i < NMEMIDX; i++)
        used_ranges[i] = NULL;
    ctr_groups = NULL;
    ctr_lists = NULL;
}

/* ---------------------------------------------------------------------- */

KEYWORD *find_memctl_kw(char *name)
{
    return (KEYWORD *)tab_search(name, memctl_kw_tab, (long)memctl_kw_cnt,
                                 (long)sizeof(KEYWORD), name_cmp);
}

KEYWORD *find_map_opt(char *name)
{
    return (KEYWORD *)tab_search(name, memctl_mapopt_tab, (long)memctl_mapopt_cnt,
                                 (long)sizeof(KEYWORD), name_cmp);
}

KEYWORD *find_xopt(char *name)
{
    return (KEYWORD *)tab_search(name, memctl_xopt_tab, (long)memctl_xopt_cnt,
                                 (long)sizeof(KEYWORD), name_cmp);
}

int name_cmp(void *key, void *entry)
{
    return strcmp((char *)key, ((KEYWORD *)entry)->name);
}

/* 1 if name is on the XREF list of the current (non-GLOBAL) section */
int sec_has_xref(char *name)
{
    char buf[FOLDBUF];
    STRNODE *x;

    if (cur_section->node->sname->num != 0) {
        name = fold_name(name, buf);
        for (x = cur_section->node->sname->xrefs; x != NULL; x = x->next)
            if (*x->str == *name && strcmp(x->str, name) == 0)
                return 1;
    }
    return 0;
}
