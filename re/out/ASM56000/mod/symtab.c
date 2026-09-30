/* symtab: 15 functions from ASM56000 */

/* ==== FUN_00437418 @ 00437418 ==== */

undefined4 __cdecl FUN_00437418(uint *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 *local_20c;
  uint local_208 [129];
  
  if (DAT_0045eaa0 != '\0') {
    strcpy((char *)local_208,(char *)param_1);
    FUN_0043b836((char *)local_208);
    param_1 = local_208;
  }
  uVar1 = FUN_00439b65((char *)param_1);
  local_20c = *(undefined4 **)(&DAT_0045fcc0 + uVar1 * 4);
  do {
    if (local_20c == (undefined4 *)0x0) {
      if (DAT_0045f8fc == 2) {
        FUN_004131f9((uint *)s_Symbol_undefined_on_pass_2_0045937c,(char *)param_1);
      }
      return 1;
    }
    if (((char)*param_1 == *(char *)*local_20c) &&
       (iVar2 = strcmp((char *)param_1,(char *)*local_20c), iVar2 == 0)) {
      if ((undefined *)local_20c[0x10] == PTR_DAT_0044f978) {
        if (((local_20c[6] & (-(uint)(DAT_0045ea88 != '\0') & 0xffffffc0) + 0x80) == 0) &&
           ((*(uint *)(PTR_DAT_0044f978 + 0xc) & 0x40) == 0)) {
          FUN_004131f9((uint *)s_Symbol_defined_in_current_sectio_004592f4,(char *)param_1);
          return 0;
        }
        if ((DAT_0044f790 != '\0') && ((local_20c[6] & 0x10) != 0)) {
          FUN_004131f9((uint *)s_SET_symbol_names_cannot_be_used_w_0045932c,(char *)param_1);
          return 0;
        }
        if (((DAT_0045f8fc == 2) && (DAT_0045ea3c != '\0')) && (DAT_0045ea70 == '\0')) {
          FUN_004388eb((int)local_20c,2);
        }
        return 1;
      }
      if ((DAT_0045ea88 != '\0') && ((local_20c[6] & 0x40) != 0)) {
        FUN_004131f9((uint *)s_Symbol_already_defined_as_global_00459358,(char *)param_1);
        return 0;
      }
    }
    local_20c = (undefined4 *)local_20c[0x17];
  } while( true );
}


/* ==== FUN_004375e6 @ 004375e6 ==== */

void FUN_004375e6(void)

{
  undefined4 *puVar1;
  undefined4 *local_10;
  undefined *local_c;
  
  for (local_c = PTR_DAT_0044f980; local_c != (undefined *)0x0;
      local_c = *(undefined **)(local_c + 0x8c)) {
    local_10 = *(undefined4 **)(local_c + 0x7c);
    while (local_10 != (undefined4 *)0x0) {
      puVar1 = (undefined4 *)local_10[1];
      FUN_004398b5((undefined *)*local_10);
      *local_10 = 0;
      FUN_004398b5((undefined *)local_10);
      local_10 = puVar1;
    }
    *(undefined4 *)(local_c + 0x7c) = 0;
    local_10 = *(undefined4 **)(local_c + 0x78);
    while (local_10 != (undefined4 *)0x0) {
      puVar1 = (undefined4 *)local_10[1];
      FUN_004398b5((undefined *)*local_10);
      *local_10 = 0;
      FUN_004398b5((undefined *)local_10);
      local_10 = puVar1;
    }
    *(undefined4 *)(local_c + 0x78) = 0;
    local_10 = *(undefined4 **)(local_c + 0x80);
    while (local_10 != (undefined4 *)0x0) {
      puVar1 = (undefined4 *)local_10[1];
      FUN_004398b5((undefined *)*local_10);
      *local_10 = 0;
      FUN_004398b5((undefined *)local_10);
      local_10 = puVar1;
    }
    *(undefined4 *)(local_c + 0x80) = 0;
  }
  return;
}


