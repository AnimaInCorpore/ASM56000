/* ==== prof_list_count @ 0046b090 ==== */

int __cdecl prof_list_count(void *tree)

{
  if (tree != (void *)0x0) {
    return *(int *)((int)tree + 4);
  }
  return -1;
}


/* ==== prof_error @ 0046b0a0 ==== */

void __cdecl prof_error(int level,char *fmt,...)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  char local_40 [64];
  
  pcVar2 = s_Warning__004d3ef8;
  if (level < 1) {
    pcVar2 = s_Error__004d3ef0;
  }
  sprintf(local_40,pcVar2);
  uVar3 = 0xffffffff;
  pcVar2 = local_40;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  vsprintf(local_40 + (~uVar3 - 1),fmt,&stack0x0000000c);
  if (level == 3) {
    prof_printf(&DAT_004d2270,local_40);
    return;
  }
  out_text(local_40,1);
  if (level == 0) {
    out_text(PTR_s_____MAJOR_PROFILING_ERROR___SIMU_004d3b8c,1);
    exit(-1);
  }
  if (level == 1) {
                    /* WARNING: Subroutine does not return */
    longjmp(&prof_jmpbuf,1);
  }
  return;
}


/* ==== prof_malloc @ 0046b150 ==== */

void __cdecl prof_malloc(ulong n)

{
  int extraout_EAX;
  
  dsp_alloc(n,1);
  if (extraout_EAX == 0) {
    *(uint *)(prof_ctx + 0x34e0) = *(uint *)(prof_ctx + 0x34e0) | 0x10;
                    /* WARNING: Subroutine does not return */
    longjmp(&prof_jmpbuf,1);
  }
  return;
}


/* ==== prof_swap32 @ 0046b190 ==== */

