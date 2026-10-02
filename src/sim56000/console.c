/* Motorola SIM56000.EXE 6.3.0, console module, 0x43dcb0-0x43deb0.
 * Portable pool helpers and signed pair comparator; screen UI is pending.
 */
#include <string.h>
#include "sim56000.h"

void *pool_new_block(void *pool, unsigned long size, unsigned long kind)
{
    struct sim_pool *p;
    struct pool_block *block;
    p = (struct sim_pool *)pool;
    block = (struct pool_block *)prof_malloc(sizeof(*block));
    block->data = (unsigned char *)prof_malloc(size);
    block->size = size;
    block->used = 0;
    block->kind = kind;
    block->next = NULL;
    ++p->block_count;
    return block;
}

void pool_init(void *pool, unsigned long blocksize)
{
    struct sim_pool *p;
    p = (struct sim_pool *)pool;
    p->block_count = 0;
    p->block_size = blocksize;
    p->strings = (struct pool_block *)pool_new_block(p, blocksize, 1);
    p->head = p->strings;
    p->objects = (struct pool_block *)pool_new_block(p, blocksize, 0);
    p->tail = p->objects;
    p->head->next = p->objects;
}

void chain_free(void *head)
{
    struct pool_block *block, *next;
    block = *(struct pool_block **)head;
    while (block != NULL) {
        next = block->next;
        dsp_free(block->data);
        dsp_free(block);
        block = next;
    }
}

static unsigned char *pool_take(struct sim_pool *pool, unsigned long n,
                                unsigned long kind)
{
    struct pool_block *block;
    unsigned long size;
    unsigned char *result;
    block = kind == 0 ? pool->objects : pool->strings;
    size = pool->block_size;
    /* An oversized block keeps its own size. The original nevertheless uses
     * the configured size for the next allocation's capacity comparison. */
    if (block->used > size || n > size - block->used) {
        if (size <= n)
            size = n;
        block = (struct pool_block *)pool_new_block(pool, size, kind);
        pool->tail->next = block;
        pool->tail = block;
        if (kind == 0)
            pool->objects = block;
        else
            pool->strings = block;
    }
    result = block->data + block->used;
    block->used += n;
    return result;
}

void *pool_alloc(void *pool, unsigned long n)
{
    /* x86 rounds in a 32-bit register. This also handles an already aligned n. */
    n = ((n + 7UL) & MASK32) & ~7UL;
    return pool_take((struct sim_pool *)pool, n, 0);
}

char *pool_strdup(void *pool, char *s)
{
    char *result;
    size_t length;
    if (s == NULL)
        return NULL;
    length = strlen(s);
    result = (char *)pool_take((struct sim_pool *)pool,
                              (unsigned long)length + 1UL, 1);
    memcpy(result, s, length + 1);
    return result;
}

long avl_cmp_h43de70(void *a, void *b)
{
    long *item, *key;
    unsigned long x, y;
    int i;
    item = (long *)a;
    key = (long *)b;
    for (i = 0; i < 2; ++i) {
        /* Bias the sign bit to compare original signed 32-bit fields on
         * hosts with either 32-bit or 64-bit long. */
        x = ((unsigned long)item[i] & MASK32) ^ 0x80000000UL;
        y = ((unsigned long)key[i] & MASK32) ^ 0x80000000UL;
        if (y < x)
            return 0;
        if (x < y)
            return 2;
    }
    return 1;
}
