/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), elfout.c
 * ELF writer used by the COFF to ELF debug file converter
 * (0x431630-0x4326d0 elf_*, 0x431ee8 strtab_append, 0x431ffd elf_init,
 * 0x432261 elf_build_header, 0x4326d0/0x43271d byte swapping).  The
 * original builds native x86 structures and swaps every field in place
 * while writing; the port keeps the ELF header as its big-endian bytes
 * and encodes every section header field byte by byte, so any host
 * writes the same big-endian ELF file.
 * Not ported: clear_elf_scratch (0x430534, never called), the program
 * header list and the SHT_REL section type (no code creates them).
 */
#include "elfout.h"

static long elf_pos;                    /* 46a938 file position (elf_tell) */
static long elf_shnum;                  /* 46a93c number of sections */
static long elf_strtab_idx;             /* 46a948 */
static unsigned char elf_hdr[0x34];     /* 46a950 ELF header, big-endian */
static ELFSEC *elf_tail;                /* 46a954 */
static ELFSEC *elf_head;                /* 46a958 */
static ELFBUF *elf_symtab;              /* 46a970 */
static ELFBUF *elf_strtab;              /* 46a974 */
static ELFBUF *elf_shstrtab;            /* 46a978 */

long elf_tell(void)
{
    return elf_pos;
}

void elf_seek(long pos, FILE *fp)
{
    if (fseek(fp, pos, 0) != 0)
        lnk_error1("Cannot seek to ELF object file position");
    elf_pos = pos;
}

/* raw write (0x431bbf) */
void elf_write_data(void *buf, unsigned long size, unsigned long n, FILE *fp)
{
    if (size != 0) {
        if (fwrite(buf, (size_t)size, (size_t)n, fp) != 1)
            lnk_error1("Cannot write data to ELF object file");
        elf_pos += (long)size;
    }
}

/* field write (0x431c05); buf already holds the big-endian bytes */
void elf_write_data2(void *buf, unsigned long size, unsigned long n, FILE *fp)
{
    if (size != 0) {
        if (elf_write_maybe_swapped(buf, size, n, fp) != 1)
            lnk_error1("Cannot write data to ELF object file");
        elf_pos += (long)size;
    }
}

/* 0x4326d0: the original swaps the fields to big-endian here, the port
   gets them big-endian already */
unsigned long elf_write_maybe_swapped(void *buf, unsigned long size,
                                      unsigned long n, FILE *fp)
{
    return (unsigned long)fwrite(buf, (size_t)size, (size_t)n, fp);
}

static void put_be16(unsigned char *p, unsigned long v)
{
    p[0] = (unsigned char)((v >> 8) & 0xff);
    p[1] = (unsigned char)(v & 0xff);
}

static void field32(unsigned long v, FILE *fp)
{
    unsigned char b[4];

    put_be32(b, v & 0xffffffffUL);
    elf_write_data2(b, 4, 1, fp);
}

static void field16(int off, FILE *fp)
{
    elf_write_data2(elf_hdr + off, 2, 1, fp);
}

static void field32h(int off, FILE *fp)
{
    elf_write_data2(elf_hdr + off, 4, 1, fp);
}

void elf_write_sections(FILE *fp)
{
    ELFSEC *s, *next;
    ELFBUF *b;

    for (s = elf_head; s != NULL; s = s->next) {
        switch (s->type) {
        case 2:                         /* SHT_SYMTAB */
            s->offset = (unsigned long)elf_pos;
            elf_seek(elf_pos, fp);
            s->link = (unsigned long)elf_strtab_idx;
            b = s->data;
            if (b != NULL) {
                s->size = ((unsigned long)b->len << 4) & 0xffffffffUL;
                s->entsize = 0x10;
                elf_write_data(b->data, s->size, 1, fp);
                xfree(b->data);
                xfree(b);
            }
            break;
        case 3:                         /* SHT_STRTAB */
            s->offset = (unsigned long)elf_pos;
            elf_seek(elf_pos, fp);
            b = s->data;
            if (b != NULL) {
                s->size = (unsigned long)b->len;
                s->entsize = 0;
                elf_write_data(b->data, s->size, 1, fp);
                xfree(b->data);
                xfree(b);
            }
            break;
        default:
            break;
        }
    }
    put_be32(elf_hdr + 0x20, (unsigned long)elf_pos & 0xffffffffUL);
    for (s = elf_head; s != NULL; s = next) {
        next = s->next;
        field32(s->name, fp);
        field32(s->type, fp);
        field32(s->flags, fp);
        field32(s->addr, fp);
        field32(s->offset, fp);
        field32(s->size, fp);
        field32(s->link, fp);
        field32(s->info, fp);
        field32(s->align, fp);
        field32(s->entsize, fp);
        xfree(s->sname);
        xfree(s);
    }
    /* no program headers: e_phoff = 0, e_phentsize = 0x20, e_phnum = 0 */
    put_be32(elf_hdr + 0x1c, 0);
    put_be16(elf_hdr + 0x2a, 0x20);
    put_be16(elf_hdr + 0x2c, 0);
    put_be16(elf_hdr + 0x30, (unsigned long)elf_shnum & 0xffffUL);
    elf_seek(0, fp);
    elf_write_data(elf_hdr, 0x10, 1, fp);
    field16(0x10, fp);
    field16(0x12, fp);
    field32h(0x14, fp);
    field32h(0x18, fp);
    field32h(0x1c, fp);
    field32h(0x20, fp);
    field32h(0x24, fp);
    field16(0x28, fp);
    field16(0x2a, fp);
    field16(0x2c, fp);
    field16(0x2e, fp);
    field16(0x30, fp);
    field16(0x32, fp);
}

