/* macro: 26 functions from ASM56000 */

/* ==== FUN_0041e8ac @ 0041e8ac ==== */

void __cdecl FUN_0041e8ac(uint *param_1,uint param_2)

{
  byte bVar1;
  uint uVar2;
  void *this;
  void *this_00;
  char *local_3c;
  char *local_34;
  char *local_30;
  char *local_2c;
  uint local_20;
  int local_14;
  undefined8 local_10;
  
  DAT_00463c24 = DAT_00463c2c;
  if (param_1 == (uint *)0x0) {
    DAT_00463c2c = 1;
    DAT_00463c18 = 0;
    DAT_00463c1c = 0;
  }
  else {
    DAT_00463c2c = 0;
    if ((param_1[1] == 0x1c) || (param_1[1] == 0x11d)) {
      local_14 = 0x29;
    }
    else {
      local_14 = 0x1d;
    }
    DAT_00463c18 = DAT_00463c1c;
    DAT_00463c1c = (param_1[2] - 1) + param_1[3] & param_2;
    if (param_1[3] == 0) {
      if ((param_1[1] == 0x1c) || (param_1[1] == 0x11d)) {
        local_20 = 0x1fffff;
      }
      else {
        local_20 = 0xffff;
      }
      DAT_00463c20 = local_20;
      local_10 = (double)local_20 + 1.0;
    }
    else {
      local_10 = (double)param_1[3];
    }
    if ((param_1[1] == 0x1c) || (param_1[1] == 0x11d)) {
      local_2c = s__08lX_0044e090;
    }
    else {
      local_2c = s__04lX_0044e088;
    }
    sprintf(&DAT_0045f220,local_2c,param_1[2]);
    FUN_0041c9cf(&DAT_0045f220);
    FUN_0041c9cf(&DAT_0045552c);
    if (param_1[1] != 0x1c) {
      FUN_0041c9cf(&DAT_00455530);
    }
    if ((param_1[1] == 0x1c) || (param_1[1] == 0x11d)) {
      local_30 = s__08lX_0044e090;
    }
    else {
      local_30 = s__04lX_0044e088;
    }
    sprintf(&DAT_0045f220,local_30,DAT_00463c1c);
    FUN_0041c9cf(&DAT_0045f220);
    FUN_0041c9cf(&DAT_00455534);
    if ((param_1[1] == 0x1c) || (param_1[1] == 0x11d)) {
      local_34 = s__10_0f_0044e0a8;
    }
    else {
      local_34 = s__5_0f_0044e0a0;
    }
    sprintf(&DAT_0045f220,local_34,(undefined4)local_10,local_10._4_4_);
    FUN_0041c9cf(&DAT_0045f220);
    FUN_0041c9cf(&DAT_00455538);
    if ((*param_1 & 0xc0e) == 0) {
      FUN_0041c9cf(s_UNUSED_0045553c);
    }
    else {
      uVar2 = *param_1 & 0xc0e;
      if (uVar2 < 9) {
        if (uVar2 == 8) {
          FUN_0041c9cf(s_CONST_00455554);
        }
        else if (uVar2 == 2) {
          FUN_0041c9cf(s_CODE_00455544);
        }
        else if (uVar2 == 4) {
          FUN_0041c9cf(s_DATA_0045554c);
        }
      }
      else if (uVar2 == 0x400) {
        FUN_0041c9cf(s_MOD_0045555c);
      }
      else if (uVar2 == 0x800) {
        FUN_0041c9cf(s_REV_00455564);
      }
      if (param_1[4] != 0) {
        FUN_0041cb2d(local_14);
        DAT_0045f220 = 0;
        strncat(&DAT_0045f220,*(char **)param_1[4],0x10);
        FUN_0041c9cf(&DAT_0045f220);
      }
      if ((undefined *)param_1[5] != &DAT_0044f878) {
        FUN_0041cb2d(local_14 + 0x12);
        DAT_0045f220 = 0;
        strncat(&DAT_0045f220,*(char **)(param_1[5] + 4),0x10);
        FUN_0041c9cf(&DAT_0045f220);
      }
      if (param_1[6] == 0) {
        if ((DAT_00463c24 == 0) && (param_1[2] <= DAT_00463c18)) {
          FUN_0041cb2d(local_14 + 0x34);
          FUN_0041c9cf(s__Overlap__00455574);
        }
      }
      else {
        FUN_0041cb2d(local_14 + 0x24);
        bVar1 = FUN_0043a6c5(*(int *)(param_1[6] + 4));
        FUN_0041e011(this,bVar1);
        FUN_0041e011(this_00,0x3a);
        if ((*(int *)(param_1[6] + 4) == 0x1c) || (*(int *)(param_1[6] + 4) == 0x11d)) {
          local_3c = s__08lX_0044e090;
        }
        else {
          local_3c = s__04lX_0044e088;
        }
        sprintf(&DAT_0045f220,local_3c,*(undefined4 *)(param_1[6] + 8));
        FUN_0041c9cf(&DAT_0045f220);
        sprintf(&DAT_0045f220,&DAT_0045556c,
                (-(uint)((*(uint *)param_1[6] & 1) != 0) & 0xfffffffa) + 0x52);
        FUN_0041c9cf(&DAT_0045f220);
      }
      FUN_0041c9cf(&DAT_00455580);
    }
  }
  return;
}


/* ==== FUN_0041ed0d @ 0041ed0d ==== */

void __cdecl FUN_0041ed0d(undefined4 param_1,int param_2)

{
  DAT_0045fc80 = param_1;
  DAT_0045fb60 = FUN_0041ed35;
  FUN_004399c9(0,param_2 + -1);
  return;
}


/* ==== FUN_0041ed35 @ 0041ed35 ==== */

