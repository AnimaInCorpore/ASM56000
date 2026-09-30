/* fixup: 38 functions from DSPLNK */

/* ==== FUN_0040cac2 @ 0040cac2 ==== */

void FUN_0040cac2(void)

{
  while (DAT_00461f2c != DAT_00461f28) {
    DAT_00461f2c = DAT_00461f2c + -1;
    thunk_FUN_0042e1ce((undefined *)*DAT_00461f2c);
  }
  return;
}


/* ==== FUN_0040d4e0 @ 0040d4e0 ==== */

void FUN_0040d4e0(void)

{
  if (DAT_0046125c != '\0') {
    fprintf(&DAT_0045d670,s__s__Beginning_section_and_symbol_00456300,PTR_s_dsplnk_00457ed0);
  }
  FUN_0040ebca();
  DAT_00461dbc = 0;
  if (DAT_00461f40 != (void *)0x0) {
    thunk_FUN_00423710(0);
  }
  if (DAT_00461274 == '\0') {
    FUN_0040d5e0();
  }
  else {
    FUN_0040e2bd();
    FUN_0040d5e0();
    do {
      DAT_0046127c = '\0';
      thunk_FUN_0042a84c();
      if (DAT_0046127c != '\0') {
        FUN_0040e501();
        if (DAT_00461f40 != (void *)0x0) {
          rewind(DAT_00461f40);
          thunk_FUN_00423710(0);
        }
        FUN_0040d5e0();
      }
    } while (DAT_0046127c != '\0');
    FUN_0040e501();
    if (DAT_00461f40 != (void *)0x0) {
      rewind(DAT_00461f40);
      thunk_FUN_00423710(0);
    }
    FUN_0040d5e0();
    thunk_FUN_0042b28f();
  }
  if (DAT_00461f40 != (void *)0x0) {
    fclose(DAT_00461f40);
  }
  return;
}


/* ==== FUN_0040d5e0 @ 0040d5e0 ==== */

void FUN_0040d5e0(void)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int *local_40;
  undefined4 local_3c;
  int *local_34;
  int local_28;
  int local_1c;
  int local_18;
  int local_14;
  int *local_8;
  
  thunk_FUN_0040df91();
  for (local_1c = DAT_00461dcc; local_1c != 0; local_1c = *(int *)(local_1c + 0xc)) {
    DAT_00461e80 = local_1c;
  }
  *(int *)(DAT_00461e80 + 0xc) = DAT_00461dcc;
  for (local_1c = *(int *)(DAT_00461dcc + 0xc); local_1c != 0; local_1c = *(int *)(local_1c + 0xc))
  {
    DAT_00461dd0 = local_1c;
    piVar3 = (int *)FUN_0040e832(local_1c);
    local_18 = -1;
    local_34 = piVar3;
    if (local_1c == DAT_00461dcc) {
      for (local_14 = 0; local_14 < 8; local_14 = local_14 + 1) {
        if (*(int *)(&DAT_00461df8 + local_14 * 4) != 0) {
          thunk_FUN_0042d7fa(*(undefined **)(&DAT_00461df8 + local_14 * 4));
          *(undefined4 *)(&DAT_00461df8 + local_14 * 4) = 0;
        }
      }
    }
    for (; (local_34 != (int *)0x0 && (*local_34 != 0)); local_34 = local_34 + 1) {
      piVar1 = (int *)*local_34;
      DAT_00461dd4 = piVar1;
      DAT_00461dd8 = thunk_FUN_0042c4e2(DAT_00461dcc,piVar1 + 3,0);
      iVar4 = thunk_FUN_0042f22f(piVar1[3]);
      if (piVar1[5] != local_18) {
        local_18 = piVar1[5];
        FUN_0040dd4a(local_18);
        DAT_00461e18 = 0;
        DAT_00461e1c = 0;
        for (local_14 = 0; local_14 < 8; local_14 = local_14 + 1) {
          if ((*(int *)(&DAT_00461df8 + local_14 * 4) != 0) && (local_1c != DAT_00461dcc)) {
            thunk_FUN_0042d7fa(*(undefined **)(&DAT_00461df8 + local_14 * 4));
          }
          if (local_1c == DAT_00461dcc) {
            local_3c = *(undefined4 *)(DAT_00461e28 + local_14 * 4);
          }
          else {
            local_3c = 0;
          }
          *(undefined4 *)(&DAT_00461df8 + local_14 * 4) = local_3c;
        }
      }
      piVar5 = (int *)FUN_0040e8ba((int)piVar1);
      local_8 = piVar5;
      if (piVar5 != (int *)0x0) {
        for (; *local_8 != 0; local_8 = local_8 + 1) {
          FUN_0040ed4c((int *)*local_8,iVar4);
        }
        thunk_FUN_0042e1ce((undefined *)piVar5);
      }
      piVar5 = (int *)FUN_0040e981((int)piVar1);
      local_8 = piVar5;
      if (piVar5 != (int *)0x0) {
        for (; *local_8 != 0; local_8 = local_8 + 1) {
          FUN_0040ed4c((int *)*local_8,iVar4);
        }
        thunk_FUN_0042e1ce((undefined *)piVar5);
      }
      piVar5 = (int *)FUN_0040eb31((int)piVar1);
      if (piVar5 != (int *)0x0) {
        if (iVar4 == 3) {
          FUN_0040ddde(piVar1);
        }
        if ((piVar1[1] & 0x820000U) == 0) {
          local_40 = (int *)0x0;
        }
        else {
          local_40 = (int *)FUN_0040ea59((int)piVar1);
        }
        DAT_00461e18 = *(undefined4 *)(&DAT_00461df8 + iVar4 * 4);
        DAT_00461e1c = DAT_00461e18;
        if (local_40 != (int *)0x0) {
          for (local_8 = local_40; *local_8 != 0; local_8 = local_8 + 1) {
            if ((*(uint *)(*local_8 + 8) & 0x800000) != 0) {
              FUN_0040f04a((int *)*local_8,iVar4);
            }
          }
        }
        local_8 = piVar5;
        if ((piVar1[2] & 0x200U) != 0) {
          for (; *local_8 != 0; local_8 = local_8 + 1) {
            if ((*(uint *)(*local_8 + 0xc) & 0x200) != 0) {
              FUN_0040f17f((int *)*local_8,iVar4);
            }
          }
        }
        DAT_00461e18 = *(undefined4 *)(&DAT_00461df8 + iVar4 * 4);
        DAT_00461e1c = DAT_00461e18;
        if (local_40 != (int *)0x0) {
          FUN_0040f3c5((int)piVar1,local_40,iVar4);
          thunk_FUN_0042e1ce((undefined *)local_40);
        }
        if ((piVar1[2] & 0x100U) != 0) {
          FUN_0040f225((int)piVar1,iVar4);
        }
        FUN_0040f58e((int)piVar1,piVar5,iVar4);
        thunk_FUN_0042e1ce((undefined *)piVar5);
      }
      if (local_1c == DAT_00461dcc) {
        for (local_14 = 0; local_14 < 8; local_14 = local_14 + 1) {
          *(undefined4 *)(DAT_00461e28 + local_14 * 4) =
               *(undefined4 *)(&DAT_00461df8 + local_14 * 4);
        }
      }
    }
    if (local_1c == DAT_00461dcc) {
      local_1c = DAT_00461e80;
      *(undefined4 *)(DAT_00461e80 + 0xc) = 0;
    }
    thunk_FUN_0042e1ce((undefined *)piVar3);
  }
  thunk_FUN_0042d825();
  if (DAT_0046120c != '\0') {
    FUN_0041006f();
  }
  thunk_FUN_0042ceac();
  for (local_14 = 0; local_14 < 0x7d3; local_14 = local_14 + 1) {
    for (local_28 = *(int *)(&DAT_00461ff8 + local_14 * 4); local_28 != 0;
        local_28 = *(int *)(local_28 + 0x60)) {
      uVar2 = *(uint *)(local_28 + 0x28);
      if ((uVar2 & 0x20000) == 0) {
        if (((uVar2 & 0x1000) != 0) && ((uVar2 & 0x4000) == 0)) {
          if (DAT_00461248 == '\0') {
            if (DAT_00461274 != '\0') {
              *(undefined4 *)(local_28 + 8) = *(undefined4 *)(local_28 + 0x18);
              *(undefined4 *)(local_28 + 0xc) = *(undefined4 *)(local_28 + 0x1c);
              *(undefined4 *)(local_28 + 0x10) = *(undefined4 *)(local_28 + 0x20);
              *(undefined4 *)(local_28 + 0x14) = *(undefined4 *)(local_28 + 0x24);
            }
            if (((*(int *)(local_28 + 0x50) != 0) &&
                (*(int *)(local_28 + 0x10) =
                      *(int *)(local_28 + 0x10) +
                      *(int *)(*(int *)(*(int *)(local_28 + 0x50) + 0x3c) + 0x18),
                *(int *)(*(int *)(local_28 + 0x50) + 0x38) != 0)) &&
               (*(int *)(*(int *)(*(int *)(local_28 + 0x50) + 0x38) + 0x28) != 0)) {
              piVar3 = *(int **)(*(int *)(local_28 + 0x50) + 0x38);
              *(int *)(local_28 + 0x10) =
                   *(int *)(local_28 + 0x10) + *(int *)(piVar3[10] + 0x1c + (*piVar3 + -1) * 0x2c);
            }
            if ((*(uint *)(*(int *)(local_28 + 0x4c) + 8) & 0x20000) == 0) {
              *(int *)(local_28 + 0x10) =
                   *(int *)(local_28 + 0x10) +
                   *(int *)(*(int *)(local_28 + 0x4c) + 0x10) +
                   *(int *)(*(int *)(local_28 + 0x54) + 4);
              if ((DAT_00461f44 == 6) && (*(int *)(local_28 + 0x2c) == 0)) {
                *(uint *)(local_28 + 0xc) =
                     (*(uint *)(local_28 + 0x10) & ~DAT_00461f6c) >> ((byte)DAT_00461f58 & 0x1f) &
                     DAT_00461f6c;
              }
              iVar4 = *(int *)(*(int *)(local_28 + 0x4c) + 0x38);
              if (((*(int *)(local_28 + 0x40) != 0) && (iVar4 != 0)) &&
                 (*(int *)(iVar4 + 0x28) != 0)) {
                *(int *)(local_28 + 0x10) =
                     *(int *)(local_28 + 0x10) +
                     *(int *)(*(int *)(iVar4 + 0x28) + 0x1c +
                             (*(int *)(local_28 + 0x40) + -1) * 0x2c);
              }
            }
            else if ((*(uint *)(local_28 + 0x28) & 0x2000) == 0) {
              *(int *)(local_28 + 0x10) =
                   *(int *)(local_28 + 0x10) +
                   ((*(int *)(*(int *)(local_28 + 0x4c) + 0x10) +
                    *(int *)(*(int *)(local_28 + 0x54) + 8)) - *(int *)(local_28 + 0x44));
              iVar4 = *(int *)(*(int *)(local_28 + 0x4c) + 0x38);
              if (((*(int *)(local_28 + 0x40) != 0) && (iVar4 != 0)) &&
                 (*(int *)(iVar4 + 0x28) != 0)) {
                *(int *)(local_28 + 0x10) =
                     *(int *)(local_28 + 0x10) +
                     *(int *)(*(int *)(iVar4 + 0x28) + 0x1c +
                             (*(int *)(local_28 + 0x40) + -1) * 0x2c);
              }
            }
            else {
              *(int *)(local_28 + 0x10) =
                   *(int *)(local_28 + 0x10) - *(int *)(*(int *)(local_28 + 0x58) + 4);
              *(int *)(local_28 + 0x10) =
                   *(int *)(local_28 + 0x10) + *(int *)(**(int **)(local_28 + 0x58) + 0x10);
            }
          }
          else {
            *(int *)(local_28 + 0x10) =
                 *(int *)(local_28 + 0x10) + *(int *)(*(int *)(local_28 + 0x54) + 4);
          }
        }
      }
      else if (*(int *)(local_28 + 0x48) == 0) {
        iVar4 = FUN_0040e72e((int *)(local_28 + 0x2c));
        *(int *)(local_28 + 0x10) = iVar4;
      }
    }
  }
  if ((DAT_00461248 == '\0') && (DAT_004612cc != 0)) {
    FUN_00410668();
  }
  return;
}


