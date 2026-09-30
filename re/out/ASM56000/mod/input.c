/* input: 20 functions from ASM56000 */

/* ==== FUN_004197d0 @ 004197d0 ==== */

void FUN_004197d0(void)

{
  int iVar1;
  
  while (iVar1 = FUN_0041983e(), iVar1 != 0) {
    FUN_0041d334();
    iVar1 = FUN_0041a4bc();
    if (iVar1 == 0) {
      FUN_0041c742(0x20);
    }
    else if (DAT_0045f8fc == 0) {
      FUN_0041ad75();
    }
    else {
      FUN_0041af7e(0,0);
      FUN_0041bdca(' ');
    }
    DAT_0045f924 = 0;
    DAT_0045f928 = 0;
    DAT_0045f92c = 0;
  }
  return;
}


/* ==== FUN_0041983e @ 0041983e ==== */

undefined4 FUN_0041983e(void)

{
  int iVar1;
  int *extraout_EAX;
  uint uVar2;
  int *extraout_EAX_00;
  bool bVar3;
  uint *local_10;
  uint *local_8;
  
  if (DAT_0045ea18 != '\0') {
    return 0;
  }
  if ((((DAT_0045fc2c != (int *)0x0) && (*DAT_0045fc2c == 2)) && (DAT_0045fb6c != 0)) &&
     (*(int *)(DAT_0045fb6c + 8) == 0)) {
    return 0;
  }
  DAT_0045eb80 = DAT_0045eb80 + 1;
  if (DAT_0045eb80 < 1) {
    FUN_00412fa0((uint *)s_Too_many_lines_in_source_file_00454af4);
  }
  iVar1 = FUN_00419caf();
  if (iVar1 == 1) {
    if (DAT_0045fb6c == 0) {
      DAT_0045eb78 = DAT_0045eb7c + 1;
      DAT_0045eb7c = DAT_0045eb78;
    }
    DAT_0045d824 = DAT_0045d824 + 1;
    return 1;
  }
  while (iVar1 = FUN_00419ba2(), iVar1 == 1) {
    iVar1 = FUN_00419caf();
    if (iVar1 == 1) {
      if ((DAT_0045fb6c == 0) &&
         (DAT_0045eb78 = DAT_0045eb7c + 1, DAT_0045eb7c = DAT_0045eb78, DAT_0045eae0 == '\0')) {
        if (DAT_0045eb24 == '\0') {
          local_8 = (uint *)PTR_DAT_0044f80c;
        }
        else {
          local_8 = DAT_0045f858;
        }
        FUN_0040f5d5((uint *)&DAT_00454b14,local_8,(char *)0x0,0);
        FUN_00435d9f();
        FUN_00435eca(PTR_DAT_0044f978,0);
      }
      DAT_0045d824 = DAT_0045d824 + 1;
      return 1;
    }
  }
  if (DAT_0045ea98 != '\0') {
    return 0;
  }
  do {
    if (DAT_0045ea78 == '\0') {
      DAT_0044f958 = DAT_0044f958 + 1;
      bVar3 = DAT_0044f958 <= DAT_0045f904;
    }
    else {
      iVar1 = FUN_00402a03(&DAT_00465a88);
      bVar3 = iVar1 != 0;
    }
    if (!bVar3) {
      return 0;
    }
    if (DAT_0045ea78 == '\0') {
      DAT_0045f908 = DAT_0045f908 + 1;
      strcpy(&DAT_0045f220,(char *)*DAT_0045f908);
    }
    if (DAT_0045eb4c != '\0') {
      fprintf(PTR_DAT_0044f9a4,s__s__Opening_source_file__s_00454b1c,PTR_s_asm56000_0044e084,
              &DAT_0045f220);
    }
    fopen(&DAT_0045f220,&DAT_00454b38);
    DAT_0045f900 = extraout_EAX;
    if ((extraout_EAX == (int *)0x0) &&
       ((uVar2 = FUN_00402bfa((uint *)&DAT_00454b3c), uVar2 == 0 ||
        (fopen(&DAT_0045f220,&DAT_00454b44), DAT_0045f900 = extraout_EAX_00,
        extraout_EAX_00 == (int *)0x0)))) {
      FUN_004137c6(s_Cannot_open_source_file_00454b48,&DAT_0045f220);
    }
    FUN_0043b8f1(DAT_0045f900,0);
    DAT_0044f954 = DAT_0044f954 + 1;
    FUN_00402cde((uint *)&DAT_0045f220);
    DAT_0045eb7c = 0;
    DAT_0045d824 = 0;
    iVar1 = FUN_00419caf();
  } while (iVar1 != 1);
  if ((DAT_0045fb6c == 0) &&
     (DAT_0045eb78 = DAT_0045eb7c + 1, DAT_0045eb7c = DAT_0045eb78, DAT_0045eae0 == '\0')) {
    if (DAT_0045eb24 == '\0') {
      local_10 = (uint *)PTR_DAT_0044f80c;
    }
    else {
      local_10 = DAT_0045f858;
    }
    FUN_0040f5d5((uint *)&DAT_00454b60,local_10,(char *)0x0,0);
    FUN_00435d9f();
    FUN_00435eca(PTR_DAT_0044f978,0);
  }
  DAT_0045d824 = DAT_0045d824 + 1;
  return 1;
}


/* ==== FUN_00419ba2 @ 00419ba2 ==== */

