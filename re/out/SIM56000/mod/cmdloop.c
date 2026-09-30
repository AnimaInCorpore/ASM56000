/* ==== sim_init_tables @ 00439000 ==== */

void sim_init_tables(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  console_open();
  iVar3 = 0;
  if (0 < num_chiptypes) {
    do {
      cur_dtype = *(int *)(chiptype_tab + iVar3 * 4);
      if (cur_dtype != 0) {
        iVar1 = 0x4c;
        do {
          *(undefined4 *)(cur_dtype + iVar1) = 0xffffffff;
          iVar1 = iVar1 + 4;
        } while (iVar1 < 0x4dc);
        iVar1 = *(int *)(cur_dtype + 0x1c) + -1;
        if (-1 < iVar1) {
          iVar2 = iVar1 * 0x2c;
          do {
            iVar2 = iVar2 + -0x2c;
            *(int *)(cur_dtype + 0x4c + *(int *)(*(int *)(cur_dtype + 0x20) + 0x30 + iVar2) * 4) =
                 iVar1;
            iVar1 = iVar1 + -1;
          } while (-1 < iVar1);
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < num_chiptypes);
  }
  return;
}


/* ==== memmap_find @ 00439080 ==== */

int __cdecl memmap_find(int space,ulong addr)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  int local_4;
  
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar3 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar3 = (**(code **)(cur_dtype + 0x4e8))();
  }
  iVar1 = *(int *)(cur_dtype + 0x20);
  iVar2 = *(int *)(cur_dtype + 0x4c + space * 4);
  iVar5 = iVar1 + iVar2 * 0x2c;
  uVar3 = (-(uint)((uVar3 & 0x800) != 0) & 0x10000) - 1;
  local_4 = iVar2;
  if ((((*(uint *)(iVar1 + 0x10 + iVar2 * 0x2c) & uVar3) < addr) ||
      (addr < (*(uint *)(iVar5 + 0xc) & uVar3))) && ((*(uint *)(iVar5 + 0x18) & 0x20000) != 0)) {
    iVar5 = iVar2 + 1;
    if (iVar5 < *(int *)(cur_dtype + 0x1c)) {
      puVar4 = (uint *)(iVar1 + 0xc + iVar5 * 0x2c);
      while (((puVar4[-2] != space || ((puVar4[1] & uVar3) < addr)) ||
             (local_4 = iVar5, addr < (uVar3 & *puVar4)))) {
        iVar5 = iVar5 + 1;
        puVar4 = puVar4 + 0xb;
        if (*(int *)(cur_dtype + 0x1c) <= iVar5) {
          return iVar2;
        }
      }
    }
  }
  return local_4;
}


/* ==== dev_select @ 00439140 ==== */

void __cdecl dev_select(int dev)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = cur_dev;
  iVar1 = cur_sim;
  if (*(int *)(dev_state_tab + dev * 4) == 0) {
    iVar3 = dev_create(dev,(char *)**(undefined4 **)chiptype_tab);
    if (iVar3 == 0) {
      cur_sim = iVar1;
      cur_dev = (int *)uVar2;
      *(undefined4 *)(iVar1 + 0x40) = 0;
      return;
    }
  }
  cur_dev_index = dev;
  run_dev_index = dev;
  cur_dev = *(int **)(dev_tab + dev * 4);
  cur_sim = *(undefined4 *)(dev_state_tab + dev * 4);
  cur_itype = *(undefined4 *)(itype_tab + *cur_dev * 4);
  cur_dtype = *(undefined4 *)(chiptype_tab + *cur_dev * 4);
  return;
}


/* ==== cmd_complete @ 004391f0 ==== */

char __cdecl cmd_complete(char *line)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  undefined **ppuVar9;
  byte *pbVar10;
  char *pcVar11;
  int iVar12;
  char *pcVar13;
  bool bVar14;
  byte local_100 [255];
  undefined1 local_1;
  
  strncpy((char *)local_100,line,0xff);
  local_1 = 0;
  str_tolower((char *)local_100);
  iVar3 = num_commands;
  iVar12 = 0;
  iVar7 = 1;
  piVar8 = (int *)command_table;
  if (0 < num_commands) {
    do {
      pbVar10 = *(byte **)(*piVar8 + 4);
      pbVar4 = local_100;
      do {
        bVar2 = *pbVar4;
        bVar14 = bVar2 < *pbVar10;
        if (bVar2 != *pbVar10) {
LAB_0043926e:
          iVar7 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
          goto LAB_00439273;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar4[1];
        bVar14 = bVar2 < pbVar10[1];
        if (bVar2 != pbVar10[1]) goto LAB_0043926e;
        pbVar4 = pbVar4 + 2;
        pbVar10 = pbVar10 + 2;
      } while (bVar2 != 0);
      iVar7 = 0;
LAB_00439273:
      if (iVar7 == 0) goto LAB_004392cb;
      piVar8 = piVar8 + 1;
      iVar12 = iVar12 + 1;
    } while (iVar12 < num_commands);
  }
  if (iVar7 != 0) {
    uVar5 = 0xffffffff;
    iVar12 = 0;
    pbVar4 = local_100;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      bVar2 = *pbVar4;
      pbVar4 = pbVar4 + 1;
    } while (bVar2 != 0);
    piVar8 = (int *)command_table;
    if (0 < num_commands) {
      do {
        iVar7 = strncmp((char *)local_100,*(char **)*piVar8,~uVar5 - 1);
        if (iVar7 == 0) goto LAB_004392cb;
        piVar8 = piVar8 + 1;
        iVar12 = iVar12 + 1;
      } while (iVar12 < iVar3);
    }
    if (iVar7 != 0) {
      ppuVar9 = &PTR_s_comments_004c5d38;
      if (*line != ';') {
        ppuVar9 = &PTR_s_macros_004c5d28;
      }
      goto LAB_0043930d;
    }
  }