/* ==== FUN_00437710 @ 00437710 ==== */

void __cdecl FUN_00437710(uint *param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  int local_10;
  int local_c;
  
  uVar1 = FUN_00439b65((char *)param_1);
  local_10 = *(int *)(&DAT_0045da48 + uVar1 * 4);
  if (local_10 == 0) {
    puVar2 = FUN_0043da70();
    piVar3 = (int *)FUN_00439857(0xc);
    memset(piVar3,0,0xc);
    uVar4 = strlen((char *)param_1);
    iVar5 = FUN_00439857(uVar4 + 1);
    *piVar3 = iVar5;
    strcpy((char *)*piVar3,(char *)param_1);
    piVar3[1] = (int)puVar2;
    iVar5 = FUN_0043cd73();
    (*(code *)puVar2[3])(puVar2,iVar5);
    *(int **)(&DAT_0045da48 + uVar1 * 4) = piVar3;
  }
  else {
    for (; local_10 != 0; local_10 = *(int *)(local_10 + 8)) {
      local_c = local_10;
    }
    iVar5 = FUN_00439857(0xc);
    *(int *)(local_c + 8) = iVar5;
    memset(*(void **)(local_c + 8),0,0xc);
    piVar3 = *(int **)(local_c + 8);
    uVar1 = strlen((char *)param_1);
    iVar5 = FUN_00439857(uVar1 + 1);
    *piVar3 = iVar5;
    strcpy((char *)*piVar3,(char *)param_1);
    piVar3[2] = 0;
  }
  return;
}


/* ==== FUN_00437837 @ 00437837 ==== */

undefined4 FUN_00437837(void)

{
  int *piVar1;
  int local_10;
  int *local_8;
  
  for (local_10 = 0; local_10 < 0x3f1; local_10 = local_10 + 1) {
    local_8 = *(int **)(&DAT_0045da48 + local_10 * 4);
    while (local_8 != (int *)0x0) {
      piVar1 = (int *)local_8[2];
      if (*local_8 != 0) {
        FUN_004398b5((undefined *)*local_8);
      }
      if (local_8[1] != 0) {
        (**(code **)(local_8[1] + 0x1c))(local_8[1]);
        FUN_004398b5((undefined *)local_8[1]);
        local_8[1] = 0;
      }
      FUN_004398b5((undefined *)local_8);
      local_8 = piVar1;
    }
  }
  return 1;
}


/* ==== FUN_004378e5 @ 004378e5 ==== */

undefined4 __cdecl FUN_004378e5(char *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 *local_c;
  
  uVar1 = FUN_00439b65(param_1);
  local_c = *(undefined4 **)(&DAT_0045da48 + uVar1 * 4);
  if (local_c != (undefined4 *)0x0) {
    for (; local_c != (undefined4 *)0x0; local_c = (undefined4 *)local_c[2]) {
      iVar2 = strcmp((char *)*local_c,param_1);
      if (iVar2 == 0) {
        return 1;
      }
    }
  }
  return 0;
}


/* ==== FUN_0043794f @ 0043794f ==== */

undefined4 FUN_0043794f(void)

{
  int iVar1;
  
  iVar1 = FUN_004378e5(PTR_DAT_0044f810);
  if (iVar1 == 0) {
    FUN_00437710((uint *)PTR_DAT_0044f810);
  }
  return 1;
}


/* ==== FUN_0043797a @ 0043797a ==== */

