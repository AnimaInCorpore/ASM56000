/* ==== prof_reset @ 00454630 ==== */

void prof_reset(void)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  
  piVar1 = (int *)(cur_sim + 0x3c30);
  if (*(int *)(cur_sim + 0x3c30) != 0) {
    prof_ctx = (undefined4 *)(cur_sim + 0x490);
    if (*piVar1 != 4) {
      prof_out_close();
    }
    chain_free((void **)(prof_ctx + 0xd3a));
    puVar3 = prof_ctx;
    for (iVar2 = 0xde9; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    *piVar1 = 0;
  }
  return;
}


/* ==== prof_record_insn @ 00454690 ==== */

int __cdecl prof_record_insn(void *insn)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  int iVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  void *extraout_EAX;
  uint uVar5;
  int iVar6;
  void *src_line;
  undefined3 extraout_var_01;
  
  iVar6 = cur_sim;
  iVar4 = _setjmp3(&prof_jmpbuf,0);
  if (iVar4 != 0) {
    return 0;
  }
  prof_ctx = iVar6 + 0x490;
  if ((*(byte *)(iVar6 + 0x3970) & 0x10) == 0) {
    if (*(int *)(iVar6 + 0x3c30) == 1) {
      *(undefined4 *)(iVar6 + 0x3c30) = 2;
    }
    cVar3 = prof_find_instr(*(ulong *)insn,insn,0);
    src_line = (void *)CONCAT31(extraout_var,cVar3);
    if (((src_line == (void *)0x0) || (*(int *)((int)src_line + 4) != *(int *)((int)insn + 4))) ||
       (((*(byte *)((int)src_line + 0xc) & 4) != 0 &&
        (*(int *)((int)src_line + 8) != *(int *)((int)insn + 8))))) {
      cVar3 = prof_find_instr(*(ulong *)insn,insn,1);
      src_line = (void *)CONCAT31(extraout_var_00,cVar3);
    }
    if (src_line == (void *)0x0) {
      prof_add_instr(*(ulong *)insn,3,*(ulong *)insn,(void *)0x0);
      src_line = extraout_EAX;
      if (extraout_EAX == (void *)0x0) {
        return 0;
      }
    }
    if (*(int *)((int)src_line + 0xc0) == 0) {
      *(undefined4 *)((int)src_line + 0x8c) = *(undefined4 *)((int)insn + 0x8c);
      *(undefined4 *)((int)src_line + 0x90) = *(undefined4 *)((int)insn + 0x90);
    }
    iVar4 = (**(code **)(*(int *)(cur_itype + 0x18) + 0x24))(insn);
    uVar5 = (uint)(*(int *)((int)insn + 0xe8) != 0);
    *(int *)(prof_ctx + 0x34e4) = *(int *)((int)insn + 0xe0) - *(int *)((int)insn + 0xdc);
    cg_note_pc_change(src_line,iVar4,uVar5,*(int *)(prof_ctx + 0x34e4));
    *(undefined4 *)(prof_ctx + 0x34e4) = *(undefined4 *)((int)insn + 0xe0);
    *(undefined4 *)((int)src_line + 0xb4) = *(undefined4 *)(prof_ctx + 0x34e4);
    *(int *)((int)src_line + 0xc0) = *(int *)((int)src_line + 0xc0) + 1;
    if ((iVar4 == 1) && (uVar5 == 1)) {
      *(int *)((int)src_line + 0xc4) = *(int *)((int)src_line + 0xc4) + 1;
    }
    *(int *)((int)src_line + 0xcc) = *(int *)((int)src_line + 0xcc) + *(int *)((int)insn + 0xdc);
    *(int *)((int)src_line + 0xd0) = *(int *)((int)src_line + 0xd0) + *(int *)((int)insn + 0xe4);
    iVar4 = (**(code **)(*(int *)(cur_itype + 0x18) + 0x10))(insn);
    if (*(int *)(iVar6 + 0x470) == 0) {
      piVar1 = (int *)(prof_ctx + 0x19c8 + iVar4 * 4);
      *piVar1 = *piVar1 + 1;
    }
    else {
      uVar5 = *(uint *)(iVar6 + 0x474);
      uVar2 = *(uint *)(prof_ctx + 5000 + iVar4 * 4);
      *(int *)((int)src_line + 200) = *(int *)((int)src_line + 200) + 1;
      if (uVar2 < uVar5) {
        *(uint *)(prof_ctx + 5000 + iVar4 * 4) = uVar5;
        *(undefined4 *)(prof_ctx + 0x16a8 + iVar4 * 4) = 1;
      }
      else if (uVar5 == uVar2) {
        piVar1 = (int *)(prof_ctx + 0x16a8 + iVar4 * 4);
        *piVar1 = *piVar1 + 1;
      }
    }
    *(int *)(prof_ctx + 0x708 + iVar4 * 4) = *(int *)(prof_ctx + 0x708 + iVar4 * 4) + 1;
    *(int *)(prof_ctx + 0xb4) = *(int *)(prof_ctx + 0xb4) + 1;
    *(int *)(prof_ctx + 0xc0) = *(int *)(prof_ctx + 0xc0) + *(int *)((int)insn + 0xe4);
    *(uint *)(prof_ctx + 0xac) =
         *(int *)(prof_ctx + 0xac) + ((*(uint *)((int)insn + 0xc) & 4) != 0) + 1;
    (**(code **)(*(int *)(cur_itype + 0x18) + 0x20))(insn);
    (**(code **)(*(int *)(cur_itype + 0x18) + 0x1c))(insn);
    prof_flush_refs(insn);
    if (*(ulong **)((int)insn + 0xf0) != (ulong *)0x0) {
      cVar3 = prof_find_instr(**(ulong **)((int)insn + 0xf0),(void *)0x0,0);
      iVar6 = CONCAT31(extraout_var_01,cVar3);
      if (iVar6 == 0) {
        return 0;
      }
      *(int *)(iVar6 + 0xd4) = *(int *)(iVar6 + 0xd4) + *(int *)(*(int *)((int)insn + 0xf0) + 8);
    }
    *(undefined4 *)(prof_ctx + 0x37a0) = 3;
  }
  return 1;
}


/* ==== prof_flush_refs @ 00454990 ==== */

void __cdecl prof_flush_refs(void *insn)

{
  int *piVar1;
  char cVar2;
  int extraout_EAX;
  int extraout_EAX_00;
  undefined3 extraout_var;
  int iVar3;
  undefined3 extraout_var_01;
  int iVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  char *local_e4;
  int local_e0;
  int local_dc [55];
  undefined3 extraout_var_00;
  
  piVar7 = (int *)((int)insn + 0x104);
  local_e0 = 0x14;
  do {
    if (piVar7[-4] != 0) {
      prof_del_line(piVar7[-4],piVar7[-2]);
      iVar3 = extraout_EAX;
      if (extraout_EAX == 0) {
        prof_add_line(piVar7[-4],piVar7[-2]);
        iVar3 = extraout_EAX_00;
      }
      *(int *)(iVar3 + 0x10 + *piVar7 * 4) = *(int *)(iVar3 + 0x10 + *piVar7 * 4) + 1;
      piVar1 = (int *)(prof_ctx + 0x2fa8 + (piVar7[-3] + *piVar7 * 4) * 4);
      *piVar1 = *piVar1 + 1;
      if (*piVar7 == 0) {
        *(int *)(prof_ctx + 0x14 + *(int *)(prof_ctx + 0x54) * 8) = piVar7[-4];
        *(int *)(prof_ctx + 0x18 + *(int *)(prof_ctx + 0x54) * 8) = piVar7[-2];
        *(int *)(prof_ctx + 0x54) = *(int *)(prof_ctx + 0x54) + 1;
        uVar6 = (int)*(uint *)(prof_ctx + 0x54) >> 0x1f;
        *(uint *)(prof_ctx + 0x54) =
             ((*(uint *)(prof_ctx + 0x54) ^ uVar6) - uVar6 & 7 ^ uVar6) - uVar6;
      }
      else {
        if ((*(byte *)(iVar3 + 0xc) & 4) != 0) {
          piVar1 = (int *)(prof_ctx + 0x94 + piVar7[-4] * 4);
          *piVar1 = *piVar1 + 1;
          *(uint *)(iVar3 + 0xc) = *(uint *)(iVar3 + 0xc) & 0xfffffffb;
        }
        if (piVar7[-4] == 3) {
          local_dc[0] = piVar7[-2];
          cVar2 = avl_iter(*(void **)(prof_ctx + 8),(char *)local_dc,local_dc);
          local_e4 = (char *)CONCAT31(extraout_var,cVar2);
          cVar2 = avl_iter((void *)0x0,local_e4,(void *)0x0);
          iVar3 = CONCAT31(extraout_var_00,cVar2);
          while (iVar3 != 0) {
            iVar4 = *(int *)(prof_ctx + 0x54);
            do {
              iVar5 = iVar4 + -1;
              if (iVar4 == 0) {
                iVar5 = 7;
              }
              if (((*(int *)(prof_ctx + 0x18 + iVar5 * 8) == *(int *)(iVar3 + 0xb0)) &&
                  (*(int *)(prof_ctx + 0x14 + iVar5 * 8) == *(int *)(iVar3 + 0xac))) &&
                 (*(int *)(iVar3 + 0xac) != 0)) {
                *(undefined4 *)(iVar3 + 0xb4) = *(undefined4 *)(prof_ctx + 0x34e4);
                dsp_free(local_e4);
                local_e4 = (char *)0x0;
                break;
              }
              iVar4 = iVar5;
            } while (iVar5 != *(int *)(prof_ctx + 0x54));
            cVar2 = avl_iter((void *)0x0,local_e4,(void *)0x0);
            iVar3 = CONCAT31(extraout_var_01,cVar2);
          }
        }
      }
      piVar7[-4] = 0;
    }
    piVar7 = piVar7 + 5;
    local_e0 = local_e0 + -1;
    if (local_e0 == 0) {
      return;
    }
  } while( true );
}


