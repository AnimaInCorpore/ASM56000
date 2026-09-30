/* data: 16 functions from ASM56000 */

/* ==== FUN_0040b8ed @ 0040b8ed ==== */

float10 __cdecl FUN_0040b8ed(uint3 param_1,uint param_2)

{
  bool bVar1;
  double local_10;
  
  bVar1 = (param_1 & 0x800000) != 0;
  if (bVar1) {
    param_2 = (~param_2 & 0xffffff) + 1;
    param_1 = (~param_1 & 0x7fffff) + (uint3)((param_2 & 0x1000000) != 0);
  }
  param_2 = param_2 & 0xffffff;
  local_10 = (double)param_2 / 140737488355328.0 + (double)param_1 / 8388608.0;
  if (bVar1) {
    local_10 = -local_10;
  }
  return (float10)local_10;
}


/* ==== FUN_0040b9b7 @ 0040b9b7 ==== */

void __cdecl FUN_0040b9b7(double param_1,uint *param_2,uint *param_3)

{
  uint uVar1;
  longlong lVar2;
  ulonglong uVar3;
  uint local_34;
  uint local_24;
  uint local_14;
  
  if (-1.0 <= param_1) {
    if (param_1 < 1.0) {
      lVar2 = _ftol();
      local_14 = (uint)lVar2;
      uVar3 = _ftol();
      local_24 = (uint)uVar3 & 0xffffff;
      if (param_1 < 0.0) {
        uVar1 = (uint)((uVar3 & 0xffffff) == 0);
        if (uVar1 == 0) {
          local_34 = ~local_24 & 0xffffff;
        }
        else {
          local_34 = 0;
        }
        local_24 = local_34;
        local_14 = ~local_14 + uVar1;
      }
      *param_2 = local_14 & 0xffffff;
      *param_3 = local_24;
    }
    else {
      FUN_004133a9((uint *)s_Expression_value_outside_fractio_00452d4c);
      *param_2 = 0x7fffff;
      *param_3 = 0xffffff;
    }
  }
  else {
    FUN_004133a9((uint *)s_Expression_value_outside_fractio_00452d20);
    *param_2 = 0x800000;
    *param_3 = 0;
  }
  return;
}


/* ==== FUN_0040baed @ 0040baed ==== */

void __cdecl
FUN_0040baed(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4)

{
  *param_3 = param_2;
  *param_4 = param_1;
  return;
}


/* ==== FUN_0040bb20 @ 0040bb20 ==== */

/* WARNING: Removing unreachable block (ram,0x0040bfd3) */
/* WARNING: Removing unreachable block (ram,0x0040bde1) */

undefined4 FUN_0040bb20(void)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int in_stack_ffffffa0;
  uint local_5c;
  int local_58;
  int local_54;
  uint *local_50;
  double *local_48;
  int local_44;
  int local_38;
  uint local_10;
  uint local_c [2];
  
  local_38 = 0;
  local_48 = (double *)0x0;
  if (((DAT_0045eaa8 == '\0') || (DAT_0045f8c0 == DAT_0045f8cc)) &&
     ((DAT_0045f8a0 == 0x11f || (DAT_0045f8b0 != 0x11f)))) {
    local_54 = 1;
  }
  else {
    local_54 = 3;
  }
  bVar1 = false;
  if (local_54 == 1) {
    if ((DAT_0045f8a4 == 0x120) || (DAT_0045f8b4 == 0x120)) {
      uVar2 = FUN_0040c252();
      return uVar2;
    }
    if ((DAT_0045f8a4 == 0x121) || (DAT_0045f8b4 == 0x121)) {
      uVar2 = FUN_0040c6ac(2);
      return uVar2;
    }
  }
  FUN_0043b007(1);
  if (*DAT_0045f860 == '\0') {
    FUN_00413085((uint *)s_Missing_expression_00452db0);
    uVar2 = 0;
  }
  else {
    if ((((DAT_0045eadc != '\0') && (DAT_0045ea98 == '\0')) && (DAT_0045ea70 == '\0')) &&
       ((DAT_0045eacc == '\0' && (DAT_0045f8a0 == 0)))) {
      if (DAT_0045eb24 == '\0') {
        local_58 = DAT_0045eb78;
      }
      else {
        local_58 = DAT_0044f7e8;
      }
      FUN_0042433e(local_58);
    }
    while (*DAT_0045f860 != '\0') {
      local_44 = 0;
      local_10 = 0;
      local_c[0] = 0;
      if (*DAT_0045f860 == ',') {
        FUN_004232b6(&local_10,(uint *)0x0,local_54);
      }
      else if (((*DAT_0045f860 == '\'') || (*DAT_0045f860 == '\"')) || (*DAT_0045f860 == '[')) {
        local_48 = (double *)FUN_004142a7((undefined4 *)0x0,0);
        if (local_48 == (double *)0x0) {
          return 0;
        }
        local_c[0] = 0;
        local_44 = 0;
        local_50 = *(uint **)local_48;
        for (; local_44 < *(int *)(local_48 + 7); local_44 = local_44 + 1) {
          if ((DAT_0045f8b0 == 3) && (DAT_0044f79c != '\0')) {
            local_c[0] = *local_50;
            local_50 = local_50 + 1;
            local_44 = local_44 + 1;
          }
          if (local_44 == *(int *)(local_48 + 7)) {
            local_5c = 0;
          }
          else {
            local_5c = *local_50;
            local_50 = local_50 + 1;
          }
          local_10 = local_5c;
          FUN_004232b6(&local_10,(uint *)0x0,local_54);
        }
      }
      else {
        DAT_0045eb5c = 1;
        local_48 = (double *)FUN_00414862();
        DAT_0045eb5c = 0;
        if (local_48 == (double *)0x0) {
          DAT_0045eb5c = 0;
          return 0;
        }
        iVar4 = DAT_0045f8ac >> 4;
        iVar3 = DAT_0045f8bc >> 4;
        if (*(int *)(local_48 + 2) == 0x100) {
          local_c[0] = *(uint *)((int)local_48 + 4);
          local_10 = *(uint *)(local_48 + 1);
          if ((DAT_0045f8ac != 0) || (DAT_0045f8bc != 0)) {
            if ((iVar4 == 2) || (iVar3 == 2)) {
              if ((!bVar1) &&
                 ((iVar3 = FUN_0040a7ea((int)local_48), iVar3 < -0x80 ||
                  (iVar3 = FUN_0040a7ea((int)local_48), 0x7f < iVar3)))) {
                FUN_004133a9((uint *)s_EMI_8_bit_memory_value_truncated_00452dc4);
                bVar1 = true;
              }
              local_10 = local_10 & 0xff;
            }
            else if ((iVar4 == 3) || (iVar3 == 3)) {
              if ((!bVar1) &&
                 ((iVar3 = FUN_0040a7ea((int)local_48), iVar3 < -0x800 ||
                  (iVar3 = FUN_0040a7ea((int)local_48), 0x7ff < iVar3)))) {
                FUN_004133a9((uint *)s_EMI_12_bit_memory_value_truncate_00452de8);
                bVar1 = true;
              }
              local_10 = local_10 & 0xfff;
            }
            else if ((iVar4 == 4) || (iVar3 == 4)) {
              if ((!bVar1) &&
                 ((iVar3 = FUN_0040a7ea((int)local_48), iVar3 < -0x8000 ||
                  (iVar3 = FUN_0040a7ea((int)local_48), 0x7fff < iVar3)))) {
                FUN_004133a9((uint *)s_EMI_16_bit_memory_value_truncate_00452e0c);
                bVar1 = true;
              }
              local_10 = local_10 & 0xffff;
            }
            else if ((iVar4 == 5) || (iVar3 == 5)) {
              if ((!bVar1) &&
                 ((iVar3 = FUN_0040a7ea((int)local_48), iVar3 < -0x80000 ||
                  (iVar3 = FUN_0040a7ea((int)local_48), 0x7ffff < iVar3)))) {
                FUN_004133a9((uint *)s_EMI_20_bit_memory_value_truncate_00452e30);
                bVar1 = true;
              }
              local_10 = local_10 & 0xfffff;
            }
          }
        }
        else if (DAT_0045f8b0 == 3) {
          FUN_0040b9b7(*local_48,local_c,&local_10,in_stack_ffffffa0);
        }
        else if ((DAT_0045f8ac == 0) && (DAT_0045f8bc == 0)) {
          local_10 = FUN_0040b6bf(*local_48,in_stack_ffffffa0);
        }
        else if ((iVar4 == 2) || (iVar3 == 2)) {
          local_10 = FUN_0040b797(*local_48,0xff,in_stack_ffffffa0);
        }
        else if ((iVar4 == 3) || (iVar3 == 3)) {
          local_10 = FUN_0040b797(*local_48,0xfff,in_stack_ffffffa0);
        }
        else if ((iVar4 == 4) || (iVar3 == 4)) {
          local_10 = FUN_0040b797(*local_48,0xffff,in_stack_ffffffa0);
        }
        else if ((iVar4 == 5) || (iVar3 == 5)) {
          local_10 = FUN_0040b797(*local_48,0xfffff,in_stack_ffffffa0);
        }
        else {
          local_10 = FUN_0040b6bf(*local_48,in_stack_ffffffa0);
        }
        if ((((ulonglong)local_48[3] & 0x1000) == 0) && (-1 < *(int *)((int)local_48 + 0x3c))) {
          FUN_004232b6(&local_10,(uint *)0x0,local_54);
        }
        else {
          FUN_004232b6(&local_10,(uint *)&DAT_0045f428,local_54);
        }
      }
      if (local_48 != (double *)0x0) {
        FUN_004167ef((undefined4 *)local_48);
        local_48 = (double *)0x0;
      }
      if (*DAT_0045f860 != '\0') {
        if (*DAT_0045f860 != ',') {
          FUN_00413085((uint *)s_Syntax_error___expected_comma_00452e54);
          return 0;
        }
        DAT_0045f860 = DAT_0045f860 + 1;
        if (*DAT_0045f860 == '\0') {
          local_10 = 0;
          local_c[0] = 0;
          FUN_004232b6(&local_10,(uint *)0x0,local_54);
          local_38 = local_38 + 1;
        }
      }
      in_stack_ffffffa0 = local_44;
      if (local_44 == 0) {
        in_stack_ffffffa0 = 1;
      }
      local_38 = local_38 + in_stack_ffffffa0;
    }
    DAT_0045ea60 = 1;
    if ((DAT_0045ea10 != '\0') && (DAT_0045ebc4 == 0)) {
      FUN_0041e1e8(8,local_38);
    }
    DAT_0045f920 = 1;
    if (DAT_0045ea48 == '\0') {
      DAT_0045f924 = 0;
    }
    else {
      FUN_0041bdca('d');
      DAT_0045ea54 = 1;
    }
    uVar2 = 1;
  }
  return uVar2;
}


