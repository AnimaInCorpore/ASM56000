/* ==== cmd_execute @ 0043b5a0 ==== */

void __cdecl cmd_execute(int dev,char *line)

{
  undefined4 *puVar1;
  
  cur_dev = *(int **)(dev_tab + dev * 4);
  cur_itype = *(undefined4 *)(itype_tab + *cur_dev * 4);
  cur_dtype = *(undefined4 *)(chiptype_tab + *cur_dev * 4);
  cur_sim = *(undefined4 *)(dev_state_tab + dev * 4);
  puVar1 = (undefined4 *)parse_command_line(line,0);
  more_line_count = 0;
  screen_hold();
  log_echo(line,(uint)(macro_active != 0));
  if (puVar1 != (undefined4 *)0x0) {
    (*(code *)*puVar1)(line);
  }
  if (macro_active != 0) {
    screen_flush();
  }
  return;
}


/* ==== iolist_remove @ 0043b640 ==== */

void __cdecl iolist_remove(void *list_head_addr,char *name,int mode)

{
  byte bVar1;
  void *pvVar2;
  void *pvVar3;
  void *p;
  undefined4 *puVar4;
  void *p_00;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  bool bVar8;
  int local_4;
  
  local_4 = 0;
  if (1 < mode) {
    local_4 = mode + -2;
    mode = 2;
  }
  pvVar2 = *(void **)list_head_addr;
joined_r0x0043b671:
  puVar4 = list_head_addr;
  p = pvVar2;
  if (p == (void *)0x0) {
    return;
  }
  pvVar2 = *(void **)((int)p + 0x1e0);
  if (((mode != 2) || (*(int *)((int)p + 0x1e4) != local_4)) && (mode != 1)) goto code_r0x0043b69b;
  goto LAB_0043b6e3;
code_r0x0043b69b:
  list_head_addr = (undefined4 *)((int)p + 0x1e0);
  if (mode == 0) {
    pbVar5 = (byte *)((int)p + 0x100);
    pbVar7 = (byte *)name;
    do {
      bVar1 = *pbVar5;
      bVar8 = bVar1 < *pbVar7;
      if (bVar1 != *pbVar7) {
LAB_0043b6cd:
        iVar6 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
        goto LAB_0043b6d2;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar5[1];
      bVar8 = bVar1 < pbVar7[1];
      if (bVar1 != pbVar7[1]) goto LAB_0043b6cd;
      pbVar5 = pbVar5 + 2;
      pbVar7 = pbVar7 + 2;
    } while (bVar1 != 0);
    iVar6 = 0;
LAB_0043b6d2:
    if (iVar6 == 0) {
LAB_0043b6e3:
      p_00 = *(void **)((int)p + 0x1dc);
      while (p_00 != (void *)0x0) {
        pvVar3 = *(void **)((int)p_00 + 0xc);
        dsp_free(p_00);
        p_00 = pvVar3;
      }
      if (*(void **)((int)p + 0x150) != (void *)0x0) {
        fclose(*(void **)((int)p + 0x150));
      }
      if (*(int *)((int)p + 0x154) == 0) {
        memtag_clear_id(*(int *)((int)p + 0x164),*(ulong *)((int)p + 0x15c));
      }
      if (*(int *)((int)p + 0x154) == 9) {
        iVar6 = *(int *)(*(int *)(cur_sim + 8) + 4 + *(int *)((int)p + 0x158) * 8);
        *(uint *)(iVar6 + *(int *)((int)p + 0x15c) * 4) =
             *(uint *)(iVar6 + *(int *)((int)p + 0x15c) * 4) & ~*(uint *)((int)p + 0x160);
      }
      dsp_free(p);
      *puVar4 = pvVar2;
      list_head_addr = puVar4;
    }
  }
  goto joined_r0x0043b671;
}


/* ==== memtag_clear_id @ 0043b790 ==== */

void __cdecl memtag_clear_id(int id,ulong addr)

{
  int space_size;
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_4;
  
  iVar2 = 0;
  local_4 = 0;
  if (0 < *(int *)(cur_dtype + 0x1c)) {
    iVar3 = 0;
    do {
      space_size = *(int *)(*(int *)(cur_dtype + 0x20) + 0x20 + iVar2);
      iVar1 = rangemap_get((void *)(*(int *)(cur_sim + 4) + 0x10 + iVar3),addr);
      if (id == iVar1) {
        rangemap_set((void *)(*(int *)(cur_sim + 4) + 0x10 + iVar3),addr,addr,space_size,0);
      }
      iVar1 = rangemap_get((void *)(*(int *)(cur_sim + 4) + 0xc + iVar3),addr);
      if (id == iVar1) {
        rangemap_set((void *)(*(int *)(cur_sim + 4) + 0xc + iVar3),addr,addr,space_size,0);
      }
      local_4 = local_4 + 1;
      iVar2 = iVar2 + 0x2c;
      iVar3 = iVar3 + 300;
    } while (local_4 < *(int *)(cur_dtype + 0x1c));
  }
  return;
}


/* ==== iolist_find_id @ 0043b860 ==== */

void __cdecl iolist_find_id(void *list,int id)

{
  for (; (list != (void *)0x0 && (*(int *)((int)list + 0x164) != id));
      list = *(void **)((int)list + 0x1e0)) {
  }
  return;
}


/* ==== iolist_find @ 0043b880 ==== */

void __cdecl iolist_find(void *list,int type,int a,int b)

{
  for (; (list != (void *)0x0 &&
         (((*(int *)((int)list + 0x154) != type || (*(int *)((int)list + 0x158) != a)) ||
          (*(int *)((int)list + 0x15c) != b)))); list = *(void **)((int)list + 0x1e0)) {
  }
  return;
}


/* ==== rangemap_set @ 0043b8c0 ==== */

void __cdecl rangemap_set(void *mapp,ulong lo,ulong hi,int space_size,int value)

{
  uint uVar1;
  bool bVar2;
  int *extraout_EAX;
  int *extraout_EAX_00;
  int *extraout_EAX_01;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  
  if (hi < lo) {
    rangemap_set(mapp,lo,space_size,space_size,value);
    lo = 0;
  }
  piVar6 = *(int **)mapp;
  if (piVar6 == (int *)0x0) {
    dsp_alloc(0x10,0);
    if (extraout_EAX == (int *)0x0) {
      return;
    }
    *extraout_EAX = 0;
    extraout_EAX[1] = 0;
    extraout_EAX[2] = space_size;
    extraout_EAX[3] = 0;
    *(int **)mapp = extraout_EAX;
    piVar6 = extraout_EAX;
  }
  uVar1 = piVar6[2];
  piVar4 = (int *)0x0;
  while (uVar1 < lo) {
    uVar1 = ((int *)piVar6[3])[2];
    piVar4 = piVar6;
    piVar6 = (int *)piVar6[3];
  }
  if (*piVar6 == value) {
    if (hi < (uint)piVar6[2]) {
      return;
    }
    piVar6[2] = hi;
  }
  else {
    if (hi < (uint)piVar6[2]) {
      dsp_alloc(0x10,0);
      if (extraout_EAX_00 == (int *)0x0) {
        return;
      }
      extraout_EAX_00[3] = piVar6[3];
      extraout_EAX_00[2] = piVar6[2];
      extraout_EAX_00[1] = hi + 1;
      *extraout_EAX_00 = *piVar6;
      piVar5 = extraout_EAX_00;
    }
    else {
      piVar5 = (int *)piVar6[3];
    }
    if ((uint)piVar6[1] < lo) {
      dsp_alloc(0x10,0);
      if (extraout_EAX_01 == (int *)0x0) {
        return;
      }
      piVar6[3] = (int)extraout_EAX_01;
      piVar6[2] = lo - 1;
      piVar3 = extraout_EAX_01;
    }
    else {
      piVar3 = piVar6;
      if (piVar4 != (int *)0x0) {
        piVar6 = piVar4;
      }
    }
    piVar3[1] = lo;
    *piVar3 = value;
    piVar3[2] = hi;
    piVar3[3] = (int)piVar5;
  }
  bVar2 = false;
  piVar4 = (int *)piVar6[3];
  if ((int *)piVar6[3] == (int *)0x0) {
    return;
  }
  do {
    if ((uint)piVar6[2] < (uint)piVar4[2]) {
      if (*piVar4 == *piVar6) {
        piVar6[3] = piVar4[3];
        piVar6[2] = piVar4[2];
        dsp_free(piVar4);
        piVar5 = (int *)piVar6[3];
      }
      else {
        if ((uint)piVar4[1] <= (uint)piVar6[2]) {
          piVar4[1] = piVar6[2] + 1;
          return;
        }
        if (bVar2) {
          return;
        }
        piVar5 = (int *)piVar4[3];
        bVar2 = true;
        piVar6 = piVar4;
      }
    }
    else {
      piVar6[3] = piVar4[3];
      dsp_free(piVar4);
      piVar5 = (int *)piVar6[3];
    }
    piVar4 = piVar5;
    if (piVar5 == (int *)0x0) {
      return;
    }
  } while( true );
}


/* ==== rangemap_get @ 0043ba40 ==== */

int __cdecl rangemap_get(void *mapp,ulong addr)

{
  int *piVar1;
  uint uVar2;
  
  piVar1 = *(int **)mapp;
  if (piVar1 != (int *)0x0) {
    uVar2 = piVar1[2];
    while (uVar2 < addr) {
      piVar1 = (int *)piVar1[3];
      uVar2 = piVar1[2];
    }
    return *piVar1;
  }
  return 0;
}


/* ==== prompt_help_cycle @ 0043ba70 ==== */

void __cdecl prompt_help_cycle(int step)

{
  undefined4 *puVar1;
  
  if (step == -1) {
    help_mode = 0;
    help_index = 0;
  }
  if (step == 1) {
    help_index = help_index + 1;
  }
  puVar1 = help_lines_alt;
  if (help_mode == 0) {
    puVar1 = help_lines_cur;
  }
  if (puVar1[help_index] == 0) {
    help_index = 0;
    if (help_mode != 0) {
      help_mode = 0;
      status_line2((char *)*help_lines_cur);
      return;
    }
    help_mode = 1;
    puVar1 = help_lines_alt;
  }
  status_line2((char *)puVar1[help_index]);
  return;
}


/* ==== status_line2 @ 0043bb00 ==== */

void __cdecl status_line2(char *text)

{
  undefined4 uStack00000008;
  
  if (gui_mode != 0) {
    ret_true(text);
    return;
  }
  strncpy(&status2_buf,text,99);
  screen_write(text_rows + 2,0,text,3);
  uStack00000008 = 0x43bb48;
  screen_clear_eol();
  return;
}


/* ==== display_refresh @ 0043bb50 ==== */

void __cdecl display_refresh(int full)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  uVar5 = 0;
  uVar1 = *(uint *)(cur_dtype + 0x14);
  if (uVar1 != 0) {
    iVar6 = 0;
    do {
      iVar7 = *(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + iVar6) + 0x28);
      puVar3 = *(uint **)(*(int *)(cur_sim + 8) + 4 + uVar5 * 8);
      if (iVar7 != 0) {
        iVar4 = 0;
        do {
          uVar2 = *puVar3;
          if ((*(byte *)(*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + iVar6) + 0x2c) + 0x10
                        + iVar4) & 0x10) == 0) {
            if ((((uVar2 & 0x10) == 0) && (((uVar2 & 0x20) == 0 || ((uVar2 & 0x40000) == 0)))) &&
               (((uVar2 & 0x40) == 0 || ((uVar2 & 0x80000) == 0)))) {
              uVar2 = uVar2 & 0xfffff7ff;
            }
            else {
              uVar2 = uVar2 | 0x800;
            }
            *puVar3 = uVar2;
          }
          iVar4 = iVar4 + 0x1c;
          puVar3 = puVar3 + 1;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
      uVar5 = uVar5 + 1;
      iVar6 = iVar6 + 0x48;
    } while (uVar5 < uVar1);
  }
  memtag_rebuild();
  display_all(full);
  return;
}


