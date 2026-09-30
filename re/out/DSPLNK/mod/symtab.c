/* symtab: 28 functions from DSPLNK */

/* ==== FUN_0042944b @ 0042944b ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0042944b(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  if (DAT_00461248 == '\0') {
    puVar2 = (undefined4 *)thunk_FUN_0042e170(0x38);
    puVar1 = puVar2;
    if (DAT_00461f08 != (undefined4 *)0x0) {
      DAT_00461f08[0xd] = puVar2;
      puVar1 = DAT_00461f04;
    }
    DAT_00461f04 = puVar1;
    DAT_00461f08 = puVar2;
    puVar2[6] = 0;
    *puVar2 = 0;
    puVar2[7] = 0;
    puVar2[1] = 0;
    puVar2[3] = 4;
    puVar2[2] = 4;
    puVar2[4] = 0;
    puVar2[5] = 0;
    puVar2[9] = 4;
    puVar2[8] = 4;
    puVar2[10] = 0;
    puVar2[0xb] = 0;
    puVar2[0xc] = 0xffffffff;
    puVar2[0xd] = 0;
    thunk_FUN_00430534();
    strcpy(&DAT_0046c140,s__text_00457fb0);
    _DAT_0046c148 = 0;
    _DAT_0046c14c = 4;
    _DAT_0046c150 = 1;
    _DAT_0046c158 = 3;
    DAT_0046c15c = 1;
    iVar3 = thunk_FUN_00429641((undefined4 *)&DAT_0046c140);
    DAT_00461f08[0xc] = iVar3;
    _DAT_0046c080 = 0;
    _DAT_0046c084 = 0;
    DAT_0046c088 = DAT_00461f0c;
    thunk_FUN_00429641((undefined4 *)&DAT_0046c080);
    strcpy(&DAT_0046c140,s__data_00457fc0);
    _DAT_0046c148 = 0;
    _DAT_0046c14c = 4;
    _DAT_0046c150 = 2;
    _DAT_0046c158 = 3;
    DAT_0046c15c = 1;
    thunk_FUN_00429641((undefined4 *)&DAT_0046c140);
    _DAT_0046c080 = 0;
    DAT_0046c088 = 0;
    _DAT_0046c084 = 0;
    thunk_FUN_00429641((undefined4 *)&DAT_0046c080);
    DAT_00461f0c = 0;
  }
  return;
}


/* ==== FUN_00429641 @ 00429641 ==== */

int __cdecl FUN_00429641(undefined4 *param_1)

{
  int iVar1;
  
  if ((DAT_00461294 == 2) && (DAT_00461f38 != 0)) {
    if (DAT_00461ee0 == 0) {
      DAT_00461ee0 = 0x1000;
      DAT_00461edc = (int *)thunk_FUN_0042e170(0x20000);
    }
    else if (DAT_00461ee0 <= DAT_00461ed8) {
      if (DAT_00461ee0 < 0x40000) {
        DAT_00461ee0 = DAT_00461ee0 << 1;
      }
      else {
        DAT_00461ee0 = DAT_00461ee0 + 0x40000;
      }
      DAT_00461edc = thunk_FUN_0042e19d(DAT_00461edc,DAT_00461ee0 << 5);
    }
    memcpy(DAT_00461edc + DAT_00461ed8 * 8,param_1,0x20);
  }
  iVar1 = DAT_00461ed8;
  DAT_00461ed8 = DAT_00461ed8 + 1;
  return iVar1;
}


/* ==== FUN_00429716 @ 00429716 ==== */

int __cdecl FUN_00429716(uint *param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = strlen((char *)param_1);
  iVar1 = DAT_00457c04;
  iVar3 = uVar2 + 1;
  if ((DAT_00461294 == 2) && (DAT_00461f38 != 0)) {
    if (DAT_00461eec == 0) {
      DAT_00461eec = 0x1000;
      DAT_00461ee8 = (int *)thunk_FUN_0042e170(0x1000);
    }
    else if ((int)DAT_00461eec <= DAT_00457c04 + iVar3) {
      if ((int)DAT_00461eec < 0x40000) {
        DAT_00461eec = DAT_00461eec << 1;
      }
      else {
        DAT_00461eec = DAT_00461eec + 0x40000;
      }
      DAT_00461ee8 = thunk_FUN_0042e19d(DAT_00461ee8,DAT_00461eec);
    }
    strcpy((char *)((int)DAT_00461ee8 + DAT_00457c04),(char *)param_1);
    *(undefined1 *)((int)DAT_00461ee8 + DAT_00457c04 + iVar3) = 0;
  }
  DAT_00457c04 = DAT_00457c04 + iVar3;
  return iVar1;
}


/* ==== FUN_00429811 @ 00429811 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_00429811(uint *param_1,undefined4 param_2)

{
  if ((DAT_00461294 == 2) && (DAT_00461f38 != 0)) {
    thunk_FUN_00430534();
    strcpy(&DAT_0046c140,&DAT_00457fd0);
    _DAT_0046c148 = thunk_FUN_00429716(param_1);
    _DAT_0046c14c = 4;
    _DAT_0046c150 = param_2;
    thunk_FUN_00429641((undefined4 *)&DAT_0046c140);
  }
  return;
}


/* ==== FUN_00429870 @ 00429870 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00429870(void)

{
  uint *s;
  uint uVar1;
  undefined4 local_18;
  int local_10;
  undefined4 *local_8;
  
  for (local_10 = 0; local_10 < 0x7d3; local_10 = local_10 + 1) {
    for (local_8 = *(undefined4 **)(&DAT_00461ff8 + local_10 * 4); local_8 != (undefined4 *)0x0;
        local_8 = (undefined4 *)local_8[0x18]) {
      if ((local_8[10] & 0x10000) != 0) {
        thunk_FUN_00430534();
        s = (uint *)*local_8;
        uVar1 = strlen((char *)s);
        if (uVar1 < 8) {
          strcpy(&DAT_0046c140,(char *)s);
        }
        else {
          _DAT_0046c144 = thunk_FUN_00429716(s);
        }
        if (local_8[0xb] == 4) {
          if ((local_8[10] & 0x200) == 0) {
            if (local_8[3] == 0) {
              local_18 = 4;
            }
            else {
              local_18 = local_8[3];
            }
            _DAT_0046c14c = local_18;
            _DAT_0046c148 = local_8[4];
          }
          else {
            thunk_FUN_00408bba(local_8[2],local_8[3],(undefined4 *)&DAT_0046c14c,
                               (undefined4 *)&DAT_0046c148);
          }
        }
        else {
          _DAT_0046c14c = local_8[0xc];
          _DAT_0046c148 = local_8[4];
        }
        _DAT_0046c150 = 0xffffffff;
        if ((local_8[10] & 0x200) == 0) {
          DAT_0046c154 = ((local_8[10] & 0x800) != 0) + 4;
        }
        else {
          DAT_0046c154 = 6;
        }
        _DAT_0046c158 = (-(uint)(DAT_00461210 != '\0') & 0xffffff30) + 0xd2;
        if (local_8[0xb] != 4) {
          DAT_0046c154 = DAT_0046c154 | 0x10;
        }
        thunk_FUN_00429641((undefined4 *)&DAT_0046c140);
        if (0 < DAT_0046c15c) {
          thunk_FUN_00429641((undefined4 *)&DAT_0046c080);
        }
      }
    }
  }
  return;
}


/* ==== FUN_0042a300 @ 0042a300 ==== */

