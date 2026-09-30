/* listing: 35 functions from ASM56000 */

/* ==== FUN_0041b8bc @ 0041b8bc ==== */

int FUN_0041b8bc(void)

{
  int local_28;
  uint local_24;
  int local_20;
  uint local_1c;
  int local_18;
  uint local_14;
  int local_10;
  uint local_c;
  char *local_8;
  
  DAT_00463c10 = (uint)(DAT_00463c10 == 0);
  if (DAT_00463c10 == 0) {
    if (DAT_00463c14 != 0) {
      FUN_0041bb8d();
      DAT_00463c14 = 0;
    }
    return 0;
  }
  if (*PTR_DAT_0044f81c == '\0') {
    return DAT_00463c14;
  }
  if (*PTR_DAT_0044f820 == '\0') {
    return DAT_00463c14;
  }
  if (*PTR_DAT_0044f81c == '#') {
    if (__mb_cur_max < 2) {
      local_c = *(ushort *)(_pctype + (char)PTR_DAT_0044f820[2] * 2) & 1;
    }
    else {
      local_c = _isctype((int)(char)PTR_DAT_0044f820[2],1);
    }
    if (local_c == 0) {
      local_10 = (int)(char)PTR_DAT_0044f820[2];
    }
    else {
      local_10 = tolower((int)(char)PTR_DAT_0044f820[2]);
    }
    if (local_10 != 0x78) goto LAB_0041b998;
  }
  else {
LAB_0041b998:
    if (*PTR_DAT_0044f820 != '#') goto LAB_0041ba23;
    if (__mb_cur_max < 2) {
      local_14 = *(ushort *)(_pctype + (char)PTR_DAT_0044f81c[2] * 2) & 1;
    }
    else {
      local_14 = _isctype((int)(char)PTR_DAT_0044f81c[2],1);
    }
    if (local_14 == 0) {
      local_18 = (int)(char)PTR_DAT_0044f81c[2];
    }
    else {
      local_18 = tolower((int)(char)PTR_DAT_0044f81c[2]);
    }
    if (local_18 != 0x79) goto LAB_0041ba23;
  }
  FUN_0041bb8d();
  DAT_00463c14 = 1;
LAB_0041ba23:
  if (DAT_00463c14 == 0) {
    for (local_8 = PTR_DAT_0044f81c; *local_8 != '\0'; local_8 = local_8 + 1) {
      if (__mb_cur_max < 2) {
        local_1c = *(ushort *)(_pctype + *local_8 * 2) & 1;
      }
      else {
        local_1c = _isctype((int)*local_8,1);
      }
      if (local_1c == 0) {
        local_20 = (int)*local_8;
      }
      else {
        local_20 = tolower((int)*local_8);
      }
      if ((local_20 == 0x79) && (local_8[1] == ':')) {
        FUN_0041bb8d();
        DAT_00463c14 = 1;
        break;
      }
    }
  }
  if (DAT_00463c14 == 0) {
    for (local_8 = PTR_DAT_0044f820; *local_8 != '\0'; local_8 = local_8 + 1) {
      if (__mb_cur_max < 2) {
        local_24 = *(ushort *)(_pctype + *local_8 * 2) & 1;
      }
      else {
        local_24 = _isctype((int)*local_8,1);
      }
      if (local_24 == 0) {
        local_28 = (int)*local_8;
      }
      else {
        local_28 = tolower((int)*local_8);
      }
      if ((local_28 == 0x78) && (local_8[1] == ':')) {
        FUN_0041bb8d();
        DAT_00463c14 = 1;
        return 1;
      }
    }
  }
  return DAT_00463c14;
}


/* ==== FUN_0041bb8d @ 0041bb8d ==== */

void FUN_0041bb8d(void)

{
  undefined *puVar1;
  
  puVar1 = PTR_DAT_0044f81c;
  PTR_DAT_0044f81c = PTR_DAT_0044f820;
  PTR_DAT_0044f820 = puVar1;
  return;
}


/* ==== FUN_0041bbb2 @ 0041bbb2 ==== */

void FUN_0041bbb2(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 *puVar11;
  char local_208 [516];
  
  if (DAT_0045da3c == 0) {
    if ((*PTR_DAT_0044f810 != '\0') &&
       (puVar11 = FUN_00438441((uint *)PTR_DAT_0044f810,2), puVar11 != (undefined4 *)0x0)) {
      puVar11[4] = *DAT_0045f8c0 + 1;
    }
    if (DAT_0045ea98 == '\0') {
      FUN_004133a9((uint *)s_Contents_of_register_written_in_p_00454f58);
    }
    uVar8 = DAT_0045f860;
    uVar7 = DAT_0045da40;
    puVar6 = PTR_DAT_0044f824;
    puVar5 = PTR_DAT_0044f820;
    puVar4 = PTR_DAT_0044f81c;
    puVar3 = PTR_DAT_0044f818;
    puVar2 = PTR_DAT_0044f814;
    puVar1 = PTR_DAT_0044f810;
    strcpy(local_208,&DAT_0045ec08);
    uVar10 = DAT_0045f92c;
    uVar9 = DAT_0045f928;
    strcpy(&DAT_0045ec08,&DAT_00454fb8);
    DAT_0045eacc = 1;
    FUN_0041a4bc();
    FUN_0041af7e(0,0);
    FUN_0041bdca('p');
    DAT_0045eacc = 0;
    strcpy(&DAT_0045ec08,local_208);
    DAT_0045da40 = uVar7;
    FUN_0041a4bc();
    DAT_0045f8c4 = *DAT_0045f8c0;
    DAT_0045f8d0 = *DAT_0045f8cc;
    DAT_0045eb80 = DAT_0045eb80 + 1;
    DAT_0045f924 = 0;
    PTR_DAT_0044f810 = puVar1;
    PTR_DAT_0044f814 = puVar2;
    PTR_DAT_0044f818 = puVar3;
    PTR_DAT_0044f81c = puVar4;
    PTR_DAT_0044f820 = puVar5;
    PTR_DAT_0044f824 = puVar6;
    DAT_0045f860 = uVar8;
    DAT_0045f928 = uVar9;
    DAT_0045f92c = uVar10;
  }
  return;
}


/* ==== FUN_0041bdc0 @ 0041bdc0 ==== */

void FUN_0041bdc0(void)

{
  FUN_0041edc3();
  return;
}


/* ==== FUN_0041bdca @ 0041bdca ==== */

void __cdecl FUN_0041bdca(char param_1)