/* ==== prof_start @ 00454b50 ==== */

void __cdecl prof_start(char *symfile,char *outfile,char *title)

{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined4 uVar4;
  undefined3 extraout_var_01;
  
  iVar1 = cur_sim;
  iVar3 = _setjmp3(&prof_jmpbuf,0);
  if (iVar3 == 0) {
    prof_reset();
    prof_ctx = iVar1 + 0x490;
    pool_init((int *)(iVar1 + 0x3978),20000);
    *(undefined4 *)(prof_ctx + 0x37a0) = 1;
    *(undefined4 *)(prof_ctx + 0x3504) = 0xffffffff;
    cVar2 = pool_strdup(prof_ctx + 0x34e8,title);
    *(uint *)(prof_ctx + 0x68) = CONCAT31(extraout_var,cVar2);
    if (symfile == (char *)0x0) {
      uVar4 = 0;
    }
    else {
      cVar2 = pool_strdup(prof_ctx + 0x34e8,symfile);
      uVar4 = CONCAT31(extraout_var_00,cVar2);
    }
    *(undefined4 *)(prof_ctx + 0x60) = uVar4;
    if (outfile != (char *)0x0) {
      cVar2 = pool_strdup(prof_ctx + 0x34e8,outfile);
      *(uint *)(prof_ctx + 0x5c) = CONCAT31(extraout_var_01,cVar2);
      prof_load_cld();
      return;
    }
    *(char **)(prof_ctx + 0x5c) = s_metrics_log_004d1cac;
    prof_load_cld();
  }
  return;
}


/* ==== prof_report @ 00454c50 ==== */

void __cdecl prof_report(long arg)

{
  int iVar1;
  int iVar2;
  
  iVar2 = cur_sim;
  iVar1 = _setjmp3(&prof_jmpbuf,0);
  if (iVar1 == 0) {
    prof_ctx = iVar2 + 0x490;
    *(long *)(iVar2 + 0x54c) = arg;
    prof_out_open(*(char **)(prof_ctx + 0x60),*(char **)(prof_ctx + 0x5c),
                  *(char **)(prof_ctx + 0x68));
    iVar2 = subr_profile_finish();
    *(int *)(prof_ctx + 0xb8) = iVar2;
    if (((byte)*(undefined4 *)(prof_ctx + 0x34e0) & 0x10) == 0x10) {
      prof_error(2,PTR_s_Profiler_file_not_generated_004d3be8);
      prof_reset();
      return;
    }
    if (*(int *)(prof_ctx + 0x37a0) == 1) {
      prof_printf(s_No_instructions_executed___Stati_004d1cb8);
      prof_basic_profile();
      prof_occurrence_reports();
      prof_moves_breakdown();
      prof_reset();
      return;
    }
    prof_basic_profile();
    prof_data_mem_refs();
    prof_symbol_mem_refs();
    prof_occurrence_reports();
    prof_moves_breakdown();
    prof_addr_mode_breakdown();
    subr_report();
    prof_coverage_report();
    prof_reset();
  }
  return;
}


/* ==== prof_coverage_report @ 00454d50 ==== */

int prof_coverage_report(void)

{
  char cVar1;
  int iVar2;
  undefined4 extraout_EAX;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined4 extraout_EAX_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  int unaff_EBP;
  int unaff_retaddr;
  
  if (((byte)*(undefined4 *)(prof_ctx + 0x34e0) & 1) == 1) {
    prof_printf(s_Coff_file_did_not_read_properly___004d1e54);
    return 1;
  }
  prof_heading(s_Code_Coverage_Report_004d1e3c);
  ps_font(0,2,6);
  prof_printf(&DAT_004d1e2c,0x14);
  prof_printf(&DAT_004d1e1c,0x3e);
  prof_printf(&DAT_004d1e08,0x66);
  prof_printf(&DAT_004d1df4,0x8a);
  prof_printf(&DAT_004d1ddc,200);
  prof_printf(&DAT_004d1dc4,0x104);
  ps_font(6,unaff_EBP,unaff_retaddr);
  prof_printf(&DAT_004d1d70,&DAT_004d1d90,s_address_004d1d98,&DAT_004d1da0,s_cyc_stall_004d1da8,
              s_passes__004d1db4,s_source_004d1dbc);
  prof_printf(&DAT_004d1d48,&empty_str,&empty_str,&empty_str,&empty_str,s_all_cond_004d1d64);
  prof_printf(&DAT_004ad72c);
  iVar2 = _setjmp3(&prof_jmpbuf,0);
  if (iVar2 == 0) {
    if (*(int *)(prof_ctx + 0x3504) < 0) {
      avl_copy_sorted(*(void **)(prof_ctx + 8),2,1);
      *(undefined4 *)(prof_ctx + 8) = extraout_EAX;
      cVar1 = avl_iter(*(void **)(prof_ctx + 8),(char *)0x0,(void *)0x0);
      prof_sym_list = (char *)CONCAT31(extraout_var,cVar1);
      cVar1 = avl_iter((void *)0x0,prof_sym_list,(void *)0x0);
      prof_sym_cur = (long *)CONCAT31(extraout_var_00,cVar1);
      prof_cov_by_source();
    }
    else {
      avl_copy_sorted(*(void **)(prof_ctx + 8),3,1);
      *(undefined4 *)(prof_ctx + 8) = extraout_EAX_00;
      cVar1 = avl_iter(*(void **)(prof_ctx + 8),(char *)0x0,(void *)0x0);
      prof_sym_list = (char *)CONCAT31(extraout_var_01,cVar1);
      cVar1 = avl_iter((void *)0x0,prof_sym_list,(void *)0x0);
      prof_sym_cur = (long *)CONCAT31(extraout_var_02,cVar1);
      prof_cov_source_file(*(char **)(prof_ctx + 0x58));
    }
    if ((prof_sym_cur != (long *)0x0) && ((prof_sym_cur[3] & 0x1000U) != 0)) {
      prof_printf(s_Note___new_instructions_were_cre_004d1cec);
      while (prof_sym_cur != (long *)0x0) {
        (**(code **)(*(int *)(cur_itype + 0x18) + 0x38))(prof_sym_cur);
        prof_print_cov_line(*prof_sym_cur,1,prof_sym_cur + 0x30,1);
        cVar1 = avl_iter((void *)0x0,prof_sym_list,(void *)0x0);
        prof_sym_cur = (long *)CONCAT31(extraout_var_03,cVar1);
      }
    }
    return 0;
  }
  prof_printf(s_Code_coverage_report_aborted_004d1d24);
  return 1;
}


/* ==== prof_print_cov_line @ 00454fc0 ==== */

void __cdecl prof_print_cov_line(long addr,int is_addr,void *counts,int kind)

