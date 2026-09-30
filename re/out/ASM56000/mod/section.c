/* section: 21 functions from ASM56000 */

/* ==== FUN_00434f48 @ 00434f48 ==== */

void FUN_00434f48(void)

{
  undefined *puVar1;
  int *piVar2;
  undefined *local_20;
  int *local_1c;
  undefined *local_14;
  undefined *local_c;
  
  for (local_20 = PTR_DAT_0044f980; local_20 != (undefined *)0x0;
      local_20 = *(undefined **)(local_20 + 0x8c)) {
    local_c = *(undefined **)(local_20 + 0x68);
    while (local_c != (undefined *)0x0) {
      local_1c = *(int **)(local_c + 0x18);
      while (local_1c != (int *)0x0) {
        if (*local_1c != 0) {
          FUN_004398b5((undefined *)*local_1c);
          *local_1c = 0;
        }
        local_14 = (undefined *)local_1c[8];
        while (local_14 != (undefined *)0x0) {
          puVar1 = *(undefined **)(local_14 + 4);
          FUN_004398b5(local_14);
          local_14 = puVar1;
        }
        piVar2 = (int *)local_1c[9];
        FUN_004398b5((undefined *)local_1c);
        local_1c = piVar2;
      }
      if (*(int *)(local_c + 0x1c) != 0) {
        FUN_004398b5(*(undefined **)(local_c + 0x1c));
      }
      puVar1 = *(undefined **)(local_c + 0x20);
      FUN_004398b5(local_c);
      local_c = puVar1;
    }
    *(undefined4 *)(local_20 + 0x68) = 0;
  }
  local_c = DAT_0044f8e0;
  while (local_c != (undefined *)0x0) {
    local_1c = *(int **)(local_c + 0x18);
    while (local_1c != (int *)0x0) {
      if (*local_1c != 0) {
        FUN_004398b5((undefined *)*local_1c);
        *local_1c = 0;
      }
      piVar2 = (int *)local_1c[9];
      FUN_004398b5((undefined *)local_1c);
      local_1c = piVar2;
    }
    FUN_004398b5(*(undefined **)(local_c + 0x1c));
    puVar1 = *(undefined **)(local_c + 0x20);
    FUN_004398b5(local_c);
    local_c = puVar1;
  }
  DAT_0044f8e0 = (undefined *)0x0;
  return;
}


/* ==== FUN_004350d3 @ 004350d3 ==== */

int FUN_004350d3(void)

{
  int iVar1;
  int local_1c;
  uint local_18;
  undefined1 local_14 [16];
  
  if ((PTR_DAT_0044f814 != (undefined *)0x0) && (*PTR_DAT_0044f814 != '\0')) {
    if (__mb_cur_max < 2) {
      local_18 = *(ushort *)(_pctype + (char)*PTR_DAT_0044f814 * 2) & 1;
    }
    else {
      local_18 = _isctype((int)(char)*PTR_DAT_0044f814,1);
    }
    if (local_18 == 0) {
      local_1c = (int)(char)*PTR_DAT_0044f814;
    }
    else {
      local_1c = tolower((int)(char)*PTR_DAT_0044f814);
    }
    if (local_1c == 0x6a) {
      strcpy(local_14,PTR_DAT_0044f814);
      FUN_0043b836(local_14);
      iVar1 = strcmp(local_14,&DAT_00458ac0);
      if (iVar1 == 0) {
        strcpy(local_14,&DAT_00458ac4);
      }
      else {
        local_14[0] = 'b';
      }
      iVar1 = FUN_00438f1a((uint *)local_14,0);
      return iVar1;
    }
  }
  return 0;
}


/* ==== FUN_004351c0 @ 004351c0 ==== */

undefined4 __cdecl FUN_004351c0(uint *param_1,uint *param_2,uint *param_3)