/* ==== FUN_0040c252 @ 0040c252 ==== */

undefined4 FUN_0040c252(void)

{
  char cVar1;
  char *pcVar2;
  char cVar3;
  undefined4 uVar4;
  undefined3 extraout_var;
  uint uVar5;
  undefined4 *puVar6;
  uint local_23c;
  char *local_238;
  int local_234;
  int local_230;
  uint *local_22c;
  int *local_228;
  int local_224;
  char *local_21c;
  char local_218 [512];
  int local_18;
  uint local_14;
  uint local_10;
  char *local_8;
  
  cVar1 = DAT_0044f79c;
  local_228 = (int *)0x0;
  if (((DAT_0045eaa8 == '\0') || (DAT_0045f8c0 == DAT_0045f8cc)) &&
     ((DAT_0045f8a0 == 0x11f || (DAT_0045f8b0 != 0x11f)))) {
    local_230 = 1;
  }
  else {
    local_230 = 3;
  }
  local_18 = local_230;
  FUN_0043b007(1);
  if (*DAT_0045f860 == '\0') {
    FUN_00413085((uint *)s_Missing_expression_00452e74);
    uVar4 = 0;
  }
  else {
    if ((((DAT_0045eadc != '\0') && (DAT_0045ea98 == '\0')) && (DAT_0045ea70 == '\0')) &&
       ((DAT_0045eacc == '\0' && (DAT_0045f8a0 == 0)))) {
      if (DAT_0045eb24 == '\0') {
        local_234 = DAT_0045eb78;
      }
      else {
        local_234 = DAT_0044f7e8;
      }
      FUN_0042433e(local_234);
    }
    local_21c = local_218;
    while (DAT_0045f860 != (char *)0x0) {
      cVar3 = strchr(DAT_0045f860,0x2c);
      local_8 = (char *)CONCAT31(extraout_var,cVar3);
      if (DAT_0045f860 == local_8) {
        *local_21c = '\0';
        pcVar2 = local_21c + 1;
        if (local_8[1] == '\0') {
          local_21c[1] = '\0';
          local_8 = (char *)0x0;
          pcVar2 = local_21c + 2;
        }
      }
      else if (((*DAT_0045f860 == '\'') || (*DAT_0045f860 == '\"')) || (*DAT_0045f860 == '[')) {
        local_8 = FUN_0043b08d(DAT_0045f860,local_21c);
        if (local_8 == (char *)0x0) {
          return 0;
        }
        uVar5 = strlen(local_21c);
        pcVar2 = local_21c + uVar5;
        if (*local_8 == '\0') {
          local_8 = (char *)0x0;
        }
      }
      else {
        if (local_8 != (char *)0x0) {
          *local_8 = '\0';
        }
        DAT_0045eb5c = 1;
        local_228 = FUN_00413f38();
        DAT_0045eb5c = 0;
        if (local_8 != (char *)0x0) {
          *local_8 = ',';
        }
        if (local_228 == (int *)0x0) {
          return 0;
        }
        *local_21c = (char)local_228[2];
        pcVar2 = local_21c + 1;
      }
      local_21c = pcVar2;
      if (local_228 != (int *)0x0) {
        FUN_004167ef(local_228);
        local_228 = (int *)0x0;
      }
      if (local_8 == (char *)0x0) {
        local_238 = (char *)0x0;
      }
      else {
        local_238 = local_8 + 1;
        local_8 = local_238;
      }
      DAT_0045f860 = local_238;
    }
    if ((DAT_0045f8a0 == 0x11f) || (DAT_0045f8b0 == 0x11f)) {
      DAT_0044f79c = '\0';
    }
    puVar6 = FUN_004142a7((undefined4 *)local_218,(int)local_21c - (int)local_218);
    if (puVar6 == (undefined4 *)0x0) {
      uVar4 = 0;
    }
    else {
      local_10 = 0;
      local_224 = 0;
      local_22c = (uint *)*puVar6;
      DAT_0044f79c = cVar1;
      for (; local_224 < (int)puVar6[0xe]; local_224 = local_224 + 1) {
        if ((DAT_0045f8b0 == 3) && (DAT_0044f79c != '\0')) {
          local_10 = *local_22c;
          local_22c = local_22c + 1;
          local_224 = local_224 + 1;
        }
        if (local_224 == puVar6[0xe]) {
          local_23c = 0;
        }
        else {
          local_23c = *local_22c;
          local_22c = local_22c + 1;
        }
        local_14 = local_23c;
        FUN_004232b6(&local_14,(uint *)0x0,local_18);
      }
      DAT_0045ea60 = 1;
      if ((DAT_0045ea10 != '\0') && (DAT_0045ebc4 == 0)) {
        FUN_0041e1e8(8,local_224);
      }
      DAT_0045f920 = 1;
      if (DAT_0045ea48 == '\0') {
        DAT_0045f924 = 0;
      }
      else {
        FUN_0041bdca('d');
        DAT_0045ea54 = 1;
      }
      uVar4 = 1;
    }
  }
  return uVar4;
}


