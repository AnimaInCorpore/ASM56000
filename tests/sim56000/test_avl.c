/* Structural tests for the translated SIM56000 AVL primitives. */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "sim56000.h"
#include "simproto.h"

static long values[7] = { 1, 2, 3, 4, 5, 6, 7 };
static long seen[16];
static int count;

static void visit(void *item)
{
    assert(count < 16);
    seen[count++] = item == NULL ? 0 : *(long *)item;
}

static void check_walk(struct avl_tree *tree, long order, long bracket,
                       const long *expected, int n)
{
    int i;
    count = 0;
    avl_walk(tree, visit, order, bracket);
    assert(count == n);
    for (i = 0; i < n; ++i)
        assert(seen[i] == expected[i]);
}

static long check_height(struct avl_node *node)
{
    long l, r;
    if (node == NULL)
        return 0;
    l = check_height(node->left);
    r = check_height(node->right);
    assert(node->height == (l > r ? l : r) + 1);
    assert(l - r >= -1 && l - r <= 1);
    return node->height;
}

static void rotations(void)
{
    struct avl_node root, other, middle, leaf;
    struct avl_tree tree;
    long expect[3] = { 1, 2, 3 };
    long expect4[4] = { 1, 2, 3, 4 };
    tree.root = &root;
    tree.count = 3;
    tree.cmp_index = 0;
    assert(avl_set_node(NULL, NULL, NULL, NULL) == NULL);

    /* Left and right single rotations, preserving the root address. */
    avl_set_node(&leaf, NULL, &values[0], NULL);
    assert(avl_rebalance(&root, &other, &leaf, &values[1], NULL,
                         &values[2], NULL) == &root);
    check_walk(&tree, 0, 0, expect, 3);
    check_height(&root);
    avl_set_node(&leaf, NULL, &values[2], NULL);
    assert(avl_rebalance(&root, &other, NULL, &values[0], NULL,
                         &values[1], &leaf) == &root);
    check_walk(&tree, 0, 0, expect, 3);
    check_height(&root);

    /* Both call orientations of a double rotation; middle is reused. */
    avl_set_node(&middle, NULL, &values[1], NULL);
    avl_rebalance(&root, &other, NULL, &values[0], &middle,
                  &values[2], NULL);
    check_walk(&tree, 0, 0, expect, 3);
    check_height(&root);
    avl_set_node(&middle, NULL, &values[1], NULL);
    avl_rebalance(&other, &root, NULL, &values[0], &middle,
                  &values[2], NULL);
    tree.root = &other;
    check_walk(&tree, 0, 0, expect, 3);
    check_height(&other);

    /* Preserve the middle node's children while rewriting its contents. */
    avl_set_node(&leaf, NULL, &values[2], NULL);
    avl_set_node(&middle, NULL, &values[1], &leaf);
    avl_rebalance(&root, &other, NULL, &values[0], &middle,
                  &values[3], NULL);
    tree.root = &root;
    check_walk(&tree, 0, 0, expect4, 4);
    check_height(&root);

    /* Equal heights choose the left-root branch, including two leaves. */
    avl_rebalance(&root, &other, NULL, &values[0], NULL,
                  &values[1], NULL);
    assert(root.item == &values[0]);
    assert(root.right == &other);
    check_height(&root);
}

static void extended_tests(void);

int main(void)
{
    struct avl_node nodes[7];
    struct avl_tree tree;
    static const long orders[6][7] = {
        {1,2,3,4,5,6,7}, {7,6,5,4,3,2,1},
        {4,2,1,3,6,5,7}, {4,6,7,5,2,3,1},
        {1,3,2,5,7,6,4}, {7,5,6,3,1,2,4}
    };
    static const long empty[2] = {0,0};
    static const long brackets[4][3] = {
        {4,0,0}, {0,4,0}, {4,0,0}, {0,4,0}
    };
    int i;
    memset(nodes, 0, sizeof(nodes));
    for (i = 0; i < 7; ++i)
        avl_set_node(&nodes[i], NULL, &values[i], NULL);
    avl_set_node(&nodes[1], &nodes[0], &values[1], &nodes[2]);
    avl_set_node(&nodes[5], &nodes[4], &values[5], &nodes[6]);
    avl_set_node(&nodes[3], &nodes[1], &values[3], &nodes[5]);
    tree.root = &nodes[3];
    tree.count = 7;
    tree.cmp_index = 0;
    check_height(tree.root);
    for (i = 0; i < 6; ++i)
        check_walk(&tree, i, 0, orders[i], 7);
    tree.root = &nodes[3];
    avl_set_node(tree.root, NULL, &values[3], NULL);
    for (i = 0; i < 4; ++i)
        check_walk(&tree, 0, i, brackets[i], i == 3 ? 3 : i == 0 ? 1 : 2);
    tree.root = NULL;
    check_walk(&tree, 0, 3, empty, 2);
    check_walk(NULL, 0, 3, NULL, 0);
    count = 0;
    avl_walk_node(NULL, visit, 0);
    assert(count == 0);
    rotations();
    extended_tests();
    puts("OK: all 14 SIM56000 AVL routines, mutations, ranges and ownership");
    return 0;
}

