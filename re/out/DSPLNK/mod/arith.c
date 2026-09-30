/* arith: 54 functions from DSPLNK */

/* ==== FUN_00404c3a @ 00404c3a ==== */

undefined4 FUN_00404c3a(void)

{
  return 1;
}


/* ==== FUN_004058d0 @ 004058d0 ==== */

double * __cdecl FUN_004058d0(double *param_1,double *param_2)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  float10 fVar5;
  float10 fVar6;
  int local_20;
  int local_1c;
  
  if ((*(int *)(param_1 + 2) == 0x100) && (*(int *)(param_2 + 2) == 0x100)) {
    if ((DAT_00461200 == '\0') ||
       (iVar1 = FUN_00405bff((uint *)param_1,(uint *)param_2), iVar1 != 0)) {
      bVar3 = (*(uint *)(param_1 + 1) & DAT_00461f70) != 0;
      bVar4 = (*(uint *)(param_2 + 1) & DAT_00461f70) != 0;
      if (((bVar3) && (bVar4)) ||
         (((*(int *)(param_1 + 1) + *(int *)(param_2 + 1) & DAT_00461f70) == 0 &&
          ((bVar3 || (bVar4)))))) {
        local_1c = 1;
      }
      else {
        local_1c = 0;
      }
      *(uint *)(param_1 + 1) = *(int *)(param_1 + 1) + *(int *)(param_2 + 1) & DAT_00461f6c;
      uVar2 = *(int *)((int)param_1 + 4) + *(int *)((int)param_2 + 4) + local_1c;
      bVar3 = (*(uint *)((int)param_1 + 4) & DAT_00461f70) != 0;
      bVar4 = (*(uint *)((int)param_2 + 4) & DAT_00461f70) != 0;
      if (((bVar3) && (bVar4)) || (((uVar2 & DAT_00461f70) == 0 && ((bVar3 || (bVar4)))))) {
        local_20 = 1;
      }
      else {
        local_20 = 0;
      }
      *(uint *)((int)param_1 + 4) = uVar2 & DAT_00461f6c;
      *(uint *)param_1 = *(int *)param_1 + *(int *)param_2 + local_20 & DAT_00461f6c;
      thunk_FUN_0040c8ab((int)param_1);
    }
    else {
      param_1 = (double *)0x0;
    }
  }
  else if ((((ulonglong)param_1[3] & 0x1000) == 0) && (((ulonglong)param_2[3] & 0x1000) == 0)) {
    fVar5 = thunk_FUN_00408429(param_1);
    fVar6 = thunk_FUN_00408429(param_2);
    *param_1 = (double)(fVar6 + (float10)(double)fVar5);
    *(undefined4 *)(param_1 + 2) = 0x200;
    *(undefined4 *)(param_1 + 4) = 4;
    *(undefined4 *)((int)param_1 + 0x1c) = 4;
    *(undefined4 *)((int)param_1 + 0x24) = 0;
    *(undefined4 *)(param_1 + 5) = 0;
    *(undefined4 *)((int)param_1 + 0x14) = 8;
  }
  else {
    thunk_FUN_0040ca80((undefined *)param_1);
    thunk_FUN_0040ca80((undefined *)param_2);
    thunk_FUN_00409a25(s_Floating_point_not_allowed_in_re_00454a8c);
    param_1 = (double *)0x0;
  }
  return param_1;
}


/* ==== FUN_00405b12 @ 00405b12 ==== */

double * __cdecl FUN_00405b12(double *param_1,double *param_2)

{
  float10 fVar1;
  float10 fVar2;
  
  if ((*(int *)(param_1 + 2) == 0x100) && (*(int *)(param_2 + 2) == 0x100)) {
    thunk_FUN_004079b8(param_2);
    param_1 = thunk_FUN_004058d0(param_1,param_2);
  }
  else if ((((ulonglong)param_1[3] & 0x1000) == 0) && (((ulonglong)param_2[3] & 0x1000) == 0)) {
    fVar1 = thunk_FUN_00408429(param_1);
    fVar2 = thunk_FUN_00408429(param_2);
    *param_1 = (double)((float10)(double)fVar1 - fVar2);
    *(undefined4 *)(param_1 + 2) = 0x200;
    *(undefined4 *)(param_1 + 4) = 4;
    *(undefined4 *)((int)param_1 + 0x1c) = 4;
    *(undefined4 *)((int)param_1 + 0x24) = 0;
    *(undefined4 *)(param_1 + 5) = 0;
    *(undefined4 *)((int)param_1 + 0x14) = 8;
  }
  else {
    thunk_FUN_0040ca80((undefined *)param_1);
    thunk_FUN_0040ca80((undefined *)param_2);
    thunk_FUN_00409a25(s_Floating_point_not_allowed_in_re_00454ac0);
    param_1 = (double *)0x0;
  }
  return param_1;
}


/* ==== FUN_00405bff @ 00405bff ==== */

undefined4 __cdecl FUN_00405bff(uint *param_1,uint *param_2)

{
  bool bVar1;
  int iVar2;
  
  if (((((*param_1 & DAT_00461f70) == 0) || ((*param_2 & DAT_00461f70) != 0)) &&
      (((*param_1 & DAT_00461f70) != 0 || ((*param_2 & DAT_00461f70) == 0)))) &&
     ((iVar2 = thunk_FUN_00407988((int)param_1), iVar2 != 0 &&
      (iVar2 = thunk_FUN_00407988((int)param_2), iVar2 != 0)))) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((param_1[7] != 4) && (param_2[7] != 4)) {
    if ((DAT_00457b7c != '\0') &&
       (iVar2 = thunk_FUN_0043016a(param_1[7],param_2[7]), iVar2 == 0xa2c2a)) {
      thunk_FUN_00409a25(s_Expression_involves_incompatible_00454af4);
      thunk_FUN_0040ca80((undefined *)param_2);
      thunk_FUN_0040ca80((undefined *)param_1);
      return 0;
    }
    if (!bVar1) {
      thunk_FUN_00409a25(s_Invalid_address_expression_00454b24);
      thunk_FUN_0040ca80((undefined *)param_1);
      thunk_FUN_0040ca80((undefined *)param_2);
      return 0;
    }
    DAT_00461284 = 1;
  }
  if (((param_1[6] & 0x1000) != 0) && ((param_2[6] & 0x1000) != 0)) {
    if ((DAT_00457b7c != '\0') &&
       (((-1 < (int)param_1[0xb] && (-1 < (int)param_2[0xb])) && (param_1[0xb] != param_2[0xb])))) {
      thunk_FUN_00409a25(s_Relative_terms_from_different_se_00454b40);
      thunk_FUN_0040ca80((undefined *)param_1);
      thunk_FUN_0040ca80((undefined *)param_2);
      return 0;
    }
    if (!bVar1) {
      thunk_FUN_00409a25(s_Invalid_relative_expression_00454b74);
      thunk_FUN_0040ca80((undefined *)param_1);
      thunk_FUN_0040ca80((undefined *)param_2);
      return 0;
    }
  }
  return 1;
}


/* ==== FUN_00405dd4 @ 00405dd4 ==== */

double * __cdecl FUN_00405dd4(double *param_1,double *param_2)

{
  byte bVar1;
  float10 fVar2;
  float10 fVar3;
  int local_b0;
  int local_ac;
  uint local_a4 [13];
  uint local_70 [13];
  uint local_3c;
  uint local_38 [13];
  
  if ((*(int *)(param_1 + 2) != 0x100) || (*(int *)(param_2 + 2) != 0x100)) {
    fVar2 = thunk_FUN_00408429(param_1);
    fVar3 = thunk_FUN_00408429(param_2);
    *param_1 = (double)(fVar3 * (float10)(double)fVar2);
    *(undefined4 *)(param_1 + 2) = 0x200;
    *(undefined4 *)(param_1 + 4) = 4;
    *(undefined4 *)((int)param_1 + 0x1c) = 4;
    *(undefined4 *)((int)param_1 + 0x24) = 0;
    *(undefined4 *)(param_1 + 5) = 0;
    *(undefined4 *)((int)param_1 + 0x14) = 8;
    return param_1;
  }
  bVar1 = (*(uint *)param_1 & DAT_00461f70) != 0;
  if ((bool)bVar1) {
    thunk_FUN_004079b8(param_1);
  }
  if ((*(uint *)param_2 & DAT_00461f70) != 0) {
    thunk_FUN_004079b8(param_2);
    bVar1 = bVar1 | 2;
  }
  FUN_00407ff8(*(uint *)param_1,*(uint *)((int)param_1 + 4),*(uint *)(param_1 + 1),local_a4);
  FUN_00407ff8(*(uint *)param_2,*(uint *)((int)param_2 + 4),*(uint *)(param_2 + 1),local_38);
  FUN_00407ff8(0,0,0,local_70);
  local_3c = 0;
  for (local_b0 = 0; local_b0 < DAT_00461f64; local_b0 = local_b0 + 1) {
    for (local_ac = 0; local_ac <= local_b0; local_ac = local_ac + 1) {
      local_3c = local_3c + local_a4[local_ac] * local_38[local_b0 - local_ac];
    }
    local_70[local_b0] = local_3c & 0xff;
    local_3c = local_3c >> 8;
  }
  FUN_004080bf(local_70,(uint *)param_1,(uint *)((int)param_1 + 4),(uint *)(param_1 + 1));
  if (bVar1 == 1) {
    thunk_FUN_004079b8(param_1);
  }
  else {
    if (bVar1 == 2) {
      thunk_FUN_004079b8(param_1);
    }
    else if (bVar1 != 3) goto LAB_00405fbd;
    thunk_FUN_004079b8(param_2);
  }
LAB_00405fbd:
  thunk_FUN_0040c8ab((int)param_1);
  return param_1;
}