/* ==== FUN_0040c6ac @ 0040c6ac ==== */

/* WARNING: Removing unreachable block (ram,0x0040ca4f) */

undefined4 __cdecl FUN_0040c6ac(int param_1)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int in_stack_ffffffb0;
  double *local_44;
  int local_34;
  uint local_10;
  uint local_c [2];
  
  local_34 = 0;
  local_44 = (double *)0x0;
  bVar3 = false;
  FUN_0043b007(1);
  if (*DAT_0045f860 == '\0') {
    FUN_00413085((uint *)s_Missing_expression_00452e88);
    return 0;
  }
  if (DAT_0045f8c0 != DAT_0045f8cc) {
    if ((DAT_0045f8a0 == 0x11f) || (DAT_0045f8b0 != 0x11f)) {
      if ((DAT_0045f8a0 == 0x11f) && ((DAT_0045f8b0 != 0x11f && (param_1 == 4)))) {
        FUN_00413085((uint *)s_Incompatible_memory_spaces_for_l_00452edc);
        return 0;
      }
    }
    else {
      if (3 < param_1) {
        FUN_00413085((uint *)s_Incompatible_memory_spaces_for_l_00452e9c);
        return 0;
      }
      param_1 = 3;
    }
  }
  uVar1 = *(uint *)(*(int *)(DAT_0045fb88 + 0x24) + 0x30);
  uVar2 = *(uint *)(*(int *)(DAT_0045fb8c + 0x24) + 0x30);
  iVar4 = FUN_0040e749(0x400,2,0,0);
  if (iVar4 == 0) {
    uVar5 = 0;
  }
  else {
    FUN_0040f21d(uVar1,uVar2);
    FUN_0043797a();
    if ((((DAT_0045eadc != '\0') && (DAT_0045ea98 == '\0')) && (DAT_0045ea70 == '\0')) &&
       ((DAT_0045eacc == '\0' && (DAT_0045f8a0 == 0)))) {
      in_stack_ffffffb0 = DAT_0045eb78;
      if (DAT_0045eb24 != '\0') {
        in_stack_ffffffb0 = DAT_0044f7e8;
      }
      FUN_0042433e(in_stack_ffffffb0);
    }
    DAT_0045ebc4 = 0;
    while (*DAT_0045f860 != '\0') {
      local_10 = 0;
      local_c[0] = 0;
      if (*DAT_0045f860 == ',') {
        FUN_004232b6(&local_10,(uint *)0x0,param_1);
      }
      else {
        DAT_0045eb5c = 1;
        if (param_1 < 4) {
          local_44 = (double *)FUN_0041409f();
        }
        else {
          local_44 = (double *)FUN_00414862();
        }
        DAT_0045eb5c = 0;
        if (local_44 == (double *)0x0) {
          DAT_0045eb5c = 0;
          return 0;
        }
        iVar6 = DAT_0045f8ac >> 4;
        iVar4 = DAT_0045f8bc >> 4;
        if (*(int *)(local_44 + 2) == 0x100) {
          local_c[0] = *(uint *)((int)local_44 + 4);
          local_10 = *(uint *)(local_44 + 1);
          if ((DAT_0045f8ac != 0) || (DAT_0045f8bc != 0)) {
            if ((iVar6 == 2) || (iVar4 == 2)) {
              if ((!bVar3) &&
                 ((iVar4 = FUN_0040a7ea((int)local_44), iVar4 < -0x80 ||
                  (iVar4 = FUN_0040a7ea((int)local_44), 0x7f < iVar4)))) {
                FUN_004133a9((uint *)s_EMI_8_bit_memory_value_truncated_00452f1c);
                bVar3 = true;
              }
              local_10 = local_10 & 0xff;
            }
            else if ((iVar6 == 3) || (iVar4 == 3)) {
              if ((!bVar3) &&
                 ((iVar4 = FUN_0040a7ea((int)local_44), iVar4 < -0x800 ||
                  (iVar4 = FUN_0040a7ea((int)local_44), 0x7ff < iVar4)))) {
                FUN_004133a9((uint *)s_EMI_12_bit_memory_value_truncate_00452f40);
                bVar3 = true;
              }
              local_10 = local_10 & 0xfff;
            }
            else if ((iVar6 == 4) || (iVar4 == 4)) {
              if ((!bVar3) &&
                 ((iVar4 = FUN_0040a7ea((int)local_44), iVar4 < -0x8000 ||
                  (iVar4 = FUN_0040a7ea((int)local_44), 0x7fff < iVar4)))) {
                FUN_004133a9((uint *)s_EMI_16_bit_memory_value_truncate_00452f64);
                bVar3 = true;
              }
              local_10 = local_10 & 0xffff;
            }
          }
        }
        else if (DAT_0045f8b0 == 3) {
          FUN_0040b9b7(*local_44,local_c,&local_10,in_stack_ffffffb0);
        }
        else if ((DAT_0045f8ac == 0) && (DAT_0045f8bc == 0)) {
          local_10 = FUN_0040b6bf(*local_44,in_stack_ffffffb0);
        }
        else if ((iVar6 == 2) || (iVar4 == 2)) {
          local_10 = FUN_0040b797(*local_44,0xff,in_stack_ffffffb0);
        }
        else if ((iVar6 == 3) || (iVar4 == 3)) {
          local_10 = FUN_0040b797(*local_44,0xfff,in_stack_ffffffb0);
        }
        else if ((iVar6 == 4) || (iVar4 == 4)) {
          local_10 = FUN_0040b797(*local_44,0xffff,in_stack_ffffffb0);
        }
        else if ((iVar6 == 5) || (iVar4 == 5)) {
          local_10 = FUN_0040b797(*local_44,0xfffff,in_stack_ffffffb0);
        }
        else {
          local_10 = FUN_0040b6bf(*local_44,in_stack_ffffffb0);
        }
        if ((((ulonglong)local_44[3] & 0x1000) == 0) && (-1 < *(int *)((int)local_44 + 0x3c))) {
          FUN_004232b6(&local_10,(uint *)0x0,param_1);
        }
        else {
          FUN_004232b6(&local_10,(uint *)&DAT_0045f428,param_1);
        }
      }
      if (local_44 != (double *)0x0) {
        FUN_004167ef((undefined4 *)local_44);
        local_44 = (double *)0x0;
      }
      if (*DAT_0045f860 != '\0') {
        if (*DAT_0045f860 != ',') {
          FUN_00413085((uint *)s_Syntax_error___expected_comma_00452f88);
          return 0;
        }
        DAT_0045f860 = DAT_0045f860 + 1;
        if (*DAT_0045f860 == '\0') {
          local_10 = 0;
          local_c[0] = 0;
          FUN_004232b6(&local_10,(uint *)0x0,param_1);
          local_34 = local_34 + 1;
        }
      }
      local_34 = local_34 + param_1;
    }
    DAT_0045ea60 = 1;
    if (DAT_0045ea10 != '\0') {
      FUN_0041e1e8(8,local_34);
    }
    DAT_0045f920 = 1;
    if (DAT_0045ea48 == '\0') {
      DAT_0045f924 = 0;
    }
    else {
      FUN_0041bdca('d');
      DAT_0045ea54 = 1;
    }
    uVar5 = 1;
  }
  return uVar5;
}


