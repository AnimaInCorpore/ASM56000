/* input: 27 functions from DSPLNK */

/* ==== FUN_00414110 @ 00414110 ==== */

void FUN_00414110(void)

{
  char *src;
  int iVar1;
  uint uVar2;
  bool bVar3;
  char *local_28;
  char *local_24;
  char *local_20;
  undefined4 *local_10;
  int local_8;
  
  local_10 = (undefined4 *)0x0;
  local_8 = 0;
  if (DAT_00461294 == 1) {
    while( true ) {
      if (DAT_004611f4 == '\0') {
        local_8 = local_8 + 1;
        bVar3 = local_8 <= DAT_00461da0;
      }
      else {
        iVar1 = thunk_FUN_00402871((undefined4 *)&DAT_0046c114);
        bVar3 = iVar1 != 0;
      }
      if (!bVar3) break;
      if (DAT_004611f4 == '\0') {
        src = (char *)*DAT_00461da4;
        DAT_00461da4 = DAT_00461da4 + 1;
        strcpy(&DAT_00461528,src);
      }
      FUN_004143b4();
      uVar2 = DAT_00461dbc[1];
      if ((uVar2 & 2) == 0) {
        thunk_FUN_004146c6(DAT_00461dbc[2]);
      }
      else {
        thunk_FUN_0041c6d7();
      }
      if (DAT_0046125c != '\0') {
        if ((uVar2 & 2) == 0) {
          local_20 = &DAT_00456b44;
        }
        else {
          local_20 = s_library_00456b3c;
        }
        fprintf(PTR_DAT_00457c08,s__s__Closing__s_file__s_00456b4c,PTR_s_dsplnk_00457ed0,local_20,
                *DAT_00461dbc);
      }
      fclose(DAT_00461db4);
    }
  }
  else {
    if (DAT_00461f38 != 0) {
      thunk_FUN_00427710();
    }
    for (DAT_00461dbc = DAT_00461db8; DAT_00461dbc != (undefined4 *)0x0;
        DAT_00461dbc = (undefined4 *)DAT_00461dbc[4]) {
      uVar2 = DAT_00461dbc[1] & 2;
      if (DAT_0046125c != '\0') {
        if (uVar2 == 0) {
          local_24 = &DAT_00456b6c;
        }
        else {
          local_24 = s_library_00456b64;
        }
        fprintf(PTR_DAT_00457c08,s__s__Opening__s_file__s_00456b74,PTR_s_dsplnk_00457ed0,local_24,
                *DAT_00461dbc);
      }
      DAT_00461db4 = (int *)FUN_0041a815((uint *)*DAT_00461dbc);
      if (DAT_00461db4 == (int *)0x0) {
        if (uVar2 == 0) {
          thunk_FUN_004098b0(s_Cannot_open_object_file_00456ba8);
        }
        else {
          thunk_FUN_004098b0(s_Cannot_open_library_file_00456b8c);
        }
      }
      thunk_FUN_004300c3(DAT_00461db4,0);
      if (uVar2 == 0) {
        thunk_FUN_004146c6(DAT_00461dbc[2]);
      }
      else {
        thunk_FUN_0041c6d7();
      }
      if (DAT_0046125c != '\0') {
        if (uVar2 == 0) {
          local_28 = &DAT_00456bc8;
        }
        else {
          local_28 = s_library_00456bc0;
        }
        fprintf(PTR_DAT_00457c08,s__s__Closing__s_file__s_00456bd0,PTR_s_dsplnk_00457ed0,local_28,
                *DAT_00461dbc);
      }
      fclose(DAT_00461db4);
      local_10 = DAT_00461dbc;
    }
    DAT_00461dbc = local_10;
  }
  return;
}


/* ==== FUN_004143b4 @ 004143b4 ==== */

void FUN_004143b4(void)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  uint *puVar6;
  char *va1;
  
  iVar1 = thunk_FUN_0041c4cf();
  if (DAT_00461260 != '\0') {
    thunk_FUN_00430037(&DAT_00461528);
  }
  if (DAT_0046125c != '\0') {
    if (iVar1 == 0) {
      va1 = &DAT_00456bf0;
    }
    else {
      va1 = s_library_00456be8;
    }
    fprintf(PTR_DAT_00457c08,s__s__Opening__s_file__s_00456bf8,PTR_s_dsplnk_00457ed0,va1,
            &DAT_00461528);
  }
  DAT_00461db4 = (int *)FUN_0041a815((uint *)&DAT_00461528);
  if (DAT_00461db4 == (int *)0x0) {
    if (iVar1 == 0) {
      puVar6 = (uint *)&DAT_00457fd8;
    }
    else {
      puVar6 = (uint *)&DAT_00457fe8;
    }
    uVar2 = thunk_FUN_004032e9(puVar6);
    if ((uVar2 == 0) ||
       (DAT_00461db4 = (int *)FUN_0041a815((uint *)&DAT_00461528), DAT_00461db4 == (int *)0x0)) {
      if (iVar1 == 0) {
        thunk_FUN_0040a0f6(s_Cannot_open_object_file_00456c2c,&DAT_00461528);
      }
      else {
        thunk_FUN_0040a0f6(s_Cannot_open_library_file_00456c10,&DAT_00461528);
      }
    }
  }
  thunk_FUN_004300c3(DAT_00461db4,0);
  piVar3 = (int *)thunk_FUN_0042e170(0x14);
  uVar2 = strlen(&DAT_00461528);
  iVar4 = thunk_FUN_0042e170(uVar2 + 1);
  *piVar3 = iVar4;
  strcpy((char *)*piVar3,&DAT_00461528);
  piVar3[1] = -(uint)(iVar1 != 0) & 2;
  if (iVar1 == 0) {
    iVar1 = FUN_0041a8c0((int)DAT_00461db4);
    if (iVar1 < 0) {
      thunk_FUN_004098b0(s_Cannot_determine_file_size_00456c44);
    }
    piVar5 = thunk_FUN_004145bb((uint *)0x0,iVar1,0);
    piVar3[2] = (int)piVar5;
    piVar3[3] = 0;
  }
  else {
    thunk_FUN_0041c5ec(*piVar3);
    piVar3[3] = 0;
    piVar3[2] = 0;
  }
  piVar3[4] = 0;
  piVar5 = piVar3;
  if (DAT_00461db8 != (int *)0x0) {
    *(int **)((int)DAT_00461dbc + 0x10) = piVar3;
    piVar5 = DAT_00461db8;
  }
  DAT_00461db8 = piVar5;
  DAT_00461dbc = piVar3;
  return;
}


/* ==== FUN_004145bb @ 004145bb ==== */

int * __cdecl FUN_004145bb(uint *param_1,int param_2,int param_3)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  
  piVar1 = (int *)thunk_FUN_0042e170(0x98);
  if (param_1 == (uint *)0x0) {
    *piVar1 = 0;
  }
  else {
    uVar2 = strlen((char *)param_1);
    iVar3 = thunk_FUN_0042e170(uVar2 + 1);
    *piVar1 = iVar3;
    strcpy((char *)*piVar1,(char *)param_1);
  }
  piVar1[2] = param_2;
  piVar1[3] = param_3;
  piVar1[1] = 0;
  piVar1[4] = 0;
  piVar1[5] = 0;
  piVar1[6] = 0;
  piVar1[7] = 0;
  piVar1[0x1d] = 0;
  piVar1[0x1e] = 0;
  piVar1[0x1f] = 0;
  piVar1[0x20] = 0;
  piVar1[0x21] = 0;
  piVar1[0x22] = 0;
  piVar1[0x23] = 0;
  piVar1[0x24] = 0;
  piVar1[0x25] = 0;
  return piVar1;
}


/* ==== FUN_004146c6 @ 004146c6 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_004146c6(int param_1)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  uint *local_24;
  int local_1c;
  int local_14;
  
  local_14 = 0;
  if (DAT_00461294 == 1) {
    FUN_00414d76(param_1);
    if (DAT_00461270 != '\0') {
      FUN_00415316(param_1);
    }
    FUN_0041507a(param_1);
    FUN_0041a5e0(param_1);
    if ((((DAT_0046124c != '\0') && (DAT_00461fe8 < 5)) &&
        ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) &&
       ((DAT_00461210 == '\0' && ((*(uint *)(param_1 + 0x38) & 4) == 0)))) {
      thunk_FUN_00409d88(s_Incompatible_debug_format_00456c60);
    }
    for (local_1c = 0; local_1c < *(int *)(param_1 + 0x30); local_1c = local_1c + puVar2[7] + 1) {
      DAT_00461e7c = local_1c;
      puVar2 = (uint *)(*(int *)(param_1 + 0x8c) + local_1c * 0x20);
      if (*puVar2 == 0) {
        local_24 = (uint *)(*(int *)(param_1 + 0x90) + puVar2[1]);
      }
      else {
        thunk_FUN_004307d5((undefined1 *)puVar2,4,2);
        local_24 = puVar2;
      }
      if ((puVar2[6] == 0x67) && (puVar2[0xd] != 0)) {
        if (DAT_00461134 == 0) {
          DAT_00461134 = puVar2[0xd];
        }
        else if (DAT_00461134 != puVar2[0xd]) {
          thunk_FUN_00409d88(s_Memory_model_mismatch___stack_me_00456c7c);
        }
        if (DAT_00461134 == 1) {
          DAT_00457b48 = 2;
        }
        else if (DAT_00461134 == 2) {
          DAT_00457b48 = 1;
        }
        else {
          DAT_00457b48 = DAT_00461134;
        }
      }
      if ((puVar2[6] == 200) && (DAT_00461134 != 0)) {
        if (DAT_00461134 == 1) {
          DAT_00457b48 = 2;
        }
        else if (DAT_00461134 == 2) {
          DAT_00457b48 = 1;
        }
      }
      if (((puVar2[6] == 0x67) || (puVar2[6] == 200)) && (puVar2[5] == 1)) {
        DAT_004612c4 = DAT_004612ac;
        DAT_004612d8 = DAT_004612c8;
        DAT_00461e68 = puVar2;
      }
      if (puVar2[6] == 100) {
        DAT_004612e8 = DAT_004612e8 +
                       (-(uint)(*(char *)((int)local_24 + 1) != 'b') & 0xfffffffe) + 1;
      }
      if ((puVar2[6] == 0x81) && (*(int *)(DAT_00461de4 + 0x38) != 0)) {
        FUN_0041839c(param_1,puVar2[2]);
      }
      if ((puVar2[6] == 3) && (puVar2[5] == 0)) {
        DAT_00457c00 = puVar2[4];
        local_14 = FUN_004153a6(local_24,(int)puVar2,param_1);
      }
      else if (local_14 != 0) {
        if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
          if ((((puVar2[6] == 2) || ((puVar2[6] == 3 && (DAT_004612e8 == 0)))) ||
              (puVar2[6] == 0x6a)) ||
             ((((puVar2[6] == 6 || (puVar2[6] == 0xd2)) || (puVar2[6] == 0xd3)) ||
              ((puVar2[6] == 0xd4 || (puVar2[6] == 0xd5)))))) {
            if (puVar2[4] == 0) {
              FUN_00416bed(local_24,(int)puVar2);
            }
            else {
              FUN_00416622((int)local_24,(int)puVar2);
            }
          }
        }
        else if (((puVar2[6] == 2) ||
                 ((((puVar2[6] == 3 && (DAT_004612e8 == 0)) || (puVar2[6] == 0xd2)) ||
                  ((puVar2[6] == 0xd3 || (puVar2[6] == 0xd4)))))) || (puVar2[6] == 0xd5)) {
          if (puVar2[4] == 0) {
            FUN_00416bed(local_24,(int)puVar2);
          }
          else {
            FUN_00416622((int)local_24,(int)puVar2);
          }
        }
      }
    }
    DAT_00457c00 = 0xffffffff;
    DAT_00461e7c = 0;
    thunk_FUN_0042ceac();
  }
  else {
    FUN_0041507a(param_1);
    DAT_00461de8 = *(undefined4 *)(param_1 + 0x10);
    DAT_00461e64 = *(undefined4 *)(param_1 + 0x14);
    DAT_00461e5c = *(undefined4 *)(param_1 + 0x18);
    DAT_00461e60 = *(undefined4 *)(param_1 + 0x1c);
    DAT_004612c8 = 0;
    DAT_004612ac = 0;
    if (DAT_00461f00 != 0) {
      thunk_FUN_004098b0(s_Section_nesting_error_00456cc8);
    }
    if (((*(uint *)(param_1 + 0x38) & 0x20000) == 0) || (DAT_00461248 != '\0')) {
      DAT_00461270 = '\0';
    }
    else {
      DAT_00461270 = '\x01';
    }
    if (DAT_00461270 == '\0') {
      *(undefined4 *)(param_1 + 0x70) = 0;
    }
    else {
      iVar3 = thunk_FUN_0042e170((*(int *)(param_1 + 0x40) + *(int *)(param_1 + 0x70)) * 4);
      *(int *)(param_1 + 0x7c) = iVar3;
      *(undefined4 *)(param_1 + 0x80) = *(undefined4 *)(param_1 + 0x7c);
    }
    DAT_00461ef8 = DAT_00461ef8 + *(int *)(param_1 + 0x70);
    _DAT_00461ebc = DAT_00461eb8;
    DAT_00461eb8 = DAT_00461eb8 + *(int *)(param_1 + 0x50);
    FUN_0041516a(param_1);
    for (local_1c = 0; local_1c < *(int *)(param_1 + 0x30); local_1c = local_1c + (char)uVar1 + 1) {
      DAT_00461e7c = local_1c;
      puVar2 = (uint *)(*(int *)(param_1 + 0x8c) + local_1c * 0x20);
      uVar1 = puVar2[7];
      if (((puVar2[6] == 0x67) || (puVar2[6] == 200)) && (puVar2[5] == 1)) {
        DAT_004612c4 = DAT_004612ac;
        DAT_004612d8 = DAT_004612c8;
        DAT_00461e68 = puVar2;
      }
      if ((puVar2[6] == 0x81) && (*(int *)(DAT_00461de4 + 0x38) != 0)) {
        *(int *)(*(int *)(DAT_00461de4 + 0x38) + 0x14) =
             *(int *)(*(int *)(DAT_00461de4 + 0x38) + 0x14) + 1;
      }
      if ((puVar2[6] == 0xc9) || (puVar2[6] == 0x80)) {
        FUN_0041874a((int)puVar2);
      }
      else if ((puVar2[6] == 3) && (puVar2[5] == 0)) {
        DAT_00457c00 = puVar2[4];
        iVar3 = FUN_004153a6((uint *)0x0,(int)puVar2,param_1);
        if (iVar3 != 0) {
          FUN_00416cf8((int *)(*(int *)(param_1 + 0x14) + -8 + puVar2[4] * 8),param_1);
        }
      }
      if (DAT_00461250 == '\0') {
        FUN_0041882a(puVar2,param_1);
      }
    }
    DAT_00457c00 = 0xffffffff;
    DAT_00461e7c = 0;
    thunk_FUN_00427ebb(param_1);
  }
  return 1;
}


/* ==== FUN_00414d76 @ 00414d76 ==== */

