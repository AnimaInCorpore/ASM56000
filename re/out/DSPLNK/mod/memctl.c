/* memctl: 15 functions from DSPLNK */

/* ==== FUN_00421ec7 @ 00421ec7 ==== */

void __cdecl FUN_00421ec7(undefined4 param_1,int param_2)

{
  DAT_00461f18 = param_1;
  DAT_00461dc8 = FUN_00421eef;
  thunk_FUN_0042e25d(0,param_2 + -1);
  return;
}


/* ==== FUN_00421eef @ 00421eef ==== */

int __cdecl FUN_00421eef(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = strcmp((char *)*param_1,(char *)*param_2);
  if (iVar1 == 0) {
    if ((param_1[2] == 0) && (param_2[2] == 0)) {
      iVar1 = 0;
    }
    else if (param_1[2] == 0) {
      iVar1 = -1;
    }
    else if (param_2[2] == 0) {
      iVar1 = 1;
    }
    else if (param_1[2] == param_2[2]) {
      iVar1 = 0;
    }
    else {
      iVar1 = strcmp(*(char **)param_1[2],*(char **)param_2[2]);
    }
  }
  return iVar1;
}


/* ==== FUN_00421f79 @ 00421f79 ==== */

undefined4 __cdecl FUN_00421f79(int param_1,int param_2)

{
  if (param_1 < 0x1d) {
    if (param_1 == 0x1c) {
      if (param_2 < 0x11e) {
        if (param_2 == 0x11d) {
          return 0xffffffff;
        }
        if ((-1 < param_2) && (param_2 < 4)) {
          return 1;
        }
      }
      else if (param_2 == 0x11f) {
        return 0xffffffff;
      }
    }
    else {
      switch(param_1) {
      case 0:
        if (param_2 < 0x1d) {
          if (param_2 == 0x1c) {
            return 0xffffffff;
          }
          if ((0 < param_2) && (param_2 < 4)) {
            return 1;
          }
        }
        else {
          if (param_2 == 0x11d) {
            return 0xffffffff;
          }
          if (param_2 == 0x11f) {
            return 0xffffffff;
          }
        }
        break;
      case 1:
        if (param_2 < 0x1d) {
          if (((param_2 == 0x1c) || (param_2 == 0)) || ((1 < param_2 && (param_2 < 4)))) {
            return 0xffffffff;
          }
        }
        else {
          if (param_2 == 0x11d) {
            return 0xffffffff;
          }
          if (param_2 == 0x11f) {
            return 0xffffffff;
          }
        }
        break;
      case 2:
        if (param_2 < 0x1d) {
          if ((param_2 != 0x1c) && (param_2 != 0)) {
            if (param_2 == 1) {
              return 1;
            }
            if (param_2 != 3) {
              return 0;
            }
          }
        }
        else if ((param_2 != 0x11d) && (param_2 != 0x11f)) {
          return 0;
        }
        return 0xffffffff;
      case 3:
        if (param_2 < 0x1d) {
          if ((param_2 == 0x1c) || (param_2 == 0)) {
            return 0xffffffff;
          }
          if ((0 < param_2) && (param_2 < 3)) {
            return 1;
          }
        }
        else {
          if (param_2 == 0x11d) {
            return 0xffffffff;
          }
          if (param_2 == 0x11f) {
            return 0xffffffff;
          }
        }
      }
    }
  }
  else if (param_1 == 0x11d) {
    if (param_2 < 0x1d) {
      if ((param_2 == 0x1c) || ((-1 < param_2 && (param_2 < 4)))) {
        return 1;
      }
    }
    else if (param_2 == 0x11f) {
      return 0xffffffff;
    }
  }
  else if (param_1 == 0x11f) {
    if (param_2 < 0x1d) {
      if ((param_2 == 0x1c) || ((-1 < param_2 && (param_2 < 4)))) {
        return 1;
      }
    }
    else if (param_2 == 0x11d) {
      return 1;
    }
  }
  return 0;
}


/* ==== FUN_004221bc @ 004221bc ==== */

undefined4 __cdecl FUN_004221bc(int param_1,int param_2)

{
  if (param_1 < 0x1d) {
    if (param_1 == 0x1c) {
      if (param_2 < 0x11e) {
        if (param_2 == 0x11d) {
          return 0xffffffff;
        }
        if ((-1 < param_2) && (param_2 < 4)) {
          return 1;
        }
      }
      else if (param_2 == 0x11f) {
        return 0xffffffff;
      }
    }
    else {
      switch(param_1) {
      case 0:
        if (param_2 < 0x1d) {
          if (param_2 == 0x1c) {
            return 0xffffffff;
          }
          if ((0 < param_2) && (param_2 < 4)) {
            return 1;
          }
        }
        else {
          if (param_2 == 0x11d) {
            return 0xffffffff;
          }
          if (param_2 == 0x11f) {
            return 0xffffffff;
          }
        }
        break;
      case 1:
        if (param_2 < 0x1d) {
          if (((param_2 == 0x1c) || (param_2 == 0)) || (param_2 == 2)) {
            return 0xffffffff;
          }
          if (param_2 == 3) {
            return 1;
          }
        }
        else {
          if (param_2 == 0x11d) {
            return 0xffffffff;
          }
          if (param_2 == 0x11f) {
            return 0xffffffff;
          }
        }
        break;
      case 2:
        if (param_2 < 0x1d) {
          if ((param_2 == 0x1c) || (param_2 == 0)) {
            return 0xffffffff;
          }
          if ((param_2 == 1) || (param_2 == 3)) {
            return 1;
          }
        }
        else {
          if (param_2 == 0x11d) {
            return 0xffffffff;
          }
          if (param_2 == 0x11f) {
            return 0xffffffff;
          }
        }
        break;
      case 3:
        if (param_2 < 0x1d) {
          if ((param_2 == 0x1c) || ((-1 < param_2 && (param_2 < 3)))) {
            return 0xffffffff;
          }
        }
        else {
          if (param_2 == 0x11d) {
            return 0xffffffff;
          }
          if (param_2 == 0x11f) {
            return 0xffffffff;
          }
        }
      }
    }
  }
  else if (param_1 == 0x11d) {
    if (param_2 < 0x1d) {
      if ((param_2 == 0x1c) || ((-1 < param_2 && (param_2 < 4)))) {
        return 1;
      }
    }
    else if (param_2 == 0x11f) {
      return 0xffffffff;
    }
  }
  else if (param_1 == 0x11f) {
    if (param_2 < 0x1d) {
      if ((param_2 == 0x1c) || ((-1 < param_2 && (param_2 < 4)))) {
        return 1;
      }
    }
    else if (param_2 == 0x11d) {
      return 1;
    }
  }
  return 0;
}


/* ==== FUN_00423710 @ 00423710 ==== */

undefined4 __cdecl FUN_00423710(int param_1)

