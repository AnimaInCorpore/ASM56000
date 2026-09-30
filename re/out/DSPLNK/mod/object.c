/* object: 16 functions from DSPLNK */

/* ==== FUN_00426437 @ 00426437 ==== */

undefined4 * __cdecl FUN_00426437(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)thunk_FUN_0042bed4((uint *)s_RESERVE_00457f90,param_1);
  if (local_8 != (undefined4 *)0x0) {
    while ((local_8 != (undefined4 *)0x0 && (*(int *)(*(int *)*local_8 + 4) == -1))) {
      if ((local_8[3] & 0x1000) == 0) {
        local_8[3] = local_8[3] | 0x1200;
        local_8[4] = param_2;
        local_8[5] = param_3;
        return local_8;
      }
      local_8 = (undefined4 *)local_8[0x11];
    }
  }
  piVar1 = thunk_FUN_0042bfcb((uint *)s_RESERVE_00457f90,-1);
  piVar1 = thunk_FUN_0042c1ef((int)piVar1,param_1);
  puVar2 = thunk_FUN_0042be92(piVar1,0x1000);
  puVar2[1] = 0;
  puVar2[2] = 0x1000;
  puVar2[3] = puVar2[3] | 0x1200;
  puVar2[4] = param_2;
  puVar2[5] = param_3;
  puVar2[0x11] = piVar1[6];
  piVar1[6] = (int)puVar2;
  piVar1[10] = piVar1[10] + 1;
  DAT_0046129c = DAT_0046129c + 1;
  return puVar2;
}


/* ==== FUN_00426558 @ 00426558 ==== */

undefined4 FUN_00426558(void)

{
  return 1;
}


/* ==== FUN_00426562 @ 00426562 ==== */

uint __cdecl FUN_00426562(int param_1)

{
  uint uVar1;
  undefined1 *puVar2;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_20;
  uint local_18;
  uint local_c;
  char *local_8;
  
  if (param_1 == 4) {
    uVar1 = strlen(&DAT_00461320);
    puVar2 = &DAT_00461320 + uVar1;
    if (DAT_00469388 == '\0') {
      DAT_00461db4[1] = DAT_00461db4[1] + -1;
      if (DAT_00461db4[1] < 0) {
        uVar1 = _filbuf(DAT_00461db4);
      }
      else {
        uVar1 = (uint)*(byte *)*DAT_00461db4;
        *DAT_00461db4 = *DAT_00461db4 + 1;
      }
    }
    else {
      DAT_00469388 = '\0';
      uVar1 = (uint)DAT_00469384;
    }
    while ((0 < (int)uVar1 && (uVar1 != 10))) {
      local_c._0_1_ = (char)uVar1;
      *puVar2 = (char)local_c;
      puVar2 = puVar2 + 1;
      DAT_00461db4[1] = DAT_00461db4[1] + -1;
      if (DAT_00461db4[1] < 0) {
        uVar1 = _filbuf(DAT_00461db4);
      }
      else {
        uVar1 = (uint)*(byte *)*DAT_00461db4;
        *DAT_00461db4 = *DAT_00461db4 + 1;
      }
    }
    *puVar2 = 0;
    if (uVar1 == 10) {
      DAT_00461318 = DAT_00461318 + 1;
    }
    uVar1 = (0 < (int)uVar1) - 1;
  }
  else {
    if (DAT_00469388 == '\0') {
      DAT_00461db4[1] = DAT_00461db4[1] + -1;
      if (DAT_00461db4[1] < 0) {
        local_18 = _filbuf(DAT_00461db4);
      }
      else {
        local_18 = (uint)*(byte *)*DAT_00461db4;
        *DAT_00461db4 = *DAT_00461db4 + 1;
      }
      local_c = local_18;
    }
    else {
      DAT_00469388 = '\0';
      local_c = (uint)DAT_00469384;
    }
    if (0 < (int)local_c) {
      if (__mb_cur_max < 2) {
        uVar1 = *(ushort *)(_pctype + local_c * 2) & 8;
      }
      else {
        uVar1 = _isctype(local_c,8);
      }
      while ((uVar1 != 0 && ((local_c != 10 || (DAT_00461318 = DAT_00461318 + 1, param_1 != 10)))))
      {
        DAT_00461db4[1] = DAT_00461db4[1] + -1;
        if (DAT_00461db4[1] < 0) {
          local_20 = _filbuf(DAT_00461db4);
        }
        else {
          local_20 = (uint)*(byte *)*DAT_00461db4;
          *DAT_00461db4 = *DAT_00461db4 + 1;
        }
        local_c = local_20;
        if ((int)local_20 < 1) break;
        if (__mb_cur_max < 2) {
          uVar1 = *(ushort *)(_pctype + local_20 * 2) & 8;
        }
        else {
          uVar1 = _isctype(local_20,8);
        }
      }
    }
    if (((int)local_c < 1) || ((param_1 == 10 && (local_c != 10)))) {
      DAT_00461320 = '\0';
      uVar1 = 0xffffffff;
    }
    else {
      if (param_1 == 10) {
        DAT_00461db4[1] = DAT_00461db4[1] + -1;
        if (DAT_00461db4[1] < 0) {
          local_28 = _filbuf(DAT_00461db4);
        }
        else {
          local_28 = (uint)*(byte *)*DAT_00461db4;
          *DAT_00461db4 = *DAT_00461db4 + 1;
        }
        local_c = local_28;
        if (local_28 == 10) {
          DAT_00461318 = DAT_00461318 + 1;
          DAT_00461320 = 0;
          return 0;
        }
      }
      DAT_00461320 = (char)local_c;
      local_8 = &DAT_00461321;
      while( true ) {
        DAT_00461db4[1] = DAT_00461db4[1] + -1;
        if (DAT_00461db4[1] < 0) {
          local_2c = _filbuf(DAT_00461db4);
        }
        else {
          local_2c = (uint)*(byte *)*DAT_00461db4;
          *DAT_00461db4 = *DAT_00461db4 + 1;
        }
        local_c._0_1_ = (char)local_2c;
        if (((int)local_2c < 1) || ((param_1 == 10 && (local_2c == 10)))) break;
        if (param_1 != 10) {
          if (__mb_cur_max < 2) {
            local_30 = *(ushort *)(_pctype + local_2c * 2) & 8;
          }
          else {
            local_30 = _isctype(local_2c,8);
          }
          if (local_30 != 0) break;
        }
        *local_8 = (char)local_c;
        local_8 = local_8 + 1;
      }
      *local_8 = '\0';
      if (((int)local_2c < 1) || ((param_1 == 10 && (local_2c != 10)))) {
        uVar1 = 0xffffffff;
      }
      else if (param_1 == 10) {
        if (local_8[-1] == '\r') {
          local_8[-1] = '\0';
        }
        if (local_2c == 10) {
          DAT_00461318 = DAT_00461318 + 1;
        }
        uVar1 = 0;
      }
      else {
        DAT_00469384 = (char)local_c;
        DAT_00469388 = '\x01';
        uVar1 = (uint)(DAT_00461320 == '_');
      }
    }
  }
  return uVar1;
}


