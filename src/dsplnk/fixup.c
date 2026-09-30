/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), fixup.c
 * $Id: fixup.c,v 1.59 1999/03/19 20:11:25 jay Exp $
 * Reconstructed from DSPLNK.EXE 0040d4e0-00411808.
 *
 * Address assignment: sizes the sections, places reserves, absolute
 * pieces, buffers and relocatable sections region by region into the
 * used-range lists, relocates the symbols, and places the overlays.
 * With span-dependent instructions (-j / F_SDI inputs) the placement is
 * repeated until the SDI forms converge (sdi.c).
 *
 * Port notes: addresses are 32-bit unsigned quantities; every stored sum
 * or difference is masked with M32().  range_saved (0x461e20) dangles in
 * the original after the lists it points into are freed (with -xeso);
 * the port resets it to 0 whenever such lists are freed.
 */
#include "dsplnk.h"

static MEMREG *def_memreg;              /* 461dd8 DEFAULT memreg matching cur_memreg */
static RANGE *range_head;               /* 461e18 list being allocated from */
static RANGE *range_cur;                /* 461e1c search cursor */
static RANGE *range_saved;              /* 461e20 cursor saved by fixup_place_listed */
static unsigned long high_water[NMEMIDX]; /* 461e30 per MI_* highest end (counter 0) */
static unsigned long dsize_high;        /* 461e50 data high water (DSIZE) */
static unsigned long place_base;        /* 4612f8 placement start address */

static void fixup_alloc_sections(void);
static void fixup_get_counter_group(long mcntr);
static void fixup_mark_xy_abs(MEMREG *mr);
static void fixup_save_counters(void);
static void fixup_restore_counters(void);
static unsigned long fixup_mem_total(MEMSPEC *spec);
static MEMREG **fixup_collect_memregs(REGION *rg);
static SECTION **fixup_collect_reserves(MEMREG *mr);
static SECTION **fixup_collect_abs(MEMREG *mr);
static SECTION **fixup_collect_bufs(MEMREG *mr);
static SECTION **fixup_collect_secs(MEMREG *mr);
static void fixup_size_all_sections(void);
static void fixup_size_section(SECTION *sec);
static void fixup_mark_abs(SECTION *sec, int mi);
static unsigned long fixup_sec_length(SECTION *sec);
static void fixup_place_sbalign(SECTION *buf, int mi);
static void fixup_place_at(SECTION *sec, int mi);
static void fixup_place_listed(MEMREG *mr, int mi);
static void fixup_place_balign(MEMREG *mr, SECTION **bufs, int mi);
static void fixup_place_default(MEMREG *mr, SECTION **secs, int mi);
static void fixup_update_high_water(int mi, unsigned long end);
static void fixup_mark_used(SECTION *sec, int mi, unsigned long lo,
                            unsigned long hi, int report);
static unsigned long fixup_alloc_range(unsigned long len, unsigned long align,
                                       int commit, unsigned long mask);
static RANGE *range_insert(RANGE *after, unsigned long lo, unsigned long hi);
static void range_add(RANGE **head, unsigned long lo, unsigned long hi);
static RANGE *range_merge(RANGE *prev, RANGE *node, RANGE *next);
static int fixup_size_symbols(void);
static void fixup_place_overlays(void);
static void fixup_place_ovl_all(void);
static SECTION **fixup_collect_ovls(MEMREG *mr);
static void fixup_ovl_after_located(MEMREG *mr, SECTION **ovls, int mi);
static void fixup_ovl_after_section(MEMREG *mr, SECTION **ovls, int mi);
static void fixup_ovl_listed(MEMREG *mr, SECTION **ovls, int mi);
static void fixup_ovl_default(MEMREG *mr, SECTION **ovls, int mi);
static void fixup_check_bounds(MEMREG *mr, SECTION *sec, int mi,
                               unsigned long lo, unsigned long hi, int report);

/* growth of the last SDI record of a section (recs[n-1].growth) */
static long last_growth(SDISTAT *st)
{
    if (st->n <= 0)
        return 0;               /* original reads recs[-1] here */
    return st->recs[st->n - 1].growth;
}

/* 40d4e0 */
void fixup_relocate(void)
{
    if (opt_v)
        fprintf(stderr, "%s: Beginning section and symbol relocation\n", progname);
    fixup_size_all_sections();
    cur_infile = NULL;
    if (ctl_fp != NULL)
        memctl_process_file(0);
    if (!sdi_active) {
        fixup_alloc_sections();
    } else {
        fixup_save_counters();
        fixup_alloc_sections();
        do {
            sdi_changed = 0;
            sdi_resolve_all();
            if (sdi_changed) {
                fixup_restore_counters();
                if (ctl_fp != NULL) {
                    rewind(ctl_fp);
                    memctl_process_file(0);
                }
                fixup_alloc_sections();
            }
        } while (sdi_changed);
        fixup_restore_counters();
        if (ctl_fp != NULL) {
            rewind(ctl_fp);
            memctl_process_file(0);
        }
        fixup_alloc_sections();
        sdi_reset_all();
    }
    if (ctl_fp != NULL)
        fclose(ctl_fp);
}

/* relocation of one symbol (body of the loop in fixup_alloc_sections) */
static void fixup_reloc_symbol(SYM *sym)
{
    unsigned long fl;
    SDISTAT *st;

    fl = sym->flags;
    if ((fl & SYM_SPECIAL) == 0) {
        if ((fl & SYM_REL) != 0 && (fl & SYM_OVERLAY) == 0) {
            if (!opt_i) {
                if (sdi_active) {
                    sym->fval = sym->sfval;
                    sym->hi = sym->shi;
                    sym->lo = sym->slo;
                    sym->unk_14 = sym->sunk_14;
                }
                if (sym->osec != NULL) {
                    sym->lo = M32(sym->lo + sym->osec->ovl->sdioff);
                    st = sym->osec->sdi;
                    if (st != NULL && st->recs != NULL)
                        sym->lo = M32(sym->lo + last_growth(st));
                }
                if ((sym->rsec->flags & SF_ALIGNED) == 0) {
                    sym->lo = M32(sym->lo + sym->rsec->lo + sym->smap->base);
                    if (target_index == TGT_SC100 && sym->mem.mspace == 0)
                        sym->hi = ((sym->lo & ~word_mask & 0xffffffffUL)
                                   >> ((int)word_bits & 0x1f)) & word_mask;
                    st = sym->rsec->sdi;
                    if (sym->sdi_cnt != 0 && st != NULL && st->recs != NULL)
                        sym->lo = M32(sym->lo + st->recs[sym->sdi_cnt - 1].growth);
                } else if ((sym->flags & SYM_BUFFER) == 0) {
                    sym->lo = M32(sym->lo + (sym->rsec->lo + sym->smap->base_raw
                                             - sym->cls_off));
                    st = sym->rsec->sdi;
                    if (sym->sdi_cnt != 0 && st != NULL && st->recs != NULL)
                        sym->lo = M32(sym->lo + st->recs[sym->sdi_cnt - 1].growth);
                } else {
                    sym->lo = M32(sym->lo - sym->buf->addr);
                    sym->lo = M32(sym->lo + sym->buf->sec->lo);
                }
            } else {
                sym->lo = M32(sym->lo + sym->smap->base);
            }
        }
    } else if (sym->sec == NULL) {
        sym->lo = fixup_mem_total(&sym->mem);
    }
}

