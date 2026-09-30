/* util: 271 functions from DSPLNK */

/* ==== FUN_0042c8ba @ 0042c8ba ==== */

undefined4 * __cdecl FUN_0042c8ba(uint *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *local_21c;
  uint local_218 [129];
  undefined4 *local_14;
  int *local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)0x0;
  local_c = (undefined4 *)0x0;
  local_14 = (undefined4 *)0x0;
  if (DAT_00461214 != '\0') {
    strcpy((char *)local_218,(char *)param_1);
    thunk_FUN_00430037((char *)local_218);
    param_1 = local_218;
  }
  uVar1 = thunk_FUN_0042e3f9((char *)param_1);
  DAT_00461e88 = *(undefined4 **)(&DAT_00461ff8 + uVar1 * 4);
  for (local_21c = DAT_00461e88; local_21c != (undefined4 *)0x0;
      local_21c = (undefined4 *)local_21c[0x18]) {
    DAT_00461e88 = local_21c;
    if (((char)*param_1 == *(char *)*local_21c) &&
       (iVar2 = strcmp((char *)param_1,(char *)*local_21c), iVar2 == 0)) {
      if ((DAT_00461ddc != (undefined4 *)0x0) &&
         ((local_21c[0x12] != 0 && (**(int **)local_21c[0x12] == *(int *)*DAT_00461ddc)))) break;
      if ((((DAT_00457b74 != '\0') && (DAT_00461f00 != (int *)0x0)) &&
          (local_c == (undefined4 *)0x0)) && ((DAT_00461dbc != 0 && (param_2 == 0)))) {
        for (local_10 = DAT_00461f00; local_10 != (int *)0x0; local_10 = (int *)local_10[1]) {
          if ((local_21c[0x12] != 0) &&
             (**(int **)local_21c[0x12] == **(int **)**(undefined4 **)(DAT_00461de8 + *local_10 * 4)
             )) {
            local_c = local_21c;
            break;
          }
        }
      }
      if (((local_14 == (undefined4 *)0x0) && ((local_21c[10] & 0x80) != 0)) &&
         ((param_2 != 0 || (iVar2 = FUN_0042d950(param_1), iVar2 != 0)))) {
        local_14 = local_21c;
      }
      if ((local_8 == (undefined4 *)0x0) && ((local_21c[10] & 0x40) != 0)) {
        local_8 = local_21c;
      }
    }
  }
  if (local_21c == (undefined4 *)0x0) {
    if (local_c == (undefined4 *)0x0) {
      if (local_14 == (undefined4 *)0x0) {
        if (local_8 != (undefined4 *)0x0) {
          local_21c = local_8;
        }
      }
      else {
        local_21c = local_14;
      }
    }
    else {
      local_21c = local_c;
    }
  }
  DAT_004611dc = local_21c;
  return local_21c;
}


/* ==== FUN_0042cae9 @ 0042cae9 ==== */

int * __cdecl FUN_0042cae9(uint *param_1,int param_2,int param_3)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int local_c;
  
  if ((param_3 == 0) && (param_2 == 0)) {
    param_3 = FUN_0042d950(param_1);
  }
  piVar1 = thunk_FUN_0042cd0d(param_1);
  if (((((piVar1 == (int *)0x0) || (param_2 != 0)) || (piVar1[3] == 0)) ||
      ((DAT_00461dbc == 0 || (piVar1[3] != *(int *)(DAT_00461dbc + 8))))) ||
     ((piVar1[4] == 0 ||
      ((DAT_00461ddc == (undefined4 *)0x0 || (**(int **)piVar1[4] != *(int *)*DAT_00461ddc)))))) {
    piVar1 = (int *)thunk_FUN_0042e170(0x1c);
    uVar2 = strlen((char *)param_1);
    iVar3 = thunk_FUN_0042e170(uVar2 + 1);
    *piVar1 = iVar3;
    strcpy((char *)*piVar1,(char *)param_1);
    if (DAT_00461214 != '\0') {
      thunk_FUN_00430037((char *)*piVar1);
    }
    piVar1[1] = (-(uint)(param_3 != 0) & 0x40) + 0x40;
    if (param_2 == 0) {
      piVar1[2] = DAT_00461dbc;
      if (DAT_00461dbc == 0) {
        local_c = 0;
      }
      else {
        local_c = *(int *)(DAT_00461dbc + 8);
      }
      piVar1[3] = local_c;
      piVar1[4] = (int)DAT_00461ddc;
    }
    else {
      piVar1[2] = 0;
      piVar1[3] = 0;
      piVar1[4] = 0;
    }
    piVar1[6] = 0;
    if (DAT_00461e8c == 0) {
      uVar2 = thunk_FUN_0042e3f9((char *)*piVar1);
      *(int **)(&DAT_00465e98 + uVar2 * 4) = piVar1;
      piVar1[5] = 0;
    }
    else {
      piVar1[6] = *(int *)(DAT_00461e8c + 0x18);
      *(int **)(DAT_00461e8c + 0x18) = piVar1;
      piVar1[5] = DAT_00461e8c;
      if (piVar1[6] != 0) {
        *(int **)(piVar1[6] + 0x14) = piVar1;
      }
    }
    DAT_004612e0 = DAT_004612e0 + 1;
    DAT_004611fc = 1;
  }
  else if ((param_3 != 0) && ((piVar1[1] & 0x40U) != 0)) {
    piVar1[1] = piVar1[1] & 0xffffffbf;
    piVar1[1] = piVar1[1] | 0x80;
  }
  return piVar1;
}


/* ==== FUN_0042cd0d @ 0042cd0d ==== */

undefined4 * __cdecl FUN_0042cd0d(uint *param_1)

{
  uint uVar1;
  int iVar2;
  int local_21c;
  undefined4 *local_218;
  uint local_214 [129];
  undefined4 *local_10;
  undefined4 *local_c;
  int local_8;
  
  local_c = (undefined4 *)0x0;
  if (DAT_00461214 != '\0') {
    strcpy((char *)local_214,(char *)param_1);
    thunk_FUN_00430037((char *)local_214);
    param_1 = local_214;
  }
  local_c = (undefined4 *)0x0;
  local_10 = (undefined4 *)0x0;
  uVar1 = thunk_FUN_0042e3f9((char *)param_1);
  DAT_00461e8c = *(undefined4 **)(&DAT_00465e98 + uVar1 * 4);
  for (local_218 = DAT_00461e8c; local_218 != (undefined4 *)0x0;
      local_218 = (undefined4 *)local_218[6]) {
    DAT_00461e8c = local_218;
    if (((char)*param_1 == *(char *)*local_218) &&
       (iVar2 = strcmp((char *)param_1,(char *)*local_218), iVar2 == 0)) {
      if ((local_218[4] == 0) ||
         ((DAT_00461ddc == (undefined4 *)0x0 || (**(int **)local_218[4] != *(int *)*DAT_00461ddc))))
      {
        local_21c = 0;
      }
      else {
        local_21c = 1;
      }
      local_8 = local_21c;
      if ((((local_21c != 0) && (local_218[2] != 0)) && (DAT_00461dbc != 0)) &&
         (DAT_00461dbc == local_218[2])) break;
      if (local_21c == 0) {
        local_c = local_218;
      }
      else {
        local_10 = local_218;
      }
    }
  }
  if (local_218 == (undefined4 *)0x0) {
    if (local_10 == (undefined4 *)0x0) {
      if (local_c != (undefined4 *)0x0) {
        local_218 = local_c;
      }
    }
    else {
      local_218 = local_10;
    }
  }
  return local_218;
}


/* ==== FUN_0042ceac @ 0042ceac ==== */

void FUN_0042ceac(void)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  undefined4 *local_18;
  int local_14;
  undefined4 *local_c;
  undefined4 *local_8;
  
  local_14 = 0;
  do {
    if (0x7d2 < local_14) {
      return;
    }
    local_c = *(undefined4 **)(&DAT_00465e98 + local_14 * 4);
    while (local_c != (undefined4 *)0x0) {
      local_8 = (undefined4 *)0x0;
      bVar1 = false;
      uVar2 = thunk_FUN_0042e3f9((char *)*local_c);
      for (local_18 = *(undefined4 **)(&DAT_00461ff8 + uVar2 * 4); local_18 != (undefined4 *)0x0;
          local_18 = (undefined4 *)local_18[0x18]) {
        if ((*(char *)*local_18 == *(char *)*local_c) &&
           (iVar3 = strcmp((char *)*local_18,(char *)*local_c), iVar3 == 0)) {
          if ((local_18[10] & 0x40) != 0) {
            bVar1 = true;
          }
          if (((local_18[10] & 0xc0 & local_c[1]) != 0) ||
             ((local_18[0x12] != 0 && (**(int **)local_18[0x12] == **(int **)local_c[4])))) {
            local_8 = (undefined4 *)local_c[6];
            bVar1 = false;
            FUN_0042d029(local_c);
            local_c = (undefined4 *)0x0;
            break;
          }
        }
      }
      if (((local_8 == (undefined4 *)0x0) && (local_c != (undefined4 *)0x0)) && (bVar1)) {
        local_8 = (undefined4 *)local_c[6];
        FUN_0042d029(local_c);
        local_c = (undefined4 *)0x0;
      }
      if (local_8 == (undefined4 *)0x0) {
        if (local_c == (undefined4 *)0x0) {
          local_c = (undefined4 *)0x0;
        }
        else {
          local_c = (undefined4 *)local_c[6];
        }
      }
      else {
        local_c = local_8;
      }
    }
    local_14 = local_14 + 1;
  } while( true );
}


/* ==== FUN_0042d029 @ 0042d029 ==== */

void __cdecl FUN_0042d029(undefined4 *param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_0042e3f9((char *)*param_1);
  if ((DAT_00461248 == '\0') || ((param_1[1] & 0x80) == 0)) {
    if (param_1[5] == 0) {
      *(undefined4 *)(&DAT_00465e98 + uVar1 * 4) = param_1[6];
    }
    else {
      *(undefined4 *)(param_1[5] + 0x18) = param_1[6];
    }
    if (param_1[6] != 0) {
      *(undefined4 *)(param_1[6] + 0x14) = param_1[5];
    }
    if ((param_1[5] == 0) && (param_1[6] == 0)) {
      *(undefined4 *)(&DAT_00465e98 + uVar1 * 4) = 0;
    }
    thunk_FUN_0042e1ce((undefined *)*param_1);
    thunk_FUN_0042e1ce((undefined *)param_1);
    DAT_004612e0 = DAT_004612e0 + -1;
  }
  else {
    param_1[1] = param_1[1] | 0x100;
    DAT_004612e4 = DAT_004612e4 + 1;
  }
  return;
}


/* ==== FUN_0042d10b @ 0042d10b ==== */

void FUN_0042d10b(void)

{
  if (DAT_00461f20 != (undefined *)0x0) {
    thunk_FUN_0042e1ce(DAT_00461f20);
    DAT_00461f20 = (undefined *)0x0;
  }
  if (DAT_00461f1c != (undefined *)0x0) {
    thunk_FUN_0042e1ce(DAT_00461f1c);
    DAT_00461f1c = (undefined *)0x0;
  }
  if (DAT_00461f24 != (undefined *)0x0) {
    thunk_FUN_0042e1ce(DAT_00461f24);
    DAT_00461f24 = (undefined *)0x0;
  }
  return;
}


/* ==== FUN_0042d175 @ 0042d175 ==== */

void FUN_0042d175(void)

{
  undefined *puVar1;
  int *piVar2;
  undefined *local_1c;
  int *local_14;
  undefined *local_c;
  
  local_14 = DAT_00461dcc;
  while (local_14 != (int *)0x0) {
    if (*local_14 != 0) {
      thunk_FUN_0042e1ce((undefined *)*local_14);
    }
    local_1c = (undefined *)local_14[2];
    while (local_1c != (undefined *)0x0) {
      local_c = *(undefined **)(local_1c + 0x30);
      while (local_c != (undefined *)0x0) {
        puVar1 = *(undefined **)(local_c + 4);
        thunk_FUN_0042e1ce(local_c);
        local_c = puVar1;
      }
      puVar1 = *(undefined **)(local_1c + 0x38);
      thunk_FUN_0042e1ce(local_1c);
      local_1c = puVar1;
    }
    piVar2 = (int *)local_14[3];
    thunk_FUN_0042e1ce((undefined *)local_14);
    local_14 = piVar2;
  }
  DAT_00461e80 = 0;
  return;
}


/* ==== FUN_0042d229 @ 0042d229 ==== */

void FUN_0042d229(void)

{
  undefined *puVar1;
  undefined4 *puVar2;
  undefined *local_1c;
  int local_18;
  undefined *local_14;
  undefined4 *local_10;
  undefined *local_c;
  
  for (local_18 = 0; local_18 < 0x7d3; local_18 = local_18 + 1) {
    local_10 = *(undefined4 **)(&DAT_00463f48 + local_18 * 4);
    if (local_10 != (undefined4 *)0x0) {
      *(undefined4 *)(&DAT_00463f48 + local_18 * 4) = 0;
      while (local_10 != (undefined4 *)0x0) {
        thunk_FUN_0042e1ce((undefined *)*local_10);
        local_1c = (undefined *)local_10[2];
        while (local_1c != (undefined *)0x0) {
          local_c = *(undefined **)(local_1c + 0x18);
          while (local_c != (undefined *)0x0) {
            thunk_FUN_0042b1d5((int)local_c);
            puVar1 = *(undefined **)(local_c + 0x44);
            thunk_FUN_0042e1ce(local_c);
            local_c = puVar1;
          }
          local_c = *(undefined **)(local_1c + 0x1c);
          while (local_c != (undefined *)0x0) {
            puVar1 = *(undefined **)(local_c + 0x44);
            thunk_FUN_0042e1ce(local_c);
            local_c = puVar1;
          }
          local_c = *(undefined **)(local_1c + 0x20);
          while (local_c != (undefined *)0x0) {
            puVar1 = *(undefined **)(local_c + 0x44);
            thunk_FUN_0042e1ce(local_c);
            local_c = puVar1;
          }
          local_c = *(undefined **)(local_1c + 0x24);
          while (local_c != (undefined *)0x0) {
            thunk_FUN_0042b1d5((int)local_c);
            puVar1 = *(undefined **)(local_c + 0x44);
            thunk_FUN_0042e1ce(local_c);
            local_c = puVar1;
          }
          puVar1 = *(undefined **)(local_1c + 0x74);
          thunk_FUN_0042e1ce(local_1c);
          local_1c = puVar1;
        }
        local_14 = (undefined *)local_10[3];
        while (local_14 != (undefined *)0x0) {
          puVar1 = *(undefined **)(local_14 + 4);
          thunk_FUN_0042e1ce(local_14);
          local_14 = puVar1;
        }
        puVar2 = (undefined4 *)local_10[4];
        thunk_FUN_0042e1ce((undefined *)local_10);
        local_10 = puVar2;
      }
    }
  }
  DAT_00461e84 = 0;
  DAT_0046129c = 0;
  return;
}


/* ==== FUN_0042d3ef @ 0042d3ef ==== */

void FUN_0042d3ef(void)

{
  int *piVar1;
  int *local_10;
  int local_c;
  
  for (local_c = 0; local_c < 0x7d3; local_c = local_c + 1) {
    local_10 = *(int **)(&DAT_00461ff8 + local_c * 4);
    if (local_10 != (int *)0x0) {
      *(undefined4 *)(&DAT_00461ff8 + local_c * 4) = 0;
      while (local_10 != (int *)0x0) {
        if (*local_10 != 0) {
          thunk_FUN_0042e1ce((undefined *)*local_10);
        }
        piVar1 = (int *)local_10[0x18];
        thunk_FUN_0042e1ce((undefined *)local_10);
        local_10 = piVar1;
      }
    }
  }
  DAT_00461e88 = 0;
  DAT_004612dc = 0;
  return;
}


/* ==== FUN_0042d484 @ 0042d484 ==== */

void FUN_0042d484(void)

{
  int *piVar1;
  int *local_10;
  int local_c;
  
  for (local_c = 0; local_c < 0x7d3; local_c = local_c + 1) {
    local_10 = *(int **)(&DAT_00465e98 + local_c * 4);
    if (local_10 != (int *)0x0) {
      *(undefined4 *)(&DAT_00465e98 + local_c * 4) = 0;
      while (local_10 != (int *)0x0) {
        if (*local_10 != 0) {
          thunk_FUN_0042e1ce((undefined *)*local_10);
        }
        piVar1 = (int *)local_10[6];
        thunk_FUN_0042e1ce((undefined *)local_10);
        local_10 = piVar1;
      }
    }
  }
  DAT_00461e8c = 0;
  DAT_004612e0 = 0;
  return;
}


/* ==== FUN_0042d519 @ 0042d519 ==== */

void FUN_0042d519(void)

{
  undefined4 *puVar1;
  int local_14;
  undefined4 *local_10;
  int local_c;
  
  for (local_14 = 0; local_14 < 0x7d3; local_14 = local_14 + 1) {
    for (local_c = *(int *)(&DAT_00463f48 + local_14 * 4); local_c != 0;
        local_c = *(int *)(local_c + 0x10)) {
      local_10 = *(undefined4 **)(local_c + 0xc);
      while (local_10 != (undefined4 *)0x0) {
        thunk_FUN_0042e1ce((undefined *)*local_10);
        puVar1 = (undefined4 *)local_10[1];
        thunk_FUN_0042e1ce((undefined *)local_10);
        local_10 = puVar1;
      }
      *(undefined4 *)(local_c + 0xc) = 0;
    }
  }
  return;
}


/* ==== FUN_0042d5a4 @ 0042d5a4 ==== */

void FUN_0042d5a4(void)

{
  undefined *puVar1;
  int local_1c;
  int local_18;
  int local_10;
  int local_c;
  undefined *local_8;
  
  for (local_18 = DAT_00461db8; local_18 != 0; local_18 = *(int *)(local_18 + 0x10)) {
    if (*(int *)(local_18 + 0xc) == 0) {
      local_1c = *(int *)(local_18 + 8);
    }
    else {
      local_1c = *(int *)(local_18 + 0xc);
    }
    for (local_10 = local_1c; local_10 != 0; local_10 = *(int *)(local_10 + 0x94)) {
      if (*(int *)(local_10 + 0x10) != 0) {
        for (local_c = 0; local_c < *(int *)(local_10 + 0x48); local_c = local_c + 1) {
          local_8 = *(undefined **)(*(int *)(local_10 + 0x10) + local_c * 4);
          while (local_8 != (undefined *)0x0) {
            puVar1 = *(undefined **)(local_8 + 0x14);
            thunk_FUN_0042e1ce(local_8);
            local_8 = puVar1;
          }
        }
        thunk_FUN_0042e1ce(*(undefined **)(local_10 + 0x10));
        *(undefined4 *)(local_10 + 0x10) = 0;
      }
      if (*(int *)(local_10 + 0x18) != 0) {
        thunk_FUN_0042e1ce(*(undefined **)(local_10 + 0x18));
        *(undefined4 *)(local_10 + 0x18) = 0;
      }
      if (*(int *)(local_10 + 0x14) != 0) {
        thunk_FUN_0042e1ce(*(undefined **)(local_10 + 0x14));
        *(undefined4 *)(local_10 + 0x14) = 0;
      }
      if (*(int *)(local_10 + 0x1c) != 0) {
        thunk_FUN_0042e1ce(*(undefined **)(local_10 + 0x1c));
        *(undefined4 *)(local_10 + 0x1c) = 0;
      }
      if (*(int *)(local_10 + 0x8c) != 0) {
        thunk_FUN_0042e1ce(*(undefined **)(local_10 + 0x8c));
        *(undefined4 *)(local_10 + 0x8c) = 0;
      }
      if (*(int *)(local_10 + 0x90) != 0) {
        thunk_FUN_0042e1ce(*(undefined **)(local_10 + 0x90));
        *(undefined4 *)(local_10 + 0x90) = 0;
      }
    }
  }
  return;
}


/* ==== FUN_0042d73f @ 0042d73f ==== */

void FUN_0042d73f(void)

{
  int *piVar1;
  int *local_18;
  int *local_14;
  int *local_10;
  
  local_14 = DAT_00461db8;
  while (local_14 != (int *)0x0) {
    if (*local_14 != 0) {
      thunk_FUN_0042e1ce((undefined *)*local_14);
    }
    if (local_14[3] == 0) {
      local_18 = (int *)local_14[2];
    }
    else {
      local_18 = (int *)local_14[3];
    }
    local_10 = local_18;
    while (local_10 != (int *)0x0) {
      if (*local_10 != 0) {
        thunk_FUN_0042e1ce((undefined *)*local_10);
      }
      piVar1 = (int *)local_10[0x25];
      thunk_FUN_0042e1ce((undefined *)local_10);
      local_10 = piVar1;
    }
    piVar1 = (int *)local_14[4];
    thunk_FUN_0042e1ce((undefined *)local_14);
    local_14 = piVar1;
  }
  DAT_00461dbc = 0;
  return;
}


/* ==== FUN_0042d7fa @ 0042d7fa ==== */

void __cdecl FUN_0042d7fa(undefined *param_1)

{
  undefined *puVar1;
  
  while (param_1 != (undefined *)0x0) {
    puVar1 = *(undefined **)(param_1 + 0x10);
    thunk_FUN_0042e1ce(param_1);
    param_1 = puVar1;
  }
  return;
}


/* ==== FUN_0042d825 @ 0042d825 ==== */

void FUN_0042d825(void)

{
  undefined *puVar1;
  undefined *local_10;
  int local_c;
  
  local_10 = DAT_00461e24;
  while (local_10 != (undefined *)0x0) {
    for (local_c = 0; local_c < 8; local_c = local_c + 1) {
      if (*(int *)(local_10 + local_c * 4 + 4) != 0) {
        thunk_FUN_0042d7fa(*(undefined **)(local_10 + local_c * 4 + 4));
      }
    }
    puVar1 = *(undefined **)(local_10 + 0x24);
    thunk_FUN_0042e1ce(local_10);
    local_10 = puVar1;
  }
  for (local_c = 0; local_c < 8; local_c = local_c + 1) {
    *(undefined4 *)(&DAT_00461df8 + local_c * 4) = 0;
  }
  DAT_00461e24 = (undefined *)0x0;
  DAT_00461e28 = 0;
  return;
}


/* ==== FUN_0042d8d0 @ 0042d8d0 ==== */

void __cdecl FUN_0042d8d0(undefined4 param_1)

{
  thunk_FUN_0042e1df(param_1,0x458010,DAT_00458098,8,FUN_0042d939);
  return;
}


/* ==== FUN_0042d8f3 @ 0042d8f3 ==== */

void __cdecl FUN_0042d8f3(undefined4 param_1)

{
  thunk_FUN_0042e1df(param_1,0x4580a0,DAT_00458100,8,FUN_0042d939);
  return;
}


/* ==== FUN_0042d916 @ 0042d916 ==== */

void __cdecl FUN_0042d916(undefined4 param_1)

{
  thunk_FUN_0042e1df(param_1,0x458108,DAT_00458210,8,FUN_0042d939);
  return;
}


/* ==== FUN_0042d939 @ 0042d939 ==== */

void __cdecl FUN_0042d939(char *param_1,undefined4 *param_2)

{
  strcmp(param_1,(char *)*param_2);
  return;
}


/* ==== FUN_0042d950 @ 0042d950 ==== */

undefined4 __cdecl FUN_0042d950(uint *param_1)

{
  int iVar1;
  uint local_20c [129];
  undefined4 *local_8;
  
  if (*(int *)(*(int *)*DAT_00461ddc + 4) != 0) {
    if (DAT_00461214 != '\0') {
      strcpy((char *)local_20c,(char *)param_1);
      thunk_FUN_00430037((char *)local_20c);
      param_1 = local_20c;
    }
    for (local_8 = *(undefined4 **)(*(int *)*DAT_00461ddc + 0xc); local_8 != (undefined4 *)0x0;
        local_8 = (undefined4 *)local_8[1]) {
      if ((*(char *)*local_8 == (char)*param_1) &&
         (iVar1 = strcmp((char *)*local_8,(char *)param_1), iVar1 == 0)) {
        return 1;
      }
    }
  }
  return 0;
}


/* ==== FUN_0042e170 @ 0042e170 ==== */

int __cdecl FUN_0042e170(uint param_1)

{
  int extraout_EAX;
  
  malloc(param_1);
  if (extraout_EAX == 0) {
    thunk_FUN_004098b0(s_Out_of_memory___link_aborted_0045aa74);
  }
  return extraout_EAX;
}


/* ==== FUN_0042e19d @ 0042e19d ==== */

int * __cdecl FUN_0042e19d(int *param_1,uint param_2)

{
  int *extraout_EAX;
  
  realloc(param_1,param_2);
  if (extraout_EAX == (int *)0x0) {
    thunk_FUN_004098b0(s_Out_of_memory___link_aborted_0045aa94);
  }
  return extraout_EAX;
}


/* ==== FUN_0042e1ce @ 0042e1ce ==== */

void __cdecl FUN_0042e1ce(undefined *param_1)

{
  free(param_1);
  return;
}


/* ==== FUN_0042e1df @ 0042e1df ==== */

int __cdecl FUN_0042e1df(undefined4 param_1,uint param_2,int param_3,int param_4,undefined *param_5)

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


/* ==== FUN_0042e25d @ 0042e25d ==== */

void __cdecl FUN_0042e25d(int param_1,int param_2)

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
    uVar1 = *(undefined4 *)(DAT_00461f18 + iVar2 * 4);
    while( true ) {
      while ((local_c < local_14 &&
             (iVar3 = (*DAT_00461dc8)(*(undefined4 *)(DAT_00461f18 + local_c * 4),uVar1), iVar3 < 1)
             )) {
        local_c = local_c + 1;
      }
      while ((local_c < local_14 &&
             (iVar3 = (*DAT_00461dc8)(*(undefined4 *)(DAT_00461f18 + local_14 * 4),uVar1),
             -1 < iVar3))) {
        local_14 = local_14 + -1;
      }
      if (local_14 <= local_c) break;
      FUN_0042e3b9(local_c,local_14);
    }
    if ((iVar2 < local_c) &&
       (iVar3 = (*DAT_00461dc8)(*(undefined4 *)(DAT_00461f18 + local_c * 4),uVar1), 0 < iVar3)) {
      local_c = local_c + -1;
    }
    FUN_0042e3b9(local_c,iVar2);
    if (local_c - param_1 < param_2 - local_c) {
      thunk_FUN_0042e25d(param_1,local_c + -1);
      thunk_FUN_0042e25d(local_c + 1,param_2);
    }
    else {
      thunk_FUN_0042e25d(local_c + 1,param_2);
      thunk_FUN_0042e25d(param_1,local_c + -1);
    }
  }
  return;
}


/* ==== FUN_0042e3b9 @ 0042e3b9 ==== */

void __cdecl FUN_0042e3b9(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(DAT_00461f18 + param_1 * 4);
  *(undefined4 *)(DAT_00461f18 + param_1 * 4) = *(undefined4 *)(DAT_00461f18 + param_2 * 4);
  *(undefined4 *)(DAT_00461f18 + param_2 * 4) = uVar1;
  return;
}


/* ==== FUN_0042e3f9 @ 0042e3f9 ==== */

uint __cdecl FUN_0042e3f9(char *param_1)

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
  return local_c % 0x7d3;
}


/* ==== FUN_0042e468 @ 0042e468 ==== */

char * __cdecl FUN_0042e468(char *param_1)

{
  uint uVar1;
  char *local_8;
  
  if (param_1 == (char *)0x0) {
    param_1 = (char *)0x0;
  }
  else {
    uVar1 = strlen(param_1);
    for (local_8 = param_1 + uVar1;
        ((param_1 <= local_8 && (*local_8 != '\\')) && (*local_8 != ':')); local_8 = local_8 + -1) {
    }
    if (param_1 <= local_8) {
      param_1 = local_8 + 1;
    }
  }
  return param_1;
}


/* ==== FUN_0042e4df @ 0042e4df ==== */

