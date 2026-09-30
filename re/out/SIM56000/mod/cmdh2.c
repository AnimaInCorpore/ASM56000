/* ==== cmd_help_h0 @ 0044d670 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void cmd_help_h0(void)

{
  uint *puVar1;
  char cVar2;
  byte bVar3;
  undefined4 uVar4;
  undefined *puVar5;
  uint uVar6;
  byte *pbVar7;
  int iVar8;
  long lVar9;
  undefined4 *puVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  uint uVar15;
  int iVar16;
  int *piVar17;
  int iVar18;
  char *pcVar19;
  uint uVar20;
  byte *pbVar21;
  int iVar22;
  char *pcVar23;
  char *pcVar24;
  bool bVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int in_stack_fffffe18;
  int iVar29;
  int iVar30;
  undefined4 in_stack_fffffe30;
  undefined4 in_stack_fffffe34;
  long in_stack_fffffe38;
  long lStack_1bc;
  undefined4 uStack_1b8;
  int iStack_1b4;
  int iStack_1b0;
  int iStack_1ac;
  int iStack_1a8;
  undefined4 uStack_1a4;
  byte abStack_1a0 [256];
  char acStack_a0 [80];
  char acStack_50 [80];
  
  puVar5 = command_table;
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar6 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar6 = (**(code **)(cur_dtype + 0x4e8))();
  }
  if (DAT_004a93ea == 'e') {
    help_list_all();
    return;
  }
  if (DAT_004a93ea == 'g') {
    cmd_help_h0_sub_44dff0(0x4a96b8);
    return;
  }
  if (DAT_004a93ea == 'N') {
    strncpy((char *)abStack_1a0,&cmd_tokbuf + DAT_004a9470,99);
    str_tolower((char *)abStack_1a0);
    pcVar19 = s_stack_004cd478;
    pbVar7 = abStack_1a0;
    do {
      bVar3 = *pbVar7;
      bVar25 = bVar3 < (byte)*pcVar19;
      if (bVar3 != *pcVar19) {
LAB_0044d743:
        iVar8 = (1 - (uint)bVar25) - (uint)(bVar25 != 0);
        goto LAB_0044d748;
      }
      if (bVar3 == 0) break;
      bVar3 = pbVar7[1];
      bVar25 = bVar3 < (byte)pcVar19[1];
      if (bVar3 != pcVar19[1]) goto LAB_0044d743;
      pbVar7 = pbVar7 + 2;
      pcVar19 = pcVar19 + 2;
    } while (bVar3 != 0);
    iVar8 = 0;
LAB_0044d748:
    if (iVar8 == 0) {
      iVar8 = *(int *)(cur_dev + 4);
      iVar26 = iVar8;
      lVar9 = periph_find_reg(iVar8,&DAT_004b2928,&iStack_1b4,(int *)&stack0xfffffe18);
      if (((lVar9 != 0) &&
          (lVar9 = periph_find_reg(iVar8,&DAT_004b2920,&iStack_1ac,(int *)&stack0xfffffe38),
          lVar9 != 0)) &&
         (lVar9 = periph_find_reg(iVar8,&DAT_004b291c,&iStack_1a8,&lStack_1bc), lVar9 != 0)) {
        iVar8 = *(int *)(*(int *)(cur_dev + 8) + iStack_1b4 * 4);
        uVar6 = *(uint *)(iVar8 + in_stack_fffffe18 * 4);
        puVar1 = (uint *)(iVar8 + in_stack_fffffe18 * 4);
        out_text(s_SP_SSH_SSL_STACK_LEVEL_004cd454,1);
        out_text(s__________________________________004cd430,1);
        uVar20 = 0xf;
        do {
          *puVar1 = uVar20;
          if (uVar20 == 0) {
            in_stack_fffffe30 = 0;
            in_stack_fffffe34 = 0;
          }
          else {
            lVar9 = periph_call(iVar26,iStack_1ac,in_stack_fffffe38,(long)&stack0xfffffe34);
            if ((lVar9 == 0) ||
               (lVar9 = periph_call(iVar26,iStack_1a8,lStack_1bc,(long)&stack0xfffffe30), lVar9 == 0
               )) {
              sim_error(s_Error_reading_stack_004cd2c0);
              return;
            }
          }
          sprintf((char *)abStack_1a0,s____08lx__08lx_level__02d__004cd414,in_stack_fffffe34,
                  in_stack_fffffe30,uVar20);
          if (uVar20 == (uVar6 & 0xf)) {
            abStack_1a0[2] = 0x3e;
          }
          pbVar7 = abStack_1a0;
          if ((int)(uVar6 & 0xf) < (int)uVar20) {
            pbVar7 = abStack_1a0 + 1;
          }
          out_text((char *)pbVar7,1);
          uVar20 = uVar20 - 1;
        } while (-1 < (int)uVar20);
        *puVar1 = uVar6;
        if ((uVar6 & 0x20) != 0) {
          out_text(s___STACK_POINTER_INDICATES_STACK_U_004cd3e0,1);
          return;
        }
        if ((uVar6 & 0x10) != 0) {
          out_text(s___STACK_POINTER_INDICATES_STACK_O_004cd3ac,1);
          return;
        }
      }
    }
    else {
      pbVar21 = (byte *)0x4cd3a8;
      pbVar7 = abStack_1a0;
      do {
        bVar3 = *pbVar7;
        bVar25 = bVar3 < *pbVar21;
        if (bVar3 != *pbVar21) {
LAB_0044d913:
          iVar8 = (1 - (uint)bVar25) - (uint)(bVar25 != 0);
          goto LAB_0044d918;
        }
        if (bVar3 == 0) break;
        bVar3 = pbVar7[1];
        bVar25 = bVar3 < pbVar21[1];
        if (bVar3 != pbVar21[1]) goto LAB_0044d913;
        pbVar7 = pbVar7 + 2;
        pbVar21 = pbVar21 + 2;
      } while (bVar3 != 0);
      iVar8 = 0;
LAB_0044d918:
      if (iVar8 == 0) {
        uVar6 = 0xffffffff;
        pcVar19 = _DAT_004cc860;
        do {
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          cVar2 = *pcVar19;
          pcVar19 = pcVar19 + 1;
        } while (cVar2 != '\0');
        iVar8 = *(int *)(cur_dtype + 0x38);
        uVar20 = *(uint *)(cur_dtype + 8);
        iVar11 = ~uVar6 - 8;
        iVar26 = *(int *)(cur_dtype + 0x3c);
        iVar14 = iVar8;
        out_text(s_pin_index_port_index_bit_number_p_004cd354,1);
        iVar22 = 0;
        iVar27 = 1;
        iVar30 = 0;
        if (0 < iVar8) {
          do {
            sprintf((char *)abStack_1a0,s__c_s_c_s_c_s_004cd344,0,_DAT_004cc860,0,_DAT_004cc860,0,
                    _DAT_004cc860);
            iVar28 = 0;
            piVar17 = (int *)(iVar26 + 0xc + iVar22 * 0x18);
            do {
              if (iVar8 <= iVar22) break;
              if ((uVar20 & piVar17[2]) != 0) {
                uVar6 = piVar17[1];
                iVar16 = *piVar17;
                uVar12 = 1;
                iVar8 = 0;
                do {
                  if ((uVar6 & uVar12) != 0) break;
                  iVar8 = iVar8 + 1;
                  uVar12 = uVar12 << 1;
                } while (uVar12 != 0);
                sprintf(acStack_a0,s__3d__d__2d__s_004cd334,iVar27,iVar16,iVar8,piVar17[-3]);
                iVar22 = iVar30;
                iVar8 = iVar14;
                if (piVar17[-2] != 0) {
                  sprintf(acStack_50,(char *)0x4cd330,piVar17[-2]);
                  uVar12 = 0xffffffff;
                  pcVar19 = acStack_50;
                  do {
                    pcVar24 = pcVar19;
                    if (uVar12 == 0) break;
                    uVar12 = uVar12 - 1;
                    pcVar24 = pcVar19 + 1;
                    cVar2 = *pcVar19;
                    pcVar19 = pcVar24;
                  } while (cVar2 != '\0');
                  uVar12 = ~uVar12;
                  iVar8 = -1;
                  pcVar19 = acStack_a0;
                  do {
                    pcVar23 = pcVar19;
                    if (iVar8 == 0) break;
                    iVar8 = iVar8 + -1;
                    pcVar23 = pcVar19 + 1;
                    cVar2 = *pcVar19;
                    pcVar19 = pcVar23;
                  } while (cVar2 != '\0');
                  pcVar19 = pcVar24 + -uVar12;
                  pcVar24 = pcVar23 + -1;
                  for (uVar13 = uVar12 >> 2; uVar13 != 0; uVar13 = uVar13 - 1) {
                    *(undefined4 *)pcVar24 = *(undefined4 *)pcVar19;
                    pcVar19 = pcVar19 + 4;
                    pcVar24 = pcVar24 + 4;
                  }
                  for (uVar12 = uVar12 & 3; iVar22 = iVar30, iVar8 = iVar14, uVar12 != 0;
                      uVar12 = uVar12 - 1) {
                    *pcVar24 = *pcVar19;
                    pcVar19 = pcVar19 + 1;
                    pcVar24 = pcVar24 + 1;
                  }
                }
                if (piVar17[-1] != 0) {
                  sprintf(acStack_50,(char *)0x4cd330,piVar17[-1]);
                  uVar12 = 0xffffffff;
                  pcVar19 = acStack_50;
                  do {
                    pcVar24 = pcVar19;
                    if (uVar12 == 0) break;
                    uVar12 = uVar12 - 1;
                    pcVar24 = pcVar19 + 1;
                    cVar2 = *pcVar19;
                    pcVar19 = pcVar24;
                  } while (cVar2 != '\0');
                  uVar12 = ~uVar12;
                  iVar30 = -1;
                  pcVar19 = acStack_a0;
                  do {
                    pcVar23 = pcVar19;
                    if (iVar30 == 0) break;
                    iVar30 = iVar30 + -1;
                    pcVar23 = pcVar19 + 1;
                    cVar2 = *pcVar19;
                    pcVar19 = pcVar23;
                  } while (cVar2 != '\0');
                  pcVar19 = pcVar24 + -uVar12;
                  pcVar24 = pcVar23 + -1;
                  for (uVar13 = uVar12 >> 2; uVar13 != 0; uVar13 = uVar13 - 1) {
                    *(undefined4 *)pcVar24 = *(undefined4 *)pcVar19;
                    pcVar19 = pcVar19 + 4;
                    pcVar24 = pcVar24 + 4;
                  }
                  for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
                    *pcVar24 = *pcVar19;
                    pcVar19 = pcVar19 + 1;
                    pcVar24 = pcVar24 + 1;
                  }
                }
                uVar12 = 0xffffffff;
                acStack_a0[iVar11] = '\0';
                pcVar19 = acStack_a0;
                do {
                  pcVar24 = pcVar19;
                  if (uVar12 == 0) break;
                  uVar12 = uVar12 - 1;
                  pcVar24 = pcVar19 + 1;
                  cVar2 = *pcVar19;
                  pcVar19 = pcVar24;
                } while (cVar2 != '\0');
                uVar12 = ~uVar12;
                iVar30 = -1;
                pbVar7 = abStack_1a0;
                do {
                  pbVar21 = pbVar7;
                  if (iVar30 == 0) break;
                  iVar30 = iVar30 + -1;
                  pbVar21 = pbVar7 + 1;
                  bVar3 = *pbVar7;
                  pbVar7 = pbVar21;
                } while (bVar3 != 0);
                pbVar7 = (byte *)(pcVar24 + -uVar12);
                pbVar21 = pbVar21 + -1;
                for (uVar13 = uVar12 >> 2; uVar13 != 0; uVar13 = uVar13 - 1) {
                  *(undefined4 *)pbVar21 = *(undefined4 *)pbVar7;
                  pbVar7 = pbVar7 + 4;
                  pbVar21 = pbVar21 + 4;
                }
                for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
                  *pbVar21 = *pbVar7;
                  pbVar7 = pbVar7 + 1;
                  pbVar21 = pbVar21 + 1;
                }
                iVar30 = *(int *)(cur_dev + 0x18);
                if (iVar30 != 0) {
                  iVar16 = iVar16 * 0x128;
                  if ((*(uint *)(iVar16 + 4 + iVar30) & uVar6) == 0) {
                    pcVar19 = (char *)0x4cd318;
                  }
                  else if ((*(uint *)(iVar16 + iVar30) & uVar6) == 0) {
                    pcVar19 = (char *)0x4cd320;
                  }
                  else {
                    pcVar19 = (char *)0x4cd328;
                  }
                  uVar12 = 0xffffffff;
                  do {
                    pcVar24 = pcVar19;
                    if (uVar12 == 0) break;
                    uVar12 = uVar12 - 1;
                    pcVar24 = pcVar19 + 1;
                    cVar2 = *pcVar19;
                    pcVar19 = pcVar24;
                  } while (cVar2 != '\0');
                  uVar12 = ~uVar12;
                  iVar30 = -1;
                  pbVar7 = abStack_1a0;
                  do {
                    pbVar21 = pbVar7;
                    if (iVar30 == 0) break;
                    iVar30 = iVar30 + -1;
                    pbVar21 = pbVar7 + 1;
                    bVar3 = *pbVar7;
                    pbVar7 = pbVar21;
                  } while (bVar3 != 0);
                  pbVar7 = (byte *)(pcVar24 + -uVar12);
                  pbVar21 = pbVar21 + -1;
                  for (uVar13 = uVar12 >> 2; uVar13 != 0; uVar13 = uVar13 - 1) {
                    *(undefined4 *)pbVar21 = *(undefined4 *)pbVar7;
                    pbVar7 = pbVar7 + 4;
                    pbVar21 = pbVar21 + 4;
                  }
                  for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
                    *pbVar21 = *pbVar7;
                    pbVar7 = pbVar7 + 1;
                    pbVar21 = pbVar21 + 1;
                  }
                  iVar16 = *(int *)(cur_dev + 0x18) + iVar16;
                  if ((*(uint *)(iVar16 + 0xc) & uVar6) == 0) {
                    pcVar19 = (char *)0x4cd30c;
                  }
                  else if ((*(uint *)(iVar16 + 8) & uVar6) == 0) {
                    pcVar19 = (char *)0x4cd310;
                  }
                  else {
                    pcVar19 = (char *)0x4cd314;
                  }
                  uVar6 = 0xffffffff;
                  do {
                    pcVar24 = pcVar19;
                    if (uVar6 == 0) break;
                    uVar6 = uVar6 - 1;
                    pcVar24 = pcVar19 + 1;
                    cVar2 = *pcVar19;
                    pcVar19 = pcVar24;
                  } while (cVar2 != '\0');
                  uVar6 = ~uVar6;
                  iVar30 = -1;
                  pbVar7 = abStack_1a0;
                  do {
                    pbVar21 = pbVar7;
                    if (iVar30 == 0) break;
                    iVar30 = iVar30 + -1;
                    pbVar21 = pbVar7 + 1;
                    bVar3 = *pbVar7;
                    pbVar7 = pbVar21;
                  } while (bVar3 != 0);
                  pbVar7 = (byte *)(pcVar24 + -uVar6);
                  pbVar21 = pbVar21 + -1;
                  for (uVar12 = uVar6 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                    *(undefined4 *)pbVar21 = *(undefined4 *)pbVar7;
                    pbVar7 = pbVar7 + 4;
                    pbVar21 = pbVar21 + 4;
                  }
                  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *pbVar21 = *pbVar7;
                    pbVar7 = pbVar7 + 1;
                    pbVar21 = pbVar21 + 1;
                  }
                }
                uVar6 = 0xffffffff;
                pbVar7 = abStack_1a0;
                do {
                  if (uVar6 == 0) break;
                  uVar6 = uVar6 - 1;
                  bVar3 = *pbVar7;
                  pbVar7 = pbVar7 + 1;
                } while (bVar3 != 0);
                iVar14 = iVar8;
                abStack_1a0[~uVar6 - 1] = 0x20;
                iVar27 = iVar27 + 1;
                iVar28 = iVar28 + 1;
              }
              iVar22 = iVar22 + 1;
              piVar17 = piVar17 + 6;
              iVar30 = iVar22;
            } while (iVar28 < 2);
            out_text((char *)abStack_1a0,1);
            if (iVar8 <= iVar22) {
              return;
            }
          } while( true );
        }
      }
      else {
        pbVar21 = (byte *)0x4cd308;
        pbVar7 = abStack_1a0;
        do {
          bVar3 = *pbVar7;
          bVar25 = bVar3 < *pbVar21;
          if (bVar3 != *pbVar21) {
LAB_0044dc20:
            iVar8 = (1 - (uint)bVar25) - (uint)(bVar25 != 0);
            goto LAB_0044dc25;
          }
          if (bVar3 == 0) break;
          bVar3 = pbVar7[1];
          bVar25 = bVar3 < pbVar21[1];
          if (bVar3 != pbVar21[1]) goto LAB_0044dc20;
          pbVar7 = pbVar7 + 2;
          pbVar21 = pbVar21 + 2;
        } while (bVar3 != 0);
        iVar8 = 0;
LAB_0044dc25:
        if (iVar8 == 0) {
          iVar8 = 0;
          if (0 < *(int *)(cur_dtype + 0x1c)) {
            iVar26 = 0;
            do {
              iVar22 = iVar26 + *(int *)(cur_dtype + 0x20);
              if ((*(uint *)(iVar22 + 0x18) & 0x10000) != 0) {
                iVar30 = 0;
                uVar12 = (-(uint)((uVar6 & 0x800) != 0) & 0x10000) - 1;
                uVar20 = *(uint *)(iVar22 + 0xc) & uVar12;
                iVar14 = ((*(uint *)(iVar22 + 0x10) & uVar12) - uVar20) + 1;
                iVar22 = *(int *)(cur_dtype + 0x14);
                iVar11 = cur_dtype;
                for (; iVar14 != 0; iVar14 = iVar14 + -1) {
                  iVar27 = iVar22;
                  if (0 < iVar22) {
                    iVar28 = 0;
                    do {
                      puVar10 = (undefined4 *)(iVar28 + *(int *)(iVar11 + 0x18));
                      uStack_1b8 = *puVar10;
                      uStack_1a4 = puVar10[7];
                      uVar4 = puVar10[0xc];
                      iVar29 = 0;
                      iStack_1b0 = *(int *)(puVar10[0xb] + 0x28);
                      iVar16 = *(int *)(puVar10[0xb] + 0x2c);
                      iVar18 = iVar30;
                      if (0 < iStack_1b0) {
                        do {
                          iVar30 = iVar18;
                          if (((*(byte *)(iVar16 + 0x10 + iVar29 * 0x1c) & 0x60) != 0) &&
                             (uVar20 == (*(int *)(iVar16 + iVar29 * 0x1c + 8) + uStack_1a4 & uVar12)
                             )) {
                            if (iVar18 == 0) {
                              sprintf((char *)abStack_1a0,s__c_s_c_s_c_s_004cd344,0,PTR_s__004cc864,
                                      0,PTR_s__004cc864,0,PTR_s__004cc864);
                            }
                            sprintf(acStack_a0,s___04lx__s__s_s_004cd2f8,uVar20,uStack_1b8,
                                    *(undefined4 *)(iVar16 + iVar29 * 0x1c),uVar4);
                            uVar13 = 0xffffffff;
                            pcVar19 = acStack_a0;
                            do {
                              pcVar24 = pcVar19;
                              if (uVar13 == 0) break;
                              uVar13 = uVar13 - 1;
                              pcVar24 = pcVar19 + 1;
                              cVar2 = *pcVar19;
                              pcVar19 = pcVar24;
                            } while (cVar2 != '\0');
                            uVar13 = ~uVar13;
                            iVar30 = -1;
                            pbVar7 = abStack_1a0;
                            do {
                              pbVar21 = pbVar7;
                              if (iVar30 == 0) break;
                              iVar30 = iVar30 + -1;
                              pbVar21 = pbVar7 + 1;
                              bVar3 = *pbVar7;
                              pbVar7 = pbVar21;
                            } while (bVar3 != 0);
                            pbVar7 = (byte *)(pcVar24 + -uVar13);
                            pbVar21 = pbVar21 + -1;
                            for (uVar15 = uVar13 >> 2; uVar15 != 0; uVar15 = uVar15 - 1) {
                              *(undefined4 *)pbVar21 = *(undefined4 *)pbVar7;
                              pbVar7 = pbVar7 + 4;
                              pbVar21 = pbVar21 + 4;
                            }
                            iVar30 = iVar18 + 1;
                            for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
                              *pbVar21 = *pbVar7;
                              pbVar7 = pbVar7 + 1;
                              pbVar21 = pbVar21 + 1;
                            }
                            if (iVar18 == 2) {
                              iVar30 = 0;
                              out_text((char *)abStack_1a0,1);
                            }
                            else {
                              uVar13 = 0xffffffff;
                              pbVar7 = abStack_1a0;
                              do {
                                if (uVar13 == 0) break;
                                uVar13 = uVar13 - 1;
                                bVar3 = *pbVar7;
                                pbVar7 = pbVar7 + 1;
                              } while (bVar3 != 0);
                              abStack_1a0[~uVar13 - 1] = 0x20;
                            }
                          }
                          iVar29 = iVar29 + 1;
                          iVar18 = iVar30;
                          iVar11 = cur_dtype;
                        } while (iVar29 < iStack_1b0);
                      }
                      iVar28 = iVar28 + 0x48;
                      iVar22 = iVar22 + -1;
                    } while (iVar22 != 0);
                  }
                  uVar20 = uVar20 + 1;
                  iVar22 = iVar27;
                }
                if (iVar30 != 0) {
                  out_text((char *)abStack_1a0,1);
                }
              }
              iVar8 = iVar8 + 1;
              iVar26 = iVar26 + 0x2c;
              if (*(int *)(cur_dtype + 0x1c) <= iVar8) {
                return;
              }
            } while( true );
          }
        }
        else {
          pbVar21 = (byte *)0x4cd2f4;
          pbVar7 = abStack_1a0;
          do {
            bVar3 = *pbVar7;
            bVar25 = bVar3 < *pbVar21;
            if (bVar3 != *pbVar21) {
LAB_0044de8f:
              iVar8 = (1 - (uint)bVar25) - (uint)(bVar25 != 0);
              goto LAB_0044de94;
            }
            if (bVar3 == 0) break;
            bVar3 = pbVar7[1];
            bVar25 = bVar3 < pbVar21[1];
            if (bVar3 != pbVar21[1]) goto LAB_0044de8f;
            pbVar7 = pbVar7 + 2;
            pbVar21 = pbVar21 + 2;
          } while (bVar3 != 0);
          iVar8 = 0;
LAB_0044de94:
          if (iVar8 == 0) {
            cmd_help_h0_sub_44e5a0(0xf,0);
            cmd_help_h0_sub_44e5a0(0xe,0);
            cmd_help_h0_sub_44e5a0(0xc,0);
            cmd_help_h0_sub_44e5a0(0x122,1);
            cmd_help_h0_sub_44e5a0(0x13,1);
            cmd_help_h0_sub_44e5a0(0x14,1);
            cmd_help_h0_sub_44e5a0(0x123,2);
            cmd_help_h0_sub_44e5a0(0x18,2);
            cmd_help_h0_sub_44e5a0(0x19,2);
            return;
          }
          help_topic((char *)abStack_1a0);
          pbVar21 = &DAT_004ab490;
          pbVar7 = abStack_1a0;
          do {
            bVar3 = *pbVar7;
            bVar25 = bVar3 < *pbVar21;
            if (bVar3 != *pbVar21) {
LAB_0044df50:
              iVar8 = (1 - (uint)bVar25) - (uint)(bVar25 != 0);
              goto LAB_0044df55;
            }
            if (bVar3 == 0) break;
            bVar3 = pbVar7[1];
            bVar25 = bVar3 < pbVar21[1];
            if (bVar3 != pbVar21[1]) goto LAB_0044df50;
            pbVar7 = pbVar7 + 2;
            pbVar21 = pbVar21 + 2;
          } while (bVar3 != 0);
          iVar8 = 0;
LAB_0044df55:
          if ((iVar8 == 0) && (iVar8 = *(int *)(cur_dtype + 0x40), 0 < iVar8)) {
            iVar26 = 0;
            do {
              puVar10 = (undefined4 *)(*(int *)(cur_dtype + 0x44) + iVar26);
              sprintf((char *)abStack_1a0,s_port__s__index__d__mask_0x_lx_004cd2d4,*puVar10,
                      *(undefined4 *)(*(int *)(cur_dtype + 0x44) + 4 + iVar26),puVar10[2]);
              out_text((char *)abStack_1a0,1);
              iVar26 = iVar26 + 0x14;
              iVar8 = iVar8 + -1;
            } while (iVar8 != 0);
            return;
          }
        }
      }
    }
  }
  else {
    help_topic(*(char **)(*(int *)(puVar5 + DAT_004a96c0 * 4) + 8));
  }
  return;
}


/* ==== cmd_help_h0_sub_44dff0 @ 0044dff0 ==== */

