/* ==== cg_print_tree_text @ 00481d50 ==== */

void cg_print_tree_text(void)

{
  char cVar1;
  char cVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  void *node;
  
  cg_depth = 0;
  prof_printf(&DAT_004d7a60);
  cVar1 = avl_iter(*(void **)(prof_ctx + 0x3514),(char *)0x0,(void *)0x0);
  cVar2 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar1),(void *)0x0);
  node = (void *)CONCAT31(extraout_var_00,cVar2);
  while (node != (void *)0x0) {
    if ((*(byte *)((int)node + 0x18) & 0x10) == 0) {
      cg_print_tree_node(node);
      prof_printf(&DAT_004d7a58);
    }
    cVar2 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar1),(void *)0x0);
    node = (void *)CONCAT31(extraout_var_01,cVar2);
  }
  return;
}


/* ==== cg_print_tree_node @ 00481dd0 ==== */

void __cdecl cg_print_tree_node(void *node)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  char *pcVar7;
  
  iVar2 = cg_depth + 1;
  iVar5 = 1;
  bVar1 = 1 < cg_depth;
  cg_depth = iVar2;
  if (bVar1) {
    piVar6 = &DAT_00505284;
    do {
      if (*piVar6 == 1) {
        pcVar7 = &DAT_004d7ac0;
      }
      else {
        pcVar7 = &DAT_004d7ab4;
      }
      prof_printf(pcVar7);
      iVar5 = iVar5 + 1;
      piVar6 = piVar6 + 1;
    } while (iVar5 < cg_depth + -1);
  }
  if (1 < cg_depth) {
    if (*(int *)(&DAT_0050527c + cg_depth * 4) == 1) {
      pcVar7 = &DAT_004d7aa8;
    }
    else {
      pcVar7 = &DAT_004d7a9c;
    }
    prof_printf(pcVar7);
  }
  if (((*(byte *)((int)node + 0x18) & 0x10) == 0) &&
     ((cg_depth < 10 ||
      (uVar3 = prof_list_count(*(void **)((int)node + 0x10)),
      uVar4 = *(uint *)((int)node + 0x18) >> 2 & 1, uVar3 == uVar4 || (int)(uVar3 - uVar4) < 0)))) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  prof_printf(&DAT_004d7a98);
  if (!bVar1) {
    prof_printf(&DAT_004d7a94);
  }
  prof_printf(&DAT_004d7a90,*(undefined4 *)((int)node + 4));
  if (bVar1) {
    if ((*(byte *)((int)node + 0x18) & 4) != 0) {
      prof_printf(&DAT_004d7a84);
    }
  }
  else {
    prof_printf(&DAT_004d7a8c);
  }
  prof_printf(&DAT_004d7a80);
  if (bVar1) {
    *(uint *)((int)node + 0x18) = *(uint *)((int)node + 0x18) | 0x10;
    cg_print_tree_children(node);
  }
  cg_depth = cg_depth + -1;
  return;
}


/* ==== cg_print_tree_children @ 00481f00 ==== */

void __cdecl cg_print_tree_children(void *node)

{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar5;
  undefined3 extraout_var_01;
  int iVar6;
  int iVar7;
  int *piVar8;
  bool bVar9;
  char *fmt;
  int *piVar4;
  
  iVar3 = prof_list_count(*(void **)((int)node + 0x10));
  if ((*(byte *)((int)node + 0x18) & 4) != 0) {
    iVar3 = iVar3 + -1;
  }
  cVar1 = avl_iter(*(void **)((int)node + 0x10),(char *)0x0,(void *)0x0);
  cVar2 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar1),(void *)0x0);
  piVar4 = (int *)CONCAT31(extraout_var_00,cVar2);
  iVar5 = cg_depth;
  while (piVar4 != (int *)0x0) {
    cg_depth = iVar5;
    if ((void *)*piVar4 != node) {
      iVar3 = iVar3 + -1;
      *(uint *)(&DAT_00505280 + iVar5 * 4) = (uint)(0 < iVar3);
      iVar6 = 1;
      do {
        iVar7 = 1;
        if (0 < iVar5) {
          piVar8 = &DAT_00505284;
          bVar9 = iVar5 == 1;
          do {
            if ((bVar9) || (*piVar8 == 1)) {
              fmt = &DAT_004d7ac0;
            }
            else {
              fmt = &DAT_004d7ab4;
            }
            prof_printf(fmt);
            iVar7 = iVar7 + 1;
            piVar8 = piVar8 + 1;
            bVar9 = iVar7 == cg_depth;
          } while (iVar7 <= cg_depth);
        }
        prof_printf(&DAT_004d7a80);
        iVar6 = iVar6 + -1;
        iVar5 = cg_depth;
      } while (iVar6 != 0);
      cg_print_tree_node((void *)*piVar4);
    }
    cVar2 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar1),(void *)0x0);
    iVar5 = cg_depth;
    piVar4 = (int *)CONCAT31(extraout_var_01,cVar2);
  }
  cg_depth = iVar5;
  return;
}


