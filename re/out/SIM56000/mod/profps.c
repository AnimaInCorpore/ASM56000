/* ==== prof_out_open @ 0047b670 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl prof_out_open(char *objname,char *basename,char *ext)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined1 *puVar4;
  undefined3 extraout_var_01;
  undefined4 extraout_EAX;
  void *stream;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  char *mode;
  byte *pbVar9;
  char *pcVar10;
  undefined **ppuVar11;
  char *pcVar12;
  char *pcVar13;
  bool bVar14;
  uint local_4;
  
  local_4 = time((long *)0x0);
  pbVar9 = &DAT_004c6b48;
  pbVar5 = (byte *)ext;
  do {
    bVar1 = *pbVar5;
    bVar14 = bVar1 < *pbVar9;
    if (bVar1 != *pbVar9) {
LAB_0047b6b3:
      iVar6 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
      goto LAB_0047b6b8;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar5[1];
    bVar14 = bVar1 < pbVar9[1];
    if (bVar1 != pbVar9[1]) goto LAB_0047b6b3;
    pbVar5 = pbVar5 + 2;
    pbVar9 = pbVar9 + 2;
  } while (bVar1 != 0);
  iVar6 = 0;
LAB_0047b6b8:
  mode = &DAT_004c63b4;
  if (iVar6 != 0) {
    mode = &DAT_004c5c90;
  }
  srand(local_4);
  cVar2 = ctime((long *)&local_4);
  prof_date_str = (char *)CONCAT31(extraout_var,cVar2);
  uVar7 = 0xffffffff;
  pcVar10 = prof_date_str;
  do {
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    cVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
  } while (cVar2 != '\0');
  prof_date_str[~uVar7 - 2] = '\0';
  cVar3 = strrchr(banner_ptr,0x20);
  cVar2 = ((char *)CONCAT31(extraout_var_00,cVar3))[-1];
  pcVar10 = (char *)CONCAT31(extraout_var_00,cVar3);
  while (cVar2 != ' ') {
    cVar2 = pcVar10[-2];
    pcVar10 = pcVar10 + -1;
  }
  prof_version_str = s_Version_004d54dc[0];
  DAT_00503f81 = s_Version_004d54dc[1];
  prof_version_str_1._1_1_ = s_Version_004d54dc[2];
  prof_version_str_1._2_1_ = s_Version_004d54dc[3];
  DAT_00503f88 = s_Version_004d54dc[8];
  uVar7 = 0xffffffff;
  DAT_00503f84 = s_Version_004d54dc[4];
  DAT_00503f85 = s_Version_004d54dc[5];
  DAT_00503f84_1._1_1_ = s_Version_004d54dc[6];
  DAT_00503f84_1._2_1_ = s_Version_004d54dc[7];
  pcVar10 = pcVar10 + -1;
  do {
    pcVar13 = pcVar10;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar13 = pcVar10 + 1;
    cVar2 = *pcVar10;
    pcVar10 = pcVar13;
  } while (cVar2 != '\0');
  uVar7 = ~uVar7;
  iVar6 = -1;
  pcVar10 = &prof_version_str;
  do {
    pcVar12 = pcVar10;
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    pcVar12 = pcVar10 + 1;
    cVar2 = *pcVar10;
    pcVar10 = pcVar12;
  } while (cVar2 != '\0');
  pcVar10 = pcVar13 + -uVar7;
  pcVar13 = pcVar12 + -1;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar10;
    pcVar10 = pcVar10 + 4;
    pcVar13 = pcVar13 + 4;
  }
  puVar4 = &DAT_00503f8a;
  for (uVar7 = uVar7 & 3; cVar2 = DAT_00503f8a, uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar13 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    pcVar13 = pcVar13 + 1;
  }
  while (cVar2 != ' ') {
    pcVar10 = puVar4 + 1;
    puVar4 = puVar4 + 1;
    cVar2 = *pcVar10;
  }
  *puVar4 = 0x20;
  puVar4[1] = 0;
  if (objname == (char *)0x0) {
    prof_error(2,PTR_s_No_object_file_loaded_004d3b94);
    prof_objname = s__scratch__004d54d0;
  }
  else {
    cVar2 = strrchr(objname,0x5c);
    if (CONCAT31(extraout_var_01,cVar2) == 0) {
      prof_objname = objname;
    }
    else {
      prof_objname = (char *)(CONCAT31(extraout_var_01,cVar2) + 1);
    }
  }
  prof_fopen(basename,ext,(char *)0x0,1);
  lst_file = extraout_EAX;
  prof_fopen(basename,mode,&DAT_004d54cc,1);
  ps_file = stream;
  fputs(s___PS_Adobe_1_0___PageOrder__Asce_004d4f84,stream);
  ps_line_buf = 0;
  DAT_00503fc0 = 0;
  ps_need_page = 1;
  ps_page_no = 0;
  lst_page_no = 0;
  lst_line_no = 0;
  lst_col = 0;
  ps_font_sp = 0xffffffff;
  if (ps_font_names == (undefined *)0x0) {
    ppuVar11 = &ps_font_names;
    do {
      cVar2 = _strdup(*ppuVar11);
      *ppuVar11 = (char *)CONCAT31(extraout_var_02,cVar2);
      cVar2 = strchr((char *)CONCAT31(extraout_var_02,cVar2),0x5f);
      puVar4 = (undefined1 *)CONCAT31(extraout_var_03,cVar2);
      while (puVar4 != (undefined1 *)0x0) {
        *puVar4 = 0x2d;
        cVar2 = strchr(*ppuVar11,0x5f);
        puVar4 = (undefined1 *)CONCAT31(extraout_var_04,cVar2);
      }
      ppuVar11 = ppuVar11 + 1;
    } while ((int)ppuVar11 < 0x4d4f0c);
  }
  fprintf(ps_file,s_____Page__1_004d4f74);
  ps_font(0,4,10);
  return;
}


/* ==== prof_out_close @ 0047b8b0 ==== */

