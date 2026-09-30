/* ==== lst_write_buf @ 0047c2c0 ==== */

void __fastcall lst_write_buf(void)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int in_ECX;
  char *pcVar4;
  char *pcVar5;
  int local_4;
  
  pcVar4 = &prof_fmt_buf;
  local_4 = in_ECX;
  cVar1 = prof_fmt_buf;
  do {
    if (cVar1 == '\0') {
      return;
    }
    if ((lst_line_no == 0) && (lst_col == 0)) {
      fputs(s_Motorola_Profiler_004d553c,lst_file);
      fputs(&prof_version_str,lst_file);
      fputs(prof_date_str,lst_file);
      lst_page_no = lst_page_no + 1;
      fprintf(lst_file,s__s_Page__d_004d5580,prof_objname,lst_page_no);
      lst_line_no = 2;
    }
    switch((int)*pcVar4) {
    case 9:
      local_4 = 0;
      do {
        fputc(0x20,lst_file);
        local_4 = local_4 + 1;
      } while (local_4 < 8);
      break;
    case 10:
      fputc(10,lst_file);
      lst_line_no = lst_line_no + 1;
      if (0x3a < lst_line_no) goto switchD_0047c373_caseD_c;
      break;
    case 0xc:
switchD_0047c373_caseD_c:
      fprintf(lst_file,&DAT_004d557c);
      lst_line_no = 0;
      lst_col = 0;
      break;
    case -0x80:
      break;
    default:
      fputc((int)*pcVar4,lst_file);
      lst_col = lst_col + 1;
      break;
    case -0x7d:
      pcVar5 = pcVar4 + 2;
      if (pcVar4[1] == 'N') {
        prof_put_number(pcVar5,-0x80);
      }
      else {
        cVar1 = *pcVar5;
        pcVar5 = pcVar4 + 3;
        sscanf(pcVar5,&DAT_004c5578,&local_4);
        iVar3 = local_4 + -1;
        bVar2 = 0 < local_4;
        local_4 = iVar3;
        if (bVar2) {
          do {
            fputc((int)cVar1,lst_file);
            iVar3 = local_4 + -1;
            bVar2 = 0 < local_4;
            local_4 = iVar3;
          } while (bVar2);
        }
      }
      cVar1 = *pcVar5;
      pcVar4 = pcVar5;
      while (cVar1 != -0x7d) {
        pcVar5 = pcVar4 + 1;
        pcVar4 = pcVar4 + 1;
        cVar1 = *pcVar5;
      }
    }
    cVar1 = pcVar4[1];
    pcVar4 = pcVar4 + 1;
  } while( true );
}


/* ==== prof_parse_call_directive @ 0047c530 ==== */

void __cdecl prof_parse_call_directive(void *src_line,char *text)

