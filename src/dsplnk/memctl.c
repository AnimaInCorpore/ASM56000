/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), memctl.c
 * Original module: $Id: memctl.c,v 1.37 1997/08/18 16:17:25 lauren Exp $
 * Reconstructed from DSPLNK.EXE 00423710-00426a3b: the -r memory control
 * file parser (START SECTION SET/SYMBOL BASE MAP MEMORY RESERVE BALIGN IDENT
 * SECSIZE REGION/ENDR INCLUDE SBALIGN SIZSYM ALIGNSYM) and the -x option
 * list (set_x_options).
 */
#include "dsplnk.h"

/* include file stack frame, xmalloc(0x14) in memctl_do_include */
typedef struct ctlframe {
    char *name;                     /* +0x00 cur_infile->name of the includer */
    FILE *fp;                       /* +0x04 its stream */
    long level;                     /* +0x08 ctl_level */
    long lineno;                    /* +0x0c ctl_lineno */
    struct ctlframe *prev;          /* +0x10 */
} CTLFRAME;

static CTLFRAME *ctl_incstack;      /* 461dc0 */
static int ctl_pushc;               /* 469384 one-char pushback */
static char ctl_pushed;             /* 469388 */

static int memctl_parse_line(int pass);
static int memctl_parse_qualifiers(int kw, SECNAME *sec);
static int memctl_check_region(REGION *r);
static int memctl_do_set(void);
static int memctl_do_map(void);
static int memctl_map_page(void);
static int memctl_map_option(void);
static int memctl_do_include(void);
static int memctl_check_regions(void);
static int memctl_get_token(int mode);

static char *skip_space(char *p)
{
    while (*p != '\0' && isspace((unsigned char)*p))
        p++;
    return p;
}

static char *skip_word(char *p)
{
    while (*p != '\0' && !isspace((unsigned char)*p))
        p++;
    return p;
}

static char *xstrdup(char *s)
{
    char *p;

    p = (char *)xmalloc((unsigned long)strlen(s) + 1);
    strcpy(p, s);
    return p;
}

/* 00423710: read the whole memory control file (pass is always 0) */
int memctl_process_file(int pass)
{
    INFILE ctx;
    MODULE mod;
    CTLFRAME *f;
    int r;

    r = 1;
    in_fp = ctl_fp;
    memset(&mod, 0, sizeof mod);
    mod.name = NULL;
    ctx.name = title_name;
    ctx.flags = 0;
    ctx.module = &mod;
    ctx.members = NULL;
    ctx.next = NULL;
    cur_infile = &ctx;
    ctl_lineno = 1;
    do {
        memctl_parse_line(pass);
        if (ctl_incstack != NULL) {
            f = ctl_incstack;
            cur_infile->name = f->name;
            fclose(in_fp);          /* the original leaks the included stream */
            in_fp = f->fp;
            ctl_level = f->level;
            ctl_lineno = f->lineno;
            ctl_incstack = f->prev;
            xfree(f);
        }
    } while (!feof(in_fp));
    if (cur_region != region_head)
        lnk_error2("Region without associated ENDR directive", cur_region->name);
    if (!opt_ro && region_head->next != NULL)
        r = memctl_check_regions();
    cur_infile = NULL;
    ctl_lineno = 0;
    return r;
}