char * __cdecl FUN_0042e4df(char *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  
  if ((*param_1 == '\'') || (*param_1 == '\"')) {
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    while (*param_1 != '\0') {
      if (*param_1 == cVar1) {
        if (param_1[1] == cVar1) {
          *param_2 = *param_1;
          param_2 = param_2 + 1;
          param_1 = param_1 + 2;
        }
        else {
          if ((param_1[1] != '+') || (param_1[2] != '+')) break;
          pcVar2 = param_1 + 3;
          if ((*pcVar2 != '\'') && (*pcVar2 != '\"')) {
            thunk_FUN_00409a25(s_Missing_string_after_concatenati_0045aad4);
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
      thunk_FUN_00409a25(s_Missing_quote_in_string_0045ab00);
      pcVar2 = (char *)0x0;
    }
  }
  else {
    thunk_FUN_00409a25(s_Syntax_error___expected_quote_0045aab4);
    pcVar2 = (char *)0x0;
  }
  return pcVar2;
}


/* ==== FUN_0042e622 @ 0042e622 ==== */

undefined1 * FUN_0042e622(void)

{
  uint local_14;
  uint local_10;
  int local_c;
  char *local_8;
  
  local_c = 0;
  local_8 = &DAT_00469b90;
  if (__mb_cur_max < 2) {
    local_10 = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 0x103;
  }
  else {
    local_10 = _isctype((int)*DAT_00461d68,0x103);
  }
  if (local_10 == 0) {
    thunk_FUN_00409a25(s_Invalid_symbol_0045ab18);
  }
  else {
    while( true ) {
      if (__mb_cur_max < 2) {
        local_14 = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 0x107;
      }
      else {
        local_14 = _isctype((int)*DAT_00461d68,0x107);
      }
      if ((local_14 == 0) && (*DAT_00461d68 != '_')) {
        *local_8 = '\0';
        return &DAT_00469b90;
      }
      local_c = local_c + 1;
      if (0x200 < local_c) break;
      *local_8 = *DAT_00461d68;
      local_8 = local_8 + 1;
      DAT_00461d68 = DAT_00461d68 + 1;
    }
    thunk_FUN_00409a25(s_Symbol_name_too_long_0045ab28);
  }
  return (undefined1 *)0x0;
}


/* ==== FUN_0042e743 @ 0042e743 ==== */

undefined4 __cdecl FUN_0042e743(int *param_1)

{
  char cVar1;
  undefined3 extraout_var;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  undefined4 uVar5;
  uint local_38;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  int local_1c;
  uint local_18;
  int local_14;
  uint local_10;
  
  param_1[1] = 4;
  *param_1 = 4;
  param_1[2] = 0;
  param_1[3] = 0;
  cVar1 = strchr(DAT_00461d68,0x3a);
  if (CONCAT31(extraout_var,cVar1) == 0) {
    return 0;
  }
  iVar2 = thunk_FUN_0042f35d((int)*DAT_00461d68);
  *param_1 = iVar2;
  if (*param_1 == 0xa2c2a) {
    return 0;
  }
  if (*param_1 == 0x1c) {
    if (__mb_cur_max < 2) {
      local_10 = *(ushort *)(_pctype + DAT_00461d68[1] * 2) & 1;
    }
    else {
      local_10 = _isctype((int)DAT_00461d68[1],1);
    }
    if (local_10 == 0) {
      local_14 = (int)DAT_00461d68[1];
    }
    else {
      local_14 = tolower((int)DAT_00461d68[1]);
    }
    if (local_14 == 0x6d) {
      DAT_00461d68 = DAT_00461d68 + 1;
    }
  }
  if (*param_1 == 0x11d) {
    if (__mb_cur_max < 2) {
      local_18 = *(ushort *)(_pctype + DAT_00461d68[1] * 2) & 1;
    }
    else {
      local_18 = _isctype((int)DAT_00461d68[1],1);
    }
    if (local_18 == 0) {
      local_1c = (int)DAT_00461d68[1];
    }
    else {
      local_1c = tolower((int)DAT_00461d68[1]);
    }
    if (local_1c == 0x6d) {
      DAT_00461d68 = DAT_00461d68 + 1;
    }
  }
  pcVar3 = DAT_00461d68 + 1;
  if (*pcVar3 == ':') {
    if (*param_1 == 0x11f) {
      DAT_00461d68 = pcVar3;
      param_1[1] = 0x120;
    }
    else {
      DAT_00461d68 = pcVar3;
      param_1[1] = *param_1;
    }
    DAT_00461d68 = DAT_00461d68 + 1;
    return 1;
  }
  if (*pcVar3 == '8') {
    DAT_00461d68 = pcVar3;
    iVar2 = FUN_0042fc06(*param_1,8);
    if (iVar2 == 0xa2c2a) {
      thunk_FUN_00409a25(s_Illegal_memory_space_character_0045ab40);
      return 0xffffffff;
    }
    param_1[1] = iVar2;
    pcVar3 = DAT_00461d68 + 1;
    if (DAT_00461d68[1] == ':') {
      DAT_00461d68 = DAT_00461d68 + 2;
      return 1;
    }
  }
  else if ((*pcVar3 == '1') && (DAT_00461d68[2] == '6')) {
    DAT_00461d68 = pcVar3;
    iVar2 = FUN_0042fc06(*param_1,0x10);
    if (iVar2 == 0xa2c2a) {
      thunk_FUN_00409a25(s_Illegal_memory_space_character_0045ab60);
      return 0xffffffff;
    }
    param_1[1] = iVar2;
    pcVar3 = DAT_00461d68 + 2;
    if (DAT_00461d68[2] == ':') {
      DAT_00461d68 = DAT_00461d68 + 3;
      return 1;
    }
  }
  DAT_00461d68 = pcVar3;
  iVar2 = thunk_FUN_0042f450((int)*DAT_00461d68);
  param_1[2] = iVar2;
  if (param_1[2] != -1) {
    pcVar3 = DAT_00461d68 + 1;
    if (*pcVar3 == ':') {
      DAT_00461d68 = DAT_00461d68 + 2;
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
    DAT_00461d68 = pcVar3;
    if ((*param_1 != 0x11f) && (param_1[1] != 0x11e)) {
      if (*param_1 == 0x1c) {
        if (__mb_cur_max < 2) {
          local_20 = *(ushort *)(_pctype + *pcVar3 * 2) & 4;
        }
        else {
          local_20 = _isctype((int)*pcVar3,4);
        }
        if (local_20 != 0) {
          uVar4 = strtol(DAT_00461d68,(char **)0x0,10);
          iVar2 = FUN_0042facc(uVar4,(uint *)(param_1 + 3));
          param_1[1] = iVar2;
          if (param_1[1] == 0xa2c2a) {
            return 0;
          }
          while( true ) {
            if (__mb_cur_max < 2) {
              local_24 = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 4;
            }
            else {
              local_24 = _isctype((int)*DAT_00461d68,4);
            }
            if (local_24 == 0) break;
            DAT_00461d68 = DAT_00461d68 + 1;
          }
          goto LAB_0042ec88;
        }
      }
      cVar1 = *DAT_00461d68;
      if (param_1[1] != 4) {
        thunk_FUN_00409a25(s_Illegal_memory_map_character_0045ab80);
        return 0xffffffff;
      }
      iVar2 = thunk_FUN_0042f503((int)*DAT_00461d68,0,*param_1);
      param_1[1] = iVar2;
      if (param_1[1] == 0xa2c2a) {
        thunk_FUN_00409a25(s_Illegal_memory_counter_specified_0045aba0);
        return 0xffffffff;
      }
      DAT_00461d68 = DAT_00461d68 + 1;
      if (*DAT_00461d68 != ':') {
        if (*param_1 == 3) {
          iVar2 = thunk_FUN_0042f503((int)cVar1,(int)*DAT_00461d68,*param_1);
          param_1[1] = iVar2;
          if (param_1[1] != 0xa2c2a) {
            DAT_00461d68 = DAT_00461d68 + 1;
            goto LAB_0042ec88;
          }
        }
        thunk_FUN_00409a25(s_Illegal_memory_map_character_0045abc4);
        return 0xffffffff;
      }
LAB_0042ec88:
      if (*DAT_00461d68 != ':') {
        thunk_FUN_00409a25(s_Syntax_error___expected_____0045abe4);
        return 0xffffffff;
      }
      DAT_00461d68 = DAT_00461d68 + 1;
      return 1;
    }
  }
  param_1[2] = 0;
  if (*DAT_00461d68 == '(') {
    DAT_00461d68 = DAT_00461d68 + 1;
    if (DAT_00461f6c == 0) {
      param_1[2] = 0;
      while( true ) {
        if (__mb_cur_max < 2) {
          local_28 = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 4;
        }
        else {
          local_28 = _isctype((int)*DAT_00461d68,4);
        }
        if (local_28 == 0) break;
        param_1[2] = param_1[2] * 10 + -0x30 + (int)*DAT_00461d68;
        DAT_00461d68 = DAT_00461d68 + 1;
      }
    }
    else {
      iVar2 = thunk_FUN_0040a4fd();
      param_1[2] = iVar2;
      if (param_1[2] == -1) {
        param_1[2] = 0;
        return 0xffffffff;
      }
    }
    if (param_1[1] == 4) {
      if (*param_1 == 0x11f) {
        param_1[1] = 0x120;
      }
      else {
        param_1[1] = *param_1;
      }
    }
    if ((*DAT_00461d68 == ')') && (DAT_00461d68[1] == ':')) {
      DAT_00461d68 = DAT_00461d68 + 2;
      return 1;
    }
    thunk_FUN_00409a25(s_Syntax_error___expected______0045ac00);
    return 0xffffffff;
  }
  if (*param_1 == 0x1c) {
    if (__mb_cur_max < 2) {
      local_2c = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 4;
    }
    else {
      local_2c = _isctype((int)*DAT_00461d68,4);
    }
    if (local_2c != 0) {
      uVar4 = strtol(DAT_00461d68,(char **)0x0,10);
      iVar2 = FUN_0042facc(uVar4,(uint *)(param_1 + 3));
      param_1[1] = iVar2;
      if (param_1[1] == 0xa2c2a) {
        return 0;
      }
      while( true ) {
        if (__mb_cur_max < 2) {
          local_30 = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 4;
        }
        else {
          local_30 = _isctype((int)*DAT_00461d68,4);
        }
        pcVar3 = DAT_00461d68;
        if (local_30 == 0) break;
        DAT_00461d68 = DAT_00461d68 + 1;
      }
      goto LAB_0042f004;
    }
  }
  pcVar3 = DAT_00461d68;
  if ((*param_1 != 0x11f) && (param_1[1] != 0x11e)) {
    cVar1 = *DAT_00461d68;
    if (param_1[1] != 4) {
      thunk_FUN_00409a25(s_Illegal_memory_map_character_0045ac20);
      return 0xffffffff;
    }
    iVar2 = thunk_FUN_0042f503((int)*DAT_00461d68,0,*param_1);
    param_1[1] = iVar2;
    if (param_1[1] == 0xa2c2a) {
      thunk_FUN_00409a25(s_Illegal_memory_counter_specified_0045ac40);
      return 0xffffffff;
    }
    pcVar3 = DAT_00461d68 + 1;
    if ((*pcVar3 != ':') && (*pcVar3 != '(')) {
      if (*param_1 == 3) {
        DAT_00461d68 = DAT_00461d68 + 2;
        iVar2 = thunk_FUN_0042f503((int)cVar1,(int)*pcVar3,*param_1);
        param_1[1] = iVar2;
        pcVar3 = DAT_00461d68;
        if (param_1[1] != 0xa2c2a) goto LAB_0042f004;
      }
      DAT_00461d68 = pcVar3;
      thunk_FUN_00409a25(s_Illegal_memory_map_character_0045ac64);
      return 0xffffffff;
    }
  }
LAB_0042f004:
  DAT_00461d68 = pcVar3;
  if (*DAT_00461d68 == '(') {
    DAT_00461d68 = DAT_00461d68 + 1;
    if (DAT_00461f6c == 0) {
      param_1[2] = 0;
      while( true ) {
        if (__mb_cur_max < 2) {
          local_38 = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 4;
        }
        else {
          local_38 = _isctype((int)*DAT_00461d68,4);
        }
        if (local_38 == 0) break;
        param_1[2] = param_1[2] * 10 + -0x30 + (int)*DAT_00461d68;
        DAT_00461d68 = DAT_00461d68 + 1;
      }
    }
    else {
      iVar2 = thunk_FUN_0040a4fd();
      param_1[2] = iVar2;
      if (param_1[2] == -1) {
        param_1[2] = 0;
        return 0xffffffff;
      }
    }
    if ((*DAT_00461d68 == ')') && (DAT_00461d68[1] == ':')) {
      DAT_00461d68 = DAT_00461d68 + 2;
      uVar5 = 1;
    }
    else {
      thunk_FUN_00409a25(s_Syntax_error___expected______0045ac84);
      uVar5 = 0xffffffff;
    }
  }
  else if (*DAT_00461d68 == ':') {
    DAT_00461d68 = DAT_00461d68 + 1;
    uVar5 = 1;
  }
  else {
    thunk_FUN_00409a25(s_Syntax_error___expected_____0045aca4);
    uVar5 = 0xffffffff;
  }
  return uVar5;
}


/* ==== FUN_0042f146 @ 0042f146 ==== */

undefined4 __cdecl FUN_0042f146(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 0x1d) {
    if (param_1 == 0x1c) {
      return 0x45;
    }
    switch(param_1) {
    case 0:
      uVar1 = 0x50;
      break;
    case 1:
      uVar1 = 0x58;
      break;
    case 2:
      uVar1 = 0x59;
      break;
    case 3:
      uVar1 = 0x4c;
      break;
    default:
      goto switchD_0042f165_default;
    }
  }
  else {
    if (param_1 == 0x11d) {
      return 0x44;
    }
    if (param_1 == 0x11f) {
      return 0x55;
    }
switchD_0042f165_default:
    uVar1 = 0x4e;
  }
  return uVar1;
}


/* ==== FUN_0042f1ca @ 0042f1ca ==== */

undefined4 __cdecl FUN_0042f1ca(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 1:
    uVar1 = 1;
    break;
  case 2:
    uVar1 = 2;
    break;
  default:
    uVar1 = 4;
    break;
  case 4:
    uVar1 = 3;
    break;
  case 8:
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_0042f22f @ 0042f22f ==== */

undefined4 __cdecl FUN_0042f22f(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 0x1d) {
    if (param_1 == 0x1c) {
      return 5;
    }
    switch(param_1) {
    case 0:
      uVar1 = 4;
      break;
    case 1:
      uVar1 = 1;
      break;
    case 2:
      uVar1 = 2;
      break;
    case 3:
      uVar1 = 3;
      break;
    default:
      goto switchD_0042f24e_default;
    }
  }
  else {
    if (param_1 == 0x11d) {
      return 6;
    }
    if (param_1 == 0x11f) {
      return 7;
    }
switchD_0042f24e_default:
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_0042f2b0 @ 0042f2b0 ==== */

undefined4 __cdecl FUN_0042f2b0(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 1:
    uVar1 = 1;
    break;
  case 2:
    uVar1 = 2;
    break;
  case 3:
    uVar1 = 3;
    break;
  case 4:
    uVar1 = 0;
    break;
  case 5:
    uVar1 = 0x1c;
    break;
  case 6:
    uVar1 = 0x11d;
    break;
  case 7:
    uVar1 = 0x11f;
    break;
  default:
    uVar1 = 4;
  }
  return uVar1;
}


/* ==== FUN_0042f326 @ 0042f326 ==== */

undefined4 __cdecl FUN_0042f326(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0;
  }
  else if (param_1 == 0x10) {
    uVar1 = 1;
  }
  else if (param_1 == 0x20) {
    uVar1 = 2;
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}


/* ==== FUN_0042f35d @ 0042f35d ==== */

undefined4 __cdecl FUN_0042f35d(uint param_1)

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
    uVar1 = 0x11d;
    break;
  case 0x65:
    uVar1 = 0x1c;
    break;
  default:
    uVar1 = 0xa2c2a;
    break;
  case 0x6c:
    uVar1 = 3;
    break;
  case 0x6e:
    uVar1 = 4;
    break;
  case 0x70:
    uVar1 = 0;
    break;
  case 0x75:
    uVar1 = 0x11f;
    break;
  case 0x78:
    uVar1 = 1;
    break;
  case 0x79:
    uVar1 = 2;
  }
  return uVar1;
}


/* ==== FUN_0042f450 @ 0042f450 ==== */

undefined4 __cdecl FUN_0042f450(uint param_1)

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


/* ==== FUN_0042f503 @ 0042f503 ==== */

undefined4 __cdecl FUN_0042f503(uint param_1,uint param_2,int param_3)

{
  undefined4 uVar1;
  uint local_58;
  uint local_54;
  uint local_4c;
  uint local_48;
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
      if (__mb_cur_max < 2) {
        local_54 = *(ushort *)(_pctype + param_1 * 2) & 1;
      }
      else {
        local_54 = _isctype(param_1,1);
      }
      if (local_54 == 0) {
        local_58 = param_1;
      }
      else {
        local_58 = tolower(param_1);
      }
      if (local_58 != 0x3a) {
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
      case 0x61:
        uVar1 = 0xb;
        break;
      case 0x62:
        uVar1 = 0xc;
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
      case 0x61:
        uVar1 = 0x10;
        break;
      case 0x62:
        uVar1 = 0x11;
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
      case 0x61:
        uVar1 = 0x15;
        break;
      case 0x62:
        uVar1 = 0x16;
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
      switch(local_34) {
      case 0x3a:
        uVar1 = 3;
        break;
      default:
        uVar1 = 0xa2c2a;
        break;
      case 0x61:
        if (__mb_cur_max < 2) {
          local_3c = *(ushort *)(_pctype + param_2 * 2) & 1;
        }
        else {
          local_3c = _isctype(param_2,1);
        }
        if (local_3c == 0) {
          local_40 = param_2;
        }
        else {
          local_40 = tolower(param_2);
        }
        if (local_40 == 0x61) {
          uVar1 = 5;
        }
        else if (local_40 == 0x62) {
          uVar1 = 6;
        }
        else {
          uVar1 = 0xa2c2a;
        }
        break;
      case 0x62:
        if (__mb_cur_max < 2) {
          local_48 = *(ushort *)(_pctype + param_2 * 2) & 1;
        }
        else {
          local_48 = _isctype(param_2,1);
        }
        if (local_48 == 0) {
          local_4c = param_2;
        }
        else {
          local_4c = tolower(param_2);
        }
        if (local_4c == 0x61) {
          uVar1 = 7;
        }
        else if (local_4c == 0x62) {
          uVar1 = 8;
        }
        else {
          uVar1 = 0xa2c2a;
        }
        break;
      case 0x65:
        uVar1 = 9;
        break;
      case 0x69:
        uVar1 = 10;
      }
      break;
    default:
      goto switchD_0042f532_default;
    }
  }
  else {
switchD_0042f532_default:
    uVar1 = 0xa2c2a;
  }
  return uVar1;
}


/* ==== FUN_0042facc @ 0042facc ==== */

int __cdecl FUN_0042facc(uint param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = param_1 + 0x1d;
  uVar2 = param_1 & 7;
  if (((((int)param_1 < 0x40) || (0x5f < (int)param_1)) &&
      (((int)param_1 < 0xc0 || (0xdf < (int)param_1)))) &&
     (((int)param_1 < 0x80 || ((((uVar2 != 0 && (uVar2 != 1)) && (uVar2 != 6)) && (uVar2 != 7))))))
  {
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
    thunk_FUN_00409a25(s_Invalid_EMI_memory_designation_0045acc0);
    iVar1 = 0xa2c2a;
  }
  return iVar1;
}


/* ==== FUN_0042fc06 @ 0042fc06 ==== */

int __cdecl FUN_0042fc06(int param_1,int param_2)

{
  int iVar1;
  
  if ((param_2 == 8) || (param_2 == 0x10)) {
    if (param_1 == 0) {
      iVar1 = 0x11e;
    }
    else if (param_1 == 0x11f) {
      iVar1 = (param_2 != 8) + 0x120;
    }
    else {
      iVar1 = 0xa2c2a;
    }
  }
  else {
    iVar1 = 0xa2c2a;
  }
  return iVar1;
}


/* ==== FUN_0042fc54 @ 0042fc54 ==== */

undefined4 __cdecl FUN_0042fc54(int param_1)

{
  undefined4 uVar1;
  
  if (0x14 < param_1) {
    if (0x1b < param_1) {
      if (param_1 < 0x11e) {
        if (param_1 == 0x11d) {
          return 0x11d;
        }
        if ((0x1b < param_1) && (param_1 < 0x11d)) {
          return 0x1c;
        }
      }
      else {
        if (param_1 == 0x11e) {
          return 0;
        }
        if (param_1 == 0x120) {
          return 0x11f;
        }
        if (param_1 == 0x121) {
          return 0x11f;
        }
      }
LAB_0042fd30:
      return 0xa2c2a;
    }
    if (0x19 < param_1) {
      return 0;
    }
    if (param_1 < 0x15) {
      return 0xa2c2a;
    }
    if (0x19 < param_1) {
      return 0xa2c2a;
    }
LAB_0042fd30:
    return 2;
  }
  if (param_1 < 0x10) {
    switch(param_1) {
    case 0:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
      return 0;
    case 1:
      goto switchD_0042fc83_caseD_1;
    case 2:
      goto LAB_0042fd30;
    case 3:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
      uVar1 = 3;
      break;
    case 4:
      uVar1 = 4;
      break;
    default:
      goto LAB_0042fd30;
    }
  }
  else {
switchD_0042fc83_caseD_1:
    uVar1 = 1;
  }
  return uVar1;
}


/* ==== FUN_0042fd64 @ 0042fd64 ==== */

undefined4 __cdecl FUN_0042fd64(undefined4 param_1,int param_2)

{
  switch(param_1) {
  case 0:
    if (param_2 < 0x201) {
      if (param_2 == 0x200) {
        param_1 = 0xd;
      }
      else if (param_2 == 0x100) {
        param_1 = 0xe;
      }
    }
    else if (param_2 == 0x400) {
      param_1 = 0xf;
    }
    else if (param_2 == 0x1000) {
      param_1 = 0xb;
    }
    else if (param_2 == 0x2000) {
      param_1 = 0xc;
    }
    break;
  case 1:
    if (param_2 < 0x201) {
      if (param_2 == 0x200) {
        param_1 = 0x12;
      }
      else if (param_2 == 0x100) {
        param_1 = 0x13;
      }
    }
    else if (param_2 == 0x400) {
      param_1 = 0x14;
    }
    else if (param_2 == 0x1000) {
      param_1 = 0x10;
    }
    else if (param_2 == 0x2000) {
      param_1 = 0x11;
    }
    break;
  case 2:
    if (param_2 < 0x201) {
      if (param_2 == 0x200) {
        param_1 = 0x17;
      }
      else if (param_2 == 0x100) {
        param_1 = 0x18;
      }
    }
    else if (param_2 == 0x400) {
      param_1 = 0x19;
    }
    else if (param_2 == 0x1000) {
      param_1 = 0x15;
    }
    else if (param_2 == 0x2000) {
      param_1 = 0x16;
    }
    break;
  case 3:
    if (param_2 < 0x201) {
      if (param_2 == 0x200) {
        return 9;
      }
      if (param_2 == 0x100) {
        return 10;
      }
      return param_1;
    }
    if (param_2 < 0x2001) {
      if (param_2 == 0x2000) {
        return 8;
      }
      if (param_2 != 0x1000) {
        return param_1;
      }
    }
    else {
      if (0x6000 < param_2) {
        if (param_2 == 0x9000) {
          return 6;
        }
        if (param_2 == 0xa000) {
          return 8;
        }
        return param_1;
      }
      if (param_2 == 0x6000) {
        return 7;
      }
      if (param_2 != 0x5000) {
        return param_1;
      }
    }
    param_1 = 5;
    break;
  default:
    param_1 = 0xa2c2a;
  }
  return param_1;
}


/* ==== FUN_0042ffab @ 0042ffab ==== */

char * __cdecl FUN_0042ffab(char *param_1)

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


/* ==== FUN_00430037 @ 00430037 ==== */

char * __cdecl FUN_00430037(char *param_1)

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


/* ==== FUN_004300c3 @ 004300c3 ==== */

void __cdecl FUN_004300c3(int *param_1,int param_2)

{
  char *local_8;
  
  if (param_2 == 0) {
    local_8 = &DAT_00469390;
  }
  else {
    local_8 = &DAT_00469d98;
  }
  setvbuf(param_1,local_8,0,0x800);
  return;
}


/* ==== FUN_004300f8 @ 004300f8 ==== */

bool FUN_004300f8(void)

{
  uint local_c;
  char *local_8;
  
  for (local_8 = &DAT_00461320; *local_8 != '\0'; local_8 = local_8 + 1) {
    if (__mb_cur_max < 2) {
      local_c = *(ushort *)(_pctype + *local_8 * 2) & 4;
    }
    else {
      local_c = _isctype((int)*local_8,4);
    }
    if (local_c == 0) break;
  }
  return (bool)('\x01' - (*local_8 != '\0'));
}


/* ==== FUN_0043016a @ 0043016a ==== */

int __cdecl FUN_0043016a(int param_1,int param_2)

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
      goto switchD_00430193_default;
    }
  }
  else {
    if (param_1 == 0x11d) {
      if ((param_2 != 0x11d) && (param_2 != 4)) {
        return 0xa2c2a;
      }
      return 0x11d;
    }
    if (param_1 == 0x11f) {
      if ((((param_2 != 0x11f) && (param_2 != 1)) && (param_2 != 2)) && (param_2 != 3)) {
        return 0xa2c2a;
      }
      return 0x11f;
    }
switchD_00430193_default:
    local_8 = param_2;
  }
  return local_8;
}


/* ==== FUN_004302d1 @ 004302d1 ==== */