void __cdecl prof_swap32(void *buf,ulong nbytes)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 *puVar3;
  uint uVar4;
  
  uVar4 = nbytes >> 2;
  if (uVar4 != 0) {
    puVar3 = (undefined1 *)((int)buf + 2);
    do {
      uVar1 = puVar3[-2];
      puVar3[-2] = puVar3[1];
      uVar2 = *puVar3;
      *puVar3 = puVar3[-1];
      puVar3[-1] = uVar2;
      puVar3[1] = uVar1;
      puVar3 = puVar3 + 4;
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
  return;
}


/* ==== prof_fopen @ 0046b1d0 ==== */

void __cdecl prof_fopen(char *name,char *mode,char *ext,int errlevel)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  int iVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  void *stream;
  int iVar6;
  uint uVar7;
  uint uVar8;
  char cVar9;
  byte *pbVar10;
  char *pcVar11;
  char *pcVar12;
  bool bVar13;
  undefined1 local_124 [28];
  undefined4 local_108;
  char local_100 [256];
  char *pcVar5;
  
  pbVar10 = &DAT_004c5ff4;
  pbVar3 = (byte *)mode;
  do {
    bVar1 = *pbVar3;
    bVar13 = bVar1 < *pbVar10;
    if (bVar1 != *pbVar10) {
LAB_0046b210:
      iVar4 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
      goto LAB_0046b215;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar3[1];
    bVar13 = bVar1 < pbVar10[1];
    if (bVar1 != pbVar10[1]) goto LAB_0046b210;
    pbVar3 = pbVar3 + 2;
    pbVar10 = pbVar10 + 2;
  } while (bVar1 != 0);
  iVar4 = 0;
LAB_0046b215:
  if (iVar4 != 0) {
    pbVar10 = &DAT_004c5574;
    pbVar3 = (byte *)mode;
    do {
      bVar1 = *pbVar3;
      bVar13 = bVar1 < *pbVar10;
      if (bVar1 != *pbVar10) {
LAB_0046b24c:
        iVar4 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
        goto LAB_0046b251;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar13 = bVar1 < pbVar10[1];
      if (bVar1 != pbVar10[1]) goto LAB_0046b24c;
      pbVar3 = pbVar3 + 2;
      pbVar10 = pbVar10 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_0046b251:
    if (iVar4 != 0) {
      pbVar10 = &DAT_004c9570;
      pbVar3 = (byte *)mode;
      do {
        bVar1 = *pbVar3;
        bVar13 = bVar1 < *pbVar10;
        if (bVar1 != *pbVar10) {
LAB_0046b28e:
          cVar9 = (-(1 - bVar13 != (uint)(bVar13 != 0)) & 0x16U) + 0x61;
          goto LAB_0046b2a1;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar13 = bVar1 < pbVar10[1];
        if (bVar1 != pbVar10[1]) goto LAB_0046b28e;
        pbVar3 = pbVar3 + 2;
        pbVar10 = pbVar10 + 2;
      } while (bVar1 != 0);
      cVar9 = 'a';
      goto LAB_0046b2a1;
    }
  }
  cVar9 = 'r';
LAB_0046b2a1:
  strncpy((char *)&prof_filename,name,0x100);
  if (ext != (char *)0x0) {
    cVar2 = strrchr((char *)&prof_filename,0x2e);
    pcVar5 = (char *)CONCAT31(extraout_var,cVar2);
    if (pcVar5 != (char *)0x0) {
      cVar2 = strchr(pcVar5,0x5c);
      if (CONCAT31(extraout_var_00,cVar2) == 0) {
        *pcVar5 = cVar2;
      }
    }
    uVar7 = 0xffffffff;
    do {
      pcVar5 = ext;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar5 = ext + 1;
      cVar2 = *ext;
      ext = pcVar5;
    } while (cVar2 != '\0');
    uVar7 = ~uVar7;
    iVar4 = -1;
    pcVar12 = (char *)&prof_filename;
    do {
      pcVar11 = pcVar12;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pcVar11 = pcVar12 + 1;
      cVar2 = *pcVar12;
      pcVar12 = pcVar11;
    } while (cVar2 != '\0');
    pcVar5 = pcVar5 + -uVar7;
    pcVar12 = pcVar11 + -1;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar12 = pcVar12 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar12 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar12 = pcVar12 + 1;
    }
  }
  if ((cVar9 == 'r') || (cVar9 == 'a')) {
    iVar4 = path_search((char *)&prof_filename,&empty_str,local_100);
    if (iVar4 != 0) {
      strncpy((char *)&prof_filename,local_100,0x100);
    }
  }
  fopen((char *)&prof_filename,mode);
  if (stream == (void *)0x0) {
    prof_error(errlevel,PTR_s_Failed_to_open_file__s_004d3bb4,&prof_filename);
    return;
  }
  if (cVar9 == 'a') {
    iVar4 = fseek(stream,0,2);
    if (iVar4 != 0) {
      prof_error(1,PTR_s_Failed_to_open_file__s_004d3bb4,&prof_filename);
      return;
    }
  }
  else if (cVar9 == 'r') {
    iVar4 = _open((char *)&prof_filename,0);
    if (iVar4 != -1) {
      iVar6 = _fstat(iVar4,local_124);
      if (iVar6 != -1) {
        prof_file_size = local_108;
        _close(iVar4);
        return;
      }
    }
    _close(iVar4);
    return;
  }
  return;
}


/* ==== prof_match_word @ 0046b440 ==== */

int __cdecl prof_match_word(char **pp,char *word)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  
  uVar4 = 0xffffffff;
  pcVar5 = word;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  while( true ) {
    if (__mb_cur_max < 2) {
      uVar2 = (byte)_pctype[**pp * 2] & 8;
    }
    else {
      uVar2 = _isctype((int)**pp,8);
    }
    if (uVar2 == 0) break;
    *pp = *pp + 1;
  }
  iVar3 = prof_strnicmp(*pp,word,~uVar4 - 1);
  if (iVar3 == 0) {
    *pp = *pp + (~uVar4 - 1);
    return 1;
  }
  return 0;
}


/* ==== prof_fwrite @ 0046b4c0 ==== */

void __cdecl prof_fwrite(void *buf,ulong size,ulong count,void *fp,int swap)

{
  if (swap == 1) {
    prof_swap32(buf,count * size);
  }
  fwrite(buf,size,count,fp);
  if (swap == 1) {
    prof_swap32(buf,count * size);
  }
  return;
}


/* ==== prof_fread @ 0046b510 ==== */

void __cdecl prof_fread(void *buf,ulong size,ulong count,void *fp,int swap)

{
  void *extraout_EAX;
  uint uVar1;
  
  if (buf == (void *)0x0) {
    prof_malloc(count * size);
    buf = extraout_EAX;
  }
  uVar1 = fread(buf,size,count,fp);
  if (uVar1 != count) {
    prof_error(1,PTR_s_Failed_to_read_from_file__s_004d3bcc,&prof_filename);
  }
  if (swap == 1) {
    prof_swap32(buf,count * size);
  }
  return;
}


/* ==== prof_func_fullname @ 0046b580 ==== */

void __cdecl prof_func_fullname(char *out,void *func,ulong max)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  
  *out = '\0';
  if (*(int *)((int)func + 8) == 0xd5) {
    if (-1 < *(int *)((int)func + 4)) {
      strncat(out,*(char **)(*(int *)(prof_ctx + 0x350c) + *(int *)((int)func + 4) * 4),max);
    }
    uVar2 = 0xffffffff;
    pcVar5 = &DAT_004d32d4;
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
    pcVar5 = out;
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
  }
  uVar2 = 0xffffffff;
  pcVar5 = out;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  strncat(out,*(char **)func,(max - (~uVar2 - 1)) + 1);
  return;
}


/* ==== prof_strnicmp @ 0046b610 ==== */

int __cdecl prof_strnicmp(char *a,char *b,int n)

{
  uint uVar1;
  int c;
  int c_00;
  
  if (n != 0) {
    while( true ) {
      c = (int)*a;
      c_00 = (int)*b;
      a = a + 1;
      b = b + 1;
      if (__mb_cur_max < 2) {
        uVar1 = (byte)_pctype[c * 2] & 1;
      }
      else {
        uVar1 = _isctype(c,1);
      }
      if (uVar1 != 0) {
        c = tolower(c);
      }
      if (__mb_cur_max < 2) {
        uVar1 = (byte)_pctype[c_00 * 2] & 1;
      }
      else {
        uVar1 = _isctype(c_00,1);
      }
      if (uVar1 != 0) {
        c_00 = tolower(c_00);
      }
      if (c != c_00) {
        return c - c_00;
      }
      if (c == 0) break;
      n = n + -1;
      if (n == 0) {
        return 0;
      }
    }
  }
  return 0;
}


/* ==== avl_cmp_h46b6c0 @ 0046b6c0 ==== */

char avl_cmp_h46b6c0(int *param_1,int *param_2)

{
  if (*param_2 < *param_1) {
    return '\0';
  }
  if (*param_1 < *param_2) {
    return '\x02';
  }
  if ((uint)param_2[1] < (uint)param_1[1]) {
    return '\0';
  }
  return ((uint)param_1[1] < (uint)param_2[1]) + '\x01';
}


/* ==== prof_add_line @ 0046b700 ==== */

void __cdecl prof_add_line(ulong file_idx,ulong line)

{
  ulong *extraout_EAX;
  ulong *item;
  
  if (*(int *)(prof_ctx + 0x3500) == 1) {
    prof_malloc(0x18);
    item = extraout_EAX;
  }
  else {
    item = (ulong *)pool_alloc(prof_ctx + 0x34e8,0x18);
  }
  *item = file_idx;
  item[1] = line;
  if (*(int *)(prof_ctx + 0x37a0) != 1) {
    item[3] = item[3] | 4;
  }
  avl_insert(*(void **)(prof_ctx + 4),item,1);
  return;
}


/* ==== prof_del_line @ 0046b770 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl prof_del_line(ulong file_idx,ulong line)

{
  _prof_line_key = file_idx;
  _DAT_00503f2c = line;
  avl_find(*(void **)(prof_ctx + 4),&prof_line_key,1);
  return;
}


/* ==== prof_cmp_ulong @ 0046b7a0 ==== */

int __cdecl prof_cmp_ulong(ulong *a,ulong *b)

{
  if (*b != *a) {
    return (-(uint)(*b < *a) & 0xfffffffe) + 2;
  }
  return 1;
}


/* ==== avl_cmp_h46b7c0 @ 0046b7c0 ==== */

int avl_cmp_h46b7c0(ulong *param_1,ulong *param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  bool bVar5;
  
  pbVar2 = (byte *)param_1[0x29];
  if ((pbVar2 == (byte *)0x0) || (pbVar4 = (byte *)param_2[0x29], pbVar4 == (byte *)0x0)) {
    if (pbVar2 != (byte *)0x0) {
      return 0;
    }
    return (param_2[0x29] != 0) + 1;
  }
  do {
    bVar1 = *pbVar2;
    bVar5 = bVar1 < *pbVar4;
    if (bVar1 != *pbVar4) {
LAB_0046b808:
      iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
      goto LAB_0046b80d;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar2[1];
    bVar5 = bVar1 < pbVar4[1];
    if (bVar1 != pbVar4[1]) goto LAB_0046b808;
    pbVar2 = pbVar2 + 2;
    pbVar4 = pbVar4 + 2;
  } while (bVar1 != 0);
  iVar3 = 0;
LAB_0046b80d:
  if (iVar3 != 0) {
    return ((iVar3 < 1) - 1 & 0xfffffffe) + 2;
  }
  if (param_2[0x2a] != param_1[0x2a]) {
    return (-(uint)(param_2[0x2a] < param_1[0x2a]) & 0xfffffffe) + 2;
  }
  iVar3 = prof_cmp_ulong(param_1,param_2);
  return iVar3;
}


/* ==== avl_cmp_h46b870 @ 0046b870 ==== */

int avl_cmp_h46b870(ulong *param_1,ulong *param_2)

{
  int iVar1;
  
  if (param_2[0x2f] < param_1[0x2f]) {
    return 0;
  }
  if (param_1[0x2f] < param_2[0x2f]) {
    return 2;
  }
  iVar1 = prof_cmp_ulong(param_1,param_2);
  return iVar1;
}


/* ==== prof_add_instr @ 0046b8b0 ==== */

void __cdecl prof_add_instr(ulong addr,int kind,ulong space_addr,void *srcloc)

{
  int *piVar1;
  ulong *extraout_EAX;
  ulong *src_line;
  int iVar2;
  ulong uVar3;
  int iVar4;
  char cVar5;
  ulong *puVar6;
  undefined4 *puVar7;
  ulong *puVar8;
  char *text;
  
  if (kind == 3) {
    cVar5 = '\0';
  }
  else {
    cVar5 = (kind != 1) + '\x01';
  }
  puVar7 = &prof_instr_scratch;
  for (iVar4 = 0xa1; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  (**(code **)(*(int *)(cur_itype + 0x18) + 0x3c))
            (*(undefined4 *)(cur_dev + 4),cVar5,space_addr,space_addr,&prof_instr_scratch);
  if (DAT_00503cb0 < 0) {
    return;
  }
  if (*(int *)(prof_ctx + 0x3500) == 1) {
    prof_malloc(0xdc);
    src_line = extraout_EAX;
  }
  else {
    src_line = (ulong *)pool_alloc(prof_ctx + 0x34e8,0xdc);
  }
  puVar6 = &prof_instr_scratch;
  puVar8 = src_line;
  for (iVar4 = 0x37; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar8 = puVar8 + 1;
  }
  *src_line = addr;
  if (srcloc == (void *)0x0) {
    src_line[0x29] = (ulong)s__new__004d3f04;
    src_line[0x2a] = 0xfffffffe;
    src_line[3] = src_line[3] | 0x1000;
    text = (char *)0x0;
  }
  else {
    src_line[0x28] = *(ulong *)((int)srcloc + 8);
    src_line[0x29] = *(ulong *)srcloc;
    src_line[0x2a] = *(ulong *)((int)srcloc + 4);
    text = *(char **)((int)srcloc + 0xc);
  }
  prof_parse_call_directive(src_line,text);
  iVar4 = (**(code **)(*(int *)(cur_itype + 0x18) + 0x10))(src_line);
  iVar2 = prof_is_branch_class(src_line);
  if (iVar2 != 0) {
    *(undefined4 *)(prof_ctx + 200 + iVar4 * 4) = 1;
  }
  if (src_line[0x21] == 0) {
    piVar1 = (int *)(prof_ctx + 0x1ce8 + iVar4 * 4);
    *piVar1 = *piVar1 + 1;
  }
  else if (*(int *)(src_line[0x21] + 4) == 0) {
    piVar1 = (int *)(prof_ctx + 0x2008 + iVar4 * 4);
    *piVar1 = *piVar1 + 1;
  }
  else {
    piVar1 = (int *)(prof_ctx + 9000 + iVar4 * 4);
    *piVar1 = *piVar1 + 1;
  }
  *(int *)(prof_ctx + 1000 + iVar4 * 4) = *(int *)(prof_ctx + 1000 + iVar4 * 4) + 1;
  *(int *)(prof_ctx + 0xb0) = *(int *)(prof_ctx + 0xb0) + 1;
  *(uint *)(prof_ctx + 0xa8) = *(int *)(prof_ctx + 0xa8) + ((src_line[3] & 4) != 0) + 1;
  avl_insert(*(void **)(prof_ctx + 8),src_line,1);
  uVar3 = prof_list_count(*(void **)(prof_ctx + 8));
  src_line[0x2f] = uVar3;
  return;
}


/* ==== prof_is_branch_class @ 0046ba80 ==== */

int __cdecl prof_is_branch_class(void *instr)

{
  uint uVar1;
  
  if (((((*(uint *)((int)instr + 4) & 0xf00000) == 0) &&
       (uVar1 = *(uint *)((int)instr + 4) & 0xfc000, uVar1 != 0x80000)) && (uVar1 != 0x90000)) &&
     ((uVar1 != 0x88000 && (uVar1 != 0x98000)))) {
    return 0;
  }
  return 1;
}


/* ==== prof_find_instr @ 0046bac0 ==== */

char __cdecl prof_find_instr(ulong addr,void *ref,int mode)

{
  bool bVar1;
  char cVar2;
  char cVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int iVar5;
  ulong local_dc [55];
  int iVar4;
  
  local_dc[0] = addr;
  iVar5 = 0;
  cVar2 = avl_iter(*(void **)(prof_ctx + 8),(char *)local_dc,local_dc);
  cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar2),(void *)0x0);
  iVar4 = CONCAT31(extraout_var_00,cVar3);
  while (iVar4 != 0) {
    if ((*(int *)(iVar4 + 0xac) == 0) && ((*(uint *)(iVar4 + 0xc) & 0x1000) == 0)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (((mode == 2) && (bVar1)) ||
       ((((mode == 0 && ((0 < *(int *)(iVar4 + 0xb4) || (bVar1)))) &&
         ((iVar5 == 0 || (*(int *)(iVar5 + 0xb4) < *(int *)(iVar4 + 0xb4))))) ||
        ((((mode == 1 && (*(int *)(iVar4 + 4) == *(int *)((int)ref + 4))) &&
          (((*(byte *)(iVar4 + 0xc) & 4) == 0 || (*(int *)(iVar4 + 8) == *(int *)((int)ref + 8)))))
         && ((iVar5 == 0 || (*(int *)(iVar5 + 0xb4) < *(int *)(iVar4 + 0xb4))))))))) {
      iVar5 = iVar4;
    }
    cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar2),(void *)0x0);
    iVar4 = CONCAT31(extraout_var_01,cVar3);
  }
  return (char)iVar5;
}


