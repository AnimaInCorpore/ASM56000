/* ==== display_all @ 0043c2f0 ==== */

/* WARNING: Type propagation algorithm not settling */

void __cdecl display_all(int with_watch)

{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined4 va0;
  int *piVar4;
  ulong uVar5;
  uint *puVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  ulong uVar19;
  ulong addr;
  int iVar20;
  int iVar21;
  undefined4 *puVar22;
  char *pcVar23;
  char *pcVar24;
  bool bVar25;
  uint local_374;
  int local_370;
  int local_36c;
  uint local_368;
  int local_364;
  int local_360;
  uint local_35c;
  int local_34c;
  char local_334 [20];
  char local_320 [32];
  char local_300;
  undefined4 local_2ff [63];
  char local_200 [256];
  char local_100 [256];
  
  if (*(int *)(cur_sim + 0x4400) == 0) {
    screen_hold();
  }
  local_360 = 0;
  local_36c = 0;
  iVar3 = *(int *)(cur_dtype + 0x14);
  iVar21 = cur_dtype;
  if (0 < iVar3) {
    local_368 = 0;
    do {
      iVar9 = *(int *)(iVar21 + 0x18) + local_368;
      puVar6 = *(uint **)(cur_itype[2] + local_36c * 4);
      iVar8 = *(int *)(iVar9 + 0x2c);
      cVar2 = **(char **)(iVar9 + 0x30);
      uVar16 = *(uint *)(iVar8 + 0x28);
      uVar15 = *puVar6;
      uVar18 = puVar6[1];
      iVar8 = *(int *)(iVar8 + 0x2c);
      iVar9 = *(int *)(*(int *)(cur_sim + 8) + 4 + local_36c * 8);
      local_374 = 0;
      if (uVar15 != 0) {
        do {
          local_200[0] = '\0';
          bVar25 = false;
          puVar6 = (uint *)(uVar18 + local_374 * 0xc);
          uVar13 = *puVar6;
          while (-2 < (int)uVar13) {
            if (((int)uVar13 < 0) || (uVar16 <= uVar13)) {
              uVar14 = 0;
            }
            else {
              uVar14 = *(uint *)(iVar9 + uVar13 * 4);
            }
            uVar17 = puVar6[1];
            if ((uVar14 & 0x800) == 0) {
              pcVar7 = PTR_s__004c5d44 + (0x32 - uVar17);
            }
            else {
              if ((uVar14 & 0x4000) == 0) {
                if ((uVar14 & 0x1000) == 0) {
                  iVar21 = (-(uint)((uVar14 & 0x8000) != 0) & 2) + 2;
                }
                else {
                  iVar21 = 1;
                }
              }
              else {
                iVar21 = 3;
              }
              bVar25 = true;
              pcVar7 = *(char **)(iVar8 + uVar13 * 0x1c);
              uVar10 = 0xffffffff;
              pcVar24 = pcVar7;
              do {
                if (uVar10 == 0) break;
                uVar10 = uVar10 - 1;
                cVar1 = *pcVar24;
                pcVar24 = pcVar24 + 1;
              } while (cVar1 != '\0');
              uVar11 = ~uVar10 - 1;
              uVar12 = uVar11;
              if (cVar2 != '\0') {
                uVar12 = ~uVar10;
              }
              uVar10 = 0;
              if (uVar12 < puVar6[2]) {
                uVar10 = puVar6[2] - uVar12;
                uVar12 = uVar10 >> 2;
                pcVar24 = &local_300;
                while (uVar12 != 0) {
                  uVar12 = uVar12 - 1;
                  builtin_strncpy(pcVar24,"    ",4);
                  pcVar24 = pcVar24 + 4;
                }
                for (uVar12 = uVar10 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
                  *pcVar24 = ' ';
                  pcVar24 = pcVar24 + 1;
                }
              }
              if (uVar11 != 0) {
                pcVar24 = &local_300 + uVar10;
                for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                  *(undefined4 *)pcVar24 = *(undefined4 *)pcVar7;
                  pcVar7 = pcVar7 + 4;
                  pcVar24 = pcVar24 + 4;
                }
                uVar10 = uVar10 + uVar11;
                for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
                  *pcVar24 = *pcVar7;
                  pcVar7 = pcVar7 + 1;
                  pcVar24 = pcVar24 + 1;
                }
              }
              if (cVar2 != '\0') {
                (&local_300)[uVar10] = cVar2;
                uVar10 = uVar10 + 1;
              }
              (&local_300)[uVar10] = '=';
              iVar20 = uVar10 + 1;
              iVar21 = fmt_register(local_36c,uVar13,iVar21,local_100);
              if (iVar21 == 0) {
                return;
              }
              uVar13 = 0xffffffff;
              pcVar7 = local_100;
              do {
                if (uVar13 == 0) break;
                uVar13 = uVar13 - 1;
                cVar1 = *pcVar7;
                pcVar7 = pcVar7 + 1;
              } while (cVar1 != '\0');
              uVar13 = ~uVar13 - 1;
              if (iVar20 + uVar13 < uVar17) {
                uVar17 = uVar17 - (iVar20 + uVar13);
                puVar22 = (undefined4 *)((int)local_2ff + uVar10);
                for (uVar12 = uVar17 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                  *puVar22 = 0x20202020;
                  puVar22 = puVar22 + 1;
                }
                iVar20 = iVar20 + uVar17;
                for (uVar17 = uVar17 & 3; uVar17 != 0; uVar17 = uVar17 - 1) {
                  *(undefined1 *)puVar22 = 0x20;
                  puVar22 = (undefined4 *)((int)puVar22 + 1);
                }
              }
              if ((uVar14 & 0x80000) != 0) {
                (&local_300)[iVar20] = '{';
                iVar20 = iVar20 + 1;
              }
              if (uVar13 != 0) {
                pcVar7 = local_100;
                pcVar24 = &local_300 + iVar20;
                for (uVar17 = uVar13 >> 2; uVar17 != 0; uVar17 = uVar17 - 1) {
                  *(undefined4 *)pcVar24 = *(undefined4 *)pcVar7;
                  pcVar7 = pcVar7 + 4;
                  pcVar24 = pcVar24 + 4;
                }
                iVar20 = iVar20 + uVar13;
                for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
                  *pcVar24 = *pcVar7;
                  pcVar7 = pcVar7 + 1;
                  pcVar24 = pcVar24 + 1;
                }
              }
              if ((uVar14 & 0x80000) != 0) {
                (&local_300)[iVar20] = '}';
                iVar20 = iVar20 + 1;
              }
              (&local_300)[iVar20] = '\0';
              pcVar7 = &local_300;
            }
            uVar13 = 0xffffffff;
            do {
              pcVar24 = pcVar7;
              if (uVar13 == 0) break;
              uVar13 = uVar13 - 1;
              pcVar24 = pcVar7 + 1;
              cVar1 = *pcVar7;
              pcVar7 = pcVar24;
            } while (cVar1 != '\0');
            uVar13 = ~uVar13;
            iVar21 = -1;
            pcVar7 = local_200;
            do {
              pcVar23 = pcVar7;
              if (iVar21 == 0) break;
              iVar21 = iVar21 + -1;
              pcVar23 = pcVar7 + 1;
              cVar1 = *pcVar7;
              pcVar7 = pcVar23;
            } while (cVar1 != '\0');
            pcVar7 = pcVar24 + -uVar13;
            pcVar24 = pcVar23 + -1;
            for (uVar14 = uVar13 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
              *(undefined4 *)pcVar24 = *(undefined4 *)pcVar7;
              pcVar7 = pcVar7 + 4;
              pcVar24 = pcVar24 + 4;
            }
            puVar6 = puVar6 + 3;
            for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
              *pcVar24 = *pcVar7;
              pcVar7 = pcVar7 + 1;
              pcVar24 = pcVar24 + 1;
            }
            local_374 = local_374 + 1;
            uVar13 = *puVar6;
          }
          if ((bVar25) && (iVar21 = rtrim_line(local_200), iVar21 != 0)) {
            out_text(local_200,1);
            local_360 = local_360 + 1;
            if ((text_rows <= local_360) && (local_360 = 0, *(int *)(cur_sim + 0x4400) == 0)) {
              screen_flush();
              screen_hold();
            }
          }
          local_374 = local_374 + 1;
          iVar21 = cur_dtype;
        } while (local_374 < uVar15);
      }
      local_36c = local_36c + 1;
      local_368 = local_368 + 0x48;
    } while (local_36c < iVar3);
  }
  iVar3 = *(int *)(iVar21 + 0x1c);
  local_374 = 0;
  if (0 < iVar3) {
    local_370 = 0;
    local_364 = 0;
    do {
      puVar22 = (undefined4 *)(*(int *)(cur_dtype + 0x20) + local_364);
      va0 = *puVar22;
      iVar21 = puVar22[1];
      uVar16 = *(uint *)(*cur_itype + iVar21 * 4);
      if (*(int *)(cur_sim + 0x3c34) == 0) {
        local_368 = (((int)uVar16 < 0x11) - 1 & 0xfffffffe) + 3;
      }
      else {
        local_368 = 0;
      }
      bVar25 = true;
      for (piVar4 = *(int **)(*(int *)(cur_sim + 4) + 4 + local_370); piVar4 != (int *)0x0;
          piVar4 = (int *)piVar4[3]) {
        iVar8 = *piVar4;
        if (iVar8 != 0) {
          uVar5 = piVar4[2];
          addr = piVar4[1];
          do {
            fmt_addr(addr,local_334);
            if (bVar25) {
              sprintf(local_200,s__s___s__004c6378,va0,local_334);
            }
            local_35c = 1;
LAB_0043c759:
            iVar9 = mem_addr_check(local_374,addr);
            if (iVar9 == 0) {
              iVar9 = 3;
            }
            local_34c = fmt_read_word(iVar21,addr,iVar9,local_320,(char *)0x0);
            if (local_34c == 0) {
              local_34c = 1;
            }
            uVar15 = 0xffffffff;
            uVar18 = 0;
            pcVar7 = local_320;
            do {
              if (uVar15 == 0) break;
              uVar15 = uVar15 - 1;
              cVar2 = *pcVar7;
              pcVar7 = pcVar7 + 1;
            } while (cVar2 != '\0');
            uVar15 = ~uVar15 - 1;
            if (uVar15 < uVar16) {
              uVar18 = uVar16 - uVar15;
              uVar13 = uVar18 >> 2;
              pcVar7 = &local_300;
              while (uVar13 != 0) {
                uVar13 = uVar13 - 1;
                builtin_strncpy(pcVar7,"    ",4);
                pcVar7 = pcVar7 + 4;
              }
              for (uVar13 = uVar18 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
                *pcVar7 = ' ';
                pcVar7 = pcVar7 + 1;
              }
            }
            if (iVar8 == 2) {
              (&local_300)[uVar18] = '{';
              uVar18 = uVar18 + 1;
            }
            if (uVar15 != 0) {
              pcVar7 = local_320;
              pcVar24 = &local_300 + uVar18;
              for (uVar13 = uVar15 >> 2; uVar13 != 0; uVar13 = uVar13 - 1) {
                *(undefined4 *)pcVar24 = *(undefined4 *)pcVar7;
                pcVar7 = pcVar7 + 4;
                pcVar24 = pcVar24 + 4;
              }
              uVar18 = uVar18 + uVar15;
              for (uVar15 = uVar15 & 3; uVar15 != 0; uVar15 = uVar15 - 1) {
                *pcVar24 = *pcVar7;
                pcVar7 = pcVar7 + 1;
                pcVar24 = pcVar24 + 1;
              }
            }
            if (iVar8 == 2) {
              (&local_300)[uVar18] = '}';
              uVar18 = uVar18 + 1;
            }
            uVar15 = 0xffffffff;
            (&local_300)[uVar18] = '\0';
            pcVar7 = &local_300;
            do {
              pcVar24 = pcVar7;
              if (uVar15 == 0) break;
              uVar15 = uVar15 - 1;
              pcVar24 = pcVar7 + 1;
              cVar2 = *pcVar7;
              pcVar7 = pcVar24;
            } while (cVar2 != '\0');
            uVar15 = ~uVar15;
            iVar9 = -1;
            pcVar7 = local_200;
            do {
              pcVar23 = pcVar7;
              if (iVar9 == 0) break;
              iVar9 = iVar9 + -1;
              pcVar23 = pcVar7 + 1;
              cVar2 = *pcVar7;
              pcVar7 = pcVar23;
            } while (cVar2 != '\0');
            pcVar7 = pcVar24 + -uVar15;
            pcVar24 = pcVar23 + -1;
            for (uVar18 = uVar15 >> 2; uVar18 != 0; uVar18 = uVar18 - 1) {
              *(undefined4 *)pcVar24 = *(undefined4 *)pcVar7;
              pcVar7 = pcVar7 + 4;
              pcVar24 = pcVar24 + 4;
            }
            for (uVar15 = uVar15 & 3; uVar15 != 0; uVar15 = uVar15 - 1) {
              *pcVar24 = *pcVar7;
              pcVar7 = pcVar7 + 1;
              pcVar24 = pcVar24 + 1;
            }
            if (*(int *)(cur_sim + 0x3c34) != 0) {
              pcVar7 = dbg_format_addr(iVar21,addr);
              uVar15 = 0xffffffff;
              do {
                pcVar24 = pcVar7;
                if (uVar15 == 0) break;
                uVar15 = uVar15 - 1;
                pcVar24 = pcVar7 + 1;
                cVar2 = *pcVar7;
                pcVar7 = pcVar24;
              } while (cVar2 != '\0');
              uVar15 = ~uVar15;
              iVar9 = -1;
              pcVar7 = local_200;
              do {
                pcVar23 = pcVar7;
                if (iVar9 == 0) break;
                iVar9 = iVar9 + -1;
                pcVar23 = pcVar7 + 1;
                cVar2 = *pcVar7;
                pcVar7 = pcVar23;
              } while (cVar2 != '\0');
              pcVar7 = pcVar24 + -uVar15;
              pcVar24 = pcVar23 + -1;
              for (uVar18 = uVar15 >> 2; uVar18 != 0; uVar18 = uVar18 - 1) {
                *(undefined4 *)pcVar24 = *(undefined4 *)pcVar7;
                pcVar7 = pcVar7 + 4;
                pcVar24 = pcVar24 + 4;
              }
              for (uVar15 = uVar15 & 3; uVar15 != 0; uVar15 = uVar15 - 1) {
                *pcVar24 = *pcVar7;
                pcVar7 = pcVar7 + 1;
                pcVar24 = pcVar24 + 1;
              }
            }
            uVar19 = addr;
            if (local_34c < 2) {
              bVar25 = (addr + 1 & local_368) == 0;
            }
            else {
              bVar25 = (local_368 & local_35c) == 0;
              iVar9 = 1;
              if (1 < local_34c) {
                do {
                  uVar19 = uVar5;
                  if (iVar9 + addr == uVar5) break;
                  iVar9 = iVar9 + 1;
                  uVar19 = addr;
                } while (iVar9 < local_34c);
              }
            }
            if (uVar19 != uVar5) {
              if (bVar25) goto LAB_0043c916;
              addr = uVar19 + local_34c;
              local_35c = local_35c + 1;
              goto LAB_0043c759;
            }
            if ((!bVar25) &&
               ((uVar19 != uVar5 || (((int *)piVar4[3] != (int *)0x0 && (*(int *)piVar4[3] != 0)))))
               ) {
              bVar25 = false;
              goto LAB_0043c96e;
            }
LAB_0043c916:
            bVar25 = true;
            out_text(local_200,1);
            local_360 = local_360 + 1;
            if (text_rows <= local_360) {
              local_360 = 0;
              if (*(int *)(cur_sim + 0x4400) == 0) {
                screen_flush();
                screen_hold();
              }
              iVar9 = abort_check();
              if (iVar9 != 0) break;
            }
LAB_0043c96e:
            if (uVar19 == uVar5) break;
            addr = uVar19 + local_34c;
          } while( true );
        }
        iVar8 = abort_check();
        if (iVar8 != 0) break;
      }
      iVar21 = abort_check();
      if (iVar21 != 0) break;
      local_374 = local_374 + 1;
      local_364 = local_364 + 0x2c;
      local_370 = local_370 + 300;
    } while ((int)local_374 < iVar3);
  }
  if (with_watch != 0) {
    watch_update_all();
  }
  disasm_line(0,*(ulong *)(cur_dev + 0x1c),local_200,0);
  out_text(local_200,1);
  uVar16 = 0xffffffff;
  pcVar7 = local_200;
  do {
    if (uVar16 == 0) break;
    uVar16 = uVar16 - 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar2 != '\0');
  if (screen_cols - 1U < ~uVar16 - 1) {
    out_text(local_200 + screen_cols,1);
  }
  return;
}


