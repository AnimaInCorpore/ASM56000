/* procxy: 17 functions from ASM56000 */

/* ==== FUN_00428040 @ 00428040 ==== */

undefined4 __cdecl
FUN_00428040(int *param_1,uint param_2,int *param_3,int *param_4,int *param_5,int *param_6)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  undefined4 uVar3;
  
  DAT_0045f860 = PTR_DAT_0044f81c;
  iVar2 = FUN_00439c56((int)param_3,6);
  if (iVar2 == 0) {
    return 0;
  }
  if (param_3[1] == 4) {
    iVar2 = FUN_00405fe0(param_3);
    if (iVar2 == 0) {
      *param_1 = 2;
      return 0;
    }
    if ((2 < *param_3) && (*param_3 < 7)) {
      bVar1 = FUN_0043bccb();
      if (CONCAT31(extraout_var,bVar1) == 0) {
        return 0;
      }
      FUN_00412c72((int)param_1,param_3);
      return 1;
    }
    if (((1 < *param_3) && (*param_3 < 9)) || ((0xd < *param_3 && (*param_3 < 0x11)))) {
      FUN_00413085((uint *)s_Missing_memory_space_specifier_004568f4);
      *param_1 = 2;
      return 0;
    }
    if (*param_3 == 0xb) {
      uVar3 = FUN_0042838d(param_2,param_1,param_3,param_4,param_5,param_6);
      return uVar3;
    }
    if (*param_3 == 9) {
      uVar3 = FUN_0042859c(param_2,param_1,param_3,param_4,param_5,param_6);
      return uVar3;
    }
    switch(param_3[5]) {
    case 0:
    case 1:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
      uVar3 = FUN_004287cc(param_2,param_1,(int)param_3,param_4);
      break;
    case 2:
    case 3:
      uVar3 = FUN_004288fe(param_2,param_1,(int)param_3,param_4,param_5,param_6);
      break;
    case 4:
    case 6:
      uVar3 = FUN_00428cce(param_2,param_1,(int)param_3,param_4,param_5,param_6);
      break;
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      uVar3 = FUN_00429729(param_2,param_1,(int)param_3,param_4,param_5,param_6);
      break;
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
      uVar3 = FUN_00429b8a(param_2,param_1,(int)param_3,param_4);
      break;
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      uVar3 = FUN_00429d39(param_2,param_1,(int)param_3,param_4);
      break;
    default:
      goto switchD_00428185_default;
    }
  }
  else {
switchD_00428185_default:
    iVar2 = FUN_004060d8(1,param_3,0,1,9,0);
    if (iVar2 == 0) {
      *param_1 = (param_3[3] != 0x2000000) + 1;
      uVar3 = 0;
    }
    else {
      switch(param_3[1]) {
      case 0:
        uVar3 = FUN_0042ae87(param_2,param_1,param_3,param_4);
        break;
      case 1:
        uVar3 = FUN_0042a096(param_2,param_1,param_3,param_4,param_5,param_6);
        break;
      case 2:
        uVar3 = FUN_0042aa80(param_2,param_1,param_3,param_4);
        break;
      case 3:
        uVar3 = FUN_0042adb6(param_2,param_1,param_3,param_4);
        break;
      default:
        FUN_00412fa0((uint *)s_do_xy_memory_space_select_failur_00456914);
        uVar3 = 0;
      }
    }
  }
  return uVar3;
}


/* ==== FUN_0042838d @ 0042838d ==== */

undefined4 __cdecl
FUN_0042838d(uint param_1,undefined4 *param_2,int *param_3,int *param_4,int *param_5,int *param_6)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  
  iVar2 = FUN_0042b1e5(param_1,0x11,0);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = FUN_004060d8(2,param_4,0x12,0,0,0);
  if (iVar2 == 0) {
    return 0;
  }
  switch(param_4[5]) {
  case 2:
  case 3:
  case 4:
  case 6:
    if (*PTR_DAT_0044f820 == '\0') {
      FUN_00412baf((int)param_2,(int)param_3,(int)param_4);
    }
    else {
      DAT_0045f860 = PTR_DAT_0044f820;
      iVar2 = FUN_004060d8(1,param_5,1,0,0,0);
      if (iVar2 == 0) {
        return 0;
      }
      iVar2 = FUN_004060d8(0,param_6,2,0,0,0);
      if (iVar2 == 0) {
        return 0;
      }
      *param_3 = 9;
      DAT_0045f928 = DAT_0045f928 + 2;
      if (param_3[3] != 0) {
        FUN_004133a9((uint *)s_Cannot_force_short_immediate_wit_00456938);
      }
      FUN_00412941(param_2,param_3,(int)param_4,(int)param_5,(int)param_6);
    }
    break;
  case 5:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
    bVar1 = FUN_0043bccb();
    if (CONCAT31(extraout_var_00,bVar1) == 0) {
      return 0;
    }
    FUN_00412baf((int)param_2,(int)param_3,(int)param_4);
    break;
  default:
    FUN_00413085((uint *)s_Illegal_X_field_destination_regi_00456970);
    return 0;
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
    FUN_0042b12c(param_4[5]);
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x2a:
    iVar2 = FUN_0042b1e5(param_1,0x10,(int)param_2);
    if (iVar2 == 0) {
      return 0;
    }
    bVar1 = FUN_0043bccb();
    if (CONCAT31(extraout_var,bVar1) == 0) {
      return 0;
    }
    FUN_00411de6((int)param_2,(int)param_3,(int)param_4);
  }
  return 1;
}


/* ==== FUN_0042859c @ 0042859c ==== */

undefined4 __cdecl
FUN_0042859c(uint param_1,undefined4 *param_2,int *param_3,int *param_4,int *param_5,int *param_6)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  
  iVar2 = FUN_0042b1e5(param_1,0x11,0);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = FUN_004060d8(2,param_4,0x12,0,0,0);
  if (iVar2 == 0) {
    return 0;
  }
  DAT_0045f928 = DAT_0045f928 + 2;
  switch(param_4[5]) {
  case 2:
  case 3:
  case 4:
  case 6:
    if (*PTR_DAT_0044f820 == '\0') {
      FUN_004124fe(param_2,param_3,(int)param_4);
    }
    else {
      DAT_0045f860 = PTR_DAT_0044f820;
      iVar2 = FUN_004060d8(1,param_5,1,0,0,0);
      if (iVar2 == 0) {
        return 0;
      }
      iVar2 = FUN_004060d8(0,param_6,2,0,0,0);
      if (iVar2 == 0) {
        return 0;
      }
      FUN_00412941(param_2,param_3,(int)param_4,(int)param_5,(int)param_6);
    }
    break;
  case 5:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
    bVar1 = FUN_0043bccb();
    if (CONCAT31(extraout_var_01,bVar1) == 0) {
      return 0;
    }
    FUN_004124fe(param_2,param_3,(int)param_4);
    break;
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
    iVar2 = FUN_0042b1e5(param_1,0x10,(int)param_2);
    if (iVar2 == 0) {
      return 0;
    }
    bVar1 = FUN_0043bccb();
    if (CONCAT31(extraout_var,bVar1) == 0) {
      return 0;
    }
    FUN_004120a7(param_2,param_3,(int)param_4);
    break;
  default:
    FUN_00413085((uint *)s_Illegal_X_field_destination_regi_004569a0);
    return 0;
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
    FUN_0042b12c(param_4[5]);
  case 0x2a:
    iVar2 = FUN_0042b1e5(param_1,0x10,(int)param_2);
    if (iVar2 == 0) {
      return 0;
    }
    bVar1 = FUN_0043bccb();
    if (CONCAT31(extraout_var_00,bVar1) == 0) {
      return 0;
    }
    FUN_00411db2(param_2,param_3,(int)param_4);
  }
  return 1;
}


