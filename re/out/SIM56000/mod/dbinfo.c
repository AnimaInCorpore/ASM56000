/* ==== dbg_verify_section @ 00440030 ==== */

int __cdecl dbg_verify_section(int dev,int secno)

{
  uint n;
  int iVar1;
  uint uVar2;
  long lVar3;
  int *buf;
  long lVar4;
  int *piVar5;
  int b;
  int local_14;
  int local_10;
  long local_c;
  int local_8 [2];
  
  piVar5 = (int *)(*(int *)(cur_sim + 0x4014) + secno * 0x20);
  lVar4 = piVar5[1];
  b = *piVar5;
  n = piVar5[2];
  secno = -1;
  local_c = lVar4;
  iVar1 = fseek(g_cld_fp,piVar5[3],0);
  if (iVar1 == 0) {
    if ((piVar5[4] & 0x400U) == 0) {
      iVar1 = 0;
      dsp_alloc(n * 4,0);
      if (buf != (int *)0x0) {
        uVar2 = fread_swap32((char *)buf,4,n,g_cld_fp);
        if ((uVar2 == n) && (secno = 0, piVar5 = buf, 0 < (int)n)) {
          do {
            lVar4 = dev_mem_read(dev,local_c,b,(long)local_8);
            if (lVar4 == 0) {
              sim_error(s_Error_reading_memory_004c7abc);
              break;
            }
            if (local_8[0] != *piVar5) {
              secno = secno + 1;
            }
            iVar1 = iVar1 + 1;
            piVar5 = piVar5 + 1;
            b = b + 1;
          } while (iVar1 < (int)n);
        }
        dsp_free(buf);
      }
    }
    else {
      uVar2 = fread_swap32((char *)&local_10,4,1,g_cld_fp);
      if (uVar2 == 1) {
        secno = 0;
        local_14 = 0;
        if (0 < (int)n) {
          do {
            lVar3 = dev_mem_read(dev,lVar4,b,(long)local_8);
            if (lVar3 == 0) {
              sim_error(s_Error_reading_memory_004c7abc);
              return secno;
            }
            if (local_8[0] != local_10) {
              secno = secno + 1;
            }
            local_14 = local_14 + 1;
            b = b + 1;
          } while (local_14 < (int)n);
          return secno;
        }
      }
    }
  }
  return secno;
}


/* ==== fread_swap32 @ 004401c0 ==== */

uint __cdecl fread_swap32(char *buf,uint size,uint n,void *fp)

{
  uint uVar1;
  
  uVar1 = fread(buf,size,n,fp);
  swap32_array(buf,size,n);
  return uVar1;
}


/* ==== swap32_array @ 00440200 ==== */

void __cdecl swap32_array(void *buf,int size,int count)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 uVar3;
  undefined1 *puVar4;
  
  puVar2 = (undefined1 *)((int)buf + (count * size & 0xfffffffcU));
  if (buf < puVar2) {
    puVar4 = (undefined1 *)((int)buf + 1);
    do {
      uVar3 = puVar4[-1];
      puVar4[-1] = puVar4[2];
      puVar4[2] = uVar3;
      uVar3 = *puVar4;
      *puVar4 = puVar4[1];
      puVar4[1] = uVar3;
      puVar1 = puVar4 + 3;
      puVar4 = puVar4 + 4;
    } while (puVar1 < puVar2);
  }
  return;
}


/* ==== dbg_sym_name @ 00440240 ==== */

char * __cdecl dbg_sym_name(void *sym)

{
  uint uVar1;
  
  if (*(int *)sym == 0) {
    uVar1 = *(uint *)((int)sym + 4);
    if ((3 < uVar1) && ((int)uVar1 <= *(int *)(cur_sim + 0x3fe8))) {
      return (char *)(*(int *)(cur_sim + 0x3fe4) + uVar1);
    }
    expr_error(s_invalid_string_table_offset_004c7ad4);
    sym = &empty_str;
  }
  return sym;
}


/* ==== dbg_aux_name @ 00440280 ==== */

char * __cdecl dbg_aux_name(void *aux)

{
  uint uVar1;
  
  uVar1 = *(uint *)((int)aux + 0x10);
  if (uVar1 != 0) {
    if ((3 < uVar1) && (uVar1 <= *(uint *)(cur_sim + 0x3fe8))) {
      return (char *)(*(int *)(cur_sim + 0x3fe4) + uVar1);
    }
    expr_error(s_invalid_string_table_offset_004c7ad4);
    aux = &empty_str;
  }
  return aux;
}


/* ==== dbg_find_label @ 004402c0 ==== */

int __cdecl dbg_find_label(uint addr,int space,uint *is_local)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int level;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint local_28;
  uint local_24;
  uint local_20;
  int local_1c;
  
  local_24 = 0;
  local_28 = 0xffffffff;
  local_1c = 0;
  local_20 = 0;
  level = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(space,addr);
  iVar5 = addr_to_srcline(addr,level);
  piVar1 = *(int **)(cur_sim + 0x402c);
  if (piVar1 != (int *)0x0) {
    iVar2 = *piVar1;
    iVar3 = *(int *)(cur_sim + 0x3fdc);
    iVar9 = 1;
    if (0 < iVar2) {
      space = (int)(piVar1 + iVar2 + 1);
      do {
        iVar6 = *(int *)(space + 4) + -1;
        iVar8 = (iVar9 + 1 + iVar6) / 2;
        iVar10 = iVar9;
        if (iVar9 < iVar6) {
          do {
            iVar11 = iVar8;
            if (addr < *(uint *)(piVar1[iVar8] * 0x20 + 8 + iVar3)) {
              iVar6 = iVar8 + -1;
              iVar11 = iVar10;
            }
            iVar8 = (iVar6 + 1 + iVar11) / 2;
            iVar10 = iVar11;
          } while (iVar11 < iVar6);
        }
        iVar6 = piVar1[iVar8] * 0x20 + iVar3;
        uVar4 = *(uint *)(iVar6 + 8);
        uVar7 = *(int *)(iVar6 + 0x10) - iVar5;
        if ((int)uVar7 < 0) {
          uVar7 = -uVar7;
        }
        if ((((local_24 <= uVar4) && (uVar4 <= addr)) && ((uVar7 <= local_28 || (iVar5 == 0)))) &&
           (iVar9 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))
                              (*(undefined4 *)(piVar1[iVar9] * 0x20 + 0xc + iVar3),uVar4),
           iVar9 == level)) {
          local_1c = piVar1[iVar8];
          local_20 = (uint)(*(int *)(iVar6 + 0x18) == 0xd6);
          local_28 = uVar7;
          local_24 = uVar4;
        }
        iVar9 = *(int *)(space + 4);
        space = space + 4;
      } while (iVar9 <= iVar2);
    }
    *is_local = local_20;
    return local_1c;
  }
  *is_local = 0;
  return 0;
}


/* ==== dbg_find_sym_d2 @ 00440450 ==== */

int __cdecl dbg_find_sym_d2(char *name)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  void *sym;
  
  iVar4 = dbg_sym_bsearch(name);
  if (iVar4 != 0) {
    iVar1 = *(int *)(cur_sim + 0x3fdc);
    piVar2 = *(int **)(cur_sim + 0x4030);
    iVar3 = *piVar2;
    piVar6 = piVar2 + iVar4;
    iVar5 = *(int *)(piVar2[iVar4] * 0x20 + 0x18 + iVar1);
    while( true ) {
      if (iVar5 == 0xd2) {
        return piVar2[iVar4];
      }
      iVar4 = iVar4 + 1;
      piVar6 = piVar6 + 1;
      if (iVar3 < iVar4) break;
      sym = (void *)(*piVar6 * 0x20 + iVar1);
      iVar5 = dbg_sym_name_eq(name,sym);
      if (iVar5 == 0) {
        return 0;
      }
      iVar5 = *(int *)((int)sym + 0x18);
    }
  }
  return 0;
}


/* ==== dbg_sym_name_eq @ 004404e0 ==== */

int __cdecl dbg_sym_name_eq(char *name,void *sym)

{
  byte bVar1;
  byte *pbVar2;
  bool bVar3;
  
  pbVar2 = (byte *)dbg_sym_name(sym);
  while( true ) {
    bVar1 = *name;
    bVar3 = bVar1 < *pbVar2;
    if (bVar1 != *pbVar2) break;
    if (bVar1 == 0) {
      return 1;
    }
    bVar1 = name[1];
    bVar3 = bVar1 < pbVar2[1];
    if (bVar1 != pbVar2[1]) break;
    name = name + 2;
    pbVar2 = pbVar2 + 2;
    if (bVar1 == 0) {
      return 1;
    }
  }
  return (uint)(1 - bVar3 == (uint)(bVar3 != 0));
}


/* ==== dbg_sym_bsearch @ 00440540 ==== */

int __cdecl dbg_sym_bsearch(char *name)

