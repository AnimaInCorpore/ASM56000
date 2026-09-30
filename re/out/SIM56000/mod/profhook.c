/* ==== sim_profile_step @ 00458c10 ==== */

void __cdecl sim_profile_step(int dev)

{
  undefined4 uVar1;
  int iVar2;
  long lVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int *piVar7;
  undefined4 *puVar8;
  undefined4 uStack_354;
  undefined4 uStack_350;
  int local_34c [55];
  int local_270;
  int local_26c;
  undefined4 local_268;
  undefined4 local_260;
  int iStack_25c;
  undefined4 auStack_258 [100];
  undefined4 auStack_c8 [50];
  
  iVar2 = cur_sim;
  if (*(int *)(cur_sim + 0x188) == 0) {
    return;
  }
  piVar7 = local_34c;
  for (iVar4 = 0xa1; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar7 = 0;
    piVar7 = piVar7 + 1;
  }
  if (*(uint *)(cur_dev + 0x20) < *(uint *)(cur_sim + 0x28c)) {
    *(uint *)(cur_sim + 0x28c) = *(uint *)(cur_dev + 0x20);
  }
  local_26c = *(int *)(cur_dev + 0x20);
  local_260 = *(undefined4 *)(cur_dev + 0x1c);
  local_270 = local_26c - *(int *)(iVar2 + 0x28c);
  local_268 = *(undefined4 *)(iVar2 + 0x47c);
  (**(code **)(*(int *)(cur_itype + 0x18) + 0x3c))
            (dev,0,*(undefined4 *)(iVar2 + 0x290),local_260,local_34c);
  if (*(int *)(iVar2 + 0x428) == 1) {
    *(undefined4 *)(iVar2 + 0x42c) = 0;
    *(int *)(iVar2 + 0x424) = local_34c[0];
    *(undefined4 *)(iVar2 + 0x430) = 0;
    *(undefined4 *)(iVar2 + 0x428) = 2;
  }
  else if (*(int *)(iVar2 + 0x428) == 2) {
    *(int *)(iVar2 + 0x42c) = *(int *)(iVar2 + 0x42c) + local_270;
    *(int *)(iVar2 + 0x430) = *(int *)(iVar2 + 0x430) + 1;
    if ((*(byte *)(cur_dev + 0x44) & 2) == 0) {
      iStack_25c = iVar2 + 0x424;
      *(undefined4 *)(iVar2 + 0x428) = 3;
    }
  }
  puVar6 = (undefined4 *)(iVar2 + 0x294);
  puVar8 = auStack_c8;
  for (iVar4 = 0x32; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar8 = puVar8 + 1;
  }
  ref_prune(local_34c);
  puVar6 = auStack_258;
  for (iVar4 = 100; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  puVar6 = (undefined4 *)(iVar2 + 0x35c);
  puVar8 = auStack_258;
  for (iVar4 = 0x32; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar8 = puVar8 + 1;
  }
  puVar6 = (undefined4 *)(iVar2 + 0x294);
  for (iVar4 = 100; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  prof_record_insn(local_34c);
  iVar4 = *(int *)(iVar2 + 0x428);
  puVar6 = auStack_c8;
  puVar8 = (undefined4 *)(iVar2 + 0x35c);
  for (iVar5 = 0x32; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar8 = puVar8 + 1;
  }
  if (iVar4 == 3) {
    *(undefined4 *)(iVar2 + 0x428) = 0;
  }
  *(undefined4 *)(iVar2 + 0x290) = *(undefined4 *)(cur_dev + 0x1c);
  uVar1 = *(undefined4 *)(cur_dev + 0x20);
  *(undefined4 *)(iVar2 + 0x47c) = 0;
  *(undefined4 *)(iVar2 + 0x28c) = uVar1;
  *(undefined4 *)(iVar2 + 0x488) = 1;
  if ((*(int *)(iVar2 + 0x43c) == 0) &&
     (lVar3 = periph_find_reg(dev,&DAT_004b2924,(int *)(iVar2 + 0x438),(int *)(iVar2 + 0x434)),
     lVar3 != 0)) {
    *(undefined4 *)(iVar2 + 0x43c) = 1;
  }
  if (*(int *)(iVar2 + 0x43c) != 0) {
    periph_call(dev,*(int *)(iVar2 + 0x438),*(long *)(iVar2 + 0x434),(long)(iVar2 + 0x440));
    *(uint *)(iVar2 + 0x470) = *(uint *)(iVar2 + 0x440) >> 0xf & 1;
  }
  if ((*(int *)(iVar2 + 0x464) == 0) &&
     (lVar3 = periph_find_reg(dev,&DAT_004b2998,(int *)(iVar2 + 0x460),(int *)(iVar2 + 0x45c)),
     lVar3 != 0)) {
    *(undefined4 *)(iVar2 + 0x464) = 1;
  }
  if (*(int *)(iVar2 + 0x450) == 0) {
    lVar3 = periph_find_reg(dev,&DAT_004b2994,(int *)(iVar2 + 0x44c),(int *)(iVar2 + 0x448));
    if (lVar3 != 0) {
      *(undefined4 *)(iVar2 + 0x450) = 1;
    }
    if (*(int *)(iVar2 + 0x450) == 0) {
      return;
    }
  }
  if (*(int *)(iVar2 + 0x464) == 0) {
    return;
  }
  uStack_354 = local_34c[1];
  uStack_350 = local_34c[2];
  iVar4 = (**(code **)(cur_itype + 0x10))(&uStack_354,&prof_disasm_buf,0,0,0);
  if (iVar4 != 0) {
    iVar5 = strncmp(&prof_disasm_buf,&DAT_004bfc28,2);
    if (iVar5 == 0) {
      iVar4 = *(int *)(iVar2 + 0x474) + 1;
    }
    else {
      *(undefined4 *)(iVar2 + 0x46c) = *(undefined4 *)(iVar2 + 0x468);
      periph_call(dev,*(int *)(iVar2 + 0x460),*(long *)(iVar2 + 0x45c),(long)(iVar2 + 0x468));
      if ((((*(int *)(iVar2 + 0x454) != 1) ||
           (local_34c[0] != (*(int *)(iVar2 + 0x46c) - iVar4) + 1)) ||
          (((*(int *)(iVar2 + 0x428) != 0 || (prof_prev_state != 0)) &&
           (*(int *)(iVar2 + 0x468) == *(int *)(iVar2 + 0x46c))))) ||
         ((((*(int *)(cur_dtype + 4) == 0x2ca || (*(int *)(cur_dtype + 4) == 0x2c8)) &&
           ((*(uint *)(iVar2 + 0x440) & 0x10000) != 0)) ||
          (iVar4 = *(int *)(iVar2 + 0x474), iVar4 == 0)))) goto LAB_00458fd9;
      if (*(int *)(iVar2 + 0x478) < iVar4) {
        *(int *)(iVar2 + 0x478) = iVar4;
      }
      iVar4 = iVar4 + -1;
    }
    *(int *)(iVar2 + 0x474) = iVar4;
  }
LAB_00458fd9:
  *(undefined4 *)(iVar2 + 0x458) = *(undefined4 *)(iVar2 + 0x454);
  periph_call(dev,*(int *)(iVar2 + 0x44c),*(long *)(iVar2 + 0x448),iVar2 + 0x454);
  prof_prev_state = *(undefined4 *)(iVar2 + 0x428);
  return;
}


