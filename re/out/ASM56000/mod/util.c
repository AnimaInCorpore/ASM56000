/* util: 139 functions from ASM56000 */

/* ==== FUN_00438b28 @ 00438b28 ==== */

undefined4 * __cdecl FUN_00438b28(uint *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 *local_20c;
  uint local_208 [129];
  
  if (DAT_0045eaa0 != '\0') {
    strcpy((char *)local_208,(char *)param_1);
    FUN_0043b836((char *)local_208);
    param_1 = local_208;
  }
  uVar1 = FUN_00439b65((char *)param_1);
  DAT_0045fc54 = *(undefined4 **)(&DAT_00461c50 + uVar1 * 4);
  for (local_20c = DAT_0045fc54;
      (local_20c != (undefined4 *)0x0 &&
      (((DAT_0045fc54 = local_20c, (char)*param_1 != *(char *)*local_20c ||
        (iVar2 = strcmp((char *)param_1,(char *)*local_20c), iVar2 != 0)) ||
       ((undefined *)local_20c[2] != PTR_DAT_0044f978)))); local_20c = (undefined4 *)local_20c[4]) {
  }
  return local_20c;
}


/* ==== FUN_00438c00 @ 00438c00 ==== */

int * __cdecl FUN_00438c00(char *param_1)

{
  uint uVar1;
  int iVar2;
  int *local_8;
  
  uVar1 = FUN_00439b65(param_1);
  DAT_0045fc58 = *(int **)(&DAT_00462c18 + uVar1 * 4);
  local_8 = DAT_0045fc58;
  while( true ) {
    if (local_8 == (int *)0x0) {
      return (int *)0x0;
    }
    DAT_0045fc58 = local_8;
    if ((*param_1 == *(char *)(DAT_0045fbe4 + *local_8)) &&
       (iVar2 = strcmp(param_1,(char *)(DAT_0045fbe4 + *local_8)), iVar2 == 0)) break;
    local_8 = (int *)local_8[1];
  }
  return local_8;
}


/* ==== FUN_00438c80 @ 00438c80 ==== */

void FUN_00438c80(void)

{
  int local_14;
  int local_10;
  int local_c;
  
  for (local_10 = 0; local_10 < 0x3f1; local_10 = local_10 + 1) {
    for (local_14 = *(int *)(&DAT_0045fcc0 + local_10 * 4); local_14 != 0;
        local_14 = *(int *)(local_14 + 0x5c)) {
      if (*(int *)(local_14 + 0x38) != 0) {
        *(int *)(local_14 + 0x10) =
             *(int *)(local_14 + 0x10) +
             *(int *)(*(int *)(*(int *)(local_14 + 0x48) + 0x1c) +
                      (*(int *)(local_14 + 0x38) + -1) * 0x1c + 0x18);
        *(uint *)(local_14 + 0x10) = *(uint *)(local_14 + 0x10) & 0xffff;
      }
      if (*(int *)(local_14 + 0x4c) != 0) {
        *(int *)(local_14 + 0x10) =
             *(int *)(local_14 + 0x10) +
             *(int *)(*(int *)(**(int **)(local_14 + 0x4c) + 0x1c) +
                      (*(int *)(*(int *)(local_14 + 0x4c) + 4) + -1) * 0x1c + 0x18);
        *(uint *)(local_14 + 0x10) = *(uint *)(local_14 + 0x10) & 0xffff;
      }
    }
  }
  for (local_c = DAT_0045fc3c; local_c != 0; local_c = *(int *)(local_c + 8)) {
    for (local_14 = *(int *)(local_c + 4); local_14 != 0; local_14 = *(int *)(local_14 + 0x5c)) {
      if (*(int *)(local_14 + 0x38) != 0) {
        *(int *)(local_14 + 0x10) =
             *(int *)(local_14 + 0x10) +
             *(int *)(*(int *)(*(int *)(local_14 + 0x48) + 0x1c) +
                      (*(int *)(local_14 + 0x38) + -1) * 0x1c + 0x18);
        *(uint *)(local_14 + 0x10) = *(uint *)(local_14 + 0x10) & 0xffff;
      }
      if (*(int *)(local_14 + 0x4c) != 0) {
        *(int *)(local_14 + 0x10) =
             *(int *)(local_14 + 0x10) +
             *(int *)(*(int *)(**(int **)(local_14 + 0x4c) + 0x1c) +
                      (*(int *)(*(int *)(local_14 + 0x4c) + 4) + -1) * 0x1c + 0x18);
        *(uint *)(local_14 + 0x10) = *(uint *)(local_14 + 0x10) & 0xffff;
      }
    }
  }
  for (local_c = DAT_0045fc48; local_c != 0; local_c = *(int *)(local_c + 8)) {
    for (local_14 = *(int *)(local_c + 4); local_14 != 0; local_14 = *(int *)(local_14 + 0x5c)) {
      if (*(int *)(local_14 + 0x38) != 0) {
        *(int *)(local_14 + 0x10) =
             *(int *)(local_14 + 0x10) +
             *(int *)(*(int *)(*(int *)(local_14 + 0x48) + 0x1c) +
                      (*(int *)(local_14 + 0x38) + -1) * 0x1c + 0x18);
        *(uint *)(local_14 + 0x10) = *(uint *)(local_14 + 0x10) & 0xffff;
      }
      if (*(int *)(local_14 + 0x4c) != 0) {
        *(int *)(local_14 + 0x10) =
             *(int *)(local_14 + 0x10) +
             *(int *)(*(int *)(**(int **)(local_14 + 0x4c) + 0x1c) +
                      (*(int *)(*(int *)(local_14 + 0x4c) + 4) + -1) * 0x1c + 0x18);
        *(uint *)(local_14 + 0x10) = *(uint *)(local_14 + 0x10) & 0xffff;
      }
    }
  }
  return;
}


/* ==== FUN_00438f1a @ 00438f1a ==== */

int __cdecl FUN_00438f1a(uint *param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  
  if ((param_2 != 0) && (puVar1 = FUN_0041faa5(param_1,2), puVar1 != (undefined4 *)0x0)) {
    return 0;
  }
  iVar2 = FUN_004398cc(param_1,0x44e0b0,DAT_0044ebc8,0x14,FUN_00438f5a);
  return iVar2;
}


/* ==== FUN_00438f5a @ 00438f5a ==== */

uint __cdecl FUN_00438f5a(char *param_1,undefined4 *param_2)

{
  uint uVar1;
  
  uVar1 = strcmp(param_1,(char *)*param_2);
  if (uVar1 == 0) {
    uVar1 = (uint)(((int)*(char *)(param_2 + 1) & 0x80U) != 0);
  }
  return uVar1;
}


/* ==== FUN_00438f9c @ 00438f9c ==== */

undefined1 * __cdecl FUN_00438f9c(char *param_1)

{
  int iVar1;
  char local_14;
  uint local_10;
  char *local_c;
  char *local_8;
  
  local_c = &DAT_00463c68;
  for (local_8 = param_1; *local_8 != '\0'; local_8 = local_8 + 1) {
    if (__mb_cur_max < 2) {
      local_10 = *(ushort *)(_pctype + *local_8 * 2) & 1;
    }
    else {
      local_10 = _isctype((int)*local_8,1);
    }
    if (local_10 == 0) {
      local_14 = *local_8;
    }
    else {
      iVar1 = tolower((int)*local_8);
      local_14 = (char)iVar1;
    }
    *local_c = local_14;
    local_c = local_c + 1;
  }
  *local_c = '\0';
  return &DAT_00463c68;
}


/* ==== FUN_0043903f @ 0043903f ==== */

int __cdecl FUN_0043903f(uint *param_1,int param_2)

{
  undefined4 *puVar1;
  int local_8;
  
  if ((param_2 == 0) || (puVar1 = FUN_0041faa5(param_1,2), puVar1 == (undefined4 *)0x0)) {
    local_8 = FUN_004398cc(param_1,0x44fab0,DAT_0044fd08,8,FUN_004390ac);
    if (((local_8 != 0) && (DAT_0045eb50 == '\0')) && (*(char *)(local_8 + 4) == '0')) {
      local_8 = 0;
    }
  }
  else {
    local_8 = 0;
  }
  return local_8;
}


/* ==== FUN_004390ac @ 004390ac ==== */

uint __cdecl FUN_004390ac(char *param_1,undefined4 *param_2)

{
  uint uVar1;
  
  uVar1 = strcmp(param_1,(char *)*param_2);
  if (uVar1 == 0) {
    uVar1 = (uint)(((int)*(char *)(param_2 + 1) & 0x80U) != 0);
  }
  return uVar1;
}


/* ==== FUN_004390e6 @ 004390e6 ==== */

void __cdecl FUN_004390e6(undefined4 param_1)

{
  FUN_004398cc(param_1,0x44fd10,DAT_0044fff0,8,FUN_00439109);
  return;
}


/* ==== FUN_00439109 @ 00439109 ==== */

void __cdecl FUN_00439109(char *param_1,undefined4 *param_2)

{
  strcmp(param_1,(char *)*param_2);
  return;
}


/* ==== FUN_00439120 @ 00439120 ==== */

void __cdecl FUN_00439120(undefined4 param_1)

{
  FUN_004398cc(param_1,0x44ec70,DAT_0044eca0,0xc,FUN_00439143);
  return;
}


/* ==== FUN_00439143 @ 00439143 ==== */

void __cdecl FUN_00439143(char *param_1,undefined4 *param_2)

{
  strcmp(param_1,(char *)*param_2);
  return;
}


/* ==== FUN_0043915a @ 0043915a ==== */

void __cdecl FUN_0043915a(undefined4 param_1)

{
  FUN_004398cc(param_1,0x44eca8,DAT_0044ece0,8,FUN_0043917d);
  return;
}


/* ==== FUN_0043917d @ 0043917d ==== */

void __cdecl FUN_0043917d(char *param_1,undefined4 *param_2)

{
  strcmp(param_1,(char *)*param_2);
  return;
}


/* ==== FUN_00439194 @ 00439194 ==== */

void __cdecl FUN_00439194(int param_1)

{
  FUN_004398cc(param_1 + 1,0x4503b0,DAT_0045044c,0xc,FUN_004391c0);
  return;
}


/* ==== FUN_004391c0 @ 004391c0 ==== */

void __cdecl FUN_004391c0(char *param_1,undefined4 *param_2)

{
  strcmp(param_1,(char *)*param_2);
  return;
}


/* ==== FUN_004391d7 @ 004391d7 ==== */

void __cdecl FUN_004391d7(char *param_1)

{
  uint local_8;
  
  do {
    param_1 = param_1 + 1;
    if (__mb_cur_max < 2) {
      local_8 = *(ushort *)(_pctype + *param_1 * 2) & 4;
    }
    else {
      local_8 = _isctype((int)*param_1,4);
    }
  } while (local_8 != 0);
  FUN_004398cc(param_1,0x450450,DAT_004504d0,8,FUN_00439250);
  return;
}


/* ==== FUN_00439250 @ 00439250 ==== */

void __cdecl FUN_00439250(char *param_1,undefined4 *param_2)

{
  strcmp(param_1,(char *)*param_2);
  return;
}


/* ==== FUN_00439267 @ 00439267 ==== */

void __cdecl FUN_00439267(undefined4 param_1)

{
  FUN_004398cc(param_1,0x44ebd0,DAT_0044ec68,8,FUN_0043928a);
  return;
}


/* ==== FUN_0043928a @ 0043928a ==== */

void __cdecl FUN_0043928a(char *param_1,undefined4 *param_2)

{
  strcmp(param_1,(char *)*param_2);
  return;
}


/* ==== FUN_004392a1 @ 004392a1 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004392a1(void)

{
  undefined *puVar1;
  
  if (PTR_DAT_0044f998 != &DAT_0044f990) {
    DAT_0045fc70 = PTR_DAT_0044f998;
    while (puVar1 = DAT_0045fc70, DAT_0045fc70 != &DAT_0044f990) {
      DAT_0045fc70 = *(undefined **)(DAT_0045fc70 + 8);
      FUN_004398b5(puVar1);
    }
  }
  DAT_0044f994 = 0;
  _DAT_0044f990 = 0;
  DAT_0045fc70 = &DAT_0044f990;
  PTR_DAT_0044f998 = &DAT_0044f990;
  return;
}


/* ==== FUN_00439317 @ 00439317 ==== */

void FUN_00439317(void)

{
  DAT_0045fc70 = PTR_DAT_0044f998;
  return;
}


/* ==== FUN_00439326 @ 00439326 ==== */

void FUN_00439326(void)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00439857(0xc);
  *puVar1 = DAT_0045f934;
  puVar1[1] = DAT_0045eb78;
  puVar1[2] = *(undefined4 *)((int)DAT_0045fc70 + 8);
  *(undefined4 **)((int)DAT_0045fc70 + 8) = puVar1;
  DAT_0045fc70 = puVar1;
  return;
}


/* ==== FUN_00439374 @ 00439374 ==== */

void FUN_00439374(void)

{
  if (DAT_0045fc70 != &DAT_0044f990) {
    if (*(int *)(DAT_0045fc70 + 4) != DAT_0045eb78) {
      FUN_00412fa0((uint *)s_Forward_reference_sequence_failu_00459544);
    }
    DAT_0045fc70 = *(undefined **)(DAT_0045fc70 + 8);
  }
  return;
}


/* ==== FUN_004393b2 @ 004393b2 ==== */

void FUN_004393b2(void)

{
  undefined *puVar1;
  int local_10;
  undefined *local_c;
  
  for (local_10 = 0; local_10 < 0x3f1; local_10 = local_10 + 1) {
    local_c = *(undefined **)(&DAT_00462c18 + local_10 * 4);
    if (local_c != (undefined *)0x0) {
      *(undefined4 *)(&DAT_00462c18 + local_10 * 4) = 0;
      while (local_c != (undefined *)0x0) {
        puVar1 = *(undefined **)(local_c + 4);
        FUN_004398b5(local_c);
        local_c = puVar1;
      }
    }
  }
  DAT_0045fc58 = 0;
  DAT_0044f988 = 4;
  return;
}


