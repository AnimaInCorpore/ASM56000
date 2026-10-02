/* Motorola SIM56000.EXE 6.3.0: AVL tree, 0x46a700-0x46b090.
 * Recovered tree operations, allocator selection and bounded iterator.
 * Return values checked against x86 code at 0x46a930 and 0x46a990.
 */
#include "sim56000.h"
#include "simproto.h"

static long node_height(struct avl_node *node)
{
    return node == NULL ? 0 : node->height;
}

void *avl_set_node(void *node, void *left, void *item, void *right)
{
    struct avl_node *n;
    long lh, rh;
    n = (struct avl_node *)node;
    if (n != NULL) {
        n->left = (struct avl_node *)left;
        n->item = item;
        n->right = (struct avl_node *)right;
        lh = node_height(n->left);
        rh = node_height(n->right);
        n->height = (lh > rh ? lh : rh) + 1;
    }
    return n;
}

/* Rebuild the ordered triple (l,d1,m,d2,r) using n0 and n1.
 * Keep n0 as root, as the original does; rotations exchange node contents.
 * The middle subtree supplies the third node for a double rotation.
 */
void *avl_rebalance(void *n0, void *n1, void *l, void *d1,
                    void *m, void *d2, void *r)
{
    struct avl_node *middle;
    void *a, *b, *item;
    long lh, mh, rh;
    lh = node_height((struct avl_node *)l);
    mh = node_height((struct avl_node *)m);
    rh = node_height((struct avl_node *)r);
    if (mh > lh && mh > rh) {
        middle = (struct avl_node *)m;
        item = middle->item;
        a = avl_set_node(n1, l, d1, middle->left);
        b = avl_set_node(m, middle->right, d2, r);
        return avl_set_node(n0, a, item, b);
    }
    if (lh >= rh) {
        b = avl_set_node(n1, m, d2, r);
        return avl_set_node(n0, l, d1, b);
    }
    a = avl_set_node(n1, l, d1, m);
    return avl_set_node(n0, a, d2, r);
}

void avl_walk_node(void *node, void (*fn)(void *), long order)
{
    struct avl_node *n;
    int forward;
    n = (struct avl_node *)node;
    if (n == NULL)
        return;
    forward = order == 0 || order == 2 || order == 4;
    if (order == 2 || order == 3)
        fn(n->item);
    avl_walk_node(forward ? n->left : n->right, fn, order);
    if (order == 0 || order == 1)
        fn(n->item);
    avl_walk_node(forward ? n->right : n->left, fn, order);
    if (order == 4 || order == 5)
        fn(n->item);
}

void avl_walk(void *tree, void (*fn)(void *), long order, long bracket)
{
    struct avl_tree *t;
    t = (struct avl_tree *)tree;
    if (t != NULL) {
        if (bracket == 1 || bracket == 3)
            fn(NULL);
        avl_walk_node(t->root, fn, order);
        if (bracket == 2 || bracket == 3)
            fn(NULL);
    }
}

struct avl_tree *avl_cur_tree;
struct avl_node *avl_spare_node;
struct avl_node *avl_removed;

/* Generated comparator records are seven function pointers per row.
 * Select fields explicitly: C does not permit treating struct fields as an array.
 * Comparators return 0 for key < item, 1 for equality, 2 for key > item.
 */
static long compare_items(void *item, void *key)
{
    struct rec7w_ecd15 *row;
    simcmp fn;
    long index;
    if (key == NULL)
        return 3;
    index = avl_cur_tree->cmp_index;
    row = &avl_cmp_tab[index / 7];
    switch (index % 7) {
    case 0: fn = row->w0; break;
    case 1: fn = row->w1; break;
    case 2: fn = row->w2; break;
    case 3: fn = row->w3; break;
    case 4: fn = row->w4; break;
    case 5: fn = row->w5; break;
    default: fn = row->w6; break;
    }
    return fn(item, key);
}

static void *tree_alloc(unsigned long size)
{
    if (prof_ctx->heap_mode == 1)
        return prof_malloc(size);
    return pool_alloc(&prof_ctx->pool, size);
}

