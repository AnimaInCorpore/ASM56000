/* ==== cmd_view_parse @ 00445030 ==== */

undefined ** cmd_view_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(2);
  if (iVar1 == 0) {
    iVar1 = parm_keyword1(2,&DAT_004b29b4);
    if (iVar1 == 0) {
      iVar1 = parm_keyword1(2,&DAT_004c7e04);
      if (iVar1 == 0) {
        iVar1 = parm_keyword1(2,&DAT_004c5574);
        if (iVar1 == 0) goto LAB_0044508b;
      }
    }
    iVar1 = parm_check_too_many(3);
    if (iVar1 == 0) goto LAB_0044508b;
  }
  iVar2 = 0;
LAB_0044508b:
  if (iVar2 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_view_h0_004c6fb8 + iVar2 * 2;
}


/* ==== dbg_next_label @ 004450a0 ==== */

int __cdecl dbg_next_label(int idx,char **desc)

{
  byte bVar1;
  byte *pbVar2;
  char *pcVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  void *pvVar9;
  byte *pbVar10;
  undefined1 *puVar11;
  bool bVar12;
  int local_c;
  byte *local_8;
  byte *local_4;
  
  iVar8 = 0;
  local_4 = (byte *)0x0;
  if (idx == 0) {
    local_8 = &empty_str;
  }
  else {
    local_8 = (byte *)dbg_sym_name((void *)(*(int *)(cur_sim + 0x3fdc) + idx * 0x20));
  }
  local_c = 0;
  iVar6 = local_c;
  if (0 < *(int *)(cur_sim + 0x3fd8)) {
    do {
      pvVar9 = (void *)(*(int *)(cur_sim + 0x3fdc) + iVar8 * 0x20);
      iVar6 = *(int *)((int)pvVar9 + 0x18);
      if (((((iVar6 == 0xd5) || (iVar6 == 0xd3)) || (iVar6 == 0xd6)) ||
          ((iVar6 == 0xd2 || (iVar6 == 0xd7)))) || (iVar6 == 2)) {
        pbVar2 = (byte *)dbg_sym_name(pvVar9);
        pbVar4 = pbVar2;
        pbVar10 = local_8;
        do {
          bVar1 = *pbVar4;
          bVar12 = bVar1 < *pbVar10;
          if (bVar1 != *pbVar10) {
LAB_00445163:
            iVar5 = (1 - (uint)bVar12) - (uint)(bVar12 != 0);
            goto LAB_00445168;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar4[1];
          bVar12 = bVar1 < pbVar10[1];
          if (bVar1 != pbVar10[1]) goto LAB_00445163;
          pbVar4 = pbVar4 + 2;
          pbVar10 = pbVar10 + 2;
        } while (bVar1 != 0);
        iVar5 = 0;
LAB_00445168:
        if ((iVar5 == 0) && (iVar6 = iVar8, idx < iVar8)) break;
        if (0 < iVar5) {
          pbVar4 = pbVar2;
          pbVar10 = local_4;
          if (local_4 != (byte *)0x0) {
            do {
              bVar1 = *pbVar4;
              bVar12 = bVar1 < *pbVar10;
              if (bVar1 != *pbVar10) {
LAB_004451a4:
                iVar6 = (1 - (uint)bVar12) - (uint)(bVar12 != 0);
                goto LAB_004451a9;
              }
              if (bVar1 == 0) break;
              bVar1 = pbVar4[1];
              bVar12 = bVar1 < pbVar10[1];
              if (bVar1 != pbVar10[1]) goto LAB_004451a4;
              pbVar4 = pbVar4 + 2;
              pbVar10 = pbVar10 + 2;
            } while (bVar1 != 0);
            iVar6 = 0;
LAB_004451a9:
            if (-1 < iVar6) goto LAB_004451b5;
          }
          local_c = iVar8;
          local_4 = pbVar2;
        }
      }
LAB_004451b5:
      iVar8 = iVar8 + 1 + *(int *)((int)pvVar9 + 0x1c);
      iVar6 = local_c;
    } while (iVar8 < *(int *)(cur_sim + 0x3fd8));
  }
  local_c = iVar6;
  if (local_c != 0) {
    pvVar9 = (void *)(*(int *)(cur_sim + 0x3fdc) + local_c * 0x20);
    if ((*(int *)((int)pvVar9 + 0x18) == 0xd7) ||
       (puVar11 = &DAT_004c1644, *(int *)((int)pvVar9 + 0x18) == 0xd6)) {
      puVar11 = &DAT_004c7b28;
    }
    pcVar3 = dbg_sym_name(pvVar9);
    if (*(int *)((int)pvVar9 + 0x10) < 0) {
      iVar8 = 0;
    }
    else {
      iVar8 = *(int *)(*(int *)(cur_sim + 0x4014) + 0x1c + *(int *)((int)pvVar9 + 0x10) * 0x20);
    }
    if (iVar8 < 1) {
      pcVar7 = s_global_004c7af4;
    }
    else {
      pcVar7 = (char *)(*(int *)(*(int *)(cur_sim + 0x3fdc) + 8 + iVar8 * 0x20) +
                       *(int *)(cur_sim + 0x3fe4));
    }
    sprintf(&g_label_desc_buf,s__s__20_20s__4s____8lx_section____004c7e08,puVar11,pcVar3,
            (&g_space_names)[*(int *)((int)pvVar9 + 0xc)],*(undefined4 *)((int)pvVar9 + 8),pcVar7);
    *desc = &g_label_desc_buf;
  }
  return local_c;
}


/* ==== cmd_list_h0 @ 00445290 ==== */

void cmd_list_h0(void)

{
  if (*(int *)(cur_sim + 0x4400) == 0) {
    *(uint *)(cur_sim + 0x4400) = (*(int *)(cur_sim + 0x3fd8) != 0) + 1;
  }
  win_update(0x7fff);
  return;
}


/* ==== cmd_list_h1 @ 004452d0 ==== */

void cmd_list_h1(void)

{
  if (*(int *)(cur_sim + 0x4400) == 0) {
    *(uint *)(cur_sim + 0x4400) = (*(int *)(cur_sim + 0x3fd8) != 0) + 1;
  }
  win_update(1 - text_rows);
  return;
}


/* ==== cmd_list_h2 @ 00445310 ==== */

void cmd_list_h2(void)

{
  if (*(int *)(cur_sim + 0x4400) == 0) {
    *(uint *)(cur_sim + 0x4400) = (*(int *)(cur_sim + 0x3fd8) != 0) + 1;
  }
  win_update(text_rows + -1);
  return;
}


/* ==== cmd_list_h3 @ 00445350 ==== */

void cmd_list_h3(void)

{
  uint line;
  int fileno;
  int iStack_8;
  undefined4 uStack_4;
  
  if ((g_io_id_arg < 0) || (*(int *)(cur_sim + 0x3fdc) == 0)) {
    fileno = -1;
  }
  else {
    fileno = *(int *)(g_io_id_arg * 0x20 + 0x14 + *(int *)(cur_sim + 0x3fdc));
  }
  *(int *)(cur_sim + 0x3ff8) = fileno;
  *(uint *)(cur_sim + 0x3ffc) = DAT_004a96c0;
  line = DAT_004a96c0;
  if (*(int *)(cur_sim + 0x4400) == 0) {
    *(uint *)(cur_sim + 0x4400) = (*(int *)(cur_sim + 0x3fd8) != 0) + 1;
  }
  if (*(int *)(cur_sim + 0x4400) == 1) {
    dbg_line_to_addr(fileno,line,&iStack_8);
    *(int *)(cur_sim + 0x4008) = iStack_8;
    *(undefined4 *)(cur_sim + 0x400c) = uStack_4;
  }
  win_update(0);
  return;
}


/* ==== cmd_list_h4 @ 00445410 ==== */

void cmd_list_h4(void)

{
  undefined4 va0;
  undefined4 va1;
  
  va1 = DAT_004a96d0;
  va0 = DAT_004a96cc;
  if (*(int *)(cur_sim + 0x4400) == 0) {
    *(uint *)(cur_sim + 0x4400) = (*(int *)(cur_sim + 0x3fd8) != 0) + 1;
  }
  cmd_list_h4_sub_445450(va0,va1);
  return;
}


/* ==== cmd_list_h4_sub_445450 @ 00445450 ==== */

void cmd_list_h4_sub_445450(uint param_1,int param_2)

{
  if ((g_win_buf == (char *)0x0) && (win_buf_alloc(), g_win_buf == (char *)0x0)) {
    return;
  }
  cur_dev = *(int **)(dev_tab + cur_dev_index * 4);
  cur_itype = *(undefined4 *)(itype_tab + *cur_dev * 4);
  cur_sim = *(int *)(dev_state_tab + cur_dev_index * 4);
  cur_dtype = *(undefined4 *)(chiptype_tab + *cur_dev * 4);
  if (*(int *)(cur_sim + 0x4400) == 1) {
    asmwin_scroll(0x7fff,param_1,param_2);
  }
  else {
    srcwin_scroll(0x7fff,param_1,param_2);
  }
  win_status_line();
  screen_fill_rows(g_win_buf);
  return;
}


/* ==== cmd_list_parse @ 00445500 ==== */

undefined ** cmd_list_parse(void)

{
  int iVar1;
  int extraout_EAX;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(2);
  if (iVar1 == 0) {
    iVar1 = parm_check_too_many(3);
    if (iVar1 != 0) {
      iVar1 = parm_keyword1(2,&DAT_004c7e34);
      if (iVar1 == 0) {
        iVar1 = parm_keyword1(2,&DAT_004c7e30);
        if (iVar1 == 0) {
          iVar1 = parm_keyword1(2,&DAT_004c7e2c);
          if (iVar1 == 0) {
            parse_list_spec(2);
            if (extraout_EAX == 0) {
              iVar1 = parm_match_space_cur(2);
              if (iVar1 != 0) {
                iVar2 = 4;
              }
            }
            else {
              iVar2 = 3;
            }
          }
          else {
            iVar2 = 2;
          }
        }
        else {
          iVar2 = 1;
        }
      }
      else {
        iVar2 = 0;
      }
    }
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_list_h0_004c7050 + iVar2 * 2;
}


/* ==== parse_list_spec @ 004455b0 ==== */

void __cdecl parse_list_spec(int tok)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  undefined *puVar4;
  int iVar5;
  char *s;
  char *pcVar6;
  int iVar7;
  int local_18;
  int local_10;
  char *local_8;
  int local_4;
  
  local_4 = (&g_tok_start)[tok];
  local_10 = *(int *)(cur_sim + 0x3ff8);
  puVar4 = &g_cmdline;
  iVar7 = 0;
  local_18 = 1;
  bVar3 = false;
  bVar2 = false;
  if ((&g_cmdline)[local_4] == '@') {
    puVar4 = &DAT_004a92e9;
  }
  pcVar6 = puVar4 + local_4;
  cVar1 = *pcVar6;
  do {
    if (cVar1 == '\0') {
LAB_00445618:
      s = pcVar6;
      if ((*pcVar6 != '\0') && (iVar5 = dbg_find_source_file(pcVar6), -1 < iVar5)) {
        bVar2 = true;
        s = pcVar6 + iVar7 + (uint)(cVar1 == '@');
        local_10 = iVar5;
      }
      pcVar6[iVar7] = cVar1;
      if (*s == '\0') {
        if (bVar2) {
          local_18 = 1;
          bVar3 = true;
        }
      }
      else {
        local_18 = strtol(s,&local_8,10);
        if (*local_8 == '\0') {
          if (local_18 < 1) {
            local_18 = 1;
          }
          bVar3 = true;
        }
      }
      if ((*(int *)(cur_sim + 0x3fdc) == 0) || (*(int *)(cur_sim + 0x4020) == 0)) {
        bVar3 = false;
      }
      if (bVar3) {
        (&g_tok_type)[tok] = 0x53;
        iVar7 = *(int *)(*(int *)(cur_sim + 0x4020) + local_10 * 0xc);
        if (iVar7 < local_18) {
          local_18 = iVar7;
        }
        iVar7 = tok * 0x28;
        *(int *)(&g_tok_val + iVar7) = local_18;
        iVar5 = *(int *)(cur_sim + 0x3fd8);
        pcVar6 = dbg_fileno_to_name(local_10);
        iVar5 = dbg_find_file_sym(pcVar6,iVar5);
        *(int *)(&DAT_004a9674 + iVar7) = iVar5;
        *(int *)(&DAT_004a9678 + iVar7) = local_10;
      }
      if (!bVar3) {
        parm_errmsg = s_Invalid_line_number_004c7df0;
        g_err_tok = local_4;
      }
      return;
    }
    if (cVar1 == '@') {
      pcVar6[iVar7] = '\0';
      goto LAB_00445618;
    }
    cVar1 = pcVar6[iVar7 + 1];
    iVar7 = iVar7 + 1;
  } while( true );
}


/* ==== cmd_finish_h0 @ 00445750 ==== */

void cmd_finish_h0(void)

{
  int iVar1;
  int dev;
  
  *(undefined4 *)(cur_sim + 0x28) = 1;
  *(undefined4 *)(cur_sim + 0x2c) = 0;
  *(undefined4 *)(cur_sim + 0x34) = 0;
  iVar1 = step_classify_insn(*(int *)(cur_dev + 0x1c));
  dev = 0;
  *(int *)(cur_sim + 0x34) = iVar1;
  iVar1 = cur_dev_index;
  if (0 < max_devices) {
    do {
      if ((*(int *)(dev_tab + dev * 4) != 0) &&
         ((*(byte *)(*(int *)(dev_tab + dev * 4) + 0x44) & 0x20) == 0)) {
        dev_select(dev);
        cdb_free_frames();
      }
      dev = dev + 1;
    } while (dev < max_devices);
  }
  dev_select(iVar1);
  periph_reset();
  *(undefined4 *)(cur_sim + 0x40) = 1;
  return;
}


/* ==== cmd_finish_parse @ 004457f0 ==== */

uint cmd_finish_parse(void)

{
  int iVar1;
  
  iVar1 = parm_check_too_many(2);
  return -(uint)(iVar1 != 0) & 0x4c70c0;
}


/* ==== cmd_up_h0 @ 00445810 ==== */

void cmd_up_h0(void)

{
  uint uVar1;
  undefined4 *extraout_EAX;
  undefined4 *extraout_EAX_00;
  int iVar2;
  
  cdb_frame_current();
  DAT_005024a8 = extraout_EAX;
  if (extraout_EAX == (undefined4 *)0x0) {
    cdb_build_backtrace();
    cdb_frame_current();
    DAT_005024a8 = extraout_EAX_00;
    if (extraout_EAX_00 == (undefined4 *)0x0) {
      return;
    }
  }
  iVar2 = parm_check_too_many(2);
  if (iVar2 == 0) {
    if ((g_io_id_arg != 0) || (uVar1 = DAT_004a96c0, 0x7fff < DAT_004a96c0)) {
      DAT_004a96c0 = DAT_004a96c0 | 0xffff0000;
      DAT_005024a8 = (undefined4 *)0x0;
      uVar1 = DAT_004a96c0;
    }
    for (; uVar1 != 0; uVar1 = uVar1 - 1) {
      if (DAT_005024a8 == (undefined4 *)0x0) goto LAB_004458ea;
      DAT_005024a8 = (undefined4 *)DAT_005024a8[6];
    }
  }
  else {
    DAT_005024a8 = (undefined4 *)DAT_005024a8[6];
  }
  if (DAT_005024a8 == (undefined4 *)0x0) {
LAB_004458ea:
    iVar2 = parm_check_too_many(2);
    if (iVar2 != 0) {
      sim_error(s_Can_t_go_up_any_further_004c7f7c);
      return;
    }
    sprintf(&DAT_005023a8,s_Can_t_go_up__ld_times_004c7f64,DAT_004a96c0);
    sim_error(&DAT_005023a8);
  }
  else {
    cdb_set_frame_current(DAT_005024a8);
    iVar2 = *(int *)(cur_sim + 0x4400);
    if (iVar2 == 0) {
      cdb_print_wrapped((char *)*DAT_005024a8,&DAT_004c6554,&DAT_004c61b0,4,0);
      return;
    }
    if ((iVar2 == 1) || (iVar2 == 2)) {
      win_update(0x7fff);
      return;
    }
  }
  return;
}


/* ==== cmd_up_parse @ 00445930 ==== */

uint cmd_up_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(2);
  if (iVar1 == 0) {
    iVar1 = parm_number_or_end(2);
    if (iVar1 == 0) goto LAB_00445960;
    iVar1 = parm_check_too_many(3);
    if (iVar1 == 0) goto LAB_00445960;
  }
  iVar2 = 0;
LAB_00445960:
  return -(uint)(iVar2 != -1) & 0x4c7e68;
}


