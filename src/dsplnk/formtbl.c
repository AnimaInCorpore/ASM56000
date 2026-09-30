/*
 * formtbl.c - DSPLNK.EXE (CLAS56 v6.3, DSP Linker 6.3.7), ABI expression
 * subsystem: the form table (0x435560-0x4356a0, 0x436210, 0x436855-0x4374bf).
 *
 * g_formarr maps the field-format names "F#W#[O#]" of the ABI grammar to the
 * routines that pack ctx->val into an instruction word (F<n> = instruction
 * format n, W<m> = which word, O<k> = operand variant).  The 50 routines
 * abi_pack_01..50 are straight-line expressions over abi_bit_range_mask,
 * abi_mask_then_shift and abi_func_pack, translated one to one from the
 * disassembly.  Every one reads the value to pack from ctx->val (+0x10); the
 * ones that call abi_func_pack use ctx->fill (+0x14, sign letter), ctx->unk_18
 * (+0x18, position) and ctx->type (+0x1c, width) as its arguments.
 */
#include "abi.h"

/* 435560 */
void form_elem_free(ABIFORM *elem)
{
    if (elem != NULL) {
        if (elem->name != NULL) {
            free(elem->name);
            elem->name = NULL;
        }
        free(elem);
    }
}

/* 43559d */
ABIFORM *form_define(char *name, ABIPACKFN fn)
{
    ABIFORM *f;

    f = (ABIFORM *)malloc(sizeof(ABIFORM));
    f->name = abi_strdup(name);
    f->fn = fn;
    return f;
}

/* 4355d6 */
ABIFORM *form_find_by_name(FormArr *arr, char *name)
{
    long i;

    if (name == NULL) {
        fprintf(stderr, "Table Search Name NULL");
        return NULL;
    }
    for (i = 0; i <= arr->max_index; i++) {
        if (strcmp((*arr->get)(arr, i)->name, name) == 0)
            return (*arr->get)(arr, i);
    }
    return NULL;
}

/* 436210: the 50 forms, in this order */
void abi_form_table_init(FormArr *arr)
{
    (*arr->add)(arr, form_define("F11W1", abi_pack_26));
    (*arr->add)(arr, form_define("F11W2", abi_pack_27));
    (*arr->add)(arr, form_define("F11W3", abi_pack_28));
    (*arr->add)(arr, form_define("F2W1", abi_pack_04));
    (*arr->add)(arr, form_define("F2W2", abi_pack_03));
    (*arr->add)(arr, form_define("F2W3", abi_pack_02));
    (*arr->add)(arr, form_define("F13W1", abi_pack_30));
    (*arr->add)(arr, form_define("F13W2", abi_pack_31));
    (*arr->add)(arr, form_define("F14W1", abi_pack_32));
    (*arr->add)(arr, form_define("F14W2", abi_pack_33));
    (*arr->add)(arr, form_define("F12W1", abi_pack_29));
    (*arr->add)(arr, form_define("F10W1", abi_pack_24));
    (*arr->add)(arr, form_define("F10W2", abi_pack_25));
    (*arr->add)(arr, form_define("F8W1", abi_pack_21));
    (*arr->add)(arr, form_define("F9W2O1", abi_pack_23));
    (*arr->add)(arr, form_define("F9W2O2", abi_pack_22));
    (*arr->add)(arr, form_define("F7W1", abi_pack_19));
    (*arr->add)(arr, form_define("F7W2", abi_pack_20));
    (*arr->add)(arr, form_define("F5W1O1", abi_pack_11));
    (*arr->add)(arr, form_define("F5W1O2", abi_pack_12));
    (*arr->add)(arr, form_define("F5W2O2", abi_pack_13));
    (*arr->add)(arr, form_define("F5W3O1", abi_pack_14));
    (*arr->add)(arr, form_define("F4W1O1", abi_pack_07));
    (*arr->add)(arr, form_define("F4W1O2", abi_pack_08));
    (*arr->add)(arr, form_define("F4W2O2", abi_pack_09));
    (*arr->add)(arr, form_define("F4W3O1", abi_pack_10));
    (*arr->add)(arr, form_define("F6W1O1", abi_pack_15));
    (*arr->add)(arr, form_define("F6W1O2", abi_pack_16));
    (*arr->add)(arr, form_define("F6W2O2", abi_pack_17));
    (*arr->add)(arr, form_define("F6W3O1", abi_pack_18));
    (*arr->add)(arr, form_define("F3W1", abi_pack_05));
    (*arr->add)(arr, form_define("F3W2", abi_pack_06));
    (*arr->add)(arr, form_define("F16W1O1", abi_pack_35));
    (*arr->add)(arr, form_define("F16W1O2", abi_pack_36));
    (*arr->add)(arr, form_define("F16W2O1", abi_pack_37));
    (*arr->add)(arr, form_define("F18W1O1", abi_pack_41));
    (*arr->add)(arr, form_define("F18W1O2", abi_pack_42));
    (*arr->add)(arr, form_define("F18W2O1", abi_pack_43));
    (*arr->add)(arr, form_define("F23W1", abi_pack_50));
    (*arr->add)(arr, form_define("F17W1O1", abi_pack_38));
    (*arr->add)(arr, form_define("F17W1O2", abi_pack_39));
    (*arr->add)(arr, form_define("F17W2O1", abi_pack_40));
    (*arr->add)(arr, form_define("F20W1", abi_pack_46));
    (*arr->add)(arr, form_define("F21W1", abi_pack_47));
    (*arr->add)(arr, form_define("F19W1", abi_pack_44));
    (*arr->add)(arr, form_define("F19W2", abi_pack_45));
    (*arr->add)(arr, form_define("F22W1", abi_pack_48));
    (*arr->add)(arr, form_define("F22W2", abi_pack_49));
    (*arr->add)(arr, form_define("F15W1", abi_pack_34));
    (*arr->add)(arr, form_define("F1W1", abi_pack_01));
}

