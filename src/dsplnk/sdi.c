/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), sdi.c
 * $Id: sdi.c,v 1.12 1995/02/21 22:25:48 tomc Exp $
 * Reconstructed from DSPLNK.EXE 0042a300-0042b734.
 *
 * Span-dependent instructions: pass 1 records every SDI of a section
 * (sdi_add), fixup_relocate repeatedly resolves their targets and chooses
 * short / medium / long forms until the growth converges; pass 2 reads the
 * chosen forms back in input order (sdi_next_form).  Hidden option -j;
 * the original crashes in several configurations - translated faithfully.
 */
#include "dsplnk.h"

static void sdi_build(SDISTAT *st);
static void sdi_converge(SDISTAT *st);
static int sdi_target(SDISTAT *st, SDIPIECE *p, unsigned long *val);

/* 42a300 */
void sdi_stats_new(SECTION *sec)
{
    SDISTAT *st;

    st = (SDISTAT *)xmalloc(sizeof(SDISTAT));
    st->mod_count = 0;
    st->mod_first = 0;
    st->maxgrowth = 0;
    st->growth = 0;
    st->n_saved = 0;
    st->n = 0;
    st->unk_18 = 0;
    st->owner = sec;
    st->stamp = cur_infile->module;
    st->pieces = NULL;
    st->recs = NULL;
    sec->sdi = st;
}

/* 42a38f */
void sdi_add(unsigned long addr, unsigned long orig, char *expr, long opsz,
             long opsz2, unsigned long flags, long alt1, long alt2)
{
    SDIPIECE *p, *m;
    SECNEST *copy, *last, *n;
    SDISTAT *rst;

    copy = NULL;
    p = (SDIPIECE *)xmalloc(sizeof(SDIPIECE));
    p->addr2 = addr;
    p->addr = addr;
    p->orig = orig;
    p->opsz = opsz;
    p->opsz2 = opsz2;
    p->alt1 = alt1;
    p->alt2 = alt2;
    p->flags = flags;
    if (expr == NULL) {
        p->bufoff = 0;
        p->expr = NULL;
        p->text = NULL;
        p->flags |= SDI_NOEXPR;
        p->infile = NULL;
        p->lsec = NULL;
        p->msec = NULL;
        p->ovl = NULL;
        p->nest = NULL;
        p->next = cur_alloc->sdi->pieces;
        cur_alloc->sdi->pieces = p;
        cur_alloc->sdi->n++;
        return;
    }
    p->bufoff = cur_rsection->node->bufsz;
    p->expr = expr;
    p->text = input_cursor + 1;
    if (run_reloc != 0)
        p->flags |= SDI_OVLLR;
    p->infile = cur_infile;
    p->lsec = cur_section;
    if (nested_secs && sec_nest != NULL) {
        copy = (SECNEST *)xmalloc(sizeof(SECNEST));
        copy->id = sec_nest->id;
        copy->next = NULL;
        last = copy;
        for (n = sec_nest->next; n != NULL; n = n->next) {
            last->next = (SECNEST *)xmalloc(sizeof(SECNEST));
            last = last->next;
            last->id = n->id;
            last->next = NULL;
        }
    }
    p->nest = copy;
    p->msec = cur_rmsec;
    p->ovl = (ovl_mem.mspace == MS_N) ? NULL : &mod_ovltab[cur_overlay];
    p->next = cur_alloc->sdi->pieces;
    cur_alloc->sdi->pieces = p;
    cur_alloc->sdi->n++;
    if (run_ctr != load_ctr) {
        if (cur_rsection->sdi == NULL)
            sdi_stats_new(cur_rsection);
        rst = cur_rsection->sdi;
        if (rst->pieces == NULL || (rst->pieces->flags & SDI_MARK) == 0 ||
            rst->pieces->ovl != &mod_ovltab[cur_overlay]) {
            /* marker piece: carries the growth base of the overlay */
            m = (SDIPIECE *)xmalloc(sizeof(SDIPIECE));
            m->addr2 = 0;
            m->addr = 0;
            m->orig = 0;
            m->opsz = 0;
            m->opsz2 = 0;
            m->alt1 = 0;
            m->alt2 = 0;
            m->bufoff = 0;
            m->expr = NULL;
            m->text = NULL;
            m->flags = flags | SDI_MARK;
            m->infile = NULL;
            m->lsec = NULL;
            m->msec = NULL;
            m->ovl = &mod_ovltab[cur_overlay];
            m->nest = NULL;
            m->next = rst->pieces;
            mod_ovltab[cur_overlay].marker = m;
            rst->pieces = m;
        }
    }
}

