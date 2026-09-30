/* eval: 27 functions from ASM56000 */

/* ==== FUN_004136cd @ 004136cd ==== */

void __cdecl FUN_004136cd(uint *param_1)

{
  uint uVar1;
  
  if ((DAT_0045ea50 == '\0') && (DAT_0045f8fc == 2)) {
    sprintf(&DAT_0045f220,s_______ld___s__ld___00453f14,DAT_0045eb80,PTR_DAT_0044f80c,DAT_0045eb78);
    uVar1 = strlen(&DAT_0045f220);
    strcpy(&DAT_0045f220 + uVar1,(char *)param_1);
    if ((DAT_0045fcac != &DAT_0045a470) || (DAT_0045ea9c != '\0')) {
      fprintf(&DAT_0045a470,&DAT_00453f28,&DAT_0045f220);
    }
    if (DAT_0045eb04 != '\0') {
      FUN_00413999(uVar1,(uint *)&DAT_0045f220);
    }
    FUN_0041c9cf(&DAT_0045f220);
    FUN_0041cb65();
  }
  return;
}


/* ==== FUN_0041379a @ 0041379a ==== */

void FUN_0041379a(void)

{
  undefined4 in_stack_00000004;
  
  fprintf(&DAT_0045a470,s__s___s_00453f2c,PTR_s_asm56000_0044e084,in_stack_00000004);
  exit(-1);
  return;
}


/* ==== FUN_004137c6 @ 004137c6 ==== */

void FUN_004137c6(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  fprintf(&DAT_0045a470,s__s___s___s_00453f34,PTR_s_asm56000_0044e084,in_stack_00000004,
          in_stack_00000008);
  exit(-1);
  return;
}


/* ==== FUN_004137f6 @ 004137f6 ==== */

void FUN_004137f6(void)

{
  undefined4 in_stack_00000004;
  
  fprintf(&DAT_0045a470,s__s___s_00453f40,PTR_s_asm56000_0044e084,in_stack_00000004);
  return;
}


/* ==== FUN_00413818 @ 00413818 ==== */

undefined4 __cdecl FUN_00413818(undefined1 *param_1)

{
  uint uVar1;
  
  if (((param_1 != (undefined1 *)0x0) && (&DAT_0045ee10 <= param_1)) && (param_1 < &DAT_0045f010)) {
    if (((PTR_DAT_0044f810 != (undefined *)0x0) && (*PTR_DAT_0044f810 != '\0')) &&
       ((PTR_DAT_0044f810 <= param_1 &&
        (uVar1 = strlen(PTR_DAT_0044f810), param_1 <= PTR_DAT_0044f810 + uVar1)))) {
      return 1;
    }
    if (((PTR_DAT_0044f814 != (undefined *)0x0) && (*PTR_DAT_0044f814 != '\0')) &&
       ((PTR_DAT_0044f814 <= param_1 &&
        (uVar1 = strlen(PTR_DAT_0044f814), param_1 <= PTR_DAT_0044f814 + uVar1)))) {
      return 2;
    }
    if ((((PTR_DAT_0044f818 != (undefined *)0x0) && (*PTR_DAT_0044f818 != '\0')) &&
        (PTR_DAT_0044f818 <= param_1)) &&
       (uVar1 = strlen(PTR_DAT_0044f818), param_1 <= PTR_DAT_0044f818 + uVar1)) {
      return 3;
    }
    if (((PTR_DAT_0044f81c != (undefined *)0x0) && (*PTR_DAT_0044f81c != '\0')) &&
       ((PTR_DAT_0044f81c <= param_1 &&
        (uVar1 = strlen(PTR_DAT_0044f81c), param_1 <= PTR_DAT_0044f81c + uVar1)))) {
      return 4;
    }
    if (((PTR_DAT_0044f820 != (undefined *)0x0) && (*PTR_DAT_0044f820 != '\0')) &&
       ((PTR_DAT_0044f820 <= param_1 &&
        (uVar1 = strlen(PTR_DAT_0044f820), param_1 <= PTR_DAT_0044f820 + uVar1)))) {
      return 5;
    }
  }
  return 0;
}


/* ==== FUN_00413999 @ 00413999 ==== */

void __cdecl FUN_00413999(int param_1,uint *param_2)

{
  bool bVar1;
  int iVar2;
  uint local_230;
  uint local_22c;
  uint local_228;
  char *local_224;
  int local_220;
  char *local_214;
  uint *local_210;
  char local_20c [512];
  char *local_c;
  uint *local_8;
  
  bVar1 = true;
  iVar2 = DAT_0044f7dc - DAT_0044f7e0;
  local_210 = (uint *)0x0;
  local_214 = (char *)0x0;
  local_224 = local_20c;
  local_c = local_20c;
  for (local_8 = param_2; local_8 < (uint *)((int)param_2 + param_1);
      local_8 = (uint *)((int)local_8 + 1)) {
    *local_c = (char)*local_8;
    local_c = local_c + 1;
  }
  for (; (char)*local_8 != '\0'; local_8 = (uint *)((int)local_8 + 1)) {
    if (__mb_cur_max < 2) {
      local_228 = *(ushort *)(_pctype + (char)*local_8 * 2) & 8;
    }
    else {
      local_228 = _isctype((int)(char)*local_8,8);
    }
    if (local_228 == 0) break;
  }
  do {
    if ((char)*local_8 == '\0') {
LAB_00413c2c:
      *local_c = '\0';
      strcpy((char *)param_2,local_20c);
      return;
    }
    for (; (char)*local_8 != '\0'; local_8 = (uint *)((int)local_8 + 1)) {
      if (__mb_cur_max < 2) {
        local_22c = *(ushort *)(_pctype + (char)*local_8 * 2) & 8;
      }
      else {
        local_22c = _isctype((int)(char)*local_8,8);
      }
      if (local_22c != 0) break;
      *local_c = (char)*local_8;
      local_c = local_c + 1;
    }
    if ((int)local_c - (int)local_224 < iVar2 + 1) {
      if ((char)*local_8 == '\0') goto LAB_00413c2c;
      if (bVar1) {
        bVar1 = false;
      }
      else {
        local_210 = local_8;
        local_214 = local_c;
      }
      *local_c = (char)*local_8;
      local_c = local_c + 1;
      local_8 = (uint *)((int)local_8 + 1);
    }
    else {
      if (!bVar1) {
        local_8 = local_210;
        local_c = local_214;
      }
      *local_c = '\n';
      local_224 = local_c + 1;
      local_c = local_224;
      for (local_220 = 0; local_220 < param_1; local_220 = local_220 + 1) {
        *local_c = ' ';
        local_c = local_c + 1;
      }
      for (; (char)*local_8 != '\0'; local_8 = (uint *)((int)local_8 + 1)) {
        if (__mb_cur_max < 2) {
          local_230 = *(ushort *)(_pctype + (char)*local_8 * 2) & 8;
        }
        else {
          local_230 = _isctype((int)(char)*local_8,8);
        }
        if (local_230 == 0) break;
      }
      bVar1 = true;
    }
  } while( true );
}


/* ==== FUN_00413c50 @ 00413c50 ==== */

int * __cdecl FUN_00413c50(uint param_1)

