/* ==== dev_spaces_call_c @ 00456f60 ==== */

void __cdecl dev_spaces_call_c(long a,long b,long c)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  if (0 < *(int *)(cur_dtype + 0x14)) {
    iVar2 = 0;
    do {
      (**(code **)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + iVar2) + 0xc))(iVar1,a,b,c);
      iVar1 = iVar1 + 1;
      iVar2 = iVar2 + 0x48;
    } while (iVar1 < *(int *)(cur_dtype + 0x14));
  }
  return;
}


/* ==== dev_spaces_call_8 @ 00456fb0 ==== */

void __cdecl dev_spaces_call_8(long a,long *out,long c)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  *out = 0;
  if (0 < *(int *)(cur_dtype + 0x14)) {
    iVar2 = 0;
    do {
      (**(code **)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + iVar2) + 8))(iVar1,a,out,c);
      iVar1 = iVar1 + 1;
      iVar2 = iVar2 + 0x48;
    } while (iVar1 < *(int *)(cur_dtype + 0x14));
  }
  return;
}


/* ==== dev_call_slot1 @ 00457000 ==== */

long __cdecl dev_call_slot1(int dev,long a,long b,long c)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  
  uVar2 = cur_dev;
  uVar1 = cur_dtype;
  cur_dev = *(int **)(dev_tab + dev * 4);
  lVar3 = 0;
  if (cur_dev != (int *)0x0) {
    cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
    lVar3 = (**(code **)(*(int *)(cur_dtype + 0x28) + 4))(a,b,c);
  }
  cur_dtype = uVar1;
  cur_dev = (int *)uVar2;
  return lVar3;
}


/* ==== dev_call_slot14 @ 00457060 ==== */

long __cdecl dev_call_slot14(int dev,long a,long b,long c)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  
  uVar2 = cur_dev;
  uVar1 = cur_dtype;
  cur_dev = *(int **)(dev_tab + dev * 4);
  lVar3 = 0;
  if (cur_dev != (int *)0x0) {
    cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
    lVar3 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0x38))(a,b,c);
  }
  cur_dtype = uVar1;
  cur_dev = (int *)uVar2;
  return lVar3;
}


/* ==== dev_call_slot15 @ 004570c0 ==== */

long __cdecl dev_call_slot15(int dev,long a,long b,long c)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  
  uVar2 = cur_dev;
  uVar1 = cur_dtype;
  cur_dev = *(int **)(dev_tab + dev * 4);
  lVar3 = 0;
  if (cur_dev != (int *)0x0) {
    cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
    lVar3 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0x3c))(a,b,c);
  }
  cur_dtype = uVar1;
  cur_dev = (int *)uVar2;
  return lVar3;
}


/* ==== dev_call_slot13 @ 00457120 ==== */

long __cdecl dev_call_slot13(int dev,long a,long b,long c)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  
  uVar2 = cur_dev;
  uVar1 = cur_dtype;
  cur_dev = *(int **)(dev_tab + dev * 4);
  lVar3 = 0;
  if (cur_dev != (int *)0x0) {
    cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
    lVar3 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0x34))(a,b,c);
  }
  cur_dtype = uVar1;
  cur_dev = (int *)uVar2;
  return lVar3;
}


/* ==== dev_mem_read @ 00457180 ==== */

long __cdecl dev_mem_read(int dev,long a,long b,long c)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  
  uVar2 = cur_dev;
  uVar1 = cur_dtype;
  cur_dev = *(int **)(dev_tab + dev * 4);
  lVar3 = 0;
  if (cur_dev != (int *)0x0) {
    cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
    lVar3 = (*(code *)**(undefined4 **)(cur_dtype + 0x28))(a,b,c);
  }
  cur_dtype = uVar1;
  cur_dev = (int *)uVar2;
  return lVar3;
}


/* ==== dev_call_slot10 @ 004571e0 ==== */