/* ==== FUN_00439431 @ 00439431 ==== */

void FUN_00439431(void)

{
  undefined *puVar1;
  int *piVar2;
  int *local_18;
  int local_10;
  undefined *local_c;
  
  for (local_10 = 0; local_10 < 0x3f1; local_10 = local_10 + 1) {
    local_18 = *(int **)(&DAT_0045fcc0 + local_10 * 4);
    if (local_18 != (int *)0x0) {
      *(undefined4 *)(&DAT_0045fcc0 + local_10 * 4) = 0;
      while (local_18 != (int *)0x0) {
        if (*local_18 != 0) {
          FUN_004398b5((undefined *)*local_18);
          *local_18 = 0;
        }
        local_c = (undefined *)local_18[0x14];
        while (local_c != (undefined *)0x0) {
          puVar1 = *(undefined **)(local_c + 8);
          FUN_004398b5(local_c);
          local_c = puVar1;
        }
        if (local_18[0x15] != 0) {
          FUN_004398b5((undefined *)local_18[0x15]);
        }
        if (local_18[0x16] != 0) {
          FUN_004398b5((undefined *)local_18[0x16]);
        }
        piVar2 = (int *)local_18[0x17];
        FUN_004398b5((undefined *)local_18);
        local_18 = piVar2;
      }
    }
  }
  DAT_0045fc34 = 0;
  DAT_0045eb64 = 0;
  DAT_0045eb70 = 0;
  return;
}


/* ==== FUN_00439547 @ 00439547 ==== */

void FUN_00439547(void)

{
  undefined *puVar1;
  int *piVar2;
  undefined4 *puVar3;
  int *local_1c;
  undefined *local_10;
  undefined *local_c;
  
  local_c = DAT_0045fc3c;
  while (local_c != (undefined *)0x0) {
    local_1c = *(int **)(local_c + 4);
    while (local_1c != (int *)0x0) {
      if (*local_1c != 0) {
        FUN_004398b5((undefined *)*local_1c);
        *local_1c = 0;
      }
      local_10 = (undefined *)local_1c[0x14];
      while (local_10 != (undefined *)0x0) {
        puVar1 = *(undefined **)(local_10 + 8);
        FUN_004398b5(local_10);
        local_10 = puVar1;
      }
      piVar2 = (int *)local_1c[0x17];
      FUN_004398b5((undefined *)local_1c);
      local_1c = piVar2;
    }
    puVar1 = *(undefined **)(local_c + 8);
    FUN_004398b5(local_c);
    local_c = puVar1;
  }
  DAT_0045fc3c = (undefined *)0x0;
  DAT_0045eb6c = 0;
  local_c = DAT_0045fc48;
  while (local_c != (undefined *)0x0) {
    local_1c = *(undefined4 **)(local_c + 4);
    while (local_1c != (undefined4 *)0x0) {
      FUN_004398b5((undefined *)*local_1c);
      *local_1c = 0;
      puVar3 = (undefined4 *)local_1c[0x17];
      FUN_004398b5((undefined *)local_1c);
      local_1c = puVar3;
    }
    puVar1 = *(undefined **)(local_c + 8);
    FUN_004398b5(local_c);
    local_c = puVar1;
  }
  DAT_0045fc48 = (undefined *)0x0;
  return;
}


/* ==== FUN_00439686 @ 00439686 ==== */

void FUN_00439686(void)

{
  int *piVar1;
  int *local_10;
  int local_c;
  
  for (local_c = 0; local_c < 0x3f1; local_c = local_c + 1) {
    local_10 = *(int **)(&DAT_00461c50 + local_c * 4);
    if (local_10 != (int *)0x0) {
      *(undefined4 *)(&DAT_00461c50 + local_c * 4) = 0;
      while (local_10 != (int *)0x0) {
        if (*local_10 != 0) {
          FUN_004398b5((undefined *)*local_10);
          *local_10 = 0;
        }
        piVar1 = (int *)local_10[4];
        FUN_004398b5((undefined *)local_10);
        local_10 = piVar1;
      }
    }
  }
  DAT_0045fc54 = 0;
  DAT_0045eb74 = 0;
  return;
}


/* ==== FUN_00439724 @ 00439724 ==== */

void FUN_00439724(void)

{
  undefined *puVar1;
  undefined *local_c;
  
  local_c = DAT_0045fc74;
  while (local_c != (undefined *)0x0) {
    puVar1 = *(undefined **)(local_c + 4);
    FUN_004398b5(local_c);
    local_c = puVar1;
  }
  return;
}


/* ==== FUN_00439760 @ 00439760 ==== */

uint * __cdecl FUN_00439760(uint *param_1)

{
  char *s;
  uint *dst;
  uint uVar1;
  uint *dst_00;
  uint *local_18;
  undefined4 *local_14;
  uint *local_c;
  uint local_8;
  
  local_18 = (uint *)0x0;
  if (param_1 == (uint *)0x0) {
    local_18 = (uint *)0x0;
  }
  else {
    local_8 = strlen((char *)param_1);
    malloc(local_8 + 1);
    if (dst == (uint *)0x0) {
      FUN_00412fa0((uint *)s_memory_malloc_failed_0045959c);
    }
    else {
      strcpy((char *)dst,(char *)param_1);
      local_18 = dst;
    }
    local_14 = (undefined4 *)&stack0x00000008;
    local_c = dst;
    while( true ) {
      s = (char *)*local_14;
      if (s == (char *)0x0) break;
      uVar1 = strlen(s);
      local_8 = local_8 + uVar1;
      realloc(local_c,local_8 + 1);
      local_18 = dst_00;
      if (dst_00 == (uint *)0x0) {
        FUN_00412fa0((uint *)s_memory_realloc_failed_004595b4);
        local_14 = local_14 + 1;
      }
      else {
        strcat((char *)dst_00,s);
        local_14 = local_14 + 1;
        local_c = dst_00;
      }
    }
  }
  return local_18;
}


/* ==== FUN_00439857 @ 00439857 ==== */

int __cdecl FUN_00439857(uint param_1)

{
  int extraout_EAX;
  
  malloc(param_1);
  if (extraout_EAX == 0) {
    FUN_00412fa0((uint *)s_Out_of_memory___assembly_aborted_004595cc);
  }
  return extraout_EAX;
}


/* ==== FUN_00439884 @ 00439884 ==== */

int * __cdecl FUN_00439884(int *param_1,uint param_2)

{
  int *extraout_EAX;
  
  realloc(param_1,param_2);
  if (extraout_EAX == (int *)0x0) {
    FUN_00412fa0((uint *)s_Out_of_memory___assembly_aborted_004595f0);
  }
  return extraout_EAX;
}


/* ==== FUN_004398b5 @ 004398b5 ==== */

void __cdecl FUN_004398b5(undefined *param_1)

{
  if (param_1 != (undefined *)0x0) {
    free(param_1);
  }
  return;
}


/* ==== FUN_004398cc @ 004398cc ==== */

int __cdecl FUN_004398cc(undefined4 param_1,uint param_2,int param_3,int param_4,undefined *param_5)

{
  int iVar1;
  int iVar2;
  uint local_14;
  uint local_8;
  
  local_14 = param_2;
  local_8 = param_2 + (param_3 + -1) * param_4;
  while( true ) {
    while( true ) {
      if (local_8 < local_14) {
        return 0;
      }
      iVar2 = local_14 + ((int)(local_8 - local_14) / param_4 >> 1) * param_4;
      iVar1 = (*(code *)param_5)(param_1,iVar2);
      if (-1 < iVar1) break;
      local_8 = iVar2 - param_4;
    }
    if (iVar1 < 1) break;
    local_14 = iVar2 + param_4;
  }
  return iVar2;
}


/* ==== FUN_0043994a @ 0043994a ==== */

uint __cdecl
FUN_0043994a(undefined4 param_1,uint param_2,int param_3,int param_4,undefined *param_5)

{
  int iVar1;
  uint uVar2;
  uint local_14;
  uint local_8;
  
  local_14 = param_2;
  local_8 = param_2 + (param_3 + -1) * param_4;
  while( true ) {
    while( true ) {
      if (local_8 < local_14) {
        return local_14;
      }
      uVar2 = local_14 + ((int)(local_8 - local_14) / param_4 >> 1) * param_4;
      iVar1 = (*(code *)param_5)(param_1,uVar2);
      if (-1 < iVar1) break;
      local_8 = uVar2 - param_4;
    }
    if (iVar1 < 1) break;
    local_14 = uVar2 + param_4;
  }
  return uVar2;
}


/* ==== FUN_004399c9 @ 004399c9 ==== */

void __cdecl FUN_004399c9(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 local_14;
  undefined4 local_c;
  
  if (param_1 < param_2) {
    local_c = param_1;
    local_14 = param_2;
    iVar2 = (param_1 + param_2) / 2;
    uVar1 = *(undefined4 *)(DAT_0045fc80 + iVar2 * 4);
    while( true ) {
      while ((local_c < local_14 &&
             (iVar3 = (*DAT_0045fb60)(*(undefined4 *)(DAT_0045fc80 + local_c * 4),uVar1), iVar3 < 1)
             )) {
        local_c = local_c + 1;
      }
      while ((local_c < local_14 &&
             (iVar3 = (*DAT_0045fb60)(*(undefined4 *)(DAT_0045fc80 + local_14 * 4),uVar1),
             -1 < iVar3))) {
        local_14 = local_14 + -1;
      }
      if (local_14 <= local_c) break;
      FUN_00439b25(local_c,local_14);
    }
    if ((iVar2 < local_c) &&
       (iVar3 = (*DAT_0045fb60)(*(undefined4 *)(DAT_0045fc80 + local_c * 4),uVar1), 0 < iVar3)) {
      local_c = local_c + -1;
    }
    FUN_00439b25(local_c,iVar2);
    if (local_c - param_1 < param_2 - local_c) {
      FUN_004399c9(param_1,local_c + -1);
      FUN_004399c9(local_c + 1,param_2);
    }
    else {
      FUN_004399c9(local_c + 1,param_2);
      FUN_004399c9(param_1,local_c + -1);
    }
  }
  return;
}


/* ==== FUN_00439b25 @ 00439b25 ==== */

void __cdecl FUN_00439b25(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(DAT_0045fc80 + param_1 * 4);
  *(undefined4 *)(DAT_0045fc80 + param_1 * 4) = *(undefined4 *)(DAT_0045fc80 + param_2 * 4);
  *(undefined4 *)(DAT_0045fc80 + param_2 * 4) = uVar1;
  return;
}


/* ==== FUN_00439b65 @ 00439b65 ==== */

uint __cdecl FUN_00439b65(char *param_1)

{
  uint uVar1;
  uint local_c;
  
  local_c = 0;
  for (; *param_1 != '\0'; param_1 = param_1 + 1) {
    local_c = local_c * 0x10 + (int)*param_1;
    uVar1 = local_c & 0xf0000000;
    if (uVar1 != 0) {
      local_c = local_c ^ uVar1 >> 0x18 ^ uVar1;
    }
  }
  return local_c % 0x3f1;
}


/* ==== FUN_00439bd4 @ 00439bd4 ==== */

char * __cdecl FUN_00439bd4(char *param_1)

{
  uint uVar1;
  char *local_8;
  
  if (param_1 == (char *)0x0) {
    param_1 = (char *)0x0;
  }
  else {
    uVar1 = strlen(param_1);
    for (local_8 = param_1 + uVar1;
        (((param_1 <= local_8 && (*local_8 != '\\')) && (*local_8 != '/')) && (*local_8 != ':'));
        local_8 = local_8 + -1) {
    }
    if (param_1 <= local_8) {
      param_1 = local_8 + 1;
    }
  }
  return param_1;
}


/* ==== FUN_00439c56 @ 00439c56 ==== */

undefined4 __cdecl FUN_00439c56(int param_1,undefined4 param_2)

{
  char cVar1;
  int local_8;
  
  local_8 = 4;
  if (((DAT_0045f860 != (char *)0x0) && (*DAT_0045f860 != '\0')) && (DAT_0045f860[1] == ':')) {
    cVar1 = *DAT_0045f860;
    DAT_0045f860 = DAT_0045f860 + 2;
    local_8 = FUN_0043a807((int)cVar1);
    if (local_8 == 0xa2c2a) {
      FUN_00413085((uint *)s_Illegal_memory_space_specified_00459614);
      return 0;
    }
  }
  *(int *)(param_1 + 4) = local_8;
  switch(param_2) {
  case 0:
    if (local_8 == 4) {
      return 1;
    }
    break;
  case 1:
    if (local_8 == 1) {
      return 1;
    }
    break;
  case 2:
    if (local_8 == 2) {
      return 1;
    }
    break;
  case 3:
    if (local_8 == 3) {
      return 1;
    }
    break;
  case 4:
    if (local_8 == 0) {
      return 1;
    }
    break;
  case 5:
    if ((local_8 == 1) || (local_8 == 2)) {
      return 1;
    }
    break;
  case 6:
    if (((local_8 == 1) || (local_8 == 2)) || ((local_8 == 3 || ((local_8 == 0 || (local_8 == 4)))))
       ) {
      return 1;
    }
    break;
  case 7:
    if (((local_8 == 1) || (local_8 == 2)) || (local_8 == 4)) {
      return 1;
    }
    break;
  case 8:
    if ((local_8 == 2) || (local_8 == 4)) {
      return 1;
    }
    break;
  case 9:
    if (((local_8 == 1) || (local_8 == 2)) || ((local_8 == 0 || (local_8 == 4)))) {
      return 1;
    }
  }
  switch(local_8) {
  case 0:
    FUN_00413085((uint *)s_Illegal_memory_space_specified___0045967c);
    break;
  case 1:
    FUN_00413085((uint *)s_Illegal_memory_space_specified___00459634);
    break;
  case 2:
    FUN_00413085((uint *)s_Illegal_memory_space_specified___00459658);
    break;
  case 3:
    FUN_00413085((uint *)s_Illegal_memory_space_specified___004596a0);
    break;
  default:
    FUN_00413085((uint *)s_Missing_or_illegal_memory_space_s_004596c4);
  }
  return 0;
}