{
  int iVar1;
  int extraout_EAX;
  undefined4 extraout_EAX_00;
  int extraout_EAX_01;
  undefined4 extraout_EAX_02;
  char *local_c;
  char *pcStack_8;
  uint local_4;
  
  prof_scan_call_directive(src_line,text,&local_c);
  *(uint *)((int)src_line + 0xd8) = local_4;
  if ((src_line != (void *)0x0) && ((local_4 & 0x10) != 0)) {
    iVar1 = (**(code **)(*(int *)(cur_itype + 0x18) + 0x2c))(src_line);
    if (iVar1 == 0) {
      *(uint *)(prof_ctx + 0x34e0) = *(uint *)(prof_ctx + 0x34e0) | 6;
      *(undefined4 *)(prof_ctx + 0x378c) = 0;
      *(undefined4 *)(prof_ctx + 0x3790) = 0;
      prof_error(2,PTR_s_File__s__line__d__Directive__s_n_004d3be0,
                 *(undefined4 *)((int)src_line + 0xa4),*(undefined4 *)((int)src_line + 0xa8),
                 s__call__004d5590);
      return;
    }
  }
  iVar1 = (**(code **)(*(int *)(cur_itype + 0x18) + 0x28))(src_line);
  if ((iVar1 == 1) && ((src_line == (void *)0x0 || ((*(byte *)((int)src_line + 0xd8) & 1) == 0)))) {
    *(uint *)((int)src_line + 0xd8) = *(uint *)((int)src_line + 0xd8) | 0x10;
  }
  iVar1 = (**(code **)(*(int *)(cur_itype + 0x18) + 0x30))(src_line);
  if ((iVar1 == 1) && ((src_line == (void *)0x0 || ((*(byte *)((int)src_line + 0xd8) & 1) == 0)))) {
    *(uint *)((int)src_line + 0xd8) = *(uint *)((int)src_line + 0xd8) | 2;
  }
  if (((pcStack_8 != (char *)0x0) && (src_line != (void *)0x0)) &&
     ((*(byte *)((int)src_line + 0xd8) & 0x10) != 0)) {
    cg_lookup_name(pcStack_8,4);
    *(int *)((int)src_line + 0x94) = extraout_EAX;
    if (extraout_EAX == 0) {
      prof_add_func((void *)0x0,pcStack_8,4);
      *(undefined4 *)((int)src_line + 0x94) = extraout_EAX_00;
    }
    avl_insert(*(void **)(*(int *)((int)src_line + 0x94) + 0xc),src_line,0);
  }
  if (((local_c != (char *)0x0) && (src_line != (void *)0x0)) &&
     ((*(byte *)((int)src_line + 0xd8) & 4) != 0)) {
    cg_lookup_name(local_c,4);
    *(int *)((int)src_line + 0x98) = extraout_EAX_01;
    if (extraout_EAX_01 == 0) {
      prof_add_func((void *)0x0,local_c,4);
      *(undefined4 *)((int)src_line + 0x98) = extraout_EAX_02;
    }
    avl_insert(*(void **)(*(int *)((int)src_line + 0x98) + 8),src_line,0);
  }
  return;
}


/* ==== cg_lookup_name @ 0047c6e0 ==== */

void __cdecl cg_lookup_name(char *name,int type)

{
  int extraout_EAX;
  
  if ((name != (char *)0x0) && (*name != '\0')) {
    prof_del_file(name,(void *)type);
    if (extraout_EAX != 0) {
      return;
    }
  }
  return;
}


/* ==== prof_scan_call_directive @ 0047c710 ==== */

void __cdecl prof_scan_call_directive(void *src_line,char *text,void *out)

{
  void *pvVar1;
  char cVar2;
  undefined3 extraout_var;
  int iVar3;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  
  pvVar1 = out;
  *(undefined4 *)out = 0;
  *(undefined4 *)((int)out + 4) = 0;
  *(undefined4 *)((int)out + 8) = 0;
joined_r0x0047c72c:
  while( true ) {
    do {
      while( true ) {
        while( true ) {
          if (text == (char *)0x0) {
            return;
          }
          cVar2 = strstr(text,&DAT_004d55c8);
          if (CONCAT31(extraout_var,cVar2) == 0) {
            return;
          }
          text = (char *)(CONCAT31(extraout_var,cVar2) + 3);
          iVar3 = prof_match_word(&text,s_ignore_004d55c0);
          if (iVar3 != 1) break;
          *(uint *)((int)pvVar1 + 8) = *(uint *)((int)pvVar1 + 8) | 1;
        }
        iVar3 = prof_match_word(&text,s_return_004d55b8);
        if (iVar3 != 1) break;
        *(uint *)((int)pvVar1 + 8) = *(uint *)((int)pvVar1 + 8) | 2;
      }
      iVar3 = prof_match_word(&text,s_enter_004d55b0);
      if (iVar3 != 1) goto LAB_0047c809;
      *(uint *)((int)pvVar1 + 8) = *(uint *)((int)pvVar1 + 8) | 4;
      cVar2 = prof_scan_identifier(&text,&DAT_00504288);
      *(uint *)pvVar1 = CONCAT31(extraout_var_00,cVar2);
      iVar3 = prof_match_word(&text,&DAT_004c1648);
    } while (iVar3 != 1);
    iVar3 = prof_match_word(&text,&DAT_004d55ac);
    if (iVar3 != 1) break;
    *(uint *)((int)pvVar1 + 8) = *(uint *)((int)pvVar1 + 8) | 8;
  }
  goto LAB_0047c877;
LAB_0047c809:
  iVar3 = prof_match_word(&text,&DAT_004d55a4);
  if (iVar3 == 1) {
    *(uint *)((int)pvVar1 + 8) = *(uint *)((int)pvVar1 + 8) | 0x10;
    cVar2 = prof_scan_identifier(&text,&DAT_005042a0);
    *(uint *)((int)pvVar1 + 4) = CONCAT31(extraout_var_01,cVar2);
    iVar3 = prof_match_word(&text,&DAT_004c1648);
    if (iVar3 == 1) {
      iVar3 = prof_match_word(&text,s_joint_ret_004d5598);
      if (iVar3 == 1) {
        *(uint *)((int)pvVar1 + 8) = *(uint *)((int)pvVar1 + 8) | 0x20;
      }
      else {
LAB_0047c877:
        *(uint *)(prof_ctx + 0x34e0) = *(uint *)(prof_ctx + 0x34e0) | 6;
        *(undefined4 *)(prof_ctx + 0x378c) = 0;
        *(undefined4 *)(prof_ctx + 0x3790) = 0;
        prof_error(2,PTR_s_File__s__line__d__Invalid_direct_004d3be4,
                   *(undefined4 *)((int)src_line + 0xa4),*(undefined4 *)((int)src_line + 0xa8));
      }
    }
  }
  goto joined_r0x0047c72c;
}


