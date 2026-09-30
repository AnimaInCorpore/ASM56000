/* lib: 12 functions from DSPLNK */

/* ==== FUN_0041c470 @ 0041c470 ==== */

void FUN_0041c470(void)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = DAT_004611bc;
  while( true ) {
    if (piVar2 == (int *)0x0) {
      return;
    }
    piVar1 = (int *)piVar2[1];
    if (*piVar2 == 0) break;
    thunk_FUN_0042e1ce((undefined *)*piVar2);
    thunk_FUN_0042e1ce((undefined *)piVar2);
    piVar2 = piVar1;
  }
  thunk_FUN_0042e1ce((undefined *)piVar2);
  return;
}


/* ==== FUN_0041c4cf @ 0041c4cf ==== */

undefined4 FUN_0041c4cf(void)

{
  char *src;
  int local_14;
  uint local_10;
  char *local_c;
  char *local_8;
  
  if ((DAT_004611f4 == '\0') && (DAT_00461528 == '-')) {
    if (__mb_cur_max < 2) {
      local_10 = *(ushort *)(_pctype + DAT_00461529 * 2) & 1;
    }
    else {
      local_10 = _isctype((int)DAT_00461529,1);
    }
    if (local_10 == 0) {
      local_14 = (int)DAT_00461529;
    }
    else {
      local_14 = tolower((int)DAT_00461529);
    }
    if (local_14 == 0x6c) {
      if (DAT_0046152a == '\0') {
        src = (char *)*DAT_00461da4;
        DAT_00461da4 = DAT_00461da4 + 1;
        strcpy(&DAT_00461528,src);
        DAT_00461da0 = DAT_00461da0 + -1;
      }
      else {
        local_8 = &DAT_00461528;
        for (local_c = &DAT_0046152a; *local_c != '\0'; local_c = local_c + 1) {
          *local_8 = *local_c;
          local_8 = local_8 + 1;
        }
        *local_8 = '\0';
      }
      return 1;
    }
  }
  return 0;
}


/* ==== FUN_0041c5ec @ 0041c5ec ==== */

void FUN_0041c5ec(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 in_stack_00000004;
  uint local_c;
  
  local_c = 0;
  uVar1 = strlen(&DAT_00457f98);
  for (; (int)local_c < (int)uVar1; local_c = local_c + 1) {
    DAT_00461db4[1] = DAT_00461db4[1] + -1;
    if (DAT_00461db4[1] < 0) {
      uVar3 = _filbuf(DAT_00461db4);
    }
    else {
      uVar3 = (uint)*(byte *)*DAT_00461db4;
      *DAT_00461db4 = *DAT_00461db4 + 1;
    }
    if ((uVar3 != (int)(char)(&DAT_00457f98)[local_c]) || (uVar3 == 0xffffffff)) break;
  }
  if (local_c != uVar1) {
    thunk_FUN_0040a0f6(s_Invalid_library_file_00457904,in_stack_00000004);
  }
  iVar2 = fseek(DAT_00461db4,0,0);
  if (iVar2 != 0) {
    thunk_FUN_0040a0ca(s_Seek_failure_0045791c);
  }
  return;
}


/* ==== FUN_0041c6d7 @ 0041c6d7 ==== */

void FUN_0041c6d7(void)

{
  int iVar1;
  int local_c;
  int local_8;
  
  if (DAT_00461294 == 1) {
    FUN_0041c7a2();
    DAT_00461ddc = &DAT_0046c240;
    local_8 = DAT_004612e0 - DAT_004612e4;
    while ((local_8 != 0 && (DAT_004611fc != '\0'))) {
      DAT_004611fc = '\0';
      iVar1 = fseek(DAT_00461db4,0,0);
      if (iVar1 != 0) {
        thunk_FUN_004098b0(s_Seek_failure_0045792c);
      }
      FUN_0041c7d9();
      local_8 = DAT_004612e0 - DAT_004612e4;
    }
    DAT_004611fc = local_8 != 0;
  }
  else {
    for (local_c = *(int *)(DAT_00461dbc + 0xc); local_c != 0; local_c = *(int *)(local_c + 0x94)) {
      *(int *)(DAT_00461dbc + 8) = local_c;
      thunk_FUN_004146c6(local_c);
    }
  }
  return;
}