{
  int *piVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  int *piVar7;
  byte *pbVar8;
  int iVar9;
  int iVar10;
  bool bVar11;
  
  piVar7 = *(int **)(cur_sim + 0x4030);
  iVar9 = 0;
  if (piVar7 == (int *)0x0) {
    return 0;
  }
  iVar3 = *(int *)(cur_sim + 0x3fdc);
  iVar10 = *piVar7;
  iVar4 = 1;
  iVar6 = 1;
  if (0 < iVar10) {
    do {
      iVar9 = (iVar10 + 1 + iVar6) / 2;
      pbVar5 = (byte *)dbg_sym_name((void *)(piVar7[iVar9] * 0x20 + iVar3));
      pbVar8 = (byte *)name;
      do {
        bVar2 = *pbVar5;
        bVar11 = bVar2 < *pbVar8;
        if (bVar2 != *pbVar8) {
LAB_004405cb:
          iVar4 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
          goto LAB_004405d0;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar5[1];
        bVar11 = bVar2 < pbVar8[1];
        if (bVar2 != pbVar8[1]) goto LAB_004405cb;
        pbVar5 = pbVar5 + 2;
        pbVar8 = pbVar8 + 2;
      } while (bVar2 != 0);
      iVar4 = 0;
LAB_004405d0:
      if (iVar4 == 0) break;
      if (iVar4 < 1) {
        iVar6 = iVar9 + 1;
      }
      else {
        iVar10 = iVar9 + -1;
      }
    } while (iVar6 <= iVar10);
  }
  if (iVar4 != 0) {
    return 0;
  }
  if (iVar9 < 2) {
    return iVar9;
  }
  piVar7 = piVar7 + iVar9;
  do {
    piVar1 = piVar7 + -1;
    piVar7 = piVar7 + -1;
    iVar10 = iVar9 + -1;
    pbVar5 = (byte *)dbg_sym_name((void *)(*piVar1 * 0x20 + iVar3));
    pbVar8 = (byte *)name;
    do {
      bVar2 = *pbVar5;
      bVar11 = bVar2 < *pbVar8;
      if (bVar2 != *pbVar8) {
LAB_00440641:
        iVar6 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
        goto LAB_00440646;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar5[1];
      bVar11 = bVar2 < pbVar8[1];
      if (bVar2 != pbVar8[1]) goto LAB_00440641;
      pbVar5 = pbVar5 + 2;
      pbVar8 = pbVar8 + 2;
    } while (bVar2 != 0);
    iVar6 = 0;
LAB_00440646:
    if (iVar6 != 0) {
      return iVar9;
    }
    iVar9 = iVar10;
    if (iVar10 < 2) {
      return iVar10;
    }
  } while( true );
}


/* ==== dbg_find_macro_of_file @ 00440670 ==== */

int __cdecl dbg_find_macro_of_file(int fileno)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  byte *pbVar6;
  byte *pbVar7;
  bool bVar8;
  int local_8;
  
  local_8 = 0;
  if ((fileno != 0) &&
     (iVar3 = *(int *)(cur_sim + 0x4014) + fileno * 0x20, (*(uint *)(iVar3 + 0x10) & 0x1000) != 0))
  {
    iVar3 = *(int *)(iVar3 + 0x1c);
    if (iVar3 < *(int *)(cur_sim + 0x3fd8)) {
      do {
        pbVar7 = (byte *)(iVar3 * 0x20 + *(int *)(cur_sim + 0x3fdc));
        if (*(int *)(pbVar7 + 0x18) == 0xcb) {
          pbVar6 = &DAT_004c7af0;
          pbVar4 = pbVar7;
          do {
            bVar1 = *pbVar4;
            bVar8 = bVar1 < *pbVar6;
            if (bVar1 != *pbVar6) {
LAB_004406f6:
              iVar5 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
              goto LAB_004406fb;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar4[1];
            bVar8 = bVar1 < pbVar6[1];
            if (bVar1 != pbVar6[1]) goto LAB_004406f6;
            pbVar4 = pbVar4 + 2;
            pbVar6 = pbVar6 + 2;
          } while (bVar1 != 0);
          iVar5 = 0;
LAB_004406fb:
          iVar2 = iVar3;
          if (iVar5 != 0) goto LAB_00440705;
        }
        else {
LAB_00440705:
          iVar2 = local_8;
          if (*(int *)(pbVar7 + 0x10) == fileno) {
            return local_8;
          }
        }
        local_8 = iVar2;
        iVar3 = iVar3 + 1 + *(int *)(pbVar7 + 0x1c);
      } while (iVar3 < *(int *)(cur_sim + 0x3fd8));
    }
  }
  return local_8;
}


/* ==== dbg_resolve_symbol @ 00440730 ==== */

int __cdecl dbg_resolve_symbol(char *name,void *value)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  char *pcVar11;
  bool bVar12;
  bool bVar13;
  int local_20;
  ulong local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_18 = 0;
  local_20 = 0;
  local_14 = -1;
  local_1c = 0;
  if (*name == '@') {
    name = name + 1;
  }
  iVar10 = 0;
  cVar1 = *name;
  while ((cVar1 != '\0' && (cVar1 != '@'))) {
    iVar5 = iVar10 + 1;
    iVar10 = iVar10 + 1;
    cVar1 = name[iVar5];
  }
  if (name[iVar10] == '@') {
    bVar13 = false;
    name[iVar10] = '\0';
    pcVar11 = s_global_004c7af4;
    pbVar4 = (byte *)name;
    do {
      bVar2 = *pbVar4;
      bVar12 = bVar2 < (byte)*pcVar11;
      if (bVar2 != *pcVar11) {
LAB_004407b8:
        iVar5 = (1 - (uint)bVar12) - (uint)(bVar12 != 0);
        goto LAB_004407bd;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar4[1];
      bVar12 = bVar2 < (byte)pcVar11[1];
      if (bVar2 != pcVar11[1]) goto LAB_004407b8;
      pbVar4 = pbVar4 + 2;
      pcVar11 = pcVar11 + 2;
    } while (bVar2 != 0);
    iVar5 = 0;
LAB_004407bd:
    if (iVar5 == 0) {
      local_1c = cdb_frame_pc();
      local_18 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(0,local_1c);
      bVar13 = true;
    }
    else {
      iVar5 = 3;
      if (3 < *(int *)(cur_sim + 0x3fd0)) {
        iVar3 = *(int *)(cur_sim + 0x4014);
        piVar9 = (int *)(iVar3 + 0x7c);
        do {
          if (*piVar9 != 0) {
            pbVar7 = (byte *)(*(int *)(*(int *)(cur_sim + 0x3fdc) + 8 + *piVar9 * 0x20) +
                             *(int *)(cur_sim + 0x3fe4));
            pbVar4 = (byte *)name;
            do {
              bVar2 = *pbVar4;
              bVar12 = bVar2 < *pbVar7;
              if (bVar2 != *pbVar7) {
LAB_00440855:
                iVar6 = (1 - (uint)bVar12) - (uint)(bVar12 != 0);
                goto LAB_0044085a;
              }
              if (bVar2 == 0) break;
              bVar2 = pbVar4[1];
              bVar12 = bVar2 < pbVar7[1];
              if (bVar2 != pbVar7[1]) goto LAB_00440855;
              pbVar4 = pbVar4 + 2;
              pbVar7 = pbVar7 + 2;
            } while (bVar2 != 0);
            iVar6 = 0;
LAB_0044085a:
            if (iVar6 == 0) {
              bVar13 = true;
              local_1c = *(ulong *)(iVar5 * 0x20 + iVar3);
              local_18 = *(int *)(iVar5 * 0x20 + iVar3 + 4);
              break;
            }
          }
          iVar5 = iVar5 + 1;
          piVar9 = piVar9 + 8;
        } while (iVar5 < *(int *)(cur_sim + 0x3fd0));
      }
    }
    name[iVar10] = '@';
    if (!bVar13) {
      iVar5 = cdb_find_file_index(name);
      if (iVar5 == -1) {
        return 0;
      }
      iVar10 = cdb_find_function(name + iVar10 + 1,iVar5);
      if (iVar10 == -1) {
        return 0;
      }
      iVar5 = *(int *)(cur_sim + 0x3fdc);
      *(undefined4 *)((int)value + 0x14) = *(undefined4 *)(iVar5 + 8 + iVar10 * 0x20);
      *(undefined4 *)((int)value + 0x18) = *(undefined4 *)(iVar5 + 0xc + iVar10 * 0x20);
      return iVar10;
    }
    name = name + iVar10 + 1;
  }
  else {
    local_1c = cdb_frame_pc();
    local_18 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(0,local_1c);
  }
  if (*name == '_') {
    pcVar11 = name + 1;
    local_20 = dbg_find_local_label(local_1c,local_18,pcVar11);
    iVar10 = cur_sim;
    if ((local_20 == 0) &&
       (local_20 = dbg_find_macro_local(local_1c,local_18,pcVar11), iVar10 = cur_sim, local_20 == 0)
       ) {
      local_20 = dbg_find_nearest_named(local_1c,pcVar11);
      iVar10 = cur_sim;
    }
  }
  else {
    local_14 = dbg_addr_to_first_sym(local_1c,local_18);
    iVar10 = cur_sim;
    if ((0 < local_14) &&
       (local_20 = dbg_find_scoped_sym(name,local_14), iVar10 = cur_sim, local_20 == 0)) {
      iVar5 = *(int *)(cur_sim + 0x3fe4);
      local_10 = 0;
      iVar3 = *(int *)(*(int *)(cur_sim + 0x3fdc) + 8 + local_14 * 0x20);
      local_8 = 3;
      if (3 < *(int *)(cur_sim + 0x3fd0)) {
        local_c = 0x60;
        do {
          iVar6 = *(int *)(*(int *)(iVar10 + 0x4014) + 0x1c + local_c);
          if ((iVar6 != local_14) && (iVar6 != local_10)) {
            pbVar7 = (byte *)(*(int *)(*(int *)(iVar10 + 0x3fdc) + 8 + iVar6 * 0x20) +
                             *(int *)(iVar10 + 0x3fe4));
            pbVar4 = (byte *)(iVar3 + iVar5);
            do {
              bVar2 = *pbVar4;
              bVar13 = bVar2 < *pbVar7;
              if (bVar2 != *pbVar7) {
LAB_00440b4b:
                iVar8 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
                goto LAB_00440b50;
              }
              if (bVar2 == 0) break;
              bVar2 = pbVar4[1];
              bVar13 = bVar2 < pbVar7[1];
              if (bVar2 != pbVar7[1]) goto LAB_00440b4b;
              pbVar4 = pbVar4 + 2;
              pbVar7 = pbVar7 + 2;
            } while (bVar2 != 0);
            iVar8 = 0;
LAB_00440b50:
            local_10 = iVar6;
            if ((iVar8 == 0) &&
               (local_20 = dbg_find_scoped_sym(name,iVar6), iVar10 = cur_sim, local_20 != 0)) break;
          }
          local_8 = local_8 + 1;
          local_c = local_c + 0x20;
        } while (local_8 < *(int *)(iVar10 + 0x3fd0));
      }
      if (local_20 == 0) {
        iVar5 = *(int *)(*(int *)(iVar10 + 0x3fdc) + 0x14 + local_14 * 0x20);
        while ((iVar5 != 0 &&
               (local_20 = dbg_find_scoped_sym(name,iVar5), iVar10 = cur_sim, local_20 == 0))) {
          iVar5 = *(int *)(*(int *)(cur_sim + 0x3fdc) + 0x14 + iVar5 * 0x20);
        }
      }
    }
  }
  if (local_14 < 0) {
    local_14 = dbg_addr_to_first_sym(local_1c,local_18);
    iVar10 = cur_sim;
  }
  if (local_20 == 0) {
    iVar10 = dbg_find_block_sym(name,local_14);
    if (iVar10 != 0) {
      local_20 = dbg_find_sym_d3(name);
    }
    iVar10 = cur_sim;
    if (((local_20 == 0) && (local_20 = dbg_find_sym_d2(name), iVar10 = cur_sim, local_20 == 0)) &&
       (local_20 = dbg_find_nearest_sorted(local_1c,name), iVar10 = cur_sim, local_20 == 0)) {
      iVar10 = cdb_find_file_index(&empty_str);
      local_20 = cdb_find_function(name,iVar10);
      iVar10 = cur_sim;
      if (local_20 == -1) {
        local_20 = 0;
      }
    }
  }
  if (local_20 != 0) {
    iVar10 = *(int *)(iVar10 + 0x3fdc);
    *(undefined4 *)((int)value + 0x14) = *(undefined4 *)(iVar10 + 8 + local_20 * 0x20);
    *(undefined4 *)((int)value + 0x18) = *(undefined4 *)(iVar10 + 0xc + local_20 * 0x20);
  }
  return local_20;
}


/* ==== dbg_addr_to_first_sym @ 00440bf0 ==== */

int __cdecl dbg_addr_to_first_sym(uint addr,int space)

{
  int iVar1;
  
  iVar1 = addr_to_srcline(addr,space);
  if (iVar1 != 0) {
    return *(int *)(*(int *)(cur_sim + 0x4014) + 0x1c + iVar1 * 0x20);
  }
  return 0;
}


/* ==== dbg_find_sym_d3 @ 00440c20 ==== */

int __cdecl dbg_find_sym_d3(char *name)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  void *sym;
  
  iVar4 = dbg_sym_bsearch(name);
  if (iVar4 != 0) {
    iVar1 = *(int *)(cur_sim + 0x3fdc);
    piVar2 = *(int **)(cur_sim + 0x4030);
    iVar3 = *piVar2;
    piVar6 = piVar2 + iVar4;
    iVar5 = *(int *)(piVar2[iVar4] * 0x20 + 0x18 + iVar1);
    while( true ) {
      if (iVar5 == 0xd3) {
        return piVar2[iVar4];
      }
      iVar4 = iVar4 + 1;
      piVar6 = piVar6 + 1;
      if (iVar3 < iVar4) break;
      sym = (void *)(*piVar6 * 0x20 + iVar1);
      iVar5 = dbg_sym_name_eq(name,sym);
      if (iVar5 == 0) {
        return 0;
      }
      iVar5 = *(int *)((int)sym + 0x18);
    }
  }
  return 0;
}


/* ==== dbg_find_scoped_sym @ 00440cb0 ==== */

int __cdecl dbg_find_scoped_sym(char *name,int fileidx)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  byte *sym;
  bool bVar6;
  
  iVar4 = fileidx;
  if (fileidx < *(int *)(cur_sim + 0x3fd8)) {
    do {
      sym = (byte *)(*(int *)(cur_sim + 0x3fdc) + iVar4 * 0x20);
      if ((*(int *)(sym + 0x18) == 0xc9) && (*(int *)(sym + 0x14) == fileidx)) {
        pbVar5 = &DAT_004c7afc;
        pbVar2 = sym;
        do {
          bVar1 = *pbVar2;
          bVar6 = bVar1 < *pbVar5;
          if (bVar1 != *pbVar5) {
LAB_00440d15:
            iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
            goto LAB_00440d1a;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar2[1];
          bVar6 = bVar1 < pbVar5[1];
          if (bVar1 != pbVar5[1]) goto LAB_00440d15;
          pbVar2 = pbVar2 + 2;
          pbVar5 = pbVar5 + 2;
        } while (bVar1 != 0);
        iVar3 = 0;
LAB_00440d1a:
        if (iVar3 == 0) break;
      }
      if (((*(int *)(sym + 0x18) == 0xd5) && (*(int *)(sym + 0x14) == fileidx)) &&
         (iVar3 = dbg_sym_name_eq(name,sym), iVar3 != 0)) {
        return iVar4;
      }
      iVar4 = iVar4 + 1 + *(int *)(sym + 0x1c);
    } while (iVar4 < *(int *)(cur_sim + 0x3fd8));
  }
  iVar4 = dbg_find_sym_d3(name);
  if ((iVar4 == 0) ||
     (*(int *)(*(int *)(*(int *)(cur_sim + 0x3fdc) + 0x10 + iVar4 * 0x20) * 0x20 + 0x1c +
              *(int *)(cur_sim + 0x4014)) != fileidx)) {
    iVar4 = 0;
  }
  return iVar4;
}


/* ==== dbg_find_block_sym @ 00440da0 ==== */

int __cdecl dbg_find_block_sym(char *name,int fileidx)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  bool bVar7;
  
  iVar4 = fileidx;
  if (*(int *)(cur_sim + 0x3fd8) <= fileidx) {
    return 0;
  }
  do {
    pbVar6 = (byte *)(iVar4 * 0x20 + *(int *)(cur_sim + 0x3fdc));
    if ((*(int *)(pbVar6 + 0x18) == 0xd4) && (*(int *)(pbVar6 + 0x14) == fileidx)) {
      pbVar2 = (byte *)(*(int *)(cur_sim + 0x3fe4) + *(int *)(pbVar6 + 8));
      pbVar5 = (byte *)name;
      do {
        bVar1 = *pbVar5;
        bVar7 = bVar1 < *pbVar2;
        if (bVar1 != *pbVar2) {
LAB_00440e0d:
          iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
          goto LAB_00440e12;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar5[1];
        bVar7 = bVar1 < pbVar2[1];
        if (bVar1 != pbVar2[1]) goto LAB_00440e0d;
        pbVar5 = pbVar5 + 2;
        pbVar2 = pbVar2 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_00440e12:
      if (iVar3 == 0) {
        return iVar4;
      }
    }
    else if ((*(int *)(pbVar6 + 0x18) == 0xca) && (*(int *)(pbVar6 + 0x14) == fileidx)) {
      pbVar2 = &DAT_004c7afc;
      pbVar5 = pbVar6;
      do {
        bVar1 = *pbVar5;
        bVar7 = bVar1 < *pbVar2;
        if (bVar1 != *pbVar2) {
LAB_00440e50:
          iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
          goto LAB_00440e55;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar5[1];
        bVar7 = bVar1 < pbVar2[1];
        if (bVar1 != pbVar2[1]) goto LAB_00440e50;
        pbVar5 = pbVar5 + 2;
        pbVar2 = pbVar2 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_00440e55:
      if (iVar3 == 0) {
        return 0;
      }
    }
    iVar4 = iVar4 + 1 + *(int *)(pbVar6 + 0x1c);
    if (*(int *)(cur_sim + 0x3fd8) <= iVar4) {
      return 0;
    }
  } while( true );
}


/* ==== dbg_find_macro_local @ 00440e90 ==== */

int __cdecl dbg_find_macro_local(uint addr,int space,char *name)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  byte *sym;
  bool bVar7;
  int local_8;
  
  if (*(int *)(cur_sim + 0x3fd8) == 0) {
    return 0;
  }
  local_8 = 0;
  iVar2 = addr_to_srcline(addr,space);
  if (((iVar2 == 0) || (iVar2 = dbg_find_macro_of_file(iVar2), iVar2 == 0)) ||
     (iVar5 = cur_sim, *(int *)(cur_sim + 0x3fd8) <= iVar2)) {
    return 0;
  }
  do {
    sym = (byte *)(*(int *)(iVar5 + 0x3fdc) + iVar2 * 0x20);
    if (*(int *)(sym + 0x18) == 0xcb) {
      pbVar6 = &DAT_004c7af0;
      pbVar3 = sym;
      do {
        bVar1 = *pbVar3;
        bVar7 = bVar1 < *pbVar6;
        if (bVar1 != *pbVar6) {
LAB_00440f38:
          iVar4 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
          goto LAB_00440f3d;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar7 = bVar1 < pbVar6[1];
        if (bVar1 != pbVar6[1]) goto LAB_00440f38;
        pbVar3 = pbVar3 + 2;
        pbVar6 = pbVar6 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_00440f3d:
      if (iVar4 == 0) {
        local_8 = local_8 + 1;
      }
      else {
        pbVar6 = &DAT_004c7b00;
        pbVar3 = sym;
        do {
          bVar1 = *pbVar3;
          bVar7 = bVar1 < *pbVar6;
          if (bVar1 != *pbVar6) {
LAB_00440f72:
            iVar4 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
            goto LAB_00440f77;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar3[1];
          bVar7 = bVar1 < pbVar6[1];
          if (bVar1 != pbVar6[1]) goto LAB_00440f72;
          pbVar3 = pbVar3 + 2;
          pbVar6 = pbVar6 + 2;
        } while (bVar1 != 0);
        iVar4 = 0;
LAB_00440f77:
        if ((iVar4 == 0) && (local_8 = local_8 + -1, local_8 == 0)) {
          return 0;
        }
      }
    }
    else if (((local_8 == 1) && (*(int *)(sym + 0x18) == 0xd7)) &&
            (iVar4 = dbg_sym_name_eq(name,sym), iVar5 = cur_sim, iVar4 != 0)) {
      return iVar2;
    }
    iVar2 = iVar2 + 1 + *(int *)(sym + 0x1c);
    if (*(int *)(iVar5 + 0x3fd8) <= iVar2) {
      return 0;
    }
  } while( true );
}


/* ==== dbg_find_local_label @ 00440fe0 ==== */

int __cdecl dbg_find_local_label(uint addr,int space,char *name)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  bool bVar10;
  uint local_10;
  int local_c;
  
  if (*(int *)(cur_sim + 0x3fd8) == 0) {
    return 0;
  }
  iVar3 = dbg_addr_to_first_sym(addr,space);
  local_10 = 0;
  iVar7 = cur_sim;
  iVar6 = iVar3;
  local_c = iVar3;
  if (iVar3 < *(int *)(cur_sim + 0x3fd8)) {
    do {
      pbVar9 = (byte *)(*(int *)(iVar7 + 0x3fdc) + iVar6 * 0x20);
      if ((*(int *)(pbVar9 + 0x18) == 0xc9) && (*(int *)(pbVar9 + 0x14) == iVar3)) {
        pbVar8 = &DAT_004c7afc;
        pbVar4 = pbVar9;
        do {
          bVar1 = *pbVar4;
          bVar10 = bVar1 < *pbVar8;
          if (bVar1 != *pbVar8) {
LAB_00441080:
            iVar5 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
            goto LAB_00441085;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar4[1];
          bVar10 = bVar1 < pbVar8[1];
          if (bVar1 != pbVar8[1]) goto LAB_00441080;
          pbVar4 = pbVar4 + 2;
          pbVar8 = pbVar8 + 2;
        } while (bVar1 != 0);
        iVar5 = 0;
LAB_00441085:
        if (iVar5 == 0) break;
      }
      if ((*(int *)(pbVar9 + 0x18) == 0xd5) && (*(int *)(pbVar9 + 0x14) == iVar3)) {
        uVar2 = *(uint *)(pbVar9 + 8);
        iVar5 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(*(undefined4 *)(pbVar9 + 0xc),uVar2)
        ;
        iVar7 = cur_sim;
        if ((iVar5 == space) && ((local_10 < uVar2 && (uVar2 <= addr)))) {
          local_10 = uVar2;
          local_c = iVar6;
        }
      }
      iVar6 = iVar6 + 1 + *(int *)(pbVar9 + 0x1c);
    } while (iVar6 < *(int *)(iVar7 + 0x3fd8));
  }
  local_c = *(int *)(*(int *)(iVar7 + 0x3fdc) + 0x1c + local_c * 0x20) + 1 + local_c;
  if (*(int *)(iVar7 + 0x3fd8) <= local_c) {
    return 0;
  }
  do {
    pbVar9 = (byte *)(*(int *)(iVar7 + 0x3fdc) + local_c * 0x20);
    iVar6 = *(int *)(pbVar9 + 0x18);
    if (iVar6 == 0xc9) {
      pbVar8 = &DAT_004c7afc;
      pbVar4 = pbVar9;
      do {
        bVar1 = *pbVar4;
        bVar10 = bVar1 < *pbVar8;
        if (bVar1 != *pbVar8) {
LAB_00441151:
          iVar3 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
          goto LAB_00441156;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar4[1];
        bVar10 = bVar1 < pbVar8[1];
        if (bVar1 != pbVar8[1]) goto LAB_00441151;
        pbVar4 = pbVar4 + 2;
        pbVar8 = pbVar8 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_00441156:
      iVar7 = cur_sim;
      if (iVar3 == 0) {
        return 0;
      }
    }
    if (iVar6 == 0xd5) {
      return 0;
    }
    if ((iVar6 == 0xd6) && (iVar6 = dbg_sym_name_eq(name,pbVar9), iVar7 = cur_sim, iVar6 != 0)) {
      return local_c;
    }
    local_c = local_c + 1 + *(int *)(pbVar9 + 0x1c);
    if (*(int *)(iVar7 + 0x3fd8) <= local_c) {
      return 0;
    }
  } while( true );
}


/* ==== dbg_find_nearest_named @ 004411c0 ==== */

int __cdecl dbg_find_nearest_named(uint addr,char *name)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  void *sym;
  int iVar4;
  int local_4;
  
  iVar4 = 0;
  uVar3 = 0xffffffff;
  local_4 = 0;
  if (0 < *(int *)(cur_sim + 0x3fd8)) {
    do {
      sym = (void *)(*(int *)(cur_sim + 0x3fdc) + iVar4 * 0x20);
      if (((*(int *)((int)sym + 0x18) == 0xd5) || (*(int *)((int)sym + 0x18) == 0xd7)) &&
         (iVar1 = dbg_sym_name_eq(name,sym), iVar1 != 0)) {
        uVar2 = *(uint *)((int)sym + 8);
        if (uVar2 < addr) {
          uVar2 = addr - uVar2;
        }
        else {
          uVar2 = uVar2 - addr;
        }
        if (uVar2 < uVar3) {
          uVar3 = uVar2;
          local_4 = iVar4;
        }
      }
      iVar4 = iVar4 + 1 + *(int *)((int)sym + 0x1c);
    } while (iVar4 < *(int *)(cur_sim + 0x3fd8));
  }
  return local_4;
}


/* ==== dbg_find_nearest_sorted @ 00441250 ==== */

int __cdecl dbg_find_nearest_sorted(uint addr,char *name)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  void *sym;
  uint uVar6;
  int *piVar7;
  uint local_10;
  int local_c;
  
  local_10 = 0xffffffff;
  local_c = 0;
  iVar4 = dbg_sym_bsearch(name);
  if (iVar4 != 0) {
    iVar1 = *(int *)(cur_sim + 0x3fdc);
    piVar2 = *(int **)(cur_sim + 0x4030);
    iVar3 = *piVar2;
    piVar7 = piVar2 + iVar4;
    sym = (void *)(piVar2[iVar4] * 0x20 + iVar1);
    do {
      iVar5 = *(int *)((int)sym + 0x18);
      if (((iVar5 == 0xd5) || (iVar5 == 0xd3)) || (iVar5 == 2)) {
        uVar6 = *(uint *)((int)sym + 8);
        if (uVar6 < addr) {
          uVar6 = addr - uVar6;
        }
        else {
          uVar6 = uVar6 - addr;
        }
        if (uVar6 < local_10) {
          local_c = *piVar7;
          local_10 = uVar6;
        }
      }
      iVar4 = iVar4 + 1;
      piVar7 = piVar7 + 1;
      if (iVar3 < iVar4) {
        return local_c;
      }
      sym = (void *)(*piVar7 * 0x20 + iVar1);
      iVar5 = dbg_sym_name_eq(name,sym);
    } while (iVar5 != 0);
  }
  return local_c;
}


/* ==== dbg_addr_to_file_sym @ 00441320 ==== */

int __cdecl dbg_addr_to_file_sym(uint addr,int space)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = 0;
  iVar1 = addr_to_srcline(addr,space);
  iVar5 = iVar4;
  if (iVar1 != 0) {
    iVar3 = 0;
    if (0 < *(int *)(cur_sim + 0x3fd8)) {
      do {
        iVar2 = iVar3 * 0x20 + *(int *)(cur_sim + 0x3fdc);
        iVar5 = iVar3;
        if (iVar1 == *(int *)(iVar2 + 0x10)) break;
        iVar3 = iVar3 + 1 + *(int *)(iVar2 + 0x1c);
        iVar5 = iVar4;
      } while (iVar3 < *(int *)(cur_sim + 0x3fd8));
    }
  }
  if (iVar5 == 0) {
LAB_0044139f:
    iVar4 = -1;
  }
  else {
    iVar1 = 0;
    do {
      iVar4 = iVar1;
      iVar1 = *(int *)(iVar4 * 0x20 + 0x18 + *(int *)(cur_sim + 0x3fdc));
      if ((iVar1 != 200) && (iVar1 != 0x67)) goto LAB_0044139f;
      iVar1 = *(int *)(iVar4 * 0x20 + *(int *)(cur_sim + 0x3fdc) + 8);
    } while (iVar1 <= iVar5);
  }
  return iVar4;
}


/* ==== dbg_addr_to_fileno @ 004413b0 ==== */

int __cdecl dbg_addr_to_fileno(uint addr,int space)

{
  int iVar1;
  
  iVar1 = dbg_addr_to_file_sym(addr,space);
  if (-1 < iVar1) {
    return *(int *)(*(int *)(cur_sim + 0x3fdc) + 0x14 + iVar1 * 0x20);
  }
  return -1;
}


/* ==== dbg_addr_to_filename @ 004413e0 ==== */

char * __cdecl dbg_addr_to_filename(uint addr,int space)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = dbg_addr_to_file_sym(addr,space);
  if (-1 < iVar1) {
    pcVar2 = dbg_aux_name((void *)(*(int *)(cur_sim + 0x3fdc) + (iVar1 + 1) * 0x20));
    return pcVar2;
  }
  return &empty_str;
}


/* ==== dbg_addr_to_line_index @ 00441420 ==== */

int __cdecl dbg_addr_to_line_index(uint addr,int space)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  
  iVar1 = addr_to_srcline(addr,space);
  iVar2 = -1;
  if (iVar1 != 0) {
    iVar3 = iVar1 * 0x20 + *(int *)(cur_sim + 0x4014);
    iVar1 = *(int *)(iVar3 + 0x14);
    if (iVar1 != 0) {
      iVar3 = *(int *)(iVar3 + 0x18);
      iVar2 = iVar3 + -1 + iVar1;
      if (iVar3 < iVar2) {
        puVar4 = (uint *)(*(int *)(cur_sim + 0x3ff0) + iVar2 * 0xc);
        do {
          if ((puVar4[2] != 0) && (*puVar4 <= addr)) {
            return iVar2;
          }
          iVar2 = iVar2 + -1;
          puVar4 = puVar4 + -3;
        } while (iVar3 < iVar2);
      }
    }
  }
  return iVar2;
}


/* ==== dbg_addr_to_line @ 00441490 ==== */

int __cdecl dbg_addr_to_line(uint addr,int space)

{
  int iVar1;
  
  iVar1 = dbg_addr_to_line_index(addr,space);
  if (-1 < iVar1) {
    return *(int *)(*(int *)(cur_sim + 0x3ff0) + 8 + iVar1 * 0xc);
  }
  return 0;
}


/* ==== dbg_fileno_to_name @ 004414c0 ==== */

char * __cdecl dbg_fileno_to_name(int fileno)

{
  ulong addr;
  int space;
  
  if (fileno < 0) {
    space = 0;
    addr = cdb_frame_pc();
    fileno = dbg_addr_to_fileno(addr,space);
    if (fileno < 0) {
      return (char *)0x0;
    }
  }
  if (*(int *)(cur_sim + 0x401c) <= fileno) {
    return (char *)0x0;
  }
  return *(char **)(*(int *)(cur_sim + 0x4020) + 8 + fileno * 0xc);
}


/* ==== dbg_format_addr @ 00441500 ==== */

char * __cdecl dbg_format_addr(int space,uint addr)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  char *va2;
  char *fmt;
  undefined1 *va1;
  
  uVar2 = addr;
  iVar1 = space;
  g_addr_str_buf = 0;
  iVar3 = dbg_find_label(addr,space,(uint *)&space);
  va1 = &DAT_004c7b28;
  if (space == 0) {
    va1 = &empty_str;
  }
  if (iVar3 == 0) {
    va2 = (char *)0x0;
    iVar3 = 0;
  }
  else {
    va2 = dbg_sym_name((void *)(*(int *)(cur_sim + 0x3fdc) + iVar3 * 0x20));
    iVar3 = uVar2 - *(int *)(*(int *)(cur_sim + 0x3fdc) + 8 + iVar3 * 0x20);
  }
  if (va2 == (char *)0x0) {
    fmt = &empty_str;
  }
  else {
    fmt = s__s__s__200s_004c7b18;
    if (iVar3 != 0) {
      fmt = s__s___s__200s__lu__004c7b04;
    }
  }
  sprintf(&g_addr_str_buf,fmt,(&g_space_names)[iVar1],va1,va2,iVar3);
  return &g_addr_str_buf;
}


/* ==== dbg_build_indexes @ 004415c0 ==== */

int dbg_build_indexes(void)

{
  uint *puVar1;
  int iVar2;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint *puVar7;
  uint num;
  uint *puVar8;
  int local_c;
  uint *local_8;
  
  num = 0;
  if ((*(int *)(cur_sim + 0x3fd4) != 0) && (*(int *)(cur_sim + 0x3fd8) != 0)) {
    if (*(void **)(cur_sim + 0x402c) != (void *)0x0) {
      dsp_free(*(void **)(cur_sim + 0x402c));
      *(undefined4 *)(cur_sim + 0x402c) = 0;
    }
    if (*(void **)(cur_sim + 0x4030) != (void *)0x0) {
      dsp_free(*(void **)(cur_sim + 0x4030));
      *(undefined4 *)(cur_sim + 0x4030) = 0;
    }
    dsp_alloc(*(int *)(cur_sim + 0x3fd8) << 2,0);
    *(undefined4 *)(cur_sim + 0x402c) = extraout_EAX;
    if (*(int *)(cur_sim + 0x402c) == 0) {
      return -1;
    }
    dsp_alloc(*(int *)(cur_sim + 0x3fd8) << 2,0);
    *(undefined4 *)(cur_sim + 0x4030) = extraout_EAX_00;
    puVar7 = *(uint **)(cur_sim + 0x4030);
    if (puVar7 == (uint *)0x0) {
      return -1;
    }
    puVar1 = *(uint **)(cur_sim + 0x402c);
    iVar2 = *(int *)(cur_sim + 0x3fdc);
    uVar3 = 0;
    if (0 < *(int *)(cur_sim + 0x3fd8)) {
      iVar4 = cur_sim;
      puVar8 = puVar1;
      do {
        iVar6 = uVar3 * 0x20 + iVar2;
        iVar5 = *(int *)(iVar6 + 0x18);
        if ((((iVar5 == 0xd5) || (iVar5 == 0xd3)) || (iVar5 == 2)) ||
           ((iVar5 == 0xd2 || (iVar5 == 0xd6)))) {
          num = num + 1;
          puVar8 = puVar8 + 1;
          *(uint *)(((int)puVar7 - (int)puVar1) + (int)puVar8) = uVar3;
          *puVar8 = uVar3;
          iVar4 = cur_sim;
        }
        uVar3 = uVar3 + 1 + *(int *)(iVar6 + 0x1c);
      } while ((int)uVar3 < *(int *)(iVar4 + 0x3fd8));
    }
    *puVar7 = num;
    *puVar1 = num;
    qsort(puVar1 + 1,num,4,hid_4417e0);
    qsort(puVar7 + 1,num,4,hid_441890);
    uVar3 = 1;
    puVar1[num + 1] = 1;
    local_c = num + 2;
    if (0 < (int)num) {
      local_8 = puVar1 + local_c;
      do {
        iVar4 = puVar1[uVar3] * 0x20 + iVar2;
        uVar3 = uVar3 + 1;
        if ((int)num < (int)uVar3) break;
        puVar7 = puVar1 + uVar3;
        do {
          iVar5 = *puVar7 * 0x20 + iVar2;
          if ((*(int *)(iVar4 + 0xc) != *(int *)(iVar5 + 0xc)) ||
             (*(int *)(iVar4 + 0x10) != *(int *)(iVar5 + 0x10))) {
            local_c = local_c + 1;
            *local_8 = uVar3;
            local_8 = local_8 + 1;
            break;
          }
          uVar3 = uVar3 + 1;
          puVar7 = puVar7 + 1;
        } while ((int)uVar3 <= (int)num);
      } while ((int)uVar3 <= (int)num);
    }
    puVar1[local_c] = uVar3;
  }
  return 0;
}


/* ==== hid_4417e0 @ 004417e0 ==== */

int hid_4417e0(int *param_1,int *param_2)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  void *sym;
  void *sym_00;
  bool bVar4;
  
  sym_00 = (void *)(*param_1 * 0x20 + *(int *)(cur_sim + 0x3fdc));
  sym = (void *)(*param_2 * 0x20 + *(int *)(cur_sim + 0x3fdc));
  if (*(int *)((int)sym_00 + 0xc) != *(int *)((int)sym + 0xc)) {
    return ((*(int *)((int)sym_00 + 0xc) <= *(int *)((int)sym + 0xc)) - 1 & 2) - 1;
  }
  if (*(int *)((int)sym_00 + 0x10) != *(int *)((int)sym + 0x10)) {
    return *(int *)((int)sym_00 + 0x10) - *(int *)((int)sym + 0x10);
  }
  if (*(uint *)((int)sym + 8) != *(uint *)((int)sym_00 + 8)) {
    return (-(uint)(*(uint *)((int)sym + 8) < *(uint *)((int)sym_00 + 8)) & 2) - 1;
  }
  pbVar2 = (byte *)dbg_sym_name(sym);
  pbVar3 = (byte *)dbg_sym_name(sym_00);
  while( true ) {
    bVar1 = *pbVar3;
    bVar4 = bVar1 < *pbVar2;
    if (bVar1 != *pbVar2) break;
    if (bVar1 == 0) {
      return 0;
    }
    bVar1 = pbVar3[1];
    bVar4 = bVar1 < pbVar2[1];
    if (bVar1 != pbVar2[1]) break;
    pbVar3 = pbVar3 + 2;
    pbVar2 = pbVar2 + 2;
    if (bVar1 == 0) {
      return 0;
    }
  }
  return (1 - (uint)bVar4) - (uint)(bVar4 != 0);
}


/* ==== hid_441890 @ 00441890 ==== */

uint hid_441890(int *param_1,int *param_2)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  uint uVar4;
  void *sym;
  void *sym_00;
  bool bVar5;
  
  sym_00 = (void *)(*param_1 * 0x20 + *(int *)(cur_sim + 0x3fdc));
  sym = (void *)(*param_2 * 0x20 + *(int *)(cur_sim + 0x3fdc));
  pbVar2 = (byte *)dbg_sym_name(sym_00);
  pbVar3 = (byte *)dbg_sym_name(sym);
  do {
    bVar1 = *pbVar2;
    bVar5 = bVar1 < *pbVar3;
    if (bVar1 != *pbVar3) {
LAB_004418f1:
      uVar4 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
      goto LAB_004418f6;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar2[1];
    bVar5 = bVar1 < pbVar3[1];
    if (bVar1 != pbVar3[1]) goto LAB_004418f1;
    pbVar2 = pbVar2 + 2;
    pbVar3 = pbVar3 + 2;
  } while (bVar1 != 0);
  uVar4 = 0;
LAB_004418f6:
  if (uVar4 == 0) {
    uVar4 = (uint)(*(int *)((int)sym + 0x10) < *(int *)((int)sym_00 + 0x10));
  }
  return uVar4;
}


/* ==== dbg_load_cld @ 00441910 ==== */

int __cdecl dbg_load_cld(int dev,char *filename)

{
  char cVar1;
  code *pcVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  void *extraout_EAX;
  undefined4 extraout_EAX_00;
  int iVar7;
  uint uVar8;
  uint uVar9;
  char *pcVar10;
  char *pcVar11;
  
  fopen(filename,&DAT_004c5ff4);
  uVar6 = cur_dev;
  uVar5 = cur_itype;
  uVar4 = cur_dtype;
  uVar3 = cur_sim;
  g_cld_fp = extraout_EAX;
  if (extraout_EAX == (void *)0x0) {
    expr_error2(s_cannot_open_input_file_004c7aa4,filename);
    return -1;
  }
  cur_dev = *(int **)(dev_tab + dev * 4);
  cur_itype = *(int *)(itype_tab + *cur_dev * 4);
  cur_dtype = *(undefined4 *)(chiptype_tab + *cur_dev * 4);
  cur_sim = *(int *)(dev_state_tab + dev * 4);
  if (*(void **)(cur_sim + 0x4018) != (void *)0x0) {
    dsp_free(*(void **)(cur_sim + 0x4018));
    *(undefined4 *)(cur_sim + 0x4018) = 0;
  }
  uVar8 = 0xffffffff;
  pcVar10 = filename;
  do {
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    cVar1 = *pcVar10;
    pcVar10 = pcVar10 + 1;
  } while (cVar1 != '\0');
  dsp_alloc(~uVar8,0);
  *(undefined4 *)(cur_sim + 0x4018) = extraout_EAX_00;
  if (*(char **)(cur_sim + 0x4018) == (char *)0x0) {
    return -1;
  }
  uVar8 = 0xffffffff;
  do {
    pcVar10 = filename;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar10 = filename + 1;
    cVar1 = *filename;
    filename = pcVar10;
  } while (cVar1 != '\0');
  uVar8 = ~uVar8;
  pcVar10 = pcVar10 + -uVar8;
  pcVar11 = *(char **)(cur_sim + 0x4018);
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
    pcVar10 = pcVar10 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar11 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    pcVar11 = pcVar11 + 1;
  }
  iVar7 = dbg_read_filhdr();
  if (iVar7 < 0) {
LAB_00441a5d:
    iVar7 = -1;
  }
  else {
    iVar7 = dbg_read_strtab();
    if (iVar7 < 0) goto LAB_00441a5d;
    iVar7 = dbg_read_sections();
    if (iVar7 < 0) goto LAB_00441a5d;
    iVar7 = dbg_read_symbols();
    if (iVar7 < 0) goto LAB_00441a5d;
    iVar7 = dbg_read_linenos();
    if (iVar7 < 0) goto LAB_00441a5d;
    iVar7 = 0;
  }
  if (iVar7 == 0) {
    dbg_fix_symbol_classes();
    dbg_set_section_line_start();
    dbg_fix_section_line_range();
    dbg_number_symbols();
    iVar7 = dbg_load_source_files();
    if (iVar7 == 0) {
      dbg_build_line_map(*(uint *)(cur_sim + 0x3fec),*(void **)(cur_sim + 0x3ff0),
                         *(int **)(cur_sim + 0x4048));
      iVar7 = dbg_build_indexes();
    }
  }
  fclose(g_cld_fp);
  if (-1 < iVar7) {
    if ((*(int *)(cur_sim + 0x3fd4) != 0) && (*(int *)(cur_sim + 0x3fd8) != 0)) {
      host_io_init();
    }
    if (-1 < iVar7) goto LAB_00441ae6;
  }
  dbg_free();
LAB_00441ae6:
  if ((*(undefined4 **)(cur_itype + 0x1c) != (undefined4 *)0x0) &&
     (pcVar2 = (code *)**(undefined4 **)(cur_itype + 0x1c), pcVar2 != (code *)0x0)) {
    (*pcVar2)();
  }
  cur_dtype = uVar4;
  cur_dev = (int *)uVar6;
  cur_sim = uVar3;
  cur_itype = uVar5;
  return iVar7;
}


