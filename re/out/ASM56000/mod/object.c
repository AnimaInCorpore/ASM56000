/* object: 27 functions from ASM56000 */

/* ==== FUN_00420dc7 @ 00420dc7 ==== */

int * __cdecl FUN_00420dc7(int *param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int *local_14;
  int *local_10;
  char *local_c;
  int local_8;
  
  local_8 = 0;
  local_14 = (int *)0x0;
  local_10 = (int *)0x0;
  do {
    if (*DAT_0045f860 == '\0') {
      *param_1 = local_8;
      return local_14;
    }
    local_8 = local_8 + 1;
    if (((*DAT_0045f860 == '\'') || (*DAT_0045f860 == '\"')) || (*DAT_0045f860 == '[')) {
      DAT_0045f860 = FUN_0043b08d(DAT_0045f860,&DAT_0045f220);
      if (DAT_0045f860 == (char *)0x0) {
        return (int *)0x0;
      }
    }
    else {
      local_c = &DAT_0045f220;
      for (; (*DAT_0045f860 != '\0' && (*DAT_0045f860 != ',')); DAT_0045f860 = DAT_0045f860 + 1) {
        *local_c = *DAT_0045f860;
        local_c = local_c + 1;
      }
      *local_c = '\0';
    }
    if (local_14 == (int *)0x0) {
      local_14 = (int *)FUN_00439857(8);
      local_10 = local_14;
    }
    else {
      iVar3 = FUN_00439857(8);
      local_10[1] = iVar3;
      local_10 = (int *)local_10[1];
    }
    local_10[1] = 0;
    uVar2 = strlen(&DAT_0045f220);
    iVar3 = FUN_00439857(uVar2 + 1);
    *local_10 = iVar3;
    strcpy((char *)*local_10,&DAT_0045f220);
  } while ((*DAT_0045f860 == '\0') ||
          (cVar1 = *DAT_0045f860, DAT_0045f860 = DAT_0045f860 + 1, cVar1 == ','));
  FUN_00413085((uint *)s_Syntax_error_in_macro_argument_l_00455968);
  *param_1 = 0;
  FUN_00420f8c(local_14);
  return (int *)0x0;
}


/* ==== FUN_00420f6c @ 00420f6c ==== */

void __cdecl FUN_00420f6c(undefined *param_1)

{
  FUN_00420f8c(*(int **)(param_1 + 0x14));
  FUN_004398b5(param_1);
  return;
}


/* ==== FUN_00420f8c @ 00420f8c ==== */

void __cdecl FUN_00420f8c(int *param_1)

{
  int *piVar1;
  
  while (param_1 != (int *)0x0) {
    if (*param_1 != 0) {
      FUN_004398b5((undefined *)*param_1);
      *param_1 = 0;
    }
    piVar1 = (int *)param_1[1];
    FUN_004398b5((undefined *)param_1);
    param_1 = piVar1;
  }
  return;
}


/* ==== FUN_00420fd6 @ 00420fd6 ==== */

void FUN_00420fd6(void)

{
  int *piVar1;
  int *local_8;
  
  local_8 = DAT_0045fc64;
  DAT_0045fc64 = (int *)0x0;
  while( true ) {
    if (local_8 == (int *)0x0) {
      return;
    }
    if ((DAT_0045ea98 != '\0') && (local_8[1] != 0)) break;
    if (*local_8 != 0) {
      FUN_004398b5((undefined *)*local_8);
      *local_8 = 0;
    }
    piVar1 = (int *)local_8[2];
    FUN_004398b5((undefined *)local_8);
    local_8 = piVar1;
  }
  DAT_0045fc64 = local_8;
  return;
}


/* ==== FUN_00421052 @ 00421052 ==== */

void FUN_00421052(void)

{
  int *piVar1;
  int *local_c;
  
  local_c = DAT_0045fb78;
  while (local_c != (int *)0x0) {
    if (*local_c != 0) {
      FUN_004398b5((undefined *)*local_c);
      *local_c = 0;
    }
    piVar1 = (int *)local_c[4];
    FUN_004398b5((undefined *)local_c);
    local_c = piVar1;
  }
  DAT_0045fb78 = (int *)0x0;
  return;
}


/* ==== FUN_004210b0 @ 004210b0 ==== */

void __cdecl FUN_004210b0(undefined4 *param_1,int param_2)

{
  char *local_8;
  
  if ((DAT_0045eadc != '\0') && (1 < DAT_0045f8fc)) {
    FUN_0043c34d();
    if (param_2 == 0) {
      local_8 = &DAT_00455990;
    }
    else {
      local_8 = &DAT_0045598c;
    }
    strcpy((char *)&DAT_00465a60,local_8);
    if (param_2 != 0) {
      DAT_00465a68 = FUN_0042456e((uint *)*param_1);
    }
    DAT_00465a70 = 0xffffffff;
    DAT_00465a78 = 0xcb;
    DAT_00465a7c = 1;
    FUN_0042447e(&DAT_00465a60);
    DAT_00465884 = DAT_0045eb78;
    FUN_0042447e(&DAT_00465880);
  }
  return;
}


/* ==== FUN_00421160 @ 00421160 ==== */

void __cdecl FUN_00421160(char *param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = FUN_0043c450(param_1,param_2,1,DAT_0045fca8);
  if (iVar1 != 1) {
    FUN_00412fa0((uint *)s_I_O_error_writing_data_word_to_o_004559d4);
  }
  return;
}


/* ==== FUN_0042118f @ 0042118f ==== */

void FUN_0042118f(void)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  char *local_c;
  
  if (DAT_0045eaec == '\0') {
    FUN_00422b3a((uint *)PTR_s_GLOBAL_0044f87c,DAT_0044f8dc);
    DAT_0045eaf0 = 1;
  }
  if (DAT_0045fca8 != (void *)0x0) {
    iVar1 = fseek(DAT_0045fca8,DAT_0045fb90,0);
    if (iVar1 != 0) {
      FUN_00412fa0((uint *)s_Cannot_seek_to_start_of_object_d_00455a00);
    }
    if (DAT_0045eb00 == '\0') {
      strcpy(&DAT_0045f220,&DAT_0045f950);
      uVar2 = strlen(&DAT_0045f220);
      (&DAT_0045f220)[uVar2] = 0x20;
      pcVar3 = &DAT_0045f221 + uVar2;
      sprintf(pcVar3,s__04X__04X__04X_00455a24,DAT_0045fb54,DAT_0045fb58,DAT_0045eb84);
      uVar2 = strlen(pcVar3);
      pcVar3 = pcVar3 + uVar2;
      if (DAT_0045eb50 == '\0') {
        local_c = s_6_3_0_0044f9b8;
      }
      else {
        local_c = &DAT_00455a34;
      }
      sprintf(pcVar3,s__s__s_00455a3c,s_DSP56000_0044e068,local_c);
      if (DAT_0045fb5c != 0) {
        uVar2 = strlen(pcVar3);
        sprintf(pcVar3 + uVar2,&DAT_00455a44,DAT_0045fb5c);
      }
      FUN_00424733((uint *)&DAT_0045f220,0xffffffff);
    }
  }
  DAT_0045eb44 = 1;
  return;
}


/* ==== FUN_004212f9 @ 004212f9 ==== */

void FUN_004212f9(void)

{
  DAT_0045fbb0 = DAT_0045fb90 + DAT_0045fb94 * 4;
  DAT_0045fbc0 = DAT_0045fbb0 + DAT_0045fbb4 * 0xc;
  DAT_0045fbd0 = DAT_0045fbc0 + DAT_0045fbc4 * 0xc;
  if (DAT_0045fca8 != 0) {
    FUN_004217d2();
    if (DAT_0044f790 != '\0') {
      FUN_00421c3b();
    }
    FUN_004398b5(DAT_0045fba0);
    DAT_0045fba0 = (undefined *)0x0;
    DAT_0045fba8 = 0;
    FUN_004398b5(DAT_0045fbb8);
    DAT_0045fbb8 = (undefined *)0x0;
    DAT_0045fbbc = 0;
    FUN_00421d30();
    if (DAT_0045eadc != '\0') {
      FUN_00421ca4();
    }
    FUN_00422a74();
    FUN_004213bf();
  }
  return;
}