/* ==== FUN_00427710 @ 00427710 ==== */

void FUN_00427710(void)

{
  int iVar1;
  int local_10;
  int local_c;
  
  iVar1 = DAT_00461e98;
  if (DAT_00461248 == '\0') {
    DAT_00461e98 = 2;
    DAT_00461e9c = 0xc0;
    DAT_00461ea4 = (iVar1 + -2) * 0x34 + 0xc0;
  }
  else {
    DAT_00461e98 = 0;
    DAT_00461e9c = 0x54;
    DAT_00461ea4 = iVar1 * 0x34 + 0x54;
  }
  DAT_00461eac = DAT_00461ea4 + (DAT_00461ea8 + DAT_00461ef0) * 4;
  if (DAT_00461248 == '\0') {
    local_c = 0;
  }
  else {
    local_c = DAT_00461eb4 * 0xc;
  }
  DAT_00461ec0 = DAT_00461eac + local_c;
  if (DAT_0046124c == '\0') {
    local_10 = 0;
  }
  else {
    local_10 = DAT_00461ec8 * 0xc;
  }
  DAT_00461ed4 = DAT_00461ec0 + local_10;
  DAT_00461ea0 = DAT_00461ea4;
  DAT_00461eb0 = DAT_00461eac;
  DAT_00461ec4 = DAT_00461ec0;
  if (DAT_00461f38 != (void *)0x0) {
    iVar1 = fseek(DAT_00461f38,DAT_00461ea4,0);
    if (iVar1 != 0) {
      thunk_FUN_004098b0(s_Cannot_seek_to_start_of_object_d_0045a440);
    }
  }
  return;
}


