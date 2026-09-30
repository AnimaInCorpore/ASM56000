/* avltree.c - generic AVL tree + iterator (SIM56000.EXE 6.3.0, module avltree 0x46a700-0x46b090).
 * Used by the profiler / C debugger.  Nodes hold {height, left, item, right}; a tree is
 * {root, count, cmp_index}.  The comparison functions (avl_cmp_tab) return 0 (item < key),
 * 1 (equal), 2 (item > key) or 3 (no comparison possible, a NULL argument).
 * The original rebalances by unconditional rotation heuristics; kept exactly. */
#include <stdlib.h>
#include "sim56000.h"

#define AVL_STACK 32

struct avl_frame {                     /* iterator stack entry (8 bytes in the original) */
    char state;                        /* 0 new, 1 went left, 2 went right / visited */
    struct avl_node *node;
};
struct avl_iterator {                  /* 0x10c bytes in the original */
    struct avl_frame stack[AVL_STACK]; /* +0 */
    struct avl_frame *sp;              /* +0x100 */
    struct avl_tree *tree;             /* +0x104 */
    void *limit;                       /* +0x108 stop key (NULL = none) */
};

extern struct avl_tree *avl_cur_tree;  /* 0x503c9c */
extern struct avl_node *avl_spare_node;/* 0x503c98 */
extern struct avl_node *avl_removed;   /* 0x503f24 */
struct avl_tree *avl_cur_tree = NULL;
struct avl_node *avl_spare_node = NULL;
struct avl_node *avl_removed = NULL;

typedef long (*avl_cmpfn)(void *, void *);

static long avl_compare(struct avl_node *node, void *key)
{
    simfn f;

    if (node == NULL || key == NULL)
        return 3;
    switch (avl_cur_tree->cmp_index) {
    case 0: f = avl_cmp_tab[0].w0; break;
    case 1: f = avl_cmp_tab[0].w1; break;
    case 2: f = avl_cmp_tab[0].w2; break;
    case 3: f = avl_cmp_tab[0].w3; break;
    case 4: f = avl_cmp_tab[0].w4; break;
    case 5: f = avl_cmp_tab[0].w5; break;
    case 6: f = avl_cmp_tab[0].w6; break;
    case 7: f = avl_cmp_tab[1].w0; break;
    case 8: f = avl_cmp_tab[1].w1; break;
    case 9: f = avl_cmp_tab[1].w2; break;
    case 10: f = avl_cmp_tab[1].w3; break;
    case 11: f = avl_cmp_tab[1].w4; break;
    default: f = avl_cmp_tab[1].w5; break;
    }
    return ((avl_cmpfn)f)(node->item, key);
}

static void *avl_alloc(unsigned long n)
{
    if (prof_ctx->alloc_mode == 1)
        return prof_malloc(n);
    return pool_alloc(prof_ctx->pool, n);
}

static long avl_height(struct avl_node *n)
{
    return n == NULL ? 0 : n->height;
}

void *avl_new(long cmp_type)
{
    struct avl_tree *t = (struct avl_tree *)avl_alloc(sizeof(struct avl_tree));

    t->count = 0;
    t->root = NULL;
    t->cmp_index = cmp_type;
    return t;
}

void avl_free_nodes(void *vnode, long free_mode)
{
    struct avl_node *node = (struct avl_node *)vnode;

    if (node != NULL) {
        avl_free_nodes(node->left, free_mode);
        avl_free_nodes(node->right, free_mode);
        if (free_mode == 1)
            dsp_free(node->item);
        if (free_mode != 0)
            dsp_free(node);
    }
}

void avl_free(void *vtree, long free_mode)
{
    struct avl_tree *tree = (struct avl_tree *)vtree;

    if (tree != NULL) {
        avl_cur_tree = tree;
        avl_free_nodes(tree->root, free_mode);
        dsp_free(tree);
    }
}

/* set the members of a node and recompute its height; returns the node */
void *avl_set_node_r(struct avl_node *node, struct avl_node *left, void *item, struct avl_node *right)
{
    long hl, hr;

    if (node == NULL)
        return NULL;
    node->item = item;
    node->left = left;
    node->right = right;
    hl = avl_height(left);
    hr = avl_height(right);
    if (hr < hl) {
        if (left != NULL) {
            node->height = left->height + 1;
            return node;
        }
    } else if (right != NULL) {
        node->height = right->height + 1;
        return node;
    }
    node->height = 1;
    return node;
}

void avl_set_node(void *node, void *left, void *item, void *right)
{
    avl_set_node_r((struct avl_node *)node, (struct avl_node *)left, item, (struct avl_node *)right);
}