/* ==== FUN_004213bf @ 004213bf ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004213bf(void)

{
  int iVar1;
  int local_c;
  int local_8;
  
  iVar1 = fseek(DAT_0045fca8,0,0);
  if (iVar1 != 0) {
    FUN_00412fa0((uint *)s_Cannot_seek_to_start_of_object_f_00455a48);
  }
  DAT_00465a40 = 0x2c5;
  DAT_00465a44 = DAT_0045fb98;
  DAT_00465a48 = ~-(uint)(DAT_0045eb50 != '\0') & _DAT_0045f834;
  DAT_00465a4c = DAT_0045fbd0;
  DAT_00465a50 = DAT_0045fbd4;
  DAT_00465a54 = (-(uint)(DAT_0044f790 != '\0') & 0xfffffffc) + 0x3c;
  DAT_00465a58 = 0;
  if ((DAT_0044f790 == '\0') && (DAT_00465a58 = 1, DAT_0045eb84 == 0)) {
    DAT_00465a58 = 3;
  }
  if (DAT_0045eadc == '\0') {
    DAT_00465a58 = DAT_00465a58 | 4;
  }
  if (DAT_0045ea98 != '\0') {
    DAT_00465a58 = DAT_00465a58 | 0x10000;
  }
  if (((DAT_0045eb34 != '\0') && (DAT_0044f790 != '\0')) && (DAT_0045fca4 != 0)) {
    DAT_00465a58 = DAT_00465a58 | 0x20000;
  }
  iVar1 = FUN_0043c450((char *)&DAT_00465a40,0x1c,1,DAT_0045fca8);
  if (iVar1 != 1) {
    FUN_00412fa0((uint *)s_Cannot_write_file_header_to_obje_00455a6c);
  }
  if (DAT_0044f790 == '\0') {
    _DAT_00465b20 = 0;
    _DAT_00465b24 = 0;
    _DAT_00465b28 = DAT_0045f8f0 - DAT_0045f8e8;
    _DAT_00465b2c = DAT_0045f8f4 - DAT_0045f8ec;
    _DAT_00465b30 = 0;
    if (DAT_0045ea1c == '\0') {
      _DAT_00465b38 = -(uint)(DAT_0044f90c != 4) & DAT_0044f90c;
      _DAT_00465b34 = DAT_0045f8e8;
    }
    else {
      _DAT_00465b38 = -(uint)(DAT_0044f908 != 4) & DAT_0044f908;
      _DAT_00465b34 = DAT_0045f8e4;
    }
    _DAT_00465b34 = _DAT_00465b34 & 0xffff;
    _DAT_00465b3c = DAT_0045f8e8 & 0xffff;
    _DAT_00465b40 = -(uint)(DAT_0044f90c != 4) & DAT_0044f90c;
    _DAT_00465b44 = DAT_0045f8ec & 0xffff;
    if (DAT_0044f910 == 4) {
      local_8 = 1;
    }
    else {
      local_8 = DAT_0044f910;
    }
    _DAT_00465b48 = local_8;
    _DAT_00465b4c = DAT_0045f8f0 & 0xffff;
    _DAT_00465b50 = -(uint)(DAT_0044f914 != 4) & DAT_0044f914;
    _DAT_00465b54 = DAT_0045f8f4 & 0xffff;
    if (DAT_0044f918 == 4) {
      local_c = 1;
    }
    else {
      local_c = DAT_0044f918;
    }
    _DAT_00465b58 = local_c;
    iVar1 = FUN_0043c450(&DAT_00465b20,0x3c,1,DAT_0045fca8);
    if (iVar1 != 1) {
      FUN_00412fa0((uint *)s_Cannot_write_optional_header_to_o_00455ac0);
    }
  }
  else {
    _DAT_00465bc0 =
         (-(uint)(DAT_0044f790 != '\0') & 0xfffffffc) + 0x58 + DAT_0045fb98 * 0x34 +
         DAT_0045fb94 * 4 + DAT_0045fbb4 * 0xc + DAT_0045fbc4 * 0xc + DAT_0045fbd4 * 0x20 +
         (-(uint)(4 < DAT_0044f988) & DAT_0044f988);
    _DAT_00465bc4 = DAT_0045fb94;
    if (DAT_0045ea24 == '\0') {
      _DAT_00465bc8 = 0xffffffff;
    }
    _DAT_00465bcc = DAT_0045fb80 + 1;
    _DAT_00465bd0 = DAT_0045fb98;
    _DAT_00465bd4 = DAT_0045fbb4;
    _DAT_00465bd8 = DAT_0045fbc4;
    _DAT_00465bdc = DAT_0045ebc0;
    _DAT_00465be0 = DAT_0045ebe8;
    _DAT_00465be4 = DAT_0045fcb0;
    _DAT_00465be8 = DAT_0045fcb4;
    _DAT_00465bec = DAT_0045fcb8;
    _DAT_00465bf0 = 0;
    _DAT_00465bf4 = DAT_0045fca4;
    iVar1 = FUN_0043c450(&DAT_00465bc0,0x38,1,DAT_0045fca8);
    if (iVar1 != 1) {
      FUN_00412fa0((uint *)s_Cannot_write_optional_header_to_o_00455a94);
    }
  }
  return;
}


/* ==== FUN_004217d2 @ 004217d2 ==== */

void FUN_004217d2(void)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  
  bVar3 = DAT_0044f790 != '\0';
  if (DAT_0045fb98 != 0) {
    FUN_00421865();
    if (DAT_0044f790 == '\0') {
      FUN_00421ac1();
    }
    iVar1 = fseek(DAT_0045fca8,(-(uint)bVar3 & 0xfffffffc) + 0x58,0);
    if (iVar1 != 0) {
      FUN_00412fa0((uint *)s_Cannot_seek_to_start_of_section_h_00455aec);
    }
    uVar2 = FUN_0043c481(DAT_0045fba0,0x34,DAT_0045fb98,DAT_0045fca8);
    if (uVar2 != DAT_0045fb98) {
      FUN_00412fa0((uint *)s_Cannot_write_section_headers_to_o_00455b14);
    }
  }
  return;
}


/* ==== FUN_00421865 @ 00421865 ==== */

void FUN_00421865(void)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  bool bVar5;
  bool bVar6;
  int local_24;
  int *local_20;
  undefined4 *local_1c;
  int local_10;
  int local_8;
  
  local_10 = 0;
  local_24 = 0;
  local_8 = 0;
  piVar1 = (int *)FUN_00439857(DAT_0045fb9c * 0x34);
  if (DAT_0044f790 == '\0') {
    local_1c = DAT_0045fba4 + 2;
    local_20 = piVar1 + 0x1a;
  }
  else {
    local_1c = DAT_0045fba4;
    local_20 = piVar1;
  }
  for (; local_1c < DAT_0045fba4 + DAT_0045fb98; local_1c = local_1c + 1) {
    piVar3 = (int *)*local_1c;
    if ((piVar3[0xc] & 1U) == 0) {
      bVar5 = (piVar3[0xc] & 8U) != 0;
      bVar6 = (piVar3[0xc] & 0x80U) != 0;
      if ((piVar3[0xc] & 0x400U) == 0) {
        piVar3[4] = piVar3[2];
      }
      else {
        piVar3[4] = piVar3[4] - piVar3[2];
        piVar3[5] = 4;
      }
      piVar3[0xc] = piVar3[0xc] & 0xfff8ffff;
      if ((bVar5) || (bVar6)) {
        piVar3[7] = 0;
      }
      else {
        piVar3[7] = DAT_0045fb90 + local_10 * 4;
        local_10 = local_10 + piVar3[6];
      }
      if ((bVar5) || (bVar6)) {
        piVar3[8] = 0;
        piVar3[10] = 0;
      }
      else {
        piVar3[8] = DAT_0045fbb0 + local_24 * 0xc;
        if (DAT_0044f790 == '\0') {
          piVar3[10] = 0;
        }
        local_24 = local_24 + piVar3[10];
      }
      if (bVar5) {
        piVar3[9] = 0;
        piVar3[0xb] = 0;
      }
      else {
        piVar3[9] = DAT_0045fbc0 + local_8 * 0xc;
        if (DAT_0045eadc == '\0') {
          piVar3[0xb] = 0;
        }
        local_8 = local_8 + piVar3[0xb];
      }
      if (*piVar3 != 0) {
        FUN_0043c4b2((undefined1 *)piVar3,4,2);
      }
      piVar4 = local_20;
      for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
        *piVar4 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar4 = piVar4 + 1;
      }
      local_20 = local_20 + 0xd;
    }
  }
  DAT_0045fb98 = DAT_0045fb9c;
  FUN_004398b5((undefined *)DAT_0045fba4);
  DAT_0045fba4 = (undefined4 *)0x0;
  DAT_0045fba0 = piVar1;
  return;
}


/* ==== FUN_00421ac1 @ 00421ac1 ==== */

void FUN_00421ac1(void)

