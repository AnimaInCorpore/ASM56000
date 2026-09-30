/* SECTION/ENDSEC state and per-section visibility lists. */
#include <string.h>
#include <ctype.h>

#include "asm56000.h"

#define SEC_STATIC 0x10UL
#define SEC_LOCAL  0x20UL
#define SEC_GLOBAL 0x40UL

struct section_name {
    char *name;
    struct section_name *next;
};

struct asm_section {
    char *name;
    unsigned long number;
    unsigned long flags;
    struct section_name *xdef;
    struct section_name *xref;
    struct section_name *local;
    struct section_name *global;
    struct asm_section *counter_section;
    struct asm_section *next;
};

struct section_stack_node {
    struct asm_section *section;
    struct section_stack_node *next;
};

static int list_has(struct section_name *list, char *name);
static struct asm_section GlobalSection;
static struct asm_section *SectionList;
static struct section_stack_node *SectionStack;
static unsigned long SectionCount;
static unsigned long SectionDepth;
static int SectionReady;

static char *section_copy(char *name)
{
    unsigned long n;
    char *copy;

    n = (unsigned long)strlen(name);
    copy = (char *)xmalloc(n + 1UL);
    strcpy(copy, name);
    return copy;
}

void sec_init(void)
{
    if (SectionReady)
        return;
    memset(&GlobalSection, 0, sizeof(GlobalSection));
    GlobalSection.name = (char *)"GLOBAL";
    GlobalSection.counter_section = &GlobalSection;
    SectionList = &GlobalSection;
    SectionStack = (struct section_stack_node *)0;
    SectionCount = 0UL;
    SectionDepth = 0UL;
    CurrentSection = (void *)&GlobalSection;
    SectionReady = 1;
}

void *sec_new(char *name)
{
    struct asm_section *section;

    sec_init();
    section = (struct asm_section *)xmalloc(
        (unsigned long)sizeof(struct asm_section));
    memset(section, 0, sizeof(struct asm_section));
    section->name = section_copy(name);
    section->number = ++SectionCount;
    if (SectionCount > 255UL)
        fatal("Too many sections in module");
    section->counter_section = section;
    section->next = (struct asm_section *)0;
    SectionList->next = section;
    SectionList = section;
    return (void *)section;
}

void sec_set_current(void *section_ptr, int is_new)
{
    struct asm_section *section;

    (void)is_new;
    sec_init();
    section = (struct asm_section *)section_ptr;
    if (section == (struct asm_section *)0)
        section = &GlobalSection;
    CurrentSection = (void *)section;
}

void sec_save_counters(void)
{
}

int sec_push(void *section_ptr)
{
    struct section_stack_node *node;
    struct asm_section *section;

    sec_init();
    section = (struct asm_section *)section_ptr;
    if (section == (struct asm_section *)0)
        return 0;
    node = (struct section_stack_node *)xmalloc(
        (unsigned long)sizeof(struct section_stack_node));
    node->section = section;
    node->next = SectionStack;
    SectionStack = node;
    ++SectionDepth;
    return 1;
}

int sec_section(char *name, char *mod1, char *mod2)
{
    struct asm_section *section;
    unsigned long flags;
    char *mods[2];
    int i;

    sec_init();
    if (name == (char *)0 || *name == '\0')
        return 0;
    flags = 0UL;
    mods[0] = mod1;
    mods[1] = mod2;
    for (i = 0; i < 2; ++i) {
        if (mods[i] == (char *)0 || *mods[i] == '\0')
            continue;
        if (strcmp(str_lower_copy(mods[i]), "global") == 0)
            flags |= SEC_GLOBAL;
        else if (strcmp(str_lower_copy(mods[i]), "static") == 0)
            flags |= SEC_STATIC;
        else if (strcmp(str_lower_copy(mods[i]), "local") == 0)
            flags |= SEC_LOCAL;
        else if (strcmp(str_lower_copy(mods[i]), "debug") == 0)
            flags |= 0x200000UL;
        else
            return 0;
    }
    section = &GlobalSection;
    while (section != (struct asm_section *)0) {
        if (strcmp(section->name, name) == 0)
            break;
        section = section->next;
    }
    if (section != (struct asm_section *)0 &&
        CurrentSection == (void *)section && SectionDepth != 0UL) {
        CurInstrFieldMsg = Op1Field;
        err("Cannot nest section inside itself");
        return 0;
    }
    if (section == (struct asm_section *)0) {
        section = (struct asm_section *)sec_new(name);
        section->flags = flags;
    } else {
        section->flags = (section->flags & ~0x2000050UL) | flags;
    }
    if (CurrentSection != (void *)section)
        sec_push(CurrentSection);
    sec_set_current(section, 1);
    return 1;
}