{
  undefined4 in_stack_00000014;
  int in_stack_00000018;
  char *pcVar1;
  undefined1 *puVar2;
  
  prof_printf(&DAT_004d1f08,0x14);
  if (kind == 1) {
    prof_printf(&DAT_004d1f04,&empty_str);
  }
  else {
    prof_printf(s___04u__2s_004d1ef8,in_stack_00000014,&empty_str);
  }
  if (counts == (void *)0x0) {
    prof_printf(&DAT_004d1e98);
  }
  else {
    prof_printf(&DAT_004d1f08,0x3e);
    if (is_addr == 1) {
      prof_printf(s__06lX_004d1ef0,addr);
    }
    else {
      prof_printf(s_<join>_004d1ee8);
    }
    prof_printf(&DAT_004d1ee4,&empty_str);
    prof_printf(&DAT_004d1f08,0x66);
    puVar2 = *(undefined1 **)((int)counts + 0x14);
    if (puVar2 == (undefined1 *)0x0) {
      puVar2 = &empty_str;
      pcVar1 = &DAT_004d1ed0;
    }
    else {
      pcVar1 = &DAT_004d1ed8;
    }
    prof_printf(pcVar1,puVar2);
    prof_printf(&DAT_004d1ec8,&empty_str);
    prof_printf(&DAT_004d1f08,0x8a);
    prof_printf(&DAT_004d1ed8,*(undefined4 *)((int)counts + 0xc));
    puVar2 = *(undefined1 **)((int)counts + 0x10);
    if (puVar2 == (undefined1 *)0x0) {
      puVar2 = &empty_str;
      pcVar1 = &DAT_004d1eb8;
    }
    else {
      pcVar1 = &DAT_004d1ebc;
    }
    prof_printf(pcVar1,puVar2);
    prof_printf(&DAT_004d1eb4,&empty_str);
    prof_printf(&DAT_004d1f08,200);
    prof_printf(&DAT_004d1eac,*(undefined4 *)counts);
    puVar2 = *(undefined1 **)((int)counts + 4);
    if (puVar2 == (undefined1 *)0x0) {
      puVar2 = &empty_str;
      pcVar1 = &DAT_004d1eb8;
    }
    else {
      pcVar1 = &DAT_004d1ea0;
    }
    prof_printf(pcVar1,puVar2);
    prof_printf(&DAT_004d1ee4,&empty_str);
  }
  prof_printf(&DAT_004d1f08,0x104);
  if (kind == 1) {
    prof_printf(&DAT_004d1e94);
    in_stack_00000018 = in_stack_00000018 + 2;
  }
  prof_printf(&DAT_004cb15c,in_stack_00000018);
  return;
}


/* ==== prof_cov_by_source @ 004551a0 ==== */

void prof_cov_by_source(void)