/* ==== FUN_0040ccad @ 0040ccad ==== */

/* WARNING: Removing unreachable block (ram,0x0040ce43) */
/* WARNING: Removing unreachable block (ram,0x0040d037) */

undefined4 FUN_0040ccad(void)

{
  uint uVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  double *local_20;
  uint local_10;
  uint local_c [2];
  
  if (((DAT_0045eaa8 == '\0') || (DAT_0045f8c0 == DAT_0045f8cc)) &&
     ((DAT_0045f8a0 == 0x11f || (DAT_0045f8b0 != 0x11f)))) {
    iVar7 = 1;
  }
  else {
    iVar7 = 3;
  }
  if (iVar7 == 1) {
    if ((DAT_0045f8a4 == 0x120) || (DAT_0045f8b4 == 0x120)) {
      uVar2 = FUN_0040d1f7(1);
      return uVar2;
    }
    if ((DAT_0045f8a4 == 0x121) || (DAT_0045f8b4 == 0x121)) {
      uVar2 = FUN_0040d1f7(2);
      return uVar2;
    }
  }
  iVar4 = iVar7;
  FUN_0043b007(1);
  piVar3 = FUN_00413e70();
  if (piVar3 == (int *)0x0) {
    uVar2 = 0;
  }
  else if ((piVar3[6] & 0x8000000U) == 0) {
    uVar1 = piVar3[2];
    FUN_004167ef(piVar3);
    if (uVar1 == 0) {
      FUN_00413085((uint *)s_Expression_must_be_greater_than_z_00452fd0);
      uVar2 = 0;
    }
    else {
      local_10 = 0;
      local_c[0] = 0;
      if (*DAT_0045f860 == '\0') {
        local_20 = (double *)0x0;
      }
      else {
        DAT_0045f860 = DAT_0045f860 + 1;
        local_20 = (double *)FUN_00414862();
        if (local_20 == (double *)0x0) {
          return 0;
        }
        iVar5 = DAT_0045f8ac >> 4;
        iVar6 = DAT_0045f8bc >> 4;
        if (*(int *)(local_20 + 2) == 0x100) {
          local_c[0] = *(uint *)((int)local_20 + 4);
          local_10 = *(uint *)(local_20 + 1);
          if ((DAT_0045f8ac != 0) || (DAT_0045f8bc != 0)) {
            if ((iVar5 == 2) || (iVar6 == 2)) {
              iVar4 = FUN_0040a7ea((int)local_20);
              if ((iVar4 < -0x80) || (iVar4 = FUN_0040a7ea((int)local_20), 0x7f < iVar4)) {
                FUN_004133a9((uint *)s_EMI_8_bit_memory_value_truncated_00452ff8);
              }
              local_10 = local_10 & 0xff;
            }
            else if ((iVar5 == 3) || (iVar6 == 3)) {
              iVar4 = FUN_0040a7ea((int)local_20);
              if ((iVar4 < -0x800) || (iVar4 = FUN_0040a7ea((int)local_20), 0x7ff < iVar4)) {
                FUN_004133a9((uint *)s_EMI_12_bit_memory_value_truncate_0045301c);
              }
              local_10 = local_10 & 0xfff;
            }
            else if ((iVar5 == 4) || (iVar6 == 4)) {
              iVar4 = FUN_0040a7ea((int)local_20);
              if ((iVar4 < -0x8000) || (iVar4 = FUN_0040a7ea((int)local_20), 0x7fff < iVar4)) {
                FUN_004133a9((uint *)s_EMI_16_bit_memory_value_truncate_00453040);
              }
              local_10 = local_10 & 0xffff;
            }
            else if ((iVar5 == 5) || (iVar6 == 5)) {
              iVar4 = FUN_0040a7ea((int)local_20);
              if ((iVar4 < -0x80000) || (iVar4 = FUN_0040a7ea((int)local_20), 0x7ffff < iVar4)) {
                FUN_004133a9((uint *)s_EMI_20_bit_memory_value_truncate_00453064);
              }
              local_10 = local_10 & 0xfffff;
            }
          }
        }
        else if (DAT_0045f8b0 == 3) {
          FUN_0040b9b7(*local_20,local_c,&local_10,iVar4);
        }
        else if ((DAT_0045f8ac == 0) && (DAT_0045f8bc == 0)) {
          local_10 = FUN_0040b6bf(*local_20,iVar4);
        }
        else if ((iVar5 == 2) || (iVar6 == 2)) {
          local_10 = FUN_0040b797(*local_20,0xff,iVar4);
        }
        else if ((iVar5 == 3) || (iVar6 == 3)) {
          local_10 = FUN_0040b797(*local_20,0xfff,iVar4);
        }
        else if ((iVar5 == 4) || (iVar6 == 4)) {
          local_10 = FUN_0040b797(*local_20,0xffff,iVar4);
        }
        else if ((iVar5 == 5) || (iVar6 == 5)) {
          local_10 = FUN_0040b797(*local_20,0xfffff,iVar4);
        }
        else {
          local_10 = FUN_0040b6bf(*local_20,iVar4);
        }
      }
      if ((local_20 == (double *)0x0) ||
         ((((ulonglong)local_20[3] & 0x1000) == 0 && (-1 < *(int *)((int)local_20 + 0x3c))))) {
        FUN_004238a9(uVar1,&local_10,(uint *)0x0,0,iVar7);
      }
      else {
        FUN_004238a9(uVar1,&local_10,(uint *)&DAT_0045f428,0,iVar7);
      }
      if (local_20 != (double *)0x0) {
        FUN_004167ef((undefined4 *)local_20);
      }
      DAT_0045ea60 = 1;
      if ((DAT_0045ea10 != '\0') && (DAT_0045ebc4 == 0)) {
        FUN_0041e1e8(8,uVar1);
      }
      uVar2 = 1;
    }
  }
  else {
    FUN_00413085((uint *)s_Expression_contains_forward_refe_00452fa8);
    FUN_004167ef(piVar3);
    uVar2 = 0;
  }
  return uVar2;
}


