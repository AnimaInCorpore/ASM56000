/* arith: 50 functions from ASM56000 */

/* ==== FUN_004080dc @ 004080dc ==== */

int __cdecl FUN_004080dc(int *param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint local_108;
  uint local_104;
  int local_fc;
  uint local_f8;
  uint local_f4;
  uint local_f0;
  int local_e8;
  uint local_e4;
  uint local_e0;
  uint local_dc;
  int local_d4;
  uint local_d0;
  uint local_cc;
  int local_c8;
  uint local_c4;
  int local_c0;
  uint local_bc;
  uint local_b8;
  int local_b4;
  uint local_b0;
  int local_ac;
  uint local_a8;
  uint local_a4;
  int local_a0;
  uint local_9c;
  uint local_98;
  uint local_94;
  uint local_90;
  uint local_8c;
  uint local_88;
  uint local_7c;
  uint local_78;
  uint local_74;
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  int local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  int local_28;
  uint local_24;
  uint local_20;
  int local_18;
  uint local_14;
  
  iVar3 = *param_1;
  cVar1 = *(char *)*param_1;
  *param_1 = *param_1 + 1;
  if (__mb_cur_max < 2) {
    local_14 = *(ushort *)(_pctype + cVar1 * 2) & 1;
  }
  else {
    local_14 = _isctype((int)cVar1,1);
  }
  if (local_14 == 0) {
    local_18 = (int)cVar1;
  }
  else {
    local_18 = tolower((int)cVar1);
  }
  switch(local_18) {
  case 0x61:
    if (__mb_cur_max < 2) {
      local_20 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
    }
    else {
      local_20 = _isctype((int)*(char *)*param_1,0x107);
    }
    if ((local_20 == 0) && (*(char *)*param_1 != '_')) {
      return 2;
    }
    cVar1 = *(char *)*param_1;
    *param_1 = *param_1 + 1;
    if (__mb_cur_max < 2) {
      local_24 = *(ushort *)(_pctype + cVar1 * 2) & 1;
    }
    else {
      local_24 = _isctype((int)cVar1,1);
    }
    if (local_24 == 0) {
      local_28 = (int)cVar1;
    }
    else {
      local_28 = tolower((int)cVar1);
    }
    switch(local_28) {
    case 0x30:
      if (__mb_cur_max < 2) {
        local_30 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_30 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_30 == 0) && (*(char *)*param_1 != '_')) {
        return 8;
      }
      break;
    case 0x31:
      if (__mb_cur_max < 2) {
        local_3c = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_3c = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_3c == 0) && (*(char *)*param_1 != '_')) {
        return 10;
      }
      cVar1 = *(char *)*param_1;
      *param_1 = *param_1 + 1;
      if (cVar1 == '0') {
        if (__mb_cur_max < 2) {
          local_40 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
        }
        else {
          local_40 = _isctype((int)*(char *)*param_1,0x107);
        }
        if ((local_40 == 0) && (*(char *)*param_1 != '_')) {
          return 0x28;
        }
      }
      break;
    case 0x32:
      if (__mb_cur_max < 2) {
        local_34 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_34 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_34 == 0) && (*(char *)*param_1 != '_')) {
        return 0xc;
      }
      break;
    case 0x62:
      if (__mb_cur_max < 2) {
        local_38 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_38 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_38 == 0) && (*(char *)*param_1 != '_')) {
        return 0x26;
      }
    }
    break;
  case 0x62:
    if (__mb_cur_max < 2) {
      local_44 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
    }
    else {
      local_44 = _isctype((int)*(char *)*param_1,0x107);
    }
    if ((local_44 == 0) && (*(char *)*param_1 != '_')) {
      return 3;
    }
    cVar1 = *(char *)*param_1;
    *param_1 = *param_1 + 1;
    if (__mb_cur_max < 2) {
      local_48 = *(ushort *)(_pctype + cVar1 * 2) & 1;
    }
    else {
      local_48 = _isctype((int)cVar1,1);
    }
    if (local_48 == 0) {
      local_4c = (int)cVar1;
    }
    else {
      local_4c = tolower((int)cVar1);
    }
    switch(local_4c) {
    case 0x30:
      if (__mb_cur_max < 2) {
        local_54 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_54 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_54 == 0) && (*(char *)*param_1 != '_')) {
        return 9;
      }
      break;
    case 0x31:
      if (__mb_cur_max < 2) {
        local_60 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_60 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_60 == 0) && (*(char *)*param_1 != '_')) {
        return 0xb;
      }
      cVar1 = *(char *)*param_1;
      *param_1 = *param_1 + 1;
      if (cVar1 == '0') {
        if (__mb_cur_max < 2) {
          local_64 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
        }
        else {
          local_64 = _isctype((int)*(char *)*param_1,0x107);
        }
        if ((local_64 == 0) && (*(char *)*param_1 != '_')) {
          return 0x29;
        }
      }
      break;
    case 0x32:
      if (__mb_cur_max < 2) {
        local_58 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_58 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_58 == 0) && (*(char *)*param_1 != '_')) {
        return 0xd;
      }
      break;
    case 0x61:
      if (__mb_cur_max < 2) {
        local_5c = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_5c = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_5c == 0) && (*(char *)*param_1 != '_')) {
        return 0x27;
      }
    }
    break;
  case 99:
    cVar1 = *(char *)*param_1;
    *param_1 = *param_1 + 1;
    cVar2 = *(char *)*param_1;
    *param_1 = *param_1 + 1;
    if (__mb_cur_max < 2) {
      local_bc = *(ushort *)(_pctype + cVar1 * 2) & 1;
    }
    else {
      local_bc = _isctype((int)cVar1,1);
    }
    if (local_bc == 0) {
      local_c0 = (int)cVar1;
    }
    else {
      local_c0 = tolower((int)cVar1);
    }
    if (local_c0 == 99) {
      if (__mb_cur_max < 2) {
        local_c4 = *(ushort *)(_pctype + cVar2 * 2) & 1;
      }
      else {
        local_c4 = _isctype((int)cVar2,1);
      }
      if (local_c4 == 0) {
        local_c8 = (int)cVar2;
      }
      else {
        local_c8 = tolower((int)cVar2);
      }
      if (local_c8 == 0x72) {
        if (__mb_cur_max < 2) {
          local_cc = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
        }
        else {
          local_cc = _isctype((int)*(char *)*param_1,0x107);
        }
        if ((local_cc == 0) && (*(char *)*param_1 != '_')) {
          return 0x32;
        }
      }
    }
    break;
  case 0x6c:
    cVar1 = *(char *)*param_1;
    *param_1 = *param_1 + 1;
    if (__mb_cur_max < 2) {
      local_f8 = *(ushort *)(_pctype + cVar1 * 2) & 1;
    }
    else {
      local_f8 = _isctype((int)cVar1,1);
    }
    if (local_f8 == 0) {
      local_fc = (int)cVar1;
    }
    else {
      local_fc = tolower((int)cVar1);
    }
    if (local_fc == 0x61) {
      if (__mb_cur_max < 2) {
        local_104 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_104 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_104 == 0) && (*(char *)*param_1 != '_')) {
        return 0x2c;
      }
    }
    else if (local_fc == 99) {
      if (__mb_cur_max < 2) {
        local_108 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_108 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_108 == 0) && (*(char *)*param_1 != '_')) {
        return 0x2d;
      }
    }
    break;
  case 0x6d:
    cVar1 = *(char *)*param_1;
    *param_1 = *param_1 + 1;
    if (('/' < cVar1) && (cVar1 < '8')) {
      if (__mb_cur_max < 2) {
        local_98 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_98 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_98 == 0) && (*(char *)*param_1 != '_')) {
        return cVar1 + -0x12;
      }
    }
    if (__mb_cur_max < 2) {
      local_9c = *(ushort *)(_pctype + cVar1 * 2) & 1;
    }
    else {
      local_9c = _isctype((int)cVar1,1);
    }
    if (local_9c == 0) {
      local_a0 = (int)cVar1;
    }
    else {
      local_a0 = tolower((int)cVar1);
    }
    if (local_a0 == 0x72) {
      if (__mb_cur_max < 2) {
        local_a4 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_a4 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_a4 == 0) && (*(char *)*param_1 != '_')) {
        return 0x31;
      }
    }
    break;
  case 0x6e:
    cVar1 = *(char *)*param_1;
    *param_1 = *param_1 + 1;
    if (('/' < cVar1) && (cVar1 < '8')) {
      if (__mb_cur_max < 2) {
        local_94 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_94 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_94 == 0) && (*(char *)*param_1 != '_')) {
        return cVar1 + -0x1a;
      }
    }
    break;
  case 0x6f:
    cVar1 = *(char *)*param_1;
    *param_1 = *param_1 + 1;
    cVar2 = *(char *)*param_1;
    *param_1 = *param_1 + 1;
    if (__mb_cur_max < 2) {
      local_a8 = *(ushort *)(_pctype + cVar1 * 2) & 1;
    }
    else {
      local_a8 = _isctype((int)cVar1,1);
    }
    if (local_a8 == 0) {
      local_ac = (int)cVar1;
    }
    else {
      local_ac = tolower((int)cVar1);
    }
    if (local_ac == 0x6d) {
      if (__mb_cur_max < 2) {
        local_b0 = *(ushort *)(_pctype + cVar2 * 2) & 1;
      }
      else {
        local_b0 = _isctype((int)cVar2,1);
      }
      if (local_b0 == 0) {
        local_b4 = (int)cVar2;
      }
      else {
        local_b4 = tolower((int)cVar2);
      }
      if (local_b4 == 0x72) {
        if (__mb_cur_max < 2) {
          local_b8 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
        }
        else {
          local_b8 = _isctype((int)*(char *)*param_1,0x107);
        }
        if ((local_b8 == 0) && (*(char *)*param_1 != '_')) {
          return 0x2a;
        }
      }
    }
    break;
  case 0x72:
    cVar1 = *(char *)*param_1;
    *param_1 = *param_1 + 1;
    if (('/' < cVar1) && (cVar1 < '8')) {
      if (__mb_cur_max < 2) {
        local_90 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_90 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_90 == 0) && (*(char *)*param_1 != '_')) {
        return cVar1 + -0x22;
      }
    }
    break;
  case 0x73:
    cVar1 = *(char *)*param_1;
    *param_1 = *param_1 + 1;
    if (__mb_cur_max < 2) {
      local_d0 = *(ushort *)(_pctype + cVar1 * 2) & 1;
    }
    else {
      local_d0 = _isctype((int)cVar1,1);
    }
    if (local_d0 == 0) {
      local_d4 = (int)cVar1;
    }
    else {
      local_d4 = tolower((int)cVar1);
    }
    if (local_d4 == 0x70) {
      if (__mb_cur_max < 2) {
        local_e0 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_e0 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_e0 == 0) && (*(char *)*param_1 != '_')) {
        return 0x30;
      }
    }
    else if (local_d4 == 0x72) {
      if (__mb_cur_max < 2) {
        local_dc = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_dc = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_dc == 0) && (*(char *)*param_1 != '_')) {
        return 0x2b;
      }
    }
    else if (local_d4 == 0x73) {
      cVar1 = *(char *)*param_1;
      *param_1 = *param_1 + 1;
      if (__mb_cur_max < 2) {
        local_e4 = *(ushort *)(_pctype + cVar1 * 2) & 1;
      }
      else {
        local_e4 = _isctype((int)cVar1,1);
      }
      if (local_e4 == 0) {
        local_e8 = (int)cVar1;
      }
      else {
        local_e8 = tolower((int)cVar1);
      }
      if (local_e8 == 0x68) {
        if (__mb_cur_max < 2) {
          local_f0 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
        }
        else {
          local_f0 = _isctype((int)*(char *)*param_1,0x107);
        }
        if ((local_f0 == 0) && (*(char *)*param_1 != '_')) {
          return 0x2e;
        }
      }
      else if (local_e8 == 0x6c) {
        if (__mb_cur_max < 2) {
          local_f4 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
        }
        else {
          local_f4 = _isctype((int)*(char *)*param_1,0x107);
        }
        if ((local_f4 == 0) && (*(char *)*param_1 != '_')) {
          return 0x2f;
        }
      }
    }
    break;
  case 0x78:
    if (__mb_cur_max < 2) {
      local_68 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
    }
    else {
      local_68 = _isctype((int)*(char *)*param_1,0x107);
    }
    if ((local_68 == 0) && (*(char *)*param_1 != '_')) {
      return 0;
    }
    cVar1 = *(char *)*param_1;
    *param_1 = *param_1 + 1;
    if (cVar1 == '0') {
      if (__mb_cur_max < 2) {
        local_74 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_74 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_74 == 0) && (*(char *)*param_1 != '_')) {
        return 4;
      }
    }
    else if (cVar1 == '1') {
      if (__mb_cur_max < 2) {
        local_78 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_78 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_78 == 0) && (*(char *)*param_1 != '_')) {
        return 6;
      }
    }
    break;
  case 0x79:
    if (__mb_cur_max < 2) {
      local_7c = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
    }
    else {
      local_7c = _isctype((int)*(char *)*param_1,0x107);
    }
    if ((local_7c == 0) && (*(char *)*param_1 != '_')) {
      return 1;
    }
    cVar1 = *(char *)*param_1;
    *param_1 = *param_1 + 1;
    if (cVar1 == '0') {
      if (__mb_cur_max < 2) {
        local_88 = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_88 = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_88 == 0) && (*(char *)*param_1 != '_')) {
        return 5;
      }
    }
    else if (cVar1 == '1') {
      if (__mb_cur_max < 2) {
        local_8c = *(ushort *)(_pctype + *(char *)*param_1 * 2) & 0x107;
      }
      else {
        local_8c = _isctype((int)*(char *)*param_1,0x107);
      }
      if ((local_8c == 0) && (*(char *)*param_1 != '_')) {
        return 7;
      }
    }
  }
  *param_1 = iVar3;
  return -1;
}