void avl_rebalance(void *vn0, void *vn1, void *vl, void *d1, void *vm, void *d2, void *vr)
{
    struct avl_node *n0 = (struct avl_node *)vn0, *n1 = (struct avl_node *)vn1;
    struct avl_node *l = (struct avl_node *)vl, *m = (struct avl_node *)vm, *r = (struct avl_node *)vr;
    struct avl_node *t;
    void *item;

    if (avl_height(m) > avl_height(l) && avl_height(m) > avl_height(r)) {
        /* double rotation */
        t = (struct avl_node *)avl_set_node_r(n1, l, d1, m->left);
        item = m->item;
        avl_set_node_r(m, m->right, d2, r);
        avl_set_node_r(n0, t, item, m);
        return;
    }
    if (avl_height(l) >= avl_height(r)) {
        t = (struct avl_node *)avl_set_node_r(n1, m, d2, r);
        avl_set_node_r(n0, l, d1, t);
        return;
    }
    t = (struct avl_node *)avl_set_node_r(n1, l, d1, m);
    avl_set_node_r(n0, t, d2, r);
}

void *avl_insert_node(void *vnode, void *item, long replace)
{
    struct avl_node *node = (struct avl_node *)vnode, *n1, *nn;
    long c;

    c = avl_compare(node, item);
    switch (c) {
    case 1:
        if (replace == 0)
            return node;
        /* fall through */
    case 0:
        n1 = (struct avl_node *)avl_insert_node(node->left, item, replace);
        node->left = n1;
        avl_rebalance(node, n1, n1->left, n1->item, n1->right, node->item, node->right);
        return node;
    case 2:
        n1 = (struct avl_node *)avl_insert_node(node->right, item, replace);
        node->right = n1;
        avl_rebalance(node, n1, node->left, node->item, n1->left, n1->item, n1->right);
        return node;
    case 3:
        nn = avl_spare_node;
        if (nn == NULL)
            nn = (struct avl_node *)avl_alloc(sizeof(struct avl_node));
        avl_spare_node = NULL;
        avl_cur_tree->count++;
        avl_set_node_r(nn, NULL, item, NULL);
        return nn;
    default:
        return node;
    }
}

void avl_insert(void *vtree, void *item, long replace)
{
    struct avl_tree *tree = (struct avl_tree *)vtree;

    if (tree != NULL) {
        avl_cur_tree = tree;
        tree->root = (struct avl_node *)avl_insert_node(tree->root, item, replace);
    }
}

void *avl_delete_node(void *vnode, void *key)
{
    struct avl_node *node = (struct avl_node *)vnode, *x, *r, *l;
    struct avl_node *ln, *rn;
    void *item, *tmp;
    long c;

    c = avl_compare(node, key);
    if (c == 1) {
        if (node->left != NULL) {
            x = node->left;
            while (x->right != NULL)
                x = x->right;
            tmp = node->item; node->item = x->item; x->item = tmp;
            c = 0;
        } else if (node->right == NULL) {
            avl_cur_tree->count--;
            avl_removed = node;
            return NULL;
        } else {
            x = node->right;
            while (x->left != NULL)
                x = x->left;
            tmp = node->item; node->item = x->item; x->item = tmp;
            c = 2;
        }
    }
    if (c == 0) {
        r = node->right;
        item = node->item;
        ln = (struct avl_node *)avl_delete_node(node->left, key);
        avl_set_node_r(node, ln, item, r);
        r = node->right;
        if (r == NULL)
            return node;
        avl_rebalance(node, r, node->left, node->item, r->left, r->item, r->right);
        return node;
    }
    if (c == 2) {
        rn = (struct avl_node *)avl_delete_node(node->right, key);
        avl_set_node_r(node, node->left, node->item, rn);
        l = node->left;
        if (l == NULL)
            return node;
        avl_rebalance(node, l, l->left, l->item, l->right, node->item, node->right);
        return node;
    }
    return NULL;
}

/* returns the item of the last removed node when free_mode is 0 */
void *avl_delete(void *vtree, void *key, long free_mode, long repeat)
{
    struct avl_tree *tree = (struct avl_tree *)vtree;
    void *result = NULL;

    if (tree == NULL)
        return NULL;
    avl_cur_tree = tree;
    do {
        avl_removed = NULL;
        tree->root = (struct avl_node *)avl_delete_node(tree->root, key);
        if (free_mode == 0 && avl_removed != NULL)
            result = avl_removed->item;
        if (avl_removed != NULL) {
            if (free_mode == 1)
                dsp_free(avl_removed->item);
            if (free_mode != 0)
                dsp_free(avl_removed);
        }
    } while (repeat == 1);
    return result;
}