/* ==== memtag_rebuild @ 0043bc00 ==== */

void memtag_rebuild(void)

{
  undefined4 *mapp;
  int space_size;
  int *piVar1;
  ulong uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 *mapp_00;
  int local_14;
  int local_10;
  int local_4;
  
  local_4 = *(int *)(cur_dtype + 0x1c);
  if (local_4 != 0) {
    local_14 = 0;
    local_10 = 0;
    do {
      space_size = *(int *)(*(int *)(cur_dtype + 0x20) + 0x20 + local_14);
      mapp_00 = (undefined4 *)(*(int *)(cur_sim + 4) + local_10);
      piVar1 = (int *)*mapp_00;
      mapp = mapp_00 + 1;
      rangemap_set(mapp,0,0xffffffff,-1,0);
      for (; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[3]) {
        if (*piVar1 == 1) {
          rangemap_set(mapp,piVar1[1],piVar1[2],space_size,1);
        }
      }
      if ((*(uint *)(*(int *)(cur_dtype + 0x20) + 0x18 + local_14) & 0x2000) != 0) {
        uVar3 = mapp_00[0x28];
        if (0x10 < uVar3) {
          uVar3 = 0x10;
        }
        iVar5 = mapp_00[0x29];
        for (; uVar3 != 0; uVar3 = uVar3 - 1) {
          if (iVar5 < 0) {
            iVar5 = 0xf;
          }
          uVar2 = mapp_00[iVar5 + 0x2b];
          iVar4 = rangemap_get(mapp_00,uVar2);
          if ((iVar4 == 2) || (iVar4 == 3)) {
            rangemap_set(mapp,uVar2,uVar2,space_size,1);
          }
          iVar5 = iVar5 + -1;
        }
        uVar3 = mapp_00[5];
        if (0x10 < uVar3) {
          uVar3 = 0x10;
        }
        iVar5 = mapp_00[6];
        for (; uVar3 != 0; uVar3 = uVar3 - 1) {
          if (iVar5 < 0) {
            iVar5 = 0xf;
          }
          uVar2 = mapp_00[iVar5 + 8];
          iVar4 = rangemap_get(mapp_00,uVar2);
          if (((iVar4 == 3) || (iVar4 == 4)) || (iVar4 == 1)) {
            rangemap_set(mapp,uVar2,uVar2,space_size,2);
          }
          iVar5 = iVar5 + -1;
        }
      }
      local_10 = local_10 + 300;
      local_14 = local_14 + 0x2c;
      local_4 = local_4 + -1;
    } while (local_4 != 0);
  }
  return;
}


