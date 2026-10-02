/* Test real SIM56000 allocation, pool, profiler helpers and AVL integration.
 * Only libc allocation failure, mdisk spill and transcript output are mocked.
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "sim56000.h"

struct sim_state *cur_sim;
struct dev_inst *cur_dev;
static struct sim_state states[2];
static struct dev_inst devices[2];
static struct sim_state *state_slots[2] = { &states[0], &states[1] };
static struct dev_inst *device_slots[2] = { &devices[0], &devices[1] };
struct sim_state **dev_state_tab = state_slots;
struct dev_inst **dev_tab = device_slots;
long cur_dev_index;
long gui_mode[2];
static struct prof_ctx context;
struct rec7w_ecd15 avl_cmp_tab[2] = {
    { NULL, prof_cmp_ulong, NULL, NULL, NULL, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL, avl_cmp_h43de70, NULL }
};

static void *allocations[4096];
static size_t sizes[4096];
static int slots, live;
static int malloc_fail, realloc_fail, spill_available, spill_calls, outputs;
static char message[80];
static struct sim_state *output_state;
static struct dev_inst *output_device;

static void record(void *p, size_t n)
{
    assert(p != NULL && slots < 4096);
    allocations[slots] = p;
    sizes[slots++] = n;
    ++live;
}

void *sim_test_malloc(size_t n)
{
    void *p;
    if (malloc_fail != 0) {
        --malloc_fail;
        return NULL;
    }
    p = malloc(n == 0 ? 1 : n);
    assert(p != NULL);
    memset(p, 0xa5, n);
    record(p, n);
    return p;
}

void sim_test_free(void *p)
{
    int i;
    if (p == NULL)
        return;
    for (i = 0; i < slots; ++i) {
        if (allocations[i] == p) {
            allocations[i] = NULL;
            --live;
            free(p);
            return;
        }
    }
    assert(!"free of unknown or interior pool pointer");
}

void *sim_test_realloc(void *p, size_t n)
{
    void *result;
    size_t old_size;
    int i;
    if (realloc_fail != 0) {
        --realloc_fail;
        return NULL;
    }
    if (p == NULL)
        return sim_test_malloc(n);
    for (i = 0; i < slots; ++i) {
        if (allocations[i] == p) {
            old_size = sizes[i];
            result = realloc(p, n == 0 ? 1 : n);
            assert(result != NULL);
            allocations[i] = result;
            sizes[i] = n;
            if (n > old_size)
                memset((unsigned char *)result + old_size, 0xa5, n - old_size);
            return result;
        }
    }
    assert(!"reallocation of unknown allocation");
    return NULL;
}

long mdisk_spill(void)
{
    ++spill_calls;
    if (spill_available == 0)
        return 0;
    --spill_available;
    return 1;
}

void out_text(char *text, long nocmdlog)
{
    assert(nocmdlog == 1);
    assert(strlen(text) < sizeof(message));
    strcpy(message, text);
    output_state = cur_sim;
    output_device = cur_dev;
    ++outputs;
}

static void reset(void)
{
    assert(live == 0);
    slots = 0;
    malloc_fail = realloc_fail = spill_available = spill_calls = outputs = 0;
    message[0] = '\0';
    memset(&context, 0, sizeof(context));
    prof_ctx = &context;
    cur_dev_index = 0;
    cur_sim = &states[1];
    cur_dev = &devices[1];
    gui_mode[0] = 0;
    avl_cur_tree = NULL;
    avl_removed = avl_spare_node = NULL;
}

static void allocation_tests(void)
{
    unsigned char *p, *q;
    int i;
    reset();
    p = (unsigned char *)dsp_alloc(13, 1);
    for (i = 0; i < 13; ++i)
        assert(p[i] == 0);
    q = (unsigned char *)dsp_alloc(13, 0);
    assert(q[0] == 0xa5 && q[12] == 0xa5);
    dsp_free(q);
    p[0] = 0x42;
    q = (unsigned char *)dsp_realloc(p, 29);
    assert(q[0] == 0x42);
    dsp_free(q);
    dsp_free(NULL);
    malloc_fail = 2; spill_available = 2;
    p = (unsigned char *)dsp_alloc(9, 1);
    assert(spill_calls == 2 && outputs == 0 && p[8] == 0);
    dsp_free(p);
    malloc_fail = 1; spill_available = 0;
    assert(dsp_alloc(9, 0) == NULL);
    assert(outputs == 1);
    assert(strcmp(message, "Insufficient memory: dsp_alloc") == 0);
    assert(output_state == &states[0] && output_device == &devices[0]);
    assert(cur_sim == &states[1] && cur_dev == &devices[1]);
    p = (unsigned char *)dsp_alloc(7, 1);
    p[0] = 0x31;
    realloc_fail = 1; spill_available = 1;
    q = (unsigned char *)dsp_realloc(p, 20);
    assert(q[0] == 0x31 && outputs == 1);
    realloc_fail = 2; spill_available = 1;
    assert(dsp_realloc(q, 25) == NULL);
    assert(q[0] == 0x31); /* failed resize preserves the caller's allocation */
    assert(strcmp(message, "Insufficient memory: dsp_realloc") == 0);
    assert(output_state == &states[0] && output_device == &devices[0]);
    assert(cur_sim == &states[1] && cur_dev == &devices[1]);
    gui_mode[0] = 1;
    assert(dsp_alloc(1, 1) == NULL);
    assert(dsp_realloc(q, 30) == NULL);
    dsp_free(q); /* original external free hook is a no-op */
    assert(live == 1);
    gui_mode[0] = 0;
    dsp_free(q);
    assert(live == 0);
}