void __cdecl FUN_0042a300(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)thunk_FUN_0042e170(0x2c);
  puVar1[5] = 0;
  puVar1[4] = 0;
  puVar1[3] = 0;
  puVar1[2] = 0;
  puVar1[1] = 0;
  *puVar1 = 0;
  puVar1[6] = 0;
  puVar1[7] = param_1;
  puVar1[8] = *(undefined4 *)(DAT_00461dbc + 8);
  puVar1[9] = 0;
  puVar1[10] = 0;
  *(undefined4 **)(param_1 + 0x38) = puVar1;
  return;
}


/* ==== FUN_0042a38f @ 0042a38f ==== */

void __cdecl
FUN_0042a38f(int param_1,int param_2,int param_3,int param_4,int param_5,uint param_6,int param_7,
            int param_8)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  int local_18;
  undefined4 *local_14;
  undefined4 *local_c;
  undefined4 *local_8;
  
  local_c = (undefined4 *)0x0;
  piVar1 = (int *)thunk_FUN_0042e170(0x44);
  piVar1[2] = param_1;
  piVar1[1] = param_1;
  piVar1[3] = param_2;
  piVar1[5] = param_4;
  piVar1[6] = param_5;
  piVar1[8] = param_7;
  piVar1[9] = param_8;
  piVar1[7] = param_6;
  if (param_3 == 0) {
    piVar1[4] = 0;
    *piVar1 = 0;
    piVar1[10] = 0;
    piVar1[7] = piVar1[7] | 0x2000;
    piVar1[0xb] = 0;
    piVar1[0xc] = 0;
    piVar1[0xe] = 0;
    piVar1[0xf] = 0;
    piVar1[0xd] = 0;
    piVar1[0x10] = *(int *)(*(int *)(DAT_00461de4 + 0x38) + 0x24);
    *(int **)(*(int *)(DAT_00461de4 + 0x38) + 0x24) = piVar1;
    **(int **)(DAT_00461de4 + 0x38) = **(int **)(DAT_00461de4 + 0x38) + 1;
  }
  else {
    piVar1[4] = *(int *)(*DAT_00461de0 + 0x38);
    *piVar1 = param_3;
    piVar1[10] = DAT_00461d68 + 1;
    piVar1[7] = piVar1[7] | -(uint)(DAT_00457b88 != '\0') & 0x20000;
    piVar1[0xb] = DAT_00461dbc;
    piVar1[0xc] = DAT_00461ddc;
    if ((DAT_00457b74 != '\0') && (DAT_00461f00 != (undefined4 *)0x0)) {
      local_c = (undefined4 *)thunk_FUN_0042e170(8);
      *local_c = *DAT_00461f00;
      local_c[1] = 0;
      local_8 = local_c;
      for (local_14 = (undefined4 *)DAT_00461f00[1]; local_14 != (undefined4 *)0x0;
          local_14 = (undefined4 *)local_14[1]) {
        iVar2 = thunk_FUN_0042e170(8);
        local_8[1] = iVar2;
        local_8 = (undefined4 *)local_8[1];
        *local_8 = *local_14;
        local_8[1] = 0;
      }
    }
    piVar1[0xd] = (int)local_c;
    piVar1[0xe] = DAT_00461df0;
    if (DAT_0046c2e0 == 4) {
      local_18 = 0;
    }
    else {
      local_18 = DAT_00461e60 + DAT_004612c8 * 0x24;
    }
    piVar1[0xf] = local_18;
    piVar1[0x10] = *(int *)(*(int *)(DAT_00461de4 + 0x38) + 0x24);
    *(int **)(*(int *)(DAT_00461de4 + 0x38) + 0x24) = piVar1;
    **(int **)(DAT_00461de4 + 0x38) = **(int **)(DAT_00461de4 + 0x38) + 1;
    if (DAT_00461d90 != DAT_00461d94) {
      if (DAT_00461de0[0xe] == 0) {
        thunk_FUN_0042a300((int)DAT_00461de0);
      }
      if (((*(int *)(DAT_00461de0[0xe] + 0x24) == 0) ||
          ((*(uint *)(*(int *)(DAT_00461de0[0xe] + 0x24) + 0x1c) & 0x40000) == 0)) ||
         (*(int *)(*(int *)(DAT_00461de0[0xe] + 0x24) + 0x3c) != DAT_00461e60 + DAT_004612c8 * 0x24)
         ) {
        puVar3 = (undefined4 *)thunk_FUN_0042e170(0x44);
        puVar3[2] = 0;
        puVar3[1] = 0;
        puVar3[3] = 0;
        puVar3[5] = 0;
        puVar3[6] = 0;
        puVar3[8] = 0;
        puVar3[9] = 0;
        puVar3[4] = 0;
        *puVar3 = 0;
        puVar3[10] = 0;
        puVar3[7] = param_6 | 0x40000;
        puVar3[0xb] = 0;
        puVar3[0xc] = 0;
        puVar3[0xe] = 0;
        puVar3[0xf] = DAT_00461e60 + DAT_004612c8 * 0x24;
        puVar3[0xd] = 0;
        puVar3[0x10] = *(undefined4 *)(DAT_00461de0[0xe] + 0x24);
        *(undefined4 **)(DAT_00461e60 + 0x1c + DAT_004612c8 * 0x24) = puVar3;
        *(undefined4 **)(DAT_00461de0[0xe] + 0x24) = puVar3;
      }
    }
  }
  return;
}