bool FUN_0043797a(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_54;
  undefined4 local_50;
  uint local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  uint local_20;
  uint local_1c;
  undefined4 local_10;
  
  iVar1 = FUN_0043b659(PTR_DAT_0044f810);
  if (iVar1 == 1) {
    FUN_0043b926(0);
    local_60 = 0;
    local_64 = 0;
    local_5c = *DAT_0045f8c0;
    local_50 = 3;
    local_54 = 0x100;
    uVar3 = -(uint)(DAT_0045ebc4 != 0) & 0x2000;
    uVar2 = -(uint)(DAT_0045f8c0 != DAT_0045f8cc) & 0x4000;
    local_4c = -(uint)(DAT_0044f794 != '\0') & 0x1000 | uVar3 | uVar2;
    local_48 = DAT_0045f8a0;
    local_44 = DAT_0045f8a4;
    local_40 = DAT_0045f8a8;
    local_3c = DAT_0045f8ac;
    local_2c = 0;
    local_30 = 0;
    local_28 = *(undefined4 *)(PTR_DAT_0044f978 + 8);
    local_24 = *(undefined4 *)(PTR_DAT_0044f97c + 8);
    local_20 = -(uint)(uVar3 != 0) & DAT_0045ebc0;
    local_1c = -(uint)(uVar2 != 0) & DAT_0045ebe8;
    local_10 = *(undefined4 *)(DAT_0045fb8c + 0x1c);
    FUN_00437a9f((uint *)PTR_DAT_0044f810,(double *)&local_64);
  }
  return iVar1 == 1;
}


/* ==== FUN_00437a9f @ 00437a9f ==== */