static void profiler_tests(void)
{
    unsigned char *p;
    unsigned char bytes[10] = { 0,1,2,3,4,5,6,7,8,9 };
    unsigned char swapped[10] = { 3,2,1,0,7,6,5,4,8,9 };
    unsigned long a, b;
    long pair_a[2], pair_b[2];
    reset();
    p = (unsigned char *)prof_malloc(5);
    assert(p[0] == 0 && p[4] == 0);
    dsp_free(p);
    context.flags = 0x20;
    malloc_fail = 1;
    if (setjmp(prof_jmpbuf) == 0) {
        prof_malloc(3);
        assert(!"prof_malloc must jump on failure");
    }
    assert(context.flags == (0x20 | PROF_FL_NO_FILE));
    assert(outputs == 1 && live == 0);
    prof_swap32(bytes, sizeof(bytes));
    assert(memcmp(bytes, swapped, sizeof(bytes)) == 0);
    prof_swap32(bytes, sizeof(bytes));
    assert(bytes[0] == 0 && bytes[7] == 7 && bytes[9] == 9);
    a = 0xffffffffUL; b = 0;
    assert(prof_cmp_ulong(&a, &b) == 0);
    assert(prof_cmp_ulong(&b, &a) == 2);
    assert(prof_cmp_ulong(&a, &a) == 1);
    pair_a[0] = -1; pair_a[1] = 3;
    pair_b[0] = 0; pair_b[1] = -2;
    assert(avl_cmp_h43de70(pair_a, pair_b) == 2);
    pair_b[0] = -1;
    assert(avl_cmp_h43de70(pair_a, pair_b) == 0);
    pair_b[1] = 3;
    assert(avl_cmp_h43de70(pair_a, pair_b) == 1);
    assert(prof_list_count(NULL) == -1);
}