/* ==== FUN_0040dd4a @ 0040dd4a ==== */

void __cdecl FUN_0040dd4a(int param_1)

{
  int *local_c;
  int local_8;
  
  for (local_c = DAT_00461e24; (local_c != (int *)0x0 && (*local_c != param_1));
      local_c = (int *)local_c[9]) {
  }
  if (local_c == (int *)0x0) {
    local_c = (int *)thunk_FUN_0042e170(0x28);
    *local_c = param_1;
    for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
      local_c[local_8 + 1] = 0;
    }
    local_c[9] = (int)DAT_00461e24;
    DAT_00461e24 = local_c;
  }
  DAT_00461e28 = local_c + 1;
  return;
}


/* ==== FUN_0040ddde @ 0040ddde ==== */

void __cdecl FUN_0040ddde(int *param_1)

{
  int *piVar1;
  int *piVar2;
  int local_20 [3];
  int local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  local_20[2] = param_1[5];
  local_14 = param_1[6];
  local_20[1] = 1;
  local_20[0] = 1;
  local_10 = thunk_FUN_0042c67b(*param_1,local_20);
  local_20[1] = 2;
  local_20[0] = 2;
  local_c = thunk_FUN_0042c67b(*param_1,local_20);
  if ((local_10 != 0) &&
     (piVar1 = (int *)FUN_0040e8ba(local_10), piVar2 = piVar1, piVar1 != (int *)0x0)) {
    while (local_8 = piVar2, *local_8 != 0) {
      FUN_0040ed4c((int *)*local_8,1);
      piVar2 = local_8 + 1;
    }
    thunk_FUN_0042e1ce((undefined *)piVar1);
  }
  if ((local_10 != 0) &&
     (piVar1 = (int *)FUN_0040e981(local_10), piVar2 = piVar1, piVar1 != (int *)0x0)) {
    while (local_8 = piVar2, *local_8 != 0) {
      FUN_0040ed4c((int *)*local_8,1);
      piVar2 = local_8 + 1;
    }
    thunk_FUN_0042e1ce((undefined *)piVar1);
  }
  if ((local_c != 0) &&
     (piVar1 = (int *)FUN_0040e8ba(local_c), piVar2 = piVar1, piVar1 != (int *)0x0)) {
    while (local_8 = piVar2, *local_8 != 0) {
      FUN_0040ed4c((int *)*local_8,2);
      piVar2 = local_8 + 1;
    }
    thunk_FUN_0042e1ce((undefined *)piVar1);
  }
  if ((local_c != 0) &&
     (piVar2 = (int *)FUN_0040e981(local_c), local_8 = piVar2, piVar2 != (int *)0x0)) {
    for (; *local_8 != 0; local_8 = local_8 + 1) {
      FUN_0040ed4c((int *)*local_8,2);
    }
    thunk_FUN_0042e1ce((undefined *)piVar2);
  }
  return;
}


/* ==== FUN_0040df91 @ 0040df91 ==== */

void FUN_0040df91(void)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  longlong lVar4;
  int local_1c;
  int local_18;
  uint local_14;
  undefined4 *local_10;
  int *local_8;
  
  for (local_18 = 0; local_18 < 0x7d3; local_18 = local_18 + 1) {
    for (local_10 = *(undefined4 **)(&DAT_00463f48 + local_18 * 4); local_10 != (undefined4 *)0x0;
        local_10 = (undefined4 *)local_10[4]) {
      for (local_1c = local_10[2]; local_1c != 0; local_1c = *(int *)(local_1c + 0x74)) {
        if (DAT_00461294 == 1) {
          *(undefined4 *)(local_1c + 0x68) = 0;
          if (*(int *)(local_1c + 0x70) == 0) {
            puVar2 = thunk_FUN_0042c4e2(DAT_00461dcc,(int *)(local_1c + 8),0);
            for (local_8 = *(int **)(local_1c + 0x18); local_8 != (int *)0x0;
                local_8 = (int *)local_8[0x11]) {
              thunk_FUN_004252ad((int)puVar2,local_8,0);
            }
          }
          if (((*(uint *)(local_1c + 4) & 0x40000) == 0) &&
             (((DAT_0046126c != '\0' || ((*(uint *)(*(int *)(local_1c + 0x70) + 4) & 0x20000) != 0))
              || ((*(int *)(*(int *)(local_1c + 0x18) + 0x38) != 0 &&
                  (**(int **)(*(int *)(local_1c + 0x18) + 0x38) != 0)))))) {
            *(uint *)(*(int *)(local_1c + 0x18) + 8) =
                 *(uint *)(*(int *)(local_1c + 0x18) + 8) | 0x20000;
            for (local_8 = *(int **)(local_1c + 0x20); local_8 != (int *)0x0;
                local_8 = *(int **)((int)local_8 + 0x44)) {
              if ((*(uint *)((int)local_8 + 8) & 0x1000) != 0) {
                *(uint *)((int)local_8 + 8) = *(uint *)((int)local_8 + 8) | 0x20000;
              }
            }
            if ((*(int *)(*(int *)(local_1c + 0x18) + 0x38) != 0) &&
               (**(int **)(*(int *)(local_1c + 0x18) + 0x38) != 0)) {
              *(uint *)(*(int *)(local_1c + 0x70) + 4) =
                   *(uint *)(*(int *)(local_1c + 0x70) + 4) | 0x800000;
            }
          }
        }
        if ((local_10[1] != -1) && (*(int *)(local_1c + 0x18) != 0)) {
          iVar1 = *(int *)(local_1c + 0x18);
          if ((DAT_00461294 == 1) && ((*(uint *)(iVar1 + 8) & 0x20000) != 0)) {
            *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) - *(int *)(local_1c + 0x3c);
            *(undefined4 *)(local_1c + 0x3c) = 0;
            *(undefined4 *)(local_1c + 0x38) = 0;
            *(undefined4 *)(iVar1 + 0x24) = 0;
            *(uint *)(*(int *)(local_1c + 0x70) + 4) =
                 *(uint *)(*(int *)(local_1c + 0x70) + 4) | 0x800000;
          }
          uVar3 = *(int *)(iVar1 + 0x14) - *(int *)(iVar1 + 0x10);
          if ((*(uint *)(local_1c + 4) & 0x200000) != 0) {
            if ((*(uint *)(local_1c + 4) & 0x2000000) == 0) {
              local_14 = *(uint *)(local_1c + 0x60);
            }
            else {
              lVar4 = _ftol();
              local_14 = (uint)lVar4;
            }
            if (local_14 < uVar3) {
              thunk_FUN_00409f4d(s_Actual_length_of_section_greater_00456330,*local_10);
            }
            else if (uVar3 < local_14) {
              *(uint *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + (local_14 - uVar3);
            }
          }
          if (DAT_00461294 == 2) {
            for (local_8 = *(int **)(local_1c + 0x18); local_8 != (int *)0x0;
                local_8 = *(int **)((int)local_8 + 0x44)) {
              thunk_FUN_0042b1d5((int)local_8);
            }
            for (local_8 = *(int **)(local_1c + 0x24); local_8 != (int *)0x0;
                local_8 = *(int **)((int)local_8 + 0x44)) {
              thunk_FUN_0042b1d5((int)local_8);
            }
          }
        }
      }
    }
  }
  return;
}


/* ==== FUN_0040e2bd @ 0040e2bd ==== */

void FUN_0040e2bd(void)

{
  int *piVar1;
  bool bVar2;
  int local_1c;
  int local_18;
  int local_14;
  int local_c;
  int local_8;
  
  for (local_14 = 0; local_14 < 0x7d3; local_14 = local_14 + 1) {
    for (local_c = *(int *)(&DAT_00463f48 + local_14 * 4); local_c != 0;
        local_c = *(int *)(local_c + 0x10)) {
      for (local_18 = *(int *)(local_c + 8); local_18 != 0; local_18 = *(int *)(local_18 + 0x74)) {
        bVar2 = false;
        if (((*(int *)(local_18 + 8) == 0) && (*(int *)(local_18 + 0x20) != 0)) &&
           ((*(uint *)(local_18 + 4) & 0x40000) == 0)) {
          bVar2 = true;
        }
        *(undefined4 *)(local_18 + 0x40) = *(undefined4 *)(local_18 + 0x38);
        *(undefined4 *)(local_18 + 0x44) = *(undefined4 *)(local_18 + 0x3c);
        for (local_8 = *(int *)(local_18 + 0x18); local_8 != 0; local_8 = *(int *)(local_8 + 0x44))
        {
          *(undefined4 *)(local_8 + 0x28) = *(undefined4 *)(local_8 + 0x10);
          *(undefined4 *)(local_8 + 0x2c) = *(undefined4 *)(local_8 + 0x14);
          piVar1 = *(int **)(local_8 + 0x38);
          if ((piVar1 != (int *)0x0) && (*piVar1 != 0)) {
            if (bVar2) {
              *(uint *)(local_8 + 8) = *(uint *)(local_8 + 8) | 0x20000;
              for (local_1c = *(int *)(local_18 + 0x20); local_1c != 0;
                  local_1c = *(int *)(local_1c + 0x44)) {
                if ((*(uint *)(local_1c + 8) & 0x1000) != 0) {
                  *(uint *)(local_1c + 8) = *(uint *)(local_1c + 8) | 0x820000;
                }
              }
            }
            piVar1[3] = 0;
            piVar1[2] = 0;
          }
        }
        for (local_8 = *(int *)(local_18 + 0x24); local_8 != 0; local_8 = *(int *)(local_8 + 0x44))
        {
          *(undefined4 *)(local_8 + 0x28) = *(undefined4 *)(local_8 + 0x10);
          *(undefined4 *)(local_8 + 0x2c) = *(undefined4 *)(local_8 + 0x14);
          piVar1 = *(int **)(local_8 + 0x38);
          if ((piVar1 != (int *)0x0) && (*piVar1 != 0)) {
            piVar1[3] = 0;
            piVar1[2] = 0;
          }
        }
        for (local_8 = *(int *)(local_18 + 0x1c); local_8 != 0; local_8 = *(int *)(local_8 + 0x44))
        {
          *(undefined4 *)(local_8 + 0x28) = *(undefined4 *)(local_8 + 0x10);
          *(undefined4 *)(local_8 + 0x2c) = *(undefined4 *)(local_8 + 0x14);
        }
        for (local_8 = *(int *)(local_18 + 0x20); local_8 != 0; local_8 = *(int *)(local_8 + 0x44))
        {
          *(undefined4 *)(local_8 + 0x28) = *(undefined4 *)(local_8 + 0x10);
          *(undefined4 *)(local_8 + 0x2c) = *(undefined4 *)(local_8 + 0x14);
        }
      }
    }
  }
  return;
}