/* ==== FUN_0040d1f7 @ 0040d1f7 ==== */

/* WARNING: Removing unreachable block (ram,0x0040d594) */

undefined4 __cdecl FUN_0040d1f7(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  double *local_20;
  uint local_10;
  uint local_c [2];
  
  FUN_0043b007(1);
  if (DAT_0045f8c0 != DAT_0045f8cc) {
    if ((DAT_0045f8a0 == 0x11f) || (DAT_0045f8b0 != 0x11f)) {
      if ((DAT_0045f8a0 == 0x11f) && ((DAT_0045f8b0 != 0x11f && (param_1 == 4)))) {
        FUN_00413085((uint *)s_Incompatible_memory_spaces_for_l_004530c8);
        return 0;
      }
    }
    else {
      if (3 < param_1) {
        FUN_00413085((uint *)s_Incompatible_memory_spaces_for_l_00453088);
        return 0;
      }
      param_1 = 3;
    }
  }
  local_20 = (double *)FUN_00413e70();
  if (local_20 == (double *)0x0) {
    uVar4 = 0;
  }
  else if (((ulonglong)local_20[3] & 0x8000000) == 0) {
    uVar1 = *(uint *)(local_20 + 1);
    FUN_004167ef((undefined4 *)local_20);
    if (uVar1 == 0) {
      FUN_00413085((uint *)s_Expression_must_be_greater_than_z_00453130);
      uVar4 = 0;
    }
    else {
      local_10 = 0;
      local_c[0] = 0;
      if (*DAT_0045f860 == '\0') {
        local_20 = (double *)0x0;
      }
      else {
        DAT_0045f860 = DAT_0045f860 + 1;
        iVar6 = param_1;
        if (param_1 == 1) {
          local_20 = (double *)FUN_00413f38();
        }
        else if (param_1 == 2) {
          local_20 = (double *)FUN_0041409f();
        }
        else if (param_1 == 4) {
          local_20 = (double *)FUN_00414862();
        }
        else {
          FUN_00412fa0((uint *)s_block_size_select_error_00453158);
        }
        if (local_20 == (double *)0x0) {
          return 0;
        }
        iVar7 = DAT_0045f8ac >> 4;
        iVar5 = DAT_0045f8bc >> 4;
        if (*(int *)(local_20 + 2) == 0x100) {
          local_c[0] = *(uint *)((int)local_20 + 4);
          local_10 = *(uint *)(local_20 + 1);
          if ((DAT_0045f8ac != 0) || (DAT_0045f8bc != 0)) {
            if ((iVar7 == 2) || (iVar5 == 2)) {
              iVar6 = FUN_0040a7ea((int)local_20);
              if ((iVar6 < -0x80) || (iVar6 = FUN_0040a7ea((int)local_20), 0x7f < iVar6)) {
                FUN_004133a9((uint *)s_EMI_8_bit_memory_value_truncated_00453170);
              }
              local_10 = local_10 & 0xff;
            }
            else if ((iVar7 == 3) || (iVar5 == 3)) {
              iVar6 = FUN_0040a7ea((int)local_20);
              if ((iVar6 < -0x800) || (iVar6 = FUN_0040a7ea((int)local_20), 0x7ff < iVar6)) {
                FUN_004133a9((uint *)s_EMI_12_bit_memory_value_00_trunc_00453194);
              }
              local_10 = local_10 & 0xfff;
            }
            else if ((iVar7 == 4) || (iVar5 == 4)) {
              iVar6 = FUN_0040a7ea((int)local_20);
              if ((iVar6 < -0x8000) || (iVar6 = FUN_0040a7ea((int)local_20), 0x7fff < iVar6)) {
                FUN_004133a9((uint *)s_EMI_16_bit_memory_value_truncate_004531bc);
              }
              local_10 = local_10 & 0xffff;
            }
            else if ((iVar7 == 5) || (iVar5 == 5)) {
              iVar6 = FUN_0040a7ea((int)local_20);
              if ((iVar6 < -0x80000) || (iVar6 = FUN_0040a7ea((int)local_20), 0x7ffff < iVar6)) {
                FUN_004133a9((uint *)s_EMI_20_bit_memory_value_truncate_004531e0);
              }
              local_10 = local_10 & 0xfffff;
            }
          }
        }
        else if (DAT_0045f8b0 == 3) {
          FUN_0040b9b7(*local_20,local_c,&local_10,iVar6);
        }
        else if ((DAT_0045f8ac == 0) && (DAT_0045f8bc == 0)) {
          local_10 = FUN_0040b6bf(*local_20,iVar6);
        }
        else if ((iVar7 == 2) || (iVar5 == 2)) {
          local_10 = FUN_0040b797(*local_20,0xff,iVar6);
        }
        else if ((iVar7 == 3) || (iVar5 == 3)) {
          local_10 = FUN_0040b797(*local_20,0xfff,iVar6);
        }
        else if ((iVar7 == 4) || (iVar5 == 4)) {
          local_10 = FUN_0040b797(*local_20,0xffff,iVar6);
        }
        else if ((iVar7 == 5) || (iVar5 == 5)) {
          local_10 = FUN_0040b797(*local_20,0xfffff,iVar6);
        }
        else {
          local_10 = FUN_0040b6bf(*local_20,iVar6);
        }
      }
      uVar2 = *(uint *)(*(int *)(DAT_0045fb88 + 0x24) + 0x30);
      uVar3 = *(uint *)(*(int *)(DAT_0045fb8c + 0x24) + 0x30);
      if ((param_1 < 2) || (iVar6 = FUN_0040e749(0x400,2,0,0), iVar6 != 0)) {
        if ((local_20 == (double *)0x0) ||
           ((((ulonglong)local_20[3] & 0x1000) == 0 && (-1 < *(int *)((int)local_20 + 0x3c))))) {
          FUN_004238a9(uVar1,&local_10,(uint *)0x0,(uint)(1 < param_1),param_1);
        }
        else {
          FUN_004238a9(uVar1,&local_10,(uint *)&DAT_0045f428,(uint)(1 < param_1),param_1);
        }
        if (1 < param_1) {
          FUN_0040f21d(uVar2,uVar3);
        }
        if (local_20 != (double *)0x0) {
          FUN_004167ef((undefined4 *)local_20);
        }
        DAT_0045ebc4 = 0;
        DAT_0045ea60 = 1;
        if (DAT_0045ea10 != '\0') {
          FUN_0041e1e8(8,uVar1);
        }
        DAT_0045f920 = 1;
        uVar4 = 1;
      }
      else {
        uVar4 = 0;
      }
    }
  }
  else {
    FUN_00413085((uint *)s_Expression_contains_forward_refe_00453108);
    FUN_004167ef((undefined4 *)local_20);
    uVar4 = 0;
  }
  return uVar4;
}


