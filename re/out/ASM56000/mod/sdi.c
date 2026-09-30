/* sdi: 11 functions from ASM56000 */

/* ==== FUN_00433cb0 @ 00433cb0 ==== */

char * __cdecl FUN_00433cb0(char *param_1)

{
  int iVar1;
  char *local_18;
  uint local_14;
  uint local_10;
  char *local_8;
  
  if ((((DAT_0045eb34 == '\0') || (DAT_0045ebc4 != 0)) || (DAT_0045ea70 != '\0')) ||
     ((DAT_0044f790 != '\0' && ((DAT_0044f794 == '\0' || (DAT_0044f798 == '\0')))))) {
    local_18 = (char *)0x0;
  }
  else {
    DAT_0045eb38 = 0;
    if (__mb_cur_max < 2) {
      local_10 = *(ushort *)(_pctype + *param_1 * 2) & 0x103;
    }
    else {
      local_10 = _isctype((int)*param_1,0x103);
    }
    if (((local_10 == 0) && (*param_1 != DAT_0044f830)) && (*param_1 != '#')) {
      local_18 = (char *)0x0;
    }
    else if ((((DAT_0045f8fc == 2) && (iVar1 = *(int *)(PTR_DAT_0044f97c + 0x6c), iVar1 != 0)) &&
             (*(int *)(iVar1 + 0x1c) != 0)) &&
            ((*(uint *)(*(int *)(iVar1 + 0x1c) + 0x14 + *(int *)(iVar1 + 4) * 0x1c) & 0x4000) != 0))
    {
      local_18 = (char *)0x0;
    }
    else {
      if (*param_1 == '#') {
        param_1 = param_1 + 1;
      }
      if (*param_1 == DAT_0044f830) {
        DAT_0045eb38 = 1;
      }
      for (local_8 = param_1; *local_8 != '\0'; local_8 = local_8 + 1) {
        if (__mb_cur_max < 2) {
          local_14 = *(ushort *)(_pctype + *local_8 * 2) & 0x107;
        }
        else {
          local_14 = _isctype((int)*local_8,0x107);
        }
        if ((local_14 == 0) && (*local_8 != DAT_0044f830)) break;
      }
      local_18 = param_1;
      if ((*local_8 != '\0') && (*local_8 != ',')) {
        local_18 = (char *)0x0;
      }
    }
  }
  return local_18;
}


/* ==== FUN_00433e78 @ 00433e78 ==== */

void __cdecl FUN_00433e78(int param_1)

{
  int *piVar1;
  int *local_8;
  
  if (DAT_0045eb34 != '\0') {
    for (local_8 = *(int **)(PTR_DAT_0044f97c + 0x68);
        (local_8 != (int *)0x0 && (param_1 != *local_8)); local_8 = (int *)local_8[8]) {
    }
    if (local_8 == (int *)0x0) {
      if (DAT_0045f8fc == 2) {
        FUN_00412fa0((uint *)s_SDI_list_sequence_failure_00458994);
      }
      piVar1 = (int *)FUN_00439857(0x24);
      *piVar1 = param_1;
      piVar1[4] = 0;
      piVar1[3] = 0;
      piVar1[2] = 0;
      piVar1[1] = 0;
      piVar1[5] = 0;
      piVar1[6] = 0;
      piVar1[7] = 0;
      piVar1[8] = *(int *)(PTR_DAT_0044f97c + 0x68);
      *(int **)(PTR_DAT_0044f97c + 0x68) = piVar1;
      *(int **)(PTR_DAT_0044f97c + 0x6c) = piVar1;
    }
    else {
      *(int **)(PTR_DAT_0044f97c + 0x6c) = local_8;
    }
  }
  return;
}


/* ==== FUN_00433f67 @ 00433f67 ==== */

void __cdecl FUN_00433f67(int param_1)