void __cdecl FUN_00414d76(int param_1)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  uint *puVar4;
  
  iVar1 = fseek(DAT_00461db4,*(long *)(param_1 + 0xc),0);
  if (iVar1 != 0) {
    thunk_FUN_004098b0(s_Cannot_seek_to_start_of_object_m_00456ce0);
  }
  uVar2 = thunk_FUN_0043062d((char *)(param_1 + 0x20),0x1c,1,DAT_00461db4);
  if (uVar2 != 1) {
    thunk_FUN_004098b0(s_Cannot_read_file_header_from_obj_00456d08);
  }
  if ((DAT_00461fc0 == 0) ||
     (((*(int *)(param_1 + 0x20) == 0x2c8 || (*(int *)(param_1 + 0x20) == 0x2ca)) &&
      (DAT_00461fa0 == 0x2c5)))) {
    thunk_FUN_004045d0(*(undefined **)(param_1 + 0x20));
  }
  if ((*(int *)(param_1 + 0x20) != DAT_00461fa0) &&
     (((DAT_00461fa0 != 0x2c8 && (DAT_00461fa0 != 0x2ca)) || (*(int *)(param_1 + 0x20) != 0x2c5))))
  {
    thunk_FUN_004098b0(s_Invalid_object_file_for_target_p_00456d34);
  }
  if ((*(uint *)(param_1 + 0x38) & 1) != 0) {
    thunk_FUN_004098b0(s_File_contains_no_relocation_info_00456d60);
  }
  if ((*(uint *)(param_1 + 0x38) & 0x10000) != 0) {
    DAT_00461210 = 1;
  }
  if ((*(uint *)(param_1 + 0x38) & 0x20000) == 0) {
    DAT_00461270 = 0;
  }
  else {
    DAT_00461278 = 1;
    if (DAT_00461248 == '\0') {
      DAT_00461274 = 1;
      DAT_00461270 = 1;
    }
  }
  switch(DAT_00461fa0) {
  case 0x2c5:
  case 0x2c6:
    DAT_00457b48 = 3;
    break;
  case 0x2c7:
  case 0x2c9:
  case 0x2cb:
    DAT_00457b48 = 1;
    break;
  case 0x2c8:
  case 0x2ca:
    DAT_00457b48 = 2;
    break;
  default:
    DAT_00457b48 = 2;
  }
  uVar2 = thunk_FUN_0043062d((char *)(param_1 + 0x3c),*(uint *)(param_1 + 0x34),1,DAT_00461db4);
  if (uVar2 != 1) {
    thunk_FUN_004098b0(s_Cannot_read_optional_header_from_00456d88);
  }
  uVar2 = *(uint *)(param_1 + 0x24);
  if (uVar2 != 0) {
    pcVar3 = FUN_0041a8ef(uVar2);
    *(char **)(param_1 + 0x74) = pcVar3;
    DAT_00461e98 = DAT_00461e98 + uVar2;
  }
  uVar2 = *(uint *)(param_1 + 0x30);
  if (uVar2 != 0) {
    iVar1 = fseek(DAT_00461db4,*(int *)(param_1 + 0x2c) + *(int *)(param_1 + 0xc),0);
    if (iVar1 != 0) {
      thunk_FUN_004098b0(s_Cannot_seek_to_object_module_sym_00456db8);
    }
    pcVar3 = thunk_FUN_0041a937(uVar2);
    *(char **)(param_1 + 0x8c) = pcVar3;
    if (DAT_0046c604 == (uint *)0x0) {
      DAT_0046c604 = thunk_FUN_0043457a(5,5,0x4013de);
    }
    thunk_FUN_0043a3e3((int)DAT_0046c604,param_1);
  }
  puVar4 = thunk_FUN_0041a97f();
  *(uint **)(param_1 + 0x90) = puVar4;
  if ((DAT_00461254 == '\0') && (3 < *(int *)(param_1 + 0x44))) {
    pcVar3 = (char *)(*(int *)(param_1 + 0x90) + *(int *)(param_1 + 0x44));
    uVar2 = strlen(pcVar3);
    DAT_00461dc4 = (char *)thunk_FUN_0042e170(uVar2 + 1);
    strcpy(DAT_00461dc4,pcVar3);
    DAT_00461254 = '\x01';
  }
  return;
}


/* ==== FUN_0041507a @ 0041507a ==== */

void __cdecl FUN_0041507a(int param_1)

{
  if (*(int *)(param_1 + 0x34) == 0x28) {
    DAT_00461fe8 = 4;
    DAT_00461ff0 = 0;
    DAT_00461fec = 0;
  }
  else {
    DAT_00461fe8 = *(int *)(param_1 + 0x60);
    DAT_00461fec = *(int *)(param_1 + 100);
    DAT_00461ff0 = *(undefined4 *)(param_1 + 0x68);
  }
  DAT_00461fd0 = DAT_00461fe8;
  DAT_00461fd4 = DAT_00461fec;
  DAT_00461fd8 = DAT_00461ff0;
  if ((DAT_00461294 == 1) && (DAT_00457b84 != '\0')) {
    if (DAT_00461fdc < DAT_00461fe8) {
      thunk_FUN_00409d88(s_Object_file_major_version_number_00456de4);
    }
    else if ((DAT_00461fe8 == DAT_00461fdc) && (DAT_00461fe0 < DAT_00461fec)) {
      thunk_FUN_00409d88(s_Object_file_minor_version_number_00456e30);
    }
  }
  return;
}


/* ==== FUN_0041516a @ 0041516a ==== */

void __cdecl FUN_0041516a(int param_1)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  void *pvVar4;
  char *pcVar5;
  
  iVar2 = *(int *)(param_1 + 0x40);
  if (iVar2 != 0) {
    iVar1 = fseek(DAT_00461db4,*(int *)(*(int *)(param_1 + 0x74) + 0x1c) + *(int *)(param_1 + 0xc),0
                 );
    if (iVar1 != 0) {
      thunk_FUN_004098b0(s_Cannot_seek_to_object_module_raw_00456e7c);
    }
    iVar2 = thunk_FUN_0042e170(iVar2 << 2);
    *(int *)(param_1 + 0x78) = iVar2;
    pvVar4 = DAT_00461db4;
    pvVar3 = (void *)thunk_FUN_00430667(*(char **)(param_1 + 0x78),4,(uint)DAT_00461db4,DAT_00461db4
                                       );
    if (pvVar3 != pvVar4) {
      thunk_FUN_004098b0(s_Cannot_read_raw_data_from_object_00456ea4);
    }
  }
  if ((*(int *)(param_1 + 0x84) == 0) && (*(int *)(param_1 + 0x50) != 0)) {
    pcVar5 = (char *)0x0;
    iVar2 = fseek(DAT_00461db4,*(int *)(*(int *)(param_1 + 0x74) + 0x20) + *(int *)(param_1 + 0xc),0
                 );
    if (iVar2 != 0) {
      pcVar5 = s_Cannot_seek_to_object_module_rel_00456ecc;
      thunk_FUN_004098b0(s_Cannot_seek_to_object_module_rel_00456ecc);
    }
    iVar2 = thunk_FUN_0042e170((int)pcVar5 * 0xc);
    *(int *)(param_1 + 0x84) = iVar2;
    pvVar4 = DAT_00461db4;
    pvVar3 = (void *)thunk_FUN_00430667(*(char **)(param_1 + 0x84),0xc,(uint)DAT_00461db4,
                                        DAT_00461db4);
    if (pvVar3 != pvVar4) {
      thunk_FUN_004098b0(s_Cannot_read_relocation_entries_f_00456efc);
    }
  }
  if (*(int *)(param_1 + 0x54) != 0) {
    pcVar5 = (char *)0x0;
    iVar2 = fseek(DAT_00461db4,*(int *)(*(int *)(param_1 + 0x74) + 0x24) + *(int *)(param_1 + 0xc),0
                 );
    if (iVar2 != 0) {
      pcVar5 = s_Cannot_seek_to_object_module_lin_00456f30;
      thunk_FUN_004098b0(s_Cannot_seek_to_object_module_lin_00456f30);
    }
    iVar2 = thunk_FUN_0042e170((int)pcVar5 * 0xc);
    *(int *)(param_1 + 0x88) = iVar2;
    pvVar4 = DAT_00461db4;
    pvVar3 = (void *)thunk_FUN_00430667(*(char **)(param_1 + 0x88),0xc,(uint)DAT_00461db4,
                                        DAT_00461db4);
    if (pvVar3 != pvVar4) {
      thunk_FUN_004098b0(s_Cannot_read_line_number_entries_f_00456f64);
    }
  }
  return;
}


/* ==== FUN_00415316 @ 00415316 ==== */

void __cdecl FUN_00415316(int param_1)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  void *pvVar4;
  
  iVar2 = *(int *)(param_1 + 0x50);
  if (iVar2 != 0) {
    iVar1 = fseek(DAT_00461db4,*(int *)(*(int *)(param_1 + 0x74) + 0x20) + *(int *)(param_1 + 0xc),0
                 );
    if (iVar1 != 0) {
      thunk_FUN_004098b0(s_Cannot_seek_to_object_module_rel_00456f98);
    }
    iVar2 = thunk_FUN_0042e170(iVar2 * 0xc);
    *(int *)(param_1 + 0x84) = iVar2;
    pvVar4 = DAT_00461db4;
    pvVar3 = (void *)thunk_FUN_00430667(*(char **)(param_1 + 0x84),0xc,(uint)DAT_00461db4,
                                        DAT_00461db4);
    if (pvVar3 != pvVar4) {
      thunk_FUN_004098b0(s_Cannot_read_relocation_entries_f_00456fc8);
    }
  }
  return;
}


/* ==== FUN_004153a6 @ 004153a6 ==== */

