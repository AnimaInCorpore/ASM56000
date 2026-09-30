/* ==== insn_exec_info @ 0042eec0 ==== */

void __cdecl insn_exec_info(ulong devflags,ulong opw,long mode,long sel,void **rec)

{
  int iVar1;
  
  switch(sel) {
  case 1:
  case 2:
    mode = 0;
  case 0:
    iVar1 = opclass_lookup(opw,devflags);
    iVar1 = (*(code *)(&insn_exec_handlers)[iVar1])(opw,devflags,mode,sel);
    break;
  case 3:
    iVar1 = 4;
    break;
  default:
    iVar1 = 0;
  }
  *rec = &insn_exec_records + iVar1 * 0x20;
  return;
}


/* ==== insn_move_h42ef30 @ 0042ef30 ==== */

undefined4 insn_move_h42ef30(void)

{
  return 0x2c;
}


/* ==== insn_move_h42ef40 @ 0042ef40 ==== */

undefined4 insn_move_h42ef40(void)

{
  return 0xf;
}


/* ==== insn_move_h42ef50 @ 0042ef50 ==== */

int insn_move_h42ef50(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  if (param_3 != 5) {
    if (param_3 == 6) {
      return (-(uint)(param_4 != 0) & 0xfffffff3) + 0xd;
    }
    if (param_3 != 7) {
      return 0xf;
    }
  }
  return 2;
}


/* ==== insn_move_h42ef80 @ 0042ef80 ==== */

int insn_move_h42ef80(void)

{
  int in_stack_00000010;
  
  return (-(uint)(in_stack_00000010 != 0) & 0xffffffec) + 0x14;
}


/* ==== insn_move_h42ef90 @ 0042ef90 ==== */

int insn_move_h42ef90(void)

{
  int in_stack_00000010;
  
  return (-(uint)(in_stack_00000010 != 0) & 0xffffffed) + 0x13;
}


/* ==== insn_move_h42efa0 @ 0042efa0 ==== */

undefined4 insn_move_h42efa0(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  if (param_4 != 0) {
    return 0;
  }
  if (param_3 != 5) {
    if (param_3 == 6) {
      return 0x1d;
    }
    if (param_3 != 7) {
      return 0x12;
    }
  }
  return 6;
}


/* ==== insn_move_h42efd0 @ 0042efd0 ==== */

undefined4 insn_move_h42efd0(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  if (param_4 != 0) {
    return 0;
  }
  if (param_3 != 5) {
    if (param_3 == 6) {
      return 0x1d;
    }
    if (param_3 != 7) {
      return 0x13;
    }
  }
  return 6;
}


/* ==== insn_move_h42f000 @ 0042f000 ==== */

int insn_move_h42f000(void)

{
  int in_stack_00000010;
  
  return (-(uint)(in_stack_00000010 != 0) & 0xffffffe4) + 0x1c;
}


/* ==== insn_move_h42f010 @ 0042f010 ==== */

undefined4 insn_move_h42f010(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  if (param_4 != 0) {
    return 0;
  }
  if (param_3 != 4) {
    if ((param_3 != 5) && (param_3 != 7)) {
      return 0x1c;
    }
    return 6;
  }
  return 0x2a;
}


/* ==== insn_move_h42f040 @ 0042f040 ==== */

int insn_move_h42f040(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  if (param_3 != 5) {
    if (param_3 == 6) {
      return (-(uint)(param_4 != 0) & 0xfffffff2) + 0xe;
    }
    if (param_3 != 7) {
      return 0x11;
    }
  }
  return 6;
}


/* ==== insn_move_h42f070 @ 0042f070 ==== */

char insn_move_h42f070(uint param_1,uint param_2,int param_3,int param_4)

{
  char cVar1;
  
  if (param_3 != 5) {
    if (param_3 == 6) {
      if (((param_1 & 0x400) == 0) || (param_2 < 4)) {
        cVar1 = '\0';
      }
      else {
        cVar1 = '\x01';
      }
      if (param_4 != 0) {
        return '\0';
      }
      return (-cVar1 & 0x20U) + 0xd;
    }
    if (param_3 != 7) {
      return '\x01';
    }
  }
  return '\x02';
}


/* ==== insn_move_h42f0c0 @ 0042f0c0 ==== */

int insn_move_h42f0c0(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  if (param_3 != 5) {
    if (param_3 == 6) {
      return (-(uint)(param_4 != 0) & 0xfffffff3) + 0xd;
    }
    if (param_3 != 7) {
      return 7;
    }
  }
  return 2;
}


/* ==== insn_move_h42f0f0 @ 0042f0f0 ==== */

undefined4 insn_move_h42f0f0(uint param_1,uint param_2)

{
  if ((3 < param_2) && ((param_1 & 0x3000) == 0)) {
    return 0xc;
  }
  return 1;
}


/* ==== insn_move_h42f120 @ 0042f120 ==== */

undefined4 insn_move_h42f120(void)

{
  return 8;
}


/* ==== insn_move_h42f130 @ 0042f130 ==== */

int insn_move_h42f130(void)

{
  int in_stack_00000010;
  
  return (-(uint)(in_stack_00000010 != 0) & 0xffffffe7) + 0x19;
}


/* ==== insn_move_h42f140 @ 0042f140 ==== */