{
  int *piVar1;
  uint uVar2;
  
  piVar1 = FUN_00414862();
  if (piVar1 != (int *)0x0) {
    if (piVar1[4] == 0x100) {
      uVar2 = FUN_0040a7ea((int)piVar1);
      if (DAT_0045ea98 == '\0') {
        if (param_1 < uVar2) {
          FUN_004167ef(piVar1);
          FUN_00413085((uint *)s_Expression_result_too_large_00453fa4);
          return (int *)0x0;
        }
      }
      else {
        piVar1[2] = piVar1[2] & param_1;
      }
      piVar1[1] = 0;
      *piVar1 = 0;
    }
    else {
      FUN_004167ef(piVar1);
      FUN_00413085((uint *)s_Expression_result_must_be_intege_00453f80);
      piVar1 = (int *)0x0;
    }
  }
  return piVar1;
}


/* ==== FUN_00413cfb @ 00413cfb ==== */

int * FUN_00413cfb(void)

{
  bool bVar1;
  int *piVar2;
  uint uVar3;
  uint local_18;
  
  piVar2 = FUN_00414862();
  if (piVar2 != (int *)0x0) {
    if (piVar2[4] == 0x100) {
      if ((piVar2[6] & 0x1000U) == 0) {
        if (piVar2[0xf] < 0) {
          FUN_004167ef(piVar2);
          FUN_00413085((uint *)s_External_reference_not_allowed_i_00454008);
          piVar2 = (int *)0x0;
        }
        else {
          uVar3 = FUN_0040a7ea((int)piVar2);
          local_18 = uVar3;
          if ((int)uVar3 < 0) {
            local_18 = -uVar3;
          }
          if (DAT_0044f7bc == '\0') {
            if (((int)uVar3 < -0x10000) || (DAT_0044f91c < local_18)) {
              bVar1 = true;
            }
            else {
              bVar1 = false;
            }
          }
          else if (((int)uVar3 < -0x8000) || (DAT_0044f91c < local_18)) {
            bVar1 = true;
          }
          else {
            bVar1 = false;
          }
          if (bVar1) {
            FUN_004167ef(piVar2);
            FUN_00413085((uint *)s_Expression_result_too_large_00454038);
            piVar2 = (int *)0x0;
          }
          else {
            piVar2[1] = 0;
            *piVar2 = 0;
            piVar2[2] = uVar3;
          }
        }
      }
      else {
        FUN_004167ef(piVar2);
        FUN_00413085((uint *)s_Expression_result_must_be_absolu_00453fe4);
        piVar2 = (int *)0x0;
      }
    }
    else {
      FUN_004167ef(piVar2);
      FUN_00413085((uint *)s_Expression_result_must_be_intege_00453fc0);
      piVar2 = (int *)0x0;
    }
  }
  return piVar2;
}


/* ==== FUN_00413e70 @ 00413e70 ==== */

int * FUN_00413e70(void)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = FUN_00414862();
  if (piVar1 != (int *)0x0) {
    if (piVar1[4] == 0x100) {
      if ((piVar1[6] & 0x1000U) == 0) {
        if (piVar1[0xf] < 0) {
          FUN_004167ef(piVar1);
          FUN_00413085((uint *)s_External_reference_not_allowed_i_0045409c);
          piVar1 = (int *)0x0;
        }
        else {
          iVar2 = FUN_0040a7ea((int)piVar1);
          piVar1[1] = 0;
          *piVar1 = 0;
          piVar1[2] = iVar2;
        }
      }
      else {
        FUN_004167ef(piVar1);
        FUN_00413085((uint *)s_Expression_result_must_be_absolu_00454078);
        piVar1 = (int *)0x0;
      }
    }
    else {
      FUN_004167ef(piVar1);
      FUN_00413085((uint *)s_Expression_result_must_be_intege_00454054);
      piVar1 = (int *)0x0;
    }
  }
  return piVar1;
}


/* ==== FUN_00413f38 @ 00413f38 ==== */

int * FUN_00413f38(void)

{
  bool bVar1;
  int *piVar2;
  uint uVar3;
  uint local_18;
  
  piVar2 = FUN_00414862();
  if (piVar2 != (int *)0x0) {
    if (piVar2[4] == 0x100) {
      if ((piVar2[6] & 0x1000U) == 0) {
        if (piVar2[0xf] < 0) {
          FUN_004167ef(piVar2);
          FUN_00413085((uint *)s_External_reference_not_allowed_i_00454114);
          piVar2 = (int *)0x0;
        }
        else {
          uVar3 = FUN_0040a7ea((int)piVar2);
          local_18 = uVar3;
          if ((int)uVar3 < 0) {
            local_18 = -uVar3;
          }
          if (DAT_0044f7bc == '\0') {
            if (((int)uVar3 < -0x100) || (0xff < local_18)) {
              bVar1 = true;
            }
            else {
              bVar1 = false;
            }
          }
          else if (((int)uVar3 < -0x80) || (0xff < local_18)) {
            bVar1 = true;
          }
          else {
            bVar1 = false;
          }
          if (bVar1) {
            FUN_004167ef(piVar2);
            FUN_00413085((uint *)s_Expression_result_too_large_00454144);
            piVar2 = (int *)0x0;
          }
          else {
            *piVar2 = 0;
            piVar2[1] = 0;
            piVar2[2] = uVar3;
          }
        }
      }
      else {
        FUN_004167ef(piVar2);
        FUN_00413085((uint *)s_Expression_result_must_be_absolu_004540f0);
        piVar2 = (int *)0x0;
      }
    }
    else {
      FUN_004167ef(piVar2);
      FUN_00413085((uint *)s_Expression_result_must_be_intege_004540cc);
      piVar2 = (int *)0x0;
    }
  }
  return piVar2;
}


/* ==== FUN_0041409f @ 0041409f ==== */

int * FUN_0041409f(void)

{
  bool bVar1;
  int *piVar2;
  uint uVar3;
  uint local_18;
  
  piVar2 = FUN_00414862();
  if (piVar2 != (int *)0x0) {
    if (piVar2[4] == 0x100) {
      uVar3 = FUN_0040a7ea((int)piVar2);
      local_18 = uVar3;
      if ((int)uVar3 < 0) {
        local_18 = -uVar3;
      }
      if (DAT_0044f7bc == '\0') {
        if (((int)uVar3 < -0x10000) || (0xffff < local_18)) {
          bVar1 = true;
        }
        else {
          bVar1 = false;
        }
      }
      else if (((int)uVar3 < -0x8000) || (0xffff < local_18)) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      if (bVar1) {
        FUN_004167ef(piVar2);
        FUN_00413085((uint *)s_Expression_result_too_large_00454184);
        piVar2 = (int *)0x0;
      }
      else {
        *piVar2 = 0;
        piVar2[1] = 0;
        piVar2[2] = uVar3;
      }
    }
    else {
      FUN_004167ef(piVar2);
      FUN_00413085((uint *)s_Expression_result_must_be_intege_00454160);
      piVar2 = (int *)0x0;
    }
  }
  return piVar2;
}


/* ==== FUN_004141b1 @ 004141b1 ==== */

int * FUN_004141b1(void)