/* 436855 F1W1 */
unsigned long abi_pack_01(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 0xa));
}

/* 43687e F2W3 */
unsigned long abi_pack_02(ABICTX *ctx)
{
    (void)ctx;
    return (abi_bit_range_mask(0, 0xd) & 0xffffUL);
}

/* 4368a4 F2W2 */
unsigned long abi_pack_03(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 0xc));
}

/* 4368cd F2W1 */
unsigned long abi_pack_04(ABICTX *ctx)
{
    return (abi_mask_then_shift(0xffffUL, abi_bit_range_mask(0xe, 0xf), 0xb, '>') | abi_mask_then_shift(ctx->val, abi_bit_range_mask(0xd, 0xf), 8, '>'));
}

/* 43692f F3W1 */
unsigned long abi_pack_05(ABICTX *ctx)
{
    return abi_mask_then_shift(ctx->val, abi_bit_range_mask(0xd, 0xf), 8, '>');
}

/* 436964 F3W2 */
unsigned long abi_pack_06(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 0xc));
}

/* 43698d F4W1O1 */
unsigned long abi_pack_07(ABICTX *ctx)
{
    return abi_mask_then_shift(~ctx->val, abi_bit_range_mask(0xe, 0xf), 0xb, '>');
}

/* 4369c4 F4W1O2 */
unsigned long abi_pack_08(ABICTX *ctx)
{
    return abi_mask_then_shift(ctx->val, abi_bit_range_mask(0xd, 0xf), 8, '>');
}

/* 4369f9 F4W2O2 */
unsigned long abi_pack_09(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 0xc));
}

/* 436a22 F4W3O1 */
unsigned long abi_pack_10(ABICTX *ctx)
{
    return (~ctx->val & abi_bit_range_mask(0, 0xd));
}

/* 436a4f F5W1O1 */
unsigned long abi_pack_11(ABICTX *ctx)
{
    return abi_mask_then_shift(ctx->val, abi_bit_range_mask(0xe, 0xf), 0xb, '>');
}

/* 436a84 F5W1O2 */
unsigned long abi_pack_12(ABICTX *ctx)
{
    return abi_mask_then_shift(ctx->val, abi_bit_range_mask(0xd, 0xf), 8, '>');
}

/* 436ab9 F5W2O2 */
unsigned long abi_pack_13(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 0xc));
}

/* 436ae2 F5W3O1 */
unsigned long abi_pack_14(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 0xd));
}

/* 436b0b F6W1O1 */
unsigned long abi_pack_15(ABICTX *ctx)
{
    return abi_mask_then_shift(ctx->val, abi_bit_range_mask(0xe, 0xf), 0xb, '>');
}