/* ==== dbg_read_filhdr @ 00441b30 ==== */

int dbg_read_filhdr(void)

{
  uint uVar1;
  
  fseek(g_cld_fp,0,0);
  uVar1 = fread_swap32(&g_cld_filhdr,0x1c,1,g_cld_fp);
  if (uVar1 != 1) {
    return -1;
  }
  *(int *)(cur_sim + 0x3fd0) = DAT_005021d4 + 1;
  *(undefined4 *)(cur_sim + 0x3fd8) = DAT_005021e0;
  *(undefined4 *)(cur_sim + 0x3fd4) = DAT_005021dc;
  return 0;
}


/* ==== dbg_read_strtab @ 00441ba0 ==== */

int dbg_read_strtab(void)

{
  int iVar1;
  uint uVar2;
  undefined4 extraout_EAX;
  int offset;
  
  if (*(void **)(cur_sim + 0x3fe4) != (void *)0x0) {
    dsp_free(*(void **)(cur_sim + 0x3fe4));
    *(undefined4 *)(cur_sim + 0x3fe4) = 0;
  }
  offset = *(int *)(cur_sim + 0x3fd4) + *(int *)(cur_sim + 0x3fd8) * 0x20;
  iVar1 = fseek(g_cld_fp,offset,0);
  if (iVar1 != 0) {
    expr_error(s_cannot_seek_to_string_table_leng_004c7b84);
    return -1;
  }
  uVar2 = fread_swap32((char *)(cur_sim + 0x3fe8),4,1,g_cld_fp);
  if (uVar2 == 1) {
    if ((*(byte *)((int)g_cld_fp + 0xc) & 0x10) == 0) {
      if (*(ulong *)(cur_sim + 0x3fe8) != 0) {
        dsp_alloc(*(ulong *)(cur_sim + 0x3fe8),0);
        *(undefined4 *)(cur_sim + 0x3fe4) = extraout_EAX;
        if (*(int *)(cur_sim + 0x3fe4) == 0) {
          return -1;
        }
        iVar1 = fseek(g_cld_fp,offset,0);
        if (iVar1 != 0) {
          expr_error(s_cannot_seek_to_string_table_004c7b48);
          return -1;
        }
        uVar2 = fread(*(void **)(cur_sim + 0x3fe4),*(uint *)(cur_sim + 0x3fe8),1,g_cld_fp);
        if (uVar2 != 1) {
          expr_error(s_cannot_read_string_table_004c7b2c);
          return -1;
        }
      }
      return 0;
    }
  }
  else if ((*(byte *)((int)g_cld_fp + 0xc) & 0x10) == 0) {
    expr_error(s_cannot_read_string_table_length_004c7b64);
    return -1;
  }
  *(undefined4 *)(cur_sim + 0x3fe8) = 0;
  return 0;
}