undefined4 FUN_00419ba2(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (DAT_0045fc28 == (undefined4 *)0x0) {
    uVar2 = 0;
  }
  else {
    PTR_DAT_0044f80c = (undefined *)*DAT_0045fc28;
    DAT_0045f900 = DAT_0045fc28[1];
    DAT_0044f954 = DAT_0045fc28[2];
    DAT_0045eb7c = DAT_0045fc28[3];
    if (DAT_0045fc28[4] != 0) {
      if ((DAT_0045fc2c == (int *)0x0) || (*DAT_0045fc2c == 1)) {
        strcpy(&DAT_0045ec08,(char *)DAT_0045fc28[4]);
        DAT_0045fb74 = 1;
      }
      else {
        *(undefined4 *)(DAT_0045fb6c + 8) = *(undefined4 *)(DAT_0045fb6c + 0xc);
        *(undefined4 *)(DAT_0045fb6c + 0x10) = **(undefined4 **)(DAT_0045fb6c + 8);
      }
      FUN_004398b5((undefined *)DAT_0045fc28[4]);
      DAT_0045fc28[4] = 0;
    }
    puVar1 = DAT_0045fc28;
    DAT_0045fc28 = (undefined4 *)DAT_0045fc28[5];
    FUN_004398b5((undefined *)puVar1);
    iVar3 = FUN_0041a3ff();
    if (iVar3 != 1) {
      FUN_00412fa0((uint *)s_Input_mode_stack_out_of_sequence_00454b68);
    }
    uVar2 = 1;
  }
  return uVar2;
}


/* ==== FUN_00419caf @ 00419caf ==== */

undefined4 FUN_00419caf(void)

{
  bool bVar1;
  uint c;
  undefined4 uVar2;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint *local_24;
  int local_1c;
  undefined1 local_18;
  int local_14;
  undefined1 *local_10;
  uint *local_c;
  int local_8;
  
  local_c = (uint *)&DAT_0045ec08;
  local_10 = &DAT_0045f018;
  local_8 = 0;
  bVar1 = false;
  local_1c = 0;
  local_14 = 0;
  if (DAT_0045fb74 != '\0') {
    DAT_0045fb74 = 0;
    return 1;
  }
  local_24 = (uint *)0x0;
LAB_00419d02:
  do {
    c = FUN_0041a0a7();
    if (c == 0xffffffff) goto LAB_0041a005;
    if (!bVar1) {
      if (__mb_cur_max < 2) {
        local_28 = *(ushort *)(_pctype + c * 2) & 0x107;
      }
      else {
        local_28 = _isctype(c,0x107);
      }
      if ((local_28 == 0) && (c != 0x5f)) {
        if (local_24 != (uint *)0x0) {
          if (DAT_0045ea68 != '\0') {
            local_8 = local_8 - (int)local_c;
            local_1c = local_1c + 1;
            local_c = FUN_0041a9e9(local_24,local_c,local_1c);
            local_8 = local_8 + (int)local_c;
          }
          local_24 = (uint *)0x0;
        }
      }
      else if (local_24 == (uint *)0x0) {
        if (__mb_cur_max < 2) {
          local_2c = *(ushort *)(_pctype + c * 2) & 0x103;
        }
        else {
          local_2c = _isctype(c,0x103);
        }
        if (local_2c != 0) {
          local_24 = (uint *)((int)local_c + local_14);
        }
      }
    }
    if (c != 10) {
      if (c == 9) {
        local_14 = local_14 + (DAT_0044f7d0 - (local_8 + local_14) % DAT_0044f7d0);
        goto LAB_00419d02;
      }
      if (c == 0x20) {
        local_14 = local_14 + 1;
        goto LAB_00419d02;
      }
      if ((undefined1 *)((int)local_c + local_14) < (undefined1 *)0x45ee08) {
        if ((c == 0x27) && (DAT_0045eaac == '\0')) {
          bVar1 = !bVar1;
        }
        if (local_14 != 0) {
          local_8 = local_8 + local_14;
          while (local_14 != 0) {
            *local_10 = 0x20;
            *(undefined1 *)local_c = 0x20;
            local_c = (uint *)((int)local_c + 1);
            local_10 = local_10 + 1;
            local_14 = local_14 + -1;
          }
          local_14 = 0;
        }
        local_18 = (undefined1)c;
        *local_10 = local_18;
        *(undefined1 *)local_c = local_18;
        local_c = (uint *)((int)local_c + 1);
        local_10 = local_10 + 1;
        local_8 = local_8 + 1;
        goto LAB_00419d02;
      }
      DAT_0045f860 = 0;
      FUN_00413085((uint *)s_Line_too_long_00454b8c);
      *local_10 = 0;
      *(undefined1 *)local_c = 0;
      do {
        DAT_0045f900[1] = DAT_0045f900[1] + -1;
        if (DAT_0045f900[1] < 0) {
          local_30 = _filbuf(DAT_0045f900);
        }
        else {
          local_30 = (uint)*(byte *)*DAT_0045f900;
          *DAT_0045f900 = *DAT_0045f900 + 1;
        }
      } while ((local_30 != 0xffffffff) && (local_30 != 10));
LAB_0041a005:
      if (local_c != (uint *)&DAT_0045ec08) {
        if ((local_24 != (uint *)0x0) && (DAT_0045ea68 != '\0')) {
          local_c = FUN_0041a9e9(local_24,local_c,local_1c + 1);
        }
        *local_10 = 0;
        *(undefined1 *)local_c = 0;
        uVar2 = FUN_0041a444();
        return uVar2;
      }
      if (((DAT_0045ea98 == '\0') || (DAT_0045f8fc == 2)) && (DAT_0045eb4c != '\0')) {
        fprintf(PTR_DAT_0044f9a4,s__s__Closing_file__s_00454b9c,PTR_s_asm56000_0044e084,
                PTR_DAT_0044f80c);
      }
      fclose(DAT_0045f900);
      return 0;
    }
    *local_10 = 0;
    *(undefined1 *)local_c = 0;
    if (local_c == (uint *)&DAT_0045ec08) {
      return 1;
    }
    if (*(char *)((int)local_c + -1) != '\\') {
      uVar2 = FUN_0041a444();
      return uVar2;
    }
    if (DAT_0045fb6c == 0) {
      DAT_0045eb7c = DAT_0045eb7c + 1;
    }
    DAT_0045d824 = DAT_0045d824 + 1;
    local_c = (uint *)((int)local_c + -1);
    local_10 = local_10 + -1;
    local_8 = 0;
    local_14 = 0;
  } while( true );
}


