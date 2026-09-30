/* mdisk.c - memory disk emulation: sparse memory with disk spill ("m_gdisk"/"m_pdisk")
 * (SIM56000.EXE 6.3.0, module mdisk 0x458060-0x458c10).
 * Memory regions flagged REGION_MDISK keep their words in a circular list of nodes; a node
 * covers [start, next->start) and is a constant fill (MD_CONSTANT), a resident block of
 * 256 words (MD_RESIDENT) or a block swapped out to "<type><dev>.MEM" (MD_SWAPPED).
 * The sentinel node has start 0.  The swap file is private, so its block size is
 * 256 * sizeof(uword) here instead of the original 0x400 bytes. */
#include <stdio.h>
#include <stdlib.h>
#include "sim56000.h"

#define BLOCK_BYTES (MDISK_BLOCK_WORDS * (long)sizeof(uword))

static struct mdisk_list *dev_list(long i)
{
    return &cur_dev->mem[i].md;
}

static int region_flagged(long i)
{
    return (cur_dtype->map[i].attr & REGION_MDISK) != 0;
}

static void select_dev(long dev)
{
    cur_dev = dev_tab[dev];
    cur_dtype = chiptype_tab[cur_dev->type];
}

void mdisk_save_all(long dev, void *fp)
{
    long i;
    long ok = 1;

    select_dev(dev);
    for (i = 0; i < cur_dtype->n_map; i++) {
        if (ok == 0)
            return;
        if (region_flagged(i))
            ok = mdisk_save_space(dev_list(i), fp);
    }
}

void mdisk_close(long dev)
{
    long i;
    struct mdisk_slot *p, *next;

    select_dev(dev);
    for (i = 0; i < cur_dtype->n_map; i++) {
        if (region_flagged(i))
            mdisk_clear_list(dev_list(i));
    }
    if (cur_dev->swapfile != NULL) {
        fclose(cur_dev->swapfile);
        cur_dev->swapfile = NULL;
        for (p = cur_dev->free_slots; p != NULL; p = next) {
            next = p->next;
            dsp_free(p);
        }
        cur_dev->free_slots = NULL;
    }
}

long mdisk_init(void)
{
    long i;
    long ok = 1;
    struct mdisk_node *n;

    for (i = 0; i < cur_dtype->n_map; i++) {
        if (ok == 0)
            break;
        if (region_flagged(i)) {
            n = (struct mdisk_node *)dsp_alloc(sizeof(struct mdisk_node), 1);
            if (n == NULL)
                ok = 0;
            else {
                ok = 1;
                dev_list(i)->prev_cursor = n;
                dev_list(i)->cursor = n;
                n->prev = n;
                n->next = n;
                n->state = MD_CONSTANT;
            }
        }
    }
    cur_dev->swapfile = NULL;
    cur_dev->free_slots = NULL;
    return ok;
}

void mdisk_load_all(long dev, void *fp)
{
    long i;
    long ok = 1;

    select_dev(dev);
    for (i = 0; i < cur_dtype->n_map; i++) {
        if (ok == 0)
            return;
        if (region_flagged(i))
            ok = mdisk_load_space(dev_list(i), fp);
    }
}

/* the node whose range contains addr */
void *mdisk_find_node(void *vlist, unsigned long addr)
{
    struct mdisk_list *list = (struct mdisk_list *)vlist;
    struct mdisk_node *p = list->cursor;

    while (addr < p->start)
        p = p->prev;
    while (p->next != NULL && p->next->start != 0 && addr >= p->next->start)
        p = p->next;
    return p;
}

char *mdisk_page_in(void *vnode)
{
    struct mdisk_node *node = (struct mdisk_node *)vnode;
    uword *buffer;
    struct mdisk_slot *slot;
    long offset;

    buffer = (uword *)dsp_alloc(BLOCK_BYTES, 0);
    if (buffer != NULL) {
        offset = node->u.file_off;
        if (fseek(cur_dev->swapfile, offset, SEEK_SET) != 0) {
            screen_write(text_rows, 0, "Error seeking in m_gdisk", 1);
            fclose(cur_dev->swapfile);
            exit(1);
        }
        if (fread(buffer, (size_t)BLOCK_BYTES, 1, cur_dev->swapfile) != 1) {
            screen_write(text_rows, 0, "Error reading in m_gdisk.", 1);
            fclose(cur_dev->swapfile);
            exit(1);
        }
        slot = (struct mdisk_slot *)dsp_alloc(sizeof(struct mdisk_slot), 0);
        if (slot != NULL) {
            slot->next = cur_dev->free_slots;
            slot->offset = offset;
            cur_dev->free_slots = slot;
        }
        node->state = MD_RESIDENT;
        node->u.block = buffer;
    }
    return (char *)buffer;
}