/* ==== dbg_read_sections @ 00441d10 ==== */

int dbg_read_sections(void)

{
  undefined4 *puVar1;
  undefined4 extraout_EAX;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  char local_34 [8];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_1c;
  undefined4 local_18;
  int local_8;
  uint local_4;
  
  if (*(void **)(cur_sim + 0x4014) != (void *)0x0) {
    dsp_free(*(void **)(cur_sim + 0x4014));
    *(undefined4 *)(cur_sim + 0x4014) = 0;
  }
  if (*(int *)(cur_sim + 0x3fd0) != 0) {
    dsp_alloc(*(int *)(cur_sim + 0x3fd0) << 5,0);
    *(undefined4 *)(cur_sim + 0x4014) = extraout_EAX;
  }
  puVar1 = *(undefined4 **)(cur_sim + 0x4014);
  if (puVar1 == (undefined4 *)0x0) {
    return -1;
  }
  puVar6 = &g_null_section;
  puVar8 = puVar1;
  for (iVar5 = 8; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar8 = puVar8 + 1;
  }
  iVar7 = 1;
  iVar9 = 0;
  iVar5 = DAT_005021e4 + 0x1c;
  if (*(int *)(cur_sim + 0x3fd0) < 2) {
    return 0;
  }
  while( true ) {
    iVar2 = fseek(g_cld_fp,iVar5,0);
    if (iVar2 != 0) {
      expr_error(s_cannot_seek_to_section_headers_004c7bc4);
      return -1;
    }
    uVar3 = fread_swap32(local_34,0x34,1,g_cld_fp);
    if (uVar3 != 1) break;
    iVar5 = iVar5 + 0x34;
    puVar1[8] = local_2c;
    puVar1[9] = local_28;
    uVar4 = local_24;
    if ((local_4 & 0x400) == 0) {
      uVar4 = local_1c;
    }
    puVar1[10] = uVar4;
    puVar1[0xc] = local_4;
    puVar1[0xd] = local_8;
    puVar1[0xe] = iVar9;
    puVar1[0xb] = local_18;
    puVar1[0xf] = 0;
    if (iVar7 != 1) {
      iVar9 = iVar9 + local_8;
    }
    iVar7 = iVar7 + 1;
    puVar1 = puVar1 + 8;
    if (*(int *)(cur_sim + 0x3fd0) <= iVar7) {
      return 0;
    }
  }
  expr_error(s_cannot_read_section_headers_004c7ba8);
  return -1;
}


/* ==== dbg_build_line_map @ 00441ea0 ==== */

void __cdecl dbg_build_line_map(uint nlines,void *lines,int *map)

{
  int iVar1;
  int *piVar2;
  int fileno;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  fileno = 0;
  iVar1 = 0;
  piVar2 = map;
  if (0 < (int)nlines) {
    do {
      *piVar2 = iVar1;
      piVar2[1] = 0;
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 2;
    } while (iVar1 < (int)nlines);
  }
  iVar1 = cur_sim;
  if (0 < *(int *)(cur_sim + 0x3fd8)) {
    do {
      iVar3 = iVar4 * 0x20 + *(int *)(iVar1 + 0x3fdc);
      if ((*(int *)(iVar3 + 0x18) == 200) || (*(int *)(iVar3 + 0x18) == 0x67)) {
        fileno = *(int *)(iVar3 + 0x14);
      }
      if (((1 < *(int *)(iVar3 + 0x10)) && (0 < *(int *)(iVar3 + 0x1c))) &&
         (*(int *)((iVar4 + 1) * 0x20 + *(int *)(iVar1 + 0x3fdc) + 8) != 0)) {
        dbg_map_section_lines(*(int *)(iVar3 + 0x10),map,fileno);
        iVar1 = cur_sim;
      }
      iVar4 = iVar4 + 1 + *(int *)(iVar3 + 0x1c);
    } while (iVar4 < *(int *)(iVar1 + 0x3fd8));
  }
  qsort(map,nlines,8,hid_441f50);
  return;
}


/* ==== hid_441f50 @ 00441f50 ==== */

int hid_441f50(int *param_1,int *param_2)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if ((uint)param_2[1] < (uint)param_1[1]) {
    return 1;
  }
  if ((uint)param_1[1] < (uint)param_2[1]) {
    return -1;
  }
  iVar2 = *(int *)(cur_sim + 0x3ff0);
  puVar1 = (uint *)(iVar2 + *param_1 * 0xc);
  uVar3 = *(uint *)(iVar2 + 8 + *param_2 * 0xc);
  uVar4 = puVar1[2];
  if (uVar3 < uVar4) {
    return 1;
  }
  if (uVar4 < uVar3) {
    return -1;
  }
  uVar3 = *puVar1;
  uVar4 = *(uint *)(iVar2 + *param_2 * 0xc);
  if (uVar4 < uVar3) {
    return 1;
  }
  return -(uint)(uVar3 < uVar4);
}


/* ==== dbg_map_section_lines @ 00441fc0 ==== */