/* ==== FUN_0041a0a7 @ 0041a0a7 ==== */

uint FUN_0041a0a7(void)

{
  char cVar1;
  char cVar2;
  double *pdVar3;
  undefined4 va0;
  uint uVar4;
  int iVar5;
  char *in_stack_ffffffd8;
  int local_18;
  undefined4 *local_8;
  
  if ((DAT_0045fc2c == (int *)0x0) || (*DAT_0045fc2c == 1)) {
    DAT_0045f900[1] = DAT_0045f900[1] + -1;
    if (DAT_0045f900[1] < 0) {
      uVar4 = _filbuf(DAT_0045f900);
    }
    else {
      uVar4 = (uint)*(byte *)*DAT_0045f900;
      *DAT_0045f900 = *DAT_0045f900 + 1;
    }
  }
  else {
    while( true ) {
      do {
        if (*(int *)(DAT_0045fb6c + 0x18) != 0) {
          cVar1 = **(char **)(DAT_0045fb6c + 0x18);
          *(int *)(DAT_0045fb6c + 0x18) = *(int *)(DAT_0045fb6c + 0x18) + 1;
          if ((int)cVar1 != 0) {
            return (int)cVar1;
          }
          *(undefined4 *)(DAT_0045fb6c + 0x18) = 0;
        }
        iVar5 = *(int *)(DAT_0045fb6c + 0x10) - **(int **)(DAT_0045fb6c + 8);
        uVar4 = (uint)**(char **)(DAT_0045fb6c + 0x10);
        *(int *)(DAT_0045fb6c + 0x10) = *(int *)(DAT_0045fb6c + 0x10) + 1;
      } while ((uVar4 == 2) &&
              (*(char *)(*(int *)(*(int *)(DAT_0045fb6c + 8) + 4) + iVar5) == '\x01'));
      if ((uVar4 != 1) || (*(char *)(*(int *)(*(int *)(DAT_0045fb6c + 8) + 4) + iVar5) != '\x01'))
      break;
      cVar1 = **(char **)(DAT_0045fb6c + 0x10);
      *(int *)(DAT_0045fb6c + 0x10) = *(int *)(DAT_0045fb6c + 0x10) + 1;
      cVar2 = **(char **)(DAT_0045fb6c + 0x10);
      *(int *)(DAT_0045fb6c + 0x10) = *(int *)(DAT_0045fb6c + 0x10) + 1;
      if ((int)cVar2 <= *(int *)(DAT_0045fb6c + 4)) {
        local_8 = *(undefined4 **)(DAT_0045fb6c + 0x14);
        for (local_18 = 1; local_18 < cVar2; local_18 = local_18 + 1) {
          local_8 = (undefined4 *)local_8[1];
        }
        if (cVar1 == '\x01') {
          *(undefined4 *)(DAT_0045fb6c + 0x18) = *local_8;
        }
        else {
          DAT_0045f860 = *local_8;
          pdVar3 = (double *)FUN_00414862();
          if (pdVar3 == (double *)0x0) {
            FUN_00413085((uint *)s_Macro_value_substitution_failed_00454bb4);
            DAT_00463be8 = 0;
          }
          else {
            if (*(int *)(pdVar3 + 2) == 0x100) {
              if (cVar1 == '\x02') {
                in_stack_ffffffd8 = &DAT_00454bd4;
              }
              else {
                in_stack_ffffffd8 = &DAT_00454bd8;
              }
              va0 = FUN_0040a7ea((int)pdVar3);
              sprintf(&DAT_00463be8,in_stack_ffffffd8,va0);
            }
            else if (cVar1 == '\x02') {
              FUN_0043c0ea((uint *)&DAT_00463be8,(uint *)s____15E_00454bdc,*(int *)pdVar3,
                           *(uint *)((int)pdVar3 + 4));
            }
            else {
              uVar4 = FUN_0040b6bf(*pdVar3,in_stack_ffffffd8);
              *(uint *)(pdVar3 + 1) = uVar4;
              sprintf(&DAT_00463be8,&DAT_00454be4,*(undefined4 *)(pdVar3 + 1));
            }
            *(undefined1 **)(DAT_0045fb6c + 0x18) = &DAT_00463be8;
          }
          FUN_004167ef((undefined4 *)pdVar3);
        }
      }
    }
    if (uVar4 == 0) {
      *(undefined4 *)(DAT_0045fb6c + 0xc) = *(undefined4 *)(DAT_0045fb6c + 8);
      *(undefined4 *)(DAT_0045fb6c + 8) = *(undefined4 *)(*(int *)(DAT_0045fb6c + 8) + 8);
      if (*(int *)(DAT_0045fb6c + 8) != 0) {
        *(undefined4 *)(DAT_0045fb6c + 0x10) = **(undefined4 **)(DAT_0045fb6c + 8);
      }
      uVar4 = 10;
    }
  }
  return uVar4;
}