/* ==== FUN_00406037 @ 00406037 ==== */

double * __cdecl FUN_00406037(double *param_1,double *param_2)

{
  byte bVar1;
  float10 fVar2;
  uint local_18;
  double local_14;
  uint local_c;
  uint local_8;
  
  if ((*(int *)(param_1 + 2) != 0x100) || (*(int *)(param_2 + 2) != 0x100)) {
    fVar2 = thunk_FUN_00408429(param_2);
    local_14 = (double)fVar2;
    if (local_14 != 0.0) {
      fVar2 = thunk_FUN_00408429(param_1);
      *param_1 = (double)(fVar2 / (float10)local_14);
      *(undefined4 *)(param_1 + 2) = 0x200;
      *(undefined4 *)(param_1 + 4) = 4;
      *(undefined4 *)((int)param_1 + 0x1c) = 4;
      *(undefined4 *)((int)param_1 + 0x24) = 0;
      *(undefined4 *)(param_1 + 5) = 0;
      *(undefined4 *)((int)param_1 + 0x14) = 8;
      return param_1;
    }
    thunk_FUN_0040ca80((undefined *)param_2);
    thunk_FUN_0040ca80((undefined *)param_1);
    thunk_FUN_00409a25(s_Divide_by_zero_00454ba0);
    return (double *)0x0;
  }
  if (((*(int *)param_2 == 0) && (*(int *)((int)param_2 + 4) == 0)) && (*(int *)(param_2 + 1) == 0))
  {
    thunk_FUN_0040ca80((undefined *)param_2);
    thunk_FUN_0040ca80((undefined *)param_1);
    thunk_FUN_00409a25(s_Divide_by_zero_00454b90);
    return (double *)0x0;
  }
  bVar1 = (*(uint *)param_1 & DAT_00461f70) != 0;
  if ((bool)bVar1) {
    thunk_FUN_004079b8(param_1);
  }
  if ((*(uint *)param_2 & DAT_00461f70) != 0) {
    thunk_FUN_004079b8(param_2);
    bVar1 = bVar1 | 2;
  }
  FUN_00407df5(*(uint *)param_1,*(uint *)((int)param_1 + 4),*(uint *)(param_1 + 1),*(uint *)param_2,
               *(uint *)((int)param_2 + 4),*(uint *)(param_2 + 1),(uint *)param_1,
               (uint *)((int)param_1 + 4),(uint *)(param_1 + 1),&local_c,&local_8,&local_18);
  if (bVar1 == 1) {
    thunk_FUN_004079b8(param_1);
  }
  else {
    if (bVar1 == 2) {
      thunk_FUN_004079b8(param_1);
    }
    else if (bVar1 != 3) goto LAB_00406180;
    thunk_FUN_004079b8(param_2);
  }
LAB_00406180:
  thunk_FUN_0040c8ab((int)param_1);
  return param_1;
}


/* ==== FUN_00406230 @ 00406230 ==== */

double * __cdecl FUN_00406230(double *param_1,double *param_2)

{
  float10 fVar1;
  float10 extraout_ST0;
  double y;
  undefined4 in_stack_ffffffe0;
  undefined4 in_stack_ffffffe4;
  uint uVar2;
  uint local_18;
  double local_14;
  uint local_c;
  uint local_8;
  
  if ((*(int *)(param_1 + 2) != 0x100) || (*(int *)(param_2 + 2) != 0x100)) {
    fVar1 = thunk_FUN_00408429(param_2);
    local_14 = (double)fVar1;
    if (local_14 != 0.0) {
      y = local_14;
      fVar1 = thunk_FUN_00408429(param_1);
      fmod((double)fVar1,y,in_stack_ffffffe0,in_stack_ffffffe4);
      *param_1 = (double)extraout_ST0;
      *(undefined4 *)(param_1 + 2) = 0x200;
      *(undefined4 *)(param_1 + 4) = 4;
      *(undefined4 *)((int)param_1 + 0x1c) = 4;
      *(undefined4 *)((int)param_1 + 0x24) = 0;
      *(undefined4 *)(param_1 + 5) = 0;
      *(undefined4 *)((int)param_1 + 0x14) = 8;
      return param_1;
    }
    thunk_FUN_0040ca80((undefined *)param_2);
    thunk_FUN_0040ca80((undefined *)param_1);
    thunk_FUN_00409a25(s_Divide_by_zero_00454bc0);
    return (double *)0x0;
  }
  if (((*(int *)param_2 == 0) && (*(int *)((int)param_2 + 4) == 0)) && (*(int *)(param_2 + 1) == 0))
  {
    thunk_FUN_0040ca80((undefined *)param_2);
    thunk_FUN_0040ca80((undefined *)param_1);
    thunk_FUN_00409a25(s_Divide_by_zero_00454bb0);
    return (double *)0x0;
  }
  uVar2 = 0;
  if ((*(uint *)param_1 & DAT_00461f70) != 0) {
    thunk_FUN_004079b8(param_1);
    uVar2 = uVar2 | 1;
  }
  if ((*(uint *)param_2 & DAT_00461f70) != 0) {
    thunk_FUN_004079b8(param_2);
    uVar2 = uVar2 | 2;
  }
  FUN_00407df5(*(uint *)param_1,*(uint *)((int)param_1 + 4),*(uint *)(param_1 + 1),*(uint *)param_2,
               *(uint *)((int)param_2 + 4),*(uint *)(param_2 + 1),&local_c,&local_8,&local_18,
               (uint *)param_1,(uint *)((int)param_1 + 4),(uint *)(param_1 + 1));
  if (uVar2 == 1) {
    thunk_FUN_004079b8(param_1);
  }
  else {
    if (uVar2 == 2) {
      thunk_FUN_004079b8(param_1);
    }
    else if (uVar2 != 3) goto LAB_00406379;
    thunk_FUN_004079b8(param_2);
  }
LAB_00406379:
  thunk_FUN_0040c8ab((int)param_1);
  return param_1;
}


/* ==== FUN_00406439 @ 00406439 ==== */

uint * __cdecl FUN_00406439(uint *param_1,uint *param_2)

{
  if ((param_1[4] == 0x100) && (param_2[4] == 0x100)) {
    *param_1 = *param_1 & *param_2;
    param_1[1] = param_1[1] & param_2[1];
    param_1[2] = param_1[2] & param_2[2];
    thunk_FUN_0040c8ab((int)param_1);
  }
  else {
    thunk_FUN_0040ca80((undefined *)param_1);
    thunk_FUN_0040ca80((undefined *)param_2);
    thunk_FUN_00409a25(s_Illegal_operator_for_floating_po_00454bd0);
    param_1 = (uint *)0x0;
  }
  return param_1;
}


/* ==== FUN_004064c3 @ 004064c3 ==== */

uint * __cdecl FUN_004064c3(uint *param_1,uint *param_2)

{
  if ((param_1[4] == 0x100) && (param_2[4] == 0x100)) {
    *param_1 = *param_1 | *param_2;
    param_1[1] = param_1[1] | param_2[1];
    param_1[2] = param_1[2] | param_2[2];
    thunk_FUN_0040c8ab((int)param_1);
  }
  else {
    thunk_FUN_0040ca80((undefined *)param_1);
    thunk_FUN_0040ca80((undefined *)param_2);
    thunk_FUN_00409a25(s_Illegal_operator_for_floating_po_00454bfc);
    param_1 = (uint *)0x0;
  }
  return param_1;
}