static void pool_tests(void)
{
    struct sim_pool pool;
    struct pool_block *first;
    unsigned char *a, *b, *c;
    char *s, *t;
    long count;
    unsigned long i;
    reset();
    pool_init(&pool, 16);
    assert(pool.block_count == 2 && live == 4);
    assert(pool.head == pool.strings && pool.head->next == pool.objects);
    assert(pool.tail == pool.objects);
    first = pool.objects;
    a = (unsigned char *)pool_alloc(&pool, 1);
    b = (unsigned char *)pool_alloc(&pool, 8);
    assert(b == a + 8 && pool.objects->used == 16);
    a[0] = 0x12; b[0] = 0x34;
    c = (unsigned char *)pool_alloc(&pool, 1);
    assert(pool.block_count == 3 && first->next == pool.objects);
    assert(a[0] == 0x12 && b[0] == 0x34 && c[0] == 0);
    s = pool_strdup(&pool, "hello");
    t = pool_strdup(&pool, "!");
    assert(strcmp(s, "hello") == 0 && t == s + 6);
    assert(pool_strdup(&pool, NULL) == NULL);
    count = pool.block_count;
    s = pool_strdup(&pool, "abcdefghijklmnopq");
    assert(pool.block_count == count + 1 && pool.strings->size == 18);
    assert(strcmp(s, "abcdefghijklmnopq") == 0);
    count = pool.block_count;
    t = pool_strdup(&pool, "x");
    assert(pool.block_count == count + 1 && strcmp(t, "x") == 0);
    c = (unsigned char *)pool_alloc(&pool, 37);
    assert(pool.objects->size == 40 && pool.objects->used == 40);
    for (i = 0; i < 40; ++i)
        assert(c[i] == 0);
    count = pool.block_count;
    pool_alloc(&pool, 0); /* oversized cursor exceeds configured blocksize */
    assert(pool.block_count == count + 1);
    chain_free(&pool.head);
    assert(live == 0);
    /* Original leaves the head untouched; callers reinitialize after freeing. */
    pool_init(&pool, 32);
    assert(pool.block_count == 2);
    chain_free(&pool.head);
    assert(live == 0);
}

static unsigned long values[101];
static unsigned long previous;
static int walked;

static void ordered(void *item)
{
    unsigned long value;
    value = *(unsigned long *)item;
    if (walked != 0)
        assert(previous < value);
    previous = value;
    ++walked;
}

static void integration_tests(long heap_mode)
{
    struct avl_tree *tree, *copy;
    void *cursor;
    long i, before;
    reset();
    context.heap_mode = heap_mode;
    if (heap_mode == 0)
        pool_init(&context.pool, 64);
    tree = (struct avl_tree *)avl_new(1);
    for (i = 0; i < 101; ++i) {
        values[i] = (unsigned long)i;
        avl_insert(tree, &values[i], 0);
    }
    walked = 0;
    avl_walk(tree, ordered, 0, 0);
    assert(walked == 101 && prof_list_count(tree) == 101);
    before = live;
    avl_copy_sorted(tree, 1, 1);
    assert(live == before && tree->count == 101);
    cursor = avl_iter(tree, &values[30], &values[35]);
    for (i = 30; i <= 35; ++i)
        assert(avl_iter(NULL, cursor, NULL) == &values[i]);
    assert(avl_iter(NULL, cursor, NULL) == NULL);
    assert(live == before);
    context.heap_mode = 1;
    copy = (struct avl_tree *)avl_copy_sorted(tree, 1, 0);
    assert(copy->count == 101);
    avl_free(copy, 2);
    assert(live == before);
    if (heap_mode == 1) {
        for (i = 0; i < 101; ++i)
            avl_delete(tree, &values[i], 2, 0);
        avl_free(tree, 2);
    } else {
        /* Pooled nodes have arena lifetime. Never free individual subobjects. */
        for (i = 0; i < 101; ++i)
            assert(avl_delete(tree, &values[i], 0, 0) == &values[i]);
        assert(tree->root == NULL && tree->count == 0);
        chain_free(&context.pool.head);
    }
    assert(live == 0);
}

int main(void)
{
    allocation_tests();
    profiler_tests();
    pool_tests();
    integration_tests(1);
    integration_tests(0);
    puts("OK: SIM56000 allocation, failure recovery, pools and real AVL integration");
    return 0;
}