/* ==== FUN_0040d7c7 @ 0040d7c7 ==== */

/* WARNING: Removing unreachable block (ram,0x0040d97b) */
/* WARNING: Removing unreachable block (ram,0x0040db6d) */

undefined4 __cdecl FUN_0040d7c7(uint param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  double *local_24;
  uint local_10;
  uint local_c [2];
  
  if (((DAT_0045eaa8 == '\0') || (DAT_0045f8c0 == DAT_0045f8cc)) &&
     ((DAT_0045f8a0 == 0x11f || (DAT_0045f8b0 != 0x11f)))) {
    uVar7 = 1;
  }
  else {
    uVar7 = 3;
  }
  FUN_0043b007(1);
  if ((DAT_0045eb34 == '\0') ||
     ((((DAT_0044f794 == '\0' && (DAT_0044f798 == '\0')) || (DAT_0045f8c0 == DAT_0045f8cc)) ||
      (DAT_0045f8a0 != 0)))) {
    if ((DAT_0045f8a0 == 0x11f) || (DAT_0045f8b0 == 0x11f)) {
      FUN_004133a9((uint *)s_Byte_addressable_memory_not_supp_0045324c);
    }
    piVar4 = FUN_00413e70();
    if (piVar4 == (int *)0x0) {
      uVar7 = 0;
    }
    else if ((piVar4[6] & 0x8000000U) == 0) {
      uVar1 = piVar4[2];
      FUN_004167ef(piVar4);
      if (uVar1 == 0) {
        FUN_00413085((uint *)s_Expression_must_be_greater_than_z_004532b0);
        uVar7 = 0;
      }
      else {
        local_10 = 0;
        local_c[0] = 0;
        if (*DAT_0045f860 == '\0') {
          local_24 = (double *)0x0;
        }
        else {
          DAT_0045f860 = DAT_0045f860 + 1;
          local_24 = (double *)FUN_00414862();
          if (local_24 == (double *)0x0) {
            return 0;
          }
          iVar6 = DAT_0045f8ac >> 4;
          iVar5 = DAT_0045f8bc >> 4;
          if (*(int *)(local_24 + 2) == 0x100) {
            local_c[0] = *(uint *)((int)local_24 + 4);
            local_10 = *(uint *)(local_24 + 1);
            if ((DAT_0045f8ac != 0) || (DAT_0045f8bc != 0)) {
              if ((iVar6 == 2) || (iVar5 == 2)) {
                iVar5 = FUN_0040a7ea((int)local_24);
                if ((iVar5 < -0x80) || (iVar5 = FUN_0040a7ea((int)local_24), 0x7f < iVar5)) {
                  FUN_004133a9((uint *)s_EMI_8_bit_memory_value_truncated_004532d8);
                }
                local_10 = local_10 & 0xff;
              }
              else if ((iVar6 == 3) || (iVar5 == 3)) {
                iVar5 = FUN_0040a7ea((int)local_24);
                if ((iVar5 < -0x800) || (iVar5 = FUN_0040a7ea((int)local_24), 0x7ff < iVar5)) {
                  FUN_004133a9((uint *)s_EMI_12_bit_memory_value_truncate_004532fc);
                }
                local_10 = local_10 & 0xfff;
              }
              else if ((iVar6 == 4) || (iVar5 == 4)) {
                iVar5 = FUN_0040a7ea((int)local_24);
                if ((iVar5 < -0x8000) || (iVar5 = FUN_0040a7ea((int)local_24), 0x7fff < iVar5)) {
                  FUN_004133a9((uint *)s_EMI_16_bit_memory_value_truncate_00453320);
                }
                local_10 = local_10 & 0xffff;
              }
              else if ((iVar6 == 5) || (iVar5 == 5)) {
                iVar5 = FUN_0040a7ea((int)local_24);
                if ((iVar5 < -0x80000) || (iVar5 = FUN_0040a7ea((int)local_24), 0x7ffff < iVar5)) {
                  FUN_004133a9((uint *)s_EMI_20_bit_memory_value_truncate_00453344);
                }
                local_10 = local_10 & 0xfffff;
              }
            }
          }
          else if (DAT_0045f8b0 == 3) {
            FUN_0040b9b7(*local_24,local_c,&local_10,uVar7);
          }
          else if ((DAT_0045f8ac == 0) && (DAT_0045f8bc == 0)) {
            local_10 = FUN_0040b6bf(*local_24,uVar7);
          }
          else if ((iVar6 == 2) || (iVar5 == 2)) {
            local_10 = FUN_0040b797(*local_24,0xff,uVar7);
          }
          else if ((iVar6 == 3) || (iVar5 == 3)) {
            local_10 = FUN_0040b797(*local_24,0xfff,uVar7);
          }
          else if ((iVar6 == 4) || (iVar5 == 4)) {
            local_10 = FUN_0040b797(*local_24,0xffff,uVar7);
          }
          else if ((iVar6 == 5) || (iVar5 == 5)) {
            local_10 = FUN_0040b797(*local_24,0xfffff,uVar7);
          }
          else {
            local_10 = FUN_0040b6bf(*local_24,uVar7);
          }
        }
        uVar2 = *(uint *)(*(int *)(DAT_0045fb88 + 0x24) + 0x30);
        uVar3 = *(uint *)(*(int *)(DAT_0045fb8c + 0x24) + 0x30);
        iVar5 = FUN_0040e749(param_1,uVar1,param_2,0);
        if (iVar5 == 0) {
          uVar7 = 0;
        }
        else {
          if ((local_24 == (double *)0x0) ||
             ((((ulonglong)local_24[3] & 0x1000) == 0 && (-1 < *(int *)((int)local_24 + 0x3c))))) {
            FUN_004238a9(uVar1,&local_10,(uint *)0x0,1,1);
          }
          else {
            FUN_004238a9(uVar1,&local_10,(uint *)&DAT_0045f428,1,1);
          }
          FUN_0040f21d(uVar2,uVar3);
          if (local_24 != (double *)0x0) {
            FUN_004167ef((undefined4 *)local_24);
          }
          DAT_0045ebc4 = 0;
          DAT_0045ea60 = 1;
          if (DAT_0045ea10 != '\0') {
            FUN_0041e1e8(param_1,uVar1);
          }
          DAT_0045f920 = 1;
          uVar7 = 1;
        }
      }
    }
    else {
      FUN_00413085((uint *)s_Expression_contains_forward_refe_00453288);
      FUN_004167ef(piVar4);
      uVar7 = 0;
    }
  }
  else {
    FUN_00413085((uint *)s_Directive_not_allowed_in_P_memor_00453204);
    uVar7 = 0;
  }
  return uVar7;
}