/* ==== FUN_004094bb @ 004094bb ==== */

uint * __cdecl FUN_004094bb(undefined4 *param_1)

{
  uint *dst;
  uint uVar1;
  char local_40c [1024];
  int local_c;
  int local_8;
  
  if ((DAT_0045f864 == 0) || (DAT_0045f428 == '\0')) {
    dst = (uint *)0x0;
  }
  else {
    local_c = FUN_0043a768(param_1[1]);
    switch(*param_1) {
    case 10:
      local_8 = 0xc;
      break;
    case 0xb:
      local_8 = 8;
      break;
    case 0xc:
      local_8 = 1;
      break;
    case 0xd:
      local_8 = -1;
      break;
    default:
      local_8 = 0;
      break;
    case 0xf:
      local_8 = 0xc;
      break;
    case 0x10:
      local_8 = 6;
      break;
    case 0x11:
      local_8 = 0x56;
    }
    if (local_8 == 0) {
      sprintf(local_40c,s__s__d__d_00452994,&DAT_0045f428,local_c,0);
    }
    else {
      sprintf(local_40c,s__d__s__d__d_00452988,DAT_0045eb78,&DAT_0045f428,local_c,local_8);
    }
    uVar1 = strlen(local_40c);
    dst = (uint *)FUN_00439857(uVar1 + 1);
    strcpy((char *)dst,local_40c);
  }
  return dst;
}


/* ==== FUN_00409618 @ 00409618 ==== */

undefined4 __cdecl FUN_00409618(uint param_1,int param_2)