/* ==== FUN_0041a3ce @ 0041a3ce ==== */

void __cdecl FUN_0041a3ce(undefined4 param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00439857(8);
  *puVar1 = param_1;
  puVar1[1] = DAT_0045fc2c;
  DAT_0045fc2c = puVar1;
  return;
}


/* ==== FUN_0041a3ff @ 0041a3ff ==== */

undefined4 FUN_0041a3ff(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = DAT_0045fc2c;
  if (DAT_0045fc2c == (undefined4 *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = *DAT_0045fc2c;
    DAT_0045fc2c = (undefined4 *)DAT_0045fc2c[1];
    FUN_004398b5((undefined *)puVar1);
  }
  return uVar2;
}


/* ==== FUN_0041a444 @ 0041a444 ==== */

undefined4 FUN_0041a444(void)

{
  uint local_c;
  char *local_8;
  
  local_8 = &DAT_0045ec08;
  while( true ) {
    if (*local_8 == '\0') {
      DAT_0045ec08 = 0;
      return 1;
    }
    if (__mb_cur_max < 2) {
      local_c = *(ushort *)(_pctype + *local_8 * 2) & 8;
    }
    else {
      local_c = _isctype((int)*local_8,8);
    }
    if (local_c == 0) break;
    local_8 = local_8 + 1;
  }
  return 1;
}


/* ==== FUN_0041a4bc @ 0041a4bc ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0041a4bc(void)

{
  undefined4 uVar1;
  char *pcVar2;
  bool bVar3;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  char *local_c;
  char *local_8;
  
  local_c = &DAT_0045ec08;
  DAT_0045eac0 = '\0';
  if ((DAT_0045ec08 == ';') || (DAT_0045ec08 == '\0')) {
    uVar1 = 0;
  }
  else {
    do {
      local_8 = &DAT_0045ee10;
      PTR_DAT_0044f810 = &DAT_0045ee10;
      pcVar2 = FUN_0041a92e(local_c);
      bVar3 = local_c == pcVar2;
      for (; local_c != pcVar2; local_c = local_c + 1) {
        *local_8 = *local_c;
        local_8 = local_8 + 1;
      }
      if (((bVar3) || (pcVar2[-1] != ':')) || (DAT_0045eac0 != '\0')) {
        *local_8 = '\0';
        local_8 = local_8 + 1;
      }
      else {
        DAT_0045eac0 = '\x01';
        local_8[-1] = '\0';
      }
      while( true ) {
        if (__mb_cur_max < 2) {
          local_18 = *(ushort *)(_pctype + *local_c * 2) & 8;
        }
        else {
          local_18 = _isctype((int)*local_c,8);
        }
        if (local_18 == 0) break;
        local_c = local_c + 1;
      }
      PTR_DAT_0044f814 = local_8;
      DAT_00465aa0 = local_8;
      if (*local_c == ';') goto LAB_0041a64e;
      pcVar2 = FUN_0041a92e(local_c);
    } while (((*PTR_DAT_0044f810 == '\0') && (local_c < pcVar2)) &&
            ((pcVar2[-1] == ':' && (DAT_0045eac0 == '\0'))));
    for (; local_c != pcVar2; local_c = local_c + 1) {
      *local_8 = *local_c;
      local_8 = local_8 + 1;
    }
LAB_0041a64e:
    *local_8 = '\0';
    local_8 = local_8 + 1;
    while( true ) {
      if (__mb_cur_max < 2) {
        local_1c = *(ushort *)(_pctype + *local_c * 2) & 8;
      }
      else {
        local_1c = _isctype((int)*local_c,8);
      }
      if (local_1c == 0) break;
      local_c = local_c + 1;
    }
    if (*PTR_DAT_0044f814 == '.') {
      FUN_004317e0(local_c,local_8);
      uVar1 = 1;
    }
    else {
      PTR_DAT_0044f818 = local_8;
      DAT_00465aa4 = local_8;
      if (*local_c != ';') {
        pcVar2 = FUN_0041a92e(local_c);
        for (; local_c != pcVar2; local_c = local_c + 1) {
          *local_8 = *local_c;
          local_8 = local_8 + 1;
        }
      }
      *local_8 = '\0';
      local_8 = local_8 + 1;
      while( true ) {
        if (__mb_cur_max < 2) {
          local_20 = *(ushort *)(_pctype + *local_c * 2) & 8;
        }
        else {
          local_20 = _isctype((int)*local_c,8);
        }
        if (local_20 == 0) break;
        local_c = local_c + 1;
      }
      PTR_DAT_0044f81c = local_8;
      DAT_00465aa8 = local_8;
      if (*local_c != ';') {
        pcVar2 = FUN_0041a92e(local_c);
        for (; local_c != pcVar2; local_c = local_c + 1) {
          *local_8 = *local_c;
          local_8 = local_8 + 1;
        }
      }
      *local_8 = '\0';
      local_8 = local_8 + 1;
      while( true ) {
        if (__mb_cur_max < 2) {
          local_24 = *(ushort *)(_pctype + *local_c * 2) & 8;
        }
        else {
          local_24 = _isctype((int)*local_c,8);
        }
        if (local_24 == 0) break;
        local_c = local_c + 1;
      }
      PTR_DAT_0044f820 = local_8;
      DAT_00465aac = local_8;
      if (*local_c != ';') {
        pcVar2 = FUN_0041a92e(local_c);
        for (; local_c != pcVar2; local_c = local_c + 1) {
          *local_8 = *local_c;
          local_8 = local_8 + 1;
        }
      }
      *local_8 = '\0';
      local_8 = local_8 + 1;
      while( true ) {
        if (__mb_cur_max < 2) {
          local_28 = *(ushort *)(_pctype + *local_c * 2) & 8;
        }
        else {
          local_28 = _isctype((int)*local_c,8);
        }
        if (local_28 == 0) break;
        local_c = local_c + 1;
      }
      PTR_DAT_0044f824 = local_8;
      _DAT_00465b14 = local_8;
      if ((*local_c != '\0') && (local_c[1] != ';')) {
        for (; *local_c != '\0'; local_c = local_c + 1) {
          *local_8 = *local_c;
          local_8 = local_8 + 1;
        }
      }
      *local_8 = '\0';
      uVar1 = 1;
    }
  }
  return uVar1;
}


/* ==== FUN_0041a92e @ 0041a92e ==== */

char * __cdecl FUN_0041a92e(char *param_1)

{
  uint local_8;
  
  do {
    if (*param_1 == '\0') {
      return param_1;
    }
    if (__mb_cur_max < 2) {
      local_8 = *(ushort *)(_pctype + *param_1 * 2) & 8;
    }
    else {
      local_8 = _isctype((int)*param_1,8);
    }
    if (local_8 != 0) {
      return param_1;
    }
    if (*param_1 == '\'') {
      do {
        param_1 = param_1 + 1;
        if (*param_1 == '\0') break;
      } while (*param_1 != '\'');
    }
    else if (*param_1 == '\"') {
      do {
        param_1 = param_1 + 1;
        if (*param_1 == '\0') break;
      } while (*param_1 != '\"');
    }
    param_1 = param_1 + 1;
  } while( true );
}


/* ==== FUN_0041a9e9 @ 0041a9e9 ==== */

uint * __cdecl FUN_0041a9e9(uint *param_1,uint *param_2,int param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  int local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  char *local_10;
  
  if ((char)*param_1 == DAT_0044f830) {
    return param_2;
  }
  *(undefined1 *)param_2 = 0;
  uVar1 = strlen((char *)param_1);
  if (0x200 < uVar1) {
    return param_2;
  }
  if (DAT_00463c08 != 0) {
    DAT_00463c08 = 0;
    return param_2;
  }
  if (DAT_00463c0c != 0) {
    DAT_00463c0c = 0;
    return param_2;
  }
  if (param_3 == 1) {
    if (__mb_cur_max < 2) {
      local_14 = *(ushort *)(_pctype + DAT_0045ec08 * 2) & 8;
    }
    else {
      local_14 = _isctype((int)DAT_0045ec08,8);
    }
    if ((((((local_14 != 0) && (((char)*param_1 == 'D' || ((char)*param_1 == 'd')))) &&
          ((*(char *)((int)param_1 + 1) == 'E' || (*(char *)((int)param_1 + 1) == 'e')))) &&
         ((((*(char *)((int)param_1 + 2) == 'F' || (*(char *)((int)param_1 + 2) == 'f')) &&
           ((*(char *)((int)param_1 + 3) == 'I' || (*(char *)((int)param_1 + 3) == 'i')))) &&
          (((char)param_1[1] == 'N' || ((char)param_1[1] == 'n')))))) &&
        ((*(char *)((int)param_1 + 5) == 'E' || (*(char *)((int)param_1 + 5) == 'e')))) &&
       (*(char *)((int)param_1 + 6) == '\0')) {
      DAT_00463c08 = 1;
      goto LAB_0041ace5;
    }
  }
  if (param_3 == 1) {
    if (__mb_cur_max < 2) {
      local_18 = *(ushort *)(_pctype + DAT_0045ec08 * 2) & 8;
    }
    else {
      local_18 = _isctype((int)DAT_0045ec08,8);
    }
    if (local_18 == 0) goto LAB_0041abd7;
LAB_0041ac24:
    if (((((char)*param_1 != 'U') && ((char)*param_1 != 'u')) ||
        ((*(char *)((int)param_1 + 1) != 'N' && (*(char *)((int)param_1 + 1) != 'n')))) ||
       ((((*(char *)((int)param_1 + 2) != 'D' && (*(char *)((int)param_1 + 2) != 'd')) ||
         ((*(char *)((int)param_1 + 3) != 'E' && (*(char *)((int)param_1 + 3) != 'e')))) ||
        ((((char)param_1[1] != 'F' && ((char)param_1[1] != 'f')) ||
         (*(char *)((int)param_1 + 5) != '\0')))))) goto LAB_0041acd6;
    local_20 = 1;
  }
  else {
LAB_0041abd7:
    if (param_3 == 2) {
      if (__mb_cur_max < 2) {
        local_1c = *(ushort *)(_pctype + DAT_0045ec08 * 2) & 8;
      }
      else {
        local_1c = _isctype((int)DAT_0045ec08,8);
      }
      if (local_1c == 0) goto LAB_0041ac24;
    }
LAB_0041acd6:
    local_20 = 0;
  }
  DAT_00463c0c = local_20;
LAB_0041ace5:
  puVar2 = FUN_0043012d(param_1,2);
  if (puVar2 != (undefined4 *)0x0) {
    local_10 = (char *)puVar2[1];
    uVar1 = strlen(local_10);
    if ((int)((int)&DAT_0045ec08 - ((int)param_1 + uVar1)) < 0x200) {
      DAT_0045ea6c = 1;
      for (; param_2 = param_1, *local_10 != '\0'; local_10 = local_10 + 1) {
        *(char *)param_1 = *local_10;
        param_1 = (uint *)((int)param_1 + 1);
      }
    }
    else {
      FUN_004131f9((uint *)s_Redefinition_would_overflow_line_00454be8,(char *)param_1);
    }
  }
  return param_2;
}


/* ==== FUN_0041ad75 @ 0041ad75 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0041ad75(void)

{
  undefined4 *puVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  
  if ((DAT_0045eb4c != '\0') && (DAT_0045eb80 % DAT_0044f7c8 == 0)) {
    fprintf(PTR_DAT_0044f9a4,s__s__Processing_line__ld_in_file___00454c0c,PTR_s_asm56000_0044e084,
            DAT_0045eb78,PTR_DAT_0044f80c,DAT_0045eb80);
  }
  if ((DAT_0045ea70 == '\0') || (DAT_0045eacc != '\0')) {
    if (DAT_0045f8c4 != *DAT_0045f8c0) {
      _DAT_0045f8c8 = DAT_0045f8c4;
    }
    DAT_0045f8c4 = *DAT_0045f8c0;
    DAT_0045f8d0 = *DAT_0045f8cc;
  }
  DAT_0045f860 = 0;
  DAT_0045eb98 = 0;
  if (*PTR_DAT_0044f814 == '\0') {
    if ((PTR_DAT_0044f810 != (undefined *)0x0) && (*PTR_DAT_0044f810 != '\0')) {
      FUN_0043797a();
    }
  }
  else {
    puVar1 = FUN_0041faa5((uint *)PTR_DAT_0044f814,2);
    if (puVar1 == (undefined4 *)0x0) {
      uVar2 = strlen(PTR_DAT_0044f814);
      if (uVar2 < 0x10) {
        puVar3 = (uint *)FUN_00438f9c(PTR_DAT_0044f814);
        iVar4 = FUN_00438f1a(puVar3,0);
        if (iVar4 != 0) {
          if (((DAT_0045ea70 == '\0') && (PTR_DAT_0044f810 != (undefined *)0x0)) &&
             (*PTR_DAT_0044f810 != '\0')) {
            FUN_0043797a();
          }
          DAT_0045f928 = *(int *)(iVar4 + 0x10);
          FUN_00424bf0(iVar4);
          DAT_0045f930 = DAT_0045f930 + DAT_0045f928;
          return 0;
        }
        if (*PTR_DAT_0044f814 == '.') {
          return 1;
        }
        iVar4 = FUN_0043903f(puVar3,0);
        if (iVar4 != 0) {
          FUN_0042b240(iVar4);
          return 0;
        }
      }
      iVar4 = FUN_004206ea((uint *)PTR_DAT_0044f814);
      if (iVar4 == 0) {
        FUN_004131f9((uint *)s_Unrecognized_mnemonic_00454c38,PTR_DAT_0044f814);
      }
    }
    else {
      FUN_004209f8(puVar1);
    }
  }
  return 0;
}


/* ==== FUN_0041af7e @ 0041af7e ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_0041af7e(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint *puVar4;
  undefined *extraout_ECX;
  undefined *extraout_ECX_00;
  undefined *this;
  int local_30;
  uint *local_2c;
  
  if ((DAT_0045eb4c != '\0') && (DAT_0045eb80 % DAT_0044f7c8 == 0)) {
    fprintf(PTR_DAT_0044f9a4,s__s__Processing_line__ld_in_file___00454c50,PTR_s_asm56000_0044e084,
            DAT_0045eb78,PTR_DAT_0044f80c,DAT_0045eb80);
  }
  if ((DAT_0045ea70 == '\0') || (DAT_0045eacc != '\0')) {
    if (DAT_0045f8c4 != *DAT_0045f8c0) {
      _DAT_0045f8c8 = DAT_0045f8c4;
    }
    DAT_0045f8c4 = *DAT_0045f8c0;
    DAT_0045f8d0 = *DAT_0045f8cc;
  }
  DAT_0045f860 = 0;
  DAT_0045eb98 = 0;
  if (DAT_0045eb40 == '\0') {
    DAT_0045eb40 = '\x01';
    if ((((PTR_DAT_0044f814 != (undefined *)0x0) && (*PTR_DAT_0044f814 != '\0')) &&
        (*PTR_DAT_0044f814 == s__file_00454c7c[0])) &&
       (iVar1 = strcmp(PTR_DAT_0044f814,s__file_00454c84), iVar1 == 0)) {
      DAT_0045eae0 = DAT_0045eadc != '\0';
    }
    if (DAT_0045eae0 == '\0') {
      if (DAT_0045eb24 == '\0') {
        local_2c = (uint *)PTR_DAT_0044f80c;
      }
      else {
        local_2c = DAT_0045f858;
      }
      FUN_0040f5d5((uint *)&DAT_00454c8c,local_2c,(char *)0x0,1);
    }
  }
  if (*PTR_DAT_0044f814 == '\0') {
    if ((PTR_DAT_0044f810 != (undefined *)0x0) && (*PTR_DAT_0044f810 != '\0')) {
      FUN_0043797a();
    }
  }
  else {
    puVar2 = FUN_0041faa5((uint *)PTR_DAT_0044f814,2);
    if (puVar2 == (undefined4 *)0x0) {
      uVar3 = strlen(PTR_DAT_0044f814);
      if (uVar3 < 0x10) {
        puVar4 = (uint *)FUN_00438f9c(PTR_DAT_0044f814);
        iVar1 = FUN_00438f1a(puVar4,0);
        if (iVar1 != 0) {
          if (((DAT_0045ea70 == '\0') && (PTR_DAT_0044f810 != (undefined *)0x0)) &&
             (*PTR_DAT_0044f810 != '\0')) {
            FUN_0043797a();
          }
          if (((DAT_0045eadc != '\0') && (DAT_0045ea98 == '\0')) &&
             ((DAT_0045ea70 == '\0' && ((DAT_0045eacc == '\0' && (DAT_0045f8a0 == 0)))))) {
            if (DAT_0045eb24 == '\0') {
              local_30 = DAT_0045eb78;
            }
            else {
              local_30 = DAT_0044f7e8;
            }
            FUN_0042433e(local_30);
          }
          DAT_0045f928 = *(int *)(iVar1 + 0x10);
          FUN_00424bf0(iVar1);
          DAT_0045f930 = DAT_0045f930 + DAT_0045f928;
          return 0;
        }
        if (*PTR_DAT_0044f814 == '.') {
          iVar1 = FUN_00439194((int)puVar4);
          if (iVar1 != 0) {
            this = extraout_ECX;
            if ((PTR_DAT_0044f810 != (undefined *)0x0) &&
               (this = PTR_DAT_0044f810, *PTR_DAT_0044f810 != '\0')) {
              FUN_0043797a();
              this = extraout_ECX_00;
            }
            FUN_004318d1(this,iVar1);
            return 0;
          }
          puVar2 = (undefined4 *)FUN_004391d7((char *)puVar4);
          if (puVar2 != (undefined4 *)0x0) {
            FUN_0040f3e0(puVar2);
            return 0;
          }
        }
        iVar1 = FUN_0043903f(puVar4,0);
        if (iVar1 != 0) {
          if (((param_1 == 1) && (*(char *)(iVar1 + 4) == '\x12')) && (param_2 == 1)) {
            return 0x12;
          }
          if ((param_1 == 1) && (*(char *)(iVar1 + 4) == '\x15')) {
            return 0x15;
          }
          FUN_0042b240(iVar1);
          return 0;
        }
      }
      iVar1 = FUN_004206ea((uint *)PTR_DAT_0044f814);
      if (iVar1 == 0) {
        FUN_004131f9((uint *)s_Unrecognized_mnemonic_00454c94,PTR_DAT_0044f814);
      }
    }
    else {
      FUN_004209f8(puVar2);
    }
  }
  return 0;
}


/* ==== FUN_0041b339 @ 0041b339 ==== */

void FUN_0041b339(void)

{
  DAT_0045ea5c = 0;
  DAT_0045f93c = 0;
  DAT_0045ea74 = 0;
  DAT_0045f944 = DAT_0045f940;
  DAT_0045f940 = 0;
  DAT_0045f948 = 0;
  DAT_0045ebb8 = DAT_0045ebb4;
  DAT_0045ebb4 = 0;
  if (((DAT_0045ea90 != '\0') && (*DAT_0045f8c0 < DAT_0044f924)) && ((*DAT_0045f8c0 & 1) == 0)) {
    DAT_0045f944 = 0;
    DAT_0045ebb8 = 0;
  }
  return;
}


/* ==== FUN_0041b3c7 @ 0041b3c7 ==== */

void __cdecl FUN_0041b3c7(int param_1)

{
  uint uVar1;
  int iVar2;
  int local_8;
  
  if (param_1 == 9) {
    local_8 = *(int *)(DAT_0045fc30 + 0xc);
  }
  else {
    local_8 = DAT_0045fc30;
  }
  if (local_8 == 0) {
    FUN_00412fa0((uint *)s_DO_stack_out_of_sequence_00454cac);
  }
  uVar1 = strlen(&DAT_0045ec08);
  iVar2 = FUN_00439857(uVar1 + 1);
  *(int *)(local_8 + 4) = iVar2;
  strcpy(*(char **)(local_8 + 4),&DAT_0045ec08);
  *(undefined4 *)(local_8 + 8) = *DAT_0045f8c0;
  return;
}


/* ==== FUN_0041b43f @ 0041b43f ==== */

void __cdecl FUN_0041b43f(int *param_1)

{
  uint *puVar1;
  uint local_c;
  
  local_c = *DAT_0045f8c0;
  if (1 < *param_1) {
    local_c = local_c + 1;
  }
  while ((DAT_0045fc30 != (uint *)0x0 && (*DAT_0045fc30 <= local_c))) {
    if (DAT_0045fc30[1] != 0) {
      FUN_0041b4d3(param_1);
      FUN_004398b5((undefined *)DAT_0045fc30[1]);
      DAT_0045fc30[1] = 0;
    }
    puVar1 = DAT_0045fc30;
    DAT_0045fc30 = (uint *)DAT_0045fc30[3];
    FUN_004398b5((undefined *)puVar1);
  }
  return;
}


/* ==== FUN_0041b4d3 @ 0041b4d3 ==== */

void __cdecl FUN_0041b4d3(int *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  
  DAT_0045da3c = 1;
  FUN_0042400d(param_1[1]);
  if (1 < *param_1) {
    FUN_0042400d(param_1[2]);
  }
  DAT_0045f930 = DAT_0045f930 + DAT_0045f928;
  FUN_0041bdca(' ');
  uVar6 = DAT_0045f94c;
  uVar5 = DAT_0045f940;
  uVar4 = DAT_0045ebb8;
  uVar3 = DAT_0045ebb4;
  uVar2 = DAT_0044f95c;
  DAT_0045ea54 = 1;
  uVar1 = *DAT_0045f8c0;
  DAT_0045ea70 = 1;
  *DAT_0045f8c0 = *(undefined4 *)(DAT_0045fc30 + 8);
  strcpy(&DAT_0045ec08,*(char **)(DAT_0045fc30 + 4));
  iVar7 = FUN_0041a4bc();
  if (iVar7 != 0) {
    FUN_0041af7e(0,0);
  }
  DAT_0045ea70 = 0;
  DAT_0045ebb4 = uVar3;
  DAT_0045ebb8 = uVar4;
  DAT_0045f940 = uVar5;
  *DAT_0045f8c0 = uVar1;
  DAT_0045f94c = uVar6;
  DAT_0044f95c = uVar2;
  DAT_0045f930 = DAT_0045f930 - DAT_0045f928;
  DAT_0045f928 = 0;
  DAT_0045f92c = 0;
  DAT_0045da3c = 0;
  return;
}


/* ==== FUN_0041b615 @ 0041b615 ==== */

undefined4 __cdecl FUN_0041b615(int param_1)

{
  undefined4 uVar1;
  int local_c;
  
  if (DAT_0045fc30 == (int *)0x0) {
    uVar1 = 0;
  }
  else if (DAT_0045ea70 == '\0') {
    for (local_c = param_1; (-1 < local_c && (*DAT_0045f8c0 != *DAT_0045fc30 - local_c));
        local_c = local_c + -1) {
    }
    if (local_c < 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_0041b685 @ 0041b685 ==== */

int __cdecl FUN_0041b685(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int local_10;
  
  uVar1 = DAT_0045f860;
  if (DAT_0045fc30 == (int *)0x0) {
    iVar2 = 0;
  }
  else if (DAT_0045ea70 == '\0') {
    if (DAT_0045ea74 == '\0') {
      for (local_10 = param_1; (-1 < local_10 && (*DAT_0045f8c0 != *DAT_0045fc30 - local_10));
          local_10 = local_10 + -1) {
      }
      if (-1 < local_10) {
        DAT_0045ea74 = '\x01';
        DAT_0045f860 = 0;
        switch(param_1) {
        case 0:
          FUN_00413085((uint *)s_Instruction_cannot_appear_at_las_00454cc8);
          break;
        case 1:
          FUN_00413085((uint *)s_Instruction_cannot_appear_within_00454d00);
          break;
        case 2:
          FUN_00413085((uint *)s_Instruction_cannot_appear_within_00454d3c);
          break;
        case 3:
          FUN_00413085((uint *)s_Instruction_cannot_appear_within_00454d78);
          break;
        case 4:
          FUN_00413085((uint *)s_Instruction_cannot_appear_within_00454db4);
          break;
        case 5:
          FUN_00413085((uint *)s_Instruction_cannot_appear_within_00454df0);
          break;
        default:
          FUN_00412fa0((uint *)s_Invalid_DO_loop_range_check_00454e2c);
        }
      }
      iVar2 = (int)DAT_0045ea74;
    }
    else {
      iVar2 = 1;
    }
  }
  else {
    iVar2 = 0;
  }
  DAT_0045f860 = uVar1;
  return iVar2;
}


/* ==== FUN_0041b7c9 @ 0041b7c9 ==== */

int __cdecl FUN_0041b7c9(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = DAT_0045f860;
  if (DAT_0045fc30 == (int *)0x0) {
    iVar2 = 0;
  }
  else if (DAT_0045ea70 == '\0') {
    if (DAT_0045ea74 == '\0') {
      if (*DAT_0045f8c0 == *DAT_0045fc30 - param_1) {
        DAT_0045ea74 = '\x01';
        DAT_0045f860 = 0;
        switch(param_1) {
        case 0:
          FUN_00413085((uint *)s_Instruction_cannot_appear_in_las_00454e48);
          break;
        case 1:
          FUN_00413085((uint *)s_Instruction_cannot_appear_in_nex_00454e7c);
          break;
        case 2:
          FUN_00413085((uint *)s_Instruction_cannot_appear_in_sec_00454eb8);
          break;
        case 3:
          FUN_00413085((uint *)s_Instruction_cannot_appear_in_thi_00454ef8);
          break;
        default:
          FUN_00412fa0((uint *)s_Invalid_DO_loop_address_check_00454f38);
        }
      }
      iVar2 = (int)DAT_0045ea74;
    }
    else {
      iVar2 = 1;
    }
  }
  else {
    iVar2 = 0;
  }
  DAT_0045f860 = uVar1;
  return iVar2;
}