{
  char *pcVar1;
  char *pcVar2;
  int local_38;
  
  memset(DAT_0045fba0,0,0x68);
  pcVar2 = DAT_0045fba0;
  strcpy(DAT_0045fba0,s__text_0044fa70);
  FUN_0043c4b2(pcVar2,4,2);
  *(uint *)(pcVar2 + 0x10) = DAT_0045f8e8 & 0xffff;
  *(undefined4 *)(pcVar2 + 8) = *(undefined4 *)(pcVar2 + 0x10);
  *(uint *)(pcVar2 + 0x14) = -(uint)(DAT_0044f90c != 4) & DAT_0044f90c;
  *(undefined4 *)(pcVar2 + 0xc) = *(undefined4 *)(pcVar2 + 0x14);
  *(uint *)(pcVar2 + 0x18) = DAT_0045f8f0 - DAT_0045f8e8;
  *(undefined4 *)(pcVar2 + 0x20) = DAT_0045fbb0;
  *(undefined4 *)(pcVar2 + 0x24) = DAT_0045fbc0;
  pcVar2[0x28] = '\0';
  pcVar2[0x29] = '\0';
  pcVar2[0x2a] = '\0';
  pcVar2[0x2b] = '\0';
  *(uint *)(pcVar2 + 0x2c) = -(uint)(DAT_0045eadc != '\0') & DAT_0045fbc4;
  pcVar2[0x30] = ' ';
  pcVar1 = DAT_0045fba0;
  pcVar2[0x31] = '\0';
  pcVar2[0x32] = '\0';
  pcVar2[0x33] = '\0';
  pcVar2 = DAT_0045fba0 + 0x34;
  strcpy(pcVar2,s__data_0044fa80);
  FUN_0043c4b2(pcVar2,4,2);
  *(uint *)(pcVar1 + 0x44) = DAT_0045f8ec & 0xffff;
  *(undefined4 *)(pcVar1 + 0x3c) = *(undefined4 *)(pcVar1 + 0x44);
  if (DAT_0044f910 == 4) {
    local_38 = 1;
  }
  else {
    local_38 = DAT_0044f910;
  }
  *(int *)(pcVar1 + 0x48) = local_38;
  *(int *)(pcVar1 + 0x40) = local_38;
  *(uint *)(pcVar1 + 0x4c) = DAT_0045f8f4 - DAT_0045f8ec;
  *(undefined4 *)(pcVar1 + 0x54) = DAT_0045fbb0;
  pcVar1[100] = '@';
  pcVar1[0x65] = '\0';
  pcVar1[0x66] = '\0';
  pcVar1[0x67] = '\0';
  return;
}


/* ==== FUN_00421c3b @ 00421c3b ==== */

void FUN_00421c3b(void)

{
  int iVar1;
  uint uVar2;
  
  if (DAT_0045fbb4 != 0) {
    iVar1 = fseek(DAT_0045fca8,DAT_0045fbb0,0);
    if (iVar1 != 0) {
      FUN_00412fa0((uint *)s_Cannot_seek_to_start_of_relocati_00455b40);
    }
    uVar2 = FUN_0043c481(DAT_0045fbb8,0xc,DAT_0045fbb4,DAT_0045fca8);
    if (uVar2 != DAT_0045fbb4) {
      FUN_00412fa0((uint *)s_Cannot_write_relocation_entries_t_00455b6c);
    }
  }
  return;
}


/* ==== FUN_00421ca4 @ 00421ca4 ==== */

void FUN_00421ca4(void)

{
  int iVar1;
  uint uVar2;
  
  if (DAT_0045fbc4 != 0) {
    iVar1 = fseek(DAT_0045fca8,DAT_0045fbc0,0);
    if (iVar1 != 0) {
      FUN_00412fa0((uint *)s_Cannot_seek_to_start_of_line_num_00455b9c);
    }
    uVar2 = FUN_0043c481(DAT_0045fbc8,0xc,DAT_0045fbc4,DAT_0045fca8);
    if (uVar2 != DAT_0045fbc4) {
      FUN_00412fa0((uint *)s_Cannot_write_line_number_entries_00455bc8);
    }
    FUN_004398b5(DAT_0045fbc8);
    DAT_0045fbc8 = (char *)0x0;
    DAT_0045fbcc = 0;
  }
  return;
}


/* ==== FUN_00421d30 @ 00421d30 ==== */

void FUN_00421d30(void)

{
  int iVar1;
  uint uVar2;
  int *local_8;
  
  if (DAT_0045fbd4 != 0) {
    if (DAT_0044f790 == '\0') {
      FUN_00421e32();
      FUN_004229f3();
      FUN_004225ac();
    }
    for (local_8 = DAT_0045fbd8; local_8 < DAT_0045fbd8 + DAT_0045fbd4 * 8;
        local_8 = local_8 + local_8[7] * 8 + 8) {
      if (*local_8 != 0) {
        FUN_0043c4b2((undefined1 *)local_8,4,2);
      }
    }
    iVar1 = fseek(DAT_0045fca8,DAT_0045fbd0,0);
    if (iVar1 != 0) {
      FUN_00412fa0((uint *)s_Cannot_seek_to_start_of_symbol_t_00455bf8);
    }
    uVar2 = FUN_0043c481((char *)DAT_0045fbd8,0x20,DAT_0045fbd4,DAT_0045fca8);
    if (uVar2 != DAT_0045fbd4) {
      FUN_00412fa0((uint *)s_Cannot_write_symbols_to_object_f_00455c20);
    }
    FUN_004398b5((undefined *)DAT_0045fbd8);
    DAT_0045fbd8 = (int *)0x0;
    DAT_0045fbdc = 0;
  }
  return;
}


/* ==== FUN_00421e32 @ 00421e32 ==== */

