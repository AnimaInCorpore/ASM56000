/* ==== cdb_load_value @ 0045efe0 ==== */

int __cdecl cdb_load_value(void *v)

{
  int iVar1;
  
  if (*(short *)((int)v + 0x3c) == 1) {
    iVar1 = *(int *)((int)v + 0x24);
    if (iVar1 == 1) {
      iVar1 = cdb_load_auto(v);
      if (iVar1 == 0) {
        return 0;
      }
    }
    else if ((((iVar1 == 2) || (iVar1 == 0x12)) || (iVar1 == 3)) || (iVar1 == 0x13)) {
      iVar1 = cdb_load_memory(v);
      if (iVar1 == 0) {
        return 0;
      }
    }
    else if ((iVar1 == 4) || (iVar1 == 0x11)) {
      iVar1 = cdb_load_register(v);
      if (iVar1 == 0) {
        return 0;
      }
    }
    else if (iVar1 == -0x80000000) {
      iVar1 = cdb_load_devreg(v);
      if (iVar1 == 0) {
        return 0;
      }
    }
    else {
      if (iVar1 != 9) {
        cdb_internal_error(0x4d30a4,0x12f);
        return 1;
      }
      iVar1 = cdb_load_arg(v);
      if (iVar1 == 0) {
        return 0;
      }
    }
  }
  return 1;
}


/* ==== cdb_store_value @ 0045f090 ==== */

int __cdecl cdb_store_value(void *v)

{
  int iVar1;
  
  if (*(short *)((int)v + 0x3c) == 1) {
    iVar1 = *(int *)((int)v + 0x24);
    if (iVar1 == 1) {
      iVar1 = cdb_store_auto(v);
      if (iVar1 == 0) {
        return 0;
      }
    }
    else if ((((iVar1 == 2) || (iVar1 == 0x12)) || (iVar1 == 3)) || (iVar1 == 0x13)) {
      iVar1 = cdb_store_memory(v);
      if (iVar1 == 0) {
        return 0;
      }
    }
    else if ((iVar1 == 4) || (iVar1 == 0x11)) {
      iVar1 = cdb_store_register(v);
      if (iVar1 == 0) {
        return 0;
      }
    }
    else if (iVar1 == -0x80000000) {
      iVar1 = cdb_store_devreg(v);
      if (iVar1 == 0) {
        return 0;
      }
    }
    else {
      if (iVar1 != 9) {
        cdb_internal_error(0x4d30a4,0x15b);
        return 1;
      }
      iVar1 = cdb_store_arg(v);
      if (iVar1 == 0) {
        return 0;
      }
    }
  }
  else {
    cdb_internal_error(0x4d30a4,0x161);
  }
  return 1;
}


/* ==== cdb_set_quiet @ 0045f150 ==== */

void __cdecl cdb_set_quiet(int flag)

{
  cdb_quiet = flag;
  return;
}


/* ==== cdb_error @ 0045f160 ==== */

void __cdecl cdb_error(char *msg)

{
  int va0;
  char *va1;
  
  if ((msg != (char *)0x0) && (cdb_quiet == 0)) {
    va1 = msg + 1;
    va0 = toupper((int)*msg);
    sprintf(&cdb_errbuf,&DAT_004d30b0,va0,va1);
    expr_error(&cdb_errbuf);
  }
  return;
}


/* ==== cdb_c_error @ 0045f1b0 ==== */

void __cdecl cdb_c_error(char *msg)

{
  if ((msg != (char *)0x0) && (cdb_quiet == 0)) {
    sprintf(&cdb_errbuf,s_C_error___s_004d30b8,msg);
    sim_error(&cdb_errbuf);
  }
  return;
}


/* ==== cdb_internal_error @ 0045f1f0 ==== */

void __cdecl cdb_internal_error(char *file,int line)

{
  if ((file != (char *)0x0) && (cdb_quiet == 0)) {
    sprintf(&cdb_errbuf,s_C_error__internal_error__please_r_004d30c4,file,line);
    sim_error(&cdb_errbuf);
  }
  return;
}


/* ==== cdb_malloc @ 0045f230 ==== */

void __cdecl cdb_malloc(ulong n)

{
  dsp_alloc(n,0);
  return;
}


/* ==== cdb_realloc @ 0045f240 ==== */

void __cdecl cdb_realloc(void *p,ulong n)

{
  dsp_realloc(p,n);
  return;
}


/* ==== cdb_free @ 0045f260 ==== */

void __cdecl cdb_free(void *p)

{
  dsp_free(p);
  return;
}


/* ==== cdb_free_expr @ 0045f270 ==== */

void __cdecl cdb_free_expr(void *node)

{
  undefined4 *puVar1;
  undefined4 *p;
  
  if (node != (void *)0x0) {
    if (*(void **)node != (void *)0x0) {
      cdb_free_expr(*(void **)node);
    }
    if (*(void **)((int)node + 4) != (void *)0x0) {
      cdb_free_expr(*(void **)((int)node + 4));
    }
    if (*(void **)((int)node + 8) != (void *)0x0) {
      cdb_free_expr(*(void **)((int)node + 8));
    }
    if (*(void **)((int)node + 0x10) != (void *)0x0) {
      cdb_free(*(void **)((int)node + 0x10));
    }
    p = *(undefined4 **)((int)node + 0x14);
    while (p != (undefined4 *)0x0) {
      puVar1 = (undefined4 *)p[1];
      if ((void *)*p != (void *)0x0) {
        cdb_free_expr((void *)*p);
      }
      cdb_free(p);
      p = puVar1;
    }
    cdb_free(node);
  }
  return;
}


/* ==== cdb_value_to_string @ 0045f2f0 ==== */

char __cdecl cdb_value_to_string(void *v,int radix)

{
  cdb_out_reset();
  cdb_format_value(v,radix);
  return (char)cdb_outbuf;
}


/* ==== cdb_type_to_string @ 0045f310 ==== */

char __cdecl cdb_type_to_string(void *v)

{
  cdb_out_reset();
  cdb_type_name(v);
  return (char)cdb_outbuf;
}


/* ==== cdb_print_typed_value @ 0045f330 ==== */

void __cdecl cdb_print_typed_value(int radix,void *v)

{
  char cVar1;
  undefined3 extraout_var;
  
  if (v == (void *)0x0) {
    cdb_internal_error(0x4d30a4,0x1e2);
    return;
  }
  cVar1 = cdb_type_to_string(v);
  if (CONCAT31(extraout_var,cVar1) != 0) {
    cdb_out_append(&DAT_004d3100);
    cdb_format_value(v,radix);
    cdb_print_wrapped(cdb_outbuf,(char *)0x0,(char *)0x0,0,0);
  }
  return;
}


/* ==== cdb_frame_slot @ 0045f390 ==== */

int __cdecl cdb_frame_slot(int sclass,int offset,int *space_out,ulong *addr_out)

{
  ulong uVar1;
  int iVar2;
  
  if (cdb_arch == 0x2cb) {
    *space_out = 0;
    uVar1 = cdb_frame_fp();
    *addr_out = uVar1 + (8 - offset) & cdb_addr_mask;
    return 1;
  }
  iVar2 = cdb_default_space();
  *space_out = iVar2;
  uVar1 = cdb_frame_fp();
  *addr_out = uVar1 + offset & cdb_addr_mask;
  return 1;
}


/* ==== cdb_register_value @ 0045f400 ==== */

void __cdecl cdb_register_value(char *name)

{
  char cVar1;
  long lVar2;
  int extraout_EAX;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  int local_2c;
  char local_28 [4];
  char local_24 [4];
  char local_20 [32];
  
  pcVar6 = name;
  lVar2 = periph_find_reg(*(int *)(cur_dev + 4),name,(int *)&name,&local_2c);
  if (lVar2 == 0) {
    local_28[0] = s_register_004d3124[0];
    local_28[1] = s_register_004d3124[1];
    local_28[2] = s_register_004d3124[2];
    local_28[3] = s_register_004d3124[3];
    local_24[0] = s_register_004d3124[4];
    local_24[1] = s_register_004d3124[5];
    local_24[2] = s_register_004d3124[6];
    local_24[3] = s_register_004d3124[7];
    local_20[0] = s_register_004d3124[8];
    local_20[1] = s_register_004d3124[9];
    strncat(local_28,pcVar6,10);
    pcVar6 = s_unknown_004d3104;
  }
  else {
    new_node();
    if (extraout_EAX == 0) {
      return;
    }
    *(int *)(*(int *)(extraout_EAX + 0x10) + 0x18) = local_2c;
    *(char **)(*(int *)(extraout_EAX + 0x10) + 0x1c) = name;
    *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x24) = 0x80000000;
    uVar3 = *(uint *)(*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + (int)name * 0x48) + 0x2c
                              ) + 0x10 + local_2c * 0x1c);
    if ((uVar3 & 0x200) == 0) {
      *(ushort *)(*(int *)(extraout_EAX + 0x10) + 0x3c) = (byte)~(byte)(uVar3 >> 8) & 1;
      *(uint *)(*(int *)(extraout_EAX + 0x10) + 0x28) = uVar3 & 0xfffc0007;
      iVar4 = str_nicmp_ascii(pcVar6,&DAT_004d3110,3);
      if (((iVar4 != 0) && (iVar4 = str_nicmp_ascii(pcVar6,&DAT_004b722c,3), iVar4 != 0)) &&
         (iVar4 = str_nicmp_ascii(pcVar6,&DAT_004b7220,4), iVar4 != 0)) {
        iVar4 = tolower((int)*pcVar6);
        if (iVar4 == 0x72) {
          if (__mb_cur_max < 2) {
            uVar5 = (byte)_pctype[pcVar6[1] * 2] & 4;
          }
          else {
            uVar5 = _isctype((int)pcVar6[1],4);
          }
          if (uVar5 != 0) {
            *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 0x1e;
            return;
          }
        }
        iVar4 = tolower((int)*pcVar6);
        if (iVar4 == 100) {
          if (__mb_cur_max < 2) {
            uVar5 = (byte)_pctype[pcVar6[1] * 2] & 4;
          }
          else {
            uVar5 = _isctype((int)pcVar6[1],4);
          }
          if ((uVar5 != 0) &&
             (((pcVar6[2] == '.' &&
               (((iVar4 = tolower((int)pcVar6[3]), iVar4 == 0x73 ||
                 (iVar4 = tolower((int)pcVar6[3]), iVar4 == 100)) ||
                (iVar4 = tolower((int)pcVar6[3]), iVar4 == 0x78)))) || (pcVar6[2] == '\0')))) {
            if (pcVar6[2] == '\0') {
              *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 7;
              return;
            }
            iVar4 = tolower((int)pcVar6[3]);
            if (iVar4 != 0x73) {
              *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 7;
              return;
            }
            *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 6;
            return;
          }
        }
        if (((cdb_arch == 0x2c7) || (cdb_arch == 0x2ca)) ||
           ((cdb_arch == 0x2cb || ((cdb_arch == 0x2cc || (cdb_arch == 0x2c9)))))) {
          if ((uVar3 & 0xf0000000) == 0) {
            uVar3 = uVar3 & 0xf200000;
            goto LAB_0045f6e0;
          }
        }
        else {
          if ((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) {
            if (cdb_arch != 0x2c6) {
              cdb_internal_error(0x4d30a4,0x290);
              return;
            }
            *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 0xe;
            return;
          }
          if ((uVar3 & 0xfc000000) == 0) {
            uVar3 = uVar3 & 0x3b00000;
LAB_0045f6e0:
            if (uVar3 == 0) {
              *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 0xe;
              return;
            }
            *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 0xf;
            return;
          }
        }
      }
      *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 0xe;
      return;
    }
    local_28[0] = s_register_004d3124[0];
    local_28[1] = s_register_004d3124[1];
    local_28[2] = s_register_004d3124[2];
    local_28[3] = s_register_004d3124[3];
    local_24[0] = s_register_004d3124[4];
    local_24[1] = s_register_004d3124[5];
    local_24[2] = s_register_004d3124[6];
    local_24[3] = s_register_004d3124[7];
    local_20[0] = s_register_004d3124[8];
    local_20[1] = s_register_004d3124[9];
    strncat(local_28,pcVar6,10);
    pcVar6 = s_is_write_only_004d3114;
  }
  uVar3 = 0xffffffff;
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
  pcVar6 = local_28;
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
  cdb_error(local_28);
  return;
}


/* ==== cdb_arch_init @ 0045f790 ==== */

void cdb_arch_init(void)