{
  bool bVar1;
  int va0;
  char cVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  int local_38;
  int local_30;
  char local_18;
  int local_8;
  
  local_18 = ' ';
  local_8 = 0;
  if ((((DAT_0045f8a0 == 0x1c) || (DAT_0045f8b0 == 0x1c)) || (DAT_0045f8a0 == 0x11d)) ||
     (DAT_0045f8b0 == 0x11d)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (DAT_0045f8a0 != DAT_0045f8b0)) {
    local_38 = 4;
  }
  else {
    local_38 = 0;
  }
  iVar4 = (-(uint)bVar1 & 6) + 0x1a;
  iVar6 = (-(uint)bVar1 & 4) + 8;
  if (((1 < DAT_0045f8fc) && (DAT_0045ea34 == '\0')) &&
     ((0 < DAT_0045ebec && (DAT_0045ea54 == '\0')))) {
    if ((DAT_0045ea58 == '\0') && (DAT_0045fb6c != 0)) {
      if (DAT_0045ea30 == '\0') {
        return;
      }
      local_18 = '+';
    }
    if ((DAT_0044f78c == '\0') && (DAT_0045ea6c != '\0')) {
      DAT_0045ea6c = '\0';
      strcpy(&DAT_0045ec08,&DAT_0045f018);
      FUN_0041a4bc();
    }
    if (((*PTR_DAT_0044f810 != '\0') && (*PTR_DAT_0044f814 != '\0')) &&
       (uVar5 = strlen(PTR_DAT_0044f810), va0 = DAT_0045eb80, DAT_0044f7f4 < uVar5)) {
      DAT_0045eb80 = DAT_0045eb80 + 1;
      sprintf(&DAT_0045f220,s___5lu_c_c_00454ff4,va0,(int)param_1,(int)local_18);
      FUN_0041c9cf(&DAT_0045f220);
      local_30 = iVar4;
      if (DAT_0045f8c0 != DAT_0045f8cc) {
        local_30 = iVar4 + iVar6;
      }
      if (DAT_0045ea38 != '\0') {
        local_30 = local_30 + 0x10;
      }
      FUN_0041cb2d(local_30);
      FUN_0041c9cf(PTR_DAT_0044f810);
      if (DAT_0045eac0 != '\0') {
        FUN_0041c9cf(&DAT_00455000);
      }
      FUN_0041cb65();
      *PTR_DAT_0044f810 = 0;
    }
    sprintf(&DAT_0045f220,s___5lu_c_c_00455004,DAT_0045eb80,(int)param_1,(int)local_18);
    FUN_0041c9cf(&DAT_0045f220);
    local_30 = 10;
    FUN_0041cb2d(10);
    if (DAT_0045f8c0 != DAT_0045f8cc) {
      local_30 = (-(uint)bVar1 & 4) + 0x11;
    }
    if (DAT_0045f91c == 0) {
      if (DAT_0045f918 == 0) {
        if (DAT_0045f920 != 0) {
          local_8 = (local_30 + iVar6) - local_38;
          if (DAT_0045f8c0 == DAT_0045f8cc) {
            cVar2 = FUN_0043a6c5(DAT_0045f8a0);
            if ((DAT_0045f8a0 == 0x1c) || (DAT_0045f8a0 == 0x11d)) {
              local_40 = 8;
            }
            else {
              local_40 = 4;
            }
            sprintf(&DAT_0045f220,s__c__0_lX_00455018,(int)cVar2,local_40,
                    DAT_0045f8c4 & DAT_0044f91c);
            FUN_0041c9cf(&DAT_0045f220);
          }
          else {
            cVar2 = FUN_0043a6c5(DAT_0045f8a0);
            cVar3 = FUN_0043a6c5(DAT_0045f8b0);
            if ((DAT_0045f8a0 == 0x1c) || (DAT_0045f8a0 == 0x11d)) {
              local_44 = 8;
            }
            else {
              local_44 = 4;
            }
            sprintf(&DAT_0045f220,s__c__0_lX_00455024,(int)cVar2,local_44,
                    DAT_0045f8c4 & DAT_0044f91c);
            FUN_0041c9cf(&DAT_0045f220);
            if ((DAT_0045f8b0 == 0x1c) || (DAT_0045f8b0 == 0x11d)) {
              local_48 = 8;
            }
            else {
              local_48 = 4;
            }
            sprintf(&DAT_0045f220,s__c__0_lX_00455030,(int)cVar3,local_48,
                    DAT_0045f8d0 & DAT_0044f920);
            FUN_0041c9cf(&DAT_0045f220);
          }
          if (DAT_0045f924 != 0) {
            sprintf(&DAT_0045f220,s__06lX_0044e098,DAT_00465480 & 0xffffff);
            FUN_0041c9cf(&DAT_0045f220);
          }
        }
      }
      else {
        local_8 = local_30 + 1;
        sprintf(&DAT_0045f220,s__06lX_0044e098,DAT_00465480 & 0xffffff);
        FUN_0041c9cf(&DAT_0045f220);
      }
    }
    else {
      FUN_0043c0ea((uint *)&DAT_0045f220,(uint *)s____6E_00455010,DAT_00465a80,DAT_00465a84);
      FUN_0041c9cf(&DAT_0045f220);
    }
    local_30 = local_30 + -10 + iVar4;
    if (DAT_0045ea38 != '\0') {
      FUN_0041cb2d(local_30);
      local_30 = local_30 + 0x10;
      if (DAT_0045f928 != 0) {
        if (DAT_0045f92c == 0) {
          sprintf(&DAT_0045f220,s___1d____8ld__00455050,DAT_0045f928,DAT_0045f930);
        }
        else {
          sprintf(&DAT_0045f220,s___1d__1d____6ld__0045503c,DAT_0045f928 - DAT_0045f92c,DAT_0045f92c
                  ,DAT_0045f930);
        }
        FUN_0041c9cf(&DAT_0045f220);
      }
    }
    if (DAT_0045eac4 != '\0') {
      FUN_0041cb2d(local_30);
      local_30 = local_30 + 8;
      if ((DAT_0045eba8 != 0) || (DAT_0045eba4 != 0)) {
        if ((DAT_0045eba8 == 0) || (DAT_0045eba4 == 0)) {
          if (DAT_0045eba8 == 0) {
            sprintf(&DAT_0045f220,s__2d_00455070,DAT_0045eba4);
          }
          else {
            sprintf(&DAT_0045f220,&DAT_0045506c,*(undefined4 *)(PTR_DAT_0044f978 + 8));
          }
        }
        else {
          sprintf(&DAT_0045f220,s__2d__2d_00455060,*(undefined4 *)(PTR_DAT_0044f978 + 8),
                  DAT_0045eba4);
        }
        FUN_0041c9cf(&DAT_0045f220);
      }
    }
    if ((DAT_0044f7a8 == '\0') && (DAT_0045ec08 != '\0')) {
      FUN_0041cb2d(local_30);
      FUN_0041c9cf(&DAT_0045ec08);
      FUN_0041c8fd(param_1,local_8,local_30);
      FUN_0041cb65();
    }
    else {
      if (*PTR_DAT_0044f810 != '\0') {
        FUN_0041cb2d(local_30);
        FUN_0041c9cf(PTR_DAT_0044f810);
        if (DAT_0045eac0 != '\0') {
          FUN_0041c9cf(&DAT_00455078);
        }
      }
      if ((((((DAT_0045ea64 == '\0') || (DAT_0045ea0c != '\0')) || (*PTR_DAT_0044f810 != '\0')) ||
           ((*PTR_DAT_0044f814 != '\0' || (*PTR_DAT_0044f818 != '\0')))) ||
          (*PTR_DAT_0044f81c != '\0')) || (*PTR_DAT_0044f820 != '\0')) {
        local_30 = local_30 + DAT_0044f7f4;
      }
      iVar4 = local_30;
      if (*PTR_DAT_0044f814 != '\0') {
        FUN_0041cb2d(local_30);
        FUN_0041c9cf(PTR_DAT_0044f814);
      }
      if (((DAT_0045ea64 == '\0') || (DAT_0045ea0c != '\0')) ||
         ((*PTR_DAT_0044f814 != '\0' ||
          (((*PTR_DAT_0044f818 != '\0' || (*PTR_DAT_0044f81c != '\0')) ||
           (*PTR_DAT_0044f820 != '\0')))))) {
        local_30 = local_30 + DAT_0044f7f8;
      }
      if (*PTR_DAT_0044f818 != '\0') {
        FUN_0041cb2d(local_30);
        FUN_0041c9cf(PTR_DAT_0044f818);
      }
      if (((DAT_0045ea64 == '\0') || (DAT_0045ea0c != '\0')) ||
         ((*PTR_DAT_0044f818 != '\0' || ((*PTR_DAT_0044f81c != '\0' || (*PTR_DAT_0044f820 != '\0')))
          ))) {
        local_30 = local_30 + DAT_0044f7fc;
      }
      if (*PTR_DAT_0044f81c != '\0') {
        FUN_0041cb2d(local_30);
        FUN_0041c9cf(PTR_DAT_0044f81c);
      }
      if ((((DAT_0045ea64 == '\0') || (DAT_0045ea0c != '\0')) || (*PTR_DAT_0044f81c != '\0')) ||
         (*PTR_DAT_0044f820 != '\0')) {
        local_30 = local_30 + DAT_0044f800;
      }
      if (*PTR_DAT_0044f820 != '\0') {
        FUN_0041cb2d(local_30);
        FUN_0041c9cf(PTR_DAT_0044f820);
      }
      if (((DAT_0045ea64 == '\0') || (DAT_0045ea0c != '\0')) || (*PTR_DAT_0044f820 != '\0')) {
        local_30 = local_30 + DAT_0044f804;
      }
      if (*PTR_DAT_0044f824 != '\0') {
        if (DAT_0045ea0c == '\0') {
          FUN_0041cb2d(local_30);
          FUN_0041c9cf(PTR_DAT_0044f824);
        }
        else if (DAT_0045f924 < 2) {
          FUN_0041cb65();
          FUN_0041cb2d(iVar4);
          FUN_0041c9cf(PTR_DAT_0044f824);
        }
      }
      if (1 < DAT_0045f924) {
        FUN_0041c8fd(param_1,local_8,iVar4);
      }
      FUN_0041cb65();
    }
  }
  return;
}