undefined4 __cdecl FUN_004153a6(uint *param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  char *local_a4;
  uint local_a0;
  uint local_9c;
  int local_98;
  int local_94;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int *local_70;
  int *local_4c;
  int local_48;
  int local_44;
  int local_40;
  undefined4 local_3c;
  uint local_38;
  int *local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int *local_20;
  int local_1c;
  int *local_18;
  int local_14;
  int local_10;
  uint local_c;
  uint local_8;
  
  local_2c = param_2 + 0x40;
  local_34 = (int *)(param_2 + 0x60);
  local_4c = (int *)(param_2 + 0x80);
  local_28 = *(int *)(param_2 + 0x40);
  local_24 = *(int *)(param_2 + 0x44);
  if ((((local_28 < 0) || (local_24 < 0)) || (*(int *)(param_3 + 0x48) < local_28)) ||
     (*(int *)(param_3 + 0x48) < local_24)) {
    thunk_FUN_004098b0(s_Invalid_section_number_data_00456ffc);
  }
  if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
    local_44 = 4;
    local_48 = 4;
    local_40 = 0;
    local_3c = 0;
    local_48 = thunk_FUN_0042f1ca(*(uint *)(param_2 + 0x48) & 0xf);
    local_44 = thunk_FUN_0042fd64(local_48,*(uint *)(param_2 + 0x48) & 0xf700);
    local_40 = thunk_FUN_0042f326(*(uint *)(param_2 + 0x48) & 0x30);
    local_c = *(uint *)(param_2 + 0x4c);
  }
  else {
    local_48 = *(int *)(local_2c + 0xc);
    local_44 = *(int *)(local_2c + 0x10);
    local_40 = *(int *)(local_2c + 0x14);
    local_3c = *(undefined4 *)(local_2c + 0x18);
    local_c = *(uint *)(local_2c + 8);
  }
  if ((local_48 != 4) && (local_44 == 4)) {
    local_44 = local_48;
  }
  if ((param_1 == (uint *)0x0) ||
     (puVar1 = thunk_FUN_0042bc50(param_1,local_28,&local_48,1), puVar1 != (undefined4 *)0x0)) {
    iVar5 = local_28;
    if ((local_c & 0x20) != 0) {
      local_30 = local_28;
      local_28 = local_24;
      local_24 = iVar5;
    }
    local_20 = *(int **)(DAT_00461de8 + local_28 * 4);
    while ((local_20 != (int *)0x0 &&
           ((*(int *)(*(int *)*local_20 + 8) != local_48 ||
            (*(int *)(*(int *)*local_20 + 0x10) != local_40))))) {
      local_20 = (int *)local_20[5];
    }
    if (local_20 == (int *)0x0) {
      thunk_FUN_0042bc50(*(uint **)**(undefined4 **)**(undefined4 **)(DAT_00461de8 + local_28 * 4),
                         local_28,&local_48,1);
      local_20 = *(int **)(DAT_00461de8 + local_28 * 4);
      while ((local_20 != (int *)0x0 &&
             ((*(int *)(*(int *)*local_20 + 8) != local_48 ||
              (*(int *)(*(int *)*local_20 + 0x10) != local_40))))) {
        local_20 = (int *)local_20[5];
      }
      if (local_20 == (int *)0x0) {
        thunk_FUN_004098b0(s_Section_map_lookup_failure_00457018);
      }
      else {
        DAT_00461dec = local_20;
      }
    }
    else {
      DAT_00461dec = local_20;
    }
    DAT_00461ddc = (int *)*DAT_00461dec;
    if (DAT_00461ddc == (int *)0x0) {
      thunk_FUN_004098b0(s_Cannot_set_current_section_00457034);
    }
    DAT_004612a4 = *(int *)(*(int *)*DAT_00461ddc + 4);
    if (local_24 == local_28) {
      DAT_00461df0 = DAT_00461dec;
      DAT_00461de0 = DAT_00461ddc;
    }
    else {
      local_20 = *(int **)(DAT_00461de8 + local_24 * 4);
      while ((local_20 != (int *)0x0 &&
             ((*(int *)(*(int *)*local_20 + 8) != local_48 ||
              (*(int *)(*(int *)*local_20 + 0x10) != local_40))))) {
        local_20 = (int *)local_20[5];
      }
      if (local_20 == (int *)0x0) {
        thunk_FUN_0042bc50(*(uint **)**(undefined4 **)**(undefined4 **)(DAT_00461de8 + local_24 * 4)
                           ,local_24,&local_48,1);
        local_20 = *(int **)(DAT_00461de8 + local_24 * 4);
        while ((local_20 != (int *)0x0 &&
               ((*(int *)(*(int *)*local_20 + 8) != local_48 ||
                (*(int *)(*(int *)*local_20 + 0x10) != local_40))))) {
          local_20 = (int *)local_20[5];
        }
        if (local_20 == (int *)0x0) {
          thunk_FUN_004098b0(s_Section_map_lookup_failure_00457050);
        }
        else {
          DAT_00461df0 = local_20;
        }
      }
      else {
        DAT_00461df0 = local_20;
      }
      DAT_00461de0 = (int *)*DAT_00461df0;
    }
    if (DAT_00461de0 == (int *)0x0) {
      thunk_FUN_004098b0(s_Current_relocation_section_not_a_0045706c);
    }
    DAT_004612a8 = *(int *)(*(int *)*DAT_00461de0 + 4);
    DAT_00461dd4 = *(undefined4 *)(*DAT_00461de0 + 0x70);
    DAT_00461ddc[0x10] = (int)DAT_00461de0;
    DAT_004612a0 = local_24;
    DAT_00457b88 = (local_c & 0x1000) != 0;
    DAT_00457b74 = (local_c & 0x100) != 0;
    DAT_00461218 = (local_c & 0x200) != 0;
    DAT_0046121c = (local_c & 0x800) != 0;
    DAT_00461220 = (local_c & 0x20) != 0;
    if (((DAT_00461224 == '\0') || (DAT_00461138 != local_28)) || (DAT_0046113c != local_24)) {
      DAT_00461224 = (local_c & 0x20) != 0;
    }
    uVar6 = local_c & 0x10000;
    DAT_00461138 = local_28;
    DAT_0046113c = local_24;
    DAT_00457b8c = DAT_00457b88;
    *(uint *)(*DAT_00461de0 + 4) = *(uint *)(*DAT_00461de0 + 4) | local_c & 0x40000;
    local_c = local_c & 0xfffaf48f;
    DAT_00457b98 = '\x01';
    if (DAT_00461294 == 2) {
      if ((DAT_00461224 == '\0') && (DAT_004612a4 != DAT_004612a8)) {
        local_70 = DAT_00461ddc;
        local_20 = DAT_00461dec;
      }
      else {
        local_70 = DAT_00461de0;
        local_20 = DAT_00461df0;
      }
      if (local_20[4] != DAT_00461e68) {
        local_20[3] = local_70[5] - local_70[4];
        local_20[4] = DAT_00461e68;
      }
    }
    DAT_00461e90 = (int *)(DAT_00461e64 + -8 + *(int *)(param_2 + 0x10) * 8);
    DAT_00461e94 = DAT_00461e90;
    local_18 = DAT_00461e90;
    if (DAT_00461e90 == (int *)0x0) {
      thunk_FUN_004098b0(s_Cannot_set_section_counter_00457098);
    }
    if (DAT_00461294 == 1) {
      *local_18 = *(int *)(param_3 + 0x74) + (*(int *)(param_2 + 0x10) + -1) * 0x34;
      local_18[1] = param_2;
      DAT_00461ec8 = DAT_00461ec8 + *(int *)(*local_18 + 0x2c);
      if ((*(uint *)(*local_18 + 0x30) & 0x88) == 0) {
        DAT_00461ea8 = DAT_00461ea8 + *(int *)(*local_18 + 0x18);
        DAT_00461eb4 = DAT_00461eb4 + *(int *)(*local_18 + 0x28);
      }
    }
    if ((local_c & 0x2000) == 0) {
      if (((local_c & 0x1000) != 0) && ((*(uint *)(*local_18 + 0x30) & 8) != 0)) {
        if (local_48 == 3) {
          local_78 = *(int *)(*local_18 + 0x18) / 2;
        }
        else {
          local_78 = *(int *)(*local_18 + 0x18);
        }
        DAT_004612bc = local_78;
        if (local_48 == 3) {
          local_7c = *(int *)(*local_18 + 0x18) / 2;
        }
        else {
          local_7c = *(int *)(*local_18 + 0x18);
        }
        *(int *)(*DAT_00461de0 + 0x38) = *(int *)(*DAT_00461de0 + 0x38) + local_7c;
        if (local_48 == 3) {
          local_80 = *(int *)(*local_18 + 0x18) / 2;
        }
        else {
          local_80 = *(int *)(*local_18 + 0x18);
        }
        *(int *)(*DAT_00461de0 + 0x3c) = *(int *)(*DAT_00461de0 + 0x3c) + local_80;
      }
      DAT_004612b8 = 0;
      DAT_004612c0 = 0;
      local_4c = local_34;
      uVar3 = local_c;
    }
    else {
      if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
        local_84 = *(int *)(param_2 + 0x50);
      }
      else {
        local_84 = *local_34;
      }
      local_30 = local_84;
      if (local_84 == DAT_004612ac) {
        DAT_00461204 = '\0';
      }
      else {
        if (local_84 != DAT_004612ac + 1) {
          if (DAT_00461294 == 1) {
            thunk_FUN_00409a25(s_Buffer_out_of_order_004570b4);
          }
          return 0;
        }
        DAT_00461204 = '\x01';
        DAT_004612ac = DAT_004612ac + 1;
        DAT_004612b0 = DAT_004612b0 + 1;
      }
      DAT_004612b4 = DAT_004612b4 + 1;
      if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
        DAT_004612b8 = *(uint *)(param_2 + 0x54);
        DAT_004612c0 = *(uint *)(param_2 + 0x58);
      }
      else {
        DAT_004612b8 = local_34[1];
        DAT_004612c0 = local_34[2];
      }
      DAT_00457b98 = '\x01' - ((DAT_004612b8 & 0x2000) != 0);
      if ((DAT_00457b98 == '\0') || ((DAT_00461de0[3] & 0x2000U) == 0)) {
        DAT_00461de0[3] = DAT_00461de0[3] | DAT_004612b8 & 0x2000;
      }
      else {
        thunk_FUN_00409d88(s_Cannot_deactivate_load_alignment_004570c8);
      }
      DAT_004612b8 = DAT_004612b8 & 0xffffdfff;
      uVar4 = DAT_00461de0[2];
      uVar3 = local_c | uVar4 & 0x20000;
      if (((local_c & 0x1000) != 0) && (DAT_00461204 != '\0')) {
        *(uint *)(*DAT_00461de0 + 0x38) = *(int *)(*DAT_00461de0 + 0x38) + DAT_004612c0;
        *(uint *)(*DAT_00461de0 + 0x3c) = *(int *)(*DAT_00461de0 + 0x3c) + DAT_004612c0;
        if (((local_c & 0x4000) != 0) && ((local_c & 0x20000) != 0 || (uVar4 & 0x20000) != 0)) {
          local_c = uVar3;
          thunk_FUN_00409a25(s_Autoaligned_buffer_not_allowed_i_00457108);
          uVar3 = local_c;
        }
      }
    }
    local_c = uVar3;
    if ((local_c & 0x4000) == 0) {
      DAT_0046c2e4 = 4;
      DAT_0046c2e0 = 4;
    }
    else {
      if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
        local_88 = *(int *)(param_2 + 0x50);
      }
      else {
        local_88 = local_4c[4];
      }
      local_30 = local_88;
      if (local_88 == DAT_004612c8 + 1) {
        DAT_004612c8 = DAT_004612c8 + 1;
        DAT_004612cc = DAT_004612cc + 1;
      }
      else if (local_88 != DAT_004612c8) {
        if (DAT_00461294 == 1) {
          thunk_FUN_00409a25(s_Overlay_out_of_order_00457134);
        }
        return 0;
      }
      if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
        DAT_0046c2e4 = 4;
        DAT_0046c2e0 = 4;
        DAT_0046c2e8 = 0;
        DAT_0046c2ec = 0;
        DAT_0046c2e0 = thunk_FUN_0042f1ca(*(uint *)(param_2 + 0x54) & 0xf);
        DAT_0046c2e4 = thunk_FUN_0042fd64(DAT_0046c2e0,*(uint *)(param_2 + 0x54) & 0xf700);
        DAT_0046c2e8 = thunk_FUN_0042f326(*(uint *)(param_2 + 0x54) & 0x30);
      }
      else {
        DAT_0046c2e0 = *local_4c;
        DAT_0046c2e4 = local_4c[1];
        DAT_0046c2e8 = local_4c[2];
        DAT_0046c2ec = local_4c[3];
      }
      if (((DAT_00461fe8 < 6) && ((DAT_00461fe8 != 5 || (DAT_00461fec < 4)))) &&
         ((DAT_00461fe8 != 5 || ((DAT_00461fec != 3 || (DAT_00461ff0 < 3)))))) {
        local_8c = 0;
      }
      else {
        local_8c = local_4c[6];
      }
      DAT_00461d9c = local_8c;
      DAT_004612d0 = DAT_004612d0 + 1;
      DAT_00457b88 = (local_c & 0x8000) != 0;
      local_c = local_c & 0xffff7fff;
      if (DAT_00461294 == 1) {
        if (*(int *)(DAT_00461e60 + 4 + DAT_004612c8 * 0x24) == 0) {
          *(undefined4 *)(DAT_00461e60 + DAT_004612c8 * 0x24) = *(undefined4 *)(DAT_00461dbc + 8);
          *(undefined4 *)(DAT_00461e60 + 0x10 + DAT_004612c8 * 0x24) = 0;
          *(undefined4 *)(DAT_00461e60 + 4 + DAT_004612c8 * 0x24) = 0;
          *(int **)(DAT_00461e60 + 8 + DAT_004612c8 * 0x24) = DAT_00461ddc;
          *(int **)(DAT_00461e60 + 0xc + DAT_004612c8 * 0x24) = DAT_00461de0;
          if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
            local_90 = *(int *)(param_2 + 0x58);
          }
          else {
            local_90 = local_4c[5];
          }
          local_10 = local_90;
          if (local_90 < 0) {
            *(undefined4 *)(DAT_00461e60 + 0x20 + DAT_004612c8 * 0x24) = 0;
          }
          else {
            *(int *)(DAT_00461e60 + 0x20 + DAT_004612c8 * 0x24) =
                 *(int *)(param_3 + 0x90) + local_90;
          }
        }
        if (*(uint *)(DAT_00461e60 + 0x14 + DAT_004612c8 * 0x24) < DAT_004612c0) {
          *(uint *)(DAT_00461e60 + 0x14 + DAT_004612c8 * 0x24) = DAT_004612c0;
        }
      }
      if (((DAT_00461294 == 2) && (DAT_00457b88 != '\0')) &&
         (*(int *)(DAT_00461e60 + 0x14 + DAT_004612c8 * 0x24) != 0)) {
        uVar4 = *(uint *)(*(int *)(DAT_00461e60 + 4 + DAT_004612c8 * 0x24) + 0x10);
        uVar3 = thunk_FUN_00430b53(*(uint *)(DAT_00461e60 + 0x14 + DAT_004612c8 * 0x24));
        if (uVar4 != ((uVar4 - 1) + uVar3 & ~(uVar3 - 1))) {
          thunk_FUN_00409d88(s_Overlay_buffer_not_aligned_0045714c);
        }
        *(undefined4 *)(DAT_00461e60 + 0x14 + DAT_004612c8 * 0x24) = 0;
      }
    }
    FUN_0041999e(local_c,&local_48,*(int *)(*local_18 + 8));
    uVar4 = *(uint *)(*local_18 + 0x30) & 0x400;
    DAT_00461f0c = DAT_00461f0c + *(int *)(*local_18 + 0x2c);
    if ((DAT_00461270 != '\0') && (DAT_00461d70 == 0)) {
      if (*(int *)(DAT_00461de4 + 0x38) == 0) {
        thunk_FUN_0042a300(DAT_00461de4);
      }
      else {
        puVar1 = *(undefined4 **)(DAT_00461de4 + 0x38);
        if (puVar1[8] != *(int *)(DAT_00461dbc + 8)) {
          puVar1[4] = *puVar1;
          puVar1[5] = 0;
          puVar1[8] = *(undefined4 *)(DAT_00461dbc + 8);
        }
      }
    }
    if ((DAT_00461d7c & 0xf) == 0) {
      local_94 = 1;
    }
    else {
      local_94 = (int)(CONCAT44((int)DAT_00461d7c >> 0x1f,(int)DAT_00461d7c >> 4) /
                      (longlong)(int)(DAT_00461d7c & 0xf)) +
                 ((int)DAT_00461d7c >> 4 & (uint)((DAT_00461d7c & 1) == 0));
    }
    local_1c = local_94;
    if ((DAT_00461d8c & 0xf) == 0) {
      local_98 = 1;
    }
    else {
      local_98 = (int)(CONCAT44((int)DAT_00461d8c >> 0x1f,(int)DAT_00461d8c >> 4) /
                      (longlong)(int)(DAT_00461d8c & 0xf)) +
                 ((int)DAT_00461d8c >> 4 & (uint)((DAT_00461d8c & 1) == 0));
    }
    local_14 = local_98;
    if (((DAT_00457b78 == '\0') || (DAT_00461d70 == 0x1c)) ||
       ((DAT_00461d70 == 0x11d || ((DAT_00461f44 == 4 && (DAT_00461d70 == 0)))))) {
      local_9c = DAT_00461f78;
    }
    else {
      local_9c = DAT_00461f74;
    }
    local_38 = local_9c;
    if ((((DAT_00457b78 == '\0') || (DAT_00461d80 == 0x1c)) || (DAT_00461d80 == 0x11d)) ||
       ((DAT_00461f44 == 4 && (DAT_00461d80 == 0)))) {
      local_a0 = DAT_00461f78;
    }
    else {
      local_a0 = DAT_00461f74;
    }
    if (DAT_00461294 == 1) {
      if (uVar4 == 0) {
        if (DAT_00461d80 == 3) {
          local_8 = *(int *)(*local_18 + 0x18) / 2;
        }
        else if ((DAT_00461d70 == 0x11f) || (DAT_00461d80 != 0x11f)) {
          local_8 = *(int *)(*local_18 + 0x18) * local_94;
        }
        else {
          local_8 = *(int *)(*local_18 + 0x18) / (int)DAT_00461f4c;
        }
      }
      else {
        local_8 = *(uint *)(*local_18 + 0x10);
        if ((DAT_00461d70 == 0x11f) || (DAT_00461d80 == 0x11f)) {
          local_8 = local_8 / *(uint *)(*local_18 + 0x18);
        }
      }
      DAT_00461d98 = *DAT_00461d90;
      if (((DAT_00461d90 == DAT_00461d94) || (DAT_00461218 == '\0')) || (uVar4 == 0)) {
        *DAT_00461d90 = *DAT_00461d90 + local_8;
      }
      else {
        *DAT_00461d90 = *DAT_00461d90 + local_8 / DAT_00461f4c;
      }
      *DAT_00461d90 = *DAT_00461d90 & local_9c;
      if (DAT_00461d90 != DAT_00461d94) {
        if (uVar4 == 0) {
          if (DAT_00461d80 == 3) {
            local_8 = *(int *)(*local_18 + 0x18) / 2;
          }
          else {
            local_8 = *(int *)(*local_18 + 0x18) * local_98;
          }
        }
        else {
          local_8 = *(uint *)(*local_18 + 0x10);
          if ((DAT_00461d70 == 0x11f) || (DAT_00461d80 == 0x11f)) {
            local_8 = local_8 / *(uint *)(*local_18 + 0x18);
          }
        }
        if ((DAT_00461218 == '\0') || (DAT_00461d80 == 0x1c)) {
          *DAT_00461d94 = *DAT_00461d94 + local_8;
        }
        else {
          *DAT_00461d94 = *DAT_00461d94 + local_8 * DAT_00461f4c;
        }
        *DAT_00461d94 = *DAT_00461d94 & local_a0;
        *(uint *)(*(int *)(DAT_00461e60 + 4 + DAT_004612c8 * 0x24) + 8) =
             *(uint *)(*(int *)(DAT_00461e60 + 4 + DAT_004612c8 * 0x24) + 8) | uVar6;
      }
    }
    else {
      if (DAT_00461248 == '\0') {
        if ((*(uint *)(*local_18 + 0x30) & 0x100) == 0) {
          memset((void *)*local_18,0,8);
          if (((*(uint *)(*local_18 + 0x30) & 8) == 0) &&
             ((*(uint *)(*local_18 + 0x30) & 0x80) == 0)) {
            if (DAT_00461d80 == 0) {
              local_a4 = &DAT_00457fb8;
            }
            else {
              local_a4 = &DAT_00457fc8;
            }
          }
          else {
            local_a4 = &DAT_00457168;
          }
          strcpy((char *)*local_18,local_a4);
          thunk_FUN_004307d5((undefined1 *)*local_18,4,2);
        }
        else if (*(int *)*local_18 == 0) {
          iVar5 = thunk_FUN_00429716((uint *)(*(int *)(param_3 + 0x90) + *(int *)(*local_18 + 4)));
          *(int *)(*local_18 + 4) = iVar5;
        }
        else {
          thunk_FUN_004307d5((undefined1 *)*local_18,4,2);
        }
      }
      else if (*(int *)*local_18 == 0) {
        iVar5 = thunk_FUN_00429716((uint *)(*(int *)(param_3 + 0x90) + *(int *)(*local_18 + 4)));
        *(int *)(*local_18 + 4) = iVar5;
      }
      else {
        thunk_FUN_004307d5((undefined1 *)*local_18,4,2);
      }
      *(uint *)(*local_18 + 8) = *DAT_00461d94;
      if (uVar4 == 0) {
        *(uint *)(*local_18 + 0x10) = *DAT_00461d94;
      }
      DAT_00461e98 = DAT_00461e98 + 1;
    }
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}


/* ==== FUN_00416622 @ 00416622 ==== */