/* ==== FUN_004287cc @ 004287cc ==== */

undefined4 __cdecl FUN_004287cc(uint param_1,int *param_2,int param_3,int *param_4)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined4 uVar3;
  
  iVar2 = FUN_0042b1e5(param_1,1,0);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = FUN_00439c56((int)param_4,3);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = FUN_004060d8(0,param_4,0,1,9,0);
  if (iVar2 == 0) {
    *param_2 = (param_4[3] != 0x2000000) + 1;
    return 0;
  }
  switch(*param_4) {
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
    goto switchD_0042885c_caseD_2;
  case 7:
  case 8:
  case 0xe:
    break;
  default:
    FUN_00412fa0((uint *)s_p_xyabba_failure_004569d0);
    return 0;
  case 0x10:
    bVar1 = FUN_0043bccb();
    if (CONCAT31(extraout_var_00,bVar1) == 0) {
      return 0;
    }
    FUN_0041297d((int)param_2,param_3,(int)param_4);
    goto LAB_004288d2;
  }
  DAT_0045f928 = DAT_0045f928 + 2;
switchD_0042885c_caseD_2:
  bVar1 = FUN_0043bccb();
  if (CONCAT31(extraout_var,bVar1) == 0) {
    *param_2 = 2;
    uVar3 = 0;
  }
  else {
    FUN_00412ac3(param_2,param_3,param_4);
LAB_004288d2:
    uVar3 = 1;
  }
  return uVar3;
}


/* ==== FUN_004288fe @ 004288fe ==== */

undefined4 __cdecl
FUN_004288fe(uint param_1,int *param_2,int param_3,int *param_4,int *param_5,int *param_6)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined4 uVar3;
  
  iVar2 = FUN_00439c56((int)param_4,6);
  if (iVar2 == 0) {
    return 0;
  }
  if (param_4[1] != 4) {
    uVar3 = FUN_00428e50(param_1,param_2,param_3,param_4,param_5,param_6);
    return uVar3;
  }
  iVar2 = FUN_0042b1e5(param_1,0x11,0);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = FUN_004060d8(2,param_4,0x12,0,0,0);
  if (iVar2 != 0) {
    switch(param_4[5]) {
    case 2:
    case 3:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      bVar1 = FUN_0043bccb();
      if (CONCAT31(extraout_var_00,bVar1) == 0) {
        return 0;
      }
      FUN_00412c09((int)param_2,param_3,(int)param_4);
      break;
    case 4:
    case 6:
      if (*PTR_DAT_0044f820 == '\0') {
        FUN_00412c09((int)param_2,param_3,(int)param_4);
      }
      else {
        DAT_0045f860 = PTR_DAT_0044f820;
        iVar2 = FUN_00439c56((int)param_5,8);
        if (iVar2 == 0) {
          return 0;
        }
        if (param_5[1] == 4) {
          iVar2 = FUN_0042b1e5(param_1,1,0);
          if (iVar2 == 0) {
            return 0;
          }
          iVar2 = FUN_004060d8(1,param_5,4,0,0,1);
          if (iVar2 == 0) {
            *param_2 = 2;
            return 0;
          }
          if (*param_5 == 9) {
            DAT_0045f928 = DAT_0045f928 + 2;
            iVar2 = FUN_004060d8(2,param_6,4,0,0,0);
            if (iVar2 == 0) {
              return 0;
            }
            FUN_004127e6(param_2,param_3,(int)param_4,param_5,(int)param_6);
          }
          else {
            iVar2 = FUN_00439c56((int)param_6,2);
            if (iVar2 == 0) {
              return 0;
            }
            iVar2 = FUN_004060d8(0,param_6,0,1,1,0);
            if (iVar2 == 0) {
              *param_2 = 2;
              return 0;
            }
            iVar2 = *param_6;
            if ((6 < iVar2) && ((iVar2 < 9 || (iVar2 == 0xe)))) {
              DAT_0045f928 = DAT_0045f928 + 2;
            }
            FUN_004126b2(param_2,param_3,(int)param_4,(int)param_5,param_6);
          }
        }
        else {
          iVar2 = FUN_0042b1e5(param_1,1,0);
          if (iVar2 == 0) {
            return 0;
          }
          iVar2 = FUN_004060d8(1,param_5,0,1,1,0);
          if (iVar2 == 0) {
            *param_2 = 2;
            return 0;
          }
          iVar2 = *param_5;
          if ((6 < iVar2) && ((iVar2 < 9 || (iVar2 == 0xe)))) {
            DAT_0045f928 = DAT_0045f928 + 2;
          }
          iVar2 = FUN_004060d8(2,param_6,4,0,0,0);
          if (iVar2 == 0) {
            return 0;
          }
          FUN_004127e6(param_2,param_3,(int)param_4,param_5,(int)param_6);
        }
      }
      break;
    default:
      FUN_00413085((uint *)s_Illegal_X_field_destination_regi_004569e4);
      return 0;
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      FUN_0042b12c(param_4[5]);
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x2a:
      iVar2 = FUN_0042b1e5(param_1,0x10,(int)param_2);
      if (iVar2 == 0) {
        return 0;
      }
      bVar1 = FUN_0043bccb();
      if (CONCAT31(extraout_var,bVar1) == 0) {
        return 0;
      }
      FUN_00411edd((int)param_2,param_3,(int)param_4);
    }
    return 1;
  }
  return 0;
}


/* ==== FUN_00428cce @ 00428cce ==== */

