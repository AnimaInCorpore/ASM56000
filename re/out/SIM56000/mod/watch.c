/* ==== watch_update_all @ 0043e9b0 ==== */

void watch_update_all(void)

{
  void *watch;
  
  for (watch = *(void **)(cur_sim + 0x3fa8); watch != (void *)0x0;
      watch = *(void **)((int)watch + 0x120)) {
    watch_display(watch);
  }
  return;
}


/* ==== cmd_watch_h0 @ 0043e9e0 ==== */

void cmd_watch_h0(void)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  uint *node;
  uint *extraout_EAX;
  uint extraout_EAX_00;
  uint uVar4;
  uint *puVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  uint *puVar9;
  
  uVar3 = (DAT_004a93ea != 'w') - 1 & DAT_004a96c0;
  bVar2 = false;
  if (uVar3 == 0) {
    iVar6 = 2;
    node = (uint *)0x0;
    uVar3 = list_next_id((void *)(cur_sim + 0x3e88));
  }
  else {
    iVar6 = 3;
    node = (uint *)list_find_id((void *)(cur_sim + 0x3e88),uVar3);
  }
  if (node == (uint *)0x0) {
    bVar2 = true;
    dsp_alloc(0x124,0);
    if (extraout_EAX == (uint *)0x0) {
      return;
    }
    extraout_EAX[0x48] = 0;
    *extraout_EAX = uVar3;
    extraout_EAX[0x45] = 0;
    *(undefined1 *)(extraout_EAX + 1) = 0;
    extraout_EAX[0x41] = 0;
    extraout_EAX[0x42] = 0;
    extraout_EAX[0x43] = 0;
    extraout_EAX[0x44] = 0;
    node = extraout_EAX;
  }
  if ((&g_tok_type)[iVar6] == 'r') {
    uVar3 = *(uint *)(&g_tok_val + iVar6 * 0x28);
  }
  else {
    uVar3 = 0xffffffff;
  }
  node[0x42] = uVar3;
  if (uVar3 != 0xffffffff) {
    iVar6 = iVar6 + 1;
  }
  uVar3 = 0xffffffff;
  pcVar7 = &g_cmdline + (&g_tok_start)[iVar6];
  do {
    pcVar8 = pcVar7;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  puVar5 = (uint *)(pcVar8 + -uVar3);
  puVar9 = node + 1;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar9 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar9 = puVar9 + 1;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(char *)puVar9 = (char)*puVar5;
    puVar5 = (uint *)((int)puVar5 + 1);
    puVar9 = (uint *)((int)puVar9 + 1);
  }
  switch((&g_tok_type)[iVar6]) {
  case 0x43:
    if ((void *)node[0x45] != (void *)0x0) {
      cdb_free_expr((void *)node[0x45]);
    }
    node[0x41] = 0;
    parse_c_expression((char *)(node + 1));
    node[0x45] = extraout_EAX_00;
    node[0x46] = cdb_lookup_cache_depth;
    node[0x47] = cdb_lookup_cache_sym;
    break;
  default:
    node[0x41] = 2;
    break;
  case 0x46:
    node[0x41] = 3;
    break;
  case 0x67:
    node[0x41] = 1;
  }
  if (bVar2) {
    list_insert_sorted((void *)(cur_sim + 0x3e88),node);
  }
  return;
}


/* ==== cmd_watch_h1 @ 0043ebe0 ==== */

void cmd_watch_h1(void)

{
  uint va1;
  
  va1 = (DAT_004a93ea != 'w') - 1 & DAT_004a96c0;
  if (va1 != 0) {
    cmd_watch_h1_sub_43cbb0(cur_sim + 0x3e88,va1);
    return;
  }
  cmd_watch_h1_sub_43cc10(cur_sim + 0x3e88);
  return;
}


/* ==== cmd_watch_h2 @ 0043ec30 ==== */

void cmd_watch_h2(void)

{
  uint wnum;
  
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  wnum = (DAT_004a93ea != 'w') - 1 & DAT_004a96c0;
  if (wnum != 0) {
    watch_update_one(cur_sim + 0x3e88,wnum);
    return;
  }
  watch_update_all();
  return;
}


/* ==== watch_update_one @ 0043ec80 ==== */

void __cdecl watch_update_one(int dev,int wnum)

{
  void *watch;
  
  watch = (void *)list_find_id((void *)dev,wnum);
  if (watch != (void *)0x0) {
    watch_display(watch);
  }
  return;
}


/* ==== watch_display @ 0043eca0 ==== */

void __cdecl watch_display(void *watch)