{
  cdb_arch = *(int *)(cur_dtype + 4);
  if (((cdb_arch == 0x2c7) || (cdb_arch == 0x2ca)) || (cdb_arch == 0x2c9)) {
    cdb_addr_mask = 0xffff;
  }
  else {
    if (cdb_arch != 0x2cc) {
      if ((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) {
        cdb_ext_mask = 0xff;
        cdb_ext_sign_bit = 0x80;
        cdb_ext_bits = 8;
        cdb_word_mask = 0xffffff;
        cdb_addr_mask = (-(uint)(cdb_arch != 0x2c8) & 0xff010000) + 0xffffff;
        cdb_word_bits = 0x18;
        cdb_sign_bit = 0x800000;
        return;
      }
      if (cdb_arch == 0x2c6) {
        cdb_ext_mask = 0xffffffff;
        cdb_word_mask = 0xffffffff;
        cdb_addr_mask = 0xffffffff;
        cdb_word_bits = 0x20;
        cdb_ext_bits = 0x20;
        cdb_sign_bit = 0x80000000;
        cdb_ext_sign_bit = 0x80000000;
        return;
      }
      if (cdb_arch == 0x2cb) {
        cdb_ext_mask = 0xff;
        cdb_word_mask = 0xffff;
        cdb_addr_mask = 0xffffffff;
        cdb_word_bits = 0x10;
        cdb_ext_bits = 8;
        cdb_sign_bit = 0x8000;
        cdb_ext_sign_bit = 0x80;
        return;
      }
      cdb_internal_error(0x4d30a4,0x2ef);
      return;
    }
    cdb_addr_mask = 0xffffff;
  }
  cdb_ext_mask = 0xf;
  cdb_word_mask = 0xffff;
  cdb_word_bits = 0x10;
  cdb_ext_bits = 4;
  cdb_sign_bit = 0x8000;
  cdb_ext_sign_bit = 8;
  return;
}


/* ==== cdb_reg_name @ 0045f930 ==== */

char __cdecl cdb_reg_name(int reg_class,ulong index)

{
  if (cdb_arch == 0x2c7) {
    if ((((reg_class != 5) && (reg_class != 0xf)) && (reg_class != 6)) && (reg_class != 7)) {
      if (9 < index) {
        cdb_internal_error(0x4d30a4,0x30c);
        return '\0';
      }
      return (char)(&PTR_DAT_004922a0)[index];
    }
    if (9 < index) {
      cdb_internal_error(0x4d30a4,0x302);
      return '\0';
    }
    return (char)(&PTR_DAT_004922c8)[index];
  }
  if ((cdb_arch == 0x2c9) || (cdb_arch == 0x2cc)) {
    if ((reg_class != 5) && (((reg_class != 0xf && (reg_class != 6)) && (reg_class != 7)))) {
      if (8 < index) {
        cdb_internal_error(0x4d30a4,0x328);
        return '\0';
      }
      return (char)(&PTR_DAT_004922f0)[index];
    }
    if (8 < index) {
      cdb_internal_error(0x4d30a4,0x31e);
      return '\0';
    }
    return (char)(&PTR_DAT_00492318)[index];
  }
  if (((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) || (cdb_arch == 0x2ca)) {
    if (((reg_class != 5) && (reg_class != 0xf)) && ((reg_class != 6 && (reg_class != 7)))) {
      if (0x15 < index) {
        cdb_internal_error(0x4d30a4,0x343);
        return '\0';
      }
      return (char)(&PTR_DAT_004921f0)[index];
    }
    if (0x15 < index) {
      cdb_internal_error(0x4d30a4,0x339);
      return '\0';
    }
    return (char)(&PTR_DAT_00492248)[index];
  }
  if (cdb_arch != 0x2c6) {
    if (cdb_arch != 0x2cb) {
      cdb_internal_error(0x4d30a4,0x37b);
      return '\0';
    }
    if (0x20 < index) {
      cdb_internal_error(0x4d30a4,0x373);
      return '\0';
    }
    return (char)(&PTR_DAT_00492128)[index];
  }
  if (reg_class == 7) {
    if (7 < index / 3) {
      cdb_internal_error(0x4d30a4,0x352);
      return '\0';
    }
    return (char)(&PTR_DAT_004921d0)[index / 3];
  }
  if (reg_class != 6) {
    if (0x27 < index) {
      cdb_internal_error(0x4d30a4,0x368);
      return '\0';
    }
    return (char)(&PTR_DAT_00492088)[index];
  }
  if (7 < index / 3) {
    cdb_internal_error(0x4d30a4,0x35e);
    return '\0';
  }
  return (char)(&PTR_DAT_004921b0)[index / 3];
}


/* ==== cdb_memspace_name @ 0045fb90 ==== */

char __cdecl cdb_memspace_name(int space,ulong addr)

{
  uint uVar1;
  
  uVar1 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(space,addr);
  if (0x123 < uVar1) {
    return '<';
  }
  return (char)(&PTR_DAT_00492340)[uVar1];
}


/* ==== cdb_print_wrapped @ 0045fbc0 ==== */

/* WARNING: Type propagation algorithm not settling */

void __cdecl
cdb_print_wrapped(char *text,char *prefix_first,char *prefix_cont,ulong indent,int to_log)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  undefined3 extraout_var;
  char *pcVar6;
  undefined3 extraout_var_00;
  uint uVar7;
  uint uVar8;
  int iVar9;
  char *pcVar10;
  undefined4 *puVar11;
  char *pcVar12;
  char *local_18;
  int local_14;
  char *local_10;
  char *local_c;
  char *pcVar5;
  
  bVar2 = false;
  bVar3 = false;
  if (text != (char *)0x0) {
    if (prefix_first == (char *)0x0) {
      local_c = prefix_first;
    }
    else {
      uVar7 = 0xffffffff;
      pcVar5 = prefix_first;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar4 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar4 != '\0');
      local_c = (char *)(~uVar7 - 1);
    }
    if (prefix_cont == (char *)0x0) {
      local_18 = prefix_cont;
    }
    else {
      uVar7 = 0xffffffff;
      pcVar5 = prefix_cont;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar4 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar4 != '\0');
      local_18 = (char *)(~uVar7 - 1);
    }
    cVar4 = strtok(text,&DAT_004c5890);
    bVar1 = true;
    pcVar5 = (char *)CONCAT31(extraout_var,cVar4);
    while (pcVar5 != (char *)0x0) {
      iVar9 = 0;
      cVar4 = *pcVar5;
      while (cVar4 != '\0') {
        local_10 = (char *)0xffffffff;
        local_14 = -1;
        if (bVar1) {
          pcVar10 = (char *)0x0;
        }
        else {
          pcVar10 = (char *)((screen_cols <= (int)indent) - 1 & indent);
          if (0 < (int)pcVar10) {
            puVar11 = &cdb_wrap_line;
            for (uVar7 = (uint)pcVar10 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
              *puVar11 = 0x20202020;
              puVar11 = puVar11 + 1;
            }
            for (uVar7 = (uint)pcVar10 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
              *(undefined1 *)puVar11 = 0x20;
              puVar11 = (undefined4 *)((int)puVar11 + 1);
            }
          }
        }
        if (bVar1) {
          if ((prefix_first == (char *)0x0) || (local_c == (char *)0x0)) {
            if (!bVar1) goto LAB_0045fcd1;
          }
          else {
            uVar7 = 0xffffffff;
            pcVar6 = prefix_first;
            do {
              pcVar12 = pcVar6;
              if (uVar7 == 0) break;
              uVar7 = uVar7 - 1;
              pcVar12 = pcVar6 + 1;
              cVar4 = *pcVar6;
              pcVar6 = pcVar12;
            } while (cVar4 != '\0');
            uVar7 = ~uVar7;
            pcVar6 = pcVar12 + -uVar7;
            pcVar12 = pcVar10 + 0x502a70;
            for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
              *(undefined4 *)pcVar12 = *(undefined4 *)pcVar6;
              pcVar6 = pcVar6 + 4;
              pcVar12 = pcVar12 + 4;
            }
            pcVar10 = pcVar10 + (int)local_c;
            for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
              *pcVar12 = *pcVar6;
              pcVar6 = pcVar6 + 1;
              pcVar12 = pcVar12 + 1;
            }
          }
        }
        else {
LAB_0045fcd1:
          if ((prefix_cont != (char *)0x0) && (local_18 != (char *)0x0)) {
            uVar7 = 0xffffffff;
            pcVar6 = prefix_cont;
            do {
              pcVar12 = pcVar6;
              if (uVar7 == 0) break;
              uVar7 = uVar7 - 1;
              pcVar12 = pcVar6 + 1;
              cVar4 = *pcVar6;
              pcVar6 = pcVar12;
            } while (cVar4 != '\0');
            uVar7 = ~uVar7;
            pcVar6 = pcVar12 + -uVar7;
            pcVar12 = pcVar10 + 0x502a70;
            for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
              *(undefined4 *)pcVar12 = *(undefined4 *)pcVar6;
              pcVar6 = pcVar6 + 4;
              pcVar12 = pcVar12 + 4;
            }
            pcVar10 = pcVar10 + (int)local_18;
            for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
              *pcVar12 = *pcVar6;
              pcVar6 = pcVar6 + 1;
              pcVar12 = pcVar12 + 1;
            }
          }
        }
        cVar4 = pcVar5[iVar9];
        while (cVar4 != '\0') {
          if (__mb_cur_max < 2) {
            uVar7 = (byte)_pctype[cVar4 * 2] & 8;
          }
          else {
            uVar7 = _isctype((int)cVar4,8);
          }
          if ((uVar7 == 0) || (bVar2)) break;
          iVar9 = iVar9 + 1;
          cVar4 = pcVar5[iVar9];
        }
        pcVar6 = pcVar5 + iVar9;
        if (*pcVar6 != '\0') {
          pcVar12 = pcVar10 + 0x502a70;
          while ((int)pcVar10 < screen_cols) {
            cVar4 = *pcVar6;
            if (((cVar4 == '\"') && ((iVar9 == 0 || ((0 < iVar9 && (pcVar6[-1] != '\\')))))) &&
               (bVar2 = !bVar2, bVar2)) {
              bVar3 = true;
            }
            if (__mb_cur_max < 2) {
              uVar7 = (byte)_pctype[cVar4 * 2] & 8;
            }
            else {
              uVar7 = _isctype((int)cVar4,8);
            }
            if ((uVar7 != 0) && (!bVar2)) {
              local_14 = iVar9;
              local_10 = pcVar10;
            }
            pcVar10 = pcVar10 + 1;
            *pcVar12 = *pcVar6;
            iVar9 = iVar9 + 1;
            pcVar6 = pcVar6 + 1;
            if (((((!bVar2) && (0x502a71 < (int)(pcVar12 + 1))) && (pcVar12[-1] == '}')) &&
                (*pcVar12 == ',')) || (pcVar12 = pcVar12 + 1, *pcVar6 == '\0')) goto LAB_0045fe31;
          }
          if ((local_14 != -1) && (iVar9 = local_14, pcVar10 = local_10, bVar3)) {
            bVar2 = false;
          }
        }
LAB_0045fe31:
        pcVar10[0x502a70] = '\0';
        if (to_log == 0) {
          log_echo((char *)&cdb_wrap_line,1);
        }
        else {
          out_text((char *)&cdb_wrap_line,1);
        }
        bVar1 = false;
        cVar4 = pcVar5[iVar9];
      }
      cVar4 = strtok((char *)0x0,&DAT_004c5890);
      pcVar5 = (char *)CONCAT31(extraout_var_00,cVar4);
    }
  }
  return;
}


/* ==== cdb_expr_has_call @ 0045fea0 ==== */

int __cdecl cdb_expr_has_call(void *tree)

{
  int iVar1;
  
  if (tree == (void *)0x0) {
    return 0;
  }
  if (*(int *)((int)tree + 0xc) == 0x145) {
    return 1;
  }
  if ((*(void **)tree != (void *)0x0) && (iVar1 = cdb_expr_has_call(*(void **)tree), iVar1 != 0)) {
    return 1;
  }
  if ((*(void **)((int)tree + 4) != (void *)0x0) &&
     (iVar1 = cdb_expr_has_call(*(void **)((int)tree + 4)), iVar1 != 0)) {
    return 1;
  }
  if ((*(void **)((int)tree + 8) != (void *)0x0) &&
     (iVar1 = cdb_expr_has_call(*(void **)((int)tree + 8)), iVar1 != 0)) {
    return 1;
  }
  return 0;
}


/* ==== cdb_saved_push @ 0045ff00 ==== */

void __cdecl cdb_saved_push(void *node)

{
  uint uVar1;
  
  *(void **)(&cdb_saved_stack + cdb_saved_idx * 4) = node;
  uVar1 = (int)(cdb_saved_idx + 1U) >> 0x1f;
  cdb_saved_idx = ((cdb_saved_idx + 1U ^ uVar1) - uVar1 & 0x3ff ^ uVar1) - uVar1;
  return;
}


/* ==== cdb_saved_pop @ 0045ff30 ==== */

void cdb_saved_pop(void)

{
  if (cdb_saved_idx == 0) {
    return;
  }
  cdb_saved_idx = cdb_saved_idx + -1;
  return;
}


/* ==== cdb_saved_clear @ 0045ff50 ==== */

void cdb_saved_clear(void)

{
  cdb_saved_idx = 0;
  return;
}


/* ==== cdb_save_counters @ 0045ff60 ==== */

void __cdecl cdb_save_counters(int retaddr)

{
  int devidx;
  long lVar1;
  int local_c;
  long local_8;
  int local_4;
  
  devidx = *(int *)(cur_dev + 4);
  cdb_saved_retaddr = retaddr;
  lVar1 = periph_find_reg(devidx,&DAT_004b7220,&local_c,&retaddr);
  if ((lVar1 == 0) || (lVar1 = periph_call(devidx,local_c,retaddr,0x502a60), lVar1 != 0)) {
    lVar1 = periph_find_reg(devidx,&DAT_004b722c,&local_4,&local_8);
    if (lVar1 == 0) {
      return;
    }
    lVar1 = periph_call(devidx,local_4,local_8,0x502b70);
    if (lVar1 != 0) {
      return;
    }
  }
  cdb_c_error(s_unable_to_read_register_004d3130);
  return;
}


/* ==== cdb_finish_call @ 00460000 ==== */

void __cdecl cdb_finish_call(ulong *retaddr_out)