/* ==== FUN_0042785f @ 0042785f ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0042785f(void)

{
  int *piVar1;
  
  if (DAT_00461f38 != 0) {
    if (DAT_00461248 == '\0') {
      FUN_00427d54();
      if (DAT_00461efc != 0) {
        FUN_00429870();
      }
    }
    FUN_00428356();
    if (DAT_0046124c != '\0') {
      FUN_004282de();
    }
    if (DAT_00461dc4 == (uint *)0x0) {
      if (DAT_00461248 != '\0') {
        _DAT_0046c348 = -1;
      }
    }
    else {
      DAT_00461d68 = DAT_00461dc4;
      piVar1 = thunk_FUN_0040a370();
      if (piVar1 != (int *)0x0) {
        DAT_004612fc = thunk_FUN_00407988((int)piVar1);
        DAT_00457ba8 = piVar1[7];
        thunk_FUN_0040ca80((undefined *)piVar1);
      }
      if (DAT_00461248 != '\0') {
        _DAT_0046c348 = thunk_FUN_00429716(DAT_00461dc4);
      }
      thunk_FUN_0042e1ce((undefined *)DAT_00461dc4);
    }
    FUN_00429399();
    FUN_00427941();
  }
  return;
}


/* ==== FUN_00427941 @ 00427941 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00427941(void)

{
  int iVar1;
  int local_10;
  int local_c;
  int local_8;
  
  iVar1 = fseek(DAT_00461f38,0,0);
  if (iVar1 != 0) {
    thunk_FUN_004098b0(s_Cannot_seek_to_start_of_object_f_0045a464);
  }
  _DAT_0046c120 = DAT_00461fa0;
  _DAT_0046c124 = DAT_00461e98;
  _DAT_0046c128 = ~-(uint)(DAT_00461260 != '\0') & _DAT_00461d44;
  _DAT_0046c12c = DAT_00461ed4;
  _DAT_0046c130 = DAT_00461ed8;
  _DAT_0046c134 = (-(uint)(DAT_00461248 != '\0') & 0xfffffffc) + 0x3c;
  DAT_0046c138 = 0;
  if (DAT_00461248 == '\0') {
    DAT_0046c138 = 1;
    if (DAT_004612ec == 0) {
      DAT_0046c138 = 3;
    }
  }
  else if (DAT_00461278 != '\0') {
    DAT_0046c138 = 0x20000;
  }
  if (DAT_0046124c == '\0') {
    DAT_0046c138 = DAT_0046c138 | 4;
  }
  if (DAT_0046120c != '\0') {
    DAT_0046c138 = DAT_0046c138 | 0x10000;
  }
  iVar1 = thunk_FUN_00430773(&DAT_0046c120,0x1c,1,DAT_00461f38);
  if (iVar1 != 1) {
    thunk_FUN_004098b0(s_Cannot_write_file_header_to_obje_0045a488);
  }
  if (DAT_00461248 == '\0') {
    _DAT_0046c2a0 = 0;
    _DAT_0046c2a4 = 0;
    _DAT_0046c2a8 = DAT_00461308 - DAT_00461300;
    _DAT_0046c2ac = DAT_0046130c - DAT_00461304;
    _DAT_0046c2b0 = 0;
    if (DAT_00461254 == '\0') {
      _DAT_0046c2b4 = DAT_00461300;
      _DAT_0046c2b8 = -(uint)(DAT_00457bac != 4) & DAT_00457bac;
    }
    else {
      _DAT_0046c2b4 = DAT_004612fc;
      _DAT_0046c2b8 = -(uint)(DAT_00457ba8 != 4) & DAT_00457ba8;
    }
    _DAT_0046c2bc = DAT_00461300;
    _DAT_0046c2c0 = -(uint)(DAT_00457bac != 4) & DAT_00457bac;
    _DAT_0046c2c4 = DAT_00461304;
    if (DAT_00457bb0 == 4) {
      local_10 = 1;
    }
    else {
      local_10 = DAT_00457bb0;
    }
    _DAT_0046c2c8 = local_10;
    _DAT_0046c2cc = DAT_00461308;
    _DAT_0046c2d0 = -(uint)(DAT_00457bb4 != 4) & DAT_00457bb4;
    _DAT_0046c2d4 = DAT_0046130c;
    _DAT_0046c2d8 = DAT_00457bb8;
    if (DAT_00457bb8 == 4) {
      _DAT_0046c2d8 = 1;
    }
    iVar1 = thunk_FUN_00430773(&DAT_0046c2a0,0x3c,1,DAT_00461f38);
    if (iVar1 != 1) {
      thunk_FUN_004098b0(s_Cannot_write_optional_header_to_o_0045a4dc);
    }
  }
  else {
    _DAT_0046c340 =
         (-(uint)(DAT_00461248 != '\0') & 0xfffffffc) + 0x58 + DAT_00461e98 * 0x34 +
         DAT_00461ea8 * 4 + DAT_00461eb4 * 0xc + DAT_00461ec8 * 0xc + DAT_00461ed8 * 0x20 +
         (-(uint)(4 < DAT_00457c04) & DAT_00457c04);
    _DAT_0046c344 = DAT_00461ea8;
    _DAT_0046c34c = DAT_0046129c;
    _DAT_0046c350 = DAT_00461e98;
    _DAT_0046c354 = DAT_00461eb4;
    _DAT_0046c358 = DAT_00461ec8;
    _DAT_0046c35c = DAT_004612b4;
    _DAT_0046c360 = DAT_004612cc;
    if (DAT_00461fd0 < DAT_00461fdc) {
      local_8 = DAT_00461fdc;
    }
    else {
      local_8 = DAT_00461fd0;
    }
    _DAT_0046c364 = local_8;
    if ((DAT_00461fdc < DAT_00461fd0) || (DAT_00461fe0 <= DAT_00461fd4)) {
      local_c = DAT_00461fd4;
    }
    else {
      local_c = DAT_00461fe0;
    }
    _DAT_0046c368 = local_c;
    _DAT_0046c36c = DAT_00461fd8;
    _DAT_0046c370 = 0;
    _DAT_0046c374 = DAT_00461ef8;
    iVar1 = thunk_FUN_00430773(&DAT_0046c340,0x38,1,DAT_00461f38);
    if (iVar1 != 1) {
      thunk_FUN_004098b0(s_Cannot_write_optional_header_to_o_0045a4b0);
    }
  }
  return;
}


/* ==== FUN_00427d54 @ 00427d54 ==== */

void FUN_00427d54(void)

