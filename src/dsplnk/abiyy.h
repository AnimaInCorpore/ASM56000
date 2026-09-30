/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), abiyy.h
 * Interface between the flex generated scanner (abilex.c) and the yacc
 * generated parser (abiparse.c) of the ABI expression language.
 */
#ifndef ABIYY_H
#define ABIYY_H

/* semantic value: four words (yylval 46b430, yyval 46b450, value stack elements
 * of 16 bytes = ABIVAL).  Word 0 is the value (number, character or a malloc'ed
 * string: a union, because a pointer does not fit into a long on every host),
 * word 2 the type tag that the parser fills in. */
typedef union yyword {
    unsigned long u;
    char *s;
} YYWORD;

typedef struct yystype {
    YYWORD v;                       /* +0  value */
    unsigned long w1;               /* +4  high word of a 64-bit value */
    long type;                      /* +8  type tag (ABIVAL.type) */
    long w3;                        /* +12 status (ABIVAL.status) */
} YYSTYPE;

extern YYSTYPE yylval;              /* 46b430 */
extern char *yytext;                /* 46c058 */
extern long yyleng;                 /* 46c048 */
extern long yylineno;               /* 45ceb8 */

/* debug print used by the numeric conversion messages (abidbg.c, 4335b0) */
void dbg_print_str(char *msg, char *val);

#endif
