/* ==== cmd_history_parse @ 0044d140 ==== */

uint cmd_history_parse(void)

{
  int iVar1;
  
  iVar1 = parm_check_too_many(2);
  return -(uint)(iVar1 != 0) & 0x4cc4f0;
}


/* ==== help_list_all @ 0044d160 ==== */

void help_list_all(void)

{
  char *pcVar1;
  undefined *puVar2;
  int iVar3;
  int va1;
  bool bVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int state;
  int *piVar8;
  undefined **ppuVar9;
  int iVar10;
  int local_10c;
  int local_108;
  char local_100 [256];
  
  piVar5 = (int *)command_table;
  iVar6 = 0;
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  screen_hold();
  state = 1;
  out_text(s__________________DSP_SIMULATOR_C_004cd26c,1);
  if (0 < num_commands) {
    do {
      if (state < 0) goto LAB_0044d35a;
      piVar8 = *(int **)(*piVar5 + 0xc);
      iVar10 = *piVar8;
      while ((iVar10 != 0 && (-1 < state))) {
        state = help_page_check(state);
        pcVar1 = (char *)*piVar8;
        piVar8 = piVar8 + 1;
        out_text(pcVar1,1);
        iVar10 = *piVar8;
      }
      iVar6 = iVar6 + 1;
      piVar5 = piVar5 + 1;
    } while (iVar6 < num_commands);
  }
  if (-1 < state) {
    ppuVar9 = &g_help_misc_topics;
    puVar2 = g_help_misc_topics;
    while (puVar2 != (undefined *)0x0) {
      if (state < 0) goto LAB_0044d35a;
      state = help_page_check(state);
      pcVar1 = *ppuVar9;
      ppuVar9 = ppuVar9 + 1;
      out_text(pcVar1,1);
      puVar2 = *ppuVar9;
    }
    if (-1 < state) {
      iVar6 = 0;
      piVar5 = *(int **)(cur_itype + 0x14);
      if (0 < *piVar5) {
        iVar10 = 0;
        do {
          iVar7 = *(int *)(piVar5[1] + iVar10);
          iVar3 = ((int *)(piVar5[1] + iVar10))[2];
          if ((iVar7 != 0) && (iVar3 != 0)) {
            sprintf(local_100,s___s_____s_004cd260,iVar7,iVar3);
            state = help_page_check(state);
            out_text(local_100,1);
          }
          iVar6 = iVar6 + 1;
          iVar10 = iVar10 + 0x14;
          piVar5 = *(int **)(cur_itype + 0x14);
        } while (iVar6 < *piVar5);
      }
      if (-1 < state) {
        iVar6 = *(int *)(cur_dtype + 0x14);
        local_108 = 0;
        if (0 < iVar6) {
          local_10c = 0;
          do {
            piVar5 = *(int **)(cur_itype + 8);
            piVar8 = *(int **)(*(int *)(local_10c + (int)piVar5) + 0x14);
            if (piVar8 != (int *)0x0) {
              bVar4 = false;
              iVar10 = local_108;
              if (0 < local_10c) {
                do {
                  if (*(int **)(*piVar5 + 0x14) == piVar8) {
                    bVar4 = true;
                  }
                  piVar5 = piVar5 + 1;
                  iVar10 = iVar10 + -1;
                } while (iVar10 != 0);
              }
              if ((!bVar4) && (iVar10 = 0, 0 < *piVar8)) {
                iVar7 = 0;
                do {
                  iVar3 = *(int *)(piVar8[1] + iVar7);
                  va1 = ((int *)(piVar8[1] + iVar7))[2];
                  if ((iVar3 != 0) && (va1 != 0)) {
                    sprintf(local_100,s___s_____s_004cd260,iVar3,va1);
                    state = help_page_check(state);
                    out_text(local_100,1);
                  }
                  iVar10 = iVar10 + 1;
                  iVar7 = iVar7 + 0x14;
                } while (iVar10 < *piVar8);
              }
            }
            local_108 = local_108 + 1;
            local_10c = local_10c + 4;
          } while (local_108 < iVar6);
        }
      }
    }
  }
LAB_0044d35a:
  screen_release();
  return;
}


/* ==== help_page_check @ 0044d370 ==== */

int __cdecl help_page_check(int state)

{
  if (abort_flag == 1) {
    return -1;
  }
  return state;
}


/* ==== help_topic @ 0044d390 ==== */

void __cdecl help_topic(char *topic)