/* ==== prof_cmp_srcloc @ 0046bbb0 ==== */

int __cdecl prof_cmp_srcloc(void *a,void *b)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  bool bVar7;
  
  pbVar3 = *(byte **)a;
  pbVar6 = *(byte **)b;
  do {
    bVar1 = *pbVar3;
    bVar7 = bVar1 < *pbVar6;
    if (bVar1 != *pbVar6) {
LAB_0046bbe9:
      iVar4 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
      goto LAB_0046bbee;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar3[1];
    bVar7 = bVar1 < pbVar6[1];
    if (bVar1 != pbVar6[1]) goto LAB_0046bbe9;
    pbVar3 = pbVar3 + 2;
    pbVar6 = pbVar6 + 2;
  } while (bVar1 != 0);
  iVar4 = 0;
LAB_0046bbee:
  if (iVar4 != 0) {
    return ((iVar4 < 1) - 1 & 0xfffffffe) + 2;
  }
  iVar4 = *(int *)((int)a + 0xc);
  iVar5 = *(int *)((int)b + 0xc);
  if (iVar4 == iVar5) {
    iVar2 = *(int *)((int)b + 4);
    if (0 < iVar2) {
      iVar4 = *(int *)((int)a + 8);
      iVar5 = *(int *)((int)b + 8);
      if (iVar4 != iVar5) goto LAB_0046bc22;
      if (*(int *)((int)a + 4) != iVar2) {
        return ((iVar2 <= *(int *)((int)a + 4)) - 1 & 0xfffffffe) + 2;
      }
    }
    return 1;
  }
LAB_0046bc22:
  return ((iVar5 <= iVar4) - 1 & 0xfffffffe) + 2;
}