{
  if (param_2 == 6) {
    if (0x3f < param_1) {
      return 0;
    }
  }
  else if (param_2 == 8) {
    if (0xff < param_1) {
      return 0;
    }
  }
  else if (param_2 == 0xc) {
    if (0xfff < param_1) {
      return 0;
    }
  }
  else {
    FUN_00412fa0((uint *)s_Invalid_operand_size_004529a0);
  }
  return 1;
}


/* ==== FUN_00409680 @ 00409680 ==== */

undefined4 FUN_00409680(void)

{
  undefined4 uStack00000004;
  undefined4 uStack00000008;
  
  uStack00000008 = 0;
  uStack00000004 = 0;
  FUN_00412fa0((uint *)s_Expression_operator_failure_004529ec);
  return 0;
}


/* ==== FUN_004096ab @ 004096ab ==== */

double * __cdecl FUN_004096ab(double *param_1,double *param_2)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  float10 fVar5;
  float10 fVar6;
  int local_20;
  int local_1c;
  
  if ((*(int *)(param_1 + 2) == 0x100) && (*(int *)(param_2 + 2) == 0x100)) {
    iVar1 = FUN_004099d3((uint *)param_1,(uint *)param_2);
    if (iVar1 == 0) {
      param_1 = (double *)0x0;
    }
    else {
      bVar3 = ((ulonglong)param_1[1] & 0x800000) != 0;
      bVar4 = ((ulonglong)param_2[1] & 0x800000) != 0;
      if (((bVar3) && (bVar4)) ||
         (((*(int *)(param_1 + 1) + *(int *)(param_2 + 1) & 0x800000U) == 0 && ((bVar3 || (bVar4))))
         )) {
        local_1c = 1;
      }
      else {
        local_1c = 0;
      }
      *(uint *)(param_1 + 1) = *(int *)(param_1 + 1) + *(int *)(param_2 + 1) & 0xffffff;
      uVar2 = *(int *)((int)param_1 + 4) + *(int *)((int)param_2 + 4) + local_1c;
      bVar3 = ((ulonglong)*param_1 & 0x80000000000000) != 0;
      bVar4 = ((ulonglong)*param_2 & 0x80000000000000) != 0;
      if (((bVar3) && (bVar4)) || (((uVar2 & 0x800000) == 0 && ((bVar3 || (bVar4)))))) {
        local_20 = 1;
      }
      else {
        local_20 = 0;
      }
      *(uint *)((int)param_1 + 4) = uVar2 & 0xffffff;
      *(uint *)param_1 = *(int *)param_1 + *(int *)param_2 + local_20 & 0xff;
      FUN_004165e3((int *)param_1);
    }
  }
  else if ((((ulonglong)param_1[3] & 0x1000) == 0) && (((ulonglong)param_2[3] & 0x1000) == 0)) {
    fVar5 = FUN_0040b1e5(param_1);
    fVar6 = FUN_0040b1e5(param_2);
    *param_1 = (double)(fVar6 + (float10)(double)fVar5);
    *(undefined4 *)(param_1 + 2) = 0x200;
    *(undefined4 *)(param_1 + 4) = 4;
    *(undefined4 *)((int)param_1 + 0x1c) = 4;
    *(undefined4 *)((int)param_1 + 0x24) = 0;
    *(undefined4 *)(param_1 + 5) = 0;
    *(undefined4 *)((int)param_1 + 0x14) = 8;
  }
  else {
    FUN_004167ef((undefined4 *)param_1);
    FUN_004167ef((undefined4 *)param_2);
    FUN_00413085((uint *)s_Floating_point_not_allowed_in_re_00452a08);
    param_1 = (double *)0x0;
  }
  return param_1;
}


/* ==== FUN_004098e6 @ 004098e6 ==== */

double * __cdecl FUN_004098e6(double *param_1,double *param_2)

{
  float10 fVar1;
  float10 fVar2;
  
  if ((*(int *)(param_1 + 2) == 0x100) && (*(int *)(param_2 + 2) == 0x100)) {
    FUN_0040a80c(param_2);
    param_1 = FUN_004096ab(param_1,param_2);
  }
  else if ((((ulonglong)param_1[3] & 0x1000) == 0) && (((ulonglong)param_2[3] & 0x1000) == 0)) {
    fVar1 = FUN_0040b1e5(param_1);
    fVar2 = FUN_0040b1e5(param_2);
    *param_1 = (double)((float10)(double)fVar1 - fVar2);
    *(undefined4 *)(param_1 + 2) = 0x200;
    *(undefined4 *)(param_1 + 4) = 4;
    *(undefined4 *)((int)param_1 + 0x1c) = 4;
    *(undefined4 *)((int)param_1 + 0x24) = 0;
    *(undefined4 *)(param_1 + 5) = 0;
    *(undefined4 *)((int)param_1 + 0x14) = 8;
  }
  else {
    FUN_004167ef((undefined4 *)param_1);
    FUN_004167ef((undefined4 *)param_2);
    FUN_00413085((uint *)s_Floating_point_not_allowed_in_re_00452a3c);
    param_1 = (double *)0x0;
  }
  return param_1;
}


/* ==== FUN_004099d3 @ 004099d3 ==== */

undefined4 __cdecl FUN_004099d3(uint *param_1,uint *param_2)

{
  bool bVar1;
  int iVar2;
  
  if (((((*param_1 & 0x80) == 0) || ((*param_2 & 0x80) != 0)) &&
      (((*param_1 & 0x80) != 0 || ((*param_2 & 0x80) == 0)))) &&
     (((iVar2 = FUN_0040a7ea((int)param_1), iVar2 != 0 &&
       (iVar2 = FUN_0040a7ea((int)param_2), iVar2 != 0)) && ((param_1[6] & 0x8000000) == 0)))) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((param_1[7] != 4) && (param_2[7] != 4)) {
    if ((DAT_0044f7b4 != '\0') && (iVar2 = FUN_0043baf1(param_1[7],param_2[7]), iVar2 == 0xa2c2a)) {
      FUN_00413085((uint *)s_Expression_involves_incompatible_00452a70);
      FUN_004167ef(param_2);
      FUN_004167ef(param_1);
      return 0;
    }
    if (!bVar1) {
      FUN_00413085((uint *)s_Invalid_address_expression_00452aa0);
      FUN_004167ef(param_1);
      FUN_004167ef(param_2);
      return 0;
    }
    DAT_0045eb60 = 1;
  }
  if (((param_1[6] & 0x1000) != 0) && ((param_2[6] & 0x1000) != 0)) {
    if ((-1 < (int)param_1[0x10]) && ((-1 < (int)param_2[0x10] && (param_1[0x10] != param_2[0x10])))
       ) {
      FUN_00413085((uint *)s_Relative_terms_from_different_se_00452abc);
      FUN_004167ef(param_1);
      FUN_004167ef(param_2);
      return 0;
    }
    if (!bVar1) {
      FUN_00413085((uint *)s_Invalid_relative_expression_00452af0);
      FUN_004167ef(param_1);
      FUN_004167ef(param_2);
      return 0;
    }
  }
  return 1;
}


/* ==== FUN_00409ba7 @ 00409ba7 ==== */

double * __cdecl FUN_00409ba7(double *param_1,double *param_2)

