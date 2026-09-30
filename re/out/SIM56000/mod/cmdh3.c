/* ==== cmd_break_h0 @ 00453100 ==== */

void cmd_break_h0(void)

{
  char cVar1;
  int *extraout_EAX;
  int extraout_EAX_00;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  bool bVar10;
  int iStack_38;
  int iStack_34;
  int *piStack_30;
  int *piStack_2c;
  int aiStack_28 [8];
  uint uStack_8;
  uint uStack_4;
  
  dsp_alloc(0x250,1);
  uVar4 = DAT_004a96e8;
  if (extraout_EAX != (int *)0x0) {
    bVar10 = DAT_004a93eb != 'A';
    extraout_EAX[0x84] = 1;
    *(undefined1 *)(extraout_EAX + 0x44) = 0;
    extraout_EAX[3] = bVar10 - 1 & uVar4;
    extraout_EAX[1] = 6;
    extraout_EAX[0x91] = 0;
    extraout_EAX[0x92] = -1;
    extraout_EAX[0x93] = -1;
    iStack_38 = 0;
    iStack_34 = 0;
    iVar7 = 2;
    if (DAT_004a93ea != 'e') {
      piStack_30 = &DAT_004a9470;
      piStack_2c = (int *)0x4a96b8;
      cVar1 = DAT_004a93ea;
      do {
        piVar6 = piStack_2c;
        piVar2 = aiStack_28;
        for (iVar3 = 10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *piVar2 = *piVar6;
          piVar6 = piVar6 + 1;
          piVar2 = piVar2 + 1;
        }
        switch(cVar1) {
        case '#':
          iStack_34 = aiStack_28[2];
          break;
        case 'A':
          extraout_EAX[3] = aiStack_28[2];
          break;
        case 'C':
          extraout_EAX[1] = 0xc;
          piVar6 = aiStack_28;
          piVar2 = extraout_EAX + 0x86;
          for (iVar3 = 10; iVar3 != 0; iVar3 = iVar3 + -1) {
            *piVar2 = *piVar6;
            piVar6 = piVar6 + 1;
            piVar2 = piVar2 + 1;
          }
          parse_c_expression(&g_cmdline + *piStack_30);
          extraout_EAX[0x91] = extraout_EAX_00;
          extraout_EAX[0x92] = cdb_lookup_cache_sym;
          extraout_EAX[0x93] = cdb_lookup_cache_depth;
          iStack_38 = iVar7;
          break;
        case 'E':
          piVar6 = piStack_2c;
          piVar2 = extraout_EAX + 0x86;
          for (iVar3 = 10; iVar3 != 0; iVar3 = iVar3 + -1) {
            *piVar2 = *piVar6;
            piVar6 = piVar6 + 1;
            piVar2 = piVar2 + 1;
          }
          extraout_EAX[1] = 8;
          iStack_38 = iVar7;
          break;
        case 'F':
        case 'I':
          extraout_EAX[1] = 6;
          iStack_38 = iVar7;
          break;
        case 'K':
          uVar4 = 0xffffffff;
          pcVar9 = (char *)(parm_cmdline + *piStack_30);
          do {
            pcVar8 = pcVar9;
            if (uVar4 == 0) break;
            uVar4 = uVar4 - 1;
            pcVar8 = pcVar9 + 1;
            cVar1 = *pcVar9;
            pcVar9 = pcVar8;
          } while (cVar1 != '\0');
          uVar4 = ~uVar4;
          piVar6 = (int *)(pcVar8 + -uVar4);
          piVar2 = extraout_EAX + 0x44;
          for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *piVar2 = *piVar6;
            piVar6 = piVar6 + 1;
            piVar2 = piVar2 + 1;
          }
          for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
            *(char *)piVar2 = (char)*piVar6;
            piVar6 = (int *)((int)piVar6 + 1);
            piVar2 = (int *)((int)piVar2 + 1);
          }
          break;
        case 'M':
          extraout_EAX[1] = aiStack_28[2];
          break;
        case 'N':
          extraout_EAX[1] = aiStack_28[2] + 9;
          break;
        case 'P':
        case 'X':
          goto switchD_004531b7_caseD_50;
        case 'Y':
          extraout_EAX[1] = 7;
          goto switchD_004531b7_caseD_50;
        case 'g':
          extraout_EAX[1] = extraout_EAX[1] + 3;
          piVar6 = aiStack_28;
          piVar2 = extraout_EAX + 0x86;
          for (iVar3 = 10; iVar3 != 0; iVar3 = iVar3 + -1) {
            *piVar2 = *piVar6;
            piVar6 = piVar6 + 1;
            piVar2 = piVar2 + 1;
          }
          iVar3 = *(int *)(*(int *)(cur_sim + 8) + 4 + (uStack_4 & 0xffff) * 8);
          *(uint *)(iVar3 + (uStack_8 & 0xffff) * 4) =
               *(uint *)(iVar3 + (uStack_8 & 0xffff) * 4) & 0xfffcffff;
          iStack_38 = iVar7;
          break;
        case 'p':
          aiStack_28[3] = aiStack_28[2];
switchD_004531b7_caseD_50:
          piVar6 = aiStack_28;
          piVar2 = extraout_EAX + 0x86;
          for (iVar3 = 10; iStack_38 = iVar7, iVar3 != 0; iVar3 = iVar3 + -1) {
            *piVar2 = *piVar6;
            piVar6 = piVar6 + 1;
            piVar2 = piVar2 + 1;
          }
        }
        cVar1 = (&DAT_004a93e9)[iVar7];
        iVar7 = iVar7 + 1;
        piStack_2c = piStack_2c + 10;
        piStack_30 = piStack_30 + 1;
      } while (cVar1 != 'e');
    }
    if (iStack_38 == 0) {
      pcVar9 = &DAT_004d04dc;
    }
    else {
      pcVar9 = &g_cmdline + (&g_tok_start)[iStack_38];
    }
    uVar4 = 0xffffffff;
    do {
      pcVar8 = pcVar9;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar8 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar8;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    piVar6 = (int *)(pcVar8 + -uVar4);
    piVar2 = extraout_EAX + 4;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *piVar2 = *piVar6;
      piVar6 = piVar6 + 1;
      piVar2 = piVar2 + 1;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(char *)piVar2 = (char)*piVar6;
      piVar6 = (int *)((int)piVar6 + 1);
      piVar2 = (int *)((int)piVar2 + 1);
    }
    if (iStack_38 == 0) {
      pcVar9 = &DAT_004d04dc;
    }
    else {
      pcVar9 = &cmd_tokbuf + (&g_tok_start)[iStack_38];
    }
    iVar7 = str_find_word(pcVar9,&DAT_004b722c);
    extraout_EAX[2] = (uint)(iVar7 != -1);
    iVar7 = str_find_word(pcVar9,&DAT_004b294c);
    extraout_EAX[2] = extraout_EAX[2] | -(uint)(iVar7 != -1) & 2;
    if (iStack_34 == 0) {
      iVar7 = *(int *)(cur_sim + 0x3c38);
      piVar6 = (int *)(cur_sim + 0x3c38);
      for (piVar2 = *(int **)(cur_sim + 0x3e78);
          (iStack_34 = iVar7 + 1, piVar2 != (int *)0x0 && (iVar7 = *piVar2, iVar7 <= iStack_34));
          piVar2 = (int *)piVar2[0x90]) {
        piVar6 = piVar2;
      }
    }
    else {
      piVar6 = (int *)(cur_sim + 0x3c38);
      for (piVar2 = *(int **)(cur_sim + 0x3e78); (piVar2 != (int *)0x0 && (*piVar2 <= iStack_34));
          piVar2 = (int *)piVar2[0x90]) {
        piVar6 = piVar2;
      }
    }
    *extraout_EAX = iStack_34;
    extraout_EAX[0x90] = (int)piVar2;
    piVar6[0x90] = (int)extraout_EAX;
  }
  return;
}