void FUN_00421e32(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int local_24;
  int local_20;
  int local_1c;
  undefined4 *local_18;
  int local_14;
  int local_8;
  
  local_14 = 0;
  local_8 = 0;
  puVar1 = (undefined4 *)FUN_00439857((DAT_0045fbd4 + 2) * 0x20);
  local_1c = 0;
  local_18 = puVar1;
  do {
    iVar3 = local_1c;
    if (DAT_0045fbd4 <= local_1c) {
      for (local_1c = 0; local_1c < DAT_0045fbd4; local_1c = local_1c + 1) {
        puVar6 = (undefined4 *)((int)DAT_0045fbd8 + local_1c * 0x20);
        if ((((puVar6[6] == 2) || (puVar6[6] == 0xd2)) || (puVar6[6] == 0xd3)) &&
           ((puVar6[5] & 0x30) != 0x20)) {
          puVar7 = puVar6;
          puVar8 = local_18;
          for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar8 = *puVar7;
            puVar7 = puVar7 + 1;
            puVar8 = puVar8 + 1;
          }
          for (local_20 = 0; local_18 = local_18 + 8, local_20 < (int)puVar6[7];
              local_20 = local_20 + 1) {
            local_1c = local_1c + 1;
            puVar7 = (undefined4 *)((int)DAT_0045fbd8 + local_1c * 0x20);
            puVar8 = local_18;
            for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar8 = *puVar7;
              puVar7 = puVar7 + 1;
              puVar8 = puVar8 + 1;
            }
          }
        }
        else {
          local_1c = local_1c + puVar6[7];
        }
      }
      FUN_004398b5((undefined *)DAT_0045fbd8);
      DAT_0045fbd8 = puVar1;
      return;
    }
    puVar6 = (undefined4 *)((int)DAT_0045fbd8 + local_1c * 0x20);
    if ((puVar6[6] == 0x67) || (puVar6[6] == 200)) {
      iVar2 = (int)local_18 - (int)puVar1 >> 5;
      puVar7 = puVar6;
      puVar8 = local_18;
      for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      for (local_20 = 0; local_18 = local_18 + 8, iVar4 = local_1c, local_20 < (int)puVar6[7];
          local_20 = local_20 + 1) {
        local_1c = local_1c + 1;
        puVar7 = (undefined4 *)((int)DAT_0045fbd8 + local_1c * 0x20);
        puVar8 = local_18;
        for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar8 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar8 = puVar8 + 1;
        }
      }
      while (local_1c = iVar4 + 1, local_1c < DAT_0045fbd4) {
        puVar6 = (undefined4 *)((int)DAT_0045fbd8 + local_1c * 0x20);
        if (puVar6[6] == 0x65) {
          local_14 = local_14 + (-(uint)(*(char *)((int)puVar6 + 1) != 'b') & 0xfffffffe) + 1;
        }
        if (puVar6[6] == 100) {
          local_8 = local_8 + (-(uint)(*(char *)((int)puVar6 + 1) != 'b') & 0xfffffffe) + 1;
        }
        if ((puVar6[6] == 0x67) || (puVar6[6] == 200)) break;
        if (((puVar6[5] & 0x30) == 0x20) ||
           (((puVar6[6] != 3 || (((local_14 != 0 || (local_8 != 0)) && (puVar6[5] != 0)))) &&
            (((puVar6[6] != 2 && (puVar6[6] != 0xd2)) && (puVar6[6] != 0xd3)))))) {
          puVar7 = puVar6;
          puVar8 = local_18;
          for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar8 = *puVar7;
            puVar7 = puVar7 + 1;
            puVar8 = puVar8 + 1;
          }
          for (local_20 = 0; local_18 = local_18 + 8, iVar4 = local_1c, local_20 < (int)puVar6[7];
              local_20 = local_20 + 1) {
            local_1c = local_1c + 1;
            puVar7 = (undefined4 *)((int)DAT_0045fbd8 + local_1c * 0x20);
            puVar8 = local_18;
            for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
              *puVar8 = *puVar7;
              puVar7 = puVar7 + 1;
              puVar8 = puVar8 + 1;
            }
          }
        }
        else {
          iVar4 = local_1c + puVar6[7];
        }
      }
      for (local_20 = iVar3; local_20 < local_1c; local_20 = local_20 + 1) {
        puVar6 = (undefined4 *)((int)DAT_0045fbd8 + local_20 * 0x20);
        if (puVar6[6] == 0x65) {
          local_14 = local_14 + (-(uint)(*(char *)((int)puVar6 + 1) != 'b') & 0xfffffffe) + 1;
        }
        if (puVar6[6] == 100) {
          local_8 = local_8 + (-(uint)(*(char *)((int)puVar6 + 1) != 'b') & 0xfffffffe) + 1;
        }
        if ((puVar6[6] == 3) &&
           ((((local_14 == 0 && (local_8 == 0)) || (puVar6[5] == 0)) && ((puVar6[5] & 0x30) != 0x20)
            ))) {
          puVar7 = puVar6;
          puVar8 = local_18;
          for (iVar5 = 8; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar8 = *puVar7;
            puVar7 = puVar7 + 1;
            puVar8 = puVar8 + 1;
          }
          for (local_24 = 0; local_18 = local_18 + 8, local_24 < (int)puVar6[7];
              local_24 = local_24 + 1) {
            local_20 = local_20 + 1;
            puVar7 = (undefined4 *)((int)DAT_0045fbd8 + local_20 * 0x20);
            puVar8 = local_18;
            for (iVar5 = 8; iVar5 != 0; iVar5 = iVar5 + -1) {
              *puVar8 = *puVar7;
              puVar7 = puVar7 + 1;
              puVar8 = puVar8 + 1;
            }
          }
        }
        else {
          local_20 = local_20 + puVar6[7];
        }
      }
      iVar5 = (int)local_18 - (int)puVar1 >> 5;
      FUN_00422378(iVar2,iVar2,iVar5,iVar5,(int)puVar1,(int)puVar1);
      FUN_00422378(iVar3,iVar2,local_1c,iVar5,(int)DAT_0045fbd8,(int)puVar1);
      local_1c = iVar4;
    }
    else if (((puVar6[5] & 0x30) == 0x20) ||
            (((puVar6[6] != 2 && (puVar6[6] != 0xd2)) && (puVar6[6] != 0xd3)))) {
      puVar7 = puVar6;
      puVar8 = local_18;
      for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      for (local_20 = 0; local_18 = local_18 + 8, local_20 < (int)puVar6[7]; local_20 = local_20 + 1
          ) {
        local_1c = local_1c + 1;
        puVar7 = (undefined4 *)((int)DAT_0045fbd8 + local_1c * 0x20);
        puVar8 = local_18;
        for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar8 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar8 = puVar8 + 1;
        }
      }
    }
    local_1c = local_1c + 1;
  } while( true );
}


/* ==== FUN_00422378 @ 00422378 ==== */

void __cdecl FUN_00422378(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int *piVar1;
  int iVar2;
  int *local_18;
  int local_14;
  int local_10;
  
  local_10 = param_1;
  do {
    if (param_3 <= local_10) {
      return;
    }
    piVar1 = (int *)(param_5 + local_10 * 0x20);
    if ((param_1 == param_2) ||
       ((((piVar1[6] == 2 || (piVar1[6] == 0xd2)) || (piVar1[6] == 0xd3)) &&
        ((piVar1[5] & 0x30U) != 0x20)))) {
      if (((((piVar1[6] != 10) && (piVar1[6] != 0xc)) && (piVar1[6] != 0xf)) &&
          ((0 < piVar1[7] && (piVar1[8] != 0)))) &&
         (((piVar1[5] & 0x1000fU) == 8 ||
          ((((piVar1[5] & 0x1000fU) == 9 || ((piVar1[5] & 0x1000fU) == 10)) || (piVar1[6] == 0x66)))
          ))) {
        for (local_14 = param_2; local_14 < param_4; local_14 = local_14 + 1) {
          iVar2 = param_6 + local_14 * 0x20;
          if (((*(int *)(iVar2 + 0x18) == 10) || (*(int *)(iVar2 + 0x18) == 0xc)) ||
             (*(int *)(iVar2 + 0x18) == 0xf)) {
            if ((piVar1[6] == 0x66) ||
               ((*(uint *)(iVar2 + 0x14) & 0x1000f) == (piVar1[5] & 0x1000fU))) {
              if (*(int *)(iVar2 + 0x20) == piVar1[8]) {
                piVar1[8] = local_14;
                break;
              }
              local_14 = local_14 + *(int *)(iVar2 + 0x1c);
            }
            else {
              local_14 = local_14 + *(int *)(iVar2 + 0x1c);
            }
          }
          else {
            local_14 = local_14 + *(int *)(iVar2 + 0x1c);
          }
        }
        if (param_4 <= local_14) {
          local_18 = piVar1;
          if (*piVar1 == 0) {
            if (((uint)piVar1[1] < 5) || (DAT_0045fbe8 <= piVar1[1])) {
              local_18 = (int *)0x0;
            }
            else {
              local_18 = (int *)(DAT_0045fbe4 + piVar1[1]);
            }
          }
          if (local_18 == (int *)0x0) {
            FUN_00413085((uint *)s_Symbol_tag_mismatch_00455c58);
          }
          else {
            FUN_004131f9((uint *)s_Symbol_tag_mismatch_00455c44,(char *)local_18);
          }
        }
      }
      iVar2 = piVar1[7];
    }
    else {
      iVar2 = piVar1[7];
    }
    local_10 = local_10 + iVar2;
    local_10 = local_10 + 1;
  } while( true );
}


/* ==== FUN_004225ac @ 004225ac ==== */

void FUN_004225ac(void)

