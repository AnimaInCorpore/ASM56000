/* ==== macro_read_line @ 0043a470 ==== */

void __cdecl macro_read_line(int dev,char *out)

{
  char cVar1;
  int iVar2;
  uint c;
  uint uVar3;
  int extraout_EAX;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  
  cur_dev = *(int **)(dev_tab + dev * 4);
  cur_itype = *(undefined4 *)(itype_tab + *cur_dev * 4);
  cur_dtype = *(undefined4 *)(chiptype_tab + *cur_dev * 4);
  uVar4 = 0xffffffff;
  cur_sim = *(undefined4 *)(dev_state_tab + dev * 4);
  pcVar6 = &prompt_text;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  iVar2 = abort_check();
  if (iVar2 == 0) {
    if (macro_fp != (void *)0x0) {
      do {
        *out = '\0';
        iVar2 = 0;
        do {
          if (__mb_cur_max < 2) {
            c = fgetc(macro_fp);
            uVar3 = (byte)_pctype[c * 2] & 8;
          }
          else {
            c = fgetc(macro_fp);
            uVar3 = _isctype(c,8);
          }
        } while (uVar3 != 0);
        iVar5 = 0;
        if (c == 10) {
LAB_0043a5a9:
          out[iVar5] = '\0';
          parse_command_line(out);
          iVar2 = extraout_EAX;
          if (extraout_EAX == 0) {
            sim_error(s_Error_in_Macro_004c5fc8);
            log_echo(out,1);
            goto LAB_0043a600;
          }
        }
        else {
          do {
            if (c == 0xffffffff) break;
            if (c < 0x80) {
              if (__mb_cur_max < 2) {
                uVar3 = *(ushort *)(_pctype + c * 2) & 0x157;
              }
              else {
                uVar3 = _isctype(c,0x157);
              }
              if (((uVar3 != 0) || (c == 9)) && (iVar5 < (int)(0x100 - (~uVar4 - 1)))) {
                out[iVar5] = (char)c;
                iVar5 = iVar5 + 1;
              }
            }
            c = fgetc(macro_fp);
          } while (c != 10);
          if (c == 10) goto LAB_0043a5a9;
        }
        if ((iVar2 != 0) && ((*(byte *)(iVar2 + 4) & 1) == 0)) {
          return;
        }
        if ((c == 0xffffffff) && (macro_pop(), macro_fp == (void *)0x0)) {
          return;
        }
      } while( true );
    }
  }
  else {
LAB_0043a600:
    macro_abort_all();
  }
  return;
}


/* ==== macro_pop @ 0043a610 ==== */

void macro_pop(void)

{
  char *name;
  void *stream;
  
  if (macro_fp != (void *)0x0) {
    fclose(macro_fp);
  }
  macro_fp = (void *)0x0;
  if (macro_stack == (void *)0x0) {
    macro_active = macro_stack;
    return;
  }
  name = *(char **)((int)macro_stack + 0x104);
  dsp_free(macro_stack);
  macro_stack = name;
  if (name == (char *)0x0) {
    macro_active = name;
    return;
  }
  fopen(name,&DAT_004c5ff4);
  macro_fp = stream;
  if (stream == (void *)0x0) {
    sim_error(s_Error_opening_macro_file__004c5fd8);
    macro_abort_all();
    return;
  }
  fseek(stream,*(long *)(name + 0x100),0);
  return;
}


/* ==== macro_push @ 0043a6a0 ==== */

void __cdecl macro_push(char *filename)