/* 00423863: records until the end of the current file */
static int memctl_parse_line(int pass)
{
    int r;
    int tok;
    KEYWORD *kw;
    SECNAME *sn;
    SECNODE *node;
    SECTION *p;
    SECTION *sec;
    SECTION *rsec;
    MEMSPEC spec;
    SYM tmpl;
    char word[512];
    char *s;
    char *d;

    r = 1;
    spec.mspace = 0;
    spec.mmap = 0;
    spec.mcntr = 0;
    spec.mclass = 0;
    cur_section = sec_lookup_create(global_secname, global_secno, &spec, 0);
    if (cur_section == NULL)
        lnk_fatal1("Cannot find GLOBAL section");
    for (;;) {
        tok = memctl_get_token(TOK_WORD);
        if (tok == -1)
            return r;
        if (ctl_token[0] == ';') {
            memctl_get_token(TOK_LINE);
            continue;
        }
        d = word;
        for (s = ctl_token; *s != '\0'; s++)
            *d++ = isupper((unsigned char)*s) ? (char)tolower((unsigned char)*s) : *s;
        *d = '\0';
        kw = find_memctl_kw(word);
        if (kw == NULL) {
            lnk_error2("Invalid relocation type field", ctl_token);
            memctl_get_token(TOK_LINE);
            continue;
        }
        switch (kw->id) {
        case KW_START:
            if (pass == 0) {
                if (memctl_get_token(TOK_WORD) < 1) {
                    if (start_name != NULL)
                        xfree(start_name);
                    start_name = xstrdup(ctl_token);
                    start_given = 1;
                } else {
                    lnk_error1("Invalid start address field");
                    memctl_get_token(TOK_LINE);
                    r = 0;
                }
            } else {
                memctl_get_token(TOK_LINE);
            }
            break;
        case KW_SECTION:
            if (memctl_get_token(TOK_WORD) == 0) {
                sn = secname_lookup(ctl_token);
                if (sn == NULL) {
                    lnk_error2("Section not found", ctl_token);
                    memctl_get_token(TOK_LINE);
                    r = 0;
                } else {
                    ctl_token[0] = '\0';
                    memctl_get_token(TOK_LINE);
                    s = skip_space(ctl_token);
                    if (*s == '\0' || *s == ';') {
                        for (node = sn->nodes; node != NULL; node = node->next) {
                            if (node->secs != NULL) {
                                cur_memreg = memreg_get(cur_region, &node->spec, 0);
                                memctl_assign_region(cur_memreg, node->secs, 0x100L);
                            }
                        }
                    } else {
                        s = skip_word(s);
                        if (*s != '\0')
                            *s = '\0';
                        r = memctl_parse_qualifiers(kw->id, sn);
                        if (r == 0)
                            memctl_get_token(TOK_LINE);
                    }
                }
            } else {
                lnk_error1("Invalid section name field");
                memctl_get_token(TOK_LINE);
                r = 0;
            }
            break;
        case KW_SET:
            if (pass != 0 || (r = memctl_do_set()) == 0)
                memctl_get_token(TOK_LINE);
            break;
        default:
            lnk_fatal1("Relocation type select failure");
            break;
        case KW_BASE:
        case KW_RESERVE:
        case KW_BALIGN:
            if (pass != 0) {
                memctl_get_token(TOK_LINE);
                break;
            }
            /* fall through */
        case KW_MEMORY:
            if (memctl_get_token(TOK_WORD) < 1) {
                if (memctl_parse_qualifiers(kw->id, NULL) == 0) {
                    memctl_get_token(TOK_LINE);
                    r = 0;
                }
            } else {
                lnk_error1("Invalid address relocation field");
                memctl_get_token(TOK_LINE);
                r = 0;
            }
            break;
        case KW_MAP:
            if (pass != 0 || (r = memctl_do_map()) == 0)
                memctl_get_token(TOK_LINE);
            break;
        case KW_IDENT:
            if (pass != 0) {
                memctl_get_token(TOK_LINE);
                break;
            }
            if (memctl_get_token(TOK_WORD) != 0) {
                lnk_error1("Invalid module name field");
                memctl_get_token(TOK_LINE);
                r = 0;
                break;
            }
            if (ident_name != NULL && ident_name != ident_none)
                xfree(ident_name);
            ident_name = xstrdup(ctl_token);
            if (memctl_get_token(TOK_WORD) != 0 || !tok_is_digits()) {
                lnk_error1("Invalid version number field");
                memctl_get_token(TOK_LINE);
                r = 0;
                break;
            }
            sscanf(ctl_token, "%ld", &ident_ver);
            if (memctl_get_token(TOK_WORD) != 0 || !tok_is_digits()) {
                lnk_error1("Invalid revision number field");
                memctl_get_token(TOK_LINE);
                r = 0;
                break;
            }
            sscanf(ctl_token, "%ld", &ident_rev);
            if (ident_comment != NULL && ident_comment != empty_str)
                xfree(ident_comment);
            ctl_token[0] = '\0';
            memctl_get_token(TOK_LINE);
            ident_comment = xstrdup(skip_space(ctl_token));
            break;
        case KW_SECSIZE:
            if (memctl_get_token(TOK_WORD) == 0) {
                sn = secname_lookup(ctl_token);
                if (sn == NULL) {
                    lnk_error2("Section not found", ctl_token);
                    memctl_get_token(TOK_LINE);
                    r = 0;
                } else if (memctl_get_token(TOK_WORD) < 1) {
                    r = memctl_parse_qualifiers(kw->id, sn);
                    if (r == 0)
                        memctl_get_token(TOK_LINE);
                } else {
                    lnk_error1("Invalid address relocation field");
                    memctl_get_token(TOK_LINE);
                    r = 0;
                }
            } else {
                lnk_error1("Invalid section name field");
                memctl_get_token(TOK_LINE);
                r = 0;
            }
            break;
        case KW_REGION:
            if (cur_region != region_head) {
                lnk_error1("Cannot nest regions");
                memctl_get_token(TOK_LINE);
                r = 0;
            } else if (memctl_get_token(TOK_WORD) == 0) {
                cur_region = region_get(ctl_token);
                ctl_token[0] = '\0';
                memctl_get_token(TOK_LINE);
                s = skip_space(ctl_token);
                if (*s != '\0' && *s != ';') {
                    s = skip_word(s);
                    if (*s != '\0')
                        *s = '\0';
                    r = memctl_parse_qualifiers(kw->id, NULL);
                    if (r == 0) {
                        cur_region = region_head;
                        memctl_get_token(TOK_LINE);
                    }
                }
            } else {
                lnk_error1("Invalid region name field");
                memctl_get_token(TOK_LINE);
                r = 0;
            }
            break;
        case KW_ENDR:
            if (cur_region == region_head) {
                lnk_error1("ENDR without corresponding REGION directive");
            } else {
                if (cur_memreg == NULL)
                    cur_memreg = memreg_get(cur_region, &spec, 0);
                memctl_check_region(cur_region);
                cur_region = region_head;
                cur_memreg = NULL;
                memctl_get_token(TOK_LINE);
            }
            break;
        case KW_INCLUDE:
            r = memctl_do_include();
            if (r == 0)
                memctl_get_token(TOK_LINE);
            break;
        case KW_SBALIGN:
            if (opt_i) {
                r = 1;
                break;
            }
            if (memctl_get_token(TOK_WORD) != 0) {
                lnk_error1("Invalid section name field");
                memctl_get_token(TOK_LINE);
                r = 0;
                break;
            }
            sn = secname_lookup(ctl_token);
            if (sn == NULL) {
                lnk_error2("Section not found", ctl_token);
                memctl_get_token(TOK_LINE);
                r = 0;
                break;
            }
            ctl_token[0] = '\0';
            memctl_get_token(TOK_LINE);
            s = skip_space(ctl_token);
            if (*s == '\0' || *s == ';') {
                for (node = sn->nodes; node != NULL; node = node->next) {
                    if (node->secs != NULL && (node->flags & SN_F40000) == 0) {
                        node->secs->flags |= SF_ALIGNED;
                        for (p = node->secs->node->bufs; p != NULL; p = p->next) {
                            if (p->flags & SF_REL)
                                p->flags |= SF_ALIGNED;
                        }
                    }
                }
            } else {
                s = skip_word(s);
                if (*s != '\0')
                    *s = '\0';
                r = memctl_parse_qualifiers(kw->id, sn);
                if (r == 0)
                    memctl_get_token(TOK_LINE);
            }
            break;
        case KW_SIZSYM:
        case KW_ALIGNSYM:
            if (memctl_get_token(TOK_WORD) != 0) {
                lnk_error1("Invalid symbol name field");
                memctl_get_token(TOK_LINE);
                r = 0;
                break;
            }
            if (sym_lookup(ctl_token, 0) != NULL) {
                memctl_get_token(TOK_LINE);
                r = 1;
                break;
            }
            strcpy(word, ctl_token);
            if (memctl_get_token(TOK_WORD) >= 1) {
                lnk_error1("Invalid memory space field");
                memctl_get_token(TOK_LINE);
                r = 0;
                break;
            }
            input_cursor = ctl_token;
            if (!get_mem_spec(&spec))
                return 0;
            p = NULL;
            memset(&tmpl, 0, sizeof tmpl);
            tmpl.fval = 0.0;
            tmpl.sfval = 0.0;
            tmpl.name = word;
            tmpl.flags = SYM_SPECIAL | SYM_INT | SYM_GLOBAL;   /* 0x20140 */
            tmpl.mem = spec;
            tmpl.scnum = -1;
            sec = NULL;
            rsec = NULL;
            if (*input_cursor != '\0') {
                p = sec_find(input_cursor, &spec);
                if (p == NULL) {
                    if (!opt_isw)
                        lnk_warning2("Section not found", input_cursor);
                    memctl_get_token(TOK_LINE);
                    rsec = cur_section;
                    sec = cur_section;
                    tmpl.lo = 0;
                } else {
                    sec = p;
                    rsec = p;
                    if (!opt_csl)
                        tmpl.lo = p->size != 0 ? p->size : p->ovlsize;
                    else
                        tmpl.lo = p->node->totsize != 0 ? p->node->totsize
                                                        : p->node->totovl;
                }
            }
            if (kw->id == KW_ALIGNSYM) {
                if (rsec == NULL || rsec->align == 0) {
                    if (sec == NULL || sec->node == NULL || sec->node->next == NULL ||
                        sec->node->next->secs == NULL)
                        tmpl.lo = 0;
                    else
                        tmpl.lo = sec->node->next->secs->align;
                } else {
                    tmpl.lo = rsec->align;
                }
            }
            tmpl.sec = sec;
            tmpl.rsec = rsec;
            sym_enter(&tmpl);
            break;
        }
    }
}