/* ==== FUN_0040e501 @ 0040e501 ==== */

void FUN_0040e501(void)

{
  int *piVar1;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  for (local_10 = 0; local_10 < 0x7d3; local_10 = local_10 + 1) {
    for (local_c = *(int *)(&DAT_00463f48 + local_10 * 4); local_c != 0;
        local_c = *(int *)(local_c + 0x10)) {
      for (local_14 = *(int *)(local_c + 8); local_14 != 0; local_14 = *(int *)(local_14 + 0x74)) {
        *(undefined4 *)(local_14 + 0x38) = *(undefined4 *)(local_14 + 0x40);
        *(undefined4 *)(local_14 + 0x3c) = *(undefined4 *)(local_14 + 0x44);
        for (local_8 = *(int *)(local_14 + 0x18); local_8 != 0; local_8 = *(int *)(local_8 + 0x44))
        {
          *(undefined4 *)(local_8 + 0x10) = *(undefined4 *)(local_8 + 0x28);
          *(undefined4 *)(local_8 + 0x14) = *(undefined4 *)(local_8 + 0x2c);
          *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) & 0xffffefff;
          piVar1 = *(int **)(local_8 + 0x38);
          if ((piVar1 != (int *)0x0) && (*piVar1 != 0)) {
            *(int *)(local_8 + 0x14) = *(int *)(local_8 + 0x14) + piVar1[3];
          }
        }
        for (local_8 = *(int *)(local_14 + 0x1c); local_8 != 0; local_8 = *(int *)(local_8 + 0x44))
        {
          *(undefined4 *)(local_8 + 0x10) = *(undefined4 *)(local_8 + 0x28);
          *(undefined4 *)(local_8 + 0x14) = *(undefined4 *)(local_8 + 0x2c);
          *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) & 0xffffefff;
        }
        for (local_8 = *(int *)(local_14 + 0x20); local_8 != 0; local_8 = *(int *)(local_8 + 0x44))
        {
          *(undefined4 *)(local_8 + 0x10) = *(undefined4 *)(local_8 + 0x28);
          *(undefined4 *)(local_8 + 0x14) = *(undefined4 *)(local_8 + 0x2c);
          *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) & 0xffffefff;
        }
      }
      for (local_14 = *(int *)(local_c + 8); local_14 != 0; local_14 = *(int *)(local_14 + 0x74)) {
        for (local_8 = *(int *)(local_14 + 0x24); local_8 != 0; local_8 = *(int *)(local_8 + 0x44))
        {
          *(undefined4 *)(local_8 + 0x10) = *(undefined4 *)(local_8 + 0x28);
          *(undefined4 *)(local_8 + 0x14) = *(undefined4 *)(local_8 + 0x2c);
          *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) & 0xffffefff;
          piVar1 = *(int **)(local_8 + 0x38);
          if ((piVar1 != (int *)0x0) && (*piVar1 != 0)) {
            *(int *)(local_8 + 0x14) = *(int *)(local_8 + 0x14) + piVar1[3];
            *(int *)(*(int *)(local_8 + 0x40) + 0x14) =
                 *(int *)(*(int *)(local_8 + 0x40) + 0x14) + piVar1[2];
          }
        }
      }
    }
  }
  return;
}


/* ==== FUN_0040e72e @ 0040e72e ==== */

int __cdecl FUN_0040e72e(int *param_1)

{
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_14 = 0;
  for (local_c = 0; local_c < 0x7d3; local_c = local_c + 1) {
    for (local_8 = *(int *)(&DAT_00463f48 + local_c * 4); local_8 != 0;
        local_8 = *(int *)(local_8 + 0x10)) {
      for (local_10 = *(int *)(local_8 + 8); local_10 != 0; local_10 = *(int *)(local_10 + 0x74)) {
        if ((*(int *)(local_10 + 8) == *param_1) && (*(int *)(local_10 + 0x10) == param_1[2])) {
          if (DAT_00461244 == '\0') {
            if (*(int *)(*(int *)(local_10 + 0x18) + 0x1c) == 0) {
              local_20 = *(int *)(*(int *)(local_10 + 0x18) + 0x20);
            }
            else {
              local_20 = *(int *)(*(int *)(local_10 + 0x18) + 0x1c);
            }
            local_1c = local_20;
          }
          else {
            if (*(int *)(local_10 + 0x54) == 0) {
              local_18 = *(int *)(local_10 + 0x50);
            }
            else {
              local_18 = *(int *)(local_10 + 0x54);
            }
            local_1c = local_18;
          }
          local_14 = local_14 + local_1c;
        }
      }
    }
  }
  return local_14;
}


/* ==== FUN_0040e832 @ 0040e832 ==== */

int __cdecl FUN_0040e832(int param_1)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  if (*(int *)(param_1 + 4) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = thunk_FUN_0042e170(*(int *)(param_1 + 4) * 4 + 4);
    local_c = *(int *)(param_1 + 8);
    local_8 = 0;
    for (; local_c != 0; local_c = *(int *)(local_c + 0x38)) {
      *(int *)(iVar1 + local_8 * 4) = local_c;
      local_8 = local_8 + 1;
    }
    *(undefined4 *)(iVar1 + local_8 * 4) = 0;
    thunk_FUN_0041ee04(iVar1,local_8);
  }
  return iVar1;
}


/* ==== FUN_0040e8ba @ 0040e8ba ==== */

int __cdecl FUN_0040e8ba(int param_1)

{
  int iVar1;
  int local_14;
  int local_10;
  undefined4 *local_c;
  
  local_10 = 0;
  local_c = *(undefined4 **)(param_1 + 0x30);
  do {
    if (local_c == (undefined4 *)0x0) {
LAB_0040e901:
      if (local_10 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = thunk_FUN_0042e170(local_10 * 4 + 4);
        local_14 = *(int *)(*(int *)*local_c + 0x18);
        local_10 = 0;
        for (; local_14 != 0; local_14 = *(int *)(local_14 + 0x44)) {
          *(int *)(iVar1 + local_10 * 4) = local_14;
          local_10 = local_10 + 1;
        }
        *(undefined4 *)(iVar1 + local_10 * 4) = 0;
        thunk_FUN_0041eda4(iVar1,local_10);
      }
      return iVar1;
    }
    if (*(int *)(**(int **)*local_c + 4) == -1) {
      local_10 = *(int *)(*(int *)*local_c + 0x28);
      goto LAB_0040e901;
    }
    local_c = (undefined4 *)local_c[1];
  } while( true );
}


/* ==== FUN_0040e981 @ 0040e981 ==== */

int __cdecl FUN_0040e981(int param_1)

{
  int iVar1;
  int local_14;
  int local_10;
  undefined4 *local_c;
  
  local_10 = 0;
  for (local_c = *(undefined4 **)(param_1 + 0x30); local_c != (undefined4 *)0x0;
      local_c = (undefined4 *)local_c[1]) {
    local_10 = local_10 + *(int *)(*(int *)*local_c + 0x2c);
  }
  if (local_10 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = thunk_FUN_0042e170(local_10 * 4 + 4);
    local_10 = 0;
    for (local_c = *(undefined4 **)(param_1 + 0x30); local_c != (undefined4 *)0x0;
        local_c = (undefined4 *)local_c[1]) {
      for (local_14 = *(int *)(*(int *)*local_c + 0x1c); local_14 != 0;
          local_14 = *(int *)(local_14 + 0x44)) {
        *(int *)(iVar1 + local_10 * 4) = local_14;
        local_10 = local_10 + 1;
      }
    }
    *(undefined4 *)(iVar1 + local_10 * 4) = 0;
    thunk_FUN_0041eda4(iVar1,local_10);
  }
  return iVar1;
}


/* ==== FUN_0040ea59 @ 0040ea59 ==== */

int __cdecl FUN_0040ea59(int param_1)

{
  int iVar1;
  int local_14;
  int local_10;
  undefined4 *local_c;
  
  local_10 = 0;
  for (local_c = *(undefined4 **)(param_1 + 0x30); local_c != (undefined4 *)0x0;
      local_c = (undefined4 *)local_c[1]) {
    local_10 = local_10 + *(int *)(*(int *)*local_c + 0x30);
  }
  if (local_10 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = thunk_FUN_0042e170(local_10 * 4 + 4);
    local_10 = 0;
    for (local_c = *(undefined4 **)(param_1 + 0x30); local_c != (undefined4 *)0x0;
        local_c = (undefined4 *)local_c[1]) {
      for (local_14 = *(int *)(*(int *)*local_c + 0x20); local_14 != 0;
          local_14 = *(int *)(local_14 + 0x44)) {
        *(int *)(iVar1 + local_10 * 4) = local_14;
        local_10 = local_10 + 1;
      }
    }
    *(undefined4 *)(iVar1 + local_10 * 4) = 0;
    thunk_FUN_0041ed36(iVar1,local_10);
  }
  return iVar1;
}


/* ==== FUN_0040eb31 @ 0040eb31 ==== */

int __cdecl FUN_0040eb31(int param_1)

{
  int iVar1;
  int local_10;
  undefined4 *local_c;
  
  local_10 = 0;
  if (*(int *)(param_1 + 0x34) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = thunk_FUN_0042e170(*(int *)(param_1 + 0x34) * 4 + 4);
    for (local_c = *(undefined4 **)(param_1 + 0x30); local_c != (undefined4 *)0x0;
        local_c = (undefined4 *)local_c[1]) {
      if (*(int *)(**(int **)*local_c + 4) != -1) {
        *(undefined4 *)(iVar1 + local_10 * 4) = *local_c;
        local_10 = local_10 + 1;
      }
    }
    *(undefined4 *)(iVar1 + local_10 * 4) = 0;
    thunk_FUN_0041eda4(iVar1,local_10);
  }
  return iVar1;
}


/* ==== FUN_0040ebca @ 0040ebca ==== */

void FUN_0040ebca(void)

