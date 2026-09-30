/* procop: 33 functions from ASM56000 */

/* ==== FUN_0042420d @ 0042420d ==== */

int __cdecl FUN_0042420d(uint *param_1)

{
  int *piVar1;
  int iVar2;
  
  if (DAT_0044f790 == '\0') {
    FUN_00412fa0((uint *)s_Attempt_to_write_relocation_entr_00455d34);
  }
  if ((DAT_0045f8fc == 2) && (DAT_0045fca8 != 0)) {
    if (DAT_0045fbb8 == (int *)0x0) {
      DAT_0045fbbc = DAT_0045fbbc + 0x1000;
      DAT_0045fbb8 = (int *)FUN_00439857(DAT_0045fbbc * 0xc);
    }
    else if (DAT_0045fbbc <= DAT_0045fbb4) {
      if (DAT_0045fbbc < 0x40000) {
        DAT_0045fbbc = DAT_0045fbbc << 1;
      }
      else {
        DAT_0045fbbc = DAT_0045fbbc + 0x40000;
      }
      DAT_0045fbb8 = FUN_00439884(DAT_0045fbb8,DAT_0045fbbc * 0xc);
    }
    piVar1 = DAT_0045fbb8 + DAT_0045fbb4 * 3;
    *piVar1 = *DAT_0045f8cc;
    iVar2 = FUN_0042456e(param_1);
    piVar1[1] = iVar2;
    piVar1[2] = 0;
    *(int *)(*(int *)(DAT_0045fb8c + 0x24) + 0x28) =
         *(int *)(*(int *)(DAT_0045fb8c + 0x24) + 0x28) + 1;
  }
  iVar2 = DAT_0045fbb4;
  DAT_0045fbb4 = DAT_0045fbb4 + 1;
  return iVar2;
}


/* ==== FUN_0042433e @ 0042433e ==== */

int __cdecl FUN_0042433e(int param_1)

{
  int iVar1;
  int *piVar2;
  
  if ((DAT_0045f8fc == 2) && (DAT_0045fca8 != 0)) {
    if (DAT_0045fbc8 == (int *)0x0) {
      DAT_0045fbcc = DAT_0045fbcc + 0x1000;
      DAT_0045fbc8 = (int *)FUN_00439857(DAT_0045fbcc * 0xc);
    }
    else if (DAT_0045fbcc <= DAT_0045fbc4) {
      if (DAT_0045fbcc < 0x40000) {
        DAT_0045fbcc = DAT_0045fbcc << 1;
      }
      else {
        DAT_0045fbcc = DAT_0045fbcc + 0x40000;
      }
      DAT_0045fbc8 = FUN_00439884(DAT_0045fbc8,DAT_0045fbcc * 0xc);
    }
    piVar2 = DAT_0045fbc8 + DAT_0045fbc4 * 3;
    if (param_1 == 0) {
      *piVar2 = DAT_0045fbd4;
    }
    else {
      *piVar2 = *DAT_0045f8c0;
      piVar2[1] = DAT_0045f8a4;
    }
    piVar2[2] = param_1;
  }
  if ((DAT_0045fb8c != 0) && (DAT_0045f8fc == 1)) {
    *(int *)(*(int *)(DAT_0045fb8c + 0x24) + 0x2c) =
         *(int *)(*(int *)(DAT_0045fb8c + 0x24) + 0x2c) + 1;
  }
  DAT_0045fc14 = DAT_0045fc14 + 1;
  iVar1 = DAT_0045fbc4;
  DAT_0045fbc4 = DAT_0045fbc4 + 1;
  return iVar1;
}


/* ==== FUN_0042447e @ 0042447e ==== */

int __cdecl FUN_0042447e(undefined4 *param_1)