/* 436b40 F6W1O2 */
unsigned long abi_pack_16(ABICTX *ctx)
{
    return abi_mask_then_shift(ctx->val, abi_bit_range_mask(0xd, 0xf), 8, '>');
}

/* 436b75 F6W2O2 */
unsigned long abi_pack_17(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 0xc));
}

/* 436b9e F6W3O1 */
unsigned long abi_pack_18(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 0xd));
}

/* 436bc7 F7W1 */
unsigned long abi_pack_19(ABICTX *ctx)
{
    return abi_mask_then_shift(ctx->val, abi_bit_range_mask(0xd, 0xf), 8, '>');
}

/* 436bfc F7W2 */
unsigned long abi_pack_20(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 0xc));
}

/* 436c25 F8W1 */
unsigned long abi_pack_21(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 6));
}

/* 436c4e F9W2O2 */
unsigned long abi_pack_22(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 5));
}

/* 436c77 F9W2O1 */
unsigned long abi_pack_23(ABICTX *ctx)
{
    return abi_mask_then_shift(ctx->val, abi_bit_range_mask(0, 5), 6, '<');
}

/* 436cac F10W1 */
unsigned long abi_pack_24(ABICTX *ctx)
{
    return abi_mask_then_shift(ctx->val, abi_bit_range_mask(0xd, 0xe), 8, '>');
}

/* 436ce1 F10W2 */
unsigned long abi_pack_25(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 0xc));
}

/* 436d0a F11W1 */
unsigned long abi_pack_26(ABICTX *ctx)
{
    return (abi_mask_then_shift(ctx->val, abi_bit_range_mask(0x1e, 0x1f), 0x1b, '>') | abi_mask_then_shift(ctx->val, abi_bit_range_mask(0xd, 0xf), 8, '>'));
}

/* 436d6e F11W2 */
unsigned long abi_pack_27(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 0xc));
}

/* 436d97 F11W3 */
unsigned long abi_pack_28(ABICTX *ctx)
{
    return abi_mask_then_shift(ctx->val, abi_bit_range_mask(0x10, 0x1d), 0x10, '>');
}

/* 436dcc F12W1 */
unsigned long abi_pack_29(ABICTX *ctx)
{
    return abi_mask_then_shift(ctx->val, abi_bit_range_mask(0, 4), 0, '>');
}

/* 436e01 F13W1 */
unsigned long abi_pack_30(ABICTX *ctx)
{
    return abi_mask_then_shift(~ctx->val, abi_bit_range_mask(0xd, 0xf), 8, '>');
}

/* 436e38 F13W2 */
unsigned long abi_pack_31(ABICTX *ctx)
{
    return (~ctx->val & abi_bit_range_mask(0, 0xc));
}

/* 436e65 F14W1 */
unsigned long abi_pack_32(ABICTX *ctx)
{
    return abi_mask_then_shift(ctx->val, abi_bit_range_mask(0xd, 0xf), 8, '>');
}

/* 436e9a F14W2 */
unsigned long abi_pack_33(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 0xc));
}

/* 436ec3 F15W1 */
unsigned long abi_pack_34(ABICTX *ctx)
{
    unsigned long t1;

    t1 = abi_func_pack(ctx->val, (int)ctx->fill, (int)ctx->unk_18, (int)ctx->type);
    return abi_mask_then_shift(t1, abi_bit_range_mask(0, 7), 1, '<');
}

/* 436f26 F16W1O1 */
unsigned long abi_pack_35(ABICTX *ctx)
{
    return abi_mask_then_shift(ctx->val, abi_bit_range_mask(0xd, 0xf), 8, '>');
}

/* 436f5b F16W1O2 */
unsigned long abi_pack_36(ABICTX *ctx)
{
    unsigned long t1;

    t1 = abi_func_pack(ctx->val, (int)ctx->fill, (int)ctx->unk_18, (int)ctx->type);
    return (t1 & abi_bit_range_mask(0, 4));
}

/* 436fb2 F16W2O1 */
unsigned long abi_pack_37(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 0xc));
}

/* 436fdb F17W1O1 */
unsigned long abi_pack_38(ABICTX *ctx)
{
    return abi_mask_then_shift(~ctx->val, abi_bit_range_mask(0xd, 0xf), 8, '>');
}