{
  int iVar1;
  int iVar2;
  int local_48;
  int local_40;
  int local_3c;
  int local_34;
  int local_30;
  int local_28;
  int local_24;
  int local_20;
  int local_18;
  int local_10;
  int local_c;
  int local_8;
  
  local_3c = -1;
  local_40 = -1;
  local_18 = 0;
  local_c = 0;
  local_24 = 0;
  local_20 = 0;
  local_30 = 0;
  local_28 = 0;
  local_10 = 0;
  local_8 = 0;
  local_48 = 0;
  if (DAT_0045fbd4 != 0) {
    for (local_34 = 0; local_34 < DAT_0045fbd4; local_34 = local_34 + *(int *)(iVar2 + 0x1c) + 1) {
      iVar2 = DAT_0045fbd8 + local_34 * 0x20;
      if (*(int *)(iVar2 + 0x18) == 0x65) {
        local_18 = local_18 + (-(uint)(*(char *)(iVar2 + 1) != 'b') & 0xfffffffe) + 1;
      }
      if (*(int *)(iVar2 + 0x18) == 100) {
        local_c = local_c + (-(uint)(*(char *)(iVar2 + 1) != 'b') & 0xfffffffe) + 1;
      }
      if ((*(int *)(iVar2 + 0x18) == 0x67) || (*(int *)(iVar2 + 0x18) == 200)) {
        if (local_20 != 0) {
          *(int *)(local_20 + 0x10) = local_3c;
        }
        if (local_28 != 0) {
          *(int *)(local_28 + 0x10) = local_3c;
        }
        if (local_10 != 0) {
          *(int *)(local_10 + 0x10) = local_3c;
        }
        if (local_8 != 0) {
          *(int *)(local_8 + 0x10) = local_3c;
        }
        if (local_48 != 0) {
          *(int *)(local_48 + 0x10) = local_3c;
        }
        if (local_30 != 0) {
          *(int *)(local_30 + 0x10) = local_3c;
        }
        local_3c = -1;
        iVar1 = iVar2;
        if (local_24 != 0) {
          *(int *)(local_24 + 8) = local_34;
        }
      }
      else {
        iVar1 = local_24;
        if (*(int *)(iVar2 + 0x18) == 0x65) {
          if (*(char *)(iVar2 + 1) == 'b') {
            if (local_28 != 0) {
              *(int *)(local_28 + 0x10) = local_34;
            }
            local_28 = iVar2 + 0x20;
          }
        }
        else if ((*(int *)(iVar2 + 0x18) == 100) && (*(char *)(iVar2 + 1) == 'b')) {
          if (local_10 != 0) {
            *(int *)(local_10 + 0x10) = local_34;
          }
          local_10 = iVar2 + 0x20;
        }
        else if (*(int *)(iVar2 + 0x18) == -1) {
          if (local_20 == 0) {
            FUN_00413085((uint *)s_No_previous_function_declaration_00455c6c);
          }
          *(int *)(local_20 + 4) = *(int *)(iVar2 + 8) - *(int *)(local_20 + -0x18);
        }
        else if (*(int *)(iVar2 + 0x18) == 0xc9) {
          if (local_8 != 0) {
            *(int *)(local_8 + 0x10) = local_34;
          }
          local_8 = iVar2 + 0x20;
        }
        else if (*(int *)(iVar2 + 0x18) == 0xcb) {
          if (local_48 != 0) {
            *(int *)(local_48 + 0x10) = local_34;
          }
          local_48 = iVar2 + 0x20;
        }
        else if ((((*(int *)(iVar2 + 0x18) == 3) && (local_18 == 0)) && (local_c == 0)) &&
                (((*(uint *)(iVar2 + 0x14) & 0x30) != 0x20 && (local_3c < 0)))) {
          local_3c = local_34;
        }
      }
      local_24 = iVar1;
      if (((*(uint *)(iVar2 + 0x14) & 0x30) == 0x20) && (0 < *(int *)(iVar2 + 0x10))) {
        if (DAT_0045fbc8 != 0) {
          iVar1 = *(int *)(iVar2 + 0x2c);
          if (DAT_0045ea98 != '\0') {
            *(int *)(DAT_0045fbc8 + iVar1 * 0xc) = local_34;
          }
          *(int *)(iVar2 + 0x2c) = DAT_0045fbc0 + iVar1 * 0xc;
        }
        if (local_20 != 0) {
          *(int *)(local_20 + 0x10) = local_34;
        }
        local_20 = iVar2 + 0x20;
      }
      if (((*(int *)(iVar2 + 0x18) == 10) || (*(int *)(iVar2 + 0x18) == 0xc)) ||
         (*(int *)(iVar2 + 0x18) == 0xf)) {
        if (local_30 != 0) {
          *(int *)(local_30 + 0x10) = local_34;
        }
        local_30 = iVar2 + 0x20;
      }
      if ((((local_40 < 0) && ((*(int *)(iVar2 + 0x18) == 2 || (*(int *)(iVar2 + 0x18) == 0xd2))))
          && (*(int *)(iVar2 + 0x10) != 0)) && ((*(uint *)(iVar2 + 0x14) & 0x30) != 0x20)) {
        local_40 = local_34;
      }
    }
    for (local_34 = 0; local_34 < DAT_0045fbd4; local_34 = local_34 + *(int *)(iVar2 + 0x1c) + 1) {
      iVar2 = DAT_0045fbd8 + local_34 * 0x20;
      if (((*(int *)(iVar2 + 0x18) == 10) || (*(int *)(iVar2 + 0x18) == 0xc)) ||
         (*(int *)(iVar2 + 0x18) == 0xf)) {
        *(undefined4 *)(iVar2 + 0x20) = 0;
      }
    }
    if (local_20 != 0) {
      *(int *)(local_20 + 0x10) = local_3c;
    }
    if (local_28 != 0) {
      *(int *)(local_28 + 0x10) = local_3c;
    }
    if (local_10 != 0) {
      *(int *)(local_10 + 0x10) = local_3c;
    }
    if (local_8 != 0) {
      *(int *)(local_8 + 0x10) = local_3c;
    }
    if (local_48 != 0) {
      *(int *)(local_48 + 0x10) = local_3c;
    }
    if (local_30 != 0) {
      *(int *)(local_30 + 0x10) = local_3c;
    }
    if (local_24 != 0) {
      *(int *)(local_24 + 8) = local_40;
    }
  }
  return;
}


/* ==== FUN_004229f3 @ 004229f3 ==== */

void FUN_004229f3(void)

{
  FUN_0043c34d();
  strcpy((char *)&DAT_00465a60,s_etext_00455c90);
  DAT_00465a68 = DAT_0045f8f0;
  DAT_00465a6c = 0;
  DAT_00465a70 = 0xffffffff;
  DAT_00465a78 = 2;
  FUN_0042447e(&DAT_00465a60);
  memset(&DAT_00465a60,0,8);
  strcpy((char *)&DAT_00465a60,&DAT_00455c98);
  FUN_0042447e(&DAT_00465a60);
  return;
}


/* ==== FUN_00422a74 @ 00422a74 ==== */

void FUN_00422a74(void)

{
  int iVar1;
  uint uVar2;
  
  DAT_0045fbe0 = DAT_0045fbd0 + DAT_0045fbd4 * 0x20;
  if (4 < DAT_0044f988) {
    iVar1 = fseek(DAT_0045fca8,DAT_0045fbe0,0);
    if (iVar1 != 0) {
      FUN_00412fa0((uint *)s_Cannot_seek_to_start_of_string_t_00455c9c);
    }
    *DAT_0045fbe4 = DAT_0044f988;
    FUN_0043c4b2((undefined1 *)DAT_0045fbe4,4,1);
    uVar2 = FUN_0043c37e((char *)DAT_0045fbe4,1,DAT_0044f988,DAT_0045fca8);
    if (uVar2 != DAT_0044f988) {
      FUN_00412fa0((uint *)s_Cannot_write_string_table_to_obj_00455cc4);
    }
    FUN_004398b5((undefined *)DAT_0045fbe4);
    DAT_0045fbe4 = (uint *)0x0;
    DAT_0045fbe8 = 0;
  }
  return;
}


/* ==== FUN_00422b3a @ 00422b3a ==== */

