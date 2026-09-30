/* ==== prof_load_cld @ 0047dc80 ==== */

void prof_load_cld(void)

{
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  undefined4 extraout_EAX_01;
  undefined4 extraout_EAX_02;
  int iVar1;
  
  avl_new(1);
  *(undefined4 *)(prof_ctx + 8) = extraout_EAX;
  avl_new(0);
  *(undefined4 *)(prof_ctx + 4) = extraout_EAX_00;
  avl_new(4);
  *(undefined4 *)(prof_ctx + 0xc) = extraout_EAX_01;
  avl_new(6);
  *(undefined4 *)(prof_ctx + 0x3514) = extraout_EAX_02;
  iVar1 = _setjmp3(&prof_jmpbuf,0);
  if (iVar1 == 0) {
    if (*(int *)(prof_ctx + 0x60) != 0) {
      prof_read_cld();
    }
    avl_walk(*(void **)(prof_ctx + 8),hid_47efa0,0,1);
  }
  return;
}


/* ==== prof_read_cld @ 0047dd20 ==== */

void prof_read_cld(void)

{
  void *extraout_EAX;
  void *tree;
  
  prof_fopen(*(char **)(prof_ctx + 0x60),&DAT_004c5ff4,(char *)0x0,1);
  g_prof_fp = extraout_EAX;
  *(undefined4 *)(prof_ctx + 100) = prof_file_size;
  prof_read_filhdr();
  prof_read_sections();
  prof_read_strtab();
  prof_read_symbols();
  prof_get_source_line(0,0);
  prof_read_all_lines();
  prof_get_source_line(-1,0);
  fclose(g_prof_fp);
  *(undefined4 *)(prof_ctx + 0x3500) = 1;
  avl_copy_sorted(*(void **)(prof_ctx + 0xc),5,0);
  *(undefined4 *)(prof_ctx + 0x3500) = 0;
  avl_walk(tree,hid_47e7d0,1,1);
  avl_free(tree,2);
  if (g_prof_strtab != (void *)0x0) {
    dsp_free(g_prof_strtab);
  }
  if (g_prof_sections != (void *)0x0) {
    dsp_free(g_prof_sections);
  }
  return;
}


/* ==== prof_read_strtab @ 0047de10 ==== */

int prof_read_strtab(void)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_EAX;
  
  if (g_prof_nsyms == 0) {
    return 0;
  }
  iVar1 = g_prof_nsyms * 0x20 + g_prof_symptr;
  iVar2 = fseek(g_prof_fp,iVar1,0);
  if (iVar2 != 0) {
    prof_error(1,PTR_s_Failed_to_handle_COFF_file_004d3b98);
  }
  prof_fread(&g_prof_strlen,4,1,g_prof_fp,1);
  if ((*(byte *)((int)g_prof_fp + 0xc) & 0x10) != 0) {
    g_prof_strlen = 0;
    return 0;
  }
  if (g_prof_strlen != 0) {
    g_prof_strlen = g_prof_strlen - 4;
    if ((int)g_prof_strlen < 0) {
      prof_error(1,PTR_s_Failed_to_handle_COFF_file_004d3b98);
    }
    iVar1 = fseek(g_prof_fp,iVar1 + 4,0);
    if (iVar1 != 0) {
      prof_error(1,PTR_s_Failed_to_handle_COFF_file_004d3b98);
    }
    prof_fread((void *)0x0,g_prof_strlen,1,g_prof_fp,0);
    g_prof_strtab = extraout_EAX;
  }
  return 0;
}


/* ==== prof_read_sections @ 0047df00 ==== */

void prof_read_sections(void)

{
  int extraout_EAX;
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int local_34 [4];
  int local_24;
  int local_1c;
  uint local_4;
  
  prof_malloc((g_prof_nscns + 1) * 0x44);
  iVar3 = 1;
  g_prof_sections = extraout_EAX;
  if (0 < g_prof_nscns) {
    iVar2 = 0x44;
    do {
      iVar1 = fseek(g_prof_fp,g_prof_scn_ofs,0);
      if (iVar1 != 0) {
        prof_error(1,PTR_s_Failed_to_handle_COFF_file_004d3b98);
      }
      prof_fread(local_34,0x34,1,g_prof_fp,1);
      prof_swap32(local_34,8);
      *(undefined4 *)(g_prof_sections + 0x3c + iVar2) = 0;
      piVar4 = local_34;
      piVar5 = (int *)(g_prof_sections + iVar2);
      for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
        *piVar5 = *piVar4;
        piVar4 = piVar4 + 1;
        piVar5 = piVar5 + 1;
      }
      if (((local_34[3] == 3) || (local_34[3] == 10)) || (iVar1 = local_1c, local_34[3] == 9)) {
        iVar1 = local_1c >> 1;
      }
      if ((local_4 & 0x400) != 0) {
        iVar1 = local_24;
      }
      *(int *)(g_prof_sections + 0x34 + iVar2) = iVar1 + local_34[2];
      *(int *)(g_prof_sections + 0x38 + iVar2) = iVar3;
      g_prof_scn_ofs = g_prof_scn_ofs + 0x34;
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + 0x44;
    } while (iVar3 <= g_prof_nscns);
  }
  prof_link_sections();
  return;
}


