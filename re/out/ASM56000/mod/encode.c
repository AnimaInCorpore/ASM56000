/* encode: 70 functions from ASM56000 */

/* ==== FUN_00410901 @ 00410901 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00410901(void)

{
  DAT_0045fbf4 = 0;
  DAT_0045fc04 = 0;
  DAT_0045fbf8 = 0;
  DAT_0045fc00 = 0;
  DAT_0045fbfc = 0;
  _DAT_0044f98c = 4;
  DAT_0045fc18 = 0;
  return;
}


/* ==== FUN_00410950 @ 00410950 ==== */

void __cdecl FUN_00410950(int param_1,int param_2,int param_3)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  
  bVar3 = 2;
  bVar2 = 0;
  uVar1 = FUN_00410994(*(int *)(param_3 + 0x14));
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4) | 0xb8,uVar1,bVar2,bVar3);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_0043bdfb(param_1,param_2,8,8);
  return;
}


/* ==== FUN_00410994 @ 00410994 ==== */

undefined4 __cdecl FUN_00410994(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0x2a) {
    uVar1 = 2;
  }
  else if (param_1 == 0x31) {
    uVar1 = 0;
  }
  else if (param_1 == 0x32) {
    uVar1 = 1;
  }
  else {
    FUN_00412fa0((uint *)s_EE_encoding_failure_00453bc4);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_004109d7 @ 004109d7 ==== */

void __cdecl FUN_004109d7(int param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 1;
  bVar3 = 3;
  uVar1 = FUN_00410a2b(*(int *)(param_3 + 0x14));
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),uVar1,bVar3,bVar4);
  bVar4 = 2;
  bVar3 = 4;
  uVar2 = FUN_00410a61(*(undefined4 *)(param_2 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  *(uint *)(param_1 + 4) = uVar1;
  return;
}


/* ==== FUN_00410a2b @ 00410a2b ==== */

undefined4 __cdecl FUN_00410a2b(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 2) {
    uVar1 = 0;
  }
  else if (param_1 == 3) {
    uVar1 = 1;
  }
  else {
    FUN_00412fa0((uint *)s_D_encoding_failure_00453bd8);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_00410a61 @ 00410a61 ==== */

undefined4 __cdecl FUN_00410a61(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 2:
  case 3:
    uVar1 = 0;
    break;
  case 4:
    uVar1 = 4;
    break;
  case 5:
    uVar1 = 5;
    break;
  case 6:
    uVar1 = 6;
    break;
  case 7:
    uVar1 = 7;
    break;
  default:
    FUN_00412fa0((uint *)s_DXY_encoding_failure_00453bec);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_00410acf @ 00410acf ==== */

void __cdecl FUN_00410acf(int param_1,int *param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 1;
  bVar3 = 3;
  uVar1 = FUN_00410a2b(*(int *)(param_3 + 0x14));
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),uVar1,bVar3,bVar4);
  bVar4 = 3;
  bVar3 = 8;
  uVar2 = FUN_00410b29(*param_2,param_2[5]);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  *(uint *)(param_1 + 4) = uVar1;
  return;
}


/* ==== FUN_00410b29 @ 00410b29 ==== */

undefined4 __cdecl FUN_00410b29(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (param_1 == 0xe) {
    uVar1 = 0;
  }
  else if (param_1 == 9) {
    uVar1 = 4;
  }
  else {
    switch(param_2) {
    case 0xe:
      uVar1 = 0;
      break;
    case 0xf:
      uVar1 = 1;
      break;
    case 0x10:
      uVar1 = 2;
      break;
    case 0x11:
      uVar1 = 3;
      break;
    case 0x12:
      uVar1 = 4;
      break;
    case 0x13:
      uVar1 = 5;
      break;
    case 0x14:
      uVar1 = 6;
      break;
    case 0x15:
      uVar1 = 7;
      break;
    default:
      FUN_00412fa0((uint *)s_RRR_encoding_failure_00453c04);
      uVar1 = 0;
    }
  }
  return uVar1;
}


/* ==== FUN_00410bcb @ 00410bcb ==== */

void __cdecl FUN_00410bcb(int param_1,int *param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  uint uVar2;
  uint uVar3;
  byte bVar4;
  byte bVar5;
  
  bVar5 = 1;
  bVar4 = 6;
  bVar1 = FUN_00410cfb(param_2[1]);
  uVar2 = FUN_0043bd1e(*(uint *)(param_1 + 4),CONCAT31(extraout_var,bVar1),bVar4,bVar5);
  bVar5 = 3;
  bVar4 = 8;
  uVar3 = FUN_00410b29(*param_2,param_2[5]);
  uVar2 = FUN_0043bd1e(uVar2,uVar3,bVar4,bVar5);
  bVar5 = 3;
  bVar4 = 0xb;
  uVar3 = FUN_00410c5c(*param_2);
  uVar2 = FUN_0043bd1e(uVar2,uVar3,bVar4,bVar5);
  uVar2 = FUN_0043bd1e(uVar2,1,0xe,1);
  *(uint *)(param_1 + 4) = uVar2;
  return;
}


/* ==== FUN_00410c5c @ 00410c5c ==== */

undefined4 __cdecl FUN_00410c5c(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 2:
    uVar1 = 4;
    break;
  case 3:
    uVar1 = 3;
    break;
  case 4:
    uVar1 = 2;
    break;
  case 5:
    uVar1 = 1;
    break;
  case 6:
    uVar1 = 0;
    break;
  case 7:
    uVar1 = 5;
    break;
  case 8:
    uVar1 = 7;
    break;
  case 9:
  case 0xe:
    uVar1 = 6;
    break;
  default:
    FUN_00412fa0((uint *)s_MMM_encoding_failure_00453c1c);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_00410cfb @ 00410cfb ==== */

bool __cdecl FUN_00410cfb(int param_1)

{
  return param_1 == 2;
}


/* ==== FUN_00410d0f @ 00410d0f ==== */

void __cdecl FUN_00410d0f(int param_1,int param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 1;
  bVar3 = 6;
  bVar1 = FUN_00410cfb(*(int *)(param_2 + 4));
  uVar2 = FUN_0043bd1e(*(uint *)(param_1 + 4),CONCAT31(extraout_var,bVar1),bVar3,bVar4);
  *(uint *)(param_1 + 4) = uVar2;
  FUN_0043bdfb(param_1,param_2,8,6);
  return;
}


/* ==== FUN_00410d51 @ 00410d51 ==== */

void __cdecl FUN_00410d51(int param_1,int param_2)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  
  bVar3 = 6;
  bVar2 = 8;
  uVar1 = FUN_00410d97(*(undefined4 *)(param_2 + 0x14));
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),uVar1,bVar2,bVar3);
  uVar1 = FUN_0043bd1e(uVar1,3,0xe,2);
  *(uint *)(param_1 + 4) = uVar1;
  return;
}