/* 42a767: pass 2 - form of the next SDI of cur_alloc: 2 long, 1 medium,
   0 short (2 as well when the section has no SDI records) */
int sdi_next_form(void)
{
    SDISTAT *st;
    SDIREC *r;
    int form;

    st = cur_alloc->sdi;
    if (st == NULL)
        return 2;
    r = &st->recs[st->n];
    st->n++;
    if ((r->flags & SDI_LONG) == 0)
        form = (r->flags & SDI_MED) != 0;
    else
        form = 2;
    if ((r->flags & SDI_LONG) != 0) {
        obj_nwords++;
        cur_sectref->hdr->s_size++;
        if (run_ctr != load_ctr)
            cur_rsection->node->sdigrow++;
    }
    return form;
}

/* one SECTION of sdi_resolve_all */
static void sdi_resolve_sec(SECTION *s)
{
    SDISTAT *st;

    st = s->sdi;
    if (st == NULL || st->n == 0)
        return;
    if (st->recs != NULL) {
        xfree(st->recs);
        st->recs = NULL;
    }
    st->growth = 0;
    sdi_build(st);
    sdi_converge(st);
    sdi_total += st->growth;
    if (st->maxgrowth < st->growth) {
        st->maxgrowth = st->growth;
        sdi_changed = 1;
    }
}

/* 42a84c */
void sdi_resolve_all(void)
{
    int i;
    SECNAME *sn;
    SECNODE *node;
    SECTION *s;

    sdi_total = 0;
    for (i = 0; i < HASHSIZE; i++)
        for (sn = sec_hash[i]; sn != NULL; sn = sn->hnext)
            for (node = sn->nodes; node != NULL; node = node->next) {
                for (s = node->secs; s != NULL; s = s->next)
                    sdi_resolve_sec(s);
                for (s = node->ovls; s != NULL; s = s->next)
                    sdi_resolve_sec(s);
            }
}

/* 42aa32: records in input order (the piece list is reversed) */
static void sdi_build(SDISTAT *st)
{
    SECTION *owner;
    SDIPIECE *p;
    SDIREC *r;
    long k;
    unsigned long val;

    owner = st->owner;
    st->recs = (SDIREC *)xmalloc((unsigned long)(st->n + 1) * sizeof(SDIREC));
    k = st->n - 1;
    for (p = st->pieces; p != NULL; p = p->next) {
        if ((p->flags & SDI_MARK) != 0 && p != st->pieces) {
            /* a marker between records: growth base of the next record */
            st->recs[k + 1].flags |= SDI_MARK;
            st->recs[k + 1].growth = p->opsz2;
            continue;
        }
        /* the list head marker takes the spare slot recs[n] */
        r = ((p->flags & SDI_MARK) != 0) ? &st->recs[k + 1] : &st->recs[k];
        r->addr = p->addr;
        r->orig = p->orig;
        r->growth = 0;
        r->disp = 0;
        r->value = 0;
        r->opsz = p->opsz;
        r->opsz2 = p->opsz2;
        r->flags = p->flags;
        r->alt1 = p->alt1;
        r->alt2 = p->alt2;
        r->text = p->text;
        if ((owner->flags & SF_REL) != 0) {
            if ((owner->flags & SF_OVL) == 0) {
                if ((owner->flags & SF_ALIGNED) == 0)
                    r->addr = M32(r->addr + owner->lo);
                else
                    r->addr = M32(r->addr + (owner->lo - p->bufoff));
            } else {
                r->addr = M32(r->addr + p->ovl->grp->lo);
            }
        }
        suppress_errors = 1;
        if (!sdi_target(st, p, &val)) {
            suppress_errors = 0;
            if (p->expr != NULL)
                r->flags |= SDI_UNRES;
        } else {
            suppress_errors = 0;
            r->value = val;
            if (target_index == TGT_96000 || target_index == TGT_56100)
                r->disp = M32(r->value - (r->addr + 1));
            else
                r->disp = M32(r->value - r->addr);
        }
        if ((p->flags & SDI_MARK) == 0)
            k--;
    }
}