/* ==== rtrim_line @ 0043ca50 ==== */

int __cdecl rtrim_line(char *s)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  
  uVar2 = 0xffffffff;
  pcVar4 = s;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  for (iVar3 = ~uVar2 - 2; (0 < iVar3 && (s[iVar3] == ' ')); iVar3 = iVar3 + -1) {
    s[iVar3] = '\0';
  }
  return (uint)(0 < iVar3);
}


/* ==== reg_next @ 0043ca80 ==== */

void __cdecl reg_next(int *reg,int *bank)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *reg + 1;
  iVar1 = *bank;
  if (iVar2 == *(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + iVar1 * 0x48) + 0x28)) {
    iVar2 = 0;
    do {
      iVar1 = iVar1 + 1;
      if (iVar1 == *(int *)(cur_dtype + 0x14)) {
        iVar1 = 0;
      }
    } while (*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + iVar1 * 0x48) + 0x28) == 0);
  }
  *reg = iVar2;
  *bank = iVar1;
  return;
}


/* ==== reg_prev @ 0043cad0 ==== */

void __cdecl reg_prev(int *reg,int *bank)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *bank;
  iVar2 = *reg;
  if (iVar2 == 0) {
    do {
      if (iVar1 == 0) {
        iVar1 = *(int *)(cur_dtype + 0x14);
      }
      iVar1 = iVar1 + -1;
      iVar2 = *(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + iVar1 * 0x48) + 0x28);
    } while (iVar2 == 0);
  }
  *reg = iVar2 + -1;
  *bank = iVar1;
  return;
}