/* ==== FUN_0041c7a2 @ 0041c7a2 ==== */

void FUN_0041c7a2(void)

{
  DAT_004611b8 = (undefined4 *)thunk_FUN_0042e170(8);
  DAT_004611bc = DAT_004611b8;
  *DAT_004611b8 = 0;
  DAT_004611b8[1] = 0;
  return;
}


/* ==== FUN_0041c7d9 @ 0041c7d9 ==== */

void FUN_0041c7d9(void)

{
  int iVar1;
  uint uVar2;
  char local_464 [512];
  uint local_264 [128];
  uint local_64;
  long local_60;
  undefined *local_5c [3];
  int local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  char local_40 [36];
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  long local_8;
  
  while ((DAT_004612e0 != 0 && (iVar1 = FUN_0041d288(DAT_00461db4,local_464), iVar1 != 0))) {
    sscanf(local_464,s___s__s__ld_0045793c,local_264,&local_8);
    local_60 = ftell(DAT_00461db4);
    if (local_60 < 0) {
      thunk_FUN_004098b0(s_Offset_failure_00457948);
    }
    uVar2 = thunk_FUN_0043062d((char *)local_5c,0x1c,1,DAT_00461db4);
    if (uVar2 != 1) {
      thunk_FUN_004098b0(s_Cannot_read_file_header_from_lib_00457958);
    }
    if ((DAT_00461fc0 == 0) ||
       (((local_5c[0] == (undefined *)0x2c8 || (local_5c[0] == (undefined *)0x2ca)) &&
        (DAT_00461fa0 == (undefined *)0x2c5)))) {
      thunk_FUN_004045d0(local_5c[0]);
    }
    if (((local_5c[0] == DAT_00461fa0) ||
        (((DAT_00461fa0 == (undefined *)0x2c8 || (DAT_00461fa0 == (undefined *)0x2ca)) &&
         (local_5c[0] == (undefined *)0x2c5)))) && ((local_44 & 1) == 0)) {
      uVar2 = thunk_FUN_0043062d(local_40,local_48,1,DAT_00461db4);
      if (uVar2 != 1) {
        thunk_FUN_004098b0(s_Cannot_read_optional_header_from_00457994);
      }
      if (local_48 == 0x28) {
        DAT_00461fe8 = 4;
        DAT_00461ff0 = 0;
        DAT_00461fec = 0;
      }
      else {
        DAT_00461fe8 = local_1c;
        DAT_00461fec = local_18;
        DAT_00461ff0 = local_14;
      }
      local_64 = local_4c;
      if (local_4c == 0) {
        iVar1 = fseek(DAT_00461db4,local_60,0);
        if ((iVar1 != 0) || (iVar1 = fseek(DAT_00461db4,local_8,1), iVar1 != 0)) {
          thunk_FUN_004098b0(s_Seek_failure_004579f0);
        }
      }
      else {
        iVar1 = fseek(DAT_00461db4,local_50 + local_60,0);
        if (iVar1 != 0) {
          thunk_FUN_004098b0(s_Cannot_seek_to_library_module_sy_004579c4);
        }
        DAT_00461e6c = thunk_FUN_0041a937(local_64);
        DAT_00461e70 = local_64;
        DAT_00461e74 = 0;
        DAT_00461e78 = thunk_FUN_0041a97f();
        FUN_0041ca95(local_264,local_60,local_8);
        iVar1 = fseek(DAT_00461db4,local_60,0);
        if ((iVar1 != 0) || (iVar1 = fseek(DAT_00461db4,local_8,1), iVar1 != 0)) {
          thunk_FUN_004098b0(s_Seek_failure_00457a00);
        }
      }
    }
    else {
      iVar1 = fseek(DAT_00461db4,local_60,0);
      if ((iVar1 != 0) || (iVar1 = fseek(DAT_00461db4,local_8,1), iVar1 != 0)) {
        thunk_FUN_004098b0(s_Seek_failure_00457984);
      }
    }
  }
  return;
}