{
  byte bVar1;
  float10 fVar2;
  float10 fVar3;
  int local_74;
  int local_70;
  uint local_68 [8];
  uint local_48 [8];
  uint local_28;
  uint local_24 [8];
  
  if ((*(int *)(param_1 + 2) != 0x100) || (*(int *)(param_2 + 2) != 0x100)) {
    fVar2 = FUN_0040b1e5(param_1);
    fVar3 = FUN_0040b1e5(param_2);
    *param_1 = (double)(fVar3 * (float10)(double)fVar2);
    *(undefined4 *)(param_1 + 2) = 0x200;
    *(undefined4 *)(param_1 + 4) = 4;
    *(undefined4 *)((int)param_1 + 0x1c) = 4;
    *(undefined4 *)((int)param_1 + 0x24) = 0;
    *(undefined4 *)(param_1 + 5) = 0;
    *(undefined4 *)((int)param_1 + 0x14) = 8;
    return param_1;
  }
  bVar1 = ((ulonglong)*param_1 & 0x80) != 0;
  if ((bool)bVar1) {
    FUN_0040a80c(param_1);
  }
  if (((ulonglong)*param_2 & 0x80) != 0) {
    FUN_0040a80c(param_2);
    bVar1 = bVar1 | 2;
  }
  FUN_0040ae41(*(uint *)param_1,*(uint *)((int)param_1 + 4),*(uint *)(param_1 + 1),local_68);
  FUN_0040ae41(*(uint *)param_2,*(uint *)((int)param_2 + 4),*(uint *)(param_2 + 1),local_24);
  FUN_0040ae41(0,0,0,local_48);
  local_28 = 0;
  for (local_74 = 0; local_74 < 7; local_74 = local_74 + 1) {
    for (local_70 = 0; local_70 <= local_74; local_70 = local_70 + 1) {
      local_28 = local_28 + local_68[local_70] * local_24[local_74 - local_70];
    }
    local_48[local_74] = local_28 & 0xff;
    local_28 = local_28 >> 8;
  }
  FUN_0040aece(local_48,(undefined4 *)param_1,(uint *)((int)param_1 + 4),(uint *)(param_1 + 1));
  if (bVar1 == 1) {
    FUN_0040a80c(param_1);
  }
  else {
    if (bVar1 == 2) {
      FUN_0040a80c(param_1);
    }
    else if (bVar1 != 3) goto LAB_00409d3a;
    FUN_0040a80c(param_2);
  }
LAB_00409d3a:
  FUN_004165e3((int *)param_1);
  return param_1;
}


/* ==== FUN_00409dae @ 00409dae ==== */

double * __cdecl FUN_00409dae(double *param_1,double *param_2)

{
  byte bVar1;
  float10 fVar2;
  uint local_18;
  double local_14;
  uint local_c;
  uint local_8;
  
  if ((*(int *)(param_1 + 2) != 0x100) || (*(int *)(param_2 + 2) != 0x100)) {
    fVar2 = FUN_0040b1e5(param_2);
    local_14 = (double)fVar2;
    if (local_14 != 0.0) {
      fVar2 = FUN_0040b1e5(param_1);
      *param_1 = (double)(fVar2 / (float10)local_14);
      *(undefined4 *)(param_1 + 2) = 0x200;
      *(undefined4 *)(param_1 + 4) = 4;
      *(undefined4 *)((int)param_1 + 0x1c) = 4;
      *(undefined4 *)((int)param_1 + 0x24) = 0;
      *(undefined4 *)(param_1 + 5) = 0;
      *(undefined4 *)((int)param_1 + 0x14) = 8;
      return param_1;
    }
    FUN_004167ef((undefined4 *)param_2);
    FUN_004167ef((undefined4 *)param_1);
    FUN_00413085((uint *)s_Divide_by_zero_00452b1c);
    return (double *)0x0;
  }
  if (((*(int *)param_2 == 0) && (*(int *)((int)param_2 + 4) == 0)) && (*(int *)(param_2 + 1) == 0))
  {
    FUN_004167ef((undefined4 *)param_2);
    FUN_004167ef((undefined4 *)param_1);
    FUN_00413085((uint *)s_Divide_by_zero_00452b0c);
    return (double *)0x0;
  }
  bVar1 = ((ulonglong)*param_1 & 0x80) != 0;
  if ((bool)bVar1) {
    FUN_0040a80c(param_1);
  }
  if (((ulonglong)*param_2 & 0x80) != 0) {
    FUN_0040a80c(param_2);
    bVar1 = bVar1 | 2;
  }
  FUN_0040ac4a(*(uint *)param_1,*(uint *)((int)param_1 + 4),*(uint *)(param_1 + 1),*(uint *)param_2,
               *(uint *)((int)param_2 + 4),*(uint *)(param_2 + 1),(undefined4 *)param_1,
               (uint *)((int)param_1 + 4),(uint *)(param_1 + 1),&local_c,&local_8,&local_18);
  if (bVar1 == 1) {
    FUN_0040a80c(param_1);
  }
  else {
    if (bVar1 == 2) {
      FUN_0040a80c(param_1);
    }
    else if (bVar1 != 3) goto LAB_00409ef6;
    FUN_0040a80c(param_2);
  }
LAB_00409ef6:
  FUN_004165e3((int *)param_1);
  return param_1;
}


/* ==== FUN_00409fa6 @ 00409fa6 ==== */

double * __cdecl FUN_00409fa6(double *param_1,double *param_2)

{
  float10 fVar1;
  float10 extraout_ST0;
  double y;
  undefined4 in_stack_ffffffe0;
  undefined4 in_stack_ffffffe4;
  uint uVar2;
  uint local_18;
  double local_14;
  undefined4 local_c;
  uint local_8;
  
  if ((*(int *)(param_1 + 2) != 0x100) || (*(int *)(param_2 + 2) != 0x100)) {
    fVar1 = FUN_0040b1e5(param_2);
    local_14 = (double)fVar1;
    if (local_14 != 0.0) {
      y = local_14;
      fVar1 = FUN_0040b1e5(param_1);
      fmod((double)fVar1,y,in_stack_ffffffe0,in_stack_ffffffe4);
      *param_1 = (double)extraout_ST0;
      *(undefined4 *)(param_1 + 2) = 0x200;
      *(undefined4 *)(param_1 + 4) = 4;
      *(undefined4 *)((int)param_1 + 0x1c) = 4;
      *(undefined4 *)((int)param_1 + 0x24) = 0;
      *(undefined4 *)(param_1 + 5) = 0;
      *(undefined4 *)((int)param_1 + 0x14) = 8;
      return param_1;
    }
    FUN_004167ef((undefined4 *)param_2);
    FUN_004167ef((undefined4 *)param_1);
    FUN_00413085((uint *)s_Divide_by_zero_00452b3c);
    return (double *)0x0;
  }
  if (((*(int *)param_2 == 0) && (*(int *)((int)param_2 + 4) == 0)) && (*(int *)(param_2 + 1) == 0))
  {
    FUN_004167ef((undefined4 *)param_2);
    FUN_004167ef((undefined4 *)param_1);
    FUN_00413085((uint *)s_Divide_by_zero_00452b2c);
    return (double *)0x0;
  }
  uVar2 = 0;
  if (((ulonglong)*param_1 & 0x80) != 0) {
    FUN_0040a80c(param_1);
    uVar2 = uVar2 | 1;
  }
  if (((ulonglong)*param_2 & 0x80) != 0) {
    FUN_0040a80c(param_2);
    uVar2 = uVar2 | 2;
  }
  FUN_0040ac4a(*(uint *)param_1,*(uint *)((int)param_1 + 4),*(uint *)(param_1 + 1),*(uint *)param_2,
               *(uint *)((int)param_2 + 4),*(uint *)(param_2 + 1),&local_c,&local_8,&local_18,
               (uint *)param_1,(uint *)((int)param_1 + 4),(uint *)(param_1 + 1));
  if (uVar2 == 1) {
    FUN_0040a80c(param_1);
  }
  else {
    if (uVar2 == 2) {
      FUN_0040a80c(param_1);
    }
    else if (uVar2 != 3) goto LAB_0040a0ee;
    FUN_0040a80c(param_2);
  }
LAB_0040a0ee:
  FUN_004165e3((int *)param_1);
  return param_1;
}


/* ==== FUN_0040a1ae @ 0040a1ae ==== */

uint * __cdecl FUN_0040a1ae(uint *param_1,uint *param_2)