uint * __cdecl FUN_004302d1(uint *param_1,uint *param_2,int param_3,uint param_4)

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
        local_220 = &DAT_0045ace8;
      }
      else {
        local_220 = &DAT_0045ace0;
      }
      strcpy((char *)param_1,local_220);
    }
    else {
      if (local_218 == 0) {
        local_224 = &DAT_0045acf4;
      }
      else {
        local_224 = &DAT_0045acec;
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
      strcat((char *)param_1,s_E_000_0045acf8);
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


/* ==== FUN_00430534 @ 00430534 ==== */

void FUN_00430534(void)

{
  memset(&DAT_0046c140,0,0x20);
  memset(&DAT_0046c080,0,0x20);
  return;
}


/* ==== FUN_0043055b @ 0043055b ==== */

/* WARNING: Removing unreachable block (ram,0x00430599) */
/* WARNING: Removing unreachable block (ram,0x004305d5) */
/* WARNING: Removing unreachable block (ram,0x004305dd) */
/* WARNING: Removing unreachable block (ram,0x00430600) */
/* WARNING: Removing unreachable block (ram,0x004305cc) */
/* WARNING: Removing unreachable block (ram,0x00430613) */
/* WARNING: Removing unreachable block (ram,0x0043056e) */

uint __cdecl FUN_0043055b(char *param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  
  uVar1 = fread(param_1,param_2,param_3,param_4);
  return uVar1;
}


/* ==== FUN_0043062d @ 0043062d ==== */

uint __cdecl FUN_0043062d(char *param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  
  uVar1 = fread(param_1,param_2,param_3,param_4);
  thunk_FUN_004307d5(param_1,param_2,param_3);
  return uVar1;
}


/* ==== FUN_00430667 @ 00430667 ==== */

uint __cdecl FUN_00430667(char *param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_0043055b(param_1,param_2,param_3,param_4);
  thunk_FUN_004307d5(param_1,param_2,param_3);
  return uVar1;
}


/* ==== FUN_004306a1 @ 004306a1 ==== */

/* WARNING: Removing unreachable block (ram,0x004306df) */
/* WARNING: Removing unreachable block (ram,0x0043071b) */
/* WARNING: Removing unreachable block (ram,0x00430723) */
/* WARNING: Removing unreachable block (ram,0x00430746) */
/* WARNING: Removing unreachable block (ram,0x00430712) */
/* WARNING: Removing unreachable block (ram,0x00430759) */
/* WARNING: Removing unreachable block (ram,0x004306b4) */

uint __cdecl FUN_004306a1(char *param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  
  uVar1 = fwrite(param_1,param_2,param_3,param_4);
  return uVar1;
}


/* ==== FUN_00430773 @ 00430773 ==== */

void __cdecl FUN_00430773(char *param_1,uint param_2,uint param_3,int *param_4)

{
  thunk_FUN_004307d5(param_1,param_2,param_3);
  fwrite(param_1,param_2,param_3,param_4);
  return;
}


/* ==== FUN_004307a4 @ 004307a4 ==== */

void __cdecl FUN_004307a4(char *param_1,uint param_2,uint param_3,int *param_4)

{
  thunk_FUN_004307d5(param_1,param_2,param_3);
  thunk_FUN_004306a1(param_1,param_2,param_3,param_4);
  return;
}


/* ==== FUN_004307d5 @ 004307d5 ==== */

void __cdecl FUN_004307d5(undefined1 *param_1,int param_2,int param_3)

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


/* ==== FUN_0043084b @ 0043084b ==== */

int __cdecl FUN_0043084b(int *param_1)

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
      else if (*(int *)(&DAT_00458358 + local_1c * 4) < local_2c[3]) {
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


/* ==== FUN_00430ac9 @ 00430ac9 ==== */

uint __cdecl FUN_00430ac9(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint local_c;
  
  local_c = 0;
  if (param_1 != 0) {
    uVar1 = thunk_FUN_00430b53(param_2);
    local_c = (param_1 - 1) + uVar1 & ~(uVar1 - 1);
  }
  if (DAT_00461f44 == 5) {
    local_c = local_c & param_3;
    if (local_c < param_1) {
      thunk_FUN_00409a25(s_Buffer_block_too_large_0045ad00);
    }
  }
  else {
    local_c = local_c & DAT_00461f74;
    if (local_c < param_1) {
      thunk_FUN_00409a25(s_Buffer_block_too_large_0045ad18);
    }
  }
  return local_c;
}


/* ==== FUN_00430b53 @ 00430b53 ==== */

uint __cdecl FUN_00430b53(uint param_1)

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


/* ==== FUN_00431630 @ 00431630 ==== */

undefined4 FUN_00431630(void)

{
  return DAT_0046a938;
}


/* ==== FUN_0043163a @ 0043163a ==== */

void __cdecl FUN_0043163a(int param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = fseek(param_2,param_1,0);
  if (iVar1 != 0) {
    thunk_FUN_00409a25(s_Cannot_seek_to_ELF_object_file_p_0045adc8);
  }
  DAT_0046a938 = param_1;
  return;
}


/* ==== FUN_0043166b @ 0043166b ==== */

void __cdecl FUN_0043166b(int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  char *pcVar3;
  char *pcVar4;
  short sVar5;
  char *local_18;
  char *local_10;
  
  pcVar4 = DAT_0046a964;
  local_18 = DAT_0046a964;
  sVar5 = 0;
  for (local_10 = DAT_0046a958; local_10 != (char *)0x0; local_10 = *(char **)(local_10 + 0x3c)) {
    switch(*(undefined4 *)(local_10 + 4)) {
    case 0:
      break;
    case 2:
      *(int *)(local_10 + 0x10) = DAT_0046a938;
      thunk_FUN_0043163a(DAT_0046a938,param_1);
      *(undefined4 *)(local_10 + 0x18) = DAT_0046a948;
      puVar1 = *(undefined4 **)(local_10 + 0x28);
      if (puVar1 != (undefined4 *)0x0) {
        *(undefined4 *)(local_10 + 0x14) = puVar1[1] << 4;
        local_10[0x24] = '\x10';
        local_10[0x25] = '\0';
        local_10[0x26] = '\0';
        local_10[0x27] = '\0';
        thunk_FUN_00431bbf((char *)*puVar1,*(uint *)(local_10 + 0x14),1,param_1);
        thunk_FUN_0042e1ce((undefined *)*puVar1);
        thunk_FUN_0042e1ce((undefined *)puVar1);
      }
      break;
    case 3:
      *(int *)(local_10 + 0x10) = DAT_0046a938;
      thunk_FUN_0043163a(DAT_0046a938,param_1);
      puVar1 = *(undefined4 **)(local_10 + 0x28);
      if (puVar1 != (undefined4 *)0x0) {
        *(undefined4 *)(local_10 + 0x14) = puVar1[1];
        local_10[0x24] = '\0';
        local_10[0x25] = '\0';
        local_10[0x26] = '\0';
        local_10[0x27] = '\0';
        thunk_FUN_00431bbf((char *)*puVar1,*(uint *)(local_10 + 0x14),1,param_1);
        thunk_FUN_0042e1ce((undefined *)*puVar1);
        thunk_FUN_0042e1ce((undefined *)puVar1);
      }
      break;
    case 9:
      *(int *)(local_10 + 0x10) = DAT_0046a938;
      thunk_FUN_0043163a(DAT_0046a938,param_1);
      *(undefined4 *)(local_10 + 0x18) = DAT_0046a944;
      piVar2 = *(int **)(local_10 + 0x28);
      if (piVar2 != (int *)0x0) {
        *(int *)(local_10 + 0x14) = *piVar2 << 3;
        local_10[0x24] = '\b';
        local_10[0x25] = '\0';
        local_10[0x26] = '\0';
        local_10[0x27] = '\0';
        thunk_FUN_00431bbf((char *)piVar2[2],*(uint *)(local_10 + 0x14),1,param_1);
        thunk_FUN_0042e1ce((undefined *)piVar2[2]);
        thunk_FUN_0042e1ce((undefined *)piVar2);
      }
    }
  }
  *(int *)(DAT_0046a950 + 0x20) = DAT_0046a938;
  local_10 = DAT_0046a958;
  while (local_10 != (char *)0x0) {
    pcVar3 = *(char **)(local_10 + 0x3c);
    thunk_FUN_00431c05(local_10,4,1,param_1);
    thunk_FUN_00431c05(local_10 + 4,4,1,param_1);
    thunk_FUN_00431c05(local_10 + 8,4,1,param_1);
    thunk_FUN_00431c05(local_10 + 0xc,4,1,param_1);
    thunk_FUN_00431c05(local_10 + 0x10,4,1,param_1);
    thunk_FUN_00431c05(local_10 + 0x14,4,1,param_1);
    thunk_FUN_00431c05(local_10 + 0x18,4,1,param_1);
    thunk_FUN_00431c05(local_10 + 0x1c,4,1,param_1);
    thunk_FUN_00431c05(local_10 + 0x20,4,1,param_1);
    thunk_FUN_00431c05(local_10 + 0x24,4,1,param_1);
    thunk_FUN_0042e1ce(*(undefined **)(local_10 + 0x2c));
    thunk_FUN_0042e1ce(local_10);
    local_10 = pcVar3;
  }
  if (pcVar4 == (char *)0x0) {
    pcVar4 = DAT_0046a950;
    pcVar4[0x1c] = '\0';
    pcVar4[0x1d] = '\0';
    pcVar4[0x1e] = '\0';
    pcVar4[0x1f] = '\0';
  }
  else {
    *(int *)(DAT_0046a950 + 0x1c) = DAT_0046a938;
  }
  pcVar4 = DAT_0046a950;
  pcVar4[0x2a] = ' ';
  pcVar4[0x2b] = '\0';
  while (local_18 != (char *)0x0) {
    pcVar4 = *(char **)(local_18 + 0x20);
    thunk_FUN_00431bbf(local_18,0x20,1,param_1);
    sVar5 = sVar5 + 1;
    thunk_FUN_0042e1ce(local_18);
    local_18 = pcVar4;
  }
  *(short *)(DAT_0046a950 + 0x2c) = sVar5;
  *(undefined2 *)(DAT_0046a950 + 0x30) = DAT_0046a93c;
  thunk_FUN_0043163a(0,param_1);
  thunk_FUN_00431bbf(DAT_0046a950,0x10,1,param_1);
  thunk_FUN_00431c05(DAT_0046a950 + 0x10,2,1,param_1);
  thunk_FUN_00431c05(DAT_0046a950 + 0x12,2,1,param_1);
  thunk_FUN_00431c05(DAT_0046a950 + 0x14,4,1,param_1);
  thunk_FUN_00431c05(DAT_0046a950 + 0x18,4,1,param_1);
  thunk_FUN_00431c05(DAT_0046a950 + 0x1c,4,1,param_1);
  thunk_FUN_00431c05(DAT_0046a950 + 0x20,4,1,param_1);
  thunk_FUN_00431c05(DAT_0046a950 + 0x24,4,1,param_1);
  thunk_FUN_00431c05(DAT_0046a950 + 0x28,2,1,param_1);
  thunk_FUN_00431c05(DAT_0046a950 + 0x2a,2,1,param_1);
  thunk_FUN_00431c05(DAT_0046a950 + 0x2c,2,1,param_1);
  thunk_FUN_00431c05(DAT_0046a950 + 0x2e,2,1,param_1);
  thunk_FUN_00431c05(DAT_0046a950 + 0x30,2,1,param_1);
  thunk_FUN_00431c05(DAT_0046a950 + 0x32,2,1,param_1);
  thunk_FUN_0042e1ce(DAT_0046a950);
  return;
}


/* ==== FUN_00431bbf @ 00431bbf ==== */

void __cdecl FUN_00431bbf(char *param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  
  if (param_2 != 0) {
    uVar1 = fwrite(param_1,param_2,param_3,param_4);
    if (uVar1 != 1) {
      thunk_FUN_00409a25(s_Cannot_write_data_to_ELF_object_f_0045adf0);
    }
    DAT_0046a938 = DAT_0046a938 + param_2;
  }
  return;
}


/* ==== FUN_00431c05 @ 00431c05 ==== */

void __cdecl FUN_00431c05(char *param_1,uint param_2,uint param_3,int *param_4)

{
  int iVar1;
  
  if (param_2 != 0) {
    iVar1 = thunk_FUN_004326d0(param_1,param_2,param_3,param_4);
    if (iVar1 != 1) {
      thunk_FUN_00409a25(s_Cannot_write_data_to_ELF_object_f_0045ae18);
    }
    DAT_0046a938 = DAT_0046a938 + param_2;
  }
  return;
}


/* ==== FUN_00431c4b @ 00431c4b ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __cdecl FUN_00431c4b(uint *param_1)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  
  if (DAT_0046a954 == (int *)0x0) {
    DAT_0046a954 = (int *)thunk_FUN_0042e170(0x40);
    uVar1 = strlen((char *)param_1);
    iVar2 = thunk_FUN_0042e170(uVar1 + 1);
    DAT_0046a954[0xb] = iVar2;
    strcpy((char *)DAT_0046a954[0xb],(char *)param_1);
    *DAT_0046a954 = DAT_0046a978[1];
    FUN_00431ee8(DAT_0046a978,param_1);
    DAT_0046a940 = 0;
    _DAT_0046a93c = 0;
    DAT_0046a954[0xc] = 0;
    _DAT_0046a93c = _DAT_0046a93c + 1;
    DAT_0046a940 = DAT_0046a940 + 1;
    DAT_0046a954[10] = 0;
    DAT_0046a954[0xe] = 0;
    DAT_0046a954[0xf] = 0;
    DAT_0046a954[1] = 0;
    DAT_0046a954[2] = 0;
    DAT_0046a954[3] = 0;
    DAT_0046a954[4] = 0;
    DAT_0046a954[5] = 0;
    DAT_0046a954[6] = 0;
    DAT_0046a954[7] = 0;
    DAT_0046a954[8] = 0;
    DAT_0046a954[9] = 0;
    DAT_0046a954[0xd] = 0;
    DAT_0046a958 = DAT_0046a954;
  }
  else {
    piVar3 = (int *)thunk_FUN_0042e170(0x40);
    uVar1 = strlen((char *)param_1);
    iVar2 = thunk_FUN_0042e170(uVar1 + 1);
    piVar3[0xb] = iVar2;
    strcpy((char *)piVar3[0xb],(char *)param_1);
    piVar3[0xc] = _DAT_0046a93c;
    _DAT_0046a93c = _DAT_0046a93c + 1;
    DAT_0046a940 = DAT_0046a940 + 1;
    *piVar3 = DAT_0046a978[1];
    FUN_00431ee8(DAT_0046a978,param_1);
    piVar3[10] = 0;
    piVar3[0xf] = 0;
    piVar3[1] = 0;
    piVar3[2] = 0;
    piVar3[3] = 0;
    piVar3[4] = 0;
    piVar3[5] = 0;
    piVar3[6] = 0;
    piVar3[7] = 0;
    piVar3[8] = 0;
    piVar3[9] = 0;
    piVar3[0xd] = 0;
    piVar3[0xe] = (int)DAT_0046a954;
    *(int **)((int)DAT_0046a954 + 0x3c) = piVar3;
    DAT_0046a954 = *(int **)((int)DAT_0046a954 + 0x3c);
  }
  return DAT_0046a954;
}


/* ==== FUN_00431ee8 @ 00431ee8 ==== */

int __cdecl FUN_00431ee8(int *param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  
  uVar2 = strlen((char *)param_2);
  iVar1 = param_1[1];
  if (*param_1 == 0) {
    param_1[2] = param_1[2] + 0x400;
    iVar3 = thunk_FUN_0042e170(param_1[2]);
    *param_1 = iVar3;
    memset((void *)*param_1,0,param_1[2]);
  }
  else if (param_1[2] <= (int)(param_1[1] + uVar2 + 1)) {
    iVar3 = param_1[2];
    if (param_1[2] < 0x400) {
      param_1[2] = param_1[2] << 1;
    }
    else {
      param_1[2] = param_1[2] + 0x400;
    }
    piVar4 = thunk_FUN_0042e19d((int *)*param_1,param_1[2]);
    *param_1 = (int)piVar4;
    memset((void *)(*param_1 + iVar3),0,param_1[2] - iVar3);
  }
  strcpy((char *)(*param_1 + param_1[1]),(char *)param_2);
  param_1[1] = param_1[1] + uVar2 + 1;
  return iVar1;
}


/* ==== FUN_00431ffd @ 00431ffd ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00431ffd(void)

{
  undefined4 *extraout_EAX;
  undefined4 *extraout_EAX_00;
  int *piVar1;
  
  FUN_00432261();
  DAT_0046a938 = 0;
  _DAT_0046a93c = 0;
  DAT_0046a940 = 0;
  DAT_0046a944 = 0;
  DAT_0046a948 = 0;
  DAT_0046a958 = 0;
  DAT_0046a954 = 0;
  _DAT_0046a95c = 0;
  DAT_0046a964 = 0;
  _DAT_0046a960 = 0;
  DAT_0046a970 = (undefined4 *)0x0;
  DAT_0046a974 = (undefined4 *)0x0;
  DAT_0046a978 = (undefined4 *)0x0;
  DAT_0046a980 = 0;
  _DAT_0046a97c = 0;
  DAT_0046a970 = (undefined4 *)thunk_FUN_0042e170(0xc);
  *DAT_0046a970 = 0;
  DAT_0046a970[1] = 0;
  DAT_0046a970[2] = 0;
  malloc(0xc);
  DAT_0046a974 = extraout_EAX;
  *extraout_EAX = 0;
  DAT_0046a974[1] = 0;
  DAT_0046a974[2] = 0;
  malloc(0xc);
  DAT_0046a978 = extraout_EAX_00;
  *extraout_EAX_00 = 0;
  DAT_0046a978[1] = 0;
  DAT_0046a978[2] = 0;
  piVar1 = thunk_FUN_00431c4b((uint *)&DAT_0046a984);
  piVar1[1] = 0;
  piVar1[6] = 0;
  piVar1 = thunk_FUN_00431c4b((uint *)s__shstrtab_0045ae40);
  piVar1[1] = 3;
  piVar1[2] = 0;
  piVar1[10] = (int)DAT_0046a978;
  *(short *)(DAT_0046a950 + 0x32) = (short)piVar1[0xc];
  piVar1 = thunk_FUN_00431c4b((uint *)s__strtab_0045ae4c);
  piVar1[1] = 3;
  piVar1[2] = piVar1[2] | 2;
  piVar1[10] = (int)DAT_0046a974;
  DAT_0046a948 = piVar1[0xc];
  piVar1 = thunk_FUN_00431c4b((uint *)s__note_0045ae54);
  piVar1[1] = 7;
  piVar1[2] = 0;
  _DAT_0046a94c = piVar1[0xc];
  piVar1 = thunk_FUN_00431c4b((uint *)s__symtab_0045ae5c);
  piVar1[1] = 2;
  piVar1[2] = piVar1[2] | 2;
  piVar1[6] = DAT_0046a948;
  piVar1[10] = (int)DAT_0046a970;
  DAT_0046a944 = piVar1[0xc];
  return;
}


/* ==== FUN_00432261 @ 00432261 ==== */

void FUN_00432261(void)

{
  int local_8;
  
  DAT_0046a950 = (undefined1 *)thunk_FUN_0042e170(0x34);
  *DAT_0046a950 = 0x7f;
  DAT_0046a950[1] = 0x45;
  DAT_0046a950[2] = 0x4c;
  DAT_0046a950[3] = 0x46;
  DAT_0046a950[4] = 1;
  DAT_0046a950[5] = 2;
  DAT_0046a950[6] = 1;
  for (local_8 = 0x10; 6 < local_8; local_8 = local_8 + -1) {
    DAT_0046a950[local_8] = 0;
  }
  *(undefined2 *)(DAT_0046a950 + 0x10) = 2;
  *(undefined2 *)(DAT_0046a950 + 0x12) = 2;
  *(undefined4 *)(DAT_0046a950 + 0x14) = 1;
  *(undefined4 *)(DAT_0046a950 + 0x18) = 0;
  *(undefined4 *)(DAT_0046a950 + 0x1c) = 0;
  *(undefined4 *)(DAT_0046a950 + 0x20) = 0;
  *(undefined4 *)(DAT_0046a950 + 0x24) = 0;
  *(undefined2 *)(DAT_0046a950 + 0x28) = 0x34;
  *(undefined2 *)(DAT_0046a950 + 0x2a) = 0;
  *(undefined2 *)(DAT_0046a950 + 0x2c) = 0;
  *(undefined2 *)(DAT_0046a950 + 0x2e) = 0x28;
  *(undefined2 *)(DAT_0046a950 + 0x30) = 0;
  *(undefined2 *)(DAT_0046a950 + 0x32) = 0;
  return;
}


/* ==== FUN_004326d0 @ 004326d0 ==== */

void __cdecl FUN_004326d0(char *param_1,uint param_2,uint param_3,int *param_4)

{
  if ((int)param_2 < 5) {
    FUN_0043271d(param_1,param_2,param_3);
  }
  else {
    thunk_FUN_004307d5(param_1,param_2,param_3);
  }
  fwrite(param_1,param_2,param_3,param_4);
  return;
}


/* ==== FUN_0043271d @ 0043271d ==== */

void __cdecl FUN_0043271d(undefined1 *param_1,int param_2)

{
  undefined1 uVar1;
  
  if (param_2 == 2) {
    uVar1 = *param_1;
    *param_1 = param_1[1];
    param_1[1] = uVar1;
  }
  else if (param_2 == 4) {
    uVar1 = *param_1;
    *param_1 = param_1[3];
    param_1[3] = uVar1;
    uVar1 = param_1[1];
    param_1[1] = param_1[2];
    param_1[2] = uVar1;
  }
  return;
}


/* ==== FUN_00432799 @ 00432799 ==== */

undefined4 __cdecl FUN_00432799(LPCSTR param_1,LPCSTR param_2)

{
  void *extraout_EAX;
  undefined4 uVar1;
  int iVar2;
  int *extraout_EAX_00;
  char *pcVar3;
  uint uVar4;
  uint *dst;
  int *piVar5;
  undefined4 *local_14;
  
  DAT_0046ac54 = param_1;
  DAT_0046ac58 = param_2;
  fopen(param_1,&DAT_0045ae84);
  DAT_0046abac = extraout_EAX;
  if (extraout_EAX == (void *)0x0) {
    fprintf(&DAT_0045d670,s_Cannot_open__s_0045ae88,DAT_0046ac54);
    uVar1 = 1;
  }
  else {
    iVar2 = FUN_00432a34();
    if (iVar2 == 0) {
      thunk_FUN_00431ffd();
      fopen(DAT_0046ac58,&DAT_0045ae98);
      DAT_0046ac5c = extraout_EAX_00;
      if (extraout_EAX_00 == (int *)0x0) {
        fprintf(&DAT_0045d670,s_Cannot_open__s_0045ae9c,DAT_0046ac58);
        uVar1 = 1;
      }
      else {
        thunk_FUN_0043163a(0x34,extraout_EAX_00);
        setbuf(DAT_0046ac5c,(char *)0x0);
        for (local_14 = DAT_0046ac64; local_14 != (undefined4 *)0x0;
            local_14 = (undefined4 *)local_14[7]) {
          *local_14 = local_14[1];
          pcVar3 = (char *)FUN_00433153(local_14);
          iVar2 = thunk_FUN_00431630();
          thunk_FUN_00431bbf(pcVar3,local_14[5],1,DAT_0046ac5c);
          uVar4 = strlen((char *)local_14[2]);
          dst = (uint *)thunk_FUN_0042e170(uVar4 + 2);
          strcpy((char *)dst,&DAT_0045aeac);
          strcat((char *)dst,(char *)local_14[2]);
          piVar5 = thunk_FUN_00431c4b(dst);
          piVar5[1] = 1;
          piVar5[2] = 0;
          piVar5[3] = local_14[4];
          piVar5[4] = iVar2;
          piVar5[5] = local_14[5];
          piVar5[6] = 0;
          piVar5[7] = 0;
          piVar5[8] = 0;
          piVar5[9] = 0;
          thunk_FUN_0042e1ce(pcVar3);
        }
        thunk_FUN_0043166b(DAT_0046ac5c);
        FUN_004329ca();
        fclose(DAT_0046abac);
        fclose(DAT_0046ac5c);
        uVar1 = 0;
      }
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}


/* ==== FUN_004329ca @ 004329ca ==== */

void FUN_004329ca(void)

{
  int *piVar1;
  int iVar2;
  int *local_8;
  
  local_8 = DAT_0046ac64;
  while (local_8 != (int *)0x0) {
    piVar1 = (int *)local_8[7];
    *local_8 = local_8[1];
    while (*local_8 != 0) {
      iVar2 = *(int *)*local_8;
      thunk_FUN_0042e1ce((undefined *)*local_8);
      *local_8 = iVar2;
    }
    thunk_FUN_0042e1ce((undefined *)local_8);
    local_8 = piVar1;
  }
  return;
}


/* ==== FUN_00432a34 @ 00432a34 ==== */

undefined4 FUN_00432a34(void)

{
  bool bVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined3 extraout_var;
  int iVar4;
  
  uVar2 = thunk_FUN_0043062d((char *)&DAT_0046abb0,0x1c,1,DAT_0046abac);
  if (uVar2 == 1) {
    if (((((DAT_0046abb0 == 0x2c5) || (DAT_0046abb0 == 0x2c6)) || (DAT_0046abb0 == 0x2c7)) ||
        ((DAT_0046abb0 == 0x2c8 || (DAT_0046abb0 == 0x2c9)))) ||
       ((DAT_0046abb0 == 0x2ca || ((DAT_0046abb0 == 0x2cb || (DAT_0046abb0 == 0x2cc)))))) {
      bVar1 = FUN_0043313b(DAT_0046abc8);
      if (CONCAT31(extraout_var,bVar1) == 0) {
        uVar3 = 1;
      }
      else {
        DAT_0046ac40 = DAT_0046abb4;
        DAT_0046ac4c = DAT_0046abc0;
        DAT_0046ac48 = DAT_0046abbc;
        DAT_0046ac50 = (uint)((DAT_0046abc8 & 1) != 0);
        if (DAT_0046abc4 != 0) {
          if (DAT_0046ac50 == 0) {
            uVar2 = thunk_FUN_0043062d(&DAT_0046ac08,DAT_0046abc4,1,DAT_0046abac);
            if (uVar2 != 1) {
              thunk_FUN_00409a25(s_Cannot_read_COFF_linker_file_hea_0045af18);
              return 1;
            }
          }
          else {
            uVar2 = thunk_FUN_0043062d(&DAT_0046abcc,DAT_0046abc4,1,DAT_0046abac);
            if (uVar2 != 1) {
              thunk_FUN_00409a25(s_Cannot_read_COFF_optional_file_h_0045aef0);
              return 1;
            }
          }
        }
        DAT_0046ac44 = DAT_0046abc4 + 0x1c;
        iVar4 = FUN_00432c0a(DAT_0046ac48,DAT_0046ac4c);
        if (iVar4 == 0) {
          iVar4 = FUN_00432d7b(DAT_0046ac44,DAT_0046ac40);
          if (iVar4 == 0) {
            uVar3 = 0;
          }
          else {
            uVar3 = 1;
          }
        }
        else {
          uVar3 = 1;
        }
      }
    }
    else {
      thunk_FUN_00409a25(s_Invalid_COFF_object_file_format_0045aed0);
      uVar3 = 1;
    }
  }
  else {
    thunk_FUN_00409a25(s_Cannot_read_COFF_file_header_0045aeb0);
    uVar3 = 1;
  }
  return uVar3;
}


/* ==== FUN_00432c0a @ 00432c0a ==== */

undefined4 __cdecl FUN_00432c0a(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  if (param_2 == 0) {
    uVar1 = 1;
  }
  else {
    DAT_0046aba4 = param_1 + param_2 * 0x20;
    iVar2 = fseek(DAT_0046abac,DAT_0046aba4,0);
    if (iVar2 == 0) {
      uVar3 = thunk_FUN_0043062d((char *)&DAT_0046aba0,4,1,DAT_0046abac);
      if ((uVar3 == 1) || ((DAT_0046abac[3] & 0x10U) != 0)) {
        if ((DAT_0046abac[3] & 0x10U) == 0) {
          if (DAT_0046aba0 != 0) {
            DAT_0046aba0 = DAT_0046aba0 - 4;
            if ((int)DAT_0046aba0 < 0) {
              thunk_FUN_00409a25(s_invalid_COFF_string_table_length_0045af80);
              return 1;
            }
            DAT_0046aba8 = (void *)thunk_FUN_0042e170(DAT_0046aba0);
            iVar2 = fseek(DAT_0046abac,DAT_0046aba4 + 4,0);
            if (iVar2 != 0) {
              thunk_FUN_00409a25(s_cannot_seek_to_COFF_string_table_0045afa4);
              return 1;
            }
            uVar3 = fread(DAT_0046aba8,DAT_0046aba0,1,DAT_0046abac);
            if (uVar3 != 1) {
              thunk_FUN_00409a25(s_cannot_read_COFF_string_table_0045afc8);
              return 1;
            }
          }
        }
        else {
          DAT_0046aba0 = 0;
        }
        uVar1 = 0;
      }
      else {
        thunk_FUN_00409a25(s_Cannot_read_COFF_string_table_le_0045af58);
        uVar1 = 1;
      }
    }
    else {
      thunk_FUN_00409a25(s_cannot_seek_to_string_table_0045af3c);
      uVar1 = 1;
    }
  }
  return uVar1;
}


/* ==== FUN_00432d7b @ 00432d7b ==== */

undefined4 __cdecl FUN_00432d7b(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int local_48 [2];
  undefined4 local_40;
  int local_30;
  undefined4 local_2c;
  uint local_18;
  uint *local_14;
  int local_10;
  int *local_c;
  int local_8;
  
  local_10 = 0;
  while( true ) {
    if (param_2 <= local_10) {
      return 0;
    }
    iVar3 = fseek(DAT_0046abac,param_1,0);
    if (iVar3 != 0) break;
    uVar4 = thunk_FUN_0043062d((char *)local_48,0x34,1,DAT_0046abac);
    if (uVar4 != 1) {
      thunk_FUN_00409a25(s_Can_t_read_COFF_section_header_0045b00c);
      return 1;
    }
    if (local_48[0] != 0) {
      thunk_FUN_004307d5((undefined1 *)local_48,4,2);
    }
    if ((local_30 != 0) && ((local_18 & 0x100) != 0)) {
      local_14 = (uint *)FUN_004330e5(local_48);
      uVar2 = local_2c;
      uVar1 = local_40;
      if (local_14 == (uint *)0x0) {
        return 1;
      }
      local_8 = local_30;
      local_c = (int *)FUN_004330a6((char *)local_14);
      if (local_c == (int *)0x0) {
        FUN_00432ebf(local_14,uVar1,local_8,local_10,uVar2);
      }
      else {
        FUN_00432ffa(local_c,uVar1,local_8,local_10,uVar2);
      }
    }
    param_1 = param_1 + 0x34;
    local_10 = local_10 + 1;
  }
  thunk_FUN_00409a25(s_COFF_section_header_seek_failure_0045afe8);
  return 1;
}


/* ==== FUN_00432ebf @ 00432ebf ==== */

void __cdecl
FUN_00432ebf(uint *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  uint uVar1;
  int iVar2;
  void *pvVar3;
  
  if (DAT_0046ac60 == (void *)0x0) {
    DAT_0046ac60 = FUN_00432fd2();
    uVar1 = strlen((char *)param_1);
    iVar2 = thunk_FUN_0042e170(uVar1 + 1);
    *(int *)((int)DAT_0046ac60 + 8) = iVar2;
    strcpy(*(char **)((int)DAT_0046ac60 + 8),(char *)param_1);
    *(undefined4 *)((int)DAT_0046ac60 + 0x10) = param_2;
    *(undefined4 *)((int)DAT_0046ac60 + 0x14) = param_3;
    *(undefined4 *)((int)DAT_0046ac60 + 0x18) = param_4;
    *(undefined4 *)((int)DAT_0046ac60 + 0xc) = param_5;
    DAT_0046ac64 = DAT_0046ac60;
  }
  else {
    pvVar3 = FUN_00432fd2();
    *(void **)((int)DAT_0046ac60 + 0x1c) = pvVar3;
    DAT_0046ac60 = *(void **)((int)DAT_0046ac60 + 0x1c);
    uVar1 = strlen((char *)param_1);
    iVar2 = thunk_FUN_0042e170(uVar1 + 1);
    *(int *)((int)DAT_0046ac60 + 8) = iVar2;
    strcpy(*(char **)((int)DAT_0046ac60 + 8),(char *)param_1);
    *(undefined4 *)((int)DAT_0046ac60 + 0x10) = param_2;
    *(undefined4 *)((int)DAT_0046ac60 + 0x14) = param_3;
    *(undefined4 *)((int)DAT_0046ac60 + 0x18) = param_4;
    *(undefined4 *)((int)DAT_0046ac60 + 0xc) = param_5;
  }
  return;
}


/* ==== FUN_00432fd2 @ 00432fd2 ==== */

void * FUN_00432fd2(void)

{
  void *dst;
  
  dst = (void *)thunk_FUN_0042e170(0x20);
  memset(dst,0,0x20);
  return dst;
}


/* ==== FUN_00432ffa @ 00432ffa ==== */

void __cdecl
FUN_00432ffa(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  void *pvVar1;
  
  if (*param_1 == 0) {
    pvVar1 = FUN_00432fd2();
    *param_1 = (int)pvVar1;
    *(undefined4 *)(*param_1 + 8) = 0;
    *(undefined4 *)(*param_1 + 0x10) = param_2;
    *(undefined4 *)(*param_1 + 0x14) = param_3;
    *(undefined4 *)(*param_1 + 0x18) = param_4;
    *(undefined4 *)(*param_1 + 0xc) = param_5;
    param_1[1] = *param_1;
  }
  else {
    pvVar1 = FUN_00432fd2();
    *(void **)*param_1 = pvVar1;
    *param_1 = *(int *)*param_1;
    *(undefined4 *)(*param_1 + 8) = 0;
    *(undefined4 *)(*param_1 + 0x10) = param_2;
    *(undefined4 *)(*param_1 + 0x14) = param_3;
    *(undefined4 *)(*param_1 + 0x18) = param_4;
    *(undefined4 *)(*param_1 + 0xc) = param_5;
  }
  return;
}


/* ==== FUN_004330a6 @ 004330a6 ==== */

int __cdecl FUN_004330a6(char *param_1)

{
  int iVar1;
  int local_8;
  
  local_8 = DAT_0046ac64;
  while( true ) {
    if (local_8 == 0) {
      return 0;
    }
    iVar1 = strcmp(*(char **)(local_8 + 8),param_1);
    if (iVar1 == 0) break;
    local_8 = *(int *)(local_8 + 0x1c);
  }
  return local_8;
}


/* ==== FUN_004330e5 @ 004330e5 ==== */

int * __cdecl FUN_004330e5(int *param_1)

{
  if (*param_1 == 0) {
    if ((param_1[1] < 4) || (DAT_0046aba0 < param_1[1])) {
      thunk_FUN_00409a25(s_invalid_COFF_string_table_offset_0045b02c);
      param_1 = (int *)0x0;
    }
    else {
      param_1 = (int *)(DAT_0046aba8 + -4 + param_1[1]);
    }
  }
  return param_1;
}


/* ==== FUN_0043313b @ 0043313b ==== */

bool __cdecl FUN_0043313b(uint param_1)

{
  return (param_1 & 2) != 0;
}


/* ==== FUN_00433153 @ 00433153 ==== */

int __cdecl FUN_00433153(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint local_18;
  int local_14;
  int local_c;
  
  puVar1 = param_1;
  local_c = 0;
  local_18 = 0;
  for (; param_1 != (undefined4 *)0x0; param_1 = (undefined4 *)*param_1) {
    local_18 = local_18 + param_1[5];
  }
  puVar2 = (undefined *)thunk_FUN_0042e170(local_18 << 2);
  iVar3 = thunk_FUN_0042e170(local_18);
  param_1 = puVar1;
  while( true ) {
    if (param_1 == (undefined4 *)0x0) {
      puVar1[5] = local_c;
      for (local_14 = 0; local_14 < (int)puVar1[5]; local_14 = local_14 + 1) {
        *(undefined *)(iVar3 + local_14) = puVar2[local_14 * 4];
      }
      thunk_FUN_0042e1ce(puVar2);
      return iVar3;
    }
    iVar4 = fseek(DAT_0046abac,param_1[3],0);
    if (iVar4 != 0) {
      thunk_FUN_00409a25(s_Cannot_seek_COFF_input_file_0045b068);
    }
    uVar5 = thunk_FUN_0043062d(puVar2 + local_c * 4,param_1[5] << 2,1,DAT_0046abac);
    if ((uVar5 != 1) && ((DAT_0046abac[3] & 0x10U) == 0)) break;
    local_c = local_c + param_1[5];
    param_1 = (undefined4 *)*param_1;
  }
  FUN_0043329e();
  thunk_FUN_00409a25(s_Read_of_COFF_data_failed_0045b084);
  return 0;
}


/* ==== FUN_0043329e @ 0043329e ==== */

void FUN_0043329e(void)

{
  return;
}


/* ==== FUN_004335b0 @ 004335b0 ==== */

void FUN_004335b0(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  printf(s_Msg___s__Val___s_0045b108,in_stack_00000008,in_stack_00000004);
  return;
}


/* ==== FUN_004335ca @ 004335ca ==== */

void FUN_004335ca(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  printf(s_Msg___s__Val___ld_0045b11c,in_stack_00000008,in_stack_00000004);
  return;
}


/* ==== FUN_004335e4 @ 004335e4 ==== */

void FUN_004335e4(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  printf(s_Msg___s__Unsigned_long_Val___lu_0045b130,in_stack_00000008,in_stack_00000004);
  return;
}


/* ==== FUN_00433620 @ 00433620 ==== */

void __cdecl FUN_00433620(undefined *param_1)

{
  if (param_1 != (undefined *)0x0) {
    FUN_004337cc((int)param_1);
    free(param_1);
  }
  return;
}


/* ==== FUN_0043364a @ 0043364a ==== */

/* WARNING: Removing unreachable block (ram,0x0043365a) */

uint * __cdecl FUN_0043364a(uint param_1,uint param_2,uint param_3)

{
  uint *extraout_EAX;
  
  malloc(0x40);
  if (param_2 == 0) {
    *extraout_EAX = 0x32;
  }
  else {
    *extraout_EAX = param_2;
  }
  if (param_3 == 0) {
    extraout_EAX[0xf] = (uint)FUN_00433b99;
  }
  else {
    extraout_EAX[0xf] = param_3;
  }
  extraout_EAX[1] = param_1;
  extraout_EAX[2] = 0;
  extraout_EAX[4] = 0xffffffff;
  extraout_EAX[5] = 0xffffffff;
  extraout_EAX[3] = 0;
  extraout_EAX[7] = 0;
  extraout_EAX[0xe] = (uint)FUN_0043374a;
  extraout_EAX[8] = (uint)FUN_00433b02;
  extraout_EAX[9] = (uint)FUN_00433ab6;
  extraout_EAX[10] = (uint)FUN_00433a50;
  extraout_EAX[0xc] = (uint)FUN_00433b6a;
  extraout_EAX[0xd] = (uint)FUN_00433b3b;
  extraout_EAX[0xb] = (uint)FUN_0043386c;
  FUN_004338b8(extraout_EAX,extraout_EAX[1]);
  return extraout_EAX;
}


/* ==== FUN_0043374a @ 0043374a ==== */

void FUN_0043374a(void)

{
  undefined4 *in_stack_00000004;
  
  printf(s__________Dumping_Array_Informati_0045b190);
  printf(s_1__array_size____d_0045b1c0,in_stack_00000004[2]);
  printf(s_2__blocksz____d_0045b1d8,*in_stack_00000004);
  printf(s_3__max_index____d_0045b1f0,in_stack_00000004[4]);
  printf(s_4__last_index____d_0045b208,in_stack_00000004[5]);
  printf(s_5__remove____d_0045b220,in_stack_00000004[3]);
  printf(s__________End_Dumping_____________0045b238);
  return;
}


/* ==== FUN_004337cc @ 004337cc ==== */

void __cdecl FUN_004337cc(int param_1)

{
  undefined4 local_8;
  
  if (*(int *)(param_1 + 0xc) == 1) {
    for (local_8 = 0; local_8 <= *(int *)(param_1 + 0x10); local_8 = local_8 + 1) {
      if (*(int *)(*(int *)(param_1 + 0x18) + local_8 * 4) == 1) {
        (**(code **)(param_1 + 0x3c))(*(undefined4 *)(*(int *)(param_1 + 0x1c) + local_8 * 4));
      }
    }
  }
  if (*(int *)(param_1 + 0x1c) != 0) {
    free(*(void **)(param_1 + 0x1c));
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  if (*(int *)(param_1 + 0x18) != 0) {
    free(*(void **)(param_1 + 0x18));
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  return;
}


/* ==== FUN_0043386c @ 0043386c ==== */

void __cdecl FUN_0043386c(uint *param_1)

{
  FUN_004337cc((int)param_1);
  param_1[2] = 0;
  param_1[4] = 0xffffffff;
  param_1[5] = 0xffffffff;
  param_1[3] = 0;
  FUN_004338b8(param_1,param_1[1]);
  return;
}


/* ==== FUN_004338b8 @ 004338b8 ==== */

void __cdecl FUN_004338b8(uint *param_1,uint param_2)

{
  uint extraout_EAX;
  uint extraout_EAX_00;
  uint extraout_EAX_01;
  uint extraout_EAX_02;
  uint size;
  int iVar1;
  uint local_18;
  uint local_c;
  uint local_8;
  
  if (((int)param_2 < 1) || (param_1[7] != 0)) {
    iVar1 = (param_2 + 1) / *param_1 + 1;
    local_8 = iVar1 * *param_1;
  }
  else {
    iVar1 = 1;
    local_8 = param_2;
  }
  size = local_8 * 4;
  if (param_1[7] == 0) {
    malloc(size);
    malloc(local_8 << 2);
    local_18 = extraout_EAX_00;
    local_c = extraout_EAX;
  }
  else {
    realloc((void *)param_1[7],size);
    realloc((void *)param_1[6],local_8 << 2);
    local_18 = extraout_EAX_02;
    local_c = extraout_EAX_01;
  }
  if ((local_c == 0) || (local_18 == 0)) {
    fprintf(&DAT_0045d670,s_Cannot_alloc_array_0045b268,iVar1);
    _assert(&DAT_0045b28c,s_LONGInfArray_c_0045b27c,299);
    exit(1);
  }
  else {
    param_1[7] = local_c;
    param_1[6] = local_18;
    memset((void *)(param_1[7] + param_1[2] * 4),0,size + param_1[2] * -4);
    memset((void *)(param_1[6] + param_1[2] * 4),0,local_8 - param_1[2]);
  }
  param_1[2] = local_8;
  return;
}


/* ==== FUN_00433a50 @ 00433a50 ==== */

void __cdecl FUN_00433a50(uint *param_1,uint param_2,undefined4 param_3)

{
  if (param_1[2] <= param_2) {
    FUN_004338b8(param_1,param_2);
  }
  *(undefined4 *)(param_1[7] + param_2 * 4) = param_3;
  param_1[5] = param_2;
  *(undefined4 *)(param_1[6] + param_2 * 4) = 1;
  param_1[3] = 1;
  if ((int)param_1[4] < (int)param_2) {
    param_1[4] = param_2;
  }
  return;
}


/* ==== FUN_00433ab6 @ 00433ab6 ==== */

void __cdecl FUN_00433ab6(uint *param_1,uint param_2,undefined4 param_3)

{
  if (param_1[2] <= param_2) {
    FUN_004338b8(param_1,param_2);
  }
  *(undefined4 *)(param_1[7] + param_2 * 4) = param_3;
  param_1[5] = param_2;
  if ((int)param_1[4] < (int)param_2) {
    param_1[4] = param_2;
  }
  return;
}


/* ==== FUN_00433b02 @ 00433b02 ==== */

undefined4 __cdecl FUN_00433b02(int param_1,int param_2)

{
  if ((param_2 < 0) || (*(int *)(param_1 + 0x10) < param_2)) {
    _assert(s__index>_0______index_<__arr_>max_0045b2a0,s_LONGInfArray_c_0045b290,0x18b);
  }
  return *(undefined4 *)(*(int *)(param_1 + 0x1c) + param_2 * 4);
}


/* ==== FUN_00433b3b @ 00433b3b ==== */

void __cdecl FUN_00433b3b(int param_1,undefined4 param_2)

{
  (**(code **)(param_1 + 0x28))(param_1,*(int *)(param_1 + 0x14) + 1,param_2);
  return;
}


/* ==== FUN_00433b6a @ 00433b6a ==== */

void __cdecl FUN_00433b6a(int param_1,undefined4 param_2)

{
  (**(code **)(param_1 + 0x24))(param_1,*(int *)(param_1 + 0x14) + 1,param_2);
  return;
}


/* ==== FUN_00433b99 @ 00433b99 ==== */

void FUN_00433b99(void)

{
  return;
}


/* ==== FUN_00433d00 @ 00433d00 ==== */

void __cdecl FUN_00433d00(undefined *param_1)

{
  if (param_1 != (undefined *)0x0) {
    FUN_00433eac((int)param_1);
    free(param_1);
  }
  return;
}


/* ==== FUN_00433d2a @ 00433d2a ==== */

/* WARNING: Removing unreachable block (ram,0x00433d3a) */

uint * __cdecl FUN_00433d2a(uint param_1,uint param_2,uint param_3)

{
  uint *extraout_EAX;
  
  malloc(0x40);
  if (param_2 == 0) {
    *extraout_EAX = 0x32;
  }
  else {
    *extraout_EAX = param_2;
  }
  if (param_3 == 0) {
    extraout_EAX[0xf] = (uint)FUN_00434279;
  }
  else {
    extraout_EAX[0xf] = param_3;
  }
  extraout_EAX[1] = param_1;
  extraout_EAX[2] = 0;
  extraout_EAX[4] = 0xffffffff;
  extraout_EAX[5] = 0xffffffff;
  extraout_EAX[3] = 0;
  extraout_EAX[7] = 0;
  extraout_EAX[0xe] = (uint)FUN_00433e2a;
  extraout_EAX[8] = (uint)FUN_004341e2;
  extraout_EAX[9] = (uint)FUN_00434196;
  extraout_EAX[10] = (uint)FUN_00434130;
  extraout_EAX[0xc] = (uint)FUN_0043424a;
  extraout_EAX[0xd] = (uint)FUN_0043421b;
  extraout_EAX[0xb] = (uint)FUN_00433f4c;
  FUN_00433f98(extraout_EAX,extraout_EAX[1]);
  return extraout_EAX;
}


/* ==== FUN_00433e2a @ 00433e2a ==== */

void FUN_00433e2a(void)

{
  undefined4 *in_stack_00000004;
  
  printf(s__________Dumping_Array_Informati_0045b344);
  printf(s_1__array_size____d_0045b374,in_stack_00000004[2]);
  printf(s_2__blocksz____d_0045b38c,*in_stack_00000004);
  printf(s_3__max_index____d_0045b3a4,in_stack_00000004[4]);
  printf(s_4__last_index____d_0045b3bc,in_stack_00000004[5]);
  printf(s_5__remove____d_0045b3d4,in_stack_00000004[3]);
  printf(s__________End_Dumping_____________0045b3ec);
  return;
}


/* ==== FUN_00433eac @ 00433eac ==== */

void __cdecl FUN_00433eac(int param_1)

{
  undefined4 local_8;
  
  if (*(int *)(param_1 + 0xc) == 1) {
    for (local_8 = 0; local_8 <= *(int *)(param_1 + 0x10); local_8 = local_8 + 1) {
      if (*(int *)(*(int *)(param_1 + 0x18) + local_8 * 4) == 1) {
        (**(code **)(param_1 + 0x3c))(*(undefined4 *)(*(int *)(param_1 + 0x1c) + local_8 * 4));
      }
    }
  }
  if (*(int *)(param_1 + 0x1c) != 0) {
    free(*(void **)(param_1 + 0x1c));
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  if (*(int *)(param_1 + 0x18) != 0) {
    free(*(void **)(param_1 + 0x18));
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  return;
}


/* ==== FUN_00433f4c @ 00433f4c ==== */

void __cdecl FUN_00433f4c(uint *param_1)

{
  FUN_00433eac((int)param_1);
  param_1[2] = 0;
  param_1[4] = 0xffffffff;
  param_1[5] = 0xffffffff;
  param_1[3] = 0;
  FUN_00433f98(param_1,param_1[1]);
  return;
}


/* ==== FUN_00433f98 @ 00433f98 ==== */

void __cdecl FUN_00433f98(uint *param_1,uint param_2)

{
  uint extraout_EAX;
  uint extraout_EAX_00;
  uint extraout_EAX_01;
  uint extraout_EAX_02;
  uint size;
  int iVar1;
  uint local_18;
  uint local_c;
  uint local_8;
  
  if (((int)param_2 < 1) || (param_1[7] != 0)) {
    iVar1 = (param_2 + 1) / *param_1 + 1;
    local_8 = iVar1 * *param_1;
  }
  else {
    iVar1 = 1;
    local_8 = param_2;
  }
  size = local_8 * 4;
  if (param_1[7] == 0) {
    malloc(size);
    malloc(local_8 << 2);
    local_18 = extraout_EAX_00;
    local_c = extraout_EAX;
  }
  else {
    realloc((void *)param_1[7],size);
    realloc((void *)param_1[6],local_8 << 2);
    local_18 = extraout_EAX_02;
    local_c = extraout_EAX_01;
  }
  if ((local_c == 0) || (local_18 == 0)) {
    fprintf(&DAT_0045d670,s_Cannot_alloc_array_0045b41c,iVar1);
    _assert(&DAT_0045b444,s_symtableInfArray_c_0045b430,299);
    exit(1);
  }
  else {
    param_1[7] = local_c;
    param_1[6] = local_18;
    memset((void *)(param_1[7] + param_1[2] * 4),0,size + param_1[2] * -4);
    memset((void *)(param_1[6] + param_1[2] * 4),0,local_8 - param_1[2]);
  }
  param_1[2] = local_8;
  return;
}


/* ==== FUN_00434130 @ 00434130 ==== */

void __cdecl FUN_00434130(uint *param_1,uint param_2,undefined4 param_3)

{
  if (param_1[2] <= param_2) {
    FUN_00433f98(param_1,param_2);
  }
  *(undefined4 *)(param_1[7] + param_2 * 4) = param_3;
  param_1[5] = param_2;
  *(undefined4 *)(param_1[6] + param_2 * 4) = 1;
  param_1[3] = 1;
  if ((int)param_1[4] < (int)param_2) {
    param_1[4] = param_2;
  }
  return;
}


/* ==== FUN_00434196 @ 00434196 ==== */

void __cdecl FUN_00434196(uint *param_1,uint param_2,undefined4 param_3)

{
  if (param_1[2] <= param_2) {
    FUN_00433f98(param_1,param_2);
  }
  *(undefined4 *)(param_1[7] + param_2 * 4) = param_3;
  param_1[5] = param_2;
  if ((int)param_1[4] < (int)param_2) {
    param_1[4] = param_2;
  }
  return;
}


/* ==== FUN_004341e2 @ 004341e2 ==== */

undefined4 __cdecl FUN_004341e2(int param_1,int param_2)

{
  if ((param_2 < 0) || (*(int *)(param_1 + 0x10) < param_2)) {
    _assert(s__index>_0______index_<__arr_>max_0045b45c,s_symtableInfArray_c_0045b448,0x18b);
  }
  return *(undefined4 *)(*(int *)(param_1 + 0x1c) + param_2 * 4);
}


/* ==== FUN_0043421b @ 0043421b ==== */

void __cdecl FUN_0043421b(int param_1,undefined4 param_2)

{
  (**(code **)(param_1 + 0x28))(param_1,*(int *)(param_1 + 0x14) + 1,param_2);
  return;
}


/* ==== FUN_0043424a @ 0043424a ==== */

void __cdecl FUN_0043424a(int param_1,undefined4 param_2)

{
  (**(code **)(param_1 + 0x24))(param_1,*(int *)(param_1 + 0x14) + 1,param_2);
  return;
}


/* ==== FUN_00434279 @ 00434279 ==== */

void FUN_00434279(void)

{
  return;
}


/* ==== FUN_004343e0 @ 004343e0 ==== */

void __cdecl FUN_004343e0(int *param_1)

{
  if (param_1 != (int *)0x0) {
    if (*param_1 != 0) {
      free((void *)*param_1);
    }
    if ((param_1[2] != 0) && (param_1[4] == 4)) {
      free((void *)param_1[2]);
    }
    free(param_1);
  }
  return;
}


/* ==== FUN_00434435 @ 00434435 ==== */

undefined4 * __cdecl
FUN_00434435(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 *extraout_EAX;
  undefined3 extraout_var;
  
  malloc(0x18);
  cVar1 = _strdup(param_1);
  *extraout_EAX = CONCAT31(extraout_var,cVar1);
  extraout_EAX[2] = param_2;
  extraout_EAX[3] = param_3;
  extraout_EAX[4] = param_4;
  return extraout_EAX;
}


/* ==== FUN_0043447d @ 0043447d ==== */

undefined4 __cdecl FUN_0043447d(int param_1,char *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  char *b;
  int iVar4;
  
  if (param_2 == (char *)0x0) {
    fprintf(&DAT_0045d670,s_Table_Search_Name_NULL_0045b4d0,0);
  }
  else {
    for (iVar4 = 0; iVar4 <= *(int *)(param_1 + 0x10); iVar4 = iVar4 + 1) {
      b = param_2;
      puVar1 = (undefined4 *)(**(code **)(param_1 + 0x20))(param_1,iVar4);
      iVar2 = strcmp((char *)*puVar1,b);
      if (iVar2 == 0) {
        uVar3 = (**(code **)(param_1 + 0x20))(param_1,iVar4);
        return uVar3;
      }
    }
  }
  return 0;
}


/* ==== FUN_00434550 @ 00434550 ==== */

void __cdecl FUN_00434550(undefined *param_1)

{
  if (param_1 != (undefined *)0x0) {
    FUN_004346fc((int)param_1);
    free(param_1);
  }
  return;
}


/* ==== FUN_0043457a @ 0043457a ==== */

/* WARNING: Removing unreachable block (ram,0x0043458a) */

uint * __cdecl FUN_0043457a(uint param_1,uint param_2,uint param_3)

{
  uint *extraout_EAX;
  
  malloc(0x40);
  if (param_2 == 0) {
    *extraout_EAX = 0x32;
  }
  else {
    *extraout_EAX = param_2;
  }
  if (param_3 == 0) {
    extraout_EAX[0xf] = (uint)FUN_00434ac9;
  }
  else {
    extraout_EAX[0xf] = param_3;
  }
  extraout_EAX[1] = param_1;
  extraout_EAX[2] = 0;
  extraout_EAX[4] = 0xffffffff;
  extraout_EAX[5] = 0xffffffff;
  extraout_EAX[3] = 0;
  extraout_EAX[7] = 0;
  extraout_EAX[0xe] = (uint)FUN_0043467a;
  extraout_EAX[8] = (uint)FUN_00434a32;
  extraout_EAX[9] = (uint)FUN_004349e6;
  extraout_EAX[10] = (uint)FUN_00434980;
  extraout_EAX[0xc] = (uint)FUN_00434a9a;
  extraout_EAX[0xd] = (uint)FUN_00434a6b;
  extraout_EAX[0xb] = (uint)FUN_0043479c;
  FUN_004347e8(extraout_EAX,extraout_EAX[1]);
  return extraout_EAX;
}


/* ==== FUN_0043467a @ 0043467a ==== */

void FUN_0043467a(void)

{
  undefined4 *in_stack_00000004;
  
  printf(s__________Dumping_Array_Informati_0045b524);
  printf(s_1__array_size____d_0045b554,in_stack_00000004[2]);
  printf(s_2__blocksz____d_0045b56c,*in_stack_00000004);
  printf(s_3__max_index____d_0045b584,in_stack_00000004[4]);
  printf(s_4__last_index____d_0045b59c,in_stack_00000004[5]);
  printf(s_5__remove____d_0045b5b4,in_stack_00000004[3]);
  printf(s__________End_Dumping_____________0045b5cc);
  return;
}


/* ==== FUN_004346fc @ 004346fc ==== */

void __cdecl FUN_004346fc(int param_1)

{
  undefined4 local_8;
  
  if (*(int *)(param_1 + 0xc) == 1) {
    for (local_8 = 0; local_8 <= *(int *)(param_1 + 0x10); local_8 = local_8 + 1) {
      if (*(int *)(*(int *)(param_1 + 0x18) + local_8 * 4) == 1) {
        (**(code **)(param_1 + 0x3c))(*(undefined4 *)(*(int *)(param_1 + 0x1c) + local_8 * 4));
      }
    }
  }
  if (*(int *)(param_1 + 0x1c) != 0) {
    free(*(void **)(param_1 + 0x1c));
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  if (*(int *)(param_1 + 0x18) != 0) {
    free(*(void **)(param_1 + 0x18));
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  return;
}


/* ==== FUN_0043479c @ 0043479c ==== */

void __cdecl FUN_0043479c(uint *param_1)

{
  FUN_004346fc((int)param_1);
  param_1[2] = 0;
  param_1[4] = 0xffffffff;
  param_1[5] = 0xffffffff;
  param_1[3] = 0;
  FUN_004347e8(param_1,param_1[1]);
  return;
}


/* ==== FUN_004347e8 @ 004347e8 ==== */

void __cdecl FUN_004347e8(uint *param_1,uint param_2)

{
  uint extraout_EAX;
  uint extraout_EAX_00;
  uint extraout_EAX_01;
  uint extraout_EAX_02;
  uint size;
  int iVar1;
  uint local_18;
  uint local_c;
  uint local_8;
  
  if (((int)param_2 < 1) || (param_1[7] != 0)) {
    iVar1 = (param_2 + 1) / *param_1 + 1;
    local_8 = iVar1 * *param_1;
  }
  else {
    iVar1 = 1;
    local_8 = param_2;
  }
  size = local_8 * 4;
  if (param_1[7] == 0) {
    malloc(size);
    malloc(local_8 << 2);
    local_18 = extraout_EAX_00;
    local_c = extraout_EAX;
  }
  else {
    realloc((void *)param_1[7],size);
    realloc((void *)param_1[6],local_8 << 2);
    local_18 = extraout_EAX_02;
    local_c = extraout_EAX_01;
  }
  if ((local_c == 0) || (local_18 == 0)) {
    fprintf(&DAT_0045d670,s_Cannot_alloc_array_0045b5fc,iVar1);
    _assert(&DAT_0045b628,s_ABI_mp_symtblInfArray_c_0045b610,299);
    exit(1);
  }
  else {
    param_1[7] = local_c;
    param_1[6] = local_18;
    memset((void *)(param_1[7] + param_1[2] * 4),0,size + param_1[2] * -4);
    memset((void *)(param_1[6] + param_1[2] * 4),0,local_8 - param_1[2]);
  }
  param_1[2] = local_8;
  return;
}


/* ==== FUN_00434980 @ 00434980 ==== */

void __cdecl FUN_00434980(uint *param_1,uint param_2,undefined4 param_3)

{
  if (param_1[2] <= param_2) {
    FUN_004347e8(param_1,param_2);
  }
  *(undefined4 *)(param_1[7] + param_2 * 4) = param_3;
  param_1[5] = param_2;
  *(undefined4 *)(param_1[6] + param_2 * 4) = 1;
  param_1[3] = 1;
  if ((int)param_1[4] < (int)param_2) {
    param_1[4] = param_2;
  }
  return;
}


/* ==== FUN_004349e6 @ 004349e6 ==== */

void __cdecl FUN_004349e6(uint *param_1,uint param_2,undefined4 param_3)

{
  if (param_1[2] <= param_2) {
    FUN_004347e8(param_1,param_2);
  }
  *(undefined4 *)(param_1[7] + param_2 * 4) = param_3;
  param_1[5] = param_2;
  if ((int)param_1[4] < (int)param_2) {
    param_1[4] = param_2;
  }
  return;
}


/* ==== FUN_00434a32 @ 00434a32 ==== */

undefined4 __cdecl FUN_00434a32(int param_1,int param_2)

{
  if ((param_2 < 0) || (*(int *)(param_1 + 0x10) < param_2)) {
    _assert(s__index>_0______index_<__arr_>max_0045b644,s_ABI_mp_symtblInfArray_c_0045b62c,0x18b);
  }
  return *(undefined4 *)(*(int *)(param_1 + 0x1c) + param_2 * 4);
}


/* ==== FUN_00434a6b @ 00434a6b ==== */

void __cdecl FUN_00434a6b(int param_1,undefined4 param_2)

{
  (**(code **)(param_1 + 0x28))(param_1,*(int *)(param_1 + 0x14) + 1,param_2);
  return;
}


/* ==== FUN_00434a9a @ 00434a9a ==== */

void __cdecl FUN_00434a9a(int param_1,undefined4 param_2)

{
  (**(code **)(param_1 + 0x24))(param_1,*(int *)(param_1 + 0x14) + 1,param_2);
  return;
}


/* ==== FUN_00434ac9 @ 00434ac9 ==== */

void FUN_00434ac9(void)

{
  return;
}


/* ==== FUN_00434c30 @ 00434c30 ==== */

void __cdecl FUN_00434c30(int *param_1)

{
  if (param_1 != (int *)0x0) {
    if (*param_1 != 0) {
      free((void *)*param_1);
      *param_1 = 0;
    }
    if (param_1[1] != 0) {
      thunk_FUN_00433620((undefined *)param_1[1]);
      param_1[1] = 0;
    }
    free(param_1);
  }
  return;
}


/* ==== FUN_00434c8f @ 00434c8f ==== */

undefined4 * __cdecl FUN_00434c8f(int param_1)

{
  char cVar1;
  undefined4 *extraout_EAX;
  undefined3 extraout_var;
  uint *puVar2;
  undefined4 local_74;
  char local_70 [100];
  int local_c;
  undefined4 *local_8;
  
  local_c = 0;
  local_8 = (undefined4 *)0x0;
  malloc(8);
  local_8 = extraout_EAX;
  sprintf(local_70,s___0lx_0045b6b8,param_1);
  if (&stack0x00000000 == (undefined1 *)0x70) {
    local_74 = 0;
  }
  else {
    cVar1 = _strdup(local_70);
    local_74 = CONCAT31(extraout_var,cVar1);
  }
  *local_8 = local_74;
  puVar2 = thunk_FUN_0043364a(10,10,0);
  local_8[1] = puVar2;
  for (local_c = 0; local_c < *(int *)(param_1 + 0x30); local_c = local_c + 1) {
    (**(code **)(local_8[1] + 0x30))
              (local_8[1],*(undefined4 *)(*(int *)(param_1 + 0x8c) + 4 + local_c * 0x20));
  }
  return local_8;
}


/* ==== FUN_00434d4d @ 00434d4d ==== */

undefined4 __cdecl FUN_00434d4d(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  char *b;
  char local_6c [100];
  int local_8;
  
  local_8 = 0;
  sprintf(local_6c,s___0lx_0045b6c0,param_2);
  if (param_1 == 0) {
    fprintf(&DAT_0045d670,s_ABI_mp_symtblInfArray_Search_Tab_0045b6c8);
  }
  else if (param_2 == 0) {
    fprintf(&DAT_0045d670,s_ABI_mp_symtblInfArray_Search_key_0045b6f4);
  }
  else {
    for (local_8 = 0; local_8 <= *(int *)(param_1 + 0x10); local_8 = local_8 + 1) {
      b = local_6c;
      puVar1 = (undefined4 *)(**(code **)(param_1 + 0x20))(param_1,local_8);
      iVar2 = strcmp((char *)*puVar1,b);
      if (iVar2 == 0) {
        uVar3 = (**(code **)(param_1 + 0x20))(param_1,local_8);
        return uVar3;
      }
    }
  }
  return 0;
}


/* ==== FUN_00434e80 @ 00434e80 ==== */

void __cdecl FUN_00434e80(undefined *param_1)

{
  if (param_1 != (undefined *)0x0) {
    FUN_0043502c((int)param_1);
    free(param_1);
  }
  return;
}


/* ==== FUN_00434eaa @ 00434eaa ==== */

/* WARNING: Removing unreachable block (ram,0x00434eba) */

uint * __cdecl FUN_00434eaa(uint param_1,uint param_2,uint param_3)

{
  uint *extraout_EAX;
  
  malloc(0x40);
  if (param_2 == 0) {
    *extraout_EAX = 0x32;
  }
  else {
    *extraout_EAX = param_2;
  }
  if (param_3 == 0) {
    extraout_EAX[0xf] = (uint)FUN_004353f9;
  }
  else {
    extraout_EAX[0xf] = param_3;
  }
  extraout_EAX[1] = param_1;
  extraout_EAX[2] = 0;
  extraout_EAX[4] = 0xffffffff;
  extraout_EAX[5] = 0xffffffff;
  extraout_EAX[3] = 0;
  extraout_EAX[7] = 0;
  extraout_EAX[0xe] = (uint)FUN_00434faa;
  extraout_EAX[8] = (uint)FUN_00435362;
  extraout_EAX[9] = (uint)FUN_00435316;
  extraout_EAX[10] = (uint)FUN_004352b0;
  extraout_EAX[0xc] = (uint)FUN_004353ca;
  extraout_EAX[0xd] = (uint)FUN_0043539b;
  extraout_EAX[0xb] = (uint)FUN_004350cc;
  FUN_00435118(extraout_EAX,extraout_EAX[1]);
  return extraout_EAX;
}


/* ==== FUN_00434faa @ 00434faa ==== */

void FUN_00434faa(void)

{
  undefined4 *in_stack_00000004;
  
  printf(s__________Dumping_Array_Informati_0045b76c);
  printf(s_1__array_size____d_0045b79c,in_stack_00000004[2]);
  printf(s_2__blocksz____d_0045b7b4,*in_stack_00000004);
  printf(s_3__max_index____d_0045b7cc,in_stack_00000004[4]);
  printf(s_4__last_index____d_0045b7e4,in_stack_00000004[5]);
  printf(s_5__remove____d_0045b7fc,in_stack_00000004[3]);
  printf(s__________End_Dumping_____________0045b814);
  return;
}


/* ==== FUN_0043502c @ 0043502c ==== */

void __cdecl FUN_0043502c(int param_1)

{
  undefined4 local_8;
  
  if (*(int *)(param_1 + 0xc) == 1) {
    for (local_8 = 0; local_8 <= *(int *)(param_1 + 0x10); local_8 = local_8 + 1) {
      if (*(int *)(*(int *)(param_1 + 0x18) + local_8 * 4) == 1) {
        (**(code **)(param_1 + 0x3c))(*(undefined4 *)(*(int *)(param_1 + 0x1c) + local_8 * 4));
      }
    }
  }
  if (*(int *)(param_1 + 0x1c) != 0) {
    free(*(void **)(param_1 + 0x1c));
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  if (*(int *)(param_1 + 0x18) != 0) {
    free(*(void **)(param_1 + 0x18));
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  return;
}


/* ==== FUN_004350cc @ 004350cc ==== */

void __cdecl FUN_004350cc(uint *param_1)

{
  FUN_0043502c((int)param_1);
  param_1[2] = 0;
  param_1[4] = 0xffffffff;
  param_1[5] = 0xffffffff;
  param_1[3] = 0;
  FUN_00435118(param_1,param_1[1]);
  return;
}


/* ==== FUN_00435118 @ 00435118 ==== */

void __cdecl FUN_00435118(uint *param_1,uint param_2)

{
  uint extraout_EAX;
  uint extraout_EAX_00;
  uint extraout_EAX_01;
  uint extraout_EAX_02;
  uint size;
  int iVar1;
  uint local_18;
  uint local_c;
  uint local_8;
  
  if (((int)param_2 < 1) || (param_1[7] != 0)) {
    iVar1 = (param_2 + 1) / *param_1 + 1;
    local_8 = iVar1 * *param_1;
  }
  else {
    iVar1 = 1;
    local_8 = param_2;
  }
  size = local_8 * 4;
  if (param_1[7] == 0) {
    malloc(size);
    malloc(local_8 << 2);
    local_18 = extraout_EAX_00;
    local_c = extraout_EAX;
  }
  else {
    realloc((void *)param_1[7],size);
    realloc((void *)param_1[6],local_8 << 2);
    local_18 = extraout_EAX_02;
    local_c = extraout_EAX_01;
  }
  if ((local_c == 0) || (local_18 == 0)) {
    fprintf(&DAT_0045d670,s_Cannot_alloc_array_0045b844,iVar1);
    _assert(&DAT_0045b86c,s_formtableInfArray_c_0045b858,299);
    exit(1);
  }
  else {
    param_1[7] = local_c;
    param_1[6] = local_18;
    memset((void *)(param_1[7] + param_1[2] * 4),0,size + param_1[2] * -4);
    memset((void *)(param_1[6] + param_1[2] * 4),0,local_8 - param_1[2]);
  }
  param_1[2] = local_8;
  return;
}


/* ==== FUN_004352b0 @ 004352b0 ==== */

void __cdecl FUN_004352b0(uint *param_1,uint param_2,undefined4 param_3)

{
  if (param_1[2] <= param_2) {
    FUN_00435118(param_1,param_2);
  }
  *(undefined4 *)(param_1[7] + param_2 * 4) = param_3;
  param_1[5] = param_2;
  *(undefined4 *)(param_1[6] + param_2 * 4) = 1;
  param_1[3] = 1;
  if ((int)param_1[4] < (int)param_2) {
    param_1[4] = param_2;
  }
  return;
}


/* ==== FUN_00435316 @ 00435316 ==== */

void __cdecl FUN_00435316(uint *param_1,uint param_2,undefined4 param_3)

{
  if (param_1[2] <= param_2) {
    FUN_00435118(param_1,param_2);
  }
  *(undefined4 *)(param_1[7] + param_2 * 4) = param_3;
  param_1[5] = param_2;
  if ((int)param_1[4] < (int)param_2) {
    param_1[4] = param_2;
  }
  return;
}


/* ==== FUN_00435362 @ 00435362 ==== */

undefined4 __cdecl FUN_00435362(int param_1,int param_2)

{
  if ((param_2 < 0) || (*(int *)(param_1 + 0x10) < param_2)) {
    _assert(s__index>_0______index_<__arr_>max_0045b884,s_formtableInfArray_c_0045b870,0x18b);
  }
  return *(undefined4 *)(*(int *)(param_1 + 0x1c) + param_2 * 4);
}


/* ==== FUN_0043539b @ 0043539b ==== */

void __cdecl FUN_0043539b(int param_1,undefined4 param_2)

{
  (**(code **)(param_1 + 0x28))(param_1,*(int *)(param_1 + 0x14) + 1,param_2);
  return;
}


/* ==== FUN_004353ca @ 004353ca ==== */

void __cdecl FUN_004353ca(int param_1,undefined4 param_2)

{
  (**(code **)(param_1 + 0x24))(param_1,*(int *)(param_1 + 0x14) + 1,param_2);
  return;
}


/* ==== FUN_004353f9 @ 004353f9 ==== */

void FUN_004353f9(void)

{
  return;
}


/* ==== FUN_00435560 @ 00435560 ==== */

void __cdecl FUN_00435560(int *param_1)

{
  if (param_1 != (int *)0x0) {
    if (*param_1 != 0) {
      free((void *)*param_1);
      *param_1 = 0;
    }
    free(param_1);
  }
  return;
}


/* ==== FUN_0043559d @ 0043559d ==== */

undefined4 * __cdecl FUN_0043559d(char *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 *extraout_EAX;
  undefined3 extraout_var;
  
  malloc(8);
  cVar1 = _strdup(param_1);
  *extraout_EAX = CONCAT31(extraout_var,cVar1);
  extraout_EAX[1] = param_2;
  return extraout_EAX;
}


/* ==== FUN_004355d6 @ 004355d6 ==== */

undefined4 __cdecl FUN_004355d6(int param_1,char *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  char *b;
  int iVar4;
  
  if (param_2 == (char *)0x0) {
    fprintf(&DAT_0045d670,s_Table_Search_Name_NULL_0045b8f8,0);
  }
  else {
    for (iVar4 = 0; iVar4 <= *(int *)(param_1 + 0x10); iVar4 = iVar4 + 1) {
      b = param_2;
      puVar1 = (undefined4 *)(**(code **)(param_1 + 0x20))(param_1,iVar4);
      iVar2 = strcmp((char *)*puVar1,b);
      if (iVar2 == 0) {
        uVar3 = (**(code **)(param_1 + 0x20))(param_1,iVar4);
        return uVar3;
      }
    }
  }
  return 0;
}


/* ==== FUN_004356a0 @ 004356a0 ==== */

int __cdecl FUN_004356a0(int param_1,int param_2)

{
  return param_1 + param_2;
}


/* ==== FUN_004356ab @ 004356ab ==== */

int __cdecl FUN_004356ab(int param_1,int param_2)

{
  return param_1 - param_2;
}


/* ==== FUN_004356b6 @ 004356b6 ==== */

int __cdecl FUN_004356b6(int param_1,int param_2)

{
  return param_1 * param_2;
}


/* ==== FUN_004356c2 @ 004356c2 ==== */

int __cdecl FUN_004356c2(int param_1,int param_2)

{
  int iVar1;
  
  if (param_2 == 0) {
    thunk_FUN_0043a408(s_Divide_by_Zero_0045b914);
    iVar1 = 0;
  }
  else {
    iVar1 = param_1 / param_2;
  }
  return iVar1;
}


/* ==== FUN_004356e5 @ 004356e5 ==== */

int __cdecl FUN_004356e5(int param_1,int param_2)

{
  int iVar1;
  
  if (param_2 == 0) {
    thunk_FUN_0043a408(s_Divide_by_Zero_0045b924);
    iVar1 = 0;
  }
  else {
    iVar1 = param_1 % param_2;
  }
  return iVar1;
}


/* ==== FUN_0043570a @ 0043570a ==== */

undefined8 __cdecl FUN_0043570a(uint param_1,int param_2,uint param_3,int param_4)

{
  return CONCAT44(param_2 + param_4 + (uint)CARRY4(param_1,param_3),param_1 + param_3);
}


/* ==== FUN_0043571b @ 0043571b ==== */

undefined8 __cdecl FUN_0043571b(uint param_1,int param_2,uint param_3,int param_4)

{
  return CONCAT44((param_2 - param_4) - (uint)(param_1 < param_3),param_1 - param_3);
}


/* ==== FUN_0043572c @ 0043572c ==== */

longlong __cdecl FUN_0043572c(uint param_1,int param_2,uint param_3,int param_4)

{
  longlong lVar1;
  
  lVar1 = _allmul(CONCAT44(param_2,param_1),CONCAT44(param_4,param_3));
  return lVar1;
}


/* ==== FUN_00435746 @ 00435746 ==== */

longlong __cdecl FUN_00435746(uint param_1,uint param_2,uint param_3,uint param_4)

{
  longlong lVar1;
  
  if (param_3 == 0 && param_4 == 0) {
    thunk_FUN_0043a408(s_Divide_by_Zero_0045b934);
    lVar1 = 0;
  }
  else {
    lVar1 = _alldiv(CONCAT44(param_2,param_1),CONCAT44(param_4,param_3));
  }
  return lVar1;
}


/* ==== FUN_0043577d @ 0043577d ==== */

longlong __cdecl FUN_0043577d(uint param_1,uint param_2,uint param_3,uint param_4)

{
  longlong lVar1;
  
  if (param_3 == 0 && param_4 == 0) {
    thunk_FUN_0043a408(s_Divide_by_Zero_0045b944);
    lVar1 = 0;
  }
  else {
    lVar1 = _allrem(CONCAT44(param_2,param_1),CONCAT44(param_4,param_3));
  }
  return lVar1;
}


/* ==== FUN_004357b4 @ 004357b4 ==== */

uint __cdecl FUN_004357b4(uint param_1,byte param_2)

{
  return param_1 >> (param_2 & 0x1f);
}


/* ==== FUN_004357c1 @ 004357c1 ==== */

int __cdecl FUN_004357c1(int param_1,byte param_2)

{
  return param_1 << (param_2 & 0x1f);
}


/* ==== FUN_004357ce @ 004357ce ==== */

uint __cdecl FUN_004357ce(uint param_1)

{
  return ~param_1;
}


/* ==== FUN_004357d8 @ 004357d8 ==== */

int __cdecl FUN_004357d8(int param_1)

{
  return -param_1;
}


/* ==== FUN_004357e2 @ 004357e2 ==== */

bool __cdecl FUN_004357e2(int param_1)

{
  return param_1 == 0;
}


/* ==== FUN_004357f0 @ 004357f0 ==== */

undefined4 __cdecl FUN_004357f0(int param_1,int param_2)

{
  undefined4 local_8;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    local_8 = 0;
  }
  else {
    local_8 = 1;
  }
  return local_8;
}


/* ==== FUN_00435817 @ 00435817 ==== */

undefined4 __cdecl FUN_00435817(int param_1,int param_2)

{
  undefined4 local_8;
  
  if ((param_1 == 0) && (param_2 == 0)) {
    local_8 = 0;
  }
  else {
    local_8 = 1;
  }
  return local_8;
}


/* ==== FUN_0043583e @ 0043583e ==== */

bool __cdecl FUN_0043583e(int param_1,int param_2)

{
  return param_2 < param_1;
}


/* ==== FUN_00435850 @ 00435850 ==== */

bool __cdecl FUN_00435850(int param_1,int param_2)

{
  return param_2 <= param_1;
}


/* ==== FUN_00435862 @ 00435862 ==== */

bool __cdecl FUN_00435862(int param_1,int param_2)

{
  return param_1 < param_2;
}


/* ==== FUN_00435874 @ 00435874 ==== */

bool __cdecl FUN_00435874(int param_1,int param_2)

{
  return param_1 <= param_2;
}


/* ==== FUN_00435886 @ 00435886 ==== */

bool __cdecl FUN_00435886(int param_1,int param_2)

{
  return param_1 == param_2;
}


/* ==== FUN_00435898 @ 00435898 ==== */

bool __cdecl FUN_00435898(int param_1,int param_2)

{
  return param_1 != param_2;
}


/* ==== FUN_004358aa @ 004358aa ==== */

uint __cdecl FUN_004358aa(uint param_1,uint param_2)

{
  return param_1 & param_2;
}


/* ==== FUN_004358b5 @ 004358b5 ==== */

uint __cdecl FUN_004358b5(uint param_1,uint param_2)

{
  return param_1 | param_2;
}


/* ==== FUN_004358c0 @ 004358c0 ==== */

uint __cdecl FUN_004358c0(uint param_1,uint param_2)

{
  return param_1 ^ param_2;
}


/* ==== FUN_004358cb @ 004358cb ==== */

undefined4 __cdecl FUN_004358cb(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 local_8;
  
  if (param_1 == 0) {
    local_8 = param_3;
  }
  else {
    local_8 = param_2;
  }
  return local_8;
}


/* ==== FUN_004358ea @ 004358ea ==== */

longlong __cdecl
FUN_004358ea(int param_1,char *param_2,undefined4 param_3,uint param_4,uint param_5)

{
  longlong lVar1;
  undefined4 *local_10;
  undefined8 local_c;
  
  local_c = 0;
  local_10 = (undefined4 *)thunk_FUN_0043447d(param_1,param_2);
  if (local_10 == (undefined4 *)0x0) {
    local_10 = thunk_FUN_00434435(param_2,0,0,3);
    (**(code **)(param_1 + 0x34))(param_1,local_10);
  }
  switch(param_3) {
  case 0x3d:
    local_c = CONCAT44(param_5,param_4);
    local_10[2] = param_4;
    local_10[3] = param_5;
    break;
  default:
    fprintf(&DAT_0045d670,s_Not_A_Recognized_Assign_Operator_0045b954);
    exit(1);
    break;
  case 0x101:
    lVar1 = thunk_FUN_0043570a(local_10[2],local_10[3],param_4,param_5);
    local_c._0_4_ = (undefined4)lVar1;
    local_10[2] = (undefined4)local_c;
    local_c._4_4_ = (undefined4)((ulonglong)lVar1 >> 0x20);
    local_10[3] = local_c._4_4_;
    local_c = lVar1;
    break;
  case 0x102:
    lVar1 = thunk_FUN_0043571b(local_10[2],local_10[3],param_4,param_5);
    local_c._0_4_ = (undefined4)lVar1;
    local_10[2] = (undefined4)local_c;
    local_c._4_4_ = (undefined4)((ulonglong)lVar1 >> 0x20);
    local_10[3] = local_c._4_4_;
    local_c = lVar1;
    break;
  case 0x103:
    lVar1 = thunk_FUN_0043572c(local_10[2],local_10[3],param_4,param_5);
    local_c._0_4_ = (undefined4)lVar1;
    local_10[2] = (undefined4)local_c;
    local_c._4_4_ = (undefined4)((ulonglong)lVar1 >> 0x20);
    local_10[3] = local_c._4_4_;
    local_c = lVar1;
    break;
  case 0x104:
    lVar1 = thunk_FUN_00435746(local_10[2],local_10[3],param_4,param_5);
    local_c._0_4_ = (undefined4)lVar1;
    local_10[2] = (undefined4)local_c;
    local_c._4_4_ = (undefined4)((ulonglong)lVar1 >> 0x20);
    local_10[3] = local_c._4_4_;
    local_c = lVar1;
    break;
  case 0x105:
    lVar1 = thunk_FUN_0043577d(local_10[2],local_10[3],param_4,param_5);
    local_c._0_4_ = (undefined4)lVar1;
    local_10[2] = (undefined4)local_c;
    local_c._4_4_ = (undefined4)((ulonglong)lVar1 >> 0x20);
    local_10[3] = local_c._4_4_;
    local_c = lVar1;
  }
  return local_c;
}


/* ==== FUN_00435d00 @ 00435d00 ==== */

void __cdecl FUN_00435d00(int *param_1)

{
  if (*param_1 != 0) {
    free((void *)*param_1);
  }
  if (param_1 != (int *)0x0) {
    free(param_1);
  }
  return;
}


/* ==== FUN_00435d2d @ 00435d2d ==== */

undefined4 * __cdecl FUN_00435d2d(undefined4 param_1,undefined4 param_2)

{
  undefined4 *extraout_EAX;
  
  malloc(0x70);
  *extraout_EAX = 0;
  extraout_EAX[1] = 0;
  extraout_EAX[2] = param_1;
  extraout_EAX[3] = 0xffffffff;
  extraout_EAX[4] = 0;
  *(undefined1 *)(extraout_EAX + 5) = 0x20;
  extraout_EAX[6] = 0;
  *(undefined2 *)(extraout_EAX + 7) = 0xffff;
  extraout_EAX[8] = 4;
  extraout_EAX[0xd] = DAT_004612a0;
  extraout_EAX[0xe] = DAT_00461e60;
  extraout_EAX[0xf] = DAT_00461e5c;
  extraout_EAX[0x10] = DAT_00461de8;
  extraout_EAX[0x11] = DAT_004612d8;
  extraout_EAX[0x12] = DAT_00461de0;
  extraout_EAX[0x13] = DAT_00461df0;
  *(undefined1 *)(extraout_EAX + 0x14) = DAT_00461248;
  extraout_EAX[0x15] = DAT_00461d94;
  extraout_EAX[0x16] = DAT_00461de4;
  extraout_EAX[0x17] = param_2;
  extraout_EAX[0x18] = DAT_00461d90;
  extraout_EAX[0xc] = 0;
  extraout_EAX[0x19] = DAT_00461d90;
  extraout_EAX[0x1a] = DAT_00461f6c;
  *(undefined2 *)(extraout_EAX + 0x1b) = (undefined2)DAT_00461f4c;
  return extraout_EAX;
}


/* ==== FUN_00435e58 @ 00435e58 ==== */

char * __cdecl FUN_00435e58(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined4 local_10;
  undefined4 local_c;
  
  if ((param_3 < *(int *)(param_1 + 0x30)) && (-1 < param_3)) {
    if (*(int *)(*(int *)(param_1 + 0x8c) + param_3 * 0x20) == 0) {
      iVar2 = thunk_FUN_00434d4d(param_2,param_1);
      if (iVar2 == 0) {
        local_10 = (char *)0x0;
      }
      else {
        iVar3 = (**(code **)(*(int *)(iVar2 + 4) + 0x20))(*(undefined4 *)(iVar2 + 4),param_3);
        if (*(int *)(param_1 + 0x90) + iVar3 == 0) {
          local_c = (char *)0x0;
          local_10 = local_c;
        }
        else {
          iVar2 = (**(code **)(*(int *)(iVar2 + 4) + 0x20))(*(undefined4 *)(iVar2 + 4),param_3);
          cVar1 = _strdup((char *)(*(int *)(param_1 + 0x90) + iVar2));
          local_10 = (char *)CONCAT31(extraout_var,cVar1);
        }
      }
    }
    else if (*(int *)(param_1 + 0x8c) + param_3 * 0x20 == 0) {
      local_10 = (char *)0x0;
    }
    else {
      cVar1 = _strdup((char *)(*(int *)(param_1 + 0x8c) + param_3 * 0x20));
      local_10 = (char *)CONCAT31(extraout_var_00,cVar1);
    }
  }
  else {
    local_10 = (char *)0x0;
  }
  return local_10;
}


/* ==== FUN_00435f5a @ 00435f5a ==== */

uint __cdecl FUN_00435f5a(uint param_1,uint param_2,byte param_3,char param_4)

{
  uint uVar1;
  
  if (param_4 == '>') {
    uVar1 = (param_1 & param_2) >> (param_3 & 0x1f);
  }
  else if (param_4 == '<') {
    uVar1 = (param_1 & param_2) << (param_3 & 0x1f);
  }
  else {
    fprintf(&DAT_0045d670,s_abi_mask_then_shift_shift_direct_0045b98c);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_00435f9f @ 00435f9f ==== */

int __cdecl FUN_00435f9f(short param_1,short param_2)

{
  int iVar1;
  undefined4 local_c;
  undefined2 local_8;
  
  local_c = 0;
  if ((param_1 < 0) || (param_2 < 0)) {
    iVar1 = 0;
  }
  else {
    for (local_8 = 0; (int)local_8 <= (int)param_2 - (int)param_1; local_8 = local_8 + 1) {
      local_c = local_c << 1 | 1;
    }
    iVar1 = local_c << ((byte)param_1 & 0x1f);
  }
  return iVar1;
}


/* ==== FUN_00436012 @ 00436012 ==== */

uint __cdecl FUN_00436012(uint param_1,short param_2)

{
  uint uVar1;
  undefined4 local_8;
  
  uVar1 = thunk_FUN_00435f9f(0x1f,0x1f);
  if ((int)(param_1 & uVar1) < 0) {
    local_8 = thunk_FUN_00435f9f(0x20 - param_2,0x1f);
    local_8 = param_1 >> ((byte)param_2 & 0x1f) | local_8;
  }
  else {
    local_8 = param_1 >> ((byte)param_2 & 0x1f);
  }
  return local_8;
}


/* ==== FUN_00436090 @ 00436090 ==== */

void __cdecl FUN_00436090(undefined4 param_1,undefined4 param_2,int param_3)

{
  char local_208 [516];
  
  local_208[0] = '\0';
  if (param_3 == 0) {
    sprintf(local_208,s__s_at_Location__s_0045b9bc,param_1,param_2);
  }
  else {
    sprintf(local_208,s__s_at_Location__s__last_referenc_0045b9d0,param_1,param_2,
            *(undefined4 *)param_3,*(undefined4 *)(param_3 + 4),*(undefined4 *)(param_3 + 0xc));
  }
  thunk_FUN_00409a25(local_208);
  return;
}


/* ==== FUN_00436210 @ 00436210 ==== */

void __cdecl FUN_00436210(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = thunk_FUN_0043559d(s_F11W1_0045ba30,FUN_00436d0a);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F11W2_0045ba38,FUN_00436d6e);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F11W3_0045ba40,FUN_00436d97);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(&DAT_0045ba48,FUN_004368cd);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(&DAT_0045ba50,FUN_004368a4);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(&DAT_0045ba58,FUN_0043687e);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F13W1_0045ba60,FUN_00436e01);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F13W2_0045ba68,FUN_00436e38);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F14W1_0045ba70,FUN_00436e65);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F14W2_0045ba78,FUN_00436e9a);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F12W1_0045ba80,FUN_00436dcc);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F10W1_0045ba88,FUN_00436cac);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F10W2_0045ba90,FUN_00436ce1);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(&DAT_0045ba98,FUN_00436c25);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F9W2O1_0045baa0,FUN_00436c77);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F9W2O2_0045baa8,FUN_00436c4e);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(&DAT_0045bab0,FUN_00436bc7);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(&DAT_0045bab8,FUN_00436bfc);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F5W1O1_0045bac0,FUN_00436a4f);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F5W1O2_0045bac8,FUN_00436a84);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F5W2O2_0045bad0,FUN_00436ab9);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F5W3O1_0045bad8,FUN_00436ae2);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F4W1O1_0045bae0,FUN_0043698d);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F4W1O2_0045bae8,FUN_004369c4);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F4W2O2_0045baf0,FUN_004369f9);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F4W3O1_0045baf8,FUN_00436a22);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F6W1O1_0045bb00,FUN_00436b0b);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F6W1O2_0045bb08,FUN_00436b40);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F6W2O2_0045bb10,FUN_00436b75);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F6W3O1_0045bb18,FUN_00436b9e);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(&DAT_0045bb20,FUN_0043692f);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(&DAT_0045bb28,FUN_00436964);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F16W1O1_0045bb30,FUN_00436f26);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F16W1O2_0045bb38,FUN_00436f5b);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F16W2O1_0045bb40,FUN_00436fb2);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F18W1O1_0045bb48,FUN_00437096);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F18W1O2_0045bb50,FUN_004370cb);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F18W2O1_0045bb58,FUN_00437122);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F23W1_0045bb60,FUN_00437427);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F17W1O1_0045bb68,FUN_00436fdb);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F17W1O2_0045bb70,FUN_00437012);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F17W2O1_0045bb78,FUN_00437069);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F20W1_0045bb80,FUN_0043728f);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F21W1_0045bb88,FUN_004372e3);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F19W1_0045bb90,FUN_0043714b);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F19W2_0045bb98,FUN_00437202);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F22W1_0045bba0,FUN_00437337);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F22W2_0045bba8,FUN_0043739a);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(s_F15W1_0045bbb0,FUN_00436ec3);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  puVar1 = thunk_FUN_0043559d(&DAT_0045bbb8,FUN_00436855);
  (**(code **)(param_1 + 0x34))(param_1,puVar1);
  return;
}