{
  undefined4 *puVar1;
  undefined4 local_b8;
  undefined4 uStack_b4;
  undefined4 *local_20;
  undefined *local_1c;
  undefined4 local_18;
  undefined4 *local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 1;
  DAT_00461db4 = DAT_00461f40;
  DAT_00461dbc = &local_1c;
  local_1c = &DAT_00461730;
  local_18 = 0;
  local_14 = &local_b8;
  local_b8 = 0;
  local_10 = 0;
  local_c = 0;
  DAT_00461318 = 1;
  do {
    FUN_00423863(param_1);
    if (DAT_00461dc0 != (undefined4 *)0x0) {
      *DAT_00461dbc = (undefined *)*DAT_00461dc0;
      puVar1 = DAT_00461dc0;
      DAT_00461db4 = DAT_00461dc0[1];
      DAT_00457bfc = DAT_00461dc0[2];
      DAT_00461318 = DAT_00461dc0[3];
      local_20 = DAT_00461dc0;
      DAT_00461dc0 = (undefined4 *)DAT_00461dc0[4];
      thunk_FUN_0042e1ce((undefined *)puVar1);
    }
  } while ((*(uint *)(DAT_00461db4 + 0xc) & 0x10) == 0);
  if (DAT_00461dd0 != DAT_00461dcc) {
    thunk_FUN_00409bfd(s_Region_without_associated_ENDR_d_00459a90,*DAT_00461dd0);
  }
  if ((DAT_0046122c == '\0') && (DAT_00461dcc[3] != 0)) {
    uStack_b4 = 0x423845;
    local_8 = FUN_00426558();
  }
  DAT_00461dbc = (undefined **)0x0;
  DAT_00461318 = 0;
  return local_8;
}


/* ==== FUN_00423863 @ 00423863 ==== */

int __cdecl FUN_00423863(int param_1)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined4 *puVar4;
  int iVar5;
  int local_2cc;
  int local_2c8;
  int local_2c4;
  uint local_2c0;
  uint local_2bc;
  uint local_2b8;
  uint local_2b4;
  uint local_2b0;
  uint local_2ac;
  uint local_2a8;
  char local_2a0;
  uint local_29c;
  int local_294;
  int local_290;
  undefined4 local_28c;
  undefined4 local_288;
  undefined4 local_284;
  undefined4 *local_280;
  int *local_27c;
  char local_278 [512];
  int local_78;
  char *local_74 [4];
  int local_64;
  undefined4 local_4c;
  int local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  int *local_2c;
  int *local_28;
  char *local_c;
  char *local_8;
  
  local_78 = 1;
  local_288 = 0;
  local_284 = 0;
  local_28c = 0;
  local_290 = 0;
  DAT_00461ddc = thunk_FUN_0042bc50((uint *)s_GLOBAL_00457f88,DAT_00461fc4,&local_290,0);
  if (DAT_00461ddc == (int *)0x0) {
    thunk_FUN_004098b0(s_Cannot_find_GLOBAL_section_00459abc);
  }