{
  int local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  for (local_10 = 0; local_10 < 0x7d3; local_10 = local_10 + 1) {
    for (local_c = *(int *)(&DAT_00463f48 + local_10 * 4); local_c != 0;
        local_c = *(int *)(local_c + 0x10)) {
      for (local_14 = *(int *)(local_c + 8); local_14 != 0; local_14 = *(int *)(local_14 + 0x74)) {
        for (local_8 = *(int **)(local_14 + 0x18); local_8 != (int *)0x0;
            local_8 = (int *)local_8[0x11]) {
          FUN_0040ec8b(local_8);
        }
        for (local_8 = *(int **)(local_14 + 0x1c); local_8 != (int *)0x0;
            local_8 = (int *)local_8[0x11]) {
          FUN_0040ec8b(local_8);
        }
      }
    }
  }
  return;
}


/* ==== FUN_0040ec8b @ 0040ec8b ==== */

void __cdecl FUN_0040ec8b(int *param_1)

{
  int iVar1;
  int local_10;
  int local_c;
  int local_8;
  
  if (param_1[7] == 0) {
    iVar1 = param_1[5] - param_1[4];
    if (iVar1 == 0) {
      local_c = *(int *)(*param_1 + 0x24);
      if (local_c != 0) {
        local_8 = 0;
        for (local_10 = 0; local_10 < *(int *)(*param_1 + 0x34); local_10 = local_10 + 1) {
          local_8 = local_8 + (*(int *)(local_c + 0x14) - *(int *)(local_c + 0x10));
          local_c = *(int *)(local_c + 0x44);
        }
        param_1[8] = local_8;
        *(int *)(*param_1 + 0x50) = *(int *)(*param_1 + 0x50) + local_8;
      }
    }
    else {
      param_1[7] = iVar1;
      *(int *)(*param_1 + 0x54) = *(int *)(*param_1 + 0x54) + iVar1;
    }
  }
  return;
}


/* ==== FUN_0040ed4c @ 0040ed4c ==== */

void __cdecl FUN_0040ed4c(int *param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = param_1[4];
  uVar2 = param_1[5];
  FUN_0040f005(param_1);
  if (param_1[6] != 0) {
    FUN_004115dd(DAT_00461dd4,param_1,param_2,uVar1,uVar2,(int)DAT_00461228);
    FUN_0040fe58((int *)(&DAT_00461df8 + param_2 * 4),uVar1,uVar2);
    if (0 < param_2) {
      if (param_2 < 3) {
        FUN_004115dd(DAT_00461dd4,param_1,3,uVar1,uVar2,(int)DAT_00461228);
        FUN_0040fe58((int *)&DAT_00461e04,uVar1,uVar2);
      }
      else if (param_2 == 3) {
        FUN_004115dd(DAT_00461dd4,param_1,1,uVar1,uVar2,(int)DAT_00461228);
        FUN_0040fe58((int *)&DAT_00461dfc,uVar1,uVar2);
        FUN_004115dd(DAT_00461dd4,param_1,2,uVar1,uVar2,(int)DAT_00461228);
        FUN_0040fe58((int *)&DAT_00461e00,uVar1,uVar2);
      }
    }
    if ((DAT_0046122c == '\0') && (DAT_00461dd4 != DAT_00461dd8)) {
      FUN_004115dd(DAT_00461dd8,param_1,param_2,uVar1,uVar2,(int)DAT_00461228);
      FUN_0040fe58((int *)(DAT_00461e28 + param_2 * 4),uVar1,uVar2);
      if (0 < param_2) {
        if (param_2 < 3) {
          FUN_004115dd(DAT_00461dd8,param_1,3,uVar1,uVar2,(int)DAT_00461228);
          FUN_0040fe58((int *)(DAT_00461e28 + 0xc),uVar1,uVar2);
        }
        else if (param_2 == 3) {
          FUN_004115dd(DAT_00461dd8,param_1,1,uVar1,uVar2,(int)DAT_00461228);
          FUN_0040fe58((int *)(DAT_00461e28 + 4),uVar1,uVar2);
          FUN_004115dd(DAT_00461dd8,param_1,2,uVar1,uVar2,(int)DAT_00461228);
          FUN_0040fe58((int *)(DAT_00461e28 + 8),uVar1,uVar2);
        }
      }
    }
    if (*(int *)(*(int *)*param_1 + 4) != -1) {
      param_1[5] = param_1[4];
      param_1[3] = param_1[3] & 0xffffefff;
    }
  }
  return;
}


/* ==== FUN_0040f005 @ 0040f005 ==== */

int __cdecl FUN_0040f005(int *param_1)

{
  int local_8;
  
  local_8 = param_1[6];
  if (local_8 == 0) {
    local_8 = param_1[5] - param_1[4];
    param_1[6] = local_8;
    *(int *)(*param_1 + 0x4c) = *(int *)(*param_1 + 0x4c) + local_8;
  }
  return local_8;
}


/* ==== FUN_0040f04a @ 0040f04a ==== */

void __cdecl FUN_0040f04a(int *param_1,int param_2)

{
  uint uVar1;
  int local_1c;
  uint local_18;
  uint local_10;
  uint local_8;
  
  local_8 = 0;
  DAT_004612f8 = *(undefined4 *)(*param_1 + 0x48);
  local_18 = param_1[4];
  uVar1 = FUN_0040f005(param_1);
  if ((uVar1 != 0) && (DAT_00461248 == '\0')) {
    if (DAT_0046128c == '\x01') {
      local_10 = 0;
    }
    else {
      local_10 = param_1[9];
    }
    if ((DAT_00461e20 == 0) || (DAT_00461230 == '\0')) {
      local_1c = DAT_00461e18;
    }
    else {
      local_1c = DAT_00461e20;
    }
    DAT_00461e1c = local_1c;
    local_18 = FUN_0040fa6c(uVar1,local_10,1,DAT_00461f74);
    local_8 = local_18 + uVar1;
    *(int *)(&DAT_00461df8 + param_2 * 4) = DAT_00461e18;
    FUN_0040f868(param_1,param_2,local_18,local_8,(int)DAT_00457b80);
  }
  param_1[4] = local_18;
  param_1[5] = local_18;
  param_1[3] = param_1[3] & 0xffffefff;
  if (*(int *)(*param_1 + 0x10) == 0) {
    FUN_0040f722(param_2,local_8);
  }
  return;
}


/* ==== FUN_0040f17f @ 0040f17f ==== */

void __cdecl FUN_0040f17f(int *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint local_8;
  
  local_8 = 0;
  uVar1 = param_1[4];
  iVar2 = FUN_0040f005(param_1);
  if (iVar2 != 0) {
    local_8 = uVar1 + iVar2;
    FUN_0040fe58((int *)(&DAT_00461df8 + param_2 * 4),uVar1,local_8);
    FUN_0040f868(param_1,param_2,uVar1,local_8,(int)DAT_00461228);
  }
  param_1[5] = uVar1;
  param_1[3] = param_1[3] & 0xffffefff;
  if (*(int *)(*param_1 + 0x10) == 0) {
    FUN_0040f722(param_2,local_8);
  }
  return;
}


/* ==== FUN_0040f225 @ 0040f225 ==== */

void __cdecl FUN_0040f225(int param_1,int param_2)

{
  int *piVar1;
  uint uVar2;
  int local_24;
  uint local_20;
  uint local_18;
  undefined4 *local_10;
  uint local_c;
  
  local_c = 0;
  DAT_004612f8 = *(uint *)(param_1 + 0x1c);
  local_20 = DAT_004612f8;
  for (local_10 = *(undefined4 **)(param_1 + 0x30); local_10 != (undefined4 *)0x0;
      local_10 = (undefined4 *)local_10[1]) {
    piVar1 = (int *)*local_10;
    if ((piVar1[3] & 0x100U) != 0) {
      uVar2 = FUN_0040f005(piVar1);
      if ((uVar2 != 0) && (DAT_00461248 == '\0')) {
        if ((DAT_0046128c == '\x01') || ((*(uint *)(*(int *)(*piVar1 + 0x18) + 0xc) & 0x2000) != 0))
        {
          local_18 = 0;
        }
        else {
          local_18 = piVar1[9];
        }
        if ((DAT_00461e20 == 0) || (DAT_00461230 == '\0')) {
          local_24 = DAT_00461e18;
        }
        else {
          local_24 = DAT_00461e20;
        }
        DAT_00461e1c = local_24;
        local_20 = FUN_0040fa6c(uVar2,local_18,1,DAT_00461f74);
        local_c = local_20 + uVar2;
        *(int *)(&DAT_00461df8 + param_2 * 4) = DAT_00461e18;
        FUN_0040f868(piVar1,param_2,local_20,local_c,(int)DAT_00457b80);
      }
      piVar1[4] = local_20;
      piVar1[5] = local_20;
      piVar1[3] = piVar1[3] & 0xffffefff;
      if (DAT_00461248 == '\0') {
        local_20 = local_20 + uVar2;
      }
      if (*(int *)(*piVar1 + 0x10) == 0) {
        FUN_0040f722(param_2,local_c);
      }
    }
  }
  DAT_00461e20 = DAT_00461e1c;
  return;
}


/* ==== FUN_0040f3c5 @ 0040f3c5 ==== */

void __cdecl FUN_0040f3c5(int param_1,int *param_2,int param_3)

{
  int *piVar1;
  uint uVar2;
  int local_28;
  uint local_24;
  uint local_1c;
  int *local_c;
  uint local_8;
  
  local_8 = 0;
  if ((*(uint *)(param_1 + 8) & 0x800000) == 0) {
    local_24 = *(uint *)(param_1 + 0x1c);
  }
  else {
    local_24 = *(uint *)(param_1 + 0x28);
  }
  local_1c = local_24;
  DAT_004612f8 = local_24;
  for (local_c = param_2; *local_c != 0; local_c = local_c + 1) {
    piVar1 = (int *)*local_c;
    if ((((piVar1[2] & 0x1000U) != 0) && ((piVar1[2] & 0x20000U) != 0)) &&
       ((piVar1[2] & 0x800000U) == 0)) {
      uVar2 = FUN_0040f005(piVar1);
      if ((uVar2 != 0) && (DAT_00461248 == '\0')) {
        if ((DAT_00461e20 == 0) || (DAT_00461230 == '\0')) {
          local_28 = DAT_00461e18;
        }
        else {
          local_28 = DAT_00461e20;
        }
        DAT_00461e1c = local_28;
        local_1c = FUN_0040fa6c(uVar2,piVar1[9],1,DAT_00461f74);
        local_8 = local_1c + uVar2;
        *(int *)(&DAT_00461df8 + param_3 * 4) = DAT_00461e18;
        FUN_0040f868(piVar1,param_3,local_1c,local_8,(int)DAT_00457b80);
      }
      piVar1[4] = local_1c;
      piVar1[5] = local_1c;
      piVar1[3] = piVar1[3] & 0xffffefff;
      if (DAT_00461248 == '\0') {
        local_1c = local_1c + uVar2;
      }
      if (*(int *)(*piVar1 + 0x10) == 0) {
        FUN_0040f722(param_3,local_8);
      }
    }
  }
  return;
}


