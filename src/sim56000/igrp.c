/* igrp.c - SIM56000.EXE v6.3 (CLAS56), instruction group statistics (module igrp, 0x401140-0x401a30):
 * methods of the instruction group descriptor used by the profiler: kind remapping, per group/operand mode
 * counters, mode name labels, and small predicates on the statistics record (struct insn_stat, insstat.c). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sim56000.h"
#include "simdata.h"
#include "simproto.h"

/* the control group uses its own kind numbers unless the record has the aux field 0x10 */
long igrp_map_kind(void *vrec)
{
    struct insn_stat *rec = (struct insn_stat *)vrec;
    long kind = rec->cat;
    int aux16 = (rec->aux != 0x10);

    switch (kind) {
    case 0:
        return 0;
    case 0x10:
        return (aux16 ? 0x4f : 0) + 0x10;
    case 0x14:
        return (aux16 ? 0x4c : 0) + 0x14;
    case 0x2b:
        return (aux16 ? 0x36 : 0) + 0x2b;
    case 0x2c:
        return (aux16 ? 0x36 : 0) + 0x2c;
    case 0x49:
        return 0x48;
    case 0x4b:
        return 0x4a;
    case 0x4f:
        return 0x4e;
    case 0x51:
        return 0x50;
    }
    return kind;
}

char *igrp_names_hook(long id)
{
    return mnemonic_name(id);
}

/* labels of the report rows: tab[group * 16 + operand mode] */
void igrp_fill_mode_names(char **tab)
{
    tab[12] = "opcode reg1,reg2,acc";
    tab[10] = "opcode reg,#n,acc";
    tab[28] = "opcode reg,acc";
    tab[26] = "opcode immediate,acc";
    tab[37] = "opcode #n,s:indirect";
    tab[41] = "opcode #n,s:absolute";
    tab[44] = "opcode #n,reg";
    tab[60] = "opcode reg1,reg2,acc";
    tab[58] = "opcode immediate,reg,acc";
    tab[69] = "opcode #n,s:indirect,label";
    tab[73] = "opcode #n,s:absolute,label";
    tab[76] = "opcode #n,reg,label";
    tab[89] = "opcode label";
    tab[85] = "opcode indirect";
    tab[92] = "opcode relative_label";
    tab[94] = "opcode relative_indirect";
    tab[101] = "opcode s:indirect,label";
    tab[105] = "opcode s:absolute,label";
    tab[106] = "opcode immediate,label";
    tab[108] = "opcode reg,label";
    tab[117] = "opcode s:indirect,dst";
    tab[121] = "opcode s:absolute,dst";
    tab[122] = "opcode immediate,dst";
    tab[124] = "opcode reg,dst";
    tab[125] = "opcode s:(Rn+absolute),dst";
    tab[133] = "opcode src,s:indirect";
    tab[137] = "opcode src,s:absolute";
    tab[140] = "opcode src,reg";
    tab[141] = "opcode src,s:(Rn+absolute)";
}

/* operand mode code -> report column */
long igrp_mode_bucket(long mode)
{
    switch (mode) {
    case 0:
    case 9:
    case 10:
    case 0xc:
    case 0xd:
    case 0xe:
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 8:
        return 5;
    default:
        abort();
    }
    return mode;
}

