/* amode: 19 functions from ASM56000 */

/* ==== FUN_00405eea @ 00405eea ==== */

void __cdecl FUN_00405eea(undefined1 *param_1,undefined1 *param_2)

{
  int *extraout_EAX;
  long local_8;
  
  local_8 = time((long *)0x0);
  localtime(&local_8);
  sprintf(param_1,s__02d__02d__02d_00451a18,extraout_EAX[5],extraout_EAX[4] + 1,extraout_EAX[3]);
  sprintf(param_2,s__02d__02d__02d_00451a28,extraout_EAX[2],extraout_EAX[1],*extraout_EAX);
  FUN_0043c528(extraout_EAX);
  return;
}


/* ==== FUN_00405f6a @ 00405f6a ==== */

undefined4 FUN_00405f6a(void)

{
  return 1;
}


/* ==== FUN_00405f74 @ 00405f74 ==== */

void __cdecl FUN_00405f74(int *param_1)

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


/* ==== FUN_00405fbe @ 00405fbe ==== */

void __cdecl FUN_00405fbe(undefined1 param_1)

{
  if (DAT_0045eb8c == 0) {
    DAT_0045eac8 = param_1;
  }
  return;
}


/* ==== FUN_00405fd4 @ 00405fd4 ==== */

int FUN_00405fd4(void)

{
  return (int)DAT_0045eac8;
}


/* ==== FUN_00405fe0 @ 00405fe0 ==== */

undefined4 __cdecl FUN_00405fe0(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = FUN_004061ae(0,param_1,0x12,1,6,6);
  if (iVar2 == 0) {
    if (param_1[7] != 0) {
      FUN_004398b5((undefined *)param_1[7]);
      param_1[7] = 0;
    }
    uVar3 = 0;
  }
  else {
    if (((param_1[1] == 4) && (2 < *param_1)) && (*param_1 < 7)) {
      if (*DAT_0045f860 != '\0') {
        FUN_00413085((uint *)s_Address_mode_syntax_error___extr_00451a70);
        if (param_1[7] != 0) {
          FUN_004398b5((undefined *)param_1[7]);
          param_1[7] = 0;
        }
        return 0;
      }
    }
    else {
      cVar1 = *DAT_0045f860;
      DAT_0045f860 = DAT_0045f860 + 1;
      if (cVar1 != ',') {
        FUN_00413085((uint *)s_Address_mode_syntax_error___expe_00451aa0);
        if (param_1[7] != 0) {
          FUN_004398b5((undefined *)param_1[7]);
          param_1[7] = 0;
        }
        return 0;
      }
    }
    uVar3 = 1;
  }
  return uVar3;
}


/* ==== FUN_004060d8 @ 004060d8 ==== */

undefined4 __cdecl
FUN_004060d8(uint param_1,int *param_2,int param_3,int param_4,int param_5,int param_6)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = FUN_004061ae(param_1,param_2,param_3,param_4,param_5,param_6);
  if (iVar2 == 0) {
    if (param_2[7] != 0) {
      FUN_004398b5((undefined *)param_2[7]);
      param_2[7] = 0;
    }
    uVar3 = 0;
  }
  else if ((param_1 & 1) == 0) {
    if (*DAT_0045f860 == '\0') {
      uVar3 = 1;
    }
    else {
      FUN_00413085((uint *)s_Address_mode_syntax_error___extr_00451af8);
      if (param_2[7] != 0) {
        FUN_004398b5((undefined *)param_2[7]);
        param_2[7] = 0;
      }
      uVar3 = 0;
    }
  }
  else {
    cVar1 = *DAT_0045f860;
    DAT_0045f860 = DAT_0045f860 + 1;
    if (cVar1 == ',') {
      uVar3 = 1;
    }
    else {
      FUN_00413085((uint *)s_Address_mode_syntax_error___expe_00451acc);
      uVar3 = 0;
    }
  }
  return uVar3;
}


/* ==== FUN_004061ae @ 004061ae ==== */