/* 42ac5f: choose the forms until nothing changes, then accumulate growth */
static void sdi_converge(SDISTAT *st)
{
    int done, ok, fv, fd, fd2;
    long i, j;
    SDIREC *r, *o;

    done = 0;
    while (!done) {
        done = 1;
        for (i = 0; i < st->n; i++) {
            r = &st->recs[i];
            if ((r->flags & SDI_NOEXPR) != 0 || (r->flags & SDI_LONG) != 0)
                continue;
            fv = opsize_fits(r->value, r->opsz);
            fd = opsize_fits(r->disp, r->opsz);
            fd2 = (r->opsz2 == 0) ? 0 : opsize_fits(r->disp, r->opsz2);
            ok = 0;
            if ((r->flags & SDI_ABS) == 0 || !fv) {
                if ((r->flags & SDI_ABS) == 0 && (r->flags & SDI_REL) != 0 && fd)
                    ok = 1;
                else if ((r->flags & (SDI_ABS | SDI_REL)) != 0 && fd2)
                    ok = 1;
            } else {
                ok = 1;
            }
            if (!opt_sdi || !ok) {
                done = 0;
                r->flags |= SDI_LONG;
                r->flags &= ~SDI_MED;
                for (j = 0; j < st->n; j++) {
                    if (j == i)
                        continue;
                    o = &st->recs[j];
                    if ((o->flags & SDI_UNRES) != 0)
                        continue;
                    if (r->addr < o->addr || o->value <= r->addr) {
                        if (o->value <= r->addr && r->addr < o->addr)
                            o->disp = M32(o->disp - 1);
                    } else {
                        o->disp = M32(o->disp + 1);
                    }
                }
            }
            if ((r->flags & (SDI_ABS | SDI_REL)) != 0 && (r->flags & SDI_LONG) == 0 &&
                !fv && fd2)
                r->flags |= SDI_MED;
        }
    }
    r = &st->recs[0];
    if ((r->flags & SDI_NOEXPR) == 0 && (r->flags & SDI_LONG) != 0) {
        r->growth++;
        st->growth++;
    }
    for (i = 1; i < st->n; i++) {
        r = &st->recs[i];
        if ((r->flags & SDI_NOEXPR) != 0)
            continue;
        if ((r->flags & SDI_LONG) == 0) {
            if ((r->flags & SDI_MARK) == 0)
                r->growth = st->recs[i - 1].growth;
            else
                r->growth += st->recs[i - 1].growth;
        } else {
            if ((r->flags & SDI_MARK) == 0)
                r->growth = st->recs[i - 1].growth + 1;
            else
                r->growth += 1 + st->recs[i - 1].growth;
            st->growth++;
        }
    }
}

/* 42b005: value of the target of an SDI; 0 = unresolved */
static int sdi_target(SDISTAT *st, SDIPIECE *p, unsigned long *val)
{
    char *s, *d;
    SECTION *owner;
    SECTION *b;
    unsigned long sum;
    SYM *sym;
    int c;

    s = p->expr;
    if (s == NULL)
        return 0;
    c = (unsigned char)*s;
    if (c < 0x80 && isalpha(c)) {
        /* symbol: look it up in the context of the SDI (globals stay set) */
        cur_infile = p->infile;
        cur_section = p->lsec;
        sec_nest = p->nest != NULL ? p->nest : NULL;
        nested_secs = p->nest != NULL;
        sym = sym_lookup(s, 0);
        if (sym == NULL)
            return 0;
        *val = sym->lo;
        return 1;
    }
    d = strchr(s, '$');
    if (d == NULL) {
        lnk_error1("Syntax error in expression");
        return 0;
    }
    sscanf(d, "$%lx,", val);
    if (p->ovl == NULL) {
        owner = st->owner;
        if ((owner->flags & SF_ALIGNED) == 0) {
            *val = M32(*val + owner->lo + p->msec->base);
        } else {
            sum = 0;
            for (b = owner->node->bufs; b != NULL; b = b->next)
                if (b->bufaddr <= *val)
                    sum = M32(sum + b->bufspan);
            *val = M32(*val + ((owner->lo + p->msec->base_raw) - sum));
        }
    } else {
        *val = M32(*val + p->ovl->grp->lo);
    }
    return 1;
}