void __cdecl FUN_00422b3a(uint *param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  char *local_70;
  uint *local_6c;
  uint *local_68;
  undefined4 local_64;
  uint local_60;
  undefined4 local_5c;
  int local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  undefined4 local_2c;
  undefined4 local_24;
  undefined4 local_20;
  uint local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  if ((DAT_0045f8fc == 2) && (DAT_0045fca8 != 0)) {
    if (param_2 == (int *)0x0) {
      param_2 = DAT_0045fb8c;
    }
    if (param_1 == (uint *)0x0) {
      param_1 = *(uint **)(PTR_DAT_0044f978 + 4);
    }
    if ((*(uint *)(param_2[9] + 0x30) & 1) != 0) {
      return;
    }
    if (DAT_0044f790 == '\0') {
      if (((*(uint *)(param_2[9] + 0x30) & 8) == 0) && ((*(uint *)(param_2[9] + 0x30) & 0x80) == 0))
      {
        if (*param_2 == 0) {
          local_68 = (uint *)&DAT_0044fa78;
        }
        else {
          local_68 = (uint *)&DAT_0044fa88;
        }
        local_6c = local_68;
      }
      else {
        local_6c = (uint *)&DAT_00455cf0;
      }
      param_1 = local_6c;
    }
    if ((DAT_0045eadc != '\0') && (DAT_0045fb6c != 0)) {
      *(uint *)(param_2[9] + 0x30) = *(uint *)(param_2[9] + 0x30) | 0x1000;
    }
    if ((DAT_0045eaa8 != '\0') && (DAT_0045f8c0 != DAT_0045f8cc)) {
      *(uint *)(param_2[9] + 0x30) = *(uint *)(param_2[9] + 0x30) | 0x2000;
    }
    FUN_0043c34d();
    memset(&local_24,0,0x20);
    memset(&local_64,0,0x20);
    memset(&local_44,0,0x20);
    uVar1 = strlen((char *)param_1);
    if (uVar1 < 8) {
      strcpy((char *)&DAT_00465a60,(char *)param_1);
      strcpy((char *)param_2[9],(char *)param_1);
    }
    else {
      iVar2 = FUN_0042456e(param_1);
      *(int *)(param_2[9] + 4) = iVar2;
      DAT_00465a64 = *(undefined4 *)(param_2[9] + 4);
    }
    DAT_00465a68 = *(undefined4 *)(param_2[9] + 8);
    DAT_00465a6c = *(undefined4 *)(param_2[9] + 0xc);
    DAT_00465a70 = param_2[7];
    DAT_00465a78 = 3;
    DAT_00465a7c = 1;
    if (DAT_0044f790 != '\0') {
      DAT_00465a7c = 2;
      if (DAT_0045ebcc != 0) {
        DAT_00465a7c = 3;
      }
      if (DAT_00465b60 != 4) {
        DAT_00465a7c = DAT_00465a7c + 1;
      }
    }
    FUN_0042447e(&DAT_00465a60);
    DAT_00465880 = *(undefined4 *)(param_2[9] + 0x18);
    DAT_00465884 = *(undefined4 *)(param_2[9] + 0x28);
    DAT_00465888 = *(undefined4 *)(param_2[9] + 0x2c);
    FUN_0042447e(&DAT_00465880);
    if (DAT_0044f790 != '\0') {
      local_24 = *(undefined4 *)(PTR_DAT_0044f978 + 8);
      if ((*(uint *)(PTR_DAT_0044f978 + 0xc) & 0x20) == 0) {
        local_20 = *(undefined4 *)(PTR_DAT_0044f97c + 8);
      }
      else {
        local_20 = *(undefined4 *)(DAT_0045fb7c + 8);
      }
      local_18 = *param_2;
      local_14 = param_2[1];
      local_10 = param_2[2];
      local_c = param_2[3];
      uVar1 = -(uint)(DAT_0044f798 != '\0') & 0x1000 | -(uint)(DAT_0044f7ac != '\0') & 0x100 |
              -(uint)(DAT_0045eaa4 != '\0') & 0x200 | -(uint)(DAT_0045eaa8 != '\0') & 0x800 |
              *(uint *)(PTR_DAT_0044f978 + 0xc) & 0x20;
      local_1c = uVar1;
      if (DAT_0045ebcc != 0) {
        local_1c = uVar1 | 0x2000;
        if (DAT_0045eb3c != '\0') {
          local_1c = uVar1 | 0x42000;
        }
        local_64 = DAT_0045ebc0;
        local_60 = DAT_0045ebcc;
        local_5c = DAT_0045ebd0;
      }
      if (DAT_00465b60 != 4) {
        local_1c = local_1c | (uint)((byte)(-(uint)(DAT_0044f794 != '\0') >> 8) & 0x80 | 0x40) << 8;
        local_34 = DAT_0045ebe8;
        local_44 = DAT_00465b60;
        local_40 = DAT_00465b64;
        local_3c = DAT_00465b68;
        local_38 = DAT_00465b6c;
        if (DAT_0045f630 == '\0') {
          local_30 = -1;
        }
        else {
          local_30 = FUN_0042456e((uint *)&DAT_0045f630);
        }
        local_2c = *DAT_0045f8c0;
        if ((DAT_0045ebcc != 0) && (DAT_0044f7c0 == '\0')) {
          local_60 = local_60 | 0x2000;
        }
      }
      FUN_0042447e(&local_24);
      if (DAT_0045ebcc != 0) {
        FUN_0042447e(&local_64);
      }
      if (DAT_00465b60 != 4) {
        FUN_0042447e(&local_44);
        DAT_0045f630 = '\0';
        DAT_00465b64 = 4;
        DAT_00465b60 = 4;
        DAT_00465b68 = 0;
        DAT_00465b6c = 0;
      }
    }
  }
  if (DAT_0045eadc != '\0') {
    FUN_0043c34d();
    if (*param_2 == 0) {
      local_70 = &DAT_00455cf8;
    }
    else {
      local_70 = &DAT_00455cfc;
    }
    strcpy((char *)&DAT_00465a60,local_70);
    DAT_00465a68 = *(undefined4 *)(param_2[9] + 8);
    DAT_00465a6c = *(undefined4 *)(param_2[9] + 0xc);
    DAT_00465a70 = param_2[7];
    DAT_00465a78 = 0xca;
    FUN_0042447e(&DAT_00465a60);
  }
  return;
}


/* ==== FUN_00423011 @ 00423011 ==== */

void FUN_00423011(void)

{
  int *piVar1;
  int *piVar2;
  
  if (DAT_0044f790 == '\0') {
    if (DAT_0045f8fc < 2) {
      piVar2 = (int *)FUN_00439857(0x38);
      piVar1 = piVar2;
      if (DAT_0045fc10 != (int *)0x0) {
        DAT_0045fc10[0xd] = (int)piVar2;
        piVar1 = DAT_0045fc0c;
      }
      DAT_0045fc0c = piVar1;
      DAT_0045fc10 = piVar2;
      piVar2[6] = 0;
      *piVar2 = 0;
      piVar2[7] = 0;
      piVar2[1] = 0;
      piVar2[3] = 4;
      piVar2[2] = 4;
      piVar2[4] = 0;
      piVar2[5] = 0;
      piVar2[3] = 0;
      piVar2[2] = 0;
      piVar2[9] = 4;
      piVar2[8] = 4;
      piVar2[10] = 0;
      piVar2[0xb] = 0;
      piVar2[9] = 0;
      piVar2[8] = 0;
      piVar2[0xc] = -1;
      piVar2[0xd] = 0;
      DAT_0045fbd4 = DAT_0045fbd4 + 4;
    }
    else if (DAT_0045f8fc == 2) {
      if (DAT_0045fc10 == (int *)0x0) {
        FUN_00412fa0((uint *)s_File_info_out_of_sequence_00455d00);
      }
      FUN_0043c34d();
      strcpy((char *)&DAT_00465a60,s__text_0044fa70);
      DAT_00465a68 = *DAT_0045fc10;
      DAT_00465a6c = DAT_0045fc10[3];
      DAT_00465a70 = 1;
      DAT_00465a78 = 3;
      DAT_00465a7c = 1;
      FUN_0042447e(&DAT_00465a60);
      DAT_00465880 = DAT_0045fc10[1] - *DAT_0045fc10;
      DAT_00465884 = 0;
      DAT_00465888 = DAT_0045fc14;
      FUN_0042447e(&DAT_00465880);
      strcpy((char *)&DAT_00465a60,s__data_0044fa80);
      DAT_00465a68 = DAT_0045fc10[6];
      DAT_00465a6c = DAT_0045fc10[9];
      DAT_00465a70 = 2;
      DAT_00465a78 = 3;
      DAT_00465a7c = 1;
      FUN_0042447e(&DAT_00465a60);
      DAT_00465880 = DAT_0045fc10[7] - DAT_0045fc10[6];
      DAT_00465888 = 0;
      DAT_00465884 = 0;
      FUN_0042447e(&DAT_00465880);
      piVar1 = DAT_0045fc10;
      DAT_0045fc10 = (int *)DAT_0045fc10[0xd];
      FUN_004398b5((undefined *)piVar1);
    }
    DAT_0045fc14 = 0;
  }
  return;
}


/* ==== FUN_004232b6 @ 004232b6 ==== */

void __cdecl FUN_004232b6(uint *param_1,uint *param_2,int param_3)