long __cdecl dev_call_slot10(int dev,long a,long b,long c)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  
  uVar2 = cur_dev;
  uVar1 = cur_dtype;
  cur_dev = *(int **)(dev_tab + dev * 4);
  lVar3 = 0;
  if (cur_dev != (int *)0x0) {
    cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
    lVar3 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0x28))(a,b,c);
  }
  cur_dtype = uVar1;
  cur_dev = (int *)uVar2;
  return lVar3;
}


/* ==== dev_call_slot11 @ 00457240 ==== */

long __cdecl dev_call_slot11(int dev,long a,long b,long c)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  
  uVar2 = cur_dev;
  uVar1 = cur_dtype;
  cur_dev = *(int **)(dev_tab + dev * 4);
  lVar3 = 0;
  if (cur_dev != (int *)0x0) {
    cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
    lVar3 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0x2c))(a,b,c);
  }
  cur_dtype = uVar1;
  cur_dev = (int *)uVar2;
  return lVar3;
}


/* ==== dev_call_slot12 @ 004572a0 ==== */

long __cdecl dev_call_slot12(int dev,long a,long b,long c)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  
  uVar2 = cur_dev;
  uVar1 = cur_dtype;
  cur_dev = *(int **)(dev_tab + dev * 4);
  lVar3 = 0;
  if (cur_dev != (int *)0x0) {
    cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
    lVar3 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0x30))(a,b,c);
  }
  cur_dtype = uVar1;
  cur_dev = (int *)uVar2;
  return lVar3;
}


/* ==== dev_call_slot2 @ 00457300 ==== */

long __cdecl dev_call_slot2(int dev,long a,long b,long c,long d)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  
  uVar2 = cur_dev;
  uVar1 = cur_dtype;
  cur_dev = *(int **)(dev_tab + dev * 4);
  lVar3 = 0;
  if (cur_dev != (int *)0x0) {
    cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
    lVar3 = (**(code **)(*(int *)(cur_dtype + 0x28) + 8))(a,b,c,d);
  }
  cur_dtype = uVar1;
  cur_dev = (int *)uVar2;
  return lVar3;
}


/* ==== dev_find_space @ 00457370 ==== */

int __cdecl dev_find_space(int dev,char *name,long *pid)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  uVar2 = cur_dev;
  uVar1 = cur_dtype;
  cur_dev = *(int **)(dev_tab + dev * 4);
  if (cur_dev != (int *)0x0) {
    iVar4 = 0;
    cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
    if (0 < *(int *)(cur_dtype + 0x1c)) {
      iVar5 = 0;
      do {
        iVar3 = stricmp_ci(name,*(char **)(*(int *)(cur_dtype + 0x20) + iVar5));
        if (iVar3 == 0) {
          *pid = *(long *)(*(int *)(cur_dtype + 0x20) + 4 + iVar4 * 0x2c);
          cur_dtype = uVar1;
          cur_dev = (int *)uVar2;
          return 1;
        }
        iVar4 = iVar4 + 1;
        iVar5 = iVar5 + 0x2c;
      } while (iVar4 < *(int *)(cur_dtype + 0x1c));
    }
  }
  cur_dtype = uVar1;
  cur_dev = (int *)uVar2;
  return 0;
}


/* ==== stricmp_ci @ 00457420 ==== */

int __cdecl stricmp_ci(char *a,char *b)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  
  pcVar3 = b;
  do {
    b._0_1_ = *a;
    cVar1 = *pcVar3;
    a = a + 1;
    pcVar3 = pcVar3 + 1;
    if ((char)b != cVar1) {
      iVar4 = (int)(char)b;
      if (__mb_cur_max < 2) {
        uVar2 = (byte)_pctype[iVar4 * 2] & 1;
      }
      else {
        uVar2 = _isctype(iVar4,1);
      }
      if (uVar2 != 0) {
        iVar4 = tolower(iVar4);
        b._0_1_ = (char)iVar4;
      }
      iVar4 = (int)cVar1;
      if (__mb_cur_max < 2) {
        uVar2 = (byte)_pctype[iVar4 * 2] & 1;
      }
      else {
        uVar2 = _isctype(iVar4,1);
      }
      if (uVar2 != 0) {
        iVar4 = tolower(iVar4);
        cVar1 = (char)iVar4;
      }
    }
  } while ((((char)b != '\0') && (cVar1 != '\0')) && ((char)b == cVar1));
  return (int)(char)b - (int)cVar1;
}


