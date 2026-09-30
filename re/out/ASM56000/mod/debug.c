/* debug: 17 functions from ASM56000 */

/* ==== FUN_0040e749 @ 0040e749 ==== */

undefined4 __cdecl FUN_0040e749(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  undefined4 uVar4;
  uint uVar5;
  uint local_40;
  uint local_38;
  int local_34;
  int local_30;
  uint local_18;
  uint local_c;
  uint local_8;
  
  DAT_0045ebc4 = 0;
  if (param_2 == 0) {
    FUN_00413085((uint *)s_Storage_block_size_must_be_great_004535a8);
    uVar4 = 0;
  }
  else {
    if ((param_2 == 1) || ((param_2 & param_2 - 1) != 0)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    if ((param_1 != 0x800) || (bVar3)) {
      if ((param_1 == 0x400) && ((param_2 < 2 || ((DAT_0044f91c >> 1) + 1 < param_2)))) {
        FUN_00413085((uint *)s_Storage_block_size_out_of_range_004535fc);
        return 0;
      }
    }
    else {
      FUN_004133a9((uint *)s_Storage_block_size_not_a_power_o_004535d8);
    }
    if ((DAT_0045f8ac & 0xf) == 0) {
      local_30 = 1;
    }
    else {
      local_30 = (int)(CONCAT44((int)DAT_0045f8ac >> 0x1f,(int)DAT_0045f8ac >> 4) /
                      (longlong)(int)(DAT_0045f8ac & 0xf)) +
                 ((int)DAT_0045f8ac >> 4 & (uint)((DAT_0045f8ac & 1) == 0));
    }
    uVar5 = param_2 * local_30;
    if ((DAT_0045f8bc & 0xf) == 0) {
      local_34 = 1;
    }
    else {
      local_34 = (int)(CONCAT44((int)DAT_0045f8bc >> 0x1f,(int)DAT_0045f8bc >> 4) /
                      (longlong)(int)(DAT_0045f8bc & 0xf)) +
                 ((int)DAT_0045f8bc >> 4 & (uint)((DAT_0045f8bc & 1) == 0));
    }
    local_8 = param_2 * local_34;
    uVar1 = *DAT_0045f8c0;
    local_c = uVar1;
    if (uVar1 != 0) {
      local_38 = uVar5;
      if (!bVar3) {
        local_38 = FUN_0040f390(uVar5);
      }
      local_c = (uVar1 - 1) + local_38 & ~(local_38 - 1);
    }
    uVar2 = *DAT_0045f8cc;
    local_18 = uVar2;
    if (DAT_0045f8c0 != DAT_0045f8cc) {
      if ((((param_3 == 6) || (param_3 == 0x46)) || (param_3 == 0x47)) || (param_3 == 0x48)) {
        local_18 = uVar2 + local_34 * (local_c - uVar1);
        if ((DAT_0045eaa4 != '\0') && (DAT_0045f8b0 != 0x1c)) {
          local_18 = uVar2 + (local_c - uVar1) * 3;
          local_8 = local_8 * 3;
        }
      }
      else {
        if ((local_8 == 1) || ((local_8 & local_8 - 1) != 0)) {
          bVar3 = false;
        }
        else {
          bVar3 = true;
        }
        local_40 = local_8;
        if (!bVar3) {
          local_40 = FUN_0040f390(local_8);
        }
        local_18 = (uVar2 - 1) + local_40 & ~(local_40 - 1);
      }
    }
    local_c = local_c & DAT_0044f91c;
    if (local_c < uVar1) {
      FUN_00413085((uint *)s_Storage_block_too_large_0045361c);
      uVar4 = 0;
    }
    else {
      DAT_0045ebc0 = DAT_0045ebc0 + 1;
      DAT_0045ebcc = param_1;
      DAT_0045ebd0 = param_2;
      DAT_0045ebc4 = local_c + uVar5;
      DAT_0045ebc8 = local_18 + local_8;
      FUN_0040ee80(uVar1,local_c,uVar2,local_18);
      uVar4 = 1;
    }
  }
  return uVar4;
}


/* ==== FUN_0040ea5e @ 0040ea5e ==== */

void __cdecl
FUN_0040ea5e(int param_1,int param_2,int param_3,int param_4,uint param_5,uint param_6,uint param_7)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  int local_1c;
  
  iVar2 = param_4 - param_3;
  uVar3 = param_5 & 0x2000;
  bVar4 = DAT_0045f8c0 != DAT_0045f8cc;
  if ((0 < param_2 - param_1) || (0 < iVar2)) {
    piVar1 = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8a0,
                          param_5 | -(uint)(DAT_0044f794 != '\0') & 0x1000 | -(uint)bVar4 & 0x4000,0
                         );
    DAT_0045fb88 = piVar1;
    *(int *)(piVar1[9] + 8) = param_1;
    *(int *)(piVar1[9] + 0x10) = param_2;
    *(int *)(piVar1[9] + 0x18) = param_2 - param_1;
    if (*piVar1 == 3) {
      *(int *)(piVar1[9] + 0x18) = *(int *)(piVar1[9] + 0x18) << 1;
    }
    *(uint *)(piVar1[9] + 0x30) =
         *(uint *)(piVar1[9] + 0x30) | (-(uint)(uVar3 != 0) & 0xffffff88) + 0x80;
    if (bVar4) {
      piVar1 = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8b0,
                            param_5 | -(uint)(DAT_0044f798 != '\0') & 0x1000,0);
      DAT_0045fb8c = piVar1;
      *(int *)(piVar1[9] + 8) = param_3;
      *(int *)(piVar1[9] + 0x10) = param_4;
      if ((((DAT_0045eaa4 == '\0') && (DAT_0045eaa8 == '\0')) || (DAT_0045f8b0 == 0x1c)) ||
         ((DAT_0044f7c0 != '\0' || (uVar3 == 0)))) {
        *(int *)(piVar1[9] + 0x18) = iVar2;
      }
      else {
        *(undefined4 *)(piVar1[9] + 0x18) = 0;
      }
      if (*piVar1 == 3) {
        *(int *)(piVar1[9] + 0x18) = *(int *)(piVar1[9] + 0x18) << 1;
      }
      *(uint *)(piVar1[9] + 0x30) =
           *(uint *)(piVar1[9] + 0x30) | (-(uint)(uVar3 != 0) & 0xffffff88) + 0x80;
      DAT_0045f8cc = piVar1[9] + 0x10;
      if (DAT_0045eadc != '\0') {
        *(uint *)(piVar1[9] + 0x30) = *(uint *)(piVar1[9] + 0x30) | 0x800;
      }
    }
    else {
      DAT_0045fb8c = DAT_0045fb88;
      DAT_0045f8cc = DAT_0045f8c0;
    }
  }
  if (uVar3 == 0) {
    FUN_0043797a();
    if (((DAT_0045eadc != '\0') && (DAT_0045ea98 == '\0')) &&
       ((DAT_0045ea70 == '\0' && ((DAT_0045eacc == '\0' && (DAT_0045f8a0 == 0)))))) {
      if (DAT_0045eb24 == '\0') {
        local_1c = DAT_0045eb78;
      }
      else {
        local_1c = DAT_0044f7e8;
      }
      FUN_0042433e(local_1c);
    }
  }
  else {
    DAT_0045ebcc = 0;
  }
  piVar1 = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8a0,
                        -(uint)(DAT_0044f794 != '\0') & 0x1000 | -(uint)bVar4 & 0x4000,0);
  DAT_0045fb88 = piVar1;
  *(int *)(piVar1[9] + 0x10) = param_2;
  *(int *)(piVar1[9] + 8) = param_2;
  *(uint *)(piVar1[9] + 0x30) = *(uint *)(piVar1[9] + 0x30) | param_6 & 0xfffffffe;
  DAT_0045f8c0 = piVar1[9] + 0x10;
  if (bVar4) {
    piVar1 = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8b0,-(uint)(DAT_0044f798 != '\0') & 0x1000
                          ,0);
    DAT_0045fb8c = piVar1;
    if ((((DAT_0045eaa4 == '\0') && (DAT_0045eaa8 == '\0')) || (DAT_0045f8b0 == 0x1c)) ||
       ((DAT_0044f7c0 != '\0' || (uVar3 == 0)))) {
      *(int *)(piVar1[9] + 0x10) = param_3 + iVar2;
      *(undefined4 *)(piVar1[9] + 8) = *(undefined4 *)(piVar1[9] + 0x10);
    }
    else {
      *(int *)(piVar1[9] + 0x10) = param_3;
      *(int *)(piVar1[9] + 8) = param_3;
    }
    *(uint *)(piVar1[9] + 0x30) = *(uint *)(piVar1[9] + 0x30) | param_7 & 0xfffffffe;
    DAT_0045f8cc = piVar1[9] + 0x10;
    if (DAT_0045eadc != '\0') {
      *(uint *)(piVar1[9] + 0x30) = *(uint *)(piVar1[9] + 0x30) | 0x800;
    }
  }
  else {
    DAT_0045fb8c = DAT_0045fb88;
    DAT_0045f8cc = DAT_0045f8c0;
  }
  return;
}