void cmd_help_h0_sub_44dff0(int param_1)

{
  char cVar1;
  ushort uVar2;
  long lVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  uint uVar12;
  uint uVar13;
  char *pcVar14;
  char *pcVar15;
  uint uStack_120;
  uint uStack_118;
  char *pcStack_110;
  uint uStack_10c;
  uint uStack_108;
  uint uStack_104;
  char acStack_100 [256];
  
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  uVar2 = *(ushort *)(param_1 + 0x24);
  uVar8 = (uint)*(ushort *)(param_1 + 0x20);
  iVar10 = (uint)uVar2 * 0x48;
  iVar5 = *(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + iVar10) + 0x2c);
  iVar9 = iVar5 + uVar8 * 0x1c;
  uStack_118 = *(uint *)(iVar5 + 4 + uVar8 * 0x1c);
  uVar13 = *(uint *)(iVar9 + 0x10);
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uStack_120 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uStack_120 = (**(code **)(cur_dtype + 0x4e8))();
  }
  if (((*(int *)(cur_dtype + 4) == 0x2ca) && (0xfffe < uStack_118)) &&
     (((uVar13 & 0x10200000) != 0 || (((uVar13 & 0x2000000) != 0 && ((uVar13 & 1) == 0)))))) {
    uStack_118 = 0xffff;
    uStack_120 = uStack_120 & 0xfbffffff | 0x10000000;
  }
  if ((uVar13 & 0x60) == 0) {
    sprintf(acStack_100,s__s_register_004cd490,*(undefined4 *)(*(int *)(cur_dtype + 0x18) + iVar10))
    ;
  }
  else {
    puVar11 = (undefined4 *)(*(int *)(cur_dtype + 0x18) + iVar10);
    pcStack_110 = s__s__s_register__X__04lx_004cd4d8;
    if (*(int *)(*(int *)(cur_dtype + 0x18) + 0x40 + iVar10) != 0) {
      pcStack_110 = s__s__s_register__Y__04lx_004cd4c0;
    }
    if ((*(uint *)(iVar9 + 0x10) & 0x20) == 0) {
      pcVar7 = s_Write_Only_004cd49c;
    }
    else if ((*(uint *)(iVar9 + 0x10) & 0x40) == 0) {
      pcVar7 = s_Read_Only_004cd4a8;
    }
    else {
      pcVar7 = s_Read_Write_004cd4b4;
    }
    sprintf(acStack_100,pcStack_110,pcVar7,*puVar11,
            *(int *)(iVar9 + 8) + puVar11[7] & (-(uint)((uStack_120 & 0x800) != 0) & 0x10000) - 1);
  }
  out_text(acStack_100,1);
  puVar11 = *(undefined4 **)(iVar9 + 0x14);
  if (puVar11 != (undefined4 *)0x0) {
    pcVar7 = (char *)*puVar11;
    while (pcVar7 != (char *)0x0) {
      puVar11 = puVar11 + 1;
      out_text(pcVar7,1);
      pcVar7 = (char *)*puVar11;
    }
  }
  uVar12 = uVar13 & 4;
  if ((uVar12 != 0) && ((uStack_120 & 0x2000000) != 0)) {
    return;
  }
  lVar3 = periph_call(*(int *)(cur_dev + 4),(uint)uVar2,uVar8,(long)&uStack_10c);
  if (lVar3 == 0) {
    sim_error(s_Error_reading_register_004c6178);
    return;
  }
  acStack_100[0] = '\0';
  if ((uVar12 == 0) && (((uVar13 & 2) == 0 || ((uStack_120 & 0x6000000) == 0)))) {
    iVar9 = 0;
  }
  else {
    iVar9 = 1;
  }
  if (uVar12 != 0) {
    uVar8 = 0x80;
    do {
      pcVar7 = (char *)(iVar9 + 0x4cc5d0);
      if ((uVar8 & uStack_104) == 0) {
        pcVar7 = (char *)(iVar9 + 0x4cc5d4);
      }
      uVar4 = 0xffffffff;
      do {
        pcVar15 = pcVar7;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar15 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar15;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar5 = -1;
      pcVar7 = acStack_100;
      do {
        pcVar14 = pcVar7;
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar14 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar14;
      } while (cVar1 != '\0');
      pcVar7 = pcVar15 + -uVar4;
      pcVar15 = pcVar14 + -1;
      for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar15 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar15 = pcVar15 + 4;
      }
      uVar8 = uVar8 >> 1;
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar15 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar15 = pcVar15 + 1;
      }
    } while (uVar8 != 0);
  }
  if ((uVar13 & 6) != 0) {
    if ((uStack_120 & 0x10000000) == 0) {
      uVar8 = (-(uint)((uStack_120 & 0x2000000) != 0) & 0x7f800000) + 0x800000;
    }
    else {
      uVar8 = 0x8000;
    }
    while (uVar8 != 0) {
      pcVar7 = (char *)(iVar9 + 0x4cc5d0);
      if ((uVar8 & uStack_108) == 0) {
        pcVar7 = (char *)(iVar9 + 0x4cc5d4);
      }
      uVar4 = 0xffffffff;
      do {
        pcVar15 = pcVar7;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar15 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar15;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar5 = -1;
      pcVar7 = acStack_100;
      do {
        pcVar14 = pcVar7;
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar14 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar14;
      } while (cVar1 != '\0');
      pcVar7 = pcVar15 + -uVar4;
      pcVar15 = pcVar14 + -1;
      for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar15 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar15 = pcVar15 + 4;
      }
      uVar8 = uVar8 >> 1;
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar15 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar15 = pcVar15 + 1;
      }
    }
  }
  if (uStack_118 < 0x100) {
    uVar8 = 0x80;
  }
  else if (uStack_118 < 0x10000) {
    uVar8 = 0x8000;
  }
  else {
    uVar8 = (-(uint)(0xffffff < uStack_118) & 0x7f800000) + 0x800000;
  }
  while (uVar8 != 0) {
    pcVar7 = (char *)(iVar9 + 0x4cc5d0);
    if ((uVar8 & uStack_10c) == 0) {
      pcVar7 = (char *)(iVar9 + 0x4cc5d4);
    }
    uVar4 = 0xffffffff;
    do {
      pcVar15 = pcVar7;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar15 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar15;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar5 = -1;
    pcVar7 = acStack_100;
    do {
      pcVar14 = pcVar7;
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      pcVar14 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar14;
    } while (cVar1 != '\0');
    pcVar7 = pcVar15 + -uVar4;
    pcVar15 = pcVar14 + -1;
    for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar15 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar15 = pcVar15 + 4;
    }
    uVar8 = uVar8 >> 1;
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar15 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar15 = pcVar15 + 1;
    }
  }
  uVar8 = 0xffffffff;
  pcVar7 = s_<_Bit_States_004cd480;
  do {
    pcVar15 = pcVar7;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar15 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar15;
  } while (cVar1 != '\0');
  uVar8 = ~uVar8;
  iVar9 = -1;
  pcVar7 = acStack_100;
  do {
    pcVar14 = pcVar7;
    if (iVar9 == 0) break;
    iVar9 = iVar9 + -1;
    pcVar14 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar14;
  } while (cVar1 != '\0');
  pcVar7 = pcVar15 + -uVar8;
  pcVar15 = pcVar14 + -1;
  for (uVar4 = uVar8 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar15 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar15 = pcVar15 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar15 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar15 = pcVar15 + 1;
  }
  if (uVar12 != 0) {
    uVar13 = (uStack_120 & 0x10000000 | 0x8000000) >> 0x18;
    out_text(s__________________________________004cc708 + uVar13,1);
    out_text(acStack_100,1);
    out_text(s__________________________________004cc708 + uVar13,1);
    out_text(s_66665555555555444444444433333333_004cc5d8 + uVar13,1);
    out_text((char *)(uVar13 + 0x4cc628),1);
    return;
  }
  uVar13 = uVar13 & 2;
  if (((uVar13 != 0) && ((uStack_120 & 0x4000000) != 0)) && ((uStack_120 & 0x10000000) != 0)) {
    out_text(s__________________________________004cc708 + 0x20,1);
    out_text(acStack_100,1);
    out_text(s__________________________________004cc708 + 0x20,1);
    out_text(s_66665555555555444444444433333333_004cc5d8 + 0x20,1);
    out_text((char *)0x4cc648,1);
    return;
  }
  if (uVar13 != 0) {
    if ((uStack_120 & 0x4000000) != 0) {
      out_text(s__________________________________004cc708 + 0x10,1);
      out_text(acStack_100,1);
      out_text(s__________________________________004cc708 + 0x10,1);
      out_text(s_66665555555555444444444433333333_004cc5d8 + 0x10,1);
      out_text((char *)0x4cc638,1);
      return;
    }
    if (uVar13 != 0) {
      if ((uStack_120 & 0x2000000) != 0) {
        out_text(s__________________________________004cc708,1);
        out_text(acStack_100,1);
        out_text(s__________________________________004cc708,1);
        out_text(s_66665555555555444444444433333333_004cc5d8,1);
        out_text((char *)0x4cc628,1);
        return;
      }
      if (uVar13 != 0) {
        iVar9 = 0;
        goto LAB_0044e53f;
      }
    }
  }
  if (uStack_118 < 0x100) {
    iVar9 = 0x30;
  }
  else if (uStack_118 < 0x10000) {
    iVar9 = 0x20;
  }
  else {
    iVar9 = (-(uint)(0xffffff < uStack_118) & 0xfffffff0) + 0x10;
  }
LAB_0044e53f:
  out_text(s__________________________________004cc708 + iVar9,1);
  out_text(acStack_100,1);
  out_text(s__________________________________004cc708 + iVar9,1);
  out_text(s_3_3_2_2_2_2_2_2_2_2_2_2_1_1_1_1_1_004cc670 + iVar9,1);
  out_text(s_1_0_9_8_7_6_5_4_3_2_1_0_9_8_7_6_5_004cc6c0 + iVar9,1);
  return;
}


/* ==== cmd_help_h0_sub_44e5a0 @ 0044e5a0 ==== */