{
  int iVar1;
  
  if (DAT_0045ead8 == '\0') {
    if ((DAT_0045f8fc == 2) && (DAT_0045fca8 != 0)) {
      if (DAT_0045fbd8 == (int *)0x0) {
        DAT_0045fbdc = DAT_0045fbdc + 0x1000;
        DAT_0045fbd8 = (int *)FUN_00439857(DAT_0045fbdc * 0x20);
      }
      else if (DAT_0045fbdc <= DAT_0045fbd4) {
        if (DAT_0045fbdc < 0x40000) {
          DAT_0045fbdc = DAT_0045fbdc << 1;
        }
        else {
          DAT_0045fbdc = DAT_0045fbdc + 0x40000;
        }
        DAT_0045fbd8 = FUN_00439884(DAT_0045fbd8,DAT_0045fbdc << 5);
      }
      memcpy(DAT_0045fbd8 + DAT_0045fbd4 * 8,param_1,0x20);
    }
    iVar1 = DAT_0045fbd4;
    DAT_0045fbd4 = DAT_0045fbd4 + 1;
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}


/* ==== FUN_0042456e @ 0042456e ==== */

int __cdecl FUN_0042456e(uint *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  uVar1 = strlen((char *)param_1);
  iVar3 = DAT_0044f988;
  iVar2 = uVar1 + 1;
  if (DAT_0045ead8 == '\0') {
    if ((DAT_0045f8fc == 2) && (DAT_0045fca8 != 0)) {
      if ((DAT_0045fbe4 != (int *)0x0) &&
         (piVar4 = FUN_00438c00((char *)param_1), piVar4 != (int *)0x0)) {
        return *piVar4;
      }
      uVar1 = DAT_0045fbe8;
      if (DAT_0045fbe4 == (int *)0x0) {
        DAT_0045fbe8 = DAT_0045fbe8 + 0x1000;
        DAT_0045fbe4 = (int *)FUN_00439857(DAT_0045fbe8);
        memset(DAT_0045fbe4,0,DAT_0045fbe8);
      }
      else if ((int)DAT_0045fbe8 <= DAT_0044f988 + iVar2) {
        if ((int)DAT_0045fbe8 < 0x40000) {
          DAT_0045fbe8 = DAT_0045fbe8 << 1;
        }
        else {
          DAT_0045fbe8 = DAT_0045fbe8 + 0x40000;
        }
        DAT_0045fbe4 = FUN_00439884(DAT_0045fbe4,DAT_0045fbe8);
        memset((void *)((int)DAT_0045fbe4 + uVar1),0,DAT_0045fbe8 - uVar1);
      }
      strcpy((char *)((int)DAT_0045fbe4 + DAT_0044f988),(char *)param_1);
      *(undefined1 *)((int)DAT_0045fbe4 + DAT_0044f988 + iVar2) = 0;
      piVar4 = (int *)FUN_00439857(8);
      *piVar4 = iVar3;
      piVar4[1] = 0;
      if (DAT_0045fc58 == 0) {
        uVar1 = FUN_00439b65((char *)param_1);
        *(int **)(&DAT_00462c18 + uVar1 * 4) = piVar4;
      }
      else {
        *(int **)(DAT_0045fc58 + 4) = piVar4;
      }
    }
    DAT_0044f988 = DAT_0044f988 + iVar2;
  }
  else {
    iVar3 = 0;
  }
  return iVar3;
}


/* ==== FUN_00424733 @ 00424733 ==== */

void __cdecl FUN_00424733(uint *param_1,undefined4 param_2)

{
  if (DAT_0045fb8c != 0) {
    if (DAT_0045f8fc < 2) {
      *(int *)(DAT_0045fb8c + 0x20) = *(int *)(DAT_0045fb8c + 0x20) + 1;
    }
    else if (DAT_0045fca8 != 0) {
      FUN_0043c34d();
      strcpy((char *)&DAT_00465a60,&DAT_0044fa90);
      DAT_00465a68 = FUN_0042456e(param_1);
      DAT_00465a6c = 4;
      DAT_00465a70 = param_2;
      FUN_0042447e(&DAT_00465a60);
    }
  }
  return;
}


/* ==== FUN_004247b1 @ 004247b1 ==== */

void __cdecl FUN_004247b1(undefined4 param_1)

{
  if ((DAT_0045fb8c != 0) && (DAT_0045fca8 != 0)) {
    FUN_0043c34d();
    strcpy((char *)&DAT_00465a60,&DAT_0044fa98);
    DAT_00465a68 = param_1;
    DAT_00465a6c = 4;
    DAT_00465a70 = *(undefined4 *)(DAT_0045fb8c + 0x1c);
    DAT_00465a78 = 0x81;
    FUN_0042447e(&DAT_00465a60);
  }
  return;
}


/* ==== FUN_00424817 @ 00424817 ==== */

void __cdecl FUN_00424817(undefined4 *param_1)

{
  undefined4 *puVar1;
  uint *s;
  bool bVar2;
  uint uVar3;
  int local_24;
  int local_20;
  int local_1c;
  undefined4 local_18;
  
  puVar1 = (undefined4 *)param_1[0x15];
  if ((DAT_0045f8fc == 2) && (DAT_0045fca8 != 0)) {
    if (puVar1 != (undefined4 *)0x0) {
      puVar1[4] = param_1[0xd];
      if ((puVar1[6] == 2) || (puVar1[6] == 3)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      FUN_0042447e(puVar1);
      if (0 < (int)puVar1[7]) {
        FUN_0042447e((undefined4 *)param_1[0x16]);
      }
      FUN_004398b5((undefined *)puVar1);
      param_1[0x15] = 0;
      FUN_004398b5((undefined *)param_1[0x16]);
      param_1[0x16] = 0;
      if (bVar2) {
        FUN_0043c34d();
        return;
      }
    }
    FUN_0043c34d();
    s = (uint *)*param_1;
    uVar3 = strlen((char *)s);
    if (uVar3 < 8) {
      strcpy((char *)&DAT_00465a60,(char *)s);
    }
    else {
      DAT_00465a64 = FUN_0042456e(s);
    }
    if (param_1[7] == 4) {
      if ((param_1[6] & 0x200) == 0) {
        if (param_1[3] == 0) {
          local_18 = 4;
        }
        else {
          local_18 = param_1[3];
        }
        DAT_00465a6c = local_18;
        DAT_00465a68 = param_1[4];
      }
      else {
        FUN_0040baed(param_1[2],param_1[3],&DAT_00465a6c,&DAT_00465a68);
      }
    }
    else {
      DAT_00465a6c = param_1[8];
      DAT_00465a68 = param_1[4];
    }
    DAT_00465a70 = 0xffffffff;
    if ((param_1[6] & 0x200) == 0) {
      DAT_00465a74 = ((param_1[6] & 0x800) != 0) + 4;
      if (param_1[7] != 4) {
        DAT_00465a70 = param_1[0xd];
      }
    }
    else {
      DAT_00465a74 = 6;
    }
    if ((param_1[6] & 0x40) == 0) {
      if ((param_1[6] & 0x80) == 0) {
        if ((param_1[6] & 0x20) == 0) {
          local_24 = 0xd5;
        }
        else {
          local_24 = (DAT_0045fb6c != 0) + 0xd6;
        }
        local_20 = local_24;
      }
      else {
        local_20 = 0xd3;
      }
      local_1c = local_20;
    }
    else {
      local_1c = (-(uint)(DAT_0045ea98 != '\0') & 0xffffff30) + 0xd2;
    }
    DAT_00465a78 = local_1c;
    if (((param_1[6] & 0x40) != 0) && (param_1[7] == 0)) {
      DAT_00465a74 = DAT_00465a74 | 0x20;
      DAT_00465a7c = 1;
    }
    if (((((param_1[6] & 0x1000) == 0) && (param_1[7] != 4)) && ((param_1[6] & 0x400) != 0)) &&
       ((DAT_00465a74 & 0x30) != 0x20)) {
      DAT_00465a74 = DAT_00465a74 | 0x10;
      DAT_00465a70 = 0xffffffff;
    }
    FUN_0042447e(&DAT_00465a60);
    if (0 < DAT_00465a7c) {
      FUN_0042447e(&DAT_00465880);
    }
  }
  return;
}


/* ==== FUN_00424b1a @ 00424b1a ==== */

void __cdecl FUN_00424b1a(undefined4 *param_1)

{
  uint uVar1;
  int local_8;
  
  if ((DAT_0045f8fc == 2) && (DAT_0045fca8 != 0)) {
    FUN_0043c34d();
    uVar1 = strlen((char *)*param_1);
    if (uVar1 < 8) {
      strcpy((char *)&DAT_00465a60,(char *)*param_1);
    }
    else {
      DAT_00465a64 = FUN_0042456e((uint *)*param_1);
    }
    DAT_00465a68 = *(undefined4 *)(param_1[2] + 8);
    DAT_00465a70 = 0;
    if ((param_1[1] & 0x40) == 0) {
      local_8 = (-(uint)((param_1[1] & 0x80) != 0) & 0xfffffffe) + 0xd5;
    }
    else {
      local_8 = (-(uint)(DAT_0045ea98 != '\0') & 0xffffff30) + 0xd2;
    }
    DAT_00465a78 = local_8;
    FUN_0042447e(&DAT_00465a60);
  }
  return;
}


/* ==== FUN_00424bf0 @ 00424bf0 ==== */

uint __cdecl FUN_00424bf0(int param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar2;
  int local_f4;
  int local_f0 [7];
  undefined *local_d4;
  int local_d0;
  int local_cc;
  undefined *local_b4;
  int local_b0;
  uint local_ac;
  uint local_a8;
  uint *local_70;
  uint *local_6c;
  int local_60 [7];
  undefined *local_44;
  uint local_40;
  int local_3c;
  int local_38;
  undefined *local_20;
  int local_1c;
  uint local_18;
  int local_14;
  uint local_10 [3];
  
  local_1c = (int)*(char *)(param_1 + 4);
  local_18 = 1;
  if ((DAT_0045eaa8 == '\0') || (DAT_0045f8c0 == DAT_0045f8cc)) {
    local_f4 = 1;
  }
  else {
    local_f4 = 3;
  }
  local_14 = local_f4;
  if (DAT_0045f8a0 == 0) {
    FUN_0041b339();
    local_44 = (undefined *)0x0;
    local_d4 = (undefined *)0x0;
    local_20 = (undefined *)0x0;
    local_b4 = (undefined *)0x0;
    local_b0 = 1;
    local_ac = *(uint *)(param_1 + 0xc);
    local_a8 = 0;
    local_6c = (uint *)0x0;
    local_70 = (uint *)0x0;
    DAT_0045f860 = PTR_DAT_0044f818;
    switch(local_1c) {
    case 1:
      local_18 = FUN_0042578d((int)&local_b0);
      break;
    case 2:
    case 3:
    case 0x27:
    case 0x28:
      local_18 = FUN_004256e7(local_1c,(int)&local_b0);
      break;
    case 4:
      local_18 = FUN_0042562d((int)&local_b0);
      break;
    case 5:
    case 6:
      local_18 = FUN_00425abb(local_1c,&local_b0);
      break;
    case 7:
    case 0x22:
    case 0x23:
      local_18 = FUN_00425883(local_1c,(int)&local_b0);
      break;
    case 8:
      local_18 = FUN_00425a60((int)&local_b0);
      break;
    case 9:
      local_18 = FUN_00425d15(&local_b0);
      break;
    case 10:
      bVar1 = FUN_00426106();
      local_18 = CONCAT31(extraout_var,bVar1);
      break;
    case 0xb:
    case 0xc:
    case 0xd:
    case 0x1b:
    case 0x29:
    case 0x2c:
      bVar1 = FUN_00425340(local_1c);
      local_18 = CONCAT31(extraout_var_00,bVar1);
      break;
    case 0xe:
    case 0x13:
      local_18 = FUN_00426305(local_1c,&local_b0);
      break;
    case 0xf:
    case 0x11:
      local_18 = FUN_00426a45(local_1c,&local_b0);
      break;
    case 0x10:
    case 0x12:
      local_18 = FUN_0042666f(local_1c,&local_b0);
      break;
    case 0x14:
      local_18 = FUN_00425a05((int)&local_b0);
      break;
    case 0x15:
    case 0x1a:
    case 0x2a:
    case 0x2b:
      local_18 = FUN_00426ee5(local_1c,(int)&local_b0);
      break;
    case 0x16:
    case 0x17:
    case 0x18:
      local_18 = FUN_004270d6();
      break;
    case 0x19:
      local_18 = FUN_0042712b(&local_b0);
      break;
    case 0x1c:
      local_18 = FUN_00425945((int)&local_b0);
      break;
    case 0x1d:
      local_18 = FUN_004261da((int)&local_b0);
      break;
    case 0x1e:
    case 0x1f:
      local_18 = FUN_0042546b(local_1c);
      break;
    case 0x20:
    case 0x24:
      local_18 = FUN_004257f4(local_1c,(int)&local_b0);
      break;
    default:
      FUN_00412fa0((uint *)s_Error_in_mnemonic_table_00455db8);
      break;
    case 0x25:
      local_18 = FUN_00425552((int)&local_b0);
      break;
    case 0x26:
      local_18 = FUN_00426dc3((int)&local_b0);
    }
    if (*(int *)(param_1 + 8) == 2) {
      local_40 = local_18;
      local_18 = 1;
    }
    else {
      local_40 = *(uint *)(param_1 + 8);
    }
    if (local_40 == 0) {
      if (((*PTR_DAT_0044f81c != '\0') && (local_1c != 0x19)) && (local_1c != 0x26)) {
        FUN_00413085((uint *)s_Too_many_fields_specified_for_in_00455e98);
        FUN_00413085((uint *)s_Possible_invalid_white_space_bet_00455ec4);
        local_18 = 0;
      }
    }
    else if (*PTR_DAT_0044f81c == '\0') {
      local_ac = local_ac | 0x200000;
    }
    else {
      if (((PTR_DAT_0044f824 != (undefined *)0x0) && (*PTR_DAT_0044f824 != '\0')) &&
         (*PTR_DAT_0044f824 != ';')) {
        FUN_00413085((uint *)s_Too_many_fields_specified_for_in_00455dd0);
        FUN_00413085((uint *)s_Possible_invalid_white_space_bet_00455dfc);
      }
      local_60[1] = 4;
      local_f0[1] = 4;
      local_38 = 4;
      local_cc = 4;
      FUN_0041b8bc();
      local_18 = FUN_00428040(&local_b0,local_40,&local_d0,&local_3c,local_f0,local_60);
      FUN_0041b8bc();
      if ((local_1c == 0x16) && (DAT_0045ea5c == '\0')) {
        FUN_004133a9((uint *)s_No_control_registers_accessed___u_00455e38);
      }
      if (((local_1c == 0x18) && (local_cc != 0)) && (local_38 != 0)) {
        FUN_004133a9((uint *)s_P_space_not_accessed___using_MOV_00455e6c);
      }
    }
    DAT_0044f95c = local_b0;
    if ((DAT_0045ea70 == '\0') || (DAT_0045eacc != '\0')) {
      if ((DAT_0045fc30 != 0) && (DAT_0045eacc == '\0')) {
        if ((local_18 != 0) && ((DAT_0045ebb8 & 0x100) != 0)) {
          FUN_0041b3c7(local_1c);
        }
        FUN_0041b43f(&local_b0);
      }
      if ((((DAT_0045ea90 != '\0') && (DAT_0044f794 == '\0')) && (*DAT_0045f8c0 < 0x40)) &&
         ((DAT_0045ebb4 & 0x200) != 0)) {
        DAT_0045f860 = PTR_DAT_0044f814;
        FUN_004133a9((uint *)s_Instruction_cannot_appear_in_int_00455f00);
      }
      local_10[0] = local_ac;
      if (local_70 == (uint *)0x0) {
        FUN_004232b6(local_10,(uint *)0x0,local_14);
      }
      else {
        FUN_004232b6(local_10,local_70,local_14);
        FUN_004398b5((undefined *)local_70);
        local_70 = (uint *)0x0;
      }
      if (local_b0 == 2) {
        if ((DAT_0045ebb8 & 1) != 0) {
          DAT_0045f860 = PTR_DAT_0044f814;
          FUN_00413085((uint *)s_Cannot_repeat_two_word_instructi_00455f38);
          local_18 = 0;
        }
        iVar2 = FUN_0041b685(0);
        if (iVar2 != 0) {
          local_18 = 0;
        }
        local_10[0] = local_a8;
        if (local_6c == (uint *)0x0) {
          FUN_004232b6(local_10,(uint *)0x0,local_14);
        }
        else {
          FUN_004232b6(local_10,local_6c,local_14);
          FUN_004398b5((undefined *)local_6c);
          local_6c = (uint *)0x0;
        }
      }
      if (DAT_0045ea10 != '\0') {
        FUN_0041e1e8(2,local_b0);
      }
      if (local_b4 != (undefined *)0x0) {
        FUN_004398b5(local_b4);
        local_b4 = (undefined *)0x0;
      }
      if (local_20 != (undefined *)0x0) {
        FUN_004398b5(local_20);
        local_20 = (undefined *)0x0;
      }
      if (local_d4 != (undefined *)0x0) {
        FUN_004398b5(local_d4);
        local_d4 = (undefined *)0x0;
      }
      if (local_44 != (undefined *)0x0) {
        FUN_004398b5(local_44);
      }
    }
  }
  else {
    FUN_00413085((uint *)s_Runtime_space_must_be_P_00455da0);
    local_18 = 0;
  }
  return local_18;
}


/* ==== FUN_00425340 @ 00425340 ==== */

bool __cdecl FUN_00425340(int param_1)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = true;
  DAT_0045f860 = PTR_DAT_0044f814;
  switch(param_1) {
  case 0xb:
    bVar2 = DAT_0044f9fc == 0;
    if (bVar2) {
      FUN_00413085((uint *)s_Unrecognized_mnemonic_00455f7c);
    }
    bVar2 = !bVar2;
    break;
  case 0xd:
  case 0x2c:
    bVar2 = (DAT_0045ebb8 & 1) != 0;
    if (bVar2) {
      FUN_00413085((uint *)s_Cannot_repeat_this_instruction_00455f5c);
    }
    bVar2 = !bVar2;
    if (param_1 == 0x2c) break;
  case 0xc:
    iVar1 = FUN_0041b685(0);
    if (iVar1 != 0) {
      bVar2 = false;
    }
    break;
  case 0x29:
    if (DAT_0044f9fc < 2) {
      FUN_00413085((uint *)s_Unrecognized_mnemonic_00455f94);
      bVar2 = false;
    }
  }
  DAT_0045f860 = PTR_DAT_0044f818;
  PTR_DAT_0044f820 = PTR_DAT_0044f81c;
  PTR_DAT_0044f81c = PTR_DAT_0044f818;
  PTR_DAT_0044f818 = &DAT_0045ec04;
  return bVar2;
}


/* ==== FUN_0042546b @ 0042546b ==== */

undefined4 __cdecl FUN_0042546b(int param_1)

{
  int iVar1;
  undefined4 local_8;
  
  local_8 = 1;
  DAT_0045f860 = PTR_DAT_0044f814;
  DAT_0045ebb4 = DAT_0045ebb4 | 0x200;
  if ((DAT_0045ebb8 & 1) == 0) {
    if ((DAT_0045ebb8 & (-(uint)(param_1 != 0x1f) & 0x80) + 0x40) != 0) {
      if (((DAT_0045eac8 == '\0') || (DAT_0045ea70 != '\0')) || (DAT_0045eb98 != 0)) {
        FUN_00413085((uint *)s_Instruction_cannot_appear_immedi_00455fcc);
        local_8 = 0;
      }
      else {
        FUN_0041bbb2();
      }
    }
  }
  else {
    FUN_00413085((uint *)s_Cannot_repeat_this_instruction_00455fac);
    local_8 = 0;
  }
  iVar1 = FUN_0041b685(0);
  if (iVar1 != 0) {
    local_8 = 0;
  }
  DAT_0045f860 = PTR_DAT_0044f818;
  PTR_DAT_0044f820 = PTR_DAT_0044f81c;
  PTR_DAT_0044f81c = PTR_DAT_0044f818;
  PTR_DAT_0044f818 = &DAT_0045ec04;
  return local_8;
}


/* ==== FUN_00425552 @ 00425552 ==== */

undefined4 __cdecl FUN_00425552(int param_1)

{
  int iVar1;
  int local_44 [5];
  int local_30;
  int local_24 [7];
  undefined *local_8;
  
  if (*DAT_0045f860 == '#') {
    iVar1 = FUN_004060d8(5,local_24,0,0,0,3);
    if ((iVar1 != 0) && (iVar1 = FUN_004060d8(0,local_44,0x13,0,0,0), iVar1 != 0)) {
      if (local_30 == 0x32) {
        DAT_0045ebb4 = DAT_0045ebb4 | 0x280;
      }
      else if (local_30 == 0x31) {
        DAT_0045ebb4 = DAT_0045ebb4 | 0x288;
        iVar1 = FUN_0041b685(2);
        if (iVar1 != 0) {
          if (local_8 != (undefined *)0x0) {
            FUN_004398b5(local_8);
          }
          return 0;
        }
      }
      FUN_00410950(param_1,(int)local_24,(int)local_44);
      return 1;
    }
  }
  else {
    FUN_00413085((uint *)s_Immediate_operand_required_00456010);
  }
  return 0;
}


/* ==== FUN_0042562d @ 0042562d ==== */

undefined4 __cdecl FUN_0042562d(int param_1)

{
  int iVar1;
  int local_48 [5];
  int local_34;
  int local_28 [5];
  int local_14;
  undefined4 local_8;
  
  local_8 = 0;
  if (*DAT_0045f860 == '#') {
    FUN_00425552(param_1);
  }
  else {
    local_8 = 1;
    if (*(int *)(param_1 + 4) == 0) {
      *(undefined4 *)(param_1 + 4) = 0x46;
    }
    else {
      *(undefined4 *)(param_1 + 4) = 0x42;
    }
    iVar1 = FUN_004060d8(1,local_28,0xb,0,0,0);
    if ((iVar1 == 0) || (iVar1 = FUN_004060d8(2,local_48,0x18,0,0,0), iVar1 == 0)) {
      local_8 = 0;
    }
    else {
      FUN_00427d58(1,local_14,(uint *)(param_1 + 4));
      FUN_00427d58(2,local_34,(uint *)(param_1 + 4));
    }
  }
  return local_8;
}


/* ==== FUN_004256e7 @ 004256e7 ==== */

undefined4 __cdecl FUN_004256e7(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_24 [5];
  int local_10;
  
  if ((param_1 == 2) && (DAT_0044f9fc < 2)) {
    DAT_0045f860 = PTR_DAT_0044f814;
    FUN_00413085((uint *)s_Unrecognized_mnemonic_0045602c);
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_004060d8(-(uint)(param_1 != 0x27) & 2,local_24,
                         (-(uint)(param_1 != 0x28) & 0xffffffe9) + 0x18,0,0,0);
    if (iVar2 == 0) {
      uVar1 = 0;
    }
    else {
      if (param_1 == 2) {
        *(uint *)(param_2 + 4) = *(uint *)(param_2 + 4) | (uint)(local_10 != 2);
      }
      else {
        FUN_00427d58(2,local_10,(uint *)(param_2 + 4));
      }
      uVar1 = 1;
    }
  }
  return uVar1;
}


/* ==== FUN_0042578d @ 0042578d ==== */

undefined4 __cdecl FUN_0042578d(int param_1)

{
  int iVar1;
  int local_44 [5];
  int local_30;
  int local_24 [5];
  int local_10;
  
  iVar1 = FUN_004060d8(1,local_24,1,0,0,0);
  if ((iVar1 != 0) && (iVar1 = FUN_004060d8(2,local_44,(local_10 == 2) + 0xd,0,0,0), iVar1 != 0)) {
    FUN_00427d58(2,local_30,(uint *)(param_1 + 4));
    return 1;
  }
  return 0;
}


/* ==== FUN_004257f4 @ 004257f4 ==== */

undefined4 __cdecl FUN_004257f4(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_44 [5];
  int local_30;
  int local_24 [5];
  int local_10;
  
  iVar1 = FUN_004060d8(1,local_24,(param_1 != 0x24) + 10,0,0,0);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    FUN_00427d58(1,local_10,(uint *)(param_2 + 4));
    iVar1 = FUN_004060d8(2,local_44,(-(uint)(param_1 != 0x24) & 0x17) + 1,0,0,0);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      FUN_00427d58(2,local_30,(uint *)(param_2 + 4));
      uVar2 = 1;
    }
  }
  return uVar2;
}