{
  int iVar1;
  
  if ((param_1[4] == 0x100) && (param_2[4] == 0x100)) {
    if ((DAT_0045ea98 != '\0') && (iVar1 = FUN_004099d3(param_1,param_2), iVar1 == 0)) {
      return (uint *)0x0;
    }
    *param_1 = *param_1 & *param_2;
    param_1[1] = param_1[1] & param_2[1];
    param_1[2] = param_1[2] & param_2[2];
    FUN_004165e3((int *)param_1);
  }
  else {
    FUN_004167ef(param_1);
    FUN_004167ef(param_2);
    FUN_00413085((uint *)s_Illegal_operator_for_floating_po_00452b4c);
    param_1 = (uint *)0x0;
  }
  return param_1;
}


/* ==== FUN_0040a25b @ 0040a25b ==== */

uint * __cdecl FUN_0040a25b(uint *param_1,uint *param_2)

{
  int iVar1;
  
  if ((param_1[4] == 0x100) && (param_2[4] == 0x100)) {
    if ((DAT_0045ea98 != '\0') && (iVar1 = FUN_004099d3(param_1,param_2), iVar1 == 0)) {
      return (uint *)0x0;
    }
    *param_1 = *param_1 | *param_2;
    param_1[1] = param_1[1] | param_2[1];
    param_1[2] = param_1[2] | param_2[2];
    FUN_004165e3((int *)param_1);
  }
  else {
    FUN_004167ef(param_1);
    FUN_004167ef(param_2);
    FUN_00413085((uint *)s_Illegal_operator_for_floating_po_00452b78);
    param_1 = (uint *)0x0;
  }
  return param_1;
}


/* ==== FUN_0040a308 @ 0040a308 ==== */

uint * __cdecl FUN_0040a308(uint *param_1,uint *param_2)

{
  int iVar1;
  
  if ((param_1[4] == 0x100) && (param_2[4] == 0x100)) {
    if ((DAT_0045ea98 != '\0') && (iVar1 = FUN_004099d3(param_1,param_2), iVar1 == 0)) {
      return (uint *)0x0;
    }
    *param_1 = *param_1 ^ *param_2;
    param_1[1] = param_1[1] ^ param_2[1];
    param_1[2] = param_1[2] ^ param_2[2];
    FUN_004165e3((int *)param_1);
  }
  else {
    FUN_004167ef(param_1);
    FUN_004167ef(param_2);
    FUN_00413085((uint *)s_Illegal_operator_for_floating_po_00452ba4);
    param_1 = (uint *)0x0;
  }
  return param_1;
}


/* ==== FUN_0040a3b5 @ 0040a3b5 ==== */

uint * __cdecl FUN_0040a3b5(uint *param_1,int *param_2)

{
  int local_8;
  
  if ((param_1[4] == 0x100) && (param_2[4] == 0x100)) {
    if ((((*param_2 == 0) && (param_2[1] == 0)) && (local_8 = param_2[2], -1 < local_8)) &&
       (local_8 < 0x31)) {
      while (local_8 != 0) {
        *param_1 = *param_1 << 1;
        if ((param_1[1] & 0x800000) != 0) {
          *param_1 = *param_1 | 1;
        }
        param_1[1] = param_1[1] << 1;
        if ((param_1[2] & 0x800000) != 0) {
          param_1[1] = param_1[1] | 1;
        }
        param_1[2] = param_1[2] << 1;
        local_8 = local_8 + -1;
      }
      FUN_004165e3((int *)param_1);
    }
    else {
      FUN_004167ef(param_2);
      FUN_004167ef(param_1);
      FUN_00413085((uint *)s_Invalid_shift_amount_00452bd0);
      param_1 = (uint *)0x0;
    }
  }
  else {
    FUN_004167ef(param_1);
    FUN_004167ef(param_2);
    FUN_00413085((uint *)s_Illegal_operator_for_floating_po_00452be8);
    param_1 = (uint *)0x0;
  }
  return param_1;
}


/* ==== FUN_0040a4de @ 0040a4de ==== */

uint * __cdecl FUN_0040a4de(uint *param_1,int *param_2)

{
  int iVar1;
  int local_8;
  
  if ((param_1[4] == 0x100) && (param_2[4] == 0x100)) {
    if ((((*param_2 == 0) && (param_2[1] == 0)) && (local_8 = param_2[2], -1 < local_8)) &&
       (local_8 < 0x31)) {
      while (iVar1 = local_8 + -1, local_8 != 0) {
        param_1[2] = param_1[2] >> 1;
        if ((param_1[1] & 1) != 0) {
          param_1[2] = param_1[2] | 0x800000;
        }
        param_1[1] = param_1[1] >> 1;
        if ((*param_1 & 1) != 0) {
          param_1[1] = param_1[1] | 0x800000;
        }
        *param_1 = *param_1 >> 1;
        local_8 = iVar1;
        if ((*param_1 & 0x40) != 0) {
          *param_1 = *param_1 | 0x80;
        }
      }
      FUN_004165e3((int *)param_1);
    }
    else {
      FUN_004167ef(param_2);
      FUN_004167ef(param_1);
      FUN_00413085((uint *)s_Invalid_shift_amount_00452c14);
      param_1 = (uint *)0x0;
    }
  }
  else {
    FUN_004167ef(param_1);
    FUN_004167ef(param_2);
    FUN_00413085((uint *)s_Illegal_operator_for_floating_po_00452c2c);
    param_1 = (uint *)0x0;
  }
  return param_1;
}


/* ==== FUN_0040a628 @ 0040a628 ==== */

double * __cdecl FUN_0040a628(double *param_1,double *param_2)

{
  uint uVar1;
  undefined4 local_8;
  
  uVar1 = FUN_0040a95b(param_1);
  if (uVar1 != 0) {
    uVar1 = FUN_0040a95b(param_2);
    if (uVar1 != 0) {
      local_8 = 1;
      goto LAB_0040a65c;
    }
  }
  local_8 = 0;
LAB_0040a65c:
  *(undefined4 *)(param_1 + 1) = local_8;
  *(undefined4 *)param_1 = 0;
  *(undefined4 *)((int)param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 2) = 0x100;
  *(undefined4 *)(param_1 + 4) = 4;
  *(undefined4 *)((int)param_1 + 0x1c) = 4;
  *(undefined4 *)((int)param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 5) = 0;
  *(undefined4 *)((int)param_1 + 0x14) = 3;
  return param_1;
}


/* ==== FUN_0040a6bb @ 0040a6bb ==== */

double * __cdecl FUN_0040a6bb(double *param_1,double *param_2)

{
  uint uVar1;
  undefined4 local_8;
  
  uVar1 = FUN_0040a95b(param_1);
  if (uVar1 == 0) {
    uVar1 = FUN_0040a95b(param_2);
    if (uVar1 == 0) {
      local_8 = 0;
      goto LAB_0040a6ef;
    }
  }
  local_8 = 1;
LAB_0040a6ef:
  *(undefined4 *)(param_1 + 1) = local_8;
  *(undefined4 *)param_1 = 0;
  *(undefined4 *)((int)param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 2) = 0x100;
  *(undefined4 *)(param_1 + 4) = 4;
  *(undefined4 *)((int)param_1 + 0x1c) = 4;
  *(undefined4 *)((int)param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 5) = 0;
  *(undefined4 *)((int)param_1 + 0x14) = 3;
  return param_1;
}


/* ==== FUN_0040a74e @ 0040a74e ==== */

double * __cdecl FUN_0040a74e(double *param_1,double *param_2)

{
  FUN_0040aa08(0xb,param_1,param_2);
  return param_1;
}


/* ==== FUN_0040a768 @ 0040a768 ==== */

double * __cdecl FUN_0040a768(double *param_1,double *param_2)

{
  FUN_0040aa08(0xc,param_1,param_2);
  return param_1;
}


/* ==== FUN_0040a782 @ 0040a782 ==== */

double * __cdecl FUN_0040a782(double *param_1,double *param_2)