/* ==== FUN_0041ca95 @ 0041ca95 ==== */

undefined4 __cdecl FUN_0041ca95(uint *param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  char local_80 [100];
  undefined4 local_1c;
  int *local_18;
  undefined4 *local_14;
  undefined4 local_10;
  undefined4 *local_c;
  undefined4 local_8;
  
  local_8 = 0;
  local_10 = DAT_00461e70;
  local_1c = DAT_00461e74;
  DAT_00461148 = 0;
  while (local_c = (undefined4 *)FUN_0041ce63(), local_c != (undefined4 *)0x0) {
    if ((DAT_004611e8 == 1) && ((local_c[10] & 0x40) != 0)) {
      iVar1 = FUN_0041ce1b((char *)*local_c);
      if (iVar1 == 1) {
        sprintf(local_80,s_Found_duplicate_global_symbol____00457a10,*local_c,param_1);
        thunk_FUN_00409d88(local_80);
      }
      else {
        FUN_0041cd73((uint *)*local_c);
      }
    }
  }
  DAT_00461148 = 1;
  DAT_00461e70 = local_10;
  DAT_00461e74 = local_1c;
  local_c = (undefined4 *)0x0;
  while (local_c = (undefined4 *)FUN_0041ce63(), local_c != (undefined4 *)0x0) {
    local_14 = thunk_FUN_0042cd0d((uint *)*local_c);
    if ((local_14 != (undefined4 *)0x0) && ((local_14[1] & 0x100) == 0)) {
      if (local_14[4] == 0) {
        if (**(char **)**(undefined4 **)local_c[0x12] == s_GLOBAL_00457f88[0]) {
          iVar1 = strcmp(*(char **)**(undefined4 **)local_c[0x12],s_GLOBAL_00457f88);
          goto joined_r0x0041cc10;
        }
      }
      else if (**(char **)**(undefined4 **)local_c[0x12] == **(char **)**(undefined4 **)local_14[4])
      {
        iVar1 = strcmp(*(char **)**(undefined4 **)local_c[0x12],
                       *(char **)**(undefined4 **)local_14[4]);
joined_r0x0041cc10:
        if (iVar1 == 0) break;
      }
      if ((((local_c[10] & 0x80) != 0) && ((local_14[1] & 0x80) != 0)) ||
         ((local_c[10] & 0x40) != 0)) break;
    }
  }
  thunk_FUN_0042e1ce(DAT_00461e6c);
  DAT_00461e6c = (undefined *)0x0;
  if (DAT_00461e78 != (undefined *)0x0) {
    thunk_FUN_0042e1ce(DAT_00461e78);
  }
  DAT_00461e78 = (undefined *)0x0;
  DAT_00461e74 = 0;
  DAT_00461e70 = 0;
  if (local_c == (undefined4 *)0x0) {
    iVar1 = fseek(DAT_00461db4,param_2,0);
    if ((iVar1 != 0) || (iVar1 = fseek(DAT_00461db4,param_3,1), iVar1 != 0)) {
      thunk_FUN_004098b0(s_Seek_failure_00457a48);
    }
    uVar2 = 0;
  }
  else {
    iVar1 = fseek(DAT_00461db4,param_2,0);
    if (iVar1 != 0) {
      thunk_FUN_004098b0(s_Seek_failure_00457a58);
    }
    local_18 = thunk_FUN_004145bb(param_1,param_3,param_2);
    if (*(int *)(DAT_00461dbc + 0xc) == 0) {
      *(int **)(DAT_00461dbc + 8) = local_18;
      *(int **)(DAT_00461dbc + 0xc) = local_18;
    }
    else {
      *(int **)(*(int *)(DAT_00461dbc + 8) + 0x94) = local_18;
      *(int **)(DAT_00461dbc + 8) = local_18;
    }
    uVar2 = thunk_FUN_004146c6((int)local_18);
  }
  return uVar2;
}


