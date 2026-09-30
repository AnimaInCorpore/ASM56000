/* scs: 32 functions from ASM56000 */

/* ==== FUN_004317e0 @ 004317e0 ==== */

void __cdecl FUN_004317e0(char *param_1,char *param_2)

{
  uint local_8;
  
  PTR_DAT_0044f818 = param_2;
  for (; (*param_1 != '\0' && (*param_1 != ';')); param_1 = param_1 + 1) {
    *param_2 = *param_1;
    param_2 = param_2 + 1;
  }
  while( true ) {
    if (__mb_cur_max < 2) {
      local_8 = *(ushort *)(_pctype + param_2[-1] * 2) & 8;
    }
    else {
      local_8 = _isctype((int)param_2[-1],8);
    }
    if (local_8 == 0) break;
    param_2 = param_2 + -1;
  }
  PTR_DAT_0044f820 = param_2;
  PTR_DAT_0044f81c = param_2;
  *param_2 = '\0';
  PTR_DAT_0044f824 = param_2 + 1;
  param_2 = PTR_DAT_0044f824;
  if (param_1[1] != ';') {
    for (; *param_1 != '\0'; param_1 = param_1 + 1) {
      *param_2 = *param_1;
      param_2 = param_2 + 1;
    }
  }
  *param_2 = '\0';
  return;
}


/* ==== FUN_004318d1 @ 004318d1 ==== */

bool __thiscall FUN_004318d1(void *this,int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  DAT_0045ea54 = '\x01' - (DAT_0044f77c != '\0');
  iVar1 = (**(code **)(param_1 + 8))(this);
  if (iVar1 != 0) {
    FUN_0041bdca(' ');
    puVar2 = FUN_00420b7b(DAT_0045fc84);
    FUN_00420cd5((undefined *)puVar2);
    FUN_0041f9ab(DAT_0045fc84);
    DAT_0045fc88 = 0;
    DAT_0045fc84 = (int *)0x0;
  }
  else {
    FUN_0041f9ab(DAT_0045fc84);
    DAT_0045fc88 = 0;
    DAT_0045fc84 = (int *)0x0;
    FUN_0041bdca(' ');
  }
  DAT_0045ea54 = 1;
  return iVar1 != 0;
}


/* ==== FUN_00431984 @ 00431984 ==== */

undefined4 FUN_00431984(void)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  undefined3 extraout_var;
  undefined4 uVar4;
  int local_74;
  int local_68 [19];
  undefined4 local_1c;
  uint *local_18;
  int *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  bVar1 = false;
  bVar2 = false;
  local_8 = 1;
  local_18 = (uint *)s__BREAK_cannot_appear_within_one_i_004581e0;
  DAT_0045f860 = PTR_DAT_0044f818;
  DAT_0045ea50 = 1;
  bVar3 = FUN_00432d3b(local_68);
  local_10 = CONCAT31(extraout_var,bVar3);
  DAT_0045ea50 = 0;
  if ((local_10 == 0) || (local_68[0] == 0)) {
    local_74 = DAT_0045fc90;
    while ((local_74 != 0 && (!bVar1))) {
      switch(*(undefined1 *)(local_74 + 4)) {
      default:
        break;
      case 5:
        DAT_0045ea50 = 1;
        local_c = FUN_0041b685(local_8);
        DAT_0045ea50 = 0;
        if (local_c != 0) {
          FUN_00413085(local_18);
        }
        if ((local_10 == 0) && (!bVar2)) {
          FUN_00432cee((uint *)s_enddo_00458248);
        }
      case 3:
      case 6:
      case 0xb:
        bVar1 = true;
        if (local_10 == 0) {
          FUN_00432c82(local_74);
        }
        else {
          local_14 = FUN_00433ad5(0);
          local_1c = 2;
          FUN_00432bc8((int)local_68,local_74,local_14);
          FUN_00433870(local_68);
          FUN_004398b5((undefined *)local_14);
        }
        break;
      case 0x12:
        bVar2 = true;
      }
      local_74 = *(int *)(local_74 + 8);
    }
    if (bVar1) {
      uVar4 = 1;
    }
    else {
      FUN_004133a9((uint *)s_No_looping_construct_found____BR_00458250);
      uVar4 = 0;
    }
  }
  else {
    FUN_00413085((uint *)s_Syntax_error___invalid_expressio_0045821c);
    uVar4 = 0;
  }
  return uVar4;
}


/* ==== FUN_00431b47 @ 00431b47 ==== */

bool FUN_00431b47(void)

{
  bool bVar1;
  int iVar2;
  int *local_20;
  int *local_1c;
  int *local_c;
  
  local_1c = (int *)0x0;
  local_c = (int *)0x0;
  bVar1 = false;
  FUN_0043b007(0);
  local_20 = DAT_0045fc90;
  while ((local_20 != (int *)0x0 && (!bVar1))) {
    switch((char)local_20[1]) {
    case '\x05':
      DAT_0045ea50 = 1;
      iVar2 = FUN_0041b685(0);
      DAT_0045ea50 = 0;
      if (iVar2 != 0) {
        FUN_00413085((uint *)s__CONTINUE_cannot_appear_immediat_0045827c);
      }
      if (local_1c == (int *)0x0) {
        local_1c = FUN_00433ad5(0x11);
        if (local_c == (int *)0x0) {
          local_1c[2] = (int)DAT_0045fc90;
          DAT_0045fc90 = local_1c;
        }
        else {
          local_1c[2] = local_c[2];
          local_c[2] = (int)local_1c;
        }
      }
      local_20 = local_1c;
    case '\f':
    case '\x0e':
    case '\x0f':
    case '\x12':
      FUN_00432c82(local_20);
      bVar1 = true;
      break;
    default:
      break;
    case '\x11':
      if (local_1c == (int *)0x0) {
        local_1c = local_20;
      }
    }
    local_c = local_20;
    local_20 = (int *)local_20[2];
  }
  if (!bVar1) {
    FUN_004133a9((uint *)s_No_looping_construct_found____CO_004582b0);
  }
  return bVar1;
}


