/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), map.c
 * $Id: map.c,v 1.33 1998/12/15 19:29:00 russo Exp $
 * Reconstructed from 0041d7d0-004223f9 (map_sort_exts .. mem_order_l
 * included): the -m map file writer with its paging engine, the sort
 * comparators used through util.c sort_ptrs, and the unresolved external
 * listings.
 *
 * Every formatted map line is built in the shared namebuf (as the original
 * does); some paths print namebuf without refreshing it (reproduced).
 */
#include "dsplnk.h"

static void map_putstr(char *s);
static void map_newline(void);
static void map_leftmargin(void);
static void map_newpage(int hdr);
static void map_pageheader(void);
static void map_banner(void);
static void map_putstr_wrap(char *s);
static void map_sec_by_addr(void);
static void map_tab(int col);
static void map_sort_secs_addr(SECTION **arr, long n);
static long sec_cmp_addr(void *a, void *b);
static long piece_cmp_size(void *a, void *b);
static long piece_cmp_num(void *a, void *b);
static long memreg_cmp(void *a, void *b);
static void map_sec_by_name(void);
static void map_sort_secs_name(SECTION **arr, long n);
static long sec_cmp_name(void *a, void *b);
static SECTION **map_collect_secs(void);
static void map_sym_by_name(void);
static void map_tab_dots(int col);
static void map_sort_syms_name(SYM **arr, long n);
static long sym_cmp_name(void *a, void *b);
static void map_sym_by_value(void);
static void map_sort_syms_value(SYM **arr, long n);
static long sym_cmp_value(void *a, void *b);
static void map_global_by_memspace(void);
static void map_build_sec_symlists(void);
static void map_sort_secs_memspace(SECTION **arr, long n);
static long sec_cmp_memspace(void *a, void *b);
static void map_unresolved(void);
static void map_sort_exts(XREF **arr, long n);
static long ext_cmp(void *a, void *b);

/* sign of the 32-bit difference a-b, as the original's int subtraction */
static long diff32(unsigned long a, unsigned long b)
{
    unsigned long v;

    v = M32(a - b);
    if (v == 0)
        return 0;
    return (v & 0x80000000UL) ? -1L : 1L;
}

static long sgn(int v)
{
    return v < 0 ? -1L : (v > 0 ? 1L : 0L);
}

#define SECNAME_OF(p)   ((p)->node->sname->name)
#define OWNNAME_OF(p)   ((p)->run->node->sname->name)

/* 41d7d0 */
void map_write(void)
{
    if (num_secs == 0) {
        map_putstr("No sections found");
    } else {
        map_sec_by_addr();
        map_sec_by_name();
    }
    if (num_syms == 0) {
        if (map_symname || map_symval) {
            if (!map_need_hdr)
                map_newpage(1);
            map_putstr("No symbols found");
        }
    } else {
        if ((map_symname || map_symval) && !map_need_hdr)
            map_newpage(1);
        map_sym_by_name();
        map_sym_by_value();
    }
    if (map_globmap && num_secs != 0) {
        if (!map_need_hdr)
            map_newpage(1);
        map_global_by_memspace();
    }
    if (!opt_i && num_xrefs != num_xrefs_done) {
        if (!map_need_hdr)
            map_newpage(1);
        map_unresolved();
    }
}

/* 41d8d1 */
static void map_putstr(char *s)
{
    long save;
    int wrap;

    save = map_lcol;
    if (map_need_hdr) {
        map_need_hdr = 0;
        map_pageheader();
        map_lcol = save;
    }
    for (; *s != '\0'; s++) {
        save = map_lcol;
        wrap = map_width < map_col;
        map_col++;
        if (wrap && *s != '\n')
            map_newline();
        map_lcol = save + 1;
        if (*s == '\n') {
            map_newline();
        } else if (putc(*s, map_fp) == EOF) {
            lnk_fatal1("Cannot write string to map file");
        }
    }
}

/* 41da05 */
static void map_newline(void)
{
    if (map_line < map_lastline) {
        if (putc('\n', map_fp) == EOF)
            lnk_fatal1("Cannot write new line to map file");
        map_line++;
        map_col = 1;
        map_lcol = 1;
    } else {
        map_newpage(1);
    }
    map_leftmargin();
}

/* 41dac4 */
static void map_leftmargin(void)
{
    for (; map_col < map_lmargin; map_col++) {
        if (putc(' ', map_fp) == EOF)
            lnk_fatal1("Cannot write left margin to map file");
    }
}

/* 41db64 */
static void map_newpage(int hdr)
{
    if (!opt_ff) {
        for (; map_line <= map_pagelen; map_line++) {
            if (putc('\n', map_fp) == EOF)
                lnk_fatal1("Cannot write new page to map file");
        }
    } else {
        if (putc('\f', map_fp) == EOF)
            lnk_fatal1("Cannot write form feed to map file");
    }
    if (hdr) {
        map_col = 1;
        map_lcol = 1;
        map_line = 1;
        map_pageno++;
        map_pageheader();
    }
}

/* 41dcc0 */
static void map_pageheader(void)
{
    for (map_line = 1; map_line <= map_topmargin; map_line++) {
        if (putc('\n', map_fp) == EOF)
            lnk_fatal1("Cannot write page header to map file");
    }
    if (map_hdr_on)
        map_banner();
}

/* 41dd75 */
static void map_banner(void)
{
    char buf[16];

    map_leftmargin();
    map_putstr("DSP ");
    map_putstr(lnk_name);
    map_putstr("  Version ");
    map_putstr_wrap(opt_t ? "XXXX" : lnk_version);
    map_putstr("  ");
    map_putstr_wrap(opt_t ? "00-00-00" : date_str);
    map_putstr("  ");
    map_putstr_wrap(opt_t ? "00:00:00" : time_str);
    map_putstr("  ");
    map_putstr_wrap(opt_t ? base_name(title_name) : title_name);
    sprintf(buf, "  Page %ld\n", map_pageno);
    map_putstr_wrap(buf);
    map_newline();
    map_newline();
}

/* 41dea5 */
static void map_putstr_wrap(char *s)
{
    long len;
    long save;

    len = (long)strlen(s);
    save = map_lcol;
    if (len <= map_width - map_lmargin + 1 && map_width < len + map_col)
        map_newline();
    map_lcol = save;
    map_putstr(s);
}