/* ==== prof_scan_identifier @ 0047c8e0 ==== */

char __cdecl prof_scan_identifier(char **pp,char *outbuf)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  uVar3 = 0;
  pcVar4 = *pp;
  while( true ) {
    if (__mb_cur_max < 2) {
      uVar2 = (byte)_pctype[*pcVar4 * 2] & 8;
    }
    else {
      uVar2 = _isctype((int)*pcVar4,8);
    }
    if (uVar2 == 0) break;
    pcVar4 = pcVar4 + 1;
  }
  if (__mb_cur_max < 2) {
    uVar2 = *(ushort *)(_pctype + *pcVar4 * 2) & 0x103;
  }
  else {
    uVar2 = _isctype((int)*pcVar4,0x103);
  }
  pcVar5 = pcVar4;
  if (uVar2 == 0) {
    return '\0';
  }
  while( true ) {
    if (__mb_cur_max < 2) {
      uVar2 = *(ushort *)(_pctype + *pcVar5 * 2) & 0x107;
    }
    else {
      uVar2 = _isctype((int)*pcVar5,0x107);
    }
    if ((uVar2 == 0) && (*pcVar5 != '_')) break;
    uVar3 = uVar3 + 1;
    pcVar5 = pcVar5 + 1;
  }
  cVar1 = *pcVar5;
  if (cVar1 != '\0') {
    if (__mb_cur_max < 2) {
      uVar2 = (byte)_pctype[cVar1 * 2] & 8;
    }
    else {
      uVar2 = _isctype((int)cVar1,8);
    }
    if ((uVar2 == 0) && (*pcVar5 != ',')) {
      return '\0';
    }
  }
  *pp = pcVar5;
  if (0x17 < (int)uVar3) {
    uVar3 = 0x17;
  }
  pcVar5 = outbuf;
  for (uVar2 = uVar3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar2 = uVar3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar5 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  }
  outbuf[uVar3] = '\0';
  return (char)outbuf;
}


/* ==== cg_note_pc_change @ 0047ca00 ==== */

void __cdecl cg_note_pc_change(void *src_line,int a,int b,int cycles)