/* ==== cmd_unlock_parse @ 00445970 ==== */

undefined ** cmd_unlock_parse(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = -1;
  iVar1 = parm_need_more(2);
  if (iVar1 != 0) {
    iVar2 = parm_need_more(3);
    iVar1 = DAT_004a9470;
    if (iVar2 != 0) {
      iVar2 = devtype_find(&g_cmdline + DAT_004a9470,&g_cmdline + DAT_004a9474);
      if (iVar2 < 0) {
        g_err_tok = iVar1;
        parm_errmsg = s_Invalid_Device_Name_or_Password_004c80dc;
      }
      else {
        iVar3 = 0;
      }
    }
  }
  if (iVar3 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_unlock_h0_004c7fc0 + iVar3 * 2;
}


/* ==== cmd_type_h0 @ 004459e0 ==== */

void cmd_type_h0(void)

{
  byte bVar1;
  char cVar2;
  void *node;
  int iVar3;
  void *extraout_EAX;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  ulong uVar4;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  char *pcVar5;
  char cVar6;
  uint uVar7;
  uint uVar8;
  undefined *va4;
  void *v;
  void *pvVar9;
  char *pcVar10;
  char *pcVar11;
  uint uStack_1bc;
  int iStack_1b8;
  undefined *puStack_1b4;
  void *pvStack_1b0;
  int iStack_1ac;
  uint uStack_1a8;
  char acStack_1a4 [100];
  undefined1 auStack_140 [24];
  uint uStack_128;
  uint uStack_114;
  char acStack_100 [256];
  
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  uStack_1a8 = 0;
  iStack_1ac = 0;
  if (cdb_arch == 0x2c9) {
    puStack_1b4 = &DAT_004c8308;
  }
  else if (cdb_arch == 0x2c8) {
LAB_00445a4a:
    puStack_1b4 = &DAT_004b2930;
  }
  else if ((cdb_arch == 0x2c5) || (cdb_arch == 0x2ca)) {
    if ((cdb_arch == 0x2c8) || (puStack_1b4 = &DAT_004b2948, cdb_arch == 0x2ca)) goto LAB_00445a4a;
  }
  else {
    puStack_1b4 = &DAT_004b2948;
  }
  parse_c_expression(&g_cmdline + DAT_004a9470);
  if (node == (void *)0x0) {
    return;
  }
  pvStack_1b0 = node;
  iVar3 = eval_tree(node);
  if (iVar3 == 1) {
    cdb_saved_pop();
    pvVar9 = extraout_EAX;
    pvStack_1b0 = extraout_EAX;
    if (extraout_EAX == (void *)0x0) {
      v = (void *)0x0;
    }
    else {
      v = *(void **)((int)extraout_EAX + 0x10);
    }
  }
  else {
    if (iVar3 == 2) {
      return;
    }
    v = (void *)0x0;
    pvVar9 = node;
  }
  if (v == (void *)0x0) goto LAB_00445db0;
  cVar2 = cdb_type_to_string(v);
  uVar7 = 0xffffffff;
  pcVar5 = (char *)CONCAT31(extraout_var,cVar2);
  do {
    pcVar11 = pcVar5;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar11 = pcVar5 + 1;
    cVar2 = *pcVar5;
    pcVar5 = pcVar11;
  } while (cVar2 != '\0');
  uVar7 = ~uVar7;
  pcVar5 = pcVar11 + -uVar7;
  pcVar11 = acStack_100;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar11 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar11 = pcVar11 + 1;
  }
  if (*(short *)((int)v + 0x3c) == 1) {
    iVar3 = *(int *)((int)v + 0x24);
    if ((iVar3 == 4) || (iVar3 == 0x11)) {
      cVar2 = cdb_reg_name(*(int *)((int)v + 0x20),*(ulong *)((int)v + 0x18));
      pcVar5 = (char *)CONCAT31(extraout_var_02,cVar2);
      if (pcVar5 == (char *)0x0) {
        pcVar5 = s__unknown__004c8288;
      }
      sprintf(acStack_1a4,s_in_register__s_004c8278,pcVar5);
LAB_00445d6e:
      uVar7 = 0xffffffff;
      pcVar5 = acStack_1a4;
      do {
        pcVar11 = pcVar5;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar11 = pcVar5 + 1;
        cVar2 = *pcVar5;
        pcVar5 = pcVar11;
      } while (cVar2 != '\0');
      uVar7 = ~uVar7;
      iVar3 = -1;
      pcVar5 = acStack_100;
      do {
        pcVar10 = pcVar5;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar10 = pcVar5 + 1;
        cVar2 = *pcVar5;
        pcVar5 = pcVar10;
      } while (cVar2 != '\0');
      pcVar5 = pcVar11 + -uVar7;
      pcVar11 = pcVar10 + -1;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar11 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar11 = pcVar11 + 1;
      }
    }
    else if (iVar3 != -0x80000000) {
      if (iVar3 == 0x12) {
        iStack_1b8 = *(int *)((int)v + 0x1c);
        if (iStack_1b8 == 3) {
          iStack_1b8 = 2;
        }
        cdb_sym_to_value(auStack_140,*(int *)((int)v + 0x28));
        uVar7 = uStack_128 % cdb_word_bits;
        uStack_1bc = uStack_128 / cdb_word_bits + *(int *)(*(int *)((int)pvVar9 + 0x10) + 0x18);
        cVar2 = cdb_memspace_name(iStack_1b8,uStack_1bc & cdb_addr_mask);
        va4 = &DAT_004c8300;
        if (uStack_114 < 2) {
          va4 = &DAT_004c82fc;
        }
        sprintf(acStack_1a4,s_starting_at__s_0x_lx__bit__lu__w_004c82c8,
                CONCAT31(extraout_var_00,cVar2),uStack_1bc,uVar7,uStack_114,va4);
        goto LAB_00445d6e;
      }
      uStack_1bc = *(uint *)((int)v + 0x18);
      iStack_1b8 = *(int *)((int)v + 0x1c);
      if ((*(int *)((int)v + 0x24) == 1) || (*(int *)((int)v + 0x24) == 9)) {
        cdb_frame_slot(iStack_1b8,uStack_1bc,&iStack_1b8,&uStack_1bc);
      }
      uStack_1bc = uStack_1bc & cdb_addr_mask;
      if (iStack_1b8 == 3) {
        uVar7 = *(uint *)((int)v + 0x20);
        bVar1 = (byte)uVar7;
        while ((bVar1 & 0x30) == 0x30) {
          uVar7 = uVar7 & 0x1000f | uVar7 >> 2 & 0x3ffebff0;
          bVar1 = (byte)uVar7;
        }
        if (((((((((byte)uVar7 & 0x30) == 0x10) || (uVar7 == 2)) || (uVar7 == 0xc)) ||
              ((uVar7 == 3 || (uVar7 == 0xd)))) ||
             ((uVar7 == 4 || ((uVar7 == 0xb || (uVar7 == 10)))))) || (uVar7 == 0xe)) ||
           ((uVar7 == 6 && (cdb_arch == 0x2c6)))) {
          iStack_1b8 = 2;
        }
      }
      if ((*(int *)((int)v + 0x24) == 1) || (iVar3 = iStack_1ac, *(int *)((int)v + 0x24) == 9)) {
        uVar4 = cdb_frame_fp();
        uStack_1a8 = uVar4 & cdb_addr_mask;
        iVar3 = uStack_1bc - uStack_1a8;
      }
      cVar2 = cdb_memspace_name(iStack_1b8,uStack_1bc & cdb_addr_mask);
      if ((uStack_1a8 == 0) && (iVar3 == 0)) {
        sprintf(acStack_1a4,s_at__s_0x_lx_004c82b8,CONCAT31(extraout_var_01,cVar2),
                uStack_1bc & cdb_addr_mask);
      }
      else {
        if (iVar3 < 0) {
          iVar3 = -iVar3;
          cVar6 = '-';
          iStack_1ac = iVar3;
        }
        else {
          cVar6 = '+';
        }
        sprintf(acStack_1a4,s_at__s_0x_lx___s__0x_lx__c0x_lx__004c8294,
                CONCAT31(extraout_var_01,cVar2),uStack_1bc,puStack_1b4,uStack_1a8,(int)cVar6,iVar3);
      }
      uVar7 = 0xffffffff;
      pcVar5 = acStack_1a4;
      do {
        pcVar11 = pcVar5;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar11 = pcVar5 + 1;
        cVar2 = *pcVar5;
        pcVar5 = pcVar11;
      } while (cVar2 != '\0');
      uVar7 = ~uVar7;
      iVar3 = -1;
      pcVar5 = acStack_100;
      do {
        pcVar10 = pcVar5;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar10 = pcVar5 + 1;
        cVar2 = *pcVar5;
        pcVar5 = pcVar10;
      } while (cVar2 != '\0');
      pcVar5 = pcVar11 + -uVar7;
      pcVar11 = pcVar10 + -1;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar7 = uVar7 & 3; pvVar9 = pvStack_1b0, uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar11 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar11 = pcVar11 + 1;
      }
    }
  }
  log_echo(acStack_100,1);