/* ==== cmd_break_h1 @ 004534f0 ==== */

void cmd_break_h1(int param_1)

{
  char cVar1;
  int extraout_EAX;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  char *pcVar10;
  char *pcVar11;
  int *piStack_30;
  int *piStack_2c;
  int aiStack_28 [8];
  uint uStack_8;
  uint uStack_4;
  
  piVar7 = *(int **)(cur_sim + 0x3e78);
  if (piVar7 != (int *)0x0) {
    do {
      if (*piVar7 == DAT_004a96c0) break;
      piVar7 = (int *)piVar7[0x90];
    } while (piVar7 != (int *)0x0);
    if (piVar7 != (int *)0x0) {
      param_1 = 0;
      iVar6 = 3;
      iVar2 = 0;
      if (DAT_004a93eb != 'e') {
        piStack_30 = &DAT_004a9474;
        piStack_2c = (int *)&DAT_004a96e0;
        cVar1 = DAT_004a93eb;
        do {
          piVar8 = piStack_2c;
          piVar9 = aiStack_28;
          for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *piVar9 = *piVar8;
            piVar8 = piVar8 + 1;
            piVar9 = piVar9 + 1;
          }
          switch(cVar1) {
          case 'A':
            piVar7[3] = aiStack_28[2];
            if (*(&g_bp_action_names)[aiStack_28[2]] != 'x') {
              *(undefined1 *)(piVar7 + 0x44) = 0;
            }
            break;
          case 'C':
            if (piVar7[1] == 0xc) {
              cdb_free_expr((void *)piVar7[0x91]);
            }
            piVar7[1] = 0xc;
            piVar8 = aiStack_28;
            piVar9 = piVar7 + 0x86;
            for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
              *piVar9 = *piVar8;
              piVar8 = piVar8 + 1;
              piVar9 = piVar9 + 1;
            }
            parse_c_expression(&g_cmdline + *piStack_30);
            piVar7[0x91] = extraout_EAX;
            piVar7[0x92] = cdb_lookup_cache_sym;
            piVar7[0x93] = cdb_lookup_cache_depth;
            param_1 = iVar6;
            break;
          case 'E':
            piVar8 = piStack_2c;
            piVar9 = piVar7 + 0x86;
            for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
              *piVar9 = *piVar8;
              piVar8 = piVar8 + 1;
              piVar9 = piVar9 + 1;
            }
            piVar7[1] = 8;
            param_1 = iVar6;
            break;
          case 'F':
          case 'I':
            piVar7[1] = 6;
            param_1 = iVar6;
            break;
          case 'K':
            strncpy((char *)(piVar7 + 0x44),(char *)(parm_cmdline + *piStack_30),0xff);
            break;
          case 'M':
            piVar7[1] = aiStack_28[2];
            break;
          case 'N':
            piVar7[1] = aiStack_28[2] + 9;
            break;
          case 'P':
          case 'X':
            goto switchD_00453574_caseD_50;
          case 'Y':
            piVar7[1] = 7;
            goto switchD_00453574_caseD_50;
          case 'g':
            iVar2 = piVar7[1];
            piVar8 = aiStack_28;
            piVar9 = piVar7 + 0x86;
            for (iVar3 = 10; iVar3 != 0; iVar3 = iVar3 + -1) {
              *piVar9 = *piVar8;
              piVar8 = piVar8 + 1;
              piVar9 = piVar9 + 1;
            }
            piVar7[1] = iVar2 + 3;
            iVar2 = *(int *)(*(int *)(cur_sim + 8) + 4 + (uStack_4 & 0xffff) * 8);
            *(uint *)(iVar2 + (uStack_8 & 0xffff) * 4) =
                 *(uint *)(iVar2 + (uStack_8 & 0xffff) * 4) & 0xfffcffff;
            param_1 = iVar6;
            break;
          case 'p':
            aiStack_28[3] = aiStack_28[2];
switchD_00453574_caseD_50:
            piVar8 = aiStack_28;
            piVar9 = piVar7 + 0x86;
            for (iVar2 = 10; param_1 = iVar6, iVar2 != 0; iVar2 = iVar2 + -1) {
              *piVar9 = *piVar8;
              piVar8 = piVar8 + 1;
              piVar9 = piVar9 + 1;
            }
          }
          cVar1 = (&DAT_004a93e9)[iVar6];
          iVar6 = iVar6 + 1;
          piStack_2c = piStack_2c + 10;
          piStack_30 = piStack_30 + 1;
          iVar2 = param_1;
        } while (cVar1 != 'e');
      }
      if (iVar2 == 0) {
        return;
      }
      uVar4 = 0xffffffff;
      pcVar10 = &g_cmdline + (&g_tok_start)[iVar2];
      do {
        pcVar11 = pcVar10;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar11 = pcVar10 + 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar11;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      piVar8 = (int *)(pcVar11 + -uVar4);
      piVar9 = piVar7 + 4;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *piVar9 = *piVar8;
        piVar8 = piVar8 + 1;
        piVar9 = piVar9 + 1;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(char *)piVar9 = (char)*piVar8;
        piVar8 = (int *)((int)piVar8 + 1);
        piVar9 = (int *)((int)piVar9 + 1);
      }
      iVar2 = (&g_tok_start)[iVar2];
      iVar6 = str_find_word(&cmd_tokbuf + iVar2,&DAT_004b722c);
      piVar7[2] = (uint)(iVar6 != -1);
      iVar2 = str_find_word(&cmd_tokbuf + iVar2,&DAT_004b294c);
      piVar7[2] = piVar7[2] | -(uint)(iVar2 != -1) & 2;
      return;
    }
  }
  if (DAT_004a93eb != 'A') {
    cmd_break_h0(param_1);
  }
  return;
}