{
  int iVar1;
  void *extraout_EAX;
  void *extraout_EAX_00;
  undefined4 uVar2;
  int joint;
  bool bVar3;
  void *pvVar4;
  bool bVar5;
  
  bVar5 = prof_ctx[0xde8] == 2;
  if (((byte)prof_ctx[0xd38] & 6) != 2) {
    if (((bVar5) || (prof_ctx[0xde5] != 0)) ||
       ((src_line != (void *)0x0 && ((*(byte *)((int)src_line + 0xd8) & 8) != 0)))) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if (((!bVar3) && (prof_ctx[0xde6] != 0)) &&
       (*(int *)(prof_ctx[0xde6] + 0xa8) != *(int *)((int)src_line + 0xa8))) {
      subr_return((void *)prof_ctx[0xde7],cycles);
    }
    pvVar4 = (void *)prof_ctx[0xde7];
    if ((pvVar4 != (void *)0x0) && ((*(byte *)((int)pvVar4 + 0xd8) & 2) != 0)) {
      subr_return(pvVar4,cycles);
    }
    if (bVar3) {
      iVar1 = prof_ctx[0xde7];
      if ((iVar1 == 0) || ((*(byte *)(iVar1 + 0xd8) & 0x20) == 0)) {
        joint = 0;
      }
      else {
        joint = 1;
      }
      pvVar4 = (void *)0x0;
      if (bVar5) {
        *prof_ctx = *(undefined4 *)src_line;
        cg_make_mother();
      }
      else if (prof_ctx[0xde5] == 1) {
        pvVar4 = *(void **)(iVar1 + 0x94);
      }
      if (*(int *)((int)src_line + 0x98) == 0) {
        prof_add_func(src_line,(char *)0x0,4);
      }
      cg_merge_nodes(*(void **)((int)src_line + 0x98),pvVar4);
      if (bVar5) {
        prof_ctx[0xd46] = *(undefined4 *)((int)src_line + 0x98);
      }
      else {
        avl_insert(*(void **)(*(int *)((int)src_line + 0x98) + 0xc),(void *)prof_ctx[0xde7],0);
      }
      cg_push_call(*(void **)((int)src_line + 0x98),src_line,cycles,joint,(void *)0x0);
    }
    if ((*(char **)((int)src_line + 0xa0) != (char *)0x0) &&
       ((prof_ctx[0xde6] == 0 ||
        (*(int *)(prof_ctx[0xde6] + 0xa8) != *(int *)((int)src_line + 0xa8))))) {
      cg_lookup_name(*(char **)((int)src_line + 0xa0),5);
      pvVar4 = extraout_EAX;
      if (extraout_EAX == (void *)0x0) {
        prof_add_func((void *)0x0,*(char **)((int)src_line + 0xa0),5);
        pvVar4 = extraout_EAX_00;
      }
      avl_insert(*(void **)((int)pvVar4 + 0xc),src_line,0);
      cg_push_call(pvVar4,src_line,cycles,0,src_line);
    }
    if (((src_line == (void *)0x0) || ((*(byte *)((int)src_line + 0xd8) & 0x10) == 0)) ||
       ((a != 0 && (b != 1)))) {
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
    prof_ctx[0xde5] = uVar2;
    prof_ctx[0xde7] = src_line;
  }
  return;
}


/* ==== cg_merge_nodes @ 0047cc20 ==== */

void __cdecl cg_merge_nodes(void *node,void *other)

{
  int iVar1;
  
  if (other == (void *)0x0) {
    return;
  }
  if (node != other) {
    if (node != (void *)0x0) {
      iVar1 = cg_reaches(node,other,*(int *)(prof_ctx + 0x34e4));
      if ((iVar1 == 1) || (iVar1 = cg_reaches(other,node,-*(int *)(prof_ctx + 0x34e4)), iVar1 == 1))
      {
        *(uint *)((int)node + 0x18) = *(uint *)((int)node + 0x18) | 8;
      }
      cg_merge_edges(node,other,*(void **)((int)node + 0x14),*(void **)((int)other + 0x14),0xb);
      cg_merge_edges(node,other,*(void **)((int)node + 0x10),*(void **)((int)other + 0x10),10);
      cg_merge_edges(node,other,*(void **)((int)node + 8),*(void **)((int)other + 8),9);
      cg_merge_edges(node,other,*(void **)((int)node + 0xc),*(void **)((int)other + 0xc),8);
      *(int *)((int)node + 0x28) = *(int *)((int)node + 0x28) + *(int *)((int)other + 0x28);
      *(int *)((int)node + 0x24) = *(int *)((int)node + 0x24) + *(int *)((int)other + 0x24);
      *(int *)((int)node + 0x1c) = *(int *)((int)node + 0x1c) + *(int *)((int)other + 0x1c);
      *(int *)((int)node + 0x20) = *(int *)((int)node + 0x20) + *(int *)((int)other + 0x20);
      *(uint *)((int)node + 0x18) = *(uint *)((int)node + 0x18) | *(uint *)((int)other + 0x18);
      if ((*(int *)((int)other + 4) != 0) && (*(int *)((int)node + 4) == 0)) {
        *(int *)((int)node + 4) = *(int *)((int)other + 4);
      }
      if (other == *(void **)(prof_ctx + 0x3518)) {
        *(void **)(prof_ctx + 0x3518) = node;
      }
      avl_delete(*(void **)(prof_ctx + 0x3514),other,0,0);
      return;
    }
    return;
  }
  return;
}


/* ==== cg_reaches @ 0047cd50 ==== */

int __cdecl cg_reaches(void *from,void *target,int mark)

{
  char cVar1;
  undefined3 extraout_var;
  undefined4 *puVar2;
  int iVar3;
  undefined3 extraout_var_01;
  char *iter;
  undefined3 extraout_var_00;
  
  if (from == target) {
    return 1;
  }
  if (*(int *)((int)from + 0x2c) != mark) {
    *(int *)((int)from + 0x2c) = mark;
    cVar1 = avl_iter(*(void **)((int)from + 0x10),(char *)0x0,(void *)0x0);
    iter = (char *)CONCAT31(extraout_var,cVar1);
    cVar1 = avl_iter((void *)0x0,iter,(void *)0x0);
    puVar2 = (undefined4 *)CONCAT31(extraout_var_00,cVar1);
    if (puVar2 != (undefined4 *)0x0) {
      do {
        iVar3 = cg_reaches((void *)*puVar2,target,mark);
        if (iVar3 == 1) {
          dsp_free(iter);
          return 1;
        }
        cVar1 = avl_iter((void *)0x0,iter,(void *)0x0);
        puVar2 = (undefined4 *)CONCAT31(extraout_var_01,cVar1);
      } while (puVar2 != (undefined4 *)0x0);
      return 0;
    }
  }
  return 0;
}


/* ==== cg_merge_edges @ 0047cde0 ==== */

void __cdecl cg_merge_edges(void *node,void *other,void *dst_list,void *src_list,int kind)

{
  int iVar1;
  int *key;
  int extraout_EAX;
  void *list;
  
  iVar1 = *(int *)src_list;
  do {
    if (iVar1 == 0) {
      return;
    }
    avl_delete(src_list,*(void **)(iVar1 + 8),0,0);
    avl_find(dst_list,key,1);
    if (kind == 0xb) {
      list = *(void **)(*key + 0x10);
LAB_0047ce78:
      cg_merge_edge_counts(list,node,other);
      if (extraout_EAX == 0) {
LAB_0047ce8f:
        avl_insert(dst_list,key,0);
      }
      else {
        *(int *)(extraout_EAX + 8) = *(int *)(extraout_EAX + 8) + key[2];
        *(int *)(extraout_EAX + 4) = *(int *)(extraout_EAX + 4) + key[1];
      }
    }
    else {
      if (kind == 10) {
        list = *(void **)(*key + 0x14);
        goto LAB_0047ce78;
      }
      if (extraout_EAX == 0) {
        if (kind == 9) {
          key[0x26] = (int)node;
        }
        if ((kind == 8) && (key[0x25] != 0)) {
          key[0x25] = (int)node;
          avl_insert(dst_list,key,0);
          goto LAB_0047ceb3;
        }
        goto LAB_0047ce8f;
      }
    }
LAB_0047ceb3:
    iVar1 = *(int *)src_list;
  } while( true );
}


/* ==== cg_merge_edge_counts @ 0047ced0 ==== */

void __cdecl cg_merge_edge_counts(void *list,void *node,void *other)

{
  undefined4 *item;
  int extraout_EAX;
  
  prof_list_delete(list,other);
  if (item != (undefined4 *)0x0) {
    prof_list_remove(list,node);
    if (extraout_EAX != 0) {
      *(int *)(extraout_EAX + 8) = *(int *)(extraout_EAX + 8) + item[2];
      *(int *)(extraout_EAX + 4) = *(int *)(extraout_EAX + 4) + item[1];
      return;
    }
    *item = node;
    avl_insert(list,item,0);
  }
  return;
}


/* ==== cg_make_mother @ 0047cf30 ==== */

void cg_make_mother(void)

{
  undefined4 *puVar1;
  void *item;
  char cVar2;
  char cVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int extraout_EAX;
  undefined3 extraout_var_01;
  undefined4 extraout_EAX_00;
  void *node;
  
  cVar2 = avl_iter(*(void **)(prof_ctx + 0x3514),(char *)0x0,(void *)0x0);
  cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar2),(void *)0x0);
  node = (void *)CONCAT31(extraout_var_00,cVar3);
  while (node != (void *)0x0) {
    if ((*(void **)((int)node + 4) != (void *)0x0) &&
       (prof_del_file(*(void **)((int)node + 4),(void *)0x3), extraout_EAX != 0)) {
      item = *(void **)(extraout_EAX + 0x1c);
      if (*(void **)((int)item + 0x98) == (void *)0x0) {
        *(void **)((int)item + 0x98) = node;
        avl_insert(*(void **)((int)node + 8),item,0);
      }
      else {
        cg_merge_nodes(node,*(void **)((int)item + 0x98));
      }
    }
    cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar2),(void *)0x0);
    node = (void *)CONCAT31(extraout_var_01,cVar3);
  }
  puVar1 = (undefined4 *)(prof_ctx + 0x3520);
  *(undefined4 *)(prof_ctx + 0x3528) = 0;
  prof_add_func((void *)0x0,s___MOTHER___004d55cc,4);
  *puVar1 = extraout_EAX_00;
  return;
}