{
  undefined *puVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  char *a;
  undefined *puVar5;
  undefined *local_248;
  uint local_23c;
  undefined *local_238;
  char local_234 [20];
  undefined *local_220;
  uint local_21c [129];
  char local_18 [20];
  
  local_23c = 0;
  iVar3 = FUN_0043b659((char *)param_1);
  if (iVar3 == -1) {
    uVar4 = 0;
  }
  else if (iVar3 == 0) {
    FUN_00413085((uint *)s_Missing_section_name_00458b00);
    uVar4 = 0;
  }
  else if ((((char)*param_1 == DAT_0044f830) ||
           (((char)*param_1 == s_GLOBAL_0044f868[0] &&
            (iVar3 = strcmp((char *)param_1,s_GLOBAL_0044f868), iVar3 == 0)))) ||
          (((char)*param_1 == s_RESERVE_0044f870[0] &&
           (iVar3 = strcmp((char *)param_1,s_RESERVE_0044f870), iVar3 == 0)))) {
    FUN_004131f9((uint *)s_Invalid_section_name_00458b18,(char *)param_1);
    uVar4 = 0;
  }
  else {
    if (DAT_0045eaa0 != '\0') {
      strcpy((char *)local_21c,(char *)param_1);
      FUN_0043b836((char *)local_21c);
      param_1 = local_21c;
    }
    if (DAT_0045eab0 != '\0') {
      local_23c = 0x40;
    }
    if (DAT_0045eab4 != '\0') {
      local_23c = local_23c | 0x10;
    }
    if ((param_2 != (uint *)0x0) && ((char)*param_2 != '\0')) {
      cVar2 = strcpy(local_234,(char *)param_2);
      param_2 = (uint *)FUN_0043b836((char *)CONCAT31(extraout_var,cVar2));
      if (((char)*param_2 == s_global_00458b30[0]) &&
         (iVar3 = strcmp((char *)param_2,s_global_00458b38), iVar3 == 0)) {
        local_23c = local_23c | 0x40;
      }
      else if (((char)*param_2 == s_static_00458b40[0]) &&
              (iVar3 = strcmp((char *)param_2,s_static_00458b48), iVar3 == 0)) {
        local_23c = local_23c | 0x10;
      }
      else if (((char)*param_2 == s_local_00458b50[0]) &&
              (iVar3 = strcmp((char *)param_2,s_local_00458b58), iVar3 == 0)) {
        local_23c = local_23c | 0x20;
      }
      else {
        if (((char)*param_2 != s_debug_00458b60[0]) ||
           (iVar3 = strcmp((char *)param_2,s_debug_00458b68), iVar3 != 0)) {
          FUN_004131f9((uint *)s_Invalid_section_directive_modifi_00458b70,(char *)param_2);
          return 0;
        }
        local_23c = local_23c | 0x200000;
      }
    }
    if ((param_3 != (uint *)0x0) && ((char)*param_3 != '\0')) {
      cVar2 = strcpy(local_18,(char *)param_3);
      a = FUN_0043b836((char *)CONCAT31(extraout_var_00,cVar2));
      if ((*a == s_global_00458b94[0]) && (iVar3 = strcmp(a,s_global_00458b9c), iVar3 == 0)) {
        local_23c = local_23c | 0x40;
      }
      else if ((*a == s_static_00458ba4[0]) && (iVar3 = strcmp(a,s_static_00458bac), iVar3 == 0)) {
        local_23c = local_23c | 0x10;
      }
      else if ((*a == s_local_00458bb4[0]) && (iVar3 = strcmp(a,s_local_00458bbc), iVar3 == 0)) {
        local_23c = local_23c | 0x20;
      }
      else {
        if ((*a != s_debug_00458bc4[0]) || (iVar3 = strcmp(a,s_debug_00458bcc), iVar3 != 0)) {
          FUN_004131f9((uint *)s_Invalid_section_directive_modifi_00458bd4,(char *)param_2);
          return 0;
        }
        local_23c = local_23c | 0x200000;
      }
    }
    local_238 = *(undefined **)(PTR_DAT_0044f980 + 0x8c);
    while ((local_238 != (undefined *)0x0 &&
           (((char)*param_1 != **(char **)(local_238 + 4) ||
            (iVar3 = strcmp((char *)param_1,*(char **)(local_238 + 4)), iVar3 != 0))))) {
      local_238 = *(undefined **)(local_238 + 0x8c);
    }
    if (local_238 == (undefined *)0x0) {
      if (DAT_0045f8fc == 2) {
        FUN_004131f9((uint *)s_Section_not_encountered_on_pass_1_00458bf8,(char *)param_1);
        uVar4 = 0;
      }
      else {
        iVar3 = FUN_00435c1a((undefined *)0x0);
        if (iVar3 == 0) {
          uVar4 = 0;
        }
        else {
          FUN_00435d9f();
          puVar5 = (undefined *)FUN_00435a59(param_1);
          DAT_0045fb80 = DAT_0045fb80 + 1;
          if (0xff < DAT_0045fb80) {
            FUN_00412fa0((uint *)s_Too_many_sections_in_module_00458c1c);
          }
          *(int *)(puVar5 + 8) = DAT_0045fb80;
          *(uint *)(puVar5 + 0xc) = local_23c | 8;
          if ((local_23c & 0x20) == 0) {
            FUN_00435cde((int)puVar5,1);
          }
          puVar1 = PTR_DAT_0044f97c;
          local_220 = PTR_DAT_0044f978;
          local_248 = puVar5;
          if ((local_23c & 0x10) != 0) {
            local_248 = PTR_DAT_0044f97c;
          }
          *(undefined **)(puVar5 + 0x88) = local_248;
          FUN_00435eca(puVar5,1);
          if ((local_23c & 0x20) != 0) {
            *(undefined **)(puVar5 + 0x88) = puVar1;
            PTR_DAT_0044f978 = local_220;
            *(undefined **)(local_220 + 0x88) = puVar5;
          }
          if (DAT_0044f790 == '\0') {
            *(uint *)(DAT_0045fb8c + 0x10) = *(uint *)(DAT_0045fb8c + 0x10) & 0xffffefff;
          }
          else {
            *(int *)(DAT_0045fb8c + 0x20) = *(int *)(DAT_0045fb8c + 0x20) + 1;
          }
          *(undefined **)(PTR_DAT_0044f984 + 0x8c) = puVar5;
          PTR_DAT_0044f984 = puVar5;
          *(uint *)(puVar5 + 0xc) = *(uint *)(puVar5 + 0xc) & 0xfffffff7;
          uVar4 = 1;
        }
      }
    }
    else {
      iVar3 = FUN_00435c1a(local_238);
      if (iVar3 == 0) {
        uVar4 = 0;
      }
      else {
        FUN_00435d9f();
        *(uint *)(local_238 + 0xc) = *(uint *)(local_238 + 0xc) & 0xffffff8f;
        if ((local_23c & 0x40) != 0) {
          *(uint *)(local_238 + 0xc) = *(uint *)(local_238 + 0xc) | 0x40;
        }
        if ((local_23c & 0x10) != 0) {
          *(uint *)(local_238 + 0xc) = *(uint *)(local_238 + 0xc) | 0x10;
          *(undefined4 *)(local_238 + 0x88) = *(undefined4 *)(PTR_DAT_0044f978 + 0x88);
        }
        if ((local_23c & 0x200000) != 0) {
          *(uint *)(local_238 + 0xc) = *(uint *)(local_238 + 0xc) | 0x200000;
        }
        if ((local_23c & 0x20) == 0) {
          FUN_00435cde((int)local_238,1);
        }
        puVar5 = PTR_DAT_0044f97c;
        local_220 = PTR_DAT_0044f978;
        if ((local_23c & 0x20) != 0) {
          *(uint *)(local_238 + 0xc) = *(uint *)(local_238 + 0xc) | 0x20;
          DAT_0045fb7c = PTR_DAT_0044f978;
          *(undefined **)(local_238 + 0x88) = local_238;
        }
        FUN_00435eca(local_238,1);
        if ((local_23c & 0x20) != 0) {
          *(undefined **)(local_238 + 0x88) = puVar5;
          PTR_DAT_0044f978 = local_220;
          *(undefined **)(local_220 + 0x88) = local_238;
        }
        if (DAT_0044f790 != '\0') {
          *(int *)(DAT_0045fb8c + 0x20) = *(int *)(DAT_0045fb8c + 0x20) + 1;
        }
        uVar4 = 1;
      }
    }
  }
  return uVar4;
}