undefined4 __cdecl
FUN_004061ae(uint param_1,int *param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  
  *param_2 = 0;
  if ((param_1 & 4) != 0) {
    param_2[1] = 4;
  }
  param_2[2] = 0;
  param_2[3] = 0;
  param_2[4] = 0;
  param_2[5] = -1;
  param_2[6] = 0;
  param_2[7] = 0;
  if ((DAT_0045f860 == (char *)0x0) || (*DAT_0045f860 == '\0')) {
    FUN_00413085((uint *)s_Syntax_error___missing_address_m_00451b28);
    FUN_00413085((uint *)s_Possible_invalid_white_space_bet_00451b58);
    return 0;
  }
  if (param_3 != 0) {
    iVar1 = FUN_0040641c(param_3,param_2);
    if (iVar1 == -1) {
      return 0;
    }
    if (iVar1 == 1) {
      iVar1 = FUN_00406938(param_1,param_3,param_2[5]);
      if (iVar1 == 0) {
        return 0;
      }
      return 1;
    }
  }
  if (((param_6 == 0) && (param_4 == 0)) && (param_5 == 0)) {
    FUN_00413085((uint *)s_Only_register_direct_addressing_a_00451b94);
    return 0;
  }
  if (param_6 != 0) {
    iVar1 = FUN_00406f87(param_6,param_2);
    if (iVar1 == -1) {
      return 0;
    }
    if (iVar1 == 1) {
      return 1;
    }
  }
  if ((param_4 == 0) && (param_5 == 0)) {
    if (param_3 == 0) {
      FUN_00413085((uint *)s_Only_immediate_addressing_allowe_00451bbc);
      return 0;
    }
    if (param_6 == 0) {
      FUN_00413085((uint *)s_Only_register_direct_addressing_a_00451be0);
      return 0;
    }
    FUN_00413085((uint *)s_Only_immediate_and_register_dire_00451c08);
    return 0;
  }
  if (param_4 != 0) {
    iVar1 = FUN_00406bfa(param_4,param_2);
    if (iVar1 == -1) {
      return 0;
    }
    if (iVar1 == 1) {
      FUN_004069eb((char)param_2[5],*param_2);
      return 1;
    }
  }
  if (param_5 != 0) {
    if (param_5 != 0) {
      iVar1 = FUN_0040758c(param_5,param_2);
      if (iVar1 == -1) {
        return 0;
      }
      if (iVar1 == 1) {
        return 1;
      }
    }
    FUN_00413085((uint *)s_Invalid_addressing_mode_00451ce8);
    return 0;
  }
  if (param_3 == 0) {
    FUN_00413085((uint *)s_Only_register_indirect_addressin_00451c40);
    return 0;
  }
  if (param_6 == 0) {
    FUN_00413085((uint *)s_Only_register_direct_and_indirec_00451c6c);
    return 0;
  }
  FUN_00413085((uint *)s_Only_immediate_and_register_dire_00451ca4);
  return 0;
}


/* ==== FUN_0040641c @ 0040641c ==== */