{
  byte bVar1;
  char cVar2;
  undefined3 extraout_var;
  int iVar3;
  ulong uVar4;
  int iVar5;
  byte *pbVar6;
  int *piVar7;
  byte *pbVar8;
  bool bVar9;
  int local_38;
  char *local_34;
  ulong local_30;
  byte *local_2c;
  undefined4 local_28;
  ulong *local_24;
  long *local_20;
  int local_1c [4];
  int iStack_c;
  int iStack_8;
  
  local_30 = 0xffffffff;
  local_2c = &empty_str;
  local_28 = 0;
  local_38 = 0;
  do {
    if ((prof_sym_cur == (long *)0x0) ||
       (iVar5 = 0, local_20 = prof_sym_cur, (prof_sym_cur[3] & 0x1000U) != 0)) {
      src_get_line(&local_28,&local_38,(char **)&local_2c,&local_30,&DAT_004d1f10,0xffffffff,
                   &local_34);
      return;
    }
    local_24 = (ulong *)(prof_sym_cur + 0x2a);
    src_get_line(&local_28,&local_38,(char **)&local_2c,&local_30,(char *)prof_sym_cur[0x29],
                 *local_24,&local_34);
    if (local_30 == 0xffffffff) {
      src_get_line(&local_28,&local_38,(char **)&local_2c,&local_30,(char *)prof_sym_cur[0x29],
                   prof_sym_cur[0x2a],&local_34);
    }
    if (local_38 == 1) {
      local_34 = (char *)(**(code **)(*(int *)(cur_itype + 0x18) + 0x38))(prof_sym_cur);
    }
    piVar7 = local_1c;
    for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar7 = 0;
      piVar7 = piVar7 + 1;
    }
    while (prof_sym_cur != (long *)0x0) {
      pbVar6 = (byte *)prof_sym_cur[0x29];
      pbVar8 = local_2c;
      do {
        bVar1 = *pbVar6;
        bVar9 = bVar1 < *pbVar8;
        if (bVar1 != *pbVar8) {
LAB_004552c0:
          iVar3 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
          goto LAB_004552c5;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar6[1];
        bVar9 = bVar1 < pbVar8[1];
        if (bVar1 != pbVar8[1]) goto LAB_004552c0;
        pbVar6 = pbVar6 + 2;
        pbVar8 = pbVar8 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_004552c5:
      if (iVar3 != 0) break;
      if (prof_sym_cur == (long *)0x0) {
        uVar4 = 0xffffffff;
      }
      else {
        uVar4 = prof_sym_cur[0x2a];
      }
      if (uVar4 != *local_24) break;
      local_1c[0] = local_1c[0] + prof_sym_cur[0x30];
      local_1c[1] = local_1c[1] + prof_sym_cur[0x31];
      iStack_c = iStack_c + prof_sym_cur[0x34];
      local_1c[3] = local_1c[3] + prof_sym_cur[0x33];
      iStack_8 = iStack_8 + prof_sym_cur[0x35];
      iVar5 = iVar5 + 1;
      cVar2 = avl_iter((void *)0x0,prof_sym_list,(void *)0x0);
      prof_sym_cur = (long *)CONCAT31(extraout_var,cVar2);
    }
    prof_print_cov_line(*local_20,(uint)(iVar5 == 1),local_1c,local_38);
  } while( true );
}


/* ==== src_get_line @ 004553c0 ==== */

char __cdecl
src_get_line(void *pfile,int *pfailed,char **pname,ulong *pline,char *name,ulong want,char **ptext)

{
  byte bVar1;
  ulong uVar2;
  char cVar3;
  byte *pbVar4;
  int iVar5;
  undefined4 extraout_EAX;
  char *pcVar6;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  byte *pbVar7;
  bool bVar8;
  
  pbVar4 = (byte *)*pname;
  pbVar7 = (byte *)name;
  do {
    bVar1 = *pbVar4;
    bVar8 = bVar1 < *pbVar7;
    if (bVar1 != *pbVar7) {
LAB_004553f4:
      iVar5 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
      goto LAB_004553f9;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar4[1];
    bVar8 = bVar1 < pbVar7[1];
    if (bVar1 != pbVar7[1]) goto LAB_004553f4;
    pbVar4 = pbVar4 + 2;
    pbVar7 = pbVar7 + 2;
  } while (bVar1 != 0);
  iVar5 = 0;
LAB_004553f9:
  if (iVar5 != 0) {
    if (*pline == 0xffffffff) {
      *pname = name;
      pbVar4 = &DAT_004d1f10;
      do {
        bVar1 = *name;
        bVar8 = bVar1 < *pbVar4;
        if (bVar1 != *pbVar4) {
LAB_00455437:
          iVar5 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_0045543c;
        }
        if (bVar1 == 0) break;
        bVar1 = name[1];
        bVar8 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_00455437;
        name = name + 2;
        pbVar4 = pbVar4 + 2;
      } while (bVar1 != 0);
      iVar5 = 0;
LAB_0045543c:
      if (iVar5 == 0) {
        return '\0';
      }
      *pfailed = 0;
      *(undefined4 *)pfile = 0;
    }
    else {
      want = 0xffffffff;
    }
  }
  if ((*(int *)pfile != 0) || (*pfailed != 0)) goto LAB_00455543;
  iVar5 = src_is_c_file(*pname);
  if (iVar5 == 0) {
    prof_fopen(*pname,&DAT_004c5574,(char *)0x0,3);
    *(undefined4 *)pfile = extraout_EAX;
  }
  else {
    prof_error(3,PTR_s_File__s__C_sources_not_supported_004d3bbc,*pname);
    *(undefined4 *)pfile = 0;
  }
  if (*(int *)pfile == 0) {
LAB_0045550b:
    *pfailed = 1;
    if (*(int *)pfile != 0) goto LAB_0045551b;
    pcVar6 = s_RECONSTRUCT_004d1f48;
  }
  else {
    if (*(int *)(prof_ctx + 100) < prof_file_size) {
      prof_error(3,PTR_s_Source_file__s_more_recent_than_e_004d3bc0,*pname);
      fclose(*(void **)pfile);
      *(undefined4 *)pfile = 0;
    }
    if (*(int *)pfile == 0) goto LAB_0045550b;
LAB_0045551b:
    pcVar6 = s_START_004d1f54;
  }
  prof_printf(s_________s_file___s__004d1f30,pcVar6,*pname);
  *pline = 1;
LAB_00455543:
  if (*pline <= want) {
    while (((*pfailed != 1 && ((*(byte *)((int)*(void **)pfile + 0xc) & 0x10) == 0)) &&
           (cVar3 = fgets(&src_line_buf,400,*(void **)pfile), CONCAT31(extraout_var,cVar3) != 0))) {
      if (*pline == want) {
        *pline = *pline + 1;
        *ptext = &src_line_buf;
        return '\0';
      }
      prof_print_cov_line(0,0,(void *)0x0,0);
      if ((-1 < *(int *)(prof_ctx + 0x3504)) &&
         (cVar3 = src_include_name(&src_line_buf), CONCAT31(extraout_var_00,cVar3) != 0)) {
        *pline = *pline + 1;
        return cVar3;
      }
      uVar2 = *pline;
      *pline = uVar2 + 1;
      if (want < uVar2 + 1) {
        return '\0';
      }
    }
    if ((want == 0xffffffff) && ((*pfailed == 1 || ((*(byte *)(*(int *)pfile + 0xc) & 0x10) != 0))))
    {
      *pline = 0xffffffff;
      prof_printf(s________END_file___s__004d1f18,*pname);
      if (*(void **)pfile != (void *)0x0) {
        fclose(*(void **)pfile);
      }
      *(undefined4 *)pfile = 0;
      *ptext = (char *)0x0;
      return '\0';
    }
    if (*pfailed == 0) {
      *pfailed = 1;
      prof_error(3,PTR_s_Failed_to_read_from_file__s_004d3bcc,*pname);
      *pline = want + 1;
    }
    *ptext = (char *)0x0;
  }
  return '\0';
}


/* ==== src_include_name @ 00455670 ==== */

char __cdecl src_include_name(char *line)

{
  char cVar1;
  uint uVar2;
  undefined3 extraout_var;
  int iVar3;
  char *pcVar4;
  undefined3 extraout_var_01;
  char *s;
  undefined3 extraout_var_00;
  
  if (line == (char *)0x0) {
    return '\0';
  }
  if (__mb_cur_max < 2) {
    uVar2 = *(ushort *)(_pctype + *line * 2) & 0x103;
  }
  else {
    uVar2 = _isctype((int)*line,0x103);
  }
  if (uVar2 != 0) {
    cVar1 = strpbrk(line,&DAT_004d1f68);
    line = (char *)CONCAT31(extraout_var,cVar1);
    if (line == (char *)0x0) {
      return cVar1;
    }
  }
  for (; (*line == ' ' || (*line == '\t')); line = line + 1) {
  }
  iVar3 = strncmp(line,s_include_004d1f60,7);
  if (iVar3 != 0) {
    return '\0';
  }
  cVar1 = strpbrk(line + 7,&DAT_004d1f5c);
  pcVar4 = (char *)CONCAT31(extraout_var_00,cVar1);
  if (pcVar4 == (char *)0x0) {
    return cVar1;
  }
  s = pcVar4 + 1;
  cVar1 = strchr(s,(int)*pcVar4);
  if (CONCAT31(extraout_var_01,cVar1) == 0) {
    return cVar1;
  }
  uVar2 = CONCAT31(extraout_var_01,cVar1) - (int)s;
  strncpy(&src_include_buf,s,uVar2);
  (&src_include_buf)[uVar2] = 0;
  return -0x50;
}


/* ==== src_is_c_file @ 00455750 ==== */

int __cdecl src_is_c_file(char *name)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  
  uVar2 = 0xffffffff;
  pcVar4 = name;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  iVar3 = ~uVar2 - 2;
  if (0 < iVar3) {
    iVar3 = toupper((int)name[iVar3]);
    if ((iVar3 == 0x43) && (name[~uVar2 - 3] == '.')) {
      return 1;
    }
  }
  return 0;
}


/* ==== prof_cov_source_file @ 004557a0 ==== */

void __cdecl prof_cov_source_file(char *name)

{
  byte bVar1;
  long *plVar2;
  char cVar3;
  undefined3 extraout_var;
  char *pcVar4;
  char *pcVar5;
  undefined3 extraout_var_00;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  int iVar9;
  long lVar10;
  int iVar11;
  byte *pbVar12;
  bool bVar13;
  char *local_90;
  int local_8c;
  ulong local_88;
  undefined4 local_84;
  char local_80 [128];
  
  local_88 = 0;
  local_84 = 0;
  local_8c = 0;
  do {
    while( true ) {
      if (prof_sym_cur == (long *)0x0) {
        src_get_line(&local_84,&local_8c,&name,&local_88,&DAT_004d1f10,0xffffffff,&local_90);
        return;
      }
      if ((prof_sym_cur[3] & 0x1000U) != 0) {
        return;
      }
      cVar3 = src_get_line(&local_84,&local_8c,&name,&local_88,(char *)prof_sym_cur[0x29],
                           prof_sym_cur[0x2a],&local_90);
      plVar2 = prof_sym_cur;
      if ((char *)CONCAT31(extraout_var,cVar3) != (char *)0x0) break;
      if (local_88 == 0xffffffff) {
        return;
      }
      iVar11 = 0;
      pcVar4 = local_90;
      if (local_8c == 1) {
        pcVar4 = (char *)(**(code **)(*(int *)(cur_itype + 0x18) + 0x38))(prof_sym_cur);
      }
      while (local_90 = pcVar4, prof_sym_cur != (long *)0x0) {
        pbVar8 = (byte *)prof_sym_cur[0x29];
        pbVar12 = (byte *)name;
        do {
          bVar1 = *pbVar8;
          bVar13 = bVar1 < *pbVar12;
          if (bVar1 != *pbVar12) {
LAB_004558b7:
            iVar9 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
            goto LAB_004558bc;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar8[1];
          bVar13 = bVar1 < pbVar12[1];
          if (bVar1 != pbVar12[1]) goto LAB_004558b7;
          pbVar8 = pbVar8 + 2;
          pbVar12 = pbVar12 + 2;
        } while (bVar1 != 0);
        iVar9 = 0;
LAB_004558bc:
        if (iVar9 != 0) break;
        if (prof_sym_cur == (long *)0x0) {
          lVar10 = -1;
        }
        else {
          lVar10 = prof_sym_cur[0x2a];
        }
        if (lVar10 != plVar2[0x2a]) break;
        if (((*(int *)(prof_ctx + 0x3504) == 0) || (iVar11 <= *(int *)(prof_ctx + 0x3504))) &&
           (0 < iVar11)) {
          if (iVar11 == 1) {
            pcVar5 = &DAT_004c5890;
            if (local_8c != 1) {
              pcVar5 = pcVar4;
            }
            prof_print_cov_line(0,0,(void *)0x0,0,plVar2[0x2a],pcVar5);
          }
          (**(code **)(*(int *)(cur_itype + 0x18) + 0x38))(plVar2);
          prof_print_cov_line(*plVar2,1,plVar2 + 0x30,1);
        }
        plVar2 = prof_sym_cur;
        iVar11 = iVar11 + 1;
        cVar3 = avl_iter((void *)0x0,prof_sym_list,(void *)0x0);
        pcVar4 = local_90;
        prof_sym_cur = (long *)CONCAT31(extraout_var_00,cVar3);
      }
      if ((*(int *)(prof_ctx + 0x3504) == 0) || (iVar11 <= *(int *)(prof_ctx + 0x3504))) {
        if (1 < iVar11) {
          pcVar4 = (char *)(**(code **)(*(int *)(cur_itype + 0x18) + 0x38))(plVar2);
        }
        prof_print_cov_line(*plVar2,1,plVar2 + 0x30,(uint)(1 < iVar11),plVar2[0x2a],pcVar4);
      }
      else {
        prof_printf(&DAT_004d1f08,0x3e);
        prof_printf(&DAT_004d1f78,&empty_str);
        prof_printf(s_<____>_2s_004d1f6c,&empty_str);
      }
    }
    uVar6 = 0xffffffff;
    pcVar4 = (char *)CONCAT31(extraout_var,cVar3);
    do {
      pcVar5 = pcVar4;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar5 = pcVar4 + 1;
      cVar3 = *pcVar4;
      pcVar4 = pcVar5;
    } while (cVar3 != '\0');
    uVar6 = ~uVar6;
    pcVar4 = pcVar5 + -uVar6;
    pcVar5 = local_80;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      pcVar5 = pcVar5 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar5 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      pcVar5 = pcVar5 + 1;
    }
    prof_cov_source_file(local_80);
  } while( true );
}


/* ==== prof_symbol_mem_refs @ 00455a50 ==== */

void prof_symbol_mem_refs(void)

{
  int iVar1;
  bool bVar2;
  char cVar3;
  char cVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int *piVar5;
  undefined3 extraout_var_02;
  uint *puVar6;
  int iVar7;
  int unaff_ESI;
  int iVar8;
  int unaff_EDI;
  uint local_8 [2];
  void *sym;
  
  local_8[0] = 0;
  local_8[1] = 0;
  bVar2 = false;
  cVar3 = avl_iter(*(void **)(prof_ctx + 0xc),(char *)0x0,(void *)0x0);
  cVar4 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar3),(void *)0x0);
  sym = (void *)CONCAT31(extraout_var_00,cVar4);
  while (sym != (void *)0x0) {
    if ((*(int *)((int)sym + 0xc) == 3) &&
       ((*(int *)((int)sym + 0x10) != 3 ||
        (cVar4 = prof_find_instr(*(ulong *)((int)sym + 0x14),(void *)0x0,2),
        CONCAT31(extraout_var_01,cVar4) == 0)))) {
      if (!bVar2) {
        bVar2 = true;
        puVar6 = local_8;
        piVar5 = (int *)(prof_ctx + 0x2fa8);
        iVar8 = 2;
        do {
          iVar7 = 4;
          do {
            iVar1 = *piVar5;
            piVar5 = piVar5 + 1;
            *puVar6 = *puVar6 + iVar1;
            iVar7 = iVar7 + -1;
          } while (iVar7 != 0);
          puVar6 = puVar6 + 1;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
        prof_heading(s_Symbol_memory_references_004d1fe4);
        ps_font(2,4,unaff_EDI);
        prof_printf(&DAT_004d1fc8,0x16,s_symbol_offset_004d1fd4);
        iVar8 = 5;
        do {
          prof_printf(s__5s_5s_004d1fc0,&DAT_004c5574,&DAT_004c6b48);
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
        ps_font(6,unaff_EDI,unaff_ESI);
        prof_printf(&DAT_004d1fb4,0x54);
      }
      prof_symbol_mem_refs_sym(sym,(long *)local_8);
    }
    cVar4 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar3),(void *)0x0);
    sym = (void *)CONCAT31(extraout_var_02,cVar4);
  }
  if ((0 < (int)local_8[0]) || (0 < (int)local_8[1])) {
    prof_printf(s_unnamed_memory_references____ld_r_004d1f80,((int)local_8[0] < 1) - 1 & local_8[0],
                ((int)local_8[1] < 1) - 1 & local_8[1]);
  }
  return;
}