void cmd_help_h0_sub_44e5a0(int param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  int iVar11;
  char acStack_64 [100];
  
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar2 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar2 = (**(code **)(cur_dtype + 0x4e8))();
  }
  iVar11 = *(int *)(cur_dtype + 0x4c + param_1 * 4);
  uVar2 = (-(uint)((uVar2 & 0x800) != 0) & 0x10000) - 1;
  if (iVar11 < *(int *)(cur_dtype + 0x1c)) {
    iVar5 = iVar11 * 0x2c;
    iVar4 = cur_dtype;
    do {
      if (((iVar5 != 0) && (iVar3 = *(int *)(iVar4 + 0x20) + iVar5, *(int *)(iVar3 + 4) == param_1))
         && ((*(uint *)(iVar3 + 0x18) & 0x5000004) == 0)) {
        uVar6 = *(uint *)(iVar3 + 0xc);
        uVar7 = *(uint *)(iVar3 + 0x10) & uVar2;
        iVar4 = memmap_find(param_1,uVar7);
        iVar3 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(param_2,uVar7);
        sprintf(acStack_64,s__s_from___08lx_through___08lx_004cd508,
                *(undefined4 *)(*(int *)(cur_dtype + 0x20) + iVar5),uVar6 & uVar2,uVar7);
        if ((iVar3 != param_1) ||
           (pcVar8 = s_enabled_004cd4fc, *(int *)(iVar4 * 0x10 + 0xc + *(int *)(cur_dev + 0xc)) != 0
           )) {
          pcVar8 = s_disabled_004cd4f0;
        }
        uVar6 = 0xffffffff;
        do {
          pcVar10 = pcVar8;
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          pcVar10 = pcVar8 + 1;
          cVar1 = *pcVar8;
          pcVar8 = pcVar10;
        } while (cVar1 != '\0');
        uVar6 = ~uVar6;
        iVar4 = -1;
        pcVar8 = acStack_64;
        do {
          pcVar9 = pcVar8;
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          pcVar9 = pcVar8 + 1;
          cVar1 = *pcVar8;
          pcVar8 = pcVar9;
        } while (cVar1 != '\0');
        pcVar8 = pcVar10 + -uVar6;
        pcVar10 = pcVar9 + -1;
        for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
          pcVar8 = pcVar8 + 4;
          pcVar10 = pcVar10 + 4;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar10 = *pcVar8;
          pcVar8 = pcVar8 + 1;
          pcVar10 = pcVar10 + 1;
        }
        out_text(acStack_64,1);
        iVar4 = cur_dtype;
      }
      iVar11 = iVar11 + 1;
      iVar5 = iVar5 + 0x2c;
    } while (iVar11 < *(int *)(iVar4 + 0x1c));
  }
  return;
}


/* ==== cmd_help_h2 @ 0044e720 ==== */

void cmd_help_h2(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 va1;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int va2;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  int iStack_140;
  int iStack_13c;
  int iStack_138;
  undefined1 *puStack_134;
  char acStack_128 [39];
  char acStack_101 [257];
  
  iStack_140 = 0;
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  iVar2 = *(int *)(cur_dtype + 0x14);
  if (0 < iVar2) {
    iStack_13c = 0;
    do {
      iVar3 = *(int *)(cur_dtype + 0x18);
      iVar6 = *(int *)(iVar3 + 0x2c + iStack_13c);
      puStack_134 = *(undefined1 **)(iVar3 + 0x30 + iStack_13c);
      va1 = *(undefined4 *)(iVar3 + iStack_13c);
      iStack_138 = *(int *)(iVar6 + 0x28);
      out_text(&empty_str,1);
      sprintf(acStack_101 + 1,s_peripheral_index__d__name__s__nu_004cd550,iStack_140,va1,iStack_138)
      ;
      out_text(acStack_101 + 1,1);
      if (puStack_134 == (undefined1 *)0x0) {
        puStack_134 = &empty_str;
      }
      iVar3 = *(int *)(iVar6 + 0x2c);
      iVar6 = 0;
      va2 = -1;
      iVar7 = iVar6;
      if (0 < iStack_138) {
        do {
          va2 = cmd_help_h2_sub_44e900(iStack_140,va2);
          iVar6 = iVar7;
          if (-1 < va2) {
            uVar4 = *(uint *)(iVar3 + 0x10 + va2 * 0x1c);
            if ((uVar4 & 4) == 0) {
              iVar6 = ((uVar4 & 2) != 0) + 1;
            }
            else {
              iVar6 = 3;
            }
            sprintf(acStack_128,s__s_s____d__sz__d_004cd53c,*(undefined4 *)(iVar3 + va2 * 0x1c),
                    puStack_134,va2,iVar6);
            if (iVar7 == 0) {
              sprintf(acStack_101 + 1,s__c_s_c_s_c_s_c_s_004cd528,0,0x4cc868,0,0x4cc868,0,0x4cc868,0
                      ,0x4cc868);
            }
            uVar4 = 0xffffffff;
            pcVar8 = acStack_128;
            do {
              pcVar10 = pcVar8;
              if (uVar4 == 0) break;
              uVar4 = uVar4 - 1;
              pcVar10 = pcVar8 + 1;
              cVar1 = *pcVar8;
              pcVar8 = pcVar10;
            } while (cVar1 != '\0');
            uVar4 = ~uVar4;
            iVar6 = -1;
            pcVar8 = acStack_101 + 1;
            do {
              pcVar9 = pcVar8;
              if (iVar6 == 0) break;
              iVar6 = iVar6 + -1;
              pcVar9 = pcVar8 + 1;
              cVar1 = *pcVar8;
              pcVar8 = pcVar9;
            } while (cVar1 != '\0');
            pcVar8 = pcVar10 + -uVar4;
            pcVar10 = pcVar9 + -1;
            for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
              pcVar8 = pcVar8 + 4;
              pcVar10 = pcVar10 + 4;
            }
            iVar6 = iVar7 + 1;
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *pcVar10 = *pcVar8;
              pcVar8 = pcVar8 + 1;
              pcVar10 = pcVar10 + 1;
            }
            if (iVar7 == 3) {
              iVar6 = 0;
              out_text(acStack_101 + 1,1);
            }
            else {
              pcVar8 = acStack_101;
              uVar4 = 0xffffffff;
              do {
                pcVar8 = pcVar8 + 1;
                if (uVar4 == 0) break;
                uVar4 = uVar4 - 1;
              } while (*pcVar8 != '\0');
              acStack_101[~uVar4] = ' ';
            }
          }
          iStack_138 = iStack_138 + -1;
          iVar7 = iVar6;
        } while (iStack_138 != 0);
      }
      if (iVar6 != 0) {
        out_text(acStack_101 + 1,1);
      }
      iStack_140 = iStack_140 + 1;
      iStack_13c = iStack_13c + 0x48;
    } while (iStack_140 < iVar2);
  }
  return;
}


/* ==== cmd_help_h2_sub_44e900 @ 0044e900 ==== */

int cmd_help_h2_sub_44e900(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  int iVar8;
  bool bVar9;
  int iStack_8;
  
  iVar2 = param_1;
  iVar6 = 0;
  param_1 = -1;
  iVar2 = *(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + iVar2 * 0x48);
  iVar3 = *(int *)(iVar2 + 0x2c);
  iVar2 = *(int *)(iVar2 + 0x28);
  if (0 < iVar2) {
    iVar8 = 0;
    iStack_8 = -0x1c;
    do {
      if (param_2 < 0) {
LAB_0044e985:
        if (-1 < param_1) {
          pbVar7 = *(byte **)(iVar3 + iStack_8);
          pbVar4 = *(byte **)(iVar3 + iVar8);
          do {
            bVar1 = *pbVar4;
            bVar9 = bVar1 < *pbVar7;
            if (bVar1 != *pbVar7) {
LAB_0044e9bd:
              iVar5 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
              goto LAB_0044e9c2;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar4[1];
            bVar9 = bVar1 < pbVar7[1];
            if (bVar1 != pbVar7[1]) goto LAB_0044e9bd;
            pbVar4 = pbVar4 + 2;
            pbVar7 = pbVar7 + 2;
          } while (bVar1 != 0);
          iVar5 = 0;
LAB_0044e9c2:
          if (-1 < iVar5) goto LAB_0044e9ce;
        }
        param_1 = iVar6;
        iStack_8 = iVar8;
      }
      else {
        pbVar7 = *(byte **)(iVar3 + param_2 * 0x1c);
        pbVar4 = *(byte **)(iVar3 + iVar8);
        do {
          bVar1 = *pbVar4;
          bVar9 = bVar1 < *pbVar7;
          if (bVar1 != *pbVar7) {
LAB_0044e97c:
            iVar5 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
            goto LAB_0044e981;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar4[1];
          bVar9 = bVar1 < pbVar7[1];
          if (bVar1 != pbVar7[1]) goto LAB_0044e97c;
          pbVar4 = pbVar4 + 2;
          pbVar7 = pbVar7 + 2;
        } while (bVar1 != 0);
        iVar5 = 0;
LAB_0044e981:
        if (0 < iVar5) goto LAB_0044e985;
      }
LAB_0044e9ce:
      iVar6 = iVar6 + 1;
      iVar8 = iVar8 + 0x1c;
    } while (iVar6 < iVar2);
  }
  return param_1;
}


/* ==== cmd_help_h3 @ 0044e9f0 ==== */

void cmd_help_h3(void)

{
  int iVar1;
  undefined4 *puVar2;
  int va0;
  int iVar3;
  char acStack_100 [256];
  
  iVar3 = 0;
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  va0 = 0;
  iVar1 = *(int *)(cur_dtype + 0x14);
  if (0 < iVar1) {
    do {
      puVar2 = (undefined4 *)(*(int *)(cur_dtype + 0x18) + iVar3);
      sprintf(acStack_100,s_peripheral_index__d__name__s__re_004cd588,va0,*puVar2,
              *(undefined4 *)(puVar2[0xb] + 0x28),
              *(undefined4 *)(*(int *)(cur_dtype + 0x18) + 4 + iVar3),puVar2[2]);
      out_text(acStack_100,1);
      va0 = va0 + 1;
      iVar3 = iVar3 + 0x48;
    } while (va0 < iVar1);
  }
  return;
}


/* ==== cmd_help_h4 @ 0044ea70 ==== */

void cmd_help_h4(void)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  char *fmt;
  undefined4 uVar7;
  undefined4 uVar8;
  int iStack_108;
  int iStack_104;
  char acStack_100 [256];
  
  iVar6 = 0;
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar5 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar5 = (**(code **)(cur_dtype + 0x4e8))();
  }
  iStack_104 = 1;
  iStack_108 = 0;
  uVar5 = (-(uint)((uVar5 & 0x800) != 0) & 0x10000) - 1;
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  if (0 < *(int *)(cur_dtype + 0x1c)) {
    do {
      iVar2 = *(int *)(cur_dtype + 0x20);
      uVar3 = *(uint *)(iVar2 + 0x18 + iVar6);
      iVar4 = *(int *)(iVar2 + 4 + iVar6);
      puVar1 = (undefined4 *)(iVar2 + iVar6);
      if ((uVar3 & 0x4000000) == 0) {
        uVar8 = *(undefined4 *)(*(int *)(cur_itype + 4) + iVar4 * 4);
        if ((uVar3 & 0x8000000) == 0) {
          uVar7 = *puVar1;
          fmt = s__s__lx___lx___s_004cd5d4;
        }
        else {
          uVar7 = *puVar1;
          fmt = s__s__lx___lx___s_SHARED_004cd5e4;
        }
      }
      else {
        uVar8 = *(undefined4 *)(*(int *)(cur_itype + 4) + iVar4 * 4);
        uVar7 = *puVar1;
        fmt = s__s__lx___lx___s__reserved__004cd600;
      }
      sprintf(acStack_100,fmt,uVar7,puVar1[3] & uVar5,*(uint *)(iVar2 + 0x10 + iVar6) & uVar5,uVar8)
      ;
      iStack_104 = help_page_check(iStack_104);
      out_text(acStack_100,1);
      iStack_108 = iStack_108 + 1;
      iVar6 = iVar6 + 0x2c;
    } while (iStack_108 < *(int *)(cur_dtype + 0x1c));
  }
  return;
}


/* ==== cmd_help_h1 @ 0044eb90 ==== */

void cmd_help_h1(void)

{
  int idx;
  int state;
  char *pcStack_4;
  
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  screen_hold();
  state = 1;
  out_text(s__________________Symbol_Table_Du_004cd620,1);
  idx = dbg_next_label(0,&pcStack_4);
  while ((idx != 0 && (-1 < state))) {
    state = help_page_check(state);
    out_text(pcStack_4,1);
    idx = dbg_next_label(idx,&pcStack_4);
  }
  screen_release();
  return;
}


/* ==== cmd_help_parse @ 0044ec10 ==== */

int cmd_help_parse(void)

{
  int iVar1;
  
  iVar1 = parm_keyword1(2,&DAT_004cd668);
  if (iVar1 != 0) {
    iVar1 = parm_check_too_many(3);
    if (iVar1 != 0) {
      iVar1 = 1;
      goto LAB_0044ed03;
    }
  }
  iVar1 = parm_keyword1(2,&DAT_004cd664);
  if (iVar1 != 0) {
    iVar1 = parm_check_too_many(3);
    if (iVar1 != 0) {
      iVar1 = 2;
      goto LAB_0044ed03;
    }
  }
  iVar1 = parm_keyword1(2,s_periph_004cd65c);
  if (iVar1 != 0) {
    iVar1 = parm_check_too_many(3);
    if (iVar1 != 0) {
      iVar1 = 3;
      goto LAB_0044ed03;
    }
  }
  iVar1 = parm_keyword1(2,&DAT_004cd658);
  if (iVar1 != 0) {
    iVar1 = parm_check_too_many(3);
    if (iVar1 != 0) {
      iVar1 = 4;
      goto LAB_0044ed03;
    }
  }
  iVar1 = parm_check_too_many(2);
  if (iVar1 == 0) {
    iVar1 = parm_register(2);
    if (iVar1 == 0) {
      iVar1 = parm_command_name(2);
      if (iVar1 != 0) goto LAB_0044ecee;
      iVar1 = parm_any_token(2);
      if (iVar1 != 0) goto LAB_0044ecee;
    }
    else {
LAB_0044ecee:
      iVar1 = parm_check_too_many(3);
      if (iVar1 != 0) goto LAB_0044ed01;
    }
    iVar1 = -1;
  }
  else {
LAB_0044ed01:
    iVar1 = 0;
  }
LAB_0044ed03:
  if (iVar1 == -1) {
    return 0;
  }
  return iVar1 * 8 + 0x4cc8c0;
}


/* ==== cmd_go_h0 @ 0044ed20 ==== */

void cmd_go_h0(void)

{
  char cVar1;
  long lVar2;
  int iVar3;
  int dev;
  undefined4 *puVar4;
  undefined1 *puVar5;
  int iStack_10;
  int iStack_c;
  long lStack_8;
  undefined4 uStack_4;
  
  *(undefined4 *)(cur_sim + 0x28) = 1;
  dev = 0;
  *(undefined4 *)(cur_sim + 0x2c) = 0;
  *(undefined4 *)(cur_sim + 0x34) = 0;
  iVar3 = cur_dev_index;
  if (0 < max_devices) {
    do {
      if ((*(int *)(dev_tab + dev * 4) != 0) &&
         ((*(byte *)(*(int *)(dev_tab + dev * 4) + 0x44) & 0x20) == 0)) {
        dev_select(dev);
        cdb_free_frames();
      }
      dev = dev + 1;
    } while (dev < max_devices);
  }
  dev_select(iVar3);
  if (DAT_004a93ea != 'e') {
    puVar5 = &DAT_004a93ea;
    puVar4 = &g_io_id_arg;
    cVar1 = DAT_004a93ea;
    do {
      lStack_8 = puVar4[-1];
      uStack_4 = *puVar4;
      switch(cVar1) {
      case '#':
        *(long *)(cur_sim + 0x2c) = lStack_8;
        break;
      case ':':
        *(long *)(cur_sim + 0x28) = lStack_8;
        break;
      case 'I':
        lVar2 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b294c,&iStack_c,&iStack_10);
        if ((lVar2 != 0) &&
           (iVar3 = dev_write_reg(*(int *)(cur_dev + 4),iStack_c,iStack_10,&lStack_8), iVar3 == 0))
        {
          sim_error(s_Error_writing_register_004c5550);
          return;
        }
        break;
      case 'j':
        chip_reset_regs(1,-1);
      }
      cVar1 = puVar5[1];
      puVar4 = puVar4 + 10;
      puVar5 = puVar5 + 1;
    } while (cVar1 != 'e');
  }
  show_running_banner();
  periph_reset();
  *(undefined4 *)(cur_sim + 0x40) = 1;
  return;
}


/* ==== cmd_go_parse @ 0044eee0 ==== */

undefined ** cmd_go_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(2);
  if (iVar1 == 0) {
    iVar1 = parm_number_addr(2);
    if (iVar1 == 0) {
      iVar1 = parm_keyword1(2,&DAT_004c5574);
      if (iVar1 == 0) {
        iVar1 = parm_break_number(2);
        if (iVar1 == 0) {
          iVar1 = parm_colon_number(2);
          if (iVar1 == 0) goto LAB_0044f009;
          iVar1 = parm_check_too_many(3);
          if (iVar1 == 0) goto LAB_0044f009;
        }
        else {
          iVar1 = parm_check_too_many(3);
          if (iVar1 == 0) goto LAB_0044efbf;
        }
      }
      else {
        iVar1 = parm_check_too_many(3);
        if (iVar1 == 0) {
          iVar1 = parm_break_number(3);
          if (iVar1 == 0) {
LAB_0044efbf:
            iVar1 = parm_colon_number(3);
            if (iVar1 == 0) goto LAB_0044f009;
            iVar1 = 4;
            goto LAB_0044efcf;
          }
          iVar1 = parm_check_too_many(4);
          if (iVar1 == 0) {
            iVar1 = parm_colon_number(4);
            if (iVar1 == 0) goto LAB_0044f009;
            iVar1 = 5;
            goto LAB_0044efcf;
          }
        }
      }
    }
    else {
      iVar1 = parm_check_too_many(3);
      if (iVar1 == 0) {
        iVar1 = parm_break_number(3);
        if (iVar1 == 0) goto LAB_0044efbf;
        iVar1 = parm_check_too_many(4);
        if (iVar1 == 0) {
          iVar1 = parm_colon_number(4);
          if (iVar1 == 0) goto LAB_0044f009;
          iVar1 = 5;
LAB_0044efcf:
          iVar1 = parm_check_too_many(iVar1);
          if (iVar1 != 0) {
            return &PTR_cmd_go_h0_004cd710;
          }
          goto LAB_0044f009;
        }
      }
    }
  }
  iVar2 = 0;
