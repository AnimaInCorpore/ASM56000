/*
 * ASM56000 symbol-table core.
 *
 * The original program uses four 1009-entry hash tables and a compact 0x60
 * byte symbol record.  This translation keeps the same lookup and value-word
 * conventions while using ordinary C structures so it remains buildable on a
 * hosted compiler during the reconstruction.
 */
#include <string.h>
#include <ctype.h>

#include "asm56000.h"

#define ASM56000_SYM_BUCKETS 1009

#define SYM_SET       0x00000010UL
#define SYM_LOCAL     0x00000020UL
#define SYM_PRIVATE   0x00000040UL
#define SYM_INTEGER   0x00000100UL
#define SYM_FLOAT     0x00000200UL
#define SYM_LONG      0x00000800UL
#define SYM_RELOC     0x00001000UL
#define ASM56000_MAX_SYMBOLS 4096

struct asm56000_ref {
    int type;
    unsigned long line;
    struct asm56000_ref *next;
};

struct asm56000_symbol {
    char *name;
    unsigned long value[3];
    unsigned long flags;
    unsigned long space;
    unsigned long map;
    unsigned long counter;
    unsigned long emi;
    unsigned long buffer;
    unsigned long overlay;
    unsigned long coff_scn;
    unsigned long rel_sec;
    unsigned long rel_cnt;
    unsigned long obj_seq;
    unsigned long obj_scn;
    unsigned long definition_line;
    int duplicate_definition;
    int sectioned;
    int global;
    unsigned long sdi_cnt;
    unsigned long sdi_cnt2;
    void *section;
    void *counter_section;
    void *sdi_group;
    void *sdi_mark;
    struct asm56000_ref *refs;
    void *dbg_sym;
    void *dbg_aux;
    struct asm56000_symbol *next;
};

struct asm56000_ext {
    char *name;
    unsigned long flags;
    void *section;
    struct asm56000_ext *prev;
    struct asm56000_ext *next;
};

struct asm56000_local_block {
    unsigned long number;
    struct asm56000_symbol *first;
    struct asm56000_local_block *next;
};

struct pending_ref {
    char *name;
    unsigned long line;
    struct pending_ref *next;
};

static struct asm56000_symbol *SymHash[ASM56000_SYM_BUCKETS];
static struct asm56000_ext *ExtHash[ASM56000_SYM_BUCKETS];
static struct asm56000_symbol *SymInsertPoint;
static struct asm56000_ext *ExtInsertPoint;
static struct asm56000_local_block *LocalBlocks;
static struct asm56000_local_block *CurrentLocalBlock;
static unsigned long LocalBlockNumber;
static unsigned long SymbolCount;
static struct asm56000_symbol *SymbolOrder[ASM56000_MAX_SYMBOLS];
static unsigned long SymbolOrderCount;
static char *PrivateNames[256];
static unsigned long PrivateNameCount;
static struct pending_ref *PendingRefs;
extern void *CurrentSection;

/* These are owned by the pass driver (globals.c during reconstruction). */
extern char OptIC;
extern char OptXR;
extern char OptUR;
extern int AbsoluteMode;
extern unsigned long LineNo;
extern char *MnemField;

static int operation_is(char *name)
{
    char *p;

    if (MnemField == (char *)0)
        return 0;
    p = MnemField;
    while (*p != '\0' && *name != '\0') {
        if (tolower((unsigned char)*p++) !=
            tolower((unsigned char)*name++))
            return 0;
    }
    return *p == '\0' && *name == '\0';
}

static void add_ref_at(struct asm56000_symbol *sym, int type,
                       unsigned long line)
{
    struct asm56000_ref *ref;

    if (sym == (struct asm56000_symbol *)0)
        return;
    ref = (struct asm56000_ref *)xmalloc(
        (unsigned long)sizeof(struct asm56000_ref));
    ref->type = type;
    ref->line = line;
    ref->next = sym->refs;
    sym->refs = ref;
}

static void add_ref(struct asm56000_symbol *sym, int type)
{
    add_ref_at(sym, type, LineNo);
}