/* ==== FUN_0040f58e @ 0040f58e ==== */

void __cdecl FUN_0040f58e(int param_1,int *param_2,int param_3)

{
  int *piVar1;
  uint uVar2;
  int local_24;
  uint local_20;
  uint local_18;
  uint local_10;
  int *local_8;
  
  local_10 = 0;
  DAT_004612f8 = *(uint *)(param_1 + 0x1c);
  local_20 = DAT_004612f8;
  for (local_8 = param_2; *local_8 != 0; local_8 = local_8 + 1) {
    piVar1 = (int *)*local_8;
    if ((piVar1[3] & 0x300U) == 0) {
      uVar2 = FUN_0040f005(piVar1);
      if ((uVar2 != 0) && (DAT_00461248 == '\0')) {
        if ((DAT_0046128c == '\x01') || ((*(uint *)(*(int *)(*piVar1 + 0x18) + 0xc) & 0x2000) != 0))
        {
          local_18 = 0;
        }
        else {
          local_18 = piVar1[9];
        }
        if ((DAT_00461e20 == 0) || (DAT_00461230 == '\0')) {
          local_24 = DAT_00461e18;
        }
        else {
          local_24 = DAT_00461e20;
        }
        DAT_00461e1c = local_24;
        local_20 = FUN_0040fa6c(uVar2,local_18,1,DAT_00461f74);
        local_10 = local_20 + uVar2;
        *(int *)(&DAT_00461df8 + param_3 * 4) = DAT_00461e18;
        FUN_0040f868(piVar1,param_3,local_20,local_10,(int)DAT_00457b80);
      }
      piVar1[4] = local_20;
      piVar1[5] = local_20;
      piVar1[3] = piVar1[3] & 0xffffefff;
      if (DAT_00461248 == '\0') {
        local_20 = local_20 + uVar2;
      }
      if (*(int *)(*piVar1 + 0x10) == 0) {
        FUN_0040f722(param_3,local_10);
      }
    }
  }
  return;
}


/* ==== FUN_0040f722 @ 0040f722 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0040f722(int param_1,uint param_2)

{
  if ((param_1 == 1) && (DAT_00461e34 < param_2)) {
    DAT_00461e34 = param_2;
    if (DAT_00461e3c < param_2) {
      DAT_00461e3c = param_2;
    }
  }
  else if ((param_1 == 2) && (DAT_00461e38 < param_2)) {
    DAT_00461e38 = param_2;
    if (DAT_00461e3c < param_2) {
      DAT_00461e3c = param_2;
    }
  }
  else if (param_1 == 3) {
    if (DAT_00461e34 < param_2) {
      DAT_00461e34 = param_2;
    }
    if (DAT_00461e38 < param_2) {
      DAT_00461e38 = param_2;
    }
    if (DAT_00461e3c < param_2) {
      DAT_00461e3c = param_2;
    }
  }
  if ((param_1 == 4) && (_DAT_00461e40 < param_2)) {
    _DAT_00461e40 = param_2;
  }
  if ((param_1 == 5) && (uRam00461e44 < param_2)) {
    uRam00461e44 = param_2;
  }
  if (DAT_00461210 == '\0') {
    if (((param_1 != 4) && (param_1 != 5)) && (DAT_00461e50 < param_2)) {
      DAT_00461e50 = param_2;
    }
  }
  else if ((param_1 == DAT_00457b48) && (DAT_00461e50 < param_2)) {
    DAT_00461e50 = param_2;
  }
  return;
}


/* ==== FUN_0040f868 @ 0040f868 ==== */

void __cdecl FUN_0040f868(int *param_1,int param_2,uint param_3,uint param_4,int param_5)

{
  FUN_004115dd(DAT_00461dd4,param_1,param_2,param_3,param_4,param_5);
  if ((DAT_0046122c == '\0') && (DAT_00461dd4 != DAT_00461dd8)) {
    FUN_0040fe58((int *)(DAT_00461e28 + param_2 * 4),param_3,param_4);
  }
  if ((param_2 == 1) || (param_2 == 2)) {
    FUN_004115dd(DAT_00461dd4,param_1,3,param_3,param_4,param_5);
    FUN_0040fe58((int *)&DAT_00461e04,param_3,param_4);
    if ((DAT_0046122c == '\0') && (DAT_00461dd4 != DAT_00461dd8)) {
      FUN_004115dd(DAT_00461dd8,param_1,3,param_3,param_4,param_5);
      FUN_0040fe58((int *)(DAT_00461e28 + 0xc),param_3,param_4);
    }
  }
  else if (param_2 == 3) {
    FUN_004115dd(DAT_00461dd4,param_1,1,param_3,param_4,param_5);
    FUN_0040fe58((int *)&DAT_00461dfc,param_3,param_4);
    FUN_004115dd(DAT_00461dd4,param_1,2,param_3,param_4,param_5);
    FUN_0040fe58((int *)&DAT_00461e00,param_3,param_4);
    if ((DAT_0046122c == '\0') && (DAT_00461dd4 != DAT_00461dd8)) {
      FUN_004115dd(DAT_00461dd8,param_1,1,param_3,param_4,param_5);
      FUN_0040fe58((int *)(DAT_00461e28 + 4),param_3,param_4);
      FUN_004115dd(DAT_00461dd8,param_1,2,param_3,param_4,param_5);
      FUN_0040fe58((int *)(DAT_00461e28 + 8),param_3,param_4);
    }
  }
  return;
}


/* ==== FUN_0040fa6c @ 0040fa6c ==== */

uint __cdecl FUN_0040fa6c(uint param_1,uint param_2,int param_3,uint param_4)

{
  bool bVar1;
  uint local_1c;
  uint local_18;
  uint local_14;
  undefined *local_c;
  uint local_8;
  
  if (param_2 == 0) {
    local_18 = DAT_004612f8;
  }
  else {
    local_18 = thunk_FUN_00430ac9(DAT_004612f8,param_2,param_4);
  }
  local_14 = local_18;
  local_8 = local_18 + param_1;
  if (DAT_00461e1c == (undefined *)0x0) {
    if (param_3 != 0) {
      DAT_00461e1c = (undefined *)FUN_0040fdb9(0,local_18,local_8);
    }
  }
  else if (((DAT_00461e1c == DAT_00461e18) && (local_18 < *(uint *)(DAT_00461e1c + 4))) &&
          (param_1 <= *(int *)(DAT_00461e1c + 4) - local_18)) {
    if (param_3 != 0) {
      if (local_8 == *(uint *)(DAT_00461e1c + 4)) {
        *(uint *)(DAT_00461e1c + 4) = local_18;
      }
      else {
        DAT_00461e1c = (undefined *)FUN_0040fdb9(0,local_18,local_8);
      }
    }
  }
  else {
    local_c = *(undefined **)(DAT_00461e1c + 0x10);
    bVar1 = false;
    while ((local_c != (undefined *)0x0 && (!bVar1))) {
      if ((param_1 <= (uint)(*(int *)(local_c + 4) - *(int *)(DAT_00461e1c + 8))) &&
         (local_8 <= *(uint *)(local_c + 4))) {
        if (local_14 < *(uint *)(DAT_00461e1c + 8)) {
          local_14 = *(uint *)(DAT_00461e1c + 8);
          local_8 = local_14 + param_1;
          if (param_2 != 0) {
            local_14 = thunk_FUN_00430ac9(local_14,param_2,param_4);
            local_8 = local_14 + param_1;
            if (*(uint *)(local_c + 4) < local_8) goto LAB_0040fb5c;
          }
        }
        bVar1 = true;
        if (param_3 != 0) {
          if ((local_14 == *(uint *)(DAT_00461e1c + 8)) && (local_8 == *(uint *)(local_c + 4))) {
            *(undefined4 *)(DAT_00461e1c + 8) = *(undefined4 *)(local_c + 8);
            *(undefined4 *)(DAT_00461e1c + 0x10) = *(undefined4 *)(local_c + 0x10);
            if (*(int *)(DAT_00461e1c + 0x10) != 0) {
              *(undefined **)(*(int *)(DAT_00461e1c + 0x10) + 0xc) = DAT_00461e1c;
            }
            thunk_FUN_0042e1ce(local_c);
          }
          else if (local_14 == *(uint *)(DAT_00461e1c + 8)) {
            *(uint *)(DAT_00461e1c + 8) = local_8;
          }
          else if (local_8 == *(uint *)(local_c + 4)) {
            *(uint *)(local_c + 4) = local_14;
          }
          else {
            FUN_0040fdb9((int)DAT_00461e1c,local_14,local_8);
          }
        }
      }
LAB_0040fb5c:
      DAT_00461e1c = local_c;
      local_c = *(undefined **)(local_c + 0x10);
    }
    if (bVar1) {
      if (*(int *)(DAT_00461e1c + 0xc) != 0) {
        DAT_00461e1c = *(undefined **)(DAT_00461e1c + 0xc);
      }
    }
    else {
      if (param_2 == 0) {
        local_1c = DAT_004612f8;
      }
      else {
        local_1c = thunk_FUN_00430ac9(DAT_004612f8,param_2,param_4);
      }
      local_14 = local_1c;
      if (local_1c < *(uint *)(DAT_00461e1c + 8)) {
        if (param_2 == 0) {
          local_14 = *(uint *)(DAT_00461e1c + 8);
        }
        else {
          local_14 = thunk_FUN_00430ac9(*(uint *)(DAT_00461e1c + 8),param_2,param_4);
        }
      }
      local_8 = local_14 + param_1;
      if (*(uint *)(DAT_00461e1c + 8) < local_14) {
        if (param_3 != 0) {
          DAT_00461e1c = (undefined *)FUN_0040fdb9((int)DAT_00461e1c,local_14,local_8);
        }
      }
      else if (param_3 != 0) {
        *(uint *)(DAT_00461e1c + 8) = local_8;
      }
    }
  }
  return local_14;
}


/* ==== FUN_0040fdb9 @ 0040fdb9 ==== */

int __cdecl FUN_0040fdb9(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = thunk_FUN_0042e170(0x14);
  *(undefined4 *)(iVar1 + 4) = param_2;
  *(undefined4 *)(iVar1 + 8) = param_3;
  if (param_1 == 0) {
    *(undefined4 *)(iVar1 + 0xc) = 0;
    if (DAT_00461e18 == 0) {
      DAT_00461e18 = iVar1;
      *(undefined4 *)(iVar1 + 0x10) = 0;
    }
    else {
      *(int *)(iVar1 + 0x10) = DAT_00461e18;
      *(int *)(DAT_00461e18 + 0xc) = iVar1;
      DAT_00461e18 = iVar1;
    }
  }
  else {
    *(undefined4 *)(iVar1 + 0x10) = *(undefined4 *)(param_1 + 0x10);
    *(int *)(param_1 + 0x10) = iVar1;
    *(int *)(iVar1 + 0xc) = param_1;
  }
  return iVar1;
}