/* ==== FUN_0040ee80 @ 0040ee80 ==== */

void __cdecl FUN_0040ee80(int param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  bool bVar5;
  
  uVar3 = DAT_0045ebcc;
  bVar5 = DAT_0045f8c0 != DAT_0045f8cc;
  uVar1 = *(uint *)(*(int *)((int)DAT_0045fb88 + 0x24) + 0x30);
  uVar2 = *(uint *)(*(int *)((int)DAT_0045fb8c + 0x24) + 0x30);
  if (0 < param_2 - param_1) {
    DAT_0045ebcc = 0;
    piVar4 = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8a0,
                          -(uint)(DAT_0044f794 != '\0') & 0x1000 | -(uint)bVar5 & 0x4000,0);
    *(int *)(piVar4[9] + 8) = param_1;
    *(int *)(piVar4[9] + 0x10) = param_2;
    *(int *)(piVar4[9] + 0x18) = param_2 - param_1;
    if (*piVar4 == 3) {
      *(int *)(piVar4[9] + 0x18) = *(int *)(piVar4[9] + 0x18) << 1;
    }
    *(uint *)(piVar4[9] + 0x30) = *(uint *)(piVar4[9] + 0x30) | 8;
    if (bVar5) {
      piVar4 = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8b0,
                            -(uint)(DAT_0044f798 != '\0') & 0x1000,0);
      *(int *)(piVar4[9] + 8) = param_3;
      *(int *)(piVar4[9] + 0x10) = param_4;
      *(uint *)(piVar4[9] + 0x18) = -(uint)(DAT_0044f7c0 != '\0') & param_4 - param_3;
      if (*piVar4 == 3) {
        *(int *)(piVar4[9] + 0x18) = *(int *)(piVar4[9] + 0x18) << 1;
      }
      *(uint *)(piVar4[9] + 0x30) = *(uint *)(piVar4[9] + 0x30) | 8;
      if (DAT_0045eadc != '\0') {
        *(uint *)(piVar4[9] + 0x30) = *(uint *)(piVar4[9] + 0x30) | 0x800;
      }
    }
  }
  DAT_0045ebcc = uVar3;
  if ((*(int *)(PTR_DAT_0044f97c + 0x6c) != 0) && (DAT_0045f8a0 == 0)) {
    *(undefined4 *)(*(int *)(PTR_DAT_0044f97c + 0x6c) + 0x10) = 0;
    FUN_00434023((uint *)0x0,0,0,0);
  }
  piVar4 = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8a0,
                        (uint)((byte)(-(uint)(DAT_0044f794 != '\0') >> 8) & 0x10 | 0x20) << 8 |
                        -(uint)bVar5 & 0x4000,0);
  DAT_0045fb88 = piVar4;
  piVar4[8] = piVar4[8] + 1;
  *(int *)(piVar4[9] + 0x10) = param_2;
  *(int *)(piVar4[9] + 8) = param_2;
  *(uint *)(piVar4[9] + 0x30) = *(uint *)(piVar4[9] + 0x30) | uVar1 & 0xfffffffe;
  DAT_0045f8c0 = (int *)(piVar4[9] + 0x10);
  DAT_0045f8c4 = param_2;
  DAT_0045ebd4 = param_2;
  if (bVar5) {
    piVar4 = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8b0,
                          (uint)((byte)(-(uint)(DAT_0044f798 != '\0') >> 8) & 0x10 | 0x20) << 8,0);
    DAT_0045fb8c = piVar4;
    piVar4[8] = piVar4[8] + 1;
    *(uint *)(piVar4[9] + 0x10) = param_3 + (-(uint)(DAT_0044f7c0 != '\0') & param_4 - param_3);
    *(undefined4 *)(piVar4[9] + 8) = *(undefined4 *)(piVar4[9] + 0x10);
    *(uint *)(piVar4[9] + 0x30) = *(uint *)(piVar4[9] + 0x30) | uVar2 & 0xfffffffe;
    DAT_0045f8cc = (int *)(piVar4[9] + 0x10);
    DAT_0045ebd8 = *DAT_0045f8cc;
    DAT_0045f8d0 = DAT_0045ebd8;
    if (DAT_0045eadc != '\0') {
      *(uint *)(piVar4[9] + 0x30) = *(uint *)(piVar4[9] + 0x30) | 0x800;
    }
  }
  else {
    DAT_0045fb8c = DAT_0045fb88;
    DAT_0045f8d0 = param_2;
    DAT_0045ebd8 = param_2;
    DAT_0045f8cc = DAT_0045f8c0;
  }
  return;
}