/* ==== prof_link_sections @ 0047e020 ==== */

void prof_link_sections(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int local_4;
  
  *(undefined4 *)(g_prof_sections + 0x38) = 0;
  if (1 < g_prof_nscns) {
    iVar2 = g_prof_nscns * 0x44;
    local_4 = g_prof_nscns + -1;
    iVar3 = g_prof_sections;
    do {
      iVar1 = *(int *)(iVar3 + -0x38 + iVar2);
      uVar4 = *(uint *)(iVar3 + -0x2c + iVar2);
      if ((*(byte *)(iVar3 + -0x13 + iVar2) & 4) == 0) {
        if (((iVar1 == 3) || (iVar1 == 10)) || (iVar1 == 9)) {
          uVar4 = uVar4 >> 1;
        }
      }
      else {
        uVar4 = *(uint *)(iVar3 + -0x34 + iVar2);
      }
      if ((iVar1 == *(int *)(iVar3 + 0xc + iVar2)) &&
         (*(int *)(iVar3 + 8 + iVar2) == uVar4 + *(int *)(iVar3 + -0x3c + iVar2))) {
        *(undefined4 *)(iVar3 + -0xc + iVar2) = *(undefined4 *)(iVar3 + 0x38 + iVar2);
        iVar3 = g_prof_sections;
      }
      iVar2 = iVar2 + -0x44;
      local_4 = local_4 + -1;
    } while (local_4 != 0);
  }
  return;
}


/* ==== prof_read_filhdr @ 0047e0b0 ==== */

void prof_read_filhdr(void)

{
  prof_fread(&g_prof_filhdr,0x1c,1,g_prof_fp,1);
  if (((((g_prof_filhdr != 0x2c5) && (g_prof_filhdr != 0x2c6)) && (g_prof_filhdr != 0x2c7)) &&
      ((g_prof_filhdr != 0x2c8 && (g_prof_filhdr != 0x2c9)))) &&
     ((g_prof_filhdr != 0x2ca && ((g_prof_filhdr != 0x2cb && (g_prof_filhdr != 0x2cc)))))) {
    prof_error(1,PTR_s_Failed_to_handle_COFF_file_004d3b98);
  }
  *(undefined4 *)(prof_ctx + 0x3508) = DAT_005042cc;
  g_prof_symptr = DAT_005042d4;
  g_prof_nscns = DAT_005042cc;
  g_prof_nsyms = DAT_005042d8;
  if ((DAT_005042e0 & 1) == 0) {
    prof_error(1,PTR_s_Failed_to_handle_COFF_file_004d3b98);
  }
  g_prof_scn_ofs = DAT_005042dc + 0x1c;
  return;
}


/* ==== prof_read_symbols @ 0047e180 ==== */

void prof_read_symbols(void)