/* ==== FUN_0042a767 @ 0042a767 ==== */

undefined1 FUN_0042a767(void)

{
  int *piVar1;
  int iVar2;
  undefined1 uVar3;
  
  piVar1 = *(int **)(DAT_00461de4 + 0x38);
  if (piVar1 == (int *)0x0) {
    uVar3 = 2;
  }
  else {
    iVar2 = piVar1[10] + *piVar1 * 0x2c;
    *piVar1 = *piVar1 + 1;
    if ((*(uint *)(iVar2 + 0x18) & 0x100) == 0) {
      uVar3 = (*(uint *)(iVar2 + 0x18) & 0x200) != 0;
    }
    else {
      uVar3 = 2;
    }
    if ((*(uint *)(iVar2 + 0x18) & 0x100) != 0) {
      DAT_00461ea8 = DAT_00461ea8 + 1;
      *(int *)(*DAT_00461e90 + 0x18) = *(int *)(*DAT_00461e90 + 0x18) + 1;
      if (DAT_00461d90 != DAT_00461d94) {
        *(int *)(*DAT_00461de0 + 0x58) = *(int *)(*DAT_00461de0 + 0x58) + 1;
      }
    }
  }
  return uVar3;
}


/* ==== FUN_0042a84c @ 0042a84c ==== */

void FUN_0042a84c(void)

{
  int *piVar1;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  DAT_00461ef0 = 0;
  for (local_10 = 0; local_10 < 0x7d3; local_10 = local_10 + 1) {
    for (local_c = *(int *)(&DAT_00463f48 + local_10 * 4); local_c != 0;
        local_c = *(int *)(local_c + 0x10)) {
      for (local_14 = *(int *)(local_c + 8); local_14 != 0; local_14 = *(int *)(local_14 + 0x74)) {
        for (local_8 = *(int *)(local_14 + 0x18); local_8 != 0; local_8 = *(int *)(local_8 + 0x44))
        {
          piVar1 = *(int **)(local_8 + 0x38);
          if ((piVar1 != (int *)0x0) && (*piVar1 != 0)) {
            if (piVar1[10] != 0) {
              thunk_FUN_0042e1ce((undefined *)piVar1[10]);
              piVar1[10] = 0;
            }
            piVar1[2] = 0;
            FUN_0042aa32(piVar1);
            FUN_0042ac5f(piVar1);
            DAT_00461ef0 = DAT_00461ef0 + piVar1[2];
            if (piVar1[3] < piVar1[2]) {
              piVar1[3] = piVar1[2];
              DAT_0046127c = 1;
            }
          }
        }
        for (local_8 = *(int *)(local_14 + 0x24); local_8 != 0; local_8 = *(int *)(local_8 + 0x44))
        {
          piVar1 = *(int **)(local_8 + 0x38);
          if ((piVar1 != (int *)0x0) && (*piVar1 != 0)) {
            if (piVar1[10] != 0) {
              thunk_FUN_0042e1ce((undefined *)piVar1[10]);
              piVar1[10] = 0;
            }
            piVar1[2] = 0;
            FUN_0042aa32(piVar1);
            FUN_0042ac5f(piVar1);
            DAT_00461ef0 = DAT_00461ef0 + piVar1[2];
            if (piVar1[3] < piVar1[2]) {
              piVar1[3] = piVar1[2];
              DAT_0046127c = 1;
            }
          }
        }
      }
    }
  }
  return;
}


/* ==== FUN_0042aa32 @ 0042aa32 ==== */

void __cdecl FUN_0042aa32(int *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *local_14;
  int *local_10;
  uint local_8;
  
  iVar1 = param_1[7];
  iVar3 = thunk_FUN_0042e170((*param_1 + 1) * 0x2c);
  param_1[10] = iVar3;
  local_10 = (int *)(param_1[10] + -0x2c + *param_1 * 0x2c);
  for (local_14 = (int *)param_1[9]; local_14 != (int *)0x0; local_14 = (int *)local_14[0x10]) {
    piVar2 = local_10;
    if (((local_14[7] & 0x40000U) == 0) || (piVar2 = local_10 + 0xb, local_14 == (int *)param_1[9]))
    {
      local_10 = piVar2;
      *local_10 = local_14[1];
      local_10[1] = local_14[3];
      local_10[7] = 0;
      local_10[3] = 0;
      local_10[2] = 0;
      local_10[4] = local_14[5];
      local_10[5] = local_14[6];
      local_10[6] = local_14[7];
      local_10[8] = local_14[8];
      local_10[9] = local_14[9];
      local_10[10] = local_14[10];
      if ((*(uint *)(iVar1 + 8) & 0x1000) != 0) {
        if ((*(uint *)(iVar1 + 8) & 0x4000) == 0) {
          if ((*(uint *)(iVar1 + 8) & 0x20000) == 0) {
            *local_10 = *local_10 + *(int *)(iVar1 + 0x10);
          }
          else {
            *local_10 = *local_10 + (*(int *)(iVar1 + 0x10) - local_14[4]);
          }
        }
        else {
          *local_10 = *local_10 + *(int *)(*(int *)(local_14[0xf] + 0x10) + 0x10);
        }
      }
      DAT_004611f0 = 1;
      iVar3 = FUN_0042b005((int)param_1,local_14,&local_8);
      DAT_004611f0 = 0;
      if (iVar3 == 0) {
        if (*local_14 != 0) {
          local_10[6] = local_10[6] | 0x10000;
        }
      }
      else {
        local_10[2] = local_8;
        if ((DAT_00461f44 == 1) || (DAT_00461f44 == 2)) {
          local_10[3] = local_10[2] - (*local_10 + 1);
        }
        else {
          local_10[3] = local_10[2] - *local_10;
        }
      }
    }
    else {
      local_10[0x11] = local_10[0x11] | 0x40000;
      local_10[0x12] = local_14[6];
      local_10 = local_10 + 0xb;
    }
    local_10 = local_10 + -0xb;
  }
  return;
}


