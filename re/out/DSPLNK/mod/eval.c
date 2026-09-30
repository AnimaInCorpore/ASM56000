/* eval: 16 functions from DSPLNK */

/* ==== FUN_0040a370 @ 0040a370 ==== */

int * FUN_0040a370(void)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = thunk_FUN_0040a571();
  if (piVar1 != (int *)0x0) {
    if (piVar1[4] == 0x100) {
      iVar2 = thunk_FUN_00407988((int)piVar1);
      *piVar1 = 0;
      piVar1[1] = 0;
      piVar1[2] = iVar2;
    }
    else {
      thunk_FUN_0040ca80((undefined *)piVar1);
      thunk_FUN_00409a25(s_Expression_result_must_be_intege_00455e88);
      piVar1 = (int *)0x0;
    }
  }
  return piVar1;
}


/* ==== FUN_0040a3e6 @ 0040a3e6 ==== */

undefined4 * FUN_0040a3e6(void)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = thunk_FUN_0040a571();
  if (piVar1 != (int *)0x0) {
    if (piVar1[4] == 0x100) {
      if ((piVar1[6] & 0x1000U) == 0) {
        if (piVar1[0xb] < 0) {
          thunk_FUN_0040ca80((undefined *)piVar1);
          thunk_FUN_00409a25(s_External_reference_not_allowed_i_00455ef4);
          piVar1 = (int *)0x0;
        }
        else {
          iVar2 = thunk_FUN_00407988((int)piVar1);
          *piVar1 = 0;
          piVar1[1] = 0;
          piVar1[2] = iVar2;
        }
      }
      else {
        thunk_FUN_0040ca80((undefined *)piVar1);
        thunk_FUN_00409a25(s_Expression_result_must_be_absolu_00455ed0);
        piVar1 = (int *)0x0;
      }
    }
    else {
      thunk_FUN_0040ca80((undefined *)piVar1);
      thunk_FUN_00409a25(s_Expression_result_must_be_intege_00455eac);
      piVar1 = (int *)0x0;
    }
  }
  return piVar1;
}


/* ==== FUN_0040a4ae @ 0040a4ae ==== */

int FUN_0040a4ae(void)

{
  undefined4 *puVar1;
  int local_8;
  
  puVar1 = thunk_FUN_0040a3e6();
  if (puVar1 == (undefined4 *)0x0) {
    local_8 = -1;
  }
  else {
    local_8 = puVar1[2];
    if (local_8 < 0) {
      thunk_FUN_00409a25(s_Expression_cannot_have_a_negativ_00455f24);
      local_8 = -1;
    }
    thunk_FUN_0040ca80((undefined *)puVar1);
  }
  return local_8;
}


/* ==== FUN_0040a4fd @ 0040a4fd ==== */

int FUN_0040a4fd(void)

{
  undefined4 *puVar1;
  int local_8;
  
  puVar1 = thunk_FUN_0040a3e6();
  if (puVar1 == (undefined4 *)0x0) {
    local_8 = -1;
  }
  else {
    local_8 = puVar1[2];
    if (local_8 < 0) {
      thunk_FUN_00409a25(s_Expression_cannot_have_a_negativ_00455f4c);
      local_8 = -1;
    }
    else if ((puVar1[6] & 0x8000000) != 0) {
      thunk_FUN_00409a25(s_Expression_contains_forward_refe_00455f74);
      local_8 = -1;
    }
    thunk_FUN_0040ca80((undefined *)puVar1);
  }
  return local_8;
}


/* ==== FUN_0040a571 @ 0040a571 ==== */

int * FUN_0040a571(void)

{
  int iVar1;
  int *piVar2;
  
  if (*DAT_00461d68 == '\0') {
    thunk_FUN_00409a25(s_Missing_expression_00455f9c);
    return (int *)0x0;
  }
  iVar1 = _setjmp3(&DAT_0046c300,0);
  if (iVar1 != 0) {
    DAT_00461284 = 0;
    DAT_00461f30 = 0;
    DAT_00461b40 = 0;
    DAT_00461938 = 0;
    DAT_00461d6c = (undefined1 *)0x0;
    DAT_00461314 = 0;
    FUN_0040cac2();
    return (int *)0x0;
  }
  DAT_00461f30 = 1;
  DAT_00461d6c = &DAT_00461938;
  DAT_00461938 = 0;
  DAT_00461314 = 0;
  piVar2 = thunk_FUN_0040a772();
  if (piVar2 == (int *)0x0) {
    DAT_00461314 = 0;
    DAT_00461938 = 0;
    DAT_00461b40 = 0;
    DAT_00461d6c = (undefined1 *)0x0;
    DAT_00461f30 = 0;
    return (int *)0x0;
  }
  if ((piVar2[0xb] < 0) || ((piVar2[6] & 0x8000000U) != 0)) {
    if (piVar2[4] == 0x100) {
      piVar2[2] = 0;
      piVar2[1] = 0;
      *piVar2 = 0;
    }
    else if (piVar2[4] != 0x200) goto LAB_0040a6b6;
    *piVar2 = 0;
    piVar2[1] = 0;
  }
LAB_0040a6b6:
  if ((((*DAT_00461d68 == '\0') || (*DAT_00461d68 == ',')) || (*DAT_00461d68 == ')')) ||
     ((*DAT_00461d68 == '.' && (DAT_00461d68[1] == '.')))) {
    DAT_00461f30 = 0;
    *DAT_00461d6c = 0;
  }
  else {
    thunk_FUN_00409a25(s_Extra_characters_beyond_expressi_00455fb0);
    thunk_FUN_0040ca80((undefined *)piVar2);
    DAT_00461f30 = 0;
    DAT_00461938 = 0;
    DAT_00461d6c = (undefined1 *)0x0;
    piVar2 = (int *)0x0;
  }
  DAT_00461b40 = 0;
  DAT_00461314 = 0;
  return piVar2;
}


/* ==== FUN_0040a772 @ 0040a772 ==== */

int * FUN_0040a772(void)

