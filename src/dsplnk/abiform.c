/*
 * abiform.c - DSPLNK.EXE (CLAS56 v6.3, DSP Linker 6.3.7), ABI expression
 * subsystem: abi_map_lookup (0x437950-0x437e45), the section-relative address
 * computation of the ABI grammar.  It is the same computation as the '['
 * term of the linker's own expression parser (parse_bracket in eval.c), but
 * runs on the linker state saved in the ABI context (abi_ctx_new) instead of
 * the live globals, and on a scratch expression built from the arguments.
 */
#include "abi.h"

/* section flag of buffer/overlay pieces tested with 0x20000 in the original */
#define ML_SDI      0x20000UL
#define ML_BUF      0x2000UL

/* Returns the absolute address for the section-relative value `lo' of the
   memory (map, ctr) of section `rsect'; `buf'/`ovl' are the buffer/overlay
   numbers and `sdi' the 1-based SDI record of the reference. */
long abi_map_lookup(ABICTX *ctx, long lo, long map, long ctr, long sect,
                    long rsect, long buf, long ovl, long sdi)
{
    int nv;                         /* object version >= 5.0.11 */
    long cur_rsecno_v = ctx->cur_rsecno;
    OVLENT *ovltab = ctx->ovltab;
    BUFREF *buftab = ctx->buftab;
    MODSEC **secmap = ctx->secmap;
    long ovlbase = ctx->ovl_base;
    SECTION *rsec = ctx->rsection;
    MODSEC *ms = ctx->rmsec;
    char opti = ctx->opt_i;
    unsigned long *runc = ctx->run_ctr;
    unsigned long *loadc = ctx->load_ctr;
    SECTION *alloc = ctx->alloc;
    EXPR *e;
    long idx, k;
    SECTION *sec;
    SECNAME *sn;
    SECNODE *n;
    SECTION *p;
    unsigned long adj, result;
    MEMSPEC spec;
    SDISTAT *sd;

    /* the arguments are 32-bit ints in the original (rsect = -1 means "current") */
    lo = ABI_S32(lo);
    map = ABI_S32(map);
    ctr = ABI_S32(ctr);
    sect = ABI_S32(sect);
    rsect = ABI_S32(rsect);
    buf = ABI_S32(buf);
    ovl = ABI_S32(ovl);
    sdi = ABI_S32(sdi);
    nv = !(obj_major < 6 && (obj_major != 5 || obj_minor < 1) &&
           (obj_major != 5 || obj_minor != 0 || obj_rev < 0xb));
    e = new_expr();
    e->lo = M32(lo);
    e->type = EXPR_INT;
    e->map = map;
    e->space = map_to_space(e->map);
    e->ctr = ctr;
    e->sect = sect;
    e->rsect = rsect;
    e->buf = buf;
    e->ovl = ovl;
    e->sdi = sdi;
    idx = cur_rsecno_v;
    if (e->rsect >= 0)
        idx = e->rsect;
    if ((nv && e->ovl != 0) || (!nv && runc != loadc)) {
        k = nv ? ovlbase + e->ovl : cur_overlay;
        e->lo = M32(e->lo + ovltab[k].grp->lo);
    } else {
        if (e->buf == 0 || !(buftab[buf_base + e->buf].sec->flags & ML_SDI)) {
            if ((nv && e->rsect == cur_rsecno_v && e->space == load_spec.mspace &&
                 e->ctr == load_spec.mcntr) ||
                (!nv && e->space == load_spec.mspace && e->ctr == load_spec.mcntr)) {
                sec = rsec;
            } else {
                sec = NULL;
                sn = rsec->node->sname;
                for (n = sn->nodes; n != NULL; n = n->next) {
                    if (n->spec.mspace == e->space && n->spec.mcntr == e->ctr) {
                        sec = n->secs;
                        break;
                    }
                }
                ms = secmap[idx];
                while (ms != NULL && (ms->sec->node->spec.mspace != e->space ||
                                      ms->sec->node->spec.mcntr != e->ctr))
                    ms = ms->next;
                if (ms == NULL) {
                    spec.mspace = e->space;
                    spec.mmap = e->map;
                    spec.mcntr = e->ctr;
                    spec.mclass = e->attr;
                    sec_lookup_create(secmap[idx]->sec->node->sname->name, idx, &spec, 1);
                    e->space = spec.mspace;
                    e->map = spec.mmap;
                    e->ctr = spec.mcntr;
                    e->attr = spec.mclass;
                    ms = secmap[idx];
                    while (ms != NULL && (ms->sec->node->spec.mspace != e->space ||
                                          ms->sec->node->spec.mcntr != e->ctr))
                        ms = ms->next;
                }
            }
        } else {
            sec = buftab[buf_base + e->buf].sec;
            ms = ctx->rmsec;
        }
        if (sec == NULL || ms == NULL)
            lnk_fatal1("Section map lookup failure");
        e->lo = M32(e->lo + sec->lo);
        if (!opti || (sec->flags & ML_SDI)) {
            if (!(sec->flags & ML_BUF)) {
                adj = 0;
                if (sec->flags & ML_SDI) {
                    for (p = sec->node->bufs; p != NULL; p = p->next)
                        if (p->bufaddr <= e->lo)
                            adj = M32(adj + p->bufspan);
                }
                e->lo = M32(e->lo + M32(ms->base2 - adj));
            } else {
                e->lo = M32(e->lo - buftab[buf_base + e->buf].addr);
            }
        } else {
            e->lo = M32(e->lo + ms->base2);
        }
    }
    if (runc == loadc)
        e->lo = M32(e->lo + rsec->node->sdigrow);
    else
        e->lo = M32(e->lo + (unsigned long)ovltab[ovlbase + e->ovl].sdioff);
    if (alloc != NULL && alloc->sdi != NULL && e->sdi != 0) {
        sd = alloc->sdi;
        e->lo = M32(e->lo + (unsigned long)sd->recs[sd->mod_first - 1 + e->sdi].growth);
    }
    result = e->lo;
    free_expr(e);
    return (long)result;
}