/* ==== FUN_0041c742 @ 0041c742 ==== */

void FUN_0041c742(void)

{
  byte bVar1;
  char in_stack_00000004;
  int local_18;
  char local_c;
  
  local_c = ' ';
  if ((((DAT_0045f8a0 == 0x1c) || (DAT_0045f8b0 == 0x1c)) || (DAT_0045f8a0 == 0x11d)) ||
     (DAT_0045f8b0 == 0x11d)) {
    bVar1 = 1;
  }
  else {
    bVar1 = 0;
  }
  local_18 = (-(uint)bVar1 & 6) + 0x1a;
  if ((((1 < DAT_0045f8fc) && (DAT_0045ea34 == '\0')) &&
      ((0 < DAT_0045ebec && (DAT_0045ea54 == '\0')))) &&
     ((DAT_0045ec08 != ';' || (DAT_0045ec09 != ';')))) {
    if ((DAT_0045ea58 == '\0') && (DAT_0045fb6c != 0)) {
      if (DAT_0045ea30 == '\0') {
        return;
      }
      local_c = '+';
    }
    if ((DAT_0044f78c == '\0') && (DAT_0045ea6c != '\0')) {
      DAT_0045ea6c = '\0';
      strcpy(&DAT_0045ec08,&DAT_0045f018);
      FUN_0041a4bc();
    }
    sprintf(&DAT_0045f220,s___5lu_c_c_0045507c,DAT_0045eb80,(int)in_stack_00000004,(int)local_c);
    FUN_0041c9cf(&DAT_0045f220);
    if (DAT_0045ec08 != '\0') {
      if (DAT_0045f8c0 != DAT_0045f8cc) {
        local_18 = (-(uint)bVar1 & 6) + (-(uint)bVar1 & 4) + 0x21;
      }
      if (DAT_0045ea38 != '\0') {
        local_18 = local_18 + 0x10;
      }
      if (DAT_0045eac4 != '\0') {
        local_18 = local_18 + 8;
      }
      FUN_0041cb2d(local_18);
      FUN_0041c9cf(&DAT_0045ec08);
    }
    FUN_0041cb65();
  }
  return;
}


/* ==== FUN_0041c8fd @ 0041c8fd ==== */

void __cdecl FUN_0041c8fd(char param_1,int param_2,int param_3)

{
  int local_8;
  
  for (local_8 = 1; local_8 < DAT_0045f924; local_8 = local_8 + 1) {
    FUN_0041cb65();
    if (param_1 == 'd') {
      sprintf(&DAT_0045f220,s__c_00455088,100);
      FUN_0041c9cf(&DAT_0045f220);
    }
    FUN_0041cb2d(param_2);
    sprintf(&DAT_0045f220,s__06lX_0044e098,(&DAT_00465480)[local_8] & 0xffffff);
    FUN_0041c9cf(&DAT_0045f220);
    if (((local_8 == 1) && (DAT_0045ea0c != '\0')) && (DAT_0044f7a8 != '\0')) {
      FUN_0041cb2d(param_3);
      FUN_0041c9cf(PTR_DAT_0044f824);
    }
  }
  return;
}


/* ==== FUN_0041c9cf @ 0041c9cf ==== */

void __cdecl FUN_0041c9cf(char *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint local_c;
  
  iVar2 = DAT_0044f7d8;
  if (DAT_0045ea9c == '\0') {
    DAT_0044f7d8 = iVar2;
    if ((DAT_0044f7a0 != '\0') && (DAT_0045f8fc == 2)) {
      DAT_0044f7a0 = '\0';
      if (DAT_0045ea34 == '\0') {
        FUN_0041ce8d();
        DAT_0044f7d8 = iVar2;
      }
      else {
        FUN_0041cc4d();
        DAT_0044f7d8 = iVar2;
      }
    }
    for (; iVar2 = DAT_0044f7d8, *param_1 != '\0'; param_1 = param_1 + 1) {
      iVar3 = DAT_0044f7d4 + 1;
      bVar1 = DAT_0044f7dc < DAT_0044f7d4;
      DAT_0044f7d4 = iVar3;
      if ((bVar1) && (*param_1 != '\n')) {
        FUN_0041cb65();
      }
      DAT_0044f7d8 = iVar2 + 1;
      if (*param_1 == '\n') {
        FUN_0041cb65();
      }
      else {
        DAT_0045fcac[1] = DAT_0045fcac[1] + -1;
        if (DAT_0045fcac[1] < 0) {
          local_c = _flsbuf((int)*param_1,DAT_0045fcac);
        }
        else {
          *(char *)*DAT_0045fcac = *param_1;
          local_c = (uint)*(byte *)*DAT_0045fcac;
          *DAT_0045fcac = *DAT_0045fcac + 1;
        }
        if (local_c == 0xffffffff) {
          FUN_00412fa0((uint *)s_Cannot_write_string_to_listing_f_00455094);
        }
      }
    }
  }
  return;
}


/* ==== FUN_0041cb2d @ 0041cb2d ==== */

void __cdecl FUN_0041cb2d(int param_1)

{
  if (DAT_0044f7d8 < param_1) {
    while (DAT_0044f7d8 < param_1) {
      FUN_0041c9cf(&DAT_004550bc);
    }
  }
  else {
    FUN_0041c9cf(&DAT_004550b8);
  }
  return;
}


/* ==== FUN_0041cb65 @ 0041cb65 ==== */

void FUN_0041cb65(void)