/* ==== FUN_0040654d @ 0040654d ==== */

uint * __cdecl FUN_0040654d(uint *param_1,uint *param_2)

{
  if ((param_1[4] == 0x100) && (param_2[4] == 0x100)) {
    *param_1 = *param_1 ^ *param_2;
    param_1[1] = param_1[1] ^ param_2[1];
    param_1[2] = param_1[2] ^ param_2[2];
    thunk_FUN_0040c8ab((int)param_1);
  }
  else {
    thunk_FUN_0040ca80((undefined *)param_1);
    thunk_FUN_0040ca80((undefined *)param_2);
    thunk_FUN_00409a25(s_Illegal_operator_for_floating_po_00454c28);
    param_1 = (uint *)0x0;
  }
  return param_1;
}


/* ==== FUN_004065d7 @ 004065d7 ==== */

uint * __cdecl FUN_004065d7(uint *param_1,int *param_2)

{
  int local_8;
  
  if ((param_1[4] == 0x100) && (param_2[4] == 0x100)) {
    if ((((*param_2 == 0) && (param_2[1] == 0)) && (local_8 = param_2[2], -1 < local_8)) &&
       (local_8 <= DAT_00461f5c)) {
      while (local_8 != 0) {
        *param_1 = *param_1 << 1;
        if ((param_1[1] & DAT_00461f70) != 0) {
          *param_1 = *param_1 | 1;
        }
        param_1[1] = param_1[1] << 1;
        if ((param_1[2] & DAT_00461f70) != 0) {
          param_1[1] = param_1[1] | 1;
        }
        param_1[2] = param_1[2] << 1;
        local_8 = local_8 + -1;
      }
      thunk_FUN_0040c8ab((int)param_1);
    }
    else {
      thunk_FUN_0040ca80((undefined *)param_2);
      thunk_FUN_0040ca80((undefined *)param_1);
      thunk_FUN_00409a25(s_Invalid_shift_amount_00454c54);
      param_1 = (uint *)0x0;
    }
  }
  else {
    thunk_FUN_0040ca80((undefined *)param_1);
    thunk_FUN_0040ca80((undefined *)param_2);
    thunk_FUN_00409a25(s_Illegal_operator_for_floating_po_00454c6c);
    param_1 = (uint *)0x0;
  }
  return param_1;
}


/* ==== FUN_00406706 @ 00406706 ==== */

uint * __cdecl FUN_00406706(uint *param_1,int *param_2)

{
  int iVar1;
  int local_8;
  
  if ((param_1[4] == 0x100) && (param_2[4] == 0x100)) {
    if ((((*param_2 == 0) && (param_2[1] == 0)) && (local_8 = param_2[2], -1 < local_8)) &&
       (local_8 <= DAT_00461f5c)) {
      while (iVar1 = local_8 + -1, local_8 != 0) {
        param_1[2] = param_1[2] >> 1;
        if ((param_1[1] & 1) != 0) {
          param_1[2] = param_1[2] | DAT_00461f70;
        }
        param_1[1] = param_1[1] >> 1;
        if ((*param_1 & 1) != 0) {
          param_1[1] = param_1[1] | DAT_00461f70;
        }
        *param_1 = *param_1 >> 1;
        local_8 = iVar1;
        if ((*param_1 & DAT_00461f70 >> 1) != 0) {
          *param_1 = *param_1 | DAT_00461f70;
        }
      }
      thunk_FUN_0040c8ab((int)param_1);
    }
    else {
      thunk_FUN_0040ca80((undefined *)param_2);
      thunk_FUN_0040ca80((undefined *)param_1);
      thunk_FUN_00409a25(s_Invalid_shift_amount_00454c98);
      param_1 = (uint *)0x0;
    }
  }
  else {
    thunk_FUN_0040ca80((undefined *)param_1);
    thunk_FUN_0040ca80((undefined *)param_2);
    thunk_FUN_00409a25(s_Illegal_operator_for_floating_po_00454cb0);
    param_1 = (uint *)0x0;
  }
  return param_1;
}


/* ==== FUN_0040685f @ 0040685f ==== */

double * __cdecl FUN_0040685f(double *param_1,double *param_2)

{
  uint uVar1;
  undefined4 local_8;
  
  uVar1 = thunk_FUN_00407b01(param_1);
  if (uVar1 != 0) {
    uVar1 = thunk_FUN_00407b01(param_2);
    if (uVar1 != 0) {
      local_8 = 1;
      goto LAB_00406893;
    }
  }
  local_8 = 0;
LAB_00406893:
  *(undefined4 *)(param_1 + 1) = local_8;
  *(undefined4 *)param_1 = 0;
  *(undefined4 *)((int)param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 2) = 0x100;
  *(undefined4 *)(param_1 + 4) = 4;
  *(undefined4 *)((int)param_1 + 0x1c) = 4;
  *(undefined4 *)((int)param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 5) = 0;
  *(undefined4 *)((int)param_1 + 0x14) = DAT_00461f60;
  return param_1;
}


/* ==== FUN_004068f3 @ 004068f3 ==== */

double * __cdecl FUN_004068f3(double *param_1,double *param_2)

{
  uint uVar1;
  undefined4 local_8;
  
  uVar1 = thunk_FUN_00407b01(param_1);
  if (uVar1 == 0) {
    uVar1 = thunk_FUN_00407b01(param_2);
    if (uVar1 == 0) {
      local_8 = 0;
      goto LAB_00406927;
    }
  }
  local_8 = 1;
LAB_00406927:
  *(undefined4 *)(param_1 + 1) = local_8;
  *(undefined4 *)param_1 = 0;
  *(undefined4 *)((int)param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 2) = 0x100;
  *(undefined4 *)(param_1 + 4) = 4;
  *(undefined4 *)((int)param_1 + 0x1c) = 4;
  *(undefined4 *)((int)param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 5) = 0;
  *(undefined4 *)((int)param_1 + 0x14) = DAT_00461f60;
  return param_1;
}


/* ==== FUN_00406987 @ 00406987 ==== */

double * __cdecl FUN_00406987(double *param_1,double *param_2)

{
  thunk_FUN_00407baf(0xb,param_1,param_2);
  return param_1;
}


/* ==== FUN_004069a1 @ 004069a1 ==== */

double * __cdecl FUN_004069a1(double *param_1,double *param_2)

{
  thunk_FUN_00407baf(0xc,param_1,param_2);
  return param_1;
}


/* ==== FUN_004069bb @ 004069bb ==== */

double * __cdecl FUN_004069bb(double *param_1,double *param_2)

{
  thunk_FUN_00407baf(0xd,param_1,param_2);
  return param_1;
}


/* ==== FUN_004069d5 @ 004069d5 ==== */

double * __cdecl FUN_004069d5(double *param_1,double *param_2)

{
  thunk_FUN_00407baf(0xe,param_1,param_2);
  return param_1;
}


/* ==== FUN_004069ef @ 004069ef ==== */

double * __cdecl FUN_004069ef(double *param_1,double *param_2)

{
  thunk_FUN_00407baf(0xf,param_1,param_2);
  return param_1;
}


/* ==== FUN_00406a09 @ 00406a09 ==== */

double * __cdecl FUN_00406a09(double *param_1,double *param_2)

{
  thunk_FUN_00407baf(0x10,param_1,param_2);
  return param_1;
}


/* ==== FUN_00406a23 @ 00406a23 ==== */

void __cdecl FUN_00406a23(uint param_1,int param_2,char param_3)

{
  uint uVar1;
  int local_10;
  uint local_c;
  
  local_c = 0;
  for (local_10 = 0; local_10 < param_2; local_10 = local_10 + 1) {
    local_c = local_c << 1 | 1;
  }
  if (param_3 == 'w') {
    local_c = local_c << 1 | 1;
    if ((param_1 & 1) != 0) {
      if (DAT_004611dc == (undefined4 *)0x0) {
        thunk_FUN_00409a25(s_Pc_relative_expression_value_mus_00454d3c);
      }
      else {
        sprintf(&stack0xffffff24,s_Pc_relative_expression_value__0x_00454cdc,param_1,*DAT_004611dc,
                DAT_004611dc[4]);
        thunk_FUN_00409a25(&stack0xffffff24);
      }
    }
  }
  else if ((param_3 == 'l') && (local_c = local_c << 2 | 3, (param_1 & 3) != 0)) {
    if (DAT_004611dc == (undefined4 *)0x0) {
      thunk_FUN_00409a25(s_Pc_relative_expression_value_mus_00454dd4);
    }
    else {
      sprintf(&stack0xffffff24,s_Pc_relative_expression_value__0x_00454d70,param_1,*DAT_004611dc,
              DAT_004611dc[4]);
      thunk_FUN_00409a25(&stack0xffffff24);
    }
  }
  uVar1 = param_1 & ~local_c;
  if ((uVar1 != 0) && (uVar1 != ~local_c)) {
    thunk_FUN_00409a25(s_Pc_relative_value_out_of_range_00454e0c);
  }
  return;
}