{
  undefined4 *puVar1;
  
  if (DAT_0045eb34 != '\0') {
    if (DAT_0045f8fc == 1) {
      if (*(int *)(param_1 + 0x70) == 0) {
        puVar1 = (undefined4 *)FUN_00439857(0xc);
        *puVar1 = 0;
        puVar1[1] = 0;
        puVar1[2] = 0;
        *(undefined4 **)(param_1 + 0x74) = puVar1;
        *(undefined4 **)(param_1 + 0x70) = puVar1;
      }
      puVar1 = (undefined4 *)FUN_00439857(0xc);
      *puVar1 = *(undefined4 *)(param_1 + 0x6c);
      puVar1[1] = 0;
      puVar1[2] = 0;
      *(undefined4 **)(*(int *)(param_1 + 0x74) + 8) = puVar1;
      *(undefined4 **)(param_1 + 0x74) = puVar1;
    }
    else {
      *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(*(int *)(param_1 + 0x74) + 8);
    }
  }
  return;
}


/* ==== FUN_00434023 @ 00434023 ==== */

void __cdecl FUN_00434023(uint *param_1,int param_2,int param_3,int param_4)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int local_18;
  undefined4 *local_14;
  undefined4 *local_c;
  undefined4 *local_8;
  
  local_c = (undefined4 *)0x0;
  piVar1 = (int *)FUN_00439857(0x28);
  piVar1[1] = *DAT_0045f8c0;
  piVar1[2] = param_2;
  piVar1[3] = param_3;
  piVar1[4] = param_4;
  piVar1[5] = -1;
  piVar1[6] = 0;
  if (param_1 == (uint *)0x0) {
    *piVar1 = 0;
    piVar1[4] = piVar1[4] | 0x2000;
    piVar1[7] = 0;
    piVar1[8] = 0;
    piVar1[9] = *(int *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 0x18);
    *(int **)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 0x18) = piVar1;
    *(int *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 4) =
         *(int *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 4) + 1;
  }
  else {
    if ((char)*param_1 == '<') {
      param_1 = (uint *)((int)param_1 + 1);
      piVar1[4] = piVar1[4] | 0x8000;
    }
    uVar2 = strlen((char *)param_1);
    iVar3 = FUN_00439857(uVar2 + 1);
    *piVar1 = iVar3;
    strcpy((char *)*piVar1,(char *)param_1);
    piVar1[4] = piVar1[4] | -(uint)(DAT_0045eb28 != '\0') & 0x1000;
    piVar1[4] = piVar1[4] | -(uint)(DAT_0044f794 != '\0') & 0x20000;
    if (*(char *)*piVar1 == DAT_0044f830) {
      if ((DAT_0045fb6c == 0) || (DAT_0045eb10 != '\0')) {
        piVar1[5] = DAT_0045eb68;
        if (DAT_0045fc40 == 0) {
          local_18 = DAT_0045fc44;
        }
        else {
          local_18 = DAT_0045fc40;
        }
        piVar1[6] = local_18;
      }
      else {
        piVar1[6] = DAT_0045fc4c;
      }
    }
    piVar1[7] = (int)PTR_DAT_0044f978;
    if ((DAT_0044f7ac != '\0') && (DAT_0045fb84 != (undefined4 *)0x0)) {
      local_c = (undefined4 *)FUN_00439857(8);
      *local_c = *DAT_0045fb84;
      local_c[1] = 0;
      local_8 = local_c;
      for (local_14 = (undefined4 *)DAT_0045fb84[1]; local_14 != (undefined4 *)0x0;
          local_14 = (undefined4 *)local_14[1]) {
        iVar3 = FUN_00439857(8);
        local_8[1] = iVar3;
        local_8 = (undefined4 *)local_8[1];
        *local_8 = *local_14;
        local_8[1] = 0;
      }
    }
    piVar1[8] = (int)local_c;
    piVar1[9] = *(int *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 0x18);
    *(int **)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 0x18) = piVar1;
    *(int *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 4) =
         *(int *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 4) + 1;
    *(int *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 8) =
         *(int *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 8) + 1;
    if (DAT_0045f8c0 != DAT_0045f8cc) {
      *(undefined4 *)(*(int *)(PTR_DAT_0044f97c + 0x74) + 4) =
           *(undefined4 *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 4);
    }
  }
  return;
}