{
  int *sym;
  byte bVar1;
  int iVar2;
  void *extraout_EAX;
  byte *name;
  void *buf;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  int local_8;
  int local_4;
  
  local_8 = 0;
  if ((g_prof_symptr != 0) && (g_prof_nsyms != 0)) {
    iVar2 = fseek(g_prof_fp,g_prof_symptr,0);
    if (iVar2 != 0) {
      prof_error(1,PTR_s_Failed_to_handle_COFF_file_004d3b98);
    }
    prof_fread((void *)0x0,0x20,g_prof_nsyms,g_prof_fp,1);
    local_4 = 0;
    g_prof_symtab = extraout_EAX;
    if (0 < (int)g_prof_nsyms) {
      do {
        iVar2 = local_4 * 0x20;
        sym = (int *)((int)g_prof_symtab + iVar2);
        if (*(int *)((int)g_prof_symtab + iVar2) != 0) {
          prof_swap32(sym,8);
        }
        if (((sym[6] == 200) || (sym[6] == 0x67)) &&
           (buf = (void *)((local_4 + 1) * 0x20 + (int)g_prof_symtab),
           *(int *)((int)buf + 0x10) == 0)) {
          prof_swap32(buf,0x10);
        }
        name = (byte *)prof_sym_name(sym);
        pbVar5 = &DAT_004c7af0;
        pbVar3 = name;
        do {
          bVar1 = *pbVar3;
          bVar6 = bVar1 < *pbVar5;
          if (bVar1 != *pbVar5) {
LAB_0047e281:
            iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
            goto LAB_0047e286;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar3[1];
          bVar6 = bVar1 < pbVar5[1];
          if (bVar1 != pbVar5[1]) goto LAB_0047e281;
          pbVar3 = pbVar3 + 2;
          pbVar5 = pbVar5 + 2;
        } while (bVar1 != 0);
        iVar4 = 0;
LAB_0047e286:
        if (iVar4 == 0) {
          local_8 = local_8 + 1;
        }
        pbVar5 = &DAT_004c7b00;
        pbVar3 = name;
        do {
          bVar1 = *pbVar3;
          bVar6 = bVar1 < *pbVar5;
          if (bVar1 != *pbVar5) {
LAB_0047e2b9:
            iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
            goto LAB_0047e2be;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar3[1];
          bVar6 = bVar1 < pbVar5[1];
          if (bVar1 != pbVar5[1]) goto LAB_0047e2b9;
          pbVar3 = pbVar3 + 2;
          pbVar5 = pbVar5 + 2;
        } while (bVar1 != 0);
        iVar4 = 0;
LAB_0047e2be:
        if (iVar4 == 0) {
          local_8 = local_8 + -1;
        }
        if (0 < local_8) {
          pbVar5 = &DAT_004d594c;
          pbVar3 = name;
          do {
            bVar1 = *pbVar3;
            bVar6 = bVar1 < *pbVar5;
            if (bVar1 != *pbVar5) {
LAB_0047e2f9:
              iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
              goto LAB_0047e2fe;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar3[1];
            bVar6 = bVar1 < pbVar5[1];
            if (bVar1 != pbVar5[1]) goto LAB_0047e2f9;
            pbVar3 = pbVar3 + 2;
            pbVar5 = pbVar5 + 2;
          } while (bVar1 != 0);
          iVar4 = 0;
LAB_0047e2fe:
          if (iVar4 == 0) {
            *(undefined4 *)(g_prof_sections + 0x3c + sym[4] * 0x44) = 1;
          }
        }
        iVar4 = sym[6];
        if (((((iVar4 == 2) || (iVar4 == 5)) || ((iVar4 == 3 || ((iVar4 == 6 || (iVar4 == 0xd3))))))
            || (iVar4 == 0xd5)) || (iVar4 == 0xd2)) {
          prof_add_symbol((char *)sym,(char *)name);
        }
        local_4 = local_4 + 1 + *(int *)((int)g_prof_symtab + iVar2 + 0x1c);
      } while (local_4 < (int)g_prof_nsyms);
    }
    prof_build_file_names();
    if (g_prof_symtab != (void *)0x0) {
      dsp_free(g_prof_symtab);
    }
  }
  return;
}


/* ==== prof_sym_name @ 0047e3a0 ==== */

char * __cdecl prof_sym_name(int *sym)

{
  if (*sym != 0) {
    return (char *)sym;
  }
  if (((uint)sym[1] < 4) || (g_prof_strlen < sym[1])) {
    prof_error(1,PTR_s_Failed_to_handle_COFF_file_004d3b98);
  }
  return (char *)(g_prof_strtab + -4 + sym[1]);
}


/* ==== prof_build_file_names @ 0047e3e0 ==== */

void prof_build_file_names(void)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  undefined3 extraout_var;
  int iVar4;
  undefined3 extraout_var_00;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar2 = pool_alloc(prof_ctx + 0x34e8,g_prof_nscns * 4 + 4);
  *(int *)(prof_ctx + 0x350c) = iVar2;
  iVar2 = pool_alloc(prof_ctx + 0x34e8,g_prof_nscns * 4 + 4);
  *(int *)(prof_ctx + 0x3510) = iVar2;
  prof_number_symbols();
  iVar2 = g_prof_nscns;
joined_r0x0047e44c:
  if (iVar2 < 1) {
    *(undefined4 *)(prof_ctx + 0x58) = *(undefined4 *)(*(int *)(prof_ctx + 0x3510) + 4);
    return;
  }
  pcVar3 = prof_section_file_name(iVar2);
  cVar1 = pool_strdup(prof_ctx + 0x34e8,pcVar3);
  iVar5 = 0;
  *(uint *)(*(int *)(prof_ctx + 0x350c) + iVar2 * 4) = CONCAT31(extraout_var,cVar1);
  if (0 < g_prof_nsyms) {
    do {
      iVar4 = iVar5 * 0x20 + g_prof_symtab;
      if (iVar2 == *(int *)(iVar4 + 0x10)) {
        iVar4 = 0;
        goto LAB_0047e4ad;
      }
      iVar5 = iVar5 + 1 + *(int *)(iVar4 + 0x1c);
    } while (iVar5 < g_prof_nsyms);
  }
  goto LAB_0047e503;
  while (iVar4 = *(int *)(iVar6 + g_prof_symtab + 8), iVar4 <= iVar5) {
LAB_0047e4ad:
    iVar7 = iVar4;
    iVar6 = iVar7 * 0x20;
    iVar4 = *(int *)(iVar6 + 0x18 + g_prof_symtab);
    if ((iVar4 != 200) && (iVar4 != 0x67)) goto LAB_0047e503;
  }
  pcVar3 = prof_aux_name((char *)((iVar7 + 1) * 0x20 + g_prof_symtab));
  cVar1 = pool_strdup(prof_ctx + 0x34e8,pcVar3);
  *(uint *)(*(int *)(prof_ctx + 0x3510) + iVar2 * 4) = CONCAT31(extraout_var_00,cVar1);
LAB_0047e503:
  iVar2 = iVar2 + -1;
  goto joined_r0x0047e44c;
}


/* ==== prof_aux_name @ 0047e530 ==== */

char * __cdecl prof_aux_name(char *aux)

{
  uint uVar1;
  
  uVar1 = *(uint *)(aux + 0x10);
  if (uVar1 == 0) {
    return aux;
  }
  if ((uVar1 < 4) || (g_prof_strlen < uVar1)) {
    prof_error(1,PTR_s_Failed_to_handle_COFF_file_004d3b98);
  }
  return (char *)(g_prof_strtab + -4 + *(int *)(aux + 0x10));
}


/* ==== prof_section_file_name @ 0047e570 ==== */

char * __cdecl prof_section_file_name(int sec)

{
  int iVar1;
  
  iVar1 = *(int *)(g_prof_sections + 0x40 + sec * 0x44);
  if (iVar1 < 1) {
    return &empty_str;
  }
  return (char *)(*(int *)(iVar1 * 0x20 + 8 + g_prof_symtab) + -4 + g_prof_strtab);
}


/* ==== prof_number_symbols @ 0047e5b0 ==== */

void prof_number_symbols(void)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  bool bVar9;
  
  iVar5 = 0;
  if (((g_prof_nsyms != 0) && (g_prof_symtab != 0)) && (iVar4 = 0, 0 < g_prof_nsyms)) {
    do {
      pbVar2 = (byte *)(iVar4 * 0x20 + g_prof_symtab);
      *(int *)(pbVar2 + 0x14) = iVar5;
      iVar6 = iVar5;
      if (*(int *)(pbVar2 + 0x18) == 0xca) {
        *(int *)(g_prof_sections + 0x40 + *(int *)(pbVar2 + 0x10) * 0x44) = iVar5;
      }
      else if (*(int *)(pbVar2 + 0x18) == 0xc9) {
        pbVar8 = &DAT_004c7c6c;
        pbVar7 = pbVar2;
        do {
          bVar1 = *pbVar7;
          bVar9 = bVar1 < *pbVar8;
          if (bVar1 != *pbVar8) {
LAB_0047e63f:
            iVar3 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
            goto LAB_0047e644;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar7[1];
          bVar9 = bVar1 < pbVar8[1];
          if (bVar1 != pbVar8[1]) goto LAB_0047e63f;
          pbVar7 = pbVar7 + 2;
          pbVar8 = pbVar8 + 2;
        } while (bVar1 != 0);
        iVar3 = 0;
LAB_0047e644:
        iVar6 = iVar4;
        if (iVar3 != 0) {
          iVar6 = *(int *)(iVar5 * 0x20 + 0x14 + g_prof_symtab);
        }
      }
      iVar4 = iVar4 + 1 + *(int *)(pbVar2 + 0x1c);
      iVar5 = iVar6;
    } while (iVar4 < g_prof_nsyms);
  }
  return;
}


/* ==== prof_add_symbol @ 0047e680 ==== */

int __cdecl prof_add_symbol(char *sym,char *name)

{
  char *pcVar1;
  uint uVar2;
  ulong kind;
  int extraout_EAX;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  long local_14;
  char *local_10;
  char *local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  pcVar1 = sym;
  uVar2 = *(uint *)(sym + 0x14) & 0x1000f;
  if ((((((uVar2 == 4) || (uVar2 == 1)) || (uVar2 == 0xe)) || ((uVar2 == 10 || (uVar2 == 0xb)))) ||
      ((uVar2 == 3 || ((uVar2 == 0xd || (uVar2 == 2)))))) ||
     ((uVar2 == 0xc || ((uVar2 == 8 || (uVar2 == 9)))))) {
    pcVar5 = *(char **)(sym + 8);
    ref_kind_info(*(int *)(sym + 0xc),(long *)&sym,&local_14);
    if (sym == (char *)0x0) {
      kind = 0;
      pcVar4 = local_c;
    }
    else {
      kind = 3;
      local_4 = 0;
      pcVar4 = pcVar5;
      pcVar5 = sym;
      if (0 < *(int *)(pcVar1 + 0x10)) {
        local_8 = *(undefined4 *)
                   (g_prof_sections + 0x34 +
                   *(int *)(g_prof_sections + 0x38 + *(int *)(pcVar1 + 0x10) * 0x44) * 0x44);
      }
    }
  }
  else if ((uVar2 == 6) || (uVar2 == 7)) {
    local_10 = *(char **)(sym + 8);
    local_c = *(char **)(sym + 0xc);
    kind = 2;
    pcVar4 = local_c;
    pcVar5 = local_10;
  }
  else {
    if ((uVar2 != 5) && (uVar2 != 0xf)) {
      return 1;
    }
    kind = 1;
    pcVar4 = *(char **)(sym + 8);
    pcVar5 = *(char **)(sym + 0xc);
  }
  if (((byte)*(undefined4 *)(pcVar1 + 0x14) & 0x30) == 0x20) {
    kind = 3;
  }
  prof_add_file(name,kind);
  iVar3 = *(int *)(pcVar1 + 0x10);
  if (iVar3 < 0) {
    iVar3 = -1;
  }
  *(int *)(extraout_EAX + 4) = iVar3;
  *(undefined4 *)(extraout_EAX + 8) = *(undefined4 *)(pcVar1 + 0x18);
  *(char **)(extraout_EAX + 0x10) = pcVar5;
  *(char **)(extraout_EAX + 0x14) = pcVar4;
  *(undefined4 *)(extraout_EAX + 0x18) = local_8;
  *(undefined4 *)(extraout_EAX + 0x1c) = local_4;
  return 0;
}


/* ==== hid_47e7d0 @ 0047e7d0 ==== */

void hid_47e7d0(int param_1)

{
  char cVar1;
  char cVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined4 auStack_dc [55];
  int iVar3;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0xc) == 3)) {
    auStack_dc[0] = *(undefined4 *)(param_1 + 0x14);
    cVar1 = avl_iter(*(void **)(prof_ctx + 8),(char *)auStack_dc,auStack_dc);
    cVar2 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar1),(void *)0x0);
    iVar3 = CONCAT31(extraout_var_00,cVar2);
    while (iVar3 != 0) {
      if (*(int *)(g_prof_sections + 0x38 + *(int *)(iVar3 + 0xb8) * 0x44) ==
          *(int *)(g_prof_sections + 0x38 + *(int *)(param_1 + 4) * 0x44)) {
        *(int *)(param_1 + 0x1c) = iVar3;
        *(int *)(iVar3 + 0x9c) = param_1;
      }
      cVar2 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar1),(void *)0x0);
      iVar3 = CONCAT31(extraout_var_01,cVar2);
    }
    if (((DAT_005042c4 != 0) && (*(int *)(DAT_005042c4 + 0xc) == 3)) &&
       (*(int *)(g_prof_sections + 0x38 + *(int *)(param_1 + 4) * 0x44) ==
        *(int *)(g_prof_sections + 0x38 + *(int *)(DAT_005042c4 + 4) * 0x44))) {
      iVar3 = *(int *)(DAT_005042c4 + 0x14);
      if (*(int *)(param_1 + 0x14) == iVar3) {
        iVar3 = *(int *)(DAT_005042c4 + 0x18);
      }
      *(int *)(param_1 + 0x18) = iVar3;
    }
  }
  DAT_005042c4 = param_1;
  return;
}