extern long avl_test_live, avl_test_heap, avl_test_pool, avl_test_frees;
extern void avl_test_reset(long mode);

static long data[257];
static long last_value;
static int total, reverse_order;

static void sorted_visit(void *item)
{
    long value;
    assert(item != NULL);
    value = *(long *)item;
    if (total != 0)
        assert(reverse_order ? value <= last_value : value >= last_value);
    last_value = value;
    ++total;
}

static void check_tree(struct avl_tree *tree)
{
    total = 0;
    reverse_order = tree->cmp_index == 9;
    avl_walk(tree, sorted_visit, 0, 0);
    assert(total == tree->count);
    check_height(tree->root);
}

static void check_range(struct avl_tree *tree, long *start, long *end,
                        long lo, long hi)
{
    void *cursor, *item;
    long expected, before;
    before = avl_test_live;
    cursor = avl_iter(tree, start, end);
    expected = lo;
    item = avl_iter(NULL, cursor, NULL);
    while (item != NULL) {
        assert(*(long *)item == expected);
        ++expected;
        item = avl_iter(NULL, cursor, NULL);
    }
    assert(expected == hi + 1);
    assert(avl_test_live == before);
}

static void mutation_tests(long mode)
{
    struct avl_tree *tree, *copy;
    struct avl_node *removed;
    long i, j, key, start, end, before, replacement;
    void *item, *cursor, *cursor2;
    avl_test_reset(mode);
    tree = (struct avl_tree *)avl_new(1);
    assert(tree->count == 0 && tree->root == NULL);
    assert(avl_find(tree, &data[0], 1) == NULL);
    assert(avl_iter(tree, NULL, NULL) == NULL);
    assert(avl_iter(NULL, NULL, NULL) == NULL);
    /* Multiplication permutes all 257 keys; check after every mutation. */
    for (i = 0; i < 257; ++i) {
        j = (i * 73) % 257;
        avl_insert(tree, &data[j], 0);
        check_tree(tree);
    }
    for (i = 0; i < 257; ++i) {
        key = i;
        assert(avl_find(tree, &key, 1) == &data[i]);
    }
    before = avl_test_live;
    replacement = 128;
    avl_insert(tree, &replacement, 0);
    assert(tree->count == 257 && avl_test_live == before);
    assert(avl_find(tree, &replacement, 1) == &data[128]);
    avl_insert(tree, &replacement, 1);
    assert(tree->count == 258 && avl_test_live == before + 1);
    check_tree(tree);
    /* Delete each equal item separately; pointer identity may differ. */
    item = avl_delete(tree, &replacement, 0, 0);
    assert(item == &replacement || item == &data[128]);
    removed = avl_removed;
    assert(removed != NULL && removed->item == item);
    dsp_free(removed);
    item = avl_delete(tree, &replacement, 0, 0);
    assert(item == &replacement || item == &data[128]);
    dsp_free(avl_removed);
    assert(tree->count == 256);
    avl_insert(tree, &data[128], 0);
    check_tree(tree);

    key = -1;
    assert(avl_find(tree, &key, 1) == NULL);
    assert(avl_find(tree, &key, 0) == NULL);
    assert(avl_find(tree, &key, 2) == &data[0]);
    key = 257;
    assert(avl_find(tree, &key, 1) == NULL);
    assert(avl_find(tree, &key, 0) == &data[256]);
    assert(avl_find(tree, &key, 2) == NULL);
    check_range(tree, NULL, NULL, 0, 256);
    start = 90; end = 100;
    check_range(tree, &start, &end, 90, 100);
    start = -1; end = 0;
    check_range(tree, &start, &end, 0, 0);
    start = 257;
    check_range(tree, &start, NULL, 257, 256);
    start = 20; end = 19;
    check_range(tree, &start, &end, 20, 19);
    /* Cursors keep their own tree while the global current tree changes. */
    copy = (struct avl_tree *)avl_copy_sorted(tree, 9, 0);
    assert(copy != tree && copy->count == tree->count);
    check_tree(copy);
    cursor = avl_iter(tree, NULL, NULL);
    cursor2 = avl_iter(copy, NULL, NULL);
    for (i = 0; i < 257; ++i) {
        assert(avl_iter(NULL, cursor, NULL) == &data[i]);
        assert(avl_iter(NULL, cursor2, NULL) == &data[256 - i]);
    }
    assert(avl_iter(NULL, cursor, NULL) == NULL);
    assert(avl_iter(NULL, cursor2, NULL) == NULL);
    avl_free(copy, 2);
    before = avl_test_live;
    assert(avl_copy_sorted(tree, 9, 1) == tree);
    assert(avl_test_live == before && avl_spare_node == NULL);
    check_tree(tree);
    assert(avl_copy_sorted(tree, 1, 1) == tree);
    check_tree(tree);
    key = 500;
    assert(avl_delete(tree, &key, 2, 0) == NULL);
    assert(avl_removed == NULL && tree->count == 257);
    for (i = 0; i < 257; ++i) {
        j = (i * 131) % 257;
        assert(avl_find(tree, &data[j], 1) == &data[j]);
        assert(avl_delete(tree, &data[j], 2, 0) == NULL);
        check_tree(tree);
    }
    assert(tree->count == 0 && tree->root == NULL);
    if (mode == 1)
        assert(avl_test_pool == 0 && avl_test_heap > 0);
    else
        assert(avl_test_pool > 0 && avl_test_heap > 0); /* cursors use heap */
    avl_free(tree, 2);
    assert(avl_test_live == 0);
}