int __cdecl FUN_0041ed35(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0043a768(*(int *)(param_1 + 4));
  iVar2 = FUN_0043a768(*(int *)(param_2 + 4));
  if (iVar1 == iVar2) {
    iVar2 = *(int *)(param_1 + 8) - *(int *)(param_2 + 8);
    if (iVar2 < 0) {
      iVar1 = -1;
    }
    else if (iVar2 < 1) {
      iVar2 = *(int *)(param_1 + 0xc) - *(int *)(param_2 + 0xc);
      if (iVar2 < 0) {
        iVar1 = -1;
      }
      else if (iVar2 < 1) {
        iVar1 = 0;
      }
      else {
        iVar1 = 1;
      }
    }
    else {
      iVar1 = 1;
    }
  }
  else {
    iVar1 = iVar1 - iVar2;
  }
  return iVar1;
}


/* ==== FUN_0041edc3 @ 0041edc3 ==== */

void FUN_0041edc3(void)

{
  undefined *puVar1;
  undefined *local_c;
  
  local_c = DAT_0045fc7c;
  while (local_c != (undefined *)0x0) {
    puVar1 = *(undefined **)(local_c + 0x1c);
    FUN_004398b5(local_c);
    local_c = puVar1;
  }
  DAT_0045fc7c = (undefined *)0x0;
  local_c = DAT_0045fc78;
  while (local_c != (undefined *)0x0) {
    puVar1 = *(undefined **)(local_c + 0x1c);
    FUN_004398b5(local_c);
    local_c = puVar1;
  }
  DAT_0045fc78 = (undefined *)0x0;
  return;
}


/* ==== FUN_0041ee40 @ 0041ee40 ==== */

undefined4 FUN_0041ee40(void)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int *local_218;
  uint local_214 [129];
  int local_10;
  int *local_c;
  undefined *local_8;
  
  local_218 = (int *)0x0;
  local_8 = DAT_0045f860;
  DAT_0045f860 = PTR_DAT_0044f810;
  local_10 = FUN_0043b659(PTR_DAT_0044f810);
  if (local_10 == -1) {
    uVar1 = 0;
  }
  else if (local_10 == 0) {
    FUN_00413085((uint *)s_Missing_macro_name_004555bc);
    uVar1 = 0;
  }
  else {
    for (; (*PTR_DAT_0044f810 != '\0' && (*PTR_DAT_0044f810 == DAT_0044f830));
        PTR_DAT_0044f810 = PTR_DAT_0044f810 + 1) {
    }
    strcpy((char *)local_214,PTR_DAT_0044f810);
    DAT_0045f860 = (undefined *)0x0;
    local_c = FUN_0041faa5(local_214,1);
    if (local_c == (undefined4 *)0x0) {
      if (DAT_0045f8fc == 2) {
        iVar2 = FUN_00438f1a(local_214,0);
        if (iVar2 == 0) {
          iVar2 = FUN_0043903f(local_214,0);
          if (iVar2 != 0) {
            FUN_004133a9((uint *)s_Macro_name_is_the_same_as_existi_00455624);
          }
        }
        else {
          FUN_004133a9((uint *)s_Macro_name_is_the_same_as_existi_004555ec);
        }
      }
      DAT_0045f860 = local_8;
      if (*PTR_DAT_0044f818 == '\0') {
        local_10 = 0;
      }
      else {
        local_218 = FUN_0041f784(&local_10);
        if (local_218 == (int *)0x0) {
          return 0;
        }
      }
      if (DAT_0044f77c != '\0') {
        FUN_0041bdca(' ');
      }
      local_c = (int *)FUN_00439857(0x1c);
      uVar3 = strlen((char *)local_214);
      iVar2 = FUN_00439857(uVar3 + 1);
      *local_c = iVar2;
      strcpy((char *)*local_c,(char *)local_214);
      if (DAT_0045eaa0 != '\0') {
        FUN_0043b836((char *)*local_c);
      }
      local_c[1] = (int)PTR_DAT_0044f978;
      local_c[2] = DAT_0045eb80;
      local_c[3] = local_10;
      local_c[4] = (int)local_218;
      piVar4 = FUN_0041f09a(local_218);
      local_c[5] = (int)piVar4;
      local_c[6] = (int)DAT_0045fb70;
      DAT_0045fb70 = local_c;
      DAT_0045ea54 = 1;
      uVar1 = 1;
    }
    else if (DAT_0045f8fc < 2) {
      uVar1 = 0;
    }
    else {
      FUN_004131f9((uint *)s_Macro_cannot_be_redefined_004555d0,(char *)local_214);
      uVar1 = 0;
    }
  }
  return uVar1;
}


/* ==== FUN_0041f09a @ 0041f09a ==== */

int * __cdecl FUN_0041f09a(undefined4 *param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  int *piVar6;
  int local_1c;
  int *local_c;
  int *local_8;
  
  local_1c = 1;
  local_8 = (int *)0x0;
  local_c = (int *)0x0;
  piVar1 = local_c;
  piVar2 = local_8;
  do {
    local_8 = piVar2;
    local_c = piVar1;
    iVar3 = FUN_0041983e();
    if (iVar3 == 0) {
      FUN_00413085((uint *)s_Unexpected_end_of_file___missing_0045565c);
      FUN_0041f9ab(local_c);
      return (int *)0x0;
    }
    DAT_0045ea54 = '\x01' - (DAT_0044f77c != '\0');
    iVar3 = FUN_0041a4bc();
    if (iVar3 == 0) {
      FUN_0041c742(0x6d);
    }
    else {
      if ((*PTR_DAT_0044f814 != '\0') && (uVar4 = strlen(PTR_DAT_0044f814), uVar4 < 0x10)) {
        puVar5 = (uint *)FUN_00438f9c(PTR_DAT_0044f814);
        iVar3 = FUN_0043903f(puVar5,1);
        if (iVar3 != 0) {
          if (*(char *)(iVar3 + 4) == '\x16') {
            local_1c = local_1c + -1;
            if (local_1c == 0) {
              FUN_0042baac(0);
              FUN_0043b007(0);
              if (DAT_0044f77c == '\0') {
                return local_c;
              }
              FUN_0041bdca('m');
              return local_c;
            }
          }
          else if ((((*(char *)(iVar3 + 4) == '%') || (*(char *)(iVar3 + 4) == '\x0e')) ||
                   (*(char *)(iVar3 + 4) == '\x0f')) ||
                  ((*(char *)(iVar3 + 4) == '\x10' || (*(char *)(iVar3 + 4) == '\x11')))) {
            local_1c = local_1c + 1;
          }
        }
      }
      FUN_0041bdca('m');
    }
    piVar6 = FUN_0041f234(param_1);
    piVar1 = local_c;
    piVar2 = local_8;
    if ((piVar6 != (int *)0x0) && (piVar1 = piVar6, piVar2 = piVar6, local_c != (int *)0x0)) {
      local_8[2] = (int)piVar6;
      piVar1 = local_c;
    }
  } while( true );
}