/* ==== FUN_00425883 @ 00425883 ==== */

undefined4 __cdecl FUN_00425883(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_50;
  int local_48 [5];
  int local_34;
  int local_28 [5];
  int local_14;
  uint local_8;
  
  iVar1 = FUN_004060d8(1,local_28,(-(uint)(param_1 != 0x22) & 0xfffffffa) + 0x15,0,0,0);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    FUN_00427d58(1,local_14,(uint *)(param_2 + 4));
    local_8 = -(uint)(param_1 != 7) & 2;
    if (local_14 == 2) {
      local_50 = 0xe;
    }
    else {
      local_50 = (-(uint)(local_14 != 3) & 0xfffffff4) + 0xd;
    }
    iVar1 = FUN_004060d8(local_8,local_48,local_50,0,0,0);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      FUN_00427d58(2,local_34,(uint *)(param_2 + 4));
      uVar2 = 1;
    }
  }
  return uVar2;
}


/* ==== FUN_00425945 @ 00425945 ==== */

undefined4 __cdecl FUN_00425945(int param_1)

{
  int iVar1;
  int local_48 [8];
  int local_28 [5];
  char local_14;
  uint local_8;
  
  iVar1 = FUN_004060d8(1,local_28,0x10,0,0,0);
  if ((iVar1 != 0) && (iVar1 = FUN_004060d8(0,local_48,1,0,0,0), iVar1 != 0)) {
    local_8 = 1 << (local_14 - 0xeU & 0x1f);
    if (((DAT_0045f944 & local_8) != 0) && (*DAT_0045f8c0 == DAT_0045f94c + DAT_0044f95c)) {
      if (((DAT_0045eac8 == '\0') || (DAT_0045ea70 != '\0')) || (DAT_0045eb98 != 0)) {
        FUN_00413085((uint *)s_Contents_of_register_written_in_p_00456044);
      }
      else {
        FUN_0041bbb2();
      }
    }
    FUN_00410acf(param_1,local_28,(int)local_48);
    return 1;
  }
  return 0;
}


