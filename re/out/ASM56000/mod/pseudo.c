/* pseudo: 50 functions from ASM56000 */

/* ==== FUN_0042b12c @ 0042b12c ==== */

bool __cdecl FUN_0042b12c(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  
  switch(param_1) {
  case 0x2b:
    DAT_0045ebb4 = DAT_0045ebb4 | 0x288;
    iVar2 = FUN_0041b685(2);
    cVar1 = '\x01' - (iVar2 != 0);
    break;
  case 0x2c:
  case 0x2d:
    DAT_0045ebb4 = DAT_0045ebb4 | 0x20c;
    iVar2 = FUN_0041b685(2);
    cVar1 = '\x01' - (iVar2 != 0);
    break;
  case 0x30:
    DAT_0045ebb4 = DAT_0045ebb4 | 0x210;
  case 0x2e:
  case 0x2f:
    DAT_0045ebb4 = DAT_0045ebb4 | 0x24c;
    iVar2 = FUN_0041b685(2);
    cVar1 = '\x01' - (iVar2 != 0);
    break;
  default:
    cVar1 = '\x01';
  }
  return (bool)cVar1;
}


/* ==== FUN_0042b1e5 @ 0042b1e5 ==== */

undefined4 __cdecl FUN_0042b1e5(uint param_1,uint param_2,int param_3)

