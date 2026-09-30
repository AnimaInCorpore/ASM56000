/* error: 24 functions from ASM56000 */

/* ==== FUN_004127e6 @ 004127e6 ==== */

void __cdecl FUN_004127e6(undefined4 *param_1,int param_2,int param_3,int *param_4,int param_5)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(param_1[1],1,0xf,1);
  param_1[1] = uVar1;
  FUN_004126b2(param_1,param_2,param_3,param_5,param_4);
  return;
}


/* ==== FUN_00412822 @ 00412822 ==== */

void __cdecl FUN_00412822(undefined4 *param_1,int param_2,int *param_3,int param_4,int param_5)

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
  bVar4 = 1;
  bVar3 = 0x10;
  uVar2 = FUN_0041290b(*(int *)(param_5 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  bVar4 = 1;
  bVar3 = 0x11;
  uVar2 = FUN_00410a2b(*(int *)(param_4 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  bVar4 = 2;
  bVar3 = 0x12;
  uVar2 = FUN_004121da(*(undefined4 *)(param_2 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,1,0x14,1);
  param_1[1] = uVar1;
  FUN_004112e0(param_1,param_3,0);
  return;
}


/* ==== FUN_0041290b @ 0041290b ==== */

undefined4 __cdecl FUN_0041290b(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 5) {
    uVar1 = 0;
  }
  else if (param_1 == 7) {
    uVar1 = 1;
  }
  else {
    FUN_00412fa0((uint *)s_Y_encoding_failure_00453d30);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_00412941 @ 00412941 ==== */

void __cdecl FUN_00412941(undefined4 *param_1,int *param_2,int param_3,int param_4,int param_5)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(param_1[1],1,0xf,1);
  param_1[1] = uVar1;
  FUN_00412822(param_1,param_3,param_2,param_4,param_5);
  return;
}


/* ==== FUN_0041297d @ 0041297d ==== */

void __cdecl FUN_0041297d(int param_1,int param_2,int param_3)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  
  bVar3 = 4;
  bVar2 = 0x10;
  uVar1 = FUN_004129d7(*(undefined4 *)(param_2 + 0x14));
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),uVar1,bVar2,bVar3);
  uVar1 = FUN_0043bd1e(uVar1,1,0x16,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_0043bdfb(param_1,param_3,8,6);
  return;
}


/* ==== FUN_004129d7 @ 004129d7 ==== */

undefined4 __cdecl FUN_004129d7(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 0:
    uVar1 = 2;
    break;
  case 1:
    uVar1 = 3;
    break;
  case 2:
    uVar1 = 8;
    break;
  case 3:
    uVar1 = 9;
    break;
  default:
    FUN_00412fa0((uint *)s_LLL_encoding_failure_00453d44);
    uVar1 = 0;
    break;
  case 0x26:
    uVar1 = 10;
    break;
  case 0x27:
    uVar1 = 0xb;
    break;
  case 0x28:
    uVar1 = 0;
    break;
  case 0x29:
    uVar1 = 1;
  }
  return uVar1;
}


/* ==== FUN_00412a8f @ 00412a8f ==== */

void __cdecl FUN_00412a8f(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),1,0xf,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_0041297d(param_1,param_3,param_2);
  return;
}


/* ==== FUN_00412ac3 @ 00412ac3 ==== */

void __cdecl FUN_00412ac3(undefined4 *param_1,int param_2,int *param_3)

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
  bVar4 = 4;
  bVar3 = 0x10;
  uVar2 = FUN_004129d7(*(undefined4 *)(param_2 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,1,0x16,1);
  param_1[1] = uVar1;
  FUN_004112e0(param_1,param_3,0);
  return;
}


/* ==== FUN_00412b7b @ 00412b7b ==== */

void __cdecl FUN_00412b7b(undefined4 *param_1,int *param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(param_1[1],1,0xf,1);
  param_1[1] = uVar1;
  FUN_00412ac3(param_1,param_3,param_2);
  return;
}


/* ==== FUN_00412baf @ 00412baf ==== */

void __cdecl FUN_00412baf(int param_1,int param_2,int param_3)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  
  bVar3 = 5;
  bVar2 = 0x10;
  uVar1 = FUN_00410ec7(*(undefined4 *)(param_3 + 0x14));
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),uVar1,bVar2,bVar3);
  uVar1 = FUN_0043bd1e(uVar1,1,0x15,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_0043bdfb(param_1,param_2,8,8);
  return;
}