/* ==== FUN_0041f234 @ 0041f234 ==== */

int * __cdecl FUN_0041f234(undefined4 *param_1)

{
  bool bVar1;
  uint uVar2;
  uint *extraout_EAX;
  int *piVar3;
  uint local_41c;
  uint *local_418;
  uint local_410 [129];
  uint *local_20c;
  undefined4 local_208 [128];
  char *local_8;
  
  local_418 = (uint *)0x0;
  bVar1 = false;
  local_8 = &DAT_0045ec08;
  local_20c = local_410;
  memset(local_208,0,0x200);
  do {
    while (bVar1) {
LAB_0041f4bf:
      if (*local_8 == '\0') {
        if ((local_20c == local_410) && (DAT_0044f784 == '\0')) {
          return (int *)0x0;
        }
        *(char *)local_20c = '\0';
        piVar3 = FUN_0041f6e2(local_410,local_208);
        return piVar3;
      }
      if (*local_8 == '\'') {
        bVar1 = !bVar1;
      }
      if ((*local_8 != '\"') || (bVar1)) {
        *(char *)local_20c = *local_8;
      }
      else {
        *(char *)local_20c = '\'';
      }
      local_8 = local_8 + 1;
      local_20c = (uint *)((int)local_20c + 1);
    }
    if (__mb_cur_max < 2) {
      local_41c = *(ushort *)(_pctype + *local_8 * 2) & 0x107;
    }
    else {
      local_41c = _isctype((int)*local_8,0x107);
    }
    if ((local_41c != 0) || (*local_8 == '_')) {
      if (local_418 == (uint *)0x0) {
        local_418 = local_20c;
      }
      goto LAB_0041f4bf;
    }
    if (local_418 != (uint *)0x0) {
      FUN_0041f58e((char *)local_418,(char *)local_20c,(int)local_410,(int)local_208,param_1,
                   (uint)(local_418 == local_410));
      local_418 = (uint *)0x0;
      local_20c = extraout_EAX;
    }
    if ((*local_8 != '\\') || (local_8[1] != '\"')) {
      if (*local_8 != ';') goto LAB_0041f4bf;
      if (local_8[1] == ';') {
        if (local_20c == local_410) {
          return (int *)0x0;
        }
        *(char *)local_20c = '\0';
        piVar3 = FUN_0041f6e2(local_410,local_208);
        return piVar3;
      }
      if (DAT_0044f784 != '\0') {
        do {
          *(char *)local_20c = *local_8;
          uVar2 = *local_20c;
          local_20c = (uint *)((int)local_20c + 1);
          local_8 = local_8 + 1;
        } while ((char)uVar2 != '\0');
        piVar3 = FUN_0041f6e2(local_410,local_208);
        return piVar3;
      }
      break;
    }
    local_8 = local_8 + 2;
    *(char *)local_20c = '\"';
    local_20c = (uint *)((int)local_20c + 1);
  } while( true );
  while (*(char *)local_20c != '\t') {
    if ((local_20c == local_410) ||
       (local_20c = (uint *)((int)local_20c + -1), *(char *)local_20c == ' ')) break;
  }
  if (local_20c == local_410) {
    piVar3 = (int *)0x0;
  }
  else {
    *(char *)local_20c = '\0';
    piVar3 = FUN_0041f6e2(local_410,local_208);
  }
  return piVar3;
}


/* ==== FUN_0041f58e @ 0041f58e ==== */

/* WARNING: Variable defined which should be unmapped: param_2 */

char * __cdecl
FUN_0041f58e(char *param_1,char *param_2,int param_3,int param_4,undefined4 *param_5,int param_6)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  char local_8;
  
  local_8 = '\x01';
  if (param_5 != (undefined4 *)0x0) {
    *param_2 = '\0';
    uVar1 = strlen(param_1);
    if (uVar1 < 0x201) {
      do {
        if ((*param_1 == *(char *)*param_5) &&
           (iVar2 = strcmp(param_1,(char *)*param_5), iVar2 == 0)) {
          if (param_6 == 0) {
            if (param_1[-1] == '?') {
              param_1 = param_1 + -1;
              local_8 = '\x02';
            }
            else if (param_1[-1] == '%') {
              param_1 = param_1 + -1;
              local_8 = '\x03';
            }
            if (param_1[-1] == '\\') {
              param_1 = param_1 + -1;
            }
          }
          *param_1 = '\x01';
          param_1[1] = local_8;
          param_1[2] = *(char *)(param_5 + 1);
          memset(param_1 + (param_4 - param_3),1,3);
          return param_2;
        }
        param_5 = (undefined4 *)param_5[2];
      } while (param_5 != (undefined4 *)0x0);
      if ((param_6 == 0) && (pcVar3 = param_1 + -1, *pcVar3 == '\\')) {
        *pcVar3 = '\x02';
        pcVar3[param_4 - param_3] = '\x01';
      }
    }
  }
  return param_2;
}


/* ==== FUN_0041f6e2 @ 0041f6e2 ==== */

int * __cdecl FUN_0041f6e2(uint *param_1,undefined4 *param_2)