static char *copy_name(char *name)
{
    char *copy;
    char *lower;
    unsigned long n;

    if (name == (char *)0)
        return (char *)0;
    lower = OptIC ? str_lower_copy(name) : name;
    n = (unsigned long)strlen(lower);
    copy = (char *)xmalloc(n + 1UL);
    strcpy(copy, lower);
    return copy;
}

static int private_name_equal(char *a, char *b)
{
    unsigned long i;

    if (!OptIC)
        return strcmp(a, b) == 0;
    for (i = 0UL; a[i] != '\0' || b[i] != '\0'; ++i)
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i]))
            return 0;
    return 1;
}

static int private_name_known(char *name)
{
    unsigned long i;

    for (i = 0UL; i < PrivateNameCount; ++i)
        if (private_name_equal(PrivateNames[i], name))
            return 1;
    return 0;
}

void sym_hide_name(char *name)
{
    unsigned long bucket;
    struct asm56000_symbol *sym;

    if (name == (char *)0 || *name == '\0')
        return;
    if (!private_name_known(name) &&
        PrivateNameCount < sizeof(PrivateNames) / sizeof(PrivateNames[0]))
        PrivateNames[PrivateNameCount++] = copy_name(name);
    bucket = hash_name(name);
    sym = SymHash[bucket];
    while (sym != (struct asm56000_symbol *)0) {
        if (private_name_equal(sym->name, name))
            sym->flags |= SYM_PRIVATE;
        sym = sym->next;
    }
}

static char *lookup_name(char *name, int *is_local)
{
    if (is_local != (int *)0)
        *is_local = 0;
    if (name == (char *)0)
        return (char *)0;
    if (*name == '_') {
        if (is_local != (int *)0)
            *is_local = 1;
        ++name;
    }
    return OptIC ? str_lower_copy(name) : name;
}

static struct asm56000_symbol *find_symbol(char *name, int local_only)
{
    struct asm56000_symbol *sym;
    unsigned long bucket;

    bucket = hash_name(name);
    sym = SymHash[bucket];
    SymInsertPoint = (struct asm56000_symbol *)0;
    while (sym != (struct asm56000_symbol *)0) {
        if (strcmp(sym->name, name) == 0 &&
            (!local_only || (sym->flags & SYM_LOCAL) != 0UL))
            return sym;
        SymInsertPoint = sym;
        sym = sym->next;
    }
    return (struct asm56000_symbol *)0;
}

static struct asm56000_symbol *find_local_for_line(char *name)
{
    struct asm56000_symbol *sym;
    struct asm56000_symbol *past;
    struct asm56000_symbol *future;
    unsigned long bucket;

    bucket = hash_name(name);
    past = (struct asm56000_symbol *)0;
    future = (struct asm56000_symbol *)0;
    sym = SymHash[bucket];
    while (sym != (struct asm56000_symbol *)0) {
        if (strcmp(sym->name, name) == 0 &&
            (sym->flags & SYM_LOCAL) != 0UL) {
            if (sym->definition_line >= LineNo &&
                (future == (struct asm56000_symbol *)0 ||
                 sym->definition_line < future->definition_line))
                future = sym;
            if (sym->definition_line <= LineNo &&
                (past == (struct asm56000_symbol *)0 ||
                 sym->definition_line > past->definition_line))
                past = sym;
        }
        sym = sym->next;
    }
    return past != (struct asm56000_symbol *)0 ? past : future;
}

static void copy_value(struct asm56000_symbol *sym, void *value)
{
    unsigned long *v;
    unsigned long local;
    unsigned long private;

    v = (unsigned long *)value;
    if (value == (void *)0)
        return;
    local = sym->flags & SYM_LOCAL;
    private = sym->flags & SYM_PRIVATE;
    sym->value[0] = v[ASM56000_EXPR_W0 / 4];
    sym->value[1] = v[ASM56000_EXPR_W1 / 4];
    sym->value[2] = v[ASM56000_EXPR_W2 / 4];
    sym->flags = local | private | v[ASM56000_EXPR_W6 / 4] |
                 v[ASM56000_EXPR_W4 / 4];
    sym->space = v[ASM56000_EXPR_W7 / 4];
    sym->map = v[ASM56000_EXPR_W8 / 4];
    sym->counter = v[ASM56000_EXPR_W9 / 4];
    sym->emi = v[ASM56000_EXPR_W10 / 4];
    sym->buffer = v[ASM56000_EXPR_W17 / 4];
    sym->overlay = v[ASM56000_EXPR_W18 / 4];
    sym->sdi_cnt = v[ASM56000_EXPR_W19 / 4];
    sym->sdi_cnt2 = v[ASM56000_EXPR_W20 / 4];
    sym->coff_scn = v[ASM56000_EXPR_W21 / 4];
    sym->rel_sec = v[ASM56000_EXPR_W15 / 4];
    sym->rel_cnt = v[ASM56000_EXPR_W16 / 4];
}

