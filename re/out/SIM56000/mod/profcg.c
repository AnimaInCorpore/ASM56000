/* ==== subr_on_stack @ 0047d160 ==== */

int __cdecl subr_on_stack(void *sub)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  if (*(int *)(prof_ctx + 0x3788) < 1) {
    return 0;
  }
  piVar2 = (int *)(prof_ctx + 0x3520);
  do {
    if ((void *)*piVar2 == sub) {
      return 1;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 7;
  } while (iVar1 < *(int *)(prof_ctx + 0x3788));
  return 0;
}


/* ==== subr_return @ 0047d1a0 ==== */

void __cdecl subr_return(void *from,int cycles)

{
  int *piVar1;
  void *sub;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  uVar4 = *(uint *)(prof_ctx + 0x34e0) & 6;
  if ((uVar4 == 0) && (iVar3 = *(int *)(prof_ctx + 0x3788), 0 < iVar3)) {
    sub = *(void **)(prof_ctx + 0x3520 + iVar3 * 0x1c);
    iVar5 = cycles - *(int *)(prof_ctx + iVar3 * 0x1c + 0x3528);
    *(int *)((int)sub + 0x1c) = *(int *)((int)sub + 0x1c) + iVar5;
    iVar3 = subr_on_stack(sub);
    if (iVar3 == 1) {
      *(int *)((int)sub + 0x20) = *(int *)((int)sub + 0x20) + iVar5;
    }
    do {
      iVar5 = *(int *)(prof_ctx + 0x3788);
      iVar2 = *(int *)(prof_ctx + 0x3504 + iVar5 * 0x1c);
      iVar3 = prof_ctx + iVar5 * 0x1c;
      iVar6 = cycles - *(int *)(prof_ctx + 0x350c + iVar5 * 0x1c);
      iVar5 = subr_on_stack(*(void **)(prof_ctx + 0x3520 + iVar5 * 0x1c));
      if (iVar5 != 1) {
        *(int *)(iVar2 + 0x24) = *(int *)(iVar2 + 0x24) + iVar6;
        *(int *)(*(int *)(iVar3 + 0x3510) + 8) = *(int *)(*(int *)(iVar3 + 0x3510) + 8) + iVar6;
        piVar1 = (int *)(*(int *)(iVar3 + 0x3530) + 8);
        *piVar1 = *piVar1 + iVar6;
      }
      *(undefined4 *)(prof_ctx + 0x3798) = *(undefined4 *)(iVar3 + 0x3534);
      *(int *)(prof_ctx + 0x3788) = *(int *)(prof_ctx + 0x3788) + -1;
    } while (*(int *)(iVar3 + 0x3538) == 1);
    *(int *)(iVar3 + 0x350c) = cycles;
    return;
  }
  if (uVar4 == 0) {
    *(uint *)(prof_ctx + 0x34e0) = *(uint *)(prof_ctx + 0x34e0) & 0xfffffffd | 4;
    *(undefined4 *)(prof_ctx + 0x378c) = *(undefined4 *)((int)from + 0xa4);
    *(undefined4 *)(prof_ctx + 0x3790) = *(undefined4 *)((int)from + 0xa8);
  }
  return;
}


/* ==== subr_profile_finish @ 0047d2e0 ==== */

int subr_profile_finish(void)