/* ==== FUN_00431d53 @ 00431d53 ==== */

undefined4 FUN_00431d53(void)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  undefined *puVar4;
  int *piVar5;
  undefined4 *puVar6;
  
  if (DAT_0045ebb0 == 0x2000000) {
    cVar2 = '<';
  }
  else {
    cVar2 = (-(DAT_0045ebb0 != 0x1000000) & 0xe2U) + 0x3e;
  }
  FUN_0043b007(0);
  if ((DAT_0045fc90 == 0) || (*(char *)(DAT_0045fc90 + 4) != '\x0f')) {
    DAT_0045f860 = 0;
    FUN_00413085((uint *)s__ENDF_without_associated__FOR_st_00458308);
    uVar3 = 0;
  }
  else {
    puVar4 = (undefined *)FUN_00433b34();
    FUN_00433b5f(puVar4);
    FUN_004398b5(puVar4);
    piVar5 = (int *)FUN_00433aa7();
    iVar1 = piVar5[0x24];
    sprintf(&DAT_0045f220,s_move__s__s_00458330,*piVar5,PTR_DAT_0044f938);
    FUN_00432cee((uint *)&DAT_0045f220);
    if (iVar1 == 0) {
      puVar4 = &DAT_00458340;
    }
    else {
      puVar4 = &DAT_0045833c;
    }
    sprintf(&DAT_0045f220,s__s__s__s_00458344,puVar4,PTR_DAT_0044f934,PTR_DAT_0044f938);
    FUN_00432cee((uint *)&DAT_0045f220);
    sprintf(&DAT_0045f220,s_move__s__s_00458350,PTR_DAT_0044f938,*piVar5);
    FUN_00432cee((uint *)&DAT_0045f220);
    FUN_004338fa(piVar5);
    FUN_004398b5((undefined *)piVar5);
    if ((DAT_0045fc90 == 0) || (*(char *)(DAT_0045fc90 + 4) != '\x10')) {
      DAT_0045f860 = 0;
      FUN_00413085((uint *)s__ENDF_without_associated__FOR_st_0045835c);
      uVar3 = 0;
    }
    else {
      puVar4 = (undefined *)FUN_00433b34();
      FUN_00433b5f(puVar4);
      FUN_004398b5(puVar4);
      sprintf(&DAT_0045f220,s_cmp__s__s_00458384,PTR_DAT_0044f93c,PTR_DAT_0044f938);
      FUN_00432cee((uint *)&DAT_0045f220);
      if ((DAT_0045fc90 == 0) || (*(char *)(DAT_0045fc90 + 4) != '\a')) {
        DAT_0045f860 = 0;
        FUN_00413085((uint *)s__ENDF_without_associated__FOR_st_00458390);
        uVar3 = 0;
      }
      else {
        puVar6 = (undefined4 *)FUN_00433b34();
        sprintf(&DAT_0045f220,s__c_s__c_s_05d_004583c0,0x6a,PTR_DAT_0044f99c,(int)cVar2,
                PTR_DAT_0044f99c,*puVar6);
        FUN_00432cee((uint *)&DAT_0045f220);
        FUN_004398b5((undefined *)puVar6);
        if ((DAT_0045fc90 == 0) || (*(char *)(DAT_0045fc90 + 4) != '\x03')) {
          DAT_0045f860 = 0;
          FUN_00413085((uint *)s__ENDF_without_associated__FOR_st_004583d0);
          uVar3 = 0;
        }
        else {
          puVar4 = (undefined *)FUN_00433b34();
          FUN_00433b5f(puVar4);
          FUN_004398b5(puVar4);
          uVar3 = 1;
        }
      }
    }
  }
  return uVar3;
}


/* ==== FUN_00432030 @ 00432030 ==== */

undefined4 FUN_00432030(void)

{
  undefined4 uVar1;
  undefined *va0;
  
  FUN_0043b007(0);
  if ((DAT_0045fc90 == 0) || (*(char *)(DAT_0045fc90 + 4) != '\x04')) {
    DAT_0045f860 = 0;
    FUN_00413085((uint *)s__ENDI_without_associated__IF_sta_004583f8);
    uVar1 = 0;
  }
  else {
    va0 = (undefined *)FUN_00433b34();
    FUN_00433b5f(va0);
    FUN_004398b5(va0);
    uVar1 = 1;
  }
  return uVar1;
}


/* ==== FUN_00432099 @ 00432099 ==== */

undefined4 FUN_00432099(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  FUN_0043b007(0);
  if ((DAT_0045fc90 == 0) ||
     (((*(char *)(DAT_0045fc90 + 4) != '\x05' && (*(char *)(DAT_0045fc90 + 4) != '\x11')) &&
      (*(char *)(DAT_0045fc90 + 4) != '\x12')))) {
    DAT_0045f860 = 0;
    FUN_00413085((uint *)s__ENDL_without_associated__LOOP_s_00458420);
    uVar1 = 0;
  }
  else {
    if (*(char *)(DAT_0045fc90 + 4) == '\x12') {
      puVar2 = (undefined *)FUN_00433b34();
      FUN_00432c82(puVar2);
      FUN_004398b5(puVar2);
    }
    if (*(char *)(DAT_0045fc90 + 4) == '\x11') {
      puVar2 = (undefined *)FUN_00433b34();
      FUN_00433b5f(puVar2);
      FUN_004398b5(puVar2);
      FUN_00432cee((uint *)&DAT_0045844c);
    }
    if ((DAT_0045fc90 == 0) || (*(char *)(DAT_0045fc90 + 4) != '\x05')) {
      DAT_0045f860 = 0;
      FUN_00413085((uint *)s__ENDL_without_associated__LOOP_s_00458454);
      uVar1 = 0;
    }
    else {
      puVar2 = (undefined *)FUN_00433b34();
      FUN_00433b5f(puVar2);
      FUN_004398b5(puVar2);
      uVar1 = 1;
    }
  }
  return uVar1;
}