/* ==== cmd_break_h2 @ 00453820 ==== */

void cmd_break_h2(void)

{
  int iVar1;
  int iVar2;
  int *p;
  int *piVar3;
  int *piVar4;
  char *pcStack_8;
  
  if (DAT_004a93ea == 'j') {
    break_list_free();
    return;
  }
  if (DAT_004a93ea == '#') {
    pcStack_8 = &DAT_004a93ea;
    piVar4 = &g_io_id_arg;
    do {
      iVar1 = *piVar4;
      iVar2 = piVar4[-1];
      p = (int *)(cur_sim + 0x3c38);
      while (piVar3 = p, piVar3 != (int *)0x0) {
        p = (int *)piVar3[0x90];
        if (((p != (int *)0x0) && (iVar2 <= *p)) && (*p <= iVar1)) {
          piVar3[0x90] = p[0x90];
          if (p[1] == 0xc) {
            cdb_free_expr((void *)p[0x91]);
          }
          dsp_free(p);
          p = piVar3;
        }
      }
      piVar4 = piVar4 + 10;
      pcStack_8 = pcStack_8 + 1;
    } while (*pcStack_8 == '#');
  }
  return;
}


/* ==== cmd_break_h4 @ 004538d0 ==== */

void cmd_break_h4(void)