/* ==== FUN_00410d97 @ 00410d97 ==== */

int __cdecl FUN_00410d97(undefined4 param_1)

{
  int iVar1;
  
  switch(param_1) {
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
    iVar1 = FUN_00410ec7(param_1);
    break;
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
    iVar1 = FUN_00411079(param_1);
    iVar1 = iVar1 + 0x20;
    break;
  default:
    FUN_00412fa0((uint *)s_D6_encoding_failure_00453c34);
    iVar1 = 0;
    break;
  case 0x2a:
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
    iVar1 = FUN_00410e44(param_1);
    iVar1 = iVar1 + 0x38;
  }
  return iVar1;
}


/* ==== FUN_00410e44 @ 00410e44 ==== */

undefined4 __cdecl FUN_00410e44(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 0x2a:
    uVar1 = 2;
    break;
  case 0x2b:
    uVar1 = 1;
    break;
  case 0x2c:
    uVar1 = 6;
    break;
  case 0x2d:
    uVar1 = 7;
    break;
  case 0x2e:
    uVar1 = 4;
    break;
  case 0x2f:
    uVar1 = 5;
    break;
  case 0x30:
    uVar1 = 3;
    break;
  default:
    FUN_00412fa0((uint *)s_CCC_encoding_failure_00453c48);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_00410ec7 @ 00410ec7 ==== */

int __cdecl FUN_00410ec7(undefined4 param_1)

{
  int iVar1;
  
  switch(param_1) {
  case 2:
  case 3:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
    iVar1 = FUN_00410fde(param_1);
    iVar1 = iVar1 + 8;
    break;
  case 4:
  case 5:
  case 6:
  case 7:
    iVar1 = FUN_00410f7f(param_1);
    iVar1 = iVar1 + 4;
    break;
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
    iVar1 = FUN_00410b29(0,param_1);
    iVar1 = iVar1 + 0x10;
    break;
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
    iVar1 = FUN_00411104(param_1);
    iVar1 = iVar1 + 0x18;
    break;
  default:
    FUN_00412fa0((uint *)s_DDDDD_encoding_failure_00453c60);
    iVar1 = 0;
  }
  return iVar1;
}


/* ==== FUN_00410f7f @ 00410f7f ==== */

undefined4 __cdecl FUN_00410f7f(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 4:
    uVar1 = 0;
    break;
  case 5:
    uVar1 = 2;
    break;
  case 6:
    uVar1 = 1;
    break;
  case 7:
    uVar1 = 3;
    break;
  default:
    FUN_00412fa0((uint *)s_DD_encoding_failure_00453c78);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_00410fde @ 00410fde ==== */

undefined4 __cdecl FUN_00410fde(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 2:
    uVar1 = 6;
    break;
  case 3:
    uVar1 = 7;
    break;
  default:
    FUN_00412fa0((uint *)s_DDD_encoding_failure_00453c8c);
    uVar1 = 0;
    break;
  case 8:
    uVar1 = 0;
    break;
  case 9:
    uVar1 = 1;
    break;
  case 10:
    uVar1 = 4;
    break;
  case 0xb:
    uVar1 = 5;
    break;
  case 0xc:
    uVar1 = 2;
    break;
  case 0xd:
    uVar1 = 3;
  }
  return uVar1;
}


/* ==== FUN_00411079 @ 00411079 ==== */

undefined4 __cdecl FUN_00411079(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 0x1e:
    uVar1 = 0;
    break;
  case 0x1f:
    uVar1 = 1;
    break;
  case 0x20:
    uVar1 = 2;
    break;
  case 0x21:
    uVar1 = 3;
    break;
  case 0x22:
    uVar1 = 4;
    break;
  case 0x23:
    uVar1 = 5;
    break;
  case 0x24:
    uVar1 = 6;
    break;
  case 0x25:
    uVar1 = 7;
    break;
  default:
    FUN_00412fa0((uint *)s_FFF_encoding_failure_00453ca4);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_00411104 @ 00411104 ==== */

undefined4 __cdecl FUN_00411104(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 0x16:
    uVar1 = 0;
    break;
  case 0x17:
    uVar1 = 1;
    break;
  case 0x18:
    uVar1 = 2;
    break;
  case 0x19:
    uVar1 = 3;
    break;
  case 0x1a:
    uVar1 = 4;
    break;
  case 0x1b:
    uVar1 = 5;
    break;
  case 0x1c:
    uVar1 = 6;
    break;
  case 0x1d:
    uVar1 = 7;
    break;
  default:
    FUN_00412fa0((uint *)s_NNN_encoding_failure_00453cbc);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_0041118f @ 0041118f ==== */

void __cdecl FUN_0041118f(int param_1,int param_2)

{
  undefined uVar1;
  undefined uVar2;
  uint uVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  char local_404 [1024];
  
  uVar3 = FUN_0043bd1e(*(uint *)(param_1 + 4),1,7,1);
  if (*(int *)(param_2 + 0x1c) == 0) {
    uVar3 = FUN_0043bd1e(uVar3,*(int *)(param_2 + 0x10) >> 8,0,4);
    uVar3 = FUN_0043bd1e(uVar3,*(uint *)(param_2 + 0x10),8,8);
    *(uint *)(param_1 + 4) = uVar3;
  }
  else {
    sprintf(&DAT_0045f220,s___06lx_00453cd4,uVar3);
    FUN_0043b7aa(&DAT_0045f220);
    sprintf(local_404,s___s>>8__00453cdc,*(undefined4 *)(param_2 + 0x1c));
    uVar1 = FUN_0043bd53(&DAT_0045f220,local_404,0,4);
    uVar2 = FUN_0043bd53((undefined *)CONCAT31(extraout_var,uVar1),*(undefined4 *)(param_2 + 0x1c),8
                         ,8);
    *(uint *)(param_1 + 0x40) = CONCAT31(extraout_var_00,uVar2);
    FUN_004398b5((undefined *)CONCAT31(extraout_var,uVar1));
    FUN_004398b5(*(undefined **)(param_2 + 0x1c));
    *(undefined4 *)(param_2 + 0x1c) = 0;
  }
  return;
}


/* ==== FUN_004112b9 @ 004112b9 ==== */

void __cdecl FUN_004112b9(undefined4 *param_1,int *param_2,int *param_3)

{
  FUN_00410bcb((int)param_1,param_2);
  FUN_004112e0(param_1,param_3,1);
  return;
}


/* ==== FUN_004112e0 @ 004112e0 ==== */

void __cdecl FUN_004112e0(undefined4 *param_1,int *param_2,int param_3)

{
  char *s;
  uint uVar1;
  char *buf;
  
  if ((*param_2 == 0xe) || (*param_2 == 9)) {
    param_1[2] = param_2[4];
    if (param_2[7] != 0) {
      param_1[0x11] = param_2[7];
      param_2[7] = 0;
    }
    *param_1 = 2;
    if (param_3 != 0) {
      if (param_1[2] != 0) {
        param_1[2] = param_1[2] + -1;
      }
      s = (char *)param_1[0x11];
      if (s != (char *)0x0) {
        uVar1 = strlen(s);
        buf = (char *)FUN_00439857(uVar1 + 8);
        sprintf(buf,&DAT_00453ce4,s);
        FUN_004398b5(s);
        param_1[0x11] = buf;
      }
    }
  }
  return;
}


/* ==== FUN_004113ae @ 004113ae ==== */

void __cdecl FUN_004113ae(undefined4 *param_1,int param_2,int *param_3)

{
  FUN_00410d0f((int)param_1,param_2);
  FUN_004112e0(param_1,param_3,1);
  return;
}


/* ==== FUN_004113d5 @ 004113d5 ==== */

void __cdecl FUN_004113d5(undefined4 *param_1,int param_2,int *param_3)

{
  FUN_00410d51((int)param_1,param_2);
  FUN_004112e0(param_1,param_3,1);
  return;
}


/* ==== FUN_004113fc @ 004113fc ==== */

void __cdecl FUN_004113fc(undefined4 *param_1,int param_2,int *param_3)

{
  FUN_0041118f((int)param_1,param_2);
  FUN_004112e0(param_1,param_3,1);
  return;
}


/* ==== FUN_00411423 @ 00411423 ==== */

void __cdecl FUN_00411423(int param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),1,0x12,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_0043bdfb(param_1,param_2,0,0xc);
  return;
}


/* ==== FUN_00411457 @ 00411457 ==== */

void __cdecl FUN_00411457(undefined4 *param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  uVar1 = FUN_0043bd1e(param_1[1],1,7,1);
  bVar4 = 3;
  bVar3 = 8;
  uVar2 = FUN_00410b29(*param_2,param_2[5]);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  bVar4 = 3;
  bVar3 = 0xb;
  uVar2 = FUN_00410c5c(*param_2);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,3,0xe,2);
  uVar1 = FUN_0043bd1e(uVar1,1,0x11,1);
  param_1[1] = uVar1;
  FUN_004112e0(param_1,param_2,0);
  return;
}


/* ==== FUN_00411501 @ 00411501 ==== */

void __cdecl FUN_00411501(int param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),1,0x12,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_0043bdfb(param_1,param_2,0,0xc);
  return;
}