long strtab_append(ELFBUF *tab, char *name)
{
    long len = (long)strlen(name);
    long ret = tab->len;
    long old;

    if (tab->data == NULL) {
        tab->cap += 0x400;
        tab->data = (char *)xmalloc((unsigned long)tab->cap);
        memset(tab->data, 0, (size_t)tab->cap);
    } else {
        while (tab->cap <= tab->len + len + 1) {
            old = tab->cap;
            if (tab->cap < 0x400)
                tab->cap <<= 1;
            else
                tab->cap += 0x400;
            tab->data = (char *)xrealloc(tab->data, (unsigned long)tab->cap);
            memset(tab->data + old, 0, (size_t)(tab->cap - old));
        }
    }
    strcpy(tab->data + tab->len, name);
    tab->len += len + 1;
    return ret;
}

ELFSEC *elf_new_section(char *name)
{
    ELFSEC *s = (ELFSEC *)xmalloc(sizeof(ELFSEC));

    s->sname = (char *)xmalloc(strlen(name) + 1);
    strcpy(s->sname, name);
    s->index = elf_shnum;
    elf_shnum++;
    s->name = (unsigned long)strtab_append(elf_shstrtab, name);
    s->type = 0;
    s->flags = 0;
    s->addr = 0;
    s->offset = 0;
    s->size = 0;
    s->link = 0;
    s->info = 0;
    s->align = 0;
    s->entsize = 0;
    s->data = NULL;
    s->unk_34 = 0;
    s->prev = elf_tail;
    s->next = NULL;
    if (elf_tail == NULL)
        elf_head = s;
    else
        elf_tail->next = s;
    elf_tail = s;
    return s;
}

static ELFBUF *new_elfbuf(void)
{
    ELFBUF *b = (ELFBUF *)xmalloc(sizeof(ELFBUF));

    b->data = NULL;
    b->len = 0;
    b->cap = 0;
    return b;
}

void elf_build_header(void)
{
    memset(elf_hdr, 0, sizeof elf_hdr);
    elf_hdr[0] = 0x7f;
    elf_hdr[1] = 'E';
    elf_hdr[2] = 'L';
    elf_hdr[3] = 'F';
    elf_hdr[4] = 1;                     /* ELFCLASS32 */
    elf_hdr[5] = 2;                     /* ELFDATA2MSB */
    elf_hdr[6] = 1;                     /* EV_CURRENT */
    put_be16(elf_hdr + 0x10, 2);        /* ET_EXEC */
    put_be16(elf_hdr + 0x12, 2);        /* e_machine */
    put_be32(elf_hdr + 0x14, 1);        /* e_version */
    put_be16(elf_hdr + 0x28, 0x34);     /* e_ehsize */
    put_be16(elf_hdr + 0x2e, 0x28);     /* e_shentsize */
}

void elf_init(void)
{
    ELFSEC *s;

    elf_build_header();
    elf_pos = 0;
    elf_shnum = 0;
    elf_strtab_idx = 0;
    elf_head = NULL;
    elf_tail = NULL;
    elf_symtab = new_elfbuf();
    elf_strtab = new_elfbuf();
    elf_shstrtab = new_elfbuf();
    s = elf_new_section("");            /* SHT_NULL */
    s = elf_new_section(".shstrtab");
    s->type = 3;
    s->data = elf_shstrtab;
    put_be16(elf_hdr + 0x32, (unsigned long)s->index & 0xffffUL);
    s = elf_new_section(".strtab");
    s->type = 3;
    s->flags |= 2;
    s->data = elf_strtab;
    elf_strtab_idx = s->index;
    s = elf_new_section(".note");
    s->type = 7;
    s = elf_new_section(".symtab");
    s->type = 2;
    s->flags |= 2;
    s->link = (unsigned long)elf_strtab_idx;
    s->data = elf_symtab;
}