/* ==== FUN_004321c0 @ 004321c0 ==== */

undefined4 FUN_004321c0(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  FUN_0043b007(0);
  if ((DAT_0045fc90 == 0) || (*(char *)(DAT_0045fc90 + 4) != '\f')) {
    DAT_0045f860 = 0;
    FUN_00413085((uint *)s__ENDW_without_associated__WHILE_s_00458480);
    uVar1 = 0;
  }
  else {
    puVar2 = (undefined *)FUN_00433b34();
    FUN_00432c82(puVar2);
    FUN_004398b5(puVar2);
    if ((DAT_0045fc90 == 0) || (*(char *)(DAT_0045fc90 + 4) != '\x06')) {
      DAT_0045f860 = 0;
      FUN_00413085((uint *)s__ENDW_without_associated__WHILE_s_004584ac);
      uVar1 = 0;
    }
    else {
      puVar2 = (undefined *)FUN_00433b34();
      FUN_00433b5f(puVar2);
      FUN_004398b5(puVar2);
      uVar1 = 1;
    }
  }
  return uVar1;
}


/* ==== FUN_0043227c @ 0043227c ==== */

bool FUN_0043227c(void)

{
  bool bVar1;
  int *va0;
  int *piVar2;
  int *va0_00;
  int *piVar3;
  int *piVar4;
  undefined3 extraout_var;
  int iVar5;
  
  va0 = FUN_00433ad5(7);
  piVar2 = FUN_00433ad5(0xf);
  va0_00 = FUN_00433ad5(0x10);
  piVar3 = FUN_00433ad5(3);
  piVar4 = (int *)FUN_00439857(0x98);
  bVar1 = FUN_004330dd(piVar4);
  bVar1 = CONCAT31(extraout_var,bVar1) != 0;
  if (bVar1) {
    sprintf(&DAT_0045f220,s_move__s__s_004584d8,piVar4[9],PTR_DAT_0044f938);
    FUN_00432cee((uint *)&DAT_0045f220);
    sprintf(&DAT_0045f220,s_move__s__s_004584e4,PTR_DAT_0044f938,*piVar4);
    FUN_00432cee((uint *)&DAT_0045f220);
    sprintf(&DAT_0045f220,s_move__s__s_004584f0,piVar4[0x12],PTR_DAT_0044f93c);
    FUN_00432cee((uint *)&DAT_0045f220);
    sprintf(&DAT_0045f220,s_move__s__s_004584fc,piVar4[0x1b],PTR_DAT_0044f934);
    FUN_00432cee((uint *)&DAT_0045f220);
    FUN_00433a8a((int)piVar4);
    FUN_00432c82(va0_00);
    FUN_00433b5f(va0);
    FUN_00433b1a((int)piVar3);
    iVar5 = 0x432410;
    FUN_00433b1a((int)piVar3);
    FUN_00433b1a(iVar5);
    FUN_00433b1a((int)piVar2);
  }
  else {
    FUN_004398b5((undefined *)va0);
    FUN_004398b5((undefined *)piVar2);
    FUN_004398b5((undefined *)va0_00);
    FUN_004398b5((undefined *)piVar3);
    FUN_004338fa(piVar4);
    FUN_004398b5((undefined *)piVar4);
  }
  return bVar1;
}


/* ==== FUN_00432434 @ 00432434 ==== */

undefined4 FUN_00432434(void)

{
  char *va0;
  int *va1;
  int iVar1;
  undefined4 uVar2;
  
  va0 = (char *)FUN_00433ad5(8);
  va1 = FUN_00433ad5(4);
  iVar1 = FUN_004328bc(va0,va1);
  if ((iVar1 == 3) || (iVar1 == 0)) {
    FUN_00433b5f(va0);
    FUN_004398b5(va0);
    FUN_00433b1a(0x4324b5);
    uVar2 = 1;
  }
  else {
    DAT_0045f860 = 0;
    if (iVar1 != -1) {
      va0 = s_Syntax_error___invalid_statement_00458508;
      FUN_00413085((uint *)s_Syntax_error___invalid_statement_00458508);
    }
    FUN_004398b5(va0);
    FUN_004398b5((undefined *)0x432499);
    uVar2 = 0;
  }
  return uVar2;
}


/* ==== FUN_004324d9 @ 004324d9 ==== */

undefined4 FUN_004324d9(void)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int local_28;
  int local_24;
  int local_14;
  int *local_8;
  
  FUN_0043b007(1);
  DAT_0045f860 = PTR_DAT_0044f818;
  if (*PTR_DAT_0044f818 == '\0') {
    piVar1 = FUN_00433ad5(5);
    FUN_00433b1a((int)piVar1);
    local_8 = FUN_00433ad5(0x12);
    FUN_00433b1a((int)local_8);
    FUN_00433b5f(local_8);
    uVar2 = 1;
  }
  else {
    iVar3 = FUN_00439c56((int)&local_28,7);
    if (iVar3 == 0) {
      uVar2 = 0;
    }
    else {
      if (local_24 == 4) {
        iVar3 = FUN_004060d8(0,&local_28,0x11,0,0,2);
        if (iVar3 == 0) {
          return 0;
        }
        if ((local_28 == 1) && (local_14 == 0x2e)) {
          DAT_0045f860 = (undefined *)0x0;
          FUN_00413085((uint *)s_Illegal_use_of_SSH_as_loop_count_00458534);
          return 0;
        }
      }
      else {
        iVar3 = FUN_004060d8(0,&local_28,0,1,4,0);
        if (iVar3 == 0) {
          return 0;
        }
      }
      piVar1 = FUN_00433ad5(5);
      sprintf(&DAT_0045f220,s_do__s__s_05d_00458560,PTR_DAT_0044f818,PTR_DAT_0044f99c,*piVar1);
      FUN_00432cee((uint *)&DAT_0045f220);
      FUN_00433b1a((int)piVar1);
      uVar2 = 1;
    }
  }
  return uVar2;
}