{
  void *from;
  int iVar1;
  int iVar2;
  byte bVar3;
  char cVar4;
  char cVar5;
  void *item;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int extraout_EAX;
  undefined3 extraout_var_01;
  int local_4;
  void *pvVar6;
  
  local_4 = 0;
  if (((*(int *)(prof_ctx + 0x37a0) == 3) &&
      (bVar3 = (byte)*(undefined4 *)(prof_ctx + 0x34e0), (bVar3 & 0x10) != 0x10)) &&
     ((bVar3 & 6) != 2)) {
    pvVar6 = *(void **)(prof_ctx + 0x3518);
    if (*(int *)(prof_ctx + 0x3798) != 0) {
      subr_return(*(void **)(prof_ctx + 0x379c),*(int *)(prof_ctx + 0xbc));
    }
    from = *(void **)(prof_ctx + 0x379c);
    if ((from != (void *)0x0) && ((*(byte *)((int)from + 0xd8) & 2) != 0)) {
      subr_return(from,*(int *)(prof_ctx + 0xbc));
    }
    if ((*(int *)(prof_ctx + 0x3788) == 1) && (*(void **)(prof_ctx + 0x353c) == pvVar6)) {
      subr_return((void *)0x0,*(int *)(prof_ctx + 0xbc));
    }
    iVar1 = *(int *)(prof_ctx + 0x3788);
    iVar2 = iVar1;
    while (0 < iVar2) {
      subr_return((void *)0x0,*(int *)(prof_ctx + 0xbc));
      iVar2 = *(int *)(prof_ctx + 0x3788);
    }
    *(int *)(prof_ctx + 0x3788) = iVar1;
    *(int *)((int)pvVar6 + 0x28) = *(int *)((int)pvVar6 + 0x28) + -1;
    cg_lookup_name(s___MOTHER___004d55cc,4);
    prof_list_delete(*(void **)((int)item + 0x10),pvVar6);
    prof_list_delete(*(void **)((int)pvVar6 + 0x14),item);
    *(undefined4 *)((int)item + 0x24) = 0;
    *(undefined4 *)((int)item + 4) = 0;
    cg_merge_nodes(pvVar6,item);
    cVar4 = avl_iter(*(void **)(prof_ctx + 0x3514),(char *)0x0,(void *)0x0);
    cVar5 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar4),(void *)0x0);
    pvVar6 = (void *)CONCAT31(extraout_var_00,cVar5);
    while (pvVar6 != (void *)0x0) {
      local_4 = local_4 + *(int *)((int)pvVar6 + 0x28);
      subr_format_name(pvVar6);
      prof_list_remove(*(void **)((int)pvVar6 + 0x10),pvVar6);
      if (extraout_EAX != 0) {
        *(uint *)((int)pvVar6 + 0x18) = *(uint *)((int)pvVar6 + 0x18) | 4;
      }
      cVar5 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar4),(void *)0x0);
      pvVar6 = (void *)CONCAT31(extraout_var_01,cVar5);
    }
    return local_4;
  }
  return 0;
}


/* ==== subr_format_name @ 0047d4a0 ==== */

void __cdecl subr_format_name(void *sub)