/* 41df05: -x ovlp overlap warnings (called by finish_link) */
void map_check_overlap(void)
{
    SECTION **arr;
    SECTION *p;
    int first;
    unsigned long prev_end;
    unsigned long prev_ovl;
    long space;
    long cntr;
    long i;
    unsigned long lo, hi, ovl;
    char *name;

    if (opt_i || opt_ro || !opt_ovlp || num_secs == 0)
        return;
    /* The original frees map_secs and then calls map_collect_secs, which
       still sees the stale pointer and returns the freed array unchanged
       (no re-collection, no clearing of the symbol lists); it then sets
       map_secs to 0.  Reproduced without the use-after-free. */
    arr = map_collect_secs();
    map_sort_secs_memspace(arr, num_secs);
    first = 1;
    prev_end = 0;
    prev_ovl = 0;
    space = MS_N;
    cntr = 0;
    for (i = 0; i < num_secs; i++) {
        p = arr[i];
        if (p->node->spec.mspace != space) {
            space = p->node->spec.mspace;
            cntr = p->node->spec.mcntr;
            first = 1;
            prev_ovl = 0;
        }
        lo = p->lo;
        hi = p->hi;
        if (lo < hi) {
            ovl = p->flags & SF_OVL;
            if ((p->flags & SF_BUF) == 0 && ovl == 0)
                name = SECNAME_OF(p);
            else
                name = OWNNAME_OF(p);
            if (!first && lo <= prev_end && ovl == 0 && prev_ovl == 0 &&
                (p->flags & SF_BUF) == 0) {
                sprintf(namebuf, "Overlap of section \"%s\" at address %c(%ld):%lX",
                        name, mem_idx_char[mem_space_index(space)], cntr, lo);
                lnk_warning1(namebuf);
            }
            first = 0;
            prev_ovl = ovl;
            prev_end = M32(hi - 1);
        }
    }
    xfree(arr);
    map_secs = NULL;
}

/* one UNUSED/section address row of map_sec_by_addr */
static void addr_row(int w8, int w6, char *f8, char *f6, char *f4,
                     unsigned long a, unsigned long b, unsigned long c)
{
    if (w8)
        sprintf(namebuf, f8, a, b, c);
    else if (w6)
        sprintf(namebuf, f6, a, b, c);
    else
        sprintf(namebuf, f4, a, b, c);
}

#define CPU_W8()  (target_index == 1 || target_index == 6)
#define CPU_W6()  (target_index == 3 || target_index == 4 || target_index == 5)
#define CPU_WIDE() (target_index == 1 || target_index == 3 || \
                    target_index == 4 || target_index == 5)

static char *mem_letter(long space)
{
    switch (mem_space_index(space)) {
    case 1: return "X";
    case 2: return "Y";
    case 3: return "L";
    case 4: return "P";
    case 5: return "E";
    case 6: return "D";
    case 7: return "U";
    }
    return NULL;
}

static char *mem_letter_colon(long space)
{
    switch (mem_space_index(space)) {
    case 1: return "X:";
    case 2: return "Y:";
    case 3: return "L:";
    case 4: return "P:";
    case 5: return "E:";
    case 6: return "D:";
    case 7: return "U:";
    }
    return NULL;
}

static void put_letter(char *s)
{
    if (s != NULL)
        map_putstr(s);
}

/* 41e110 */
static void map_sec_by_addr(void)
{
    SECTION **arr;
    SECTION *p;
    unsigned long lo, hi, mask, next, prev_end, ovl, prev_ovl, len;
    long space, cntr, i;
    int first, emi, tabcol;
    double wrapv;
    char *name;

    mask = addr_mask;
    if (num_secs == 0 || !map_secaddr)
        return;
    if (map_secs == NULL) {
        arr = map_collect_secs();
        map_secs = arr;
        map_sort_secs_addr(arr, num_secs);
    } else {
        arr = map_secs;
    }
    map_putstr("                        Section Link Map by Address");
    map_newline();
    space = MS_N;
    cntr = 0;
    first = 1;
    emi = 0;
    tabcol = CPU_WIDE() ? 0x22 : 0x1e;
    next = 0;
    prev_ovl = 0;
    prev_end = 0;
    wrapv = 0.0;
    for (i = 0; i < num_secs; i++) {
        p = arr[i];
        if (((p->flags & SF_BUF) != 0 && !map_buffer) ||
            ((p->flags & SF_OVL) != 0 && !map_overlay))
            continue;
        lo = p->lo;
        hi = p->hi;
        if (hi == lo)
            continue;
        if (p->node->spec.mspace != space || p->node->spec.mcntr != cntr) {
            emi = (space == MS_E || space == MS_D);
            tabcol = (CPU_WIDE() || emi) ? 0x22 : 0x1e;
            if (map_unused && space != MS_N && next < mask && wrapv < 1.0) {
                addr_row(CPU_W8(), CPU_W6() || emi,
                         "%08lX  %08lX  %10lu     UNUSED",
                         "%06lX   %06lX    %8lu    UNUSED",
                         "%04lX     %04lX    %5lu     UNUSED",
                         next, mask, M32(mask - next + 1));
                map_putstr(namebuf);
                map_newline();
                namebuf[0] = '\0';
            }
            space = p->node->spec.mspace;
            cntr = p->node->spec.mcntr;
            emi = (space == MS_E || space == MS_D);
            if (!opt_abc || space == MS_E || space == MS_D ||
                (target_index == 4 && space == MS_P))
                mask = ext_addr_mask;
            else
                mask = addr_mask;
            first = 1;
            prev_end = 0;
            next = 0;
            wrapv = 0.0;
            prev_ovl = 0;
            map_newline();
            map_newline();
            put_letter(mem_letter(space));
            map_putstr(" Memory (");
            sprintf(namebuf, "%ld", cntr);
            map_putstr(namebuf);
            if (cntr == 0)
                map_putstr(" - default");
            else if (cntr == 1)
                map_putstr(" - low");
            else if (cntr == 2)
                map_putstr(" - high");
            map_putstr(")");
            map_newline();
            map_newline();
            if (CPU_W8())
                map_putstr("Start     End           Length     Section");
            else if (CPU_W6() || emi)
                map_putstr("Start    End         Length    Section");
            else
                map_putstr("Start    End     Length    Section");
            map_newline();
        }
        if (lo < hi) {
            len = M32(hi - lo);
        } else {
            wrapv = ((double)mask + (double)M32(hi + 1)) - (double)lo;
            len = M32((unsigned long)wrapv);
        }
        if (map_unused && next < lo) {
            addr_row(CPU_W8(), CPU_W6() || emi,
                     "%08lX  %08lX  %10lu     UNUSED",
                     "%06lX   %06lX    %8lu    UNUSED",
                     "%04lX     %04lX    %5lu     UNUSED",
                     next, M32(lo - 1), M32(lo - next));
            map_putstr(namebuf);
            map_newline();
            namebuf[0] = '\0';
            if (next < M32(lo + len))
                next = M32(lo + len);
        }
        hi = p->hi;
        ovl = p->flags & SF_OVL;
        if (next < M32(lo + len))
            next = M32(lo + len);
        addr_row(CPU_W8(), CPU_W6() || emi,
                 "%08lX  %08lX  %10lu     ",
                 "%06lX   %06lX    %8lu    ",
                 "%04lX     %04lX    %5lu     ",
                 lo, M32(p->hi - 1) & mask, len);
        map_putstr(namebuf);
        if ((p->flags & SF_BUF) == 0 && ovl == 0)
            name = SECNAME_OF(p);
        else
            name = OWNNAME_OF(p);
        strncpy(namebuf, name, 16);
        namebuf[16] = '\0';
        map_putstr(namebuf);
        if ((p->flags & SF_REL) == 0) {
            map_tab(tabcol + 0x10);
            map_putstr("Abs");
        }
        if ((p->flags & SF_BUF) != 0) {
            map_tab(tabcol + 0x10);
            if ((p->state & SS_MODBUF) != 0)
                map_putstr("Mod");
            else if ((p->state & SS_REVBUF) != 0)
                map_putstr("Rev");
            else
                map_putstr("Buf");
            if ((p->flags & SF_ALIGNED) != 0)
                map_putstr("+");
        }
        if (ovl != 0) {
            map_tab(tabcol + 0x10);
            map_putstr("Ovl");
        }
        if (!opt_i && !first && lo <= prev_end && !opt_ro && ovl == 0 &&
            prev_ovl == 0 && (p->flags & SF_BUF) == 0) {
            map_tab(tabcol + 0x10);
            map_putstr("*Overlap*");
        }
        first = 0;
        map_newline();
        prev_ovl = ovl;
        prev_end = M32(hi - 1);
    }
    if (map_unused && space != MS_N && next < mask && wrapv < 1.0) {
        addr_row(CPU_W8(), CPU_W6() || emi,
                 "%08lX  %08lX  %10lu     UNUSED",
                 "%06lX   %06lX    %8lu    UNUSED",
                 "%04lX     %04lX    %5lu     UNUSED",
                 next, mask, M32(mask - next + 1));
        map_putstr(namebuf);
        map_newline();
        namebuf[0] = '\0';
    }
    map_newline();
    map_newline();
    map_newline();
}

