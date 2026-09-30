/* Minimal listing hooks required by error.c and the two-pass driver. */
#include <stdio.h>
#include <string.h>

#include "asm56000.h"

extern void listing_count_external_line(void);

static int in_field(char *field, char *pos)
{
    return field != (char *)0 && *field != '\0' && field <= pos &&
           pos <= field + strlen(field);
}

/* 00413818: which line field does the scan pointer point into? */
int which_field(char *text)
{
    if (text == (char *)0)
        return 0;
    if (in_field(LabelField, text))
        return 1;
    if (in_field(MnemField, text))
        return 2;
    if (in_field(Op1Field, text))
        return 3;
    if (in_field(Op2Field, text))
        return 4;
    if (in_field(Op3Field, text))
        return 5;
    return 0;
}

void wrap_message(int indent, char *text)
{
    unsigned long left;
    unsigned long chunk;
    char *p;

    (void)indent;
    if (LstFilePtr == (FILE *)0 || text == (char *)0)
        return;
    p = text;
    left = (unsigned long)strlen(text);
    while (left != 0UL) {
        chunk = left > 80UL ? 80UL : left;
        fwrite(p, 1, chunk, LstFilePtr);
        fputs("\r\n", LstFilePtr);
        listing_count_external_line();
        p += chunk;
        left -= chunk;
    }
}

void lst_putstr(char *text)
{
    if (LstFilePtr != (FILE *)0 && text != (char *)0)
        fputs(text, LstFilePtr);
}

void lst_newline(void)
{
    if (LstFilePtr != (FILE *)0)
        fputc('\n', LstFilePtr);
}