/* ==== avl_cmp_h46bc60 @ 0046bc60 ==== */

int avl_cmp_h46bc60(void *param_1,void *param_2)

{
  int iVar1;
  
  if ((*(int *)((int)param_1 + 0xc) != 3) || (*(int *)((int)param_2 + 0xc) != 3)) {
    if (*(int *)((int)param_1 + 0xc) == 3) {
      return 0;
    }
    if (*(int *)((int)param_2 + 0xc) == 3) {
      return 2;
    }
    iVar1 = prof_cmp_srcloc(param_1,param_2);
    return iVar1;
  }
  if (*(int *)((int)param_1 + 0x10) != *(int *)((int)param_2 + 0x10)) {
    return ((*(int *)((int)param_1 + 0x10) <= *(int *)((int)param_2 + 0x10)) - 1 & 0xfffffffe) + 2;
  }
  if (*(uint *)((int)param_2 + 0x14) != *(uint *)((int)param_1 + 0x14)) {
    return (-(uint)(*(uint *)((int)param_2 + 0x14) < *(uint *)((int)param_1 + 0x14)) & 0xfffffffe) +
           2;
  }
  return 1;
}


/* ==== prof_add_file @ 0046bcd0 ==== */

void __cdecl prof_add_file(char *name,ulong kind)