/* ==== FUN_00439e8d @ 00439e8d ==== */

undefined4 __cdecl FUN_00439e8d(int *param_1)

{
  char cVar1;
  undefined3 extraout_var;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  char *pcVar5;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  int local_18;
  uint local_14;
  int local_10;
  uint local_c;
  
  param_1[1] = 4;
  *param_1 = 4;
  param_1[2] = 0;
  param_1[3] = 0;
  cVar1 = strchr(DAT_0045f860,0x3a);
  if (CONCAT31(extraout_var,cVar1) == 0) {
    return 0;
  }
  iVar2 = FUN_0043a807((int)*DAT_0045f860);
  *param_1 = iVar2;
  if (*param_1 == 0xa2c2a) {
    return 0;
  }
  if (*param_1 == 0x1c) {
    if (__mb_cur_max < 2) {
      local_c = *(ushort *)(_pctype + DAT_0045f860[1] * 2) & 1;
    }
    else {
      local_c = _isctype((int)DAT_0045f860[1],1);
    }
    if (local_c == 0) {
      local_10 = (int)DAT_0045f860[1];
    }
    else {
      local_10 = tolower((int)DAT_0045f860[1]);
    }
    if (local_10 == 0x6d) {
      DAT_0045f860 = DAT_0045f860 + 1;
    }
  }
  if (*param_1 == 0x11d) {
    if (__mb_cur_max < 2) {
      local_14 = *(ushort *)(_pctype + DAT_0045f860[1] * 2) & 1;
    }
    else {
      local_14 = _isctype((int)DAT_0045f860[1],1);
    }
    if (local_14 == 0) {
      local_18 = (int)DAT_0045f860[1];
    }
    else {
      local_18 = tolower((int)DAT_0045f860[1]);
    }
    if (local_18 == 0x6d) {
      DAT_0045f860 = DAT_0045f860 + 1;
    }
  }
  DAT_0045f860 = DAT_0045f860 + 1;
  if (*DAT_0045f860 == ':') {
    if (*param_1 == 0x11f) {
      param_1[1] = 0x120;
    }
    else {
      param_1[1] = *param_1;
    }
    DAT_0045f860 = DAT_0045f860 + 1;
    return 1;
  }
  iVar2 = FUN_0043a91e((int)*DAT_0045f860);
  param_1[2] = iVar2;
  if (param_1[2] != -1) {
    pcVar5 = DAT_0045f860 + 1;
    if (*pcVar5 == ':') {
      DAT_0045f860 = DAT_0045f860 + 2;
      if (param_1[1] == 4) {
        if (*param_1 == 0x11f) {
          param_1[1] = 0x120;
        }
        else {
          param_1[1] = *param_1;
        }
      }
      return 1;
    }
    DAT_0045f860 = pcVar5;
    if ((*param_1 != 0x11f) && (param_1[1] != 0x11e)) {
      if (*param_1 == 0x1c) {
        if (__mb_cur_max < 2) {
          local_1c = *(ushort *)(_pctype + *pcVar5 * 2) & 4;
        }
        else {
          local_1c = _isctype((int)*pcVar5,4);
        }
        if (local_1c != 0) {
          uVar3 = strtol(DAT_0045f860,(char **)0x0,10);
          iVar2 = FUN_0043aeb8(uVar3,(uint *)(param_1 + 3));
          param_1[1] = iVar2;
          if (param_1[1] == 0xa2c2a) {
            return 0;
          }
          while( true ) {
            if (__mb_cur_max < 2) {
              local_20 = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 4;
            }
            else {
              local_20 = _isctype((int)*DAT_0045f860,4);
            }
            if (local_20 == 0) break;
            DAT_0045f860 = DAT_0045f860 + 1;
          }
          goto LAB_0043a2cf;
        }
      }
      cVar1 = *DAT_0045f860;
      if (param_1[1] != 4) {
        FUN_00413085((uint *)s_Illegal_memory_map_character_004596f0);
        return 0xffffffff;
      }
      iVar2 = FUN_0043a9d1((int)*DAT_0045f860,0,*param_1);
      param_1[1] = iVar2;
      if (param_1[1] == 0xa2c2a) {
        FUN_00413085((uint *)s_Illegal_memory_counter_specified_00459710);
        return 0xffffffff;
      }
      DAT_0045f860 = DAT_0045f860 + 1;
      if (*DAT_0045f860 != ':') {
        if (*param_1 == 3) {
          iVar2 = FUN_0043a9d1((int)cVar1,(int)*DAT_0045f860,*param_1);
          param_1[1] = iVar2;
          if (param_1[1] != 0xa2c2a) {
            DAT_0045f860 = DAT_0045f860 + 1;
            goto LAB_0043a2cf;
          }
        }
        FUN_00413085((uint *)s_Illegal_memory_map_character_00459734);
        return 0xffffffff;
      }
LAB_0043a2cf:
      if (*DAT_0045f860 != ':') {
        FUN_00413085((uint *)s_Syntax_error___expected_____00459754);
        return 0xffffffff;
      }
      DAT_0045f860 = DAT_0045f860 + 1;
      return 1;
    }
  }
  param_1[2] = 0;
  if (*DAT_0045f860 == '(') {
    DAT_0045f860 = DAT_0045f860 + 1;
    iVar2 = FUN_004147ee();
    param_1[2] = iVar2;
    if (param_1[2] == -1) {
      param_1[2] = 0;
      return 0xffffffff;
    }
    if (0xffff < param_1[2]) {
      FUN_00413085((uint *)s_Memory_counter_designator_value_t_00459770);
      return 0xffffffff;
    }
    if (param_1[1] == 4) {
      if (*param_1 == 0x11f) {
        param_1[1] = 0x120;
      }
      else {
        param_1[1] = *param_1;
      }
    }
    if ((*DAT_0045f860 == ')') && (DAT_0045f860[1] == ':')) {
      DAT_0045f860 = DAT_0045f860 + 2;
      return 1;
    }
    FUN_00413085((uint *)s_Syntax_error___expected______0045979c);
    return 0xffffffff;
  }
  if (*param_1 == 0x1c) {
    if (__mb_cur_max < 2) {
      local_24 = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 4;
    }
    else {
      local_24 = _isctype((int)*DAT_0045f860,4);
    }
    if (local_24 != 0) {
      uVar3 = strtol(DAT_0045f860,(char **)0x0,10);
      iVar2 = FUN_0043aeb8(uVar3,(uint *)(param_1 + 3));
      param_1[1] = iVar2;
      if (param_1[1] == 0xa2c2a) {
        return 0;
      }
      while( true ) {
        if (__mb_cur_max < 2) {
          local_28 = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 4;
        }
        else {
          local_28 = _isctype((int)*DAT_0045f860,4);
        }
        pcVar5 = DAT_0045f860;
        if (local_28 == 0) break;
        DAT_0045f860 = DAT_0045f860 + 1;
      }
      goto LAB_0043a5e8;
    }
  }
  pcVar5 = DAT_0045f860;
  if ((*param_1 != 0x11f) && (param_1[1] != 0x11e)) {
    cVar1 = *DAT_0045f860;
    if (param_1[1] != 4) {
      FUN_00413085((uint *)s_Illegal_memory_map_character_004597bc);
      return 0xffffffff;
    }
    iVar2 = FUN_0043a9d1((int)*DAT_0045f860,0,*param_1);
    param_1[1] = iVar2;
    if (param_1[1] == 0xa2c2a) {
      FUN_00413085((uint *)s_Illegal_memory_counter_specified_004597dc);
      return 0xffffffff;
    }
    pcVar5 = DAT_0045f860 + 1;
    if ((*pcVar5 != ':') && (*pcVar5 != '(')) {
      if (*param_1 == 3) {
        DAT_0045f860 = DAT_0045f860 + 2;
        iVar2 = FUN_0043a9d1((int)cVar1,(int)*pcVar5,*param_1);
        param_1[1] = iVar2;
        pcVar5 = DAT_0045f860;
        if (param_1[1] != 0xa2c2a) goto LAB_0043a5e8;
      }
      DAT_0045f860 = pcVar5;
      FUN_00413085((uint *)s_Illegal_memory_map_character_00459800);
      return 0xffffffff;
    }
  }
LAB_0043a5e8:
  DAT_0045f860 = pcVar5;
  if (*DAT_0045f860 == '(') {
    DAT_0045f860 = DAT_0045f860 + 1;
    iVar2 = FUN_004147ee();
    param_1[2] = iVar2;
    if (param_1[2] == -1) {
      param_1[2] = 0;
      uVar4 = 0xffffffff;
    }
    else if (param_1[2] < 0x10000) {
      if ((*DAT_0045f860 == ')') && (DAT_0045f860[1] == ':')) {
        DAT_0045f860 = DAT_0045f860 + 2;
        uVar4 = 1;
      }
      else {
        FUN_00413085((uint *)s_Syntax_error___expected______0045984c);
        uVar4 = 0xffffffff;
      }
    }
    else {
      FUN_00413085((uint *)s_Memory_counter_designator_value_t_00459820);
      uVar4 = 0xffffffff;
    }
  }
  else if (*DAT_0045f860 == ':') {
    DAT_0045f860 = DAT_0045f860 + 1;
    uVar4 = 1;
  }
  else {
    FUN_00413085((uint *)s_Syntax_error___expected_____0045986c);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}


/* ==== FUN_0043a6c5 @ 0043a6c5 ==== */

char __cdecl FUN_0043a6c5(int param_1)

{
  char cVar1;
  
  if (param_1 < 0x1d) {
    if (param_1 == 0x1c) {
      return (-(DAT_0044f9fc < 3) & 9U) + 0x45;
    }
    switch(param_1) {
    case 0:
      cVar1 = 'P';
      break;
    case 1:
      cVar1 = 'X';
      break;
    case 2:
      cVar1 = 'Y';
      break;
    case 3:
      cVar1 = 'L';
      break;
    default:
      goto switchD_0043a6e6_default;
    }
  }
  else {
    if (param_1 == 0x11d) {
      if ((1 < DAT_0044f9fc) && (0x1fff < DAT_0044fa00)) {
        return 'D';
      }
      return 'N';
    }
switchD_0043a6e6_default:
    cVar1 = 'N';
  }
  return cVar1;
}


/* ==== FUN_0043a768 @ 0043a768 ==== */

int __cdecl FUN_0043a768(int param_1)

{
  int iVar1;
  
  if (param_1 < 0x1d) {
    if (param_1 == 0x1c) {
      return (-(uint)(DAT_0044f9fc < 3) & 0xfffffffb) + 5;
    }
    switch(param_1) {
    case 0:
      iVar1 = 4;
      break;
    case 1:
      iVar1 = 1;
      break;
    case 2:
      iVar1 = 2;
      break;
    case 3:
      iVar1 = 3;
      break;
    default:
      goto switchD_0043a789_default;
    }
  }
  else {
    if (param_1 == 0x11d) {
      if ((1 < DAT_0044f9fc) && (0x1fff < DAT_0044fa00)) {
        return 6;
      }
      return 0;
    }
switchD_0043a789_default:
    iVar1 = 0;
  }
  return iVar1;
}


/* ==== FUN_0043a807 @ 0043a807 ==== */

int __cdecl FUN_0043a807(uint param_1)

{
  int local_14;
  uint local_c;
  uint local_8;
  
  if (__mb_cur_max < 2) {
    local_8 = *(ushort *)(_pctype + param_1 * 2) & 1;
  }
  else {
    local_8 = _isctype(param_1,1);
  }
  if (local_8 == 0) {
    local_c = param_1;
  }
  else {
    local_c = tolower(param_1);
  }
  switch(local_c) {
  case 100:
    if ((DAT_0044f9fc < 2) || (DAT_0044fa00 < 0x2000)) {
      local_14 = 0xa2c2a;
    }
    else {
      local_14 = 0x11d;
    }
    break;
  case 0x65:
    local_14 = (-(uint)(DAT_0044f9fc < 3) & 0xa2c0e) + 0x1c;
    break;
  default:
    local_14 = 0xa2c2a;
    break;
  case 0x6c:
    local_14 = 3;
    break;
  case 0x6e:
    local_14 = 4;
    break;
  case 0x70:
    local_14 = 0;
    break;
  case 0x78:
    local_14 = 1;
    break;
  case 0x79:
    local_14 = 2;
  }
  return local_14;
}


/* ==== FUN_0043a91e @ 0043a91e ==== */

undefined4 __cdecl FUN_0043a91e(uint param_1)

{
  undefined4 uVar1;
  uint local_c;
  uint local_8;
  
  if (__mb_cur_max < 2) {
    local_8 = *(ushort *)(_pctype + param_1 * 2) & 1;
  }
  else {
    local_8 = _isctype(param_1,1);
  }
  if (local_8 == 0) {
    local_c = param_1;
  }
  else {
    local_c = tolower(param_1);
  }
  switch(local_c) {
  case 100:
  case 0x6e:
    uVar1 = 0;
    break;
  default:
    uVar1 = 0xffffffff;
    break;
  case 0x68:
    uVar1 = 2;
    break;
  case 0x6c:
    uVar1 = 1;
  }
  return uVar1;
}


/* ==== FUN_0043a9d1 @ 0043a9d1 ==== */

undefined4 __cdecl FUN_0043a9d1(uint param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  uint local_40;
  uint local_3c;
  uint local_34;
  uint local_30;
  uint local_28;
  uint local_24;
  uint local_1c;
  uint local_18;
  uint local_10;
  uint local_c;
  
  if (param_3 < 0x11e) {
    if (param_3 == 0x11d) {
      if ((DAT_0044f9fc < 2) || (DAT_0044fa00 < 0x2000)) {
        return 0xa2c2a;
      }
      if (__mb_cur_max < 2) {
        local_3c = *(ushort *)(_pctype + param_1 * 2) & 1;
      }
      else {
        local_3c = _isctype(param_1,1);
      }
      if (local_3c == 0) {
        local_40 = param_1;
      }
      else {
        local_40 = tolower(param_1);
      }
      if (local_40 != 0x3a) {
        return 0xa2c2a;
      }
      return 0x11d;
    }
    switch(param_3) {
    case 0:
      if (__mb_cur_max < 2) {
        local_c = *(ushort *)(_pctype + param_1 * 2) & 1;
      }
      else {
        local_c = _isctype(param_1,1);
      }
      if (local_c == 0) {
        local_10 = param_1;
      }
      else {
        local_10 = tolower(param_1);
      }
      switch(local_10) {
      case 0x3a:
        uVar1 = 0;
        break;
      default:
        uVar1 = 0xa2c2a;
        break;
      case 0x65:
        uVar1 = 0xd;
        break;
      case 0x69:
        uVar1 = 0xe;
        break;
      case 0x72:
        uVar1 = 0xf;
      }
      break;
    case 1:
      if (__mb_cur_max < 2) {
        local_18 = *(ushort *)(_pctype + param_1 * 2) & 1;
      }
      else {
        local_18 = _isctype(param_1,1);
      }
      if (local_18 == 0) {
        local_1c = param_1;
      }
      else {
        local_1c = tolower(param_1);
      }
      switch(local_1c) {
      case 0x3a:
        uVar1 = 1;
        break;
      default:
        uVar1 = 0xa2c2a;
        break;
      case 0x65:
        uVar1 = 0x12;
        break;
      case 0x69:
        uVar1 = 0x13;
        break;
      case 0x72:
        uVar1 = 0x14;
      }
      break;
    case 2:
      if (__mb_cur_max < 2) {
        local_24 = *(ushort *)(_pctype + param_1 * 2) & 1;
      }
      else {
        local_24 = _isctype(param_1,1);
      }
      if (local_24 == 0) {
        local_28 = param_1;
      }
      else {
        local_28 = tolower(param_1);
      }
      switch(local_28) {
      case 0x3a:
        uVar1 = 2;
        break;
      default:
        uVar1 = 0xa2c2a;
        break;
      case 0x65:
        uVar1 = 0x17;
        break;
      case 0x69:
        uVar1 = 0x18;
        break;
      case 0x72:
        uVar1 = 0x19;
      }
      break;
    case 3:
      if (__mb_cur_max < 2) {
        local_30 = *(ushort *)(_pctype + param_1 * 2) & 1;
      }
      else {
        local_30 = _isctype(param_1,1);
      }
      if (local_30 == 0) {
        local_34 = param_1;
      }
      else {
        local_34 = tolower(param_1);
      }
      if (local_34 == 0x3a) {
        uVar1 = 3;
      }
      else if (local_34 == 0x65) {
        uVar1 = 9;
      }
      else if (local_34 == 0x69) {
        uVar1 = 10;
      }
      else {
        uVar1 = 0xa2c2a;
      }
      break;
    default:
      goto switchD_0043aa00_default;
    }
  }
  else {
switchD_0043aa00_default:
    uVar1 = 0xa2c2a;
  }
  return uVar1;
}


/* ==== FUN_0043ae13 @ 0043ae13 ==== */

undefined4 __cdecl FUN_0043ae13(uint param_1)

{
  char *pcVar1;
  char *pcVar2;
  undefined4 uVar3;
  
  pcVar1 = DAT_0045f860;
  if (*DAT_0045f860 == '<') {
    pcVar2 = DAT_0045f860 + 1;
    if (*pcVar2 == '<') {
      if ((param_1 & 0x4000000) == 0) {
        DAT_0045f860 = pcVar2;
        FUN_00413085((uint *)s_I_O_short_addressing_mode_not_al_00459888);
        uVar3 = 0xffffffff;
        DAT_0045f860 = pcVar1;
      }
      else {
        uVar3 = 0x4000000;
        DAT_0045f860 = DAT_0045f860 + 2;
      }
    }
    else {
      uVar3 = 0x2000000;
      DAT_0045f860 = pcVar2;
    }
  }
  else {
    uVar3 = DAT_0045ebac;
    DAT_0045f860 = pcVar1;
    if (*DAT_0045f860 == '>') {
      uVar3 = 0x1000000;
      DAT_0045f860 = DAT_0045f860 + 1;
    }
  }
  return uVar3;
}


/* ==== FUN_0043aeb8 @ 0043aeb8 ==== */

int __cdecl FUN_0043aeb8(uint param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = param_1 + 0x1d;
  uVar2 = param_1 & 7;
  if ((DAT_0044f9fc < 3) || ((DAT_0044f9fc < 4 && (0x3f < (int)param_1)))) {
    iVar1 = 0xa2c2a;
  }
  else if (((((int)param_1 < 0x40) || (0x5f < (int)param_1)) &&
           (((int)param_1 < 0xc0 || (0xdf < (int)param_1)))) &&
          (((int)param_1 < 0x80 ||
           ((((uVar2 != 0 && (uVar2 != 1)) && (uVar2 != 6)) && (uVar2 != 7)))))) {
    switch(uVar2) {
    case 0:
    case 1:
      *param_2 = 0x20;
      break;
    case 2:
    case 3:
      *param_2 = ((0x7f < (int)param_1) - 1 & 0x10) + 0x30;
      break;
    case 4:
    case 5:
      *param_2 = ((0x7f < (int)param_1) - 1 & 0x10) + 0x50;
      break;
    case 6:
    case 7:
      *param_2 = 0x40;
      break;
    default:
      *param_2 = 0x60;
    }
    if (((iVar1 < 0x25) || ((0x5c < iVar1 && (iVar1 < 0xa5)))) ||
       ((0xdc < iVar1 && (iVar1 < 0x11d)))) {
      *param_2 = *param_2 | (param_1 & 1) + 1;
    }
  }
  else {
    iVar1 = 0xa2c2a;
  }
  return iVar1;
}


/* ==== FUN_0043b007 @ 0043b007 ==== */

undefined4 __cdecl FUN_0043b007(int param_1)

{
  undefined4 uVar1;
  
  if ((((param_1 == 0) &&
       (((*PTR_DAT_0044f818 != '\0' || (*PTR_DAT_0044f81c != '\0')) || (*PTR_DAT_0044f820 != '\0')))
       ) || ((param_1 == 1 && ((*PTR_DAT_0044f81c != '\0' || (*PTR_DAT_0044f820 != '\0')))))) ||
     ((param_1 == 2 && (*PTR_DAT_0044f820 != '\0')))) {
    FUN_00413085((uint *)s_Extra_fields_ignored_004598b0);
    FUN_00413085((uint *)s_Possible_invalid_white_space_bet_004598c8);
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}


/* ==== FUN_0043b08d @ 0043b08d ==== */

char * __cdecl FUN_0043b08d(char *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  
  if (((*param_1 == '\'') || (*param_1 == '\"')) || (*param_1 == '[')) {
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    while (*param_1 != '\0') {
      if (cVar1 == '[') {
        param_1 = FUN_0043b214(param_1,(int *)&param_2);
        if (param_1 == (char *)0x0) {
          return (char *)0x0;
        }
        cVar1 = *param_1;
      }
      if (*param_1 == cVar1) {
        if (param_1[1] == cVar1) {
          *param_2 = *param_1;
          param_2 = param_2 + 1;
          param_1 = param_1 + 2;
        }
        else {
          if ((param_1[1] != '+') || (param_1[2] != '+')) break;
          pcVar2 = param_1 + 3;
          if ((*pcVar2 != '\'') && ((*pcVar2 != '\"' && (*pcVar2 != '[')))) {
            FUN_00413085((uint *)s_Missing_string_after_concatenati_00459924);
            return (char *)0x0;
          }
          cVar1 = *pcVar2;
          param_1 = param_1 + 4;
        }
      }
      else {
        *param_2 = *param_1;
        param_2 = param_2 + 1;
        param_1 = param_1 + 1;
      }
    }
    *param_2 = '\0';
    if (*param_1 == cVar1) {
      pcVar2 = param_1 + 1;
    }
    else {
      FUN_00413085((uint *)s_Missing_quote_in_string_00459950);
      pcVar2 = (char *)0x0;
    }
  }
  else {
    FUN_00413085((uint *)s_Syntax_error___expected_quote_00459904);
    pcVar2 = (char *)0x0;
  }
  return pcVar2;
}


/* ==== FUN_0043b214 @ 0043b214 ==== */

char * __cdecl FUN_0043b214(char *param_1,int *param_2)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  char local_208 [512];
  uint local_8;
  
  pcVar3 = FUN_0043b08d(param_1,local_208);
  if (pcVar3 == (char *)0x0) {
    pcVar3 = (char *)0x0;
  }
  else {
    local_8 = strlen(local_208);
    pcVar2 = DAT_0045f860;
    DAT_0045f860 = pcVar3 + 1;
    if (*pcVar3 == ',') {
      iVar4 = FUN_0041479f();
      if (iVar4 == -1) {
        pcVar3 = (char *)0x0;
        DAT_0045f860 = pcVar2;
      }
      else {
        cVar1 = *DAT_0045f860;
        DAT_0045f860 = DAT_0045f860 + 1;
        if (cVar1 == ',') {
          iVar5 = FUN_0041479f();
          pcVar3 = DAT_0045f860;
          if (iVar5 == -1) {
            pcVar3 = (char *)0x0;
            DAT_0045f860 = pcVar2;
          }
          else if (iVar4 < (int)local_8) {
            if ((int)local_8 < iVar5) {
              DAT_0045f860 = pcVar2;
              FUN_00413085((uint *)s_Length_value_greater_than_string_004599d0);
              pcVar3 = (char *)0x0;
            }
            else {
              DAT_0045f860 = pcVar2;
              for (param_1 = local_208 + iVar4;
                  (*param_1 != '\0' && (param_1 < local_208 + iVar5 + iVar4)); param_1 = param_1 + 1
                  ) {
                *(char *)*param_2 = *param_1;
                *param_2 = *param_2 + 1;
              }
              *(undefined1 *)*param_2 = 0;
              if (*pcVar3 != ']') {
                FUN_00413085((uint *)s_Missing_delimiter_in_substring_004599f8);
                pcVar3 = (char *)0x0;
              }
            }
          }
          else {
            DAT_0045f860 = pcVar2;
            FUN_00413085((uint *)s_Offset_value_greater_than_string_004599a8);
            pcVar3 = (char *)0x0;
          }
        }
        else {
          DAT_0045f860 = pcVar2;
          FUN_00413085((uint *)s_Syntax_error___expected_comma_00459988);
          pcVar3 = (char *)0x0;
        }
      }
    }
    else {
      FUN_00413085((uint *)s_Syntax_error___expected_comma_00459968);
      pcVar3 = (char *)0x0;
    }
  }
  return pcVar3;
}


/* ==== FUN_0043b405 @ 0043b405 ==== */

char * __cdecl FUN_0043b405(char *param_1,char *param_2)

{
  char *pcVar1;
  
  pcVar1 = FUN_0043b08d(param_1,param_2);
  if (pcVar1 == (char *)0x0) {
    pcVar1 = (char *)0x0;
  }
  else if (*pcVar1 != '\0') {
    FUN_00413085((uint *)s_Extra_characters_following_strin_00459a18);
    pcVar1 = (char *)0x0;
  }
  return pcVar1;
}


/* ==== FUN_0043b448 @ 0043b448 ==== */

undefined1 * FUN_0043b448(void)

{
  int iVar1;
  uint local_14;
  uint local_10;
  int local_c;
  char *local_8;
  
  local_c = 0;
  iVar1 = FUN_0043b5bb(DAT_0045f860);
  if (iVar1 != 0) {
    local_8 = &DAT_00464480;
    if (*DAT_0045f860 == DAT_0044f830) {
      DAT_00464480 = *DAT_0045f860;
      local_8 = &DAT_00464481;
      DAT_0045f860 = DAT_0045f860 + 1;
    }
    if (__mb_cur_max < 2) {
      local_10 = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 0x103;
    }
    else {
      local_10 = _isctype((int)*DAT_0045f860,0x103);
    }
    if (local_10 == 0) {
      FUN_00413085((uint *)s_Symbols_must_start_with_alphabet_00459a3c);
    }
    else {
      while( true ) {
        if (__mb_cur_max < 2) {
          local_14 = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 0x107;
        }
        else {
          local_14 = _isctype((int)*DAT_0045f860,0x107);
        }
        if ((local_14 == 0) && (*DAT_0045f860 != '_')) {
          *local_8 = '\0';
          return &DAT_00464480;
        }
        local_c = local_c + 1;
        if (0x200 < local_c) break;
        *local_8 = *DAT_0045f860;
        local_8 = local_8 + 1;
        DAT_0045f860 = DAT_0045f860 + 1;
      }
      FUN_00413085((uint *)s_Symbol_name_too_long_00459a6c);
    }
  }
  return (undefined1 *)0x0;
}


/* ==== FUN_0043b5bb @ 0043b5bb ==== */

undefined4 __cdecl FUN_0043b5bb(char *param_1)

{
  int iVar1;
  uint local_10;
  char *local_c;
  char local_8;
  
  local_c = param_1;
  iVar1 = FUN_004080dc((int *)&local_c);
  if (iVar1 != -1) {
    if (__mb_cur_max < 2) {
      local_10 = *(ushort *)(_pctype + *local_c * 2) & 0x107;
    }
    else {
      local_10 = _isctype((int)*local_c,0x107);
    }
    if ((local_10 == 0) && (*local_c != '_')) {
      local_8 = *local_c;
      *local_c = '\0';
      FUN_004131f9((uint *)s_Reserved_name_used_for_symbol_na_00459a84,param_1);
      *local_c = local_8;
      return 0;
    }
  }
  return 1;
}


/* ==== FUN_0043b659 @ 0043b659 ==== */

undefined4 __cdecl FUN_0043b659(char *param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint local_10;
  uint local_c;
  int local_8;
  
  local_8 = 1;
  if (*param_1 == '\0') {
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_0043b5bb(param_1);
    if (iVar2 == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      if (*param_1 == DAT_0044f830) {
        param_1 = param_1 + 1;
      }
      if (__mb_cur_max < 2) {
        local_c = *(ushort *)(_pctype + *param_1 * 2) & 0x103;
      }
      else {
        local_c = _isctype((int)*param_1,0x103);
      }
      if (local_c == 0) {
        FUN_00413085((uint *)s_Symbols_must_start_with_alphabet_00459aa8);
        uVar1 = 0xffffffff;
      }
      else {
        do {
          param_1 = param_1 + 1;
          if (__mb_cur_max < 2) {
            local_10 = *(ushort *)(_pctype + *param_1 * 2) & 0x107;
          }
          else {
            local_10 = _isctype((int)*param_1,0x107);
          }
          if ((local_10 == 0) && (*param_1 != '_')) {
            if (*param_1 != '\0') {
              FUN_00413085((uint *)s_Extra_characters_following_symbo_00459af0);
              return 0xffffffff;
            }
            return 1;
          }
          local_8 = local_8 + 1;
        } while (local_8 < 0x201);
        FUN_00413085((uint *)s_Symbol_name_too_long_00459ad8);
        uVar1 = 0xffffffff;
      }
    }
  }
  return uVar1;
}


/* ==== FUN_0043b7aa @ 0043b7aa ==== */

char * __cdecl FUN_0043b7aa(char *param_1)

{
  int iVar1;
  char local_10;
  uint local_c;
  char *local_8;
  
  for (local_8 = param_1; *local_8 != '\0'; local_8 = local_8 + 1) {
    if (__mb_cur_max < 2) {
      local_c = *(ushort *)(_pctype + *local_8 * 2) & 2;
    }
    else {
      local_c = _isctype((int)*local_8,2);
    }
    if (local_c == 0) {
      local_10 = *local_8;
    }
    else {
      iVar1 = toupper((int)*local_8);
      local_10 = (char)iVar1;
    }
    *local_8 = local_10;
  }
  return param_1;
}


/* ==== FUN_0043b836 @ 0043b836 ==== */

char * __cdecl FUN_0043b836(char *param_1)

{
  int iVar1;
  char local_10;
  uint local_c;
  char *local_8;
  
  for (local_8 = param_1; *local_8 != '\0'; local_8 = local_8 + 1) {
    if (__mb_cur_max < 2) {
      local_c = *(ushort *)(_pctype + *local_8 * 2) & 1;
    }
    else {
      local_c = _isctype((int)*local_8,1);
    }
    if (local_c == 0) {
      local_10 = *local_8;
    }
    else {
      iVar1 = tolower((int)*local_8);
      local_10 = (char)iVar1;
    }
    *local_8 = local_10;
  }
  return param_1;
}


/* ==== FUN_0043b8c2 @ 0043b8c2 ==== */

char * __cdecl FUN_0043b8c2(char *param_1)

{
  char *pcVar1;
  
  if (param_1 == (char *)0x0) {
    pcVar1 = (char *)0x0;
  }
  else {
    strncpy(&DAT_00464688,param_1,0x20);
    pcVar1 = FUN_0043b7aa(&DAT_00464688);
  }
  return pcVar1;
}


/* ==== FUN_0043b8f1 @ 0043b8f1 ==== */

void __cdecl FUN_0043b8f1(int *param_1,int param_2)

{
  char *local_8;
  
  if (param_2 == 0) {
    local_8 = &DAT_00463c80;
  }
  else {
    local_8 = &DAT_004646b0;
  }
  setvbuf(param_1,local_8,0,0x800);
  return;
}


/* ==== FUN_0043b926 @ 0043b926 ==== */

bool __cdecl FUN_0043b926(int param_1)

{
  bool bVar1;
  
  bVar1 = false;
  if (param_1 != 0) {
    DAT_00464ebc = 0;
    DAT_00464eb8 = 0;
    DAT_00464eb4 = 0;
    DAT_00464eb0 = 0;
    bVar1 = *DAT_0045f8c0 < *DAT_0045f8d4;
    if (bVar1) {
      FUN_004133a9((uint *)s_Runtime_location_counter_underfl_00459b18);
    }
    if ((DAT_0045f8c0 != DAT_0045f8cc) && (*DAT_0045f8cc < *DAT_0045f8dc)) {
      FUN_004133a9((uint *)s_Load_location_counter_underflow_00459b3c);
      bVar1 = true;
    }
  }
  if (DAT_0045eab8 == '\0') {
    if ((DAT_00464eb0 == 0) &&
       ((*DAT_0045f8d8 < *DAT_0045f8c0 ||
        (*DAT_0045f8c0 = *DAT_0045f8c0 & DAT_0044f91c, *DAT_0045f8c0 < DAT_0045f8c4)))) {
      DAT_0045eab8 = '\x01';
      *DAT_0045f8c0 = *DAT_0045f8c0 & DAT_0044f91c;
    }
  }
  else {
    FUN_004133a9((uint *)s_Runtime_location_counter_overflo_00459b5c);
    DAT_0045eab8 = '\0';
    bVar1 = true;
    DAT_00464eb0 = 1;
  }
  if (DAT_0045f8c0 != DAT_0045f8cc) {
    if (DAT_0045eabc == '\0') {
      if ((DAT_00464eb4 == 0) &&
         ((*DAT_0045f8e0 < *DAT_0045f8cc ||
          (*DAT_0045f8cc = *DAT_0045f8cc & DAT_0044f920, *DAT_0045f8cc < DAT_0045f8d0)))) {
        DAT_0045eabc = '\x01';
        *DAT_0045f8cc = *DAT_0045f8cc & DAT_0044f920;
      }
    }
    else {
      FUN_004133a9((uint *)s_Load_location_counter_overflow_00459b80);
      DAT_0045eabc = '\0';
      bVar1 = true;
      DAT_00464eb4 = 1;
    }
  }
  return bVar1;
}


/* ==== FUN_0043baf1 @ 0043baf1 ==== */

int __cdecl FUN_0043baf1(int param_1,int param_2)

{
  int local_8;
  
  if (param_1 < 0x1d) {
    if (param_1 == 0x1c) {
      if ((param_2 != 0x1c) && (param_2 != 4)) {
        return 0xa2c2a;
      }
      return 0x1c;
    }
    switch(param_1) {
    case 0:
      if ((param_2 == 0) || (param_2 == 4)) {
        local_8 = 0;
      }
      else {
        local_8 = 0xa2c2a;
      }
      break;
    case 1:
      if ((param_2 == 2) || (param_2 == 0)) {
        local_8 = 0xa2c2a;
      }
      else {
        local_8 = 1;
      }
      break;
    case 2:
      if ((param_2 == 1) || (param_2 == 0)) {
        local_8 = 0xa2c2a;
      }
      else {
        local_8 = 2;
      }
      break;
    case 3:
      if (param_2 == 0) {
        local_8 = 0xa2c2a;
      }
      else if ((param_2 == 1) || (param_2 == 2)) {
        local_8 = param_2;
      }
      else {
        local_8 = 3;
      }
      break;
    default:
      goto switchD_0043bb1a_default;
    }
  }
  else {
    if (param_1 == 0x11d) {
      if ((param_2 != 0x11d) && (param_2 != 4)) {
        return 0xa2c2a;
      }
      return 0x11d;
    }
switchD_0043bb1a_default:
    local_8 = param_2;
  }
  return local_8;
}


/* ==== FUN_0043bc1b @ 0043bc1b ==== */

void FUN_0043bc1b(void)

{
  uint local_8;
  
  if (DAT_0045f860 != (char *)0x0) {
    for (; *DAT_0045f860 != '\0'; DAT_0045f860 = DAT_0045f860 + 1) {
      if (__mb_cur_max < 2) {
        local_8 = *(ushort *)(_pctype + *DAT_0045f860 * 2) & 0x107;
      }
      else {
        local_8 = _isctype((int)*DAT_0045f860,0x107);
      }
      if ((local_8 == 0) && (*DAT_0045f860 != '_')) break;
    }
    if ((*DAT_0045f860 != '\0') && (*DAT_0045f860 == ',')) {
      DAT_0045f860 = DAT_0045f860 + 1;
    }
  }
  return;
}


/* ==== FUN_0043bccb @ 0043bccb ==== */

bool FUN_0043bccb(void)

{
  char cVar1;
  undefined4 uVar2;
  
  uVar2 = DAT_0045f860;
  cVar1 = *PTR_DAT_0044f820;
  if (cVar1 != '\0') {
    DAT_0045f860 = PTR_DAT_0044f820;
    FUN_00413085((uint *)s_Too_many_fields_specified_for_in_00459ba0);
    FUN_00413085((uint *)s_Possible_invalid_white_space_bet_00459bcc);
  }
  DAT_0045f860 = (undefined *)uVar2;
  return cVar1 == '\0';
}


/* ==== FUN_0043bd1e @ 0043bd1e ==== */

uint __cdecl FUN_0043bd1e(uint param_1,uint param_2,byte param_3,byte param_4)

{
  return param_1 & ~(~(-1 << (param_4 & 0x1f)) << (param_3 & 0x1f)) |
         (param_2 & ~(-1 << (param_4 & 0x1f))) << (param_3 & 0x1f);
}


/* ==== FUN_0043bd53 @ 0043bd53 ==== */

void __cdecl FUN_0043bd53(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  char *dst;
  undefined4 in_stack_00000010;
  char local_404 [1024];
  
  if (param_3 == 0) {
    sprintf(local_404,s____s___0<<_d))_(_s&~(~0<<_d)))_00459c08,param_1,in_stack_00000010,param_2,
            in_stack_00000010);
  }
  else {
    sprintf(local_404,s____s______0<<_d)<<_d))_((_s&~(~0_00459c28,param_1,in_stack_00000010,param_3,
            param_2,in_stack_00000010,param_3);
  }
  uVar1 = strlen(local_404);
  dst = (char *)FUN_00439857(uVar1 + 1);
  strcpy(dst,local_404);
  return;
}