undefined4 insn_move_h42f140(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  
  if (param_4 != 0) {
    return 0;
  }
  if ((param_3 == 5) || (uVar1 = 0x19, param_3 == 7)) {
    uVar1 = 0x18;
  }
  return uVar1;
}


/* ==== insn_move_h42f170 @ 0042f170 ==== */

int insn_move_h42f170(void)

{
  int in_stack_00000010;
  
  return (-(uint)(in_stack_00000010 != 0) & 0xfffffff7) + 9;
}


/* ==== insn_move_h42f180 @ 0042f180 ==== */

undefined4 insn_move_h42f180(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  
  if (param_4 != 0) {
    return 0;
  }
  if ((param_3 == 5) || (uVar1 = 9, param_3 == 7)) {
    uVar1 = 6;
  }
  return uVar1;
}


/* ==== insn_move_h42f1b0 @ 0042f1b0 ==== */

undefined4 insn_move_h42f1b0(void)

{
  return 0xc;
}


/* ==== insn_move_h42f1c0 @ 0042f1c0 ==== */

int insn_move_h42f1c0(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  if (param_3 != 5) {
    if (param_3 == 6) {
      return (-(uint)(param_4 != 0) & 0xfffffff2) + 0xe;
    }
    if (param_3 != 7) {
      return 0xc;
    }
  }
  return 6;
}


/* ==== insn_move_h42f1f0 @ 0042f1f0 ==== */

undefined4 insn_move_h42f1f0(void)

{
  return 4;
}


/* ==== insn_move_h42f200 @ 0042f200 ==== */

undefined4 insn_move_h42f200(void)

{
  return 10;
}


/* ==== insn_move_h42f210 @ 0042f210 ==== */

undefined4 insn_move_h42f210(void)

{
  return 0x10;
}


/* ==== insn_exec_h42f220 @ 0042f220 ==== */

undefined4 insn_exec_h42f220(void)

{
  return 0x2b;
}


/* ==== insn_move_h42f230 @ 0042f230 ==== */

int insn_move_h42f230(void)

{
  int in_stack_00000010;
  
  return (-(uint)(in_stack_00000010 != 0) & 0xffffffe6) + 0x1a;
}


/* ==== insn_move_h42f240 @ 0042f240 ==== */

int insn_move_h42f240(void)

{
  int in_stack_00000010;
  
  return (-(uint)(in_stack_00000010 != 0) & 0xffffffe9) + 0x17;
}


/* ==== insn_move_h42f250 @ 0042f250 ==== */

undefined4 insn_move_h42f250(void)

{
  return 0x1b;
}


/* ==== insn_move_h42f260 @ 0042f260 ==== */

int insn_move_h42f260(void)

{
  int in_stack_00000010;
  
  return (-(uint)(in_stack_00000010 != 0) & 0xfffffff5) + 0xb;
}


/* ==== insn_move_h42f270 @ 0042f270 ==== */

undefined4 insn_move_h42f270(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  
  if ((param_3 == 5) || (uVar1 = 0xf, param_3 == 7)) {
    uVar1 = 2;
  }
  return uVar1;
}


/* ==== insn_move_h42f290 @ 0042f290 ==== */

undefined4 insn_move_h42f290(void)

{
  return 0x16;
}


/* ==== insn_move_info @ 0042f2a0 ==== */

void __cdecl insn_move_info(ulong opw,long mode,long sel,void **rec,ulong devflags)

{
  int iVar1;
  
  iVar1 = 0;
  switch(sel) {
  case 0:
    iVar1 = opclass_lookup(opw,devflags);
    iVar1 = (*(code *)(&insn_move_handlers)[iVar1])(opw,devflags,opw >> 0xb & 7,mode);
    *rec = &insn_move_records + iVar1 * 0xc;
    return;
  case 1:
    *rec = &insn_move_records + ((-(uint)((opw & 0xf0000) != 0) & 0x12) + 3) * 0xc;
    return;
  case 2:
    *rec = &DAT_004c38e4;
    return;
  case 3:
    *rec = &DAT_004c395c;
    return;
  case 4:
    *rec = &DAT_004c3a28;
    return;
  case 5:
    *rec = &DAT_004c3a40;
    return;
  case 6:
    *rec = &DAT_004c3a88;
    return;
  case 7:
    *rec = &DAT_004c3a94;
    return;
  case 8:
    *rec = &DAT_004c3a1c;
    return;
  case 10:
    *rec = &DAT_004c3a7c;
    return;
  case 0xb:
    *rec = &DAT_004c3a70;
    return;
  case 0xc:
    *rec = &DAT_004c3a64;
    return;
  case 0xd:
    *rec = &DAT_004c3a58;
    return;
  case 0xe:
    *rec = &DAT_004c3a4c;
    return;
  case 0xf:
    iVar1 = 0x21;
  }
  *rec = &insn_move_records + iVar1 * 0xc;
  return;
}


/* ==== insn_class_h42f4a0 @ 0042f4a0 ==== */

undefined4 insn_class_h42f4a0(void)

{
  return 0;
}


/* ==== insn_class_h42f4b0 @ 0042f4b0 ==== */

int insn_class_h42f4b0(uint param_1)

{
  return (-(uint)((param_1 & 0x400) != 0) & 0xe00) + 0x140e;
}


/* ==== insn_class_h42f4d0 @ 0042f4d0 ==== */