/* ==== FUN_004342fb @ 004342fb ==== */

undefined1 FUN_004342fb(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined1 uVar4;
  
  iVar1 = *(int *)(PTR_DAT_0044f97c + 0x6c);
  if (iVar1 == 0) {
    uVar4 = 2;
  }
  else {
    iVar3 = *(int *)(iVar1 + 0x1c) + *(int *)(iVar1 + 4) * 0x1c;
    *(int *)(iVar1 + 4) = *(int *)(iVar1 + 4) + 1;
    uVar2 = (uint)((*(uint *)(iVar3 + 0x14) & 0x100) != 0);
    if ((*(uint *)(iVar3 + 0x14) & 0x100) == 0) {
      uVar4 = (*(uint *)(iVar3 + 0x14) & 0x200) != 0;
    }
    else {
      uVar4 = 2;
    }
    *(int *)(iVar1 + 8) = *(int *)(iVar1 + 8) + 1;
    if ((*(uint *)(iVar3 + 0x14) & 0x4000) != 0) {
      FUN_004133a9((uint *)s_SET_symbol_used_as_span_dependen_004589b0);
    }
    if (uVar2 != 0) {
      if ((*(uint *)(iVar3 + 0x14) & 0x8000) != 0) {
        FUN_004133a9((uint *)s_Instruction_operand_too_large_to_004589fc);
      }
      *(int *)(*(int *)(DAT_0045fb88 + 0x24) + 0x18) =
           *(int *)(*(int *)(DAT_0045fb88 + 0x24) + 0x18) + 1;
      if (DAT_0045f8c0 != DAT_0045f8cc) {
        *(int *)(*(int *)(DAT_0045fb8c + 0x24) + 0x18) =
             *(int *)(*(int *)(DAT_0045fb8c + 0x24) + 0x18) + 1;
      }
    }
    *(uint *)(iVar1 + 0x10) = *(int *)(iVar1 + 0x10) + uVar2;
  }
  return uVar4;
}


/* ==== FUN_00434430 @ 00434430 ==== */

void FUN_00434430(void)

{
  undefined *local_c;
  int local_8;
  
  for (local_c = PTR_DAT_0044f980; local_c != (undefined *)0x0;
      local_c = *(undefined **)(local_c + 0x8c)) {
    for (local_8 = *(int *)(local_c + 0x68); local_8 != 0; local_8 = *(int *)(local_8 + 0x20)) {
      if (*(int *)(local_8 + 4) != 0) {
        FUN_0043449c(local_8);
        FUN_004346c2(local_8);
      }
    }
  }
  FUN_00438c80();
  return;
}


/* ==== FUN_0043449c @ 0043449c ==== */

void __cdecl FUN_0043449c(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  int *local_14;
  int *local_c;
  
  iVar2 = FUN_00439857((*(int *)(param_1 + 4) + 1) * 0x1c);
  *(int *)(param_1 + 0x1c) = iVar2;
  local_14 = *(int **)(param_1 + 0x18);
  for (local_c = (int *)(*(int *)(param_1 + 0x1c) + -0x1c + *(int *)(param_1 + 4) * 0x1c);
      (local_14 != (int *)0x0 && (*(int **)(param_1 + 0x1c) <= local_c)); local_c = local_c + -7) {
    *local_c = local_14[1];
    local_c[6] = 0;
    local_c[2] = 0;
    local_c[1] = 0;
    local_c[3] = local_14[2];
    local_c[4] = local_14[3];
    local_c[5] = local_14[4];
    DAT_0045ea50 = 1;
    puVar3 = FUN_004349d5(local_14);
    DAT_0045ea50 = 0;
    if (puVar3 == (undefined4 *)0x0) {
      if (*local_14 != 0) {
        local_c[5] = local_c[5] | 0x10000;
        FUN_004398b5((undefined *)*local_14);
        *local_14 = 0;
      }
      piVar1 = (int *)local_14[9];
      FUN_004398b5((undefined *)local_14);
      local_14 = piVar1;
    }
    else if (((puVar3[6] & 0x1000) == 0) && ((local_c[5] & 0x20000U) == 0)) {
      local_c[1] = puVar3[4];
      local_c[2] = local_c[1] - *local_c;
      if (*local_14 != 0) {
        FUN_004398b5((undefined *)*local_14);
        *local_14 = 0;
      }
      piVar1 = (int *)local_14[9];
      FUN_004398b5((undefined *)local_14);
      local_14 = piVar1;
    }
    else {
      local_c[5] = local_c[5] | 0x10000;
      if (*local_14 != 0) {
        FUN_004398b5((undefined *)*local_14);
        *local_14 = 0;
      }
      piVar1 = (int *)local_14[9];
      FUN_004398b5((undefined *)local_14);
      local_14 = piVar1;
    }
  }
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}