/* ==== FUN_0043bdfb @ 0043bdfb ==== */

void __cdecl FUN_0043bdfb(int param_1,int param_2,int param_3,byte param_4)

{
  undefined uVar1;
  uint uVar2;
  undefined3 extraout_var;
  undefined3 in_stack_00000011;
  
  if (*(int *)(param_2 + 0x1c) == 0) {
    uVar2 = FUN_0043bd1e(*(uint *)(param_1 + 4),*(uint *)(param_2 + 0x10),(byte)param_3,param_4);
    *(uint *)(param_1 + 4) = uVar2;
  }
  else {
    sprintf(&DAT_0045f220,s___0_lX_00459c58,6,*(undefined4 *)(param_1 + 4));
    uVar1 = FUN_0043bd53(&DAT_0045f220,*(undefined4 *)(param_2 + 0x1c),param_3,_param_4);
    *(uint *)(param_1 + 0x40) = CONCAT31(extraout_var,uVar1);
    FUN_004398b5(*(undefined **)(param_2 + 0x1c));
    *(undefined4 *)(param_2 + 0x1c) = 0;
  }
  return;
}


/* ==== FUN_0043be85 @ 0043be85 ==== */

void __cdecl
FUN_0043be85(int param_1,int param_2,uint param_3,byte param_4,byte param_5,byte param_6,
            uint param_7,byte param_8,byte param_9,byte param_10)