long mdisk_read(long dev, unsigned long space, unsigned long addr, unsigned long *pval)
{
    long idx = memmap_find(space, addr);
    struct mdisk_list *list;
    struct mdisk_node *node;

    select_dev(dev);
    list = dev_list(idx);
    if (!region_flagged(idx))
        return 0;
    node = (struct mdisk_node *)mdisk_find_node(list, addr);
    if (node->state == MD_CONSTANT) {
        *pval = node->u.fill;
        return 1;
    }
    if (node->state == MD_SWAPPED && mdisk_page_in(node) == NULL)
        return 0;
    *pval = node->u.block[addr & 0xff];
    if (list->cursor != node) {
        list->prev_cursor = list->cursor;
        list->cursor = node;
    }
    return 1;
}

void mdisk_write(long dev, unsigned long space, unsigned long addr, unsigned long val)
{
    long idx = memmap_find(space, addr);
    struct mdisk_list *list;
    struct mdisk_node *node, *target, *n;
    uword *block;
    unsigned long fill, base;
    long i;

    cur_dev = dev_tab[dev];
    list = dev_list(idx);
    if (!region_flagged(idx))
        return;
    node = (struct mdisk_node *)mdisk_find_node(list, addr);
    target = node;
    if (node->state == MD_CONSTANT) {
        fill = node->u.fill;
        if (val == fill)
            return;
        block = (uword *)dsp_alloc(BLOCK_BYTES, 0);
        if (block == NULL)
            return;
        for (i = 0; i < MDISK_BLOCK_WORDS; i++)
            block[i] = fill;
        base = addr & 0xffffff00UL;
        if (((base + 0x100UL) & MASK32) != node->next->start) {
            n = (struct mdisk_node *)dsp_alloc(sizeof(struct mdisk_node), 0);
            if (n == NULL)
                return;
            n->start = (base + 0x100UL) & MASK32;
            n->state = MD_CONSTANT;
            n->u.fill = fill;
            n->next = node->next;
            n->prev = node;
            node->next->prev = n;
            node->next = n;
        }
        if (base != node->start) {
            n = (struct mdisk_node *)dsp_alloc(sizeof(struct mdisk_node), 0);
            if (n == NULL)
                return;
            n->next = node->next;
            n->prev = node;
            n->start = base;
            node->next->prev = n;
            node->next = n;
            target = n;
        }
        target->state = MD_RESIDENT;
        target->u.block = block;
    } else if (node->state == MD_SWAPPED && mdisk_page_in(node) == NULL)
        return;
    target->u.block[addr & 0xff] = val;
    if (list->cursor != target) {
        list->prev_cursor = list->cursor;
        list->cursor = target;
    }
}

void mdisk_clear_list(void *vlist)
{
    struct mdisk_list *list = (struct mdisk_list *)vlist;
    struct mdisk_node *keep = list->cursor;
    struct mdisk_node *p = keep->next, *next;

    while (p != keep) {
        next = p->next;
        if (p->state == MD_RESIDENT)
            dsp_free(p->u.block);
        dsp_free(p);
        p = next;
    }
    if (p->state == MD_RESIDENT)
        dsp_free(p->u.block);
    p->next = p;
    p->prev = p;                       /* the original leaves prev dangling */
    p->start = 0;
    p->u.fill = 0;
    p->state = MD_CONSTANT;
    list->prev_cursor = p;
}

long mdisk_save_space(void *vlist, void *vfp)
{
    struct mdisk_list *list = (struct mdisk_list *)vlist;
    FILE *fp = (FILE *)vfp;
    struct mdisk_node *first = list->cursor, *prev, *node, *p;
    uword *block;
    long count = 1, i;
    unsigned long j;

    prev = first;
    node = first;
    for (p = first->next; p != first; p = p->next) {
        if (prev->start == 0)
            node = prev;
        count++;
        prev = p;
    }
    fprintf(fp, "\n%ld", count);
    for (; count != 0; count--) {
        fprintf(fp, "\n%lx", node->start);
        if (node->state == MD_SWAPPED)
            block = (uword *)mdisk_page_in(node);
        else if (node->state == MD_RESIDENT)
            block = node->u.block;
        else
            block = NULL;
        fprintf(fp, "\n%d\n", (int)node->state);
        if (block == NULL)
            fprintf(fp, "%lx ", node->u.fill);
        else {
            for (j = 0; j < (unsigned long)MDISK_BLOCK_WORDS; j++) {
                if (j != 0 && (j & 7) == 0)
                    fprintf(fp, "\n");
                fprintf(fp, "%lx ", (unsigned long)block[j]);
            }
        }
        node = node->next;
    }
    i = fprintf(fp, "\n");
    return i != -1;
}