{
  byte bVar1;
  int iVar2;
  code *pcVar3;
  char *line;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  byte *pbVar9;
  undefined **ppuVar10;
  bool bVar11;
  int *local_114;
  code *local_110;
  int local_10c;
  int local_108;
  char acStack_100 [256];
  
  piVar8 = (int *)command_table;
  iVar7 = 0;
  if (topic != (char *)0x0) {
    local_110 = (code *)0x0;
    local_114 = (int *)0x0;
    *(undefined4 *)(cur_sim + 0x4400) = 0;
    more_line_count = 0;
    do {
      if (num_commands <= iVar7) break;
      pbVar4 = *(byte **)(*piVar8 + 8);
      pbVar9 = (byte *)topic;
      do {
        bVar1 = *pbVar4;
        bVar11 = bVar1 < *pbVar9;
        if (bVar1 != *pbVar9) {
LAB_0044d402:
          iVar5 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
          goto LAB_0044d407;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar4[1];
        bVar11 = bVar1 < pbVar9[1];
        if (bVar1 != pbVar9[1]) goto LAB_0044d402;
        pbVar4 = pbVar4 + 2;
        pbVar9 = pbVar9 + 2;
      } while (bVar1 != 0);
      iVar5 = 0;
LAB_0044d407:
      if (iVar5 == 0) {
        local_114 = *(int **)(*piVar8 + 0x10);
      }
      iVar7 = iVar7 + 1;
      piVar8 = piVar8 + 1;
    } while (local_114 == (int *)0x0);
    iVar7 = 0;
    if (local_114 == (int *)0x0) {
      iVar5 = 0;
      do {
        if (**(int **)(cur_itype + 0x14) <= iVar7) break;
        iVar2 = (*(int **)(cur_itype + 0x14))[1];
        pbVar4 = *(byte **)(iVar2 + iVar5);
        iVar2 = iVar2 + iVar5;
        pbVar9 = (byte *)topic;
        do {
          bVar1 = *pbVar4;
          bVar11 = bVar1 < *pbVar9;
          if (bVar1 != *pbVar9) {
LAB_0044d46b:
            iVar6 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
            goto LAB_0044d470;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar4[1];
          bVar11 = bVar1 < pbVar9[1];
          if (bVar1 != pbVar9[1]) goto LAB_0044d46b;
          pbVar4 = pbVar4 + 2;
          pbVar9 = pbVar9 + 2;
        } while (bVar1 != 0);
        iVar6 = 0;
LAB_0044d470:
        if (iVar6 == 0) {
          pcVar3 = *(code **)(iVar2 + 0xc);
          if (pcVar3 == (code *)0x0) {
            local_114 = *(int **)(iVar2 + 4);
          }
          else {
            local_114 = (int *)(*pcVar3)();
          }
          local_110 = *(code **)(*(int *)(*(int *)(cur_itype + 0x14) + 4) + 0x10 + iVar5);
        }
        iVar7 = iVar7 + 1;
        iVar5 = iVar5 + 0x14;
      } while (local_114 == (int *)0x0);
    }
    local_108 = 0;
    iVar7 = *(int *)(cur_dtype + 0x14);
    if (0 < iVar7) {
      do {
        iVar5 = 0;
        piVar8 = *(int **)(*(int *)(*(int *)(cur_itype + 8) + local_108 * 4) + 0x14);
        if (piVar8 != (int *)0x0) {
          for (local_10c = 0; (local_114 == (int *)0x0 && (local_10c < *piVar8));
              local_10c = local_10c + 1) {
            pbVar4 = *(byte **)(iVar5 + piVar8[1]);
            iVar2 = iVar5 + piVar8[1];
            pbVar9 = (byte *)topic;
            do {
              bVar1 = *pbVar4;
              bVar11 = bVar1 < *pbVar9;
              if (bVar1 != *pbVar9) {
LAB_0044d526:
                iVar6 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
                goto LAB_0044d52b;
              }
              if (bVar1 == 0) break;
              bVar1 = pbVar4[1];
              bVar11 = bVar1 < pbVar9[1];
              if (bVar1 != pbVar9[1]) goto LAB_0044d526;
              pbVar4 = pbVar4 + 2;
              pbVar9 = pbVar9 + 2;
            } while (bVar1 != 0);
            iVar6 = 0;
LAB_0044d52b:
            if (iVar6 == 0) {
              pcVar3 = *(code **)(iVar2 + 0xc);
              if (pcVar3 == (code *)0x0) {
                local_114 = *(int **)(iVar2 + 4);
              }
              else {
                local_114 = (int *)(*pcVar3)();
              }
              local_110 = *(code **)(iVar5 + 0x10 + piVar8[1]);
            }
            iVar5 = iVar5 + 0x14;
          }
        }
        local_108 = local_108 + 1;
      } while (local_108 < iVar7);
    }
    if (local_114 == (int *)0x0) {
      ppuVar10 = &PTR_PTR_004cc814;
      do {
        if ((undefined **)0x4cc863 < ppuVar10) break;
        pbVar4 = ppuVar10[-1];
        pbVar9 = (byte *)topic;
        do {
          bVar1 = *pbVar4;
          bVar11 = bVar1 < *pbVar9;
          if (bVar1 != *pbVar9) {
LAB_0044d5c0:
            iVar7 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
            goto LAB_0044d5c5;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar4[1];
          bVar11 = bVar1 < pbVar9[1];
          if (bVar1 != pbVar9[1]) goto LAB_0044d5c0;
          pbVar4 = pbVar4 + 2;
          pbVar9 = pbVar9 + 2;
        } while (bVar1 != 0);
        iVar7 = 0;
LAB_0044d5c5:
        if (iVar7 == 0) {
          local_114 = (int *)*ppuVar10;
        }
        ppuVar10 = ppuVar10 + 5;
      } while (local_114 == (int *)0x0);
      if (local_114 == (int *)0x0) {
        sprintf(acStack_100,s__Help_topic_not_found__004cd2a8);
        out_text(acStack_100,1);
        return;
      }
    }
    screen_hold();
    iVar5 = 0;
    iVar7 = *local_114;
    piVar8 = local_114;
    while ((iVar7 != 0 && (-1 < iVar5))) {
      iVar5 = help_page_check(iVar5);
      line = (char *)*piVar8;
      piVar8 = piVar8 + 1;
      out_text(line,1);
      iVar7 = *piVar8;
    }
    if (local_110 != (code *)0x0) {
      (*local_110)(local_114);
    }
    screen_release();
  }
  return;
}