/* ==== FUN_004346c2 @ 004346c2 ==== */

void __cdecl FUN_004346c2(int param_1)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  uint *puVar6;
  int local_2c;
  int local_18;
  int local_14;
  
  bVar1 = false;
  while (!bVar1) {
    bVar1 = true;
    for (local_14 = 0; local_14 < *(int *)(param_1 + 0xc); local_14 = local_14 + 1) {
      puVar6 = (uint *)(*(int *)(param_1 + 0x1c) + local_14 * 0x1c);
      if ((((puVar6[5] & 0x10000) == 0) && ((puVar6[5] & 0x2000) == 0)) &&
         ((puVar6[5] & 0x100) == 0)) {
        iVar3 = FUN_00409618(puVar6[1],puVar6[3]);
        iVar4 = FUN_00409618(puVar6[2],puVar6[3]);
        if (puVar6[4] == 0) {
          local_2c = 0;
        }
        else {
          local_2c = FUN_00409618(puVar6[2],puVar6[4]);
        }
        bVar2 = false;
        if (((puVar6[5] & 2) == 0) || (iVar3 == 0)) {
          if (((puVar6[5] & 2) == 0) && (((puVar6[5] & 1) != 0 && (iVar4 != 0)))) {
            bVar2 = true;
          }
          else if (((puVar6[5] & 3) != 0) && (local_2c != 0)) {
            bVar2 = true;
          }
        }
        else {
          bVar2 = true;
        }
        if (((puVar6[5] & 0x4000) != 0) || (!bVar2)) {
          bVar1 = false;
          puVar6[5] = puVar6[5] | 0x100;
          puVar6[5] = puVar6[5] & 0xfffffdff;
          for (local_18 = 0; local_18 < *(int *)(param_1 + 4); local_18 = local_18 + 1) {
            if ((local_18 != local_14) &&
               (puVar5 = (uint *)(*(int *)(param_1 + 0x1c) + local_18 * 0x1c),
               (puVar5[5] & 0x10000) == 0)) {
              if ((*puVar6 < *puVar5) || (puVar5[1] <= *puVar6)) {
                if ((puVar5[1] <= *puVar6) && (*puVar6 < *puVar5)) {
                  puVar5[2] = puVar5[2] - 1;
                }
              }
              else {
                puVar5[2] = puVar5[2] + 1;
              }
            }
          }
        }
        if (((((puVar6[5] & 3) != 0) && ((puVar6[5] & 0x100) == 0)) && (iVar3 == 0)) &&
           (local_2c != 0)) {
          puVar6[5] = puVar6[5] | 0x200;
        }
      }
    }
  }
  iVar3 = *(int *)(param_1 + 0x1c);
  if ((*(uint *)(iVar3 + 0x14) & 0x2000) == 0) {
    *(uint *)(iVar3 + 0x18) = (uint)((*(uint *)(iVar3 + 0x14) & 0x100) != 0);
  }
  for (local_14 = 1; local_14 < *(int *)(param_1 + 0xc); local_14 = local_14 + 1) {
    iVar3 = *(int *)(param_1 + 0x1c) + local_14 * 0x1c;
    if ((*(uint *)(iVar3 + 0x14) & 0x2000) == 0) {
      *(uint *)(iVar3 + 0x18) =
           *(int *)(*(int *)(param_1 + 0x1c) + 0x18 + (local_14 + -1) * 0x1c) +
           (uint)((*(uint *)(iVar3 + 0x14) & 0x100) != 0);
    }
  }
  return;
}