/* ==== FUN_00411535 @ 00411535 ==== */

void __cdecl FUN_00411535(undefined4 *param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  uVar1 = FUN_0043bd1e(param_1[1] | (uint)param_1[1] >> 0xc & 0xf,5,5,3);
  bVar4 = 3;
  bVar3 = 8;
  uVar2 = FUN_00410b29(*param_2,param_2[5]);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  bVar4 = 3;
  bVar3 = 0xb;
  uVar2 = FUN_00410c5c(*param_2);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,3,0xe,2);
  param_1[1] = uVar1;
  FUN_004112e0(param_1,param_2,0);
  return;
}


/* ==== FUN_004115dc @ 004115dc ==== */

void __cdecl FUN_004115dc(int param_1,int param_2,int param_3,int *param_4,int *param_5)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 3;
  bVar3 = 0;
  uVar1 = FUN_00410b29(*param_5,param_5[5]);
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),uVar1,bVar3,bVar4);
  bVar4 = 1;
  bVar3 = 3;
  uVar2 = FUN_00410a2b(*(int *)(param_3 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  bVar4 = 3;
  bVar3 = 4;
  uVar2 = FUN_00410a61(*(undefined4 *)(param_2 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  bVar4 = 3;
  bVar3 = 8;
  uVar2 = FUN_00410b29(*param_4,param_4[5]);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,1,0x10,1);
  *(uint *)(param_1 + 4) = uVar1;
  return;
}


/* ==== FUN_00411697 @ 00411697 ==== */

void __cdecl FUN_00411697(int param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 1;
  bVar3 = 3;
  uVar1 = FUN_00410a2b(*(int *)(param_3 + 0x14));
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),uVar1,bVar3,bVar4);
  bVar4 = 3;
  bVar3 = 4;
  uVar2 = FUN_00410a61(*(undefined4 *)(param_2 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  *(uint *)(param_1 + 4) = uVar1;
  return;
}


/* ==== FUN_004116eb @ 004116eb ==== */

void __cdecl FUN_004116eb(undefined4 *param_1,int param_2,int *param_3)

{
  bool bVar1;
  undefined3 extraout_var;
  uint uVar2;
  uint uVar3;
  byte bVar4;
  byte bVar5;
  
  bVar5 = 1;
  bVar4 = 6;
  bVar1 = FUN_00410cfb(param_3[1]);
  uVar2 = FUN_0043bd1e(param_1[1],CONCAT31(extraout_var,bVar1),bVar4,bVar5);
  bVar5 = 3;
  bVar4 = 8;
  uVar3 = FUN_00410b29(*param_3,param_3[5]);
  uVar2 = FUN_0043bd1e(uVar2,uVar3,bVar4,bVar5);
  bVar5 = 3;
  bVar4 = 0xb;
  uVar3 = FUN_00410c5c(*param_3);
  uVar2 = FUN_0043bd1e(uVar2,uVar3,bVar4,bVar5);
  uVar2 = FUN_0043bd1e(uVar2,1,0xe,1);
  param_1[1] = uVar2;
  FUN_0043bdfb((int)param_1,param_2,0,5);
  FUN_004112e0(param_1,param_3,0);
  return;
}


/* ==== FUN_004117a2 @ 004117a2 ==== */

void __cdecl FUN_004117a2(int param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),0x301,6,10);
  bVar4 = 6;
  bVar3 = 8;
  uVar2 = FUN_00410d97(*(undefined4 *)(param_3 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_0043bdfb(param_1,param_2,0,5);
  return;
}


/* ==== FUN_004117ff @ 004117ff ==== */

void __cdecl FUN_004117ff(int param_1,int param_2,int param_3)

{
  bool bVar1;
  undefined uVar2;
  undefined uVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  byte bVar4;
  byte bVar5;
  uint local_c;
  
  bVar5 = 1;
  bVar4 = 6;
  bVar1 = FUN_00410cfb(*(int *)(param_3 + 4));
  local_c = FUN_0043bd1e(*(uint *)(param_1 + 4),CONCAT31(extraout_var,bVar1),bVar4,bVar5);
  if (*(int *)(param_2 + 0x1c) == 0) {
    local_c = FUN_0043bd1e(local_c,*(uint *)(param_2 + 0x10),0,5);
  }
  if (*(int *)(param_3 + 0x1c) == 0) {
    local_c = FUN_0043bd1e(local_c,*(uint *)(param_3 + 0x10),8,6);
  }
  *(uint *)(param_1 + 4) = local_c;
  sprintf(&DAT_0045f220,s___06lx_00453cec,local_c);
  FUN_0043b7aa(&DAT_0045f220);
  if ((*(int *)(param_2 + 0x1c) == 0) || (*(int *)(param_3 + 0x1c) != 0)) {
    if ((*(int *)(param_3 + 0x1c) == 0) || (*(int *)(param_2 + 0x1c) != 0)) {
      if ((*(int *)(param_2 + 0x1c) != 0) && (*(int *)(param_3 + 0x1c) != 0)) {
        uVar2 = FUN_0043bd53(&DAT_0045f220,*(undefined4 *)(param_2 + 0x1c),0,5);
        uVar3 = FUN_0043bd53((undefined *)CONCAT31(extraout_var_02,uVar2),
                             *(undefined4 *)(param_3 + 0x1c),8,6);
        *(uint *)(param_1 + 0x40) = CONCAT31(extraout_var_03,uVar3);
        FUN_004398b5(*(undefined **)(param_2 + 0x1c));
        *(undefined4 *)(param_2 + 0x1c) = 0;
        FUN_004398b5(*(undefined **)(param_3 + 0x1c));
        *(undefined4 *)(param_3 + 0x1c) = 0;
        FUN_004398b5((undefined *)CONCAT31(extraout_var_02,uVar2));
      }
    }
    else {
      uVar2 = FUN_0043bd53(&DAT_0045f220,*(undefined4 *)(param_3 + 0x1c),8,6);
      *(uint *)(param_1 + 0x40) = CONCAT31(extraout_var_01,uVar2);
      FUN_004398b5(*(undefined **)(param_3 + 0x1c));
      *(undefined4 *)(param_3 + 0x1c) = 0;
    }
  }
  else {
    uVar2 = FUN_0043bd53(&DAT_0045f220,*(undefined4 *)(param_2 + 0x1c),0,5);
    *(uint *)(param_1 + 0x40) = CONCAT31(extraout_var_00,uVar2);
    FUN_004398b5(*(undefined **)(param_2 + 0x1c));
    *(undefined4 *)(param_2 + 0x1c) = 0;
  }
  *(undefined4 *)(param_2 + 0x1c) = 0;
  *(undefined4 *)(param_3 + 0x1c) = 0;
  return;
}


/* ==== FUN_004119e4 @ 004119e4 ==== */

void __cdecl FUN_004119e4(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),1,0xf,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_004117ff(param_1,param_2,param_3);
  return;
}


/* ==== FUN_00411a18 @ 00411a18 ==== */

void __cdecl FUN_00411a18(undefined4 *param_1,int param_2,int *param_3,int *param_4)

{
  FUN_004116eb(param_1,param_2,param_3);
  FUN_004112e0(param_1,param_4,0);
  return;
}


/* ==== FUN_00411a43 @ 00411a43 ==== */

void __cdecl FUN_00411a43(undefined4 *param_1,int param_2,int param_3,int *param_4)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  uVar1 = FUN_0043bd1e(param_1[1],0x180,7,9);
  bVar4 = 6;
  bVar3 = 8;
  uVar2 = FUN_00410d97(*(undefined4 *)(param_3 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  param_1[1] = uVar1;
  FUN_0043bdfb((int)param_1,param_2,0,5);
  FUN_004112e0(param_1,param_4,0);
  return;
}


/* ==== FUN_00411ab2 @ 00411ab2 ==== */

void __cdecl FUN_00411ab2(undefined4 *param_1,int param_2,int param_3,int *param_4)

{
  FUN_004117ff((int)param_1,param_2,param_3);
  FUN_004112e0(param_1,param_4,0);
  return;
}


/* ==== FUN_00411add @ 00411add ==== */

void __cdecl FUN_00411add(undefined4 *param_1,int param_2,int param_3,int *param_4)

{
  FUN_004119e4((int)param_1,param_2,param_3);
  FUN_004112e0(param_1,param_4,0);
  return;
}


/* ==== FUN_00411b08 @ 00411b08 ==== */

void __cdecl FUN_00411b08(int param_1,int param_2,int param_3)

{
  bool bVar1;
  uint uVar2;
  undefined3 extraout_var;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 6;
  bVar3 = 8;
  uVar2 = FUN_00410d97(*(undefined4 *)(param_3 + 0x14));
  uVar2 = FUN_0043bd1e(*(uint *)(param_1 + 4),uVar2,bVar3,bVar4);
  bVar4 = 1;
  bVar3 = 0x10;
  bVar1 = FUN_00410cfb(*(int *)(param_2 + 4));
  uVar2 = FUN_0043bd1e(uVar2,CONCAT31(extraout_var,bVar1),bVar3,bVar4);
  *(uint *)(param_1 + 4) = uVar2;
  FUN_0043bdfb(param_1,param_2,0,6);
  return;
}


/* ==== FUN_00411b70 @ 00411b70 ==== */

void __cdecl FUN_00411b70(undefined4 *param_1,int param_2,int *param_3)

{
  bool bVar1;
  undefined3 extraout_var;
  uint uVar2;
  undefined3 extraout_var_00;
  uint uVar3;
  byte bVar4;
  byte bVar5;
  uint local_8;
  
  bVar5 = 1;
  bVar4 = 0x10;
  bVar1 = FUN_00410cfb(*(int *)(param_2 + 4));
  uVar2 = FUN_0043bd1e(param_1[1],CONCAT31(extraout_var,bVar1),bVar4,bVar5);
  if (param_3[1] == 0) {
    local_8 = FUN_0043bd1e(uVar2,1,6,1);
  }
  else {
    bVar5 = 1;
    bVar4 = 6;
    bVar1 = FUN_00410cfb(param_3[1]);
    uVar2 = FUN_0043bd1e(uVar2,CONCAT31(extraout_var_00,bVar1),bVar4,bVar5);
    local_8 = FUN_0043bd1e(uVar2,1,7,1);
  }
  bVar5 = 3;
  bVar4 = 8;
  uVar2 = FUN_00410b29(*param_3,param_3[5]);
  uVar2 = FUN_0043bd1e(local_8,uVar2,bVar4,bVar5);
  bVar5 = 3;
  bVar4 = 0xb;
  uVar3 = FUN_00410c5c(*param_3);
  uVar2 = FUN_0043bd1e(uVar2,uVar3,bVar4,bVar5);
  param_1[1] = uVar2;
  FUN_0043bdfb((int)param_1,param_2,0,6);
  FUN_004112e0(param_1,param_3,0);
  return;
}


/* ==== FUN_00411c6a @ 00411c6a ==== */

void __cdecl FUN_00411c6a(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),1,0xf,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_00411b08(param_1,param_3,param_2);
  return;
}


/* ==== FUN_00411c9e @ 00411c9e ==== */

void __cdecl FUN_00411c9e(undefined4 *param_1,int *param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(param_1[1],1,0xf,1);
  param_1[1] = uVar1;
  FUN_00411b70(param_1,param_3,param_2);
  return;
}


/* ==== FUN_00411cd2 @ 00411cd2 ==== */

void __cdecl FUN_00411cd2(undefined4 *param_1,int param_2,int *param_3)

{
  bool bVar1;
  uint uVar2;
  undefined3 extraout_var;
  uint uVar3;
  byte bVar4;
  byte bVar5;
  
  bVar5 = 6;
  bVar4 = 0;
  uVar2 = FUN_00410d97(*(undefined4 *)(param_2 + 0x14));
  uVar2 = FUN_0043bd1e(param_1[1] | 0x40000,uVar2,bVar4,bVar5);
  bVar5 = 1;
  bVar4 = 6;
  bVar1 = FUN_00410cfb(param_3[1]);
  uVar2 = FUN_0043bd1e(uVar2,CONCAT31(extraout_var,bVar1),bVar4,bVar5);
  bVar5 = 3;
  bVar4 = 8;
  uVar3 = FUN_00410b29(*param_3,param_3[5]);
  uVar2 = FUN_0043bd1e(uVar2,uVar3,bVar4,bVar5);
  bVar5 = 3;
  bVar4 = 0xb;
  uVar3 = FUN_00410c5c(*param_3);
  uVar2 = FUN_0043bd1e(uVar2,uVar3,bVar4,bVar5);
  uVar2 = FUN_0043bd1e(uVar2,1,0xe,1);
  uVar2 = FUN_0043bd1e(uVar2,1,0x10,1);
  param_1[1] = uVar2;
  FUN_004112e0(param_1,param_3,0);
  return;
}


/* ==== FUN_00411db2 @ 00411db2 ==== */

void __cdecl FUN_00411db2(undefined4 *param_1,int *param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(param_1[1],1,0xf,1);
  param_1[1] = uVar1;
  FUN_00411cd2(param_1,param_3,param_2);
  return;
}


/* ==== FUN_00411de6 @ 00411de6 ==== */

void __cdecl FUN_00411de6(int param_1,int param_2,int param_3)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  
  bVar3 = 6;
  bVar2 = 0;
  uVar1 = FUN_00410d97(*(undefined4 *)(param_3 + 0x14));
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4) | 0x40000,uVar1,bVar2,bVar3);
  uVar1 = FUN_0043bd1e(uVar1,1,7,1);
  uVar1 = FUN_0043bd1e(uVar1,1,0x10,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_0043bdfb(param_1,param_2,8,8);
  return;
}