void symtab_init(void)
{
    unsigned long i;

    for (i = 0UL; i < ASM56000_SYM_BUCKETS; ++i) {
        SymHash[i] = (struct asm56000_symbol *)0;
        ExtHash[i] = (struct asm56000_ext *)0;
    }
    SymInsertPoint = (struct asm56000_symbol *)0;
    ExtInsertPoint = (struct asm56000_ext *)0;
    LocalBlocks = (struct asm56000_local_block *)0;
    CurrentLocalBlock = (struct asm56000_local_block *)0;
    LocalBlockNumber = 0UL;
    SymbolCount = 0UL;
    SymbolOrderCount = 0UL;
    PrivateNameCount = 0UL;
    PendingRefs = (struct pending_ref *)0;
}

int sym_set_value(void *sym_ptr, void *value)
{
    struct asm56000_symbol *sym;

    sym = (struct asm56000_symbol *)sym_ptr;
    if (sym == (struct asm56000_symbol *)0 ||
        (sym->flags & SYM_SET) == 0UL)
        return 0;
    copy_value(sym, value);
    sym->flags |= SYM_SET;
    if (Pass == 1UL && operation_is("set")) {
        sym->definition_line = LineNo;
        add_ref(sym, 2);
    }
    return 1;
}

int sym_define(char *name, void *value)
{
    struct asm56000_symbol *sym;
    struct asm56000_symbol *new_sym;
    char *key;
    int local;
    unsigned long bucket;

    key = lookup_name(name, &local);
    if (key == (char *)0 || *key == '\0')
        return 0;
    sym = local && Pass == 2UL ? find_local_for_line(key) :
          find_symbol(key, local);
    if (sym != (struct asm56000_symbol *)0 && !(local && Pass == 1UL)) {
        if (Pass == 2UL && sym->duplicate_definition &&
            !operation_is("equ") && !operation_is("set")) {
            err_s("Symbol redefined", name);
            return 0;
        }
        if ((sym->flags & SYM_SET) != 0UL) {
            if (Pass == 2UL && operation_is("equ") &&
                sym->definition_line != LineNo) {
                CurInstrFieldMsg = Op1Field;
                err_s("Symbol already used as SET symbol", name);
                return 0;
            }
            return sym_set_value(sym, value);
        }
        if (Pass == 2UL && sym->definition_line != LineNo && !local) {
            if (operation_is("set")) {
                CurInstrFieldMsg = Op1Field;
                err_s("Symbol cannot be set to new value", name);
                copy_value(sym, value);
            } else
                err_s("Symbol redefined", name);
            return 0;
        }
        if (Pass == 1UL) {
            if (!operation_is("equ") && !operation_is("set"))
                sym->duplicate_definition = 1;
            return 0;
        }
        copy_value(sym, value);
        if (Pass == 2UL) {
            ObjSeq += 64UL;
            sym->obj_seq = ObjSeq;
            sym->obj_scn = 0UL;
            obj_symbol_defined(sym->obj_seq, sym->flags, sym->space,
                               sym->global);
        }
        return 1;
    }
    if (Pass == 2UL)
        return 0;

    new_sym = (struct asm56000_symbol *)xmalloc(
        (unsigned long)sizeof(struct asm56000_symbol));
    memset(new_sym, 0, sizeof(struct asm56000_symbol));
    new_sym->name = copy_name(key);
    copy_value(new_sym, value);
    if (local)
        new_sym->flags |= SYM_LOCAL;
    if (private_name_known(new_sym->name))
        new_sym->flags |= SYM_PRIVATE;
    new_sym->section = CurrentSection;
    new_sym->definition_line = LineNo;
    new_sym->sectioned = !sec_current_is_global();
    new_sym->global = sec_is_global(new_sym->name) ||
                      sec_current_section_global();
    bucket = hash_name(new_sym->name);
    if (SymInsertPoint != (struct asm56000_symbol *)0) {
        new_sym->next = SymInsertPoint->next;
        SymInsertPoint->next = new_sym;
    } else {
        new_sym->next = SymHash[bucket];
        SymHash[bucket] = new_sym;
    }
    ++SymbolCount;
    if (SymbolOrderCount < ASM56000_MAX_SYMBOLS)
        SymbolOrder[SymbolOrderCount++] = new_sym;
    if (local)
        sym_new_local_block((void *)new_sym);
    add_ref(new_sym, 2);
    {
        struct pending_ref *pending;
        struct pending_ref *previous;
        struct pending_ref *next;

        previous = (struct pending_ref *)0;
        pending = PendingRefs;
        while (pending != (struct pending_ref *)0) {
            next = pending->next;
            if (strcmp(pending->name, new_sym->name) == 0) {
                add_ref_at(new_sym, 1, pending->line);
                if (previous == (struct pending_ref *)0)
                    PendingRefs = next;
                else
                    previous->next = next;
                xfree((void *)pending->name);
                xfree((void *)pending);
            } else
                previous = pending;
            pending = next;
        }
    }
    return 1;
}