{
  char cVar1;
  long lVar2;
  char *p;
  void *extraout_EAX;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  if (macro_active != 0) {
    lVar2 = ftell(macro_fp);
    *(long *)((int)macro_stack + 0x100) = lVar2;
    fclose(macro_fp);
  }
  dsp_alloc(0x108,0);
  if (p != (char *)0x0) {
    fopen(filename,&DAT_004c5ff4);
    macro_fp = extraout_EAX;
    if (extraout_EAX != (void *)0x0) {
      uVar3 = 0xffffffff;
      *(char **)(p + 0x104) = macro_stack;
      do {
        pcVar5 = filename;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar5 = filename + 1;
        cVar1 = *filename;
        filename = pcVar5;
      } while (cVar1 != '\0');
      uVar3 = ~uVar3;
      pcVar5 = pcVar5 + -uVar3;
      pcVar6 = p;
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
      macro_stack = p;
      macro_active = 1;
      return;
    }
  }
  sim_error(s_Error_opening_macro_file_004c5ff8);
  if (p != (char *)0x0) {
    dsp_free(p);
  }
  macro_abort_all();
  return;
}


/* ==== macro_abort_all @ 0043a770 ==== */

void macro_abort_all(void)

{
  void *p;
  
  if (macro_fp != (void *)0x0) {
    fclose(macro_fp);
  }
  macro_fp = (void *)0x0;
  p = macro_stack;
  while (p != (void *)0x0) {
    macro_stack = *(void **)((int)p + 0x104);
    dsp_free(p);
    p = macro_stack;
  }
  macro_stack = p;
  macro_active = 0;
  return;
}


/* ==== confirm_overwrite @ 0043a7c0 ==== */

int __cdecl confirm_overwrite(char *filename,int mode)

{
  int iVar1;
  char cVar2;
  
  screen_flush();
  iVar1 = _access(filename,0);
  if (iVar1 != 0) {
    return 0;
  }
  if (mode == 0) {
    if (gui_mode == 0) {
      status_line1(s_A_file_with_the_same_name_curren_004c6048);
      status_line2(s__a___append__o___overwrite__c___c_004c6014);
      iVar1 = key_get();
      cVar2 = (char)iVar1;
      while (((cVar2 != 'a' && (cVar2 = (char)iVar1, cVar2 != 'o')) && (cVar2 != 'c'))) {
        iVar1 = key_get();
        cVar2 = (char)iVar1;
      }
      filename = (char *)CONCAT31(filename._1_3_,cVar2);
      screen_putc(filename,(int)filename);
      status_line1(&empty_str);
      status_line2(&empty_str);
    }
    else {
      iVar1 = ret_99();
      cVar2 = (char)iVar1;
    }
  }
  else if (mode == 1) {
    cVar2 = 'a';
  }
  else {
    cVar2 = (-(mode != 2) & 0xcU) + 99;
  }
  if (cVar2 != 'a') {
    if (cVar2 != 'c') {
      return 0;
    }
    return -1;
  }
  return 1;
}


/* ==== show_running_banner @ 0043a8b0 ==== */

void show_running_banner(void)