/* ==== FUN_00411e5a @ 00411e5a ==== */

void __cdecl FUN_00411e5a(int param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 6;
  bVar3 = 0;
  uVar1 = FUN_00410d97(*(undefined4 *)(param_2 + 0x14));
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4) | 0x40000,uVar1,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,1,7,1);
  bVar4 = 6;
  bVar3 = 8;
  uVar2 = FUN_00410d97(*(undefined4 *)(param_3 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,1,0xe,1);
  *(uint *)(param_1 + 4) = uVar1;
  return;
}


/* ==== FUN_00411edd @ 00411edd ==== */

void __cdecl FUN_00411edd(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),1,0xf,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_00411e5a(param_1,param_3,param_2);
  return;
}


/* ==== FUN_00411f11 @ 00411f11 ==== */

void __cdecl FUN_00411f11(int param_1,int param_2,int param_3)

{
  bool bVar1;
  uint uVar2;
  undefined3 extraout_var;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 6;
  bVar3 = 0;
  uVar2 = FUN_00410d97(*(undefined4 *)(param_2 + 0x14));
  uVar2 = FUN_0043bd1e(*(uint *)(param_1 + 4) | 0x40000,uVar2,bVar3,bVar4);
  bVar4 = 1;
  bVar3 = 6;
  bVar1 = FUN_00410cfb(*(int *)(param_3 + 4));
  uVar2 = FUN_0043bd1e(uVar2,CONCAT31(extraout_var,bVar1),bVar3,bVar4);
  uVar2 = FUN_0043bd1e(uVar2,1,0x10,1);
  *(uint *)(param_1 + 4) = uVar2;
  FUN_0043bdfb(param_1,param_3,8,6);
  return;
}