int insn_class_h42f4d0(uint param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = param_1 >> 0xb & 7;
  uVar1 = param_1 & 0x400;
  if (uVar2 != 5) {
    if (uVar2 == 6) {
      return (-(uint)(param_3 != 0) & 0xffffffe7) + 0x19;
    }
    if (uVar2 != 7) {
      if ((param_1 & 0x80000) != 0) {
        return (-(uint)(uVar1 != 0) & 0xe00) + 0x20e;
      }
      return (-(uint)(uVar1 != 0) & 0x1c00) + 0x40e;
    }
  }
  return (-(uint)(uVar1 != 0) & 0x40) + 0x49;
}


/* ==== insn_class_h42f530 @ 0042f530 ==== */

int insn_class_h42f530(uint param_1)

{
  if ((param_1 & 0x80000) != 0) {
    return (-(uint)((param_1 & 0x400) != 0) & 0xfffff200) + 0x1006;
  }
  return (-(uint)((param_1 & 0x400) != 0) & 0xffffe400) + 0x2006;
}


/* ==== insn_class_h42f570 @ 0042f570 ==== */

int insn_class_h42f570(uint param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = param_1 >> 0xb & 7;
  if (uVar1 != 5) {
    if (uVar1 == 6) {
      return (-(uint)(param_3 != 0) & 0xffffffe7) + 0x19;
    }
    if (uVar1 != 7) {
      return (-(uint)((param_1 & 0x400) != 0) & 0x2a00) + 0x60e;
    }
  }
  return (-(uint)((param_1 & 0x400) != 0) & 0x40) + 0x49;
}


/* ==== insn_class_h42f5c0 @ 0042f5c0 ==== */

int insn_class_h42f5c0(uint param_1)

{
  return (-(uint)((param_1 & 0x400) != 0) & 0xffffd600) + 0x3006;
}


/* ==== insn_class_h42f5e0 @ 0042f5e0 ==== */

undefined4 insn_class_h42f5e0(void)

{
  return 0xe;
}


/* ==== insn_class_h42f5f0 @ 0042f5f0 ==== */

int insn_class_h42f5f0(uint param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = param_1 >> 0xb & 7;
  if (uVar1 != 5) {
    if (uVar1 == 6) {
      return (-(uint)(param_3 != 0) & 0xffffffe7) + 0x19;
    }
    if (uVar1 != 7) {
      return (-(uint)((param_1 & 0x400) != 0) & 0xe00) + 0x20e;
    }
  }
  return (-(uint)((param_1 & 0x400) != 0) & 0x40) + 0x49;
}


/* ==== insn_class_h42f640 @ 0042f640 ==== */

int insn_class_h42f640(uint param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = param_1 >> 0xb & 7;
  if (uVar1 != 5) {
    if (uVar1 == 6) {
      return (-(uint)(param_3 != 0) & 0xffffffe7) + 0x19;
    }
    if (uVar1 != 7) {
      return (-(uint)((param_1 & 0x400) != 0) & 0x1c00) + 0x40e;
    }
  }
  return (-(uint)((param_1 & 0x400) != 0) & 0x40) + 0x49;
}


/* ==== insn_class_h42f690 @ 0042f690 ==== */

int insn_class_h42f690(uint param_1,undefined4 param_2,int param_3)

{
  if (param_3 != 0) {
    return 0;
  }
  return (-(uint)((param_1 & 0x400) != 0) & 0xfffff900) + 0x806;
}


/* ==== insn_class_h42f6c0 @ 0042f6c0 ==== */

int insn_class_h42f6c0(uint param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = param_1 >> 0xb & 7;
  if (param_3 != 0) {
    return 0;
  }
  if (uVar1 != 5) {
    if (uVar1 == 6) {
      return 0x19;
    }
    if (uVar1 != 7) {
      return (-(uint)((param_1 & 0x400) != 0) & 0x700) + 0x10e;
    }
  }
  return (-(uint)((param_1 & 0x400) != 0) & 0x40) + 0x49;
}


/* ==== insn_class_h42f710 @ 0042f710 ==== */

int insn_class_h42f710(uint param_1,undefined4 param_2,int param_3,int param_4)

{
  if (param_4 != 0) {
    return (-(uint)((param_1 & 0x400) != 0) & 0xfffff900) + 0x806;
  }
  if (param_3 != 0) {
    return 0;
  }
  if ((param_1 & 0x400) != 0) {
    return (-(uint)((param_1 & 0x40) != 0) & 0xfffffe00) + 0x412;
  }
  return (-(uint)((param_1 & 0x40) != 0) & 0xfffff000) + 0x2022;
}


/* ==== insn_class_h42f770 @ 0042f770 ==== */

int insn_class_h42f770(uint param_1)

{
  if ((param_1 & 0x400) != 0) {
    return (-(uint)((param_1 & 0x40) != 0) & 0xfffffe00) + 0x406;
  }
  return (-(uint)((param_1 & 0x40) != 0) & 0xfffff000) + 0x2006;
}


/* ==== insn_class_h42f7a0 @ 0042f7a0 ==== */