/* 40d5e0 */
static void fixup_alloc_sections(void)
{
    REGION *rg;
    MEMREG **mrs, **mrp, *mr;
    SECTION **arr, **pp, **secs, **bufs;
    SYM *sym;
    long lastctr;
    int i, mi;

    fixup_check_secsizes();
    for (rg = region_head; rg != NULL; rg = rg->next)
        region_last = rg;
    region_last->next = region_head;
    for (rg = region_head->next; rg != NULL; rg = rg->next) {
        cur_region = rg;
        mrs = fixup_collect_memregs(rg);
        lastctr = -1;
        if (rg == region_head) {
            for (i = 0; i < NMEMIDX; i++) {
                if (used_ranges[i] != NULL) {
                    free_ranges(used_ranges[i]);
                    used_ranges[i] = NULL;
                    range_saved = NULL;
                }
            }
        }
        for (mrp = mrs; mrp != NULL && *mrp != NULL; mrp++) {
            mr = *mrp;
            cur_memreg = mr;
            def_memreg = memreg_get(region_head, &mr->spec, 0);
            mi = mem_space_index(mr->spec.mspace);
            if (mr->spec.mcntr != lastctr) {
                lastctr = mr->spec.mcntr;
                fixup_get_counter_group(lastctr);
                range_head = NULL;
                range_cur = NULL;
                for (i = 0; i < NMEMIDX; i++) {
                    if (used_ranges[i] != NULL && rg != region_head) {
                        free_ranges(used_ranges[i]);
                        range_saved = NULL;
                    }
                    used_ranges[i] = (rg == region_head) ? ctr_lists[i] : NULL;
                }
            }
            arr = fixup_collect_reserves(mr);
            if (arr != NULL) {
                for (pp = arr; *pp != NULL; pp++)
                    fixup_mark_abs(*pp, mi);
                xfree(arr);
            }
            arr = fixup_collect_abs(mr);
            if (arr != NULL) {
                for (pp = arr; *pp != NULL; pp++)
                    fixup_mark_abs(*pp, mi);
                xfree(arr);
            }
            secs = fixup_collect_secs(mr);
            if (secs != NULL) {
                if (mi == MI_L)
                    fixup_mark_xy_abs(mr);
                if ((mr->flags & (MR_SBALIGN | MR_BALIGN)) == 0)
                    bufs = NULL;
                else
                    bufs = fixup_collect_bufs(mr);
                range_head = used_ranges[mi];
                range_cur = range_head;
                if (bufs != NULL) {
                    for (pp = bufs; *pp != NULL; pp++)
                        if (((*pp)->flags & SF_SBALIGN) != 0)
                            fixup_place_sbalign(*pp, mi);
                }
                pp = secs;
                if ((mr->flags2 & MR2_ADDR) != 0) {
                    for (; *pp != NULL; pp++)
                        if (((*pp)->state & SS_ADDR) != 0)
                            fixup_place_at(*pp, mi);
                }
                range_head = used_ranges[mi];
                range_cur = range_head;
                if (bufs != NULL) {
                    fixup_place_balign(mr, bufs, mi);
                    xfree(bufs);
                }
                if ((mr->flags2 & MR2_LISTED) != 0)
                    fixup_place_listed(mr, mi);
                fixup_place_default(mr, secs, mi);
                xfree(secs);
            }
            if (rg == region_head) {
                for (i = 0; i < NMEMIDX; i++)
                    ctr_lists[i] = used_ranges[i];
            }
        }
        if (rg == region_head) {
            rg = region_last;
            region_last->next = NULL;
        }
        xfree(mrs);
    }
    free_ctr_groups();
    range_saved = NULL;
    if (opt_c)
        fixup_size_symbols();
    xref_purge();
    for (i = 0; i < HASHSIZE; i++)
        for (sym = sym_hash[i]; sym != NULL; sym = sym->next)
            fixup_reloc_symbol(sym);
    if (!opt_i && num_overlays != 0)
        fixup_place_overlays();
}

/* 40dd4a */
static void fixup_get_counter_group(long mcntr)
{
    CTRGROUP *g;
    int i;

    for (g = ctr_groups; g != NULL && g->mcntr != mcntr; g = g->next)
        ;
    if (g == NULL) {
        g = (CTRGROUP *)xmalloc(sizeof(CTRGROUP));
        g->mcntr = mcntr;
        for (i = 0; i < NMEMIDX; i++)
            g->lists[i] = NULL;
        g->next = ctr_groups;
        ctr_groups = g;
    }
    ctr_lists = &g->lists[0];
}

/* 40ddde: an L memreg - mark the reserves and absolute pieces of the X and
   Y memregs of the same region and counter as used */
static void fixup_mark_xy_abs(MEMREG *mr)
{
    MEMSPEC spec;
    MEMREG *xmr, *ymr;
    SECTION **arr, **pp;

    spec.mcntr = mr->spec.mcntr;
    spec.mclass = mr->spec.mclass;
    spec.mmap = MS_X;
    spec.mspace = MS_X;
    xmr = memreg_find(mr->region, &spec);
    spec.mmap = MS_Y;
    spec.mspace = MS_Y;
    ymr = memreg_find(mr->region, &spec);
    if (xmr != NULL && (arr = fixup_collect_reserves(xmr)) != NULL) {
        for (pp = arr; *pp != NULL; pp++)
            fixup_mark_abs(*pp, MI_X);
        xfree(arr);
    }
    if (xmr != NULL && (arr = fixup_collect_abs(xmr)) != NULL) {
        for (pp = arr; *pp != NULL; pp++)
            fixup_mark_abs(*pp, MI_X);
        xfree(arr);
    }
    if (ymr != NULL && (arr = fixup_collect_reserves(ymr)) != NULL) {
        for (pp = arr; *pp != NULL; pp++)
            fixup_mark_abs(*pp, MI_Y);
        xfree(arr);
    }
    if (ymr != NULL && (arr = fixup_collect_abs(ymr)) != NULL) {
        for (pp = arr; *pp != NULL; pp++)
            fixup_mark_abs(*pp, MI_Y);
        xfree(arr);
    }
}

/* SECSIZE target of a node (x87 fild/fmul/_ftol: low 32 bits of the
   truncated product) */
static unsigned long secsize_target(SECNODE *node, unsigned long len)
{
    double v;

    if ((node->flags & SN_SECPCT) == 0)
        return node->secsize;
    v = (double)len * node->secpct;
    if (v >= 4294967296.0)
        v = fmod(v, 4294967296.0);
    return M32((unsigned long)v);
}