{
  undefined uVar1;
  uint uVar2;
  undefined3 extraout_var;
  undefined3 in_stack_00000011;
  undefined3 in_stack_00000015;
  undefined3 in_stack_00000019;
  undefined3 in_stack_00000021;
  undefined3 in_stack_00000025;
  undefined3 in_stack_00000029;
  
  if (*(int *)(param_2 + 0x1c) == 0) {
    uVar2 = FUN_0043bf3d(*(uint *)(param_1 + 4),*(uint *)(param_2 + 0x10),param_3,param_4,param_5,
                         param_6,param_7,param_8,param_9,param_10);
    *(uint *)(param_1 + 4) = uVar2;
  }
  else {
    sprintf(&DAT_0045f220,s___06lX_00459c60,*(undefined4 *)(param_1 + 4));
    uVar1 = FUN_0043bfa7(&DAT_0045f220,*(undefined4 *)(param_2 + 0x1c),param_3,_param_4,_param_5,
                         _param_6,param_7,_param_8,_param_9,_param_10);
    *(uint *)(param_1 + 0x40) = CONCAT31(extraout_var,uVar1);
    FUN_004398b5(*(undefined **)(param_2 + 0x1c));
    *(undefined4 *)(param_2 + 0x1c) = 0;
  }
  return;
}


/* ==== FUN_0043bf3d @ 0043bf3d ==== */

uint __cdecl
FUN_0043bf3d(uint param_1,uint param_2,uint param_3,byte param_4,byte param_5,byte param_6,
            uint param_7,byte param_8,byte param_9,byte param_10)

{
  return ((param_2 & param_7) >> (param_8 & 0x1f) & ~(-1 << (param_10 & 0x1f))) << (param_9 & 0x1f)
         | param_1 & ~(~(-1 << (param_6 & 0x1f)) << (param_5 & 0x1f) |
                      ~(-1 << (param_10 & 0x1f)) << (param_9 & 0x1f)) |
           ((param_2 & param_3) >> (param_4 & 0x1f) & ~(-1 << (param_6 & 0x1f))) << (param_5 & 0x1f)
  ;
}


/* ==== FUN_0043bfa7 @ 0043bfa7 ==== */

void FUN_0043bfa7(void)