/* ==== FUN_00435924 @ 00435924 ==== */

undefined4 FUN_00435924(void)

{
  int *piVar1;
  undefined4 uVar2;
  int local_10;
  int *local_c;
  undefined *local_8;
  
  local_8 = (undefined *)0x0;
  local_10 = 0;
  if (DAT_0045fb84 == (int *)0x0) {
    DAT_0045f860 = 0;
    FUN_00413085((uint *)s_ENDSEC_without_associated_SECTIO_00458c38);
    uVar2 = 0;
  }
  else {
    if ((*(uint *)(PTR_DAT_0044f97c + 0xc) & 0x20) == 0) {
      FUN_00435cde((int)PTR_DAT_0044f978,0);
    }
    local_c = DAT_0045fb84;
    while ((local_c != (int *)0x0 && ((local_8 == (undefined *)0x0 || (local_10 == 0))))) {
      if ((local_8 == (undefined *)0x0) && ((*(uint *)(*local_c + 0xc) & 0x20) == 0)) {
        local_8 = (undefined *)*local_c;
      }
      if ((local_10 == 0) && ((*(uint *)(*local_c + 0xc) & 0x10) == 0)) {
        local_10 = *local_c;
      }
      local_c = (int *)local_c[1];
    }
    if ((local_8 == (undefined *)0x0) || (local_10 == 0)) {
      FUN_00412fa0((uint *)s_Section_stack_mode_error_00458c64);
    }
    *(int *)(local_8 + 0x88) = local_10;
    FUN_00435d9f();
    FUN_00435eca(local_8,0);
    piVar1 = DAT_0045fb84;
    DAT_0045fb84 = (int *)DAT_0045fb84[1];
    FUN_004398b5((undefined *)piVar1);
    if (0 < DAT_0045eba8) {
      DAT_0045eba8 = DAT_0045eba8 + -1;
    }
    uVar2 = 1;
  }
  return uVar2;
}


/* ==== FUN_00435a59 @ 00435a59 ==== */

int __cdecl FUN_00435a59(uint *param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 local_10;
  undefined4 local_c;
  
  iVar1 = FUN_00439857(0x90);
  uVar2 = strlen((char *)param_1);
  iVar3 = FUN_00439857(uVar2 + 1);
  *(int *)(iVar1 + 4) = iVar3;
  strcpy(*(char **)(iVar1 + 4),(char *)param_1);
  *(undefined4 *)(iVar1 + 8) = 0;
  *(uint *)(iVar1 + 0xc) = -(uint)(DAT_0044f790 != '\0') & 0x30000;
  *(undefined4 *)(iVar1 + 0x10) = 0;
  memset((void *)(iVar1 + 0x14),0,0x10);
  for (local_c = 0; local_c < 2; local_c = local_c + 1) {
    for (local_10 = 0; local_10 < 2; local_10 = local_10 + 1) {
      *(undefined4 *)(iVar1 + local_c * 0x20 + 0x28 + local_10 * 0x10) = 0;
      *(undefined4 *)(iVar1 + 0x24 + local_c * 0x20 + local_10 * 0x10) = 0;
      *(undefined4 *)(iVar1 + local_c * 0x20 + 0x2c + local_10 * 0x10) = 0;
      *(undefined4 *)(iVar1 + local_c * 0x20 + 0x30 + local_10 * 0x10) = 0;
    }
  }
  *(undefined4 *)(iVar1 + 100) = 0;
  *(undefined4 *)(iVar1 + 0x6c) = 0;
  *(undefined4 *)(iVar1 + 0x68) = 0;
  *(undefined4 *)(iVar1 + 0x74) = 0;
  *(undefined4 *)(iVar1 + 0x70) = 0;
  if (DAT_0045eb34 != '\0') {
    FUN_00433f67(iVar1);
  }
  *(undefined4 *)(iVar1 + 0x84) = 0;
  *(undefined4 *)(iVar1 + 0x80) = 0;
  *(undefined4 *)(iVar1 + 0x7c) = 0;
  *(undefined4 *)(iVar1 + 0x78) = 0;
  *(int *)(iVar1 + 0x88) = iVar1;
  *(undefined4 *)(iVar1 + 0x8c) = 0;
  return iVar1;
}


/* ==== FUN_00435c1a @ 00435c1a ==== */

undefined4 __cdecl FUN_00435c1a(undefined *param_1)

{
  undefined4 *puVar1;
  undefined *local_10;
  int *local_c;
  
  if ((*(uint *)(PTR_DAT_0044f97c + 0xc) & 0x20) == 0) {
    local_10 = PTR_DAT_0044f978;
  }
  else {
    local_10 = PTR_DAT_0044f97c;
  }
  if (param_1 != (undefined *)0x0) {
    if (param_1 == local_10) {
      FUN_00413085((uint *)s_Cannot_nest_section_inside_itsel_00458c80);
      return 0;
    }
    for (local_c = DAT_0045fb84; local_c != (int *)0x0; local_c = (int *)local_c[1]) {
      if ((undefined *)*local_c == param_1) {
        FUN_00413085((uint *)s_Cannot_nest_section_inside_itsel_00458ca4);
        return 0;
      }
    }
  }
  puVar1 = (undefined4 *)FUN_00439857(8);
  *puVar1 = local_10;
  puVar1[1] = DAT_0045fb84;
  DAT_0045fb84 = puVar1;
  DAT_0045eba8 = DAT_0045eba8 + 1;
  return 1;
}


/* ==== FUN_00435cde @ 00435cde ==== */

void __cdecl FUN_00435cde(int param_1,int param_2)

{
  char *local_8;
  
  if ((DAT_0045f8fc != 1) && ((DAT_0044f790 != '\0' || (DAT_0045eadc != '\0')))) {
    FUN_0043c34d();
    if (param_2 == 0) {
      local_8 = &DAT_00458ccc;
    }
    else {
      local_8 = &DAT_00458cc8;
    }
    strcpy((char *)&DAT_00465a60,local_8);
    if (param_2 != 0) {
      DAT_00465a68 = FUN_0042456e(*(uint **)(param_1 + 4));
    }
    DAT_00465a70 = 0xffffffff;
    DAT_00465a78 = 0xc9;
    DAT_00465a7c = 1;
    FUN_0042447e(&DAT_00465a60);
    DAT_00465880 = *(undefined4 *)(param_1 + 8);
    DAT_00465884 = DAT_0045eb78;
    FUN_0042447e(&DAT_00465880);
  }
  return;
}


