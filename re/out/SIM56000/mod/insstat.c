/* ==== insn_stat_classify @ 0041c750 ==== */

void __cdecl insn_stat_classify(void *stat,void *dec)

{
  uint uVar1;
  uint uVar2;
  
  *(undefined4 *)((int)stat + 0x10) = *(undefined4 *)dec;
  *(undefined4 *)((int)stat + 0x88) = *(undefined4 *)((int)dec + 0xa8);
  uVar1 = *(uint *)((int)dec + 0xb8);
  *(uint *)((int)stat + 4) = uVar1;
  *(undefined4 *)((int)stat + 8) = *(undefined4 *)((int)dec + 0xbc);
  if ((((((uVar1 & 0xfe4080) == 0x84080) || ((uVar1 & 0xfe40c0) == 0x84040)) ||
       ((uVar1 & 0xfe40c0) == 0x84000)) ||
      (((uVar1 & 0xff4080) == 0x74000 || ((uVar1 & 0xff4080) == 0x70080)))) ||
     (((uVar1 & 0xff40a0) == 0x44080 ||
      (((uVar1 & 0xff40a0) == 0x44020 || ((uVar1 & 0xff8080) == 0x8000)))))) {
    *(undefined4 *)((int)stat + 0x10) = 0x65;
  }
  if (((((uVar1 & 0xff00a0) == 0x500a0) || (uVar2 = uVar1 & 0xff40a0, uVar2 == 0x54020)) ||
      (uVar2 == 0x50020)) || (uVar2 == 0x440a0)) {
    *(undefined4 *)((int)stat + 0x10) = 99;
  }
  if (((uVar1 & 0xff4080) == 0x74080) || ((uVar1 & 0xff4080) == 0x70000)) {
    *(undefined4 *)((int)stat + 0x10) = 100;
  }
  uVar1 = *(uint *)((int)stat + 0xc);
  if (*(int *)((int)dec + 4) == 0xd) {
    uVar1 = uVar1 | 8;
  }
  else if (*(int *)((int)dec + 4) == 0xe) {
    uVar1 = uVar1 | 0x10;
  }
  if (*(int *)((int)dec + 0xb0) == -1) {
    uVar1 = uVar1 | 0x20;
  }
  uVar2 = *(uint *)((int)dec + 0xac);
  if ((uVar2 & 4) != 0) {
    uVar1 = uVar1 | 0x40;
  }
  if ((uVar2 & 8) != 0) {
    uVar1 = uVar1 | 0x80;
  }
  if ((uVar2 & 0x100) != 0) {
    uVar1 = uVar1 | 0x400;
  }
  if ((uVar2 & 0x20) != 0) {
    uVar1 = uVar1 | 0x200;
  }
  if ((uVar2 & 0x80) != 0) {
    uVar1 = uVar1 | 0x100;
  }
  if ((uVar2 & 0x40) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((*(int *)((int)stat + 0x10) == 0x27) || (*(int *)((int)stat + 0x10) == 0x29)) {
    uVar1 = uVar1 | 2;
  }
  *(uint *)((int)stat + 0xc) = uVar1;
  return;
}


/* ==== insn_stat_operands @ 0041c8b0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl insn_stat_operands(void *stat,void *dec)

{
  int *piVar1;
  bool bVar2;
  int *dst;
  int iVar3;
  uint uVar4;
  long *plVar5;
  long *plVar6;
  undefined4 *puVar7;
  int local_4;
  
  uVar4 = 0;
  piVar1 = (int *)((int)stat + 0x14);
  local_4 = 0;
  plVar6 = (long *)((int)dec + 8);
  dst = piVar1;
  do {
    copy_operand4(dst,plVar6);
    if (*plVar6 != 0) {
      local_4 = uVar4 + 1;
    }
    uVar4 = uVar4 + 1;
    dst = dst + 7;
    plVar6 = plVar6 + 5;
  } while (uVar4 < 4);
  if ((*(byte *)((int)dec + 0xac) & 0x80) == 0) {
    iVar3 = 4;
    plVar5 = (long *)((int)dec + 0x58);
    plVar6 = (long *)((int)stat + local_4 * 0x1c + 0x14);
    do {
      if (*plVar5 != 0) {
        copy_operand4(plVar6,plVar5);
        plVar6 = plVar6 + 7;
      }
      plVar5 = plVar5 + 5;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    goto LAB_0041ca59;
  }
  if ((((*(int *)((int)dec + 0x58) == 0) && (*(int *)((int)dec + 0x6c) == 0)) &&
      (*(int *)((int)dec + 0x80) == 0)) && (*(int *)((int)dec + 0x94) == 0)) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if (*(int *)((int)stat + 0x10) == 0x28) {
    if (!bVar2) goto LAB_0041ca59;
    copy_operand4((long *)((int)stat + 0x4c),(long *)((int)dec + 0x58));
    plVar5 = (long *)((int)dec + 0x6c);
    plVar6 = (long *)((int)stat + 0x68);
  }
  else {
    if (!bVar2) goto LAB_0041ca59;
    _DAT_004dbe20 = 0;
    _DAT_004dbdd8 = 0;
    _DAT_004dbe24 = 0;
    DAT_004dbddc = 0;
    DAT_004dbe28 = 0;
    puVar7 = &DAT_004dbde8;
    for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
    }
    puVar7 = &DAT_004dbe30;
    for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
    }
    *(undefined **)((int)stat + 0x84) = &DAT_004dbdd8;
    DAT_004dbde0 = &DAT_004dbde8;
    plVar6 = *(long **)(*(int *)((int)stat + 0x84) + 8);
    copy_operand4(plVar6,(long *)((int)dec + 0x58));
    copy_operand4(plVar6 + 7,(long *)((int)dec + 0x6c));
    if (*(int *)((int)dec + 0x80) == 0) goto LAB_0041ca59;
    *(undefined **)(*(int *)((int)stat + 0x84) + 4) = &DAT_004dbe20;
    *(undefined4 **)(*(int *)(*(int *)((int)stat + 0x84) + 4) + 8) = &DAT_004dbe30;
    plVar6 = *(long **)(*(int *)(*(int *)((int)stat + 0x84) + 4) + 8);
    copy_operand4(plVar6,(long *)((int)dec + 0x80));
    plVar5 = (long *)((int)dec + 0x94);
    plVar6 = plVar6 + 7;
  }
  copy_operand4(plVar6,plVar5);
LAB_0041ca59:
  switch(*(undefined4 *)((int)stat + 0x10)) {
  case 8:
    *(int *)((int)stat + 0x38) = *(int *)((int)stat + 0x38) + 1;
    return;
  case 9:
    *(int *)((int)stat + 0x1c) = *(int *)((int)stat + 0x1c) + 1;
    return;
  case 10:
    *(undefined4 *)((int)stat + 0x30) = 0xe;
    *(int *)((int)stat + 0x38) = *(int *)((int)stat + 0x38) + 1;
    return;
  case 0xb:
    *(int *)((int)stat + 0x1c) = *(int *)((int)stat + 0x1c) + 1;
    *piVar1 = 0xe;
    return;
  case 0x16:
    if (*piVar1 == 10) {
      *piVar1 = 0xe;
      return;
    }
    break;
  case 0x2b:
  case 0x2c:
    if (*piVar1 == 9) {
      *piVar1 = 0xe;
      return;
    }
    break;
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
    *(undefined4 *)((int)stat + 0x4c) = 0xe;
  }
  return;
}


/* ==== copy_operand4 @ 0041cb40 ==== */

void __cdecl copy_operand4(long *dst,long *src)

{
  *dst = *src;
  dst[1] = src[1];
  dst[2] = src[2];
  dst[3] = src[3];
  return;
}


/* ==== eval_cc @ 0041cb60 ==== */

ulong __cdecl eval_cc(ulong ccr,int cc)

{
  switch(cc) {
  case 0:
    return ~ccr & 1;
  case 1:
    if (((ccr & 8) == 0) && ((ccr & 2) == 0)) {
      return 1;
    }
    if (((ccr & 8) != 0) && ((ccr & 2) != 0)) {
      return 1;
    }
    break;
  case 2:
    return ~ccr >> 2 & 1;
  case 3:
    return ~ccr >> 3 & 1;
  case 4:
    if (((ccr & 4) == 0) && ((ccr & 0x30) != 0)) {
      return 1;
    }
    break;
  case 5:
    return ~ccr >> 5 & 1;
  case 6:
    return ~ccr >> 6 & 1;
  case 7:
    if ((ccr & 4) != 0) {
      return 0;
    }
    if (((ccr & 2) == 0) && ((ccr & 8) == 0)) {
      return 1;
    }
    if (((ccr & 2) != 0) && ((ccr & 8) != 0)) {
      return 1;
    }
    break;
  case 8:
    return ccr & 1;
  case 9:
    if (((ccr & 2) == 0) && ((ccr & 8) != 0)) {
      return 1;
    }
    if (((ccr & 2) != 0) && ((ccr & 8) == 0)) {
      return 1;
    }
    break;
  case 10:
    return ccr >> 2 & 1;
  case 0xb:
    return ccr >> 3 & 1;
  case 0xc:
    if ((ccr & 4) != 0) {
      return 1;
    }
    if ((ccr & 0x30) == 0) {
      return 1;
    }
    return 0;
  case 0xd:
    return ccr >> 5 & 1;
  case 0xe:
    return ccr >> 6 & 1;
  case 0xf:
    if ((ccr & 4) != 0) {
      return 1;
    }
    if (((ccr & 2) == 0) && ((ccr & 8) != 0)) {
      return 1;
    }
    if (((ccr & 2) != 0) && ((ccr & 8) == 0)) {
      return 1;
    }
    break;
  default:
    return 1;
  }
  return 0;
}


/* ==== mnemonic_name @ 0041cd00 ==== */

char * __cdecl mnemonic_name(int id)

{
  if (*mnemonic_names == 'n') {
    mnemonic_names = &DAT_004bfc6c;
  }
  if (id < 0x5f) {
    return (&mnemonic_names)[id];
  }
  if (id < 0x66) {
    return (&PTR_DAT_004bf864)[id];
  }
  return (char *)0x0;
}


/* ==== stat_lmove_class @ 0041cd40 ==== */

int __cdecl
stat_lmove_class(void *stat,long a2,long a3,long *class_out,long *flag1,long a6,long *flag2)

{
  long *b;
  long *a;
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)((int)stat + 0x84);
  if ((iVar1 == 0) || (*(int *)(iVar1 + 4) == 0)) {
    return 1;
  }
  b = *(long **)(*(int *)(iVar1 + 4) + 8);
  a = *(long **)(iVar1 + 8);
  iVar1 = operand_is_xy_pair(a,b);
  if (iVar1 == 0) {
    *flag1 = 0;
    iVar1 = a[8];
    uVar2 = b[8];
  }
  else {
    iVar1 = operand_is_xy_pair(a + 7,b + 7);
    if (iVar1 != 0) {
      return 1;
    }
    *flag2 = 1;
    iVar1 = a[1];
    uVar2 = b[1];
  }
  uVar2 = iVar1 << 0x10 | uVar2;
  if (uVar2 < 0x350035) {
    if (uVar2 == 0x350034) {
      *class_out = 0x54;
      return 0;
    }
    if (uVar2 == 0x320031) {
      *class_out = 0x53;
      return 0;
    }
  }
  else if (uVar2 == 0x59005b) {
    *class_out = 0x4e;
  }
  else if (uVar2 == 0x5a005c) {
    *class_out = 0x4f;
    return 0;
  }
  return 0;
}