/* ==== cg_ps_call_tree @ 00482000 ==== */

void cg_ps_call_tree(void)

{
  char cVar1;
  char cVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int unaff_ESI;
  int unaff_retaddr;
  void *node;
  
  ps_new_page();
  prof_printf(&DAT_004d7b28);
  ps_font(0,2,10);
  prof_printf(&DAT_004d7af0);
  ps_font(6,unaff_ESI,unaff_retaddr);
  ps_font(0,0,9);
  cg_depth = 0;
  cg_ps_y = 700;
  cVar1 = avl_iter(*(void **)(prof_ctx + 0x3514),(char *)0x0,(void *)0x0);
  cVar2 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar1),(void *)0x0);
  node = (void *)CONCAT31(extraout_var_00,cVar2);
  while (node != (void *)0x0) {
    if ((*(byte *)((int)node + 0x18) & 0x20) == 0) {
      cg_ps_tree_node(node,0x28);
    }
    cVar2 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar1),(void *)0x0);
    node = (void *)CONCAT31(extraout_var_01,cVar2);
  }
  ps_font(6,unaff_ESI,unaff_retaddr);
  prof_printf(&DAT_004d7acc);
  return;
}


/* ==== cg_ps_tree_node @ 004820d0 ==== */

void __cdecl cg_ps_tree_node(void *node,int x)

{
  int iVar1;
  char cVar2;
  char cVar3;
  uint uVar4;
  int extraout_EAX;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  uint uVar6;
  int iVar7;
  int *piVar5;
  
  cg_depth = cg_depth + 1;
  if (((*(byte *)((int)node + 0x18) & 0x20) == 0) &&
     ((x < 0x1c2 ||
      (uVar4 = prof_list_count(*(void **)((int)node + 0x10)),
      uVar6 = *(uint *)((int)node + 0x18) >> 2 & 1, uVar4 == uVar6 || (int)(uVar4 - uVar6) < 0)))) {
    iVar7 = 1;
  }
  else {
    iVar7 = 0;
  }
  cg_ps_tree_box(x,node,iVar7);
  if ((iVar7 == 1) && (prof_list_remove(*(void **)((int)node + 0x10),node), extraout_EAX != 0)) {
    prof_printf(&DAT_004d7b64,x + -10,cg_ps_y + -10);
  }
  cg_ps_y = cg_ps_y + -0x1e;
  if (cg_ps_y < 0x14) {
    cg_ps_tree_flush();
    cg_ps_y = 700;
  }
  if (iVar7 == 1) {
    iVar7 = prof_list_count(*(void **)((int)node + 0x10));
    if ((*(byte *)((int)node + 0x18) & 4) != 0) {
      iVar7 = iVar7 + -1;
    }
    cVar2 = avl_iter(*(void **)((int)node + 0x10),(char *)0x0,(void *)0x0);
    cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar2),(void *)0x0);
    piVar5 = (int *)CONCAT31(extraout_var_00,cVar3);
    iVar1 = cg_depth;
    while (cg_depth = iVar1, piVar5 != (int *)0x0) {
      if ((void *)*piVar5 != node) {
        iVar7 = iVar7 + -1;
        *(int *)(&DAT_00505248 + iVar1 * 4) = cg_ps_y;
        *(int *)(&DAT_00505220 + iVar1 * 4) = x + 0x4b;
        *(uint *)(&DAT_00505280 + iVar1 * 4) = (uint)(0 < iVar7);
        cg_ps_tree_node((void *)*piVar5,x + 0x4b);
        if (*(int *)(&DAT_00505280 + cg_depth * 4) == 1) {
          prof_printf(&DAT_004d7b50,x,*(int *)(&DAT_00505248 + cg_depth * 4) + 0x1e,x,cg_ps_y);
        }
      }
      cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar2),(void *)0x0);
      iVar1 = cg_depth;
      piVar5 = (int *)CONCAT31(extraout_var_01,cVar3);
    }
  }
  cg_depth = cg_depth + -1;
  return;
}


/* ==== cg_ps_tree_flush @ 00482250 ==== */

void cg_ps_tree_flush(void)

{
  int iVar1;
  int *piVar2;
  
  if (0 < cg_depth) {
    piVar2 = (int *)(&DAT_00505248 + cg_depth * 4);
    iVar1 = cg_depth;
    do {
      if (*(int *)(&DAT_00505280 + iVar1 * 4) == 1) {
        prof_printf(&DAT_004d7b50,*(int *)(&DAT_00505220 + iVar1 * 4) + -0x4b,*piVar2 + 0x1e,
                    *(int *)(&DAT_00505220 + iVar1 * 4) + -0x4b,cg_ps_y);
        *piVar2 = 700;
      }
      iVar1 = iVar1 + -1;
      piVar2 = piVar2 + -1;
    } while (0 < iVar1);
  }
  ps_new_page();
  return;
}