/* ==== FUN_004349d5 @ 004349d5 ==== */

undefined4 * __cdecl FUN_004349d5(undefined4 *param_1)

{
  uint uVar1;
  int *local_214;
  undefined4 *local_210;
  char *local_20c;
  char local_208 [516];
  
  local_20c = (char *)*param_1;
  if (local_20c == (char *)0x0) {
    local_210 = (undefined4 *)0x0;
  }
  else {
    if (DAT_0045eaa0 != '\0') {
      strcpy(local_208,local_20c);
      FUN_0043b836(local_208);
      local_20c = local_208;
    }
    PTR_DAT_0044f978 = (undefined *)param_1[7];
    DAT_0045eb28 = (param_1[4] & 0x1000) != 0;
    if (param_1[8] == 0) {
      DAT_0045fb84 = 0;
    }
    else {
      DAT_0045fb84 = param_1[8];
    }
    DAT_0044f7ac = param_1[8] != 0;
    if (*local_20c == DAT_0044f830) {
      DAT_0045fc34 = 0;
      if ((int)param_1[5] < 0) {
        DAT_0045fc34 = *(int *)(param_1[6] + 4);
      }
      else if (param_1[6] == 0) {
        for (local_214 = DAT_0045fc3c; local_214 != (int *)0x0; local_214 = (int *)local_214[2]) {
          if (*local_214 == param_1[5]) {
            DAT_0045fc34 = local_214[1];
            break;
          }
        }
      }
      else if (*(int *)param_1[6] == param_1[5]) {
        DAT_0045fc34 = *(int *)(param_1[6] + 4);
      }
      else if (*(int *)(param_1[6] + 8) != 0) {
        DAT_0045fc34 = *(int *)(*(int *)(param_1[6] + 8) + 4);
      }
      local_210 = FUN_00438713(local_20c + 1,2,1);
    }
    else {
      uVar1 = FUN_00439b65(local_20c);
      DAT_0045fc34 = *(int *)(&DAT_0045fcc0 + uVar1 * 4);
      local_210 = FUN_00438713(local_20c,2,0);
    }
    if ((local_210 != (undefined4 *)0x0) && ((local_210[6] & 0x10) != 0)) {
      param_1[4] = param_1[4] | 0x4000;
    }
  }
  return local_210;
}


/* ==== FUN_00434be7 @ 00434be7 ==== */

void FUN_00434be7(void)

{
  uint uVar1;
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  undefined4 in_stack_0000000c;
  undefined4 in_stack_00000010;
  int in_stack_00000014;
  int in_stack_00000018;
  char local_210 [512];
  char *local_10;
  uint local_c;
  int local_8;
  
  local_8 = *(int *)(PTR_DAT_0044f97c + 0x6c);
  sprintf(local_210,s___0_lX__s__00458a3c,6,*(undefined4 *)(in_stack_00000018 + 4),
          *(undefined4 *)(in_stack_00000018 + 0x44));
  local_c = strlen(local_210);
  sprintf(local_210,s__SDI__s___04lX___0_lX___0_lX__d__00458a48,in_stack_00000004,in_stack_00000008,
          6,in_stack_0000000c,6,in_stack_00000010,local_c,6,*(undefined4 *)(in_stack_00000018 + 4),
          *(undefined4 *)(in_stack_00000018 + 0x44),*(undefined4 *)(in_stack_00000014 + 0x40));
  uVar1 = strlen(local_210);
  local_10 = (char *)FUN_00439857(uVar1 + 1);
  strcpy(local_10,local_210);
  FUN_004398b5(*(undefined **)(in_stack_00000014 + 0x40));
  *(undefined4 *)(in_stack_00000014 + 0x40) = 0;
  FUN_004398b5(*(undefined **)(in_stack_00000014 + 0x44));
  *(undefined4 *)(in_stack_00000014 + 0x44) = 0;
  FUN_004398b5(*(undefined **)(in_stack_00000018 + 0x40));
  *(undefined4 *)(in_stack_00000018 + 0x40) = 0;
  FUN_004398b5(*(undefined **)(in_stack_00000018 + 0x44));
  *(undefined4 *)(in_stack_00000018 + 0x44) = 0;
  *(char **)(in_stack_00000014 + 0x40) = local_10;
  *(undefined4 *)(in_stack_00000014 + 0x44) = 0;
  if (local_8 != 0) {
    *(int *)(local_8 + 4) = *(int *)(local_8 + 4) + 1;
    *(int *)(local_8 + 8) = *(int *)(local_8 + 8) + 1;
    FUN_004247b1(DAT_0045fbb4);
  }
  DAT_0045fca4 = DAT_0045fca4 + 1;
  return;
}