/* ==== prof_get_source_line @ 0047e8c0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void * __cdecl prof_get_source_line(int fileno,int line)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  byte *pbVar5;
  int iVar6;
  void *extraout_EAX;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  uint uVar7;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  byte *pbVar8;
  bool bVar9;
  
  iVar3 = line;
  iVar2 = fileno;
  if (fileno == 0) {
    g_prof_src_name = &empty_str;
    g_prof_src_fp = (void *)0x0;
    return (void *)0x0;
  }
  if (fileno == -1) {
    if (g_prof_src_fp != (void *)0x0) {
      fclose(g_prof_src_fp);
    }
    return (void *)0x0;
  }
  pbVar5 = *(byte **)(*(int *)(prof_ctx + 0x3510) + fileno * 4);
  pbVar8 = g_prof_src_name;
  do {
    bVar1 = *pbVar5;
    bVar9 = bVar1 < *pbVar8;
    if (bVar1 != *pbVar8) {
LAB_0047e93b:
      iVar6 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
      goto LAB_0047e940;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar5[1];
    bVar9 = bVar1 < pbVar8[1];
    if (bVar1 != pbVar8[1]) goto LAB_0047e93b;
    pbVar5 = pbVar5 + 2;
    pbVar8 = pbVar8 + 2;
  } while (bVar1 != 0);
  iVar6 = 0;
LAB_0047e940:
  if ((iVar6 != 0) || (line < g_prof_src_line)) {
    if (g_prof_src_fp != (void *)0x0) {
      fclose(g_prof_src_fp);
    }
    g_prof_src_name = *(byte **)(*(int *)(prof_ctx + 0x3510) + iVar2 * 4);
    prof_fopen((char *)g_prof_src_name,&DAT_004c5574,(char *)0x0,2);
    g_prof_src_fp = extraout_EAX;
    if ((extraout_EAX != (void *)0x0) && (*(int *)(prof_ctx + 100) < prof_file_size)) {
      prof_error(2,PTR_s_Source_file__s_more_recent_than_e_004d3bc0,g_prof_src_name);
      g_prof_src_fp = (void *)0x0;
    }
    _g_prof_srcinfo = g_prof_src_name;
    _DAT_00504498 = 0;
    _DAT_0050449c = 0;
    _DAT_005044a0 = 0;
    g_prof_src_line = 0;
  }
  _DAT_00504494 = iVar3;
  if (g_prof_src_fp != (void *)0x0) {
    while ((g_prof_src_line < iVar3 && ((*(byte *)((int)g_prof_src_fp + 0xc) & 0x10) == 0))) {
      fgets(&g_prof_linebuf,400,g_prof_src_fp);
      cVar4 = strstr(&g_prof_linebuf,&DAT_004d55c8);
      _DAT_0050449c = CONCAT31(extraout_var,cVar4);
      if (_DAT_0050449c != 0) {
        line = _DAT_0050449c + 3;
        iVar6 = prof_match_word((char **)&line,s_nested_004d5958);
        if (iVar6 == 1) {
          iVar6 = atoi((char *)line);
          *(int *)(prof_ctx + 0x3504) = iVar6;
        }
      }
      if (g_prof_src_line + 1 == iVar3) {
        cVar4 = strtok(&g_prof_linebuf,&DAT_004d5954);
        fileno = CONCAT31(extraout_var_00,cVar4);
        if (__mb_cur_max < 2) {
          uVar7 = *(ushort *)(_pctype + g_prof_linebuf * 2) & 0x103;
        }
        else {
          uVar7 = _isctype((int)g_prof_linebuf,0x103);
        }
        if (uVar7 != 0) {
          cVar4 = strtok((char *)0x0,&DAT_004d5954);
          fileno = CONCAT31(extraout_var_01,cVar4);
        }
        if (fileno == 0) {
          _DAT_00504498 = 0;
        }
        else {
          if (*(int *)(g_prof_sections + 0x3c + iVar2 * 0x44) == 1) {
            cVar4 = pool_strdup(prof_ctx + 0x34e8,(char *)fileno);
            _DAT_00504498 = CONCAT31(extraout_var_02,cVar4);
          }
          else {
            _DAT_00504498 = 0;
          }
          iVar6 = prof_match_word((char **)&fileno,&DAT_004d5950);
          if ((iVar6 != 0) || (iVar6 = prof_match_word((char **)&fileno,&DAT_004a8bfc), iVar6 != 0))
          {
            _DAT_005044a0 = 1;
            goto LAB_0047eb81;
          }
        }
        _DAT_005044a0 = 0;
      }
LAB_0047eb81:
      g_prof_src_line = g_prof_src_line + 1;
    }
  }
  return &g_prof_srcinfo;
}


/* ==== prof_read_all_lines @ 0047eba0 ==== */

