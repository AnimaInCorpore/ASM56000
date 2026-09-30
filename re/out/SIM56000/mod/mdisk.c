/* ==== mdisk_save_all @ 00458060 ==== */

void __cdecl mdisk_save_all(int dev,void *fp)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  void *list;
  
  cur_dev = *(int **)(dev_tab + dev * 4);
  iVar4 = 0;
  cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
  list = (void *)cur_dev[3];
  iVar1 = *(int *)(cur_dtype + 0x1c);
  iVar2 = 1;
  if (0 < iVar1) {
    puVar3 = (uint *)(*(int *)(cur_dtype + 0x20) + 0x18);
    do {
      if (iVar2 == 0) {
        return;
      }
      if ((*puVar3 & 0x1000000) != 0) {
        iVar2 = mdisk_save_space(list,fp);
      }
      iVar4 = iVar4 + 1;
      puVar3 = puVar3 + 0xb;
      list = (void *)((int)list + 0x10);
    } while (iVar4 < iVar1);
  }
  return;
}


/* ==== mdisk_close @ 004580d0 ==== */

void __cdecl mdisk_close(int dev)

{
  undefined4 *puVar1;
  undefined4 *p;
  int iVar2;
  int iVar3;
  int iVar4;
  void *list;
  
  cur_dev = *(int **)(dev_tab + dev * 4);
  iVar2 = *(int *)(chiptype_tab + *cur_dev * 4);
  list = (void *)cur_dev[3];
  iVar3 = *(int *)(iVar2 + 0x1c);
  cur_dtype = iVar2;
  if (0 < iVar3) {
    iVar4 = 0;
    do {
      if ((*(uint *)(*(int *)(iVar2 + 0x20) + 0x18 + iVar4) & 0x1000000) != 0) {
        mdisk_clear_list(list);
        iVar2 = cur_dtype;
      }
      iVar4 = iVar4 + 0x2c;
      list = (void *)((int)list + 0x10);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  if ((void *)cur_dev[4] != (void *)0x0) {
    fclose((void *)cur_dev[4]);
    cur_dev[4] = 0;
    p = (undefined4 *)cur_dev[5];
    while (p != (undefined4 *)0x0) {
      puVar1 = (undefined4 *)*p;
      dsp_free(p);
      p = puVar1;
    }
    cur_dev[5] = 0;
  }
  return;
}


/* ==== mdisk_init @ 00458180 ==== */

int mdisk_init(void)

{
  int iVar1;
  int extraout_EAX;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  iVar1 = *(int *)(cur_dtype + 0x1c);
  piVar4 = *(int **)(cur_dev + 0xc);
  iVar5 = 0;
  iVar2 = 1;
  if (0 < iVar1) {
    iVar3 = 0;
    do {
      if (iVar2 == 0) break;
      if ((*(uint *)(*(int *)(cur_dtype + 0x20) + 0x18 + iVar3) & 0x1000000) != 0) {
        dsp_alloc(0x14,1);
        if (extraout_EAX == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = 1;
          piVar4[1] = extraout_EAX;
          *piVar4 = extraout_EAX;
          *(int *)(extraout_EAX + 4) = extraout_EAX;
          *(int *)extraout_EAX = extraout_EAX;
          *(undefined4 *)(extraout_EAX + 0xc) = 2;
        }
      }
      iVar5 = iVar5 + 1;
      iVar3 = iVar3 + 0x2c;
      piVar4 = piVar4 + 4;
    } while (iVar5 < iVar1);
  }
  *(undefined4 *)(cur_dev + 0x10) = 0;
  *(undefined4 *)(cur_dev + 0x14) = 0;
  return iVar2;
}


/* ==== mdisk_load_all @ 00458210 ==== */

void __cdecl mdisk_load_all(int dev,void *fp)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  void *list;
  
  cur_dev = *(int **)(dev_tab + dev * 4);
  iVar5 = 0;
  iVar3 = *(int *)(chiptype_tab + *cur_dev * 4);
  list = (void *)cur_dev[3];
  iVar1 = *(int *)(iVar3 + 0x1c);
  iVar2 = 1;
  cur_dtype = iVar3;
  if (0 < iVar1) {
    iVar4 = 0;
    do {
      if (iVar2 == 0) {
        return;
      }
      if ((*(byte *)(*(int *)(iVar3 + 0x20) + 0x1b + iVar4) & 1) != 0) {
        iVar2 = mdisk_load_space(list,fp);
        iVar3 = cur_dtype;
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0x2c;
      list = (void *)((int)list + 0x10);
    } while (iVar5 < iVar1);
  }
  return;
}


/* ==== mdisk_read @ 00458280 ==== */

int __cdecl mdisk_read(int dev,ulong space,ulong addr,ulong *pval)

{
  char cVar1;
  int iVar2;
  void *node;
  undefined3 extraout_var;
  int *list;
  
  iVar2 = memmap_find(space,addr);
  cur_dev = *(int **)(dev_tab + dev * 4);
  cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
  list = (int *)(iVar2 * 0x10 + cur_dev[3]);
  if ((*(uint *)(*(int *)(cur_dtype + 0x20) + 0x18 + iVar2 * 0x2c) & 0x1000000) == 0) {
    return 0;
  }
  mdisk_find_node(list,addr);
  if (*(int *)((int)node + 0xc) == 2) {
    *pval = *(ulong *)((int)node + 0x10);
    return 1;
  }
  if (*(int *)((int)node + 0xc) == 1) {
    cVar1 = mdisk_page_in(node);
    if (CONCAT31(extraout_var,cVar1) == 0) {
      return 0;
    }
  }
  *pval = *(ulong *)(*(int *)((int)node + 0x10) + (addr & 0xff) * 4);
  if ((void *)*list != node) {
    list[1] = *list;
    *list = (int)node;
  }
  return 1;
}


/* ==== mdisk_find_node @ 00458340 ==== */

void __cdecl mdisk_find_node(void *list,ulong addr)

{
  uint uVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)list;
  uVar1 = puVar2[2];
  while (addr < uVar1) {
    puVar2 = (undefined4 *)puVar2[1];
    uVar1 = puVar2[2];
  }
  for (puVar2 = (undefined4 *)*puVar2;
      ((puVar2 != (undefined4 *)0x0 && (puVar2[2] != 0)) && ((uint)puVar2[2] <= addr));
      puVar2 = (undefined4 *)*puVar2) {
  }
  return;
}


/* ==== mdisk_page_in @ 00458380 ==== */

char __cdecl mdisk_page_in(void *node)

{
  long offset;
  undefined4 uVar1;
  void *buffer;
  int iVar2;
  uint uVar3;
  undefined4 *extraout_EAX;
  
  dsp_alloc(mdisk_block_bytes,0);
  if (buffer != (void *)0x0) {
    offset = *(long *)((int)node + 0x10);
    iVar2 = fseek(*(void **)(cur_dev + 0x10),offset,0);
    if (iVar2 != 0) {
      screen_write(text_rows,0,s_Error_seeking_in_m_gdisk_004d28dc,1);
      fclose(*(void **)(cur_dev + 0x10));
      exit(1);
    }
    uVar3 = fread(buffer,mdisk_block_bytes,1,*(void **)(cur_dev + 0x10));
    if (uVar3 != 1) {
      screen_write(text_rows,0,s_Error_reading_in_m_gdisk__004d28c0,1);
      fclose(*(void **)(cur_dev + 0x10));
      exit(1);
    }
    dsp_alloc(8,0);
    if (extraout_EAX != (undefined4 *)0x0) {
      uVar1 = *(undefined4 *)(cur_dev + 0x14);
      extraout_EAX[1] = offset;
      *extraout_EAX = uVar1;
      *(undefined4 **)(cur_dev + 0x14) = extraout_EAX;
    }
    *(undefined4 *)((int)node + 0xc) = 4;
    *(void **)((int)node + 0x10) = buffer;
  }
  return (char)buffer;
}


/* ==== mdisk_write @ 00458480 ==== */

void __cdecl mdisk_write(int dev,ulong space,ulong addr,ulong val)

{
  ulong uVar1;
  char cVar2;
  int iVar3;
  int *node;
  ulong *extraout_EAX;
  int *extraout_EAX_00;
  int *extraout_EAX_01;
  undefined3 extraout_var;
  int *piVar4;
  undefined4 *list;
  ulong *puVar5;
  uint uVar6;
  
  iVar3 = memmap_find(space,addr);
  cur_dev = *(int *)(dev_tab + dev * 4);
  list = (undefined4 *)(iVar3 * 0x10 + *(int *)(cur_dev + 0xc));
  if ((*(uint *)(*(int *)(cur_dtype + 0x20) + 0x18 + iVar3 * 0x2c) & 0x1000000) == 0) {
    return;
  }
  mdisk_find_node(list,addr);
  piVar4 = node;
  if (node[3] == 2) {
    uVar1 = node[4];
    if (val == uVar1) {
      return;
    }
    dsp_alloc(mdisk_block_bytes,0);
    if (extraout_EAX == (ulong *)0x0) {
      return;
    }
    puVar5 = extraout_EAX;
    for (iVar3 = 0x100; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = uVar1;
      puVar5 = puVar5 + 1;
    }
    uVar6 = addr & 0xffffff00;
    if (uVar6 + 0x100 != *(int *)(*node + 8)) {
      dsp_alloc(0x14,0);
      if (extraout_EAX_00 == (int *)0x0) {
        return;
      }
      extraout_EAX_00[2] = uVar6 + 0x100;
      extraout_EAX_00[3] = 2;
      extraout_EAX_00[4] = uVar1;
      iVar3 = *node;
      extraout_EAX_00[1] = (int)node;
      *extraout_EAX_00 = iVar3;
      *(int **)(*node + 4) = extraout_EAX_00;
      *node = (int)extraout_EAX_00;
    }
    if (uVar6 != node[2]) {
      dsp_alloc(0x14,0);
      if (extraout_EAX_01 == (int *)0x0) {
        return;
      }
      iVar3 = *node;
      extraout_EAX_01[1] = (int)node;
      *extraout_EAX_01 = iVar3;
      extraout_EAX_01[2] = uVar6;
      *(int **)(*node + 4) = extraout_EAX_01;
      *node = (int)extraout_EAX_01;
      piVar4 = extraout_EAX_01;
    }
    piVar4[3] = 4;
    piVar4[4] = (int)extraout_EAX;
  }
  else if ((node[3] == 1) && (cVar2 = mdisk_page_in(node), CONCAT31(extraout_var,cVar2) == 0)) {
    return;
  }
  *(ulong *)(piVar4[4] + (addr & 0xff) * 4) = val;
  if ((int *)*list != piVar4) {
    list[1] = (int *)*list;
    *list = piVar4;
  }
  return;
}


/* ==== mdisk_clear_list @ 004585f0 ==== */

void __cdecl mdisk_clear_list(void *list)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *p;
  
  puVar1 = *(undefined4 **)list;
  p = (undefined4 *)*puVar1;
  while (p != puVar1) {
    puVar2 = (undefined4 *)*p;
    if (p[3] == 4) {
      dsp_free((void *)p[4]);
    }
    dsp_free(p);
    p = puVar2;
  }
  if (p[3] == 4) {
    dsp_free((void *)p[4]);
  }
  *p = p;
  p[2] = 0;
  p[4] = 0;
  p[3] = 2;
  *(undefined4 **)((int)list + 4) = p;
  return;
}