/* ==== space_notify @ 004574d0 ==== */

void __cdecl space_notify(int space_idx,ulong addr,ulong val,int arg)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar5 = 0;
  uVar1 = *(uint *)(*(int *)(cur_dtype + 0x20) + 8 + space_idx * 0x2c);
  if (0 < *(int *)(cur_dtype + 0x1c)) {
    iVar6 = 0;
    iVar7 = 0;
    iVar4 = cur_dtype;
    do {
      iVar3 = *(int *)(iVar4 + 0x20) + iVar7;
      uVar2 = *(uint *)(iVar3 + 8);
      if (((uVar2 & uVar1) == uVar2) && ((char)uVar2 == (char)uVar1)) {
        rangemap_set((void *)(*(int *)(cur_sim + 4) + 8 + iVar6),addr,val,*(int *)(iVar3 + 0x20),arg
                    );
        iVar4 = cur_dtype;
      }
      iVar5 = iVar5 + 1;
      iVar7 = iVar7 + 0x2c;
      iVar6 = iVar6 + 300;
    } while (iVar5 < *(int *)(iVar4 + 0x1c));
  }
  return;
}


/* ==== mem_addr_check @ 00457560 ==== */

int __cdecl mem_addr_check(int space_idx,ulong addr)

{
  int iVar1;
  
  iVar1 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))
                    (*(undefined4 *)(*(int *)(cur_dtype + 0x20) + 4 + space_idx * 0x2c),addr);
  iVar1 = memmap_find(iVar1,addr);
  if (iVar1 == -1) {
    return 0;
  }
  iVar1 = rangemap_get((void *)(*(int *)(cur_sim + 4) + 8 + iVar1 * 300),addr);
  return iVar1;
}


/* ==== fmt_addr @ 004575c0 ==== */

void __cdecl fmt_addr(ulong addr,char *buf)

{
  uint uVar1;
  char *fmt;
  
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar1 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar1 = (**(code **)(cur_dtype + 0x4e8))();
  }
  if ((uVar1 & 0xc00) == 0) {
    if ((uVar1 & 0x200) == 0) {
      fmt = s__04lx_004d283c;
      if ((uVar1 & 8) == 0) {
        fmt = s__08lx_004d282c;
      }
    }
    else {
      fmt = s__06lx_004d2834;
    }
  }
  else {
    fmt = s__04lx_004d283c;
  }
  sprintf(buf,fmt,(-(uint)((uVar1 & 0x800) != 0) & 0x10000) - 1 & addr);
  return;
}


/* ==== fmt_read_word @ 00457630 ==== */

long __cdecl fmt_read_word(long space,ulong addr,int radix,char *out,char *nanfmt)