undefined4 __cdecl FUN_00437a9f(uint *param_1,double *param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 *local_24;
  uint *local_20;
  uint local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  local_1c = *(uint *)(param_2 + 3) | *(uint *)(param_2 + 2);
  if (DAT_0045f8fc == 0) {
    if ((char)*param_1 == DAT_0044f830) {
      local_20 = (uint *)((int)param_1 + 1);
    }
    else {
      local_20 = param_1;
    }
    piVar1 = FUN_0043d23d((char *)local_20,*(undefined4 *)(PTR_DAT_0044f978 + 8));
    if (piVar1 != (int *)0x0) {
      FUN_0043d179(piVar1);
      iVar2 = FUN_0043cd80();
      if (iVar2 != 0) {
        FUN_0043ceb2(iVar2,0xf);
      }
    }
  }
  if (((local_1c & 0x10) == 0) || (DAT_0044f7c4 != '\0')) {
    local_18 = *(int *)((int)param_2 + 0x1c);
    local_14 = *(int *)(param_2 + 4);
    local_10 = *(int *)((int)param_2 + 0x24);
    local_c = *(int *)(param_2 + 5);
  }
  else {
    local_14 = 4;
    local_18 = 4;
    local_10 = 0;
    local_c = 0;
  }
  if ((char)*param_1 == DAT_0044f830) {
    local_1c = local_1c | 0x20;
  }
  else {
    if (((((PTR_DAT_0044f978 == &DAT_0044f878) || ((*(uint *)(PTR_DAT_0044f978 + 0xc) & 0x40) != 0))
         || (iVar2 = FUN_00436d85((char *)param_1), iVar2 != 0)) ||
        ((DAT_0045ea88 != '\0' && (iVar2 = FUN_00436e56((char *)param_1), iVar2 != 0)))) ||
       (((local_1c & 0x10) != 0 &&
        ((DAT_0045eb28 != '\0' || (iVar2 = FUN_00436def((char *)param_1), iVar2 != 0)))))) {
      local_1c = local_1c | 0x40;
    }
    else if ((DAT_0045ea88 == '\0') && (iVar2 = FUN_00436e56((char *)param_1), iVar2 != 0)) {
      local_1c = local_1c | 0x80;
    }
    iVar2 = strncmp((char *)param_1,PTR_DAT_0044f99c,3);
    if ((iVar2 == 0) || (iVar2 = strncmp((char *)param_1,PTR_DAT_0044f9a0,3), iVar2 == 0)) {
      local_1c = local_1c | 0x40000;
    }
    else {
      DAT_0045eb68 = DAT_0045eb68 + 1;
    }
  }
  if (((DAT_0045f8fc == 1) && (DAT_0045fb8c != 0)) && ((local_1c & 0x10) == 0)) {
    *(int *)(DAT_0045fb8c + 0x20) = *(int *)(DAT_0045fb8c + 0x20) + 1;
  }
  local_24 = FUN_00438441(param_1,1);
  if (local_24 != (undefined4 *)0x0) {
    if ((local_24[6] & 0x40) == 0) {
      if ((local_24[6] & 0x80) == 0) {
        if ((local_1c & 0xc0) != 0) {
          local_24 = (undefined4 *)0x0;
        }
      }
      else if ((local_1c & 0x80) == 0) {
        local_24 = (undefined4 *)0x0;
      }
    }
    else if (((local_1c & 0x40) == 0) &&
            (((local_1c & 0x10) == 0 || (iVar2 = FUN_00436def((char *)param_1), iVar2 == 0)))) {
      local_24 = (undefined4 *)0x0;
    }
  }
  if (local_24 == (undefined4 *)0x0) {
    if (DAT_0045f8fc == 2) {
      if ((((local_1c & 0x10) != 0) && (DAT_0045eb28 != '\0')) &&
         ((PTR_DAT_0044f978 != &DAT_0044f878 && (DAT_0044f790 != '\0')))) {
        FUN_004131f9((uint *)s_Symbol_undefined_on_pass_2_00459418,(char *)param_1);
      }
      uVar3 = 0;
    }
    else {
      if ((local_1c & 0x20) == 0) {
        DAT_0045eb64 = DAT_0045eb64 + 1;
        if ((local_1c & 0x40000) != 0) {
          DAT_0045eb70 = DAT_0045eb70 + 1;
        }
      }
      else {
        param_1 = (uint *)((int)param_1 + 1);
        if (DAT_0045fb6c == 0) {
          DAT_0045eb6c = DAT_0045eb6c + 1;
        }
      }
      piVar1 = (int *)FUN_00439857(0x60);
      uVar4 = strlen((char *)param_1);
      iVar2 = FUN_00439857(uVar4 + 1);
      *piVar1 = iVar2;
      strcpy((char *)*piVar1,(char *)param_1);
      if (DAT_0045eaa0 != '\0') {
        FUN_0043b836((char *)*piVar1);
      }
      if ((local_1c & 0x100) == 0) {
        piVar1[2] = *(int *)param_2;
        piVar1[3] = *(int *)((int)param_2 + 4);
      }
      else {
        piVar1[2] = *(int *)param_2;
        piVar1[3] = *(int *)((int)param_2 + 4);
        piVar1[4] = *(int *)(param_2 + 1);
      }
      if (*(int *)((int)param_2 + 0x14) == 6) {
        local_1c = local_1c | 0x800;
      }
      piVar1[6] = local_1c;
      piVar1[7] = local_18;
      piVar1[8] = local_14;
      piVar1[9] = local_10;
      piVar1[10] = local_c;
      piVar1[0xb] = *(int *)((int)param_2 + 0x44);
      piVar1[0xc] = *(int *)(param_2 + 9);
      piVar1[0xd] = *(int *)((int)param_2 + 0x54);
      piVar1[0xe] = 0;
      piVar1[0xf] = 0;
      if ((((local_1c & 0x10) == 0) && (*(int *)(PTR_DAT_0044f97c + 0x6c) != 0)) &&
         (DAT_0045f8a0 == 0)) {
        piVar1[0xe] = *(int *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 4);
        piVar1[0xf] = *(int *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 8);
      }
      piVar1[0x10] = (int)PTR_DAT_0044f978;
      piVar1[0x11] = (int)PTR_DAT_0044f97c;
      piVar1[0x12] = *(int *)(PTR_DAT_0044f97c + 0x6c);
      if ((((DAT_0045f8c0 == DAT_0045f8cc) && (*(int *)(PTR_DAT_0044f97c + 0x74) != 0)) &&
          (**(int **)(PTR_DAT_0044f97c + 0x74) != 0)) &&
         (*(int *)(*(int *)(PTR_DAT_0044f97c + 0x74) + 4) != 0)) {
        piVar1[0x13] = *(int *)(PTR_DAT_0044f97c + 0x74);
      }
      else {
        piVar1[0x13] = 0;
      }
      piVar1[0x14] = 0;
      piVar1[0x15] = 0;
      piVar1[0x16] = 0;
      piVar1[0x17] = 0;
      if (((local_1c & 0x20) == 0) && (((local_1c & 0x40000) == 0 || (DAT_0045ead0 == '\0')))) {
        DAT_0045fc40 = 0;
        DAT_0045fc38 = 0;
      }
      if (DAT_0045fc34 == 0) {
        if ((local_1c & 0x20) == 0) {
          uVar4 = FUN_00439b65((char *)*piVar1);
          *(int **)(&DAT_0045fcc0 + uVar4 * 4) = piVar1;
        }
        else if (DAT_0045fc38 == 0) {
          FUN_004382bb(piVar1);
        }
        else {
          piVar1[0x17] = DAT_0045fc38;
          *(int **)(DAT_0045fc38 + 0x5c) = piVar1;
        }
      }
      else {
        piVar1[0x17] = *(int *)(DAT_0045fc34 + 0x5c);
        *(int **)(DAT_0045fc34 + 0x5c) = piVar1;
      }
      uVar3 = 1;
    }
  }
  else {
    if ((local_1c & 0x20) == 0) {
      if (((DAT_0045ea84 != '\0') && (DAT_0045fc40 != 0)) &&
         (((local_1c & 0x40000) == 0 || (DAT_0045ead0 == '\0')))) {
        DAT_0045ea84 = '\0';
        DAT_0045fc40 = *(int *)(DAT_0045fc40 + 8);
      }
    }
    else if ((DAT_0045fb6c == 0) && (DAT_0045fc84 == 0)) {
      DAT_0045ea84 = '\x01';
    }
    if ((local_1c & 0x10) == 0) {
      if (DAT_0045f8fc == 1) {
        if ((local_24[6] & 0x10) == 0) {
          local_24[6] = local_24[6] | 0x8000;
        }
        uVar3 = 0;
      }
      else {
        local_24[0xd] = *(undefined4 *)((int)param_2 + 0x54);
        if ((local_24[6] & 0x8000) == 0) {
          if ((local_24[6] & 0x10) == 0) {
            if (((((local_1c & 0x20) == 0) || (DAT_0045eb0c != '\0')) &&
                (((local_1c & 0x400) == 0 || (DAT_0045eb08 == '\0')))) &&
               (((local_1c & 0x40000) == 0 || (DAT_0045eb20 != '\0')))) {
              FUN_00424817(local_24);
            }
            if ((((DAT_0044f790 != '\0') && (*(int *)(PTR_DAT_0044f97c + 0x6c) != 0)) &&
                (DAT_0045f8a0 == 0)) && ((local_1c & 0x20) == 0)) {
              local_24[0xe] = 0;
              local_24[0xf] = 0;
            }
            if ((local_24[6] & 0x100) == 0) {
              if ((((local_24[6] & 0x200) != 0) && (*(int *)(param_2 + 2) == 0x200)) &&
                 (*(double *)(local_24 + 2) == *param_2)) {
                return 1;
              }
            }
            else if ((*(int *)(param_2 + 2) == 0x100) &&
                    (((local_24[4] == *(int *)(param_2 + 1) || (local_24[0xe] != 0)) ||
                     (local_24[0x13] != 0)))) {
              return 1;
            }
            FUN_004131f9((uint *)s_Phasing_error_00459408,(char *)param_1);
            uVar3 = 0;
          }
          else {
            FUN_004131f9((uint *)s_Symbol_already_used_as_SET_symbo_004593e4,(char *)param_1);
            uVar3 = 0;
          }
        }
        else {
          FUN_004131f9((uint *)s_Symbol_redefined_004593d0,(char *)param_1);
          uVar3 = 0;
        }
      }
    }
    else {
      uVar3 = FUN_0043835d(local_24,(undefined4 *)param_2);
    }
  }
  return uVar3;
}