LAB_0044f009:
  return (undefined **)(-(uint)(iVar2 != -1) & 0x4cd710);
}


/* ==== cmd_frame_h0 @ 0044f020 ==== */

void cmd_frame_h0(void)

{
  undefined4 *extraout_EAX;
  undefined4 *extraout_EAX_00;
  undefined4 *puVar1;
  
  cdb_frame_current();
  puVar1 = extraout_EAX;
  if (extraout_EAX == (undefined4 *)0x0) {
    cdb_build_backtrace();
    cdb_frame_current();
    puVar1 = extraout_EAX_00;
    if (extraout_EAX_00 == (undefined4 *)0x0) {
      return;
    }
  }
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  cdb_print_wrapped((char *)*puVar1,&DAT_004c6554,&DAT_004c61b0,4,0);
  return;
}


/* ==== cmd_frame_h1 @ 0044f070 ==== */

void cmd_frame_h1(void)

{
  undefined4 *frame;
  int iVar1;
  undefined4 *extraout_EAX;
  undefined4 *extraout_EAX_00;
  
  cdb_frame_first();
  frame = extraout_EAX;
  iVar1 = DAT_004a96c0;
  if (extraout_EAX == (undefined4 *)0x0) {
    cdb_build_backtrace();
    cdb_frame_first();
    frame = extraout_EAX_00;
    iVar1 = DAT_004a96c0;
    if (extraout_EAX_00 == (undefined4 *)0x0) {
      return;
    }
  }
  for (; iVar1 != 0; iVar1 = iVar1 + -1) {
    if (frame == (undefined4 *)0x0) goto LAB_0044f0f5;
    frame = (undefined4 *)frame[6];
  }
  if (frame == (undefined4 *)0x0) {
LAB_0044f0f5:
    sprintf(&DAT_00502500,s_There_is_no_frame___ld_004cddac,DAT_004a96c0);
    sim_error(&DAT_00502500);
  }
  else {
    cdb_set_frame_current(frame);
    iVar1 = *(int *)(cur_sim + 0x4400);
    if (iVar1 == 0) {
      cdb_print_wrapped((char *)*frame,&DAT_004c6554,&DAT_004c61b0,4,0);
      return;
    }
    if ((iVar1 == 1) || (iVar1 == 2)) {
      win_update(0x7fff);
      return;
    }
  }
  return;
}


/* ==== cmd_frame_parse @ 0044f120 ==== */

undefined ** cmd_frame_parse(void)

{
  int iVar1;
  undefined **ppuVar2;
  
  ppuVar2 = (undefined **)0x0;
  iVar1 = parm_check_too_many(2);
  if (iVar1 != 0) {
    return &PTR_cmd_frame_h0_004cdc80;
  }
  iVar1 = parm_frame_number(2);
  if (iVar1 != 0) {
    iVar1 = parm_check_too_many(3);
    if (iVar1 != 0) {
      ppuVar2 = &PTR_cmd_frame_h1_004cdc88;
    }
  }
  return ppuVar2;
}


/* ==== cmd_evaluate_h0 @ 0044f160 ==== */