/* ==== cg_ps_tree_box @ 004822b0 ==== */

void __cdecl cg_ps_tree_box(int x,void *node,int expanded)

{
  if (1 < cg_depth) {
    prof_printf(&DAT_004d7b84,0x1e,0x4b,x,cg_ps_y);
  }
  prof_printf(&DAT_004d7b70,*(undefined4 *)((int)node + 4),expanded,x,cg_ps_y);
  if (expanded == 1) {
    *(uint *)((int)node + 0x18) = *(uint *)((int)node + 0x18) | 0x20;
  }
  return;
}


/* ==== cg_ps_call_graph @ 00482310 ==== */

void cg_ps_call_graph(void)

{
  void *node;
  int unaff_ESI;
  int unaff_EDI;
  int local_8;
  undefined4 local_4;
  
  node = *(void **)(prof_ctx + 0x3518);
  ps_new_page();
  prof_printf(&DAT_004d7bf4);
  ps_font(0,2,10);
  prof_printf(&DAT_004d7bbc);
  ps_font(6,unaff_EDI,unaff_ESI);
  cgl_layout_node(node);
  if ((*(int *)((int)node + 0x34) < 0x65) && (*(int *)((int)node + 0x38) < 0x65)) {
    local_8 = (int)(0x226 / (longlong)*(int *)((int)node + 0x34));
    local_4 = (undefined4)(0x28a / (longlong)*(int *)((int)node + 0x38));
    ps_font(0,4,7);
    cg_ps_graph_node(node,0,0,&local_8);
    ps_font(6,unaff_EDI,unaff_ESI);
  }
  else {
    prof_printf(&DAT_004d7b98);
  }
  prof_printf(&DAT_004d2254);
  return;
}


/* ==== cgl_layout_node @ 004823e0 ==== */

void __cdecl cgl_layout_node(void *node)

{
  void *pvVar1;
  char cVar2;
  char cVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int iVar5;
  int *piVar4;
  
  if (*(int *)((int)node + 0x3c) == 0) {
    iVar5 = 0;
    *(undefined4 *)((int)node + 0x3c) = 2;
    cVar2 = avl_iter(*(void **)((int)node + 0x10),(char *)0x0,(void *)0x0);
    cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar2),(void *)0x0);
    piVar4 = (int *)CONCAT31(extraout_var_00,cVar3);
    while (piVar4 != (int *)0x0) {
      pvVar1 = (void *)*piVar4;
      if ((pvVar1 != node) && (*(int *)((int)pvVar1 + 0x3c) == 0)) {
        *(void **)((int)pvVar1 + 0x48) = node;
        iVar5 = iVar5 + 1;
        cgl_layout_node((void *)*piVar4);
      }
      cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar2),(void *)0x0);
      piVar4 = (int *)CONCAT31(extraout_var_01,cVar3);
    }
    if (iVar5 == 0) {
      *(undefined4 *)((int)node + 0x34) = 1;
      *(undefined4 *)((int)node + 0x38) = 1;
      return;
    }
    cgl_init_shape(node);
    iVar5 = iVar5 + -1;
    if (0 < iVar5) {
      do {
        cgl_compute_edges();
        cgl_place_child();
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    cgl_finish();
    *(undefined4 *)((int)node + 0x34) = DAT_005057b0;
    *(int *)((int)node + 0x38) = DAT_005057b4 + 1;
  }
  return;
}


/* ==== cgl_init_shape @ 00482490 ==== */

void __cdecl cgl_init_shape(void *node)

{
  int iVar1;
  void *prev;
  void *prev_00;
  void *prev_01;
  int *local_4;
  
  cgl_next_child(node,&node);
  iVar1 = cgl_next_child((void *)0x0,&local_4);
  while (iVar1 == 0) {
    if (local_4[1] * *local_4 - *(int *)((int)node + 4) * *(int *)node != 0 &&
        *(int *)((int)node + 4) * *(int *)node <= local_4[1] * *local_4) {
      node = local_4;
    }
    iVar1 = cgl_next_child((void *)0x0,&local_4);
  }
  *(int *)((int)node + 8) = 1;
  *(int *)((int)node + 0xc) = 0;
  *(int *)((int)node + 0x10) = 0;
  DAT_005057a8 = 0;
  DAT_005057ac = 0;
  DAT_005057b0 = *(int *)node;
  DAT_005057b4 = *(int *)((int)node + 4);
  DAT_005057b8 = *(int *)node * *(int *)((int)node + 4);
  cgl_add_point((void *)0x0,0,0);
  cgl_add_point(prev,0,*(int *)((int)node + 4));
  cgl_add_point(prev_00,*(int *)node,*(int *)((int)node + 4));
  cgl_add_point(prev_01,*(int *)node,0);
  return;
}


/* ==== cgl_next_child @ 00482580 ==== */

int __cdecl cgl_next_child(void *node,void **out)