/* free the piece list of a SDISTAT */
static void sdi_free_pieces(SDISTAT *st)
{
    SDIPIECE *p, *pn;
    SECNEST *n, *nn;

    p = st->pieces;
    while (p != NULL) {
        if (p->expr != NULL)
            xfree(p->expr);
        n = p->nest;
        while (n != NULL) {
            nn = n->next;
            xfree(n);
            n = nn;
        }
        pn = p->next;
        xfree(p);
        p = pn;
    }
}

/* 42b1d5 */
void sdi_free(SECTION *sec)
{
    SDISTAT *st;

    st = sec->sdi;
    if (st == NULL)
        return;
    sdi_free_pieces(st);
    if (st->recs != NULL)
        xfree(st->recs);
    xfree(st);
    sec->sdi = NULL;
}

/* reset of one SECTION (sdi_reset_all) */
static void sdi_reset_sec(SECTION *s)
{
    SDISTAT *st;

    st = s->sdi;
    if (st == NULL)
        return;
    sdi_free_pieces(st);
    st->pieces = NULL;
    st->n_saved = st->n;
    st->mod_count = 0;
    st->mod_first = 0;
    st->maxgrowth = 0;
    st->growth = 0;
    st->n = 0;
}

/* 42b28f: pieces freed, records kept for pass 2 */
void sdi_reset_all(void)
{
    int i;
    SECNAME *sn;
    SECNODE *node;
    SECTION *s;

    for (i = 0; i < HASHSIZE; i++)
        for (sn = sec_hash[i]; sn != NULL; sn = sn->hnext)
            for (node = sn->nodes; node != NULL; node = node->next) {
                for (s = node->secs; s != NULL; s = s->next)
                    sdi_reset_sec(s);
                for (s = node->ovls; s != NULL; s = s->next)
                    sdi_reset_sec(s);
            }
}

/* 32-bit two's complement view */
static long s32(unsigned long v)
{
    v &= 0xffffffffUL;
    if ((v & 0x80000000UL) != 0)
        return -(long)(0xffffffffUL - v) - 1L;
    return (long)v;
}

/* 42b501 */
int opsize_fits(unsigned long v, long opsz)
{
    long s;

    v &= 0xffffffffUL;
    s = s32(v);
    if (opsz < -0x57L) {
        if (opsz == OPSZ_S8) {
            if (s > -0x81L && s < 0x80L)
                return 1;
            if (s > 0xff7fL && s < 0x10000L)
                return 1;
            return 0;
        }
        if (opsz == OPSZ_S15X) {
            if (s > -0x4001L && s < 0x4000L)
                return 1;
            if (v > 0xffffbfffUL)
                return 1;
            return 0;
        }
        lnk_fatal1("Invalid operand size");
        return 1;
    }
    if (opsz == OPSZ_U8) {
        if (v > 0xffUL)
            return 0;
    } else if (opsz == OPSZ_U12) {
        if (v > 0xfffUL)
            return 0;
    } else if (opsz == OPSZ_S9W) {
        if ((v & sign_bit) != 0)
            v = (v | ~(sign_bit - 1)) & 0xffffffffUL;
        s = s32(v);
        if (s < -0x100L || s > 0xffL)
            return 0;
    } else if (opsz == OPSZ_S7) {
        if (v == 0 || v == 0x40 ||
            ((s < -0x40L || s > 0x3fL) && (s < 0x7ffc0L || s > 0x7ffffL)))
            return 0;
    } else if (opsz == OPSZ_S6) {
        if ((s < -0x20L || s > 0x1fL) && (s < 0xffe0L || s > 0xffffL))
            return 0;
    } else if (opsz == OPSZ_S15) {
        if (s < -0x4000L || s > 0x3fffL)
            return 0;
    } else {
        lnk_fatal1("Invalid operand size");
    }
    return 1;
}