/* ==== prof_symbol_mem_refs_sym @ 00455bd0 ==== */

void __cdecl prof_symbol_mem_refs_sym(void *sym,long *unnamed)

{
  char cVar1;
  byte bVar2;
  ulong file_idx;
  uint uVar3;
  bool bVar4;
  int extraout_EAX;
  byte *pbVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  uint uVar12;
  char *pcVar13;
  int iVar14;
  char *pcVar15;
  bool bVar16;
  ulong local_35c;
  char local_33c [27];
  char acStack_321 [401];
  byte local_190 [400];
  
  file_idx = *(ulong *)((int)sym + 0x10);
  uVar3 = *(uint *)((int)sym + 0x14);
  uVar12 = *(uint *)((int)sym + 0x18);
  bVar4 = false;
  iVar10 = 1;
  prof_func_fullname(local_33c,sym,0x16);
  local_190[0] = 0;
  uVar7 = uVar3;
  local_35c = uVar3;
  if (99 < uVar12 - uVar3) {
    uVar12 = uVar3 + 99;
  }
joined_r0x00455c33:
  do {
    if (uVar12 <= uVar7) {
      return;
    }
    iVar10 = 1 - iVar10;
    iVar9 = 0;
    pcVar15 = acStack_321 + iVar10 * 400 + 1;
    *pcVar15 = '\0';
    uVar6 = uVar7;
    do {
      if (uVar12 <= uVar6) break;
      uVar6 = 0xffffffff;
      pcVar13 = pcVar15;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        cVar1 = *pcVar13;
        pcVar13 = pcVar13 + 1;
      } while (cVar1 != '\0');
      iVar14 = 0;
      iVar8 = 0;
      prof_del_line(file_idx,local_35c);
      if (extraout_EAX != 0) {
        iVar14 = *(int *)(extraout_EAX + 0x10);
        iVar8 = *(int *)(extraout_EAX + 0x14);
        *unnamed = *unnamed - iVar14;
        unnamed[1] = unnamed[1] - iVar8;
      }
      sprintf(acStack_321 + iVar10 * 400 + ~uVar6,&DAT_004d2018,
              (-(uint)(iVar9 != 0) & 0xffffffa4) + 0x7c,iVar14,iVar8);
      iVar9 = iVar9 + 1;
      uVar6 = local_35c + 1;
      local_35c = uVar6;
    } while (iVar9 < 5);
    pbVar11 = local_190;
    pbVar5 = (byte *)(acStack_321 + 1);
    do {
      bVar2 = *pbVar5;
      bVar16 = bVar2 < *pbVar11;
      if (bVar2 != *pbVar11) {
LAB_00455d1e:
        iVar9 = (1 - (uint)bVar16) - (uint)(bVar16 != 0);
        goto LAB_00455d23;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar5[1];
      bVar16 = bVar2 < pbVar11[1];
      if (bVar2 != pbVar11[1]) goto LAB_00455d1e;
      pbVar5 = pbVar5 + 2;
      pbVar11 = pbVar11 + 2;
    } while (bVar2 != 0);
    iVar9 = 0;
LAB_00455d23:
    if ((iVar9 == 0) && (uVar6 < uVar12)) {
      uVar7 = uVar6;
      if (!bVar4) {
        uVar7 = 0xffffffff;
        pcVar15 = local_33c;
        do {
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          cVar1 = *pcVar15;
          pcVar15 = pcVar15 + 1;
        } while (cVar1 != '\0');
        prof_printf(s___s__004d2010,0x17 - (~uVar7 - 1),&empty_str);
        bVar4 = true;
        uVar7 = uVar6;
      }
      goto joined_r0x00455c33;
    }
    prof_printf(s___s___4lu__s_004d2000,0x17,local_33c,uVar7 - uVar3,pcVar15);
    bVar4 = false;
    uVar7 = uVar6;
  } while( true );
}


/* ==== prof_moves_breakdown @ 00455db0 ==== */

void prof_moves_breakdown(void)