{
  long lVar1;
  int iVar2;
  void *node;
  int iVar3;
  int iVar4;
  char *name;
  int local_20;
  int local_1c;
  int local_18;
  long local_14;
  int local_10;
  uint local_c;
  uint local_8;
  
  *retaddr_out = cdb_saved_retaddr;
  iVar4 = *(int *)(cur_dev + 4);
  lVar1 = periph_find_reg(iVar4,&DAT_004b7220,&local_20,(int *)&retaddr_out);
  if ((lVar1 != 0) &&
     (iVar2 = dev_write_reg(iVar4,local_20,(int)retaddr_out,(long *)&cdb_saved_ictr), iVar2 == 0)) {
    cdb_c_error(s_unable_to_write_register_004d3148);
    return;
  }
  lVar1 = periph_find_reg(iVar4,&DAT_004b722c,&local_18,&local_1c);
  if ((lVar1 != 0) &&
     (iVar2 = dev_write_reg(iVar4,local_18,local_1c,(long *)&cdb_saved_cyc), iVar2 == 0)) {
    cdb_c_error(s_unable_to_write_register_004d3148);
    return;
  }
  cdb_saved_pop();
  if (node == (void *)0x0) {
    return;
  }
  *(undefined4 *)((int)node + 0x18) = 1;
  iVar2 = *(int *)(*(int *)((int)node + 0x10) + 0x20);
  if (((cdb_arch == 0x2c7) || (cdb_arch == 0x2cc)) || (cdb_arch == 0x2c9)) {
    iVar3 = periph_find_reg(iVar4,&DAT_004b29b4,&local_14,&local_10);
  }
  else {
    if (((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) && (cdb_arch != 0x2ca)) {
      if (cdb_arch == 0x2c6) {
        if (((((((byte)iVar2 & 0x30) == 0x10) || (iVar2 == 2)) || (iVar2 == 3)) ||
            ((iVar2 == 4 || (iVar2 == 0xb)))) ||
           ((((iVar2 == 10 || ((iVar2 == 5 || (iVar2 == 0xc)))) || (iVar2 == 0xd)) ||
            ((iVar2 == 0xe || (iVar2 == 0xf)))))) {
          name = &DAT_004d3098;
        }
        else if (iVar2 == 6) {
          name = &DAT_004d2fb8;
        }
        else {
          name = (char *)((iVar2 != 7) - 1 & 0x4d2f78);
        }
        if (((name != (char *)0x0) &&
            (lVar1 = periph_find_reg(iVar4,name,&local_10,&local_14), lVar1 != 0)) &&
           (lVar1 = periph_call(iVar4,local_10,local_14,(long)&local_c), lVar1 == 0)) {
          cdb_c_error(s_unable_to_read_register_004d3130);
          return;
        }
        if ((iVar2 != 6) && (iVar2 != 7)) {
          local_8 = local_c;
        }
      }
      goto LAB_00460277;
    }
    iVar3 = periph_find_reg(iVar4,&DAT_004b29b4,&local_14,&local_10);
  }
  if ((iVar3 != 0) && (lVar1 = periph_call(iVar4,local_14,local_10,(long)&local_c), lVar1 == 0)) {
    cdb_c_error(s_unable_to_read_register_004d3130);
    return;
  }
LAB_00460277:
  if (((byte)iVar2 & 0x30) == 0x10) {
    iVar4 = cdb_default_space();
    *(int *)(*(int *)((int)node + 0x10) + 0x10) = iVar4;
    *(uint *)(*(int *)((int)node + 0x10) + 0xc) = local_8;
    cdb_saved_push(node);
    return;
  }
  if (((iVar2 == 2) || (iVar2 == 0xc)) || ((iVar2 == 3 || (iVar2 == 0xd)))) {
    *(uint *)(*(int *)((int)node + 0x10) + 0xc) = local_8;
    *(undefined4 *)(*(int *)((int)node + 0x10) + 0x10) = 0;
  }
  else {
    if ((((iVar2 == 4) || (iVar2 == 0xb)) || (iVar2 == 10)) || (iVar2 == 0xe)) {
      *(uint *)(*(int *)((int)node + 0x10) + 0xc) = local_8;
      *(undefined4 *)(*(int *)((int)node + 0x10) + 0x10) = 0;
      cdb_saved_push(node);
      return;
    }
    if ((iVar2 == 5) || (iVar2 == 0xf)) {
      *(uint *)(*(int *)((int)node + 0x10) + 0xc) = local_c;
      *(uint *)(*(int *)((int)node + 0x10) + 0x10) = local_8;
      cdb_saved_push(node);
      return;
    }
    if (iVar2 == 6) {
      if (((cdb_arch != 0x2c7) && (cdb_arch != 0x2c9)) &&
         ((cdb_arch != 0x2cb && (cdb_arch != 0x2ca)))) {
        if ((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) {
          *(uint *)(*(int *)((int)node + 0x10) + 8) = local_c;
          cdb_saved_push(node);
          return;
        }
        *(uint *)(*(int *)((int)node + 0x10) + 0x10) = local_8;
        *(uint *)(*(int *)((int)node + 0x10) + 0xc) = local_c;
        cdb_saved_push(node);
        return;
      }
      *(short *)(*(int *)((int)node + 0x10) + 10) = (short)local_8;
      *(undefined2 *)(*(int *)((int)node + 0x10) + 8) = (undefined2)local_c;
      cdb_saved_push(node);
      return;
    }
    if (iVar2 == 7) {
      if ((((cdb_arch != 0x2c7) && (cdb_arch != 0x2c9)) && (cdb_arch != 0x2cb)) &&
         (cdb_arch != 0x2ca)) {
        if ((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) {
          **(uint **)((int)node + 0x10) = local_c;
          *(uint *)(*(int *)((int)node + 0x10) + 4) = local_8;
          cdb_saved_push(node);
          return;
        }
        *(uint *)(*(int *)((int)node + 0x10) + 0x10) = local_8 & cdb_word_mask;
        *(uint *)(*(int *)((int)node + 0x10) + 0xc) = local_c & cdb_word_mask;
        cdb_saved_push(node);
        return;
      }
      *(short *)(*(int *)((int)node + 0x10) + 10) = (short)local_8;
      *(undefined2 *)(*(int *)((int)node + 0x10) + 8) = (undefined2)local_c;
      cdb_saved_push(node);
      return;
    }
    if (((iVar2 != 8) && (iVar2 != 9)) && (iVar2 != 1)) {
      cdb_internal_error(0x4d30a4,0x53d);
      cdb_saved_push(node);
      return;
    }
  }
  cdb_saved_push(node);
  return;
}


/* ==== cdb_type_name @ 004604e0 ==== */

void __cdecl cdb_type_name(void *v)

{
  undefined4 uVar1;
  char cVar2;
  uint uVar3;
  undefined3 extraout_var;
  char *va0;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  uint uVar9;
  undefined4 *puVar10;
  char *pcVar11;
  undefined4 local_80 [8];
  uint local_60;
  int local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  char local_40 [64];
  
  puVar8 = v;
  puVar10 = local_80;
  for (iVar4 = 0x10; uVar5 = local_50, uVar7 = local_4c, uVar9 = local_60, iVar4 != 0;
      iVar4 = iVar4 + -1) {
    *puVar10 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar10 = puVar10 + 1;
  }
  for (; ((uVar3 = uVar9 & 0x30, uVar3 == 0x30 || (uVar3 == 0x20)) || (uVar3 == 0x10));
      uVar9 = uVar9 & 0x1000f | uVar9 >> 2 & 0x3ffebff0) {
    uVar6 = uVar5;
    if (uVar3 == 0x10) {
      pcVar11 = s_pointer_to_004d328c;
LAB_0046056d:
      cdb_out_append(pcVar11);
    }
    else if (uVar3 == 0x30) {
      sprintf(local_40,s_array___ld__of_004d327c,local_54);
      cdb_out_append(local_40);
      uVar1 = local_48;
      local_48 = 1;
      uVar6 = uVar7;
      uVar7 = uVar1;
      local_54 = uVar5;
    }
    else if (uVar3 == 0x20) {
      pcVar11 = s_function_returning_004d3268;
      goto LAB_0046056d;
    }
    uVar5 = uVar6;
  }
  if (uVar9 == 1) {
    cdb_out_append(&DAT_004d3260);
    return;
  }
  if (uVar9 == 2) {
    cdb_out_append(&DAT_004d3258);
    return;
  }
  if (uVar9 == 3) {
    cdb_out_append(s_short_004d3250);
    return;
  }
  if (uVar9 != 4) {
    if (uVar9 == 0xb) goto LAB_00460857;
    if (uVar9 != 10) {
      if (uVar9 == 5) {
        cdb_out_append(&DAT_004d3248);
        return;
      }
      if (uVar9 == 6) {
        cdb_out_append(s_float_004cbf74);
        return;
      }
      if (uVar9 == 7) {
        cdb_out_append(s_double_004d2218);
        return;
      }
      if ((uVar9 == 8) || (uVar9 == 9)) {
        if (*(int *)((int)v + 0x28) == 0) {
          pcVar11 = s_structure_004d3198;
          if (uVar9 != 8) {
            pcVar11 = s_union_004d31ac;
          }
          va0 = s_struct_004d31b4;
          if (uVar9 != 8) {
            va0 = s_union_004d31ac;
          }
          sprintf(local_40,s__s_<_s_type_not_available>_004d317c,va0,pcVar11);
          cdb_out_append(local_40);
          return;
        }
        pcVar11 = s_struct_004d31b4;
        if (uVar9 != 8) {
          pcVar11 = s_union_004d31ac;
        }
        cVar2 = cdb_sym_name(*(int *)((int)v + 0x28));
        sprintf(local_40,s__s__s_004d31a4,pcVar11,CONCAT31(extraout_var,cVar2));
        cdb_out_append(local_40);
        return;
      }
      if (uVar9 == 0xc) {
        cdb_out_append(s_unsigned_char_004d3238);
        return;
      }
      if (uVar9 == 0xd) {
        cdb_out_append(s_unsigned_short_004d3228);
        return;
      }
      if (uVar9 == 0xe) {
        cdb_out_append(s_unsigned_int_004d3218);
        return;
      }
      if (uVar9 != 0xf) {
        if (uVar9 == 0x10000) {
          cdb_out_append(&DAT_004d3200);
          return;
        }
        if (uVar9 == 0x10001) {
          cdb_out_append(s_unsigned_frac_004d31f0);
          return;
        }
        if (uVar9 == 0x10003) {
          cdb_out_append(s_unsigned_long_frac_004d31dc);
          return;
        }
        if (uVar9 != 0x10002) {
          if (uVar9 == 0x10004) {
            cdb_out_append(s_accum_004d31c8);
            return;
          }
          if (uVar9 != 0x10005) {
            cdb_internal_error(0x4d30a4,0x619);
            return;
          }
          cdb_out_append(s_long_accum_004d31bc);
          return;
        }
        cdb_out_append(s_long_frac_004d31d0);
        return;
      }
      cdb_out_append(s_unsigned_long_004d3208);
      return;
    }
  }
  if (uVar9 != 0xb) {
    if (uVar9 != 10) {
      cdb_out_append(&DAT_004ab514);
      return;
    }
    cdb_out_append(s_enum_004d3174);
    if (local_58 != 0) {
      if (cdb_arch != 0x2cb) {
        cVar2 = cdb_sym_name(local_58);
        cdb_out_append((char *)CONCAT31(extraout_var_01,cVar2));
        return;
      }
      cdb_out_append((char *)0x0);
      cdb_free((void *)0x0);
      return;
    }
    cdb_out_append(s_<type_unknown>_004d3164);
    return;
  }
LAB_00460857:
  iVar4 = cdb_enum_tag_sym(local_58);
  cdb_out_append(s_enum_004d3174);
  if (iVar4 != -1) {
    cVar2 = cdb_sym_name(iVar4);
    cdb_out_append((char *)CONCAT31(extraout_var_00,cVar2));
    return;
  }
  cdb_out_append(s_<type_unknown>_004d3164);
  return;
}


/* ==== cdb_format_value @ 00460940 ==== */

void __cdecl cdb_format_value(void *v,int radix)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = *(uint *)((int)v + 0x20);
  if ((((*(short *)((int)v + 0x3c) == 1) && ((uVar1 & 0x30) != 0x30)) && ((uVar1 & 0x30) != 0x20))
     && (iVar2 = cdb_load_value(v), iVar2 == 0)) {
    return;
  }
  uVar3 = uVar1 & 0x30;
  if (uVar3 == 0x10) {
    cdb_fmt_pointer(v,radix);
    return;
  }
  if (uVar3 == 0x20) {
    cdb_fmt_function(v,radix);
    return;
  }
  if (uVar3 == 0x30) {
    cdb_fmt_array(v,radix);
    return;
  }
  if ((uVar1 == 2) || (uVar1 == 0xc)) {
    cdb_fmt_char(v,radix);
  }
  else {
    if ((uVar1 == 3) || (uVar1 == 0xd)) {
      cdb_fmt_short(v,radix);
      return;
    }
    if ((((uVar1 == 4) || (uVar1 == 0xb)) || (uVar1 == 10)) || (uVar1 == 0xe)) {
      cdb_fmt_int(v,radix);
      return;
    }
    if ((uVar1 == 0x10000) || (uVar1 == 0x10001)) {
      cdb_fmt_int(v,radix);
      return;
    }
    if ((uVar1 == 5) || (uVar1 == 0xf)) {
      cdb_fmt_long(v,radix);
      return;
    }
    if ((uVar1 == 0x10002) || (uVar1 == 0x10003)) {
      cdb_fmt_long(v,radix);
      return;
    }
    if (uVar1 == 0x10004) {
      cdb_fmt_accum(v,radix);
      return;
    }
    if (uVar1 == 0x10005) {
      cdb_fmt_long_accum(v,radix);
      return;
    }
    if (uVar1 == 6) {
      cdb_fmt_float(v,radix);
      return;
    }
    if (uVar1 == 7) {
      cdb_fmt_double(v,radix);
      return;
    }
    if (uVar1 == 8) {
      cdb_fmt_struct(v,radix);
      return;
    }
    if (uVar1 == 9) {
      cdb_fmt_union(v,radix);
      return;
    }
    if (uVar1 != 1) {
      cdb_internal_error(0x4d30a4,0x66e);
      return;
    }
  }
  return;
}


/* ==== cdb_fmt_pointer @ 00460b50 ==== */

void __cdecl cdb_fmt_pointer(void *v,int radix)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  undefined3 extraout_var;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint *puVar7;
  uint *puVar8;
  char *fmt;
  undefined2 local_b0;
  undefined1 local_ae;
  uint local_8c [6];
  uint local_74;
  undefined4 local_70;
  uint local_68;
  undefined4 local_64;
  uint local_60;
  undefined4 local_5c;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined2 local_44;
  undefined1 local_40 [12];
  int local_34;
  undefined4 local_20;
  
  puVar7 = v;
  puVar8 = local_8c + 3;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  uVar3 = local_60 >> 2;
  local_60 = uVar3 & 0x3ffebff0 | local_60 & 0x1000f;
  if (((byte)uVar3 & 0x30) == 0x20) {
    iVar6 = 0;
  }
  else {
    iVar6 = cdb_default_space();
    if (iVar6 == 3) {
      uVar3 = *(uint *)((int)v + 0x20) >> 2 & 0x3ffebff0 | *(uint *)((int)v + 0x20) & 0x1000f;
      bVar1 = (byte)uVar3;
      while ((bVar1 & 0x30) == 0x30) {
        uVar3 = uVar3 & 0x1000f | uVar3 >> 2 & 0x3ffebff0;
        bVar1 = (byte)uVar3;
      }
      if ((((((((byte)uVar3 & 0x30) == 0x10) || (uVar3 == 2)) || (uVar3 == 0xc)) ||
           ((uVar3 == 3 || (uVar3 == 0xd)))) || ((uVar3 == 4 || ((uVar3 == 0xb || (uVar3 == 10))))))
         || ((uVar3 == 0xe || ((uVar3 == 6 && (cdb_arch == 0x2c6)))))) {
        iVar6 = 2;
      }
    }
  }
  uVar3 = *(uint *)((int)v + 0xc) & cdb_addr_mask;
  cVar2 = cdb_memspace_name(iVar6,uVar3);
  cdb_out_append((char *)CONCAT31(extraout_var,cVar2));
  cdb_out_append(&DAT_004d32d4);
  local_8c[2] = 0;
  local_8c[1] = 0;
  local_8c[0] = uVar3;
  if (radix == 0) {
    cdb_num_bin(local_8c,(char *)&local_b0,0);
  }
  else if (radix == 1) {
    cdb_num_signed(local_8c,(char *)&local_b0,0);
  }
  else if (radix == 2) {
    if (cdb_arch == 0x2c6) {
      cdb_num_float(local_8c,(char *)&local_b0);
    }
    else {
      cdb_num_frac(local_8c + 3,local_8c,(char *)&local_b0,0);
    }
  }
  else if (radix == 3) {
    cdb_num_hex(local_8c,(char *)&local_b0,0);
  }
  else if (radix == 4) {
    cdb_num_unsigned(local_8c,(char *)&local_b0,0);
  }
  else {
    cdb_num_hex(local_8c,(char *)&local_b0,0);
  }
  cdb_out_append((char *)&local_b0);
  if ((local_60 == 2) || (local_60 == 0xc)) {
    local_64 = local_70;
    local_68 = local_74;
    local_54 = local_50;
    local_44 = 1;
    local_5c = 2;
    local_50 = local_4c;
    local_4c = local_48;
    local_48 = 1;
    cdb_out_append(&DAT_004d32d0);
    local_20 = 4;
    type_size(local_8c + 3,local_40);
    iVar6 = 0;
    while (iVar4 = cdb_load_memory(local_8c + 3), uVar3 = local_74, iVar4 != 0) {
      if ((local_74 == 0) || (0x400 < iVar6)) {
        cdb_out_append(&DAT_004d3298);
        return;
      }
      if (local_74 < 0x7f) {
        cVar2 = (char)local_74;
        if (__mb_cur_max < 2) {
          uVar5 = *(ushort *)(_pctype + (char)local_74 * 2) & 0x157;
        }
        else {
          uVar5 = _isctype((int)(char)local_74,0x157);
        }
        if (uVar5 == 0) {
          if (0x7e < uVar3) goto LAB_00460f62;
          switch(cVar2) {
          case '\a':
            local_b0 = DAT_004d32bc;
            local_ae = DAT_004d32be;
            break;
          case '\b':
            local_b0 = DAT_004d32b8;
            local_ae = DAT_004d32ba;
            break;
          case '\t':
            local_b0 = DAT_004d32a8;
            local_ae = DAT_004d32aa;
            break;
          case '\n':
            local_b0 = DAT_004d32b0;
            local_ae = DAT_004d32b2;
            break;
          case '\v':
            local_b0 = DAT_004d32a4;
            local_ae = DAT_004d32a6;
            break;
          case '\f':
            local_b0 = DAT_004d32b4;
            local_ae = DAT_004d32b6;
            break;
          case '\r':
            local_b0 = DAT_004d32ac;
            local_ae = DAT_004d32ae;
            break;
          default:
            fmt = &DAT_004d329c;
            goto override_prt_460f6d_623b4d9a;
          }
        }
        else if (cVar2 == '\"') {
          local_b0 = DAT_004d32c0;
          local_ae = DAT_004d32c2;
        }
        else if (cVar2 == '\'') {
          local_b0 = DAT_004d32c4;
          local_ae = DAT_004d32c6;
        }
        else {
          if (cVar2 != '\\') {
            uVar3 = (uint)cVar2;
            fmt = &DAT_004d32cc;
            goto override_prt_460f6d_623b4d9a;
          }
          local_b0 = DAT_004d32c8;
          local_ae = DAT_004d32ca;
        }
      }
      else {
LAB_00460f62:
        fmt = &DAT_004d329c;
override_prt_460f6d_623b4d9a:
        sprintf((char *)&local_b0,fmt,uVar3);
      }
      cdb_out_append((char *)&local_b0);
      local_68 = local_68 + local_34;
      iVar6 = iVar6 + 1;
    }
  }
  return;
}


/* ==== cdb_fmt_function @ 00460fd0 ==== */

void __cdecl cdb_fmt_function(void *v,int radix)

{
  char cVar1;
  undefined3 extraout_var;
  uint addr;
  uint local_30 [3];
  char local_24 [36];
  
  addr = *(uint *)((int)v + 0x18) & cdb_addr_mask;
  cVar1 = cdb_memspace_name(*(int *)((int)v + 0x1c),addr);
  cdb_out_append((char *)CONCAT31(extraout_var,cVar1));
  cdb_out_append(&DAT_004d32d4);
  local_30[2] = 0;
  local_30[1] = 0;
  local_30[0] = addr;
  if (radix == 0) {
    cdb_num_bin(local_30,local_24,0);
  }
  else if (radix == 1) {
    cdb_num_signed(local_30,local_24,0);
  }
  else if (radix == 2) {
    if (cdb_arch == 0x2c6) {
      cdb_num_float(local_30,local_24);
    }
    else {
      cdb_num_frac(v,local_30,local_24,0);
    }
  }
  else if (radix == 3) {
    cdb_num_hex(local_30,local_24,0);
  }
  else if (radix == 4) {
    cdb_num_unsigned(local_30,local_24,0);
  }
  else {
    cdb_num_hex(local_30,local_24,0);
  }
  cdb_out_append(local_24);
  return;
}


/* ==== cdb_fmt_array @ 004610f0 ==== */

void __cdecl cdb_fmt_array(void *v,int radix)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 local_80 [6];
  int local_68;
  uint local_60;
  int local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined1 local_40 [12];
  int local_34;
  undefined4 local_20;
  
  bVar1 = true;
  cdb_out_append(&DAT_004d32e0);
  puVar4 = local_80;
  for (iVar2 = 0x10; iVar3 = local_54, iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *(undefined4 *)v;
    v = (undefined4 *)((int)v + 4);
    puVar4 = puVar4 + 1;
  }
  local_60 = local_60 >> 2 & 0x3ffebff0 | local_60 & 0x1000f;
  local_54 = local_50;
  local_50 = local_4c;
  local_4c = local_48;
  local_48 = 1;
  local_20 = 4;
  type_size(local_80,local_40);
  if (0 < iVar3) {
    do {
      if (bVar1) {
        bVar1 = false;
      }
      else {
        cdb_out_append((char *)&DAT_004d32dc);
      }
      cdb_format_value(local_80,radix);
      local_68 = local_68 + local_34;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  cdb_out_append(&DAT_004d32d8);
  return;
}


/* ==== cdb_fmt_char @ 004611d0 ==== */

void __cdecl cdb_fmt_char(void *v,int radix)

{
  uint uVar1;
  char cVar2;
  char *fmt;
  uint local_30 [3];
  undefined4 local_24;
  undefined1 local_20;
  
  local_30[0] = *(uint *)((int)v + 0xc);
  local_30[2] = 0;
  local_30[1] = 0;
  if (radix == 0) {
    cdb_num_bin(local_30,(char *)&local_24,0);
    cdb_out_append((char *)&local_24);
    return;
  }
  if (radix == 1) {
    cdb_num_signed(local_30,(char *)&local_24,0);
    cdb_out_append((char *)&local_24);
    return;
  }
  if (radix == 2) {
    if (cdb_arch != 0x2c6) {
      cdb_num_frac(v,local_30,(char *)&local_24,0);
      cdb_out_append((char *)&local_24);
      return;
    }
    cdb_num_float(local_30,(char *)&local_24);
    cdb_out_append((char *)&local_24);
    return;
  }
  if (radix == 3) {
    cdb_num_hex(local_30,(char *)&local_24,0);
    cdb_out_append((char *)&local_24);
    return;
  }
  if (radix == 4) {
    cdb_num_unsigned(local_30,(char *)&local_24,0);
    cdb_out_append((char *)&local_24);
    return;
  }
  if (0x7e < local_30[0]) {
LAB_004614af:
    sprintf((char *)&local_24,s____lo__004d32e4,local_30[0]);
    cdb_out_append((char *)&local_24);
    return;
  }
  if (__mb_cur_max < 2) {
    uVar1 = *(ushort *)(_pctype + (char)local_30[0] * 2) & 0x157;
  }
  else {
    uVar1 = _isctype((int)(char)local_30[0],0x157);
  }
  cVar2 = (char)local_30[0];
  if (uVar1 == 0) {
    if (0x7e < local_30[0]) goto LAB_004614af;
    switch(cVar2) {
    case '\a':
      local_24 = DAT_004d331c;
      local_20 = DAT_004d3320;
      cdb_out_append((char *)&local_24);
      return;
    case '\b':
      local_20 = DAT_004d3318;
      local_24 = DAT_004d3314;
      cdb_out_append((char *)&local_24);
      return;
    case '\t':
      local_24 = DAT_004d32f4;
      local_20 = DAT_004d32f8;
      cdb_out_append((char *)&local_24);
      return;
    case '\n':
      local_24 = DAT_004d3304;
      local_20 = DAT_004d3308;
      cdb_out_append((char *)&local_24);
      return;
    case '\v':
      local_24 = DAT_004d32ec;
      local_20 = DAT_004d32f0;
      cdb_out_append((char *)&local_24);
      return;
    case '\f':
      local_24 = DAT_004d330c;
      local_20 = DAT_004d3310;
      cdb_out_append((char *)&local_24);
      return;
    case '\r':
      local_20 = DAT_004d3300;
      local_24 = DAT_004d32fc;
      cdb_out_append((char *)&local_24);
      return;
    default:
      fmt = s____lo__004d32e4;
      uVar1 = local_30[0];
    }
  }
  else {
    if (cVar2 == '\"') {
      local_24 = DAT_004d3324;
      local_20 = DAT_004d3328;
      cdb_out_append((char *)&local_24);
      return;
    }
    if (cVar2 == '\'') {
      local_20 = DAT_004d3330;
      local_24 = DAT_004d332c;
      cdb_out_append((char *)&local_24);
      return;
    }
    if (cVar2 == '\\') {
      local_24 = DAT_004d3334;
      local_20 = DAT_004d3338;
      cdb_out_append((char *)&local_24);
      return;
    }
    fmt = &DAT_004d333c;
    uVar1 = (int)cVar2;
  }
  sprintf((char *)&local_24,fmt,uVar1);
  cdb_out_append((char *)&local_24);
  return;
}


/* ==== cdb_fmt_short @ 00461550 ==== */

void __cdecl cdb_fmt_short(void *v,int radix)

{
  ulong local_30 [3];
  char local_24 [36];
  
  local_30[2] = 0;
  local_30[1] = 0;
  local_30[0] = *(ulong *)((int)v + 0xc);
  if (radix == 0) {
    cdb_num_bin(local_30,local_24,0);
    cdb_out_append(local_24);
    return;
  }
  if (radix != 1) {
    if (radix == 2) {
      if (cdb_arch != 0x2c6) {
        cdb_num_frac(v,local_30,local_24,0);
        cdb_out_append(local_24);
        return;
      }
      cdb_num_float(local_30,local_24);
      cdb_out_append(local_24);
      return;
    }
    if (radix == 3) {
      cdb_num_hex(local_30,local_24,0);
      cdb_out_append(local_24);
      return;
    }
    if (radix == 4) {
      cdb_num_unsigned(local_30,local_24,0);
      cdb_out_append(local_24);
      return;
    }
    if (*(int *)((int)v + 0x20) != 3) {
      cdb_num_unsigned(local_30,local_24,0);
      cdb_out_append(local_24);
      return;
    }
  }
  cdb_num_signed(local_30,local_24,0);
  cdb_out_append(local_24);
  return;
}


/* ==== cdb_fmt_int @ 004616a0 ==== */

void __cdecl cdb_fmt_int(void *v,int radix)

{
  char cVar1;
  undefined3 extraout_var;
  int iVar2;
  char *pcVar3;
  undefined3 extraout_var_01;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  uint uVar7;
  ulong local_90;
  undefined4 local_8c;
  undefined4 local_88;
  char local_84 [128];
  undefined1 local_4;
  undefined3 extraout_var_00;
  
  local_90 = *(ulong *)((int)v + 0xc);
  local_88 = 0;
  local_8c = 0;
  if (cdb_arch == 0x2cb) {
    local_8c = *(undefined4 *)((int)v + 0x10);
  }
  if (radix == 0) {
    cdb_num_bin(&local_90,local_84,0);
    goto LAB_004618a2;
  }
  if (radix == 1) {
LAB_004617a6:
    cdb_num_signed(&local_90,local_84,0);
  }
  else {
    if (radix == 2) {
      if (cdb_arch == 0x2c6) {
        cdb_num_float(&local_90,local_84);
        goto LAB_004618a2;
      }
    }
    else {
      if (radix == 3) {
        cdb_num_hex(&local_90,local_84,0);
        goto LAB_004618a2;
      }
      if (radix == 4) {
        cdb_num_unsigned(&local_90,local_84,0);
        goto LAB_004618a2;
      }
      iVar2 = *(int *)((int)v + 0x20);
      if (iVar2 == 0xb) {
        uVar7 = 0x80;
        cVar1 = cdb_sym_name(*(int *)((int)v + 0x28));
        strncpy(local_84,(char *)CONCAT31(extraout_var,cVar1),uVar7);
        local_4 = 0;
        goto LAB_004618a2;
      }
      if (iVar2 == 10) {
        if (cdb_arch == 0x2cb) {
          iVar2 = -1;
        }
        else {
          iVar2 = cdb_enum_member_by_value(*(int *)((int)v + 0x28),local_90);
        }
        if (iVar2 != -1) {
          if (cdb_arch == 0x2cb) {
            cVar1 = cdb_sym_name(iVar2);
            pcVar3 = (char *)CONCAT31(extraout_var_00,cVar1);
            if (pcVar3 != (char *)0x0) {
              uVar7 = 0xffffffff;
              pcVar5 = pcVar3;
              do {
                pcVar6 = pcVar5;
                if (uVar7 == 0) break;
                uVar7 = uVar7 - 1;
                pcVar6 = pcVar5 + 1;
                cVar1 = *pcVar5;
                pcVar5 = pcVar6;
              } while (cVar1 != '\0');
              uVar7 = ~uVar7;
              pcVar5 = pcVar6 + -uVar7;
              pcVar6 = local_84;
              for (uVar4 = uVar7 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                pcVar5 = pcVar5 + 4;
                pcVar6 = pcVar6 + 4;
              }
              for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                *pcVar6 = *pcVar5;
                pcVar5 = pcVar5 + 1;
                pcVar6 = pcVar6 + 1;
              }
            }
            cdb_free(pcVar3);
          }
          else {
            cVar1 = cdb_sym_name(iVar2);
            uVar7 = 0xffffffff;
            pcVar3 = (char *)CONCAT31(extraout_var_01,cVar1);
            do {
              pcVar5 = pcVar3;
              if (uVar7 == 0) break;
              uVar7 = uVar7 - 1;
              pcVar5 = pcVar3 + 1;
              cVar1 = *pcVar3;
              pcVar3 = pcVar5;
            } while (cVar1 != '\0');
            uVar7 = ~uVar7;
            pcVar3 = pcVar5 + -uVar7;
            pcVar5 = local_84;
            for (uVar4 = uVar7 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
              *(undefined4 *)pcVar5 = *(undefined4 *)pcVar3;
              pcVar3 = pcVar3 + 4;
              pcVar5 = pcVar5 + 4;
            }
            for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
              *pcVar5 = *pcVar3;
              pcVar3 = pcVar3 + 1;
              pcVar5 = pcVar5 + 1;
            }
          }
          goto LAB_004618a2;
        }
        goto LAB_004617a6;
      }
      if (iVar2 == 4) {
        cdb_num_signed(&local_90,local_84,0);
        goto LAB_004618a2;
      }
      if ((iVar2 != 0x10000) && (iVar2 != 0x10001)) {
        cdb_num_unsigned(&local_90,local_84,0);
        goto LAB_004618a2;
      }
    }
    cdb_num_frac(v,&local_90,local_84,0);
  }
LAB_004618a2:
  cdb_out_append(local_84);
  return;
}