/* ==== FUN_0042ac5f @ 0042ac5f ==== */

void __cdecl FUN_0042ac5f(int *param_1)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  uint *puVar6;
  int local_2c;
  int local_18;
  int local_14;
  
  bVar1 = false;
  while (!bVar1) {
    bVar1 = true;
    for (local_14 = 0; local_14 < *param_1; local_14 = local_14 + 1) {
      puVar6 = (uint *)(param_1[10] + local_14 * 0x2c);
      if (((puVar6[6] & 0x2000) == 0) && ((puVar6[6] & 0x100) == 0)) {
        iVar3 = FUN_0042b501(puVar6[2],puVar6[4]);
        iVar4 = FUN_0042b501(puVar6[3],puVar6[4]);
        if (puVar6[5] == 0) {
          local_2c = 0;
        }
        else {
          local_2c = FUN_0042b501(puVar6[3],puVar6[5]);
        }
        bVar2 = false;
        if (((puVar6[6] & 2) == 0) || (iVar3 == 0)) {
          if (((puVar6[6] & 2) == 0) && (((puVar6[6] & 1) != 0 && (iVar4 != 0)))) {
            bVar2 = true;
          }
          else if (((puVar6[6] & 3) != 0) && (local_2c != 0)) {
            bVar2 = true;
          }
        }
        else {
          bVar2 = true;
        }
        if ((DAT_00457b94 == '\0') || (!bVar2)) {
          bVar1 = false;
          puVar6[6] = puVar6[6] | 0x100;
          puVar6[6] = puVar6[6] & 0xfffffdff;
          for (local_18 = 0; local_18 < *param_1; local_18 = local_18 + 1) {
            if ((local_18 != local_14) &&
               (puVar5 = (uint *)(param_1[10] + local_18 * 0x2c), (puVar5[6] & 0x10000) == 0)) {
              if ((*puVar6 < *puVar5) || (puVar5[2] <= *puVar6)) {
                if ((puVar5[2] <= *puVar6) && (*puVar6 < *puVar5)) {
                  puVar5[3] = puVar5[3] - 1;
                }
              }
              else {
                puVar5[3] = puVar5[3] + 1;
              }
            }
          }
        }
        if (((((puVar6[6] & 3) != 0) && ((puVar6[6] & 0x100) == 0)) && (iVar3 == 0)) &&
           (local_2c != 0)) {
          puVar6[6] = puVar6[6] | 0x200;
        }
      }
    }
  }
  iVar3 = param_1[10];
  if (((*(uint *)(iVar3 + 0x18) & 0x2000) == 0) && ((*(uint *)(iVar3 + 0x18) & 0x100) != 0)) {
    *(int *)(iVar3 + 0x1c) = *(int *)(iVar3 + 0x1c) + 1;
    param_1[2] = param_1[2] + 1;
  }
  for (local_14 = 1; local_14 < *param_1; local_14 = local_14 + 1) {
    iVar3 = param_1[10] + local_14 * 0x2c;
    if ((*(uint *)(iVar3 + 0x18) & 0x2000) == 0) {
      if ((*(uint *)(iVar3 + 0x18) & 0x100) == 0) {
        if ((*(uint *)(iVar3 + 0x18) & 0x40000) == 0) {
          *(undefined4 *)(iVar3 + 0x1c) =
               *(undefined4 *)(param_1[10] + 0x1c + (local_14 + -1) * 0x2c);
        }
        else {
          *(int *)(iVar3 + 0x1c) =
               *(int *)(iVar3 + 0x1c) + *(int *)(param_1[10] + 0x1c + (local_14 + -1) * 0x2c);
        }
      }
      else {
        if ((*(uint *)(iVar3 + 0x18) & 0x40000) == 0) {
          *(int *)(iVar3 + 0x1c) = *(int *)(param_1[10] + 0x1c + (local_14 + -1) * 0x2c) + 1;
        }
        else {
          *(int *)(iVar3 + 0x1c) =
               *(int *)(iVar3 + 0x1c) + 1 + *(int *)(param_1[10] + 0x1c + (local_14 + -1) * 0x2c);
        }
        param_1[2] = param_1[2] + 1;
      }
    }
  }
  return;
}


/* ==== FUN_0042b005 @ 0042b005 ==== */

undefined4 __cdecl FUN_0042b005(int param_1,undefined4 *param_2,uint *param_3)

{
  uint *s;
  int *piVar1;
  char cVar2;
  undefined4 uVar3;
  undefined3 extraout_var;
  undefined4 *puVar4;
  uint local_20;
  int local_14;
  int local_10;
  
  s = (uint *)*param_2;
  if (s == (uint *)0x0) {
    uVar3 = 0;
  }
  else {
    if (__mb_cur_max < 2) {
      local_20 = *(ushort *)(_pctype + (char)*s * 2) & 0x103;
    }
    else {
      local_20 = _isctype((int)(char)*s,0x103);
    }
    if (local_20 == 0) {
      cVar2 = strchr((char *)s,0x24);
      if ((char *)CONCAT31(extraout_var,cVar2) == (char *)0x0) {
        thunk_FUN_00409a25(s_Syntax_error_in_expression_0045a8bc);
        return 0;
      }
      sscanf((char *)CONCAT31(extraout_var,cVar2),s___lx__0045a8d8,param_3);
      if (param_2[0xf] == 0) {
        piVar1 = *(int **)(param_1 + 0x1c);
        if ((piVar1[2] & 0x20000U) == 0) {
          *param_3 = *param_3 + piVar1[4] + *(int *)(param_2[0xe] + 4);
        }
        else {
          local_10 = 0;
          for (local_14 = *(int *)(*piVar1 + 0x20); local_14 != 0;
              local_14 = *(int *)(local_14 + 0x44)) {
            if (*(uint *)(local_14 + 0x30) <= *param_3) {
              local_10 = local_10 + *(int *)(local_14 + 0x34);
            }
          }
          *param_3 = *param_3 + ((piVar1[4] + *(int *)(param_2[0xe] + 8)) - local_10);
        }
      }
      else {
        *param_3 = *param_3 + *(int *)(*(int *)(param_2[0xf] + 0x10) + 0x10);
      }
    }
    else {
      DAT_00461dbc = param_2[0xb];
      DAT_00461ddc = param_2[0xc];
      if (param_2[0xd] == 0) {
        DAT_00461f00 = 0;
      }
      else {
        DAT_00461f00 = param_2[0xd];
      }
      DAT_00457b74 = param_2[0xd] != 0;
      puVar4 = thunk_FUN_0042c8ba(s,0);
      if (puVar4 == (undefined4 *)0x0) {
        return 0;
      }
      *param_3 = puVar4[4];
    }
    uVar3 = 1;
  }
  return uVar3;
}