void cmd_evaluate_h0(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  char *pcVar5;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar6;
  void *node;
  void *extraout_EAX;
  void *v;
  void *frame;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined1 *puVar10;
  uint uVar11;
  uint uVar12;
  void *node_00;
  char *pcVar13;
  char *pcVar14;
  uint uStack_224;
  uint uStack_220;
  uint *puStack_21c;
  uint uStack_218;
  uint uStack_214;
  ulong uStack_20c;
  undefined4 uStack_208;
  char acStack_200 [256];
  char acStack_100 [256];
  
  uVar11 = 0;
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  uStack_224 = 0;
  puStack_21c = (uint *)0x0;
  uStack_220 = 0;
  uStack_214 = 0;
  if ((DAT_004a93ea != 'C') && ((DAT_004a93ea != 'r' || (DAT_004a93eb != 'C')))) {
    if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
      uVar2 = *(uint *)(cur_dtype + 0xc);
    }
    else {
      uVar2 = (**(code **)(cur_dtype + 0x4e8))();
    }
    uVar12 = uVar2 >> 0x1c & 1;
    uVar9 = uVar2 >> 0x19 & 1;
    uVar3 = uVar2 >> 0x1a & 1;
    uStack_218 = 0xffffffff;
    if (DAT_004a93ea != 'e') {
      puVar10 = &DAT_004a93ea;
      puVar4 = (uint *)&DAT_004a96c0;
      cVar1 = DAT_004a93ea;
      do {
        if (cVar1 == 'r') {
          uStack_218 = *puVar4;
        }
        else if ((cVar1 == 'I') || (cVar1 == 'F')) {
          puStack_21c = puVar4 + -2;
          uVar11 = *puVar4;
          uStack_224 = puVar4[5];
          uStack_220 = puVar4[1];
          uStack_214 = puVar4[2];
        }
        cVar1 = puVar10[1];
        puVar4 = puVar4 + 10;
        puVar10 = puVar10 + 1;
      } while (cVar1 != 'e');
    }
    acStack_200[0] = '\0';
    if ((uStack_218 == 0xffffffff) || (uStack_218 == 3)) {
      if ((uStack_224 & 4) == 0) {
        if ((uStack_224 & 2) == 0) {
          if (uVar12 == 0) {
            pcVar5 = s_Hex__06lx_004ce470;
            if (uVar3 == 0) {
              pcVar5 = s_Hex__08lx_004ce464;
            }
          }
          else {
            pcVar5 = s_Hex__04lx_004ce47c;
          }
          sprintf(acStack_100,pcVar5,uVar11);
        }
        else {
          if (uVar12 == 0) {
            pcVar5 = s_Hex__06lx_06lx_004ce498;
            if (uVar3 == 0) {
              pcVar5 = s_Hex__08lx_08lx_004ce488;
            }
          }
          else {
            pcVar5 = s_Hex__04lx_04lx_004ce4a8;
          }
          sprintf(acStack_100,pcVar5,uStack_220,uVar11);
        }
      }
      else {
        if ((uVar2 >> 0x18 & 1) == 0) {
          if (uVar12 == 0) {
            pcVar5 = s_Hex__02lx_06lx_06lx_004ce4d0;
            if (uVar3 == 0) {
              pcVar5 = s_Hex__08lx_08lx_08lx_004ce4b8;
            }
          }
          else {
            pcVar5 = s_Hex__02lx_04lx_04lx_004ce4e8;
          }
        }
        else {
          pcVar5 = s_Hex__01lx_04lx_04lx_004ce500;
        }
        sprintf(acStack_100,pcVar5,uStack_214,uStack_220,uVar11);
      }
      uVar12 = 0xffffffff;
      pcVar5 = acStack_100;
      do {
        pcVar14 = pcVar5;
        if (uVar12 == 0) break;
        uVar12 = uVar12 - 1;
        pcVar14 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar14;
      } while (cVar1 != '\0');
      uVar12 = ~uVar12;
      iVar7 = -1;
      pcVar5 = acStack_200;
      do {
        pcVar13 = pcVar5;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      pcVar5 = pcVar14 + -uVar12;
      pcVar14 = pcVar13 + -1;
      for (uVar8 = uVar12 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar14 = pcVar14 + 4;
      }
      for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
        *pcVar14 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar14 = pcVar14 + 1;
      }
    }
    if (((uStack_218 == 0xffffffff) || (uStack_218 == 1)) || (uStack_218 == 4)) {
      acStack_100[0] = '\0';
      if ((uStack_224 & 4) == 0) {
        if ((uStack_224 & 2) == 0) {
          uVar2 = uVar11;
          if (uStack_218 == 1) {
            if ((uStack_224 & 0x80000000) == 0) {
              if ((uStack_224 & 0x40000000) == 0) {
                if ((uStack_224 & 0x20000000) == 0) {
                  if ((uStack_224 & 0x10000000) == 0) {
                    if ((uStack_224 & 0x8000000) == 0) {
                      uVar12 = (-(uint)((uStack_224 & 0x4000000) != 0) & 0x80800000) + 0x80000000;
                    }
                    else {
                      uVar12 = 0x80000;
                    }
                  }
                  else {
                    uVar12 = 0x8000;
                  }
                }
                else {
                  uVar12 = 0x800;
                }
              }
              else {
                uVar12 = 0x80;
              }
            }
            else {
              uVar12 = 8;
            }
            if ((uVar11 & uVar12) != 0) {
              uVar2 = ~(uVar12 - 1) | uVar11;
            }
          }
          pcVar5 = s_Dec__05ld_004ce448;
          if (uStack_218 != 1) {
            pcVar5 = s_Uns__05lu_004ce43c;
          }
          sprintf(acStack_100,pcVar5,uVar2);
        }
        else if (uVar9 == 0) {
          val_to_dec_parts(uVar2,puStack_21c + 2,(long *)&uStack_20c);
          sprintf(acStack_100,s_Dec__06lu_09lu_004ce454,uStack_208,uStack_20c);
        }
        else if (uStack_218 != 0xffffffff) {
          sprintf(acStack_100,s_Hex__08lx_08lx_004ce488,uStack_220,uVar11);
        }
      }
      else if (uVar9 == 0) {
        val_to_dec_parts2(uVar2,puStack_21c + 2,&uStack_20c);
        sprintf(acStack_100,s_Dec__06lu_09lu_004ce454,uStack_208,uStack_20c);
      }
      else if (uStack_218 != 0xffffffff) {
        sprintf(acStack_100,s_Hex__08lx_08lx_08lx_004ce4b8,uStack_214,uStack_220,uVar11);
      }
      uVar2 = 0xffffffff;
      pcVar5 = acStack_100;
      do {
        pcVar14 = pcVar5;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar14 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar14;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      iVar7 = -1;
      pcVar5 = acStack_200;
      do {
        pcVar13 = pcVar5;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      pcVar5 = pcVar14 + -uVar2;
      pcVar14 = pcVar13 + -1;
      for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar14 = pcVar14 + 4;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar14 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar14 = pcVar14 + 1;
      }
    }
    if ((uStack_218 == 0xffffffff) || (uStack_218 == 2)) {
      if (uVar9 == 0) {
        if ((uStack_224 & 6) == 0) {
          pcVar5 = s_Fract__10_7g_004ce3fc;
        }
        else {
          pcVar5 = s_Fract__13_10g_004ce40c;
        }
        sprintf(acStack_100,pcVar5,*puStack_21c,puStack_21c[1]);
      }
      else if ((uStack_224 & 6) == 0) {
        cVar1 = fmt_float_exp(s__14_14s_004c6ac8,(int *)puStack_21c);
        sprintf(acStack_100,s_Float__14_14s_004ce41c,CONCAT31(extraout_var_00,cVar1));
      }
      else {
        cVar1 = fmt_float_exp(s__25_25s_004c6ad0,(int *)puStack_21c);
        sprintf(acStack_100,s_Float__25_25s_004ce42c,CONCAT31(extraout_var,cVar1));
      }
      uVar2 = 0xffffffff;
      pcVar5 = acStack_100;
      do {
        pcVar14 = pcVar5;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar14 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar14;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      iVar7 = -1;
      pcVar5 = acStack_200;
      do {
        pcVar13 = pcVar5;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      pcVar5 = pcVar14 + -uVar2;
      pcVar14 = pcVar13 + -1;
      for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar14 = pcVar14 + 4;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar14 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar14 = pcVar14 + 1;
      }
    }
    if ((((uStack_218 == 0xffffffff) && ((uStack_224 & 1) != 0)) && (uVar9 == 0)) ||
       (uStack_218 == 0)) {
      uVar2 = 0xffffffff;
      pcVar5 = &DAT_004ce3f4;
      do {
        pcVar14 = pcVar5;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar14 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar14;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      iVar7 = -1;
      pcVar5 = acStack_200;
      do {
        pcVar13 = pcVar5;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      pcVar5 = pcVar14 + -uVar2;
      pcVar14 = pcVar13 + -1;
      for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar14 = pcVar14 + 4;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar14 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar14 = pcVar14 + 1;
      }
      if ((uStack_224 & 4) != 0) {
        if (uVar9 != 0) {
          uVar2 = 0xffffffff;
          pcVar5 = (&PTR_DAT_004cde60)[(int)uStack_214 >> 0x1c & 0xf];
          do {
            pcVar14 = pcVar5;
            if (uVar2 == 0) break;
            uVar2 = uVar2 - 1;
            pcVar14 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar14;
          } while (cVar1 != '\0');
          uVar2 = ~uVar2;
          iVar7 = -1;
          pcVar5 = acStack_200;
          do {
            pcVar13 = pcVar5;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar13 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar13;
          } while (cVar1 != '\0');
          pcVar5 = pcVar14 + -uVar2;
          pcVar14 = pcVar13 + -1;
          for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar14 = pcVar14 + 4;
          }
          for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *pcVar14 = *pcVar5;
            pcVar5 = pcVar5 + 1;
            pcVar14 = pcVar14 + 1;
          }
          uVar2 = 0xffffffff;
          pcVar5 = (&PTR_DAT_004cde60)[(int)uStack_214 >> 0x18 & 0xf];
          do {
            pcVar14 = pcVar5;
            if (uVar2 == 0) break;
            uVar2 = uVar2 - 1;
            pcVar14 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar14;
          } while (cVar1 != '\0');
          uVar2 = ~uVar2;
          iVar7 = -1;
          pcVar5 = acStack_200;
          do {
            pcVar13 = pcVar5;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar13 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar13;
          } while (cVar1 != '\0');
          pcVar5 = pcVar14 + -uVar2;
          pcVar14 = pcVar13 + -1;
          for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar14 = pcVar14 + 4;
          }
          for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *pcVar14 = *pcVar5;
            pcVar5 = pcVar5 + 1;
            pcVar14 = pcVar14 + 1;
          }
          uVar2 = 0xffffffff;
          pcVar5 = (&PTR_DAT_004cde60)[(int)uStack_214 >> 0x14 & 0xf];
          do {
            pcVar14 = pcVar5;
            if (uVar2 == 0) break;
            uVar2 = uVar2 - 1;
            pcVar14 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar14;
          } while (cVar1 != '\0');
          uVar2 = ~uVar2;
          iVar7 = -1;
          pcVar5 = acStack_200;
          do {
            pcVar13 = pcVar5;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar13 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar13;
          } while (cVar1 != '\0');
          pcVar5 = pcVar14 + -uVar2;
          pcVar14 = pcVar13 + -1;
          for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar14 = pcVar14 + 4;
          }
          for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *pcVar14 = *pcVar5;
            pcVar5 = pcVar5 + 1;
            pcVar14 = pcVar14 + 1;
          }
          uVar2 = 0xffffffff;
          pcVar5 = (&PTR_DAT_004cde60)[(int)uStack_214 >> 0x10 & 0xf];
          do {
            pcVar14 = pcVar5;
            if (uVar2 == 0) break;
            uVar2 = uVar2 - 1;
            pcVar14 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar14;
          } while (cVar1 != '\0');
          uVar2 = ~uVar2;
          iVar7 = -1;
          pcVar5 = acStack_200;
          do {
            pcVar13 = pcVar5;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar13 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar13;
          } while (cVar1 != '\0');
          pcVar5 = pcVar14 + -uVar2;
          pcVar14 = pcVar13 + -1;
          for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar14 = pcVar14 + 4;
          }
          for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *pcVar14 = *pcVar5;
            pcVar5 = pcVar5 + 1;
            pcVar14 = pcVar14 + 1;
          }
          uVar2 = 0xffffffff;
          pcVar5 = (&PTR_DAT_004cde60)[(int)uStack_214 >> 0xc & 0xf];
          do {
            pcVar14 = pcVar5;
            if (uVar2 == 0) break;
            uVar2 = uVar2 - 1;
            pcVar14 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar14;
          } while (cVar1 != '\0');
          uVar2 = ~uVar2;
          iVar7 = -1;
          pcVar5 = acStack_200;
          do {
            pcVar13 = pcVar5;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar13 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar13;
          } while (cVar1 != '\0');
          pcVar5 = pcVar14 + -uVar2;
          pcVar14 = pcVar13 + -1;
          for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar14 = pcVar14 + 4;
          }
          for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *pcVar14 = *pcVar5;
            pcVar5 = pcVar5 + 1;
            pcVar14 = pcVar14 + 1;
          }
          uVar2 = 0xffffffff;
          pcVar5 = (&PTR_DAT_004cde60)[(int)uStack_214 >> 8 & 0xf];
          do {
            pcVar14 = pcVar5;
            if (uVar2 == 0) break;
            uVar2 = uVar2 - 1;
            pcVar14 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar14;
          } while (cVar1 != '\0');
          uVar2 = ~uVar2;
          iVar7 = -1;
          pcVar5 = acStack_200;
          do {
            pcVar13 = pcVar5;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar13 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar13;
          } while (cVar1 != '\0');
          pcVar5 = pcVar14 + -uVar2;
          pcVar14 = pcVar13 + -1;
          for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar14 = pcVar14 + 4;
          }
          for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *pcVar14 = *pcVar5;
            pcVar5 = pcVar5 + 1;
            pcVar14 = pcVar14 + 1;
          }
        }
        uVar2 = 0xffffffff;
        pcVar5 = (&PTR_DAT_004cde60)[(int)uStack_214 >> 4 & 0xf];
        do {
          pcVar14 = pcVar5;
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          pcVar14 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar14;
        } while (cVar1 != '\0');
        uVar2 = ~uVar2;
        iVar7 = -1;
        pcVar5 = acStack_200;
        do {
          pcVar13 = pcVar5;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar13 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar13;
        } while (cVar1 != '\0');
        pcVar5 = pcVar14 + -uVar2;
        pcVar14 = pcVar13 + -1;
        for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
          *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar14 = pcVar14 + 4;
        }
        for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *pcVar14 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar14 = pcVar14 + 1;
        }
        uVar2 = 0xffffffff;
        pcVar5 = (&PTR_DAT_004cde60)[uStack_214 & 0xf];
        do {
          pcVar14 = pcVar5;
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          pcVar14 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar14;
        } while (cVar1 != '\0');
        uVar2 = ~uVar2;
        iVar7 = -1;
        pcVar5 = acStack_200;
        do {
          pcVar13 = pcVar5;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar13 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar13;
        } while (cVar1 != '\0');
        pcVar5 = pcVar14 + -uVar2;
        pcVar14 = pcVar13 + -1;
        for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
          *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar14 = pcVar14 + 4;
        }
        for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *pcVar14 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar14 = pcVar14 + 1;
        }
      }
      if ((uStack_224 & 6) != 0) {
        if (uVar9 != 0) {
          uVar2 = 0xffffffff;
          pcVar5 = (&PTR_DAT_004cde60)[(int)uStack_220 >> 0x1c & 0xf];
          do {
            pcVar14 = pcVar5;
            if (uVar2 == 0) break;
            uVar2 = uVar2 - 1;
            pcVar14 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar14;
          } while (cVar1 != '\0');
          uVar2 = ~uVar2;
          iVar7 = -1;
          pcVar5 = acStack_200;
          do {
            pcVar13 = pcVar5;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar13 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar13;
          } while (cVar1 != '\0');
          pcVar5 = pcVar14 + -uVar2;
          pcVar14 = pcVar13 + -1;
          for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar14 = pcVar14 + 4;
          }
          for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *pcVar14 = *pcVar5;
            pcVar5 = pcVar5 + 1;
            pcVar14 = pcVar14 + 1;
          }
          uVar2 = 0xffffffff;
          pcVar5 = (&PTR_DAT_004cde60)[(int)uStack_220 >> 0x18 & 0xf];
          do {
            pcVar14 = pcVar5;
            if (uVar2 == 0) break;
            uVar2 = uVar2 - 1;
            pcVar14 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar14;
          } while (cVar1 != '\0');
          uVar2 = ~uVar2;
          iVar7 = -1;
          pcVar5 = acStack_200;
          do {
            pcVar13 = pcVar5;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar13 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar13;
          } while (cVar1 != '\0');
          pcVar5 = pcVar14 + -uVar2;
          pcVar14 = pcVar13 + -1;
          for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar14 = pcVar14 + 4;
          }
          for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *pcVar14 = *pcVar5;
            pcVar5 = pcVar5 + 1;
            pcVar14 = pcVar14 + 1;
          }
        }
        if ((uVar3 != 0) || (uVar9 != 0)) {
          uVar2 = 0xffffffff;
          pcVar5 = (&PTR_DAT_004cde60)[(int)uStack_220 >> 0x14 & 0xf];
          do {
            pcVar14 = pcVar5;
            if (uVar2 == 0) break;
            uVar2 = uVar2 - 1;
            pcVar14 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar14;
          } while (cVar1 != '\0');
          uVar2 = ~uVar2;
          iVar7 = -1;
          pcVar5 = acStack_200;
          do {
            pcVar13 = pcVar5;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar13 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar13;
          } while (cVar1 != '\0');
          pcVar5 = pcVar14 + -uVar2;
          pcVar14 = pcVar13 + -1;
          for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar14 = pcVar14 + 4;
          }
          for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *pcVar14 = *pcVar5;
            pcVar5 = pcVar5 + 1;
            pcVar14 = pcVar14 + 1;
          }
          uVar2 = 0xffffffff;
          pcVar5 = (&PTR_DAT_004cde60)[(int)uStack_220 >> 0x10 & 0xf];
          do {
            pcVar14 = pcVar5;
            if (uVar2 == 0) break;
            uVar2 = uVar2 - 1;
            pcVar14 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar14;
          } while (cVar1 != '\0');
          uVar2 = ~uVar2;
          iVar7 = -1;
          pcVar5 = acStack_200;
          do {
            pcVar13 = pcVar5;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar13 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar13;
          } while (cVar1 != '\0');
          pcVar5 = pcVar14 + -uVar2;
          pcVar14 = pcVar13 + -1;
          for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar14 = pcVar14 + 4;
          }
          for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *pcVar14 = *pcVar5;
            pcVar5 = pcVar5 + 1;
            pcVar14 = pcVar14 + 1;
          }
        }
        uVar2 = 0xffffffff;
        pcVar5 = (&PTR_DAT_004cde60)[(int)uStack_220 >> 0xc & 0xf];
        do {
          pcVar14 = pcVar5;
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          pcVar14 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar14;
        } while (cVar1 != '\0');
        uVar2 = ~uVar2;
        iVar7 = -1;
        pcVar5 = acStack_200;
        do {
          pcVar13 = pcVar5;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar13 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar13;
        } while (cVar1 != '\0');
        pcVar5 = pcVar14 + -uVar2;
        pcVar14 = pcVar13 + -1;
        for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
          *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar14 = pcVar14 + 4;
        }
        for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *pcVar14 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar14 = pcVar14 + 1;
        }
        uVar2 = 0xffffffff;
        pcVar5 = (&PTR_DAT_004cde60)[(int)uStack_220 >> 8 & 0xf];
        do {
          pcVar14 = pcVar5;
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          pcVar14 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar14;
        } while (cVar1 != '\0');
        uVar2 = ~uVar2;
        iVar7 = -1;
        pcVar5 = acStack_200;
        do {
          pcVar13 = pcVar5;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar13 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar13;
        } while (cVar1 != '\0');
        pcVar5 = pcVar14 + -uVar2;
        pcVar14 = pcVar13 + -1;
        for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
          *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar14 = pcVar14 + 4;
        }
        for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *pcVar14 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar14 = pcVar14 + 1;
        }
        uVar2 = 0xffffffff;
        pcVar5 = (&PTR_DAT_004cde60)[(int)uStack_220 >> 4 & 0xf];
        do {
          pcVar14 = pcVar5;
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          pcVar14 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar14;
        } while (cVar1 != '\0');
        uVar2 = ~uVar2;
        iVar7 = -1;
        pcVar5 = acStack_200;
        do {
          pcVar13 = pcVar5;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar13 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar13;
        } while (cVar1 != '\0');
        pcVar5 = pcVar14 + -uVar2;
        pcVar14 = pcVar13 + -1;
        for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
          *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar14 = pcVar14 + 4;
        }
        for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *pcVar14 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar14 = pcVar14 + 1;
        }
        uVar2 = 0xffffffff;
        pcVar5 = (&PTR_DAT_004cde60)[uStack_220 & 0xf];
        do {
          pcVar14 = pcVar5;
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          pcVar14 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar14;
        } while (cVar1 != '\0');
        uVar2 = ~uVar2;
        iVar7 = -1;
        pcVar5 = acStack_200;
        do {
          pcVar13 = pcVar5;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar13 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar13;
        } while (cVar1 != '\0');
        pcVar5 = pcVar14 + -uVar2;
        pcVar14 = pcVar13 + -1;
        for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
          *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar14 = pcVar14 + 4;
        }
        for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *pcVar14 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar14 = pcVar14 + 1;
        }
      }
      if (uVar9 != 0) {
        uVar2 = 0xffffffff;
        pcVar5 = (&PTR_DAT_004cde60)[(int)uVar11 >> 0x1c & 0xf];
        do {
          pcVar14 = pcVar5;
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          pcVar14 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar14;
        } while (cVar1 != '\0');
        uVar2 = ~uVar2;
        iVar7 = -1;
        pcVar5 = acStack_200;
        do {
          pcVar13 = pcVar5;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar13 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar13;
        } while (cVar1 != '\0');
        pcVar5 = pcVar14 + -uVar2;
        pcVar14 = pcVar13 + -1;
        for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
          *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar14 = pcVar14 + 4;
        }
        for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *pcVar14 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar14 = pcVar14 + 1;
        }
        uVar2 = 0xffffffff;
        pcVar5 = (&PTR_DAT_004cde60)[(int)uVar11 >> 0x18 & 0xf];
        do {
          pcVar14 = pcVar5;
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          pcVar14 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar14;
        } while (cVar1 != '\0');
        uVar2 = ~uVar2;
        iVar7 = -1;
        pcVar5 = acStack_200;
        do {
          pcVar13 = pcVar5;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar13 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar13;
        } while (cVar1 != '\0');
        pcVar5 = pcVar14 + -uVar2;
        pcVar14 = pcVar13 + -1;
        for (uVar12 = uVar2 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
          *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar14 = pcVar14 + 4;
        }
        for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *pcVar14 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar14 = pcVar14 + 1;
        }
      }
      if ((uVar3 != 0) || (uVar9 != 0)) {
        uVar2 = 0xffffffff;
        pcVar5 = (&PTR_DAT_004cde60)[(int)uVar11 >> 0x14 & 0xf];
        do {
          pcVar14 = pcVar5;
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          pcVar14 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar14;
        } while (cVar1 != '\0');
        uVar2 = ~uVar2;
        iVar7 = -1;
        pcVar5 = acStack_200;
        do {
          pcVar13 = pcVar5;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar13 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar13;
        } while (cVar1 != '\0');
        pcVar5 = pcVar14 + -uVar2;
        pcVar14 = pcVar13 + -1;
        for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
          *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar14 = pcVar14 + 4;
        }
        for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *pcVar14 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar14 = pcVar14 + 1;
        }
        uVar2 = 0xffffffff;
        pcVar5 = (&PTR_DAT_004cde60)[(int)uVar11 >> 0x10 & 0xf];
        do {
          pcVar14 = pcVar5;
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          pcVar14 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar14;
        } while (cVar1 != '\0');
        uVar2 = ~uVar2;
        iVar7 = -1;
        pcVar5 = acStack_200;
        do {
          pcVar13 = pcVar5;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar13 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar13;
        } while (cVar1 != '\0');
        pcVar5 = pcVar14 + -uVar2;
        pcVar14 = pcVar13 + -1;
        for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
          *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar14 = pcVar14 + 4;
        }
        for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *pcVar14 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar14 = pcVar14 + 1;
        }
      }
      uVar2 = 0xffffffff;
      pcVar5 = (&PTR_DAT_004cde60)[(int)uVar11 >> 0xc & 0xf];
      do {
        pcVar14 = pcVar5;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar14 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar14;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      iVar7 = -1;
      pcVar5 = acStack_200;
      do {
        pcVar13 = pcVar5;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      pcVar5 = pcVar14 + -uVar2;
      pcVar14 = pcVar13 + -1;
      for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar14 = pcVar14 + 4;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar14 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar14 = pcVar14 + 1;
      }
      uVar2 = 0xffffffff;
      pcVar5 = (&PTR_DAT_004cde60)[(int)uVar11 >> 8 & 0xf];
      do {
        pcVar14 = pcVar5;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar14 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar14;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      iVar7 = -1;
      pcVar5 = acStack_200;
      do {
        pcVar13 = pcVar5;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      pcVar5 = pcVar14 + -uVar2;
      pcVar14 = pcVar13 + -1;
      for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar14 = pcVar14 + 4;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar14 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar14 = pcVar14 + 1;
      }
      uVar2 = 0xffffffff;
      pcVar5 = (&PTR_DAT_004cde60)[(int)uVar11 >> 4 & 0xf];
      do {
        pcVar14 = pcVar5;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar14 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar14;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      iVar7 = -1;
      pcVar5 = acStack_200;
      do {
        pcVar13 = pcVar5;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      pcVar5 = pcVar14 + -uVar2;
      pcVar14 = pcVar13 + -1;
      for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar14 = pcVar14 + 4;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar14 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar14 = pcVar14 + 1;
      }
      uVar2 = 0xffffffff;
      pcVar5 = (&PTR_DAT_004cde60)[uVar11 & 0xf];
      do {
        pcVar14 = pcVar5;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar14 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar14;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      iVar7 = -1;
      pcVar5 = acStack_200;
      do {
        pcVar13 = pcVar5;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      pcVar5 = pcVar14 + -uVar2;
      pcVar14 = pcVar13 + -1;
      for (uVar11 = uVar2 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
        *(undefined4 *)pcVar14 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar14 = pcVar14 + 4;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar14 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar14 = pcVar14 + 1;
      }
    }
    log_echo(acStack_200,1);
    return;
  }
  if (DAT_004a93ea == 'r') {
    iVar6 = 3;
    iVar7 = DAT_004a96c0;
  }
  else {
    iVar7 = -1;
    iVar6 = 2;
  }
  parse_c_expression(&g_cmdline + (&g_tok_start)[iVar6]);
  if (node == (void *)0x0) {
    return;
  }
  cdb_save_counters(iVar7);
  iVar6 = eval_tree(node);
  if (iVar6 == 1) {
    cdb_saved_pop();
    node_00 = extraout_EAX;
    if (extraout_EAX != (void *)0x0) {
      v = *(void **)((int)extraout_EAX + 0x10);
      goto LAB_0044fc2c;
    }
  }
  else {
    node_00 = node;
    if (iVar6 == 2) {
      return;
    }
  }
  v = (void *)0x0;
LAB_0044fc2c:
  if (v != (void *)0x0) {
    cdb_print_typed_value(iVar7,v);
    cdb_frame_current();
    if (frame != (void *)0x0) {
      cdb_frame_refresh_text(frame);
    }
  }
  cdb_free_expr(node_00);
  return;
}


/* ==== cmd_evaluate_parse @ 0044fc60 ==== */

undefined ** cmd_evaluate_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(3);
  if (iVar1 == 0) {
    iVar1 = parm_kw_r_radix(2);
    if (iVar1 != 0) {
      iVar1 = parm_number_expr(3);
      if (iVar1 != 0) {
        iVar1 = parm_check_too_many(4);
        if (iVar1 != 0) goto LAB_0044fd14;
      }
    }
    iVar1 = parm_kw_r_radix(2);
    if (iVar1 == 0) goto LAB_0044fd16;
    iVar1 = parm_brace_block(3);
    if (iVar1 == 0) goto LAB_0044fd16;
    iVar1 = parm_check_too_many(4);
    if (iVar1 == 0) goto LAB_0044fd16;
    iVar1 = parm_c_expr(3);
    if (iVar1 == 0) goto LAB_0044fd16;
  }
  else {
    iVar1 = parm_number_expr(2);
    if (iVar1 == 0) {
      iVar1 = parm_brace_block(2);
      if (iVar1 != 0) {
        iVar1 = parm_c_expr(2);
        if (iVar1 != 0) {
          return &PTR_cmd_evaluate_h0_004cdea0;
        }
      }
      goto LAB_0044fd16;
    }
  }
LAB_0044fd14:
  iVar2 = 0;
LAB_0044fd16:
  return (undefined **)(-(uint)(iVar2 != -1) & 0x4cdea0);
}


/* ==== cmd_down_h0 @ 0044fd30 ==== */

void cmd_down_h0(void)

{
  uint uVar1;
  undefined4 *extraout_EAX;
  undefined4 *extraout_EAX_00;
  int iVar2;
  
  cdb_frame_current();
  DAT_00502700 = extraout_EAX;
  if (extraout_EAX == (undefined4 *)0x0) {
    cdb_build_backtrace();
    cdb_frame_current();
    DAT_00502700 = extraout_EAX_00;
    if (extraout_EAX_00 == (undefined4 *)0x0) {
      return;
    }
  }
  iVar2 = parm_check_too_many(2);
  if (iVar2 == 0) {
    if ((g_io_id_arg != 0) || (uVar1 = DAT_004a96c0, 0x7fff < DAT_004a96c0)) {
      DAT_004a96c0 = DAT_004a96c0 | 0xffff0000;
      DAT_00502700 = (undefined4 *)0x0;
      uVar1 = DAT_004a96c0;
    }
    for (; uVar1 != 0; uVar1 = uVar1 - 1) {
      if (DAT_00502700 == (undefined4 *)0x0) goto LAB_0044fe0a;
      DAT_00502700 = (undefined4 *)DAT_00502700[5];
    }
  }
  else {
    DAT_00502700 = (undefined4 *)DAT_00502700[5];
  }
  if (DAT_00502700 == (undefined4 *)0x0) {
LAB_0044fe0a:
    iVar2 = parm_check_too_many(2);
    if (iVar2 != 0) {
      sim_error(s_Can_t_go_down_any_further_004ce66c);
      return;
    }
    sprintf(&DAT_00502600,s_Can_t_go_down__ld_times_004ce654,DAT_004a96c0);
    sim_error(&DAT_00502600);
  }
  else {
    cdb_set_frame_current(DAT_00502700);
    iVar2 = *(int *)(cur_sim + 0x4400);
    if (iVar2 == 0) {
      cdb_print_wrapped((char *)*DAT_00502700,&DAT_004c6554,&DAT_004c61b0,4,0);
      return;
    }
    if ((iVar2 == 1) || (iVar2 == 2)) {
      win_update(0x7fff);
      return;
    }
  }
  return;
}


/* ==== cmd_down_parse @ 0044fe50 ==== */

uint cmd_down_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(2);
  if (iVar1 == 0) {
    iVar1 = parm_number_or_end(2);
    if (iVar1 == 0) goto LAB_0044fe80;
    iVar1 = parm_check_too_many(3);
    if (iVar1 == 0) goto LAB_0044fe80;
  }
  iVar2 = 0;
LAB_0044fe80:
  return -(uint)(iVar2 != -1) & 0x4ce548;
}


/* ==== cmd_display_h1 @ 0044fe90 ==== */