{
  int local_8;
  
  if (DAT_0045ea9c == '\0') {
    if ((DAT_0044f7ec == 0) || (DAT_0044f7e4 < DAT_0044f7ec)) {
      DAT_0045fcac[1] = DAT_0045fcac[1] + -1;
      if (DAT_0045fcac[1] < 0) {
        local_8 = _flsbuf(10,DAT_0045fcac);
      }
      else {
        *(undefined1 *)*DAT_0045fcac = 10;
        local_8 = 10;
        *DAT_0045fcac = *DAT_0045fcac + 1;
      }
      if (local_8 == -1) {
        FUN_00412fa0((uint *)s_Cannot_write_new_line_to_listing_004550c0);
      }
      DAT_0044f7e4 = DAT_0044f7e4 + 1;
      DAT_0044f7e8 = DAT_0044f7e8 + 1;
      DAT_0044f7d4 = 1;
      DAT_0044f7d8 = 1;
    }
    else {
      FUN_0041cced(1);
    }
    FUN_0041cc4d();
  }
  return;
}


/* ==== FUN_0041cc4d @ 0041cc4d ==== */

void FUN_0041cc4d(void)

{
  int local_8;
  
  for (; DAT_0044f7d4 < DAT_0044f7e0; DAT_0044f7d4 = DAT_0044f7d4 + 1) {
    DAT_0045fcac[1] = DAT_0045fcac[1] + -1;
    if (DAT_0045fcac[1] < 0) {
      local_8 = _flsbuf(0x20,DAT_0045fcac);
    }
    else {
      *(undefined1 *)*DAT_0045fcac = 0x20;
      local_8 = 0x20;
      *DAT_0045fcac = *DAT_0045fcac + 1;
    }
    if (local_8 == -1) {
      FUN_00412fa0((uint *)s_Cannot_write_left_margin_to_list_004550e8);
    }
  }
  return;
}


/* ==== FUN_0041cced @ 0041cced ==== */

void __cdecl FUN_0041cced(int param_1)

{
  int local_c;
  int local_8;
  
  if (DAT_0045ea9c == '\0') {
    if (DAT_0045ea34 == '\0') {
      if (DAT_0044f7a0 != '\0') {
        DAT_0044f7a0 = '\0';
        FUN_0041ce8d();
      }
      if (DAT_0045eb2c == '\0') {
        for (; DAT_0044f7e4 <= DAT_0044f7f0; DAT_0044f7e4 = DAT_0044f7e4 + 1) {
          DAT_0045fcac[1] = DAT_0045fcac[1] + -1;
          if (DAT_0045fcac[1] < 0) {
            local_c = _flsbuf(10,DAT_0045fcac);
          }
          else {
            *(undefined1 *)*DAT_0045fcac = 10;
            local_c = 10;
            *DAT_0045fcac = *DAT_0045fcac + 1;
          }
          if (local_c == -1) {
            FUN_00412fa0((uint *)s_Cannot_write_new_page_to_listing_0045513c);
          }
          DAT_0044f7e8 = DAT_0044f7e8 + 1;
        }
      }
      else {
        DAT_0045fcac[1] = DAT_0045fcac[1] + -1;
        if (DAT_0045fcac[1] < 0) {
          local_8 = _flsbuf(0xc,DAT_0045fcac);
        }
        else {
          *(undefined1 *)*DAT_0045fcac = 0xc;
          local_8 = 0xc;
          *DAT_0045fcac = *DAT_0045fcac + 1;
        }
        if (local_8 == -1) {
          FUN_00412fa0((uint *)s_Cannot_write_form_feed_to_listin_00455114);
        }
      }
    }
    if (param_1 != 0) {
      DAT_0044f7d4 = 1;
      DAT_0044f7d8 = 1;
      DAT_0044f7e4 = 1;
      DAT_0045ebf0 = DAT_0045ebf0 + 1;
      FUN_0041ce8d();
    }
  }
  return;
}


/* ==== FUN_0041ce8d @ 0041ce8d ==== */

void FUN_0041ce8d(void)

{
  int local_8;
  
  if ((DAT_0045ea34 == '\0') && (DAT_0044f7f0 != 0)) {
    for (DAT_0044f7e4 = 1; DAT_0044f7e4 <= DAT_0045ebf4; DAT_0044f7e4 = DAT_0044f7e4 + 1) {
      DAT_0045fcac[1] = DAT_0045fcac[1] + -1;
      if (DAT_0045fcac[1] < 0) {
        local_8 = _flsbuf(10,DAT_0045fcac);
      }
      else {
        *(undefined1 *)*DAT_0045fcac = 10;
        local_8 = 10;
        *DAT_0045fcac = *DAT_0045fcac + 1;
      }
      if (local_8 == -1) {
        FUN_00412fa0((uint *)s_Cannot_write_page_header_to_list_00455164);
      }
      DAT_0044f7e8 = DAT_0044f7e8 + 1;
    }
    FUN_0041cf64();
  }
  return;
}


/* ==== FUN_0041cf64 @ 0041cf64 ==== */

void FUN_0041cf64(void)

{
  char *local_24;
  char *local_20;
  char *local_1c;
  char *local_18;
  char local_14 [16];
  
  if (DAT_0044f7b8 != '\0') {
    FUN_0041cc4d();
    FUN_0041c9cf(s_Motorola_00455190);
    FUN_0041c9cf(&DAT_0045519c);
    FUN_0041c9cf(s_DSP56000_0044e068);
    FUN_0041c9cf(&DAT_004551a0);
    FUN_0041c9cf(s_Assembler_0044f9a8);
    FUN_0041c9cf(&DAT_004551a4);
    FUN_0041c9cf(s_Version_004551a8);
    FUN_0041c9cf(&DAT_004551b0);
    if (DAT_0045eb50 == '\0') {
      local_18 = s_6_3_0_0044f9b8;
    }
    else {
      local_18 = &DAT_004551b4;
    }
    FUN_0041d11c(local_18);
    FUN_0041c9cf(&DAT_004551bc);
    if (DAT_0045eb50 == '\0') {
      local_1c = &DAT_0045f838;
    }
    else {
      local_1c = s_00_00_00_004551c0;
    }
    FUN_0041d11c(local_1c);
    FUN_0041c9cf(&DAT_004551cc);
    if (DAT_0045eb50 == '\0') {
      local_20 = &DAT_0045f848;
    }
    else {
      local_20 = s_00_00_00_004551d0;
    }
    FUN_0041d11c(local_20);
    FUN_0041c9cf(&DAT_004551dc);
    if (DAT_0045eb50 == '\0') {
      local_24 = PTR_DAT_0044f80c;
    }
    else {
      local_24 = FUN_00439bd4(PTR_DAT_0044f80c);
    }
    FUN_0041d11c(local_24);
    sprintf(local_14,s_Page__d_004551e0,DAT_0045ebf0);
    FUN_0041d11c(local_14);
    if (DAT_0045ebfc != (char *)0x0) {
      FUN_0041c9cf(DAT_0045ebfc);
    }
    FUN_0041cb65();
    if (DAT_0045ec00 != (char *)0x0) {
      FUN_0041c9cf(DAT_0045ec00);
    }
    FUN_0041cb65();
    FUN_0041cb65();
  }
  return;
}


/* ==== FUN_0041d11c @ 0041d11c ==== */

void __cdecl FUN_0041d11c(char *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = strlen(param_1);
  uVar1 = DAT_0044f7d8;
  if (((int)uVar2 <= (DAT_0044f7dc - DAT_0044f7e0) + 1) &&
     (DAT_0044f7dc < (int)(uVar2 + DAT_0044f7d4))) {
    FUN_0041cb65();
  }
  DAT_0044f7d8 = uVar1;
  FUN_0041c9cf(param_1);
  return;
}


/* ==== FUN_0041d17c @ 0041d17c ==== */