/* 41eb80 */
static void map_tab(int col)
{
    if (map_lcol < col) {
        while (map_lcol < col)
            map_putstr(" ");
    } else {
        map_putstr(" ");
    }
}

/* 41ebb8 */
static void map_sort_secs_addr(SECTION **arr, long n)
{
    sort_array = (void **)arr;
    sort_cmp = sec_cmp_addr;
    sort_ptrs(0L, n - 1);
}

/* flags tie-break shared by the section comparators */
static long flags_cmp(unsigned long f1, unsigned long f2)
{
    if ((f1 & SF_REL) != 0 && (f2 & SF_REL) == 0)
        return -1;
    if ((f1 & SF_REL) == 0 && (f2 & SF_REL) != 0)
        return 1;
    return diff32(f1, f2);
}

/* 41ebe0 */
static long sec_cmp_addr(void *a, void *b)
{
    SECTION *p1 = (SECTION *)a;
    SECTION *p2 = (SECTION *)b;
    unsigned long c1, c2;
    long r;

    r = mem_order(p1->node->spec.mspace, p2->node->spec.mspace);
    if (r != 0)
        return r;
    c1 = (unsigned long)p1->node->spec.mcntr;
    c2 = (unsigned long)p2->node->spec.mcntr;
    if (M32(c1) < M32(c2))
        return -1;
    if (M32(c2) < M32(c1))
        return 1;
    if (p1->lo < p2->lo)
        return -1;
    if (p2->lo < p1->lo)
        return 1;
    if (p2->hi < p1->hi)
        return -1;
    if (p1->hi < p2->hi)
        return 1;
    r = sgn(strcmp(SECNAME_OF(p1), SECNAME_OF(p2)));
    if (r != 0)
        return r;
    return flags_cmp(p1->flags, p2->flags);
}

/* 41ed36: fixup sorts buffer pieces by size */
void map_sort_pieces_size(SECTION **arr, long n)
{
    sort_array = (void **)arr;
    sort_cmp = piece_cmp_size;
    sort_ptrs(0L, n - 1);
}

/* 41ed5e: size descending */
static long piece_cmp_size(void *a, void *b)
{
    SECTION *p1 = (SECTION *)a;
    SECTION *p2 = (SECTION *)b;
    unsigned long s1, s2;

    s1 = M32(p1->hi - p1->lo);
    s2 = M32(p2->hi - p2->lo);
    if (s1 < s2)
        return 1;
    if (s2 < s1)
        return -1;
    return 0;
}

/* 41eda4 */
void map_sort_pieces_num(SECTION **arr, long n)
{
    sort_array = (void **)arr;
    sort_cmp = piece_cmp_num;
    sort_ptrs(0L, n - 1);
}

/* 41edcc */
static long piece_cmp_num(void *a, void *b)
{
    SECTION *p1 = (SECTION *)a;
    SECTION *p2 = (SECTION *)b;
    long r;

    r = diff32((unsigned long)p1->node->sname->num, (unsigned long)p2->node->sname->num);
    if (r == 0)
        r = diff32((unsigned long)p1->index, (unsigned long)p2->index);
    return r;
}

/* 41ee04 */
void map_sort_memregs(MEMREG **arr, long n)
{
    sort_array = (void **)arr;
    sort_cmp = memreg_cmp;
    sort_ptrs(0L, n - 1);
}

/* 41ee2c */
static long memreg_cmp(void *a, void *b)
{
    MEMREG *m1 = (MEMREG *)a;
    MEMREG *m2 = (MEMREG *)b;
    long r;

    r = diff32((unsigned long)m1->spec.mcntr, (unsigned long)m2->spec.mcntr);
    if (r == 0)
        r = mem_order_l(m1->spec.mspace, m2->spec.mspace);
    return r;
}