{
  uint *puVar1;
  double *pdVar2;
  int *piVar3;
  
  puVar1 = DAT_00461d6c;
  pdVar2 = FUN_0040af6e();
  if (pdVar2 == (double *)0x0) {
    piVar3 = (int *)0x0;
  }
  else {
    piVar3 = FUN_0040a7ed((int *)pdVar2,99,puVar1);
    if (((piVar3 != (int *)0x0) && ((piVar3[6] & 0x1000U) != 0)) && (piVar3[4] != 0x100)) {
      thunk_FUN_00409a25(s_Relative_expression_must_be_inte_00455fd4);
      thunk_FUN_0040ca80((undefined *)piVar3);
      piVar3 = (int *)0x0;
    }
  }
  return piVar3;
}


/* ==== FUN_0040a7ed @ 0040a7ed ==== */

int * __cdecl FUN_0040a7ed(int *param_1,int param_2,uint *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  double *local_10;
  
  while( true ) {
    iVar1 = FUN_0040ab66();
    if (iVar1 == 0) {
      return param_1;
    }
    iVar2 = FUN_0040ade2(iVar1);
    if (param_2 <= iVar2) {
      return param_1;
    }
    *(undefined1 *)DAT_00461d6c = *DAT_00461d68;
    DAT_00461d6c = (uint *)((int)DAT_00461d6c + 1);
    DAT_00461d68 = DAT_00461d68 + 1;
    if (((((iVar1 == 10) || (iVar1 == 9)) || (iVar1 == 0xd)) || ((iVar1 == 0xe || (iVar1 == 0xf))))
       || ((iVar1 == 0x10 || ((iVar1 == 0x11 || (iVar1 == 0x12)))))) {
      *(undefined1 *)DAT_00461d6c = *DAT_00461d68;
      DAT_00461d6c = (uint *)((int)DAT_00461d6c + 1);
      DAT_00461d68 = DAT_00461d68 + 1;
    }
    if (((param_1[6] & 0x1000U) != 0) || (param_1[0xb] < 0)) {
      param_3 = DAT_00461d6c;
    }
    if (iVar1 == 0x16) {
      DAT_00461314 = thunk_FUN_00407988((int)param_1);
    }
    local_10 = FUN_0040af6e();
    if (local_10 == (double *)0x0) {
      thunk_FUN_0040ca80((undefined *)param_1);
      return (int *)0x0;
    }
    iVar3 = FUN_0040ab66();
    if (((iVar3 != 0) && (iVar3 = FUN_0040ade2(iVar3), iVar3 < iVar2)) &&
       (local_10 = (double *)FUN_0040a7ed((int *)local_10,iVar2,param_3), local_10 == (double *)0x0)
       ) {
      thunk_FUN_0040ca80((undefined *)param_1);
      return (int *)0x0;
    }
    if ((((DAT_00461200 != '\0') && (DAT_00457b7c != '\0')) &&
        ((DAT_0046120c == '\0' && ((iVar1 != 1 && (iVar1 != 2)))))) &&
       ((param_1[7] != 4 || (*(int *)((int)local_10 + 0x1c) != 4)))) break;
    DAT_00461284 = '\0';
    if ((-1 < *(int *)((int)local_10 + 0x2c)) &&
       (iVar2 = (*(code *)(&PTR_LAB_00458218)[iVar1])(param_1,local_10), iVar2 == 0)) {
      DAT_00461284 = 0;
      return (int *)0x0;
    }
    if (DAT_00461284 == '\0') {
      if (((param_1[6] & 0x1000U) == 0) && (((ulonglong)local_10[3] & 0x1000) != 0)) {
        param_1[6] = param_1[6] | 0x1000;
        param_1[0xb] = *(int *)((int)local_10 + 0x2c);
        param_1[0xc] = *(int *)(local_10 + 6);
        param_1[0xd] = *(int *)((int)local_10 + 0x34);
        param_1[0xe] = *(int *)(local_10 + 7);
        param_1[0xf] = *(int *)((int)local_10 + 0x3c);
        param_1[0x10] = *(int *)(local_10 + 8);
      }
      iVar2 = thunk_FUN_0043016a(param_1[7],*(int *)((int)local_10 + 0x1c));
      param_1[7] = iVar2;
      if (param_1[7] == 0xa2c2a) {
        param_1[8] = 4;
        param_1[7] = 4;
      }
    }
    else {
      DAT_00461284 = '\0';
      param_1[6] = param_1[6] & 0xffffefff;
      param_1[8] = 4;
      param_1[7] = 4;
      param_1[9] = 0;
      param_1[10] = 0;
    }
    if (((ulonglong)local_10[3] & 0x8000000) != 0) {
      param_1[6] = param_1[6] | 0x8000000;
    }
    if (*(int *)((int)local_10 + 0x2c) < 0) {
      param_1[0xb] = *(int *)((int)local_10 + 0x2c);
    }
    thunk_FUN_0040ca80((undefined *)local_10);
    if ((DAT_00461248 != '\0') && (iVar1 != 0x15)) {
      param_3 = FUN_0040ae96(param_1,param_3);
    }
  }
  thunk_FUN_0040ca80((undefined *)param_1);
  thunk_FUN_0040ca80((undefined *)local_10);
  thunk_FUN_00409a25(s_Operation_not_allowed_with_addre_00455ff8);
  return (int *)0x0;
}


/* ==== FUN_0040ab66 @ 0040ab66 ==== */

undefined4 FUN_0040ab66(void)

{
  char cVar1;
  uint local_14;
  undefined4 local_8;
  
  local_8 = 0;
  if (*DAT_00461d68 == '\0') {
    local_8 = 0;
  }
  else {
    cVar1 = DAT_00461d68[1];
    switch(*DAT_00461d68) {
    case '!':
      if (cVar1 == '=') {
        local_8 = 0x10;
      }
      else {
        local_8 = 0x16;
      }
      break;
    case '#':
      local_8 = 0x13;
      break;
    case '%':
      local_8 = 8;
      break;
    case '&':
      if (cVar1 == '&') {
        local_8 = 0x11;
      }
      else {
        local_8 = 5;
      }
      break;
    case '*':
      local_8 = 3;
      break;
    case '+':
      local_8 = 1;
      break;
    case '-':
      local_8 = 2;
      break;
    case '/':
      local_8 = 4;
      break;
    case ':':
      local_8 = 0x15;
      if (__mb_cur_max < 2) {
        local_14 = *(ushort *)(_pctype + DAT_00461d68[4] * 2) & 0x80;
      }
      else {
        local_14 = _isctype((int)DAT_00461d68[4],0x80);
      }
      DAT_00461268 = local_14 == 0;
      break;
    case '<':
      if (cVar1 == '<') {
        local_8 = 9;
      }
      else if (cVar1 == '=') {
        local_8 = 0xe;
      }
      else {
        local_8 = 0xb;
      }
      break;
    case '=':
      if (cVar1 == '=') {
        local_8 = 0xd;
      }
      break;
    case '>':
      if (cVar1 == '>') {
        local_8 = 10;
      }
      else if (cVar1 == '=') {
        local_8 = 0xf;
      }
      else {
        local_8 = 0xc;
      }
      break;
    case '@':
      local_8 = 0x14;
      break;
    case '^':
      local_8 = 7;
      break;
    case '|':
      if (cVar1 == '|') {
        local_8 = 0x12;
      }
      else {
        local_8 = 6;
      }
    }
  }
  return local_8;
}