/* ==== FUN_00425a05 @ 00425a05 ==== */

undefined4 __cdecl FUN_00425a05(int param_1)

{
  int iVar1;
  int local_44 [8];
  int local_24 [8];
  
  iVar1 = FUN_004060d8(1,local_24,0,3,0,0);
  if ((iVar1 != 0) && (iVar1 = FUN_004060d8(2,local_44,0x14,0,0,0), iVar1 != 0)) {
    FUN_00412e4f(param_1,local_24,(int)local_44);
    return 1;
  }
  return 0;
}


/* ==== FUN_00425a60 @ 00425a60 ==== */

undefined4 __cdecl FUN_00425a60(int param_1)

{
  int iVar1;
  int local_44 [8];
  int local_24 [8];
  
  iVar1 = FUN_004060d8(1,local_24,0xb,0,0,0);
  if ((iVar1 != 0) && (iVar1 = FUN_004060d8(0,local_44,1,0,0,0), iVar1 != 0)) {
    FUN_004109d7(param_1,(int)local_24,(int)local_44);
    return 1;
  }
  return 0;
}


/* ==== FUN_00425abb @ 00425abb ==== */

int __cdecl FUN_00425abb(int param_1,undefined4 *param_2)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  undefined4 local_4c;
  int local_48;
  int local_44;
  int local_3c;
  int local_34;
  int local_28 [7];
  undefined *local_c;
  int local_8;
  
  local_8 = 1;
  iVar2 = FUN_004060d8(5,local_28,0,0,0,4);
  if (iVar2 == 0) {
    local_8 = 0;
    FUN_0043bc1b();
  }
  iVar2 = FUN_00439c56((int)&local_48,(-(uint)(DAT_0044f9fc == 0) & 0xfffffffe) + 7);
  if (iVar2 == 0) {
    if (local_c != (undefined *)0x0) {
      FUN_004398b5(local_c);
    }
    local_8 = 0;
  }
  else if (local_44 == 4) {
    iVar2 = FUN_004060d8(0,&local_48,0x11,0,0,0);
    if (iVar2 == 0) {
      if (local_c != (undefined *)0x0) {
        FUN_004398b5(local_c);
      }
      local_8 = 0;
    }
    else {
      if (param_1 == 6) {
        if ((local_34 == 0x2e) && (iVar2 = FUN_0041b685(2), iVar2 != 0)) {
          local_8 = 0;
        }
      }
      else {
        bVar1 = FUN_0042b12c(local_34);
        if (CONCAT31(extraout_var,bVar1) == 0) {
          local_8 = 0;
        }
      }
      if (local_8 == 0) {
        if (local_c != (undefined *)0x0) {
          FUN_004398b5(local_c);
        }
        local_8 = 0;
      }
      else {
        FUN_004117a2((int)param_2,(int)local_28,(int)&local_48);
      }
    }
  }
  else {
    iVar2 = FUN_004060d8(0,&local_48,0,1,6,0);
    if (iVar2 == 0) {
      if ((local_3c == 0x2000000) || (local_3c == 0x4000000)) {
        local_4c = 1;
      }
      else {
        local_4c = 2;
      }
      *param_2 = local_4c;
      if (local_c != (undefined *)0x0) {
        FUN_004398b5(local_c);
      }
      local_8 = 0;
    }
    else if (local_8 == 0) {
      *param_2 = 2;
      if (local_c != (undefined *)0x0) {
        FUN_004398b5(local_c);
      }
      local_8 = 0;
    }
    else {
      switch(local_48) {
      case 7:
      case 8:
      case 0xe:
        DAT_0045f928 = DAT_0045f928 + 2;
      default:
        FUN_004116eb(param_2,(int)local_28,&local_48);
        break;
      case 0x10:
        FUN_004117ff((int)param_2,(int)local_28,(int)&local_48);
        break;
      case 0x11:
        FUN_004119e4((int)param_2,(int)local_28,(int)&local_48);
      }
    }
  }
  return local_8;
}


/* ==== FUN_00425d15 @ 00425d15 ==== */

int __cdecl FUN_00425d15(undefined4 *param_1)

{
  int iVar1;
  uint *puVar2;
  int local_48;
  int local_44;
  int local_30;
  int local_28;
  int local_24;
  int local_14;
  undefined *local_c;
  int local_8;
  
  local_8 = 1;
  DAT_0045f860 = PTR_DAT_0044f814;
  DAT_0045ebb4 = DAT_0045ebb4 | 0x200;
  if ((DAT_0045ebb8 & 1) == 0) {
    if ((DAT_0045ebb8 & 4) != 0) {
      if (((DAT_0045eac8 == '\0') || (DAT_0045ea70 != '\0')) || (DAT_0045eb98 != 0)) {
        FUN_00413085((uint *)s_Instruction_cannot_appear_immedi_004560a8);
        local_8 = 0;
      }
      else {
        FUN_0041bbb2();
      }
    }
  }
  else {
    FUN_00413085((uint *)s_Cannot_repeat_this_instruction_00456088);
    DAT_0045ebb8 = DAT_0045ebb8 & 0xfffffffe;
    local_8 = 0;
  }
  iVar1 = FUN_0041b685(2);
  if (iVar1 != 0) {
    local_8 = 0;
  }
  DAT_0045f860 = PTR_DAT_0044f818;
  *param_1 = 2;
  local_44 = 4;
  iVar1 = FUN_00439c56((int)&local_28,7);
  if (iVar1 == 0) {
    return 0;
  }
  if (local_24 == 4) {
    iVar1 = FUN_004060d8(1,&local_28,0x11,0,0,2);
    if (iVar1 == 0) {
      local_8 = 0;
      FUN_0043bc1b();
    }
    if ((local_28 == 1) && (local_14 == 0x2e)) {
      FUN_00413085((uint *)s_Illegal_use_of_SSH_as_loop_count_004560ec);
      if (local_c != (undefined *)0x0) {
        FUN_004398b5(local_c);
      }
      return 0;
    }
    iVar1 = FUN_004060d8(4,&local_48,0,0,1,0);
    if (iVar1 == 0) {
      if (local_c != (undefined *)0x0) {
        FUN_004398b5(local_c);
      }
      return 0;
    }
    if ((DAT_0044f7a4 != '\0') && (iVar1 = FUN_0043baf1(local_44,0), iVar1 == 0xa2c2a)) {
      FUN_004133a9((uint *)s_Absolute_address_involves_incomp_00456118);
    }
    if (local_8 == 0) {
      if (local_c != (undefined *)0x0) {
        FUN_004398b5(local_c);
      }
      return 0;
    }
    if (local_28 == 10) {
      FUN_004113fc(param_1,(int)&local_28,&local_48);
    }
    else {
      FUN_004113d5(param_1,(int)&local_28,&local_48);
    }
  }
  else {
    iVar1 = FUN_004060d8(1,&local_28,0,1,4,0);
    if (iVar1 == 0) {
      local_8 = 0;
      FUN_0043bc1b();
    }
    iVar1 = FUN_004060d8(4,&local_48,0,0,1,0);
    if (iVar1 == 0) {
      if (local_c != (undefined *)0x0) {
        FUN_004398b5(local_c);
      }
      return 0;
    }
    if ((DAT_0044f7a4 != '\0') && (iVar1 = FUN_0043baf1(local_44,0), iVar1 == 0xa2c2a)) {
      FUN_004133a9((uint *)s_Absolute_address_involves_incomp_00456150);
    }
    if (local_8 == 0) {
      if (local_c != (undefined *)0x0) {
        FUN_004398b5(local_c);
      }
      return 0;
    }
    if (local_28 == 0x10) {
      FUN_004113ae(param_1,(int)&local_28,&local_48);
    }
    else {
      FUN_004112b9(param_1,&local_28,&local_48);
    }
  }
  if (((DAT_0045f8fc == 2) && (DAT_0045ea70 == '\0')) &&
     (local_30 != *(int *)(PTR_DAT_0044f978 + 8))) {
    FUN_00413085((uint *)s_DO_loop_address_must_be_in_curre_00456188);
    local_8 = 0;
  }
  else if ((DAT_0045f8fc == 2) && (DAT_0045ea70 == '\0')) {
    DAT_0045f860 = (undefined *)0x0;
    if (*DAT_0045f8c0 + 1U < (uint)param_1[2]) {
      if ((DAT_0045fc30 == (uint *)0x0) || ((uint)param_1[2] < *DAT_0045fc30)) {
        puVar2 = (uint *)FUN_00439857(0x10);
        *puVar2 = param_1[2];
        puVar2[1] = 0;
        puVar2[2] = 0;
        puVar2[3] = (uint)DAT_0045fc30;
        DAT_0045ebb4 = DAT_0045ebb4 | 0x100;
        DAT_0045fc30 = puVar2;
      }
      else {
        FUN_004133a9((uint *)s_Improper_nesting_of_DO_loops_004561dc);
        local_8 = 0;
      }
    }
    else {
      FUN_00413085((uint *)s_Negative_or_empty_DO_loop_not_al_004561b4);
      local_8 = 0;
    }
  }
  return local_8;
}


/* ==== FUN_00426106 @ 00426106 ==== */

bool FUN_00426106(void)