/* ==== FUN_00435d9f @ 00435d9f ==== */

void FUN_00435d9f(void)

{
  undefined4 *puVar1;
  bool bVar2;
  bool bVar3;
  
  bVar2 = DAT_0044f794 != '\0';
  bVar3 = DAT_0044f798 != '\0';
  *(uint *)(PTR_DAT_0044f97c + 0xc) = *(uint *)(PTR_DAT_0044f97c + 0xc) & 0xfffcbfff;
  *(uint *)(PTR_DAT_0044f97c + 0xc) =
       *(uint *)(PTR_DAT_0044f97c + 0xc) |
       -(uint)(DAT_0044f794 != '\0') & 0x10000 | -(uint)(DAT_0044f798 != '\0') & 0x20000 |
       -(uint)(DAT_0045f8c0 != DAT_0045f8cc) & 0x4000;
  puVar1 = (undefined4 *)(PTR_DAT_0044f97c + (uint)bVar2 * 0x20 + 0x24);
  *puVar1 = DAT_0045f8a0;
  puVar1[1] = DAT_0045f8a4;
  puVar1[2] = DAT_0045f8a8;
  puVar1[3] = DAT_0045f8ac;
  *(uint *)(PTR_DAT_0044f97c + (uint)bVar2 * 8 + 0x14) = -(uint)(DAT_0045eab8 != '\0') & 0x400;
  puVar1 = (undefined4 *)(PTR_DAT_0044f97c + (uint)bVar3 * 0x20 + 0x34);
  *puVar1 = DAT_0045f8b0;
  puVar1[1] = DAT_0045f8b4;
  puVar1[2] = DAT_0045f8b8;
  puVar1[3] = DAT_0045f8bc;
  *(uint *)(PTR_DAT_0044f97c + (uint)bVar3 * 8 + 0x18) = -(uint)(DAT_0045eabc != '\0') & 0x400;
  return;
}


/* ==== FUN_00435eca @ 00435eca ==== */

void __cdecl FUN_00435eca(undefined *param_1,int param_2)

{
  int *piVar1;
  undefined *puVar2;
  uint uVar3;
  bool bVar4;
  
  bVar4 = DAT_0045f8c0 != DAT_0045f8cc;
  PTR_DAT_0044f978 = param_1;
  puVar2 = *(undefined **)(param_1 + 0x88);
  if ((*(uint *)(param_1 + 0xc) & 0x10) == 0) {
    if (param_2 == 0) {
      uVar3 = *(uint *)(puVar2 + 0xc);
      DAT_0044f794 = (uVar3 & 0x10000) != 0;
      DAT_0044f798 = (uVar3 & 0x20000) != 0;
      bVar4 = (uVar3 & 0x4000) != 0;
    }
    else {
      DAT_0044f798 = DAT_0044f790;
      DAT_0044f794 = DAT_0044f790;
      bVar4 = false;
    }
  }
  piVar1 = (int *)(puVar2 + (uint)(DAT_0044f794 != '\0') * 0x20 + 0x24);
  DAT_0045f8a0 = *piVar1;
  DAT_0045f8a4 = piVar1[1];
  DAT_0045f8a8 = piVar1[2];
  DAT_0045f8ac = piVar1[3];
  DAT_0045eab8 = (*(uint *)(puVar2 + (uint)(DAT_0044f794 != '\0') * 8 + 0x14) & 0x400) != 0;
  PTR_DAT_0044f97c = puVar2;
  DAT_0045fb88 = FUN_0042c829((int)puVar2,&DAT_0045f8a0,
                              -(uint)(DAT_0044f794 != '\0') & 0x1000 | -(uint)bVar4 & 0x4000,0);
  DAT_0045f8c0 = (undefined4 *)(DAT_0045fb88[9] + 0x10);
  DAT_0045f8c4 = *DAT_0045f8c0;
  DAT_0045f8d4 = FUN_0042ce91(0x22,&DAT_0045f8a0,(uint)!bVar4);
  DAT_0045f8d8 = FUN_0042ce91(0x1c,&DAT_0045f8a0,(uint)!bVar4);
  if ((DAT_0045eb34 != '\0') && (DAT_0045f8a0 == 0)) {
    FUN_00433e78(DAT_0045f8a8);
  }
  if (bVar4) {
    piVar1 = (int *)(puVar2 + (uint)(DAT_0044f798 != '\0') * 0x20 + 0x34);
    DAT_0045f8b0 = *piVar1;
    DAT_0045f8b4 = piVar1[1];
    DAT_0045f8b8 = piVar1[2];
    DAT_0045f8bc = piVar1[3];
    DAT_0045eabc = (*(uint *)(puVar2 + (uint)(DAT_0044f798 != '\0') * 8 + 0x18) & 0x400) != 0;
    DAT_0045fb8c = FUN_0042c829((int)puVar2,&DAT_0045f8b0,-(uint)(DAT_0044f798 != '\0') & 0x1000,0);
    DAT_0045f8cc = (undefined4 *)(DAT_0045fb8c[9] + 0x10);
    DAT_0045f8dc = FUN_0042ce91(0x22,&DAT_0045f8b0,1);
    DAT_0045f8e0 = FUN_0042ce91(0x1c,&DAT_0045f8b0,1);
  }
  else {
    DAT_0045f8b0 = DAT_0045f8a0;
    DAT_0045f8b4 = DAT_0045f8a4;
    DAT_0045f8b8 = DAT_0045f8a8;
    DAT_0045f8bc = DAT_0045f8ac;
    DAT_0045eabc = DAT_0045eab8;
    DAT_0045f8dc = DAT_0045f8d4;
    DAT_0045f8e0 = DAT_0045f8d8;
    DAT_0045fb8c = DAT_0045fb88;
    DAT_0045f8cc = DAT_0045f8c0;
  }
  DAT_0045f8d0 = *DAT_0045f8cc;
  return;
}