void __cdecl dbg_map_section_lines(int secno,int *map,int fileno)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = *(int *)(cur_sim + 0x4014) + secno * 0x20;
  iVar3 = *(int *)(iVar1 + 0x14);
  if (iVar3 != 0) {
    iVar1 = *(int *)(iVar1 + 0x18);
    iVar3 = iVar3 + iVar1;
    if (iVar1 < iVar3) {
      iVar3 = iVar3 - iVar1;
      piVar2 = map + iVar1 * 2 + 1;
      do {
        *piVar2 = fileno;
        piVar2 = piVar2 + 2;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  return;
}


/* ==== dbg_read_linenos @ 00442000 ==== */

int dbg_read_linenos(void)

{
  int iVar1;
  uint uVar2;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  char local_34 [36];
  long local_10;
  uint local_8;
  
  iVar1 = fseek(g_cld_fp,DAT_005021e4 + 0x1c,0);
  if (iVar1 != 0) {
    expr_error(s_cannot_seek_to_section_headers_004c7bc4);
    return -1;
  }
  uVar2 = fread_swap32(local_34,0x34,1,g_cld_fp);
  if (uVar2 != 1) {
    expr_error(s_cannot_read_section_headers_004c7ba8);
    return -1;
  }
  iVar1 = fseek(g_cld_fp,local_10,0);
  if (iVar1 != 0) {
    expr_error(s_cannot_seek_to_line_number_recor_004c7c04);
    return -1;
  }
  if (*(void **)(cur_sim + 0x3ff0) != (void *)0x0) {
    dsp_free(*(void **)(cur_sim + 0x3ff0));
    *(undefined4 *)(cur_sim + 0x3ff0) = 0;
  }
  if (*(void **)(cur_sim + 0x4048) != (void *)0x0) {
    dsp_free(*(void **)(cur_sim + 0x4048));
    *(undefined4 *)(cur_sim + 0x4048) = 0;
  }
  *(uint *)(cur_sim + 0x3fec) = local_8;
  if (local_8 != 0) {
    dsp_alloc(local_8 << 3,0);
    *(undefined4 *)(cur_sim + 0x4048) = extraout_EAX;
    if (*(int *)(cur_sim + 0x4048) == 0) {
      return -1;
    }
    dsp_alloc(local_8 * 0xc,0);
    *(undefined4 *)(cur_sim + 0x3ff0) = extraout_EAX_00;
    if (*(char **)(cur_sim + 0x3ff0) == (char *)0x0) {
      return -1;
    }
    uVar2 = fread_swap32(*(char **)(cur_sim + 0x3ff0),0xc,local_8,g_cld_fp);
    if (uVar2 != local_8) {
      expr_error(s_cannot_read_line_number_records_004c7be4);
      return -1;
    }
    dbg_fix_linenos(local_10,*(void **)(cur_sim + 0x3ff0),local_8);
  }
  return 0;
}


/* ==== dbg_fix_linenos @ 004421c0 ==== */

void __cdecl dbg_fix_linenos(int lnnoptr,void *lines,uint nlines)

{
  uint uVar1;
  int *piVar2;
  byte bVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  byte *pbVar8;
  int iVar9;
  bool bVar10;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  undefined4 local_8;
  undefined4 local_4;
  
  local_1c = 0;
  local_14 = 0;
  local_18 = 0;
  if (0 < *(int *)(cur_sim + 0x3fd8)) {
    do {
      pbVar7 = (byte *)(local_18 * 0x20 + *(int *)(cur_sim + 0x3fdc));
      iVar9 = (local_18 + 1) * 0x20 + *(int *)(cur_sim + 0x3fdc);
      if ((((byte)*(undefined4 *)(pbVar7 + 0x14) & 0x30) == 0x20) &&
         (*(int *)(pbVar7 + 0x18) != 0xd)) {
        local_14 = *(int *)(iVar9 + 0xc);
        local_8 = *(undefined4 *)(pbVar7 + 8);
        local_4 = *(undefined4 *)(pbVar7 + 0xc);
      }
      else if (*(int *)(pbVar7 + 0x18) == 0x65) {
        pbVar8 = &DAT_004c7c28;
        pbVar4 = pbVar7;
        do {
          bVar3 = *pbVar4;
          bVar10 = bVar3 < *pbVar8;
          if (bVar3 != *pbVar8) {
LAB_00442267:
            iVar5 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
            goto LAB_0044226c;
          }
          if (bVar3 == 0) break;
          bVar3 = pbVar4[1];
          bVar10 = bVar3 < pbVar8[1];
          if (bVar3 != pbVar8[1]) goto LAB_00442267;
          pbVar4 = pbVar4 + 2;
          pbVar8 = pbVar8 + 2;
        } while (bVar3 != 0);
        iVar5 = 0;
LAB_0044226c:
        local_10 = *(int *)(iVar9 + 4);
        if (iVar5 == 0) {
          local_1c = local_10 + -1;
        }
        else {
          if (local_10 < 2) {
            local_10 = 2;
          }
          iVar9 = 2;
          uVar6 = (uint)(local_14 - lnnoptr) / 0xc;
          if (1 < local_10) {
            while (uVar1 = iVar9 + uVar6, uVar1 < nlines) {
              iVar5 = *(int *)((int)lines + uVar1 * 0xc + 8);
              piVar2 = (int *)((int)lines + uVar1 * 0xc + 8);
              if (iVar5 == 0) break;
              if (iVar9 == 2) {
                *(int *)((int)lines + uVar6 * 0xc + 0x14) =
                     *(int *)((int)lines + uVar6 * 0xc + 0x14) + local_1c;
                *(undefined4 *)((int)lines + (uVar6 + 1) * 0xc) = local_8;
                *(undefined4 *)((int)lines + (uVar6 + 1) * 0xc + 4) = local_4;
              }
              *piVar2 = *piVar2 + local_1c;
              if ((iVar5 == local_10) || (iVar9 = iVar9 + 1, local_10 < iVar9)) break;
            }
          }
        }
      }
      local_18 = local_18 + 1 + *(int *)(pbVar7 + 0x1c);
    } while (local_18 < *(int *)(cur_sim + 0x3fd8));
  }
  return;
}


/* ==== dbg_read_symbols @ 00442340 ==== */

int dbg_read_symbols(void)

{
  uint n;
  int iVar1;
  undefined4 extraout_EAX;
  uint uVar2;
  undefined4 extraout_EAX_00;
  int iVar3;
  void *buf;
  int iVar4;
  int iVar5;
  int *buf_00;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  iVar5 = 0;
  if ((*(int *)(cur_sim + 0x3fd4) != 0) && (*(int *)(cur_sim + 0x3fd8) != 0)) {
    iVar1 = fseek(g_cld_fp,*(int *)(cur_sim + 0x3fd4),0);
    if (iVar1 != 0) {
      expr_error(s_cannot_seek_to_symbol_table_004c7c50);
      return -1;
    }
    if (*(void **)(cur_sim + 0x3fdc) != (void *)0x0) {
      dsp_free(*(void **)(cur_sim + 0x3fdc));
      *(undefined4 *)(cur_sim + 0x3fdc) = 0;
    }
    if (*(int *)(cur_sim + 0x3fd8) != 0) {
      dsp_alloc(*(int *)(cur_sim + 0x3fd8) << 5,0);
      *(undefined4 *)(cur_sim + 0x3fdc) = extraout_EAX;
    }
    if (*(char **)(cur_sim + 0x3fdc) == (char *)0x0) {
      return -1;
    }
    n = *(uint *)(cur_sim + 0x3fd8);
    uVar2 = fread_swap32(*(char **)(cur_sim + 0x3fdc),0x20,n,g_cld_fp);
    if (uVar2 != n) {
      expr_error(s_cannot_read_symbol_table_entries_004c7c2c);
      return -1;
    }
    iVar1 = 0;
    iVar3 = cur_sim;
    if (0 < (int)n) {
      do {
        buf_00 = (int *)(*(int *)(iVar3 + 0x3fdc) + iVar1 * 0x20);
        if (*buf_00 != 0) {
          swap32_array(buf_00,4,2);
          iVar3 = cur_sim;
        }
        if ((buf_00[6] == 200) || (buf_00[6] == 0x67)) {
          buf = (void *)(*(int *)(iVar3 + 0x3fdc) + (iVar1 + 1) * 0x20);
          if (*(int *)((int)buf + 0x10) == 0) {
            swap32_array(buf,1,0x10);
            iVar3 = cur_sim;
          }
        }
        iVar1 = iVar1 + 1 + buf_00[7];
      } while (iVar1 < *(int *)(iVar3 + 0x3fd8));
    }
    if (*(void **)(iVar3 + 0x3fe0) != (void *)0x0) {
      dsp_free(*(void **)(iVar3 + 0x3fe0));
      *(undefined4 *)(cur_sim + 0x3fe0) = 0;
      iVar3 = cur_sim;
    }
    if (*(int *)(iVar3 + 0x3fd8) != 0) {
      dsp_alloc(*(int *)(iVar3 + 0x3fd8) << 5,0);
      *(undefined4 *)(cur_sim + 0x3fe0) = extraout_EAX_00;
      iVar3 = cur_sim;
    }
    if (*(int *)(iVar3 + 0x3fe0) == 0) {
      return -1;
    }
    if (0 < *(int *)(iVar3 + 0x3fd8)) {
      iVar1 = 0;
      do {
        iVar5 = iVar5 + 1;
        puVar6 = (undefined4 *)(*(int *)(iVar3 + 0x3fdc) + iVar1);
        puVar7 = (undefined4 *)(*(int *)(iVar3 + 0x3fe0) + iVar1);
        for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar7 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar7 = puVar7 + 1;
        }
        iVar1 = iVar1 + 0x20;
        iVar3 = cur_sim;
      } while (iVar5 < *(int *)(cur_sim + 0x3fd8));
    }
    cdb_detect_space_model();
  }
  return 0;
}


/* ==== dbg_number_symbols @ 00442530 ==== */

void dbg_number_symbols(void)

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
  
  iVar4 = 0;
  if (((*(int *)(cur_sim + 0x3fd8) != 0) && (*(int *)(cur_sim + 0x3fdc) != 0)) &&
     (iVar6 = 0, 0 < *(int *)(cur_sim + 0x3fd8))) {
    do {
      pbVar2 = (byte *)(*(int *)(cur_sim + 0x3fdc) + iVar6 * 0x20);
      *(int *)(pbVar2 + 0x14) = iVar4;
      iVar5 = iVar4;
      if (*(int *)(pbVar2 + 0x18) == 0xca) {
        *(int *)(*(int *)(cur_sim + 0x4014) + 0x1c + *(int *)(pbVar2 + 0x10) * 0x20) = iVar4;
      }
      else if (*(int *)(pbVar2 + 0x18) == 0xc9) {
        pbVar8 = &DAT_004c7c6c;
        pbVar7 = pbVar2;
        do {
          bVar1 = *pbVar7;
          bVar9 = bVar1 < *pbVar8;
          if (bVar1 != *pbVar8) {
LAB_004425c8:
            iVar3 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
            goto LAB_004425cd;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar7[1];
          bVar9 = bVar1 < pbVar8[1];
          if (bVar1 != pbVar8[1]) goto LAB_004425c8;
          pbVar7 = pbVar7 + 2;
          pbVar8 = pbVar8 + 2;
        } while (bVar1 != 0);
        iVar3 = 0;
LAB_004425cd:
        iVar5 = iVar6;
        if (iVar3 != 0) {
          iVar5 = *(int *)(*(int *)(cur_sim + 0x3fdc) + 0x14 + iVar4 * 0x20);
        }
      }
      iVar6 = iVar6 + 1 + *(int *)(pbVar2 + 0x1c);
      iVar4 = iVar5;
    } while (iVar6 < *(int *)(cur_sim + 0x3fd8));
  }
  return;
}


/* ==== dbg_set_section_line_start @ 00442610 ==== */

void dbg_set_section_line_start(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 3;
  if (3 < *(int *)(cur_sim + 0x3fd0)) {
    iVar3 = 0x60;
    iVar2 = cur_sim;
    do {
      puVar1 = (undefined4 *)(*(int *)(iVar2 + 0x4014) + iVar3);
      if (((puVar1[4] & 0x800) != 0) && (puVar1[5] != 0)) {
        iVar2 = *(int *)(iVar2 + 0x3ff0);
        *puVar1 = *(undefined4 *)(iVar2 + puVar1[6] * 0xc);
        puVar1[1] = *(undefined4 *)(iVar2 + 4 + puVar1[6] * 0xc);
        iVar2 = cur_sim;
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x20;
    } while (iVar4 < *(int *)(iVar2 + 0x3fd0));
  }
  return;
}


/* ==== dbg_fix_section_line_range @ 00442680 ==== */

void dbg_fix_section_line_range(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = 3;
  if (3 < *(int *)(cur_sim + 0x3fd0) + -1) {
    iVar3 = 0x60;
    iVar5 = cur_sim;
    do {
      iVar1 = *(int *)(iVar5 + 0x4014);
      if ((((*(int *)(iVar3 + 8 + iVar1) == 0) &&
           (iVar2 = *(int *)(iVar3 + 0x14 + iVar1), iVar2 != 0)) &&
          (*(int *)(iVar3 + 0x28 + iVar1) != 0)) && (*(int *)(iVar3 + 0x34 + iVar1) == 0)) {
        *(int *)(iVar3 + 0x34 + iVar1) = iVar2;
        *(undefined4 *)(iVar3 + 0x38 + iVar1) = *(undefined4 *)(iVar3 + 0x18 + iVar1);
        iVar4 = iVar4 + 1;
        iVar3 = iVar3 + 0x20;
        iVar5 = cur_sim;
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x20;
    } while (iVar4 < *(int *)(iVar5 + 0x3fd0) + -1);
  }
  return;
}


/* ==== dbg_load_source_files @ 004426f0 ==== */

int dbg_load_source_files(void)

{
  void *p;
  char *pcVar1;
  int iVar2;
  undefined4 extraout_EAX;
  int fileno;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_4;
  
  fileno = 0;
  local_4 = 0;
  if (*(int *)(cur_sim + 0x4020) != 0) {
    iVar5 = 0;
    iVar2 = cur_sim;
    if (0 < *(int *)(cur_sim + 0x401c)) {
      iVar3 = 0;
      do {
        p = *(void **)(*(int *)(iVar2 + 0x4020) + 4 + iVar3);
        if (p != (void *)0x0) {
          dsp_free(p);
          iVar2 = cur_sim;
        }
        iVar5 = iVar5 + 1;
        iVar3 = iVar3 + 0xc;
      } while (iVar5 < *(int *)(iVar2 + 0x401c));
    }
    dsp_free(*(void **)(iVar2 + 0x4020));
    *(undefined4 *)(cur_sim + 0x4020) = 0;
  }
  *(undefined4 *)(cur_sim + 0x3ff8) = 0xffffffff;
  iVar2 = *(int *)(cur_sim + 0x3fdc);
  if (iVar2 != 0) {
    local_4 = 0;
    iVar5 = 0;
    while( true ) {
      iVar4 = iVar5 * 0x20;
      iVar3 = *(int *)(iVar4 + 0x18 + iVar2);
      if ((iVar3 != 200) && (iVar3 != 0x67)) break;
      pcVar1 = dbg_aux_name((void *)((iVar5 + 1) * 0x20 + iVar2));
      if (pcVar1 != (char *)0x0) {
        if ((iVar5 < 1) || (iVar2 = dbg_find_file_sym(pcVar1,iVar5), iVar2 < 0)) {
          *(int *)(*(int *)(cur_sim + 0x3fdc) + 0x14 + iVar4) = local_4;
          local_4 = local_4 + 1;
        }
        else {
          *(undefined4 *)(iVar4 + 0x14 + *(int *)(cur_sim + 0x3fdc)) =
               *(undefined4 *)(iVar2 * 0x20 + 0x14 + *(int *)(cur_sim + 0x3fdc));
        }
      }
      iVar2 = *(int *)(cur_sim + 0x3fdc);
      iVar5 = *(int *)(iVar4 + 8 + iVar2);
    }
  }
  *(int *)(cur_sim + 0x401c) = local_4;
  *(int *)(cur_sim + 0x4044) = local_4;
  if (*(int *)(cur_sim + 0x401c) == 0) {
    *(undefined4 *)(cur_sim + 0x4020) = 0;
  }
  else {
    dsp_alloc(*(int *)(cur_sim + 0x401c) * 0xc,0);
    *(undefined4 *)(cur_sim + 0x4020) = extraout_EAX;
    if (*(int *)(cur_sim + 0x4020) == 0) {
      return -1;
    }
    iVar2 = 0;
    if (0 < local_4) {
      iVar5 = 0;
      do {
        *(undefined4 *)(*(int *)(cur_sim + 0x4020) + iVar5) = 0;
        *(undefined4 *)(*(int *)(cur_sim + 0x4020) + 4 + iVar5) = 0;
        *(undefined4 *)(*(int *)(cur_sim + 0x4020) + 8 + iVar5) = 0;
        pcVar1 = dbg_aux_name((void *)(*(int *)(cur_sim + 0x3fdc) + (iVar2 + 1) * 0x20));
        if ((pcVar1 != (char *)0x0) &&
           ((iVar2 == 0 || (iVar3 = dbg_find_file_sym(pcVar1,iVar2), iVar3 < 0)))) {
          iVar3 = dbg_load_source_index(fileno,pcVar1);
          if (iVar3 == -1) {
            return -1;
          }
          fileno = fileno + 1;
          iVar5 = iVar5 + 0xc;
        }
        iVar2 = *(int *)(*(int *)(cur_sim + 0x3fdc) + 8 + iVar2 * 0x20);
      } while (fileno < local_4);
      return 0;
    }
  }
  return 0;
}


/* ==== dbg_find_file_sym @ 00442930 ==== */

int __cdecl dbg_find_file_sym(char *name,int limit)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  
  if ((name != (char *)0x0) && (iVar5 = 0, 0 < limit)) {
    while( true ) {
      iVar4 = *(int *)(*(int *)(cur_sim + 0x3fdc) + 0x18 + iVar5 * 0x20);
      if ((iVar4 != 200) && (iVar4 != 0x67)) break;
      pbVar2 = (byte *)dbg_aux_name((void *)((iVar5 + 1) * 0x20 + *(int *)(cur_sim + 0x3fdc)));
      pbVar3 = (byte *)name;
      if (pbVar2 != (byte *)0x0) {
        do {
          bVar1 = *pbVar3;
          bVar6 = bVar1 < *pbVar2;
          if (bVar1 != *pbVar2) {
LAB_004429ae:
            iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
            goto LAB_004429b3;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar3[1];
          bVar6 = bVar1 < pbVar2[1];
          if (bVar1 != pbVar2[1]) goto LAB_004429ae;
          pbVar2 = pbVar2 + 2;
          pbVar3 = pbVar3 + 2;
        } while (bVar1 != 0);
        iVar4 = 0;
LAB_004429b3:
        if (iVar4 == 0) {
          return iVar5;
        }
      }
      iVar5 = *(int *)(*(int *)(cur_sim + 0x3fdc) + 8 + iVar5 * 0x20);
      if (limit <= iVar5) {
        return -1;
      }
    }
  }
  return -1;
}


/* ==== dbg_load_source_index @ 004429f0 ==== */

int __cdecl dbg_load_source_index(int fileno,char *path)

{
  char cVar1;
  undefined4 extraout_EAX;
  undefined4 *extraout_EAX_00;
  int *piVar2;
  undefined4 *extraout_EAX_01;
  long lVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  long *plVar9;
  char *pcVar10;
  char local_100 [256];
  
  path_search(path,&empty_str,local_100);
  uVar4 = 0xffffffff;
  iVar7 = fileno * 0xc;
  pcVar8 = path;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  malloc(~uVar4);
  uVar4 = 0xffffffff;
  *(undefined4 *)(*(int *)(cur_sim + 0x4020) + 8 + iVar7) = extraout_EAX;
  do {
    pcVar8 = path;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar8 = path + 1;
    cVar1 = *path;
    path = pcVar8;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar8 = pcVar8 + -uVar4;
  pcVar10 = *(char **)(*(int *)(cur_sim + 0x4020) + 8 + iVar7);
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
    pcVar8 = pcVar8 + 4;
    pcVar10 = pcVar10 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar10 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    pcVar10 = pcVar10 + 1;
  }
  fopen(local_100,&DAT_004c5ff4);
  g_src_fp = extraout_EAX_00;
  if (extraout_EAX_00 != (undefined4 *)0x0) {
    iVar6 = 1;
    while( true ) {
      g_src_fp[1] = g_src_fp[1] + -1;
      if ((int)g_src_fp[1] < 0) {
        uVar4 = _filbuf(g_src_fp);
      }
      else {
        uVar4 = (uint)*(byte *)*g_src_fp;
        *g_src_fp = (byte *)*g_src_fp + 1;
      }
      if (uVar4 == 0xffffffff) break;
      if (uVar4 == 10) {
        iVar6 = iVar6 + 1;
      }
    }
    if (iVar6 != 0) {
      piVar2 = (int *)(*(int *)(cur_sim + 0x4020) + iVar7);
      if (piVar2[2] == 0) {
        return -1;
      }
      *piVar2 = iVar6;
      dsp_alloc(iVar6 * 4,0);
      if (extraout_EAX_01 == (undefined4 *)0x0) {
        return -1;
      }
      *(undefined4 **)(*(int *)(cur_sim + 0x4020) + 4 + iVar7) = extraout_EAX_01;
      *extraout_EAX_01 = 0;
      if (1 < iVar6) {
        extraout_EAX_01[1] = 0;
      }
      iVar7 = 1;
      fseek(g_src_fp,0,0);
      plVar9 = extraout_EAX_01 + 1;
      while( true ) {
        do {
          g_src_fp[1] = g_src_fp[1] + -1;
          if ((int)g_src_fp[1] < 0) {
            uVar4 = _filbuf(g_src_fp);
          }
          else {
            uVar4 = (uint)*(byte *)*g_src_fp;
            *g_src_fp = (byte *)*g_src_fp + 1;
          }
          if (uVar4 == 0xffffffff) goto LAB_00442bb7;
        } while (uVar4 != 10);
        iVar7 = iVar7 + 1;
        plVar9 = plVar9 + 1;
        if (iVar6 <= iVar7) break;
        lVar3 = ftell(g_src_fp);
        *plVar9 = lVar3;
      }
    }
LAB_00442bb7:
    fclose(g_src_fp);
  }
  return 0;
}


/* ==== dbg_fix_symbol_classes @ 00442be0 ==== */

void dbg_fix_symbol_classes(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (((*(int *)(cur_sim + 0x3fd4) != 0) && (*(int *)(cur_sim + 0x3fd8) != 0)) &&
     (iVar3 = 0, iVar4 = cur_sim, 0 < *(int *)(cur_sim + 0x3fd8))) {
    do {
      iVar2 = *(int *)(iVar4 + 0x3fdc) + iVar3 * 0x20;
      if (*(int *)(iVar2 + 0x10) == -1) {
        uVar1 = *(uint *)(iVar2 + 0x14);
        if (((uVar1 == 0) || (uVar1 == 4)) ||
           (((uVar1 & 0x30) == 0x20 || (((uVar1 & 0x30) == 0x10 || (*(int *)(iVar2 + 0xc) == 0))))))
        {
          if (((uVar1 & 0x30) != 0x20) && (((uVar1 & 0x30) != 0x10 && (*(int *)(iVar2 + 0xc) != 0)))
             ) {
            *(undefined4 *)(iVar2 + 0xc) = 4;
            iVar4 = cur_sim;
          }
        }
        else {
          *(undefined4 *)(iVar2 + 0x18) = 0x6a;
          iVar4 = cur_sim;
        }
      }
      iVar3 = iVar3 + 1 + *(int *)(iVar2 + 0x1c);
    } while (iVar3 < *(int *)(iVar4 + 0x3fd8));
  }
  return;
}


/* ==== dbg_free @ 00442c80 ==== */

void dbg_free(void)

{
  void *p;
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (*(void **)(cur_sim + 0x3fe4) != (void *)0x0) {
    dsp_free(*(void **)(cur_sim + 0x3fe4));
    *(undefined4 *)(cur_sim + 0x3fe4) = 0;
  }
  if (*(void **)(cur_sim + 0x4014) != (void *)0x0) {
    dsp_free(*(void **)(cur_sim + 0x4014));
    *(undefined4 *)(cur_sim + 0x4014) = 0;
  }
  if (*(void **)(cur_sim + 0x3ff0) != (void *)0x0) {
    dsp_free(*(void **)(cur_sim + 0x3ff0));
    *(undefined4 *)(cur_sim + 0x3ff0) = 0;
  }
  if (*(void **)(cur_sim + 0x3fdc) != (void *)0x0) {
    dsp_free(*(void **)(cur_sim + 0x3fdc));
    *(undefined4 *)(cur_sim + 0x3fdc) = 0;
  }
  if (*(int *)(cur_sim + 0x4020) != 0) {
    iVar3 = 0;
    iVar1 = cur_sim;
    if (0 < *(int *)(cur_sim + 0x401c)) {
      iVar2 = 0;
      do {
        p = *(void **)(*(int *)(iVar1 + 0x4020) + 4 + iVar2);
        if (p != (void *)0x0) {
          dsp_free(p);
          iVar1 = cur_sim;
        }
        iVar3 = iVar3 + 1;
        iVar2 = iVar2 + 0xc;
      } while (iVar3 < *(int *)(iVar1 + 0x401c));
    }
    dsp_free(*(void **)(iVar1 + 0x4020));
    *(undefined4 *)(cur_sim + 0x4020) = 0;
  }
  if (*(void **)(cur_sim + 0x402c) != (void *)0x0) {
    dsp_free(*(void **)(cur_sim + 0x402c));
    *(undefined4 *)(cur_sim + 0x402c) = 0;
  }
  if (*(void **)(cur_sim + 0x4030) != (void *)0x0) {
    dsp_free(*(void **)(cur_sim + 0x4030));
    *(undefined4 *)(cur_sim + 0x4030) = 0;
  }
  *(undefined4 *)(cur_sim + 0x401c) = 0;
  *(undefined4 *)(cur_sim + 0x3fd0) = 0;
  *(undefined4 *)(cur_sim + 0x3fd4) = 0;
  return;
}


/* ==== win_buf_alloc @ 00442de0 ==== */

int win_buf_alloc(void)

{
  undefined4 *extraout_EAX;
  int iVar1;
  undefined4 *puVar2;
  
  dsp_alloc(0x6464,0);
  g_win_buf = extraout_EAX;
  if (extraout_EAX == (undefined4 *)0x0) {
    return -1;
  }
  puVar2 = extraout_EAX;
  for (iVar1 = 0x1919; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return 0;
}


/* ==== win_update @ 00442e10 ==== */

void __cdecl win_update(int delta)

{
  ulong pc;
  int space;
  
  if ((g_win_buf == (char *)0x0) && (win_buf_alloc(), g_win_buf == (char *)0x0)) {
    return;
  }
  cur_dev = *(int **)(dev_tab + cur_dev_index * 4);
  cur_itype = *(undefined4 *)(itype_tab + *cur_dev * 4);
  cur_sim = *(int *)(dev_state_tab + cur_dev_index * 4);
  cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
  pc = cdb_frame_pc();
  space = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(0,pc);
  if (*(int *)(cur_sim + 0x4400) == 1) {
    asmwin_scroll(delta,pc,space);
  }
  else {
    srcwin_scroll(delta,pc,space);
  }
  if (*(int *)(cur_sim + 0x4400) != 0) {
    win_status_line();
    screen_fill_rows(g_win_buf);
  }
  return;
}


/* ==== win_status_line @ 00442ee0 ==== */

void win_status_line(void)

{
  char cVar1;
  ulong addr;
  int space;
  char *va0;
  int va1;
  int iVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  undefined1 *puStack_1b4;
  char *pcStack_1b0;
  char *pcStack_1a8;
  int iStack_1a4;
  uint uStack_19c;
  char acStack_198 [20];
  char acStack_184 [32];
  char acStack_164 [356];
  
  addr = cdb_frame_pc();
  space = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(0,addr);
  va0 = dbg_addr_to_filename(addr,space);
  if (va0 != (char *)0x0) {
    uVar4 = 0xffffffff;
    pcVar5 = va0;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    if (0x14 < (int)(~uVar4 - 1)) {
      va0 = va0 + (~uVar4 - 0x15);
    }
  }
  pcStack_1a8 = dbg_fileno_to_name(*(int *)(cur_sim + 0x3ff8));
  if (pcStack_1a8 != (char *)0x0) {
    uVar4 = 0xffffffff;
    pcVar5 = pcStack_1a8;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    if (0x14 < (int)(~uVar4 - 1)) {
      pcStack_1a8 = pcStack_1a8 + (~uVar4 - 0x15);
    }
  }
  va1 = dbg_addr_to_line(addr,space);
  iVar2 = dbg_find_label(addr,space,&uStack_19c);
  puStack_1b4 = &DAT_004c7b28;
  if (uStack_19c == 0) {
    puStack_1b4 = &empty_str;
  }
  if (iVar2 == 0) {
    pcStack_1b0 = s_no_label_004c7d50;
    iStack_1a4 = 0;
  }
  else {
    pcStack_1b0 = dbg_sym_name((void *)(*(int *)(cur_sim + 0x3fdc) + iVar2 * 0x20));
    iStack_1a4 = addr - *(int *)(*(int *)(cur_sim + 0x3fdc) + 8 + iVar2 * 0x20);
  }
  iVar2 = addr_to_srcline(addr,space);
  if (iVar2 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = *(int *)(*(int *)(cur_sim + 0x4014) + 0x1c + iVar2 * 0x20);
  }
  if (iVar3 < 1) {
    pcVar5 = s_global_004c7af4;
  }
  else {
    pcVar5 = (char *)(*(int *)(*(int *)(cur_sim + 0x3fdc) + 8 + iVar3 * 0x20) +
                     *(int *)(cur_sim + 0x3fe4));
  }
  if (iStack_1a4 == 0) {
    acStack_198[0] = '\0';
  }
  else {
    sprintf(acStack_198,&DAT_004c7d48,iStack_1a4);
  }
  iVar2 = dbg_find_macro_of_file(iVar2);
  if (iVar2 == 0) {
    acStack_184[0] = '\0';
  }
  else {
    sprintf(acStack_184,s_macro___12s_004c7d38,
            *(int *)(*(int *)(cur_sim + 0x3fdc) + 8 + iVar2 * 0x20) + *(int *)(cur_sim + 0x3fe4));
  }
  if (*(int *)(cur_sim + 0x4400) == 1) {
    sprintf(acStack_164,s_asm__s___lx_pc___20s__lu__s___lx_004c7cf8,
            (&g_space_names)[*(int *)(cur_sim + 0x400c)],*(undefined4 *)(cur_sim + 0x4008),va0,va1,
            (&g_space_names)[space],addr,puStack_1b4,pcStack_1b0,acStack_198,acStack_184,pcVar5,
            s__004c6d88);
  }
  else if (pcStack_1a8 == (char *)0x0) {
    sprintf(acStack_164,s_no_source_file_pc___20s__lu__s___004c7c70,va0,va1,(&g_space_names)[space],
            addr,puStack_1b4,pcStack_1b0,acStack_198,acStack_184,pcVar5,s__004c6d88);
  }
  else {
    sprintf(acStack_164,s_src___20s__lu_pc___20s__lu__s____004c7cb4,pcStack_1a8,
            *(undefined4 *)(cur_sim + 0x3ffc),va0,va1,(&g_space_names)[space],addr,puStack_1b4,
            pcStack_1b0,acStack_198,acStack_184,pcVar5,s__004c6d88);
  }
  strncpy(g_win_buf,acStack_164,screen_cols);
  if ((*(int *)(cur_sim + 0x184) != 0) && (*(int *)(cur_sim + 0x48) != 0)) {
    out_text(g_win_buf,1);
  }
  g_win_buf[screen_cols] = '\0';
  return;
}


/* ==== asmwin_scroll @ 004431f0 ==== */

void __cdecl asmwin_scroll(int delta,uint pc,int space)

{
  if (delta == 0x7fff) {
    if (((*(int *)(cur_sim + 0x400c) != space) || (pc < *(uint *)(cur_sim + 0x4008))) ||
       (*(uint *)(cur_sim + 0x4010) < pc)) {
      *(int *)(cur_sim + 0x400c) = space;
      *(uint *)(cur_sim + 0x4008) = pc;
    }
  }
  else {
    *(int *)(cur_sim + 0x4008) = *(int *)(cur_sim + 0x4008) + delta;
  }
  asmwin_fill(*(uint *)(cur_sim + 0x4008),*(int *)(cur_sim + 0x400c));
  return;
}


/* ==== asmwin_fill @ 00443260 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl asmwin_fill(uint addr,int space)

{
  char cVar1;
  code *pcVar2;
  ulong addr_00;
  int iVar3;
  long lVar4;
  char *pcVar5;
  uint uVar6;
  uint addr_01;
  undefined *puVar7;
  undefined1 *puVar8;
  uint uVar9;
  int iVar10;
  char *pcVar11;
  char *pcVar12;
  long lStack_390;
  int iStack_38c;
  char *pcStack_388;
  undefined4 local_384;
  int iStack_380;
  undefined4 uStack_37c;
  char *pcStack_378;
  int iStack_374;
  int iStack_370;
  uint uStack_36c;
  long lStack_368;
  uint uStack_364;
  ulong local_360;
  int iStack_35c;
  long lStack_358;
  undefined1 auStack_354 [40];
  char acStack_32c [152];
  char acStack_294 [52];
  undefined1 auStack_260 [256];
  char acStack_160 [352];
  
  iVar10 = cur_dev_index;
  local_384 = 0;
  addr_00 = cdb_frame_pc();
  local_360 = addr_00;
  iVar3 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(0,addr_00);
  iVar3 = memmap_find(iVar3,addr_00);
  *(undefined4 *)(cur_sim + 0x4028) =
       *(undefined4 *)(*(int *)(cur_dtype + 0x20) + 0x20 + iVar3 * 0x2c);
  uStack_36c = *(uint *)(cur_sim + 0x4028);
  addr_01 = addr & uStack_36c;
  *(uint *)(cur_sim + 0x4024) = addr_01;
  *(uint *)(cur_sim + 0x4008) = addr_01;
  *(int *)(cur_sim + 0x400c) = space;
  iVar3 = dbg_addr_to_fileno(addr_01,space);
  *(int *)(cur_sim + 0x3ff8) = iVar3;
  lVar4 = periph_find_reg(iVar10,&DAT_004b2924,&iStack_370,&lStack_368);
  if ((lVar4 != 0) &&
     (lVar4 = periph_call(iVar10,iStack_370,lStack_368,(long)&uStack_37c), lVar4 == 0)) {
    sim_error(s_Error_reading_register_004c6178);
    return;
  }
  lVar4 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2928,&iStack_38c,&lStack_390);
  if (lVar4 == 0) {
    _DAT_00502278 = 0;
  }
  else {
    periph_call(*(int *)(cur_dev + 4),iStack_38c,lStack_390,0x502278);
  }
  lVar4 = periph_find_reg(iVar10,&DAT_004b2950,&iStack_35c,&lStack_358);
  if ((lVar4 != 0) &&
     (lVar4 = periph_call(iVar10,iStack_35c,lStack_358,(long)&local_384), lVar4 == 0)) {
    sim_error(s_Error_reading_register_004c6178);
    return;
  }
  lVar4 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2934,&iStack_38c,&lStack_390);
  uVar9 = -(uint)(lVar4 != 0) & 4;
  iVar10 = uVar9 + 4;
  lVar4 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2948,&iStack_38c,&lStack_390);
  if ((lVar4 != 0) && (iVar3 = 0, uVar9 != 0xfffffffc)) {
    puVar7 = &DAT_00502204;
    do {
      lVar4 = periph_call(*(int *)(cur_dev + 4),iStack_38c,lStack_390 + iVar3,(long)puVar7);
      if (lVar4 == 0) goto LAB_00443a19;
      iVar3 = iVar3 + 1;
      puVar7 = puVar7 + 4;
    } while (iVar3 < iVar10);
  }
  lVar4 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2990,&iStack_38c,&lStack_390);
  if ((lVar4 != 0) && (iVar3 = 0, uVar9 != 0xfffffffc)) {
    puVar7 = &DAT_00502244;
    do {
      lVar4 = periph_call(*(int *)(cur_dev + 4),iStack_38c,lStack_390 + iVar3,(long)puVar7);
      if (lVar4 == 0) goto LAB_00443a19;
      iVar3 = iVar3 + 1;
      puVar7 = puVar7 + 4;
    } while (iVar3 < iVar10);
  }
  lVar4 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2970,&iStack_38c,&lStack_390);
  if ((lVar4 != 0) && (iVar3 = 0, uVar9 != 0xfffffffc)) {
    puVar7 = &DAT_00502224;
    do {
      lVar4 = periph_call(*(int *)(cur_dev + 4),iStack_38c,lStack_390 + iVar3,(long)puVar7);
      if (lVar4 == 0) {
LAB_00443a19:
        sim_error(s_Error_reading_register_004c6178);
        return;
      }
      iVar3 = iVar3 + 1;
      puVar7 = puVar7 + 4;
    } while (iVar3 < iVar10);
  }
  pcStack_378 = g_win_buf;
  iStack_374 = 1;
  if (1 < text_rows) {
    do {
      pcStack_378 = pcStack_378 + 0x101;
      pcVar2 = *(code **)(*(int *)(cur_dtype + 0x28) + 0x24);
      if (pcVar2 == (code *)0x0) {
        if (*(int *)(*(int *)(cur_dtype + 0x28) + 0x14) == 0) {
          iVar10 = 0;
          puVar8 = auStack_354;
          do {
            (*(code *)**(undefined4 **)(cur_dtype + 0x28))(space,addr_01 + iVar10,puVar8);
            iVar10 = iVar10 + 1;
            puVar8 = puVar8 + 4;
          } while (iVar10 < 10);
          _g_dasm_pc = addr_01;
          iStack_380 = (**(code **)(cur_itype + 0x10))
                                 (auStack_354,auStack_260,uStack_37c,local_384,&DAT_005021f0);
          if (iStack_380 == 0) {
            iStack_380 = 1;
          }
        }
        else {
          iVar10 = 0;
          iVar3 = 0;
          puVar8 = auStack_354;
          do {
            iVar10 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0x14))
                               (space,iVar10 * iVar3 + addr_01,puVar8,0);
            iVar3 = iVar3 + 1;
            puVar8 = puVar8 + 4;
          } while (iVar3 < 10);
          _g_dasm_pc = addr_01;
          iStack_380 = (**(code **)(cur_itype + 0x10))
                                 (auStack_354,auStack_260,uStack_37c,local_384,&DAT_005021f0);
          if (iStack_380 == 0) {
            iStack_380 = 1;
          }
          iStack_380 = iVar10 * iStack_380;
        }
      }
      else {
        iStack_380 = (*pcVar2)(space,addr_01,auStack_354,0);
        _g_dasm_pc = addr_01;
        (**(code **)(cur_itype + 0x10))(auStack_354,auStack_260,uStack_37c,local_384,&DAT_005021f0);
      }
      acStack_32c[0] = '\0';
      acStack_32c[1] = 0;
      acStack_32c[2] = '\0';
      if (g_dasm_opflags != 0) {
        uVar9 = 0xffffffff;
        pcVar5 = &DAT_004c6174;
        do {
          pcVar12 = pcVar5;
          if (uVar9 == 0) break;
          uVar9 = uVar9 - 1;
          pcVar12 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar12;
        } while (cVar1 != '\0');
        uVar9 = ~uVar9;
        iVar10 = -1;
        pcVar5 = acStack_32c;
        do {
          pcVar11 = pcVar5;
          if (iVar10 == 0) break;
          iVar10 = iVar10 + -1;
          pcVar11 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar11;
        } while (cVar1 != '\0');
        pcVar5 = pcVar12 + -uVar9;
        pcVar12 = pcVar11 + -1;
        for (uVar6 = uVar9 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined4 *)pcVar12 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar12 = pcVar12 + 4;
        }
        for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
          *pcVar12 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar12 = pcVar12 + 1;
        }
      }
      if ((g_dasm_opflags & 1) != 0) {
        uVar9 = 0x2f;
        pcVar5 = dbg_format_addr(0,DAT_0050226c);
        strncat(acStack_32c,pcVar5,uVar9);
      }
      if ((g_dasm_opflags & 2) != 0) {
        uVar9 = 0x2f;
        pcVar5 = dbg_format_addr(1,DAT_00502270);
        strncat(acStack_32c,pcVar5,uVar9);
      }
      if ((g_dasm_opflags & 0x40) != 0) {
        uVar9 = 0x2f;
        pcVar5 = dbg_format_addr(0,DAT_00502270);
        strncat(acStack_32c,pcVar5,uVar9);
      }
      if ((g_dasm_opflags & 4) != 0) {
        uVar9 = 0x2f;
        pcVar5 = dbg_format_addr(2,DAT_00502274);
        strncat(acStack_32c,pcVar5,uVar9);
      }
      if ((g_dasm_opflags & 8) != 0) {
        uVar9 = 0x2f;
        pcVar5 = dbg_format_addr(3,DAT_00502270);
        strncat(acStack_32c,pcVar5,uVar9);
      }
      if ((g_dasm_opflags & 0x10) != 0) {
        uVar9 = 0x2f;
        pcVar5 = dbg_format_addr(2,DAT_00502270);
        strncat(acStack_32c,pcVar5,uVar9);
      }
      if ((g_dasm_opflags & 0x20) != 0) {
        uVar9 = 0x2f;
        pcVar5 = dbg_format_addr(1,DAT_00502274);
        strncat(acStack_32c,pcVar5,uVar9);
      }
      if ((g_dasm_opflags & 0x80) != 0) {
        uVar9 = 0x2f;
        pcVar5 = dbg_format_addr(0,DAT_00502274);
        strncat(acStack_32c,pcVar5,uVar9);
      }
      if (acStack_32c[2] == '\0') {
        acStack_32c[0] = '\0';
      }
      iVar10 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(space,addr_01);
      iVar10 = dbg_find_label(addr_01,iVar10,&uStack_364);
      if (iVar10 == 0) {
        pcStack_388 = (char *)0x0;
        iVar10 = 0;
      }
      else {
        pcStack_388 = dbg_sym_name((void *)(*(int *)(cur_sim + 0x3fdc) + iVar10 * 0x20));
        iVar10 = addr_01 - *(int *)(*(int *)(cur_sim + 0x3fdc) + 8 + iVar10 * 0x20);
      }
      if (pcStack_388 == (char *)0x0) {
LAB_00443939:
        pcVar5 = s__004c7da0;
      }
      else {
        pcVar5 = &DAT_004c7b28;
        if (uStack_364 == 0) {
          pcVar5 = &empty_str;
        }
        uVar9 = 0xffffffff;
        do {
          pcVar12 = pcVar5;
          if (uVar9 == 0) break;
          uVar9 = uVar9 - 1;
          pcVar12 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar12;
        } while (cVar1 != '\0');
        uVar9 = ~uVar9;
        pcVar5 = pcVar12 + -uVar9;
        pcVar12 = acStack_160;
        for (uVar6 = uVar9 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined4 *)pcVar12 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar12 = pcVar12 + 4;
        }
        for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
          *pcVar12 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar12 = pcVar12 + 1;
        }
        strncat(acStack_160,pcStack_388,8);
        if (pcStack_388 == (char *)0x0) goto LAB_00443939;
        if (iVar10 == 0) {
          pcVar5 = s__8_8s_004c7db0;
        }
        else {
          pcVar5 = s__8_8s__04lu_004c7dbc;
        }
      }
      sprintf(acStack_294,pcVar5,acStack_160,iVar10);
      uVar9 = uStack_36c;
      puVar7 = &DAT_004c7d9c;
      if (addr_01 != local_360) {
        puVar7 = &DAT_004c7d98;
      }
      if ((uStack_36c & 0x1000000) == 0) {
        pcVar5 = s__s_06lx__s__s_s_s_004c7d70;
        if ((uStack_36c & 0x10000) == 0) {
          pcVar5 = s__s_04lx__s__s_s_s_004c7d5c;
        }
      }
      else {
        pcVar5 = s__s_08lx__s__s_s_s_004c7d84;
      }
      sprintf(acStack_160,pcVar5,puVar7,addr_01,acStack_294,auStack_260,acStack_32c,s__004c6d88);
      pcVar5 = pcStack_378;
      addr_01 = addr_01 + iStack_380 & uVar9;
      strncpy(pcStack_378,acStack_160,screen_cols);
      iStack_374 = iStack_374 + 1;
      pcVar5[screen_cols] = '\0';
    } while (iStack_374 < text_rows);
  }
  *(uint *)(cur_sim + 0x4010) = addr_01 - 1;
  return;
}


/* ==== srcwin_scroll @ 00443a40 ==== */

void __cdecl srcwin_scroll(int delta,uint pc,int space)

{
  uint addr;
  ulong addr_00;
  int iVar1;
  int iVar2;
  int va0;
  int iVar3;
  char *pcVar4;
  int fileno;
  int iVar5;
  
  addr = pc;
  addr_00 = cdb_frame_pc();
  iVar1 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(0,pc);
  pc = 0;
  iVar2 = dbg_addr_to_fileno(addr,space);
  va0 = dbg_addr_to_fileno(addr_00,iVar1);
  iVar5 = *(int *)(cur_sim + 0x3ff8);
  fileno = iVar2;
  if (delta != 0x7fff) {
    fileno = iVar5;
  }
  if (-1 < fileno) {
    iVar3 = dbg_addr_to_line(addr,space);
    iVar1 = dbg_addr_to_line(addr_00,iVar1);
    if (0 < iVar3) {
      if (delta == 0x7fff) {
        if (((iVar2 == iVar5) && (*(int *)(cur_sim + 0x3ffc) <= iVar3)) &&
           (iVar3 < *(int *)(cur_sim + 0x4000))) {
          iVar3 = *(int *)(cur_sim + 0x3ffc) + 3;
        }
        else {
          *(int *)(cur_sim + 0x3ff8) = fileno;
        }
      }
      else {
        iVar3 = *(int *)(cur_sim + 0x3ffc) + 3 + delta;
      }
      if (iVar3 < 1) {
        iVar3 = 1;
      }
      if (*(int *)(*(int *)(cur_sim + 0x4020) + fileno * 0xc) <= iVar3 + -3) {
        iVar3 = *(int *)(cur_sim + 0x3ffc) + 3;
      }
      pcVar4 = dbg_fileno_to_name(fileno);
      iVar3 = iVar3 + -3;
      if (iVar3 < 1) {
        iVar3 = 1;
      }
      *(int *)(cur_sim + 0x3ffc) = iVar3;
      *(int *)(cur_sim + 0x4024) = iVar3;
      *(int *)(cur_sim + 0x4000) = iVar3 + -1 + text_rows;
      *(undefined4 *)(cur_sim + 0x4028) = *(undefined4 *)(*(int *)(cur_sim + 0x4020) + fileno * 0xc)
      ;
      *(int *)(cur_sim + 0x3ff8) = fileno;
      pc = srcwin_fill(pcVar4,0x100,iVar3,fileno,iVar1,va0);
    }
  }
  if (pc == 0) {
    iVar5 = 1;
    pcVar4 = g_win_buf;
    if (1 < text_rows) {
      do {
        pcVar4 = pcVar4 + 0x101;
        strncpy(pcVar4,s__004c6d88,screen_cols);
        iVar5 = iVar5 + 1;
        pcVar4[screen_cols] = '\0';
      } while (iVar5 < text_rows);
    }
    *(undefined4 *)(cur_sim + 0x3ff8) = 0xffffffff;
  }
  return;
}


/* ==== srcwin_fill @ 00443c30 ==== */

int __cdecl srcwin_fill(char *file,int width,int first_line,int fileno,int pc_line,int pc_fileno)

{
  char cVar1;
  void *extraout_EAX;
  int iVar2;
  uint uVar3;
  undefined *puVar4;
  int *piVar5;
  int iVar6;
  char *dst;
  char *pcVar7;
  char local_d00 [256];
  char local_c00 [1024];
  char local_800;
  char local_7ff [1023];
  char local_400 [1024];
  
  iVar6 = 0;
  path_search(file,&empty_str,local_d00);
  fopen(local_d00,&DAT_004c5ff4);
  g_src_fp = extraout_EAX;
  if (extraout_EAX != (void *)0x0) {
    iVar6 = 1;
    if (1 < text_rows) {
      dst = g_win_buf;
      do {
        dst = dst + width + 1;
        piVar5 = (int *)(fileno * 0xc + *(int *)(cur_sim + 0x4020));
        if (first_line < *piVar5) {
          local_800 = '\0';
          iVar2 = fseek(g_src_fp,*(long *)(piVar5[1] + first_line * 4),0);
          if (iVar2 == 0) {
            fscanf(g_src_fp,s__160_____004c7de0,&local_800);
          }
          uVar3 = 0;
          pcVar7 = local_7ff;
          cVar1 = local_800;
          while (cVar1 != '\0') {
            if (cVar1 == '\t') {
              do {
                local_c00[uVar3] = ' ';
                uVar3 = uVar3 + 1;
              } while ((uVar3 & 7) != 0);
            }
            else {
              local_c00[uVar3] = cVar1;
              uVar3 = uVar3 + 1;
            }
            cVar1 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          }
          local_c00[uVar3] = '\0';
          if (pc_line < 1) {
            sprintf(local_400,s___6d__s_s_004c7dc8,first_line,local_c00,s__004c6d88);
            pcVar7 = local_400;
          }
          else {
            if ((fileno != pc_fileno) || (puVar4 = &DAT_004c7d9c, first_line != pc_line)) {
              puVar4 = &DAT_004c7d98;
            }
            sprintf(local_400,s__s__6d__s_s_004c7dd4,puVar4,first_line,local_c00,s__004c6d88);
            pcVar7 = local_400;
          }
        }
        else {
          pcVar7 = s__004c6d88;
        }
        strncpy(dst,pcVar7,screen_cols);
        first_line = first_line + 1;
        iVar6 = iVar6 + 1;
        dst[screen_cols] = '\0';
      } while (iVar6 < text_rows);
    }
    fclose(g_src_fp);
    iVar6 = 1;
  }
  return iVar6;
}


/* ==== step_mode_at_pc @ 00443e30 ==== */

int __cdecl step_mode_at_pc(int mode)

{
  uint addr;
  int iVar1;
  int iVar2;
  int iStack_4;
  
  addr = *(uint *)(cur_dev + 0x1c);
  iVar1 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(0,addr);
  iVar2 = dbg_addr_to_line(addr,iVar1);
  if (0 < iVar2) {
    iVar1 = dbg_addr_to_fileno(addr,iVar1);
    *(int *)(cur_sim + 0x3ff8) = iVar1;
    *(int *)(cur_sim + 0x4004) = iVar2;
    mode = (mode != 3) + 0xd;
    iVar1 = insn_is_branch(addr,&iStack_4);
    if (iVar1 != 0) {
      return (mode != 0xd) + 0x12;
    }
  }
  return mode;
}


/* ==== insn_is_branch @ 00443ed0 ==== */

int __cdecl insn_is_branch(int addr,int *len)

{
  int iVar1;
  undefined1 local_128 [4];
  undefined1 auStack_124 [4];
  undefined1 auStack_120 [32];
  char cStack_100;
  char cStack_ff;
  char cStack_fe;
  char cStack_fd;
  
  if (*(undefined4 **)(cur_itype + 0x20) != (undefined4 *)0x0) {
    iVar1 = (*(code *)**(undefined4 **)(cur_itype + 0x20))(addr,len);
    return iVar1;
  }
  (*(code *)**(undefined4 **)(cur_dtype + 0x28))(0,addr,local_128);
  (*(code *)**(undefined4 **)(cur_dtype + 0x28))(0,addr + 1,auStack_124);
  (*(code *)**(undefined4 **)(cur_dtype + 0x28))(0,addr + 2,auStack_120);
  cur_itype = *(int *)(itype_tab + *cur_dev * 4);
  iVar1 = (**(code **)(cur_itype + 0x10))(local_128,&cStack_100,0,0,0);
  if (iVar1 == 0) {
    iVar1 = 1;
  }
  if (((cStack_ff == 's') && ((cStack_100 == 'b' || (cStack_100 == 'j')))) &&
     ((cStack_fe != 'e' || (cStack_fd != 't')))) {
    *len = iVar1;
    return 1;
  }
  *len = iVar1;
  return 0;
}


/* ==== step_advance @ 00443fd0 ==== */

void __cdecl step_advance(int *refresh,int *stop_run)

{
  ulong addr;
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  void *node;
  void *v;
  void *frame;
  int iVar5;
  ulong uVar6;
  bool bVar7;
  int iStack_8;
  ulong uStack_4;
  
  iVar4 = *(int *)(cur_sim + 0x34);
  addr = *(ulong *)(cur_dev + 0x1c);
  uVar6 = 0;
  bVar2 = false;
  bVar1 = false;
  bVar7 = false;
  iVar3 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(0,addr);
  if ((*(int *)(*(int *)(cur_dev + 0x40) + 0xc) != 0) || ((*(byte *)(cur_dev + 0x44) & 4) != 0)) {
    bVar2 = true;
    bVar1 = true;
  }
  if (iVar4 == 6) {
    bVar7 = addr == *(ulong *)(cur_sim + 0x17c);
    goto LAB_0044443c;
  }
  if ((iVar4 == 7) || ((iVar4 == 8 && (addr == *(ulong *)(cur_sim + 0x17c))))) {
    iVar4 = dbg_addr_to_line(addr,iVar3);
    if ((iVar4 < 1) ||
       ((iVar4 == *(int *)(cur_sim + 0x4004) &&
        (iVar4 = dbg_addr_to_fileno(addr,iVar3), iVar4 == *(int *)(cur_sim + 0x3ff8))))) {
      bVar7 = false;
      iVar4 = insn_is_branch(addr,&iStack_8);
      *(undefined4 *)(cur_sim + 0x180) = 0;
      *(ulong *)(cur_sim + 0x17c) = iStack_8 + addr;
      *(uint *)(cur_sim + 0x34) = (iVar4 != 0) + 7;
    }
    else {
      bVar7 = true;
    }
    goto LAB_0044443c;
  }
  if (iVar4 == 9) {
    if ((addr == *(ulong *)(cur_sim + 0x17c)) &&
       (iVar4 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))
                          (*(undefined4 *)(cur_sim + 0x180),addr), iVar3 == iVar4)) {
      bVar2 = true;
      bVar1 = true;
    }
    goto LAB_0044443c;
  }
  if ((iVar4 == 10) || (iVar4 == 0xf)) {
    iVar4 = step_classify_insn(addr);
    *(int *)(cur_sim + 0x34) = iVar4;
    goto LAB_0044443c;
  }
  if ((iVar4 == 0xb) || (iVar4 == 0x10)) {
    if (addr == *(ulong *)(cur_sim + 0x17c)) {
      iVar4 = step_classify_insn(addr);
      *(int *)(cur_sim + 0x34) = iVar4;
    }
    goto LAB_0044443c;
  }
  if (iVar4 == 0xc) {
    bVar2 = true;
    bVar1 = true;
    goto LAB_0044443c;
  }
  if (iVar4 == 0x11) {
    cdb_finish_call(&uStack_4);
    iVar4 = eval_tree_core_thunk();
    if (iVar4 == 1) {
      cdb_saved_pop();
      if (node == (void *)0x0) {
        v = (void *)0x0;
      }
      else {
        v = *(void **)((int)node + 0x10);
      }
      if (v != (void *)0x0) {
        cdb_print_typed_value(uStack_4,v);
        cdb_frame_current();
        if (frame != (void *)0x0) {
          cdb_frame_refresh_text(frame);
        }
        cdb_free_expr(node);
        bVar1 = false;
        bVar2 = true;
        goto LAB_0044443c;
      }
    }
    else if (iVar4 == 2) goto LAB_0044443c;
    bVar1 = false;
    bVar2 = true;
    goto LAB_0044443c;
  }
  if ((iVar4 == 0xd) || (iVar4 == 0xe)) {
LAB_004441e9:
    if ((iVar4 == 0x12) || (iVar4 == 0x13)) {
LAB_004441f3:
      uVar6 = cdb_func_body_addr(addr);
    }
    if ((uVar6 == 0) && ((iVar4 == 0x12 || (iVar4 == 0x13)))) {
      *(uint *)(cur_sim + 0x34) = (iVar4 != 0x12) + 0xd;
      iVar4 = *(int *)(cur_sim + 0x34);
    }
    if (uVar6 != 0) {
      if (uVar6 == addr) {
        *(int *)(cur_sim + 0x28) = *(int *)(cur_sim + 0x28) + -1;
        if (*(int *)(cur_sim + 0x28) == 0) {
          bVar2 = true;
          bVar1 = true;
        }
        else {
          if (iVar4 == 0x15) {
            bVar1 = true;
          }
          iVar4 = step_mode_at_pc((-(uint)(iVar4 != 0x14) & 0xfffffffe) + 3);
          *(int *)(cur_sim + 0x34) = iVar4;
        }
      }
      else {
        *(undefined4 *)(cur_sim + 0x180) = 0;
        *(ulong *)(cur_sim + 0x17c) = uVar6;
        *(uint *)(cur_sim + 0x34) = (iVar4 != 0x12) + 0x14;
      }
      goto LAB_0044443c;
    }
    iVar5 = dbg_addr_to_line(addr,iVar3);
    if ((iVar5 < 1) ||
       ((iVar5 == *(int *)(cur_sim + 0x4004) &&
        (iVar3 = dbg_addr_to_fileno(addr,iVar3), iVar3 == *(int *)(cur_sim + 0x3ff8))))) {
      iVar3 = insn_is_branch(addr,&iStack_8);
      if (iVar3 != 0) {
        *(uint *)(cur_sim + 0x34) = (iVar4 != 0xd) + 0x12;
      }
      goto LAB_0044443c;
    }
    *(int *)(cur_sim + 0x28) = *(int *)(cur_sim + 0x28) + -1;
    if (*(int *)(cur_sim + 0x28) == 0) {
      bVar2 = true;
      bVar1 = true;
      goto LAB_0044443c;
    }
    if (iVar4 == 0xe) {
      bVar1 = true;
    }
    iVar4 = iVar4 + -0xd;
  }
  else {
    if (iVar4 == 0x12) goto LAB_004441f3;
    if (iVar4 == 0x13) goto LAB_004441e9;
    if (((iVar4 != 0x14) && (iVar4 != 0x15)) || (addr != *(ulong *)(cur_sim + 0x17c))) {
      if (iVar4 == 5) {
        bVar7 = true;
      }
      goto LAB_0044443c;
    }
    *(int *)(cur_sim + 0x28) = *(int *)(cur_sim + 0x28) + -1;
    if (*(int *)(cur_sim + 0x28) == 0) {
      bVar2 = true;
      bVar1 = true;
      goto LAB_0044443c;
    }
    if (iVar4 == 0x15) {
      bVar1 = true;
    }
    iVar4 = iVar4 + -0x14;
  }
  iVar4 = step_mode_at_pc((-(uint)(iVar4 != 0) & 0xfffffffe) + 3);
  *(int *)(cur_sim + 0x34) = iVar4;
LAB_0044443c:
  if (bVar7) {
    *(int *)(cur_sim + 0x28) = *(int *)(cur_sim + 0x28) + -1;
    if (*(int *)(cur_sim + 0x28) == 0) {
      bVar2 = true;
      bVar1 = true;
    }
    else {
      step_setup_next();
    }
  }
  if (bVar1) {
    *refresh = 1;
  }
  if (bVar2) {
    *stop_run = 1;
  }
  return;
}


/* ==== step_classify_insn @ 004444a0 ==== */

int __cdecl step_classify_insn(int addr)

{
  int iVar1;
  int iVar2;
  int local_12c;
  undefined1 local_128 [4];
  undefined1 auStack_124 [4];
  undefined1 auStack_120 [32];
  char cStack_100;
  char cStack_ff;
  char cStack_fe;
  char cStack_fd;
  
  iVar1 = *(int *)(cur_sim + 0x34);
  if (*(int *)(cur_itype + 0x20) == 0) {
    (*(code *)**(undefined4 **)(cur_dtype + 0x28))(0,addr,local_128);
    (*(code *)**(undefined4 **)(cur_dtype + 0x28))(0,addr + 1,auStack_124);
    (*(code *)**(undefined4 **)(cur_dtype + 0x28))(0,addr + 2,auStack_120);
    cur_itype = *(int *)(itype_tab + *cur_dev * 4);
    iVar2 = (**(code **)(cur_itype + 0x10))(local_128,&cStack_100,0,0,0);
    if (((cStack_100 == 'r') && (cStack_ff == 't')) && (cStack_fe == 's')) {
      if ((0xe < iVar1) && (iVar1 < 0x12)) {
        return 0x11;
      }
      return 0xc;
    }
    if (((cStack_ff == 's') && ((cStack_100 == 'b' || (cStack_100 == 'j')))) &&
       ((cStack_fe != 'e' || (cStack_fd != 't')))) {
      *(undefined4 *)(cur_sim + 0x180) = 0;
      *(int *)(cur_sim + 0x17c) = iVar2 + addr;
      if ((0xe < iVar1) && (iVar1 < 0x12)) {
        return 0x10;
      }
      return 0xb;
    }
    if ((0xe < iVar1) && (iVar1 < 0x12)) {
      return 0xf;
    }
  }
  else {
    iVar2 = (**(code **)(*(int *)(cur_itype + 0x20) + 4))(addr,&local_12c);
    if (iVar2 != 0) {
      if ((0xe < iVar1) && (iVar1 < 0x12)) {
        return 0x11;
      }
      return 0xc;
    }
    iVar2 = (*(code *)**(undefined4 **)(cur_itype + 0x20))(addr,&local_12c);
    if (iVar2 != 0) {
      *(undefined4 *)(cur_sim + 0x180) = 0;
      *(int *)(cur_sim + 0x17c) = local_12c + addr;
      if ((0xe < iVar1) && (iVar1 < 0x12)) {
        return 0x10;
      }
      return 0xb;
    }
    if (0xe < iVar1) {
      if (iVar1 < 0x12) {
        return 0xf;
      }
      return 10;
    }
  }
  return 10;
}


/* ==== step_setup_next @ 004446d0 ==== */

void step_setup_next(void)

{
  uint addr;
  int iVar1;
  int iVar2;
  int iVar3;
  int iStack_4;
  
  addr = *(uint *)(cur_dev + 0x1c);
  iVar1 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(0,addr);
  iVar2 = insn_is_branch(addr,&iStack_4);
  *(undefined4 *)(cur_sim + 0x180) = 0;
  *(uint *)(cur_sim + 0x17c) = iStack_4 + addr;
  if ((((*(int *)(cur_sim + 0x38) == 0) &&
       ((*(int *)(cur_sim + 0x4400) == 2 || (*(int *)(cur_sim + 0x4404) != 0)))) ||
      (*(int *)(cur_sim + 0x38) == 2)) && (iVar3 = dbg_addr_to_line(addr,iVar1), 0 < iVar3)) {
    iVar1 = dbg_addr_to_fileno(addr,iVar1);
    *(int *)(cur_sim + 0x3ff8) = iVar1;
    *(int *)(cur_sim + 0x4004) = iVar3;
    *(uint *)(cur_sim + 0x34) = (iVar2 != 0) + 7;
    return;
  }
  *(uint *)(cur_sim + 0x34) = (iVar2 != 0) + 5;
  return;
}


/* ==== cmd_next_h0 @ 004447b0 ==== */

void cmd_next_h0(void)

{
  int dev;
  undefined4 uVar1;
  int dev_00;
  
  *(undefined4 *)(cur_sim + 0x3c) = 0;
  *(undefined4 *)(cur_sim + 0x38) = 0;
  uVar1 = DAT_004a96c0;
  if (DAT_004a93ea != 'i') {
    uVar1 = 1;
  }
  *(undefined4 *)(cur_sim + 0x28) = uVar1;
  *(undefined4 *)(cur_sim + 0x2c) = 0;
  step_setup_next();
  dev = cur_dev_index;
  dev_00 = 0;
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


/* ==== cmd_next_h1 @ 00444860 ==== */

void cmd_next_h1(void)

{
  int dev;
  undefined4 uVar1;
  int dev_00;
  
  *(undefined4 *)(cur_sim + 0x3c) = 1;
  *(undefined4 *)(cur_sim + 0x38) = 0;
  uVar1 = DAT_004a96c0;
  if (DAT_004a93ea != 'i') {
    uVar1 = 1;
  }
  *(undefined4 *)(cur_sim + 0x28) = uVar1;
  *(undefined4 *)(cur_sim + 0x2c) = 0;
  step_setup_next();
  dev = cur_dev_index;
  dev_00 = 0;
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


/* ==== cmd_next_h2 @ 00444880 ==== */

void cmd_next_h2(void)

{
  int dev;
  undefined4 uVar1;
  int dev_00;
  
  *(undefined4 *)(cur_sim + 0x3c) = 0;
  *(undefined4 *)(cur_sim + 0x38) = 2;
  uVar1 = DAT_004a96c0;
  if (DAT_004a93ea != 'i') {
    uVar1 = 1;
  }
  *(undefined4 *)(cur_sim + 0x28) = uVar1;
  *(undefined4 *)(cur_sim + 0x2c) = 0;
  step_setup_next();
  dev = cur_dev_index;
  dev_00 = 0;
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


/* ==== cmd_next_h3 @ 004448a0 ==== */

void cmd_next_h3(void)

{
  int dev;
  undefined4 uVar1;
  int dev_00;
  
  *(undefined4 *)(cur_sim + 0x3c) = 1;
  *(undefined4 *)(cur_sim + 0x38) = 2;
  uVar1 = DAT_004a96c0;
  if (DAT_004a93ea != 'i') {
    uVar1 = 1;
  }
  *(undefined4 *)(cur_sim + 0x28) = uVar1;
  *(undefined4 *)(cur_sim + 0x2c) = 0;
  step_setup_next();
  dev = cur_dev_index;
  dev_00 = 0;
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


/* ==== cmd_next_h4 @ 004448c0 ==== */

void cmd_next_h4(void)

{
  int dev;
  undefined4 uVar1;
  int dev_00;
  
  *(undefined4 *)(cur_sim + 0x3c) = 0;
  *(undefined4 *)(cur_sim + 0x38) = 1;
  uVar1 = DAT_004a96c0;
  if (DAT_004a93ea != 'i') {
    uVar1 = 1;
  }
  *(undefined4 *)(cur_sim + 0x28) = uVar1;
  *(undefined4 *)(cur_sim + 0x2c) = 0;
  step_setup_next();
  dev = cur_dev_index;
  dev_00 = 0;
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


/* ==== cmd_next_h5 @ 004448e0 ==== */

void cmd_next_h5(void)

{
  int dev;
  undefined4 uVar1;
  int dev_00;
  
  *(undefined4 *)(cur_sim + 0x3c) = 1;
  *(undefined4 *)(cur_sim + 0x38) = 1;
  uVar1 = DAT_004a96c0;
  if (DAT_004a93ea != 'i') {
    uVar1 = 1;
  }
  *(undefined4 *)(cur_sim + 0x28) = uVar1;
  *(undefined4 *)(cur_sim + 0x2c) = 0;
  step_setup_next();
  dev = cur_dev_index;
  dev_00 = 0;
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


/* ==== cmd_next_parse @ 00444900 ==== */

undefined ** cmd_next_parse(void)

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
        if (iVar1 == 0) goto LAB_00444ab3;
        iVar1 = parm_count_expr(2);
        if (iVar1 == 0) goto LAB_00444ab3;
        iVar1 = parm_keyword1(4,&DAT_004c6aa8);
        if (iVar1 == 0) goto LAB_00444ab3;
        iVar1 = parm_keyword1(3,&DAT_004a8688);
        if (iVar1 != 0) {
          iVar2 = 3;
          goto LAB_00444ab3;
        }
        iVar1 = parm_keyword1(3,&DAT_004c7dec);
        if (iVar1 == 0) goto LAB_00444ab3;
      }
      else {
        iVar1 = parm_keyword1(3,&DAT_004c6aa8);
        if (iVar1 == 0) {
          iVar1 = parm_count_expr(2);
          if (iVar1 != 0) {
            iVar1 = parm_keyword1(3,&DAT_004a8688);
            if (iVar1 == 0) {
              iVar1 = parm_keyword1(3,&DAT_004c7dec);
              if (iVar1 != 0) {
                iVar2 = 4;
              }
            }
            else {
              iVar2 = 2;
            }
          }
          goto LAB_00444ab3;
        }
        iVar1 = parm_keyword1(2,&DAT_004a8688);
        if (iVar1 != 0) {
          iVar2 = 3;
          goto LAB_00444ab3;
        }
        iVar1 = parm_keyword1(2,&DAT_004c7dec);
        if (iVar1 == 0) {
          iVar1 = parm_count_expr(2);
          if (iVar1 != 0) {
            iVar2 = 1;
          }
          goto LAB_00444ab3;
        }
      }
      iVar2 = 5;
    }
    else {
      iVar1 = parm_keyword1(2,&DAT_004c6aa8);
      if (iVar1 == 0) {
        iVar1 = parm_keyword1(2,&DAT_004a8688);
        if (iVar1 == 0) {
          iVar1 = parm_keyword1(2,&DAT_004c7dec);
          if (iVar1 == 0) {
            iVar1 = parm_count_expr(2);
            if (iVar1 != 0) {
              iVar2 = 0;
            }
          }
          else {
            iVar2 = 4;
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
  }
  else {
    iVar2 = 0;
  }
LAB_00444ab3:
  if (iVar2 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_next_h0_004c6e90 + iVar2 * 2;
}


/* ==== parse_line_spec @ 00444ad0 ==== */

int __cdecl parse_line_spec(int tok)

{
  int iVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  char *name;
  int iVar6;
  int local_10;
  int local_8;
  int local_4;
  
  iVar1 = tok;
  iVar5 = *(int *)(cur_sim + 0x3ff8);
  iVar3 = (&g_tok_start)[tok];
  iVar6 = 0;
  cVar2 = (&g_cmdline)[iVar3];
  name = &g_cmdline + iVar3;
  local_10 = 0;
  do {
    if (cVar2 == '\0') {
LAB_00444b49:
      uVar4 = strtol(name,(char **)&tok,10);
      if ((((char *)tok != name) && (*(char *)tok == '\0')) &&
         (uVar4 = dbg_line_to_addr(iVar5,uVar4,&local_8), uVar4 != 0)) {
        (&g_tok_type)[iVar1] = 0x70;
        iVar1 = iVar1 * 0x28;
        *(int *)(&DAT_004a967c + iVar1) = local_8;
        *(int *)(&DAT_004a9680 + iVar1) = local_4;
        iVar5 = memmap_find(local_4,*(ulong *)(&DAT_004a967c + iVar1));
        *(short *)(&DAT_004a968c + iVar1) = (short)iVar5;
        *(undefined4 *)(&g_tok_val + iVar1) = *(undefined4 *)(&DAT_004a967c + iVar1);
        *(undefined4 *)(&DAT_004a9684 + iVar1) = 0x4100;
        local_10 = 1;
      }
      if (local_10 == 0) {
        parm_errmsg = s_Invalid_line_number_004c7df0;
        g_err_tok = iVar3;
      }
      return local_10;
    }
    if (cVar2 == '@') {
      name[iVar6] = '\0';
      if (*name == '\0') {
        name[iVar6] = '@';
        name = &DAT_004a92e9 + iVar6 + iVar3;
      }
      else {
        iVar5 = dbg_find_source_file(name);
        name[iVar6] = '@';
        name = &DAT_004a92e9 + iVar6 + iVar3;
        if (iVar5 < 0) {
          return 0;
        }
      }
      goto LAB_00444b49;
    }
    cVar2 = (&DAT_004a92e9)[iVar6 + iVar3];
    iVar6 = iVar6 + 1;
  } while( true );
}


/* ==== dbg_line_to_addr @ 00444bf0 ==== */

uint __cdecl dbg_line_to_addr(int fileno,uint line,int *addr_space)

{
  int iVar1;
  uint uVar2;
  ulong addr;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int local_8;
  
  iVar4 = 0;
  if (fileno < 0) {
    iVar8 = 0;
    addr = cdb_frame_pc();
    fileno = dbg_addr_to_fileno(addr,iVar8);
  }
  local_8 = 0;
  iVar8 = *(int *)(cur_sim + 0x3ff0);
  piVar5 = *(int **)(cur_sim + 0x4048);
  if ((iVar8 == 0) || (piVar5 == (int *)0x0)) {
    return 0;
  }
  if (*(int *)(cur_sim + 0x4014) == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = *(int *)(*(int *)(cur_sim + 0x4014) + 0x34);
  }
  uVar7 = 0xffffffff;
  uVar6 = 0xffffffff;
  iVar1 = local_8;
  if (0 < iVar3) {
    do {
      iVar1 = *piVar5;
      uVar2 = *(uint *)(iVar8 + 8 + iVar1 * 0xc);
      uVar7 = uVar6;
      if ((uVar2 != 0) && (fileno == piVar5[1])) {
        uVar7 = line;
        if (uVar2 == line) break;
        uVar7 = uVar6;
        if (((int)line < (int)uVar2) && (uVar2 < uVar6)) {
          uVar7 = uVar2;
          local_8 = iVar1;
        }
      }
      iVar4 = iVar4 + 1;
      piVar5 = piVar5 + 2;
      uVar6 = uVar7;
      iVar1 = local_8;
    } while (iVar4 < iVar3);
  }
  local_8 = iVar1;
  *addr_space = *(int *)(iVar8 + local_8 * 0xc);
  addr_space[1] = *(int *)(iVar8 + 4 + local_8 * 0xc);
  return -(uint)(uVar7 != 0xffffffff) & uVar7;
}


/* ==== dbg_find_source_file @ 00444cd0 ==== */

int __cdecl dbg_find_source_file(char *name)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  undefined4 *puVar4;
  byte *pbVar5;
  int iVar6;
  bool bVar7;
  
  iVar6 = *(int *)(cur_sim + 0x401c) + -1;
  if (iVar6 < 0) {
    return -1;
  }
  puVar4 = (undefined4 *)(*(int *)(cur_sim + 0x4020) + 8 + iVar6 * 0xc);
  do {
    pbVar2 = (byte *)*puVar4;
    pbVar5 = (byte *)name;
    if (pbVar2 != (byte *)0x0) {
      do {
        bVar1 = *pbVar2;
        bVar7 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_00444d21:
          iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
          goto LAB_00444d26;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar2[1];
        bVar7 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_00444d21;
        pbVar2 = pbVar2 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_00444d26:
      if (iVar3 == 0) {
        return iVar6;
      }
    }
    iVar6 = iVar6 + -1;
    puVar4 = puVar4 + -3;
    if (iVar6 < 0) {
      return -1;
    }
  } while( true );
}


/* ==== dbg_parse_file_line @ 00444d50 ==== */

int __cdecl dbg_parse_file_line(char *arg,void *value,uint *line)

{
  char cVar1;
  uint uVar2;
  int fileno;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int local_8;
  undefined4 local_4;
  
  pcVar5 = arg;
  fileno = *(int *)(cur_sim + 0x3ff8);
  iVar3 = 0;
  iVar4 = 0;
  cVar1 = *arg;
  do {
    if (cVar1 == '\0') {
      if (fileno < 0) {
        return 0;
      }
LAB_00444d8b:
      uVar2 = strtol(pcVar5,&arg,10);
      if ((arg != pcVar5) && (*arg == '\0')) {
        uVar2 = dbg_line_to_addr(fileno,uVar2,&local_8);
        *line = uVar2;
        if (uVar2 != 0) {
          iVar3 = 1;
          *(int *)((int)value + 0x14) = local_8;
          *(undefined4 *)((int)value + 0x18) = local_4;
        }
      }
      return iVar3;
    }
    if (cVar1 == '@') {
      arg[iVar4] = '\0';
      fileno = dbg_find_source_file(arg);
      pcVar5[iVar4] = '@';
      pcVar5 = pcVar5 + iVar4 + 1;
      if (fileno < 0) {
        return 0;
      }
      goto LAB_00444d8b;
    }
    cVar1 = arg[iVar4 + 1];
    iVar4 = iVar4 + 1;
  } while( true );
}


/* ==== cmd_until_h0 @ 00444e10 ==== */

void cmd_until_h0(void)

{
  int dev;
  int dev_00;
  
  *(undefined4 *)(cur_sim + 0x3c) = 0;
  dev_00 = 0;
  *(undefined4 *)(cur_sim + 0x28) = 0;
  *(undefined4 *)(cur_sim + 0x2c) = 0;
  *(undefined4 *)(cur_sim + 0x34) = 9;
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
  *(undefined4 *)(cur_sim + 0x17c) = DAT_004a96cc;
  *(undefined4 *)(cur_sim + 0x180) = DAT_004a96d0;
  periph_reset();
  *(undefined4 *)(cur_sim + 0x40) = 1;
  return;
}


/* ==== cmd_until_h1 @ 00444ee0 ==== */

void cmd_until_h1(void)

{
  int dev;
  int dev_00;
  
  *(undefined4 *)(cur_sim + 0x3c) = 1;
  dev_00 = 0;
  *(undefined4 *)(cur_sim + 0x28) = 0;
  *(undefined4 *)(cur_sim + 0x2c) = 0;
  *(undefined4 *)(cur_sim + 0x34) = 9;
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
  *(undefined4 *)(cur_sim + 0x17c) = DAT_004a96cc;
  *(undefined4 *)(cur_sim + 0x180) = DAT_004a96d0;
  periph_reset();
  *(undefined4 *)(cur_sim + 0x40) = 1;
  return;
}


/* ==== cmd_until_parse @ 00444f00 ==== */

undefined ** cmd_until_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_match_space_cur(2);
  if (iVar1 != 0) {
    iVar1 = parm_check_too_many(3);
    if (iVar1 == 0) {
      iVar1 = parm_keyword1(3,&DAT_004c6aa8);
      if (iVar1 != 0) {
        iVar1 = parm_check_too_many(4);
        if (iVar1 != 0) {
          iVar2 = 1;
        }
      }
    }
    else {
      iVar2 = 0;
    }
  }
  if (iVar2 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_until_h0_004c6f40 + iVar2 * 2;
}


/* ==== cmd_view_h0 @ 00444f60 ==== */

void cmd_view_h0(void)

{
  char cVar1;
  int iVar2;
  
  if (DAT_004a93ea == 'j') {
    cVar1 = (&cmd_tokbuf)[DAT_004a9470];
    if (cVar1 == 'a') {
      *(undefined4 *)(cur_sim + 0x4400) = 1;
    }
    else if (cVar1 == 'r') {
      *(undefined4 *)(cur_sim + 0x4400) = 0;
    }
    else if (cVar1 == 's') {
      *(undefined4 *)(cur_sim + 0x4400) = 2;
    }
  }
  else {
    iVar2 = *(int *)(cur_sim + 0x4400);
    if (iVar2 == 0) {
      *(uint *)(cur_sim + 0x4400) = (*(int *)(cur_sim + 0x3fd8) != 0) + 1;
    }
    else if (iVar2 == 1) {
      *(undefined4 *)(cur_sim + 0x4400) = 0;
    }
    else if (iVar2 == 2) {
      *(undefined4 *)(cur_sim + 0x4400) = 1;
    }
  }
  iVar2 = *(int *)(cur_sim + 0x4400);
  if (iVar2 == 0) {
    scrollback_end(cur_dev_index);
  }
  else if ((0 < iVar2) && (iVar2 < 3)) {
    win_update(0x7fff);
    return;
  }
  return;
}