{
  uint n;
  int *piVar1;
  int iVar2;
  
  n = strlen((char *)param_1);
  piVar1 = (int *)FUN_00439857(0xc);
  iVar2 = FUN_00439857(n + 1);
  *piVar1 = iVar2;
  iVar2 = FUN_00439857(n + 1);
  piVar1[1] = iVar2;
  strcpy((char *)*piVar1,(char *)param_1);
  if (param_2 == (undefined4 *)0x0) {
    memset((void *)piVar1[1],0,n);
  }
  else {
    memcpy((void *)piVar1[1],param_2,n);
  }
  piVar1[2] = 0;
  return piVar1;
}


/* ==== FUN_0041f784 @ 0041f784 ==== */

int * __cdecl FUN_0041f784(int *param_1)

{
  char cVar1;
  int *piVar2;
  char *a;
  uint uVar3;
  int iVar4;
  int local_18;
  int *local_14;
  int *local_10;
  int *local_c;
  
  local_10 = (int *)0x0;
  local_18 = 0;
  DAT_0045f860 = PTR_DAT_0044f818;
  while( true ) {
    if (*DAT_0045f860 == '\0') {
      *param_1 = local_18;
      return local_10;
    }
    if (*DAT_0045f860 == DAT_0044f830) {
      if (local_10 != (int *)0x0) {
        FUN_0041f961(local_10);
      }
      FUN_00413085((uint *)s_Syntax_error_in_dummy_argument_l_00455684);
      return (int *)0x0;
    }
    a = FUN_0043b448();
    if (a == (char *)0x0) {
      if (local_10 != (int *)0x0) {
        FUN_0041f961(local_10);
      }
      return (int *)0x0;
    }
    if ((*DAT_0045f860 != '\0') &&
       (cVar1 = *DAT_0045f860, DAT_0045f860 = DAT_0045f860 + 1, cVar1 != ',')) break;
    if (local_10 == (int *)0x0) {
      local_14 = (int *)FUN_00439857(0xc);
      local_10 = local_14;
    }
    else {
      local_c = local_10;
      piVar2 = local_c;
      do {
        local_c = piVar2;
        if ((*a == *(char *)*local_c) && (iVar4 = strcmp(a,(char *)*local_c), iVar4 == 0)) {
          FUN_0041f961(local_10);
          FUN_004131f9((uint *)s_Two_dummy_arguments_are_the_same_004556cc,a);
          return (int *)0x0;
        }
        piVar2 = (int *)local_c[2];
      } while (local_c[2] != 0);
      iVar4 = FUN_00439857(0xc);
      local_c[2] = iVar4;
      local_14 = (int *)local_c[2];
    }
    local_14[2] = 0;
    uVar3 = strlen(a);
    iVar4 = FUN_00439857(uVar3 + 1);
    *local_14 = iVar4;
    strcpy((char *)*local_14,a);
    local_18 = local_18 + 1;
    local_14[1] = local_18;
  }
  if (local_10 != (int *)0x0) {
    FUN_0041f961(local_10);
  }
  FUN_00413085((uint *)s_Syntax_error_in_dummy_argument_l_004556a8);
  return (int *)0x0;
}


/* ==== FUN_0041f961 @ 0041f961 ==== */

void __cdecl FUN_0041f961(int *param_1)

{
  int *piVar1;
  
  while (param_1 != (int *)0x0) {
    if (*param_1 != 0) {
      FUN_004398b5((undefined *)*param_1);
      *param_1 = 0;
    }
    piVar1 = (int *)param_1[2];
    FUN_004398b5((undefined *)param_1);
    param_1 = piVar1;
  }
  return;
}


/* ==== FUN_0041f9ab @ 0041f9ab ==== */

void __cdecl FUN_0041f9ab(int *param_1)

{
  int *piVar1;
  
  while (param_1 != (int *)0x0) {
    if (*param_1 != 0) {
      FUN_004398b5((undefined *)*param_1);
      *param_1 = 0;
    }
    if (param_1[1] != 0) {
      FUN_004398b5((undefined *)param_1[1]);
      param_1[1] = 0;
    }
    piVar1 = (int *)param_1[2];
    FUN_004398b5((undefined *)param_1);
    param_1 = piVar1;
  }
  return;
}


/* ==== FUN_0041fa17 @ 0041fa17 ==== */

void FUN_0041fa17(void)

{
  int *piVar1;
  int *local_c;
  
  local_c = DAT_0045fb70;
  while (local_c != (int *)0x0) {
    if (*local_c != 0) {
      FUN_004398b5((undefined *)*local_c);
      *local_c = 0;
    }
    if (local_c[5] != 0) {
      FUN_0041f9ab((int *)local_c[5]);
    }
    if (local_c[4] != 0) {
      FUN_0041f961((int *)local_c[4]);
    }
    piVar1 = (int *)local_c[6];
    FUN_004398b5((undefined *)local_c);
    local_c = piVar1;
  }
  DAT_0045fb70 = (int *)0x0;
  return;
}


/* ==== FUN_0041faa5 @ 0041faa5 ==== */

undefined4 * __cdecl FUN_0041faa5(uint *param_1,int param_2)

{
  int iVar1;
  undefined4 *local_210;
  uint local_20c [129];
  undefined4 *local_8;
  
  local_210 = (undefined4 *)0x0;
  if (DAT_0045eaa0 != '\0') {
    strcpy((char *)local_20c,(char *)param_1);
    FUN_0043b836((char *)local_20c);
    param_1 = local_20c;
  }
  for (local_8 = DAT_0045fb70; local_8 != (undefined4 *)0x0; local_8 = (undefined4 *)local_8[6]) {
    if (((char)*param_1 == *(char *)*local_8) &&
       (iVar1 = strcmp((char *)param_1,(char *)*local_8), iVar1 == 0)) {
      if ((undefined *)local_8[1] == PTR_DAT_0044f978) break;
      if (((param_2 != 1) && (local_210 == (undefined4 *)0x0)) &&
         ((undefined *)local_8[1] == &DAT_0044f878)) {
        local_210 = local_8;
      }
    }
  }
  if ((local_8 == (undefined4 *)0x0) && (local_210 != (undefined4 *)0x0)) {
    local_8 = local_210;
  }
  return local_8;
}