void *avl_find(void *vtree, void *key, long mode)
{
    struct avl_tree *tree = (struct avl_tree *)vtree;
    struct avl_node *node, *best = NULL;
    long c;

    node = tree == NULL ? NULL : tree->root;
    avl_cur_tree = tree;
    while (node != NULL) {
        c = avl_compare(node, key);
        if (c == 1)
            return node->item;
        if (c != mode)
            best = node;
        node = c == 0 ? node->left : node->right;
    }
    if (mode != 1 && best != NULL)
        return best->item;
    return NULL;
}

void avl_walk_node(void *vnode, void (*fn)(void *), long order)
{
    struct avl_node *node = (struct avl_node *)vnode;
    int fwd;

    if (node == NULL)
        return;
    fwd = (order == 2 || order == 0 || order == 4);
    if (order == 2 || order == 3)
        fn(node->item);
    avl_walk_node(fwd ? node->left : node->right, fn, order);
    if (order == 0 || order == 1)
        fn(node->item);
    avl_walk_node(fwd ? node->right : node->left, fn, order);
    if (order == 4 || order == 5)
        fn(node->item);
}

void avl_walk(void *vtree, void (*fn)(void *), long order, long bracket)
{
    struct avl_tree *tree = (struct avl_tree *)vtree;

    if (tree != NULL) {
        if (bracket == 1 || bracket == 3)
            fn(NULL);
        avl_walk_node(tree->root, fn, order);
        if (bracket == 2 || bracket == 3)
            fn(NULL);
    }
}

/* avl_iter(tree, start, limit) creates an iterator positioned at the first item that is not
 * below `start`; avl_iter(NULL, iterator, NULL) returns the next item (0 at the end, freeing
 * the iterator).  The iterator is returned as a char * (void * in disguise). */
char *avl_iter(void *vtree, char *viter, void *key)
{
    struct avl_tree *tree = (struct avl_tree *)vtree;
    struct avl_iterator *it;
    struct avl_frame *best, *sp;
    struct avl_node *node, *n;
    long c;

    if (tree != NULL) {
        if (tree->root == NULL)
            return NULL;
        it = (struct avl_iterator *)prof_malloc(sizeof(struct avl_iterator));
        avl_cur_tree = tree;
        it->sp = it->stack;
        best = NULL;
        node = tree->root;
        while (node != NULL) {
            c = avl_compare(node, viter);
            it->sp->node = node;
            it->sp->state = c == 2 ? 2 : 1;
            if (c != 2)
                best = it->sp;
            node = c == 2 ? node->right : node->left;
            it->sp++;
        }
        if (best == NULL) {
            dsp_free(it);
            return NULL;
        }
        it->sp = best;
        it->limit = key;
        it->tree = tree;
        return (char *)it;
    }
    it = (struct avl_iterator *)viter;
    if (it == NULL)
        return NULL;
    avl_cur_tree = it->tree;
    while (it->sp >= it->stack) {
        sp = it->sp;
        n = sp->node;
        if (n == NULL) {
            it->sp--;
        } else {
            sp->state++;
            sp = it->sp;
            if (sp->state == 1) {
                it->sp++;
                it->sp->state = 0;
                it->sp->node = n->left;
            } else if (sp->state == 2) {
                it->sp++;
                it->sp->state = 0;
                it->sp->node = n->right;
                if (n == NULL || it->limit == NULL)
                    c = 3;
                else {
                    avl_cur_tree = it->tree;
                    c = avl_compare(n, it->limit);
                }
                if (c != 0)
                    return (char *)n->item;
                break;
            } else if (sp->state == 3) {
                it->sp--;
            }
        }
        if (it->sp < it->stack) {
            dsp_free(it);
            return NULL;
        }
    }
    dsp_free(it);
    return NULL;
}

void *avl_copy_sorted(void *vtree, long cmp_type, long resort)
{
    struct avl_tree *tree = (struct avl_tree *)vtree;
    struct avl_tree tmp, *nt;
    char *it;
    void *item;

    if (resort == 1) {
        tmp.root = NULL;
        tmp.count = 0;
        tmp.cmp_index = cmp_type;
        while (tree->root != NULL) {
            item = avl_delete(tree, tree->root->item, 0, 0);
            avl_spare_node = avl_removed;
            avl_insert(&tmp, item, 1);
        }
        tree->root = tmp.root;
        tree->count = tmp.count;
        tree->cmp_index = tmp.cmp_index;
        return tree;
    }
    nt = (struct avl_tree *)avl_new(cmp_type);
    it = avl_iter(tree, NULL, NULL);
    item = avl_iter(NULL, it, NULL);
    while (item != NULL) {
        avl_insert(nt, item, 1);
        item = avl_iter(NULL, it, NULL);
    }
    return nt;
}