/* 40df91 */
void fixup_check_secsizes(void)
{
    int i;
    SECNAME *sn;
    SECNODE *node;
    SECTION *s, *prim;
    MEMREG *mr;
    unsigned long len, target;

    for (i = 0; i < HASHSIZE; i++) {
        for (sn = sec_hash[i]; sn != NULL; sn = sn->hnext) {
            for (node = sn->nodes; node != NULL; node = node->next) {
                if (pass == 1) {
                    node->ovl_last = NULL;
                    if (node->memreg == NULL) {
                        mr = memreg_get(region_head, &node->spec, 0);
                        for (s = node->secs; s != NULL; s = s->next)
                            memctl_assign_region(mr, s, 0L);
                    }
                    if ((node->flags & SN_F40000) == 0 &&
                        (opt_a || (node->memreg->flags & MR_BALIGN) != 0 ||
                         (node->secs->sdi != NULL && node->secs->sdi->n != 0))) {
                        node->secs->flags |= SF_ALIGNED;
                        for (s = node->bufs; s != NULL; s = s->next)
                            if ((s->flags & SF_REL) != 0)
                                s->flags |= SF_ALIGNED;
                        if (node->secs->sdi != NULL && node->secs->sdi->n != 0)
                            node->memreg->flags |= MR_SBALIGN;
                    }
                }
                if (sn->num != SN_RESERVE_NUM && node->secs != NULL) {
                    prim = node->secs;
                    if (pass == 1 && (prim->flags & SF_ALIGNED) != 0) {
                        prim->hi = M32(prim->hi - node->bufsz_al);
                        node->bufsz_al = 0;
                        node->bufsz = 0;
                        prim->align = 0;
                        node->memreg->flags |= MR_SBALIGN;
                    }
                    len = M32(prim->hi - prim->lo);
                    if ((node->flags & SN_SECSIZE) != 0) {
                        target = secsize_target(node, len);
                        if (target < len)
                            lnk_warning2("Actual length of section greater than specified size",
                                         sn->name);
                        else if (len < target)
                            prim->hi = M32(prim->hi + (target - len));
                    }
                    if (pass == 2) {
                        for (s = node->secs; s != NULL; s = s->next)
                            sdi_free(s);
                        for (s = node->ovls; s != NULL; s = s->next)
                            sdi_free(s);
                    }
                }
            }
        }
    }
}

/* 40e2bd */
static void fixup_save_counters(void)
{
    int i, align_bufs;
    SECNAME *sn;
    SECNODE *node;
    SECTION *s, *b;
    SDISTAT *st;

    for (i = 0; i < HASHSIZE; i++) {
        for (sn = sec_hash[i]; sn != NULL; sn = sn->hnext) {
            for (node = sn->nodes; node != NULL; node = node->next) {
                align_bufs = 0;
                if (node->spec.mspace == MS_P && node->bufs != NULL &&
                    (node->flags & SN_F40000) == 0)
                    align_bufs = 1;
                node->sv_bufsz = node->bufsz;
                node->sv_bufsz_al = node->bufsz_al;
                for (s = node->secs; s != NULL; s = s->next) {
                    s->sv_lo = s->lo;
                    s->sv_hi = s->hi;
                    st = s->sdi;
                    if (st != NULL && st->n != 0) {
                        if (align_bufs) {
                            s->flags |= SF_ALIGNED;
                            for (b = node->bufs; b != NULL; b = b->next)
                                if ((b->flags & SF_REL) != 0)
                                    b->flags |= SF_ALIGNED | SF_SBALIGN;
                        }
                        st->maxgrowth = 0;
                        st->growth = 0;
                    }
                }
                for (s = node->ovls; s != NULL; s = s->next) {
                    s->sv_lo = s->lo;
                    s->sv_hi = s->hi;
                    st = s->sdi;
                    if (st != NULL && st->n != 0) {
                        st->maxgrowth = 0;
                        st->growth = 0;
                    }
                }
                for (s = node->abss; s != NULL; s = s->next) {
                    s->sv_lo = s->lo;
                    s->sv_hi = s->hi;
                }
                for (s = node->bufs; s != NULL; s = s->next) {
                    s->sv_lo = s->lo;
                    s->sv_hi = s->hi;
                }
            }
        }
    }
}

/* 40e501 */
static void fixup_restore_counters(void)
{
    int i;
    SECNAME *sn;
    SECNODE *node;
    SECTION *s;
    SDISTAT *st;

    for (i = 0; i < HASHSIZE; i++) {
        for (sn = sec_hash[i]; sn != NULL; sn = sn->hnext) {
            for (node = sn->nodes; node != NULL; node = node->next) {
                node->bufsz = node->sv_bufsz;
                node->bufsz_al = node->sv_bufsz_al;
                for (s = node->secs; s != NULL; s = s->next) {
                    s->lo = s->sv_lo;
                    s->hi = s->sv_hi;
                    s->state &= ~SS_ACTIVE;
                    st = s->sdi;
                    if (st != NULL && st->n != 0)
                        s->hi = M32(s->hi + st->maxgrowth);
                }
                for (s = node->abss; s != NULL; s = s->next) {
                    s->lo = s->sv_lo;
                    s->hi = s->sv_hi;
                    s->state &= ~SS_ACTIVE;
                }
                for (s = node->bufs; s != NULL; s = s->next) {
                    s->lo = s->sv_lo;
                    s->hi = s->sv_hi;
                    s->state &= ~SS_ACTIVE;
                }
            }
            for (node = sn->nodes; node != NULL; node = node->next) {
                for (s = node->ovls; s != NULL; s = s->next) {
                    s->lo = s->sv_lo;
                    s->hi = s->sv_hi;
                    s->state &= ~SS_ACTIVE;
                    st = s->sdi;
                    if (st != NULL && st->n != 0) {
                        s->hi = M32(s->hi + st->maxgrowth);
                        s->run->hi = M32(s->run->hi + st->growth);
                    }
                }
            }
        }
    }
}

/* 40e72e: total size of all sections of a memory space/counter (SIZSYM) */
static unsigned long fixup_mem_total(MEMSPEC *spec)
{
    int i;
    SECNAME *sn;
    SECNODE *node;
    unsigned long total, v;

    total = 0;
    for (i = 0; i < HASHSIZE; i++) {
        for (sn = sec_hash[i]; sn != NULL; sn = sn->hnext) {
            for (node = sn->nodes; node != NULL; node = node->next) {
                if (node->spec.mspace == spec->mspace &&
                    node->spec.mcntr == spec->mcntr) {
                    if (!opt_csl)
                        v = node->secs->size != 0 ? node->secs->size
                                                  : node->secs->ovlsize;
                    else
                        v = node->totsize != 0 ? node->totsize : node->totovl;
                    total = M32(total + v);
                }
            }
        }
    }
    return total;
}

/* 40e832 */
static MEMREG **fixup_collect_memregs(REGION *rg)
{
    MEMREG **arr, *m;
    long n;

    if (rg->nmem == 0)
        return NULL;
    arr = (MEMREG **)xmalloc((unsigned long)(rg->nmem + 1) * sizeof(MEMREG *));
    n = 0;
    for (m = rg->mems; m != NULL; m = m->next)
        arr[n++] = m;
    arr[n] = NULL;
    map_sort_memregs(arr, n);
    return arr;
}

