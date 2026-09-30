/* ==== parse_get_root @ 0047f090 ==== */

void parse_get_root(void)

{
  return;
}


/* ==== new_node @ 0047f0a0 ==== */

void new_node(void)

{
  undefined4 *puVar1;
  undefined4 *p;
  undefined4 *p_00;
  int extraout_EAX;
  int iVar2;
  
  cdb_malloc(8);
  if (p == (undefined4 *)0x0) {
    return;
  }
  cdb_malloc(0x1c);
  *p = p_00;
  if (p_00 == (undefined4 *)0x0) {
    cdb_free(p);
    return;
  }
  cdb_malloc(0x40);
  p_00[4] = extraout_EAX;
  if (extraout_EAX == 0) {
    cdb_free(p);
    cdb_free(p_00);
    return;
  }
  p[1] = node_alloc_list;
  node_alloc_list = p;
  p_00[3] = 0;
  p_00[2] = 0;
  p_00[1] = 0;
  *p_00 = 0;
  p_00[5] = 0;
  *(undefined4 *)(p_00[4] + 0x14) = 0;
  *(undefined4 *)(p_00[4] + 0x10) = 0;
  *(undefined4 *)(p_00[4] + 0xc) = 0;
  *(undefined4 *)(p_00[4] + 0x18) = 0;
  *(undefined4 *)(p_00[4] + 0x1c) = 0;
  puVar1 = (undefined4 *)p_00[4];
  *puVar1 = 0;
  puVar1[1] = 0;
  *(undefined4 *)(p_00[4] + 8) = 0;
  *(undefined4 *)(p_00[4] + 0x20) = 0;
  *(undefined4 *)(p_00[4] + 0x24) = 0;
  iVar2 = 0x2c;
  *(undefined2 *)(p_00[4] + 0x3c) = 0;
  *(undefined4 *)(p_00[4] + 0x28) = 0;
  do {
    iVar2 = iVar2 + 4;
    *(undefined4 *)(p_00[4] + -4 + iVar2) = 0;
  } while (iVar2 < 0x3c);
  return;
}


/* ==== parse_free_all @ 0047f180 ==== */

void parse_free_all(void)

{
  free_node_list(&node_alloc_list,1);
  free_node_list(&tmp_list_cells,0);
  return;
}


/* ==== parse_free_keep_nodes @ 0047f1a0 ==== */

void parse_free_keep_nodes(void)

{
  free_node_list(&node_alloc_list,0);
  free_node_list(&tmp_list_cells,1);
  return;
}


/* ==== free_node_list @ 0047f1c0 ==== */

void __cdecl free_node_list(void *plist,int free_contents)

{
  int *piVar1;
  void *pvVar2;
  void *pvVar3;
  int *p;
  
  p = *(int **)plist;
  while (p != (int *)0x0) {
    piVar1 = (int *)p[1];
    if ((free_contents != 0) && (*p != 0)) {
      pvVar2 = *(void **)(*p + 0x10);
      if (pvVar2 != (void *)0x0) {
        cdb_free(pvVar2);
      }
      pvVar2 = *(void **)(*p + 0x14);
      while (pvVar2 != (void *)0x0) {
        pvVar3 = *(void **)((int)pvVar2 + 4);
        cdb_free(pvVar2);
        pvVar2 = pvVar3;
      }
      cdb_free((void *)*p);
    }
    cdb_free(p);
    p = piVar1;
  }
  *(undefined4 *)plist = 0;
  return;
}


/* ==== yyparse @ 0047f240 ==== */