/* ==== FUN_00411f93 @ 00411f93 ==== */

void __cdecl FUN_00411f93(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),1,0xf,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_00411f11(param_1,param_3,param_2);
  return;
}


/* ==== FUN_00411fc7 @ 00411fc7 ==== */

void __cdecl FUN_00411fc7(undefined4 *param_1,int param_2,int *param_3)

{
  bool bVar1;
  uint uVar2;
  undefined3 extraout_var;
  uint uVar3;
  byte bVar4;
  byte bVar5;
  
  bVar5 = 6;
  bVar4 = 0;
  uVar2 = FUN_00410d97(*(undefined4 *)(param_2 + 0x14));
  uVar2 = FUN_0043bd1e(param_1[1] | 0x40000,uVar2,bVar4,bVar5);
  bVar5 = 1;
  bVar4 = 6;
  bVar1 = FUN_00410cfb(param_3[1]);
  uVar2 = FUN_0043bd1e(uVar2,CONCAT31(extraout_var,bVar1),bVar4,bVar5);
  bVar5 = 3;
  bVar4 = 8;
  uVar3 = FUN_00410b29(*param_3,param_3[5]);
  uVar2 = FUN_0043bd1e(uVar2,uVar3,bVar4,bVar5);
  bVar5 = 3;
  bVar4 = 0xb;
  uVar3 = FUN_00410c5c(*param_3);
  uVar2 = FUN_0043bd1e(uVar2,uVar3,bVar4,bVar5);
  uVar2 = FUN_0043bd1e(uVar2,1,0xe,1);
  uVar2 = FUN_0043bd1e(uVar2,1,0x10,1);
  param_1[1] = uVar2;
  FUN_004112e0(param_1,param_3,0);
  return;
}