{
  bool local_8;
  
  DAT_0045f860 = PTR_DAT_0044f814;
  DAT_0045ebb4 = DAT_0045ebb4 | 0x200;
  if (DAT_0045fc30 == 0) {
    FUN_004133a9((uint *)s_ENDDO_instruction_not_inside_DO_l_004561fc);
  }
  local_8 = (DAT_0045ebb8 & 1) != 0;
  if (local_8) {
    FUN_00413085((uint *)s_Cannot_repeat_this_instruction_00456224);
  }
  local_8 = !local_8;
  if ((DAT_0045ebb8 & 8) != 0) {
    if (((DAT_0045eac8 == '\0') || (DAT_0045ea70 != '\0')) || (DAT_0045eb98 != 0)) {
      FUN_00413085((uint *)s_Instruction_cannot_appear_immedi_00456244);
      local_8 = false;
    }
    else {
      FUN_0041bbb2();
    }
  }
  DAT_0045f860 = PTR_DAT_0044f818;
  PTR_DAT_0044f820 = PTR_DAT_0044f81c;
  PTR_DAT_0044f81c = PTR_DAT_0044f818;
  PTR_DAT_0044f818 = &DAT_0045ec04;
  return local_8;
}


/* ==== FUN_004261da @ 004261da ==== */

uint __cdecl FUN_004261da(int param_1)

{
  int iVar1;
  bool bVar2;
  int local_28;
  int local_24;
  uint local_8;
  
  local_8 = 1;
  DAT_0045f860 = PTR_DAT_0044f814;
  DAT_0045ebb4 = DAT_0045ebb4 | 1;
  bVar2 = (DAT_0045ebb8 & 1) != 0;
  if (bVar2) {
    FUN_00413085((uint *)s_Cannot_repeat_this_instruction_00456288);
  }
  local_8 = (uint)!bVar2;
  iVar1 = FUN_0041b685(0);
  if (iVar1 != 0) {
    local_8 = 0;
  }
  DAT_0045f860 = PTR_DAT_0044f818;
  iVar1 = FUN_00439c56((int)&local_28,7);
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else if (local_24 == 4) {
    iVar1 = FUN_004060d8(0,&local_28,0x11,0,0,2);
    if (iVar1 == 0) {
      local_8 = 0;
    }
    else if (local_28 == 1) {
      FUN_00410d51(param_1,(int)&local_28);
    }
    else if (local_28 == 10) {
      FUN_0041118f(param_1,(int)&local_28);
    }
  }
  else {
    iVar1 = FUN_004060d8(0,&local_28,0,1,4,0);
    if (iVar1 == 0) {
      local_8 = 0;
    }
    else if (local_28 == 0x10) {
      FUN_00410d0f(param_1,(int)&local_28);
    }
    else {
      FUN_00410bcb(param_1,&local_28);
    }
  }
  return local_8;
}


/* ==== FUN_00426305 @ 00426305 ==== */

undefined4 __cdecl FUN_00426305(int param_1,int *param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined3 extraout_var;
  uint uVar3;
  char *dst;
  int *piVar4;
  int *piVar5;
  uint *local_84;
  int local_7c [17];
  uint *local_38;
  int local_2c;
  int local_28;
  int local_20;
  char local_18;
  char *local_10;
  char *local_c;
  undefined4 local_8;
  
  local_8 = 1;
  DAT_0045f860 = PTR_DAT_0044f814;
  iVar2 = FUN_0041b685(0);
  if (iVar2 != 0) {
    local_8 = 0;
  }
  if ((DAT_0045ebb8 & 1) != 0) {
    FUN_00413085((uint *)s_Cannot_repeat_this_instruction_004562a8);
    DAT_0045ebb8 = DAT_0045ebb8 & 0xfffffffe;
    local_8 = 0;
  }
  DAT_0045f860 = PTR_DAT_0044f818;
  local_c = PTR_DAT_0044f818;
  local_28 = 4;
  iVar2 = FUN_004060d8(0,&local_2c,0x10,1,5,0);
  if (iVar2 == 0) {
    *param_2 = (local_20 != 0x2000000) + 1;
    local_8 = 0;
  }
  else {
    if ((DAT_0044f7a4 != '\0') && (iVar2 = FUN_0043baf1(local_28,0), iVar2 == 0xa2c2a)) {
      FUN_004133a9((uint *)s_Absolute_address_involves_incomp_004562c8);
    }
    if (local_2c == 1) {
      local_2c = 2;
      FUN_004069eb(local_18,2);
    }
    if ((local_2c == 0xf) || (local_2c == 0xe)) {
      DAT_0045f868 = (uint *)FUN_00433cb0(local_c);
      if (DAT_0045f868 == (uint *)0x0) {
        if (local_2c == 0xf) {
          if (param_1 == 0x13) {
            FUN_00411423((int)param_2,(int)&local_2c);
          }
          else {
            FUN_00411501((int)param_2,(int)&local_2c);
          }
        }
        else {
          DAT_0045f928 = DAT_0045f928 + 2;
          if (param_1 == 0x13) {
            FUN_00411457(param_2,&local_2c);
          }
          else {
            FUN_00411535(param_2,&local_2c);
          }
        }
      }
      else if (DAT_0045f8fc == 1) {
        if (local_10 != (char *)0x0) {
          FUN_004398b5(local_10);
          local_10 = (char *)0x0;
        }
        FUN_00434023(DAT_0045f868,0xc,0,2);
      }
      else if (local_10 == (char *)0x0) {
        uVar1 = FUN_004342fb();
        if (CONCAT31(extraout_var,uVar1) == 0) {
          local_2c = 0xf;
          if (param_1 == 0x13) {
            FUN_00411423((int)param_2,(int)&local_2c);
          }
          else {
            FUN_00411501((int)param_2,(int)&local_2c);
          }
        }
        else {
          DAT_0045f928 = DAT_0045f928 + 2;
          if (param_1 == 0x13) {
            FUN_00411457(param_2,&local_2c);
          }
          else {
            FUN_00411535(param_2,&local_2c);
          }
        }
      }
      else {
        piVar4 = param_2;
        piVar5 = local_7c;
        for (iVar2 = 0x14; iVar2 != 0; iVar2 = iVar2 + -1) {
          *piVar5 = *piVar4;
          piVar4 = piVar4 + 1;
          piVar5 = piVar5 + 1;
        }
        uVar3 = strlen(local_10);
        dst = (char *)FUN_00439857(uVar3 + 1);
        strcpy(dst,local_10);
        local_2c = 0xf;
        if (param_1 == 0x13) {
          FUN_00411423((int)param_2,(int)&local_2c);
        }
        else {
          FUN_00411501((int)param_2,(int)&local_2c);
        }
        local_2c = 0xe;
        local_10 = dst;
        if (param_1 == 0x13) {
          FUN_00411457(local_7c,&local_2c);
        }
        else {
          FUN_00411535(local_7c,&local_2c);
        }
        if (DAT_0045eb38 == '\0') {
          local_84 = DAT_0045f868;
        }
        else {
          local_84 = local_38;
        }
        FUN_00434be7(local_84,2,0xc,0,param_2,local_7c);
        *param_2 = 1;
      }
    }
    else {
      if ((local_2c == 7) || (local_2c == 8)) {
        DAT_0045f928 = DAT_0045f928 + 2;
      }
      if (param_1 == 0x13) {
        FUN_00411457(param_2,&local_2c);
      }
      else {
        FUN_00411535(param_2,&local_2c);
      }
    }
  }
  return local_8;
}


/* ==== FUN_0042666f @ 0042666f ==== */

undefined4 __cdecl FUN_0042666f(int param_1,int *param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined3 extraout_var;
  uint uVar3;
  char *dst;
  int *piVar4;
  int *piVar5;
  uint *local_84;
  int local_7c [17];
  uint *local_38;
  int local_2c;
  int local_28;
  int local_20;
  int local_1c;
  char local_18;
  char *local_10;
  char *local_c;
  undefined4 local_8;
  
  local_8 = 1;
  DAT_0045f860 = PTR_DAT_0044f814;
  iVar2 = FUN_0041b685(0);
  if (iVar2 != 0) {
    local_8 = 0;
  }
  if ((DAT_0045ebb8 & 1) != 0) {
    FUN_00413085((uint *)s_Cannot_repeat_this_instruction_00456300);
    DAT_0045ebb8 = DAT_0045ebb8 & 0xfffffffe;
    local_8 = 0;
  }
  DAT_0045f860 = PTR_DAT_0044f818;
  local_c = PTR_DAT_0044f818;
  local_28 = 4;
  iVar2 = FUN_004060d8(4,&local_2c,0x10,1,5,0);
  if (iVar2 == 0) {
    *param_2 = (local_20 != 0x2000000) + 1;
    local_8 = 0;
  }
  else {
    if ((DAT_0044f7a4 != '\0') && (iVar2 = FUN_0043baf1(local_28,0), iVar2 == 0xa2c2a)) {
      FUN_004133a9((uint *)s_Absolute_address_involves_incomp_00456320);
    }
    if (local_2c == 1) {
      local_2c = 2;
      FUN_004069eb(local_18,2);
    }
    if ((local_2c == 0xf) || (local_2c == 0xe)) {
      DAT_0045f868 = (uint *)FUN_00433cb0(local_c);
      if (DAT_0045f868 == (uint *)0x0) {
        if (((DAT_0045f8fc == 2) && (DAT_0045fc30 != (int *)0x0)) && (*DAT_0045fc30 == local_1c)) {
          FUN_00413085((uint *)s_Subroutine_jump_to_loop_address_n_00456358);
          local_8 = 0;
        }
        if (local_2c == 0xf) {
          if (param_1 == 0x12) {
            FUN_00411423((int)param_2,(int)&local_2c);
          }
          else {
            FUN_00411501((int)param_2,(int)&local_2c);
          }
        }
        else {
          DAT_0045f928 = DAT_0045f928 + 2;
          if (param_1 == 0x12) {
            FUN_00411457(param_2,&local_2c);
          }
          else {
            FUN_00411535(param_2,&local_2c);
          }
        }
      }
      else if (DAT_0045f8fc == 1) {
        if (local_10 != (char *)0x0) {
          FUN_004398b5(local_10);
          local_10 = (char *)0x0;
        }
        FUN_00434023(DAT_0045f868,0xc,0,2);
      }
      else if (local_10 == (char *)0x0) {
        if (((DAT_0045f8fc == 2) && (DAT_0045fc30 != (int *)0x0)) && (*DAT_0045fc30 == local_1c)) {
          FUN_00413085((uint *)s_Subroutine_jump_to_loop_address_n_00456384);
          local_8 = 0;
        }
        uVar1 = FUN_004342fb();
        if (CONCAT31(extraout_var,uVar1) == 0) {
          local_2c = 0xf;
          if (param_1 == 0x12) {
            FUN_00411423((int)param_2,(int)&local_2c);
          }
          else {
            FUN_00411501((int)param_2,(int)&local_2c);
          }
        }
        else {
          DAT_0045f928 = DAT_0045f928 + 2;
          if (param_1 == 0x12) {
            FUN_00411457(param_2,&local_2c);
          }
          else {
            FUN_00411535(param_2,&local_2c);
          }
        }
      }
      else {
        piVar4 = param_2;
        piVar5 = local_7c;
        for (iVar2 = 0x14; iVar2 != 0; iVar2 = iVar2 + -1) {
          *piVar5 = *piVar4;
          piVar4 = piVar4 + 1;
          piVar5 = piVar5 + 1;
        }
        uVar3 = strlen(local_10);
        dst = (char *)FUN_00439857(uVar3 + 1);
        strcpy(dst,local_10);
        local_2c = 0xf;
        if (param_1 == 0x12) {
          FUN_00411423((int)param_2,(int)&local_2c);
        }
        else {
          FUN_00411501((int)param_2,(int)&local_2c);
        }
        local_2c = 0xe;
        local_10 = dst;
        if (param_1 == 0x12) {
          FUN_00411457(local_7c,&local_2c);
        }
        else {
          FUN_00411535(local_7c,&local_2c);
        }
        if (DAT_0045eb38 == '\0') {
          local_84 = DAT_0045f868;
        }
        else {
          local_84 = local_38;
        }
        FUN_00434be7(local_84,2,0xc,0,param_2,local_7c);
        *param_2 = 1;
      }
    }
    else {
      if ((local_2c == 7) || (local_2c == 8)) {
        DAT_0045f928 = DAT_0045f928 + 2;
      }
      if (param_1 == 0x12) {
        FUN_00411457(param_2,&local_2c);
      }
      else {
        FUN_00411535(param_2,&local_2c);
      }
    }
  }
  return local_8;
}