int sym_undef(char *name)
{
    char *key;
    struct asm56000_symbol *sym;
    struct asm56000_symbol *prev;
    unsigned long bucket;
    int local;

    key = lookup_name(name, &local);
    if (key == (char *)0 || *key == '\0')
        return 0;
    bucket = hash_name(key);
    prev = (struct asm56000_symbol *)0;
    sym = SymHash[bucket];
    while (sym != (struct asm56000_symbol *)0) {
        if (strcmp(sym->name, key) == 0 &&
            (!local || (sym->flags & SYM_LOCAL) != 0UL)) {
            if (prev == (struct asm56000_symbol *)0)
                SymHash[bucket] = sym->next;
            else
                prev->next = sym->next;
            --SymbolCount;
            return 1;
        }
        prev = sym;
        sym = sym->next;
    }
    return 0;
}

void *sym_search(char *name, int reftype, int is_local)
{
    char *key;
    int local;

    (void)reftype;
    key = lookup_name(name, &local);
    if (key == (char *)0)
        return (void *)0;
    if (is_local)
        local = 1;
    if (is_local)
        return (void *)find_local_for_line(key);
    return (void *)find_symbol(key, local);
}

void *sym_lookup_local(char *name, int reftype)
{
    (void)reftype;
    return sym_search(name, reftype, 1);
}

void *sym_lookup(char *name, int reftype)
{
    int local;
    char *key;

    key = lookup_name(name, &local);
    if (key == (char *)0)
        return (void *)0;
    if (local)
        return sym_lookup_local(name, reftype);
    {
        struct asm56000_symbol *sym;

        sym = find_symbol(key, 0);
        if (sym != (struct asm56000_symbol *)0 &&
            sym->section != CurrentSection && sym->sectioned &&
            !sym->global)
            return (void *)0;
        return (void *)sym;
    }
}

int sym_is_sectioned_name(char *name)
{
    char *key;
    struct asm56000_symbol *sym;
    int local;

    key = lookup_name(name, &local);
    if (key == (char *)0 || local)
        return 0;
    sym = find_symbol(key, 0);
    return sym != (struct asm56000_symbol *)0 && sym->sectioned;
}

int sym_duplicate_name(char *name)
{
    char *key;
    int local;
    struct asm56000_symbol *sym;

    key = lookup_name(name, &local);
    if (key == (char *)0)
        return 0;
    sym = find_symbol(key, local);
    return sym != (struct asm56000_symbol *)0 &&
           sym->duplicate_definition != 0;
}