{
  FUN_0040aa08(0xd,param_1,param_2);
  return param_1;
}


/* ==== FUN_0040a79c @ 0040a79c ==== */

double * __cdecl FUN_0040a79c(double *param_1,double *param_2)

{
  FUN_0040aa08(0xe,param_1,param_2);
  return param_1;
}


/* ==== FUN_0040a7b6 @ 0040a7b6 ==== */

double * __cdecl FUN_0040a7b6(double *param_1,double *param_2)

{
  FUN_0040aa08(0xf,param_1,param_2);
  return param_1;
}


/* ==== FUN_0040a7d0 @ 0040a7d0 ==== */

double * __cdecl FUN_0040a7d0(double *param_1,double *param_2)

{
  FUN_0040aa08(0x10,param_1,param_2);
  return param_1;
}


/* ==== FUN_0040a7ea @ 0040a7ea ==== */

undefined4 __cdecl FUN_0040a7ea(int param_1)

{
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | *(int *)(param_1 + 4) << 0x18;
  return *(undefined4 *)(param_1 + 8);
}


/* ==== FUN_0040a80c @ 0040a80c ==== */

void __cdecl FUN_0040a80c(double *param_1)

{
  if (*(int *)(param_1 + 2) == 0x200) {
    *param_1 = -*param_1;
  }
  else {
    FUN_0040a8b1((uint *)param_1);
    if (*(int *)(param_1 + 1) == 0xffffff) {
      if (*(int *)((int)param_1 + 4) == 0xffffff) {
        *(int *)param_1 = *(int *)param_1 + 1;
        *(uint *)param_1 = *(uint *)param_1 & 0xff;
      }
      *(int *)((int)param_1 + 4) = *(int *)((int)param_1 + 4) + 1;
      *(uint *)((int)param_1 + 4) = *(uint *)((int)param_1 + 4) & 0xffffff;
    }
    *(int *)(param_1 + 1) = *(int *)(param_1 + 1) + 1;
    *(uint *)(param_1 + 1) = *(uint *)(param_1 + 1) & 0xffffff;
  }
  return;
}


/* ==== FUN_0040a8b1 @ 0040a8b1 ==== */

void __cdecl FUN_0040a8b1(uint *param_1)

{
  *param_1 = ~*param_1 & 0xff;
  param_1[1] = ~param_1[1] & 0xffffff;
  param_1[2] = ~param_1[2] & 0xffffff;
  return;
}


/* ==== FUN_0040a8f0 @ 0040a8f0 ==== */

void __cdecl FUN_0040a8f0(double *param_1)

{
  uint uVar1;
  
  uVar1 = FUN_0040a95b(param_1);
  *(uint *)(param_1 + 1) = (uint)(uVar1 == 0);
  *(undefined4 *)param_1 = 0;
  *(undefined4 *)((int)param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 2) = 0x100;
  *(undefined4 *)(param_1 + 4) = 4;
  *(undefined4 *)((int)param_1 + 0x1c) = 4;
  *(undefined4 *)((int)param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 5) = 0;
  *(undefined4 *)((int)param_1 + 0x14) = 3;
  return;
}


/* ==== FUN_0040a95b @ 0040a95b ==== */

uint __cdecl FUN_0040a95b(double *param_1)

{
  uint local_10;
  uint local_c;
  uint local_8;
  
  if (*(int *)(param_1 + 2) == 0x200) {
    local_c = (uint)(*param_1 != 0.0);
    local_8 = local_c;
    if ((local_c != 0) && (*param_1 < 0.0)) {
      local_8 = 0xffffffff;
    }
  }
  else {
    if (((*(int *)param_1 == 0) && (*(int *)((int)param_1 + 4) == 0)) &&
       (*(int *)(param_1 + 1) == 0)) {
      local_10 = 0;
    }
    else {
      local_10 = 1;
    }
    local_8 = local_10;
    if ((local_10 != 0) && (((ulonglong)*param_1 & 0x80) != 0)) {
      local_8 = 0xffffffff;
    }
  }
  return local_8;
}


/* ==== FUN_0040aa08 @ 0040aa08 ==== */

void __cdecl FUN_0040aa08(undefined4 param_1,double *param_2,double *param_3)

{
  float10 fVar1;
  float10 fVar2;
  uint local_8;
  
  if ((*(int *)(param_2 + 2) == 0x100) && (*(int *)(param_3 + 2) == 0x100)) {
    if (*(uint *)param_2 < *(uint *)param_3) {
      local_8 = 0xffffffff;
    }
    else if (*(uint *)param_3 < *(uint *)param_2) {
      local_8 = 1;
    }
    else if (*(uint *)((int)param_2 + 4) < *(uint *)((int)param_3 + 4)) {
      local_8 = 0xffffffff;
    }
    else if (*(uint *)((int)param_3 + 4) < *(uint *)((int)param_2 + 4)) {
      local_8 = 1;
    }
    else if (*(uint *)(param_2 + 1) < *(uint *)(param_3 + 1)) {
      local_8 = 0xffffffff;
    }
    else if (*(uint *)(param_3 + 1) < *(uint *)(param_2 + 1)) {
      local_8 = 1;
    }
    else {
      local_8 = 0;
    }
    if ((local_8 != 0) &&
       (((((ulonglong)*param_2 & 0x80) != 0 && (((ulonglong)*param_3 & 0x80) == 0)) ||
        ((((ulonglong)*param_2 & 0x80) == 0 && (((ulonglong)*param_3 & 0x80) != 0)))))) {
      local_8 = -local_8;
    }
  }
  else {
    fVar1 = FUN_0040b1e5(param_2);
    fVar2 = FUN_0040b1e5(param_3);
    if ((double)fVar2 <= (double)fVar1) {
      if ((double)fVar1 <= (double)fVar2) {
        local_8 = 0;
      }
      else {
        local_8 = 1;
      }
    }
    else {
      local_8 = 0xffffffff;
    }
  }
  switch(param_1) {
  case 0xb:
    local_8 = (uint)(local_8 == 0xffffffff);
    break;
  case 0xc:
    local_8 = (uint)(local_8 == 1);
    break;
  case 0xd:
    local_8 = (uint)(local_8 == 0);
    break;
  case 0xe:
    local_8 = (uint)(local_8 != 1);
    break;
  case 0xf:
    local_8 = (uint)(local_8 != 0xffffffff);
    break;
  case 0x10:
    local_8 = (uint)(local_8 != 0);
    break;
  default:
    FUN_00412fa0((uint *)s_Compare_select_failure_00452c58);
  }
  *(uint *)(param_2 + 1) = local_8;
  *(undefined4 *)param_2 = 0;
  *(undefined4 *)((int)param_2 + 4) = 0;
  *(undefined4 *)(param_2 + 2) = 0x100;
  *(undefined4 *)(param_2 + 4) = 4;
  *(undefined4 *)((int)param_2 + 0x1c) = 4;
  *(undefined4 *)((int)param_2 + 0x24) = 0;
  *(undefined4 *)(param_2 + 5) = 0;
  *(undefined4 *)((int)param_2 + 0x14) = 3;
  return;
}


/* ==== FUN_0040ac4a @ 0040ac4a ==== */

void __cdecl
FUN_0040ac4a(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
            undefined4 *param_7,uint *param_8,uint *param_9,uint *param_10,uint *param_11,
            uint *param_12)