/* ==== FUN_00412c09 @ 00412c09 ==== */

void __cdecl FUN_00412c09(int param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 5;
  bVar3 = 8;
  uVar1 = FUN_00410ec7(*(undefined4 *)(param_3 + 0x14));
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),uVar1,bVar3,bVar4);
  bVar4 = 5;
  bVar3 = 0xd;
  uVar2 = FUN_00410ec7(*(undefined4 *)(param_2 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,1,0x15,1);
  *(uint *)(param_1 + 4) = uVar1;
  return;
}


/* ==== FUN_00412c72 @ 00412c72 ==== */

void __cdecl FUN_00412c72(int param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 3;
  bVar3 = 8;
  uVar1 = FUN_00410b29(*param_2,param_2[5]);
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),uVar1,bVar3,bVar4);
  bVar4 = 2;
  bVar3 = 0xb;
  uVar2 = FUN_00410c5c(*param_2);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,0x81,0xe,8);
  *(uint *)(param_1 + 4) = uVar1;
  return;
}


/* ==== FUN_00412ce3 @ 00412ce3 ==== */

void __cdecl FUN_00412ce3(undefined4 *param_1,int param_2,int *param_3)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 6;
  bVar3 = 0;
  uVar1 = FUN_00410d97(*(undefined4 *)(param_2 + 0x14));
  uVar1 = FUN_0043bd1e(param_1[1] | 0x70000,uVar1,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,1,7,1);
  bVar4 = 3;
  bVar3 = 8;
  uVar2 = FUN_00410b29(*param_3,param_3[5]);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  bVar4 = 3;
  bVar3 = 0xb;
  uVar2 = FUN_00410c5c(*param_3);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  uVar1 = FUN_0043bd1e(uVar1,1,0xe,1);
  param_1[1] = uVar1;
  FUN_004112e0(param_1,param_3,0);
  return;
}


/* ==== FUN_00412da0 @ 00412da0 ==== */

void __cdecl FUN_00412da0(undefined4 *param_1,int *param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(param_1[1],1,0xf,1);
  param_1[1] = uVar1;
  FUN_00412ce3(param_1,param_3,param_2);
  return;
}


/* ==== FUN_00412dd4 @ 00412dd4 ==== */

void __cdecl FUN_00412dd4(int param_1,int param_2,int param_3)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  
  bVar3 = 6;
  bVar2 = 0;
  uVar1 = FUN_00410d97(*(undefined4 *)(param_2 + 0x14));
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4) | 0x70000,uVar1,bVar2,bVar3);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_0043bdfb(param_1,param_3,8,6);
  return;
}


/* ==== FUN_00412e1b @ 00412e1b ==== */

void __cdecl FUN_00412e1b(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),1,0xf,1);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_00412dd4(param_1,param_3,param_2);
  return;
}


/* ==== FUN_00412e4f @ 00412e4f ==== */

void __cdecl FUN_00412e4f(int param_1,int *param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 4;
  bVar3 = 0;
  uVar1 = FUN_00410ec7(*(undefined4 *)(param_3 + 0x14));
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),uVar1,bVar3,bVar4);
  bVar4 = 3;
  bVar3 = 8;
  uVar2 = FUN_00410b29(*param_2,param_2[5]);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  bVar4 = 2;
  bVar3 = 0xb;
  uVar2 = FUN_00410c5c(*param_2);
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  *(uint *)(param_1 + 4) = uVar1;
  return;
}


/* ==== FUN_00412ecb @ 00412ecb ==== */

void __cdecl FUN_00412ecb(int param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 1;
  bVar3 = 3;
  uVar1 = FUN_00410a2b(*(int *)(param_4 + 0x14));
  uVar1 = FUN_0043bd1e(*(uint *)(param_1 + 4),uVar1,bVar3,bVar4);
  bVar4 = 2;
  bVar3 = 4;
  uVar2 = FUN_00412f33(*(undefined4 *)(param_2 + 0x14));
  uVar1 = FUN_0043bd1e(uVar1,uVar2,bVar3,bVar4);
  *(uint *)(param_1 + 4) = uVar1;
  FUN_0043bdfb(param_1,param_3,8,5);
  return;
}


/* ==== FUN_00412f33 @ 00412f33 ==== */