void prof_out_close(void)

{
  if (lst_file != &DAT_004d7fc0) {
    fclose(lst_file);
  }
  if (ps_file != (void *)0x0) {
    prof_printf(&DAT_004d54e8);
    fclose(ps_file);
  }
  return;
}


/* ==== ps_font @ 0047b8f0 ==== */

void __cdecl ps_font(int op,int a,int b)

{
  undefined *va0;
  void *stream;
  int iVar1;
  int *piVar2;
  int iVar3;
  int va1;
  undefined4 va1_00;
  
  ps_flush_line();
  piVar2 = &a;
  switch(op) {
  case 0:
  case 1:
  case 2:
    if (op == 1) {
      iVar3 = *(int *)(&DAT_005041ec + ps_font_sp * 8);
    }
    else {
      piVar2 = &b;
      iVar3 = a;
    }
    if (op == 2) {
      va1 = *(int *)(&ps_font_stack + ps_font_sp * 8);
    }
    else {
      va1 = *piVar2;
    }
    ps_font_sp = ps_font_sp + 1;
    if (0x13 < ps_font_sp) {
      prof_error(1,PTR_empty_str_004d3bdc);
    }
    iVar1 = ps_font_sp;
    stream = ps_file;
    va0 = (&ps_font_names)[iVar3];
    *(int *)(&DAT_005041ec + ps_font_sp * 8) = iVar3;
    *(int *)(&ps_font_stack + iVar1 * 8) = va1;
    fprintf(stream,s___s__d_nf_004d54f0,va0,va1);
    return;
  case 3:
    fprintf(ps_file,s___s__d_nf_004d54f0,(&ps_font_names)[a],b);
    return;
  case 4:
    fprintf(ps_file,s___s__d_nf_004d54f0,(&ps_font_names)[*(int *)(&DAT_005041ec + ps_font_sp * 8)],
            a);
    return;
  case 5:
    va1_00 = *(undefined4 *)(&ps_font_stack + ps_font_sp * 8);
    iVar3 = a;
    break;
  case 6:
    ps_font_sp = ps_font_sp + -1;
    if (ps_font_sp < -1) {
      prof_error(1,PTR_empty_str_004d3bdc);
    }
  case 7:
    va1_00 = *(undefined4 *)(&ps_font_stack + ps_font_sp * 8);
    iVar3 = *(int *)(&DAT_005041ec + ps_font_sp * 8);
    break;
  default:
    goto switchD_0047b908_default;
  }
  fprintf(ps_file,s___s__d_nf_004d54f0,(&ps_font_names)[iVar3],va1_00);
switchD_0047b908_default:
  return;
}


