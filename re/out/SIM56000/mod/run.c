/* ==== cmd_change_parse @ 004523c0 ==== */

void * cmd_change_parse(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int idx;
  
  iVar2 = parm_check_too_many(2);
  if (iVar2 == 0) {
    iVar2 = parm_register(2);
    if ((iVar2 == 0) || (iVar2 = parm_check_too_many(3), iVar2 == 0)) {
      iVar2 = parm_match_space_cur(2);
      if ((iVar2 == 0) || (iVar2 = parm_check_too_many(3), iVar2 == 0)) {
        iVar1 = g_tok_start;
        iVar2 = 2;
        idx = 2;
        if (1 < g_tok_start) {
          do {
            iVar3 = parm_addr_or_expr(idx);
            if ((iVar3 == 0) || (iVar3 = parm_number_expr(idx + 1), iVar3 == 0)) {
              iVar2 = -1;
              break;
            }
            idx = idx + 2;
          } while (idx <= iVar1);
        }
      }
      else {
        iVar2 = 1;
      }
    }
    else {
      iVar2 = 0;
    }
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 != -1) {
    return &PTR_cmd_change_h0_004cfec0 + iVar2 * 2;
  }
  return (void *)0x0;
}


/* ==== break_list_free @ 00452470 ==== */

void break_list_free(void)

{
  void *pvVar1;
  void *p;
  
  p = *(void **)(cur_sim + 0x3e78);
  while (p != (void *)0x0) {
    pvVar1 = *(void **)((int)p + 0x240);
    if (*(int *)((int)p + 4) == 0xc) {
      cdb_free_expr(*(void **)((int)p + 0x244));
    }
    dsp_free(p);
    p = pvVar1;
  }
  *(undefined4 *)(cur_sim + 0x3e78) = 0;
  return;
}


/* ==== sim_check_stop @ 004524d0 ==== */

int sim_check_stop(void)

