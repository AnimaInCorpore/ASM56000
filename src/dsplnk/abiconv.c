/*
 * abiconv.c - DSPLNK.EXE (CLAS56 v6.3, DSP Linker 6.3.7), ABI expression
 * subsystem: conversion between the value types of the grammar
 * (0x4385f0-0x438b5f).  The value record ABIVAL is {lo, hi, type, status};
 * types are 0 = 16-bit, 1 = int, 2 = unsigned, 3 = 64-bit.  status is 2 for a
 * conversion done, 1 for an incompatible source type, 0 for "already of that
 * type".  The original returns the destination record through a hidden
 * pointer (first argument), as here.
 */
#include "abi.h"

/* sign-extended low 16 bits as a 32-bit pattern (movsx word ptr) */
static unsigned long sx16(unsigned long v)
{
    v &= 0xffffUL;
    if (v & 0x8000UL)
        v |= 0xffff0000UL;
    return v;
}

/* 4387f2: to type 0 (16-bit; the value words are kept) */
ABIVAL *abi_conv_case1(ABIVAL *dst, ABIVAL *val)
{
    ABIVAL r;

    r = *val;
    r.type = 0;
    r.status = 2;
    if (val->type != 1 && val->type != 2 && val->type != 3)
        r.status = 1;
    *dst = r;
    return dst;
}

/* 438889: to type 2 */
ABIVAL *abi_conv_case2(ABIVAL *dst, ABIVAL *val)
{
    ABIVAL r;

    r = *val;
    r.type = 2;
    r.status = 2;
    if (val->type == 0)
        r.lo = sx16(val->lo);
    else if (val->type == 1 || val->type == 3)
        r.lo = val->lo;
    else
        r.status = 1;
    *dst = r;
    return dst;
}

/* 43891b: to type 1 (the 16-bit case falls through to the plain copy) */
ABIVAL *abi_conv_case3(ABIVAL *dst, ABIVAL *val)
{
    ABIVAL r;

    r = *val;
    r.type = 1;
    r.status = 2;
    if (val->type == 0 || val->type == 2 || val->type == 3)
        r.lo = val->lo;
    else
        r.status = 1;
    *dst = r;
    return dst;
}

/* 4389ab: to type 3 (64-bit: hi = sign / zero extension) */
ABIVAL *abi_conv_case4(ABIVAL *dst, ABIVAL *val)
{
    ABIVAL r;

    r = *val;
    r.type = 3;
    r.status = 2;
    if (val->type == 1) {
        r.lo = val->lo & 0xffffffffUL;
        r.hi = (r.lo & 0x80000000UL) ? 0xffffffffUL : 0UL;
    } else if (val->type == 2) {
        r.lo = val->lo & 0xffffffffUL;
        r.hi = 0;
    } else if (val->type == 0) {
        r.lo = sx16(val->lo);
        r.hi = (r.lo & 0x80000000UL) ? 0xffffffffUL : 0UL;
    } else {
        r.status = 1;
    }
    *dst = r;
    return dst;
}

/* 438679 */
ABIVAL *abi_lnk_convert_type(ABIVAL *dst, ABIVAL *val, long totype)
{
    ABIVAL r;
    ABIVAL t;

    if (val->type == totype) {
        r = *val;
        r.status = 0;
        *dst = r;
        return dst;
    }
    switch (totype) {
    case 0:
        r = *abi_conv_case1(&t, val);
        break;
    case 1:
        r = *abi_conv_case3(&t, val);
        break;
    case 2:
        r = *abi_conv_case2(&t, val);
        break;
    case 3:
        r = *abi_conv_case4(&t, val);
        break;
    default:
        r.lo = 0;
        r.hi = 0;
        r.type = 0;
        r.status = 1;
        fprintf(stderr, "Parser Error:  %s in Location %s \n",
                "Requested Data Type Not Found!", "abi_lnk_convert_type");
        lnk_error1("Requested Data Type Not Found!");
        break;
    }
    *dst = r;
    return dst;
}

/* 4385f0 */
ABIVAL *abi_lnk_extract_val(ABIVAL *dst, ABIVAL *val, long type)
{
    ABIVAL t, r;

    r = *abi_lnk_convert_type(&t, val, type);
    if (r.status != 2 && r.status == 1) {
        fprintf(stderr, "Parser Error:  %s in Location %s \n",
                "Can not Convert to Incompatible Data Type", "abi_lnk_extract_val");
        lnk_error1("Can not Convert to Incompatible Data Type");
    }
    *dst = r;
    return dst;
}