undefined4 __cdecl FUN_00412f33(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 4:
    uVar1 = 1;
    break;
  case 5:
    uVar1 = 2;
    break;
  case 6:
    uVar1 = 3;
    break;
  case 7:
    uVar1 = 0;
    break;
  default:
    FUN_00412fa0((uint *)s_QQ_encoding_failure_00453d5c);
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_00412fa0 @ 00412fa0 ==== */

void __cdecl FUN_00412fa0(uint *param_1)

{
  uint uVar1;
  
  sprintf(&DAT_0045f220,s_______ld___s__ld___FATAL_____00453da8,DAT_0045eb80,PTR_DAT_0044f80c,
          DAT_0045eb78);
  uVar1 = strlen(&DAT_0045f220);
  strcpy(&DAT_0045f220 + uVar1,(char *)param_1);
  if ((DAT_0045fcac != &DAT_0045a470) || (DAT_0045ea9c != '\0')) {
    fprintf(&DAT_0045a470,&DAT_00453dc8,&DAT_0045f220);
  }
  if (DAT_0045eb04 != '\0') {
    FUN_00413999(uVar1,(uint *)&DAT_0045f220);
  }
  if (DAT_00463be4 == 0) {
    DAT_00463be4 = 1;
    FUN_0041c9cf(&DAT_0045f220);
    FUN_0041cb65();
  }
  if (DAT_0045f854 != (char *)0x0) {
    remove(DAT_0045f854);
  }
  exit(-1);
  return;
}


/* ==== FUN_00413085 @ 00413085 ==== */

void __cdecl FUN_00413085(uint *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  if (DAT_0045ea50 == '\0') {
    if (DAT_0045f8fc == 2) {
      sprintf(&DAT_0045f220,s_______ld___s__ld___ERROR_____00453dcc,DAT_0045eb80,PTR_DAT_0044f80c,
              DAT_0045eb78);
      uVar1 = strlen(&DAT_0045f220);
      strcpy(&DAT_0045f220 + uVar1,(char *)param_1);
      if (DAT_0045f860 != (undefined1 *)0x0) {
        iVar2 = FUN_00413818(DAT_0045f860);
        if (iVar2 != 0) {
          uVar3 = strlen(&DAT_0045f220);
          if (DAT_0045ea70 == '\0') {
            sprintf(&DAT_0045f220 + uVar3,s___s_field__00453e0c,(&PTR_DAT_0044f960)[iVar2]);
          }
          else {
            sprintf(&DAT_0045f220 + uVar3,s__See_instruction_at_P__0_lX__00453dec,4,
                    *(undefined4 *)(DAT_0045fc30 + 8));
          }
        }
      }
      if ((DAT_0045fcac != &DAT_0045a470) || (DAT_0045ea9c != '\0')) {
        fprintf(&DAT_0045a470,&DAT_00453e18,&DAT_0045f220);
      }
      if (DAT_0045eb04 != '\0') {
        FUN_00413999(uVar1,(uint *)&DAT_0045f220);
      }
      FUN_0041c9cf(&DAT_0045f220);
      FUN_0041cb65();
      DAT_0045eb84 = DAT_0045eb84 + 1;
      DAT_0045eb98 = DAT_0045eb98 + 1;
    }
  }
  else {
    DAT_0045eb9c = DAT_0045eb9c + 1;
  }
  return;
}


/* ==== FUN_004131f9 @ 004131f9 ==== */

void __cdecl FUN_004131f9(uint *param_1,char *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  if (DAT_0045ea50 == '\0') {
    if (DAT_0045f8fc == 2) {
      sprintf(&DAT_0045f220,s_______ld___s__ld___ERROR_____00453e1c,DAT_0045eb80,PTR_DAT_0044f80c,
              DAT_0045eb78);
      uVar1 = strlen(&DAT_0045f220);
      strcpy(&DAT_0045f220 + uVar1,(char *)param_1);
      strcat(&DAT_0045f220,&DAT_00453e3c);
      uVar2 = strlen(&DAT_0045f220);
      strncat(&DAT_0045f220 + uVar2,param_2,0x100);
      if (DAT_0045f860 != (undefined1 *)0x0) {
        iVar3 = FUN_00413818(DAT_0045f860);
        if (iVar3 != 0) {
          uVar2 = strlen(&DAT_0045f220);
          if (DAT_0045ea70 == '\0') {
            sprintf(&DAT_0045f220 + uVar2,s___s_field__00453e60,(&PTR_DAT_0044f960)[iVar3]);
          }
          else {
            sprintf(&DAT_0045f220 + uVar2,s__See_instruction_at_P__0_lX__00453e40,4,
                    *(undefined4 *)(DAT_0045fc30 + 8));
          }
        }
      }
      if ((DAT_0045fcac != &DAT_0045a470) || (DAT_0045ea9c != '\0')) {
        fprintf(&DAT_0045a470,&DAT_00453e6c,&DAT_0045f220);
      }
      if (DAT_0045eb04 != '\0') {
        FUN_00413999(uVar1,(uint *)&DAT_0045f220);
      }
      FUN_0041c9cf(&DAT_0045f220);
      FUN_0041cb65();
      DAT_0045eb84 = DAT_0045eb84 + 1;
      DAT_0045eb98 = DAT_0045eb98 + 1;
    }
  }
  else {
    DAT_0045eb9c = DAT_0045eb9c + 1;
  }
  return;
}


/* ==== FUN_004133a9 @ 004133a9 ==== */

void __cdecl FUN_004133a9(uint *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  if (((DAT_0045ea50 == '\0') && (DAT_0045f8fc == 2)) && (DAT_0044f788 != '\0')) {
    sprintf(&DAT_0045f220,s_______ld___s__ld___WARNING_____00453e70,DAT_0045eb80,PTR_DAT_0044f80c,
            DAT_0045eb78);
    uVar1 = strlen(&DAT_0045f220);
    strcpy(&DAT_0045f220 + uVar1,(char *)param_1);
    if ((DAT_0045f860 != (undefined1 *)0x0) && (iVar2 = FUN_00413818(DAT_0045f860), iVar2 != 0)) {
      uVar3 = strlen(&DAT_0045f220);
      if (DAT_0045ea70 == '\0') {
        sprintf(&DAT_0045f220 + uVar3,s___s_field__00453eb0,(&PTR_DAT_0044f960)[iVar2]);
      }
      else {
        sprintf(&DAT_0045f220 + uVar3,s__See_instruction_at_P__0_lX__00453e90,4,
                *(undefined4 *)(DAT_0045fc30 + 8));
      }
    }
    if ((DAT_0045fcac != &DAT_0045a470) || (DAT_0045ea9c != '\0')) {
      fprintf(&DAT_0045a470,&DAT_00453ebc,&DAT_0045f220);
    }
    if (DAT_0045eb04 != '\0') {
      FUN_00413999(uVar1,(uint *)&DAT_0045f220);
    }
    FUN_0041c9cf(&DAT_0045f220);
    FUN_0041cb65();
    DAT_0045eb88 = DAT_0045eb88 + 1;
    DAT_0045eb98 = DAT_0045eb98 + 1;
  }
  return;
}


/* ==== FUN_0041351d @ 0041351d ==== */

void __cdecl FUN_0041351d(uint *param_1,char *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  if (((DAT_0045ea50 == '\0') && (DAT_0045f8fc == 2)) && (DAT_0044f788 != '\0')) {
    sprintf(&DAT_0045f220,s_______ld___s__ld___WARNING_____00453ec0,DAT_0045eb80,PTR_DAT_0044f80c,
            DAT_0045eb78);
    uVar1 = strlen(&DAT_0045f220);
    strcpy(&DAT_0045f220 + uVar1,(char *)param_1);
    strcat(&DAT_0045f220,&DAT_00453ee0);
    uVar2 = strlen(&DAT_0045f220);
    strncat(&DAT_0045f220 + uVar2,param_2,0x100);
    if ((DAT_0045f860 != (undefined1 *)0x0) && (iVar3 = FUN_00413818(DAT_0045f860), iVar3 != 0)) {
      uVar2 = strlen(&DAT_0045f220);
      if (DAT_0045ea70 == '\0') {
        sprintf(&DAT_0045f220 + uVar2,s___s_field__00453f04,(&PTR_DAT_0044f960)[iVar3]);
      }
      else {
        sprintf(&DAT_0045f220 + uVar2,s__See_instruction_at_P__0_lX__00453ee4,4,
                *(undefined4 *)(DAT_0045fc30 + 8));
      }
    }
    if ((DAT_0045fcac != &DAT_0045a470) || (DAT_0045ea9c != '\0')) {
      fprintf(&DAT_0045a470,&DAT_00453f10,&DAT_0045f220);
    }
    if (DAT_0045eb04 != '\0') {
      FUN_00413999(uVar1,(uint *)&DAT_0045f220);
    }
    FUN_0041c9cf(&DAT_0045f220);
    FUN_0041cb65();
    DAT_0045eb88 = DAT_0045eb88 + 1;
    DAT_0045eb98 = DAT_0045eb98 + 1;
  }
  return;
}