/* ==== cdb_fmt_long @ 004618c0 ==== */

void __cdecl cdb_fmt_long(void *v,int radix)

{
  int iVar1;
  uint nwords;
  ulong local_40;
  undefined4 local_3c;
  undefined4 local_38;
  char local_34 [52];
  
  local_38 = 0;
  if (cdb_arch != 0x2c6) {
    local_3c = *(undefined4 *)((int)v + 0x10);
  }
  else {
    local_3c = 0;
  }
  nwords = (uint)(cdb_arch != 0x2c6);
  local_40 = *(ulong *)((int)v + 0xc);
  if (radix == 0) {
    cdb_num_bin(&local_40,local_34,nwords);
    goto LAB_004619d3;
  }
  if (radix == 1) {
LAB_00461954:
    cdb_num_signed(&local_40,local_34,nwords);
  }
  else {
    if (radix == 2) {
      if (cdb_arch == 0x2c6) {
        cdb_num_float(&local_40,local_34);
        goto LAB_004619d3;
      }
LAB_004619ca:
      cdb_num_frac(v,&local_40,local_34,nwords);
      goto LAB_004619d3;
    }
    if (radix == 3) {
      cdb_num_hex(&local_40,local_34,nwords);
      goto LAB_004619d3;
    }
    if (radix != 4) {
      iVar1 = *(int *)((int)v + 0x20);
      if (iVar1 == 5) goto LAB_00461954;
      if (((iVar1 == 0x10002) || (iVar1 == 0x10003)) || (iVar1 == 0x10004)) goto LAB_004619ca;
    }
    cdb_num_unsigned(&local_40,local_34,nwords);
  }
LAB_004619d3:
  cdb_out_append(local_34);
  return;
}


/* ==== cdb_fmt_accum @ 004619f0 ==== */

void __cdecl cdb_fmt_accum(void *v,int radix)

{
  ulong local_40;
  undefined4 local_3c;
  undefined4 local_38;
  char local_34 [52];
  
  local_38 = 0;
  local_3c = *(undefined4 *)((int)v + 0x10);
  local_40 = *(ulong *)((int)v + 0xc);
  if (radix == 0) {
    cdb_num_bin(&local_40,local_34,1);
    cdb_out_append(local_34);
    return;
  }
  if (radix == 1) {
    cdb_num_signed(&local_40,local_34,1);
    cdb_out_append(local_34);
    return;
  }
  if (radix != 2) {
    if (radix == 3) {
      cdb_num_hex(&local_40,local_34,1);
      cdb_out_append(local_34);
      return;
    }
    if (radix == 4) {
      cdb_num_unsigned(&local_40,local_34,1);
      cdb_out_append(local_34);
      return;
    }
  }
  cdb_num_frac(v,&local_40,local_34,1);
  cdb_out_append(local_34);
  return;
}


/* ==== cdb_fmt_long_accum @ 00461af0 ==== */

void __cdecl cdb_fmt_long_accum(void *v,int radix)

{
  ulong local_40;
  undefined4 local_3c;
  undefined4 local_38;
  char local_34 [52];
  
  local_38 = *(undefined4 *)((int)v + 0x14);
  local_3c = *(undefined4 *)((int)v + 0x10);
  local_40 = *(ulong *)((int)v + 0xc);
  if (radix == 0) {
    cdb_num_bin(&local_40,local_34,2);
    cdb_out_append(local_34);
    return;
  }
  if (radix == 1) {
    cdb_num_signed(&local_40,local_34,2);
    cdb_out_append(local_34);
    return;
  }
  if (radix != 2) {
    if (radix == 3) {
      cdb_num_hex(&local_40,local_34,2);
      cdb_out_append(local_34);
      return;
    }
    if (radix == 4) {
      cdb_num_unsigned(&local_40,local_34,2);
      cdb_out_append(local_34);
      return;
    }
  }
  cdb_num_frac(v,&local_40,local_34,2);
  cdb_out_append(local_34);
  return;
}


/* ==== cdb_fmt_float @ 00461bf0 ==== */

void __cdecl cdb_fmt_float(void *v,int radix)

{
  int nwords;
  uint local_40;
  uint local_3c;
  undefined4 local_38;
  char local_34 [52];
  
  nwords = 0;
  local_38 = 0;
  if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cc)) ||
     ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))) {
    local_3c = (uint)*(ushort *)((int)v + 10);
    local_40 = (uint)*(ushort *)((int)v + 8);
  }
  else {
    if ((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) {
      local_40 = *(uint *)((int)v + 8);
      goto LAB_00461c86;
    }
    local_3c = *(uint *)((int)v + 0xc);
    local_40 = *(uint *)((int)v + 0x10);
  }
  local_3c = local_3c & cdb_word_mask;
  local_40 = local_40 & cdb_word_mask;
  nwords = 1;
LAB_00461c86:
  if (radix == 0) {
    cdb_num_bin(&local_40,local_34,nwords);
  }
  else if (radix == 1) {
    cdb_num_signed(&local_40,local_34,nwords);
  }
  else if (radix == 2) {
    if (cdb_arch == 0x2c6) {
      cdb_num_float(&local_40,local_34);
    }
    else {
      cdb_num_frac(v,&local_40,local_34,nwords);
    }
  }
  else if (radix == 3) {
    cdb_num_hex(&local_40,local_34,nwords);
  }
  else if (radix == 4) {
    cdb_num_unsigned(&local_40,local_34,nwords);
  }
  else {
    cdb_num_float(&local_40,local_34);
  }
  cdb_out_append(local_34);
  return;
}


/* ==== cdb_fmt_double @ 00461d50 ==== */

void __cdecl cdb_fmt_double(void *v,int radix)

{
  uint local_50;
  uint local_4c;
  undefined4 local_48;
  char local_44 [68];
  
  local_48 = 0;
  if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2cc)) || (cdb_arch == 0x2c9)) ||
     ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))) {
    local_4c = (uint)*(ushort *)((int)v + 10);
    local_50 = (uint)*(ushort *)((int)v + 8);
  }
  else {
    if ((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) {
      local_4c = *(uint *)((int)v + 4);
      local_50 = *(uint *)v;
      goto LAB_00461de9;
    }
    local_4c = *(uint *)((int)v + 0xc);
    local_50 = *(uint *)((int)v + 0x10);
  }
  local_4c = local_4c & cdb_word_mask;
  local_50 = local_50 & cdb_word_mask;
LAB_00461de9:
  if (radix == 0) {
    cdb_num_bin(&local_50,local_44,1);
  }
  else if (radix == 1) {
    cdb_num_signed(&local_50,local_44,1);
  }
  else if (radix == 2) {
    if (cdb_arch == 0x2c6) {
      cdb_num_double(&local_50,local_44);
    }
    else {
      cdb_num_frac(v,&local_50,local_44,1);
    }
  }
  else if (radix == 3) {
    cdb_num_hex(&local_50,local_44,1);
  }
  else if (radix == 4) {
    cdb_num_unsigned(&local_50,local_44,1);
  }
  else {
    cdb_num_double(&local_50,local_44);
  }
  cdb_out_append(local_44);
  return;
}


/* ==== cdb_fmt_struct @ 00461ec0 ==== */

void __cdecl cdb_fmt_struct(void *v,int radix)

{
  bool bVar1;
  char cVar2;
  int sym;
  undefined3 extraout_var;
  int iVar3;
  char *va0;
  char local_68 [40];
  undefined1 local_40 [24];
  uint local_28;
  undefined4 local_20;
  int local_1c;
  int local_18;
  
  bVar1 = true;
  cdb_out_append(&DAT_004d32e0);
  sym = *(int *)((int)v + 0x28);
  if (sym == 0) {
    va0 = s_structure_004d3198;
    if (*(int *)((int)v + 0x20) != 8) {
      va0 = s_union_004d31ac;
    }
    sprintf(local_68,s_<_s_contents_not_available>_004d3344,va0);
    cdb_out_append(local_68);
  }
  else {
    do {
      sym = cdb_next_member(sym);
      if (sym == -1) break;
      if (bVar1) {
        bVar1 = false;
      }
      else {
        cdb_out_append((char *)&DAT_004d32dc);
      }
      cdb_sym_to_value(local_40,sym);
      if (local_1c == 0x12) {
        local_28 = 0;
        local_18 = sym;
      }
      local_28 = local_28 + *(int *)((int)v + 0xc) & cdb_addr_mask;
      cVar2 = cdb_sym_name(sym);
      cdb_out_append((char *)CONCAT31(extraout_var,cVar2));
      cdb_out_append((char *)&DAT_004d3360);
      if ((((byte)local_20 & 0x30) != 0x30) && (iVar3 = cdb_load_memory(local_40), iVar3 == 0)) {
        return;
      }
      cdb_format_value(local_40,radix);
    } while (sym != 0);
  }
  cdb_out_append(&DAT_004d32d8);
  return;
}


/* ==== cdb_fmt_union @ 00461ff0 ==== */

void __cdecl cdb_fmt_union(void *v,int radix)