{
  char cVar1;
  void *pvVar2;
  ulong uVar3;
  void *node;
  int extraout_EAX;
  undefined4 *puVar4;
  uint *puVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  void *value;
  int iVar9;
  int iVar10;
  uint uVar11;
  char *pcVar12;
  uint uVar13;
  int iVar14;
  char *pcVar15;
  uint *puVar16;
  bool bVar17;
  int local_164;
  int local_160;
  void *local_15c;
  uint local_158;
  int local_154;
  int local_150;
  uint local_14c;
  uint local_148;
  uint local_144;
  int local_140;
  uint local_13c [3];
  uint local_130;
  uint local_12c [8];
  ushort local_10c;
  undefined2 uStack_10a;
  ushort local_108;
  int local_104;
  char local_100 [256];
  
  local_164 = 0;
  local_160 = 0;
  uVar13 = *(uint *)(cur_dev + 0x44);
  local_154 = 0;
  local_158 = 0;
  uVar11 = uVar13 & 3;
  local_140 = 0;
  local_144 = 0;
  local_148 = 0;
  local_14c = uVar11;
  local_130 = uVar13;
  abort_check();
  if (uVar11 != 0) {
    if (*(int *)(cur_dev + 0x48) != 0) {
      *(undefined4 *)(cur_dev + 0x48) = 0;
      screen_hold();
      out_text(s__SIMULATION_ABORTED__004d1794,1);
      local_160 = 1;
      local_164 = 1;
    }
    if ((uVar13 & 4) != 0) {
      screen_hold();
      pcVar12 = s__Illegal_Op_Code_Encountered__004d1774;
      pcVar15 = local_100;
      for (iVar6 = 7; iVar6 != 0; iVar6 = iVar6 + -1) {
        *(undefined4 *)pcVar15 = *(undefined4 *)pcVar12;
        pcVar12 = pcVar12 + 4;
        pcVar15 = pcVar15 + 4;
      }
      *(undefined2 *)pcVar15 = *(undefined2 *)pcVar12;
      out_text(local_100,1);
      local_160 = 1;
      local_164 = 1;
    }
    if ((uVar13 & 0x40) != 0) {
      screen_hold();
      uVar7 = 0xffffffff;
      pcVar12 = parm_errmsg;
      do {
        pcVar15 = pcVar12;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar15 = pcVar12 + 1;
        cVar1 = *pcVar12;
        pcVar12 = pcVar15;
      } while (cVar1 != '\0');
      uVar7 = ~uVar7;
      pcVar12 = pcVar15 + -uVar7;
      pcVar15 = local_100;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar15 = *(undefined4 *)pcVar12;
        pcVar12 = pcVar12 + 4;
        pcVar15 = pcVar15 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar15 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        pcVar15 = pcVar15 + 1;
      }
      out_text(local_100,1);
      local_160 = 1;
      local_164 = 1;
    }
    if ((uVar13 & 0x10) != 0) {
      local_160 = 1;
      local_164 = 1;
    }
  }
  iVar6 = *(int *)(cur_sim + 0x34);
  local_104 = iVar6;
  if ((*(uint *)(cur_dev + 0x20) % 1000 == 0) && ((iVar6 == 0 || (4 < iVar6)))) {
    show_running_banner();
  }
  local_15c = *(void **)(cur_sim + 0x3e78);
  if (local_15c != (void *)0x0) {
    do {
      if ((*(int *)((int)local_15c + 0x210) == 0) ||
         (((local_14c == 0 && ((*(uint *)((int)local_15c + 8) & 1) == 0)) &&
          (((*(uint *)((int)local_15c + 8) & 2) == 0 || ((local_130 & 8) == 0))))))
      goto LAB_00452b4f;
      puVar5 = (uint *)((int)local_15c + 0x218);
      puVar16 = local_12c;
      for (iVar6 = 10; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar16 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar16 = puVar16 + 1;
      }
      uVar13 = *(uint *)((int)local_15c + 4);
      if (((int)uVar13 < 9) || (local_150 = 0x80000, 0xb < (int)uVar13)) {
        local_150 = 0;
      }
      if (0xc < uVar13) goto LAB_00452b4f;
      uVar11 = (uint)local_108;
      switch(uVar13) {
      default:
        iVar9 = *(int *)(cur_sim + 4);
        iVar14 = *(int *)(iVar9 + 0xa4 + uVar11 * 300);
        iVar6 = iVar9 + uVar11 * 300;
        local_154 = iVar6;
        local_144 = local_12c[3];
        local_148 = local_12c[2];
        for (iVar9 = *(int *)(iVar9 + 0xa8 + uVar11 * 300); iVar9 != 0; iVar9 = iVar9 + -1) {
          local_140 = *(int *)(iVar6 + 0xec + iVar14 * 4);
          uVar7 = *(uint *)(iVar6 + 0xac + iVar14 * 4);
          iVar14 = iVar14 + -1;
          if (iVar14 < 0) {
            iVar14 = 0xf;
          }
          if (((local_12c[2] <= uVar7) && (uVar7 <= local_12c[3])) &&
             ((local_150 == 0 || (local_150 == local_140)))) {
            break_hit(local_15c,&local_164,&local_160);
            if (cur_dev == 0) {
              return 0;
            }
            iVar6 = local_154;
            if (cur_sim == 0) {
              return 0;
            }
          }
        }
        if ((uVar13 != 0) && (uVar13 != 9)) goto switchD_004526a4_caseD_2;
        break;
      case 2:
      case 0xb:
switchD_004526a4_caseD_2:
        pvVar2 = local_15c;
        if ((uVar13 == 2) || (uVar13 == 0xb)) {
          local_154 = *(int *)(cur_sim + 4) + uVar11 * 300;
          local_148 = local_12c[2];
          local_144 = local_12c[3];
        }
        iVar14 = local_154;
        iVar9 = *(int *)(local_154 + 0x18);
        for (iVar6 = *(int *)(local_154 + 0x1c); iVar6 != 0; iVar6 = iVar6 + -1) {
          uVar13 = *(uint *)(iVar14 + 0x20 + iVar9 * 4);
          iVar9 = iVar9 + -1;
          if (iVar9 < 0) {
            iVar9 = 0xf;
          }
          if (((local_148 <= uVar13) && (uVar13 <= local_144)) &&
             ((local_150 == 0 || (local_150 == local_140)))) {
            break_hit(pvVar2,&local_164,&local_160);
            if (cur_dev == 0) {
              return 0;
            }
            if (cur_sim == 0) {
              return 0;
            }
          }
        }
        break;
      case 3:
      case 4:
      case 5:
        if (uVar13 == 3) {
          uVar13 = 0x10000;
        }
        else {
          uVar13 = (-(uint)(uVar13 != 5) & 0x10000) + 0x20000;
        }
        if ((*(uint *)(*(int *)(*(int *)(cur_sim + 8) + 4 + (uint)local_108 * 8) +
                      (uint)local_10c * 4) & uVar13) != 0) {
          break_hit(local_15c,&local_164,&local_160);
        }
        goto joined_r0x00452b3c;
      case 6:
        optr = (int)local_15c + 0x10;
        if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
          uVar3 = *(ulong *)(cur_dtype + 0xc);
        }
        else {
          uVar3 = (**(code **)(cur_dtype + 0x4e8))();
        }
        eval_expr(uVar3);
        if (node != (void *)0x0) {
          if ((*(uint *)((int)node + 0x1c) & 0x100) == 0) {
            uVar3 = frac_to_word(uVar3,node);
          }
          else {
            uVar3 = *(ulong *)((int)node + 8);
          }
          if (uVar3 != 0) {
            break_hit(local_15c,&local_164,&local_160);
            if (cur_dev == 0) {
              return 0;
            }
            if (cur_sim == 0) {
              return 0;
            }
          }
          node_free(node);
        }
        break;
      case 7:
        periph_call(*(int *)(cur_dev + 4),(uint)local_108,(uint)local_10c,(long)local_13c);
        switch(uStack_10a) {
        case 0:
          local_158 = (uint)(local_13c[0] != local_12c[2]);
          break;
        case 1:
          local_158 = (uint)((int)local_13c[0] <= (int)local_12c[2]);
          break;
        case 2:
          bVar17 = (int)local_13c[0] < (int)local_12c[2];
          goto LAB_004529d6;
        case 3:
          local_158 = (uint)((int)local_12c[2] <= (int)local_13c[0]);
          break;
        case 4:
          local_158 = (uint)((int)local_12c[2] < (int)local_13c[0]);
          break;
        case 5:
        case 6:
          bVar17 = local_13c[0] == local_12c[2];
LAB_004529d6:
          local_158 = (uint)bVar17;
        }
        if (local_158 != 0) {
LAB_00452a16:
          break_hit(local_15c,&local_164,&local_160);
        }
joined_r0x00452b3c:
        if ((cur_dev == 0) || (cur_sim == 0)) {
          return 0;
        }
        break;
      case 8:
        if (*(uint *)(cur_dev + 0x1c) != local_12c[2]) break;
        goto LAB_00452a16;
      case 0xc:
        if (((*(int *)((int)local_15c + 0x244) != 0) &&
            (iVar6 = cdb_line_index(*(ulong *)(cur_dev + 0x1c)), pvVar2 = local_15c, iVar6 != 0)) &&
           (iVar6 = cdb_pc_in_function(*(int *)((int)local_15c + 0x248),
                                       *(int *)((int)local_15c + 0x24c)), iVar6 != 0)) {
          cdb_set_quiet(1);
          iVar6 = eval_tree(*(void **)((int)pvVar2 + 0x244));
          cdb_set_quiet(0);
          if ((iVar6 == 1) && (cdb_saved_pop(), extraout_EAX != 0)) {
            value = *(void **)(extraout_EAX + 0x10);
          }
          else {
            value = (void *)0x0;
          }
          if (((value != (void *)0x0) &&
              ((((((iVar6 = *(int *)((int)value + 0x20), ((byte)iVar6 & 0x30) == 0x10 ||
                   (iVar6 == 2)) ||
                  ((iVar6 == 3 ||
                   ((((iVar6 == 4 || (iVar6 == 0xb)) || (iVar6 == 10)) ||
                    ((iVar6 == 5 || (iVar6 == 0xc)))))))) || (iVar6 == 0xd)) ||
                ((iVar6 == 0xe || (iVar6 == 0xf)))) || ((iVar6 == 6 || (iVar6 == 7)))))) &&
             (iVar6 = value_is_true(value), iVar6 == 0)) {
            break_hit(pvVar2,&local_164,&local_160);
            goto joined_r0x00452b3c;
          }
        }
      }
LAB_00452b4f:
      local_15c = *(void **)((int)local_15c + 0x240);
    } while (local_15c != (void *)0x0);
    local_15c = (void *)0x0;
    uVar11 = local_14c;
    iVar6 = local_104;
  }
  if (uVar11 != 0) {
    iVar14 = cur_sim;
    for (iVar9 = *(int *)(cur_sim + 0x3e78); iVar9 != 0; iVar9 = *(int *)(iVar9 + 0x240)) {
      if ((2 < *(int *)(iVar9 + 4)) && (*(int *)(iVar9 + 4) < 6)) {
        iVar14 = *(int *)(*(int *)(iVar14 + 8) + 4 + (uint)*(ushort *)(iVar9 + 0x23c) * 8);
        *(uint *)(iVar14 + (uint)*(ushort *)(iVar9 + 0x238) * 4) =
             *(uint *)(iVar14 + (uint)*(ushort *)(iVar9 + 0x238) * 4) & 0xfffcffff;
        iVar14 = cur_sim;
      }
    }
    *(undefined4 *)(iVar14 + 0x18) = 0;
    iVar9 = 0;
    *(undefined4 *)(cur_sim + 0x1c) = 0;
    if (0 < *(int *)(cur_dtype + 0x1c)) {
      puVar4 = (undefined4 *)(*(int *)(cur_sim + 4) + 0x1c);
      do {
        puVar4[0x23] = 0;
        *puVar4 = 0;
        iVar9 = iVar9 + 1;
        puVar4 = puVar4 + 0x4b;
      } while (iVar9 < *(int *)(cur_dtype + 0x1c));
    }
  }
  *(uint *)(cur_dev + 0x44) = *(uint *)(cur_dev + 0x44) & 0xfffffff7;
  switch(iVar6) {
  case 0:
    if ((*(int *)(cur_sim + 0x28) == 0) && (uVar11 != 0)) {
      local_164 = 1;
      local_160 = 1;
    }
    break;
  case 1:
    if (uVar11 != 0) {
      local_160 = 1;
      *(int *)(cur_sim + 0x28) = *(int *)(cur_sim + 0x28) + -1;
      if (*(int *)(cur_sim + 0x28) == 0) {
        local_164 = 1;
      }
      screen_hold();
    }
    break;
  case 2:
    local_160 = 1;
    if (*(int *)(cur_sim + 0x28) != 0) {
      *(int *)(cur_sim + 0x28) = *(int *)(cur_sim + 0x28) + -1;
    }
    if ((uVar11 != 0) && (*(int *)(cur_sim + 0x28) == 0)) {
      local_164 = 1;
    }
    screen_hold();
    sprintf(local_100,s__Trace_cycle_count__lu__004d175c,*(undefined4 *)(cur_sim + 0x28));
    out_text(local_100,1);
    break;
  case 3:
    if (uVar11 == 0) break;
    *(int *)(cur_sim + 0x28) = *(int *)(cur_sim + 0x28) + -1;
    iVar6 = *(int *)(cur_sim + 0x28);
    goto LAB_00452d1a;
  case 4:
    if (*(int *)(cur_sim + 0x28) != 0) {
      *(int *)(cur_sim + 0x28) = *(int *)(cur_sim + 0x28) + -1;
    }
    if (uVar11 == 0) break;
    iVar6 = *(int *)(cur_sim + 0x28);
LAB_00452d1a:
    if (iVar6 == 0) {
      local_164 = 1;
      local_160 = 1;
    }
    break;
  default:
    if (uVar11 != 0) {
      step_advance(&local_160,&local_164);
    }
  }
  if (local_160 != 0) {
    display_refresh(1);
    iVar6 = cur_dev_index;
    if (gui_mode != 0) {
      screen_hold_cnt = 1;
      dsp_free_ext((void *)0xfffffffe);
      iVar9 = 0;
      if (0 < max_devices) {
        do {
          if ((*(int *)(dev_tab + iVar9 * 4) != 0) &&
             ((*(byte *)(*(int *)(dev_tab + iVar9 * 4) + 0x44) & 0x20) == 0)) {
            dev_select(iVar9);
            cdb_free_frames();
          }
          iVar9 = iVar9 + 1;
        } while (iVar9 < max_devices);
      }
      dev_select(iVar6);
    }
    if ((*(int *)(cur_sim + 0x4400) == 1) || (*(int *)(cur_sim + 0x4400) == 2)) {
      win_update(0x7fff);
    }
    if (local_164 == 0) {
      screen_flush();
      iVar6 = 0;
      if (0 < *(int *)(cur_dtype + 0x1c)) {
        puVar4 = (undefined4 *)(*(int *)(cur_sim + 4) + 0x14);
        do {
          puVar4[0x23] = 0;
          *puVar4 = 0;
          iVar6 = iVar6 + 1;
          puVar4 = puVar4 + 0x4b;
        } while (iVar6 < *(int *)(cur_dtype + 0x1c));
      }
      iVar6 = 0;
      if (0 < *(int *)(cur_dtype + 0x14)) {
        iVar14 = 0;
        puVar4 = (undefined4 *)(*(int *)(cur_sim + 8) + 4);
        iVar9 = cur_dtype;
        do {
          iVar10 = 0;
          puVar5 = (uint *)*puVar4;
          if (0 < *(int *)(*(int *)(*(int *)(iVar9 + 0x18) + 0x2c + iVar14) + 0x28)) {
            do {
              iVar10 = iVar10 + 1;
              *puVar5 = *puVar5 & 0xfff3ffff;
              puVar5 = puVar5 + 1;
              iVar9 = cur_dtype;
            } while (iVar10 < *(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + iVar14) + 0x28))
            ;
          }
          iVar6 = iVar6 + 1;
          iVar14 = iVar14 + 0x48;
          puVar4 = puVar4 + 2;
        } while (iVar6 < *(int *)(iVar9 + 0x14));
      }
    }
  }
  if ((local_14c != 0) && (*(int *)(cur_sim + 0x404c) != 0)) {
    host_io_service();
  }
  return local_164;
}