void *avl_new(long cmp_type)
{
    struct avl_tree *tree;
    tree = (struct avl_tree *)tree_alloc(sizeof(*tree));
    tree->root = NULL;
    tree->count = 0;
    tree->cmp_index = cmp_type;
    return tree;
}

void avl_free_nodes(void *node, long free_mode)
{
    struct avl_node *n;
    n = (struct avl_node *)node;
    if (n != NULL) {
        avl_free_nodes(n->left, free_mode);
        avl_free_nodes(n->right, free_mode);
        if (free_mode == 1)
            dsp_free(n->item);
        if (free_mode != 0)
            dsp_free(n);
    }
}

void avl_free(void *tree, long free_mode)
{
    if (tree != NULL) {
        avl_cur_tree = (struct avl_tree *)tree;
        avl_free_nodes(avl_cur_tree->root, free_mode);
        dsp_free(tree);
    }
}

void *avl_insert_node(void *node, void *item, long replace)
{
    struct avl_node *n, *child;
    long cmp;
    n = (struct avl_node *)node;
    cmp = n == NULL ? 3 : compare_items(n->item, item);
    if (cmp == 1 && replace == 0)
        return n;
    if (cmp == 0 || cmp == 1) {
        child = (struct avl_node *)avl_insert_node(n->left, item, replace);
        n->left = child;
        return avl_rebalance(n, child, child->left, child->item,
                              child->right, n->item, n->right);
    }
    if (cmp == 2) {
        child = (struct avl_node *)avl_insert_node(n->right, item, replace);
        n->right = child;
        return avl_rebalance(n, child, n->left, n->item,
                              child->left, child->item, child->right);
    }
    if (cmp == 3) {
        n = avl_spare_node;
        if (n == NULL)
            n = (struct avl_node *)tree_alloc(sizeof(*n));
        avl_spare_node = NULL;
        ++avl_cur_tree->count;
        return avl_set_node(n, NULL, item, NULL);
    }
    return n;
}

void avl_insert(void *tree, void *item, long replace)
{
    if (tree != NULL) {
        avl_cur_tree = (struct avl_tree *)tree;
        avl_cur_tree->root = (struct avl_node *)
            avl_insert_node(avl_cur_tree->root, item, replace);
    }
}

void *avl_delete_node(void *node, void *key)
{
    struct avl_node *n, *child, *swap;
    void *item;
    long cmp;
    n = (struct avl_node *)node;
    cmp = n == NULL ? 3 : compare_items(n->item, key);
    if (cmp == 1) {
        if (n->left != NULL) {
            swap = n->left;
            while (swap->right != NULL)
                swap = swap->right;
            item = n->item;
            n->item = swap->item;
            swap->item = item;
            cmp = 0;
        } else if (n->right != NULL) {
            swap = n->right;
            while (swap->left != NULL)
                swap = swap->left;
            item = n->item;
            n->item = swap->item;
            swap->item = item;
            cmp = 2;
        } else {
            --avl_cur_tree->count;
            avl_removed = n;
            return NULL;
        }
    }
    if (cmp == 0) {
        child = (struct avl_node *)avl_delete_node(n->left, key);
        avl_set_node(n, child, n->item, n->right);
        child = n->right;
        if (child != NULL)
            return avl_rebalance(n, child, n->left, n->item,
                                  child->left, child->item, child->right);
        return n;
    }
    if (cmp == 2) {
        child = (struct avl_node *)avl_delete_node(n->right, key);
        avl_set_node(n, n->left, n->item, child);
        child = n->left;
        if (child != NULL)
            return avl_rebalance(n, child, child->left, child->item,
                                  child->right, n->item, n->right);
        return n;
    }
    return NULL;
}

void *avl_delete(void *tree, void *key, long free_mode, long repeat)
{
    void *item;
    item = NULL;
    if (tree != NULL) {
        avl_cur_tree = (struct avl_tree *)tree;
        do {
            avl_removed = NULL;
            avl_cur_tree->root = (struct avl_node *)
                avl_delete_node(avl_cur_tree->root, key);
            if (avl_removed != NULL) {
                if (free_mode == 0)
                    item = avl_removed->item;
                if (free_mode == 1)
                    dsp_free(avl_removed->item);
                if (free_mode != 0)
                    dsp_free(avl_removed);
            }
            /* Original loops unconditionally for repeat == 1; all recovered
             * callers use zero. Preserve this internal interface behavior. */
        } while (repeat == 1);
    }
    return item;
}