undefined4 __cdecl
FUN_00428cce(uint param_1,int *param_2,int param_3,int *param_4,int *param_5,int *param_6)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined4 uVar3;
  
  iVar2 = FUN_00439c56((int)param_4,9);
  if (iVar2 == 0) {
    return 0;
  }
  if (param_4[1] != 4) {
    uVar3 = FUN_00428e50(param_1,param_2,param_3,param_4,param_5,param_6);
    return uVar3;
  }
  iVar2 = FUN_0042b1e5(param_1,0x11,0);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = FUN_004060d8(2,param_4,0x12,0,0,0);
  if (iVar2 == 0) {
    return 0;
  }
  switch(param_4[5]) {
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
    bVar1 = FUN_0043bccb();
    if (CONCAT31(extraout_var_00,bVar1) == 0) {
      return 0;
    }
    FUN_00412c09((int)param_2,param_3,(int)param_4);
    goto LAB_00428de2;
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x2a:
    break;
  default:
    FUN_00413085((uint *)s_Illegal_X_field_destination_regi_00456a14);
    return 0;
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
    FUN_0042b12c(param_4[5]);
  }
  iVar2 = FUN_0042b1e5(param_1,0x10,(int)param_2);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    bVar1 = FUN_0043bccb();
    if (CONCAT31(extraout_var,bVar1) == 0) {
      uVar3 = 0;
    }
    else {
      FUN_00411edd((int)param_2,param_3,(int)param_4);
LAB_00428de2:
      uVar3 = 1;
    }
  }
  return uVar3;
}


/* ==== FUN_00428e50 @ 00428e50 ==== */

undefined4 __cdecl
FUN_00428e50(uint param_1,int *param_2,int param_3,int *param_4,int *param_5,int *param_6)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined4 uVar3;
  int local_10;
  
  if (param_4[1] == 1) {
    iVar2 = FUN_0042b1e5(param_1,0x11,0);
    if (iVar2 == 0) {
      return 0;
    }
    iVar2 = FUN_004060d8(0,param_4,0,1,9,0);
    if (iVar2 == 0) {
      *param_2 = (param_4[3] != 0x2000000) + 1;
      return 0;
    }
    switch(*param_4) {
    case 2:
    case 3:
    case 4:
    case 5:
      if (*PTR_DAT_0044f820 == '\0') {
        FUN_00412424(param_2,param_3,param_4);
      }
      else {
        iVar2 = FUN_0042b1e5(param_1,1,0);
        if (iVar2 == 0) {
          return 0;
        }
        DAT_0045f860 = PTR_DAT_0044f820;
        iVar2 = FUN_00439c56((int)param_5,8);
        if (iVar2 == 0) {
          return 0;
        }
        if (param_5[1] == 4) {
          iVar2 = FUN_004060d8(1,param_5,(-(uint)(DAT_0044f9fc == 0) & 0xffffffed) + 0x17,0,0,0);
          if (iVar2 == 0) {
            return 0;
          }
          switch(param_5[5]) {
          case 2:
          case 3:
            iVar2 = FUN_00439c56((int)param_6,8);
            if (iVar2 == 0) {
              return 0;
            }
            if (param_6[1] == 4) {
              iVar2 = FUN_004060d8(0,param_6,2,0,0,0);
              if (iVar2 == 0) {
                return 0;
              }
              FUN_00412822(param_2,param_3,param_4,(int)param_5,(int)param_6);
            }
            else {
              iVar2 = FUN_004060d8(0,param_6,0,2,0,0);
              if (iVar2 == 0) {
                return 0;
              }
              iVar2 = FUN_0042b08d(param_4[5],param_6[5]);
              if (iVar2 != 0) {
                return 0;
              }
              FUN_004120db((int)param_2,param_3,param_4,(int)param_5,param_6);
            }
            break;
          case 4:
            if ((*(int *)(param_3 + 0x14) != 2) && (*(int *)(param_3 + 0x14) != 3)) {
              FUN_00413085((uint *)s_Invalid_addressing_mode_00456a44);
              return 0;
            }
            iVar2 = FUN_004060d8(2,param_6,(*(int *)(param_3 + 0x14) != 2) + 0xd,0,0,0);
            if (iVar2 == 0) {
              return 0;
            }
            FUN_00412370((int)param_2,param_3,param_4);
            break;
          case 5:
          case 7:
            iVar2 = FUN_00439c56((int)param_6,2);
            if (iVar2 == 0) {
              return 0;
            }
            iVar2 = FUN_004060d8(0,param_6,0,2,0,0);
            if (iVar2 == 0) {
              return 0;
            }
            iVar2 = FUN_0042b08d(param_4[5],param_6[5]);
            if (iVar2 != 0) {
              return 0;
            }
            FUN_004120db((int)param_2,param_3,param_4,(int)param_5,param_6);
          }
        }
        else {
          iVar2 = FUN_004060d8(1,param_5,0,2,0,0);
          if (iVar2 == 0) {
            return 0;
          }
          iVar2 = FUN_0042b08d(param_4[5],param_5[5]);
          if (iVar2 != 0) {
            return 0;
          }
          iVar2 = FUN_004060d8(2,param_6,4,0,0,0);
          if (iVar2 == 0) {
            return 0;
          }
          FUN_004122e0((int)param_2,param_3,param_4,param_5,(int)param_6);
        }
      }
      break;
    case 7:
    case 8:
      DAT_0045f928 = DAT_0045f928 + 2;
    case 6:
      if (*PTR_DAT_0044f820 == '\0') {
        FUN_00412424(param_2,param_3,param_4);
      }
      else {
        iVar2 = FUN_0042b1e5(param_1,1,0);
        if (iVar2 == 0) {
          return 0;
        }
        DAT_0045f860 = PTR_DAT_0044f820;
        iVar2 = FUN_004060d8(1,param_5,(-(uint)(DAT_0044f9fc == 0) & 0xffffffeb) + 0x16,0,0,0);
        if (iVar2 == 0) {
          return 0;
        }
        if (param_5[5] == 4) {
          local_10 = (*(int *)(param_3 + 0x14) != 2) + 0xd;
        }
        else {
          local_10 = 2;
        }
        iVar2 = FUN_004060d8(0,param_6,local_10,0,0,0);
        if (iVar2 == 0) {
          return 0;
        }
        if (param_5[5] == 4) {
          if ((*(int *)(param_3 + 0x14) != 2) && (*(int *)(param_3 + 0x14) != 3)) {
            FUN_00413085((uint *)s_Invalid_addressing_mode_00456a5c);
            return 0;
          }
          FUN_00412370((int)param_2,param_3,param_4);
        }
        else {
          FUN_00412822(param_2,param_3,param_4,(int)param_5,(int)param_6);
        }
      }
      break;
    default:
      FUN_00412fa0((uint *)s_xdst_mem_failure_00456ab0);
      break;
    case 0xe:
      DAT_0045f928 = DAT_0045f928 + 2;
      if (*PTR_DAT_0044f820 == '\0') {
        FUN_00412424(param_2,param_3,param_4);
      }
      else {
        iVar2 = FUN_0042b1e5(param_1,1,0);
        if (iVar2 == 0) {
          return 0;
        }
        DAT_0045f860 = PTR_DAT_0044f820;
        iVar2 = FUN_004060d8(1,param_5,1,0,0,0);
        if (iVar2 == 0) {
          return 0;
        }
        iVar2 = FUN_004060d8(0,param_6,2,0,0,0);
        if (iVar2 == 0) {
          return 0;
        }
        FUN_00412822(param_2,param_3,param_4,(int)param_5,(int)param_6);
      }
      break;
    case 0x10:
      if (*PTR_DAT_0044f820 == '\0') {
        FUN_0041259a((int)param_2,param_3,(int)param_4);
      }
      else {
        *param_4 = 0xe;
        DAT_0045f928 = DAT_0045f928 + 2;
        if (param_4[3] != 0) {
          FUN_004133a9((uint *)s_Short_absolute_address_cannot_be_00456a74);
        }
        iVar2 = FUN_0042b1e5(param_1,1,0);
        if (iVar2 == 0) {
          return 0;
        }
        DAT_0045f860 = PTR_DAT_0044f820;
        iVar2 = FUN_004060d8(1,param_5,1,0,0,0);
        if (iVar2 == 0) {
          return 0;
        }
        iVar2 = FUN_004060d8(0,param_6,2,0,0,0);
        if (iVar2 == 0) {
          return 0;
        }
        FUN_00412822(param_2,param_3,param_4,(int)param_5,(int)param_6);
      }
    }
  }
  else if (param_4[1] == 2) {
    iVar2 = FUN_0042b1e5(param_1,0x11,0);
    if (iVar2 == 0) {
      return 0;
    }
    iVar2 = FUN_004060d8(0,param_4,0,1,9,0);
    if (iVar2 == 0) {
      *param_2 = (param_4[3] != 0x2000000) + 1;
      return 0;
    }
    bVar1 = FUN_0043bccb();
    if (CONCAT31(extraout_var,bVar1) == 0) {
      *param_2 = 2;
      return 0;
    }
    PTR_DAT_0044f820 = PTR_DAT_0044f81c;
    PTR_DAT_0044f81c = &DAT_0045ec04;
    if (*param_4 == 0x10) {
      FUN_0041264a((int)param_2,param_3,(int)param_4);
    }
    else {
      iVar2 = *param_4;
      if ((6 < iVar2) && ((iVar2 < 9 || (iVar2 == 0xe)))) {
        DAT_0045f928 = DAT_0045f928 + 2;
      }
      FUN_00412532(param_2,param_3,param_4);
    }
  }
  else {
    if (param_4[1] != 3) {
      if (param_4[1] == 0) {
        uVar3 = FUN_00429fb4(param_1,param_2,param_3,param_4);
        return uVar3;
      }
      FUN_00413085((uint *)s_Illegal_X_field_destination_spec_00456ac4);
      return 0;
    }
    iVar2 = FUN_0042b1e5(param_1,1,0);
    if (iVar2 == 0) {
      return 0;
    }
    iVar2 = FUN_004060d8(0,param_4,0,1,9,0);
    if (iVar2 == 0) {
      *param_2 = (param_4[3] != 0x2000000) + 1;
      return 0;
    }
    switch(*param_4) {
    case 7:
    case 8:
    case 0xe:
      DAT_0045f928 = DAT_0045f928 + 2;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      bVar1 = FUN_0043bccb();
      if (CONCAT31(extraout_var_00,bVar1) == 0) {
        *param_2 = 2;
        return 0;
      }
      FUN_00412ac3(param_2,param_3,param_4);
      break;
    case 0x10:
      bVar1 = FUN_0043bccb();
      if (CONCAT31(extraout_var_01,bVar1) == 0) {
        return 0;
      }
      FUN_0041297d((int)param_2,param_3,(int)param_4);
    }
  }
  return 1;
}