{
  uint uVar1;
  uint *buf;
  int local_74;
  uint local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  uint local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  uint local_38;
  int local_34;
  int local_30;
  uint local_2c;
  uint local_28;
  int local_24;
  int local_20;
  uint local_1c;
  int local_18;
  int local_14;
  int local_10;
  uint local_c;
  uint local_8;
  
  local_8 = (uint)(DAT_0045f8c0 != DAT_0045f8cc);
  local_c = DAT_0045f8bc;
  if (((DAT_0045f8b0 == 3) && (DAT_0045eaa8 != '\0')) && (DAT_0045f8c0 != DAT_0045f8cc)) {
    local_40 = param_3 << 1;
  }
  else {
    if (DAT_0045f8b0 == 3) {
      local_44 = 2;
    }
    else {
      if (((DAT_0045eaa8 == '\0') || (DAT_0045f8c0 == DAT_0045f8cc)) &&
         ((DAT_0045f8a0 != 0x11f && (DAT_0045f8b0 != 0x11f)))) {
        local_48 = 1;
      }
      else {
        local_48 = param_3;
      }
      local_44 = local_48;
    }
    local_40 = local_44;
  }
  local_14 = local_40;
  if (((DAT_0045eaa8 == '\0') || (DAT_0045f8c0 == DAT_0045f8cc)) &&
     ((DAT_0045f8a0 != 0x11f && (DAT_0045f8b0 != 0x11f)))) {
    if ((DAT_0045f8b0 == 3) || ((DAT_0045f8bc & 0xf) == 0)) {
      local_4c = 1;
    }
    else {
      local_4c = ((int)DAT_0045f8bc >> 4) / (int)(DAT_0045f8bc & 0xf) +
                 ((int)DAT_0045f8bc >> 4 & (uint)((DAT_0045f8bc & 1) == 0));
    }
    local_50 = local_4c;
  }
  else {
    local_50 = param_3;
  }
  local_18 = local_50;
  if (DAT_0045f8a0 == 0x11f) {
    local_54 = param_3;
  }
  else {
    if ((DAT_0045f8ac & 0xf) == 0) {
      local_58 = 1;
    }
    else {
      local_58 = (int)(CONCAT44((int)DAT_0045f8ac >> 0x1f,(int)DAT_0045f8ac >> 4) /
                      (longlong)(int)(DAT_0045f8ac & 0xf)) +
                 ((int)DAT_0045f8ac >> 4 & (uint)((DAT_0045f8ac & 1) == 0));
    }
    local_54 = local_58;
  }
  local_10 = local_54;
  if (DAT_0045f8fc == 2) {
    *param_1 = *param_1 & 0xffffff;
    param_1[1] = param_1[1] & 0xffffff;
    if (((DAT_0045f8b0 == 3) || (param_3 == 4)) && (FUN_0042400d(param_1[1]), DAT_0045eaf8 != '\0'))
    {
      DAT_0045ebe4 = DAT_0045ebe4 + param_1[1];
    }
    FUN_0042400d(*param_1);
    if (DAT_0045eaf8 != '\0') {
      DAT_0045ebe4 = DAT_0045ebe4 + *param_1;
    }
    if (DAT_0045fca8 != 0) {
      if (local_c == 0) {
        if ((param_3 < 2) ||
           (((DAT_0045eaa8 == '\0' || (DAT_0045f8c0 == DAT_0045f8cc)) &&
            ((DAT_0045f8a0 != 0x11f && (DAT_0045f8b0 != 0x11f)))))) {
          FUN_00421160((char *)param_1,4);
        }
        else {
          if (((DAT_0045eaa8 == '\0') || (DAT_0045f8c0 == DAT_0045f8cc)) || (DAT_0045f8b0 != 3)) {
            local_1c = param_1[1] << 0x18 | *param_1;
          }
          else {
            local_1c = *param_1;
          }
          for (local_20 = 0; local_20 < param_3; local_20 = local_20 + 1) {
            if ((DAT_0045eaa8 == '\0') || (DAT_0045f8c0 == DAT_0045f8cc)) {
              local_5c = (param_3 - local_20) + -1;
            }
            else {
              local_5c = local_20;
            }
            local_24 = local_5c;
            local_28 = local_1c >> ((byte)(local_5c << 3) & 0x1f) & 0xff;
            FUN_00421160((char *)&local_28,4);
          }
        }
      }
      else {
        if (local_c == 0) {
          local_60 = *param_1;
        }
        else {
          if (local_c == 0x20) {
            local_64 = *param_1 & 0xff;
          }
          else {
            if (local_c == 0x30) {
              local_68 = *param_1 & 0xfff;
            }
            else {
              if (local_c == 0x40) {
                local_6c = *param_1 & 0xffff;
              }
              else {
                if (local_c == 0x50) {
                  local_70 = *param_1 & 0xfffff;
                }
                else {
                  local_70 = *param_1;
                }
                local_6c = local_70;
              }
              local_68 = local_6c;
            }
            local_64 = local_68;
          }
          local_60 = local_64;
        }
        local_2c = local_60;
        FUN_00421160((char *)&local_2c,4);
      }
      if (DAT_0045f8b0 == 3) {
        if ((param_3 < 2) ||
           (((DAT_0045eaa8 == '\0' || (DAT_0045f8c0 == DAT_0045f8cc)) && (DAT_0045f8a0 != 0x11f))))
        {
          FUN_00421160((char *)(param_1 + 1),4);
        }
        else {
          for (local_30 = 0; local_30 < param_3; local_30 = local_30 + 1) {
            if ((DAT_0045eaa8 == '\0') || (DAT_0045f8c0 == DAT_0045f8cc)) {
              local_74 = (param_3 - local_30) + -1;
            }
            else {
              local_74 = local_30;
            }
            local_34 = local_74;
            local_38 = param_1[1] >> ((byte)(local_74 << 3) & 0x1f) & 0xff;
            FUN_00421160((char *)&local_38,4);
          }
        }
      }
      if (param_2 != (uint *)0x0) {
        if ((param_3 < 2) ||
           (((DAT_0045eaa8 == '\0' || (DAT_0045f8c0 == DAT_0045f8cc)) &&
            ((DAT_0045f8a0 != 0x11f && (DAT_0045f8b0 != 0x11f)))))) {
          FUN_0042420d(param_2);
        }
        else {
          uVar1 = strlen((char *)param_2);
          buf = (uint *)FUN_00439857(uVar1 + 0x10);
          sprintf((char *)buf,s__BYT__d__s__00455d1c,param_3,param_2);
          FUN_0042420d(buf);
          FUN_004398b5((undefined *)buf);
        }
      }
    }
  }
  FUN_00424050(local_10);
  DAT_0045fb94 = DAT_0045fb94 + local_14;
  *DAT_0045f8c0 = *DAT_0045f8c0 + local_10;
  if (DAT_0045f8c0 != DAT_0045f8cc) {
    if (((DAT_0045eaa4 == '\0') || (DAT_0045f8b0 == 0x1c)) || (DAT_0045f8b0 == 0x11f)) {
      *DAT_0045f8cc = *DAT_0045f8cc + local_18;
    }
    else {
      *DAT_0045f8cc = *DAT_0045f8cc + local_18 * 3;
    }
  }
  FUN_0043b926(0);
  DAT_0045ea60 = 1;
  return;
}


/* ==== FUN_004238a9 @ 004238a9 ==== */