/* 40e8ba: the RESERVE ranges assigned to a memreg */
static SECTION **fixup_collect_reserves(MEMREG *mr)
{
    SECTION **arr, *s;
    SECREF *sr;
    long n;

    n = 0;
    for (sr = mr->secs; sr != NULL; sr = sr->next) {
        if (sr->sec->node->sname->num == SN_RESERVE_NUM) {
            n = sr->sec->node->nsecs;
            break;
        }
    }
    if (n == 0)
        return NULL;
    arr = (SECTION **)xmalloc((unsigned long)(n + 1) * sizeof(SECTION *));
    n = 0;
    for (s = sr->sec->node->secs; s != NULL; s = s->next)
        arr[n++] = s;
    arr[n] = NULL;
    map_sort_pieces_num(arr, n);
    return arr;
}

/* 40e981 */
static SECTION **fixup_collect_abs(MEMREG *mr)
{
    SECTION **arr, *s;
    SECREF *sr;
    long n;

    n = 0;
    for (sr = mr->secs; sr != NULL; sr = sr->next)
        n += sr->sec->node->nabss;
    if (n == 0)
        return NULL;
    arr = (SECTION **)xmalloc((unsigned long)(n + 1) * sizeof(SECTION *));
    n = 0;
    for (sr = mr->secs; sr != NULL; sr = sr->next)
        for (s = sr->sec->node->abss; s != NULL; s = s->next)
            arr[n++] = s;
    arr[n] = NULL;
    map_sort_pieces_num(arr, n);
    return arr;
}

/* 40ea59 */
static SECTION **fixup_collect_bufs(MEMREG *mr)
{
    SECTION **arr, *s;
    SECREF *sr;
    long n;

    n = 0;
    for (sr = mr->secs; sr != NULL; sr = sr->next)
        n += sr->sec->node->nbufs;
    if (n == 0)
        return NULL;
    arr = (SECTION **)xmalloc((unsigned long)(n + 1) * sizeof(SECTION *));
    n = 0;
    for (sr = mr->secs; sr != NULL; sr = sr->next)
        for (s = sr->sec->node->bufs; s != NULL; s = s->next)
            arr[n++] = s;
    arr[n] = NULL;
    map_sort_pieces_size(arr, n);
    return arr;
}

/* 40eb31 */
static SECTION **fixup_collect_secs(MEMREG *mr)
{
    SECTION **arr;
    SECREF *sr;
    long n;

    n = 0;
    if (mr->nsecs == 0)
        return NULL;
    arr = (SECTION **)xmalloc((unsigned long)(mr->nsecs + 1) * sizeof(SECTION *));
    for (sr = mr->secs; sr != NULL; sr = sr->next)
        if (sr->sec->node->sname->num != SN_RESERVE_NUM)
            arr[n++] = sr->sec;
    arr[n] = NULL;
    map_sort_pieces_num(arr, n);
    return arr;
}

/* 40ebca */
static void fixup_size_all_sections(void)
{
    int i;
    SECNAME *sn;
    SECNODE *node;
    SECTION *s;

    for (i = 0; i < HASHSIZE; i++)
        for (sn = sec_hash[i]; sn != NULL; sn = sn->hnext)
            for (node = sn->nodes; node != NULL; node = node->next) {
                for (s = node->secs; s != NULL; s = s->next)
                    fixup_size_section(s);
                for (s = node->abss; s != NULL; s = s->next)
                    fixup_size_section(s);
            }
}

/* 40ec8b */
static void fixup_size_section(SECTION *sec)
{
    unsigned long d, sum;
    SECTION *o;
    long i;

    if (sec->size != 0)
        return;
    d = M32(sec->hi - sec->lo);
    if (d == 0) {
        o = sec->node->ovls;
        if (o != NULL) {
            sum = 0;
            for (i = 0; i < sec->node->novls; i++) {
                sum = M32(sum + (o->hi - o->lo));
                o = o->next;
            }
            sec->ovlsize = sum;
            sec->node->totovl = M32(sec->node->totovl + sum);
        }
    } else {
        sec->size = d;
        sec->node->totsize = M32(sec->node->totsize + d);
    }
}

/* 40ed4c: mark a reserve range / absolute piece as used */
static void fixup_mark_abs(SECTION *sec, int mi)
{
    unsigned long lo, hi;

    lo = sec->lo;
    hi = sec->hi;
    fixup_sec_length(sec);
    if (sec->len == 0)
        return;
    fixup_check_bounds(cur_memreg, sec, mi, lo, hi, opt_asc);
    range_add(&used_ranges[mi], lo, hi);
    if (mi > 0) {
        if (mi < MI_L) {
            fixup_check_bounds(cur_memreg, sec, MI_L, lo, hi, opt_asc);
            range_add(&used_ranges[MI_L], lo, hi);
        } else if (mi == MI_L) {
            fixup_check_bounds(cur_memreg, sec, MI_X, lo, hi, opt_asc);
            range_add(&used_ranges[MI_X], lo, hi);
            fixup_check_bounds(cur_memreg, sec, MI_Y, lo, hi, opt_asc);
            range_add(&used_ranges[MI_Y], lo, hi);
        }
    }
    if (!opt_ro && cur_memreg != def_memreg) {
        fixup_check_bounds(def_memreg, sec, mi, lo, hi, opt_asc);
        range_add(&ctr_lists[mi], lo, hi);
        if (mi > 0) {
            if (mi < MI_L) {
                fixup_check_bounds(def_memreg, sec, MI_L, lo, hi, opt_asc);
                range_add(&ctr_lists[MI_L], lo, hi);
            } else if (mi == MI_L) {
                fixup_check_bounds(def_memreg, sec, MI_X, lo, hi, opt_asc);
                range_add(&ctr_lists[MI_X], lo, hi);
                fixup_check_bounds(def_memreg, sec, MI_Y, lo, hi, opt_asc);
                range_add(&ctr_lists[MI_Y], lo, hi);
            }
        }
    }
    if (sec->node->sname->num != SN_RESERVE_NUM) {
        sec->hi = sec->lo;
        sec->state &= ~SS_ACTIVE;
    }
}

/* 40f005 */
static unsigned long fixup_sec_length(SECTION *sec)
{
    unsigned long len;

    len = sec->len;
    if (len == 0) {
        len = M32(sec->hi - sec->lo);
        sec->len = len;
        sec->node->totlen = M32(sec->node->totlen + len);
    }
    return len;
}

/* starting cursor of an allocation */
static RANGE *start_cursor(void)
{
    if (range_saved == NULL || !opt_eso)
        return range_head;
    return range_saved;
}