/* ==== FUN_0042b1d5 @ 0042b1d5 ==== */

void __cdecl FUN_0042b1d5(int param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  int *piVar3;
  int *local_18;
  undefined *local_10;
  
  puVar1 = *(undefined **)(param_1 + 0x38);
  if (puVar1 != (undefined *)0x0) {
    local_18 = *(int **)(puVar1 + 0x24);
    while (local_18 != (int *)0x0) {
      if (*local_18 != 0) {
        thunk_FUN_0042e1ce((undefined *)*local_18);
      }
      local_10 = (undefined *)local_18[0xd];
      while (local_10 != (undefined *)0x0) {
        puVar2 = *(undefined **)(local_10 + 4);
        thunk_FUN_0042e1ce(local_10);
        local_10 = puVar2;
      }
      piVar3 = (int *)local_18[0x10];
      thunk_FUN_0042e1ce((undefined *)local_18);
      local_18 = piVar3;
    }
    if (*(int *)(puVar1 + 0x28) != 0) {
      thunk_FUN_0042e1ce(*(undefined **)(puVar1 + 0x28));
    }
    thunk_FUN_0042e1ce(puVar1);
    *(undefined4 *)(param_1 + 0x38) = 0;
  }
  return;
}


/* ==== FUN_0042b28f @ 0042b28f ==== */

void FUN_0042b28f(void)

{
  undefined *puVar1;
  int *piVar2;
  int *local_24;
  int local_1c;
  int local_18;
  int local_14;
  undefined *local_10;
  int local_8;
  
  for (local_18 = 0; local_18 < 0x7d3; local_18 = local_18 + 1) {
    for (local_14 = *(int *)(&DAT_00463f48 + local_18 * 4); local_14 != 0;
        local_14 = *(int *)(local_14 + 0x10)) {
      for (local_1c = *(int *)(local_14 + 8); local_1c != 0; local_1c = *(int *)(local_1c + 0x74)) {
        for (local_8 = *(int *)(local_1c + 0x18); local_8 != 0; local_8 = *(int *)(local_8 + 0x44))
        {
          if (*(int *)(local_8 + 0x38) != 0) {
            local_24 = *(int **)(*(int *)(local_8 + 0x38) + 0x24);
            while (local_24 != (int *)0x0) {
              if (*local_24 != 0) {
                thunk_FUN_0042e1ce((undefined *)*local_24);
              }
              local_10 = (undefined *)local_24[0xd];
              while (local_10 != (undefined *)0x0) {
                puVar1 = *(undefined **)(local_10 + 4);
                thunk_FUN_0042e1ce(local_10);
                local_10 = puVar1;
              }
              piVar2 = (int *)local_24[0x10];
              thunk_FUN_0042e1ce((undefined *)local_24);
              local_24 = piVar2;
            }
            *(undefined4 *)(*(int *)(local_8 + 0x38) + 0x24) = 0;
            *(undefined4 *)(*(int *)(local_8 + 0x38) + 4) = **(undefined4 **)(local_8 + 0x38);
            *(undefined4 *)(*(int *)(local_8 + 0x38) + 0x14) = 0;
            *(undefined4 *)(*(int *)(local_8 + 0x38) + 0x10) = 0;
            *(undefined4 *)(*(int *)(local_8 + 0x38) + 0xc) = 0;
            *(undefined4 *)(*(int *)(local_8 + 0x38) + 8) = 0;
            **(undefined4 **)(local_8 + 0x38) = 0;
          }
        }
        for (local_8 = *(int *)(local_1c + 0x24); local_8 != 0; local_8 = *(int *)(local_8 + 0x44))
        {
          if (*(int *)(local_8 + 0x38) != 0) {
            local_24 = *(int **)(*(int *)(local_8 + 0x38) + 0x24);
            while (local_24 != (int *)0x0) {
              if (*local_24 != 0) {
                thunk_FUN_0042e1ce((undefined *)*local_24);
              }
              local_10 = (undefined *)local_24[0xd];
              while (local_10 != (undefined *)0x0) {
                puVar1 = *(undefined **)(local_10 + 4);
                thunk_FUN_0042e1ce(local_10);
                local_10 = puVar1;
              }
              piVar2 = (int *)local_24[0x10];
              thunk_FUN_0042e1ce((undefined *)local_24);
              local_24 = piVar2;
            }
            *(undefined4 *)(*(int *)(local_8 + 0x38) + 0x24) = 0;
            *(undefined4 *)(*(int *)(local_8 + 0x38) + 4) = **(undefined4 **)(local_8 + 0x38);
            *(undefined4 *)(*(int *)(local_8 + 0x38) + 0x14) = 0;
            *(undefined4 *)(*(int *)(local_8 + 0x38) + 0x10) = 0;
            *(undefined4 *)(*(int *)(local_8 + 0x38) + 0xc) = 0;
            *(undefined4 *)(*(int *)(local_8 + 0x38) + 8) = 0;
            **(undefined4 **)(local_8 + 0x38) = 0;
          }
        }
      }
    }
  }
  return;
}


/* ==== FUN_0042b501 @ 0042b501 ==== */

undefined4 __cdecl FUN_0042b501(uint param_1,int param_2)