LAB_00445db0:
  cdb_free_expr(pvVar9);
  return;
}


/* ==== cmd_type_parse @ 00445dd0 ==== */

undefined ** cmd_type_parse(void)

{
  int iVar1;
  undefined **ppuVar2;
  
  ppuVar2 = (undefined **)0x0;
  iVar1 = parm_brace_block(2);
  if (iVar1 != 0) {
    iVar1 = parm_check_too_many(3);
    if (iVar1 != 0) {
      iVar1 = parm_type_expr(2);
      if (iVar1 != 0) {
        ppuVar2 = &PTR_cmd_type_h0_004c8130;
      }
    }
  }
  return ppuVar2;
}


/* ==== cmd_trace_h0 @ 00445e10 ==== */

void cmd_trace_h0(void)

{
  int dev;
  undefined4 uVar1;
  int dev_00;
  
  *(undefined4 *)(cur_sim + 0x3c) = 0;
  uVar1 = DAT_004a96c0;
  if (DAT_004a93ea != 'i') {
    uVar1 = 1;
  }
  dev_00 = 0;
  *(undefined4 *)(cur_sim + 0x28) = uVar1;
  *(undefined4 *)(cur_sim + 0x2c) = 0;
  *(undefined4 *)(cur_sim + 0x34) = 2;
  dev = cur_dev_index;
  if (0 < max_devices) {
    do {
      if ((*(int *)(dev_tab + dev_00 * 4) != 0) &&
         ((*(byte *)(*(int *)(dev_tab + dev_00 * 4) + 0x44) & 0x20) == 0)) {
        dev_select(dev_00);
        cdb_free_frames();
      }
      dev_00 = dev_00 + 1;
    } while (dev_00 < max_devices);
  }
  dev_select(dev);
  periph_reset();
  *(undefined4 *)(cur_sim + 0x40) = 1;
  return;
}


/* ==== cmd_trace_h2 @ 00445ed0 ==== */

void cmd_trace_h2(void)

{
  int dev;
  undefined4 uVar1;
  int dev_00;
  
  *(undefined4 *)(cur_sim + 0x3c) = 1;
  uVar1 = DAT_004a96c0;
  if (DAT_004a93ea != 'i') {
    uVar1 = 1;
  }
  dev_00 = 0;
  *(undefined4 *)(cur_sim + 0x28) = uVar1;
  *(undefined4 *)(cur_sim + 0x2c) = 0;
  *(undefined4 *)(cur_sim + 0x34) = 2;
  dev = cur_dev_index;
  if (0 < max_devices) {
    do {
      if ((*(int *)(dev_tab + dev_00 * 4) != 0) &&
         ((*(byte *)(*(int *)(dev_tab + dev_00 * 4) + 0x44) & 0x20) == 0)) {
        dev_select(dev_00);
        cdb_free_frames();
      }
      dev_00 = dev_00 + 1;
    } while (dev_00 < max_devices);
  }
  dev_select(dev);
  periph_reset();
  *(undefined4 *)(cur_sim + 0x40) = 1;
  return;
}


/* ==== cmd_trace_h1 @ 00445ef0 ==== */

void cmd_trace_h1(void)

{
  *(undefined4 *)(cur_sim + 0x3c) = 0;
  cmd_step_exec(0);
  return;
}


/* ==== cmd_step_exec @ 00445f10 ==== */

void __cdecl cmd_step_exec(int arg)

{
  undefined4 uVar1;
  int iVar2;
  int dev;
  
  uVar1 = DAT_004a96c0;
  if (DAT_004a93ea != 'i') {
    uVar1 = 1;
  }
  *(undefined4 *)(cur_sim + 0x28) = uVar1;
  *(undefined4 *)(cur_sim + 0x2c) = 0;
  if ((arg == 1) ||
     ((arg == 0 && ((*(int *)(cur_sim + 0x4400) == 2 || (*(int *)(cur_sim + 0x4404) != 0)))))) {
    iVar2 = step_mode_at_pc(1);
  }
  else {
    iVar2 = 1;
  }
  *(int *)(cur_sim + 0x34) = iVar2;
  iVar2 = cur_dev_index;
  dev = 0;
  if (0 < max_devices) {
    do {
      if ((*(int *)(dev_tab + dev * 4) != 0) &&
         ((*(byte *)(*(int *)(dev_tab + dev * 4) + 0x44) & 0x20) == 0)) {
        dev_select(dev);
        cdb_free_frames();
      }
      dev = dev + 1;
    } while (dev < max_devices);
  }
  dev_select(iVar2);
  periph_reset();
  *(undefined4 *)(cur_sim + 0x40) = 1;
  return;
}


/* ==== cmd_trace_h3 @ 00445fe0 ==== */

void cmd_trace_h3(void)

{
  *(undefined4 *)(cur_sim + 0x3c) = 1;
  cmd_step_exec(0);
  return;
}


/* ==== cmd_trace_h6 @ 00446000 ==== */

void cmd_trace_h6(void)

{
  *(undefined4 *)(cur_sim + 0x3c) = 0;
  cmd_step_exec(2);
  return;
}


/* ==== cmd_trace_h7 @ 00446020 ==== */

void cmd_trace_h7(void)

{
  *(undefined4 *)(cur_sim + 0x3c) = 1;
  cmd_step_exec(2);
  return;
}


/* ==== cmd_trace_h4 @ 00446040 ==== */

void cmd_trace_h4(void)

{
  *(undefined4 *)(cur_sim + 0x3c) = 0;
  cmd_step_exec(1);
  return;
}


/* ==== cmd_trace_h5 @ 00446060 ==== */

void cmd_trace_h5(void)

{
  *(undefined4 *)(cur_sim + 0x3c) = 1;
  cmd_step_exec(1);
  return;
}


/* ==== cmd_trace_parse @ 00446080 ==== */

int cmd_trace_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(2);
  if (iVar1 == 0) {
    iVar1 = parm_check_too_many(3);
    if (iVar1 == 0) {
      iVar1 = parm_check_too_many(4);
      if (iVar1 == 0) {
        iVar1 = parm_check_too_many(5);
        if (iVar1 == 0) goto LAB_004462ab;
        iVar1 = parm_count_expr(2);
        if (iVar1 == 0) goto LAB_004462ab;
        iVar1 = parm_keyword1(4,&DAT_004c6aa8);
        if (iVar1 == 0) goto LAB_004462ab;
        iVar1 = parm_keyword1(3,&DAT_004a8688);
        if (iVar1 != 0) {
          iVar2 = 5;
          goto LAB_004462ab;
        }
        iVar1 = parm_keyword1(3,&DAT_004c7dec);
        if (iVar1 != 0) {
          iVar2 = 7;
          goto LAB_004462ab;
        }
        iVar1 = parm_keyword1(3,&DAT_004c8958);
        if (iVar1 == 0) goto LAB_004462ab;
      }
      else {
        iVar1 = parm_keyword1(3,&DAT_004c6aa8);
        if (iVar1 == 0) {
          iVar1 = parm_count_expr(2);
          if (iVar1 != 0) {
            iVar1 = parm_keyword1(3,&DAT_004a8688);
            if (iVar1 == 0) {
              iVar1 = parm_keyword1(3,&DAT_004c7dec);
              if (iVar1 == 0) {
                iVar1 = parm_keyword1(3,&DAT_004c8958);
                if (iVar1 != 0) {
                  iVar2 = 0;
                }
              }
              else {
                iVar2 = 6;
              }
            }
            else {
              iVar2 = 4;
            }
          }
          goto LAB_004462ab;
        }
        iVar1 = parm_keyword1(2,&DAT_004a8688);
        if (iVar1 != 0) {
          iVar2 = 5;
          goto LAB_004462ab;
        }
        iVar1 = parm_keyword1(2,&DAT_004c8958);
        if (iVar1 == 0) {
          iVar1 = parm_keyword1(2,&DAT_004c7dec);
          if (iVar1 == 0) {
            iVar1 = parm_count_expr(2);
            if (iVar1 != 0) {
              iVar2 = 3;
            }
          }
          else {
            iVar2 = 7;
          }
          goto LAB_004462ab;
        }
      }
      iVar2 = 2;
    }
    else {
      iVar1 = parm_keyword1(2,&DAT_004c6aa8);
      if (iVar1 == 0) {
        iVar1 = parm_keyword1(2,&DAT_004c8958);
        if (iVar1 == 0) {
          iVar1 = parm_keyword1(2,&DAT_004a8688);
          if (iVar1 == 0) {
            iVar1 = parm_keyword1(2,&DAT_004c7dec);
            if (iVar1 == 0) {
              iVar1 = parm_count_expr(2);
              if (iVar1 != 0) {
                iVar2 = 1;
              }
            }
            else {
              iVar2 = 6;
            }
          }
          else {
            iVar2 = 4;
          }
        }
        else {
          iVar2 = 0;
        }
      }
      else {
        iVar2 = 3;
      }
    }
  }
  else {
    iVar2 = 1;
  }
LAB_004462ab:
  if (iVar2 == -1) {
    return 0;
  }
  return iVar2 * 8 + 0x4c8398;
}


/* ==== cmd_system_h0 @ 004462c0 ==== */

void cmd_system_h0(void)

{
  char cVar1;
  undefined3 extraout_var;
  char *pcVar2;
  
  console_close();
  printf(s_To_return_to_the_simulator_progr_004c8c80);
  cVar1 = getenv(s_ComSpec_004c8c78);
  pcVar2 = (char *)CONCAT31(extraout_var,cVar1);
  if (pcVar2 == (char *)0x0) {
    pcVar2 = s_cmd_exe_004c8c70;
  }
  FUN_00485160((int)pcVar2);
  console_open();
  scrollback_end(*(int *)(cur_dev + 4));
  return;
}


/* ==== cmd_system_h1 @ 00446310 ==== */

void cmd_system_h1(int param_1)