/* ==== FUN_0041fb89 @ 0041fb89 ==== */

undefined4 FUN_0041fb89(void)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int local_c;
  
  FUN_0043b007(1);
  DAT_0045ea54 = '\x01' - (DAT_0044f77c != '\0');
  DAT_0045f860 = PTR_DAT_0044f818;
  piVar1 = FUN_00413e70();
  if (piVar1 == (int *)0x0) {
    FUN_0041bdca(' ');
    FUN_00420504();
    uVar2 = 0;
  }
  else if (piVar1[4] == 0x100) {
    if ((piVar1[6] & 0x8000000U) == 0) {
      FUN_0041bdca(' ');
      local_c = piVar1[2];
      FUN_004167ef(piVar1);
      if (local_c < 1) {
        FUN_00420504();
        uVar2 = 1;
      }
      else {
        piVar1 = FUN_0041f09a((undefined4 *)0x0);
        if (piVar1 == (int *)0x0) {
          DAT_0045ea54 = '\x01';
          uVar2 = 0;
        }
        else {
          while (local_c != 0) {
            puVar3 = FUN_00420b7b(piVar1);
            FUN_00420cd5((undefined *)puVar3);
            local_c = local_c + -1;
          }
          DAT_0045ea54 = '\x01';
          FUN_0041f9ab(piVar1);
          uVar2 = 1;
        }
      }
    }
    else {
      FUN_00413085((uint *)s_Expression_contains_forward_refe_00455710);
      FUN_004167ef(piVar1);
      FUN_0041bdca(' ');
      FUN_00420504();
      uVar2 = 0;
    }
  }
  else {
    FUN_00413085((uint *)s_Count_must_be_an_integer_value_004556f0);
    FUN_004167ef(piVar1);
    FUN_0041bdca(' ');
    FUN_00420504();
    uVar2 = 0;
  }
  return uVar2;
}


/* ==== FUN_0041fcec @ 0041fcec ==== */

undefined4 FUN_0041fcec(void)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int *local_14;
  int local_c;
  int *local_8;
  
  local_c = 0;
  FUN_0043b007(1);
  DAT_0045ea54 = '\x01' - (DAT_0044f77c != '\0');
  DAT_0045f860 = PTR_DAT_0044f818;
  piVar1 = FUN_004203ff();
  if (piVar1 == (int *)0x0) {
    FUN_0041bdca(' ');
    FUN_00420504();
    uVar2 = 0;
  }
  else if (*DAT_0045f860 == '\0') {
    FUN_0041bdca(' ');
    FUN_0041f961(piVar1);
    FUN_00420504();
    uVar2 = 1;
  }
  else {
    local_14 = FUN_00420dc7(&local_c);
    if (local_14 == (int *)0x0) {
      FUN_0041bdca(' ');
      FUN_0041f961(piVar1);
      FUN_00420504();
      uVar2 = 0;
    }
    else {
      FUN_0041bdca(' ');
      local_8 = FUN_0041f09a(piVar1);
      FUN_0041f961(piVar1);
      if (local_8 == (int *)0x0) {
        FUN_00420f8c(local_14);
        DAT_0045ea54 = '\x01';
        uVar2 = 0;
      }
      else {
        while (local_14 != (int *)0x0) {
          puVar3 = FUN_00420b7b(local_8);
          puVar3[5] = local_14;
          local_14 = (int *)local_14[1];
          *(undefined4 *)(puVar3[5] + 4) = 0;
          puVar3[1] = 1;
          FUN_00420cd5((undefined *)puVar3);
        }
        DAT_0045ea54 = '\x01';
        FUN_0041f9ab(local_8);
        uVar2 = 1;
      }
    }
  }
  return uVar2;
}


/* ==== FUN_0041fe57 @ 0041fe57 ==== */

undefined4 FUN_0041fe57(void)

{
  int *piVar1;
  undefined4 uVar2;
  uint uVar3;
  char *dst;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  char *pcVar7;
  char *local_18;
  char *local_10;
  
  FUN_0043b007(1);
  DAT_0045ea54 = '\x01' - (DAT_0044f77c != '\0');
  DAT_0045f860 = PTR_DAT_0044f818;
  piVar1 = FUN_004203ff();
  if (piVar1 == (int *)0x0) {
    FUN_0041bdca(' ');
    FUN_00420504();
    uVar2 = 0;
  }
  else if (*DAT_0045f860 == '\0') {
    FUN_0041bdca(' ');
    FUN_0041f961(piVar1);
    FUN_00420504();
    uVar2 = 1;
  }
  else {
    if (((*DAT_0045f860 == '\'') || (*DAT_0045f860 == '\"')) || (*DAT_0045f860 == '[')) {
      DAT_0045f860 = FUN_0043b08d(DAT_0045f860,&DAT_0045f220);
      if (*DAT_0045f860 != '\0') {
        FUN_00413085((uint *)s_Syntax_error_in_macro_argument_l_00455738);
        FUN_0041bdca(' ');
        FUN_0041f961(piVar1);
        FUN_00420504();
        return 0;
      }
    }
    else {
      for (local_10 = &DAT_0045f220; *local_10 != '\0'; local_10 = local_10 + 1) {
        *local_10 = *DAT_0045f860;
        DAT_0045f860 = DAT_0045f860 + 1;
      }
    }
    uVar3 = strlen(&DAT_0045f220);
    dst = (char *)FUN_00439857(uVar3 + 1);
    strcpy(dst,&DAT_0045f220);
    FUN_0041bdca(' ');
    piVar4 = FUN_0041f09a(piVar1);
    FUN_0041f961(piVar1);
    local_18 = dst;
    if (piVar4 == (int *)0x0) {
      FUN_004398b5(dst);
      DAT_0045ea54 = '\x01';
      uVar2 = 0;
    }
    else {
      while (*local_18 != '\0') {
        puVar5 = FUN_00420b7b(piVar4);
        iVar6 = FUN_00439857(8);
        puVar5[5] = iVar6;
        pcVar7 = (char *)FUN_00439857(2);
        *pcVar7 = *local_18;
        local_18 = local_18 + 1;
        pcVar7[1] = '\0';
        *(char **)puVar5[5] = pcVar7;
        *(undefined4 *)(puVar5[5] + 4) = 0;
        puVar5[1] = 1;
        FUN_00420cd5((undefined *)puVar5);
      }
      DAT_0045ea54 = '\x01';
      FUN_004398b5(dst);
      FUN_0041f9ab(piVar4);
      uVar2 = 1;
    }
  }
  return uVar2;
}