/* ==== break_hit @ 00452f20 ==== */

void __cdecl break_hit(void *bp,int *stop_run,int *refresh)

{
  int va0;
  int iVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  bool bVar5;
  char local_100 [256];
  
  iVar4 = *(int *)(cur_sim + 0x28);
  va0 = *(int *)bp;
  iVar1 = *(int *)((int)bp + 0xc);
  iVar2 = *(int *)(cur_sim + 0x34);
  bVar3 = false;
  bVar5 = *(int *)(cur_sim + 0x2c) == va0;
  switch(iVar1) {
  case 0:
    if (*(int *)(cur_sim + 0x2c) == 0) goto LAB_00453016;
    break;
  case 1:
    *(int *)(cur_sim + 0x15c) = *(int *)(cur_sim + 0x15c) + 1;
    break;
  case 2:
    *(int *)(cur_sim + 0x160) = *(int *)(cur_sim + 0x160) + 1;
    break;
  case 3:
    *(int *)(cur_sim + 0x164) = *(int *)(cur_sim + 0x164) + 1;
    break;
  case 4:
    *(int *)(cur_sim + 0x168) = *(int *)(cur_sim + 0x168) + 1;
    break;
  case 5:
    bVar3 = true;
    break;
  case 6:
    bVar3 = true;
    *refresh = 1;
    break;
  case 7:
    cmd_execute(*(int *)(cur_dev + 4),(char *)((int)bp + 0x110));
    if (cur_dev == 0) {
      return;
    }
    if (cur_sim == 0) {
      return;
    }
LAB_00453016:
    bVar5 = true;
  }
  if (iVar2 == 0) {
    if (!bVar5) goto LAB_0045305e;
    if ((iVar4 != 0) && (iVar4 = iVar4 + -1, *(int *)(cur_sim + 0x28) = iVar4, iVar4 == 0)) {
      *stop_run = 1;
      bVar3 = true;
    }
  }
  if ((bVar5) && (*(int *)(cur_sim + 0x3c) != 0)) {
    *stop_run = 1;
    bVar3 = true;
  }
LAB_0045305e:
  if (bVar3) {
    if ((iVar1 == 4) || (iVar1 == 0)) {
      screen_hold();
    }
    sprintf(local_100,s_Break___d__s_s__s__s_dev__d_pc___004d17ac,va0,
            (&g_bp_type_names)[*(int *)((int)bp + 4)],(int)bp + 0x10,(&g_bp_action_names)[iVar1],
            (int)bp + 0x110,*(undefined4 *)(cur_dev + 4),*(undefined4 *)(cur_dev + 0x1c),
            *(undefined4 *)(cur_dev + 0x20));
    log_echo(local_100,1);
  }
  return;
}