{
  char cVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  
  if (node != (void *)0x0) {
    DAT_005052ac = node;
  }
  if (DAT_005052b0 == (int *)0x0) {
    cVar1 = avl_iter(*(void **)((int)DAT_005052ac + 0x10),(char *)0x0,(void *)0x0);
    DAT_005052b4 = (char *)CONCAT31(extraout_var,cVar1);
  }
  cVar1 = avl_iter((void *)0x0,DAT_005052b4,(void *)0x0);
  DAT_005052b0 = (int *)CONCAT31(extraout_var_00,cVar1);
  if (DAT_005052b0 != (int *)0x0) {
    do {
      if (*(void **)(*DAT_005052b0 + 0x48) == DAT_005052ac) {
        *out = (void *)(*DAT_005052b0 + 0x34);
        return 0;
      }
      cVar1 = avl_iter((void *)0x0,DAT_005052b4,(void *)0x0);
      DAT_005052b0 = (int *)CONCAT31(extraout_var_01,cVar1);
    } while (DAT_005052b0 != (int *)0x0);
    return 1;
  }
  return 1;
}


/* ==== cgl_add_point @ 00482610 ==== */

void __cdecl cgl_add_point(void *prev,int x,int y)

{
  int iVar1;
  int *extraout_EAX;
  
  prof_malloc(0x3c);
  *extraout_EAX = x;
  extraout_EAX[1] = y;
  if (prev == (void *)0x0) {
    DAT_005057a0 = prev;
    extraout_EAX[5] = (int)extraout_EAX;
    extraout_EAX[4] = (int)extraout_EAX;
    DAT_005057a4 = extraout_EAX;
  }
  else {
    iVar1 = *(int *)((int)prev + 0x10);
    extraout_EAX[5] = (int)prev;
    extraout_EAX[4] = iVar1;
    *(int **)(iVar1 + 0x14) = extraout_EAX;
    *(int **)((int)prev + 0x10) = extraout_EAX;
  }
  DAT_005057a0 = (void *)((int)DAT_005057a0 + 1);
  if (x <= DAT_005057a8) {
    DAT_005057a8 = x;
  }
  if (y <= DAT_005057ac) {
    DAT_005057ac = y;
  }
  if (DAT_005057b0 <= x) {
    DAT_005057b0 = x;
  }
  if (DAT_005057b4 <= y) {
    DAT_005057b4 = y;
  }
  return;
}


/* ==== cgl_compute_edges @ 004826a0 ==== */

void cgl_compute_edges(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  piVar1 = DAT_005057a4;
  iVar3 = DAT_005057a0;
  if (0 < DAT_005057a0) {
    do {
      piVar1[6] = *piVar1 - *(int *)piVar1[5];
      piVar1[7] = piVar1[1] - ((int *)piVar1[5])[1];
      piVar1[8] = *(int *)piVar1[4] - *piVar1;
      piVar1[9] = ((int *)piVar1[4])[1] - piVar1[1];
      if (piVar1[6] == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = ((piVar1[6] < 1) - 1 & 2) - 1;
      }
      piVar1[10] = iVar2;
      if (piVar1[7] == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = ((piVar1[7] < 1) - 1 & 2) - 1;
      }
      piVar1[0xb] = iVar2;
      if (piVar1[8] == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = ((piVar1[8] < 1) - 1 & 2) - 1;
      }
      piVar1[0xc] = iVar2;
      if (piVar1[9] == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = ((piVar1[9] < 1) - 1 & 2) - 1;
      }
      piVar1[0xd] = iVar2;
      if (((((piVar1[10] < 0) && (piVar1[0xd] < 0)) || ((piVar1[0xb] < 0 && (0 < piVar1[0xc])))) ||
          ((0 < piVar1[10] && (0 < piVar1[0xd])))) || ((0 < piVar1[0xb] && (piVar1[0xc] < 0)))) {
        iVar2 = 0;
      }
      else {
        iVar2 = 1;
      }
      piVar1[0xe] = iVar2;
      iVar2 = (-(uint)(iVar2 != 0) & 2) - 1;
      piVar1[2] = (int)((float)*piVar1 - (float)((piVar1[0xc] - piVar1[10]) * iVar2) * -0.5);
      iVar3 = iVar3 + -1;
      piVar1[3] = (int)((float)piVar1[1] - (float)((piVar1[0xd] - piVar1[0xb]) * iVar2) * -0.5);
      piVar1 = (int *)piVar1[4];
    } while (iVar3 != 0);
  }
  return;
}


/* ==== cgl_place_child @ 00482800 ==== */

void cgl_place_child(void)