undefined4 __cdecl FUN_00416622(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  float10 fVar5;
  int local_98;
  uint local_94;
  uint local_90;
  uint local_8c;
  uint local_88;
  uint local_84;
  uint local_80;
  undefined4 *local_74;
  int local_6c [2];
  undefined8 local_64;
  uint local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  uint local_4c;
  undefined4 local_48;
  uint local_44;
  int local_40;
  int local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  undefined4 local_28;
  int *local_24;
  int *local_20;
  undefined4 local_1c;
  undefined4 *local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  
  iVar2 = DAT_004612c0;
  bVar4 = DAT_0046c2e0 != 4;
  memset(local_6c,0,0x68);
  if (*(int *)(param_2 + 0x18) != 0xd4) {
    if (DAT_00461de0 == (int *)0x0) {
      thunk_FUN_004098b0(s_Current_relocation_section_not_a_00457170);
    }
    if (DAT_00461df0 == (undefined4 *)0x0) {
      thunk_FUN_004098b0(s_Current_relocation_map_not_avail_0045719c);
    }
    local_6c[0] = param_1;
    local_44 = 0;
    local_3c = 4;
    local_40 = 4;
    local_38 = 0;
    local_34 = 0;
    if ((0 < *(int *)(param_2 + 0x10)) || ((*(uint *)(param_2 + 0x14) & 0x30) == 0x10)) {
      local_3c = *(int *)(param_2 + 0xc);
      local_40 = thunk_FUN_0042fc54(local_3c);
      if (local_40 == 0xa2c2a) {
        thunk_FUN_00409bfd(s_Invalid_symbol_memory_mapping_004571c4,param_1);
        return 0;
      }
      if (local_40 != 4) {
        if ((DAT_00457b88 == '\0') || (*(int *)(param_2 + 0x10) < 1)) {
          local_80 = 0;
        }
        else {
          local_80 = 0x1000;
        }
        local_44 = local_80;
      }
    }
    if (((*(int *)(param_2 + 0x14) == 6) || (*(int *)(param_2 + 0x14) == 7)) && (local_40 == 4)) {
      local_44 = local_44 | 0x200;
    }
    else {
      local_44 = local_44 | 0x100;
    }
    if ((*(int *)(param_2 + 0x14) == 5) && (local_40 == 4)) {
      local_44 = local_44 | 0x800;
    }
    if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
      if (*(int *)(param_2 + 0x18) == 2) {
        local_8c = 0x40;
      }
      else if (*(int *)(param_2 + 0x18) == 0xd2) {
        local_90 = 0x40;
        local_8c = local_90;
      }
      else if (*(int *)(param_2 + 0x18) == 0xd3) {
        local_94 = 0x80;
        local_8c = local_94;
      }
      else {
        local_8c = (-(uint)(*(int *)(param_2 + 0x18) != 0x6a) & 0xffffffa0) + 0x80;
      }
    }
    else if (*(int *)(param_2 + 0x18) == 2) {
      local_84 = 0x40;
      local_8c = local_84;
    }
    else if (*(int *)(param_2 + 0x18) == 0xd2) {
      local_88 = 0x40;
      local_8c = local_88;
    }
    else {
      local_8c = (-(uint)(*(int *)(param_2 + 0x18) != 0xd3) & 0xffffffa0) + 0x80;
    }
    local_44 = local_44 | local_8c;
    uVar3 = local_44 | -(uint)(iVar2 != 0) & 0x2000 | -(uint)bVar4 & 0x4000;
    local_64 = (double)((ulonglong)local_64._4_4_ << 0x20);
    if ((local_44 & 0x200) == 0) {
      if ((((local_44 & 0x800) == 0) && (-1 < *(int *)(param_2 + 0xc))) &&
         (*(int *)(param_2 + 0xc) < 0x124)) {
        local_64 = 0.0;
        local_5c = *(uint *)(param_2 + 8);
        local_44 = uVar3;
        if ((DAT_00461f44 == 4) && (local_40 == 0)) {
          local_64 = (double)(((ulonglong)
                               ((local_5c & ~DAT_00461f6c) >> ((byte)DAT_00461f58 & 0x1f)) & 0xf) <<
                             0x20);
          local_5c = local_5c & DAT_00461f6c;
          local_44 = uVar3 | 0x800;
        }
        if ((DAT_00461f44 == 6) && (local_40 == 0)) {
          local_64 = (double)((ulonglong)
                              ((local_5c & ~DAT_00461f6c) >> ((byte)DAT_00461f58 & 0x1f) &
                              DAT_00461f6c) << 0x20);
          local_44 = local_44 | 0x800;
        }
      }
      else {
        local_64 = (double)((ulonglong)*(uint *)(param_2 + 0xc) << 0x20);
        local_5c = *(uint *)(param_2 + 8);
        local_44 = uVar3;
      }
    }
    else {
      local_44 = uVar3;
      fVar5 = thunk_FUN_00408ba1(*(undefined4 *)(param_2 + 0xc),*(undefined4 *)(param_2 + 8));
      local_64 = (double)fVar5;
    }
    local_54 = (undefined4)local_64;
    local_50 = local_64._4_4_;
    local_4c = local_5c;
    local_48 = local_58;
    local_30 = *(undefined4 *)(param_2 + 0x10);
    local_2c = 0;
    if (((DAT_00461270 != '\0') && (local_40 == 0)) && ((local_44 & 0x1000) != 0)) {
      piVar1 = *(int **)(DAT_00461de4 + 0x38);
      if ((piVar1 != (int *)0x0) && (*piVar1 != 0)) {
        local_2c = piVar1[4] + piVar1[5];
      }
      if (*(int *)(*DAT_00461de0 + 0x68) != 0) {
        local_1c = *(undefined4 *)(*DAT_00461de0 + 0x68);
      }
    }
    local_28 = *(undefined4 *)(*DAT_00461de0 + 0x38);
    local_24 = DAT_00461ddc;
    local_20 = DAT_00461de0;
    local_18 = DAT_00461df0;
    if (iVar2 == 0) {
      local_98 = 0;
    }
    else {
      local_98 = DAT_00461e5c + DAT_004612ac * 8;
    }
    local_14 = local_98;
    if (bVar4) {
      local_10 = DAT_00461e60 + DAT_004612c8 * 0x24;
    }
    else {
      local_10 = 0;
    }
    local_c = 0;
    if ((local_40 != 4) && (local_40 != DAT_00461d70)) {
      local_38 = DAT_00461d78;
      local_74 = *(undefined4 **)(DAT_00461de8 + DAT_004612a0 * 4);
      while ((local_74 != (undefined4 *)0x0 &&
             ((*(int *)(*(int *)*local_74 + 8) != local_40 ||
              (*(int *)(*(int *)*local_74 + 0x10) != DAT_00461d78))))) {
        local_74 = (undefined4 *)local_74[5];
      }
      if (local_74 == (undefined4 *)0x0) {
        local_24 = thunk_FUN_0042bc50(*(uint **)**(undefined4 **)
                                                  **(undefined4 **)(DAT_00461de8 + DAT_004612a0 * 4)
                                      ,DAT_004612a0,&local_40,1);
        local_74 = *(undefined4 **)(DAT_00461de8 + DAT_004612a0 * 4);
        while ((local_74 != (undefined4 *)0x0 &&
               ((*(int *)(*(int *)*local_74 + 8) != local_40 ||
                (*(int *)(*(int *)*local_74 + 0x10) != local_38))))) {
          local_74 = (undefined4 *)local_74[5];
        }
        local_20 = local_24;
        if (local_74 == (undefined4 *)0x0) {
          thunk_FUN_004098b0(s_Symbol_map_lookup_failure_004571e4);
        }
        else {
          local_18 = local_74;
        }
      }
      else {
        local_18 = local_74;
        local_24 = (int *)*local_74;
        local_20 = local_24;
      }
    }
    thunk_FUN_0042c6c1(local_6c);
  }
  return 1;
}


/* ==== FUN_00416bed @ 00416bed ==== */

void __cdecl FUN_00416bed(uint *param_1,int param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  uint local_c;
  
  if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
    iVar3 = 0x6a;
  }
  else {
    iVar3 = 0xd3;
  }
  local_c = (uint)(*(int *)(param_2 + 0x18) == iVar3);
  if (((DAT_004611d8 == 1) && (local_c != 1)) && (*(int *)(param_2 + 0x18) == 2)) {
    local_c = 1;
  }
  if (DAT_00461ddc == (undefined4 *)0x0) {
    thunk_FUN_004098b0(s_Current_section_not_available_00457200);
  }
  thunk_FUN_0042cae9(param_1,0,local_c);
  if (local_c != 0) {
    piVar1 = (int *)thunk_FUN_0042e170(8);
    uVar2 = strlen((char *)param_1);
    iVar3 = thunk_FUN_0042e170(uVar2 + 1);
    *piVar1 = iVar3;
    strcpy((char *)*piVar1,(char *)param_1);
    if (DAT_00461214 != '\0') {
      thunk_FUN_00430037((char *)*piVar1);
    }
    piVar1[1] = *(int *)(*(int *)*DAT_00461ddc + 0xc);
    *(int **)(*(int *)*DAT_00461ddc + 0xc) = piVar1;
  }
  return;
}


/* ==== FUN_00416cf8 @ 00416cf8 ==== */

void __cdecl FUN_00416cf8(int *param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  bool bVar7;
  undefined1 uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  int *piVar12;
  undefined3 extraout_var;
  int *piVar13;
  int iVar14;
  bool bVar15;
  int local_b4;
  uint local_b0;
  int local_ac;
  int local_a8;
  uint local_a4;
  uint local_a0;
  uint local_9c;
  int local_98;
  uint local_94;
  uint *local_78;
  int *local_6c;
  int local_4c;
  uint *local_3c;
  uint local_34;
  uint *local_2c;
  int *local_28;
  double *local_c;
  
  uVar9 = DAT_00461d8c;
  local_2c = (uint *)0x0;
  if (DAT_00461de0 == (int *)0x0) {
    thunk_FUN_004098b0(s_Current_relocation_section_not_a_00457220);
  }
  if (DAT_00461df0 == 0) {
    thunk_FUN_004098b0(s_Current_relocation_map_not_avail_0045724c);
  }
  iVar2 = DAT_00461de0[4];
  iVar14 = *(int *)(DAT_00461df0 + 4);
  iVar3 = *(int *)(DAT_00461df0 + 8);
  iVar4 = *(int *)(*DAT_00461de0 + 0x3c);
  uVar5 = DAT_00461de0[2];
  piVar6 = *(int **)(DAT_00461de4 + 0x38);
  if (((DAT_00461270 == '\0') || (piVar6 == (int *)0x0)) || (piVar6[1] == 0)) {
    bVar7 = false;
  }
  else {
    bVar7 = true;
  }
  local_34 = 1;
  if ((*(uint *)(*param_1 + 0x30) & 0x400) != 0) {
    if (DAT_00461218 == '\0') {
      local_94 = *(uint *)(*param_1 + 0x10);
    }
    else {
      local_94 = *(uint *)(*param_1 + 0x10) / DAT_00461f4c;
    }
    local_34 = local_94;
    if (((DAT_0046121c != '\0') && (DAT_00461d90 != DAT_00461d94)) ||
       ((DAT_00461d70 == 0x11f || (DAT_00461d80 == 0x11f)))) {
      local_34 = local_94 / *(uint *)(*param_1 + 0x18);
    }
  }
  if ((DAT_00461d7c & 0xf) == 0) {
    local_98 = 1;
  }
  else {
    local_98 = (int)(CONCAT44((int)DAT_00461d7c >> 0x1f,(int)DAT_00461d7c >> 4) /
                    (longlong)(int)(DAT_00461d7c & 0xf)) +
               ((int)DAT_00461d7c >> 4 & (uint)((DAT_00461d7c & 1) == 0));
  }
  if ((uVar9 & 0xf) == 0) {
    local_9c = 1;
  }
  else {
    local_9c = ((int)uVar9 >> 4) / (int)(uVar9 & 0xf) + ((int)uVar9 >> 4 & (uint)((uVar9 & 1) == 0))
    ;
  }
  if (((DAT_00457b78 == '\0') || (DAT_00461d70 == 0x1c)) ||
     ((DAT_00461d70 == 0x11d || ((DAT_00461f44 == 4 && (DAT_00461d70 == 0)))))) {
    local_a0 = DAT_00461f78;
  }
  else {
    local_a0 = DAT_00461f74;
  }
  if ((((DAT_00457b78 == '\0') || (DAT_00461d80 == 0x1c)) || (DAT_00461d80 == 0x11d)) ||
     ((DAT_00461f44 == 4 && (DAT_00461d80 == 0)))) {
    local_a4 = DAT_00461f78;
  }
  else {
    local_a4 = DAT_00461f74;
  }
  DAT_00461e58 = 1;
  if (*(int *)(*param_1 + 0x28) != 0) {
    local_2c = (uint *)(*(int *)(param_2 + 0x84) +
                       ((uint)(*(int *)(*param_1 + 0x20) - *(int *)(*(int *)(param_2 + 0x74) + 0x20)
                              ) / 0xc) * 0xc);
    for (local_78 = local_2c; local_78 < local_2c + *(int *)(*param_1 + 0x28) * 3;
        local_78 = local_78 + 3) {
      if (DAT_00461248 == '\0') {
        if (DAT_00457b8c != '\0') {
          uVar9 = *local_78;
          *local_78 = *local_78 + iVar2;
          if ((uVar5 & 0x20000) == 0) {
            *local_78 = *local_78 + iVar14;
          }
          else if ((uVar5 & 0x2000) == 0) {
            *local_78 = *local_78 + (iVar3 - iVar4);
          }
          else {
            *local_78 = *local_78 - *(int *)(DAT_00461e5c + 4 + DAT_004612ac * 8);
          }
          if (DAT_00461d90 == DAT_00461d94) {
            *local_78 = *local_78 + *(int *)(*DAT_00461de0 + 0x58);
          }
          else {
            *local_78 = *local_78 + *(int *)(DAT_00461e60 + 0x18 + DAT_004612c8 * 0x24);
          }
          if ((bVar7) && ((*(uint *)(DAT_00461de4 + 8) & 0x2000) == 0)) {
            if (piVar6[2] == piVar6[1]) {
              local_a8 = piVar6[2] + -1;
            }
            else {
              local_a8 = piVar6[2];
            }
            iVar10 = piVar6[10] + local_a8 * 0x2c;
            local_4c = *(int *)(iVar10 + 0x1c);
            if ((piVar6[2] == piVar6[1]) || (*(uint *)(iVar10 + 4) != uVar9)) {
              if ((local_4c != 0) && (piVar6[2] != 0)) {
                *local_78 = *local_78 + *(int *)(piVar6[10] + 0x1c + (piVar6[2] + -1) * 0x2c);
              }
            }
            else {
              if ((local_4c != 0) && ((*(uint *)(iVar10 + 0x18) & 0x100) != 0)) {
                local_4c = local_4c + -1;
              }
              *local_78 = *local_78 + local_4c;
              piVar6[2] = piVar6[2] + 1;
            }
          }
        }
      }
      else {
        uVar9 = thunk_FUN_00429716((uint *)(*(int *)(param_2 + 0x90) + local_78[1]));
        local_78[1] = uVar9;
        if (DAT_00457b8c != '\0') {
          *local_78 = *local_78 + iVar14;
        }
      }
    }
  }
  if (((DAT_0046124c != '\0') && (DAT_00457b88 != '\0')) && (*(int *)(*param_1 + 0x2c) != 0)) {
    uVar11 = (uint)(*(int *)(*param_1 + 0x24) - *(int *)(*(int *)(param_2 + 0x74) + 0x24)) / 0xc;
    uVar9 = *(uint *)(param_2 + 0x54);
    piVar13 = (int *)(*(int *)(param_2 + 0x88) + uVar11 * 0xc);
    local_6c = piVar13;
    while ((local_6c < piVar13 + *(int *)(*param_1 + 0x2c) * 3 && (uVar11 <= uVar9))) {
      if (local_6c[2] != 0) {
        if (DAT_00461248 == '\0') {
          if (DAT_0046c2e0 == 4) {
            *local_6c = *local_6c + iVar2;
            if ((uVar5 & 0x20000) == 0) {
              *local_6c = *local_6c + iVar14;
            }
            else if ((uVar5 & 0x2000) == 0) {
              *local_6c = *local_6c + (iVar3 - iVar4);
            }
            else {
              *local_6c = *local_6c - *(int *)(DAT_00461e5c + 4 + DAT_004612ac * 8);
            }
            *local_6c = *local_6c + *(int *)(*DAT_00461de0 + 0x58);
          }
          else {
            *local_6c = *local_6c +
                        *(int *)(*(int *)(DAT_00461e60 + 0x10 + DAT_004612c8 * 0x24) + 0x10);
          }
        }
        else if (DAT_0046c2e0 == 4) {
          *local_6c = *local_6c + iVar14;
        }
        if ((bVar7) && ((*(uint *)(DAT_00461de4 + 8) & 0x2000) == 0)) {
          if (piVar6[3] == piVar6[1]) {
            local_ac = piVar6[3] + -1;
          }
          else {
            local_ac = piVar6[3];
          }
          piVar12 = (int *)(piVar6[10] + local_ac * 0x2c);
          local_4c = piVar12[7];
          if ((piVar6[3] == piVar6[1]) || (*piVar12 != *local_6c)) {
            if ((local_4c != 0) && (piVar6[3] != 0)) {
              *local_6c = *local_6c + *(int *)(piVar6[10] + 0x1c + (piVar6[3] + -1) * 0x2c);
            }
          }
          else {
            if ((local_4c != 0) && ((piVar12[6] & 0x100U) != 0)) {
              local_4c = local_4c + -1;
            }
            *local_6c = *local_6c + local_4c;
            piVar6[3] = piVar6[3] + 1;
          }
        }
      }
      local_6c = local_6c + 3;
    }
  }
  if (*(int *)(*param_1 + 0x18) != 0) {
    bVar15 = DAT_00461d80 == 3;
    if (*(int *)(*param_1 + 0x1c) == 0) {
      if (DAT_00461218 == '\0') {
        local_b0 = *(uint *)(*param_1 + 0x18);
      }
      else {
        local_b0 = *(int *)(*param_1 + 0x18) / (int)DAT_00461f4c;
      }
      local_34 = local_b0;
      if (DAT_00461d80 == 3) {
        local_34 = local_b0 >> 1;
      }
      local_34 = local_34 / local_9c;
      FUN_0041976c(local_34 * local_98);
      *DAT_00461d90 = *DAT_00461d90 + local_34 * local_98;
      *DAT_00461d90 = *DAT_00461d90 & local_a0;
      if (DAT_00461d90 == DAT_00461d94) {
        return;
      }
      if (DAT_00461218 == '\0') {
        *DAT_00461d94 = *DAT_00461d94 + local_34 * local_9c;
      }
      else {
        *DAT_00461d94 = *DAT_00461d94 + local_34 * DAT_00461f4c;
      }
      *DAT_00461d94 = *DAT_00461d94 & local_a4;
      return;
    }
    if (*(int *)(*param_1 + 0x28) == 0) {
      local_78 = (uint *)0x0;
    }
    else {
      local_78 = (uint *)(*(int *)(param_2 + 0x84) +
                         ((uint)(*(int *)(*param_1 + 0x20) -
                                *(int *)(*(int *)(param_2 + 0x74) + 0x20)) / 0xc) * 0xc);
      local_2c = local_78;
    }
    iVar14 = *(int *)(*param_1 + 0x1c) - *(int *)(*(int *)(param_2 + 0x74) + 0x1c);
    iVar2 = *(int *)(*param_1 + 0x18);
    puVar1 = (uint *)(*(int *)(param_2 + 0x78) + ((int)(iVar14 + (iVar14 >> 0x1f & 3U)) >> 2) * 4);
    for (local_3c = puVar1; local_3c < puVar1 + iVar2; local_3c = local_3c + bVar15 + DAT_00461e58)
    {
      DAT_00461280 = '\0';
      local_28 = (int *)0x0;
      local_c = (double *)0x0;
      if ((DAT_00461d70 == 0x11f) || (DAT_00461d80 != 0x11f)) {
        DAT_00461e58 = 1;
      }
      else {
        DAT_00461e58 = DAT_00461f4c;
      }
      DAT_00461e54 = 1;
      DAT_00457b9c = DAT_00461e58;
      if (((DAT_00461248 == '\0') && (local_78 != (uint *)0x0)) && (*DAT_00461d94 == *local_78)) {
        if ((bVar7) && (piVar6[10] != 0)) {
          if (*piVar6 == piVar6[1]) {
            local_b4 = *piVar6 + -1;
          }
          else {
            local_b4 = *piVar6;
          }
          piVar13 = (int *)(piVar6[10] + local_b4 * 0x2c);
          local_4c = piVar13[7];
          if ((local_4c != 0) && ((piVar13[6] & 0x100U) != 0)) {
            local_4c = local_4c + -1;
          }
          if (*piVar13 + local_4c == *DAT_00461d90) {
            uVar8 = thunk_FUN_0042a767();
            DAT_00461d68 = (char *)piVar13[10];
            if (CONCAT31(extraout_var,uVar8) == 2) {
              DAT_00461280 = '\x01';
              local_c = (double *)thunk_FUN_0040a571();
              DAT_00461d68 = (char *)((int)DAT_00461d68 + 1);
              if ((local_c != (double *)0x0) &&
                 (local_28 = thunk_FUN_0040a571(), local_28 == (int *)0x0)) {
                thunk_FUN_0040ca80((undefined *)local_c);
                local_c = (double *)0x0;
              }
            }
            else if (CONCAT31(extraout_var,uVar8) == 1) {
              DAT_00461d68 = (char *)((int)DAT_00461d68 + piVar13[8]);
              local_c = (double *)thunk_FUN_0040a571();
            }
            else {
              if (piVar13[9] == 0) {
                iVar14 = piVar13[8];
              }
              else {
                iVar14 = piVar13[9];
              }
              DAT_00461d68 = (char *)((int)DAT_00461d68 + iVar14);
              local_c = (double *)thunk_FUN_0040a571();
            }
          }
          else {
            DAT_00461d68 = (char *)(*(int *)(param_2 + 0x90) + local_78[1]);
            local_c = (double *)thunk_FUN_0040a571();
          }
        }
        else {
          DAT_00461d68 = (char *)(*(int *)(param_2 + 0x90) + local_78[1]);
          local_c = (double *)thunk_FUN_0043a289(param_2,local_3c,DAT_00461d68);
          if (local_c == (double *)0x0) {
            local_c = (double *)thunk_FUN_0040a571();
          }
        }
        if (local_c != (double *)0x0) {
          FUN_00417a64(local_c,(int)local_28,param_2,local_3c);
        }
        local_78 = local_78 + 3;
        if (local_2c + *(int *)(*param_1 + 0x28) * 3 <= local_78) {
          local_78 = (uint *)0x0;
        }
      }
      else if (DAT_00461270 != '\0') {
        **(uint **)(param_2 + 0x80) = *local_3c;
        *(int *)(param_2 + 0x80) = *(int *)(param_2 + 0x80) + 4;
        if (DAT_00461d70 == 3) {
          **(uint **)(param_2 + 0x80) = local_3c[1];
          *(int *)(param_2 + 0x80) = *(int *)(param_2 + 0x80) + 4;
        }
      }
      if (local_c != (double *)0x0) {
        thunk_FUN_0040ca80((undefined *)local_c);
      }
      if (local_28 != (int *)0x0) {
        thunk_FUN_0040ca80((undefined *)local_28);
      }
      if (DAT_00461280 != '\0') {
        local_34 = local_34 + 1;
      }
      FUN_0041976c(local_34 * DAT_00461e58);
      *DAT_00461d90 = *DAT_00461d90 + local_34 * local_98 * DAT_00461e54;
      *DAT_00461d90 = *DAT_00461d90 & local_a0;
      if (DAT_00461d90 != DAT_00461d94) {
        if (DAT_00461218 == '\0') {
          *DAT_00461d94 = *DAT_00461d94 + local_34 * local_9c * DAT_00461e58;
        }
        else {
          *DAT_00461d94 = *DAT_00461d94 + local_34 * DAT_00461f4c * DAT_00461e58;
        }
        *DAT_00461d94 = *DAT_00461d94 & local_a4;
      }
      if (DAT_00461280 != '\0') {
        local_34 = local_34 - 1;
      }
    }
  }
  DAT_00461280 = 0;
  return;
}