/* ==== FUN_00429729 @ 00429729 ==== */

undefined4 __cdecl
FUN_00429729(uint param_1,int *param_2,int param_3,int *param_4,int *param_5,int *param_6)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined4 uVar3;
  
  iVar2 = FUN_00439c56((int)param_4,9);
  if (iVar2 == 0) {
    return 0;
  }
  if (param_4[1] == 4) {
    iVar2 = FUN_0042b1e5(param_1,0x11,0);
    if (iVar2 == 0) {
      return 0;
    }
    iVar2 = FUN_004060d8(2,param_4,0x12,0,0,0);
    if (iVar2 == 0) {
      return 0;
    }
    switch(param_4[5]) {
    case 2:
    case 3:
      if (*PTR_DAT_0044f820 == '\0') {
        FUN_00412c09((int)param_2,param_3,(int)param_4);
      }
      else {
        iVar2 = FUN_0042b1e5(param_1,1,0);
        if (iVar2 == 0) {
          return 0;
        }
        if ((DAT_0044f9fc == 0) || (*(int *)(param_3 + 0x14) != 5)) {
          FUN_00413085((uint *)s_Invalid_addressing_mode_00456aec);
          return 0;
        }
        DAT_0045f860 = PTR_DAT_0044f820;
        iVar2 = FUN_004060d8(1,param_5,(param_4[5] != 2) + 0xd,0,0,0);
        if (iVar2 == 0) {
          return 0;
        }
        iVar2 = FUN_00439c56((int)param_6,2);
        if (iVar2 == 0) {
          return 0;
        }
        iVar2 = FUN_004060d8(0,param_6,0,1,0,0);
        if (iVar2 == 0) {
          return 0;
        }
        FUN_00412370((int)param_2,(int)param_5,param_6);
      }
      break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      bVar1 = FUN_0043bccb();
      if (CONCAT31(extraout_var_00,bVar1) == 0) {
        return 0;
      }
      FUN_00412c09((int)param_2,param_3,(int)param_4);
      break;
    default:
      FUN_00413085((uint *)s_Illegal_X_field_destination_regi_00456b04);
      return 0;
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      FUN_0042b12c(param_4[5]);
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x2a:
      iVar2 = FUN_0042b1e5(param_1,0x10,(int)param_2);
      if (iVar2 == 0) {
        return 0;
      }
      bVar1 = FUN_0043bccb();
      if (CONCAT31(extraout_var,bVar1) == 0) {
        return 0;
      }
      FUN_00411edd((int)param_2,param_3,(int)param_4);
    }
  }
  else if (param_4[1] == 1) {
    iVar2 = FUN_0042b1e5(param_1,0x11,0);
    if (iVar2 == 0) {
      return 0;
    }
    iVar2 = FUN_004060d8(0,param_4,0,1,9,0);
    if (iVar2 == 0) {
      *param_2 = (param_4[3] != 0x2000000) + 1;
      return 0;
    }
    bVar1 = FUN_0043bccb();
    if (CONCAT31(extraout_var_01,bVar1) == 0) {
      *param_2 = 2;
      return 0;
    }
    if (*param_4 == 0x10) {
      FUN_0041259a((int)param_2,param_3,(int)param_4);
    }
    else {
      iVar2 = *param_4;
      if ((6 < iVar2) && ((iVar2 < 9 || (iVar2 == 0xe)))) {
        DAT_0045f928 = DAT_0045f928 + 2;
      }
      FUN_00412424(param_2,param_3,param_4);
    }
  }
  else {
    if (param_4[1] != 2) {
      if (param_4[1] == 0) {
        uVar3 = FUN_00429fb4(param_1,param_2,param_3,param_4);
        return uVar3;
      }
      FUN_00413085((uint *)s_Illegal_X_field_destination_spec_00456b34);
      return 0;
    }
    iVar2 = FUN_0042b1e5(param_1,0x11,0);
    if (iVar2 == 0) {
      return 0;
    }
    iVar2 = FUN_004060d8(0,param_4,0,1,9,0);
    if (iVar2 == 0) {
      *param_2 = (param_4[3] != 0x2000000) + 1;
      return 0;
    }
    bVar1 = FUN_0043bccb();
    if (CONCAT31(extraout_var_02,bVar1) == 0) {
      *param_2 = 2;
      return 0;
    }
    PTR_DAT_0044f820 = PTR_DAT_0044f81c;
    PTR_DAT_0044f81c = &DAT_0045ec04;
    if (*param_4 == 0x10) {
      FUN_0041264a((int)param_2,param_3,(int)param_4);
    }
    else {
      iVar2 = *param_4;
      if ((6 < iVar2) && ((iVar2 < 9 || (iVar2 == 0xe)))) {
        DAT_0045f928 = DAT_0045f928 + 2;
      }
      FUN_00412532(param_2,param_3,param_4);
    }
  }
  return 1;
}


