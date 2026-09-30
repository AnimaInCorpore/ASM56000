/* func: 29 functions from ASM56000 */

/* ==== FUN_004167ef @ 004167ef ==== */

void __cdecl FUN_004167ef(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    if (DAT_0045fc9c == DAT_0045fc98) {
      FUN_00412fa0((uint *)s_Expression_stack_underflow_00454440);
    }
    DAT_0045fc9c = DAT_0045fc9c + -4;
    if (param_1[0xe] != 0) {
      FUN_004398b5((undefined *)*param_1);
    }
    if (param_1[0xc] != 0) {
      FUN_004398b5((undefined *)param_1[0xb]);
    }
    FUN_004398b5((undefined *)param_1);
  }
  return;
}


/* ==== FUN_00416860 @ 00416860 ==== */

void FUN_00416860(void)

{
  while (DAT_0045fc9c != DAT_0045fc98) {
    if (*(int *)(*DAT_0045fc9c + 0x38) != 0) {
      FUN_004398b5(*(undefined **)*DAT_0045fc9c);
    }
    DAT_0045fc9c = DAT_0045fc9c + -1;
    FUN_004398b5((undefined *)*DAT_0045fc9c);
  }
  return;
}


/* ==== FUN_004168c0 @ 004168c0 ==== */

double * __cdecl FUN_004168c0(double *param_1)