LAB_004392cb:
  uVar5 = 0xffffffff;
  ppuVar9 = (undefined **)((undefined4 *)*piVar8 + 2);
  pcVar11 = *(char **)*piVar8;
  do {
    pcVar13 = pcVar11;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar13 = pcVar11 + 1;
    cVar1 = *pcVar11;
    pcVar11 = pcVar13;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar11 = pcVar13 + -uVar5;
  pcVar13 = line;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
    pcVar11 = pcVar11 + 4;
    pcVar13 = pcVar13 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar13 = *pcVar11;
    pcVar11 = pcVar11 + 1;
    pcVar13 = pcVar13 + 1;
  }
LAB_0043930d:
  help_lines_cur = ppuVar9[1];
  prompt_help_cycle(-1);
  uVar5 = 0xffffffff;
  pcVar11 = &prompt_text;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar11;
    pcVar11 = pcVar11 + 1;
  } while (cVar1 != '\0');
  if (gui_mode == 0) {
    screen_write(text_rows,~uVar5 - 1,line,0);
  }
  return (char)*ppuVar9;
}


/* ==== cmdstack_push @ 00439360 ==== */

void __cdecl cmdstack_push(char *line)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  byte *pbVar9;
  char *pcVar10;
  char *pcVar11;
  bool bVar12;
  
  pbVar4 = (byte *)line;
  pbVar9 = cmdstack_buf;
  do {
    bVar2 = *pbVar4;
    bVar12 = bVar2 < *pbVar9;
    if (bVar2 != *pbVar9) {
LAB_00439398:
      iVar5 = (1 - (uint)bVar12) - (uint)(bVar12 != 0);
      goto LAB_0043939d;
    }
    if (bVar2 == 0) break;
    bVar2 = pbVar4[1];
    bVar12 = bVar2 < pbVar9[1];
    if (bVar2 != pbVar9[1]) goto LAB_00439398;
    pbVar4 = pbVar4 + 2;
    pbVar9 = pbVar9 + 2;
  } while (bVar2 != 0);
  iVar5 = 0;
LAB_0043939d:
  if (iVar5 != 0) {
    if (-1 < cmdstack_size + -2) {
      iVar5 = (cmdstack_size + -2) * 0x100;
      iVar8 = cmdstack_size + -1;
      do {
        uVar6 = 0xffffffff;
        iVar3 = iVar5 + 0x100;
        pcVar10 = cmdstack_buf + iVar5;
        do {
          pcVar11 = pcVar10;
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          pcVar11 = pcVar10 + 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar11;
        } while (cVar1 != '\0');
        uVar6 = ~uVar6;
        iVar5 = iVar5 + -0x100;
        pcVar10 = pcVar11 + -uVar6;
        pcVar11 = cmdstack_buf + iVar3;
        for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
          pcVar10 = pcVar10 + 4;
          pcVar11 = pcVar11 + 4;
        }
        iVar8 = iVar8 + -1;
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar11 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          pcVar11 = pcVar11 + 1;
        }
      } while (iVar8 != 0);
    }
    uVar6 = 0xffffffff;
    do {
      pcVar10 = line;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar10 = line + 1;
      cVar1 = *line;
      line = pcVar10;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar10 = pcVar10 + -uVar6;
    pcVar11 = cmdstack_buf;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar11 = pcVar11 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar11 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar11 = pcVar11 + 1;
    }
  }
  return;
}


/* ==== cmd_read_line @ 00439410 ==== */

