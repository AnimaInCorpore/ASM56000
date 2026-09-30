/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), error.c
 * Reconstructed from 004098b0-0040a148.
 *
 * All message functions take fixed arguments; callers build formatted text
 * with sprintf first.  Diagnostics go to err_fp (stdout), prefixed with the
 * location context kept in cur_infile / cur_scnum / cur_section /
 * cur_symidx / src_line / ctl_lineno.  (The three helpers 408b90/408ba1/
 * 408bba that follow arith.c in the binary belong to arith.c.)
 */
#include "dsplnk.h"

/* "**** [File %s, Module %s" + ", Line %ld" or ", Section ..., Symbol ..."
   [+ ", Source line %ld"]; the caller prints the closing "]: ..." part. */
static void print_context(void)
{
    MODULE *mod;
    char *secname;

    mod = cur_infile->module;
    fprintf(err_fp, "**** [File %s, Module %s", cur_infile->name,
            (mod == NULL || mod->name == NULL) ? cur_infile->name : mod->name);
    if (ctl_lineno != 0) {
        fprintf(err_fp, ", Line %ld", ctl_lineno);
    } else if (cur_scnum >= 0) {
        secname = cur_section == NULL ? NULL : cur_section->node->sname->name;
        if (secname == NULL)
            fprintf(err_fp, ", Section %ld, Symbol %ld", cur_scnum, cur_symidx);
        else
            fprintf(err_fp, ", Section %s, Symbol %ld", secname, cur_symidx);
        if (src_line != 0)
            fprintf(err_fp, ", Source line %ld", src_line);
    }
}

/* 004098b0: never suppressed.  MSVC's remove() fails on a file this process
   still has open, so the partial object survives a fatal error while obj_fp
   is open; dsplnk.c must set obj_fp to NULL after closing it. */
void lnk_fatal1(char *msg)
{
    if (cur_infile == NULL) {
        fprintf(err_fp, "**** FATAL --- %s\n", msg);
    } else {
        print_context();
        fprintf(err_fp, "]: FATAL --- %s\n", msg);
    }
    if (obj_name != NULL && (obj_fp == NULL || obj_fp == stdout))
        remove(obj_name);
    exit(-1);
}

/* 00409a25 */
void lnk_error1(char *msg)
{
    if (suppress_errors) {
        suppressed_errors++;
        return;
    }
    if (cur_infile == NULL) {
        if (err_symbol[0] == '\0')
            fprintf(err_fp, "**** ERROR --- %s\n", msg);
        else
            fprintf(err_fp, "**** ERROR --- %s: %s\n", msg, err_symbol);
    } else {
        print_context();
        if (err_symbol[0] == '\0')
            fprintf(err_fp, "]: ERROR --- %s\n", msg);
        else
            fprintf(err_fp, "]: ERROR --- %s: %s\n", msg, err_symbol);
    }
    error_count++;
}

/* 00409bfd */
void lnk_error2(char *msg, char *arg)
{
    if (suppress_errors) {
        suppressed_errors++;
        return;
    }
    if (cur_infile == NULL) {
        fprintf(err_fp, "**** ERROR --- %s: %s\n", msg, arg);
    } else {
        print_context();
        fprintf(err_fp, "]: ERROR --- %s: %s\n", msg, arg);
    }
    error_count++;
}

/* 00409d88: suppressed warnings are not counted */
void lnk_warning1(char *msg)
{
    if (suppress_errors)
        return;
    if (cur_infile == NULL) {
        if (err_symbol[0] == '\0')
            fprintf(err_fp, "**** WARNING --- %s\n", msg);
        else
            fprintf(err_fp, "**** WARNING --- %s: %s\n", msg, err_symbol);
    } else {
        print_context();
        if (err_symbol[0] == '\0')
            fprintf(err_fp, "]: WARNING --- %s\n", msg);
        else
            fprintf(err_fp, "]: WARNING --- %s: %s\n", msg, err_symbol);
    }
    warning_count++;
}

/* 00409f4d */
void lnk_warning2(char *msg, char *arg)
{
    if (suppress_errors)
        return;
    if (cur_infile == NULL) {
        fprintf(err_fp, "**** WARNING --- %s: %s\n", msg, arg);
    } else {
        print_context();
        fprintf(err_fp, "]: WARNING --- %s: %s\n", msg, arg);
    }
    warning_count++;
}

/* 0040a0ca */
void lnk_cmdline_fatal1(char *msg)
{
    fprintf(stdout, "%s: %s\n", progname, msg);
    exit(-1);
}

/* 0040a0f6 */
void lnk_cmdline_fatal2(char *msg, char *arg)
{
    fprintf(stdout, "%s: %s: %s\n", progname, msg, arg);
    exit(-1);
}

/* 0040a126 */
void lnk_cmdline_warn1(char *msg)
{
    fprintf(stdout, "%s: %s\n", progname, msg);
}