/* 40f04a */
static void fixup_place_sbalign(SECTION *buf, int mi)
{
    unsigned long len, start, end, align;

    end = 0;
    place_base = buf->node->sbalign;
    start = buf->lo;
    len = fixup_sec_length(buf);
    if (len != 0 && !opt_i) {
        align = (opt_osp == 1) ? 0 : buf->align;
        range_cur = start_cursor();
        start = fixup_alloc_range(len, align, 1, addr_mask);
        end = M32(start + len);
        used_ranges[mi] = range_head;
        fixup_mark_used(buf, mi, start, end, opt_rsc);
    }
    buf->lo = start;
    buf->hi = start;
    buf->state &= ~SS_ACTIVE;
    if (buf->node->spec.mcntr == 0)
        fixup_update_high_water(mi, end);
}

/* 40f17f */
static void fixup_place_at(SECTION *sec, int mi)
{
    unsigned long lo, len, end;

    end = 0;
    lo = sec->lo;
    len = fixup_sec_length(sec);
    if (len != 0) {
        end = M32(lo + len);
        range_add(&used_ranges[mi], lo, end);
        fixup_mark_used(sec, mi, lo, end, opt_asc);
    }
    sec->hi = lo;
    sec->state &= ~SS_ACTIVE;
    if (sec->node->spec.mcntr == 0)
        fixup_update_high_water(mi, end);
}

/* 40f225 */
static void fixup_place_listed(MEMREG *mr, int mi)
{
    SECREF *sr;
    SECTION *s;
    unsigned long len, cursor, end, align;

    end = 0;
    place_base = mr->base;
    cursor = place_base;
    for (sr = mr->secs; sr != NULL; sr = sr->next) {
        s = sr->sec;
        if ((s->state & SS_LISTED) == 0)
            continue;
        len = fixup_sec_length(s);
        if (len != 0 && !opt_i) {
            if (opt_osp == 1 || (s->node->secs->state & SS_NOLALIGN) != 0)
                align = 0;
            else
                align = s->align;
            range_cur = start_cursor();
            cursor = fixup_alloc_range(len, align, 1, addr_mask);
            end = M32(cursor + len);
            used_ranges[mi] = range_head;
            fixup_mark_used(s, mi, cursor, end, opt_rsc);
        }
        s->lo = cursor;
        s->hi = cursor;
        s->state &= ~SS_ACTIVE;
        if (!opt_i)
            cursor = M32(cursor + len);
        if (s->node->spec.mcntr == 0)
            fixup_update_high_water(mi, end);
    }
    range_saved = range_cur;
}

/* 40f3c5 */
static void fixup_place_balign(MEMREG *mr, SECTION **bufs, int mi)
{
    SECTION **pp, *b;
    unsigned long len, cursor, end;

    end = 0;
    cursor = (mr->flags2 & MR2_BALIGN) == 0 ? mr->base : mr->balign;
    place_base = cursor;
    for (pp = bufs; *pp != NULL; pp++) {
        b = *pp;
        if ((b->flags & SF_REL) == 0 || (b->flags & SF_ALIGNED) == 0 ||
            (b->flags & SF_SBALIGN) != 0)
            continue;
        len = fixup_sec_length(b);
        if (len != 0 && !opt_i) {
            range_cur = start_cursor();
            cursor = fixup_alloc_range(len, b->align, 1, addr_mask);
            end = M32(cursor + len);
            used_ranges[mi] = range_head;
            fixup_mark_used(b, mi, cursor, end, opt_rsc);
        }
        b->lo = cursor;
        b->hi = cursor;
        b->state &= ~SS_ACTIVE;
        if (!opt_i)
            cursor = M32(cursor + len);
        if (b->node->spec.mcntr == 0)
            fixup_update_high_water(mi, end);
    }
}

/* 40f58e */
static void fixup_place_default(MEMREG *mr, SECTION **secs, int mi)
{
    SECTION **pp, *s;
    unsigned long len, cursor, end, align;

    end = 0;
    place_base = mr->base;
    cursor = place_base;
    for (pp = secs; *pp != NULL; pp++) {
        s = *pp;
        if ((s->state & (SS_LISTED | SS_ADDR)) != 0)
            continue;
        len = fixup_sec_length(s);
        if (len != 0 && !opt_i) {
            if (opt_osp == 1 || (s->node->secs->state & SS_NOLALIGN) != 0)
                align = 0;
            else
                align = s->align;
            range_cur = start_cursor();
            cursor = fixup_alloc_range(len, align, 1, addr_mask);
            end = M32(cursor + len);
            used_ranges[mi] = range_head;
            fixup_mark_used(s, mi, cursor, end, opt_rsc);
        }
        s->lo = cursor;
        s->hi = cursor;
        s->state &= ~SS_ACTIVE;
        if (!opt_i)
            cursor = M32(cursor + len);
        if (s->node->spec.mcntr == 0)
            fixup_update_high_water(mi, end);
    }
}

/* 40f722 */
static void fixup_update_high_water(int mi, unsigned long end)
{
    if (mi == MI_X && high_water[MI_X] < end) {
        high_water[MI_X] = end;
        if (high_water[MI_L] < end)
            high_water[MI_L] = end;
    } else if (mi == MI_Y && high_water[MI_Y] < end) {
        high_water[MI_Y] = end;
        if (high_water[MI_L] < end)
            high_water[MI_L] = end;
    } else if (mi == MI_L) {
        if (high_water[MI_X] < end)
            high_water[MI_X] = end;
        if (high_water[MI_Y] < end)
            high_water[MI_Y] = end;
        if (high_water[MI_L] < end)
            high_water[MI_L] = end;
    }
    if (mi == MI_P && high_water[MI_P] < end)
        high_water[MI_P] = end;
    if (mi == MI_E && high_water[MI_E] < end)
        high_water[MI_E] = end;
    if (!cc_objects) {
        if (mi != MI_P && mi != MI_E && dsize_high < end)
            dsize_high = end;
    } else if ((long)mi == stack_mspace && dsize_high < end) {
        dsize_high = end;
    }
}

/* 40f868 */
static void fixup_mark_used(SECTION *sec, int mi, unsigned long lo,
                            unsigned long hi, int report)
{
    fixup_check_bounds(cur_memreg, sec, mi, lo, hi, report);
    if (!opt_ro && cur_memreg != def_memreg)
        range_add(&ctr_lists[mi], lo, hi);
    if (mi == MI_X || mi == MI_Y) {
        fixup_check_bounds(cur_memreg, sec, MI_L, lo, hi, report);
        range_add(&used_ranges[MI_L], lo, hi);
        if (!opt_ro && cur_memreg != def_memreg) {
            fixup_check_bounds(def_memreg, sec, MI_L, lo, hi, report);
            range_add(&ctr_lists[MI_L], lo, hi);
        }
    } else if (mi == MI_L) {
        fixup_check_bounds(cur_memreg, sec, MI_X, lo, hi, report);
        range_add(&used_ranges[MI_X], lo, hi);
        fixup_check_bounds(cur_memreg, sec, MI_Y, lo, hi, report);
        range_add(&used_ranges[MI_Y], lo, hi);
        if (!opt_ro && cur_memreg != def_memreg) {
            fixup_check_bounds(def_memreg, sec, MI_X, lo, hi, report);
            range_add(&ctr_lists[MI_X], lo, hi);
            fixup_check_bounds(def_memreg, sec, MI_Y, lo, hi, report);
            range_add(&ctr_lists[MI_Y], lo, hi);
        }
    }
}