{
  code *pcVar1;
  char cVar2;
  long lVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  undefined3 extraout_var;
  uint uVar7;
  char *pcVar8;
  int iStack_50;
  undefined4 uStack_4c;
  uint local_48;
  uint uStack_44;
  undefined4 uStack_34;
  long lStack_20;
  undefined4 uStack_1c;
  
  pcVar1 = (code *)(*(undefined4 **)(cur_dtype + 0x28))[0xb];
  if (pcVar1 == (code *)0x0) {
    lVar3 = (*(code *)**(undefined4 **)(cur_dtype + 0x28))(space,addr,&local_48);
  }
  else {
    lVar3 = (*pcVar1)(space,addr,&local_48);
  }
  iVar4 = memmap_find(space,addr);
  uVar7 = *(uint *)(*(int *)(cur_dtype + 0x20) + 0x24 + iVar4 * 0x2c);
  uStack_34 = CONCAT22((short)((uVar7 & 0xff400003) >> 0x10),CONCAT11(1,(char)(uVar7 & 0xff400003)))
  ;
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar5 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar5 = (**(code **)(cur_dtype + 0x4e8))();
  }
  if ((uVar7 & 2) == 0) {
    if (radix != 2) {
      if (radix == 1) {
        if ((uVar7 & 0x80000000) == 0) {
          if ((uVar7 & 0x40000000) == 0) {
            if ((uVar7 & 0x20000000) == 0) {
              if ((uVar7 & 0x10000000) == 0) {
                if ((uVar7 & 0x8000000) == 0) {
                  uVar5 = (-(uint)((uVar7 & 0x4000000) != 0) & 0x80800000) + 0x80000000;
                }
                else {
                  uVar5 = 0x80000;
                }
              }
              else {
                uVar5 = 0x8000;
              }
            }
            else {
              uVar5 = 0x800;
            }
          }
          else {
            uVar5 = 0x80;
          }
        }
        else {
          uVar5 = 8;
        }
        if ((uVar5 & local_48) != 0) {
          local_48 = local_48 | ~(uVar5 - 1);
        }
      }
      if ((uVar7 & 0x80000000) == 0) {
        if ((uVar7 & 0x40000000) == 0) {
          if ((uVar7 & 0x20000000) == 0) {
            if ((uVar7 & 0x10000000) == 0) {
              if ((uVar7 & 0x8000000) == 0) {
                if ((uVar7 & 0x4000000) == 0) {
                  pcVar6 = (&fmt_tab_32)[radix];
                }
                else {
                  pcVar6 = (&fmt_tab_24)[radix];
                }
              }
              else {
                pcVar6 = (&fmt_tab_24)[radix];
              }
            }
            else {
              pcVar6 = (&fmt_tab_16)[radix];
            }
          }
          else {
            pcVar6 = (&fmt_tab_16)[radix];
          }
        }
        else {
          pcVar6 = (&fmt_tab_16)[radix];
        }
      }
      else {
        pcVar6 = (&fmt_tab_16)[radix];
      }
      sprintf(out,pcVar6,local_48);
      return lVar3;
    }
    word_to_frac(uVar5,&iStack_50);
    if ((uVar5 & 0x80) == 0) {
      sprintf(out,s__10_7f_004c6350,iStack_50,uStack_4c);
      return lVar3;
    }
    if (nanfmt == (char *)0x0) {
      nanfmt = s__14_14s_004c6ac8;
    }
  }
  else {
    if (radix != 2) {
      if ((radix != 1) && (radix != 4)) {
        if ((uVar5 & 0x80) == 0) {
          pcVar6 = s___04lx_04lx_004c630c;
          if ((uVar5 & 0x10000000) == 0) {
            pcVar6 = s___06lx_06lx_004c62e8;
          }
        }
        else {
          pcVar6 = s___08lx_08lx_004c6300;
        }
        sprintf(out,pcVar6,uStack_44,local_48);
        return lVar3;
      }
      val_to_dec_parts(uVar5,&local_48,&lStack_20);
      sprintf(out,s__06lu_09lu_004c6250,uStack_1c,lStack_20);
      return lVar3;
    }
    if ((uVar5 & 0x1000) != 0) {
      local_48 = local_48 & 0xffff | uStack_44 << 0x10;
      uStack_44 = uStack_44 >> 8;
    }
    dword_to_frac(uVar5,&iStack_50);
    if ((uVar5 & 0x80) == 0) {
      sprintf(out,s__18_15f_004c6340,iStack_50,uStack_4c);
      return lVar3;
    }
    if (nanfmt == (char *)0x0) {
      nanfmt = s__25_25s_004c6ad0;
    }
  }
  cVar2 = fmt_float_exp(nanfmt,&iStack_50);
  uVar7 = 0xffffffff;
  pcVar6 = (char *)CONCAT31(extraout_var,cVar2);
  do {
    pcVar8 = pcVar6;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar8 = pcVar6 + 1;
    cVar2 = *pcVar6;
    pcVar6 = pcVar8;
  } while (cVar2 != '\0');
  uVar7 = ~uVar7;
  pcVar6 = pcVar8 + -uVar7;
  for (uVar5 = uVar7 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)out = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    out = out + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *out = *pcVar6;
    pcVar6 = pcVar6 + 1;
    out = out + 1;
  }
  return lVar3;
}


