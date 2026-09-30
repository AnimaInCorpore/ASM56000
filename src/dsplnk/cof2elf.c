/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), cof2elf.c
 * COFF to ELF debug information file converter, run by main() for
 * target "100" with -c (0x432799-0x43329e).  It copies the debug
 * sections (STYP_DEBUG, s_flags & 0x100) of the linked .cld into a
 * big-endian ELF file, one SHT_PROGBITS section ".<name>" per distinct
 * section name.  Like the original it keeps only the low byte of every
 * 4-byte data word (fread_swapped reverses each word, the copy loop
 * then takes byte 0).  Sections of the same name are concatenated.
 *
 * The original reads section headers with fread_swapped (every 4-byte
 * group reversed on the little-endian host, the name reversed back when
 * it is a short name); a name of 8 characters without terminator thus
 * continues into the following header bytes as they stand in x86
 * memory.  The port rebuilds that memory image (name8_image) so such
 * names come out identical.
 */
#include "elfout.h"

typedef struct crec {                   /* section record, xmalloc(0x20) */
    struct crec *tail;                  /* +0x00 cursor / tail of sub list */
    struct crec *head;                  /* +0x04 head of sub list */
    char *name;                         /* +0x08 (NULL in sub records) */
    long scnptr;                        /* +0x0c */
    long paddr;                         /* +0x10 */
    long size;                          /* +0x14 words */
    long index;                         /* +0x18 section number */
    struct crec *next;                  /* +0x1c next section (main list) */
} CREC;

static long strtab_len;                 /* 46aba0 string table length - 4 */
static long strtab_pos;                 /* 46aba4 file offset of the table */
static char *strtab_buf;                /* 46aba8 */
static FILE *coff_fp;                   /* 46abac */
static long f_magic, f_nscns, f_symptr, f_nsyms, f_opthdr;
static unsigned long f_flags;           /* 46abb0.. file header */
static long sechdr_off;                 /* 46ac44 */
static FILE *elf_fp;                    /* 46ac5c */
static CREC *rec_tail;                  /* 46ac60 */
static CREC *rec_head;                  /* 46ac64 (original: 148 byte area) */

static long sbe32(unsigned char *p)
{
    unsigned long v = get_be32(p);

    if (v & 0x80000000UL)
        return -(long)((~v + 1) & 0xffffffffUL);
    return (long)v;
}

int test_bit1(unsigned long flags)
{
    return (flags & 2) != 0;
}

static void noop_433(void)
{
}

/* section header name as the x86 original sees it in memory, see above */
static char *name8_image(unsigned char *raw, unsigned char *img)
{
    int i;

    for (i = 0; i < 8; i++)
        img[i] = raw[i];
    for (i = 8; i < 0x34; i += 4) {
        img[i] = raw[i + 3];
        img[i + 1] = raw[i + 2];
        img[i + 2] = raw[i + 1];
        img[i + 3] = raw[i];
    }
    img[0x34] = 0;
    return (char *)img;
}

static char *coff_strtab_name(unsigned char *raw, char *shortname)
{
    long off;

    if (get_be32(raw) != 0)
        return shortname;
    off = sbe32(raw + 4);
    if (off < 4 || off > strtab_len) {
        lnk_error1("invalid COFF string table offset for section header name");
        return NULL;
    }
    return strtab_buf - 4 + off;
}

static CREC *record_node_alloc(void)
{
    CREC *r = (CREC *)xmalloc(sizeof(CREC));

    memset(r, 0, sizeof(CREC));
    return r;
}

static void sec_list_add(char *name, long a, long b, long c, long d)
{
    CREC *r;

    if (rec_tail == NULL) {
        rec_tail = record_node_alloc();
        r = rec_tail;
        rec_head = r;
    } else {
        r = record_node_alloc();
        rec_tail->next = r;
        rec_tail = r;
    }
    r->name = (char *)xmalloc(strlen(name) + 1);
    strcpy(r->name, name);
    r->paddr = a;
    r->size = b;
    r->index = c;
    r->scnptr = d;
}