/* 00424879: comma list of <mem>[:expr] terms in ctl_token; 1 ok, 0 error */
static int memctl_parse_qualifiers(int kw, SECNAME *sec)
{
    SECNODE *node;
    SECTION *p;
    SECTION *q;
    EXPR *e;
    MEMSPEC spec;
    unsigned long val;
    unsigned long hi;
    int pct;
    int remap;
    double factor;
    char *c;

    node = NULL;
    p = NULL;
    val = 0;
    hi = 0;
    pct = 0;
    factor = 1.0;
    remap = (kw == KW_BASE || kw == KW_MEMORY || kw == KW_REGION) ? 1 : 0;
    for (input_cursor = ctl_token; *input_cursor != '\0'; input_cursor++)
        if (!isspace((unsigned char)*input_cursor))
            break;
    for (;;) {
        if (*input_cursor == '\0')
            return 1;
        if (!get_mem_spec(&spec))
            break;
        cur_memreg = memreg_get(cur_region, &spec, remap);
        if (sec != NULL) {
            node = secnode_get(sec, &spec);
            p = node->secs;
            if (p == NULL)
                p = sec_lookup_create(sec->name, sec->num, &spec, 0);
            if (node->spec.mmap != spec.mmap) {
                if ((node->flags & SN_REMAP) && !sdi_active)
                    lnk_warning1("Remapping section");
                node->flags |= SN_REMAP;
                node->spec.mmap = spec.mmap;
            }
        }
        if (kw == KW_SECTION && (*input_cursor == '\0' || *input_cursor == ',')) {
            if (*input_cursor == ',')
                input_cursor++;
            memctl_assign_region(cur_memreg, p, 0x100L);
        } else if (kw == KW_SBALIGN && (*input_cursor == '\0' || *input_cursor == ',')) {
            if (*input_cursor == ',')
                input_cursor++;
            if ((node->flags & SN_F40000) == 0) {
                p->flags |= SF_ALIGNED;
                for (q = node->bufs; q != NULL; q = q->next) {
                    if (q->flags & SF_REL)
                        q->flags |= SF_ALIGNED;
                }
            }
        } else if (!opt_i && kw == KW_BALIGN &&
                   (*input_cursor == '\0' || *input_cursor == ',')) {
            if (*input_cursor == ',')
                input_cursor++;
            cur_memreg->flags |= MR_BALIGN;
        } else {
            if (kw == KW_SECSIZE) {
                e = eval_expr();
                if (e == NULL)
                    return 0;
                if (e->type == EXPR_FLT) {
                    if (e->fval <= 100.0) {
                        lnk_error1("Section padding percentage too small");
                        free_expr(e);
                        return 0;
                    }
                    pct = 1;
                    factor = e->fval / 100.0;
                } else {
                    pct = 0;
                    val = e->lo;
                    if (opt_abc && cur_memreg->high < val)
                        lnk_error1("Specified size greater than maximum memory address");
                }
            } else {
                e = eval_int();
                if (e == NULL)
                    return 0;
                val = e->lo;
                if (opt_abc && cur_memreg->high < val)
                    lnk_error1("Specified address greater than maximum memory address");
                if (kw == KW_RESERVE) {
                    c = input_cursor;
                    if (*c != '.') {
                        input_cursor = c + 1;
                        lnk_error1("Invalid reserve range syntax");
                        free_expr(e);
                        return 0;
                    }
                    input_cursor = c + 2;
                    if (c[1] != '.') {
                        lnk_error1("Invalid reserve range syntax");
                        free_expr(e);
                        return 0;
                    }
                    free_expr(e);
                    e = eval_int();
                    if (e == NULL)
                        return 0;
                    hi = e->lo;
                    /* the original checks the low address again */
                    if (opt_abc && cur_memreg->high < val)
                        lnk_error1("Specified address greater than maximum memory address");
                } else if (*input_cursor != '\0' && *input_cursor != ',') {
                    lnk_error1("Extra characters beyond expression");
                    return 0;
                }
            }
            free_expr(e);
            while (*input_cursor != '\0' && *input_cursor != ',')
                input_cursor++;
            if (*input_cursor != '\0' && *input_cursor == ',')
                input_cursor++;
            switch (kw) {
            case KW_SECTION:
                p->state &= ~SS_LISTED;
                p->state |= SS_ADDR;
                p->lo = val;
                p->hi = M32(p->hi + val);
                cur_memreg = memreg_get(cur_region, &spec, 0);
                memctl_assign_region(cur_memreg, p, 0x200L);
                break;
            default:
                lnk_fatal1("Relocation type select failure");
                break;
            case KW_BASE:
                if ((cur_memreg->flags2 & MR2_BASE) == 0) {
                    cur_memreg->base = val;
                    cur_memreg->flags2 |= MR2_BASE;
                }
                break;
            case KW_MEMORY:
                cur_memreg->high = val;
                cur_memreg->flags2 |= MR2_HIGH;
                break;
            case KW_RESERVE:
                p = memctl_reserve_piece(&spec, val, M32(hi + 1));
                memctl_assign_region(cur_memreg, p, 0x200L);
                break;
            case KW_BALIGN:
                if (!opt_i) {
                    cur_memreg->flags |= MR_BALIGN;
                    if ((cur_memreg->flags2 & MR2_BALIGN) == 0) {
                        cur_memreg->balign = val;
                        cur_memreg->flags2 |= MR2_BALIGN;
                    }
                }
                break;
            case KW_SECSIZE:
                if (!pct || p->sdi == NULL || p->sdi->n == 0) {
                    node->flags |= SN_SECSIZE;
                    if (!pct) {
                        node->secsize = val;
                    } else {
                        node->flags |= SN_SECPCT;
                        node->secpct = factor;
                    }
                } else {
                    lnk_error1("Cannot use SECSIZE with percentage for sections "
                               "containing span-dependent instructions");
                }
                break;
            case KW_REGION:
                cur_memreg->size = val;
                cur_memreg->flags2 |= MR2_SIZE;
                break;
            case KW_SBALIGN:
                if ((node->flags & SN_F40000) == 0) {
                    if (!opt_i)
                        cur_memreg->flags |= MR_SBALIGN;
                    node->sbalign = val;
                    p->flags |= SF_ALIGNED;
                    for (q = node->bufs; q != NULL; q = q->next) {
                        if (q->flags & SF_REL)
                            q->flags |= SF_SBALIGN | SF_ALIGNED;
                    }
                }
                break;
            }
        }
    }
    return 0;
}