/* ==== list_next_id @ 0043cb10 ==== */

int __cdecl list_next_id(void *head)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  for (puVar1 = *(uint **)((int)head + 0x120);
      (puVar1 != (uint *)0x0 && (uVar2 = *puVar1, uVar2 <= uVar3 + 1));
      puVar1 = (uint *)puVar1[0x48]) {
    uVar3 = uVar2;
  }
  return uVar3 + 1;
}


/* ==== list_find_id @ 0043cb40 ==== */

int __cdecl list_find_id(void *head,int id)

{
  int *piVar1;
  
  piVar1 = *(int **)((int)head + 0x120);
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return 0;
    }
    if (*piVar1 == id) break;
    piVar1 = (int *)piVar1[0x48];
  }
  return (int)piVar1;
}


/* ==== list_insert_sorted @ 0043cb70 ==== */

void __cdecl list_insert_sorted(void *head,void *node)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar3 = (uint *)0x0;
  if (*(uint **)((int)head + 0x120) != (uint *)0x0) {
    puVar1 = *(uint **)((int)head + 0x120);
    puVar2 = (uint *)0x0;
    do {
      puVar3 = puVar1;
      if (*(uint *)node < *puVar3) {
        *(uint **)((int)node + 0x120) = puVar3;
        puVar3 = puVar2;
        break;
      }
      puVar1 = (uint *)puVar3[0x48];
      puVar2 = puVar3;
    } while ((uint *)puVar3[0x48] != (uint *)0x0);
  }
  if (puVar3 == (uint *)0x0) {
    puVar3 = head;
  }
  puVar3[0x48] = (uint)node;
  return;
}


/* ==== cmd_watch_h1_sub_43cbb0 @ 0043cbb0 ==== */