unsigned long sym_definition_line(char *name)
{
    char *key;
    int local;
    struct asm56000_symbol *sym;

    key = lookup_name(name, &local);
    if (key == (char *)0)
        return 0UL;
    sym = find_symbol(key, local);
    return sym == (struct asm56000_symbol *)0 ? 0UL : sym->definition_line;
}

void sym_add_ref(void *sym_ptr, int reftype)
{
    struct asm56000_symbol *sym;

    if (reftype == 0 || sym_ptr == (void *)0)
        return;
    sym = (struct asm56000_symbol *)sym_ptr;
    add_ref(sym, reftype);
}

void sym_note_unresolved(char *name)
{
    struct pending_ref *pending;
    char *key;
    int local;

    if (Pass != 1UL || name == (char *)0 || *name == '\0')
        return;
    key = lookup_name(name, &local);
    if (key == (char *)0 || *key == '\0')
        return;
    pending = (struct pending_ref *)xmalloc(
        (unsigned long)sizeof(*pending));
    pending->name = copy_name(key);
    pending->line = LineNo;
    pending->next = PendingRefs;
    PendingRefs = pending;
}

int sym_object_references(unsigned long index, unsigned long *lines,
                          int *definitions, unsigned long max_lines,
                          unsigned long *count)
{
    unsigned long i;
    unsigned long seen;
    unsigned long n;
    struct asm56000_symbol *sym;
    struct asm56000_ref *ref;

    seen = 0UL;
    for (i = 0UL; i < SymbolOrderCount; ++i) {
        sym = SymbolOrder[i];
        if ((sym->flags & SYM_PRIVATE) != 0UL)
            continue;
        if (seen++ != index)
            continue;
        n = 0UL;
        for (ref = sym->refs; ref != (struct asm56000_ref *)0;
             ref = ref->next) {
            if (lines != (unsigned long *)0 && n < max_lines)
                lines[n] = ref->line;
            if (definitions != (int *)0 && n < max_lines)
                definitions[n] = ref->type == 2;
            ++n;
        }
        if (count != (unsigned long *)0)
            *count = n;
        return 1;
    }
    return 0;
}

void sym_new_local_block(void *sym_ptr)
{
    struct asm56000_local_block *block;

    block = (struct asm56000_local_block *)xmalloc(
        (unsigned long)sizeof(struct asm56000_local_block));
    block->number = ++LocalBlockNumber;
    block->first = (struct asm56000_symbol *)sym_ptr;
    block->next = (struct asm56000_local_block *)0;
    if (CurrentLocalBlock != (struct asm56000_local_block *)0)
        CurrentLocalBlock->next = block;
    else
        LocalBlocks = block;
    CurrentLocalBlock = block;
}

static struct asm56000_ext *find_ext(char *name)
{
    struct asm56000_ext *ext;
    unsigned long bucket;

    bucket = hash_name(name);
    ext = ExtHash[bucket];
    ExtInsertPoint = (struct asm56000_ext *)0;
    while (ext != (struct asm56000_ext *)0) {
        if (strcmp(ext->name, name) == 0 && ext->section == CurrentSection)
            return ext;
        ExtInsertPoint = ext;
        ext = ext->next;
    }
    return (struct asm56000_ext *)0;
}

int ext_add(char *name, int force)
{
    struct asm56000_ext *ext;
    char *key;
    unsigned long bucket;

    key = lookup_name(name, (int *)0);
    if (key == (char *)0 || *key == '\0')
        return 0;
    ext = find_ext(key);
    if (ext != (struct asm56000_ext *)0) {
        if (force)
            ext->flags |= 0x80UL;
        return 1;
    }
    ext = (struct asm56000_ext *)xmalloc(
        (unsigned long)sizeof(struct asm56000_ext));
    memset(ext, 0, sizeof(struct asm56000_ext));
    ext->name = copy_name(key);
    ext->flags = force ? 0x80UL : 0x40UL;
    ext->section = CurrentSection;
    bucket = hash_name(ext->name);
    if (ExtInsertPoint != (struct asm56000_ext *)0) {
        ext->next = ExtInsertPoint->next;
        ext->prev = ExtInsertPoint;
        if (ext->next != (struct asm56000_ext *)0)
            ext->next->prev = ext;
        ExtInsertPoint->next = ext;
    } else {
        ext->next = ExtHash[bucket];
        if (ext->next != (struct asm56000_ext *)0)
            ext->next->prev = ext;
        ExtHash[bucket] = ext;
    }
    return 1;
}