{
  uint uVar1;
  char *fmt;
  undefined4 in_stack_ffffffa4;
  undefined4 in_stack_ffffffa8;
  undefined4 in_stack_ffffffac;
  undefined4 in_stack_ffffffb0;
  undefined4 in_stack_ffffffb4;
  undefined4 in_stack_ffffffb8;
  undefined4 in_stack_ffffffbc;
  undefined4 in_stack_ffffffc0;
  undefined4 in_stack_ffffffc4;
  undefined4 in_stack_ffffffc8;
  undefined4 in_stack_ffffffcc;
  undefined4 in_stack_ffffffd0;
  undefined4 in_stack_ffffffd4;
  undefined4 in_stack_ffffffd8;
  undefined4 in_stack_ffffffdc;
  undefined4 in_stack_ffffffe0;
  undefined4 in_stack_ffffffe4;
  undefined4 in_stack_ffffffe8;
  undefined4 in_stack_ffffffec;
  undefined4 in_stack_fffffff0;
  undefined4 in_stack_fffffff4;
  undefined4 in_stack_fffffff8;
  undefined4 in_stack_fffffffc;
  
  if (gui_mode == 0) {
    if (*(int *)(cur_dev + 4) == cur_dev_index) {
      if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
        uVar1 = *(uint *)(cur_dtype + 0xc);
      }
      else {
        uVar1 = (**(code **)(cur_dtype + 0x4e8))();
      }
      fmt = s__SIMULATION_IN_PROGRESS___Enter_C_004c60d0;
      if ((uVar1 & 0x200) == 0) {
        fmt = s__SIMULATION_IN_PROGRESS___Enter_C_004c6088;
      }
      sprintf(&stack0xffffffa4,fmt,cur_dev_index,*(undefined4 *)(cur_dev + 0x1c),
              *(undefined4 *)(cur_dev + 0x20));
      status_line1(&stack0xffffffa4);
    }
    screen_flush(in_stack_ffffffa4,in_stack_ffffffa8,in_stack_ffffffac,in_stack_ffffffb0,
                 in_stack_ffffffb4,in_stack_ffffffb8,in_stack_ffffffbc,in_stack_ffffffc0,
                 in_stack_ffffffc4,in_stack_ffffffc8,in_stack_ffffffcc,in_stack_ffffffd0,
                 in_stack_ffffffd4,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,
                 in_stack_ffffffe4,in_stack_ffffffe8,in_stack_ffffffec,in_stack_fffffff0,
                 in_stack_fffffff4,in_stack_fffffff8,in_stack_fffffffc);
  }
  return;
}


/* ==== memtag_add @ 0043a930 ==== */

void __cdecl memtag_add(int flags,int region,ulong lo,ulong hi,int kind)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar7 = 0;
  uVar1 = *(uint *)(*(int *)(cur_dtype + 0x20) + 8 + region * 0x2c);
  if (0 < *(int *)(cur_dtype + 0x1c)) {
    iVar6 = 0;
    iVar5 = 0;
    iVar4 = cur_dtype;
    do {
      iVar3 = *(int *)(iVar4 + 0x20) + iVar6;
      uVar2 = *(uint *)(iVar3 + 8);
      if (((uVar2 & uVar1) == uVar2) && ((char)uVar2 == (char)uVar1)) {
        if ((flags & 1U) == 0) {
          iVar4 = *(int *)(cur_sim + 4) + 0x10;
        }
        else {
          iVar4 = *(int *)(cur_sim + 4) + 0xc;
        }
        rangemap_set((void *)(iVar4 + iVar5),lo,hi,*(int *)(iVar3 + 0x20),kind);
        iVar4 = cur_dtype;
      }
      iVar7 = iVar7 + 1;
      iVar5 = iVar5 + 300;
      iVar6 = iVar6 + 0x2c;
    } while (iVar7 < *(int *)(iVar4 + 0x1c));
  }
  return;
}


/* ==== disasm_line @ 0043a9d0 ==== */

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl disasm_line(ulong space,ulong addr,char *out,int arg)