long mdisk_load_space(void *vlist, void *vfp)
{
    struct mdisk_list *list = (struct mdisk_list *)vlist;
    FILE *fp = (FILE *)vfp;
    struct mdisk_node *p, *n;
    long count = 0, i, result;
    int state;
    unsigned long v;

    mdisk_clear_list(list);
    result = fscanf(fp, "%ld ", &count);
    p = list->cursor;
    if (count < 1)
        return result;
    do {
        fscanf(fp, "%lx ", &p->start);
        state = 0;
        fscanf(fp, "%d ", &state);
        p->state = state;
        if (p->state == MD_RESIDENT) {
            p->u.block = (uword *)dsp_alloc(BLOCK_BYTES, 0);
            if (p->u.block == NULL)
                return 0;
            for (i = 0; i < MDISK_BLOCK_WORDS; i++) {
                v = 0;
                fscanf(fp, "%lx ", &v);
                p->u.block[i] = v;
            }
        } else
            fscanf(fp, "%lx ", &p->u.fill);
        if (count > 1) {
            n = (struct mdisk_node *)dsp_alloc(sizeof(struct mdisk_node), 0);
            if (n == NULL)
                return 0;
            n->prev = p;
            n->next = p->next;
            p->next->prev = n;
            p->next = n;
            p = n;
        }
        count--;
    } while (count > 0);
    return result;
}

void mdisk_spill_node(void *vnode)
{
    struct mdisk_node *node = (struct mdisk_node *)vnode;
    struct mdisk_slot *p = cur_dev->free_slots;
    long offset = p != NULL ? p->offset : 0;
    char name[84], path[84];

    if (cur_dev->swapfile == NULL) {
        sprintf(name, "%s%d", cur_dtype->mem_name, (int)cur_dev->number);
        path_combine(cur_dev->workdir, name, ".MEM", path);
        cur_dev->swapfile = fopen(path, "w+b");
        if (cur_dev->swapfile == NULL) {
            screen_write(text_rows, 0, "Error opening in m_pdisk", 1);
            exit(1);
        }
    }
    if (fseek(cur_dev->swapfile, offset, p != NULL ? SEEK_SET : SEEK_END) != 0) {
        screen_write(text_rows, 0, "Error seeking in m_pdisk", 1);
        exit(1);
    }
    if (p == NULL)
        offset = ftell(cur_dev->swapfile);
    if (fwrite(node->u.block, (size_t)BLOCK_BYTES, 1, cur_dev->swapfile) != 1) {
        screen_write(text_rows, 0, "Error writing block in m_pdisk.", 1);
        exit(1);
    }
    node->state = MD_SWAPPED;
    dsp_free(node->u.block);
    node->u.file_off = offset;
    if (p != NULL) {
        cur_dev->free_slots = p->next;
        dsp_free(p);
    }
}

long mdisk_spill_lru(void *vlist)
{
    struct mdisk_list *list = (struct mdisk_list *)vlist;
    struct mdisk_node *end = list->cursor;
    struct mdisk_node *va = end->prev;

    if (va == end)
        return 0;
    while (va->state != MD_RESIDENT || va == list->prev_cursor) {
        va = va->prev;
        if (va == end)
            return 0;
    }
    mdisk_spill_node(va);
    return 1;
}

long mdisk_spill_mru(void *vlist)
{
    struct mdisk_list *list = (struct mdisk_list *)vlist;
    struct mdisk_node *va = list->prev_cursor;

    if (va->state != MD_RESIDENT) {
        va = list->cursor;
        if (va->state != MD_RESIDENT)
            return 0;
    }
    mdisk_spill_node(va);
    return 1;
}

/* low-memory handler: swap out one resident block of any device; returns 1 if memory was freed */
long mdisk_spill(void)
{
    struct dev_inst *saved = cur_dev;
    long found = 0, d, i, pass;

    for (pass = 0; pass < 2 && !found; pass++) {
        for (d = 0; d < max_devices && !found; d++) {
            cur_dev = dev_tab[d];
            if (cur_dev == NULL)
                continue;
            cur_dtype = chiptype_tab[cur_dev->type];
            for (i = 0; i < cur_dtype->n_map && !found; i++) {
                if (region_flagged(i)) {
                    if (pass == 0)
                        found = mdisk_spill_lru(dev_list(i)) != 0;
                    else
                        found = mdisk_spill_mru(dev_list(i)) != 0;
                }
            }
        }
    }
    cur_dev = saved;
    cur_dtype = chiptype_tab[saved->type];
    return found;
}