{
  if (param_2 < -0x57) {
    if (param_2 == -0x58) {
      if ((-0x81 < (int)param_1) && ((int)param_1 < 0x80)) {
        return 1;
      }
      if ((0xff7f < (int)param_1) && ((int)param_1 < 0x10000)) {
        return 1;
      }
      return 0;
    }
    if (param_2 == -0x5eb) {
      if ((-0x4001 < (int)param_1) && ((int)param_1 < 0x4000)) {
        return 1;
      }
      if (0xffffbfff < param_1) {
        return 1;
      }
      return 0;
    }
switchD_0042b546_caseD_ffffffb4:
    thunk_FUN_004098b0(s_Invalid_operand_size_0045a8e0);
  }
  else {
    switch(param_2) {
    case 8:
      if (0xff < param_1) {
        return 0;
      }
      break;
    case 0xc:
      if (0xfff < param_1) {
        return 0;
      }
      break;
    case 0x45:
      if ((param_1 & DAT_00461f70) != 0) {
        param_1 = param_1 | ~(DAT_00461f70 - 1);
      }
      if (((int)param_1 < -0x100) || (0xff < (int)param_1)) {
        return 0;
      }
      break;
    case -0x4d:
      if (((param_1 == 0) || (param_1 == 0x40)) ||
         ((((int)param_1 < -0x40 || (0x3f < (int)param_1)) &&
          (((int)param_1 < 0x7ffc0 || (0x7ffff < (int)param_1)))))) {
        return 0;
      }
      break;
    default:
      goto switchD_0042b546_caseD_ffffffb4;
    case -0x37:
      if ((((int)param_1 < -0x20) || (0x1f < (int)param_1)) &&
         (((int)param_1 < 0xffe0 || (0xffff < (int)param_1)))) {
        return 0;
      }
      break;
    case -0xf:
      if (((int)param_1 < -0x4000) || (0x3fff < (int)param_1)) {
        return 0;
      }
    }
  }
  return 1;
}


/* ==== FUN_0042bc50 @ 0042bc50 ==== */

undefined4 * __cdecl FUN_0042bc50(uint *param_1,int param_2,int *param_3,int param_4)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  int *local_14;
  
  local_14 = (int *)0x0;
  if (param_4 != 0) {
    local_14 = *(int **)(DAT_00461de8 + param_2 * 4);
    while ((local_14 != (int *)0x0 &&
           (((*local_14 == 0 || (*(int *)(*(int *)*local_14 + 8) != *param_3)) ||
            (*(int *)(*(int *)*local_14 + 0x10) != param_3[2]))))) {
      local_14 = (int *)local_14[5];
    }
  }
  puVar1 = (undefined4 *)thunk_FUN_0042bed4(param_1,param_3);
  if (puVar1 == (undefined4 *)0x0) {
    if (local_14 != (int *)0x0) {
      thunk_FUN_004098b0(s_Invalid_section_number_0045a948);
    }
    if ((param_2 == 0) &&
       (((char)*param_1 != s_GLOBAL_00457f88[0] ||
        (iVar3 = strcmp((char *)param_1,s_GLOBAL_00457f88), iVar3 != 0)))) {
      thunk_FUN_004098b0(s_Invalid_global_section_0045a960);
    }
    piVar2 = thunk_FUN_0042bfcb(param_1,param_2);
    piVar2 = thunk_FUN_0042c1ef((int)piVar2,param_3);
    puVar1 = thunk_FUN_0042be92(piVar2,0x1000);
    puVar1[0x11] = piVar2[6];
    piVar2[6] = (int)puVar1;
    if (param_4 != 0) {
      puVar4 = (undefined4 *)thunk_FUN_0042e170(0x18);
      *puVar4 = puVar1;
      puVar4[3] = 0;
      puVar4[2] = 0;
      puVar4[1] = 0;
      puVar4[4] = DAT_00461e68;
      puVar4[5] = *(undefined4 *)(DAT_00461de8 + param_2 * 4);
      *(undefined4 **)(DAT_00461de8 + param_2 * 4) = puVar4;
    }
    piVar2[10] = piVar2[10] + 1;
    DAT_0046129c = DAT_0046129c + 1;
  }
  else if ((local_14 == (int *)0x0) && (param_4 != 0)) {
    piVar2 = (int *)thunk_FUN_0042e170(0x18);
    *piVar2 = (int)puVar1;
    uVar5 = puVar1[5];
    if (uVar5 < (uint)puVar1[4]) {
      uVar5 = puVar1[4];
    }
    piVar2[3] = uVar5;
    piVar2[2] = uVar5;
    piVar2[1] = uVar5;
    piVar2[4] = DAT_00461e68;
    piVar2[5] = *(int *)(DAT_00461de8 + param_2 * 4);
    *(int **)(DAT_00461de8 + param_2 * 4) = piVar2;
  }
  return puVar1;
}


/* ==== FUN_0042be92 @ 0042be92 ==== */

undefined4 * __cdecl FUN_0042be92(undefined4 param_1,undefined4 param_2)

{
  undefined4 *dst;
  
  dst = (undefined4 *)thunk_FUN_0042e170(0x48);
  memset(dst,0,0x48);
  *dst = param_1;
  dst[2] = param_2;
  dst[0x10] = dst;
  return dst;
}


/* ==== FUN_0042bed4 @ 0042bed4 ==== */

undefined4 __cdecl FUN_0042bed4(uint *param_1,int *param_2)

{
  int iVar1;
  uint local_214 [129];
  int local_10;
  undefined4 *local_c;
  uint local_8;
  
  if (DAT_00461214 != '\0') {
    strcpy((char *)local_214,(char *)param_1);
    thunk_FUN_00430037((char *)local_214);
    param_1 = local_214;
  }
  local_8 = thunk_FUN_0042e3f9((char *)param_1);
  DAT_00461e84 = *(undefined4 **)(&DAT_00463f48 + local_8 * 4);
  local_c = DAT_00461e84;
  while( true ) {
    if (local_c == (undefined4 *)0x0) {
      return 0;
    }
    DAT_00461e84 = local_c;
    if (((char)*param_1 == *(char *)*local_c) &&
       (iVar1 = strcmp((char *)param_1,(char *)*local_c), iVar1 == 0)) break;
    local_c = (undefined4 *)local_c[4];
  }
  local_10 = local_c[2];
  while( true ) {
    if (local_10 == 0) {
      return 0;
    }
    if ((*(int *)(local_10 + 8) == *param_2) && (*(int *)(local_10 + 0x10) == param_2[2])) break;
    local_10 = *(int *)(local_10 + 0x74);
  }
  return *(undefined4 *)(local_10 + 0x18);
}