/* ==== FUN_00432623 @ 00432623 ==== */

undefined4 FUN_00432623(void)

{
  int *piVar1;
  
  FUN_0043b007(0);
  piVar1 = FUN_00433ad5(10);
  FUN_00433b5f(piVar1);
  FUN_00433b1a((int)piVar1);
  piVar1 = FUN_00433ad5(0xb);
  FUN_00433b1a((int)piVar1);
  piVar1 = FUN_00433ad5(0xe);
  FUN_00433b1a((int)piVar1);
  return 1;
}


/* ==== FUN_00432691 @ 00432691 ==== */

undefined4 FUN_00432691(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  int iVar3;
  undefined *local_c;
  
  if ((DAT_0045fc90 == 0) || (*(char *)(DAT_0045fc90 + 4) != '\x0e')) {
    DAT_0045f860 = 0;
    FUN_00413085((uint *)s__UNTIL_without_associated__REPEA_00458570);
    uVar1 = 0;
  }
  else {
    puVar2 = (undefined *)FUN_00433b34();
    FUN_00433b5f(puVar2);
    FUN_004398b5(puVar2);
    if ((DAT_0045fc90 == 0) || (*(char *)(DAT_0045fc90 + 4) != '\v')) {
      DAT_0045f860 = 0;
      FUN_00413085((uint *)s__UNTIL_without_associated__REPEA_0045859c);
      uVar1 = 0;
    }
    else {
      local_c = (undefined *)FUN_00433b34();
      if ((DAT_0045fc90 == 0) || (*(char *)(DAT_0045fc90 + 4) != '\n')) {
        DAT_0045f860 = 0;
        FUN_00413085((uint *)s__UNTIL_without_associated__REPEA_004585c8);
        uVar1 = 0;
      }
      else {
        puVar2 = (undefined *)FUN_00433b34();
        iVar3 = FUN_004328bc(local_c,puVar2);
        if (iVar3 == 0) {
          FUN_00433b5f(local_c);
          FUN_004398b5((undefined *)0x4327c2);
          FUN_004398b5(puVar2);
          uVar1 = 1;
        }
        else {
          DAT_0045f860 = 0;
          if (iVar3 != -1) {
            local_c = (undefined *)0x43279a;
            FUN_00413085((uint *)s_Syntax_error___invalid_statement_004585f4);
          }
          FUN_004398b5(local_c);
          FUN_004398b5(puVar2);
          uVar1 = 0;
        }
      }
    }
  }
  return uVar1;
}


/* ==== FUN_004327e6 @ 004327e6 ==== */

undefined4 FUN_004327e6(void)

{
  int *va0;
  char *va0_00;
  int *va1;
  int iVar1;
  undefined4 uVar2;
  
  va0 = FUN_00433ad5(0xc);
  va0_00 = (char *)FUN_00433ad5(0);
  va1 = FUN_00433ad5(6);
  FUN_00433b5f(va0);
  iVar1 = FUN_004328bc(va0_00,va1);
  if ((iVar1 == 4) || (iVar1 == 0)) {
    FUN_00433b5f(va0_00);
    FUN_004398b5(va0_00);
    FUN_00433b1a(0x43288c);
    FUN_00433b1a((int)va1);
    uVar2 = 1;
  }
  else {
    DAT_0045f860 = 0;
    if (iVar1 != -1) {
      va0_00 = s_Syntax_error___invalid_statement_00458620;
      FUN_00413085((uint *)s_Syntax_error___invalid_statement_00458620);
    }
    FUN_004398b5(va0_00);
    FUN_004398b5((undefined *)0x432864);
    FUN_004398b5((undefined *)va1);
    uVar2 = 0;
  }
  return uVar2;
}


/* ==== FUN_004328bc @ 004328bc ==== */

int FUN_004328bc(void)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  int local_54 [19];
  int local_8;
  
  DAT_0045f860 = PTR_DAT_0044f818;
  do {
    bVar1 = FUN_00432d3b(local_54);
    if (CONCAT31(extraout_var,bVar1) == 0) {
      return -1;
    }
    if (local_54[0] != 0) {
      FUN_00432926(local_54);
    }
    FUN_00432bc8((int)local_54,in_stack_00000004,in_stack_00000008);
    FUN_00433870(local_54);
  } while ((local_8 == 1) || (local_8 == 2));
  return local_8;
}


/* ==== FUN_00432926 @ 00432926 ==== */

/* WARNING: Removing unreachable block (ram,0x00432a45) */
/* WARNING: Removing unreachable block (ram,0x00432b05) */