{
  int iVar1;
  char local_6c [8];
  int local_64;
  uint local_60;
  int local_5c;
  uint local_58;
  int local_54;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  uint local_40;
  undefined4 local_3c;
  char local_38 [8];
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  undefined4 local_18;
  undefined4 local_8;
  
  memset(local_6c,0,0x68);
  strcpy(local_6c,s__text_00457fb0);
  thunk_FUN_004307d5(local_6c,4,2);
  local_5c = DAT_00461300;
  local_64 = DAT_00461300;
  local_60 = -(uint)(DAT_00457bac != 4) & DAT_00457bac;
  local_54 = DAT_00461308 - DAT_00461300;
  local_4c = DAT_00461eac;
  local_48 = DAT_00461ec0;
  local_44 = 0;
  local_40 = -(uint)(DAT_0046124c != '\0') & DAT_00461ec8;
  local_3c = 0x20;
  local_58 = local_60;
  strcpy(local_38,s__data_00457fc0);
  thunk_FUN_004307d5(local_38,4,2);
  local_28 = DAT_00461304;
  local_30 = DAT_00461304;
  local_2c = DAT_00457bb0;
  if (DAT_00457bb0 == 4) {
    local_2c = 1;
  }
  local_20 = DAT_0046130c - DAT_00461304;
  local_18 = DAT_00461eac;
  local_8 = 0x40;
  local_24 = local_2c;
  iVar1 = fseek(DAT_00461f38,0x58,0);
  if (iVar1 != 0) {
    thunk_FUN_004098b0(s_Cannot_seek_to_start_of_section_h_0045a508);
  }
  iVar1 = thunk_FUN_00430773(local_6c,0x34,2,DAT_00461f38);
  if (iVar1 != 2) {
    thunk_FUN_004098b0(s_Cannot_write__text__data_headers_0045a530);
  }
  return;
}


/* ==== FUN_00427ebb @ 00427ebb ==== */

void __cdecl FUN_00427ebb(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  ushort uVar4;
  ushort uVar5;
  bool bVar6;
  bool bVar7;
  uint local_10;
  int local_c;
  
  local_c = 0;
  uVar5 = 0;
  uVar4 = 0;
  uVar1 = *(uint *)(param_1 + 0x24);
  if (uVar1 != 0) {
    for (local_10 = *(uint *)(param_1 + 0x74); local_10 < *(int *)(param_1 + 0x74) + uVar1 * 0x34;
        local_10 = local_10 + 0x34) {
      bVar6 = (*(uint *)(local_10 + 0x30) & 8) != 0;
      bVar7 = (*(uint *)(local_10 + 0x30) & 0x80) != 0;
      if ((bVar6) || (bVar7)) {
        *(undefined4 *)(local_10 + 0x1c) = 0;
      }
      else {
        *(int *)(local_10 + 0x1c) = DAT_00461ea4 + local_c * 4;
        local_c = local_c + *(int *)(local_10 + 0x18);
      }
      if ((bVar6) || (bVar7)) {
        *(undefined4 *)(local_10 + 0x20) = 0;
        *(undefined4 *)(local_10 + 0x28) = 0;
      }
      else if (DAT_00461248 == '\0') {
        *(int *)(local_10 + 0x20) = DAT_00461eb0;
        *(undefined4 *)(local_10 + 0x28) = 0;
      }
      else {
        *(uint *)(local_10 + 0x20) = DAT_00461eb0 + (uint)uVar5 * 0xc;
        uVar5 = uVar5 + *(short *)(local_10 + 0x28);
      }
      if (bVar6) {
        *(undefined4 *)(local_10 + 0x24) = 0;
        *(undefined4 *)(local_10 + 0x2c) = 0;
      }
      else if (DAT_0046124c == '\0') {
        *(int *)(local_10 + 0x24) = DAT_00461ec4;
        *(undefined4 *)(local_10 + 0x2c) = 0;
      }
      else {
        *(uint *)(local_10 + 0x24) = DAT_00461ec4 + (uint)uVar4 * 0xc;
        uVar4 = uVar4 + *(short *)(local_10 + 0x2c);
      }
    }
    iVar2 = fseek(DAT_00461f38,DAT_00461e9c,0);
    if (iVar2 != 0) {
      thunk_FUN_004098b0(s_Cannot_seek_to_object_module_sec_0045a560);
    }
    uVar3 = thunk_FUN_004307a4(*(char **)(param_1 + 0x74),0x34,uVar1,DAT_00461f38);
    if (uVar3 != uVar1) {
      thunk_FUN_004098b0(s_Cannot_write_section_headers_to_o_0045a590);
    }
    thunk_FUN_0042e1ce(*(undefined **)(param_1 + 0x74));
    DAT_00461e9c = DAT_00461e9c + uVar1 * 0x34;
  }
  uVar1 = *(uint *)(param_1 + 0x40);
  if (uVar1 != 0) {
    iVar2 = fseek(DAT_00461f38,DAT_00461ea4,0);
    if (iVar2 != 0) {
      thunk_FUN_004098b0(s_Cannot_seek_to_object_module_raw_0045a5c0);
    }
    uVar3 = thunk_FUN_004307a4((char *)DAT_00461f38,4,uVar1,DAT_00461f38);
    if (uVar3 != uVar1) {
      thunk_FUN_004098b0(s_Cannot_write_raw_data_to_object_m_0045a5e8);
    }
    thunk_FUN_0042e1ce(*(undefined **)(param_1 + 0x78));
    if (*(int *)(param_1 + 0x7c) != 0) {
      thunk_FUN_0042e1ce(*(undefined **)(param_1 + 0x7c));
    }
    DAT_00461ea4 = DAT_00461ea4 + uVar1 * 4;
  }
  uVar1 = *(uint *)(param_1 + 0x50);
  if (uVar1 != 0) {
    if (DAT_00461248 != '\0') {
      iVar2 = fseek(DAT_00461f38,DAT_00461eb0,0);
      if (iVar2 != 0) {
        thunk_FUN_004098b0(s_Cannot_seek_to_object_module_rel_0045a610);
      }
      uVar3 = thunk_FUN_004307a4(*(char **)(param_1 + 0x84),0xc,uVar1,DAT_00461f38);
      if (uVar3 != uVar1) {
        thunk_FUN_004098b0(s_Cannot_write_relocation_entries_t_0045a640);
      }
      DAT_00461eb0 = DAT_00461eb0 + uVar1 * 0xc;
    }
    thunk_FUN_0042e1ce(*(undefined **)(param_1 + 0x84));
  }
  iVar2 = *(int *)(param_1 + 0x54);
  if (iVar2 != 0) {
    if (DAT_0046124c != '\0') {
      if (DAT_00461ed0 == 0) {
        DAT_00461ecc = (int *)thunk_FUN_0042e170(iVar2 * 0xc);
      }
      else {
        DAT_00461ecc = thunk_FUN_0042e19d(DAT_00461ecc,(DAT_00461ed0 + iVar2) * 0xc);
      }
      memcpy(DAT_00461ecc + DAT_00461ed0 * 3,*(void **)(param_1 + 0x88),iVar2 * 0xc);
      DAT_00461ed0 = DAT_00461ed0 + iVar2;
      DAT_00461ec4 = DAT_00461ec4 + iVar2 * 0xc;
    }
    thunk_FUN_0042e1ce(*(undefined **)(param_1 + 0x88));
  }
  return;
}