/* ==== FUN_004200bc @ 004200bc ==== */

undefined4 FUN_004200bc(void)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  char *buf;
  int local_24;
  int local_10;
  int local_c;
  
  FUN_0043b007(1);
  DAT_0045ea54 = '\x01' - (DAT_0044f77c != '\0');
  DAT_0045f860 = PTR_DAT_0044f818;
  piVar3 = FUN_004203ff();
  if (piVar3 == (int *)0x0) {
    FUN_0041bdca(' ');
    FUN_00420504();
    return 0;
  }
  if (*DAT_0045f860 == '\0') {
    FUN_0041bdca(' ');
    FUN_0041f961(piVar3);
    FUN_00420504();
    return 1;
  }
  if (*DAT_0045f860 == ',') {
    local_24 = 0;
  }
  else {
    piVar4 = FUN_00413e70();
    if (piVar4 == (int *)0x0) {
      FUN_0041bdca(' ');
      FUN_0041f961(piVar3);
      FUN_00420504();
      return 0;
    }
    local_24 = piVar4[2];
    FUN_004167ef(piVar4);
  }
  cVar1 = *DAT_0045f860;
  DAT_0045f860 = DAT_0045f860 + 1;
  if (cVar1 != ',') {
    FUN_00413085((uint *)s_Syntax_error_in_macro_argument_l_0045575c);
    FUN_0041bdca(' ');
    FUN_0041f961(piVar3);
    FUN_00420504();
    return 0;
  }
  piVar4 = FUN_00413e70();
  if (piVar4 == (int *)0x0) {
    FUN_0041bdca(' ');
    FUN_0041f961(piVar3);
    FUN_00420504();
    return 0;
  }
  iVar2 = piVar4[2];
  FUN_004167ef(piVar4);
  if (*DAT_0045f860 == ',') {
    DAT_0045f860 = DAT_0045f860 + 1;
    piVar4 = FUN_00413e70();
    if (piVar4 == (int *)0x0) {
      FUN_0041bdca(' ');
      FUN_0041f961(piVar3);
      FUN_00420504();
      return 0;
    }
    local_c = piVar4[2];
    FUN_004167ef(piVar4);
    if (local_c == 0) {
      FUN_00413085((uint *)s_Increment_value_cannot_be_zero_004557a4);
      FUN_0041bdca(' ');
      FUN_0041f961(piVar3);
      FUN_00420504();
      return 0;
    }
  }
  else {
    local_c = 1;
    if (*DAT_0045f860 != '\0') {
      FUN_00413085((uint *)s_Syntax_error_in_macro_argument_l_00455780);
      FUN_0041bdca(' ');
      FUN_0041f961(piVar3);
      FUN_00420504();
      return 0;
    }
  }
  FUN_0041bdca(' ');
  piVar4 = FUN_0041f09a(piVar3);
  FUN_0041f961(piVar3);
  if (piVar4 == (int *)0x0) {
    DAT_0045ea54 = 1;
    return 0;
  }
  local_10 = local_24;
  do {
    if (local_c < 1) {
      if (local_10 < iVar2) goto LAB_004203e3;
    }
    else if (iVar2 < local_10) {
LAB_004203e3:
      DAT_0045ea54 = 1;
      FUN_0041f9ab(piVar4);
      return 1;
    }
    puVar5 = FUN_00420b7b(piVar4);
    iVar6 = FUN_00439857(8);
    puVar5[5] = iVar6;
    buf = (char *)FUN_00439857(0xc);
    sprintf(buf,&DAT_004557c4,local_10);
    *(char **)puVar5[5] = buf;
    *(undefined4 *)(puVar5[5] + 4) = 0;
    puVar5[1] = 1;
    FUN_00420cd5((undefined *)puVar5);
    local_10 = local_10 + local_c;
  } while( true );
}


/* ==== FUN_004203ff @ 004203ff ==== */

int * FUN_004203ff(void)

{
  char cVar1;
  int *piVar2;
  char *s;
  uint uVar3;
  int iVar4;
  
  if (*PTR_DAT_0044f818 == '\0') {
    FUN_00413085((uint *)s_Missing_argument_004557c8);
    piVar2 = (int *)0x0;
  }
  else {
    DAT_0045f860 = PTR_DAT_0044f818;
    if (*PTR_DAT_0044f818 == DAT_0044f830) {
      FUN_004131f9((uint *)s_Invalid_dummy_argument_name_004557dc,PTR_DAT_0044f818);
      piVar2 = (int *)0x0;
    }
    else {
      s = FUN_0043b448();
      if (s == (char *)0x0) {
        piVar2 = (int *)0x0;
      }
      else if ((*DAT_0045f860 == '\0') ||
              (cVar1 = *DAT_0045f860, DAT_0045f860 = DAT_0045f860 + 1, cVar1 == ',')) {
        piVar2 = (int *)FUN_00439857(0xc);
        piVar2[2] = 0;
        uVar3 = strlen(s);
        iVar4 = FUN_00439857(uVar3 + 1);
        *piVar2 = iVar4;
        strcpy((char *)*piVar2,s);
        piVar2[1] = 1;
      }
      else {
        FUN_00413085((uint *)s_Syntax_error_in_dummy_argument_l_004557f8);
        piVar2 = (int *)0x0;
      }
    }
  }
  return piVar2;
}


/* ==== FUN_00420504 @ 00420504 ==== */