{
  int iVar1;
  void **ppvVar2;
  undefined4 *puVar3;
  void *local_1a0;
  int local_19c;
  undefined1 local_198 [60];
  undefined1 local_15c [60];
  undefined1 local_120 [64];
  float local_e0;
  undefined4 local_d0 [48];
  float local_10;
  
  local_10 = -9999.0;
  iVar1 = cgl_next_child((void *)0x0,&local_1a0);
  while (iVar1 == 0) {
    if (*(int *)((int)local_1a0 + 8) != 1) {
      iVar1 = cgl_next_candidate(&local_1a0);
      while (iVar1 == 0) {
        iVar1 = cgl_segments_hit(*(void **)(local_19c + 0x14),local_198);
        if ((((iVar1 == 0) && (iVar1 = cgl_segments_hit(local_198,local_15c), iVar1 == 0)) &&
            (iVar1 = cgl_segments_hit(local_15c,local_120), iVar1 == 0)) &&
           ((iVar1 = cgl_segments_hit(local_120,*(void **)(local_19c + 0x10)), iVar1 == 0 &&
            (cgl_score(&local_1a0), local_10 < local_e0)))) {
          ppvVar2 = &local_1a0;
          puVar3 = local_d0;
          for (iVar1 = 0x34; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar3 = *ppvVar2;
            ppvVar2 = ppvVar2 + 1;
            puVar3 = puVar3 + 1;
          }
        }
        iVar1 = cgl_next_candidate(&local_1a0);
      }
    }
    iVar1 = cgl_next_child((void *)0x0,&local_1a0);
  }
  cgl_commit_shape(local_d0);
  return;
}


/* ==== cgl_commit_shape @ 00482930 ==== */

void __cdecl cgl_commit_shape(void *cand)

{
  int iVar1;
  void *extraout_EAX;
  void *prev;
  void *extraout_EAX_00;
  int iVar2;
  int *extraout_EAX_01;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  int local_8;
  int local_4;
  
  cgl_del_point(*(void **)((int)cand + 4));
  piVar4 = (int *)((int)cand + 8);
  iVar6 = 3;
  prev = extraout_EAX;
  do {
    cgl_add_point(prev,*piVar4,piVar4[1]);
    piVar4 = piVar4 + 0xf;
    iVar6 = iVar6 + -1;
    prev = extraout_EAX_00;
  } while (iVar6 != 0);
  if (0 < DAT_005057a0) {
    local_4 = DAT_005057a0;
    piVar4 = DAT_005057a4;
    do {
      iVar6 = *piVar4;
      iVar3 = *(int *)piVar4[5];
      if (iVar6 == iVar3) {
        local_8 = 0;
      }
      else {
        local_8 = ((iVar6 == iVar3 || iVar6 - iVar3 < 0) - 1 & 2) - 1;
      }
      iVar3 = piVar4[1];
      iVar2 = ((int *)piVar4[5])[1];
      if (iVar3 == iVar2) {
        iVar2 = 0;
      }
      else {
        iVar2 = ((iVar3 == iVar2 || iVar3 - iVar2 < 0) - 1 & 2) - 1;
      }
      piVar5 = (int *)piVar4[4];
      iVar1 = *piVar5;
      if (iVar1 == iVar6) {
        iVar6 = 0;
      }
      else {
        iVar6 = ((iVar1 == iVar6 || iVar1 - iVar6 < 0) - 1 & 2) - 1;
      }
      iVar1 = piVar5[1];
      if (iVar1 == iVar3) {
        iVar3 = 0;
      }
      else {
        iVar3 = ((iVar1 == iVar3 || iVar1 - iVar3 < 0) - 1 & 2) - 1;
      }
      if (((local_8 == 0) && (iVar6 == 0)) || ((iVar2 == 0 && (iVar3 == 0)))) {
        cgl_del_point(piVar4);
        piVar5 = extraout_EAX_01;
      }
      local_4 = local_4 + -1;
      piVar4 = piVar5;
    } while (local_4 != 0);
  }
  DAT_005057b8 = DAT_005057b8 + (*(int **)cand)[1] * **(int **)cand;
  *(undefined4 *)(*(int *)cand + 8) = 1;
  iVar6 = *(int *)cand;
  *(undefined4 *)(iVar6 + 0xc) = *(undefined4 *)((int)cand + 0xc4);
  *(undefined4 *)(iVar6 + 0x10) = *(undefined4 *)((int)cand + 200);
  return;
}


/* ==== cgl_del_point @ 00482a70 ==== */

void __cdecl cgl_del_point(void *pt)

{
  int iVar1;
  void *pvVar2;
  
  iVar1 = *(int *)((int)pt + 0x10);
  pvVar2 = *(void **)((int)pt + 0x14);
  *(void **)(iVar1 + 0x14) = pvVar2;
  *(int *)((int)pvVar2 + 0x10) = iVar1;
  if (DAT_005057a4 == pt) {
    DAT_005057a4 = pvVar2;
  }
  DAT_005057a0 = DAT_005057a0 + -1;
  dsp_free(pt);
  return;
}


/* ==== cgl_segments_hit @ 00482ab0 ==== */

int __cdecl cgl_segments_hit(void *p,void *q)

