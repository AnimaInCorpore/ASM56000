/*
 * infarr.inc - body of one InfArray instantiation (DSPLNK.EXE, 0x433620..)
 * The original has four hand-duplicated copies (byte identical up to the
 * string literals); the port includes this file once per instantiation.
 * Before including define:
 *   IA_PFX     token prefix ending in '_' (longarr_, symtblarr_, ...)
 *   IA_NAME    struct typedef name, IA_ELEM element type
 *   IA_FILE    file name literal used by the assert messages
 *   IA_CREATE_RET   return type of <pfx>create (NAME * or void *)
 */
#define IA_CAT2(a, b) a ## b
#define IA_CAT(a, b) IA_CAT2(a, b)
#define IA(f) IA_CAT(IA_PFX, f)

/* forward: the slots are filled by create */

void IA(count)(IA_ELEM val)
{
    (void)val;
}

void IA(free_storage)(IA_NAME *arr)
{
    long i;

    if (arr->remove == 1) {
        for (i = 0; i <= arr->max_index; i++) {
            if (arr->flags[i] == 1)
                (*arr->freefn)(arr->data[i]);
        }
    }
    if (arr->data != NULL) {
        free(arr->data);
        arr->data = NULL;
    }
    if (arr->flags != NULL) {
        free(arr->flags);
        arr->flags = NULL;
    }
}

void IA(destroy)(IA_NAME *arr)
{
    if (arr != NULL) {
        IA(free_storage)(arr);
        free(arr);
    }
}

void IA(grow)(IA_NAME *arr, long need)
{
    unsigned long n;                /* new capacity in elements */
    unsigned long bytes;
    IA_ELEM *d;
    long *f;
    unsigned long old;

    if (need > 0 && arr->data == NULL) {
        n = (unsigned long)need & 0xffffffffUL;
    } else {
        n = ((((unsigned long)(need + 1) & 0xffffffffUL) /
              ((unsigned long)arr->blocksz & 0xffffffffUL)) + 1UL) *
            ((unsigned long)arr->blocksz & 0xffffffffUL);
        n &= 0xffffffffUL;
    }
    bytes = (n * (unsigned long)sizeof(IA_ELEM)) & 0xffffffffUL;
    d = NULL;
    f = NULL;
    if (bytes <= (unsigned long)((size_t)-1) &&
        n * (unsigned long)sizeof(long) <= (unsigned long)((size_t)-1)) {
        if (arr->data == NULL) {
            d = (IA_ELEM *)malloc((size_t)bytes);
            f = (long *)malloc((size_t)(n * (unsigned long)sizeof(long)));
        } else {
            d = (IA_ELEM *)realloc(arr->data, (size_t)bytes);
            f = (long *)realloc(arr->flags, (size_t)(n * (unsigned long)sizeof(long)));
        }
    }
    if (d != NULL && f != NULL) {
        arr->data = d;
        arr->flags = f;
        old = (unsigned long)arr->array_size;
        /* the original clears only (n - old) BYTES of the flag array
           (bug: malloc'ed rest is left as is); clear all new flags */
        memset(arr->data + old, 0, (size_t)(bytes - old * (unsigned long)sizeof(IA_ELEM)));
        memset(arr->flags + old, 0, (size_t)((n - old) * (unsigned long)sizeof(long)));
    } else {
        fprintf(stderr, "Cannot alloc array\n");
        abi_assert_fail("0", IA_FILE, 299);
        exit(1);
    }
    arr->array_size = (long)n;
}

void IA(compact)(IA_NAME *arr)
{
    IA(free_storage)(arr);
    arr->array_size = 0;
    arr->max_index = -1L;
    arr->last_index = -1L;
    arr->remove = 0;
    IA(grow)(arr, arr->init_sz);
}

void IA(append)(IA_NAME *arr, long idx, IA_ELEM val)
{
    if ((unsigned long)arr->array_size <= (unsigned long)idx)
        IA(grow)(arr, idx);
    arr->data[idx] = val;
    arr->last_index = idx;
    arr->flags[idx] = 1;
    arr->remove = 1;
    if (arr->max_index < idx)
        arr->max_index = idx;
}

void IA(insert)(IA_NAME *arr, long idx, IA_ELEM val)
{
    if ((unsigned long)arr->array_size <= (unsigned long)idx)
        IA(grow)(arr, idx);
    arr->data[idx] = val;
    arr->last_index = idx;
    if (arr->max_index < idx)
        arr->max_index = idx;
}

IA_ELEM IA(get)(IA_NAME *arr, long idx)
{
    if (idx < 0 || arr->max_index < idx)
        abi_assert_fail("(index>=0) && (index <= arr->max_index)", IA_FILE, 395);
    return arr->data[idx];
}

/* original name *_is_empty: slot +0x34 "add" = append at last_index + 1 */
void IA(is_empty)(IA_NAME *arr, IA_ELEM val)
{
    (*arr->append)(arr, arr->last_index + 1, val);
}

/* original name *_is_full: slot +0x30 "add_plain" = insert at last_index + 1 */
void IA(is_full)(IA_NAME *arr, IA_ELEM val)
{
    (*arr->insert)(arr, arr->last_index + 1, val);
}

void IA(dump)(IA_NAME *arr)
{
    printf("******** Dumping Array Information ***********\n");
    printf("1. array_size = %ld \n", arr->array_size);
    printf("2. blocksz    = %ld \n", arr->blocksz);
    printf("3. max_index  = %ld \n", arr->max_index);
    printf("4. last_index = %ld \n", arr->last_index);
    printf("5. remove     = %ld \n", arr->remove);
    printf("********      End Dumping          ***********\n");
}

IA_CREATE_RET IA(create)(long init_sz, long blocksz, void (*freefn)(IA_ELEM))
{
    IA_NAME *a;

    /* assert((init_sz >= 0)&&(blocksz >= 0)) compiled as an unsigned
       compare in the original: it can never fire */
    a = (IA_NAME *)malloc(sizeof(IA_NAME));
    if (blocksz == 0)
        a->blocksz = 0x32L;
    else
        a->blocksz = blocksz;
    if (freefn != NULL)
        a->freefn = freefn;
    else
        a->freefn = IA(count);
    a->init_sz = init_sz;
    a->array_size = 0;
    a->max_index = -1L;
    a->last_index = -1L;
    a->remove = 0;
    a->data = NULL;
    a->flags = NULL;
    a->dump = IA(dump);
    a->get = IA(get);
    a->insert = IA(insert);
    a->append = IA(append);
    a->add_plain = IA(is_full);
    a->add = IA(is_empty);
    a->compact = IA(compact);
    IA(grow)(a, a->init_sz);
    return a;
}

#undef IA
#undef IA_CAT
#undef IA_CAT2