/* ==== FUN_004282de @ 004282de ==== */

void FUN_004282de(void)

{
  int iVar1;
  uint uVar2;
  
  if (DAT_00461ec8 != 0) {
    iVar1 = fseek(DAT_00461f38,DAT_00461ec0,0);
    if (iVar1 != 0) {
      thunk_FUN_004098b0(s_Cannot_seek_to_start_of_line_num_0045a674);
    }
    uVar2 = thunk_FUN_004307a4(DAT_00461ecc,0xc,DAT_00461ec8,DAT_00461f38);
    if (uVar2 != DAT_00461ec8) {
      thunk_FUN_004098b0(s_Cannot_write_line_number_entries_0045a6a0);
    }
    thunk_FUN_0042e1ce(DAT_00461ecc);
  }
  return;
}


/* ==== FUN_00428356 @ 00428356 ==== */

void FUN_00428356(void)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  
  if (DAT_00461ed8 != 0) {
    piVar3 = DAT_00461edc;
    if (DAT_00461248 == '\0') {
      FUN_00428449();
      FUN_00428524();
      FUN_0042930e();
      FUN_00428e67();
      piVar3 = DAT_00461edc;
    }
    for (; piVar3 < DAT_00461edc + DAT_00461ed8 * 8; piVar3 = piVar3 + piVar3[7] * 8 + 8) {
      if (*piVar3 != 0) {
        thunk_FUN_004307d5((undefined1 *)piVar3,4,2);
      }
    }
    iVar1 = fseek(DAT_00461f38,DAT_00461ed4,0);
    if (iVar1 != 0) {
      thunk_FUN_004098b0(s_Cannot_seek_to_start_of_symbol_t_0045a6d0);
    }
    uVar2 = thunk_FUN_004307a4((char *)DAT_00461edc,0x20,DAT_00461ed8,DAT_00461f38);
    if (uVar2 != DAT_00461ed8) {
      thunk_FUN_004098b0(s_Cannot_write_symbols_to_object_f_0045a6f8);
    }
    thunk_FUN_0042e1ce((undefined *)DAT_00461edc);
  }
  return;
}


/* ==== FUN_00428449 @ 00428449 ==== */

void FUN_00428449(void)

{
  int iVar1;
  int *piVar2;
  int *local_10;
  
  local_10 = DAT_00461f04;
  while (local_10 != (int *)0x0) {
    iVar1 = DAT_00461edc + local_10[0xc] * 0x20;
    piVar2 = (int *)(DAT_00461edc + (local_10[0xc] + 1) * 0x20);
    *(int *)(iVar1 + 8) = *local_10;
    *(int *)(iVar1 + 0xc) = local_10[3];
    *piVar2 = local_10[1] - *local_10;
    *(int *)(iVar1 + 0x48) = local_10[6];
    *(int *)(iVar1 + 0x4c) = local_10[9];
    piVar2[0x10] = local_10[7] - local_10[6];
    piVar2 = (int *)local_10[0xd];
    thunk_FUN_0042e1ce((undefined *)local_10);
    local_10 = piVar2;
  }
  DAT_00461f08 = 0;
  DAT_00461f04 = (int *)0x0;
  return;
}