/* ==== FUN_0042bfcb @ 0042bfcb ==== */

int * __cdecl FUN_0042bfcb(uint *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int local_210;
  uint local_20c [129];
  int *local_8;
  
  if (DAT_00461214 != '\0') {
    strcpy((char *)local_20c,(char *)param_1);
    thunk_FUN_00430037((char *)local_20c);
    param_1 = local_20c;
  }
  if (((DAT_00461e84 != (int *)0x0) && ((char)*param_1 == *(char *)*DAT_00461e84)) &&
     (iVar1 = strcmp((char *)param_1,(char *)*DAT_00461e84), iVar1 == 0)) {
    return DAT_00461e84;
  }
  local_8 = (int *)thunk_FUN_0042e170(0x14);
  uVar2 = strlen((char *)param_1);
  iVar1 = thunk_FUN_0042e170(uVar2 + 1);
  *local_8 = iVar1;
  strcpy((char *)*local_8,(char *)param_1);
  if (param_2 < 1) {
    local_210 = param_2;
  }
  else {
    DAT_00461298 = DAT_00461298 + 1;
    local_210 = DAT_00461298;
  }
  local_8[1] = local_210;
  local_8[2] = 0;
  local_8[3] = 0;
  local_8[4] = 0;
  if (DAT_00461e84 == (int *)0x0) {
    uVar2 = thunk_FUN_0042e3f9((char *)param_1);
    *(int **)(&DAT_00463f48 + uVar2 * 4) = local_8;
  }
  else if (DAT_00461e84[4] == 0) {
    DAT_00461e84[4] = (int)local_8;
  }
  else {
    local_8[4] = DAT_00461e84[4];
    DAT_00461e84[4] = (int)local_8;
  }
  return local_8;
}


/* ==== FUN_0042c13b @ 0042c13b ==== */

undefined4 * __cdecl FUN_0042c13b(uint *param_1)