/* ==== FUN_0040f21d @ 0040f21d ==== */

void __cdecl FUN_0040f21d(uint param_1,uint param_2)

{
  int *piVar1;
  bool bVar2;
  
  bVar2 = DAT_0045f8c0 != DAT_0045f8cc;
  DAT_0045ebcc = 0;
  piVar1 = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8a0,
                        -(uint)(DAT_0044f794 != '\0') & 0x1000 | -(uint)bVar2 & 0x4000,0);
  DAT_0045fb88 = piVar1;
  *(undefined4 *)(piVar1[9] + 0x10) = *DAT_0045f8c0;
  *(undefined4 *)(piVar1[9] + 8) = *(undefined4 *)(piVar1[9] + 0x10);
  *(uint *)(piVar1[9] + 0x30) = *(uint *)(piVar1[9] + 0x30) | param_1 & 0xfffffffe;
  DAT_0045f8c0 = (undefined4 *)(piVar1[9] + 0x10);
  if (bVar2) {
    piVar1 = FUN_0042c829((int)PTR_DAT_0044f97c,&DAT_0045f8b0,-(uint)(DAT_0044f798 != '\0') & 0x1000
                          ,0);
    DAT_0045fb8c = piVar1;
    *(undefined4 *)(piVar1[9] + 0x10) = *DAT_0045f8cc;
    *(undefined4 *)(piVar1[9] + 8) = *(undefined4 *)(piVar1[9] + 0x10);
    *(uint *)(piVar1[9] + 0x30) = *(uint *)(piVar1[9] + 0x30) | param_2 & 0xfffffffe;
    DAT_0045f8cc = (undefined4 *)(piVar1[9] + 0x10);
    if (DAT_0045eadc != '\0') {
      *(uint *)(piVar1[9] + 0x30) = *(uint *)(piVar1[9] + 0x30) | 0x800;
    }
  }
  else {
    DAT_0045fb8c = DAT_0045fb88;
    DAT_0045f8cc = DAT_0045f8c0;
  }
  return;
}


/* ==== FUN_0040f390 @ 0040f390 ==== */

uint __cdecl FUN_0040f390(uint param_1)

{
  uint uVar1;
  
  if (param_1 < 2) {
    uVar1 = -(uint)(param_1 != 0) & 2;
  }
  else {
    uVar1 = param_1 - 1;
    do {
      param_1 = uVar1;
      uVar1 = param_1 & param_1 - 1;
    } while (uVar1 != 0);
    uVar1 = param_1 << 1;
  }
  return uVar1;
}


/* ==== FUN_0040f3e0 @ 0040f3e0 ==== */

undefined4 __cdecl FUN_0040f3e0(undefined4 *param_1)

