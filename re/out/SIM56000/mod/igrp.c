/* ==== igrp_map_kind @ 00401140 ==== */

int __cdecl igrp_map_kind(void *rec)

{
  int iVar1;
  
  iVar1 = *(int *)((int)rec + 0x10);
  switch(iVar1) {
  case 0:
    return 0;
  case 0x10:
    return (-(uint)(*(int *)((int)rec + 0x88) != 0x10) & 0x4f) + 0x10;
  case 0x14:
    return (-(uint)(*(int *)((int)rec + 0x88) != 0x10) & 0x4c) + 0x14;
  case 0x2b:
    return (-(uint)(*(int *)((int)rec + 0x88) != 0x10) & 0x36) + 0x2b;
  case 0x2c:
    iVar1 = (-(uint)(*(int *)((int)rec + 0x88) != 0x10) & 0x36) + 0x2c;
    break;
  case 0x49:
    return 0x48;
  case 0x4b:
    return 0x4a;
  case 0x4f:
    return 0x4e;
  case 0x51:
    return 0x50;
  }
  return iVar1;
}


/* ==== igrp_names_hook @ 00401250 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void igrp_names_hook(void *rec)

{
  mnemonic_name((int)rec);
  return;
}


/* ==== igrp_fill_mode_names @ 00401260 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void igrp_fill_mode_names(char **tab)

{
  tab[0xc] = s_opcode_reg1_reg2_acc_004ad714;
  tab[10] = s_opcode_reg__n_acc_004ad700;
  tab[0x1c] = s_opcode_reg_acc_004ad6f0;
  tab[0x1a] = s_opcode_immediate_acc_004ad6d8;
  tab[0x25] = s_opcode__n_s_indirect_004ad6c0;
  tab[0x29] = s_opcode__n_s_absolute_004ad6a8;
  tab[0x2c] = s_opcode__n_reg_004ad698;
  tab[0x3c] = s_opcode_reg1_reg2_acc_004ad714;
  tab[0x3a] = s_opcode_immediate_reg_acc_004ad67c;
  tab[0x45] = s_opcode__n_s_indirect_label_004ad660;
  tab[0x49] = s_opcode__n_s_absolute_label_004ad644;
  tab[0x4c] = s_opcode__n_reg_label_004ad630;
  tab[0x59] = s_opcode_label_004ad620;
  tab[0x55] = s_opcode_indirect_004ad610;
  tab[0x5c] = s_opcode_relative_label_004ad5f8;
  tab[0x5e] = s_opcode_relative_indirect_004ad5dc;
  tab[0x65] = s_opcode_s_indirect_label_004ad5c4;
  tab[0x69] = s_opcode_s_absolute_label_004ad5ac;
  tab[0x6a] = s_opcode_immediate_label_004ad594;
  tab[0x6c] = s_opcode_reg_label_004ad580;
  tab[0x75] = s_opcode_s_indirect_dst_004ad568;
  tab[0x79] = s_opcode_s_absolute_dst_004ad550;
  tab[0x7a] = s_opcode_immediate_dst_004ad538;
  tab[0x7c] = s_opcode_reg_dst_004ad528;
  tab[0x7d] = s_opcode_s__Rn_absolute__dst_004ad50c;
  tab[0x85] = s_opcode_src_s_indirect_004ad4f4;
  tab[0x89] = s_opcode_src_s_absolute_004ad4dc;
  tab[0x8c] = s_opcode_src_reg_004ad4cc;
  tab[0x8d] = s_opcode_src_s__Rn_absolute__004ad4b0;
  return;
}


/* ==== igrp_count_instr @ 00401380 ==== */