{
  char cVar1;
  undefined1 *puVar2;
  char *pcVar3;
  int extraout_EAX;
  undefined3 extraout_var;
  char *extraout_EAX_00;
  int iVar4;
  char *extraout_EAX_01;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  char *pcVar9;
  char *pcVar10;
  char *local_214;
  uint local_210;
  void *local_20c;
  int local_208;
  int local_204;
  char local_200;
  char local_1ff [255];
  char local_100 [256];
  
  local_214 = (char *)0x0;
  local_20c = (void *)0x0;
  switch(*(undefined4 *)((int)watch + 0x108)) {
  case 0:
    puVar2 = &DAT_004b29b0;
    break;
  case 1:
    puVar2 = &DAT_004c6ab4;
    break;
  case 2:
    puVar2 = &DAT_004c6ab0;
    break;
  case 3:
    puVar2 = &DAT_004c6aa8;
    break;
  case 4:
    puVar2 = &DAT_004c6aac;
    break;
  default:
    puVar2 = &DAT_004c1644;
  }
  sprintf(local_100,s___d__s__s_004c6a9c,*(undefined4 *)watch,puVar2,(char *)((int)watch + 4));
  uVar5 = 0xffffffff;
  pcVar3 = local_100;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  local_210 = ~uVar5 - 1;
  if (0x28 < (int)local_210) {
    uVar6 = 0xffffffff;
    pcVar3 = &DAT_004c5890;
    do {
      pcVar9 = pcVar3;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar9 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar9;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    iVar7 = -1;
    pcVar3 = local_100;
    do {
      pcVar10 = pcVar3;
      if (iVar7 == 0) break;
      iVar7 = iVar7 + -1;
      pcVar10 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar10;
    } while (cVar1 != '\0');
    pcVar3 = pcVar9 + -uVar6;
    pcVar9 = pcVar10 + -1;
    for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar6 = uVar6 & 3; local_210 = ~uVar5, uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar9 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar9 = pcVar9 + 1;
    }
  }
  iVar7 = *(int *)((int)watch + 0x104);
  if (iVar7 == 1) {
    periph_find_reg(*(int *)(cur_dev + 4),(char *)((int)watch + 4),&local_204,&local_208);
    iVar7 = *(int *)((int)watch + 0x108);
    if (iVar7 == -1) {
      iVar7 = 3;
    }
    fmt_register(local_204,local_208,iVar7,&local_200);
    if ((local_200 == ' ') && (local_200 = local_1ff[0], local_1ff[0] != '\0')) {
      pcVar3 = &local_200;
      do {
        pcVar9 = pcVar3 + 2;
        pcVar3 = pcVar3 + 1;
        *pcVar3 = *pcVar9;
      } while (*pcVar9 != '\0');
    }
  }
  else if ((iVar7 == 2) || (iVar7 == 3)) {
    watch_format_value(watch,&local_200);
  }
  else if (iVar7 == 0) {
    cdb_frame_first();
    cdb_frame_current();
    cdb_frame_pc();
    iVar7 = cdb_pc_in_function(*(int *)((int)watch + 0x11c),*(int *)((int)watch + 0x118));
    if (iVar7 == 0) {
      pcVar3 = s_Expression_out_of_scope_004c6a64;
      pcVar9 = &local_200;
      for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar3;
        pcVar3 = pcVar3 + 4;
        pcVar9 = pcVar9 + 4;
      }
    }
    else if (*(int *)((int)watch + 0x114) != 0) {
      cdb_set_quiet(1);
      iVar7 = eval_tree(*(void **)((int)watch + 0x114));
      cdb_set_quiet(0);
      if (iVar7 == 1) {
        cdb_saved_pop();
        if (extraout_EAX == 0) {
          local_20c = (void *)0x0;
        }
        else {
          local_20c = *(void **)(extraout_EAX + 0x10);
        }
      }
      if (local_20c == (void *)0x0) {
        pcVar3 = s_Error_evaluating_C_expression_004c6a7c;
        pcVar9 = &local_200;
        for (iVar7 = 7; iVar7 != 0; iVar7 = iVar7 + -1) {
          *(undefined4 *)pcVar9 = *(undefined4 *)pcVar3;
          pcVar3 = pcVar3 + 4;
          pcVar9 = pcVar9 + 4;
        }
        *(undefined2 *)pcVar9 = *(undefined2 *)pcVar3;
      }
      else {
        cVar1 = cdb_value_to_string(local_20c,*(int *)((int)watch + 0x108));
        local_214 = (char *)CONCAT31(extraout_var,cVar1);
      }
    }
  }
  if (local_214 == (char *)0x0) {
    local_214 = &local_200;
  }
  uVar5 = 0xffffffff;
  pcVar3 = local_214;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  if (watch_line_buf == (void *)0x0) {
    watch_line_buf_size = ~uVar5 + 0x28 + local_210;
    dsp_alloc(watch_line_buf_size + 1,0);
    watch_line_buf = extraout_EAX_00;
  }
  else {
    iVar7 = ~uVar5 + 0x27 + local_210;
    iVar4 = (int)(watch_line_buf_size + (watch_line_buf_size >> 0x1f & 0xfU)) >> 4;
    if (iVar4 <= iVar7) {
      for (; iVar4 = watch_line_buf_size, watch_line_buf_size <= iVar7;
          watch_line_buf_size = watch_line_buf_size * 2) {
      }
    }
    watch_line_buf_size = iVar4;
    dsp_realloc(watch_line_buf,watch_line_buf_size + 1);
    watch_line_buf = extraout_EAX_01;
  }
  uVar5 = 0xffffffff;
  pcVar3 = local_100;
  do {
    pcVar9 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar9 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar9;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar3 = pcVar9 + -uVar5;
  pcVar9 = watch_line_buf;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar9 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar9 = pcVar9 + 1;
  }
  if ((int)local_210 < 0x29) {
    for (; (int)local_210 < 0x28; local_210 = local_210 + 1) {
      watch_line_buf[local_210] = ' ';
    }
    pcVar3 = watch_line_buf + 0x28;
  }
  else {
    pcVar3 = watch_line_buf + local_210;
  }
  uVar5 = 0xffffffff;
  do {
    pcVar9 = local_214;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar9 = local_214 + 1;
    cVar1 = *local_214;
    local_214 = pcVar9;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar9 = pcVar9 + -uVar5;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar3 = *(undefined4 *)pcVar9;
    pcVar9 = pcVar9 + 4;
    pcVar3 = pcVar3 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar3 = *pcVar9;
    pcVar9 = pcVar9 + 1;
    pcVar3 = pcVar3 + 1;
  }
  cdb_print_wrapped(watch_line_buf,(char *)0x0,(char *)0x0,0x28,0);
  return;
}