{
  uint uVar1;
  char *dst;
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  undefined4 in_stack_0000000c;
  undefined4 in_stack_00000010;
  undefined4 in_stack_00000014;
  undefined4 in_stack_00000018;
  undefined4 in_stack_0000001c;
  undefined4 in_stack_00000020;
  undefined4 in_stack_00000024;
  undefined4 in_stack_00000028;
  char local_404 [1024];
  
  sprintf(local_404,s____s_______0<<_d)<<_d)_(~(~0<<_d_00459c68,in_stack_00000004,in_stack_00000018,
          in_stack_00000014,in_stack_00000028,in_stack_00000024,in_stack_00000008,in_stack_0000000c,
          in_stack_00000010,in_stack_00000018,in_stack_00000014,in_stack_00000008,in_stack_0000001c,
          in_stack_00000020,in_stack_00000028,in_stack_00000024);
  uVar1 = strlen(local_404);
  dst = (char *)FUN_00439857(uVar1 + 1);
  strcpy(dst,local_404);
  return;
}


/* ==== FUN_0043c047 @ 0043c047 ==== */

void __cdecl FUN_0043c047(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  uint uVar1;
  char local_208 [512];
  char *local_8;
  
  sprintf(local_208,s__enc__s___lX__s__s__00459cd8,param_1,param_2,*(undefined4 *)(param_3 + 0x40),
          *(undefined4 *)(param_4 + 0x40));
  uVar1 = strlen(local_208);
  local_8 = (char *)FUN_00439857(uVar1 + 1);
  strcpy(local_8,local_208);
  FUN_004398b5(*(undefined **)(param_3 + 0x40));
  *(undefined4 *)(param_3 + 0x40) = 0;
  FUN_004398b5(*(undefined **)(param_4 + 0x40));
  *(undefined4 *)(param_4 + 0x40) = 0;
  *(char **)(param_3 + 0x40) = local_8;
  return;
}


/* ==== FUN_0043c0ea @ 0043c0ea ==== */

uint * __cdecl FUN_0043c0ea(uint *param_1,uint *param_2,int param_3,uint param_4)

{
  char cVar1;
  uint uVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  uint local_22c;
  uint *local_228;
  char *local_224;
  char *local_220;
  int local_21c;
  undefined4 local_218;
  char local_214 [512];
  int local_14;
  uint local_10;
  char local_c;
  char *local_8;
  
  local_14 = param_3;
  local_10 = param_4;
  local_218 = (uint)((param_4 & 0x80000000) != 0);
  if ((param_4 & 0x7ff00000) == 0x7ff00000) {
    if ((param_3 == 0) && ((param_4 & 0xfffff) == 0)) {
      if (local_218 == 0) {
        local_220 = &DAT_00459cf4;
      }
      else {
        local_220 = &DAT_00459cec;
      }
      strcpy((char *)param_1,local_220);
    }
    else {
      if (local_218 == 0) {
        local_224 = &DAT_00459d00;
      }
      else {
        local_224 = &DAT_00459cf8;
      }
      strcpy((char *)param_1,local_224);
    }
  }
  else {
    strcpy(local_214,(char *)param_2);
    uVar2 = strlen(local_214);
    local_8 = local_214 + (uVar2 - 1);
    if ((local_14 == 0) && ((local_10 & 0x7fffffff) == 0)) {
      local_c = *local_8;
      *local_8 = 'f';
      if (local_218 == 0) {
        local_228 = param_1;
      }
      else {
        local_228 = (uint *)((int)param_1 + 1);
      }
      sprintf((char *)local_228,local_214,0,0);
      *local_8 = local_c;
      if (local_218 != 0) {
        *(undefined1 *)param_1 = 0x2d;
      }
      strcat((char *)param_1,s_E_000_00459d04);
    }
    else {
      sprintf((char *)param_1,local_214,param_3,param_4);
    }
    cVar1 = strchr((char *)param_1,0x45);
    local_21c = CONCAT31(extraout_var,cVar1);
    if (local_21c == 0) {
      cVar1 = strchr((char *)param_1,0x65);
      local_21c = CONCAT31(extraout_var_00,cVar1);
    }
    if (local_21c != 0) {
      if (*(char *)(local_21c + 4) != '\0') {
        if (__mb_cur_max < 2) {
          local_22c = *(ushort *)(_pctype + *(char *)(local_21c + 4) * 2) & 8;
        }
        else {
          local_22c = _isctype((int)*(char *)(local_21c + 4),8);
        }
        if (local_22c == 0) {
          return param_1;
        }
      }
      *(undefined1 *)(local_21c + 5) = 0;
      *(undefined1 *)(local_21c + 4) = *(undefined1 *)(local_21c + 3);
      *(undefined1 *)(local_21c + 3) = *(undefined1 *)(local_21c + 2);
      *(undefined1 *)(local_21c + 2) = 0x30;
    }
  }
  return param_1;
}


/* ==== FUN_0043c34d @ 0043c34d ==== */

void FUN_0043c34d(void)

{
  memset(&DAT_00465a60,0,0x20);
  DAT_00465a6c = 4;
  memset(&DAT_00465880,0,0x20);
  return;
}


/* ==== FUN_0043c37e @ 0043c37e ==== */

/* WARNING: Removing unreachable block (ram,0x0043c3bc) */
/* WARNING: Removing unreachable block (ram,0x0043c3f8) */
/* WARNING: Removing unreachable block (ram,0x0043c400) */
/* WARNING: Removing unreachable block (ram,0x0043c423) */
/* WARNING: Removing unreachable block (ram,0x0043c3ef) */
/* WARNING: Removing unreachable block (ram,0x0043c436) */
/* WARNING: Removing unreachable block (ram,0x0043c391) */

uint __cdecl FUN_0043c37e(char *param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  
  uVar1 = fwrite(param_1,param_2,param_3,param_4);
  return uVar1;
}


/* ==== FUN_0043c450 @ 0043c450 ==== */

void __cdecl FUN_0043c450(char *param_1,uint param_2,uint param_3,int *param_4)

{
  FUN_0043c4b2(param_1,param_2,param_3);
  fwrite(param_1,param_2,param_3,param_4);
  return;
}


/* ==== FUN_0043c481 @ 0043c481 ==== */

void __cdecl FUN_0043c481(char *param_1,uint param_2,uint param_3,int *param_4)

{
  FUN_0043c4b2(param_1,param_2,param_3);
  FUN_0043c37e(param_1,param_2,param_3,param_4);
  return;
}


/* ==== FUN_0043c4b2 @ 0043c4b2 ==== */

void __cdecl FUN_0043c4b2(undefined1 *param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  undefined1 *local_c;
  
  for (local_c = param_1; local_c < param_1 + (param_2 * param_3 & 0xfffffffc);
      local_c = local_c + 4) {
    uVar1 = *local_c;
    *local_c = local_c[3];
    local_c[3] = uVar1;
    uVar1 = local_c[1];
    local_c[1] = local_c[2];
    local_c[2] = uVar1;
  }
  return;
}


/* ==== FUN_0043c528 @ 0043c528 ==== */

int __cdecl FUN_0043c528(int *param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  uint local_30;
  int local_2c [4];
  int local_1c;
  uint local_18;
  int local_10;
  int local_8;
  
  if (param_1 == (int *)0x0) {
    iVar1 = -1;
  }
  else {
    piVar3 = local_2c;
    for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar3 = *param_1;
      param_1 = param_1 + 1;
      piVar3 = piVar3 + 1;
    }
    for (; 0x3b < local_2c[0]; local_2c[0] = local_2c[0] + -0x3c) {
      local_2c[1] = local_2c[1] + 1;
    }
    for (; local_2c[0] < 0; local_2c[0] = local_2c[0] + 0x3c) {
      local_2c[1] = local_2c[1] + -1;
    }
    for (; 0x3b < local_2c[1]; local_2c[1] = local_2c[1] + -0x3c) {
      local_2c[2] = local_2c[2] + 1;
    }
    for (; local_2c[1] < 0; local_2c[1] = local_2c[1] + 0x3c) {
      local_2c[2] = local_2c[2] + -1;
    }
    for (; 0x17 < local_2c[2]; local_2c[2] = local_2c[2] + -0x18) {
      local_2c[3] = local_2c[3] + 1;
    }
    for (; local_2c[2] < 0; local_2c[2] = local_2c[2] + 0x18) {
      local_2c[3] = local_2c[3] + -1;
    }
    for (; 0x1f < local_2c[3]; local_2c[3] = local_2c[3] + -0x1f) {
      local_1c = local_1c + 1;
    }
    for (; local_2c[3] < 1; local_2c[3] = local_2c[3] + 0x1f) {
      local_1c = local_1c + -1;
    }
    for (; 0xb < local_1c; local_1c = local_1c + -0xc) {
      local_18 = local_18 + 1;
    }
    for (; local_1c < 0; local_1c = local_1c + 0xc) {
      local_18 = local_18 - 1;
    }
    if ((((((int)local_18 < 0) || (local_1c < 0)) || (0xb < local_1c)) ||
        ((local_2c[3] < 0 || (local_2c[2] < 0)))) ||
       ((((0x17 < local_2c[2] || ((local_2c[1] < 0 || (0x3b < local_2c[1])))) || (local_2c[0] < 0))
        || (0x3b < local_2c[0])))) {
      iVar1 = -1;
    }
    else {
      uVar2 = (int)local_18 >> 0x1f;
      if ((((((local_18 ^ uVar2) - uVar2 & 3 ^ uVar2) == uVar2) && ((int)local_18 % 100 != 0)) ||
          ((int)local_18 % 400 == 0)) && ((local_1c == 1 && (0x1d < local_2c[3])))) {
        iVar1 = -1;
      }
      else if (*(int *)(&DAT_00450508 + local_1c * 4) < local_2c[3]) {
        iVar1 = -1;
      }
      else {
        local_8 = (local_18 - 0x46) * 0x16d;
        for (local_30 = 0x7b2; (int)local_30 < (int)(local_18 + 0x76c); local_30 = local_30 + 1) {
          uVar2 = (int)local_30 >> 0x1f;
          if (((((local_30 ^ uVar2) - uVar2 & 3 ^ uVar2) == uVar2) && ((int)local_30 % 100 != 0)) ||
             ((int)local_30 % 400 == 0)) {
            local_8 = local_8 + 1;
          }
        }
        iVar1 = (local_8 + local_10) * 0x15180 + local_2c[2] * 0xe10 + local_2c[1] * 0x3c +
                local_2c[0];
      }
    }
  }
  return iVar1;
}


/* ==== FUN_0043c7a6 @ 0043c7a6 ==== */

undefined4 FUN_0043c7a6(void)

{
  undefined4 local_c;
  char *local_8;
  
  local_c = 0;
  local_8 = DAT_0045f860;
  if (DAT_0045f860 != (char *)0x0) {
    for (; (*local_8 != '\0' && (*local_8 != ',')); local_8 = local_8 + 1) {
    }
    if ((*local_8 != '\0') && ((*local_8 == ',' && (local_8[2] == ':')))) {
      local_c = 1;
    }
  }
  return local_c;
}


/* ==== FUN_0043c810 @ 0043c810 ==== */

int FUN_0043c810(void)

{
  int extraout_EAX;
  
  malloc(0x14);
  if (extraout_EAX == 0) {
    FUN_00413085((uint *)s_internal_error__Stack_creation_f_00459d0c);
    exit(1);
  }
  *(code **)(extraout_EAX + 0xc) = FUN_0043c870;
  *(code **)(extraout_EAX + 8) = FUN_0043c88d;
  *(code **)(extraout_EAX + 0x10) = FUN_0043c91d;
  (**(code **)(extraout_EAX + 0xc))(extraout_EAX);
  return extraout_EAX;
}


/* ==== FUN_0043c870 @ 0043c870 ==== */

undefined4 __cdecl FUN_0043c870(undefined4 *param_1)

{
  param_1[1] = 0;
  *param_1 = 0;
  return 1;
}


/* ==== FUN_0043c88d @ 0043c88d ==== */

undefined4 __cdecl FUN_0043c88d(int *param_1,undefined4 param_2)

{
  int iVar1;
  int extraout_EAX;
  undefined4 *extraout_EAX_00;
  
  iVar1 = *param_1;
  if (*param_1 == 0) {
    malloc(8);
    *param_1 = extraout_EAX;
    if (*param_1 == 0) {
      FUN_00413085((uint *)s_Can_t_create_node_00459d34);
      exit(1);
    }
    *(undefined4 *)*param_1 = param_2;
  }
  else {
    malloc(8);
    *extraout_EAX_00 = param_2;
    *param_1 = (int)extraout_EAX_00;
    *(int *)(*param_1 + 4) = iVar1;
  }
  param_1[1] = param_1[1] + 1;
  return 1;
}


/* ==== FUN_0043c91d @ 0043c91d ==== */

undefined4 __cdecl FUN_0043c91d(int *param_1)

{
  int iVar1;
  void *p;
  undefined4 uVar2;
  
  iVar1 = *(int *)(*param_1 + 4);
  p = (void *)*param_1;
  if (param_1 == (int *)0x0) {
    FUN_00413085((uint *)s_no_such_stack_pointer_00459d48);
  }
  else if (*param_1 == 0) {
    return 0;
  }
  uVar2 = *(undefined4 *)*param_1;
  *param_1 = iVar1;
  free(p);
  param_1[1] = param_1[1] + -1;
  return uVar2;
}


/* ==== FUN_0043c98b @ 0043c98b ==== */

void __cdecl FUN_0043c98b(int *param_1)

{
  undefined4 local_8;
  
  if (param_1 != (int *)0x0) {
    if (*param_1 != 0) {
      for (local_8 = (void *)*param_1; local_8 != (void *)0x0;
          local_8 = *(void **)((int)local_8 + 4)) {
        free(local_8);
      }
    }
    free(param_1);
  }
  return;
}


/* ==== FUN_0043c9d4 @ 0043c9d4 ==== */

int __cdecl FUN_0043c9d4(char *param_1,byte *param_2,int param_3,int param_4)