/* ==== FUN_0040dd85 @ 0040dd85 ==== */

undefined4 FUN_0040dd85(void)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  int local_28;
  int local_24;
  int local_8;
  
  FUN_0043b007(1);
  piVar2 = FUN_00413e70();
  if (piVar2 == (int *)0x0) {
    uVar3 = 0;
  }
  else if ((piVar2[6] & 0x8000000U) == 0) {
    iVar1 = piVar2[2];
    if (iVar1 == 0) {
      FUN_00413085((uint *)s_Expression_must_be_greater_than_z_00453390);
      FUN_004167ef(piVar2);
      uVar3 = 0;
    }
    else {
      FUN_004167ef(piVar2);
      if ((DAT_0045f8ac & 0xf) == 0) {
        local_24 = 1;
      }
      else {
        local_24 = (int)(CONCAT44((int)DAT_0045f8ac >> 0x1f,(int)DAT_0045f8ac >> 4) /
                        (longlong)(int)(DAT_0045f8ac & 0xf)) +
                   ((int)DAT_0045f8ac >> 4 & (uint)((DAT_0045f8ac & 1) == 0));
      }
      if ((DAT_0045f8bc & 0xf) == 0) {
        local_28 = 1;
      }
      else {
        local_28 = (int)(CONCAT44((int)DAT_0045f8bc >> 0x1f,(int)DAT_0045f8bc >> 4) /
                        (longlong)(int)(DAT_0045f8bc & 0xf)) +
                   ((int)DAT_0045f8bc >> 4 & (uint)((DAT_0045f8bc & 1) == 0));
      }
      local_8 = iVar1 * local_28;
      if ((DAT_0045eaa4 != '\0') && (DAT_0045f8b0 != 0x1c)) {
        local_8 = local_8 * 3;
      }
      FUN_0040ea5e(*DAT_0045f8c0,*DAT_0045f8c0 + iVar1 * local_24,*DAT_0045f8cc,
                   *DAT_0045f8cc + local_8,0,*(uint *)(*(int *)(DAT_0045fb88 + 0x24) + 0x30),
                   *(uint *)(*(int *)(DAT_0045fb8c + 0x24) + 0x30));
      FUN_0043b926(0);
      DAT_0045ea60 = 1;
      if ((DAT_0045ea10 != '\0') && (DAT_0045ebc4 == 0)) {
        FUN_0041e1e8(4,iVar1);
      }
      DAT_0045f920 = 1;
      uVar3 = 1;
    }
  }
  else {
    FUN_00413085((uint *)s_Expression_contains_forward_refe_00453368);
    FUN_004167ef(piVar2);
    uVar3 = 0;
  }
  return uVar3;
}


/* ==== FUN_0040df7a @ 0040df7a ==== */

undefined4 __cdecl FUN_0040df7a(uint param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  int local_24;
  int local_20;
  int local_8;
  
  FUN_0043b007(1);
  if (((DAT_0045eb34 == '\0') ||
      (((DAT_0044f794 == '\0' && (DAT_0044f798 == '\0')) || (DAT_0045f8c0 == DAT_0045f8cc)))) ||
     (DAT_0045f8a0 != 0)) {
    uVar1 = *(uint *)(*(int *)(DAT_0045fb88 + 0x24) + 0x30);
    uVar2 = *(uint *)(*(int *)(DAT_0045fb8c + 0x24) + 0x30);
    uVar4 = FUN_0040e655(param_1,1,param_2,0);
    if (uVar4 == 0) {
      uVar3 = 0;
    }
    else {
      if ((DAT_0045f8ac & 0xf) == 0) {
        local_20 = 1;
      }
      else {
        local_20 = (int)(CONCAT44((int)DAT_0045f8ac >> 0x1f,(int)DAT_0045f8ac >> 4) /
                        (longlong)(int)(DAT_0045f8ac & 0xf)) +
                   ((int)DAT_0045f8ac >> 4 & (uint)((DAT_0045f8ac & 1) == 0));
      }
      if ((DAT_0045f8bc & 0xf) == 0) {
        local_24 = 1;
      }
      else {
        local_24 = (int)(CONCAT44((int)DAT_0045f8bc >> 0x1f,(int)DAT_0045f8bc >> 4) /
                        (longlong)(int)(DAT_0045f8bc & 0xf)) +
                   ((int)DAT_0045f8bc >> 4 & (uint)((DAT_0045f8bc & 1) == 0));
      }
      local_8 = uVar4 * local_24;
      *DAT_0045f8c0 = *DAT_0045f8c0 + uVar4 * local_20;
      *(uint *)(*(int *)(DAT_0045fb88 + 0x24) + 0x30) =
           *(uint *)(*(int *)(DAT_0045fb88 + 0x24) + 0x30) | 0x80;
      if (DAT_0045f8c0 != DAT_0045f8cc) {
        if ((DAT_0045eaa4 != '\0') && (DAT_0045f8b0 != 0x1c)) {
          local_8 = local_8 * 3;
        }
        *DAT_0045f8cc = *DAT_0045f8cc + local_8;
        *(uint *)(*(int *)(DAT_0045fb8c + 0x24) + 0x30) =
             *(uint *)(*(int *)(DAT_0045fb8c + 0x24) + 0x30) | 0x80;
      }
      FUN_0040f21d(uVar1,uVar2);
      FUN_0043b926(0);
      DAT_0045ebc4 = 0;
      DAT_0045ea60 = 1;
      if (DAT_0045ea10 != '\0') {
        FUN_0041e1e8(param_1,uVar4);
      }
      DAT_0045f920 = 1;
      uVar3 = 1;
    }
  }
  else {
    FUN_00413085((uint *)s_Directive_not_allowed_in_P_memor_004533b8);
    uVar3 = 0;
  }
  return uVar3;
}


/* ==== FUN_0040e1a6 @ 0040e1a6 ==== */