void *ext_lookup(char *name)
{
    char *key;

    key = lookup_name(name, (int *)0);
    if (key == (char *)0)
        return (void *)0;
    return (void *)find_ext(key);
}

void *strtab_lookup(char *name)
{
    (void)name;
    return (void *)0;
}

unsigned long sym_value(void *sym_ptr)
{
    struct asm56000_symbol *sym;

    sym = (struct asm56000_symbol *)sym_ptr;
    return sym == (struct asm56000_symbol *)0 ? 0UL : sym->value[2];
}

unsigned long sym_flags(void *sym_ptr)
{
    struct asm56000_symbol *sym;

    sym = (struct asm56000_symbol *)sym_ptr;
    return sym == (struct asm56000_symbol *)0 ? 0UL : sym->flags;
}

unsigned long sym_count(void)
{
    return SymbolCount;
}

unsigned long sym_public_count(void)
{
    unsigned long i;
    unsigned long count;

    count = 0UL;
    for (i = 0UL; i < SymbolOrderCount; ++i)
        if ((SymbolOrder[i]->flags & (SYM_LOCAL | SYM_PRIVATE | SYM_SET)) == 0UL)
            ++count;
    return count;
}

unsigned long sym_object_count(void)
{
    unsigned long i;
    unsigned long count;

    count = 0UL;
    for (i = 0UL; i < SymbolOrderCount; ++i)
        if ((SymbolOrder[i]->flags & SYM_PRIVATE) == 0UL)
            ++count;
    return count;
}

int sym_object_info(unsigned long index, char *name, unsigned long size,
                    unsigned long *value, unsigned long *space,
                    unsigned long *coff_scn, unsigned long *flags,
                    unsigned long *word0, unsigned long *word1,
                    unsigned long *word2, int *sectioned, int *global)
{
    unsigned long i;
    unsigned long seen;
    struct asm56000_symbol *sym;

    seen = 0UL;
    for (i = 0UL; i < SymbolOrderCount; ++i) {
        sym = SymbolOrder[i];
        if ((sym->flags & SYM_PRIVATE) != 0UL)
            continue;
        if (seen++ != index)
            continue;
        if (name != (char *)0 && size != 0UL) {
            strncpy(name, sym->name, size - 1UL);
            name[size - 1UL] = '\0';
        }
        if (value != (unsigned long *)0)
            *value = sym->value[2];
        if (space != (unsigned long *)0)
            *space = sym->space;
        if (coff_scn != (unsigned long *)0)
            *coff_scn = sym->coff_scn;
        if (flags != (unsigned long *)0)
            *flags = sym->flags;
        if (word0 != (unsigned long *)0)
            *word0 = sym->value[0];
        if (word1 != (unsigned long *)0)
            *word1 = sym->value[1];
        if (word2 != (unsigned long *)0)
            *word2 = sym->value[2];
        if (sectioned != (int *)0)
            *sectioned = sym->sectioned;
        if (global != (int *)0)
            *global = sym->global;
        return 1;
    }
    return 0;
}

/* Pass-2 definition order of an object symbol: sequence stamp and the
   number of the COFF section it was defined in. */
int sym_object_order(unsigned long index, unsigned long *seq,
                     unsigned long *scn)
{
    unsigned long i;
    unsigned long seen;
    struct asm56000_symbol *sym;

    seen = 0UL;
    for (i = 0UL; i < SymbolOrderCount; ++i) {
        sym = SymbolOrder[i];
        if ((sym->flags & SYM_PRIVATE) != 0UL)
            continue;
        if (seen++ != index)
            continue;
        if (seq != (unsigned long *)0)
            *seq = sym->obj_seq;
        if (scn != (unsigned long *)0)
            *scn = sym->obj_scn;
        return 1;
    }
    return 0;
}