{
  char cVar1;
  undefined4 *extraout_EAX;
  undefined4 *item;
  undefined3 extraout_var;
  
  if (*(int *)(prof_ctx + 0x3500) == 1) {
    prof_malloc(0x20);
    item = extraout_EAX;
  }
  else {
    item = (undefined4 *)pool_alloc(prof_ctx + 0x34e8,0x20);
  }
  item[3] = kind;
  cVar1 = pool_strdup(prof_ctx + 0x34e8,name);
  *item = CONCAT31(extraout_var,cVar1);
  avl_insert(*(void **)(prof_ctx + 0xc),item,1);
  return;
}


/* ==== prof_del_file @ 0046bd40 ==== */

void __cdecl prof_del_file(void *a,void *b)

{
  void *local_20;
  undefined4 local_1c;
  void *local_14;
  
  local_20 = a;
  local_14 = b;
  local_1c = 0xffffffff;
  avl_find(*(void **)(prof_ctx + 0xc),&local_20,1);
  return;
}


/* ==== avl_cmp_h46bd80 @ 0046bd80 ==== */

char avl_cmp_h46bd80(int *param_1,int *param_2)

{
  if (*param_2 < *param_1) {
    return '\0';
  }
  return (*param_1 < *param_2) + '\x01';
}


/* ==== avl_cmp_h46bda0 @ 0046bda0 ==== */

