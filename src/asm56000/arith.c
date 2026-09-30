/* Small arithmetic-layer helpers shared by addressing-mode parsing. */
#include <ctype.h>
#include <string.h>

#include "asm56000.h"

int match_register_name(char **p)
{
    char token[8];
    char *start;
    unsigned long n;
    int i;
    static char *names[] = {
        "a", "b", "x", "y", "x0", "y0", "x1", "y1",
        "a0", "b0", "a1", "b1",
        "a2", "b2", "ab", "ba", "a10", "b10", "m0", "m1",
        "m2", "m3", "m4", "m5", "m6", "m7", "mr", "n0", "n1",
        "n2", "n3", "n4", "n5", "n6", "n7", "omr", "r0", "r1",
        "r2", "r3", "r4", "r5", "r6", "r7", "sp", "sr", "ssh",
        "ssl", "la", "lc", "ccr"
    };
    static int ids[] = {
        2, 3, 0, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
        0x26, 0x27,
        0x28, 0x29, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24,
        0x25, 0x31, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c,
        0x1d, 0x2a, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14,
        0x15, 0x30, 0x2b, 0x2e, 0x2f, 0x2c, 0x2d, 0x32
    };

    if (p == (char **)0 || *p == (char *)0)
        return -1;
    start = *p;
    n = 0UL;
    while ((isalnum((unsigned char)start[n]) || start[n] == '_') &&
           n + 1UL < sizeof(token)) {
        token[n] = (char)tolower((unsigned char)start[n]);
        ++n;
    }
    if (n == 0UL || (isalnum((unsigned char)start[n]) ||
                     start[n] == '_') || n >= sizeof(token))
        return -1;
    token[n] = '\0';
    for (i = 0; i < (int)(sizeof(ids) / sizeof(ids[0])); ++i) {
        if (strcmp(token, names[i]) == 0) {
            *p = start + n;
            return ids[i];
        }
    }
    return -1;
}

unsigned long check_field_size(unsigned long value, int width_code)
{
    if (width_code == 6)
        return value <= 0x3fUL;
    if (width_code == 8)
        return value <= 0xffUL;
    if (width_code == 12)
        return value <= 0xfffUL;
    return 0UL;
}