/* ==== FUN_0041cd73 @ 0041cd73 ==== */

void __cdecl FUN_0041cd73(uint *param_1)

{
  uint uVar1;
  int iVar2;
  
  if (*DAT_004611b8 == 0) {
    uVar1 = strlen((char *)param_1);
    iVar2 = thunk_FUN_0042e170(uVar1 + 1);
    *DAT_004611b8 = iVar2;
    strcpy((char *)*DAT_004611b8,(char *)param_1);
  }
  else {
    iVar2 = thunk_FUN_0042e170(8);
    DAT_004611b8[1] = iVar2;
    DAT_004611b8 = (int *)DAT_004611b8[1];
    uVar1 = strlen((char *)param_1);
    iVar2 = thunk_FUN_0042e170(uVar1 + 1);
    *DAT_004611b8 = iVar2;
    strcpy((char *)*DAT_004611b8,(char *)param_1);
    DAT_004611b8[1] = 0;
  }
  return;
}


/* ==== FUN_0041ce1b @ 0041ce1b ==== */

undefined4 __cdecl FUN_0041ce1b(char *param_1)

{
  int iVar1;
  int *local_8;
  
  local_8 = DAT_004611bc;
  while( true ) {
    if (*local_8 == 0) {
      return 0;
    }
    iVar1 = strcmp((char *)*local_8,param_1);
    if (iVar1 == 0) break;
    local_8 = (int *)local_8[1];
    if (local_8 == (int *)0x0) {
      return 0;
    }
  }
  return 1;
}