{
  bool bVar1;
  int *piVar2;
  uint uVar3;
  uint local_18;
  
  piVar2 = FUN_00414862();
  if ((piVar2 != (int *)0x0) && (piVar2[4] == 0x100)) {
    uVar3 = FUN_0040a7ea((int)piVar2);
    local_18 = uVar3;
    if ((int)uVar3 < 0) {
      local_18 = -uVar3;
    }
    if (DAT_0044f7bc == '\0') {
      if (((int)uVar3 < -0x1000000) || (0xffffff < local_18)) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
    }
    else if (((int)uVar3 < -0x800000) || (0xffffff < local_18)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      FUN_004167ef(piVar2);
      FUN_00413085((uint *)s_Expression_result_too_large_004541a0);
      piVar2 = (int *)0x0;
    }
    else {
      piVar2[1] = 0;
      *piVar2 = 0;
      piVar2[2] = uVar3;
    }
  }
  return piVar2;
}


/* ==== FUN_004142a7 @ 004142a7 ==== */

undefined4 * __cdecl FUN_004142a7(undefined4 *param_1,uint param_2)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined3 extraout_var;
  int iVar3;
  undefined3 extraout_var_00;
  undefined4 uVar4;
  int local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  int *local_28;
  int *local_20;
  int local_1c;
  int local_18;
  undefined1 local_14;
  int local_10;
  uint local_c;
  char *local_8;
  
  local_1c = 0;
  if (param_1 == (undefined4 *)0x0) {
    DAT_0045f860 = FUN_0043b08d(DAT_0045f860,&DAT_0045f220);
    if (DAT_0045f860 == (char *)0x0) {
      return (undefined4 *)0x0;
    }
    local_c = strlen(&DAT_0045f220);
  }
  else {
    memcpy(&DAT_0045f220,param_1,param_2);
    local_c = param_2;
  }
  puVar2 = FUN_00416653();
  if (DAT_0044f79c == '\0') {
    if (local_c == 0) {
      local_34 = 1;
    }
    else {
      local_34 = local_c;
    }
    local_30 = local_34;
  }
  else {
    if (local_c == 0) {
      local_2c = 1;
    }
    else {
      local_2c = (int)(local_c - 1) / 3 + 1;
    }
    local_30 = local_2c;
  }
  local_28 = (int *)FUN_00439857(local_30 << 2);
  *puVar2 = local_28;
  puVar2[4] = 0x100;
  puVar2[8] = 4;
  puVar2[7] = 4;
  puVar2[9] = 0;
  puVar2[10] = 0;
  puVar2[5] = 3;
  puVar2[6] = 0;
  puVar2[0xd] = local_c;
  puVar2[0xe] = local_30;
  puVar2[0x10] = 0;
  puVar2[0xf] = 0;
  puVar2[0x12] = 0;
  puVar2[0x11] = 0;
  puVar2[0x13] = 0;
  puVar2[0x14] = 0;
  puVar2[0x15] = 0xffffffff;
  puVar2[0x16] = 0;
  if ((int)local_c < 2) {
    if (local_c == 0) {
      local_38 = 0;
    }
    else {
      local_38 = (int)DAT_0045f220;
    }
    *local_28 = local_38;
  }
  else if (DAT_0044f79c == '\0') {
    local_20 = local_28;
    if (DAT_0045eb14 == '\0') {
      local_8 = &DAT_0045f220;
      for (local_18 = 0; local_18 < (int)local_c; local_18 = local_18 + 1) {
        *local_20 = (int)*local_8;
        local_20 = local_20 + 1;
        local_8 = local_8 + 1;
      }
    }
    else {
      local_8 = &DAT_0045f220;
      for (local_18 = 0; local_18 < (int)local_c; local_18 = local_18 + 1) {
        bVar1 = FUN_00414686(local_8);
        if (CONCAT31(extraout_var,bVar1) == 0) {
          *local_20 = (int)*local_8;
          local_8 = local_8 + 1;
        }
        else {
          local_18 = local_18 + 1;
          iVar3 = FUN_0041469f(local_8 + 1);
          *local_20 = iVar3;
          local_8 = local_8 + 2;
          puVar2[0xd] = puVar2[0xd] + -1;
          puVar2[0xe] = puVar2[0xe] + -1;
        }
        local_20 = local_20 + 1;
      }
    }
  }
  else {
    *local_28 = 0;
    local_8 = &DAT_0045f220;
    local_10 = 2;
    for (local_18 = 0; local_18 < (int)local_c; local_18 = local_18 + 1) {
      if (local_10 < 0) {
        local_28 = local_28 + 1;
        *local_28 = 0;
        local_10 = 2;
      }
      bVar1 = FUN_00414686(local_8);
      if ((CONCAT31(extraout_var_00,bVar1) == 0) || (DAT_0045eb14 == '\0')) {
        *(char *)((int)local_28 + local_10) = *local_8;
      }
      else {
        local_1c = local_1c + 1;
        local_8 = local_8 + 1;
        local_18 = local_18 + 1;
        uVar4 = FUN_0041469f(local_8);
        local_14 = (undefined1)uVar4;
        *(undefined1 *)((int)local_28 + local_10) = local_14;
        local_10 = local_10 + 1;
        puVar2[0xd] = puVar2[0xd] + -1;
        if (local_1c == 3) {
          puVar2[0xe] = puVar2[0xe] + -1;
          local_1c = 0;
        }
      }
      local_8 = local_8 + 1;
      local_10 = local_10 + -1;
    }
  }
  return puVar2;
}


/* ==== FUN_00414686 @ 00414686 ==== */

bool __cdecl FUN_00414686(char *param_1)

{
  return *param_1 == '\\';
}


/* ==== FUN_0041469f @ 0041469f ==== */

undefined4 __cdecl FUN_0041469f(undefined1 *param_1)

{
  undefined4 uVar1;
  
  switch(*param_1) {
  case 0x22:
    uVar1 = 0x22;
    break;
  default:
    FUN_00413085((uint *)s_Illegal_escape_char_specified_004541bc);
    uVar1 = 10;
    break;
  case 0x5c:
    uVar1 = 0x5c;
    break;
  case 0x61:
    uVar1 = 7;
    break;
  case 0x65:
    uVar1 = 0x1b;
    break;
  case 0x66:
    uVar1 = 0xc;
    break;
  case 0x6e:
    uVar1 = 10;
    break;
  case 0x72:
    uVar1 = 0xd;
    break;
  case 0x74:
    uVar1 = 9;
    break;
  case 0x76:
    uVar1 = 0xb;
  }
  return uVar1;
}


/* ==== FUN_0041479f @ 0041479f ==== */

int FUN_0041479f(void)

{
  int *piVar1;
  int local_8;
  
  piVar1 = FUN_00413cfb();
  if (piVar1 == (int *)0x0) {
    local_8 = -1;
  }
  else {
    local_8 = piVar1[2];
    if (local_8 < 0) {
      FUN_00413085((uint *)s_Expression_cannot_have_a_negativ_004541dc);
      local_8 = -1;
    }
    FUN_004167ef(piVar1);
  }
  return local_8;
}


/* ==== FUN_004147ee @ 004147ee ==== */

int FUN_004147ee(void)