char avl_cmp_h46bda0(int param_1,int param_2)

{
  if (*(uint *)(param_1 + 0x1c) < *(uint *)(param_2 + 0x1c)) {
    return '\0';
  }
  return (*(uint *)(param_2 + 0x1c) < *(uint *)(param_1 + 0x1c)) + '\x01';
}


/* ==== avl_cmp_h46bdc0 @ 0046bdc0 ==== */

char avl_cmp_h46bdc0(int param_1,int param_2)

{
  if (*(uint *)(param_1 + 0x24) < *(uint *)(param_2 + 0x24)) {
    return '\0';
  }
  return (*(uint *)(param_2 + 0x24) < *(uint *)(param_1 + 0x24)) + '\x01';
}


/* ==== prof_cmp_name_nocase @ 0046bde0 ==== */

int __cdecl prof_cmp_name_nocase(void *a,void *b)

{
  int iVar1;
  
  iVar1 = prof_strnicmp(*(char **)((int)a + 4),*(char **)((int)b + 4),-1);
  if (0 < iVar1) {
    return 0;
  }
  return (iVar1 < 0) + 1;
}


/* ==== prof_add_func @ 0046be10 ==== */

void __cdecl prof_add_func(void *instr,char *name,int kind)

{
  undefined4 *extraout_EAX;
  undefined4 *item;
  undefined4 extraout_EAX_00;
  undefined4 extraout_EAX_01;
  undefined4 extraout_EAX_02;
  undefined4 extraout_EAX_03;
  undefined4 *extraout_EAX_04;
  
  if (*(int *)(prof_ctx + 0x3500) == 1) {
    prof_malloc(0x54);
    item = extraout_EAX;
  }
  else {
    item = (undefined4 *)pool_alloc(prof_ctx + 0x34e8,0x54);
  }
  *(int *)(prof_ctx + 0x351c) = *(int *)(prof_ctx + 0x351c) + 1;
  *item = *(undefined4 *)(prof_ctx + 0x351c);
  avl_new(10);
  item[4] = extraout_EAX_00;
  avl_new(10);
  item[5] = extraout_EAX_01;
  avl_new(2);
  item[2] = extraout_EAX_02;
  avl_new(2);
  item[3] = extraout_EAX_03;
  if (kind == 5) {
    item[6] = item[6] | 1;
  }
  avl_insert(*(void **)(prof_ctx + 0x3514),item,0);
  if (instr != (void *)0x0) {
    avl_insert((void *)item[2],instr,0);
    *(undefined4 **)((int)instr + 0x98) = item;
  }
  if (name != (char *)0x0) {
    prof_add_file(name,kind);
    item[1] = *extraout_EAX_04;
    extraout_EAX_04[4] = item;
    extraout_EAX_04[2] = 0;
  }
  return;
}