/* count one executed instruction into the group / operand mode counters */
void igrp_count_instr(void *vrec)
{
    struct insn_stat *rec = (struct insn_stat *)vrec;
    struct stat_link *n;
    long *p;
    long kind, g;

    kind = igrp_map_kind(rec);
    switch (kind) {
    case 0:
        prof_ctx->grp[7][0]++;
        prof_ctx->grp[7][igrp_mode_bucket(rec->op[0].w[0])]++;
        prof_ctx->grp[8][0]++;
        p = &prof_ctx->grp[8][igrp_mode_bucket(rec->op[1].w[0])];
        break;
    case 2: case 3: case 5: case 6:
        prof_ctx->grp[2][0]++;
        p = &prof_ctx->grp[2][igrp_mode_bucket(rec->op[1].w[0])];
        break;
    case 8: case 10:
        prof_ctx->grp[6][0]++;
        p = &prof_ctx->grp[6][igrp_mode_bucket(rec->op[0].w[0])];
        break;
    case 0x10: case 0x14: case 0x2b: case 0x2c: case 0x5f: case 0x60: case 0x61: case 0x62:
        prof_ctx->grp[5][0]++;
        p = &prof_ctx->grp[5][igrp_mode_bucket(rec->op[0].w[0])];
        break;
    case 0x11: case 0x12: case 0x13: case 0x15: case 0x2d: case 0x2e: case 0x2f: case 0x30:
        prof_ctx->grp[4][0]++;
        p = &prof_ctx->grp[4][igrp_mode_bucket(rec->op[1].w[0])];
        break;
    case 0x33: case 0x36: case 0x3b: case 0x41: case 0x55: case 0x5a:
        prof_ctx->grp[1][0]++;
        p = &prof_ctx->grp[1][igrp_mode_bucket(rec->op[0].w[0])];
        break;
    case 0x37: case 0x38: case 0x42: case 0x43: case 0x45:
        prof_ctx->grp[3][0]++;
        p = &prof_ctx->grp[3][igrp_mode_bucket(rec->op[0].w[0])];
        break;
    case 0x40: case 0x48: case 0x4a: case 0x4e: case 0x50:
        prof_ctx->grp[0][0]++;
        p = &prof_ctx->grp[0][igrp_mode_bucket(rec->op[1].w[0])];
        break;
    default:
        p = NULL;
        break;
    }
    if (p != NULL)
        (*p)++;
    (void)g;
    for (n = rec->link; n != NULL; n = n->next) {
        prof_ctx->grp[7][0]++;
        prof_ctx->grp[7][igrp_mode_bucket(n->ops[0].w[0])]++;
        prof_ctx->grp[8][0]++;
        prof_ctx->grp[8][igrp_mode_bucket(n->ops[1].w[0])]++;
    }
}

/* count the executed instruction by kind and number of parallel moves */
void igrp_method_401700(void *vstat)
{
    struct insn_stat *stat = (struct insn_stat *)vstat;
    long kind, n, cls, flag;

    kind = igrp_map_kind(stat);
    if (prof_ctx->kind_on[kind] == 0)
        return;
    if (stat->link == NULL)
        n = 0;
    else
        n = (stat->link->next != NULL) + 1;
    if (n == 0) {
        prof_ctx->cnt_plain[igrp_map_kind(stat)]++;
    } else if (n == 1) {
        prof_ctx->cnt_pm1[igrp_map_kind(stat)]++;
        if (stat->cat == 0)
            prof_ctx->cnt_pm[0]++;
        else
            prof_ctx->cnt_pm[1]++;
    } else if (n == 2) {
        prof_ctx->cnt_pm2[igrp_map_kind(stat)]++;
        if (stat->cat == 0) {
            prof_ctx->cnt_pm[2]++;
            if (stat_lmove_class(stat, &cls, &flag) == 0)
                prof_ctx->cnt_pm[4]++;
        } else {
            prof_ctx->cnt_pm[3]++;
            if (stat_lmove_class(stat, &cls, &flag) == 0)
                prof_ctx->cnt_pm[5]++;
        }
    }
}

/* 1 for the instructions that are not a plain conditional branch/jump form of kinds 0x11-0x15, 0x2d-0x30 */
long igrp_method_401860(void *vstat)
{
    struct insn_stat *stat = (struct insn_stat *)vstat;
    long k = stat->cat;

    if (stat->aux == 0x10 && k != 0x2d && k != 0x2f && k != 0x2e && k != 0x30 && k != 0x11 && k != 0x12 &&
        k != 0x13 && k != 0x15)
        return 0;
    return 1;
}

long igrp_method_4018b0(void *vstat)
{
    switch (((struct insn_stat *)vstat)->cat) {
    case 0x12: case 0x14: case 0x15: case 0x2c: case 0x2e: case 0x30:
        return 1;
    }
    return 0;
}

long igrp_method_401910(void *vstat)
{
    switch (((struct insn_stat *)vstat)->cat) {
    case 8: case 9: case 10: case 0xb: case 0x23: case 0x27: case 0x29:
        return 0;
    }
    return 1;
}

long igrp_method_401970(void *vstat)
{
    long k = ((struct insn_stat *)vstat)->cat;

    return (k > 0x24 && k < 0x27) ? 1 : 0;
}

/* disassembly line of the record: 8 blanks, the text and a CR LF */
static char igrp_line[256];

char *igrp_method_401990(void *vstat)
{
    struct insn_stat *stat = (struct insn_stat *)vstat;

    sprintf(igrp_line, "%*s", 8, "");
    disassemble_l1((unsigned long *)&stat->word0, igrp_line + 8, stat->ccr, stat->omr, NULL);
    strcat(igrp_line, "\r\n");
    return igrp_line;
}

long igrp_method_401a10(void *vstat)
{
    switch (((struct insn_stat *)vstat)->cat) {
    case 8: case 9:
        return 1;
    case 10: case 0xb:
        return 2;
    }
    return 0;
}