/* place_base aligned to align (buf_align) */
static unsigned long aligned(unsigned long addr, unsigned long align,
                             unsigned long mask)
{
    if (align == 0)
        return addr;
    return buf_align(addr, align, mask);
}

/* 40fa6c: first fit of len words at or above place_base in the used-range
   list, searching from range_cur; commit records the allocation */
static unsigned long fixup_alloc_range(unsigned long len, unsigned long align,
                                       int commit, unsigned long mask)
{
    unsigned long base, start, end;
    RANGE *c, *merged_prev;
    int found;

    base = aligned(place_base, align, mask);
    start = base;
    end = M32(base + len);
    if (range_cur == NULL) {
        if (commit)
            range_cur = range_insert(NULL, base, end);
    } else if (range_cur == range_head && base < range_cur->lo &&
               len <= M32(range_cur->lo - base)) {
        if (commit) {
            if (end == range_cur->lo)
                range_cur->lo = base;
            else
                range_cur = range_insert(NULL, base, end);
        }
    } else {
        c = range_cur->next;
        found = 0;
        merged_prev = NULL;
        while (c != NULL && !found) {
            if (len <= M32(c->lo - range_cur->hi) && end <= c->lo) {
                if (start < range_cur->hi) {
                    start = range_cur->hi;
                    end = M32(start + len);
                    if (align != 0) {
                        start = buf_align(start, align, mask);
                        end = M32(start + len);
                        if (c->lo < end)
                            goto next;
                    }
                }
                found = 1;
                if (commit) {
                    if (start == range_cur->hi && end == c->lo) {
                        /* fill the gap: merge c into range_cur */
                        range_cur->hi = c->hi;
                        range_cur->next = c->next;
                        if (range_cur->next != NULL)
                            range_cur->next->prev = range_cur;
                        /* original: range_cur = c (freed), c = c->next,
                           then range_cur = range_cur->prev (read from the
                           freed node; may be stale, range_insert does not
                           update the successor's prev) */
                        merged_prev = c->prev != NULL ? c->prev : range_cur;
                        xfree(c);
                        range_cur = merged_prev;
                        break;
                    } else if (start == range_cur->hi) {
                        range_cur->hi = end;
                    } else if (end == c->lo) {
                        c->lo = start;
                    } else {
                        range_insert(range_cur, start, end);
                    }
                }
            }
        next:
            range_cur = c;
            c = c->next;
        }
        if (found) {
            if (merged_prev == NULL && range_cur->prev != NULL)
                range_cur = range_cur->prev;
        } else {
            start = base;
            if (base < range_cur->hi)
                start = aligned(range_cur->hi, align, mask);
            end = M32(start + len);
            if (range_cur->hi < start) {
                if (commit)
                    range_cur = range_insert(range_cur, start, end);
            } else if (commit) {
                range_cur->hi = end;
            }
        }
    }
    return start;
}

/* 40fdb9 */
static RANGE *range_insert(RANGE *after, unsigned long lo, unsigned long hi)
{
    RANGE *r;

    r = (RANGE *)xmalloc(sizeof(RANGE));
    r->unk_0 = 0;
    r->lo = lo;
    r->hi = hi;
    if (after == NULL) {
        r->prev = NULL;
        if (range_head == NULL) {
            range_head = r;
            r->next = NULL;
        } else {
            r->next = range_head;
            range_head->prev = r;
            range_head = r;
        }
    } else {
        r->next = after->next;
        after->next = r;
        r->prev = after;
    }
    return r;
}

/* 40fe58: sorted insert with merging */
static void range_add(RANGE **head, unsigned long lo, unsigned long hi)
{
    RANGE *r, *p, *prev;

    prev = NULL;
    r = (RANGE *)xmalloc(sizeof(RANGE));
    r->unk_0 = 0;
    r->lo = lo;
    r->hi = hi;
    r->next = NULL;
    r->prev = NULL;
    for (p = *head; p != NULL && p->lo < r->lo; p = p->next)
        prev = p;
    if (p == NULL) {
        if (prev == NULL)
            *head = r;
        else
            range_merge(prev, r, NULL);
    } else if (p == *head) {
        *head = range_merge(NULL, r, p);
    } else {
        range_merge(prev, r, p);
    }
}

/* 40ff2c */
static RANGE *range_merge(RANGE *prev, RANGE *node, RANGE *next)
{
    RANGE *t;

    if (node->lo < node->hi) {
        if (prev != NULL) {
            if (prev->hi < node->lo) {
                node->prev = prev;
                prev->next = node;
            } else {
                if (prev->hi < node->hi)
                    prev->hi = node->hi;
                xfree(node);
                node = prev;
            }
        }
        if (next != NULL) {
            while (next != NULL && next->hi < node->hi) {
                node->next = next->next;
                t = node->next;
                xfree(next);
                next = t;
            }
            if (next != NULL) {
                if (node->hi < next->lo) {
                    node->next = next;
                    next->prev = node;
                } else {
                    node->hi = next->hi;
                    node->next = next->next;
                    if (next->next != NULL)
                        next->next->prev = node;
                    xfree(next);
                }
            }
        }
    } else {
        xfree(node);
        node = next;
        if (prev != NULL)
            node = prev;
    }
    return node;
}

/* create one of the size symbols in section GLOBAL of the given space */
static SYM *size_sym(char *name, long mspace)
{
    SYM tmpl, *s;
    MEMSPEC spec;

    s = sym_lookup(name, 0);
    if (s != NULL)
        return s;
    memset(&tmpl, 0, sizeof(tmpl));
    tmpl.mem.mspace = MS_N;
    tmpl.mem.mmap = MS_N;
    tmpl.mem.mcntr = 0;
    tmpl.mem.mclass = 0;
    spec.mspace = mspace;
    spec.mmap = mspace;
    spec.mcntr = 0;
    spec.mclass = 0;
    cur_section = sec_lookup_create(global_secname, global_secno, &spec, 0);
    tmpl.name = name;
    tmpl.fval = 0.0;
    tmpl.hi = 0;
    tmpl.lo = 0;
    tmpl.unk_14 = 0;
    tmpl.sfval = 0.0;
    tmpl.flags = SYM_GLOBAL | SYM_INT;
    tmpl.cls_off = 0;
    tmpl.osec = NULL;
    tmpl.smap = NULL;
    tmpl.buf = NULL;
    tmpl.ovl = NULL;
    tmpl.next = NULL;
    cur_rsection = cur_section;
    tmpl.sec = cur_section;
    tmpl.rsec = cur_section;
    if (sym_enter(&tmpl) == NULL)
        return NULL;
    return sym_lookup(name, 0);
}