{
  int iVar1;
  uint uVar2;
  uint local_ac [8];
  uint local_8c;
  uint local_88;
  undefined1 local_84 [28];
  uint local_68 [8];
  uint local_48 [8];
  int local_28;
  uint local_24 [8];
  
  iVar1 = FUN_0040adde(param_4,param_5,param_6,param_1,param_2,param_3);
  if (iVar1 < 1) {
    FUN_0040ae41(0,0,0,local_68);
    FUN_0040ae41(0,0,0,&local_88);
    FUN_0040ae41(0,0,0,local_24);
    FUN_0040ae41(param_1,param_2,param_3,local_48);
    FUN_0040ae41(param_4,param_5,param_6,local_ac);
    local_8c = FUN_0040b1b1((int)local_ac);
    local_28 = FUN_0040b1b1((int)local_48);
    for (local_28 = local_28 + -2; -1 < local_28; local_28 = local_28 + -1) {
      FUN_0040af6b((int)&local_88,(int)local_84,local_8c - 1);
      local_88 = local_48[local_28];
      uVar2 = FUN_0040af95((int)local_ac,(int)&local_88,local_8c,(int)local_24);
      local_68[local_28] = uVar2;
    }
    FUN_0040aece(local_68,param_7,param_8,param_9);
    FUN_0040aece(&local_88,param_10,param_11,param_12);
  }
  else {
    *param_10 = param_1;
    *param_11 = param_2;
    *param_12 = param_3;
    *param_9 = 0;
    *param_8 = 0;
    *param_7 = 0;
  }
  return;
}


/* ==== FUN_0040adde @ 0040adde ==== */

int __cdecl
FUN_0040adde(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6)

{
  undefined4 local_8;
  
  if (param_1 == param_4) {
    if (param_2 == param_5) {
      if (param_3 == param_6) {
        local_8 = 0;
      }
      else {
        local_8 = (-(uint)(param_6 < param_3) & 2) - 1;
      }
    }
    else {
      local_8 = (-(uint)(param_5 < param_2) & 2) - 1;
    }
  }
  else {
    local_8 = (-(uint)(param_4 < param_1) & 2) - 1;
  }
  return local_8;
}


/* ==== FUN_0040ae41 @ 0040ae41 ==== */

void __cdecl FUN_0040ae41(uint param_1,uint param_2,uint param_3,uint *param_4)

{
  int local_8;
  
  *param_4 = param_3 & 0xff;
  param_4[3] = param_2 & 0xff;
  param_4[6] = param_1 & 0xff;
  for (local_8 = 1; local_8 < 3; local_8 = local_8 + 1) {
    param_3 = param_3 >> 8;
    param_4[local_8] = param_3 & 0xff;
    param_2 = param_2 >> 8;
    param_4[local_8 + 3] = param_2 & 0xff;
  }
  param_4[7] = 0;
  return;
}


/* ==== FUN_0040aece @ 0040aece ==== */

void __cdecl FUN_0040aece(uint *param_1,undefined4 *param_2,uint *param_3,uint *param_4)

{
  int local_8;
  
  *param_4 = 0;
  *param_3 = 0;
  *param_2 = 0;
  for (local_8 = 2; 0 < local_8; local_8 = local_8 + -1) {
    *param_3 = *param_3 | param_1[local_8 + 3];
    *param_3 = *param_3 << 8;
    *param_4 = *param_4 | param_1[local_8];
    *param_4 = *param_4 << 8;
  }
  *param_3 = *param_3 | param_1[3];
  *param_4 = *param_4 | *param_1;
  return;
}


/* ==== FUN_0040af6b @ 0040af6b ==== */

void __cdecl FUN_0040af6b(int param_1,int param_2,int param_3)

{
  while (param_3 = param_3 + -1, -1 < param_3) {
    *(undefined4 *)(param_2 + param_3 * 4) = *(undefined4 *)(param_1 + param_3 * 4);
  }
  return;
}


/* ==== FUN_0040af95 @ 0040af95 ==== */

uint __cdecl FUN_0040af95(int param_1,int param_2,uint param_3,int param_4)

{
  uint uVar1;
  bool bVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  uint local_10;
  int local_c;
  
  local_c = param_3 - 1;
  do {
    if (*(int *)(param_1 + local_c * 4) != 0) {
      local_10 = *(uint *)(param_2 + local_c * 4) / *(uint *)(param_1 + local_c * 4);
      do {
        FUN_0040b095(local_10,param_1,param_4,param_3);
        local_10 = local_10 - 1;
        bVar2 = FUN_0040b0f1(param_4,param_2,param_3);
        uVar1 = local_10;
      } while (CONCAT31(extraout_var,bVar2) == 0);
      do {
        local_10 = uVar1;
        FUN_0040b095(local_10 + 1,param_1,param_4,param_3);
        bVar2 = FUN_0040b0f1(param_4,param_2,param_3);
        uVar1 = local_10 + 1;
      } while (CONCAT31(extraout_var_00,bVar2) != 0);
      FUN_0040b095(local_10,param_1,param_4,param_3);
      FUN_0040b14d(param_4,param_2,param_3);
      return local_10;
    }
    local_c = local_c + -1;
  } while (-1 < local_c);
  return 0;
}


/* ==== FUN_0040b095 @ 0040b095 ==== */

void __cdecl FUN_0040b095(int param_1,int param_2,int param_3,uint param_4)

{
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  for (local_c = 0; local_c < param_4; local_c = local_c + 1) {
    local_8 = local_8 + param_1 * *(int *)(param_2 + local_c * 4);
    *(uint *)(param_3 + local_c * 4) = local_8 & 0xff;
    local_8 = local_8 >> 8;
  }
  return;
}


/* ==== FUN_0040b0f1 @ 0040b0f1 ==== */

bool __cdecl FUN_0040b0f1(int param_1,int param_2,int param_3)

{
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  for (local_c = 0; local_c < param_3; local_c = local_c + 1) {
    local_8 = (uint)((int)((*(int *)(param_2 + local_c * 4) - *(int *)(param_1 + local_c * 4)) -
                          local_8) < 0);
  }
  return local_8 == 0;
}


/* ==== FUN_0040b14d @ 0040b14d ==== */

void __cdecl FUN_0040b14d(int param_1,int param_2,int param_3)

{
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  for (local_c = 0; local_c < param_3; local_c = local_c + 1) {
    local_8 = (*(int *)(param_2 + local_c * 4) - *(int *)(param_1 + local_c * 4)) - local_8;
    *(uint *)(param_2 + local_c * 4) = local_8 & 0xff;
    local_8 = (uint)((int)local_8 < 0);
  }
  return;
}


/* ==== FUN_0040b1b1 @ 0040b1b1 ==== */

int __cdecl FUN_0040b1b1(int param_1)

{
  undefined4 local_8;
  
  for (local_8 = 7; (-1 < local_8 && (*(int *)(param_1 + local_8 * 4) == 0)); local_8 = local_8 + -1
      ) {
  }
  return local_8 + 2;
}


/* ==== FUN_0040b1e5 @ 0040b1e5 ==== */

float10 __cdecl FUN_0040b1e5(double *param_1)

{
  int iVar1;
  float10 fVar2;
  
  if (*(int *)(param_1 + 2) == 0x200) {
    fVar2 = (float10)*param_1;
  }
  else {
    iVar1 = *(int *)((int)param_1 + 0x14);
    if (iVar1 == 3) {
      fVar2 = FUN_0040b312(*(uint *)(param_1 + 1));
    }
    else if ((iVar1 < 6) || (7 < iVar1)) {
      fVar2 = (float10)0.0;
    }
    else {
      fVar2 = FUN_0040b391(*(uint *)((int)param_1 + 4),*(uint *)(param_1 + 1));
    }
  }
  return fVar2;
}


/* ==== FUN_0040b24c @ 0040b24c ==== */

void __cdecl FUN_0040b24c(uint param_1,uint param_2,int param_3,int *param_4)

{
  ulonglong uVar1;
  
  param_4[2] = 0;
  param_4[1] = 0;
  *param_4 = 0;
  if (param_3 == 3) {
    uVar1 = FUN_0040b376(param_1,param_2);
    param_4[2] = (int)uVar1;
    if ((param_4[2] & 0x800000U) != 0) {
      param_4[1] = 0xffffff;
      *param_4 = 0xff;
    }
  }
  else if (((5 < param_3) && (param_3 < 8)) &&
          (FUN_0040b477(param_1,param_2,(uint *)(param_4 + 1),(uint *)(param_4 + 2)),
          (param_4[1] & 0x800000U) != 0)) {
    *param_4 = 0xff;
  }
  param_4[4] = 0x100;
  FUN_004165e3(param_4);
  return;
}