{
  char *pcVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  undefined1 *puVar6;
  
  if (DAT_004a93ea == 'j') {
    iVar4 = *(int *)(cur_sim + 0x3e78);
    if (iVar4 != 0) {
      do {
        *(undefined4 *)(iVar4 + 0x210) = 1;
        iVar4 = *(int *)(iVar4 + 0x240);
      } while (iVar4 != 0);
      return;
    }
  }
  else if (DAT_004a93ea == '#') {
    puVar6 = &DAT_004a93ea;
    piVar5 = &g_io_id_arg;
    do {
      iVar4 = piVar5[-1];
      iVar2 = *piVar5;
      for (piVar3 = *(int **)(cur_sim + 0x3e78); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[0x90])
      {
        if ((iVar4 <= *piVar3) && (*piVar3 <= iVar2)) {
          piVar3[0x84] = 1;
        }
      }
      pcVar1 = puVar6 + 1;
      piVar5 = piVar5 + 10;
      puVar6 = puVar6 + 1;
    } while (*pcVar1 == '#');
  }
  return;
}


/* ==== cmd_break_h5 @ 00453960 ==== */

void cmd_break_h5(void)

{
  char *pcVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  undefined1 *puVar6;
  
  if (DAT_004a93ea == 'j') {
    iVar4 = *(int *)(cur_sim + 0x3e78);
    if (iVar4 != 0) {
      do {
        *(undefined4 *)(iVar4 + 0x210) = 0;
        iVar4 = *(int *)(iVar4 + 0x240);
      } while (iVar4 != 0);
      return;
    }
  }
  else if (DAT_004a93ea == '#') {
    puVar6 = &DAT_004a93ea;
    piVar5 = &g_io_id_arg;
    do {
      iVar4 = piVar5[-1];
      iVar2 = *piVar5;
      for (piVar3 = *(int **)(cur_sim + 0x3e78); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[0x90])
      {
        if ((iVar4 <= *piVar3) && (*piVar3 <= iVar2)) {
          piVar3[0x84] = 0;
        }
      }
      pcVar1 = puVar6 + 1;
      piVar5 = piVar5 + 10;
      puVar6 = puVar6 + 1;
    } while (*pcVar1 == '#');
  }
  return;
}


/* ==== cmd_break_h3 @ 004539f0 ==== */

void cmd_break_h3(void)

{
  char *pcVar1;
  int *piVar2;
  undefined4 *puVar3;
  char acStack_100 [256];
  
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  if (DAT_004a93ea == 'e') {
    puVar3 = *(undefined4 **)(cur_sim + 0x3e78);
    if (puVar3 != (undefined4 *)0x0) {
      do {
        pcVar1 = &empty_str;
        if (puVar3[0x84] == 0) {
          pcVar1 = s_disabled_004cd4f0;
        }
        sprintf(acStack_100,s_Break___d__s_s__s_s_s_004d17ec,*puVar3,(&PTR_DAT_004d04e0)[puVar3[1]],
                puVar3 + 4,(&g_bp_action_names)[puVar3[3]],puVar3 + 0x44,pcVar1);
        log_echo(acStack_100,1);
        puVar3 = (undefined4 *)puVar3[0x90];
      } while (puVar3 != (undefined4 *)0x0);
      return;
    }
  }
  else {
    piVar2 = *(int **)(cur_sim + 0x3e78);
    if (piVar2 != (int *)0x0) {
      while (*piVar2 != DAT_004a96c0) {
        piVar2 = (int *)piVar2[0x90];
        if (piVar2 == (int *)0x0) {
          return;
        }
      }
      pcVar1 = &empty_str;
      if (piVar2[0x84] == 0) {
        pcVar1 = s_disabled_004cd4f0;
      }
      sprintf(acStack_100,s__d___s_s__s_s_s_004d17dc,*piVar2,(&PTR_DAT_004d04e0)[piVar2[1]],
              piVar2 + 4,(&g_bp_action_names)[piVar2[3]],piVar2 + 0x44,pcVar1);
      log_echo(acStack_100,1);
    }
  }
  return;
}


/* ==== cmd_break_parse @ 00453b30 ==== */

int cmd_break_parse(void)