void FUN_00420504(void)

{
  int *piVar1;
  
  piVar1 = FUN_0041f09a((undefined4 *)0x0);
  FUN_0041f9ab(piVar1);
  DAT_0045ea54 = 1;
  return;
}


/* ==== FUN_0042052c @ 0042052c ==== */

undefined4 FUN_0042052c(void)

{
  char cVar1;
  char *a;
  int iVar2;
  int *local_10;
  int *local_c;
  
  FUN_0043b007(1);
  DAT_0045f860 = PTR_DAT_0044f818;
  if (*PTR_DAT_0044f818 == '\0') {
    FUN_00413085((uint *)s_Missing_macro_name_0045581c);
  }
  else {
    do {
      if (*DAT_0045f860 == '\0') {
        return 1;
      }
      if (*DAT_0045f860 == DAT_0044f830) {
        FUN_00413085((uint *)s_Invalid_macro_name_00455830);
        return 0;
      }
      a = FUN_0043b448();
      if (a == (char *)0x0) {
        return 0;
      }
      local_10 = DAT_0045fb70;
      local_c = DAT_0045fb70;
      while ((local_c != (int *)0x0 &&
             ((*a != *(char *)*local_c || (iVar2 = strcmp(a,(char *)*local_c), iVar2 != 0))))) {
        local_10 = local_c;
        local_c = (int *)local_c[6];
      }
      if (local_c == (int *)0x0) {
        FUN_004131f9((uint *)s_Macro_not_defined_00455844,a);
      }
      else {
        if (*local_c != 0) {
          FUN_004398b5((undefined *)*local_c);
          *local_c = 0;
        }
        if (local_c[5] != 0) {
          FUN_0041f9ab((int *)local_c[5]);
        }
        if (local_c[4] != 0) {
          FUN_0041f961((int *)local_c[4]);
        }
        if (local_c == DAT_0045fb70) {
          DAT_0045fb70 = (int *)local_c[6];
        }
        else {
          local_10[6] = local_c[6];
        }
        FUN_004398b5((undefined *)local_c);
      }
    } while ((*DAT_0045f860 == '\0') ||
            (cVar1 = *DAT_0045f860, DAT_0045f860 = DAT_0045f860 + 1, cVar1 == ','));
    FUN_00413085((uint *)s_Syntax_error_in_macro_name_list_00455858);
  }
  return 0;
}


/* ==== FUN_004206ea @ 004206ea ==== */

undefined4 __cdecl FUN_004206ea(uint *param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined4 uVar2;
  int extraout_EAX;
  int extraout_EAX_00;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  uint *local_14;
  int local_c;
  undefined4 *local_8;
  
  local_c = 0;
  bVar1 = FUN_00420936(param_1);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    uVar2 = 0;
  }
  else {
    for (local_8 = DAT_0045fc64; local_8 != (undefined4 *)0x0; local_8 = (undefined4 *)local_8[2]) {
      strcpy(&DAT_0045f220,(char *)*local_8);
      strcat(&DAT_0045f220,(char *)param_1);
      fopen(&DAT_0045f220,&DAT_00455878);
      if (extraout_EAX != 0) {
        local_c = extraout_EAX;
        if (DAT_0045eb4c != '\0') {
          fprintf(PTR_DAT_0044f9a4,s__s__Opening_macro_file__s_0045587c,PTR_s_asm56000_0044e084,
                  &DAT_0045f220);
        }
        break;
      }
      FUN_00402bfa((uint *)&DAT_00455898);
      fopen(&DAT_0045f220,&DAT_004558a0);
      local_c = extraout_EAX_00;
      if (extraout_EAX_00 != 0) {
        if (DAT_0045eb4c != '\0') {
          fprintf(PTR_DAT_0044f9a4,s__s__Opening_macro_file__s_004558a4,PTR_s_asm56000_0044e084,
                  &DAT_0045f220);
        }
        break;
      }
    }
    if (local_8 == (undefined4 *)0x0) {
      uVar2 = 0;
    }
    else {
      puVar3 = (undefined4 *)FUN_00439857(0x18);
      *puVar3 = PTR_DAT_0044f80c;
      puVar3[1] = DAT_0045f900;
      puVar3[2] = DAT_0044f954;
      DAT_0045eb7c = DAT_0045eb7c + -1;
      puVar3[3] = DAT_0045eb7c;
      uVar4 = strlen(&DAT_0045ec08);
      iVar5 = FUN_00439857(uVar4 + 1);
      puVar3[4] = iVar5;
      strcpy((char *)puVar3[4],&DAT_0045ec08);
      puVar3[5] = DAT_0045fc28;
      DAT_0044f954 = DAT_0044f954 + 1;
      DAT_0045fc28 = puVar3;
      FUN_00402cde((uint *)&DAT_0045f220);
      DAT_0045f900 = local_c;
      DAT_0045eb7c = 0;
      DAT_0045eb80 = DAT_0045eb80 + -1;
      FUN_0041a3ce(1);
      if (DAT_0045eae0 == '\0') {
        if (DAT_0045eb24 == '\0') {
          local_14 = (uint *)PTR_DAT_0044f80c;
        }
        else {
          local_14 = DAT_0045f858;
        }
        FUN_0040f5d5((uint *)&DAT_004558c0,local_14,(char *)0x0,0);
        FUN_00435d9f();
        FUN_00435eca(PTR_DAT_0044f978,0);
      }
      DAT_0045ea54 = 1;
      uVar2 = 1;
    }
  }
  return uVar2;
}


/* ==== FUN_00420936 @ 00420936 ==== */