void __cdecl FUN_00432926(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_2c [9];
  undefined1 local_8;
  
  local_8 = 0;
  if ((param_1[6] != DAT_0044f948) || (param_1[0x10] != DAT_0044f944)) {
    if ((param_1[6] == DAT_0044f944) && (param_1[0x10] == DAT_0044f948)) {
      if ((*(char *)(param_1[9] + 4) == '\x04') || (*(char *)(param_1[9] + 4) == '\x0f')) {
        puVar2 = param_1;
        puVar3 = local_2c;
        for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar2 = param_1 + 10;
        puVar3 = param_1;
        for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar2 = local_2c;
        puVar3 = param_1 + 10;
        for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
      }
      else {
        sprintf(&DAT_0045f220,s_move__s__s_0045864c,PTR_DAT_0044f938,PTR_DAT_0044f93c);
        FUN_00432cee((uint *)&DAT_0045f220);
        sprintf(&DAT_0045f220,s_tfr__s__s__s__s_00458658,PTR_DAT_0044f934,PTR_DAT_0044f938,
                PTR_DAT_0044f93c,PTR_DAT_0044f934);
        FUN_00432cee((uint *)&DAT_0045f220);
      }
    }
    else if (param_1[6] == DAT_0044f948) {
      local_8 = 0;
      sprintf(&DAT_0045f220,s_move__s__s_00458674,param_1[10],PTR_DAT_0044f934);
      FUN_00432cee((uint *)&DAT_0045f220);
    }
    else if (param_1[0x10] == DAT_0044f948) {
      sprintf(&DAT_0045f220,s_move__s__s_00458680,PTR_DAT_0044f938,PTR_DAT_0044f934);
      FUN_00432cee((uint *)&DAT_0045f220);
      sprintf(&DAT_0045f220,s_move__s__s_0045868c,*param_1,PTR_DAT_0044f938);
      FUN_00432cee((uint *)&DAT_0045f220);
    }
    else if (param_1[0x10] == DAT_0044f944) {
      local_8 = 0;
      sprintf(&DAT_0045f220,s_move__s__s_004586a0,*param_1,PTR_DAT_0044f938);
      FUN_00432cee((uint *)&DAT_0045f220);
    }
    else {
      sprintf(&DAT_0045f220,s_move__s__s_004586ac,*param_1,PTR_DAT_0044f938);
      FUN_00432cee((uint *)&DAT_0045f220);
      sprintf(&DAT_0045f220,s_move__s__s_004586b8,param_1[10],PTR_DAT_0044f934);
      FUN_00432cee((uint *)&DAT_0045f220);
    }
  }
  sprintf(&DAT_0045f220,s_cmp__s__s_004586c4,PTR_DAT_0044f934,PTR_DAT_0044f938);
  FUN_00432cee((uint *)&DAT_0045f220);
  return;
}


/* ==== FUN_00432bc8 @ 00432bc8 ==== */

void __cdecl FUN_00432bc8(int param_1)

{
  char cVar1;
  undefined4 *in_stack_00000008;
  undefined4 *in_stack_0000000c;
  
  if (DAT_0045ebb0 == 0x2000000) {
    cVar1 = '<';
  }
  else {
    cVar1 = (-(DAT_0045ebb0 != 0x1000000) & 0xe2U) + 0x3e;
  }
  if (*(int *)(param_1 + 0x4c) == 2) {
    sprintf(&DAT_0045f220,PTR_s_j_s__c_s_05d_004586d0,**(undefined4 **)(param_1 + 0x24),(int)cVar1,
            PTR_DAT_0044f99c,*in_stack_00000008);
  }
  else {
    sprintf(&DAT_0045f220,PTR_s_j_s__c_s_05d_004586d0,
            (&PTR_DAT_0044ebd0)[*(char *)(*(int *)(param_1 + 0x24) + 5) * 2],(int)cVar1,
            PTR_DAT_0044f99c,*in_stack_0000000c);
  }
  FUN_00432cee((uint *)&DAT_0045f220);
  return;
}


/* ==== FUN_00432c82 @ 00432c82 ==== */

void FUN_00432c82(void)

{
  char cVar1;
  undefined4 *in_stack_00000004;
  
  if (DAT_0045ebb0 == 0x2000000) {
    cVar1 = '<';
  }
  else {
    cVar1 = (-(DAT_0045ebb0 != 0x1000000) & 0xe2U) + 0x3e;
  }
  sprintf(&DAT_0045f220,s_jmp__c_s_05d_004586e4,(int)cVar1,PTR_DAT_0044f99c,*in_stack_00000004);
  FUN_00432cee((uint *)&DAT_0045f220);
  return;
}


/* ==== FUN_00432cee @ 00432cee ==== */

void __cdecl FUN_00432cee(uint *param_1)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = FUN_0041f6e2(param_1,(undefined4 *)0x0);
  piVar1 = piVar2;
  if (DAT_0045fc84 != (int *)0x0) {
    *(int **)((int)DAT_0045fc88 + 8) = piVar2;
    piVar1 = DAT_0045fc84;
  }
  DAT_0045fc84 = piVar1;
  DAT_0045fc88 = piVar2;
  return;
}


/* ==== FUN_00432d3b @ 00432d3b ==== */