/* ==== FUN_00417a64 @ 00417a64 ==== */

void __cdecl FUN_00417a64(double *param_1,int param_2,int param_3,uint *param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 in_stack_ffffffc4;
  uint local_34;
  uint local_30;
  int local_2c;
  uint *local_28;
  uint *local_24;
  int local_18;
  uint local_10;
  uint local_8;
  
  local_8 = 0;
  if (((DAT_0046121c == '\0') || (DAT_00461d90 == DAT_00461d94)) &&
     (((DAT_00461f44 != 3 && (DAT_00461f44 != 5)) ||
      ((DAT_00461d70 != 0x11f && (DAT_00461d80 != 0x11f)))))) {
    if (DAT_00461d70 == 3) {
      if (*(int *)(param_1 + 2) == 0x100) {
        if (DAT_00461270 == '\0') {
          if ((DAT_00461f44 == 5) && (*(int *)(param_1 + 4) == 0x1e)) {
            *param_4 = *(uint *)(param_1 + 1) & 0xffff;
            param_4[1] = *(uint *)(param_1 + 1) >> 0x10;
          }
          else {
            *param_4 = *(uint *)(param_1 + 1) & DAT_00461f6c;
            if (*(int *)((int)param_1 + 0x1c) == 4) {
              local_34 = *(uint *)((int)param_1 + 4) & DAT_00461f6c;
            }
            else {
              local_34 = 0;
            }
            param_4[1] = local_34;
          }
        }
        else {
          **(uint **)(param_3 + 0x80) = *(uint *)(param_1 + 1) & DAT_00461f6c;
          *(int *)(param_3 + 0x80) = *(int *)(param_3 + 0x80) + 4;
          if (*(int *)((int)param_1 + 0x1c) == 4) {
            local_30 = *(uint *)((int)param_1 + 4) & DAT_00461f6c;
          }
          else {
            local_30 = 0;
          }
          **(uint **)(param_3 + 0x80) = local_30;
          *(int *)(param_3 + 0x80) = *(int *)(param_3 + 0x80) + 4;
        }
      }
      else if (DAT_00461f44 == 1) {
        if (DAT_00461270 == '\0') {
          thunk_FUN_00408bba(*(undefined4 *)param_1,*(undefined4 *)((int)param_1 + 4),param_4,
                             param_4 + 1);
        }
        else {
          thunk_FUN_00408bba(*(undefined4 *)param_1,*(undefined4 *)((int)param_1 + 4),
                             *(undefined4 **)(param_3 + 0x80),
                             (undefined4 *)(*(int *)(param_3 + 0x80) + 4));
          *(int *)(param_3 + 0x80) = *(int *)(param_3 + 0x80) + 8;
        }
      }
      else {
        thunk_FUN_00408616(*(undefined4 *)param_1,*(undefined4 *)((int)param_1 + 4),DAT_00461f64,
                           (uint *)param_1);
        if (DAT_00461270 == '\0') {
          *param_4 = *(uint *)(param_1 + 1) & DAT_00461f6c;
          param_4[1] = *(uint *)((int)param_1 + 4) & DAT_00461f6c;
        }
        else {
          **(uint **)(param_3 + 0x80) = *(uint *)(param_1 + 1) & DAT_00461f6c;
          *(int *)(param_3 + 0x80) = *(int *)(param_3 + 0x80) + 4;
          **(uint **)(param_3 + 0x80) = *(uint *)((int)param_1 + 4) & DAT_00461f6c;
          *(int *)(param_3 + 0x80) = *(int *)(param_3 + 0x80) + 4;
        }
      }
    }
    else {
      iVar3 = DAT_00461d7c >> 4;
      iVar2 = DAT_00461d8c >> 4;
      if (*(int *)(param_1 + 2) == 0x100) {
        local_8 = *(uint *)(param_1 + 1);
        if ((DAT_00461f44 == 0) || (DAT_00461f44 == 5)) {
          if ((DAT_00461f44 == 5) && (DAT_00461d74 == 0x1e)) {
            if ((0xff < local_8) &&
               (((local_8 & 0x80) == 0 || ((local_8 & 0xffffff00) != 0xffffff00)))) {
              thunk_FUN_00409d88(s_EMI_8_bit_memory_value_truncated_00457274);
            }
            local_8 = local_8 & 0xff;
          }
          else if ((DAT_00461f44 == 5) && ((DAT_00461d70 == 1 || (DAT_00461d70 == 2)))) {
            if ((0xffff < local_8) &&
               (((local_8 & 0x8000) == 0 || ((local_8 & 0xffff0000) != 0xffff0000)))) {
              thunk_FUN_00409d88(s_X_or_Y_16_bit_memory_value_trunc_00457298);
            }
            local_8 = local_8 & 0xffff;
          }
          else if ((DAT_00461f44 == 5) && (DAT_00461d70 == 0)) {
            if ((0xffffff < local_8) &&
               (((local_8 & 0x800000) == 0 || ((local_8 & 0xff000000) != 0xff000000)))) {
              thunk_FUN_00409d88(s_P_24_bit_memory_value_truncated_004572c0);
            }
            local_8 = local_8 & 0xffffff;
          }
          else if ((DAT_00461d7c != 0) || (DAT_00461d8c != 0)) {
            if ((iVar3 == 2) || (iVar2 == 2)) {
              if (((int)local_8 < -0x80) || (0x7f < (int)local_8)) {
                thunk_FUN_00409d88(s_EMI_8_bit_memory_value_truncated_004572e0);
              }
              local_8 = local_8 & 0xff;
            }
            else if ((iVar3 == 3) || (iVar2 == 3)) {
              if (((int)local_8 < -0x800) || (0x7ff < (int)local_8)) {
                thunk_FUN_00409d88(s_EMI_12_bit_memory_value_truncate_00457304);
              }
              local_8 = local_8 & 0xfff;
            }
            else if ((iVar3 == 4) || (iVar2 == 4)) {
              if (((int)local_8 < -0x8000) || (0x7fff < (int)local_8)) {
                if (DAT_00461f44 == 0) {
                  thunk_FUN_00409d88(s_EMI_16_bit_memory_value_truncate_00457328);
                }
                else {
                  thunk_FUN_00409d88(s_X_or_Y_16_bit_memory_value_trunc_0045734c);
                }
              }
              local_8 = local_8 & 0xffff;
            }
            else if ((iVar3 == 5) || (iVar2 == 5)) {
              if (((int)local_8 < -0x80000) || (0x7ffff < (int)local_8)) {
                thunk_FUN_00409d88(s_EMI_20_bit_memory_value_truncate_00457374);
              }
              local_8 = local_8 & 0xfffff;
            }
          }
        }
      }
      else if (DAT_00461f44 == 1) {
        local_8 = thunk_FUN_00408b90((float)*param_1);
      }
      else if ((DAT_00461f44 == 0) || (DAT_00461f44 == 5)) {
        if ((DAT_00461f44 == 5) && (DAT_00461d74 == 0x1e)) {
          local_8 = thunk_FUN_004088a3(*param_1,0xff,in_stack_ffffffc4);
        }
        else if ((DAT_00461f44 == 5) &&
                (((DAT_00461d70 == 0 || (DAT_00461d70 == 1)) || (DAT_00461d70 == 2)))) {
          local_8 = thunk_FUN_004088a3(*param_1,0xffff,in_stack_ffffffc4);
        }
        else if ((DAT_00461d7c == 0) && (DAT_00461d8c == 0)) {
          local_8 = thunk_FUN_00408739(*param_1,in_stack_ffffffc4);
        }
        else if ((iVar3 == 2) || (iVar2 == 2)) {
          local_8 = thunk_FUN_004088a3(*param_1,0xff,in_stack_ffffffc4);
        }
        else if ((iVar3 == 3) || (iVar2 == 3)) {
          local_8 = thunk_FUN_004088a3(*param_1,0xfff,in_stack_ffffffc4);
        }
        else if ((iVar3 == 4) || (iVar2 == 4)) {
          local_8 = thunk_FUN_004088a3(*param_1,0xffff,in_stack_ffffffc4);
        }
        else if ((iVar3 == 5) || (iVar2 == 5)) {
          local_8 = thunk_FUN_004088a3(*param_1,0xfffff,in_stack_ffffffc4);
        }
      }
      else {
        thunk_FUN_00408616(*(undefined4 *)param_1,*(undefined4 *)((int)param_1 + 4),DAT_00461f60,
                           (uint *)param_1);
        local_8 = *(uint *)(param_1 + 1);
      }
      switch(iVar2) {
      case 2:
        local_10 = 0xff;
        break;
      case 3:
        local_10 = 0xfff;
        break;
      case 4:
        local_10 = 0xffff;
        break;
      case 5:
        local_10 = 0xfffff;
        break;
      default:
        local_10 = DAT_00461f6c;
      }
      if (DAT_00461f44 == 5) {
        if (DAT_00461d70 == 0) {
          local_10 = DAT_00461f6c;
        }
        else if ((DAT_00461d70 == 1) || (DAT_00461d70 == 2)) {
          local_10 = 0xffff;
        }
        else if (DAT_00461d74 == 0x1e) {
          local_10 = 0xff;
        }
      }
      if (DAT_00461270 == '\0') {
        *param_4 = local_8 & local_10;
      }
      else {
        **(uint **)(param_3 + 0x80) = local_8 & local_10;
        *(int *)(param_3 + 0x80) = *(int *)(param_3 + 0x80) + 4;
        if (DAT_00461280 != '\0') {
          **(uint **)(param_3 + 0x80) = *(uint *)(param_2 + 8) & local_10;
          *(int *)(param_3 + 0x80) = *(int *)(param_3 + 0x80) + 4;
          *(int *)(param_3 + 0x40) = *(int *)(param_3 + 0x40) + 1;
        }
      }
    }
  }
  else {
    if (DAT_00461d70 == 0x11f) {
      DAT_00461e54 = DAT_00457b9c;
    }
    if ((((DAT_0046121c != '\0') && (DAT_00461d90 != DAT_00461d94)) || (DAT_00461d70 == 0x11f)) ||
       (DAT_00461d80 == 0x11f)) {
      if (DAT_00461270 == '\0') {
        local_28 = param_4;
      }
      else {
        local_28 = *(uint **)(param_3 + 0x80);
      }
      local_24 = local_28;
      DAT_00461e58 = DAT_00457b9c;
      uVar1 = *(uint *)(param_1 + 1);
      for (local_18 = 0; local_18 < DAT_00461e58; local_18 = local_18 + 1) {
        if ((DAT_0046121c == '\0') || (DAT_00461d90 == DAT_00461d94)) {
          local_2c = (DAT_00461e58 - local_18) + -1;
        }
        else {
          local_2c = local_18;
        }
        *local_24 = uVar1 >> ((byte)(local_2c << 3) & 0x1f) & 0xff;
        local_24 = local_24 + 1;
        if (DAT_00461270 != '\0') {
          *(int *)(param_3 + 0x80) = *(int *)(param_3 + 0x80) + 4;
        }
      }
    }
  }
  return;
}