/* ==== FUN_004382bb @ 004382bb ==== */

void __cdecl FUN_004382bb(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  if (DAT_0045fb6c == 0) {
    puVar2 = (undefined4 *)FUN_00439857(0xc);
    puVar1 = puVar2;
    DAT_0045fc40 = puVar2;
    if (DAT_0045fc3c != (undefined4 *)0x0) {
      DAT_0045fc44[2] = puVar2;
      puVar1 = DAT_0045fc3c;
    }
    DAT_0045fc3c = puVar1;
    DAT_0045fc44 = DAT_0045fc40;
    puVar2[1] = param_1;
    *puVar2 = DAT_0045eb68;
    puVar2[2] = 0;
  }
  else {
    *(undefined4 *)(DAT_0045fc4c + 4) = param_1;
    *(undefined4 *)(DAT_0045fb6c + 0x20) = param_1;
  }
  return;
}


/* ==== FUN_0043835d @ 0043835d ==== */

undefined4 __cdecl FUN_0043835d(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if ((param_1[6] & 0x10) == 0) {
    FUN_004131f9((uint *)s_Symbol_cannot_be_set_to_new_valu_00459434,(char *)*param_1);
    uVar1 = 0;
  }
  else {
    param_1[6] = param_1[6] & 0xfffff0ff;
    if (param_2[4] == 0x100) {
      param_1[6] = param_1[6] | 0x100;
      param_1[2] = *param_2;
      param_1[3] = param_2[1];
      param_1[4] = param_2[2];
    }
    else if (param_2[4] == 0x200) {
      param_1[6] = param_1[6] | 0x200;
      param_1[2] = *param_2;
      param_1[3] = param_2[1];
    }
    if ((param_2[6] & 0x1000) != 0) {
      param_1[6] = param_1[6] | 0x1000;
    }
    if (param_2[5] == 6) {
      param_1[6] = param_1[6] | 0x800;
    }
    uVar1 = 1;
  }
  return uVar1;
}