void __cdecl igrp_count_instr(void *rec)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = igrp_map_kind(rec);
  switch(iVar1) {
  case 0:
    *(int *)(prof_ctx + 0x31a0) = *(int *)(prof_ctx + 0x31a0) + 1;
    iVar1 = igrp_mode_bucket(*(int *)((int)rec + 0x14));
    *(int *)(prof_ctx + 0x31a0 + iVar1 * 4) = *(int *)(prof_ctx + 0x31a0 + iVar1 * 4) + 1;
    *(int *)(prof_ctx + 0x31e0) = *(int *)(prof_ctx + 0x31e0) + 1;
    iVar1 = igrp_mode_bucket(*(int *)((int)rec + 0x30));
    piVar2 = (int *)(prof_ctx + 0x31e0 + iVar1 * 4);
    break;
  default:
    goto switchD_0040139f_caseD_1;
  case 2:
  case 3:
  case 5:
  case 6:
    *(int *)(prof_ctx + 0x3060) = *(int *)(prof_ctx + 0x3060) + 1;
    iVar1 = igrp_mode_bucket(*(int *)((int)rec + 0x30));
    piVar2 = (int *)(prof_ctx + 0x3060 + iVar1 * 4);
    break;
  case 8:
  case 10:
    *(int *)(prof_ctx + 0x3160) = *(int *)(prof_ctx + 0x3160) + 1;
    iVar1 = igrp_mode_bucket(*(int *)((int)rec + 0x14));
    piVar2 = (int *)(prof_ctx + 0x3160 + iVar1 * 4);
    break;
  case 0x10:
  case 0x14:
  case 0x2b:
  case 0x2c:
  case 0x5f:
  case 0x60:
  case 0x61:
  case 0x62:
    *(int *)(prof_ctx + 0x3120) = *(int *)(prof_ctx + 0x3120) + 1;
    iVar1 = igrp_mode_bucket(*(int *)((int)rec + 0x14));
    piVar2 = (int *)(prof_ctx + 0x3120 + iVar1 * 4);
    break;
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x15:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
    *(int *)(prof_ctx + 0x30e0) = *(int *)(prof_ctx + 0x30e0) + 1;
    iVar1 = igrp_mode_bucket(*(int *)((int)rec + 0x30));
    piVar2 = (int *)(prof_ctx + 0x30e0 + iVar1 * 4);
    break;
  case 0x33:
  case 0x36:
  case 0x3b:
  case 0x41:
  case 0x55:
  case 0x5a:
    *(int *)(prof_ctx + 0x3020) = *(int *)(prof_ctx + 0x3020) + 1;
    iVar1 = igrp_mode_bucket(*(int *)((int)rec + 0x14));
    piVar2 = (int *)(prof_ctx + 0x3020 + iVar1 * 4);
    break;
  case 0x37:
  case 0x38:
  case 0x42:
  case 0x43:
  case 0x45:
    *(int *)(prof_ctx + 0x30a0) = *(int *)(prof_ctx + 0x30a0) + 1;
    iVar1 = igrp_mode_bucket(*(int *)((int)rec + 0x14));
    piVar2 = (int *)(prof_ctx + 0x30a0 + iVar1 * 4);
    break;
  case 0x40:
  case 0x48:
  case 0x4a:
  case 0x4e:
  case 0x50:
    *(int *)(prof_ctx + 0x2fe0) = *(int *)(prof_ctx + 0x2fe0) + 1;
    iVar1 = igrp_mode_bucket(*(int *)((int)rec + 0x30));
    piVar2 = (int *)(prof_ctx + 0x2fe0 + iVar1 * 4);
  }
  *piVar2 = *piVar2 + 1;
switchD_0040139f_caseD_1:
  for (iVar1 = *(int *)((int)rec + 0x84); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
    *(int *)(prof_ctx + 0x31a0) = *(int *)(prof_ctx + 0x31a0) + 1;
    iVar3 = igrp_mode_bucket(**(int **)(iVar1 + 8));
    piVar2 = (int *)(prof_ctx + 0x31a0 + iVar3 * 4);
    *piVar2 = *piVar2 + 1;
    *(int *)(prof_ctx + 0x31e0) = *(int *)(prof_ctx + 0x31e0) + 1;
    iVar3 = igrp_mode_bucket(*(int *)(*(int *)(iVar1 + 8) + 0x1c));
    piVar2 = (int *)(prof_ctx + 0x31e0 + iVar3 * 4);
    *piVar2 = *piVar2 + 1;
  }
  return;
}


/* ==== igrp_mode_bucket @ 004016a0 ==== */

int __cdecl igrp_mode_bucket(int mode)

{
  switch(mode) {
  case 0:
  case 9:
  case 10:
  case 0xc:
  case 0xd:
  case 0xe:
    break;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 8:
    return 5;
  default:
    abort();
  }
  return mode;
}


/* ==== igrp_method_401700 @ 00401700 ==== */

void igrp_method_401700(long *param_1)