/* ==== FUN_00426a45 @ 00426a45 ==== */

uint __cdecl FUN_00426a45(int param_1,undefined4 *param_2)

{
  int iVar1;
  bool bVar2;
  int local_68;
  int local_64;
  int local_58;
  undefined *local_4c;
  int local_48;
  int local_44;
  int local_34;
  undefined *local_2c;
  int local_28 [7];
  undefined *local_c;
  uint local_8;
  
  local_8 = 1;
  DAT_0045f860 = PTR_DAT_0044f814;
  bVar2 = (DAT_0045ebb8 & 1) != 0;
  if (bVar2) {
    FUN_00413085((uint *)s_Cannot_repeat_this_instruction_004563b0);
    DAT_0045ebb8 = DAT_0045ebb8 & 0xfffffffe;
  }
  local_8 = (uint)!bVar2;
  DAT_0045f860 = PTR_DAT_0044f818;
  *param_2 = 2;
  iVar1 = FUN_004060d8(5,local_28,0,0,0,4);
  if (iVar1 == 0) {
    local_8 = 0;
    FUN_0043bc1b();
  }
  iVar1 = FUN_00439c56((int)&local_48,(-(uint)(DAT_0044f9fc == 0) & 0xfffffffe) + 7);
  if (iVar1 == 0) {
    if (local_c != (undefined *)0x0) {
      FUN_004398b5(local_c);
    }
    local_8 = 0;
  }
  else {
    if (local_44 == 4) {
      iVar1 = FUN_004060d8(1,&local_48,0x11,0,0,0);
      if (iVar1 == 0) {
        local_8 = 0;
        FUN_0043bc1b();
      }
      if ((local_34 == 0x2e) && (iVar1 = FUN_0041b685(2), iVar1 != 0)) {
        local_8 = 0;
      }
    }
    else {
      iVar1 = FUN_004060d8(1,&local_48,0,1,7,0);
      if (iVar1 == 0) {
        local_8 = 0;
        FUN_0043bc1b();
      }
    }
    local_64 = 4;
    iVar1 = FUN_004060d8(0,&local_68,0,0,1,0);
    if (iVar1 == 0) {
      if (local_c != (undefined *)0x0) {
        FUN_004398b5(local_c);
        local_c = (undefined *)0x0;
      }
      if (local_2c != (undefined *)0x0) {
        FUN_004398b5(local_2c);
      }
      local_8 = 0;
    }
    else {
      if ((DAT_0044f7a4 != '\0') && (iVar1 = FUN_0043baf1(local_64,0), iVar1 == 0xa2c2a)) {
        FUN_004133a9((uint *)s_Absolute_address_involves_incomp_004563d0);
      }
      if (local_8 == 0) {
        if (local_c != (undefined *)0x0) {
          FUN_004398b5(local_c);
          local_c = (undefined *)0x0;
        }
        if (local_2c != (undefined *)0x0) {
          FUN_004398b5(local_2c);
          local_2c = (undefined *)0x0;
        }
        if (local_4c != (undefined *)0x0) {
          FUN_004398b5(local_4c);
        }
        local_8 = 0;
      }
      else if ((((DAT_0045f8fc == 2) && (param_1 == 0x11)) && (DAT_0045fc30 != (int *)0x0)) &&
              (*DAT_0045fc30 == local_58)) {
        FUN_00413085((uint *)s_Subroutine_jump_to_loop_address_n_00456408);
        if (local_c != (undefined *)0x0) {
          FUN_004398b5(local_c);
          local_c = (undefined *)0x0;
        }
        if (local_2c != (undefined *)0x0) {
          FUN_004398b5(local_2c);
          local_2c = (undefined *)0x0;
        }
        if (local_4c != (undefined *)0x0) {
          FUN_004398b5(local_4c);
        }
        local_8 = 0;
      }
      else {
        if (((local_34 == 0x2e) || (local_34 == 0x2f)) && ((DAT_0045ebb8 & 0x10) != 0)) {
          if (((DAT_0045eac8 == '\0') || (DAT_0045ea70 != '\0')) || (DAT_0045eb98 != 0)) {
            FUN_00413085((uint *)s_Jump_based_on_SSH_or_SSL_cannot_f_00456434);
          }
          else {
            FUN_0041bbb2();
          }
        }
        if (local_48 == 1) {
          FUN_00411a43(param_2,(int)local_28,(int)&local_48,&local_68);
        }
        else if (local_48 == 0x10) {
          FUN_00411ab2(param_2,(int)local_28,(int)&local_48,&local_68);
        }
        else if (local_48 == 0x11) {
          FUN_00411add(param_2,(int)local_28,(int)&local_48,&local_68);
        }
        else {
          FUN_00411a18(param_2,(int)local_28,&local_48,&local_68);
          if ((6 < local_48) && (local_48 < 9)) {
            DAT_0045f928 = DAT_0045f928 + 2;
          }
        }
      }
    }
  }
  return local_8;
}


/* ==== FUN_00426dc3 @ 00426dc3 ==== */

undefined4 __cdecl FUN_00426dc3(int param_1)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  int local_90;
  int local_8c [8];
  int local_6c [8];
  int local_4c;
  int local_48 [8];
  int local_28 [5];
  int local_14;
  undefined4 local_8;
  
  local_8 = 1;
  iVar2 = FUN_004060d8(1,local_28,0xf,0,0,0);
  if (iVar2 == 0) {
    local_8 = 0;
  }
  else {
    if (local_14 == 2) {
      local_90 = 0xe;
    }
    else {
      local_90 = (-(uint)(local_14 != 3) & 0xfffffff4) + 0xd;
    }
    local_4c = local_90;
    iVar2 = FUN_004060d8(0,local_48,local_90,0,0,0);
    if (iVar2 == 0) {
      local_8 = 0;
    }
    else if (*PTR_DAT_0044f81c == '\0') {
      FUN_00411697(param_1,(int)local_28,(int)local_48);
    }
    else {
      bVar1 = FUN_0043bccb();
      if (CONCAT31(extraout_var,bVar1) == 0) {
        local_8 = 0;
      }
      else {
        DAT_0045f860 = PTR_DAT_0044f81c;
        iVar2 = FUN_004060d8(1,local_6c,0x10,0,0,0);
        if (iVar2 == 0) {
          local_8 = 0;
        }
        else {
          iVar2 = FUN_004060d8(2,local_8c,0x10,0,0,0);
          if (iVar2 != 0) {
            FUN_004115dc(param_1,(int)local_28,(int)local_48,local_6c,local_8c);
          }
        }
      }
    }
  }
  return local_8;
}


/* ==== FUN_00426ee5 @ 00426ee5 ==== */

undefined4 __cdecl FUN_00426ee5(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_68 [5];
  int local_54;
  int local_48 [4];
  int local_38;
  int local_34;
  int local_30;
  undefined *local_2c;
  int local_28 [5];
  undefined4 local_14;
  int local_8;
  
  local_8 = 0;
  if (*DAT_0045f860 == '+') {
    DAT_0045f860 = DAT_0045f860 + 1;
  }
  else if (*DAT_0045f860 == '-') {
    DAT_0045f860 = DAT_0045f860 + 1;
    local_8 = 1;
  }
  iVar1 = FUN_004060d8(1,local_28,0xb,0,0,0);
  if (((iVar1 == 0) || (iVar1 = FUN_004060d8(5,local_48,0xb,0,0,4), iVar1 == 0)) ||
     (iVar1 = FUN_004060d8(2,local_68,1,0,0,0), iVar1 == 0)) {
    uVar2 = 0;
  }
  else if (local_48[0] == 1) {
    if (local_8 != 0) {
      *(uint *)(param_2 + 4) = *(uint *)(param_2 + 4) | 4;
    }
    FUN_00427e5d(local_14,local_34,local_54,(uint *)(param_2 + 4));
    uVar2 = 1;
  }
  else if ((local_38 == 0) && ((DAT_0044f790 == '\0' || (-1 < local_30)))) {
    FUN_00413085((uint *)s_Invalid_shift_amount_00456468);
    if (local_2c != (undefined *)0x0) {
      FUN_004398b5(local_2c);
    }
    uVar2 = 0;
  }
  else {
    switch(param_1) {
    case 0x15:
      *(undefined4 *)(param_2 + 4) = 0x100c2;
      break;
    default:
      FUN_00412fa0((uint *)s_Invalid_instruction_class_00456480);
      break;
    case 0x1a:
      *(undefined4 *)(param_2 + 4) = 0x100c0;
      break;
    case 0x2a:
      *(undefined4 *)(param_2 + 4) = 0x100c3;
      break;
    case 0x2b:
      *(undefined4 *)(param_2 + 4) = 0x100c1;
    }
    if (local_8 != 0) {
      *(uint *)(param_2 + 4) = *(uint *)(param_2 + 4) | 4;
    }
    FUN_00412ecb(param_2,(int)local_28,(int)local_48,(int)local_68);
    uVar2 = 0;
  }
  return uVar2;
}