void cmd_watch_h1_sub_43cbb0(int *param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int *p;
  
  piVar2 = (int *)0x0;
  p = (int *)param_1[0x48];
  if (p != (int *)0x0) {
    while (*p != param_2) {
      piVar1 = p + 0x48;
      piVar2 = p;
      p = (int *)*piVar1;
      if ((int *)*piVar1 == (int *)0x0) {
        return;
      }
    }
    if (piVar2 == (int *)0x0) {
      piVar2 = param_1;
    }
    piVar2[0x48] = p[0x48];
    if ((void *)p[0x45] != (void *)0x0) {
      cdb_free_expr((void *)p[0x45]);
    }
    dsp_free(p);
  }
  return;
}


/* ==== cmd_watch_h1_sub_43cc10 @ 0043cc10 ==== */

void cmd_watch_h1_sub_43cc10(int param_1)

{
  void *pvVar1;
  void *p;
  
  p = *(void **)(param_1 + 0x120);
  while (p != (void *)0x0) {
    pvVar1 = *(void **)((int)p + 0x120);
    if (*(void **)((int)p + 0x114) != (void *)0x0) {
      cdb_free_expr(*(void **)((int)p + 0x114));
    }
    dsp_free(p);
    p = pvVar1;
  }
  *(undefined4 *)(param_1 + 0x120) = 0;
  return;
}


/* ==== str_nicmp_ascii @ 0043cc60 ==== */

int __cdecl str_nicmp_ascii(char *a,char *b,int n)

{
  byte bVar1;
  int iVar2;
  
  if (n != 0) {
    while( true ) {
      iVar2 = tolower((int)*a);
      bVar1 = (byte)iVar2;
      iVar2 = tolower((int)*b);
      if (bVar1 != (byte)iVar2) {
        return (-(uint)(bVar1 < (byte)iVar2) & 0xfffffffe) + 1;
      }
      if (bVar1 == 0) break;
      n = n + -1;
      a = a + 1;
      b = b + 1;
      if (n == 0) {
        return 0;
      }
    }
  }
  return 0;
}


/* ==== str_icmp_ascii @ 0043ccc0 ==== */

int __cdecl str_icmp_ascii(char *a,char *b)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  
  do {
    cVar1 = *a;
    a = a + 1;
    iVar3 = tolower((int)cVar1);
    bVar2 = (byte)iVar3;
    cVar1 = *b;
    b = b + 1;
    iVar3 = tolower((int)cVar1);
    if (bVar2 != (byte)iVar3) {
      return (-(uint)(bVar2 < (byte)iVar3) & 0xfffffffe) + 1;
    }
  } while (bVar2 != 0);
  return 0;
}


/* ==== console_open @ 0043cd00 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void console_open(void)

{
  int cols;
  int rows;
  uint local_a0;
  CONSOLE_CURSOR_INFO local_9c;
  _OSVERSIONINFOA local_94;
  
  if (no_console == 0) {
    local_94.dwOSVersionInfoSize = 0x94;
    GetVersionExA(&local_94);
    if (local_94.dwPlatformId == 0) {
      exit(0);
    }
    SetConsoleTitleA(s_Motorola_DSP_004c6380);
    _DAT_004e904c = GetStdHandle(0xfffffff6);
    console_in_handle = _DAT_004e904c;
    GetConsoleMode(_DAT_004e904c,&DAT_004dc3c0);
    console_orig_handle = GetStdHandle(0xfffffff5);
    DAT_004e9048 = console_orig_handle;
    cols = console_rows(console_orig_handle);
    rows = console_cols(DAT_004e9048);
    GetConsoleMode(DAT_004e9048,&DAT_004e9040);
    local_9c.dwSize = 100;
    local_9c.bVisible = 1;
    SetConsoleCursorInfo(DAT_004e9048,&local_9c);
    console_out_handle =
         CreateConsoleScreenBuffer(0xc0000000,3,(SECURITY_ATTRIBUTES *)0x0,1,(LPVOID)0x0);
    console_get_attr((long)console_out_handle);
    GetConsoleMode(console_out_handle,&local_a0);
    SetConsoleMode(console_out_handle,local_a0 & 0xfffffffc);
    SetConsoleActiveScreenBuffer(console_out_handle);
    console_set_size(console_out_handle,cols,rows);
    GetConsoleMode(console_in_handle,&local_a0);
    SetConsoleMode(console_in_handle,local_a0 & 0xffffffe9 | 9);
    SetConsoleCtrlHandler(hid_43d080,1);
    signal(8,cmd_unlock_h0);
    screen_hold_cnt = screen_hold_cnt + 1;
    screen_clear();
  }
  return;
}


/* ==== cmd_unlock_h0 @ 0043ce80 ==== */

void cmd_unlock_h0(void)

{
  return;
}


/* ==== console_rows @ 0043ce90 ==== */

int __cdecl console_rows(void *h)

{
  _CONSOLE_SCREEN_BUFFER_INFO local_18;
  
  GetConsoleScreenBufferInfo(h,&local_18);
  return (local_18.srWindow._4_4_ - local_18.srWindow._0_4_) + 1;
}


/* ==== console_cols @ 0043cec0 ==== */

int __cdecl console_cols(void *h)

{
  _CONSOLE_SCREEN_BUFFER_INFO local_18;
  
  GetConsoleScreenBufferInfo(h,&local_18);
  return (local_18._16_4_ - local_18.srWindow._2_4_) + 1;
}


/* ==== console_get_attr @ 0043cef0 ==== */

void __cdecl console_get_attr(long h)

{
  long hConsoleOutput;
  _CONSOLE_SCREEN_BUFFER_INFO local_18;
  
  hConsoleOutput = h;
  GetConsoleScreenBufferInfo((HANDLE)h,&local_18);
  DAT_004e27c8 = CONCAT22(DAT_004e27c8._2_2_,local_18.wAttributes);
  h = (uint)(ushort)text_rows << 0x10;
  DAT_004e9044 = local_18.wAttributes;
  ReadConsoleOutputAttribute((HANDLE)hConsoleOutput,&DAT_004e9044,1,(COORD)h,(LPDWORD)&h);
  if (DAT_004e9044 == (ushort)DAT_004e27c8) {
    DAT_004e9044 = (ushort)DAT_004e27c8 ^ 0x77;
  }
  return;
}


/* ==== console_set_size @ 0043cf70 ==== */

void __cdecl console_set_size(void *h,int cols,int rows)