bool __cdecl FUN_00420936(uint *param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int *local_8;
  
  for (local_8 = DAT_0045fb78;
      (local_8 != (int *)0x0 &&
      (((*(char *)*local_8 != (char)*param_1 ||
        (iVar1 = strcmp((char *)*local_8,(char *)param_1), iVar1 != 0)) ||
       ((undefined *)local_8[2] != PTR_DAT_0044f978)))); local_8 = (int *)local_8[4]) {
  }
  if (local_8 == (int *)0x0) {
    piVar2 = (int *)FUN_00439857(0x14);
    uVar3 = strlen((char *)param_1);
    iVar1 = FUN_00439857(uVar3 + 1);
    *piVar2 = iVar1;
    strcpy((char *)*piVar2,(char *)param_1);
    piVar2[2] = (int)PTR_DAT_0044f978;
    piVar2[4] = (int)DAT_0045fb78;
    DAT_0045fb78 = piVar2;
  }
  return local_8 == (int *)0x0;
}


/* ==== FUN_004209f8 @ 004209f8 ==== */

undefined4 __cdecl FUN_004209f8(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int *piVar3;
  int local_8;
  
  local_8 = 0;
  FUN_0043b007(1);
  DAT_0045ea54 = '\x01' - (DAT_0044f780 != '\0');
  if (param_1[5] == 0) {
    FUN_0041bdca(' ');
    uVar1 = 0;
  }
  else {
    if ((PTR_DAT_0044f810 != (undefined *)0x0) && (*PTR_DAT_0044f810 != '\0')) {
      FUN_0043797a();
    }
    puVar2 = FUN_00420b7b((undefined4 *)param_1[5]);
    *puVar2 = param_1;
    DAT_0045f860 = PTR_DAT_0044f818;
    if (*PTR_DAT_0044f818 != '\0') {
      piVar3 = FUN_00420dc7(&local_8);
      puVar2[5] = piVar3;
      if (puVar2[5] == 0) {
        FUN_00420f6c((undefined *)puVar2);
        FUN_0041bdca(' ');
        DAT_0045ea54 = 1;
        return 0;
      }
    }
    puVar2[1] = local_8;
    if ((int)param_1[3] < local_8) {
      FUN_004133a9((uint *)s_Number_of_macro_expansion_argume_004558c8);
    }
    else if (local_8 < (int)param_1[3]) {
      FUN_004133a9((uint *)s_Number_of_macro_expansion_argume_00455908);
    }
    FUN_0041bdca(' ');
    if (DAT_0045fb6c == 0) {
      DAT_0045ea58 = 1;
    }
    FUN_004210b0(param_1,1);
    FUN_00420cd5((undefined *)puVar2);
    FUN_004210b0(param_1,0);
    if (DAT_0045eadc != '\0') {
      FUN_00435d9f();
      FUN_00435eca(PTR_DAT_0044f978,0);
    }
    uVar1 = 1;
  }
  DAT_0045ea54 = 1;
  return uVar1;
}


/* ==== FUN_00420b7b @ 00420b7b ==== */

undefined4 * __cdecl FUN_00420b7b(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)FUN_00439857(0x2c);
  *puVar3 = 0;
  puVar3[1] = 0;
  puVar3[5] = 0;
  puVar3[2] = param_1;
  puVar3[3] = 0;
  puVar3[4] = *param_1;
  puVar3[6] = 0;
  puVar3[7] = DAT_0045eb80;
  puVar3[8] = 0;
  if (DAT_0045fb6c == 0) {
    puVar3[9] = 0;
  }
  else {
    puVar3[9] = DAT_0045fc4c;
  }
  if (DAT_0045f8fc < 2) {
    DAT_0045fc4c = (undefined4 *)FUN_00439857(0xc);
    DAT_0045fc4c[1] = 0;
    *DAT_0045fc4c = DAT_0045eb80;
    DAT_0045fc4c[2] = 0;
    puVar1 = DAT_0045fc4c;
    puVar2 = DAT_0045fc4c;
    if (DAT_0045fc48 != (undefined4 *)0x0) {
      DAT_0045fc50[2] = DAT_0045fc4c;
      puVar1 = DAT_0045fc48;
      puVar2 = DAT_0045fc4c;
    }
  }
  else {
    puVar1 = DAT_0045fc48;
    puVar2 = DAT_0045fc50;
    if (DAT_0045f8fc == 2) {
      if (DAT_0045fc50 == (undefined4 *)0x0) {
        DAT_0045fc50 = DAT_0045fc48;
      }
      else {
        DAT_0045fc50 = (undefined4 *)DAT_0045fc50[2];
      }
      DAT_0045fc4c = DAT_0045fc50;
      puVar3[8] = DAT_0045fc50[1];
      puVar1 = DAT_0045fc48;
      puVar2 = DAT_0045fc50;
    }
  }
  DAT_0045fc50 = puVar2;
  DAT_0045fc48 = puVar1;
  return puVar3;
}


/* ==== FUN_00420cd5 @ 00420cd5 ==== */

void __cdecl FUN_00420cd5(undefined *param_1)

{
  int iVar1;
  
  *(undefined **)(param_1 + 0x28) = DAT_0045fb6c;
  DAT_0045fb6c = param_1;
  FUN_0041a3ce(2);
  if (DAT_0045eadc != '\0') {
    FUN_00435d9f();
    FUN_00435eca(PTR_DAT_0044f978,0);
  }
  while( true ) {
    iVar1 = FUN_0041983e();
    if (iVar1 == 0) break;
    FUN_0041d334();
    iVar1 = FUN_0041a4bc();
    if (iVar1 == 0) {
      FUN_0041c742(0x20);
    }
    else {
      FUN_0041af7e(0,0);
      FUN_0041bdca(' ');
    }
    DAT_0045f924 = 0;
    DAT_0045f928 = 0;
    DAT_0045f92c = 0;
  }
  iVar1 = FUN_0041a3ff();
  if (iVar1 != 2) {
    FUN_00412fa0((uint *)s_Input_mode_stack_out_of_sequence_00455944);
  }
  if (*(int *)(param_1 + 0x24) == 0) {
    DAT_0045fc4c = DAT_0045fc50;
  }
  else {
    DAT_0045fc4c = *(undefined4 *)(param_1 + 0x24);
  }
  DAT_0045fb6c = *(undefined **)(DAT_0045fb6c + 0x28);
  FUN_00420f6c(param_1);
  return;
}