/* 41006f: DSIZE XSIZE YSIZE LSIZE PSIZE */
static int fixup_size_symbols(void)
{
    SYM *d, *x, *y, *l, *p;

    if ((d = size_sym("DSIZE", MS_X)) == NULL)
        return 0;
    if ((x = size_sym("XSIZE", MS_X)) == NULL)
        return 0;
    if ((y = size_sym("YSIZE", MS_Y)) == NULL)
        return 0;
    if ((l = size_sym("LSIZE", MS_L)) == NULL)
        return 0;
    if ((p = size_sym("PSIZE", MS_P)) == NULL)
        return 0;
    d->lo = M32(d->lo + dsize_high);
    x->lo = M32(x->lo + high_water[MI_X]);
    y->lo = M32(y->lo + high_water[MI_Y]);
    l->lo = M32(l->lo + high_water[MI_L]);
    p->lo = M32(p->lo + high_water[MI_P]);
    cur_rsection = NULL;
    cur_section = NULL;
    return 1;
}

/* 410668 */
static void fixup_place_overlays(void)
{
    INFILE *inf;
    MODULE *m;
    OVLENT *ent;
    SECTION *sec;
    EXPR *e;
    SYM *sym;
    SDISTAT *st;
    unsigned long len;
    long i;
    int mi, h;

    for (inf = infile_head; inf != NULL; inf = inf->next) {
        cur_infile = inf;
        m = inf->members != NULL ? inf->members : inf->module;
        for (; m != NULL; m = m->next) {
            for (i = 1; i <= m->lh.ovlcnt; i++) {
                if (m->ovltab == NULL || m->ovltab[i].baseexpr == NULL)
                    continue;
                mod_ovltab = m->ovltab;
                cur_overlay = i;
                ent = &mod_ovltab[i];
                sec = ent->sec;
                if (sec == NULL)
                    continue;
                mi = mem_space_index(sec->node->spec.mspace);
                cur_section = ent->lsec;
                cur_secid = cur_section->node->sname->num;
                cur_rsection = ent->rsec;
                cur_rsecid = cur_rsection->node->sname->num;
                cur_memreg = cur_rsection->node->memreg;
                cur_region = cur_memreg->region;
                input_cursor = ent->baseexpr;
                e = abi_expr_eval(m, 0L, input_cursor);
                if (e == NULL && (e = eval_int()) == NULL)
                    continue;
                if (e->sect < 0) {
                    lnk_error1("Unresolved overlay base address");
                } else if ((e->flags & EXPR_OVL) == 0) {
                    len = M32(sec->hi - sec->lo);
                    sec->hi = e->lo;
                    sec->lo = sec->hi;
                    sec->hi = M32(sec->hi + len);
                    fixup_check_bounds(cur_memreg, sec, mi, sec->lo, sec->hi, opt_asc);
                    sec->state |= SS_ACTIVE;
                    sec->node->memreg->flags2 |= MR2_OVLLOC;
                    free_expr(e);
                } else {
                    lnk_error1("Invalid overlay base address");
                }
            }
        }
    }
    cur_infile = NULL;
    cur_rsection = NULL;
    cur_section = NULL;
    cur_region = region_head;
    cur_memreg = NULL;
    mod_ovltab = NULL;
    cur_overlay = 0;
    cur_rsecid = 0;
    cur_secid = 0;
    fixup_place_ovl_all();
    if (!sdi_active || !sdi_changed) {
        for (h = 0; h < HASHSIZE; h++) {
            for (sym = sym_hash[h]; sym != NULL; sym = sym->next) {
                if ((sym->flags & (SYM_OVERLAY | SYM_REL | SYM_INT)) !=
                    (SYM_OVERLAY | SYM_REL | SYM_INT))
                    continue;
                if (opt_aec &&
                    merge_mem_space(sym->mem.mspace,
                                    sym->ovl->sec->node->spec.mspace) == MS_BAD) {
                    lnk_error1("Overlay address involves incompatible memory spaces");
                    continue;
                }
                if (sdi_active) {
                    sym->fval = sym->sfval;
                    sym->hi = sym->shi;
                    sym->lo = sym->slo;
                    sym->unk_14 = sym->sunk_14;
                }
                sym->lo = M32(sym->lo + sym->ovl->grp->lo);
                st = sym->ovl->sec->sdi;
                if (sym->sdi_cnt != 0 && st != NULL && st->recs != NULL)
                    sym->lo = M32(sym->lo + st->recs[sym->sdi_cnt - 1].growth);
            }
        }
    }
}

/* 410a84 */
static void fixup_place_ovl_all(void)
{
    REGION *rg;
    MEMREG **mrs, **mrp, *mr;
    SECTION **ovls, **pp;
    long lastspace;
    int mi;

    lastspace = MS_N;
    mi = 0;
    if (region_last == NULL)
        for (rg = region_head; rg != NULL; rg = rg->next)
            region_last = rg;
    region_last->next = region_head;
    for (rg = region_head->next; rg != NULL; rg = rg->next) {
        cur_region = rg;
        mrs = fixup_collect_memregs(rg);
        for (mrp = mrs; mrp != NULL && *mrp != NULL; mrp++) {
            mr = *mrp;
            cur_memreg = mr;
            if ((mr->flags2 & MR2_OVL) == 0)
                continue;
            if (mr->spec.mspace != lastspace) {
                lastspace = mr->spec.mspace;
                mi = mem_space_index(lastspace);
            }
            ovls = fixup_collect_ovls(mr);
            if (ovls == NULL)
                continue;
            mr->ovlcur = mr->base;
            if ((mr->flags2 & MR2_OVLLOC) != 0)
                fixup_ovl_after_located(mr, ovls, mi);
            if ((mr->flags2 & MR2_ADDR) != 0)
                fixup_ovl_after_section(mr, ovls, mi);
            if ((mr->flags2 & MR2_LISTED) != 0)
                fixup_ovl_listed(mr, ovls, mi);
            fixup_ovl_default(mr, ovls, mi);
            for (pp = ovls; *pp != NULL; pp++)
                (*pp)->hi = (*pp)->lo;
            xfree(ovls);
        }
        if (rg == region_head) {
            rg = region_last;
            region_last->next = NULL;
        }
        xfree(mrs);
    }
}

/* 410c8b */
static SECTION **fixup_collect_ovls(MEMREG *mr)
{
    SECTION **arr, *s;
    SECREF *sr;
    long n, total;

    n = 0;
    total = 0;
    arr = (SECTION **)xmalloc(sizeof(SECTION *));
    for (sr = mr->secs; sr != NULL; sr = sr->next) {
        if (sr->sec->node->novls != 0) {
            total += sr->sec->node->novls;
            arr = (SECTION **)xrealloc(arr, (unsigned long)(total + 1) * sizeof(SECTION *));
            for (s = sr->sec->node->ovls; s != NULL; s = s->next)
                arr[n++] = s;
        }
    }
    if (total == 0) {
        xfree(arr);
        return NULL;
    }
    arr[n] = NULL;
    map_sort_pieces_num(arr, n);
    return arr;
}