/* ==== FUN_00429b8a @ 00429b8a ==== */

undefined4 __cdecl FUN_00429b8a(uint param_1,int *param_2,int param_3,int *param_4)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined4 uVar2;
  int iVar3;
  
  bVar1 = FUN_0043bccb();
  if (CONCAT31(extraout_var,bVar1) == 0) {
    uVar2 = 0;
  }
  else {
    iVar3 = FUN_00439c56((int)param_4,9);
    if (iVar3 == 0) {
      uVar2 = 0;
    }
    else {
      if (param_4[1] == 4) {
        iVar3 = FUN_0042b1e5(param_1,0x10,(int)param_2);
        if (iVar3 == 0) {
          return 0;
        }
        iVar3 = FUN_004060d8(2,param_4,0x12,0,0,0);
        if (iVar3 == 0) {
          return 0;
        }
        FUN_00411e5a((int)param_2,param_3,(int)param_4);
      }
      else {
        if ((param_4[1] != 1) && (param_4[1] != 2)) {
          if (param_4[1] == 0) {
            uVar2 = FUN_00429fb4(param_1,param_2,param_3,param_4);
            return uVar2;
          }
          FUN_00413085((uint *)s_Illegal_X_field_destination_spec_00456b5c);
          return 0;
        }
        iVar3 = FUN_0042b1e5(param_1,0x10,(int)param_2);
        if (iVar3 == 0) {
          return 0;
        }
        iVar3 = FUN_004060d8(0,param_4,0,1,9,0);
        if (iVar3 == 0) {
          *param_2 = (param_4[3] != 0x2000000) + 1;
          return 0;
        }
        if (*param_4 == 0x10) {
          FUN_00411f11((int)param_2,param_3,(int)param_4);
        }
        else {
          iVar3 = *param_4;
          if ((6 < iVar3) && ((iVar3 < 9 || (iVar3 == 0xe)))) {
            DAT_0045f928 = DAT_0045f928 + 2;
          }
          FUN_00411fc7(param_2,param_3,param_4);
        }
        if (param_4[1] == 2) {
          PTR_DAT_0044f820 = PTR_DAT_0044f81c;
          PTR_DAT_0044f81c = &DAT_0045ec04;
        }
      }
      uVar2 = 1;
    }
  }
  return uVar2;
}


/* ==== FUN_00429d39 @ 00429d39 ==== */

undefined4 __cdecl FUN_00429d39(uint param_1,int *param_2,int param_3,int *param_4)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined4 uVar2;
  int iVar3;
  int local_8;
  
  local_8 = 0;
  if (*(int *)(param_3 + 0x14) == 0x2e) {
    DAT_0045ebb4 = DAT_0045ebb4 | 0x24c;
    local_8 = FUN_0041b685(2);
  }
  if ((local_8 == 0) && (*(int *)(param_3 + 0x14) == 0x2c)) {
    FUN_0041b685(1);
  }
  if (((*(int *)(param_3 + 0x14) == 0x2e) || (*(int *)(param_3 + 0x14) == 0x2f)) &&
     ((DAT_0045ebb8 & 0x10) != 0)) {
    if (((DAT_0045eac8 == '\0') || (DAT_0045ea70 != '\0')) || (DAT_0045eb98 != 0)) {
      FUN_00413085((uint *)s_Move_from_SSH_or_SSL_cannot_foll_00456b84);
    }
    else {
      FUN_0041bbb2();
    }
  }
  bVar1 = FUN_0043bccb();
  if (CONCAT31(extraout_var,bVar1) == 0) {
    uVar2 = 0;
  }
  else {
    iVar3 = FUN_00439c56((int)param_4,9);
    if (iVar3 == 0) {
      uVar2 = 0;
    }
    else {
      if (param_4[1] == 4) {
        iVar3 = FUN_0042b1e5(param_1,0x10,(int)param_2);
        if (iVar3 == 0) {
          return 0;
        }
        iVar3 = FUN_004060d8(2,param_4,0x12,0,0,0);
        if (iVar3 == 0) {
          return 0;
        }
        if ((*(int *)(param_3 + 0x14) == 0x2e) && (param_4[5] == 0x2e)) {
          FUN_00413085((uint *)s_SSH_cannot_be_both_source_and_de_00456bb4);
          return 0;
        }
        FUN_00411e5a((int)param_2,param_3,(int)param_4);
      }
      else if ((param_4[1] == 1) || (param_4[1] == 2)) {
        iVar3 = FUN_0042b1e5(param_1,0x10,(int)param_2);
        if (iVar3 == 0) {
          return 0;
        }
        iVar3 = FUN_004060d8(0,param_4,0,1,9,0);
        if (iVar3 == 0) {
          *param_2 = (param_4[3] != 0x2000000) + 1;
          return 0;
        }
        if (*param_4 == 0x10) {
          FUN_00411f11((int)param_2,param_3,(int)param_4);
        }
        else {
          iVar3 = *param_4;
          if ((6 < iVar3) && ((iVar3 < 9 || (iVar3 == 0xe)))) {
            DAT_0045f928 = DAT_0045f928 + 2;
          }
          FUN_00411cd2(param_2,param_3,param_4);
        }
        if (param_4[1] == 2) {
          PTR_DAT_0044f820 = PTR_DAT_0044f81c;
          PTR_DAT_0044f81c = &DAT_0045ec04;
        }
      }
      else {
        if (param_4[1] != 0) {
          FUN_00413085((uint *)s_Illegal_X_field_destination_spec_00456be8);
          return 0;
        }
        iVar3 = FUN_00429fb4(param_1,param_2,param_3,param_4);
        if (iVar3 == 0) {
          return 0;
        }
      }
      uVar2 = 1;
    }
  }
  return uVar2;
}


