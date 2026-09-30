/* Portable macro-definition and expansion layer for the ASM56000 driver. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asm56000.h"

extern unsigned long LineNo;

#define MACRO_MAX_PARAMS 16

struct macro_def {
    char *name;
    char *params[MACRO_MAX_PARAMS];
    int param_count;
    char **body;
    int body_count;
    int body_size;
    int library_lines;
    int library_listed;
    int capture_pass2;
    int purged;
    unsigned long definition_line;
    struct macro_def *next;
};

static struct macro_def *MacroList;
static struct macro_def *DefiningMacro;
static int MacroDefinitionRejected;
static int MacroParameterError;
static char *MacroPath;
static int ActiveArgCount;

static int name_equal(char *a, char *b)
{
    while (*a != '\0' && *b != '\0') {
        if (tolower((unsigned char)*a++) != tolower((unsigned char)*b++))
            return 0;
    }
    return *a == '\0' && *b == '\0';
}

static char *copy_text(char *text)
{
    return str_dupcat(text == (char *)0 ? (char *)"" : text,
                      (char *)0);
}

static struct macro_def *find_macro_any(char *name)
{
    struct macro_def *macro;

    for (macro = MacroList; macro != (struct macro_def *)0;
         macro = macro->next) {
        if (name_equal(macro->name, name))
            return macro;
    }
    return (struct macro_def *)0;
}

static struct macro_def *find_macro(char *name)
{
    struct macro_def *macro;

    macro = find_macro_any(name);
    return macro != (struct macro_def *)0 && !macro->purged ?
           macro : (struct macro_def *)0;
}

static void clear_body(struct macro_def *macro)
{
    int i;

    if (macro == (struct macro_def *)0)
        return;
    for (i = 0; i < macro->body_count; ++i)
        xfree((void *)macro->body[i]);
    xfree((void *)macro->body);
    macro->body = (char **)0;
    macro->body_count = 0;
    macro->body_size = 0;
}

static void trim_range(char *dst, unsigned size, char *begin, char *end)
{
    unsigned n;

    while (begin < end && (*begin == ' ' || *begin == '\t'))
        ++begin;
    while (end > begin && (end[-1] == ' ' || end[-1] == '\t'))
        --end;
    n = (unsigned)(end - begin);
    if (n >= size)
        n = size - 1U;
    memcpy(dst, begin, n);
    dst[n] = '\0';
}

unsigned long macro_eval_builtin(char *text, int *handled)
{
    char name[128];
    char *p;
    char *q;
    int argument;
    struct macro_def *macro;

    if (handled != (int *)0)
        *handled = 0;
    if (text == (char *)0)
        return 0UL;
    p = text;
    while (*p == ' ' || *p == '\t')
        ++p;
    if (strncmp(p, "@cnt()", 6) == 0 &&
        (p[6] == '\0' || isspace((unsigned char)p[6]))) {
        if (handled != (int *)0)
            *handled = 1;
        return (unsigned long)ActiveArgCount;
    }
    if (strncmp(p, "@mxp()", 6) == 0 &&
        (p[6] == '\0' || isspace((unsigned char)p[6]))) {
        if (handled != (int *)0)
            *handled = 1;
        return (unsigned long)ActiveArgCount;
    }
    if (strncmp(p, "@arg(", 5) == 0) {
        argument = atoi(p + 5);
        q = strchr(p + 5, ')');
        if (q != (char *)0 && argument > 0) {
            if (handled != (int *)0)
                *handled = 1;
            return argument <= ActiveArgCount ? 1UL : 0UL;
        }
    }
    if (strncmp(p, "@mac(", 5) == 0) {
        q = strchr(p + 5, ')');
        if (q != (char *)0) {
            trim_range(name, sizeof(name), p + 5, q);
            macro = find_macro(name);
            if (handled != (int *)0)
                *handled = 1;
            return macro != (struct macro_def *)0 ? 1UL : 0UL;
        }
    }
    return 0UL;
}

static void parse_params(struct macro_def *macro, char *text)
{
    char *p;
    char *start;
    char name[64];
    int count;
    int bad;

    count = 0;
    bad = 0;
    p = text == (char *)0 ? (char *)"" : text;
    start = p;
    for (;;) {
        if (*p == ',' || *p == '\0') {
            if (count < MACRO_MAX_PARAMS) {
                trim_range(name, sizeof(name), start, p);
                if (name[0] != '\0' &&
                    !isalpha((unsigned char)name[0]))
                    bad = 1;
                if (name[0] != '\0' && isalpha((unsigned char)name[0]))
                    macro->params[count++] = copy_text(name);
            }
            if (*p == '\0')
                break;
            start = p + 1;
        }
        ++p;
    }
    macro->param_count = count;
    MacroParameterError = bad;
}

void macro_init(void)
{
    MacroList = (struct macro_def *)0;
    DefiningMacro = (struct macro_def *)0;
    MacroPath = (char *)0;
    ActiveArgCount = 0;
    MacroDefinitionRejected = 0;
    MacroParameterError = 0;
}

void macro_set_path(char *path)
{
    char *joined;

    if (path != (char *)0 && *path != '\0') {
        if (MacroPath == (char *)0)
            MacroPath = copy_text(path);
        else {
            joined = str_dupcat(MacroPath, ";", path, (char *)0);
            xfree((void *)MacroPath);
            MacroPath = joined;
        }
    }
}

void macro_begin(char *name, char *params)
{
    struct macro_def *macro;
    int i;

    if (name == (char *)0 || *name == '\0')
        return;
    MacroParameterError = 0;
    macro = find_macro(name);
    if (macro == (struct macro_def *)0)
        macro = find_macro_any(name);
    MacroDefinitionRejected = 0;
    if (macro == (struct macro_def *)0) {
        macro = (struct macro_def *)xmalloc((unsigned long)sizeof(*macro));
        memset(macro, 0, sizeof(*macro));
        macro->name = copy_text(name);
        macro->capture_pass2 = Pass == 2UL;
        macro->next = MacroList;
        MacroList = macro;
    } else if (macro->purged) {
        for (i = 0; i < macro->param_count; ++i)
            xfree((void *)macro->params[i]);
        macro->param_count = 0;
        clear_body(macro);
        macro->purged = 0;
        macro->capture_pass2 = Pass == 2UL;
    } else if (Pass == 2UL && macro->definition_line == LineNo) {
        DefiningMacro = macro;
        macro->capture_pass2 = 0;
        return;
    } else {
        MacroDefinitionRejected = 1;
        DefiningMacro = (struct macro_def *)0;
        if (Pass == 2UL)
            err_s("Macro cannot be redefined", name);
        return;
    }
    macro->purged = 0;
    if (Pass == 1UL)
        macro->definition_line = LineNo;
    if (Pass == 1UL || macro->capture_pass2)
        parse_params(macro, params);
    if (MacroParameterError) {
        MacroDefinitionRejected = 1;
        macro->purged = 1;
        DefiningMacro = (struct macro_def *)0;
        if (Pass == 2UL) {
            CurInstrFieldMsg = Op1Field;
            err("Symbols must start with alphabetic character");
        }
        return;
    }
    DefiningMacro = macro;
}

int macro_definition_rejected(void)
{
    return MacroDefinitionRejected;
}

int macro_parameter_error(void)
{
    return MacroParameterError;
}

int macro_is_defined(char *name)
{
    return find_macro(name) != (struct macro_def *)0;
}

unsigned long macro_report_count(void)
{
    unsigned long count;
    struct macro_def *macro;

    count = 0UL;
    for (macro = MacroList; macro != (struct macro_def *)0;
         macro = macro->next)
        if (!macro->purged)
            ++count;
    return count;
}

int macro_report_info(unsigned long index, char *name, unsigned long size,
                      unsigned long *line)
{
    unsigned long seen;
    struct macro_def *macro;

    seen = 0UL;
    for (macro = MacroList; macro != (struct macro_def *)0;
         macro = macro->next) {
        if (macro->purged)
            continue;
        if (seen++ != index)
            continue;
        if (name != (char *)0 && size != 0UL) {
            strncpy(name, macro->name, size - 1UL);
            name[size - 1UL] = '\0';
        }
        if (line != (unsigned long *)0)
            *line = macro->definition_line;
        return 1;
    }
    return 0;
}

void macro_add_line(char *line)
{
    char **next;
    int size;

    if (DefiningMacro == (struct macro_def *)0 ||
        (Pass != 1UL && !DefiningMacro->capture_pass2))
        return;
    if (DefiningMacro->body_count == DefiningMacro->body_size) {
        size = DefiningMacro->body_size == 0 ? 8 :
               DefiningMacro->body_size * 2;
        next = (char **)xrealloc((void *)DefiningMacro->body,
                                 (unsigned long)size * sizeof(char *));
        DefiningMacro->body = next;
        DefiningMacro->body_size = size;
    }
    DefiningMacro->body[DefiningMacro->body_count++] = copy_text(line);
}

void macro_end(void)
{
    DefiningMacro = (struct macro_def *)0;
}

void macro_purge(char *text)
{
    char item[64];
    char *p;
    char *start;
    struct macro_def *macro;

    if (text == (char *)0)
        return;
    p = text;
    start = p;
    for (;;) {
        if (*p == ',' || *p == '\0') {
            trim_range(item, sizeof(item), start, p);
            macro = find_macro_any(item);
            if (macro != (struct macro_def *)0)
                macro->purged = 1;
            if (*p == '\0')
                break;
            start = p + 1;
        }
        ++p;
    }
}

static int param_number(struct macro_def *macro, char *start, char *end)
{
    char name[64];
    int i;

    trim_range(name, sizeof(name), start, end);
    for (i = 0; i < macro->param_count; ++i) {
        if (name_equal(name, macro->params[i]))
            return i;
    }
    return -1;
}

static char *substitute(struct macro_def *macro, char *line,
                        char **args, int arg_count)
{
    char out[ASM56000_INPUT_LINE_CAP * 2];
    char *p;
    char *word;
    char *end;
    char *arg;
    char formatted[128];
    char quote;
    unsigned used;
    unsigned n;
    unsigned long value;
    int index;

    used = 0U;
    quote = '\0';
    p = line;
    while (*p != '\0' && used + 1U < sizeof(out)) {
        if (*p == '\'' || *p == '"') {
            if (quote == '\0')
                quote = *p;
            else if (quote == *p)
                quote = '\0';
            out[used++] = *p == '"' ? '\'' : *p;
            ++p;
            continue;
        }
        if (quote != '\'' && (*p == '?' || *p == '%')) {
            word = p + 1;
            end = word;
            while (isalnum((unsigned char)*end) || *end == '_')
                ++end;
            index = param_number(macro, word, end);
            if (index >= 0) {
                arg = index < arg_count ? args[index] : (char *)"";
                if (*p == '?') {
                    void *evaluated;

                    evaluated = eval_expr_text(arg);
                    value = expr_as_int32(evaluated);
                    free_expr(evaluated);
                    sprintf(formatted, "%lu", value);
                    arg = formatted;
                } else {
                    void *evaluated;

                    evaluated = eval_expr_text(arg);
                    value = expr_as_int32(evaluated);
                    free_expr(evaluated);
                    sprintf(formatted, "%lX", value);
                    arg = formatted;
                }
                n = (unsigned)strlen(arg);
                if (used + n >= sizeof(out))
                    n = sizeof(out) - used - 1U;
                memcpy(out + used, arg, n);
                used += n;
                p = end;
                continue;
            }
        }
        if (quote != '\'' && *p == '\\') {
            word = p + 1;
            end = word;
            while (isalnum((unsigned char)*end) || *end == '_')
                ++end;
            index = param_number(macro, word, end);
            if (index >= 0) {
                arg = index < arg_count ? args[index] : (char *)"";
                n = (unsigned)strlen(arg);
                if (used + n >= sizeof(out))
                    n = sizeof(out) - used - 1U;
                memcpy(out + used, arg, n);
                used += n;
                p = end;
                continue;
            }
        }
        if (quote != '\'' &&
            (isalpha((unsigned char)*p) || *p == '_')) {
            word = p;
            end = p + 1;
            while (isalnum((unsigned char)*end) || *end == '_')
                ++end;
            index = param_number(macro, word, end);
            if (index >= 0) {
                arg = index < arg_count ? args[index] : (char *)"";
                n = (unsigned)strlen(arg);
                if (used + n >= sizeof(out))
                    n = sizeof(out) - used - 1U;
                memcpy(out + used, arg, n);
                used += n;
                p = end;
                continue;
            }
        }
        out[used++] = *p++;
    }
    out[used] = '\0';
    return copy_text(out);
}

static int split_args(char *text, char **args, char storage[][128], int max)
{
    char *p;
    char *start;
    int depth;
    int count;
    unsigned n;

    if (text == (char *)0 || *text == '\0')
        return 0;
    p = text;
    start = p;
    depth = 0;
    count = 0;
    while (*p != '\0') {
        if (*p == '(')
            ++depth;
        else if (*p == ')' && depth > 0)
            --depth;
        if (*p == ',' && depth == 0) {
            if (count < max) {
                n = (unsigned)(p - start);
                if (n >= sizeof(storage[0]))
                    n = sizeof(storage[0]) - 1U;
                memcpy(storage[count], start, n);
                storage[count][n] = '\0';
                args[count] = storage[count];
                ++count;
            }
            start = p + 1;
        }
        ++p;
    }
    if (count < max) {
        n = (unsigned)(p - start);
        if (n >= sizeof(storage[0]))
            n = sizeof(storage[0]) - 1U;
        memcpy(storage[count], start, n);
        storage[count][n] = '\0';
        args[count] = storage[count];
        ++count;
    }
    return count;
}

static int load_library_macro(char *name)
{
    char path[512];
    char line[ASM56000_INPUT_LINE_CAP];
    char macro_name[64];
    char mnemonic[32];
    char params[128];
    char *p;
    char *q;
    FILE *fp;
    struct macro_def *macro;
    int in_macro;
    int lines_read;
    char *path_start;
    char *path_end;
    char path_part[256];
    unsigned path_len;
    unsigned long library_base;

    if (MacroPath == (char *)0)
        return 0;
    fp = (FILE *)0;
    path_start = MacroPath;
    while (path_start != (char *)0 && *path_start != '\0') {
        path_end = strchr(path_start, ';');
        if (path_end == (char *)0)
            path_end = path_start + strlen(path_start);
        path_len = (unsigned)(path_end - path_start);
        if (path_len >= sizeof(path_part))
            path_len = sizeof(path_part) - 1U;
        memcpy(path_part, path_start, path_len);
        path_part[path_len] = '\0';
        sprintf(path, "%s/%s.asm", path_part, name);
        fp = fopen(path, "rb");
        if (fp != (FILE *)0)
            break;
        if (*path_end == '\0')
            break;
        path_start = path_end + 1;
    }
    if (fp == (FILE *)0)
        return 0;
    in_macro = 0;
    lines_read = 0;
    library_base = LineNo;
    while (fgets(line, sizeof(line), fp) != (char *)0) {
        ++lines_read;
        p = line;
        while (*p == ' ' || *p == '\t')
            ++p;
        if (*p == ';' || *p == '\r' || *p == '\n' || *p == '\0')
            continue;
        q = p;
        while (*q != '\0' && *q != ' ' && *q != '\t' &&
               *q != '\r' && *q != '\n')
            ++q;
        if (!in_macro) {
            trim_range(macro_name, sizeof(macro_name), p, q);
            p = q;
            while (*p == ' ' || *p == '\t')
                ++p;
            q = p;
            while (*q != '\0' && *q != ' ' && *q != '\t' &&
                   *q != '\r' && *q != '\n')
                ++q;
            trim_range(mnemonic, sizeof(mnemonic), p, q);
            if (!name_equal(mnemonic, "macro"))
                continue;
            p = q;
            while (*p == ' ' || *p == '\t')
                ++p;
            q = p + strlen(p);
            while (q > p && (q[-1] == '\r' || q[-1] == '\n'))
                --q;
            trim_range(params, sizeof(params), p, q);
            macro_begin(macro_name, params);
            if (Pass == 2UL)
                listing_library_line(line, library_base +
                                     (unsigned long)lines_read - 1UL, 0);
            in_macro = 1;
        } else {
            p = line;
            while (*p == ' ' || *p == '\t')
                ++p;
            q = p + strlen(p);
            while (q > p && (q[-1] == '\r' || q[-1] == '\n' ||
                             q[-1] == ' ' || q[-1] == '\t'))
                --q;
            trim_range(mnemonic, sizeof(mnemonic), p, q);
            if (name_equal(mnemonic, "endm")) {
                if (Pass == 2UL)
                    listing_library_line(line, library_base +
                                         (unsigned long)lines_read - 1UL, 1);
                macro_end();
                break;
            }
            if (Pass == 2UL)
                listing_library_line(line, library_base +
                                     (unsigned long)lines_read - 1UL, 1);
            macro_add_line(line);
        }
    }
    fclose(fp);
    macro = find_macro(name);
    if (macro != (struct macro_def *)0) {
        macro->library_lines = lines_read;
        LineNo += (unsigned long)lines_read;
    }
    return macro != (struct macro_def *)0;
}

static void list_library_macro_source(char *name)
{
    char path[512];
    char line[ASM56000_INPUT_LINE_CAP];
    char *path_start;
    char *path_end;
    char path_part[256];
    unsigned path_len;
    unsigned long base;
    unsigned long line_no;
    unsigned long count;
    char *p;
    char *q;
    FILE *fp;
    int in_macro;

    if (MacroPath == (char *)0)
        return;
    fp = (FILE *)0;
    path_start = MacroPath;
    while (path_start != (char *)0 && *path_start != '\0') {
        path_end = strchr(path_start, ';');
        if (path_end == (char *)0)
            path_end = path_start + strlen(path_start);
        path_len = (unsigned)(path_end - path_start);
        if (path_len >= sizeof(path_part))
            path_len = sizeof(path_part) - 1U;
        memcpy(path_part, path_start, path_len);
        path_part[path_len] = '\0';
        sprintf(path, "%s/%s.asm", path_part, name);
        fp = fopen(path, "rb");
        if (fp != (FILE *)0)
            break;
        if (*path_end == '\0')
            break;
        path_start = path_end + 1;
    }
    if (fp == (FILE *)0)
        return;
    base = LineNo;
    line_no = 0UL;
    count = 0UL;
    in_macro = 0;
    while (fgets(line, sizeof(line), fp) != (char *)0) {
        ++count;
        p = line;
        while (*p == ' ' || *p == '\t')
            ++p;
        if (!in_macro) {
            if (*p == ';' || *p == '\r' || *p == '\n' || *p == '\0')
                continue;
            q = p;
            while (*q != '\0' && *q != ' ' && *q != '\t' &&
                   *q != '\r' && *q != '\n')
                ++q;
            p = q;
            while (*p == ' ' || *p == '\t')
                ++p;
            q = p;
            while (*q != '\0' && *q != ' ' && *q != '\t' &&
                   *q != '\r' && *q != '\n')
                ++q;
            if (strncmp(p, "macro", 5) != 0 ||
                (p[5] != '\0' && p[5] != ' ' && p[5] != '\t' &&
                 p[5] != '\r' && p[5] != '\n'))
                continue;
            in_macro = 1;
            listing_library_line(line, base + count - 1UL, 0);
        } else {
            q = p;
            while (*q != '\0' && *q != ' ' && *q != '\t' &&
                   *q != '\r' && *q != '\n')
                ++q;
            if (strncmp(p, "endm", 4) == 0 &&
                (p[4] == '\0' || p[4] == ' ' || p[4] == '\t' ||
                 p[4] == '\r' || p[4] == '\n')) {
                listing_library_line(line, base + count - 1UL, 1);
                break;
            }
            listing_library_line(line, base + count - 1UL, 1);
        }
        line_no = count;
    }
    (void)line_no;
    fclose(fp);
}

int macro_expand(char *name, char *arg_text)
{
    struct macro_def *macro;
    char storage[MACRO_MAX_PARAMS][128];
    char *args[MACRO_MAX_PARAMS];
    char **lines;
    int arg_count;
    int i;

    macro = find_macro(name);
    if (macro == (struct macro_def *)0 && load_library_macro(name))
        macro = find_macro(name);
    if (macro == (struct macro_def *)0)
        return 0;
    if (Pass == 2UL && macro->library_lines != 0 &&
        !macro->library_listed) {
        list_library_macro_source(name);
        macro->library_listed = 1;
    }
    if (Pass == 2UL && macro->library_lines != 0)
        LineNo += (unsigned long)macro->library_lines;
    arg_count = split_args(arg_text, args, storage, MACRO_MAX_PARAMS);
    ActiveArgCount = arg_count;
    if (Pass == 2UL && arg_count < macro->param_count) {
        CurInstrFieldMsg = Op1Field;
        warn("Number of macro expansion arguments is less than definition");
    }
    if (Pass == 2UL && arg_count > macro->param_count) {
        CurInstrFieldMsg = Op1Field;
        warn("Number of macro expansion arguments is greater than definition");
    }
    lines = (char **)xmalloc((unsigned long)macro->body_count *
                             sizeof(char *));
    for (i = 0; i < macro->body_count; ++i)
        lines[i] = substitute(macro, macro->body[i], args, arg_count);
    input_push_lines(lines, macro->body_count);
    return 1;
}