/* 004250ad: ENDR - complete base/high/size of every memory of a region */
static int memctl_check_region(REGION *r)
{
    char msg[512];
    MEMREG *m;
    unsigned long len;
    int r2;

    r2 = 1;
    for (m = r->mems; m != NULL; m = m->next) {
        if (!opt_abc || m->base <= m->high) {
            len = M32(m->high - m->base + 1);
            if ((m->flags2 & MR2_BASE) == 0) {
                if ((m->flags2 & MR2_HIGH) == 0) {
                    if (m->flags2 & MR2_SIZE)
                        m->high = M32(m->size - 1);
                } else if ((m->flags2 & MR2_SIZE) == 0) {
                    m->size = M32(m->high + 1);
                } else {
                    m->base = M32(m->high - (m->size - 1));
                }
            } else if ((m->flags2 & MR2_HIGH) == 0) {
                if ((m->flags2 & MR2_SIZE) == 0)
                    m->size = len;
                else
                    m->high = M32(m->base - 1 + m->size);
            } else if ((m->flags2 & MR2_SIZE) == 0) {
                m->size = len;
            } else if (m->size != len) {
                sprintf(msg, "Region %s %c(%ld) size/address mismatch", r->name,
                        mem_idx_char[mem_space_index(m->spec.mspace)], m->spec.mcntr);
                lnk_error1(msg);
                r2 = 0;
            }
        } else {
            sprintf(msg, "Region %s %c(%ld) high address lower than base address",
                    r->name, mem_idx_char[mem_space_index(m->spec.mspace)],
                    m->spec.mcntr);
            lnk_error1(msg);
            r2 = 0;
        }
    }
    return r2;
}