void __cdecl cmd_read_line(int dev,char *out)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  char *pcVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int col;
  int iVar10;
  int iVar11;
  char *pcVar12;
  char *pcVar13;
  int iStack_224;
  int iStack_21c;
  int iStack_214;
  char *pcStack_20c;
  char *pcStack_208;
  char acStack_200 [256];
  char acStack_100 [256];
  
  cur_sim = *(int *)(dev_state_tab + dev * 4);
  cur_dev = *(int **)(dev_tab + dev * 4);
  iVar11 = 0;
  cur_itype = *(undefined4 *)(itype_tab + *cur_dev * 4);
  cur_dtype = *(undefined4 *)(chiptype_tab + *cur_dev * 4);
  screen_hold_cnt = 1;
  cmd_linebuf._0_1_ = '\0';
  prompt_show();
  uVar5 = 0xffffffff;
  iStack_21c = 0;
  pcVar4 = &prompt_text;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar3 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar3 != '\0');
  iVar6 = ~uVar5 - 1;
  iStack_224 = 0;
  iStack_214 = 0;
  bVar2 = false;
  bVar1 = false;
  acStack_100[0] = '\0';
  pcStack_208 = (char *)0x0;
  pcStack_20c = (char *)0x0;
LAB_004394b2:
  uVar5 = screen_cols - iVar6;
  iVar10 = uVar5 - 1;
  if (iVar10 < iVar11) {
    iVar11 = iVar10;
  }
  if (bVar1) {
    iStack_21c = (int)*pcStack_208;
    pcStack_208 = pcStack_208 + 1;
    if (iStack_21c == 0) {
      bVar1 = false;
    }
  }
  col = iVar6 + iVar11;
  screen_hold_cnt = (uint)bVar1;
  cursor_set(text_rows,col);
  screen_hold_cnt = 1;
  if (!bVar1) {
    iStack_21c = key_get();
  }
  switch(iStack_21c) {
  default:
    goto switchD_00439545_caseD_3;
  case 5:
    cVar3 = *(char *)((int)&cmd_linebuf + iVar11);
    while (cVar3 != '\0') {
      iVar10 = iVar11 + 1;
      iVar11 = iVar11 + 1;
      cVar3 = *(char *)((int)&cmd_linebuf + iVar10);
    }
    goto LAB_004394b2;
  case 6:
    iStack_224 = iStack_224 + -1;
    if (iStack_224 < 0) {
      iStack_224 = cmdstack_size + -1;
    }
    if (0 < iStack_224) {
      pcVar4 = cmdstack_buf + iStack_224 * 0x100;
      do {
        if (*pcVar4 != '\0') break;
        iStack_224 = iStack_224 + -1;
        pcVar4 = pcVar4 + -0x100;
      } while (0 < iStack_224);
    }
    uVar5 = 0xffffffff;
    pcVar4 = cmdstack_buf + iStack_224 * 0x100;
    do {
      pcVar12 = pcVar4;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar12 = pcVar4 + 1;
      cVar3 = *pcVar4;
      pcVar4 = pcVar12;
    } while (cVar3 != '\0');
    uVar5 = ~uVar5;
    pcVar4 = pcVar12 + -uVar5;
    pcVar12 = acStack_100;
    for (uVar8 = uVar5 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      pcVar12 = pcVar12 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar12 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      pcVar12 = pcVar12 + 1;
    }
  case 2:
    if (iStack_21c == 2) {
      if (iStack_224 < cmdstack_size) {
        pcVar4 = cmdstack_buf + iStack_224 * 0x100;
        do {
          if (*pcVar4 != '\0') break;
          iStack_224 = iStack_224 + 1;
          pcVar4 = pcVar4 + 0x100;
        } while (iStack_224 < cmdstack_size);
        if (cmdstack_size <= iStack_224) goto LAB_0043991a;
      }
      else {
LAB_0043991a:
        iStack_224 = 0;
      }
      uVar5 = 0xffffffff;
      pcVar4 = cmdstack_buf + iStack_224 * 0x100;
      do {
        pcVar12 = pcVar4;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar12 = pcVar4 + 1;
        cVar3 = *pcVar4;
        pcVar4 = pcVar12;
      } while (cVar3 != '\0');
      uVar5 = ~uVar5;
      pcVar4 = pcVar12 + -uVar5;
      pcVar12 = acStack_100;
      for (uVar8 = uVar5 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        pcVar12 = pcVar12 + 4;
      }
      iStack_224 = iStack_224 + 1;
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar12 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        pcVar12 = pcVar12 + 1;
      }
    }
    pcStack_208 = acStack_100;
    bVar1 = true;