int insn_class_h42f7a0(uint param_1,undefined4 param_2,int param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = param_1 & 0x400;
  uVar1 = param_1 & 0x40;
  uVar3 = param_1 >> 0xb & 7;
  if (param_4 != 0) {
    return (-(uint)(uVar2 != 0) & 0xfffff900) + 0x806;
  }
  if (param_3 != 0) {
    return 0;
  }
  if (uVar3 == 4) {
    if (uVar2 != 0) {
      return (-(uint)(uVar1 != 0) & 0xfffff000) + 0x201b;
    }
    return (-(uint)(uVar1 != 0) & 0xfffffe00) + 0x42b;
  }
  if ((uVar3 != 5) && (uVar3 != 7)) {
    if (uVar2 != 0) {
      return (-(uint)(uVar1 != 0) & 0xfffff000) + 0x201a;
    }
    return (-(uint)(uVar1 != 0) & 0xfffffe00) + 0x42a;
  }
  return (-(uint)(uVar2 != 0) & 0x40) + 0x49;
}


/* ==== insn_class_h42f850 @ 0042f850 ==== */

int insn_class_h42f850(uint param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = param_1 >> 0xb & 7;
  if (uVar1 != 5) {
    if (uVar1 == 6) {
      return (-(uint)(param_3 != 0) & 0xffffffe7) + 0x19;
    }
    if (uVar1 != 7) {
      if ((param_1 & 0x400) != 0) {
        return (-(uint)((param_1 & 0x40) != 0) & 0xfffff000) + 0x200e;
      }
      return (-(uint)((param_1 & 0x40) != 0) & 0xfffffe00) + 0x40e;
    }
  }
  return (-(uint)((param_1 & 0x400) != 0) & 0x40) + 0x49;
}


/* ==== insn_class_h42f8b0 @ 0042f8b0 ==== */

int insn_class_h42f8b0(uint param_1,uint param_2,int param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = param_1 & 0x400;
  uVar1 = param_1 >> 0x10 & 1;
  uVar2 = param_1 & 0x40;
  uVar4 = param_1 >> 0xb & 7;
  param_1 = param_1 & 0x8000;
  if (param_4 == 0) {
    switch(uVar4) {
    case 4:
      goto switchD_0042f958_caseD_4;
    case 5:
    case 7:
      return (-(uint)(uVar3 != 0) & 0x40) + 0x49;
    case 6:
      if (param_3 != 0) {
        return 0;
      }
      if (uVar3 == 0) {
        return 0x19;
      }
      return 0xb - (uint)(param_2 < 4);
    default:
      if (param_1 == 0) {
        if (uVar3 == 0) {
          return (-(uint)(uVar1 != 0) & 0xfffff000) + 0x200a;
        }
        return (-(uint)(uVar1 != 0) & 0xfffffe00) + 0x40a;
      }
      if (uVar3 == 0) {
        return (-(uint)(uVar2 != 0) & 0xfffffe00) + 0x40a;
      }
      return (-(uint)(uVar2 != 0) & 0xfffff000) + 0x200a;
    }
  }
  if (uVar4 == 6) {
    return 3;
  }
  if (param_1 == 0) {
    if (uVar3 == 0) {
      return (-(uint)(uVar2 != 0) & 0xfffffe00) + 0x406;
    }
    return (-(uint)(uVar2 != 0) & 0xfffff000) + 0x2006;
  }
  if (uVar3 == 0) {
    return (-(uint)(uVar1 != 0) & 0xfffff000) + 0x2006;
  }
  return (-(uint)(uVar1 != 0) & 0xfffffe00) + 0x406;
switchD_0042f958_caseD_4:
  if (param_1 == 0) {
    if (uVar3 == 0) {
      return (-(uint)(uVar1 != 0) & 0xfffff000) + 0x200b;
    }
    return (-(uint)(uVar1 != 0) & 0xfffffe00) + 0x40b;
  }
  if (uVar3 == 0) {
    return (-(uint)(uVar2 != 0) & 0xfffffe00) + 0x40b;
  }
  return (-(uint)(uVar2 != 0) & 0xfffff000) + 0x200b;
}


/* ==== insn_class_h42fba0 @ 0042fba0 ==== */

int insn_class_h42fba0(uint param_1)

{
  if ((param_1 & 0x10000) != 0) {
    return (-(uint)((param_1 & 0x400) != 0) & 0xfffff200) + 0x1006;
  }
  return (-(uint)((param_1 & 0x400) != 0) & 0xffffe400) + 0x2006;
}


/* ==== insn_class_h42fbe0 @ 0042fbe0 ==== */

int insn_class_h42fbe0(uint param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = param_1 >> 0xb & 7;
  if (uVar1 != 5) {
    if (uVar1 == 6) {
      return (-(uint)(param_3 != 0) & 0xffffffe7) + 0x19;
    }
    if (uVar1 != 7) {
      return (-(uint)((param_1 & 0x400) != 0) & 0x700) + 0x10e;
    }
  }
  return (-(uint)((param_1 & 0x400) != 0) & 0x40) + 0x49;
}


/* ==== insn_class_h42fc30 @ 0042fc30 ==== */

int insn_class_h42fc30(uint param_1)

{
  return (-(uint)((param_1 & 0x400) != 0) & 0xfffff900) + 0x806;
}


/* ==== insn_class_h42fc50 @ 0042fc50 ==== */