void cmd_display_h1(void)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uStack_18;
  uint uStack_14;
  uint uStack_10;
  ushort *puStack_c;
  char *pcStack_8;
  uint uStack_4;
  
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar1 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar1 = (**(code **)(cur_dtype + 0x4e8))();
  }
  uStack_4 = (-(uint)((uVar1 & 0x800) != 0) & 0x10000) - 1;
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  iVar7 = *(int *)(cur_dtype + 0x1c);
  if (iVar7 != 0) {
    iVar5 = 0;
    do {
      rangemap_set((void *)(*(int *)(cur_sim + 4) + 4 + iVar5),0,0xffffffff,-1,0);
      iVar5 = iVar5 + 300;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  iVar7 = *(int *)(cur_dtype + 0x14);
  iVar6 = 0;
  iVar5 = cur_dtype;
  if (0 < iVar7) {
    iVar8 = 0;
    do {
      iVar3 = *(int *)(*(int *)(*(int *)(iVar5 + 0x18) + 0x2c + iVar8) + 0x28);
      puVar2 = *(uint **)(*(int *)(cur_sim + 8) + 4 + iVar6 * 8);
      if (0 < iVar3) {
        do {
          iVar3 = iVar3 + -1;
          *puVar2 = *puVar2 & 0xfffff7ff;
          puVar2 = puVar2 + 1;
          iVar5 = cur_dtype;
        } while (iVar3 != 0);
      }
      iVar6 = iVar6 + 1;
      iVar8 = iVar8 + 0x48;
    } while (iVar6 < iVar7);
  }
  iVar7 = (int)DAT_004a93ea;
  if (iVar7 != 0x65) {
    pcStack_8 = &DAT_004a93ea;
    puStack_c = (ushort *)&DAT_004a96dc;
    do {
      puVar4 = puStack_c;
      if (iVar7 == 0x75) break;
      switch(iVar7) {
      case 0x47:
        uStack_14 = *(uint *)(puStack_c + -10);
        uStack_18 = (uint)*puStack_c;
        uStack_10 = (uint)puStack_c[-2];
        puStack_c = (ushort *)*(uint *)(puStack_c + -0xe);
        while( true ) {
          iVar7 = *(int *)(*(int *)(cur_sim + 8) + 4 + uStack_18 * 8);
          if ((*(byte *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x18) + 0x2c + uStack_18 * 0x48) + 0x2c)
                         + 0x10 + uStack_10 * 0x1c) & 0x10) == 0) {
            *(uint *)(iVar7 + uStack_10 * 4) = *(uint *)(iVar7 + uStack_10 * 4) | 0x800;
            iVar5 = cur_dtype;
          }
          if ((uStack_18 == uStack_14) && ((ushort *)uStack_10 == puStack_c)) break;
          reg_next((int *)&uStack_10,(int *)&uStack_18);
          iVar5 = cur_dtype;
        }
        break;
      case 0x67:
        uStack_18 = (uint)*puStack_c;
        iVar7 = *(int *)(*(int *)(cur_sim + 8) + 4 + uStack_18 * 8);
        uVar1 = (uint)puStack_c[-2];
        if ((*(byte *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x18) + 0x2c + uStack_18 * 0x48) + 0x2c) +
                       0x10 + uVar1 * 0x1c) & 0x10) == 0) {
          *(uint *)(iVar7 + uVar1 * 4) = *(uint *)(iVar7 + uVar1 * 4) | 0x800;
          iVar5 = cur_dtype;
        }
        break;
      case 0x70:
        *(undefined4 *)(puStack_c + -0xc) = *(undefined4 *)(puStack_c + -0xe);
      case 0x50:
      case 0x58:
        uVar1 = *(uint *)(*(int *)(iVar5 + 0x20) + 0x20 + (uint)*puStack_c * 0x2c) & uStack_4;
        rangemap_set((void *)(*(int *)(cur_sim + 4) + 4 + (uint)*puStack_c * 300),
                     *(uint *)(puStack_c + -0xe) & uVar1,*(uint *)(puStack_c + -0xc) & uVar1,uVar1,1
                    );
        iVar5 = cur_dtype;
        break;
      case 0x76:
        uVar1 = (uint)*puStack_c;
        uStack_18 = uVar1;
        uStack_14 = uVar1;
        if (uVar1 == *(uint *)(iVar5 + 0x14)) {
          uStack_18 = 0;
          uVar1 = *(int *)(iVar5 + 0x14) - 1;
          uStack_14 = uVar1;
          memtag_rebuild();
          iVar5 = cur_dtype;
        }
        iVar7 = *(int *)(iVar5 + 0x14);
        if (uStack_18 == iVar7 + 1U) {
          uStack_18 = 1;
          iVar7 = *(int *)(iVar5 + 0x14);
          uVar1 = iVar7 - 1;
          uStack_14 = uVar1;
        }
        if (uStack_18 == iVar7 + 2U) {
          uVar1 = 0;
          uStack_18 = 0;
          uStack_14 = 0;
        }
        if ((int)uStack_18 <= (int)uVar1) {
          do {
            puVar2 = *(uint **)(*(int *)(cur_sim + 8) + 4 + uStack_18 * 8);
            iVar7 = *(int *)(*(int *)(*(int *)(iVar5 + 0x18) + 0x2c + uStack_18 * 0x48) + 0x28);
            if (0 < iVar7) {
              iVar6 = 0;
              do {
                if ((*(byte *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x18) + 0x2c + uStack_18 * 0x48) +
                                       0x2c) + 0x10 + iVar6) & 0x10) == 0) {
                  *puVar2 = *puVar2 | 0x800;
                  iVar5 = cur_dtype;
                }
                iVar6 = iVar6 + 0x1c;
                puVar2 = puVar2 + 1;
                iVar7 = iVar7 + -1;
                puVar4 = puStack_c;
                uVar1 = uStack_14;
              } while (iVar7 != 0);
            }
            uStack_18 = uStack_18 + 1;
          } while ((int)uStack_18 <= (int)uVar1);
        }
      }
      puStack_c = puVar4 + 0x14;
      pcStack_8 = pcStack_8 + 1;
      iVar7 = (int)*pcStack_8;
    } while (iVar7 != 0x65);
  }
  display_all(0);
  return;
}


/* ==== cmd_display_h3 @ 00450550 ==== */

void cmd_display_h3(void)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar1 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar1 = (**(code **)(cur_dtype + 0x4e8))();
  }
  uVar7 = DAT_004a96c0;
  uVar3 = *(uint *)(DAT_004a96c0 * 4 + 0x4ce790);
  iVar8 = 0;
  iVar6 = *(int *)(cur_dtype + 0x14);
  iVar4 = cur_dtype;
  if (0 < iVar6) {
    iVar9 = 0;
    do {
      iVar5 = *(int *)(*(int *)(*(int *)(iVar4 + 0x18) + 0x2c + iVar9) + 0x28);
      puVar2 = *(uint **)(*(int *)(cur_sim + 8) + 4 + iVar8 * 8);
      if (0 < iVar5) {
        do {
          iVar5 = iVar5 + -1;
          *puVar2 = *puVar2 & 0xffffff8f | uVar3;
          puVar2 = puVar2 + 1;
          iVar4 = cur_dtype;
        } while (iVar5 != 0);
      }
      iVar8 = iVar8 + 1;
      iVar9 = iVar9 + 0x48;
    } while (iVar8 < iVar6);
  }
  if (uVar7 == 1) {
    uVar7 = 3;
  }
  iVar6 = *(int *)(iVar4 + 0x1c);
  if (0 < iVar6) {
    iVar9 = 0;
    iVar8 = 0;
    do {
      uVar3 = *(uint *)(*(int *)(iVar4 + 0x20) + 0x20 + iVar8) &
              (-(uint)((uVar1 & 0x800) != 0) & 0x10000) - 1;
      rangemap_set((void *)(*(int *)(cur_sim + 4) + iVar9),0,uVar3,uVar3,
                   -(uint)((*(uint *)(*(int *)(iVar4 + 0x20) + iVar8 + 0x18) & 0x4000) != 0) & uVar7
                  );
      iVar8 = iVar8 + 0x2c;
      iVar9 = iVar9 + 300;
      iVar6 = iVar6 + -1;
      iVar4 = cur_dtype;
    } while (iVar6 != 0);
  }
  return;
}


/* ==== cmd_display_h4 @ 00450650 ==== */

void cmd_display_h4(void)

{
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  log_echo(banner_ptr,1);
  return;
}


/* ==== cmd_display_h5 @ 00450680 ==== */

void cmd_display_h5(void)

{
  *(undefined4 *)(cur_sim + 0x3c34) = 1;
  return;
}


/* ==== cmd_display_h6 @ 00450690 ==== */

void cmd_display_h6(void)

{
  *(undefined4 *)(cur_sim + 0x3c34) = 0;
  return;
}


/* ==== cmd_display_h0 @ 004506a0 ==== */

void cmd_display_h0(void)

{
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  display_refresh(0);
  return;
}


/* ==== cmd_display_parse @ 004506c0 ==== */

undefined ** cmd_display_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(2);
  if (iVar1 == 0) {
    iVar1 = parm_keyword1(2,&DAT_004c73d8);
    if (iVar1 == 0) {
      iVar1 = parm_keyword1(2,&DAT_004a8690);
      if (iVar1 == 0) {
        iVar1 = parm_kw_d_onoff(2);
        if (iVar1 == 0) {
          iVar1 = parm_addr_list(2);
          if (iVar1 != 0) {
            iVar2 = 1;
          }
        }
        else {
          iVar1 = parm_check_too_many(3);
          if (iVar1 == 0) {
            iVar1 = parm_addr_list(3);
            if (iVar1 != 0) {
              iVar2 = 2;
            }
          }
          else {
            iVar2 = 3;
          }
        }
      }
      else {
        iVar1 = parm_check_too_many(3);
        if (iVar1 == 0) {
          iVar1 = parm_keyword1(3,&DAT_004c6aec);
          if (iVar1 != 0) {
            iVar1 = parm_check_too_many(4);
            if (iVar1 != 0) {
              iVar2 = 6;
            }
          }
        }
        else {
          iVar2 = 5;
        }
      }
    }
    else {
      iVar1 = parm_check_too_many(3);
      if (iVar1 != 0) {
        iVar2 = 4;
      }
    }
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_display_h0_004ce7a8 + iVar2 * 2;
}


/* ==== cmd_disassemble_h0 @ 004507c0 ==== */

void cmd_disassemble_h0(void)

{
  char cVar1;
  code *pcVar2;
  bool bVar3;
  bool bVar4;
  uint uVar5;
  uint arg;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  ulong addr;
  char *pcVar11;
  bool bVar12;
  bool bVar13;
  int iStack_14c;
  ulong uStack_148;
  int iStack_144;
  int iStack_13c;
  undefined1 auStack_128 [40];
  char acStack_100 [256];
  
  bVar3 = false;
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar5 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar5 = (**(code **)(cur_dtype + 0x4e8))();
  }
  iStack_13c = 0;
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  arg = (uint)(DAT_004a93ea == 'j');
  cVar1 = (&DAT_004a93ea)[arg];
  if (cVar1 == 'e') {
    if (*(int *)(cur_sim + 0x24) == 0) {
      uStack_148 = 0;
      addr = *(ulong *)(cur_dev + 0x1c);
      *(undefined4 *)(cur_sim + 0x24) = 0;
    }
    else {
      uStack_148 = *(ulong *)(cur_sim + 0x20);
      addr = *(ulong *)(cur_sim + 0x10);
    }
    more_line_count = 0;
    uVar6 = memmap_find(uStack_148,addr);
    iStack_14c = text_rows + -1;
    uVar10 = addr - 1;
    bVar3 = true;
  }
  else {
    iVar8 = (arg + 2) * 0x28;
    uVar6 = (uint)*(ushort *)(&DAT_004a968c + iVar8);
    uStack_148 = *(ulong *)(*(int *)(cur_dtype + 0x20) + 4 + uVar6 * 0x2c);
    *(ulong *)(cur_sim + 0x20) = uStack_148;
    addr = *(ulong *)(&g_tok_val + iVar8);
    if (cVar1 == 'p') {
      more_line_count = 0;
      iStack_14c = text_rows + -1;
      uVar10 = addr - 1;
      bVar3 = true;
    }
    else if (cVar1 == 'X') {
      uVar10 = addr - 2;
      iStack_14c = (*(int *)(&DAT_004a9674 + iVar8) - addr) + 1;
    }
    else {
      uVar10 = *(uint *)(&DAT_004a9674 + iVar8);
      iStack_14c = -1;
    }
  }
  uVar6 = *(uint *)(*(int *)(cur_dtype + 0x20) + 0x20 + uVar6 * 0x2c) &
          (-(uint)((uVar5 & 0x800) != 0) & 0x10000) - 1;
  pcVar2 = (code *)(*(undefined4 **)(cur_dtype + 0x28))[5];
  uVar5 = uVar6 & addr;
  if (pcVar2 == (code *)0x0) {
    iStack_144 = (*(code *)**(undefined4 **)(cur_dtype + 0x28))(uStack_148,uVar5,auStack_128);
  }
  else {
    iStack_144 = (*pcVar2)(uStack_148,uVar5,auStack_128,arg);
  }
  if (iStack_144 == 0) {
    iStack_144 = 1;
  }
  bVar4 = false;
  iVar8 = iStack_14c;
  while (iVar8 != 0) {
    iStack_14c = iVar8 + -1;
    iVar7 = disasm_line(uStack_148,uVar6 & addr,acStack_100,arg);
    uVar9 = 0xffffffff;
    pcVar11 = acStack_100;
    do {
      if (uVar9 == 0) break;
      uVar9 = uVar9 - 1;
      cVar1 = *pcVar11;
      pcVar11 = pcVar11 + 1;
    } while (cVar1 != '\0');
    bVar12 = screen_cols - 1U < ~uVar9 - 1;
    if (((bVar12) && (bVar3)) && (bVar13 = iStack_14c == 0, iStack_14c = iVar8 + -2, bVar13)) break;
    log_echo(acStack_100,1);
    if (bVar12) {
      log_echo(acStack_100 + screen_cols,1);
    }
    uVar9 = iStack_144 * iVar7 + addr & uVar6;
    if (uVar9 < addr) {
      bVar4 = true;
    }
    if (uVar10 < uVar5) {
LAB_00450a24:
      if ((bVar4) && (uVar10 < uVar9)) break;
    }
    else {
      if (uVar10 < uVar9) break;
      if (uVar10 < uVar5) goto LAB_00450a24;
    }
    if (((addr == uVar10) || ((iVar7 == 2 && (addr == uVar10 - iStack_144)))) ||
       ((iVar7 == 3 && (addr == uVar10 + iStack_144 * -2)))) break;
    iStack_13c = iStack_13c + 1;
    if (text_rows <= iStack_13c) {
      iStack_13c = 0;
      screen_flush();
      screen_hold();
      iVar8 = abort_check();
      if (iVar8 != 0) break;
    }
    if (iVar7 < 1) {
      iVar7 = 1;
    }
    addr = addr + iStack_144 * iVar7;
    iVar8 = iStack_14c;
  }
  *(ulong *)(cur_sim + 0x10) = addr;
  *(undefined4 *)(cur_sim + 0x24) = 1;
  return;
}


/* ==== cmd_disassemble_parse @ 00450ac0 ==== */

undefined ** cmd_disassemble_parse(void)

{
  int iVar1;
  int iVar2;
  int idx;
  
  iVar1 = parm_keyword1(2,&DAT_004b29b0);
  idx = (iVar1 != 0) + 2;
  iVar2 = parm_check_too_many(idx);
  if (iVar2 != 0) {
    return &PTR_cmd_disassemble_h0_004cf1f0;
  }
  iVar2 = parm_address_spec(idx);
  if ((iVar2 != 0) && (iVar1 = parm_check_too_many((iVar1 != 0) + 3), iVar1 != 0)) {
    return &PTR_cmd_disassemble_h0_004cf1f0;
  }
  return (undefined **)0x0;
}


/* ==== cmd_device_h0 @ 00450b10 ==== */

void cmd_device_h0(void)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined *puVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int va0;
  char *pcVar9;
  char *pcVar10;
  char *pcVar11;
  char acStack_200 [24];
  undefined1 uStack_1e8;
  char acStack_100 [256];
  
  va0 = 0;
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  log_echo(s_DEVICE_STATUS_TYPE_DEVICE_STATUS_004cfa74,1);
  log_echo(s__________________________________004cfa44,1);
  iVar3 = (max_devices + 1) / 2;
  iVar8 = iVar3;
  if (0 < iVar3) {
    do {
      piVar2 = *(int **)(dev_tab + va0 * 4);
      if (piVar2 == (int *)0x0) {
        sprintf(acStack_200,s_dv_02d_unused_004cfa0c,va0);
      }
      else {
        puVar4 = &DAT_004c6aec;
        if ((*(byte *)(piVar2 + 0x11) & 0x20) == 0) {
          puVar4 = &DAT_004cfa40;
        }
        sprintf(acStack_200,s_dv_02d__s__s_004cfa28,va0,puVar4,
                **(undefined4 **)(chiptype_tab + *piVar2 * 4));
      }
      if (iVar8 < max_devices) {
        piVar2 = *(int **)(dev_tab + iVar8 * 4);
        if (piVar2 == (int *)0x0) {
          sprintf(acStack_100,s_dv_02d_unused_004cf9e8,iVar8);
        }
        else {
          puVar4 = &DAT_004c6aec;
          if ((*(byte *)(piVar2 + 0x11) & 0x20) == 0) {
            puVar4 = &DAT_004cfa40;
          }
          sprintf(acStack_100,s_dv_02d__s__s_004cf9f8,iVar8,puVar4,
                  **(undefined4 **)(chiptype_tab + *piVar2 * 4));
        }
      }
      else {
        acStack_100[0] = '\0';
      }
      uVar5 = 0xffffffff;
      pcVar9 = acStack_100;
      do {
        pcVar11 = pcVar9;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      uStack_1e8 = 0;
      iVar6 = -1;
      pcVar9 = acStack_200;
      do {
        pcVar10 = pcVar9;
        if (iVar6 == 0) break;
        iVar6 = iVar6 + -1;
        pcVar10 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar10;
      } while (cVar1 != '\0');
      pcVar9 = pcVar11 + -uVar5;
      pcVar11 = pcVar10 + -1;
      for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar11 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar11 = pcVar11 + 1;
      }
      log_echo(acStack_200,1);
      va0 = va0 + 1;
      iVar8 = iVar8 + 1;
    } while (va0 < iVar3);
  }
  log_echo(&empty_str,1);
  log_echo(s___Possible_device_types___004cf9cc,1);
  iVar8 = num_chiptypes;
  iVar3 = 0;
  if (0 < num_chiptypes) {
    do {
      if (*(undefined4 **)(chiptype_tab + iVar3 * 4) == (undefined4 *)0x0) {
        return;
      }
      log_echo((char *)**(undefined4 **)(chiptype_tab + iVar3 * 4),1);
      iVar3 = iVar3 + 1;
    } while (iVar3 < iVar8);
  }
  return;
}