/* ==== FUN_00429fb4 @ 00429fb4 ==== */

undefined4 __cdecl FUN_00429fb4(uint param_1,int *param_2,int param_3,int *param_4)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  undefined4 uVar4;
  undefined3 extraout_var;
  
  iVar3 = FUN_0042b1e5(param_1,0x20,(int)param_2);
  if (iVar3 == 0) {
    uVar4 = 0;
  }
  else {
    iVar3 = FUN_004060d8(0,param_4,0,1,9,0);
    if (iVar3 == 0) {
      *param_2 = (param_4[3] != 0x2000000) + 1;
      uVar4 = 0;
    }
    else {
      bVar2 = FUN_0043bccb();
      if (CONCAT31(extraout_var,bVar2) == 0) {
        *param_2 = 2;
        uVar4 = 0;
      }
      else {
        iVar3 = DAT_0045f928 + 4;
        if (*param_4 == 0x10) {
          DAT_0045f928 = iVar3;
          FUN_00412dd4((int)param_2,param_3,(int)param_4);
        }
        else {
          iVar1 = *param_4;
          if ((6 < iVar1) && ((iVar1 < 9 || (iVar1 == 0xe)))) {
            iVar3 = DAT_0045f928 + 6;
          }
          DAT_0045f928 = iVar3;
          FUN_00412ce3(param_2,param_3,param_4);
        }
        uVar4 = 1;
      }
    }
  }
  return uVar4;
}


/* ==== FUN_0042a096 @ 0042a096 ==== */

undefined4 __cdecl
FUN_0042a096(uint param_1,undefined4 *param_2,int *param_3,int *param_4,int *param_5,int *param_6)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  int iVar2;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  
  switch(*param_3) {
  case 2:
  case 3:
  case 4:
  case 5:
    iVar2 = FUN_00439c56((int)param_4,0);
    if (iVar2 == 0) {
      return 0;
    }
    if (param_4[1] == 4) {
      iVar2 = FUN_004060d8(2,param_4,0x12,0,0,0);
      if (iVar2 == 0) {
        return 0;
      }
      switch(param_4[5]) {
      case 2:
      case 3:
      case 4:
      case 6:
        iVar2 = FUN_0042a7d2(param_1,param_2,param_3,(int)param_4,param_5,param_6);
        if (iVar2 == 0) {
          return 0;
        }
        break;
      case 0xe:
      case 0xf:
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x13:
      case 0x14:
      case 0x15:
        if ((*param_3 != 2) && (param_3[5] == param_4[5])) {
          FUN_004133a9((uint *)s_Post_update_operation_will_not_o_00456c10);
        }
      case 5:
      case 7:
      case 8:
      case 9:
      case 10:
      case 0xb:
      case 0xc:
      case 0xd:
      case 0x16:
      case 0x17:
      case 0x18:
      case 0x19:
      case 0x1a:
      case 0x1b:
      case 0x1c:
      case 0x1d:
        iVar2 = FUN_0042b1e5(param_1,0x11,0);
        if (iVar2 == 0) {
          return 0;
        }
        bVar1 = FUN_0043bccb();
        if (CONCAT31(extraout_var_01,bVar1) == 0) {
          return 0;
        }
        FUN_004124fe(param_2,param_3,(int)param_4);
        break;
      case 0x1e:
      case 0x1f:
      case 0x20:
      case 0x21:
      case 0x22:
      case 0x23:
      case 0x24:
      case 0x25:
        iVar2 = FUN_0042b1e5(param_1,0x10,(int)param_2);
        if (iVar2 == 0) {
          return 0;
        }
        bVar1 = FUN_0043bccb();
        if (CONCAT31(extraout_var,bVar1) == 0) {
          return 0;
        }
        FUN_004120a7(param_2,param_3,(int)param_4);
        break;
      default:
        FUN_00413085((uint *)s_Illegal_X_field_destination_regi_00456c50);
        return 0;
      case 0x2b:
      case 0x2c:
      case 0x2d:
      case 0x2e:
      case 0x2f:
      case 0x30:
        FUN_0042b12c(param_4[5]);
      case 0x2a:
        iVar2 = FUN_0042b1e5(param_1,0x10,(int)param_2);
        if (iVar2 == 0) {
          return 0;
        }
        bVar1 = FUN_0043bccb();
        if (CONCAT31(extraout_var_00,bVar1) == 0) {
          return 0;
        }
        FUN_00411db2(param_2,param_3,(int)param_4);
      }
    }
    break;
  case 7:
  case 8:
  case 0xe:
    DAT_0045f928 = DAT_0045f928 + 2;
  case 6:
    iVar2 = FUN_004060d8(2,param_4,0x12,0,0,0);
    if (iVar2 == 0) {
      return 0;
    }
    switch(param_4[5]) {
    case 2:
    case 3:
    case 4:
    case 6:
      if (*PTR_DAT_0044f820 == '\0') {
        iVar2 = FUN_0042b1e5(param_1,0x11,0);
        if (iVar2 == 0) {
          return 0;
        }
        FUN_004124fe(param_2,param_3,(int)param_4);
      }
      else {
        iVar2 = FUN_0042b1e5(param_1,1,0);
        if (iVar2 == 0) {
          return 0;
        }
        DAT_0045f860 = PTR_DAT_0044f820;
        iVar2 = FUN_004060d8(1,param_5,1,0,0,0);
        if (iVar2 == 0) {
          return 0;
        }
        iVar2 = FUN_004060d8(0,param_6,2,0,0,0);
        if (iVar2 == 0) {
          return 0;
        }
        FUN_00412941(param_2,param_3,(int)param_4,(int)param_5,(int)param_6);
      }
      break;
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
      if ((*param_3 == 6) && (param_3[5] == param_4[5])) {
        FUN_004133a9((uint *)s_Post_update_operation_will_not_o_00456c80);
      }
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      iVar2 = FUN_0042b1e5(param_1,0x11,0);
      if (iVar2 == 0) {
        return 0;
      }
      bVar1 = FUN_0043bccb();
      if (CONCAT31(extraout_var_04,bVar1) == 0) {
        return 0;
      }
      FUN_004124fe(param_2,param_3,(int)param_4);
      break;
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
      iVar2 = FUN_0042b1e5(param_1,0x10,(int)param_2);
      if (iVar2 == 0) {
        return 0;
      }
      bVar1 = FUN_0043bccb();
      if (CONCAT31(extraout_var_02,bVar1) == 0) {
        return 0;
      }
      FUN_004120a7(param_2,param_3,(int)param_4);
      break;
    default:
      FUN_00413085((uint *)s_Illegal_X_field_destination_regi_00456cc0);
      return 0;
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      FUN_0042b12c(param_4[5]);
    case 0x2a:
      iVar2 = FUN_0042b1e5(param_1,0x10,(int)param_2);
      if (iVar2 == 0) {
        return 0;
      }
      bVar1 = FUN_0043bccb();
      if (CONCAT31(extraout_var_03,bVar1) == 0) {
        return 0;
      }
      FUN_00411db2(param_2,param_3,(int)param_4);
    }
    break;
  case 0x10:
    iVar2 = FUN_004060d8(2,param_4,0x12,0,0,0);
    if (iVar2 == 0) {
      return 0;
    }
    switch(param_4[5]) {
    case 2:
    case 3:
    case 4:
    case 6:
      if (*PTR_DAT_0044f820 == '\0') {
        iVar2 = FUN_0042b1e5(param_1,0x11,0);
        if (iVar2 == 0) {
          return 0;
        }
        FUN_00412616((int)param_2,(int)param_3,(int)param_4);
      }
      else {
        iVar2 = FUN_0042b1e5(param_1,1,0);
        if (iVar2 == 0) {
          return 0;
        }
        DAT_0045f860 = PTR_DAT_0044f820;
        iVar2 = FUN_004060d8(1,param_5,1,0,0,0);
        if (iVar2 == 0) {
          return 0;
        }
        iVar2 = FUN_004060d8(0,param_6,2,0,0,0);
        if (iVar2 == 0) {
          return 0;
        }
        if (param_3[3] != 0) {
          FUN_004133a9((uint *)s_Short_absolute_address_cannot_be_00456cf0);
        }
        *param_3 = 0xe;
        DAT_0045f928 = DAT_0045f928 + 2;
        FUN_00412941(param_2,param_3,(int)param_4,(int)param_5,(int)param_6);
      }
      break;
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      iVar2 = FUN_0042b1e5(param_1,0x11,0);
      if (iVar2 == 0) {
        return 0;
      }
      bVar1 = FUN_0043bccb();
      if (CONCAT31(extraout_var_06,bVar1) == 0) {
        return 0;
      }
      FUN_00412616((int)param_2,(int)param_3,(int)param_4);
      break;
    default:
      FUN_00413085((uint *)s_Illegal_X_field_destination_regi_00456d2c);
      return 0;
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      FUN_0042b12c(param_4[5]);
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x2a:
      iVar2 = FUN_0042b1e5(param_1,0x10,(int)param_2);
      if (iVar2 == 0) {
        return 0;
      }
      bVar1 = FUN_0043bccb();
      if (CONCAT31(extraout_var_05,bVar1) == 0) {
        return 0;
      }
      FUN_00411f93((int)param_2,(int)param_3,(int)param_4);
    }
  }
  return 1;
}