/* ==== FUN_00406b7c @ 00406b7c ==== */

void __cdecl FUN_00406b7c(uint param_1,int param_2,char param_3)

{
  uint uVar1;
  int local_10;
  uint local_c;
  
  local_c = 0;
  for (local_10 = 0; local_10 < param_2; local_10 = local_10 + 1) {
    local_c = local_c << 1 | 1;
  }
  if (param_3 == 'w') {
    local_c = local_c << 1 | 1;
    if ((param_1 & 1) != 0) {
      if (DAT_004611dc == (undefined4 *)0x0) {
        thunk_FUN_00409a25(s_Signed_expression_value_must_be_w_00454e88);
      }
      else {
        sprintf(&stack0xffffff24,s_Signed_expression_value__0x_lx__m_00454e2c,param_1,*DAT_004611dc,
                DAT_004611dc[4]);
        thunk_FUN_00409a25(&stack0xffffff24);
      }
    }
  }
  else if ((param_3 == 'l') && (local_c = local_c << 2 | 3, (param_1 & 3) != 0)) {
    if (DAT_004611dc == (undefined4 *)0x0) {
      thunk_FUN_00409a25(s_Signed_expression_value_must_be_l_00454f18);
    }
    else {
      sprintf(&stack0xffffff24,s_Signed_expression_value__0x_lx__m_00454eb8,param_1,*DAT_004611dc,
              DAT_004611dc[4]);
      thunk_FUN_00409a25(&stack0xffffff24);
    }
  }
  uVar1 = param_1 & ~local_c;
  if ((uVar1 != 0) && (uVar1 != ~local_c)) {
    thunk_FUN_00409a25(s_Signed_value_out_of_range_00454f4c);
  }
  return;
}


/* ==== FUN_00406cd5 @ 00406cd5 ==== */

void __cdecl FUN_00406cd5(uint param_1,int param_2,char param_3)

{
  int local_10;
  uint local_c;
  
  local_c = 0;
  for (local_10 = 0; local_10 < param_2; local_10 = local_10 + 1) {
    local_c = local_c << 1 | 1;
  }
  if (param_3 == 'w') {
    local_c = local_c << 1 | 1;
    if ((param_1 & 1) != 0) {
      if (DAT_004611dc == (undefined4 *)0x0) {
        thunk_FUN_00409a25(s_Unsigned_value_must_be_word_alig_00454fc4);
      }
      else {
        sprintf(&stack0xffffff24,s_Unsigned_expression_value__0x_lx_00454f68,param_1,*DAT_004611dc,
                DAT_004611dc[4]);
        thunk_FUN_00409a25(&stack0xffffff24);
      }
    }
  }
  else if ((param_3 == 'l') && (local_c = local_c << 2 | 3, (param_1 & 3) != 0)) {
    if (DAT_004611dc == (undefined4 *)0x0) {
      thunk_FUN_00409a25(s_Unsigned_value_must_be_long_word_0045504c);
    }
    else {
      sprintf(&stack0xffffff24,s_Unsigned_expression_value__0x_lx_00454fe8,param_1,*DAT_004611dc,
              DAT_004611dc[4]);
      thunk_FUN_00409a25(&stack0xffffff24);
    }
  }
  if ((param_1 & ~local_c) != 0) {
    thunk_FUN_00409a25(s_Unsigned_value_out_of_range_00455078);
  }
  return;
}


/* ==== FUN_00406e26 @ 00406e26 ==== */

void __cdecl FUN_00406e26(uint param_1,undefined1 param_2,int param_3,char param_4)

{
  switch(param_2) {
  case 0x61:
  case 0x75:
    thunk_FUN_00406cd5(param_1,param_3,param_4);
    break;
  case 0x70:
    if (param_1 < DAT_00461f7c) {
      thunk_FUN_00409a25(s_Invalid_IO_address_00455094);
    }
    break;
  case 0x72:
    thunk_FUN_00406a23(param_1,param_3,param_4);
    break;
  case 0x73:
    thunk_FUN_00406b7c(param_1,param_3,param_4);
  }
  return;
}


/* ==== FUN_00406edd @ 00406edd ==== */