LAB_004238ea:
  do {
    while( true ) {
      while( true ) {
        uVar2 = FUN_00426562(0);
        if (uVar2 == 0xffffffff) {
          return local_78;
        }
        if (DAT_00461320 != ';') break;
        FUN_00426562(4);
      }
      local_8 = local_278;
      for (local_c = &DAT_00461320; *local_c != '\0'; local_c = local_c + 1) {
        if (__mb_cur_max < 2) {
          local_29c = *(ushort *)(_pctype + *local_c * 2) & 1;
        }
        else {
          local_29c = _isctype((int)*local_c,1);
        }
        if (local_29c == 0) {
          local_2a0 = *local_c;
        }
        else {
          iVar3 = tolower((int)*local_c);
          local_2a0 = (char)iVar3;
        }
        *local_8 = local_2a0;
        local_8 = local_8 + 1;
      }
      *local_8 = '\0';
      iVar3 = thunk_FUN_0042d8d0(local_278);
      if (iVar3 != 0) break;
      thunk_FUN_00409bfd(s_Invalid_relocation_type_field_00459ad8,&DAT_00461320);
      FUN_00426562(4);
    }
    switch(*(undefined4 *)(iVar3 + 4)) {
    case 1:
      if (param_1 == 0) {
        uVar2 = FUN_00426562(0);
        if ((int)uVar2 < 1) {
          if (DAT_00461dc4 != (char *)0x0) {
            thunk_FUN_0042e1ce(DAT_00461dc4);
          }
          uVar2 = strlen(&DAT_00461320);
          DAT_00461dc4 = (char *)thunk_FUN_0042e170(uVar2 + 1);
          strcpy(DAT_00461dc4,&DAT_00461320);
          DAT_00461254 = 1;
        }
        else {
          thunk_FUN_00409a25(s_Invalid_start_address_field_00459cdc);
          FUN_00426562(4);
          local_78 = 0;
        }
      }
      else {
        FUN_00426562(4);
      }
      break;
    case 2:
      uVar2 = FUN_00426562(0);
      if (uVar2 == 0) {
        local_280 = thunk_FUN_0042c13b((uint *)&DAT_00461320);
        if (local_280 == (undefined4 *)0x0) {
          thunk_FUN_00409bfd(s_Section_not_found_00459b9c,&DAT_00461320);
          FUN_00426562(4);
          local_78 = 0;
        }
        else {
          DAT_00461320 = '\0';
          FUN_00426562(4);
          for (local_8 = &DAT_00461320; *local_8 != '\0'; local_8 = local_8 + 1) {
            if (__mb_cur_max < 2) {
              local_2ac = *(ushort *)(_pctype + *local_8 * 2) & 8;
            }
            else {
              local_2ac = _isctype((int)*local_8,8);
            }
            if (local_2ac == 0) break;
          }
          if ((*local_8 == '\0') || (*local_8 == ';')) {
            for (local_294 = local_280[2]; local_294 != 0; local_294 = *(int *)(local_294 + 0x74)) {
              if (*(int *)(local_294 + 0x18) != 0) {
                DAT_00461dd4 = thunk_FUN_0042c4e2((int)DAT_00461dd0,(int *)(local_294 + 8),0);
                thunk_FUN_004252ad((int)DAT_00461dd4,*(int **)(local_294 + 0x18),0x100);
              }
            }
          }
          else {
            for (; *local_8 != '\0'; local_8 = local_8 + 1) {
              if (__mb_cur_max < 2) {
                local_2b0 = *(ushort *)(_pctype + *local_8 * 2) & 8;
              }
              else {
                local_2b0 = _isctype((int)*local_8,8);
              }
              if (local_2b0 != 0) break;
            }
            if (*local_8 != '\0') {
              *local_8 = '\0';
            }
            local_78 = FUN_00424879(*(int *)(iVar3 + 4),local_280);
            if (local_78 == 0) {
              FUN_00426562(4);
            }
          }
        }
      }
      else {
        thunk_FUN_00409a25(s_Invalid_section_name_field_00459b80);
        FUN_00426562(4);
        local_78 = 0;
      }
      break;
    case 3:
      if ((param_1 != 0) || (local_78 = FUN_00425470(), local_78 == 0)) {
        FUN_00426562(4);
      }
      break;
    default:
      thunk_FUN_004098b0(s_Relocation_type_select_failure_00459cf8);
      break;
    case 5:
    case 9:
    case 10:
      if (param_1 != 0) {
        FUN_00426562(4);
        break;
      }
    case 7:
      uVar2 = FUN_00426562(0);
      if ((int)uVar2 < 1) {
        iVar3 = FUN_00424879(*(int *)(iVar3 + 4),(undefined4 *)0x0);
        if (iVar3 == 0) {
          FUN_00426562(4);
          local_78 = 0;
        }
      }
      else {
        thunk_FUN_00409a25(s_Invalid_address_relocation_field_00459af8);
        FUN_00426562(4);
        local_78 = 0;
      }
      break;
    case 6:
      if ((param_1 != 0) || (local_78 = FUN_0042568f(), local_78 == 0)) {
        FUN_00426562(4);
      }
      break;
    case 0xb:
      if (param_1 == 0) {
        uVar2 = FUN_00426562(0);
        if (uVar2 == 0) {
          if ((PTR_DAT_00457fa4 != (undefined *)0x0) && (PTR_DAT_00457fa4 != &DAT_00457be8)) {
            thunk_FUN_0042e1ce(PTR_DAT_00457fa4);
          }
          uVar2 = strlen(&DAT_00461320);
          PTR_DAT_00457fa4 = (undefined *)thunk_FUN_0042e170(uVar2 + 1);
          strcpy(PTR_DAT_00457fa4,&DAT_00461320);
          uVar2 = FUN_00426562(0);
          if ((uVar2 == 0) && (bVar1 = thunk_FUN_004300f8(), CONCAT31(extraout_var,bVar1) != 0)) {
            sscanf(&DAT_00461320,&DAT_00459b58,&DAT_00461fc8);
            uVar2 = FUN_00426562(0);
            if ((uVar2 == 0) && (bVar1 = thunk_FUN_004300f8(), CONCAT31(extraout_var_00,bVar1) != 0)
               ) {
              sscanf(&DAT_00461320,&DAT_00459b7c,&DAT_00461fcc);
              if ((PTR_DAT_00457fa8 != (undefined *)0x0) && (PTR_DAT_00457fa8 != &DAT_0046131c)) {
                thunk_FUN_0042e1ce(PTR_DAT_00457fa8);
              }
              DAT_00461320 = '\0';
              FUN_00426562(4);
              for (local_8 = &DAT_00461320; *local_8 != '\0'; local_8 = local_8 + 1) {
                if (__mb_cur_max < 2) {
                  local_2a8 = *(ushort *)(_pctype + *local_8 * 2) & 8;
                }
                else {
                  local_2a8 = _isctype((int)*local_8,8);
                }
                if (local_2a8 == 0) break;
              }
              uVar2 = strlen(local_8);
              PTR_DAT_00457fa8 = (undefined *)thunk_FUN_0042e170(uVar2 + 1);
              strcpy(PTR_DAT_00457fa8,local_8);
            }
            else {
              thunk_FUN_00409a25(s_Invalid_revision_number_field_00459b5c);
              FUN_00426562(4);
              local_78 = 0;
            }
          }
          else {
            thunk_FUN_00409a25(s_Invalid_version_number_field_00459b38);
            FUN_00426562(4);
            local_78 = 0;
          }
        }
        else {
          thunk_FUN_00409a25(s_Invalid_module_name_field_00459b1c);
          FUN_00426562(4);
          local_78 = 0;
        }
      }
      else {
        FUN_00426562(4);
      }
      break;
    case 0xc:
      uVar2 = FUN_00426562(0);
      if (uVar2 == 0) {
        local_280 = thunk_FUN_0042c13b((uint *)&DAT_00461320);
        if (local_280 == (undefined4 *)0x0) {
          thunk_FUN_00409bfd(s_Section_not_found_00459c58,&DAT_00461320);
          FUN_00426562(4);
          local_78 = 0;
        }
        else {
          uVar2 = FUN_00426562(0);
          if ((int)uVar2 < 1) {
            local_78 = FUN_00424879(*(int *)(iVar3 + 4),local_280);
            if (local_78 == 0) {
              FUN_00426562(4);
            }
          }
          else {
            thunk_FUN_00409a25(s_Invalid_address_relocation_field_00459c6c);
            FUN_00426562(4);
            local_78 = 0;
          }
        }
      }
      else {
        thunk_FUN_00409a25(s_Invalid_section_name_field_00459c3c);
        FUN_00426562(4);
        local_78 = 0;
      }
      break;
    case 0xd:
      if (DAT_00461dd0 == DAT_00461dcc) {
        uVar2 = FUN_00426562(0);
        if (uVar2 == 0) {
          DAT_00461dd0 = thunk_FUN_0042c373((uint *)&DAT_00461320);
          DAT_00461320 = '\0';
          FUN_00426562(4);
          for (local_8 = &DAT_00461320; *local_8 != '\0'; local_8 = local_8 + 1) {
            if (__mb_cur_max < 2) {
              local_2bc = *(ushort *)(_pctype + *local_8 * 2) & 8;
            }
            else {
              local_2bc = _isctype((int)*local_8,8);
            }
            if (local_2bc == 0) break;
          }
          if ((*local_8 != '\0') && (*local_8 != ';')) {
            for (; *local_8 != '\0'; local_8 = local_8 + 1) {
              if (__mb_cur_max < 2) {
                local_2c0 = *(ushort *)(_pctype + *local_8 * 2) & 8;
              }
              else {
                local_2c0 = _isctype((int)*local_8,8);
              }
              if (local_2c0 != 0) break;
            }
            if (*local_8 != '\0') {
              *local_8 = '\0';
            }
            local_78 = FUN_00424879(*(int *)(iVar3 + 4),(undefined4 *)0x0);
            if (local_78 == 0) {
              DAT_00461dd0 = DAT_00461dcc;
              FUN_00426562(4);
            }
          }
        }
        else {
          thunk_FUN_00409a25(s_Invalid_region_name_field_00459bf4);
          FUN_00426562(4);
          local_78 = 0;
        }
      }
      else {
        thunk_FUN_00409a25(s_Cannot_nest_regions_00459be0);
        FUN_00426562(4);
        local_78 = 0;
      }
      break;
    case 0xe:
      if (DAT_00461dd0 == DAT_00461dcc) {
        thunk_FUN_00409a25(s_ENDR_without_corresponding_REGIO_00459c10);
      }
      else {
        if (DAT_00461dd4 == (undefined4 *)0x0) {
          DAT_00461dd4 = thunk_FUN_0042c4e2((int)DAT_00461dd0,&local_290,0);
        }
        FUN_004250ad((int)DAT_00461dd0);
        DAT_00461dd0 = DAT_00461dcc;
        DAT_00461dd4 = (undefined4 *)0x0;
        FUN_00426562(4);
      }
      break;
    case 0xf:
      local_78 = FUN_0042609f();
      if (local_78 == 0) {
        FUN_00426562(4);
      }
      break;
    case 0x10:
      if (DAT_00461248 == '\0') {
        uVar2 = FUN_00426562(0);
        if (uVar2 == 0) {
          local_280 = thunk_FUN_0042c13b((uint *)&DAT_00461320);
          if (local_280 == (undefined4 *)0x0) {
            thunk_FUN_00409bfd(s_Section_not_found_00459bcc,&DAT_00461320);
            FUN_00426562(4);
            local_78 = 0;
          }
          else {
            DAT_00461320 = '\0';
            FUN_00426562(4);
            for (local_8 = &DAT_00461320; *local_8 != '\0'; local_8 = local_8 + 1) {
              if (__mb_cur_max < 2) {
                local_2b4 = *(ushort *)(_pctype + *local_8 * 2) & 8;
              }
              else {
                local_2b4 = _isctype((int)*local_8,8);
              }
              if (local_2b4 == 0) break;
            }
            if ((*local_8 == '\0') || (*local_8 == ';')) {
              for (local_294 = local_280[2]; local_294 != 0; local_294 = *(int *)(local_294 + 0x74))
              {
                if ((*(int *)(local_294 + 0x18) != 0) && ((*(uint *)(local_294 + 4) & 0x40000) == 0)
                   ) {
                  *(uint *)(*(int *)(local_294 + 0x18) + 8) =
                       *(uint *)(*(int *)(local_294 + 0x18) + 8) | 0x20000;
                  for (local_27c = *(int **)(**(int **)(local_294 + 0x18) + 0x20);
                      local_27c != (int *)0x0; local_27c = (int *)local_27c[0x11]) {
                    if ((local_27c[2] & 0x1000U) != 0) {
                      local_27c[2] = local_27c[2] | 0x20000;
                    }
                  }
                }
              }
            }
            else {
              for (; *local_8 != '\0'; local_8 = local_8 + 1) {
                if (__mb_cur_max < 2) {
                  local_2b8 = *(ushort *)(_pctype + *local_8 * 2) & 8;
                }
                else {
                  local_2b8 = _isctype((int)*local_8,8);
                }
                if (local_2b8 != 0) break;
              }
              if (*local_8 != '\0') {
                *local_8 = '\0';
              }
              local_78 = FUN_00424879(*(int *)(iVar3 + 4),local_280);
              if (local_78 == 0) {
                FUN_00426562(4);
              }
            }
          }
        }
        else {
          thunk_FUN_00409a25(s_Invalid_section_name_field_00459bb0);
          FUN_00426562(4);
          local_78 = 0;
        }
      }
      else {
        local_78 = 1;
      }
      break;
    case 0x11:
    case 0x12:
      goto switchD_00423a32_caseD_11;
    }
  } while( true );