{
  char cVar1;
  long lVar2;
  int iVar3;
  undefined *puVar4;
  char *pcVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint *puVar10;
  int iVar11;
  undefined4 *puVar12;
  char *pcVar13;
  undefined4 *puVar14;
  char *pcVar15;
  int iStack_1d4;
  long lStack_1d0;
  uint local_1cc;
  uint uStack_1c8;
  undefined *puStack_1c4;
  char *pcStack_1c0;
  int iStack_1bc;
  undefined4 local_1b8;
  undefined4 uStack_1b4;
  uint uStack_1b0;
  uint uStack_1ac;
  uint uStack_1a8;
  uint uStack_1a4;
  uint uStack_1a0;
  uint auStack_19c [9];
  char acStack_178 [39];
  char acStack_151 [257];
  char acStack_50 [40];
  char acStack_28 [40];
  
  local_1b8 = 0;
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    local_1cc = *(uint *)(cur_dtype + 0xc);
  }
  else {
    local_1cc = (**(code **)(cur_dtype + 0x4e8))();
  }
  puVar12 = &DAT_004dc278;
  puVar14 = &DAT_004dc308;
  for (iVar6 = 0x23; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar14 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar14 = puVar14 + 1;
  }
  pcStack_1c0 = (char *)(local_1cc & 0x4000000);
  if (pcStack_1c0 == (char *)0x0) {
    uStack_1c8 = (-(uint)((local_1cc & 0x10000000) != 0) & 0x10000) - 1;
  }
  else {
    uStack_1c8 = 0xffffff;
  }
  lVar2 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2924,&iStack_1d4,&lStack_1d0);
  if (lVar2 == 0) {
    uStack_1b4 = 0;
  }
  else {
    lVar2 = periph_call(*(int *)(cur_dev + 4),iStack_1d4,lStack_1d0,(long)&uStack_1b4);
    if (lVar2 == 0) goto LAB_0043af86;
  }
  lVar2 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2950,&iStack_1d4,&lStack_1d0);
  if (lVar2 == 0) {
    local_1b8 = 0;
  }
  else {
    lVar2 = periph_call(*(int *)(cur_dev + 4),iStack_1d4,lStack_1d0,(long)&local_1b8);
    if (lVar2 == 0) goto LAB_0043af86;
  }
  iVar6 = memmap_find(space,addr);
  puVar12 = *(undefined4 **)(cur_dtype + 0x28);
  iStack_1bc = *(undefined4 *)(*(int *)(cur_dtype + 0x20) + iVar6 * 0x2c);
  if ((code *)puVar12[9] == (code *)0x0) {
    if ((code *)puVar12[5] == (code *)0x0) {
      iVar6 = (*(code *)*puVar12)(space,addr,&uStack_1a0);
    }
    else {
      iVar6 = (*(code *)puVar12[5])(space,addr,&uStack_1a0,arg);
    }
  }
  else {
    iVar6 = (*(code *)puVar12[9])(space,addr,&uStack_1a0,arg);
  }
  uStack_1a8 = (uint)(iVar6 == 0);
  if (iVar6 == 0) {
    iVar6 = 1;
  }
  puVar12 = *(undefined4 **)(cur_dtype + 0x28);
  iVar11 = iVar6;
  if (puVar12[9] == 0) {
    if ((code *)puVar12[5] == (code *)0x0) {
      iVar11 = (*(code *)*puVar12)(space,iVar6 + addr,auStack_19c);
    }
    else {
      iVar11 = (*(code *)puVar12[5])(space,iVar6 + addr,auStack_19c,arg);
    }
  }
  uStack_1b0 = (uint)(iVar11 == 0);
  if (iVar11 == 0) {
    iVar11 = 1;
  }
  puVar12 = *(undefined4 **)(cur_dtype + 0x28);
  iVar3 = iVar6;
  if (puVar12[9] == 0) {
    if ((code *)puVar12[5] == (code *)0x0) {
      iVar3 = (*(code *)*puVar12)(space,iVar11 + iVar6 + addr,auStack_19c + 1);
    }
    else {
      iVar3 = (*(code *)puVar12[5])(space,iVar11 + iVar6 + addr,auStack_19c + 1,arg);
    }
  }
  uStack_1ac = (uint)(iVar3 == 0);
  if (iVar3 == 0) {
    iVar3 = 1;
  }
  puVar12 = *(undefined4 **)(cur_dtype + 0x28);
  if (puVar12[9] == 0) {
    if ((code *)puVar12[5] == (code *)0x0) {
      iVar6 = (*(code *)*puVar12)(space,iVar3 + iVar11 + iVar6 + addr,auStack_19c + 2);
    }
    else {
      iVar6 = (*(code *)puVar12[5])(space,iVar3 + iVar11 + iVar6 + addr,auStack_19c + 2,arg);
    }
  }
  pcVar5 = pcStack_1c0;
  uStack_1a4 = (uint)(iVar6 == 0);
  if ((local_1cc & 8) == 0) {
    if ((local_1cc & 0x400) == 0) {
      puVar4 = &DAT_004c61d0;
      if ((local_1cc & 0x10) == 0) {
        puVar4 = &DAT_004c61cc;
      }
    }
    else {
      puVar4 = &DAT_004c61d4;
    }
  }
  else {
    puVar4 = &DAT_004c61d4;
  }
  if ((local_1cc & 0x2000000) == 0) {
    puStack_1c4 = &DAT_004c61cc;
    if (pcStack_1c0 == (char *)0x0) {
      puStack_1c4 = &DAT_004c61d4;
    }
  }
  else {
    puStack_1c4 = &DAT_004c61d0;
  }
  if ((local_1cc & 0x2000000) == 0) {
    pcStack_1c0 = s__004c61b8;
    if (pcVar5 == (char *)0x0) {
      pcStack_1c0 = &DAT_004c61b0;
    }
  }
  else {
    pcStack_1c0 = s__004c61c0;
  }
  sprintf(acStack_50,s__s_s_s_s_s_004c6190,s__s___0_004c619c,puVar4,s_lx__0_004c61a4,puStack_1c4,
          &DAT_004c61ac);
  sprintf(out,acStack_50,iStack_1bc,addr,uStack_1c8 & uStack_1a0);
  uVar7 = 0xffffffff;
  pcVar5 = out;
  do {
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  local_1cc = ~uVar7 - 1;
  _DAT_004dc318 = addr;
  lVar2 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2928,&iStack_1d4,&lStack_1d0);
  if (lVar2 == 0) {
    _DAT_004dc390 = 0;
  }
  else {
    periph_call(*(int *)(cur_dev + 4),iStack_1d4,lStack_1d0,0x4dc390);
  }
  lVar2 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2934,&iStack_1d4,&lStack_1d0);
  iVar6 = (-(uint)(lVar2 != 0) & 4) + 4;
  lVar2 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2948,&iStack_1d4,&lStack_1d0);
  if (lVar2 == 0) {
    iVar6 = 0;
  }
  iVar11 = 0;
  if (iVar6 != 0) {
    puVar4 = &DAT_004dc31c;
    do {
      lVar2 = periph_call(*(int *)(cur_dev + 4),iStack_1d4,iVar11 + lStack_1d0,(long)puVar4);
      if (lVar2 == 0) goto LAB_0043af86;
      iVar11 = iVar11 + 1;
      puVar4 = puVar4 + 4;
    } while (iVar11 < iVar6);
  }
  lVar2 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2990,&iStack_1d4,&lStack_1d0);
  if (lVar2 == 0) {
    iVar6 = 0;
  }
  iVar11 = 0;
  if (iVar6 != 0) {
    puVar4 = &DAT_004dc35c;
    do {
      lVar2 = periph_call(*(int *)(cur_dev + 4),iStack_1d4,iVar11 + lStack_1d0,(long)puVar4);
      if (lVar2 == 0) goto LAB_0043af86;
      iVar11 = iVar11 + 1;
      puVar4 = puVar4 + 4;
    } while (iVar11 < iVar6);
  }
  lVar2 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2970,&iStack_1d4,&lStack_1d0);
  if (lVar2 == 0) {
    iVar6 = 0;
  }
  iVar11 = 0;
  if (iVar6 != 0) {
    puVar4 = &DAT_004dc33c;
    do {
      lVar2 = periph_call(*(int *)(cur_dev + 4),iStack_1d4,iVar11 + lStack_1d0,(long)puVar4);
      if (lVar2 == 0) goto LAB_0043af86;
      iVar11 = iVar11 + 1;
      puVar4 = puVar4 + 4;
    } while (iVar11 < iVar6);
  }
  if ((iVar6 != 4) ||
     (((lVar2 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004a8a6c,&iStack_1d4,&lStack_1d0),
       lVar2 == 0 ||
       (lVar2 = periph_call(*(int *)(cur_dev + 4),iStack_1d4,lStack_1d0,0x4dc32c), lVar2 != 0)) &&
      ((lVar2 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b29a8,&iStack_1d4,&lStack_1d0),
       lVar2 == 0 ||
       (lVar2 = periph_call(*(int *)(cur_dev + 4),iStack_1d4,lStack_1d0,0x4dc330), lVar2 != 0))))))
  {
    iVar6 = (**(code **)(cur_itype + 0x10))
                      (&uStack_1a0,acStack_151 + 1,uStack_1b4,local_1b8,&DAT_004dc308);
    pcVar5 = acStack_151;
    uVar7 = 0xffffffff;
    do {
      pcVar5 = pcVar5 + 1;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
    } while (*pcVar5 != '\0');
    uVar7 = ~uVar7;
    acStack_151[uVar7 + 2] = '\0';
    if (DAT_004dc380 != 0) {
      uVar8 = 0xffffffff;
      pcVar5 = &DAT_004c6174;
      do {
        pcVar13 = pcVar5;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      iVar11 = -1;
      pcVar5 = acStack_151 + 1;
      do {
        pcVar15 = pcVar5;
        if (iVar11 == 0) break;
        iVar11 = iVar11 + -1;
        pcVar15 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar15;
      } while (cVar1 != '\0');
      pcVar5 = pcVar13 + -uVar8;
      pcVar13 = pcVar15 + -1;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar13 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
    iStack_1bc = iVar6;
    if ((DAT_004dc380 & 1) != 0) {
      pcVar5 = dbg_format_addr(0,DAT_004dc384);
      uVar8 = 0xffffffff;
      do {
        pcVar13 = pcVar5;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      iVar11 = -1;
      pcVar5 = acStack_151 + 1;
      do {
        pcVar15 = pcVar5;
        if (iVar11 == 0) break;
        iVar11 = iVar11 + -1;
        pcVar15 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar15;
      } while (cVar1 != '\0');
      pcVar5 = pcVar13 + -uVar8;
      pcVar13 = pcVar15 + -1;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar13 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
    if ((DAT_004dc380 & 2) != 0) {
      pcVar5 = dbg_format_addr(1,DAT_004dc388);
      uVar8 = 0xffffffff;
      do {
        pcVar13 = pcVar5;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      iVar11 = -1;
      pcVar5 = acStack_151 + 1;
      do {
        pcVar15 = pcVar5;
        if (iVar11 == 0) break;
        iVar11 = iVar11 + -1;
        pcVar15 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar15;
      } while (cVar1 != '\0');
      pcVar5 = pcVar13 + -uVar8;
      pcVar13 = pcVar15 + -1;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar13 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
    if ((DAT_004dc380 & 0x40) != 0) {
      pcVar5 = dbg_format_addr(0,DAT_004dc388);
      uVar8 = 0xffffffff;
      do {
        pcVar13 = pcVar5;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      iVar11 = -1;
      pcVar5 = acStack_151 + 1;
      do {
        pcVar15 = pcVar5;
        if (iVar11 == 0) break;
        iVar11 = iVar11 + -1;
        pcVar15 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar15;
      } while (cVar1 != '\0');
      pcVar5 = pcVar13 + -uVar8;
      pcVar13 = pcVar15 + -1;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar13 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
    if ((DAT_004dc380 & 4) != 0) {
      pcVar5 = dbg_format_addr(2,DAT_004dc38c);
      uVar8 = 0xffffffff;
      do {
        pcVar13 = pcVar5;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      iVar11 = -1;
      pcVar5 = acStack_151 + 1;
      do {
        pcVar15 = pcVar5;
        if (iVar11 == 0) break;
        iVar11 = iVar11 + -1;
        pcVar15 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar15;
      } while (cVar1 != '\0');
      pcVar5 = pcVar13 + -uVar8;
      pcVar13 = pcVar15 + -1;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar13 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
    if ((DAT_004dc380 & 8) != 0) {
      pcVar5 = dbg_format_addr(3,DAT_004dc388);
      uVar8 = 0xffffffff;
      do {
        pcVar13 = pcVar5;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      iVar11 = -1;
      pcVar5 = acStack_151 + 1;
      do {
        pcVar15 = pcVar5;
        if (iVar11 == 0) break;
        iVar11 = iVar11 + -1;
        pcVar15 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar15;
      } while (cVar1 != '\0');
      pcVar5 = pcVar13 + -uVar8;
      pcVar13 = pcVar15 + -1;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar13 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
    if ((DAT_004dc380 & 0x10) != 0) {
      pcVar5 = dbg_format_addr(2,DAT_004dc388);
      uVar8 = 0xffffffff;
      do {
        pcVar13 = pcVar5;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      iVar11 = -1;
      pcVar5 = acStack_151 + 1;
      do {
        pcVar15 = pcVar5;
        if (iVar11 == 0) break;
        iVar11 = iVar11 + -1;
        pcVar15 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar15;
      } while (cVar1 != '\0');
      pcVar5 = pcVar13 + -uVar8;
      pcVar13 = pcVar15 + -1;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar13 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
    if ((DAT_004dc380 & 0x20) != 0) {
      pcVar5 = dbg_format_addr(1,DAT_004dc38c);
      uVar8 = 0xffffffff;
      do {
        pcVar13 = pcVar5;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      iVar11 = -1;
      pcVar5 = acStack_151 + 1;
      do {
        pcVar15 = pcVar5;
        if (iVar11 == 0) break;
        iVar11 = iVar11 + -1;
        pcVar15 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar15;
      } while (cVar1 != '\0');
      pcVar5 = pcVar13 + -uVar8;
      pcVar13 = pcVar15 + -1;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar13 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
    if ((DAT_004dc380 & 0x80) != 0) {
      pcVar5 = dbg_format_addr(0,DAT_004dc38c);
      uVar8 = 0xffffffff;
      do {
        pcVar13 = pcVar5;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      iVar11 = -1;
      pcVar5 = acStack_151 + 1;
      do {
        pcVar15 = pcVar5;
        if (iVar11 == 0) break;
        iVar11 = iVar11 + -1;
        pcVar15 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar15;
      } while (cVar1 != '\0');
      pcVar5 = pcVar13 + -uVar8;
      pcVar13 = pcVar15 + -1;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar13 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
    if (acStack_151[uVar7 + 2] == '\0') {
      acStack_151[uVar7] = '\0';
    }
    if (iVar6 == 0) {
      iVar6 = 1;
      iStack_1bc = 1;
    }
    if ((((uStack_1a8 != 0) || ((iVar6 == 2 && (uStack_1b0 != 0)))) ||
        ((iVar6 == 3 && (uStack_1ac != 0)))) || ((iVar6 == 4 && (uStack_1a4 != 0)))) {
      uVar7 = 0xffffffff;
      pcVar5 = s______MEMORY_LOCATION_DOESN_T_EXI_004c6150;
      do {
        pcVar13 = pcVar5;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      uVar7 = ~uVar7;
      iVar11 = -1;
      pcVar5 = acStack_151 + 1;
      do {
        pcVar15 = pcVar5;
        if (iVar11 == 0) break;
        iVar11 = iVar11 + -1;
        pcVar15 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar15;
      } while (cVar1 != '\0');
      pcVar5 = pcVar13 + -uVar7;
      pcVar13 = pcVar15 + -1;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar13 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar13 = pcVar13 + 1;
      }
      acStack_151[screen_cols + 1] = '\0';
    }
    if (*(int *)(*(int *)(cur_dtype + 0x28) + 0x24) == 0) {
      if (iVar6 == 4) {
        sprintf(acStack_178,s__s_s_s_s_s_s_s_004c6128,&DAT_004c614c,puStack_1c4,s_lx__0_004c61a4,
                puStack_1c4,s_lx__0_004c61a4,puStack_1c4,s_lx____s_004c6138);
        sprintf(out + local_1cc,acStack_178,uStack_1c8 & auStack_19c[0],uStack_1c8 & auStack_19c[1],
                uStack_1c8 & auStack_19c[2],acStack_151 + 1);
        return 4;
      }
      if (iVar6 != 3) {
        if (iVar6 != 2) {
          sprintf(acStack_178,&DAT_004c6118,pcStack_1c0,s____s_004c6120);
          sprintf(out + local_1cc,acStack_178,acStack_151 + 1);
          return iVar6;
        }
        sprintf(acStack_178,s__s_s_s_004c6144,&DAT_004c614c,puStack_1c4,s_lx____s_004c6138);
        sprintf(out + local_1cc,acStack_178,uStack_1c8 & auStack_19c[0],acStack_151 + 1);
        return 2;
      }
      sprintf(acStack_178,s__s_s_s_s_s_004c6190,&DAT_004c614c,puStack_1c4,s_lx__0_004c61a4,
              puStack_1c4,s_lx____s_004c6138);
      sprintf(out + local_1cc,acStack_178,uStack_1c8 & auStack_19c[0],uStack_1c8 & auStack_19c[1],
              acStack_151 + 1);
      return 3;
    }
    sprintf(acStack_178,s__s_s_s_004c6144,&DAT_004c614c,puStack_1c4,&DAT_004c61ac);
    if (1 < iVar6) {
      puVar10 = auStack_19c;
      iVar11 = iStack_1bc + -1;
      do {
        sprintf(acStack_28,acStack_178,uStack_1c8 & *puVar10);
        uVar7 = 0xffffffff;
        pcVar5 = acStack_28;
        do {
          pcVar13 = pcVar5;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar13 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar13;
        } while (cVar1 != '\0');
        uVar7 = ~uVar7;
        puVar10 = puVar10 + 1;
        iVar6 = -1;
        pcVar5 = out;
        do {
          pcVar15 = pcVar5;
          if (iVar6 == 0) break;
          iVar6 = iVar6 + -1;
          pcVar15 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar15;
        } while (cVar1 != '\0');
        pcVar5 = pcVar13 + -uVar7;
        pcVar13 = pcVar15 + -1;
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar13 = pcVar13 + 4;
        }
        iVar11 = iVar11 + -1;
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pcVar13 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar13 = pcVar13 + 1;
        }
        iVar6 = iStack_1bc;
      } while (iVar11 != 0);
    }
    uVar7 = 0xffffffff;
    pcVar5 = &DAT_004c6140;
    do {
      pcVar13 = pcVar5;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar13 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar13;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7;
    iVar11 = -1;
    pcVar5 = out;
    do {
      pcVar15 = pcVar5;
      if (iVar11 == 0) break;
      iVar11 = iVar11 + -1;
      pcVar15 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar15;
    } while (cVar1 != '\0');
    pcVar5 = pcVar13 + -uVar7;
    pcVar13 = pcVar15 + -1;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar13 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar13 = pcVar13 + 1;
    }
    uVar7 = 0xffffffff;
    pcVar5 = acStack_151 + 1;
    do {
      pcVar13 = pcVar5;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar13 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar13;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7;
    iVar11 = -1;
    do {
      pcVar5 = out;
      if (iVar11 == 0) break;
      iVar11 = iVar11 + -1;
      pcVar5 = out + 1;
      cVar1 = *out;
      out = pcVar5;
    } while (cVar1 != '\0');
    pcVar13 = pcVar13 + -uVar7;
    pcVar5 = pcVar5 + -1;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar5 = *(undefined4 *)pcVar13;
      pcVar13 = pcVar13 + 4;
      pcVar5 = pcVar5 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar5 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      pcVar5 = pcVar5 + 1;
    }
    return iVar6;
  }
LAB_0043af86:
  sim_error(s_Error_reading_register_004c6178);
  return -1;
}