/* ==== ps_flush_line @ 0047ba70 ==== */

void ps_flush_line(void)

{
  if (ps_line_len != 0) {
    fputc(0x28,ps_file);
    fputs(&ps_line_buf,ps_file);
    fputs(s___sh_004d54fc,ps_file);
  }
  ps_line_len = 0;
  ps_line_buf = 0;
  return;
}


/* ==== prof_heading @ 0047bad0 ==== */

void __cdecl prof_heading(char *fmt,...)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int unaff_ESI;
  char *pcVar5;
  int unaff_EDI;
  char *pcVar6;
  char *pcVar7;
  char local_190 [400];
  
  ps_font(0,2,10);
  prof_printf(&DAT_004ad72c);
  vsprintf(local_190,fmt,&stack0x00000008);
  uVar2 = 0xffffffff;
  pcVar5 = &DAT_004d5504;
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
  pcVar5 = local_190;
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
  prof_printf(&DAT_004cb15c,local_190);
  ps_font(6,unaff_EDI,unaff_ESI);
  return;
}


/* ==== ps_new_page @ 0047bb70 ==== */

void ps_new_page(void)

{
  char cVar1;
  int iVar2;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  undefined4 extraout_EAX_01;
  undefined4 extraout_EAX_02;
  undefined4 extraout_EAX_03;
  int unaff_ESI;
  char *pcVar3;
  int unaff_EDI;
  char *pcVar4;
  bool bVar5;
  char local_28;
  char local_27 [39];
  
  pcVar4 = prof_date_str;
  iVar2 = ps_page_no + 1;
  pcVar3 = s_Motorola_Profiler_004d553c;
  bVar5 = ps_page_no != 0;
  ps_need_page = 0;
  ps_page_no = iVar2;
  if (bVar5) {
    fprintf(ps_file,&DAT_004d5538);
    fprintf(ps_file,s_____Page___d_004d5524,ps_page_no);
  }
  fprintf(ps_file,&DAT_004d5520);
  ps_line_no = 1;
  ps_line_len = 0;
  ps_font(0,1,10);
  iVar2 = CONCAT31((int3)((uint)extraout_EAX >> 8),s_Motorola_Profiler_004d553c[0]);
  cVar1 = s_Motorola_Profiler_004d553c[0];
  while (cVar1 != '\0') {
    pcVar3 = pcVar3 + 1;
    ps_putc(iVar2);
    cVar1 = *pcVar3;
    iVar2 = CONCAT31((int3)((uint)extraout_EAX_00 >> 8),cVar1);
  }
  iVar2 = CONCAT31((int3)((uint)iVar2 >> 8),prof_version_str);
  pcVar3 = &prof_version_str;
  cVar1 = prof_version_str;
  while (cVar1 != '\0') {
    pcVar3 = pcVar3 + 1;
    ps_putc(iVar2);
    cVar1 = *pcVar3;
    iVar2 = CONCAT31((int3)((uint)extraout_EAX_01 >> 8),cVar1);
  }
  cVar1 = *pcVar4;
  iVar2 = CONCAT31((int3)((uint)iVar2 >> 8),cVar1);
  while (cVar1 != '\0') {
    pcVar4 = pcVar4 + 1;
    ps_putc(iVar2);
    cVar1 = *pcVar4;
    iVar2 = CONCAT31((int3)((uint)extraout_EAX_02 >> 8),cVar1);
  }
  iVar2 = sprintf(&local_28,s__s_Page__d_004d5510,prof_objname,ps_page_no);
  iVar2 = CONCAT31((int3)((uint)iVar2 >> 8),local_28);
  pcVar3 = &local_28;
  while (local_28 != '\0') {
    ps_putc(iVar2);
    local_28 = pcVar3[1];
    iVar2 = CONCAT31((int3)((uint)extraout_EAX_03 >> 8),local_28);
    pcVar3 = pcVar3 + 1;
  }
  ps_font(6,unaff_EDI,unaff_ESI);
  fprintf(ps_file,&DAT_004d550c);
  return;
}