{
  char cVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  uint uVar2;
  undefined4 extraout_EAX;
  undefined3 extraout_var_01;
  int local_c;
  char *local_8;
  char *s;
  
  local_c = 0;
  cVar1 = _strdup(param_1);
  s = (char *)CONCAT31(extraout_var,cVar1);
  if (s == (char *)0x0) {
    local_c = 0;
  }
  else {
    cVar1 = strtok(s,(char *)param_2);
    local_8 = (char *)CONCAT31(extraout_var_00,cVar1);
    while ((local_8 != (char *)0x0 && (local_c < param_4))) {
      uVar2 = strlen(local_8);
      malloc(uVar2 + 1);
      *(undefined4 *)(param_3 + local_c * 4) = extraout_EAX;
      strcpy(*(char **)(param_3 + local_c * 4),local_8);
      local_c = local_c + 1;
      cVar1 = strtok((char *)0x0,(char *)param_2);
      local_8 = (char *)CONCAT31(extraout_var_01,cVar1);
    }
    if (s != (char *)0x0) {
      free(s);
    }
  }
  return local_c;
}


/* ==== FUN_0043ca8c @ 0043ca8c ==== */

void __cdecl FUN_0043ca8c(undefined4 *param_1,undefined4 *param_2)

{
  strcmp((char *)*param_1,(char *)*param_2);
  return;
}


/* ==== FUN_0043cab6 @ 0043cab6 ==== */

void __cdecl FUN_0043cab6(undefined4 *param_1,undefined4 *param_2)

{
  strcmp((char *)*param_1,(char *)*param_2);
  return;
}


/* ==== FUN_0043cae0 @ 0043cae0 ==== */

void FUN_0043cae0(void)

{
  int *stream;
  undefined4 va1;
  undefined4 va0;
  int iVar1;
  int local_c;
  
  fopen(s_instlist_out_00459d64,&DAT_00459d60);
  if (stream == (int *)0x0) {
    printf(s_Can_t_open_instlist_out_00459d74);
  }
  else {
    for (local_c = 0; local_c < DAT_00464ec4; local_c = local_c + 1) {
      fprintf(stream,s___10d_00459d90,local_c);
      iVar1 = DAT_00464ecc + local_c * 0x44;
      if (iVar1 != 0) {
        va1 = FUN_0043cc9f(iVar1);
        va0 = FUN_0043cc75(iVar1);
        fprintf(stream,s_pc___10ld_ctr___10ld_00459d98,va0,va1);
        FUN_0043cba9(iVar1,stream);
      }
    }
    fclose(stream);
  }
  return;
}


/* ==== FUN_0043cba9 @ 0043cba9 ==== */

void __cdecl FUN_0043cba9(int param_1,int *param_2)

{
  uint uVar1;
  uint local_8;
  
  for (local_8 = 0; (int)local_8 < 0x2e; local_8 = local_8 + 1) {
    uVar1 = FUN_0043d028(param_1,local_8);
    if (uVar1 != 0) {
      fprintf(param_2,s_attrib__s_is_set_0045a2fc,(&PTR_s_ia_none_00459db0)[local_8]);
    }
  }
  return;
}


/* ==== FUN_0043cbfb @ 0043cbfb ==== */

void FUN_0043cbfb(void)

{
  FUN_004398b5(DAT_00464ecc);
  DAT_00464ec0 = 0;
  DAT_00464ec4 = 0;
  DAT_00464ec8 = 0;
  return;
}


/* ==== FUN_0043cc37 @ 0043cc37 ==== */

void __cdecl FUN_0043cc37(int param_1,undefined4 param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  
  bVar1 = FUN_0043cc4e();
  if (CONCAT31(extraout_var,bVar1) != 0) {
    *(undefined4 *)(param_1 + 4) = param_2;
  }
  return;
}


/* ==== FUN_0043cc4e @ 0043cc4e ==== */

bool FUN_0043cc4e(void)

{
  return DAT_00464ec4 != 0;
}


/* ==== FUN_0043cc5f @ 0043cc5f ==== */

void __cdecl FUN_0043cc5f(undefined4 *param_1,undefined4 param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  
  bVar1 = FUN_0043cc4e();
  if (CONCAT31(extraout_var,bVar1) != 0) {
    *param_1 = param_2;
  }
  return;
}


/* ==== FUN_0043cc75 @ 0043cc75 ==== */

undefined4 __cdecl FUN_0043cc75(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = *(undefined4 *)(param_1 + 4);
  }
  return uVar1;
}


/* ==== FUN_0043cc8b @ 0043cc8b ==== */

void __cdecl FUN_0043cc8b(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 8) = param_2;
  }
  return;
}


/* ==== FUN_0043cc9f @ 0043cc9f ==== */

undefined4 __cdecl FUN_0043cc9f(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = *(undefined4 *)(param_1 + 8);
  }
  return uVar1;
}


/* ==== FUN_0043ccb5 @ 0043ccb5 ==== */

void FUN_0043ccb5(void)

{
  if ((DAT_00464ec4 == 0) || (DAT_00464ec0 <= DAT_00464ec4)) {
    FUN_0043ccf3();
  }
  DAT_00464ec4 = DAT_00464ec4 + 1;
  DAT_00464ec8 = DAT_00464ec8 + 1;
  return;
}


/* ==== FUN_0043ccf3 @ 0043ccf3 ==== */

void FUN_0043ccf3(void)

{
  int extraout_EAX;
  int extraout_EAX_00;
  undefined4 local_8;
  
  if (DAT_00464ec4 < 1) {
    malloc(68000);
    local_8 = extraout_EAX_00;
  }
  else {
    realloc(DAT_00464ecc,(DAT_00464ec4 + 1000) * 0x44);
    local_8 = extraout_EAX;
  }
  memset((void *)(local_8 + DAT_00464ec0 * 0x44),0,68000);
  DAT_00464ecc = (void *)local_8;
  DAT_00464ec0 = DAT_00464ec0 + 1000;
  return;
}


/* ==== FUN_0043cd73 @ 0043cd73 ==== */

int FUN_0043cd73(void)

{
  return DAT_00464ec4 + -1;
}


/* ==== FUN_0043cd80 @ 0043cd80 ==== */

int FUN_0043cd80(void)

{
  int iVar1;
  
  iVar1 = DAT_00464ecc;
  if (-1 < DAT_00464ec8 + -1) {
    iVar1 = DAT_00464ecc + (DAT_00464ec8 + -1) * 0x44;
  }
  return iVar1;
}


/* ==== FUN_0043cdab @ 0043cdab ==== */

int __cdecl FUN_0043cdab(int param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  
  bVar1 = FUN_0043cc4e();
  if (CONCAT31(extraout_var,bVar1) == 0) {
    iVar2 = 0;
  }
  else if (param_1 < 1) {
    iVar2 = DAT_00464ecc;
    if (0 < DAT_00464ec4 + param_1) {
      iVar2 = DAT_00464ecc + (DAT_00464ec4 + -1 + param_1) * 0x44;
    }
  }
  else {
    iVar2 = (DAT_00464ec4 + -1) * 0x44 + DAT_00464ecc;
  }
  return iVar2;
}


/* ==== FUN_0043ce03 @ 0043ce03 ==== */

void FUN_0043ce03(void)

{
  DAT_00464ec8 = 0;
  return;
}


/* ==== FUN_0043ce12 @ 0043ce12 ==== */

int FUN_0043ce12(void)

{
  int iVar1;
  
  if (DAT_00464ec0 <= DAT_00464ec8) {
    FUN_00412fa0((uint *)s_internal_error__instruction_tabl_0045a310);
  }
  iVar1 = DAT_00464ecc + DAT_00464ec8 * 0x44;
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    DAT_00464ec8 = DAT_00464ec8 + 1;
  }
  return iVar1;
}


/* ==== FUN_0043ce62 @ 0043ce62 ==== */

int __cdecl FUN_0043ce62(int param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  
  bVar1 = FUN_0043cc4e();
  if (CONCAT31(extraout_var,bVar1) == 0) {
    iVar2 = 0;
  }
  else if ((DAT_00464ec4 < param_1 + DAT_00464ec8) || (param_1 + -1 + DAT_00464ec8 < 0)) {
    iVar2 = 0;
  }
  else {
    iVar2 = (DAT_00464ec8 + -1 + param_1) * 0x44 + DAT_00464ecc;
  }
  return iVar2;
}


/* ==== FUN_0043ceb2 @ 0043ceb2 ==== */

void __cdecl FUN_0043ceb2(int param_1,uint param_2)

{
  bool bVar1;
  uint uVar2;
  undefined3 extraout_var;
  byte local_10;
  
  uVar2 = param_2 >> 5;
  if (param_2 < 0x20) {
    local_10 = (byte)param_2;
  }
  else {
    local_10 = (byte)(param_2 % 0x20);
  }
  if (1 < uVar2) {
    FUN_00412fa0((uint *)s_internal_error__instruction_attr_0045a344);
  }
  bVar1 = FUN_0043cc4e();
  if (CONCAT31(extraout_var,bVar1) != 0) {
    *(uint *)(param_1 + 0x10 + uVar2 * 4) =
         *(uint *)(param_1 + 0x10 + uVar2 * 4) | 1 << (local_10 & 0x1f);
  }
  return;
}


/* ==== FUN_0043cf24 @ 0043cf24 ==== */

void __cdecl FUN_0043cf24(int param_1,uint param_2)

{
  bool bVar1;
  uint uVar2;
  undefined3 extraout_var;
  byte local_10;
  
  uVar2 = param_2 >> 5;
  if (param_2 < 0x20) {
    local_10 = (byte)param_2;
  }
  else {
    local_10 = (byte)(param_2 % 0x20);
  }
  if (1 < uVar2) {
    FUN_00412fa0((uint *)s_internal_error__instruction_attr_0045a378);
  }
  bVar1 = FUN_0043cc4e();
  if (CONCAT31(extraout_var,bVar1) != 0) {
    *(uint *)(param_1 + 0x10 + uVar2 * 4) =
         *(uint *)(param_1 + 0x10 + uVar2 * 4) & ~(1 << (local_10 & 0x1f));
  }
  return;
}


/* ==== FUN_0043cf98 @ 0043cf98 ==== */

void __cdecl FUN_0043cf98(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  if (DAT_0045f8fc == 0) {
    iVar1 = FUN_0043ce62(-1);
    if (iVar1 != 0) {
      *(undefined4 *)(iVar1 + 0xc) = param_2;
    }
  }
  return;
}


/* ==== FUN_0043cfc5 @ 0043cfc5 ==== */

void __cdecl FUN_0043cfc5(undefined4 param_1,uint param_2)

{
  int iVar1;
  
  if (DAT_0045f8fc == 0) {
    iVar1 = FUN_0043ce62(-1);
    if (iVar1 != 0) {
      FUN_0043ceb2(iVar1,param_2);
    }
  }
  return;
}


/* ==== FUN_0043cff9 @ 0043cff9 ==== */

uint __cdecl FUN_0043cff9(uint param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_0043ce62(-1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0043d028(iVar1,param_1);
  }
  return uVar2;
}


/* ==== FUN_0043d028 @ 0043d028 ==== */

uint __cdecl FUN_0043d028(int param_1,uint param_2)

{
  uint uVar1;
  byte local_10;
  
  if (param_2 < 0x20) {
    local_10 = (byte)param_2;
  }
  else {
    local_10 = (byte)(param_2 % 0x20);
  }
  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    if (1 < param_2 >> 5) {
      FUN_00412fa0((uint *)s_internal_error__instruction_attr_0045a3ac);
    }
    uVar1 = 1 << (local_10 & 0x1f) & *(uint *)(param_1 + 0x10 + (param_2 >> 5) * 4);
  }
  return uVar1;
}


/* ==== FUN_0043d091 @ 0043d091 ==== */

void __cdecl FUN_0043d091(uint *param_1,int param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = (int)DAT_00464ee0;
  if (DAT_00464ee0 == (int *)0x0) {
    piVar1 = (int *)FUN_00439857(0x10);
    uVar2 = strlen((char *)param_1);
    iVar3 = FUN_00439857(uVar2 + 1);
    *piVar1 = iVar3;
    strcpy((char *)*piVar1,(char *)param_1);
    piVar1[1] = param_2;
    piVar1[2] = 0;
    piVar1[3] = 0;
    DAT_00464ee0 = piVar1;
  }
  else {
    piVar1 = (int *)FUN_00439857(0x10);
    uVar2 = strlen((char *)param_1);
    iVar4 = FUN_00439857(uVar2 + 1);
    *piVar1 = iVar4;
    strcpy((char *)*piVar1,(char *)param_1);
    piVar1[1] = param_2;
    *(int **)(iVar3 + 8) = piVar1;
    piVar1[3] = iVar3;
    piVar1[2] = 0;
    DAT_00464ee0 = piVar1;
  }
  return;
}


/* ==== FUN_0043d179 @ 0043d179 ==== */

void __cdecl FUN_0043d179(int *param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)param_1[3];
  iVar2 = param_1[2];
  if (piVar1 != (int *)0x0) {
    piVar1[2] = iVar2;
  }
  if (iVar2 != 0) {
    *(int **)(iVar2 + 0xc) = piVar1;
  }
  if (param_1 == DAT_00464ee0) {
    DAT_00464ee0 = piVar1;
  }
  if (*param_1 != 0) {
    FUN_004398b5((undefined *)*param_1);
  }
  FUN_004398b5((undefined *)param_1);
  return;
}


/* ==== FUN_0043d1e8 @ 0043d1e8 ==== */

void FUN_0043d1e8(void)

{
  int *piVar1;
  int *local_8;
  
  local_8 = DAT_00464ee0;
  while (local_8 != (int *)0x0) {
    piVar1 = (int *)local_8[3];
    if (*local_8 != 0) {
      FUN_004398b5((undefined *)*local_8);
    }
    FUN_004398b5((undefined *)local_8);
    local_8 = piVar1;
  }
  DAT_00464ee0 = (int *)0x0;
  return;
}


/* ==== FUN_0043d23d @ 0043d23d ==== */

undefined4 * __cdecl FUN_0043d23d(char *param_1)

