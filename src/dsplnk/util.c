/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), util.c
 * $Id: util.c,v 1.21 1997/07/30 22:07:06 lauren Exp $
 * Reconstructed from 0042e170-00430b99.
 *
 * Memory helpers, table search/sort, name hashing, memory space parsing
 * and mapping, float formatting, and the portable big-endian COFF codecs
 * that replace the original fread_swapped/fwrite_swapped/swap_words family
 * (the original read COFF words on little-endian x86 and swapped them in
 * place; the port decodes every field byte by byte).
 */
#include "dsplnk.h"

static char iobuf0[IOBUFSIZE];      /* 469390 */
static char iobuf1[IOBUFSIZE];      /* 469d98 */
static char sym_buf[0x208];         /* 469b90 get_symbol result */

static void sort_swap(long i, long j);
static long emi_map(long n, long *attr);
static long width_map(long space, int width);

/* ---------------------------------------------------------------------- */

void *xmalloc(unsigned long size)
{
    void *p;

    p = malloc((size_t)(size ? size : 1));
    if (p == NULL)
        lnk_fatal1("Out of memory - link aborted");
    return p;
}

void *xrealloc(void *p, unsigned long size)
{
    void *q;

    q = realloc(p, (size_t)(size ? size : 1));
    if (q == NULL)
        lnk_fatal1("Out of memory - link aborted");
    return q;
}

void xfree(void *p)
{
    free(p);
}

/* binary search; same probe sequence as the original pointer version */
void *tab_search(void *key, void *base, long count, long size,
                 int (*cmp)(void *key, void *elem))
{
    long lo, hi, mid;
    int r;
    char *elem;

    lo = 0;
    hi = count - 1;
    while (hi >= lo) {
        mid = lo + ((hi - lo) >> 1);
        elem = (char *)base + mid * size;
        r = cmp(key, elem);
        if (r < 0)
            hi = mid - 1;
        else if (r > 0)
            lo = mid + 1;
        else
            return elem;
    }
    return NULL;
}

/* quicksort of sort_array[lo..hi] with sort_cmp - exactly the original's
   partitioning (the pivot stays in place; result not always sorted) */
void sort_ptrs(long lo, long hi)
{
    long i, j, mid;
    void *piv;

    if (lo >= hi)
        return;
    i = lo;
    j = hi;
    mid = (lo + hi) / 2;
    piv = sort_array[mid];
    for (;;) {
        while (i < j && sort_cmp(sort_array[i], piv) <= 0)
            i++;
        while (i < j && sort_cmp(sort_array[j], piv) >= 0)
            j--;
        if (j <= i)
            break;
        sort_swap(i, j);
    }
    if (mid < i && sort_cmp(sort_array[i], piv) > 0)
        i--;
    sort_swap(i, mid);
    if (i - lo < hi - i) {
        sort_ptrs(lo, i - 1);
        sort_ptrs(i + 1, hi);
    } else {
        sort_ptrs(i + 1, hi);
        sort_ptrs(lo, i - 1);
    }
}

static void sort_swap(long i, long j)
{
    void *t;

    t = sort_array[i];
    sort_array[i] = sort_array[j];
    sort_array[j] = t;
}

/* PJW hash over SIGNED chars, 32 bit, modulo 2003 */
unsigned long hash_name(char *s)
{
    unsigned long h, g;
    long c;

    h = 0;
    for (; *s != '\0'; s++) {
        c = (long)(signed char)*s;
        h = M32((h << 4) + (unsigned long)c);
        g = h & 0xf0000000UL;
        if (g != 0)
            h = h ^ (g >> 24) ^ g;
    }
    return h % HASHSIZE;
}

char *base_name(char *path)
{
    long i;

    if (path == NULL)
        return NULL;
    for (i = (long)strlen(path); i >= 0 && path[i] != '\\' &&path[i] != ':'; i--)
        ;
    if (i >= 0)
        return path + i + 1;
    return path;
}