/* ==== ps_putc @ 0047bcb0 ==== */

void __cdecl ps_putc(int c)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  int unaff_EBX;
  int unaff_ESI;
  bool bVar4;
  
  switch((undefined1)c) {
  case 9:
    iVar2 = 8;
    do {
      ps_putc(0x20);
      iVar2 = iVar2 + -1;
      uVar3 = ps_line_len;
    } while (iVar2 != 0);
    break;
  case 10:
    ps_flush_line();
    fprintf(ps_file,&DAT_004d5550);
    if (0 < DAT_00503fc0) {
      DAT_00503fc0 = 0;
      ps_font(6,unaff_ESI,unaff_EBX);
    }
    ps_line_no = ps_line_no + 1;
    uVar3 = ps_line_len;
    if (ps_line_no < 0x3f) break;
  case 0xc:
    ps_flush_line();
    ps_need_page = 1;
    uVar3 = ps_line_len;
    break;
  case 0x28:
  case 0x29:
    (&ps_line_buf)[ps_line_len] = 0x5c;
    ps_line_len = ps_line_len + 1;
    goto LAB_0047bd7d;
  case 0x3b:
    iVar2 = DAT_00503fc0 + 1;
    bVar4 = DAT_00503fc0 != 0;
    uVar3 = ps_line_len;
    DAT_00503fc0 = iVar2;
    if (bVar4) break;
    ps_font(2,6,unaff_ESI);
  default:
LAB_0047bd7d:
    (&ps_line_buf)[ps_line_len] = (undefined1)c;
    uVar3 = ps_line_len + 1;
    puVar1 = &DAT_00504161 + ps_line_len;
    ps_line_len = uVar3;
    *puVar1 = 0;
  }
  if (0x78 < uVar3) {
    ps_line_len = uVar3 - 1;
    *(undefined1 *)((int)&prof_objname + uVar3 + 3) = 0;
  }
  return;
}


/* ==== prof_printf @ 0047bdf0 ==== */

void __cdecl prof_printf(char *fmt,...)

