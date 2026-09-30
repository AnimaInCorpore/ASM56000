/* ==== watch_format_value @ 0043f010 ==== */

void __cdecl watch_format_value(void *watch,char *out)

{
  uint va0;
  bool bVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int *node;
  int *node_00;
  char *pcVar6;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int *dbl;
  char *pcVar13;
  char *pcVar14;
  uint uStack_10c;
  uint uStack_108;
  char acStack_100 [256];
  
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar3 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar3 = (**(code **)(cur_dtype + 0x4e8))();
  }
  if (((uVar3 & 0x10000000) == 0) || (bVar1 = true, (uVar3 & 0x5000000) != 0)) {
    bVar1 = false;
  }
  uVar4 = uVar3 >> 0x19 & 1;
  uVar5 = uVar3 >> 0x1a & 1;
  if (*(int *)((int)watch + 0x104) == 2) {
    optr = (int)watch + 4;
    eval_expr(uVar3);
    if (node == (int *)0x0) {
      sprintf(out,s_Invalid_Expression_004c6ad8);
      return;
    }
    node_get_double(uVar3,node);
    dbl = node;
  }
  else {
    optr = (int)watch + 4;
    eval_expr(uVar3);
    if (node_00 == (int *)0x0) {
      sprintf(out,s_Invalid_Expression_004c6ad8);
      return;
    }
    node_from_double(uVar3,node_00);
    dbl = node_00;
  }
  uVar12 = dbl[3];
  uVar11 = dbl[7];
  va0 = dbl[2];
  uVar10 = dbl[4];
  *out = '\0';
  if ((*(int *)((int)watch + 0x108) == -1) || (*(int *)((int)watch + 0x108) == 3)) {
    if ((uVar11 & 4) == 0) {
      if ((uVar11 & 2) == 0) {
        if (bVar1) {
          pcVar6 = s___04lx_004c6328;
        }
        else {
          pcVar6 = s___06lx_004c6320;
          if (uVar5 == 0) {
            pcVar6 = s___08lx_004c6318;
          }
        }
        sprintf(acStack_100,pcVar6,va0);
      }
      else {
        if (bVar1) {
          pcVar6 = s___04lx_04lx_004c630c;
        }
        else {
          pcVar6 = s___06lx_06lx_004c62e8;
          if (uVar5 == 0) {
            pcVar6 = s___08lx_08lx_004c6300;
          }
        }
        sprintf(acStack_100,pcVar6,uVar12,va0);
      }
    }
    else {
      if ((uVar3 >> 0x18 & 1) == 0) {
        if (bVar1) {
          pcVar6 = s___02lx_04lx_04lx_004c62b4;
        }
        else {
          pcVar6 = s___02lx_06lx_06lx_004c628c;
          if (uVar5 == 0) {
            pcVar6 = s___08lx_08lx_08lx_004c62a0;
          }
        }
      }
      else {
        pcVar6 = s___01lx_04lx_04lx_004c62c8;
      }
      sprintf(acStack_100,pcVar6,uVar10,uVar12,va0);
    }
    uVar7 = 0xffffffff;
    pcVar6 = acStack_100;
    do {
      pcVar13 = pcVar6;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar13 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar13;
    } while (cVar2 != '\0');
    uVar7 = ~uVar7;
    iVar8 = -1;
    pcVar6 = out;
    do {
      pcVar14 = pcVar6;
      if (iVar8 == 0) break;
      iVar8 = iVar8 + -1;
      pcVar14 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar14;
    } while (cVar2 != '\0');
    pcVar6 = pcVar13 + -uVar7;
    pcVar13 = pcVar14 + -1;
    for (uVar9 = uVar7 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar13 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar13 = pcVar13 + 1;
    }
  }
  iVar8 = *(int *)((int)watch + 0x108);
  if ((iVar8 != 1) && (iVar8 != 4)) goto LAB_0043f3db;
  acStack_100[0] = '\0';
  if ((uVar11 & 4) == 0) {
    if ((uVar11 & 2) == 0) {
      uVar3 = va0;
      if (iVar8 == 1) {
        if ((uVar11 & 0x80000000) == 0) {
          if ((uVar11 & 0x40000000) == 0) {
            if ((uVar11 & 0x20000000) == 0) {
              if ((uVar11 & 0x10000000) == 0) {
                if ((uVar11 & 0x8000000) == 0) {
                  uVar7 = (-(uint)((uVar11 & 0x4000000) != 0) & 0x80800000) + 0x80000000;
                }
                else {
                  uVar7 = 0x80000;
                }
              }
              else {
                uVar7 = 0x8000;
              }
            }
            else {
              uVar7 = 0x800;
            }
          }
          else {
            uVar7 = 0x80;
          }
        }
        else {
          uVar7 = 8;
        }
        if ((va0 & uVar7) != 0) {
          uVar3 = ~(uVar7 - 1) | va0;
        }
      }
      pcVar6 = s__05ld_004c6274;
      if (iVar8 != 1) {
        pcVar6 = s__05lu_004c626c;
      }
      sprintf(acStack_100,pcVar6,uVar3);
    }
    else {
      if (uVar4 == 0) {
        val_to_dec_parts(uVar3,(ulong *)(dbl + 2),(long *)&uStack_10c);
        pcVar6 = s__06lu_09lu_004c6250;
      }
      else {
        if (iVar8 == -1) goto LAB_0043f3a3;
        pcVar6 = s___08lx_08lx_004c6300;
        uStack_108 = uVar12;
        uStack_10c = va0;
      }
      sprintf(acStack_100,pcVar6,uStack_108,uStack_10c);
    }
  }
  else if (uVar4 == 0) {
    val_to_dec_parts2(uVar3,(ulong *)(dbl + 2),&uStack_10c);
    sprintf(acStack_100,s__06lu_09lu_004c6250,uStack_108,uStack_10c);
  }
  else if (iVar8 != -1) {
    sprintf(acStack_100,s___08lx_08lx_08lx_004c62a0,uVar10,uVar12,va0);
  }