{
  int va0;
  int iVar1;
  int iVar2;
  int iVar3;
  int va1;
  int va2;
  int *base;
  int iVar4;
  undefined4 uVar5;
  int *piVar6;
  int iVar7;
  int *local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_c;
  int local_8;
  
  local_24 = 0;
  local_2c = 0;
  local_28 = 0;
  local_18 = 0;
  local_20 = 0;
  local_1c = 0;
  prof_printf(&DAT_004d2254);
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_heading(s_Parallel_move_instruction_dynami_004d2228);
    prof_printf(&DAT_004d21dc,s_move_type_004d2204,s_single_004d2210,s_double_004d2218,
                s_L_space_004d2220);
    prof_printf(&DAT_004d21b4,s_unpaired_004d21d0,*(undefined4 *)(prof_ctx + 0x2fc8),
                *(undefined4 *)(prof_ctx + 0x2fd0),*(undefined4 *)(prof_ctx + 0x2fd8));
    prof_printf(&DAT_004d21b4,s_paired_004d21ac,*(undefined4 *)(prof_ctx + 0x2fcc),
                *(undefined4 *)(prof_ctx + 0x2fd4),*(undefined4 *)(prof_ctx + 0x2fdc));
    prof_heading(s_Notes__1___paired__moves_are_tho_004d2120);
  }
  prof_malloc(*(int *)(*(int *)(cur_itype + 0x18) + 4) << 2);
  prof_heading(s_Instruction_moves_breakdown_004d2104);
  prof_printf(s___9s_27s_004d20ec,&empty_str,s_s_t_a_t_i_c_004d20f8);
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_printf(&DAT_004d20d4,s_d_y_n_a_m_i_c_004d20dc);
  }
  prof_printf(s___9s_26s_004d20bc,&empty_str,s_m_o_v_e_s_004d20c8);
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_printf(&DAT_004d20d4,s_m_o_v_e_s_004d20c8);
  }
  prof_printf(s___12s_10s_8s_8s_8s_004d2090,s_mnemonic_004d20a8,s_unpaired_004d21d0,
              s_single_004d2210,s_double_004d2218,s_total_004d20b4);
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_printf(s__10s_8s_8s_8s_004d2080,s_unpaired_004d21d0,s_single_004d2210,s_double_004d2218,
                s_total_004d20b4);
  }
  prof_printf(&DAT_004d2074);
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_printf(&DAT_004d206c);
  }
  prof_printf(&DAT_004ad72c);
  iVar4 = 0;
  piVar6 = base;
  if (0 < *(int *)(*(int *)(cur_itype + 0x18) + 4)) {
    do {
      *piVar6 = iVar4;
      iVar4 = iVar4 + 1;
      piVar6 = piVar6 + 1;
    } while (iVar4 < *(int *)(*(int *)(cur_itype + 0x18) + 4));
  }
  qsort(base,*(uint *)(*(int *)(cur_itype + 0x18) + 4),4,hid_4561b0);
  local_c = 0;
  local_8 = *(int *)(cur_itype + 0x18);
  iVar4 = prof_ctx;
  iVar7 = 0;
  local_30 = base;
  if (0 < *(int *)(local_8 + 4)) {
    do {
      iVar7 = *local_30;
      va0 = *(int *)(iVar4 + 0x2648 + iVar7 * 4);
      iVar1 = *(int *)(iVar4 + 0x1ce8 + iVar7 * 4);
      iVar2 = *(int *)(iVar4 + 0x2008 + iVar7 * 4);
      iVar3 = *(int *)(iVar4 + 9000 + iVar7 * 4);
      va1 = *(int *)(iVar4 + 0x2968 + iVar7 * 4);
      va2 = *(int *)(iVar4 + 0x2c88 + iVar7 * 4);
      if (*(int *)(iVar4 + 200 + iVar7 * 4) == 1) {
        uVar5 = (**(code **)(local_8 + 0x14))(iVar7,iVar1,iVar2,iVar3,iVar2 + iVar3 * 2);
        prof_printf(s___9s_10u_8u_8u_8u_004d2058,uVar5);
        if (*(int *)(prof_ctx + 0x37a0) == 3) {
          prof_printf(s__10u_8u_8u_8u_004d2048,va0,va1,va2,va1 + va2 * 2);
        }
        prof_printf(&DAT_004ad72c);
        local_24 = local_24 + iVar1;
        local_20 = local_20 + va1;
        local_2c = local_2c + iVar2;
        local_18 = local_18 + va0;
        local_28 = local_28 + iVar3;
        local_1c = local_1c + va2;
        iVar4 = prof_ctx;
      }
      local_c = local_c + 1;
      local_8 = *(int *)(cur_itype + 0x18);
      local_30 = local_30 + 1;
      iVar7 = local_2c;
    } while (local_c < *(int *)(local_8 + 4));
  }
  prof_printf(s___9s_10u_8u_8u_8u_004d202c,s_TOTAL_004d2040,local_24,iVar7,local_28,
              iVar7 + local_28 * 2);
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_printf(s__10u_8u_8u_8u_004d2048,local_18,local_20,local_1c,local_20 + local_1c * 2);
  }
  prof_printf(&DAT_004ad72c);
  if (base != (int *)0x0) {
    dsp_free(base);
  }
  return;
}


/* ==== hid_4561b0 @ 004561b0 ==== */

int hid_4561b0(int *param_1,int *param_2)

{
  return ((*(int *)(prof_ctx + 0x2c88 + *param_2 * 4) - *(int *)(prof_ctx + 0x2c88 + *param_1 * 4))
          * 2 - *(int *)(prof_ctx + 0x2968 + *param_1 * 4)) +
         *(int *)(prof_ctx + 0x2968 + *param_2 * 4);
}


/* ==== prof_addr_mode_breakdown @ 004561f0 ==== */

void prof_addr_mode_breakdown(void)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  int unaff_EBX;
  int unaff_EBP;
  int unaff_EDI;
  char *pcVar8;
  int in_stack_fffffaa4;
  char acStack_558 [24];
  int aiStack_540 [16];
  int local_500 [320];
  
  piVar5 = local_500;
  for (iVar4 = 0x140; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar5 = 0;
    piVar5 = piVar5 + 1;
  }
  (**(code **)(*(int *)(cur_itype + 0x18) + 0x18))(local_500);
  prof_printf(&DAT_004d2254);
  prof_heading(s_Dynamic_addressing_mode_breakdow_004d22bc);
  ps_font(2,4,unaff_EDI);
  prof_printf(&DAT_004d2284,s_instruction_group_004d2298,s_operand_modes_004d22ac);
  ps_font(6,unaff_EDI,in_stack_fffffaa4);
  stats_group = 0;
  if (0 < **(int **)(cur_itype + 0x18)) {
    do {
      iVar4 = 0;
      piVar5 = aiStack_540;
      do {
        *piVar5 = iVar4;
        iVar4 = iVar4 + 1;
        piVar5 = piVar5 + 1;
      } while (iVar4 < 0x10);
      qsort(aiStack_540,0x10,4,hid_456400);
      prof_printf(&DAT_004d2278,
                  *(undefined4 *)(*(int *)(*(int *)(cur_itype + 0x18) + 8) + stats_group * 4));
      ps_font(2,6,unaff_EBX);
      prof_printf(&DAT_004d2270,
                  *(undefined4 *)(*(int *)(*(int *)(cur_itype + 0x18) + 0xc) + stats_group * 4));
      ps_font(6,unaff_EBX,unaff_EBP);
      piVar5 = aiStack_540;
      iVar4 = 0x10;
      do {
        iVar3 = *piVar5;
        if ((iVar3 != 0) && (iVar1 = stats_group * 0x10 + iVar3, local_500[iVar1] != 0)) {
          sprintf(acStack_558,&DAT_004c5578,*(undefined4 *)(prof_ctx + 0x2fe0 + iVar1 * 4));
          uVar6 = 0xffffffff;
          pcVar8 = (char *)local_500[stats_group * 0x10 + iVar3];
          do {
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            cVar2 = *pcVar8;
            pcVar8 = pcVar8 + 1;
          } while (cVar2 != '\0');
          uVar7 = 0xffffffff;
          pcVar8 = acStack_558;
          do {
            if (uVar7 == 0) break;
            uVar7 = uVar7 - 1;
            cVar2 = *pcVar8;
            pcVar8 = pcVar8 + 1;
          } while (cVar2 != '\0');
          prof_printf(&DAT_004d2260,(char *)local_500[stats_group * 0x10 + iVar3],
                      (0x1e - (~uVar6 - 1)) - (~uVar7 - 1));
          prof_printf(&DAT_004d2258,
                      *(undefined4 *)(prof_ctx + 0x2fe0 + (stats_group * 0x10 + iVar3) * 4));
        }
        piVar5 = piVar5 + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
      prof_printf(&DAT_004ad72c);
      stats_group = stats_group + 1;
    } while (stats_group < **(int **)(cur_itype + 0x18));
  }
  return;
}


/* ==== hid_456400 @ 00456400 ==== */

int hid_456400(int *param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(prof_ctx + 0x2fe0 + (*param_1 + stats_group * 0x10) * 4);
  uVar2 = *(uint *)(prof_ctx + 0x2fe0 + (*param_2 + stats_group * 0x10) * 4);
  if (uVar1 < uVar2) {
    return 1;
  }
  return -(uint)(uVar2 < uVar1);
}


/* ==== prof_data_mem_refs @ 00456440 ==== */

void prof_data_mem_refs(void)