void __cdecl FUN_0041d17c(char *param_1,int param_2)

{
  uint local_c;
  char *local_8;
  
  if (DAT_0045ea34 == '\0') {
    for (local_8 = param_1; local_8 < param_1 + param_2; local_8 = local_8 + 1) {
      DAT_0045fcac[1] = DAT_0045fcac[1] + -1;
      if (DAT_0045fcac[1] < 0) {
        local_c = _flsbuf((int)*local_8,DAT_0045fcac);
      }
      else {
        *(char *)*DAT_0045fcac = *local_8;
        local_c = (uint)*(byte *)*DAT_0045fcac;
        *DAT_0045fcac = *DAT_0045fcac + 1;
      }
      if (local_c == 0xffffffff) {
        FUN_00412fa0((uint *)s_Cannot_write_control_string_to_l_004551ec);
      }
    }
  }
  return;
}


/* ==== FUN_0041d23b @ 0041d23b ==== */

void FUN_0041d23b(void)

{
  if (DAT_0045ea34 == '\0') {
    FUN_0041cb65();
    sprintf(&DAT_0045f220,s___4u_Error_c_00455218,DAT_0045eb84,
            (-(uint)(DAT_0045eb84 != 1) & 0x53) + 0x20);
    FUN_0041c9cf(&DAT_0045f220);
    sprintf(&DAT_0045f220,s___4u_Warning_c_00455228,DAT_0045eb88,
            (-(uint)(DAT_0045eb88 != 1) & 0x53) + 0x20);
    FUN_0041c9cf(&DAT_0045f220);
    FUN_0041cb65();
    FUN_0041cb65();
    if (DAT_0045ea40 != '\0') {
      FUN_0041cced(1);
      FUN_0041d36f();
      FUN_0041d584();
      FUN_0041d7ce();
    }
    FUN_0041d90d();
    if (DAT_0045ea10 != '\0') {
      FUN_0041cced(1);
      FUN_0041e4ac();
    }
    if (DAT_0045fb64 != (char *)0x0) {
      FUN_0041d17c(DAT_0045fb64,DAT_0045fb68);
    }
  }
  return;
}


/* ==== FUN_0041d334 @ 0041d334 ==== */

void FUN_0041d334(void)

{
  DAT_0045ea54 = 0;
  DAT_0045f920 = 0;
  DAT_0045ea58 = 0;
  DAT_0045f918 = 0;
  DAT_0045f91c = 0;
  return;
}


/* ==== FUN_0041d36f @ 0041d36f ==== */

undefined4 FUN_0041d36f(void)

{
  undefined *puVar1;
  int local_14;
  int local_10;
  int local_c;
  
  if (DAT_0045eb50 != '\0') {
    DAT_0045ea50 = 1;
    FUN_0043035b((uint *)s_DSPHOST_00455238);
    DAT_0045ea50 = 0;
  }
  if (DAT_0045eba0 != 0) {
    puVar1 = (undefined *)FUN_00439857(DAT_0045eba0 << 2);
    local_c = 0;
    for (local_10 = 0; local_10 < 0x3f1; local_10 = local_10 + 1) {
      for (local_14 = *(int *)(&DAT_00460c88 + local_10 * 4); local_14 != 0;
          local_14 = *(int *)(local_14 + 0x10)) {
        *(int *)(puVar1 + local_c * 4) = local_14;
        local_c = local_c + 1;
      }
    }
    FUN_0041d51c(puVar1,DAT_0045eba0);
    FUN_0041c9cf(s_Define_symbols__00455240);
    FUN_0041cb65();
    FUN_0041c9cf(s_Symbol_Definition_00455254);
    FUN_0041cb65();
    for (local_c = 0; local_c < DAT_0045eba0; local_c = local_c + 1) {
      DAT_0045f220 = 0;
      strncat(&DAT_0045f220,(char *)**(undefined4 **)(puVar1 + local_c * 4),0x10);
      FUN_0041c9cf(&DAT_0045f220);
      FUN_0041d4fe(0x12);
      FUN_0041c9cf(&DAT_00455274);
      FUN_0041c9cf(*(char **)(*(int *)(puVar1 + local_c * 4) + 4));
      FUN_0041c9cf(&DAT_00455278);
    }
    FUN_0041cb65();
    FUN_0041cb65();
    FUN_0043055e();
    FUN_004398b5(puVar1);
  }
  return 1;
}


/* ==== FUN_0041d4fe @ 0041d4fe ==== */

void __cdecl FUN_0041d4fe(int param_1)

{
  while (DAT_0044f7d8 < param_1) {
    FUN_0041c9cf(&DAT_0045527c);
  }
  return;
}


/* ==== FUN_0041d51c @ 0041d51c ==== */

void __cdecl FUN_0041d51c(undefined4 param_1,int param_2)

{
  DAT_0045fc80 = param_1;
  DAT_0045fb60 = FUN_0041d544;
  FUN_004399c9(0,param_2 + -1);
  return;
}


/* ==== FUN_0041d544 @ 0041d544 ==== */

int __cdecl FUN_0041d544(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = strcmp((char *)*param_1,(char *)*param_2);
  if (iVar1 == 0) {
    iVar1 = strcmp((char *)param_1[1],(char *)param_2[1]);
  }
  return iVar1;
}


/* ==== FUN_0041d584 @ 0041d584 ==== */

undefined4 FUN_0041d584(void)

{
  undefined *puVar1;
  int local_14;
  int local_10;
  int local_8;
  
  local_8 = 0;
  if (DAT_0045fb70 != 0) {
    for (local_14 = DAT_0045fb70; local_14 != 0; local_14 = *(int *)(local_14 + 0x18)) {
      local_8 = local_8 + 1;
      if (*(int *)(local_14 + 0x14) != 0) {
        FUN_0041f9ab(*(int **)(local_14 + 0x14));
        *(undefined4 *)(local_14 + 0x14) = 0;
      }
    }
    puVar1 = (undefined *)FUN_00439857(local_8 << 2);
    local_10 = 0;
    for (local_14 = DAT_0045fb70; local_14 != 0; local_14 = *(int *)(local_14 + 0x18)) {
      *(int *)(puVar1 + local_10 * 4) = local_14;
      local_10 = local_10 + 1;
    }
    FUN_0041d770(puVar1,local_8);
    FUN_0041c9cf(s_Macros__00455280);
    FUN_0041cb65();
    FUN_0041c9cf(s_Name_Definition_Section_0045528c);
    FUN_0041c9cf(s_Line_004552b4);
    FUN_0041cb65();
    for (local_10 = 0; local_10 < local_8; local_10 = local_10 + 1) {
      DAT_0045f220 = 0;
      strncat(&DAT_0045f220,(char *)**(undefined4 **)(puVar1 + local_10 * 4),0x10);
      FUN_0041c9cf(&DAT_0045f220);
      FUN_0041d4fe(0x12);
      sprintf(&DAT_0045f220,s___6lu_004552cc,*(undefined4 *)(*(int *)(puVar1 + local_10 * 4) + 8));
      FUN_0041c9cf(&DAT_0045f220);
      if (*(undefined **)(*(int *)(puVar1 + local_10 * 4) + 4) != &DAT_0044f878) {
        FUN_0041cb2d(0x20);
        sprintf(&DAT_0045f220,&DAT_004552d4,
                *(undefined4 *)(*(int *)(*(int *)(puVar1 + local_10 * 4) + 4) + 4));
        FUN_0041c9cf(&DAT_0045f220);
      }
      FUN_0041cb65();
    }
    FUN_0041cb65();
    FUN_0041cb65();
    FUN_0041fa17();
    FUN_004398b5(puVar1);
  }
  return 1;
}