/* ==== FUN_0040fe58 @ 0040fe58 ==== */

void __cdecl FUN_0040fe58(int *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined *puVar1;
  undefined *local_10;
  undefined *local_c;
  
  local_c = (undefined *)0x0;
  puVar1 = (undefined *)thunk_FUN_0042e170(0x14);
  *(undefined4 *)(puVar1 + 4) = param_2;
  *(undefined4 *)(puVar1 + 8) = param_3;
  *(undefined4 *)(puVar1 + 0x10) = 0;
  *(undefined4 *)(puVar1 + 0xc) = 0;
  for (local_10 = (undefined *)*param_1;
      (local_10 != (undefined *)0x0 && (*(uint *)(local_10 + 4) < *(uint *)(puVar1 + 4)));
      local_10 = *(undefined **)(local_10 + 0x10)) {
    local_c = local_10;
  }
  if (local_10 == (undefined *)0x0) {
    if (local_c == (undefined *)0x0) {
      *param_1 = (int)puVar1;
    }
    else {
      FUN_0040ff2c(local_c,puVar1,(undefined *)0x0);
    }
  }
  else if (local_10 == (undefined *)*param_1) {
    puVar1 = FUN_0040ff2c((undefined *)0x0,puVar1,local_10);
    *param_1 = (int)puVar1;
  }
  else {
    FUN_0040ff2c(local_c,puVar1,local_10);
  }
  return;
}


/* ==== FUN_0040ff2c @ 0040ff2c ==== */

undefined * __cdecl FUN_0040ff2c(undefined *param_1,undefined *param_2,undefined *param_3)

{
  undefined *puVar1;
  
  if (*(uint *)(param_2 + 4) < *(uint *)(param_2 + 8)) {
    if (param_1 != (undefined *)0x0) {
      if (*(uint *)(param_1 + 8) < *(uint *)(param_2 + 4)) {
        *(undefined **)(param_2 + 0xc) = param_1;
        *(undefined **)(param_1 + 0x10) = param_2;
      }
      else {
        if (*(uint *)(param_1 + 8) < *(uint *)(param_2 + 8)) {
          *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_2 + 8);
        }
        thunk_FUN_0042e1ce(param_2);
        param_2 = param_1;
      }
    }
    if (param_3 != (undefined *)0x0) {
      while ((param_3 != (undefined *)0x0 && (*(uint *)(param_3 + 8) < *(uint *)(param_2 + 8)))) {
        *(undefined4 *)(param_2 + 0x10) = *(undefined4 *)(param_3 + 0x10);
        puVar1 = *(undefined **)(param_2 + 0x10);
        thunk_FUN_0042e1ce(param_3);
        param_3 = puVar1;
      }
      if (param_3 != (undefined *)0x0) {
        if (*(uint *)(param_2 + 8) < *(uint *)(param_3 + 4)) {
          *(undefined **)(param_2 + 0x10) = param_3;
          *(undefined **)(param_3 + 0xc) = param_2;
        }
        else {
          *(undefined4 *)(param_2 + 8) = *(undefined4 *)(param_3 + 8);
          *(undefined4 *)(param_2 + 0x10) = *(undefined4 *)(param_3 + 0x10);
          if (*(int *)(param_3 + 0x10) != 0) {
            *(undefined **)(*(int *)(param_3 + 0x10) + 0xc) = param_2;
          }
          thunk_FUN_0042e1ce(param_3);
        }
      }
    }
  }
  else {
    thunk_FUN_0042e1ce(param_2);
    param_2 = param_3;
    if (param_1 != (undefined *)0x0) {
      param_2 = param_1;
    }
  }
  return param_2;
}


/* ==== FUN_0041006f @ 0041006f ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0041006f(void)

{
  int *piVar1;
  int local_94 [4];
  undefined4 *local_84;
  undefined4 *local_80;
  undefined4 *local_7c;
  char *local_78 [2];
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 *local_30;
  undefined4 *local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 *local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  
  local_94[1] = 4;
  local_94[0] = 4;
  local_94[2] = 0;
  local_94[3] = 0;
  local_c = thunk_FUN_0042c8ba((uint *)s_DSIZE_004562d8,0);
  if (local_c == (undefined4 *)0x0) {
    memset(local_78,0,0x68);
    local_48 = 4;
    local_4c = 4;
    local_44 = 0;
    local_40 = 0;
    local_94[1] = 1;
    local_94[0] = 1;
    DAT_00461ddc = thunk_FUN_0042bc50((uint *)s_GLOBAL_00457f88,DAT_00461fc4,local_94,0);
    local_78[0] = s_DSIZE_004562d8;
    local_68 = 0;
    local_6c = 0;
    local_70 = 0;
    local_50 = 0x140;
    local_28 = 0;
    local_24 = 0;
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;
    DAT_00461de0 = DAT_00461ddc;
    local_7c = DAT_00461ddc;
    local_30 = DAT_00461ddc;
    local_2c = DAT_00461ddc;
    piVar1 = thunk_FUN_0042c6c1((int *)local_78);
    if ((piVar1 == (int *)0x0) ||
       (local_c = thunk_FUN_0042c8ba((uint *)s_DSIZE_004562d8,0), local_c == (undefined4 *)0x0)) {
      return 0;
    }
  }
  local_84 = thunk_FUN_0042c8ba((uint *)s_XSIZE_004562e0,0);
  if (local_84 == (undefined4 *)0x0) {
    memset(local_78,0,0x68);
    local_48 = 4;
    local_4c = 4;
    local_44 = 0;
    local_40 = 0;
    local_94[1] = 1;
    local_94[0] = 1;
    DAT_00461ddc = thunk_FUN_0042bc50((uint *)s_GLOBAL_00457f88,DAT_00461fc4,local_94,0);
    local_78[0] = s_XSIZE_004562e0;
    local_68 = 0;
    local_6c = 0;
    local_70 = 0;
    local_50 = 0x140;
    local_28 = 0;
    local_24 = 0;
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;
    DAT_00461de0 = DAT_00461ddc;
    local_7c = DAT_00461ddc;
    local_30 = DAT_00461ddc;
    local_2c = DAT_00461ddc;
    piVar1 = thunk_FUN_0042c6c1((int *)local_78);
    if ((piVar1 == (int *)0x0) ||
       (local_84 = thunk_FUN_0042c8ba((uint *)s_XSIZE_004562e0,0), local_84 == (undefined4 *)0x0)) {
      return 0;
    }
  }
  local_8 = thunk_FUN_0042c8ba((uint *)s_YSIZE_004562e8,0);
  if (local_8 == (undefined4 *)0x0) {
    memset(local_78,0,0x68);
    local_48 = 4;
    local_4c = 4;
    local_44 = 0;
    local_40 = 0;
    local_94[1] = 2;
    local_94[0] = 2;
    DAT_00461ddc = thunk_FUN_0042bc50((uint *)s_GLOBAL_00457f88,DAT_00461fc4,local_94,0);
    local_78[0] = s_YSIZE_004562e8;
    local_68 = 0;
    local_6c = 0;
    local_70 = 0;
    local_50 = 0x140;
    local_28 = 0;
    local_24 = 0;
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;
    DAT_00461de0 = DAT_00461ddc;
    local_7c = DAT_00461ddc;
    local_30 = DAT_00461ddc;
    local_2c = DAT_00461ddc;
    piVar1 = thunk_FUN_0042c6c1((int *)local_78);
    if ((piVar1 == (int *)0x0) ||
       (local_8 = thunk_FUN_0042c8ba((uint *)s_YSIZE_004562e8,0), local_8 == (undefined4 *)0x0)) {
      return 0;
    }
  }
  local_10 = thunk_FUN_0042c8ba((uint *)s_LSIZE_004562f0,0);
  if (local_10 == (undefined4 *)0x0) {
    memset(local_78,0,0x68);
    local_48 = 4;
    local_4c = 4;
    local_44 = 0;
    local_40 = 0;
    local_94[1] = 3;
    local_94[0] = 3;
    DAT_00461ddc = thunk_FUN_0042bc50((uint *)s_GLOBAL_00457f88,DAT_00461fc4,local_94,0);
    local_78[0] = s_LSIZE_004562f0;
    local_68 = 0;
    local_6c = 0;
    local_70 = 0;
    local_50 = 0x140;
    local_28 = 0;
    local_24 = 0;
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;
    DAT_00461de0 = DAT_00461ddc;
    local_7c = DAT_00461ddc;
    local_30 = DAT_00461ddc;
    local_2c = DAT_00461ddc;
    piVar1 = thunk_FUN_0042c6c1((int *)local_78);
    if ((piVar1 == (int *)0x0) ||
       (local_10 = thunk_FUN_0042c8ba((uint *)s_LSIZE_004562f0,0), local_10 == (undefined4 *)0x0)) {
      return 0;
    }
  }
  local_80 = thunk_FUN_0042c8ba((uint *)s_PSIZE_004562f8,0);
  if (local_80 == (undefined4 *)0x0) {
    memset(local_78,0,0x68);
    local_48 = 4;
    local_4c = 4;
    local_44 = 0;
    local_40 = 0;
    local_94[1] = 0;
    local_94[0] = 0;
    DAT_00461ddc = thunk_FUN_0042bc50((uint *)s_GLOBAL_00457f88,DAT_00461fc4,local_94,0);
    local_78[0] = s_PSIZE_004562f8;
    local_68 = 0;
    local_6c = 0;
    local_70 = 0;
    local_50 = 0x140;
    local_28 = 0;
    local_24 = 0;
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;
    DAT_00461de0 = DAT_00461ddc;
    local_7c = DAT_00461ddc;
    local_30 = DAT_00461ddc;
    local_2c = DAT_00461ddc;
    piVar1 = thunk_FUN_0042c6c1((int *)local_78);
    if ((piVar1 == (int *)0x0) ||
       (local_80 = thunk_FUN_0042c8ba((uint *)s_PSIZE_004562f8,0), local_80 == (undefined4 *)0x0)) {
      return 0;
    }
  }
  local_c[4] = local_c[4] + DAT_00461e50;
  local_84[4] = local_84[4] + DAT_00461e34;
  local_8[4] = local_8[4] + DAT_00461e38;
  local_10[4] = local_10[4] + DAT_00461e3c;
  local_80[4] = local_80[4] + _DAT_00461e40;
  DAT_00461de0 = (undefined4 *)0x0;
  DAT_00461ddc = (undefined4 *)0x0;
  return 1;
}


/* ==== FUN_00410668 @ 00410668 ==== */