/* ==== FUN_0040ade2 @ 0040ade2 ==== */

undefined4 __cdecl FUN_0040ade2(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 1:
  case 2:
    uVar1 = 2;
    break;
  case 3:
  case 4:
  case 8:
    uVar1 = 1;
    break;
  case 5:
  case 6:
  case 7:
    uVar1 = 6;
    break;
  case 9:
  case 10:
    uVar1 = 3;
    break;
  case 0xb:
  case 0xc:
  case 0xe:
  case 0xf:
    uVar1 = 4;
    break;
  case 0xd:
  case 0x10:
    uVar1 = 5;
    break;
  case 0x11:
  case 0x12:
    uVar1 = 7;
    break;
  default:
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_0040ae82 @ 0040ae82 ==== */

undefined4 FUN_0040ae82(void)

{
  thunk_FUN_004098b0(s_Expression_operator_failure_00456020);
  return 0;
}


/* ==== FUN_0040ae96 @ 0040ae96 ==== */

uint * __cdecl FUN_0040ae96(int *param_1,uint *param_2)

{
  uint uVar1;
  uint *puVar2;
  
  puVar2 = DAT_00461d6c;
  if (((param_1[6] & 0x1000U) == 0) && (-1 < param_1[0xb])) {
    if (param_1[4] == 0x200) {
      thunk_FUN_004302d1(param_2,(uint *)s____15E_0045603c,*param_1,param_1[1]);
    }
    else if (param_1[5] == DAT_00461f60) {
      sprintf((char *)param_2,s__s_lX_00456044,PTR_DAT_00457bf4,param_1[2] & DAT_00461f6c);
    }
    else {
      sprintf((char *)param_2,s__s_lX_0_lX_0045604c,PTR_DAT_00457bf4,param_1[1] & DAT_00461f6c,
              DAT_00461fa4,param_1[2] & DAT_00461f6c);
    }
    uVar1 = strlen((char *)param_2);
    DAT_00461d6c = (uint *)((int)param_2 + uVar1);
    puVar2 = param_2;
  }
  return puVar2;
}


/* ==== FUN_0040af6e @ 0040af6e ==== */

double * FUN_0040af6e(void)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  double *pdVar4;
  undefined3 extraout_var;
  undefined4 *puVar5;
  int iVar6;
  double dVar7;
  int local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  uint local_8c;
  uint local_88;
  int local_84;
  int local_80;
  uint local_7c;
  uint local_78;
  int local_74;
  uint local_70;
  uint local_6c;
  uint local_68;
  int local_64;
  int local_50;
  char *local_4c;
  int local_48;
  uint local_44;
  char *local_40;
  int local_3c;
  int local_38;
  int local_34;
  undefined4 *local_30;
  uint local_2c;
  int local_28;
  int local_24;
  int local_20;
  char *local_1c;
  int *local_18;
  uint local_14;
  uint *local_10;
  uint local_c;
  double *local_8;
  
  uVar3 = DAT_00461f6c >> 4;
  if (*DAT_00461d68 == '+') {
    *DAT_00461d6c = *DAT_00461d68;
    DAT_00461d6c = DAT_00461d6c + 1;
    DAT_00461d68 = DAT_00461d68 + 1;
    pdVar4 = FUN_0040af6e();
    if (pdVar4 != (double *)0x0) {
      return pdVar4;
    }
    return (double *)0x0;
  }
  if (*DAT_00461d68 == '-') {
    *DAT_00461d6c = *DAT_00461d68;
    DAT_00461d6c = DAT_00461d6c + 1;
    DAT_00461d68 = DAT_00461d68 + 1;
    local_8 = FUN_0040af6e();
    if (local_8 == (double *)0x0) {
      return (double *)0x0;
    }
    thunk_FUN_004079b8(local_8);
    return local_8;
  }
  if (*DAT_00461d68 == '~') {
    *DAT_00461d6c = *DAT_00461d68;
    DAT_00461d6c = DAT_00461d6c + 1;
    DAT_00461d68 = DAT_00461d68 + 1;
    local_8 = FUN_0040af6e();
    if (local_8 == (double *)0x0) {
      return (double *)0x0;
    }
    if (*(int *)(local_8 + 2) == 0x100) {
      thunk_FUN_00407a61((uint *)local_8);
      return local_8;
    }
    thunk_FUN_00409a25(s_Illegal_operator_for_floating_po_00456058);
    thunk_FUN_0040ca80((undefined *)local_8);
    return (double *)0x0;
  }
  if (*DAT_00461d68 == '!') {
    *DAT_00461d6c = *DAT_00461d68;
    DAT_00461d6c = DAT_00461d6c + 1;
    DAT_00461d68 = DAT_00461d68 + 1;
    local_8 = FUN_0040af6e();
    if (local_8 == (double *)0x0) {
      return (double *)0x0;
    }
    thunk_FUN_00407aa0(local_8);
    return local_8;
  }
  if (*DAT_00461d68 == '(') {
    *DAT_00461d6c = *DAT_00461d68;
    DAT_00461d6c = DAT_00461d6c + 1;
    DAT_00461d68 = DAT_00461d68 + 1;
    local_8 = (double *)thunk_FUN_0040a772();
    if (local_8 == (double *)0x0) {
      return (double *)0x0;
    }
    if (*DAT_00461d68 != ')') {
      thunk_FUN_0040ca80((undefined *)local_8);
      thunk_FUN_00409a25(s_Missing_____in_expression_00456084);
      return (double *)0x0;
    }
    *DAT_00461d6c = *DAT_00461d68;
    DAT_00461d68 = DAT_00461d68 + 1;
    DAT_00461d6c = DAT_00461d6c + 1;
    return local_8;
  }
  if (*DAT_00461d68 == '[') {
    if (((DAT_00461fe8 < 6) && ((DAT_00461fe8 != 5 || (DAT_00461fec < 1)))) &&
       ((DAT_00461fe8 != 5 || ((DAT_00461fec != 0 || (DAT_00461ff0 < 0xb)))))) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    *DAT_00461d6c = *DAT_00461d68;
    DAT_00461d6c = DAT_00461d6c + 1;
    DAT_00461d68 = DAT_00461d68 + 1;
    local_8 = (double *)thunk_FUN_0040a772();
    if (local_8 == (double *)0x0) {
      return (double *)0x0;
    }
    if ((*(int *)(local_8 + 2) != 0x100) || (DAT_00461d70 == 4)) {
      thunk_FUN_0040ca80((undefined *)local_8);
      thunk_FUN_00409a25(s_Invalid_relative_expression_004560a0);
      return (double *)0x0;
    }
    if (*(int *)(local_8 + 6) < 0) {
      local_64 = DAT_004612a0;
    }
    else {
      local_64 = *(int *)(local_8 + 6);
    }
    local_38 = local_64;
    if (((bVar1) && (*(int *)(local_8 + 7) != 0)) || ((!bVar1 && (DAT_00461d90 != DAT_00461d94)))) {
      if (bVar1) {
        local_68 = DAT_004612d8 + *(int *)(local_8 + 7);
      }
      else {
        local_68 = DAT_004612c8;
      }
      *(int *)(local_8 + 1) =
           *(int *)(local_8 + 1) + *(int *)(*(int *)(DAT_00461e60 + 0x10 + local_68 * 0x24) + 0x10);
    }
    else {
      if ((*(int *)((int)local_8 + 0x34) == 0) ||
         ((*(uint *)(*(int *)(DAT_00461e5c + (DAT_004612c4 + *(int *)((int)local_8 + 0x34)) * 8) + 8
                    ) & 0x20000) == 0)) {
        if (((bVar1) &&
            (((*(int *)(local_8 + 6) == DAT_004612a0 &&
              (*(int *)((int)local_8 + 0x1c) == DAT_00461d80)) &&
             (*(int *)((int)local_8 + 0x24) == DAT_00461d88)))) ||
           (((!bVar1 && (*(int *)((int)local_8 + 0x1c) == DAT_00461d80)) &&
            (*(int *)((int)local_8 + 0x24) == DAT_00461d88)))) {
          local_18 = DAT_00461de0;
          local_30 = DAT_00461df0;
        }
        else {
          local_18 = (int *)0x0;
          local_20 = *(int *)*DAT_00461de0;
          for (local_24 = *(int *)(local_20 + 8); local_24 != 0;
              local_24 = *(int *)(local_24 + 0x74)) {
            if ((*(int *)(local_24 + 8) == *(int *)((int)local_8 + 0x1c)) &&
               (*(int *)(local_24 + 0x10) == *(int *)((int)local_8 + 0x24))) {
              local_18 = *(int **)(local_24 + 0x18);
              break;
            }
          }
          local_30 = *(undefined4 **)(DAT_00461de8 + local_64 * 4);
          while ((local_30 != (undefined4 *)0x0 &&
                 ((*(int *)(*(int *)*local_30 + 8) != *(int *)((int)local_8 + 0x1c) ||
                  (*(int *)(*(int *)*local_30 + 0x10) != *(int *)((int)local_8 + 0x24)))))) {
            local_30 = (undefined4 *)local_30[5];
          }
          if (local_30 == (undefined4 *)0x0) {
            thunk_FUN_0042bc50(*(uint **)**(undefined4 **)
                                           **(undefined4 **)(DAT_00461de8 + local_64 * 4),local_64,
                               (int *)((int)local_8 + 0x1c),1);
            local_30 = *(undefined4 **)(DAT_00461de8 + local_38 * 4);
            while ((local_30 != (undefined4 *)0x0 &&
                   ((*(int *)(*(int *)*local_30 + 8) != *(int *)((int)local_8 + 0x1c) ||
                    (*(int *)(*(int *)*local_30 + 0x10) != *(int *)((int)local_8 + 0x24)))))) {
              local_30 = (undefined4 *)local_30[5];
            }
          }
        }
      }
      else {
        local_18 = *(int **)(DAT_00461e5c + (DAT_004612c4 + *(int *)((int)local_8 + 0x34)) * 8);
        local_30 = DAT_00461df0;
      }
      if ((local_18 == (int *)0x0) || (local_30 == (undefined4 *)0x0)) {
        thunk_FUN_004098b0(s_Section_map_lookup_failure_004560bc);
      }
      *(int *)(local_8 + 1) = *(int *)(local_8 + 1) + local_18[4];
      if ((DAT_00461248 == '\0') || ((local_18[2] & 0x20000U) != 0)) {
        if ((local_18[2] & 0x2000U) == 0) {
          local_34 = 0;
          if ((local_18[2] & 0x20000U) != 0) {
            for (local_50 = *(int *)(*local_18 + 0x20); local_50 != 0;
                local_50 = *(int *)(local_50 + 0x44)) {
              if (*(uint *)(local_50 + 0x30) <= *(uint *)(local_8 + 1)) {
                local_34 = local_34 + *(int *)(local_50 + 0x34);
              }
            }
          }
          *(int *)(local_8 + 1) = *(int *)(local_8 + 1) + (local_30[3] - local_34);
        }
        else {
          *(int *)(local_8 + 1) =
               *(int *)(local_8 + 1) -
               *(int *)(DAT_00461e5c + 4 + (DAT_004612c4 + *(int *)((int)local_8 + 0x34)) * 8);
        }
      }
      else {
        *(int *)(local_8 + 1) = *(int *)(local_8 + 1) + local_30[3];
      }
    }
    if (DAT_00461d90 == DAT_00461d94) {
      *(int *)(local_8 + 1) = *(int *)(local_8 + 1) + *(int *)(*DAT_00461de0 + 0x58);
    }
    else {
      *(int *)(local_8 + 1) =
           *(int *)(local_8 + 1) +
           *(int *)(DAT_00461e60 + 0x18 + (DAT_004612d8 + *(int *)(local_8 + 7)) * 0x24);
    }
    if (((DAT_00461de4 != 0) && (*(int *)(DAT_00461de4 + 0x38) != 0)) &&
       (local_3c = *(int *)(DAT_00461de4 + 0x38), *(int *)(local_8 + 8) != 0)) {
      *(int *)(local_8 + 1) =
           *(int *)(local_8 + 1) +
           *(int *)(*(int *)(local_3c + 0x28) + 0x1c +
                   (*(int *)(local_3c + 0x10) + -1 + *(int *)(local_8 + 8)) * 0x2c);
    }
    *(uint *)(local_8 + 3) = *(uint *)(local_8 + 3) | 0x1000;
    if (*DAT_00461d68 != ']') {
      thunk_FUN_0040ca80((undefined *)local_8);
      thunk_FUN_00409a25(s_Missing_____in_expression_004560d8);
      return (double *)0x0;
    }
    *DAT_00461d6c = *DAT_00461d68;
    DAT_00461d68 = DAT_00461d68 + 1;
    DAT_00461d6c = DAT_00461d6c + 1;
    return local_8;
  }
  if (*DAT_00461d68 == '{') {
    *DAT_00461d6c = *DAT_00461d68;
    DAT_00461d6c = DAT_00461d6c + 1;
    DAT_00461d68 = DAT_00461d68 + 1;
    DAT_00461b40 = 0;
    DAT_00461200 = 1;
    local_8 = (double *)thunk_FUN_0040a772();
    DAT_00461200 = 0;
    if (local_8 == (double *)0x0) {
      DAT_00461200 = 0;
      return (double *)0x0;
    }
    if (*DAT_00461d68 != '}') {
      thunk_FUN_0040ca80((undefined *)local_8);
      thunk_FUN_00409a25(s_Missing_____in_expression_004560f4);
      return (double *)0x0;
    }
    *DAT_00461d6c = *DAT_00461d68;
    DAT_00461d68 = DAT_00461d68 + 1;
    DAT_00461d6c = DAT_00461d6c + 1;
    return local_8;
  }
  local_8 = (double *)thunk_FUN_0040c91d();
  local_28 = 0;
  local_44 = 0;
  local_14 = 0;
  local_c = 0;
  local_48 = 0;
  if ((*DAT_00461d68 == '%') ||
     ((DAT_00457ba4 == 2 && ((*DAT_00461d68 == '0' || (*DAT_00461d68 == '1')))))) {
    if (*DAT_00461d68 == '%') {
      *DAT_00461d6c = *DAT_00461d68;
      DAT_00461d6c = DAT_00461d6c + 1;
      DAT_00461d68 = DAT_00461d68 + 1;
    }
    for (; (*DAT_00461d68 == '0' || (*DAT_00461d68 == '1')); DAT_00461d68 = DAT_00461d68 + 1) {
      local_28 = local_28 + 1;
      if (DAT_00461f5c < local_28) {
        local_c = local_c * 2;
        if ((local_14 & DAT_00461f70) != 0) {
          local_c = local_c + 1;
        }
        local_14 = local_14 & ~DAT_00461f70 & DAT_00461f6c;
      }
      if (DAT_00461f58 < local_28) {
        local_14 = local_14 * 2;
        if ((local_44 & DAT_00461f70) != 0) {
          local_14 = local_14 + 1;
        }
        local_44 = local_44 & ~DAT_00461f70 & DAT_00461f6c;
      }
      local_44 = *DAT_00461d68 + -0x30 + local_44 * 2;
      *DAT_00461d6c = *DAT_00461d68;
      DAT_00461d6c = DAT_00461d6c + 1;
    }
    local_c = local_c & DAT_00461f6c;
    if (DAT_00461f58 < local_28) {
      *(uint *)((int)local_8 + 0x14) = DAT_00461f64;
    }
    else if (local_28 == 0) {
      thunk_FUN_0040ca80((undefined *)local_8);
      thunk_FUN_00409a25(s_Binary_constant_expected_00456110);
      return (double *)0x0;
    }
    *(uint *)local_8 = local_c;
    *(uint *)((int)local_8 + 4) = local_14;
    *(uint *)(local_8 + 1) = local_44;
    return local_8;
  }
  if (*DAT_00461d68 == '$') {
LAB_0040ba3b:
    if ((*DAT_00461d68 == '$') || (*DAT_00461d68 == '0')) {
      *DAT_00461d6c = *DAT_00461d68;
      DAT_00461d6c = DAT_00461d6c + 1;
      DAT_00461d68 = DAT_00461d68 + 1;
    }
    if (__mb_cur_max < 2) {
      local_70 = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 1;
    }
    else {
      local_70 = _isctype((int)*DAT_00461d68,1);
    }
    if (local_70 == 0) {
      local_74 = (int)*DAT_00461d68;
    }
    else {
      local_74 = tolower((int)*DAT_00461d68);
    }
    if (local_74 == 0x78) {
      *DAT_00461d6c = *DAT_00461d68;
      DAT_00461d6c = DAT_00461d6c + 1;
      DAT_00461d68 = DAT_00461d68 + 1;
    }
    while( true ) {
      if (__mb_cur_max < 2) {
        local_78 = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 0x80;
      }
      else {
        local_78 = _isctype((int)*DAT_00461d68,0x80);
      }
      if (local_78 == 0) break;
      local_28 = local_28 + 1;
      if (DAT_00461f54 < local_28) {
        local_c = local_c << 4 | local_14 >> ((char)DAT_00461f58 - 4U & 0x1f);
      }
      if (DAT_00461f50 < local_28) {
        local_14 = local_14 << 4 | local_44 >> ((char)DAT_00461f58 - 4U & 0x1f);
      }
      local_44 = local_44 << 4;
      if (*DAT_00461d68 < ':') {
        local_84 = *DAT_00461d68 + -0x30;
      }
      else {
        if (__mb_cur_max < 2) {
          local_7c = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 1;
        }
        else {
          local_7c = _isctype((int)*DAT_00461d68,1);
        }
        if (local_7c == 0) {
          local_80 = (int)*DAT_00461d68;
        }
        else {
          local_80 = tolower((int)*DAT_00461d68);
        }
        local_84 = local_80 + -0x57;
      }
      local_44 = local_44 + local_84;
      *DAT_00461d6c = *DAT_00461d68;
      DAT_00461d6c = DAT_00461d6c + 1;
      DAT_00461d68 = DAT_00461d68 + 1;
    }
    local_c = local_c & DAT_00461f6c;
    if (DAT_00461f50 < local_28) {
      *(uint *)((int)local_8 + 0x14) = DAT_00461f64;
    }
    else if (local_28 == 0) {
      thunk_FUN_0040ca80((undefined *)local_8);
      thunk_FUN_00409a25(s_Hex_constant_expected_0045612c);
      return (double *)0x0;
    }
    *(uint *)local_8 = local_c;
    *(uint *)((int)local_8 + 4) = local_14;
    *(uint *)(local_8 + 1) = local_44;
    return local_8;
  }
  if (DAT_00457ba4 == 0x10) {
    if (__mb_cur_max < 2) {
      local_6c = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 0x80;
    }
    else {
      local_6c = _isctype((int)*DAT_00461d68,0x80);
    }
    if (local_6c != 0) goto LAB_0040ba3b;
  }
  if (*DAT_00461d68 == '`') {
LAB_0040bd73:
    if (*DAT_00461d68 == '`') {
      *DAT_00461d6c = *DAT_00461d68;
      DAT_00461d6c = DAT_00461d6c + 1;
      DAT_00461d68 = DAT_00461d68 + 1;
    }
    local_1c = DAT_00461d68;
    local_40 = DAT_00461d6c;
    while( true ) {
      if (__mb_cur_max < 2) {
        local_8c = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 4;
      }
      else {
        local_8c = _isctype((int)*DAT_00461d68,4);
      }
      if (local_8c == 0) break;
      local_28 = local_28 + 1;
      local_44 = local_44 * 10 + -0x30 + (int)*DAT_00461d68;
      local_14 = local_14 * 10;
      local_c = local_c * 10;
      local_48 = local_48 * 10;
      cVar2 = (char)DAT_00461f58;
      if (uVar3 < local_44) {
        local_14 = local_14 + (local_44 >> (cVar2 - 4U & 0x1f));
        local_44 = local_44 & uVar3;
      }
      if (uVar3 < local_14) {
        local_c = local_c + (local_14 >> (cVar2 - 4U & 0x1f));
        local_14 = local_14 & uVar3;
      }
      if (uVar3 < local_c) {
        local_48 = local_48 + (local_c >> (cVar2 - 4U & 0x1f));
        local_c = local_c & uVar3;
      }
      *DAT_00461d6c = *DAT_00461d68;
      DAT_00461d6c = DAT_00461d6c + 1;
      DAT_00461d68 = DAT_00461d68 + 1;
    }
    if ((((*DAT_00461d68 == '.') && (DAT_00461d68[1] != '.')) || (*DAT_00461d68 == 'e')) ||
       (*DAT_00461d68 == 'E')) {
      DAT_00461d68 = local_1c;
      DAT_00461d6c = local_40;
      dVar7 = strtod(local_1c,&local_4c);
      *local_8 = dVar7;
      if (local_4c == DAT_00461d68) {
        thunk_FUN_0040ca80((undefined *)local_8);
        thunk_FUN_00409a25(s_Floating_point_constant_expected_00456144);
        return (double *)0x0;
      }
      DAT_00461d68 = local_4c;
      local_28 = (int)*local_4c;
      *local_4c = '\0';
      cVar2 = strcpy(local_40,local_1c);
      uVar3 = strlen((char *)CONCAT31(extraout_var,cVar2));
      DAT_00461d6c = DAT_00461d6c + uVar3;
      *DAT_00461d68 = (char)local_28;
      *(uint *)((int)local_8 + 0x14) = 8;
      *(uint *)(local_8 + 2) = 0x200;
    }
    else if (local_28 == 0) {
      thunk_FUN_0040ca80((undefined *)local_8);
      thunk_FUN_00409a25(s_Decimal_constant_expected_00456168);
      return (double *)0x0;
    }
    if (*(uint *)(local_8 + 2) == 0x100) {
      *(uint *)(local_8 + 1) =
           (local_44 | local_14 << ((char)DAT_00461f58 - 4U & 0x1f)) & DAT_00461f6c;
      local_14 = local_14 >> 4;
      *(uint *)((int)local_8 + 4) =
           (local_14 | local_c << ((char)DAT_00461f58 - 8U & 0x1f)) & DAT_00461f6c;
      local_c = local_c >> 8;
      *(uint *)local_8 = (local_c | local_48 << ((char)DAT_00461f58 - 0xcU & 0x1f)) & DAT_00461f6c;
      thunk_FUN_0040c8ab((int)local_8);
    }
  }
  else {
    if (DAT_00457ba4 == 10) {
      if (__mb_cur_max < 2) {
        local_88 = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 4;
      }
      else {
        local_88 = _isctype((int)*DAT_00461d68,4);
      }
      if ((local_88 != 0) || (*DAT_00461d68 == '.')) goto LAB_0040bd73;
    }
    if (*DAT_00461d68 == '*') {
      DAT_00461d68 = DAT_00461d68 + 1;
      *(undefined4 *)(local_8 + 1) = *DAT_00461d90;
      *(int *)((int)local_8 + 0x1c) = DAT_00461d70;
      *(undefined4 *)(local_8 + 4) = DAT_00461d74;
      *(undefined4 *)((int)local_8 + 0x24) = DAT_00461d78;
      *(undefined4 *)(local_8 + 5) = DAT_00461d7c;
      if ((DAT_00461200 == '\0') && (DAT_00461280 != '\0')) {
        *(int *)(local_8 + 1) = *(int *)(local_8 + 1) + 1;
      }
      if ((DAT_00461f44 == 4) && (DAT_00461d70 == 0)) {
        *(uint *)((int)local_8 + 4) =
             (*(uint *)(local_8 + 1) & ~DAT_00461f6c) >> ((byte)DAT_00461f58 & 0x1f) & 0xf;
        *(uint *)(local_8 + 1) = *(uint *)(local_8 + 1) & DAT_00461f6c;
        *(uint *)((int)local_8 + 0x14) = DAT_00461f64;
      }
      if ((DAT_00461f44 == 6) && (DAT_00461d70 == 0)) {
        *(uint *)((int)local_8 + 4) =
             (*(uint *)(local_8 + 1) & ~DAT_00461f6c) >> ((byte)DAT_00461f58 & 0x1f) & DAT_00461f6c;
        *(uint *)(local_8 + 1) = *(uint *)(local_8 + 1) & DAT_00461f6c;
        *(uint *)((int)local_8 + 0x14) = DAT_00461f64;
      }
      *(uint *)(local_8 + 3) = *(uint *)(local_8 + 3) | 0x1000;
      *(undefined4 *)((int)local_8 + 0x2c) = DAT_004612a4;
      *(int *)(local_8 + 6) = DAT_004612a8;
      *(uint *)((int)local_8 + 0x34) = -(uint)(DAT_004612b8 != 0) & DAT_004612ac;
      *(uint *)(local_8 + 7) = -(uint)(DAT_0046c2e0 != 4) & DAT_004612c8;
      if ((DAT_00461270 == '\0') || (DAT_00461d70 != 0)) {
        local_90 = 0;
      }
      else {
        local_90 = DAT_00461ef4;
      }
      *(undefined4 *)(local_8 + 8) = local_90;
      FUN_0040c749((int *)local_8);
    }
    else if ((*DAT_00461d68 == '\'') || (*DAT_00461d68 == '\"')) {
      DAT_00461d68 = thunk_FUN_0042e4df(DAT_00461d68,&DAT_00461528);
      if (DAT_00461d68 == (char *)0x0) {
        thunk_FUN_0040ca80((undefined *)local_8);
        local_8 = (double *)0x0;
      }
      else {
        local_2c = strlen(&DAT_00461528);
        if ((int)DAT_00461f64 < (int)local_2c) {
          local_2c = DAT_00461f64;
          thunk_FUN_00409d88(s_String_truncated_in_expression_e_00456184);
        }
        *DAT_00461d6c = '\'';
        DAT_00461d6c = DAT_00461d6c + 1;
        strncpy(DAT_00461d6c,&DAT_00461528,local_2c);
        DAT_00461d6c = DAT_00461d6c + local_2c;
        *DAT_00461d6c = '\'';
        DAT_00461d6c = DAT_00461d6c + 1;
        local_1c = &DAT_00461528;
        for (local_28 = 0; local_28 < (int)local_2c; local_28 = local_28 + 1) {
          if (DAT_00461f60 < local_28) {
            local_14 = local_14 << 8 | local_44 >> ((char)DAT_00461f58 - 8U & 0x1f);
            local_44 = local_44 & DAT_00461f6c >> 8;
          }
          local_44 = local_44 * 0x100 + (int)*local_1c;
          local_1c = local_1c + 1;
        }
        if ((int)DAT_00461f64 < (int)local_2c) {
          *(uint *)((int)local_8 + 0x14) = DAT_00461f64;
        }
        else {
          *(uint *)((int)local_8 + 0x14) = local_2c;
        }
        *(undefined4 *)local_8 = 0;
        *(uint *)((int)local_8 + 4) = local_14;
        *(uint *)(local_8 + 1) = local_44;
      }
    }
    else if (*DAT_00461d68 == '@') {
      *DAT_00461d6c = *DAT_00461d68;
      DAT_00461d6c = DAT_00461d6c + 1;
      DAT_00461d68 = DAT_00461d68 + 1;
      local_8 = (double *)thunk_FUN_004128e0((uint *)local_8);
      if (local_8 == (double *)0x0) {
        local_8 = (double *)0x0;
      }
    }
    else {
      local_10 = (uint *)thunk_FUN_0042e622();
      if (local_10 == (uint *)0x0) {
        thunk_FUN_0040ca80((undefined *)local_8);
        local_8 = (double *)0x0;
      }
      else {
        strcpy(&DAT_00461b40,(char *)local_10);
        puVar5 = thunk_FUN_0042c8ba(local_10,0);
        if (puVar5 == (undefined4 *)0x0) {
          if (DAT_00461294 == 1) {
            thunk_FUN_0040ca80((undefined *)local_8);
            local_8 = (double *)0x0;
          }
          else {
            *(undefined4 *)((int)local_8 + 0x2c) = 0xffffffff;
            *(uint *)(local_8 + 3) = *(uint *)(local_8 + 3) | 0x8000000;
            strcpy(DAT_00461d6c,(char *)local_10);
            uVar3 = strlen(DAT_00461d6c);
            DAT_00461d6c = DAT_00461d6c + uVar3;
            thunk_FUN_0042cae9(local_10,0,0);
          }
        }
        else {
          if ((puVar5[10] & 0x100) == 0) {
            if ((puVar5[10] & 0x200) != 0) {
              *(undefined4 *)local_8 = puVar5[2];
              *(undefined4 *)((int)local_8 + 4) = puVar5[3];
              *(undefined4 *)(local_8 + 2) = 0x200;
            }
          }
          else {
            *(undefined4 *)local_8 = puVar5[2];
            *(undefined4 *)((int)local_8 + 4) = puVar5[3];
            *(undefined4 *)(local_8 + 1) = puVar5[4];
          }
          *(undefined4 *)((int)local_8 + 0x1c) = puVar5[0xb];
          *(undefined4 *)(local_8 + 4) = puVar5[0xc];
          *(undefined4 *)((int)local_8 + 0x24) = puVar5[0xd];
          *(undefined4 *)(local_8 + 5) = puVar5[0xe];
          if ((puVar5[10] & 0x800) != 0) {
            *(uint *)((int)local_8 + 0x14) = DAT_00461f64;
          }
          *(uint *)(local_8 + 3) = *(uint *)(local_8 + 3) | puVar5[10] & 0x1000;
          *(uint *)(local_8 + 3) = *(uint *)(local_8 + 3) | puVar5[10] & 0x4000;
          if (puVar5[0x12] == 0) {
            local_94 = 0;
          }
          else {
            local_94 = *(undefined4 *)(**(int **)puVar5[0x12] + 4);
          }
          *(undefined4 *)((int)local_8 + 0x2c) = local_94;
          if (puVar5[0x13] == 0) {
            local_98 = 0;
          }
          else {
            local_98 = *(undefined4 *)(**(int **)puVar5[0x13] + 4);
          }
          *(undefined4 *)(local_8 + 6) = local_98;
          if (puVar5[0x16] == 0) {
            local_9c = 0;
          }
          else {
            local_9c = (DAT_00461e5c - puVar5[0x16] >> 3) + 1;
          }
          *(int *)((int)local_8 + 0x34) = local_9c;
          if (puVar5[0x17] == 0) {
            iVar6 = 0;
          }
          else {
            iVar6 = (DAT_00461e60 - puVar5[0x17]) / 0x24 + 1;
          }
          *(int *)(local_8 + 7) = iVar6;
          *(undefined4 *)((int)local_8 + 0x3c) = puVar5[0xf];
          *(undefined4 *)(local_8 + 8) = puVar5[0x10];
          if ((((ulonglong)local_8[3] & 0x1000) == 0) ||
             (((*(int *)((int)local_8 + 0x2c) == DAT_004612a8 && (DAT_00461d90 == DAT_00461d94)) &&
              (DAT_004612b8 == 0)))) {
            FUN_0040c749((int *)local_8);
          }
          else {
            strcpy(DAT_00461d6c,(char *)local_10);
            uVar3 = strlen(DAT_00461d6c);
            DAT_00461d6c = DAT_00461d6c + uVar3;
          }
        }
      }
    }
  }
  return local_8;
}