/* ==== FUN_00428524 @ 00428524 ==== */

void FUN_00428524(void)

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
  puVar1 = (undefined4 *)thunk_FUN_0042e170((DAT_00461ed8 + 2) * 0x20);
  local_1c = 0;
  local_18 = puVar1;
  do {
    iVar2 = local_1c;
    if (DAT_00461ed8 <= local_1c) {
      for (local_1c = 0; local_1c < DAT_00461ed8; local_1c = local_1c + 1) {
        puVar6 = (undefined4 *)((int)DAT_00461edc + local_1c * 0x20);
        if (((((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) ||
             ((puVar6[6] != 2 && ((puVar6[6] != 0xd2 && (puVar6[6] != 0xd3)))))) &&
            (((4 < DAT_00461fe8 || ((DAT_00461fe8 == 4 && (1 < DAT_00461fec)))) ||
             ((puVar6[6] != 2 &&
              (((puVar6[6] != 0xd2 && (puVar6[6] != 0xd3)) && (puVar6[6] != 0x6a)))))))) ||
           ((puVar6[5] & 0x30) == 0x20)) {
          local_1c = local_1c + puVar6[7];
        }
        else {
          puVar7 = puVar6;
          puVar8 = local_18;
          for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar8 = *puVar7;
            puVar7 = puVar7 + 1;
            puVar8 = puVar8 + 1;
          }
          for (local_20 = 0; local_18 = local_18 + 8, local_20 < (int)puVar6[7];
              local_20 = local_20 + 1) {
            local_1c = local_1c + 1;
            puVar7 = (undefined4 *)((int)DAT_00461edc + local_1c * 0x20);
            puVar8 = local_18;
            for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
              *puVar8 = *puVar7;
              puVar7 = puVar7 + 1;
              puVar8 = puVar8 + 1;
            }
          }
        }
      }
      thunk_FUN_0042e1ce((undefined *)DAT_00461edc);
      DAT_00461edc = puVar1;
      return;
    }
    puVar6 = (undefined4 *)((int)DAT_00461edc + local_1c * 0x20);
    if ((puVar6[6] == 0x67) || (puVar6[6] == 200)) {
      iVar3 = (int)local_18 - (int)puVar1 >> 5;
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
        puVar7 = (undefined4 *)((int)DAT_00461edc + local_1c * 0x20);
        puVar8 = local_18;
        for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar8 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar8 = puVar8 + 1;
        }
      }
      while (local_1c = iVar4 + 1, local_1c < DAT_00461ed8) {
        puVar6 = (undefined4 *)((int)DAT_00461edc + local_1c * 0x20);
        if (puVar6[6] == 0x65) {
          local_14 = local_14 + (-(uint)(*(char *)((int)puVar6 + 1) != 'b') & 0xfffffffe) + 1;
        }
        if (puVar6[6] == 100) {
          local_8 = local_8 + (-(uint)(*(char *)((int)puVar6 + 1) != 'b') & 0xfffffffe) + 1;
        }
        if ((puVar6[6] == 0x67) || (puVar6[6] == 200)) break;
        if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
          if (((puVar6[5] & 0x30) == 0x20) ||
             (((puVar6[6] != 3 || (((local_14 != 0 || (local_8 != 0)) && (puVar6[5] != 0)))) &&
              ((((puVar6[6] != 2 && (puVar6[6] != 0xd2)) && (puVar6[6] != 0xd3)) &&
               (puVar6[6] != 0x6a)))))) {
LAB_00428894:
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
              puVar7 = (undefined4 *)((int)DAT_00461edc + local_1c * 0x20);
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
        else {
          if (((puVar6[5] & 0x30) == 0x20) ||
             (((puVar6[6] != 3 || (((local_14 != 0 || (local_8 != 0)) && (puVar6[5] != 0)))) &&
              (((puVar6[6] != 2 && (puVar6[6] != 0xd2)) && (puVar6[6] != 0xd3))))))
          goto LAB_00428894;
          iVar4 = local_1c + puVar6[7];
        }
      }
      for (local_20 = iVar2; local_20 < local_1c; local_20 = local_20 + 1) {
        puVar6 = (undefined4 *)((int)DAT_00461edc + local_20 * 0x20);
        if (puVar6[6] == 0x65) {
          local_14 = local_14 + (-(uint)(*(char *)((int)puVar6 + 1) != 'b') & 0xfffffffe) + 1;
        }
        if (puVar6[6] == 100) {
          local_8 = local_8 + (-(uint)(*(char *)((int)puVar6 + 1) != 'b') & 0xfffffffe) + 1;
        }
        if (((puVar6[6] == 3) && (((local_14 == 0 && (local_8 == 0)) || (puVar6[5] == 0)))) &&
           ((puVar6[5] & 0x30) != 0x20)) {
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
            puVar7 = (undefined4 *)((int)DAT_00461edc + local_20 * 0x20);
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
      FUN_00428bc4(iVar3,iVar3,iVar5,iVar5,(int)puVar1,(int)puVar1);
      FUN_00428bc4(iVar2,iVar3,local_1c,iVar5,(int)DAT_00461edc,(int)puVar1);
      local_1c = iVar4;
    }
    else if (((puVar6[5] & 0x30) == 0x20) ||
            ((((4 < DAT_00461fe8 || ((DAT_00461fe8 == 4 && (1 < DAT_00461fec)))) &&
              ((puVar6[6] != 2 && ((puVar6[6] != 0xd2 && (puVar6[6] != 0xd3)))))) ||
             (((DAT_00461fe8 < 5 &&
               (((DAT_00461fe8 != 4 || (DAT_00461fec < 2)) && (puVar6[6] != 2)))) &&
              (((puVar6[6] != 0xd2 && (puVar6[6] != 0xd3)) && (puVar6[6] != 0x6a)))))))) {
      puVar7 = puVar6;
      puVar8 = local_18;
      for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      for (local_20 = 0; local_18 = local_18 + 8, local_20 < (int)puVar6[7]; local_20 = local_20 + 1
          ) {
        local_1c = local_1c + 1;
        puVar7 = (undefined4 *)((int)DAT_00461edc + local_1c * 0x20);
        puVar8 = local_18;
        for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar8 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar8 = puVar8 + 1;
        }
      }
    }
    local_1c = local_1c + 1;
  } while( true );
}