void *avl_find(void *tree, void *key, long mode)
{
    struct avl_node *n, *candidate;
    long cmp;
    avl_cur_tree = (struct avl_tree *)tree;
    n = tree == NULL ? NULL : avl_cur_tree->root;
    candidate = NULL;
    while (n != NULL) {
        cmp = compare_items(n->item, key);
        if (cmp == 1)
            return n->item;
        if (cmp != mode)
            candidate = n;
        n = cmp == 0 ? n->left : n->right;
    }
    return mode != 1 && candidate != NULL ? candidate->item : NULL;
}

/* The original cursor stores 32 (state,node) pairs. Keep that bound but
 * use an index, avoiding its pointer-before-array exhaustion sentinel. */
struct avl_cursor {
    struct avl_node *node[32];
    unsigned char state[32];
    int top;
    struct avl_tree *tree;
    void *end_key;
};

void *avl_iter(void *tree, void *iter, void *key)
{
    struct avl_cursor *cursor;
    struct avl_node *n;
    long cmp;
    int last, top;
    if (tree != NULL) {
        avl_cur_tree = (struct avl_tree *)tree;
        n = avl_cur_tree->root;
        if (n == NULL)
            return NULL;
        cursor = (struct avl_cursor *)prof_malloc(sizeof(*cursor));
        cursor->tree = avl_cur_tree;
        cursor->end_key = key;
        cursor->top = 0;
        last = -1;
        while (n != NULL) {
            top = cursor->top;
            cmp = compare_items(n->item, iter);
            cursor->node[top] = n;
            cursor->state[top] = (unsigned char)(cmp == 2 ? 2 : 1);
            if (cmp != 2)
                last = top;
            n = cmp == 2 ? n->right : n->left;
            ++cursor->top;
        }
        if (last < 0) {
            dsp_free(cursor);
            return NULL;
        }
        cursor->top = last;
        return cursor;
    }
    cursor = (struct avl_cursor *)iter;
    if (cursor == NULL)
        return NULL;
    avl_cur_tree = cursor->tree;
    while (cursor->top >= 0) {
        top = cursor->top;
        n = cursor->node[top];
        if (n == NULL) {
            --cursor->top;
            continue;
        }
        ++cursor->state[top];
        if (cursor->state[top] == 1) {
            ++cursor->top;
            cursor->state[top + 1] = 0;
            cursor->node[top + 1] = n->left;
        } else if (cursor->state[top] == 2) {
            ++cursor->top;
            cursor->state[top + 1] = 0;
            cursor->node[top + 1] = n->right;
            cmp = compare_items(n->item, cursor->end_key);
            if (cmp != 0)
                return n->item;
            break;
        } else if (cursor->state[top] == 3) {
            --cursor->top;
        }
    }
    dsp_free(cursor);
    return NULL;
}

void *avl_copy_sorted(void *tree, long cmp_type, long resort)
{
    struct avl_tree *source, *copy;
    struct avl_tree rebuilt;
    void *item, *cursor;
    source = (struct avl_tree *)tree;
    if (resort == 1) {
        rebuilt.root = NULL;
        rebuilt.count = 0;
        rebuilt.cmp_index = cmp_type;
        while (source->root != NULL) {
            item = avl_delete(source, source->root->item, 0, 0);
            avl_spare_node = avl_removed;
            avl_insert(&rebuilt, item, 1);
        }
        *source = rebuilt;
        return source;
    }
    copy = (struct avl_tree *)avl_new(cmp_type);
    cursor = avl_iter(source, NULL, NULL);
    item = avl_iter(NULL, cursor, NULL);
    while (item != NULL) {
        avl_insert(copy, item, 1);
        item = avl_iter(NULL, cursor, NULL);
    }
    return copy;
}