/* ==== FUN_00438441 @ 00438441 ==== */

undefined4 * __cdecl FUN_00438441(uint *param_1,int param_2)

{
  undefined4 *puVar1;
  uint local_20c [129];
  uint local_8;
  
  if (DAT_0045ea70 == '\0') {
    DAT_0045f934 = DAT_0045f934 + 1;
  }
  if (DAT_0045eaa0 != '\0') {
    strcpy((char *)local_20c,(char *)param_1);
    FUN_0043b836((char *)local_20c);
    param_1 = local_20c;
  }
  if ((char)*param_1 == DAT_0044f830) {
    puVar1 = FUN_00438583((int)param_1,param_2);
  }
  else {
    local_8 = FUN_00439b65((char *)param_1);
    DAT_0045fc34 = *(undefined4 *)(&DAT_0045fcc0 + local_8 * 4);
    puVar1 = FUN_00438713((char *)param_1,param_2,0);
    if (puVar1 == (undefined4 *)0x0) {
      if (DAT_0045f8fc == 2) {
        if (DAT_0044f790 == '\0') {
          FUN_004131f9((uint *)s_Symbol_undefined_on_pass_2_00459458,(char *)param_1);
        }
        else if (DAT_0045eaf4 != '\0') {
          FUN_0041351d((uint *)s_Unresolved_external_reference_00459474,(char *)param_1);
        }
      }
      puVar1 = (undefined4 *)0x0;
    }
    else if (((DAT_0045f8fc == 2) && (DAT_0045ea3c != '\0')) && (DAT_0045ea70 == '\0')) {
      FUN_004388eb((int)puVar1,param_2);
    }
  }
  return puVar1;
}


/* ==== FUN_00438583 @ 00438583 ==== */