int sym_object_xdef(unsigned long index)
{
    unsigned long i;
    unsigned long seen;
    struct asm56000_symbol *sym;

    seen = 0UL;
    for (i = 0UL; i < SymbolOrderCount; ++i) {
        sym = SymbolOrder[i];
        if ((sym->flags & SYM_PRIVATE) != 0UL)
            continue;
        if (seen++ != index)
            continue;
        return sec_has_xdef(sym->section, sym->name);
    }
    return 0;
}

/* Attach the symbol defined at sequence stamp OLD_SEQ to COFF section SCN;
   a non-zero NEW_SEQ moves it later in the symbol table. */
void sym_object_set(unsigned long old_seq, unsigned long scn,
                    unsigned long new_seq)
{
    unsigned long i;
    struct asm56000_symbol *sym;

    for (i = 0UL; i < SymbolOrderCount; ++i) {
        sym = SymbolOrder[i];
        if (sym->obj_seq != old_seq || old_seq == 0UL)
            continue;
        sym->obj_scn = scn;
        if (new_seq > old_seq)
            sym->obj_seq = new_seq;
        return;
    }
}

int sym_object_definition_line(unsigned long index, unsigned long *line)
{
    unsigned long i;
    unsigned long seen;
    struct asm56000_symbol *sym;

    seen = 0UL;
    for (i = 0UL; i < SymbolOrderCount; ++i) {
        sym = SymbolOrder[i];
        if ((sym->flags & SYM_PRIVATE) != 0UL)
            continue;
        if (seen++ != index)
            continue;
        if (line != (unsigned long *)0)
            *line = sym->definition_line;
        return 1;
    }
    return 0;
}

int sym_public_info(unsigned long index, char *name, unsigned long size,
                    unsigned long *value, unsigned long *space,
                    unsigned long *coff_scn)
{
    unsigned long i;
    unsigned long seen;
    struct asm56000_symbol *sym;

    seen = 0UL;
    for (i = 0UL; i < SymbolOrderCount; ++i) {
        sym = SymbolOrder[i];
        if ((sym->flags & (SYM_LOCAL | SYM_PRIVATE | SYM_SET)) != 0UL)
            continue;
        if (seen++ != index)
            continue;
        if (name != (char *)0 && size != 0UL) {
            strncpy(name, sym->name, size - 1UL);
            name[size - 1UL] = '\0';
        }
        if (value != (unsigned long *)0)
            *value = sym->value[2];
        if (space != (unsigned long *)0)
            *space = sym->space;
        if (coff_scn != (unsigned long *)0)
            *coff_scn = sym->coff_scn;
        return 1;
    }
    return 0;
}

int sym_public_details(unsigned long index, char *name, unsigned long size,
                       unsigned long *value, unsigned long *space,
                       unsigned long *coff_scn, unsigned long *flags,
                       unsigned long *word0, unsigned long *word1,
                       unsigned long *word2, int *sectioned, int *global)
{
    unsigned long i;
    unsigned long seen;
    struct asm56000_symbol *sym;

    seen = 0UL;
    for (i = 0UL; i < SymbolOrderCount; ++i) {
        sym = SymbolOrder[i];
        if ((sym->flags & (SYM_LOCAL | SYM_PRIVATE | SYM_SET)) != 0UL)
            continue;
        if (seen++ != index)
            continue;
        if (name != (char *)0 && size != 0UL) {
            strncpy(name, sym->name, size - 1UL);
            name[size - 1UL] = '\0';
        }
        if (value != (unsigned long *)0)
            *value = sym->value[2];
        if (space != (unsigned long *)0)
            *space = sym->space;
        if (coff_scn != (unsigned long *)0)
            *coff_scn = sym->coff_scn;
        if (flags != (unsigned long *)0)
            *flags = sym->flags;
        if (word0 != (unsigned long *)0)
            *word0 = sym->value[0];
        if (word1 != (unsigned long *)0)
            *word1 = sym->value[1];
        if (word2 != (unsigned long *)0)
            *word2 = sym->value[2];
        if (sectioned != (int *)0)
            *sectioned = sym->sectioned;
        if (global != (int *)0)
            *global = sym->global;
        return 1;
    }
    return 0;
}