/* 41ee64 */
static void map_sec_by_name(void)
{
    SECTION **arr;
    SECTION *p;
    char *b;
    unsigned long lo, hi, mask, len;
    long space, cntr, i, j, run;
    int need_nl, none, printed;

    if (num_secs == 0 || !map_secname)
        return;
    if (map_secs == NULL)
        map_secs = map_collect_secs();
    arr = map_secs;
    map_sort_secs_name(arr, num_secs);
    map_putstr("                         Section Link Map by Name");
    map_newline();
    map_newline();
    map_newline();
    map_putstr("Section                Memory       Start     End           Length");
    map_newline();
    for (i = 0; i < num_secs; i += run) {
        strncpy(namebuf, SECNAME_OF(arr[i]), 16);
        namebuf[16] = '\0';
        map_putstr(namebuf);
        need_nl = 1;
        none = 1;
        printed = 0;
        b = SECNAME_OF(arr[i]);
        run = i;
        do {
            run++;
            if (arr[run] == NULL)
                break;
        } while (SECNAME_OF(arr[run]) == b);
        run -= i;
        if (run > 1)
            map_sort_secs_addr(arr + i, run);
        for (j = 0; j < run; j++) {
            p = arr[i + j];
            if (((p->flags & SF_BUF) != 0 && !map_buffer) ||
                ((p->flags & SF_OVL) != 0 && !map_overlay))
                continue;
            lo = p->lo;
            hi = p->hi;
            if (hi == lo)
                continue;
            space = p->node->spec.mspace;
            cntr = p->node->spec.mcntr;
            if (!opt_abc || space == MS_E || space == MS_D ||
                (target_index == 4 && space == MS_P))
                mask = ext_addr_mask;
            else
                mask = addr_mask;
            if (lo < hi)
                len = M32(hi - lo);
            else
                len = M32((unsigned long)(((double)mask + (double)M32(hi + 1))
                                          - (double)lo));
            mask = M32(p->hi - 1) & mask;
            none = 0;
            if ((p->flags & (SF_BUF | SF_OVL)) != 0 &&
                strcmp(OWNNAME_OF(p), b) != 0) {
                if (need_nl) {
                    need_nl = 0;
                    if (!printed)
                        map_newline();
                }
                map_tab(3);
                strncpy(namebuf, OWNNAME_OF(p), 14);
                namebuf[14] = '\0';
                map_putstr(namebuf);
            }
            printed = 1;
            map_tab(0x12);
            if ((p->flags & SF_BUF) == 0) {
                if ((p->flags & SF_OVL) != 0)
                    map_putstr("Ovl");
                else if ((p->flags & SF_REL) == 0)
                    map_putstr("Abs");
            } else {
                if ((p->state & SS_MODBUF) != 0)
                    map_putstr("Mod");
                else if ((p->state & SS_REVBUF) != 0)
                    map_putstr("Rev");
                else
                    map_putstr("Buf");
                if ((p->flags & SF_ALIGNED) != 0)
                    map_putstr("+");
            }
            map_tab(0x18);
            put_letter(mem_letter(space));
            sprintf(namebuf, " (%ld)", cntr);
            map_putstr(namebuf);
            map_tab(0x25);
            if (CPU_W8())
                sprintf(namebuf, "%08lX  %08lX  %10lu", lo, mask, len);
            else if (CPU_W6() || space == MS_E || space == MS_D)
                sprintf(namebuf, "%06lX    %06lX      %8lu", lo, mask, len);
            else
                sprintf(namebuf, "%04lX      %04lX           %5lu", lo, mask, len);
            map_putstr(namebuf);
            map_newline();
        }
        if (none) {
            map_tab(0x18);
            map_putstr("None");
            map_newline();
        }
    }
    map_newline();
    map_newline();
    map_newline();
}

/* 41f45b */
static void map_sort_secs_name(SECTION **arr, long n)
{
    sort_array = (void **)arr;
    sort_cmp = sec_cmp_name;
    sort_ptrs(0L, n - 1);
}

/* 41f483 */
static long sec_cmp_name(void *a, void *b)
{
    SECTION *p1 = (SECTION *)a;
    SECTION *p2 = (SECTION *)b;
    unsigned long c1, c2;
    long r;

    r = sgn(strcmp(SECNAME_OF(p1), SECNAME_OF(p2)));
    if (r != 0)
        return r;
    r = mem_order(p1->node->spec.mspace, p2->node->spec.mspace);
    if (r != 0)
        return r;
    c1 = M32(p1->node->spec.mcntr);
    c2 = M32(p2->node->spec.mcntr);
    if (c1 < c2)
        return -1;
    if (c2 < c1)
        return 1;
    if (p1->lo < p2->lo)
        return -1;
    if (p2->lo < p1->lo)
        return 1;
    if (p2->hi < p1->hi)
        return -1;
    if (p1->hi < p2->hi)
        return 1;
    return flags_cmp(p1->flags, p2->flags);
}

/* 41f5d6: NULL-terminated array of every section piece (cached) */
static SECTION **map_collect_secs(void)
{
    SECTION **arr;
    SECNAME *sn;
    SECNODE *nd;
    SECTION *p;
    long n;
    int h;

    if (num_secs == 0)
        return NULL;
    if (map_secs != NULL)
        return map_secs;
    arr = (SECTION **)xmalloc((unsigned long)(num_secs + 1) * sizeof(SECTION *));
    map_secs = arr;
    n = 0;
    for (h = 0; h < HASHSIZE; h++) {
        for (sn = sec_hash[h]; sn != NULL; sn = sn->hnext) {
            for (nd = sn->nodes; nd != NULL; nd = nd->next) {
                for (p = nd->secs; p != NULL; p = p->next) {
                    arr[n++] = p;
                    p->msyms = NULL;
                    p->ovl = NULL;          /* same slot (+0x3c) in the original */
                }
                for (p = nd->abss; p != NULL; p = p->next) {
                    arr[n++] = p;
                    p->msyms = NULL;
                    p->ovl = NULL;
                }
                for (p = nd->bufs; p != NULL; p = p->next) {
                    arr[n++] = p;
                    p->msyms = NULL;
                    p->ovl = NULL;
                }
                for (p = nd->ovls; p != NULL; p = p->next) {
                    arr[n++] = p;
                    p->msyms = NULL;
                    p->ovl = NULL;
                }
            }
        }
    }
    arr[n] = NULL;
    return arr;
}

/* cached array of every symbol (map_syms) */
static SYM **map_collect_syms(void)
{
    SYM **arr;
    SYM *s;
    long n;
    int h;

    if (map_syms != NULL)
        return map_syms;
    arr = (SYM **)xmalloc((unsigned long)num_syms * sizeof(SYM *));
    map_syms = arr;
    n = 0;
    for (h = 0; h < HASHSIZE; h++)
        for (s = sym_hash[h]; s != NULL; s = s->next)
            arr[n++] = s;
    return arr;
}

/* symbols with SYM_SPECIAL lose their memory spec before listing */
static int sym_listed(SYM *s)
{
    if ((s->flags & SYM_SPECIAL) != 0) {
        s->mem.mmap = 4;
        s->mem.mspace = 4;
        s->mem.mcntr = 0;
        s->mem.mclass = 0;
    }
    return (s->sec != NULL || (s->flags & SYM_SPECIAL) != 0) &&
           (map_const || s->mem.mspace != MS_N) &&
           (map_local || (s->flags & (SYM_GLOBAL | SYM_XDEF)) != 0);
}