void prof_read_all_lines(void)

{
  byte *sec;
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  int secno;
  byte *pbVar5;
  bool bVar6;
  
  secno = 1;
  if (0 < g_prof_nscns) {
    iVar4 = 0x44;
    do {
      sec = (byte *)(g_prof_sections + iVar4);
      if (0x44 < iVar4) {
        pbVar5 = &DAT_004d2c20;
        pbVar2 = sec;
        do {
          bVar1 = *pbVar2;
          bVar6 = bVar1 < *pbVar5;
          if (bVar1 != *pbVar5) {
LAB_0047ebf7:
            iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
            goto LAB_0047ebfc;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar2[1];
          bVar6 = bVar1 < pbVar5[1];
          if (bVar1 != pbVar5[1]) goto LAB_0047ebf7;
          pbVar2 = pbVar2 + 2;
          pbVar5 = pbVar5 + 2;
        } while (bVar1 != 0);
        iVar3 = 0;
LAB_0047ebfc:
        if ((iVar3 == 0) || ((*(uint *)(sec + 0x30) & 0x800) != 0)) {
          prof_read_section_lines(secno,(char *)sec);
        }
        pbVar5 = &DAT_004d2c18;
        pbVar2 = sec;
        do {
          bVar1 = *pbVar2;
          bVar6 = bVar1 < *pbVar5;
          if (bVar1 != *pbVar5) {
LAB_0047ec3d:
            iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
            goto LAB_0047ec42;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar2[1];
          bVar6 = bVar1 < pbVar5[1];
          if (bVar1 != pbVar5[1]) goto LAB_0047ec3d;
          pbVar2 = pbVar2 + 2;
          pbVar5 = pbVar5 + 2;
        } while (bVar1 != 0);
        iVar3 = 0;
LAB_0047ec42:
        if (iVar3 != 0) {
          pbVar5 = &DAT_004d5960;
          pbVar2 = sec;
          do {
            bVar1 = *pbVar2;
            bVar6 = bVar1 < *pbVar5;
            if (bVar1 != *pbVar5) {
LAB_0047ec71:
              iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
              goto LAB_0047ec76;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar2[1];
            bVar6 = bVar1 < pbVar5[1];
            if (bVar1 != pbVar5[1]) goto LAB_0047ec71;
            pbVar2 = pbVar2 + 2;
            pbVar5 = pbVar5 + 2;
          } while (bVar1 != 0);
          iVar3 = 0;
LAB_0047ec76:
          if (iVar3 != 0) goto LAB_0047ec84;
        }
        prof_mark_data_section(secno,(char *)sec);
      }
LAB_0047ec84:
      secno = secno + 1;
      iVar4 = iVar4 + 0x44;
    } while (secno <= g_prof_nscns);
  }
  return;
}


/* ==== prof_mark_data_section @ 0047eca0 ==== */

void __cdecl prof_mark_data_section(int secno,char *sec)

{
  int *piVar1;
  int iVar2;
  int extraout_EAX;
  ulong uVar3;
  int iVar4;
  ulong line;
  uint uVar5;
  ulong local_8;
  ulong local_4;
  
  uVar5 = ~*(uint *)(sec + 0x30) >> 7 & 1;
  ref_kind_info(*(int *)(sec + 0xc),(long *)&local_8,(long *)0x0);
  uVar3 = 1;
  if (local_8 != 4) {
    uVar3 = local_8;
  }
  local_4 = 2;
  if (local_8 != 4) {
    local_4 = local_8;
  }
  if ((*(uint *)(sec + 0x30) & 0x400) == 0) {
    iVar4 = *(int *)(sec + 0x18);
    if (local_8 == 4) {
      iVar4 = iVar4 >> 1;
    }
  }
  else {
    iVar4 = *(int *)(sec + 0x10);
  }
  if ((int)uVar3 <= (int)local_4) {
    do {
      line = *(ulong *)(sec + 8);
      local_8 = uVar3;
      iVar2 = iVar4;
      if (uVar5 == 1) {
        piVar1 = (int *)(prof_ctx + 0x6c + uVar3 * 4);
        *piVar1 = *piVar1 + iVar4;
      }
      else {
        piVar1 = (int *)(prof_ctx + 0x80 + uVar3 * 4);
        *piVar1 = *piVar1 + iVar4;
      }
      for (; iVar2 != 0; iVar2 = iVar2 + -1) {
        prof_add_line(local_8,line);
        if (uVar5 == 1) {
          *(uint *)(extraout_EAX + 0xc) = *(uint *)(extraout_EAX + 0xc) | 2;
        }
        line = line + 1;
      }
      uVar3 = local_8 + 1;
    } while ((int)uVar3 <= (int)local_4);
  }
  return;
}


/* ==== prof_read_section_lines @ 0047ed70 ==== */

void __cdecl prof_read_section_lines(int secno,char *sec)

{
  uint line;
  uint *puVar1;
  int iVar2;
  uint *extraout_EAX;
  int extraout_EAX_00;
  void *srcloc;
  int extraout_EAX_01;
  uint uVar3;
  ulong space_addr;
  uint local_1c;
  uint *local_18;
  long local_14;
  int local_10;
  uint *local_c;
  uint local_8;
  int local_4;
  
  uVar3 = 0;
  local_18 = (uint *)0x0;
  local_4 = 1;
  if (*(int *)(sec + 0x2c) == 0) {
    local_1c = 0;
  }
  else {
    iVar2 = fseek(g_prof_fp,*(long *)(sec + 0x24),0);
    if (iVar2 == 0) {
      prof_fread((void *)0x0,0xc,*(ulong *)(sec + 0x2c),g_prof_fp,1);
      local_1c = *(uint *)(sec + 0x30) & 0x800;
      local_18 = extraout_EAX;
    }
    else {
      prof_error(1,PTR_s_Failed_to_handle_COFF_file_004d3b98);
      local_1c = *(uint *)(sec + 0x30) & 0x800;
    }
  }
  if (local_1c == 0) {
    local_8 = *(uint *)(sec + 8);
    local_14 = 0;
  }
  else {
    ref_kind_info(*(int *)(sec + 0xc),&local_14,(long *)0x0);
    if (local_14 == 3) {
      iVar2 = 0;
    }
    else {
      iVar2 = (local_14 != 1) + 1;
    }
    iVar2 = memmap_find(iVar2,0);
    if (((*(uint *)(*(int *)(cur_dtype + 0x20) + 0x24 + iVar2 * 0x2c) & 0x10000000) != 0) &&
       (iVar2 = memmap_find(0,0),
       (*(uint *)(*(int *)(cur_dtype + 0x20) + 0x24 + iVar2 * 0x2c) & 0x4000000) != 0)) {
      local_4 = 2;
    }
    local_8 = *local_18;
  }
  iVar2 = 0;
  puVar1 = local_18;
  if (*(int *)(sec + 0x18) != 0) {
    do {
      local_c = puVar1;
      line = uVar3 + local_8;
      if (iVar2 == 2) {
        prof_add_line(3,line);
        *(uint *)(extraout_EAX_00 + 0xc) = *(uint *)(extraout_EAX_00 + 0xc) | 2;
        uVar3 = uVar3 + 1;
        *(int *)(prof_ctx + 0x78) = *(int *)(prof_ctx + 0x78) + 1;
        iVar2 = 0;
      }
      if ((local_18 != (uint *)0x0) && (*local_c <= line)) {
        srcloc = prof_get_source_line(secno,local_c[2]);
        if (*(int *)((int)srcloc + 0x10) == 0) {
          if (local_1c == 0) {
            local_10 = 3;
            space_addr = line;
          }
          else {
            local_10 = local_14;
            space_addr = local_4 * uVar3 + *(int *)(sec + 8);
          }
          prof_add_instr(line,local_10,space_addr,srcloc);
          if (extraout_EAX_01 != 0) {
            *(int *)(extraout_EAX_01 + 0xb8) = secno;
            if (local_1c != 0) {
              *(ulong *)(extraout_EAX_01 + 0xb0) = space_addr;
              *(int *)(extraout_EAX_01 + 0xac) = local_10;
            }
            uVar3 = uVar3 + ((*(uint *)(extraout_EAX_01 + 0xc) & 4) != 0) + 1;
            iVar2 = 0;
          }
        }
        local_c = local_c + 3;
      }
      iVar2 = iVar2 + 1;
      puVar1 = local_c;
    } while (uVar3 < *(uint *)(sec + 0x18));
  }
  if (local_18 != (uint *)0x0) {
    dsp_free(local_18);
  }
  return;
}


/* ==== hid_47efa0 @ 0047efa0 ==== */

void hid_47efa0(int *param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  
  if (param_1 != (int *)0x0) {
    if (param_1[0x2b] == 0) {
      iVar3 = (**(code **)(*(int *)(cur_itype + 0x18) + 0x10))(param_1);
      if ((0 < (int)DAT_00504488) && (*param_1 == *(int *)(&DAT_005044b0 + (int)DAT_00504488 * 4)))
      {
        DAT_00504488 = (int *)((int)DAT_00504488 - 1);
      }
      if (DAT_00504488 == (int *)0x0) {
        piVar1 = (int *)(prof_ctx + 0x1068 + iVar3 * 4);
        *piVar1 = *piVar1 + 1;
      }
      else {
        uVar2 = *(uint *)(prof_ctx + 0xd48 + iVar3 * 4);
        if (uVar2 < DAT_00504488) {
          if (*(uint *)(prof_ctx + 0xc4) < DAT_00504488) {
            *(int **)(prof_ctx + 0xc4) = DAT_00504488;
          }
          *(int **)(prof_ctx + 0xd48 + iVar3 * 4) = DAT_00504488;
          *(undefined4 *)(prof_ctx + 0xa28 + iVar3 * 4) = 1;
        }
        else if (DAT_00504488 == (int *)uVar2) {
          piVar1 = (int *)(prof_ctx + 0xa28 + iVar3 * 4);
          *piVar1 = *piVar1 + 1;
        }
      }
      iVar3 = (**(code **)(*(int *)(cur_itype + 0x18) + 0x34))(param_1);
      if (0 < iVar3) {
        if (iVar3 == 2) {
          iVar3 = *param_1;
        }
        else {
          iVar3 = 0;
        }
        DAT_00504488 = (int *)((int)DAT_00504488 + 1);
        *(int *)(&DAT_005044b0 + (int)DAT_00504488 * 4) = param_1[2] + 1 + iVar3;
      }
    }
    return;
  }
  DAT_00504488 = param_1;
  return;
}