/* ==== FUN_004120a7 @ 004120a7 ==== */

void __cdecl FUN_004120a7(undefined4 *param_1,int *param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(param_1[1],1,0xf,1);
  param_1[1] = uVar1;
  FUN_00411fc7(param_1,param_3,param_2);
  return;
}


/* ==== FUN_004120db @ 004120db ==== */

void __cdecl FUN_004120db(int param_1,int param_2,int *param_3,int param_4,int *param_5)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 3;
  bVar3 = 8;
  uVar1 = FUN_00410b29(*param_3,param_3[5]);
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),uVar1,bVar3,bVar4);
  bVar4 = 2;
  bVar3 = 0xb;
  uVar2 = FUN_00410c5c(*param_3);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  bVar4 = 2;
  bVar3 = 0xd;
  uVar2 = FUN_00410b29(*param_5,param_5[5]);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  bVar4 = 2;
  bVar3 = 0x10;
  uVar2 = FUN_0041223d(*(undefined4 *)(param_4 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  bVar4 = 2;
  bVar3 = 0x12;
  uVar2 = FUN_004121da(*(undefined4 *)(param_2 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  bVar4 = 2;
  bVar3 = 0x14;
  uVar2 = FUN_00410c5c(*param_5);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,1,0x17,1);
  *(uint *)(param_1 + 4) = uVar1;
  return;
}


/* ==== FUN_004121da @ 004121da ==== */

undefined4 __cdecl FUN_004121da(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 2:
    uVar1 = 2;
    break;
  case 3:
    uVar1 = 3;
    break;
  case 4:
    uVar1 = 0;
    break;
  default:
    FUN_00412fa0((uint *)s_XX_encoding_failure_00453cf4);
    uVar1 = 0;
    break;
  case 6:
    uVar1 = 1;
  }
  return uVar1;
}


/* ==== FUN_0041223d @ 0041223d ==== */

undefined4 __cdecl FUN_0041223d(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 2:
    uVar1 = 2;
    break;
  case 3:
    uVar1 = 3;
    break;
  default:
    FUN_00412fa0((uint *)s_YY_encoding_failure_00453d08);
    uVar1 = 0;
    break;
  case 5:
    uVar1 = 0;
    break;
  case 7:
    uVar1 = 1;
  }
  return uVar1;
}