/* ==== FUN_0042a7d2 @ 0042a7d2 ==== */

undefined4 __cdecl
FUN_0042a7d2(uint param_1,undefined4 *param_2,int *param_3,int param_4,int *param_5,int *param_6)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*PTR_DAT_0044f820 == '\0') {
    iVar1 = FUN_0042b1e5(param_1,0x11,0);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      FUN_004124fe(param_2,param_3,param_4);
      uVar2 = 1;
    }
  }
  else {
    iVar1 = FUN_0042b1e5(param_1,1,0);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      DAT_0045f860 = PTR_DAT_0044f820;
      iVar1 = FUN_00439c56((int)param_5,8);
      if (iVar1 == 0) {
        uVar2 = 0;
      }
      else {
        if (param_5[1] == 4) {
          iVar1 = FUN_004060d8(1,param_5,4,0,0,0);
          if (iVar1 == 0) {
            return 0;
          }
          switch(param_5[5]) {
          case 2:
          case 3:
            iVar1 = FUN_00439c56((int)param_6,8);
            if (iVar1 == 0) {
              return 0;
            }
            if (param_6[1] == 4) {
              iVar1 = FUN_004060d8(0,param_6,2,0,0,0);
              if (iVar1 == 0) {
                return 0;
              }
              FUN_00412941(param_2,param_3,param_4,(int)param_5,(int)param_6);
            }
            else {
              iVar1 = FUN_004060d8(0,param_6,0,2,0,0);
              if (iVar1 == 0) {
                return 0;
              }
              iVar1 = FUN_0042b08d(param_3[5],param_6[5]);
              if (iVar1 != 0) {
                return 0;
              }
              FUN_004122a4((int)param_2,param_3,param_4,(int)param_5,param_6);
            }
            break;
          case 5:
          case 7:
            iVar1 = FUN_00439c56((int)param_6,2);
            if (iVar1 == 0) {
              return 0;
            }
            iVar1 = FUN_004060d8(0,param_6,0,2,0,0);
            if (iVar1 == 0) {
              return 0;
            }
            iVar1 = FUN_0042b08d(param_3[5],param_6[5]);
            if (iVar1 != 0) {
              return 0;
            }
            FUN_004122a4((int)param_2,param_3,param_4,(int)param_5,param_6);
          }
        }
        else {
          iVar1 = FUN_004060d8(1,param_5,0,2,0,0);
          if (iVar1 == 0) {
            return 0;
          }
          iVar1 = FUN_0042b08d(param_3[5],param_5[5]);
          if (iVar1 != 0) {
            return 0;
          }
          iVar1 = FUN_004060d8(2,param_6,4,0,0,0);
          if (iVar1 == 0) {
            return 0;
          }
          FUN_0041231c((int)param_2,param_3,param_4,param_5,(int)param_6);
        }
        uVar2 = 1;
      }
    }
  }
  return uVar2;
}


/* ==== FUN_0042aa80 @ 0042aa80 ==== */