{
  int *piVar1;
  int local_8;
  
  piVar1 = FUN_00413cfb();
  if (piVar1 == (int *)0x0) {
    local_8 = -1;
  }
  else {
    local_8 = piVar1[2];
    if (local_8 < 0) {
      FUN_00413085((uint *)s_Expression_cannot_have_a_negativ_00454204);
      local_8 = -1;
    }
    else if ((piVar1[6] & 0x8000000U) != 0) {
      FUN_00413085((uint *)s_Expression_contains_forward_refe_0045422c);
      local_8 = -1;
    }
    FUN_004167ef(piVar1);
  }
  return local_8;
}


/* ==== FUN_00414862 @ 00414862 ==== */

int * FUN_00414862(void)

{
  int iVar1;
  int *piVar2;
  
  if (*DAT_0045f860 == '\0') {
    FUN_00413085((uint *)s_Missing_expression_00454254);
    FUN_00413085((uint *)s_Possible_invalid_white_space_bet_00454268);
    return (int *)0x0;
  }
  iVar1 = _setjmp3(&DAT_00465b80,0);
  if (iVar1 != 0) {
    DAT_0045eb60 = 0;
    DAT_0045fca0 = 0;
    DAT_0045eb10 = 0;
    FUN_00416860();
    return (int *)0x0;
  }
  DAT_0045fca0 = 1;
  DAT_0045f428 = 0x7b;
  DAT_0045f864 = &DAT_0045f429;
  piVar2 = FUN_00414a26();
  if (piVar2 == (int *)0x0) {
    DAT_0045f428 = 0;
    DAT_0045f864 = (undefined1 *)0x0;
    DAT_0045fca0 = 0;
    return (int *)0x0;
  }
  *DAT_0045f864 = 0x7d;
  DAT_0045f864 = DAT_0045f864 + 1;
  if ((((*DAT_0045f860 != '\0') && (*DAT_0045f860 != ',')) && (*DAT_0045f860 != ')')) &&
     (*DAT_0045f860 != ']')) {
    FUN_00413085((uint *)s_Extra_characters_beyond_expressi_004542a4);
    FUN_004167ef(piVar2);
    DAT_0045f428 = 0;
    DAT_0045f864 = (undefined1 *)0x0;
    DAT_0045fca0 = 0;
    return (int *)0x0;
  }
  if ((piVar2[0xf] < 0) || (((piVar2[6] & 0x8000000U) != 0 && (DAT_0045f8fc == 1)))) {
    if (piVar2[4] == 0x100) {
      piVar2[2] = 0;
      piVar2[1] = 0;
      *piVar2 = 0;
    }
    else if (piVar2[4] != 0x200) goto LAB_00414a0f;
    *piVar2 = 0;
    piVar2[1] = 0;
  }
LAB_00414a0f:
  DAT_0045fca0 = 0;
  *DAT_0045f864 = 0;
  return piVar2;
}


/* ==== FUN_00414a26 @ 00414a26 ==== */

int * FUN_00414a26(void)

{
  uint *puVar1;
  double *pdVar2;
  int *piVar3;
  
  puVar1 = DAT_0045f864;
  pdVar2 = FUN_0041518e();
  if (pdVar2 == (double *)0x0) {
    piVar3 = (int *)0x0;
  }
  else {
    piVar3 = FUN_00414aa1((int *)pdVar2,99,puVar1);
    if (((piVar3 != (int *)0x0) && ((piVar3[6] & 0x1000U) != 0)) && (piVar3[4] != 0x100)) {
      FUN_00413085((uint *)s_Relative_expression_must_be_inte_004542c8);
      FUN_004167ef(piVar3);
      piVar3 = (int *)0x0;
    }
  }
  return piVar3;
}


/* ==== FUN_00414aa1 @ 00414aa1 ==== */

int * __cdecl FUN_00414aa1(int *param_1,int param_2,uint *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  double *local_10;
  
  while( true ) {
    iVar1 = FUN_00414e2e();
    if (iVar1 == 0) {
      return param_1;
    }
    iVar2 = FUN_0041501f(iVar1);
    if (param_2 <= iVar2) {
      return param_1;
    }
    *(undefined1 *)DAT_0045f864 = *DAT_0045f860;
    DAT_0045f864 = (uint *)((int)DAT_0045f864 + 1);
    DAT_0045f860 = DAT_0045f860 + 1;
    if ((((((iVar1 == 10) || (iVar1 == 9)) || (iVar1 == 0xd)) || ((iVar1 == 0xe || (iVar1 == 0xf))))
        || (iVar1 == 0x10)) || ((iVar1 == 0x11 || (iVar1 == 0x12)))) {
      *(undefined1 *)DAT_0045f864 = *DAT_0045f860;
      DAT_0045f864 = (uint *)((int)DAT_0045f864 + 1);
      DAT_0045f860 = DAT_0045f860 + 1;
    }
    if (((param_1[6] & 0x1000U) != 0) || (param_1[0xf] < 0)) {
      param_3 = DAT_0045f864;
    }
    local_10 = FUN_0041518e();
    if (local_10 == (double *)0x0) {
      FUN_004167ef(param_1);
      return (int *)0x0;
    }
    iVar3 = FUN_00414e2e();
    if (((iVar3 != 0) && (iVar3 = FUN_0041501f(iVar3), iVar3 < iVar2)) &&
       (local_10 = (double *)FUN_00414aa1((int *)local_10,iVar2,param_3), local_10 == (double *)0x0)
       ) {
      FUN_004167ef(param_1);
      return (int *)0x0;
    }
    if ((((DAT_0044f7b4 != '\0') && (DAT_0045ea98 == '\0')) &&
        ((iVar1 != 1 && ((iVar1 != 2 && (DAT_0045eb5c == '\0')))))) &&
       ((param_1[7] != 4 || (*(int *)((int)local_10 + 0x1c) != 4)))) break;
    DAT_0045eb60 = '\0';
    if ((-1 < *(int *)((int)local_10 + 0x3c)) &&
       (((((ulonglong)local_10[3] & 0x8000000) == 0 || (DAT_0045f8fc != 1)) &&
        (iVar1 = (*(code *)(&PTR_FUN_0044fff8)[iVar1])(param_1,local_10), iVar1 == 0)))) {
      DAT_0045eb60 = 0;
      return (int *)0x0;
    }
    if (DAT_0045eb60 == '\0') {
      if (((param_1[6] & 0x1000U) == 0) && (((ulonglong)local_10[3] & 0x1000) != 0)) {
        param_1[6] = param_1[6] | 0x1000;
        param_1[0xf] = *(int *)((int)local_10 + 0x3c);
        param_1[0x10] = *(int *)(local_10 + 8);
        param_1[0x11] = *(int *)((int)local_10 + 0x44);
        param_1[0x12] = *(int *)(local_10 + 9);
        param_1[0x13] = *(int *)((int)local_10 + 0x4c);
        param_1[0x14] = *(int *)(local_10 + 10);
        param_1[0x15] = *(int *)((int)local_10 + 0x54);
      }
      iVar1 = FUN_0043baf1(param_1[7],*(int *)((int)local_10 + 0x1c));
      param_1[7] = iVar1;
      if (param_1[7] == 0xa2c2a) {
        param_1[8] = 4;
        param_1[7] = 4;
      }
    }
    else {
      DAT_0045eb60 = '\0';
      param_1[6] = param_1[6] & 0xffffefff;
      param_1[8] = 4;
      param_1[7] = 4;
      param_1[9] = 0;
      param_1[10] = 0;
    }
    if (((ulonglong)local_10[3] & 0x8000000) != 0) {
      param_1[6] = param_1[6] | 0x8000000;
    }
    if (*(int *)((int)local_10 + 0x3c) < 0) {
      param_1[0xf] = *(int *)((int)local_10 + 0x3c);
    }
    FUN_004167ef((undefined4 *)local_10);
    if ((DAT_0044f790 != '\0') && (DAT_0045f8fc == 2)) {
      param_3 = FUN_004150bf(param_1,param_3);
    }
  }
  FUN_004167ef(param_1);
  FUN_004167ef((undefined4 *)local_10);
  FUN_00413085((uint *)s_Operation_not_allowed_with_addre_004542ec);
  return (int *)0x0;
}