{
  cdb_fmt_struct(v,radix);
  return;
}


/* ==== cdb_num_signed @ 00462010 ==== */

void __cdecl cdb_num_signed(ulong *w,char *out,int nwords)

{
  uint va0;
  
  if (((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) && (nwords == 1)) {
    cdb_num_dec_wide_signed(w,out,1,1);
    return;
  }
  if ((cdb_arch == 0x2c6) && (nwords == 1)) {
    cdb_num_dec_wide_signed32(w,out,1,1);
    return;
  }
  if (cdb_arch == 0x2cb) {
    va0 = *w | w[1] << 0x10;
    *w = va0;
    sprintf(out,&DAT_004d3364,va0);
    return;
  }
  if (((cdb_arch == 0x2c7) || (cdb_arch == 0x2cc)) || ((cdb_arch == 0x2c9 || (cdb_arch == 0x2ca))))
  {
    if (nwords == 0) {
      if ((*w & cdb_sign_bit) != 0) {
        *w = *w | 0xffff0000;
      }
    }
    else {
      *w = *w | w[1] << 0x10;
    }
  }
  else if (((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) && ((*w & cdb_sign_bit) != 0)) {
    *w = *w | 0xff000000;
  }
  sprintf(out,&DAT_004d3364,*w);
  return;
}


/* ==== cdb_num_dec_wide_signed @ 00462110 ==== */

void __cdecl cdb_num_dec_wide_signed(ulong *w,char *out,int nwords,int is_signed)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  uint local_48;
  uint local_44;
  undefined4 local_40;
  ulong local_3c;
  uint local_38;
  undefined4 local_34;
  ulong local_30 [3];
  char local_24 [11];
  char acStack_19 [25];
  
  local_44 = w[1];
  local_48 = *w;
  iVar3 = 0;
  bVar1 = false;
  local_40 = 0;
  local_30[2] = 0;
  local_30[1] = 0;
  local_30[0] = 10;
  if (((is_signed != 0) && (nwords == 1)) && ((cdb_sign_bit & local_44) != 0)) {
    uVar2 = (~local_48 & cdb_word_mask) + 1;
    local_48 = uVar2 & cdb_word_mask;
    local_44 = (uVar2 >> ((byte)cdb_word_bits & 0x1f)) + (~local_44 & cdb_word_mask) & cdb_word_mask
    ;
    bVar1 = true;
  }
  local_3c = 1;
  local_38 = 0;
  while ((local_38 != 0 || (local_3c != 0))) {
    dw_udivmod(&local_48,local_30,&local_3c,(ulong *)local_24);
    local_44 = local_38;
    local_40 = local_34;
    acStack_19[iVar3 + 1] = local_24[0] + '0';
    local_48 = local_3c;
    iVar3 = iVar3 + 1;
  }
  if (bVar1) {
    *out = '-';
  }
  uVar2 = (uint)bVar1;
  for (; iVar3 != 0; iVar3 = iVar3 + -1) {
    out[uVar2] = acStack_19[iVar3];
    uVar2 = uVar2 + 1;
  }
  out[uVar2] = '\0';
  return;
}


/* ==== cdb_num_dec_wide_signed32 @ 00462220 ==== */

void __cdecl cdb_num_dec_wide_signed32(ulong *w,char *out,int nwords,int is_signed)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint local_48;
  uint local_44;
  undefined4 local_40;
  ulong local_3c;
  uint local_38;
  undefined4 local_34;
  ulong local_30 [3];
  char local_24 [11];
  char acStack_19 [25];
  
  local_44 = w[1];
  local_48 = *w;
  iVar4 = 0;
  bVar1 = false;
  local_40 = 0;
  local_30[2] = 0;
  local_30[1] = 0;
  local_30[0] = 10;
  if (((is_signed != 0) && (nwords == 1)) && ((cdb_sign_bit & local_44) != 0)) {
    bVar1 = true;
    uVar2 = ~local_48;
    uVar3 = (uVar2 & cdb_word_mask) + 1;
    local_48 = uVar3 & cdb_word_mask;
    local_44 = (~local_44 & cdb_word_mask) + (uint)(uVar3 < (uVar2 & cdb_word_mask)) & cdb_word_mask
    ;
  }
  local_3c = 1;
  local_38 = 0;
  while ((local_38 != 0 || (local_3c != 0))) {
    dw_udivmod_b(&local_48,local_30,&local_3c,(ulong *)local_24);
    local_44 = local_38;
    local_40 = local_34;
    acStack_19[iVar4 + 1] = local_24[0] + '0';
    local_48 = local_3c;
    iVar4 = iVar4 + 1;
  }
  if (bVar1) {
    *out = '-';
  }
  uVar2 = (uint)bVar1;
  for (; iVar4 != 0; iVar4 = iVar4 + -1) {
    out[uVar2] = acStack_19[iVar4];
    uVar2 = uVar2 + 1;
  }
  out[uVar2] = '\0';
  return;
}


/* ==== cdb_num_unsigned @ 00462320 ==== */

void __cdecl cdb_num_unsigned(ulong *w,char *out,int nwords)

{
  if (((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) && (nwords == 1)) {
    cdb_num_dec_wide_signed(w,out,1,0);
    return;
  }
  if ((cdb_arch == 0x2c6) && (nwords == 1)) {
    cdb_num_dec_wide_signed32(w,out,1,0);
    return;
  }
  if (((((cdb_arch == 0x2c7) || ((cdb_arch == 0x2cc || (cdb_arch == 0x2c9)))) || (cdb_arch == 0x2cb)
       ) || (cdb_arch == 0x2ca)) && ((nwords == 1 || (cdb_arch == 0x2cb)))) {
    *w = *w | w[1] << 0x10;
  }
  sprintf(out,&DAT_004d3368,*w);
  return;
}


/* ==== cdb_num_float @ 004623d0 ==== */

void __cdecl cdb_num_float(void *w,char *out)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  double local_40;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_20;
  undefined2 local_4;
  
  if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2cc)) || (cdb_arch == 0x2c9)) ||
     ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))) {
    w = (void *)(*(uint *)w & cdb_word_mask | *(int *)((int)w + 4) << 0x10);
  }
  else if ((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) {
    local_20 = 6;
    local_34 = *(undefined4 *)((int)w + 4);
    local_30 = *(undefined4 *)w;
    local_4 = 0;
    value_dsp_to_double(&local_40);
    w = (void *)(float)local_40;
  }
  else {
    w = *(void **)w;
  }
  sprintf(out,s___15e_004d336c,(double)(float)w);
  uVar2 = 0xffffffff;
  pcVar3 = out;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  if (out[uVar2 - 4] == '0') {
    out[uVar2 - 4] = out[uVar2 - 3];
    out[uVar2 - 3] = out[uVar2 - 2];
    out[uVar2 - 2] = out[uVar2 - 1];
  }
  return;
}


/* ==== cdb_num_double @ 004624c0 ==== */

void __cdecl cdb_num_double(void *w,char *out)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  undefined8 local_48;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_20;
  undefined2 local_4;
  
  if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2cc)) || (cdb_arch == 0x2c9)) ||
     ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))) {
    w = (void *)CONCAT22(*(undefined2 *)((int)w + 4),*(undefined2 *)w);
    local_48 = (double)(float)w;
  }
  else if ((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) {
    local_20 = 7;
    local_4 = 0;
    local_34 = *(undefined4 *)((int)w + 4);
    local_30 = *(undefined4 *)w;
    value_dsp_to_double(&local_40);
    local_48 = (double)CONCAT44(local_3c,local_40);
  }
  else {
    local_48 = *(double *)w;
  }
  sprintf(out,s___15e_004d336c,(undefined4)local_48,local_48._4_4_);
  uVar2 = 0xffffffff;
  pcVar3 = out;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  if (out[uVar2 - 4] == '0') {
    out[uVar2 - 4] = out[uVar2 - 3];
    out[uVar2 - 3] = out[uVar2 - 2];
    out[uVar2 - 2] = out[uVar2 - 1];
  }
  return;
}


/* ==== cdb_num_hex @ 004625c0 ==== */

void __cdecl cdb_num_hex(void *w,char *out,int nwords)

{
  char *fmt;
  char *fmt_00;
  
  if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2cc)) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2ca))
  {
    fmt_00 = s_0x_lx_04lx_004d33a8;
    fmt = s_0x_lx_04lx_04lx_004d3398;
  }
  else if ((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) {
    fmt_00 = s_0x_lx_06lx_004d338c;
    fmt = s_0x_lx_06lx_06lx_004d337c;
  }
  else if (cdb_arch == 0x2c6) {
    fmt_00 = s_0x_lx_08lx_004d33c4;
    fmt = s_0x_lx_08lx_08lx_004d33b4;
  }
  else {
    fmt_00 = s_0x_lx_04lx_004d33a8;
    fmt = s_0x_lx_04lx_04lx_004d3398;
    if (cdb_arch == 0x2cb) {
      nwords = 1;
    }
  }
  if ((1 < nwords) && (*(int *)((int)w + 8) != 0)) {
    sprintf(out,fmt,*(int *)((int)w + 8),*(undefined4 *)((int)w + 4),*(undefined4 *)w);
    return;
  }
  if ((0 < nwords) && (*(int *)((int)w + 4) != 0)) {
    sprintf(out,fmt_00,*(int *)((int)w + 4),*(undefined4 *)w);
    return;
  }
  sprintf(out,s_0x_lx_004d3374,*(undefined4 *)w);
  return;
}


/* ==== cdb_num_bin @ 004626a0 ==== */

void __cdecl cdb_num_bin(void *w,char *out,int nwords)

{
  char cVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  char *pcVar12;
  char *pcVar13;
  
  bVar3 = true;
  uVar11 = cdb_word_bits >> 2;
  bVar4 = false;
  iVar8 = 1;
  if (cdb_arch != 0x2cb) {
    iVar8 = nwords;
  }
  if (-1 < iVar8) {
    puVar5 = (uint *)((int)w + iVar8 * 4);
    do {
      uVar2 = *puVar5;
      if (((uVar2 != 0) || (!bVar3)) || (iVar8 == 0)) {
        iVar10 = 0;
        if (uVar11 != 0) {
          iVar9 = uVar11 * 4;
          do {
            uVar6 = uVar2 >> ((char)iVar9 - 4U & 0x1f) & 0xf;
            if ((((short)uVar6 != 0) || (bVar4)) || (iVar10 == uVar11 - 1)) {
              uVar7 = 0xffffffff;
              bVar4 = true;
              pcVar12 = (&cdb_hexdigit_tab)[uVar6];
              do {
                pcVar13 = pcVar12;
                if (uVar7 == 0) break;
                uVar7 = uVar7 - 1;
                pcVar13 = pcVar12 + 1;
                cVar1 = *pcVar12;
                pcVar12 = pcVar13;
              } while (cVar1 != '\0');
              uVar7 = ~uVar7;
              pcVar12 = pcVar13 + -uVar7;
              pcVar13 = out;
              for (uVar6 = uVar7 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                *(undefined4 *)pcVar13 = *(undefined4 *)pcVar12;
                pcVar12 = pcVar12 + 4;
                pcVar13 = pcVar13 + 4;
              }
              out = out + 4;
              for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                *pcVar13 = *pcVar12;
                pcVar12 = pcVar12 + 1;
                pcVar13 = pcVar13 + 1;
              }
            }
            iVar10 = iVar10 + 1;
            iVar9 = iVar9 + -4;
          } while (iVar10 < (int)uVar11);
        }
        bVar3 = false;
      }
      iVar8 = iVar8 + -1;
      puVar5 = puVar5 + -1;
    } while (-1 < iVar8);
  }
  return;
}


/* ==== cdb_num_frac @ 004627a0 ==== */

void __cdecl cdb_num_frac(void *v,ulong *w,char *out,int nwords)

{
  int iVar1;
  undefined4 local_14;
  undefined4 local_10;
  ulong local_c;
  ulong local_8;
  ulong local_4;
  
  local_c = *w;
  local_8 = w[1];
  local_4 = w[2];
  iVar1 = *(int *)((int)v + 0x20);
  if (iVar1 == 0x10000) {
LAB_0046280b:
    cdb_frac1_to_double(local_c,(double *)&local_14);
  }
  else {
    if ((((iVar1 == 0x10001) || (iVar1 == 0x10003)) || (iVar1 == 0x10002)) ||
       ((iVar1 == 0x10004 || (iVar1 == 0x10005)))) {
      if (iVar1 == 0x10000) goto LAB_0046280b;
      if (iVar1 != 0x10002) {
        if (iVar1 == 0x10001) {
          cdb_frac_to_double_a(&local_c,(double *)&local_14);
        }
        else if (iVar1 == 0x10003) {
          cdb_frac_to_double_b(&local_c,(double *)&local_14);
        }
        else if (iVar1 == 0x10005) {
          cdb_frac_to_double(&local_c,(double *)&local_14);
        }
        else if (iVar1 == 0x10004) {
          cdb_frac_to_double_c(&local_c,(double *)&local_14);
        }
        goto LAB_00462891;
      }
    }
    else if (nwords == 0) {
      cdb_frac1_to_double(local_c,(double *)&local_14);
      goto LAB_00462891;
    }
    cdb_frac2_to_double(local_8,local_c,(double *)&local_14);
  }
LAB_00462891:
  sprintf(out,s___15f_004d33d0,local_14,local_10);
  return;
}


/* ==== cdb_frac_to_double @ 004628c0 ==== */

void __cdecl cdb_frac_to_double(ulong *w,double *out)

{
  double dVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar2 = w[2] & cdb_ext_mask;
  uVar3 = cdb_word_mask << 8 | cdb_word_mask;
  uVar5 = *w & cdb_word_mask;
  dVar1 = (double)(-cdb_ext_mask - 1);
  if (((uVar2 != cdb_ext_sign_bit) || ((w[1] & cdb_word_mask) != 0)) || (uVar5 != 0)) {
    uVar4 = w[1] & cdb_word_mask | uVar2 << ((byte)cdb_word_bits & 0x1f);
    if ((cdb_ext_sign_bit & uVar2) == 0) {
      uVar5 = uVar5 & cdb_word_mask;
    }
    else {
      if (cdb_ext_mask == 0xf) {
        uVar4 = uVar4 | 0xf00000;
      }
      if (uVar5 == 0) {
        uVar4 = (~uVar4 & uVar3) + 1;
        uVar5 = 0;
      }
      else {
        uVar4 = ~uVar4 & uVar3;
        uVar5 = (~uVar5 & cdb_word_mask) + 1;
      }
    }
    dVar1 = (double)uVar4 / (double)cdb_sign_bit +
            (double)uVar5 / ((double)(cdb_word_mask + 1) * (double)cdb_sign_bit);
    if ((cdb_ext_sign_bit & uVar2) != 0) {
      dVar1 = -dVar1;
    }
  }
  *out = dVar1;
  return;
}


/* ==== cdb_frac_to_double_a @ 004629d0 ==== */

void __cdecl cdb_frac_to_double_a(ulong *w,double *out)

{
  w[2] = 0;
  w[1] = *w;
  *w = 0;
  cdb_frac_to_double(w,out);
  return;
}


/* ==== cdb_frac_to_double_b @ 00462a00 ==== */

void __cdecl cdb_frac_to_double_b(ulong *w,double *out)

{
  w[2] = 0;
  cdb_frac_to_double(w,out);
  return;
}


/* ==== cdb_frac_to_double_c @ 00462a20 ==== */

void __cdecl cdb_frac_to_double_c(ulong *w,double *out)

{
  w[2] = w[1];
  w[1] = *w;
  *w = 0;
  cdb_frac_to_double(w,out);
  return;
}


/* ==== cdb_load_auto @ 00462a50 ==== */

int __cdecl cdb_load_auto(void *v)

{
  int offset;
  int sclass;
  void *v_00;
  int iVar1;
  int local_4;
  
  v_00 = v;
  offset = *(int *)((int)v + 0x18);
  sclass = *(int *)((int)v + 0x1c);
  iVar1 = cdb_frame_slot(sclass,offset,&local_4,(ulong *)&v);
  if (iVar1 == 0) {
    return 0;
  }
  *(void **)((int)v_00 + 0x18) = v;
  *(int *)((int)v_00 + 0x1c) = local_4;
  iVar1 = cdb_load_memory(v_00);
  if (iVar1 == 0) {
    return 0;
  }
  *(int *)((int)v_00 + 0x18) = offset;
  *(int *)((int)v_00 + 0x1c) = sclass;
  return 1;
}


/* ==== cdb_store_auto @ 00462ab0 ==== */

int __cdecl cdb_store_auto(void *v)

{
  int offset;
  int sclass;
  void *v_00;
  int iVar1;
  int local_4;
  
  v_00 = v;
  offset = *(int *)((int)v + 0x18);
  sclass = *(int *)((int)v + 0x1c);
  iVar1 = cdb_frame_slot(sclass,offset,&local_4,(ulong *)&v);
  if (iVar1 == 0) {
    return 0;
  }
  *(void **)((int)v_00 + 0x18) = v;
  *(int *)((int)v_00 + 0x1c) = local_4;
  iVar1 = cdb_store_memory(v_00);
  if (iVar1 == 0) {
    return 0;
  }
  *(int *)((int)v_00 + 0x18) = offset;
  *(int *)((int)v_00 + 0x1c) = sclass;
  return 1;
}