double * __cdecl FUN_00406edd(double *param_1,undefined *param_2)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  uint local_20;
  char *local_1c;
  uint local_8;
  
  local_1c = (char *)0x0;
  if (DAT_00461248 != '\0') {
    if (((ulonglong)param_1[3] & 0x1000) != 0) {
      return param_1;
    }
    if (*(int *)((int)param_1 + 0x2c) < 0) {
      return param_1;
    }
  }
  iVar2 = thunk_FUN_00407988((int)param_2);
  if (*(int *)(param_1 + 2) == 0x100) {
    if (((*(int *)((int)param_1 + 0x14) == DAT_00461f64) ||
        (*(uint *)((int)param_1 + 4) == DAT_00461f6c)) || (*(int *)((int)param_1 + 0x1c) == 4)) {
      local_20 = thunk_FUN_00407988((int)param_1);
    }
    else {
      local_20 = *(uint *)(param_1 + 1);
    }
    local_8 = local_20;
  }
  else if (DAT_00461f44 == 1) {
    local_8 = thunk_FUN_00408b90((float)*param_1);
  }
  else {
    thunk_FUN_00408616(*(undefined4 *)param_1,*(undefined4 *)((int)param_1 + 4),DAT_00461f60,
                       (uint *)param_1);
    local_8 = *(uint *)(param_1 + 1);
  }
  if (*(int *)(param_2 + 0x10) == 0x4000000) {
    uVar1 = FUN_004075f2((int)param_2);
    iVar2 = FUN_00407664((int)param_2);
    uVar3 = FUN_00407744((int)param_2);
    thunk_FUN_00406e26(local_8,uVar1,iVar2,(char)uVar3);
    goto LAB_0040748d;
  }
  if (iVar2 < -0x57) {
    if (iVar2 == -0x58) {
      if ((((int)local_8 < -0x80) || (0x7f < (int)local_8)) &&
         (((int)local_8 < 0xff80 || (0xffff < (int)local_8)))) {
        local_1c = s_Offset_value_too_large_004550c0;
      }
      goto LAB_0040748d;
    }
    if (iVar2 == -0x5eb) {
      if ((((int)local_8 < -0x4000) || (0x3fff < (int)local_8)) && (local_8 < 0xffffc000)) {
        local_1c = s_Offset_value_too_large_004550a8;
      }
      goto LAB_0040748d;
    }
switchD_0040705a_caseD_ffffffb4:
    thunk_FUN_004098b0(s_Invalid_operand_bit_size_004554a0);
  }
  else {
    switch(iVar2) {
    case 1:
      if (DAT_00461f5c <= local_8) {
        local_1c = s_Immediate_value_too_large_004551f4;
      }
      break;
    case 2:
      if ((local_8 & 1) != 0) {
        local_1c = s_Immediate_value_must_be_even_00455210;
      }
      break;
    case 5:
      if (0x1f < local_8) {
        local_1c = s_Address_value_too_large_00455230;
      }
      break;
    case 6:
      if (0x3f < local_8) {
        local_1c = s_Address_or_immediate_value_too_l_00455248;
      }
      break;
    case 7:
      if (0x7f < local_8) {
        local_1c = s_Address__immediate__or_offset_va_00455270;
      }
      break;
    case 8:
      if ((DAT_00461f44 == 0) && ((local_8 & 0xffff) == 0)) {
        local_8 = (int)local_8 >> 0x10 & 0xff;
        *(uint *)(param_1 + 1) = local_8;
      }
      if (0xff < local_8) {
        local_1c = s_Address_or_immediate_value_too_l_004552a0;
      }
      break;
    case 0xc:
      if (0xfff < local_8) {
        local_1c = s_Address_or_immediate_value_too_l_004552c8;
      }
      break;
    case 0xd:
      if (0x1fff < local_8) {
        local_1c = s_Address_or_immediate_value_too_l_004552f0;
      }
      break;
    case 0x13:
      if (0x7ffff < local_8) {
        local_1c = s_Address_or_immediate_value_too_l_00455318;
      }
      break;
    case 0x43:
      if ((local_8 & DAT_00461f70) != 0) {
        local_8 = local_8 | ~(DAT_00461f70 - 1);
      }
      if (((int)local_8 < -0x40) || (0x3f < (int)local_8)) {
        local_1c = s_Displacement_value_too_large_00455340;
      }
      break;
    case 0x45:
      if ((local_8 & DAT_00461f70) != 0) {
        local_8 = local_8 | ~(DAT_00461f70 - 1);
      }
      if (((int)local_8 < -0x100) || (0xff < (int)local_8)) {
        local_1c = s_Offset_value_too_large_00455360;
      }
      break;
    case 0x4c:
      if (((local_8 < DAT_00461f80) || (DAT_00461f74 < local_8)) &&
         ((local_8 < DAT_00461f8c || (DAT_00461f90 < local_8)))) {
        local_1c = s_Invalid_I_O_address_00455378;
      }
      break;
    case 0x55:
    case 0x56:
    case 0x57:
      if (((local_8 < DAT_00461f7c) || (DAT_00461f74 < local_8)) &&
         ((local_8 < DAT_00461f84 || (DAT_00461f88 < local_8)))) {
        local_1c = s_Invalid_I_O_address_0045538c;
      }
      break;
    case 100:
      if (local_8 == 0) {
        local_1c = s_Invalid_address_or_immediate_val_004553a0;
      }
      break;
    case 0x65:
      if (local_8 < 0x80) {
        if (local_8 == 0x40) {
          local_1c = s_Invalid_address_value_004553f4;
        }
      }
      else {
        local_1c = s_Address__immediate__or_offset_va_004553c4;
      }
      break;
    case 0x66:
      if (((local_8 < DAT_00461f7c) || (DAT_00461f74 < local_8)) &&
         ((local_8 < DAT_00461f84 || (DAT_00461f88 < local_8)))) {
        local_1c = s_Invalid_I_O_address_0045540c;
      }
      else if (local_8 == 0x40) {
        local_1c = s_Invalid_address_value_00455420;
      }
      break;
    case 0x69:
      if (local_8 < 0x20) {
        if (local_8 == 0) {
          local_1c = s_Invalid_immediate_value_00455454;
        }
      }
      else {
        local_1c = s_Immediate_value_too_large_00455438;
      }
      break;
    case 0x6a:
      if (local_8 < 0x40) {
        if (local_8 == 0) {
          local_1c = s_Invalid_immediate_value_00455488;
        }
      }
      else {
        local_1c = s_Immediate_value_too_large_0045546c;
      }
      break;
    case -0x4d:
      if ((((int)local_8 < -0x40) || (0x3f < (int)local_8)) &&
         (((int)local_8 < 0x7ffc0 || (0x7ffff < (int)local_8)))) {
        local_1c = s_Offset_value_too_large_004550d8;
      }
      break;
    default:
      goto switchD_0040705a_caseD_ffffffb4;
    case -0x37:
      if ((((int)local_8 < -0x20) || (0x1f < (int)local_8)) &&
         (((int)local_8 < 0xffe0 || (0xffff < (int)local_8)))) {
        local_1c = s_Offset_value_too_large_004550f0;
      }
      break;
    case -0x13:
      if (0x7ffff < local_8) {
        local_1c = s_Address_value_too_large_00455108;
      }
      if ((local_8 & ~DAT_00461f6c) != (*DAT_00461d90 & ~DAT_00461f6c)) {
        local_1c = s_Subroutine_address_not_on_curren_00455120;
      }
      *(uint *)(param_1 + 1) = local_8;
      break;
    case -0x10:
      if (((int)local_8 < -0x8000) || (0x7fff < (int)local_8)) {
        local_1c = s_Immediate_value_too_large_00455148;
      }
      break;
    case -0xf:
      if (((int)local_8 < -0x4000) || (0x3fff < (int)local_8)) {
        local_1c = s_Offset_or_immediate_value_too_la_00455164;
      }
      break;
    case -7:
      if (((int)local_8 < -0x80) || (0x7f < (int)local_8)) {
        local_1c = s_Offset_or_immediate_value_too_la_00455188;
      }
      break;
    case -6:
      if (((int)local_8 < -0x40) || (0x3f < (int)local_8)) {
        local_1c = s_Offset_value_too_large_004551ac;
      }
      break;
    case -5:
      if (((int)local_8 < -0x20) || (0x1f < (int)local_8)) {
        local_1c = s_Offset_value_too_large_004551c4;
      }
      break;
    case -2:
      if ((local_8 == 0) || ((int)local_8 < -0x3f)) {
        local_1c = s_Invalid_offset_value_004551dc;
      }
      break;
    case -1:
    case 0:
    }
  }
LAB_0040748d:
  if (local_1c != (char *)0x0) {
    thunk_FUN_00409a25(local_1c);
    thunk_FUN_0040ca80((undefined *)param_1);
    thunk_FUN_0040ca80(param_2);
    param_1 = (double *)0x0;
  }
  return param_1;
}


/* ==== FUN_004075f2 @ 004075f2 ==== */

undefined1 __cdecl FUN_004075f2(int param_1)

{
  int iVar1;
  undefined1 local_8;
  
  iVar1 = *(int *)(param_1 + 0x14);
  if (iVar1 == 2) {
    local_8 = (undefined1)((uint)*(undefined4 *)(param_1 + 8) >> 8);
  }
  else if (iVar1 == 3) {
    local_8 = (undefined1)((uint)*(undefined4 *)(param_1 + 8) >> 0x10);
  }
  else if (iVar1 == 4) {
    local_8 = (undefined1)((uint)*(undefined4 *)(param_1 + 4) >> 8);
  }
  else {
    thunk_FUN_00409a25(s_Error_in_size_check_function_arg_004554bc);
  }
  return local_8;
}


/* ==== FUN_00407664 @ 00407664 ==== */

void __cdecl FUN_00407664(int param_1)

{
  int iVar1;
  uint uVar2;
  char local_24;
  char local_23;
  undefined1 local_22;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  local_8 = *(uint *)(param_1 + 4) >> 8 & 0xff;
  local_c = *(uint *)(param_1 + 4) & 0xff;
  local_10 = *(uint *)(param_1 + 8) >> 0x10 & 0xff;
  local_14 = *(uint *)(param_1 + 8) >> 8 & 0xff;
  uVar2 = *(uint *)(param_1 + 8) & 0xff;
  iVar1 = *(int *)(param_1 + 0x14);
  local_18._0_1_ = (char)*(uint *)(param_1 + 8);
  local_18 = uVar2;
  if (iVar1 == 2) {
    local_24 = (char)local_18;
    local_23 = '\0';
  }
  else {
    local_14._0_1_ = (char)(*(uint *)(param_1 + 8) >> 8);
    if (iVar1 == 3) {
      if (((char)local_18 == 'w') || ((char)local_18 == 'l')) {
        local_23 = '\0';
      }
      else {
        local_23 = (char)local_18;
        local_22 = 0;
      }
      local_24 = (char)local_14;
    }
    else if (iVar1 == 4) {
      local_c._0_1_ = (char)*(uint *)(param_1 + 4);
      local_24 = (char)local_c;
      local_23 = (char)local_14;
      local_22 = 0;
    }
    else {
      thunk_FUN_00409a25(s_Error_in_size_check_function_arg_004554fc);
    }
  }
  atoi(&local_24);
  return;
}


/* ==== FUN_00407744 @ 00407744 ==== */

uint __cdecl FUN_00407744(int param_1)

{
  int iVar1;
  char cVar2;
  undefined uVar3;
  uint uVar4;
  undefined3 extraout_var;
  
  iVar1 = *(int *)(param_1 + 0x14);
  if (iVar1 == 2) {
    uVar4 = CONCAT31((int3)((uint)param_1 >> 8),0x20);
  }
  else if ((iVar1 < 3) || (4 < iVar1)) {
    uVar3 = thunk_FUN_00409a25(s_Error_in_size_check_function_arg_0045553c);
    uVar4 = CONCAT31(extraout_var,uVar3);
  }
  else {
    cVar2 = (char)*(uint *)(param_1 + 8);
    if ((cVar2 == 'w') || (cVar2 == 'l')) {
      uVar4 = *(uint *)(param_1 + 8) & 0xff;
    }
    else {
      uVar4 = 0x20;
    }
  }
  return uVar4;
}