{
  int iVar1;
  uint local_210 [129];
  undefined4 *local_c;
  uint local_8;
  
  if (DAT_00461214 != '\0') {
    strcpy((char *)local_210,(char *)param_1);
    thunk_FUN_00430037((char *)local_210);
    param_1 = local_210;
  }
  local_8 = thunk_FUN_0042e3f9((char *)param_1);
  DAT_00461e84 = *(undefined4 **)(&DAT_00463f48 + local_8 * 4);
  local_c = DAT_00461e84;
  while( true ) {
    if (local_c == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    DAT_00461e84 = local_c;
    if (((char)*param_1 == *(char *)*local_c) &&
       (iVar1 = strcmp((char *)param_1,(char *)*local_c), iVar1 == 0)) break;
    local_c = (undefined4 *)local_c[4];
  }
  return local_c;
}


/* ==== FUN_0042c1ef @ 0042c1ef ==== */

int * __cdecl FUN_0042c1ef(int param_1,int *param_2)

{
  int *local_8;
  
  local_8 = (int *)thunk_FUN_0042c32f(param_1,param_2);
  if (local_8 == (int *)0x0) {
    local_8 = (int *)thunk_FUN_0042e170(0x78);
    *local_8 = param_1;
    local_8[2] = *param_2;
    local_8[3] = param_2[1];
    local_8[4] = param_2[2];
    local_8[5] = param_2[3];
    local_8[1] = 0;
    local_8[9] = 0;
    local_8[8] = 0;
    local_8[7] = 0;
    local_8[6] = 0;
    local_8[0xd] = 0;
    local_8[0xc] = 0;
    local_8[0xb] = 0;
    local_8[10] = 0;
    local_8[0x16] = 0;
    local_8[0x13] = 0;
    local_8[0x12] = 0;
    local_8[0xf] = 0;
    local_8[0xe] = 0;
    local_8[0x14] = 0;
    local_8[0x15] = 0;
    local_8[0x18] = 0;
    local_8[0x19] = 0;
    local_8[0x1a] = 0;
    local_8[0x1b] = 0;
    local_8[0x1c] = 0;
    local_8[0x1d] = *(int *)(param_1 + 8);
    *(int **)(param_1 + 8) = local_8;
  }
  return local_8;
}


/* ==== FUN_0042c32f @ 0042c32f ==== */

int __cdecl FUN_0042c32f(int param_1,int *param_2)

{
  int local_8;
  
  for (local_8 = *(int *)(param_1 + 8);
      (local_8 != 0 &&
      ((*(int *)(local_8 + 8) != *param_2 || (*(int *)(local_8 + 0x10) != param_2[2]))));
      local_8 = *(int *)(local_8 + 0x74)) {
  }
  return local_8;
}


/* ==== FUN_0042c373 @ 0042c373 ==== */

int * __cdecl FUN_0042c373(uint *param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int *local_8;
  
  local_8 = thunk_FUN_0042c429(param_1);
  piVar1 = DAT_00461dcc;
  if (local_8 == (int *)0x0) {
    local_8 = (int *)thunk_FUN_0042e170(0x10);
    uVar2 = strlen((char *)param_1);
    iVar3 = thunk_FUN_0042e170(uVar2 + 1);
    *local_8 = iVar3;
    strcpy((char *)*local_8,(char *)param_1);
    if (DAT_00461214 != '\0') {
      thunk_FUN_00430037((char *)*local_8);
    }
    local_8[1] = 0;
    local_8[2] = 0;
    local_8[3] = 0;
    piVar1 = local_8;
    if (DAT_00461e80 != 0) {
      *(int **)(DAT_00461e80 + 0xc) = local_8;
      piVar1 = DAT_00461dcc;
    }
  }
  DAT_00461dcc = piVar1;
  return local_8;
}


/* ==== FUN_0042c429 @ 0042c429 ==== */

undefined4 * __cdecl FUN_0042c429(uint *param_1)

{
  int iVar1;
  undefined4 *local_20c;
  uint local_208 [129];
  
  if (DAT_00461214 != '\0') {
    strcpy((char *)local_208,(char *)param_1);
    thunk_FUN_00430037((char *)local_208);
    param_1 = local_208;
  }
  DAT_00461e80 = DAT_00461dcc;
  local_20c = DAT_00461dcc;
  while( true ) {
    if (local_20c == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    DAT_00461e80 = local_20c;
    if (((char)*param_1 == *(char *)*local_20c) &&
       (iVar1 = strcmp((char *)param_1,(char *)*local_20c), iVar1 == 0)) break;
    local_20c = (undefined4 *)local_20c[3];
  }
  return local_20c;
}


/* ==== FUN_0042c4e2 @ 0042c4e2 ==== */

undefined4 * __cdecl FUN_0042c4e2(int param_1,int *param_2,int param_3)

{
  undefined4 *local_8;
  
  local_8 = (undefined4 *)thunk_FUN_0042c67b(param_1,param_2);
  if (local_8 == (undefined4 *)0x0) {
    local_8 = thunk_FUN_0042c58b(param_1,param_2);
    local_8[0xe] = *(undefined4 *)(param_1 + 8);
    *(undefined4 **)(param_1 + 8) = local_8;
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
  }
  else if (param_3 != 0) {
    if (((local_8[1] & 0x1000000) != 0) && (DAT_00461274 == '\0')) {
      thunk_FUN_00409d88(s_Remapping_region_0045a978);
    }
    local_8[1] = local_8[1] | 0x1000000;
    local_8[4] = param_2[1];
  }
  return local_8;
}


/* ==== FUN_0042c58b @ 0042c58b ==== */

undefined4 * __cdecl FUN_0042c58b(undefined4 param_1,int *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)thunk_FUN_0042e170(0x3c);
  *puVar1 = param_1;
  puVar1[2] = 0;
  puVar1[1] = 0;
  puVar1[3] = *param_2;
  puVar1[4] = param_2[1];
  puVar1[5] = param_2[2];
  puVar1[6] = param_2[3];
  puVar1[0xb] = 0;
  puVar1[10] = 0;
  puVar1[9] = 0;
  puVar1[7] = 0;
  if (*param_2 == 0x1c) {
    if (param_2[1] == 0x1c) {
      puVar1[8] = DAT_00461f78;
    }
    else if (DAT_00461f44 == 5) {
      puVar1[8] = DAT_00461f78;
    }
    else {
      puVar1[8] = (&PTR_DAT_00458314)[param_2[1]];
    }
  }
  else {
    puVar1[8] = DAT_00461f74;
  }
  puVar1[0xc] = 0;
  puVar1[0xd] = 0;
  puVar1[0xe] = 0;
  return puVar1;
}


/* ==== FUN_0042c67b @ 0042c67b ==== */

int __cdecl FUN_0042c67b(int param_1,int *param_2)

{
  int local_8;
  
  local_8 = *(int *)(param_1 + 8);
  while( true ) {
    if (local_8 == 0) {
      return 0;
    }
    if ((*(int *)(local_8 + 0xc) == *param_2) && (*(int *)(local_8 + 0x14) == param_2[2])) break;
    local_8 = *(int *)(local_8 + 0x38);
  }
  return local_8;
}


/* ==== FUN_0042c6c1 @ 0042c6c1 ==== */

int * __cdecl FUN_0042c6c1(int *param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  
  piVar1 = thunk_FUN_0042c8ba((uint *)*param_1,1);
  if (piVar1 != (int *)0x0) {
    if (piVar1[0x12] == 0) {
      thunk_FUN_00409bfd(s_Duplicate_special_symbol_0045a98c,*param_1);
      return piVar1;
    }
    if (param_1[0x12] == piVar1[0x12]) {
      if ((piVar1[0x12] != 0) && (*(int *)(**(int **)piVar1[0x12] + 4) != 0)) {
        thunk_FUN_00409bfd(s_Duplicate_local_symbol_0045a9c0,*param_1);
        return piVar1;
      }
      thunk_FUN_00409bfd(s_Duplicate_global_symbol_0045a9a8,*param_1);
      return piVar1;
    }
    if (((param_1[10] & 0x80U) != 0) && ((piVar1[10] & 0x80U) != 0)) {
      if (DAT_00461dbc == 0) {
        return piVar1;
      }
      if ((*(uint *)(DAT_00461dbc + 4) & 2) != 0) {
        return piVar1;
      }
      thunk_FUN_00409f4d(s_Duplicate_XDEF_symbol_0045a9d8,*param_1);
      return piVar1;
    }
    if (((param_1[10] & 0x40U) != 0) && ((piVar1[10] & 0x40U) != 0)) {
      if (DAT_00461dbc == 0) {
        return piVar1;
      }
      if ((*(uint *)(DAT_00461dbc + 4) & 2) != 0) {
        return piVar1;
      }
      thunk_FUN_00409f4d(s_Duplicate_global_symbol_0045a9f0,*param_1);
      return piVar1;
    }
  }
  piVar2 = (int *)thunk_FUN_0042e170(0x68);
  piVar1 = param_1;
  piVar5 = piVar2;
  for (iVar4 = 0x1a; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar5 = *piVar1;
    piVar1 = piVar1 + 1;
    piVar5 = piVar5 + 1;
  }
  uVar3 = strlen((char *)*param_1);
  iVar4 = thunk_FUN_0042e170(uVar3 + 1);
  *piVar2 = iVar4;
  strcpy((char *)*piVar2,(char *)*param_1);
  if (DAT_00461214 != '\0') {
    thunk_FUN_00430037((char *)*piVar2);
  }
  DAT_004612dc = DAT_004612dc + 1;
  if (DAT_00461e88 == 0) {
    uVar3 = thunk_FUN_0042e3f9((char *)*piVar2);
    *(int **)(&DAT_00461ff8 + uVar3 * 4) = piVar2;
  }
  else {
    piVar2[0x18] = *(int *)(DAT_00461e88 + 0x60);
    *(int **)(DAT_00461e88 + 0x60) = piVar2;
  }
  return piVar2;
}