{
  float fVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  bool bVar6;
  int iVar7;
  int local_4;
  
  local_4 = DAT_005057a0;
  if (DAT_005057a0 < 0) {
    return 0;
  }
  iVar2 = *(int *)p;
  iVar7 = DAT_005057a4;
  do {
    iVar3 = *(int *)(iVar7 + 0x10);
    if (iVar2 == *(int *)q) {
      if (*(float *)(iVar3 + 8) <= *(float *)(iVar7 + 8)) {
        fVar1 = *(float *)(iVar3 + 8);
      }
      else {
        fVar1 = *(float *)(iVar7 + 8);
      }
      if ((float)iVar2 < fVar1) goto LAB_00482c44;
      if (*(float *)(iVar7 + 8) <= *(float *)(iVar3 + 8)) {
        fVar1 = *(float *)(iVar3 + 8);
      }
      else {
        fVar1 = *(float *)(iVar7 + 8);
      }
      if (fVar1 < (float)iVar2) goto LAB_00482c44;
      fVar4 = (float)*(int *)((int)p + 4);
      fVar1 = (float)*(int *)((int)q + 4);
      fVar5 = fVar1;
      if (fVar4 < fVar1) {
        fVar5 = fVar4;
      }
      if (*(float *)(iVar7 + 0xc) < fVar5) goto LAB_00482c44;
      if (fVar4 <= fVar1) {
        fVar4 = fVar1;
      }
      if (fVar4 < *(float *)(iVar7 + 0xc)) goto LAB_00482c44;
      bVar6 = true;
    }
    else {
      if (*(float *)(iVar3 + 0xc) <= *(float *)(iVar7 + 0xc)) {
        fVar1 = *(float *)(iVar3 + 0xc);
      }
      else {
        fVar1 = *(float *)(iVar7 + 0xc);
      }
      if (fVar1 <= (float)*(int *)((int)p + 4)) {
        if (*(float *)(iVar7 + 0xc) <= *(float *)(iVar3 + 0xc)) {
          fVar1 = *(float *)(iVar3 + 0xc);
        }
        else {
          fVar1 = *(float *)(iVar7 + 0xc);
        }
        if ((float)*(int *)((int)p + 4) <= fVar1) {
          fVar4 = (float)iVar2;
          fVar1 = (float)*(int *)q;
          fVar5 = fVar1;
          if (fVar4 < fVar1) {
            fVar5 = fVar4;
          }
          if (fVar5 <= *(float *)(iVar7 + 8)) {
            if (fVar4 <= fVar1) {
              fVar4 = fVar1;
            }
            if (*(float *)(iVar7 + 8) <= fVar4) {
              bVar6 = true;
              goto LAB_00482c46;
            }
          }
        }
      }
LAB_00482c44:
      bVar6 = false;
    }
LAB_00482c46:
    if (bVar6) {
      return 1;
    }
    local_4 = local_4 + -1;
    iVar7 = iVar3;
    if (local_4 < 0) {
      return 0;
    }
  } while( true );
}


/* ==== cgl_next_candidate @ 00482c80 ==== */

int __cdecl cgl_next_candidate(void *cand)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (DAT_005052b8 == 0) {
    DAT_005052b8 = DAT_005057a0 + 1;
    *(undefined4 *)((int)cand + 4) = DAT_005057a4;
    DAT_00505278 = 3;
  }
  if (1 < DAT_00505278) {
    DAT_005052b8 = DAT_005052b8 + -1;
    if (DAT_005052b8 == 0) {
      return 1;
    }
    DAT_00505274 = *(int **)(*(int *)((int)cand + 4) + 0x10);
    *(int **)((int)cand + 4) = DAT_00505274;
    *(int *)((int)cand + 0xcc) = DAT_00505274[0xe];
    DAT_00505278 = -((-(uint)(DAT_00505274[0xe] != 0) & 2) - 1);
  }
  iVar2 = DAT_00505274[0xb] * DAT_00505278;
  iVar4 = DAT_00505274[10] * DAT_00505278;
  iVar5 = DAT_00505274[0xc];
  if (*(int *)((int)cand + 0xcc) != 0) {
    iVar5 = iVar5 * DAT_00505278;
  }
  iVar3 = DAT_00505274[0xd];
  if (*(int *)((int)cand + 0xcc) != 0) {
    iVar3 = iVar3 * DAT_00505278;
  }
  piVar1 = *(int **)cand;
  *(int *)((int)cand + 8) = iVar4 * *piVar1 + *DAT_00505274;
  *(int *)((int)cand + 0xc) = iVar2 * piVar1[1] + DAT_00505274[1];
  *(int *)((int)cand + 0x44) = (iVar5 + iVar4) * *piVar1 + *DAT_00505274;
  *(int *)((int)cand + 0x48) = (iVar2 + iVar3) * piVar1[1] + DAT_00505274[1];
  *(int *)((int)cand + 0x80) = iVar5 * *piVar1 + *DAT_00505274;
  *(int *)((int)cand + 0x84) = iVar3 * piVar1[1] + DAT_00505274[1];
  if (*(int *)((int)cand + 0xcc) == 0) {
    iVar2 = (DAT_00505274[10] <= DAT_00505274[0xc]) - 1;
    iVar5 = (DAT_00505274[0xb] <= DAT_00505274[0xd]) - 1;
  }
  else {
    iVar5 = -DAT_00505278;
    if ((DAT_00505274[10] == iVar5) || (DAT_00505274[0xc] == iVar5)) {
      iVar2 = -1;
    }
    else {
      iVar2 = 0;
    }
    if ((DAT_00505274[0xb] == iVar5) || (DAT_00505274[0xd] == iVar5)) {
      iVar5 = -1;
    }
    else {
      iVar5 = 0;
    }
  }
  *(int *)((int)cand + 0xc4) = iVar2 * *piVar1 + *DAT_00505274;
  *(int *)((int)cand + 200) = iVar5 * piVar1[1] + DAT_00505274[1];
  *(int *)((int)cand + 0xbc) = DAT_00505278;
  DAT_00505278 = DAT_00505278 + 2;
  return 0;
}