/* ==== FUN_0040b312 @ 0040b312 ==== */

float10 __cdecl FUN_0040b312(uint param_1)

{
  bool bVar1;
  double local_20;
  
  bVar1 = (param_1 & 0x800000) != 0;
  if (bVar1) {
    param_1 = (~param_1 & 0xffffff) + 1;
  }
  local_20 = (double)param_1;
  if (bVar1) {
    local_20 = -local_20;
  }
  return (float10)local_20;
}


/* ==== FUN_0040b376 @ 0040b376 ==== */

ulonglong FUN_0040b376(void)

{
  ulonglong uVar1;
  
  uVar1 = _ftol();
  return uVar1 & 0xffffffff00ffffff;
}


/* ==== FUN_0040b391 @ 0040b391 ==== */

float10 __cdecl FUN_0040b391(uint param_1,uint param_2)

{
  uint uVar1;
  bool bVar2;
  float10 fVar3;
  double local_34;
  
  if ((param_1 == 0) && (param_2 == 0)) {
    fVar3 = (float10)0.0;
  }
  else {
    bVar2 = (param_1 & 0x800000) != 0;
    if (bVar2) {
      uVar1 = (~param_2 & 0xffffff) + 1;
      param_2 = uVar1 & 0xffffff;
      param_1 = (~param_1 & 0xffffff) + (uint)(uVar1 >> 0x18 != 0) & 0xffffff;
    }
    local_34 = (double)param_1 * 16777216.0 + (double)param_2;
    if (bVar2) {
      local_34 = -local_34;
    }
    fVar3 = (float10)local_34;
  }
  return fVar3;
}


/* ==== FUN_0040b477 @ 0040b477 ==== */

void __cdecl FUN_0040b477(uint param_1,uint param_2,uint *param_3,uint *param_4)

{
  float10 extraout_ST0;
  longlong lVar1;
  undefined4 in_stack_ffffffec;
  uint uVar2;
  
  fabs((double)CONCAT44(param_2,param_1),in_stack_ffffffec);
  if ((float10)16777216.0 <= extraout_ST0) {
    lVar1 = _ftol();
    *param_3 = (uint)lVar1 & 0xffffff;
    lVar1 = _ftol();
    *param_4 = (uint)lVar1 & 0xffffff;
  }
  else {
    if (0.0 <= (double)CONCAT44(param_2,param_1)) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0xffffff;
    }
    *param_3 = uVar2;
    lVar1 = _ftol();
    *param_4 = (uint)lVar1;
    *param_4 = *param_4 & 0xffffff;
  }
  return;
}


/* ==== FUN_0040b53d @ 0040b53d ==== */

float10 __cdecl FUN_0040b53d(double *param_1)

{
  int iVar1;
  float10 fVar2;
  
  if (*(int *)(param_1 + 2) == 0x200) {
    fVar2 = (float10)*param_1;
  }
  else {
    iVar1 = *(int *)((int)param_1 + 0x14);
    if (iVar1 == 3) {
      fVar2 = FUN_0040b67c(*(uint *)(param_1 + 1));
    }
    else if ((iVar1 < 6) || (7 < iVar1)) {
      fVar2 = (float10)0.0;
    }
    else {
      fVar2 = FUN_0040b8ed((uint3)*(undefined4 *)((int)param_1 + 4),*(uint *)(param_1 + 1));
    }
  }
  return fVar2;
}


/* ==== FUN_0040b5a4 @ 0040b5a4 ==== */

void __cdecl FUN_0040b5a4(undefined4 param_1,undefined4 param_2,int param_3,int *param_4)

{
  uint uVar1;
  
  param_4[2] = 0;
  param_4[1] = 0;
  *param_4 = 0;
  if (param_3 == 3) {
    uVar1 = FUN_0040b6bf((double)CONCAT44(param_2,param_1),3);
    param_4[2] = uVar1;
    if ((param_4[2] & 0x800000U) != 0) {
      param_4[1] = 0xffffff;
      *param_4 = 0xff;
    }
  }
  else if (((5 < param_3) && (param_3 < 8)) &&
          (FUN_0040b9b7((double)CONCAT44(param_2,param_1),(uint *)(param_4 + 1),
                        (uint *)(param_4 + 2),param_3), (param_4[1] & 0x800000U) != 0)) {
    *param_4 = 0xff;
  }
  param_4[6] = param_4[6] | 0x100000;
  param_4[4] = 0x100;
  FUN_004165e3(param_4);
  return;
}


/* ==== FUN_0040b67c @ 0040b67c ==== */

float10 __cdecl FUN_0040b67c(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = param_1 & 0xffffff;
  uVar2 = param_1 & 0x800000;
  param_1 = uVar1;
  if (uVar2 != 0) {
    param_1 = uVar1 | 0xff800000;
  }
  return (float10)((double)(int)param_1 / 8388608.0);
}


/* ==== FUN_0040b6bf @ 0040b6bf ==== */

uint __cdecl FUN_0040b6bf(double param_1)

{
  longlong lVar1;
  uint local_18;
  double local_c;
  
  if (-1.0 <= param_1) {
    if (param_1 < 1.0) {
      if (0.0 <= param_1) {
        local_c = param_1 * 8388608.0 + 0.5;
      }
      else {
        local_c = param_1 * 8388608.0 + -0.5;
      }
      lVar1 = _ftol();
      local_18 = (uint)lVar1;
      if (local_c - (double)(int)local_18 == 0.0) {
        local_18 = local_18 & 0xfffffffe;
      }
      if (0x7fffff < (int)local_18) {
        local_18 = 0x7fffff;
      }
      local_18 = local_18 & 0xffffff;
    }
    else {
      FUN_004133a9((uint *)s_Expression_value_outside_fractio_00452c9c);
      local_18 = 0x7fffff;
    }
  }
  else {
    FUN_004133a9((uint *)s_Expression_value_outside_fractio_00452c70);
    local_18 = 0xff800000;
  }
  return local_18;
}


/* ==== FUN_0040b797 @ 0040b797 ==== */

uint __cdecl FUN_0040b797(double param_1,uint param_2)

{
  longlong lVar1;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_18;
  double local_c;
  
  if (param_2 == 0xff) {
    local_20 = 0x80;
  }
  else {
    if (param_2 == 0xfff) {
      local_24 = 0x800;
    }
    else {
      if (param_2 == 0xffff) {
        local_28 = 0x8000;
      }
      else {
        local_28 = (-(uint)(param_2 != 0xfffff) & 0x780000) + 0x80000;
      }
      local_24 = local_28;
    }
    local_20 = local_24;
  }
  if (-1.0 <= param_1) {
    if (param_1 < 1.0) {
      if (0.0 <= param_1) {
        local_c = param_1 * (double)local_20 + 0.5;
      }
      else {
        local_c = param_1 * (double)local_20 + -0.5;
      }
      lVar1 = _ftol();
      local_18 = (uint)lVar1;
      if (local_c - (double)(int)local_18 == 0.0) {
        local_18 = local_18 & 0xfffffffe;
      }
      if ((int)(~local_20 & param_2) < (int)local_18) {
        local_18 = ~local_20 & param_2;
      }
      local_18 = local_18 & param_2;
    }
    else {
      FUN_004133a9((uint *)s_Expression_value_outside_fractio_00452cf4);
      local_18 = param_2 & 0x7fffff;
    }
  }
  else {
    FUN_004133a9((uint *)s_Expression_value_outside_fractio_00452cc8);
    local_18 = param_2 & 0xff800000;
  }
  return local_18;
}