/* ==== cg_push_call @ 0047cfe0 ==== */

void __cdecl cg_push_call(void *node,void *src_line,int cycles,int joint,void *ret_line)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  void *sub;
  undefined4 uVar4;
  int iVar5;
  int extraout_EAX;
  undefined4 extraout_EAX_00;
  int extraout_EAX_01;
  undefined4 extraout_EAX_02;
  uint uVar6;
  int iVar7;
  
  uVar6 = *(uint *)(prof_ctx + 0x34e0) & 6;
  if ((uVar6 == 0) && (iVar3 = *(int *)(prof_ctx + 0x3788), iVar3 < 0x15)) {
    iVar7 = *(int *)(prof_ctx + 0x3528 + iVar3 * 0x1c);
    sub = *(void **)(prof_ctx + 0x3520 + iVar3 * 0x1c);
    iVar3 = prof_ctx + 0x3520 + iVar3 * 0x1c;
    *(int *)(iVar3 + 8) = cycles;
    iVar7 = cycles - iVar7;
    *(int *)((int)sub + 0x1c) = *(int *)((int)sub + 0x1c) + iVar7;
    iVar5 = subr_on_stack(sub);
    if (iVar5 == 1) {
      *(int *)((int)sub + 0x20) = *(int *)((int)sub + 0x20) + iVar7;
    }
    *(int *)((int)node + 0x28) = *(int *)((int)node + 0x28) + 1;
    *(int *)(prof_ctx + 0x3788) = *(int *)(prof_ctx + 0x3788) + 1;
    puVar2 = (undefined4 *)(prof_ctx + 0x3520 + *(int *)(prof_ctx + 0x3788) * 0x1c);
    puVar2[1] = *(undefined4 *)src_line;
    puVar2[2] = cycles;
    uVar4 = *(undefined4 *)(prof_ctx + 0x3798);
    *puVar2 = node;
    puVar2[5] = uVar4;
    puVar2[6] = joint;
    prof_list_remove(*(void **)((int)node + 0x14),sub);
    puVar2[4] = extraout_EAX;
    if (extraout_EAX == 0) {
      prof_list_add(*(void **)((int)node + 0x14),sub);
      puVar2[4] = extraout_EAX_00;
    }
    puVar2[3] = 0;
    *(int *)(puVar2[4] + 4) = *(int *)(puVar2[4] + 4) + 1;
    *(void **)(prof_ctx + 0x3798) = ret_line;
    prof_list_remove(*(void **)((int)sub + 0x10),node);
    *(int *)(iVar3 + 0xc) = extraout_EAX_01;
    if (extraout_EAX_01 == 0) {
      prof_list_add(*(void **)((int)sub + 0x10),node);
      *(undefined4 *)(iVar3 + 0xc) = extraout_EAX_02;
    }
    piVar1 = (int *)(*(int *)(iVar3 + 0xc) + 4);
    *piVar1 = *piVar1 + 1;
    return;
  }
  if (uVar6 == 0) {
    *(uint *)(prof_ctx + 0x34e0) = *(uint *)(prof_ctx + 0x34e0) & 0xfffffffb | 2;
    *(undefined4 *)(prof_ctx + 0x378c) = *(undefined4 *)((int)src_line + 0xa4);
    *(undefined4 *)(prof_ctx + 0x3790) = *(undefined4 *)((int)src_line + 0xa8);
  }
  return;
}