/* ==== FUN_004077a5 @ 004077a5 ==== */

undefined * __cdecl FUN_004077a5(undefined *param_1,undefined *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(int *)(param_2 + 0x10) == 0x100) {
    uVar1 = thunk_FUN_0042f2b0(*(undefined4 *)(param_2 + 8));
    *(undefined4 *)(param_2 + 0x1c) = uVar1;
    if ((DAT_00457b7c != '\0') &&
       (iVar2 = thunk_FUN_0043016a(*(int *)(param_1 + 0x1c),*(int *)(param_2 + 0x1c)),
       iVar2 == 0xa2c2a)) {
      thunk_FUN_00409a25(s_Expression_involves_incompatible_00455598);
      thunk_FUN_0040ca80(param_2);
      thunk_FUN_0040ca80(param_1);
      param_1 = (undefined *)0x0;
    }
  }
  else {
    thunk_FUN_0040ca80(param_1);
    thunk_FUN_0040ca80(param_2);
    thunk_FUN_00409a25(s_Invalid_relative_expression_0045557c);
    param_1 = (undefined *)0x0;
  }
  return param_1;
}


/* ==== FUN_00407848 @ 00407848 ==== */

undefined * __cdecl FUN_00407848(undefined *param_1,undefined *param_2)

{
  undefined4 uVar1;
  
  if (*(int *)(param_2 + 0x10) == 0x100) {
    if (((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) ||
       (DAT_00461268 != '\0')) {
      *(uint *)(param_1 + 0x24) = *(uint *)(param_2 + 8) & 0xf;
      *(uint *)(param_2 + 8) = *(uint *)(param_2 + 8) >> 4;
      uVar1 = thunk_FUN_0042f2b0(*(uint *)(param_2 + 8) & 0xf);
      *(undefined4 *)(param_1 + 0x20) = uVar1;
      *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x20);
    }
    else {
      *(uint *)(param_1 + 0x24) = *(uint *)(param_2 + 8) & 0xffff;
      *(uint *)(param_2 + 8) = *(uint *)(param_2 + 8) >> 0x10;
      *(uint *)(param_1 + 0x20) = *(uint *)(param_2 + 8) & 0xffff;
      uVar1 = thunk_FUN_0042fc54(*(int *)(param_1 + 0x20));
      *(undefined4 *)(param_1 + 0x1c) = uVar1;
    }
  }
  else {
    thunk_FUN_0040ca80(param_1);
    thunk_FUN_0040ca80(param_2);
    thunk_FUN_00409a25(s_Invalid_relative_expression_004555c8);
    param_1 = (undefined *)0x0;
  }
  return param_1;
}


/* ==== FUN_0040793a @ 0040793a ==== */

undefined4 * __cdecl FUN_0040793a(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (param_1[4] == 0x100) {
    puVar2 = param_1;
    for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *param_2;
      param_2 = param_2 + 1;
      puVar2 = puVar2 + 1;
    }
  }
  else {
    thunk_FUN_0040ca80((undefined *)param_1);
    thunk_FUN_0040ca80((undefined *)param_2);
    thunk_FUN_00409a25(s_Invalid_source_line_number_004555e4);
    param_1 = (undefined4 *)0x0;
  }
  return param_1;
}


/* ==== FUN_00407988 @ 00407988 ==== */

undefined4 __cdecl FUN_00407988(int param_1)

{
  if (DAT_00461f4c < 4) {
    *(uint *)(param_1 + 8) =
         *(uint *)(param_1 + 8) | *(int *)(param_1 + 4) << ((byte)DAT_00461f58 & 0x1f);
  }
  return *(undefined4 *)(param_1 + 8);
}


/* ==== FUN_004079b8 @ 004079b8 ==== */

void __cdecl FUN_004079b8(double *param_1)

{
  if (*(int *)(param_1 + 2) == 0x200) {
    *param_1 = -*param_1;
  }
  else {
    thunk_FUN_00407a61((uint *)param_1);
    if (*(uint *)(param_1 + 1) == DAT_00461f6c) {
      if (*(uint *)((int)param_1 + 4) == DAT_00461f6c) {
        *(int *)param_1 = *(int *)param_1 + 1;
        *(uint *)param_1 = *(uint *)param_1 & DAT_00461f6c;
      }
      *(int *)((int)param_1 + 4) = *(int *)((int)param_1 + 4) + 1;
      *(uint *)((int)param_1 + 4) = *(uint *)((int)param_1 + 4) & DAT_00461f6c;
    }
    *(int *)(param_1 + 1) = *(int *)(param_1 + 1) + 1;
    *(uint *)(param_1 + 1) = *(uint *)(param_1 + 1) & DAT_00461f6c;
  }
  return;
}


/* ==== FUN_00407a61 @ 00407a61 ==== */

void __cdecl FUN_00407a61(uint *param_1)

{
  *param_1 = ~*param_1 & DAT_00461f6c;
  param_1[1] = ~param_1[1] & DAT_00461f6c;
  param_1[2] = ~param_1[2] & DAT_00461f6c;
  return;
}


/* ==== FUN_00407aa0 @ 00407aa0 ==== */

void __cdecl FUN_00407aa0(double *param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00407b01(param_1);
  *(uint *)(param_1 + 1) = (uint)(uVar1 == 0);
  *(undefined4 *)param_1 = 0;
  *(undefined4 *)((int)param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 2) = 0x100;
  *(undefined4 *)(param_1 + 4) = 4;
  *(undefined4 *)((int)param_1 + 0x1c) = 4;
  *(undefined4 *)((int)param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 5) = 0;
  return;
}


/* ==== FUN_00407b01 @ 00407b01 ==== */

uint __cdecl FUN_00407b01(double *param_1)

{
  uint local_10;
  uint local_c;
  uint local_8;
  
  if (*(int *)(param_1 + 2) == 0x200) {
    local_c = (uint)(*param_1 != 0.0);
    local_8 = local_c;
    if ((local_c != 0) && (*param_1 < 0.0)) {
      local_8 = 0xffffffff;
    }
  }
  else {
    if (((*(int *)param_1 == 0) && (*(int *)((int)param_1 + 4) == 0)) &&
       (*(int *)(param_1 + 1) == 0)) {
      local_10 = 0;
    }
    else {
      local_10 = 1;
    }
    local_8 = local_10;
    if ((local_10 != 0) && ((*(uint *)param_1 & DAT_00461f70) != 0)) {
      local_8 = 0xffffffff;
    }
  }
  return local_8;
}


/* ==== FUN_00407baf @ 00407baf ==== */

void __cdecl FUN_00407baf(undefined4 param_1,double *param_2,double *param_3)

{
  float10 fVar1;
  float10 fVar2;
  uint local_8;
  
  if ((*(int *)(param_2 + 2) == 0x100) && (*(int *)(param_3 + 2) == 0x100)) {
    if (*(uint *)param_2 < *(uint *)param_3) {
      local_8 = 0xffffffff;
    }
    else if (*(uint *)param_3 < *(uint *)param_2) {
      local_8 = 1;
    }
    else if (*(uint *)((int)param_2 + 4) < *(uint *)((int)param_3 + 4)) {
      local_8 = 0xffffffff;
    }
    else if (*(uint *)((int)param_3 + 4) < *(uint *)((int)param_2 + 4)) {
      local_8 = 1;
    }
    else if (*(uint *)(param_2 + 1) < *(uint *)(param_3 + 1)) {
      local_8 = 0xffffffff;
    }
    else if (*(uint *)(param_3 + 1) < *(uint *)(param_2 + 1)) {
      local_8 = 1;
    }
    else {
      local_8 = 0;
    }
    if ((local_8 != 0) &&
       ((((*(uint *)param_2 & DAT_00461f70) != 0 && ((*(uint *)param_3 & DAT_00461f70) == 0)) ||
        (((*(uint *)param_2 & DAT_00461f70) == 0 && ((*(uint *)param_3 & DAT_00461f70) != 0)))))) {
      local_8 = -local_8;
    }
  }
  else {
    fVar1 = thunk_FUN_00408429(param_2);
    fVar2 = thunk_FUN_00408429(param_3);
    if ((double)fVar2 <= (double)fVar1) {
      if ((double)fVar1 <= (double)fVar2) {
        local_8 = 0;
      }
      else {
        local_8 = 1;
      }
    }
    else {
      local_8 = 0xffffffff;
    }
  }
  switch(param_1) {
  case 0xb:
    local_8 = (uint)(local_8 == 0xffffffff);
    break;
  case 0xc:
    local_8 = (uint)(local_8 == 1);
    break;
  case 0xd:
    local_8 = (uint)(local_8 == 0);
    break;
  case 0xe:
    local_8 = (uint)(local_8 != 1);
    break;
  case 0xf:
    local_8 = (uint)(local_8 != 0xffffffff);
    break;
  case 0x10:
    local_8 = (uint)(local_8 != 0);
    break;
  default:
    thunk_FUN_004098b0(s_Compare_select_failure_00455600);
  }
  *(uint *)(param_2 + 1) = local_8;
  *(undefined4 *)param_2 = 0;
  *(undefined4 *)((int)param_2 + 4) = 0;
  *(undefined4 *)(param_2 + 2) = 0x100;
  *(undefined4 *)(param_2 + 4) = 4;
  *(undefined4 *)((int)param_2 + 0x1c) = 4;
  *(undefined4 *)((int)param_2 + 0x24) = 0;
  *(undefined4 *)(param_2 + 5) = 0;
  *(undefined4 *)((int)param_2 + 0x14) = DAT_00461f60;
  return;
}