{
  COORD CVar1;
  short sVar2;
  uint uVar3;
  short sVar4;
  int iVar5;
  SMALL_RECT local_20;
  _CONSOLE_SCREEN_BUFFER_INFO local_18;
  
  sVar4 = (short)cols;
  if (0xfe < sVar4) {
    sVar4 = 0xff;
  }
  sVar2 = (short)rows;
  if (0x62 < sVar2) {
    sVar2 = 99;
  }
  GetConsoleScreenBufferInfo(h,&local_18);
  CVar1 = GetLargestConsoleWindowSize(h);
  cols._0_2_ = CVar1.X;
  if (sVar4 < (short)cols) {
    cols._0_2_ = sVar4;
  }
  local_20.Right = (short)cols + -1;
  cols._2_2_ = CVar1.Y;
  local_20.Bottom = cols._2_2_;
  if (sVar2 < cols._2_2_) {
    local_20.Bottom = sVar2;
  }
  cols = CONCAT22(sVar2,sVar4);
  iVar5 = (int)sVar2;
  local_20.Bottom = local_20.Bottom + -1;
  uVar3 = iVar5 * sVar4;
  local_20.Top = 0;
  local_20.Left = 0;
  if (uVar3 <= (uint)((int)local_18.dwSize.X * (int)local_18.dwSize.Y) &&
      (int)local_18.dwSize.X * (int)local_18.dwSize.Y - uVar3 != 0) {
    SetConsoleWindowInfo(h,1,&local_20);
    SetConsoleScreenBufferSize(h,(COORD)cols);
  }
  if ((uint)((int)local_18.dwSize.X * (int)local_18.dwSize.Y) < uVar3) {
    SetConsoleScreenBufferSize(h,(COORD)cols);
    SetConsoleWindowInfo(h,1,&local_20);
  }
  screen_rows = iVar5;
  text_rows = iVar5 + -3;
  screen_cols = (int)sVar4;
  return;
}


/* ==== hid_43d080 @ 0043d080 ==== */

undefined4 hid_43d080(int param_1)

{
  if ((param_1 != 0) && (param_1 != 1)) {
    return 0;
  }
  abort_flag = 1;
  return 1;
}


/* ==== screen_clear @ 0043d0b0 ==== */

void screen_clear(void)

{
  int iVar1;
  undefined4 *puVar2;
  DWORD local_1c;
  _CONSOLE_SCREEN_BUFFER_INFO local_18;
  
  if (no_console == 0) {
    GetConsoleScreenBufferInfo(console_out_handle,&local_18);
    FillConsoleOutputCharacterA
              (console_out_handle,' ',(int)local_18.dwSize.X * (int)local_18.dwSize.Y,(COORD)0x0,
               &local_1c);
    GetConsoleScreenBufferInfo(console_out_handle,&local_18);
    FillConsoleOutputAttribute
              (console_out_handle,local_18.wAttributes,
               (int)local_18.dwSize.X * (int)local_18.dwSize.Y,(COORD)0x0,&local_1c);
    SetConsoleCursorPosition(console_out_handle,(COORD)0x0);
    puVar2 = &screen_attr_buf;
    for (iVar1 = 0x1900; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0x7070707;
      puVar2 = puVar2 + 1;
    }
    puVar2 = &screen_char_buf;
    for (iVar1 = 0x1919; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0x20202020;
      puVar2 = puVar2 + 1;
    }
    screen_top_row = 0;
  }
  screen_hold_cnt = 0;
  return;
}


/* ==== scrollback_end @ 0043d180 ==== */

void __cdecl scrollback_end(int dev)

{
  int iVar1;
  
  cur_sim = *(int *)(dev_state_tab + dev * 4);
  if (cur_sim != 0) {
    *(undefined4 *)(*(int *)(cur_sim + 0x3fbc) + 4) = text_rows;
    iVar1 = *(int *)(cur_sim + 0x4400);
    if (iVar1 == 0) {
      scrollback_move(scrollback_lines);
    }
    else if ((0 < iVar1) && (iVar1 < 3)) {
      win_update(0x7fff);
      return;
    }
  }
  return;
}


/* ==== log_echo @ 0043d1e0 ==== */

void __cdecl log_echo(char *line,int nocmdlog)

{
  out_line(line,nocmdlog,1);
  return;
}


/* ==== out_line @ 0043d200 ==== */

void __cdecl out_line(char *line,int nocmdlog,int plain)

{
  char cVar1;
  char cVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (cur_sim != 0) {
    piVar3 = *(int **)(cur_sim + 0x3fbc);
    iVar4 = *piVar3;
    *piVar3 = iVar4 + 1;
    if (iVar4 + 1 == scrollback_lines) {
      *piVar3 = 0;
    }
    piVar3[1] = piVar3[1] + 1;
    strncpy((char *)(*piVar3 * 0x100 + piVar3[2]),line,0xff);
    if (plain == 0) {
      iVar4 = *piVar3 * 0x100 + piVar3[2];
      iVar5 = 0;
      iVar6 = 0;
      do {
        cVar1 = *(char *)(iVar5 + iVar4);
        if ((cVar1 == '$') &&
           ((cVar2 = *(char *)(iVar5 + 1 + iVar4), cVar2 == '{' || (cVar2 == '}')))) {
          *(char *)(iVar6 + iVar4) = cVar2;
          iVar5 = iVar5 + 1;
        }
        else if (cVar1 == '{') {
          *(undefined1 *)(iVar6 + iVar4) = 0xf;
        }
        else if (cVar1 == '}') {
          *(undefined1 *)(iVar6 + iVar4) = 7;
        }
        else {
          if (cVar1 == '\0') {
            *(undefined1 *)(iVar6 + iVar4) = 0;
            break;
          }
          *(char *)(iVar6 + iVar4) = cVar1;
        }
        iVar5 = iVar5 + 1;
        iVar6 = iVar6 + 1;
      } while (iVar5 < 0x100);
    }
    if ((((*(int *)(cur_dev + 4) == cur_dev_index) && (*(int *)(cur_sim + 0x4400) == 0)) &&
        (scrollback_move(piVar3[1]), more_flag != 0)) &&
       (more_line_count = more_line_count + 1, text_rows <= more_line_count)) {
      more_line_count = 0;
      status_line2(s__More__Type_any_key_to_continue__004c6390);
      screen_flush();
      iVar4 = key_get();
      if (iVar4 == 3) {
        abort_flag = 1;
      }
      status_line2(&DAT_004c1640);
      screen_hold();
    }
    if ((nocmdlog == 0) && (cmdlog_fp != (void *)0x0)) {
      fprintf(cmdlog_fp,&DAT_004c5990,line);
      fflush(cmdlog_fp);
    }
    if (*(void **)(cur_sim + 0x48) != (void *)0x0) {
      fprintf(*(void **)(cur_sim + 0x48),&DAT_004c5990,line);
      fflush(*(void **)(cur_sim + 0x48));
    }
  }
  return;
}


/* ==== out_text @ 0043d3a0 ==== */

void __cdecl out_text(char *line,int nocmdlog)

{
  out_line(line,nocmdlog,0);
  return;
}


/* ==== scrollback_move @ 0043d3c0 ==== */