/* ==== FUN_0041839c @ 0041839c ==== */

void __cdecl FUN_0041839c(int param_1,int param_2)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  uint n;
  char *dst;
  int *piVar4;
  char *pcVar5;
  int *piVar6;
  uint local_3c;
  uint local_34;
  int local_24;
  char *local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  piVar6 = (int *)(*(int *)(param_1 + 0x84) + param_2 * 0xc);
  DAT_00461d68 = (char *)(*(int *)(param_1 + 0x90) + piVar6[1]);
  iVar3 = strncmp(DAT_00461d68,&DAT_00457398,4);
  if (iVar3 != 0) {
    thunk_FUN_004098b0(s_Invalid__SDI_expression_004573a0);
  }
  pcVar5 = DAT_00461d68 + 4;
  bVar1 = false;
  if (*pcVar5 == '(') {
    DAT_00461d68 = DAT_00461d68 + 5;
  }
  else if (*pcVar5 == '2') {
    DAT_00461d68 = DAT_00461d68 + 6;
    bVar1 = true;
  }
  else {
    DAT_00461d68 = pcVar5;
    thunk_FUN_004098b0(s_Invalid__SDI_expression_004573b8);
  }
  pcVar5 = DAT_00461d68;
  local_1c = DAT_00461d68;
  if (__mb_cur_max < 2) {
    local_3c = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 0x103;
  }
  else {
    local_3c = _isctype((int)*DAT_00461d68,0x103);
  }
  if (local_3c == 0) {
    cVar2 = strchr(pcVar5,0x40);
    if ((char *)CONCAT31(extraout_var,cVar2) == (char *)0x0) {
      thunk_FUN_004098b0(s_Invalid__SDI_expression_004573d0);
    }
    cVar2 = strchr((char *)CONCAT31(extraout_var,cVar2),0x29);
    local_1c = (char *)CONCAT31(extraout_var_00,cVar2);
    if (local_1c == (char *)0x0) {
      thunk_FUN_004098b0(s_Invalid__SDI_expression_004573e8);
    }
  }
  cVar2 = strchr(local_1c,0x2c);
  pcVar5 = (char *)CONCAT31(extraout_var_01,cVar2);
  if (pcVar5 == (char *)0x0) {
    thunk_FUN_004098b0(s_Invalid__SDI_expression_00457400);
  }
  n = (int)pcVar5 - (int)DAT_00461d68;
  dst = (char *)thunk_FUN_0042e170(n + 1);
  strncpy(dst,DAT_00461d68,n);
  dst[n] = '\0';
  DAT_00461d68 = pcVar5 + 1;
  if (*pcVar5 != ',') {
    thunk_FUN_004098b0(s_Invalid__SDI_expression_00457418);
  }
  local_34 = 0;
  piVar4 = thunk_FUN_0040a571();
  if (piVar4 != (int *)0x0) {
    local_34 = piVar4[2];
  }
  cVar2 = *DAT_00461d68;
  DAT_00461d68 = DAT_00461d68 + 1;
  if (cVar2 != ',') {
    thunk_FUN_004098b0(s_Invalid__SDI_expression_00457430);
  }
  local_18 = 0;
  piVar4 = thunk_FUN_0040a571();
  if (piVar4 != (int *)0x0) {
    local_18 = piVar4[2];
  }
  cVar2 = *DAT_00461d68;
  DAT_00461d68 = DAT_00461d68 + 1;
  if (cVar2 != ',') {
    thunk_FUN_004098b0(s_Invalid__SDI_expression_00457448);
  }
  local_10 = 0;
  piVar4 = thunk_FUN_0040a571();
  if (piVar4 != (int *)0x0) {
    local_10 = piVar4[2];
  }
  cVar2 = *DAT_00461d68;
  DAT_00461d68 = DAT_00461d68 + 1;
  if (cVar2 != ',') {
    thunk_FUN_004098b0(s_Invalid__SDI_expression_00457460);
  }
  local_24 = 0;
  piVar4 = thunk_FUN_0040a571();
  if (piVar4 != (int *)0x0) {
    local_24 = piVar4[2];
  }
  local_14 = 0;
  if (bVar1) {
    cVar2 = *DAT_00461d68;
    DAT_00461d68 = DAT_00461d68 + 1;
    if (cVar2 != ',') {
      thunk_FUN_004098b0(s_Invalid__SDI_expression_00457478);
    }
    piVar4 = thunk_FUN_0040a571();
    if (piVar4 != (int *)0x0) {
      local_14 = piVar4[2];
    }
  }
  iVar3 = DAT_00461d98;
  if (DAT_00461d90 != DAT_00461d94) {
    iVar3 = DAT_00461d9c;
  }
  thunk_FUN_0042a38f(iVar3 + (*piVar6 - *(int *)(*DAT_00461e94 + 8)),*piVar6,(int)dst,local_18,
                     local_10,local_34,local_24,local_14);
  *(int *)(*(int *)(DAT_00461de4 + 0x38) + 0x14) =
       *(int *)(*(int *)(DAT_00461de4 + 0x38) + 0x14) + 1;
  return;
}


/* ==== FUN_0041874a @ 0041874a ==== */

void __cdecl FUN_0041874a(int param_1)

{
  undefined *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int local_14;
  
  if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
    local_14 = 1;
  }
  else {
    local_14 = 0;
  }
  if (*(int *)(param_1 + 8 + local_14 * 4) == 0) {
    if (DAT_00461f00 == (undefined4 *)0x0) {
      thunk_FUN_004098b0(s_Section_nesting_error_00457490);
    }
    puVar1 = (undefined *)DAT_00461f00;
    DAT_00461f00 = *(undefined4 **)((int)DAT_00461f00 + 4);
    thunk_FUN_0042e1ce(puVar1);
  }
  else {
    puVar2 = (undefined4 *)thunk_FUN_0042e170(8);
    if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
      uVar3 = *(undefined4 *)(param_1 + 8);
    }
    else {
      uVar3 = *(undefined4 *)(param_1 + 0x20);
    }
    *puVar2 = uVar3;
    puVar2[1] = DAT_00461f00;
    DAT_00461f00 = puVar2;
  }
  return;
}


/* ==== FUN_0041882a @ 0041882a ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0041882a(uint *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  char *local_e4;
  uint *local_e0;
  uint *local_dc;
  int local_d8;
  int local_d4;
  uint local_d0;
  uint local_cc;
  char *local_c8;
  char *local_c4;
  int local_c0;
  uint local_bc;
  uint local_b4 [8];
  int local_94;
  int local_90;
  char *local_8c;
  int local_88;
  int local_84;
  uint local_80;
  uint local_7c;
  uint local_78;
  undefined4 local_74;
  uint local_70;
  uint local_6c;
  int local_60;
  uint *local_5c;
  int local_58;
  uint local_54;
  int local_50;
  undefined4 local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  int local_28;
  int *local_24;
  uint *local_20;
  undefined4 *local_1c;
  int *local_18;
  uint *local_14;
  uint *local_10;
  uint *local_c;
  char *local_8;
  
  local_5c = param_1 + 8;
  local_20 = param_1 + 0x10;
  local_c = param_1 + 0x10;
  local_10 = param_1 + 0x18;
  local_14 = param_1 + 0x20;
  local_18 = (int *)0x0;
  local_24 = (int *)0x0;
  if ((DAT_00461248 != '\0') ||
     ((param_1[4] != 0 &&
      ((DAT_0046124c != '\0' ||
       ((((param_1[6] != 0x80 && (param_1[6] != 0xc9)) && (param_1[6] != 0xcb)) &&
        ((param_1[6] != 0xd6 && (param_1[6] != 0xd7)))))))))) {
    if (0 < (int)param_1[4]) {
      local_18 = (int *)(DAT_00461e64 + -8 + param_1[4] * 8);
    }
    if ((param_1[6] == 0x67) || (param_1[6] == 200)) {
      if (DAT_00461248 == '\0') {
        param_1[5] = 0;
      }
      if (param_1[0xc] != 0) {
        uVar1 = thunk_FUN_00429716((uint *)(*(int *)(param_2 + 0x90) + param_1[0xc]));
        local_5c[4] = uVar1;
      }
    }
    if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
      uVar1 = param_1[6];
      if (uVar1 == 2) {
        if (DAT_00461210 == '\0') {
          param_1[6] = 0xd2;
        }
      }
      else if (uVar1 == 6) {
        param_1[6] = 0xd5;
      }
      else if (uVar1 == 0x6a) {
        param_1[6] = 0xd3;
      }
    }
    if (param_1[6] == 0x80) {
      param_1[6] = 0xc9;
      if (param_1[3] == 0) {
        local_bc = 0;
      }
      else {
        local_bc = thunk_FUN_00429716((uint *)**(undefined4 **)*DAT_00461ddc);
      }
      param_1[2] = local_bc;
      param_1[3] = 0;
      param_1[7] = 1;
      memset(local_b4,0,0x20);
      local_5c = local_b4;
      local_b4[0] = *(uint *)(*(int *)*DAT_00461ddc + 4);
      local_b4[1] = 0;
    }
    else if (param_1[6] == 0xc9) {
      if (param_1[2] != 0) {
        uVar1 = thunk_FUN_00429716((uint *)(*(int *)(param_2 + 0x90) + param_1[2]));
        param_1[2] = uVar1;
      }
      *local_5c = *(uint *)(*(int *)*DAT_00461ddc + 4);
    }
    if ((param_1[6] == 3) && (param_1[5] == 0)) {
      local_c0 = 1;
    }
    else {
      local_c0 = 0;
    }
    local_94 = local_c0;
    if (local_c0 != 0) {
      if (DAT_0046124c == '\0') {
        local_5c[2] = 0;
      }
      if (DAT_00461248 == '\0') {
        if (local_18 == (int *)0x0) {
          thunk_FUN_004098b0(s_No_current_counter_map_004574a8);
        }
        memset(param_1,0,8);
        if (((*(uint *)(*local_18 + 0x30) & 8) == 0) && ((*(uint *)(*local_18 + 0x30) & 0x80) == 0))
        {
          if (DAT_00461d80 == 0) {
            local_c4 = &DAT_00457fb8;
          }
          else {
            local_c4 = &DAT_00457fc8;
          }
          local_c8 = local_c4;
        }
        else {
          local_c8 = &DAT_004574c0;
        }
        local_8c = local_c8;
        strcpy((char *)param_1,local_c8);
        param_1[7] = 1;
        local_5c[1] = 0;
        *(uint *)(*local_18 + 0xc) = DAT_00461d84;
        param_1[3] = DAT_00461d84;
        if ((*(uint *)(*local_18 + 0x30) & 0x400) == 0) {
          *(uint *)(*local_18 + 0x14) = DAT_00461d84;
        }
        if (((*(uint *)(*local_18 + 0x30) & 8) != 0) && ((DAT_00461de0[2] & 0x20000U) != 0)) {
          *(undefined4 *)(*local_18 + 0x14) = 4;
          *(undefined4 *)(*local_18 + 0xc) = 4;
          *(undefined4 *)(*local_18 + 0x10) = 0;
          *(undefined4 *)(*local_18 + 8) = 0;
          *(undefined4 *)(*local_18 + 0x18) = 0;
        }
      }
      else {
        if (DAT_00461df0 == (undefined4 *)0x0) {
          thunk_FUN_004098b0(s_Current_relocation_map_not_avail_004574c8);
        }
        param_1[2] = param_1[2] + DAT_00461df0[1];
        if (DAT_00461220 == '\0') {
          local_cc = *(uint *)(*(int *)*DAT_00461ddc + 4);
        }
        else {
          local_cc = *(uint *)(**(int **)DAT_00461ddc[0x10] + 4);
        }
        *local_20 = local_cc;
        if (DAT_00461220 == '\0') {
          local_d0 = *(uint *)(**(int **)DAT_00461ddc[0x10] + 4);
        }
        else {
          local_d0 = *(uint *)(*(int *)*DAT_00461ddc + 4);
        }
        local_20[1] = local_d0;
        if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
          memset(&local_48,0,0x20);
          memset(&local_80,0,0x20);
          local_48 = *local_20;
          local_44 = local_20[1];
          local_40 = local_20[3];
          local_3c = thunk_FUN_0042f1ca(local_20[2] & 0xf);
          local_38 = thunk_FUN_0042fd64(local_3c,local_20[2] & 0xf700);
          local_34 = thunk_FUN_0042f326(local_20[2] & 0x30);
          if (DAT_004612c0 == 0) {
            if (DAT_0046c2e0 != 4) {
              local_40 = local_40 |
                         *(uint *)(*(int *)(DAT_00461e60 + 4 + DAT_004612c8 * 0x24) + 8) & 0x10000;
              local_80 = DAT_0046c2e0;
              local_7c = DAT_0046c2e4;
              local_78 = DAT_0046c2e8;
              local_74 = DAT_0046c2ec;
              local_70 = DAT_004612cc;
              if ((int)local_20[6] < 0) {
                local_6c = local_20[6];
              }
              else {
                local_6c = thunk_FUN_00429716((uint *)(*(int *)(param_2 + 0x90) + local_20[6]));
              }
              param_1[7] = 3;
            }
          }
          else {
            local_80 = DAT_004612b0;
            local_7c = local_20[5];
            local_78 = local_20[6];
            param_1[7] = 3;
          }
        }
        else {
          if (DAT_004612c0 != 0) {
            *local_10 = DAT_004612b0;
          }
          if ((DAT_004612c0 == 0) && (DAT_0046c2e0 != 4)) {
            local_c[2] = local_c[2] |
                         *(uint *)(*(int *)(DAT_00461e60 + 4 + DAT_004612c8 * 0x24) + 8) & 0x10000;
            local_10[4] = DAT_004612cc;
            if (-1 < (int)local_10[5]) {
              uVar1 = thunk_FUN_00429716((uint *)(*(int *)(param_2 + 0x90) + local_10[5]));
              local_10[5] = uVar1;
            }
          }
          if ((DAT_004612c0 != 0) && (DAT_0046c2e0 != 4)) {
            local_c[2] = local_c[2] |
                         *(uint *)(*(int *)(DAT_00461e60 + 4 + DAT_004612c8 * 0x24) + 8) & 0x10000;
            local_14[4] = DAT_004612cc;
            if (-1 < (int)local_14[5]) {
              uVar1 = thunk_FUN_00429716((uint *)(*(int *)(param_2 + 0x90) + local_14[5]));
              local_14[5] = uVar1;
            }
          }
        }
      }
    }
    if ((((param_1[5] & 0x30) == 0x20) && (0 < (int)param_1[4])) && (*(int *)(param_2 + 0x88) != 0))
    {
      local_90 = *(int *)(param_2 + 0x88) + local_5c[3] * 0xc;
      local_5c[3] = (uint)(DAT_00461ec4 - DAT_00461ec0) / 0xc +
                    (local_90 - *(int *)(param_2 + 0x88)) / 0xc;
    }
    if (*param_1 == 0) {
      if ((local_94 == 0) || (local_18 == (int *)0x0)) {
        uVar1 = thunk_FUN_00429716((uint *)(*(int *)(param_2 + 0x90) + param_1[1]));
        param_1[1] = uVar1;
      }
      else {
        param_1[1] = *(uint *)(*local_18 + 4);
      }
    }
    if (((param_1[6] == 0) && (param_1[5] == 0)) &&
       ((*param_1 != 0 &&
        (((char)*param_1 == DAT_00457fd0 &&
         (iVar2 = strcmp((char *)param_1,&DAT_00457fd0), iVar2 == 0)))))) {
      local_d4 = 1;
    }
    else {
      local_d4 = 0;
    }
    local_88 = local_d4;
    if (local_d4 != 0) {
      uVar1 = thunk_FUN_00429716((uint *)(*(int *)(param_2 + 0x90) + param_1[2]));
      param_1[2] = uVar1;
    }
    if ((param_1[6] == 0xcb) && (param_1[2] != 0)) {
      uVar1 = thunk_FUN_00429716((uint *)(*(int *)(param_2 + 0x90) + param_1[2]));
      param_1[2] = uVar1;
    }
    if (param_1[6] == 0x81) {
      if (DAT_00461248 == '\0') {
        return;
      }
      DAT_00461ef4 = DAT_00461ef4 + 1;
      param_1[2] = param_1[2] + _DAT_00461ebc;
    }
    if (0 < (int)param_1[4]) {
      local_58 = 4;
      local_50 = 0;
      local_4c = 0;
      local_54 = param_1[3];
      local_58 = thunk_FUN_0042fc54(local_54);
      local_50 = DAT_00461d78;
      if (((local_58 == 4) || (local_58 == DAT_00461d70)) || (DAT_0046c2e0 != 4)) {
        local_1c = DAT_00461df0;
        local_24 = DAT_00461de0;
      }
      else {
        local_1c = *(undefined4 **)(DAT_00461de8 + DAT_004612a0 * 4);
        while ((local_1c != (undefined4 *)0x0 &&
               ((*(int *)(*(int *)*local_1c + 8) != local_58 ||
                (*(int *)(*(int *)*local_1c + 0x10) != DAT_00461d78))))) {
          local_1c = (undefined4 *)local_1c[5];
        }
        if (local_1c == (undefined4 *)0x0) {
          thunk_FUN_004098b0(s_Symbol_map_lookup_failure_004574f0);
        }
        else {
          local_24 = (int *)*local_1c;
        }
      }
      if (local_24 == (int *)0x0) {
        thunk_FUN_004098b0(s_Current_relocation_section_not_a_0045750c);
      }
      if (local_1c == (undefined4 *)0x0) {
        thunk_FUN_004098b0(s_Current_relocation_map_not_avail_00457538);
      }
      param_1[4] = DAT_00461e98;
      local_84 = *(int *)(DAT_00461de4 + 0x38);
      if (((DAT_00461270 == '\0') || (local_84 == 0)) || (*(int *)(local_84 + 4) == 0)) {
        local_d8 = 0;
      }
      else {
        local_d8 = 1;
      }
      local_28 = local_d8;
      if (((((DAT_00461248 != '\0') && (DAT_00457b8c != '\0')) && (local_88 == 0)) &&
          ((local_94 == 0 && (local_58 != 4)))) && (DAT_0046c2e0 == 4)) {
        param_1[2] = param_1[2] + local_1c[1];
      }
      if ((((DAT_00461248 == '\0') && (local_88 == 0)) &&
          (((local_94 == 0 && (((DAT_00457b88 != '\0' && (local_58 != 4)) && (DAT_0046c2e0 != 4))))
           && ((param_1[2] = param_1[2] +
                             *(int *)(*(int *)(DAT_00461e60 + 0x10 + DAT_004612c8 * 0x24) + 0x10),
               local_d8 != 0 && (*(int *)(local_84 + 0x28) != 0)))))) &&
         (((*(int *)(local_84 + 0x10) != 0 || (*(int *)(local_84 + 0x14) != 0)) &&
          (((local_58 == 0 && (DAT_00457b88 != '\0')) && (0 < (int)param_1[4])))))) {
        param_1[2] = param_1[2] +
                     *(int *)(*(int *)(local_84 + 0x28) + 0x1c +
                             (*(int *)(local_84 + 0x10) + -1 + *(int *)(local_84 + 0x14)) * 0x2c);
      }
      if ((((DAT_00461248 == '\0') && (local_88 == 0)) && (DAT_00457b8c != '\0')) &&
         ((local_58 != 4 && ((DAT_0046c2e0 == 4 || (local_94 != 0)))))) {
        param_1[2] = param_1[2] + local_24[4];
        if ((local_24[2] & 0x20000U) == 0) {
          param_1[2] = param_1[2] + local_1c[1];
        }
        else if ((local_24[2] & 0x2000U) == 0) {
          param_1[2] = param_1[2] + (local_1c[2] - *(int *)(*local_24 + 0x38));
          if ((local_94 != 0) && ((*(uint *)(*local_18 + 0x30) & 8) != 0)) {
            param_1[3] = 4;
            param_1[2] = 0;
          }
        }
        else {
          param_1[2] = param_1[2] - *(int *)(DAT_00461e5c + 4 + DAT_004612ac * 8);
        }
        if ((((local_d8 != 0) && (*(int *)(local_84 + 0x28) != 0)) &&
            ((*(int *)(local_84 + 0x10) != 0 || (*(int *)(local_84 + 0x14) != 0)))) &&
           ((((local_58 == 0 && (DAT_00457b88 != '\0')) && (0 < (int)param_1[4])) &&
            ((local_24[2] & 0x2000U) == 0)))) {
          param_1[2] = param_1[2] +
                       *(int *)(*(int *)(local_84 + 0x28) + 0x1c +
                               (*(int *)(local_84 + 0x10) + -1 + *(int *)(local_84 + 0x14)) * 0x2c);
        }
        if (((*(int *)(*local_24 + 0x68) != 0) && (*(int *)(*(int *)(*local_24 + 0x68) + 0x38) != 0)
            ) && ((*(int *)(*(int *)(*(int *)(*local_24 + 0x68) + 0x38) + 4) != 0 &&
                  (*(int *)(*(int *)(*(int *)(*local_24 + 0x68) + 0x38) + 0x28) != 0)))) {
          local_60 = *(int *)(*(int *)(*local_24 + 0x68) + 0x38);
          param_1[2] = param_1[2] +
                       *(int *)(*(int *)(local_60 + 0x28) + 0x1c +
                               (*(int *)(local_60 + 4) + -1) * 0x2c);
        }
      }
    }
    thunk_FUN_00429641(param_1);
    if (0 < (int)param_1[7]) {
      thunk_FUN_00429641(local_5c);
    }
    if (1 < (int)param_1[7]) {
      if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
        local_dc = &local_48;
      }
      else {
        local_dc = local_20;
      }
      thunk_FUN_00429641(local_dc);
    }
    if (2 < (int)param_1[7]) {
      if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
        local_e0 = &local_80;
      }
      else {
        local_e0 = local_10;
      }
      thunk_FUN_00429641(local_e0);
    }
    if (3 < (int)param_1[7]) {
      thunk_FUN_00429641(local_14);
    }
    if ((param_1[6] == 0x67) || (param_1[6] == 200)) {
      if ((DAT_00456b34 != 0) &&
         ((DAT_00456b34 = 0, PTR_DAT_00457fa4 != (undefined *)0x0 &&
          (PTR_DAT_00457fa4 != &DAT_00457be8)))) {
        strcpy(&DAT_00461528,PTR_DAT_00457fa4);
        uVar1 = strlen(&DAT_00461528);
        (&DAT_00461528)[uVar1] = 0x20;
        local_8 = &DAT_00461529 + uVar1;
        sprintf(local_8,s__04X__04X__04X_00457560,DAT_00461fc8,DAT_00461fcc,DAT_004612ec);
        uVar1 = strlen(local_8);
        local_8 = local_8 + uVar1;
        if (DAT_00461260 == '\0') {
          local_e4 = s_6_3_7_00457ee0;
        }
        else {
          local_e4 = &DAT_00457570;
        }
        sprintf(local_8,s__s__s_00457578,DAT_00461f48,local_e4);
        if (PTR_DAT_00457fa8 != (undefined *)0x0) {
          uVar1 = strlen(local_8);
          local_8 = local_8 + uVar1;
          uVar1 = strlen(PTR_DAT_00457fa8);
          if (0x48 < uVar1) {
            PTR_DAT_00457fa8[0x48] = 0;
          }
          sprintf(local_8,&DAT_00457580,PTR_DAT_00457fa8);
        }
        thunk_FUN_00429811((uint *)&DAT_00461528,0xffffffff);
      }
      thunk_FUN_0042944b();
    }
  }
  return;
}


/* ==== FUN_0041976c @ 0041976c ==== */