/* ==== cmd_device_h1 @ 00450cd0 ==== */

void cmd_device_h1(void)

{
  int dev;
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = cur_dev;
  uVar1 = cur_sim;
  dev = DAT_004a96c0;
  if (*(int *)(dev_state_tab + DAT_004a96c0 * 4) == 0) {
    iVar3 = dev_create(DAT_004a96c0,(char *)**(undefined4 **)chiptype_tab);
    if (iVar3 == 0) {
      cur_sim = uVar1;
      cur_dev = uVar2;
      return;
    }
  }
  if (*(int *)(dev_state_tab + cur_dev_index * 4) != 0) {
    *(undefined4 *)(*(int *)(dev_state_tab + cur_dev_index * 4) + 0x40) = 1;
    *(undefined4 *)(*(int *)(dev_state_tab + cur_dev_index * 4) + 0x34) = 0;
    *(undefined4 *)(*(int *)(dev_state_tab + cur_dev_index * 4) + 0x28) = 1;
  }
  cur_dev_index = dev;
  run_dev_index = dev;
  *(undefined4 *)(*(int *)(dev_state_tab + dev * 4) + 0x40) = 0;
  scrollback_end(dev);
  return;
}


/* ==== cmd_device_h3 @ 00450d90 ==== */

void cmd_device_h3(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar2 = cur_dev;
  uVar1 = cur_sim;
  if (*(int *)(dev_state_tab + DAT_004a96c0 * 4) == 0) {
    dev_create(DAT_004a96c0,(char *)**(undefined4 **)chiptype_tab);
    cur_dev = uVar2;
    cur_sim = uVar1;
    return;
  }
  *(uint *)(*(int *)(dev_tab + DAT_004a96c0 * 4) + 0x44) =
       *(uint *)(*(int *)(dev_tab + DAT_004a96c0 * 4) + 0x44) & 0xffffffdf;
  return;
}


/* ==== cmd_device_h2 @ 00450df0 ==== */

void cmd_device_h2(void)

{
  uint *puVar1;
  
  if (*(int *)(dev_tab + DAT_004a96c0 * 4) != 0) {
    puVar1 = (uint *)(*(int *)(dev_tab + DAT_004a96c0 * 4) + 0x44);
    *puVar1 = *puVar1 | 0x20;
  }
  return;
}


/* ==== cmd_device_h5 @ 00450e10 ==== */

void cmd_device_h5(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = cur_dev;
  uVar2 = cur_sim;
  iVar1 = DAT_004a96c0;
  iVar4 = DAT_004a96c0;
  if (cur_dev != 0) {
    iVar4 = *(int *)(cur_dev + 4);
  }
  dev_create(DAT_004a96c0,(char *)**(undefined4 **)(chiptype_tab + DAT_004a96e8 * 4));
  if (iVar1 != iVar4) {
    cur_sim = uVar2;
    cur_dev = iVar3;
  }
  return;
}


/* ==== cmd_device_h4 @ 00450e70 ==== */

void cmd_device_h4(void)

{
  void *p;
  void *dev;
  int *piVar1;
  
  p = DAT_004a96c0;
  if (DAT_004a96c0 == cur_dev_index) {
    dev = (void *)0x0;
    piVar1 = (int *)dev_state_tab;
    if (0 < max_devices) {
      do {
        if ((*piVar1 != 0) && (dev != DAT_004a96c0)) break;
        dev = (void *)((int)dev + 1);
        piVar1 = piVar1 + 1;
      } while ((int)dev < max_devices);
    }
    if (max_devices <= (int)dev) {
      out_text(s__Can_t_delete_the_only_device___004cfaa4,1);
      return;
    }
    cur_dev_index = dev;
    run_dev_index = dev;
    *(undefined4 *)(*(int *)(dev_state_tab + (int)dev * 4) + 0x40) = 0;
    scrollback_end((int)dev);
  }
  if (gui_mode != 0) {
    dsp_free_ext(p);
  }
  dev_destroy((int)p);
  return;
}


/* ==== cmd_device_parse @ 00450f00 ==== */

undefined ** cmd_device_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(2);
  if (iVar1 == 0) {
    iVar1 = parm_device_name(2);
    if (iVar1 != 0) {
      iVar1 = parm_check_too_many(3);
      if (iVar1 == 0) {
        iVar1 = parm_check_too_many(4);
        if (iVar1 != 0) {
          iVar1 = parm_keyword1(3,&DAT_004c6aec);
          if (iVar1 == 0) {
            iVar1 = parm_keyword1(3,&DAT_004cfac4);
            if (iVar1 == 0) {
              iVar1 = parm_keyword1(3,&DAT_004a86b0);
              if (iVar1 == 0) {
                iVar1 = parm_device_type(3);
                if (iVar1 != 0) {
                  iVar2 = 5;
                }
              }
              else {
                iVar2 = 4;
              }
            }
            else {
              iVar2 = 3;
            }
          }
          else {
            iVar2 = 2;
          }
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
  if (iVar2 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_device_h0_004cf638 + iVar2 * 2;
}


/* ==== cmd_copy_h0 @ 00450fd0 ==== */

void cmd_copy_h0(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar3 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar3 = (**(code **)(cur_dtype + 0x4e8))();
  }
  uVar8 = DAT_004a96c0;
  uVar6 = DAT_004a96c0;
  if (DAT_004a93ea != 'p') {
    uVar6 = g_io_id_arg;
  }
  iVar4 = *(int *)(cur_dtype + 0x20);
  uVar1 = *(undefined4 *)(iVar4 + 4 + (DAT_004a96dc & 0xffff) * 0x2c);
  uVar2 = *(undefined4 *)(iVar4 + 4 + (DAT_004a9704 & 0xffff) * 0x2c);
  uVar7 = *(uint *)(iVar4 + (DAT_004a96dc & 0xffff) * 0x2c + 0x20) &
          (-(uint)((uVar3 & 0x800) != 0) & 0x10000) - 1;
  uStack_4 = 0;
  uStack_8 = 0;
  uVar3 = DAT_004a96e8;
  if (DAT_004a96e8 <= DAT_004a96c0) {
    while( true ) {
      (*(code *)**(undefined4 **)(cur_dtype + 0x28))(uVar1,uVar8,&uStack_8);
      (**(code **)(*(int *)(cur_dtype + 0x28) + 4))(uVar2,uVar3,&uStack_8);
      if (((uVar8 & 0x1ff) == 0) && (iVar4 = abort_check(), iVar4 != 0)) break;
      if ((uVar7 & uVar8) == uVar6) {
        return;
      }
      uVar8 = uVar8 + 1;
      uVar3 = uVar3 + 1;
    }
    return;
  }
  iVar4 = DAT_004a96e8 + (uVar6 - DAT_004a96c0);
  while( true ) {
    (*(code *)**(undefined4 **)(cur_dtype + 0x28))(uVar1,uVar6,&uStack_8);
    (**(code **)(*(int *)(cur_dtype + 0x28) + 4))(uVar2,iVar4,&uStack_8);
    if (((uVar6 & 0x1ff) == 0) && (iVar5 = abort_check(), iVar5 != 0)) break;
    if (uVar8 == (uVar7 & uVar6)) {
      return;
    }
    uVar6 = uVar6 - 1;
    iVar4 = iVar4 + -1;
  }
  return;
}


/* ==== cmd_copy_parse @ 00451120 ==== */

undefined ** cmd_copy_parse(void)

{
  int iVar1;
  
  iVar1 = parm_address_spec(2);
  if (iVar1 != 0) {
    iVar1 = parm_match_space_cur(3);
    if (iVar1 != 0) {
      iVar1 = parm_check_too_many(4);
      if (iVar1 != 0) {
        return &PTR_cmd_copy_h0_004cfb20;
      }
    }
  }
  return (undefined **)0x0;
}


/* ==== cmd_change_h0 @ 00451160 ==== */

void cmd_change_h0(void)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  void *node;
  uint uVar6;
  undefined4 va0;
  uint uVar7;
  byte *pbVar8;
  bool bVar9;
  char *pcVar10;
  uint uStack_518;
  uint uStack_514;
  uint uStack_510;
  uint uStack_50c;
  int iStack_508;
  int iStack_504;
  byte abStack_500 [256];
  char acStack_400 [256];
  char acStack_300 [256];
  char acStack_200 [256];
  byte abStack_100 [256];
  
  iStack_508 = *(int *)(cur_dev + 0x1c);
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uStack_510 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uStack_510 = (**(code **)(cur_dtype + 0x4e8))();
  }
  uVar7 = uStack_510 >> 7 & 1;
  DAT_00502704 = (&PTR_s_Fract_004cfe38)[uVar7 != 0];
  if (DAT_004a93ea == 'e') {
    uStack_514 = 0;
    uStack_518 = 0;
  }
  else {
    uStack_518 = DAT_004a96d8 & 0xffff;
    uStack_514 = DAT_004a96dc & 0xffff;
  }
  bVar1 = *(byte *)(*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + uStack_514 * 0x48) + 0x2c)
                    + 0x10 + uStack_518 * 0x1c);
  uStack_50c = uVar7;
  while ((bVar1 & 0x10) != 0) {
    reg_next((int *)&uStack_518,(int *)&uStack_514);
    bVar1 = *(byte *)(*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + uStack_514 * 0x48) +
                              0x2c) + 0x10 + uStack_518 * 0x1c);
  }
  va0 = *(undefined4 *)
         (*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + uStack_514 * 0x48) + 0x2c) +
         uStack_518 * 0x1c);
  fmt_register(uStack_514,uStack_518,3,acStack_300);
  fmt_register(uStack_514,uStack_518,1,acStack_200);
  fmt_register(uStack_514,uStack_518,2,acStack_400);
  uVar2 = *(undefined4 *)(*(int *)(cur_dtype + 0x18) + 0x30 + uStack_514 * 0x48);
  pcVar10 = PTR_s_change__s_s___Hex__s_Dec__s__s___004cfe40;
  if (uVar7 != 0) {
    uVar7 = *(uint *)(*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + uStack_514 * 0x48 + 0x2c) +
                              0x2c) + 0x10 + uStack_518 * 0x1c);
    if ((uVar7 & 1) == 0) {
      if ((uVar7 & 2) == 0) {
        sprintf((char *)abStack_500,s_change__s_s____s__s_004d0434,va0,uVar2,DAT_00502704,
                acStack_400);
      }
      else {
        sprintf((char *)abStack_500,s_change__s_s___Hex__s__s__s_004d0448,va0,uVar2,acStack_300,
                DAT_00502704,acStack_400);
      }
      goto LAB_0045138d;
    }
    pcVar10 = s_change__s_s___Hex__s_Dec__s__s___004d0464;
  }
  sprintf((char *)abStack_500,pcVar10,va0,uVar2,acStack_300,acStack_200,DAT_00502704,acStack_400);
LAB_0045138d:
  help_lines_cur = &PTR_s__CR__change___U__previous_reg____004cfe28;
  prompt_help_cycle(-1);
  do {
    iVar3 = str_find_char((char *)abStack_500,0x3d);
    uVar7 = 0xffffffff;
    pbVar5 = abStack_500;
    do {
      pbVar8 = pbVar5;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pbVar8 = pbVar5 + 1;
      bVar1 = *pbVar5;
      pbVar5 = pbVar8;
    } while (bVar1 != 0);
    uVar7 = ~uVar7;
    pbVar5 = pbVar8 + -uVar7;
    pbVar8 = abStack_100;
    for (uVar6 = uVar7 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pbVar8 = *(undefined4 *)pbVar5;
      pbVar5 = pbVar5 + 4;
      pbVar8 = pbVar8 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pbVar8 = *pbVar5;
      pbVar5 = pbVar5 + 1;
      pbVar8 = pbVar8 + 1;
    }
    while (iVar4 = help_line_edit((char *)abStack_100), uVar7 = uStack_510, iStack_504 = iVar4,
          iVar4 == 0xd) {
      pbVar8 = abStack_100;
      pbVar5 = abStack_500;
      do {
        bVar1 = *pbVar5;
        bVar9 = bVar1 < *pbVar8;
        if (bVar1 != *pbVar8) {
LAB_0045143a:
          iVar4 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
          goto LAB_0045143f;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar5[1];
        bVar9 = bVar1 < pbVar8[1];
        if (bVar1 != pbVar8[1]) goto LAB_0045143a;
        pbVar5 = pbVar5 + 2;
        pbVar8 = pbVar8 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_0045143f:
      if (iVar4 == 0) {
LAB_00451654:
        iVar4 = iStack_504;
        if (gui_mode != 0) {
          dsp_free_ext(cur_dev_index,0);
        }
        do {
          reg_next((int *)&uStack_518,(int *)&uStack_514);
        } while ((*(byte *)(*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + uStack_514 * 0x48)
                                    + 0x2c) + 0x10 + uStack_518 * 0x1c) & 0x10) != 0);
        goto LAB_004516a8;
      }
      optr = abStack_100 + iVar3 + 1;
      eval_expr(uStack_510);
      if (node != (void *)0x0) {
        if ((*(uint *)((int)node + 0x1c) & 0x200) != 0) {
          uVar6 = *(uint *)(*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + uStack_514 * 0x48)
                                    + 0x2c) + 0x10 + uStack_518 * 0x1c) & 0xfffc0207;
          *(uint *)((int)node + 0x1c) = CONCAT22((short)(uVar6 >> 0x10),CONCAT11(2,(char)uVar6));
          node_from_double(uVar7,node);
        }
        if ((((*(byte *)((int)node + 0x1c) & 2) != 0) && ((uVar7 & 0x10000000) != 0)) &&
           ((uVar7 & 0x4000000) != 0)) {
          *(uint *)((int)node + 8) =
               *(uint *)((int)node + 8) | (*(uint *)((int)node + 0xc) & 0xff) << 0x10;
        }
        iVar3 = dev_write_reg(*(int *)(cur_dev + 4),uStack_514,uStack_518,(long *)((int)node + 8));
        if (iVar3 == 0) {
          sim_error(s_Error_writing_register_004c5550);
          return;
        }
        fmt_register(uStack_514,uStack_518,3,acStack_300);
        fmt_register(uStack_514,uStack_518,1,acStack_200);
        fmt_register(uStack_514,uStack_518,2,acStack_400);
        iVar3 = *(int *)(cur_dtype + 0x18) + uStack_514 * 0x48;
        uVar2 = *(undefined4 *)(iVar3 + 0x30);
        pcVar10 = PTR_s_change__s_s__s__Dec__s__s__s_004cfe44;
        if (uStack_50c == 0) {
override_prt_451630_17c75eb5:
          sprintf((char *)abStack_500,pcVar10,va0,uVar2,acStack_300,acStack_200,DAT_00502704,
                  acStack_400);
        }
        else {
          uVar7 = *(uint *)(*(int *)(*(int *)(iVar3 + 0x2c) + 0x2c) + 0x10 + uStack_518 * 0x1c);
          if ((uVar7 & 1) != 0) {
            pcVar10 = s_change__s_s__s__Dec__s__s__s_004d031c;
            goto override_prt_451630_17c75eb5;
          }
          if ((uVar7 & 2) == 0) {
            sprintf((char *)abStack_500,s_change__s_s__s_004d040c,va0,uVar2,acStack_400);
          }
          else {
            sprintf((char *)abStack_500,s_change__s_s__s___s__s_004d041c,va0,uVar2,acStack_300,
                    DAT_00502704,acStack_400);
          }
        }
        dsp_free(node);
        log_echo((char *)abStack_500,0);
        goto LAB_00451654;
      }
      status_line1(parm_errmsg);
    }
    if (iVar4 == 0x1b) {
      if (*(int *)(cur_dev + 0x1c) == iStack_508) {
        return;
      }
      cdb_free_frames();
      return;
    }
LAB_004516a8:
    status_line1(&empty_str);
    if (iVar4 == 0xe) {
      do {
        reg_next((int *)&uStack_518,(int *)&uStack_514);
      } while ((*(byte *)(*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + uStack_514 * 0x48) +
                                  0x2c) + 0x10 + uStack_518 * 0x1c) & 0x10) != 0);
    }
    else if (iVar4 == 0x15) {
      do {
        reg_prev((int *)&uStack_518,(int *)&uStack_514);
      } while ((*(byte *)(*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + uStack_514 * 0x48) +
                                  0x2c) + 0x10 + uStack_518 * 0x1c) & 0x10) != 0);
    }
    va0 = *(undefined4 *)
           (*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + uStack_514 * 0x48) + 0x2c) +
           uStack_518 * 0x1c);
    fmt_register(uStack_514,uStack_518,3,acStack_300);
    fmt_register(uStack_514,uStack_518,1,acStack_200);
    fmt_register(uStack_514,uStack_518,2,acStack_400);
    uVar2 = *(undefined4 *)(*(int *)(cur_dtype + 0x18) + 0x30 + uStack_514 * 0x48);
    if (uStack_50c == 0) {
      sprintf((char *)abStack_500,PTR_s_change__s_s___Hex__s_Dec__s__s___004cfe40,va0,uVar2,
              acStack_300,acStack_200,DAT_00502704,acStack_400);
    }
    else {
      uVar7 = *(uint *)(*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + uStack_514 * 0x48 + 0x2c) +
                                0x2c) + 0x10 + uStack_518 * 0x1c);
      if ((uVar7 & 1) == 0) {
        if ((uVar7 & 2) == 0) {
          sprintf((char *)abStack_500,s_change__s_s____s__s_004d0434,va0,uVar2,DAT_00502704,
                  acStack_400);
        }
        else {
          sprintf((char *)abStack_500,s_change__s_s___Hex__s__s__s_004d0448,va0,uVar2,acStack_300,
                  DAT_00502704,acStack_400);
        }
      }
      else {
        sprintf((char *)abStack_500,s_change__s_s___Hex__s_Dec__s__s___004d0464,va0,uVar2,
                acStack_300,acStack_200,DAT_00502704,acStack_400);
      }
    }
  } while( true );
}