{
  int *piVar1;
  long *stat;
  int iVar2;
  char cVar3;
  long *unaff_ESI;
  long unaff_retaddr;
  long *extraout_var;
  long *flag1;
  
  stat = param_1;
  iVar2 = igrp_map_kind(param_1);
  if (*(int *)(prof_ctx + 200 + iVar2 * 4) != 0) {
    if (stat[0x21] == 0) {
      cVar3 = '\0';
    }
    else {
      cVar3 = (*(int *)(stat[0x21] + 4) != 0) + '\x01';
    }
    if (cVar3 == '\0') {
      iVar2 = (**(code **)(*(int *)(cur_itype + 0x18) + 0x10))(stat);
      piVar1 = (int *)(prof_ctx + 0x2648 + iVar2 * 4);
      *piVar1 = *piVar1 + 1;
    }
    else {
      if (cVar3 == '\x01') {
        iVar2 = (**(code **)(*(int *)(cur_itype + 0x18) + 0x10))(stat);
        piVar1 = (int *)(prof_ctx + 0x2968 + iVar2 * 4);
        *piVar1 = *piVar1 + 1;
        if (stat[4] == 0) {
          *(int *)(prof_ctx + 0x2fc8) = *(int *)(prof_ctx + 0x2fc8) + 1;
          return;
        }
        *(int *)(prof_ctx + 0x2fcc) = *(int *)(prof_ctx + 0x2fcc) + 1;
        return;
      }
      if (cVar3 == '\x02') {
        flag1 = extraout_var;
        iVar2 = (**(code **)(*(int *)(cur_itype + 0x18) + 0x10))(stat);
        *(int *)(prof_ctx + 0x2c88 + iVar2 * 4) = *(int *)(prof_ctx + 0x2c88 + iVar2 * 4) + 1;
        if (stat[4] == 0) {
          *(int *)(prof_ctx + 0x2fd0) = *(int *)(prof_ctx + 0x2fd0) + 1;
          iVar2 = stat_lmove_class(stat,(long)&stack0xfffffffc,(long)&stack0x00000004,unaff_ESI,
                                   flag1,unaff_retaddr,param_1);
          if (iVar2 == 0) {
            *(int *)(prof_ctx + 0x2fd8) = *(int *)(prof_ctx + 0x2fd8) + 1;
            return;
          }
        }
        else {
          *(int *)(prof_ctx + 0x2fd4) = *(int *)(prof_ctx + 0x2fd4) + 1;
          iVar2 = stat_lmove_class(stat,(long)&stack0xfffffffc,(long)&stack0x00000004,unaff_ESI,
                                   flag1,unaff_retaddr,param_1);
          if (iVar2 == 0) {
            *(int *)(prof_ctx + 0x2fdc) = *(int *)(prof_ctx + 0x2fdc) + 1;
            return;
          }
        }
      }
    }
  }
  return;
}


/* ==== igrp_method_401860 @ 00401860 ==== */

undefined4 igrp_method_401860(int param_1)

{
  int iVar1;
  
  if ((((((*(int *)(param_1 + 0x88) == 0x10) && (iVar1 = *(int *)(param_1 + 0x10), iVar1 != 0x2d))
        && (iVar1 != 0x2f)) && ((iVar1 != 0x2e && (iVar1 != 0x30)))) &&
      ((iVar1 != 0x11 && ((iVar1 != 0x12 && (iVar1 != 0x13)))))) && (iVar1 != 0x15)) {
    return 0;
  }
  return 1;
}


/* ==== igrp_method_4018b0 @ 004018b0 ==== */

undefined4 igrp_method_4018b0(int param_1)

{
  switch(*(undefined4 *)(param_1 + 0x10)) {
  case 0x12:
  case 0x14:
  case 0x15:
  case 0x2c:
  case 0x2e:
  case 0x30:
    return 1;
  default:
    return 0;
  }
}


/* ==== igrp_method_401910 @ 00401910 ==== */

undefined4 igrp_method_401910(int param_1)

{
  switch(*(undefined4 *)(param_1 + 0x10)) {
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0x23:
  case 0x27:
  case 0x29:
    return 0;
  default:
    return 1;
  }
}


/* ==== igrp_method_401970 @ 00401970 ==== */

undefined4 igrp_method_401970(int param_1)

{
  if ((0x24 < *(int *)(param_1 + 0x10)) && (*(int *)(param_1 + 0x10) < 0x27)) {
    return 1;
  }
  return 0;
}


/* ==== igrp_method_401990 @ 00401990 ==== */

undefined4 * igrp_method_401990(int param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  
  sprintf((char *)&DAT_004dbb88,&DAT_004ad730,8,&empty_str);
  disassemble_l1((ulong *)(param_1 + 4),&DAT_004dbb90,*(long *)(param_1 + 0x8c),
                 *(long *)(param_1 + 0x90),(void *)0x0);
  uVar2 = 0xffffffff;
  pcVar5 = &DAT_004ad72c;
  do {
    pcVar7 = pcVar5;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar7 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar7;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  iVar3 = -1;
  pcVar5 = (char *)&DAT_004dbb88;
  do {
    pcVar6 = pcVar5;
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  pcVar5 = pcVar7 + -uVar2;
  pcVar7 = pcVar6 + -1;
  for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar7 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar7 = pcVar7 + 1;
  }
  return &DAT_004dbb88;
}


/* ==== igrp_method_401a10 @ 00401a10 ==== */

undefined4 igrp_method_401a10(int param_1)

{
  switch(*(undefined4 *)(param_1 + 0x10)) {
  case 8:
  case 9:
    return 1;
  case 10:
  case 0xb:
    return 2;
  default:
    return 0;
  }
}