/* ==== mdisk_save_space @ 00458660 ==== */

int __cdecl mdisk_save_space(void *list,void *fp)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  char cVar3;
  undefined3 extraout_var;
  uint uVar4;
  undefined4 *node;
  int iVar5;
  undefined4 *puVar6;
  
  puVar6 = *(undefined4 **)list;
  iVar5 = 1;
  puVar1 = puVar6;
  node = puVar6;
  for (puVar2 = (undefined4 *)*puVar6; puVar2 != puVar6; puVar2 = (undefined4 *)*puVar2) {
    if (puVar1[2] == 0) {
      node = puVar1;
    }
    iVar5 = iVar5 + 1;
    puVar1 = puVar2;
  }
  fprintf(fp,&DAT_004c5694,iVar5);
  for (; iVar5 != 0; iVar5 = iVar5 + -1) {
    fprintf(fp,&DAT_004c5934,node[2]);
    if (node[3] == 1) {
      cVar3 = mdisk_page_in(node);
      puVar6 = (undefined4 *)CONCAT31(extraout_var,cVar3);
    }
    else if (node[3] == 4) {
      puVar6 = (undefined4 *)node[4];
    }
    else {
      puVar6 = (undefined4 *)0x0;
    }
    fprintf(fp,&DAT_004c5764,node[3]);
    if (puVar6 == (undefined4 *)0x0) {
      fprintf(fp,&DAT_004c586c,node[4]);
    }
    else {
      uVar4 = 0;
      do {
        if ((uVar4 != 0) && ((uVar4 & 7) == 0)) {
          fprintf(fp,&DAT_004c5890);
        }
        fprintf(fp,&DAT_004c586c,*puVar6);
        uVar4 = uVar4 + 1;
        puVar6 = puVar6 + 1;
      } while ((int)uVar4 < 0x100);
    }
    node = (undefined4 *)*node;
  }
  iVar5 = fprintf(fp,&DAT_004c5890);
  return (uint)(iVar5 != -1);
}