static void sub_record_list_add(CREC *node, long a, long b, long c, long d)
{
    CREC *r = record_node_alloc();

    if (node->tail == NULL) {
        node->tail = r;
        node->head = r;
    } else {
        node->tail->tail = r;           /* +0 of a sub record is its link */
        node->tail = r;
    }
    r->name = NULL;
    r->paddr = a;
    r->size = b;
    r->index = c;
    r->scnptr = d;
}

static CREC *record_list_find(char *name)
{
    CREC *r;

    for (r = rec_head; r != NULL; r = r->next)
        if (strcmp(r->name, name) == 0)
            return r;
    return NULL;
}

int read_coff_headers(void)
{
    unsigned char b[0x1c];
    unsigned char *opt;
    unsigned long n;

    if (fread(b, 0x1c, 1, coff_fp) != 1) {
        lnk_error1("Cannot read COFF file header");
        return 1;
    }
    f_magic = (long)get_be32(b);
    if (f_magic < 0x2c5 || f_magic > 0x2cc) {
        lnk_error1("Invalid COFF object file format");
        return 1;
    }
    f_nscns = sbe32(b + 4);
    f_symptr = sbe32(b + 12);
    f_nsyms = sbe32(b + 16);
    f_opthdr = sbe32(b + 20);
    f_flags = get_be32(b + 24);
    if (!test_bit1(f_flags))
        return 1;
    if (f_opthdr != 0) {
        n = (unsigned long)f_opthdr;
        opt = NULL;
        if (n <= 0x10000UL) {
            opt = (unsigned char *)xmalloc(n);
            if (fread(opt, (size_t)n, 1, coff_fp) != 1) {
                xfree(opt);
                opt = NULL;
            }
        }
        if (opt == NULL) {
            if (f_flags & 1)
                lnk_error1("Cannot read COFF optional file header");
            else
                lnk_error1("Cannot read COFF linker file header");
            return 1;
        }
        xfree(opt);
    }
    sechdr_off = f_opthdr + 0x1c;
    if (read_coff_strtab(f_symptr, f_nsyms) != 0)
        return 1;
    if (read_coff_sections(sechdr_off, f_nscns) != 0)
        return 1;
    return 0;
}

int read_coff_strtab(long off, long count)
{
    unsigned char lb[4];
    long len;

    if (count == 0)
        return 1;
    strtab_pos = off + count * 0x20;
    if (fseek(coff_fp, strtab_pos, 0) != 0) {
        lnk_error1("cannot seek to string table");
        return 1;
    }
    if (fread(lb, 4, 1, coff_fp) != 1 && !feof(coff_fp)) {
        lnk_error1("Cannot read COFF string table length");
        return 1;
    }
    if (feof(coff_fp)) {
        strtab_len = 0;
        return 0;
    }
    len = sbe32(lb);
    strtab_len = len;
    if (len != 0) {
        strtab_len = len - 4;
        if (strtab_len < 0) {
            lnk_error1("invalid COFF string table length");
            return 1;
        }
        strtab_buf = (char *)xmalloc((unsigned long)strtab_len + 1);
        strtab_buf[strtab_len] = '\0';
        if (fseek(coff_fp, strtab_pos + 4, 0) != 0) {
            lnk_error1("cannot seek to COFF string table");
            return 1;
        }
        if (fread(strtab_buf, (size_t)strtab_len, 1, coff_fp) != 1) {
            lnk_error1("cannot read COFF string table");
            return 1;
        }
    }
    return 0;
}