void __cdecl FUN_004238a9(uint param_1,uint *param_2,uint *param_3,int param_4,int param_5)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  uint *buf;
  uint local_74;
  uint local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  uint local_44;
  int local_40;
  int local_3c;
  uint local_38;
  uint local_34;
  int local_30;
  int local_2c;
  uint local_28;
  uint local_24;
  int local_20;
  int local_1c;
  int local_18;
  uint local_14;
  uint local_10;
  int local_c;
  uint local_8;
  
  local_8 = (uint)(DAT_0045f8c0 != DAT_0045f8cc);
  local_c = DAT_0045f8bc;
  local_14 = *(uint *)(DAT_0045fb88[9] + 0x30);
  local_10 = *(uint *)(DAT_0045fb8c[9] + 0x30);
  if (DAT_0045f8b0 == 3) {
    local_4c = 2;
  }
  else {
    if ((DAT_0045f8a0 == 0x11f) || (DAT_0045f8b0 == 0x11f)) {
      local_50 = param_5;
    }
    else {
      local_50 = 1;
    }
    local_4c = local_50;
  }
  local_1c = local_4c;
  if ((DAT_0045f8a0 == 0x11f) || (DAT_0045f8b0 == 0x11f)) {
    local_54 = param_5;
  }
  else {
    local_54 = 1;
  }
  local_20 = local_54;
  if (DAT_0045f8a0 == 0x11f) {
    local_58 = param_5;
  }
  else {
    local_58 = 1;
  }
  local_18 = local_58;
  piVar1 = DAT_0045f8cc;
  piVar2 = DAT_0045fb8c;
  if ((param_4 == 0) && ((DAT_0045eaa8 == '\0' || (DAT_0045f8c0 == DAT_0045f8cc)))) {
    DAT_0045fb88 = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8a0,
                                -(uint)(DAT_0044f794 != '\0') & 0x1000 |
                                -(uint)(local_8 != 0) & 0x4000,0);
    DAT_0045f8c0 = (int *)(DAT_0045fb88[9] + 0x10);
    piVar1 = DAT_0045f8c0;
    piVar2 = DAT_0045fb88;
    if (local_8 != 0) {
      DAT_0045fb8c = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8b0,
                                  -(uint)(DAT_0044f798 != '\0') & 0x1000,0);
      DAT_0045f8cc = (int *)(DAT_0045fb8c[9] + 0x10);
      piVar1 = DAT_0045f8cc;
      piVar2 = DAT_0045fb8c;
      if (DAT_0045eadc != '\0') {
        *(uint *)(DAT_0045fb8c[9] + 0x30) = *(uint *)(DAT_0045fb8c[9] + 0x30) | 0x800;
        piVar1 = DAT_0045f8cc;
        piVar2 = DAT_0045fb8c;
      }
    }
  }
  DAT_0045fb8c = piVar2;
  DAT_0045f8cc = piVar1;
  FUN_0043797a();
  if ((((DAT_0045eadc != '\0') && (DAT_0045ea98 == '\0')) && (DAT_0045ea70 == '\0')) &&
     ((DAT_0045eacc == '\0' && (DAT_0045f8a0 == 0)))) {
    if (DAT_0045eb24 == '\0') {
      local_5c = DAT_0045eb78;
    }
    else {
      local_5c = DAT_0044f7e8;
    }
    FUN_0042433e(local_5c);
  }
  if ((DAT_0045eaa8 == '\0') || (DAT_0045f8c0 == DAT_0045f8cc)) {
    if (DAT_0045f8fc < 2) {
      *(uint *)(DAT_0045fb8c[9] + 0x30) = *(uint *)(DAT_0045fb8c[9] + 0x30) | 0x400;
      if (DAT_0045f8b0 == 0x11f) {
        local_60 = param_5;
      }
      else {
        local_60 = 1;
      }
      *(int *)(DAT_0045fb8c[9] + 0x18) = local_60;
    }
    else if (DAT_0045f8fc == 2) {
      *param_2 = *param_2 & 0xffffff;
      param_2[1] = param_2[1] & 0xffffff;
      if (((DAT_0045f8b0 == 3) || (param_5 == 4)) &&
         (FUN_0042400d(param_2[1]), DAT_0045eaf8 != '\0')) {
        DAT_0045ebe4 = DAT_0045ebe4 + param_2[1];
      }
      FUN_0042400d(*param_2);
      if (DAT_0045eaf8 != '\0') {
        DAT_0045ebe4 = DAT_0045ebe4 + *param_2;
      }
      if (DAT_0045fca8 != 0) {
        if (local_c == 0) {
          if ((param_5 < 2) || ((DAT_0045f8a0 != 0x11f && (DAT_0045f8b0 != 0x11f)))) {
            FUN_00421160((char *)param_2,4);
          }
          else {
            local_28 = param_2[1] << 0x18 | *param_2;
            for (local_2c = 0; local_2c < param_5; local_2c = local_2c + 1) {
              local_30 = (param_5 - local_2c) + -1;
              local_34 = local_28 >> ((char)local_30 * '\b' & 0x1fU) & 0xff;
              FUN_00421160((char *)&local_34,4);
            }
          }
        }
        else {
          if (local_c == 0) {
            local_64 = *param_2;
          }
          else {
            if (local_c == 0x20) {
              local_68 = *param_2 & 0xff;
            }
            else {
              if (local_c == 0x30) {
                local_6c = *param_2 & 0xfff;
              }
              else {
                if (local_c == 0x40) {
                  local_70 = *param_2 & 0xffff;
                }
                else {
                  if (local_c == 0x50) {
                    local_74 = *param_2 & 0xfffff;
                  }
                  else {
                    local_74 = *param_2;
                  }
                  local_70 = local_74;
                }
                local_6c = local_70;
              }
              local_68 = local_6c;
            }
            local_64 = local_68;
          }
          local_38 = local_64;
          FUN_00421160((char *)&local_38,4);
        }
        if (DAT_0045f8b0 == 3) {
          if ((param_5 < 2) || (DAT_0045f8a0 != 0x11f)) {
            FUN_00421160((char *)(param_2 + 1),4);
          }
          else {
            for (local_3c = 0; local_3c < param_5; local_3c = local_3c + 1) {
              local_40 = (param_5 - local_3c) + -1;
              local_44 = param_2[1] >> ((char)local_40 * '\b' & 0x1fU) & 0xff;
              FUN_00421160((char *)&local_44,4);
            }
          }
        }
        if (param_3 != (uint *)0x0) {
          if ((param_5 < 2) || ((DAT_0045f8a0 != 0x11f && (DAT_0045f8b0 != 0x11f)))) {
            FUN_0042420d(param_3);
          }
          else {
            uVar3 = strlen((char *)param_3);
            buf = (uint *)FUN_00439857(uVar3 + 0x10);
            sprintf((char *)buf,s__BYT__d__s__00455d28,param_5,param_3);
            FUN_0042420d(buf);
            FUN_004398b5((undefined *)buf);
          }
        }
      }
    }
    FUN_00424050(param_1 * local_18);
    DAT_0045fb94 = DAT_0045fb94 + local_1c;
    *DAT_0045f8c0 = *DAT_0045f8c0 + param_1 * local_18;
    if (DAT_0045f8c0 != DAT_0045f8cc) {
      if ((DAT_0045eaa4 == '\0') || (DAT_0045f8b0 == 0x1c)) {
        *DAT_0045f8cc = *DAT_0045f8cc + param_1 * local_20;
      }
      else {
        *DAT_0045f8cc = *DAT_0045f8cc + param_1 * local_20 * 3;
      }
    }
    FUN_0043b926(0);
    DAT_0045ea60 = 1;
    if (param_4 == 0) {
      DAT_0045fb88 = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8a0,
                                  -(uint)(DAT_0044f794 != '\0') & 0x1000 |
                                  -(uint)(local_8 != 0) & 0x4000,0);
      *(uint *)(DAT_0045fb88[9] + 0x30) = *(uint *)(DAT_0045fb88[9] + 0x30) | local_14 & 0xfffffffe;
      DAT_0045f8c0 = (int *)(DAT_0045fb88[9] + 0x10);
      if (local_8 == 0) {
        DAT_0045fb8c = DAT_0045fb88;
        DAT_0045f8cc = DAT_0045f8c0;
      }
      else {
        DAT_0045fb8c = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8b0,
                                    -(uint)(DAT_0044f798 != '\0') & 0x1000,0);
        *(uint *)(DAT_0045fb8c[9] + 0x30) =
             *(uint *)(DAT_0045fb8c[9] + 0x30) | local_10 & 0xfffffffe;
        DAT_0045f8cc = (int *)(DAT_0045fb8c[9] + 0x10);
        if (DAT_0045eadc != '\0') {
          *(uint *)(DAT_0045fb8c[9] + 0x30) = *(uint *)(DAT_0045fb8c[9] + 0x30) | 0x800;
        }
      }
    }
  }
  else {
    for (local_24 = 0; local_24 < param_1; local_24 = local_24 + 1) {
      FUN_004232b6(param_2,param_3,param_5);
    }
  }
  return;
}


/* ==== FUN_0042400d @ 0042400d ==== */

void __cdecl FUN_0042400d(uint param_1)

{
  if (DAT_0045f924 < 0xff) {
    (&DAT_00465480)[DAT_0045f924] = param_1 & 0xffffff;
    DAT_0045f924 = DAT_0045f924 + 1;
  }
  DAT_0045f920 = 1;
  return;
}


/* ==== FUN_00424050 @ 00424050 ==== */

void __cdecl FUN_00424050(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  uint local_20;
  
  uVar5 = DAT_0045f8bc;
  uVar4 = DAT_0045f8b8;
  uVar3 = DAT_0045f8b4;
  uVar2 = DAT_0045f8b0;
  uVar1 = *DAT_0045f8cc;
  local_20 = uVar1 + param_1;
  if (DAT_0045f8b0 == 0) {
    if (DAT_0045fc10 != (uint *)0x0) {
      if ((DAT_0045fc10[1] == 0) || (uVar1 < *DAT_0045fc10)) {
        *DAT_0045fc10 = uVar1;
        puVar6 = DAT_0045fc10;
        DAT_0045fc10[2] = 0;
        puVar6[3] = uVar3;
        puVar6[4] = uVar4;
        puVar6[5] = uVar5;
      }
      if (DAT_0045fc10[1] < local_20) {
        DAT_0045fc10[1] = local_20;
      }
    }
    if ((DAT_004559d0 != 0) || (uVar1 < DAT_0045f8e8)) {
      DAT_0044f90c = uVar2;
      DAT_004559d0 = 0;
      DAT_0045f8e8 = uVar1;
    }
    if (DAT_0045f8f0 < local_20) {
      if (0xffff < local_20) {
        local_20 = 0xffff;
      }
      DAT_0045f8f0 = local_20;
      DAT_0044f914 = uVar2;
    }
  }
  else {
    if (DAT_0045fc10 != (uint *)0x0) {
      if ((DAT_0045fc10[7] == 0) || (uVar1 < DAT_0045fc10[6])) {
        DAT_0045fc10[6] = uVar1;
        puVar6 = DAT_0045fc10;
        DAT_0045fc10[8] = uVar2;
        puVar6[9] = uVar3;
        puVar6[10] = uVar4;
        puVar6[0xb] = uVar5;
      }
      if (DAT_0045fc10[7] < local_20) {
        DAT_0045fc10[7] = local_20;
      }
    }
    if (DAT_0045ea28 == '\0') {
      DAT_0044f910 = uVar2;
      DAT_0045ea28 = '\x01';
      DAT_0045f8ec = uVar1;
    }
    if (DAT_0045f8f4 < local_20) {
      DAT_0044f918 = uVar2;
      DAT_0045f8f4 = local_20;
    }
  }
  return;
}