/* ==== mdisk_load_space @ 00458770 ==== */

int __cdecl mdisk_load_space(void *list,void *fp)

{
  void *pvVar1;
  void *stream;
  int extraout_EAX;
  int *extraout_EAX_00;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  pvVar1 = list;
  mdisk_clear_list(list);
  stream = fp;
  fp = (void *)fscanf(fp,&DAT_004d28fc,&list);
  piVar4 = *(int **)pvVar1;
  if ((int)list < 1) {
    return (int)fp;
  }
  do {
    fscanf(stream,&DAT_004c586c,piVar4 + 2);
    fscanf(stream,&DAT_004d28f8,piVar4 + 3);
    if (piVar4[3] == 4) {
      dsp_alloc(mdisk_block_bytes,0);
      piVar4[4] = extraout_EAX;
      if (extraout_EAX == 0) {
        return 0;
      }
      iVar2 = 0x100;
      iVar3 = extraout_EAX;
      do {
        fscanf(stream,&DAT_004c586c,iVar3);
        iVar3 = iVar3 + 4;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    else {
      fscanf(stream,&DAT_004c586c,piVar4 + 4);
    }
    if (1 < (int)list) {
      dsp_alloc(0x14,0);
      if (extraout_EAX_00 == (int *)0x0) {
        return 0;
      }
      iVar3 = *piVar4;
      extraout_EAX_00[1] = (int)piVar4;
      *extraout_EAX_00 = iVar3;
      *(int **)(*piVar4 + 4) = extraout_EAX_00;
      *piVar4 = (int)extraout_EAX_00;
      piVar4 = extraout_EAX_00;
    }
    list = (void *)((int)list + -1);
  } while (0 < (int)list);
  return (int)fp;
}


/* ==== mdisk_spill @ 00458870 ==== */

int mdisk_spill(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int local_c;
  int local_8;
  
  piVar2 = cur_dev;
  iVar3 = 0;
  local_8 = 0;
  local_c = 0;
  if (0 < max_devices) {
    do {
      if (iVar3 != 0) break;
      cur_dev = *(int **)(dev_tab + local_8 * 4);
      if (cur_dev != (int *)0x0) {
        cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
        iVar5 = 0;
        iVar1 = *(int *)(cur_dtype + 0x1c);
        if (0 < iVar1) {
          iVar4 = 0;
          iVar6 = 0;
          do {
            if (iVar3 != 0) break;
            if (((*(uint *)(*(int *)(cur_dtype + 0x20) + 0x18 + iVar6) & 0x1000000) != 0) &&
               (iVar3 = mdisk_spill_lru((void *)(cur_dev[3] + iVar4)), iVar3 != 0)) {
              local_c = 1;
            }
            iVar5 = iVar5 + 1;
            iVar6 = iVar6 + 0x2c;
            iVar4 = iVar4 + 0x10;
            iVar3 = local_c;
          } while (iVar5 < iVar1);
        }
      }
      local_8 = local_8 + 1;
    } while (local_8 < max_devices);
  }
  local_8 = 0;
  if (0 < max_devices) {
    do {
      if (iVar3 != 0) break;
      cur_dev = *(int **)(dev_tab + local_8 * 4);
      if (cur_dev != (int *)0x0) {
        cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
        iVar5 = 0;
        iVar1 = *(int *)(cur_dtype + 0x1c);
        if (0 < iVar1) {
          iVar4 = 0;
          iVar6 = 0;
          do {
            if (iVar3 != 0) break;
            if (((*(uint *)(*(int *)(cur_dtype + 0x20) + 0x18 + iVar6) & 0x1000000) != 0) &&
               (iVar3 = mdisk_spill_mru((void *)(cur_dev[3] + iVar4)), iVar3 != 0)) {
              local_c = 1;
            }
            iVar5 = iVar5 + 1;
            iVar6 = iVar6 + 0x2c;
            iVar4 = iVar4 + 0x10;
            iVar3 = local_c;
          } while (iVar5 < iVar1);
        }
      }
      local_8 = local_8 + 1;
    } while (local_8 < max_devices);
  }
  cur_dev = piVar2;
  cur_dtype = *(undefined4 *)(chiptype_tab + *piVar2 * 4);
  return iVar3;
}


/* ==== mdisk_spill_lru @ 00458a10 ==== */

int __cdecl mdisk_spill_lru(void *list)

{
  int iVar1;
  int va0;
  
  iVar1 = *(int *)list;
  va0 = *(int *)(iVar1 + 4);
  if (va0 == iVar1) {
    return 0;
  }
  while ((*(int *)(va0 + 0xc) != 4 || (va0 == *(int *)((int)list + 4)))) {
    va0 = *(int *)(va0 + 4);
    if (va0 == iVar1) {
      return 0;
    }
  }
  mdisk_spill_node(va0);
  return 1;
}


/* ==== mdisk_spill_mru @ 00458a50 ==== */

int __cdecl mdisk_spill_mru(void *list)

{
  int va0;
  
  va0 = *(int *)((int)list + 4);
  if ((*(int *)(va0 + 0xc) != 4) && (va0 = *(int *)list, *(int *)(va0 + 0xc) != 4)) {
    return 0;
  }
  mdisk_spill_node(va0);
  return 1;
}


/* ==== mdisk_spill_node @ 00458a80 ==== */

void mdisk_spill_node(void *node)

{
  undefined4 *p;
  undefined4 extraout_EAX;
  int iVar1;
  long offset;
  uint uVar2;
  int in_stack_00000014;
  char local_54 [84];
  
  p = *(undefined4 **)(cur_dev + 0x14);
  if (p == (undefined4 *)0x0) {
    offset = 0;
  }
  else {
    offset = p[1];
  }
  if (*(int *)(cur_dev + 0x10) == 0) {
    sprintf(&stack0xffffff58,&DAT_004d2968,*(undefined4 *)(cur_dtype + 0x24),
            *(undefined4 *)(cur_dev + 4));
    path_combine((char *)(cur_dev + 0x58),&stack0xffffff58,&DAT_004d2960,local_54);
    fopen(local_54,&DAT_004d295c);
    *(undefined4 *)(cur_dev + 0x10) = extraout_EAX;
    if (*(int *)(cur_dev + 0x10) == 0) {
      screen_write(text_rows,0,s_Error_opening_in_m_pdisk_004d2940,1);
      exit(1);
    }
  }
  iVar1 = fseek(*(void **)(cur_dev + 0x10),offset,(-(uint)(p != (undefined4 *)0x0) & 0xfffffffe) + 2
               );
  if (iVar1 != 0) {
    screen_write(text_rows,0,s_Error_seeking_in_m_pdisk_004d2924,1);
    exit(1);
  }
  if (p == (undefined4 *)0x0) {
    offset = ftell(*(void **)(cur_dev + 0x10));
  }
  uVar2 = fwrite(*(void **)(in_stack_00000014 + 0x10),mdisk_block_bytes,1,*(void **)(cur_dev + 0x10)
                );
  if (uVar2 != 1) {
    screen_write(text_rows,0,s_Error_writing_block_in_m_pdisk__004d2904,1);
    exit(1);
  }
  *(undefined4 *)(in_stack_00000014 + 0xc) = 1;
  dsp_free(*(void **)(in_stack_00000014 + 0x10));
  *(long *)(in_stack_00000014 + 0x10) = offset;
  if (p != (undefined4 *)0x0) {
    *(undefined4 *)(cur_dev + 0x14) = *p;
    dsp_free(p);
  }
  return;
}