/* ==== avl_cmp_h46bf00 @ 0046bf00 ==== */

char avl_cmp_h46bf00(undefined4 *param_1,undefined4 *param_2)

{
  if (*(int *)*param_2 < *(int *)*param_1) {
    return '\0';
  }
  return (*(int *)*param_1 < *(int *)*param_2) + '\x01';
}


/* ==== avl_cmp_h46bf30 @ 0046bf30 ==== */

void avl_cmp_h46bf30(undefined4 *param_1,undefined4 *param_2)

{
  prof_cmp_name_nocase((void *)*param_1,(void *)*param_2);
  return;
}


/* ==== prof_list_add @ 0046bf50 ==== */

void __cdecl prof_list_add(void *list,void *item)

{
  undefined4 *extraout_EAX;
  undefined4 *item_00;
  
  if (*(int *)(prof_ctx + 0x3500) == 1) {
    prof_malloc(0xc);
    item_00 = extraout_EAX;
  }
  else {
    item_00 = (undefined4 *)pool_alloc(prof_ctx + 0x34e8,0xc);
  }
  *item_00 = item;
  avl_insert(list,item_00,0);
  return;
}


/* ==== prof_list_remove @ 0046bfa0 ==== */

void __cdecl prof_list_remove(void *list,void *item)

{
  void *local_c [3];
  
  local_c[0] = item;
  avl_find(list,local_c,1);
  return;
}


/* ==== prof_list_delete @ 0046bfd0 ==== */

void __cdecl prof_list_delete(void *list,void *item)

{
  void *local_c [3];
  
  local_c[0] = item;
  avl_delete(list,local_c,0,0);
  return;
}