/* ==== FUN_00436855 @ 00436855 ==== */

uint __cdecl FUN_00436855(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,10);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_0043687e @ 0043687e ==== */

uint FUN_0043687e(void)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,0xd);
  return uVar1 & 0xffff;
}


/* ==== FUN_004368a4 @ 004368a4 ==== */

uint __cdecl FUN_004368a4(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,0xc);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_004368cd @ 004368cd ==== */

uint __cdecl FUN_004368cd(int param_1)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  char cVar4;
  
  cVar4 = '>';
  bVar3 = 8;
  uVar1 = thunk_FUN_00435f9f(0xd,0xf);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar3,cVar4);
  cVar4 = '>';
  bVar3 = 0xb;
  uVar2 = thunk_FUN_00435f9f(0xe,0xf);
  uVar2 = thunk_FUN_00435f5a(0xffff,uVar2,bVar3,cVar4);
  return uVar2 | uVar1;
}


/* ==== FUN_0043692f @ 0043692f ==== */

uint __cdecl FUN_0043692f(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 8;
  uVar1 = thunk_FUN_00435f9f(0xd,0xf);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_00436964 @ 00436964 ==== */

uint __cdecl FUN_00436964(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,0xc);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_0043698d @ 0043698d ==== */

uint __cdecl FUN_0043698d(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 0xb;
  uVar1 = thunk_FUN_00435f9f(0xe,0xf);
  uVar1 = thunk_FUN_00435f5a(~*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_004369c4 @ 004369c4 ==== */

uint __cdecl FUN_004369c4(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 8;
  uVar1 = thunk_FUN_00435f9f(0xd,0xf);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_004369f9 @ 004369f9 ==== */

uint __cdecl FUN_004369f9(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,0xc);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_00436a22 @ 00436a22 ==== */

uint __cdecl FUN_00436a22(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(param_1 + 0x10);
  uVar2 = thunk_FUN_00435f9f(0,0xd);
  return ~uVar1 & uVar2;
}


/* ==== FUN_00436a4f @ 00436a4f ==== */

uint __cdecl FUN_00436a4f(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 0xb;
  uVar1 = thunk_FUN_00435f9f(0xe,0xf);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_00436a84 @ 00436a84 ==== */

uint __cdecl FUN_00436a84(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 8;
  uVar1 = thunk_FUN_00435f9f(0xd,0xf);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_00436ab9 @ 00436ab9 ==== */

uint __cdecl FUN_00436ab9(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,0xc);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_00436ae2 @ 00436ae2 ==== */

uint __cdecl FUN_00436ae2(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,0xd);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_00436b0b @ 00436b0b ==== */

uint __cdecl FUN_00436b0b(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 0xb;
  uVar1 = thunk_FUN_00435f9f(0xe,0xf);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_00436b40 @ 00436b40 ==== */

uint __cdecl FUN_00436b40(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 8;
  uVar1 = thunk_FUN_00435f9f(0xd,0xf);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_00436b75 @ 00436b75 ==== */

uint __cdecl FUN_00436b75(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,0xc);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_00436b9e @ 00436b9e ==== */

uint __cdecl FUN_00436b9e(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,0xd);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_00436bc7 @ 00436bc7 ==== */

uint __cdecl FUN_00436bc7(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 8;
  uVar1 = thunk_FUN_00435f9f(0xd,0xf);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_00436bfc @ 00436bfc ==== */

uint __cdecl FUN_00436bfc(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,0xc);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_00436c25 @ 00436c25 ==== */

uint __cdecl FUN_00436c25(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,6);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_00436c4e @ 00436c4e ==== */

uint __cdecl FUN_00436c4e(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,5);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_00436c77 @ 00436c77 ==== */

uint __cdecl FUN_00436c77(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '<';
  bVar2 = 6;
  uVar1 = thunk_FUN_00435f9f(0,5);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_00436cac @ 00436cac ==== */

uint __cdecl FUN_00436cac(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 8;
  uVar1 = thunk_FUN_00435f9f(0xd,0xe);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_00436ce1 @ 00436ce1 ==== */

uint __cdecl FUN_00436ce1(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,0xc);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_00436d0a @ 00436d0a ==== */

uint __cdecl FUN_00436d0a(int param_1)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  char cVar4;
  
  cVar4 = '>';
  bVar3 = 0x1b;
  uVar1 = thunk_FUN_00435f9f(0x1e,0x1f);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar3,cVar4);
  cVar4 = '>';
  bVar3 = 8;
  uVar2 = thunk_FUN_00435f9f(0xd,0xf);
  uVar2 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar2,bVar3,cVar4);
  return uVar1 | uVar2;
}


/* ==== FUN_00436d6e @ 00436d6e ==== */

uint __cdecl FUN_00436d6e(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,0xc);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_00436d97 @ 00436d97 ==== */

uint __cdecl FUN_00436d97(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 0x10;
  uVar1 = thunk_FUN_00435f9f(0x10,0x1d);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_00436dcc @ 00436dcc ==== */

uint __cdecl FUN_00436dcc(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 0;
  uVar1 = thunk_FUN_00435f9f(0,4);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_00436e01 @ 00436e01 ==== */

uint __cdecl FUN_00436e01(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 8;
  uVar1 = thunk_FUN_00435f9f(0xd,0xf);
  uVar1 = thunk_FUN_00435f5a(~*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_00436e38 @ 00436e38 ==== */

uint __cdecl FUN_00436e38(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(param_1 + 0x10);
  uVar2 = thunk_FUN_00435f9f(0,0xc);
  return ~uVar1 & uVar2;
}


/* ==== FUN_00436e65 @ 00436e65 ==== */

uint __cdecl FUN_00436e65(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 8;
  uVar1 = thunk_FUN_00435f9f(0xd,0xf);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_00436e9a @ 00436e9a ==== */

uint __cdecl FUN_00436e9a(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,0xc);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_00436ec3 @ 00436ec3 ==== */

uint __cdecl FUN_00436ec3(int param_1)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  char cVar4;
  
  uVar1 = thunk_FUN_00437fc0(*(uint *)(param_1 + 0x10),*(char *)(param_1 + 0x14),
                             (short)*(undefined4 *)(param_1 + 0x18),*(short *)(param_1 + 0x1c));
  cVar4 = '<';
  bVar3 = 1;
  uVar2 = thunk_FUN_00435f9f(0,7);
  uVar1 = thunk_FUN_00435f5a(uVar1,uVar2,bVar3,cVar4);
  return uVar1;
}


/* ==== FUN_00436f26 @ 00436f26 ==== */

uint __cdecl FUN_00436f26(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 8;
  uVar1 = thunk_FUN_00435f9f(0xd,0xf);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_00436f5b @ 00436f5b ==== */

uint __cdecl FUN_00436f5b(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = thunk_FUN_00437fc0(*(uint *)(param_1 + 0x10),*(char *)(param_1 + 0x14),
                             (short)*(undefined4 *)(param_1 + 0x18),*(short *)(param_1 + 0x1c));
  uVar2 = thunk_FUN_00435f9f(0,4);
  return uVar1 & uVar2;
}


/* ==== FUN_00436fb2 @ 00436fb2 ==== */

uint __cdecl FUN_00436fb2(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,0xc);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_00436fdb @ 00436fdb ==== */

uint __cdecl FUN_00436fdb(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 8;
  uVar1 = thunk_FUN_00435f9f(0xd,0xf);
  uVar1 = thunk_FUN_00435f5a(~*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_00437012 @ 00437012 ==== */

uint __cdecl FUN_00437012(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = thunk_FUN_00437fc0(*(uint *)(param_1 + 0x10),*(char *)(param_1 + 0x14),
                             (short)*(undefined4 *)(param_1 + 0x18),*(short *)(param_1 + 0x1c));
  uVar2 = thunk_FUN_00435f9f(0,4);
  return uVar1 & uVar2;
}


/* ==== FUN_00437069 @ 00437069 ==== */

uint __cdecl FUN_00437069(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(param_1 + 0x10);
  uVar2 = thunk_FUN_00435f9f(0,0xc);
  return ~uVar1 & uVar2;
}


/* ==== FUN_00437096 @ 00437096 ==== */

uint __cdecl FUN_00437096(int param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = '>';
  bVar2 = 8;
  uVar1 = thunk_FUN_00435f9f(0xd,0xf);
  uVar1 = thunk_FUN_00435f5a(*(uint *)(param_1 + 0x10),uVar1,bVar2,cVar3);
  return uVar1;
}


/* ==== FUN_004370cb @ 004370cb ==== */

uint __cdecl FUN_004370cb(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = thunk_FUN_00437fc0(*(uint *)(param_1 + 0x10),*(char *)(param_1 + 0x14),
                             (short)*(undefined4 *)(param_1 + 0x18),*(short *)(param_1 + 0x1c));
  uVar2 = thunk_FUN_00435f9f(0,4);
  return uVar1 & uVar2;
}


/* ==== FUN_00437122 @ 00437122 ==== */

uint __cdecl FUN_00437122(int param_1)

{
  uint uVar1;
  
  uVar1 = thunk_FUN_00435f9f(0,0xc);
  return *(uint *)(param_1 + 0x10) & uVar1;
}


/* ==== FUN_0043714b @ 0043714b ==== */

uint __cdecl FUN_0043714b(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  char cVar6;
  
  uVar1 = thunk_FUN_00437fc0(*(uint *)(param_1 + 0x10),*(char *)(param_1 + 0x14),
                             (short)*(undefined4 *)(param_1 + 0x18),*(short *)(param_1 + 0x1c));
  cVar6 = '>';
  bVar5 = 8;
  uVar2 = thunk_FUN_00435f9f(0x13,0x13);
  uVar2 = thunk_FUN_00435f5a(uVar1,uVar2,bVar5,cVar6);
  cVar6 = '>';
  bVar5 = 0x10;
  uVar3 = thunk_FUN_00435f9f(0x10,0x12);
  uVar3 = thunk_FUN_00435f5a(uVar1,uVar3,bVar5,cVar6);
  cVar6 = '>';
  bVar5 = 7;
  uVar4 = thunk_FUN_00435f9f(0xc,0xe);
  uVar1 = thunk_FUN_00435f5a(uVar1,uVar4,bVar5,cVar6);
  return uVar2 | uVar3 | uVar1;
}


/* ==== FUN_00437202 @ 00437202 ==== */

uint __cdecl FUN_00437202(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  byte bVar4;
  char cVar5;
  
  uVar1 = thunk_FUN_00437fc0(*(uint *)(param_1 + 0x10),*(char *)(param_1 + 0x14),
                             (short)*(undefined4 *)(param_1 + 0x18),*(short *)(param_1 + 0x1c));
  cVar5 = '>';
  bVar4 = 0xf;
  uVar2 = thunk_FUN_00435f9f(0xf,0xf);
  uVar2 = thunk_FUN_00435f5a(uVar1,uVar2,bVar4,cVar5);
  cVar5 = '<';
  bVar4 = 1;
  uVar3 = thunk_FUN_00435f9f(0,0xb);
  uVar1 = thunk_FUN_00435f5a(uVar1,uVar3,bVar4,cVar5);
  return uVar2 | uVar1;
}


/* ==== FUN_0043728f @ 0043728f ==== */

uint __cdecl FUN_0043728f(int param_1)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  char cVar4;
  
  cVar4 = '>';
  bVar3 = 0;
  uVar1 = thunk_FUN_00435f9f(0,4);
  uVar2 = thunk_FUN_00437fc0(*(uint *)(param_1 + 0x10),*(char *)(param_1 + 0x14),
                             (short)*(undefined4 *)(param_1 + 0x18),*(short *)(param_1 + 0x1c));
  uVar1 = thunk_FUN_00435f5a(uVar2,uVar1,bVar3,cVar4);
  return uVar1;
}


/* ==== FUN_004372e3 @ 004372e3 ==== */

uint __cdecl FUN_004372e3(int param_1)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  char cVar4;
  
  cVar4 = '>';
  bVar3 = 0;
  uVar1 = thunk_FUN_00435f9f(0,5);
  uVar2 = thunk_FUN_00437fc0(*(uint *)(param_1 + 0x10),*(char *)(param_1 + 0x14),
                             (short)*(undefined4 *)(param_1 + 0x18),*(short *)(param_1 + 0x1c));
  uVar1 = thunk_FUN_00435f5a(uVar2,uVar1,bVar3,cVar4);
  return uVar1;
}


/* ==== FUN_00437337 @ 00437337 ==== */

uint __cdecl FUN_00437337(int param_1)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  char cVar4;
  
  uVar1 = thunk_FUN_00437fc0(*(uint *)(param_1 + 0x10),*(char *)(param_1 + 0x14),
                             (short)*(undefined4 *)(param_1 + 0x18),*(short *)(param_1 + 0x1c));
  cVar4 = '>';
  bVar3 = 7;
  uVar2 = thunk_FUN_00435f9f(0xc,0xe);
  uVar1 = thunk_FUN_00435f5a(uVar1,uVar2,bVar3,cVar4);
  return uVar1;
}


/* ==== FUN_0043739a @ 0043739a ==== */

uint __cdecl FUN_0043739a(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  byte bVar4;
  char cVar5;
  
  uVar1 = thunk_FUN_00437fc0(*(uint *)(param_1 + 0x10),*(char *)(param_1 + 0x14),
                             (short)*(undefined4 *)(param_1 + 0x18),*(short *)(param_1 + 0x1c));
  cVar5 = '>';
  bVar4 = 0xf;
  uVar2 = thunk_FUN_00435f9f(0xf,0xf);
  uVar2 = thunk_FUN_00435f5a(uVar1,uVar2,bVar4,cVar5);
  cVar5 = '<';
  bVar4 = 1;
  uVar3 = thunk_FUN_00435f9f(0,0xb);
  uVar1 = thunk_FUN_00435f5a(uVar1,uVar3,bVar4,cVar5);
  return uVar2 | uVar1;
}


/* ==== FUN_00437427 @ 00437427 ==== */

uint __cdecl FUN_00437427(int param_1)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  char cVar4;
  
  uVar1 = thunk_FUN_00437fc0(*(uint *)(param_1 + 0x10),*(char *)(param_1 + 0x14),
                             (short)*(undefined4 *)(param_1 + 0x18),*(short *)(param_1 + 0x1c));
  cVar4 = '>';
  bVar3 = 8;
  uVar2 = thunk_FUN_00435f9f(0xd,0xf);
  thunk_FUN_00435f5a(0xffff,uVar2,bVar3,cVar4);
  uVar2 = thunk_FUN_00435f9f(0,4);
  return uVar1 & uVar2;
}


/* ==== FUN_00437950 @ 00437950 ==== */

undefined4 __cdecl
FUN_00437950(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  undefined4 *puVar11;
  undefined4 uVar12;
  int iVar13;
  int local_64;
  int local_58;
  int local_3c;
  undefined4 *local_38;
  int local_30;
  int *local_1c;
  
  if (((DAT_00461fe8 < 6) && ((DAT_00461fe8 != 5 || (DAT_00461fec < 1)))) &&
     ((DAT_00461fe8 != 5 || ((DAT_00461fec != 0 || (DAT_00461ff0 < 0xb)))))) {
    bVar10 = false;
  }
  else {
    bVar10 = true;
  }
  iVar13 = *(int *)(param_1 + 0x34);
  iVar2 = *(int *)(param_1 + 0x38);
  iVar3 = *(int *)(param_1 + 0x3c);
  iVar4 = *(int *)(param_1 + 0x40);
  iVar5 = *(int *)(param_1 + 0x44);
  piVar6 = *(int **)(param_1 + 0x48);
  local_38 = *(undefined4 **)(param_1 + 0x4c);
  cVar1 = *(char *)(param_1 + 0x50);
  iVar7 = *(int *)(param_1 + 0x60);
  iVar8 = *(int *)(param_1 + 0x54);
  iVar9 = *(int *)(param_1 + 0x58);
  puVar11 = thunk_FUN_0040c91d();
  puVar11[2] = param_2;
  puVar11[4] = 0x100;
  puVar11[8] = param_3;
  uVar12 = thunk_FUN_0042fc54(puVar11[8]);
  puVar11[7] = uVar12;
  puVar11[9] = param_4;
  puVar11[0xb] = param_5;
  puVar11[0xc] = param_6;
  puVar11[0xd] = param_7;
  puVar11[0xe] = param_8;
  puVar11[0x10] = param_9;
  local_64 = iVar13;
  if (-1 < (int)puVar11[0xc]) {
    local_64 = puVar11[0xc];
  }
  if (((bVar10) && (puVar11[0xe] != 0)) || ((!bVar10 && (iVar7 != iVar8)))) {
    iVar13 = DAT_004612c8;
    if (bVar10) {
      iVar13 = iVar5 + puVar11[0xe];
    }
    puVar11[2] = puVar11[2] + *(int *)(*(int *)(iVar2 + 0x10 + iVar13 * 0x24) + 0x10);
  }
  else {
    if ((puVar11[0xd] == 0) ||
       ((*(uint *)(*(int *)(iVar3 + (DAT_004612c4 + puVar11[0xd]) * 8) + 8) & 0x20000) == 0)) {
      local_1c = piVar6;
      if (((!bVar10) ||
          (((puVar11[0xc] != iVar13 || (puVar11[7] != DAT_00461d80)) || (puVar11[9] != DAT_00461d88)
           ))) && (((bVar10 || (puVar11[7] != DAT_00461d80)) || (puVar11[9] != DAT_00461d88)))) {
        local_1c = (int *)0x0;
        for (local_30 = *(int *)(*(int *)*piVar6 + 8); local_30 != 0;
            local_30 = *(int *)(local_30 + 0x74)) {
          if ((*(int *)(local_30 + 8) == puVar11[7]) && (*(int *)(local_30 + 0x10) == puVar11[9])) {
            local_1c = *(int **)(local_30 + 0x18);
            break;
          }
        }
        local_38 = *(undefined4 **)(iVar4 + local_64 * 4);
        while ((local_38 != (undefined4 *)0x0 &&
               ((*(int *)(*(int *)*local_38 + 8) != puVar11[7] ||
                (*(int *)(*(int *)*local_38 + 0x10) != puVar11[9]))))) {
          local_38 = (undefined4 *)local_38[5];
        }
        if (local_38 == (undefined4 *)0x0) {
          thunk_FUN_0042bc50(*(uint **)**(undefined4 **)**(undefined4 **)(iVar4 + local_64 * 4),
                             local_64,puVar11 + 7,1);
          local_38 = *(undefined4 **)(iVar4 + local_64 * 4);
          while ((local_38 != (undefined4 *)0x0 &&
                 ((*(int *)(*(int *)*local_38 + 8) != puVar11[7] ||
                  (*(int *)(*(int *)*local_38 + 0x10) != puVar11[9]))))) {
            local_38 = (undefined4 *)local_38[5];
          }
        }
      }
    }
    else {
      local_1c = *(int **)(iVar3 + (DAT_004612c4 + puVar11[0xd]) * 8);
    }
    if ((local_1c == (int *)0x0) || (local_38 == (undefined4 *)0x0)) {
      thunk_FUN_004098b0(s_Section_map_lookup_failure_0045bc0c);
    }
    puVar11[2] = puVar11[2] + local_1c[4];
    if ((cVar1 == '\0') || ((local_1c[2] & 0x20000U) != 0)) {
      if ((local_1c[2] & 0x2000U) == 0) {
        local_3c = 0;
        if ((local_1c[2] & 0x20000U) != 0) {
          for (local_58 = *(int *)(*local_1c + 0x20); local_58 != 0;
              local_58 = *(int *)(local_58 + 0x44)) {
            if (*(uint *)(local_58 + 0x30) <= (uint)puVar11[2]) {
              local_3c = local_3c + *(int *)(local_58 + 0x34);
            }
          }
        }
        puVar11[2] = puVar11[2] + (local_38[3] - local_3c);
      }
      else {
        puVar11[2] = puVar11[2] - *(int *)(iVar3 + 4 + (DAT_004612c4 + puVar11[0xd]) * 8);
      }
    }
    else {
      puVar11[2] = puVar11[2] + local_38[3];
    }
  }
  if (iVar7 == iVar8) {
    puVar11[2] = puVar11[2] + *(int *)(*piVar6 + 0x58);
  }
  else {
    puVar11[2] = puVar11[2] + *(int *)(iVar2 + 0x18 + (iVar5 + puVar11[0xe]) * 0x24);
  }
  if (((iVar9 != 0) && (*(int *)(iVar9 + 0x38) != 0)) && (puVar11[0x10] != 0)) {
    puVar11[2] = puVar11[2] +
                 *(int *)(*(int *)(*(int *)(iVar9 + 0x38) + 0x28) + 0x1c +
                         (*(int *)(*(int *)(iVar9 + 0x38) + 0x10) + -1 + puVar11[0x10]) * 0x2c);
  }
  uVar12 = puVar11[2];
  thunk_FUN_0040ca80((undefined *)puVar11);
  return uVar12;
}


/* ==== FUN_00437e46 @ 00437e46 ==== */

int __cdecl FUN_00437e46(int *param_1,int param_2,int param_3)

{
  uint *p;
  int iVar1;
  undefined4 *puVar2;
  
  if (param_3 == param_1[3]) {
    iVar1 = param_1[1];
  }
  else {
    p = (uint *)thunk_FUN_00435e58(param_1[2],param_2,param_3);
    if (p == (uint *)0x0) {
      if (1 < DAT_00461294) {
        DAT_0046c400 = 0;
        sprintf(&DAT_0046c400,s_A_Symbol_is_Not_Found_at_Given_S_0045bc28,param_3);
        thunk_FUN_00436090(&DAT_0046c400,s_abi_func_sym___0045bc58,0);
      }
      param_1[1] = 0;
      param_1[3] = param_3;
      iVar1 = 0;
    }
    else {
      puVar2 = thunk_FUN_0042c8ba(p,0);
      if (puVar2 == (undefined4 *)0x0) {
        param_1[1] = 0;
        param_1[3] = param_3;
        if (p != (uint *)0x0) {
          free(p);
        }
        iVar1 = 0;
      }
      else {
        DAT_004611dc = puVar2;
        param_1[8] = puVar2[0xb];
        param_1[9] = puVar2[0xc];
        param_1[10] = puVar2[0xd];
        param_1[0xb] = puVar2[0xe];
        if (*param_1 != 0) {
          free((void *)*param_1);
        }
        *param_1 = (int)p;
        param_1[1] = 0;
        param_1[1] = param_1[1] | puVar2[3];
        param_1[1] = param_1[1] << 0x10;
        param_1[1] = param_1[1] | puVar2[4];
        param_1[3] = param_3;
        iVar1 = param_1[1];
      }
    }
  }
  return iVar1;
}


/* ==== FUN_00437fc0 @ 00437fc0 ==== */

uint __cdecl FUN_00437fc0(uint param_1,char param_2,short param_3,short param_4)

{
  uint uVar1;
  undefined4 uVar2;
  
  if (param_2 == 'n') {
    uVar1 = thunk_FUN_00435f9f(0,param_3 + -1);
    uVar1 = uVar1 & param_1;
  }
  else {
    uVar2 = thunk_FUN_00438042(param_1,param_2,param_3,param_4);
    if ((short)uVar2 == 0) {
      uVar1 = thunk_FUN_00436012(param_1,param_4);
    }
    else {
      thunk_FUN_00436090(s_Unable_to_Pack_Value_0045bc78,s_abi_func_pack_0045bc68,DAT_0046c378);
      uVar1 = 0;
    }
  }
  return uVar1;
}


/* ==== FUN_00438042 @ 00438042 ==== */

uint __cdecl FUN_00438042(uint param_1,char param_2,short param_3,short param_4)

{
  uint uVar1;
  undefined2 extraout_var;
  uint uVar2;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  
  uVar1 = thunk_FUN_00435f9f(0,param_4 + -1);
  if ((uVar1 & param_1) != 0) {
    DAT_0046c400 = 0;
    sprintf(&DAT_0046c400,s_Value___0lx_Must_be__dbit_aligne_0045bc90,param_1,(int)param_4);
    thunk_FUN_00436090(&DAT_0046c400,s_abi_func_check_0045bcb4,DAT_0046c378);
    return CONCAT22(extraout_var,1);
  }
  uVar2 = thunk_FUN_00436012(param_1,param_4);
  uVar1 = thunk_FUN_00435f9f(0,param_3 + -1);
  uVar2 = uVar2 & ~uVar1;
  if (param_2 == 's') {
    if ((uVar2 != 0) && (uVar2 != ~uVar1)) {
      DAT_0046c400 = 0;
      sprintf(&DAT_0046c400,s_Signed_Value___0lx_is_Out_of_Ran_0045bcc4,param_1);
      thunk_FUN_00436090(&DAT_0046c400,s_abi_func_check_0045bce8,DAT_0046c378);
      return CONCAT22(extraout_var_00,1);
    }
  }
  else {
    if (param_2 != 'u') {
      DAT_0046c400 = 0;
      sprintf(&DAT_0046c400,s_No_Sign_Specified__s_u__for_Chec_0045bd30,param_1);
      thunk_FUN_00436090(&DAT_0046c400,s_abi_func_check_0045bd64,DAT_0046c378);
      thunk_FUN_00436090(s_No_Sign_specified_0045bd84,s_abi_func_check_0045bd74,DAT_0046c378);
      return CONCAT22(extraout_var_02,1);
    }
    if (uVar2 != 0) {
      DAT_0046c400 = 0;
      sprintf(&DAT_0046c400,s_Unsigned_Value___0lx_is_Out_of_R_0045bcf8,param_1);
      thunk_FUN_00436090(&DAT_0046c400,s_abi_func_check_0045bd20,DAT_0046c378);
      return CONCAT22(extraout_var_01,1);
    }
  }
  return uVar2 & 0xffff0000;
}


/* ==== FUN_00438203 @ 00438203 ==== */

uint __cdecl FUN_00438203(int param_1,uint param_2)

{
  short sVar1;
  uint uVar2;
  
  if (*(short *)(param_1 + 0x6c) == 0) {
    sVar1 = 2;
  }
  else {
    sVar1 = *(short *)(param_1 + 0x6c);
  }
  if (sVar1 == 2) {
    uVar2 = thunk_FUN_00435f9f(0,7);
  }
  else {
    uVar2 = thunk_FUN_00435f9f(0,7);
  }
  return uVar2 & param_2;
}


/* ==== FUN_0043825a @ 0043825a ==== */

void __cdecl FUN_0043825a(int param_1,uint param_2)

{
  short sVar1;
  uint uVar2;
  byte bVar3;
  char cVar4;
  
  if (*(short *)(param_1 + 0x6c) == 0) {
    sVar1 = 2;
  }
  else {
    sVar1 = *(short *)(param_1 + 0x6c);
  }
  if (sVar1 == 2) {
    cVar4 = '>';
    bVar3 = 8;
    uVar2 = thunk_FUN_00435f9f(8,0xf);
    thunk_FUN_00435f5a(param_2,uVar2,bVar3,cVar4);
  }
  else {
    cVar4 = '>';
    bVar3 = 8;
    uVar2 = thunk_FUN_00435f9f(8,0xf);
    thunk_FUN_00435f5a(param_2,uVar2,bVar3,cVar4);
  }
  return;
}


/* ==== FUN_004382c9 @ 004382c9 ==== */

undefined4 __cdecl FUN_004382c9(int *param_1,undefined4 param_2,int param_3,short param_4)

{
  int iVar1;
  
  thunk_FUN_00437e46(param_1,DAT_0046c604,param_3);
  iVar1 = thunk_FUN_0042f2b0((int)param_4);
  if ((DAT_00457b7c != '\0') && (iVar1 = thunk_FUN_0043016a(param_1[8],iVar1), iVar1 == 0xa2c2a)) {
    thunk_FUN_00436090(s_Memory_Constraint_Violation__0045bdac,s_abi_func_memcheck_0045bd98,
                       (int)param_1);
    return 1;
  }
  return 0;
}


/* ==== FUN_0043833c @ 0043833c ==== */

undefined4 __cdecl FUN_0043833c(undefined4 param_1)

{
  DAT_00461314 = param_1;
  return param_1;
}


/* ==== FUN_0043834c @ 0043834c ==== */

undefined4 __cdecl FUN_0043834c(int param_1,undefined2 param_2)

{
  *(undefined2 *)(param_1 + 0x6c) = param_2;
  return 0;
}


/* ==== FUN_004385f0 @ 004385f0 ==== */

int * __cdecl FUN_004385f0(int *param_1,int *param_2,int param_3)

{
  int *piVar1;
  int local_24 [4];
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  piVar1 = FUN_00438679(local_24,param_2,param_3);
  local_14 = *piVar1;
  local_10 = piVar1[1];
  local_c = piVar1[2];
  local_8 = piVar1[3];
  if ((local_8 != 2) && (local_8 == 1)) {
    fprintf(&DAT_0045d670,s_Parser_Error___s_in_Location__s_0045be64,
            s_Can_not_Convert_to_Incompatible_D_0045be38,s_abi_lnk_extract_val_0045be24);
    thunk_FUN_00409a25(s_Can_not_Convert_to_Incompatible_D_0045be88);
  }
  *param_1 = local_14;
  param_1[1] = local_10;
  param_1[2] = local_c;
  param_1[3] = local_8;
  return param_1;
}


/* ==== FUN_00438679 @ 00438679 ==== */

int * __cdecl FUN_00438679(int *param_1,int *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int local_54 [4];
  undefined4 local_44 [4];
  undefined4 local_34 [4];
  int local_24 [4];
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (param_2[2] == param_3) {
    iVar1 = param_2[1];
    iVar2 = param_2[2];
    *param_1 = *param_2;
    param_1[1] = iVar1;
    param_1[2] = iVar2;
    param_1[3] = 0;
  }
  else {
    switch(param_3) {
    case 0:
      piVar3 = FUN_004387f2(local_44,param_2);
      local_14 = *piVar3;
      local_10 = piVar3[1];
      local_c = piVar3[2];
      local_8 = piVar3[3];
      break;
    case 1:
      piVar3 = FUN_0043891b(local_34,param_2);
      local_14 = *piVar3;
      local_10 = piVar3[1];
      local_c = piVar3[2];
      local_8 = piVar3[3];
      break;
    case 2:
      piVar3 = FUN_00438889(local_24,param_2);
      local_14 = *piVar3;
      local_10 = piVar3[1];
      local_c = piVar3[2];
      local_8 = piVar3[3];
      break;
    case 3:
      piVar3 = FUN_004389ab(local_54,param_2);
      local_14 = *piVar3;
      local_10 = piVar3[1];
      local_c = piVar3[2];
      local_8 = piVar3[3];
      break;
    default:
      local_8 = 1;
      fprintf(&DAT_0045d670,s_Parser_Error___s_in_Location__s_0045beec,
              s_Requested_Data_Type_Not_Found__0045becc,s_abi_lnk_convert_type_0045beb4);
      thunk_FUN_00409a25(s_Requested_Data_Type_Not_Found__0045bf10);
    }
    *param_1 = local_14;
    param_1[1] = local_10;
    param_1[2] = local_c;
    param_1[3] = local_8;
  }
  return param_1;
}


/* ==== FUN_004387f2 @ 004387f2 ==== */

undefined4 * __cdecl FUN_004387f2(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_14;
  undefined4 local_8;
  
  uVar1 = param_2[1];
  local_8 = 2;
  iVar2 = param_2[2];
  local_14._2_2_ = (undefined2)((uint)*param_2 >> 0x10);
  if (iVar2 == 1) {
    local_14 = CONCAT22(local_14._2_2_,*(undefined2 *)param_2);
  }
  else if (iVar2 == 2) {
    local_14 = CONCAT22(local_14._2_2_,*(undefined2 *)param_2);
  }
  else if (iVar2 == 3) {
    local_14 = CONCAT22(local_14._2_2_,*(undefined2 *)param_2);
  }
  else {
    local_8 = 1;
    local_14 = *param_2;
  }
  *param_1 = local_14;
  param_1[1] = uVar1;
  param_1[2] = 0;
  param_1[3] = local_8;
  return param_1;
}


/* ==== FUN_00438889 @ 00438889 ==== */

int * __cdecl FUN_00438889(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int local_14;
  int local_8;
  
  local_14 = *param_2;
  iVar1 = param_2[1];
  local_8 = 2;
  iVar2 = param_2[2];
  if (iVar2 == 0) {
    local_14 = (int)(short)*param_2;
  }
  else if (iVar2 == 1) {
    local_14 = *param_2;
  }
  else if (iVar2 == 3) {
    local_14 = *param_2;
  }
  else {
    local_8 = 1;
  }
  *param_1 = local_14;
  param_1[1] = iVar1;
  param_1[2] = 2;
  param_1[3] = local_8;
  return param_1;
}


/* ==== FUN_0043891b @ 0043891b ==== */

undefined4 * __cdecl FUN_0043891b(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_14;
  undefined4 local_8;
  
  local_14 = *param_2;
  uVar1 = param_2[1];
  local_8 = 2;
  iVar2 = param_2[2];
  if (iVar2 != 0) {
    if (iVar2 == 2) {
      local_14 = *param_2;
      goto LAB_0043898a;
    }
    if (iVar2 != 3) {
      local_8 = 1;
      goto LAB_0043898a;
    }
  }
  local_14 = *param_2;
LAB_0043898a:
  *param_1 = local_14;
  param_1[1] = uVar1;
  param_1[2] = 1;
  param_1[3] = local_8;
  return param_1;
}


/* ==== FUN_004389ab @ 004389ab ==== */

int * __cdecl FUN_004389ab(int *param_1,int *param_2)

{
  int iVar1;
  int local_14;
  int local_10;
  int local_8;
  
  local_14 = *param_2;
  local_10 = param_2[1];
  local_8 = 2;
  iVar1 = param_2[2];
  if (iVar1 == 0) {
    local_14 = (int)(short)*param_2;
    local_10 = local_14 >> 0x1f;
  }
  else if (iVar1 == 1) {
    local_14 = *param_2;
    local_10 = local_14 >> 0x1f;
  }
  else if (iVar1 == 2) {
    local_14 = *param_2;
    local_10 = 0;
  }
  else {
    local_8 = 1;
  }
  *param_1 = local_14;
  param_1[1] = local_10;
  param_1[2] = 3;
  param_1[3] = local_8;
  return param_1;
}


/* ==== FUN_00438b60 @ 00438b60 ==== */

void FUN_00438b60(void)

{
  char cVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  uint uVar2;
  int iVar3;
  int iVar4;
  ulong local_30;
  ulong local_2c;
  ulong local_28;
  uint local_18;
  uint local_14;
  int local_10;
  byte *local_c;
  byte *local_8;
  
  if (DAT_0045bf68 != 0) {
    DAT_0045bf68 = 0;
    if (DAT_0046ad14 == 0) {
      DAT_0046ad14 = 1;
    }
    if (DAT_0046ad18 == (undefined **)0x0) {
      DAT_0046ad18 = &PTR_DAT_0045d630;
    }
    if (DAT_0046ad1c == (undefined *)0x0) {
      DAT_0046ad1c = &DAT_0045d650;
    }
    if (DAT_0046ad0c == (int *)0x0) {
      DAT_0046ad0c = thunk_FUN_004399db((int)DAT_0046ad18,0x4000);
    }
    thunk_FUN_00439993();
  }
LAB_00438bd8:
  local_c = DAT_0046ad10;
  *DAT_0046ad10 = DAT_0046acfc;
  local_8 = DAT_0046ad10;
  local_14 = DAT_0046ad14;
LAB_00438c07:
  do {
    local_18 = (uint)(byte)(&DAT_0045c0c8)[(uint)*local_c * 4];
    if (*(short *)(&DAT_0045bf70 + local_14 * 2) != 0) {
      DAT_0046ad08 = local_14;
      DAT_0046ad04 = local_c;
    }
    while ((int)*(short *)(&DAT_0045cba0 +
                          ((int)*(short *)(&DAT_0045c5b8 + local_14 * 2) + local_18) * 2) !=
           local_14) {
      local_14 = (uint)*(short *)(&DAT_0045c720 + local_14 * 2);
      if (0xab < (int)local_14) {
        local_18 = (uint)(byte)(&DAT_0045c4c8)[local_18 * 4];
      }
    }
    local_14 = (uint)*(short *)(&DAT_0045c888 +
                               ((int)*(short *)(&DAT_0045c5b8 + local_14 * 2) + local_18) * 2);
    local_c = local_c + 1;
  } while (*(short *)(&DAT_0045c5b8 + local_14 * 2) != 0x14f);
LAB_00438cc7:
  local_10 = (int)*(short *)(&DAT_0045bf70 + local_14 * 2);
  if (local_10 == 0) {
    local_c = DAT_0046ad04;
    local_10 = (int)*(short *)(&DAT_0045bf70 + DAT_0046ad08 * 2);
  }
  DAT_0046c058 = local_8;
  DAT_0046c048 = (int)local_c - (int)local_8;
  DAT_0046acfc = *local_c;
  *local_c = 0;
  DAT_0046ad10 = local_c;
LAB_00438d29:
  switch(local_10) {
  case 0:
    goto switchD_00438d3c_caseD_0;
  case 1:
    errno = 0;
    DAT_0046b430 = strtoul((char *)DAT_0046c058,(char **)0x0,2);
    if ((errno == 0x16) && (DAT_0046b430 == 0)) {
      thunk_FUN_004335b0(DAT_0046c058,s_STRTOUL_can_not_perform_this_con_0045cebc);
    }
    if ((errno == 0x22) && (DAT_0046b430 == 0xffffffff)) {
      thunk_FUN_004335b0(DAT_0046c058,s_binary_number_is_outside_the_ran_0045cee4);
    }
    break;
  case 2:
    errno = 0;
    DAT_0046b430 = strtoul((char *)DAT_0046c058,(char **)0x0,0);
    if ((errno == 0x16) && (DAT_0046b430 == 0)) {
      thunk_FUN_004335b0(DAT_0046c058,s_STRTOUL_can_not_perform_this_con_0045cf40);
    }
    if ((errno == 0x22) && (DAT_0046b430 == 0xffffffff)) {
      thunk_FUN_004335b0(DAT_0046c058,s_hex_number_is_outside_the_range_o_0045cf68);
    }
    break;
  case 3:
    errno = 0;
    DAT_0046b430 = strtoul((char *)DAT_0046c058,(char **)0x0,0);
    if ((errno == 0x16) && (DAT_0046b430 == 0)) {
      thunk_FUN_004335b0(DAT_0046c058,s_STRTOUL_can_not_perform_this_con_0045cfc0);
    }
    if ((errno == 0x22) && (DAT_0046b430 == 0xffffffff)) {
      thunk_FUN_004335b0(DAT_0046c058,s_octal_number_is_outside_the_rang_0045cfe8);
    }
    break;
  case 4:
    errno = 0;
    DAT_0046b430 = strtoul((char *)DAT_0046c058,(char **)0x0,0);
    if ((errno == 0x16) && (DAT_0046b430 == 0)) {
      thunk_FUN_004335b0(DAT_0046c058,s_STRTOUL_can_not_perform_this_con_0045d040);
    }
    if ((errno == 0x22) && (DAT_0046b430 == 0xffffffff)) {
      thunk_FUN_004335b0(DAT_0046c058,s_decimal_number_is_outside_the_ra_0045d068);
    }
    break;
  case 5:
    if (DAT_0046c058 == (byte *)0x0) {
      local_28 = 0;
    }
    else {
      cVar1 = _strdup((char *)DAT_0046c058);
      local_28 = CONCAT31(extraout_var,cVar1);
    }
    DAT_0046b430 = local_28;
    break;
  case 6:
    break;
  case 7:
    break;
  case 8:
    break;
  case 9:
    break;
  case 10:
    break;
  case 0xb:
    break;
  case 0xc:
    break;
  case 0xd:
    break;
  case 0xe:
    break;
  case 0xf:
    break;
  case 0x10:
    break;
  case 0x11:
    break;
  case 0x12:
    break;
  case 0x13:
    break;
  case 0x14:
    break;
  case 0x15:
    break;
  case 0x16:
    break;
  case 0x17:
    break;
  case 0x18:
    break;
  case 0x19:
    break;
  case 0x1a:
    break;
  case 0x1b:
    break;
  case 0x1c:
    break;
  case 0x1d:
    break;
  case 0x1e:
    break;
  case 0x1f:
    break;
  case 0x20:
    break;
  case 0x21:
    break;
  case 0x22:
    break;
  case 0x23:
    break;
  case 0x24:
    break;
  case 0x25:
    break;
  case 0x26:
    break;
  case 0x27:
    break;
  case 0x28:
    break;
  case 0x29:
    break;
  case 0x2a:
    break;
  case 0x2b:
    break;
  case 0x2c:
    break;
  case 0x2d:
    break;
  case 0x2e:
    break;
  case 0x2f:
    if (DAT_0046c058 == (byte *)0x0) {
      local_2c = 0;
    }
    else {
      cVar1 = _strdup((char *)DAT_0046c058);
      local_2c = CONCAT31(extraout_var_00,cVar1);
    }
    DAT_0046b430 = local_2c;
    break;
  case 0x30:
    break;
  case 0x31:
    break;
  case 0x32:
    break;
  case 0x33:
    DAT_0046b430 = CONCAT31(DAT_0046b430._1_3_,*DAT_0046c058);
    break;
  case 0x34:
    DAT_0046b430 = CONCAT31(DAT_0046b430._1_3_,*DAT_0046c058);
    break;
  case 0x35:
    if (DAT_0046c058 == (byte *)0x0) {
      local_30 = 0;
    }
    else {
      cVar1 = _strdup((char *)DAT_0046c058);
      local_30 = CONCAT31(extraout_var_01,cVar1);
    }
    DAT_0046b430 = local_30;
    break;
  case 0x36:
    DAT_0045ceb8 = DAT_0045ceb8 + 1;
    goto LAB_00438bd8;
  case 0x37:
    goto LAB_00438bd8;
  case 0x38:
    break;
  case 0x39:
    fwrite(DAT_0046c058,DAT_0046c048,1,DAT_0046ad1c);
    goto LAB_00438bd8;
  case 0x3a:
    iVar4 = -1 - (int)DAT_0046c058;
    *local_c = DAT_0046acfc;
    if (DAT_0046ad0c[9] == 0) {
      DAT_0046ad00 = DAT_0046ad0c[4];
      *DAT_0046ad0c = (int)DAT_0046ad18;
      DAT_0046ad0c[9] = 1;
    }
    if ((byte *)(DAT_0046ad0c[1] + DAT_0046ad00) < DAT_0046ad10) {
      iVar3 = FUN_004394be();
      if (iVar3 == 0) {
        DAT_0046ad10 = DAT_0046c058 + (int)(local_c + iVar4);
        local_14 = FUN_00439743();
        local_c = DAT_0046ad10;
        local_8 = DAT_0046c058;
        goto LAB_00438c07;
      }
      if (iVar3 == 1) {
        DAT_0046acf8 = 0;
        iVar4 = thunk_FUN_00439dbb();
        if (iVar4 != 0) goto code_r0x00439319;
        if (DAT_0046acf8 == 0) {
          thunk_FUN_004398f9((int)DAT_0046ad18);
        }
        goto LAB_00438bd8;
      }
      if (iVar3 != 2) goto LAB_00438bd8;
      DAT_0046ad10 = (byte *)(DAT_0046ad0c[1] + DAT_0046ad00);
      local_14 = FUN_00439743();
      local_c = DAT_0046ad10;
      local_8 = DAT_0046c058;
      goto LAB_00438cc7;
    }
    DAT_0046ad10 = DAT_0046c058 + (int)(local_c + iVar4);
    local_14 = FUN_00439743();
    uVar2 = FUN_00439839(local_14);
    local_8 = DAT_0046c058;
    if (uVar2 != 0) {
      local_c = DAT_0046ad10 + 1;
      local_14 = uVar2;
      goto LAB_00438c07;
    }
    local_c = DAT_0046ad10;
    goto LAB_00438cc7;
  case 0x3b:
    break;
  default:
    FUN_00439cf9(s_fatal_flex_scanner_internal_erro_0045d0c4);
    goto LAB_00438bd8;
  }
  return;
code_r0x00439319:
  DAT_0046ad10 = DAT_0046c058;
  local_10 = (int)(DAT_0046ad14 - 1) / 2 + 0x3b;
  goto LAB_00438d29;
switchD_00438d3c_caseD_0:
  *local_c = DAT_0046acfc;
  local_c = DAT_0046ad04;
  local_14 = DAT_0046ad08;
  goto LAB_00438cc7;
}


/* ==== FUN_004394be @ 004394be ==== */

undefined4 FUN_004394be(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint local_1c;
  int local_18;
  undefined4 local_14;
  undefined1 *local_10;
  undefined1 *local_c;
  
  local_c = *(undefined1 **)(DAT_0046ad0c + 4);
  local_10 = DAT_0046c058;
  if (*(int *)(DAT_0046ad0c + 4) + 1 + DAT_0046ad00 < DAT_0046ad10) {
    FUN_00439cf9(s_fatal_flex_scanner_internal_erro_0045d0f8);
  }
  if (*(int *)(DAT_0046ad0c + 0x20) == 0) {
    if (DAT_0046ad10 - (int)DAT_0046c058 == 1) {
      local_14 = 1;
    }
    else {
      local_14 = 2;
    }
  }
  else {
    iVar2 = (DAT_0046ad10 - (int)DAT_0046c058) + -1;
    for (local_18 = 0; local_18 < iVar2; local_18 = local_18 + 1) {
      *local_c = *local_10;
      local_c = local_c + 1;
      local_10 = local_10 + 1;
    }
    if (*(int *)(DAT_0046ad0c + 0x24) == 2) {
      DAT_0046ad00 = 0;
      *(undefined4 *)(DAT_0046ad0c + 0x10) = 0;
    }
    else {
      iVar3 = *(int *)(DAT_0046ad0c + 0xc) - iVar2;
      while (iVar1 = DAT_0046ad0c, local_1c = iVar3 - 1, (int)local_1c < 1) {
        iVar3 = DAT_0046ad10 - *(int *)(DAT_0046ad0c + 4);
        if (*(int *)(DAT_0046ad0c + 0x14) == 0) {
          *(undefined4 *)(DAT_0046ad0c + 4) = 0;
        }
        else {
          if (*(int *)(DAT_0046ad0c + 0xc) << 1 < 1) {
            *(uint *)(DAT_0046ad0c + 0xc) =
                 *(int *)(DAT_0046ad0c + 0xc) + (*(uint *)(DAT_0046ad0c + 0xc) >> 3);
          }
          else {
            *(int *)(DAT_0046ad0c + 0xc) = *(int *)(DAT_0046ad0c + 0xc) << 1;
          }
          uVar4 = FUN_00439d2f(*(int **)(iVar1 + 4),*(int *)(iVar1 + 0xc) + 2);
          *(undefined4 *)(iVar1 + 4) = uVar4;
        }
        if (*(int *)(iVar1 + 4) == 0) {
          FUN_00439cf9(s_fatal_error___scanner_input_buff_0045d130);
        }
        DAT_0046ad10 = *(int *)(iVar1 + 4) + iVar3;
        iVar3 = *(int *)(DAT_0046ad0c + 0xc) - iVar2;
      }
      if (0x2000 < (int)local_1c) {
        local_1c = 0x2000;
      }
      DAT_0046ad00 = FUN_00439d55((undefined4 *)(*(int *)(DAT_0046ad0c + 4) + iVar2),local_1c);
      *(uint *)(DAT_0046ad0c + 0x10) = DAT_0046ad00;
    }
    if (DAT_0046ad00 == 0) {
      if (iVar2 == 0) {
        local_14 = 1;
        thunk_FUN_004398f9(DAT_0046ad18);
      }
      else {
        local_14 = 2;
        *(undefined4 *)(DAT_0046ad0c + 0x24) = 2;
      }
    }
    else {
      local_14 = 0;
    }
    DAT_0046ad00 = DAT_0046ad00 + iVar2;
    *(undefined1 *)(*(int *)(DAT_0046ad0c + 4) + DAT_0046ad00) = 0;
    *(undefined1 *)(*(int *)(DAT_0046ad0c + 4) + 1 + DAT_0046ad00) = 0;
    DAT_0046c058 = *(undefined1 **)(DAT_0046ad0c + 4);
  }
  return local_14;
}


/* ==== FUN_00439743 @ 00439743 ==== */

int FUN_00439743(void)

{
  byte local_14;
  uint local_10;
  int local_c;
  byte *local_8;
  
  local_c = DAT_0046ad14;
  for (local_8 = DAT_0046c058; local_8 < DAT_0046ad10; local_8 = local_8 + 1) {
    if (*local_8 == 0) {
      local_14 = 1;
    }
    else {
      local_14 = (byte)*(undefined4 *)(&DAT_0045c0c8 + (uint)*local_8 * 4);
    }
    local_10 = (uint)local_14;
    if (*(short *)(&DAT_0045bf70 + local_c * 2) != 0) {
      DAT_0046ad08 = local_c;
      DAT_0046ad04 = local_8;
    }
    while (*(short *)(&DAT_0045cba0 + ((int)*(short *)(&DAT_0045c5b8 + local_c * 2) + local_10) * 2)
           != local_c) {
      local_c = (int)*(short *)(&DAT_0045c720 + local_c * 2);
      if (0xab < local_c) {
        local_10 = (uint)(byte)(&DAT_0045c4c8)[local_10 * 4];
      }
    }
    local_c = (int)*(short *)(&DAT_0045c888 +
                             ((int)*(short *)(&DAT_0045c5b8 + local_c * 2) + local_10) * 2);
  }
  return local_c;
}


/* ==== FUN_00439839 @ 00439839 ==== */

uint __cdecl FUN_00439839(int param_1)

{
  uint local_c;
  
  local_c = 1;
  if (*(short *)(&DAT_0045bf70 + param_1 * 2) != 0) {
    DAT_0046ad08 = param_1;
    DAT_0046ad04 = DAT_0046ad10;
  }
  while (*(short *)(&DAT_0045cba0 + ((int)*(short *)(&DAT_0045c5b8 + param_1 * 2) + local_c) * 2) !=
         param_1) {
    param_1 = (int)*(short *)(&DAT_0045c720 + param_1 * 2);
    if (0xab < param_1) {
      local_c = (uint)(byte)(&DAT_0045c4c8)[local_c * 4];
    }
  }
  return ~-(uint)((int)*(short *)(&DAT_0045c888 +
                                 ((int)*(short *)(&DAT_0045c5b8 + param_1 * 2) + local_c) * 2) ==
                 0xab) &
         (int)*(short *)(&DAT_0045c888 +
                        ((int)*(short *)(&DAT_0045c5b8 + param_1 * 2) + local_c) * 2);
}


/* ==== FUN_004398f9 @ 004398f9 ==== */

void __cdecl FUN_004398f9(int param_1)

{
  if (DAT_0046ad0c == (int *)0x0) {
    DAT_0046ad0c = thunk_FUN_004399db(DAT_0046ad18,0x4000);
  }
  thunk_FUN_00439a9d(DAT_0046ad0c,param_1);
  thunk_FUN_00439993();
  return;
}


/* ==== FUN_00439937 @ 00439937 ==== */

void __cdecl FUN_00439937(int param_1)

{
  if (DAT_0046ad0c != param_1) {
    if (DAT_0046ad0c != 0) {
      *DAT_0046ad10 = DAT_0046acfc;
      *(undefined1 **)(DAT_0046ad0c + 8) = DAT_0046ad10;
      *(undefined4 *)(DAT_0046ad0c + 0x10) = DAT_0046ad00;
    }
    DAT_0046ad0c = param_1;
    thunk_FUN_00439993();
    DAT_0046acf8 = 1;
  }
  return;
}


/* ==== FUN_00439993 @ 00439993 ==== */

void FUN_00439993(void)

{
  DAT_0046ad00 = DAT_0046ad0c[4];
  DAT_0046ad10 = (undefined1 *)DAT_0046ad0c[2];
  DAT_0046c058 = DAT_0046ad10;
  DAT_0046ad18 = *DAT_0046ad0c;
  DAT_0046acfc = *DAT_0046ad10;
  return;
}


/* ==== FUN_004399db @ 004399db ==== */

int * __cdecl FUN_004399db(int param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_00439d1e(0x28);
  if (iVar1 == 0) {
    FUN_00439cf9(s_out_of_dynamic_memory_in_yy_crea_0045d15c);
  }
  *(int *)(iVar1 + 0xc) = param_2;
  pcVar2 = (char *)(*(int *)(iVar1 + 0xc) + 2);
  uVar3 = FUN_00439d1e((uint)pcVar2);
  *(undefined4 *)(pcVar2 + 4) = uVar3;
  if (*(int *)(pcVar2 + 4) == 0) {
    pcVar2 = s_out_of_dynamic_memory_in_yy_crea_0045d188;
    FUN_00439cf9(s_out_of_dynamic_memory_in_yy_crea_0045d188);
  }
  pcVar2[0x14] = '\x01';
  pcVar2[0x15] = '\0';
  pcVar2[0x16] = '\0';
  pcVar2[0x17] = '\0';
  thunk_FUN_00439a9d((int *)param_1,param_1);
  return (int *)param_1;
}


/* ==== FUN_00439a57 @ 00439a57 ==== */

void __cdecl FUN_00439a57(undefined *param_1)

{
  if (param_1 != (undefined *)0x0) {
    if (param_1 == DAT_0046ad0c) {
      DAT_0046ad0c = (undefined *)0x0;
    }
    if (*(int *)(param_1 + 0x14) != 0) {
      FUN_00439d44(*(undefined **)(param_1 + 4));
    }
    FUN_00439d44(param_1);
  }
  return;
}


/* ==== FUN_00439a9d @ 00439a9d ==== */

void __cdecl FUN_00439a9d(int *param_1,int param_2)

{
  int iVar1;
  uint local_8;
  
  thunk_FUN_00439afa((int)param_1);
  *param_1 = param_2;
  param_1[8] = 1;
  if (param_2 == 0) {
    local_8 = 0;
  }
  else {
    iVar1 = _fileno((void *)param_2);
    iVar1 = _isatty(iVar1);
    local_8 = (uint)(0 < iVar1);
  }
  param_1[6] = local_8;
  return;
}


/* ==== FUN_00439afa @ 00439afa ==== */

void __cdecl FUN_00439afa(int param_1)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x10) = 0;
    **(undefined1 **)(param_1 + 4) = 0;
    *(undefined1 *)(*(int *)(param_1 + 4) + 1) = 0;
    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_1 + 4);
    *(undefined4 *)(param_1 + 0x1c) = 1;
    *(undefined4 *)(param_1 + 0x24) = 0;
    if (param_1 == DAT_0046ad0c) {
      thunk_FUN_00439993();
    }
  }
  return;
}


/* ==== FUN_00439b54 @ 00439b54 ==== */

undefined4 * __cdecl FUN_00439b54(int param_1,uint param_2)

{
  undefined4 *puVar1;
  
  if (((param_2 < 2) || (*(char *)(param_1 + param_2 + -2) != '\0')) ||
     (*(char *)(param_1 + param_2 + -1) != '\0')) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1 = (undefined4 *)FUN_00439d1e(0x28);
    if (puVar1 == (undefined4 *)0x0) {
      FUN_00439cf9(s_out_of_dynamic_memory_in_yy_scan_0045d1b4);
    }
    puVar1[3] = param_2 - 2;
    puVar1[1] = param_1;
    puVar1[2] = param_1;
    puVar1[5] = 0;
    *puVar1 = 0;
    puVar1[4] = puVar1[3];
    puVar1[6] = 0;
    puVar1[7] = 1;
    puVar1[8] = 0;
    puVar1[9] = 0;
    thunk_FUN_00439937((int)puVar1);
  }
  return puVar1;
}


/* ==== FUN_00439c19 @ 00439c19 ==== */

void __cdecl FUN_00439c19(int param_1)

{
  undefined4 local_8;
  
  for (local_8 = 0; *(char *)(param_1 + local_8) != '\0'; local_8 = local_8 + 1) {
  }
  thunk_FUN_00439c52(param_1,local_8);
  return;
}


/* ==== FUN_00439c52 @ 00439c52 ==== */

undefined4 * __cdecl FUN_00439c52(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  int local_10;
  
  uVar1 = param_2 + 2;
  iVar2 = FUN_00439d1e(uVar1);
  if (iVar2 == 0) {
    FUN_00439cf9(s_out_of_dynamic_memory_in_yy_scan_0045d1e0);
  }
  for (local_10 = 0; local_10 < param_2; local_10 = local_10 + 1) {
    *(undefined1 *)(iVar2 + local_10) = *(undefined1 *)(param_1 + local_10);
  }
  *(undefined1 *)(iVar2 + param_2 + 1) = 0;
  *(undefined1 *)(iVar2 + param_2) = 0;
  puVar3 = thunk_FUN_00439b54(iVar2,uVar1);
  if (puVar3 == (undefined4 *)0x0) {
    FUN_00439cf9(s_bad_buffer_in_yy_scan_bytes___0045d20c);
  }
  puVar3[5] = 1;
  return puVar3;
}


/* ==== FUN_00439cf9 @ 00439cf9 ==== */

void FUN_00439cf9(void)

{
  undefined4 in_stack_00000004;
  
  fprintf(&DAT_0045d670,&DAT_0045d22c,in_stack_00000004);
  exit(2);
  return;
}


/* ==== FUN_00439d1e @ 00439d1e ==== */

void __cdecl FUN_00439d1e(uint param_1)

{
  thunk_FUN_0042e170(param_1);
  return;
}


/* ==== FUN_00439d2f @ 00439d2f ==== */

void __cdecl FUN_00439d2f(int *param_1,uint param_2)

{
  thunk_FUN_0042e19d(param_1,param_2);
  return;
}


/* ==== FUN_00439d44 @ 00439d44 ==== */

void __cdecl FUN_00439d44(undefined *param_1)

{
  thunk_FUN_0042e1ce(param_1);
  return;
}


/* ==== FUN_00439d55 @ 00439d55 ==== */

uint __cdecl FUN_00439d55(undefined4 *param_1,uint param_2)

{
  undefined4 local_c;
  
  if ((int)param_2 < DAT_0046c074 - (int)DAT_0046c070) {
    local_c = param_2;
  }
  else {
    local_c = DAT_0046c074 - (int)DAT_0046c070;
  }
  if (0 < (int)local_c) {
    memcpy(param_1,DAT_0046c070,local_c);
    DAT_0046c070 = (void *)((int)DAT_0046c070 + local_c);
  }
  return local_c;
}


/* ==== FUN_00439dbb @ 00439dbb ==== */

undefined4 FUN_00439dbb(void)

{
  return 1;
}


/* ==== FUN_0043a260 @ 0043a260 ==== */

int __cdecl FUN_0043a260(undefined4 param_1,undefined4 param_2,char *param_3)

{
  int iVar1;
  
  iVar1 = thunk_FUN_0043a289(param_1,param_2,param_3);
  return iVar1;
}


/* ==== FUN_0043a289 @ 0043a289 ==== */

int __cdecl FUN_0043a289(undefined4 param_1,undefined4 param_2,char *param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  DAT_0046c070 = param_3;
  uVar1 = strlen(param_3);
  DAT_0046c074 = DAT_0046c070 + uVar1;
  thunk_FUN_004398f9(DAT_0046ad18);
  if (DAT_0046ad2c == 0) {
    DAT_0046c06c = thunk_FUN_00433d2a(0x14,0x14,0x401325);
    DAT_0046c078 = thunk_FUN_00434eaa(0x14,0x14,0x4010b4);
    thunk_FUN_00436210((int)DAT_0046c078);
    DAT_0046ad2c = 1;
  }
  else {
    (*(code *)DAT_0046c06c[0xb])(DAT_0046c06c,uVar3);
  }
  DAT_0046c378 = thunk_FUN_00435d2d(param_1,param_2);
  iVar2 = thunk_FUN_0043a40d();
  if (iVar2 == 0) {
    DAT_00461f2c = DAT_00461f2c + 4;
    iVar2 = DAT_0046c378[0xc];
    thunk_FUN_00435d00(DAT_0046c378);
  }
  else {
    iVar2 = 0;
    thunk_FUN_00435d00(DAT_0046c378);
  }
  return iVar2;
}


/* ==== FUN_0043a394 @ 0043a394 ==== */

void FUN_0043a394(void)

{
  thunk_FUN_00433d00(DAT_0046c06c);
  DAT_0046c06c = (undefined *)0x0;
  thunk_FUN_00434e80(DAT_0046c078);
  DAT_0046c078 = (undefined *)0x0;
  thunk_FUN_00434550(DAT_0046c604);
  DAT_0046c604 = (undefined *)0x0;
  return;
}


/* ==== FUN_0043a3e3 @ 0043a3e3 ==== */

void __cdecl FUN_0043a3e3(int param_1,int param_2)

{
  undefined4 *puVar1;
  
  if (param_1 != 0) {
    puVar1 = thunk_FUN_00434c8f(param_2);
    (**(code **)(param_1 + 0x34))(param_1,puVar1);
  }
  return;
}


/* ==== FUN_0043a408 @ 0043a408 ==== */

void FUN_0043a408(void)

{
  return;
}


/* ==== FUN_0043a40d @ 0043a40d ==== */

undefined4 FUN_0043a40d(void)

{
  char *pcVar1;
  bool bVar2;
  undefined *extraout_EAX;
  undefined *extraout_EAX_00;
  undefined4 *puVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined4 uVar4;
  uint *puVar5;
  int *piVar6;
  uint uVar7;
  longlong lVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  char cVar13;
  uint uVar14;
  short sVar15;
  int iVar16;
  uint uVar17;
  byte bVar18;
  short sVar19;
  int iVar20;
  undefined *va0;
  int local_4b8 [4];
  int local_4a8 [4];
  int local_498 [4];
  int local_488 [4];
  int local_478 [4];
  int local_468 [4];
  int local_458 [4];
  int local_448 [4];
  int local_438 [4];
  int local_428 [4];
  int local_418 [4];
  int local_408 [4];
  int local_3f8 [4];
  int local_3e8 [4];
  int local_3d8 [4];
  int local_3c8 [4];
  int local_3b8 [4];
  int local_3a8 [4];
  int local_398 [4];
  int local_388 [4];
  int local_378 [4];
  int local_368 [4];
  int local_358 [4];
  int local_348 [4];
  int local_338 [4];
  int local_328 [4];
  int local_318 [4];
  int local_308 [4];
  int local_2f8 [4];
  int local_2e8 [4];
  int local_2d8 [4];
  int local_2c8 [4];
  int local_2b8 [4];
  int local_2a8 [4];
  int local_298 [4];
  int local_288 [4];
  int local_278 [4];
  int local_268 [4];
  int local_258 [4];
  int local_248 [4];
  int local_238 [4];
  int local_228 [4];
  int local_218 [4];
  int local_208 [4];
  int local_1f8 [4];
  int local_1e8 [4];
  int local_1d8 [4];
  int local_1c8 [4];
  int local_1b8 [4];
  int local_1a8 [4];
  int local_198 [4];
  int local_188 [4];
  int local_178 [4];
  int local_168 [4];
  int local_158 [4];
  int local_148 [4];
  int local_138 [4];
  int local_128 [4];
  int local_118 [4];
  int local_108 [4];
  int local_f8 [4];
  int local_e8 [4];
  int local_d8 [4];
  int local_c8 [4];
  int local_b8 [4];
  int local_a8 [4];
  int local_98 [4];
  int local_88 [4];
  int local_78 [4];
  int local_68 [4];
  int local_58 [4];
  int local_48 [4];
  int local_38;
  int *local_34;
  void *local_30;
  void *local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int *local_14;
  int local_10;
  uint *local_c;
  uint *local_8;
  
  local_8 = (uint *)0x0;
  DAT_0046b448 = (uint *)(PTR_DAT_0045d5fc + -0x10);
  DAT_0046b444 = (int *)(PTR_DAT_0045d5f8 + -4);
  DAT_0046c040 = 0;
  DAT_0046b460 = 0;
  DAT_0046b464 = 0;
  DAT_0046b1b4 = 0;
  DAT_0046b440 = -1;
LAB_0043a48c:
  local_c = DAT_0046b448;
  local_14 = DAT_0046b444;
  local_18 = DAT_0046c040;
LAB_0043a4a6:
  local_14 = local_14 + 1;
  if (PTR_DAT_0045d5f8 + DAT_0045d600 * 4 <= local_14) {
    local_24 = (int)local_14 - (int)PTR_DAT_0045d5f8 >> 2;
    local_28 = (int)local_c - (int)PTR_DAT_0045d5fc >> 4;
    local_1c = (int)local_8 - (int)PTR_DAT_0045d5fc >> 4;
    local_20 = DAT_0045d600 << 1;
    if (DAT_0045d600 == 0x96) {
      local_30 = (void *)thunk_FUN_0042e170(0x4b0);
      local_2c = (void *)thunk_FUN_0042e170(local_20 << 4);
      if ((local_30 == (void *)0x0) || (local_2c == (void *)0x0)) {
        local_20 = 0;
      }
      else {
        memcpy(local_30,PTR_DAT_0045d5f8,DAT_0045d600 << 2);
        PTR_DAT_0045d5f8 = extraout_EAX;
        memcpy(local_2c,PTR_DAT_0045d5fc,DAT_0045d600 << 4);
        PTR_DAT_0045d5fc = extraout_EAX_00;
      }
    }
    else {
      PTR_DAT_0045d5f8 = (undefined *)thunk_FUN_0042e19d((int *)PTR_DAT_0045d5f8,DAT_0045d600 << 3);
      PTR_DAT_0045d5fc = (undefined *)thunk_FUN_0042e19d((int *)PTR_DAT_0045d5fc,local_20 << 4);
      if ((PTR_DAT_0045d5f8 == (undefined *)0x0) || ((int *)PTR_DAT_0045d5fc == (int *)0x0)) {
        local_20 = 0;
      }
    }
    if (local_20 <= DAT_0045d600) {
      thunk_FUN_0043a408(s_yacc_stack_overflow_0045d604);
      return 1;
    }
    DAT_0045d600 = local_20;
    local_14 = (int *)(PTR_DAT_0045d5f8 + local_24 * 4);
    local_c = (uint *)(PTR_DAT_0045d5fc + local_28 * 0x10);
    local_8 = (uint *)(PTR_DAT_0045d5fc + local_1c * 0x10);
  }
  *local_14 = local_18;
  local_c[4] = DAT_0046b450;
  local_c[5] = DAT_0046b454;
  local_c[6] = DAT_0046b458;
  local_c[7] = DAT_0046b45c;
  local_c = local_c + 4;
  do {
    local_10 = *(int *)(&DAT_00451440 + local_18 * 4);
    if (-10000000 < local_10) {
      if ((DAT_0046b440 < 0) && (DAT_0046b440 = thunk_FUN_00438b60(), DAT_0046b440 < 0)) {
        DAT_0046b440 = 0;
      }
      local_10 = local_10 + DAT_0046b440;
      if (((-1 < local_10) && (local_10 < 0x4da)) &&
         (local_10 = (&DAT_004500d8)[local_10],
         *(int *)(&DAT_004519f0 + local_10 * 4) == DAT_0046b440)) {
        DAT_0046b440 = -1;
        DAT_0046b450 = DAT_0046b430;
        DAT_0046b454 = DAT_0046b434;
        DAT_0046b458 = DAT_0046b438;
        DAT_0046b45c = DAT_0046b43c;
        local_18 = local_10;
        if (0 < DAT_0046b1b4) {
          DAT_0046b1b4 = DAT_0046b1b4 + -1;
        }
        goto LAB_0043a4a6;
      }
    }
    local_10 = *(int *)(&DAT_00451cb8 + local_18 * 4);
    if (local_10 == -2) {
      if ((DAT_0046b440 < 0) && (DAT_0046b440 = thunk_FUN_00438b60(), DAT_0046b440 < 0)) {
        DAT_0046b440 = 0;
      }
      for (local_34 = &DAT_004500c0;
          (*local_34 != -1 || (piVar6 = local_34, local_34[1] != local_18)); local_34 = local_34 + 2
          ) {
      }
      do {
        local_34 = piVar6;
        piVar6 = local_34 + 2;
        if (*piVar6 < 0) break;
      } while (*piVar6 != DAT_0046b440);
      local_10 = local_34[3];
      local_34 = piVar6;
      if (local_10 < 0) {
        return 0;
      }
    }
    puVar5 = local_c;
    if (local_10 != 0) {
switchD_0043a7fd_default:
      DAT_0046b460 = local_10;
      local_8 = local_c;
      local_38 = (int)*(uint *)(&DAT_004518b8 + local_10 * 4) >> 1;
      if ((*(uint *)(&DAT_004518b8 + local_10 * 4) & 1) == 0) {
        local_c = local_c + local_38 * -4;
        DAT_0046b450 = local_c[4];
        DAT_0046b454 = local_c[5];
        DAT_0046b458 = local_c[6];
        DAT_0046b45c = local_c[7];
        local_10 = *(int *)(&DAT_00451780 + local_10 * 4);
        local_14 = local_14 + -local_38;
        iVar20 = *(int *)(&DAT_00451708 + local_10 * 4) + 1 + *local_14;
        if ((0x4d9 < iVar20) ||
           (local_18 = (&DAT_004500d8)[iVar20], *(int *)(&DAT_004519f0 + local_18 * 4) != -local_10)
           ) {
          local_18 = (&DAT_004500d8)[*(int *)(&DAT_00451708 + local_10 * 4)];
        }
        goto LAB_0043a4a6;
      }
      DAT_0046b448 = local_c + local_38 * -4;
      uVar7 = DAT_0046b448[4];
      DAT_0046b454 = DAT_0046b448[5];
      DAT_0046b458 = DAT_0046b448[6];
      DAT_0046b45c = DAT_0046b448[7];
      iVar16 = *(int *)(&DAT_00451780 + local_10 * 4);
      DAT_0046b444 = local_14 + -local_38;
      iVar20 = *(int *)(&DAT_00451708 + iVar16 * 4) + 1 + *DAT_0046b444;
      if ((0x4d9 < iVar20) ||
         (local_18 = (&DAT_004500d8)[iVar20], *(int *)(&DAT_004519f0 + local_18 * 4) != -iVar16)) {
        local_18 = (&DAT_004500d8)[*(int *)(&DAT_00451708 + iVar16 * 4)];
      }
      DAT_0046c040 = local_18;
      DAT_0046b450._1_3_ = (undefined3)(uVar7 >> 8);
      DAT_0046b450 = uVar7;
      local_14 = DAT_0046b444;
      switch(local_10) {
      case 1:
        uVar7 = *local_c;
        break;
      case 2:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        puVar5 = (uint *)thunk_FUN_004385f0(local_48,(int *)puVar5,2);
        DAT_0046b450 = *puVar5;
        puVar3 = thunk_FUN_0040c91d();
        DAT_0046c378[0xc] = (int)puVar3;
        *(uint *)(DAT_0046c378[0xc] + 8) = DAT_0046b450;
        uVar7 = DAT_0046b450;
        iVar16 = local_10;
        break;
      case 3:
        DAT_0046b454 = local_c[1];
        DAT_0046b458 = local_c[2];
        DAT_0046b45c = local_c[3];
        uVar7 = *local_c;
        break;
      case 4:
        DAT_0046b454 = local_c[1];
        DAT_0046b458 = local_c[2];
        DAT_0046b45c = local_c[3];
        uVar7 = *local_c;
        break;
      case 5:
        DAT_0046b458 = 1;
        uVar7 = *local_c;
        break;
      case 6:
        DAT_0046b458 = 1;
        uVar7 = *local_c;
        break;
      case 7:
        DAT_0046b458 = 2;
        uVar7 = *local_c;
        break;
      case 8:
        DAT_0046b458 = 1;
        uVar7 = *local_c;
        break;
      case 9:
        DAT_0046b458 = 2;
        uVar7 = *local_c;
        break;
      case 10:
        DAT_0046b458 = 1;
        uVar7 = *local_c;
        break;
      case 0xb:
        DAT_0046b458 = 1;
        uVar7 = *local_c;
        break;
      case 0xc:
        DAT_0046b458 = 1;
        uVar7 = *local_c;
        break;
      case 0xd:
        DAT_0046b458 = 1;
        uVar7 = *local_c;
        break;
      case 0xe:
        DAT_0046b458 = 2;
        uVar7 = *local_c;
        break;
      case 0xf:
        DAT_0046b458 = 2;
        uVar7 = *local_c;
        break;
      case 0x10:
        DAT_0046b458 = 2;
        uVar7 = *local_c;
        break;
      case 0x11:
        DAT_0046b458 = 2;
        uVar7 = *local_c;
        break;
      case 0x12:
        pcVar1 = (char *)*local_c;
        local_10 = iVar16;
        local_c = DAT_0046b448;
        DAT_0046c05c = thunk_FUN_0043447d(DAT_0046c06c,pcVar1);
        if (DAT_0046c05c == 0) {
          return 1;
        }
        DAT_0046b450 = *(uint *)(DAT_0046c05c + 8);
        DAT_0046b454 = *(uint *)(DAT_0046c05c + 0xc);
        DAT_0046b458 = 3;
        uVar7 = DAT_0046b450;
        iVar16 = local_10;
        if (*local_8 != 0) {
          free((void *)*local_8);
          uVar7 = DAT_0046b450;
          iVar16 = local_10;
        }
        break;
      case 0x13:
        uVar7 = *(uint *)DAT_0046c378[0x17];
        break;
      case 0x14:
        uVar7 = *(uint *)DAT_0046c378[0x19];
        break;
      case 0x15:
        uVar7 = *(uint *)DAT_0046c378[0x18];
        break;
      case 0x16:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_58,(int *)puVar5,1);
        iVar20 = *piVar6;
        piVar6 = thunk_FUN_004385f0(local_68,(int *)(local_8 + -8),1);
        uVar7 = thunk_FUN_004356a0(*piVar6,iVar20);
        iVar16 = local_10;
        break;
      case 0x17:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_78,(int *)puVar5,1);
        iVar20 = *piVar6;
        piVar6 = thunk_FUN_004385f0(local_88,(int *)(local_8 + -8),1);
        uVar7 = thunk_FUN_004356ab(*piVar6,iVar20);
        iVar16 = local_10;
        break;
      case 0x18:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        if (DAT_0046ad28 == 0) {
          puVar5 = (uint *)thunk_FUN_004385f0(local_98,(int *)puVar5,3);
          lVar8 = thunk_FUN_004358ea(DAT_0046c06c,(char *)local_8[-8],0x101,*puVar5,puVar5[1]);
          DAT_0046b450 = (uint)lVar8;
        }
        uVar7 = DAT_0046b450;
        iVar16 = local_10;
        if (local_8[-8] != 0) {
          free((void *)local_8[-8]);
          uVar7 = DAT_0046b450;
          iVar16 = local_10;
        }
        break;
      case 0x19:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        if (DAT_0046ad28 == 0) {
          puVar5 = (uint *)thunk_FUN_004385f0(local_a8,(int *)puVar5,3);
          lVar8 = thunk_FUN_004358ea(DAT_0046c06c,(char *)local_8[-8],0x102,*puVar5,puVar5[1]);
          DAT_0046b450 = (uint)lVar8;
        }
        uVar7 = DAT_0046b450;
        iVar16 = local_10;
        if (local_8[-8] != 0) {
          free((void *)local_8[-8]);
          uVar7 = DAT_0046b450;
          iVar16 = local_10;
        }
        break;
      case 0x1a:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        if (DAT_0046ad28 == 0) {
          puVar5 = (uint *)thunk_FUN_004385f0(local_b8,(int *)puVar5,3);
          lVar8 = thunk_FUN_004358ea(DAT_0046c06c,(char *)local_8[-8],0x103,*puVar5,puVar5[1]);
          DAT_0046b450 = (uint)lVar8;
        }
        uVar7 = DAT_0046b450;
        iVar16 = local_10;
        if (local_8[-8] != 0) {
          free((void *)local_8[-8]);
          uVar7 = DAT_0046b450;
          iVar16 = local_10;
        }
        break;
      case 0x1b:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        if (DAT_0046ad28 == 0) {
          puVar5 = (uint *)thunk_FUN_004385f0(local_c8,(int *)puVar5,3);
          lVar8 = thunk_FUN_004358ea(DAT_0046c06c,(char *)local_8[-8],0x103,*puVar5,puVar5[1]);
          DAT_0046b450 = (uint)lVar8;
        }
        uVar7 = DAT_0046b450;
        iVar16 = local_10;
        if (local_8[-8] != 0) {
          free((void *)local_8[-8]);
          uVar7 = DAT_0046b450;
          iVar16 = local_10;
        }
        break;
      case 0x1c:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        if (DAT_0046ad28 == 0) {
          puVar5 = (uint *)thunk_FUN_004385f0(local_d8,(int *)puVar5,3);
          lVar8 = thunk_FUN_004358ea(DAT_0046c06c,(char *)local_8[-8],0x103,*puVar5,puVar5[1]);
          DAT_0046b450 = (uint)lVar8;
        }
        uVar7 = DAT_0046b450;
        iVar16 = local_10;
        if (local_8[-8] != 0) {
          free((void *)local_8[-8]);
          uVar7 = DAT_0046b450;
          iVar16 = local_10;
        }
        break;
      case 0x1d:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        if (DAT_0046ad28 == 0) {
          puVar5 = (uint *)thunk_FUN_004385f0(local_e8,(int *)puVar5,3);
          lVar8 = thunk_FUN_004358ea(DAT_0046c06c,(char *)local_8[-8],0x3d,*puVar5,puVar5[1]);
          DAT_0046b450 = (uint)lVar8;
        }
        uVar7 = DAT_0046b450;
        iVar16 = local_10;
        if (local_8[-8] != 0) {
          free((void *)local_8[-8]);
          uVar7 = DAT_0046b450;
          iVar16 = local_10;
        }
        break;
      case 0x1e:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        puVar5 = (uint *)thunk_FUN_004385f0(local_f8,(int *)puVar5,2);
        uVar7 = *puVar5;
        puVar5 = (uint *)thunk_FUN_004385f0(local_108,(int *)(local_8 + -8),2);
        uVar7 = thunk_FUN_004358aa(*puVar5,uVar7);
        iVar16 = local_10;
        break;
      case 0x1f:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        puVar5 = (uint *)thunk_FUN_004385f0(local_118,(int *)puVar5,2);
        uVar7 = *puVar5;
        puVar5 = (uint *)thunk_FUN_004385f0(local_128,(int *)(local_8 + -8),2);
        uVar7 = thunk_FUN_004358b5(*puVar5,uVar7);
        iVar16 = local_10;
        break;
      case 0x20:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        puVar5 = (uint *)thunk_FUN_004385f0(local_138,(int *)puVar5,2);
        uVar7 = *puVar5;
        puVar5 = (uint *)thunk_FUN_004385f0(local_148,(int *)(local_8 + -8),2);
        uVar7 = thunk_FUN_004358c0(*puVar5,uVar7);
        iVar16 = local_10;
        break;
      case 0x21:
        puVar5 = local_c + -4;
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_158,(int *)puVar5,1);
        if (*piVar6 == 0) {
          DAT_0045d5f4 = 3;
        }
        else {
          DAT_0045d5f4 = 2;
        }
        DAT_0046ad28 = (uint)(*piVar6 == 0);
        uVar7 = DAT_0046b450;
        iVar16 = local_10;
        break;
      case 0x22:
        DAT_0046ad28 = (uint)(DAT_0045d5f4 == 2);
        break;
      case 0x23:
        DAT_0046ad28 = 0;
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_168,(int *)puVar5,1);
        iVar20 = *piVar6;
        piVar6 = thunk_FUN_004385f0(local_178,(int *)(local_8 + -0xc),1);
        iVar16 = *piVar6;
        piVar6 = thunk_FUN_004385f0(local_188,(int *)(local_8 + -0x18),1);
        uVar7 = thunk_FUN_004358cb(*piVar6,iVar16,iVar20);
        iVar16 = local_10;
        break;
      case 0x24:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_198,(int *)puVar5,1);
        iVar20 = *piVar6;
        piVar6 = thunk_FUN_004385f0(local_1a8,(int *)(local_8 + -8),1);
        bVar2 = thunk_FUN_00435886(*piVar6,iVar20);
        uVar7 = CONCAT31(extraout_var,bVar2);
        iVar16 = local_10;
        break;
      case 0x25:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_1b8,(int *)puVar5,1);
        iVar20 = *piVar6;
        piVar6 = thunk_FUN_004385f0(local_1c8,(int *)(local_8 + -8),1);
        bVar2 = thunk_FUN_00435898(*piVar6,iVar20);
        uVar7 = CONCAT31(extraout_var_00,bVar2);
        iVar16 = local_10;
        break;
      case 0x26:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_1d8,(int *)puVar5,1);
        iVar20 = *piVar6;
        piVar6 = thunk_FUN_004385f0(local_1e8,(int *)(local_8 + -8),1);
        uVar7 = thunk_FUN_004357f0(*piVar6,iVar20);
        iVar16 = local_10;
        break;
      case 0x27:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_1f8,(int *)puVar5,1);
        iVar20 = *piVar6;
        piVar6 = thunk_FUN_004385f0(local_208,(int *)(local_8 + -8),1);
        uVar7 = thunk_FUN_00435817(*piVar6,iVar20);
        iVar16 = local_10;
        break;
      case 0x28:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_218,(int *)puVar5,1);
        iVar20 = *piVar6;
        piVar6 = thunk_FUN_004385f0(local_228,(int *)(local_8 + -8),1);
        uVar7 = thunk_FUN_004356b6(*piVar6,iVar20);
        iVar16 = local_10;
        break;
      case 0x29:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_238,(int *)puVar5,1);
        iVar20 = *piVar6;
        piVar6 = thunk_FUN_004385f0(local_248,(int *)(local_8 + -8),1);
        uVar7 = thunk_FUN_004356c2(*piVar6,iVar20);
        iVar16 = local_10;
        break;
      case 0x2a:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_258,(int *)puVar5,1);
        iVar20 = *piVar6;
        piVar6 = thunk_FUN_004385f0(local_268,(int *)(local_8 + -8),1);
        uVar7 = thunk_FUN_004356e5(*piVar6,iVar20);
        iVar16 = local_10;
        break;
      case 0x2b:
        DAT_0046b454 = local_c[-3];
        DAT_0046b458 = local_c[-2];
        DAT_0046b45c = local_c[-1];
        uVar7 = local_c[-4];
        break;
      case 0x2c:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_278,(int *)puVar5,1);
        iVar20 = *piVar6;
        piVar6 = thunk_FUN_004385f0(local_288,(int *)(local_8 + -8),1);
        bVar2 = thunk_FUN_00435874(*piVar6,iVar20);
        uVar7 = CONCAT31(extraout_var_01,bVar2);
        iVar16 = local_10;
        break;
      case 0x2d:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_298,(int *)puVar5,1);
        iVar20 = *piVar6;
        piVar6 = thunk_FUN_004385f0(local_2a8,(int *)(local_8 + -8),1);
        bVar2 = thunk_FUN_00435850(*piVar6,iVar20);
        uVar7 = CONCAT31(extraout_var_02,bVar2);
        iVar16 = local_10;
        break;
      case 0x2e:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_2b8,(int *)puVar5,1);
        iVar20 = *piVar6;
        piVar6 = thunk_FUN_004385f0(local_2c8,(int *)(local_8 + -8),1);
        bVar2 = thunk_FUN_0043583e(*piVar6,iVar20);
        uVar7 = CONCAT31(extraout_var_03,bVar2);
        iVar16 = local_10;
        break;
      case 0x2f:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_2d8,(int *)puVar5,1);
        iVar20 = *piVar6;
        piVar6 = thunk_FUN_004385f0(local_2e8,(int *)(local_8 + -8),1);
        bVar2 = thunk_FUN_00435862(*piVar6,iVar20);
        uVar7 = CONCAT31(extraout_var_04,bVar2);
        iVar16 = local_10;
        break;
      case 0x30:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_2f8,(int *)puVar5,2);
        bVar18 = (byte)*piVar6;
        puVar5 = (uint *)thunk_FUN_004385f0(local_308,(int *)(local_8 + -8),2);
        uVar7 = thunk_FUN_004357b4(*puVar5,bVar18);
        iVar16 = local_10;
        break;
      case 0x31:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_318,(int *)puVar5,2);
        bVar18 = (byte)*piVar6;
        piVar6 = thunk_FUN_004385f0(local_328,(int *)(local_8 + -8),2);
        uVar7 = thunk_FUN_004357c1(*piVar6,bVar18);
        iVar16 = local_10;
        break;
      case 0x32:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_338,(int *)puVar5,1);
        bVar2 = thunk_FUN_004357e2(*piVar6);
        DAT_0046b458 = 1;
        uVar7 = CONCAT31(extraout_var_05,bVar2);
        iVar16 = local_10;
        break;
      case 0x33:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        puVar5 = (uint *)thunk_FUN_004385f0(local_348,(int *)puVar5,2);
        uVar7 = thunk_FUN_004357ce(*puVar5);
        DAT_0046b458 = 2;
        iVar16 = local_10;
        break;
      case 0x34:
        local_10 = iVar16;
        local_c = DAT_0046b448;
        piVar6 = thunk_FUN_004385f0(local_358,(int *)puVar5,1);
        uVar7 = thunk_FUN_004357d8(*piVar6);
        DAT_0046b458 = 1;
        iVar16 = local_10;
        break;
      case 0x35:
        local_10 = iVar16;
        puVar5 = DAT_0046b448;
        if (DAT_0046ad28 == 0) {
          puVar5 = local_c + -0x24;
          local_c = DAT_0046b448;
          DAT_0046c07c = thunk_FUN_004355d6(DAT_0046c078,(char *)*puVar5);
          if (DAT_0046c07c == 0) {
            return 1;
          }
          piVar6 = thunk_FUN_004385f0(local_368,(int *)(local_8 + -0x1c),2);
          DAT_0046c378[4] = *piVar6;
          *(char *)(DAT_0046c378 + 5) = (char)local_8[-0x14];
          piVar6 = thunk_FUN_004385f0(local_378,(int *)(local_8 + -0xc),1);
          DAT_0046c378[6] = *piVar6;
          piVar6 = thunk_FUN_004385f0(local_388,(int *)(local_8 + -4),0);
          *(short *)(DAT_0046c378 + 7) = (short)*piVar6;
          DAT_0046b450 = (**(code **)(DAT_0046c07c + 4))(DAT_0046c378);
          puVar5 = local_c;
        }
        local_c = puVar5;
        uVar7 = DAT_0046b450;
        iVar16 = local_10;
        if (local_8[-0x24] != 0) {
          free((void *)local_8[-0x24]);
          uVar7 = DAT_0046b450;
          iVar16 = local_10;
        }
        break;
      case 0x38:
        uVar7 = *local_c;
        break;
      case 0x3f:
        if (DAT_0046ad28 == 0) {
          sVar19 = 0;
          puVar5 = local_c + -4;
          local_10 = iVar16;
          local_c = DAT_0046b448;
          piVar6 = thunk_FUN_004385f0(local_398,(int *)puVar5,1);
          sVar15 = (short)*piVar6;
          cVar13 = (char)local_8[-0xc];
          puVar5 = (uint *)thunk_FUN_004385f0(local_3a8,(int *)(local_8 + -0x14),2);
          uVar4 = thunk_FUN_00438042(*puVar5,cVar13,sVar15,sVar19);
          uVar7 = (int)(short)uVar4;
          iVar16 = local_10;
        }
        break;
      case 0x40:
        if (DAT_0046ad28 == 0) {
          puVar5 = local_c + -4;
          local_10 = iVar16;
          local_c = DAT_0046b448;
          piVar6 = thunk_FUN_004385f0(local_3b8,(int *)puVar5,0);
          sVar15 = (short)*piVar6;
          piVar6 = thunk_FUN_004385f0(local_3c8,(int *)(local_8 + -0xc),1);
          sVar19 = (short)*piVar6;
          cVar13 = (char)local_8[-0x14];
          puVar5 = (uint *)thunk_FUN_004385f0(local_3d8,(int *)(local_8 + -0x1c),2);
          uVar4 = thunk_FUN_00438042(*puVar5,cVar13,sVar19,sVar15);
          uVar7 = (int)(short)uVar4;
          iVar16 = local_10;
        }
        break;
      case 0x41:
        if (DAT_0046ad28 == 0) {
          sVar19 = 0;
          puVar5 = local_c + -4;
          local_10 = iVar16;
          local_c = DAT_0046b448;
          piVar6 = thunk_FUN_004385f0(local_3e8,(int *)puVar5,1);
          sVar15 = (short)*piVar6;
          cVar13 = (char)local_8[-0xc];
          puVar5 = (uint *)thunk_FUN_004385f0(local_3f8,(int *)(local_8 + -0x14),2);
          uVar7 = thunk_FUN_00437fc0(*puVar5,cVar13,sVar15,sVar19);
          iVar16 = local_10;
        }
        break;
      case 0x42:
        if (DAT_0046ad28 == 0) {
          puVar5 = local_c + -4;
          local_10 = iVar16;
          local_c = DAT_0046b448;
          piVar6 = thunk_FUN_004385f0(local_408,(int *)puVar5,0);
          sVar15 = (short)*piVar6;
          piVar6 = thunk_FUN_004385f0(local_418,(int *)(local_8 + -0xc),1);
          sVar19 = (short)*piVar6;
          cVar13 = (char)local_8[-0x14];
          puVar5 = (uint *)thunk_FUN_004385f0(local_428,(int *)(local_8 + -0x1c),2);
          uVar7 = thunk_FUN_00437fc0(*puVar5,cVar13,sVar19,sVar15);
          iVar16 = local_10;
        }
        break;
      case 0x43:
        DAT_0046b450 = CONCAT31(DAT_0046b450._1_3_,(char)*local_c);
        uVar7 = DAT_0046b450;
        break;
      case 0x44:
        DAT_0046b450 = CONCAT31(DAT_0046b450._1_3_,(char)*local_c);
        uVar7 = DAT_0046b450;
        break;
      case 0x45:
        if (DAT_0046ad28 == 0) {
          puVar5 = local_c + -4;
          local_10 = iVar16;
          local_c = DAT_0046b448;
          piVar6 = thunk_FUN_004385f0(local_438,(int *)puVar5,1);
          uVar7 = thunk_FUN_00437e46(DAT_0046c378,DAT_0046c604,*piVar6);
          iVar16 = local_10;
        }
        break;
      case 0x46:
        if (DAT_0046ad28 == 0) {
          puVar5 = local_c + -4;
          local_10 = iVar16;
          local_c = DAT_0046b448;
          piVar6 = thunk_FUN_004385f0(local_448,(int *)puVar5,1);
          uVar7 = thunk_FUN_0043834c((int)DAT_0046c378,(short)*piVar6);
          iVar16 = local_10;
        }
        break;
      case 0x47:
        if (DAT_0046ad28 == 0) {
          va0 = &DAT_0046ad30;
          puVar5 = local_c + -4;
          local_10 = iVar16;
          local_c = DAT_0046b448;
          piVar6 = thunk_FUN_004385f0(local_458,(int *)puVar5,1);
          uVar7 = thunk_FUN_0043833c(*piVar6,va0);
          iVar16 = local_10;
        }
        break;
      case 0x48:
        if (DAT_0046ad28 == 0) {
          uVar7 = local_c[-4];
          puVar5 = local_c + -0xc;
          local_10 = iVar16;
          local_c = DAT_0046b448;
          piVar6 = thunk_FUN_004385f0(local_468,(int *)puVar5,1);
          uVar7 = thunk_FUN_0043833c(*piVar6,uVar7);
          iVar16 = local_10;
        }
        break;
      case 0x49:
        if (DAT_0046ad28 == 0) {
          puVar5 = local_c + -4;
          local_10 = iVar16;
          local_c = DAT_0046b448;
          puVar5 = (uint *)thunk_FUN_004385f0(local_478,(int *)puVar5,2);
          uVar7 = thunk_FUN_0043825a((int)DAT_0046c378,*puVar5);
          iVar16 = local_10;
        }
        break;
      case 0x4a:
        if (DAT_0046ad28 == 0) {
          puVar5 = local_c + -4;
          local_10 = iVar16;
          local_c = DAT_0046b448;
          puVar5 = (uint *)thunk_FUN_004385f0(local_488,(int *)puVar5,2);
          uVar7 = thunk_FUN_00438203((int)DAT_0046c378,*puVar5);
          iVar16 = local_10;
        }
        break;
      case 0x4b:
        if (DAT_0046ad28 == 0) {
          puVar5 = local_c + -4;
          local_10 = iVar16;
          local_c = DAT_0046b448;
          piVar6 = thunk_FUN_004385f0(local_498,(int *)puVar5,0);
          sVar15 = (short)*piVar6;
          piVar6 = thunk_FUN_004385f0(local_4a8,(int *)(local_8 + -0xc),1);
          uVar7 = thunk_FUN_004382c9(DAT_0046c378,DAT_0046c604,*piVar6,sVar15);
          iVar16 = local_10;
        }
        break;
      case 0x4c:
        if (DAT_0046ad28 == 0) {
          uVar7 = local_c[-4];
          uVar17 = local_c[-0xc];
          uVar14 = local_c[-0x14];
          uVar12 = local_c[-0x1c];
          uVar11 = local_c[-0x24];
          uVar10 = local_c[-0x2c];
          uVar9 = local_c[-0x34];
          puVar5 = local_c + -0x3c;
          local_10 = iVar16;
          local_c = DAT_0046b448;
          piVar6 = thunk_FUN_004385f0(local_4b8,(int *)puVar5,2);
          uVar7 = thunk_FUN_00437950((int)DAT_0046c378,*piVar6,uVar9,uVar10,uVar11,uVar12,uVar14,
                                     uVar17,uVar7);
          iVar16 = local_10;
        }
      }
      local_10 = iVar16;
      DAT_0046b450 = uVar7;
      goto LAB_0043a48c;
    }
    switch(DAT_0046b1b4) {
    case 0:
      thunk_FUN_0043a408(s_syntax_error_0045d618);
      DAT_0046b464 = DAT_0046b464 + 1;
    case 1:
    case 2:
      goto switchD_0043a7fd_caseD_1;
    case 3:
      if (DAT_0046b440 == 0) {
        return 1;
      }
      DAT_0046b440 = -1;
      break;
    default:
      goto switchD_0043a7fd_default;
    }
  } while( true );
switchD_0043a7fd_caseD_1:
  DAT_0046b1b4 = 3;
  while( true ) {
    if (local_14 < PTR_DAT_0045d5f8) {
      DAT_0046b1b4 = 3;
      return 1;
    }
    local_10 = *(int *)(&DAT_00451440 + *local_14 * 4) + 0x100;
    if (((-1 < local_10) && (local_10 < 0x4da)) &&
       (*(int *)(&DAT_004519f0 + (&DAT_004500d8)[local_10] * 4) == 0x100)) break;
    local_14 = local_14 + -1;
    local_c = local_c + -4;
  }
  local_18 = (&DAT_004500d8)[local_10];
  goto LAB_0043a4a6;
}