void __cdecl FUN_0041976c(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  uint local_2c;
  uint local_28;
  uint local_24;
  
  uVar5 = DAT_00461d8c;
  uVar4 = DAT_00461d88;
  uVar3 = DAT_00461d84;
  uVar2 = DAT_00461d80;
  uVar1 = *DAT_00461d94;
  if ((((DAT_00457b78 == '\0') || (DAT_00461d80 == 0x1c)) || (DAT_00461d80 == 0x11d)) ||
     ((DAT_00461f44 == 4 && (DAT_00461d80 == 0)))) {
    local_24 = DAT_00461f78;
  }
  else {
    local_24 = DAT_00461f74;
  }
  local_2c = uVar1 + param_1;
  if (DAT_00461d80 == 0) {
    if (DAT_00461f08 != (uint *)0x0) {
      if ((DAT_00461f08[1] == 0) || (uVar1 < *DAT_00461f08)) {
        *DAT_00461f08 = uVar1;
        puVar6 = DAT_00461f08;
        DAT_00461f08[2] = 0;
        puVar6[3] = uVar3;
        puVar6[4] = uVar4;
        puVar6[5] = uVar5;
      }
      if (DAT_00461f08[1] < local_2c) {
        DAT_00461f08[1] = local_2c;
      }
    }
    if ((DAT_00456b38 != 0) || (uVar1 < DAT_00461300)) {
      DAT_00457bac = uVar3;
      DAT_00456b38 = 0;
      DAT_00461300 = uVar1;
    }
    if (DAT_00461308 < local_2c) {
      local_28 = local_2c;
      if (local_24 < local_2c) {
        local_28 = local_24;
      }
      DAT_00461308 = local_28;
      DAT_00457bb4 = uVar3;
    }
  }
  else {
    if (DAT_00461f08 != (uint *)0x0) {
      if ((DAT_00461f08[7] == 0) || (uVar1 < DAT_00461f08[6])) {
        DAT_00461f08[6] = uVar1;
        puVar6 = DAT_00461f08;
        DAT_00461f08[8] = uVar2;
        puVar6[9] = uVar3;
        puVar6[10] = uVar4;
        puVar6[0xb] = uVar5;
      }
      if (DAT_00461f08[7] < local_2c) {
        DAT_00461f08[7] = local_2c;
      }
    }
    if (DAT_00461258 == '\0') {
      DAT_00457bb0 = uVar3;
      DAT_00461258 = '\x01';
      DAT_00461304 = uVar1;
    }
    else if (uVar1 < DAT_00461304) {
      DAT_00457bb0 = uVar3;
      DAT_00461304 = uVar1;
    }
    if (DAT_0046130c < local_2c) {
      if (local_24 < local_2c) {
        local_2c = local_24;
      }
      DAT_0046130c = local_2c;
      DAT_00457bb8 = uVar3;
    }
  }
  return;
}


/* ==== FUN_0041999e @ 0041999e ==== */

void __cdecl FUN_0041999e(uint param_1,int *param_2,int param_3)

{
  uint uVar1;
  int *piVar2;
  int local_18;
  int *local_14;
  int *local_c;
  
  local_14 = (int *)0x0;
  if ((param_1 & 0x1000) == 0) {
    local_c = FUN_00419ece(param_1,param_3);
  }
  else {
    local_c = *(int **)(DAT_00461ddc + 0x40);
  }
  DAT_00461de4 = local_c;
  DAT_00461de0 = local_c;
  if ((param_1 & 0x4000) != 0) {
    local_c = FUN_0041a425();
  }
  DAT_00461de4 = local_c;
  if ((((param_1 & 0x2000) != 0) &&
      (local_14 = FUN_00419ff9(param_1,param_3), (param_1 & 0x1000) != 0)) &&
     ((param_1 & 0x20000) != 0)) {
    DAT_00461de0 = local_14;
    local_c = local_14;
  }
  if ((local_c == (int *)0x0) && (local_14 == (int *)0x0)) {
    thunk_FUN_004098b0(s_Invalid_data_block_type_00457584);
  }
  uVar1 = DAT_00461de0[2];
  if ((param_1 & 0x4000) == 0) {
    DAT_00461d70 = *param_2;
    DAT_00461d84 = param_2[1];
    DAT_00461d78 = param_2[2];
    DAT_00461d7c = param_2[3];
    if ((*param_2 == param_2[1]) && (*param_2 != 0x1c)) {
      if ((*(uint *)(*DAT_00461de0 + 4) & 0x1000000) == 0) {
        if ((DAT_00461dd4 != 0) && ((*(uint *)(DAT_00461dd4 + 4) & 0x1000000) != 0)) {
          DAT_00461d84 = *(int *)(DAT_00461dd4 + 0x10);
        }
      }
      else {
        DAT_00461d84 = *(int *)(*DAT_00461de0 + 0xc);
      }
    }
    DAT_00461d90 = DAT_00461de0 + 5;
    DAT_00461d74 = DAT_00461d84;
    DAT_00461d80 = DAT_00461d70;
    DAT_00461d88 = DAT_00461d78;
    DAT_00461d8c = DAT_00461d7c;
    DAT_00461d94 = DAT_00461d90;
    if ((uVar1 & 0x1000) == 0) {
      if (DAT_00461de0[5] != param_3) {
        DAT_00461de0[4] = param_3;
        *DAT_00461d90 = param_3;
      }
    }
    else if ((uVar1 & 0x20000) == 0) {
      *DAT_00461d90 = param_3 + *(int *)(DAT_00461df0 + 4);
      if ((DAT_00461294 == 2) && (DAT_00461248 == '\0')) {
        *DAT_00461d90 = *DAT_00461d90 + DAT_00461de0[4];
      }
    }
    else if ((((uVar1 & 0x2000) == 0) &&
             (*DAT_00461d90 =
                   (param_3 + *(int *)(DAT_00461df0 + 8)) - *(int *)(*DAT_00461de0 + 0x3c),
             DAT_00461294 == 2)) && (DAT_00461248 == '\0')) {
      *DAT_00461d90 = *DAT_00461d90 + DAT_00461de0[4];
    }
    if (((DAT_00461294 == 2) && ((uVar1 & 0x1000) != 0)) &&
       (((uVar1 & 0x2000) == 0 &&
        (((*DAT_00461d94 = *DAT_00461d94 + *(int *)(*DAT_00461de0 + 0x58), DAT_00461270 != '\0' &&
          (DAT_00461de4[0xe] != 0)) && (piVar2 = (int *)DAT_00461de4[0xe], *piVar2 != 0)))))) {
      *DAT_00461d90 = *DAT_00461d90 + *(int *)(piVar2[10] + 0x1c + (*piVar2 + -1) * 0x2c);
    }
  }
  else {
    DAT_00461d80 = *param_2;
    DAT_00461d84 = param_2[1];
    DAT_00461d88 = param_2[2];
    DAT_00461d8c = param_2[3];
    DAT_00461d70 = DAT_0046c2e0;
    DAT_00461d74 = DAT_0046c2e4;
    DAT_00461d78 = DAT_0046c2e8;
    DAT_00461d7c = DAT_0046c2ec;
    if (DAT_00461f44 == 5) {
      if (DAT_0046c2e0 == 0) {
        if ((DAT_00461d80 == 1) || (DAT_00461d80 == 2)) {
          DAT_00461d8c = 0x42;
        }
        if (DAT_00461d84 == 0x1e) {
          DAT_00461d8c = 0x62;
        }
      }
      if (((DAT_0046c2e0 == 1) || (DAT_0046c2e0 == 2)) && (DAT_00461d84 == 0x1e)) {
        DAT_00461d8c = 0x21;
      }
    }
    if ((*param_2 == param_2[1]) && (*param_2 != 0x1c)) {
      if ((*(uint *)(*DAT_00461de0 + 4) & 0x1000000) == 0) {
        if ((DAT_00461dd4 != 0) && ((*(uint *)(DAT_00461dd4 + 4) & 0x1000000) != 0)) {
          DAT_00461d84 = *(int *)(DAT_00461dd4 + 0x10);
        }
      }
      else {
        DAT_00461d84 = *(int *)(*DAT_00461de0 + 0xc);
      }
    }
    DAT_00461d90 = local_c + 5;
    DAT_00461d94 = DAT_00461de0 + 5;
    if ((uVar1 & 0x1000) == 0) {
      if (DAT_00461de0[5] != param_3) {
        DAT_00461de0[4] = param_3;
        *DAT_00461d94 = param_3;
      }
    }
    else {
      if (DAT_00457b98 == '\0') {
        local_18 = *(int *)(DAT_00461df0 + 8);
      }
      else {
        local_18 = *(int *)(DAT_00461df0 + 4);
      }
      *DAT_00461d94 = param_3 + local_18;
      if (((DAT_00461294 == 2) && (DAT_00461248 == '\0')) &&
         (*DAT_00461d94 = *DAT_00461d94 + DAT_00461de0[4], (uVar1 & 0x2000) == 0)) {
        *DAT_00461d94 = *DAT_00461d94 + *(int *)(*DAT_00461de0 + 0x58);
      }
    }
  }
  return;
}