/* 004252ad: put section piece sec into the memory record mr (how 0x100
   region member, 0x200 fixed address); moved to the end of mr's list */
void memctl_assign_region(MEMREG *mr, SECTION *sec, long how)
{
    SECREF *n;
    SECREF *found;
    SECREF *fprev;
    SECREF *last;

    if (sec->node->memreg != NULL && sec->node->memreg != mr) {
        lnk_error2("Duplicate region assignment for section", sec->node->sname->name);
        return;
    }
    if (how == 0x200L) {
        mr->flags2 |= MR2_ADDR;
    } else if (how == 0x100L) {
        if (sec->state & SS_ADDR) {
            lnk_warning2("Section already set as absolute", sec->node->sname->name);
            return;
        }
        sec->state |= SS_LISTED;
        mr->flags2 |= MR2_LISTED;
    }
    if (sec->node->ovls != NULL)
        mr->flags2 |= MR2_OVL;
    fprev = NULL;
    last = NULL;
    found = NULL;
    for (n = mr->secs; n != NULL; n = n->next) {
        if (n->sec == sec) {
            if (found == NULL) {
                found = n;
                fprev = last;
            } else {
                lnk_fatal1("Duplicate section entry");
            }
        }
        last = n;
    }
    if (found == NULL) {
        n = (SECREF *)xmalloc(sizeof(SECREF));
        n->sec = sec;
        n->next = NULL;
        if (mr->secs == NULL)
            mr->secs = n;
        else
            last->next = n;
        mr->nsecs++;
    } else if (found != last) {
        if (found == mr->secs)
            mr->secs = found->next;
        else
            fprev->next = found->next;
        last->next = found;
        found->next = NULL;
    }
    sec->node->memreg = mr;
}

