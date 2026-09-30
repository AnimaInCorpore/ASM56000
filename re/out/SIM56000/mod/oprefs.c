/* ==== ref_kind_info @ 00459030 ==== */

void __cdecl ref_kind_info(int kind,long *pcat,long *prw)

{
  if (prw != (long *)0x0) {
    if (kind < 0xf) {
      if ((kind == 0xe) || (kind == 10)) goto LAB_0045908b;
LAB_00459048:
      *prw = 1;
    }
    else if (kind < 0x14) {
      if (kind == 0x13) goto LAB_0045908b;
      if (kind == 0xf) goto LAB_00459093;
      *prw = 1;
    }
    else {
      if (kind < 0x19) {
        if (kind != 0x18) {
          if (kind != 0x14) {
            *prw = 1;
            goto LAB_00459099;
          }
LAB_00459093:
          *prw = 2;
          goto LAB_00459099;
        }
      }
      else {
        if (kind == 0x19) goto LAB_00459093;
        if ((kind < 0x122) || (0x123 < kind)) goto LAB_00459048;
      }
LAB_0045908b:
      *prw = 0;
    }
  }
LAB_00459099:
  if (kind < 0x10) {
    if (kind < 0xd) {
      switch(kind) {
      case 0:
        break;
      case 1:
        goto switchD_004590b0_caseD_1;
      case 2:
        goto switchD_004590b0_caseD_2;
      case 3:
      case 9:
      case 10:
        *pcat = 4;
        return;
      default:
        goto switchD_004590b0_caseD_4;
      }
    }
    *pcat = 3;
    return;
  }
  if (kind < 0x1a) {
    if (0x16 < kind) {
switchD_004590b0_caseD_2:
      *pcat = 2;
      return;
    }
    if (kind < 0x12) {
switchD_004590b0_caseD_4:
      *pcat = 0;
      return;
    }
    if (0x14 < kind) {
      *pcat = 0;
      return;
    }
  }
  else if (kind != 0x122) {
    if (kind != 0x123) goto switchD_004590b0_caseD_4;
    goto switchD_004590b0_caseD_2;
  }
switchD_004590b0_caseD_1:
  *pcat = 1;
  return;
}


/* ==== ref_record @ 00459140 ==== */

void __cdecl ref_record(int kind,long addr,long a3,long a4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  long local_4;
  
  iVar2 = cur_sim;
  iVar1 = cur_sim + 0x188;
  ref_kind_info(kind,&kind,&local_4);
  iVar3 = 0;
  piVar4 = (int *)(iVar2 + 0x294);
  do {
    if (*piVar4 == 0) {
      iVar2 = iVar1 + iVar3 * 0x14;
      *(int *)(iVar2 + 0x10c) = kind;
      *(long *)(iVar2 + 0x110) = local_4;
      *(long *)(iVar2 + 0x114) = addr;
      *(long *)(iVar1 + (iVar3 + 0xe) * 0x14) = a3;
      *(long *)(iVar2 + 0x11c) = a4;
      return;
    }
    iVar3 = iVar3 + 1;
    piVar4 = piVar4 + 5;
  } while (iVar3 < 10);
  return;
}


/* ==== ref_prune @ 004591c0 ==== */

void __cdecl ref_prune(void *insn)

{
  int iVar1;
  bool bVar2;
  int *piVar3;
  int iVar4;
  
  bVar2 = false;
  iVar4 = 0;
  piVar3 = (int *)((int)insn + 0x20);
  do {
    if (*piVar3 == 3) {
      bVar2 = true;
      break;
    }
    iVar4 = iVar4 + 1;
    piVar3 = piVar3 + 7;
  } while (iVar4 < 4);
  if (!bVar2) {
    iVar4 = *(int *)((int)insn + 0x84);
    if (((iVar4 != 0) && (iVar1 = *(int *)(iVar4 + 8), iVar1 != 0)) &&
       (((*(int *)(iVar1 + 0xc) == 3 || (*(int *)(iVar1 + 0x28) == 3)) ||
        (((*(int *)(iVar4 + 4) != 0 && (iVar4 = *(int *)(*(int *)(iVar4 + 4) + 8), iVar4 != 0)) &&
         ((*(int *)(iVar4 + 0xc) == 3 || (*(int *)(iVar4 + 0x28) == 3)))))))) {
      bVar2 = true;
    }
    if (!bVar2) {
      iVar4 = 0x14;
      piVar3 = (int *)(cur_sim + 0x294);
      do {
        if ((*piVar3 == 3) && (piVar3[4] == 0)) {
          *piVar3 = 0;
        }
        piVar3 = piVar3 + 5;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
  }
  return;
}