{
  void *func;
  undefined4 *puVar1;
  void *pvVar2;
  char cVar3;
  char cVar4;
  int extraout_EAX;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined4 va0;
  undefined3 extraout_var_02;
  uint uVar6;
  int iVar7;
  uint uVar8;
  void *pvVar9;
  undefined4 *puVar10;
  char *pcVar11;
  char *pcVar12;
  char *pcVar13;
  char local_1c [22];
  char local_6 [6];
  undefined4 *puVar5;
  
  pvVar2 = sub;
  if ((*(uint *)((int)sub + 0x18) & 2) == 0) {
    *(uint *)((int)sub + 0x18) = *(uint *)((int)sub + 0x18) | 2;
    puVar10 = (undefined4 *)0x0;
    local_1c[0] = '\0';
    if (*(char **)((int)sub + 4) == (char *)0x0) {
      puVar5 = (undefined4 *)((int)sub + 8);
      sub = (void *)0x0;
      cVar4 = avl_iter((void *)*puVar5,(char *)0x0,(void *)0x0);
      cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar4),(void *)0x0);
      puVar5 = (undefined4 *)CONCAT31(extraout_var_00,cVar3);
      func = (void *)0x0;
      puVar1 = sub;
      while (puVar5 != (undefined4 *)0x0) {
        pvVar9 = (void *)puVar5[0x27];
        sub = puVar1;
        if (((pvVar9 == (void *)0x0) && (pvVar9 = func, sub = puVar5, (puVar5[3] & 0x1000) == 0)) &&
           ((puVar10 == (undefined4 *)0x0 || (sub = puVar1, puVar5[0x2b] != 0)))) {
          puVar10 = puVar5;
          sub = puVar1;
        }
        cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar4),(void *)0x0);
        func = pvVar9;
        puVar1 = sub;
        puVar5 = (undefined4 *)CONCAT31(extraout_var_01,cVar3);
      }
      if (func == (void *)0x0) {
        if (puVar10 == (undefined4 *)0x0) {
          va0 = *puVar1;
        }
        else {
          va0 = *puVar10;
        }
        sprintf(local_1c,s______p___lx_004d55f8,va0);
        if ((puVar10 != (undefined4 *)0x0) && (puVar10[0x2b] != 0)) {
          sprintf(local_1c,s______p___lx_<__c:__lx)_004d55e0,*puVar10,
                  (int)(char)(&DAT_004d3bf0)[puVar10[0x2b]],puVar10[0x2c]);
        }
      }
      else {
        prof_func_fullname(local_1c,func,0x16);
      }
    }
    else {
      strncat(local_1c,*(char **)((int)sub + 4),0x17);
      if (((*(byte *)((int)sub + 0x18) & 1) != 0) &&
         (cg_lookup_name(*(char **)((int)sub + 4),4), extraout_EAX != 0)) {
        uVar6 = 0xffffffff;
        pcVar11 = &DAT_004d5604;
        do {
          pcVar13 = pcVar11;
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          pcVar13 = pcVar11 + 1;
          cVar4 = *pcVar11;
          pcVar11 = pcVar13;
        } while (cVar4 != '\0');
        uVar6 = ~uVar6;
        iVar7 = -1;
        pcVar11 = local_1c;
        do {
          pcVar12 = pcVar11;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar12 = pcVar11 + 1;
          cVar4 = *pcVar11;
          pcVar11 = pcVar12;
        } while (cVar4 != '\0');
        pcVar11 = pcVar13 + -uVar6;
        pcVar13 = pcVar12 + -1;
        for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
          pcVar11 = pcVar11 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar13 = *pcVar11;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        }
      }
    }
    uVar6 = 0xffffffff;
    pcVar11 = local_1c;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar4 = *pcVar11;
      pcVar11 = pcVar11 + 1;
    } while (cVar4 != '\0');
    if (0x16 < ~uVar6 - 1) {
      sprintf(local_6,&DAT_004d55dc);
    }
    if (pvVar2 == *(void **)(prof_ctx + 0x3518)) {
      uVar6 = 0xffffffff;
      pcVar11 = &DAT_004d55d8;
      do {
        pcVar13 = pcVar11;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar13 = pcVar11 + 1;
        cVar4 = *pcVar11;
        pcVar11 = pcVar13;
      } while (cVar4 != '\0');
      uVar6 = ~uVar6;
      iVar7 = -1;
      pcVar11 = local_1c;
      do {
        pcVar12 = pcVar11;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar12 = pcVar11 + 1;
        cVar4 = *pcVar11;
        pcVar11 = pcVar12;
      } while (cVar4 != '\0');
      pcVar11 = pcVar13 + -uVar6;
      pcVar13 = pcVar12 + -1;
      for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
        pcVar11 = pcVar11 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar13 = *pcVar11;
        pcVar11 = pcVar11 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
    cVar4 = pool_strdup(prof_ctx + 0x34e8,local_1c);
    *(uint *)((int)pvVar2 + 4) = CONCAT31(extraout_var_02,cVar4);
  }
  return;
}


/* ==== subr_report @ 0047d680 ==== */

void subr_report(void)

{
  uint uVar1;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  undefined4 extraout_EAX_01;
  
  if (*(int *)(prof_ctx + 0x37a0) == 1) {
    prof_printf(s_No_instructions_executed___No_Su_004d56f8);
    return;
  }
  uVar1 = *(uint *)(prof_ctx + 0x34e0) >> 1 & 3;
  if (uVar1 != 0) {
    if (uVar1 == 1) {
      prof_printf(s_Note___Subroutine_stack_overflow_004d5608,*(undefined4 *)(prof_ctx + 0x378c),
                  *(undefined4 *)(prof_ctx + 0x3790),0x14);
    }
    else if (uVar1 == 2) {
      prof_printf(s_Note___Subroutine_stack_underflo_004d56a4,*(undefined4 *)(prof_ctx + 0x378c),
                  *(undefined4 *)(prof_ctx + 0x3790));
      prof_printf(s_Subroutine_Coverage_Error_s____N_004d566c);
      return;
    }
    prof_printf(s_Subroutine_Coverage_Error_s____N_004d566c);
    return;
  }
  avl_copy_sorted(*(void **)(prof_ctx + 0x3514),8,1);
  *(undefined4 *)(prof_ctx + 0x3514) = extraout_EAX;
  subr_report_basic(*(undefined4 *)(prof_ctx + 0xbc));
  avl_copy_sorted(*(void **)(prof_ctx + 0x3514),9,1);
  *(undefined4 *)(prof_ctx + 0x3514) = extraout_EAX_00;
  subr_report_callgraph();
  avl_copy_sorted(*(void **)(prof_ctx + 0x3514),7,1);
  *(undefined4 *)(prof_ctx + 0x3514) = extraout_EAX_01;
  cg_print_tree_text();
  cg_ps_call_tree();
  cg_ps_call_graph();
  return;
}