/* 00425470: SET/SYMBOL <name> [<mem>:]<expr> */
static int memctl_do_set(void)
{
    char name[NAMEBUF_SIZE];
    MEMSPEC spec;
    SYM tmpl;
    EXPR *e;
    SECTION *g;
    unsigned long fl;
    char *p;

    if (memctl_get_token(TOK_WORD) != 0) {
        lnk_error1("Invalid symbol name field");
        return 0;
    }
    if (sym_lookup(ctl_token, 0) != NULL) {
        memctl_get_token(TOK_LINE);
        return 1;
    }
    strcpy(name, ctl_token);
    if (memctl_get_token(TOK_WORD) >= 1) {
        lnk_error1("Invalid symbol value field");
        return 0;
    }
    input_cursor = ctl_token;
    for (p = ctl_token; *p != '\0' && *p != ':'; p++)
        ;
    if (*p == ':') {
        if (!get_mem_spec(&spec))
            return 0;
    } else {
        spec.mmap = 4;
        spec.mspace = 4;
        spec.mcntr = 0;
        spec.mclass = 0;
    }
    e = eval_expr();
    if (e == NULL)
        return 0;
    memset(&tmpl, 0, sizeof tmpl);
    tmpl.fval = 0.0;
    tmpl.sfval = 0.0;
    tmpl.name = name;
    fl = (unsigned long)e->type & 0xf00UL;
    tmpl.flags = fl | SYM_OUTPUT | SYM_GLOBAL;
    if ((e->type & EXPR_FLT) == 0) {
        tmpl.hi = e->mid;
        tmpl.lo = e->lo;
    } else {
        tmpl.fval = e->fval;
    }
    if (e->size == fmt_dword)
        tmpl.flags = fl | SYM_OUTPUT | SYM_LONG | SYM_GLOBAL;
    free_expr(e);
    tmpl.mem = spec;
    tmpl.scnum = -1;
    tmpl.sdi_cnt = 0;
    tmpl.cls_off = 0;
    g = sec_lookup_create(global_secname, global_secno, &spec, 0);
    if (g == NULL)
        lnk_fatal1("Cannot find GLOBAL section");
    tmpl.sec = g;
    tmpl.rsec = g;
    sym_enter(&tmpl);
    num_set_syms++;
    return 1;
}

/* 0042568f: MAP PAGE ... | MAP OPT ... */
static int memctl_do_map(void)
{
    if (memctl_get_token(TOK_WORD) != 0) {
        lnk_error1("Invalid MAP record field");
        return 0;
    }
    str_lower(ctl_token);
    if (strcmp(ctl_token, "page") == 0) {
        if (!memctl_map_page())
            return 0;
    } else {
        if (strcmp(ctl_token, "opt") != 0) {
            lnk_error1("Invalid MAP record field");
            return 0;
        }
        if (!memctl_map_option())
            return 0;
    }
    return 1;
}

/* 00425747: MAP PAGE [width][,[length][,[top][,[bottom][,lmargin]]]] */
static int memctl_map_page(void)
{
    long w;
    long len;
    long top;
    long bot;
    long lm;

    if (memctl_get_token(TOK_WORD) > 0) {
        lnk_error1("Invalid MAP page field");
        return 0;
    }
    input_cursor = ctl_token;
    if (ctl_token[0] == ',') {
        w = map_width;
    } else {
        w = eval_nonneg();
        if (w == -1)
            return 0;
        if (w < 1 || w > MAP_MAXPAGE) {
            lnk_error1("Invalid page width specified");
            return 0;
        }
    }
    if (*input_cursor == ',')
        input_cursor++;
    if (*input_cursor == '\0') {
        len = map_pagelen;
        top = map_topmargin;
        bot = map_botmargin;
        lm = map_lmargin - 1;
    } else {
        if (*input_cursor == ',') {
            len = map_pagelen;
        } else {
            len = eval_nonneg();
            if (len == -1)
                return 0;
            if (len < 10 || len > MAP_MAXPAGE) {
                lnk_error1("Invalid page length specified");
                return 0;
            }
        }
        if (*input_cursor == ',')
            input_cursor++;
        if (*input_cursor == '\0') {
            top = map_topmargin;
            bot = map_botmargin;
            lm = map_lmargin - 1;
        } else {
            if (*input_cursor == ',') {
                top = map_topmargin;
            } else {
                top = eval_nonneg();
                if (top == -1)
                    return 0;
            }
            if (*input_cursor == ',')
                input_cursor++;
            if (*input_cursor == '\0') {
                bot = len - map_lastline;
                lm = map_lmargin - 1;
            } else {
                if (*input_cursor == ',') {
                    bot = len - map_lastline;
                    if (bot < 0) {
                        lnk_error1("Page length too small to allow default bottom margin");
                        return 0;
                    }
                } else {
                    bot = eval_nonneg();
                    if (bot == -1)
                        return 0;
                }
                if (*input_cursor == ',')
                    input_cursor++;
                if (*input_cursor == '\0') {
                    lm = map_lmargin - 1;
                } else {
                    lm = eval_nonneg();
                    if (lm == -1)
                        return 0;
                    if (*input_cursor != '\0') {
                        lnk_error1("Extra characters beyond expression");
                        return 0;
                    }
                }
            }
        }
    }
    if (lm >= w) {
        lnk_error1("Left margin exceeds page width");
        return 0;
    }
    if (len - 10 < top + bot) {
        lnk_error1("Page length too small for specified top and bottom margins");
        return 0;
    }
    map_width = w;
    map_pagelen = len;
    map_topmargin = top;
    map_botmargin = bot;
    map_lastline = len - bot;
    map_lmargin = lm + 1;
    return 1;
}