/* ==== FUN_0041d770 @ 0041d770 ==== */

void __cdecl FUN_0041d770(undefined4 param_1,int param_2)

{
  DAT_0045fc80 = param_1;
  DAT_0045fb60 = FUN_0041d798;
  FUN_004399c9(0,param_2 + -1);
  return;
}


/* ==== FUN_0041d798 @ 0041d798 ==== */

int __cdecl FUN_0041d798(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = strcmp((char *)*param_1,(char *)*param_2);
  if (iVar1 == 0) {
    iVar1 = param_1[2] - param_2[2];
  }
  return iVar1;
}


/* ==== FUN_0041d7ce @ 0041d7ce ==== */

undefined4 FUN_0041d7ce(void)

{
  undefined *puVar1;
  int local_10;
  int local_c;
  
  if (DAT_0045fb80 != 0) {
    puVar1 = (undefined *)FUN_00439857(DAT_0045fb80 << 2);
    local_c = 0;
    for (local_10 = *(int *)(PTR_DAT_0044f980 + 0x8c); local_10 != 0;
        local_10 = *(int *)(local_10 + 0x8c)) {
      *(int *)(puVar1 + local_c * 4) = local_10;
      local_c = local_c + 1;
    }
    FUN_0041d8ca(puVar1,DAT_0045fb80);
    FUN_0041c9cf(s_Relocatable_Sections__004552d8);
    FUN_0041cb65();
    FUN_0041c9cf(s_Name_004552f0);
    FUN_0041cb65();
    for (local_c = 0; local_c < DAT_0045fb80; local_c = local_c + 1) {
      FUN_0041c9cf(*(char **)(*(int *)(puVar1 + local_c * 4) + 4));
      FUN_0041cb65();
    }
    FUN_0041cb65();
    FUN_0041cb65();
    FUN_004398b5(puVar1);
  }
  return 1;
}


/* ==== FUN_0041d8ca @ 0041d8ca ==== */

void __cdecl FUN_0041d8ca(undefined4 param_1,int param_2)

{
  DAT_0045fc80 = param_1;
  DAT_0045fb60 = FUN_0041d8f2;
  FUN_004399c9(0,param_2 + -1);
  return;
}


/* ==== FUN_0041d8f2 @ 0041d8f2 ==== */

void __cdecl FUN_0041d8f2(int param_1,int param_2)

{
  strcmp(*(char **)(param_1 + 4),*(char **)(param_2 + 4));
  return;
}


/* ==== FUN_0041d90d @ 0041d90d ==== */

undefined4 FUN_0041d90d(void)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  undefined3 extraout_var;
  void *this;
  void *this_00;
  uint local_4c;
  uint local_48;
  char *local_44;
  char *local_40;
  undefined4 *local_38;
  int local_34;
  undefined4 *local_20;
  int local_1c;
  int local_c;
  
  if ((DAT_0045ea40 != '\0') || (DAT_0045ea3c != '\0')) {
    iVar3 = (DAT_0045eb64 + (-(uint)(DAT_0045ea4c != '\0') & DAT_0045eb6c)) -
            (~-(uint)(DAT_0045eb20 != '\0') & DAT_0045eb70);
    if (iVar3 == 0) {
      FUN_0041c9cf(s_No_symbols_used_004552f8);
    }
    else {
      puVar4 = (undefined *)FUN_00439857(iVar3 * 4);
      local_1c = 0;
      for (local_34 = 0; local_34 < 0x3f1; local_34 = local_34 + 1) {
        for (local_38 = *(undefined4 **)(&DAT_0045fcc0 + local_34 * 4);
            local_38 != (undefined4 *)0x0; local_38 = (undefined4 *)local_38[0x17]) {
          if (((((local_38[6] & 0x20) == 0) || (DAT_0045ea4c != '\0')) &&
              ((iVar5 = strncmp((char *)*local_38,PTR_DAT_0044f99c,3), iVar5 != 0 ||
               (DAT_0045eb20 != '\0')))) &&
             ((iVar5 = strncmp((char *)*local_38,PTR_DAT_0044f9a0,3), iVar5 != 0 ||
              (DAT_0045eb20 != '\0')))) {
            *(undefined4 **)(puVar4 + local_1c * 4) = local_38;
            local_1c = local_1c + 1;
          }
        }
      }
      if (DAT_0045ea4c != '\0') {
        for (local_c = DAT_0045fc3c; local_c != 0; local_c = *(int *)(local_c + 8)) {
          for (local_38 = *(undefined4 **)(local_c + 4); local_38 != (undefined4 *)0x0;
              local_38 = *(undefined4 **)((int)local_38 + 0x5c)) {
            *(undefined4 **)(puVar4 + local_1c * 4) = local_38;
            local_1c = local_1c + 1;
          }
        }
      }
      FUN_0041e02f(puVar4,iVar3);
      if (DAT_0045ea40 != '\0') {
        FUN_0041c9cf(s_Symbols__0045530c);
        FUN_0041cb65();
        FUN_0041c9cf(s_Name_Type_Value_Section_Attribut_00455318);
        FUN_0041cb65();
        for (local_1c = 0; local_1c < iVar3; local_1c = local_1c + 1) {
          uVar1 = *(uint *)(*(int *)(puVar4 + local_1c * 4) + 0x18);
          iVar5 = *(int *)(*(int *)(puVar4 + local_1c * 4) + 0x1c);
          DAT_0045f220 = 0;
          strncat(&DAT_0045f220,(char *)**(undefined4 **)(puVar4 + local_1c * 4),0x10);
          FUN_0041c9cf(&DAT_0045f220);
          FUN_0041d4fe(0x12);
          if ((uVar1 & 0x200) == 0) {
            if ((uVar1 & 0x100) == 0) {
              FUN_0041c9cf(&DAT_00455368);
            }
            else {
              FUN_0041c9cf(&DAT_00455364);
            }
          }
          else {
            FUN_0041c9cf(&DAT_00455360);
          }
          FUN_0041cb2d(0x18);
          bVar2 = FUN_0043a6c5(iVar5);
          if (CONCAT31(extraout_var,bVar2) == 0x4e) {
            FUN_0041c9cf(&DAT_0045536c);
          }
          else {
            FUN_0041e011(this,bVar2);
            FUN_0041e011(this_00,0x3a);
          }
          if (iVar5 == 4) {
            local_40 = s__06lX_0044e098;
          }
          else {
            if ((iVar5 == 0x1c) || (iVar5 == 0x11d)) {
              local_44 = s__08lX_0044e090;
            }
            else {
              local_44 = s__04lX_0044e088;
            }
            local_40 = local_44;
          }
          if (iVar5 == 4) {
            local_48 = 0xffffff;
          }
          else {
            if ((iVar5 == 0x1c) || (iVar5 == 0x11d)) {
              local_4c = 0x1fffff;
            }
            else {
              local_4c = 0xffff;
            }
            local_48 = local_4c;
          }
          if ((uVar1 & 0x200) == 0) {
            if ((uVar1 & 0x100) != 0) {
              if ((uVar1 & 0x800) == 0) {
                sprintf(&DAT_0045f220,local_40,
                        *(uint *)(*(int *)(puVar4 + local_1c * 4) + 0x10) & local_48);
              }
              else {
                sprintf(&DAT_0045f220,local_40,
                        *(uint *)(*(int *)(puVar4 + local_1c * 4) + 0xc) & local_48);
                FUN_0041c9cf(&DAT_0045f220);
                sprintf(&DAT_0045f220,local_40,
                        *(uint *)(*(int *)(puVar4 + local_1c * 4) + 0x10) & local_48);
              }
            }
          }
          else {
            FUN_0043c0ea((uint *)&DAT_0045f220,(uint *)s____6E_00455370,
                         *(int *)(*(int *)(puVar4 + local_1c * 4) + 8),
                         *(uint *)(*(int *)(puVar4 + local_1c * 4) + 0xc));
          }
          FUN_0041c9cf(&DAT_0045f220);
          if (*(undefined **)(*(int *)(puVar4 + local_1c * 4) + 0x40) != &DAT_0044f878) {
            FUN_0041cb2d(0x28);
            DAT_0045f220 = 0;
            strncat(&DAT_0045f220,*(char **)(*(int *)(*(int *)(puVar4 + local_1c * 4) + 0x40) + 4),
                    0x10);
            FUN_0041c9cf(&DAT_0045f220);
          }
          if ((uVar1 & 0x10) == 0) {
            if ((uVar1 & 0x1000) == 0) {
              if (DAT_0044f790 != '\0') {
                FUN_0041cb2d(0x3a);
                FUN_0041c9cf(&DAT_00455380);
              }
            }
            else {
              FUN_0041cb2d(0x3a);
              FUN_0041c9cf(&DAT_0045537c);
            }
          }
          else {
            FUN_0041cb2d(0x3a);
            FUN_0041c9cf(&DAT_00455378);
          }
          if ((uVar1 & 0x20) == 0) {
            if ((uVar1 & 0x80) == 0) {
              if ((uVar1 & 0x40) != 0) {
                FUN_0041cb2d(0x3a);
                FUN_0041c9cf(s_GLOBAL_00455394);
              }
            }
            else {
              FUN_0041cb2d(0x3a);
              FUN_0041c9cf(s_EXTERN_0045538c);
            }
          }
          else {
            FUN_0041cb2d(0x3a);
            FUN_0041c9cf(s_LOCAL_00455384);
          }
          if ((uVar1 & 0x2000) != 0) {
            FUN_0041cb2d(0x3a);
            FUN_0041c9cf(s_BUFFER_0045539c);
          }
          if ((uVar1 & 0x4000) != 0) {
            FUN_0041cb2d(0x3a);
            FUN_0041c9cf(s_OVERLAY_004553a4);
          }
          FUN_0041cb65();
        }
        FUN_0041cb65();
        FUN_0041cb65();
      }
      if (DAT_0045ea3c != '\0') {
        FUN_0041c9cf(s_Symbol_cross_reference_listing__004553ac);
        FUN_0041cb65();
        FUN_0041c9cf(s_Name_Line_number____is_definitio_004553d0);
        for (local_1c = 0; local_1c < iVar3; local_1c = local_1c + 1) {
          DAT_0045f220 = 0;
          strncat(&DAT_0045f220,(char *)**(undefined4 **)(puVar4 + local_1c * 4),0x10);
          FUN_0041c9cf(&DAT_0045f220);
          FUN_0041d4fe(0x12);
          for (local_20 = *(undefined4 **)(*(int *)(puVar4 + local_1c * 4) + 0x50);
              local_20 != (undefined4 *)0x0; local_20 = (undefined4 *)local_20[2]) {
            if (DAT_0044f7dc < DAT_0044f7d4 + 8) {
              FUN_0041cb65();
              FUN_0041cb2d(DAT_0044f7d8 + 0x11);
            }
            iVar5 = DAT_0044f7d8;
            sprintf(&DAT_0045f220,&DAT_00455400,*local_20);
            FUN_0041c9cf(&DAT_0045f220);
            if (local_20[1] == 1) {
              FUN_0041c9cf(&DAT_00455408);
            }
            FUN_0041cb2d(iVar5 + 8);
          }
          FUN_0041cb65();
        }
        FUN_0041cb65();
        FUN_0041cb65();
      }
      FUN_004398b5(puVar4);
    }
  }
  return 1;
}