int read_coff_sections(long off, long count)
{
    unsigned char raw[0x34];
    unsigned char img[0x35];
    long i;
    char *name;
    long paddr, size, scnptr;
    unsigned long flags;
    CREC *r;

    for (i = 0; i < count; i++) {
        if (fseek(coff_fp, off, 0) != 0) {
            lnk_error1("COFF section header seek failure");
            return 1;
        }
        if (fread(raw, 0x34, 1, coff_fp) != 1) {
            lnk_error1("Can't read COFF section header");
            return 1;
        }
        paddr = sbe32(raw + 8);
        size = sbe32(raw + 0x18);
        scnptr = sbe32(raw + 0x1c);
        flags = get_be32(raw + 0x30);
        if (size != 0 && (flags & 0x100) != 0) {
            name = coff_strtab_name(raw, name8_image(raw, img));
            if (name == NULL)
                return 1;
            r = record_list_find(name);
            if (r == NULL)
                sec_list_add(name, paddr, size, i, scnptr);
            else
                sub_record_list_add(r, paddr, size, i, scnptr);
        }
        off += 0x34;
    }
    return 0;
}

/* concatenated low bytes of all pieces of one section name (0x433153) */
static char *record_list_total_size(CREC *list)
{
    CREC *p;
    long total = 0;
    long c = 0;
    long k;
    unsigned char *tmp;
    unsigned long nbytes;
    char *out;

    for (p = list; p != NULL; p = p->tail)
        total += p->size;
    tmp = (unsigned char *)xmalloc((unsigned long)total * 4UL);
    memset(tmp, 0, (size_t)total * 4);
    out = (char *)xmalloc((unsigned long)total);
    for (p = list; p != NULL; p = p->tail) {
        if (fseek(coff_fp, p->scnptr, 0) != 0)
            lnk_error1("Cannot seek COFF input file");
        nbytes = (unsigned long)p->size * 4UL;
        if (fread(tmp + c * 4, (size_t)nbytes, 1, coff_fp) != 1 &&
            !feof(coff_fp)) {
            noop_433();
            lnk_error1("Read of COFF data failed");
            return NULL;
        }
        c += p->size;
    }
    list->size = c;
    for (k = 0; k < list->size; k++)
        out[k] = (char)tmp[k * 4 + 3];  /* low byte of the big-endian word */
    xfree(tmp);
    return out;
}

static void free_elf_section_list(void)
{
    CREC *r, *next;
    CREC *s, *sn;

    for (r = rec_head; r != NULL; r = next) {
        next = r->next;
        r->tail = r->head;
        for (s = r->tail; s != NULL; s = sn) {
            sn = s->tail;
            xfree(s);
        }
        xfree(r);
    }
}

int coff_to_elf(char *coff_path, char *elf_path)
{
    CREC *r;
    char *data;
    long pos;
    char *sname;
    ELFSEC *e;

    rec_tail = NULL;
    rec_head = NULL;
    strtab_len = 0;
    strtab_buf = NULL;
    coff_fp = fopen(coff_path, "rb");
    if (coff_fp == NULL) {
        fprintf(stderr, "Cannot open %s\n", coff_path);
        return 1;
    }
    if (read_coff_headers() != 0)
        return 1;
    elf_init();
    elf_fp = fopen(elf_path, "wb");
    if (elf_fp == NULL) {
        fprintf(stderr, "Cannot open %s\n", elf_path);
        return 1;
    }
    elf_seek(0x34, elf_fp);
    setbuf(elf_fp, NULL);
    for (r = rec_head; r != NULL; r = r->next) {
        r->tail = r->head;
        data = record_list_total_size(r);
        pos = elf_tell();
        if (data != NULL)
            elf_write_data(data, (unsigned long)r->size, 1, elf_fp);
        sname = (char *)xmalloc(strlen(r->name) + 2);
        strcpy(sname, ".");
        strcat(sname, r->name);
        e = elf_new_section(sname);
        e->type = 1;
        e->flags = 0;
        e->addr = (unsigned long)r->paddr & 0xffffffffUL;
        e->offset = (unsigned long)pos;
        e->size = (unsigned long)r->size;
        e->link = 0;
        e->info = 0;
        e->align = 0;
        e->entsize = 0;
        xfree(data);
    }
    elf_write_sections(elf_fp);
    free_elf_section_list();
    fclose(coff_fp);
    fclose(elf_fp);
    return 0;
}