switchD_00439545_caseD_1b:
    if ((char)cmd_linebuf != '\0') {
      iVar11 = 0;
      bVar2 = false;
      prompt_show();
      cmd_linebuf._0_1_ = '\0';
    }
    goto LAB_004394b2;
  case 8:
  case 0x7f:
    if ((bVar2) && (iVar11 <= iStack_214)) goto LAB_00439859;
    if (0 < iVar11) {
      uVar5 = 0xffffffff;
      pcVar4 = (char *)((int)&cmd_linebuf + iVar11);
      do {
        pcVar12 = pcVar4;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar12 = pcVar4 + 1;
        cVar3 = *pcVar4;
        pcVar4 = pcVar12;
      } while (cVar3 != '\0');
      uVar5 = ~uVar5;
      pcVar4 = &DAT_004a8fd3 + iVar11;
      pcVar12 = pcVar12 + -uVar5;
      pcVar13 = acStack_200;
      for (uVar8 = uVar5 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar12;
        pcVar12 = pcVar12 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar13 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        pcVar13 = pcVar13 + 1;
      }
      uVar5 = 0xffffffff;
      pcVar12 = acStack_200;
      do {
        pcVar13 = pcVar12;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar13 = pcVar12 + 1;
        cVar3 = *pcVar12;
        pcVar12 = pcVar13;
      } while (cVar3 != '\0');
      uVar5 = ~uVar5;
      pcVar12 = pcVar13 + -uVar5;
      pcVar13 = pcVar4;
      for (uVar8 = uVar5 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar12;
        pcVar12 = pcVar12 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar13 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        pcVar13 = pcVar13 + 1;
      }
      col = iVar6 + iVar11 + -1;
      iVar11 = iVar11 + -1;
      goto LAB_004397b8;
    }
    goto LAB_004394b2;
  case 9:
    cVar3 = *(char *)((int)&cmd_linebuf + iVar11);
    while ((cVar3 != '\0' && (cVar3 != ' '))) {
      iVar10 = iVar11 + 1;
      iVar11 = iVar11 + 1;
      cVar3 = *(char *)((int)&cmd_linebuf + iVar10);
    }
    cVar3 = *(char *)((int)&cmd_linebuf + iVar11);
    while (cVar3 == ' ') {
      iVar10 = iVar11 + 1;
      iVar11 = iVar11 + 1;
      cVar3 = *(char *)((int)&cmd_linebuf + iVar10);
    }
    goto LAB_004394b2;
  case 0xb:
    pcVar4 = (char *)((int)&cmd_linebuf + iVar11);
    if (*(char *)((int)&cmd_linebuf + iVar11) != '\0') {
      uVar5 = 0xffffffff;
      pcVar12 = (char *)((int)&cmd_linebuf + iVar11 + 1);
      do {
        pcVar13 = pcVar12;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar13 = pcVar12 + 1;
        cVar3 = *pcVar12;
        pcVar12 = pcVar13;
      } while (cVar3 != '\0');
      uVar5 = ~uVar5;
      pcVar12 = pcVar13 + -uVar5;
      pcVar13 = acStack_200;
      for (uVar8 = uVar5 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar12;
        pcVar12 = pcVar12 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar13 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        pcVar13 = pcVar13 + 1;
      }
      uVar5 = 0xffffffff;
      pcVar12 = acStack_200;
      do {
        pcVar13 = pcVar12;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar13 = pcVar12 + 1;
        cVar3 = *pcVar12;
        pcVar12 = pcVar13;
      } while (cVar3 != '\0');
      uVar5 = ~uVar5;
      pcVar12 = pcVar13 + -uVar5;
      pcVar13 = pcVar4;
      for (uVar8 = uVar5 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar12;
        pcVar12 = pcVar12 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar13 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        pcVar13 = pcVar13 + 1;
      }
LAB_004397b8:
      screen_write(text_rows,col,pcVar4,0);
      screen_clear_eol();
    }
    goto LAB_004394b2;
  case 0xc:
    if ((bVar2) && (iVar11 <= iStack_214)) {
LAB_00439859:
      iVar11 = 0;
      bVar2 = false;
      prompt_show();
      cmd_linebuf._0_1_ = '\0';
    }
    else {
      iVar11 = iVar11 + -1;
      if (iVar11 < 0) {
        iVar11 = 0;
      }
    }
    goto LAB_004394b2;
  case 0xd:
    if (!bVar2) {
      if ((char)cmd_linebuf == '\0') {
        uVar5 = 0xffffffff;
        pcVar4 = cmdstack_buf;
        do {
          pcVar12 = pcVar4;
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          pcVar12 = pcVar4 + 1;
          cVar3 = *pcVar4;
          pcVar4 = pcVar12;
        } while (cVar3 != '\0');
        uVar5 = ~uVar5;
        pcVar4 = pcVar12 + -uVar5;
        pcVar12 = (char *)&cmd_linebuf;
        for (uVar8 = uVar5 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
          pcVar4 = pcVar4 + 4;
          pcVar12 = pcVar12 + 4;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *pcVar12 = *pcVar4;
          pcVar4 = pcVar4 + 1;
          pcVar12 = pcVar12 + 1;
        }
      }
      else {
        cVar3 = cmd_complete((char *)&cmd_linebuf);
        pcStack_20c = (char *)CONCAT31(extraout_var,cVar3);
        uVar5 = 0xffffffff;
        bVar2 = true;
        pcVar4 = (char *)&cmd_linebuf;
        do {
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          cVar3 = *pcVar4;
          pcVar4 = pcVar4 + 1;
        } while (cVar3 != '\0');
        iStack_214 = ~uVar5 - 1;
      }
    }
    iVar11 = parse_command_line((char *)&cmd_linebuf,1);
    if (iVar11 == 0) {
      iVar11 = cmd_error_position((char *)&cmd_linebuf);
      goto LAB_004394b2;
    }
    cmdstack_push((char *)&cmd_linebuf);
    abort_flag = 0;
    cur_dev[0x12] = 0;
    uVar5 = 0xffffffff;
    pcVar4 = (char *)&cmd_linebuf;
    break;
  case 0xe:
    iVar10 = *(int *)(cur_sim + 0x4400);
    if (iVar10 == 0) {
      scrollback_move(1);
    }
    else if ((0 < iVar10) && (iVar10 < 3)) {
      win_update(1);
    }
    goto LAB_004394b2;
  case 0xf:
    overwrite_mode = (uint)(overwrite_mode == 0);
    goto LAB_004394b2;
  case 0x12:
    if (*(char *)((int)&cmd_linebuf + iVar11) != '\0') {
      iVar11 = iVar11 + 1;
    }
    goto LAB_004394b2;
  case 0x14:
    iVar10 = *(int *)(cur_sim + 0x4400);
    if (iVar10 == 0) {
      scrollback_move(-text_rows);
    }
    else if ((0 < iVar10) && (iVar10 < 3)) {
      win_update(1 - text_rows);
    }
    goto LAB_004394b2;
  case 0x15:
    iVar10 = *(int *)(cur_sim + 0x4400);
    if (iVar10 == 0) {
      scrollback_move(-1);
    }
    else if ((0 < iVar10) && (iVar10 < 3)) {
      win_update(-1);
    }
    goto LAB_004394b2;
  case 0x16:
    iVar10 = *(int *)(cur_sim + 0x4400);
    if (iVar10 == 0) {
      scrollback_move(text_rows);
    }
    else if ((0 < iVar10) && (iVar10 < 3)) {
      win_update(text_rows + -1);
    }
    goto LAB_004394b2;
  case 0x17:
    iVar10 = *(int *)(cur_sim + 0x4400);
    if (iVar10 == 0) {
      *(uint *)(cur_sim + 0x4400) = (*(int *)(cur_sim + 0x3fd8) != 0) + 1;
    }
    else if (iVar10 == 1) {
      *(undefined4 *)(cur_sim + 0x4400) = 0;
    }
    else if (iVar10 == 2) {
      *(undefined4 *)(cur_sim + 0x4400) = 1;
    }
    iVar10 = *(int *)(cur_sim + 0x4400);
    if (iVar10 == 0) {
      scrollback_end(cur_dev_index);
    }
    else if ((0 < iVar10) && (iVar10 < 3)) {
      win_update(0x7fff);
    }
    goto LAB_004394b2;
  case 0x1a:
    *(undefined1 *)((int)&cmd_linebuf + iVar11) = 0;
    screen_clear_eol();
    goto LAB_004394b2;
  case 0x1b:
    goto switchD_00439545_caseD_1b;
  case 0x20:
    if (iVar11 != 0) {
      if (bVar2) {
        if ((&DAT_004a8fd3)[iVar11] == ' ') {
          prompt_help_cycle(1);
          goto LAB_004394b2;
        }
      }
      else {
        cVar3 = cmd_complete((char *)&cmd_linebuf);
        pcStack_20c = (char *)CONCAT31(extraout_var_00,cVar3);
        uVar8 = 0xffffffff;
        pcVar4 = (char *)&cmd_linebuf;
        do {
          if (uVar8 == 0) break;
          uVar8 = uVar8 - 1;
          cVar3 = *pcVar4;
          pcVar4 = pcVar4 + 1;
        } while (cVar3 != '\0');
        iStack_214 = ~uVar8 - 1;
        iVar11 = iStack_214;
        if (iVar10 < iStack_214) {
          iVar11 = iVar10;
        }
        bVar2 = true;
      }
switchD_00439545_caseD_3:
      if (iStack_21c < 0x20) {
        cursor_set(text_rows,iVar6 + iVar11);
        abort_flag = 0;
        cur_dev[0x12] = 0;
      }
      else {
        if ((overwrite_mode == 0) || (*(char *)((int)&cmd_linebuf + iVar11) == '\0')) {
          uVar8 = 0xffffffff;
          pcVar4 = (char *)&cmd_linebuf;
          do {
            if (uVar8 == 0) break;
            uVar8 = uVar8 - 1;
            cVar3 = *pcVar4;
            pcVar4 = pcVar4 + 1;
          } while (cVar3 != '\0');
          if (~uVar8 - 1 < uVar5) {
            uVar5 = 0xffffffff;
            pcVar4 = (char *)((int)&cmd_linebuf + iVar11);
            do {
              pcVar12 = pcVar4;
              if (uVar5 == 0) break;
              uVar5 = uVar5 - 1;
              pcVar12 = pcVar4 + 1;
              cVar3 = *pcVar4;
              pcVar4 = pcVar12;
            } while (cVar3 != '\0');
            uVar5 = ~uVar5;
            pcVar4 = pcVar12 + -uVar5;
            pcVar12 = acStack_200;
            for (uVar8 = uVar5 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
              *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
              pcVar4 = pcVar4 + 4;
              pcVar12 = pcVar12 + 4;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *pcVar12 = *pcVar4;
              pcVar4 = pcVar4 + 1;
              pcVar12 = pcVar12 + 1;
            }
            uVar5 = 0xffffffff;
            pcVar4 = acStack_200;
            do {
              pcVar12 = pcVar4;
              if (uVar5 == 0) break;
              uVar5 = uVar5 - 1;
              pcVar12 = pcVar4 + 1;
              cVar3 = *pcVar4;
              pcVar4 = pcVar12;
            } while (cVar3 != '\0');
            uVar5 = ~uVar5;
            pcVar4 = pcVar12 + -uVar5;
            pcVar12 = (char *)((int)&cmd_linebuf + iVar11 + 1);
            for (uVar8 = uVar5 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
              *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
              pcVar4 = pcVar4 + 4;
              pcVar12 = pcVar12 + 4;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *pcVar12 = *pcVar4;
              pcVar4 = pcVar4 + 1;
              pcVar12 = pcVar12 + 1;
            }
          }
        }
        pcVar4 = (char *)((int)&cmd_linebuf + iVar11);
        col = iVar6 + iVar11;
        *pcVar4 = (char)iStack_21c;
LAB_00439c30:
        screen_write(text_rows,col,pcVar4,0);
        if (iVar11 < iVar10) {
          iVar11 = iVar11 + 1;
        }
      }
      goto LAB_004394b2;
    }
    prompt_help_cycle(1);
    goto LAB_004394b2;
  case 0x3f:
    iVar9 = 0;
    iVar7 = 0;
    if (0 < iVar11) {
      do {
        if (*(char *)((int)&cmd_linebuf + iVar7) == '{') {
          iVar9 = iVar9 + 1;
        }
        else if (*(char *)((int)&cmd_linebuf + iVar7) == '}') {
          iVar9 = iVar9 + -1;
        }
        iVar7 = iVar7 + 1;
      } while (iVar7 < iVar11);
    }
    if (iVar9 == 0) goto code_r0x004399b6;
    if ((overwrite_mode == 0) || (*(char *)((int)&cmd_linebuf + iVar11) == '\0')) {
      uVar8 = 0xffffffff;
      pcVar4 = (char *)&cmd_linebuf;
      do {
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        cVar3 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar3 != '\0');
      if (~uVar8 - 1 < uVar5) {
        uVar5 = 0xffffffff;
        pcVar4 = (char *)((int)&cmd_linebuf + iVar11);
        do {
          pcVar12 = pcVar4;
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          pcVar12 = pcVar4 + 1;
          cVar3 = *pcVar4;
          pcVar4 = pcVar12;
        } while (cVar3 != '\0');
        uVar5 = ~uVar5;
        pcVar4 = pcVar12 + -uVar5;
        pcVar12 = acStack_200;
        for (uVar8 = uVar5 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
          pcVar4 = pcVar4 + 4;
          pcVar12 = pcVar12 + 4;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *pcVar12 = *pcVar4;
          pcVar4 = pcVar4 + 1;
          pcVar12 = pcVar12 + 1;
        }
        uVar5 = 0xffffffff;
        pcVar4 = acStack_200;
        do {
          pcVar12 = pcVar4;
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          pcVar12 = pcVar4 + 1;
          cVar3 = *pcVar4;
          pcVar4 = pcVar12;
        } while (cVar3 != '\0');
        uVar5 = ~uVar5;
        pcVar4 = pcVar12 + -uVar5;
        pcVar12 = (char *)((int)&cmd_linebuf + iVar11 + 1);
        for (uVar8 = uVar5 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
          pcVar4 = pcVar4 + 4;
          pcVar12 = pcVar12 + 4;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *pcVar12 = *pcVar4;
          pcVar4 = pcVar4 + 1;
          pcVar12 = pcVar12 + 1;
        }
      }
    }
    pcVar4 = (char *)((int)&cmd_linebuf + iVar11);
    *pcVar4 = (char)iStack_21c;
    goto LAB_00439c30;
  }
  do {
    pcVar12 = pcVar4;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar12 = pcVar4 + 1;
    cVar3 = *pcVar4;
    pcVar4 = pcVar12;
  } while (cVar3 != '\0');
  uVar5 = ~uVar5;
  pcVar4 = pcVar12 + -uVar5;
  for (uVar8 = uVar5 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)out = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    out = out + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *out = *pcVar4;
    pcVar4 = pcVar4 + 1;
    out = out + 1;
  }
  return;
