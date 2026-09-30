/* oprefs.c - instruction operand reference recording
 * (SIM56000.EXE 6.3.0, module oprefs 0x459030-0x459250). */
#include "sim56000.h"

/* map a reference kind (0..0x123) to a category and an access mode */
void ref_kind_info(long kind, long *pcat, long *prw)
{
    if (prw != NULL) {
        if (kind == 0xe || kind == 10 || kind == 0x13 || kind == 0x18 || kind == 0x122 || kind == 0x123)
            *prw = 0;
        else if (kind == 0xf || kind == 0x14 || kind == 0x19)
            *prw = 2;
        else
            *prw = 1;
    }
    if (kind < 0x10) {
        if (kind < 0xd) {
            switch (kind) {
            case 0: *pcat = 3; break;
            case 1: *pcat = 1; break;
            case 2: *pcat = 2; break;
            case 3: case 9: case 10: *pcat = 4; break;
            default: *pcat = 0; break;
            }
        } else
            *pcat = 3;
    } else if (kind < 0x1a) {
        if (kind >= 0x17)
            *pcat = 2;
        else if (kind < 0x12 || kind > 0x14)
            *pcat = 0;
        else
            *pcat = 1;
    } else if (kind == 0x122)
        *pcat = 1;
    else if (kind == 0x123)
        *pcat = 2;
    else
        *pcat = 0;
}

void ref_record(long kind, long addr, long a3, long a4)
{
    struct op_ref *r = cur_sim->refs;
    long cat, rw;
    int i;

    ref_kind_info(kind, &cat, &rw);
    for (i = 0; i < 10; i++, r++) {
        if (r->cat == 0) {
            r->cat = cat;
            r->rw = rw;
            r->addr = addr;
            r->a3 = a3;
            r->a4 = a4;
            return;
        }
    }
}

/* drop pending category-3 references when the instruction has no operand of that kind */
void ref_prune(void *vinsn)
{
    struct stat_rec *insn = (struct stat_rec *)vinsn;
    struct stat_link *lk;
    struct stat_mv *mv;
    struct op_ref *r;
    int found = 0, i;

    for (i = 0; i < 4; i++) {
        if (insn->operand[i].kind == 3) {
            found = 1;
            break;
        }
    }
    if (found)
        return;
    lk = insn->link;
    if (lk != NULL && (mv = lk->mv) != NULL) {
        if (mv->kind0 == 3 || mv->kind1 == 3)
            found = 1;
        else if (lk->next != NULL && (mv = lk->next->mv) != NULL &&
                 (mv->kind0 == 3 || mv->kind1 == 3))
            found = 1;
    }
    if (found)
        return;
    r = cur_sim->refs;
    for (i = 0; i < 20; i++, r++) {
        if (r->cat == 3 && r->a4 == 0)
            r->cat = 0;
    }
}