/* ==== FUN_004361d3 @ 004361d3 ==== */

void FUN_004361d3(void)

{
  undefined *puVar1;
  undefined4 *puVar2;
  undefined4 *local_30;
  undefined *local_28;
  undefined *local_24;
  undefined *local_14;
  undefined *local_10;
  undefined *local_c;
  
  local_c = PTR_DAT_0044f980;
  puVar1 = local_c;
  while (local_c = puVar1, local_c != (undefined *)0x0) {
    if ((local_c != &DAT_0044f878) && (*(int *)(local_c + 4) != 0)) {
      FUN_004398b5(*(undefined **)(local_c + 4));
      *(undefined4 *)(local_c + 4) = 0;
    }
    local_14 = *(undefined **)(local_c + 100);
    while (local_14 != (undefined *)0x0) {
      if (*(int *)(local_14 + 0x24) != 0) {
        FUN_004398b5(*(undefined **)(local_14 + 0x24));
      }
      *(undefined4 *)(local_14 + 0x24) = 0;
      puVar1 = *(undefined **)(local_14 + 0x2c);
      FUN_004398b5(local_14);
      local_14 = puVar1;
    }
    *(undefined4 *)(local_c + 100) = 0;
    local_10 = *(undefined **)(local_c + 0x68);
    while (local_10 != (undefined *)0x0) {
      puVar1 = *(undefined **)(local_10 + 0x20);
      FUN_004398b5(local_10);
      local_10 = puVar1;
    }
    *(undefined4 *)(local_c + 0x68) = 0;
    local_28 = *(undefined **)(local_c + 0x70);
    while (local_28 != (undefined *)0x0) {
      puVar1 = *(undefined **)(local_28 + 8);
      FUN_004398b5(local_28);
      local_28 = puVar1;
    }
    *(undefined4 *)(local_c + 0x70) = 0;
    local_30 = *(undefined4 **)(local_c + 0x7c);
    while (local_30 != (undefined4 *)0x0) {
      FUN_004398b5((undefined *)*local_30);
      *local_30 = 0;
      puVar2 = (undefined4 *)local_30[1];
      FUN_004398b5((undefined *)local_30);
      local_30 = puVar2;
    }
    *(undefined4 *)(local_c + 0x7c) = 0;
    local_30 = *(undefined4 **)(local_c + 0x78);
    while (local_30 != (undefined4 *)0x0) {
      FUN_004398b5((undefined *)*local_30);
      *local_30 = 0;
      puVar2 = (undefined4 *)local_30[1];
      FUN_004398b5((undefined *)local_30);
      local_30 = puVar2;
    }
    *(undefined4 *)(local_c + 0x78) = 0;
    local_30 = *(undefined4 **)(local_c + 0x84);
    while (local_30 != (undefined4 *)0x0) {
      FUN_004398b5((undefined *)*local_30);
      *local_30 = 0;
      puVar2 = (undefined4 *)local_30[1];
      FUN_004398b5((undefined *)local_30);
      local_30 = puVar2;
    }
    *(undefined4 *)(local_c + 0x84) = 0;
    local_30 = *(undefined4 **)(local_c + 0x80);
    while (local_30 != (undefined4 *)0x0) {
      FUN_004398b5((undefined *)*local_30);
      *local_30 = 0;
      puVar2 = (undefined4 *)local_30[1];
      FUN_004398b5((undefined *)local_30);
      local_30 = puVar2;
    }
    *(undefined4 *)(local_c + 0x80) = 0;
    local_24 = *(undefined **)(local_c + 0x10);
    while (local_24 != (undefined *)0x0) {
      puVar1 = *(undefined **)(local_24 + 0xc);
      FUN_004398b5(local_24);
      local_24 = puVar1;
    }
    *(undefined4 *)(local_c + 0x10) = 0;
    puVar1 = *(undefined **)(local_c + 0x8c);
    if (local_c != &DAT_0044f878) {
      FUN_004398b5(local_c);
    }
  }
  *(undefined4 *)(PTR_DAT_0044f980 + 0x8c) = 0;
  PTR_DAT_0044f984 = PTR_DAT_0044f980;
  DAT_0045fb80 = 0;
  return;
}


/* ==== FUN_004364a5 @ 004364a5 ==== */

undefined4 FUN_004364a5(void)

{
  char cVar1;
  undefined4 uVar2;
  uint *s;
  int iVar3;
  int *piVar4;
  uint uVar5;
  
  if (PTR_DAT_0044f978 == &DAT_0044f878) {
    FUN_00413085((uint *)s_LOCAL_without_preceding_SECTION_d_00458cd0);
    uVar2 = 0;
  }
  else if ((*(uint *)(PTR_DAT_0044f978 + 0xc) & 0x40) == 0) {
    if (*PTR_DAT_0044f818 == '\0') {
      FUN_00413085((uint *)s_Missing_symbol_name_00458d28);
      uVar2 = 0;
    }
    else {
      FUN_0043b007(1);
      DAT_0045f860 = PTR_DAT_0044f818;
      while (*DAT_0045f860 != '\0') {
        s = (uint *)FUN_0043b448();
        if (s == (uint *)0x0) {
          return 0;
        }
        if ((*DAT_0045f860 != '\0') &&
           (cVar1 = *DAT_0045f860, DAT_0045f860 = DAT_0045f860 + 1, cVar1 != ',')) {
          FUN_00413085((uint *)s_Syntax_error_in_symbol_name_list_00458d3c);
          return 0;
        }
        if ((char)*s == DAT_0044f830) {
          FUN_004131f9((uint *)s_Local_symbol_names_cannot_be_use_00458d60,(char *)s);
        }
        else {
          iVar3 = FUN_00436d1b((char *)s);
          if (iVar3 == 0) {
            iVar3 = FUN_00436d85((char *)s);
            if (iVar3 == 0) {
              iVar3 = FUN_00436def((char *)s);
              if (iVar3 == 0) {
                iVar3 = FUN_00436e56((char *)s);
                if (iVar3 == 0) {
                  iVar3 = FUN_00436ebd(s);
                  if (iVar3 != 0) {
                    piVar4 = (int *)FUN_00439857(8);
                    uVar5 = strlen((char *)s);
                    iVar3 = FUN_00439857(uVar5 + 1);
                    *piVar4 = iVar3;
                    strcpy((char *)*piVar4,(char *)s);
                    piVar4[1] = *(int *)(PTR_DAT_0044f978 + 0x80);
                    *(int **)(PTR_DAT_0044f978 + 0x80) = piVar4;
                  }
                }
                else {
                  FUN_004131f9((uint *)s_Symbol_already_defined_as_XDEF_00458df4,(char *)s);
                }
              }
              else {
                FUN_004131f9((uint *)s_Symbol_already_defined_as_XREF_00458dd4,(char *)s);
              }
            }
            else {
              FUN_004131f9((uint *)s_Symbol_already_defined_as_GLOBAL_00458db0,(char *)s);
            }
          }
          else {
            FUN_004131f9((uint *)s_Symbol_already_defined_as_LOCAL_00458d90,(char *)s);
          }
        }
      }
      uVar2 = 1;
    }
  }
  else {
    FUN_00413085((uint *)s_LOCAL_directive_not_valid_in_glo_00458cfc);
    uVar2 = 0;
  }
  return uVar2;
}