/* 437012 F17W1O2 */
unsigned long abi_pack_39(ABICTX *ctx)
{
    unsigned long t1;

    t1 = abi_func_pack(ctx->val, (int)ctx->fill, (int)ctx->unk_18, (int)ctx->type);
    return (t1 & abi_bit_range_mask(0, 4));
}

/* 437069 F17W2O1 */
unsigned long abi_pack_40(ABICTX *ctx)
{
    return (~ctx->val & abi_bit_range_mask(0, 0xc));
}

/* 437096 F18W1O1 */
unsigned long abi_pack_41(ABICTX *ctx)
{
    return abi_mask_then_shift(ctx->val, abi_bit_range_mask(0xd, 0xf), 8, '>');
}

/* 4370cb F18W1O2 */
unsigned long abi_pack_42(ABICTX *ctx)
{
    unsigned long t1;

    t1 = abi_func_pack(ctx->val, (int)ctx->fill, (int)ctx->unk_18, (int)ctx->type);
    return (t1 & abi_bit_range_mask(0, 4));
}

/* 437122 F18W2O1 */
unsigned long abi_pack_43(ABICTX *ctx)
{
    return (ctx->val & abi_bit_range_mask(0, 0xc));
}

/* 43714b F19W1 */
unsigned long abi_pack_44(ABICTX *ctx)
{
    unsigned long t1;

    t1 = abi_func_pack(ctx->val, (int)ctx->fill, (int)ctx->unk_18, (int)ctx->type);
    return ((abi_mask_then_shift(t1, abi_bit_range_mask(0x13, 0x13), 8, '>') | abi_mask_then_shift(t1, abi_bit_range_mask(0x10, 0x12), 0x10, '>')) | abi_mask_then_shift(t1, abi_bit_range_mask(0xc, 0xe), 7, '>'));
}

/* 437202 F19W2 */
unsigned long abi_pack_45(ABICTX *ctx)
{
    unsigned long t1;

    t1 = abi_func_pack(ctx->val, (int)ctx->fill, (int)ctx->unk_18, (int)ctx->type);
    return (abi_mask_then_shift(t1, abi_bit_range_mask(0xf, 0xf), 0xf, '>') | abi_mask_then_shift(t1, abi_bit_range_mask(0, 0xb), 1, '<'));
}

/* 43728f F20W1 */
unsigned long abi_pack_46(ABICTX *ctx)
{
    unsigned long t1;

    t1 = abi_func_pack(ctx->val, (int)ctx->fill, (int)ctx->unk_18, (int)ctx->type);
    return abi_mask_then_shift(t1, abi_bit_range_mask(0, 4), 0, '>');
}

/* 4372e3 F21W1 */
unsigned long abi_pack_47(ABICTX *ctx)
{
    unsigned long t1;

    t1 = abi_func_pack(ctx->val, (int)ctx->fill, (int)ctx->unk_18, (int)ctx->type);
    return abi_mask_then_shift(t1, abi_bit_range_mask(0, 5), 0, '>');
}

/* 437337 F22W1 */
unsigned long abi_pack_48(ABICTX *ctx)
{
    unsigned long t1;

    t1 = abi_func_pack(ctx->val, (int)ctx->fill, (int)ctx->unk_18, (int)ctx->type);
    return abi_mask_then_shift(t1, abi_bit_range_mask(0xc, 0xe), 7, '>');
}

/* 43739a F22W2 */
unsigned long abi_pack_49(ABICTX *ctx)
{
    unsigned long t1;

    t1 = abi_func_pack(ctx->val, (int)ctx->fill, (int)ctx->unk_18, (int)ctx->type);
    return (abi_mask_then_shift(t1, abi_bit_range_mask(0xf, 0xf), 0xf, '>') | abi_mask_then_shift(t1, abi_bit_range_mask(0, 0xb), 1, '<'));
}

/* 437427 F23W1 */
unsigned long abi_pack_50(ABICTX *ctx)
{
    unsigned long t1;

    t1 = abi_func_pack(ctx->val, (int)ctx->fill, (int)ctx->unk_18, (int)ctx->type);
    return (t1 & abi_bit_range_mask(0, 4));
}