int insn_class_h42fc50(uint param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = param_1 >> 0xb & 7;
  if (param_3 != 0) {
    return 0;
  }
  if ((uVar1 != 5) && (uVar1 != 7)) {
    if ((param_1 & 0x400) != 0) {
      return (-(uint)((param_1 & 0x40) != 0) & 0xfffff000) + 0x200e;
    }
    return (-(uint)((param_1 & 0x40) != 0) & 0xfffffe00) + 0x40e;
  }
  return (-(uint)((param_1 & 0x400) != 0) & 0x40) + 0x49;
}


/* ==== insn_class_h42fcb0 @ 0042fcb0 ==== */

char insn_class_h42fcb0(uint param_1)

{
  return (-((param_1 & 0x400) != 0) & 0x40U) + 0x46;
}


/* ==== insn_class_h42fcd0 @ 0042fcd0 ==== */

int insn_class_h42fcd0(uint param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  if (param_4 != 0) {
    return 0;
  }
  if (((param_1 & 0x2000) != 0) && ((param_1 & 0x800) != 0)) {
    return (-(uint)((param_1 & 0x400) != 0) & 0x40) + 0x49;
  }
  return (-(uint)((param_1 & 0x400) != 0) & 0x1c00) + 0x40e;
}


/* ==== insn_class_h42fd20 @ 0042fd20 ==== */

int insn_class_h42fd20(uint param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  if (param_4 != 0) {
    return 0;
  }
  if (((param_1 & 0x2000) != 0) && ((param_1 & 0x800) != 0)) {
    return (-(uint)((param_1 & 0x400) != 0) & 0x40) + 0x49;
  }
  return (-(uint)((param_1 & 0x400) != 0) & 0xe00) + 0x20e;
}


/* ==== insn_class_h42fd70 @ 0042fd70 ==== */

int insn_class_h42fd70(uint param_1,undefined4 param_2,int param_3,int param_4)

{
  if (param_4 != 0) {
    return (-(uint)((param_1 & 0x400) != 0) & 0xfffff900) + 0x806;
  }
  if (param_3 != 0) {
    return 0;
  }
  return (-(uint)((param_1 & 0x400) != 0) & 0xfffffff0) + 0x22;
}


/* ==== insn_class_code @ 0042fdb0 ==== */

ulong __cdecl insn_class_code(ulong opw,long mode,long sel,ulong devflags)

{
  int iVar1;
  ulong uVar2;
  
  if (sel != 0) {
    if (sel != 1) {
      if (sel != 3) {
        return 0;
      }
      return 6;
    }
    mode = 0;
  }
  iVar1 = opclass_lookup(opw,devflags);
  uVar2 = (*(code *)(&insn_class_handlers)[iVar1])(opw,devflags,mode,sel);
  return uVar2;
}


/* ==== insn_ea_class @ 0042fe10 ==== */

void __cdecl insn_ea_class(ulong opw,long flag,ulong *out,ulong devflags)

{
  int iVar1;
  
  iVar1 = opclass_lookup(opw,devflags);
  if (flag != 0) {
    *out = *(ulong *)(&DAT_004c3ff8 + iVar1 * 4);
    return;
  }
  *out = *(ulong *)(&DAT_004c3e40 + iVar1 * 4);
  return;
}


/* ==== insn_valid_h42fe50 @ 0042fe50 ==== */

undefined4 insn_valid_h42fe50(void)

{
  return 2;
}


/* ==== insn_valid_h42fe60 @ 0042fe60 ==== */

int insn_valid_h42fe60(uint param_1)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  
  uVar2 = (int)param_1 >> 8;
  bVar3 = true;
  if (((uVar2 & 0xcf80) == 0xcf80) || ((uVar2 & 0xcf80) == 0xca80)) {
    bVar3 = false;
  }
  if ((((param_1 & 0x80) != 0) || (*(int *)(&DAT_004c41b0 + (param_1 & 0x7f) * 4) != 0)) &&
     ((((((uVar2 & 0x8c80) == 0x8c80 && (((byte)param_1 & 8) == 8)) ||
        (((uVar2 & 0xc300) == 0xc300 && (((byte)param_1 & 8) == 8)))) ||
       (((uVar2 & 0x8c80) == 0x8880 && ((param_1 & 8) == 0)))) ||
      (((uVar2 & 0xc300) == 0xc200 && ((param_1 & 8) == 0)))))) {
    bVar3 = false;
  }
  iVar1 = 0;
  if (bVar3) {
    iVar1 = ea_mode_index(param_1);
  }
  return iVar1;
}


/* ==== ea_mode_index @ 0042ff20 ==== */

int __cdecl ea_mode_index(ulong opw)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = opw & 0xff;
  if ((opw & 0x80) == 0) {
    if (((uVar1 == 4) || (uVar1 == 8)) || (uVar1 == 0xc)) {
      iVar2 = 0x40;
    }
    else {
      iVar2 = ((int)uVar1 >> 1 & 0x38U) + (opw & 7);
    }
  }
  else {
    iVar2 = (opw & 3) + 0x42;
  }
  if (((iVar2 != 4) && (iVar2 != 0xd)) && ((iVar2 != 0x40 && (iVar2 != 0x41)))) {
    return 1;
  }
  return 0;
}


/* ==== insn_valid_pm_a @ 0042ff80 ==== */

int __cdecl insn_valid_pm_a(ulong opw)

{
  int iVar1;
  
  iVar1 = ea_mode_index(opw);
  if (((opw & 0x8000) == 0) && ((opw & 0x3f00) == 0x3400)) {
    iVar1 = 0;
  }
  return iVar1;
}