/* one overlay piece placed at cursor: SDI offsets, bounds, group leader */
static void ovl_place(MEMREG *mr, SECTION *s, int mi, unsigned long cursor,
                      unsigned long len, long *acc, SECTION **lead,
                      MODULE **stamp, int report)
{
    SDISTAT *st;

    s->lo = cursor;
    s->ovl->sdioff = *acc;
    st = s->sdi;
    if (st != NULL && st->n != 0 && st->recs != NULL) {
        *acc += last_growth(st);
        if (s->ovl->marker != NULL)
            s->ovl->marker->opsz2 = last_growth(st);
    }
    fixup_check_bounds(mr, s, mi, cursor, M32(cursor + len), report);
    if ((s->flags & SF_OVLNEW) == 0 && s->ovl->module == *stamp) {
        s->ovl->grp = *lead;
    } else {
        *stamp = s->ovl->module;
        *lead = s;
    }
    s->state |= SS_ACTIVE;
}

/* 410d70: overlays following a located overlay of the same section */
static void fixup_ovl_after_located(MEMREG *mr, SECTION **ovls, int mi)
{
    SECTION **p, **q, **prevp, *lead, *s;
    MODULE *stamp;
    unsigned long cursor, len;
    long acc, num;
    SDISTAT *st;

    stamp = NULL;
    p = ovls;
    for (;;) {
        if (*p == NULL)
            return;
        lead = *p;
        if ((lead->state & SS_ACTIVE) != 0) {
            cursor = lead->hi;
            acc = 0;
            st = lead->sdi;
            if (st != NULL && st->n != 0 && st->recs != NULL &&
                lead->ovl->marker != NULL)
                lead->ovl->marker->opsz2 = last_growth(st);
            num = lead->node->sname->num;
            for (;;) {
                prevp = p;
                p = prevp + 1;
                s = *p;
                q = p;
                if (s == NULL)
                    break;
                if (((lead->flags & SF_REL) == 0) == ((s->flags & SF_REL) == 0)) {
                    q = prevp;
                    if ((s->state & SS_ACTIVE) != 0 || s->node->sname->num != num)
                        break;
                    len = M32(s->hi - s->lo);
                    ovl_place(mr, s, mi, cursor, len, &acc, &lead, &stamp, opt_asc);
                    cursor = M32(cursor + len);
                }
            }
            p = q;
            if (*p == NULL)
                return;
        }
        p++;
    }
}

/* 410fe8: overlays of a section with an explicit address follow it */
static void fixup_ovl_after_section(MEMREG *mr, SECTION **ovls, int mi)
{
    SECTION **p, *lead, *s;
    MODULE *stamp;
    unsigned long cursor, len;
    long acc, num;

    stamp = NULL;
    p = ovls;
    for (;;) {
        if (*p == NULL)
            return;
        lead = *p;
        if ((lead->flags & SF_REL) != 0 && (lead->state & SS_ACTIVE) == 0) {
            num = lead->node->sname->num;
            if ((lead->node->secs->state & SS_ADDR) != 0) {
                cursor = lead->node->secs->hi;
                acc = 0;
                for (; (s = *p) != NULL; p++) {
                    if ((s->flags & SF_REL) != 0 && (s->state & SS_ACTIVE) == 0) {
                        if (s->node->sname->num != num) {
                            p--;
                            break;
                        }
                        len = M32(s->hi - s->lo);
                        ovl_place(mr, s, mi, cursor, len, &acc, &lead, &stamp, opt_asc);
                        cursor = M32(cursor + len);
                    }
                }
                if (*p == NULL)
                    return;
            }
        }
        p++;
    }
}

/* 411200: overlays of SECTION-listed sections at the memreg cursor */
static void fixup_ovl_listed(MEMREG *mr, SECTION **ovls, int mi)
{
    SECREF *sr;
    SECTION **p, *lead, *s;
    MODULE *stamp;
    unsigned long cursor, len;
    long acc, num;

    lead = NULL;
    stamp = NULL;
    cursor = mr->ovlcur;
    for (sr = mr->secs; sr != NULL; sr = sr->next) {
        if ((sr->sec->state & SS_LISTED) == 0)
            continue;
        num = sr->sec->node->sname->num;
        p = ovls;
        while (*p != NULL && (*p)->node->sname->num < num)
            p++;
        if (*p != NULL)
            lead = *p;
        acc = 0;
        while ((s = *p) != NULL && s->node->sname->num == num) {
            if ((s->flags & SF_REL) != 0 && (s->state & SS_ACTIVE) == 0) {
                len = M32(s->hi - s->lo);
                if (s->ovl->maxbuf != 0)
                    cursor = buf_align(cursor, s->ovl->maxbuf, addr_mask);
                ovl_place(mr, s, mi, cursor, len, &acc, &lead, &stamp, opt_rsc);
                cursor = M32(cursor + len);
            }
            p++;
        }
    }
    mr->ovlcur = cursor;
}

/* 411450: all remaining relocatable overlays at the memreg cursor */
static void fixup_ovl_default(MEMREG *mr, SECTION **ovls, int mi)
{
    SECTION **p, *lead, *s;
    MODULE *stamp;
    unsigned long cursor, len;
    long acc;

    lead = NULL;
    stamp = NULL;
    cursor = mr->ovlcur;
    acc = 0;
    for (p = ovls; (s = *p) != NULL; p++) {
        if ((s->flags & SF_REL) != 0 && (s->state & SS_ACTIVE) == 0) {
            len = M32(s->hi - s->lo);
            ovl_place(mr, s, mi, cursor, len, &acc, &lead, &stamp, opt_rsc);
            cursor = M32(cursor + len);
        }
    }
    mr->ovlcur = cursor;
}

/* 4115dd */
static void fixup_check_bounds(MEMREG *mr, SECTION *sec, int mi,
                               unsigned long lo, unsigned long hi, int report)
{
    char buf[1200];             /* original: 1024 */
    char *kind, *name;
    long space;
    MEMREG *m;
    unsigned long end;

    kind = "Relative";
    if (!report)
        return;
    space = index_mem_space(mi);
    for (m = mr->region->mems; m != NULL; m = m->next)
        if (m->spec.mspace == space && m->spec.mcntr == sec->node->spec.mcntr)
            break;
    if (m == NULL)
        return;
    if ((sec->flags & SF_BUF) != 0)
        kind = "Buffer";
    else if ((sec->flags & SF_OVL) != 0)
        kind = "Overlay";
    else if ((sec->flags & SF_REL) == 0)
        kind = "Absolute";
    name = sec->node->sname->name;
    if (lo < m->base) {
        sprintf(buf, "%s section \"%s\" %c(%ld) start address $%lX less than region %s base address of $%lX",
                kind, name, mem_idx_char[mi], m->spec.mcntr, lo,
                m->region->name, m->base);
        lnk_error1(buf);
    }
    end = hi == 0 ? 0 : M32(hi - 1);
    if (m->high < end) {
        sprintf(buf, "%s section \"%s\" %c(%ld) end address $%lX greater than region %s maximum address of $%lX",
                kind, name, mem_idx_char[mi], m->spec.mcntr, end,
                m->region->name, m->high);
        lnk_error1(buf);
    }
}