/* ==== FUN_004122a4 @ 004122a4 ==== */

void __cdecl FUN_004122a4(int param_1,int *param_2,int param_3,int param_4,int *param_5)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),1,0xf,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_004120db(param_1,param_3,param_2,param_4,param_5);
  return;
}


/* ==== FUN_004122e0 @ 004122e0 ==== */

void __cdecl FUN_004122e0(int param_1,int param_2,int *param_3,int *param_4,int param_5)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),1,0x16,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_004120db(param_1,param_2,param_3,param_5,param_4);
  return;
}


/* ==== FUN_0041231c @ 0041231c ==== */

void __cdecl FUN_0041231c(int param_1,int *param_2,int param_3,int *param_4,int param_5)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),1,0xf,1);
  uVar1 = FUN_0043bd1e(uVar1,1,0x16,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_004120db(param_1,param_3,param_2,param_5,param_4);
  return;
}


/* ==== FUN_00412370 @ 00412370 ==== */

void __cdecl FUN_00412370(int param_1,int param_2,int *param_3)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  undefined3 extraout_var;
  byte bVar4;
  byte bVar5;
  
  bVar5 = 3;
  bVar4 = 8;
  uVar2 = FUN_00410b29(*param_3,param_3[5]);
  uVar2 = FUN_0043bd1e(*(uint *)(param_1 + 4),uVar2,bVar4,bVar5);
  bVar5 = 3;
  bVar4 = 0xb;
  uVar3 = FUN_00410c5c(*param_3);
  uVar2 = FUN_0043bd1e(uVar2,uVar3,bVar4,bVar5);
  bVar5 = 1;
  bVar4 = 0xf;
  bVar1 = FUN_00410cfb(param_3[1]);
  uVar2 = FUN_0043bd1e(uVar2,CONCAT31(extraout_var,bVar1),bVar4,bVar5);
  bVar5 = 1;
  bVar4 = 0x10;
  uVar3 = FUN_00410a2b(*(int *)(param_2 + 0x14));
  uVar2 = FUN_0043bd1e(uVar2,uVar3,bVar4,bVar5);
  uVar2 = FUN_0043bd1e(uVar2,1,0x13,1);
  *(uint *)(param_1 + 4) = uVar2;
  return;
}