{
  char cVar1;
  LPSTR pCVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  char acStack_100 [255];
  undefined1 uStack_1;
  
  if (gui_mode == 0) {
    strncpy(acStack_100,(char *)(DAT_004a9470 + param_1),0xfe);
    uVar4 = 0xffffffff;
    pcVar8 = &DAT_004c5890;
    do {
      pcVar7 = pcVar8;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar7 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar7;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar3 = -1;
    pcVar8 = acStack_100;
    do {
      pcVar6 = pcVar8;
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      pcVar6 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar6;
    } while (cVar1 != '\0');
    pcVar8 = pcVar7 + -uVar4;
    pcVar7 = pcVar6 + -1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar7 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar7 = pcVar7 + 1;
    }
  }
  else {
    if (DAT_004dc270 == 0) {
      pcVar8 = s_command_com__K__s_004c8cdc;
    }
    else {
      pcVar8 = s_cmd_exe__K__s_004c8ccc;
    }
    sprintf(acStack_100,pcVar8,DAT_004a9470 + param_1);
    uStack_1 = 0;
  }
  console_close();
  pCVar2 = FUN_00485160((int)acStack_100);
  printf(s_Type_return_to_continue__004c8cb0);
  console_beep();
  console_open();
  scrollback_end(*(int *)(cur_dev + 4));
  if (pCVar2 == (LPSTR)0xffffffff) {
    uVar4 = 0xffffffff;
    pcVar8 = (&PTR_s_No_error_004d7e90)[errno];
    do {
      pcVar7 = pcVar8;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar7 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar7;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar8 = pcVar7 + -uVar4;
    pcVar7 = acStack_100;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar7 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar7 = pcVar7 + 1;
    }
    out_text(acStack_100,1);
  }
  return;
}


/* ==== cmd_system_h2 @ 00446440 ==== */

void cmd_system_h2(int param_1)

{
  char cVar1;
  LPSTR pCVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  char acStack_100 [256];
  
  strncpy(acStack_100,(char *)(DAT_004a9474 + param_1),0xfe);
  uVar3 = 0xffffffff;
  pcVar6 = &DAT_004c5890;
  do {
    pcVar8 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar8 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar8;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar4 = -1;
  pcVar6 = acStack_100;
  do {
    pcVar7 = pcVar6;
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  pcVar6 = pcVar8 + -uVar3;
  pcVar8 = pcVar7 + -1;
  for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar8 = pcVar8 + 1;
  }
  console_close();
  pCVar2 = FUN_00485160((int)acStack_100);
  console_open();
  scrollback_end(*(int *)(cur_dev + 4));
  if (pCVar2 == (LPSTR)0xffffffff) {
    uVar3 = 0xffffffff;
    pcVar6 = (&PTR_s_No_error_004d7e90)[errno];
    do {
      pcVar8 = pcVar6;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar8 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar8;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar6 = pcVar8 + -uVar3;
    pcVar8 = acStack_100;
    for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar8 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar8 = pcVar8 + 1;
    }
    out_text(acStack_100,1);
  }
  return;
}


/* ==== cmd_system_parse @ 00446510 ==== */

undefined ** cmd_system_parse(void)

{
  int iVar1;
  
  iVar1 = parm_check_too_many(2);
  if (iVar1 != 0) {
    return &PTR_cmd_system_h0_004c89c0;
  }
  iVar1 = parm_keyword1(2,&DAT_004c8cf0);
  if (iVar1 != 0) {
    iVar1 = parm_any_token(3);
    if (iVar1 != 0) {
      return &PTR_cmd_system_h2_004c89d0;
    }
  }
  iVar1 = parm_any_token(2);
  if (iVar1 != 0) {
    return &PTR_cmd_system_h1_004c89c8;
  }
  return (undefined **)0x0;
}


/* ==== cmd_streams_h0 @ 00446580 ==== */

void cmd_streams_h0(void)

{
  *(undefined4 *)(cur_sim + 0x404c) = 1;
  return;
}


/* ==== cmd_streams_h1 @ 00446590 ==== */

void cmd_streams_h1(void)

{
  *(undefined4 *)(cur_sim + 0x404c) = 0;
  return;
}


/* ==== cmd_streams_h2 @ 004465a0 ==== */

void cmd_streams_h2(void)

{
  char *va0;
  char acStack_14 [20];
  
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  va0 = s_enabled_004c8fdc;
  if (*(int *)(cur_sim + 0x404c) == 0) {
    va0 = s_disabled_004c8fd0;
  }
  sprintf(acStack_14,s_streams__s_004c8fc4,va0);
  out_text(acStack_14,1);
  return;
}


/* ==== cmd_streams_parse @ 00446600 ==== */

int cmd_streams_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(2);
  if (iVar1 != 0) {
    iVar2 = 2;
    goto LAB_0044668a;
  }
  iVar1 = parm_keyword1(2,s_enable_004c8ff0);
  if (iVar1 == 0) {
    iVar1 = parm_keyword1(2,&DAT_004c8fec);
    if (iVar1 != 0) goto LAB_0044663f;
  }
  else {
LAB_0044663f:
    iVar1 = parm_check_too_many(3);
    if (iVar1 != 0) {
      iVar2 = 0;
      goto LAB_0044668a;
    }
  }
  iVar1 = parm_keyword1(2,s_disable_004c8fe4);
  if (iVar1 == 0) {
    iVar1 = parm_keyword1(2,&DAT_004c6ab4);
    if (iVar1 == 0) goto LAB_0044668a;
  }
  iVar1 = parm_check_too_many(3);
  if (iVar1 != 0) {
    iVar2 = 1;
  }
LAB_0044668a:
  if (iVar2 == -1) {
    return 0;
  }
  return iVar2 * 8 + 0x4c8d40;
}


/* ==== cmd_step_h0 @ 004466a0 ==== */

void cmd_step_h0(undefined4 param_1)

{
  *(undefined4 *)(cur_sim + 0x3c) = 0;
  *(undefined4 *)(cur_sim + 0x34) = 4;
  cmd_run_devices(param_1);
  return;
}


/* ==== cmd_run_devices @ 004466d0 ==== */

void cmd_run_devices(void)

{
  int dev;
  undefined4 uVar1;
  int dev_00;
  
  uVar1 = DAT_004a96c0;
  if (DAT_004a93ea != 'i') {
    uVar1 = 1;
  }
  dev_00 = 0;
  *(undefined4 *)(cur_sim + 0x28) = uVar1;
  *(undefined4 *)(cur_sim + 0x2c) = 0;
  dev = cur_dev_index;
  if (0 < max_devices) {
    do {
      if ((*(int *)(dev_tab + dev_00 * 4) != 0) &&
         ((*(byte *)(*(int *)(dev_tab + dev_00 * 4) + 0x44) & 0x20) == 0)) {
        dev_select(dev_00);
        cdb_free_frames();
      }
      dev_00 = dev_00 + 1;
    } while (dev_00 < max_devices);
  }
  dev_select(dev);
  periph_reset();
  *(undefined4 *)(cur_sim + 0x40) = 1;
  return;
}


/* ==== cmd_step_h1 @ 00446760 ==== */

void cmd_step_h1(undefined4 param_1)

{
  int iVar1;
  
  *(undefined4 *)(cur_sim + 0x3c) = 0;
  if ((*(int *)(cur_sim + 0x4400) != 2) && (*(int *)(cur_sim + 0x4404) == 0)) {
    *(undefined4 *)(cur_sim + 0x34) = 3;
    cmd_run_devices(param_1);
    return;
  }
  iVar1 = step_mode_at_pc(3);
  *(int *)(cur_sim + 0x34) = iVar1;
  cmd_run_devices(param_1);
  return;
}


/* ==== cmd_step_h2 @ 004467c0 ==== */

void cmd_step_h2(undefined4 param_1)

{
  *(undefined4 *)(cur_sim + 0x3c) = 0;
  *(undefined4 *)(cur_sim + 0x34) = 3;
  cmd_run_devices(param_1);
  return;
}


/* ==== cmd_step_h3 @ 004467f0 ==== */

void cmd_step_h3(undefined4 param_1)

{
  int iVar1;
  
  *(undefined4 *)(cur_sim + 0x3c) = 0;
  iVar1 = step_mode_at_pc(3);
  *(int *)(cur_sim + 0x34) = iVar1;
  cmd_run_devices(param_1);
  return;
}


/* ==== cmd_step_h4 @ 00446820 ==== */

void cmd_step_h4(undefined4 param_1)

{
  *(undefined4 *)(cur_sim + 0x3c) = 1;
  *(undefined4 *)(cur_sim + 0x34) = 4;
  cmd_run_devices(param_1);
  return;
}


/* ==== cmd_step_h5 @ 00446850 ==== */

void cmd_step_h5(undefined4 param_1)

{
  int iVar1;
  
  *(undefined4 *)(cur_sim + 0x3c) = 1;
  if ((*(int *)(cur_sim + 0x4400) != 2) && (*(int *)(cur_sim + 0x4404) == 0)) {
    *(undefined4 *)(cur_sim + 0x34) = 3;
    cmd_run_devices(param_1);
    return;
  }
  iVar1 = step_mode_at_pc(3);
  *(int *)(cur_sim + 0x34) = iVar1;
  cmd_run_devices(param_1);
  return;
}


/* ==== cmd_step_h6 @ 004468b0 ==== */

void cmd_step_h6(undefined4 param_1)

{
  *(undefined4 *)(cur_sim + 0x3c) = 1;
  *(undefined4 *)(cur_sim + 0x34) = 3;
  cmd_run_devices(param_1);
  return;
}


/* ==== cmd_step_h7 @ 004468e0 ==== */

void cmd_step_h7(undefined4 param_1)

{
  int iVar1;
  
  *(undefined4 *)(cur_sim + 0x3c) = 1;
  iVar1 = step_mode_at_pc(3);
  *(int *)(cur_sim + 0x34) = iVar1;
  cmd_run_devices(param_1);
  return;
}


/* ==== cmd_step_parse @ 00446910 ==== */

int cmd_step_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(2);
  if (iVar1 == 0) {
    iVar1 = parm_check_too_many(3);
    if (iVar1 == 0) {
      iVar1 = parm_check_too_many(4);
      if (iVar1 == 0) {
        iVar1 = parm_check_too_many(5);
        if (iVar1 == 0) goto LAB_00446b3b;
        iVar1 = parm_count_expr(2);
        if (iVar1 == 0) goto LAB_00446b3b;
        iVar1 = parm_keyword1(4,&DAT_004c6aa8);
        if (iVar1 == 0) goto LAB_00446b3b;
        iVar1 = parm_keyword1(3,&DAT_004a8688);
        if (iVar1 != 0) {
          iVar2 = 7;
          goto LAB_00446b3b;
        }
        iVar1 = parm_keyword1(3,&DAT_004c7dec);
        if (iVar1 != 0) {
          iVar2 = 6;
          goto LAB_00446b3b;
        }
        iVar1 = parm_keyword1(3,&DAT_004c8958);
        if (iVar1 == 0) goto LAB_00446b3b;
      }
      else {
        iVar1 = parm_keyword1(3,&DAT_004c6aa8);
        if (iVar1 == 0) {
          iVar1 = parm_count_expr(2);
          if (iVar1 != 0) {
            iVar1 = parm_keyword1(3,&DAT_004a8688);
            if (iVar1 == 0) {
              iVar1 = parm_keyword1(3,&DAT_004c7dec);
              if (iVar1 == 0) {
                iVar1 = parm_keyword1(3,&DAT_004c8958);
                if (iVar1 != 0) {
                  iVar2 = 0;
                }
              }
              else {
                iVar2 = 2;
              }
            }
            else {
              iVar2 = 3;
            }
          }
          goto LAB_00446b3b;
        }
        iVar1 = parm_keyword1(2,&DAT_004a8688);
        if (iVar1 != 0) {
          iVar2 = 7;
          goto LAB_00446b3b;
        }
        iVar1 = parm_keyword1(2,&DAT_004c7dec);
        if (iVar1 != 0) {
          iVar2 = 6;
          goto LAB_00446b3b;
        }
        iVar1 = parm_keyword1(2,&DAT_004c8958);
        if (iVar1 == 0) {
          iVar1 = parm_count_expr(2);
          if (iVar1 != 0) {
            iVar2 = 5;
          }
          goto LAB_00446b3b;
        }
      }
      iVar2 = 4;
    }
    else {
      iVar1 = parm_keyword1(2,&DAT_004c6aa8);
      if (iVar1 == 0) {
        iVar1 = parm_keyword1(2,&DAT_004c8958);
        if (iVar1 == 0) {
          iVar1 = parm_keyword1(2,&DAT_004a8688);
          if (iVar1 == 0) {
            iVar1 = parm_keyword1(2,&DAT_004c7dec);
            if (iVar1 == 0) {
              iVar1 = parm_count_expr(2);
              if (iVar1 != 0) {
                iVar2 = 1;
              }
            }
            else {
              iVar2 = 2;
            }
          }
          else {
            iVar2 = 3;
          }
        }
        else {
          iVar2 = 0;
        }
      }
      else {
        iVar2 = 5;
      }
    }
  }
  else {
    iVar2 = 1;
  }