undefined4 __cdecl FUN_0042aa80(uint param_1,undefined4 *param_2,int *param_3,int *param_4)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  
  bVar1 = FUN_0043bccb();
  if (CONCAT31(extraout_var,bVar1) == 0) {
    return 0;
  }
  PTR_DAT_0044f820 = PTR_DAT_0044f81c;
  PTR_DAT_0044f81c = &DAT_0045ec04;
  switch(*param_3) {
  case 7:
  case 8:
  case 0xe:
    DAT_0045f928 = DAT_0045f928 + 2;
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
    iVar2 = FUN_004060d8(2,param_4,0x12,0,0,0);
    if (iVar2 == 0) {
      return 0;
    }
    switch(param_4[5]) {
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
      if (((((*param_3 == 3) || (*param_3 == 5)) || (*param_3 == 4)) || (*param_3 == 6)) &&
         (param_3[5] == param_4[5])) {
        FUN_004133a9((uint *)s_Post_update_operation_will_not_o_00456d5c);
      }
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      iVar2 = FUN_0042b1e5(param_1,0x11,0);
      if (iVar2 == 0) {
        return 0;
      }
      FUN_00412566(param_2,param_3,(int)param_4);
      break;
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
      iVar2 = FUN_0042b1e5(param_1,0x10,(int)param_2);
      if (iVar2 == 0) {
        return 0;
      }
      FUN_004120a7(param_2,param_3,(int)param_4);
      break;
    default:
      FUN_00413085((uint *)s_Illegal_X_field_destination_regi_00456d9c);
      return 0;
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      FUN_0042b12c(param_4[5]);
    case 0x2a:
      iVar2 = FUN_0042b1e5(param_1,0x10,(int)param_2);
      if (iVar2 == 0) {
        return 0;
      }
      FUN_00411db2(param_2,param_3,(int)param_4);
    }
    break;
  case 0x10:
    iVar2 = FUN_004060d8(2,param_4,0x12,0,0,0);
    if (iVar2 == 0) {
      return 0;
    }
    switch(param_4[5]) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      iVar2 = FUN_0042b1e5(param_1,0x11,0);
      if (iVar2 == 0) {
        return 0;
      }
      FUN_0041267e((int)param_2,(int)param_3,(int)param_4);
      break;
    default:
      FUN_00413085((uint *)s_Illegal_X_field_destination_regi_00456dcc);
      return 0;
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      FUN_0042b12c(param_4[5]);
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x2a:
      iVar2 = FUN_0042b1e5(param_1,0x10,(int)param_2);
      if (iVar2 == 0) {
        return 0;
      }
      FUN_00411f93((int)param_2,(int)param_3,(int)param_4);
    }
  }
  return 1;
}


/* ==== FUN_0042adb6 @ 0042adb6 ==== */

undefined4 __cdecl FUN_0042adb6(uint param_1,undefined4 *param_2,int *param_3,int *param_4)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined4 uVar2;
  int iVar3;
  
  bVar1 = FUN_0043bccb();
  if (CONCAT31(extraout_var,bVar1) == 0) {
    uVar2 = 0;
  }
  else {
    iVar3 = FUN_0042b1e5(param_1,1,0);
    if (iVar3 == 0) {
      uVar2 = 0;
    }
    else {
      if (*param_3 == 0x10) {
        iVar3 = FUN_004060d8(2,param_4,5,0,0,0);
        if (iVar3 == 0) {
          return 0;
        }
        FUN_00412a8f((int)param_2,(int)param_3,(int)param_4);
      }
      else {
        iVar3 = *param_3;
        if ((6 < iVar3) && ((iVar3 < 9 || (iVar3 == 0xe)))) {
          DAT_0045f928 = DAT_0045f928 + 2;
        }
        iVar3 = FUN_004060d8(2,param_4,5,0,0,0);
        if (iVar3 == 0) {
          return 0;
        }
        FUN_00412b7b(param_2,param_3,(int)param_4);
      }
      uVar2 = 1;
    }
  }
  return uVar2;
}


/* ==== FUN_0042ae87 @ 0042ae87 ==== */

undefined4 __cdecl FUN_0042ae87(uint param_1,undefined4 *param_2,int *param_3,int *param_4)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  undefined4 uVar3;
  
  bVar1 = FUN_0043bccb();
  if (CONCAT31(extraout_var,bVar1) == 0) {
    return 0;
  }
  iVar2 = FUN_0042b1e5(param_1,0x20,(int)param_2);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = DAT_0045f928 + 4;
  switch(*param_3) {
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 0x10:
    break;
  case 7:
  case 8:
  case 0xe:
    iVar2 = DAT_0045f928 + 6;
    break;
  default:
    goto switchD_0042aeef_caseD_9;
  }
  DAT_0045f928 = iVar2;
  iVar2 = FUN_004060d8(2,param_4,0x12,0,0,0);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    switch(param_4[5]) {
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
      if (((((*param_3 == 3) || (*param_3 == 5)) || (*param_3 == 4)) || (*param_3 == 6)) &&
         (param_3[5] == param_4[5])) {
        FUN_004133a9((uint *)s_Post_update_operation_will_not_o_00456dfc);
      }
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x2a:
      if (*param_3 == 0x10) {
        FUN_00412e1b((int)param_2,(int)param_3,(int)param_4);
        iVar2 = DAT_0045f928;
      }
      else {
        FUN_00412da0(param_2,param_3,(int)param_4);
        iVar2 = DAT_0045f928;
      }
      break;
    default:
      FUN_00413085((uint *)s_Illegal_X_field_destination_regi_00456e3c);
      return 0;
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      FUN_0042b12c(param_4[5]);
      if (*param_3 == 0x10) {
        FUN_00412e1b((int)param_2,(int)param_3,(int)param_4);
        iVar2 = DAT_0045f928;
      }
      else {
        FUN_00412da0(param_2,param_3,(int)param_4);
        iVar2 = DAT_0045f928;
      }
    }
switchD_0042aeef_caseD_9:
    DAT_0045f928 = iVar2;
    uVar3 = 1;
  }
  return uVar3;
}


/* ==== FUN_0042b08d @ 0042b08d ==== */

undefined4 __cdecl FUN_0042b08d(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
    if ((param_2 < 0xe) || (0x11 < param_2)) {
      uVar1 = 0;
    }
    else {
      FUN_00413085((uint *)s_Invalid_XY_address_register_spec_00456e6c);
      uVar1 = 1;
    }
    break;
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
    if ((param_2 < 0x12) || (0x15 < param_2)) {
      uVar1 = 0;
    }
    else {
      FUN_00413085((uint *)s_Invalid_XY_address_register_spec_00456e98);
      uVar1 = 1;
    }
    break;
  default:
    uVar1 = 0;
  }
  return uVar1;
}