{
  int va1;
  int va2;
  int va3;
  char *pcVar1;
  int iVar2;
  undefined1 *va0;
  
  va1 = *(int *)(prof_ctx + 0x98);
  va2 = *(int *)(prof_ctx + 0x9c);
  va3 = *(int *)(prof_ctx + 0xa0);
  prof_heading(s_Data_memory_references_004d23d8);
  prof_printf(&DAT_004d239c,s_Memory_004d23c0,&DAT_004d23c8,s_Write_004d23d0);
  iVar2 = 0;
  do {
    if (iVar2 == 0) {
      pcVar1 = s_Internal_004d2390;
    }
    else if (iVar2 == 1) {
      pcVar1 = s_External_004d2384;
    }
    else {
      pcVar1 = s_Internal_ROM_004d2374;
      if (iVar2 != 2) {
        pcVar1 = s_External_ROM_004d2364;
      }
    }
    prof_printf(&DAT_004d2358,pcVar1);
    prof_printf(s__10u__004d2350,*(undefined4 *)(prof_ctx + 0x2fa8 + iVar2 * 4));
    if ((iVar2 == 2) || (iVar2 == 3)) {
      va0 = &empty_str;
      pcVar1 = &DAT_004d233c;
    }
    else {
      va0 = *(undefined1 **)(prof_ctx + 0x2fb8 + iVar2 * 4);
      pcVar1 = s__10u_004d2348;
    }
    prof_printf(pcVar1,va0);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 4);
  iVar2 = va2 + va1 + va3;
  if (iVar2 != 0) {
    prof_printf(s__lu_locations_were_written_witho_004d22e0,iVar2,va1,va2,va3);
  }
  return;
}


/* ==== prof_occurrence_reports @ 00456530 ==== */

void prof_occurrence_reports(void)

{
  prof_insn_occurrence(cmp_insn_name,s_sorted_alphabetically_004d2440);
  prof_insn_occurrence(hid_456640,s_sorted_by_percentage_004d2428);
  prof_doloop_occurrence(cmp_insn_name,s_sorted_alphabetically_004d2440);
  prof_doloop_occurrence(hid_456640,s_sorted_by_percentage_004d2428);
  if (((byte)*(undefined4 *)(prof_ctx + 0x34e0) & 8) == 8) {
    prof_printf(s_Note___P_memory_undecoded_instru_004d23f0);
  }
  return;
}


/* ==== cmp_insn_name @ 004565a0 ==== */

int __cdecl cmp_insn_name(void *a,void *b)

{
  char cVar1;
  byte bVar2;
  char *pcVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  byte *pbVar7;
  char *pcVar8;
  bool bVar9;
  byte abStack_18 [24];
  
  pcVar3 = (char *)(**(code **)(*(int *)(cur_itype + 0x18) + 0x14))(*(undefined4 *)a);
  uVar5 = 0xffffffff;
  do {
    pcVar8 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar8;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pbVar7 = (byte *)(pcVar8 + -uVar5);
  pbVar4 = abStack_18;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pbVar4 = *(undefined4 *)pbVar7;
    pbVar7 = pbVar7 + 4;
    pbVar4 = pbVar4 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar4 = *pbVar7;
    pbVar7 = pbVar7 + 1;
    pbVar4 = pbVar4 + 1;
  }
  pbVar4 = (byte *)(**(code **)(*(int *)(cur_itype + 0x18) + 0x14))(*(undefined4 *)b);
  pbVar7 = abStack_18;
  while( true ) {
    bVar2 = *pbVar7;
    bVar9 = bVar2 < *pbVar4;
    if (bVar2 != *pbVar4) break;
    if (bVar2 == 0) {
      return 0;
    }
    bVar2 = pbVar7[1];
    bVar9 = bVar2 < pbVar4[1];
    if (bVar2 != pbVar4[1]) break;
    pbVar7 = pbVar7 + 2;
    pbVar4 = pbVar4 + 2;
    if (bVar2 == 0) {
      return 0;
    }
  }
  return (1 - (uint)bVar9) - (uint)(bVar9 != 0);
}


/* ==== hid_456640 @ 00456640 ==== */

int hid_456640(int *param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = *(uint *)(prof_ctx + 0x708 + *param_1 * 4);
  uVar2 = *(uint *)(prof_ctx + 0x708 + *param_2 * 4);
  if (uVar1 < uVar2) {
    return 1;
  }
  if (uVar2 < uVar1) {
    return -1;
  }
  iVar3 = cmp_insn_name(param_1,param_2);
  return iVar3;
}


/* ==== prof_insn_occurrence @ 00456690 ==== */

void __cdecl prof_insn_occurrence(void *cmp,char *title)

{
  int iVar1;
  uint uVar2;
  float fVar3;
  bool bVar4;
  int *base;
  int iVar5;
  undefined4 uVar6;
  int *piVar7;
  char cVar8;
  int unaff_ESI;
  int unaff_EDI;
  int iVar9;
  
  bVar4 = false;
  prof_malloc(*(int *)(*(int *)(cur_itype + 0x18) + 4) << 2);
  prof_printf(&DAT_004d2254);
  prof_heading(s_Instruction_Occurrence_Breakdown_004d251c,title);
  ps_font(2,4,unaff_EDI);
  prof_printf(&DAT_004d2514);
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_printf(&DAT_004d250c,s_d_y_n_a_m_i_c_004d20dc);
  }
  prof_printf(&DAT_004ad72c);
  prof_printf(s__2s__12s_10s_10s_004d24e4,&empty_str,s_mnemonic_004d20a8,s___occur_004d24f8);
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_printf(s__10s_10s_004d24d8,s___occur_004d24f8,s___of_100_004d2500);
  }
  prof_printf(&DAT_004ad72c);
  ps_font(6,unaff_EDI,unaff_ESI);
  prof_printf(&DAT_004d24d0);
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_printf(&DAT_004d24c8);
  }
  prof_printf(&DAT_004ad72c);
  if ((*(int *)(prof_ctx + 0xb0) != 0) || (iVar5 = prof_ctx, *(int *)(prof_ctx + 0xb4) != 0)) {
    iVar5 = 0;
    piVar7 = base;
    if (0 < *(int *)(*(int *)(cur_itype + 0x18) + 4)) {
      do {
        *piVar7 = iVar5;
        iVar5 = iVar5 + 1;
        piVar7 = piVar7 + 1;
      } while (iVar5 < *(int *)(*(int *)(cur_itype + 0x18) + 4));
    }
    qsort(base,*(uint *)(*(int *)(cur_itype + 0x18) + 4),4,cmp);
    cmp = (void *)0x0;
    iVar9 = *(int *)(cur_itype + 0x18);
    iVar5 = prof_ctx;
    piVar7 = base;
    if (0 < *(int *)(iVar9 + 4)) {
      do {
        iVar1 = *piVar7;
        cVar8 = ' ';
        uVar2 = *(uint *)(iVar5 + 1000 + iVar1 * 4);
        if ((uVar2 != 0) || (*(int *)(iVar5 + 0x708 + iVar1 * 4) != 0)) {
          if (*(int *)(iVar5 + 0xb0) == 0) {
            fVar3 = 0.0;
          }
          else {
            fVar3 = (float)uVar2 / (float)*(int *)(iVar5 + 0xb0);
          }
          if (*(int *)(iVar5 + 0xb4) == 0) {
            title = (char *)0x0;
          }
          else {
            title = (char *)((float)*(uint *)(iVar5 + 0x708 + iVar1 * 4) /
                            (float)*(int *)(iVar5 + 0xb4));
          }
          if (*(int *)(iVar5 + 200 + iVar1 * 4) == 1) {
            cVar8 = '+';
            bVar4 = true;
          }
          uVar6 = (**(code **)(iVar9 + 0x14))(iVar1,uVar2,(double)(fVar3 * 100.0));
          prof_printf(s__c___12s_10u_10_2f_004d24b4,(int)cVar8,uVar6);
          if (*(int *)(prof_ctx + 0x37a0) == 3) {
            prof_printf(s__10u_10_2f_004d24a8,*(undefined4 *)(prof_ctx + 0x708 + iVar1 * 4),
                        SUB84((double)((float)title * 100.0),0),
                        (int)((ulonglong)(double)((float)title * 100.0) >> 0x20));
          }
          prof_printf(&DAT_004ad72c);
          iVar5 = prof_ctx;
        }
        cmp = (void *)((int)cmp + 1);
        iVar9 = *(int *)(cur_itype + 0x18);
        piVar7 = piVar7 + 1;
      } while ((int)cmp < *(int *)(iVar9 + 4));
    }
  }
  prof_printf(s__2s__12s_10u_10_2f_004d2490,&empty_str,s_TOTAL_004d2040,
              *(undefined4 *)(iVar5 + 0xb0),0);
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_printf(s__10u_10_2f_004d24a8,*(undefined4 *)(prof_ctx + 0xb4),0,0x40590000);
  }
  prof_printf(&DAT_004ad72c);
  if (bVar4) {
    prof_printf(s_instructions_marked_with_____all_004d2458);
  }
  if (base != (int *)0x0) {
    dsp_free(base);
  }
  return;
}