/* value of a symbol into namebuf (symbol tables); frc values print
   nothing new: namebuf keeps its previous contents */
static void sym_value_str(SYM *s)
{
    long space;
    char *fmt;
    unsigned long mask, fl;

    space = s->mem.mspace;
    fl = s->flags;
    if (space == MS_N)
        fmt = value_fmt;
    else if (!opt_abc || space == MS_E || space == MS_D)
        fmt = "%08lX";
    else
        fmt = addr_fmt;
    if (space == MS_N)
        mask = word_mask;
    else if (!opt_abc || space == MS_E || space == MS_D)
        mask = ext_addr_mask;
    else
        mask = addr_mask;
    if ((fl & SYM_FLOAT) != 0) {
        fmt_double(namebuf, "%-.6E", s->fval);
    } else if ((fl & SYM_INT) != 0) {
        if ((fl & SYM_LONG) == 0) {
            sprintf(namebuf, fmt, s->lo & mask);
        } else if ((target_index == 4 || target_index == 6) && space == MS_P) {
            sprintf(namebuf, fmt,
                    M32((s->hi << (int)(word_bits & 0x1f)) | s->lo) & ext_addr_mask);
        } else if (target_index == 7 && (space == MS_P || space == MS_N)) {
            sprintf(namebuf, fmt,
                    M32((s->hi << (int)(word_bits & 0x1f)) | s->lo) & 0xfffffffUL);
        } else {
            sprintf(namebuf, fmt, s->hi & mask);
            sprintf(namebuf + strlen(namebuf), fmt, s->lo & mask);
        }
    }
}

/* long name (MAP OPT symlen) into namebuf; strncpy may leave it
   unterminated at map_symlen chars, as in the original */
static void sym_long_name(SYM *s)
{
    if (strlen(s->name) < 0x200) {
        if (map_symlen < 1)
            strcpy(namebuf, s->name);
        else
            strncpy(namebuf, s->name, (size_t)map_symlen);
    } else {
        strncpy(namebuf, s->name, 0x1ff);
        namebuf[0x1ff] = '\0';
    }
}

/* 41f797 */
static void map_sym_by_name(void)
{
    SYM **arr;
    SYM *s;
    unsigned long fl;
    long space, i;
    int none;

    if (num_syms == 0 || !map_symname)
        return;
    arr = map_collect_syms();
    map_sort_syms_name(arr, num_syms);
    map_putstr("                          Symbol Listing by Name");
    map_newline();
    map_newline();
    map_newline();
    map_putstr("Name             Type    Value             Section           Attributes");
    map_newline();
    none = 1;
    for (i = 0; i < num_syms; i++) {
        s = arr[i];
        fl = s->flags;
        if (!sym_listed(s))
            continue;
        space = s->mem.mspace;
        none = 0;
        if (strlen(s->name) < 0x11 || map_symlen_on != 1) {
            strncpy(namebuf, s->name, 16);
            namebuf[16] = '\0';
            map_putstr(namebuf);
        } else {
            sym_long_name(s);
            map_putstr(namebuf);
            map_newline();
        }
        map_tab_dots(0x12);
        if ((fl & SYM_FLOAT) != 0)
            map_putstr("fpt");
        else if ((fl & SYM_INT) != 0)
            map_putstr("int");
        else
            map_putstr("frc");
        map_tab(0x18);
        if (space == MS_E)
            map_putstr("E:");
        else if (space == MS_D)
            map_putstr("D:");
        else if (space == MS_U)
            map_putstr("U:");
        else if (space == MS_P)
            map_putstr("P:");
        else if (space == MS_X)
            map_putstr("X:");
        else if (space == MS_Y)
            map_putstr("Y:");
        else if (space == MS_L)
            map_putstr("L:");
        else
            map_putstr("  ");
        sym_value_str(s);
        map_putstr(namebuf);
        map_tab(0x2c);
        if ((fl & SYM_SPECIAL) == 0)
            strncpy(namebuf, SECNAME_OF(s->sec), 16);
        else
            namebuf[0] = '\0';
        namebuf[16] = '\0';
        map_putstr(namebuf);
        map_tab(0x3e);
        if ((fl & SYM_REL) == 0)
            map_putstr("ABS");
        else
            map_putstr("REL");
        if ((fl & SYM_LOCAL) != 0) {
            map_tab(0x3e);
            map_putstr("LOCAL");
        } else if ((fl & SYM_XDEF) != 0) {
            map_tab(0x3e);
            map_putstr("EXTERN");
        } else if ((fl & SYM_GLOBAL) != 0) {
            map_tab(0x3e);
            map_putstr("GLOBAL");
        }
        if ((fl & SYM_BUFFER) != 0) {
            map_tab(0x3e);
            map_putstr("BUFFER");
        }
        if ((fl & SYM_OVERLAY) != 0) {
            map_tab(0x3e);
            map_putstr("OVERLAY");
        }
        map_newline();
    }
    if (none) {
        map_newline();
        map_putstr("  No symbols");
    }
    map_newline();
    map_newline();
    map_newline();
}

/* 41feae */
static void map_tab_dots(int col)
{
    while (map_lcol < col)
        map_putstr(".");
}

/* 41fecc */
static void map_sort_syms_name(SYM **arr, long n)
{
    sort_array = (void **)arr;
    sort_cmp = sym_cmp_name;
    sort_ptrs(0L, n - 1);
}

/* numeric value of a symbol for the comparators */
static double sym_num(SYM *s)
{
    if ((s->flags & SYM_FLOAT) != 0)
        return s->fval;
    if ((s->flags & SYM_LONG) != 0)
        return long_to_double(s->hi, s->lo);
    if (s->mem.mspace == MS_N)
        return int_to_double(s->lo);
    return long_to_double(0UL, s->lo);
}

/* 41fef4 */
static long sym_cmp_name(void *a, void *b)
{
    SYM *s1 = (SYM *)a;
    SYM *s2 = (SYM *)b;
    double v1, v2;
    long r;

    r = sgn(strcmp(s1->name, s2->name));
    if (r != 0)
        return r;
    if (s1->sec == NULL && s2->sec == NULL)
        return 0;
    if (s2->sec == NULL)
        return 1;
    if (s1->sec == NULL)
        return -1;
    if (s1->sec != s2->sec)
        return diff32((unsigned long)s1->sec->node->sname->num,
                      (unsigned long)s2->sec->node->sname->num);
    v1 = sym_num(s1);
    v2 = sym_num(s2);
    if (0.0 <= v1 - v2) {
        if (v1 - v2 <= 0.0)
            return 0;
        return 1;
    }
    return -1;
}