switchD_00423a32_caseD_11:
  uVar2 = FUN_00426562(0);
  if (uVar2 == 0) {
    puVar4 = thunk_FUN_0042c8ba((uint *)&DAT_00461320,0);
    if (puVar4 == (undefined4 *)0x0) {
      strcpy(local_278,&DAT_00461320);
      uVar2 = FUN_00426562(0);
      if ((int)uVar2 < 1) {
        DAT_00461d68 = (uint *)&DAT_00461320;
        iVar5 = thunk_FUN_0042e743(&local_290);
        if (iVar5 == 0) {
          return 0;
        }
        local_27c = (int *)0x0;
        memset(local_74,0,0x68);
        local_74[0] = local_278;
        local_4c = 0x20140;
        local_48 = local_290;
        local_44 = local_28c;
        local_40 = local_288;
        local_3c = local_284;
        local_38 = 0xffffffff;
        if ((char)*DAT_00461d68 != '\0') {
          local_27c = (int *)thunk_FUN_0042bed4(DAT_00461d68,&local_290);
          if (local_27c == (int *)0x0) {
            if (DAT_00461290 == '\0') {
              thunk_FUN_00409f4d(s_Section_not_found_00459cc8,DAT_00461d68);
            }
            FUN_00426562(4);
            local_28 = DAT_00461ddc;
            local_2c = DAT_00461ddc;
            local_64 = 0;
          }
          else {
            local_2c = local_27c;
            local_28 = local_27c;
            if (local_27c == (int *)0x0) {
              local_64 = 0;
            }
            else if (DAT_00461244 == '\0') {
              if (local_27c[7] == 0) {
                local_2cc = local_27c[8];
              }
              else {
                local_2cc = local_27c[7];
              }
              local_2c8 = local_2cc;
              local_64 = local_2c8;
            }
            else {
              if (*(int *)(*local_27c + 0x54) == 0) {
                local_2c4 = *(int *)(*local_27c + 0x50);
              }
              else {
                local_2c4 = *(int *)(*local_27c + 0x54);
              }
              local_2c8 = local_2c4;
              local_64 = local_2c8;
            }
          }
        }
        if (*(int *)(iVar3 + 4) == 0x12) {
          if ((local_28 == (int *)0x0) || (local_28[9] == 0)) {
            if ((local_2c == (int *)0x0) ||
               (((*local_2c == 0 || (*(int *)(*local_2c + 0x74) == 0)) ||
                (*(int *)(*(int *)(*local_2c + 0x74) + 0x18) == 0)))) {
              local_64 = 0;
            }
            else {
              local_64 = *(int *)(*(int *)(*(int *)(*local_2c + 0x74) + 0x18) + 0x24);
            }
          }
          else {
            local_64 = local_28[9];
          }
        }
        thunk_FUN_0042c6c1((int *)local_74);
      }
      else {
        thunk_FUN_00409a25(s_Invalid_memory_space_field_00459cac);
        FUN_00426562(4);
        local_78 = 0;
      }
    }
    else {
      FUN_00426562(4);
      local_78 = 1;
    }
  }
  else {
    thunk_FUN_00409a25(s_Invalid_symbol_name_field_00459c90);
    FUN_00426562(4);
    local_78 = 0;
  }
  goto LAB_004238ea;
}


/* ==== FUN_00424879 @ 00424879 ==== */