/* ==== insn_valid_h42ffb0 @ 0042ffb0 ==== */

void insn_valid_h42ffb0(ulong param_1)

{
  ea_mode_index(param_1);
  return;
}


/* ==== insn_valid_h42ffc0 @ 0042ffc0 ==== */

int insn_valid_h42ffc0(uint param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  
  bVar1 = (byte)(param_1 >> 8);
  bVar4 = true;
  if (((param_1 & 0x80) == 0) && (*(int *)(&DAT_004c41b0 + (param_1 & 0x7f) * 4) == 0))
  goto LAB_0043004c;
  iVar2 = insn_valid_pm_b(param_1);
  if (iVar2 == 0) {
    uVar3 = (int)param_1 >> 8 & 0xf180;
    if ((uVar3 != 0x5180) || (((byte)param_1 & 8) != 8)) {
      if (uVar3 != 0x5080) goto LAB_0043004c;
      goto joined_r0x00430048;
    }
  }
  else {
    uVar3 = (int)param_1 >> 8 & 0xf580;
    if ((uVar3 != 0x5580) || (((byte)param_1 & 8) != 8)) {
      if (uVar3 != 0x5480) goto LAB_0043004c;
joined_r0x00430048:
      if ((param_1 & 8) != 0) goto LAB_0043004c;
    }
  }
  bVar4 = false;
LAB_0043004c:
  iVar2 = 0;
  if (bVar4) {
    iVar2 = ea_mode_index(param_1);
  }
  if (((bVar1 & 0xc0) == 0x40) && ((bVar1 & 0x3f) == 0x34)) {
    iVar2 = 0;
  }
  return iVar2;
}


/* ==== insn_valid_pm_b @ 00430080 ==== */

int __cdecl insn_valid_pm_b(ulong opw)

{
  if (((opw & 0x80) == 0) && (*(int *)(&DAT_004c43b0 + (opw & 0x7f) * 4) != 0)) {
    return 1;
  }
  return 0;
}


/* ==== insn_valid_h4300a0 @ 004300a0 ==== */

int insn_valid_h4300a0(uint param_1)

{
  int iVar1;
  bool bVar2;
  uint uVar3;
  
  bVar2 = true;
  if ((((param_1 & 0x80) != 0) || (*(int *)(&DAT_004c41b0 + (param_1 & 0x7f) * 4) != 0)) &&
     (((((uVar3 = (int)param_1 >> 8 & 0xff80, uVar3 == 0x4b80 || (uVar3 == 0x4a80)) ||
        ((uVar3 == 0x4180 && (((byte)param_1 & 8) == 8)))) ||
       ((uVar3 == 0x4080 && ((param_1 & 8) == 0)))) ||
      (((uVar3 == 0x4980 && (((byte)param_1 & 8) == 8)) ||
       ((uVar3 == 0x4880 && ((param_1 & 8) == 0)))))))) {
    bVar2 = false;
  }
  iVar1 = 0;
  if (bVar2) {
    iVar1 = ea_mode_index(param_1);
  }
  if ((((int)param_1 >> 8 & 0x40U) != 0) && (((byte)(param_1 >> 8) & 0x3f) == 0x34)) {
    iVar1 = 0;
  }
  return iVar1;
}


/* ==== insn_valid_h430160 @ 00430160 ==== */

int insn_valid_h430160(uint param_1)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  
  bVar3 = true;
  if (((param_1 & 0x80) == 0) && (*(int *)(&DAT_004c41b0 + (param_1 & 0x7f) * 4) == 0))
  goto LAB_004301ef;
  iVar1 = insn_valid_pm_b(param_1);
  if (iVar1 == 0) {
    uVar2 = (int)param_1 >> 8 & 0xf900;
    if ((uVar2 != 0x2900) || (((byte)param_1 & 8) != 8)) {
      if (uVar2 != 0x2800) goto LAB_004301ef;
      goto joined_r0x004301eb;
    }
  }
  else {
    uVar2 = (int)param_1 >> 8 & 0xfd00;
    if ((uVar2 != 0x2d00) || (((byte)param_1 & 8) != 8)) {
      if (uVar2 != 0x2c00) goto LAB_004301ef;
joined_r0x004301eb:
      if ((param_1 & 8) != 0) goto LAB_004301ef;
    }
  }
  bVar3 = false;
LAB_004301ef:
  iVar1 = 0;
  if (bVar3) {
    iVar1 = ea_mode_index(param_1);
  }
  return iVar1;
}


/* ==== insn_valid_h430210 @ 00430210 ==== */

int insn_valid_h430210(uint param_1)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  
  uVar2 = (int)param_1 >> 8;
  bVar3 = true;
  if (((param_1 & 0x80) == 0) && (*(int *)(&DAT_004c41b0 + (param_1 & 0x7f) * 4) == 0))
  goto LAB_0043029c;
  iVar1 = insn_valid_pm_b(param_1);
  if (iVar1 == 0) {
    if (((uVar2 & 0xfc19) != 0x2009) || (((byte)param_1 & 8) != 8)) {
      if ((uVar2 & 0xfc19) != 0x2008) goto LAB_0043029c;
      goto joined_r0x00430298;
    }
  }
  else if (((uVar2 & 0xfc1d) != 0x200d) || (((byte)param_1 & 8) != 8)) {
    if ((uVar2 & 0xfc1d) != 0x200c) goto LAB_0043029c;
joined_r0x00430298:
    if ((param_1 & 8) != 0) goto LAB_0043029c;
  }
  bVar3 = false;