/* ==== FUN_00434d60 @ 00434d60 ==== */

void FUN_00434d60(void)

{
  uint uVar1;
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  undefined4 in_stack_0000000c;
  undefined4 in_stack_00000010;
  int in_stack_00000014;
  int in_stack_00000018;
  int in_stack_0000001c;
  char local_214 [512];
  char *local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_10 = *(int *)(PTR_DAT_0044f97c + 0x6c);
  sprintf(local_214,s___0_lX__s__00458a78,6,*(undefined4 *)(in_stack_0000001c + 4),
          *(undefined4 *)(in_stack_0000001c + 0x44));
  local_8 = strlen(local_214);
  sprintf(local_214,&DAT_00458a84,*(undefined4 *)(in_stack_00000018 + 0x40));
  uVar1 = strlen(local_214);
  local_c = local_8 + uVar1;
  sprintf(local_214,s__SDI2__s___04lX___0_lX___0_lX__d_00458a88,in_stack_00000004,in_stack_00000008,
          6,in_stack_0000000c,6,in_stack_00000010,local_8,local_c,6,
          *(undefined4 *)(in_stack_0000001c + 4),*(undefined4 *)(in_stack_0000001c + 0x44),
          *(undefined4 *)(in_stack_00000018 + 0x40),*(undefined4 *)(in_stack_00000014 + 0x40));
  uVar1 = strlen(local_214);
  local_14 = (char *)FUN_00439857(uVar1 + 1);
  strcpy(local_14,local_214);
  FUN_004398b5(*(undefined **)(in_stack_00000014 + 0x40));
  *(undefined4 *)(in_stack_00000014 + 0x40) = 0;
  FUN_004398b5(*(undefined **)(in_stack_00000014 + 0x44));
  *(undefined4 *)(in_stack_00000014 + 0x44) = 0;
  FUN_004398b5(*(undefined **)(in_stack_00000018 + 0x40));
  *(undefined4 *)(in_stack_00000018 + 0x40) = 0;
  FUN_004398b5(*(undefined **)(in_stack_00000018 + 0x44));
  *(undefined4 *)(in_stack_00000018 + 0x44) = 0;
  FUN_004398b5(*(undefined **)(in_stack_0000001c + 0x40));
  *(undefined4 *)(in_stack_0000001c + 0x40) = 0;
  FUN_004398b5(*(undefined **)(in_stack_0000001c + 0x44));
  *(undefined4 *)(in_stack_0000001c + 0x44) = 0;
  *(char **)(in_stack_00000014 + 0x40) = local_14;
  *(undefined4 *)(in_stack_00000014 + 0x44) = 0;
  if (local_10 != 0) {
    *(int *)(local_10 + 4) = *(int *)(local_10 + 4) + 1;
    *(int *)(local_10 + 8) = *(int *)(local_10 + 8) + 1;
    FUN_004247b1(DAT_0045fbb4);
  }
  DAT_0045fca4 = DAT_0045fca4 + 1;
  return;
}