/* ==== FUN_0040c749 @ 0040c749 ==== */

void __cdecl FUN_0040c749(int *param_1)

{
  int iVar1;
  uint *puVar2;
  char *buf;
  uint uVar3;
  uint uVar4;
  
  if ((param_1[6] & 0x1000U) != 0) {
    *(undefined1 *)DAT_00461d6c = 0x5b;
    DAT_00461d6c = (uint *)((int)DAT_00461d6c + 1);
  }
  puVar2 = DAT_00461d6c;
  if (param_1[4] == 0x100) {
    iVar1 = param_1[8];
    uVar4 = param_1[9];
    *(undefined1 *)DAT_00461d6c = 0x24;
    buf = (char *)((int)puVar2 + 1);
    if (param_1[5] == DAT_00461f60) {
      sprintf(buf,DAT_00461fb4,param_1[2] & DAT_00461f6c);
    }
    else {
      sprintf(buf,s__0_lX_0_lX_004561b8,DAT_00461fa4,param_1[1] & DAT_00461f6c,DAT_00461fa4,
              param_1[2] & DAT_00461f6c);
    }
    uVar3 = strlen(buf);
    sprintf(buf + uVar3,s____08lX_004561c4,iVar1 << 0x10 | uVar4);
  }
  else {
    thunk_FUN_004302d1(DAT_00461d6c,(uint *)s___15E_004561b0,*param_1,param_1[1]);
  }
  uVar4 = strlen((char *)DAT_00461d6c);
  DAT_00461d6c = (uint *)((int)DAT_00461d6c + uVar4);
  if ((param_1[6] & 0x1000U) != 0) {
    *(undefined1 *)DAT_00461d6c = 0x5d;
    DAT_00461d6c = (uint *)((int)DAT_00461d6c + 1);
  }
  return;
}