undefined4 __cdecl FUN_00424879(int param_1,undefined4 *param_2)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  uint local_44;
  int local_40;
  uint local_3c;
  int local_38;
  int local_34;
  int *local_28;
  char local_24;
  int *local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined8 local_10;
  double *local_8;
  
  local_28 = (int *)0x0;
  local_20 = (int *)0x0;
  local_3c = 0;
  local_18 = 0;
  local_24 = '\0';
  local_10 = 1.0;
  if (((param_1 == 5) || (param_1 == 7)) || (param_1 == 0xd)) {
    local_40 = 1;
  }
  else {
    local_40 = 0;
  }
  local_14 = local_40;
  for (DAT_00461d68 = &DAT_00461320; *DAT_00461d68 != '\0'; DAT_00461d68 = DAT_00461d68 + 1) {
    if (__mb_cur_max < 2) {
      local_44 = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 8;
    }
    else {
      local_44 = _isctype((int)*DAT_00461d68,8);
    }
    if (local_44 == 0) break;
  }
  while( true ) {
    if (*DAT_00461d68 == '\0') {
      return 1;
    }
    iVar2 = thunk_FUN_0042e743(&local_38);
    if (iVar2 == 0) break;
    DAT_00461dd4 = thunk_FUN_0042c4e2(DAT_00461dd0,&local_38,local_14);
    if (param_2 != (undefined4 *)0x0) {
      local_28 = thunk_FUN_0042c1ef((int)param_2,&local_38);
      local_20 = (int *)local_28[6];
      if (local_20 == (int *)0x0) {
        local_20 = thunk_FUN_0042bc50((uint *)*param_2,param_2[1],&local_38,0);
      }
      if (local_28[3] != local_34) {
        if (((local_28[1] & 0x1000000U) != 0) && (DAT_00461274 == '\0')) {
          thunk_FUN_00409d88(s_Remapping_section_00459d18);
        }
        local_28[1] = local_28[1] | 0x1000000;
        local_28[3] = local_34;
      }
    }
    if ((param_1 == 2) && ((*DAT_00461d68 == '\0' || (*DAT_00461d68 == ',')))) {
      if (*DAT_00461d68 == ',') {
        DAT_00461d68 = DAT_00461d68 + 1;
      }
      thunk_FUN_004252ad((int)DAT_00461dd4,local_20,0x100);
    }
    else if ((param_1 == 0x10) && ((*DAT_00461d68 == '\0' || (*DAT_00461d68 == ',')))) {
      if (*DAT_00461d68 == ',') {
        DAT_00461d68 = DAT_00461d68 + 1;
      }
      if ((local_28[1] & 0x40000U) == 0) {
        local_20[2] = local_20[2] | 0x20000;
        for (local_1c = local_28[8]; local_1c != 0; local_1c = *(int *)(local_1c + 0x44)) {
          if ((*(uint *)(local_1c + 8) & 0x1000) != 0) {
            *(uint *)(local_1c + 8) = *(uint *)(local_1c + 8) | 0x20000;
          }
        }
      }
    }
    else if ((DAT_00461248 == '\0') &&
            ((param_1 == 10 && ((*DAT_00461d68 == '\0' || (*DAT_00461d68 == ',')))))) {
      if (*DAT_00461d68 == ',') {
        DAT_00461d68 = DAT_00461d68 + 1;
      }
      DAT_00461dd4[1] = DAT_00461dd4[1] | 0x20000;
    }
    else {
      if (param_1 == 0xc) {
        local_8 = (double *)thunk_FUN_0040a571();
        if (local_8 == (double *)0x0) {
          return 0;
        }
        if (*(int *)(local_8 + 2) == 0x200) {
          if (*local_8 <= 100.0) {
            thunk_FUN_00409a25(s_Section_padding_percentage_too_s_00459e14);
            thunk_FUN_0040ca80((undefined *)local_8);
            return 0;
          }
          local_24 = '\x01';
          local_10 = *local_8 / 100.0;
        }
        else {
          local_24 = '\0';
          local_3c = *(uint *)(local_8 + 1);
          if ((DAT_00457b78 != '\0') && ((uint)DAT_00461dd4[8] < local_3c)) {
            thunk_FUN_00409a25(s_Specified_size_greater_than_maxi_00459de0);
          }
        }
      }
      else {
        local_8 = (double *)thunk_FUN_0040a370();
        if (local_8 == (double *)0x0) {
          return 0;
        }
        local_3c = *(uint *)(local_8 + 1);
        if ((DAT_00457b78 != '\0') && ((uint)DAT_00461dd4[8] < local_3c)) {
          thunk_FUN_00409a25(s_Specified_address_greater_than_m_00459d2c);
        }
        if (param_1 == 9) {
          pcVar3 = DAT_00461d68 + 1;
          pcVar1 = pcVar3;
          if ((*DAT_00461d68 != '.') ||
             (DAT_00461d68 = DAT_00461d68 + 2, pcVar1 = DAT_00461d68, *pcVar3 != '.')) {
            DAT_00461d68 = pcVar1;
            thunk_FUN_00409a25(s_Invalid_reserve_range_syntax_00459d64);
            thunk_FUN_0040ca80((undefined *)local_8);
            return 0;
          }
          thunk_FUN_0040ca80((undefined *)local_8);
          local_8 = (double *)thunk_FUN_0040a370();
          if (local_8 == (double *)0x0) {
            return 0;
          }
          local_18 = *(int *)(local_8 + 1);
          if ((DAT_00457b78 != '\0') && ((uint)DAT_00461dd4[8] < local_3c)) {
            thunk_FUN_00409a25(s_Specified_address_greater_than_m_00459d84);
          }
        }
        else if ((*DAT_00461d68 != '\0') && (*DAT_00461d68 != ',')) {
          thunk_FUN_00409a25(s_Extra_characters_beyond_expressi_00459dbc);
          return 0;
        }
      }
      thunk_FUN_0040ca80((undefined *)local_8);
      for (; (*DAT_00461d68 != '\0' && (*DAT_00461d68 != ',')); DAT_00461d68 = DAT_00461d68 + 1) {
      }
      if ((*DAT_00461d68 != '\0') && (*DAT_00461d68 == ',')) {
        DAT_00461d68 = DAT_00461d68 + 1;
      }
      switch(param_1) {
      case 2:
        local_20[3] = local_20[3] & 0xfffffeff;
        local_20[3] = local_20[3] | 0x200;
        local_20[4] = local_3c;
        local_20[5] = local_20[5] + local_3c;
        DAT_00461dd4 = thunk_FUN_0042c4e2(DAT_00461dd0,&local_38,0);
        thunk_FUN_004252ad((int)DAT_00461dd4,local_20,0x200);
        break;
      default:
        thunk_FUN_004098b0(s_Relocation_type_select_failure_00459e94);
        break;
      case 5:
        if ((DAT_00461dd4[2] & 0x100000) == 0) {
          DAT_00461dd4[7] = local_3c;
          DAT_00461dd4[2] = DAT_00461dd4[2] | 0x100000;
        }
        break;
      case 7:
        DAT_00461dd4[8] = local_3c;
        DAT_00461dd4[2] = DAT_00461dd4[2] | 0x400000;
        break;
      case 9:
        local_20 = FUN_00426437(&local_38,local_3c,local_18 + 1);
        thunk_FUN_004252ad((int)DAT_00461dd4,local_20,0x200);
        break;
      case 10:
        if ((DAT_00461248 == '\0') &&
           (DAT_00461dd4[1] = DAT_00461dd4[1] | 0x20000, (DAT_00461dd4[2] & 0x800000) == 0)) {
          DAT_00461dd4[10] = local_3c;
          DAT_00461dd4[2] = DAT_00461dd4[2] | 0x800000;
        }
        break;
      case 0xc:
        if (((local_24 == '\0') || (local_20[0xe] == 0)) || (*(int *)local_20[0xe] == 0)) {
          local_28[1] = local_28[1] | 0x200000;
          if (local_24 == '\0') {
            local_28[0x18] = local_3c;
          }
          else {
            local_28[1] = local_28[1] | 0x2000000;
            local_28[0x18] = (int)local_10;
            local_28[0x19] = local_10._4_4_;
          }
        }
        else {
          thunk_FUN_00409a25(s_Cannot_use_SECSIZE_with_percenta_00459e3c);
        }
        break;
      case 0xd:
        DAT_00461dd4[9] = local_3c;
        DAT_00461dd4[2] = DAT_00461dd4[2] | 0x200000;
        break;
      case 0x10:
        if ((local_28[1] & 0x40000U) == 0) {
          if (DAT_00461248 == '\0') {
            DAT_00461dd4[1] = DAT_00461dd4[1] | 0x800000;
          }
          local_28[0x12] = local_3c;
          local_20[2] = local_20[2] | 0x20000;
          for (local_1c = local_28[8]; local_1c != 0; local_1c = *(int *)(local_1c + 0x44)) {
            if ((*(uint *)(local_1c + 8) & 0x1000) != 0) {
              *(uint *)(local_1c + 8) = *(uint *)(local_1c + 8) | 0x820000;
            }
          }
        }
      }
    }
  }
  return 0;
}


/* ==== FUN_004250ad @ 004250ad ==== */

undefined4 __cdecl FUN_004250ad(int param_1)

{
  char local_214 [512];
  int local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  
  local_8 = 1;
  for (local_10 = *(int *)(param_1 + 8); local_10 != 0; local_10 = *(int *)(local_10 + 0x38)) {
    if ((DAT_00457b78 == '\0') || (*(uint *)(local_10 + 0x1c) <= *(uint *)(local_10 + 0x20))) {
      local_14 = (*(int *)(local_10 + 0x20) - *(int *)(local_10 + 0x1c)) + 1;
      if ((*(uint *)(local_10 + 8) & 0x100000) == 0) {
        if ((*(uint *)(local_10 + 8) & 0x400000) == 0) {
          if ((*(uint *)(local_10 + 8) & 0x200000) != 0) {
            *(int *)(local_10 + 0x20) = *(int *)(local_10 + 0x24) + -1;
          }
        }
        else if ((*(uint *)(local_10 + 8) & 0x200000) == 0) {
          *(int *)(local_10 + 0x24) = *(int *)(local_10 + 0x20) + 1;
        }
        else {
          *(int *)(local_10 + 0x1c) = *(int *)(local_10 + 0x20) - (*(int *)(local_10 + 0x24) + -1);
        }
      }
      else if ((*(uint *)(local_10 + 8) & 0x400000) == 0) {
        if ((*(uint *)(local_10 + 8) & 0x200000) == 0) {
          *(int *)(local_10 + 0x24) = local_14;
        }
        else {
          *(int *)(local_10 + 0x20) = *(int *)(local_10 + 0x1c) + -1 + *(int *)(local_10 + 0x24);
        }
      }
      else if ((*(uint *)(local_10 + 8) & 0x200000) == 0) {
        *(int *)(local_10 + 0x24) = local_14;
      }
      else if (*(int *)(local_10 + 0x24) != local_14) {
        local_c = thunk_FUN_0042f22f(*(int *)(local_10 + 0xc));
        sprintf(local_214,s_Region__s__c__ld__size_address_m_00459eec,*(undefined4 *)param_1,
                (int)s_XYLPEDU_00457ff0[local_c],*(undefined4 *)(local_10 + 0x14));
        thunk_FUN_00409a25(local_214);
        local_8 = 0;
      }
    }
    else {
      local_c = thunk_FUN_0042f22f(*(int *)(local_10 + 0xc));
      sprintf(local_214,s_Region__s__c__ld__high_address_l_00459eb4,*(undefined4 *)param_1,
              (int)s_XYLPEDU_00457ff0[local_c],*(undefined4 *)(local_10 + 0x14));
      thunk_FUN_00409a25(local_214);
      local_8 = 0;
    }
  }
  return local_8;
}