/* ==== cdb_load_memory @ 00462b10 ==== */

int __cdecl cdb_load_memory(void *v)

{
  uint *puVar1;
  uint *c;
  ulonglong uVar2;
  long lVar3;
  uint uVar4;
  int iVar5;
  byte bVar6;
  int iVar7;
  uint uVar8;
  uint a;
  uint *c_00;
  uint local_4c;
  uint local_48;
  uint local_44;
  undefined1 local_40 [24];
  uint local_28;
  uint local_14;
  
  iVar5 = *(int *)(cur_dev + 4);
  puVar1 = (uint *)((int)v + 0x14);
  uVar4 = *(uint *)((int)v + 0x18);
  a = *(uint *)((int)v + 0x1c);
  *puVar1 = 0;
  iVar7 = *(int *)((int)v + 0x20);
  c_00 = (uint *)((int)v + 0xc);
  c = (uint *)((int)v + 0x10);
  *c_00 = 0;
  *c = 0;
  if (((byte)iVar7 & 0x30) == 0x10) {
    if (cdb_arch != 0x2cb) {
      lVar3 = dev_mem_read(iVar5,a,uVar4,(long)c_00);
      if (lVar3 == 0) {
        cdb_c_error(s_unable_to_read_memory_004d33d8);
        return 0;
      }
      uVar4 = cdb_default_space();
      *c = uVar4;
      return 1;
    }
    lVar3 = dev_call_slot12(iVar5,a,uVar4,(long)c_00);
    if (lVar3 == 0) {
      cdb_c_error(s_unable_to_read_memory_004d33d8);
      return 0;
    }
    *c = 0;
    return 1;
  }
  if (*(int *)((int)v + 0x24) == 0x12) {
    if (a == 3) {
      a = 2;
    }
    cdb_sym_to_value(local_40,*(int *)((int)v + 0x28));
    iVar7 = uVar4 + local_28 / cdb_word_bits;
    uVar2 = (ulonglong)cdb_word_bits;
    lVar3 = dev_mem_read(iVar5,a,iVar7,(long)&local_4c);
    if (lVar3 == 0) {
      cdb_c_error(s_unable_to_read_memory_004d33d8);
      return 0;
    }
    *c = local_48;
    *c_00 = local_4c;
    *puVar1 = local_44;
    uVar4 = local_14 + (int)((ulonglong)local_28 % uVar2);
    bVar6 = (byte)((ulonglong)local_28 % uVar2);
    if (cdb_word_bits < uVar4) {
      lVar3 = dev_mem_read(iVar5,a,iVar7 + 1,(long)&local_48);
      if (lVar3 == 0) {
        cdb_c_error(s_unable_to_read_memory_004d33d8);
        return 0;
      }
      *c = local_48;
      uVar8 = *c_00 >> (bVar6 & 0x1f);
      *c_00 = uVar8;
      uVar8 = local_48 << ((char)cdb_word_bits - bVar6 & 0x1f) | uVar8;
      *c_00 = uVar8;
      if (cdb_word_bits * 2 < uVar4) {
        lVar3 = dev_mem_read(iVar5,a,iVar7 + 2,(long)&local_4c);
        if (lVar3 == 0) {
          cdb_c_error(s_unable_to_read_memory_004d33d8);
          return 0;
        }
        uVar4 = *c >> (bVar6 & 0x1f);
        *c = uVar4;
        uVar4 = local_4c << ((char)cdb_word_bits - bVar6 & 0x1f) | uVar4;
        *c = uVar4;
        *c = *(uint *)(&cdb_bitmask_tab + (local_14 - cdb_word_bits) * 4) & uVar4;
      }
      else if (local_14 < cdb_word_bits) {
        uVar4 = *(uint *)(&cdb_bitmask_tab + local_14 * 4);
        *c = 0;
        *c_00 = uVar4 & uVar8;
      }
      else {
        *c_00 = cdb_word_mask & uVar8;
        uVar4 = *c >> (bVar6 & 0x1f);
        *c = uVar4;
        *c = *(uint *)(&cdb_bitmask_tab + (local_14 - cdb_word_bits) * 4) & uVar4;
      }
    }
    else {
      local_4c = local_4c >> (bVar6 & 0x1f);
      *c_00 = local_4c;
      uVar4 = *(uint *)(&cdb_bitmask_tab + local_14 * 4);
      *c = 0;
      *c_00 = uVar4 & local_4c;
    }
    if (cdb_word_bits < local_14) {
      if (*(int *)((int)v + 0x20) != 5) {
        return 1;
      }
      if (*c >> ((char)(local_14 - cdb_word_bits) - 1U & 0x1f) == 0) {
        return 1;
      }
      uVar4 = ~*(uint *)(&cdb_bitmask_tab + (local_14 - cdb_word_bits) * 4) | *c;
      *c = uVar4;
      *c = cdb_word_mask & uVar4;
      return 1;
    }
    iVar5 = *(int *)((int)v + 0x20);
    if ((((iVar5 != 2) && (iVar5 != 3)) && (iVar5 != 4)) &&
       (((iVar5 != 0xb && (iVar5 != 10)) && (iVar5 != 5)))) {
      return 1;
    }
    if (*c_00 >> ((char)local_14 - 1U & 0x1f) == 0) {
      return 1;
    }
    uVar4 = ~*(uint *)(&cdb_bitmask_tab + local_14 * 4) | *c_00;
    *c_00 = uVar4;
    *c_00 = cdb_word_mask & uVar4;
    return 1;
  }
  if ((((iVar7 == 2) || (iVar7 == 3)) ||
      ((((iVar7 == 4 || (((iVar7 == 0xb || (iVar7 == 10)) || (iVar7 == 5)))) ||
        ((iVar7 == 0xc || (iVar7 == 0xd)))) || (iVar7 == 0xe)))) || (iVar7 == 0xf)) {
    if (cdb_arch == 0x2cb) {
      if ((iVar7 != 2) && (iVar7 != 0xc)) {
        lVar3 = dev_call_slot11(iVar5,a,uVar4,(long)c_00);
        if (lVar3 == 0) {
          cdb_c_error(s_unable_to_read_memory_004d33d8);
          return 0;
        }
        iVar5 = dev_call_slot11(iVar5,a,uVar4 + 2,(long)c);
        goto LAB_00463451;
      }
    }
    else {
      lVar3 = dev_mem_read(iVar5,a,uVar4,(long)c_00);
      if (lVar3 == 0) {
        cdb_c_error(s_unable_to_read_memory_004d33d8);
        return 0;
      }
      if ((*(int *)((int)v + 0x20) != 5) && (*(int *)((int)v + 0x20) != 0xf)) {
        return 1;
      }
      if (((cdb_arch != 0x2c7) && (cdb_arch != 0x2c9)) && (cdb_arch != 0x2cc)) {
        if (((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) && (cdb_arch != 0x2ca)) {
          return 1;
        }
        if (a == 3) {
          return 1;
        }
      }
      uVar4 = uVar4 + 1;
      c_00 = c;
    }
  }
  else {
    if (iVar7 == 6) {
      lVar3 = dev_mem_read(iVar5,a,uVar4,(long)c_00);
      if (lVar3 == 0) {
        cdb_c_error(s_unable_to_read_memory_004d33d8);
        return 0;
      }
      if ((cdb_arch == 0x2cb) && (lVar3 = dev_call_slot11(iVar5,a,uVar4,(long)c_00), lVar3 == 0)) {
        cdb_c_error(s_unable_to_read_memory_004d33d8);
        return 0;
      }
      if ((((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cc)) ||
           (cdb_arch == 0x2cb)) ||
          ((((cdb_arch == 0x2c5 || (cdb_arch == 0x2c8)) || (cdb_arch == 0x2ca)) && (a != 3)))) &&
         (lVar3 = dev_mem_read(iVar5,a,uVar4 + 1,(long)c), lVar3 == 0)) {
        cdb_c_error(s_unable_to_read_memory_004d33d8);
        return 0;
      }
      if ((cdb_arch == 0x2cb) && (lVar3 = dev_call_slot11(iVar5,a,uVar4 + 2,(long)c), lVar3 == 0)) {
        cdb_c_error(s_unable_to_read_memory_004d33d8);
        return 0;
      }
      if (cdb_arch == 0x2c6) {
        *(uint *)((int)v + 8) = *c_00;
        return 1;
      }
      if ((((cdb_arch != 0x2c7) && (cdb_arch != 0x2c9)) && (cdb_arch != 0x2cc)) &&
         ((cdb_arch != 0x2cb && (cdb_arch != 0x2ca)))) {
        return 1;
      }
      *(ushort *)((int)v + 8) = (ushort)cdb_word_mask & *(ushort *)c_00;
      *(ushort *)((int)v + 10) = (ushort)cdb_word_mask & *(ushort *)c;
      return 1;
    }
    if (iVar7 == 7) {
      lVar3 = dev_mem_read(iVar5,a,uVar4,(long)c_00);
      if (lVar3 == 0) {
        cdb_c_error(s_unable_to_read_memory_004d33d8);
        return 0;
      }
      if ((a != 3) && (lVar3 = dev_mem_read(iVar5,a,uVar4 + 1,(long)c), lVar3 == 0)) {
        cdb_c_error(s_unable_to_read_memory_004d33d8);
        return 0;
      }
      if (cdb_arch == 0x2cb) {
        lVar3 = dev_call_slot11(iVar5,a,uVar4,(long)c_00);
        if (lVar3 == 0) {
          cdb_c_error(s_unable_to_read_memory_004d33d8);
          return 0;
        }
        lVar3 = dev_call_slot11(iVar5,a,uVar4 + 2,(long)c);
        if (lVar3 == 0) {
          cdb_c_error(s_unable_to_read_memory_004d33d8);
          return 0;
        }
      }
      if (cdb_arch == 0x2c6) {
        if (a != 3) {
          *(uint *)v = *c;
          *(uint *)((int)v + 4) = *c_00;
          return 1;
        }
        *(uint *)v = *c_00;
        *(uint *)((int)v + 4) = *c;
        return 1;
      }
      if ((((cdb_arch != 0x2c7) && (cdb_arch != 0x2ca)) && (cdb_arch != 0x2cb)) &&
         ((cdb_arch != 0x2cc && (cdb_arch != 0x2c9)))) {
        return 1;
      }
      *(ushort *)((int)v + 8) = (ushort)cdb_word_mask & *(ushort *)c_00;
      *(ushort *)((int)v + 10) = (ushort)cdb_word_mask & *(ushort *)c;
      return 1;
    }
    if ((iVar7 == 8) || (iVar7 == 9)) {
      *c_00 = uVar4;
      *c = a;
      return 1;
    }
    if (iVar7 == 1) {
      return 1;
    }
    if (((((iVar7 != 0x10000) && (iVar7 != 0x10001)) && (iVar7 != 0x10003)) &&
        ((iVar7 != 0x10002 && (iVar7 != 0x10004)))) && (iVar7 != 0x10005)) {
      cdb_internal_error(0x4d30a4,0xe53);
      return 1;
    }
    if (cdb_arch == 0x2cb) {
      lVar3 = dev_call_slot11(iVar5,a,uVar4,(long)c_00);
      if (lVar3 == 0) {
        cdb_c_error(s_unable_to_read_memory_004d33d8);
        return 0;
      }
      iVar7 = uVar4 + 2;
LAB_004632e5:
      lVar3 = dev_mem_read(iVar5,a,iVar7,(long)c);
      if (lVar3 == 0) {
        cdb_c_error(s_unable_to_read_memory_004d33d8);
        return 0;
      }
    }
    else {
      lVar3 = dev_mem_read(iVar5,a,uVar4,(long)c_00);
      if (lVar3 == 0) {
        cdb_c_error(s_unable_to_read_memory_004d33d8);
        return 0;
      }
      iVar7 = *(int *)((int)v + 0x20);
      if ((((iVar7 == 0x10002) || (iVar7 == 0x10005)) || ((iVar7 == 0x10004 || (iVar7 == 0x10003))))
         && ((((cdb_arch == 0x2c7 || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cc)) ||
             ((((cdb_arch == 0x2c5 || (cdb_arch == 0x2c8)) || (cdb_arch == 0x2ca)) && (a != 3))))))
      {
        iVar7 = uVar4 + 1;
        goto LAB_004632e5;
      }
    }
    if (*(int *)((int)v + 0x20) != 0x10005) {
      return 1;
    }
    if (((cdb_arch != 0x2c7) && (cdb_arch != 0x2c9)) && ((cdb_arch != 0x2cc && (cdb_arch != 0x2cb)))
       ) {
      if (((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) && (cdb_arch != 0x2ca)) {
        return 1;
      }
      if (a == 3) {
        return 1;
      }
    }
    uVar4 = uVar4 + 2;
    c_00 = puVar1;
  }
  iVar5 = dev_mem_read(iVar5,a,uVar4,(long)c_00);
LAB_00463451:
  if (iVar5 != 0) {
    return 1;
  }
  cdb_c_error(s_unable_to_read_memory_004d33d8);
  return 0;
}


/* ==== cdb_store_memory @ 00463480 ==== */

int __cdecl cdb_store_memory(void *v)

{
  long lVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  int a;
  int iVar5;
  int iVar6;
  uint local_7c;
  uint local_74;
  int local_70;
  uint local_5c;
  uint local_58 [2];
  uint local_50;
  uint local_4c;
  uint local_48 [2];
  undefined1 local_40 [24];
  uint local_28;
  uint local_14;
  
  iVar2 = *(int *)(cur_dev + 4);
  iVar6 = *(int *)((int)v + 0x20);
  a = *(int *)((int)v + 0x1c);
  iVar5 = *(int *)((int)v + 0x18);
  if (((byte)iVar6 & 0x30) == 0x10) {
    if (a == 3) {
      a = 2;
    }
    local_5c = *(uint *)((int)v + 0xc) & cdb_addr_mask;
    lVar1 = dev_call_slot1(iVar2,a,iVar5,(long)&local_5c);
    if (lVar1 == 0) {
      cdb_c_error(s_unable_to_write_memory_004d33f0);
      return 0;
    }
    if (cdb_arch != 0x2cb) {
      return 1;
    }
    iVar2 = dev_call_slot15(iVar2,a,iVar5,(long)&local_5c);
    goto LAB_00463e1f;
  }
  if (*(int *)((int)v + 0x24) == 0x12) {
    if (a == 3) {
      a = 2;
    }
    cdb_sym_to_value(local_40,*(int *)((int)v + 0x28));
    iVar5 = iVar5 + local_28 / cdb_word_bits;
    uVar4 = local_28 % cdb_word_bits;
    lVar1 = dev_mem_read(iVar2,a,iVar5,(long)&local_50);
    if (lVar1 == 0) {
      cdb_c_error(s_unable_to_read_memory_004d33d8);
      return 0;
    }
    lVar1 = dev_mem_read(iVar2,a,iVar5 + 1,(long)&local_4c);
    if (lVar1 == 0) {
      cdb_c_error(s_unable_to_read_memory_004d33d8);
      return 0;
    }
    lVar1 = dev_mem_read(iVar2,a,iVar5 + 2,(long)local_48);
    if (lVar1 == 0) {
      cdb_c_error(s_unable_to_read_memory_004d33d8);
      return 0;
    }
    if (cdb_word_bits < local_14 + uVar4) {
      if (cdb_word_bits * 2 < local_14 + uVar4) {
        local_7c = cdb_word_bits;
        local_74 = cdb_word_bits - uVar4;
        local_70 = (local_14 - local_74) - cdb_word_bits;
      }
      else {
        local_74 = cdb_word_bits - uVar4;
        local_70 = 0;
        local_7c = local_14 - local_74;
      }
    }
    else {
      local_70 = 0;
      local_7c = 0;
      local_74 = local_14;
    }
    local_50 = (*(uint *)(&cdb_bitmask_tab + local_74 * 4) & *(uint *)((int)v + 0xc)) <<
               ((byte)uVar4 & 0x1f) |
               ~(*(uint *)(&cdb_bitmask_tab + local_74 * 4) << ((byte)uVar4 & 0x1f)) & local_50;
    if (local_7c != 0) {
      local_4c = *(uint *)((int)v + 0xc) >> ((byte)local_74 & 0x1f) &
                 *(uint *)(&cdb_bitmask_tab + (cdb_word_bits - local_74) * 4) |
                 ~*(uint *)(&cdb_bitmask_tab + local_7c * 4) & local_4c;
      if (cdb_word_bits < local_14) {
        local_4c = local_4c |
                   (*(uint *)((int)v + 0x10) & *(uint *)(&cdb_bitmask_tab + local_74 * 4)) <<
                   ((byte)(cdb_word_bits - local_74) & 0x1f);
      }
    }
    if (local_70 != 0) {
      local_48[0] = *(uint *)((int)v + 0x10) >> ((byte)local_74 & 0x1f) &
                    *(uint *)(&cdb_bitmask_tab + local_70 * 4) |
                    local_48[0] & ~*(uint *)(&cdb_bitmask_tab + local_70 * 4);
    }
    lVar1 = dev_call_slot1(iVar2,a,iVar5,(long)&local_50);
    if (lVar1 == 0) {
      cdb_c_error(s_unable_to_write_memory_004d33f0);
      return 0;
    }
    lVar1 = dev_call_slot1(iVar2,a,iVar5 + 1,(long)&local_4c);
    if (lVar1 == 0) {
      cdb_c_error(s_unable_to_write_memory_004d33f0);
      return 0;
    }
    lVar1 = dev_call_slot1(iVar2,a,iVar5 + 2,(long)local_48);
    if (lVar1 != 0) {
      iVar2 = cdb_load_value(v);
      if (iVar2 != 0) {
        return 1;
      }
      return 0;
    }
    cdb_c_error(s_unable_to_write_memory_004d33f0);
    return 0;
  }
  if ((((iVar6 == 2) || (iVar6 == 3)) || (iVar6 == 4)) || ((iVar6 == 0xb || (iVar6 == 10)))) {
LAB_00463ccf:
    if ((iVar6 == 5) || (iVar6 == 0xf)) {
LAB_00463d38:
      if ((cdb_arch == 0x2c6) && (a == 3)) {
        a = 2;
      }
      lVar1 = dev_call_slot1(iVar2,a,iVar5,(int)v + 0xc);
      if (lVar1 == 0) {
        cdb_c_error(s_unable_to_write_memory_004d33f0);
        return 0;
      }
      if (cdb_arch == 0x2cb) {
        a = 0;
        lVar1 = dev_call_slot14(iVar2,0,iVar5,(int)v + 0xc);
        if (lVar1 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        lVar1 = dev_call_slot14(iVar2,0,iVar5 + 2,(int)v + 0x10);
        if (lVar1 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
      }
      if (((cdb_arch != 0x2c7) && (cdb_arch != 0x2c9)) && (cdb_arch != 0x2cc)) {
        if (((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) && (cdb_arch != 0x2ca)) {
          return 1;
        }
joined_r0x00463e10:
        if (a == 3) {
          return 1;
        }
      }
      v = (void *)((int)v + 0x10);
      goto LAB_00463e16;
    }
    if (cdb_arch != 0x2cb) {
      if (a == 3) {
        a = 2;
      }
      v = (void *)((int)v + 0xc);
      goto LAB_00463e19;
    }
    lVar1 = dev_call_slot14(iVar2,0,iVar5,(int)v + 0xc);
    if (lVar1 == 0) {
      cdb_c_error(s_unable_to_write_memory_004d33f0);
      return 0;
    }
    iVar2 = dev_call_slot14(iVar2,0,iVar5 + 2,(int)v + 0x10);
  }
  else {
    if (iVar6 == 5) goto LAB_00463d38;
    if (((iVar6 == 0xc) || (iVar6 == 0xd)) || ((iVar6 == 0xe || (iVar6 == 0xf)))) goto LAB_00463ccf;
    if (((iVar6 == 0x10000) || (iVar6 == 0x10001)) ||
       ((iVar6 == 0x10003 || (((iVar6 == 0x10002 || (iVar6 == 0x10004)) || (iVar6 == 0x10005)))))) {
      lVar1 = dev_call_slot1(iVar2,a,iVar5,(int)v + 0xc);
      if (lVar1 == 0) {
        cdb_c_error(s_unable_to_write_memory_004d33f0);
        return 0;
      }
      iVar6 = *(int *)((int)v + 0x20);
      if ((((iVar6 == 0x10002) || (iVar6 == 0x10005)) || ((iVar6 == 0x10004 || (iVar6 == 0x10003))))
         && (((((cdb_arch == 0x2c7 || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cc)) ||
              ((((cdb_arch == 0x2c5 || (cdb_arch == 0x2c8)) || (cdb_arch == 0x2ca)) && (a != 3))))
             && (lVar1 = dev_call_slot1(iVar2,a,iVar5 + 1,(int)v + 0x10), lVar1 == 0)))) {
        cdb_c_error(s_unable_to_write_memory_004d33f0);
        return 0;
      }
      if (cdb_arch == 0x2cb) {
        a = 0;
        lVar1 = dev_call_slot14(iVar2,0,iVar5,(int)v + 0xc);
        if (lVar1 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        lVar1 = dev_call_slot14(iVar2,0,iVar5 + 2,(int)v + 0x10);
        if (lVar1 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
      }
      if (*(int *)((int)v + 0x20) != 0x10005) {
        return 1;
      }
      v = (void *)((int)v + 0x14);
      iVar5 = iVar5 + 2;
      goto LAB_00463e19;
    }
    if (iVar6 == 6) {
      if (((cdb_arch != 0x2c7) && (cdb_arch != 0x2c9)) &&
         ((cdb_arch != 0x2cc && (cdb_arch != 0x2ca)))) {
        if (cdb_arch == 0x2cb) {
          local_5c = (uint)*(ushort *)((int)v + 8);
          local_58[0] = (uint)*(ushort *)((int)v + 10);
          lVar1 = dev_call_slot14(iVar2,a,iVar5,(long)&local_5c);
          if (lVar1 == 0) {
            cdb_c_error(s_unable_to_write_memory_004d33f0);
            return 0;
          }
          iVar2 = dev_call_slot14(iVar2,a,iVar5 + 2,(long)local_58);
          goto LAB_00463e1f;
        }
        if ((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) {
          if (cdb_arch != 0x2c6) {
            return 1;
          }
          if (a == 3) {
            a = 2;
          }
          v = (void *)((int)v + 8);
          goto LAB_00463e19;
        }
LAB_00463a4d:
        lVar1 = dev_call_slot1(iVar2,a,iVar5,(int)v + 0xc);
        if (lVar1 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        goto joined_r0x00463e10;
      }
      local_5c = (uint)*(ushort *)((int)v + 8);
      local_58[0] = (uint)*(ushort *)((int)v + 10);
      lVar1 = dev_call_slot1(iVar2,a,iVar5,(long)&local_5c);
      if (lVar1 == 0) {
        cdb_c_error(s_unable_to_write_memory_004d33f0);
        return 0;
      }
      if (a == 3) {
        return 1;
      }
      v = local_58;
    }
    else {
      if (iVar6 != 7) {
        if ((iVar6 != 8) && (iVar6 != 9)) {
          cdb_internal_error(0x4d30a4,0x1052);
          return 1;
        }
        iVar6 = *(int *)((int)v + 0xc);
        lVar1 = *(long *)((int)v + 0x10);
        if (cdb_arch == 0x2cb) {
          local_74 = 0;
        }
        else {
          local_74 = cdb_struct_size(*(int *)((int)v + 0x28));
        }
        if (local_74 == 0) {
          return 1;
        }
        while( true ) {
          local_74 = local_74 - 1;
          lVar3 = dev_mem_read(iVar2,lVar1,iVar6,(long)&local_5c);
          if (lVar3 == 0) {
            cdb_c_error(s_unable_to_read_memory_004d33d8);
            return 0;
          }
          lVar3 = dev_call_slot1(iVar2,a,iVar5,(long)&local_5c);
          if (lVar3 == 0) break;
          iVar5 = iVar5 + 1;
          iVar6 = iVar6 + 1;
          if (local_74 == 0) {
            return 1;
          }
        }
        goto LAB_00463e26;
      }
      if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cc)) ||
         (cdb_arch == 0x2ca)) {
        local_5c = (uint)*(ushort *)((int)v + 8);
        local_58[0] = (uint)*(ushort *)((int)v + 10);
        lVar1 = dev_call_slot1(iVar2,a,iVar5,(long)&local_5c);
        if (lVar1 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        if (a == 3) {
          return 1;
        }
        v = local_58;
      }
      else {
        if (cdb_arch == 0x2cb) {
          local_5c = (uint)*(ushort *)((int)v + 8);
          local_58[0] = (uint)*(ushort *)((int)v + 10);
          lVar1 = dev_call_slot14(iVar2,a,iVar5,(long)&local_5c);
          if (lVar1 == 0) {
            cdb_c_error(s_unable_to_write_memory_004d33f0);
            return 0;
          }
          iVar2 = dev_call_slot14(iVar2,a,iVar5 + 2,(long)local_58);
          goto LAB_00463e1f;
        }
        if ((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) goto LAB_00463a4d;
        if (cdb_arch != 0x2c6) {
          return 1;
        }
        if (a == 3) {
          lVar1 = dev_call_slot1(iVar2,2,iVar5,(long)v);
          if (lVar1 == 0) goto LAB_00463e26;
          v = (void *)((int)v + 4);
          a = 1;
          goto LAB_00463e19;
        }
        lVar1 = dev_call_slot1(iVar2,a,iVar5,(int)v + 4);
        if (lVar1 == 0) goto LAB_00463e26;
      }
    }
LAB_00463e16:
    iVar5 = iVar5 + 1;
LAB_00463e19:
    iVar2 = dev_call_slot1(iVar2,a,iVar5,(long)v);
  }
LAB_00463e1f:
  if (iVar2 != 0) {
    return 1;
  }
LAB_00463e26:
  cdb_c_error(s_unable_to_write_memory_004d33f0);
  return 0;
}


/* ==== cdb_load_register @ 00463e50 ==== */

int __cdecl cdb_load_register(void *v)

{
  void *pvVar1;
  char cVar2;
  undefined3 extraout_var;
  int extraout_EAX;
  int extraout_EAX_00;
  undefined3 extraout_var_00;
  int iVar3;
  long lVar4;
  int iVar5;
  int local_50;
  uint local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined2 local_4;
  char *name;
  
  pvVar1 = v;
  iVar5 = *(int *)(cur_dev + 4);
  cVar2 = cdb_reg_name(*(int *)((int)v + 0x20),*(ulong *)((int)v + 0x18));
  name = (char *)CONCAT31(extraout_var,cVar2);
  if (name == (char *)0x0) {
    return 0;
  }
  cdb_frame_current();
  if ((extraout_EAX == 0) || (cdb_frame_first(), extraout_EAX == extraout_EAX_00)) {
    iVar3 = 0;
  }
  else {
    cVar2 = cdb_find_saved_reg(*(void **)(extraout_EAX + 0x14),name);
    iVar3 = CONCAT31(extraout_var_00,cVar2);
  }
  if (iVar3 != 0) {
    local_28 = *(undefined4 *)(iVar3 + 8);
    local_24 = *(undefined4 *)(iVar3 + 0xc);
    local_20 = *(undefined4 *)((int)pvVar1 + 0x20);
    local_1c = 2;
    local_4 = 1;
    cdb_load_value(&local_40);
    *(undefined4 *)((int)pvVar1 + 0xc) = local_34;
    *(undefined4 *)((int)pvVar1 + 0x10) = local_30;
    *(undefined4 *)((int)pvVar1 + 0x14) = local_2c;
    *(undefined4 *)pvVar1 = local_40;
    *(undefined4 *)((int)pvVar1 + 4) = local_3c;
    *(undefined4 *)((int)pvVar1 + 8) = local_38;
    return 1;
  }
  lVar4 = periph_find_reg(iVar5,name,&local_50,(int *)&v);
  if (lVar4 == 0) {
    cdb_internal_error(0x4d30a4,0x10b9);
    return 0;
  }
  lVar4 = periph_call(iVar5,local_50,(long)v,(long)&local_4c);
  if (lVar4 == 0) {
    cdb_c_error(s_unable_to_read_register_004d3130);
    return 0;
  }
  iVar5 = *(int *)((int)pvVar1 + 0x20);
  if (((byte)iVar5 & 0x30) == 0x10) {
    if (cdb_arch != 0x2cb) {
      iVar5 = cdb_default_space();
      *(int *)((int)pvVar1 + 0x10) = iVar5;
      *(uint *)((int)pvVar1 + 0xc) = local_4c & cdb_addr_mask;
      return 1;
    }
    *(undefined4 *)((int)pvVar1 + 0x10) = 0;
    *(uint *)((int)pvVar1 + 0xc) = local_4c & cdb_addr_mask;
    return 1;
  }
  if ((((((iVar5 == 2) || (iVar5 == 3)) || (iVar5 == 4)) ||
       (((iVar5 == 0xb || (iVar5 == 10)) || ((iVar5 == 5 || ((iVar5 == 0xc || (iVar5 == 0xd))))))))
      || (iVar5 == 0xe)) || (iVar5 == 0xf)) {
    if (cdb_arch == 0x2cb) {
      if ((((iVar5 != 5) && (iVar5 != 0xf)) && (iVar5 != 4)) &&
         (((iVar5 != 0xb && (iVar5 != 10)) && (iVar5 != 0xe)))) {
        *(undefined4 *)((int)pvVar1 + 0x10) = 0;
        *(uint *)((int)pvVar1 + 0xc) = local_4c;
        return 1;
      }
      *(uint *)((int)pvVar1 + 0xc) = local_4c;
      *(undefined4 *)((int)pvVar1 + 0x10) = local_48;
      return 1;
    }
    if ((iVar5 != 5) && (iVar5 != 0xf)) {
      *(undefined4 *)((int)pvVar1 + 0x10) = 0;
      *(uint *)((int)pvVar1 + 0xc) = local_4c;
      return 1;
    }
    if (cdb_arch == 0x2c6) {
      *(undefined4 *)((int)pvVar1 + 0x10) = 0;
      *(uint *)((int)pvVar1 + 0xc) = local_4c;
      return 1;
    }
    *(undefined4 *)((int)pvVar1 + 0x10) = local_48;
    *(uint *)((int)pvVar1 + 0xc) = local_4c;
  }
  else {
    if (((((iVar5 != 0x10000) && (iVar5 != 0x10001)) && (iVar5 != 0x10003)) &&
        ((iVar5 != 0x10002 && (iVar5 != 0x10004)))) && (iVar5 != 0x10005)) {
      if (iVar5 == 6) {
        if ((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) {
LAB_00464121:
          *(uint *)((int)pvVar1 + 0xc) = local_4c;
          *(undefined4 *)((int)pvVar1 + 0x10) = local_48;
          return 1;
        }
        if (cdb_arch == 0x2c6) {
          *(uint *)((int)pvVar1 + 8) = local_4c;
          return 1;
        }
      }
      else {
        if (iVar5 != 7) {
          cdb_internal_error(0x4d30a4,0x112e);
          return 1;
        }
        if ((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) goto LAB_00464121;
        if (cdb_arch == 0x2c6) {
          *(uint *)pvVar1 = local_4c;
          *(undefined4 *)((int)pvVar1 + 4) = local_48;
          return 1;
        }
        if ((((cdb_arch != 0x2c7) && (cdb_arch != 0x2c9)) && (cdb_arch != 0x2cc)) &&
           ((cdb_arch != 0x2cb && (cdb_arch != 0x2ca)))) {
          return 1;
        }
      }
      *(ushort *)((int)pvVar1 + 8) = (ushort)local_4c & (ushort)cdb_word_mask;
      *(ushort *)((int)pvVar1 + 10) = (ushort)local_48 & (ushort)cdb_word_mask;
      return 1;
    }
    *(uint *)((int)pvVar1 + 0xc) = local_4c;
    if ((((iVar5 == 0x10002) || (iVar5 == 0x10005)) || (iVar5 == 0x10004)) || (iVar5 == 0x10003)) {
      *(undefined4 *)((int)pvVar1 + 0x10) = local_48;
    }
    if (iVar5 == 0x10005) {
      *(undefined4 *)((int)pvVar1 + 0x14) = local_44;
      return 1;
    }
  }
  return 1;
}


/* ==== cdb_find_saved_reg @ 00464290 ==== */

char __cdecl cdb_find_saved_reg(void *list,char *name)

{
  char *a;
  int iVar1;
  
  if (list == (void *)0x0) {
    return '\0';
  }
  do {
    for (a = *(char **)((int)list + 0x10); a != (char *)0x0; a = *(char **)(a + 0x10)) {
      iVar1 = strncmp(a,name,5);
      if (iVar1 == 0) {
        return (char)a;
      }
    }
    list = *(void **)((int)list + 0x14);
  } while (list != (void *)0x0);
  return '\0';
}


/* ==== cdb_store_register @ 004642e0 ==== */

int __cdecl cdb_store_register(void *v)

{
  void *pvVar1;
  char cVar2;
  undefined3 extraout_var;
  int extraout_EAX;
  int extraout_EAX_00;
  undefined3 extraout_var_00;
  int iVar3;
  long lVar4;
  int iVar5;
  undefined4 va0;
  int local_50;
  uint local_4c;
  uint local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined2 local_4;
  char *name;
  
  pvVar1 = v;
  local_44 = 0;
  iVar5 = *(int *)(cur_dev + 4);
  cVar2 = cdb_reg_name(*(int *)((int)v + 0x20),*(ulong *)((int)v + 0x18));
  name = (char *)CONCAT31(extraout_var,cVar2);
  if (name == (char *)0x0) {
    return 0;
  }
  cdb_frame_current();
  if ((extraout_EAX == 0) || (cdb_frame_first(), extraout_EAX == extraout_EAX_00)) {
    iVar3 = 0;
  }
  else {
    cVar2 = cdb_find_saved_reg(*(void **)(extraout_EAX + 0x14),name);
    iVar3 = CONCAT31(extraout_var_00,cVar2);
  }
  if (iVar3 != 0) {
    local_34 = *(undefined4 *)((int)pvVar1 + 0xc);
    local_30 = *(undefined4 *)((int)pvVar1 + 0x10);
    local_2c = *(undefined4 *)((int)pvVar1 + 0x14);
    local_40 = *(undefined4 *)pvVar1;
    local_3c = *(undefined4 *)((int)pvVar1 + 4);
    local_38 = *(undefined4 *)((int)pvVar1 + 8);
    local_28 = *(undefined4 *)(iVar3 + 8);
    local_20 = *(undefined4 *)((int)pvVar1 + 0x20);
    local_24 = *(undefined4 *)(iVar3 + 0xc);
    local_1c = 2;
    local_4 = 1;
    cdb_store_value(&local_40);
    return 1;
  }
  iVar3 = *(int *)((int)pvVar1 + 0x20);
  if (((byte)iVar3 & 0x30) == 0x10) {
    local_4c = *(uint *)((int)pvVar1 + 0xc);
    local_48 = 0;
  }
  else if ((((((iVar3 == 2) || (iVar3 == 3)) || (iVar3 == 4)) ||
            (((iVar3 == 0xb || (iVar3 == 10)) ||
             ((iVar3 == 5 || ((iVar3 == 0xc || (iVar3 == 0xd)))))))) || (iVar3 == 0xe)) ||
          (iVar3 == 0xf)) {
    if (cdb_arch == 0x2cb) {
      if (((((iVar3 == 5) || (iVar3 == 0xf)) || (iVar3 == 4)) || ((iVar3 == 0xb || (iVar3 == 10))))
         || (iVar3 == 0xe)) {
        local_48 = *(uint *)((int)pvVar1 + 0x10);
        local_4c = *(uint *)((int)pvVar1 + 0xc);
        goto LAB_004645d0;
      }
      local_48 = 0;
    }
    else if ((iVar3 == 5) || (iVar3 == 0xf)) {
      if (cdb_arch == 0x2c6) {
        local_4c = *(uint *)((int)pvVar1 + 0xc);
        local_48 = 0;
        goto LAB_004645d0;
      }
      local_48 = *(uint *)((int)pvVar1 + 0x10);
    }
    else {
      local_48 = 0;
    }
    local_4c = *(uint *)((int)pvVar1 + 0xc);
  }
  else if (((iVar3 == 0x10000) || (iVar3 == 0x10001)) ||
          ((iVar3 == 0x10003 || (((iVar3 == 0x10002 || (iVar3 == 0x10004)) || (iVar3 == 0x10005)))))
          ) {
    local_4c = *(uint *)((int)pvVar1 + 0xc);
    if (((iVar3 == 0x10002) || (iVar3 == 0x10005)) || ((iVar3 == 0x10004 || (iVar3 == 0x10003)))) {
      local_48 = *(uint *)((int)pvVar1 + 0x10);
    }
    if (iVar3 == 0x10005) {
      local_44 = *(undefined4 *)((int)pvVar1 + 0x14);
    }
  }
  else if (iVar3 == 6) {
    if ((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) {
LAB_00464504:
      local_4c = *(uint *)((int)pvVar1 + 0xc);
      local_48 = *(uint *)((int)pvVar1 + 0x10);
    }
    else if (cdb_arch == 0x2c6) {
      local_4c = *(uint *)((int)pvVar1 + 8);
      local_48 = 0;
    }
    else {
LAB_004644eb:
      local_4c = (uint)*(ushort *)((int)pvVar1 + 8);
      local_48 = (uint)*(ushort *)((int)pvVar1 + 10);
    }
  }
  else {
    if (iVar3 != 7) {
      va0 = 0x11e2;
      goto LAB_00464628;
    }
    if ((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) goto LAB_00464504;
    if (cdb_arch == 0x2c6) {
      local_4c = *(uint *)pvVar1;
      local_48 = *(uint *)((int)pvVar1 + 4);
    }
    else if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cc)) ||
            ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))) goto LAB_004644eb;
  }
LAB_004645d0:
  lVar4 = periph_find_reg(iVar5,name,&local_50,(int *)&v);
  if (lVar4 != 0) {
    iVar5 = dev_write_reg(iVar5,local_50,(int)v,(long *)&local_4c);
    if (iVar5 != 0) {
      return 1;
    }
    cdb_c_error(s_unable_to_write_register_004d3148);
    return 0;
  }
  va0 = 0x11f1;
LAB_00464628:
  cdb_internal_error(0x4d30a4,va0);
  return 0;
}


/* ==== cdb_load_devreg @ 00464640 ==== */

int __cdecl cdb_load_devreg(void *v)

{
  long lVar1;
  int iVar2;
  uint uVar3;
  uint local_c;
  uint local_8;
  uint local_4;
  
  lVar1 = periph_call(*(int *)(cur_dev + 4),*(int *)((int)v + 0x1c),*(long *)((int)v + 0x18),
                      (long)&local_c);
  if (lVar1 == 0) {
    cdb_c_error(s_unable_to_read_register_004d3130);
    return 0;
  }
  if ((((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) && (cdb_arch == 0x2c8)) &&
     ((*(uint *)((int)v + 0x28) & 0x2000000) != 0)) {
    local_8 = local_c >> 0x18;
    local_c = local_c & 0xffffff;
  }
  iVar2 = *(int *)((int)v + 0x20);
  if (((byte)iVar2 & 0x30) == 0x10) {
    *(uint *)((int)v + 0xc) = local_c;
    iVar2 = cdb_default_space();
    *(int *)((int)v + 0x10) = iVar2;
    return 1;
  }
  if (((iVar2 == 4) || (iVar2 == 0xb)) || ((iVar2 == 10 || (iVar2 == 0xe)))) {
    *(uint *)((int)v + 0xc) = local_c;
    *(undefined4 *)((int)v + 0x10) = 0;
    return 1;
  }
  if ((iVar2 != 5) && (iVar2 != 0xf)) {
    if ((iVar2 == 0x10000) || (iVar2 == 0x10001)) {
      *(uint *)((int)v + 0xc) = local_c;
      return 1;
    }
    if ((iVar2 != 0x10002) && (iVar2 != 0x10003)) {
      if (iVar2 == 0x10005) {
        *(uint *)((int)v + 0x10) = local_8;
        *(uint *)((int)v + 0xc) = local_c;
        *(uint *)((int)v + 0x14) = local_4;
        return 1;
      }
      if (iVar2 == 0x10004) {
        *(uint *)((int)v + 0x14) = local_8;
        *(uint *)((int)v + 0x10) = local_c;
        return 1;
      }
      if (cdb_arch != 0x2c6) {
        cdb_internal_error(0x4d30a4,0x125d);
        return 0;
      }
      if (iVar2 != 6) {
        if (iVar2 != 7) {
          return 1;
        }
        if ((*(uint *)((int)v + 0x28) & 0x80000) != 0) {
          uVar3 = local_c >> 0xb & cdb_word_mask;
          *(uint *)v = uVar3;
          *(uint *)v = local_8 << 0x15 & cdb_word_mask | uVar3;
          uVar3 = (local_8 & ~cdb_sign_bit) >> 0xb & cdb_word_mask;
          *(uint *)((int)v + 4) = uVar3;
          uVar3 = (local_4 & 0x7ff) << 0x14 & cdb_word_mask | uVar3;
          *(uint *)((int)v + 4) = uVar3;
          *(uint *)((int)v + 4) = local_4 & cdb_sign_bit | uVar3;
          return 1;
        }
        *(uint *)((int)v + 4) = local_8;
        *(uint *)v = local_c;
        return 1;
      }
      *(uint *)((int)v + 8) = local_c;
      return 1;
    }
  }
  *(uint *)((int)v + 0x10) = local_8;
  *(uint *)((int)v + 0xc) = local_c;
  return 1;
}


/* ==== cdb_store_devreg @ 004648a0 ==== */

int __cdecl cdb_store_devreg(void *v)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint local_c;
  uint local_8;
  uint local_4;
  
  iVar2 = *(int *)((int)v + 0x20);
  local_4 = 0;
  if ((((((byte)iVar2 & 0x30) == 0x10) || (iVar2 == 4)) || (iVar2 == 0xb)) ||
     ((iVar2 == 10 || (iVar2 == 0xe)))) {
    local_c = *(uint *)((int)v + 0xc);
    local_8 = 0;
  }
  else if ((iVar2 == 5) || (iVar2 == 0xf)) {
    local_8 = *(uint *)((int)v + 0x10);
    local_c = *(uint *)((int)v + 0xc);
  }
  else if ((iVar2 == 0x10000) || (iVar2 == 0x10001)) {
    local_c = *(uint *)((int)v + 0xc);
  }
  else if ((iVar2 == 0x10002) || (iVar2 == 0x10003)) {
    local_c = *(uint *)((int)v + 0xc);
    local_8 = *(uint *)((int)v + 0x10);
  }
  else if (iVar2 == 0x10005) {
    local_c = *(uint *)((int)v + 0xc);
    local_8 = *(uint *)((int)v + 0x10);
    local_4 = *(uint *)((int)v + 0x14);
  }
  else if (iVar2 == 0x10004) {
    local_8 = *(uint *)((int)v + 0xc);
    local_4 = *(uint *)((int)v + 0x10);
    local_c = 0;
  }
  else {
    if (cdb_arch != 0x2c6) {
      cdb_internal_error(0x4d30a4,0x12b3);
      return 0;
    }
    if (iVar2 == 6) {
      local_c = *(uint *)((int)v + 8);
      local_8 = 0;
    }
    else if (iVar2 == 7) {
      if ((*(uint *)((int)v + 0x28) & 0x80000) == 0) {
        local_8 = *(uint *)((int)v + 4);
        local_c = *(uint *)v;
      }
      else {
        uVar1 = *(uint *)((int)v + 4);
        local_c = *(uint *)v << 0xb & cdb_word_mask;
        uVar3 = cdb_sign_bit;
        if (*(double *)v == 0.0) {
          uVar3 = 0;
        }
        local_8 = (uVar1 << 0xb | *(uint *)v >> 0x15) & cdb_word_mask | uVar3;
        local_4 = (~cdb_sign_bit & uVar1) >> 0x14 & cdb_word_mask | cdb_sign_bit & uVar1;
      }
    }
  }
  if ((((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) && (cdb_arch == 0x2c8)) &&
     ((*(uint *)((int)v + 0x28) & 0x2000000) != 0)) {
    local_c = local_c | local_8 << 0x18;
    local_8 = 0;
  }
  iVar2 = dev_write_reg(*(int *)(cur_dev + 4),*(int *)((int)v + 0x1c),*(int *)((int)v + 0x18),
                        (long *)&local_c);
  if (iVar2 != 0) {
    iVar2 = cdb_load_value(v);
    return (uint)(iVar2 != 0);
  }
  cdb_c_error(s_unable_to_write_register_004d3148);
  return 0;
}


/* ==== cdb_load_arg @ 00464b10 ==== */

int __cdecl cdb_load_arg(void *v)

{
  int iVar1;
  
  iVar1 = cdb_load_auto(v);
  return (uint)(iVar1 != 0);
}


/* ==== cdb_store_arg @ 00464b30 ==== */

int __cdecl cdb_store_arg(void *v)

{
  int iVar1;
  
  iVar1 = cdb_store_auto(v);
  return (uint)(iVar1 != 0);
}


/* ==== cdb_out_reset @ 00464b50 ==== */

void cdb_out_reset(void)

{
  int extraout_EAX;
  
  cdb_outlen = 0;
  if (cdb_outbuf == 0) {
    cdb_malloc(cdb_outcap);
    cdb_outbuf = extraout_EAX;
  }
  return;
}


/* ==== cdb_out_append @ 00464b80 ==== */

void __cdecl cdb_out_append(char *s)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int extraout_EAX;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  
  uVar4 = 0xffffffff;
  pcVar7 = s;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar2 != '\0');
  iVar1 = (~uVar4 - 1) + cdb_outlen;
  iVar3 = (int)(cdb_outcap + (cdb_outcap >> 0x1f & 0xfU)) >> 4;
  if (iVar3 <= iVar1) {
    for (; iVar3 = cdb_outcap, cdb_outcap <= iVar1; cdb_outcap = cdb_outcap * 2) {
    }
  }
  cdb_outcap = iVar3;
  cdb_realloc(cdb_outbuf,cdb_outcap + 1);
  uVar5 = 0xffffffff;
  do {
    pcVar7 = s;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar7 = s + 1;
    cVar2 = *s;
    s = pcVar7;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  pcVar7 = pcVar7 + -uVar5;
  pcVar8 = (char *)(cdb_outlen + extraout_EAX);
  cdb_outbuf = (void *)extraout_EAX;
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
  cdb_outlen = cdb_outlen + (~uVar4 - 1);
  return;
}


/* ==== cdb_frac2_to_double @ 00464c30 ==== */

void __cdecl cdb_frac2_to_double(ulong hi,ulong lo,double *out)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  
  uVar5 = cdb_word_mask;
  iVar6 = 0x3ff;
  uVar7 = hi & cdb_sign_bit;
  if (uVar7 != 0) {
    hi = hi & ~cdb_sign_bit;
  }
  bVar2 = (char)cdb_word_bits - 1;
  uVar8 = lo << 1;
  uVar1 = (lo & cdb_sign_bit) >> (bVar2 & 0x1f) | hi * 2;
  if ((uVar1 == 0) && (uVar8 == 0)) {
    *(undefined4 *)out = 0;
    if (uVar7 != 0) {
      *(undefined4 *)((int)out + 4) = 0xbff00000;
      return;
    }
    *(undefined4 *)((int)out + 4) = 0;
    return;
  }
  if (uVar7 != 0) {
    uVar8 = (~uVar8 & cdb_word_mask) + 1;
    uVar1 = ~uVar1;
    if ((uVar8 & cdb_sign_bit * 2) != 0) {
      uVar1 = uVar1 + 1;
      uVar8 = uVar8 & cdb_word_mask;
    }
  }
  for (; (cdb_sign_bit & uVar1) == 0; uVar1 = uVar1 * 2 | uVar3 >> (bVar2 & 0x1f)) {
    uVar3 = uVar8 & cdb_sign_bit;
    uVar8 = uVar8 << 1;
    iVar6 = iVar6 + -1;
  }
  uVar4 = uVar8 & cdb_sign_bit;
  uVar8 = uVar8 * 2 & cdb_word_mask;
  uVar3 = (iVar6 + 0xfff) * 0x100000;
  *(uint *)((int)out + 4) = uVar3;
  uVar5 = (uVar4 >> (bVar2 & 0x1f) | uVar1 * 2) & uVar5;
  if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cc)) ||
     ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))) {
    *(uint *)((int)out + 4) = uVar8 >> 0xc | uVar5 << 4 | uVar3;
    *(uint *)out = uVar8 << 0x14;
  }
  else {
    *(uint *)((int)out + 4) = uVar5 >> 4 | uVar3;
    *(uint *)out = (uVar5 << 0x18 | uVar8) << 4;
  }
  if (uVar7 != 0) {
    *out = -*out;
  }
  return;
}