undefined4 * __cdecl FUN_00438583(int param_1,int param_2)

{
  char *pcVar1;
  undefined4 *local_8;
  
  pcVar1 = (char *)(param_1 + 1);
  local_8 = (undefined4 *)0x0;
  if ((DAT_0045fb6c == 0) || (DAT_0045eb10 != '\0')) {
    if ((DAT_0045fc40 == (int *)0x0) || (*DAT_0045fc40 != DAT_0045eb68)) {
      DAT_0045fc34 = 0;
    }
    else {
      DAT_0045fc34 = DAT_0045fc40[1];
      local_8 = FUN_00438713(pcVar1,param_2,1);
      if ((((local_8 != (undefined4 *)0x0) && (DAT_0045f8fc == 2)) && (DAT_0045ea3c != '\0')) &&
         (DAT_0045ea70 == '\0')) {
        FUN_004388eb((int)local_8,param_2);
      }
    }
  }
  else if (*(int *)(DAT_0045fb6c + 0x20) == 0) {
    DAT_0045fc34 = 0;
  }
  else {
    DAT_0045fc34 = *(int *)(DAT_0045fb6c + 0x20);
    local_8 = FUN_00438713(pcVar1,param_2,1);
  }
  if (local_8 == (undefined4 *)0x0) {
    if ((DAT_0045f8fc == 2) && (DAT_0045ea70 == '\0')) {
      FUN_004131f9((uint *)s_Symbol_undefined_on_pass_2_004594ec,pcVar1);
    }
  }
  else {
    if ((((local_8[6] & 0x2000) != 0) && (local_8[0xb] != DAT_0045ebc0)) && (param_2 == 2)) {
      FUN_004131f9((uint *)s_Reference_outside_of_current_buf_00459494,pcVar1);
    }
    if ((((local_8[6] & 0x4000) != 0) && (local_8[0xc] != DAT_0045ebe8)) && (param_2 == 2)) {
      FUN_004131f9((uint *)s_Reference_outside_of_current_ove_004594c0,pcVar1);
    }
  }
  DAT_0045fc38 = DAT_0045fc34;
  return local_8;
}


/* ==== FUN_00438713 @ 00438713 ==== */

undefined4 * __cdecl FUN_00438713(char *param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 *local_20;
  int *local_18;
  undefined4 *local_14;
  undefined4 *local_10;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)0x0;
  local_10 = (undefined4 *)0x0;
  local_14 = (undefined4 *)0x0;
  for (local_20 = DAT_0045fc34; local_20 != (undefined4 *)0x0;
      local_20 = (undefined4 *)local_20[0x17]) {
    DAT_0045fc34 = local_20;
    if ((*param_1 == *(char *)*local_20) && (iVar1 = strcmp(param_1,(char *)*local_20), iVar1 == 0))
    {
      if (PTR_DAT_0044f978 == (undefined *)local_20[0x10]) {
        if ((DAT_0045eb28 == '\0') || (PTR_DAT_0044f978 == &DAT_0044f878)) break;
      }
      else if (param_3 == 0) {
        if (((DAT_0044f7ac != '\0') && (local_10 == (undefined4 *)0x0)) && (param_2 != 1)) {
          for (local_18 = DAT_0045fb84;
              (local_18 != (int *)0x0 && ((undefined *)*local_18 != &DAT_0044f878));
              local_18 = (int *)local_18[1]) {
            if ((local_20[0x10] == *local_18) && ((*(uint *)(*local_18 + 0xc) & 0x20) == 0)) {
              local_10 = local_20;
            }
          }
        }
        if (((local_14 == (undefined4 *)0x0) && ((local_20[6] & 0x80) != 0)) &&
           ((param_2 == 1 || (iVar1 = FUN_00436def(param_1), iVar1 != 0)))) {
          local_14 = local_20;
        }
        if ((local_8 == (undefined4 *)0x0) && ((local_20[6] & 0x40) != 0)) {
          local_8 = local_20;
        }
      }
    }
  }
  if ((local_8 != (undefined4 *)0x0) &&
     ((DAT_0045eb28 != '\0' ||
      (((local_20 != (undefined4 *)0x0 && ((local_20[6] & 0x10) != 0)) &&
       (iVar1 = FUN_00436def(param_1), iVar1 != 0)))))) {
    local_20 = local_8;
  }
  if ((local_20 == (undefined4 *)0x0) && (iVar1 = FUN_00436d1b(param_1), iVar1 == 0)) {
    if (local_10 == (undefined4 *)0x0) {
      if (local_14 == (undefined4 *)0x0) {
        if (local_8 != (undefined4 *)0x0) {
          local_20 = local_8;
        }
      }
      else {
        local_20 = local_14;
      }
    }
    else {
      local_20 = local_10;
    }
  }
  return local_20;
}