/* 4200d0 */
static void map_sym_by_value(void)
{
    static char hdr[] = "Value             Name              ";
    SYM **arr;
    SYM *s;
    long hlen, off, i, len, pad;
    int none;

    if (num_syms == 0 || !map_symval)
        return;
    arr = map_collect_syms();
    map_sort_syms_value(arr, num_syms);
    map_putstr("                          Symbol Listing by Value");
    map_newline();
    map_newline();
    map_newline();
    hlen = (long)strlen(hdr);
    do {
        map_putstr(hdr);
        if (map_symlen_on == 1)
            break;
    } while (map_col + hlen < map_width);
    map_newline();
    off = 0;
    none = 1;
    for (i = 0; i < num_syms; i++) {
        s = arr[i];
        if (!sym_listed(s))
            continue;
        none = 0;
        sym_value_str(s);
        map_putstr(namebuf);
        map_tab((int)(off + 0x13));
        if (map_symlen_on == 1) {
            sym_long_name(s);
            map_putstr(namebuf);
            map_newline();
        } else {
            strncpy(namebuf, s->name, 16);
            namebuf[16] = '\0';
            map_putstr(namebuf);
            len = (long)strlen(namebuf);
            if (len < 0x11)
                pad = 0x12 - len;
            else
                pad = 2;
            if (map_col + pad + hlen < map_width) {
                off += hlen;
                map_tab((int)(off + 1));
            } else {
                off = 0;
                map_newline();
            }
        }
    }
    if (none) {
        map_newline();
        map_putstr("  No symbols");
    }
    map_newline();
    map_newline();
    map_newline();
}

/* 42062b */
static void map_sort_syms_value(SYM **arr, long n)
{
    sort_array = (void **)arr;
    sort_cmp = sym_cmp_value;
    sort_ptrs(0L, n - 1);
}

/* 420653 */
static long sym_cmp_value(void *a, void *b)
{
    SYM *s1 = (SYM *)a;
    SYM *s2 = (SYM *)b;
    double v1, v2;

    if ((s1->sec != NULL || (s1->flags & SYM_SPECIAL) != 0) &&
        (s2->sec != NULL || (s2->flags & SYM_SPECIAL) != 0)) {
        v1 = sym_num(s1);
        v2 = sym_num(s2);
        if (v1 - v2 < 0.0)
            return -1;
        if (0.0 < v1 - v2)
            return 1;
    }
    return sgn(strcmp(s1->name, s2->name));
}

/* 4207e9 */
static void map_global_by_memspace(void)
{
    SECTION **arr;
    SECTION *p;
    SYMLIST *sl, *slnext;
    SYM *s;
    int wide, emi, first, sfirst;
    int attrcol, ovlcol;
    long space, i;
    unsigned long lo, hi, mask, next, prev_end, prev_ovl, ovl, len, end;
    unsigned long sprev, vmask;
    double wrapv;
    char *fmt, *name;

    if (num_secs == 0 || !map_globmap)
        return;
    if (map_secs == NULL)
        map_secs = map_collect_secs();
    arr = map_secs;
    map_sort_secs_memspace(arr, num_secs);
    if (map_syms != NULL) {
        xfree(map_syms);
        map_syms = NULL;
    }
    if (map_globsym)
        map_build_sec_symlists();
    map_putstr("                      Global Link Map by Memory Space");
    map_newline();
    space = MS_N;
    first = 1;
    emi = 0;
    wide = CPU_WIDE();
    attrcol = wide ? 0x2e : 0x2b;
    ovlcol = wide ? 0x4c : 0x46;
    next = 0;
    prev_ovl = 0;
    prev_end = 0;
    mask = addr_mask;
    wrapv = 0.0;
    for (i = 0; i < num_secs; i++) {
        p = arr[i];
        if (((p->flags & SF_BUF) != 0 && !map_buffer) ||
            ((p->flags & SF_OVL) != 0 && !map_overlay))
            continue;
        lo = p->lo;
        hi = p->hi;
        if (hi == lo && !(map_globsym && p->msyms != NULL))
            continue;
        if (p->node->spec.mspace != space) {
            emi = (space == MS_E || space == MS_D);
            if (map_unused && space != MS_N && next < mask && wrapv < 1.0) {
                /* no else: the 8-digit form is overwritten (original bug) */
                if (CPU_W8())
                    sprintf(namebuf, "%08lX  %08lX  UNUSED", next, mask);
                if (CPU_W6() || emi)
                    sprintf(namebuf, "%06lX    %06lX    UNUSED", next, mask);
                else
                    sprintf(namebuf, "%04lX     %04lX    UNUSED", next, mask);
                map_putstr(namebuf);
                map_newline();
                namebuf[0] = '\0';
            }
            space = p->node->spec.mspace;
            emi = (space == MS_E || space == MS_D);
            if (!opt_abc || space == MS_E || space == MS_D ||
                (target_index == 4 && space == MS_P))
                mask = ext_addr_mask;
            else
                mask = addr_mask;
            first = 1;
            prev_end = 0;
            next = 0;
            wrapv = 0.0;
            prev_ovl = 0;
            map_newline();
            map_newline();
            put_letter(mem_letter(space));
            map_putstr(" Memory");
            map_newline();
            map_newline();
            if (wide || emi)
                map_putstr("Start     End       Section          Counter  Symbol              Value");
            else
                map_putstr("Start    End     Section          Counter  Symbol              Value");
            map_newline();
        }
        end = prev_end;
        if (hi == lo)
            len = 0;
        else if (lo < hi)
            len = M32(hi - lo);
        else {
            wrapv = ((double)mask + (double)M32(hi + 1)) - (double)lo;
            len = M32((unsigned long)wrapv);
        }
        if (map_unused && next < lo) {
            if (CPU_W8())
                sprintf(namebuf, "%08lX  %08lX  UNUSED", next, M32(lo - 1));
            else if (CPU_W6() || emi)
                sprintf(namebuf, "%06lX    %06lX    UNUSED", next, M32(lo - 1));
            else
                sprintf(namebuf, "%04lX     %04lX    UNUSED", next, M32(lo - 1));
            map_putstr(namebuf);
            map_newline();
            namebuf[0] = '\0';
            if (next < M32(lo + len))
                next = M32(lo + len);
        }
        prev_end = (len == 0) ? p->hi : M32(p->hi - 1);
        ovl = p->flags & SF_OVL;
        if (next < M32(lo + len))
            next = M32(lo + len);
        if (len == 0) {
            map_tab(wide ? 0x15 : 0x12);
        } else {
            if (CPU_W8())
                sprintf(namebuf, "%08lX  %08lX  ", lo, prev_end & mask);
            if (CPU_W6() || emi)
                sprintf(namebuf, "%06lX    %06lX    ", lo, prev_end & mask);
            else
                sprintf(namebuf, "%04lX     %04lX    ", lo, prev_end & mask);
            map_putstr(namebuf);
        }
        if ((p->flags & SF_BUF) == 0 && ovl == 0)
            name = SECNAME_OF(p);
        else
            name = OWNNAME_OF(p);
        strncpy(namebuf, name, 16);
        namebuf[16] = '\0';
        map_putstr(namebuf);
        map_tab(wide ? 0x26 : 0x23);
        sprintf(namebuf, "%-6ld", p->node->spec.mcntr);
        map_putstr(namebuf);
        map_tab(attrcol);
        if ((p->flags & SF_REL) == 0 || (p->flags & SF_BUF) != 0 || ovl != 0)
            map_putstr("[");
        if ((p->flags & SF_REL) == 0) {
            map_tab(attrcol);
            map_putstr("Abs");
        }
        if ((p->flags & SF_BUF) != 0) {
            map_tab(attrcol);
            if ((p->state & SS_MODBUF) != 0)
                map_putstr("Mod");
            else if ((p->state & SS_REVBUF) != 0)
                map_putstr("Rev");
            else
                map_putstr("Buf");
            if ((p->flags & SF_ALIGNED) != 0)
                map_putstr("+");
        }
        if (ovl != 0) {
            map_tab(attrcol);
            map_putstr("Ovl");
        }
        if ((p->flags & SF_REL) == 0 || (p->flags & SF_BUF) != 0 || ovl != 0) {
            map_tab(attrcol);
            map_putstr("]");
        }
        if (!opt_i && !first && lo <= end && len != 0 && !opt_ro && ovl == 0 &&
            prev_ovl == 0 && (p->flags & SF_BUF) == 0) {
            map_tab(ovlcol);
            map_putstr("*Section Overlap*");
        }
        first = 0;
        map_newline();
        prev_ovl = ovl;
        if (map_globsym) {
            sfirst = 1;
            sprev = 0;
            for (sl = p->msyms; sl != NULL; sl = slnext) {
                s = sl->sym;
                map_tab(attrcol);
                strncpy(namebuf, s->name, 16);
                namebuf[16] = '\0';
                map_putstr(namebuf);
                map_tab(wide ? 0x40 : 0x3d);
                put_letter(mem_letter_colon(space));
                if (space == MS_N)
                    fmt = word_fmt;
                else if (!opt_abc || space == MS_E || space == MS_D)
                    fmt = "%08lX";
                else
                    fmt = addr_fmt;
                vmask = (space == MS_N) ? word_mask : mask;
                if (target_index == 4 && space == MS_P)
                    sprintf(namebuf, fmt,
                            M32((s->hi << (int)(word_bits & 0x1f)) | s->lo) & vmask);
                else
                    sprintf(namebuf, fmt, s->lo & vmask);
                map_putstr(namebuf);
                if (sfirst) {
                    sfirst = 0;
                } else if (s->lo <= sprev) {
                    map_tab(ovlcol);
                    map_putstr("*Symbol Overlap*");
                }
                sprev = s->lo;
                map_newline();
                slnext = sl->next;
                xfree(sl);
            }
            p->msyms = NULL;
        }
    }
    if (map_unused && space != MS_N && next < mask && wrapv < 1.0) {
        if (CPU_W8())
            sprintf(namebuf, "%08lX  %08lX  UNUSED", next, mask);
        else if (CPU_W6() || emi)
            sprintf(namebuf, "%06lX    %06lX    UNUSED", next, mask);
        else
            sprintf(namebuf, "%04lX     %04lX    UNUSED", next, mask);
        map_putstr(namebuf);
        map_newline();
        namebuf[0] = '\0';
    }
    map_newline();
    map_newline();
    map_newline();
}