/* ==== fmt_float_exp @ 0043bd90 ==== */

char __cdecl fmt_float_exp(char *fmt,int *dbl)

{
  int *piVar1;
  char cVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  
  piVar1 = dbl;
  uVar4 = dbl[1];
  uVar5 = uVar4 & 0x80000000;
  if ((uVar4 & 0x7ff00000) == 0x7ff00000) {
    if ((*dbl == 0) && ((uVar4 & 0xfffff) == 0)) {
      cVar2 = ',';
      if (uVar5 == 0) {
        return '(';
      }
    }
    else {
      cVar2 = ' ';
      if (uVar5 == 0) {
        return '\x1c';
      }
    }
  }
  else {
    cVar2 = strrchr(fmt,0x2e);
    sscanf((char *)(CONCAT31(extraout_var,cVar2) + 1),&DAT_004c5578,&dbl);
    if ((*piVar1 == 0) && ((piVar1[1] & 0x7fffffffU) == 0)) {
      pcVar6 = s__0_000000000000000000e_00_004c6200;
      if (uVar5 == 0) {
        pcVar6 = s_0_0000000000000000000e_00_004c61e4;
      }
      uVar4 = 0xffffffff;
      do {
        pcVar3 = pcVar6;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar3 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar3;
      } while (cVar2 != '\0');
      uVar4 = ~uVar4;
      pcVar6 = pcVar3 + -uVar4;
      pcVar3 = (char *)&float_fmt_buf;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar3 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar3 = pcVar3 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar3 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar3 = pcVar3 + 1;
      }
    }
    else {
      sprintf((char *)&float_fmt_buf,s___26_24e_004c61d8,*piVar1,piVar1[1]);
    }
    cVar2 = strchr((char *)&float_fmt_buf,0x65);
    pcVar6 = (char *)CONCAT31(extraout_var_00,cVar2);
    if ((pcVar6[2] == '0') && (pcVar6[4] != '\0')) {
      cVar2 = pcVar6[3];
      pcVar6[3] = pcVar6[4];
      pcVar6[2] = cVar2;
      pcVar6[4] = pcVar6[5];
    }
    uVar4 = 0xffffffff;
    pcVar3 = pcVar6;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar2 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar2 != '\0');
    uVar4 = ~uVar4;
    if (-1 < (int)(uVar4 - 1)) {
      pcVar3 = (char *)((int)dbl + ((int)&float_fmt_buf - (uVar4 - 1)));
      do {
        cVar2 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        *pcVar3 = cVar2;
        pcVar3 = pcVar3 + 1;
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
    }
    cVar2 = -0x68;
  }
  return cVar2;
}