/* ==== FUN_0041e011 @ 0041e011 ==== */

void __thiscall FUN_0041e011(void *this,byte param_1)

{
  ushort local_8;
  undefined2 uStack_6;
  
  uStack_6 = (undefined2)((uint)this >> 0x10);
  local_8 = (ushort)param_1;
  FUN_0041c9cf((char *)&local_8);
  return;
}


/* ==== FUN_0041e02f @ 0041e02f ==== */

void __cdecl FUN_0041e02f(undefined4 param_1,int param_2)

{
  DAT_0045fc80 = param_1;
  DAT_0045fb60 = FUN_0041e057;
  FUN_004399c9(0,param_2 + -1);
  return;
}


/* ==== FUN_0041e057 @ 0041e057 ==== */

int __cdecl FUN_0041e057(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  float10 fVar2;
  double local_28;
  double local_c;
  
  iVar1 = strcmp((char *)*param_1,(char *)*param_2);
  if (iVar1 == 0) {
    if (param_1[0x10] == param_2[0x10]) {
      if ((param_1[6] & 0x200) == 0) {
        if ((param_1[6] & 0x800) == 0) {
          if (param_1[7] == 4) {
            fVar2 = FUN_0040b312(param_1[4]);
            local_28 = (double)fVar2;
          }
          else {
            fVar2 = FUN_0040b391(0,param_1[4]);
            local_28 = (double)fVar2;
          }
        }
        else {
          fVar2 = FUN_0040b391(param_1[3],param_1[4]);
          local_28 = (double)fVar2;
        }
      }
      else {
        local_28 = *(double *)(param_1 + 2);
      }
      if ((param_2[6] & 0x200) == 0) {
        if ((param_2[6] & 0x800) == 0) {
          if (param_2[7] == 4) {
            fVar2 = FUN_0040b312(param_2[4]);
            local_c = (double)fVar2;
          }
          else {
            fVar2 = FUN_0040b391(0,param_2[4]);
            local_c = (double)fVar2;
          }
        }
        else {
          fVar2 = FUN_0040b391(param_2[3],param_2[4]);
          local_c = (double)fVar2;
        }
      }
      else {
        local_c = *(double *)(param_2 + 2);
      }
      if (0.0 <= local_28 - local_c) {
        if (local_28 - local_c <= 0.0) {
          iVar1 = 0;
        }
        else {
          iVar1 = 1;
        }
      }
      else {
        iVar1 = -1;
      }
    }
    else {
      iVar1 = *(int *)(param_1[0x10] + 8) - *(int *)(param_2[0x10] + 8);
    }
  }
  return iVar1;
}


/* ==== FUN_0041e1e8 @ 0041e1e8 ==== */

void __cdecl FUN_0041e1e8(uint param_1,int param_2)

{
  if (DAT_0045ea10 != '\0') {
    if ((((DAT_0045fc7c == 0) && (DAT_0045fc78 == 0)) || (DAT_0045ea14 != '\0')) ||
       ((param_1 != DAT_00463c28 || ((*PTR_DAT_0044f810 != '\0' && (2 < param_1)))))) {
      FUN_0041e289(param_1);
      DAT_00463c28 = param_1;
      DAT_0045ea14 = '\0';
    }
    *(int *)(DAT_0045fc7c + 0xc) = *(int *)(DAT_0045fc7c + 0xc) + param_2;
    if (DAT_0045f8c0 != DAT_0045f8cc) {
      *(int *)(DAT_0045fc78 + 0xc) = *(int *)(DAT_0045fc78 + 0xc) + param_2;
    }
  }
  return;
}