bool __cdecl FUN_00432d3b(int *param_1)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char local_20;
  uint local_1c;
  char local_18;
  uint local_14;
  char *local_8;
  
  bVar1 = true;
  uVar2 = strlen(PTR_DAT_0044f940 + 2);
  param_1[10] = 0;
  *param_1 = 0;
  param_1[0x12] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[0x13] = 0;
  local_8 = FUN_0043377d();
  if (DAT_0045f220 != '<') {
    DAT_0045f860 = &DAT_0045f220;
    iVar3 = FUN_00439c56((int)(param_1 + 1),9);
    iVar4 = FUN_004061ae(0,param_1 + 1,0x11,1,6,6);
    bVar1 = iVar4 != 0 && iVar3 != 0;
    uVar5 = strlen(&DAT_0045f220);
    iVar3 = FUN_00439857(uVar5 + 1 + uVar2);
    *param_1 = iVar3;
    strcpy((char *)*param_1,&DAT_0045f220);
    DAT_0045f860 = local_8;
    local_8 = FUN_0043377d();
  }
  if (((DAT_0045f220 == '<') && (DAT_0045f223 == '>')) && (DAT_0045f224 == '\0')) {
    if (__mb_cur_max < 2) {
      local_14 = *(ushort *)(_pctype + DAT_0045f221 * 2) & 1;
    }
    else {
      local_14 = _isctype((int)DAT_0045f221,1);
    }
    if (local_14 == 0) {
      local_18 = DAT_0045f221;
    }
    else {
      iVar3 = tolower((int)DAT_0045f221);
      local_18 = (char)iVar3;
    }
    DAT_0045f221 = local_18;
    if (__mb_cur_max < 2) {
      local_1c = *(ushort *)(_pctype + DAT_0045f222 * 2) & 1;
    }
    else {
      local_1c = _isctype((int)DAT_0045f222,1);
    }
    if (local_1c == 0) {
      local_20 = DAT_0045f222;
    }
    else {
      iVar3 = tolower((int)DAT_0045f222);
      local_20 = (char)iVar3;
    }
    DAT_0045f222 = local_20;
    DAT_0045f223 = '\0';
    iVar3 = FUN_00439267(&DAT_0045f221);
    param_1[9] = iVar3;
    if (param_1[9] == 0) {
      DAT_0045f860 = (char *)0x0;
      FUN_00413085((uint *)s_Syntax_error___invalid_condition_00458720);
      bVar1 = false;
    }
  }
  else {
    DAT_0045f860 = (char *)0x0;
    FUN_00413085((uint *)s_Syntax_error___invalid_condition_004586f4);
    bVar1 = false;
  }
  DAT_0045f860 = local_8;
  pcVar6 = FUN_0043377d();
  iVar3 = FUN_00433984();
  param_1[0x13] = iVar3;
  if (param_1[0x13] == -1) {
    DAT_0045f860 = &DAT_0045f220;
    iVar3 = FUN_00439c56((int)(param_1 + 0xb),9);
    if (iVar3 == 0) {
      bVar1 = false;
    }
    iVar3 = FUN_004061ae(0,param_1 + 0xb,0x11,1,6,6);
    if (iVar3 == 0) {
      bVar1 = false;
    }
    uVar5 = strlen(&DAT_0045f220);
    iVar3 = FUN_00439857(uVar5 + 1 + uVar2);
    param_1[10] = iVar3;
    strcpy((char *)param_1[10],&DAT_0045f220);
    DAT_0045f860 = pcVar6;
    pcVar6 = FUN_0043377d();
    iVar3 = FUN_00433984();
    param_1[0x13] = iVar3;
    if (param_1[0x13] == -1) {
      DAT_0045f860 = (char *)0x0;
      FUN_00413085((uint *)s_Syntax_error___invalid_compound_o_0045876c);
      bVar1 = false;
    }
    DAT_0045f860 = pcVar6;
    if (!bVar1) {
      FUN_00433870(param_1);
    }
  }
  else {
    if (*param_1 != 0) {
      DAT_0045f860 = (char *)0x0;
      FUN_00413085((uint *)s_Syntax_error___missing_operand_0045874c);
      bVar1 = false;
    }
    if (!bVar1) {
      FUN_00433870(param_1);
    }
  }
  return bVar1;
}


/* ==== FUN_004330dd @ 004330dd ==== */