code_r0x004399b6:
  if (bVar2) {
    help_topic(pcStack_20c);
  }
  else {
    help_list_all();
  }
  goto LAB_004394b2;
}


/* ==== prompt_show @ 00439d80 ==== */

void prompt_show(void)

{
  void *unaff_retaddr;
  
  help_mode = 0;
  help_lines_cur = default_help_lines;
  help_index = 0;
  help_lines_alt = &PTR_s___A__sel_ln_004c5d00;
  if (gui_mode == 0) {
    help_lines_alt = &PTR_s___U__ln_up___N__ln_dn___T__pg_up_004c5ce8;
  }
  if (cur_dev == 0) {
    cur_dev = *(int *)(dev_tab + cur_dev_index * 4);
  }
  sprintf(&prompt_text,&DAT_004c5fbc,*(undefined4 *)(cur_dev + 4));
  screen_hold();
  prompt_help_cycle(0);
  status_line1(&empty_str);
  cmd_linebuf._0_1_ = 0;
  if (gui_mode == 0) {
    screen_write(text_rows,0,&prompt_text,2);
    screen_clear_eol();
  }
  else {
    dsp_free_ext(unaff_retaddr);
  }
  screen_release();
  return;
}


/* ==== status_line1 @ 00439e50 ==== */

void __cdecl status_line1(char *text)