/* ==== cdb_frac1_to_double @ 00464d60 ==== */

void __cdecl cdb_frac1_to_double(ulong w,double *out)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar2 = 0x3ff;
  uVar4 = w & cdb_sign_bit;
  if (uVar4 != 0) {
    w = w & ~cdb_sign_bit;
  }
  uVar1 = w << 1;
  if (uVar1 == 0) {
    *(undefined4 *)out = 0;
    if (uVar4 != 0) {
      *(undefined4 *)((int)out + 4) = 0xbff00000;
      return;
    }
    *(undefined4 *)((int)out + 4) = 0;
    return;
  }
  if (uVar4 != 0) {
    uVar1 = ~uVar1 + 1;
  }
  for (; (cdb_sign_bit & uVar1) == 0; uVar1 = uVar1 << 1) {
    iVar2 = iVar2 + -1;
  }
  uVar3 = (iVar2 + 0xfff) * 0x100000;
  uVar1 = uVar1 * 2 & cdb_word_mask;
  *(uint *)((int)out + 4) = uVar3;
  if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cc)) ||
     ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))) {
    *(undefined4 *)out = 0;
    *(uint *)((int)out + 4) = uVar1 << 4 | uVar3;
  }
  else {
    *(uint *)((int)out + 4) = uVar1 >> 4 | uVar3;
    *(uint *)out = uVar1 << 0x1c;
  }
  if (uVar4 != 0) {
    *out = -*out;
  }
  return;
}