int sec_endsec(void)
{
    struct section_stack_node *node;

    sec_init();
    if (SectionDepth == 0UL || SectionStack == (struct section_stack_node *)0) {
        CurrentSection = (void *)&GlobalSection;
        return 0;
    }
    node = SectionStack;
    SectionStack = node->next;
    --SectionDepth;
    sec_set_current((void *)node->section, 0);
    xfree(node);
    return 1;
}

/* Number of sections defined so far (SECTION names, GLOBAL excluded). */
unsigned long sec_defined_count(void)
{
    sec_init();
    return SectionCount;
}

/* True when NAME was declared XDEF in the given section. */
int sec_has_xdef(void *section, char *name)
{
    sec_init();
    if (section == (void *)0)
        section = (void *)&GlobalSection;
    return list_has(((struct asm_section *)section)->xdef, name);
}

unsigned long sec_number(void *section)
{
    sec_init();
    if (section == (void *)0 || section == (void *)&GlobalSection)
        return 0UL;
    return ((struct asm_section *)section)->number;
}

/* Number of the section whose location counters a section uses: a STATIC
   section allocates from the global section's counters. */
unsigned long sec_counter_number(void *section)
{
    sec_init();
    if (section == (void *)0 || section == (void *)&GlobalSection ||
        (((struct asm_section *)section)->flags & SEC_STATIC) != 0UL)
        return 0UL;
    return ((struct asm_section *)section)->number;
}

int sec_is_static_section(void *section)
{
    if (section == (void *)0 || section == (void *)&GlobalSection)
        return 0;
    return (((struct asm_section *)section)->flags & SEC_STATIC) != 0UL;
}

void *sec_global_section(void)
{
    return (void *)&GlobalSection;
}

unsigned long sec_depth(void)
{
    sec_init();
    return SectionDepth;
}

static struct section_name **list_for(struct asm_section *section, int which)
{
    if (which == 0)
        return &section->local;
    if (which == 1)
        return &section->global;
    if (which == 2)
        return &section->xref;
    return &section->xdef;
}

static int list_has(struct section_name *list, char *name)
{
    while (list != (struct section_name *)0) {
        if (strcmp(list->name, name) == 0)
            return 1;
        list = list->next;
    }
    return 0;
}

static int add_current_names(int which)
{
    struct asm_section *section;
    struct section_name **head;
    struct section_name *node;
    char *fields[4];
    char *p;
    char *q;
    char name[128];
    int i;
    unsigned long n;

    sec_init();
    section = (struct asm_section *)CurrentSection;
    if (section == (struct asm_section *)0)
        return 0;
    fields[0] = Op1Field; fields[1] = Op2Field;
    fields[2] = Op3Field; fields[3] = Op4Field;
    head = list_for(section, which);
    for (i = 0; i < 4; ++i) {
        if (fields[i] == (char *)0 || *fields[i] == '\0')
            continue;
        p = fields[i];
        while (p != (char *)0 && *p != '\0') {
            q = strchr(p, ',');
            n = q == (char *)0 ? (unsigned long)strlen(p) :
                (unsigned long)(q - p);
            while (n != 0UL && isspace((unsigned char)p[n - 1UL]))
                --n;
            while (*p != '\0' && isspace((unsigned char)*p))
                ++p;
            if (n >= sizeof(name))
                return 0;
            memcpy(name, p, n);
            name[n] = '\0';
            if (n != 0UL && !isalpha((unsigned char)name[0])) {
                CurInstrFieldMsg = Op1Field;
                err("Symbols must start with alphabetic character");
            } else if (n != 0UL && which == 1 && section == &GlobalSection) {
                CurInstrFieldMsg = Op1Field;
                err("GLOBAL without preceding SECTION directive");
            } else if (n != 0UL && which == 0 && Pass == 2UL &&
                       sym_definition_line(name) != 0UL &&
                       sym_definition_line(name) <= LineNo) {
                CurInstrFieldMsg = Op1Field;
                err_s("Symbol undefined on pass 2", name);
            } else if (n != 0UL && which != 0 &&
                       list_has(section->local, name)) {
                CurInstrFieldMsg = Op1Field;
                err_s("Symbol already defined as LOCAL", name);
            } else if (n != 0UL && !list_has(*head, name)) {
                node = (struct section_name *)xmalloc(
                    (unsigned long)sizeof(struct section_name));
                node->name = section_copy(name);
                node->next = *head;
                *head = node;
            }
            if (q == (char *)0)
                break;
            p = q + 1;
        }
    }
    return 1;
}