LAB_00446b3b:
  if (iVar2 == -1) {
    return 0;
  }
  return iVar2 * 8 + 0x4c9070;
}


/* ==== cmd_save_h0 @ 00446b50 ==== */

void cmd_save_h0(int param_1)

{
  char cVar1;
  int iVar2;
  int extraout_EAX;
  uint uVar3;
  char *pcVar4;
  char acStack_200 [256];
  char acStack_100 [256];
  
  uVar3 = 0xffffffff;
  pcVar4 = &cmd_tokbuf + DAT_004a9474;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  strncpy(acStack_200,(char *)(DAT_004a9474 + param_1),~uVar3 - 1);
  acStack_200[~uVar3 - 1] = '\0';
  if (DAT_004a93ec == 'o') {
    iVar2 = DAT_004a9710 + 1;
  }
  else {
    iVar2 = 0;
  }
  path_combine((char *)(cur_dev + 0x58),acStack_200,&DAT_004c97ec,acStack_100);
  sprintf(acStack_200,s_Output_file__s_004c97dc,acStack_100);
  out_text(acStack_200,1);
  screen_flush();
  iVar2 = confirm_overwrite(acStack_100,iVar2);
  if (iVar2 != -1) {
    save_state_all(acStack_100);
    if (extraout_EAX != 0) {
      sprintf(acStack_200,s_Error_writing_file__s_004c97c4,acStack_100);
      sim_error(acStack_200);
    }
  }
  return;
}


/* ==== cmd_save_h1 @ 00446c50 ==== */

void cmd_save_h1(int param_1)

{
  code *pcVar1;
  bool bVar2;
  undefined uVar3;
  char cVar4;
  uint uVar5;
  undefined3 extraout_var;
  void *stream;
  int iVar6;
  long lVar7;
  undefined4 *puVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  char *pcVar13;
  char *pcVar14;
  char *pcVar15;
  void *stream_00;
  int iStack_23c;
  uint uStack_238;
  uint uStack_234;
  void *pvStack_230;
  uint *puStack_22c;
  uint uStack_228;
  uint uStack_224;
  int iStack_220;
  char *pcStack_21c;
  undefined4 uStack_218;
  undefined4 uStack_214;
  uint uStack_210;
  undefined4 uStack_20c;
  uint uStack_208;
  undefined4 uStack_204;
  char acStack_200 [251];
  char acStack_105 [261];
  
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar5 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar5 = (**(code **)(cur_dtype + 0x4e8))();
  }
  iVar12 = 1;
  uVar5 = (-(uint)((uVar5 & 0x800) != 0) & 0x10000) - 1;
  uStack_234 = *(uint *)(*(int *)(cur_dtype + 0x20) + 0x10) & uVar5;
  acStack_105[4] = 0;
  cVar4 = DAT_004a93e9;
  while (cVar4 != 'N') {
    pcVar13 = &DAT_004a93e9 + iVar12;
    iVar12 = iVar12 + 1;
    cVar4 = *pcVar13;
  }
  uVar9 = 0xffffffff;
  pcVar13 = &cmd_tokbuf + (&g_tok_start)[iVar12];
  do {
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    cVar4 = *pcVar13;
    pcVar13 = pcVar13 + 1;
  } while (cVar4 != '\0');
  uStack_204 = uVar5;
  strncpy(acStack_200,(char *)((&g_tok_start)[iVar12] + param_1),~uVar9 - 1);
  cVar4 = (&DAT_004a93e9)[iVar12];
  acStack_200[~uVar9 - 1] = '\0';
  if (cVar4 == 'o') {
    iVar12 = *(int *)(&g_tok_val + (iVar12 + 1) * 0x28) + 1;
  }
  else {
    iVar12 = 0;
  }
  path_combine((char *)(cur_dev + 0x58),acStack_200,(char *)0x4c9840,acStack_105 + 5);
  sprintf(acStack_200,s_Output_file__s_004c97dc,acStack_105 + 5);
  out_text(acStack_200,1);
  screen_flush();
  iVar12 = confirm_overwrite(acStack_105 + 5,iVar12);
  if (iVar12 == -1) {
    return;
  }
  uVar9 = 0xffffffff;
  pcVar13 = acStack_105 + 5;
  do {
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    cVar4 = *pcVar13;
    pcVar13 = pcVar13 + 1;
  } while (cVar4 != '\0');
  uVar9 = ~uVar9;
  if ((((4 < (int)(uVar9 - 1)) &&
       ((acStack_105[uVar9 + 3] == 'd' || (acStack_105[uVar9 + 3] == 'D')))) &&
      ((acStack_105[uVar9 + 2] == 'l' || (acStack_105[uVar9 + 2] == 'L')))) &&
     (((acStack_105[uVar9 + 1] == 'c' || (acStack_105[uVar9 + 1] == 'C')) &&
      (acStack_105[uVar9] == '.')))) {
    uVar3 = cmd_save_h1_sub_45d910(acStack_105 + 5,iVar12);
    if (CONCAT31(extraout_var,uVar3) != 0) {
      return;
    }
    sim_error(s_Error_saving_file__004c982c);
    return;
  }
  fopen(acStack_105 + 5,*(char **)(iVar12 * 4 + 0x4c9530));
  if (stream == (void *)0x0) {
    sim_error(s_Error_opening_file__004c59d8);
    return;
  }
  pvStack_230 = stream;
  if (iVar12 != 1) goto LAB_00446eea;
  iVar12 = fscanf(stream,&DAT_004c556c,acStack_200);
  if (iVar12 == -1) {
LAB_00446e8c:
    func_0x00485330(stream);
    iVar12 = 0;
  }
  else {
    do {
      iVar6 = __strcmpi(acStack_200,(char *)0x4c9824);
      if (iVar6 == 0) break;
      iVar12 = fscanf(stream,&DAT_004c556c,acStack_200);
    } while (iVar12 != -1);
    if (iVar12 == -1) goto LAB_00446e8c;
    lVar7 = ftell(stream);
    iVar12 = lVar7 + -4;
    iVar6 = fscanf(stream,&DAT_004c556c,acStack_200);
    if (iVar6 != -1) {
      sscanf(acStack_200,&DAT_004c5568,&uStack_234);
    }
    if (iVar12 < 0) {
      iVar12 = 0;
    }
  }
  fseek(stream,iVar12,0);
LAB_00446eea:
  stream_00 = stream;
  if (DAT_004a93ea != 'N') {
    pcStack_21c = &DAT_004a93ea;
    puStack_22c = &DAT_004a96c0;
    cVar4 = DAT_004a93ea;
    do {
      if ((cVar4 == 'P') || (cVar4 == 'X')) {
LAB_00446f1d:
        uVar11 = (uint)(ushort)puStack_22c[7];
        iVar12 = uVar11 * 0x2c;
        puVar8 = (undefined4 *)(*(int *)(cur_dtype + 0x20) + iVar12);
        uStack_20c = *puVar8;
        uStack_224 = puVar8[8] & uVar5;
        uVar9 = *puStack_22c;
        uStack_208 = puStack_22c[1];
        if (((*(byte *)((int)puVar8 + 0x19) & 0x10) != 0) && (uVar9 < uStack_234)) {
          uStack_234 = uVar9;
        }
        uStack_210 = puVar8[9] & 2;
        uStack_228 = 0xffffffff;
        uStack_238 = 0;
        iStack_220 = iVar12;
        do {
          uVar9 = uVar9 & uStack_224;
          if (uStack_228 != uVar11) {
            uStack_228 = uVar11;
            sprintf(acStack_200,s__DATA__s__lx_004c9814,uStack_20c,uVar9);
            fputs(acStack_200,pvStack_230);
          }
          pcVar1 = (code *)(*(undefined4 **)(cur_dtype + 0x28))[10];
          if (pcVar1 == (code *)0x0) {
            iStack_23c = (*(code *)**(undefined4 **)(cur_dtype + 0x28))
                                   (*(undefined4 *)(*(int *)(cur_dtype + 0x20) + 4 + iVar12),uVar9,
                                    &uStack_218);
          }
          else {
            iStack_23c = (*pcVar1)(*(undefined4 *)(*(int *)(cur_dtype + 0x20) + 4 + iVar12),uVar9,
                                   &uStack_218);
          }
          if (iStack_23c == 0) {
            iStack_23c = 1;
          }
          if (uStack_210 == 0) {
            sprintf(acStack_200,&DAT_004c575c,uStack_218);
          }
          else {
            sprintf(acStack_200,(char *)0x4c9808,uStack_214,uStack_218);
          }
          uVar5 = uVar9;
          if (1 < iStack_23c) {
            uVar5 = uStack_238 + 1;
          }
          uStack_238 = uVar5;
          uVar5 = (int)uStack_238 >> 0x1f;
          if (((uStack_238 ^ uVar5) - uVar5 & 7 ^ uVar5) - uVar5 == 7) {
            uVar5 = 0xffffffff;
            pcVar13 = &DAT_004c5890;
            do {
              pcVar15 = pcVar13;
              if (uVar5 == 0) break;
              uVar5 = uVar5 - 1;
              pcVar15 = pcVar13 + 1;
              cVar4 = *pcVar13;
              pcVar13 = pcVar15;
            } while (cVar4 != '\0');
            uVar5 = ~uVar5;
            iVar12 = -1;
            pcVar13 = acStack_200;
            do {
              pcVar14 = pcVar13;
              if (iVar12 == 0) break;
              iVar12 = iVar12 + -1;
              pcVar14 = pcVar13 + 1;
              cVar4 = *pcVar13;
              pcVar13 = pcVar14;
            } while (cVar4 != '\0');
            pcVar13 = pcVar15 + -uVar5;
            pcVar15 = pcVar14 + -1;
            for (uVar10 = uVar5 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
              *(undefined4 *)pcVar15 = *(undefined4 *)pcVar13;
              pcVar13 = pcVar13 + 4;
              pcVar15 = pcVar15 + 4;
            }
            for (uVar5 = uVar5 & 3; iVar12 = iStack_220, uVar5 != 0; uVar5 = uVar5 - 1) {
              *pcVar15 = *pcVar13;
              pcVar13 = pcVar13 + 1;
              pcVar15 = pcVar15 + 1;
            }
          }
          fputs(acStack_200,pvStack_230);
          iVar6 = 0;
          bVar2 = false;
          if (0 < iStack_23c) {
            do {
              if ((uVar9 + iVar6 & uStack_224) == uStack_208) {
                bVar2 = true;
              }
              iVar6 = iVar6 + 1;
              iVar12 = iStack_220;
            } while (iVar6 < iStack_23c);
          }
          uVar5 = uStack_204;
          stream_00 = pvStack_230;
          if (bVar2) goto LAB_004470f6;
          uVar9 = uVar9 + iStack_23c;
        } while( true );
      }
      if (cVar4 == 'p') {
        puStack_22c[1] = *puStack_22c;
        goto LAB_00446f1d;
      }
LAB_004470f6:
      puStack_22c = puStack_22c + 10;
      pcStack_21c = pcStack_21c + 1;
      cVar4 = *pcStack_21c;
    } while (cVar4 != 'N');
  }
  uVar5 = *(uint *)(*(int *)(cur_dtype + 0x20) + 0x10) & uVar5;
  if (uStack_234 == uVar5) {
    sprintf(acStack_200,(char *)0x4c9800);
  }
  else {
    sprintf(acStack_200,s__END__lx_004c97f4,uVar5 & uStack_234);
  }
  fputs(acStack_200,stream_00);
  fclose(stream_00);
  return;
}


/* ==== cmd_save_parse @ 00447170 ==== */