/* ==== FUN_00407df5 @ 00407df5 ==== */

void __cdecl
FUN_00407df5(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
            uint *param_7,uint *param_8,uint *param_9,uint *param_10,uint *param_11,uint *param_12)

{
  int iVar1;
  uint uVar2;
  uint local_110 [13];
  uint local_dc;
  uint local_d8;
  undefined1 local_d4 [48];
  uint local_a4 [13];
  uint local_70 [13];
  int local_3c;
  uint local_38 [13];
  
  iVar1 = FUN_00407f95(param_4,param_5,param_6,param_1,param_2,param_3);
  if (iVar1 < 1) {
    FUN_00407ff8(0,0,0,local_a4);
    FUN_00407ff8(0,0,0,&local_d8);
    FUN_00407ff8(0,0,0,local_38);
    FUN_00407ff8(param_1,param_2,param_3,local_70);
    FUN_00407ff8(param_4,param_5,param_6,local_110);
    local_dc = FUN_004083f1((int)local_110);
    local_3c = FUN_004083f1((int)local_70);
    for (local_3c = local_3c + -2; -1 < local_3c; local_3c = local_3c + -1) {
      FUN_004081ab((int)&local_d8,(int)local_d4,local_dc - 1);
      local_d8 = local_70[local_3c];
      uVar2 = FUN_004081d5((int)local_110,(int)&local_d8,local_dc,(int)local_38);
      local_a4[local_3c] = uVar2;
    }
    FUN_004080bf(local_a4,param_7,param_8,param_9);
    FUN_004080bf(&local_d8,param_10,param_11,param_12);
  }
  else {
    *param_10 = param_1;
    *param_11 = param_2;
    *param_12 = param_3;
    *param_9 = 0;
    *param_8 = 0;
    *param_7 = 0;
  }
  return;
}


/* ==== FUN_00407f95 @ 00407f95 ==== */

int __cdecl
FUN_00407f95(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6)

{
  undefined4 local_8;
  
  if (param_1 == param_4) {
    if (param_2 == param_5) {
      if (param_3 == param_6) {
        local_8 = 0;
      }
      else {
        local_8 = (-(uint)(param_6 < param_3) & 2) - 1;
      }
    }
    else {
      local_8 = (-(uint)(param_5 < param_2) & 2) - 1;
    }
  }
  else {
    local_8 = (-(uint)(param_4 < param_1) & 2) - 1;
  }
  return local_8;
}


/* ==== FUN_00407ff8 @ 00407ff8 ==== */

void __cdecl FUN_00407ff8(uint param_1,uint param_2,uint param_3,uint *param_4)

{
  int local_8;
  
  *param_4 = param_3 & 0xff;
  param_4[DAT_00461f4c] = param_2 & 0xff;
  param_4[DAT_00461f4c * 2] = param_1 & 0xff;
  for (local_8 = 1; local_8 < DAT_00461f4c; local_8 = local_8 + 1) {
    param_3 = param_3 >> 8;
    param_4[local_8] = param_3 & 0xff;
    param_2 = param_2 >> 8;
    param_4[local_8 + DAT_00461f4c] = param_2 & 0xff;
    param_1 = param_1 >> 8;
    param_4[local_8 + DAT_00461f4c * 2] = param_1 & 0xff;
  }
  param_4[0xc] = 0;
  return;
}


/* ==== FUN_004080bf @ 004080bf ==== */

void __cdecl FUN_004080bf(uint *param_1,uint *param_2,uint *param_3,uint *param_4)

{
  int local_8;
  
  *param_4 = 0;
  *param_3 = 0;
  *param_2 = 0;
  local_8 = DAT_00461f4c;
  while (local_8 = local_8 + -1, 0 < local_8) {
    *param_2 = *param_2 | param_1[local_8 + DAT_00461f4c * 2];
    *param_2 = *param_2 << 8;
    *param_3 = *param_3 | param_1[local_8 + DAT_00461f4c];
    *param_3 = *param_3 << 8;
    *param_4 = *param_4 | param_1[local_8];
    *param_4 = *param_4 << 8;
  }
  *param_2 = *param_2 | param_1[DAT_00461f4c * 2];
  *param_3 = *param_3 | param_1[DAT_00461f4c];
  *param_4 = *param_4 | *param_1;
  return;
}


/* ==== FUN_004081ab @ 004081ab ==== */

void __cdecl FUN_004081ab(int param_1,int param_2,int param_3)

{
  while (param_3 = param_3 + -1, -1 < param_3) {
    *(undefined4 *)(param_2 + param_3 * 4) = *(undefined4 *)(param_1 + param_3 * 4);
  }
  return;
}


/* ==== FUN_004081d5 @ 004081d5 ==== */

uint __cdecl FUN_004081d5(int param_1,int param_2,uint param_3,int param_4)

{
  uint uVar1;
  bool bVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  uint local_10;
  int local_c;
  
  local_c = param_3 - 1;
  do {
    if (*(int *)(param_1 + local_c * 4) != 0) {
      local_10 = *(uint *)(param_2 + local_c * 4) / *(uint *)(param_1 + local_c * 4);
      do {
        FUN_004082d5(local_10,param_1,param_4,param_3);
        local_10 = local_10 - 1;
        bVar2 = FUN_00408331(param_4,param_2,param_3);
        uVar1 = local_10;
      } while (CONCAT31(extraout_var,bVar2) == 0);
      do {
        local_10 = uVar1;
        FUN_004082d5(local_10 + 1,param_1,param_4,param_3);
        bVar2 = FUN_00408331(param_4,param_2,param_3);
        uVar1 = local_10 + 1;
      } while (CONCAT31(extraout_var_00,bVar2) != 0);
      FUN_004082d5(local_10,param_1,param_4,param_3);
      FUN_0040838d(param_4,param_2,param_3);
      return local_10;
    }
    local_c = local_c + -1;
  } while (-1 < local_c);
  return 0;
}


/* ==== FUN_004082d5 @ 004082d5 ==== */

void __cdecl FUN_004082d5(int param_1,int param_2,int param_3,uint param_4)

{
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  for (local_c = 0; local_c < param_4; local_c = local_c + 1) {
    local_8 = local_8 + param_1 * *(int *)(param_2 + local_c * 4);
    *(uint *)(param_3 + local_c * 4) = local_8 & 0xff;
    local_8 = local_8 >> 8;
  }
  return;
}


/* ==== FUN_00408331 @ 00408331 ==== */

bool __cdecl FUN_00408331(int param_1,int param_2,int param_3)

{
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  for (local_c = 0; local_c < param_3; local_c = local_c + 1) {
    local_8 = (uint)((int)((*(int *)(param_2 + local_c * 4) - *(int *)(param_1 + local_c * 4)) -
                          local_8) < 0);
  }
  return local_8 == 0;
}


/* ==== FUN_0040838d @ 0040838d ==== */

void __cdecl FUN_0040838d(int param_1,int param_2,int param_3)

{
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  for (local_c = 0; local_c < param_3; local_c = local_c + 1) {
    local_8 = (*(int *)(param_2 + local_c * 4) - *(int *)(param_1 + local_c * 4)) - local_8;
    *(uint *)(param_2 + local_c * 4) = local_8 & 0xff;
    local_8 = (uint)((int)local_8 < 0);
  }
  return;
}


/* ==== FUN_004083f1 @ 004083f1 ==== */

int __cdecl FUN_004083f1(int param_1)

