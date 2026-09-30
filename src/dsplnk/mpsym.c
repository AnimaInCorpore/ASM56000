/*
 * mpsym.c - DSPLNK.EXE (CLAS56 v6.3, DSP Linker 6.3.7), ABI expression
 * subsystem: per-module symbol name tables (0x434c30-0x434e02, 0x435e58,
 * 0x438203-0x43834c).
 *
 * abi_modules (ABI_mp_symtblInfArray) holds one ABIMPENT per object module
 * that has symbols: the key is the text "%#0lx" of the MODULE address and the
 * value a LONGInfArray with word 1 of every symbol table slot (the string
 * table offset of a long name), indexed by the slot number.
 *
 * The original reads the symbol slots as raw 32-byte memory images.  The port
 * keeps decoded fields (SYMENT/AUXENT), so slot_image() rebuilds the image the
 * x86 program sees: the eight name bytes followed by the little-endian
 * long fields, or eight little-endian longs for an auxiliary entry.
 */
#include "abi.h"

/* little-endian store of a 32-bit value */
static void put4(unsigned char *p, long v)
{
    unsigned long u = (unsigned long)v & 0xffffffffUL;

    p[0] = (unsigned char)(u & 0xff);
    p[1] = (unsigned char)((u >> 8) & 0xff);
    p[2] = (unsigned char)((u >> 16) & 0xff);
    p[3] = (unsigned char)((u >> 24) & 0xff);
}

/* image of a main symbol entry / of an auxiliary entry */
static void image_main(SYMSLOT *s, unsigned char *img)
{
    int i;

    for (i = 0; i < 8; i++)
        img[i] = (unsigned char)s->s.n_name[i];
    put4(img + 8, s->s.n_value);
    put4(img + 12, s->s.n_mem);
    put4(img + 16, s->s.n_scnum);
    put4(img + 20, s->s.n_type);
    put4(img + 24, s->s.n_sclass);
    put4(img + 28, s->s.n_numaux);
}

static void image_aux(SYMSLOT *s, unsigned char *img)
{
    int i;

    for (i = 0; i < 8; i++)
        put4(img + 4 * i, s->a.x[i]);
}

/* 32-byte image of slot idx (0 <= idx < f_nsyms) */
static void slot_image(MODULE *mod, long idx, unsigned char *img)
{
    long i, n;

    i = 0;
    while (i < idx) {
        n = mod->syms[i].s.n_numaux;
        if (n < 0)
            n = 0;
        if (i + 1 + n > idx) {
            image_aux(&mod->syms[idx], img);    /* idx is inside the aux run */
            return;
        }
        i += 1 + n;
    }
    image_main(&mod->syms[idx], img);
}

static unsigned long word_at(unsigned char *img, int w)
{
    return (unsigned long)img[4 * w] | ((unsigned long)img[4 * w + 1] << 8) |
           ((unsigned long)img[4 * w + 2] << 16) | ((unsigned long)img[4 * w + 3] << 24);
}

/* 434c30: freefn of abi_modules */
void abi_mp_sym_free_with_arr(void *elem)
{
    ABIMPENT *e = (ABIMPENT *)elem;

    if (e != NULL) {
        if (e->name != NULL) {
            free(e->name);
            e->name = NULL;
        }
        if (e->offs != NULL) {
            longarr_destroy(e->offs);
            e->offs = NULL;
        }
        free(e);
    }
}

/* 434c8f */
ABIMPENT *abi_mp_sym_build(MODULE *mod)
{
    ABIMPENT *e;
    char buf[100];
    long i, aux;
    unsigned char img[32];
    LONGArr *offs;

    e = (ABIMPENT *)malloc(sizeof(ABIMPENT));
    sprintf(buf, "%#0lx", (unsigned long)(size_t)mod);
    e->name = abi_strdup(buf);
    offs = longarr_create(10L, 10L, NULL);
    e->offs = offs;
    aux = 0;
    for (i = 0; i < mod->fh.f_nsyms; i++) {
        if (aux > 0) {
            image_aux(&mod->syms[i], img);
            aux--;
        } else {
            image_main(&mod->syms[i], img);
            aux = mod->syms[i].s.n_numaux;
        }
        (*offs->add_plain)(offs, (long)word_at(img, 1));
    }
    return e;
}

/* 434d4d: the entry of module `key' (matched through its "%#0lx" text) */
ABIMPENT *abi_mp_sym_find(MpArr *arr, MODULE *key)
{
    char buf[100];
    long i;

    sprintf(buf, "%#0lx", (unsigned long)(size_t)key);
    if (arr == NULL) {
        fprintf(stderr, "ABI_mp_symtblInfArray Search Table is NULL");
        return NULL;
    }
    if (key == NULL) {
        fprintf(stderr, "ABI_mp_symtblInfArray Search key 'mp' is NULL");
        return NULL;
    }
    for (i = 0; i <= arr->max_index; i++) {
        if (strcmp(((ABIMPENT *)(*arr->get)(arr, i))->name, buf) == 0)
            return (ABIMPENT *)(*arr->get)(arr, i);
    }
    return NULL;
}

/* 435e58: strdup'ed name of symbol slot idx, or NULL.  A long name (first
   word of the slot zero) is taken from the module string table at the offset
   saved by abi_mp_sym_build; a short name is the C string starting at the
   slot (running on into the following fields when all eight characters are
   used, as the original does). */
char *abi_mp_sym_name(MODULE *mod, MpArr *tab, long idx)
{
    ABIMPENT *e;
    unsigned char img[32];
    char buf[40];
    long off;
    int i;

    if (idx >= mod->fh.f_nsyms || idx < 0)
        return NULL;
    slot_image(mod, idx, img);
    if (word_at(img, 0) == 0) {
        e = abi_mp_sym_find(tab, mod);
        if (e == NULL)
            return NULL;
        off = (*e->offs->get)(e->offs, idx);
        if (mod->strtab == NULL)
            return NULL;
        return abi_strdup(mod->strtab + off);
    }
    for (i = 0; i < 32; i++)
        buf[i] = (char)img[i];
    buf[32] = '\0';
    return abi_strdup(buf);
}

/* 438203: low byte of m (word size 2 or otherwise: identical mask 0..7) */
unsigned long abi_mp_sym_get_mask(ABICTX *ctx, unsigned long m)
{
    (void)ctx;
    return abi_bit_range_mask(0, 7) & m;
}

/* 43825a: both branches compute the same masked shift and return it */
unsigned long abi_mp_sym_shift_field(ABICTX *ctx, unsigned long v)
{
    (void)ctx;
    return abi_mask_then_shift(v, abi_bit_range_mask(8, 15), 8, '>');
}

/* 43834c */
long abi_mp_sym_set_type(ABICTX *ctx, int type)
{
    ctx->word_bytes = (short)type;
    return 0;
}