bool __cdecl FUN_004330dd(int *param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int local_214;
  char local_20c [516];
  char *local_8;
  
  local_214 = 1;
  param_1[0x1b] = 0;
  param_1[0x12] = 0;
  param_1[9] = 0;
  *param_1 = 0;
  param_1[0x23] = 0;
  param_1[0x1a] = 0;
  param_1[0x11] = 0;
  param_1[8] = 0;
  DAT_0045f860 = PTR_DAT_0044f818;
  local_8 = FUN_0043377d();
  DAT_0045f860 = &DAT_0045f220;
  iVar3 = FUN_00439c56((int)(param_1 + 1),9);
  iVar4 = FUN_004061ae(0,param_1 + 1,0x11,1,6,0);
  bVar2 = iVar4 != 0 && iVar3 != 0;
  uVar5 = strlen(&DAT_0045f220);
  iVar3 = FUN_00439857(uVar5 + 1);
  *param_1 = iVar3;
  strcpy((char *)*param_1,&DAT_0045f220);
  DAT_0045f860 = local_8;
  local_8 = FUN_0043377d();
  if ((DAT_0045f220 != '=') || (DAT_0045f221 != '\0')) {
    DAT_0045f860 = (char *)0x0;
    FUN_00413085((uint *)s_Syntax_error___invalid_assignmen_00458798);
    bVar2 = false;
  }
  DAT_0045f860 = local_8;
  local_8 = FUN_0043377d();
  DAT_0045f860 = &DAT_0045f220;
  iVar3 = FUN_00439c56((int)(param_1 + 10),9);
  if (iVar3 == 0) {
    bVar2 = false;
  }
  iVar3 = FUN_004061ae(0,param_1 + 10,0x11,1,6,6);
  if (iVar3 == 0) {
    bVar2 = false;
  }
  uVar5 = strlen(&DAT_0045f220);
  iVar3 = FUN_00439857(uVar5 + 1);
  param_1[9] = iVar3;
  strcpy((char *)param_1[9],&DAT_0045f220);
  DAT_0045f860 = local_8;
  local_8 = FUN_0043377d();
  cVar1 = strcpy(local_20c,&DAT_0045f220);
  FUN_0043b836((char *)CONCAT31(extraout_var,cVar1));
  if (((local_20c[0] != DAT_004587c4) || (iVar3 = strcmp(local_20c,&DAT_004587c8), iVar3 != 0)) &&
     (local_214 = strcmp(local_20c,s_downto_004587cc), local_214 != 0)) {
    DAT_0045f860 = (char *)0x0;
    FUN_00413085((uint *)s_Syntax_error___expected_keyword_T_004587d4);
    bVar2 = false;
  }
  if (local_214 == 0) {
    param_1[0x24] = 1;
  }
  else {
    param_1[0x24] = 0;
  }
  DAT_0045f860 = local_8;
  local_8 = FUN_0043377d();
  DAT_0045f860 = &DAT_0045f220;
  iVar3 = FUN_00439c56((int)(param_1 + 0x13),9);
  if (iVar3 == 0) {
    bVar2 = false;
  }
  iVar3 = FUN_004061ae(0,param_1 + 0x13,0x11,1,6,6);
  if (iVar3 == 0) {
    bVar2 = false;
  }
  uVar5 = strlen(&DAT_0045f220);
  iVar3 = FUN_00439857(uVar5 + 1);
  param_1[0x12] = iVar3;
  strcpy((char *)param_1[0x12],&DAT_0045f220);
  DAT_0045f860 = local_8;
  local_8 = FUN_0043377d();
  cVar1 = strcpy(local_20c,&DAT_0045f220);
  FUN_0043b836((char *)CONCAT31(extraout_var_00,cVar1));
  if ((DAT_0045f220 == '\0') ||
     ((local_20c[0] == DAT_00458804 && (iVar3 = strcmp(local_20c,&DAT_00458808), iVar3 == 0)))) {
    strcpy(&DAT_0045f220,&DAT_0045880c);
    uVar5 = strlen(&DAT_0045f220);
    iVar3 = FUN_00439857(uVar5 + 1);
    param_1[0x1b] = iVar3;
    strcpy((char *)param_1[0x1b],&DAT_0045f220);
    param_1[0x1c] = 9;
    param_1[0x20] = 1;
    if (param_1[8] != 0) {
      FUN_004398b5((undefined *)param_1[8]);
      param_1[8] = 0;
    }
    if (param_1[0x11] != 0) {
      FUN_004398b5((undefined *)param_1[0x11]);
      param_1[0x11] = 0;
    }
    if (param_1[0x1a] != 0) {
      FUN_004398b5((undefined *)param_1[0x1a]);
      param_1[0x1a] = 0;
    }
    if (param_1[0x23] != 0) {
      FUN_004398b5((undefined *)param_1[0x23]);
      param_1[0x23] = 0;
    }
  }
  else {
    if ((local_20c[0] != DAT_00458810) || (iVar3 = strcmp(local_20c,&DAT_00458814), iVar3 != 0)) {
      DAT_0045f860 = (char *)0x0;
      FUN_00413085((uint *)s_Syntax_error___expected_keyword_B_00458818);
      bVar2 = false;
    }
    DAT_0045f860 = local_8;
    local_8 = FUN_0043377d();
    DAT_0045f860 = &DAT_0045f220;
    iVar3 = FUN_00439c56((int)(param_1 + 0x1c),9);
    if (iVar3 == 0) {
      bVar2 = false;
    }
    iVar3 = FUN_004061ae(0,param_1 + 0x1c,0x11,1,6,6);
    if (iVar3 == 0) {
      bVar2 = false;
    }
    uVar5 = strlen(&DAT_0045f220);
    iVar3 = FUN_00439857(uVar5 + 1);
    param_1[0x1b] = iVar3;
    strcpy((char *)param_1[0x1b],&DAT_0045f220);
    DAT_0045f860 = local_8;
    local_8 = FUN_0043377d();
    cVar1 = strcpy(local_20c,&DAT_0045f220);
    FUN_0043b836((char *)CONCAT31(extraout_var_01,cVar1));
    if ((DAT_0045f220 != '\0') &&
       ((local_20c[0] != DAT_0045883c || (iVar3 = strcmp(local_20c,&DAT_00458840), iVar3 != 0)))) {
      DAT_0045f860 = (char *)0x0;
      FUN_00413085((uint *)s_Syntax_error___expected_keyword_D_00458844);
      bVar2 = false;
    }
    DAT_0045f860 = local_8;
    if (param_1[8] != 0) {
      FUN_004398b5((undefined *)param_1[8]);
      param_1[8] = 0;
    }
    if (param_1[0x11] != 0) {
      FUN_004398b5((undefined *)param_1[0x11]);
      param_1[0x11] = 0;
    }
    if (param_1[0x1a] != 0) {
      FUN_004398b5((undefined *)param_1[0x1a]);
      param_1[0x1a] = 0;
    }
    if (param_1[0x23] != 0) {
      FUN_004398b5((undefined *)param_1[0x23]);
      param_1[0x23] = 0;
    }
  }
  return bVar2;
}


/* ==== FUN_0043377d @ 0043377d ==== */

char * FUN_0043377d(void)

{
  uint local_10;
  uint local_c;
  char *local_8;
  
  for (; *DAT_0045f860 != '\0'; DAT_0045f860 = DAT_0045f860 + 1) {
    if (__mb_cur_max < 2) {
      local_c = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 8;
    }
    else {
      local_c = _isctype((int)*DAT_0045f860,8);
    }
    if (local_c == 0) break;
  }
  local_8 = &DAT_0045f220;
  for (; *DAT_0045f860 != '\0'; DAT_0045f860 = DAT_0045f860 + 1) {
    if (__mb_cur_max < 2) {
      local_10 = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 8;
    }
    else {
      local_10 = _isctype((int)*DAT_0045f860,8);
    }
    if (local_10 != 0) break;
    *local_8 = *DAT_0045f860;
    local_8 = local_8 + 1;
  }
  *local_8 = '\0';
  return DAT_0045f860;
}


/* ==== FUN_00433870 @ 00433870 ==== */