/* ==== FUN_00428bc4 @ 00428bc4 ==== */

void __cdecl FUN_00428bc4(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

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
    if ((DAT_00461fe8 < 5) && ((DAT_00461fe8 != 4 || (DAT_00461fec < 2)))) {
      if ((param_1 == param_2) ||
         ((((piVar1[6] == 2 || (piVar1[6] == 0xd2)) || ((piVar1[6] == 0xd3 || (piVar1[6] == 0x6a))))
          && ((piVar1[5] & 0x30U) != 0x20)))) {
LAB_00428cb5:
        if ((((piVar1[6] != 10) && (piVar1[6] != 0xc)) &&
            ((piVar1[6] != 0xf && ((0 < piVar1[7] && (piVar1[8] != 0)))))) &&
           (((piVar1[5] & 0x1000fU) == 8 ||
            ((((piVar1[5] & 0x1000fU) == 9 || ((piVar1[5] & 0x1000fU) == 10)) || (piVar1[6] == 0x66)
             ))))) {
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
              if (((uint)piVar1[1] < 5) || (DAT_00461eec <= piVar1[1])) {
                local_18 = (int *)0x0;
              }
              else {
                local_18 = (int *)(DAT_00461ee8 + piVar1[1]);
              }
            }
            if (local_18 == (int *)0x0) {
              thunk_FUN_00409a25(s_Symbol_tag_mismatch_0045a730);
            }
            else {
              thunk_FUN_00409bfd(s_Symbol_tag_mismatch_0045a71c,local_18);
            }
          }
        }
        local_10 = local_10 + piVar1[7];
      }
      else {
        local_10 = local_10 + piVar1[7];
      }
    }
    else {
      if ((param_1 == param_2) ||
         ((((piVar1[6] == 2 || (piVar1[6] == 0xd2)) || (piVar1[6] == 0xd3)) &&
          ((piVar1[5] & 0x30U) != 0x20)))) goto LAB_00428cb5;
      local_10 = local_10 + piVar1[7];
    }
    local_10 = local_10 + 1;
  } while( true );
}


/* ==== FUN_00428e67 @ 00428e67 ==== */

void FUN_00428e67(void)