/* ==== FUN_004366be @ 004366be ==== */

undefined4 FUN_004366be(void)

{
  char cVar1;
  undefined4 uVar2;
  uint *s;
  int iVar3;
  int *piVar4;
  uint uVar5;
  
  if (PTR_DAT_0044f978 == &DAT_0044f878) {
    FUN_00413085((uint *)s_GLOBAL_without_preceding_SECTION_00458e14);
    uVar2 = 0;
  }
  else if (*DAT_0045f860 == '\0') {
    FUN_00413085((uint *)s_Missing_symbol_name_00458e40);
    uVar2 = 0;
  }
  else {
    FUN_0043b007(1);
    DAT_0045f860 = PTR_DAT_0044f818;
    while (*DAT_0045f860 != '\0') {
      s = (uint *)FUN_0043b448();
      if (s == (uint *)0x0) {
        return 0;
      }
      if ((*DAT_0045f860 != '\0') &&
         (cVar1 = *DAT_0045f860, DAT_0045f860 = DAT_0045f860 + 1, cVar1 != ',')) {
        FUN_00413085((uint *)s_Syntax_error_in_symbol_name_list_00458e54);
        return 0;
      }
      if ((char)*s == DAT_0044f830) {
        FUN_004131f9((uint *)s_Local_symbol_names_cannot_be_use_00458e78,(char *)s);
      }
      else {
        iVar3 = FUN_00436d1b((char *)s);
        if (iVar3 == 0) {
          if ((DAT_0045f8fc == 1) && (iVar3 = FUN_00436d85((char *)s), iVar3 != 0)) {
            FUN_004131f9((uint *)s_Symbol_already_defined_as_GLOBAL_00458ec8,(char *)s);
          }
          else {
            iVar3 = FUN_00436def((char *)s);
            if (iVar3 == 0) {
              iVar3 = FUN_00436e56((char *)s);
              if (iVar3 == 0) {
                iVar3 = FUN_00437037(s);
                if ((iVar3 != 0) && (DAT_0045f8fc == 1)) {
                  piVar4 = (int *)FUN_00439857(8);
                  uVar5 = strlen((char *)s);
                  iVar3 = FUN_00439857(uVar5 + 1);
                  *piVar4 = iVar3;
                  strcpy((char *)*piVar4,(char *)s);
                  piVar4[1] = *(int *)(PTR_DAT_0044f978 + 0x84);
                  *(int **)(PTR_DAT_0044f978 + 0x84) = piVar4;
                }
              }
              else {
                FUN_004131f9((uint *)s_Symbol_already_defined_as_XDEF_00458f0c,(char *)s);
              }
            }
            else {
              FUN_004131f9((uint *)s_Symbol_already_defined_as_XREF_00458eec,(char *)s);
            }
          }
        }
        else {
          FUN_004131f9((uint *)s_Symbol_already_defined_as_LOCAL_00458ea8,(char *)s);
        }
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}


/* ==== FUN_004368c3 @ 004368c3 ==== */

undefined4 FUN_004368c3(void)

{
  char cVar1;
  undefined4 uVar2;
  uint *s;
  int iVar3;
  int *piVar4;
  uint uVar5;
  
  if (PTR_DAT_0044f978 == &DAT_0044f878) {
    FUN_00413085((uint *)s_XREF_without_preceding_SECTION_d_00458f2c);
    uVar2 = 0;
  }
  else if (*PTR_DAT_0044f818 == '\0') {
    FUN_00413085((uint *)s_Missing_symbol_name_00458f58);
    uVar2 = 0;
  }
  else {
    FUN_0043b007(1);
    DAT_0045f860 = PTR_DAT_0044f818;
    while (*DAT_0045f860 != '\0') {
      s = (uint *)FUN_0043b448();
      if (s == (uint *)0x0) {
        return 0;
      }
      if ((*DAT_0045f860 != '\0') &&
         (cVar1 = *DAT_0045f860, DAT_0045f860 = DAT_0045f860 + 1, cVar1 != ',')) {
        FUN_00413085((uint *)s_Syntax_error_in_symbol_name_list_00458f6c);
        return 0;
      }
      if ((char)*s == DAT_0044f830) {
        FUN_004131f9((uint *)s_Local_symbol_names_cannot_be_use_00458f90,(char *)s);
      }
      else {
        iVar3 = FUN_00436d1b((char *)s);
        if (iVar3 == 0) {
          iVar3 = FUN_00436d85((char *)s);
          if (iVar3 == 0) {
            iVar3 = FUN_00436def((char *)s);
            if (iVar3 == 0) {
              iVar3 = FUN_00436e56((char *)s);
              if (iVar3 == 0) {
                iVar3 = FUN_00437220(s);
                if (iVar3 != 0) {
                  piVar4 = (int *)FUN_00439857(8);
                  uVar5 = strlen((char *)s);
                  iVar3 = FUN_00439857(uVar5 + 1);
                  *piVar4 = iVar3;
                  strcpy((char *)*piVar4,(char *)s);
                  piVar4[1] = *(int *)(PTR_DAT_0044f978 + 0x7c);
                  *(int **)(PTR_DAT_0044f978 + 0x7c) = piVar4;
                  *(int *)(DAT_0045fb8c + 0x20) = *(int *)(DAT_0045fb8c + 0x20) + 1;
                }
              }
              else {
                FUN_004131f9((uint *)s_Symbol_already_defined_as_XDEF_00459020,(char *)s);
              }
            }
            else {
              FUN_004131f9((uint *)s_Symbol_already_defined_as_XREF_00459000,(char *)s);
            }
          }
          else {
            FUN_004131f9((uint *)s_Symbol_already_defined_as_GLOBAL_00458fdc,(char *)s);
          }
        }
        else {
          FUN_004131f9((uint *)s_Symbol_already_defined_as_LOCAL_00458fbc,(char *)s);
        }
      }
      if (((DAT_0045f8fc == 2) && (DAT_0045fca8 != 0)) && (DAT_0045eadc != '\0')) {
        FUN_0043c34d();
        strcpy((char *)&DAT_00465a60,&DAT_00459040);
        DAT_00465a68 = FUN_0042456e(s);
        DAT_00465a70 = *(undefined4 *)(DAT_0045fb8c + 0x1c);
        DAT_00465a78 = 0xd4;
        FUN_0042447e(&DAT_00465a60);
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}


/* ==== FUN_00436b2e @ 00436b2e ==== */

undefined4 FUN_00436b2e(void)

{
  char cVar1;
  undefined4 uVar2;
  uint *s;
  int iVar3;
  int *piVar4;
  uint uVar5;
  
  if (PTR_DAT_0044f978 == &DAT_0044f878) {
    FUN_00413085((uint *)s_XDEF_without_preceding_SECTION_d_00459044);
    uVar2 = 0;
  }
  else if (*PTR_DAT_0044f818 == '\0') {
    FUN_00413085((uint *)s_Missing_symbol_name_00459070);
    uVar2 = 0;
  }
  else {
    FUN_0043b007(1);
    DAT_0045f860 = PTR_DAT_0044f818;
    while (*DAT_0045f860 != '\0') {
      s = (uint *)FUN_0043b448();
      if (s == (uint *)0x0) {
        return 0;
      }
      if ((*DAT_0045f860 != '\0') &&
         (cVar1 = *DAT_0045f860, DAT_0045f860 = DAT_0045f860 + 1, cVar1 != ',')) {
        FUN_00413085((uint *)s_Syntax_error_in_symbol_name_list_00459084);
        return 0;
      }
      if ((char)*s == DAT_0044f830) {
        FUN_004131f9((uint *)s_Local_symbol_names_cannot_be_use_004590a8,(char *)s);
      }
      else {
        iVar3 = FUN_00436d1b((char *)s);
        if (iVar3 == 0) {
          iVar3 = FUN_00436d85((char *)s);
          if (iVar3 == 0) {
            iVar3 = FUN_00436def((char *)s);
            if (iVar3 == 0) {
              iVar3 = FUN_00436e56((char *)s);
              if (iVar3 == 0) {
                iVar3 = FUN_00437418(s);
                if (iVar3 != 0) {
                  piVar4 = (int *)FUN_00439857(8);
                  uVar5 = strlen((char *)s);
                  iVar3 = FUN_00439857(uVar5 + 1);
                  *piVar4 = iVar3;
                  strcpy((char *)*piVar4,(char *)s);
                  piVar4[1] = *(int *)(PTR_DAT_0044f978 + 0x78);
                  *(int **)(PTR_DAT_0044f978 + 0x78) = piVar4;
                }
              }
              else {
                FUN_004131f9((uint *)s_Symbol_already_defined_as_XDEF_00459138,(char *)s);
              }
            }
            else {
              FUN_004131f9((uint *)s_Symbol_already_defined_as_XREF_00459118,(char *)s);
            }
          }
          else {
            FUN_004131f9((uint *)s_Symbol_already_defined_as_GLOBAL_004590f4,(char *)s);
          }
        }
        else {
          FUN_004131f9((uint *)s_Symbol_already_defined_as_LOCAL_004590d4,(char *)s);
        }
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}


/* ==== FUN_00436d1b @ 00436d1b ==== */

undefined4 __cdecl FUN_00436d1b(char *param_1)

{
  int iVar1;
  undefined4 *local_8;
  
  if (PTR_DAT_0044f978 != &DAT_0044f878) {
    for (local_8 = *(undefined4 **)(PTR_DAT_0044f978 + 0x80); local_8 != (undefined4 *)0x0;
        local_8 = (undefined4 *)local_8[1]) {
      if ((*(char *)*local_8 == *param_1) && (iVar1 = strcmp((char *)*local_8,param_1), iVar1 == 0))
      {
        return 1;
      }
    }
  }
  return 0;
}


/* ==== FUN_00436d85 @ 00436d85 ==== */

undefined4 __cdecl FUN_00436d85(char *param_1)

{
  int iVar1;
  undefined4 *local_8;
  
  if (PTR_DAT_0044f978 != &DAT_0044f878) {
    for (local_8 = *(undefined4 **)(PTR_DAT_0044f978 + 0x84); local_8 != (undefined4 *)0x0;
        local_8 = (undefined4 *)local_8[1]) {
      if ((*(char *)*local_8 == *param_1) && (iVar1 = strcmp((char *)*local_8,param_1), iVar1 == 0))
      {
        return 1;
      }
    }
  }
  return 0;
}


/* ==== FUN_00436def @ 00436def ==== */

undefined4 __cdecl FUN_00436def(char *param_1)

{
  int iVar1;
  undefined4 *local_8;
  
  if (PTR_DAT_0044f978 != &DAT_0044f878) {
    for (local_8 = *(undefined4 **)(PTR_DAT_0044f978 + 0x7c); local_8 != (undefined4 *)0x0;
        local_8 = (undefined4 *)local_8[1]) {
      if ((*(char *)*local_8 == *param_1) && (iVar1 = strcmp((char *)*local_8,param_1), iVar1 == 0))
      {
        return 1;
      }
    }
  }
  return 0;
}


/* ==== FUN_00436e56 @ 00436e56 ==== */

undefined4 __cdecl FUN_00436e56(char *param_1)

{
  int iVar1;
  undefined4 *local_8;
  
  if (PTR_DAT_0044f978 != &DAT_0044f878) {
    for (local_8 = *(undefined4 **)(PTR_DAT_0044f978 + 0x78); local_8 != (undefined4 *)0x0;
        local_8 = (undefined4 *)local_8[1]) {
      if ((*(char *)*local_8 == *param_1) && (iVar1 = strcmp((char *)*local_8,param_1), iVar1 == 0))
      {
        return 1;
      }
    }
  }
  return 0;
}


/* ==== FUN_00436ebd @ 00436ebd ==== */

undefined4 __cdecl FUN_00436ebd(uint *param_1)

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
  while( true ) {
    if (local_20c == (undefined4 *)0x0) {
      if (DAT_0045f8fc == 2) {
        FUN_004131f9((uint *)s_Symbol_undefined_on_pass_2_004591a8,(char *)param_1);
      }
      return 1;
    }
    if ((((char)*param_1 == *(char *)*local_20c) &&
        (iVar2 = strcmp((char *)param_1,(char *)*local_20c), iVar2 == 0)) &&
       ((undefined *)local_20c[0x10] == PTR_DAT_0044f978)) break;
    local_20c = (undefined4 *)local_20c[0x17];
  }
  if ((local_20c[6] & 0xc0) != 0) {
    FUN_004131f9((uint *)s_Symbol_already_defined_as_global_00459158,(char *)param_1);
    return 0;
  }
  if ((DAT_0044f790 != '\0') && ((local_20c[6] & 0x10) != 0)) {
    FUN_004131f9((uint *)s_SET_symbol_names_cannot_be_used_w_0045917c,(char *)param_1);
    return 0;
  }
  if ((DAT_0045f8fc == 2) && ((DAT_0045ea3c != '\0' && (DAT_0045ea70 == '\0')))) {
    FUN_004388eb((int)local_20c,2);
  }
  return 1;
}


/* ==== FUN_00437037 @ 00437037 ==== */

undefined4 __cdecl FUN_00437037(uint *param_1)

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
        if (DAT_0044f790 == '\0') {
          FUN_004131f9((uint *)s_Symbol_undefined_on_pass_2_00459250,(char *)param_1);
        }
        else if (DAT_0045eaf4 != '\0') {
          FUN_0041351d((uint *)s_Unresolved_external_reference_0045926c,(char *)param_1);
        }
      }
      return 1;
    }
    if (((char)*param_1 == *(char *)*local_20c) &&
       (iVar2 = strcmp((char *)param_1,(char *)*local_20c), iVar2 == 0)) {
      if ((undefined *)local_20c[0x10] == PTR_DAT_0044f978) {
        if ((DAT_0045ea98 == '\0') && ((local_20c[6] & 0x40) == 0)) {
          FUN_004131f9((uint *)s_Symbol_defined_in_current_sectio_004591c4,(char *)param_1);
          return 0;
        }
        if ((DAT_0044f790 != '\0') && ((local_20c[6] & 0x10) != 0)) {
          FUN_004131f9((uint *)s_SET_symbol_names_cannot_be_used_w_00459200,(char *)param_1);
          return 0;
        }
        local_20c[6] = local_20c[6] | 0x40;
        if (((DAT_0045f8fc == 2) && (DAT_0045ea3c != '\0')) && (DAT_0045ea70 == '\0')) {
          FUN_004388eb((int)local_20c,2);
        }
        return 1;
      }
      if ((local_20c[6] & 0x40) != 0) {
        FUN_004131f9((uint *)s_Symbol_already_defined_as_global_0045922c,(char *)param_1);
        return 0;
      }
    }
    local_20c = (undefined4 *)local_20c[0x17];
  } while( true );
}


/* ==== FUN_00437220 @ 00437220 ==== */

undefined4 __cdecl FUN_00437220(uint *param_1)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  uint local_21c;
  undefined4 *local_214;
  uint local_20c;
  uint local_208 [129];
  
  local_20c = 0;
  bVar1 = false;
  if (DAT_0045eaa0 != '\0') {
    strcpy((char *)local_208,(char *)param_1);
    FUN_0043b836((char *)local_208);
    param_1 = local_208;
  }
  uVar2 = FUN_00439b65((char *)param_1);
  local_214 = *(undefined4 **)(&DAT_0045fcc0 + uVar2 * 4);
  do {
    if (local_214 == (undefined4 *)0x0) {
      if (DAT_0045f8fc == 2) {
        if (DAT_0044f790 == '\0') {
          if (!bVar1) {
            FUN_004131f9((uint *)s_Symbol_undefined_on_pass_2_004592d8,(char *)param_1);
          }
        }
        else {
          if (local_20c == 0) {
            FUN_0043896d(param_1,1);
          }
          if (DAT_0045eaf4 != '\0') {
            FUN_0041351d((uint *)s_Unresolved_external_reference_004592b8,(char *)param_1);
          }
        }
      }
      return 1;
    }
    if (((char)*param_1 == *(char *)*local_214) &&
       (iVar3 = strcmp((char *)param_1,(char *)*local_214), iVar3 == 0)) {
      local_20c = local_214[6] & 0x10;
      if (((undefined *)local_214[0x10] == PTR_DAT_0044f978) && (local_20c == 0)) {
        FUN_004131f9((uint *)s_Symbol_already_defined_in_curren_0045928c,(char *)param_1);
        return 0;
      }
      if ((DAT_0045ea88 == '\0') && (local_20c == 0)) {
        local_21c = 0x80;
      }
      else {
        local_21c = 0x40;
      }
      if (((((local_214[6] & local_21c) != 0) && (bVar1 = true, DAT_0045f8fc == 2)) &&
          (DAT_0045ea3c != '\0')) && (DAT_0045ea70 == '\0')) {
        FUN_004388eb((int)local_214,2);
      }
    }
    local_214 = (undefined4 *)local_214[0x17];
  } while( true );
}