/* ==== fmt_word @ 00457950 ==== */

void __cdecl fmt_word(int space_idx,long addr,int radix,char *out,ulong value)

{
  char cVar1;
  uint mode;
  undefined3 extraout_var;
  int iVar2;
  char *pcVar3;
  undefined3 extraout_var_00;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  int iStack_50;
  undefined4 uStack_4c;
  uint local_48;
  uint uStack_44;
  undefined4 local_34;
  long lStack_20;
  undefined4 uStack_1c;
  
  uVar6 = *(uint *)(*(int *)(cur_dtype + 0x20) + 0x24 + space_idx * 0x2c);
  local_34 = CONCAT22((short)((uVar6 & 0xff400003) >> 0x10),CONCAT11(1,(char)(uVar6 & 0xff400003)));
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    mode = *(uint *)(cur_dtype + 0xc);
  }
  else {
    mode = (**(code **)(cur_dtype + 0x4e8))();
  }
  if ((uVar6 & 2) == 0) {
    local_48 = value;
    if (radix == 2) {
      word_to_frac(mode,&iStack_50);
      if ((mode & 0x80) == 0) {
        sprintf(out,s__10_7f_004c6350,iStack_50,uStack_4c);
        return;
      }
      cVar1 = fmt_float_exp(s__15_15s_004cb1cc,&iStack_50);
      pcVar3 = &DAT_004cb15c;
      uVar6 = CONCAT31(extraout_var_00,cVar1);
    }
    else {
      if (radix == 0) {
        if ((mode & 0x10000000) == 0) {
          iVar4 = (-(uint)((mode & 0x2000000) != 0) & 8) + 0x18;
        }
        else {
          iVar4 = 0x10;
        }
        iVar2 = 0;
        if (iVar4 != 0) {
          puVar5 = &abort_flag + iVar4;
          do {
            uVar6 = *puVar5;
            puVar5 = puVar5 + -1;
            out[iVar2] = ((value & uVar6) != 0) + '0';
            iVar2 = iVar2 + 1;
          } while (iVar2 < iVar4);
        }
        out[iVar4] = '\0';
        return;
      }
      if (radix == 1) {
        if ((uVar6 & 0x80000000) == 0) {
          if ((uVar6 & 0x40000000) == 0) {
            if ((uVar6 & 0x20000000) == 0) {
              if ((uVar6 & 0x10000000) == 0) {
                if ((uVar6 & 0x8000000) == 0) {
                  uVar6 = (-(uint)((uVar6 & 0x4000000) != 0) & 0x80800000) + 0x80000000;
                }
                else {
                  uVar6 = 0x80000;
                }
              }
              else {
                uVar6 = 0x8000;
              }
            }
            else {
              uVar6 = 0x800;
            }
          }
          else {
            uVar6 = 0x80;
          }
        }
        else {
          uVar6 = 8;
        }
        if ((value & uVar6) != 0) {
          local_48 = ~(uVar6 - 1) | value;
        }
      }
      uVar6 = local_48;
      if ((mode & 0x10000000) == 0) {
        if ((mode & 0x4000000) == 0) {
          pcVar3 = (&fmt_tab_32_nosym)[radix];
        }
        else {
          pcVar3 = (&fmt_tab_24_nosym)[radix];
        }
      }
      else {
        pcVar3 = (&fmt_tab_16_nosym)[radix];
      }
    }
    sprintf(out,pcVar3,uVar6);
    return;
  }
  (*(code *)**(undefined4 **)(cur_dtype + 0x28))
            (*(undefined4 *)(*(int *)(cur_dtype + 0x20) + 4 + space_idx * 0x2c),addr,&local_48);
  if (radix == 2) {
    dword_to_frac(mode,&iStack_50);
    if ((mode & 0x80) == 0) {
      sprintf(out,s__18_15f_004c6340,iStack_50,uStack_4c);
      return;
    }
    cVar1 = fmt_float_exp(s__18_18s_004d2870,&iStack_50);
    sprintf(out,&DAT_004cb15c,CONCAT31(extraout_var,cVar1));
    return;
  }
  if (radix != 1) {
    if (radix != 0) {
      pcVar3 = s___06lx_06lx_004c62e8;
      if ((mode & 0x4000000) == 0) {
        pcVar3 = s___08lx_08lx_004c6300;
      }
      sprintf(out,pcVar3,uStack_44,local_48);
      return;
    }
    if ((mode & 0x10000000) == 0) {
      iVar4 = (-(uint)((mode & 0x2000000) != 0) & 8) + 0x18;
    }
    else {
      iVar4 = 0x10;
    }
    iVar2 = 0;
    if (iVar4 != 0) {
      puVar5 = &abort_flag + iVar4;
      do {
        uVar6 = *puVar5;
        puVar5 = puVar5 + -1;
        out[iVar2] = ((uStack_44 & uVar6) != 0) + '0';
        iVar2 = iVar2 + 1;
      } while (iVar2 < iVar4);
    }
    iVar2 = 0;
    if (iVar4 != 0) {
      puVar5 = &abort_flag + iVar4;
      do {
        uVar6 = *puVar5;
        puVar5 = puVar5 + -1;
        out[iVar2 + iVar4] = ((local_48 & uVar6) != 0) + '0';
        iVar2 = iVar2 + 1;
      } while (iVar2 < iVar4);
    }
    out[iVar4 * 2] = '\0';
    return;
  }
  val_to_dec_parts(mode,&local_48,&lStack_20);
  sprintf(out,s__06ld_09ld_004d2864,uStack_1c,lStack_20);
  return;
}