void FUN_00410668(void)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int local_30;
  int local_24;
  int local_1c;
  int local_14;
  int local_10;
  int *local_8;
  
  for (local_14 = DAT_00461db8; local_14 != 0; local_14 = *(int *)(local_14 + 0x10)) {
    DAT_00461dbc = local_14;
    if (*(int *)(local_14 + 0xc) == 0) {
      local_30 = *(int *)(local_14 + 8);
    }
    else {
      local_30 = *(int *)(local_14 + 0xc);
    }
    for (local_10 = local_30; local_10 != 0; local_10 = *(int *)(local_10 + 0x94)) {
      for (local_1c = 1; local_1c <= *(int *)(local_10 + 0x5c); local_1c = local_1c + 1) {
        if ((*(int *)(local_10 + 0x1c) != 0) &&
           (*(int *)(*(int *)(local_10 + 0x1c) + 0x20 + local_1c * 0x24) != 0)) {
          DAT_00461e60 = *(int *)(local_10 + 0x1c);
          DAT_004612c8 = local_1c;
          iVar4 = DAT_00461e60 + local_1c * 0x24;
          piVar1 = *(int **)(iVar4 + 4);
          if (piVar1 != (int *)0x0) {
            uVar3 = thunk_FUN_0042f22f(*(int *)(*piVar1 + 8));
            DAT_00461ddc = *(undefined4 **)(iVar4 + 8);
            DAT_004612a4 = *(undefined4 *)(*(int *)*DAT_00461ddc + 4);
            DAT_00461de0 = *(int **)(iVar4 + 0xc);
            DAT_004612a8 = *(undefined4 *)(*(int *)*DAT_00461de0 + 4);
            DAT_00461dd4 = *(int **)(*DAT_00461de0 + 0x70);
            DAT_00461dd0 = *DAT_00461dd4;
            DAT_00461d68 = *(char **)(iVar4 + 0x20);
            local_8 = (int *)thunk_FUN_0043a260(local_10,0,DAT_00461d68);
            if ((local_8 != (int *)0x0) || (local_8 = thunk_FUN_0040a370(), local_8 != (int *)0x0))
            {
              if (local_8[0xb] < 0) {
                thunk_FUN_00409a25(s_Unresolved_overlay_base_address_00456368);
              }
              else if ((local_8[6] & 0x4000U) == 0) {
                iVar4 = piVar1[5];
                iVar2 = piVar1[4];
                piVar1[5] = local_8[2];
                piVar1[4] = piVar1[5];
                piVar1[5] = piVar1[5] + (iVar4 - iVar2);
                FUN_004115dd(DAT_00461dd4,piVar1,uVar3,piVar1[4],piVar1[5],(int)DAT_00461228);
                piVar1[3] = piVar1[3] | 0x1000;
                *(uint *)(*(int *)(*piVar1 + 0x70) + 8) =
                     *(uint *)(*(int *)(*piVar1 + 0x70) + 8) | 0x1000;
                thunk_FUN_0040ca80((undefined *)local_8);
              }
              else {
                thunk_FUN_00409a25(s_Invalid_overlay_base_address_00456388);
              }
            }
          }
        }
      }
    }
  }
  DAT_00461dbc = 0;
  DAT_00461de0 = (int *)0x0;
  DAT_00461ddc = (undefined4 *)0x0;
  DAT_00461dd0 = DAT_00461dcc;
  DAT_00461dd4 = (int *)0x0;
  DAT_00461e60 = 0;
  DAT_004612c8 = 0;
  DAT_004612a8 = 0;
  DAT_004612a4 = 0;
  FUN_00410a84();
  if ((DAT_00461274 == '\0') || (DAT_0046127c == '\0')) {
    for (local_1c = 0; local_1c < 0x7d3; local_1c = local_1c + 1) {
      for (local_24 = *(int *)(&DAT_00461ff8 + local_1c * 4); local_24 != 0;
          local_24 = *(int *)(local_24 + 0x60)) {
        if ((*(uint *)(local_24 + 0x28) & 0x5100) == 0x5100) {
          if ((DAT_00457b7c == '\0') ||
             (iVar4 = thunk_FUN_0043016a(*(int *)(local_24 + 0x2c),
                                         *(int *)(**(int **)(*(int *)(local_24 + 0x5c) + 4) + 8)),
             iVar4 != 0xa2c2a)) {
            if (DAT_00461274 != '\0') {
              *(undefined4 *)(local_24 + 8) = *(undefined4 *)(local_24 + 0x18);
              *(undefined4 *)(local_24 + 0xc) = *(undefined4 *)(local_24 + 0x1c);
              *(undefined4 *)(local_24 + 0x10) = *(undefined4 *)(local_24 + 0x20);
              *(undefined4 *)(local_24 + 0x14) = *(undefined4 *)(local_24 + 0x24);
            }
            *(int *)(local_24 + 0x10) =
                 *(int *)(local_24 + 0x10) +
                 *(int *)(*(int *)(*(int *)(local_24 + 0x5c) + 0x10) + 0x10);
            iVar4 = *(int *)(*(int *)(*(int *)(local_24 + 0x5c) + 4) + 0x38);
            if (((*(int *)(local_24 + 0x40) != 0) && (iVar4 != 0)) && (*(int *)(iVar4 + 0x28) != 0))
            {
              *(int *)(local_24 + 0x10) =
                   *(int *)(local_24 + 0x10) +
                   *(int *)(*(int *)(iVar4 + 0x28) + 0x1c + (*(int *)(local_24 + 0x40) + -1) * 0x2c)
              ;
            }
          }
          else {
            thunk_FUN_00409a25(s_Overlay_address_involves_incompa_004563a8);
          }
        }
      }
    }
  }
  return;
}


/* ==== FUN_00410a84 @ 00410a84 ==== */

void FUN_00410a84(void)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *local_28;
  int local_18;
  int local_14;
  undefined4 local_c;
  int *local_8;
  
  local_14 = 4;
  local_c = 0;
  if (DAT_00461e80 == 0) {
    for (local_18 = DAT_00461dcc; local_18 != 0; local_18 = *(int *)(local_18 + 0xc)) {
      DAT_00461e80 = local_18;
    }
  }
  *(int *)(DAT_00461e80 + 0xc) = DAT_00461dcc;
  for (local_18 = *(int *)(DAT_00461dcc + 0xc); local_18 != 0; local_18 = *(int *)(local_18 + 0xc))
  {
    DAT_00461dd0 = local_18;
    piVar2 = (int *)FUN_0040e832(local_18);
    for (local_28 = piVar2; *local_28 != 0; local_28 = local_28 + 1) {
      piVar1 = (int *)*local_28;
      DAT_00461dd4 = piVar1;
      if ((piVar1[2] & 0x4000U) != 0) {
        if (piVar1[3] != local_14) {
          local_14 = piVar1[3];
          local_c = thunk_FUN_0042f22f(piVar1[3]);
        }
        piVar3 = FUN_00410c8b((int)piVar1);
        if (piVar3 != (int *)0x0) {
          piVar1[0xb] = piVar1[7];
          if ((piVar1[2] & 0x1000U) != 0) {
            FUN_00410d70(piVar1,piVar3,local_c);
          }
          if ((piVar1[2] & 0x200U) != 0) {
            FUN_00410fe8(piVar1,piVar3,local_c);
          }
          if ((piVar1[2] & 0x100U) != 0) {
            FUN_00411200(piVar1,piVar3,local_c);
          }
          FUN_00411450(piVar1,piVar3,local_c);
          for (local_8 = piVar3; *local_8 != 0; local_8 = local_8 + 1) {
            *(undefined4 *)(*local_8 + 0x14) = *(undefined4 *)(*local_8 + 0x10);
          }
          thunk_FUN_0042e1ce((undefined *)piVar3);
        }
      }
    }
    if (local_18 == DAT_00461dcc) {
      local_18 = DAT_00461e80;
      *(undefined4 *)(DAT_00461e80 + 0xc) = 0;
    }
    thunk_FUN_0042e1ce((undefined *)piVar2);
  }
  return;
}


/* ==== FUN_00410c8b @ 00410c8b ==== */

int * __cdecl FUN_00410c8b(int param_1)

{
  int local_18;
  int local_14;
  undefined4 *local_10;
  int local_c;
  int *local_8;
  
  local_14 = 0;
  local_18 = 0;
  local_8 = (int *)thunk_FUN_0042e170(4);
  for (local_10 = *(undefined4 **)(param_1 + 0x30); local_10 != (undefined4 *)0x0;
      local_10 = (undefined4 *)local_10[1]) {
    if (*(int *)(*(int *)*local_10 + 0x34) != 0) {
      local_18 = local_18 + *(int *)(*(int *)*local_10 + 0x34);
      local_8 = thunk_FUN_0042e19d(local_8,local_18 * 4 + 4);
      for (local_c = *(int *)(*(int *)*local_10 + 0x24); local_c != 0;
          local_c = *(int *)(local_c + 0x44)) {
        local_8[local_14] = local_c;
        local_14 = local_14 + 1;
      }
    }
  }
  if (local_18 == 0) {
    thunk_FUN_0042e1ce((undefined *)local_8);
    local_8 = (int *)0x0;
  }
  else {
    local_8[local_14] = 0;
    thunk_FUN_0041eda4(local_8,local_14);
  }
  return local_8;
}


/* ==== FUN_00410d70 @ 00410d70 ==== */

void __cdecl FUN_00410d70(int *param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int *local_28;
  uint local_24;
  int local_1c;
  int *local_c;
  int local_8;
  
  local_1c = 0;
  local_c = param_2;
  do {
    if (*local_c == 0) {
      return;
    }
    local_28 = (int *)*local_c;
    if ((local_28[3] & 0x1000U) != 0) {
      local_24 = local_28[5];
      local_8 = 0;
      if ((((local_28[0xe] != 0) && (*(int *)local_28[0xe] != 0)) &&
          (*(int *)(local_28[0xe] + 0x28) != 0)) && (*(int *)(local_28[0xf] + 0x1c) != 0)) {
        *(undefined4 *)(*(int *)(local_28[0xf] + 0x1c) + 0x18) =
             *(undefined4 *)
              (*(int *)(local_28[0xe] + 0x28) + 0x1c + (*(int *)local_28[0xe] + -1) * 0x2c);
      }
      iVar1 = *(int *)(*(int *)*local_28 + 4);
      while( true ) {
        piVar5 = local_c;
        local_c = piVar5 + 1;
        piVar2 = (int *)*local_c;
        piVar6 = local_c;
        if (piVar2 == (int *)0x0) break;
        if ((((local_28[2] & 0x1000U) == 0) || ((piVar2[2] & 0x1000U) != 0)) &&
           (((local_28[2] & 0x1000U) != 0 || ((piVar2[2] & 0x1000U) == 0)))) {
          piVar6 = piVar5;
          if (((piVar2[3] & 0x1000U) != 0) || (*(int *)(*(int *)*piVar2 + 4) != iVar1)) break;
          iVar3 = piVar2[5];
          iVar4 = piVar2[4];
          piVar2[4] = local_24;
          *(int *)(piVar2[0xf] + 0x18) = local_8;
          if ((((piVar2[0xe] != 0) && (*(int *)piVar2[0xe] != 0)) &&
              (*(int *)(piVar2[0xe] + 0x28) != 0)) &&
             (local_8 = local_8 + *(int *)(*(int *)(piVar2[0xe] + 0x28) + 0x1c +
                                          (*(int *)piVar2[0xe] + -1) * 0x2c),
             *(int *)(piVar2[0xf] + 0x1c) != 0)) {
            *(undefined4 *)(*(int *)(piVar2[0xf] + 0x1c) + 0x18) =
                 *(undefined4 *)
                  (*(int *)(piVar2[0xe] + 0x28) + 0x1c + (*(int *)piVar2[0xe] + -1) * 0x2c);
          }
          FUN_004115dd(param_1,piVar2,param_3,local_24,local_24 + (iVar3 - iVar4),(int)DAT_00461228)
          ;
          if (((piVar2[2] & 0x10000U) == 0) && (*(int *)piVar2[0xf] == local_1c)) {
            *(int **)(piVar2[0xf] + 0x10) = local_28;
          }
          else {
            local_1c = *(int *)piVar2[0xf];
            local_28 = piVar2;
          }
          piVar2[3] = piVar2[3] | 0x1000;
          local_24 = local_24 + (iVar3 - iVar4);
        }
      }
      local_c = piVar6;
      if (*local_c == 0) {
        return;
      }
    }
    local_c = local_c + 1;
  } while( true );
}