/* ==== FUN_004270d6 @ 004270d6 ==== */

undefined4 FUN_004270d6(void)

{
  undefined *puVar1;
  bool bVar2;
  undefined3 extraout_var;
  undefined4 uVar3;
  
  bVar2 = FUN_0043bccb();
  puVar1 = PTR_DAT_0044f818;
  if (CONCAT31(extraout_var,bVar2) == 0) {
    uVar3 = 0;
  }
  else {
    PTR_DAT_0044f820 = PTR_DAT_0044f81c;
    PTR_DAT_0044f81c = PTR_DAT_0044f818;
    PTR_DAT_0044f818 = &DAT_0045ec04;
    if (*puVar1 == '\0') {
      FUN_00413085((uint *)s_Not_enough_fields_specified_for_i_0045649c);
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
  }
  return uVar3;
}


/* ==== FUN_0042712b @ 0042712b ==== */

undefined4 __cdecl FUN_0042712b(undefined4 *param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  int local_54;
  int local_50;
  int local_48;
  uint local_44;
  int local_40;
  undefined *local_38;
  int local_34;
  int local_30;
  int local_28;
  uint local_24;
  int local_20;
  undefined *local_18;
  uint *local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  puVar1 = PTR_DAT_0044f818;
  local_8 = 0;
  local_10 = 5;
  if (*PTR_DAT_0044f81c == '\0') {
    PTR_DAT_0044f820 = PTR_DAT_0044f81c;
    PTR_DAT_0044f81c = PTR_DAT_0044f818;
    PTR_DAT_0044f818 = &DAT_0045ec04;
    if (*puVar1 == '\0') {
      FUN_00413085((uint *)s_Not_enough_fields_specified_for_i_00456530);
      uVar2 = 0;
    }
    else {
      local_14 = (uint *)s_I_O_short_addressing_must_be_use_0045655c;
      iVar3 = FUN_00439c56((int)&local_34,9);
      if (iVar3 == 0) {
        uVar2 = 0;
      }
      else {
        if (local_30 == 0) {
          local_14 = (uint *)s_I_O_short_addressing_must_be_use_004565dc;
          local_c = FUN_004060d8(1,&local_34,0,1,1,0);
        }
        else if (local_30 == 4) {
          local_14 = (uint *)s_I_O_short_addressing_must_be_use_004565a0;
          local_c = FUN_004060d8(1,&local_34,0x11,0,0,1);
        }
        else {
          local_10 = 9;
          local_c = FUN_004060d8(1,&local_34,0,1,8,0);
        }
        if (local_c == 0) {
          *param_1 = 2;
          local_8 = 1;
          FUN_0043bc1b();
        }
        iVar3 = FUN_00439c56((int)&local_54,local_10);
        if (iVar3 == 0) {
          uVar2 = 0;
        }
        else if ((((local_30 == 1) || (local_30 == 2)) || (local_50 == 1)) || (local_50 == 2)) {
          if (local_50 == 0) {
            local_14 = (uint *)s_I_O_short_addressing_must_be_use_0045668c;
            local_c = FUN_004060d8(2,&local_54,0,1,1,0);
          }
          else if (local_50 == 4) {
            local_14 = (uint *)s_I_O_short_addressing_must_be_use_00456654;
            local_c = FUN_004060d8(2,&local_54,0x11,0,0,0);
          }
          else {
            local_c = FUN_004060d8(2,&local_54,0,1,8,0);
          }
          if (local_c == 0) {
            *param_1 = 2;
            if (local_18 != (undefined *)0x0) {
              FUN_004398b5(local_18);
              local_18 = (undefined *)0x0;
            }
            if (local_38 != (undefined *)0x0) {
              FUN_004398b5(local_38);
            }
            uVar2 = 0;
          }
          else if (local_8 == 0) {
            if ((local_34 != 1) && (local_54 != 1)) {
              *param_1 = 2;
            }
            if ((DAT_0045fc30 != 0) &&
               ((local_20 == 0x2e || ((0x2a < local_40 && (local_40 < 0x31)))))) {
              FUN_0041b685(2);
            }
            if (((local_20 == 0x2e) || (local_20 == 0x2f)) && ((DAT_0045ebb8 & 0x10) != 0)) {
              if (((DAT_0045eac8 == '\0') || (DAT_0045ea70 != '\0')) || (DAT_0045eb98 != 0)) {
                FUN_00413085((uint *)s_Move_from_SSH_or_SSL_cannot_foll_004566c4);
              }
              else {
                FUN_0041bbb2();
              }
            }
            if (local_20 == 0x2e) {
              DAT_0045ebb4 = DAT_0045ebb4 | 0x24c;
            }
            switch(local_40) {
            case 0x2b:
              DAT_0045ebb4 = DAT_0045ebb4 | 0x288;
              break;
            case 0x2c:
            case 0x2d:
              DAT_0045ebb4 = DAT_0045ebb4 | 0x20c;
              break;
            case 0x30:
              DAT_0045ebb4 = DAT_0045ebb4 | 0x210;
            case 0x2e:
            case 0x2f:
              DAT_0045ebb4 = DAT_0045ebb4 | 0x24c;
            }
            if (((1 < DAT_0044f9fc) && (0xd < local_40)) && (local_40 < 0x26)) {
              DAT_0045f940 = 0;
            }
            if ((local_34 == 0x11) && (local_54 == 0x11)) {
              if ((local_28 == 0) || (local_48 == 0)) {
                if (local_28 == 0) {
                  if (local_48 == 0) {
                    if (local_30 == 0) {
                      local_34 = 0xe;
                    }
                    else {
                      local_54 = 0xe;
                    }
                  }
                  else {
                    local_34 = 0xe;
                  }
                }
                else {
                  local_54 = 0xe;
                }
              }
              else {
                FUN_004133a9((uint *)s_Cannot_force_short_addressing_fo_004566f4);
                local_54 = 0xe;
              }
            }
            else if ((local_34 != 0x11) && (local_54 != 0x11)) {
              if ((local_34 != 0xe) && (local_54 != 0xe)) {
                FUN_00413085(local_14);
                if (local_18 != (undefined *)0x0) {
                  FUN_004398b5(local_18);
                  local_18 = (undefined *)0x0;
                }
                if (local_38 != (undefined *)0x0) {
                  FUN_004398b5(local_38);
                }
                return 0;
              }
              if ((local_34 == 0xe) && (local_54 == 0xe)) {
                if ((local_28 != 0) && (local_48 != 0)) {
                  FUN_00413085(local_14);
                  if (local_18 != (undefined *)0x0) {
                    FUN_004398b5(local_18);
                    local_18 = (undefined *)0x0;
                  }
                  if (local_38 != (undefined *)0x0) {
                    FUN_004398b5(local_38);
                  }
                  return 0;
                }
                if (local_28 == 0) {
                  if (local_48 == 0) {
                    if (local_30 == 0) {
                      if (((DAT_0045ea70 == '\0') && ((local_44 < 0xffc0 || (0xffff < local_44))))
                         && ((local_44 < 0x40 || (0x7f < local_44)))) {
                        FUN_00413085(local_14);
                        if (local_18 != (undefined *)0x0) {
                          FUN_004398b5(local_18);
                          local_18 = (undefined *)0x0;
                        }
                        if (local_38 != (undefined *)0x0) {
                          FUN_004398b5(local_38);
                        }
                        return 0;
                      }
                      local_54 = 0x11;
                    }
                    else if (local_50 == 0) {
                      if (((DAT_0045ea70 == '\0') && ((local_24 < 0xffc0 || (0xffff < local_24))))
                         && ((local_24 < 0x40 || (0x7f < local_24)))) {
                        FUN_00413085(local_14);
                        if (local_18 != (undefined *)0x0) {
                          FUN_004398b5(local_18);
                          local_18 = (undefined *)0x0;
                        }
                        if (local_38 != (undefined *)0x0) {
                          FUN_004398b5(local_38);
                        }
                        return 0;
                      }
                      local_34 = 0x11;
                    }
                    else {
                      local_34 = 0x11;
                      if ((((DAT_0045f8fc == 2) && (DAT_0045ea70 == '\0')) &&
                          ((local_24 < 0xffc0 || (0xffff < local_24)))) &&
                         ((local_24 < 0x40 || (0x7f < local_24)))) {
                        if (((local_44 < 0xffc0) || (0xffff < local_44)) &&
                           ((local_44 < 0x40 || (0x7f < local_44)))) {
                          FUN_00413085(local_14);
                          if (local_18 != (undefined *)0x0) {
                            FUN_004398b5(local_18);
                            local_18 = (undefined *)0x0;
                          }
                          if (local_38 != (undefined *)0x0) {
                            FUN_004398b5(local_38);
                          }
                          return 0;
                        }
                        local_54 = 0x11;
                        local_34 = 0xe;
                        if ((0x3f < local_44) && (local_44 < 0x80)) {
                          FUN_004133a9((uint *)s_Destination_operand_assumed_I_O_s_0045677c);
                        }
                        if (((0x3f < local_24) && (local_24 < 0x80)) && (local_28 != 0x4000000)) {
                          FUN_004133a9((uint *)s_Source_operand_assumed_I_O_short_004567a4);
                        }
                      }
                    }
                  }
                  else {
                    local_34 = 0x11;
                    if ((local_30 == 0) ||
                       ((((DAT_0045f8fc == 2 && (DAT_0045ea70 == '\0')) &&
                         ((local_24 < 0xffc0 || (0xffff < local_24)))) &&
                        ((local_24 < 0x40 || (0x7f < local_24)))))) {
                      FUN_00413085(local_14);
                      if (local_18 != (undefined *)0x0) {
                        FUN_004398b5(local_18);
                        local_18 = (undefined *)0x0;
                      }
                      if (local_38 != (undefined *)0x0) {
                        FUN_004398b5(local_38);
                      }
                      return 0;
                    }
                    if ((0x3f < local_24) && (local_24 < 0x80)) {
                      FUN_004133a9((uint *)s_Source_operand_assumed_I_O_short_00456758);
                    }
                  }
                }
                else {
                  local_54 = 0x11;
                  if ((local_50 == 0) ||
                     ((((DAT_0045f8fc == 2 && (DAT_0045ea70 == '\0')) &&
                       ((local_44 < 0xffc0 || (0xffff < local_44)))) &&
                      ((local_44 < 0x40 || (0x7f < local_44)))))) {
                    FUN_00413085(local_14);
                    if (local_18 != (undefined *)0x0) {
                      FUN_004398b5(local_18);
                      local_18 = (undefined *)0x0;
                    }
                    if (local_38 != (undefined *)0x0) {
                      FUN_004398b5(local_38);
                    }
                    return 0;
                  }
                  if (((0x3f < local_44) && (local_44 < 0x80)) && (local_48 != 0x4000000)) {
                    FUN_004133a9((uint *)s_Destination_operand_assumed_I_O_s_00456730);
                  }
                }
              }
              else if (local_34 == 0xe) {
                if ((local_28 != 0) || (local_30 == 0)) {
                  FUN_00413085(local_14);
                  if (local_18 != (undefined *)0x0) {
                    FUN_004398b5(local_18);
                    local_18 = (undefined *)0x0;
                  }
                  if (local_38 != (undefined *)0x0) {
                    FUN_004398b5(local_38);
                  }
                  return 0;
                }
                local_34 = 0x11;
                if ((((DAT_0045f8fc == 2) && (DAT_0045ea70 == '\0')) &&
                    ((local_24 < 0xffc0 || (0xffff < local_24)))) &&
                   ((local_24 < 0x40 || (0x7f < local_24)))) {
                  FUN_00413085(local_14);
                  if (local_18 != (undefined *)0x0) {
                    FUN_004398b5(local_18);
                    local_18 = (undefined *)0x0;
                  }
                  if (local_38 != (undefined *)0x0) {
                    FUN_004398b5(local_38);
                  }
                  return 0;
                }
                if ((0x3f < local_24) && (local_24 < 0x80)) {
                  FUN_004133a9((uint *)s_Source_operand_assumed_I_O_short_004567c8);
                }
              }
              else if (local_54 == 0xe) {
                if ((local_48 != 0) || (local_50 == 0)) {
                  if (local_18 != (undefined *)0x0) {
                    FUN_004398b5(local_18);
                    local_18 = (undefined *)0x0;
                  }
                  if (local_38 != (undefined *)0x0) {
                    FUN_004398b5(local_38);
                    local_38 = (undefined *)0x0;
                  }
                  FUN_00413085(local_14);
                  return 0;
                }
                local_54 = 0x11;
                if ((((DAT_0045f8fc == 2) && (DAT_0045ea70 == '\0')) &&
                    ((local_44 < 0xffc0 || (0xffff < local_44)))) &&
                   ((local_44 < 0x40 || (0x7f < local_44)))) {
                  FUN_00413085(local_14);
                  if (local_18 != (undefined *)0x0) {
                    FUN_004398b5(local_18);
                    local_18 = (undefined *)0x0;
                  }
                  if (local_38 != (undefined *)0x0) {
                    FUN_004398b5(local_38);
                  }
                  return 0;
                }
                if ((0x3f < local_44) && (local_44 < 0x80)) {
                  FUN_004133a9((uint *)s_Destination_operand_assumed_I_O_s_004567ec);
                }
              }
            }
            if (DAT_0045ea38 != '\0') {
              if ((local_30 == 0) || (local_50 == 0)) {
                DAT_0045f928 = DAT_0045f928 + 2;
              }
              else if (((local_30 == 4) && (local_34 != 9)) || (local_50 == 4)) {
                if ((1 < DAT_0044f9fc) &&
                   (((1 < local_20 && (local_20 < 0xd)) || ((1 < local_40 && (local_40 < 0xd)))))) {
                  DAT_0045f928 = DAT_0045f928 + -2;
                }
              }
              else {
                if (local_34 == 0x11) {
                  if ((6 < local_54) && ((local_54 < 9 || (local_54 == 0xe)))) {
                    DAT_0045f928 = DAT_0045f928 + 2;
                  }
                }
                else if (local_54 == 0x11) {
                  switch(local_34) {
                  case 7:
                  case 8:
                  case 0xe:
                    DAT_0045f928 = DAT_0045f928 + 2;
                    break;
                  case 9:
                    if (DAT_0044f9fc < 2) {
                      DAT_0045f928 = DAT_0045f928 + 2;
                    }
                  }
                }
              }
            }
            if (((local_34 == 9) || (local_34 == 0xe)) || (local_54 == 0xe)) {
              *param_1 = 2;
            }
            else {
              *param_1 = 1;
            }
            if (local_34 == 0x11) {
              if (local_54 == 1) {
                FUN_00411b08((int)param_1,(int)&local_34,(int)&local_54);
              }
              else {
                FUN_00411b70(param_1,(int)&local_34,&local_54);
              }
            }
            else if (local_34 == 1) {
              FUN_00411c6a((int)param_1,(int)&local_34,(int)&local_54);
            }
            else {
              FUN_00411c9e(param_1,&local_34,(int)&local_54);
            }
            uVar2 = 1;
          }
          else {
            if (local_18 != (undefined *)0x0) {
              FUN_004398b5(local_18);
              local_18 = (undefined *)0x0;
            }
            if (local_38 != (undefined *)0x0) {
              FUN_004398b5(local_38);
            }
            uVar2 = 0;
          }
        }
        else {
          FUN_00413085((uint *)s_Either_source_or_destination_mem_00456618);
          if (local_18 != (undefined *)0x0) {
            FUN_004398b5(local_18);
            local_18 = (undefined *)0x0;
          }
          if (local_38 != (undefined *)0x0) {
            FUN_004398b5(local_38);
          }
          uVar2 = 0;
        }
      }
    }
  }
  else {
    FUN_00413085((uint *)s_Too_many_fields_specified_for_in_004564c8);
    FUN_00413085((uint *)s_Possible_invalid_white_space_bet_004564f4);
    uVar2 = 0;
  }
  return uVar2;
}


/* ==== FUN_00427d58 @ 00427d58 ==== */

void __cdecl FUN_00427d58(int param_1,int param_2,uint *param_3)

{
  uint local_8;
  
  local_8 = 0;
  if (param_1 == 2) {
    local_8 = -(uint)(param_2 != 2) & 8;
  }
  else {
    switch(param_2) {
    case 0:
      local_8 = 0x20;
      break;
    case 1:
      local_8 = 0x30;
      break;
    case 2:
    case 3:
      local_8 = *param_3 & 7;
      switch(local_8) {
      case 0:
      case 4:
        local_8 = 0x10;
        break;
      case 1:
      case 5:
      case 7:
        local_8 = 0;
      }
      break;
    case 4:
      local_8 = 0x40;
      break;
    case 5:
      local_8 = 0x50;
      break;
    case 6:
      local_8 = 0x60;
      break;
    case 7:
      local_8 = 0x70;
      break;
    default:
      FUN_00412fa0((uint *)s_Register_selection_failure_00456814);
    }
  }
  *param_3 = *param_3 | local_8;
  return;
}


/* ==== FUN_00427e5d @ 00427e5d ==== */

undefined4 __cdecl FUN_00427e5d(undefined4 param_1,int param_2,int param_3,uint *param_4)

{
  uint local_8;
  
  local_8 = 0;
  switch(param_1) {
  case 4:
    switch(param_2) {
    case 4:
      break;
    case 5:
      local_8 = 0x50;
      break;
    case 6:
      local_8 = 0x20;
      break;
    case 7:
      local_8 = 0x40;
      break;
    default:
      FUN_00413085((uint *)s_Invalid_register_combination_00456830);
      return 0;
    }
    break;
  case 5:
    switch(param_2) {
    case 4:
      local_8 = 0x50;
      break;
    case 5:
      local_8 = 0x10;
      break;
    case 6:
      local_8 = 0x60;
      break;
    case 7:
      local_8 = 0x30;
      break;
    default:
      FUN_00413085((uint *)s_Invalid_register_combination_00456870);
      return 0;
    }
    break;
  case 6:
    if (param_2 == 4) {
      local_8 = 0x20;
    }
    else if (param_2 == 5) {
      local_8 = 0x60;
    }
    else {
      if (param_2 != 7) {
        FUN_00413085((uint *)s_Invalid_register_combination_00456850);
        return 0;
      }
      local_8 = 0x70;
    }
    break;
  case 7:
    if (param_2 == 4) {
      local_8 = 0x40;
    }
    else if (param_2 == 5) {
      local_8 = 0x30;
    }
    else {
      if (param_2 != 6) {
        FUN_00413085((uint *)s_Invalid_register_combination_00456890);
        return 0;
      }
      local_8 = 0x70;
    }
    break;
  default:
    FUN_00412fa0((uint *)s_mulreg_failure_004568b0);
    return 0;
  }
  if (param_3 == 3) {
    local_8 = local_8 | 8;
  }
  *param_4 = *param_4 | local_8;
  return 1;
}


