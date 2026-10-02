/* Test-only boundaries for untranslated profiler allocation and comparators. */
#include <assert.h>
#include <stdlib.h>
#include "sim56000.h"

static struct prof_ctx context;
struct prof_ctx *prof_ctx = &context;
static void *allocated[8192];
static int slots;
long avl_test_live, avl_test_heap, avl_test_pool, avl_test_frees;

void *prof_malloc(unsigned long size)
{
    void *p;
    assert(slots < 8192);
    p = malloc((size_t)size);
    assert(p != NULL);
    allocated[slots++] = p;
    ++avl_test_live;
    ++avl_test_heap;
    return p;
}

void *pool_alloc(void *pool, unsigned long size)
{
    void *p;
    assert(pool == &context.pool);
    p = prof_malloc(size);
    --avl_test_heap;
    ++avl_test_pool;
    return p;
}

void dsp_free(void *p)
{
    int i;
    if (p == NULL)
        return;
    for (i = 0; i < slots; ++i) {
        if (allocated[i] == p) {
            free(p);
            allocated[i] = NULL;
            --avl_test_live;
            ++avl_test_frees;
            return;
        }
    }
    assert(!"free of an unowned or already freed allocation");
}

void avl_test_reset(long mode)
{
    int i;
    for (i = 0; i < slots; ++i)
        if (allocated[i] != NULL)
            dsp_free(allocated[i]);
    slots = 0;
    avl_test_live = avl_test_heap = avl_test_pool = avl_test_frees = 0;
    context.heap_mode = mode;
    avl_cur_tree = NULL;
    avl_spare_node = avl_removed = NULL;
}

static long ascending(void *item, void *key)
{
    long a, b;
    a = *(long *)item;
    b = *(long *)key;
    return b < a ? 0 : b == a ? 1 : 2;
}

static long descending(void *item, void *key)
{
    long cmp;
    cmp = ascending(item, key);
    return cmp == 1 ? 1 : 2 - cmp;
}

/* Keep the generated table's shape at the test boundary. */
#define ASC ascending
#define DESC descending
struct rec7w_ecd15 avl_cmp_tab[2] = {
    {ASC, ASC, ASC, ASC, ASC, ASC, ASC},
    {ASC, ASC, DESC, ASC, ASC, ASC, ASC}
};