/* ==== FUN_00414e2e @ 00414e2e ==== */

undefined4 FUN_00414e2e(void)

{
  char cVar1;
  undefined4 local_8;
  
  local_8 = 0;
  if (*DAT_0045f860 == '\0') {
    local_8 = 0;
  }
  else {
    cVar1 = DAT_0045f860[1];
    switch(*DAT_0045f860) {
    case '!':
      if (cVar1 == '=') {
        local_8 = 0x10;
      }
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


/* ==== FUN_0041501f @ 0041501f ==== */

undefined4 __cdecl FUN_0041501f(undefined4 param_1)

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


/* ==== FUN_004150bf @ 004150bf ==== */

uint * __cdecl FUN_004150bf(int *param_1,uint *param_2)

{
  uint uVar1;
  uint *puVar2;
  
  puVar2 = DAT_0045f864;
  if (((param_1[6] & 0x1000U) == 0) && (-1 < param_1[0xf])) {
    if (param_1[4] == 0x200) {
      FUN_0043c0ea(param_2,(uint *)s____15E_00454314,*param_1,param_1[1]);
    }
    else if (param_1[5] == 3) {
      sprintf((char *)param_2,s__s_lX_0045431c,PTR_DAT_0044f828,param_1[2] & 0xffffff);
    }
    else {
      sprintf((char *)param_2,s__s_lX_0_lX_00454324,PTR_DAT_0044f828,param_1[1] & 0xffffff,6,
              param_1[2] & 0xffffff);
    }
    uVar1 = strlen((char *)param_2);
    DAT_0045f864 = (uint *)((int)param_2 + uVar1);
    puVar2 = param_2;
  }
  return puVar2;
}


/* ==== FUN_0041518e @ 0041518e ==== */

double * FUN_0041518e(void)

{
  char cVar1;
  double *pdVar2;
  undefined3 extraout_var;
  uint uVar3;
  double dVar4;
  uint local_60;
  uint local_5c;
  int local_58;
  int local_54;
  uint local_50;
  uint local_4c;
  int local_48;
  uint local_44;
  int local_40;
  uint local_3c;
  uint local_38;
  char *local_34;
  uint local_30;
  uint local_2c;
  char *local_28;
  uint local_24;
  int local_20;
  char *local_1c;
  undefined4 *local_18;
  uint local_14;
  uint *local_10;
  uint local_c;
  double *local_8;
  
  if (*DAT_0045f860 == '+') {
    *DAT_0045f864 = *DAT_0045f860;
    DAT_0045f864 = DAT_0045f864 + 1;
    DAT_0045f860 = DAT_0045f860 + 1;
    pdVar2 = FUN_0041518e();
    if (pdVar2 != (double *)0x0) {
      return pdVar2;
    }
    return (double *)0x0;
  }
  if (*DAT_0045f860 == '-') {
    *DAT_0045f864 = *DAT_0045f860;
    DAT_0045f864 = DAT_0045f864 + 1;
    DAT_0045f860 = DAT_0045f860 + 1;
    local_8 = FUN_0041518e();
    if (local_8 == (double *)0x0) {
      return (double *)0x0;
    }
    FUN_0040a80c(local_8);
    return local_8;
  }
  if (*DAT_0045f860 == '~') {
    *DAT_0045f864 = *DAT_0045f860;
    DAT_0045f864 = DAT_0045f864 + 1;
    DAT_0045f860 = DAT_0045f860 + 1;
    local_8 = FUN_0041518e();
    if (local_8 == (double *)0x0) {
      return (double *)0x0;
    }
    if (*(int *)(local_8 + 2) == 0x100) {
      FUN_0040a8b1((uint *)local_8);
      return local_8;
    }
    FUN_00413085((uint *)s_Illegal_operator_for_floating_po_00454330);
    FUN_004167ef((undefined4 *)local_8);
    return (double *)0x0;
  }
  if (*DAT_0045f860 == '!') {
    *DAT_0045f864 = *DAT_0045f860;
    DAT_0045f864 = DAT_0045f864 + 1;
    DAT_0045f860 = DAT_0045f860 + 1;
    local_8 = FUN_0041518e();
    if (local_8 == (double *)0x0) {
      return (double *)0x0;
    }
    FUN_0040a8f0(local_8);
    return local_8;
  }
  if (*DAT_0045f860 == '^') {
    DAT_0045eb10 = 1;
    *DAT_0045f864 = *DAT_0045f860;
    DAT_0045f864 = DAT_0045f864 + 1;
    DAT_0045f860 = DAT_0045f860 + 1;
    pdVar2 = FUN_0041518e();
    DAT_0045eb10 = 0;
    return pdVar2;
  }
  if (*DAT_0045f860 == '(') {
    *DAT_0045f864 = *DAT_0045f860;
    DAT_0045f864 = DAT_0045f864 + 1;
    DAT_0045f860 = DAT_0045f860 + 1;
    local_8 = (double *)FUN_00414a26();
    if (local_8 == (double *)0x0) {
      return (double *)0x0;
    }
    if (*DAT_0045f860 != ')') {
      FUN_004167ef((undefined4 *)local_8);
      FUN_00413085((uint *)s_Missing_____in_expression_0045435c);
      return (double *)0x0;
    }
    *DAT_0045f864 = *DAT_0045f860;
    DAT_0045f860 = DAT_0045f860 + 1;
    DAT_0045f864 = DAT_0045f864 + 1;
    return local_8;
  }
  local_8 = (double *)FUN_00416653();
  local_20 = 0;
  local_2c = 0;
  local_14 = 0;
  local_c = 0;
  local_30 = 0;
  if ((*DAT_0045f860 == '%') ||
     ((DAT_0044f7cc == 2 && ((*DAT_0045f860 == '0' || (*DAT_0045f860 == '1')))))) {
    if (*DAT_0045f860 == '%') {
      *DAT_0045f864 = *DAT_0045f860;
      DAT_0045f864 = DAT_0045f864 + 1;
      DAT_0045f860 = DAT_0045f860 + 1;
    }
    for (; (*DAT_0045f860 == '0' || (*DAT_0045f860 == '1')); DAT_0045f860 = DAT_0045f860 + 1) {
      local_20 = local_20 + 1;
      if (0x30 < local_20) {
        local_c = local_c * 2;
        if ((local_14 & 0x800000) != 0) {
          local_c = local_c + 1;
        }
        local_14 = local_14 & 0x7fffff;
      }
      if (0x18 < local_20) {
        local_14 = local_14 * 2;
        if ((local_2c & 0x800000) != 0) {
          local_14 = local_14 + 1;
        }
        local_2c = local_2c & 0x7fffff;
      }
      local_2c = *DAT_0045f860 + -0x30 + local_2c * 2;
      *DAT_0045f864 = *DAT_0045f860;
      DAT_0045f864 = DAT_0045f864 + 1;
    }
    local_c = local_c & 0xff;
    if (local_20 < 0x31) {
      if (local_20 < 0x19) {
        if (local_20 == 0) {
          FUN_004167ef((undefined4 *)local_8);
          FUN_00413085((uint *)s_Binary_constant_expected_00454378);
          return (double *)0x0;
        }
      }
      else {
        *(uint *)((int)local_8 + 0x14) = 6;
      }
    }
    else {
      *(uint *)((int)local_8 + 0x14) = 7;
    }
    *(uint *)local_8 = local_c;
    *(uint *)((int)local_8 + 4) = local_14;
    *(uint *)(local_8 + 1) = local_2c;
    return local_8;
  }
  if (*DAT_0045f860 != '$') {
    if (DAT_0044f7cc == 0x10) {
      if (__mb_cur_max < 2) {
        local_38 = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 0x80;
      }
      else {
        local_38 = _isctype((int)*DAT_0045f860,0x80);
      }
      if (local_38 != 0) goto LAB_0041568d;
    }
    if (*DAT_0045f860 != '`') {
      if (DAT_0044f7cc == 10) {
        if (__mb_cur_max < 2) {
          local_5c = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 4;
        }
        else {
          local_5c = _isctype((int)*DAT_0045f860,4);
        }
        if ((local_5c != 0) || (*DAT_0045f860 == '.')) goto LAB_00415a6a;
      }
      if (*DAT_0045f860 == '*') {
        DAT_0045f860 = DAT_0045f860 + 1;
        *(undefined4 *)(local_8 + 1) = DAT_0045f8c4;
        *(int *)((int)local_8 + 0x1c) = DAT_0045f8a0;
        *(undefined4 *)(local_8 + 4) = DAT_0045f8a4;
        *(undefined4 *)((int)local_8 + 0x24) = DAT_0045f8a8;
        *(undefined4 *)(local_8 + 5) = DAT_0045f8ac;
        *(uint *)(local_8 + 3) = *(uint *)(local_8 + 3) | -(uint)(DAT_0044f794 != '\0') & 0x1000;
        *(undefined4 *)((int)local_8 + 0x3c) = *(undefined4 *)(PTR_DAT_0044f978 + 8);
        *(undefined4 *)(local_8 + 8) = *(undefined4 *)(PTR_DAT_0044f97c + 8);
        *(uint *)((int)local_8 + 0x44) = -(uint)(DAT_0045ebc4 != 0) & DAT_0045ebc0;
        *(uint *)(local_8 + 9) = -(uint)(DAT_0045f8c0 != DAT_0045f8cc) & DAT_0045ebe8;
        if ((*(int *)(PTR_DAT_0044f97c + 0x6c) != 0) && (DAT_0045f8a0 == 0)) {
          *(undefined4 *)((int)local_8 + 0x4c) =
               *(undefined4 *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 4);
          *(undefined4 *)(local_8 + 10) = *(undefined4 *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 8);
        }
        *(undefined4 *)((int)local_8 + 0x54) = *(undefined4 *)(DAT_0045fb8c + 0x1c);
        FUN_00416453((int *)local_8);
        return local_8;
      }
      if (((*DAT_0045f860 == '\'') || (*DAT_0045f860 == '\"')) || (*DAT_0045f860 == '[')) {
        DAT_0045f860 = FUN_0043b08d(DAT_0045f860,&DAT_0045f220);
        if (DAT_0045f860 == (char *)0x0) {
          FUN_004167ef((undefined4 *)local_8);
          return (double *)0x0;
        }
        uVar3 = strlen(&DAT_0045f220);
        local_1c = (char *)FUN_00439857(uVar3 + 1);
        strcpy(local_1c,&DAT_0045f220);
        local_24 = strlen(local_1c);
        if (6 < (int)local_24) {
          local_24 = 6;
          FUN_004133a9((uint *)s_String_truncated_in_expression_e_004543ec);
        }
        *DAT_0045f864 = '\'';
        DAT_0045f864 = DAT_0045f864 + 1;
        strncpy(DAT_0045f864,local_1c,local_24);
        DAT_0045f864 = DAT_0045f864 + local_24;
        *DAT_0045f864 = '\'';
        DAT_0045f864 = DAT_0045f864 + 1;
        local_28 = local_1c;
        for (local_20 = 0; local_20 < (int)local_24; local_20 = local_20 + 1) {
          if (2 < local_20) {
            local_14 = local_14 << 8 | local_2c >> 0x10;
            local_2c = local_2c & 0xffff;
          }
          local_2c = local_2c * 0x100 + (int)*local_28;
          local_28 = local_28 + 1;
        }
        FUN_004398b5(local_1c);
        if (3 < (int)local_24) {
          *(undefined4 *)((int)local_8 + 0x14) = 6;
        }
        *(undefined4 *)local_8 = 0;
        *(uint *)((int)local_8 + 4) = local_14;
        *(uint *)(local_8 + 1) = local_2c;
        return local_8;
      }
      if (*DAT_0045f860 == '@') {
        DAT_0045f860 = DAT_0045f860 + 1;
        local_1c = DAT_0045f864;
        local_8 = FUN_004168c0(local_8);
        if (local_8 == (double *)0x0) {
          return (double *)0x0;
        }
        if (*(int *)((int)local_8 + 0x3c) < 0) {
          return local_8;
        }
        DAT_0045f864 = local_1c;
        FUN_00416453((int *)local_8);
        return local_8;
      }
      local_10 = (uint *)FUN_0043b448();
      if (local_10 == (uint *)0x0) {
        FUN_004167ef((undefined4 *)local_8);
        return (double *)0x0;
      }
      local_18 = FUN_00438441(local_10,2);
      if (local_18 == (undefined4 *)0x0) {
        if (DAT_0045f8fc == 1) {
          FUN_00439326();
          *(uint *)(local_8 + 3) = *(uint *)(local_8 + 3) | 0x8000000;
          *DAT_0045f864 = '{';
          DAT_0045f864 = DAT_0045f864 + 1;
          strcpy(DAT_0045f864,(char *)local_10);
          uVar3 = strlen(DAT_0045f864);
          DAT_0045f864 = DAT_0045f864 + uVar3;
          *DAT_0045f864 = '}';
          DAT_0045f864 = DAT_0045f864 + 1;
        }
        else if (DAT_0045f8fc == 0) {
          *(uint *)(local_8 + 3) = *(uint *)(local_8 + 3) | 0x8000000;
        }
      }
      else {
        if ((local_18[6] & 0x100) == 0) {
          if ((local_18[6] & 0x200) != 0) {
            *(undefined4 *)local_8 = local_18[2];
            *(undefined4 *)((int)local_8 + 4) = local_18[3];
            *(undefined4 *)(local_8 + 2) = 0x200;
          }
        }
        else {
          *(undefined4 *)local_8 = local_18[2];
          *(undefined4 *)((int)local_8 + 4) = local_18[3];
          *(undefined4 *)(local_8 + 1) = local_18[4];
        }
        *(undefined4 *)((int)local_8 + 0x1c) = local_18[7];
        *(undefined4 *)(local_8 + 4) = local_18[8];
        *(undefined4 *)((int)local_8 + 0x24) = local_18[9];
        *(undefined4 *)(local_8 + 5) = local_18[10];
        if ((local_18[6] & 0x800) != 0) {
          *(undefined4 *)((int)local_8 + 0x14) = 6;
        }
        *(uint *)(local_8 + 3) = *(uint *)(local_8 + 3) | local_18[6] & 0x7000;
        *(undefined4 *)((int)local_8 + 0x3c) = *(undefined4 *)(local_18[0x10] + 8);
        *(undefined4 *)(local_8 + 8) = *(undefined4 *)(local_18[0x11] + 8);
        *(undefined4 *)((int)local_8 + 0x44) = local_18[0xb];
        *(undefined4 *)(local_8 + 9) = local_18[0xc];
        *(undefined4 *)((int)local_8 + 0x4c) = local_18[0xe];
        *(undefined4 *)(local_8 + 10) = local_18[0xf];
        *(undefined4 *)((int)local_8 + 0x54) = local_18[0xd];
        *(undefined4 **)(local_8 + 0xb) = local_18;
        if ((((((ulonglong)local_8[3] & 0x1000) == 0) || ((local_18[6] & 0x30) != 0)) ||
            (((local_18[6] & 0x40000) != 0 && (DAT_0045eb20 == '\0')))) ||
           (((local_18[6] & 0x400) != 0 && (DAT_0045eb08 != '\0')))) {
          FUN_00416453((int *)local_8);
        }
        else {
          *DAT_0045f864 = '{';
          DAT_0045f864 = DAT_0045f864 + 1;
          strcpy(DAT_0045f864,(char *)local_10);
          uVar3 = strlen(DAT_0045f864);
          DAT_0045f864 = DAT_0045f864 + uVar3;
          *DAT_0045f864 = '}';
          DAT_0045f864 = DAT_0045f864 + 1;
        }
      }
      if (DAT_0045f8fc != 2) {
        return local_8;
      }
      if (*DAT_0045fc70 == DAT_0045f934) {
        *(uint *)(local_8 + 3) = *(uint *)(local_8 + 3) | 0x8000000;
        FUN_00439374();
      }
      if (local_18 != (undefined4 *)0x0) {
        return local_8;
      }
      if (DAT_0045ea70 != '\0') {
        return local_8;
      }
      if (DAT_0044f790 == '\0') {
        FUN_004167ef((undefined4 *)local_8);
        return (double *)0x0;
      }
      *(undefined4 *)((int)local_8 + 0x3c) = 0xffffffff;
      if ((char)*local_10 == DAT_0044f830) {
        *DAT_0045f864 = '0';
        DAT_0045f864 = DAT_0045f864 + 1;
        return local_8;
      }
      *DAT_0045f864 = '{';
      DAT_0045f864 = DAT_0045f864 + 1;
      strcpy(DAT_0045f864,(char *)local_10);
      uVar3 = strlen(DAT_0045f864);
      DAT_0045f864 = DAT_0045f864 + uVar3;
      *DAT_0045f864 = '}';
      DAT_0045f864 = DAT_0045f864 + 1;
      FUN_0043896d(local_10,0);
      return local_8;
    }
LAB_00415a6a:
    if (*DAT_0045f860 == '`') {
      *DAT_0045f864 = *DAT_0045f860;
      DAT_0045f864 = DAT_0045f864 + 1;
      DAT_0045f860 = DAT_0045f860 + 1;
    }
    local_1c = DAT_0045f860;
    local_28 = DAT_0045f864;
    while( true ) {
      if (__mb_cur_max < 2) {
        local_60 = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 4;
      }
      else {
        local_60 = _isctype((int)*DAT_0045f860,4);
      }
      if (local_60 == 0) break;
      local_20 = local_20 + 1;
      local_2c = local_2c * 10 + -0x30 + (int)*DAT_0045f860;
      local_14 = local_14 * 10;
      local_c = local_c * 10;
      local_30 = local_30 * 10;
      if (0xfffff < local_2c) {
        local_14 = local_14 + (local_2c >> 0x14);
        local_2c = local_2c & 0xfffff;
      }
      if (0xfffff < local_14) {
        local_c = local_c + (local_14 >> 0x14);
        local_14 = local_14 & 0xfffff;
      }
      if (0xfffff < local_c) {
        local_30 = local_30 + (local_c >> 0x14);
        local_c = local_c & 0xfffff;
      }
      *DAT_0045f864 = *DAT_0045f860;
      DAT_0045f864 = DAT_0045f864 + 1;
      DAT_0045f860 = DAT_0045f860 + 1;
    }
    if (((*DAT_0045f860 == '.') || (*DAT_0045f860 == 'e')) || (*DAT_0045f860 == 'E')) {
      DAT_0045f860 = local_1c;
      DAT_0045f864 = local_28;
      dVar4 = strtod(local_1c,&local_34);
      *local_8 = dVar4;
      if (local_34 == DAT_0045f860) {
        FUN_004167ef((undefined4 *)local_8);
        FUN_00413085((uint *)s_Floating_point_constant_expected_004543ac);
        return (double *)0x0;
      }
      DAT_0045f860 = local_34;
      local_20 = (int)*local_34;
      *local_34 = '\0';
      cVar1 = strcpy(local_28,local_1c);
      uVar3 = strlen((char *)CONCAT31(extraout_var,cVar1));
      DAT_0045f864 = DAT_0045f864 + uVar3;
      *DAT_0045f860 = (char)local_20;
      *(uint *)((int)local_8 + 0x14) = 8;
      *(uint *)(local_8 + 2) = 0x200;
    }
    else if (local_20 == 0) {
      FUN_004167ef((undefined4 *)local_8);
      FUN_00413085((uint *)s_Decimal_constant_expected_004543d0);
      return (double *)0x0;
    }
    if (*(uint *)(local_8 + 2) != 0x100) {
      return local_8;
    }
    *(uint *)(local_8 + 1) = (local_2c | local_14 << 0x14) & 0xffffff;
    local_14 = local_14 >> 4;
    *(uint *)((int)local_8 + 4) = (local_14 | local_c << 0x10) & 0xffffff;
    local_c = local_c >> 8;
    *(uint *)local_8 = local_c | (local_30 & 0xfff) << 0xc;
    FUN_004165e3((int *)local_8);
    return local_8;
  }
LAB_0041568d:
  if (*DAT_0045f860 != '$') {
    if (*DAT_0045f860 != '0') goto LAB_00415749;
    if (__mb_cur_max < 2) {
      local_3c = *(ushort *)(_pctype + DAT_0045f860[1] * 2) & 1;
    }
    else {
      local_3c = _isctype((int)DAT_0045f860[1],1);
    }
    if (local_3c == 0) {
      local_40 = (int)DAT_0045f860[1];
    }
    else {
      local_40 = tolower((int)DAT_0045f860[1]);
    }
    if (local_40 != 0x78) goto LAB_00415749;
  }
  *DAT_0045f864 = *DAT_0045f860;
  DAT_0045f864 = DAT_0045f864 + 1;
  DAT_0045f860 = DAT_0045f860 + 1;
LAB_00415749:
  if (__mb_cur_max < 2) {
    local_44 = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 1;
  }
  else {
    local_44 = _isctype((int)*DAT_0045f860,1);
  }
  if (local_44 == 0) {
    local_48 = (int)*DAT_0045f860;
  }
  else {
    local_48 = tolower((int)*DAT_0045f860);
  }
  if (local_48 == 0x78) {
    *DAT_0045f864 = *DAT_0045f860;
    DAT_0045f864 = DAT_0045f864 + 1;
    DAT_0045f860 = DAT_0045f860 + 1;
  }
  local_24 = 0;
  while( true ) {
    if (__mb_cur_max < 2) {
      local_4c = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 0x80;
    }
    else {
      local_4c = _isctype((int)*DAT_0045f860,0x80);
    }
    if (local_4c == 0) break;
    local_24 = local_24 + 1;
    if ((((*DAT_0045f860 != '0') || (local_c != 0)) || (local_14 != 0)) || (local_2c != 0)) {
      local_20 = local_20 + 1;
      if (0xc < local_20) {
        local_c = local_c << 4 | local_14 >> 0x14;
        local_14 = local_14 & 0xfffff;
      }
      if (6 < local_20) {
        local_14 = local_14 << 4 | local_2c >> 0x14;
        local_2c = local_2c & 0xfffff;
      }
      local_2c = local_2c << 4;
      if (*DAT_0045f860 < ':') {
        local_58 = *DAT_0045f860 + -0x30;
      }
      else {
        if (__mb_cur_max < 2) {
          local_50 = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 1;
        }
        else {
          local_50 = _isctype((int)*DAT_0045f860,1);
        }
        if (local_50 == 0) {
          local_54 = (int)*DAT_0045f860;
        }
        else {
          local_54 = tolower((int)*DAT_0045f860);
        }
        local_58 = local_54 + -0x57;
      }
      local_2c = local_2c + local_58;
    }
    *DAT_0045f864 = *DAT_0045f860;
    DAT_0045f864 = DAT_0045f864 + 1;
    DAT_0045f860 = DAT_0045f860 + 1;
  }
  local_c = local_c & 0xff;
  if (local_20 < 0xd) {
    if (local_20 < 7) {
      if (local_24 == 0) {
        FUN_004167ef((undefined4 *)local_8);
        FUN_00413085((uint *)s_Hex_constant_expected_00454394);
        return (double *)0x0;
      }
    }
    else {
      *(uint *)((int)local_8 + 0x14) = 6;
    }
  }
  else {
    *(uint *)((int)local_8 + 0x14) = 7;
  }
  *(uint *)local_8 = local_c;
  *(uint *)((int)local_8 + 4) = local_14;
  *(uint *)(local_8 + 1) = local_2c;
  return local_8;
}


/* ==== FUN_00416453 @ 00416453 ==== */

void __cdecl FUN_00416453(int *param_1)

{
  uint *dst;
  uint uVar1;
  char *local_8;
  
  if ((param_1[6] & 0x1000U) != 0) {
    *(undefined1 *)DAT_0045f864 = 0x5b;
    DAT_0045f864 = (uint *)((int)DAT_0045f864 + 1);
  }
  dst = DAT_0045f864;
  if (param_1[4] == 0x200) {
    FUN_0043c0ea(DAT_0045f864,(uint *)s____15E_00454418,*param_1,param_1[1]);
  }
  else {
    *(undefined1 *)DAT_0045f864 = 0;
    strcat((char *)dst,s__LRF__00454420);
    uVar1 = strlen((char *)dst);
    *(undefined1 *)((int)dst + uVar1) = 0x24;
    local_8 = (undefined1 *)((int)dst + uVar1) + 1;
    if (param_1[5] == 6) {
      sprintf(local_8,s__06lX_0044e098,param_1[1] & 0xffffff);
      uVar1 = strlen(local_8);
      local_8 = local_8 + uVar1;
    }
    sprintf(local_8,s__06lX_0044e098,param_1[2] & 0xffffff);
    uVar1 = strlen(local_8);
    sprintf(local_8 + uVar1,s___d__ld__d__d__d__d__d__00454428,param_1[8],param_1[9],param_1[0xf],
            param_1[0x10],param_1[0x11],param_1[0x12],param_1[0x14]);
  }
  uVar1 = strlen((char *)DAT_0045f864);
  DAT_0045f864 = (uint *)((int)DAT_0045f864 + uVar1);
  if ((param_1[6] & 0x1000U) != 0) {
    *(undefined1 *)DAT_0045f864 = 0x5d;
    DAT_0045f864 = (uint *)((int)DAT_0045f864 + 1);
  }
  return;
}


/* ==== FUN_004165e3 @ 004165e3 ==== */

void __cdecl FUN_004165e3(int *param_1)

{
  if (param_1[4] == 0x200) {
    param_1[5] = 8;
  }
  else if ((*param_1 == 0) || (*param_1 == 0xff)) {
    if ((param_1[1] == 0) || ((param_1[1] == 0xffffff || (param_1[7] != 4)))) {
      param_1[5] = 3;
    }
    else {
      param_1[5] = 6;
    }
  }
  else {
    param_1[5] = 7;
  }
  return;
}


/* ==== FUN_00416653 @ 00416653 ==== */

undefined4 * FUN_00416653(void)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  
  if (DAT_0045fc98 == (int *)0x0) {
    DAT_0045fc98 = (int *)FUN_00439857(DAT_00453f7c << 2);
    DAT_0045fc9c = DAT_0045fc98;
  }
  if (DAT_0045fc98 + DAT_00453f7c <= DAT_0045fc9c) {
    iVar3 = (int)DAT_0045fc9c - (int)DAT_0045fc98;
    uVar2 = DAT_00453f7c << 3;
    DAT_00453f7c = DAT_00453f7c << 1;
    DAT_0045fc98 = FUN_00439884(DAT_0045fc98,uVar2);
    DAT_0045fc9c = DAT_0045fc98 + (iVar3 >> 2);
  }
  puVar1 = (undefined4 *)FUN_00439857(0x60);
  puVar1[2] = 0;
  puVar1[1] = 0;
  *puVar1 = 0;
  puVar1[4] = 0x100;
  puVar1[8] = 4;
  puVar1[7] = 4;
  puVar1[9] = 0;
  puVar1[10] = 0;
  puVar1[5] = 3;
  puVar1[6] = 0;
  puVar1[0xb] = 0;
  puVar1[0xc] = 0;
  puVar1[0xe] = 0;
  puVar1[0xd] = 0;
  puVar1[0x10] = 0;
  puVar1[0xf] = 0;
  puVar1[0x12] = 0;
  puVar1[0x11] = 0;
  puVar1[0x13] = 0;
  puVar1[0x14] = 0;
  puVar1[0x15] = 0xffffffff;
  puVar1[0x16] = 0;
  *DAT_0045fc9c = (int)puVar1;
  DAT_0045fc9c = DAT_0045fc9c + 1;
  return puVar1;
}