{
  if (gui_mode != 0) {
    ret_true(text);
    return;
  }
  if (text == (char *)0x0) {
    status1_buf = 0;
  }
  else {
    strncpy(&status1_buf,text,0xff);
  }
  screen_write(text_rows + 1,0,&status1_buf,3);
  screen_clear_eol();
  return;
}


/* ==== cmd_error_position @ 00439eb0 ==== */

int __cdecl cmd_error_position(char *line)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  uVar3 = 0xffffffff;
  pcVar7 = &prompt_text;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  iVar2 = screen_cols - (~uVar3 - 1);
  if ((g_err_tok <= iVar2) && (iVar2 = g_err_tok, g_err_tok < 0)) {
    iVar2 = 0;
  }
  uVar3 = 0xffffffff;
  pcVar7 = line;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  if (((int)(~uVar3 - 1) < iVar2) && ((int)(~uVar3 - 1) < screen_cols + -1)) {
    uVar3 = 0xffffffff;
    pcVar7 = &DAT_004c1644;
    do {
      pcVar6 = pcVar7;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar6 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar6;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    iVar4 = -1;
    do {
      pcVar7 = line;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pcVar7 = line + 1;
      cVar1 = *line;
      line = pcVar7;
    } while (cVar1 != '\0');
    pcVar6 = pcVar6 + -uVar3;
    pcVar7 = pcVar7 + -1;
    for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar7 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    }
  }
  status_line1(parm_errmsg);
  return iVar2;
}