/* 00425a60: MAP OPT <opt>[=n][,...] */
static int memctl_map_option(void)
{
    char opt[512];
    char *s;
    char *d;
    char *eq;
    long n;
    KEYWORD *k;

    n = 0;
    if (memctl_get_token(TOK_WORD) >= 1) {
        lnk_error1("Invalid MAP option field");
        return 0;
    }
    s = ctl_token;
    while (*s != '\0') {
        d = opt;
        for (; *s != '\0' && *s != ','; s++)
            *d++ = isupper((unsigned char)*s) ? (char)tolower((unsigned char)*s) : *s;
        *d = '\0';
        if (*s != '\0')
            s++;
        eq = strrchr(opt, '=');
        if (eq != NULL) {
            *eq = '\0';
            n = strtol(eq + 1, NULL, 0);
        }
        k = find_map_opt(opt);
        if (k == NULL) {
            lnk_error2("Invalid MAP option", opt);
            return 0;
        }
        switch (k->id) {
        case MO_NOCONST:   map_const = 0; break;
        case MO_NOLOCAL:   map_local = 0; break;
        case MO_NOSECADDR: map_secaddr = 0; break;
        case MO_NOSECNAME: map_secname = 0; break;
        case MO_NOSYMNAME: map_symname = 0; break;
        case MO_NOSYMVAL:  map_symval = 0; break;
        case MO_NOBUFFER:  map_buffer = 0; break;
        case MO_NOOVERLAY: map_overlay = 0; break;
        case MO_NOUNUSED:  map_unused = 0; break;
        case MO_GLOBMAP:   map_globmap = 1; break;
        case MO_NOGLOBSYM: map_globsym = 0; break;
        case MO_SYMLEN:
            map_symlen_on = 1;
            map_symlen = n;
            break;
        default:
            lnk_fatal1("Map option select failure");
            break;
        }
    }
    return 1;
}

/* 00425cf1: -x option list (command line / DSPLNKOPT) */
int set_x_options(char *list)
{
    char opt[12];
    char *d;
    int n;
    KEYWORD *k;

    if (*list == '\0') {
        lnk_error1("Missing option");
        return 0;
    }
    while (*list != '\0') {
        n = 0;
        d = opt;
        for (; *list != '\0' && *list != ','; list++) {
            if (n > 7) {
                lnk_error1("Illegal option");
                return 0;
            }
            n++;
            *d++ = isupper((unsigned char)*list) ? (char)tolower((unsigned char)*list)
                                                  : *list;
        }
        *d = '\0';
        if (opt[0] == '\0') {
            lnk_error1("Missing option");
            return 0;
        }
        k = find_xopt(opt);
        if (k == NULL) {
            lnk_error1("Illegal option");
            return 0;
        }
        switch (k->id) {
        case 1:  opt_abc = 1; break;
        case 2:  opt_abc = 0; break;
        case 3:  opt_aec = 1; break;
        case 4:  opt_aec = 0; break;
        case 5:  opt_ro = 1; break;
        case 6:  opt_ro = 0; break;
        case 7:  opt_asc = 1; break;
        case 8:  opt_asc = 0; break;
        case 9:  opt_eso = 1; break;
        case 10: opt_eso = 0; break;
        case 11: opt_wex = 1; break;
        case 12: opt_wex = 0; break;
        case 13: opt_ovlp = 1; break;
        case 14: opt_ovlp = 0; break;
        case 15: opt_svo = 1; break;
        case 16: opt_rsc = 1; break;
        case 17: opt_rsc = 0; break;
        case 18: opt_ff = 1; break;
        case 19: opt_ff = 0; break;
        case 20: opt_csl = 1; break;
        case 21: opt_csl = 0; break;
        case 22: opt_sdi = 1; break;
        case 23: opt_sdi = 0; break;
        case 24:
            if (target_index == TGT_56300 || target_index == TGT_56600)
                opt_sbm = 1;
            break;
        case 25:
            if (target_index != TGT_56600)
                opt_sbm = 0;
            break;
        case 26: opt_wvr = 1; break;
        case 27: opt_wvr = 0; break;
        case 28: opt_osp = 1; break;
        case 29: opt_isw = 1; break;
        case 30: opt_wdg = 1; break;
        case 31: opt_wdg = 0; break;
        case 32: opt_mcm = 1; break;
        case 33: opt_mcm = 0; break;
        default:
            lnk_fatal1("Option select error");
            break;
        }
        if (*list != '\0')
            list++;
    }
    return 1;
}

/* try name, then every -p path + name; namebuf holds the name tried */
static FILE *open_inc(char *fname, char *ext)
{
    FILE *fp;
    STRNODE *lp;

    strcpy(namebuf, fname);
    if (ext != NULL)
        set_default_ext(ext);
    fp = fopen(namebuf, "r");
    if (fp == NULL) {
        for (lp = libpath_head; lp != NULL; lp = lp->next) {
            strcpy(namebuf, lp->str);
            strcat(namebuf, fname);
            if (ext != NULL)
                set_default_ext(ext);
            fp = fopen(namebuf, "r");
            if (fp != NULL)
                break;
        }
    }
    return fp;
}