{
  undefined4 local_8;
  
  for (local_8 = DAT_00461f64 + 1; (-1 < local_8 && (*(int *)(param_1 + local_8 * 4) == 0));
      local_8 = local_8 + -1) {
  }
  return local_8 + 2;
}


/* ==== FUN_00408429 @ 00408429 ==== */

float10 __cdecl FUN_00408429(double *param_1)

{
  float10 fVar1;
  
  if (*(int *)(param_1 + 2) == 0x200) {
    fVar1 = (float10)*param_1;
  }
  else if (*(int *)((int)param_1 + 0x14) == DAT_00461f60) {
    fVar1 = thunk_FUN_0040848c(*(uint *)(param_1 + 1));
  }
  else if (*(int *)((int)param_1 + 0x14) == DAT_00461f64) {
    fVar1 = thunk_FUN_004084f1(*(uint *)((int)param_1 + 4),*(uint *)(param_1 + 1));
  }
  else {
    fVar1 = (float10)0.0;
  }
  return fVar1;
}


/* ==== FUN_0040848c @ 0040848c ==== */

float10 __cdecl FUN_0040848c(uint param_1)

{
  bool bVar1;
  double local_20;
  
  bVar1 = (param_1 & DAT_00461f70) != 0;
  if (bVar1) {
    param_1 = (~param_1 & DAT_00461f6c) + 1;
  }
  local_20 = (double)param_1;
  if (bVar1) {
    local_20 = -local_20;
  }
  return (float10)local_20;
}


/* ==== FUN_004084f1 @ 004084f1 ==== */

float10 __cdecl FUN_004084f1(uint param_1,uint param_2)

{
  bool bVar1;
  uint uVar2;
  float10 fVar3;
  double local_48;
  uint local_18;
  
  bVar1 = false;
  local_18 = 0;
  if ((param_1 == 0) && (param_2 == 0)) {
    fVar3 = (float10)0.0;
  }
  else {
    if ((param_1 & DAT_00461f70) != 0) {
      bVar1 = true;
      uVar2 = (~param_2 & DAT_00461f6c) + 1;
      if (DAT_00461f4c < 4) {
        local_18 = (uint)((uVar2 >> ((byte)DAT_00461f58 & 0x1f) & 1) != 0);
      }
      param_2 = uVar2 & DAT_00461f6c;
      param_1 = (~param_1 & DAT_00461f6c) + local_18 & DAT_00461f6c;
    }
    local_48 = (double)param_1 * (double)DAT_00461f70 * 2.0 + (double)param_2;
    if (bVar1) {
      local_48 = -local_48;
    }
    fVar3 = (float10)local_48;
  }
  return fVar3;
}


/* ==== FUN_00408616 @ 00408616 ==== */

void __cdecl FUN_00408616(undefined4 param_1,undefined4 param_2,uint param_3,uint *param_4)

{
  uint uVar1;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  if (DAT_00461288 == '\0') {
    local_18 = DAT_00461f6c;
  }
  else {
    local_18 = 0xffff;
  }
  local_10 = local_18;
  local_c = DAT_00461f70;
  if (DAT_00461288 != '\0') {
    local_c = 0x8000;
  }
  param_4[2] = 0;
  param_4[1] = 0;
  *param_4 = 0;
  if (param_3 == DAT_00461f60) {
    uVar1 = thunk_FUN_00408739((double)CONCAT44(param_2,param_1),local_c);
    param_4[2] = uVar1;
    if ((param_4[2] & local_c) != 0) {
      *param_4 = local_10;
      param_4[1] = local_10;
    }
  }
  else {
    thunk_FUN_004089f9((double)CONCAT44(param_2,param_1),&local_8,&local_14,local_c);
    param_4[1] = local_8;
    param_4[2] = local_14;
    if ((*param_4 & local_c) != 0) {
      *param_4 = local_10;
    }
  }
  if ((param_4[1] == 0) || (param_4[1] == local_10)) {
    param_4[5] = DAT_00461f60;
  }
  else {
    param_4[5] = DAT_00461f64;
  }
  param_4[4] = 0x100;
  return;
}


/* ==== FUN_00408739 @ 00408739 ==== */

uint __cdecl FUN_00408739(double param_1)

{
  longlong lVar1;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_18;
  double local_c;
  
  if (DAT_00461288 == '\0') {
    local_28 = DAT_00461f70;
    local_24 = DAT_00461f6c;
  }
  else {
    local_24 = 0xffff;
    local_28 = 0x8000;
  }
  if (-1.0 <= param_1) {
    if (param_1 < 1.0) {
      if (0.0 <= param_1) {
        local_c = param_1 * (double)local_28 + 0.5;
      }
      else {
        local_c = param_1 * (double)local_28 + -0.5;
      }
      lVar1 = _ftol();
      local_18 = (uint)lVar1;
      if (local_c - (double)(int)local_18 == 0.0) {
        local_18 = local_18 & 0xfffffffe;
      }
      if ((int)(~local_28 & local_24) < (int)local_18) {
        local_18 = ~local_28 & local_24;
      }
      local_30 = local_18 & local_24;
    }
    else {
      thunk_FUN_00409d88(s_Expression_value_outside_fractio_00455644);
      local_30 = DAT_00461f9c;
      if (DAT_00461288 != '\0') {
        local_30 = 0x7fff;
      }
    }
  }
  else {
    thunk_FUN_00409d88(s_Expression_value_outside_fractio_00455618);
    local_30 = DAT_00461f98;
    if (DAT_00461288 != '\0') {
      local_2c = 0xffff8000;
      local_30 = local_2c;
    }
  }
  return local_30;
}


/* ==== FUN_004088a3 @ 004088a3 ==== */

uint __cdecl FUN_004088a3(double param_1,uint param_2)

{
  longlong lVar1;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_18;
  double local_c;
  
  if (param_2 == 0xff) {
    local_20 = 0x80;
  }
  else {
    if (param_2 == 0xfff) {
      local_24 = 0x800;
    }
    else {
      if (param_2 == 0xffff) {
        local_28 = 0x8000;
      }
      else {
        if (param_2 == 0xfffff) {
          local_2c = 0x80000;
        }
        else {
          local_2c = DAT_00461f70;
        }
        local_28 = local_2c;
      }
      local_24 = local_28;
    }
    local_20 = local_24;
  }
  if (-1.0 <= param_1) {
    if (param_1 < 1.0) {
      if (0.0 <= param_1) {
        local_c = param_1 * (double)local_20 + 0.5;
      }
      else {
        local_c = param_1 * (double)local_20 + -0.5;
      }
      lVar1 = _ftol();
      local_18 = (uint)lVar1;
      if (local_c - (double)(int)local_18 == 0.0) {
        local_18 = local_18 & 0xfffffffe;
      }
      if ((int)(~local_20 & param_2) < (int)local_18) {
        local_18 = ~local_20 & param_2;
      }
      local_18 = local_18 & param_2;
    }
    else {
      thunk_FUN_00409d88(s_Expression_value_outside_fractio_0045569c);
      local_18 = DAT_00461f9c;
    }
  }
  else {
    thunk_FUN_00409d88(s_Expression_value_outside_fractio_00455670);
    local_18 = DAT_00461f98;
  }
  return local_18;
}


/* ==== FUN_004089f9 @ 004089f9 ==== */

void __cdecl FUN_004089f9(double param_1,uint *param_2,uint *param_3)

{
  bool bVar1;
  longlong lVar2;
  uint local_64;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_14;
  
  if (DAT_00461288 == '\0') {
    local_34 = DAT_00461f70;
    local_30 = DAT_00461f6c;
  }
  else {
    local_30 = 0xffff;
    local_34 = 0x8000;
  }
  if (-1.0 <= param_1) {
    if (param_1 < 1.0) {
      lVar2 = _ftol();
      local_14 = (uint)lVar2;
      lVar2 = _ftol();
      local_2c = (uint)lVar2 & local_30;
      if (param_1 < 0.0) {
        bVar1 = local_2c == 0;
        if (bVar1 == 0) {
          local_64 = ~local_2c & local_30;
        }
        else {
          local_64 = 0;
        }
        local_2c = local_64;
        local_14 = ~local_14 + (uint)bVar1;
      }
      *param_2 = local_14 & local_30;
      *param_3 = local_2c;
    }
    else {
      thunk_FUN_00409d88(s_Expression_value_outside_fractio_004556f4);
      *param_2 = local_30 >> 1;
      *param_3 = local_30;
    }
  }
  else {
    thunk_FUN_00409d88(s_Expression_value_outside_fractio_004556c8);
    *param_2 = local_34;
    *param_3 = 0;
  }
  return;
}