{
  undefined uVar1;
  int iVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = -1;
  iVar2 = parm_check_too_many(2);
  if (iVar2 != 0) {
    iVar3 = 3;
    goto LAB_00453e6d;
  }
  iVar2 = parm_break_number(2);
  if (iVar2 != 0) {
    iVar2 = parm_check_too_many(3);
    if (iVar2 != 0) {
      iVar3 = 3;
      goto LAB_00453e6d;
    }
    iVar2 = parm_match_condition(3);
    if (iVar2 == 0) {
      iVar2 = parm_brace_block(3);
      if (iVar2 == 0) {
        iVar2 = parm_keyword1(3,&DAT_004c6aec);
        if (iVar2 != 0) {
          iVar2 = parm_check_too_many(4);
LAB_00453e11:
          if (iVar2 != 0) {
            iVar3 = 2;
          }
          goto LAB_00453e6d;
        }
        iVar2 = parm_keyword1(3,&DAT_004c8fec);
        if (iVar2 != 0) {
          iVar2 = parm_check_too_many(4);
LAB_00453e39:
          if (iVar2 != 0) {
            iVar3 = 4;
          }
          goto LAB_00453e6d;
        }
        iVar2 = parm_keyword1(3,&DAT_004c6ab4);
        if (iVar2 != 0) {
          iVar2 = parm_check_too_many(4);
          goto joined_r0x00453c33;
        }
        iVar2 = parm_kw_M_rw(3);
        if (iVar2 == 0) {
          iVar2 = parm_kw_N_drw(3);
          if (iVar2 != 0) {
            iVar2 = parm_address_spec(4);
            if (iVar2 == 0) goto LAB_00453e6d;
            goto LAB_00453c9e;
          }
          uVar4 = 3;
        }
        else {
          iVar2 = parm_register(4);
          if (iVar2 == 0) {
            iVar2 = parm_address_spec(4);
            if (iVar2 == 0) goto LAB_00453e6d;
            iVar2 = parm_check_too_many(5);
            if (iVar2 != 0) goto LAB_00453cc2;
            uVar4 = 5;
          }
          else {
LAB_00453c9e:
            iVar2 = parm_check_too_many(5);
            if (iVar2 != 0) goto LAB_00453cc2;
            uVar4 = 5;
          }
        }
override_prt_453cb2_4b34f2a8:
        uVar1 = cmd_break_parse_sub_453e80(uVar4);
        if (CONCAT31(extraout_var,uVar1) == 0) goto LAB_00453e6d;
      }
      else {
        iVar2 = parm_bp_expr(3);
        if (iVar2 == 0) goto LAB_00453e6d;
        iVar2 = parm_check_too_many(4);
        if (iVar2 == 0) {
          uVar4 = 4;
          goto override_prt_453cb2_4b34f2a8;
        }
      }
    }
    else {
      iVar2 = parm_check_too_many(4);
      if (iVar2 == 0) {
        uVar4 = 4;
        goto override_prt_453cb2_4b34f2a8;
      }
    }
LAB_00453cc2:
    iVar3 = 1;
    goto LAB_00453e6d;
  }
  iVar2 = parm_match_condition(2);
  if (iVar2 == 0) {
    iVar2 = parm_brace_block(2);
    if (iVar2 != 0) {
      iVar2 = parm_bp_expr(2);
      if (iVar2 == 0) goto LAB_00453e6d;
      iVar2 = parm_check_too_many(3);
      if (iVar2 == 0) {
        uVar4 = 3;
        goto override_prt_453d73_4b34f2a8;
      }
      goto LAB_00453d83;
    }
    iVar2 = parm_kw_M_rw(2);
    if (iVar2 == 0) {
      iVar2 = parm_kw_N_drw(2);
      if (iVar2 == 0) {
        iVar2 = parm_check_too_many(3);
        if (iVar2 == 0) {
          iVar2 = parm_check_too_many(4);
          if (iVar2 == 0) goto LAB_00453e6d;
          iVar2 = parm_keyword1(3,&DAT_004c6aec);
          if (iVar2 != 0) {
            iVar2 = parm_break_number_list(2);
            goto LAB_00453e11;
          }
          iVar2 = parm_keyword1(3,&DAT_004c8fec);
          if (iVar2 != 0) {
            iVar2 = parm_break_number_list(2);
            goto LAB_00453e39;
          }
          iVar2 = parm_keyword1(3,&DAT_004c6ab4);
          if (iVar2 == 0) goto LAB_00453e6d;
          iVar2 = parm_break_number_list(2);
        }
        else {
          iVar2 = parm_keyword1(2,&DAT_004c6aec);
          if (iVar2 != 0) {
            iVar3 = 2;
            goto LAB_00453e6d;
          }
          iVar2 = parm_keyword1(2,&DAT_004c8fec);
          if (iVar2 != 0) {
            iVar3 = 4;
            goto LAB_00453e6d;
          }
          iVar2 = parm_keyword1(2,&DAT_004c6ab4);
        }
joined_r0x00453c33:
        if (iVar2 != 0) {
          iVar3 = 5;
        }
        goto LAB_00453e6d;
      }
LAB_00453d53:
      iVar2 = parm_address_spec(3);
      if (iVar2 == 0) goto LAB_00453e6d;
    }
    else {
      iVar2 = parm_register(3);
      if (iVar2 == 0) goto LAB_00453d53;
    }
    iVar2 = parm_check_too_many(4);
    if (iVar2 == 0) {
      uVar4 = 4;
      goto override_prt_453d73_4b34f2a8;
    }
  }
  else {
    iVar2 = parm_check_too_many(3);
    if (iVar2 == 0) {
      uVar4 = 3;
override_prt_453d73_4b34f2a8:
      uVar1 = cmd_break_parse_sub_453e80(uVar4);
      if (CONCAT31(extraout_var_00,uVar1) == 0) goto LAB_00453e6d;
    }
  }
LAB_00453d83:
  iVar3 = 0;
LAB_00453e6d:
  if (iVar3 == -1) {
    return 0;
  }
  return iVar3 * 8 + 0x4d06d8;
}