/* quoted string (' or ") with doubled quotes and ++ concatenation */
char *get_string(char *src, char *dst)
{
    int q;

    if (*src != '\'' && *src != '"') {
        lnk_error1("Syntax error - expected quote");
        return NULL;
    }
    q = *src++;
    while (*src != '\0') {
        if (*src == q) {
            if (src[1] == q) {
                *dst++ = *src;
                src += 2;
            } else {
                if (src[1] != '+' || src[2] != '+')
                    break;
                if (src[3] != '\'' && src[3] != '"') {
                    lnk_error1("Missing string after concatenation operator");
                    return NULL;
                }
                q = src[3];
                src += 4;
            }
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
    if (*src == q)
        return src + 1;
    lnk_error1("Missing quote in string");
    return NULL;
}

#define UC(c)   ((int)(unsigned char)(c))

char *get_symbol(void)
{
    int n;
    char *d;

    n = 0;
    d = sym_buf;
    if (!isalpha(UC(*input_cursor))) {
        lnk_error1("Invalid symbol");
        return NULL;
    }
    for (;;) {
        if (!isalnum(UC(*input_cursor)) && *input_cursor != '_') {
            *d = '\0';
            return sym_buf;
        }
        n++;
        if (n > 0x200)
            break;
        *d++ = *input_cursor++;
    }
    lnk_error1("Symbol name too long");
    return NULL;
}

/* "(n)" counter: plain digits before a target is known, else evaluated.
   Returns 0 ok, -1 error (counter reset). */
static int get_counter(MEMSPEC *ms)
{
    if (word_mask == 0) {
        ms->mcntr = 0;
        while (isdigit(UC(*input_cursor))) {
            ms->mcntr = (long)M32(ms->mcntr * 10L - '0' + *input_cursor);
            input_cursor++;
        }
    } else {
        ms->mcntr = eval_nonneg_resolved();
        if (ms->mcntr == -1) {
            ms->mcntr = 0;
            return -1;
        }
    }
    return 0;
}

static void default_map(MEMSPEC *ms)
{
    if (ms->mmap == MS_N) {
        if (ms->mspace == MS_U)
            ms->mmap = MM_U8;
        else
            ms->mmap = ms->mspace;
    }
}

/* parse a memory specification "space[m][8|16][ctr][map][(n)]:" at
   input_cursor; 1 ok, 0 not a memory spec, -1 error reported */
int get_mem_spec(MEMSPEC *ms)
{
    char *p;
    int c1;
    long m;

    ms->mmap = 4;
    ms->mspace = 4;
    ms->mcntr = 0;
    ms->mclass = 0;
    if (strchr(input_cursor, ':') == NULL)
        return 0;
    ms->mspace = char_to_mem_space(UC(*input_cursor));
    if (ms->mspace == MS_BAD)
        return 0;
    if (ms->mspace == MS_E && tolower(UC(input_cursor[1])) == 'm')
        input_cursor++;
    if (ms->mspace == MS_D && tolower(UC(input_cursor[1])) == 'm')
        input_cursor++;
    p = input_cursor + 1;
    if (*p == ':') {
        input_cursor = p;
        if (ms->mspace == MS_U)
            ms->mmap = MM_U8;
        else
            ms->mmap = ms->mspace;
        input_cursor++;
        return 1;
    }
    if (*p == '8') {
        input_cursor = p;
        m = width_map(ms->mspace, 8);
        if (m == MS_BAD) {
            lnk_error1("Illegal memory space character");
            return -1;
        }
        ms->mmap = m;
        p = input_cursor + 1;
        if (input_cursor[1] == ':') {
            input_cursor += 2;
            return 1;
        }
    } else if (*p == '1' && input_cursor[2] == '6') {
        input_cursor = p;
        m = width_map(ms->mspace, 16);
        if (m == MS_BAD) {
            lnk_error1("Illegal memory space character");
            return -1;
        }
        ms->mmap = m;
        p = input_cursor + 2;
        if (input_cursor[2] == ':') {
            input_cursor += 3;
            return 1;
        }
    }
    input_cursor = p;
    ms->mcntr = char_to_counter(UC(*input_cursor));
    if (ms->mcntr != -1) {
        p = input_cursor + 1;
        if (*p == ':') {
            input_cursor += 2;
            default_map(ms);
            return 1;
        }
        input_cursor = p;
        if (ms->mspace != MS_U && ms->mmap != MM_P8) {
            if (ms->mspace == MS_E && isdigit(UC(*p))) {
                ms->mmap = emi_map(strtol(input_cursor, NULL, 10), &ms->mclass);
                if (ms->mmap == MS_BAD)
                    return 0;
                while (isdigit(UC(*input_cursor)))
                    input_cursor++;
            } else {
                c1 = UC(*input_cursor);
                if (ms->mmap != 4) {
                    lnk_error1("Illegal memory map character");
                    return -1;
                }
                ms->mmap = char_to_mem_map(UC(*input_cursor), 0, ms->mspace);
                if (ms->mmap == MS_BAD) {
                    lnk_error1("Illegal memory counter specified");
                    return -1;
                }
                input_cursor++;
                if (*input_cursor != ':') {
                    if (ms->mspace == MS_L) {
                        ms->mmap = char_to_mem_map(c1, UC(*input_cursor), ms->mspace);
                        if (ms->mmap != MS_BAD) {
                            input_cursor++;
                            goto colon;
                        }
                    }
                    lnk_error1("Illegal memory map character");
                    return -1;
                }
            }
colon:
            if (*input_cursor != ':') {
                lnk_error1("Syntax error - expected ':'");
                return -1;
            }
            input_cursor++;
            return 1;
        }
    }
    ms->mcntr = 0;
    if (*input_cursor == '(') {
        input_cursor++;
        if (get_counter(ms) != 0)
            return -1;
        default_map(ms);
        if (input_cursor[0] == ')' && input_cursor[1] == ':') {
            input_cursor += 2;
            return 1;
        }
        lnk_error1("Syntax error - expected '):'");
        return -1;
    }
    if (ms->mspace == MS_E && isdigit(UC(*input_cursor))) {
        ms->mmap = emi_map(strtol(input_cursor, NULL, 10), &ms->mclass);
        if (ms->mmap == MS_BAD)
            return 0;
        while (isdigit(UC(*input_cursor)))
            input_cursor++;
        p = input_cursor;
        goto tail;
    }
    p = input_cursor;
    if (ms->mspace != MS_U && ms->mmap != MM_P8) {
        c1 = UC(*input_cursor);
        if (ms->mmap != 4) {
            lnk_error1("Illegal memory map character");
            return -1;
        }
        ms->mmap = char_to_mem_map(UC(*input_cursor), 0, ms->mspace);
        if (ms->mmap == MS_BAD) {
            lnk_error1("Illegal memory counter specified");
            return -1;
        }
        p = input_cursor + 1;
        if (*p != ':' && *p != '(') {
            if (ms->mspace == MS_L) {
                input_cursor += 2;
                ms->mmap = char_to_mem_map(c1, UC(*p), ms->mspace);
                p = input_cursor;
                if (ms->mmap != MS_BAD)
                    goto tail;
            }
            input_cursor = p;
            lnk_error1("Illegal memory map character");
            return -1;
        }
    }
tail:
    input_cursor = p;
    if (*input_cursor == '(') {
        input_cursor++;
        if (get_counter(ms) != 0)
            return -1;
        if (input_cursor[0] == ')' && input_cursor[1] == ':') {
            input_cursor += 2;
            return 1;
        }
        lnk_error1("Syntax error - expected '):'");
        return -1;
    }
    if (*input_cursor == ':') {
        input_cursor++;
        return 1;
    }
    lnk_error1("Syntax error - expected ':'");
    return -1;
}

/* (no callers in the original) */
int mem_space_char(long space)
{
    switch (space) {
    case 0x1c:  return 'E';
    case 0:     return 'P';
    case 1:     return 'X';
    case 2:     return 'Y';
    case 3:     return 'L';
    case 0x11d: return 'D';
    case 0x11f: return 'U';
    }
    return 'N';
}

/* old object format memory bits (w & 0xf) -> space */
long mem_bits_space(long bits)
{
    switch (bits) {
    case 1: return 1;
    case 2: return 2;
    case 4: return 3;
    case 8: return 0;
    }
    return 4;
}

int mem_space_index(long space)
{
    switch (space) {
    case 0x1c:  return MI_E;
    case 0:     return MI_P;
    case 1:     return MI_X;
    case 2:     return MI_Y;
    case 3:     return MI_L;
    case 0x11d: return MI_D;
    case 0x11f: return MI_U;
    }
    return MI_NONE;
}

long index_mem_space(int idx)
{
    switch (idx) {
    case 1: return 1;
    case 2: return 2;
    case 3: return 3;
    case 4: return 0;
    case 5: return 0x1c;
    case 6: return 0x11d;
    case 7: return 0x11f;
    }
    return 4;
}

int mem_bits_counter(long bits)
{
    if (bits == 0)
        return 0;
    if (bits == 0x10)
        return 1;
    if (bits == 0x20)
        return 2;
    return -1;
}

static int lower(int c)
{
    return (c >= 0 && c <= UCHAR_MAX && isupper(c)) ? tolower(c) : c;
}

long char_to_mem_space(int c)
{
    c = lower(c);
    switch (c) {
    case 'd': return 0x11d;
    case 'e': return 0x1c;
    case 'l': return 3;
    case 'n': return 4;
    case 'p': return 0;
    case 'u': return 0x11f;
    case 'x': return 1;
    case 'y': return 2;
    }
    return MS_BAD;
}

int char_to_counter(int c)
{
    c = lower(c);
    switch (c) {
    case 'd':
    case 'n': return 0;
    case 'h': return 2;
    case 'l': return 1;
    }
    return -1;
}

long char_to_mem_map(int c1, int c2, long space)
{
    long base;

    if (space == 0x11d)
        return lower(c1) == ':' ? 0x11d : MS_BAD;
    switch (space) {
    case 0: base = 0xb; break;
    case 1: base = 0x10; break;
    case 2: base = 0x15; break;
    case 3:
        switch (lower(c1)) {
        case ':': return 3;
        case 'a':
            c2 = lower(c2);
            return c2 == 'a' ? 5 : c2 == 'b' ? 6 : MS_BAD;
        case 'b':
            c2 = lower(c2);
            return c2 == 'a' ? 7 : c2 == 'b' ? 8 : MS_BAD;
        case 'e': return 9;
        case 'i': return 10;
        }
        return MS_BAD;
    default:
        return MS_BAD;
    }
    switch (lower(c1)) {
    case ':': return space;
    case 'a': return base;
    case 'b': return base + 1;
    case 'e': return base + 2;
    case 'i': return base + 3;
    case 'r': return base + 4;
    }
    return MS_BAD;
}

/* EMI number -> map code n+0x1d, attribute bits into *attr */
static long emi_map(long n, long *attr)
{
    long m, k;

    m = n + 0x1d;
    k = n & 7;
    if ((n >= 0x40 && n <= 0x5f) || (n >= 0xc0 && n <= 0xdf) ||
        (n >= 0x80 && (k == 0 || k == 1 || k == 6 || k == 7))) {
        lnk_error1("Invalid EMI memory designation");
        return MS_BAD;
    }
    switch (k) {
    case 0:
    case 1: *attr = 0x20; break;
    case 2:
    case 3: *attr = n > 0x7f ? 0x30 : 0x40; break;
    case 4:
    case 5: *attr = n > 0x7f ? 0x50 : 0x60; break;
    default: *attr = 0x40; break;
    }
    if (m < 0x25 || (m > 0x5c && m < 0xa5) || (m > 0xdc && m < 0x11d))
        *attr |= (n & 1) + 1;
    return m;
}

static long width_map(long space, int width)
{
    if (width == 8 || width == 16) {
        if (space == 0)
            return MM_P8;
        if (space == MS_U)
            return width != 8 ? MM_U16 : MM_U8;
    }
    return MS_BAD;
}

long map_to_space(long map)
{
    if (map == 0 || (map >= 0xb && map <= 0xf) || map == 0x1a || map == 0x1b ||
        map == 0x11e)
        return 0;
    if (map == 1 || (map >= 0x10 && map <= 0x14))
        return 1;
    if (map == 2 || (map >= 0x15 && map <= 0x19))
        return 2;
    if (map == 3 || (map >= 5 && map <= 10))
        return 3;
    if (map == 4)
        return 4;
    if (map >= 0x1c && map <= 0x11c)
        return 0x1c;
    if (map == 0x11d)
        return 0x11d;
    if (map == 0x120 || map == 0x121)
        return 0x11f;
    return MS_BAD;
}

/* old object format map bits (w & 0xf700) -> map code */
long mem_bits_map(long space, long bits)
{
    long base;

    switch (space) {
    case 0: base = 0xb; break;
    case 1: base = 0x10; break;
    case 2: base = 0x15; break;
    case 3:
        switch (bits) {
        case 0x200:  return 9;
        case 0x100:  return 10;
        case 0x2000:
        case 0xa000: return 8;
        case 0x1000:
        case 0x5000: return 5;
        case 0x9000: return 6;
        case 0x6000: return 7;
        }
        return space;
    default:
        return MS_BAD;
    }
    switch (bits) {
    case 0x1000: return base;
    case 0x2000: return base + 1;
    case 0x200:  return base + 2;
    case 0x100:  return base + 3;
    case 0x400:  return base + 4;
    }
    return space;
}

/* (no callers in the original) */
char *str_upper(char *s)
{
    char *p;

    for (p = s; *p != '\0'; p++)
        if (islower(UC(*p)))
            *p = (char)toupper(UC(*p));
    return s;
}

char *str_lower(char *s)
{
    char *p;

    for (p = s; *p != '\0'; p++)
        if (isupper(UC(*p)))
            *p = (char)tolower(UC(*p));
    return s;
}

void set_file_buffer(FILE *fp, int which)
{
    setvbuf(fp, which ? iobuf1 : iobuf0, _IOFBF, IOBUFSIZE);
}

/* 1 iff the memctl token consists of decimal digits only */
int tok_is_digits(void)
{
    char *p;

    for (p = ctl_token; *p != '\0'; p++)
        if (!isdigit(UC(*p)))
            break;
    return *p == '\0';
}

long merge_mem_space(long space, long space2)
{
    switch (space) {
    case 0x1c:
        return (space2 == 0x1c || space2 == 4) ? 0x1c : MS_BAD;
    case 0:
        return (space2 == 0 || space2 == 4) ? 0 : MS_BAD;
    case 1:
        return (space2 == 2 || space2 == 0) ? MS_BAD : 1;
    case 2:
        return (space2 == 1 || space2 == 0) ? MS_BAD : 2;
    case 3:
        if (space2 == 0)
            return MS_BAD;
        if (space2 == 1 || space2 == 2)
            return space2;
        return 3;
    case 0x11d:
        return (space2 == 0x11d || space2 == 4) ? 0x11d : MS_BAD;
    case 0x11f:
        return (space2 == 0x11f || space2 == 1 || space2 == 2 || space2 == 3) ?
               0x11f : MS_BAD;
    }
    return space2;
}

/* printf a double with Inf/NaN text and MSVC style 3-digit exponents */
char *fmt_double(char *buf, char *fmt, double val)
{
    unsigned long hi, lo;
    int neg;
    char fcopy[512];
    char *last, *p;
    char save;

    double_to_words(val, &hi, &lo);
    neg = (hi & 0x80000000UL) != 0;
    if ((hi & 0x7ff00000UL) == 0x7ff00000UL) {
        if (lo == 0 && (hi & 0xfffffUL) == 0)
            strcpy(buf, neg ? "-Inf" : "Inf");
        else
            strcpy(buf, neg ? "-NaN" : "NaN");
        return buf;
    }
    strcpy(fcopy, fmt);
    last = fcopy + strlen(fcopy) - 1;
    if (lo == 0 && (hi & 0x7fffffffUL) == 0) {
        save = *last;
        *last = 'f';
        sprintf(neg ? buf + 1 : buf, fcopy, 0.0);
        *last = save;
        if (neg)
            buf[0] = '-';
        strcat(buf, "E+000");
    } else {
        sprintf(buf, fcopy, val);
    }
    p = strchr(buf, 'E');
    if (p == NULL)
        p = strchr(buf, 'e');
    if (p != NULL && p[1] != '\0' && p[2] != '\0' && p[3] != '\0') {
        if (p[4] == '\0' || isspace(UC(p[4]))) {
            p[5] = '\0';
            p[4] = p[3];
            p[3] = p[2];
            p[2] = '0';
        }
    }
    return buf;
}

void clear_coff_sym(void)
{
    memset(&obj_symbuf, 0, sizeof obj_symbuf);
    memset(&obj_auxbuf, 0, sizeof obj_auxbuf);
}

/* mktime-like conversion (the only caller discards the result) */
long tm_to_secs(struct tm *tm)
{
    long sec, min, hour, mday, mon, year, yday, days, y;

    if (tm == NULL)
        return -1;
    sec = tm->tm_sec;
    min = tm->tm_min;
    hour = tm->tm_hour;
    mday = tm->tm_mday;
    mon = tm->tm_mon;
    year = tm->tm_year;
    yday = tm->tm_yday;
    for (; sec > 59; sec -= 60) min++;
    for (; sec < 0; sec += 60) min--;
    for (; min > 59; min -= 60) hour++;
    for (; min < 0; min += 60) hour--;
    for (; hour > 23; hour -= 24) mday++;
    for (; hour < 0; hour += 24) mday--;
    for (; mday > 31; mday -= 31) mon++;
    for (; mday < 1; mday += 31) mon--;
    for (; mon > 11; mon -= 12) year++;
    for (; mon < 0; mon += 12) year--;
    if (year < 0 || mon < 0 || mon > 11 || mday < 0 || hour < 0 || hour > 23 ||
        min < 0 || min > 59 || sec < 0 || sec > 59)
        return -1;
    if (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) &&
        mon == 1 && mday > 29)
        return -1;
    if (mon_days_leap[mon] < mday)
        return -1;
    days = (year - 70) * 365;
    for (y = 1970; y < year + 1900; y++)
        if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
            days++;
    return (long)M32((unsigned long)(days + yday) * 86400UL +
                     (unsigned long)(hour * 3600L + min * 60L + sec));
}

/* align a modulo buffer base up to the next power of two boundary */
unsigned long buf_align(unsigned long addr, unsigned long bufsize, unsigned long mask)
{
    unsigned long p, r;

    r = 0;
    if (addr != 0) {
        p = round_up_pow2(bufsize);
        r = M32((addr - 1 + p) & ~(p - 1));
    }
    if (target_index == TGT_56600) {
        r &= mask;
        if (r < addr)
            lnk_error1("Buffer block too large");
    } else {
        r &= addr_mask;
        if (r < addr)
            lnk_error1("Buffer block too large");
    }
    return r;
}

unsigned long round_up_pow2(unsigned long n)
{
    unsigned long m;

    n = M32(n);
    if (n < 2)
        return n != 0 ? 2 : 0;
    m = n - 1;
    do {
        n = m;
        m = n & (n - 1);
    } while (m != 0);
    return M32(n << 1);
}

/* ---------------------------------------------------------------------- *
 * Portable file I/O and big-endian COFF codecs
 * ---------------------------------------------------------------------- */

unsigned long obj_fread(void *buf, unsigned long size, unsigned long n, FILE *fp)
{
    return (unsigned long)fread(buf, (size_t)size, (size_t)n, fp);
}

unsigned long obj_fwrite(void *buf, unsigned long size, unsigned long n, FILE *fp)
{
    return (unsigned long)fwrite(buf, (size_t)size, (size_t)n, fp);
}

unsigned long get_be32(unsigned char *p)
{
    return ((unsigned long)p[0] << 24) | ((unsigned long)p[1] << 16) |
           ((unsigned long)p[2] << 8) | (unsigned long)p[3];
}

void put_be32(unsigned char *p, unsigned long v)
{
    p[0] = (unsigned char)((v >> 24) & 0xff);
    p[1] = (unsigned char)((v >> 16) & 0xff);
    p[2] = (unsigned char)((v >> 8) & 0xff);
    p[3] = (unsigned char)(v & 0xff);
}

/* signed 32-bit big-endian value */
static long get_sbe32(unsigned char *p)
{
    unsigned long v;

    v = get_be32(p);
    if (v & 0x80000000UL)
        return -(long)((~v) & 0x7fffffffUL) - 1;
    return (long)v;
}

static void put_sbe32(unsigned char *p, long v)
{
    put_be32(p, M32(v));
}

/* reverse the bytes of each 4-byte group of an 8-byte name (swap_words(n,4,2)) */
void name_swap(char *n)
{
    char t;

    t = n[0]; n[0] = n[3]; n[3] = t;
    t = n[1]; n[1] = n[2]; n[2] = t;
    t = n[4]; n[4] = n[7]; n[7] = t;
    t = n[5]; n[5] = n[6]; n[6] = t;
}

unsigned long name_off(char *n)
{
    unsigned char *u = (unsigned char *)n;

    return (unsigned long)u[4] | ((unsigned long)u[5] << 8) |
           ((unsigned long)u[6] << 16) | ((unsigned long)u[7] << 24);
}

void set_name_off(char *n, unsigned long v)
{
    n[4] = (char)(v & 0xff);
    n[5] = (char)((v >> 8) & 0xff);
    n[6] = (char)((v >> 16) & 0xff);
    n[7] = (char)((v >> 24) & 0xff);
}

/* file bytes -> in-memory name (x86 after word swap) and back */
static void name_get(char *n, unsigned char *f)
{
    n[0] = (char)f[3]; n[1] = (char)f[2]; n[2] = (char)f[1]; n[3] = (char)f[0];
    n[4] = (char)f[7]; n[5] = (char)f[6]; n[6] = (char)f[5]; n[7] = (char)f[4];
}

static void name_put(unsigned char *f, char *n)
{
    f[0] = (unsigned char)n[3]; f[1] = (unsigned char)n[2];
    f[2] = (unsigned char)n[1]; f[3] = (unsigned char)n[0];
    f[4] = (unsigned char)n[7]; f[5] = (unsigned char)n[6];
    f[6] = (unsigned char)n[5]; f[7] = (unsigned char)n[4];
}

unsigned long read_filhdr(FILHDR *h, FILE *fp)
{
    unsigned char b[OBJ_FHDRSZ];

    if (fread(b, OBJ_FHDRSZ, 1, fp) != 1)
        return 0;
    h->f_magic = get_be32(b);
    h->f_nscns = get_sbe32(b + 4);
    h->f_timdat = get_sbe32(b + 8);
    h->f_symptr = get_sbe32(b + 12);
    h->f_nsyms = get_sbe32(b + 16);
    h->f_opthdr = get_sbe32(b + 20);
    h->f_flags = get_be32(b + 24);
    return 1;
}

unsigned long write_filhdr(FILHDR *h, FILE *fp)
{
    unsigned char b[OBJ_FHDRSZ];

    put_be32(b, M32(h->f_magic));
    put_sbe32(b + 4, h->f_nscns);
    put_sbe32(b + 8, h->f_timdat);
    put_sbe32(b + 12, h->f_symptr);
    put_sbe32(b + 16, h->f_nsyms);
    put_sbe32(b + 20, h->f_opthdr);
    put_be32(b + 24, M32(h->f_flags));
    return (unsigned long)fwrite(b, OBJ_FHDRSZ, 1, fp);
}

static long *lnkhdr_field(LNKHDR *h, int i)
{
    switch (i) {
    case 0:  return &h->modsize;
    case 1:  return &h->datasize;
    case 2:  return &h->endstr;
    case 3:  return &h->secnt;
    case 4:  return &h->ctrcnt;
    case 5:  return &h->relocnt;
    case 6:  return &h->lnocnt;
    case 7:  return &h->bufcnt;
    case 8:  return &h->ovlcnt;
    case 9:  return &h->majver;
    case 10: return &h->minver;
    case 11: return &h->revno;
    case 12: return &h->unused;
    }
    return &h->sditot;
}

/* reads nbytes (the optional header size); fills the first min(nbytes/4,14)
   fields, leaves the others unchanged; 1 ok, 0 short read */
unsigned long read_lnkhdr(LNKHDR *h, long nbytes, FILE *fp)
{
    unsigned char b[4];
    long i, n;

    n = nbytes / 4;
    for (i = 0; i < n; i++) {
        if (fread(b, 4, 1, fp) != 1)
            return 0;
        if (i < 14)
            *lnkhdr_field(h, (int)i) = get_sbe32(b);
    }
    for (i = n * 4; i < nbytes; i++)
        if (getc(fp) == EOF)
            return 0;
    return 1;
}

unsigned long write_lnkhdr(LNKHDR *h, FILE *fp)
{
    unsigned char b[OBJ_LNKSZ];
    int i;

    for (i = 0; i < 14; i++)
        put_sbe32(b + 4 * i, *lnkhdr_field(h, i));
    return (unsigned long)fwrite(b, OBJ_LNKSZ, 1, fp);
}

unsigned long write_aouthdr(AOUTHDR *h, FILE *fp)
{
    unsigned char b[OBJ_AOUTSZ];

    put_sbe32(b, h->magic);
    put_sbe32(b + 4, h->vstamp);
    put_sbe32(b + 8, h->tsize);
    put_sbe32(b + 12, h->dsize);
    put_sbe32(b + 16, h->bsize);
    put_sbe32(b + 20, h->entry);
    put_sbe32(b + 24, h->entry_mem);
    put_sbe32(b + 28, h->text_start);
    put_sbe32(b + 32, h->text_start_mem);
    put_sbe32(b + 36, h->data_start);
    put_sbe32(b + 40, h->data_start_mem);
    put_sbe32(b + 44, h->text_end);
    put_sbe32(b + 48, h->text_end_mem);
    put_sbe32(b + 52, h->data_end);
    put_sbe32(b + 56, h->data_end_mem);
    return (unsigned long)fwrite(b, OBJ_AOUTSZ, 1, fp);
}

unsigned long read_scnhdrs(SCNHDR *s, unsigned long n, FILE *fp)
{
    unsigned char b[OBJ_SCNSZ];
    unsigned long i;

    for (i = 0; i < n; i++, s++) {
        if (fread(b, OBJ_SCNSZ, 1, fp) != 1)
            break;
        name_get(s->s_name, b);
        s->s_paddr = get_sbe32(b + 8);
        s->s_pmem = get_sbe32(b + 12);
        s->s_vaddr = get_sbe32(b + 16);
        s->s_vmem = get_sbe32(b + 20);
        s->s_size = get_sbe32(b + 24);
        s->s_scnptr = get_sbe32(b + 28);
        s->s_relptr = get_sbe32(b + 32);
        s->s_lnnoptr = get_sbe32(b + 36);
        s->s_nreloc = get_sbe32(b + 40);
        s->s_nlnno = get_sbe32(b + 44);
        s->s_flags = get_be32(b + 48);
    }
    return i;
}

unsigned long write_scnhdrs(SCNHDR *s, unsigned long n, FILE *fp)
{
    unsigned char b[OBJ_SCNSZ];
    unsigned long i;

    for (i = 0; i < n; i++, s++) {
        name_put(b, s->s_name);
        put_sbe32(b + 8, s->s_paddr);
        put_sbe32(b + 12, s->s_pmem);
        put_sbe32(b + 16, s->s_vaddr);
        put_sbe32(b + 20, s->s_vmem);
        put_sbe32(b + 24, s->s_size);
        put_sbe32(b + 28, s->s_scnptr);
        put_sbe32(b + 32, s->s_relptr);
        put_sbe32(b + 36, s->s_lnnoptr);
        put_sbe32(b + 40, s->s_nreloc);
        put_sbe32(b + 44, s->s_nlnno);
        put_be32(b + 48, M32(s->s_flags));
        if (fwrite(b, OBJ_SCNSZ, 1, fp) != 1)
            break;
    }
    return i;
}

/* symbol slots: a main entry is followed by n_numaux aux entries */
unsigned long read_symslots(SYMSLOT *s, unsigned long n, FILE *fp)
{
    unsigned char b[OBJ_SYMSZ];
    unsigned long i;
    long aux;
    int k;

    aux = 0;
    for (i = 0; i < n; i++, s++) {
        if (fread(b, OBJ_SYMSZ, 1, fp) != 1)
            break;
        if (aux > 0) {
            for (k = 0; k < 8; k++)
                s->a.x[k] = get_sbe32(b + 4 * k);
            aux--;
        } else {
            name_get(s->s.n_name, b);
            s->s.n_value = get_sbe32(b + 8);
            s->s.n_mem = get_sbe32(b + 12);
            s->s.n_scnum = get_sbe32(b + 16);
            s->s.n_type = get_sbe32(b + 20);
            s->s.n_sclass = get_sbe32(b + 24);
            s->s.n_numaux = get_sbe32(b + 28);
            aux = s->s.n_numaux;
        }
    }
    return i;
}

unsigned long write_symslots(SYMSLOT *s, unsigned long n, FILE *fp)
{
    unsigned char b[OBJ_SYMSZ];
    unsigned long i;
    long aux;
    int k;

    aux = 0;
    for (i = 0; i < n; i++, s++) {
        if (aux > 0) {
            for (k = 0; k < 8; k++)
                put_sbe32(b + 4 * k, s->a.x[k]);
            aux--;
        } else {
            name_put(b, s->s.n_name);
            put_sbe32(b + 8, s->s.n_value);
            put_sbe32(b + 12, s->s.n_mem);
            put_sbe32(b + 16, s->s.n_scnum);
            put_sbe32(b + 20, s->s.n_type);
            put_sbe32(b + 24, s->s.n_sclass);
            put_sbe32(b + 28, s->s.n_numaux);
            aux = s->s.n_numaux;
        }
        if (fwrite(b, OBJ_SYMSZ, 1, fp) != 1)
            break;
    }
    return i;
}

unsigned long read_relents(RELENT *r, unsigned long n, FILE *fp)
{
    unsigned char b[OBJ_RELSZ];
    unsigned long i;

    for (i = 0; i < n; i++, r++) {
        if (fread(b, OBJ_RELSZ, 1, fp) != 1)
            break;
        r->r_vaddr = get_sbe32(b);
        r->r_symndx = get_sbe32(b + 4);
        r->r_unused = get_sbe32(b + 8);
    }
    return i;
}

unsigned long write_relents(RELENT *r, unsigned long n, FILE *fp)
{
    unsigned char b[OBJ_RELSZ];
    unsigned long i;

    for (i = 0; i < n; i++, r++) {
        put_sbe32(b, r->r_vaddr);
        put_sbe32(b + 4, r->r_symndx);
        put_sbe32(b + 8, r->r_unused);
        if (fwrite(b, OBJ_RELSZ, 1, fp) != 1)
            break;
    }
    return i;
}

unsigned long read_linenos(LINENO *l, unsigned long n, FILE *fp)
{
    unsigned char b[OBJ_LNNOSZ];
    unsigned long i;

    for (i = 0; i < n; i++, l++) {
        if (fread(b, OBJ_LNNOSZ, 1, fp) != 1)
            break;
        l->l_addr = get_sbe32(b);
        l->l_mem = get_sbe32(b + 4);
        l->l_lnno = get_sbe32(b + 8);
    }
    return i;
}

unsigned long write_linenos(LINENO *l, unsigned long n, FILE *fp)
{
    unsigned char b[OBJ_LNNOSZ];
    unsigned long i;

    for (i = 0; i < n; i++, l++) {
        put_sbe32(b, l->l_addr);
        put_sbe32(b + 4, l->l_mem);
        put_sbe32(b + 8, l->l_lnno);
        if (fwrite(b, OBJ_LNNOSZ, 1, fp) != 1)
            break;
    }
    return i;
}

unsigned long read_words(unsigned long *w, unsigned long n, FILE *fp)
{
    unsigned char b[4];
    unsigned long i;

    for (i = 0; i < n; i++) {
        if (fread(b, 4, 1, fp) != 1)
            break;
        w[i] = get_be32(b);
    }
    return i;
}

unsigned long write_words(unsigned long *w, unsigned long n, FILE *fp)
{
    unsigned char b[4];
    unsigned long i;

    for (i = 0; i < n; i++) {
        put_be32(b, M32(w[i]));
        if (fwrite(b, 4, 1, fp) != 1)
            break;
    }
    return i;
}