/* ==== subr_report_basic @ 0047d7a0 ==== */

void subr_report_basic(void)

{
  float fVar1;
  char cVar2;
  char cVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined1 *puVar4;
  undefined3 extraout_var_02;
  int iVar5;
  int iVar6;
  int unaff_ESI;
  int iVar7;
  int unaff_EDI;
  char *pcVar8;
  char *pcVar9;
  int in_stack_00000004;
  undefined3 extraout_var_01;
  
  iVar6 = 0;
  prof_printf(&DAT_004d2254);
  prof_heading(s_Basic_Subroutine_Profile_004d589c);
  ps_font(2,4,unaff_EDI);
  prof_printf(s_Routine_Type__calls__call__entry_004d583c);
  prof_printf(s_points_points_Cycles_004d57e0);
  ps_font(6,unaff_EDI,unaff_ESI);
  prof_printf(&DAT_004d57d4);
  cVar2 = avl_iter(*(void **)(prof_ctx + 0x3514),(char *)0x0,(void *)0x0);
  cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar2),(void *)0x0);
  iVar7 = CONCAT31(extraout_var_00,cVar3);
  while (iVar7 != 0) {
    cVar3 = strstr(*(char **)(iVar7 + 4),&DAT_004d5604);
    puVar4 = (undefined1 *)CONCAT31(extraout_var_01,cVar3);
    if (puVar4 != (undefined1 *)0x0) {
      *puVar4 = 0;
    }
    iVar5 = -1;
    pcVar8 = *(char **)(iVar7 + 4);
    do {
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      cVar3 = *pcVar8;
      pcVar8 = pcVar8 + 1;
    } while (cVar3 != '\0');
    prof_printf(&DAT_004d57c8,*(char **)(iVar7 + 4));
    prof_printf(&DAT_004d57b8);
    prof_printf(s__5d_004d57b0);
    prof_list_count(*(void **)(iVar7 + 0xc));
    prof_printf(s__5d_004d57a4);
    prof_list_count(*(void **)(iVar7 + 8));
    prof_printf(s__5d_004d579c);
    prof_printf(s__6ld_004d5794);
    if (in_stack_00000004 == 0) {
      fVar1 = 0.0;
    }
    else {
      fVar1 = ((float)*(uint *)(iVar7 + 0x1c) / (float)in_stack_00000004) * 100.0;
    }
    prof_printf(s__6_1f_004d5788,(double)fVar1);
    iVar6 = iVar6 + *(int *)(iVar7 + 0x1c);
    prof_printf(&DAT_004d5780,iVar6);
    prof_printf(&DAT_004ad72c);
    if (puVar4 != (undefined1 *)0x0) {
      *puVar4 = 0x28;
    }
    cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar2),(void *)0x0);
    iVar7 = CONCAT31(extraout_var_02,cVar3);
  }
  prof_printf(&DAT_004d57d4);
  prof_heading(s_Subroutine_Stack_at_program_term_004d5754);
  iVar6 = *(int *)(prof_ctx + 0x3788);
  if (iVar6 == 0) {
    prof_printf(s_____EMPTY_____004d5744);
  }
  else if (0 < iVar6) {
    iVar7 = iVar6 * 0x1c;
    do {
      iVar5 = -1;
      pcVar8 = *(char **)(*(int *)(prof_ctx + 0x3520 + iVar7) + 4);
      pcVar9 = pcVar8;
      do {
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        cVar2 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar2 != '\0');
      prof_printf(&DAT_004d5738,pcVar8);
      prof_printf(s_pc___06lx_004d572c,*(undefined4 *)(prof_ctx + 0x3524 + iVar7));
      iVar7 = iVar7 + -0x1c;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  prof_printf(&DAT_004d5504);
  return;
}


/* ==== subr_report_callgraph @ 0047da20 ==== */

void subr_report_callgraph(void)

{
  void *pvVar1;
  char cVar2;
  char cVar3;
  undefined3 extraout_var;
  void *item;
  undefined4 extraout_EAX;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  int extraout_EAX_00;
  undefined4 uVar5;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  uint uVar6;
  int unaff_EBX;
  int unaff_EBP;
  int unaff_ESI;
  char *pcVar7;
  char *pcVar8;
  char *iter;
  int *piVar4;
  undefined3 extraout_var_00;
  
  prof_printf(&DAT_004d2254);
  prof_heading(s_Subroutine_Call_Graph_report_004d592c);
  ps_font(0,4,0xb);
  prof_printf(&DAT_004d5920);
  cVar2 = avl_iter(*(void **)(prof_ctx + 0x3514),(char *)0x0,(void *)0x0);
  iter = (char *)CONCAT31(extraout_var,cVar2);
  cVar2 = avl_iter((void *)0x0,iter,(void *)0x0);
  item = (void *)CONCAT31(extraout_var_00,cVar2);
  do {
    if (item == (void *)0x0) {
      ps_font(6,unaff_ESI,(int)iter);
      return;
    }
    ps_font(1,9,unaff_EBX);
    avl_copy_sorted(*(void **)((int)item + 0x10),0xb,1);
    *(undefined4 *)((int)item + 0x10) = extraout_EAX;
    cVar2 = avl_iter(*(void **)((int)item + 0x14),(char *)0x0,(void *)0x0);
    cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var_01,cVar2),(void *)0x0);
    piVar4 = (int *)CONCAT31(extraout_var_02,cVar3);
    while (piVar4 != (int *)0x0) {
      if ((void *)*piVar4 != item) {
        pcVar8 = *(char **)(*piVar4 + 4);
        uVar6 = 0xffffffff;
        pcVar7 = pcVar8;
        do {
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          cVar3 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar3 != '\0');
        prof_printf(&DAT_004d58f0,0x1a,pcVar8,0x1c - (~uVar6 - 1),piVar4[1],
                    *(undefined4 *)((int)item + 0x28),piVar4[2]);
      }
      cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var_01,cVar2),(void *)0x0);
      piVar4 = (int *)CONCAT31(extraout_var_03,cVar3);
    }
    ps_font(6,unaff_EBX,unaff_EBP);
    uVar6 = 0xffffffff;
    pcVar8 = *(char **)((int)item + 4);
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar2 = *pcVar8;
      pcVar8 = pcVar8 + 1;
    } while (cVar2 != '\0');
    prof_printf(&DAT_004d58c8,*(char **)((int)item + 4),0x1c - (~uVar6 - 1),
                *(undefined4 *)((int)item + 0x28),*(undefined4 *)((int)item + 0x1c),
                *(undefined4 *)((int)item + 0x24));
    if ((*(byte *)((int)item + 0x18) & 8) != 0) {
      prof_printf(&DAT_004d2f3c);
    }
    if (*(int *)((int)item + 0x20) != 0) {
      prof_list_remove(*(void **)((int)item + 0x10),item);
      if (extraout_EAX_00 == 0) {
        uVar5 = 0;
      }
      else {
        uVar5 = *(undefined4 *)(extraout_EAX_00 + 4);
      }
      prof_printf(s___rec____d__ld_004d58b8,uVar5,*(undefined4 *)((int)item + 0x20));
      if ((*(byte *)((int)item + 0x18) & 8) != 0) {
        prof_printf(&DAT_004d2f3c);
      }
    }
    prof_printf(&DAT_004ad72c);
    ps_font(1,9,unaff_EBX);
    cVar2 = avl_iter(*(void **)((int)item + 0x10),(char *)0x0,(void *)0x0);
    cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var_04,cVar2),(void *)0x0);
    piVar4 = (int *)CONCAT31(extraout_var_05,cVar3);
    while (piVar4 != (int *)0x0) {
      pvVar1 = (void *)*piVar4;
      if (pvVar1 != item) {
        uVar6 = 0xffffffff;
        pcVar8 = *(char **)((int)pvVar1 + 4);
        do {
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          cVar3 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar3 != '\0');
        prof_printf(&DAT_004d58f0,0x1a,*(char **)((int)pvVar1 + 4),0x1c - (~uVar6 - 1),piVar4[1],
                    *(undefined4 *)((int)pvVar1 + 0x28),piVar4[2]);
      }
      cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var_04,cVar2),(void *)0x0);
      piVar4 = (int *)CONCAT31(extraout_var_06,cVar3);
    }
    ps_font(6,unaff_EBX,unaff_EBP);
    prof_printf(&DAT_004d5920);
    cVar2 = avl_iter((void *)0x0,iter,(void *)0x0);
    item = (void *)CONCAT31(extraout_var_07,cVar2);
  } while( true );
}