{
  char cVar1;
  int iVar2;
  double *extraout_EAX;
  char local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  char local_24 [32];
  
  local_2c = 0;
  while( true ) {
    if (__mb_cur_max < 2) {
      local_30 = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 0x107;
    }
    else {
      local_30 = _isctype((int)*DAT_0045f860,0x107);
    }
    if (((local_30 == 0) && (*DAT_0045f860 != '_')) || (0x1e < local_2c)) break;
    if (__mb_cur_max < 2) {
      local_34 = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 1;
    }
    else {
      local_34 = _isctype((int)*DAT_0045f860,1);
    }
    if (local_34 == 0) {
      local_38 = *DAT_0045f860;
    }
    else {
      iVar2 = tolower((int)*DAT_0045f860);
      local_38 = (char)iVar2;
    }
    local_24[local_2c] = local_38;
    local_2c = local_2c + 1;
    DAT_0045f860 = DAT_0045f860 + 1;
  }
  local_24[local_2c] = '\0';
  cVar1 = *DAT_0045f860;
  DAT_0045f860 = DAT_0045f860 + 1;
  if (cVar1 == '(') {
    iVar2 = FUN_004398cc(local_24,0x450048,DAT_004503a8,0x10,FUN_00416efc);
    if (iVar2 == 0) {
      FUN_004131f9((uint *)s_Invalid_function_name_004544b0,local_24);
      FUN_004167ef((undefined4 *)param_1);
      param_1 = (double *)0x0;
    }
    else {
      switch(*(undefined1 *)(iVar2 + 4)) {
      case 1:
      case 6:
        param_1 = (double *)FUN_00417168((undefined4 *)param_1,(int)*(char *)(iVar2 + 4));
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 2:
        param_1 = (double *)FUN_004175d8((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 3:
        param_1 = (double *)FUN_0041769d((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 4:
        FUN_00417736((undefined4 *)param_1);
        param_1 = extraout_EAX;
        if (extraout_EAX == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 5:
        param_1 = (double *)FUN_00417d6a((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 7:
        param_1 = (double *)FUN_00417e90((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 8:
      case 9:
      case 0xb:
      case 0x1b:
      case 0x25:
      case 0x26:
        param_1 = FUN_00418711((undefined4 *)param_1,(int)*(char *)(iVar2 + 4));
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 10:
        param_1 = (double *)FUN_004189ba((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0xc:
      case 0xd:
      case 0xe:
      case 0xf:
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x13:
      case 0x14:
      case 0x15:
      case 0x18:
      case 0x1c:
      case 0x1d:
      case 0x1e:
      case 0x1f:
      case 0x20:
        param_1 = FUN_00419493((undefined4 *)param_1,*(undefined **)(iVar2 + 8));
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x16:
      case 0x17:
        param_1 = FUN_004195e5((undefined4 *)param_1,*(undefined **)(iVar2 + 0xc));
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x19:
        param_1 = FUN_00418b0d((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x1a:
      case 0x23:
      case 0x28:
      case 0x29:
      case 0x2a:
      case 0x2c:
      case 0x2d:
      case 0x31:
      case 0x32:
        param_1 = (double *)FUN_00416f22((undefined4 *)param_1,(int)*(char *)(iVar2 + 4));
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x21:
      case 0x22:
        param_1 = FUN_00418eba(param_1,(int)*(char *)(iVar2 + 4));
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x24:
        param_1 = FUN_0041905d(param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x27:
        param_1 = (double *)FUN_0041913c((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x2b:
        param_1 = (double *)FUN_00417347((uint *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x2e:
        param_1 = (double *)FUN_00418033((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x2f:
        param_1 = (double *)FUN_004180ea((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x30:
        param_1 = (double *)FUN_00418453((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x33:
        param_1 = (double *)FUN_004192d1((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x34:
        param_1 = (double *)FUN_00418c1e((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x35:
        param_1 = (double *)FUN_00418deb((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x36:
        param_1 = (double *)FUN_00418cdb((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x37:
        param_1 = (double *)FUN_00418d12((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
        break;
      case 0x38:
        param_1 = (double *)FUN_00418d81((undefined4 *)param_1);
        if (param_1 == (double *)0x0) {
          return (double *)0x0;
        }
      }
      cVar1 = *DAT_0045f860;
      DAT_0045f860 = DAT_0045f860 + 1;
      if (cVar1 == ')') {
        if (*(int *)((int)param_1 + 0x3c) < 0) {
          FUN_004167ef((undefined4 *)param_1);
          FUN_00413085((uint *)s_External_reference_not_allowed_i_0045450c);
          param_1 = (double *)0x0;
        }
      }
      else {
        FUN_004167ef((undefined4 *)param_1);
        FUN_00413085((uint *)s_Extra_characters_in_function_arg_004544c8);
        param_1 = (double *)0x0;
      }
    }
  }
  else {
    FUN_004167ef((undefined4 *)param_1);
    FUN_00413085((uint *)s_Missing_____for_function_00454494);
    param_1 = (double *)0x0;
  }
  return param_1;
}


/* ==== FUN_00416efc @ 00416efc ==== */

void __cdecl FUN_00416efc(char *param_1,undefined4 *param_2)

{
  uint n;
  
  n = strlen((char *)*param_2);
  strncmp(param_1,(char *)*param_2,n);
  return;
}


/* ==== FUN_00416f22 @ 00416f22 ==== */

undefined4 * __cdecl FUN_00416f22(undefined4 *param_1,undefined4 param_2)

{
  int local_10;
  uint local_c;
  
  switch(param_2) {
  case 0x1a:
    param_1[2] = DAT_0045ebec;
    break;
  case 0x23:
    param_1[2] = (uint)(DAT_0044f790 != '\0');
    break;
  case 0x28:
    param_1[2] = DAT_0045f930;
    break;
  case 0x29:
    if (__mb_cur_max < 2) {
      local_c = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 1;
    }
    else {
      local_c = _isctype((int)*DAT_0045f860,1);
    }
    if (local_c == 0) {
      local_10 = (int)*DAT_0045f860;
    }
    else {
      local_10 = tolower((int)*DAT_0045f860);
    }
    if (local_10 == 0x6c) {
      param_1[2] = DAT_0045f8b8;
    }
    else {
      if (local_10 != 0x72) {
        FUN_00413085((uint *)s_Illegal_function_argument_00454554);
        FUN_004167ef(param_1);
        return (undefined4 *)0x0;
      }
      param_1[2] = DAT_0045f8a8;
    }
    DAT_0045f860 = DAT_0045f860 + 1;
    break;
  case 0x2a:
    if (DAT_0045fb6c == 0) {
      FUN_004133a9((uint *)s_Macro_expansion_not_active_00454538);
      param_1[2] = 0;
    }
    else {
      param_1[2] = *(undefined4 *)(DAT_0045fb6c + 4);
    }
    break;
  case 0x2c:
    param_1[2] = DAT_0045ebe4 & 0xffffff;
    break;
  case 0x2d:
    param_1[2] = (uint)(DAT_0045fb6c != 0);
    break;
  case 0x31:
    param_1[2] = DAT_0045fcb0;
    break;
  case 0x32:
    param_1[2] = DAT_0045fcb4;
  }
  param_1[1] = 0;
  *param_1 = 0;
  param_1[4] = 0x100;
  param_1[8] = 4;
  param_1[7] = 4;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[6] = param_1[6] & 0xffffefff;
  param_1[5] = 3;
  return param_1;
}


/* ==== FUN_00417168 @ 00417168 ==== */

undefined4 * __cdecl FUN_00417168(undefined4 *param_1,int param_2)

{
  char cVar1;
  undefined1 uVar2;
  uint *puVar3;
  undefined4 *puVar4;
  
  cVar1 = '\0';
  if ((param_2 == 1) && ((*DAT_0045f860 == '\'' || (*DAT_0045f860 == '\"')))) {
    cVar1 = *DAT_0045f860;
    DAT_0045f860 = DAT_0045f860 + 1;
  }
  puVar3 = (uint *)FUN_0043b448();
  uVar2 = DAT_0045ea50;
  if (puVar3 == (uint *)0x0) {
    FUN_004167ef(param_1);
    param_1 = (undefined4 *)0x0;
  }
  else {
    if (cVar1 != '\0') {
      if (*DAT_0045f860 != cVar1) {
        FUN_00413085((uint *)s_Missing_or_mismatched_quote_00454570);
        FUN_004167ef(param_1);
        return (undefined4 *)0x0;
      }
      DAT_0045f860 = DAT_0045f860 + 1;
    }
    DAT_0045ea50 = 1;
    param_1[2] = 0;
    param_1[1] = 0;
    *param_1 = 0;
    if (param_2 == 1) {
      if (cVar1 == '\0') {
        puVar4 = FUN_00438441(puVar3,2);
        if (DAT_0045f8fc == 1) {
          if (puVar4 == (undefined4 *)0x0) {
            FUN_00439326();
          }
          else {
            param_1[2] = 1;
          }
        }
        else if (DAT_0045f8fc == 2) {
          if (*DAT_0045fc70 == DAT_0045f934) {
            FUN_00439374();
          }
          else {
            param_1[2] = 1;
          }
        }
      }
      else {
        puVar4 = FUN_0043012d(puVar3,2);
        if (puVar4 != (undefined4 *)0x0) {
          param_1[2] = 1;
        }
      }
    }
    else {
      puVar4 = FUN_0041faa5(puVar3,2);
      if (puVar4 != (undefined4 *)0x0) {
        param_1[2] = 1;
      }
    }
    DAT_0045ea50 = uVar2;
    param_1[4] = 0x100;
    param_1[8] = 4;
    param_1[7] = 4;
    param_1[9] = 0;
    param_1[10] = 0;
    param_1[6] = param_1[6] & 0xffffefff;
    param_1[5] = 3;
  }
  return param_1;
}


/* ==== FUN_00417347 @ 00417347 ==== */

uint * __cdecl FUN_00417347(uint *param_1)

{
  char *a;
  int iVar1;
  undefined4 *local_18;
  int local_14;
  undefined4 *local_10;
  uint local_c;
  
  if (DAT_0045fb6c == (int *)0x0) {
    FUN_004133a9((uint *)s_Macro_expansion_not_active_0045458c);
    param_1[2] = 0;
    param_1[4] = 0x100;
    param_1[8] = 4;
    param_1[7] = 4;
    param_1[9] = 0;
    param_1[10] = 0;
    param_1[6] = param_1[6] & 0xffffefff;
    param_1[5] = 3;
    return param_1;
  }
  if (*DAT_0045f860 == '\'') {
    DAT_0045f860 = DAT_0045f860 + 1;
    a = FUN_0043b448();
    if (a == (char *)0x0) {
      FUN_004167ef(param_1);
      return (uint *)0x0;
    }
    if (*DAT_0045f860 != '\'') {
      FUN_00413085((uint *)s_Missing_quote_004545a8);
      FUN_004167ef(param_1);
      return (uint *)0x0;
    }
    DAT_0045f860 = DAT_0045f860 + 1;
    local_10 = *(undefined4 **)(*DAT_0045fb6c + 0x10);
    while ((local_10 != (undefined4 *)0x0 &&
           ((*a != *(char *)*local_10 || (iVar1 = strcmp(a,(char *)*local_10), iVar1 != 0))))) {
      local_10 = (undefined4 *)local_10[2];
    }
    if (local_10 == (undefined4 *)0x0) {
      FUN_004131f9((uint *)s_Dummy_argument_not_found_004545b8,a);
      FUN_004167ef(param_1);
      return (uint *)0x0;
    }
    local_c = local_10[1];
  }
  else {
    FUN_004167ef(param_1);
    param_1 = (uint *)FUN_00414a26();
    if (param_1 == (uint *)0x0) {
      return (uint *)0x0;
    }
    if (param_1[4] == 0x200) {
      FUN_0040b24c(*param_1,param_1[1],3,(int *)param_1);
    }
    local_c = param_1[2];
  }
  param_1[2] = 0;
  param_1[1] = 0;
  *param_1 = 0;
  if ((local_c != 0) && ((int)local_c <= DAT_0045fb6c[1])) {
    local_18 = (undefined4 *)DAT_0045fb6c[5];
    for (local_14 = 1; local_14 < (int)local_c; local_14 = local_14 + 1) {
      local_18 = (undefined4 *)local_18[1];
    }
    if (*(char *)*local_18 != '\0') {
      param_1[2] = 1;
    }
  }
  param_1[4] = 0x100;
  param_1[8] = 4;
  param_1[7] = 4;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[6] = param_1[6] & 0xffffefff;
  param_1[5] = 3;
  return param_1;
}


/* ==== FUN_004175d8 @ 004175d8 ==== */

undefined4 * __cdecl FUN_004175d8(undefined4 *param_1)

{
  undefined1 uVar1;
  int *piVar2;
  
  uVar1 = DAT_0045ea50;
  DAT_0045ea50 = 1;
  DAT_0045eb9c = 0;
  param_1[2] = 0;
  param_1[1] = 0;
  *param_1 = 0;
  piVar2 = FUN_00414a26();
  if (piVar2 != (int *)0x0) {
    if (DAT_0045eb9c == 0) {
      param_1[2] = 1;
    }
    FUN_004167ef(piVar2);
  }
  DAT_0045ea50 = uVar1;
  param_1[4] = 0x100;
  param_1[8] = 4;
  param_1[7] = 4;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[6] = param_1[6] & 0xffffefff;
  param_1[5] = 3;
  return param_1;
}


/* ==== FUN_0041769d @ 0041769d ==== */

undefined4 * __cdecl FUN_0041769d(undefined4 *param_1)

{
  int *piVar1;
  
  FUN_004167ef(param_1);
  piVar1 = FUN_00414a26();
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1[1] = 0;
    *piVar1 = 0;
    piVar1[2] = (uint)(piVar1[4] == 0x100);
    piVar1[4] = 0x100;
    piVar1[8] = 4;
    piVar1[7] = 4;
    piVar1[9] = 0;
    piVar1[10] = 0;
    piVar1[6] = piVar1[6] & 0xffffefff;
    piVar1[5] = 3;
  }
  return piVar1;
}


/* ==== FUN_00417736 @ 00417736 ==== */

/* WARNING: Variable defined which should be unmapped: param_1 */

undefined4 * __cdecl FUN_00417736(undefined4 *param_1)

{
  char *pcVar1;
  int iVar2;
  int *piVar3;
  uint local_38;
  uint local_34;
  int local_30;
  uint local_2c;
  int local_28;
  undefined4 local_24;
  int local_20;
  undefined4 local_1c;
  int local_18;
  int *local_14;
  int local_10;
  int *local_c;
  uint local_8;
  
  local_18 = -1;
  local_8 = (uint)(DAT_0045f8c0 != DAT_0045f8cc);
  if (__mb_cur_max < 2) {
    local_2c = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 1;
  }
  else {
    local_2c = _isctype((int)*DAT_0045f860,1);
  }
  if (local_2c == 0) {
    local_30 = (int)*DAT_0045f860;
  }
  else {
    local_30 = tolower((int)*DAT_0045f860);
  }
  local_10 = local_30;
  pcVar1 = DAT_0045f860 + 1;
  if (DAT_0045f860[1] == ',') {
    DAT_0045f860 = DAT_0045f860 + 2;
    if (__mb_cur_max < 2) {
      local_34 = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 1;
    }
    else {
      local_34 = _isctype((int)*DAT_0045f860,1);
    }
    if (local_34 == 0) {
      local_38 = (uint)*DAT_0045f860;
    }
    else {
      local_38 = tolower((int)*DAT_0045f860);
    }
    local_18 = FUN_0043a91e(local_38);
    if (local_18 == -1) {
      local_18 = FUN_004147ee();
      pcVar1 = DAT_0045f860;
      if (local_18 == -1) {
        FUN_004167ef(param_1);
        return param_1;
      }
    }
    else {
      pcVar1 = DAT_0045f860 + 1;
    }
  }
  DAT_0045f860 = pcVar1;
  if ((local_8 == 0) && ((local_18 < 0 || (local_18 == DAT_0045f8a8)))) {
    param_1[2] = *(undefined4 *)(DAT_0045fb88[9] + 0x10);
    param_1[7] = DAT_0045f8a0;
    param_1[8] = DAT_0045f8a4;
    param_1[9] = DAT_0045f8a8;
    param_1[10] = DAT_0045f8ac;
    if (DAT_0044f794 == '\0') {
      param_1[6] = param_1[6] & 0xffffefff;
    }
    else {
      param_1[6] = param_1[6] | 0x1000;
    }
    param_1[0x11] = -(uint)(DAT_0045ebc4 != 0) & DAT_0045ebc0;
    param_1[0x12] = 0;
    param_1[0x15] = DAT_0045fb88[7];
    param_1[0xf] = *(undefined4 *)(PTR_DAT_0044f978 + 8);
    param_1[0x10] = *(undefined4 *)(PTR_DAT_0044f97c + 8);
    param_1[4] = 0x100;
    param_1[5] = 3;
  }
  else {
    if (local_10 == 0x6c) {
      local_28 = DAT_0045f8b0;
      local_24 = DAT_0045f8b4;
      local_20 = DAT_0045f8b8;
      local_1c = DAT_0045f8bc;
      if (-1 < local_18) {
        local_20 = local_18;
      }
      local_14 = FUN_0042c829((int)PTR_DAT_0044f97c,&local_28,
                              -(uint)(DAT_0044f798 != '\0') & 0x1000 |
                              -(uint)(DAT_0045ebc4 != 0) & 0x2000,0);
      local_14[8] = local_14[8] + 1;
      param_1[2] = *(undefined4 *)(local_14[9] + 0x10);
      param_1[7] = local_28;
      param_1[8] = local_24;
      param_1[9] = local_20;
      param_1[10] = local_1c;
      if (DAT_0044f798 == '\0') {
        param_1[6] = param_1[6] & 0xffffefff;
      }
      else {
        param_1[6] = param_1[6] | 0x1000;
      }
      param_1[0x11] = -(uint)(DAT_0045ebc4 != 0) & DAT_0045ebc0;
      param_1[0x12] = 0;
      param_1[0x15] = local_14[7];
    }
    else {
      if (local_10 != 0x72) {
        FUN_00413085((uint *)s_Illegal_function_argument_004545d4);
        FUN_004167ef(param_1);
        return param_1;
      }
      local_28 = DAT_0045f8a0;
      local_24 = DAT_0045f8a4;
      local_20 = DAT_0045f8a8;
      local_1c = DAT_0045f8ac;
      if (-1 < local_18) {
        local_20 = local_18;
      }
      local_14 = FUN_0042c829((int)PTR_DAT_0044f97c,&local_28,
                              -(uint)(DAT_0044f794 != '\0') & 0x1000 |
                              -(uint)(DAT_0045ebc4 != 0) & 0x2000 | -(uint)(local_8 != 0) & 0x4000,0
                             );
      local_c = local_14;
      if ((local_8 != 0) &&
         (local_14 = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8b0,
                                  -(uint)(DAT_0044f798 != '\0') & 0x1000 |
                                  -(uint)(DAT_0045ebc4 != 0) & 0x2000,0), DAT_0045eadc != '\0')) {
        *(uint *)(local_14[9] + 0x30) = *(uint *)(local_14[9] + 0x30) | 0x800;
      }
      local_14[8] = local_14[8] + 1;
      param_1[2] = *(undefined4 *)(local_c[9] + 0x10);
      param_1[7] = local_28;
      param_1[8] = local_24;
      param_1[9] = local_20;
      param_1[10] = local_1c;
      if (DAT_0044f794 == '\0') {
        param_1[6] = param_1[6] & 0xffffefff;
      }
      else {
        param_1[6] = param_1[6] | 0x1000;
      }
      param_1[0x11] = -(uint)(DAT_0045ebc4 != 0) & DAT_0045ebc0;
      param_1[0x12] = -(uint)(local_8 != 0) & DAT_0045ebe8;
      param_1[0x15] = local_14[7];
    }
    DAT_0045fb88 = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8a0,
                                -(uint)(DAT_0044f794 != '\0') & 0x1000 |
                                -(uint)(DAT_0045ebc4 != 0) & 0x2000 | -(uint)(local_8 != 0) & 0x4000
                                ,0);
    DAT_0045f8c0 = DAT_0045fb88[9] + 0x10;
    iVar2 = DAT_0045f8c0;
    piVar3 = DAT_0045fb88;
    if (local_8 != 0) {
      local_c = DAT_0045fb88;
      DAT_0045fb8c = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8b0,
                                  -(uint)(DAT_0044f798 != '\0') & 0x1000 |
                                  -(uint)(DAT_0045ebc4 != 0) & 0x2000,0);
      DAT_0045f8cc = DAT_0045fb8c[9] + 0x10;
      iVar2 = DAT_0045f8cc;
      piVar3 = DAT_0045fb8c;
      if (DAT_0045eadc != '\0') {
        *(uint *)(DAT_0045fb8c[9] + 0x30) = *(uint *)(DAT_0045fb8c[9] + 0x30) | 0x800;
        iVar2 = DAT_0045f8cc;
        piVar3 = DAT_0045fb8c;
      }
    }
    DAT_0045fb8c = piVar3;
    DAT_0045f8cc = iVar2;
    param_1[0xf] = *(undefined4 *)(PTR_DAT_0044f978 + 8);
    param_1[0x10] = *(undefined4 *)(PTR_DAT_0044f97c + 8);
    param_1[4] = 0x100;
    param_1[5] = 3;
  }
  return param_1;
}


/* ==== FUN_00417d6a @ 00417d6a ==== */

undefined4 * __cdecl FUN_00417d6a(undefined4 *param_1)

{
  int *piVar1;
  
  FUN_004167ef(param_1);
  piVar1 = FUN_00414a26();
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    switch(piVar1[7]) {
    case 0:
      piVar1[2] = 4;
      break;
    case 1:
      piVar1[2] = 1;
      break;
    case 2:
      piVar1[2] = 2;
      break;
    case 3:
      piVar1[2] = 3;
      break;
    default:
      piVar1[2] = 0;
      break;
    case 0x1c:
      piVar1[2] = 5;
    }
    piVar1[1] = 0;
    *piVar1 = 0;
    piVar1[4] = 0x100;
    piVar1[8] = 4;
    piVar1[7] = 4;
    piVar1[9] = 0;
    piVar1[10] = 0;
    piVar1[6] = piVar1[6] & 0xffffefff;
    piVar1[5] = 3;
  }
  return piVar1;
}


/* ==== FUN_00417e90 @ 00417e90 ==== */

undefined4 * __cdecl FUN_00417e90(undefined4 *param_1)

{
  char cVar1;
  uint uVar2;
  char *dst;
  int iVar3;
  undefined4 local_c;
  
  DAT_0045f860 = FUN_0043b08d(DAT_0045f860,&DAT_0045f220);
  if (DAT_0045f860 == (char *)0x0) {
    FUN_004167ef(param_1);
    return (undefined4 *)0x0;
  }
  cVar1 = *DAT_0045f860;
  DAT_0045f860 = DAT_0045f860 + 1;
  if (cVar1 == ',') {
    uVar2 = strlen(&DAT_0045f220);
    dst = (char *)FUN_00439857(uVar2 + 1);
    strcpy(dst,&DAT_0045f220);
    DAT_0045f860 = FUN_0043b08d(DAT_0045f860,&DAT_0045f220);
    if (DAT_0045f860 != (char *)0x0) {
      param_1[1] = 0;
      *param_1 = 0;
      if ((DAT_0045f220 == *dst) && (iVar3 = strcmp(&DAT_0045f220,dst), iVar3 == 0)) {
        local_c = 1;
      }
      else {
        local_c = 0;
      }
      param_1[2] = local_c;
      FUN_004398b5(dst);
      param_1[4] = 0x100;
      param_1[8] = 4;
      param_1[7] = 4;
      param_1[9] = 0;
      param_1[10] = 0;
      param_1[6] = param_1[6] & 0xffffefff;
      param_1[5] = 3;
      return param_1;
    }
    FUN_004398b5(dst);
    FUN_004167ef(param_1);
    return (undefined4 *)0x0;
  }
  FUN_00413085((uint *)s_Syntax_error___expected_comma_004545f0);
  FUN_004167ef(param_1);
  return (undefined4 *)0x0;
}


/* ==== FUN_00418033 @ 00418033 ==== */

undefined4 * __cdecl FUN_00418033(undefined4 *param_1)

{
  uint uVar1;
  char local_204 [512];
  
  DAT_0045f860 = FUN_0043b08d(DAT_0045f860,local_204);
  if (DAT_0045f860 == (char *)0x0) {
    FUN_004167ef(param_1);
    param_1 = (undefined4 *)0x0;
  }
  else {
    param_1[1] = 0;
    *param_1 = 0;
    uVar1 = strlen(local_204);
    param_1[2] = uVar1;
    param_1[4] = 0x100;
    param_1[8] = 4;
    param_1[7] = 4;
    param_1[9] = 0;
    param_1[10] = 0;
    param_1[6] = param_1[6] & 0xffffefff;
    param_1[5] = 3;
  }
  return param_1;
}


/* ==== FUN_004180ea @ 004180ea ==== */

undefined4 * __cdecl FUN_004180ea(undefined4 *param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  uint local_420;
  int local_41c;
  char local_414 [512];
  uint local_214;
  uint local_210;
  char local_20c [512];
  uint local_c;
  char *local_8;
  
  local_41c = 0;
  bVar2 = false;
  DAT_0045f860 = FUN_0043b08d(DAT_0045f860,local_414);
  if (DAT_0045f860 == (char *)0x0) {
    FUN_004167ef(param_1);
    param_1 = (undefined4 *)0x0;
  }
  else {
    local_214 = strlen(local_414);
    if (local_214 == 0) {
      param_1[2] = 0;
      param_1[1] = 0;
      *param_1 = 0;
      param_1[4] = 0x100;
      param_1[8] = 4;
      param_1[7] = 4;
      param_1[9] = 0;
      param_1[10] = 0;
      param_1[6] = param_1[6] & 0xffffefff;
      param_1[5] = 3;
    }
    else {
      cVar1 = *DAT_0045f860;
      DAT_0045f860 = DAT_0045f860 + 1;
      if (cVar1 == ',') {
        DAT_0045f860 = FUN_0043b08d(DAT_0045f860,local_20c);
        if (DAT_0045f860 == (char *)0x0) {
          FUN_004167ef(param_1);
          param_1 = (undefined4 *)0x0;
        }
        else {
          local_c = strlen(local_20c);
          if (local_c == 0) {
            param_1[1] = 0;
            *param_1 = 0;
            param_1[2] = local_214;
            param_1[4] = 0x100;
            param_1[8] = 4;
            param_1[7] = 4;
            param_1[9] = 0;
            param_1[10] = 0;
            param_1[6] = param_1[6] & 0xffffefff;
            param_1[5] = 3;
          }
          else {
            if (*DAT_0045f860 == ',') {
              DAT_0045f860 = DAT_0045f860 + 1;
              local_41c = FUN_0041479f();
              if (local_41c == -1) {
                FUN_004167ef(param_1);
                return (undefined4 *)0x0;
              }
              if ((int)local_214 <= local_41c) {
                FUN_004167ef(param_1);
                FUN_00413085((uint *)s_Start_position_greater_than_sour_00454630);
                return (undefined4 *)0x0;
              }
            }
            local_210 = local_214;
            local_8 = local_414 + local_41c;
            while( true ) {
              if ((*local_8 == '\0') || ((int)local_214 < (int)local_c)) goto LAB_004183ba;
              iVar3 = strncmp(local_8,local_20c,local_c);
              if (iVar3 == 0) break;
              local_8 = local_8 + 1;
              local_214 = local_214 - 1;
            }
            bVar2 = true;
LAB_004183ba:
            param_1[1] = 0;
            *param_1 = 0;
            if (bVar2) {
              local_420 = (int)local_8 - (int)local_414;
            }
            else {
              local_420 = local_210;
            }
            param_1[2] = local_420;
            param_1[4] = 0x100;
            param_1[8] = 4;
            param_1[7] = 4;
            param_1[9] = 0;
            param_1[10] = 0;
            param_1[6] = param_1[6] & 0xffffefff;
            param_1[5] = 3;
          }
        }
      }
      else {
        FUN_00413085((uint *)s_Syntax_error___expected_comma_00454610);
        FUN_004167ef(param_1);
        param_1 = (undefined4 *)0x0;
      }
    }
  }
  return param_1;
}


/* ==== FUN_00418453 @ 00418453 ==== */

undefined4 * __cdecl FUN_00418453(undefined4 *param_1)

{
  char cVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  int local_10;
  
  local_10 = 0;
  FUN_004167ef(param_1);
  piVar3 = FUN_00414862();
  if (piVar3 == (int *)0x0) {
    piVar3 = (int *)0x0;
  }
  else if (piVar3[4] == 0x100) {
    if ((piVar3[6] & 0x800U) == 0) {
      uVar5 = piVar3[2];
      cVar1 = *DAT_0045f860;
      DAT_0045f860 = DAT_0045f860 + 1;
      if (cVar1 == ',') {
        FUN_004167ef(piVar3);
        piVar3 = FUN_00414862();
        if (piVar3 == (int *)0x0) {
          piVar3 = (int *)0x0;
        }
        else if (piVar3[4] == 0x100) {
          if ((piVar3[6] & 0x800U) == 0) {
            uVar2 = piVar3[2];
            cVar1 = *DAT_0045f860;
            DAT_0045f860 = DAT_0045f860 + 1;
            if (cVar1 == ',') {
              iVar4 = FUN_0041479f();
              if (iVar4 == -1) {
                FUN_004167ef(piVar3);
                piVar3 = (int *)0x0;
              }
              else if (iVar4 < 0x19) {
                if (*DAT_0045f860 == ',') {
                  DAT_0045f860 = DAT_0045f860 + 1;
                  local_10 = FUN_0041479f();
                  if (local_10 == -1) {
                    FUN_004167ef(piVar3);
                    return (undefined4 *)0x0;
                  }
                  if (0x17 < local_10) {
                    FUN_004167ef(piVar3);
                    FUN_00413085((uint *)s_Start_argument_greater_than_mach_00454774);
                    return (undefined4 *)0x0;
                  }
                }
                piVar3[1] = 0;
                *piVar3 = 0;
                uVar5 = FUN_0043bd1e(uVar5,uVar2,(byte)local_10,(byte)iVar4);
                piVar3[2] = uVar5;
                piVar3[4] = 0x100;
                piVar3[8] = 4;
                piVar3[7] = 4;
                piVar3[9] = 0;
                piVar3[10] = 0;
                piVar3[6] = piVar3[6] & 0xffffefff;
                piVar3[5] = 3;
              }
              else {
                FUN_004167ef(piVar3);
                FUN_00413085((uint *)s_Width_argument_greater_than_mach_00454744);
                piVar3 = (int *)0x0;
              }
            }
            else {
              FUN_00413085((uint *)s_Syntax_error___expected_comma_00454724);
              FUN_004167ef(piVar3);
              piVar3 = (int *)0x0;
            }
          }
          else {
            FUN_004167ef(piVar3);
            FUN_00413085((uint *)s_Value_argument_larger_than_machi_004546f4);
            piVar3 = (int *)0x0;
          }
        }
        else {
          FUN_004167ef(piVar3);
          FUN_00413085((uint *)s_Expression_result_must_be_intege_004546d0);
          piVar3 = (int *)0x0;
        }
      }
      else {
        FUN_00413085((uint *)s_Syntax_error___expected_comma_004546b0);
        FUN_004167ef(piVar3);
        piVar3 = (int *)0x0;
      }
    }
    else {
      FUN_004167ef(piVar3);
      FUN_00413085((uint *)s_Base_argument_larger_than_machin_00454684);
      piVar3 = (int *)0x0;
    }
  }
  else {
    FUN_004167ef(piVar3);
    FUN_00413085((uint *)s_Expression_result_must_be_intege_00454660);
    piVar3 = (int *)0x0;
  }
  return piVar3;
}


/* ==== FUN_00418711 @ 00418711 ==== */

double * __cdecl FUN_00418711(undefined4 *param_1,undefined4 param_2)

{
  double *pdVar1;
  float10 fVar2;
  
  FUN_004167ef(param_1);
  pdVar1 = (double *)FUN_00414a26();
  if (pdVar1 == (double *)0x0) {
    pdVar1 = (double *)0x0;
  }
  else if (((ulonglong)pdVar1[3] & 0x1000) == 0) {
    switch(param_2) {
    case 8:
      if (*(int *)(pdVar1 + 2) == 0x200) {
        FUN_0040b24c(*(uint *)pdVar1,*(uint *)((int)pdVar1 + 4),6,(int *)pdVar1);
      }
      *(undefined4 *)(pdVar1 + 2) = 0x100;
      FUN_004165e3((int *)pdVar1);
      break;
    case 9:
      if (*(int *)(pdVar1 + 2) == 0x100) {
        fVar2 = FUN_0040b1e5(pdVar1);
        *pdVar1 = (double)fVar2;
      }
      *(undefined4 *)(pdVar1 + 2) = 0x200;
      *(undefined4 *)((int)pdVar1 + 0x14) = 8;
      break;
    default:
      FUN_00413085((uint *)s_Illegal_function_argument_004547c4);
      FUN_004167ef((undefined4 *)pdVar1);
      return (double *)0x0;
    case 0xb:
      if (*(int *)(pdVar1 + 2) == 0x100) {
        fVar2 = FUN_0040b1e5(pdVar1);
        *pdVar1 = (double)fVar2;
      }
      *(undefined4 *)(pdVar1 + 2) = 0x200;
      FUN_0040b5a4(*(undefined4 *)pdVar1,*(undefined4 *)((int)pdVar1 + 4),3,(int *)pdVar1);
      break;
    case 0x1b:
      if (*(int *)(pdVar1 + 2) == 0x200) {
        FUN_0040b24c(*(uint *)pdVar1,*(uint *)((int)pdVar1 + 4),3,(int *)pdVar1);
      }
      fVar2 = FUN_0040b53d(pdVar1);
      *pdVar1 = (double)fVar2;
      *(undefined4 *)(pdVar1 + 2) = 0x200;
      *(undefined4 *)((int)pdVar1 + 0x14) = 8;
      break;
    case 0x25:
      if (*(int *)(pdVar1 + 2) == 0x100) {
        fVar2 = FUN_0040b1e5(pdVar1);
        *pdVar1 = (double)fVar2;
      }
      *(undefined4 *)(pdVar1 + 2) = 0x200;
      FUN_0040b5a4(*(undefined4 *)pdVar1,*(undefined4 *)((int)pdVar1 + 4),6,(int *)pdVar1);
      break;
    case 0x26:
      if (*(int *)(pdVar1 + 2) == 0x200) {
        FUN_0040b24c(*(uint *)pdVar1,*(uint *)((int)pdVar1 + 4),6,(int *)pdVar1);
      }
      fVar2 = FUN_0040b53d(pdVar1);
      *pdVar1 = (double)fVar2;
      *(undefined4 *)(pdVar1 + 2) = 0x200;
      *(undefined4 *)((int)pdVar1 + 0x14) = 8;
    }
    *(undefined4 *)(pdVar1 + 4) = 4;
    *(undefined4 *)((int)pdVar1 + 0x1c) = 4;
    *(undefined4 *)((int)pdVar1 + 0x24) = 0;
    *(undefined4 *)(pdVar1 + 5) = 0;
    *(uint *)(pdVar1 + 3) = *(uint *)(pdVar1 + 3) & 0xffffefff;
  }
  else {
    FUN_00413085((uint *)s_Relative_expression_not_allowed_004547a4);
    FUN_004167ef((undefined4 *)pdVar1);
    pdVar1 = (double *)0x0;
  }
  return pdVar1;
}


/* ==== FUN_004189ba @ 004189ba ==== */

undefined4 * __cdecl FUN_004189ba(undefined4 *param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
  FUN_004167ef(param_1);
  cVar1 = *DAT_0045f860;
  DAT_0045f860 = DAT_0045f860 + 1;
  iVar2 = FUN_0043a807((int)cVar1);
  if (iVar2 == 0xa2c2a) {
    FUN_00413085((uint *)s_Invalid_memory_space_attribute_004547e0);
    piVar3 = (int *)0x0;
  }
  else {
    cVar1 = *DAT_0045f860;
    DAT_0045f860 = DAT_0045f860 + 1;
    if (cVar1 == ',') {
      piVar3 = FUN_00414a26();
      if (piVar3 == (int *)0x0) {
        FUN_004167ef((undefined4 *)0x0);
        piVar3 = (int *)0x0;
      }
      else {
        if (iVar2 == 4) {
          piVar3[6] = piVar3[6] & 0xffff8fff;
        }
        else {
          if (piVar3[4] != 0x100) {
            FUN_004167ef(piVar3);
            FUN_00413085((uint *)s_Expression_result_must_be_intege_00454820);
            return (undefined4 *)0x0;
          }
          uVar4 = FUN_0040a7ea((int)piVar3);
          if (((int)uVar4 < 0) || (0xffffff < uVar4)) {
            FUN_004167ef(piVar3);
            FUN_00413085((uint *)s_Expression_result_too_large_00454844);
            return (undefined4 *)0x0;
          }
        }
        piVar3[8] = iVar2;
        piVar3[7] = iVar2;
        piVar3[9] = 0;
        piVar3[10] = 0;
      }
    }
    else {
      FUN_00413085((uint *)s_Syntax_error___expected_comma_00454800);
      piVar3 = (int *)0x0;
    }
  }
  return piVar3;
}


/* ==== FUN_00418b0d @ 00418b0d ==== */

double * __cdecl FUN_00418b0d(undefined4 *param_1)

{
  double *pdVar1;
  float10 fVar2;
  double local_c;
  
  FUN_004167ef(param_1);
  pdVar1 = (double *)FUN_00414a26();
  if (pdVar1 == (double *)0x0) {
    FUN_004167ef((undefined4 *)0x0);
    pdVar1 = (double *)0x0;
  }
  else {
    if (*(int *)(pdVar1 + 2) == 0x100) {
      fVar2 = FUN_0040b1e5(pdVar1);
      local_c = (double)fVar2;
    }
    else {
      local_c = *pdVar1;
    }
    *(undefined4 *)((int)pdVar1 + 4) = 0;
    *(undefined4 *)pdVar1 = 0;
    *(undefined4 *)(pdVar1 + 2) = 0x100;
    *(undefined4 *)(pdVar1 + 4) = 4;
    *(undefined4 *)((int)pdVar1 + 0x1c) = 4;
    *(undefined4 *)((int)pdVar1 + 0x24) = 0;
    *(undefined4 *)(pdVar1 + 5) = 0;
    *(uint *)(pdVar1 + 3) = *(uint *)(pdVar1 + 3) & 0xffffefff;
    *(undefined4 *)((int)pdVar1 + 0x14) = 3;
    if (0.0 <= local_c) {
      if (local_c <= 0.0) {
        *(undefined4 *)(pdVar1 + 1) = 0;
      }
      else {
        *(undefined4 *)(pdVar1 + 1) = 1;
      }
    }
    else {
      *(undefined4 *)(pdVar1 + 1) = 1;
      FUN_0040a80c(pdVar1);
    }
  }
  return pdVar1;
}


/* ==== FUN_00418c1e @ 00418c1e ==== */

int __cdecl FUN_00418c1e(undefined4 *param_1)

{
  char *pcVar1;
  char *dst;
  int *piVar2;
  char *local_c;
  
  FUN_004167ef(param_1);
  dst = DAT_0045f864;
  piVar2 = FUN_00414a26();
  if (piVar2 == (int *)0x0) {
    FUN_004167ef((undefined4 *)0x0);
    piVar2 = (int *)0x0;
  }
  else {
    pcVar1 = DAT_0045f864;
    if (piVar2[0xf] < 0) {
      while (local_c = pcVar1 + -1, dst <= local_c) {
        pcVar1[3] = *local_c;
        pcVar1 = local_c;
      }
      strncpy(dst,&DAT_00454860,4);
      DAT_0045f864[4] = ')';
      DAT_0045f864 = DAT_0045f864 + 5;
    }
    else {
      piVar2[2] = piVar2[2] << 1;
    }
  }
  return (int)piVar2;
}


/* ==== FUN_00418cdb @ 00418cdb ==== */

int __cdecl FUN_00418cdb(undefined4 *param_1)

{
  int *piVar1;
  
  FUN_004167ef(param_1);
  piVar1 = FUN_00414a26();
  if (piVar1 == (int *)0x0) {
    FUN_004167ef((undefined4 *)0x0);
    piVar1 = (int *)0x0;
  }
  return (int)piVar1;
}


/* ==== FUN_00418d12 @ 00418d12 ==== */

int __cdecl FUN_00418d12(undefined4 *param_1)

{
  int *piVar1;
  
  FUN_004167ef(param_1);
  piVar1 = FUN_00414a26();
  if (piVar1 == (int *)0x0) {
    FUN_004167ef((undefined4 *)0x0);
    piVar1 = (int *)0x0;
  }
  else {
    piVar1[2] = (uint)piVar1[2] >> 1;
    if ((piVar1[1] & 1U) != 0) {
      piVar1[2] = piVar1[2] | 0x8000;
    }
    piVar1[1] = (uint)piVar1[1] >> 1;
  }
  return (int)piVar1;
}


/* ==== FUN_00418d81 @ 00418d81 ==== */

int __cdecl FUN_00418d81(undefined4 *param_1)

{
  int *piVar1;
  
  FUN_004167ef(param_1);
  piVar1 = FUN_00414a26();
  if (piVar1 == (int *)0x0) {
    FUN_004167ef((undefined4 *)0x0);
    piVar1 = (int *)0x0;
  }
  else {
    piVar1[2] = (uint)piVar1[2] >> 2;
    piVar1[2] = piVar1[2] | (piVar1[1] & 3U) << 0xe;
    piVar1[1] = (uint)piVar1[1] >> 2;
  }
  return (int)piVar1;
}


/* ==== FUN_00418deb @ 00418deb ==== */

int __cdecl FUN_00418deb(undefined4 *param_1)

{
  char *pcVar1;
  char *dst;
  int *piVar2;
  char *local_c;
  
  FUN_004167ef(param_1);
  dst = DAT_0045f864;
  piVar2 = FUN_00414a26();
  if (piVar2 == (int *)0x0) {
    FUN_004167ef((undefined4 *)0x0);
    piVar2 = (int *)0x0;
  }
  else {
    pcVar1 = DAT_0045f864;
    if (piVar2[0xf] < 0) {
      while (local_c = pcVar1 + -1, dst <= local_c) {
        pcVar1[3] = *local_c;
        pcVar1 = local_c;
      }
      strncpy(dst,&DAT_00454868,4);
      DAT_0045f864[4] = ')';
      DAT_0045f864 = DAT_0045f864 + 5;
    }
    else {
      piVar2[2] = piVar2[2] << 1;
      piVar2[2] = piVar2[2] + 1;
    }
  }
  return (int)piVar2;
}


/* ==== FUN_00418eba @ 00418eba ==== */

double * __cdecl FUN_00418eba(double *param_1,int param_2)

{
  float10 fVar1;
  undefined8 local_14;
  double local_c;
  
  FUN_004167ef((undefined4 *)param_1);
  param_1 = (double *)FUN_00414a26();
  if (param_1 == (double *)0x0) {
    FUN_004167ef((undefined4 *)0x0);
    param_1 = (double *)0x0;
  }
  else if (((ulonglong)param_1[3] & 0x1000) == 0) {
    if (*(int *)(param_1 + 2) == 0x100) {
      fVar1 = FUN_0040b1e5(param_1);
      local_14 = (double)fVar1;
    }
    else {
      local_14 = *param_1;
    }
    while (*DAT_0045f860 == ',') {
      DAT_0045f860 = DAT_0045f860 + 1;
      FUN_004167ef((undefined4 *)param_1);
      param_1 = (double *)FUN_00414a26();
      if (param_1 == (double *)0x0) {
        FUN_004167ef((undefined4 *)0x0);
        return (double *)0x0;
      }
      if (*(int *)(param_1 + 2) == 0x100) {
        fVar1 = FUN_0040b1e5(param_1);
        local_c = (double)fVar1;
      }
      else {
        local_c = *param_1;
      }
      if (param_2 == 0x21) {
        if (local_c < local_14) {
          local_14 = local_c;
        }
      }
      else if (local_14 < local_c) {
        local_14 = local_c;
      }
    }
    *(undefined4 *)param_1 = (undefined4)local_14;
    *(undefined4 *)((int)param_1 + 4) = local_14._4_4_;
    *(undefined4 *)(param_1 + 2) = 0x200;
    *(undefined4 *)((int)param_1 + 0x14) = 8;
    *(uint *)(param_1 + 3) = *(uint *)(param_1 + 3) & 0xffffefff;
    *(undefined4 *)(param_1 + 4) = 4;
    *(undefined4 *)((int)param_1 + 0x1c) = 4;
    *(undefined4 *)((int)param_1 + 0x24) = 0;
    *(undefined4 *)(param_1 + 5) = 0;
  }
  else {
    FUN_00413085((uint *)s_Relative_expression_not_allowed_00454870);
    FUN_004167ef((undefined4 *)param_1);
    param_1 = (double *)0x0;
  }
  return param_1;
}


/* ==== FUN_0041905d @ 0041905d ==== */

double * __cdecl FUN_0041905d(double *param_1)

{
  int local_14;
  
  if (DAT_0045ebbc == 0) {
    DAT_0045ebbc = GetCurrentProcessId();
  }
  local_14 = ((int)DAT_0045ebbc % 0x1f31d) * 0x41a7 + ((int)DAT_0045ebbc / 0x1f31d) * -0xb14;
  if (local_14 < 1) {
    local_14 = local_14 + 0x7fffffff;
  }
  DAT_0045ebbc = local_14;
  *param_1 = (double)local_14;
  *param_1 = *param_1 / 2147483647.0;
  *(undefined4 *)(param_1 + 2) = 0x200;
  *(uint *)(param_1 + 3) = *(uint *)(param_1 + 3) & 0xffffefff;
  *(undefined4 *)((int)param_1 + 0x14) = 8;
  *(undefined4 *)(param_1 + 4) = 4;
  *(undefined4 *)((int)param_1 + 0x1c) = 4;
  *(undefined4 *)((int)param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 5) = 0;
  return param_1;
}


/* ==== FUN_0041913c @ 0041913c ==== */

undefined4 * __cdecl FUN_0041913c(undefined4 *param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  
  FUN_004167ef(param_1);
  piVar3 = FUN_00414a26();
  if (piVar3 == (int *)0x0) {
    FUN_004167ef((undefined4 *)0x0);
    piVar3 = (int *)0x0;
  }
  else if (piVar3[4] == 0x200) {
    FUN_00413085((uint *)s_Expression_result_must_be_intege_00454890);
    FUN_004167ef(piVar3);
    piVar3 = (int *)0x0;
  }
  else if (piVar3[5] < 4) {
    iVar2 = piVar3[2];
    FUN_004167ef(piVar3);
    cVar1 = *DAT_0045f860;
    DAT_0045f860 = DAT_0045f860 + 1;
    if (cVar1 == ',') {
      piVar3 = FUN_00414a26();
      if (piVar3 == (int *)0x0) {
        FUN_004167ef((undefined4 *)0x0);
        piVar3 = (int *)0x0;
      }
      else if (piVar3[4] == 0x200) {
        FUN_00413085((uint *)s_Expression_result_must_be_intege_004548f0);
        FUN_004167ef(piVar3);
        piVar3 = (int *)0x0;
      }
      else if (piVar3[5] < 4) {
        piVar3[1] = iVar2;
        *piVar3 = 0;
        piVar3[5] = 6;
        piVar3[6] = piVar3[6] & 0xffffefff;
        piVar3[8] = 4;
        piVar3[7] = 4;
        piVar3[9] = 0;
        piVar3[10] = 0;
      }
      else {
        FUN_00413085((uint *)s_Expression_result_too_large_00454914);
        FUN_004167ef(piVar3);
        piVar3 = (int *)0x0;
      }
    }
    else {
      FUN_00413085((uint *)s_Syntax_error___expected_comma_004548d0);
      piVar3 = (int *)0x0;
    }
  }
  else {
    FUN_00413085((uint *)s_Expression_result_too_large_004548b4);
    FUN_004167ef(piVar3);
    piVar3 = (int *)0x0;
  }
  return piVar3;
}


/* ==== FUN_004192d1 @ 004192d1 ==== */

undefined4 * __cdecl FUN_004192d1(undefined4 *param_1)

{
  uint uVar1;
  int local_1c;
  uint local_18;
  uint local_14;
  int local_10;
  uint local_c;
  
  local_c = 0;
  FUN_004167ef(param_1);
  param_1 = FUN_00414a26();
  if (param_1 == (int *)0x0) {
    FUN_004167ef((undefined4 *)0x0);
    param_1 = (undefined4 *)0x0;
  }
  else if (param_1[4] == 0x200) {
    FUN_00413085((uint *)s_Expression_result_must_be_intege_00454930);
    FUN_004167ef(param_1);
    param_1 = (undefined4 *)0x0;
  }
  else if ((int)param_1[5] < 4) {
    uVar1 = param_1[2];
    if (*DAT_0045f860 == ',') {
      FUN_004167ef(param_1);
      DAT_0045f860 = DAT_0045f860 + 1;
      param_1 = FUN_00414a26();
      if (param_1 == (int *)0x0) {
        FUN_004167ef((undefined4 *)0x0);
        return (undefined4 *)0x0;
      }
      if (param_1[4] == 0x200) {
        FUN_00413085((uint *)s_Expression_result_must_be_intege_00454970);
        FUN_004167ef(param_1);
        return (undefined4 *)0x0;
      }
      if (0x18 < (uint)param_1[2]) {
        FUN_00413085((uint *)s_Expression_result_too_large_00454994);
        FUN_004167ef(param_1);
        return (undefined4 *)0x0;
      }
      local_1c = param_1[2];
    }
    else {
      local_1c = 0x18;
    }
    local_14 = 1;
    local_18 = 1 << ((char)local_1c - 1U & 0x1f);
    for (local_10 = 0; local_10 < local_1c; local_10 = local_10 + 1) {
      if ((uVar1 & local_14) != 0) {
        local_c = local_c | local_18;
      }
      local_14 = local_14 << 1;
      local_18 = local_18 >> 1;
    }
    param_1[2] = local_c;
    *param_1 = 0;
    param_1[1] = 0;
  }
  else {
    FUN_00413085((uint *)s_Expression_result_too_large_00454954);
    FUN_004167ef(param_1);
    param_1 = (undefined4 *)0x0;
  }
  return param_1;
}


/* ==== FUN_00419493 @ 00419493 ==== */

double * __cdecl FUN_00419493(undefined4 *param_1,undefined *param_2)

{
  double *pdVar1;
  float10 fVar2;
  undefined8 local_c;
  
  FUN_004167ef(param_1);
  pdVar1 = (double *)FUN_00414a26();
  if (pdVar1 == (double *)0x0) {
    FUN_004167ef((undefined4 *)0x0);
    pdVar1 = (double *)0x0;
  }
  else if (((ulonglong)pdVar1[3] & 0x1000) == 0) {
    if (*(int *)(pdVar1 + 2) == 0x100) {
      fVar2 = FUN_0040b1e5(pdVar1);
      local_c = (double)fVar2;
    }
    else {
      local_c = *pdVar1;
    }
    errno = 0;
    fVar2 = (float10)(*(code *)param_2)((undefined4)local_c,local_c._4_4_);
    *pdVar1 = (double)fVar2;
    if (errno == 0) {
      *(undefined4 *)(pdVar1 + 2) = 0x200;
      *(undefined4 *)(pdVar1 + 4) = 4;
      *(undefined4 *)((int)pdVar1 + 0x1c) = 4;
      *(undefined4 *)((int)pdVar1 + 0x24) = 0;
      *(undefined4 *)(pdVar1 + 5) = 0;
      *(uint *)(pdVar1 + 3) = *(uint *)(pdVar1 + 3) & 0xffffefff;
      *(undefined4 *)((int)pdVar1 + 0x14) = 8;
    }
    else {
      if (errno == 0x21) {
        FUN_00413085((uint *)s_Argument_outside_function_domain_004549d0);
      }
      else if (errno == 0x22) {
        FUN_00413085((uint *)s_Function_result_out_of_range_004549f4);
      }
      else {
        FUN_00413085((uint *)s_Unknown_math_error_00454a14);
      }
      FUN_004167ef((undefined4 *)pdVar1);
      pdVar1 = (double *)0x0;
    }
  }
  else {
    FUN_00413085((uint *)s_Relative_expression_not_allowed_004549b0);
    FUN_004167ef((undefined4 *)pdVar1);
    pdVar1 = (double *)0x0;
  }
  return pdVar1;
}


/* ==== FUN_004195e5 @ 004195e5 ==== */

double * __cdecl FUN_004195e5(undefined4 *param_1,undefined *param_2)

{
  char cVar1;
  double *pdVar2;
  float10 fVar3;
  undefined8 local_14;
  undefined8 local_c;
  
  FUN_004167ef(param_1);
  pdVar2 = (double *)FUN_00414a26();
  if (pdVar2 == (double *)0x0) {
    FUN_004167ef((undefined4 *)0x0);
    pdVar2 = (double *)0x0;
  }
  else if (((ulonglong)pdVar2[3] & 0x1000) == 0) {
    if (*(int *)(pdVar2 + 2) == 0x100) {
      fVar3 = FUN_0040b1e5(pdVar2);
      local_c = (double)fVar3;
    }
    else {
      local_c = *pdVar2;
    }
    FUN_004167ef((undefined4 *)pdVar2);
    cVar1 = *DAT_0045f860;
    DAT_0045f860 = DAT_0045f860 + 1;
    if (cVar1 == ',') {
      pdVar2 = (double *)FUN_00414a26();
      if (pdVar2 == (double *)0x0) {
        FUN_004167ef((undefined4 *)0x0);
        pdVar2 = (double *)0x0;
      }
      else {
        if (*(int *)(pdVar2 + 2) == 0x100) {
          fVar3 = FUN_0040b1e5(pdVar2);
          local_14 = (double)fVar3;
        }
        else {
          local_14 = *pdVar2;
        }
        errno = 0;
        fVar3 = (float10)(*(code *)param_2)((undefined4)local_c,local_c._4_4_,(undefined4)local_14,
                                            local_14._4_4_);
        *pdVar2 = (double)fVar3;
        if (errno == 0) {
          *(undefined4 *)(pdVar2 + 2) = 0x200;
          *(undefined4 *)(pdVar2 + 4) = 4;
          *(undefined4 *)((int)pdVar2 + 0x1c) = 4;
          *(undefined4 *)((int)pdVar2 + 0x24) = 0;
          *(undefined4 *)(pdVar2 + 5) = 0;
          *(uint *)(pdVar2 + 3) = *(uint *)(pdVar2 + 3) & 0xffffefff;
          *(undefined4 *)((int)pdVar2 + 0x14) = 8;
        }
        else {
          if (errno == 0x21) {
            FUN_00413085((uint *)s_Argument_outside_function_domain_00454a68);
          }
          else if (errno == 0x22) {
            FUN_00413085((uint *)s_Function_result_out_of_range_00454a8c);
          }
          else {
            FUN_00413085((uint *)s_Unknown_math_error_00454aac);
          }
          FUN_004167ef((undefined4 *)pdVar2);
          pdVar2 = (double *)0x0;
        }
      }
    }
    else {
      FUN_00413085((uint *)s_Syntax_error___expected_comma_00454a48);
      pdVar2 = (double *)0x0;
    }
  }
  else {
    FUN_00413085((uint *)s_Relative_expression_not_allowed_00454a28);
    FUN_004167ef((undefined4 *)pdVar2);
    pdVar2 = (double *)0x0;
  }
  return pdVar2;
}