{
  int iVar1;
  int iVar2;
  int local_4c;
  int local_44;
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
  
  local_40 = -1;
  local_44 = -1;
  local_3c = -1;
  local_18 = 0;
  local_c = 0;
  local_24 = 0;
  local_20 = 0;
  local_30 = 0;
  local_28 = 0;
  local_10 = 0;
  local_8 = 0;
  local_4c = 0;
  if (DAT_00461ed8 != 0) {
    for (local_34 = 0; local_34 < DAT_00461ed8; local_34 = local_34 + *(int *)(iVar2 + 0x1c) + 1) {
      iVar2 = DAT_00461edc + local_34 * 0x20;
      if (*(int *)(iVar2 + 0x18) == 0x65) {
        local_18 = local_18 + (-(uint)(*(char *)(iVar2 + 1) != 'b') & 0xfffffffe) + 1;
      }
      if (*(int *)(iVar2 + 0x18) == 100) {
        local_c = local_c + (-(uint)(*(char *)(iVar2 + 1) != 'b') & 0xfffffffe) + 1;
      }
      if ((*(int *)(iVar2 + 0x18) == 0x67) || (*(int *)(iVar2 + 0x18) == 200)) {
        if (local_20 != 0) {
          *(int *)(local_20 + 0x10) = local_40;
        }
        if (local_28 != 0) {
          *(int *)(local_28 + 0x10) = local_40;
        }
        if (local_10 != 0) {
          *(int *)(local_10 + 0x10) = local_40;
        }
        if (local_8 != 0) {
          *(int *)(local_8 + 0x10) = local_40;
        }
        if (local_4c != 0) {
          *(int *)(local_4c + 0x10) = local_40;
        }
        if (local_30 != 0) {
          *(int *)(local_30 + 0x10) = local_40;
        }
        local_40 = -1;
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
            thunk_FUN_00409a25(s_No_previous_function_declaration_0045a744);
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
          if (local_4c != 0) {
            *(int *)(local_4c + 0x10) = local_34;
          }
          local_4c = iVar2 + 0x20;
        }
        else if ((((*(int *)(iVar2 + 0x18) == 3) && (local_18 == 0)) && (local_c == 0)) &&
                ((*(uint *)(iVar2 + 0x14) & 0x30) != 0x20)) {
          if (local_40 < 0) {
            local_40 = local_34;
          }
          if ((DAT_00461248 != '\0') && (*(int *)(iVar2 + 0x14) == 0)) {
            if (0 < local_3c) {
              *(int *)(iVar2 + 0x30) = local_3c;
            }
            local_3c = local_34;
          }
        }
      }
      local_24 = iVar1;
      if (((*(uint *)(iVar2 + 0x14) & 0x30) == 0x20) && (0 < *(int *)(iVar2 + 0x10))) {
        if (DAT_00461ecc != 0) {
          iVar1 = *(int *)(iVar2 + 0x2c);
          if (DAT_00461210 != '\0') {
            *(int *)(DAT_00461ecc + iVar1 * 0xc) = local_34;
          }
          *(int *)(iVar2 + 0x2c) = DAT_00461ec0 + iVar1 * 0xc;
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
      if ((((local_44 < 0) && ((*(int *)(iVar2 + 0x18) == 2 || (*(int *)(iVar2 + 0x18) == 0xd2))))
          && (*(int *)(iVar2 + 0x10) != 0)) && ((*(uint *)(iVar2 + 0x14) & 0x30) != 0x20)) {
        local_44 = local_34;
      }
    }
    for (local_34 = 0; local_34 < DAT_00461ed8; local_34 = local_34 + *(int *)(iVar2 + 0x1c) + 1) {
      iVar2 = DAT_00461edc + local_34 * 0x20;
      if (((*(int *)(iVar2 + 0x18) == 10) || (*(int *)(iVar2 + 0x18) == 0xc)) ||
         (*(int *)(iVar2 + 0x18) == 0xf)) {
        *(undefined4 *)(iVar2 + 0x20) = 0;
      }
      else if (((DAT_00461248 == '\0') && (*(int *)(iVar2 + 0x18) == 3)) &&
              (*(int *)(iVar2 + 0x14) == 0)) {
        *(undefined4 *)(iVar2 + 0x30) = 0;
      }
    }
    if (local_20 != 0) {
      *(int *)(local_20 + 0x10) = local_40;
    }
    if (local_28 != 0) {
      *(int *)(local_28 + 0x10) = local_40;
    }
    if (local_10 != 0) {
      *(int *)(local_10 + 0x10) = local_40;
    }
    if (local_8 != 0) {
      *(int *)(local_8 + 0x10) = local_40;
    }
    if (local_4c != 0) {
      *(int *)(local_4c + 0x10) = local_40;
    }
    if (local_30 != 0) {
      *(int *)(local_30 + 0x10) = local_40;
    }
    if (local_24 != 0) {
      *(int *)(local_24 + 8) = local_44;
    }
  }
  return;
}


/* ==== FUN_0042930e @ 0042930e ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0042930e(void)

{
  thunk_FUN_00430534();
  strcpy(&DAT_0046c140,s_etext_0045a768);
  _DAT_0046c148 = DAT_00461308;
  _DAT_0046c14c = 0;
  _DAT_0046c150 = 0xffffffff;
  _DAT_0046c158 = 2;
  DAT_0046c15c = 0;
  thunk_FUN_00429641((undefined4 *)&DAT_0046c140);
  memset(&DAT_0046c140,0,8);
  strcpy(&DAT_0046c140,&DAT_0045a770);
  thunk_FUN_00429641((undefined4 *)&DAT_0046c140);
  return;
}


/* ==== FUN_00429399 @ 00429399 ==== */

void FUN_00429399(void)

{
  int iVar1;
  uint uVar2;
  
  DAT_00461ee4 = DAT_00461ed4 + DAT_00461ed8 * 0x20;
  if (DAT_00461ee8 != (uint *)0x0) {
    iVar1 = fseek(DAT_00461f38,DAT_00461ee4,0);
    if (iVar1 != 0) {
      thunk_FUN_004098b0(s_Cannot_seek_to_start_of_string_t_0045a774);
    }
    *DAT_00461ee8 = DAT_00457c04;
    thunk_FUN_004307d5((undefined1 *)DAT_00461ee8,4,1);
    uVar2 = thunk_FUN_004306a1((char *)DAT_00461ee8,1,DAT_00457c04,DAT_00461f38);
    if (uVar2 != DAT_00457c04) {
      thunk_FUN_004098b0(s_Cannot_write_string_table_to_obj_0045a79c);
    }
    thunk_FUN_0042e1ce((undefined *)DAT_00461ee8);
  }
  return;
}