undefined4 __cdecl FUN_0040641c(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  bool bVar2;
  int local_c;
  
  local_c = FUN_004080dc(&DAT_0045f860);
  if (local_c == -1) {
    uVar1 = 0;
  }
  else {
    switch(param_1) {
    case 1:
      if ((local_c == 2) || (local_c == 3)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      break;
    case 2:
      if ((local_c == 5) || (local_c == 7)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      break;
    case 3:
      if ((((local_c == 4) || (local_c == 6)) || (local_c == 2)) || (local_c == 3)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      break;
    case 4:
      if (((local_c == 5) || (local_c == 7)) || ((local_c == 2 || (local_c == 3)))) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      break;
    case 5:
      if (((((local_c == 0) || (local_c == 1)) || (local_c == 2)) || (local_c == 3)) ||
         ((0x25 < local_c && (local_c < 0x2a)))) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      break;
    case 6:
      if (((local_c < 2) || (0x25 < local_c)) && ((local_c < 0x2a || (0x30 < local_c)))) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      break;
    case 7:
      if ((local_c < 0x2a) || (0x30 < local_c)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      break;
    case 8:
      if ((local_c < 0x1e) || (0x1f < local_c)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      break;
    case 9:
      if (((local_c < 2) || (7 < local_c)) && ((local_c < 0xe || (0x1d < local_c)))) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      break;
    case 10:
      if ((local_c == 0) || (local_c == 1)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      break;
    case 0xb:
      if ((local_c < 4) || (7 < local_c)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      break;
    case 0xc:
      if (((local_c == 0) || (local_c == 1)) || ((3 < local_c && (local_c < 8)))) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      break;
    case 0xd:
      bVar2 = local_c == 2;
      break;
    case 0xe:
      bVar2 = local_c == 3;
      break;
    case 0xf:
      if ((local_c < 2) || (7 < local_c)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      break;
    case 0x10:
      if ((local_c < 0xe) || (0x15 < local_c)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      break;
    case 0x11:
      if (((local_c < 2) || (0x25 < local_c)) && ((local_c < 0x2a || (0x30 < local_c)))) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      break;
    case 0x12:
      if ((local_c < 0) || (0x30 < local_c)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      break;
    case 0x13:
      if (((local_c == 0x31) || (local_c == 0x32)) || (local_c == 0x2a)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      break;
    case 0x14:
      if ((local_c < 0xe) || (0x1d < local_c)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      break;
    case 0x15:
      if ((local_c < 0) || (7 < local_c)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      break;
    case 0x16:
      if (((local_c == 4) || (local_c == 2)) || (local_c == 3)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      break;
    case 0x17:
      if (((local_c == 4) || (local_c == 5)) ||
         ((local_c == 7 || ((local_c == 2 || (local_c == 3)))))) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      break;
    case 0x18:
      if ((((local_c == 2) || (local_c == 3)) || (local_c == 10)) || (local_c == 0xb)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      if (local_c == 10) {
        local_c = 2;
      }
      else if (local_c == 0xb) {
        local_c = 3;
      }
      break;
    default:
      bVar2 = false;
    }
    if (bVar2) {
      *param_2 = 1;
      param_2[5] = local_c;
      uVar1 = 1;
    }
    else {
      if (param_1 == 0) {
        FUN_00413085((uint *)s_Register_direct_addressing_not_a_00451d00);
      }
      else {
        FUN_004131f9((uint *)s_Invalid_register_specified_00451d28,
                     *(char **)(local_c * 4 + 0x44ece8));
      }
      uVar1 = 0xffffffff;
    }
  }
  return uVar1;
}


/* ==== FUN_00406938 @ 00406938 ==== */

undefined4 __cdecl FUN_00406938(uint param_1,int param_2,int param_3)

{
  int iVar1;
  char local_8;
  
  if (DAT_0045ea5c == '\0') {
    if (((param_3 < 0x1e) || (0x25 < param_3)) && ((param_3 < 0x2a || (0x32 < param_3)))) {
      local_8 = '\0';
    }
    else {
      local_8 = '\x01';
    }
    DAT_0045ea5c = local_8;
  }
  if ((param_1 & 2) == 0) {
    DAT_0045f948 = param_3;
  }
  else {
    if (((0xd < param_3) && (param_3 < 0x26)) && (param_3 != DAT_0045f948)) {
      DAT_0045f940 = DAT_0045f940 | 1 << ((char)param_3 - 0xeU & 0x1f);
      DAT_0045f94c = *DAT_0045f8c0;
    }
    iVar1 = FUN_00406aaf(param_2,param_3);
    if (iVar1 != 0) {
      return 0;
    }
  }
  return 1;
}


/* ==== FUN_004069eb @ 004069eb ==== */

void __cdecl FUN_004069eb(char param_1,int param_2)

{
  uint uVar1;
  uint local_8;
  
  uVar1 = 1 << (param_1 - 0xeU & 0x1f);
  local_8 = uVar1;
  if ((4 < param_2) && (param_2 < 8)) {
    local_8 = uVar1 | uVar1 << 8;
  }
  if ((2 < param_2) && (param_2 < 9)) {
    local_8 = local_8 | uVar1 << 0x10;
  }
  if (((DAT_0045f944 & local_8) != 0) &&
     ((*DAT_0045f8c0 == DAT_0045f94c + DAT_0044f95c || (DAT_0045ea70 != '\0')))) {
    if ((DAT_0045eac8 == '\0') || ((DAT_0045ea70 != '\0' || (DAT_0045eb98 != 0)))) {
      FUN_00413085((uint *)s_Contents_of_register_written_in_p_00451d44);
    }
    else {
      FUN_0041bbb2();
    }
  }
  return;
}


/* ==== FUN_00406aaf @ 00406aaf ==== */

uint __cdecl FUN_00406aaf(int param_1,undefined4 param_2)

{
  bool bVar1;
  uint local_8;
  
  switch(param_2) {
  case 2:
    local_8 = (-(uint)(param_1 != 0x18) & 5) + 2;
    break;
  case 3:
    local_8 = (-(uint)(param_1 != 0x18) & 0x50) + 0x20;
    break;
  default:
    return 0;
  case 8:
    local_8 = 1;
    break;
  case 9:
    local_8 = 0x10;
    break;
  case 10:
    local_8 = 2;
    break;
  case 0xb:
    local_8 = 0x20;
    break;
  case 0xc:
    local_8 = 4;
    break;
  case 0xd:
    local_8 = 0x40;
    break;
  case 0x26:
    local_8 = 0x66;
    break;
  case 0x27:
    local_8 = 0x66;
    break;
  case 0x28:
    local_8 = 3;
    break;
  case 0x29:
    local_8 = 0x30;
  }
  bVar1 = (local_8 & DAT_0045f93c) == 0;
  if (bVar1) {
    DAT_0045f93c = DAT_0045f93c | local_8;
  }
  else {
    FUN_00413085((uint *)s_Duplicate_destination_register_n_00451d88);
  }
  return (uint)!bVar1;
}


/* ==== FUN_00406bfa @ 00406bfa ==== */

undefined4 __cdecl FUN_00406bfa(int param_1,undefined4 *param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  
  pcVar4 = DAT_0045f860;
  if ((*DAT_0045f860 == '-') && (DAT_0045f860[1] == '(')) {
    DAT_0045f860 = DAT_0045f860 + 2;
    iVar2 = FUN_0040800f();
    param_2[5] = iVar2;
    if (param_2[5] == -1) {
      uVar3 = 0;
      DAT_0045f860 = pcVar4;
    }
    else {
      cVar1 = *DAT_0045f860;
      DAT_0045f860 = DAT_0045f860 + 1;
      if (cVar1 == ')') {
        if (param_1 == 1) {
          *param_2 = 8;
          uVar3 = 1;
        }
        else {
          FUN_00413085((uint *)s_Pre_decrement_addressing_mode_no_00451de0);
          uVar3 = 0xffffffff;
        }
      }
      else {
        FUN_00413085((uint *)s_Address_mode_syntax_error___expe_00451db4);
        uVar3 = 0xffffffff;
      }
    }
  }
  else if (*DAT_0045f860 == '(') {
    DAT_0045f860 = DAT_0045f860 + 1;
    iVar2 = FUN_0040800f();
    param_2[5] = iVar2;
    if (param_2[5] == -1) {
      uVar3 = 0;
      DAT_0045f860 = pcVar4;
    }
    else if (*DAT_0045f860 == '+') {
      DAT_0045f860 = DAT_0045f860 + 1;
      iVar2 = FUN_00408046(param_2[5]);
      if (iVar2 == -1) {
        FUN_00413085((uint *)s_Address_mode_syntax_error___prob_00451e0c);
        uVar3 = 0xffffffff;
      }
      else {
        cVar1 = *DAT_0045f860;
        DAT_0045f860 = DAT_0045f860 + 1;
        if (cVar1 == ')') {
          if ((*DAT_0045f860 == ',') || (*DAT_0045f860 == '\0')) {
            if (param_1 == 1) {
              *param_2 = 7;
              uVar3 = 1;
            }
            else {
              FUN_00413085((uint *)s_Indexed_address_mode_not_allowed_00451ea8);
              uVar3 = 0xffffffff;
            }
          }
          else {
            FUN_00413085((uint *)s_Address_mode_syntax_error___expe_00451e6c);
            uVar3 = 0xffffffff;
          }
        }
        else {
          FUN_00413085((uint *)s_Address_mode_syntax_error___expe_00451e40);
          uVar3 = 0xffffffff;
        }
      }
    }
    else {
      pcVar4 = DAT_0045f860 + 1;
      if (*DAT_0045f860 == ')') {
        if ((*pcVar4 == '\0') || (*pcVar4 == ',')) {
          if ((param_1 == 1) || (param_1 == 2)) {
            DAT_0045f860 = pcVar4;
            *param_2 = 2;
            uVar3 = 1;
          }
          else {
            DAT_0045f860 = pcVar4;
            FUN_00413085((uint *)s_No_update_mode_not_allowed_00451ef8);
            uVar3 = 0xffffffff;
          }
        }
        else if ((*pcVar4 == '+') || (*pcVar4 == '-')) {
          cVar1 = *pcVar4;
          DAT_0045f860 = DAT_0045f860 + 2;
          if ((*DAT_0045f860 == '\0') || (*DAT_0045f860 == ',')) {
            if (cVar1 == '+') {
              *param_2 = 3;
              uVar3 = 1;
            }
            else {
              *param_2 = 4;
              uVar3 = 1;
            }
          }
          else {
            iVar2 = FUN_00408046(param_2[5]);
            if (iVar2 == 0) {
              FUN_00413085((uint *)s_Address_mode_syntax_error___prob_00451f44);
              uVar3 = 0xffffffff;
            }
            else if ((*DAT_0045f860 == '\0') || (*DAT_0045f860 == ',')) {
              if (cVar1 == '+') {
                *param_2 = 5;
                uVar3 = 1;
              }
              else if ((param_1 == 1) || (param_1 == 3)) {
                *param_2 = 6;
                uVar3 = 1;
              }
              else {
                FUN_00413085((uint *)s_Post_decrement_by_offset_address_00451fb4);
                uVar3 = 0xffffffff;
              }
            }
            else {
              FUN_00413085((uint *)s_Address_mode_syntax_error___expe_00451f78);
              uVar3 = 0xffffffff;
            }
          }
        }
        else {
          DAT_0045f860 = pcVar4;
          FUN_00413085((uint *)s_Address_mode_syntax_error___expe_00451f14);
          uVar3 = 0xffffffff;
        }
      }
      else {
        DAT_0045f860 = pcVar4;
        FUN_00413085((uint *)s_Address_mode_syntax_error___expe_00451ecc);
        uVar3 = 0xffffffff;
      }
    }
  }
  else {
    uVar3 = 0;
    DAT_0045f860 = pcVar4;
  }
  return uVar3;
}


/* ==== FUN_00406f87 @ 00406f87 ==== */

undefined4 __cdecl FUN_00406f87(int param_1,undefined4 *param_2)

{
  uint uVar1;
  bool bVar2;
  bool bVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  bool bVar7;
  uint *local_30;
  uint local_2c;
  int local_10;
  
  if (*DAT_0045f860 == '#') {
    if (param_1 == 0) {
      FUN_00413085((uint *)s_Immediate_addressing_mode_not_al_00451fec);
      for (; (*DAT_0045f860 != '\0' && (*DAT_0045f860 != ',')); DAT_0045f860 = DAT_0045f860 + 1) {
      }
      uVar4 = 0xffffffff;
    }
    else {
      DAT_0045f860 = DAT_0045f860 + 1;
      local_10 = FUN_0043ae13(0x3000000);
      if (local_10 == -1) {
        uVar4 = 0xffffffff;
      }
      else {
        piVar5 = FUN_00407462(param_1);
        if (piVar5 == (int *)0x0) {
          uVar4 = 0xffffffff;
        }
        else {
          bVar7 = (piVar5[6] & 0x100000U) != 0;
          uVar1 = piVar5[2];
          if ((((*PTR_DAT_0044f820 == '\0') && ((piVar5[6] & 0x8000000U) == 0)) &&
              (local_10 != 0x1000000)) && (iVar6 = FUN_00407511(), iVar6 != 0)) {
            if (((DAT_0045ead4 == '\0') || (0xff < uVar1)) ||
               ((param_1 != 6 || (local_10 == 0x2000000)))) {
              if ((uVar1 & 0xffff) == 0) {
                piVar5[2] = (int)uVar1 >> 0x10 & 0xff;
              }
            }
            else {
              local_10 = 0x1000000;
            }
          }
          if ((uVar1 == piVar5[2]) && (uVar1 != 0)) {
            bVar2 = false;
          }
          else {
            bVar2 = true;
          }
          param_2[3] = local_10;
          param_2[4] = piVar5[2];
          param_2[2] = piVar5[6] & 0x8000000;
          if (((piVar5[6] & 0x1000U) == 0) && (-1 < piVar5[0xf])) {
            bVar3 = false;
          }
          else {
            bVar3 = true;
          }
          param_2[6] = piVar5[0xf];
          FUN_004167ef(piVar5);
          switch(param_1) {
          case 1:
            if (local_10 == 0x2000000) {
              FUN_004133a9((uint *)s_Short_immediate_cannot_be_forced_00452014);
            }
            *param_2 = 9;
            break;
          case 2:
            if (local_10 == 0x1000000) {
              FUN_004133a9((uint *)s_Long_immediate_cannot_be_forced_00452038);
            }
            *param_2 = 10;
            if (((param_2[2] == 0) || (DAT_0045f8fc == 2)) && (0xfff < (uint)param_2[4])) {
              FUN_00413085((uint *)s_Immediate_value_too_large_00452058);
              return 0xffffffff;
            }
            break;
          case 3:
            if (local_10 == 0x1000000) {
              FUN_004133a9((uint *)s_Long_immediate_cannot_be_forced_00452074);
            }
            *param_2 = 0xb;
            if (((param_2[2] == 0) || (DAT_0045f8fc == 2)) && (0xff < (uint)param_2[4])) {
              FUN_00413085((uint *)s_Immediate_value_too_large_00452094);
              return 0xffffffff;
            }
            break;
          case 4:
            if (local_10 == 0x1000000) {
              FUN_004133a9((uint *)s_Long_immediate_cannot_be_forced_004520b0);
            }
            *param_2 = 0xc;
            if (((param_2[2] == 0) || (DAT_0045f8fc == 2)) && (0x17 < (uint)param_2[4])) {
              FUN_00413085((uint *)s_Immediate_value_too_large_004520d0);
              return 0xffffffff;
            }
            break;
          case 5:
            if (local_10 == 0x1000000) {
              FUN_004133a9((uint *)s_Long_immediate_cannot_be_forced_004520ec);
            }
            *param_2 = 0xd;
            if ((int)param_2[4] < 0) {
              local_2c = -param_2[4];
            }
            else {
              local_2c = param_2[4];
            }
            if (((param_2[2] == 0) || (DAT_0045f8fc == 2)) && (0x17 < local_2c)) {
              FUN_00413085((uint *)s_Immediate_value_too_large_0045210c);
              return 0xffffffff;
            }
            break;
          case 6:
            if (local_10 == 0x1000000) {
              *param_2 = 9;
            }
            else if (local_10 == 0x2000000) {
              *param_2 = 0xb;
              if (param_2[2] == 0) {
                if ((0xff < (uint)param_2[4]) || ((bVar7 && (!bVar2)))) {
                  *param_2 = 9;
                  FUN_004133a9((uint *)s_Immediate_value_too_large_to_use_00452128);
                }
              }
              else if ((DAT_0045f8fc == 2) && (0xff < (uint)param_2[4])) {
                FUN_00413085((uint *)s_Immediate_value_too_large_to_use_00452164);
                return 0xffffffff;
              }
            }
            else if ((param_2[2] != 0) || (bVar3)) {
              *param_2 = 9;
            }
            else if ((0xff < (uint)param_2[4]) || ((bVar7 && (!bVar2)))) {
              *param_2 = 9;
            }
            else {
              *param_2 = 0xb;
            }
            break;
          default:
            FUN_00412fa0((uint *)s_Immediate_mode_select_failure_0045218c);
          }
          if (bVar3) {
            local_30 = FUN_004094bb(param_2);
          }
          else {
            local_30 = (uint *)0x0;
          }
          param_2[7] = local_30;
          uVar4 = 1;
        }
      }
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}


/* ==== FUN_00407462 @ 00407462 ==== */

int * __cdecl FUN_00407462(int param_1)

{
  int *piVar1;
  
  piVar1 = FUN_004141b1();
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else if (piVar1[4] == 0x100) {
    if ((((piVar1[2] < 0) && (param_1 != 5)) && (param_1 != 1)) && (param_1 != 6)) {
      FUN_004167ef(piVar1);
      FUN_00413085((uint *)s_Negative_immediate_value_not_all_004521ac);
      piVar1 = (int *)0x0;
    }
  }
  else if ((param_1 == 1) || (param_1 == 6)) {
    FUN_0040b5a4(*piVar1,piVar1[1],3,piVar1);
  }
  else {
    FUN_004167ef(piVar1);
    FUN_00413085((uint *)s_Floating_point_value_not_allowed_004521d4);
    piVar1 = (int *)0x0;
  }
  return piVar1;
}


/* ==== FUN_00407511 @ 00407511 ==== */

int FUN_00407511(void)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 local_2c [8];
  char *local_c;
  int local_8;
  
  uVar2 = DAT_0045ea50;
  local_c = DAT_0045f860;
  DAT_0045ea50 = 1;
  cVar1 = *DAT_0045f860;
  DAT_0045f860 = DAT_0045f860 + 1;
  if (cVar1 == ',') {
    local_8 = FUN_0040641c(0xf,local_2c);
    if (local_8 != 1) {
      local_8 = 0;
    }
  }
  else {
    local_8 = 0;
  }
  DAT_0045f860 = local_c;
  DAT_0045ea50 = uVar2;
  return local_8;
}


/* ==== FUN_0040758c @ 0040758c ==== */

undefined4 __cdecl FUN_0040758c(int param_1,undefined4 *param_2)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  uint *local_20;
  int local_14;
  
  if (param_1 == 0) {
    FUN_00413085((uint *)s_Absolute_addressing_mode_not_all_004521f8);
    uVar2 = 0xffffffff;
  }
  else {
    iVar3 = FUN_0043ae13(0x7000000);
    if (iVar3 == -1) {
      uVar2 = 0xffffffff;
    }
    else {
      param_2[3] = iVar3;
      piVar4 = FUN_00413c50(DAT_0044f91c);
      if (piVar4 == (int *)0x0) {
        uVar2 = 0xffffffff;
      }
      else {
        if ((DAT_0044f7a4 != '\0') && (iVar5 = FUN_0043baf1(piVar4[7],param_2[1]), iVar5 == 0xa2c2a)
           ) {
          FUN_004133a9((uint *)s_Absolute_address_involves_incomp_00452220);
        }
        if ((piVar4[7] != 4) && (param_2[1] == 4)) {
          param_2[1] = piVar4[7];
        }
        if ((iVar3 == 0x4000000) && (piVar4[0xf] < 0)) {
          local_14 = 0xffc0;
        }
        else {
          local_14 = piVar4[2];
        }
        param_2[4] = local_14;
        param_2[2] = piVar4[6] & 0x8000000;
        if (((piVar4[6] & 0x1000U) == 0) && (-1 < piVar4[0xf])) {
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
        param_2[6] = piVar4[0xf];
        FUN_004167ef(piVar4);
        switch(param_1) {
        case 1:
          if (iVar3 == 0x2000000) {
            FUN_004133a9((uint *)s_Short_absolute_address_cannot_be_00452258);
          }
          else if (iVar3 == 0x4000000) {
            FUN_004133a9((uint *)s_I_O_short_absolute_address_canno_00452280);
          }
          *param_2 = 0xe;
          break;
        case 2:
          if (iVar3 == 0x1000000) {
            FUN_004133a9((uint *)s_Long_absolute_address_cannot_be_f_004522ac);
          }
          else if (iVar3 == 0x2000000) {
            FUN_004133a9((uint *)s_Short_absolute_address_cannot_be_004522d4);
          }
          *param_2 = 0x11;
          if (((param_2[2] == 0) || (DAT_0045f8fc == 2)) &&
             ((DAT_0045ea70 == '\0' && (((uint)param_2[4] < 0xffc0 || (0xffff < (uint)param_2[4]))))
             )) {
            FUN_00413085((uint *)s_Short_I_O_absolute_address_too_s_004522fc);
            return 0xffffffff;
          }
          break;
        case 3:
          if (iVar3 == 0x1000000) {
            FUN_004133a9((uint *)s_Long_absolute_address_cannot_be_f_00452324);
          }
          else if (iVar3 == 0x4000000) {
            FUN_004133a9((uint *)s_I_O_short_absolute_address_canno_0045234c);
          }
          *param_2 = 0xf;
          if (((param_2[2] == 0) || (DAT_0045f8fc == 2)) && (0xfff < (uint)param_2[4])) {
            FUN_00413085((uint *)s_Short_absolute_address_too_large_00452378);
            return 0xffffffff;
          }
          break;
        case 4:
          if (iVar3 == 0x1000000) {
            FUN_004133a9((uint *)s_Long_absolute_address_cannot_be_f_0045239c);
          }
          else if (iVar3 == 0x4000000) {
            FUN_004133a9((uint *)s_I_O_short_absolute_address_canno_004523c4);
          }
          *param_2 = 0x10;
          if (((param_2[2] == 0) || (DAT_0045f8fc == 2)) && (0x3f < (uint)param_2[4])) {
            FUN_00413085((uint *)s_Short_absolute_address_too_large_004523f0);
            return 0xffffffff;
          }
          break;
        case 5:
          if (iVar3 == 0x1000000) {
            *param_2 = 0xe;
          }
          else if (iVar3 == 0x2000000) {
            *param_2 = 0xf;
            if (param_2[2] == 0) {
              if (0xfff < (uint)param_2[4]) {
                *param_2 = 0xe;
                FUN_004133a9((uint *)s_Absolute_address_too_large_to_us_00452414);
              }
            }
            else if ((DAT_0045f8fc == 2) && (0xfff < (uint)param_2[4])) {
              FUN_00413085((uint *)s_Absolute_address_too_large_to_us_00452450);
              return 0xffffffff;
            }
          }
          else if ((param_2[2] != 0) || (bVar1)) {
            *param_2 = 0xe;
          }
          else if ((uint)param_2[4] < 0x1000) {
            *param_2 = 0xf;
          }
          else {
            *param_2 = 0xe;
          }
          break;
        case 6:
          if (iVar3 == 0x1000000) {
            *param_2 = 0xe;
          }
          else if (iVar3 == 0x4000000) {
            *param_2 = 0x11;
            if ((0x3f < (uint)param_2[4]) && ((uint)param_2[4] < 0x80)) {
              param_2[4] = param_2[4] | 0xffc0;
            }
            if (param_2[2] == 0) {
              if ((DAT_0045ea70 == '\0') &&
                 (((uint)param_2[4] < 0xffc0 || (0xffff < (uint)param_2[4])))) {
                *param_2 = 0xe;
                FUN_004133a9((uint *)s_Absolute_address_too_small_to_us_00452478);
              }
            }
            else if (((DAT_0045f8fc == 2) && (DAT_0045ea70 == '\0')) &&
                    (((uint)param_2[4] < 0xffc0 || (0xffff < (uint)param_2[4])))) {
              FUN_00413085((uint *)s_Absolute_address_too_small_to_us_004524b8);
              return 0xffffffff;
            }
          }
          else if (iVar3 == 0x2000000) {
            *param_2 = 0x10;
            if (param_2[2] == 0) {
              if (0x3f < (uint)param_2[4]) {
                *param_2 = 0xe;
                FUN_004133a9((uint *)s_Absolute_address_too_large_to_us_004524e4);
              }
            }
            else if ((DAT_0045f8fc == 2) && (0x3f < (uint)param_2[4])) {
              FUN_00413085((uint *)s_Absolute_address_too_large_to_us_00452520);
              return 0xffffffff;
            }
          }
          else if ((param_2[2] != 0) || (bVar1)) {
            *param_2 = 0xe;
          }
          else if ((uint)param_2[4] < 0x40) {
            *param_2 = 0x10;
          }
          else if ((DAT_0045ea70 == '\0') &&
                  (((uint)param_2[4] < 0xffc0 || (0xffff < (uint)param_2[4])))) {
            *param_2 = 0xe;
          }
          else {
            *param_2 = 0x11;
          }
          break;
        case 7:
          if (iVar3 == 0x1000000) {
            if (param_2[2] == 0) {
              if ((uint)param_2[4] < 0x40) {
                FUN_004133a9((uint *)s_Long_absolute_address_cannot_be_f_00452548);
                *param_2 = 0x10;
              }
              else {
                if ((DAT_0045ea70 == '\0') &&
                   (((uint)param_2[4] < 0xffc0 || (0xffff < (uint)param_2[4])))) {
                  FUN_00413085((uint *)s_Long_absolute_address_cannot_be_u_004525dc);
                  return 0xffffffff;
                }
                FUN_004133a9((uint *)s_Long_absolute_address_cannot_be_f_00452590);
                *param_2 = 0x11;
              }
            }
            else {
              *param_2 = 0x10;
              if (DAT_0045f8fc == 2) {
                if (0x3f < (uint)param_2[4]) {
                  FUN_00413085((uint *)s_Long_absolute_cannot_be_used___f_00452604);
                  return 0xffffffff;
                }
                FUN_004133a9((uint *)s_Long_absolute_address_cannot_be_f_0045263c);
              }
            }
          }
          else if (iVar3 == 0x4000000) {
            *param_2 = 0x11;
            if ((0x3f < (uint)param_2[4]) && ((uint)param_2[4] < 0x80)) {
              param_2[4] = param_2[4] | 0xffc0;
            }
            if (param_2[2] == 0) {
              if ((DAT_0045ea70 == '\0') &&
                 (((uint)param_2[4] < 0xffc0 || (0xffff < (uint)param_2[4])))) {
                FUN_00413085((uint *)s_Absolute_address_too_small_to_us_00452684);
                return 0xffffffff;
              }
            }
            else if (((DAT_0045f8fc == 2) && (DAT_0045ea70 == '\0')) &&
                    (((uint)param_2[4] < 0xffc0 || (0xffff < (uint)param_2[4])))) {
              FUN_00413085((uint *)s_Absolute_address_too_small_to_us_004526b0);
              return 0xffffffff;
            }
          }
          else if (iVar3 == 0x2000000) {
            *param_2 = 0x10;
            if (param_2[2] == 0) {
              if (0x3f < (uint)param_2[4]) {
                FUN_00413085((uint *)s_Absolute_address_too_large_to_us_004526dc);
                return 0xffffffff;
              }
            }
            else if ((DAT_0045f8fc == 2) && (0x3f < (uint)param_2[4])) {
              FUN_00413085((uint *)s_Absolute_address_too_large_to_us_00452704);
              return 0xffffffff;
            }
          }
          else if ((param_2[2] != 0) || (bVar1)) {
            *param_2 = 0x10;
            if ((DAT_0045f8fc == 2) && (0x3f < (uint)param_2[4])) {
              FUN_00413085((uint *)s_Absolute_address_contains_forwar_00452760);
              return 0xffffffff;
            }
          }
          else if ((uint)param_2[4] < 0x40) {
            *param_2 = 0x10;
          }
          else {
            if ((DAT_0045ea70 == '\0') &&
               (((uint)param_2[4] < 0xffc0 || (0xffff < (uint)param_2[4])))) {
              FUN_00413085((uint *)s_Absolute_address_must_be_either_s_0045272c);
              return 0xffffffff;
            }
            *param_2 = 0x11;
          }
          break;
        case 8:
          if (iVar3 == 0x1000000) {
            *param_2 = 0xe;
          }
          else if (iVar3 == 0x4000000) {
            *param_2 = 0x11;
            if ((0x3f < (uint)param_2[4]) && ((uint)param_2[4] < 0x80)) {
              param_2[4] = param_2[4] | 0xffc0;
            }
            if (param_2[2] == 0) {
              if ((DAT_0045ea70 == '\0') &&
                 (((uint)param_2[4] < 0xffc0 || (0xffff < (uint)param_2[4])))) {
                *param_2 = 0xe;
                FUN_004133a9((uint *)s_Absolute_address_too_small_to_us_004527b0);
              }
            }
            else if (((DAT_0045f8fc == 2) && (DAT_0045ea70 == '\0')) &&
                    (((uint)param_2[4] < 0xffc0 || (0xffff < (uint)param_2[4])))) {
              FUN_00413085((uint *)s_Absolute_address_too_small_to_us_004527f0);
              return 0xffffffff;
            }
          }
          else if (iVar3 == 0x2000000) {
            *param_2 = 0xe;
            FUN_004133a9((uint *)s_Short_absolute_address_cannot_be_0045281c);
          }
          else if ((param_2[2] != 0) || (bVar1)) {
            *param_2 = 0xe;
          }
          else if ((DAT_0045ea70 == '\0') &&
                  (((uint)param_2[4] < 0xffc0 || (0xffff < (uint)param_2[4])))) {
            *param_2 = 0xe;
          }
          else {
            *param_2 = 0x11;
          }
          break;
        case 9:
          if (iVar3 == 0x1000000) {
            *param_2 = 0xe;
          }
          else if (iVar3 == 0x2000000) {
            *param_2 = 0x10;
            if (param_2[2] == 0) {
              if (0x3f < (uint)param_2[4]) {
                *param_2 = 0xe;
                FUN_004133a9((uint *)s_Absolute_address_too_large_to_us_00452858);
              }
            }
            else if ((DAT_0045f8fc == 2) && (0x3f < (uint)param_2[4])) {
              FUN_00413085((uint *)s_Absolute_address_too_large_to_us_00452894);
              return 0xffffffff;
            }
          }
          else if (iVar3 == 0x4000000) {
            *param_2 = 0xe;
            FUN_004133a9((uint *)s_I_O_short_absolute_address_canno_004528bc);
          }
          else if ((param_2[2] != 0) || (bVar1)) {
            *param_2 = 0xe;
          }
          else if ((uint)param_2[4] < 0x40) {
            *param_2 = 0x10;
          }
          else {
            *param_2 = 0xe;
          }
          break;
        default:
          FUN_00412fa0((uint *)s_Absolute_mode_select_failure_004528fc);
        }
        if (bVar1) {
          local_20 = FUN_004094bb(param_2);
        }
        else {
          local_20 = (uint *)0x0;
        }
        param_2[7] = local_20;
        uVar2 = 1;
      }
    }
  }
  return uVar2;
}


/* ==== FUN_0040800f @ 0040800f ==== */

int FUN_0040800f(void)

{
  int iVar1;
  
  iVar1 = FUN_004080dc(&DAT_0045f860);
  if (iVar1 == -1) {
    iVar1 = -1;
  }
  else if ((iVar1 < 0xe) || (0x15 < iVar1)) {
    iVar1 = -1;
  }
  return iVar1;
}


/* ==== FUN_00408046 @ 00408046 ==== */

undefined4 __cdecl FUN_00408046(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_004080dc((int *)&DAT_0045f860);
  if (iVar1 == -1) {
    if ((*DAT_0045f860 == 'N') || (*DAT_0045f860 == 'n')) {
      DAT_0045f860 = DAT_0045f860 + 1;
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  else if ((iVar1 < 0x16) || (0x1d < iVar1)) {
    FUN_00413085((uint *)s_Invalid_register_specified_for_o_00452960);
    uVar2 = 0;
  }
  else if (iVar1 + -0x16 == param_1 + -0xe) {
    uVar2 = 1;
  }
  else {
    FUN_00413085((uint *)s_Offset_register_number_must_be_t_0045291c);
    uVar2 = 0;
  }
  return uVar2;
}