/* ==== FUN_00410fe8 @ 00410fe8 ==== */

void __cdecl FUN_00410fe8(int *param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *local_2c;
  uint local_28;
  int local_20;
  int *local_c;
  int local_8;
  
  local_20 = 0;
  local_c = param_2;
  do {
    if (*local_c == 0) {
      return;
    }
    local_2c = (int *)*local_c;
    if (((local_2c[2] & 0x1000U) != 0) && ((local_2c[3] & 0x1000U) == 0)) {
      iVar1 = *(int *)(*(int *)*local_2c + 4);
      if ((*(uint *)(*(int *)(*local_2c + 0x18) + 0xc) & 0x200) != 0) {
        local_28 = *(uint *)(*(int *)(*local_2c + 0x18) + 0x14);
        local_8 = 0;
        for (; piVar2 = (int *)*local_c, piVar2 != (int *)0x0; local_c = local_c + 1) {
          if (((piVar2[2] & 0x1000U) != 0) && ((piVar2[3] & 0x1000U) == 0)) {
            if (*(int *)(*(int *)*piVar2 + 4) != iVar1) {
              local_c = local_c + -1;
              break;
            }
            iVar3 = piVar2[5];
            iVar4 = piVar2[4];
            piVar2[4] = local_28;
            *(int *)(piVar2[0xf] + 0x18) = local_8;
            if ((((piVar2[0xe] != 0) && (*(int *)piVar2[0xe] != 0)) &&
                (*(int *)(piVar2[0xe] + 0x28) != 0)) &&
               (local_8 = local_8 + *(int *)(*(int *)(piVar2[0xe] + 0x28) + 0x1c +
                                            (*(int *)piVar2[0xe] + -1) * 0x2c),
               *(int *)(piVar2[0xf] + 0x1c) != 0)) {
              *(undefined4 *)(*(int *)(piVar2[0xf] + 0x1c) + 0x18) =
                   *(undefined4 *)
                    (*(int *)(piVar2[0xe] + 0x28) + 0x1c + (*(int *)piVar2[0xe] + -1) * 0x2c);
            }
            FUN_004115dd(param_1,piVar2,param_3,local_28,local_28 + (iVar3 - iVar4),
                         (int)DAT_00461228);
            if (((piVar2[2] & 0x10000U) == 0) && (*(int *)piVar2[0xf] == local_20)) {
              *(int **)(piVar2[0xf] + 0x10) = local_2c;
            }
            else {
              local_20 = *(int *)piVar2[0xf];
              local_2c = piVar2;
            }
            piVar2[3] = piVar2[3] | 0x1000;
            local_28 = local_28 + (iVar3 - iVar4);
          }
        }
        if (*local_c == 0) {
          return;
        }
      }
    }
    local_c = local_c + 1;
  } while( true );
}


/* ==== FUN_00411200 @ 00411200 ==== */

void __cdecl FUN_00411200(int *param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *local_34;
  uint local_30;
  int local_28;
  int *local_18;
  int *local_c;
  int local_8;
  
  local_34 = (int *)0x0;
  local_28 = 0;
  local_30 = param_1[0xb];
  for (local_18 = (int *)param_1[0xc]; local_18 != (int *)0x0; local_18 = (int *)local_18[1]) {
    if ((((undefined4 *)*local_18)[3] & 0x100) != 0) {
      iVar1 = *(int *)(**(int **)*local_18 + 4);
      local_c = param_2;
      while ((*local_c != 0 && (*(int *)(**(int **)*local_c + 4) < iVar1))) {
        local_c = local_c + 1;
      }
      if (*local_c != 0) {
        local_34 = (int *)*local_c;
      }
      local_8 = 0;
      while ((piVar2 = (int *)*local_c, piVar2 != (int *)0x0 &&
             (*(int *)(*(int *)*piVar2 + 4) == iVar1))) {
        if (((piVar2[2] & 0x1000U) != 0) && ((piVar2[3] & 0x1000U) == 0)) {
          iVar3 = piVar2[5];
          iVar4 = piVar2[4];
          if (*(uint *)(piVar2[0xf] + 0x14) != 0) {
            local_30 = thunk_FUN_00430ac9(local_30,*(uint *)(piVar2[0xf] + 0x14),DAT_00461f74);
          }
          piVar2[4] = local_30;
          *(int *)(piVar2[0xf] + 0x18) = local_8;
          if ((((piVar2[0xe] != 0) && (*(int *)piVar2[0xe] != 0)) &&
              (*(int *)(piVar2[0xe] + 0x28) != 0)) &&
             (local_8 = local_8 + *(int *)(*(int *)(piVar2[0xe] + 0x28) + 0x1c +
                                          (*(int *)piVar2[0xe] + -1) * 0x2c),
             *(int *)(piVar2[0xf] + 0x1c) != 0)) {
            *(undefined4 *)(*(int *)(piVar2[0xf] + 0x1c) + 0x18) =
                 *(undefined4 *)
                  (*(int *)(piVar2[0xe] + 0x28) + 0x1c + (*(int *)piVar2[0xe] + -1) * 0x2c);
          }
          FUN_004115dd(param_1,piVar2,param_3,local_30,local_30 + (iVar3 - iVar4),(int)DAT_00457b80)
          ;
          if (((piVar2[2] & 0x10000U) == 0) && (*(int *)piVar2[0xf] == local_28)) {
            *(int **)(piVar2[0xf] + 0x10) = local_34;
          }
          else {
            local_28 = *(int *)piVar2[0xf];
            local_34 = piVar2;
          }
          piVar2[3] = piVar2[3] | 0x1000;
          local_30 = local_30 + (iVar3 - iVar4);
        }
        local_c = local_c + 1;
      }
    }
  }
  param_1[0xb] = local_30;
  return;
}


/* ==== FUN_00411450 @ 00411450 ==== */

void __cdecl FUN_00411450(int *param_1,undefined4 *param_2,undefined4 param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *local_20;
  uint local_1c;
  int local_14;
  undefined4 *local_c;
  int local_8;
  
  local_20 = (int *)0x0;
  local_14 = 0;
  local_1c = param_1[0xb];
  local_8 = 0;
  for (local_c = param_2; piVar1 = (int *)*local_c, piVar1 != (int *)0x0; local_c = local_c + 1) {
    if (((piVar1[2] & 0x1000U) != 0) && ((piVar1[3] & 0x1000U) == 0)) {
      iVar2 = piVar1[5];
      iVar3 = piVar1[4];
      piVar1[4] = local_1c;
      *(int *)(piVar1[0xf] + 0x18) = local_8;
      if ((piVar1[0xe] != 0) &&
         (((*(int *)piVar1[0xe] != 0 && (*(int *)(piVar1[0xe] + 0x28) != 0)) &&
          (local_8 = local_8 + *(int *)(*(int *)(piVar1[0xe] + 0x28) + 0x1c +
                                       (*(int *)piVar1[0xe] + -1) * 0x2c),
          *(int *)(piVar1[0xf] + 0x1c) != 0)))) {
        *(undefined4 *)(*(int *)(piVar1[0xf] + 0x1c) + 0x18) =
             *(undefined4 *)
              (*(int *)(piVar1[0xe] + 0x28) + 0x1c + (*(int *)piVar1[0xe] + -1) * 0x2c);
      }
      FUN_004115dd(param_1,piVar1,param_3,local_1c,local_1c + (iVar2 - iVar3),(int)DAT_00457b80);
      if (((piVar1[2] & 0x10000U) == 0) && (*(int *)piVar1[0xf] == local_14)) {
        *(int **)(piVar1[0xf] + 0x10) = local_20;
      }
      else {
        local_14 = *(int *)piVar1[0xf];
        local_20 = piVar1;
      }
      piVar1[3] = piVar1[3] | 0x1000;
      local_1c = local_1c + (iVar2 - iVar3);
    }
  }
  param_1[0xb] = local_1c;
  return;
}


/* ==== FUN_004115dd @ 004115dd ==== */

void __cdecl
FUN_004115dd(int *param_1,int *param_2,int param_3,uint param_4,uint param_5,int param_6)

{
  undefined4 va1;
  int iVar1;
  uint va4;
  undefined4 *local_420;
  char *local_408;
  char local_404 [1024];
  
  local_408 = s_Relative_004563dc;
  if (param_6 != 0) {
    iVar1 = thunk_FUN_0042f2b0(param_3);
    for (local_420 = *(undefined4 **)(*param_1 + 8);
        (local_420 != (undefined4 *)0x0 &&
        ((local_420[3] != iVar1 || (local_420[5] != *(int *)(*param_2 + 0x10)))));
        local_420 = (undefined4 *)local_420[0xe]) {
    }
    if (local_420 != (undefined4 *)0x0) {
      if ((param_2[2] & 0x2000U) == 0) {
        if ((param_2[2] & 0x4000U) == 0) {
          if ((param_2[2] & 0x1000U) == 0) {
            local_408 = s_Absolute_004563f8;
          }
        }
        else {
          local_408 = s_Overlay_004563f0;
        }
      }
      else {
        local_408 = s_Buffer_004563e8;
      }
      va1 = **(undefined4 **)*param_2;
      if (param_4 < (uint)local_420[7]) {
        sprintf(local_404,s__s_section___s___c__ld__start_ad_00456404,local_408,va1,
                (int)s_XYLPEDU_00457ff0[param_3],local_420[5],param_4,*(undefined4 *)*local_420,
                local_420[7]);
        thunk_FUN_00409a25(local_404);
      }
      if (param_5 == 0) {
        va4 = 0;
      }
      else {
        va4 = param_5 - 1;
      }
      if ((uint)local_420[8] < va4) {
        sprintf(local_404,s__s_section___s___c__ld__end_addr_00456458,local_408,va1,
                (int)s_XYLPEDU_00457ff0[param_3],local_420[5],va4,*(undefined4 *)*local_420,
                local_420[8]);
        thunk_FUN_00409a25(local_404);
      }
    }
  }
  return;
}