{
  int iVar1;
  undefined4 *local_8;
  
  local_8 = DAT_00464ee0;
  while( true ) {
    if (local_8 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    iVar1 = strcmp((char *)*local_8,param_1);
    if (iVar1 == 0) break;
    local_8 = (undefined4 *)local_8[3];
  }
  return local_8;
}


/* ==== FUN_0043d27b @ 0043d27b ==== */

void FUN_0043d27b(void)

{
  if ((DAT_00464ed4 == 0) || (DAT_00464ed0 <= DAT_00464ed4)) {
    FUN_0043d2b9();
  }
  DAT_00464ed4 = DAT_00464ed4 + 1;
  DAT_00464ed8 = DAT_00464ed8 + 1;
  return;
}


/* ==== FUN_0043d2b9 @ 0043d2b9 ==== */

void FUN_0043d2b9(void)

{
  int extraout_EAX;
  int extraout_EAX_00;
  undefined4 local_8;
  
  if (DAT_00464ed4 < 1) {
    malloc(0x280);
    local_8 = extraout_EAX_00;
  }
  else {
    realloc(DAT_00464edc,(DAT_00464ed4 + 0x14) * 0x20);
    local_8 = extraout_EAX;
  }
  memset((void *)(local_8 + DAT_00464ed0 * 0x20),0,0x280);
  DAT_00464edc = (void *)local_8;
  DAT_00464ed0 = DAT_00464ed0 + 0x14;
  return;
}


/* ==== FUN_0043d343 @ 0043d343 ==== */

int FUN_0043d343(void)

{
  return (DAT_00464ed8 + -1) * 0x20 + DAT_00464edc;
}


/* ==== FUN_0043d35b @ 0043d35b ==== */

void __cdecl FUN_0043d35b(undefined4 *param_1,undefined4 param_2)

{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = param_2;
  }
  return;
}


/* ==== FUN_0043d36e @ 0043d36e ==== */

void __cdecl FUN_0043d36e(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 4) = param_2;
  }
  return;
}


/* ==== FUN_0043d382 @ 0043d382 ==== */

void __cdecl FUN_0043d382(int param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  
  if (param_1 != 0) {
    uVar1 = strlen((char *)param_2);
    iVar2 = FUN_00439857(uVar1 + 1);
    *(int *)(param_1 + 0xc) = iVar2;
    strcpy(*(char **)(param_1 + 0xc),(char *)param_2);
  }
  return;
}


/* ==== FUN_0043d3be @ 0043d3be ==== */

void __cdecl FUN_0043d3be(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 8) = param_2;
  }
  return;
}


/* ==== FUN_0043d3d2 @ 0043d3d2 ==== */

void __cdecl FUN_0043d3d2(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x1c) = param_2;
  }
  return;
}


/* ==== FUN_0043d3e6 @ 0043d3e6 ==== */

void __cdecl FUN_0043d3e6(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x10) = param_2;
  }
  return;
}


/* ==== FUN_0043d3fa @ 0043d3fa ==== */

void __cdecl FUN_0043d3fa(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = param_2;
  }
  return;
}


/* ==== FUN_0043d40e @ 0043d40e ==== */

void __cdecl FUN_0043d40e(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x18) = param_2;
  }
  return;
}


/* ==== FUN_0043d422 @ 0043d422 ==== */

void FUN_0043d422(void)

{
  undefined *puVar1;
  int local_8;
  
  for (local_8 = 0; local_8 < DAT_00464ed4; local_8 = local_8 + 1) {
    puVar1 = DAT_00464edc + local_8 * 0x20;
    if ((puVar1 != (undefined *)0x0) && (*(int *)(puVar1 + 0xc) != 0)) {
      FUN_004398b5(*(undefined **)(puVar1 + 0xc));
      *(undefined4 *)(puVar1 + 0xc) = 0;
    }
  }
  if (DAT_00464edc != (undefined *)0x0) {
    FUN_004398b5(DAT_00464edc);
  }
  DAT_00464ed0 = 0;
  DAT_00464ed4 = 0;
  DAT_00464ed8 = 0;
  return;
}


/* ==== FUN_0043d4bc @ 0043d4bc ==== */

int __cdecl FUN_0043d4bc(int param_1,int param_2)

{
  int iVar1;
  
  DAT_00464ec8 = 1;
  while( true ) {
    if (DAT_00464ec4 < DAT_00464ec8) {
      return 0;
    }
    iVar1 = FUN_0043cd80();
    if (((iVar1 != 0) && (*(int *)(iVar1 + 4) == param_1)) && (*(int *)(iVar1 + 8) == param_2))
    break;
    DAT_00464ec8 = DAT_00464ec8 + 1;
  }
  return iVar1;
}


/* ==== FUN_0043d51a @ 0043d51a ==== */

int * __cdecl FUN_0043d51a(int param_1)

{
  int *piVar1;
  int local_10;
  int local_c;
  int *local_8;
  
  local_8 = (int *)0x0;
  local_c = 5;
  for (local_10 = 0; local_10 < DAT_00464ed4; local_10 = local_10 + 1) {
    piVar1 = (int *)(DAT_00464edc + local_10 * 0x20);
    if (((piVar1 != (int *)0x0) && (*piVar1 == param_1)) && (local_c < piVar1[2])) {
      local_c = piVar1[2];
      local_8 = piVar1;
    }
  }
  return local_8;
}


/* ==== FUN_0043d58e @ 0043d58e ==== */

void FUN_0043d58e(void)

{
  int iVar1;
  int iVar2;
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < DAT_00464ed4; local_8 = local_8 + 1) {
    iVar1 = DAT_00464edc + local_8 * 0x20;
    if (iVar1 != 0) {
      iVar2 = FUN_0043d4bc(*(int *)(iVar1 + 0x10),*(int *)(iVar1 + 0x14));
      if (iVar2 != 0) {
        FUN_0043d601(iVar2,iVar1);
      }
    }
  }
  FUN_0043ce03();
  return;
}


/* ==== FUN_0043d601 @ 0043d601 ==== */

void __cdecl FUN_0043d601(int param_1,int param_2)

{
  uint uVar1;
  
  switch(*(undefined4 *)(param_2 + 8)) {
  case 0x25:
    uVar1 = FUN_0043d028(param_1,0xf);
    if (uVar1 != 0) {
      FUN_0043ceb2(param_1,0x2d);
    }
    FUN_0043ceb2(param_1,6);
    FUN_0043ceb2(param_1,0x24);
    *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_2 + 0xc);
    break;
  case 0x26:
    uVar1 = FUN_0043cff9(0xf);
    if (uVar1 != 0) {
      FUN_0043cfc5(param_1,0x2d);
    }
    FUN_0043cfc5(param_1,6);
    FUN_0043cfc5(param_1,0x24);
    FUN_0043cf98(param_1,*(undefined4 *)(param_2 + 0xc));
    break;
  case 0x27:
    uVar1 = FUN_0043d028(param_1,0xf);
    if (uVar1 != 0) {
      FUN_0043ceb2(param_1,0x2d);
    }
    FUN_0043ceb2(param_1,7);
    FUN_0043ceb2(param_1,0x24);
    *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_2 + 0xc);
    break;
  case 0x28:
    uVar1 = FUN_0043cff9(0xf);
    if (uVar1 != 0) {
      FUN_0043cfc5(param_1,0x2d);
    }
    FUN_0043cfc5(param_1,7);
    FUN_0043cfc5(param_1,0x24);
    FUN_0043cf98(param_1,*(undefined4 *)(param_2 + 0xc));
    break;
  case 0x29:
    FUN_0043ceb2(param_1,0x22);
    FUN_0043ceb2(param_1,0x24);
    *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_2 + 0xc);
    break;
  case 0x2a:
    FUN_0043ceb2(param_1,0x23);
    FUN_0043ceb2(param_1,0x24);
    *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_2 + 0xc);
    break;
  case 0x2b:
    FUN_0043cfc5(param_1,0x2c);
    FUN_0043cfc5(param_1,0x24);
    FUN_0043cf98(param_1,*(undefined4 *)(param_2 + 0xc));
  }
  return;
}


/* ==== FUN_0043d808 @ 0043d808 ==== */

void FUN_0043d808(void)

{
  int iVar1;
  
  for (DAT_00464ec8 = 1; DAT_00464ec8 <= DAT_00464ec4; DAT_00464ec8 = DAT_00464ec8 + 1) {
    iVar1 = FUN_0043cd80();
    if (iVar1 != 0) {
      (*DAT_00465a34)(iVar1);
      (*DAT_00465a38)(iVar1);
      (*DAT_00465a3c)(iVar1);
      (*DAT_00465a40)(iVar1);
      (*DAT_00465a44)(iVar1);
      (*DAT_00465a48)(iVar1);
      (*DAT_00465a4c)(iVar1);
      (*DAT_00465a50)(iVar1);
      (*DAT_00465a54)(iVar1);
      (*DAT_00465a58)(iVar1);
      (*DAT_00465a5c)(iVar1);
      (*DAT_00465a60)(iVar1);
      (*DAT_00465a64)(iVar1);
      (*DAT_00465a68)(iVar1);
      (*DAT_00465a6c)(iVar1);
      (*DAT_00465a70)(iVar1);
      (*DAT_00465a74)(iVar1);
      (*DAT_00465a78)(iVar1);
      (*DAT_00465a7c)(iVar1);
      (*DAT_00465a80)(iVar1);
      (*DAT_00465a84)(iVar1);
      (*DAT_00465a88)(iVar1);
      (*DAT_00465a8c)(iVar1);
      (*DAT_00465a90)(iVar1);
      (*DAT_00465a94)(iVar1);
      (*DAT_00465a98)(iVar1);
      (*DAT_00465a9c)(iVar1);
      (*DAT_00465aa0)(iVar1);
      (*DAT_00465aa4)(iVar1);
      (*DAT_00465aa8)(iVar1);
      (*DAT_00465aac)(iVar1);
      (*DAT_00465ab0)(iVar1);
      (*DAT_00465ab4)(iVar1);
      (*DAT_00465ab8)(iVar1);
      (*DAT_00465abc)(iVar1);
      (*DAT_00465ac0)(iVar1);
      (*DAT_00465ac4)(iVar1);
      (*DAT_00465ac8)(iVar1);
      (*DAT_00465acc)(iVar1);
      (*DAT_00465ad0)(iVar1);
      (*DAT_00465ad4)(iVar1);
    }
  }
  return;
}


/* ==== FUN_0043da70 @ 0043da70 ==== */

undefined4 * FUN_0043da70(void)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00439857(0x20);
  *puVar1 = 0;
  puVar1[1] = 0;
  puVar1[6] = FUN_0043dada;
  puVar1[3] = FUN_0043db06;
  puVar1[4] = FUN_0043dc32;
  puVar1[5] = FUN_0043dc80;
  puVar1[7] = FUN_0043dae9;
  (*(code *)puVar1[6])(puVar1);
  return puVar1;
}


/* ==== FUN_0043dada @ 0043dada ==== */

void __cdecl FUN_0043dada(int param_1)

{
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}


/* ==== FUN_0043dae9 @ 0043dae9 ==== */

void __cdecl FUN_0043dae9(int param_1)

{
  if (*(int *)(param_1 + 8) != 0) {
    FUN_004398b5(*(undefined **)(param_1 + 8));
  }
  return;
}


/* ==== FUN_0043db06 @ 0043db06 ==== */

void __cdecl FUN_0043db06(int *param_1,undefined4 param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  
  bVar1 = FUN_0043db63((int)param_1);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    bVar1 = FUN_0043db76(param_1);
    if (CONCAT31(extraout_var_00,bVar1) == 0) goto LAB_0043db36;
  }
  FUN_0043db8b(param_1);
LAB_0043db36:
  *(undefined4 *)(param_1[2] + param_1[1] * 4) = param_2;
  param_1[1] = param_1[1] + 1;
  return;
}


/* ==== FUN_0043db63 @ 0043db63 ==== */

bool __cdecl FUN_0043db63(int param_1)

{
  return *(int *)(param_1 + 4) == 0;
}


/* ==== FUN_0043db76 @ 0043db76 ==== */

bool __cdecl FUN_0043db76(int *param_1)

{
  return *param_1 < param_1[1];
}


/* ==== FUN_0043db8b @ 0043db8b ==== */

void __cdecl FUN_0043db8b(int *param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  int extraout_EAX;
  undefined3 extraout_var_00;
  int extraout_EAX_00;
  
  bVar1 = FUN_0043db63((int)param_1);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    bVar1 = FUN_0043db76(param_1);
    if (CONCAT31(extraout_var_00,bVar1) != 0) {
      realloc((void *)param_1[2],(*param_1 + 100) * 4);
      param_1[2] = extraout_EAX_00;
    }
  }
  else {
    malloc(400);
    param_1[2] = extraout_EAX;
  }
  if (param_1[2] == 0) {
    FUN_00412fa0((uint *)s_Internal_error__alloc_failed_0045a3e0);
  }
  else {
    memset((void *)(param_1[2] + *param_1 * 4),0,400);
  }
  *param_1 = *param_1 + 100;
  return;
}


/* ==== FUN_0043dc32 @ 0043dc32 ==== */

void __cdecl FUN_0043dc32(int *param_1,int param_2,undefined4 param_3)

{
  while (*param_1 <= param_2) {
    FUN_0043db8b(param_1);
  }
  *(undefined4 *)(param_1[2] + param_2 * 4) = param_3;
  if (param_1[1] <= param_2) {
    param_1[1] = param_2 + 1;
  }
  return;
}


/* ==== FUN_0043dc80 @ 0043dc80 ==== */

undefined4 __cdecl FUN_0043dc80(int *param_1,int param_2)

{
  bool bVar1;
  undefined4 uVar2;
  undefined3 extraout_var;
  
  if (param_2 < *param_1) {
    bVar1 = FUN_0043db63((int)param_1);
    if (CONCAT31(extraout_var,bVar1) == 0) {
      uVar2 = *(undefined4 *)(param_1[2] + param_2 * 4);
    }
    else {
      FUN_00413085((uint *)s_Internal_error__Array_has_no_dat_0045a42c);
      uVar2 = 0;
    }
  }
  else {
    FUN_00413085((uint *)s_Internal_error__Not_that_many_ar_0045a400);
    uVar2 = 0;
  }
  return uVar2;
}