void * cmd_save_parse(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = -1;
  iVar1 = parm_keyword1(2,&DAT_004c7e04);
  iVar2 = g_tok_start;
  if (iVar1 == 0) {
    if (2 < g_tok_start) {
      if ((3 < g_tok_start) && (iVar1 = parm_kw_o_options(g_tok_start), iVar1 != 0)) {
        iVar2 = iVar2 + -1;
      }
      iVar1 = parm_any_token(iVar2);
      if (iVar1 != 0) {
        iVar1 = 2;
        iVar4 = 1;
        if (2 < iVar2) {
          do {
            iVar3 = parm_address_spec(iVar1);
            if (iVar3 == 0) {
              iVar4 = -1;
              break;
            }
            iVar1 = iVar1 + 1;
          } while (iVar1 < iVar2);
        }
      }
    }
  }
  else {
    iVar2 = parm_any_token(3);
    if ((iVar2 != 0) &&
       ((iVar2 = parm_check_too_many(4), iVar2 != 0 ||
        ((iVar2 = parm_kw_o_options(4), iVar2 != 0 && (iVar2 = parm_check_too_many(5), iVar2 != 0)))
        ))) {
      iVar4 = 0;
    }
  }
  if (iVar4 != -1) {
    return &PTR_cmd_save_h0_004c9538 + iVar4 * 2;
  }
  return (void *)0x0;
}


/* ==== cmd_reset_h0 @ 00447230 ==== */

void cmd_reset_h0(void)

{
  int arg;
  
  arg = -1;
  if (DAT_004a93eb == 'm') {
    arg = DAT_004a96e8;
  }
  if (DAT_004a96c0 == 0) {
    chip_reset_regs(1,arg);
  }
  else if (DAT_004a96c0 == 1) {
    dev_reset(*(int *)(cur_dev + 4),arg);
  }
  periph_reset();
  return;
}


/* ==== cmd_reset_parse @ 00447270 ==== */

undefined ** cmd_reset_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(3);
  if (iVar1 == 0) {
    iVar1 = parm_kw_m_memmode(3);
    if (iVar1 == 0) goto LAB_004472b8;
    iVar1 = parm_check_too_many(4);
    if (iVar1 == 0) goto LAB_004472b8;
  }
  iVar1 = parm_match_keyword(2,&PTR_DAT_004c9888,0x66,2);
  if (iVar1 != -1) {
    iVar2 = 0;
  }
LAB_004472b8:
  if (iVar2 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_reset_h0_004c9890 + iVar2 * 2;
}


/* ==== cmd_redirect_h0 @ 004472d0 ==== */

void cmd_redirect_h0(void)

{
  char cVar1;
  void *pvVar2;
  int iVar3;
  int extraout_EAX;
  int iVar4;
  int extraout_EAX_00;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  char acStack_300 [256];
  char acStack_200 [256];
  char acStack_100 [256];
  
  iVar3 = DAT_004a96c0;
  if (DAT_004a93eb == 'N') {
    uVar5 = 0xffffffff;
    pcVar7 = &g_cmdline + DAT_004a9474;
    do {
      pcVar8 = pcVar7;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar7 = pcVar8 + -uVar5;
    pcVar8 = acStack_100;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar8 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    }
    path_combine((char *)(cur_dev + 0x58),acStack_100,&DAT_004ca058,acStack_300);
    if (iVar3 == 0) {
      fopen(acStack_300,&DAT_004c5574);
      iVar4 = extraout_EAX;
      if (extraout_EAX == 0) {
        sprintf(acStack_200,s_Error_opening__s_004ca044,acStack_300);
        sim_error(acStack_200);
        return;
      }
    }
    else {
      if (DAT_004a93ec == 'o') {
        iVar4 = DAT_004a9710 + 1;
      }
      else {
        iVar4 = 0;
      }
      iVar4 = confirm_overwrite(acStack_300,iVar4);
      if (iVar4 == -1) {
        return;
      }
      fopen(acStack_300,(&PTR_DAT_004c9b60)[iVar4]);
      if (extraout_EAX_00 == 0) {
        sprintf(acStack_200,s_Error_opening__s_004ca044,acStack_300);
        sim_error(acStack_200);
        return;
      }
      pvVar2 = *(void **)(cur_sim + 0x4098 + iVar3 * 4);
      iVar4 = extraout_EAX_00;
      if (pvVar2 != (void *)0x0) {
        fclose(pvVar2);
      }
    }
    uVar5 = 0xffffffff;
    pcVar7 = acStack_300;
    do {
      pcVar8 = pcVar7;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar7 = pcVar8 + -uVar5;
    pcVar8 = (char *)(iVar3 * 0x100 + 0x40a4 + cur_sim);
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar8 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    }
    *(int *)(cur_sim + 0x4098 + iVar3 * 4) = iVar4;
  }
  else {
    pvVar2 = *(void **)(cur_sim + 0x4098 + DAT_004a96c0 * 4);
    if (pvVar2 != (void *)0x0) {
      fclose(pvVar2);
      *(undefined1 *)(iVar3 * 0x100 + 0x40a4 + cur_sim) = 0;
    }
  }
  *(undefined4 *)(cur_sim + 0x408c + iVar3 * 4) = 1;
  return;
}


/* ==== cmd_redirect_h1 @ 004474c0 ==== */

void cmd_redirect_h1(void)

{
  if (DAT_004a93ea == 'h') {
    cmd_redirect_h1_sub_447500(DAT_004a96c0);
    return;
  }
  cmd_redirect_h1_sub_447500(0);
  cmd_redirect_h1_sub_447500(1);
  cmd_redirect_h1_sub_447500(2);
  return;
}


/* ==== cmd_redirect_h1_sub_447500 @ 00447500 ==== */

void cmd_redirect_h1_sub_447500(int param_1)

{
  int iVar1;
  void *stream;
  
  *(undefined4 *)(cur_sim + 0x408c + param_1 * 4) = 0;
  iVar1 = param_1 * 4 + 0x4098;
  stream = *(void **)(cur_sim + iVar1);
  if (stream != (void *)0x0) {
    fclose(stream);
    *(undefined1 *)(param_1 * 0x100 + 0x40a4 + cur_sim) = 0;
    *(undefined4 *)(cur_sim + iVar1) = 0;
  }
  return;
}


/* ==== cmd_redirect_h2 @ 00447560 ==== */

void cmd_redirect_h2(void)

{
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  if (DAT_004a93ea == 'h') {
    redirect_show(DAT_004a96c0);
    return;
  }
  redirect_show(0);
  redirect_show(1);
  redirect_show(2);
  return;
}


/* ==== redirect_show @ 004475b0 ==== */

void __cdecl redirect_show(int which)

{
  char local_80 [128];
  
  if (*(int *)(cur_sim + 0x408c + which * 4) == 0) {
    sprintf(local_80,s__s_off_004ca06c,(&g_redir_names)[which]);
  }
  else {
    sprintf(local_80,s__s__s__s_004ca060,(&g_redir_names)[which],(&g_redir_modes)[which],
            which * 0x100 + 0x40a4 + cur_sim);
  }
  out_text(local_80,1);
  return;
}


/* ==== cmd_redirect_parse @ 00447630 ==== */

undefined ** cmd_redirect_parse(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = -1;
  iVar1 = parm_keyword1(2,s_stdin_004c9bcc);
  iVar2 = parm_check_too_many(2);
  if (iVar2 != 0) {
    iVar3 = 2;
    goto LAB_0044770b;
  }
  iVar2 = parm_kw_h_stdio(2);
  if (iVar2 == 0) {
    iVar1 = parm_keyword1(2,&DAT_004c6aec);
    if (iVar1 == 0) goto LAB_0044770b;
    iVar1 = parm_check_too_many(3);
    if (iVar1 == 0) goto LAB_0044770b;
LAB_00447706:
    iVar3 = 1;
    goto LAB_0044770b;
  }
  iVar2 = parm_check_too_many(3);
  if (iVar2 != 0) {
    iVar3 = 2;
    goto LAB_0044770b;
  }
  iVar2 = parm_keyword1(3,&DAT_004c6aec);
  if (iVar2 != 0) {
    iVar2 = parm_check_too_many(4);
    if (iVar2 != 0) goto LAB_00447706;
  }
  iVar2 = parm_any_token(3);
  if (iVar2 == 0) goto LAB_0044770b;
  iVar2 = parm_check_too_many(4);
  if (iVar2 == 0) {
    if (iVar1 != 0) goto LAB_0044770b;
    iVar1 = parm_kw_o_options(4);
    if (iVar1 == 0) goto LAB_0044770b;
    iVar1 = parm_check_too_many(5);
    if (iVar1 == 0) goto LAB_0044770b;
  }
  iVar3 = 0;
LAB_0044770b:
  if (iVar3 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_redirect_h0_004c9b68 + iVar3 * 2;
}


/* ==== cmd_radix_h0 @ 00447720 ==== */

void cmd_radix_h0(void)

{
  char acStack_50 [80];
  
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  sprintf(acStack_50,s_The_current_default_radix_is___s_004ca474,
          (&PTR_s_binary_004ca0d8)[*(int *)(cur_sim + 0x30)]);
  out_text(acStack_50,1);
  return;
}


/* ==== cmd_radix_h1 @ 00447770 ==== */

void cmd_radix_h1(void)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  ulong *puVar5;
  uint uVar6;
  ulong *puVar7;
  uint uVar8;
  int iStack_34;
  ulong *puStack_30;
  char *pcStack_2c;
  ulong auStack_28 [4];
  uint uStack_18;
  uint uStack_8;
  uint uStack_4;
  
  iStack_34 = DAT_004a96c0;
  if (DAT_004a93eb == 'e') {
    iVar4 = DAT_004a96c0;
    if (DAT_004a96c0 == 2) {
      iVar4 = 1;
    }
    *(int *)(cur_sim + 0x30) = iVar4;
    dsp_free_ext((void *)0xfffffffe,1);
    return;
  }
  if (DAT_004a96c0 == 0) {
    iStack_34 = 3;
  }
  iVar4 = (int)DAT_004a93eb;
  if (iVar4 != 0x65) {
    pcStack_2c = &DAT_004a93eb;
    puStack_30 = (ulong *)&DAT_004a96e0;
    do {
      if (iVar4 == 0x75) break;
      puVar5 = puStack_30;
      puVar7 = auStack_28;
      for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar7 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar7 = puVar7 + 1;
      }
      switch(iVar4) {
      case 0x47:
        uVar8 = uStack_4 & 0xffff;
        uVar3 = uStack_8 & 0xffff;
        if (((int)uStack_18 < (int)uVar8) ||
           ((uStack_18 == uVar8 && ((int)auStack_28[2] < (int)uVar3)))) {
          iVar4 = -1;
        }
        else {
          iVar4 = 1;
        }
        while( true ) {
          iVar2 = *(int *)(*(int *)(cur_sim + 8) + 4 + uVar8 * 8);
          puVar1 = (uint *)(iVar2 + uVar3 * 4);
          uVar6 = *(uint *)(iVar2 + uVar3 * 4) & 0xffff0fff;
          *puVar1 = uVar6;
          *puVar1 = uVar6 | *(uint *)(&DAT_004ca0f0 + iStack_34 * 4);
          if ((uVar8 == uStack_18) && (uVar3 == auStack_28[2])) break;
          uVar3 = uVar3 + iVar4;
          if (uVar3 == *(uint *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + uVar8 * 0x48) + 0x28))
          {
            if (uVar8 == *(uint *)(cur_dtype + 0x14)) {
              uVar8 = 0;
              uVar3 = 0;
            }
            else {
              uVar8 = uVar8 + 1;
              uVar3 = 0;
            }
          }
          else if (uVar3 == 0) {
            if (uVar8 == 0) {
              uVar8 = *(uint *)(cur_dtype + 0x14);
            }
            uVar8 = uVar8 - 1;
            uVar3 = *(uint *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + uVar8 * 0x48) + 0x28);
          }
        }
        break;
      case 0x67:
        iVar4 = *(int *)(*(int *)(cur_sim + 8) + 4 + (uStack_4 & 0xffff) * 8);
        puVar1 = (uint *)(iVar4 + (uStack_8 & 0xffff) * 4);
        uVar8 = *(uint *)(iVar4 + (uStack_8 & 0xffff) * 4) & 0xffff0fff;
        *puVar1 = uVar8;
        *puVar1 = *(uint *)(&DAT_004ca0f0 + iStack_34 * 4) | uVar8;
        break;
      case 0x70:
        auStack_28[3] = auStack_28[2];
      case 0x50:
      case 0x58:
        space_notify(uStack_4 & 0xffff,auStack_28[2],auStack_28[3],iStack_34);
      }
      puStack_30 = puStack_30 + 10;
      pcStack_2c = pcStack_2c + 1;
      iVar4 = (int)*pcStack_2c;
    } while (iVar4 != 0x65);
  }
  dsp_free_ext((void *)0xfffffffe,1);
  return;
}