/* ==== FUN_0041ce63 @ 0041ce63 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_0041ce63(void)

{
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  int *local_28;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int *local_c;
  int *local_8;
  
  memset(&DAT_00461150,0,0x68);
  do {
    if (DAT_00461e70 <= DAT_00461e74) {
      return (undefined *)0x0;
    }
    local_8 = (int *)(DAT_00461e6c + DAT_00461e74 * 0x20);
    if (*local_8 == 0) {
      local_28 = (int *)(DAT_00461e78 + local_8[1]);
    }
    else {
      if (DAT_00461148 == 0) {
        thunk_FUN_004307d5((undefined1 *)local_8,4,2);
      }
      local_28 = local_8;
    }
    if ((local_8[6] == 3) && (local_8[5] == 0)) {
      if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
        local_c = local_8 + 0x10;
        local_10 = *local_c;
        local_1c = 4;
        local_20 = 4;
        local_18 = 0;
        local_14 = 0;
        local_20 = thunk_FUN_0042f1ca(local_8[0x12] & 0xf);
        local_1c = local_20;
      }
      else {
        local_10 = local_8[0x10];
        local_20 = local_8[0x13];
        local_1c = local_8[0x14];
        local_18 = local_8[0x15];
        local_14 = local_8[0x16];
      }
      FUN_0041d20a(local_28,local_10,&local_20);
      DAT_00461d80 = local_20;
      DAT_00461d84 = local_1c;
      DAT_00461d88 = local_18;
      DAT_00461d8c = local_14;
      DAT_00461d70 = local_20;
      DAT_00461d74 = local_1c;
      DAT_00461d78 = local_18;
      DAT_00461d7c = local_14;
    }
    else if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
      if (((((local_8[6] == 2) || ((local_8[6] == 3 && (DAT_004612e8 == 0)))) ||
           (local_8[6] == 0x6a)) ||
          ((((local_8[6] == 6 || (local_8[6] == 0xd2)) || (local_8[6] == 0xd3)) ||
           (local_8[6] == 0xd5)))) && (local_8[4] != 0)) {
        if (local_8[6] == 2) {
          local_34 = 0x40;
        }
        else {
          if (local_8[6] == 0xd2) {
            local_38 = 0x40;
          }
          else {
            if (local_8[6] == 0xd3) {
              local_3c = 0x80;
            }
            else {
              local_3c = (local_8[6] != 0x6a) - 1 & 0x80;
            }
            local_38 = local_3c;
          }
          local_34 = local_38;
        }
        _DAT_00461198 = &DAT_0046c240;
        _DAT_00461150 = local_28;
        DAT_00461178 = DAT_00461178 | local_34;
        DAT_00461e74 = DAT_00461e74 + 1 + local_8[7];
        return &DAT_00461150;
      }
    }
    else if (((local_8[6] == 2) ||
             ((((local_8[6] == 3 && (DAT_004612e8 == 0)) || (local_8[6] == 0xd2)) ||
              ((local_8[6] == 0xd3 || (local_8[6] == 0xd5)))))) && (local_8[4] != 0)) {
      if (local_8[6] == 2) {
        local_2c = 0x40;
      }
      else {
        if (local_8[6] == 0xd2) {
          local_30 = 0x40;
        }
        else {
          local_30 = (local_8[6] != 0xd3) - 1 & 0x80;
        }
        local_2c = local_30;
      }
      _DAT_00461198 = &DAT_0046c240;
      _DAT_00461150 = local_28;
      DAT_00461178 = DAT_00461178 | local_2c;
      DAT_00461e74 = DAT_00461e74 + 1 + local_8[7];
      return &DAT_00461150;
    }
    DAT_00461e74 = DAT_00461e74 + 1 + local_8[7];
  } while( true );
}


/* ==== FUN_0041d20a @ 0041d20a ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __cdecl FUN_0041d20a(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  if (DAT_00461294 != 2) {
    _DAT_0046c1a0 = param_1;
    _DAT_0046c1a4 = param_2;
    _DAT_0046c1a8 = &DAT_0046c1c0;
    _DAT_0046c1c0 = &DAT_0046c1a0;
    _DAT_0046c1c8 = *param_3;
    _DAT_0046c1cc = param_3[1];
    _DAT_0046c1d0 = param_3[2];
    _DAT_0046c1d4 = param_3[3];
    _DAT_0046c1d8 = &DAT_0046c240;
    _DAT_0046c1e8 = 1;
    _DAT_0046c240 = &DAT_0046c1c0;
  }
  return DAT_00461294 != 2;
}


/* ==== FUN_0041d288 @ 0041d288 ==== */

undefined4 __cdecl FUN_0041d288(int *param_1,char *param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint c;
  uint local_10;
  char local_c;
  char *local_8;
  
  clearerr(param_1);
  local_8 = param_2;
  while( true ) {
    param_1[1] = param_1[1] + -1;
    if (param_1[1] < 0) {
      local_10 = _filbuf(param_1);
    }
    else {
      local_10 = (uint)*(byte *)*param_1;
      *param_1 = *param_1 + 1;
    }
    if (((local_10 == 0xffffffff) || (local_10 == 0xd)) || (local_10 == 10)) break;
    local_c = (char)local_10;
    *local_8 = local_c;
    local_8 = local_8 + 1;
  }
  *local_8 = '\0';
  if ((param_1[3] & 0x10U) == 0) {
    if ((param_1[3] & 0x20U) != 0) {
      thunk_FUN_004098b0(s_Invalid_library_module_header_00457a68);
    }
    if (local_10 == 0xd) {
      param_1[1] = param_1[1] + -1;
      if (param_1[1] < 0) {
        c = _filbuf(param_1);
      }
      else {
        c = (uint)*(byte *)*param_1;
        *param_1 = *param_1 + 1;
      }
      if ((c != 0xffffffff) && (c != 10)) {
        ungetc(c,param_1);
      }
    }
    iVar2 = strncmp(param_2,&DAT_00457f98,DAT_00457fa0);
    if (iVar2 != 0) {
      thunk_FUN_004098b0(s_Invalid_library_module_header_fo_00457a88);
    }
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