/* ==== help_line_edit @ 00439f40 ==== */

int __cdecl help_line_edit(char *line)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *in_stack_00000014;
  int in_stack_00000018;
  int in_stack_0000001c;
  char *in_stack_00000020;
  int iStack_f8;
  char acStack_f0 [240];
  
  uVar3 = 0xffffffff;
  pcVar5 = line;
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
  pcVar6 = (char *)&cmd_linebuf;
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
  if (gui_mode == 0) {
    uVar3 = 0xffffffff;
    pcVar5 = &prompt_text;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    screen_write(text_rows,~uVar3 - 1,(char *)&cmd_linebuf,0);
    help_lines_alt = &PTR_s_____help___T__pg_up___V__pg_dn___004c5d08;
    screen_clear_eol();
    screen_flush();
LAB_0043a005:
    uVar3 = screen_cols - iStack_f8;
    iVar2 = uVar3 - 1;
    if (iVar2 < in_stack_00000018) {
      in_stack_00000018 = iVar2;
    }
    cursor_set(text_rows,iStack_f8 + in_stack_00000018);
    iVar2 = key_get();
    switch(iVar2) {
    case 5:
      cVar1 = *(char *)((int)&cmd_linebuf + in_stack_00000018);
      while (cVar1 != '\0') {
        iVar2 = in_stack_00000018 + 1;
        in_stack_00000018 = in_stack_00000018 + 1;
        cVar1 = *(char *)((int)&cmd_linebuf + iVar2);
      }
      goto LAB_0043a005;
    case 8:
    case 0x7f:
      if (in_stack_0000001c < in_stack_00000018) {
        in_stack_00000018 = in_stack_00000018 + -1;
        goto switchD_0043a049_caseD_b;
      }
      goto LAB_0043a005;
    case 9:
      cVar1 = *(char *)((int)&cmd_linebuf + in_stack_00000018);
      while ((cVar1 != '\0' && (cVar1 != ' '))) {
        iVar2 = in_stack_00000018 + 1;
        in_stack_00000018 = in_stack_00000018 + 1;
        cVar1 = *(char *)((int)&cmd_linebuf + iVar2);
      }
      cVar1 = *(char *)((int)&cmd_linebuf + in_stack_00000018);
      while (cVar1 == ' ') {
        iVar2 = in_stack_00000018 + 1;
        in_stack_00000018 = in_stack_00000018 + 1;
        cVar1 = *(char *)((int)&cmd_linebuf + iVar2);
      }
      goto LAB_0043a005;
    case 0xb:
switchD_0043a049_caseD_b:
      if (*(char *)((int)&cmd_linebuf + in_stack_00000018) != '\0') {
        uVar3 = 0xffffffff;
        pcVar5 = (char *)((int)&cmd_linebuf + in_stack_00000018 + 1);
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
        pcVar6 = acStack_f0;
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
        uVar3 = 0xffffffff;
        pcVar5 = acStack_f0;
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
        pcVar6 = (char *)((int)&cmd_linebuf + in_stack_00000018);
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
        screen_write(text_rows,iStack_f8 + in_stack_00000018,
                     (char *)((int)&cmd_linebuf + in_stack_00000018),0);
        screen_clear_eol();
      }
      goto LAB_0043a005;
    case 0xc:
      in_stack_00000018 = in_stack_00000018 + -1;
      if (in_stack_00000018 < in_stack_0000001c) {
        in_stack_00000018 = in_stack_0000001c;
      }
      goto LAB_0043a005;
    case 0xd:
    case 0xe:
    case 0x15:
      goto switchD_0043a049_caseD_d;
    case 0xf:
      overwrite_mode = (uint)(overwrite_mode == 0);
      goto LAB_0043a005;
    case 0x12:
      if (*(char *)((int)&cmd_linebuf + in_stack_00000018) != '\0') {
        in_stack_00000018 = in_stack_00000018 + 1;
      }
      goto LAB_0043a005;
    case 0x14:
      iVar2 = *(int *)(cur_sim + 0x4400);
      if (iVar2 == 0) {
        scrollback_move(-text_rows);
      }
      else if ((0 < iVar2) && (iVar2 < 3)) {
        win_update(1 - text_rows);
      }
      goto LAB_0043a005;
    case 0x16:
      iVar2 = *(int *)(cur_sim + 0x4400);
      if (iVar2 == 0) {
        scrollback_move(text_rows);
      }
      else if ((0 < iVar2) && (iVar2 < 3)) {
        win_update(text_rows + -1);
      }
      goto LAB_0043a005;
    case 0x1a:
      *(undefined1 *)((int)&cmd_linebuf + in_stack_00000018) = 0;
      screen_clear_eol();
      goto LAB_0043a005;
    case 0x1b:
      prompt_show();
      goto switchD_0043a049_caseD_d;
    case 0x20:
      if ((&DAT_004a8fd3)[in_stack_00000018] == ' ') {
        prompt_help_cycle(1);
        goto LAB_0043a005;
      }
      break;
    case 0x3f:
      goto switchD_0043a049_caseD_3f;
    }
    if (iVar2 < 0x20) {
      cursor_set(text_rows,in_stack_00000018 + 1);
    }
    else {
      if ((overwrite_mode == 0) || (*(char *)((int)&cmd_linebuf + in_stack_00000018) == '\0')) {
        uVar4 = 0xffffffff;
        pcVar5 = (char *)&cmd_linebuf;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar5 + 1;
        } while (cVar1 != '\0');
        if (~uVar4 - 1 < uVar3) {
          uVar3 = 0xffffffff;
          pcVar5 = (char *)((int)&cmd_linebuf + in_stack_00000018);
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
          pcVar6 = acStack_f0;
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
          uVar3 = 0xffffffff;
          pcVar5 = acStack_f0;
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
          pcVar6 = (char *)((int)&cmd_linebuf + in_stack_00000018 + 1);
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
        }
      }
      *(char *)((int)&cmd_linebuf + in_stack_00000018) = (char)iVar2;
      screen_write(text_rows,iStack_f8 + in_stack_00000018,
                   (char *)((int)&cmd_linebuf + in_stack_00000018),0);
      in_stack_00000018 = in_stack_00000018 + 1;
    }
    goto LAB_0043a005;
  }
  iVar2 = ret_true();
  uVar3 = 0xffffffff;
  pcVar5 = (char *)&cmd_linebuf;
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
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)line = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    line = line + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *line = *pcVar5;
    pcVar5 = pcVar5 + 1;
    line = line + 1;
  }
  return iVar2;
switchD_0043a049_caseD_3f:
  help_topic(in_stack_00000020);
  goto LAB_0043a005;
switchD_0043a049_caseD_d:
  uVar3 = 0xffffffff;
  pcVar5 = (char *)&cmd_linebuf;
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
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)in_stack_00000014 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    in_stack_00000014 = in_stack_00000014 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *in_stack_00000014 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    in_stack_00000014 = in_stack_00000014 + 1;
  }
  return iVar2;
}


/* ==== hid_43a3f0 @ 0043a3f0 ==== */

void hid_43a3f0(char *param_1)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  char acStack_200 [256];
  char acStack_100 [256];
  
  uVar2 = 0xffffffff;
  pcVar4 = &g_cmdline + DAT_004a946c;
  do {
    pcVar5 = pcVar4;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar5 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar5;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar5 + -uVar2;
  pcVar5 = acStack_200;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar5 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  }
  path_search(acStack_200,&DAT_004c5fc0,acStack_100);
  if (macro_active == 0) {
    cmdstack_push(param_1);
  }
  macro_push(acStack_100);
  return;
}