{
  undefined4 uVar1;
  
  if ((param_1 & param_2) == 0) {
    FUN_00413085((uint *)s_Instruction_does_not_allow_data_m_00456ec4);
    uVar1 = 0;
  }
  else {
    if (param_3 != 0) {
      if ((param_1 & 0x10) == 0) {
        if ((param_1 & 0x20) != 0) {
          *(undefined4 *)(param_3 + 4) = 0x70000;
        }
      }
      else {
        *(undefined4 *)(param_3 + 4) = 0x40000;
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}


/* ==== FUN_0042b240 @ 0042b240 ==== */

undefined4 __cdecl FUN_0042b240(int param_1)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_0042bafc((int)*(char *)(param_1 + 4));
  FUN_0042baac((int)*(char *)(param_1 + 5));
  if (iVar1 == 0) {
    if (DAT_0045ebc4 != 0) {
      FUN_004131f9((uint *)s_Illegal_directive_in_buffer_decl_00456f74,PTR_DAT_0044f814);
      return 0;
    }
    if ((DAT_0045fc30 != 0) && (DAT_0045eb30 == '\0')) {
      if (*(char *)(param_1 + 4) == ')') {
        iVar1 = strcmp(PTR_DAT_0044f818,&DAT_00456f9c);
        if (iVar1 == 0) {
          DAT_0045ea38 = 1;
        }
        else {
          FUN_004131f9((uint *)s_Illegal_directive_inside_DO_loop_00456fa0,PTR_DAT_0044f814);
        }
      }
      else {
        FUN_004131f9((uint *)s_Illegal_directive_inside_DO_loop_00456fc4,PTR_DAT_0044f814);
      }
    }
  }
  DAT_0045f860 = PTR_DAT_0044f818;
  switch(*(undefined1 *)(param_1 + 4)) {
  case 0:
    uVar3 = 1;
    break;
  case 1:
    uVar3 = FUN_0040e1a6();
    break;
  case 2:
    uVar3 = FUN_0040e25f(0);
    break;
  case 3:
    uVar3 = FUN_0040d7c7(0x800,0);
    break;
  case 4:
    uVar3 = FUN_0040ccad();
    break;
  case 5:
    uVar3 = FUN_0040d7c7(0x400,0);
    break;
  case 6:
    uVar3 = FUN_0040e3f6();
    break;
  case 7:
    pcVar2 = FUN_0043b405(PTR_DAT_0044f818,&DAT_0045f220);
    if (pcVar2 == (char *)0x0) {
      uVar3 = 0;
    }
    else {
      FUN_00424733((uint *)&DAT_0045f220,*(undefined4 *)(DAT_0045fb8c + 0x1c));
      uVar3 = FUN_0043b007(1);
    }
    break;
  case 8:
    uVar3 = FUN_0042fec3(0);
    break;
  case 9:
    uVar3 = FUN_0040bb20();
    break;
  case 10:
    if (*PTR_DAT_0044f810 == '\0') {
      FUN_0042bba2((uint *)PTR_DAT_0044f818,PTR_DAT_0044f81c,0);
    }
    else {
      FUN_0042bba2((uint *)PTR_DAT_0044f810,PTR_DAT_0044f818,0);
    }
    uVar3 = FUN_0043b007(2 - (uint)(*PTR_DAT_0044f810 != '\0'));
    break;
  case 0xb:
    uVar3 = FUN_0040df7a(0x400,0);
    break;
  case 0xc:
    uVar3 = FUN_0040df7a(0x800,0);
    break;
  case 0xd:
    uVar3 = FUN_0040dd85();
    break;
  case 0xe:
    uVar3 = FUN_0041fb89();
    break;
  case 0xf:
    uVar3 = FUN_0041fcec();
    break;
  case 0x10:
    uVar3 = FUN_0041fe57();
    break;
  case 0x11:
    uVar3 = FUN_004200bc();
    break;
  case 0x12:
    DAT_0045f860 = (undefined *)0x0;
    FUN_00413085((uint *)s_ELSE_without_associated_IF_direc_00456fe8);
    uVar3 = 0;
    break;
  case 0x13:
    uVar3 = FUN_00430015();
    break;
  case 0x14:
    FUN_0040e572();
    uVar3 = FUN_0043b007(0);
    break;
  case 0x15:
    DAT_0045f860 = (undefined *)0x0;
    FUN_00413085((uint *)s_ENDIF_without_associated_IF_dire_00457010);
    uVar3 = 0;
    break;
  case 0x16:
    DAT_0045f860 = (undefined *)0x0;
    FUN_00413085((uint *)s_ENDM_without_associated_MACRO_di_00457038);
    uVar3 = 0;
    break;
  case 0x17:
    FUN_00435924();
    uVar3 = FUN_0043b007(0);
    break;
  case 0x18:
    uVar3 = FUN_00430b62();
    break;
  case 0x19:
    if (DAT_0045fb6c == 0) {
      DAT_0045f860 = (undefined *)0x0;
      FUN_00413085((uint *)s_EXITM_without_associated_MACRO_d_00457060);
      uVar3 = 0;
    }
    else {
      *(undefined4 *)(DAT_0045fb6c + 8) = 0;
      uVar3 = FUN_0043b007(0);
    }
    break;
  case 0x1a:
    uVar3 = FUN_00430916(0x1a);
    break;
  case 0x1b:
    uVar3 = FUN_004366be();
    break;
  case 0x1c:
  case 0x22:
    uVar3 = FUN_0042de8d((int)*(char *)(param_1 + 4));
    break;
  case 0x1d:
    uVar3 = FUN_0042bcab();
    break;
  case 0x1e:
    uVar3 = FUN_0042e838();
    break;
  case 0x1f:
    uVar3 = FUN_0042bf3a();
    break;
  case 0x20:
    uVar3 = FUN_004364a5();
    break;
  case 0x21:
    DAT_0045ebec = DAT_0045ebec + 1;
    DAT_0045ea54 = 1;
    uVar3 = FUN_0043b007(0);
    break;
  case 0x23:
    if (*PTR_DAT_0044f818 == '\0') {
      DAT_0044f7f4 = 10;
      DAT_0044f7f8 = 8;
      DAT_0044f7fc = 10;
      DAT_0044f800 = 0xc;
      DAT_0044f804 = 0xc;
    }
    else {
      FUN_0043b007(1);
      iVar1 = FUN_0042e539();
      if (iVar1 == 0) {
        return 0;
      }
    }
    uVar3 = 1;
    break;
  case 0x24:
    uVar3 = FUN_0042c457((uint *)PTR_DAT_0044f818,0);
    break;
  case 0x25:
    uVar3 = FUN_0041ee40();
    break;
  case 0x26:
    uVar3 = FUN_0042c5f3();
    break;
  case 0x27:
    uVar3 = FUN_00430916(0x27);
    break;
  case 0x28:
    DAT_0045ebec = DAT_0045ebec + -1;
    DAT_0045ea54 = 1;
    uVar3 = FUN_0043b007(0);
    break;
  case 0x29:
    uVar3 = FUN_0042ec12(PTR_DAT_0044f818);
    break;
  case 0x2a:
    uVar3 = FUN_0042cef3();
    break;
  case 0x2b:
    if (*PTR_DAT_0044f818 == '\0') {
      if (((DAT_0045f8fc == 2) && (DAT_0045ea34 == '\0')) && (0 < DAT_0045ebec)) {
        if (((DAT_0045fb6c == 0) || (DAT_0045ea30 != '\0')) && (FUN_0041cced(1), DAT_0044f7f0 < 1))
        {
          FUN_004133a9((uint *)s_Page_directive_with_no_arguments_0045708c);
        }
        DAT_0045ea54 = 1;
      }
    }
    else {
      FUN_0043b007(1);
      iVar1 = FUN_0042e1f7();
      if (iVar1 == 0) {
        return 0;
      }
    }
    uVar3 = 1;
    break;
  case 0x2c:
    uVar3 = FUN_0042052c();
    break;
  case 0x2d:
    uVar3 = FUN_0043063f();
    break;
  case 0x2e:
    uVar3 = FUN_0043104e();
    break;
  case 0x2f:
    uVar3 = FUN_0042fd1e();
    break;
  case 0x30:
    uVar3 = FUN_0042f9fb(PTR_DAT_0044f818);
    break;
  case 0x31:
    if (*PTR_DAT_0044f810 == '\0') {
      FUN_004351c0((uint *)PTR_DAT_0044f818,(uint *)PTR_DAT_0044f81c,(uint *)PTR_DAT_0044f820);
    }
    else {
      FUN_004351c0((uint *)PTR_DAT_0044f810,(uint *)PTR_DAT_0044f818,(uint *)PTR_DAT_0044f81c);
    }
    uVar3 = FUN_0043b007(3 - (uint)(*PTR_DAT_0044f810 != '\0'));
    break;
  case 0x32:
  case 0x40:
    uVar3 = FUN_00430e0f((int)*(char *)(param_1 + 4));
    break;
  case 0x33:
    uVar3 = FUN_0043158e(&DAT_0045ec00);
    break;
  case 0x34:
    uVar3 = FUN_0042feb9();
    break;
  case 0x35:
    if (*PTR_DAT_0044f818 == '\0') {
      DAT_0044f7d0 = 8;
    }
    else {
      FUN_0043b007(1);
      iVar1 = FUN_0042e7e6();
      if (iVar1 == 0) {
        return 0;
      }
    }
    uVar3 = 1;
    break;
  case 0x36:
    uVar3 = FUN_0043158e(&DAT_0045ebfc);
    break;
  case 0x37:
    FUN_0042bc44((uint *)PTR_DAT_0044f818);
    uVar3 = FUN_0043b007(1);
    break;
  case 0x38:
    uVar3 = FUN_00430916(0x38);
    break;
  case 0x39:
    uVar3 = FUN_00436b2e();
    break;
  case 0x3a:
    uVar3 = FUN_004368c3();
    break;
  case 0x3b:
    uVar3 = FUN_0040c252();
    break;
  case 0x3c:
    uVar3 = FUN_004310e5((int)*(char *)(param_1 + 4));
    break;
  case 0x3d:
    uVar3 = FUN_004310e5((int)*(char *)(param_1 + 4));
    break;
  case 0x3e:
    uVar3 = FUN_004312d0();
    break;
  case 0x3f:
    uVar3 = FUN_0042fb7e(PTR_DAT_0044f818);
    break;
  case 0x41:
    uVar3 = FUN_0040c6ac(2);
    break;
  case 0x42:
    uVar3 = FUN_0040c6ac(4);
    break;
  case 0x43:
    uVar3 = FUN_0040d1f7(1);
    break;
  case 0x44:
    uVar3 = FUN_0040d1f7(2);
    break;
  case 0x45:
    uVar3 = FUN_0040d1f7(4);
    break;
  case 0x46:
    uVar3 = FUN_0040d7c7(0x400,0x46);
    break;
  case 0x47:
    uVar3 = FUN_0040df7a(0x400,0x47);
    break;
  case 0x48:
    uVar3 = FUN_0040e25f(0x48);
    break;
  default:
    FUN_00412fa0((uint *)s_Directive_select_error_004570d0);
    uVar3 = 0;
  }
  return uVar3;
}


/* ==== FUN_0042baac @ 0042baac ==== */

void __cdecl FUN_0042baac(int param_1)

{
  if (param_1 == 2) {
    if ((PTR_DAT_0044f810 != (undefined *)0x0) && (*PTR_DAT_0044f810 != '\0')) {
      FUN_0043797a();
    }
  }
  else if (((param_1 == 0) && (PTR_DAT_0044f810 != (undefined *)0x0)) && (*PTR_DAT_0044f810 != '\0')
          ) {
    FUN_004133a9((uint *)s_Label_field_ignored_004570e8);
  }
  return;
}


/* ==== FUN_0042bafc @ 0042bafc ==== */

undefined4 __cdecl FUN_0042bafc(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 1:
  case 2:
  case 3:
  case 5:
  case 6:
  case 0xb:
  case 0xc:
  case 0x13:
  case 0x17:
  case 0x26:
  case 0x29:
  case 0x2a:
  case 0x31:
  case 0x46:
    uVar1 = 0;
    break;
  default:
    uVar1 = 1;
  }
  return uVar1;
}


/* ==== FUN_0042bba2 @ 0042bba2 ==== */

undefined4 __cdecl FUN_0042bba2(uint *param_1,char *param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  uint local_204 [128];
  
  if ((char)*param_1 == '\0') {
    FUN_00413085((uint *)s_Missing_symbol_name_004570fc);
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_0043b659((char *)param_1);
    if (iVar2 == -1) {
      uVar1 = 0;
    }
    else if ((char)*param_1 == DAT_0044f830) {
      FUN_004131f9((uint *)s_DEFINE_symbol_must_be_a_global_s_00457110,(char *)param_1);
      uVar1 = 0;
    }
    else {
      pcVar3 = FUN_0043b405(param_2,(char *)local_204);
      if (pcVar3 == (char *)0x0) {
        FUN_00413085((uint *)s_Missing_definition_string_0045713c);
        uVar1 = 0;
      }
      else {
        uVar1 = FUN_00430239(param_1,local_204,param_3);
      }
    }
  }
  return uVar1;
}


/* ==== FUN_0042bc44 @ 0042bc44 ==== */

undefined4 __cdecl FUN_0042bc44(uint *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((char)*param_1 == '\0') {
    FUN_00413085((uint *)s_Missing_symbol_name_00457158);
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_0043b659((char *)param_1);
    if (iVar2 == -1) {
      uVar1 = 0;
    }
    else if ((char)*param_1 == DAT_0044f830) {
      FUN_004131f9((uint *)s_UNDEF_symbol_must_be_a_global_sy_0045716c,(char *)param_1);
      uVar1 = 0;
    }
    else {
      uVar1 = FUN_0043035b(param_1);
    }
  }
  return uVar1;
}


/* ==== FUN_0042bcab @ 0042bcab ==== */

undefined4 FUN_0042bcab(void)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  char *pcVar5;
  char *local_10;
  
  if (DAT_0045eafc == '\0') {
    if (*PTR_DAT_0044f810 != '\0') {
      iVar2 = FUN_0043b659(PTR_DAT_0044f810);
      if (iVar2 == -1) {
        return 0;
      }
      for (; (*PTR_DAT_0044f810 != '\0' && (*PTR_DAT_0044f810 == DAT_0044f830));
          PTR_DAT_0044f810 = PTR_DAT_0044f810 + 1) {
      }
      strcpy(&DAT_0045f950,PTR_DAT_0044f810);
    }
    if (*DAT_0045f860 == '\0') {
      FUN_00413085((uint *)s_IDENT_directive_must_contain_ver_00457198);
      uVar1 = 0;
    }
    else {
      piVar3 = FUN_00413e70();
      if (piVar3 == (int *)0x0) {
        uVar1 = 0;
      }
      else {
        DAT_0045fb54 = piVar3[2];
        FUN_004167ef(piVar3);
        if ((*DAT_0045f860 == ',') && (DAT_0045f860 = DAT_0045f860 + 1, *DAT_0045f860 != '\0')) {
          piVar3 = FUN_00413e70();
          if (piVar3 == (int *)0x0) {
            uVar1 = 0;
          }
          else {
            DAT_0045fb58 = piVar3[2];
            FUN_004167ef(piVar3);
            if ((*PTR_DAT_0044f824 != '\0') && (DAT_0045fb5c == (char *)0x0)) {
              uVar4 = strlen(PTR_DAT_0044f824);
              DAT_0045fb5c = (char *)FUN_00439857(uVar4 + 1);
              strcpy(DAT_0045fb5c,PTR_DAT_0044f824);
            }
            strcpy(&DAT_0045f220,&DAT_0045f950);
            uVar4 = strlen(&DAT_0045f220);
            (&DAT_0045f220)[uVar4] = 0x20;
            pcVar5 = &DAT_0045f221 + uVar4;
            sprintf(pcVar5,s__04X__04X__04X_004571f4,DAT_0045fb54,DAT_0045fb58,DAT_0045eb84);
            uVar4 = strlen(pcVar5);
            pcVar5 = pcVar5 + uVar4;
            if (DAT_0045eb50 == '\0') {
              local_10 = s_6_3_0_0044f9b8;
            }
            else {
              local_10 = &DAT_00457204;
            }
            sprintf(pcVar5,s__s__s_0045720c,s_DSP56000_0044e068,local_10);
            if (DAT_0045fb5c != (char *)0x0) {
              uVar4 = strlen(pcVar5);
              sprintf(pcVar5 + uVar4,&DAT_00457214,DAT_0045fb5c);
            }
            FUN_00424733((uint *)&DAT_0045f220,0xffffffff);
            DAT_0045eb00 = 1;
            DAT_0045eafc = '\x01';
            uVar1 = FUN_0043b007(1);
          }
        }
        else {
          FUN_00413085((uint *)s_IDENT_directive_must_contain_rev_004571c4);
          uVar1 = 0;
        }
      }
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}


/* ==== FUN_0042bf3a @ 0042bf3a ==== */

undefined4 FUN_0042bf3a(void)

{
  bool bVar1;
  char *pcVar2;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int extraout_EAX_03;
  int extraout_EAX_04;
  undefined4 *puVar3;
  undefined4 uVar4;
  uint *local_228;
  int local_21c;
  undefined4 *local_218;
  undefined4 *local_214;
  char local_210 [516];
  char *local_c;
  char *local_8;
  
  local_21c = 0;
  bVar1 = false;
  if (*PTR_DAT_0044f818 == '<') {
    local_c = local_210;
    local_8 = PTR_DAT_0044f818;
    while ((local_8 = local_8 + 1, *local_8 != '\0' && (*local_8 != '>'))) {
      *local_c = *local_8;
      local_c = local_c + 1;
    }
    *local_c = '\0';
    if (*local_8 != '>') {
      FUN_00413085((uint *)s_Syntax_error___expected__>__00457218);
      return 0;
    }
    if (local_8[1] != '\0') {
      FUN_00413085((uint *)s_Extra_characters_following_strin_00457234);
      return 0;
    }
    bVar1 = true;
  }
  else {
    pcVar2 = FUN_0043b405(PTR_DAT_0044f818,local_210);
    if (pcVar2 == (char *)0x0) {
      FUN_00413085((uint *)s_Missing_filename_00457258);
      return 0;
    }
  }
  strcpy(&DAT_0045f220,local_210);
  if ((bVar1) || (fopen(&DAT_0045f220,&DAT_0045726c), local_21c = extraout_EAX, extraout_EAX == 0))
  {
    for (local_218 = DAT_0045fc5c; local_218 != (undefined4 *)0x0;
        local_218 = (undefined4 *)local_218[1]) {
      strcpy(&DAT_0045f220,(char *)*local_218);
      strcat(&DAT_0045f220,local_210);
      fopen(&DAT_0045f220,&DAT_00457270);
      local_21c = extraout_EAX_00;
      if (extraout_EAX_00 != 0) break;
    }
    if ((local_21c == 0) && (DAT_0045ea8c != '\0')) {
      for (local_214 = DAT_0045fc64; local_214 != (undefined4 *)0x0;
          local_214 = (undefined4 *)local_214[2]) {
        strcpy(&DAT_0045f220,(char *)*local_214);
        strcat(&DAT_0045f220,local_210);
        fopen(&DAT_0045f220,&DAT_00457274);
        local_21c = extraout_EAX_01;
        if (extraout_EAX_01 != 0) break;
      }
    }
  }
  if (local_21c == 0) {
    strcpy(&DAT_0045f220,local_210);
    FUN_00402bfa((uint *)&DAT_00457278);
    if ((bVar1) ||
       (fopen(&DAT_0045f220,&DAT_00457280), local_21c = extraout_EAX_02, extraout_EAX_02 == 0)) {
      for (local_218 = DAT_0045fc5c; local_218 != (undefined4 *)0x0;
          local_218 = (undefined4 *)local_218[1]) {
        strcpy(&DAT_0045f220,(char *)*local_218);
        strcat(&DAT_0045f220,local_210);
        FUN_00402bfa((uint *)&DAT_00457284);
        fopen(&DAT_0045f220,&DAT_0045728c);
        local_21c = extraout_EAX_03;
        if (extraout_EAX_03 != 0) break;
      }
      if ((local_21c == 0) && (DAT_0045ea8c != '\0')) {
        for (local_214 = DAT_0045fc64; local_214 != (undefined4 *)0x0;
            local_214 = (undefined4 *)local_214[2]) {
          strcpy(&DAT_0045f220,(char *)*local_214);
          strcat(&DAT_0045f220,local_210);
          FUN_00402bfa((uint *)&DAT_00457290);
          fopen(&DAT_0045f220,&DAT_00457298);
          local_21c = extraout_EAX_04;
          if (extraout_EAX_04 != 0) break;
        }
      }
    }
  }
  if (local_21c == 0) {
    FUN_004131f9((uint *)s_Cannot_open_include_file_004572bc,local_210);
    uVar4 = 0;
  }
  else {
    if (DAT_0045eb4c != '\0') {
      fprintf(PTR_DAT_0044f9a4,s__s__Opening_include_file__s_0045729c,PTR_s_asm56000_0044e084,
              &DAT_0045f220);
    }
    puVar3 = (undefined4 *)FUN_00439857(0x18);
    *puVar3 = PTR_DAT_0044f80c;
    puVar3[1] = DAT_0045f900;
    puVar3[2] = DAT_0044f954;
    puVar3[3] = DAT_0045eb7c;
    puVar3[4] = 0;
    puVar3[5] = DAT_0045fc28;
    DAT_0044f954 = DAT_0044f954 + 1;
    DAT_0045fc28 = puVar3;
    FUN_00402cde((uint *)&DAT_0045f220);
    DAT_0045f900 = local_21c;
    DAT_0045eb7c = 0;
    FUN_0041a3ce(1);
    if (DAT_0045eae0 == '\0') {
      if (DAT_0045eb24 == '\0') {
        local_228 = (uint *)PTR_DAT_0044f80c;
      }
      else {
        local_228 = DAT_0045f858;
      }
      FUN_0040f5d5((uint *)&DAT_004572d8,local_228,(char *)0x0,0);
      FUN_00435d9f();
      FUN_00435eca(PTR_DAT_0044f978,0);
    }
    uVar4 = FUN_0043b007(1);
  }
  return uVar4;
}


/* ==== FUN_0042c457 @ 0042c457 ==== */

undefined4 __cdecl FUN_0042c457(uint *param_1,int param_2)

{
  int *piVar1;
  char *pcVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  
  if (param_2 == 0) {
    pcVar2 = FUN_0043b405((char *)param_1,&DAT_0045f220);
    if (pcVar2 == (char *)0x0) {
      FUN_00413085((uint *)s_Missing_pathname_004572e0);
      return 0;
    }
  }
  else {
    strcpy(&DAT_0045f220,(char *)param_1);
  }
  piVar1 = DAT_0045fc64;
  piVar3 = DAT_0045fc68;
  if (DAT_0045f8fc != 2) {
    FUN_00402c7c();
    piVar3 = (int *)FUN_00439857(0xc);
    uVar4 = strlen(&DAT_0045f220);
    iVar5 = FUN_00439857(uVar4 + 1);
    *piVar3 = iVar5;
    strcpy((char *)*piVar3,&DAT_0045f220);
    piVar3[1] = param_2;
    piVar3[2] = 0;
    piVar1 = piVar3;
    if (DAT_0045fc64 != (int *)0x0) {
      DAT_0045fc68[2] = (int)piVar3;
      piVar1 = DAT_0045fc64;
    }
  }
  DAT_0045fc68 = piVar3;
  DAT_0045fc64 = piVar1;
  return 1;
}


/* ==== FUN_0042c542 @ 0042c542 ==== */

undefined4 __cdecl FUN_0042c542(uint *param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
  piVar1 = DAT_0045fc5c;
  piVar2 = DAT_0045fc60;
  if (DAT_0045f8fc != 2) {
    strcpy(&DAT_0045f220,(char *)param_1);
    FUN_00402c7c();
    piVar2 = (int *)FUN_00439857(8);
    uVar3 = strlen(&DAT_0045f220);
    iVar4 = FUN_00439857(uVar3 + 1);
    *piVar2 = iVar4;
    strcpy((char *)*piVar2,&DAT_0045f220);
    piVar2[1] = 0;
    piVar1 = piVar2;
    if (DAT_0045fc5c != (int *)0x0) {
      DAT_0045fc60[1] = (int)piVar2;
      piVar1 = DAT_0045fc5c;
    }
  }
  DAT_0045fc60 = piVar2;
  DAT_0045fc5c = piVar1;
  return 1;
}


/* ==== FUN_0042c5f3 @ 0042c5f3 ==== */

undefined4 FUN_0042c5f3(void)

{
  char *src;
  int iVar1;
  undefined4 uVar2;
  int local_210;
  char local_20c;
  char local_20b;
  int local_8;
  
  if (DAT_0044f790 == '\0') {
    FUN_004133a9((uint *)s_Directive_not_allowed_in_command_004572f4);
    return 0;
  }
  if ((PTR_DAT_0044f818 != (undefined *)0x0) && (*PTR_DAT_0044f818 != '\0')) {
    src = FUN_0043b836(PTR_DAT_0044f818);
    strcpy(&local_20c,src);
    if ((((local_20c == 'a') && (local_20b == '\0')) ||
        ((local_20c == DAT_0045733c && (iVar1 = strcmp(&local_20c,&DAT_00457340), iVar1 == 0)))) ||
       ((local_20c == s_absolute_00457344[0] &&
        (iVar1 = strcmp(&local_20c,s_absolute_00457350), iVar1 == 0)))) {
      local_8 = 0;
    }
    else {
      if (((local_20c != 'r') || (local_20b != '\0')) &&
         (((local_20c != DAT_0045735c || (iVar1 = strcmp(&local_20c,&DAT_00457360), iVar1 != 0)) &&
          ((local_20c != s_relative_00457364[0] ||
           (iVar1 = strcmp(&local_20c,s_relative_00457370), iVar1 != 0)))))) {
        FUN_004131f9((uint *)s_Invalid_mode_0045737c,&local_20c);
        return 0;
      }
      local_8 = 1;
    }
    DAT_0044f798 = (undefined1)local_8;
    DAT_0044f794 = (undefined1)local_8;
    for (local_210 = *(int *)(PTR_DAT_0044f978 + 0x10); local_210 != 0;
        local_210 = *(int *)(local_210 + 0xc)) {
      *(bool *)(local_210 + 9) = local_8 != 0;
    }
    FUN_00435d9f();
    if (local_8 == 0) {
      *(uint *)(PTR_DAT_0044f978 + 0xc) = *(uint *)(PTR_DAT_0044f978 + 0xc) & 0xfffcffff;
    }
    else {
      *(uint *)(PTR_DAT_0044f978 + 0xc) = *(uint *)(PTR_DAT_0044f978 + 0xc) | 0x30000;
    }
    *(uint *)(PTR_DAT_0044f978 + 0xc) = *(uint *)(PTR_DAT_0044f978 + 0xc) & 0xffffbfff;
    FUN_00435eca(PTR_DAT_0044f978,0);
    uVar2 = FUN_0043b007(1);
    return uVar2;
  }
  FUN_00413085((uint *)s_Mode_not_specified_00457328);
  return 0;
}


/* ==== FUN_0042c829 @ 0042c829 ==== */

int * __cdecl FUN_0042c829(int param_1,int *param_2,uint param_3,int param_4)

{
  int iVar1;
  bool bVar2;
  int local_20;
  int *local_10;
  int *local_8;
  
  local_8 = *(int **)(param_1 + 100);
  bVar2 = (param_3 & 0x4000) != 0;
  if (DAT_0045f8fc < 2) {
    local_10 = (int *)0x0;
    if ((local_8 != (int *)0x0) && (param_4 == 0)) {
      do {
        local_8 = (int *)local_8[10];
        if ((*local_8 == *param_2) && ((local_8[2] == param_2[2] && (local_8[4] == param_3)))) {
          local_10 = local_8;
        }
      } while ((local_10 == (int *)0x0) && (local_8 != *(int **)(param_1 + 100)));
    }
    local_8 = FUN_0042cbc5(param_1,param_2,param_3);
    if (local_10 != (int *)0x0) {
      *(undefined4 *)(local_8[9] + 0x10) = *(undefined4 *)(local_10[9] + 0x10);
      *(undefined4 *)(local_8[9] + 8) = *(undefined4 *)(local_8[9] + 0x10);
    }
    if ((DAT_0045eaa4 != '\0') && (DAT_00463c60 != 0)) {
      local_8[5] = local_8[5] | 0x200;
    }
  }
  else {
    local_20 = DAT_0045fb98;
    if (bVar2) {
      local_20 = DAT_0045fbac;
    }
    local_20 = local_20 + 1;
    if (bVar2) {
      for (; (local_8 != (int *)0x0 && (((local_8[4] & 0x4000U) == 0 || (local_8[6] != local_20))));
          local_8 = (int *)local_8[0xb]) {
      }
    }
    else {
      for (; (local_8 != (int *)0x0 && (((local_8[4] & 0x4000U) != 0 || (local_8[6] != local_20))));
          local_8 = (int *)local_8[0xb]) {
      }
    }
    if (local_8 == (int *)0x0) {
      FUN_00412fa0((uint *)s_Section_counter_sequence_failure_0045738c);
    }
    if (bVar2) {
      DAT_00456f30 = *param_2;
      DAT_00456f34 = param_2[1];
      DAT_00456f38 = param_2[2];
      DAT_00456f3c = param_2[3];
    }
    else {
      DAT_00465b60 = DAT_00456f30;
      DAT_00465b64 = DAT_00456f34;
      DAT_00465b68 = DAT_00456f38;
      DAT_00465b6c = DAT_00456f3c;
      DAT_00456f34 = 4;
      DAT_00456f30 = 4;
      DAT_00456f38 = 0;
      DAT_00456f3c = 0;
      if ((*(uint *)(local_8[9] + 0x30) & 1) == 0) {
        DAT_0045fb9c = DAT_0045fb9c + 1;
        local_8[7] = DAT_0045fb9c;
        FUN_00422b3a(*(uint **)(PTR_DAT_0044f978 + 4),local_8);
      }
      else {
        local_8[7] = DAT_0045fb9c + 1;
      }
    }
    if (((*(int *)(PTR_DAT_0044f97c + 0x6c) != 0) && (DAT_0045f8a0 == 0)) &&
       (*(int *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 0x10) != 0)) {
      *(int *)(local_8[9] + 8) =
           *(int *)(local_8[9] + 8) + *(int *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 0x10);
      *(int *)(local_8[9] + 0x10) =
           *(int *)(local_8[9] + 0x10) + *(int *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 0x10);
    }
    if ((((!bVar2) && (DAT_00463c60 == 0)) &&
        ((*(int *)(PTR_DAT_0044f97c + 0x74) != 0 &&
         ((**(int **)(PTR_DAT_0044f97c + 0x74) != 0 &&
          (*(int *)(*(int *)(PTR_DAT_0044f97c + 0x74) + 4) != 0)))))) &&
       (*(int *)(**(int **)(PTR_DAT_0044f97c + 0x74) + 0x1c) != 0)) {
      iVar1 = *(int *)(*(int *)(**(int **)(PTR_DAT_0044f97c + 0x74) + 0x1c) + 0x18 +
                      (*(int *)(*(int *)(PTR_DAT_0044f97c + 0x74) + 4) + -1) * 0x1c);
      *(int *)(local_8[9] + 8) = *(int *)(local_8[9] + 8) + iVar1;
      *(int *)(local_8[9] + 0x10) = *(int *)(local_8[9] + 0x10) + iVar1;
    }
  }
  if (!bVar2) {
    DAT_0045fb98 = DAT_0045fb98 + 1;
  }
  else {
    DAT_0045fbac = DAT_0045fbac + 1;
  }
  DAT_00463c60 = (uint)bVar2;
  return local_8;
}


/* ==== FUN_0042cbc5 @ 0042cbc5 ==== */

int * __cdecl FUN_0042cbc5(int param_1,int *param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  int local_10;
  
  piVar1 = (int *)FUN_00439857(0x30);
  iVar2 = FUN_0042ccf5(param_3);
  piVar1[9] = iVar2;
  FUN_0042cd9f(piVar1,param_2,param_3);
  local_10 = DAT_0045fb98;
  if ((param_3 & 0x4000) != 0) {
    local_10 = DAT_0045fbac;
  }
  local_10 = local_10 + 1;
  piVar1[6] = local_10;
  piVar1[8] = 0;
  piVar1[10] = (int)piVar1;
  piVar1[0xb] = 0;
  if (param_1 != 0) {
    if (*(int *)(param_1 + 100) == 0) {
      *(int **)(param_1 + 100) = piVar1;
    }
    else if (*(int *)(*(int *)(param_1 + 100) + 0x28) == *(int *)(param_1 + 100)) {
      *(int **)(*(int *)(param_1 + 100) + 0x2c) = piVar1;
      *(int **)(*(int *)(param_1 + 100) + 0x28) = piVar1;
      piVar1[10] = *(int *)(param_1 + 100);
    }
    else {
      iVar2 = *(int *)(*(int *)(param_1 + 100) + 0x28);
      *(int **)(iVar2 + 0x2c) = piVar1;
      *(int **)(*(int *)(param_1 + 100) + 0x28) = piVar1;
      piVar1[10] = iVar2;
    }
    if ((*(uint *)(param_1 + 0xc) & 0x200000) != 0) {
      *(uint *)(piVar1[9] + 0x30) = *(uint *)(piVar1[9] + 0x30) | 0x100;
    }
  }
  return piVar1;
}


/* ==== FUN_0042ccf5 @ 0042ccf5 ==== */

int __cdecl FUN_0042ccf5(uint param_1)

{
  int iVar1;
  
  iVar1 = FUN_00439857(0x34);
  if ((param_1 & 0x4000) == 0) {
    if (DAT_0045fba4 == (int *)0x0) {
      DAT_0045fba8 = DAT_0045fba8 + 0x1000;
      DAT_0045fba4 = (int *)FUN_00439857(DAT_0045fba8 * 4);
    }
    else if (DAT_0045fba8 <= DAT_0045fb98) {
      DAT_0045fba8 = DAT_0045fba8 + 0x1000;
      DAT_0045fba4 = FUN_00439884(DAT_0045fba4,DAT_0045fba8 * 4);
    }
    DAT_0045fba4[DAT_0045fb98] = iVar1;
  }
  return iVar1;
}


/* ==== FUN_0042cd9f @ 0042cd9f ==== */

void __cdecl FUN_0042cd9f(int *param_1,int *param_2,int param_3)

{
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  param_1[4] = param_3;
  param_1[5] = 0;
  param_1[7] = 0;
  memset((void *)param_1[9],0,8);
  *(undefined4 *)(param_1[9] + 0x10) = 0;
  *(undefined4 *)(param_1[9] + 8) = 0;
  *(int *)(param_1[9] + 0x14) = param_2[1];
  *(undefined4 *)(param_1[9] + 0xc) = *(undefined4 *)(param_1[9] + 0x14);
  *(undefined4 *)(param_1[9] + 0x18) = 0;
  *(undefined4 *)(param_1[9] + 0x24) = 0;
  *(undefined4 *)(param_1[9] + 0x20) = 0;
  *(undefined4 *)(param_1[9] + 0x1c) = 0;
  *(undefined4 *)(param_1[9] + 0x2c) = 0;
  *(undefined4 *)(param_1[9] + 0x28) = 0;
  *(uint *)(param_1[9] + 0x30) = (-(uint)(*param_2 != 0) & 0x20) + 0x20;
  return;
}


/* ==== FUN_0042ce91 @ 0042ce91 ==== */

undefined * __cdecl FUN_0042ce91(int param_1,int *param_2,int param_3)

{
  int iVar1;
  undefined *local_c;
  
  iVar1 = FUN_0043a768(*param_2);
  iVar1 = iVar1 + -1;
  if (iVar1 < 0) {
    FUN_00412fa0((uint *)s_Location_bounds_selection_failur_004573b0);
  }
  if (param_1 == 0x22) {
    local_c = &DAT_0045f870 + iVar1 * 8 + param_3 * 4;
  }
  else {
    local_c = &DAT_0044f838 + iVar1 * 8 + param_3 * 4;
  }
  return local_c;
}


/* ==== FUN_0042cef3 @ 0042cef3 ==== */

undefined4 FUN_0042cef3(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined *local_7c;
  undefined *local_78;
  int local_74;
  undefined *local_70;
  undefined *local_6c;
  int local_68;
  int local_64;
  int local_60;
  undefined4 local_5c;
  uint local_58;
  int local_54;
  int *local_50;
  int *local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  undefined *local_2c;
  int *local_28;
  int local_24;
  int local_20;
  int local_1c;
  undefined4 local_18;
  int local_14;
  int *local_10;
  uint local_c;
  int local_8;
  
  local_50 = (int *)0x0;
  local_8 = 0;
  local_34 = 0;
  local_30 = (int)DAT_0044f794;
  local_48 = *(int *)(PTR_DAT_0044f97c + 8);
  DAT_0045f920 = 1;
  local_14 = FUN_00439e8d(&local_68);
  if (local_14 < 1) {
    if (local_14 == 0) {
      FUN_00413085((uint *)s_Illegal_memory_space_specified_004573d4);
    }
    uVar1 = 0;
  }
  else {
    if (local_68 == 0x11d) {
      local_6c = (undefined *)0x1fffff;
    }
    else if (local_68 == 0x1c) {
      if (local_64 == 0x1c) {
        local_70 = (undefined *)0x1fffff;
      }
      else {
        local_70 = (&PTR_DAT_0044ed44)[local_64];
      }
      local_6c = local_70;
    }
    else {
      local_6c = (undefined *)0xffff;
    }
    DAT_0045f8d4 = FUN_0042ce91(0x22,&local_68,1);
    DAT_0045f8dc = DAT_0045f8d4;
    DAT_0045f8d8 = FUN_0042ce91(0x1c,&local_68,1);
    DAT_0045f8e0 = DAT_0045f8d8;
    if ((DAT_0045eb34 != '\0') && (local_68 == 0)) {
      FUN_00433e78(local_60);
    }
    if (*DAT_0045f860 == '\0') {
      iVar2 = FUN_0042dd26(&local_68,1);
      DAT_0044f794 = (char)iVar2;
      DAT_0044f798 = DAT_0044f794;
      local_10 = FUN_0042c829((int)PTR_DAT_0044f97c,&local_68,-(uint)(DAT_0044f794 != '\0') & 0x1000
                              ,0);
      DAT_0045f8c0 = (undefined4 *)(local_10[9] + 0x10);
      DAT_0045f8d0 = *DAT_0045f8c0;
      DAT_0045f8c4 = *DAT_0045f8c0;
      DAT_0045eabc = 0;
      DAT_0045eab8 = 0;
      DAT_0045f8a0 = local_68;
      DAT_0045f8a4 = local_64;
      DAT_0045f8a8 = local_60;
      DAT_0045f8ac = local_5c;
      DAT_0045f8b0 = local_68;
      DAT_0045f8b4 = local_64;
      DAT_0045f8b8 = local_60;
      DAT_0045f8bc = local_5c;
      DAT_0044f91c = local_6c;
      DAT_0044f920 = local_6c;
      DAT_0045ea14 = 1;
      DAT_0045f8cc = DAT_0045f8c0;
      DAT_0045fb88 = local_10;
      DAT_0045fb8c = local_10;
      *(uint *)(PTR_DAT_0044f97c + 0xc) = *(uint *)(PTR_DAT_0044f97c + 0xc) & 0xffffbfff;
      FUN_0043b926(1);
      uVar1 = FUN_0043b007(1);
    }
    else {
      if (*DAT_0045f860 == ',') {
        DAT_0045f860 = DAT_0045f860 + 1;
      }
      else {
        local_34 = 1;
        local_50 = FUN_00413c50((uint)local_6c);
        if (local_50 == (int *)0x0) {
          return 0;
        }
        if ((DAT_0044f790 == '\0') && ((local_50[6] & 0x8000000U) != 0)) {
          FUN_00413085((uint *)s_Expression_contains_forward_refe_004573f4);
          FUN_004167ef(local_50);
          return 0;
        }
        if (((DAT_0044f7a4 != '\0') && ((local_50[6] & 0x1000U) == 0)) &&
           (iVar2 = FUN_0043baf1(local_50[7],local_68), iVar2 == 0xa2c2a)) {
          FUN_004133a9((uint *)s_Runtime_origin_involves_incompat_0045741c);
        }
        local_8 = local_50[2];
        local_c = (uint)((local_50[6] & 0x8000000U) != 0);
        if (((local_50[6] & 0x1000U) == 0) && (local_c == 0)) {
          local_74 = 0;
        }
        else {
          local_74 = 1;
        }
        local_30 = local_74;
        local_44 = local_50[7];
        local_40 = local_50[8];
        local_38 = local_50[10];
        local_3c = local_60;
        local_48 = local_50[0xf];
        FUN_004167ef(local_50);
        if (*DAT_0045f860 == ',') {
          DAT_0045f860 = DAT_0045f860 + 1;
          strcpy(&DAT_0045f630,&DAT_0045f428);
        }
        else if (*DAT_0045f860 == '\0') {
          if (local_c != 0) {
            FUN_00413085((uint *)s_Expression_contains_forward_refe_00457450);
            return 0;
          }
          if ((local_30 != 0) &&
             (((local_48 != *(int *)(PTR_DAT_0044f97c + 8) || (local_68 != local_44)) ||
              (local_60 != local_3c)))) {
            FUN_00413085((uint *)s_Relocatable_runtime_origin_must_b_00457478);
            return 0;
          }
          DAT_0044f798 = (char)local_30;
          DAT_0044f794 = (char)local_30;
          FUN_0042dddb(local_30,&local_68,1);
          local_10 = FUN_0042c829((int)PTR_DAT_0044f97c,&local_68,-(uint)(local_30 != 0) & 0x1000,1)
          ;
          DAT_0045fb88 = local_10;
          DAT_0045fb8c = local_10;
          *(int *)(local_10[9] + 0x10) = local_8;
          *(int *)(local_10[9] + 8) = local_8;
          DAT_0045f8c0 = (undefined4 *)(local_10[9] + 0x10);
          DAT_0045f8d0 = *DAT_0045f8c0;
          DAT_0045f8c4 = *DAT_0045f8c0;
          DAT_0045eabc = 0;
          DAT_0045eab8 = 0;
          DAT_0045f8a0 = local_68;
          DAT_0045f8a4 = local_64;
          DAT_0045f8a8 = local_60;
          DAT_0045f8ac = local_5c;
          DAT_0045f8b0 = local_68;
          DAT_0045f8b4 = local_64;
          DAT_0045f8b8 = local_60;
          DAT_0045f8bc = local_5c;
          DAT_0044f91c = local_6c;
          DAT_0044f920 = local_6c;
          DAT_0045ea14 = 1;
          DAT_0045f8cc = DAT_0045f8c0;
          if (DAT_0044f794 == '\0') {
            *(uint *)(PTR_DAT_0044f97c + 0xc) = *(uint *)(PTR_DAT_0044f97c + 0xc) & 0xfffcffff;
          }
          else {
            *(uint *)(PTR_DAT_0044f97c + 0xc) = *(uint *)(PTR_DAT_0044f97c + 0xc) | 0x30000;
          }
          if ((*(int *)(PTR_DAT_0044f97c + 0x6c) != 0) && (local_68 == 0)) {
            *(undefined4 *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 0x10) = 0;
            FUN_00434023((uint *)0x0,0,0,0);
          }
          *(uint *)(PTR_DAT_0044f97c + 0xc) = *(uint *)(PTR_DAT_0044f97c + 0xc) & 0xffffbfff;
          FUN_0043b926(1);
          uVar1 = FUN_0043b007(1);
          return uVar1;
        }
      }
      local_14 = FUN_00439e8d(&local_24);
      if (local_14 < 1) {
        if (local_14 == 0) {
          FUN_00413085((uint *)s_Illegal_memory_space_specified_004574c4);
        }
        uVar1 = 0;
      }
      else if ((local_68 == 3) && (local_24 != 3)) {
        FUN_00413085((uint *)s_L_space_specified_for_runtime__b_004574e4);
        uVar1 = 0;
      }
      else if ((local_24 == 3) && (local_68 != 3)) {
        FUN_00413085((uint *)s_L_space_specified_for_load__but_n_00457514);
        uVar1 = 0;
      }
      else if ((DAT_0045eaa4 == '\0') || (local_24 != 0x1c)) {
        if (local_68 == 0x11d) {
          local_6c = (undefined *)0x1fffff;
        }
        else if (local_68 == 0x1c) {
          if ((local_64 == 0x1c) || (local_64 == 0x11d)) {
            local_78 = (undefined *)0x1fffff;
          }
          else {
            local_78 = (&PTR_DAT_0044ed44)[local_64];
          }
          local_6c = local_78;
        }
        else {
          local_6c = (undefined *)0xffff;
        }
        DAT_0045f8d4 = FUN_0042ce91(0x22,&local_68,0);
        DAT_0045f8d8 = FUN_0042ce91(0x1c,&local_68,0);
        if (local_24 == 0x11d) {
          local_2c = (undefined *)0x1fffff;
        }
        else if (local_24 == 0x1c) {
          if (local_20 == 0x1c) {
            local_7c = (undefined *)0x1fffff;
          }
          else {
            local_7c = (&PTR_DAT_0044ed44)[local_20];
          }
          local_2c = local_7c;
        }
        else {
          local_2c = (undefined *)0xffff;
        }
        DAT_0045f8dc = FUN_0042ce91(0x22,&local_24,1);
        DAT_0045f8e0 = FUN_0042ce91(0x1c,&local_24,1);
        if (local_30 != 0) {
          local_8 = 0;
        }
        if ((DAT_0045eb34 != '\0') && (local_68 == 0)) {
          FUN_00433f67((int)PTR_DAT_0044f97c);
        }
        if (*DAT_0045f860 == '\0') {
          DAT_0045ebe8 = DAT_0045ebe8 + 1;
          if (local_34 == 0) {
            iVar2 = FUN_0042dd26(&local_68,0);
            DAT_0044f794 = (char)iVar2;
            DAT_0045fb88 = FUN_0042c829((int)PTR_DAT_0044f97c,&local_68,
                                        (uint)((byte)(-(uint)(DAT_0044f794 != '\0') >> 8) & 0x10 |
                                              0x40) << 8,0);
            local_10 = DAT_0045fb88;
          }
          else {
            DAT_0044f794 = (char)local_30;
            FUN_0042dddb(local_30,&local_68,0);
            local_10 = FUN_0042c829((int)PTR_DAT_0044f97c,&local_68,
                                    (uint)((byte)(-(uint)(local_30 != 0) >> 8) & 0x10 | 0x40) << 8,1
                                   );
            DAT_0045fb88 = local_10;
            *(int *)(local_10[9] + 0x10) = local_8;
            *(int *)(local_10[9] + 8) = local_8;
          }
          DAT_0045f8c0 = (undefined4 *)(local_10[9] + 0x10);
          DAT_0045f8c4 = *DAT_0045f8c0;
          iVar2 = FUN_0042dd26(&local_24,1);
          DAT_0044f798 = (char)iVar2;
          local_4c = FUN_0042c829((int)PTR_DAT_0044f97c,&local_24,
                                  -(uint)(DAT_0044f798 != '\0') & 0x1000,0);
          DAT_0045fb8c = local_4c;
          local_4c[8] = local_4c[8] + 1;
          if (DAT_0045eadc != '\0') {
            *(uint *)(local_4c[9] + 0x30) = *(uint *)(local_4c[9] + 0x30) | 0x800;
          }
          DAT_0045f8cc = (undefined4 *)(local_4c[9] + 0x10);
          DAT_0045f8d0 = *DAT_0045f8cc;
          DAT_0045eabc = 0;
          DAT_0045eab8 = 0;
          DAT_0045f8a0 = local_68;
          DAT_0045f8a4 = local_64;
          DAT_0045f8a8 = local_60;
          DAT_0045f8ac = local_5c;
          DAT_0045f8b0 = local_24;
          DAT_0045f8b4 = local_20;
          DAT_0045f8b8 = local_1c;
          DAT_0045f8bc = local_18;
          DAT_0044f91c = local_6c;
          DAT_0044f920 = local_2c;
          DAT_0045ea14 = 1;
          if (DAT_0044f794 == '\0') {
            *(uint *)(PTR_DAT_0044f97c + 0xc) = *(uint *)(PTR_DAT_0044f97c + 0xc) & 0xfffeffff;
          }
          else {
            *(uint *)(PTR_DAT_0044f97c + 0xc) = *(uint *)(PTR_DAT_0044f97c + 0xc) | 0x10000;
          }
          if (((local_50 != (int *)0x0) && (*(int *)(PTR_DAT_0044f97c + 0x6c) != 0)) &&
             (local_68 == 0)) {
            *(undefined4 *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 0x10) = 0;
            FUN_00434023((uint *)0x0,0,0,0);
          }
          *(uint *)(PTR_DAT_0044f97c + 0xc) = *(uint *)(PTR_DAT_0044f97c + 0xc) | 0x24000;
          FUN_0043b926(1);
          uVar1 = FUN_0043b007(1);
        }
        else {
          local_28 = FUN_00413c50((uint)local_2c);
          if (local_28 == (int *)0x0) {
            uVar1 = 0;
          }
          else if ((local_28[6] & 0x8000000U) == 0) {
            if (((DAT_0044f7a4 != '\0') && ((local_28[6] & 0x1000U) == 0)) &&
               (iVar2 = FUN_0043baf1(local_28[7],local_24), iVar2 == 0xa2c2a)) {
              FUN_004133a9((uint *)s_Load_origin_involves_incompatibl_00457598);
            }
            local_54 = local_28[2];
            local_58 = (uint)((local_28[6] & 0x1000U) != 0);
            local_44 = local_28[7];
            local_40 = local_28[8];
            local_38 = local_28[10];
            local_3c = local_1c;
            local_48 = local_28[0xf];
            FUN_004167ef(local_28);
            if (*DAT_0045f860 == '\0') {
              if ((local_58 == 0) ||
                 (((local_48 == *(int *)(PTR_DAT_0044f97c + 8) && (local_24 == local_44)) &&
                  (local_1c == local_3c)))) {
                DAT_0045ebe8 = DAT_0045ebe8 + 1;
                if (local_34 == 0) {
                  iVar2 = FUN_0042dd26(&local_68,0);
                  DAT_0044f794 = (char)iVar2;
                  DAT_0045fb88 = FUN_0042c829((int)PTR_DAT_0044f97c,&local_68,
                                              (uint)((byte)(-(uint)(DAT_0044f794 != '\0') >> 8) &
                                                     0x10 | 0x40) << 8,0);
                  local_10 = DAT_0045fb88;
                }
                else {
                  DAT_0044f794 = (char)local_30;
                  FUN_0042dddb(local_30,&local_68,0);
                  local_10 = FUN_0042c829((int)PTR_DAT_0044f97c,&local_68,
                                          (uint)((byte)(-(uint)(local_30 != 0) >> 8) & 0x10 | 0x40)
                                          << 8,1);
                  DAT_0045fb88 = local_10;
                  *(int *)(local_10[9] + 0x10) = local_8;
                  *(int *)(local_10[9] + 8) = local_8;
                }
                DAT_0045f8c0 = (undefined4 *)(local_10[9] + 0x10);
                DAT_0045f8c4 = *DAT_0045f8c0;
                DAT_0044f798 = (char)local_58;
                FUN_0042dddb(local_58,&local_24,1);
                local_4c = FUN_0042c829((int)PTR_DAT_0044f97c,&local_24,
                                        -(uint)(local_58 != 0) & 0x1000,1);
                DAT_0045fb8c = local_4c;
                local_4c[8] = local_4c[8] + 1;
                *(int *)(local_4c[9] + 0x10) = local_54;
                *(int *)(local_4c[9] + 8) = local_54;
                if (DAT_0045eadc != '\0') {
                  *(uint *)(local_4c[9] + 0x30) = *(uint *)(local_4c[9] + 0x30) | 0x800;
                }
                DAT_0045f8cc = (undefined4 *)(local_4c[9] + 0x10);
                DAT_0045f8d0 = *DAT_0045f8cc;
                DAT_0045eabc = 0;
                DAT_0045eab8 = 0;
                DAT_0045f8a0 = local_68;
                DAT_0045f8a4 = local_64;
                DAT_0045f8a8 = local_60;
                DAT_0045f8ac = local_5c;
                DAT_0045f8b0 = local_24;
                DAT_0045f8b4 = local_20;
                DAT_0045f8b8 = local_1c;
                DAT_0045f8bc = local_18;
                DAT_0044f91c = local_6c;
                DAT_0044f920 = local_2c;
                DAT_0045ea14 = 1;
                if (DAT_0044f794 == '\0') {
                  *(uint *)(PTR_DAT_0044f97c + 0xc) = *(uint *)(PTR_DAT_0044f97c + 0xc) & 0xfffeffff
                  ;
                }
                else {
                  *(uint *)(PTR_DAT_0044f97c + 0xc) = *(uint *)(PTR_DAT_0044f97c + 0xc) | 0x10000;
                }
                if (DAT_0044f798 == '\0') {
                  *(uint *)(PTR_DAT_0044f97c + 0xc) = *(uint *)(PTR_DAT_0044f97c + 0xc) & 0xfffdffff
                  ;
                }
                else {
                  *(uint *)(PTR_DAT_0044f97c + 0xc) = *(uint *)(PTR_DAT_0044f97c + 0xc) | 0x20000;
                }
                if (((local_50 != (int *)0x0) && (*(int *)(PTR_DAT_0044f97c + 0x6c) != 0)) &&
                   (local_68 == 0)) {
                  *(undefined4 *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 0x10) = 0;
                  FUN_00434023((uint *)0x0,0,0,0);
                }
                *(uint *)(PTR_DAT_0044f97c + 0xc) = *(uint *)(PTR_DAT_0044f97c + 0xc) | 0x4000;
                FUN_0043b926(1);
                uVar1 = FUN_0043b007(1);
              }
              else {
                FUN_00413085((uint *)s_Relocatable_load_origin_must_be_i_004575e8);
                uVar1 = 0;
              }
            }
            else {
              FUN_00413085((uint *)s_Syntax_error___extra_characters_004575c8);
              uVar1 = 0;
            }
          }
          else {
            FUN_00413085((uint *)s_Expression_contains_forward_refe_00457570);
            FUN_004167ef(local_28);
            uVar1 = 0;
          }
        }
      }
      else {
        FUN_00413085((uint *)s_LB_option_not_allowed_in_EMI_loa_00457544);
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}


/* ==== FUN_0042dd26 @ 0042dd26 ==== */

int __cdecl FUN_0042dd26(int *param_1,int param_2)

{
  char cVar1;
  int *piVar2;
  int *local_8;
  
  local_8 = *(int **)(PTR_DAT_0044f97c + 0x10);
  do {
    if (local_8 == (int *)0x0) {
      piVar2 = (int *)FUN_00439857(0x10);
      *piVar2 = *param_1;
      piVar2[1] = param_1[2];
      *(undefined1 *)(piVar2 + 2) = (undefined1)param_2;
      *(bool *)((int)piVar2 + 9) = DAT_0044f790 != '\0';
      piVar2[3] = *(int *)(PTR_DAT_0044f97c + 0x10);
      *(int **)(PTR_DAT_0044f97c + 0x10) = piVar2;
      cVar1 = *(char *)((int)piVar2 + 9);
LAB_0042ddd7:
      return (int)cVar1;
    }
    if (((*local_8 == *param_1) && (local_8[1] == param_1[2])) && ((char)local_8[2] == param_2)) {
      cVar1 = *(char *)((int)local_8 + 9);
      goto LAB_0042ddd7;
    }
    local_8 = (int *)local_8[3];
  } while( true );
}


/* ==== FUN_0042dddb @ 0042dddb ==== */

void __cdecl FUN_0042dddb(int param_1,int *param_2,int param_3)

{
  int *piVar1;
  int *local_8;
  
  local_8 = *(int **)(PTR_DAT_0044f97c + 0x10);
  while( true ) {
    if (local_8 == (int *)0x0) {
      piVar1 = (int *)FUN_00439857(0x10);
      *piVar1 = *param_2;
      piVar1[1] = param_2[2];
      *(undefined1 *)(piVar1 + 2) = (undefined1)param_3;
      *(bool *)((int)piVar1 + 9) = param_1 != 0;
      piVar1[3] = *(int *)(PTR_DAT_0044f97c + 0x10);
      *(int **)(PTR_DAT_0044f97c + 0x10) = piVar1;
      return;
    }
    if (((*local_8 == *param_2) && (local_8[1] == param_2[2])) && ((char)local_8[2] == param_3))
    break;
    local_8 = (int *)local_8[3];
  }
  *(bool *)((int)local_8 + 9) = param_1 != 0;
  return;
}


/* ==== FUN_0042de8d @ 0042de8d ==== */

undefined4 __cdecl FUN_0042de8d(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint local_3c;
  uint local_38;
  int local_30;
  uint local_2c;
  int local_24;
  int local_20;
  int local_1c;
  undefined4 local_18;
  uint local_14;
  int local_10;
  uint *local_c;
  int *local_8;
  
  local_10 = 1;
  if ((*DAT_0045f860 == ',') || (*DAT_0045f860 == '\0')) {
    FUN_00413085((uint *)s_Missing_expression_00457630);
    uVar2 = 0;
  }
  else {
    while (*DAT_0045f860 != '\0') {
      cVar1 = *DAT_0045f860;
      DAT_0045f860 = DAT_0045f860 + 1;
      local_24 = FUN_0043a807((int)cVar1);
      if ((local_24 == 0xa2c2a) || (local_24 == 4)) {
        FUN_00413085((uint *)s_Illegal_memory_space_specified_00457644);
        return 0;
      }
      local_20 = local_24;
      local_1c = FUN_0043a91e((int)*DAT_0045f860);
      if (local_1c == -1) {
        local_1c = 0;
      }
      else {
        DAT_0045f860 = DAT_0045f860 + 1;
      }
      local_18 = 0;
      if (__mb_cur_max < 2) {
        local_2c = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 1;
      }
      else {
        local_2c = _isctype((int)*DAT_0045f860,1);
      }
      if (local_2c == 0) {
        local_30 = (int)*DAT_0045f860;
      }
      else {
        local_30 = tolower((int)*DAT_0045f860);
      }
      switch(local_30) {
      default:
        FUN_00413085((uint *)s_Syntax_error___expected_____00457664);
        return 0;
      case 0x3a:
        local_10 = 1;
      case 0:
        break;
      case 0x6c:
        DAT_0045f860 = DAT_0045f860 + 1;
        local_10 = 1;
        break;
      case 0x72:
        DAT_0045f860 = DAT_0045f860 + 1;
        local_10 = 0;
      }
      cVar1 = *DAT_0045f860;
      DAT_0045f860 = DAT_0045f860 + 1;
      if (cVar1 != ':') {
        FUN_00413085((uint *)s_Syntax_error___expected_____00457680);
        return 0;
      }
      if ((*DAT_0045f860 == '\0') || (*DAT_0045f860 == ',')) {
        FUN_00413085((uint *)s_Missing_expression_0045769c);
        return 0;
      }
      if (local_10 == 0) {
        local_38 = DAT_0044f91c;
      }
      else {
        local_38 = DAT_0044f920;
      }
      local_8 = FUN_00413c50(local_38);
      if (local_8 == (int *)0x0) {
        return 0;
      }
      local_c = (uint *)FUN_0042ce91(param_1,&local_24,local_10);
      *local_c = local_8[2];
      local_14 = *local_c;
      if (local_10 == 0) {
        local_3c = DAT_0044f91c;
      }
      else {
        local_3c = DAT_0044f920;
      }
      if (local_3c < local_14) {
        FUN_00413085((uint *)s_Memory_bounds_greater_than_maxim_004576b0);
        return 0;
      }
      if (*DAT_0045f860 != '\0') {
        if (*DAT_0045f860 != ',') {
          FUN_00413085((uint *)s_Syntax_error___expected_comma_004576dc);
          return 0;
        }
        DAT_0045f860 = DAT_0045f860 + 1;
      }
    }
    uVar2 = FUN_0043b007(1);
  }
  return uVar2;
}


/* ==== FUN_0042e1f7 @ 0042e1f7 ==== */

undefined4 FUN_0042e1f7(void)

{
  undefined4 uVar1;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  DAT_0045f860 = PTR_DAT_0044f818;
  if (*PTR_DAT_0044f818 == ',') {
    local_10 = DAT_0044f7dc;
  }
  else {
    local_10 = FUN_0041479f();
    if (local_10 == -1) {
      return 0;
    }
    if ((local_10 < 1) || (0x200 < local_10)) {
      FUN_00413085((uint *)s_Invalid_page_width_specified_004576fc);
      return 0;
    }
  }
  if (*DAT_0045f860 == ',') {
    DAT_0045f860 = DAT_0045f860 + 1;
  }
  if (*DAT_0045f860 == '\0') {
    local_c = DAT_0044f7f0;
    local_14 = DAT_0045ebf4;
    local_18 = DAT_0045ebf8;
    local_8 = DAT_0044f7e0 + -1;
  }
  else {
    if (*DAT_0045f860 == ',') {
      local_c = DAT_0044f7f0;
    }
    else {
      local_c = FUN_0041479f();
      if (local_c == -1) {
        return 0;
      }
      if (local_c == 0) {
        DAT_0044f7ec = 0;
      }
      else if ((local_c < 10) || (0x200 < local_c)) {
        FUN_00413085((uint *)s_Invalid_page_length_specified_0045771c);
        return 0;
      }
    }
    if (*DAT_0045f860 == ',') {
      DAT_0045f860 = DAT_0045f860 + 1;
    }
    if (*DAT_0045f860 == '\0') {
      local_14 = DAT_0045ebf4;
      local_18 = DAT_0045ebf8;
      local_8 = DAT_0044f7e0 + -1;
    }
    else {
      if (*DAT_0045f860 == ',') {
        local_14 = DAT_0045ebf4;
      }
      else {
        local_14 = FUN_0041479f();
        if (local_14 == -1) {
          return 0;
        }
        if ((local_14 != 0) && (local_c == 0)) {
          FUN_004133a9((uint *)s_Explicit_top_margin_ignored_with_0045773c);
        }
      }
      if (*DAT_0045f860 == ',') {
        DAT_0045f860 = DAT_0045f860 + 1;
      }
      if (*DAT_0045f860 == '\0') {
        local_18 = local_c - DAT_0044f7ec;
        local_8 = DAT_0044f7e0 + -1;
      }
      else {
        if (*DAT_0045f860 == ',') {
          local_18 = local_c - DAT_0044f7ec;
          if (local_18 < 0) {
            FUN_00413085((uint *)s_Page_length_too_small_to_allow_d_00457774);
            return 0;
          }
        }
        else {
          local_18 = FUN_0041479f();
          if (local_18 == -1) {
            return 0;
          }
          if ((local_18 != 0) && (local_c == 0)) {
            FUN_004133a9((uint *)s_Explicit_bottom_margin_ignored_w_004577ac);
          }
        }
        if (*DAT_0045f860 == ',') {
          DAT_0045f860 = DAT_0045f860 + 1;
        }
        if (*DAT_0045f860 == '\0') {
          local_8 = DAT_0044f7e0 + -1;
        }
        else {
          local_8 = FUN_0041479f();
          if (local_8 == -1) {
            return 0;
          }
          if (*DAT_0045f860 != '\0') {
            FUN_00413085((uint *)s_Extra_characters_in_operand_fiel_004577e4);
            return 0;
          }
        }
      }
    }
  }
  if (local_8 < local_10) {
    if ((local_c < 1) || (local_14 + local_18 <= local_c + -10)) {
      DAT_0044f7dc = local_10;
      DAT_0044f7f0 = local_c;
      DAT_0045ebf4 = local_14;
      DAT_0045ebf8 = local_18;
      DAT_0044f7ec = local_c - local_18;
      DAT_0044f7e0 = local_8 + 1;
      uVar1 = 1;
    }
    else {
      FUN_00413085((uint *)s_Page_length_too_small_for_specif_00457828);
      uVar1 = 0;
    }
  }
  else {
    FUN_00413085((uint *)s_Left_margin_exceeds_page_width_00457808);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_0042e539 @ 0042e539 ==== */

undefined4 FUN_0042e539(void)

{
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = DAT_0044f7f4;
  local_10 = DAT_0044f7f8;
  local_18 = DAT_0044f7fc;
  local_8 = DAT_0044f800;
  local_14 = DAT_0044f804;
  DAT_0045f860 = PTR_DAT_0044f818;
  if (*PTR_DAT_0044f818 != ',') {
    local_c = FUN_0041479f();
    if (local_c == -1) {
      return 0;
    }
    if ((local_c < 1) || (0x200 < local_c)) {
      FUN_00413085((uint *)s_Invalid_label_field_width_specif_00457864);
      return 0;
    }
  }
  if (*DAT_0045f860 == ',') {
    DAT_0045f860 = DAT_0045f860 + 1;
  }
  if (*DAT_0045f860 != '\0') {
    if (*DAT_0045f860 != ',') {
      local_10 = FUN_0041479f();
      if (local_10 == -1) {
        return 0;
      }
      if ((local_10 < 1) || (0x200 - local_c < local_10)) {
        FUN_00413085((uint *)s_Invalid_opcode_field_width_speci_00457888);
        return 0;
      }
    }
    if (*DAT_0045f860 == ',') {
      DAT_0045f860 = DAT_0045f860 + 1;
    }
    if (*DAT_0045f860 != '\0') {
      if (*DAT_0045f860 != ',') {
        local_18 = FUN_0041479f();
        if (local_18 == -1) {
          return 0;
        }
        if ((local_18 < 1) || (0x200 - (local_c + local_10) < local_18)) {
          FUN_00413085((uint *)s_Invalid_operand_field_width_spec_004578b0);
          return 0;
        }
      }
      if (*DAT_0045f860 == ',') {
        DAT_0045f860 = DAT_0045f860 + 1;
      }
      if (*DAT_0045f860 != '\0') {
        if (*DAT_0045f860 != ',') {
          local_8 = FUN_0041479f();
          if (local_8 == -1) {
            return 0;
          }
          if ((local_8 < 1) || (0x200 - (local_c + local_10 + local_18) < local_8)) {
            FUN_00413085((uint *)s_Invalid_X_field_width_specified_004578d8);
            return 0;
          }
        }
        if (*DAT_0045f860 == ',') {
          DAT_0045f860 = DAT_0045f860 + 1;
        }
        if (*DAT_0045f860 != '\0') {
          local_14 = FUN_0041479f();
          if (local_14 == -1) {
            return 0;
          }
          if ((local_14 < 1) || (0x200 - (local_c + local_10 + local_18 + local_8) < local_14)) {
            FUN_00413085((uint *)s_Invalid_Y_field_width_specified_004578f8);
            return 0;
          }
        }
        if (*DAT_0045f860 != '\0') {
          FUN_00413085((uint *)s_Extra_characters_in_operand_fiel_00457918);
          return 0;
        }
      }
    }
  }
  DAT_0044f804 = local_14;
  DAT_0044f800 = local_8;
  DAT_0044f7fc = local_18;
  DAT_0044f7f8 = local_10;
  DAT_0044f7f4 = local_c;
  return 1;
}


/* ==== FUN_0042e7e6 @ 0042e7e6 ==== */

undefined4 FUN_0042e7e6(void)

{
  int iVar1;
  undefined4 uVar2;
  
  DAT_0045f860 = PTR_DAT_0044f818;
  iVar1 = FUN_0041479f();
  if (iVar1 == -1) {
    uVar2 = 0;
  }
  else if ((iVar1 < 1) || (0x200 < iVar1)) {
    FUN_00413085((uint *)s_Invalid_tab_stops_specified_0045793c);
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
    DAT_0044f7d0 = iVar1;
  }
  return uVar2;
}


/* ==== FUN_0042e838 @ 0042e838 ==== */

undefined4 FUN_0042e838(void)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  FUN_0043b007(1);
  DAT_0045f860 = PTR_DAT_0044f818;
  piVar2 = FUN_00414862();
  if (piVar2 == (int *)0x0) {
    uVar3 = 0;
  }
  else if (*DAT_0045f860 == '\0') {
    if ((piVar2[6] & 0x8000000U) == 0) {
      if (piVar2[4] == 0x100) {
        iVar1 = piVar2[2];
        FUN_004167ef(piVar2);
        DAT_0045eba4 = (void *)((int)DAT_0045eba4 + 1);
        if (iVar1 == 0) {
          uVar3 = FUN_0042e939(1);
        }
        else {
          uVar3 = FUN_0042eb07(DAT_0045eba4,1);
        }
      }
      else {
        FUN_004167ef(piVar2);
        FUN_00413085((uint *)s_Expression_result_must_be_intege_004579a4);
        uVar3 = 0;
      }
    }
    else {
      FUN_004167ef(piVar2);
      FUN_00413085((uint *)s_Expression_contains_forward_refe_0045797c);
      uVar3 = 0;
    }
  }
  else {
    FUN_00413085((uint *)s_Extra_characters_beyond_expressi_00457958);
    uVar3 = 0;
  }
  return uVar3;
}


/* ==== FUN_0042e939 @ 0042e939 ==== */

undefined4 __cdecl FUN_0042e939(int param_1)

{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  undefined4 uVar4;
  void *this;
  int local_10;
  
  local_10 = 1;
  if (DAT_0044f778 != '\0') {
    FUN_0041bdca(' ');
  }
  do {
    while( true ) {
      while( true ) {
        iVar1 = FUN_0041983e();
        if (iVar1 == 0) {
          FUN_00413085((uint *)s_Unexpected_end_of_file___missing_004579f0);
          DAT_0045ea54 = 1;
          return 0;
        }
        iVar1 = FUN_0041a4bc();
        if (iVar1 != 0) break;
        if (DAT_0045ea2c != '\0') {
          FUN_0041c742(0x69);
        }
      }
      if ((*PTR_DAT_0044f814 != '\0') && (uVar2 = strlen(PTR_DAT_0044f814), uVar2 < 0x10)) break;
LAB_0042eabc:
      if (DAT_0045ea2c != '\0') {
        FUN_0041bdca('i');
      }
    }
    puVar3 = (uint *)FUN_00438f9c(PTR_DAT_0044f814);
    iVar1 = FUN_0043903f(puVar3,1);
    if (iVar1 == 0) goto LAB_0042eabc;
    if (*(char *)(iVar1 + 4) != '\b') {
      if (*(char *)(iVar1 + 4) == '\x15') {
        local_10 = local_10 + -1;
        if (local_10 == 0) {
          FUN_0042baac(0);
          FUN_0043b007(0);
          if (0 < DAT_0045eba4) {
            DAT_0045eba4 = DAT_0045eba4 + -1;
          }
          DAT_0045ea54 = DAT_0044f778 != '\x01';
          return 1;
        }
      }
      else if (*(char *)(iVar1 + 4) == '\x12') {
        if (local_10 == 1) {
          if (param_1 != 0) {
            FUN_0042baac(0);
            FUN_0043b007(0);
            uVar4 = FUN_0042eb07(this,0);
            return uVar4;
          }
          DAT_0045f860 = 0;
          FUN_00413085((uint *)s_ELSE_without_associated_IF_direc_004579c8);
        }
      }
      else if (*(char *)(iVar1 + 4) == '\x1e') {
        local_10 = local_10 + 1;
      }
      goto LAB_0042eabc;
    }
    FUN_0042baac(0);
    FUN_0042fec3(1);
  } while( true );
}


/* ==== FUN_0042eb07 @ 0042eb07 ==== */

undefined4 __thiscall FUN_0042eb07(void *this,int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (DAT_0044f778 != '\0') {
    FUN_0041bdca(' ');
  }
  do {
    iVar1 = FUN_0041983e();
    if (iVar1 == 0) {
      FUN_00413085((uint *)s_Unexpected_end_of_file___missing_00457a18);
      DAT_0045ea54 = 1;
      return 0;
    }
    FUN_0041d334();
    iVar1 = FUN_0041a4bc();
    if (iVar1 == 0) {
      FUN_0041c742(0x20);
    }
    else {
      iVar1 = FUN_0041af7e(1,param_1);
      if (iVar1 == 0x15) {
        FUN_0042baac(0);
        FUN_0043b007(0);
        if (0 < DAT_0045eba4) {
          DAT_0045eba4 = DAT_0045eba4 + -1;
        }
        DAT_0045ea54 = '\x01' - (DAT_0044f778 != '\0');
        return 1;
      }
      if (iVar1 == 0x12) {
        FUN_0042baac(0);
        FUN_0043b007(0);
        uVar2 = FUN_0042e939(0);
        return uVar2;
      }
      FUN_0041bdca(' ');
    }
    DAT_0045f924 = 0;
    DAT_0045f928 = 0;
    DAT_0045f92c = 0;
  } while( true );
}


/* ==== FUN_0042ec12 @ 0042ec12 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_0042ec12(char *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  char local_28;
  uint local_24;
  char *local_20;
  char local_1c [12];
  int local_10;
  int local_c;
  int local_8;
  
  local_c = 0;
  FUN_0043b007(1);
  if (*param_1 == '\0') {
    FUN_00413085((uint *)s_Missing_option_00457a40);
    uVar1 = 0;
  }
  else {
    while (*param_1 != '\0') {
      local_10 = 0;
      local_20 = local_1c;
      for (; (*param_1 != '\0' && (*param_1 != ',')); param_1 = param_1 + 1) {
        iVar2 = local_10 + 1;
        if (7 < local_10) {
          local_10 = iVar2;
          FUN_00413085((uint *)s_Illegal_option_00457a50);
          return 0;
        }
        if (__mb_cur_max < 2) {
          local_24 = *(ushort *)(_pctype + *param_1 * 2) & 1;
          local_10 = iVar2;
        }
        else {
          local_10 = iVar2;
          local_24 = _isctype((int)*param_1,1);
        }
        if (local_24 == 0) {
          local_28 = *param_1;
        }
        else {
          iVar2 = tolower((int)*param_1);
          local_28 = (char)iVar2;
        }
        *local_20 = local_28;
        local_20 = local_20 + 1;
      }
      *local_20 = '\0';
      if (local_1c[0] == '\0') {
        FUN_00413085((uint *)s_Missing_option_00457a60);
        return 0;
      }
      local_8 = FUN_004390e6(local_1c);
      if (local_8 == 0) {
        FUN_00413085((uint *)s_Illegal_option_00457a70);
        return 0;
      }
      switch(*(undefined4 *)(local_8 + 4)) {
      case 0:
        break;
      case 1:
        DAT_0045ea38 = 1;
        DAT_0045f930 = 0;
        break;
      case 2:
        DAT_0044f778 = 1;
        break;
      case 3:
        DAT_0044f784 = 1;
        break;
      case 4:
        DAT_0045ea38 = 1;
        break;
      case 5:
        if ((((DAT_0045f8fc == 1) && (DAT_0045ea3c == '\0')) && (DAT_0045ea40 == '\0')) &&
           (DAT_00463c5c == 0)) {
          if ((DAT_0045eb64 == 0) && (DAT_0045eb6c == 0)) {
            local_30 = 0;
          }
          else {
            local_30 = 1;
          }
          DAT_00463c5c = local_30;
        }
        if (DAT_00463c5c == 0) {
          DAT_0045ea3c = '\x01';
          DAT_0045ea40 = '\x01';
        }
        else {
          FUN_00413085((uint *)s_CRE_option_must_be_used_before_a_00457a80);
        }
        break;
      case 6:
        DAT_0045ea48 = 1;
        break;
      case 7:
        DAT_0044f780 = 1;
        break;
      case 8:
        DAT_0044f77c = 1;
        break;
      case 9:
        DAT_0045ea30 = 1;
        break;
      case 10:
        DAT_0045ea38 = 0;
        break;
      case 0xb:
        DAT_0044f778 = 0;
        break;
      case 0xc:
        DAT_0044f784 = 0;
        break;
      case 0xd:
        DAT_0045ea48 = 0;
        break;
      case 0xe:
        DAT_0044f780 = 0;
        break;
      case 0xf:
        DAT_0044f77c = 0;
        break;
      case 0x10:
        DAT_0045ea30 = 0;
        break;
      case 0x11:
        DAT_0045ea2c = 0;
        break;
      case 0x12:
        DAT_0044f788 = 0;
        break;
      case 0x13:
        DAT_0045ea40 = '\x01';
        break;
      case 0x14:
        DAT_0045ea2c = 1;
        break;
      case 0x15:
        DAT_0044f788 = 1;
        break;
      case 0x16:
        DAT_0045ea0c = 1;
        break;
      case 0x17:
        DAT_0045ea0c = 0;
        break;
      case 0x18:
        DAT_0045ea34 = 1;
        break;
      case 0x19:
        if (1 < DAT_0045f8fc) {
          if ((DAT_0045ea10 == '\0') && (DAT_0045ea60 != '\0')) {
            FUN_00413085((uint *)s_MU_option_must_be_used_before_an_00457c70);
          }
          else {
            DAT_0045ea10 = '\x01';
          }
        }
        break;
      case 0x1a:
        if (((DAT_0045f8fc == 1) && (local_c == 0)) && (DAT_00463c54 == 0)) {
          DAT_00463c54 = (uint)(DAT_0045eb6c != 0);
        }
        if (DAT_00463c54 == 0) {
          local_c = 1;
        }
        else {
          FUN_00413085((uint *)s_LOC_option_must_be_used_before_a_00457c40);
        }
        break;
      case 0x1b:
        DAT_0045ea44 = 1;
        break;
      case 0x1c:
        DAT_0045ea64 = 1;
        break;
      case 0x1d:
        DAT_0045ea64 = 0;
        break;
      case 0x1e:
        DAT_0045ea90 = 1;
        break;
      case 0x1f:
        DAT_0045ea90 = 0;
        break;
      case 0x20:
        if (((DAT_0045f8fc == 1) && (DAT_0045ea88 == '\0')) && (DAT_00463c40 == 0)) {
          if ((DAT_0045eb64 == 0) && (DAT_0045eb6c == 0)) {
            local_3c = 0;
          }
          else {
            local_3c = 1;
          }
          DAT_00463c40 = local_3c;
        }
        if (DAT_00463c40 == 0) {
          DAT_0045ea88 = '\x01';
        }
        else {
          FUN_00413085((uint *)s_XR_option_must_be_used_before_an_00457d70);
        }
        break;
      default:
        FUN_00412fa0((uint *)s_Option_select_error_00457d98);
        break;
      case 0x22:
        DAT_0045ea8c = 1;
        break;
      case 0x23:
        DAT_0045ea8c = 0;
        break;
      case 0x24:
        DAT_0044f79c = 1;
        break;
      case 0x25:
        DAT_0044f79c = 0;
        break;
      case 0x28:
        if (((DAT_0045f8fc == 1) && (DAT_0045eaa0 == '\0')) && (DAT_00463c30 == 0)) {
          if (((DAT_0045eb64 == 0) && (DAT_0045eba0 == 0)) &&
             ((DAT_0045fb70 == 0 && (*(int *)(PTR_DAT_0044f980 + 0x8c) == 0)))) {
            local_34 = 0;
          }
          else {
            local_34 = 1;
          }
          DAT_00463c30 = local_34;
        }
        if (DAT_00463c30 == 0) {
          DAT_0045eaa0 = '\x01';
        }
        else {
          FUN_00413085((uint *)s_IC_option_must_be_used_before_an_00457b04);
        }
        break;
      case 0x29:
        if (((DAT_0045f8fc == 1) && (DAT_0045eaa4 == '\0')) && (DAT_00463c48 == 0)) {
          DAT_00463c48 = (int)DAT_0045ea60;
        }
        if (DAT_00463c48 == 0) {
          DAT_0045eaa4 = '\x01';
        }
        else {
          FUN_00413085((uint *)s_LB_option_must_be_used_before_an_00457b4c);
        }
        break;
      case 0x2a:
        if (((DAT_0045f8fc == 1) && (DAT_0045eaa8 == '\0')) && (DAT_00463c38 == 0)) {
          DAT_00463c38 = (int)DAT_0045ea60;
        }
        if (DAT_00463c38 == 0) {
          DAT_0045eaa8 = '\x01';
        }
        else {
          FUN_00413085((uint *)s_LBX_option_must_be_used_before_a_00457b88);
        }
        break;
      case 0x2b:
        DAT_0045eaac = 1;
        break;
      case 0x2c:
        DAT_0045eaac = 0;
        break;
      case 0x2d:
        DAT_0044f7a4 = 1;
        break;
      case 0x2e:
        DAT_0044f7a4 = 0;
        break;
      case 0x2f:
        if (((DAT_0045f8fc == 1) && (DAT_0045eab4 == '\0')) && (DAT_00463c3c == 0)) {
          DAT_00463c3c = (uint)(DAT_0045fb80 != 0);
        }
        if (DAT_00463c3c == 0) {
          DAT_0045eab4 = '\x01';
        }
        else {
          FUN_00413085((uint *)s_GS_option_must_be_used_before_an_00457ad8);
        }
        break;
      case 0x30:
        if (((DAT_0045f8fc == 1) && (DAT_0045eab4 != '\0')) && (DAT_00463c44 == 0)) {
          DAT_00463c44 = (uint)(DAT_0045fb80 != 0);
        }
        if (DAT_00463c44 == 0) {
          DAT_0045eab4 = '\0';
        }
        else {
          FUN_00413085((uint *)s_NOGS_option_must_be_used_before_a_00457cac);
        }
        break;
      case 0x31:
        DAT_0045eac4 = 1;
        break;
      case 0x32:
        DAT_0045eac4 = 0;
        break;
      case 0x33:
        DAT_0044f7ac = 1;
        break;
      case 0x34:
        DAT_0044f7ac = 0;
        break;
      case 0x35:
        DAT_0044f7a8 = 1;
        break;
      case 0x36:
        DAT_0044f7a8 = 0;
        break;
      case 0x37:
        DAT_0044f7b0 = 1;
        break;
      case 0x38:
        DAT_0044f7b0 = 0;
        break;
      case 0x39:
        FUN_00405fbe(1);
        break;
      case 0x3a:
        FUN_00405fbe(0);
        break;
      case 0x3b:
        DAT_0045ead4 = 1;
        break;
      case 0x3c:
        DAT_0045ead4 = 0;
        break;
      case 0x3d:
        DAT_0045ea94 = 1;
        break;
      case 0x3e:
        DAT_0045ea94 = 0;
        break;
      case 0x3f:
        DAT_0045ead0 = 1;
        break;
      case 0x40:
        DAT_0045ead0 = 0;
        break;
      case 0x41:
        DAT_0045eaf4 = 1;
        break;
      case 0x42:
        DAT_0045eaf4 = 0;
        break;
      case 0x43:
        DAT_0045eaf8 = 1;
        DAT_0045ebe4 = 0;
        break;
      case 0x44:
        DAT_0045eaf8 = 0;
        break;
      case 0x45:
        DAT_0045eaf8 = 1;
        break;
      case 0x46:
        DAT_0045eb04 = 1;
        break;
      case 0x47:
        DAT_0045eb04 = 0;
        break;
      case 0x48:
        DAT_0045eb08 = 1;
        break;
      case 0x49:
        DAT_0045eb08 = 0;
        break;
      case 0x4a:
        DAT_0044f7b4 = 1;
        break;
      case 0x4b:
        DAT_0044f7b4 = 0;
        break;
      case 0x4c:
        DAT_0045eb18 = 1;
        break;
      case 0x4d:
        if (((DAT_0045f8fc == 1) && (DAT_0045eab0 == '\0')) && (DAT_00463c4c == 0)) {
          DAT_00463c4c = (uint)(DAT_0045fb80 != 0);
        }
        if (DAT_00463c4c == 0) {
          DAT_0045eab0 = '\x01';
        }
        else {
          FUN_00413085((uint *)s_GL_option_must_be_used_before_an_00457aac);
        }
        break;
      case 0x4e:
        if (((DAT_0045f8fc == 1) && (DAT_0045eb0c == '\0')) && (DAT_00463c34 == 0)) {
          DAT_00463c34 = (uint)(DAT_0045eb6c != 0);
        }
        if (DAT_00463c34 == 0) {
          DAT_0045eb0c = '\x01';
        }
        else {
          FUN_00413085((uint *)s_XLL_option_must_be_used_before_a_00457d40);
        }
        break;
      case 0x4f:
        DAT_0044f78c = 1;
        break;
      case 0x50:
        DAT_0044f78c = 0;
        break;
      case 0x51:
        DAT_0044f7b8 = 1;
        break;
      case 0x52:
        DAT_0044f7b8 = 0;
        break;
      case 0x53:
        if (DAT_0045f8fc != 1) {
          if (((DAT_0045eb1c == '\0') && (DAT_0045fca8 != 0)) && (DAT_0045ea60 != '\0')) {
            FUN_00413085((uint *)s_SVO_option_must_be_used_before_a_00457d04);
          }
          else {
            DAT_0045eb1c = '\x01';
          }
        }
        break;
      case 0x54:
        if (((DAT_0045f8fc == 1) && (DAT_0045eb20 == '\0')) && (DAT_00463c58 == 0)) {
          if ((DAT_0045eb64 == 0) && (DAT_0045eb6c == 0)) {
            local_38 = 0;
          }
          else {
            local_38 = 1;
          }
          DAT_00463c58 = local_38;
        }
        if (DAT_00463c58 == 0) {
          DAT_0045eb20 = '\x01';
        }
        else {
          FUN_00413085((uint *)s_SCO_option_must_be_used_before_a_00457cd8);
        }
        break;
      case 0x55:
        if (((DAT_0045f8fc == 1) && (DAT_0045eb24 == '\0')) && (DAT_00463c50 == 0)) {
          DAT_00463c50 = (int)DAT_0045ea60;
        }
        if (DAT_00463c50 == 0) {
          if (DAT_0045f858 == 0) {
            if (DAT_0045f8fc == 2) {
              FUN_004137f6(s_LDB_option_with_no_listing_file_s_00457c00);
            }
          }
          else {
            DAT_0045eb24 = '\x01';
          }
        }
        else {
          FUN_00413085((uint *)s_LDB_option_must_be_used_before_a_00457bc4);
        }
        break;
      case 0x56:
        DAT_0045eb48 = 1;
        break;
      case 0x57:
        DAT_0045eb48 = 0;
        break;
      case 0x58:
        DAT_0045eb2c = 1;
        break;
      case 0x59:
        DAT_0045eb2c = 0;
        break;
      case 0x5a:
        DAT_0045eb30 = 1;
        break;
      case 0x5b:
        DAT_0045eb30 = 0;
        break;
      case 0x5c:
        DAT_0044f774 = 1;
        break;
      case 0x5d:
        DAT_0044f774 = 0;
        break;
      case 0x62:
        DAT_0044f7bc = 1;
        break;
      case 99:
        DAT_0044f7bc = 0;
        break;
      case 0x66:
        DAT_0044f7c0 = 1;
        break;
      case 0x67:
        DAT_0044f7c0 = 0;
        break;
      case 0x6a:
        DAT_0044f7c4 = 1;
        break;
      case 0x6b:
        DAT_0044f7c4 = 0;
        break;
      case 0x70:
        DAT_0045eb14 = 1;
        break;
      case 0x71:
        DAT_0045eb14 = 0;
        break;
      case 0x72:
        _DAT_0044f754 = 1;
        break;
      case 0x73:
        _DAT_0044f754 = 0;
        break;
      case 0x74:
        _DAT_0044f758 = 1;
        break;
      case 0x75:
        _DAT_0044f758 = 0;
        break;
      case 0x76:
        _DAT_0044f760 = 1;
        break;
      case 0x77:
        _DAT_0044f760 = 0;
        break;
      case 0x78:
        _DAT_0044f764 = 1;
        break;
      case 0x79:
        _DAT_0044f764 = 0;
        break;
      case 0x7a:
        _DAT_0044f768 = 1;
        break;
      case 0x7b:
        _DAT_0044f768 = 0;
        break;
      case 0x7c:
        _DAT_0044f76c = 1;
        break;
      case 0x7d:
        _DAT_0044f76c = 0;
        break;
      case 0x7e:
        _DAT_0044f75c = 1;
        break;
      case 0x7f:
        _DAT_0044f75c = 0;
        break;
      case 0x80:
        _DAT_0044f750 = 1;
        break;
      case 0x81:
        _DAT_0044f750 = 0;
      }
      if (*param_1 != '\0') {
        param_1 = param_1 + 1;
      }
    }
    if ((local_c != 0) && ((DAT_0045ea3c != '\0' || (DAT_0045ea40 != '\0')))) {
      DAT_0045ea4c = 1;
    }
    uVar1 = 1;
  }
  return uVar1;
}


/* ==== FUN_0042f9fb @ 0042f9fb ==== */

undefined4 __cdecl FUN_0042f9fb(char *param_1)

{
  int iVar1;
  char local_24;
  uint local_20;
  char *local_1c;
  int local_18;
  char local_14 [12];
  undefined4 *local_8;
  
  FUN_0043b007(1);
  if (*param_1 == '\0') {
    DAT_0044f9fc = 0x1fff;
  }
  else {
    while (*param_1 != '\0') {
      local_18 = 0;
      local_1c = local_14;
      for (; (*param_1 != '\0' && (*param_1 != ',')); param_1 = param_1 + 1) {
        if (7 < local_18) {
          FUN_00413085((uint *)s_Illegal_revision_00457dac);
          return 0;
        }
        if (__mb_cur_max < 2) {
          local_20 = *(ushort *)(_pctype + *param_1 * 2) & 1;
        }
        else {
          local_20 = _isctype((int)*param_1,1);
        }
        if (local_20 == 0) {
          local_24 = *param_1;
        }
        else {
          iVar1 = tolower((int)*param_1);
          local_24 = (char)iVar1;
        }
        *local_1c = local_24;
        local_1c = local_1c + 1;
        local_18 = local_18 + 1;
      }
      *local_1c = '\0';
      if (local_14[0] == '\0') {
        FUN_00413085((uint *)s_Missing_revision_00457dc0);
        return 0;
      }
      local_8 = (undefined4 *)FUN_00439120(local_14);
      if (local_8 == (undefined4 *)0x0) {
        FUN_00413085((uint *)s_Illegal_revision_00457dd4);
        return 0;
      }
      DAT_0045fcbc = *local_8;
      DAT_0044f9fc = local_8[1] + -1;
      if (*param_1 != '\0') {
        param_1 = param_1 + 1;
      }
    }
  }
  return 1;
}


/* ==== FUN_0042fb7e @ 0042fb7e ==== */

undefined4 __cdecl FUN_0042fb7e(char *param_1)

{
  int iVar1;
  char local_2c;
  uint local_28;
  char *local_24;
  int local_20;
  char local_1c [20];
  int local_8;
  
  FUN_0043b007(1);
  if (*param_1 == '\0') {
    DAT_0044f9fc = 0x1fff;
  }
  else {
    while (*param_1 != '\0') {
      local_20 = 0;
      local_24 = local_1c;
      for (; (*param_1 != '\0' && (*param_1 != ',')); param_1 = param_1 + 1) {
        if (0xf < local_20) {
          FUN_00413085((uint *)s_Illegal_processor_type_00457de8);
          return 0;
        }
        if (__mb_cur_max < 2) {
          local_28 = *(ushort *)(_pctype + *param_1 * 2) & 1;
        }
        else {
          local_28 = _isctype((int)*param_1,1);
        }
        if (local_28 == 0) {
          local_2c = *param_1;
        }
        else {
          iVar1 = tolower((int)*param_1);
          local_2c = (char)iVar1;
        }
        *local_24 = local_2c;
        local_24 = local_24 + 1;
        local_20 = local_20 + 1;
      }
      *local_24 = '\0';
      if (local_1c[0] == '\0') {
        FUN_00413085((uint *)s_Missing_processor_type_00457e00);
        return 0;
      }
      local_8 = FUN_0043915a(local_1c);
      if (local_8 == 0) {
        FUN_00413085((uint *)s_Illegal_processor_type_00457e18);
        return 0;
      }
      if (*(int *)(local_8 + 4) == 0x2000) {
        DAT_0044f9fc = 2;
        DAT_0044fa00 = *(undefined4 *)(local_8 + 4);
      }
      else {
        DAT_0044f9fc = *(undefined4 *)(local_8 + 4);
      }
      if (*param_1 != '\0') {
        param_1 = param_1 + 1;
      }
    }
  }
  return 1;
}


/* ==== FUN_0042fd1e @ 0042fd1e ==== */

undefined4 FUN_0042fd1e(void)

{
  char cVar1;
  uint *puVar2;
  int iVar3;
  
  if (PTR_DAT_0044f978 == &DAT_0044f878) {
    FUN_0043b007(1);
    DAT_0045f860 = PTR_DAT_0044f818;
    if (*PTR_DAT_0044f818 == '\0') {
      FUN_00413085((uint *)s_Missing_directive_name_00457e5c);
    }
    else {
      do {
        if (*DAT_0045f860 == '\0') {
          return 1;
        }
        puVar2 = (uint *)FUN_0043b448();
        if (puVar2 == (uint *)0x0) {
          return 0;
        }
        iVar3 = FUN_00438f1a(puVar2,1);
        if (iVar3 == 0) {
          iVar3 = FUN_0043903f(puVar2,1);
          if (iVar3 == 0) {
            FUN_004131f9((uint *)s_Assembler_directive_or_mnemonic_n_00457e74,(char *)puVar2);
          }
          else {
            *(byte *)(iVar3 + 4) = *(byte *)(iVar3 + 4) | 0x80;
          }
        }
        else {
          *(byte *)(iVar3 + 4) = *(byte *)(iVar3 + 4) | 0x80;
        }
      } while ((*DAT_0045f860 == '\0') ||
              (cVar1 = *DAT_0045f860, DAT_0045f860 = DAT_0045f860 + 1, cVar1 == ','));
      FUN_00413085((uint *)s_Syntax_error_in_directive_name_l_00457ea0);
    }
  }
  else {
    FUN_00413085((uint *)s_RDIRECT_directive_not_allowed_in_00457e30);
  }
  return 0;
}


/* ==== FUN_0042fe46 @ 0042fe46 ==== */

void FUN_0042fe46(void)

{
  undefined **local_c;
  undefined **local_8;
  
  for (local_c = &PTR_DAT_0044e0b0; local_c < &PTR_DAT_0044e0b0 + DAT_0044ebc8 * 5;
      local_c = local_c + 5) {
    *(byte *)(local_c + 1) = *(byte *)(local_c + 1) & 0x7f;
  }
  for (local_8 = &PTR_DAT_0044fab0; local_8 < &PTR_DAT_0044fab0 + DAT_0044fd08 * 2;
      local_8 = local_8 + 2) {
    *(byte *)(local_8 + 1) = *(byte *)(local_8 + 1) & 0x7f;
  }
  return;
}


/* ==== FUN_0042feb9 @ 0042feb9 ==== */

undefined4 FUN_0042feb9(void)

{
  return 1;
}


/* ==== FUN_0042fec3 @ 0042fec3 ==== */

undefined4 __cdecl FUN_0042fec3(int param_1)

{
  char cVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  int iVar2;
  
  if (*PTR_DAT_0044f818 != '\0') {
    cVar1 = *PTR_DAT_0044f818;
    DAT_0045f860 = PTR_DAT_0044f818 + 1;
    if ((param_1 == 0) || (DAT_0045ea2c != '\0')) {
      FUN_0041c742((-(uint)(param_1 != 0) & 0x49) + 0x20);
    }
    iVar2 = (int)cVar1;
    cVar1 = strchr(DAT_0045f860,iVar2);
    if (CONCAT31(extraout_var,cVar1) == 0) {
      iVar2 = (int)(char)iVar2;
      cVar1 = strchr(PTR_DAT_0044f81c,iVar2);
      if (CONCAT31(extraout_var_00,cVar1) == 0) {
        iVar2 = (int)(char)iVar2;
        cVar1 = strchr(PTR_DAT_0044f820,iVar2);
        if ((CONCAT31(extraout_var_01,cVar1) == 0) &&
           (cVar1 = strchr(PTR_DAT_0044f824,(int)(char)iVar2), CONCAT31(extraout_var_02,cVar1) == 0)
           ) {
          do {
            cVar1 = -0x5e;
            iVar2 = FUN_0041983e();
            if (iVar2 == 0) {
              FUN_00413085((uint *)s_Unexpected_end_of_file___missing_00457ec4);
              DAT_0045ea54 = 1;
              return 0;
            }
            if ((param_1 == 0) || (DAT_0045ea2c != '\0')) {
              iVar2 = (-(uint)(param_1 != 0) & 0x49) + 0x20;
              FUN_0041c742(iVar2);
              cVar1 = (char)iVar2;
            }
            cVar1 = strchr(&DAT_0045ec08,(int)cVar1);
          } while (CONCAT31(extraout_var_03,cVar1) == 0);
          DAT_0045ea54 = param_1 == 0;
          return 1;
        }
      }
    }
    DAT_0045ea54 = param_1 == 0;
  }
  return 1;
}


/* ==== FUN_00430015 @ 00430015 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00430015(void)

{
  undefined4 uVar1;
  int *piVar2;
  undefined1 local_c;
  
  FUN_0043b007(1);
  DAT_0045ea18 = 1;
  if (*PTR_DAT_0044f818 == '\0') {
    uVar1 = 1;
  }
  else {
    DAT_0045f860 = PTR_DAT_0044f818;
    piVar2 = FUN_00413c50(DAT_0044f91c);
    if (piVar2 == (int *)0x0) {
      uVar1 = 0;
    }
    else if ((piVar2[7] == 0) || (piVar2[7] == 4)) {
      DAT_0045ea1c = 1;
      DAT_0045f8e4 = piVar2[2];
      DAT_0044f908 = piVar2[7];
      if (((piVar2[6] & 0x1000U) == 0) && (-1 < piVar2[0xf])) {
        local_c = 0;
      }
      else {
        local_c = 1;
      }
      DAT_0045ea20 = local_c;
      FUN_004167ef(piVar2);
      if (((DAT_0045f8fc == 2) && (DAT_0044f790 != '\0')) && (DAT_0045fca8 != 0)) {
        _DAT_00465bc8 = FUN_0042456e((uint *)&DAT_0045f428);
        DAT_0045ea24 = 1;
      }
      uVar1 = 1;
    }
    else {
      FUN_00413085((uint *)s_Memory_space_must_be_P_or_NONE_00457ef8);
      uVar1 = 0;
    }
  }
  return uVar1;
}


/* ==== FUN_0043012d @ 0043012d ==== */

undefined4 * __cdecl FUN_0043012d(uint *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *local_210;
  uint local_20c [129];
  undefined4 *local_8;
  
  local_8 = (undefined4 *)0x0;
  if (DAT_0045eaa0 != '\0') {
    strcpy((char *)local_20c,(char *)param_1);
    FUN_0043b836((char *)local_20c);
    param_1 = local_20c;
  }
  uVar1 = FUN_00439b65((char *)param_1);
  for (local_210 = *(undefined4 **)(&DAT_00460c88 + uVar1 * 4); local_210 != (undefined4 *)0x0;
      local_210 = (undefined4 *)local_210[4]) {
    if (((char)*param_1 == *(char *)*local_210) &&
       (iVar2 = strcmp((char *)param_1,(char *)*local_210), iVar2 == 0)) {
      if ((undefined *)local_210[3] == PTR_DAT_0044f978) break;
      if (((param_2 != 1) && (local_8 == (undefined4 *)0x0)) &&
         ((undefined *)local_210[3] == &DAT_0044f878)) {
        local_8 = local_210;
      }
    }
  }
  if ((local_210 == (undefined4 *)0x0) && (local_8 != (undefined4 *)0x0)) {
    local_210 = local_8;
  }
  return local_210;
}


/* ==== FUN_00430239 @ 00430239 ==== */

undefined4 __cdecl FUN_00430239(uint *param_1,uint *param_2,int param_3)

{
  undefined4 *puVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
  puVar1 = FUN_0043012d(param_1,1);
  if (puVar1 != (undefined4 *)0x0) {
    FUN_0041351d((uint *)s_Redefinition_of_symbol_00457f18,(char *)param_1);
    FUN_0043035b(param_1);
  }
  piVar2 = (int *)FUN_00439857(0x14);
  uVar3 = strlen((char *)param_1);
  iVar4 = FUN_00439857(uVar3 + 1);
  *piVar2 = iVar4;
  strcpy((char *)*piVar2,(char *)param_1);
  if (DAT_0045eaa0 != '\0') {
    FUN_0043b836((char *)*piVar2);
  }
  uVar3 = strlen((char *)param_2);
  iVar4 = FUN_00439857(uVar3 + 1);
  piVar2[1] = iVar4;
  strcpy((char *)piVar2[1],(char *)param_2);
  piVar2[2] = param_3;
  piVar2[3] = (int)PTR_DAT_0044f978;
  uVar3 = FUN_00439b65((char *)*piVar2);
  piVar2[4] = *(int *)(&DAT_00460c88 + uVar3 * 4);
  *(int **)(&DAT_00460c88 + uVar3 * 4) = piVar2;
  DAT_0045eba0 = DAT_0045eba0 + 1;
  DAT_0045ea68 = 1;
  return 1;
}


/* ==== FUN_0043035b @ 0043035b ==== */

undefined4 __cdecl FUN_0043035b(uint *param_1)

{
  int iVar1;
  int *local_21c;
  uint local_218 [129];
  uint local_14;
  int *local_10;
  int *local_c;
  int *local_8;
  
  local_8 = (int *)0x0;
  local_c = (int *)0x0;
  if (DAT_0045eaa0 != '\0') {
    strcpy((char *)local_218,(char *)param_1);
    FUN_0043b836((char *)local_218);
    param_1 = local_218;
  }
  local_14 = FUN_00439b65((char *)param_1);
  local_10 = (int *)0x0;
  for (local_21c = *(int **)(&DAT_00460c88 + local_14 * 4); local_21c != (int *)0x0;
      local_21c = (int *)local_21c[4]) {
    if (((char)*param_1 == *(char *)*local_21c) &&
       (iVar1 = strcmp((char *)param_1,(char *)*local_21c), iVar1 == 0)) {
      if ((undefined *)local_21c[3] == PTR_DAT_0044f978) break;
      if (((undefined *)local_21c[3] == &DAT_0044f878) ||
         ((*(uint *)(local_21c[3] + 0xc) & 0x40) != 0)) {
        local_8 = local_21c;
        local_c = local_10;
      }
    }
    local_10 = local_21c;
  }
  if (local_21c == (int *)0x0) {
    if (local_8 == (int *)0x0) {
      FUN_004131f9((uint *)s_Symbol_not_previously_defined_00457f30,(char *)param_1);
      return 0;
    }
    local_21c = local_8;
    local_10 = local_c;
  }
  if (*local_21c != 0) {
    FUN_004398b5((undefined *)*local_21c);
    *local_21c = 0;
  }
  if (local_21c[1] != 0) {
    FUN_004398b5((undefined *)local_21c[1]);
    local_21c[1] = 0;
  }
  if (local_10 == (int *)0x0) {
    *(int *)(&DAT_00460c88 + local_14 * 4) = local_21c[4];
  }
  else {
    local_10[4] = local_21c[4];
  }
  FUN_004398b5((undefined *)local_21c);
  DAT_0045eba0 = DAT_0045eba0 + -1;
  if (DAT_0045eba0 < 1) {
    DAT_0045eba0 = 0;
    DAT_0045ea68 = 0;
  }
  return 1;
}


/* ==== FUN_0043055e @ 0043055e ==== */

void FUN_0043055e(void)

{
  int *piVar1;
  int *local_10;
  int local_c;
  
  local_c = 0;
  do {
    if (0x3f0 < local_c) {
      return;
    }
    local_10 = *(int **)(&DAT_00460c88 + local_c * 4);
    if (local_10 != (int *)0x0) {
      *(undefined4 *)(&DAT_00460c88 + local_c * 4) = 0;
      while (local_10 != (int *)0x0) {
        if ((DAT_0045ea98 != '\0') && (local_10[2] != 0)) {
          *(int **)(&DAT_00460c88 + local_c * 4) = local_10;
          break;
        }
        if (*local_10 != 0) {
          FUN_004398b5((undefined *)*local_10);
          *local_10 = 0;
        }
        if (local_10[1] != 0) {
          FUN_004398b5((undefined *)local_10[1]);
          local_10[1] = 0;
        }
        piVar1 = (int *)local_10[4];
        FUN_004398b5((undefined *)local_10);
        local_10 = piVar1;
      }
    }
    local_c = local_c + 1;
  } while( true );
}


/* ==== FUN_0043063f @ 0043063f ==== */

undefined4 FUN_0043063f(void)

{
  char *pcVar1;
  char cVar2;
  undefined4 uVar3;
  undefined3 extraout_var;
  uint uVar4;
  uint local_1c;
  char *local_18;
  char *local_14;
  char local_10;
  char *local_c;
  int *local_8;
  
  local_14 = &DAT_0045f220;
  local_8 = (int *)0x0;
  if ((DAT_0045f8fc < 2) || (DAT_0045ea34 != '\0')) {
    uVar3 = 1;
  }
  else if (DAT_0045fcac == &DAT_0045a470) {
    FUN_004133a9((uint *)s_PRCTL_directive_ignored___no_exp_00457f50);
    uVar3 = 0;
  }
  else {
    FUN_0043b007(1);
    while (DAT_0045f860 != (char *)0x0) {
      cVar2 = strchr(DAT_0045f860,0x2c);
      local_c = (char *)CONCAT31(extraout_var,cVar2);
      if (DAT_0045f860 == local_c) {
        *local_14 = '\0';
        pcVar1 = local_14 + 1;
        if (local_c[1] == '\0') {
          local_14[1] = '\0';
          local_c = (char *)0x0;
          pcVar1 = local_14 + 2;
        }
      }
      else if (((*DAT_0045f860 == '\'') || (*DAT_0045f860 == '\"')) || (*DAT_0045f860 == '[')) {
        local_c = FUN_0043b08d(DAT_0045f860,local_14);
        if (local_c == (char *)0x0) {
          return 0;
        }
        uVar4 = strlen(local_14);
        pcVar1 = local_14 + uVar4;
        if (*local_c == '\0') {
          local_c = (char *)0x0;
        }
      }
      else {
        if (local_c != (char *)0x0) {
          *local_c = '\0';
        }
        local_8 = FUN_00413f38();
        if (local_c != (char *)0x0) {
          *local_c = ',';
        }
        if (local_8 == (int *)0x0) {
          return 0;
        }
        *local_14 = (char)local_8[2];
        pcVar1 = local_14 + 1;
      }
      local_14 = pcVar1;
      if (local_8 != (int *)0x0) {
        FUN_004167ef(local_8);
        local_8 = (int *)0x0;
      }
      if (local_c == (char *)0x0) {
        local_18 = (char *)0x0;
      }
      else {
        local_18 = local_c + 1;
      }
      DAT_0045f860 = local_18;
    }
    DAT_0045f900[1] = DAT_0045f900[1] + -1;
    if (DAT_0045f900[1] < 0) {
      local_1c = _filbuf(DAT_0045f900);
    }
    else {
      local_1c = (uint)*(byte *)*DAT_0045f900;
      *DAT_0045f900 = *DAT_0045f900 + 1;
    }
    if ((local_1c == 0xffffffff) && (DAT_0045fc28 == 0)) {
      FUN_004308b8(&DAT_0045f220,(uint)(local_14 + -0x45f220));
    }
    else {
      local_10 = (char)local_1c;
      ungetc((int)local_10,DAT_0045f900);
      FUN_0041d17c(&DAT_0045f220,(int)(local_14 + -0x45f220));
    }
    DAT_0045ea54 = 1;
    uVar3 = 1;
  }
  return uVar3;
}


/* ==== FUN_004308b8 @ 004308b8 ==== */

void __cdecl FUN_004308b8(undefined1 *param_1,uint param_2)

{
  undefined1 *local_8;
  
  DAT_0045fb68 = param_2;
  DAT_0045fb64 = (undefined1 *)FUN_00439857(param_2);
  for (local_8 = DAT_0045fb64; local_8 < DAT_0045fb64 + DAT_0045fb68; local_8 = local_8 + 1) {
    *local_8 = *param_1;
    param_1 = param_1 + 1;
  }
  return;
}


/* ==== FUN_00430916 @ 00430916 ==== */

undefined4 __cdecl FUN_00430916(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_20c [512];
  uint *local_c;
  int *local_8;
  
  local_c = (uint *)local_20c;
  local_8 = (int *)0x0;
  if (*PTR_DAT_0044f818 == '\0') {
    DAT_0045f860 = &DAT_0045ec04;
    local_20c[0] = 0;
  }
  while( true ) {
    if (*DAT_0045f860 == '\0') {
      DAT_0045f860 = (char *)0x0;
      if (param_1 == 0x1a) {
        FUN_00413085((uint *)local_20c);
      }
      else if (param_1 == 0x38) {
        FUN_004133a9((uint *)local_20c);
      }
      else {
        FUN_004136cd((uint *)local_20c);
      }
      uVar2 = FUN_0043b007((uint)(*PTR_DAT_0044f818 != '\0'));
      return uVar2;
    }
    if (*DAT_0045f860 == ',') break;
    if (((*DAT_0045f860 == '\'') || (*DAT_0045f860 == '\"')) || (*DAT_0045f860 == '[')) {
      DAT_0045f860 = FUN_0043b08d(DAT_0045f860,(char *)local_c);
      if (DAT_0045f860 == (char *)0x0) {
        return 0;
      }
      uVar1 = strlen((char *)local_c);
      local_c = (uint *)((int)local_c + uVar1);
    }
    else {
      local_8 = FUN_00414862();
      if (local_8 == (int *)0x0) {
        return 0;
      }
      if (local_8[4] == 0x200) {
        FUN_0043c0ea(local_c,(uint *)s____15E_00457f98,*local_8,local_8[1]);
      }
      else if (local_8[5] == 3) {
        uVar2 = FUN_0040a7ea((int)local_8);
        sprintf((char *)local_c,&DAT_00457fa0,uVar2);
      }
      else {
        *(undefined1 *)local_c = 0x24;
        local_c = (uint *)((int)local_c + 1);
        sprintf((char *)local_c,s__06lX_0044e098,local_8[1]);
        uVar1 = strlen((char *)local_c);
        local_c = (uint *)((int)local_c + uVar1);
        sprintf((char *)local_c,s__06lX_0044e098,local_8[2]);
      }
      uVar1 = strlen((char *)local_c);
      local_c = (uint *)((int)local_c + uVar1);
    }
    if (local_8 != (int *)0x0) {
      FUN_004167ef(local_8);
      local_8 = (int *)0x0;
    }
    if (*DAT_0045f860 != '\0') {
      DAT_0045f860 = DAT_0045f860 + 1;
    }
  }
  FUN_00413085((uint *)s_Missing_argument_00457f84);
  return 0;
}


/* ==== FUN_00430b62 @ 00430b62 ==== */

undefined4 FUN_00430b62(void)

{
  undefined4 uVar1;
  int iVar2;
  double *local_10;
  int local_c;
  
  local_c = 4;
  FUN_0043b007(1);
  if (*PTR_DAT_0044f810 == '\0') {
    FUN_00413085((uint *)s_EQU_requires_label_00457fa4);
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_0043b659(PTR_DAT_0044f810);
    if (iVar2 == -1) {
      uVar1 = 0;
    }
    else {
      if (DAT_0045f860[1] == ':') {
        local_c = FUN_0043a807((int)*DAT_0045f860);
        if ((local_c == 0xa2c2a) || (local_c == 4)) {
          FUN_00413085((uint *)s_Invalid_memory_space_attribute_00457fb8);
          return 0;
        }
        DAT_0045f860 = DAT_0045f860 + 2;
      }
      if (local_c == 4) {
        local_10 = (double *)FUN_00414862();
      }
      else {
        local_10 = (double *)FUN_00413c50(DAT_0044f91c);
      }
      if (local_10 == (double *)0x0) {
        uVar1 = 0;
      }
      else {
        *(undefined4 *)((int)local_10 + 0x3c) = *(undefined4 *)(PTR_DAT_0044f978 + 8);
        if (((ulonglong)local_10[3] & 0x8000000) == 0) {
          if ((((ulonglong)local_10[3] & 0x1000) == 0) ||
             (*(int *)(local_10 + 8) == *(int *)(PTR_DAT_0044f97c + 8))) {
            if ((((ulonglong)local_10[3] & 0x1000) == 0) ||
               (*(int *)((int)local_10 + 0x24) == *(int *)(DAT_0045fb88 + 8))) {
              if (local_c != 4) {
                if (*(int *)((int)local_10 + 0x1c) == 4) {
                  *(int *)(local_10 + 4) = local_c;
                  *(int *)((int)local_10 + 0x1c) = local_c;
                }
                else if ((DAT_0044f7a4 != '\0') &&
                        (iVar2 = FUN_0043baf1(*(int *)((int)local_10 + 0x1c),local_c),
                        iVar2 == 0xa2c2a)) {
                  FUN_004133a9((uint *)s_Expression_involves_incompatible_00458054);
                }
              }
              *(uint *)(local_10 + 3) = *(uint *)(local_10 + 3) | 0x400;
              FUN_00437a9f((uint *)PTR_DAT_0044f810,local_10);
              if (*(int *)(local_10 + 2) == 0x100) {
                if (*(int *)((int)local_10 + 0x14) == 3) {
                  DAT_00465480 = *(undefined4 *)(local_10 + 1);
                  DAT_0045f924 = 1;
                }
                else {
                  DAT_00465480 = *(undefined4 *)((int)local_10 + 4);
                  DAT_00465484 = *(undefined4 *)(local_10 + 1);
                  DAT_0045f924 = 2;
                }
                DAT_0045f918 = 1;
              }
              else if (*(int *)(local_10 + 2) == 0x200) {
                DAT_0045f91c = 1;
                DAT_00465a80 = *(undefined4 *)local_10;
                DAT_00465a84 = *(undefined4 *)((int)local_10 + 4);
              }
              FUN_004167ef((undefined4 *)local_10);
              uVar1 = 1;
            }
            else {
              FUN_00413085((uint *)s_Relative_equate_must_share_the_s_00458028);
              FUN_004167ef((undefined4 *)local_10);
              uVar1 = 0;
            }
          }
          else {
            FUN_00413085((uint *)s_Relative_equate_must_be_in_same_s_00458000);
            FUN_004167ef((undefined4 *)local_10);
            uVar1 = 0;
          }
        }
        else {
          FUN_00413085((uint *)s_Expression_contains_forward_refe_00457fd8);
          FUN_004167ef((undefined4 *)local_10);
          uVar1 = 0;
        }
      }
    }
  }
  return uVar1;
}


/* ==== FUN_00430e0f @ 00430e0f ==== */

undefined4 __cdecl FUN_00430e0f(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  double *pdVar4;
  undefined *local_1c;
  uint *local_18;
  
  if (((*PTR_DAT_0044f810 == '\0') && (PTR_DAT_0044f81c != (undefined *)0x0)) &&
     (*PTR_DAT_0044f81c != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    local_18 = (uint *)PTR_DAT_0044f818;
  }
  else {
    local_18 = (uint *)PTR_DAT_0044f810;
  }
  FUN_0043b007(bVar1 + 1);
  if ((*PTR_DAT_0044f810 == '\0') &&
     ((PTR_DAT_0044f81c == (undefined *)0x0 || (*PTR_DAT_0044f81c == '\0')))) {
    FUN_00413085((uint *)s_SET_requires_label_00458084);
    uVar2 = 0;
  }
  else {
    iVar3 = FUN_0043b659((char *)local_18);
    if (iVar3 == -1) {
      uVar2 = 0;
    }
    else {
      if (bVar1) {
        local_1c = PTR_DAT_0044f81c;
      }
      else {
        local_1c = PTR_DAT_0044f818;
      }
      DAT_0045f860 = local_1c;
      pdVar4 = (double *)FUN_00414862();
      if (pdVar4 == (double *)0x0) {
        uVar2 = 0;
      }
      else {
        *(undefined4 *)((int)pdVar4 + 0x3c) = *(undefined4 *)(PTR_DAT_0044f978 + 8);
        if (((ulonglong)pdVar4[3] & 0x8000000) == 0) {
          if ((((ulonglong)pdVar4[3] & 0x1000) == 0) ||
             (*(int *)((int)pdVar4 + 0x3c) == *(int *)(PTR_DAT_0044f97c + 8))) {
            DAT_0045eb28 = param_1 == 0x40;
            *(uint *)(pdVar4 + 3) = *(uint *)(pdVar4 + 3) | 0x10;
            FUN_00437a9f(local_18,pdVar4);
            DAT_0045eb28 = 0;
            if (*(int *)(pdVar4 + 2) == 0x100) {
              if (*(int *)((int)pdVar4 + 0x14) == 3) {
                DAT_00465480 = *(undefined4 *)(pdVar4 + 1);
                DAT_0045f924 = 1;
              }
              else {
                DAT_00465480 = *(undefined4 *)((int)pdVar4 + 4);
                DAT_00465484 = *(undefined4 *)(pdVar4 + 1);
                DAT_0045f924 = 2;
              }
              DAT_0045f918 = 1;
            }
            else if (*(int *)(pdVar4 + 2) == 0x200) {
              DAT_0045f91c = 1;
              DAT_00465a80 = *(undefined4 *)pdVar4;
              DAT_00465a84 = *(undefined4 *)((int)pdVar4 + 4);
            }
            FUN_004167ef((undefined4 *)pdVar4);
            uVar2 = 1;
          }
          else {
            FUN_00413085((uint *)s_Relative_SET_must_be_in_same_sec_004580c0);
            FUN_004167ef((undefined4 *)pdVar4);
            uVar2 = 0;
          }
        }
        else {
          FUN_00413085((uint *)s_Expression_contains_forward_refe_00458098);
          FUN_004167ef((undefined4 *)pdVar4);
          uVar2 = 0;
        }
      }
    }
  }
  return uVar2;
}


/* ==== FUN_0043104e @ 0043104e ==== */

undefined4 FUN_0043104e(void)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  piVar2 = FUN_00413e70();
  if (piVar2 == (int *)0x0) {
    uVar3 = 0;
  }
  else if ((piVar2[6] & 0x8000000U) == 0) {
    iVar1 = piVar2[2];
    FUN_004167ef(piVar2);
    if (((iVar1 == 2) || (iVar1 == 10)) || (iVar1 == 0x10)) {
      uVar3 = 1;
      DAT_0044f7cc = iVar1;
    }
    else {
      FUN_00413085((uint *)s_Invalid_radix_expression_00458110);
      uVar3 = 0;
    }
  }
  else {
    FUN_00413085((uint *)s_Expression_contains_forward_refe_004580e8);
    FUN_004167ef(piVar2);
    uVar3 = 0;
  }
  return uVar3;
}


/* ==== FUN_004310e5 @ 004310e5 ==== */

undefined4 __cdecl FUN_004310e5(int param_1)

{
  char *src;
  int iVar1;
  undefined4 uVar2;
  undefined4 local_20c;
  char local_208;
  char local_207;
  
  if ((PTR_DAT_0044f818 == (undefined *)0x0) || (*PTR_DAT_0044f818 == '\0')) {
    FUN_00413085((uint *)s_Forcing_not_specified_0045812c);
    uVar2 = 0;
  }
  else {
    src = FUN_0043b836(PTR_DAT_0044f818);
    strcpy(&local_208,src);
    if (((local_208 == 's') && (local_207 == '\0')) ||
       ((local_208 == s_short_00458144[0] &&
        (iVar1 = strcmp(&local_208,s_short_0045814c), iVar1 == 0)))) {
      local_20c = 0x2000000;
    }
    else if (((local_208 == 'l') && (local_207 == '\0')) ||
            ((local_208 == DAT_00458154 && (iVar1 = strcmp(&local_208,&DAT_0045815c), iVar1 == 0))))
    {
      local_20c = 0x1000000;
    }
    else {
      if (((((local_208 != 'n') || (local_207 != '\0')) &&
           ((local_208 != DAT_00458164 || (iVar1 = strcmp(&local_208,&DAT_00458168), iVar1 != 0))))
          && ((local_208 != DAT_0045816c || (iVar1 = strcmp(&local_208,&DAT_00458170), iVar1 != 0)))
          ) && ((local_208 != DAT_00458174 || (iVar1 = strcmp(&local_208,&DAT_0045817c), iVar1 != 0)
                ))) {
        FUN_004131f9((uint *)s_Invalid_force_type_00458184,&local_208);
        return 0;
      }
      local_20c = 0;
    }
    if (param_1 == 0x3c) {
      DAT_0045ebac = local_20c;
    }
    else if (param_1 == 0x3d) {
      DAT_0045ebb0 = local_20c;
    }
    uVar2 = 1;
  }
  return uVar2;
}


/* ==== FUN_004312d0 @ 004312d0 ==== */

undefined4 FUN_004312d0(void)

{
  int iVar1;
  uint uVar2;
  int local_44;
  int local_40 [5];
  undefined4 local_2c;
  char local_20 [20];
  char *local_c;
  int local_8;
  
  local_8 = 0x11;
  DAT_0045f860 = PTR_DAT_0044f818;
  if ((PTR_DAT_0044f818 == (undefined *)0x0) || (*PTR_DAT_0044f818 == '\0')) {
    FUN_004314ab();
  }
  else {
    local_44 = 0;
    while ((local_44 < 4 && (*DAT_0045f860 != '\0'))) {
      if (*DAT_0045f860 == ',') {
        DAT_0045f860 = DAT_0045f860 + 1;
      }
      for (local_c = local_20;
          ((*DAT_0045f860 != '\0' && (*DAT_0045f860 != ',')) && (local_c < local_20 + 0x10));
          local_c = local_c + 1) {
        *local_c = *DAT_0045f860;
        DAT_0045f860 = DAT_0045f860 + 1;
      }
      *local_c = '\0';
      local_c = DAT_0045f860;
      DAT_0045f860 = local_20;
      iVar1 = FUN_004060d8(0,local_40,local_8,0,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_0045f860 = local_c;
      if ((*(int *)(&PTR_PTR_00456f50)[local_44] != 0) &&
         (*(undefined **)(&PTR_PTR_00456f50)[local_44] != (&PTR_DAT_00456f40)[local_44])) {
        FUN_004398b5(*(undefined **)(&PTR_PTR_00456f50)[local_44]);
      }
      uVar2 = strlen(local_20);
      iVar1 = FUN_00439857(uVar2 + 1);
      *(int *)(&PTR_PTR_00456f50)[local_44] = iVar1;
      strcpy(*(char **)(&PTR_PTR_00456f50)[local_44],local_20);
      *(undefined4 *)(&PTR_DAT_00456f60)[local_44] = local_2c;
      local_44 = local_44 + 1;
    }
    if ((DAT_0045f860 != (char *)0x0) && (*DAT_0045f860 != '\0')) {
      FUN_00413085((uint *)s_Extra_fields_ignored_00458198);
    }
  }
  return 1;
}


/* ==== FUN_004314ab @ 004314ab ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004314ab(void)

{
  if ((PTR_DAT_0044f934 != (undefined *)0x0) && (PTR_DAT_0044f934 != &DAT_0044f928)) {
    FUN_004398b5(PTR_DAT_0044f934);
  }
  PTR_DAT_0044f934 = &DAT_0044f928;
  DAT_0044f944 = 4;
  if ((PTR_DAT_0044f938 != (undefined *)0x0) && (PTR_DAT_0044f938 != &DAT_0044f92c)) {
    FUN_004398b5(PTR_DAT_0044f938);
  }
  PTR_DAT_0044f938 = &DAT_0044f92c;
  DAT_0044f948 = 2;
  if ((PTR_DAT_0044f93c != (undefined *)0x0) && (PTR_DAT_0044f93c != &DAT_0044f930)) {
    FUN_004398b5(PTR_DAT_0044f93c);
  }
  PTR_DAT_0044f93c = &DAT_0044f930;
  _DAT_0044f94c = 5;
  if ((PTR_DAT_0044f940 != (undefined *)0x0) && (PTR_DAT_0044f940 != &DAT_0045f8f8)) {
    FUN_004398b5(PTR_DAT_0044f940);
  }
  PTR_DAT_0044f940 = &DAT_0045f8f8;
  _DAT_0044f950 = 0xffffffff;
  return;
}


/* ==== FUN_0043158e @ 0043158e ==== */

undefined4 __cdecl FUN_0043158e(int *param_1)

{
  undefined4 uVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  
  if (DAT_0045f8fc < 2) {
    uVar1 = 1;
  }
  else if (*PTR_DAT_0044f818 == '\0') {
    if (*param_1 != 0) {
      FUN_004398b5((undefined *)*param_1);
      *param_1 = 0;
    }
    DAT_0045ea54 = 1;
    uVar1 = 1;
  }
  else {
    pcVar2 = FUN_0043b405(PTR_DAT_0044f818,&DAT_0045f220);
    if (pcVar2 == (char *)0x0) {
      uVar1 = 0;
    }
    else {
      FUN_0043b007(1);
      if (*param_1 != 0) {
        FUN_004398b5((undefined *)*param_1);
      }
      uVar3 = strlen(&DAT_0045f220);
      iVar4 = FUN_00439857(uVar3 + 1);
      *param_1 = iVar4;
      strcpy((char *)*param_1,&DAT_0045f220);
      DAT_0045ea54 = 1;
      uVar1 = 1;
    }
  }
  return uVar1;
}


/* ==== FUN_00431657 @ 00431657 ==== */

void FUN_00431657(void)

{
  char local_218 [521];
  char local_f [3];
  char *local_c;
  char *local_8;
  
  local_c = local_218;
  for (local_8 = PTR_DAT_0044f810; *local_8 != '\0'; local_8 = local_8 + 1) {
    *local_c = *local_8;
    local_c = local_c + 1;
  }
  *local_c = '\0';
  local_c = local_c + 1;
  *local_c = DAT_00456f70;
  local_c = local_c + 1;
  *local_c = DAT_00456f71;
  while (local_8 = local_8 + 1, local_c = local_c + 1, local_8 < &DAT_0045f019) {
    *local_c = *local_8;
  }
  local_c = &DAT_0045ee10;
  for (local_8 = local_218; local_8 < local_f; local_8 = local_8 + 1) {
    *local_c = *local_8;
    local_c = local_c + 1;
  }
  PTR_DAT_0044f818 = PTR_DAT_0044f818 + 2;
  PTR_DAT_0044f81c = PTR_DAT_0044f81c + 2;
  PTR_DAT_0044f820 = PTR_DAT_0044f820 + 2;
  PTR_DAT_0044f824 = PTR_DAT_0044f824 + 2;
  if (((DAT_0045f860 != (char *)0x0) && (*DAT_0045f860 != '\0')) &&
     (PTR_DAT_0044f814 < DAT_0045f860)) {
    DAT_0045f860 = DAT_0045f860 + 2;
  }
  if (((DAT_0045f864 != (char *)0x0) && (*DAT_0045f864 != '\0')) &&
     (PTR_DAT_0044f814 < DAT_0045f864)) {
    DAT_0045f864 = DAT_0045f864 + 2;
  }
  return;
}