{
  undefined4 uVar1;
  char *local_8;
  
  if (DAT_0045eae0 == '\0') {
    uVar1 = 0;
  }
  else {
    DAT_0045eae8 = 1;
    if (*PTR_DAT_0044f810 != '\0') {
      FUN_004133a9((uint *)s_Label_field_ignored_0045366c);
    }
    if (((DAT_0045f8fc == 2) && (DAT_0045fbec == '\0')) && (*(char *)(param_1 + 1) != '\x01')) {
      FUN_00413085((uint *)s_Initial_debug_directive_must_be___00453680);
      DAT_0045fbec = '\x01';
    }
    DAT_0045f860 = PTR_DAT_0044f818;
    switch(*(undefined1 *)(param_1 + 1)) {
    case 1:
      local_8 = FUN_0043b08d(PTR_DAT_0044f818,&DAT_0045f220);
      if (local_8 == (char *)0x0) {
        uVar1 = 0;
      }
      else {
        if (*local_8 == ',') {
          local_8 = local_8 + 1;
        }
        uVar1 = FUN_0040f5d5((uint *)*param_1,(uint *)&DAT_0045f220,local_8,1);
      }
      break;
    case 2:
      uVar1 = FUN_0040ffe6(PTR_DAT_0044f818);
      break;
    case 3:
      uVar1 = FUN_0040fa17((uint *)PTR_DAT_0044f818);
      break;
    case 4:
      uVar1 = FUN_00410100();
      break;
    case 5:
      uVar1 = FUN_0040fb2c(PTR_DAT_0044f818);
      break;
    case 6:
    case 7:
      uVar1 = FUN_0040fcbb((int)*(char *)(param_1 + 1),PTR_DAT_0044f818);
      break;
    case 8:
      uVar1 = FUN_0040fd68((uint *)PTR_DAT_0044f818);
      break;
    case 9:
      uVar1 = FUN_0040fdf9(PTR_DAT_0044f818);
      break;
    case 10:
      uVar1 = FUN_0040feee(PTR_DAT_0044f818);
      break;
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
      uVar1 = FUN_0040f814(param_1,PTR_DAT_0044f818);
      break;
    case 0xf:
      uVar1 = FUN_0041007c(PTR_DAT_0044f818);
      break;
    default:
      FUN_00412fa0((uint *)s_Directive_select_error_004536a8);
      uVar1 = 0;
    }
  }
  return uVar1;
}


/* ==== FUN_0040f5d5 @ 0040f5d5 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_0040f5d5(uint *param_1,uint *param_2,char *param_3,int param_4)

{
  uint uVar1;
  undefined4 local_18;
  undefined4 local_14;
  int local_c;
  int *local_8;
  
  local_8 = (int *)0x0;
  if (DAT_0045ea80 == '\0') {
    if ((param_2 == (uint *)0x0) || ((char)*param_2 == '\0')) {
      FUN_00413085((uint *)s_Missing_filename_004536f4);
      local_18 = 0;
    }
    else {
      DAT_0045f860 = param_3;
      if (((param_3 == (char *)0x0) || (*param_3 == '\0')) ||
         (local_8 = FUN_00413e70(), local_8 != (int *)0x0)) {
        FUN_0043c34d();
        DAT_00465a60._0_1_ = 0x2e;
        strcpy((char *)((int)&DAT_00465a60 + 1),(char *)param_1);
        DAT_00465a70 = 0xfffffffe;
        if ((param_4 == 0) || (DAT_0044f790 == '\0')) {
          local_14 = 0;
        }
        else {
          local_14 = 1;
        }
        DAT_00465a74 = local_14;
        DAT_00465a78 = (-(uint)(DAT_0045eae0 != '\0') & 0xffffff9f) + 200;
        DAT_00465a7c = 1;
        FUN_0042447e(&DAT_00465a60);
        if (DAT_0045eb50 != '\0') {
          param_2 = (uint *)FUN_00439bd4((char *)param_2);
        }
        uVar1 = strlen((char *)param_2);
        if ((int)uVar1 < 0x11) {
          for (local_c = 0; local_c < (int)uVar1; local_c = local_c + 1) {
            *(undefined1 *)((int)&DAT_00465880 + local_c) = *(undefined1 *)((int)param_2 + local_c);
          }
          FUN_0043c4b2((undefined1 *)&DAT_00465880,1,0x20);
        }
        else {
          _DAT_00465890 = FUN_0042456e(param_2);
        }
        if (local_8 != (int *)0x0) {
          _DAT_00465894 = local_8[2];
          FUN_004167ef(local_8);
        }
        FUN_0042447e(&DAT_00465880);
        FUN_00423011();
        if ((DAT_0045f8fc == 2) && (DAT_0045fbec = 1, DAT_0045eaf0 == '\0')) {
          FUN_00422b3a((uint *)PTR_s_GLOBAL_0044f87c,DAT_0044f8dc);
          DAT_0045eaf0 = '\x01';
        }
        DAT_0045eaec = 1;
        if (((DAT_0045f8fc == 2) && (DAT_0045fca8 != 0)) && (DAT_0045eb44 == '\0')) {
          FUN_0042118f();
        }
        if ((param_2 == (uint *)PTR_DAT_0044f80c) || (param_2 == DAT_0045f858)) {
          local_18 = 1;
        }
        else {
          local_18 = FUN_0043b007(1);
        }
      }
      else {
        local_18 = 0;
      }
    }
  }
  else {
    FUN_00413085((uint *)s_Illegal_directive_inside__DEF__E_004536c0);
    local_18 = 0;
  }
  return local_18;
}


/* ==== FUN_0040f814 @ 0040f814 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_0040f814(undefined4 *param_1,char *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int *local_c;
  
  local_c = (int *)0x0;
  if (DAT_0045ea80 == '\0') {
    if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
      FUN_00413085((uint *)s_Missing_line_number_0045373c);
      uVar1 = 0;
    }
    else if (DAT_0045f8a0 == 0) {
      DAT_0045f860 = param_2;
      piVar2 = FUN_00413e70();
      if (piVar2 == (int *)0x0) {
        uVar1 = 0;
      }
      else {
        if ((*(char *)(param_1 + 1) == '\v') && (*DAT_0045f860 == ',')) {
          DAT_0045f860 = DAT_0045f860 + 1;
          local_c = FUN_00413e70();
          if (local_c == (int *)0x0) {
            return 0;
          }
        }
        FUN_0043c34d();
        DAT_00465a60._0_1_ = 0x2e;
        strcpy((char *)((int)&DAT_00465a60 + 1),(char *)*param_1);
        DAT_00465a6c = DAT_0045f8a4;
        DAT_00465a68 = *DAT_0045f8c0;
        DAT_00465a70 = *(undefined4 *)(DAT_0045fb8c + 0x1c);
        switch(*(undefined1 *)(param_1 + 1)) {
        case 0xb:
          DAT_0045fc1c = DAT_0045fc1c + 1;
        case 0xc:
          DAT_00465a78 = 0x65;
          break;
        case 0xd:
          DAT_0045fc20 = DAT_0045fc20 + 1;
          DAT_00465a78 = 100;
          break;
        case 0xe:
          DAT_0045fc20 = DAT_0045fc20 + -1;
          DAT_00465a78 = 100;
          break;
        default:
          FUN_00412fa0((uint *)s_Debug_symbol_type_failure_00453768);
        }
        DAT_00465a7c = 1;
        DAT_00465884 = piVar2[2];
        if (local_c != (int *)0x0) {
          _DAT_00465894 = local_c[2];
          FUN_004167ef(local_c);
        }
        FUN_004167ef(piVar2);
        FUN_0042447e(&DAT_00465a60);
        FUN_0042447e(&DAT_00465880);
        uVar1 = FUN_0043b007(1);
      }
    }
    else {
      FUN_00413085((uint *)s_Runtime_space_must_be_P_00453750);
      uVar1 = 0;
    }
  }
  else {
    FUN_00413085((uint *)s_Illegal_directive_inside__DEF__E_00453708);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_0040fa17 @ 0040fa17 ==== */