/* ==== cmd_change_h1 @ 00451900 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void cmd_change_h1(void)

{
  byte bVar1;
  undefined4 va0;
  long space;
  code *pcVar2;
  long lVar3;
  uint uVar4;
  int iVar5;
  void *node;
  ulong addr;
  uint uVar6;
  byte *pbVar7;
  byte *pbVar8;
  bool bVar9;
  char *pcVar10;
  uint uStack_418;
  int iStack_414;
  char acStack_410 [12];
  byte *pbStack_404;
  long lStack_400;
  uint uStack_3fc;
  uint uStack_3f8;
  uint uStack_3f4;
  byte abStack_3f0 [120];
  char acStack_378 [256];
  char acStack_278 [256];
  char acStack_178 [256];
  byte abStack_78 [120];
  
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uStack_418 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uStack_418 = (**(code **)(cur_dtype + 0x4e8))();
  }
  addr = DAT_004a96c0;
  uVar6 = uStack_418 >> 7 & 1;
  _DAT_00502708 = (&PTR_s_Fract_004cfe38)[uVar6 != 0];
  iVar5 = *(int *)(cur_dtype + 0x20);
  uVar4 = DAT_004a96dc & 0xffff;
  uStack_3fc = *(uint *)(iVar5 + 8 + uVar4 * 0x2c);
  va0 = *(undefined4 *)(iVar5 + uVar4 * 0x2c);
  space = *(long *)(iVar5 + 4 + uVar4 * 0x2c);
  uStack_3f4 = *(uint *)(iVar5 + uVar4 * 0x2c + 0x20);
  uStack_3f8 = uVar6;
  fmt_addr(DAT_004a96c0,acStack_410);
  if (uVar6 == 0) {
    lStack_400 = fmt_read_word(space,addr,3,acStack_278,(char *)0x0);
    fmt_read_word(space,addr,2,acStack_378,(char *)0x0);
    fmt_read_word(space,addr,1,acStack_178,(char *)0x0);
    pcVar10 = PTR_s_change__s___s___Hex__s_Dec__s__s_004cfe48;
  }
  else {
    lStack_400 = fmt_read_word(space,addr,3,acStack_278,(char *)0x0);
    if ((uStack_3fc & 0x10000000) != 0) {
      fmt_read_word(space,addr,2,acStack_378,PTR_s_change__s___s___Hex__s__s__25_25_004cfe58);
      sprintf((char *)abStack_3f0,PTR_s_change__s___s___Hex__s__s__25_25_004cfe58,va0,acStack_410,
              acStack_278,_DAT_00502708,acStack_378);
      goto LAB_00451af0;
    }
    fmt_read_word(space,addr,2,acStack_378,PTR_s_change__s___s___Hex__s_Dec__s__s_004cfe50);
    fmt_read_word(space,addr,1,acStack_178,(char *)0x0);
    pcVar10 = PTR_s_change__s___s___Hex__s_Dec__s__s_004cfe50;
  }
  sprintf((char *)abStack_3f0,pcVar10,va0,acStack_410,acStack_278,acStack_178,_DAT_00502708,
          acStack_378);
LAB_00451af0:
  help_lines_cur = 0x4cfe30;
  prompt_help_cycle(-1);
  iStack_414 = str_find_char((char *)abStack_3f0,0x3d);
  uVar4 = 0xffffffff;
  iStack_414 = iStack_414 + 1;
  pbVar7 = abStack_3f0;
  do {
    pbVar8 = pbVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pbVar8 = pbVar7 + 1;
    bVar1 = *pbVar7;
    pbVar7 = pbVar8;
  } while (bVar1 != 0);
  uVar4 = ~uVar4;
  pbStack_404 = abStack_78;
  pbVar7 = pbVar8 + -uVar4;
  pbVar8 = pbStack_404;
  for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pbVar8 = *(undefined4 *)pbVar7;
    pbVar7 = pbVar7 + 4;
    pbVar8 = pbVar8 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pbVar8 = *pbVar7;
    pbVar7 = pbVar7 + 1;
    pbVar8 = pbVar8 + 1;
  }
LAB_00451b48:
  do {
    pbStack_404 = (byte *)help_line_edit((char *)abStack_78,iStack_414,iStack_414,s_change_004cfef8)
    ;
    if (pbStack_404 == (byte *)0xd) {
      pbVar8 = abStack_78;
      pbVar7 = abStack_3f0;
      do {
        bVar1 = *pbVar7;
        bVar9 = bVar1 < *pbVar8;
        if (bVar1 != *pbVar8) {
LAB_00451bad:
          iVar5 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
          goto LAB_00451bb2;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar7[1];
        bVar9 = bVar1 < pbVar8[1];
        if (bVar1 != pbVar8[1]) goto LAB_00451bad;
        pbVar7 = pbVar7 + 2;
        pbVar8 = pbVar8 + 2;
      } while (bVar1 != 0);
      iVar5 = 0;
LAB_00451bb2:
      if (iVar5 != 0) {
        optr = abStack_78 + iStack_414;
        eval_expr(uStack_418);
        if (node == (void *)0x0) {
          status_line1(parm_errmsg);
          goto LAB_00451b48;
        }
        uVar4 = *(uint *)((int)node + 0x1c);
        if ((uVar4 & 0x200) == 0) {
LAB_00451c49:
          if ((((uVar4 & 2) != 0) && ((uStack_418 & 0x10000000) != 0)) &&
             ((uStack_418 & 0x4000000) != 0)) {
            *(uint *)((int)node + 8) =
                 *(uint *)((int)node + 8) | (*(uint *)((int)node + 0xc) & 0xff) << 0x10;
          }
        }
        else {
          iVar5 = memmap_find(space,addr);
          uVar4 = *(uint *)(*(int *)(cur_dtype + 0x20) + 0x24 + iVar5 * 0x2c) & 0xff400203;
          *(uint *)((int)node + 0x1c) = CONCAT22((short)(uVar4 >> 0x10),CONCAT11(2,(char)uVar4));
          node_from_double(uStack_418,node);
          uVar4 = *(uint *)((int)node + 0x1c);
          if ((uVar4 & 2) != 0) {
            if ((uStack_418 & 0x1000) != 0) {
              uVar6 = *(uint *)((int)node + 8);
              *(uint *)((int)node + 8) = uVar6 & 0xffff;
              *(uint *)((int)node + 0xc) = (uint)*(byte *)((int)node + 0xc) << 8 | uVar6 >> 0x10;
            }
            goto LAB_00451c49;
          }
        }
        pcVar2 = *(code **)(*(int *)(cur_dtype + 0x28) + 0x38);
        if (pcVar2 == (code *)0x0) {
          (**(code **)(*(int *)(cur_dtype + 0x28) + 4))(space,addr,(int)node + 8);
        }
        else {
          (*pcVar2)(space,addr,(int)node + 8);
        }
        fmt_read_word(space,addr,3,acStack_278,(char *)0x0);
        if (uStack_3f8 == 0) {
          fmt_read_word(space,addr,3,acStack_278,(char *)0x0);
          fmt_read_word(space,addr,2,acStack_378,(char *)0x0);
          fmt_read_word(space,addr,1,acStack_178,(char *)0x0);
          pcVar10 = PTR_s_change__s___s__s__Dec__s__s__s_004cfe4c;
override_prt_451df2_17c75eb5:
          sprintf((char *)abStack_3f0,pcVar10,va0,acStack_410,acStack_278,acStack_178,_DAT_00502708,
                  acStack_378);
        }
        else {
          if ((uStack_3fc & 0x10000000) == 0) {
            fmt_read_word(space,addr,1,acStack_178,(char *)0x0);
            fmt_read_word(space,addr,2,acStack_378,PTR_s_change__s___s__s__Dec__s__s__14__004cfe54);
            pcVar10 = PTR_s_change__s___s__s__Dec__s__s__14__004cfe54;
            goto override_prt_451df2_17c75eb5;
          }
          fmt_read_word(space,addr,2,acStack_378,PTR_s_change__s___s__s___s__25_25s_004cfe5c);
          sprintf((char *)abStack_3f0,PTR_s_change__s___s__s___s__25_25s_004cfe5c,va0,acStack_410,
                  acStack_278,_DAT_00502708,acStack_378);
        }
        dsp_free(node);
        log_echo((char *)abStack_3f0,0);
      }
      if (gui_mode != 0) {
        dsp_free_ext(cur_dev_index,0);
      }
      addr = addr + lStack_400;
    }
    else if (pbStack_404 == (byte *)0x1b) {
      return;
    }
    lVar3 = lStack_400;
    status_line1(&empty_str);
    if (pbStack_404 == (byte *)0xe) {
      addr = addr + lVar3;
    }
    else if (pbStack_404 == (byte *)0x15) {
      addr = addr - lVar3;
    }
    addr = addr & uStack_3f4;
    fmt_addr(addr,acStack_410);
    if (uStack_3f8 == 0) {
      fmt_read_word(space,addr,3,acStack_278,(char *)0x0);
      fmt_read_word(space,addr,2,acStack_378,(char *)0x0);
      fmt_read_word(space,addr,1,acStack_178,(char *)0x0);
      pcVar10 = PTR_s_change__s___s___Hex__s_Dec__s__s_004cfe48;
override_prt_451fb4_17c75eb5:
      sprintf((char *)abStack_3f0,pcVar10,va0,acStack_410,acStack_278,acStack_178,_DAT_00502708,
              acStack_378);
    }
    else {
      fmt_read_word(space,addr,3,acStack_278,(char *)0x0);
      if ((uStack_3fc & 0x10000000) == 0) {
        fmt_read_word(space,addr,2,acStack_378,PTR_s_change__s___s___Hex__s_Dec__s__s_004cfe50);
        fmt_read_word(space,addr,1,acStack_178,(char *)0x0);
        pcVar10 = PTR_s_change__s___s___Hex__s_Dec__s__s_004cfe50;
        goto override_prt_451fb4_17c75eb5;
      }
      fmt_read_word(space,addr,2,acStack_378,PTR_s_change__s___s___Hex__s__s__25_25_004cfe58);
      sprintf((char *)abStack_3f0,PTR_s_change__s___s___Hex__s__s__25_25_004cfe58,va0,acStack_410,
              acStack_278,_DAT_00502708,acStack_378);
    }
    iStack_414 = str_find_char((char *)abStack_3f0,0x3d);
    iStack_414 = iStack_414 + 1;
    uVar4 = 0xffffffff;
    pbVar7 = abStack_3f0;
    do {
      pbVar8 = pbVar7;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pbVar8 = pbVar7 + 1;
      bVar1 = *pbVar7;
      pbVar7 = pbVar8;
    } while (bVar1 != 0);
    uVar4 = ~uVar4;
    pbVar7 = pbVar8 + -uVar4;
    pbVar8 = abStack_78;
    for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pbVar8 = *(undefined4 *)pbVar7;
      pbVar7 = pbVar7 + 4;
      pbVar8 = pbVar8 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pbVar8 = *pbVar7;
      pbVar7 = pbVar7 + 1;
      pbVar8 = pbVar8 + 1;
    }
  } while( true );
}


/* ==== cmd_change_h2 @ 00452030 ==== */

void cmd_change_h2(void)

{
  uint *val;
  ulong addr;
  code *pcVar1;
  uint mode;
  int iVar2;
  uint uVar3;
  ushort *puVar4;
  uint uVar5;
  uint uStack_1c;
  uint uStack_18;
  uint uStack_14;
  uint uStack_10;
  uint uStack_c;
  char *pcStack_8;
  int iStack_4;
  
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    mode = *(uint *)(cur_dtype + 0xc);
  }
  else {
    mode = (**(code **)(cur_dtype + 0x4e8))();
  }
  iVar2 = (int)DAT_004a93ea;
  iStack_4 = *(int *)(cur_dev + 0x1c);
  uStack_14 = mode;
  if (iVar2 != 0x65) {
    puVar4 = (ushort *)&DAT_004a96dc;
    pcStack_8 = &DAT_004a93ea;
    do {
      switch(iVar2) {
      default:
        break;
      case 0x50:
      case 0x58:
        goto switchD_00452099_caseD_50;
      case 0x67:
        *(uint *)(puVar4 + -0xe) = (uint)puVar4[-2];
        *(uint *)(puVar4 + -10) = (uint)*puVar4;
      case 0x47:
        uVar5 = *(uint *)(puVar4 + -10);
        uVar3 = (uint)*puVar4;
        uStack_1c = uVar5;
        uStack_10 = uVar3;
        if (uVar3 <= uVar5) {
          uStack_1c = uVar3;
          uStack_10 = uVar5;
        }
        if ((uVar3 < uVar5) || ((uVar5 == uVar3 && ((uint)puVar4[-2] <= *(uint *)(puVar4 + -0xe)))))
        {
          uStack_c = *(uint *)(puVar4 + -0xe);
          uStack_18 = (uint)puVar4[-2];
        }
        else {
          uStack_c = (uint)puVar4[-2];
          uStack_18 = *(uint *)(puVar4 + -0xe);
        }
        val = (uint *)(puVar4 + 6);
        while( true ) {
          if ((*(uint *)(puVar4 + 0x10) & 0x200) != 0) {
            uVar5 = *(uint *)(*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + uStack_1c * 0x48
                                               ) + 0x2c) + 0x10 + uStack_18 * 0x1c) & 0xfffc0207;
            *(uint *)(puVar4 + 0x10) = CONCAT22((short)(uVar5 >> 0x10),CONCAT11(2,(char)uVar5));
            node_from_double(mode,puVar4 + 2);
          }
          if ((((puVar4[0x10] & 2) != 0) && ((mode & 0x10000000) != 0)) && ((mode & 0x4000000) != 0)
             ) {
            *val = *val | (*(uint *)(puVar4 + 8) & 0xff) << 0x10;
          }
          iVar2 = dev_write_reg(*(int *)(cur_dev + 4),uStack_1c,uStack_18,(long *)val);
          if (iVar2 == 0) {
            sim_error(s_Error_writing_register_004c5550);
            return;
          }
          if ((uStack_1c == uStack_10) && (uStack_18 == uStack_c)) break;
          reg_next((int *)&uStack_18,(int *)&uStack_1c);
        }
        break;
      case 0x70:
        *(undefined4 *)(puVar4 + -0xc) = *(undefined4 *)(puVar4 + -0xe);
switchD_00452099_caseD_50:
        addr = *(ulong *)(puVar4 + -0xe);
        iVar2 = *(int *)(cur_dtype + 0x20) + (uint)*puVar4 * 0x2c;
        uStack_10 = *(uint *)(iVar2 + 4);
        uStack_c = *(uint *)(iVar2 + 0x20);
        uVar5 = *(int *)(puVar4 + -0xc) - addr & uStack_c;
        if (pcStack_8[1] == 'F') {
          iVar2 = memmap_find(uStack_10,addr);
          uVar3 = *(uint *)(*(int *)(cur_dtype + 0x20) + 0x24 + iVar2 * 0x2c) & 0xff400203;
          *(uint *)(puVar4 + 0x10) = CONCAT22((short)(uVar3 >> 0x10),CONCAT11(2,(char)uVar3));
          node_from_double(mode,puVar4 + 2);
          if ((puVar4[0x10] & 2) != 0) {
            if ((mode & 0x1000) != 0) {
              *(uint *)(puVar4 + 8) = *(uint *)(puVar4 + 6) >> 0x10 | (uint)(byte)puVar4[8] << 8;
              *(uint *)(puVar4 + 6) = *(uint *)(puVar4 + 6) & 0xffff;
            }
            goto LAB_00452137;
          }
        }
        else {
LAB_00452137:
          if ((((puVar4[0x10] & 2) != 0) && ((mode & 0x10000000) != 0)) && ((mode & 0x4000000) != 0)
             ) {
            *(uint *)(puVar4 + 6) = *(uint *)(puVar4 + 6) | (*(uint *)(puVar4 + 8) & 0xff) << 0x10;
          }
        }
        pcVar1 = *(code **)(*(int *)(cur_dtype + 0x28) + 0x38);
        if (pcVar1 == (code *)0x0) {
          uVar3 = (**(code **)(*(int *)(cur_dtype + 0x28) + 8))(uStack_10,addr,1,puVar4 + 6);
        }
        else {
          uVar3 = (*pcVar1)(uStack_10,addr);
        }
        if (uVar3 == 0) {
          uVar3 = 1;
        }
        mode = uStack_14;
        if (uVar3 <= uVar5) {
          (**(code **)(*(int *)(cur_dtype + 0x28) + 8))
                    (uStack_10,addr + uVar3 & uStack_c,(uVar5 - uVar3) + 1,puVar4 + 6);
          mode = uStack_14;
        }
      }
      puVar4 = puVar4 + 0x28;
      pcStack_8 = pcStack_8 + 2;
      iVar2 = (int)*pcStack_8;
    } while (iVar2 != 0x65);
  }
  iVar2 = iStack_4;
  if (*(int *)(cur_dev + 0x1c) != iStack_4) {
    cdb_free_frames();
  }
  if ((*(int *)(cur_sim + 0x4400) == 1) || (*(int *)(cur_sim + 0x4400) == 2)) {
    win_update(-(uint)(*(int *)(cur_dev + 0x1c) != iVar2) & 0x7fff);
  }
  return;
}