undefined4 FUN_0040e1a6(void)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  FUN_0043b007(1);
  if (((DAT_0045eb34 == '\0') || (DAT_0044f790 == '\0')) || (DAT_0045f8a0 != 0)) {
    uVar1 = *(uint *)(*(int *)(DAT_0045fb88 + 0x24) + 0x30);
    uVar2 = *(uint *)(*(int *)(DAT_0045fb8c + 0x24) + 0x30);
    DAT_0045eb3c = 1;
    uVar4 = FUN_0040e655(0x400,0,0,1);
    DAT_0045eb3c = 0;
    if (uVar4 == 0) {
      uVar3 = 0;
    }
    else {
      FUN_0040f21d(uVar1,uVar2);
      DAT_0045ebc4 = 0;
      DAT_0045f920 = 1;
      uVar3 = 1;
    }
  }
  else {
    FUN_00413085((uint *)s_Directive_not_allowed_in_P_memor_00453400);
    uVar3 = 0;
  }
  return uVar3;
}


/* ==== FUN_0040e25f @ 0040e25f ==== */

undefined4 __cdecl FUN_0040e25f(int param_1)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  char *pcVar5;
  int local_1c;
  uint local_18;
  int local_c;
  
  FUN_0043b007(1);
  if (((DAT_0045eb34 == '\0') || (DAT_0044f790 == '\0')) || (DAT_0045f8a0 != 0)) {
    if (__mb_cur_max < 2) {
      local_18 = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 1;
    }
    else {
      local_18 = _isctype((int)*DAT_0045f860,1);
    }
    if (local_18 == 0) {
      local_1c = (int)*DAT_0045f860;
    }
    else {
      local_1c = tolower((int)*DAT_0045f860);
    }
    pcVar5 = DAT_0045f860 + 1;
    if (local_1c == 0x6d) {
      local_c = 0x400;
    }
    else {
      if (local_1c != 0x72) {
        DAT_0045f860 = pcVar5;
        FUN_00413085((uint *)s_Invalid_buffer_type_00453480);
        return 0;
      }
      local_c = 0x800;
    }
    DAT_0045f860 = DAT_0045f860 + 2;
    if (*pcVar5 == ',') {
      uVar1 = *(uint *)(*(int *)(DAT_0045fb88 + 0x24) + 0x30);
      uVar2 = *(uint *)(*(int *)(DAT_0045fb8c + 0x24) + 0x30);
      DAT_0045eb3c = 1;
      uVar4 = FUN_0040e655(local_c,0,param_1,0);
      DAT_0045eb3c = 0;
      if (uVar4 == 0) {
        uVar3 = 0;
      }
      else {
        FUN_0040f21d(uVar1,uVar2);
        DAT_0045ebc4 = 0;
        DAT_0045f920 = 1;
        uVar3 = 1;
      }
    }
    else {
      FUN_00413085((uint *)s_Syntax_error___expected_comma_00453494);
      uVar3 = 0;
    }
  }
  else {
    FUN_00413085((uint *)s_Directive_not_allowed_in_P_memor_00453440);
    uVar3 = 0;
  }
  return uVar3;
}


/* ==== FUN_0040e3f6 @ 0040e3f6 ==== */

undefined4 FUN_0040e3f6(void)

{
  undefined4 uVar1;
  char *pcVar2;
  uint uVar3;
  int local_10;
  uint local_c;
  int local_8;
  
  FUN_0043b007(1);
  if (((DAT_0045eb34 == '\0') ||
      (((DAT_0044f794 == '\0' && (DAT_0044f798 == '\0')) || (DAT_0045f8c0 == DAT_0045f8cc)))) ||
     (DAT_0045f8a0 != 0)) {
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
    pcVar2 = DAT_0045f860 + 1;
    if (local_10 == 0x6d) {
      local_8 = 0x400;
    }
    else {
      if (local_10 != 0x72) {
        DAT_0045f860 = pcVar2;
        FUN_00413085((uint *)s_Invalid_buffer_type_004534fc);
        return 0;
      }
      local_8 = 0x800;
    }
    DAT_0045f860 = DAT_0045f860 + 2;
    if (*pcVar2 == ',') {
      DAT_0045ebdc = *(undefined4 *)(*(int *)(DAT_0045fb88 + 0x24) + 0x30);
      DAT_0045ebe0 = *(undefined4 *)(*(int *)(DAT_0045fb8c + 0x24) + 0x30);
      uVar3 = FUN_0040e655(local_8,0,6,0);
      if (uVar3 == 0) {
        uVar1 = 0;
      }
      else {
        DAT_0045f920 = 1;
        uVar1 = 1;
      }
    }
    else {
      FUN_00413085((uint *)s_Syntax_error___expected_comma_00453510);
      uVar1 = 0;
    }
  }
  else {
    FUN_00413085((uint *)s_Directive_not_allowed_in_P_memor_004534b4);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_0040e572 @ 0040e572 ==== */

bool FUN_0040e572(void)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  uint uVar4;
  bool bVar5;
  
  uVar4 = DAT_0045ebcc;
  bVar5 = DAT_0045ebc4 == 0;
  if (bVar5) {
    DAT_0045f860 = 0;
    FUN_00413085((uint *)s_ENDBUF_without_associated_BUFFER_00453530);
  }
  uVar1 = *DAT_0045f8c0;
  iVar2 = *DAT_0045f8cc;
  bVar3 = DAT_0045ebc4 < uVar1;
  if (bVar3) {
    DAT_0045f860 = 0;
    FUN_00413085((uint *)s_Data_allocation_exceeds_buffer_s_0045355c);
  }
  FUN_0040ea5e(uVar1,DAT_0045ebc4,iVar2,DAT_0045ebc8,0x2000,DAT_0045ebdc,DAT_0045ebe0);
  FUN_0043b926(0);
  if (DAT_0045ea10 != '\0') {
    FUN_0041e1e8(uVar4,DAT_0045ebd0);
  }
  DAT_0045ebc4 = 0;
  return !bVar3 && !bVar5;
}


/* ==== FUN_0040e655 @ 0040e655 ==== */

uint __cdecl FUN_0040e655(int param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  undefined4 in_stack_00000010;
  int local_10;
  uint local_8;
  
  piVar1 = FUN_00413e70();
  if (piVar1 == (int *)0x0) {
    local_8 = 0;
  }
  else if ((piVar1[6] & 0x8000000U) == 0) {
    local_8 = piVar1[2];
    FUN_004167ef(piVar1);
    iVar2 = FUN_0040e749(param_1,local_8,param_3,in_stack_00000010);
    if (iVar2 == 0) {
      local_8 = 0;
    }
    if (param_2 != 0) {
      FUN_0043797a();
    }
    if ((((DAT_0045eadc != '\0') && (DAT_0045ea98 == '\0')) && (DAT_0045ea70 == '\0')) &&
       ((DAT_0045eacc == '\0' && (DAT_0045f8a0 == 0)))) {
      if (DAT_0045eb24 == '\0') {
        local_10 = DAT_0045eb78;
      }
      else {
        local_10 = DAT_0044f7e8;
      }
      FUN_0042433e(local_10);
    }
  }
  else {
    FUN_00413085((uint *)s_Expression_contains_forward_refe_00453580);
    FUN_004167ef(piVar1);
    local_8 = 0;
  }
  return local_8;
}