void sym_first_info(char *name, unsigned long size, unsigned long *value)
{
    unsigned long i;
    struct asm56000_symbol *sym;

    if (name != (char *)0 && size != 0UL)
        name[0] = '\0';
    if (value != (unsigned long *)0)
        *value = 0UL;
    for (i = 0UL; i < ASM56000_SYM_BUCKETS; ++i) {
        sym = SymHash[i];
        if (sym == (struct asm56000_symbol *)0)
            continue;
        if (name != (char *)0 && size != 0UL) {
            strncpy(name, sym->name, size - 1UL);
            name[size - 1UL] = '\0';
        }
        if (value != (unsigned long *)0)
            *value = sym->value[2];
        return;
    }
}

char *sym_name(void *sym_ptr)
{
    struct asm56000_symbol *sym;

    sym = (struct asm56000_symbol *)sym_ptr;
    return sym == (struct asm56000_symbol *)0 ? (char *)0 : sym->name;
}

void sym_copy_value(void *sym_ptr, void *value)
{
    struct asm56000_symbol *sym;
    unsigned long *out;

    sym = (struct asm56000_symbol *)sym_ptr;
    out = (unsigned long *)value;
    if (sym == (struct asm56000_symbol *)0 || out == (unsigned long *)0)
        return;
    out[ASM56000_EXPR_W0 / 4] = sym->value[0];
    out[ASM56000_EXPR_W1 / 4] = sym->value[1];
    out[ASM56000_EXPR_W2 / 4] = sym->value[2];
    out[ASM56000_EXPR_W4 / 4] = (sym->flags & SYM_FLOAT) != 0UL ?
        SYM_FLOAT : SYM_INTEGER;
    out[ASM56000_EXPR_W6 / 4] = sym->flags & 0x7000UL;
    out[ASM56000_EXPR_W7 / 4] = sym->space;
    out[ASM56000_EXPR_W8 / 4] = sym->map;
    out[ASM56000_EXPR_W9 / 4] = sym->counter;
    out[ASM56000_EXPR_W10 / 4] = sym->emi;
    out[ASM56000_EXPR_W21 / 4] = sym->coff_scn;
    out[ASM56000_EXPR_W15 / 4] = sym->rel_sec;
    out[ASM56000_EXPR_W16 / 4] = sym->rel_cnt;
}

static void free_refs(struct asm56000_ref *ref)
{
    struct asm56000_ref *next;

    while (ref != (struct asm56000_ref *)0) {
        next = ref->next;
        xfree(ref);
        ref = next;
    }
}

void sym_free_all(void)
{
    unsigned long i;
    struct asm56000_symbol *sym;
    struct asm56000_symbol *next;

    for (i = 0UL; i < ASM56000_SYM_BUCKETS; ++i) {
        sym = SymHash[i];
        while (sym != (struct asm56000_symbol *)0) {
            next = sym->next;
            xfree(sym->name);
            free_refs(sym->refs);
            xfree(sym);
            sym = next;
        }
        SymHash[i] = (struct asm56000_symbol *)0;
    }
    SymbolCount = 0UL;
    SymInsertPoint = (struct asm56000_symbol *)0;
}

void sym_free_local_blocks(void)
{
    struct asm56000_local_block *block;
    struct asm56000_local_block *next;

    block = LocalBlocks;
    while (block != (struct asm56000_local_block *)0) {
        next = block->next;
        xfree(block);
        block = next;
    }
    LocalBlocks = (struct asm56000_local_block *)0;
    CurrentLocalBlock = (struct asm56000_local_block *)0;
    LocalBlockNumber = 0UL;
}

void ext_free_all(void)
{
    unsigned long i;
    struct asm56000_ext *ext;
    struct asm56000_ext *next;

    for (i = 0UL; i < ASM56000_SYM_BUCKETS; ++i) {
        ext = ExtHash[i];
        while (ext != (struct asm56000_ext *)0) {
            next = ext->next;
            xfree(ext->name);
            xfree(ext);
            ext = next;
        }
        ExtHash[i] = (struct asm56000_ext *)0;
    }
    ExtInsertPoint = (struct asm56000_ext *)0;
}