int sec_local(void) { return add_current_names(0); }
int sec_global(void) { return add_current_names(1); }
int sec_xref(void) { return add_current_names(2); }
int sec_xdef(void) { return add_current_names(3); }

static int current_has(char *name, int which)
{
    struct asm_section *section;

    sec_init();
    section = (struct asm_section *)CurrentSection;
    return section == (struct asm_section *)0 ? 0 :
        list_has(*list_for(section, which), name);
}

int sec_is_local(char *name) { return current_has(name, 0); }
int sec_is_global(char *name) { return current_has(name, 1); }
int sec_is_xref(char *name) { return current_has(name, 2); }
int sec_is_xdef(char *name) { return current_has(name, 3); }

unsigned long sec_xref_count(char *name)
{
    struct asm_section *section;
    struct section_name *item;
    unsigned long count;

    sec_init();
    section = SectionList;
    while (section != (struct asm_section *)0) {
        if (strcmp(section->name, name) == 0)
            break;
        section = section->next;
    }
    if (section == (struct asm_section *)0)
        return 0UL;
    count = 0UL;
    for (item = section->xref; item != (struct section_name *)0;
         item = item->next)
        ++count;
    return count;
}

int sec_xref_info(char *name, unsigned long index, char *out,
                  unsigned long size)
{
    struct asm_section *section;
    struct section_name *item;
    unsigned long i;

    sec_init();
    section = SectionList;
    while (section != (struct asm_section *)0) {
        if (strcmp(section->name, name) == 0)
            break;
        section = section->next;
    }
    if (section == (struct asm_section *)0)
        return 0;
    item = section->xref;
    for (i = 0UL; item != (struct section_name *)0 && i < index;
         ++i)
        item = item->next;
    if (item == (struct section_name *)0)
        return 0;
    if (out != (char *)0 && size != 0UL) {
        strncpy(out, item->name, size - 1UL);
        out[size - 1UL] = '\0';
    }
    return 1;
}
int sec_current_is_global(void)
{
    sec_init();
    return CurrentSection == (void *)&GlobalSection;
}
int sec_current_section_global(void)
{
    struct asm_section *section;

    sec_init();
    section = (struct asm_section *)CurrentSection;
    return section != (struct asm_section *)0 &&
           (section->flags & SEC_GLOBAL) != 0UL;
}
char *sec_current_name(void)
{
    struct asm_section *section;

    sec_init();
    section = (struct asm_section *)CurrentSection;
    return section == (struct asm_section *)0 || section->name == (char *)0 ?
           (char *)"GLOBAL" : section->name;
}
int sec_check_local(char *name) { return sec_is_local(name) ? 1 : 0; }
int sec_check_global(char *name) { return sec_is_global(name) ? 1 : 0; }
int sec_check_xref(char *name) { return sec_is_xref(name) ? 1 : 0; }
int sec_check_xdef(char *name) { return sec_is_xdef(name) ? 1 : 0; }

static void free_name_list(struct section_name *list)
{
    struct section_name *next;

    while (list != (struct section_name *)0) {
        next = list->next;
        xfree(list->name);
        xfree(list);
        list = next;
    }
}

void sec_free_names(void)
{
    struct asm_section *section;

    sec_init();
    section = &GlobalSection;
    while (section != (struct asm_section *)0) {
        free_name_list(section->xdef);
        free_name_list(section->xref);
        free_name_list(section->local);
        section->xdef = (struct section_name *)0;
        section->xref = (struct section_name *)0;
        section->local = (struct section_name *)0;
        section = section->next;
    }
}

void sec_debug_sym(void *section, int begin)
{
    (void)section;
    (void)begin;
}

void sec_free_all(void)
{
    struct asm_section *section;
    struct asm_section *next;

    sec_init();
    sec_free_names();
    section = GlobalSection.next;
    while (section != (struct asm_section *)0) {
        next = section->next;
        xfree(section->name);
        xfree(section);
        section = next;
    }
    GlobalSection.next = (struct asm_section *)0;
    SectionList = &GlobalSection;
    SectionCount = 0UL;
    SectionDepth = 0UL;
    while (SectionStack != (struct section_stack_node *)0) {
        struct section_stack_node *stack_next;

        stack_next = SectionStack->next;
        xfree(SectionStack);
        SectionStack = stack_next;
    }
    CurrentSection = (void *)&GlobalSection;
}