/* ==== FUN_004388eb @ 004388eb ==== */

void __cdecl FUN_004388eb(int param_1,int param_2)

{
  undefined4 *puVar1;
  int local_10;
  int local_8;
  
  if (param_2 != 0) {
    puVar1 = (undefined4 *)FUN_00439857(0xc);
    *puVar1 = DAT_0045eb80;
    puVar1[1] = param_2;
    puVar1[2] = 0;
    if (*(int *)(param_1 + 0x50) == 0) {
      *(undefined4 **)(param_1 + 0x50) = puVar1;
    }
    else {
      local_10 = *(int *)(param_1 + 0x50);
      local_8 = local_10;
      for (; local_10 != 0; local_10 = *(int *)(local_10 + 8)) {
        local_8 = local_10;
      }
      *(undefined4 **)(local_8 + 8) = puVar1;
    }
  }
  return;
}


/* ==== FUN_0043896d @ 0043896d ==== */

undefined4 __cdecl FUN_0043896d(uint *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  
  if (DAT_0044f790 == '\0') {
    FUN_00412fa0((uint *)s_Attempt_to_store_external_refere_00459508);
  }
  if ((char)*param_1 == DAT_0044f830) {
    uVar1 = 0;
  }
  else {
    if (param_2 == 0) {
      if ((DAT_0045ea88 == '\0') && (iVar5 = FUN_00436def((char *)param_1), iVar5 != 0)) {
        bVar6 = true;
      }
      else {
        bVar6 = false;
      }
    }
    else {
      bVar6 = DAT_0045ea88 == '\0';
    }
    puVar2 = FUN_00438b28(param_1);
    if (puVar2 == (undefined4 *)0x0) {
      piVar3 = (int *)FUN_00439857(0x14);
      uVar4 = strlen((char *)param_1);
      iVar5 = FUN_00439857(uVar4 + 1);
      *piVar3 = iVar5;
      strcpy((char *)*piVar3,(char *)param_1);
      if (DAT_0045eaa0 != '\0') {
        FUN_0043b836((char *)*piVar3);
      }
      piVar3[1] = (-(uint)bVar6 & 0x40) + 0x40;
      piVar3[2] = (int)PTR_DAT_0044f978;
      piVar3[4] = 0;
      if (DAT_0045fc54 == 0) {
        uVar4 = FUN_00439b65((char *)*piVar3);
        *(int **)(&DAT_00461c50 + uVar4 * 4) = piVar3;
        piVar3[3] = 0;
      }
      else {
        *(int **)(DAT_0045fc54 + 0x10) = piVar3;
        piVar3[3] = DAT_0045fc54;
      }
      FUN_00424b1a(piVar3);
      DAT_0045eb74 = DAT_0045eb74 + 1;
      uVar1 = 1;
    }
    else {
      if ((bVar6) && ((puVar2[1] & 0x40) != 0)) {
        puVar2[1] = puVar2[1] & 0xffffffbf;
        puVar2[1] = puVar2[1] | 0x80;
      }
      uVar1 = 1;
    }
  }
  return uVar1;
}