/* ==== operand_is_xy_pair @ 0041ce10 ==== */

int operand_is_xy_pair(long *a,long *b)

{
  if ((((*a == *b) && (a[1] == b[1])) && (a[2] == b[2])) && ((a[3] == 1 && (b[3] == 2)))) {
    return 0;
  }
  return 1;
}


/* ==== dec_c0_enddo @ 0041ce50 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void dec_c0_enddo(ulong opw,void *dec)

{
  void *dec_00;
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ulong uStack_14;
  undefined4 *puStack_10;
  long *plStack_c;
  undefined4 *puStack_8;
  uint uStack_4;
  
  dec_00 = dec;
  uVar3 = opw >> 8;
  uVar4 = uVar3 & 0xffff;
  uVar2 = uVar4 >> 4 & 0x300;
  uVar1 = (uVar3 & 0x60 | uVar2) >> 5;
  uStack_14 = uVar3 & 0x1f;
  uStack_4 = uVar3 & 0x4000;
  puStack_10 = (undefined4 *)((int)dec + 0x6c);
  plStack_c = (long *)((int)dec + 0x80);
  puStack_8 = (undefined4 *)((int)dec + 0x94);
  dec = (void *)((int)dec + 0x58);
  dec_alu(opw,dec_00);
  if ((uVar3 & 0x18) == 0) {
    uStack_14 = uStack_14 | 0x20;
  }
  opw = uVar1;
  if (uVar2 == 0) {
    opw = uVar1 | 0x20;
  }
  if ((uVar3 & 0x80) == 0) {
    swap_ptrs(&dec,&puStack_10);
  }
  *(undefined4 *)((int)dec + 0xc) = 1;
  dec_ea6(dec,uStack_14);
  *puStack_10 = 0xc;
  puStack_10[1] = *(undefined4 *)(&DAT_004c0270 + (uVar4 >> 10 & 3) * 4);
  if ((uVar3 & 4) == 0) {
    opw = opw | 4;
  }
  if (uStack_4 == 0) {
    swap_ptrs(&plStack_c,&puStack_8);
  }
  plStack_c[3] = 2;
  dec_ea6(plStack_c,opw);
  *puStack_8 = 0xc;
  puStack_8[1] = *(undefined4 *)(&DAT_004c0280 + (uVar4 >> 8 & 3) * 4);
  return;
}