/* ==== prof_doloop_occurrence @ 004569f0 ==== */

void __cdecl prof_doloop_occurrence(void *cmp,char *title)

{
  int iVar1;
  bool bVar2;
  int *base;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int *piVar6;
  char cVar7;
  int iVar8;
  int unaff_ESI;
  int unaff_EDI;
  int local_c;
  
  iVar8 = 0;
  bVar2 = false;
  local_c = 0;
  prof_malloc(*(int *)(*(int *)(cur_itype + 0x18) + 4) << 2);
  prof_printf(&DAT_004d2254);
  prof_heading(s_Do_Loops_Instruction_Occurrence_B_004d25ec,title);
  ps_font(2,4,unaff_EDI);
  prof_printf(&DAT_004d25e4,s_s_t_a_t_i_c_004d20f8);
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_printf(&DAT_004d25dc,s_d_y_n_a_m_i_c_004d20dc);
  }
  prof_printf(&DAT_004ad72c);
  prof_printf(s__2s__12s_10s_10s_10s_004d25bc,&empty_str,s_mnemonic_004d20a8,s___occur_004d24f8,
              s_nesting_004d25d4,s___occur_004d24f8);
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_printf(s__10s_10s_10s_004d25ac,s___occur_004d24f8,s_nesting_004d25d4,s___occur_004d24f8);
  }
  prof_printf(&DAT_004ad72c);
  prof_printf(s__14s_10s_10s_10s_004d2590,&empty_str,s_no_loop_004d25a4,&DAT_004bfa98,&empty_str);
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_printf(s__10s_10s_004d24d8,s_no_loop_004d25a4,&DAT_004bfa98);
  }
  prof_printf(&DAT_004ad72c);
  ps_font(6,unaff_EDI,unaff_ESI);
  prof_printf(&DAT_004d2588);
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_printf(&DAT_004d206c);
  }
  prof_printf(&DAT_004ad72c);
  if ((*(int *)(prof_ctx + 0xb0) != 0) || (*(int *)(prof_ctx + 0xb4) != 0)) {
    iVar3 = 0;
    piVar6 = base;
    if (0 < *(int *)(*(int *)(cur_itype + 0x18) + 4)) {
      do {
        *piVar6 = iVar3;
        iVar3 = iVar3 + 1;
        piVar6 = piVar6 + 1;
      } while (iVar3 < *(int *)(*(int *)(cur_itype + 0x18) + 4));
    }
    qsort(base,*(uint *)(*(int *)(cur_itype + 0x18) + 4),4,cmp);
    title = (char *)0x0;
    iVar3 = *(int *)(cur_itype + 0x18);
    iVar5 = prof_ctx;
    piVar6 = base;
    if (0 < *(int *)(iVar3 + 4)) {
      do {
        iVar1 = *piVar6;
        cVar7 = ' ';
        if ((*(int *)(iVar5 + 1000 + iVar1 * 4) != 0) || (*(int *)(iVar5 + 0x708 + iVar1 * 4) != 0))
        {
          if (*(int *)(iVar5 + 200 + iVar1 * 4) == 1) {
            cVar7 = '+';
            bVar2 = true;
          }
          uVar4 = (**(code **)(iVar3 + 0x14))
                            (iVar1,*(undefined4 *)(iVar5 + 0x1068 + iVar1 * 4),
                             *(undefined4 *)(iVar5 + 0xd48 + iVar1 * 4),
                             *(undefined4 *)(iVar5 + 0xa28 + iVar1 * 4));
          prof_printf(s__c___12s_10u_10u_10u_004d2570,(int)cVar7,uVar4);
          iVar8 = iVar8 + *(int *)(prof_ctx + 0x1068 + iVar1 * 4);
          if (*(int *)(prof_ctx + 0x37a0) == 3) {
            iVar3 = iVar1 * 4 + 0x19c8;
            prof_printf(s__10u_10u_10u_004d2560,*(undefined4 *)(prof_ctx + iVar3),
                        *(undefined4 *)(prof_ctx + 5000 + iVar1 * 4),
                        *(undefined4 *)(prof_ctx + 0x16a8 + iVar1 * 4));
            local_c = local_c + *(int *)(prof_ctx + iVar3);
          }
          prof_printf(&DAT_004ad72c);
          iVar5 = prof_ctx;
        }
        title = title + 1;
        iVar3 = *(int *)(cur_itype + 0x18);
        piVar6 = piVar6 + 1;
      } while ((int)title < *(int *)(iVar3 + 4));
    }
  }
  prof_printf(s__2s__12s_10u_20s_004d254c,&empty_str,s_TOTAL_004d2040,iVar8,&empty_str);
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_printf(&DAT_004d2544,local_c);
  }
  prof_printf(&DAT_004ad72c);
  if (bVar2) {
    prof_printf(s_instructions_marked_with_____all_004d2458);
  }
  if (base != (int *)0x0) {
    dsp_free(base);
  }
  return;
}


/* ==== prof_basic_profile @ 00456d60 ==== */

void prof_basic_profile(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = cur_sim;
  prof_heading(s_Basic_Profile_004d2744);
  prof_printf(s_Static_004d2738);
  iVar2 = *(int *)(prof_ctx + 0x74);
  iVar3 = *(int *)(prof_ctx + 0x78);
  iVar4 = *(int *)(prof_ctx + 0x70);
  iVar1 = iVar3 + iVar2 + iVar4;
  prof_printf(s___25s___8u_words_004d270c,s_Initialized_data_size_004d2720,iVar1);
  if (iVar1 != 0) {
    prof_printf(s__X__u__Y__u__P__u__004d26f8,iVar4,iVar2,iVar3);
  }
  prof_printf(&DAT_004ad72c);
  iVar2 = *(int *)(prof_ctx + 0x88);
  iVar3 = *(int *)(prof_ctx + 0x8c);
  iVar4 = *(int *)(prof_ctx + 0x84);
  iVar1 = iVar3 + iVar2 + iVar4;
  prof_printf(s___25s___8u_words_004d270c,s_Uninitialized_data_size_004d26e0,iVar1);
  if (iVar1 != 0) {
    prof_printf(s__X__u__Y__u__P__u__004d26f8,iVar4,iVar2,iVar3);
  }
  prof_printf(&DAT_004ad72c);
  prof_printf(s___25s___8u_words_004d26c0,s_Code_size_004d26d4,*(undefined4 *)(prof_ctx + 0xa8));
  prof_printf(s___25s___8u_004d26a0,s_Instructions_004d26b0,*(undefined4 *)(prof_ctx + 0xb0));
  prof_printf(s___25s___8u_levels_004d2678,s_Max_loop_nesting_004d268c,
              *(undefined4 *)(prof_ctx + 0xc4));
  if (*(int *)(prof_ctx + 0x37a0) == 3) {
    prof_printf(s_Dynamic_004d266c);
    prof_printf(s___25s___8lu_cycles_004d2640,s_Total_cycle_count_004d2658,
                *(undefined4 *)(prof_ctx + 0xbc));
    prof_printf(s___25s___8lu_cycles_004d2640,s_Stall_cycle_count_004d262c,
                *(undefined4 *)(prof_ctx + 0xc0));
    prof_printf(s___25s___8u_words_004d26c0,s_Code_size_004d26d4,*(undefined4 *)(prof_ctx + 0xac));
    prof_printf(s___25s___8u_004d26a0,s_Instructions_004d26b0,*(undefined4 *)(prof_ctx + 0xb4));
    prof_printf(s___25s___8u_004d26a0,s_Function_calls_004d261c,*(undefined4 *)(prof_ctx + 0xb8));
    prof_printf(s___25s___8u_levels_004d2678,s_Max_loop_nesting_004d268c,
                *(undefined4 *)(iVar5 + 0x478));
  }
  return;
}