/* ==== mem_trace_access @ 00457cc0 ==== */

void __cdecl mem_trace_access(ulong space,ulong addr,int is_write,long value)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint addr_00;
  int iVar6;
  
  iVar6 = 0;
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar1 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar1 = (**(code **)(cur_dtype + 0x4e8))();
  }
  uVar2 = (-(uint)((uVar1 & 0x800) != 0) & 0x10000) - 1;
  addr_00 = addr & uVar2;
  iVar3 = memmap_find(space,addr_00);
  space = 0;
  uVar1 = *(uint *)(*(int *)(cur_dtype + 0x20) + 8 + iVar3 * 0x2c);
  if (0 < *(int *)(cur_dtype + 0x1c)) {
    addr = 0;
    iVar3 = cur_dtype;
    do {
      iVar4 = *(int *)(iVar3 + 0x20) + iVar6;
      if (((((*(uint *)(iVar4 + 8) & uVar1) == uVar1) && ((char)*(uint *)(iVar4 + 8) == (char)uVar1)
           ) && ((*(uint *)(iVar4 + 0xc) & uVar2) <= addr_00)) &&
         (addr_00 <= (*(uint *)(iVar4 + 0x10) & uVar2))) {
        iVar3 = *(int *)(cur_sim + 4) + addr;
        if (is_write == 0) {
          piVar5 = (int *)(iVar3 + 0x14);
        }
        else {
          piVar5 = (int *)(iVar3 + 0xa0);
        }
        iVar3 = piVar5[1];
        *piVar5 = *piVar5 + 1;
        piVar5[2] = piVar5[2] + 1;
        piVar5[1] = iVar3 + 1;
        if (0xf < iVar3 + 1) {
          piVar5[1] = 0;
        }
        piVar5[piVar5[1] + 3] = addr_00;
        piVar5[piVar5[1] + 0x13] = value;
        iVar3 = cur_dtype;
      }
      space = space + 1;
      iVar6 = iVar6 + 0x2c;
      addr = addr + 300;
    } while ((int)space < *(int *)(iVar3 + 0x1c));
  }
  return;
}