LAB_0043029c:
  if (((byte)(param_1 >> 8) & 0x1f) < 4) {
    bVar3 = false;
  }
  if ((uVar2 & 0x3e0) < 0x80) {
    bVar3 = false;
  }
  iVar1 = 0;
  if (bVar3) {
    iVar1 = ea_mode_index(param_1);
  }
  return iVar1;
}


/* ==== insn_valid_pm_c @ 004302d0 ==== */

int __cdecl insn_valid_pm_c(ulong opw)

{
  int iVar1;
  
  iVar1 = ea_mode_index(opw);
  if (((opw & 0xffff00) != 0x200000) || ((char)opw == '\0')) {
    iVar1 = 0;
  }
  return iVar1;
}


/* ==== insn_valid_pm_d @ 00430300 ==== */

int __cdecl insn_valid_pm_d(ulong opw)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  
  bVar3 = true;
  if ((((opw & 0x80) != 0) || (*(int *)(&DAT_004c41b0 + (opw & 0x7f) * 4) != 0)) &&
     (((uVar2 = (int)opw >> 8 & 0xf3c0, uVar2 == 0x13c0 && (((byte)opw & 8) == 8)) ||
      ((uVar2 == 0x12c0 && ((opw & 8) == 0)))))) {
    bVar3 = false;
  }
  iVar1 = 0;
  if (bVar3) {
    iVar1 = ea_mode_index(opw);
  }
  if ((((int)opw >> 8 & 0x80U) == 0) && (((byte)(opw >> 8) & 0x3f) == 0x34)) {
    iVar1 = 0;
  }
  return iVar1;
}


/* ==== insn_valid_pm_e @ 00430390 ==== */

int __cdecl insn_valid_pm_e(ulong opw)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  
  bVar3 = true;
  if ((((opw & 0x80) != 0) || (*(int *)(&DAT_004c41b0 + (opw & 0x7f) * 4) != 0)) &&
     (((uVar2 = (int)opw >> 8 & 0xfcc0, uVar2 == 0x1c80 && (((byte)opw & 8) == 8)) ||
      ((uVar2 == 0x1880 && ((opw & 8) == 0)))))) {
    bVar3 = false;
  }
  if ((((int)opw >> 8 & 0x80U) == 0) && (((byte)(opw >> 8) & 0x3f) == 0x34)) {
    bVar3 = false;
  }
  iVar1 = 0;
  if (bVar3) {
    iVar1 = ea_mode_index(opw);
  }
  return iVar1;
}


/* ==== insn_valid_h430410 @ 00430410 ==== */

bool insn_valid_h430410(uint param_1)

{
  return (param_1 & 0x3f00) != 0x3400;
}


/* ==== insn_valid_h430430 @ 00430430 ==== */

bool insn_valid_h430430(byte param_1)

{
  return (param_1 & 0x1f) < 0x18;
}


/* ==== insn_valid_h430450 @ 00430450 ==== */

bool insn_valid_h430450(uint param_1)

{
  bool bVar1;
  
  bVar1 = ((byte)param_1 & 0x1f) < 0x18;
  if (((param_1 & 0x3f00) == 0x3400) || ((param_1 & 0x3f00) == 0x3000)) {
    bVar1 = false;
  }
  return bVar1;
}


/* ==== insn_valid_h430480 @ 00430480 ==== */

bool insn_valid_h430480(uint param_1)

{
  return (param_1 & 0x3f00) != 0x3400 && ((byte)param_1 & 0x1f) < 0x18;
}


/* ==== insn_valid_h4304b0 @ 004304b0 ==== */