/* WARNING: Removing unreachable block (ram,0x0047fac5) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int yyparse(void)

{
  void *extraout_EAX;
  int *extraout_EAX_00;
  void *extraout_EAX_01;
  int *extraout_EAX_02;
  int extraout_EAX_03;
  int extraout_EAX_04;
  int extraout_EAX_05;
  int extraout_EAX_06;
  int extraout_EAX_07;
  int extraout_EAX_08;
  int extraout_EAX_09;
  int extraout_EAX_10;
  int extraout_EAX_11;
  int extraout_EAX_12;
  int extraout_EAX_13;
  int extraout_EAX_14;
  int extraout_EAX_15;
  int extraout_EAX_16;
  int extraout_EAX_17;
  int extraout_EAX_18;
  int extraout_EAX_19;
  int extraout_EAX_20;
  int extraout_EAX_21;
  int extraout_EAX_22;
  int extraout_EAX_23;
  int extraout_EAX_24;
  int extraout_EAX_25;
  int extraout_EAX_26;
  int extraout_EAX_27;
  int extraout_EAX_28;
  int extraout_EAX_29;
  int extraout_EAX_30;
  int extraout_EAX_31;
  int extraout_EAX_32;
  int extraout_EAX_33;
  int extraout_EAX_34;
  int extraout_EAX_35;
  int extraout_EAX_36;
  int extraout_EAX_37;
  uint uVar1;
  int extraout_EAX_38;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  void *pvVar8;
  void *pvVar9;
  char *va0;
  int local_5c;
  int local_58;
  ulong local_54;
  undefined1 local_50 [40];
  undefined1 local_28 [40];
  
  local_58 = 0x96;
  dsp_alloc(600,0);
  yy_val_stack = extraout_EAX;
  dsp_alloc(600,0);
  yy_state_stack = extraout_EAX_00;
  if ((yy_val_stack == (void *)0x0) || (extraout_EAX_00 == (int *)0x0)) {
    va0 = s_out_of_memory_004d6b18;
override_prt_4802f4_ce254783:
    yyerror(va0);
    return 1;
  }
  DAT_0050458c = (int *)((int)yy_val_stack + -4);
  DAT_00504588 = extraout_EAX_00 + -1;
  DAT_0050459c = 0;
  _DAT_00504594 = 0;
  _DAT_00504598 = 0;
  DAT_00504580 = 0;
  DAT_00504584 = -1;
switchD_0047f5cc_default:
  local_54 = local_58 * 4;
  local_5c = DAT_0050459c;
  piVar5 = DAT_0050458c;
  piVar7 = DAT_00504588;
LAB_0047f2e8:
  piVar7 = piVar7 + 1;
  piVar4 = piVar5;
  if ((int *)((int)yy_state_stack + local_54) <= piVar7) {
    iVar6 = (int)piVar7 - (int)yy_state_stack;
    local_54 = local_54 + 600;
    iVar3 = (int)piVar5 - (int)yy_val_stack;
    local_58 = local_58 + 0x96;
    dsp_realloc(yy_val_stack,local_54);
    yy_val_stack = extraout_EAX_01;
    dsp_realloc(yy_state_stack,local_54);
    yy_state_stack = extraout_EAX_02;
    if ((yy_val_stack == (void *)0x0) || (extraout_EAX_02 == (int *)0x0)) {
      va0 = s_yacc_stack_overflow_004d6b28;
      goto override_prt_4802f4_ce254783;
    }
    piVar7 = extraout_EAX_02 + (iVar6 >> 2);
    piVar4 = (int *)((int)yy_val_stack + (iVar3 >> 2) * 4);
  }
  piVar5 = piVar4 + 1;
  *piVar7 = local_5c;
  *piVar5 = yyval_node;
  while( true ) {
    iVar3 = *(int *)(&DAT_004d5f98 + local_5c * 4);
    if (-1000 < iVar3) {
      if ((DAT_00504584 < 0) && (DAT_00504584 = yylex(), DAT_00504584 < 0)) {
        DAT_00504584 = 0;
      }
      iVar3 = iVar3 + DAT_00504584;
      if (((-1 < iVar3) && (iVar3 < 0x186)) &&
         (iVar3 = (&DAT_004d5980)[iVar3], *(int *)(&DAT_004d65e8 + iVar3 * 4) == DAT_00504584)) {
        DAT_00504584 = -1;
        yyval_node = DAT_005059c0;
        local_5c = iVar3;
        if (0 < DAT_00504580) {
          DAT_00504580 = DAT_00504580 + -1;
        }
        goto LAB_0047f2e8;
      }
    }
    iVar3 = *(int *)(&DAT_004d6880 + local_5c * 4);
    if (iVar3 == -2) {
      if ((DAT_00504584 < 0) && (DAT_00504584 = yylex(), DAT_00504584 < 0)) {
        DAT_00504584 = 0;
      }
      for (piVar2 = &DAT_004d5968; (*piVar2 != -1 || (piVar2[1] != local_5c)); piVar2 = piVar2 + 2)
      {
      }
      iVar3 = piVar2[2];
      while ((-1 < iVar3 && (iVar3 != DAT_00504584))) {
        iVar3 = piVar2[4];
        piVar2 = piVar2 + 2;
      }
      iVar3 = piVar2[3];
      if (iVar3 < 0) {
        dsp_free(yy_state_stack);
        dsp_free(yy_val_stack);
        return 0;
      }
    }
    if (iVar3 != 0) break;
    switch(DAT_00504580) {
    case 0:
      yyerror(s_syntax_error_004d6be8);
    case 1:
    case 2:
      goto switchD_0047f447_caseD_1;
    case 3:
      if (DAT_00504584 == 0) goto LAB_004802c5;
      DAT_00504584 = -1;
      break;
    default:
      goto switchD_0047f447_default;
    }
  }
switchD_0047f447_default:
  iVar6 = (int)*(uint *)(&DAT_004d6448 + iVar3 * 4) >> 1;
  _DAT_00504594 = iVar3;
  if ((*(uint *)(&DAT_004d6448 + iVar3 * 4) & 1) == 0) {
    piVar5 = piVar5 + -iVar6;
    piVar7 = piVar7 + -iVar6;
    yyval_node = piVar5[1];
    iVar6 = *piVar7 + 1 + *(int *)(&DAT_004d6230 + *(int *)(&DAT_004d62a8 + iVar3 * 4) * 4);
    if ((0x185 < iVar6) ||
       (local_5c = (&DAT_004d5980)[iVar6],
       *(int *)(&DAT_004d65e8 + (&DAT_004d5980)[iVar6] * 4) != -*(int *)(&DAT_004d62a8 + iVar3 * 4))
       ) {
      local_5c = (&DAT_004d5980)[*(int *)(&DAT_004d6230 + *(int *)(&DAT_004d62a8 + iVar3 * 4) * 4)];
    }
    goto LAB_0047f2e8;
  }
  DAT_0050458c = piVar5 + -iVar6;
  DAT_00504588 = piVar7 + -iVar6;
  yyval_node = DAT_0050458c[1];
  iVar6 = *DAT_00504588 + 1 + *(int *)(&DAT_004d6230 + *(int *)(&DAT_004d62a8 + iVar3 * 4) * 4);
  if ((0x185 < iVar6) ||
     (DAT_0050459c = (&DAT_004d5980)[iVar6],
     *(int *)(&DAT_004d65e8 + DAT_0050459c * 4) != -*(int *)(&DAT_004d62a8 + iVar3 * 4))) {
    DAT_0050459c = (&DAT_004d5980)
                   [*(int *)(&DAT_004d6230 + *(int *)(&DAT_004d62a8 + iVar3 * 4) * 4)];
  }
  switch(iVar3) {
  case 1:
    parse_root = yyval_node;
    goto joined_r0x004801aa;
  case 2:
    parse_root = yyval_node;
    break;
  case 3:
    yyval_node = *piVar5;
    goto joined_r0x0048020f;
  case 4:
    pvVar9 = (void *)*piVar5;
    pvVar8 = (void *)piVar4[-1];
    iVar3 = 0x146;
    goto LAB_0047f6f3;
  case 5:
    yyval_node = *piVar5;
    break;
  case 6:
    mk_binary_node((void *)piVar4[-1],0x3d,(void *)*piVar5);
    yyval_node = extraout_EAX_03;
    goto joined_r0x0048020f;
  case 7:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x124;
    goto LAB_0047f6ef;
  case 8:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x125;
    goto LAB_0047f6b6;
  case 9:
    mk_binary_node((void *)piVar4[-1],0x126,(void *)*piVar5);
    yyval_node = extraout_EAX_04;
    goto joined_r0x0048020f;
  case 10:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x127;
    goto LAB_0047f6ef;
  case 0xb:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x128;
    goto LAB_0047f6b6;
  case 0xc:
    mk_binary_node((void *)piVar4[-1],0x129,(void *)*piVar5);
    yyval_node = extraout_EAX_05;
    goto joined_r0x0048020f;
  case 0xd:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x12a;
    goto LAB_0047f6ef;
  case 0xe:
    pvVar9 = (void *)*piVar5;
    iVar3 = 299;
LAB_0047f6b6:
    mk_binary_node((void *)piVar4[-1],iVar3,pvVar9);
    yyval_node = extraout_EAX_06;
    break;
  case 0xf:
    mk_binary_node((void *)piVar4[-1],300,(void *)*piVar5);
    yyval_node = extraout_EAX_07;
    goto joined_r0x0048020f;
  case 0x10:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x12d;
LAB_0047f6ef:
    pvVar8 = (void *)piVar4[-1];
LAB_0047f6f3:
    mk_binary_node(pvVar8,iVar3,pvVar9);
    yyval_node = extraout_EAX_08;
    goto joined_r0x004801aa;
  case 0x11:
    yyval_node = *piVar5;
    break;
  case 0x12:
    mk_ternary_node((void *)piVar4[-3],(void *)piVar4[-1],(void *)*piVar5);
    yyval_node = extraout_EAX_09;
    goto joined_r0x0048020f;
  case 0x13:
    yyval_node = *piVar5;
    goto joined_r0x004801aa;
  case 0x14:
    mk_binary_node((void *)piVar4[-1],0x12e,(void *)*piVar5);
    yyval_node = extraout_EAX_10;
    break;
  case 0x15:
    yyval_node = *piVar5;
    goto joined_r0x0048020f;
  case 0x16:
    mk_binary_node((void *)piVar4[-1],0x12f,(void *)*piVar5);
    yyval_node = extraout_EAX_11;
    goto joined_r0x004801aa;
  case 0x17:
    yyval_node = *piVar5;
    break;
  case 0x18:
    mk_binary_node((void *)piVar4[-1],0x7c,(void *)*piVar5);
    yyval_node = extraout_EAX_12;
    goto joined_r0x0048020f;
  case 0x19:
    yyval_node = *piVar5;
    goto joined_r0x004801aa;
  case 0x1a:
    mk_binary_node((void *)piVar4[-1],0x5e,(void *)*piVar5);
    yyval_node = extraout_EAX_13;
    break;
  case 0x1b:
    yyval_node = *piVar5;
    goto joined_r0x0048020f;
  case 0x1c:
    pvVar9 = (void *)*piVar5;
    pvVar8 = (void *)piVar4[-1];
    iVar3 = 0x26;
    goto LAB_0047f891;
  case 0x1d:
  case 0x20:
    yyval_node = *piVar5;
    break;
  case 0x1e:
    pvVar9 = (void *)*piVar5;
    pvVar8 = (void *)piVar4[-1];
    iVar3 = 0x130;
    goto LAB_0047f94d;
  case 0x1f:
    pvVar9 = (void *)*piVar5;
    pvVar8 = (void *)piVar4[-1];
    iVar3 = 0x131;
    goto LAB_0047f891;
  case 0x21:
    pvVar9 = (void *)*piVar5;
    pvVar8 = (void *)piVar4[-1];
    iVar3 = 0x3c;
    goto LAB_0047f94d;
  case 0x22:
    pvVar9 = (void *)*piVar5;
    pvVar8 = (void *)piVar4[-1];
    iVar3 = 0x3e;
LAB_0047f891:
    mk_binary_node(pvVar8,iVar3,pvVar9);
    yyval_node = extraout_EAX_14;
    goto joined_r0x004801aa;
  case 0x23:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x132;
    goto LAB_0047f90d;
  case 0x24:
    pvVar9 = (void *)*piVar5;
    pvVar8 = (void *)piVar4[-1];
    iVar3 = 0x133;
    goto LAB_0047f94d;
  case 0x25:
  case 0x28:
  case 0x2b:
    yyval_node = *piVar5;
    goto joined_r0x004801aa;
  case 0x26:
    pvVar9 = (void *)*piVar5;
    pvVar8 = (void *)piVar4[-1];
    iVar3 = 0x134;
    goto LAB_0047f911;
  case 0x27:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x135;
    goto LAB_0047f949;
  case 0x29:
    pvVar9 = (void *)*piVar5;
    pvVar8 = (void *)piVar4[-1];
    iVar3 = 0x2b;
    goto LAB_0047f911;
  case 0x2a:
    pvVar9 = (void *)*piVar5;
    pvVar8 = (void *)piVar4[-1];
    iVar3 = 0x2d;
    goto LAB_0047f94d;
  case 0x2c:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x2a;
LAB_0047f90d:
    pvVar8 = (void *)piVar4[-1];
LAB_0047f911:
    mk_binary_node(pvVar8,iVar3,pvVar9);
    yyval_node = extraout_EAX_15;
    break;
  case 0x2d:
    pvVar9 = (void *)*piVar5;
    pvVar8 = (void *)piVar4[-1];
    iVar3 = 0x2f;
    goto LAB_0047f94d;
  case 0x2e:
    pvVar9 = (void *)*piVar5;
    pvVar8 = (void *)piVar4[-1];
    iVar3 = 0x25;
    goto LAB_0047f970;
  case 0x2f:
  case 0x32:
    yyval_node = *piVar5;
    break;
  case 0x30:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x13f;
LAB_0047f949:
    pvVar8 = (void *)piVar4[-1];
LAB_0047f94d:
    mk_binary_node(pvVar8,iVar3,pvVar9);
    yyval_node = extraout_EAX_16;
    goto joined_r0x0048020f;
  case 0x31:
    pvVar9 = (void *)*piVar5;
    pvVar8 = (void *)piVar4[-1];
    iVar3 = 0x23;
LAB_0047f970:
    mk_binary_node(pvVar8,iVar3,pvVar9);
    yyval_node = extraout_EAX_17;
    goto joined_r0x004801aa;
  case 0x33:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x141;
    goto LAB_0047fa1f;
  case 0x34:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x143;
    goto LAB_0047f9da;
  case 0x35:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x26;
    goto LAB_0047f9fc;
  case 0x36:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x2a;
    goto LAB_0047fa1f;
  case 0x37:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x2b;
    goto LAB_0047f9da;
  case 0x38:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x2d;
    goto LAB_0047f9fc;
  case 0x39:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x7e;
    goto LAB_0047fa1f;
  case 0x3a:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x21;
LAB_0047f9da:
    mk_unary_node(iVar3,pvVar9);
    yyval_node = extraout_EAX_18;
    goto joined_r0x004801aa;
  case 0x3b:
    pvVar9 = (void *)*piVar5;
    iVar3 = 0x138;
LAB_0047f9fc:
    mk_unary_node(iVar3,pvVar9);
    yyval_node = extraout_EAX_19;
    break;
  case 0x3c:
    pvVar9 = (void *)*piVar4;
    iVar3 = 0x138;
LAB_0047fa1f:
    mk_unary_node(iVar3,pvVar9);
    yyval_node = extraout_EAX_20;
    goto joined_r0x0048020f;
  case 0x3d:
    yyval_node = *piVar5;
    goto joined_r0x004801aa;
  case 0x3e:
    mk_binary_node((void *)piVar4[-2],0x144,(void *)*piVar4);
    yyval_node = extraout_EAX_21;
    break;
  case 0x3f:
    mk_call_node((void *)piVar4[-1],(void *)0x0);
    yyval_node = extraout_EAX_22;
    iVar3 = dbg_resolve_symbol(s_dummy_call_004d4de8,local_50);
    if (iVar3 == 0) {
      cdb_error(s_command_line_function_calls_aren_004d6ba8);
      yyval_node = 0;
      goto LAB_004802c5;
    }
    goto joined_r0x0048020f;
  case 0x40:
    mk_call_node((void *)piVar4[-2],(void *)*piVar4);
    yyval_node = extraout_EAX_23;
    iVar3 = dbg_resolve_symbol(s_dummy_call_004d4de8,local_28);
    if (iVar3 == 0) {
      cdb_error(s_command_line_function_calls_aren_004d6ba8);
      yyval_node = 0;
    }
    goto joined_r0x004801aa;
  case 0x41:
    mk_member_dot((void *)piVar4[-1],(char *)*piVar5);
    yyval_node = extraout_EAX_24;
    if ((void *)*piVar5 != (void *)0x0) {
      cdb_free((void *)*piVar5);
    }
    break;
  case 0x42:
    mk_member_arrow((void *)piVar4[-1],(char *)*piVar5);
    yyval_node = extraout_EAX_25;
    goto LAB_0047fbb5;
  case 0x43:
    mk_unary_node(0x140,(void *)*piVar4);
    yyval_node = extraout_EAX_26;
    goto joined_r0x004801aa;
  case 0x44:
    mk_unary_node(0x142,(void *)*piVar4);
    yyval_node = extraout_EAX_27;
    break;
  case 0x45:
    cdb_lookup_variable((char *)*piVar5);
    yyval_node = extraout_EAX_28;
LAB_0047fbb5:
    if ((void *)*piVar5 != (void *)0x0) {
      cdb_free((void *)*piVar5);
    }
    goto joined_r0x0048020f;
  case 0x46:
    cdb_register_value((char *)*piVar5);
    yyval_node = extraout_EAX_29;
    if ((void *)*piVar5 != (void *)0x0) {
      cdb_free((void *)*piVar5);
    }
    goto joined_r0x004801aa;
  case 0x47:
    yyval_node = *piVar5;
    break;
  case 0x48:
    yyval_node = *piVar4;
    goto joined_r0x0048020f;
  case 0x49:
    mk_arglist((void *)*piVar5);
    yyval_node = extraout_EAX_30;
    goto joined_r0x004801aa;
  case 0x4a:
    arglist_append((void *)piVar4[-1],(void *)*piVar5);
    yyval_node = extraout_EAX_31;
    break;
  case 0x4b:
  case 0x4e:
    yyval_node = *piVar5;
    goto joined_r0x0048020f;
  case 0x4c:
  case 0x4f:
    yyval_node = *piVar5;
    goto joined_r0x004801aa;
  case 0x4d:
    yyval_node = *piVar5;
    break;
  case 0x50:
    yyval_node = *piVar4;
    if ((*piVar4 == 0) || (iVar3 = *piVar5, iVar3 == 0)) {
LAB_0047ff27:
      yyval_node = 0;
    }
    else {
      iVar6 = *(int *)(*(int *)(*piVar4 + 0x10) + 0x20);
      if (iVar6 == 0xe) {
LAB_0047fd08:
        iVar3 = *(int *)(*(int *)(iVar3 + 0x10) + 0x20);
        if (iVar3 == 2) {
          *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0xc;
        }
        else if (iVar3 == 3) {
          *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0xd;
        }
        else if (iVar3 == 4) {
          *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0xe;
        }
        else if (iVar3 == 5) {
          *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0xf;
        }
        else if (iVar3 == 0x10000) {
          *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0x10001;
        }
        else {
          if (iVar3 != 0x10002) {
LAB_0047ff1a:
            cdb_error(s_two_or_more_data_types_in_cast_004d6b88);
            goto LAB_0047ff27;
          }
          *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0x10003;
        }
      }
      else {
        if (((((iVar6 != 4) && (iVar6 != 0xf)) && (iVar6 != 5)) && ((iVar6 != 0xd && (iVar6 != 3))))
           && ((iVar6 != 0xc && (iVar6 != 2)))) goto LAB_0047ff1a;
        if (iVar6 == 0xe) goto LAB_0047fd08;
        if (iVar6 == 4) {
          iVar3 = *(int *)(*(int *)(iVar3 + 0x10) + 0x20);
          if (iVar3 == 2) {
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 2;
          }
          else if (iVar3 == 3) {
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 3;
          }
          else if (iVar3 == 4) {
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 4;
          }
          else if (iVar3 == 5) {
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 5;
          }
          else if (iVar3 == 0x10000) {
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0x10000;
          }
          else if (iVar3 == 0x10002) {
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0x10002;
          }
          else if (iVar3 == 0x10004) {
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0x10004;
          }
          else {
            if (iVar3 != 0x10005) goto LAB_0047ff1a;
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0x10005;
          }
        }
        else if (iVar6 == 0xf) {
          iVar3 = *(int *)(*(int *)(iVar3 + 0x10) + 0x20);
          if (iVar3 == 4) {
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0xf;
          }
          else {
            if (iVar3 != 0x10000) goto LAB_0047ff1a;
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0x10003;
          }
        }
        else if (iVar6 == 5) {
          iVar3 = *(int *)(*(int *)(iVar3 + 0x10) + 0x20);
          if (iVar3 == 4) {
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 5;
          }
          else if (iVar3 == 0xe) {
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0xf;
          }
          else if (iVar3 == 0x10004) {
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0x10005;
          }
          else {
            if (iVar3 != 0x10000) goto LAB_0047ff1a;
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0x10002;
          }
        }
        else if (iVar6 == 0xd) {
          if (*(int *)(*(int *)(iVar3 + 0x10) + 0x20) != 4) goto LAB_0047ff1a;
          *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0xd;
        }
        else if (iVar6 == 3) {
          iVar3 = *(int *)(*(int *)(iVar3 + 0x10) + 0x20);
          if (iVar3 == 4) {
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 3;
          }
          else {
            if (iVar3 != 0xe) goto LAB_0047ff1a;
            *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0xd;
          }
        }
        else if (iVar6 == 0xc) {
          if (*(int *)(*(int *)(iVar3 + 0x10) + 0x20) != 4) goto LAB_0047ff1a;
          *(undefined4 *)(*(int *)(yyval_node + 0x10) + 0x20) = 0xd;
        }
      }
    }
    track_list_cell((void *)*piVar5);
    break;
  case 0x51:
    iVar3 = 1;
    goto LAB_0047ff8e;
  case 0x52:
    iVar3 = 2;
    goto LAB_0047ffaa;
  case 0x53:
    iVar3 = 3;
    goto LAB_0047ff72;
  case 0x54:
  case 0x5a:
    iVar3 = 4;
    goto LAB_0047ff8e;
  case 0x55:
    iVar3 = 5;
    goto LAB_0047ffaa;
  case 0x56:
    iVar3 = 0x10000;
    goto LAB_0047ff72;
  case 0x57:
    iVar3 = 0x10004;
LAB_0047ff8e:
    mk_type_node(iVar3);
    yyval_node = extraout_EAX_33;
    goto joined_r0x0048020f;
  case 0x58:
    iVar3 = 6;
    goto LAB_0047ffaa;
  case 0x59:
    iVar3 = 7;
LAB_0047ff72:
    mk_type_node(iVar3);
    yyval_node = extraout_EAX_32;
    break;
  case 0x5b:
    iVar3 = 0xe;
LAB_0047ffaa:
    mk_type_node(iVar3);
    yyval_node = extraout_EAX_34;
    goto joined_r0x004801aa;
  case 0x5c:
    yyval_node = *piVar5;
    break;
  case 0x5d:
    yyval_node = *piVar5;
    goto joined_r0x0048020f;
  case 0x5e:
    yyval_node = *piVar5;
    goto joined_r0x004801aa;
  case 0x5f:
    if (*piVar4 == 0) {
      iVar3 = 0;
    }
    else {
      if (*(int *)(*(int *)(*piVar4 + 0x10) + 0x20) == 8) {
        uVar1 = cdb_lookup_scoped((char *)*piVar5,10);
        *(uint *)(*(int *)(*piVar4 + 0x10) + 0x28) = -(uint)(uVar1 != 0xffffffff) & uVar1;
      }
      else {
        uVar1 = cdb_lookup_scoped((char *)*piVar5,0xc);
        *(uint *)(*(int *)(*piVar4 + 0x10) + 0x28) = -(uint)(uVar1 != 0xffffffff) & uVar1;
      }
      iVar3 = *piVar4;
      if (*(int *)(*(int *)(*piVar4 + 0x10) + 0x28) == 0) {
        sprintf(&yyerror_buf,s_There_is_no_struct_or_union_name_004d6b60,*piVar5);
        cdb_error(&yyerror_buf);
        yyval_node = 0;
        iVar3 = yyval_node;
      }
    }
    goto LAB_0048013e;
  case 0x60:
    mk_type_node(8);
    yyval_node = extraout_EAX_35;
    goto joined_r0x0048020f;
  case 0x61:
    mk_type_node(9);
    yyval_node = extraout_EAX_36;
    goto joined_r0x004801aa;
  case 0x62:
    mk_type_node(10);
    iVar3 = extraout_EAX_37;
    if (extraout_EAX_37 != 0) {
      yyval_node = extraout_EAX_37;
      uVar1 = cdb_lookup_scoped((char *)*piVar5,0xf);
      *(uint *)(*(int *)(yyval_node + 0x10) + 0x28) = -(uint)(uVar1 != 0xffffffff) & uVar1;
      iVar3 = yyval_node;
      if (*(int *)(*(int *)(yyval_node + 0x10) + 0x28) == 0) {
        yyval_node = 0;
        sprintf(&yyerror_buf,s_there_is_no_enumeration_called___004d6b3c,*piVar5);
        iVar3 = yyval_node;
      }
    }
LAB_0048013e:
    yyval_node = iVar3;
    if ((void *)*piVar5 != (void *)0x0) {
      cdb_free((void *)*piVar5);
    }
    break;
  case 99:
    mk_type_node(0);
    yyval_node = extraout_EAX_38;
    if (extraout_EAX_38 == 0) goto LAB_004802c5;
    *(undefined4 *)(*(int *)(extraout_EAX_38 + 0x10) + 0x20) = 0x10;
    goto switchD_0047f5cc_default;
  case 100:
    yyval_node = *piVar5;
    if (*piVar5 != 0) {
      uVar1 = *(uint *)(*(int *)(yyval_node + 0x10) + 0x20);
      *(uint *)(*(int *)(yyval_node + 0x10) + 0x20) =
           uVar1 & 0x1000f | (uVar1 & 0xfffefff4 | 4) << 2;
    }
joined_r0x004801aa:
    if (yyval_node == 0) {
      dsp_free(yy_state_stack);
      dsp_free(yy_val_stack);
      return 1;
    }
    goto switchD_0047f5cc_default;
  case 0x65:
    yyval_node = *piVar5;
    goto switchD_0047f5cc_default;
  case 0x66:
    yyval_node = *piVar4;
    if (*piVar4 != 0) {
      *(uint *)(*(int *)(yyval_node + 0x10) + 0x20) =
           *(uint *)(*(int *)(yyval_node + 0x10) + 0x20) |
           *(uint *)(*(int *)(*piVar5 + 0x10) + 0x20) & 0xff0;
    }
    track_list_cell((void *)*piVar5);
    break;
  case 0x67:
    goto switchD_0047f5cc_caseD_67;
  default:
    goto switchD_0047f5cc_default;
  }
  if (yyval_node == 0) {
    dsp_free(yy_state_stack);
    dsp_free(yy_val_stack);
    return 1;
  }
  goto switchD_0047f5cc_default;
switchD_0047f5cc_caseD_67:
  yyval_node = *piVar5;
joined_r0x0048020f:
  if (yyval_node == 0) {
LAB_004802c5:
    dsp_free(yy_state_stack);
    dsp_free(yy_val_stack);
    return 1;
  }
  goto switchD_0047f5cc_default;
switchD_0047f447_caseD_1:
  DAT_00504580 = 3;
  while( true ) {
    if (piVar7 < yy_state_stack) {
      dsp_free(yy_state_stack);
      dsp_free(yy_val_stack);
      return 1;
    }
    iVar3 = *(int *)(&DAT_004d5f98 + *piVar7 * 4) + 0x100;
    if (((-1 < iVar3) && (iVar3 < 0x186)) &&
       (*(int *)(&DAT_004d65e8 + (&DAT_004d5980)[iVar3] * 4) == 0x100)) break;
    piVar7 = piVar7 + -1;
    piVar5 = piVar5 + -1;
  }
  local_5c = (&DAT_004d5980)[iVar3];
  goto LAB_0047f2e8;
}