/* ==== FUN_004252ad @ 004252ad ==== */

void __cdecl FUN_004252ad(int param_1,int *param_2,int param_3)

{
  undefined4 *puVar1;
  int *local_14;
  int *local_10;
  int *local_c;
  int *local_8;
  
  if ((*(int *)(*param_2 + 0x70) == 0) || (*(int *)(*param_2 + 0x70) == param_1)) {
    if (param_3 == 0x200) {
      *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x200;
    }
    else if (param_3 == 0x100) {
      if ((param_2[3] & 0x200U) != 0) {
        thunk_FUN_00409f4d(s_Section_already_set_as_absolute_00459f3c,**(undefined4 **)*param_2);
        return;
      }
      param_2[3] = param_2[3] | 0x100;
      *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x100;
    }
    if (*(int *)(*param_2 + 0x24) != 0) {
      *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x4000;
    }
    local_10 = (int *)0x0;
    local_c = (int *)0x0;
    local_14 = (int *)0x0;
    for (local_8 = *(int **)(param_1 + 0x30); local_8 != (int *)0x0; local_8 = (int *)local_8[1]) {
      if ((int *)*local_8 == param_2) {
        if (local_14 == (int *)0x0) {
          local_14 = local_8;
          local_10 = local_c;
        }
        else {
          thunk_FUN_004098b0(s_Duplicate_section_entry_00459f5c);
        }
      }
      local_c = local_8;
    }
    if (local_14 == (int *)0x0) {
      puVar1 = (undefined4 *)thunk_FUN_0042e170(8);
      *puVar1 = param_2;
      puVar1[1] = 0;
      if (*(int *)(param_1 + 0x30) == 0) {
        *(undefined4 **)(param_1 + 0x30) = puVar1;
      }
      else {
        local_c[1] = (int)puVar1;
      }
      *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 1;
    }
    else if (local_14 != local_c) {
      if (local_14 == *(int **)(param_1 + 0x30)) {
        *(int *)(param_1 + 0x30) = local_14[1];
      }
      else {
        local_10[1] = local_14[1];
      }
      local_c[1] = (int)local_14;
      local_14[1] = 0;
    }
    *(int *)(*param_2 + 0x70) = param_1;
  }
  else {
    thunk_FUN_00409bfd(s_Duplicate_region_assignment_for_s_00459f14,**(undefined4 **)*param_2);
  }
  return;
}


/* ==== FUN_00425470 @ 00425470 ==== */

undefined4 FUN_00425470(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  int local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined1 *local_74 [2];
  int local_6c;
  int local_68;
  int local_64;
  uint local_4c;
  int local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 *local_2c;
  undefined4 *local_28;
  int *local_c;
  char *local_8;
  
  uVar1 = FUN_00426562(0);
  if (uVar1 == 0) {
    puVar3 = thunk_FUN_0042c8ba((uint *)&DAT_00461320,0);
    if (puVar3 == (undefined4 *)0x0) {
      strcpy(&stack0xfffffd7c,&DAT_00461320);
      uVar1 = FUN_00426562(0);
      if ((int)uVar1 < 1) {
        DAT_00461d68 = &DAT_00461320;
        for (local_8 = &DAT_00461320; (*local_8 != '\0' && (*local_8 != ':')); local_8 = local_8 + 1
            ) {
        }
        if (*local_8 == ':') {
          iVar4 = thunk_FUN_0042e743(&local_84);
          if (iVar4 == 0) {
            return 0;
          }
        }
        else {
          local_80 = 4;
          local_84 = 4;
          local_7c = 0;
          local_78 = 0;
        }
        local_c = thunk_FUN_0040a571();
        if (local_c == (int *)0x0) {
          uVar2 = 0;
        }
        else {
          memset(local_74,0,0x68);
          local_74[0] = &stack0xfffffd7c;
          uVar1 = local_c[4] & 0xf00;
          local_4c = uVar1 | 0x10040;
          if ((local_c[4] & 0x200U) == 0) {
            local_6c = *local_c;
            local_68 = local_c[1];
            local_64 = local_c[2];
          }
          else {
            local_6c = *local_c;
            local_68 = local_c[1];
          }
          if (local_c[5] == DAT_00461f64) {
            local_4c = uVar1 | 0x10840;
          }
          thunk_FUN_0040ca80((undefined *)local_c);
          local_48 = local_84;
          local_44 = local_80;
          local_40 = local_7c;
          local_3c = local_78;
          local_38 = 0xffffffff;
          local_34 = 0;
          local_30 = 0;
          local_2c = thunk_FUN_0042bc50((uint *)s_GLOBAL_00457f88,DAT_00461fc4,&local_84,0);
          if (local_2c == (undefined4 *)0x0) {
            thunk_FUN_004098b0(s_Cannot_find_GLOBAL_section_00459fac);
          }
          local_28 = local_2c;
          thunk_FUN_0042c6c1((int *)local_74);
          DAT_00461efc = DAT_00461efc + 1;
          uVar2 = 1;
        }
      }
      else {
        thunk_FUN_00409a25(s_Invalid_symbol_value_field_00459f90);
        uVar2 = 0;
      }
    }
    else {
      FUN_00426562(4);
      uVar2 = 1;
    }
  }
  else {
    thunk_FUN_00409a25(s_Invalid_symbol_name_field_00459f74);
    uVar2 = 0;
  }
  return uVar2;
}


/* ==== FUN_0042568f @ 0042568f ==== */

undefined4 FUN_0042568f(void)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_00426562(0);
  if (uVar1 != 0) {
    thunk_FUN_00409a25(s_Invalid_MAP_record_field_00459fc8);
    return 0;
  }
  thunk_FUN_00430037(&DAT_00461320);
  if ((DAT_00461320 == DAT_00459fe4) && (iVar2 = strcmp(&DAT_00461320,&DAT_00459fec), iVar2 == 0)) {
    iVar2 = FUN_00425747();
    if (iVar2 == 0) {
      return 0;
    }
  }
  else {
    if ((DAT_00461320 != DAT_00459ff4) || (iVar2 = strcmp(&DAT_00461320,&DAT_00459ff8), iVar2 != 0))
    {
      thunk_FUN_00409a25(s_Invalid_MAP_record_field_00459ffc);
      return 0;
    }
    iVar2 = FUN_00425a60();
    if (iVar2 == 0) {
      return 0;
    }
  }
  return 1;
}


/* ==== FUN_00425747 @ 00425747 ==== */