void __cdecl scrollback_move(int n)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (cur_sim != 0) {
    piVar1 = *(int **)(cur_sim + 0x3fbc);
    screen_hold_cnt = screen_hold_cnt + 1;
    iVar4 = piVar1[1];
    if (n < 0) {
      iVar5 = iVar4 + text_rows;
      iVar2 = scrollback_lines - iVar5;
      iVar3 = -n;
      if (-iVar2 != n && iVar2 <= -n) {
        iVar3 = iVar2;
      }
      if (text_rows <= iVar3) {
        iVar4 = iVar4 + (iVar3 - text_rows);
        iVar5 = iVar4 + text_rows;
        iVar3 = text_rows;
      }
      iVar5 = *piVar1 - iVar5;
      iVar2 = iVar4 + iVar3;
      if (0 < iVar3) {
        do {
          screen_rotate(-1);
          if (iVar5 < 0) {
            iVar5 = iVar5 + scrollback_lines;
          }
          screen_write(0,0,(char *)(iVar5 * 0x100 + piVar1[2]),1);
          iVar5 = iVar5 + -1;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
        piVar1[1] = iVar2;
        screen_release();
        return;
      }
    }
    else {
      if (iVar4 < n) {
        n = iVar4;
      }
      if (text_rows <= n) {
        iVar4 = iVar4 + (text_rows - n);
        n = text_rows;
      }
      iVar2 = iVar4 - n;
      iVar4 = (*piVar1 - iVar4) + 1 + scrollback_lines;
      if (0 < n) {
        do {
          screen_rotate(1);
          if (scrollback_lines <= iVar4) {
            iVar4 = iVar4 - scrollback_lines;
          }
          screen_write(text_rows + -1,0,(char *)(iVar4 * 0x100 + piVar1[2]),1);
          iVar4 = iVar4 + 1;
          n = n + -1;
        } while (n != 0);
      }
    }
    piVar1[1] = iVar2;
    screen_release();
  }
  return;
}


/* ==== screen_rotate @ 0043d4e0 ==== */

void __cdecl screen_rotate(int dir)

{
  if (dir < 1) {
    screen_top_row = screen_top_row + -1;
    if (screen_top_row < 0) {
      screen_top_row = text_rows + -1;
    }
  }
  else {
    screen_top_row = screen_top_row + 1;
    if (screen_top_row == text_rows) {
      screen_top_row = 0;
      return;
    }
  }
  return;
}


/* ==== cursor_set @ 0043d520 ==== */

void __cdecl cursor_set(int row,int col)

{
  COORD dwCursorPosition;
  
  if (screen_hold_cnt < 1) {
    screen_flush();
  }
  cursor_row = row;
  cursor_col = col;
  if (no_console == 0) {
    dwCursorPosition.Y = (SHORT)row;
    dwCursorPosition.X = (SHORT)col;
    SetConsoleCursorPosition(console_out_handle,dwCursorPosition);
  }
  return;
}


/* ==== screen_putc @ 0043d570 ==== */

void __thiscall screen_putc(void *this,int ch)

{
  undefined4 uStack_4;
  
  screen_hold_cnt = screen_hold_cnt + 1;
  uStack_4 = (uint)CONCAT12((undefined1)ch,(short)this);
  screen_puts_attr((char *)((int)&uStack_4 + 2),0);
  screen_release();
  return;
}


/* ==== screen_clear_eol @ 0043d5b0 ==== */