/* 42154d: per-piece symbol lists ordered by value */
static void map_build_sec_symlists(void)
{
    SYM *s;
    SECTION *p;
    SYMLIST *sl, *prev, *n;
    int h;

    if (num_syms == 0)
        return;
    for (h = 0; h < HASHSIZE; h++) {
        for (s = sym_hash[h]; s != NULL; s = s->next) {
            if (s->mem.mspace == MS_N)
                continue;
            p = s->sec;
            if (p == NULL)          /* the original would crash here */
                continue;
            prev = NULL;
            for (sl = p->msyms; sl != NULL && sl->sym->lo <= s->lo; sl = sl->next)
                prev = sl;
            n = (SYMLIST *)xmalloc(sizeof(SYMLIST));
            n->sym = s;
            if (prev == NULL) {
                n->next = p->msyms;
                p->msyms = n;
            } else {
                n->next = prev->next;
                prev->next = n;
            }
        }
    }
}

/* 42164c */
static void map_sort_secs_memspace(SECTION **arr, long n)
{
    sort_array = (void **)arr;
    sort_cmp = sec_cmp_memspace;
    sort_ptrs(0L, n - 1);
}

/* 421674 */
static long sec_cmp_memspace(void *a, void *b)
{
    SECTION *p1 = (SECTION *)a;
    SECTION *p2 = (SECTION *)b;
    long r;

    r = mem_order(p1->node->spec.mspace, p2->node->spec.mspace);
    if (r != 0)
        return r;
    if (p1->lo < p2->lo)
        return -1;
    if (p2->lo < p1->lo)
        return 1;
    if (p2->hi < p1->hi)
        return -1;
    if (p1->hi < p2->hi)
        return 1;
    r = sgn(strcmp(SECNAME_OF(p1), SECNAME_OF(p2)));
    if (r != 0)
        return r;
    return flags_cmp(p1->flags, p2->flags);
}

/* sorted array of all external references (map_xrefs) */
static XREF **collect_xrefs(void)
{
    XREF **arr;
    XREF *x;
    long n;
    int h;

    if (map_xrefs != NULL)
        xfree(map_xrefs);
    arr = (XREF **)xmalloc((unsigned long)num_xrefs * sizeof(XREF *));
    map_xrefs = arr;
    n = 0;
    for (h = 0; h < HASHSIZE; h++)
        for (x = xref_hash[h]; x != NULL; x = x->next)
            arr[n++] = x;
    map_sort_exts(arr, num_xrefs);
    return arr;
}

/* -t: ".inc" extension rewritten in place to ".cln" */
static void inc_to_cln(char *s)
{
    char *dot;

    dot = strrchr(s, '.');
    if (dot != NULL && strcmp(dot, ".inc") == 0)
        strcpy(dot, ".cln");
}