{
  char cVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined4 extraout_EAX;
  undefined1 *extraout_EAX_00;
  undefined1 *extraout_EAX_01;
  undefined1 *c;
  char *pcVar4;
  char *buf;
  undefined1 *puVar5;
  char *c_00;
  undefined1 *args;
  undefined1 *puVar6;
  
  args = &stack0x00000008;
  puVar5 = &prof_fmt_buf;
  vsprintf(&prof_fmt_buf,fmt,args);
  if (prof_fmt_buf == -0x80) {
    lst_write_buf();
    return;
  }
  if (prof_fmt_buf != -0x7f) {
    if (prof_fmt_buf == -0x7e) {
      if (ps_file == (void *)0x0) {
        return;
      }
      fprintf(ps_file,&DAT_004cb15c,&DAT_00503fc9);
      return;
    }
    args = (undefined1 *)0x47be1d;
    lst_write_buf();
  }
  if (ps_file == (void *)0x0) {
    return;
  }
  uVar3 = CONCAT31((int3)((uint)ps_file >> 8),prof_fmt_buf);
  pcVar4 = &prof_fmt_buf;
  cVar1 = prof_fmt_buf;
  do {
    if (cVar1 == '\0') {
      return;
    }
    if (ps_need_page == 1) {
      ps_new_page();
      uVar3 = extraout_EAX;
    }
    cVar1 = *pcVar4;
    c = (undefined1 *)CONCAT31((int3)((uint)uVar3 >> 8),cVar1);
    if (cVar1 != -0x7f) {
      if (cVar1 == -0x7d) {
        buf = pcVar4 + 2;
        if (pcVar4[1] == 'C') {
          ps_flush_line();
          sscanf(buf,&DAT_004c5578,&stack0xfffffffc);
          pcVar4 = s__d_sc_004d5554;
          puVar6 = args;
LAB_0047bf3e:
          c = (undefined1 *)fprintf(ps_file,pcVar4,args);
          args = puVar6;
        }
        else if (pcVar4[1] == 'N') {
          prof_put_number(buf,-0x7f);
          c = extraout_EAX_01;
        }
        else {
          cVar1 = *buf;
          buf = pcVar4 + 3;
          c_00 = (char *)CONCAT31((int3)((uint)fmt >> 8),cVar1);
          puVar6 = args;
          sscanf(buf,&DAT_004c5578,&stack0xfffffff4);
          fmt = c_00;
          args = puVar6;
          if (cVar1 == '-') {
            args = puVar5;
            ps_flush_line();
            pcVar4 = s__d_da_004d555c;
            puVar5 = args;
            fmt = c_00;
            goto LAB_0047bf3e;
          }
          while (bVar2 = 0 < (int)puVar5, c = puVar5 + -1, puVar5 = c, bVar2) {
            ps_putc((int)c_00);
            puVar5 = c;
          }
        }
        cVar1 = *buf;
        pcVar4 = buf;
        while (cVar1 != -0x7d) {
          cVar1 = pcVar4[1];
          c = (undefined1 *)CONCAT31((int3)((uint)c >> 8),cVar1);
          pcVar4 = pcVar4 + 1;
        }
      }
      else {
        ps_putc((int)c);
        c = extraout_EAX_00;
      }
    }
    cVar1 = pcVar4[1];
    uVar3 = CONCAT31((int3)((uint)c >> 8),cVar1);
    pcVar4 = pcVar4 + 1;
  } while( true );
}


/* ==== prof_put_number @ 0047bf70 ==== */

void __cdecl prof_put_number(char *spec,int dest)