/* ==== mem_trace_fetch @ 00457de0 ==== */

void __cdecl mem_trace_fetch(ulong addr)

{
  mem_trace_access(0x13,addr,0,0);
  return;
}


/* ==== dsp_alloc @ 00457e00 ==== */

void __cdecl dsp_alloc(ulong size,int zero)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *extraout_EAX;
  int iVar3;
  undefined4 *extraout_EAX_00;
  uint uVar4;
  undefined4 *puVar5;
  
  if (gui_mode != 0) {
    ret_false(size,zero);
    return;
  }
  malloc(size);
  puVar5 = extraout_EAX;
  while( true ) {
    if (puVar5 != (undefined4 *)0x0) {
      if (zero != 0) {
        for (uVar4 = size >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar5 = 0;
          puVar5 = puVar5 + 1;
        }
        for (uVar4 = size & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined1 *)puVar5 = 0;
          puVar5 = (undefined4 *)((int)puVar5 + 1);
        }
      }
      return;
    }
    iVar3 = mdisk_spill();
    uVar2 = cur_dev;
    uVar1 = cur_sim;
    if (iVar3 == 0) break;
    malloc(size);
    puVar5 = extraout_EAX_00;
  }
  cur_sim = *(undefined4 *)(dev_state_tab + cur_dev_index * 4);
  cur_dev = *(undefined4 *)(dev_tab + cur_dev_index * 4);
  out_text(s_Insufficient_memory__dsp_alloc_004d287c,1);
  cur_sim = uVar1;
  cur_dev = uVar2;
  return;
}


/* ==== dsp_free @ 00457ed0 ==== */

void __cdecl dsp_free(void *p)

{
  if (gui_mode != 0) {
    dsp_free_ext(p);
    return;
  }
  free(p);
  return;
}


/* ==== dsp_realloc @ 00457f00 ==== */

void __cdecl dsp_realloc(void *p,ulong size)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int extraout_EAX;
  int iVar3;
  int extraout_EAX_00;
  
  if (gui_mode != 0) {
    ret_false(p,size);
    return;
  }
  realloc(p,size);
  if (extraout_EAX == 0) {
    while( true ) {
      iVar3 = mdisk_spill();
      uVar2 = cur_dev;
      uVar1 = cur_sim;
      if (iVar3 == 0) break;
      realloc(p,size);
      if (extraout_EAX_00 != 0) {
        return;
      }
    }
    cur_sim = *(undefined4 *)(dev_state_tab + cur_dev_index * 4);
    cur_dev = *(undefined4 *)(dev_tab + cur_dev_index * 4);
    out_text(s_Insufficient_memory__dsp_realloc_004d289c,1);
    cur_sim = uVar1;
    cur_dev = uVar2;
  }
  return;
}


/* ==== mdisk_free_all @ 00457fb0 ==== */

void __cdecl mdisk_free_all(int dev)

{
  int *piVar1;
  int *piVar2;
  uint *puVar3;
  int *piVar4;
  int *p;
  int local_4;
  
  cur_dev = *(int **)(dev_tab + dev * 4);
  cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
  piVar4 = (int *)cur_dev[3];
  if ((piVar4 != (int *)0x0) && (local_4 = *(int *)(cur_dtype + 0x1c), 0 < local_4)) {
    puVar3 = (uint *)(*(int *)(cur_dtype + 0x20) + 0x18);
    do {
      if ((*puVar3 & 0x1000000) != 0) {
        piVar1 = (int *)*piVar4;
        p = piVar1;
        if (piVar1 != (int *)0x0) {
          do {
            piVar2 = (int *)*p;
            if (p[3] == 4) {
              dsp_free((void *)p[4]);
            }
            dsp_free(p);
            p = piVar2;
          } while (piVar2 != piVar1);
        }
        piVar4[1] = 0;
        *piVar4 = 0;
      }
      puVar3 = puVar3 + 0xb;
      piVar4 = piVar4 + 4;
      local_4 = local_4 + -1;
    } while (local_4 != 0);
  }
  return;
}