/* ==== cgl_score @ 00482e50 ==== */

void __cdecl cgl_score(void *cand)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_14;
  int local_10;
  
  iVar8 = *(int *)((int)cand + 8);
  iVar4 = DAT_005057a8;
  if (iVar8 <= DAT_005057a8) {
    iVar4 = iVar8;
  }
  iVar6 = *(int *)((int)cand + 0x44);
  iVar5 = *(int *)((int)cand + 0x80);
  iVar3 = iVar6;
  if (iVar5 <= iVar6) {
    iVar3 = iVar5;
  }
  if (iVar4 < iVar3) {
    local_14 = iVar8;
    if (DAT_005057a8 < iVar8) {
      local_14 = DAT_005057a8;
    }
  }
  else {
    local_14 = iVar6;
    if (iVar5 <= iVar6) {
      local_14 = iVar5;
    }
  }
  iVar4 = *(int *)((int)cand + 0xc);
  iVar3 = DAT_005057ac;
  if (iVar4 <= DAT_005057ac) {
    iVar3 = iVar4;
  }
  iVar1 = *(int *)((int)cand + 0x48);
  iVar2 = *(int *)((int)cand + 0x84);
  iVar7 = iVar1;
  if (iVar2 <= iVar1) {
    iVar7 = iVar2;
  }
  if (iVar3 < iVar7) {
    local_10 = iVar4;
    if (DAT_005057ac < iVar4) {
      local_10 = DAT_005057ac;
    }
  }
  else {
    local_10 = iVar1;
    if (iVar2 <= iVar1) {
      local_10 = iVar2;
    }
  }
  iVar3 = iVar8;
  if (iVar8 < DAT_005057b0) {
    iVar3 = DAT_005057b0;
  }
  iVar7 = iVar6;
  if (iVar6 <= iVar5) {
    iVar7 = iVar5;
  }
  if (iVar7 < iVar3) {
    iVar6 = iVar8;
    if (iVar8 < DAT_005057b0) {
      iVar6 = DAT_005057b0;
    }
  }
  else if (iVar6 <= iVar5) {
    iVar6 = iVar5;
  }
  iVar8 = DAT_005057b4;
  if (DAT_005057b4 <= iVar4) {
    iVar8 = iVar4;
  }
  iVar5 = iVar1;
  if (iVar1 <= iVar2) {
    iVar5 = iVar2;
  }
  if (iVar5 < iVar8) {
    if (iVar4 < DAT_005057b4) {
      iVar4 = DAT_005057b4;
    }
  }
  else {
    iVar4 = iVar1;
    if (iVar1 <= iVar2) {
      iVar4 = iVar2;
    }
  }
  iVar5 = (iVar6 - local_14) - (iVar4 - local_10);
  iVar8 = iVar5;
  if (iVar5 < 1) {
    iVar8 = -iVar5;
  }
  if (iVar5 == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = ((iVar5 < 1) - 1 & 2) - 1;
  }
  *(float *)((int)cand + 0xc0) =
       (float)((iVar5 - (iVar4 - local_10) * (iVar6 - local_14)) - iVar8 * iVar8);
  return;
}


/* ==== cgl_finish @ 00482fb0 ==== */

void cgl_finish(void)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  void *p;
  int iVar4;
  int iVar5;
  void *local_4;
  
  iVar3 = DAT_005057b0 - DAT_005057a8;
  iVar4 = DAT_005057b4 - DAT_005057ac;
  iVar2 = cgl_next_child((void *)0x0,&local_4);
  iVar5 = DAT_005057a0;
  while (DAT_005057a0 = iVar5, iVar2 == 0) {
    *(int *)((int)local_4 + 0xc) = *(int *)((int)local_4 + 0xc) - DAT_005057a8;
    *(int *)((int)local_4 + 0x10) = *(int *)((int)local_4 + 0x10) - DAT_005057ac;
    iVar2 = cgl_next_child((void *)0x0,&local_4);
    iVar5 = DAT_005057a0;
  }
  DAT_005057a8 = 0;
  DAT_005057ac = 0;
  p = *(void **)(DAT_005057a4 + 0x10);
  DAT_005057b0 = iVar3;
  DAT_005057b4 = iVar4;
  if (0 < iVar5) {
    do {
      pvVar1 = *(void **)((int)p + 0x10);
      dsp_free(p);
      iVar5 = iVar5 + -1;
      p = pvVar1;
    } while (iVar5 != 0);
  }
  return;
}