/* ==== cmd_break_parse_sub_453e80 @ 00453e80 ==== */

int cmd_break_parse_sub_453e80(int param_1)

{
  int iVar1;
  
  iVar1 = parm_keyword1(param_1,&DAT_004a86b0);
  if (iVar1 == 0) {
    iVar1 = parm_kw_A(param_1);
    if ((iVar1 != 0) && (iVar1 = parm_check_too_many(param_1 + 1), iVar1 != 0)) {
      return 1;
    }
  }
  else {
    iVar1 = parm_kw_A(param_1);
    if ((iVar1 == 0) || (iVar1 = parm_need_more(param_1 + 1), iVar1 == 0)) {
      iVar1 = 0;
    }
    else {
      iVar1 = 1;
    }
    if (iVar1 != 0) {
      (&DAT_004a93ea)[param_1] = 0x65;
      return iVar1;
    }
  }
  return 0;
}


/* ==== cmd_asm_h0 @ 00453ef0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void cmd_asm_h0(void)

{
  char cVar1;
  byte bVar2;
  undefined4 *puVar3;
  code *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  int iVar9;
  uint uVar10;
  uint arg;
  uint uVar11;
  byte *pbVar12;
  char *pcVar13;
  bool bVar14;
  ulong uStack_368;
  int iStack_364;
  uint uStack_35c;
  int iStack_358;
  char acStack_350 [256];
  undefined1 auStack_250 [80];
  char acStack_200 [8];
  byte abStack_1f8 [248];
  char acStack_100 [256];
  
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  arg = (uint)(DAT_004a93ea == 'j');
  if ((&DAT_004a93ea)[arg] == 'e') {
    uStack_368 = 0;
    uVar11 = *(uint *)(cur_dev + 0x1c);
    uStack_35c = *(uint *)(*(int *)(cur_dtype + 0x20) + 0x20);
  }
  else {
    iVar5 = (arg + 2) * 0x28;
    uVar11 = *(uint *)(&g_tok_val + iVar5);
    iVar5 = *(int *)(cur_dtype + 0x20) + (uint)*(ushort *)(&DAT_004a968c + iVar5) * 0x2c;
    uStack_368 = *(ulong *)(iVar5 + 4);
    uStack_35c = *(uint *)(iVar5 + 0x20);
  }
  puVar3 = *(undefined4 **)(cur_dtype + 0x28);
  uVar11 = uVar11 & uStack_35c;
  if (puVar3[9] == 0) {
    if ((code *)puVar3[5] == (code *)0x0) {
      iVar5 = (*(code *)*puVar3)(uStack_368,uVar11,auStack_250);
    }
    else {
      iVar5 = (*(code *)puVar3[5])(uStack_368,uVar11,auStack_250,arg);
    }
  }
  else {
    iVar5 = (*(code *)puVar3[5])(uStack_368,uVar11,auStack_250,arg);
    (**(code **)(*(int *)(cur_dtype + 0x28) + 0x24))(uStack_368,uVar11,auStack_250,arg);
  }
  if (iVar5 == 0) {
    iVar5 = 1;
  }
  *(uint *)(cur_sim + 0xc) = uVar11;
  help_lines_cur = 0x4d1888;
  prompt_help_cycle(-1);
  iStack_364 = disasm_line(uStack_368,uVar11,acStack_350,arg);
  iVar6 = str_find_char(acStack_350,0x3d);
  iStack_358 = str_find_char(acStack_350,0x20);
  out_text(acStack_350,1);
  uVar10 = 0xffffffff;
  pcVar13 = acStack_350;
  do {
    if (uVar10 == 0) break;
    uVar10 = uVar10 - 1;
    cVar1 = *pcVar13;
    pcVar13 = pcVar13 + 1;
  } while (cVar1 != '\0');
  if (screen_cols - 1U < ~uVar10 - 1) {
    out_text(acStack_350 + screen_cols,1);
  }
  do {
    sprintf(acStack_200,s_Change___s_004d1ca0,acStack_350 + iVar6 + 2);
LAB_0045409b:
    iVar7 = help_line_edit(acStack_200,8,8,s_assemble_004d18c0);
    if (iVar7 == 0xd) {
      pbVar12 = abStack_1f8;
      pbVar8 = (byte *)(acStack_350 + iVar6 + 2);
      do {
        bVar2 = *pbVar8;
        bVar14 = bVar2 < *pbVar12;
        if (bVar2 != *pbVar12) {
LAB_004540fc:
          iVar9 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
          goto LAB_00454101;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar8[1];
        bVar14 = bVar2 < pbVar12[1];
        if (bVar2 != pbVar12[1]) goto LAB_004540fc;
        pbVar8 = pbVar8 + 2;
        pbVar12 = pbVar12 + 2;
      } while (bVar2 != 0);
      iVar9 = 0;
LAB_00454101:
      if (iVar9 != 0) {
        (**(code **)(cur_itype + 0xc))(abStack_1f8,uVar11);
        iVar9 = asm_result;
        if (asm_result < 0) break;
        if (_DAT_005059f4 == 0) {
          if (0 < asm_result) {
            pcVar4 = *(code **)(*(int *)(cur_dtype + 0x28) + 0x18);
            if (pcVar4 == (code *)0x0) {
              iVar5 = (**(code **)(*(int *)(cur_dtype + 0x28) + 4))(uStack_368,uVar11,&DAT_005059e4)
              ;
            }
            else {
              iVar5 = (*pcVar4)(uStack_368,uVar11,&DAT_005059e4,arg);
            }
            if (iVar5 == 0) {
              iVar5 = 1;
            }
            iStack_364 = 1;
          }
          if (1 < iVar9) {
            pcVar4 = *(code **)(*(int *)(cur_dtype + 0x28) + 0x18);
            if (pcVar4 == (code *)0x0) {
              iVar5 = (**(code **)(*(int *)(cur_dtype + 0x28) + 4))
                                (uStack_368,iVar5 + uVar11,&DAT_005059e8);
            }
            else {
              iVar5 = (*pcVar4)(uStack_368,iVar5 + uVar11,&DAT_005059e8,arg);
            }
            if (iVar5 == 0) {
              iVar5 = 1;
            }
            iStack_364 = 2;
          }
          if (2 < iVar9) {
            pcVar4 = *(code **)(*(int *)(cur_dtype + 0x28) + 0x18);
            if (pcVar4 == (code *)0x0) {
              iVar5 = (**(code **)(*(int *)(cur_dtype + 0x28) + 4))
                                (uStack_368,uVar11 + iVar5 * 2,&DAT_005059ec);
            }
            else {
              iVar5 = (*pcVar4)(uStack_368,uVar11 + iVar5 * 2,&DAT_005059ec,arg);
            }
            if (iVar5 == 0) {
              iVar5 = 1;
            }
            iStack_364 = 3;
          }
          if (iVar9 == 0) {
            iStack_364 = iVar9;
          }
        }
        else {
          iVar6 = 0;
          iStack_364 = 0;
          if (0 < _DAT_005059f4) {
            iVar9 = 0x5059f8;
            do {
              pcVar4 = *(code **)(*(int *)(cur_dtype + 0x28) + 0x18);
              if (pcVar4 == (code *)0x0) {
                iVar5 = (**(code **)(*(int *)(cur_dtype + 0x28) + 4))(uStack_368,uVar11,iVar9);
              }
              else {
                iVar5 = (*pcVar4)(uStack_368,uVar11,iVar9,arg);
              }
              if (iVar5 == 0) {
                iVar5 = 1;
              }
              uVar11 = uVar11 + iVar5;
              iVar6 = iVar6 + 1;
              iVar9 = iVar9 + 4;
            } while (iVar6 < _DAT_005059f4);
          }
        }
        acStack_350[iStack_358] = '\0';
        sprintf(acStack_100,s_asm__s__s_004d1c94,acStack_350,abStack_1f8);
        str_tolower(acStack_100);
        out_text(acStack_100,0);
      }
      uVar11 = uVar11 + iVar5 * iStack_364;
      if (gui_mode != 0) {
        dsp_free_ext(cur_dev_index,0);
      }
    }
    else if (iVar7 == 0x1b) {
      return;
    }
    status_line1(&empty_str);
    if (iVar7 == 0xe) {
      if (iStack_364 < 1) {
        iStack_364 = 1;
      }
      uVar11 = uVar11 + iVar5 * iStack_364;
    }
    else if (iVar7 == 0x15) {
      uVar11 = uVar11 - iVar5;
    }
    uVar11 = uVar11 & uStack_35c;
    *(uint *)(cur_sim + 0xc) = uVar11;
    iStack_364 = disasm_line(uStack_368,uVar11,acStack_350,arg);
    out_text(acStack_350,1);
    uVar10 = 0xffffffff;
    pcVar13 = acStack_350;
    do {
      if (uVar10 == 0) break;
      uVar10 = uVar10 - 1;
      cVar1 = *pcVar13;
      pcVar13 = pcVar13 + 1;
    } while (cVar1 != '\0');
    if (screen_cols - 1U < ~uVar10 - 1) {
      out_text(acStack_350 + screen_cols,1);
    }
    iVar6 = str_find_char(acStack_350,0x3d);
    iStack_358 = str_find_char(acStack_350,0x20);
  } while( true );
  status_line1(parm_errmsg);
  goto LAB_0045409b;
}


/* ==== cmd_asm_h1 @ 00454400 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void cmd_asm_h1(void)

{
  code *pcVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar5 = asm_result;
  uVar2 = (uint)(DAT_004a93ea == 'j');
  iVar7 = 1;
  if ((&DAT_004a93ea)[uVar2] == 'm') {
    uVar4 = 0;
    iVar6 = *(int *)(cur_dev + 0x1c);
  }
  else {
    iVar6 = (uVar2 + 2) * 0x28;
    uVar4 = *(undefined4 *)
             (*(int *)(cur_dtype + 0x20) + 4 + (uint)*(ushort *)(&DAT_004a968c + iVar6) * 0x2c);
    iVar6 = *(int *)(&g_tok_val + iVar6);
  }
  if (_DAT_005059f4 == 0) {
    if (0 < asm_result) {
      pcVar1 = *(code **)(*(int *)(cur_dtype + 0x28) + 0x18);
      if (pcVar1 == (code *)0x0) {
        iVar7 = (**(code **)(*(int *)(cur_dtype + 0x28) + 4))(uVar4,iVar6,&DAT_005059e4);
      }
      else {
        iVar7 = (*pcVar1)(uVar4,iVar6,&DAT_005059e4,uVar2);
      }
      if (iVar7 == 0) {
        iVar7 = 1;
      }
    }
    if (1 < iVar5) {
      pcVar1 = *(code **)(*(int *)(cur_dtype + 0x28) + 0x18);
      if (pcVar1 == (code *)0x0) {
        (**(code **)(*(int *)(cur_dtype + 0x28) + 4))(uVar4,iVar7 + iVar6,&DAT_005059e8);
      }
      else {
        (*pcVar1)(uVar4,iVar7 + iVar6,&DAT_005059e8,uVar2);
      }
    }
    if (2 < iVar5) {
      pcVar1 = *(code **)(*(int *)(cur_dtype + 0x28) + 0x18);
      if (pcVar1 == (code *)0x0) {
        (**(code **)(*(int *)(cur_dtype + 0x28) + 4))(uVar4,iVar6 + iVar7 * 2,&DAT_005059ec);
      }
      else {
        (*pcVar1)(uVar4,iVar6 + iVar7 * 2,&DAT_005059ec,uVar2);
      }
    }
  }
  else {
    iVar5 = 0;
    if (0 < _DAT_005059f4) {
      iVar7 = 0x5059f8;
      do {
        pcVar1 = *(code **)(*(int *)(cur_dtype + 0x28) + 0x18);
        if (pcVar1 == (code *)0x0) {
          iVar3 = (**(code **)(*(int *)(cur_dtype + 0x28) + 4))(uVar4,iVar6,iVar7);
        }
        else {
          iVar3 = (*pcVar1)(uVar4,iVar6,iVar7,uVar2);
        }
        if (iVar3 == 0) {
          iVar3 = 1;
        }
        iVar6 = iVar6 + iVar3;
        iVar5 = iVar5 + 1;
        iVar7 = iVar7 + 4;
      } while (iVar5 < _DAT_005059f4);
    }
  }
  if (*(int *)(cur_sim + 0x4400) == 1) {
    win_update(0);
  }
  return;
}


/* ==== cmd_asm_parse @ 00454590 ==== */

int cmd_asm_parse(void)

{
  int iVar1;
  int iVar2;
  int idx;
  int iVar3;
  
  iVar3 = -1;
  iVar1 = parm_keyword1(2,&DAT_004b29b0);
  idx = (iVar1 != 0) + 2;
  iVar2 = parm_check_too_many(idx);
  if (iVar2 == 0) {
    iVar2 = parm_match_space_cur(idx);
    if (iVar2 == 0) {
      *(undefined4 *)(&g_tok_val + idx * 0x28) = *(undefined4 *)(cur_dev + 0x1c);
      iVar1 = parm_filename(idx);
    }
    else {
      iVar2 = (iVar1 != 0) + 3;
      iVar1 = parm_check_too_many(iVar2);
      if (iVar1 != 0) {
        iVar3 = 0;
        goto LAB_00454613;
      }
      iVar1 = parm_filename(iVar2);
    }
    if (iVar1 != 0) {
      iVar3 = 1;
    }
  }
  else {
    iVar3 = 0;
  }
LAB_00454613:
  if (iVar3 == -1) {
    return 0;
  }
  return iVar3 * 8 + 0x4d1890;
}