/* ==== fmt_register @ 0043bec0 ==== */

int __cdecl fmt_register(int bank,int reg,int radix,char *out)

{
  char cVar1;
  long lVar2;
  uint uVar3;
  char *pcVar4;
  undefined3 extraout_var;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  ulong uStack_34;
  undefined4 uStack_30;
  int local_28;
  undefined4 uStack_24;
  ulong local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 local_c;
  
  uVar6 = *(uint *)(*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + bank * 0x48) + 0x2c) +
                    0x10 + reg * 0x1c);
  lVar2 = periph_call(*(int *)(cur_dev + 4),bank,reg,(long)&local_20);
  if (lVar2 == 0) {
    sim_error(s_Error_reading_register_004c6178);
    return 0;
  }
  local_c = CONCAT22((short)((uVar6 & 0xfffc0007) >> 0x10),CONCAT11(1,(char)(uVar6 & 0xfffc0007)));
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar3 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar3 = (**(code **)(cur_dtype + 0x4e8))();
  }
  uVar7 = uVar3 >> 0x1c & 1;
  uVar8 = uVar3 >> 7 & 1;
  uVar5 = uVar3 >> 0xc & 1;
  if (radix != 2) {
    if ((radix == 1) || (radix == 4)) {
      if ((uVar6 & 0xc0000000) == 0) {
        if ((uVar6 & 0x10000000) == 0) {
          if ((uVar8 == 0) && (((uVar6 & 0x2000000) == 0 || ((uVar6 & 0x2000) != 0)))) {
            if ((uVar6 & 1) == 0) {
              if ((uVar6 & 2) == 0) {
                val_to_dec_parts2(uVar3,&local_20,&uStack_34);
                pcVar4 = s__06lu_09lu_004c6250;
                if (uVar7 == 0) {
                  pcVar4 = s__08lu_09lu_004c6244;
                }
                sprintf(out,pcVar4,uStack_30,uStack_34);
                return 1;
              }
              val_to_dec_parts(uVar3,&local_20,(long *)&uStack_34);
              sprintf(out,s__06lu_09lu_004c6250,uStack_30,uStack_34);
              return 1;
            }
            if (radix == 1) {
              if (uVar7 == 0) {
                pcVar4 = s__06ld_004c6264;
              }
              else {
                pcVar4 = s__05ld_004c6274;
              }
            }
            else {
              pcVar4 = s__05lu_004c626c;
              if (uVar7 == 0) {
                pcVar4 = s__06lu_004c625c;
              }
            }
          }
          else {
            pcVar4 = s__011ld_004c623c;
            if (radix != 1) {
              pcVar4 = s__011lu_004c6234;
            }
          }
        }
        else {
          pcVar4 = s__05ld_004c6274;
          if (radix != 1) {
            pcVar4 = s__05lu_004c626c;
          }
        }
      }
      else {
        pcVar4 = s__03ld_004c6284;
        if (radix != 1) {
          pcVar4 = s__03lu_004c627c;
        }
      }
    }
    else if ((uVar6 & 0x80000000) == 0) {
      if ((uVar6 & 0x40000000) == 0) {
        if ((uVar6 & 0x10000000) == 0) {
          if ((uVar6 & 0x4000000) == 0) {
            if ((uVar6 & 1) == 0) {
              if ((uVar6 & 2) != 0) {
                if (uVar7 == 0) {
                  if (uVar8 == 0) {
                    pcVar4 = s___02lx_06lx_004c62f4;
                    if (uVar5 == 0) {
                      pcVar4 = s___06lx_06lx_004c62e8;
                    }
                  }
                  else {
                    pcVar4 = s___08lx_08lx_004c6300;
                  }
                }
                else {
                  pcVar4 = s___04lx_04lx_004c630c;
                }
                sprintf(out,pcVar4,uStack_1c,local_20);
                return 1;
              }
              if (uVar5 == 0) {
                if ((uVar3 >> 0x18 & 1) == 0) {
                  if (uVar7 == 0) {
                    pcVar4 = s___08lx_08lx_08lx_004c62a0;
                    if (uVar8 == 0) {
                      pcVar4 = s___02lx_06lx_06lx_004c628c;
                    }
                  }
                  else {
                    pcVar4 = s___02lx_04lx_04lx_004c62b4;
                  }
                }
                else {
                  pcVar4 = s___01lx_04lx_04lx_004c62c8;
                }
                sprintf(out,pcVar4,uStack_18,uStack_1c,local_20);
                return 1;
              }
              sprintf(out,s___04lx_06lx_004c62dc,uStack_1c,local_20);
              return 1;
            }
            if (uVar7 == 0) {
              if ((uVar8 == 0) && (((uVar6 & 0x2000000) == 0 || ((uVar6 & 0x2000) != 0)))) {
                pcVar4 = s___06lx_004c6320;
              }
              else {
                pcVar4 = s___08lx_004c6318;
              }
            }
            else {
              pcVar4 = s___04lx_004c6328;
            }
          }
          else {
            pcVar4 = s___06lx_004c6320;
          }
        }
        else {
          pcVar4 = s___04lx_004c6328;
        }
      }
      else {
        pcVar4 = s___02lx_004c6330;
      }
    }
    else {
      pcVar4 = &DAT_004c6338;
    }
    sprintf(out,pcVar4,local_20);
    return 1;
  }
  node_to_double(uVar3,&local_28);
  if (uVar8 == 0) {
    if ((uVar6 & 1) == 0) {
      pcVar4 = s__13_10f_004c6348;
      if (uVar7 == 0) {
        pcVar4 = s__18_15f_004c6340;
      }
    }
    else if (uVar7 == 0) {
      if ((uVar6 & 0xd0000000) == 0) {
        pcVar4 = s__10_7f_004c6350;
      }
      else {
        pcVar4 = s__6_3f_004c6358;
      }
    }
    else {
      pcVar4 = s__8_5f_004c6360;
    }
    sprintf(out,pcVar4,local_28,uStack_24);
    return 1;
  }
  pcVar4 = s__12_12s_004c6370;
  if ((uVar6 & 1) == 0) {
    pcVar4 = s__22_22s_004c6368;
  }
  cVar1 = fmt_float_exp(pcVar4,&local_28);
  uVar6 = 0xffffffff;
  pcVar4 = (char *)CONCAT31(extraout_var,cVar1);
  do {
    pcVar9 = pcVar4;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar9 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar9;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar4 = pcVar9 + -uVar6;
  for (uVar3 = uVar6 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)out = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    out = out + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *out = *pcVar4;
    pcVar4 = pcVar4 + 1;
    out = out + 1;
  }
  return 1;
}