undefined4 FUN_00425747(void)

{
  uint uVar1;
  undefined4 uVar2;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  uVar1 = FUN_00426562(0);
  if (0 < (int)uVar1) {
    thunk_FUN_00409a25(s_Invalid_MAP_page_field_0045a018);
    return 0;
  }
  DAT_00461d68 = &DAT_00461320;
  if (DAT_00461320 == ',') {
    local_10 = DAT_00457bc4;
  }
  else {
    local_10 = thunk_FUN_0040a4ae();
    if (local_10 == -1) {
      return 0;
    }
    if ((local_10 < 1) || (0x200 < local_10)) {
      thunk_FUN_00409a25(s_Invalid_page_width_specified_0045a030);
      return 0;
    }
  }
  if (*DAT_00461d68 == ',') {
    DAT_00461d68 = DAT_00461d68 + 1;
  }
  if (*DAT_00461d68 == '\0') {
    local_c = DAT_00457bd4;
    local_14 = DAT_00457bdc;
    local_18 = DAT_00457be0;
    local_8 = DAT_00457bc8 + -1;
  }
  else {
    if (*DAT_00461d68 == ',') {
      local_c = DAT_00457bd4;
    }
    else {
      local_c = thunk_FUN_0040a4ae();
      if (local_c == -1) {
        return 0;
      }
      if ((local_c < 10) || (0x200 < local_c)) {
        thunk_FUN_00409a25(s_Invalid_page_length_specified_0045a050);
        return 0;
      }
    }
    if (*DAT_00461d68 == ',') {
      DAT_00461d68 = DAT_00461d68 + 1;
    }
    if (*DAT_00461d68 == '\0') {
      local_14 = DAT_00457bdc;
      local_18 = DAT_00457be0;
      local_8 = DAT_00457bc8 + -1;
    }
    else {
      if (*DAT_00461d68 == ',') {
        local_14 = DAT_00457bdc;
      }
      else {
        local_14 = thunk_FUN_0040a4ae();
        if (local_14 == -1) {
          return 0;
        }
      }
      if (*DAT_00461d68 == ',') {
        DAT_00461d68 = DAT_00461d68 + 1;
      }
      if (*DAT_00461d68 == '\0') {
        local_18 = local_c - DAT_00457bd0;
        local_8 = DAT_00457bc8 + -1;
      }
      else {
        if (*DAT_00461d68 == ',') {
          local_18 = local_c - DAT_00457bd0;
          if (local_18 < 0) {
            thunk_FUN_00409a25(s_Page_length_too_small_to_allow_d_0045a070);
            return 0;
          }
        }
        else {
          local_18 = thunk_FUN_0040a4ae();
          if (local_18 == -1) {
            return 0;
          }
        }
        if (*DAT_00461d68 == ',') {
          DAT_00461d68 = DAT_00461d68 + 1;
        }
        if (*DAT_00461d68 == '\0') {
          local_8 = DAT_00457bc8 + -1;
        }
        else {
          local_8 = thunk_FUN_0040a4ae();
          if (local_8 == -1) {
            return 0;
          }
          if (*DAT_00461d68 != '\0') {
            thunk_FUN_00409a25(s_Extra_characters_beyond_expressi_0045a0a8);
            return 0;
          }
        }
      }
    }
  }
  if (local_8 < local_10) {
    if (local_c + -10 < local_14 + local_18) {
      thunk_FUN_00409a25(s_Page_length_too_small_for_specif_0045a0ec);
      uVar2 = 0;
    }
    else {
      DAT_00457bc4 = local_10;
      DAT_00457bd4 = local_c;
      DAT_00457bdc = local_14;
      DAT_00457be0 = local_18;
      DAT_00457bd0 = local_c - local_18;
      DAT_00457bc8 = local_8 + 1;
      uVar2 = 1;
    }
  }
  else {
    thunk_FUN_00409a25(s_Left_margin_exceeds_page_width_0045a0cc);
    uVar2 = 0;
  }
  return uVar2;
}


/* ==== FUN_00425a60 @ 00425a60 ==== */

undefined4 FUN_00425a60(void)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined3 extraout_var;
  char local_220;
  uint local_21c;
  char local_210 [512];
  char *local_10;
  long local_c;
  char *local_8;
  undefined1 *puVar5;
  
  local_c = 0;
  uVar2 = FUN_00426562(0);
  if ((int)uVar2 < 1) {
    local_10 = &DAT_00461320;
    while (*local_10 != '\0') {
      local_8 = local_210;
      for (; (*local_10 != '\0' && (*local_10 != ',')); local_10 = local_10 + 1) {
        if (__mb_cur_max < 2) {
          local_21c = *(ushort *)(_pctype + *local_10 * 2) & 1;
        }
        else {
          local_21c = _isctype((int)*local_10,1);
        }
        if (local_21c == 0) {
          local_220 = *local_10;
        }
        else {
          iVar4 = tolower((int)*local_10);
          local_220 = (char)iVar4;
        }
        *local_8 = local_220;
        local_8 = local_8 + 1;
      }
      *local_8 = '\0';
      if (*local_10 != '\0') {
        local_10 = local_10 + 1;
      }
      cVar1 = strrchr(local_210,0x3d);
      puVar5 = (undefined1 *)CONCAT31(extraout_var,cVar1);
      if (puVar5 != (undefined1 *)0x0) {
        *puVar5 = 0;
        local_c = strtol(puVar5 + 1,(char **)0x0,0);
      }
      iVar4 = thunk_FUN_0042d8f3(local_210);
      if (iVar4 == 0) {
        thunk_FUN_00409bfd(s_Invalid_MAP_option_0045a144,local_210);
        return 0;
      }
      switch(*(undefined4 *)(iVar4 + 4)) {
      case 1:
        DAT_00457b50 = 0;
        break;
      case 2:
        DAT_00457b54 = 0;
        break;
      case 3:
        DAT_00457b5c = 0;
        break;
      case 4:
        DAT_00457b60 = 0;
        break;
      case 5:
        DAT_00457b64 = 0;
        break;
      case 6:
        DAT_00457b68 = 0;
        break;
      case 7:
        DAT_00457b4c = 0;
        break;
      case 8:
        DAT_00457b58 = 0;
        break;
      case 9:
        DAT_00457b6c = 0;
        break;
      case 10:
        DAT_00461208 = 1;
        break;
      case 0xb:
        DAT_00457b70 = 0;
        break;
      case 0xc:
        DAT_004611e0 = 1;
        DAT_004611e4 = local_c;
        break;
      default:
        thunk_FUN_004098b0(s_Map_option_select_failure_0045a158);
      }
    }
    uVar3 = 1;
  }
  else {
    thunk_FUN_00409a25(s_Invalid_MAP_option_field_0045a128);
    uVar3 = 0;
  }
  return uVar3;
}


/* ==== FUN_00425cf1 @ 00425cf1 ==== */

undefined4 __cdecl FUN_00425cf1(char *param_1)