LAB_0043f3a3:
  uVar3 = 0xffffffff;
  pcVar6 = acStack_100;
  do {
    pcVar13 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar13 = pcVar6 + 1;
    cVar2 = *pcVar6;
    pcVar6 = pcVar13;
  } while (cVar2 != '\0');
  uVar3 = ~uVar3;
  iVar8 = -1;
  pcVar6 = out;
  do {
    pcVar14 = pcVar6;
    if (iVar8 == 0) break;
    iVar8 = iVar8 + -1;
    pcVar14 = pcVar6 + 1;
    cVar2 = *pcVar6;
    pcVar6 = pcVar14;
  } while (cVar2 != '\0');
  pcVar6 = pcVar13 + -uVar3;
  pcVar13 = pcVar14 + -1;
  for (uVar7 = uVar3 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar13 = pcVar13 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar13 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar13 = pcVar13 + 1;
  }
LAB_0043f3db:
  if (*(int *)((int)watch + 0x108) == 2) {
    if (uVar4 == 0) {
      if ((uVar11 & 6) == 0) {
        pcVar6 = s__10_7g_004c6ab8;
      }
      else {
        pcVar6 = s__13_10g_004c6ac0;
      }
      sprintf(acStack_100,pcVar6,*dbl,dbl[1]);
    }
    else if ((uVar11 & 6) == 0) {
      cVar2 = fmt_float_exp(s__14_14s_004c6ac8,dbl);
      sprintf(acStack_100,s__14_14s_004c6ac8,CONCAT31(extraout_var_00,cVar2));
    }
    else {
      cVar2 = fmt_float_exp(s__25_25s_004c6ad0,dbl);
      sprintf(acStack_100,s__25_25s_004c6ad0,CONCAT31(extraout_var,cVar2));
    }
    uVar3 = 0xffffffff;
    pcVar6 = acStack_100;
    do {
      pcVar13 = pcVar6;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar13 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar13;
    } while (cVar2 != '\0');
    uVar3 = ~uVar3;
    iVar8 = -1;
    pcVar6 = out;
    do {
      pcVar14 = pcVar6;
      if (iVar8 == 0) break;
      iVar8 = iVar8 + -1;
      pcVar14 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar14;
    } while (cVar2 != '\0');
    pcVar6 = pcVar13 + -uVar3;
    pcVar13 = pcVar14 + -1;
    for (uVar7 = uVar3 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar13 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar13 = pcVar13 + 1;
    }
  }
  if (*(int *)((int)watch + 0x108) == 0) {
    if ((uVar11 & 4) != 0) {
      if (uVar4 != 0) {
        uVar3 = 0xffffffff;
        pcVar6 = (&PTR_DAT_004c6608)[(int)uVar10 >> 0x1c & 0xf];
        do {
          pcVar13 = pcVar6;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pcVar13 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar13;
        } while (cVar2 != '\0');
        uVar3 = ~uVar3;
        iVar8 = -1;
        pcVar6 = out;
        do {
          pcVar14 = pcVar6;
          if (iVar8 == 0) break;
          iVar8 = iVar8 + -1;
          pcVar14 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar14;
        } while (cVar2 != '\0');
        pcVar6 = pcVar13 + -uVar3;
        pcVar13 = pcVar14 + -1;
        for (uVar7 = uVar3 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar13 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar13 = pcVar13 + 1;
        }
        uVar3 = 0xffffffff;
        pcVar6 = (&PTR_DAT_004c6608)[(int)uVar10 >> 0x18 & 0xf];
        do {
          pcVar13 = pcVar6;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pcVar13 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar13;
        } while (cVar2 != '\0');
        uVar3 = ~uVar3;
        iVar8 = -1;
        pcVar6 = out;
        do {
          pcVar14 = pcVar6;
          if (iVar8 == 0) break;
          iVar8 = iVar8 + -1;
          pcVar14 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar14;
        } while (cVar2 != '\0');
        pcVar6 = pcVar13 + -uVar3;
        pcVar13 = pcVar14 + -1;
        for (uVar7 = uVar3 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar13 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar13 = pcVar13 + 1;
        }
        uVar3 = 0xffffffff;
        pcVar6 = (&PTR_DAT_004c6608)[(int)uVar10 >> 0x14 & 0xf];
        do {
          pcVar13 = pcVar6;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pcVar13 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar13;
        } while (cVar2 != '\0');
        uVar3 = ~uVar3;
        iVar8 = -1;
        pcVar6 = out;
        do {
          pcVar14 = pcVar6;
          if (iVar8 == 0) break;
          iVar8 = iVar8 + -1;
          pcVar14 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar14;
        } while (cVar2 != '\0');
        pcVar6 = pcVar13 + -uVar3;
        pcVar13 = pcVar14 + -1;
        for (uVar7 = uVar3 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar13 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar13 = pcVar13 + 1;
        }
        uVar3 = 0xffffffff;
        pcVar6 = (&PTR_DAT_004c6608)[(int)uVar10 >> 0x10 & 0xf];
        do {
          pcVar13 = pcVar6;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pcVar13 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar13;
        } while (cVar2 != '\0');
        uVar3 = ~uVar3;
        iVar8 = -1;
        pcVar6 = out;
        do {
          pcVar14 = pcVar6;
          if (iVar8 == 0) break;
          iVar8 = iVar8 + -1;
          pcVar14 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar14;
        } while (cVar2 != '\0');
        pcVar6 = pcVar13 + -uVar3;
        pcVar13 = pcVar14 + -1;
        for (uVar7 = uVar3 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar13 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar13 = pcVar13 + 1;
        }
        uVar3 = 0xffffffff;
        pcVar6 = (&PTR_DAT_004c6608)[(int)uVar10 >> 0xc & 0xf];
        do {
          pcVar13 = pcVar6;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pcVar13 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar13;
        } while (cVar2 != '\0');
        uVar3 = ~uVar3;
        iVar8 = -1;
        pcVar6 = out;
        do {
          pcVar14 = pcVar6;
          if (iVar8 == 0) break;
          iVar8 = iVar8 + -1;
          pcVar14 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar14;
        } while (cVar2 != '\0');
        pcVar6 = pcVar13 + -uVar3;
        pcVar13 = pcVar14 + -1;
        for (uVar7 = uVar3 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar13 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar13 = pcVar13 + 1;
        }
        uVar3 = 0xffffffff;
        pcVar6 = (&PTR_DAT_004c6608)[(int)uVar10 >> 8 & 0xf];
        do {
          pcVar13 = pcVar6;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pcVar13 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar13;
        } while (cVar2 != '\0');
        uVar3 = ~uVar3;
        iVar8 = -1;
        pcVar6 = out;
        do {
          pcVar14 = pcVar6;
          if (iVar8 == 0) break;
          iVar8 = iVar8 + -1;
          pcVar14 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar14;
        } while (cVar2 != '\0');
        pcVar6 = pcVar13 + -uVar3;
        pcVar13 = pcVar14 + -1;
        for (uVar7 = uVar3 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar13 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar13 = pcVar13 + 1;
        }
      }
      uVar3 = 0xffffffff;
      pcVar6 = (&PTR_DAT_004c6608)[(int)uVar10 >> 4 & 0xf];
      do {
        pcVar13 = pcVar6;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar13 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar13;
      } while (cVar2 != '\0');
      uVar3 = ~uVar3;
      iVar8 = -1;
      pcVar6 = out;
      do {
        pcVar14 = pcVar6;
        if (iVar8 == 0) break;
        iVar8 = iVar8 + -1;
        pcVar14 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar14;
      } while (cVar2 != '\0');
      pcVar6 = pcVar13 + -uVar3;
      pcVar13 = pcVar14 + -1;
      for (uVar7 = uVar3 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar13 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar13 = pcVar13 + 1;
      }
      uVar3 = 0xffffffff;
      pcVar6 = (&PTR_DAT_004c6608)[uVar10 & 0xf];
      do {
        pcVar13 = pcVar6;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar13 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar13;
      } while (cVar2 != '\0');
      uVar3 = ~uVar3;
      iVar8 = -1;
      pcVar6 = out;
      do {
        pcVar14 = pcVar6;
        if (iVar8 == 0) break;
        iVar8 = iVar8 + -1;
        pcVar14 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar14;
      } while (cVar2 != '\0');
      pcVar6 = pcVar13 + -uVar3;
      pcVar13 = pcVar14 + -1;
      for (uVar10 = uVar3 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar13 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
    if ((uVar11 & 6) != 0) {
      if (uVar4 != 0) {
        uVar3 = 0xffffffff;
        pcVar6 = (&PTR_DAT_004c6608)[(int)uVar12 >> 0x1c & 0xf];
        do {
          pcVar13 = pcVar6;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pcVar13 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar13;
        } while (cVar2 != '\0');
        uVar3 = ~uVar3;
        iVar8 = -1;
        pcVar6 = out;
        do {
          pcVar14 = pcVar6;
          if (iVar8 == 0) break;
          iVar8 = iVar8 + -1;
          pcVar14 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar14;
        } while (cVar2 != '\0');
        pcVar6 = pcVar13 + -uVar3;
        pcVar13 = pcVar14 + -1;
        for (uVar11 = uVar3 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar13 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar13 = pcVar13 + 1;
        }
        uVar3 = 0xffffffff;
        pcVar6 = (&PTR_DAT_004c6608)[(int)uVar12 >> 0x18 & 0xf];
        do {
          pcVar13 = pcVar6;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pcVar13 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar13;
        } while (cVar2 != '\0');
        uVar3 = ~uVar3;
        iVar8 = -1;
        pcVar6 = out;
        do {
          pcVar14 = pcVar6;
          if (iVar8 == 0) break;
          iVar8 = iVar8 + -1;
          pcVar14 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar14;
        } while (cVar2 != '\0');
        pcVar6 = pcVar13 + -uVar3;
        pcVar13 = pcVar14 + -1;
        for (uVar11 = uVar3 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar13 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar13 = pcVar13 + 1;
        }
      }
      if ((uVar5 != 0) || (uVar4 != 0)) {
        uVar3 = 0xffffffff;
        pcVar6 = (&PTR_DAT_004c6608)[(int)uVar12 >> 0x14 & 0xf];
        do {
          pcVar13 = pcVar6;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pcVar13 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar13;
        } while (cVar2 != '\0');
        uVar3 = ~uVar3;
        iVar8 = -1;
        pcVar6 = out;
        do {
          pcVar14 = pcVar6;
          if (iVar8 == 0) break;
          iVar8 = iVar8 + -1;
          pcVar14 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar14;
        } while (cVar2 != '\0');
        pcVar6 = pcVar13 + -uVar3;
        pcVar13 = pcVar14 + -1;
        for (uVar11 = uVar3 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar13 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar13 = pcVar13 + 1;
        }
        uVar3 = 0xffffffff;
        pcVar6 = (&PTR_DAT_004c6608)[(int)uVar12 >> 0x10 & 0xf];
        do {
          pcVar13 = pcVar6;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pcVar13 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar13;
        } while (cVar2 != '\0');
        uVar3 = ~uVar3;
        iVar8 = -1;
        pcVar6 = out;
        do {
          pcVar14 = pcVar6;
          if (iVar8 == 0) break;
          iVar8 = iVar8 + -1;
          pcVar14 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar14;
        } while (cVar2 != '\0');
        pcVar6 = pcVar13 + -uVar3;
        pcVar13 = pcVar14 + -1;
        for (uVar11 = uVar3 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar13 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar13 = pcVar13 + 1;
        }
      }
      uVar3 = 0xffffffff;
      pcVar6 = (&PTR_DAT_004c6608)[(int)uVar12 >> 0xc & 0xf];
      do {
        pcVar13 = pcVar6;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar13 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar13;
      } while (cVar2 != '\0');
      uVar3 = ~uVar3;
      iVar8 = -1;
      pcVar6 = out;
      do {
        pcVar14 = pcVar6;
        if (iVar8 == 0) break;
        iVar8 = iVar8 + -1;
        pcVar14 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar14;
      } while (cVar2 != '\0');
      pcVar6 = pcVar13 + -uVar3;
      pcVar13 = pcVar14 + -1;
      for (uVar11 = uVar3 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar13 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar13 = pcVar13 + 1;
      }
      uVar3 = 0xffffffff;
      pcVar6 = (&PTR_DAT_004c6608)[(int)uVar12 >> 8 & 0xf];
      do {
        pcVar13 = pcVar6;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar13 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar13;
      } while (cVar2 != '\0');
      uVar3 = ~uVar3;
      iVar8 = -1;
      pcVar6 = out;
      do {
        pcVar14 = pcVar6;
        if (iVar8 == 0) break;
        iVar8 = iVar8 + -1;
        pcVar14 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar14;
      } while (cVar2 != '\0');
      pcVar6 = pcVar13 + -uVar3;
      pcVar13 = pcVar14 + -1;
      for (uVar11 = uVar3 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar13 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar13 = pcVar13 + 1;
      }
      uVar3 = 0xffffffff;
      pcVar6 = (&PTR_DAT_004c6608)[(int)uVar12 >> 4 & 0xf];
      do {
        pcVar13 = pcVar6;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar13 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar13;
      } while (cVar2 != '\0');
      uVar3 = ~uVar3;
      iVar8 = -1;
      pcVar6 = out;
      do {
        pcVar14 = pcVar6;
        if (iVar8 == 0) break;
        iVar8 = iVar8 + -1;
        pcVar14 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar14;
      } while (cVar2 != '\0');
      pcVar6 = pcVar13 + -uVar3;
      pcVar13 = pcVar14 + -1;
      for (uVar11 = uVar3 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar13 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar13 = pcVar13 + 1;
      }
      uVar3 = 0xffffffff;
      pcVar6 = (&PTR_DAT_004c6608)[uVar12 & 0xf];
      do {
        pcVar13 = pcVar6;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar13 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar13;
      } while (cVar2 != '\0');
      uVar3 = ~uVar3;
      iVar8 = -1;
      pcVar6 = out;
      do {
        pcVar14 = pcVar6;
        if (iVar8 == 0) break;
        iVar8 = iVar8 + -1;
        pcVar14 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar14;
      } while (cVar2 != '\0');
      pcVar6 = pcVar13 + -uVar3;
      pcVar13 = pcVar14 + -1;
      for (uVar12 = uVar3 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar13 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
    if (uVar4 != 0) {
      uVar3 = 0xffffffff;
      pcVar6 = (&PTR_DAT_004c6608)[(int)va0 >> 0x1c & 0xf];
      do {
        pcVar13 = pcVar6;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar13 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar13;
      } while (cVar2 != '\0');
      uVar3 = ~uVar3;
      iVar8 = -1;
      pcVar6 = out;
      do {
        pcVar14 = pcVar6;
        if (iVar8 == 0) break;
        iVar8 = iVar8 + -1;
        pcVar14 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar14;
      } while (cVar2 != '\0');
      pcVar6 = pcVar13 + -uVar3;
      pcVar13 = pcVar14 + -1;
      for (uVar12 = uVar3 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar13 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar13 = pcVar13 + 1;
      }
      uVar3 = 0xffffffff;
      pcVar6 = (&PTR_DAT_004c6608)[(int)va0 >> 0x18 & 0xf];
      do {
        pcVar13 = pcVar6;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar13 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar13;
      } while (cVar2 != '\0');
      uVar3 = ~uVar3;
      iVar8 = -1;
      pcVar6 = out;
      do {
        pcVar14 = pcVar6;
        if (iVar8 == 0) break;
        iVar8 = iVar8 + -1;
        pcVar14 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar14;
      } while (cVar2 != '\0');
      pcVar6 = pcVar13 + -uVar3;
      pcVar13 = pcVar14 + -1;
      for (uVar12 = uVar3 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar13 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
    if ((uVar5 != 0) || (uVar4 != 0)) {
      uVar3 = 0xffffffff;
      pcVar6 = (&PTR_DAT_004c6608)[(int)va0 >> 0x14 & 0xf];
      do {
        pcVar13 = pcVar6;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar13 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar13;
      } while (cVar2 != '\0');
      uVar3 = ~uVar3;
      iVar8 = -1;
      pcVar6 = out;
      do {
        pcVar14 = pcVar6;
        if (iVar8 == 0) break;
        iVar8 = iVar8 + -1;
        pcVar14 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar14;
      } while (cVar2 != '\0');
      pcVar6 = pcVar13 + -uVar3;
      pcVar13 = pcVar14 + -1;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar13 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar13 = pcVar13 + 1;
      }
      uVar3 = 0xffffffff;
      pcVar6 = (&PTR_DAT_004c6608)[(int)va0 >> 0x10 & 0xf];
      do {
        pcVar13 = pcVar6;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar13 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar13;
      } while (cVar2 != '\0');
      uVar3 = ~uVar3;
      iVar8 = -1;
      pcVar6 = out;
      do {
        pcVar14 = pcVar6;
        if (iVar8 == 0) break;
        iVar8 = iVar8 + -1;
        pcVar14 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar14;
      } while (cVar2 != '\0');
      pcVar6 = pcVar13 + -uVar3;
      pcVar13 = pcVar14 + -1;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar13 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
    uVar3 = 0xffffffff;
    pcVar6 = (&PTR_DAT_004c6608)[(int)va0 >> 0xc & 0xf];
    do {
      pcVar13 = pcVar6;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar13 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar13;
    } while (cVar2 != '\0');
    uVar3 = ~uVar3;
    iVar8 = -1;
    pcVar6 = out;
    do {
      pcVar14 = pcVar6;
      if (iVar8 == 0) break;
      iVar8 = iVar8 + -1;
      pcVar14 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar14;
    } while (cVar2 != '\0');
    pcVar6 = pcVar13 + -uVar3;
    pcVar13 = pcVar14 + -1;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar13 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar13 = pcVar13 + 1;
    }
    uVar3 = 0xffffffff;
    pcVar6 = (&PTR_DAT_004c6608)[(int)va0 >> 8 & 0xf];
    do {
      pcVar13 = pcVar6;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar13 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar13;
    } while (cVar2 != '\0');
    uVar3 = ~uVar3;
    iVar8 = -1;
    pcVar6 = out;
    do {
      pcVar14 = pcVar6;
      if (iVar8 == 0) break;
      iVar8 = iVar8 + -1;
      pcVar14 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar14;
    } while (cVar2 != '\0');
    pcVar6 = pcVar13 + -uVar3;
    pcVar13 = pcVar14 + -1;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar13 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar13 = pcVar13 + 1;
    }
    uVar3 = 0xffffffff;
    pcVar6 = (&PTR_DAT_004c6608)[(int)va0 >> 4 & 0xf];
    do {
      pcVar13 = pcVar6;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar13 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar13;
    } while (cVar2 != '\0');
    uVar3 = ~uVar3;
    iVar8 = -1;
    pcVar6 = out;
    do {
      pcVar14 = pcVar6;
      if (iVar8 == 0) break;
      iVar8 = iVar8 + -1;
      pcVar14 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar14;
    } while (cVar2 != '\0');
    pcVar6 = pcVar13 + -uVar3;
    pcVar13 = pcVar14 + -1;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar13 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar13 = pcVar13 + 1;
    }
    uVar3 = 0xffffffff;
    pcVar6 = (&PTR_DAT_004c6608)[va0 & 0xf];
    do {
      pcVar13 = pcVar6;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar13 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar13;
    } while (cVar2 != '\0');
    uVar3 = ~uVar3;
    iVar8 = -1;
    do {
      pcVar6 = out;
      if (iVar8 == 0) break;
      iVar8 = iVar8 + -1;
      pcVar6 = out + 1;
      cVar2 = *out;
      out = pcVar6;
    } while (cVar2 != '\0');
    pcVar13 = pcVar13 + -uVar3;
    pcVar6 = pcVar6 + -1;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar13;
      pcVar13 = pcVar13 + 4;
      pcVar6 = pcVar6 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar6 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      pcVar6 = pcVar6 + 1;
    }
  }
  node_free(dbl);
  return;
}


/* ==== cmd_watch_parse @ 0043fa30 ==== */

undefined ** cmd_watch_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(2);
  if (iVar1 != 0) {
    iVar2 = 2;
    goto LAB_0043fd01;
  }
  iVar1 = parm_break_number_ff(2);
  if (iVar1 == 0) {
    iVar1 = parm_keyword1(2,&DAT_004c6aec);
    if ((iVar1 != 0) && (iVar1 = parm_check_too_many(3), iVar1 != 0)) {
      iVar2 = 1;
      goto LAB_0043fd01;
    }
    iVar1 = parm_brace_block(2);
    if ((iVar1 != 0) && (iVar1 = parm_check_too_many(3), iVar1 != 0)) {
      iVar1 = 2;
      goto LAB_0043fc9d;
    }
    iVar1 = parm_register(2);
    if ((((iVar1 == 0) || (iVar1 = parm_check_too_many(3), iVar1 == 0)) &&
        ((iVar1 = parm_match_space_cur(2), iVar1 == 0 ||
         (iVar1 = parm_check_too_many(3), iVar1 == 0)))) &&
       ((iVar1 = parm_number_expr(2), iVar1 == 0 || (iVar1 = parm_check_too_many(3), iVar1 == 0))))
    {
      iVar1 = parm_kw_r_radix(2);
      if (iVar1 == 0) goto LAB_0043fd01;
      iVar1 = parm_brace_block(3);
      if ((iVar1 != 0) && (iVar1 = parm_check_too_many(4), iVar1 != 0)) goto LAB_0043fc9b;
      iVar1 = parm_register(3);
      if (((iVar1 != 0) && (iVar1 = parm_check_too_many(4), iVar1 != 0)) ||
         ((iVar1 = parm_match_space_cur(3), iVar1 != 0 &&
          (iVar1 = parm_check_too_many(4), iVar1 != 0)))) goto LAB_0043fcff;
      iVar1 = parm_number_expr(3);
      if (iVar1 == 0) goto LAB_0043fd01;
      iVar1 = parm_check_too_many(4);
      goto joined_r0x0043fbb4;
    }
  }
  else {
    iVar1 = parm_check_too_many(3);
    if (iVar1 != 0) {
      iVar2 = 2;
      goto LAB_0043fd01;
    }
    iVar1 = parm_brace_block(3);
    if ((iVar1 == 0) || (iVar1 = parm_check_too_many(4), iVar1 == 0)) {
      iVar1 = parm_register(3);
      if ((((iVar1 == 0) || (iVar1 = parm_check_too_many(4), iVar1 == 0)) &&
          ((iVar1 = parm_match_space_cur(3), iVar1 == 0 ||
           (iVar1 = parm_check_too_many(4), iVar1 == 0)))) &&
         ((iVar1 = parm_number_expr(3), iVar1 == 0 || (iVar1 = parm_check_too_many(4), iVar1 == 0)))
         ) {
        iVar1 = parm_keyword1(3,&DAT_004c6aec);
        if ((iVar1 != 0) && (iVar1 = parm_check_too_many(4), iVar1 != 0)) {
          iVar2 = 1;
          goto LAB_0043fd01;
        }
        iVar1 = parm_kw_r_radix(3);
        if (iVar1 == 0) goto LAB_0043fd01;
        iVar1 = parm_brace_block(4);
        if ((iVar1 != 0) && (iVar1 = parm_check_too_many(5), iVar1 != 0)) {
          iVar1 = 4;
          goto LAB_0043fc9d;
        }
        iVar1 = parm_register(4);
        if (((iVar1 == 0) || (iVar1 = parm_check_too_many(5), iVar1 == 0)) &&
           ((iVar1 = parm_match_space_cur(4), iVar1 == 0 ||
            (iVar1 = parm_check_too_many(5), iVar1 == 0)))) {
          iVar1 = parm_number_expr(4);
          if (iVar1 == 0) goto LAB_0043fd01;
          iVar1 = parm_check_too_many(5);
          goto joined_r0x0043fbb4;
        }
      }
      goto LAB_0043fcff;
    }
LAB_0043fc9b:
    iVar1 = 3;
LAB_0043fc9d:
    iVar1 = parm_watch_expr(iVar1);
joined_r0x0043fbb4:
    if (iVar1 == 0) goto LAB_0043fd01;
  }
LAB_0043fcff:
  iVar2 = 0;
LAB_0043fd01:
  if (iVar2 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_watch_h0_004c6648 + iVar2 * 2;
}


/* ==== cmd_wait_h0 @ 0043fd20 ==== */

void cmd_wait_h0(void)

{
  int iVar1;
  int iVar2;
  void *unaff_ESI;
  int iStack_4;
  
  if (gui_mode != 0) {
    dsp_free_ext(unaff_ESI);
    return;
  }
  screen_flush();
  if (DAT_004a93ea != 'e') {
    status_line2(s__Wait_command__Type_<CTRL_C>_to_c_004c6cb4);
    time(&iStack_4);
    iVar1 = iStack_4 + 1 + DAT_004a96c0;
    while ((iStack_4 <= iVar1 && (iVar2 = abort_check(), iVar2 == 0))) {
      time(&iStack_4);
    }
    return;
  }
  status_line2(s__Wait_command__Type_any_Key_to_c_004c6ce4);
  key_get();
  return;
}


/* ==== cmd_wait_parse @ 0043fdb0 ==== */

undefined ** cmd_wait_parse(void)

{
  int iVar1;
  
  iVar1 = parm_check_too_many(2);
  if (iVar1 != 0) {
    return &PTR_cmd_wait_h0_004c6b20;
  }
  iVar1 = parm_count_expr(2);
  if ((iVar1 != 0) && (iVar1 = parm_check_too_many(3), iVar1 != 0)) {
    return &PTR_cmd_wait_h0_004c6b20;
  }
  return (undefined **)0x0;
}


/* ==== src_find_line @ 0043fdf0 ==== */

int __cdecl src_find_line(uchar *name)

{
  int iVar1;
  
  if (*(int *)(cur_sim + 0x4030) == 0) {
    iVar1 = dbg_build_indexes();
    if (iVar1 == -1) {
      return -1;
    }
  }
  iVar1 = dbg_find_sym_d2((char *)name);
  return iVar1;
}


/* ==== addr_to_srcline @ 0043fe20 ==== */

int __cdecl addr_to_srcline(ulong addr,int level)

{
  ulong uVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  void *extraout_EAX;
  int iVar5;
  uint uVar6;
  ulong uVar7;
  uint uVar8;
  int iStack_c;
  int iStack_8;
  
  uVar1 = addr;
  iVar2 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(level,addr);
  iVar5 = *(int *)(cur_sim + 0x3fcc);
  if (iVar5 != 0) {
    puVar3 = (uint *)(*(int *)(cur_sim + 0x4014) + iVar5 * 0x20);
    if (((*puVar3 <= addr) && (addr - *puVar3 < puVar3[2])) &&
       (iVar4 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(puVar3[1],addr), iVar4 == iVar2)) {
      return iVar5;
    }
  }
  uVar7 = 3;
  addr = 0;
  iStack_8 = 0;
  level = 0;
  iVar5 = cur_sim;
  if (3 < *(int *)(cur_sim + 0x3fd0)) {
    iStack_c = 0x60;
    do {
      puVar3 = (uint *)(*(int *)(iVar5 + 0x4014) + iStack_c);
      if (((*puVar3 <= uVar1) && (uVar1 - *puVar3 < puVar3[2])) &&
         (iVar4 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(puVar3[1],uVar1), iVar5 = cur_sim,
         iVar4 == iVar2)) {
        if (addr == 0) {
          addr = uVar7;
        }
        level = uVar7;
        if (((puVar3[4] & 0x800) != 0) && (puVar3[5] != 0)) {
          iStack_8 = iStack_8 + 1;
        }
      }
      uVar7 = uVar7 + 1;
      iStack_c = iStack_c + 0x20;
    } while ((int)uVar7 < *(int *)(iVar5 + 0x3fd0));
  }
  iVar4 = level;
  if (iStack_8 != 0) {
    uVar8 = 0xffffffff;
    fopen(*(char **)(iVar5 + 0x4018),&DAT_004c5ff4);
    g_cld_fp = extraout_EAX;
    if (extraout_EAX == (void *)0x0) {
      expr_error2(s_cannot_open_input_file_004c7aa4,*(undefined4 *)(cur_sim + 0x4018));
      return 0;
    }
    if ((int)addr <= level) {
      uVar7 = addr;
      addr = addr << 5;
      do {
        puVar3 = (uint *)(*(int *)(cur_sim + 0x4014) + addr);
        uVar6 = *puVar3;
        if ((((uVar6 <= uVar1) && (uVar1 - uVar6 < puVar3[2])) &&
            (iVar5 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))
                               (*(undefined4 *)(*(int *)(cur_sim + 0x4014) + 4 + addr),uVar1),
            iVar5 == iVar2)) && (uVar6 = dbg_verify_section(0,uVar7), uVar6 < uVar8)) {
          uVar8 = uVar6;
          level = uVar7;
        }
        uVar7 = uVar7 + 1;
        addr = addr + 0x20;
      } while ((int)uVar7 <= iVar4);
    }
    fclose(g_cld_fp);
  }
  return level;
}