/* ==== cg_ps_graph_node @ 00483070 ==== */

void __cdecl cg_ps_graph_node(void *node,int x,int y,int *size)

{
  void *node_00;
  char cVar1;
  char cVar2;
  int iVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int iVar5;
  longlong lVar6;
  int *piVar4;
  
  if ((*(uint *)((int)node + 0x18) & 0x40) == 0) {
    *(uint *)((int)node + 0x18) = *(uint *)((int)node + 0x18) | 0x40;
    iVar5 = *size;
    iVar3 = rand();
    lVar6 = _ftol();
    *(int *)((int)node + 0x4c) = ((iVar3 % (iVar5 / 3) + (int)lVar6) - iVar5 / 3) + 0x32;
    iVar5 = size[1];
    iVar3 = rand();
    lVar6 = _ftol();
    *(int *)((int)node + 0x50) = ((iVar3 % (iVar5 / 3) + (int)lVar6) - iVar5 / 3) + 0x32;
    cVar1 = avl_iter(*(void **)((int)node + 0x10),(char *)0x0,(void *)0x0);
    cVar2 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar1),(void *)0x0);
    iVar5 = 0;
    piVar4 = (int *)CONCAT31(extraout_var_00,cVar2);
    while (piVar4 != (int *)0x0) {
      node_00 = (void *)*piVar4;
      if (node == node_00) {
        prof_printf(&DAT_004d7c28,*(undefined4 *)((int)node + 0x4c),
                    *(undefined4 *)((int)node + 0x50));
      }
      else {
        iVar5 = iVar5 + 1;
        cg_ps_graph_node(node_00,*(int *)((int)node_00 + 0x40) + x,*(int *)((int)node_00 + 0x44) + y
                         ,size);
        cg_ps_graph_arrow(*(int *)((int)node + 0x4c),*(int *)((int)node + 0x50),
                          *(int *)(*piVar4 + 0x4c),*(int *)(*piVar4 + 0x50));
      }
      cVar2 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar1),(void *)0x0);
      piVar4 = (int *)CONCAT31(extraout_var_01,cVar2);
    }
    prof_printf(&DAT_004d7c14,*(undefined4 *)((int)node + 4),((iVar5 < 1) - 1 & 0x13) - 0xc,
                *(undefined4 *)((int)node + 0x4c),*(undefined4 *)((int)node + 0x50));
  }
  return;
}


/* ==== cg_ps_graph_arrow @ 004831f0 ==== */

void __cdecl cg_ps_graph_arrow(int x1,int y1,int x2,int y2)

{
  double dVar1;
  double dVar2;
  double dVar3;
  int va3;
  float10 extraout_ST0;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  float10 extraout_ST1;
  longlong lVar8;
  
  if (x1 == x2) {
    if (y1 < y2) {
      va3 = y2 + -2;
    }
    else {
      va3 = y2 + 2;
    }
  }
  else {
    dVar1 = (double)(y2 - y1) / (double)(x2 - x1);
    dVar3 = (double)y2 - dVar1 * (double)x2;
    dVar2 = (dVar3 * dVar1 - (double)x2) - dVar1 * (double)y2;
    lVar8 = _ftol();
    fVar4 = (SQRT((float10)(int)lVar8) - (float10)(dVar2 + dVar2)) /
            (float10)(double)(extraout_ST1 + extraout_ST1);
    fVar5 = (-extraout_ST0 - SQRT((float10)(int)lVar8)) /
            (float10)(double)(extraout_ST1 + extraout_ST1);
    fVar6 = (float10)x1 - fVar4;
    fVar4 = (float10)y1 - (float10)(double)(fVar4 * (float10)dVar1 + (float10)dVar3);
    fVar7 = (float10)x1 - (float10)(double)fVar5;
    fVar5 = (float10)y1 - (float10)(double)(fVar5 * (float10)dVar1 + (float10)dVar3);
    if (fVar5 * (float10)(double)fVar5 + fVar7 * (float10)(double)fVar7 <=
        fVar4 * (float10)(double)fVar4 + fVar6 * (float10)(double)fVar6) {
      lVar8 = _ftol();
      x2 = (int)lVar8;
    }
    else {
      lVar8 = _ftol();
      x2 = (int)lVar8;
    }
    lVar8 = _ftol();
    va3 = (int)lVar8;
  }
  prof_printf(&DAT_004d7c34,va3 - y1,x2 - x1,x2,va3,x1,y1);
  return;
}