undefined4 __cdecl FUN_0040fa17(uint *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  bool bVar3;
  
  if (DAT_0045ea80 == '\0') {
    DAT_0045ea80 = '\x01';
    if ((param_1 == (uint *)0x0) || ((char)*param_1 == '\0')) {
      FUN_00413085((uint *)s_Missing_symbol_name_004537a4);
      uVar1 = 0;
    }
    else {
      FUN_0043c34d();
      FUN_00410901();
      uVar2 = strlen((char *)param_1);
      if (uVar2 < 8) {
        strcpy((char *)&DAT_00465a60,(char *)param_1);
      }
      else {
        DAT_00465a64 = FUN_0042456e(param_1);
      }
      DAT_0045ea50 = 1;
      DAT_0045fbfc = FUN_00438441(param_1,2);
      DAT_0045fc00 = DAT_0045fbfc;
      if (DAT_0045f8fc < 2) {
        bVar3 = DAT_0045fbfc == (undefined4 *)0x0;
        if (bVar3) {
          FUN_00439326();
        }
      }
      else if (*DAT_0045fc70 == DAT_0045f934) {
        FUN_00439374();
        DAT_0045fc04 = true;
        bVar3 = (bool)DAT_0045fc04;
      }
      else {
        DAT_0045fc04 = false;
        bVar3 = (bool)DAT_0045fc04;
      }
      DAT_0045fc04 = bVar3;
      DAT_0045ea50 = 0;
      uVar1 = FUN_0043b007(1);
    }
  }
  else {
    FUN_00413085((uint *)s_Cannot_nest_symbol_definitions_00453784);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_0040fb2c @ 0040fb2c ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_0040fb2c(char *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  if (DAT_0045ea80 == '\0') {
    FUN_00413085((uint *)s_Illegal_directive_outside__DEF___004537b8);
    uVar1 = 0;
  }
  else if ((param_1 == (char *)0x0) || (*param_1 == '\0')) {
    FUN_00413085((uint *)s_Missing_symbol_value_004537ec);
    uVar1 = 0;
  }
  else {
    DAT_0045f860 = param_1;
    local_c = FUN_00439e8d(&local_1c);
    if (local_c == -1) {
      uVar1 = 0;
    }
    else {
      local_8 = FUN_00414862();
      if (local_8 == (int *)0x0) {
        uVar1 = 0;
      }
      else {
        if (local_c == 0) {
          local_1c = local_8[7];
          local_18 = local_8[8];
          local_14 = local_8[9];
          local_10 = local_8[10];
        }
        else if (DAT_0044f7a4 != '\0') {
          iVar2 = FUN_0043baf1(local_8[7],local_1c);
          if (iVar2 == 0xa2c2a) {
            FUN_004133a9((uint *)s_Expression_involves_incompatible_00453804);
          }
        }
        DAT_0045fbf8 = local_1c != 4;
        if (local_1c == DAT_0045f8a0) {
          local_20 = 4;
        }
        else {
          local_20 = local_1c;
        }
        _DAT_0044f98c = local_20;
        if (local_1c == 4) {
          DAT_00465a68 = local_8[2];
          DAT_00465a6c = local_8[1];
        }
        else {
          DAT_00465a6c = local_18;
          DAT_00465a68 = local_8[2];
          DAT_00465a70 = local_8[0x15];
          if (local_8[0x16] != 0) {
            DAT_0045fbfc = local_8[0x16];
            DAT_0045fc04 = (local_8[6] & 0x8000000U) != 0;
          }
        }
        FUN_004167ef(local_8);
        uVar1 = FUN_0043b007(1);
      }
    }
  }
  return uVar1;
}


/* ==== FUN_0040fcbb @ 0040fcbb ==== */

undefined4 __cdecl FUN_0040fcbb(int param_1,char *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  
  if (DAT_0045ea80 == '\0') {
    FUN_00413085((uint *)s_Illegal_directive_outside__DEF___00453834);
    uVar1 = 0;
  }
  else if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    FUN_00413085((uint *)s_Missing_argument_00453868);
    uVar1 = 0;
  }
  else {
    DAT_0045f860 = param_2;
    piVar2 = FUN_00413e70();
    if (piVar2 == (int *)0x0) {
      uVar1 = 0;
    }
    else {
      if (param_1 == 6) {
        DAT_00465a78 = piVar2[2];
      }
      else if (param_1 == 7) {
        DAT_00465a74 = piVar2[2];
      }
      else {
        FUN_00412fa0((uint *)s_Debug_symbol_type_failure_0045387c);
      }
      FUN_004167ef(piVar2);
      uVar1 = FUN_0043b007(1);
    }
  }
  return uVar1;
}


/* ==== FUN_0040fd68 @ 0040fd68 ==== */

undefined4 __cdecl FUN_0040fd68(uint *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (DAT_0045f8fc < 2) {
    uVar1 = FUN_0043b007(1);
  }
  else if (DAT_0045ea80 == '\0') {
    FUN_00413085((uint *)s_Illegal_directive_outside__DEF___00453898);
    uVar1 = 0;
  }
  else if ((param_1 == (uint *)0x0) || ((char)*param_1 == '\0')) {
    FUN_00413085((uint *)s_Missing_tag_name_004538cc);
    uVar1 = 0;
  }
  else {
    uVar2 = strlen((char *)param_1);
    DAT_0045fbf0 = (char *)FUN_00439857(uVar2 + 1);
    strcpy(DAT_0045fbf0,(char *)param_1);
    uVar1 = FUN_0043b007(1);
  }
  return uVar1;
}


/* ==== FUN_0040fdf9 @ 0040fdf9 ==== */

undefined4 __cdecl FUN_0040fdf9(char *param_1)

{
  undefined4 uVar1;
  int *piVar2;
  
  if (DAT_0045f8fc < 2) {
    uVar1 = FUN_0043b007(1);
  }
  else if (DAT_0045ea80 == '\0') {
    FUN_00413085((uint *)s_Illegal_directive_outside__DEF___004538e0);
    uVar1 = 0;
  }
  else if ((param_1 == (char *)0x0) || (*param_1 == '\0')) {
    FUN_00413085((uint *)s_Missing_size_argument_00453914);
    uVar1 = 0;
  }
  else {
    DAT_0045f860 = param_1;
    piVar2 = FUN_00413e70();
    if (piVar2 == (int *)0x0) {
      uVar1 = 0;
    }
    else if (piVar2[4] == 0x100) {
      if ((piVar2[6] & 0x1000U) == 0) {
        DAT_0045fbf4 = piVar2[2];
        FUN_004167ef(piVar2);
        uVar1 = FUN_0043b007(1);
      }
      else {
        FUN_00413085((uint *)s_Expression_result_must_be_absolu_00453950);
        FUN_004167ef(piVar2);
        uVar1 = 0;
      }
    }
    else {
      FUN_00413085((uint *)s_Expression_result_must_be_intege_0045392c);
      FUN_004167ef(piVar2);
      uVar1 = 0;
    }
  }
  return uVar1;
}


/* ==== FUN_0040feee @ 0040feee ==== */

undefined4 __cdecl FUN_0040feee(char *param_1)

{
  undefined4 uVar1;
  int *piVar2;
  int local_c;
  
  if (DAT_0045f8fc < 2) {
    uVar1 = FUN_0043b007(1);
  }
  else if (DAT_0045ea80 == '\0') {
    FUN_00413085((uint *)s_Illegal_directive_outside__DEF___00453974);
    uVar1 = 0;
  }
  else if ((param_1 == (char *)0x0) || (*param_1 == '\0')) {
    FUN_00413085((uint *)s_Missing_dimension_004539a8);
    uVar1 = 0;
  }
  else if (DAT_0045fc18 < 4) {
    piVar2 = FUN_00413e70();
    if (piVar2 == (int *)0x0) {
      uVar1 = 0;
    }
    else {
      for (local_c = DAT_0045fc18; 0 < local_c; local_c = local_c + -1) {
        (&DAT_0046588c)[local_c] = (&DAT_00465888)[local_c];
      }
      DAT_0046588c = piVar2[2];
      DAT_0045fc18 = DAT_0045fc18 + 1;
      FUN_004167ef(piVar2);
      uVar1 = FUN_0043b007(1);
    }
  }
  else {
    FUN_004133a9((uint *)s_Extra_dimensions_ignored_004539bc);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_0040ffe6 @ 0040ffe6 ==== */

undefined4 __cdecl FUN_0040ffe6(char *param_1)

{
  undefined4 uVar1;
  int *piVar2;
  
  if (DAT_0045f8fc < 2) {
    uVar1 = FUN_0043b007(1);
  }
  else if (DAT_0045ea80 == '\0') {
    FUN_00413085((uint *)s_Illegal_directive_outside__DEF___004539d8);
    uVar1 = 0;
  }
  else if ((param_1 == (char *)0x0) || (*param_1 == '\0')) {
    FUN_00413085((uint *)s_Missing_line_number_00453a0c);
    uVar1 = 0;
  }
  else {
    DAT_0045f860 = param_1;
    piVar2 = FUN_00413e70();
    if (piVar2 == (int *)0x0) {
      uVar1 = 0;
    }
    else {
      DAT_00465884 = piVar2[2];
      FUN_004167ef(piVar2);
      uVar1 = FUN_0043b007(1);
    }
  }
  return uVar1;
}


/* ==== FUN_0041007c @ 0041007c ==== */

undefined4 __cdecl FUN_0041007c(char *param_1)

{
  undefined4 uVar1;
  int *piVar2;
  
  if (DAT_0045ea80 == '\0') {
    if ((param_1 == (char *)0x0) || (*param_1 == '\0')) {
      FUN_00413085((uint *)s_Missing_line_number_00453a54);
      uVar1 = 0;
    }
    else {
      DAT_0045f860 = param_1;
      piVar2 = FUN_00413e70();
      if (piVar2 == (int *)0x0) {
        uVar1 = 0;
      }
      else {
        FUN_0042433e(piVar2[2]);
        FUN_004167ef(piVar2);
        uVar1 = FUN_0043b007(1);
      }
    }
  }
  else {
    FUN_00413085((uint *)s_Illegal_directive_inside__DEF__E_00453a20);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_00410100 @ 00410100 ==== */

undefined4 FUN_00410100(void)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int local_220;
  int local_21c;
  int local_218;
  int local_214;
  char local_210 [512];
  int *local_10;
  int *local_c;
  int *local_8;
  
  if (DAT_0045fbf0 == (char *)0x0) {
    local_210[0] = '\0';
  }
  else {
    strcpy(local_210,DAT_0045fbf0);
    FUN_004398b5(DAT_0045fbf0);
    DAT_0045fbf0 = (char *)0x0;
  }
  piVar1 = DAT_00463be0;
  if (DAT_0045ea80 == '\0') {
    FUN_00413085((uint *)s__ENDEF_without_associated__DEF_d_00453a68);
    FUN_00410901();
    return 0;
  }
  DAT_0045ea80 = 0;
  DAT_0045f860 = 0;
  if (((((DAT_00465a78 == 3) && ((DAT_00465a74 & 0x1000f) == 0)) || (DAT_00465a78 == 10)) ||
      ((DAT_00465a78 == 0xc || (DAT_00465a78 == 0xf)))) ||
     ((((DAT_00465a78 == 0x66 || (((DAT_00465a74 & 0x30) == 0x20 || (DAT_0045fc18 != 0)))) ||
       (DAT_00465a78 == 0x65)) ||
      ((((DAT_00465a78 == 100 || (DAT_00465a78 == 0x12)) || ((DAT_00465a74 & 0x1000f) == 8)) ||
       (((DAT_00465a74 & 0x1000f) == 9 || ((DAT_00465a74 & 0x1000f) == 10)))))))) {
    DAT_00465a7c = 1;
  }
  else {
    DAT_00465a7c = 0;
  }
  switch(DAT_00465a78) {
  case 0:
  case 5:
  case 7:
  case 0xe:
  case 0x68:
  case 0x69:
  case 0x6a:
    FUN_0043c34d();
    FUN_00410901();
    uVar2 = FUN_0043b007(0);
    return uVar2;
  case 2:
  case 3:
  case 6:
    if (DAT_0045fbf8 == '\0') {
      DAT_00465a70 = 0xffffffff;
    }
    break;
  case 10:
  case 0xc:
  case 0xf:
    DAT_00465a70 = 0xfffffffe;
    local_10 = (int *)FUN_00439857(0xc);
    *local_10 = DAT_0045fbd4;
    local_10[2] = (int)DAT_00463be0;
    DAT_0045fc08 = DAT_0045fc08 + 1;
    DAT_00465888 = DAT_0045fbf4;
    DAT_00463be0 = local_10;
    DAT_00465880 = DAT_0045fc08;
    break;
  case 0xd:
  case 0x67:
    DAT_00465a70 = 0xfffffffe;
    break;
  case 0x12:
    DAT_00465888 = DAT_0045fbf4;
  case 1:
  case 4:
  case 8:
  case 9:
  case 0xb:
  case 0x10:
  case 0x11:
    DAT_00465a70 = 0xffffffff;
    break;
  default:
    FUN_00413085((uint *)s_Invalid_storage_class_00453b4c);
    FUN_00410901();
    return 0;
  case 0x66:
    if (local_210[0] == '\0') {
      FUN_00413085((uint *)s_Missing_tag_for_end_of_structure_00453a94);
      FUN_00410901();
      return 0;
    }
    if (DAT_00463be0 == (int *)0x0) {
      FUN_00413085((uint *)s_End_of_structure_or_union_withou_00453ac0);
      FUN_00410901();
      return 0;
    }
    local_c = (int *)(DAT_0045fbd8 + *DAT_00463be0 * 0x20);
    local_10 = DAT_00463be0;
    DAT_00463be0 = (int *)DAT_00463be0[2];
    FUN_004398b5((undefined *)piVar1);
    if (((local_c[6] != 10) && (local_c[6] != 0xc)) && (local_c[6] != 0xf)) {
      FUN_00412fa0((uint *)s_Invalid_tag_storage_class_00453af8);
    }
    if (*local_c == 0) {
      local_8 = (int *)(DAT_0045fbe4 + local_c[1]);
    }
    else {
      local_8 = local_c;
    }
    if (((char)*local_8 != local_210[0]) || (iVar3 = strcmp((char *)local_8,local_210), iVar3 != 0))
    {
      FUN_00413085((uint *)s_Structure_or_union_tag_mismatch_00453b14);
      FUN_00410901();
      return 0;
    }
    DAT_00465880 = local_c[8];
    DAT_00465a70 = 0xffffffff;
    DAT_00465888 = DAT_0045fbf4;
    local_210[0] = '\0';
    break;
  case -1:
  case 100:
  case 0x65:
    if (DAT_0045f8a0 != 0) {
      FUN_00413085((uint *)s_Runtime_space_must_be_P_00453b34);
      FUN_00410901();
      return 0;
    }
    DAT_00465a70 = *(undefined4 *)(DAT_0045fb8c + 0x1c);
  }
  if ((DAT_00465a74 & 0x30) == 0x20) {
    if (DAT_0045f8a0 != 0) {
      FUN_00413085((uint *)s_Runtime_space_must_be_P_00453b64);
      FUN_00410901();
      return 0;
    }
    DAT_0046588c = FUN_0042433e(0);
  }
  if (DAT_0045fc18 != 0) {
    DAT_00465888 = DAT_0045fbf4;
  }
  if (((DAT_0045f8fc == 2) && (local_210[0] != '\0')) && (DAT_00465a78 != 0x66)) {
    local_21c = 0;
    local_220 = 0;
    local_218 = -1;
    for (local_214 = 0; local_214 < DAT_0045fbd4; local_214 = local_214 + 1) {
      local_c = (int *)(DAT_0045fbd8 + local_214 * 0x20);
      if ((local_c[6] == 0x65) && (*(char *)((int)local_c + 1) == 'b')) {
        local_220 = local_220 + 1;
      }
      if (local_c[6] == 100) {
        local_21c = local_21c + (-(uint)(*(char *)((int)local_c + 1) != 'b') & 0xfffffffe) + 1;
      }
      if ((((local_c[6] == 10) || (local_c[6] == 0xc)) || (local_c[6] == 0xf)) &&
         ((local_c[5] & 0x1000fU) == (DAT_00465a74 & 0x1000f))) {
        local_8 = local_c;
        if (*local_c == 0) {
          local_8 = (int *)(DAT_0045fbe4 + local_c[1]);
        }
        if (((char)*local_8 == local_210[0]) &&
           (iVar3 = strcmp((char *)local_8,local_210), iVar3 == 0)) {
          if (local_21c == 0) {
            local_218 = local_214;
          }
          else if ((local_220 == DAT_0045fc1c) && (local_21c <= DAT_0045fc20)) {
            local_218 = local_214;
            break;
          }
        }
        iVar3 = local_c[7];
      }
      else {
        iVar3 = local_c[7];
      }
      local_214 = local_214 + iVar3;
    }
    if (local_218 < 0) {
      FUN_00413085((uint *)s_Tag_name_not_found_00453b7c);
      FUN_00410901();
      return 0;
    }
    local_c = (int *)(DAT_0045fbd8 + local_218 * 0x20);
    DAT_00465880 = local_c[8];
    DAT_00465888 = local_c[10];
  }
  if ((((DAT_0045fbfc == 0) || (DAT_0045fbfc != DAT_0045fc00)) ||
      (*(undefined **)(DAT_0045fbfc + 0x40) != PTR_DAT_0044f978)) ||
     ((DAT_0045fbf8 == '\0' || (DAT_00465a78 == -1)))) {
    FUN_0042447e(&DAT_00465a60);
    if (0 < DAT_00465a7c) {
      FUN_0042447e(&DAT_00465880);
    }
    if ((DAT_0045f8fc < 2) && (DAT_0045fb8c != 0)) {
      *(int *)(DAT_0045fb8c + 0x20) = *(int *)(DAT_0045fb8c + 0x20) + 1;
    }
    FUN_0043c34d();
  }
  else if ((DAT_0045f8fc != 2) || (DAT_0045fc04 != '\0')) {
    if (*(int *)(DAT_0045fbfc + 0x54) == 0) {
      iVar3 = FUN_00439857(0x20);
      *(int *)(DAT_0045fbfc + 0x54) = iVar3;
    }
    puVar4 = &DAT_00465a60;
    puVar5 = *(undefined4 **)(DAT_0045fbfc + 0x54);
    for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    if (*(int *)(DAT_0045fbfc + 0x58) == 0) {
      iVar3 = FUN_00439857(0x20);
      *(int *)(DAT_0045fbfc + 0x58) = iVar3;
    }
    puVar4 = &DAT_00465880;
    puVar5 = *(undefined4 **)(DAT_0045fbfc + 0x58);
    for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
  }
  FUN_00410901();
  uVar2 = FUN_0043b007(0);
  return uVar2;
}