/* file and member names of an external reference */
static void xref_files(XREF *x, char **file, char **member)
{
    char *m;

    if (x->infile == NULL) {
        *member = "command line";
        *file = "command line";
        return;
    }
    *file = opt_t ? base_name(x->infile->name) : x->infile->name;
    m = x->module->name == NULL ? x->infile->name : x->module->name;
    *member = opt_t ? base_name(m) : m;
    if (opt_t) {
        inc_to_cln(*file);
        inc_to_cln(*member);
    }
}

/* 421791: unresolved list to err_fp (finish_link) */
void map_unresolved_stderr(void)
{
    XREF **arr;
    XREF *x;
    char *lastmem, *lastname, *file, *member;
    int newname, firstname;
    long i;

    if (num_xrefs == num_xrefs_done)
        return;
    arr = collect_xrefs();
    fprintf(err_fp, "\nUnresolved Externals:\n\n");
    lastmem = empty_str;
    lastname = empty_str;
    newname = 1;
    firstname = 1;
    for (i = 0; i < num_xrefs; i++) {
        x = arr[i];
        if ((x->flags & XREF_DONE) != 0)
            continue;
        if (strcmp(lastname, x->name) != 0) {
            if (firstname)
                firstname = 0;
            else
                fprintf(err_fp, ")\n");
            lastname = x->name;
            fprintf(err_fp, "%s (", lastname);
            newname = 1;
        }
        xref_files(x, &file, &member);
        if (newname || strcmp(lastmem, member) != 0) {
            lastmem = member;
            if (newname) {
                newname = 0;
                fprintf(err_fp, "%s", file);
            } else {
                fprintf(err_fp, ",%s", file);
            }
            if (x->infile != NULL && (x->infile->flags & IF_LIBRARY) != 0)
                fprintf(err_fp, "[%s]", member);
        }
    }
    fprintf(err_fp, ")\n");
}

/* 421b2a */
static void map_unresolved(void)
{
    XREF **arr;
    XREF *x;
    char *lastmem, *lastname, *file, *member;
    int newname, firstname;
    long i;

    if (num_xrefs == num_xrefs_done)
        return;
    arr = collect_xrefs();
    map_putstr("Unresolved Externals:");
    map_newline();
    map_newline();
    lastmem = empty_str;
    lastname = empty_str;
    newname = 1;
    firstname = 1;
    for (i = 0; i < num_xrefs; i++) {
        x = arr[i];
        if ((x->flags & XREF_DONE) != 0)
            continue;
        if (strcmp(lastname, x->name) != 0) {
            if (firstname) {
                firstname = 0;
            } else {
                map_putstr(")");
                map_newline();
            }
            lastname = x->name;
            map_putstr(lastname);
            map_putstr(" (");
            newname = 1;
        }
        xref_files(x, &file, &member);
        if (newname || strcmp(lastmem, member) != 0) {
            lastmem = member;
            if (newname)
                newname = 0;
            else
                map_putstr(",");
            map_putstr(file);
            if (x->infile != NULL && (x->infile->flags & IF_LIBRARY) != 0) {
                map_putstr("[");
                map_putstr(member);
                map_putstr("]");
            }
        }
    }
    map_putstr(")");
    map_newline();
    map_newline();
    map_newline();
}

/* 421ec7 */
static void map_sort_exts(XREF **arr, long n)
{
    sort_array = (void **)arr;
    sort_cmp = ext_cmp;
    sort_ptrs(0L, n - 1);
}

/* 421eef */
static long ext_cmp(void *a, void *b)
{
    XREF *x1 = (XREF *)a;
    XREF *x2 = (XREF *)b;
    long r;

    r = sgn(strcmp(x1->name, x2->name));
    if (r != 0)
        return r;
    if (x1->infile == NULL && x2->infile == NULL)
        return 0;
    if (x1->infile == NULL)
        return -1;
    if (x2->infile == NULL)
        return 1;
    if (x1->infile == x2->infile)
        return 0;
    return sgn(strcmp(x1->infile->name, x2->infile->name));
}

/* 421f79: memory space order X < Y < L < P < E < D < U */
int mem_order(long a, long b)
{
    int bl = (b >= 0 && b < 4);     /* P X Y L */

    if (a == MS_E) {
        if (b == MS_D || b == MS_U)
            return -1;
        if (bl)
            return 1;
        return 0;
    }
    if (a == MS_P) {
        if (b == MS_E || b == MS_D || b == MS_U)
            return -1;
        if (b > 0 && b < 4)
            return 1;
        return 0;
    }
    if (a == MS_X) {
        if (b == MS_E || b == MS_P || b == MS_Y || b == MS_L || b == MS_D || b == MS_U)
            return -1;
        return 0;
    }
    if (a == MS_Y) {
        if (b == MS_E || b == MS_P || b == MS_L || b == MS_D || b == MS_U)
            return -1;
        if (b == MS_X)
            return 1;
        return 0;
    }
    if (a == MS_L) {
        if (b == MS_E || b == MS_P || b == MS_D || b == MS_U)
            return -1;
        if (b == MS_X || b == MS_Y)
            return 1;
        return 0;
    }
    if (a == MS_D) {
        if (b == MS_E || bl)
            return 1;
        if (b == MS_U)
            return -1;
        return 0;
    }
    if (a == MS_U) {
        if (b == MS_E || bl || b == MS_D)
            return 1;
        return 0;
    }
    return 0;
}

/* 4221bc: same with L first: L < X < Y < P < E < D < U */
int mem_order_l(long a, long b)
{
    int bl = (b >= 0 && b < 4);

    if (a == MS_E) {
        if (b == MS_D || b == MS_U)
            return -1;
        if (bl)
            return 1;
        return 0;
    }
    if (a == MS_P) {
        if (b == MS_E || b == MS_D || b == MS_U)
            return -1;
        if (b > 0 && b < 4)
            return 1;
        return 0;
    }
    if (a == MS_X) {
        if (b == MS_E || b == MS_P || b == MS_Y || b == MS_D || b == MS_U)
            return -1;
        if (b == MS_L)
            return 1;
        return 0;
    }
    if (a == MS_Y) {
        if (b == MS_E || b == MS_P || b == MS_D || b == MS_U)
            return -1;
        if (b == MS_X || b == MS_L)
            return 1;
        return 0;
    }
    if (a == MS_L) {
        if (b == MS_E || (b >= 0 && b < 3) || b == MS_D || b == MS_U)
            return -1;
        return 0;
    }
    if (a == MS_D) {
        if (b == MS_E || bl)
            return 1;
        if (b == MS_U)
            return -1;
        return 0;
    }
    if (a == MS_U) {
        if (b == MS_E || bl || b == MS_D)
            return 1;
        return 0;
    }
    return 0;
}