/* ==== FUN_00412424 @ 00412424 ==== */

void __cdecl FUN_00412424(undefined4 *param_1,int param_2,int *param_3)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 3;
  bVar3 = 8;
  uVar1 = FUN_00410b29(*param_3,param_3[5]);
  uVar1 = FUN_0043bd1e(param_1[1],uVar1,bVar3,bVar4);
  bVar4 = 3;
  bVar3 = 0xb;
  uVar2 = FUN_00410c5c(*param_3);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,1,0xe,1);
  bVar4 = 3;
  bVar3 = 0x10;
  uVar2 = FUN_00410ec7(*(undefined4 *)(param_2 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,(int)uVar2 >> 3,0x14,2);
  uVar1 = FUN_0043bd1e(uVar1,1,0x16,1);
  param_1[1] = uVar1;
  FUN_004112e0(param_1,param_3,0);
  return;
}


/* ==== FUN_004124fe @ 004124fe ==== */

void __cdecl FUN_004124fe(undefined4 *param_1,int *param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(param_1[1],1,0xf,1);
  param_1[1] = uVar1;
  FUN_00412424(param_1,param_3,param_2);
  return;
}


/* ==== FUN_00412532 @ 00412532 ==== */

void __cdecl FUN_00412532(undefined4 *param_1,int param_2,int *param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(param_1[1],1,0x13,1);
  param_1[1] = uVar1;
  FUN_00412424(param_1,param_2,param_3);
  return;
}


/* ==== FUN_00412566 @ 00412566 ==== */

void __cdecl FUN_00412566(undefined4 *param_1,int *param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(param_1[1],1,0xf,1);
  param_1[1] = uVar1;
  FUN_00412532(param_1,param_3,param_2);
  return;
}


/* ==== FUN_0041259a @ 0041259a ==== */

void __cdecl FUN_0041259a(int param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 3;
  bVar3 = 0x10;
  uVar1 = FUN_00410ec7(*(undefined4 *)(param_2 + 0x14));
  uVar2 = FUN_0043bd1e(*(uint *)(param_1 + 4),uVar1,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar2,(int)uVar1 >> 3,0x14,2);
  uVar1 = FUN_0043bd1e(uVar1,1,0x16,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_0043bdfb(param_1,param_3,8,6);
  return;
}


/* ==== FUN_00412616 @ 00412616 ==== */

void __cdecl FUN_00412616(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),1,0xf,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_0041259a(param_1,param_3,param_2);
  return;
}


/* ==== FUN_0041264a @ 0041264a ==== */

void __cdecl FUN_0041264a(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),1,0x13,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_0041259a(param_1,param_2,param_3);
  return;
}


/* ==== FUN_0041267e @ 0041267e ==== */

void __cdecl FUN_0041267e(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),1,0xf,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_0041264a(param_1,param_3,param_2);
  return;
}


/* ==== FUN_004126b2 @ 004126b2 ==== */

void __cdecl FUN_004126b2(undefined4 *param_1,int param_2,int param_3,int param_4,int *param_5)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 3;
  bVar3 = 8;
  uVar1 = FUN_00410b29(*param_5,param_5[5]);
  uVar1 = FUN_0043bd1e(param_1[1],uVar1,bVar3,bVar4);
  bVar4 = 3;
  bVar3 = 0xb;
  uVar2 = FUN_00410c5c(*param_5);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,1,0xe,1);
  bVar4 = 2;
  bVar3 = 0x10;
  uVar2 = FUN_0041223d(*(undefined4 *)(param_4 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  bVar4 = 1;
  bVar3 = 0x12;
  uVar2 = FUN_004127b0(*(int *)(param_3 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  bVar4 = 1;
  bVar3 = 0x13;
  uVar2 = FUN_00410a2b(*(int *)(param_2 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,1,0x14,1);
  param_1[1] = uVar1;
  FUN_004112e0(param_1,param_5,0);
  return;
}


/* ==== FUN_004127b0 @ 004127b0 ==== */

undefined4 __cdecl FUN_004127b0(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 4) {
    uVar1 = 0;
  }
  else if (param_1 == 6) {
    uVar1 = 1;
  }
  else {
    FUN_00412fa0((uint *)s_X_encoding_failure_00453d1c);
    uVar1 = 0;
  }
  return uVar1;
}