/* 0042609f: INCLUDE <file> */
static int memctl_do_include(void)
{
    char fname[516];
    FILE *fp;
    CTLFRAME *f;

    if (memctl_get_token(TOK_WORD) != 0) {
        lnk_error1("Invalid include file name");
        return 0;
    }
    if (get_string(ctl_token, fname) == NULL) {
        lnk_error1("Missing filename");
        return 0;
    }
    fp = open_inc(fname, NULL);
    if (fp == NULL)
        fp = open_inc(fname, ".ctl");
    if (fp == NULL)
        fp = open_inc(fname, ".mem");
    if (fp == NULL) {
        lnk_error2("Cannot open include file", fname);
        return 0;
    }
    if (opt_v)
        fprintf(msg_fp, "%s: Opening include file %s\n", progname, namebuf);
    f = (CTLFRAME *)xmalloc(sizeof(CTLFRAME));
    f->name = cur_infile->name;
    f->fp = in_fp;
    f->level = ctl_level;
    f->lineno = ctl_lineno;
    f->prev = ctl_incstack;
    ctl_level++;
    in_fp = fp;
    ctl_incstack = f;
    cur_infile->name = namebuf;     /* sic: the shared buffer */
    ctl_lineno = 1;
    return 1;
}

/* 00426437: a RESERVE piece for [lo,hi) */
SECTION *memctl_reserve_piece(MEMSPEC *spec, unsigned long lo, unsigned long hi)
{
    SECTION *p;
    SECNAME *sn;
    SECNODE *node;

    p = sec_find(reserve_secname, spec);
    while (p != NULL && p->node->sname->num == SN_RESERVE_NUM) {
        if ((p->state & SS_ACTIVE) == 0) {
            p->state |= SS_ACTIVE | SS_ADDR;
            p->lo = lo;
            p->hi = hi;
            return p;
        }
        p = p->next;
    }
    sn = secname_new(reserve_secname, SN_RESERVE_NUM);
    node = secnode_get(sn, spec);
    p = sec_alloc(node, 0x1000UL);
    p->index = 0;
    p->flags = 0x1000UL;
    p->state |= SS_ACTIVE | SS_ADDR;
    p->lo = lo;
    p->hi = hi;
    p->next = node->secs;
    node->secs = p;
    node->nsecs++;
    num_secs++;
    return p;
}

/* 00426558: region overlap check hook (empty) */
static int memctl_check_regions(void)
{
    return 1;
}

/* 00426562: token reader on in_fp.  mode 0: next blank-delimited word
   (-1 at EOF, else 1 if it starts with '_'); mode 4: append the rest of
   the line to ctl_token; mode 10 (unused): one word up to the newline. */
static int memctl_get_token(int mode)
{
    int c;
    char *p;
    char *start;

    if (mode == TOK_LINE) {
        start = p = ctl_token + strlen(ctl_token);
        if (!ctl_pushed) {
            c = getc(in_fp);
        } else {
            ctl_pushed = 0;
            c = ctl_pushc;
        }
        while (c > 0 && c != '\n') {
            *p++ = (char)c;
            c = getc(in_fp);
        }
        /* text mode: MSVC drops the CR of a CR LF pair */
        if (c == '\n' && p > start && p[-1] == '\r')
            p--;
        *p = '\0';
        if (c == '\n')
            ctl_lineno++;
        return c > 0 ? 0 : -1;
    }
    if (!ctl_pushed) {
        c = getc(in_fp);
    } else {
        ctl_pushed = 0;
        c = ctl_pushc;
    }
    if (c > 0) {
        while (isspace(c)) {
            if (c == '\n') {
                ctl_lineno++;
                if (mode == TOK_NEXTLINE)
                    break;
            }
            c = getc(in_fp);
            if (c < 1)
                break;
        }
    }
    if (c < 1 || (mode == TOK_NEXTLINE && c != '\n')) {
        ctl_token[0] = '\0';
        return -1;
    }
    if (mode == TOK_NEXTLINE) {
        c = getc(in_fp);
        if (c == '\n') {
            ctl_lineno++;
            ctl_token[0] = '\0';
            return 0;
        }
    }
    ctl_token[0] = (char)c;
    p = ctl_token + 1;
    for (;;) {
        c = getc(in_fp);
        if (c < 1 || (mode == TOK_NEXTLINE && c == '\n'))
            break;
        if (mode != TOK_NEXTLINE && isspace(c))
            break;
        *p++ = (char)c;
    }
    *p = '\0';
    if (c < 1 || (mode == TOK_NEXTLINE && c != '\n'))
        return -1;
    if (mode == TOK_NEXTLINE) {
        if (p[-1] == '\r')
            p[-1] = '\0';
        if (c == '\n')
            ctl_lineno++;
        return 0;
    }
    ctl_pushc = c;
    ctl_pushed = 1;
    return ctl_token[0] == '_';
}