static void ownership_tests(void)
{
    struct avl_tree *tree;
    struct avl_node *root;
    long *item, i, before;
    avl_test_reset(1);
    tree = (struct avl_tree *)avl_new(1);
    for (i = 0; i < 5; ++i) {
        item = (long *)prof_malloc(sizeof(*item));
        *item = i;
        avl_insert(tree, item, 0);
    }
    i = 2;
    before = avl_test_live;
    assert(avl_delete(tree, &i, 1, 0) == NULL);
    assert(avl_test_live == before - 2); /* payload and node */
    avl_free(tree, 1);
    assert(avl_test_live == 0);
    tree = (struct avl_tree *)avl_new(1);
    avl_insert(tree, &data[1], 0);
    root = tree->root;
    avl_free(tree, 0);
    assert(avl_test_live == 1); /* nodes retained, header freed */
    dsp_free(root);
    assert(avl_test_live == 0);
    avl_free(NULL, 1);
    assert(avl_delete(NULL, &i, 1, 0) == NULL);
    assert(avl_find(NULL, &i, 1) == NULL);
    avl_insert(NULL, &i, 0);
}

static void extended_tests(void)
{
    int i;
    for (i = 0; i < 257; ++i)
        data[i] = i;
    mutation_tests(1);
    mutation_tests(0);
    ownership_tests();
    /* Every generated comparator field, plus nearest interior neighbors. */
    for (i = 0; i < 13; ++i) {
        struct avl_tree *tree;
        long key;
        avl_test_reset(1);
        tree = (struct avl_tree *)avl_new(i);
        avl_insert(tree, &data[1], 0);
        avl_insert(tree, &data[3], 0);
        avl_insert(tree, &data[5], 0);
        check_tree(tree);
        key = 2;
        assert(avl_find(tree, &key, 1) == NULL);
        assert(avl_find(tree, &key, 0) == &data[i == 9 ? 3 : 1]);
        assert(avl_find(tree, &key, 2) == &data[i == 9 ? 1 : 3]);
        avl_free(tree, 2);
        assert(avl_test_live == 0);
    }
    avl_test_reset(1);
}