/* ==== FUN_0040c8ab @ 0040c8ab ==== */

void __cdecl FUN_0040c8ab(int param_1)

{
  if (*(int *)(param_1 + 0x10) == 0x200) {
    *(undefined4 *)(param_1 + 0x14) = 8;
  }
  else if (((*(int *)(param_1 + 4) == 0) || (*(int *)(param_1 + 4) == DAT_00461f6c)) ||
          ((*(int *)(param_1 + 0x1c) != 4 &&
           (((DAT_00461f44 != 4 && (DAT_00461f44 != 6)) || (*(int *)(param_1 + 0x1c) != 0)))))) {
    *(undefined4 *)(param_1 + 0x14) = DAT_00461f60;
  }
  else {
    *(undefined4 *)(param_1 + 0x14) = DAT_00461f64;
  }
  return;
}


/* ==== FUN_0040c91d @ 0040c91d ==== */

undefined4 * FUN_0040c91d(void)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  
  if (DAT_00461f28 == (int *)0x0) {
    DAT_00461f28 = (int *)thunk_FUN_0042e170(DAT_00455e84 << 2);
    DAT_00461f2c = DAT_00461f28;
  }
  if (DAT_00461f28 + DAT_00455e84 <= DAT_00461f2c) {
    iVar3 = (int)DAT_00461f2c - (int)DAT_00461f28;
    uVar2 = DAT_00455e84 << 3;
    DAT_00455e84 = DAT_00455e84 << 1;
    DAT_00461f28 = thunk_FUN_0042e19d(DAT_00461f28,uVar2);
    DAT_00461f2c = DAT_00461f28 + (iVar3 >> 2);
  }
  puVar1 = (undefined4 *)thunk_FUN_0042e170(0x48);
  puVar1[2] = 0;
  puVar1[1] = 0;
  *puVar1 = 0;
  puVar1[4] = 0x100;
  puVar1[8] = 4;
  puVar1[7] = 4;
  puVar1[9] = 0;
  puVar1[10] = 0;
  puVar1[5] = DAT_00461f60;
  puVar1[6] = 0;
  puVar1[0xb] = 0;
  puVar1[0xc] = 0xffffffff;
  puVar1[0xd] = 0;
  puVar1[0xe] = 0;
  puVar1[0xf] = 0xffffffff;
  puVar1[0x10] = 0;
  *DAT_00461f2c = (int)puVar1;
  DAT_00461f2c = DAT_00461f2c + 1;
  return puVar1;
}


/* ==== FUN_0040ca80 @ 0040ca80 ==== */

void __cdecl FUN_0040ca80(undefined *param_1)

{
  if (param_1 != (undefined *)0x0) {
    if (DAT_00461f2c == DAT_00461f28) {
      thunk_FUN_004098b0(s_Expression_stack_underflow_004561cc);
    }
    DAT_00461f2c = DAT_00461f2c + -4;
    thunk_FUN_0042e1ce(param_1);
  }
  return;
}