/* ==== cmd_radix_parse @ 00447980 ==== */

undefined ** cmd_radix_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(2);
  if (iVar1 == 0) {
    iVar1 = parm_kw_R_radix(2);
    if (iVar1 != 0) {
      iVar1 = parm_check_too_many(3);
      if (iVar1 == 0) {
        iVar1 = parm_addr_list_simple(3);
        if (iVar1 == 0) goto LAB_004479c5;
      }
      iVar2 = 1;
    }
  }
  else {
    iVar2 = 0;
  }
LAB_004479c5:
  if (iVar2 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_radix_h0_004ca108 + iVar2 * 2;
}


/* ==== cmd_quit_h1 @ 004479e0 ==== */

void cmd_quit_h1(void)

{
  quit_on_error = 1;
  return;
}


/* ==== cmd_quit_h2 @ 004479f0 ==== */

void cmd_quit_h2(void)

{
  quit_on_error = 0;
  return;
}


/* ==== cmd_quit_h0 @ 00447a00 ==== */

void cmd_quit_h0(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  void *unaff_EDI;
  
  uVar4 = cur_dev;
  uVar3 = cur_itype;
  uVar2 = cur_dtype;
  uVar1 = cur_sim;
  if ((profiler_hook != (undefined *)0x0) && (iVar6 = 0, 0 < max_devices)) {
    do {
      cur_dev = *(int **)(dev_tab + iVar6 * 4);
      if ((cur_dev != (int *)0x0) && ((*(byte *)(cur_dev + 0x11) & 0x20) == 0)) {
        cur_itype = *(undefined4 *)(itype_tab + *cur_dev * 4);
        cur_dtype = *(undefined4 *)(chiptype_tab + *cur_dev * 4);
        cur_sim = *(undefined4 *)(dev_state_tab + iVar6 * 4);
        puVar5 = (undefined4 *)parse_command_line(s_log_off_p_004ca698,0);
        more_line_count = 0;
        if (puVar5 != (undefined4 *)0x0) {
          (*(code *)*puVar5)(s_log_off_p_004ca698);
        }
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < max_devices);
  }
  cur_sim = uVar1;
  cur_dtype = uVar2;
  cur_itype = uVar3;
  cur_dev = (int *)uVar4;
  if (gui_mode == 0) {
    macro_abort_all();
    console_close();
    if (quit_on_error == 0) {
      exit(0);
      return;
    }
    exit(on_error_active);
    return;
  }
  dsp_free_ext(unaff_EDI);
  return;
}


/* ==== cmd_quit_parse @ 00447b30 ==== */

undefined ** cmd_quit_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(2);
  if (iVar1 == 0) {
    iVar1 = parm_check_too_many(3);
    if (iVar1 != 0) {
      iVar1 = parm_keyword1(2,&DAT_004c8fec);
      if (iVar1 == 0) {
        iVar1 = parm_keyword1(2,&DAT_004c6ab4);
        iVar2 = (-(uint)(iVar1 != 0) & 3) - 1;
      }
      else {
        iVar2 = 1;
      }
    }
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_quit_h0_004ca4e0 + iVar2 * 2;
}


/* ==== cmd_path_h0 @ 00447ba0 ==== */

void cmd_path_h0(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *buf;
  char *pcVar4;
  char acStack_100 [256];
  
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  sprintf(acStack_100,s_Device_Working_Directory____s__004ca96c,cur_dev + 0x58);
  out_text(acStack_100,1);
  buf = source_path_list;
  if (source_path_list == (char *)0x0) {
    out_text(s_No_Alternate_Source_Paths__004ca938,1);
  }
  else {
    out_text(s_Alternate_Source_Paths__004ca954,1);
    iVar2 = sscanf(buf,s__255_____004c5cd8,acStack_100);
    if (iVar2 != 0) {
      do {
        out_text(acStack_100,1);
        uVar3 = 0xffffffff;
        pcVar4 = acStack_100;
        do {
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          cVar1 = *pcVar4;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
        if (buf[~uVar3 - 1] == '\0') {
          return;
        }
        buf = buf + (~uVar3 - 1) + 1;
        iVar2 = sscanf(buf,s__255_____004c5cd8,acStack_100);
        if (iVar2 == 0) {
          return;
        }
      } while( true );
    }
  }
  return;
}


/* ==== cmd_path_h1 @ 00447c70 ==== */

void cmd_path_h1(int param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  undefined1 auStack_124 [6];
  uint uStack_11e;
  char acStack_100 [255];
  undefined1 uStack_1;
  
  uVar3 = 0xffffffff;
  uStack_1 = 0;
  pcVar5 = &cmd_tokbuf + DAT_004a9470;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  strncpy(acStack_100,(char *)(DAT_004a9470 + param_1),~uVar3);
  acStack_100[~uVar3] = '\0';
  iVar2 = func_0x004911c0(acStack_100,auStack_124);
  if ((iVar2 != 0) || ((uStack_11e & 0x4000) != 0x4000)) {
    sim_error(s_Error_in_Path_Specification__004ca98c);
    return;
  }
  uVar3 = 0xffffffff;
  pcVar5 = acStack_100;
  do {
    pcVar6 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar6 + -uVar3;
  pcVar6 = (char *)(cur_dev + 0x58);
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  return;
}


/* ==== cmd_path_h3 @ 00447d30 ==== */

void cmd_path_h3(int param_1)

{
  char cVar1;
  int iVar2;
  char *extraout_EAX;
  char *extraout_EAX_00;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  undefined1 auStack_124 [6];
  uint uStack_11e;
  char acStack_100 [255];
  undefined1 uStack_1;
  
  pcVar6 = &g_cmdline + DAT_004a9474;
  uVar3 = 0xffffffff;
  uStack_1 = 0;
  pcVar5 = pcVar6;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  strncpy(acStack_100,(char *)(DAT_004a9474 + param_1),uVar3);
  acStack_100[uVar3] = '\0';
  iVar2 = func_0x004911c0(acStack_100,auStack_124);
  if ((iVar2 != 0) || ((uStack_11e & 0x4000) != 0x4000)) {
    sim_error(s_Error_in_Path_Specification__004ca98c);
    return;
  }
  if (source_path_list == (char *)0x0) {
    dsp_alloc(uVar3,0);
    uVar3 = 0xffffffff;
    do {
      pcVar5 = pcVar6;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar5 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar5;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar6 = pcVar5 + -uVar3;
    pcVar5 = extraout_EAX_00;
    source_path_list = extraout_EAX_00;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar5 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar5 = pcVar5 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar5 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar5 = pcVar5 + 1;
    }
    return;
  }
  uVar4 = 0xffffffff;
  pcVar5 = source_path_list;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  dsp_realloc(source_path_list,~uVar4 + uVar3);
  uVar3 = 0xffffffff;
  pcVar5 = &DAT_004c1648;
  do {
    pcVar8 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar8 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar8;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar2 = -1;
  pcVar5 = extraout_EAX;
  do {
    pcVar7 = pcVar5;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar7 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar7;
  } while (cVar1 != '\0');
  pcVar5 = pcVar8 + -uVar3;
  pcVar8 = pcVar7 + -1;
  source_path_list = extraout_EAX;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar8 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar8 = pcVar8 + 1;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar5 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar5;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar2 = -1;
  pcVar6 = extraout_EAX;
  do {
    pcVar8 = pcVar6;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar8 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar8;
  } while (cVar1 != '\0');
  pcVar6 = pcVar5 + -uVar3;
  pcVar5 = pcVar8 + -1;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar5 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar5 = pcVar5 + 1;
  }
  return;
}


/* ==== cmd_path_h2 @ 00447e90 ==== */

void cmd_path_h2(void)

{
  if (source_path_list != (void *)0x0) {
    dsp_free(source_path_list);
    source_path_list = (void *)0x0;
  }
  return;
}


/* ==== cmd_path_parse @ 00447eb0 ==== */

undefined ** cmd_path_parse(void)

{
  int iVar1;
  
  iVar1 = parm_check_too_many(2);
  if (iVar1 == 0) {
    iVar1 = parm_keyword1(2,&DAT_004c7e30);
    if (iVar1 == 0) {
      iVar1 = parm_keyword1(2,&DAT_004c7e2c);
      if (iVar1 == 0) {
        iVar1 = parm_any_token(2);
        if (iVar1 != 0) {
          iVar1 = parm_check_too_many(3);
          if (iVar1 != 0) {
            iVar1 = 1;
            goto LAB_00447f36;
          }
        }
        iVar1 = -1;
      }
      else {
        iVar1 = parm_any_token(3);
        iVar1 = (-(uint)(iVar1 != 0) & 4) - 1;
      }
    }
    else {
      iVar1 = parm_check_too_many(3);
      iVar1 = (-(uint)(iVar1 != 0) & 3) - 1;
    }
  }
  else {
    iVar1 = 0;
  }
LAB_00447f36:
  if (iVar1 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_path_h0_004ca700 + iVar1 * 2;
}


/* ==== cmd_output_h0 @ 00447f50 ==== */

void cmd_output_h0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char acStack_84 [132];
  
  iVar1 = io_next_free_id(0,(void **)(cur_sim + 0x158));
  iVar2 = io_next_free_id(0,(void **)(cur_sim + 0x154));
  if (iVar1 <= iVar2) {
    iVar1 = iVar2;
  }
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  iVar2 = 1;
  if (0 < iVar1) {
    do {
      iVar3 = io_next_free_id(iVar2,(void **)(cur_sim + 0x154));
      if (iVar3 == iVar2) {
        iVar3 = *(int *)(cur_sim + 0x154);
        if (iVar3 == 0) {
LAB_00448080:
          iVar3 = iVar2 + 1;
        }
        else {
          do {
            if (*(int *)(iVar3 + 0x1e4) == iVar2) {
              sprintf(acStack_84,s__d__Untimed_writes_of__s_to__s_004cb114,iVar2,iVar3 + 0x100,iVar3
                     );
              log_echo(acStack_84,1);
              iVar3 = iVar2 + 1;
              goto LAB_0044809a;
            }
            iVar3 = *(int *)(iVar3 + 0x1e0);
          } while (iVar3 != 0);
          iVar3 = iVar2 + 1;
        }
      }
      else {
        iVar4 = io_next_free_id(iVar2,(void **)(cur_sim + 0x158));
        if (iVar4 == iVar2) {
          iVar3 = *(int *)(cur_sim + 0x158);
          if (iVar3 == 0) goto LAB_00448080;
          do {
            if (*(int *)(iVar3 + 0x1e4) == iVar2) {
              sprintf(acStack_84,s__d__Timed_writes_of__s_to__s_004cb0f0,iVar2,iVar3 + 0x100,iVar3);
              log_echo(acStack_84,1);
              goto LAB_00448080;
            }
            iVar3 = *(int *)(iVar3 + 0x1e0);
          } while (iVar3 != 0);
          iVar3 = iVar2 + 1;
        }
        else if ((iVar4 == 0) || (iVar3 == 0)) {
          iVar3 = iVar3 + iVar4;
        }
        else if (iVar4 < iVar3) {
          iVar3 = iVar4;
        }
      }
LAB_0044809a:
      iVar2 = iVar3;
    } while (iVar3 <= iVar1);
  }
  return;
}


/* ==== cmd_output_h1 @ 004480b0 ==== */

void cmd_output_h1(void)

{
  int mode;
  
  if (DAT_004a93ea == '#') {
    mode = g_io_id_arg + 2;
    iolist_remove((void *)(cur_sim + 0x154),&empty_str,mode);
    iolist_remove((void *)(cur_sim + 0x158),&empty_str,mode);
    return;
  }
  if (DAT_004a93eb == 'e') {
    iolist_remove((void *)(cur_sim + 0x154),&empty_str,1);
    iolist_remove((void *)(cur_sim + 0x158),&empty_str,1);
    return;
  }
  if (DAT_004a93ea == 'j') {
    iolist_remove((void *)(cur_sim + 0x158),&g_cmdline + DAT_004a9474,0);
    return;
  }
  iolist_remove((void *)(cur_sim + 0x154),&g_cmdline + DAT_004a9470,0);
  return;
}


/* ==== cmd_output_h2 @ 004481a0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void cmd_output_h2(int param_1)

{
  uint *puVar1;
  int iVar2;
  char cVar3;
  char cVar4;
  byte bVar5;
  ushort uVar6;
  ushort uVar7;
  ulong uVar8;
  ulong hi;
  undefined4 uVar9;
  char *out;
  int iVar10;
  byte *pbVar11;
  int extraout_EAX;
  uint uVar12;
  uint uVar13;
  int iVar14;
  char *pcVar15;
  undefined4 *puVar16;
  byte *pbVar17;
  char *pcVar18;
  bool bVar19;
  int iStack_118;
  undefined4 *puStack_110;
  int iStack_10c;
  undefined4 uStack_104;
  char acStack_100 [256];
  
  dsp_alloc(0x1e8,1);
  if (out == (char *)0x0) {
    return;
  }
  if (DAT_004a93ea == '#') {
    iStack_118 = g_io_id_arg;
    func_0x00448150();
    iVar10 = 3;
    iStack_10c = 3;
  }
  else {
    iStack_10c = 2;
    iStack_118 = 0;
    iVar10 = 2;
  }
  cVar4 = (&g_tok_type)[iVar10];
  if (cVar4 != 'j') {
    puStack_110 = (undefined4 *)(cur_sim + 0x154);
  }
  else {
    puStack_110 = (undefined4 *)(cur_sim + 0x158);
    iVar10 = iVar10 + 1;
  }
  iVar2 = iVar10 * 0x28;
  uVar12 = 0xffffffff;
  pcVar15 = &g_cmdline + (&g_tok_start)[iVar10];
  do {
    pcVar18 = pcVar15;
    if (uVar12 == 0) break;
    uVar12 = uVar12 - 1;
    pcVar18 = pcVar15 + 1;
    cVar3 = *pcVar15;
    pcVar15 = pcVar18;
  } while (cVar3 != '\0');
  uVar12 = ~uVar12;
  uStack_104 = out + 0x100;
  pcVar15 = pcVar18 + -uVar12;
  pcVar18 = uStack_104;
  for (uVar13 = uVar12 >> 2; uVar13 != 0; uVar13 = uVar13 - 1) {
    *(undefined4 *)pcVar18 = *(undefined4 *)pcVar15;
    pcVar15 = pcVar15 + 4;
    pcVar18 = pcVar18 + 4;
  }
  for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
    *pcVar18 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    pcVar18 = pcVar18 + 1;
  }
  iolist_remove(puStack_110,uStack_104,0);
  if (iStack_118 == 0) {
    iStack_118 = cmd_output_h2_sub_4486f0();
  }
  *(int *)(out + 0x1e4) = iStack_118;
  *(undefined4 *)(out + 0x1e0) = *puStack_110;
  *puStack_110 = out;
  puVar16 = (undefined4 *)0x5024b0;
  pcVar15 = out + 0x180;
  for (iVar14 = 10; iVar14 != 0; iVar14 = iVar14 + -1) {
    *(undefined4 *)pcVar15 = *puVar16;
    puVar16 = puVar16 + 1;
    pcVar15 = pcVar15 + 4;
  }
  out[0x1d0] = '\x01';
  out[0x1d1] = '\0';
  out[0x1d2] = '\0';
  out[0x1d3] = '\0';
  out[0x1d4] = '\x03';
  out[0x1d5] = '\0';
  out[0x1d6] = '\0';
  out[0x1d7] = '\0';
  *(int *)(cur_sim + 0x44) = *(int *)(cur_sim + 0x44) + 1;
  *(undefined4 *)(out + 0x164) = *(undefined4 *)(cur_sim + 0x44);
  if ((&DAT_004a93ea)[iVar10] == 'r') {
    *(undefined4 *)(out + 0x1d4) = (&DAT_004a96c0)[iVar10 * 10];
    if ((&DAT_004a93eb)[iVar10] == 'o') {
      iStack_118 = (&DAT_004a96e8)[iVar10 * 10] + 1;
      goto LAB_0044832a;
    }
  }
  else if ((&DAT_004a93ea)[iVar10] == 'o') {
    iStack_118 = (&DAT_004a96c0)[iVar10 * 10] + 1;
    goto LAB_0044832a;
  }
  iStack_118 = 0;
LAB_0044832a:
  pbVar17 = &DAT_004cb138;
  pbVar11 = &cmd_tokbuf + (&DAT_004a946c)[iVar10];
  do {
    bVar5 = *pbVar11;
    bVar19 = bVar5 < *pbVar17;
    if (bVar5 != *pbVar17) {
LAB_00448362:
      iVar14 = (1 - (uint)bVar19) - (uint)(bVar19 != 0);
      goto LAB_00448369;
    }
    if (bVar5 == 0) break;
    bVar5 = pbVar11[1];
    bVar19 = bVar5 < pbVar17[1];
    if (bVar5 != pbVar17[1]) goto LAB_00448362;
    pbVar11 = pbVar11 + 2;
    pbVar17 = pbVar17 + 2;
  } while (bVar5 != 0);
  iVar14 = 0;
LAB_00448369:
  if (iVar14 == 0) {
    *(undefined4 *)out = _DAT_004cb138;
    out[4] = DAT_004cb13c;
  }
  else {
    uVar12 = 0xffffffff;
    pcVar15 = &cmd_tokbuf + (&DAT_004a946c)[iVar10];
    do {
      if (uVar12 == 0) break;
      uVar12 = uVar12 - 1;
      cVar3 = *pcVar15;
      pcVar15 = pcVar15 + 1;
    } while (cVar3 != '\0');
    strncpy(acStack_100,(char *)((&DAT_004a946c)[iVar10] + param_1),~uVar12 - 1);
    acStack_100[~uVar12 - 1] = '\0';
    path_combine((char *)(cur_dev + 0x58),acStack_100,(&PTR_DAT_004caa68)[iVar10 - iStack_10c],out);
    iVar14 = confirm_overwrite(out,iStack_118);
    if (iVar14 == -1) {
      iolist_remove(puStack_110,uStack_104,0);
      return;
    }
    fopen(out,(&PTR_DAT_004caa70)[iVar14]);
    *(int *)(out + 0x150) = extraout_EAX;
    if (extraout_EAX == 0) {
      sim_error(s_Error_opening_file__004c59d8);
    }
  }
  switch((&g_tok_type)[iVar10]) {
  case 0x4a:
    out[0x154] = '\x06';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    out[0x158] = '\0';
    out[0x159] = '\0';
    out[0x15a] = '\0';
    out[0x15b] = '\0';
    out[0x15c] = '\0';
    out[0x15d] = '\0';
    out[0x15e] = '\0';
    out[0x15f] = '\0';
    out[0x160] = '\0';
    out[0x161] = '\0';
    out[0x162] = '\0';
    out[0x163] = '\0';
    return;
  case 0x4b:
    out[0x154] = '\x06';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    out[0x158] = '\0';
    out[0x159] = '\0';
    out[0x15a] = '\0';
    out[0x15b] = '\0';
    out[0x15c] = '\0';
    out[0x15d] = '\0';
    out[0x15e] = '\0';
    out[0x15f] = '\0';
    out[0x160] = '\x01';
    out[0x161] = '\0';
    out[0x162] = '\0';
    out[0x163] = '\0';
    return;
  case 0x4c:
    out[0x154] = '\x06';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    out[0x158] = '\0';
    out[0x159] = '\0';
    out[0x15a] = '\0';
    out[0x15b] = '\0';
    out[0x15c] = '\0';
    out[0x15d] = '\0';
    out[0x15e] = '\0';
    out[0x15f] = '\0';
    out[0x160] = '\x02';
    out[0x161] = '\0';
    out[0x162] = '\0';
    out[0x163] = '\0';
    return;
  case 0x50:
  case 0x58:
    out[0x154] = '\0';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    *(uint *)(out + 0x158) = (uint)*(ushort *)(&DAT_004a968c + iVar2);
    uVar8 = *(ulong *)(&g_tok_val + iVar2);
    *(ulong *)(out + 0x15c) = uVar8;
    hi = *(ulong *)(&DAT_004a9674 + iVar2);
    *(ulong *)(out + 0x160) = hi;
    memtag_add(1,*(int *)(out + 0x158),uVar8,hi,*(int *)(out + 0x164));
    return;
  case 0x53:
    out[0x154] = '\x04';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    out[0x158] = '\0';
    out[0x159] = '\0';
    out[0x15a] = '\0';
    out[0x15b] = '\0';
    *(undefined4 *)(out + 0x15c) = *(undefined4 *)(&g_tok_val + iVar2);
    *(undefined4 *)(out + 0x160) = *(undefined4 *)(&DAT_004a9674 + iVar2);
    return;
  case 0x55:
    out[0x154] = '\x02';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    *(undefined4 *)(out + 0x158) = *(undefined4 *)(&g_tok_val + iVar2);
    out[0x15c] = '\0';
    out[0x15d] = '\0';
    out[0x15e] = '\0';
    out[0x15f] = '\0';
    return;
  case 0x67:
    out[0x154] = '\t';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    uVar6 = *(ushort *)(iVar2 + 0x4a9688);
    uVar12 = (-(uint)(cVar4 == 'j') & 0x800000) + 0x800000;
    uVar7 = *(ushort *)(&DAT_004a968c + iVar2);
    *(uint *)(out + 0x15c) = (uint)uVar6;
    *(uint *)(out + 0x158) = (uint)uVar7;
    *(uint *)(out + 0x160) = uVar12;
    puVar1 = (uint *)(*(int *)(*(int *)(cur_sim + 8) + 4 + (uint)uVar7 * 8) + (uint)uVar6 * 4);
    *puVar1 = *puVar1 | uVar12;
    break;
  case 0x70:
    out[0x154] = '\0';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    *(uint *)(out + 0x158) = (uint)*(ushort *)(&DAT_004a968c + iVar2);
    uVar8 = *(ulong *)(&g_tok_val + iVar2);
    *(ulong *)(out + 0x15c) = uVar8;
    *(undefined4 *)(out + 0x160) = *(undefined4 *)(&g_tok_val + iVar2);
    memtag_add(1,*(int *)(out + 0x158),uVar8,uVar8,*(int *)(out + 0x164));
    return;
  case 0x73:
    out[0x158] = '\0';
    out[0x159] = '\0';
    out[0x15a] = '\0';
    out[0x15b] = '\0';
    *(uint *)(out + 0x154) = (-(uint)(*(int *)(out + 0x1d4) != 2) & 0xfffffffb) + 8;
    uVar9 = *(undefined4 *)(&g_tok_val + iVar2);
    *(undefined4 *)(out + 0x15c) = uVar9;
    *(undefined4 *)(out + 0x160) = uVar9;
    return;
  case 0x74:
    out[0x154] = '\x01';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    uVar6 = *(ushort *)(&DAT_004a968c + iVar2);
    out[0x15c] = '\0';
    out[0x15d] = '\0';
    out[0x15e] = '\0';
    out[0x15f] = '\0';
    *(uint *)(out + 0x158) = (uint)uVar6;
    return;
  }
  return;
}


/* ==== cmd_output_h2_sub_4486f0 @ 004486f0 ==== */

int cmd_output_h2_sub_4486f0(void)

{
  int iVar1;
  int id;
  
  id = 1;
  do {
    iVar1 = io_next_free_id(id,(void **)(cur_sim + 0x154));
    if (iVar1 != id) {
      iVar1 = io_next_free_id(id,(void **)(cur_sim + 0x158));
      if (iVar1 != id) {
        return id;
      }
    }
    id = id + 1;
  } while( true );
}


/* ==== cmd_output_h3 @ 00448730 ==== */

void cmd_output_h3(undefined4 param_1)

{
  cmd_output_h2(param_1);
  return;
}