/* ==== FUN_00419ece @ 00419ece ==== */

int * __cdecl FUN_00419ece(uint param_1,int param_2)

{
  bool bVar1;
  int *local_c;
  int *local_8;
  
  bVar1 = false;
  local_8 = *(int **)(*DAT_00461ddc + 0x1c);
  local_c = (int *)0x0;
  do {
    if (local_8 == (int *)0x0) {
LAB_00419f36:
      if (!bVar1) {
        if (DAT_00461294 == 2) {
          thunk_FUN_004098b0(s_Cannot_find_section_record_0045759c);
        }
        local_8 = thunk_FUN_0042be92(*DAT_00461ddc,0);
        local_8[1] = 0;
        local_8[2] = param_1 & 0xfffd9fff;
        local_8[0x10] = (int)DAT_00461ddc;
        if (local_c == (int *)0x0) {
          local_8[0x11] = *(int *)(*local_8 + 0x1c);
          *(int **)(*local_8 + 0x1c) = local_8;
        }
        else {
          local_8[0x11] = local_c[0x11];
          local_c[0x11] = (int)local_8;
        }
        *(int *)(*local_8 + 0x2c) = *(int *)(*local_8 + 0x2c) + 1;
        DAT_0046129c = DAT_0046129c + 1;
      }
      local_8[3] = local_8[3] | 0x1000;
      return local_8;
    }
    if (((local_8[3] & 0x1000U) == 0) || (local_8[5] == param_2)) {
      bVar1 = true;
      goto LAB_00419f36;
    }
    local_c = local_8;
    local_8 = (int *)local_8[0x11];
  } while( true );
}


/* ==== FUN_00419ff9 @ 00419ff9 ==== */

int * __cdecl FUN_00419ff9(uint param_1,int param_2)

{
  bool bVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  uint local_14;
  int *local_10;
  int *local_c;
  
  bVar1 = false;
  if (DAT_00457b88 == '\0') {
    param_1 = param_1 & 0xffffefff;
  }
  else {
    param_1 = param_1 | 0x1000;
  }
  if (*(int *)(DAT_00461e5c + DAT_004612ac * 8) == 0) {
    local_c = *(int **)(*DAT_00461de0 + 0x20);
    local_10 = (int *)0x0;
    for (; local_c != (int *)0x0; local_c = (int *)local_c[0x11]) {
      if (((param_1 & 0x27000) == (local_c[2] & 0x27000U)) &&
         (((local_c[3] & 0x1000U) == 0 || (((local_c[2] & 0x1000U) == 0 && (local_c[5] == param_2)))
          ))) {
        bVar1 = true;
        break;
      }
      local_10 = local_c;
    }
    if (!bVar1) {
      if (DAT_00461294 == 2) {
        thunk_FUN_004098b0(s_Cannot_find_section_record_004575b8);
      }
      if ((param_1 & 0x4000) == 0) {
        iVar4 = *DAT_00461de0;
      }
      else {
        iVar4 = **(int **)(DAT_00461e60 + 4 + DAT_004612c8 * 0x24);
      }
      local_c = thunk_FUN_0042be92(iVar4,0x2000);
      local_c[1] = DAT_004612b4;
      local_c[2] = param_1;
      local_c[4] = 0;
      local_c[9] = DAT_004612c0;
      local_c[5] = DAT_004612c0;
      local_c[0xc] = param_2;
      local_c[0xd] = DAT_004612bc + DAT_004612c0;
      local_c[0x10] = (int)DAT_00461de0;
      if (local_10 == (int *)0x0) {
        local_c[0x11] = *(int *)(*local_c + 0x20);
        *(int **)(*local_c + 0x20) = local_c;
      }
      else {
        local_c[0x11] = local_10[0x11];
        local_10[0x11] = (int)local_c;
      }
      *(int *)(*local_c + 0x30) = *(int *)(*local_c + 0x30) + 1;
      DAT_0046129c = DAT_0046129c + 1;
    }
    DAT_004612bc = 0;
    local_c[3] = local_c[3] | DAT_004612b8 | 0x1000;
    *(int **)(DAT_00461e5c + DAT_004612ac * 8) = local_c;
    *(int *)(DAT_00461e5c + 4 + DAT_004612ac * 8) = param_2;
    if ((DAT_00457b88 != '\0') && (DAT_00461294 == 1)) {
      if (*(int *)(*local_c + 0xc) == 0x1e) {
        local_14 = DAT_00461f78;
      }
      else {
        local_14 = DAT_00461f74;
      }
      uVar3 = thunk_FUN_00430ac9(*(uint *)(DAT_00461df0 + 4),DAT_004612c0,local_14);
      *(uint *)(DAT_00461df0 + 4) = uVar3;
      *(int *)(*DAT_00461de0 + 0x3c) =
           *(int *)(*DAT_00461de0 + 0x38) +
           (*(int *)(DAT_00461df0 + 4) - *(int *)(DAT_00461df0 + 8));
      if ((uint)DAT_00461de0[9] < DAT_004612c0) {
        DAT_00461de0[9] = DAT_004612c0;
      }
    }
  }
  else {
    local_c = *(int **)(DAT_00461e5c + DAT_004612ac * 8);
    if (DAT_00461204 != '\0') {
      piVar2 = local_c + 4;
      if (((param_1 & 0x1000) == 0) || ((param_1 & 0x20000) == 0)) {
        if ((param_1 & 0x4000) == 0) {
          *piVar2 = param_2;
          if (DAT_00457b88 != '\0') {
            *piVar2 = *piVar2 + DAT_00461de0[4] + *(int *)(DAT_00461df0 + 4);
          }
        }
        else {
          *piVar2 = *(int *)(*(int *)(DAT_00461e60 + 4 + DAT_004612c8 * 0x24) + 0x14);
        }
        local_c[5] = *piVar2 + DAT_004612c0;
      }
    }
    DAT_004612bc = 0;
    if (((DAT_00457b88 != '\0') && (DAT_00461294 == 2)) && ((DAT_00461de0[2] & 0x20000U) == 0)) {
      if (*(int *)(*local_c + 0xc) == 0x1e) {
        local_14 = DAT_00461f78;
      }
      else {
        local_14 = DAT_00461f74;
      }
      uVar3 = thunk_FUN_00430ac9(*(uint *)(DAT_00461df0 + 0xc),DAT_004612c0,local_14);
      *(uint *)(DAT_00461df0 + 0xc) = uVar3;
    }
    if (((param_1 & 0x1000) == 0) || ((param_1 & 0x20000) == 0)) {
      local_c = DAT_00461de0;
    }
  }
  return local_c;
}


/* ==== FUN_0041a425 @ 0041a425 ==== */

undefined4 * FUN_0041a425(void)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  int local_18;
  
  if ((DAT_004612d4 == 0) && (*(int *)(DAT_00461e60 + 4 + DAT_004612c8 * 0x24) == 0)) {
    piVar2 = thunk_FUN_0042bc50((uint *)**(undefined4 **)*DAT_00461de0,
                                (*(undefined4 **)*DAT_00461de0)[1],&DAT_0046c2e0,0);
    iVar1 = *piVar2;
    puVar3 = thunk_FUN_0042be92(iVar1,0x4000);
    puVar3[1] = DAT_004612cc;
    puVar3[2] = (uint)((byte)(-(uint)(DAT_00457b88 != '\0') >> 8) & 0x10 | 0x40) << 8;
    puVar3[0xf] = DAT_00461e60 + DAT_004612c8 * 0x24;
    puVar3[0x10] = DAT_00461de0;
    puVar3[0x11] = *(undefined4 *)(iVar1 + 0x24);
    *(undefined4 **)(iVar1 + 0x24) = puVar3;
    *(int *)(iVar1 + 0x34) = *(int *)(iVar1 + 0x34) + 1;
    DAT_0046129c = DAT_0046129c + 1;
    if (*(int *)(DAT_00461dbc + 8) != *(int *)(iVar1 + 0x6c)) {
      *(undefined4 *)(iVar1 + 0x6c) = *(undefined4 *)(DAT_00461dbc + 8);
      puVar3[2] = puVar3[2] | 0x10000;
    }
    if (DAT_00457b88 != '\0') {
      *(undefined4 **)(*DAT_00461de0 + 0x68) = puVar3;
    }
    *(undefined4 **)(DAT_00461e60 + 0x10 + DAT_004612c8 * 0x24) = puVar3;
    *(undefined4 **)(DAT_00461e60 + 4 + DAT_004612c8 * 0x24) = puVar3;
  }
  else {
    if (DAT_004612d4 == 0) {
      local_18 = DAT_004612c8;
    }
    else {
      local_18 = DAT_004612d4;
    }
    puVar3 = *(undefined4 **)(DAT_00461e60 + 4 + local_18 * 0x24);
    DAT_00457b88 = (puVar3[2] & 0x1000) != 0;
    DAT_004612d4 = 0;
  }
  return puVar3;
}


/* ==== FUN_0041a5e0 @ 0041a5e0 ==== */

void __cdecl FUN_0041a5e0(int param_1)

{
  int iVar1;
  undefined4 local_8;
  
  iVar1 = thunk_FUN_0042e170(*(int *)(param_1 + 0x48) << 2);
  *(int *)(param_1 + 0x10) = iVar1;
  DAT_00461de8 = *(int *)(param_1 + 0x10);
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x48); local_8 = local_8 + 1) {
    *(undefined4 *)(DAT_00461de8 + local_8 * 4) = 0;
  }
  iVar1 = thunk_FUN_0042e170(*(int *)(param_1 + 0x4c) << 3);
  *(int *)(param_1 + 0x14) = iVar1;
  DAT_00461e64 = *(int *)(param_1 + 0x14);
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x4c); local_8 = local_8 + 1) {
    *(undefined4 *)(DAT_00461e64 + local_8 * 8) = 0;
    *(undefined4 *)(DAT_00461e64 + 4 + local_8 * 8) = 0;
  }
  iVar1 = thunk_FUN_0042e170(*(int *)(param_1 + 0x58) * 8 + 8);
  *(int *)(param_1 + 0x18) = iVar1;
  DAT_00461e5c = *(int *)(param_1 + 0x18);
  for (local_8 = 0; local_8 <= *(int *)(param_1 + 0x58); local_8 = local_8 + 1) {
    *(undefined4 *)(DAT_00461e5c + local_8 * 8) = 0;
    *(undefined4 *)(DAT_00461e5c + 4 + local_8 * 8) = 0;
  }
  DAT_004612ac = 0;
  iVar1 = thunk_FUN_0042e170((*(int *)(param_1 + 0x5c) + 1) * 0x24);
  *(int *)(param_1 + 0x1c) = iVar1;
  DAT_00461e60 = *(int *)(param_1 + 0x1c);
  for (local_8 = 0; local_8 <= *(int *)(param_1 + 0x5c); local_8 = local_8 + 1) {
    *(undefined4 *)(DAT_00461e60 + local_8 * 0x24) = 0;
    *(undefined4 *)(DAT_00461e60 + 0x10 + local_8 * 0x24) = 0;
    *(undefined4 *)(DAT_00461e60 + 0xc + local_8 * 0x24) = 0;
    *(undefined4 *)(DAT_00461e60 + 8 + local_8 * 0x24) = 0;
    *(undefined4 *)(DAT_00461e60 + 4 + local_8 * 0x24) = 0;
    *(undefined4 *)(DAT_00461e60 + 0x14 + local_8 * 0x24) = 0;
    *(undefined4 *)(DAT_00461e60 + 0x18 + local_8 * 0x24) = 0;
    *(undefined4 *)(DAT_00461e60 + 0x1c + local_8 * 0x24) = 0;
    *(undefined4 *)(DAT_00461e60 + 0x20 + local_8 * 0x24) = 0;
  }
  DAT_004612c8 = 0;
  return;
}


/* ==== FUN_0041a815 @ 0041a815 ==== */

int __cdecl FUN_0041a815(uint *param_1)

{
  int extraout_EAX;
  int extraout_EAX_00;
  int local_20c;
  undefined4 *local_208;
  char local_204 [512];
  
  fopen((char *)param_1,&DAT_004575d4);
  local_20c = extraout_EAX;
  if (extraout_EAX == 0) {
    for (local_208 = DAT_00461f10; local_208 != (undefined4 *)0x0;
        local_208 = (undefined4 *)local_208[1]) {
      strcpy(local_204,(char *)*local_208);
      strcat(local_204,(char *)param_1);
      fopen(local_204,&DAT_004575d8);
      if (extraout_EAX_00 != 0) {
        return extraout_EAX_00;
      }
      local_20c = 0;
    }
  }
  return local_20c;
}


/* ==== FUN_0041a8c0 @ 0041a8c0 ==== */

undefined4 __cdecl FUN_0041a8c0(int param_1)

{
  int iVar1;
  undefined1 *buf;
  undefined1 local_28 [20];
  undefined4 local_14;
  
  buf = local_28;
  iVar1 = _fileno((void *)param_1);
  iVar1 = _fstat(iVar1,buf);
  if (iVar1 < 0) {
    local_14 = 0xffffffff;
  }
  return local_14;
}


/* ==== FUN_0041a8ef @ 0041a8ef ==== */

char * __cdecl FUN_0041a8ef(uint param_1)

{
  char *pcVar1;
  uint uVar2;
  
  pcVar1 = (char *)thunk_FUN_0042e170(param_1 * 0x34);
  uVar2 = thunk_FUN_00430667(pcVar1,0x34,param_1,DAT_00461db4);
  if (uVar2 != param_1) {
    thunk_FUN_004098b0(s_Cannot_read_object_module_sectio_004575dc);
  }
  return pcVar1;
}


/* ==== FUN_0041a937 @ 0041a937 ==== */

char * __cdecl FUN_0041a937(uint param_1)

{
  char *pcVar1;
  uint uVar2;
  
  pcVar1 = (char *)thunk_FUN_0042e170(param_1 << 5);
  uVar2 = thunk_FUN_00430667(pcVar1,0x20,param_1,DAT_00461db4);
  if (uVar2 != param_1) {
    thunk_FUN_004098b0(s_Cannot_read_object_module_symbol_00457608);
  }
  return pcVar1;
}


/* ==== FUN_0041a97f @ 0041a97f ==== */

uint * FUN_0041a97f(void)

{
  uint uVar1;
  uint *puVar2;
  uint local_8;
  
  local_8 = 0;
  uVar1 = thunk_FUN_0043062d((char *)&local_8,4,1,DAT_00461db4);
  if (uVar1 != 1) {
    if (((DAT_00461db4[3] & 0x10U) != 0) || (local_8 == 0)) {
      return (uint *)0x0;
    }
    thunk_FUN_004098b0(s_Cannot_read_module_string_table_s_00457634);
  }
  puVar2 = (uint *)thunk_FUN_0042e170(local_8);
  uVar1 = thunk_FUN_0043055b((char *)(puVar2 + 1),1,local_8 - 4,DAT_00461db4);
  if (uVar1 != local_8 - 4) {
    thunk_FUN_004098b0(s_Cannot_read_object_module_string_0045765c);
  }
  *puVar2 = local_8;
  return puVar2;
}