{
  undefined4 uVar1;
  int iVar2;
  char local_24;
  uint local_20;
  char *local_1c;
  char local_18 [12];
  int local_c;
  int local_8;
  
  if (*param_1 == '\0') {
    thunk_FUN_00409a25(s_Missing_option_0045a174);
    uVar1 = 0;
  }
  else {
    while (*param_1 != '\0') {
      local_c = 0;
      local_1c = local_18;
      for (; (*param_1 != '\0' && (*param_1 != ',')); param_1 = param_1 + 1) {
        iVar2 = local_c + 1;
        if (7 < local_c) {
          local_c = iVar2;
          thunk_FUN_00409a25(s_Illegal_option_0045a184);
          return 0;
        }
        if (__mb_cur_max < 2) {
          local_20 = *(ushort *)(_pctype + *param_1 * 2) & 1;
          local_c = iVar2;
        }
        else {
          local_c = iVar2;
          local_20 = _isctype((int)*param_1,1);
        }
        if (local_20 == 0) {
          local_24 = *param_1;
        }
        else {
          iVar2 = tolower((int)*param_1);
          local_24 = (char)iVar2;
        }
        *local_1c = local_24;
        local_1c = local_1c + 1;
      }
      *local_1c = '\0';
      if (local_18[0] == '\0') {
        thunk_FUN_00409a25(s_Missing_option_0045a194);
        return 0;
      }
      local_8 = thunk_FUN_0042d916(local_18);
      if (local_8 == 0) {
        thunk_FUN_00409a25(s_Illegal_option_0045a1a4);
        return 0;
      }
      switch(*(undefined4 *)(local_8 + 4)) {
      case 1:
        DAT_00457b78 = 1;
        break;
      case 2:
        DAT_00457b78 = 0;
        break;
      case 3:
        DAT_00457b7c = 1;
        break;
      case 4:
        DAT_00457b7c = 0;
        break;
      case 5:
        DAT_0046122c = 1;
        break;
      case 6:
        DAT_0046122c = 0;
        break;
      case 7:
        DAT_00461228 = 1;
        break;
      case 8:
        DAT_00461228 = 0;
        break;
      case 9:
        DAT_00461230 = 1;
        break;
      case 10:
        DAT_00461230 = 0;
        break;
      case 0xb:
        DAT_00461234 = 1;
        break;
      case 0xc:
        DAT_00461234 = 0;
        break;
      case 0xd:
        DAT_00461238 = 1;
        break;
      case 0xe:
        DAT_00461238 = 0;
        break;
      case 0xf:
        DAT_0046123c = 1;
        break;
      case 0x10:
        DAT_00457b80 = 1;
        break;
      case 0x11:
        DAT_00457b80 = 0;
        break;
      case 0x12:
        DAT_00461240 = 1;
        break;
      case 0x13:
        DAT_00461240 = 0;
        break;
      case 0x14:
        DAT_00461244 = 1;
        break;
      case 0x15:
        DAT_00461244 = 0;
        break;
      case 0x16:
        DAT_00457b94 = 1;
        break;
      case 0x17:
        DAT_00457b94 = 0;
        break;
      case 0x18:
        if ((DAT_00461f44 == 3) || (DAT_00461f44 == 5)) {
          DAT_00461288 = 1;
        }
        break;
      case 0x19:
        if (DAT_00461f44 != 5) {
          DAT_00461288 = 0;
        }
        break;
      case 0x1a:
        DAT_00457b84 = 1;
        break;
      case 0x1b:
        DAT_00457b84 = 0;
        break;
      case 0x1c:
        DAT_0046128c = 1;
        break;
      case 0x1d:
        DAT_00461290 = 1;
        break;
      case 0x1e:
        DAT_004611e8 = 1;
        break;
      case 0x1f:
        DAT_004611e8 = 0;
        break;
      case 0x20:
        DAT_004611d8 = 1;
        break;
      case 0x21:
        DAT_004611d8 = 0;
        break;
      default:
        thunk_FUN_004098b0(s_Option_select_error_0045a1b4);
      }
      if (*param_1 != '\0') {
        param_1 = param_1 + 1;
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}


/* ==== FUN_0042609f @ 0042609f ==== */

undefined4 FUN_0042609f(void)

{
  uint uVar1;
  undefined4 uVar2;
  char *pcVar3;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int extraout_EAX_03;
  int extraout_EAX_04;
  undefined4 *puVar4;
  int local_210;
  undefined4 *local_20c;
  char local_208 [516];
  
  uVar1 = FUN_00426562(0);
  if (uVar1 == 0) {
    pcVar3 = thunk_FUN_0042e4df(&DAT_00461320,local_208);
    if (pcVar3 == (char *)0x0) {
      thunk_FUN_00409a25(s_Missing_filename_0045a1e4);
      uVar2 = 0;
    }
    else {
      strcpy(&DAT_00461528,local_208);
      fopen(&DAT_00461528,&DAT_0045a1f8);
      local_210 = extraout_EAX;
      if (extraout_EAX == 0) {
        for (local_20c = DAT_00461f10; local_20c != (undefined4 *)0x0;
            local_20c = (undefined4 *)local_20c[1]) {
          strcpy(&DAT_00461528,(char *)*local_20c);
          strcat(&DAT_00461528,local_208);
          fopen(&DAT_00461528,&DAT_0045a1fc);
          local_210 = extraout_EAX_00;
          if (extraout_EAX_00 != 0) break;
        }
      }
      if (local_210 == 0) {
        strcpy(&DAT_00461528,local_208);
        thunk_FUN_004032e9((uint *)&DAT_0045a200);
        fopen(&DAT_00461528,&DAT_0045a208);
        local_210 = extraout_EAX_01;
        if (extraout_EAX_01 == 0) {
          for (local_20c = DAT_00461f10; local_20c != (undefined4 *)0x0;
              local_20c = (undefined4 *)local_20c[1]) {
            strcpy(&DAT_00461528,(char *)*local_20c);
            strcat(&DAT_00461528,local_208);
            thunk_FUN_004032e9((uint *)&DAT_0045a20c);
            fopen(&DAT_00461528,&DAT_0045a214);
            local_210 = extraout_EAX_02;
            if (extraout_EAX_02 != 0) break;
          }
        }
      }
      if (local_210 == 0) {
        strcpy(&DAT_00461528,local_208);
        thunk_FUN_004032e9((uint *)&DAT_0045a218);
        fopen(&DAT_00461528,&DAT_0045a220);
        local_210 = extraout_EAX_03;
        if (extraout_EAX_03 == 0) {
          for (local_20c = DAT_00461f10; local_20c != (undefined4 *)0x0;
              local_20c = (undefined4 *)local_20c[1]) {
            strcpy(&DAT_00461528,(char *)*local_20c);
            strcat(&DAT_00461528,local_208);
            thunk_FUN_004032e9((uint *)&DAT_0045a224);
            fopen(&DAT_00461528,&DAT_0045a22c);
            local_210 = extraout_EAX_04;
            if (extraout_EAX_04 != 0) break;
          }
        }
      }
      if (local_210 == 0) {
        thunk_FUN_00409bfd(s_Cannot_open_include_file_0045a250,local_208);
        uVar2 = 0;
      }
      else {
        if (DAT_0046125c != '\0') {
          fprintf(PTR_DAT_00457c08,s__s__Opening_include_file__s_0045a230,PTR_s_dsplnk_00457ed0,
                  &DAT_00461528);
        }
        puVar4 = (undefined4 *)thunk_FUN_0042e170(0x14);
        *puVar4 = *DAT_00461dbc;
        puVar4[1] = DAT_00461db4;
        puVar4[2] = DAT_00457bfc;
        puVar4[3] = DAT_00461318;
        puVar4[4] = DAT_00461dc0;
        DAT_00457bfc = DAT_00457bfc + 1;
        DAT_00461db4 = local_210;
        DAT_00461dc0 = puVar4;
        *DAT_00461dbc = &DAT_00461528;
        DAT_00461318 = 1;
        uVar2 = 1;
      }
    }
  }
  else {
    thunk_FUN_00409a25(s_Invalid_include_file_name_0045a1c8);
    uVar2 = 0;
  }
  return uVar2;
}