/* ==== FUN_0041e289 @ 0041e289 ==== */

void __cdecl FUN_0041e289(uint param_1)

{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  uint local_220;
  uint local_21c;
  char local_218 [516];
  uint *local_14;
  int local_c;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)0x0;
  local_14 = (uint *)FUN_00439857(0x20);
  *local_14 = param_1;
  local_14[1] = DAT_0045f8a0;
  if (DAT_0045ebc4 == 0) {
    local_21c = DAT_0045f8c4;
  }
  else {
    local_21c = DAT_0045ebd4;
  }
  local_14[2] = local_21c;
  local_14[3] = 0;
  if (*PTR_DAT_0044f810 != '\0') {
    DAT_0045ea50 = 1;
    local_c = FUN_0043b659(PTR_DAT_0044f810);
    DAT_0045ea50 = 0;
    if (local_c == 1) {
      strcpy(local_218,PTR_DAT_0044f810);
      if (DAT_0045eaa0 != '\0') {
        FUN_0043b836(local_218);
      }
      uVar1 = FUN_00439b65(local_218);
      local_8 = *(undefined4 **)(&DAT_0045fcc0 + uVar1 * 4);
      while ((local_8 != (undefined4 *)0x0 &&
             ((local_218[0] != *(char *)*local_8 ||
              (iVar2 = strcmp(local_218,(char *)*local_8), iVar2 != 0))))) {
        local_8 = (undefined4 *)local_8[0x17];
      }
    }
  }
  local_14[4] = (uint)local_8;
  local_14[5] = (uint)PTR_DAT_0044f978;
  if (DAT_0045f8c0 == DAT_0045f8cc) {
    local_14[6] = 0;
    local_14[7] = (uint)DAT_0045fc7c;
    DAT_0045fc7c = local_14;
  }
  else {
    puVar3 = (uint *)FUN_00439857(0x20);
    *puVar3 = param_1 | 1;
    puVar3[1] = DAT_0045f8b0;
    if (DAT_0045ebc4 == 0) {
      local_220 = DAT_0045f8d0;
    }
    else {
      local_220 = DAT_0045ebd8;
    }
    puVar3[2] = local_220;
    puVar3[3] = 0;
    puVar3[4] = (uint)local_8;
    puVar3[5] = (uint)PTR_DAT_0044f978;
    local_14[6] = (uint)puVar3;
    puVar3[6] = (uint)local_14;
    local_14[7] = (uint)DAT_0045fc7c;
    DAT_0045fc7c = local_14;
    puVar3[7] = (uint)DAT_0045fc78;
    DAT_0045fc78 = puVar3;
  }
  return;
}


/* ==== FUN_0041e4ac @ 0041e4ac ==== */

undefined4 FUN_0041e4ac(void)

{
  uint *puVar1;
  int *piVar2;
  int local_4c;
  int local_48;
  int *local_44;
  int local_40;
  uint local_3c;
  uint local_38;
  int local_30;
  uint local_2c;
  int local_28;
  uint local_24;
  int local_20;
  char *local_c;
  uint local_8;
  
  local_30 = 0;
  if (DAT_0045ea10 != '\0') {
    for (local_4c = DAT_0045fc7c; local_4c != 0; local_4c = *(int *)(local_4c + 0x1c)) {
      local_30 = local_30 + 1;
    }
    for (local_4c = DAT_0045fc78; local_4c != 0; local_4c = *(int *)(local_4c + 0x1c)) {
      local_30 = local_30 + 1;
    }
    piVar2 = (int *)FUN_00439857(local_30 * 4 + 4);
    if (local_30 != 0) {
      local_44 = piVar2;
      for (local_4c = DAT_0045fc7c; local_4c != 0; local_4c = *(int *)(local_4c + 0x1c)) {
        *local_44 = local_4c;
        local_44 = local_44 + 1;
      }
      for (local_4c = DAT_0045fc78; local_4c != 0; local_4c = *(int *)(local_4c + 0x1c)) {
        *local_44 = local_4c;
        local_44 = local_44 + 1;
      }
      FUN_0041ed0d(piVar2,local_30);
    }
    piVar2[local_30] = 0;
    FUN_0041c9cf(s_Memory_Utilization_Report_0045540c);
    if (local_30 == 0) {
      FUN_0041cb65();
      FUN_0041cb65();
      FUN_0041c9cf(s_No_memory_used_00455440);
      FUN_004398b5((undefined *)piVar2);
      FUN_0041edc3();
    }
    else {
      local_44 = piVar2;
      for (local_40 = 1; local_40 < 7; local_40 = local_40 + 1) {
        if (((2 < DAT_0044f9fc) || (local_40 != 5)) && ((0x1fff < DAT_0044fa00 || (local_40 != 6))))
        {
          switch(local_40) {
          case 1:
            local_48 = 1;
            local_38 = 0xffff;
            local_c = &DAT_00455450;
            break;
          case 2:
            local_48 = 2;
            local_38 = 0xffff;
            local_c = &DAT_00455454;
            break;
          case 3:
            local_48 = 3;
            local_38 = 0xffff;
            local_c = &DAT_00455458;
            break;
          case 4:
            local_48 = 0;
            local_38 = 0xffff;
            local_c = &DAT_0045545c;
            break;
          case 5:
            local_48 = 0x1c;
            local_38 = 0x1fffff;
            local_c = &DAT_00455460;
            break;
          case 6:
            local_48 = 0x11d;
            local_38 = 0x1fffff;
            local_c = &DAT_00455464;
            break;
          default:
            local_48 = 4;
            local_38 = 0xffff;
            local_c = &DAT_00455468;
          }
          if ((*local_44 != 0) && (*(int *)(*local_44 + 4) == local_48)) {
            FUN_0041cb65();
            FUN_0041cb65();
            FUN_0041c9cf(local_c);
            FUN_0041c9cf(s_Memory_0045546c);
            FUN_0041cb65();
            if ((local_48 == 0x1c) || (local_48 == 0x11d)) {
              FUN_0041c9cf(s_Start_End_Length_Type_Label_Sect_00455478);
            }
            else {
              FUN_0041c9cf(s_Start_End_Length_Type_Label_Sect_004554d8);
            }
            local_3c = 0;
            FUN_0041e8ac((uint *)0x0,local_38);
            while ((*local_44 != 0 && (*(int *)(*local_44 + 4) == local_48))) {
              puVar1 = (uint *)*local_44;
              local_44 = local_44 + 1;
              if (puVar1[3] != 0) {
                if (local_3c < puVar1[2]) {
                  local_2c = 0;
                  local_28 = local_48;
                  local_24 = local_3c;
                  local_20 = puVar1[2] - local_3c;
                  FUN_0041e8ac(&local_2c,local_38);
                  local_8 = local_24 + local_20;
                  if (local_3c < local_8) {
                    local_3c = local_8;
                  }
                }
                FUN_0041e8ac(puVar1,local_38);
                local_8 = puVar1[2] + puVar1[3];
                if (local_3c < local_8) {
                  local_3c = local_8;
                }
              }
            }
            if (local_3c < local_38) {
              local_2c = 0;
              local_28 = local_48;
              local_24 = local_3c;
              local_20 = (local_38 + 1) - local_3c;
              FUN_0041e8ac(&local_2c,local_38);
            }
          }
        }
      }
      FUN_004398b5((undefined *)piVar2);
      FUN_0041edc3();
    }
  }
  return 1;
}