{
  char *pcVar1;
  char cVar2;
  double dVar3;
  double dVar4;
  bool bVar5;
  undefined3 uVar6;
  int extraout_EAX;
  char *pcVar7;
  char *buf;
  char *pcVar8;
  char *extraout_EDX;
  char *extraout_EDX_00;
  int iVar9;
  int va0;
  int iVar10;
  bool bVar11;
  longlong lVar12;
  char **va0_00;
  char *local_14;
  undefined4 uStack_10;
  char local_c [12];
  
  iVar10 = 0;
  bVar5 = false;
  bVar11 = *spec == '-';
  pcVar7 = spec;
  if (bVar11) {
    pcVar7 = spec + 1;
  }
  iVar9 = (int)*pcVar7;
  va0 = iVar9 + -0x30;
  buf = pcVar7 + 1;
  cVar2 = pcVar7[1];
  pcVar8 = buf;
  while (cVar2 != -0x7d) {
    if ((cVar2 != ' ') && (iVar10 = iVar10 + 1, cVar2 == '.')) {
      bVar5 = true;
    }
    pcVar1 = pcVar8 + 1;
    pcVar8 = pcVar8 + 1;
    cVar2 = *pcVar1;
  }
  if (va0 < iVar10) {
    if (bVar5) {
      va0_00 = &local_14;
      pcVar7 = &DAT_004d5578;
    }
    else {
      va0_00 = &spec;
      pcVar7 = &DAT_004d3364;
    }
    sscanf(buf,pcVar7,va0_00);
    if (bVar5) {
      iVar10 = 0;
      dVar4 = (double)CONCAT44(uStack_10,local_14);
      for (dVar3 = dVar4; 10.0 <= dVar3; dVar3 = dVar3 * 0.1) {
        iVar10 = iVar10 + 1;
      }
      if (iVar10 < iVar9 + -0x31) {
        if (dVar4 == 0.0) {
          if (bVar11) {
            iVar10 = sprintf(local_c,&DAT_004d5574,va0,0);
          }
          else {
            iVar10 = sprintf(local_c,&DAT_004d556c,va0,0);
          }
        }
        else {
          if (1.0 <= dVar4) {
            iVar9 = (va0 - iVar10) + -2;
          }
          else {
            iVar9 = iVar9 + -0x32;
          }
          iVar10 = sprintf(local_c,&DAT_004d5564,iVar9,local_14,uStack_10);
        }
        uVar6 = (undefined3)((uint)iVar10 >> 8);
        pcVar7 = local_c;
        if (local_c[0] == '\0') {
          return;
        }
        cVar2 = (char)dest;
        do {
          if (cVar2 == -0x80) {
            iVar10 = fputc((int)*pcVar7,lst_file);
          }
          else {
            ps_putc(CONCAT31(uVar6,*pcVar7));
            iVar10 = extraout_EAX;
          }
          pcVar8 = pcVar7 + 1;
          uVar6 = (undefined3)((uint)iVar10 >> 8);
          pcVar7 = pcVar7 + 1;
        } while (*pcVar8 != '\0');
        return;
      }
      lVar12 = _ftol();
      spec = (char *)lVar12;
    }
    if ((!bVar11) && (iVar10 = iVar9 + -0x34, 0 < iVar10)) {
      do {
        if ((char)dest == -0x80) {
          fputc(0x20,lst_file);
        }
        else {
          ps_putc(0x20);
        }
        iVar10 = iVar10 + -1;
      } while (iVar10 != 0);
    }
    iVar10 = 0;
    for (; 99 < (int)spec; spec = (char *)((int)spec / 10)) {
      iVar10 = iVar10 + 1;
    }
    if ((char)dest == -0x80) {
      fputc((int)spec / 10 + 0x30,lst_file);
    }
    else {
      ps_putc(CONCAT31((int3)((uint)((int)spec / 10) >> 8),(char)((int)spec / 10) + '0'));
    }
    if ((char)dest == -0x80) {
      fputc((int)spec % 10 + 0x30,lst_file);
    }
    else {
      ps_putc(CONCAT31((int3)((uint)((int)spec % 10) >> 8),(char)((int)spec % 10) + '0'));
    }
    if ((char)dest == -0x80) {
      fputc(0x65,lst_file);
    }
    else {
      ps_putc(0x65);
    }
    if ((char)dest == -0x80) {
      fputc(iVar10 + 0x30,lst_file);
    }
    else {
      ps_putc(CONCAT31((int3)((uint)iVar10 >> 8),(char)iVar10 + '0'));
    }
    if ((bVar11) && (iVar9 = iVar9 + -0x34, 0 < iVar9)) {
      do {
        if ((char)dest == -0x80) {
          fputc(0x20,lst_file);
        }
        else {
          ps_putc(0x20);
        }
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
    }
  }
  else if (pcVar7[1] != -0x7d) {
    cVar2 = (char)dest;
    do {
      if (cVar2 == -0x80) {
        fputc((int)*buf,lst_file);
        pcVar8 = extraout_EDX;
      }
      else {
        ps_putc(CONCAT31((int3)((uint)pcVar8 >> 8),*buf));
        pcVar8 = extraout_EDX_00;
      }
      pcVar7 = buf + 1;
      buf = buf + 1;
    } while (*pcVar7 != -0x7d);
    return;
  }
  return;
}