undefined4 insn_valid_h4304b0(uint param_1)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if (((param_1 & 0x8000) == 0) && ((param_1 & 0x3f00) == 0x3400)) {
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== insn_valid_h4304e0 @ 004304e0 ==== */

bool insn_valid_h4304e0(uint param_1)

{
  if ((param_1 & 0x3f00) < 0x400) {
    return false;
  }
  if ((param_1 & 0x3800) == 0x2800) {
    return false;
  }
  return (param_1 & 0x3800) != 0x3000;
}


/* ==== insn_valid_h430510 @ 00430510 ==== */

bool insn_valid_h430510(uint param_1)

{
  bool bVar1;
  
  if ((param_1 & 0x3f) < 4) {
    bVar1 = false;
  }
  else if ((param_1 & 0x38) == 0x28) {
    bVar1 = false;
  }
  else {
    bVar1 = (param_1 & 0x38) != 0x30;
  }
  if ((param_1 & 0x3f00) == 0x3400) {
    bVar1 = false;
  }
  return bVar1;
}


/* ==== insn_valid_h430550 @ 00430550 ==== */

bool insn_valid_h430550(uint param_1)

{
  if ((param_1 & 0x3f) < 4) {
    return false;
  }
  if ((param_1 & 0x38) == 0x28) {
    return false;
  }
  return (param_1 & 0x38) != 0x30;
}


/* ==== insn_valid_h430580 @ 00430580 ==== */

undefined4 insn_valid_h430580(uint param_1)

{
  if (((param_1 & 0x3f00) != 0x3400) && ((param_1 & 0x3f00) != 0x3000)) {
    return 1;
  }
  return 0;
}


/* ==== insn_valid_h4305a0 @ 004305a0 ==== */

bool insn_valid_h4305a0(uint param_1)

{
  if ((param_1 & 0x3f00) < 0x400) {
    return false;
  }
  if ((param_1 & 0x3800) == 0x2800) {
    return false;
  }
  if ((param_1 & 0x3800) == 0x3000) {
    return false;
  }
  return (param_1 & 0x3f00) != 0x3c00;
}


/* ==== insn_valid_h4305e0 @ 004305e0 ==== */

undefined4 insn_valid_h4305e0(uint param_1)

{
  if ((param_1 & 0x3f00) < 0x400) {
    return 0;
  }
  if ((param_1 & 0x3800) == 0x2800) {
    return 0;
  }
  if ((param_1 & 0x3800) == 0x3000) {
    return 0;
  }
  if (((param_1 & 0x3f00) == 0x3c00) && (((byte)param_1 & 7) == 4)) {
    return 0;
  }
  return 1;
}


/* ==== insn_valid_h430630 @ 00430630 ==== */

undefined4 insn_valid_h430630(uint param_1)

{
  if ((8 < (param_1 & 0x78)) && ((param_1 & 0x78) < 0x40)) {
    return 0;
  }
  return 1;
}


/* ==== insn_valid_h430650 @ 00430650 ==== */

bool insn_valid_h430650(byte param_1)

{
  return (param_1 & 3) != 3;
}


/* ==== insn_valid_pm_f @ 00430670 ==== */

int __cdecl insn_valid_pm_f(ulong opw)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = (opw & 0x3f00) != 0x3400;
  if ((((opw & 0x80) != 0) || (*(int *)(&DAT_004c41b0 + (opw & 0x7f) * 4) != 0)) &&
     (bVar2 = (opw & 0xf4008) != 0x80000 && bVar2, (opw & 0xf4008) == 0x90008)) {
    bVar2 = false;
  }
  iVar1 = 0;
  if (bVar2) {
    iVar1 = ea_mode_index(opw);
  }
  return iVar1;
}


/* ==== insn_valid_h4306e0 @ 004306e0 ==== */

bool insn_valid_h4306e0(uint param_1)

{
  bool bVar1;
  
  bVar1 = ((byte)param_1 & 0x1f) < 0x18;
  if ((((param_1 & 0x3f00) < 0x400) || ((param_1 & 0x3800) == 0x2800)) ||
     ((param_1 & 0x3800) == 0x3000)) {
    bVar1 = false;
  }
  return bVar1;
}


/* ==== insn_valid_h430720 @ 00430720 ==== */

undefined4 insn_valid_h430720(int param_1)

{
  uint uVar1;
  
  uVar1 = param_1 >> 8 & 0x1f;
  if ((uVar1 != 0) && (uVar1 < 0x18)) {
    return 1;
  }
  return 0;
}


/* ==== opclass_lookup @ 00430740 ==== */

int __cdecl opclass_lookup(ulong opw,ulong cpu)

{
  int iVar1;
  undefined4 *puVar2;
  uint *puVar3;
  uint uVar4;
  
  if (3 < cpu) {
    iVar1 = opclass_lookup_any(opw);
    return iVar1;
  }
  uVar4 = opw & 0xffffff;
  if (uVar4 == opclass_key) {
    return opclass_last;
  }
  iVar1 = 0;
  opclass_key = uVar4;
  if (uVar4 < DAT_004c45b4) {
    puVar2 = &DAT_004c45b4;
    do {
      puVar3 = puVar2 + 4;
      puVar2 = puVar2 + 4;
      iVar1 = iVar1 + 1;
    } while (uVar4 < *puVar3);
  }
  for (puVar3 = &DAT_004c45b4 + iVar1 * 4; ((puVar3[-1] & uVar4) != *puVar3 || (puVar3[2] != 0));
      puVar3 = puVar3 + 4) {
    iVar1 = iVar1 + 1;
  }
  opclass_last = *(int *)(iVar1 * 0x10 + 0x4c45b8);
  return opclass_last;
}


/* ==== opclass_lookup_any @ 004307d0 ==== */

int __cdecl opclass_lookup_any(ulong opw)

{
  uint *puVar1;
  uint *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  
  uVar4 = opw & 0xffffff;
  if (uVar4 == opclass_key_any) {
    return opclass_last_any;
  }
  iVar5 = 0;
  opclass_key_any = uVar4;
  if (uVar4 < DAT_004c45b4) {
    puVar3 = &DAT_004c45b4;
    do {
      puVar1 = puVar3 + 4;
      puVar3 = puVar3 + 4;
      iVar5 = iVar5 + 1;
    } while (uVar4 < *puVar1);
  }
  puVar3 = &DAT_004c45b4 + iVar5 * 4;
  if (((&opclass_table)[iVar5 * 4] & uVar4) != (&DAT_004c45b4)[iVar5 * 4]) {
    do {
      puVar1 = puVar3 + 3;
      puVar2 = puVar3 + 4;
      puVar3 = puVar3 + 4;
      iVar5 = iVar5 + 1;
    } while ((*puVar1 & uVar4) != *puVar2);
  }
  opclass_last_any = *(int *)(iVar5 * 0x10 + 0x4c45b8);
  return opclass_last_any;
}