void screen_clear_eol(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  iVar1 = cursor_col;
  if (cursor_row < text_rows) {
    iVar3 = cursor_row + screen_top_row;
    if (text_rows <= iVar3) {
      iVar3 = iVar3 - text_rows;
    }
  }
  else {
    iVar3 = (cursor_row - text_rows) + 0x61;
  }
  uVar4 = (screen_cols - cursor_col) + 1;
  if ((no_console == 0) && (0 < (int)uVar4)) {
    puVar5 = (undefined4 *)((int)&screen_attr_buf + cursor_col + iVar3 * 0x100);
    for (uVar2 = uVar4 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar5 = 0x7070707;
      puVar5 = puVar5 + 1;
    }
    for (uVar2 = uVar4 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)puVar5 = 7;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
    puVar5 = (undefined4 *)((int)&screen_char_buf + iVar1 + iVar3 * 0x101);
    for (uVar2 = uVar4 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar5 = 0x20202020;
      puVar5 = puVar5 + 1;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar5 = 0x20;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
  }
  return;
}


/* ==== screen_puts_attr @ 0043d640 ==== */

void __cdecl screen_puts_attr(char *s,int mode)

{
  char cVar1;
  char cVar2;
  int iVar3;
  char cVar4;
  int iVar5;
  
  cVar4 = (-(mode != 2) & 0xf8U) + 0xf;
  if (cursor_row < text_rows) {
    iVar3 = cursor_row + screen_top_row;
    if (text_rows <= iVar3) {
      iVar3 = iVar3 - text_rows;
    }
  }
  else {
    iVar3 = (cursor_row - text_rows) + 0x61;
  }
  cVar2 = *s;
  iVar5 = cursor_col;
  do {
    if (cVar2 == '\0') {
      screen_clear_eol();
      if (screen_cols <= cursor_col) {
        cursor_col = screen_cols + -1;
      }
      return;
    }
    switch(cVar2) {
    case '\a':
      if (mode == 1) {
        cVar4 = '\a';
      }
      break;
    case '\t':
    case '\n':
      screen_clear_eol();
      iVar5 = cursor_col;
      break;
    case '\x0f':
      if (mode == 1) {
        cVar4 = '\x0f';
      }
      break;
    case '$':
      if (((mode == 3) && (cVar2 == '$')) && ((cVar1 = s[1], cVar1 == '}' || (cVar1 == '{')))) {
        s = s + 1;
        cVar2 = cVar1;
      }
    default:
switchD_0043d6a3_caseD_8:
      if (iVar5 < 0x100) {
        *(char *)((int)&screen_char_buf + iVar5 + iVar3 * 0x101) = cVar2;
        *(char *)((int)&screen_attr_buf + iVar5 + iVar3 * 0x100) = cVar4;
        cursor_col = iVar5 + 1;
        iVar5 = cursor_col;
      }
      break;
    case '{':
      if (mode != 3) goto switchD_0043d6a3_caseD_8;
      cVar4 = '\x0f';
      break;
    case '}':
      if (mode != 3) goto switchD_0043d6a3_caseD_8;
      cVar4 = '\a';
    }
    cVar2 = s[1];
    s = s + 1;
  } while( true );
}


/* ==== screen_write @ 0043d800 ==== */

void screen_write(int row,int col,char *s,int mode)

{
  screen_hold_cnt = screen_hold_cnt + 1;
  cursor_row = row;
  cursor_col = col;
  screen_puts_attr(s,mode);
  screen_release();
  return;
}


/* ==== key_get @ 0043d840 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int key_get(void)

{
  int iVar1;
  short sVar2;
  uint uVar3;
  int cols;
  int rows;
  int iVar4;
  DWORD local_18;
  _INPUT_RECORD local_14;
  
  if (DAT_004e9050 == 0) {
    DAT_004e9050 = 1;
    _DAT_004e8c44 = 0xc;
    _DAT_004e8c48 = 0x12;
    _DAT_004e8c4c = 3;
    _DAT_004e8c64 = 9;
    _DAT_004e8c70 = 0x1a;
    _DAT_004e8cdc = 0x12;
    _DAT_004e8cd4 = 0xc;
    _DAT_004e8cf4 = 0xf;
    _DAT_004e8cd8 = 0x14;
    _DAT_004e8ce0 = 0x16;
    _DAT_004e8cc4 = 0x15;
    _DAT_004e8cc8 = 0xe;
    _DAT_004e8cac = 0x1b;
    _DAT_004e8cc0 = 0x20;
    _DAT_004e8cf8 = 0xb;
    _DAT_004e8c60 = 8;
  }
  iVar4 = 0;
  iVar1 = no_console;
  do {
    if (iVar1 != 0) {
      return iVar4;
    }
    do {
      WaitForSingleObject(console_in_handle,0xffffffff);
      ReadConsoleInputA(console_in_handle,&local_14,1,&local_18);
      sVar2 = local_14.EventType;
      if ((sVar2 == 1) || (sVar2 == 4)) break;
    } while (sVar2 != 0x10);
    uVar3 = local_14._0_4_ & 0xffff;
    iVar1 = iVar4;
    if (uVar3 == 1) {
      if ((local_14.Event.KeyEvent.bKeyDown != 0) &&
         (((local_14.Event._6_4_ & 0xffff) == 0 ||
          (iVar4 = *(int *)(&vk_to_editkey + (local_14.Event._6_4_ & 0xffff) * 4), iVar1 = iVar4,
          iVar4 == 0)))) {
        iVar4 = (int)(char)local_14.Event.MouseEvent.dwControlKeyState._2_1_;
        iVar1 = iVar4;
      }
    }
    else if (uVar3 == 4) {
      cols = console_rows(console_out_handle);
      rows = console_cols(console_out_handle);
      console_set_size(console_out_handle,cols,rows);
    }
    else if (uVar3 == 0x10) {
      console_get_attr((long)console_out_handle);
      screen_flush();
    }
  } while( true );
}


/* ==== console_beep @ 0043d9e0 ==== */

void console_beep(void)

{
  if (no_console == 0) {
    _getch();
    return;
  }
  return;
}


/* ==== screen_flush @ 0043d9f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void screen_flush(void)

{
  COORD dwBufferSize;
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  _SMALL_RECT local_8;
  
  if ((no_console == 0) && ((cur_dev == 0 || (*(int *)(cur_dev + 4) == cur_dev_index)))) {
    iVar5 = 0;
    DAT_004e27cc = &screen_charinfo_buf;
    iVar4 = text_rows;
    iVar6 = screen_cols;
    iVar7 = screen_rows;
    if (0 < screen_rows) {
      do {
        if (iVar5 < iVar4) {
          iVar2 = iVar5 + screen_top_row;
          if (iVar4 <= iVar2) {
            iVar2 = iVar2 - iVar4;
          }
        }
        else {
          iVar2 = (iVar5 - iVar4) + 0x61;
        }
        iVar3 = 0;
        if (0 < iVar6) {
          do {
            *DAT_004e27cc = *(undefined1 *)((int)&screen_char_buf + iVar3 + iVar2 * 0x101);
            uVar1 = (undefined2)_DAT_004e9044;
            if (*(char *)((int)&screen_attr_buf + iVar3 + iVar2 * 0x100) != '\x0f') {
              uVar1 = (undefined2)DAT_004e27c8;
            }
            *(undefined2 *)(DAT_004e27cc + 2) = uVar1;
            DAT_004e27cc = DAT_004e27cc + 4;
            iVar3 = iVar3 + 1;
            iVar4 = text_rows;
            iVar6 = screen_cols;
            iVar7 = screen_rows;
          } while (iVar3 < screen_cols);
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < iVar7);
    }
    dwBufferSize.Y = (short)iVar7;
    dwBufferSize.X = (short)iVar6;
    local_8.Right = (short)iVar6 + -1;
    local_8.Bottom = (short)iVar7 + -1;
    DAT_004e27cc = &screen_charinfo_buf;
    local_8.Left = 0;
    local_8.Top = 0;
    WriteConsoleOutputA(console_out_handle,(CHAR_INFO *)&screen_charinfo_buf,dwBufferSize,(COORD)0x0
                        ,&local_8);
  }
  screen_hold_cnt = 0;
  return;
}


/* ==== screen_hold @ 0043db40 ==== */

void screen_hold(void)

{
  screen_hold_cnt = screen_hold_cnt + 1;
  return;
}


/* ==== screen_release @ 0043db50 ==== */

void screen_release(void)

{
  if (screen_hold_cnt < 2) {
    screen_flush();
    return;
  }
  screen_hold_cnt = screen_hold_cnt + -1;
  return;
}


/* ==== console_close @ 0043db70 ==== */

void console_close(void)

{
  screen_clear();
  if (no_console == 0) {
    SetConsoleActiveScreenBuffer(console_orig_handle);
    SetConsoleMode(console_in_handle,DAT_004dc3c0);
    SetConsoleMode(DAT_004e9048,DAT_004e9040);
  }
  return;
}


/* ==== abort_check @ 0043dbc0 ==== */

int abort_check(void)

{
  if (abort_flag != 0) {
    *(undefined4 *)(*(int *)(dev_tab + run_dev_index * 4) + 0x48) = 1;
    abort_flag = 0;
  }
  return *(int *)(cur_dev + 0x48);
}


/* ==== screen_fill_rows @ 0043dc00 ==== */

void __cdecl screen_fill_rows(char *text)

{
  uint n;
  uint uVar1;
  char *dst;
  undefined4 *puVar2;
  char *src;
  undefined4 *puVar3;
  
  src = text;
  n = screen_cols;
  screen_hold_cnt = screen_hold_cnt + 1;
  screen_top_row = 0;
  if ((no_console == 0) && (text = (char *)0x0, 0 < text_rows)) {
    puVar2 = &screen_attr_buf;
    dst = (char *)&screen_char_buf;
    do {
      strncpy(dst,src,n);
      puVar3 = puVar2;
      for (uVar1 = n >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar3 = 0x7070707;
        puVar3 = puVar3 + 1;
      }
      src = src + 0x101;
      for (uVar1 = n & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
        *(undefined1 *)puVar3 = 7;
        puVar3 = (undefined4 *)((int)puVar3 + 1);
      }
      text = text + 1;
      dst = dst + 0x101;
      puVar2 = puVar2 + 0x40;
    } while ((int)text < text_rows);
  }
  screen_release();
  return;
}


/* ==== pool_init @ 0043dcb0 ==== */

void __cdecl pool_init(int *pool,ulong blocksize)

{
  ulong uVar1;
  
  pool[5] = 0;
  pool[4] = blocksize;
  uVar1 = pool_new_block((int)pool,blocksize,1);
  pool[3] = uVar1;
  *pool = uVar1;
  uVar1 = pool_new_block((int)pool,blocksize,0);
  pool[2] = uVar1;
  pool[1] = uVar1;
  *(ulong *)(*pool + 0x10) = uVar1;
  return;
}


/* ==== pool_new_block @ 0043dcf0 ==== */

ulong __cdecl pool_new_block(int pool,ulong size,ulong kind)

{
  ulong *extraout_EAX;
  ulong extraout_EAX_00;
  
  prof_malloc(0x14);
  prof_malloc(size);
  extraout_EAX[2] = extraout_EAX_00;
  extraout_EAX[3] = extraout_EAX_00;
  extraout_EAX[4] = 0;
  extraout_EAX[1] = kind;
  *extraout_EAX = size;
  *(int *)(pool + 0x14) = *(int *)(pool + 0x14) + 1;
  return (ulong)extraout_EAX;
}


/* ==== chain_free @ 0043dd40 ==== */

void __cdecl chain_free(void **head)

{
  void *pvVar1;
  void *p;
  
  p = *head;
  while (p != (void *)0x0) {
    pvVar1 = *(void **)((int)p + 0x10);
    dsp_free(*(void **)((int)p + 8));
    dsp_free(p);
    p = pvVar1;
  }
  return;
}


/* ==== pool_alloc @ 0043dd70 ==== */

int __cdecl pool_alloc(int pool,ulong n)

{
  ulong uVar1;
  ulong size;
  int iVar2;
  
  if ((n & 7) != 0) {
    n = n + (8 - (n & 7));
  }
  uVar1 = *(ulong *)(pool + 8);
  size = *(ulong *)(pool + 0x10);
  if ((int)size < (int)((*(int *)(uVar1 + 0xc) - *(int *)(uVar1 + 8)) + n)) {
    if ((int)size <= (int)n) {
      size = n;
    }
    iVar2 = *(int *)(pool + 4);
    uVar1 = pool_new_block(pool,size,0);
    *(ulong *)(iVar2 + 0x10) = uVar1;
    *(ulong *)(pool + 8) = uVar1;
    *(ulong *)(pool + 4) = uVar1;
  }
  iVar2 = *(int *)(uVar1 + 0xc) + n;
  *(int *)(uVar1 + 0xc) = iVar2;
  return iVar2 - n;
}


/* ==== pool_strdup @ 0043ddd0 ==== */

char __cdecl pool_strdup(int pool,char *s)

{
  char cVar1;
  ulong uVar2;
  uint uVar3;
  ulong size;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  
  if (s == (char *)0x0) {
    return '\0';
  }
  uVar3 = 0xffffffff;
  pcVar6 = s;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  uVar2 = *(ulong *)(pool + 0xc);
  size = *(ulong *)(pool + 0x10);
  if ((int)size < (int)((*(int *)(uVar2 + 0xc) - *(int *)(uVar2 + 8)) + uVar3)) {
    if ((int)size <= (int)uVar3) {
      size = uVar3;
    }
    iVar5 = *(int *)(pool + 4);
    uVar2 = pool_new_block(pool,size,1);
    *(ulong *)(iVar5 + 0x10) = uVar2;
    *(ulong *)(pool + 0xc) = uVar2;
    *(ulong *)(pool + 4) = uVar2;
  }
  iVar5 = *(int *)(uVar2 + 0xc) + uVar3;
  uVar4 = 0xffffffff;
  *(int *)(uVar2 + 0xc) = iVar5;
  DAT_00502070 = (char *)(iVar5 - uVar3);
  do {
    pcVar6 = s;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar6 = s + 1;
    cVar1 = *s;
    s = pcVar6;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar6 = pcVar6 + -uVar4;
  pcVar7 = DAT_00502070;
  for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  return (char)DAT_00502070;
}


/* ==== avl_cmp_h43de70 @ 0043de70 ==== */

char avl_cmp_h43de70(int *param_1,int *param_2)

{
  if (*param_2 < *param_1) {
    return '\0';
  }
  if (*param_1 < *param_2) {
    return '\x02';
  }
  if (param_2[1] < param_1[1]) {
    return '\0';
  }
  return (param_1[1] < param_2[1]) + '\x01';
}


/* ==== cdb_snapshot_write @ 0043deb0 ==== */

void __cdecl cdb_snapshot_write(char *name,int unused,int mode)

{
  ulong *buf;
  ulong uVar1;
  int *piVar2;
  char cVar3;
  char cVar4;
  int iVar5;
  void *extraout_EAX;
  void *extraout_EAX_00;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int local_c;
  int *local_8;
  void *buf_00;
  
  if (name == (char *)0x0) {
    if (snap_file != (void *)0x0) {
      fclose(snap_file);
      return;
    }
  }
  else {
    local_8 = (int *)(cur_sim + 0x188);
    prof_ctx = cur_sim + 0x490;
    iVar5 = _setjmp3(&prof_jmpbuf,0);
    if ((iVar5 == 0) && (DAT_00502064 != 1)) {
      if (mode == 0) {
        DAT_00502064 = 0;
        prof_fopen(name,&DAT_004c63b4,(char *)0x0,1);
        snap_file = extraout_EAX;
      }
      piVar2 = local_8;
      prof_fwrite(local_8,0x3aac,1,snap_file,1);
      if (*piVar2 != 0) {
        *(undefined4 *)(prof_ctx + 0x3500) = 1;
        avl_new(0xc);
        snap_reloc_list = extraout_EAX_00;
        snap_reloc_add((ulong *)&prof_ctx,1);
        *(undefined4 *)(prof_ctx + 0x3500) = 0;
        for (buf = *(ulong **)(prof_ctx + 0x34e8); buf != (ulong *)0x0; buf = (ulong *)buf[4]) {
          uVar1 = buf[1];
          prof_fwrite(buf,0x14,1,snap_file,1);
          prof_fwrite((void *)buf[2],*buf,1,snap_file,(uint)(uVar1 != 1));
        }
        local_c = prof_list_count(snap_reloc_list);
        prof_fwrite(&local_c,4,1,snap_file,1);
        cVar3 = avl_iter(snap_reloc_list,(char *)0x0,(void *)0x0);
        cVar4 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar3),(void *)0x0);
        buf_00 = (void *)CONCAT31(extraout_var_00,cVar4);
        while (buf_00 != (void *)0x0) {
          prof_fwrite(buf_00,0x10,1,snap_file,1);
          cVar4 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar3),(void *)0x0);
          buf_00 = (void *)CONCAT31(extraout_var_01,cVar4);
        }
        avl_free(snap_reloc_list,1);
        return;
      }
    }
    else {
      DAT_00502064 = 1;
      snap_file = (void *)0x0;
    }
  }
  return;
}