void __cdecl FUN_00433870(int *param_1)

{
  if (*param_1 != 0) {
    FUN_004398b5((undefined *)*param_1);
    *param_1 = 0;
  }
  if (param_1[10] != 0) {
    FUN_004398b5((undefined *)param_1[10]);
    param_1[10] = 0;
  }
  if (param_1[8] != 0) {
    FUN_004398b5((undefined *)param_1[8]);
    param_1[8] = 0;
  }
  if (param_1[0x12] != 0) {
    FUN_004398b5((undefined *)param_1[0x12]);
    param_1[0x12] = 0;
  }
  return;
}


/* ==== FUN_004338fa @ 004338fa ==== */

void __cdecl FUN_004338fa(int *param_1)

{
  if (*param_1 != 0) {
    FUN_004398b5((undefined *)*param_1);
    *param_1 = 0;
  }
  if (param_1[9] != 0) {
    FUN_004398b5((undefined *)param_1[9]);
    param_1[9] = 0;
  }
  if (param_1[0x12] != 0) {
    FUN_004398b5((undefined *)param_1[0x12]);
    param_1[0x12] = 0;
  }
  if (param_1[0x1b] != 0) {
    FUN_004398b5((undefined *)param_1[0x1b]);
    param_1[0x1b] = 0;
  }
  return;
}


/* ==== FUN_00433984 @ 00433984 ==== */

undefined4 FUN_00433984(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined3 extraout_var;
  int iVar3;
  char local_208 [516];
  
  if (DAT_0045f220 == '\0') {
    uVar2 = 0;
  }
  else {
    cVar1 = strcpy(local_208,&DAT_0045f220);
    FUN_0043b836((char *)CONCAT31(extraout_var,cVar1));
    if ((local_208[0] == DAT_00458868) && (iVar3 = strcmp(local_208,&DAT_0045886c), iVar3 == 0)) {
      return 1;
    }
    if ((local_208[0] == DAT_00458870) && (iVar3 = strcmp(local_208,&DAT_00458874), iVar3 == 0)) {
      return 2;
    }
    if ((local_208[0] == DAT_00458878) && (iVar3 = strcmp(local_208,&DAT_00458880), iVar3 == 0)) {
      return 3;
    }
    if ((local_208[0] == DAT_00458888) && (iVar3 = strcmp(local_208,&DAT_0045888c), iVar3 == 0)) {
      return 4;
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


/* ==== FUN_00433a8a @ 00433a8a ==== */

void __cdecl FUN_00433a8a(int param_1)

{
  *(int *)(param_1 + 0x94) = DAT_0045fc94;
  DAT_0045fc94 = param_1;
  return;
}


/* ==== FUN_00433aa7 @ 00433aa7 ==== */

int FUN_00433aa7(void)

{
  int iVar1;
  
  iVar1 = DAT_0045fc94;
  if (DAT_0045fc94 != 0) {
    DAT_0045fc94 = *(int *)(DAT_0045fc94 + 0x94);
  }
  return iVar1;
}


/* ==== FUN_00433ad5 @ 00433ad5 ==== */

int * __cdecl FUN_00433ad5(undefined1 param_1)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_00439857(0xc);
  *piVar1 = DAT_0045fc8c;
  DAT_0045fc8c = DAT_0045fc8c + 1;
  *(undefined1 *)(piVar1 + 1) = param_1;
  piVar1[2] = 0;
  return piVar1;
}


/* ==== FUN_00433b1a @ 00433b1a ==== */

void __cdecl FUN_00433b1a(int param_1)

{
  *(int *)(param_1 + 8) = DAT_0045fc90;
  DAT_0045fc90 = param_1;
  return;
}


/* ==== FUN_00433b34 @ 00433b34 ==== */

int FUN_00433b34(void)

{
  int iVar1;
  
  iVar1 = DAT_0045fc90;
  if (DAT_0045fc90 != 0) {
    DAT_0045fc90 = *(int *)(DAT_0045fc90 + 8);
  }
  return iVar1;
}


/* ==== FUN_00433b5f @ 00433b5f ==== */

void FUN_00433b5f(void)

{
  undefined4 *in_stack_00000004;
  
  sprintf(&DAT_0045f220,s__s_05d_00458890,PTR_DAT_0044f99c,*in_stack_00000004);
  FUN_00432cee((uint *)&DAT_0045f220);
  return;
}


/* ==== FUN_00433b90 @ 00433b90 ==== */

void FUN_00433b90(void)

{
  undefined4 uVar1;
  int *piVar2;
  undefined *puVar3;
  
  uVar1 = DAT_0045f860;
  DAT_0045f860 = 0;
  while (piVar2 = (int *)FUN_00433aa7(), piVar2 != (int *)0x0) {
    FUN_004338fa(piVar2);
    FUN_004398b5((undefined *)piVar2);
  }
  while (puVar3 = (undefined *)FUN_00433b34(), puVar3 != (undefined *)0x0) {
    if (DAT_0045f8fc == 2) {
      switch(puVar3[4]) {
      case 3:
        FUN_00413085((uint *)s_Unexpected_end_of_file___missing_00458898);
        break;
      case 4:
        FUN_00413085((uint *)s_Unexpected_end_of_file___missing_004588c0);
        break;
      case 5:
        FUN_00413085((uint *)s_Unexpected_end_of_file___missing_004588e8);
        break;
      case 6:
        FUN_00413085((uint *)s_Unexpected_end_of_file___missing_00458938);
        break;
      case 0xb:
        FUN_00413085((uint *)s_Unexpected_end_of_file___missing_00458910);
      }
    }
    FUN_004398b5(puVar3);
  }
  DAT_0045f860 = uVar1;
  DAT_0045fc8c = 0;
  return;
}


