/* ==== frame_locals_string @ 0046e870 ==== */

char __cdecl frame_locals_string(int func_symidx,int frame_base)

{
  undefined2 *puVar1;
  int iVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  undefined1 *extraout_EAX;
  uint uVar6;
  int iVar7;
  undefined3 extraout_var;
  undefined1 *extraout_EAX_00;
  undefined3 extraout_var_00;
  undefined1 *extraout_EAX_01;
  undefined1 *extraout_EAX_02;
  uint uVar9;
  int iVar10;
  uint uVar11;
  char *pcVar12;
  int iVar13;
  char *pcVar14;
  undefined1 local_40 [24];
  uint local_28;
  int local_24;
  uint local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  undefined2 local_4;
  char *pcVar8;
  
  uVar11 = 0;
  bVar3 = true;
  iVar5 = cdb_func_bf_sym(func_symidx);
  if (iVar5 == -1) {
    return -0x80;
  }
  if (frame_locals_buf == (undefined1 *)0x0) {
    cdb_malloc(frame_locals_buf_size + 1);
    frame_locals_buf = extraout_EAX;
  }
  *frame_locals_buf = 0;
  iVar7 = *(int *)(cur_sim + 0x3fe0);
  iVar5 = *(int *)(iVar5 * 0x20 + 0x1c + iVar7) + 1 + iVar5;
  iVar10 = cur_sim;
  if (iVar5 < *(int *)(cur_sim + 0x3fd8)) {
    do {
      iVar13 = iVar5 * 0x20;
      iVar2 = *(int *)(iVar13 + 0x18 + iVar7);
      if ((iVar2 == 0x65) || (iVar2 == 100)) {
        if ((uVar11 == 0) || (frame_locals_buf_size <= uVar11)) goto LAB_0046ebe9;
        goto LAB_0046ebd6;
      }
      if (((iVar2 == 9) || (iVar2 == 0x13)) || (iVar2 == 0x11)) {
        local_20 = *(uint *)(iVar13 + 0x14 + iVar7);
        uVar6 = local_20 & 0x1000f;
        if (((uVar6 == 8) || (uVar6 == 9)) || (uVar6 == 10)) {
          local_18 = *(undefined4 *)((iVar5 + 1) * 0x20 + *(int *)(iVar10 + 0x3fe0));
        }
        else {
          local_18 = 0;
        }
        if (((byte)local_20 & 0x30) == 0x30) {
          iVar7 = (iVar5 + 1) * 0x20 + *(int *)(iVar10 + 0x3fe0);
          local_14 = *(int *)(iVar7 + 0xc);
          if (local_14 == 0) {
            local_14 = 1;
          }
          local_10 = *(int *)(iVar7 + 0x10);
          if (local_10 == 0) {
            local_10 = 1;
          }
          local_c = *(int *)(iVar7 + 0x14);
          if (local_c == 0) {
            local_c = 1;
          }
          local_8 = *(int *)(iVar7 + 0x18);
          if (local_8 == 0) goto LAB_0046e9c3;
        }
        else {
          local_14 = 1;
          local_10 = 1;
          local_c = 1;
LAB_0046e9c3:
          local_8 = 1;
        }
        local_4 = 1;
        iVar7 = iVar13 + *(int *)(iVar10 + 0x3fe0);
        iVar2 = *(int *)(iVar13 + 0x18 + *(int *)(iVar10 + 0x3fe0));
        if (iVar2 == 0x13) {
          local_24 = *(int *)(iVar7 + 0xc);
          local_28 = *(uint *)(iVar13 + 8 + *(int *)(iVar10 + 0x3fe0));
          local_1c = 2;
        }
        else if ((iVar2 == 4) || (iVar2 == 0x11)) {
          local_28 = *(uint *)(iVar7 + 8);
          local_1c = 0x11;
        }
        else {
          local_24 = cdb_default_space();
          local_1c = 2;
          local_28 = *(int *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar13) + frame_base & cdb_addr_mask;
        }
        cVar4 = cdb_sym_name(iVar5);
        pcVar8 = (char *)CONCAT31(extraout_var,cVar4);
        uVar6 = 0xffffffff;
        pcVar12 = pcVar8;
        do {
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          cVar4 = *pcVar12;
          pcVar12 = pcVar12 + 1;
        } while (cVar4 != '\0');
        uVar6 = ~uVar6 + 2 + uVar11;
        if (frame_locals_buf_size < uVar6) {
          frame_locals_buf_size = uVar6 * 2;
          cdb_realloc(frame_locals_buf,frame_locals_buf_size + 1);
          frame_locals_buf = extraout_EAX_00;
        }
        if (bVar3) {
          bVar3 = false;
        }
        else {
          puVar1 = (undefined2 *)(frame_locals_buf + uVar11);
          uVar11 = uVar11 + 2;
          *puVar1 = DAT_004d32dc;
          *(undefined1 *)(puVar1 + 1) = DAT_004d32de;
        }
        uVar6 = 0xffffffff;
        pcVar12 = pcVar8;
        do {
          pcVar14 = pcVar12;
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          pcVar14 = pcVar12 + 1;
          cVar4 = *pcVar12;
          pcVar12 = pcVar14;
        } while (cVar4 != '\0');
        uVar6 = ~uVar6;
        pcVar12 = pcVar14 + -uVar6;
        pcVar14 = frame_locals_buf + uVar11;
        for (uVar9 = uVar6 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(undefined4 *)pcVar14 = *(undefined4 *)pcVar12;
          pcVar12 = pcVar12 + 4;
          pcVar14 = pcVar14 + 4;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar14 = *pcVar12;
          pcVar12 = pcVar12 + 1;
          pcVar14 = pcVar14 + 1;
        }
        uVar6 = 0xffffffff;
        do {
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          cVar4 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar4 != '\0');
        iVar7 = uVar11 + (~uVar6 - 1);
        *(undefined2 *)(frame_locals_buf + iVar7) = DAT_004d3360;
        iVar7 = iVar7 + 1;
        cdb_load_value(local_40);
        cVar4 = cdb_value_to_string(local_40,-1);
        pcVar8 = (char *)CONCAT31(extraout_var_00,cVar4);
        uVar11 = 0xffffffff;
        pcVar12 = pcVar8;
        do {
          if (uVar11 == 0) break;
          uVar11 = uVar11 - 1;
          cVar4 = *pcVar12;
          pcVar12 = pcVar12 + 1;
        } while (cVar4 != '\0');
        uVar11 = (~uVar11 - 1) + iVar7;
        if (frame_locals_buf_size < uVar11) {
          frame_locals_buf_size = uVar11 * 2;
          cdb_realloc(frame_locals_buf,frame_locals_buf_size + 1);
          frame_locals_buf = extraout_EAX_01;
        }
        uVar11 = 0xffffffff;
        pcVar12 = pcVar8;
        do {
          pcVar14 = pcVar12;
          if (uVar11 == 0) break;
          uVar11 = uVar11 - 1;
          pcVar14 = pcVar12 + 1;
          cVar4 = *pcVar12;
          pcVar12 = pcVar14;
        } while (cVar4 != '\0');
        uVar11 = ~uVar11;
        pcVar12 = pcVar14 + -uVar11;
        pcVar14 = frame_locals_buf + iVar7;
        for (uVar6 = uVar11 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined4 *)pcVar14 = *(undefined4 *)pcVar12;
          pcVar12 = pcVar12 + 4;
          pcVar14 = pcVar14 + 4;
        }
        for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
          *pcVar14 = *pcVar12;
          pcVar12 = pcVar12 + 1;
          pcVar14 = pcVar14 + 1;
        }
        uVar11 = 0xffffffff;
        do {
          if (uVar11 == 0) break;
          uVar11 = uVar11 - 1;
          cVar4 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar4 != '\0');
        uVar11 = iVar7 + (~uVar11 - 1);
        iVar10 = cur_sim;
      }
      iVar7 = *(int *)(iVar10 + 0x3fe0);
      iVar5 = iVar5 + 1 + *(int *)(iVar13 + 0x1c + iVar7);
    } while (iVar5 < *(int *)(iVar10 + 0x3fd8));
  }
  if ((uVar11 != 0) && (uVar11 < frame_locals_buf_size)) {
LAB_0046ebd6:
    cdb_realloc(frame_locals_buf,uVar11 + 1);
    frame_locals_buf_size = uVar11;
    frame_locals_buf = extraout_EAX_02;
  }
LAB_0046ebe9:
  return (char)frame_locals_buf;
}


/* ==== eval_tree @ 0046ec10 ==== */

int __cdecl eval_tree(void *node)

{
  int iVar1;
  
  tree_mark_leaves(node);
  cdb_saved_clear();
  cdb_saved_push(node);
  if (*(int *)((int)node + 0xc) != 0) {
    iVar1 = eval_tree_core();
    return iVar1;
  }
  return 1;
}


/* ==== eval_tree_core_thunk @ 0046ec50 ==== */

int eval_tree_core_thunk(void)

{
  int iVar1;
  int *node;
  int *extraout_EAX;
  int *extraout_EAX_00;
  int iVar2;
  int *extraout_EAX_01;
  int *extraout_EAX_02;
  int *piVar3;
  int *node_00;
  bool bVar4;
  
  cdb_saved_pop();
  if (node != (int *)0x0) {
    piVar3 = node;
    if (((node[3] != 0) && (node[6] != 0)) &&
       (cdb_saved_pop(), piVar3 = extraout_EAX, extraout_EAX == (int *)0x0)) {
      cdb_saved_push(node);
      return 1;
    }
    if (piVar3 != (int *)0x0) {
      do {
        iVar2 = piVar3[3];
        node_00 = piVar3;
        while (iVar2 == 0x145) {
          cdb_saved_push(node_00);
          if (node_00[1] != 0) {
            arglist_free_temps(*(void **)(node_00[1] + 0x14));
          }
          cdb_saved_pop();
          bVar4 = extraout_EAX_00 == node_00;
          node_00 = extraout_EAX_00;
          if (bVar4) break;
          iVar2 = extraout_EAX_00[3];
        }
        iVar2 = *node_00;
        if ((iVar2 == 0) || (*(int *)(iVar2 + 0x18) != 1)) {
          iVar2 = node_00[1];
          if ((iVar2 != 0) && (node_00[3] == 0x138)) {
LAB_004702db:
            *(undefined4 *)(iVar2 + 0x18) = 1;
          }
        }
        else {
          iVar1 = node_00[3];
          if (iVar1 == 0x12f) {
            iVar2 = value_is_true(*(void **)(iVar2 + 0x10));
            if (iVar2 != 0) {
              iVar2 = node_00[2];
              goto joined_r0x004702c7;
            }
          }
          else if (iVar1 == 0x12e) {
            iVar2 = value_is_true(*(void **)(iVar2 + 0x10));
            if (iVar2 == 0) {
              iVar2 = node_00[2];
joined_r0x004702c7:
              if (iVar2 != 0) goto LAB_004702db;
            }
          }
          else if (iVar1 == 0x123) {
            iVar2 = value_is_true(*(void **)(iVar2 + 0x10));
            if (iVar2 == 0) {
              iVar2 = node_00[2];
            }
            else {
              iVar2 = node_00[1];
            }
            goto joined_r0x004702c7;
          }
        }
        iVar2 = *node_00;
        if (((iVar2 == 0) || (*(int *)(iVar2 + 0xc) == 0)) || (*(int *)(iVar2 + 0x18) == 1)) {
          iVar2 = node_00[1];
          if (((iVar2 == 0) || (*(int *)(iVar2 + 0xc) == 0)) || (*(int *)(iVar2 + 0x18) == 1)) {
            iVar2 = node_00[2];
            if (((iVar2 == 0) || (*(int *)(iVar2 + 0xc) == 0)) || (*(int *)(iVar2 + 0x18) == 1)) {
              iVar2 = eval_node(node_00);
              node_00[6] = 1;
              if (iVar2 == 0) {
                return 0;
              }
              if (node_00[3] == 0x145) {
                cdb_saved_push(node_00);
                return 2;
              }
              cdb_saved_pop();
              if ((extraout_EAX_01 == (int *)0x0) ||
                 (((piVar3 = extraout_EAX_01, extraout_EAX_01[3] != 0 && (extraout_EAX_01[6] != 0))
                  && (cdb_saved_pop(), piVar3 = extraout_EAX_02, node_00 = extraout_EAX_01,
                     extraout_EAX_02 == (int *)0x0)))) {
                cdb_saved_push(node_00);
                return 1;
              }
            }
            else {
              cdb_saved_push(node_00);
              piVar3 = (int *)node_00[2];
            }
          }
          else {
            cdb_saved_push(node_00);
            piVar3 = (int *)node_00[1];
          }
        }
        else {
          cdb_saved_push(node_00);
          piVar3 = (int *)*node_00;
        }
        if (piVar3 == (int *)0x0) {
          return 0;
        }
      } while( true );
    }
  }
  return 0;
}


/* ==== parse_c_expression @ 0046ec60 ==== */

void __cdecl parse_c_expression(char *text)

{
  int iVar1;
  
  cdb_arch_init();
  cdb_lookup_cache_depth = 0xffffffff;
  cdb_lookup_cache_sym = 0xffffffff;
  iVar1 = lex_init(text);
  if (iVar1 == 0) {
    return;
  }
  iVar1 = yyparse();
  if (iVar1 != 0) {
    parse_free_all();
    return;
  }
  parse_get_root();
  parse_free_keep_nodes();
  return;
}


/* ==== type_size @ 0046ecb0 ==== */

int __cdecl type_size(void *value,void *out_value)

{
  ulong *puVar1;
  uint uVar2;
  ulong uVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined4 local_80 [8];
  uint local_60;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  undefined1 local_40 [12];
  int local_34;
  undefined4 local_20;
  
  puVar1 = (ulong *)((int)out_value + 0xc);
  *puVar1 = 0;
  *(undefined4 *)((int)out_value + 0x10) = 0;
  *(undefined4 *)((int)out_value + 0x14) = 0;
  uVar2 = *(uint *)((int)value + 0x20);
  uVar4 = uVar2 & 0x30;
  if ((uVar4 == 0x10) || (uVar4 == 0x20)) {
    *puVar1 = 1;
    *(undefined4 *)((int)out_value + 0x10) = 0;
    *(undefined4 *)((int)out_value + 0x14) = 0;
    return 1;
  }
  if (uVar4 == 0x30) {
    puVar6 = local_80;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = *(undefined4 *)value;
      value = (undefined4 *)((int)value + 4);
      puVar6 = puVar6 + 1;
    }
    iVar5 = 1;
    if (((byte)local_60 & 0x30) == 0x30) {
      do {
        iVar7 = local_50;
        local_50 = local_4c;
        local_4c = local_48;
        iVar5 = iVar5 * local_54;
        local_60 = local_60 & 0x1000f | local_60 >> 2 & 0x3ffebff0;
        local_54 = iVar7;
        local_48 = 1;
      } while (((byte)local_60 & 0x30) == 0x30);
      local_48 = 1;
    }
    local_20 = 4;
    type_size(local_80,local_40);
    *puVar1 = iVar5 * local_34;
    return 1;
  }
  if ((((((uVar2 == 2) || (uVar2 == 3)) || (uVar2 == 4)) ||
       (((uVar2 == 0xb || (uVar2 == 10)) || ((uVar2 == 5 || ((uVar2 == 0xc || (uVar2 == 0xd))))))))
      || (uVar2 == 0xe)) || (uVar2 == 0xf)) {
    if (cdb_arch == 0x2cb) {
      if ((((uVar2 == 5) || (uVar2 == 0xf)) || (uVar2 == 4)) ||
         (((uVar2 == 0xb || (uVar2 == 10)) || (uVar2 == 0xe)))) {
        *puVar1 = 4;
      }
      if ((*(int *)((int)value + 0x20) == 2) || (*(int *)((int)value + 0x20) == 0xc)) {
        *puVar1 = 1;
      }
      if ((*(int *)((int)value + 0x20) != 3) && (*(int *)((int)value + 0x20) != 0xd)) {
        return 1;
      }
      goto LAB_0046f04d;
    }
    if ((uVar2 != 5) && (uVar2 != 0xf)) {
      *puVar1 = 1;
      return 1;
    }
    if ((((cdb_arch != 0x2c8) && (cdb_arch != 0x2c5)) && (cdb_arch != 0x2ca)) &&
       ((cdb_arch != 0x2c7 && (cdb_arch != 0x2c9)))) {
      *puVar1 = 1;
      return 1;
    }
  }
  else {
    if ((uVar2 == 0x10000) || (uVar2 == 0x10001)) {
      *puVar1 = (-(uint)(cdb_arch != 0x2cb) & 0xfffffffd) + 4;
      return 1;
    }
    if ((uVar2 == 0x10002) || (uVar2 == 0x10003)) {
      *puVar1 = (-(uint)(cdb_arch != 0x2cb) & 0xfffffffe) + 4;
      return 1;
    }
    if (uVar2 == 0x10005) {
      *puVar1 = 3;
      return 1;
    }
    if (uVar2 == 0x10004) {
      *puVar1 = 2;
      return 1;
    }
    if (uVar2 != 6) {
      if (uVar2 == 7) {
        iVar5 = cdb_default_space();
        *puVar1 = (iVar5 != 3) + 1;
        if (cdb_arch != 0x2cb) {
          return 1;
        }
        *puVar1 = 4;
        return 1;
      }
      if ((uVar2 != 8) && (uVar2 != 9)) {
        cdb_internal_error(0x4d413c,0x275);
        return 0;
      }
      if (cdb_arch == 0x2cb) {
        *puVar1 = 0;
        return 1;
      }
      uVar3 = cdb_struct_size(*(int *)((int)value + 0x28));
      *puVar1 = uVar3;
      return 1;
    }
    if ((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) {
LAB_0046f04d:
      *puVar1 = 2;
      return 1;
    }
    if (cdb_arch == 0x2cb) {
      *puVar1 = 4;
      return 1;
    }
    if (((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) && (cdb_arch != 0x2ca)) {
      *puVar1 = 1;
      return 1;
    }
  }
  iVar5 = cdb_default_space();
  *puVar1 = (iVar5 != 3) + 1;
  return 1;
}


/* ==== value_dsp_to_double @ 0046f0f0 ==== */

void __cdecl value_dsp_to_double(void *value)

{
  uint uVar1;
  bool bVar2;
  uint uVar3;
  undefined4 uVar4;
  
  bVar2 = false;
  uVar1 = *(uint *)((int)value + 0x10);
  uVar4 = 0;
  uVar3 = 0;
  if ((uVar1 & 0x800000) != 0) {
    uVar4 = *(undefined4 *)((int)value + 0xc);
    bVar2 = true;
    value_neg(value,value);
    uVar3 = uVar1;
    if ((*(uint *)((int)value + 0x10) & 0x800000) != 0) {
      *(uint *)((int)value + 0x10) = *(uint *)((int)value + 0x10) >> 1;
      *(int *)((int)value + 0xc) = *(int *)((int)value + 0xc) + 1;
    }
  }
  mant_to_double(value);
  if (bVar2) {
    *(double *)value = -*(double *)value;
    *(uint *)((int)value + 0x10) = uVar3;
    *(undefined4 *)((int)value + 0xc) = uVar4;
  }
  return;
}


/* ==== value_double_to_dsp @ 0046f150 ==== */

void __cdecl value_double_to_dsp(void *value)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = *(undefined4 *)value;
  uVar2 = *(undefined4 *)((int)value + 4);
  if (*(double *)value < 0.0) {
    *(double *)value = -*(double *)value;
  }
  double_to_mant(value);
  *(undefined4 *)value = uVar1;
  *(undefined4 *)((int)value + 4) = uVar2;
  return;
}


/* ==== dw_udivmod @ 0046f1a0 ==== */

int __cdecl dw_udivmod(ulong *num,ulong *den,ulong *quot,ulong *rem)

{
  int iVar1;
  int iVar2;
  ulong local_18;
  ulong local_14;
  ulong local_10;
  ulong local_c;
  ulong local_8;
  ulong local_4;
  
  iVar1 = dw_cmp(den,num);
  if (0 < iVar1) {
    *quot = 0;
    quot[1] = 0;
    quot[2] = 0;
    *rem = *num;
    rem[1] = num[1];
    rem[2] = num[2];
    return 1;
  }
  iVar1 = 0;
  local_c = *num;
  local_8 = num[1];
  local_18 = *den;
  local_4 = num[2];
  local_14 = den[1];
  local_10 = den[2];
  while ((local_8 != 0 || (local_c != 0))) {
    dw_shr1(&local_c);
    iVar1 = iVar1 + 1;
  }
  iVar2 = 0;
  while ((local_14 != 0 || (local_18 != 0))) {
    dw_shr1(&local_18);
    iVar2 = iVar2 + 1;
  }
  if (iVar2 == 0) {
    cdb_c_error(s_attempt_to_divide_by_0_004d4148);
    return 0;
  }
  iVar1 = iVar1 - iVar2;
  if (iVar1 < 0) {
    *quot = 0;
    quot[1] = 0;
    quot[2] = 0;
    *rem = *num;
    rem[1] = num[1];
    rem[2] = num[2];
    return 1;
  }
  local_c = *num;
  local_8 = num[1];
  local_4 = num[2];
  local_14 = den[1];
  local_18 = *den;
  local_10 = den[2];
  for (iVar2 = iVar1; iVar2 != 0; iVar2 = iVar2 + -1) {
    dw_shl1(&local_18);
  }
  *quot = 0;
  quot[1] = 0;
  quot[2] = 0;
  for (iVar1 = iVar1 + 1; iVar1 != 0; iVar1 = iVar1 + -1) {
    dw_shl1(quot);
    iVar2 = dw_cmp(&local_18,&local_c);
    if (iVar2 < 1) {
      dw_neg(&local_18);
      dw_add(&local_18,&local_c,&local_c);
      dw_neg(&local_18);
      dw_shr1(&local_18);
      *quot = *quot | 1;
    }
    else {
      dw_shr1(&local_18);
    }
  }
  *rem = local_c;
  rem[1] = local_8;
  rem[2] = local_4;
  return 1;
}


/* ==== dw_udivmod_b @ 0046f3e0 ==== */

int __cdecl dw_udivmod_b(ulong *num,ulong *den,ulong *quot,ulong *rem)

{
  int iVar1;
  int iVar2;
  ulong local_18;
  ulong local_14;
  ulong local_10;
  ulong local_c;
  ulong local_8;
  ulong local_4;
  
  iVar1 = dw_cmp(den,num);
  if (0 < iVar1) {
    *quot = 0;
    quot[1] = 0;
    quot[2] = 0;
    *rem = *num;
    rem[1] = num[1];
    rem[2] = num[2];
    return 1;
  }
  iVar1 = 0;
  local_c = *num;
  local_8 = num[1];
  local_18 = *den;
  local_4 = num[2];
  local_14 = den[1];
  local_10 = den[2];
  while ((local_8 != 0 || (local_c != 0))) {
    dw_shr1_b(&local_c);
    iVar1 = iVar1 + 1;
  }
  iVar2 = 0;
  while ((local_14 != 0 || (local_18 != 0))) {
    dw_shr1_b(&local_18);
    iVar2 = iVar2 + 1;
  }
  if (iVar2 == 0) {
    cdb_c_error(s_attempt_to_divide_by_0_004d4148);
    return 0;
  }
  iVar1 = iVar1 - iVar2;
  if (iVar1 < 0) {
    *quot = 0;
    quot[1] = 0;
    quot[2] = 0;
    *rem = *num;
    rem[1] = num[1];
    rem[2] = num[2];
    return 1;
  }
  local_c = *num;
  local_8 = num[1];
  local_4 = num[2];
  local_14 = den[1];
  local_18 = *den;
  local_10 = den[2];
  for (iVar2 = iVar1; iVar2 != 0; iVar2 = iVar2 + -1) {
    dw_shl1_b(&local_18);
  }
  *quot = 0;
  quot[1] = 0;
  quot[2] = 0;
  for (iVar1 = iVar1 + 1; iVar1 != 0; iVar1 = iVar1 + -1) {
    dw_shl1_b(quot);
    iVar2 = dw_cmp(&local_18,&local_c);
    if (iVar2 < 1) {
      dw_neg_b(&local_18);
      dw_add_b(&local_18,&local_c,&local_c);
      dw_neg_b(&local_18);
      dw_shr1_b(&local_18);
      *quot = *quot | 1;
    }
    else {
      dw_shr1_b(&local_18);
    }
  }
  *rem = local_c;
  rem[1] = local_8;
  rem[2] = local_4;
  return 1;
}


/* ==== eval_unary @ 0046f620 ==== */

int __cdecl eval_unary(void *pchild,int op,void *result_node,int do_eval)

{
  int iVar1;
  
  if ((pchild != (void *)0x0) && (*(int *)pchild != 0)) {
    if ((do_eval == 0) && (op != 0x138)) {
      if (op == 0x26) goto LAB_0046f686;
      if (op != 0x145) {
        coerce_array_func(pchild);
      }
    }
    if (op < 0x27) {
      if (op == 0x26) {
LAB_0046f686:
        iVar1 = eval_addr_of(pchild,0x26,result_node,do_eval);
        return iVar1;
      }
      if (op == 0x21) {
        iVar1 = eval_lognot(pchild,0x21,result_node,do_eval);
        return iVar1;
      }
    }
    else if (op < 0x7f) {
      if (op == 0x7e) {
        iVar1 = eval_compl(pchild,0x7e,result_node,do_eval);
        return iVar1;
      }
      if (op == 0x2a) {
        iVar1 = eval_deref(pchild,0x2a,result_node,do_eval);
        return iVar1;
      }
      if (op == 0x2b) {
        iVar1 = eval_uplus(pchild,0x2b,result_node,do_eval);
        return iVar1;
      }
      if (op == 0x2d) {
        iVar1 = eval_uminus(pchild,0x2d,result_node,do_eval);
        return iVar1;
      }
    }
    else {
      switch(op) {
      case 0x138:
        iVar1 = eval_sizeof(pchild,op,result_node,do_eval);
        return iVar1;
      case 0x140:
      case 0x141:
      case 0x142:
      case 0x143:
        iVar1 = eval_incdec(pchild,op,result_node,do_eval);
        return iVar1;
      case 0x145:
        iVar1 = eval_call(pchild,op,result_node,do_eval);
        return iVar1;
      case 0x148:
        iVar1 = eval_array_to_ptr(pchild,op,result_node,do_eval);
        return iVar1;
      case 0x149:
        iVar1 = eval_func_to_ptr(pchild,op,result_node,do_eval);
        return iVar1;
      }
    }
    cdb_internal_error(0x4d413c,0x3f1);
  }
  return 0;
}


/* ==== eval_binary @ 0046f7d0 ==== */

int __cdecl eval_binary(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  int iVar1;
  
  if ((((plhs != (void *)0x0) && (*(int *)plhs != 0)) && (prhs != (void *)0x0)) &&
     (*(int *)prhs != 0)) {
    if (do_eval == 0) {
      coerce_array_func(plhs);
      coerce_array_func(prhs);
    }
    if (op < 0x2b) {
      if (op == 0x2a) {
switchD_0046f86d_caseD_2f:
        iVar1 = eval_muldiv(plhs,prhs,op,result_node,do_eval);
        return iVar1;
      }
      if (op == 0x23) {
        iVar1 = eval_hash(plhs,prhs,0x23,result_node,do_eval);
        return iVar1;
      }
      if ((0x24 < op) && (op < 0x27)) goto switchD_0046f923_caseD_7c;
    }
    else if (op < 0x3d) {
      if (op == 0x3c) {
switchD_0046f923_caseD_132:
        iVar1 = eval_relational(plhs,prhs,op,result_node,do_eval);
        return iVar1;
      }
      switch(op) {
      case 0x2b:
        iVar1 = eval_add(plhs,prhs,op,result_node,do_eval);
        return iVar1;
      case 0x2d:
        iVar1 = eval_sub(plhs,prhs,op,result_node,do_eval);
        return iVar1;
      case 0x2e:
        if (do_eval == 0) {
          return 1;
        }
        iVar1 = eval_dot_values(*(void **)(*(int *)plhs + 0x10),*(void **)(*(int *)prhs + 0x10),
                                *(void **)((int)result_node + 0x10));
        return iVar1;
      case 0x2f:
        goto switchD_0046f86d_caseD_2f;
      }
    }
    else if (op < 0x5f) {
      if (op == 0x5e) {
switchD_0046f923_caseD_7c:
        iVar1 = eval_bitop(plhs,prhs,op,result_node,do_eval);
        return iVar1;
      }
      if (op == 0x3d) {
        iVar1 = eval_assign(plhs,prhs,0x3d,result_node,do_eval);
        return iVar1;
      }
      if (op == 0x3e) goto switchD_0046f923_caseD_132;
    }
    else {
      switch(op) {
      case 0x7c:
      case 0x134:
      case 0x135:
        goto switchD_0046f923_caseD_7c;
      case 0x124:
      case 0x125:
        iVar1 = eval_muldiv_assign(plhs,prhs,op,result_node,do_eval);
        return iVar1;
      case 0x126:
      case 0x129:
      case 0x12a:
      case 299:
      case 300:
      case 0x12d:
        iVar1 = eval_bitop_assign(plhs,prhs,op,result_node,do_eval);
        return iVar1;
      case 0x127:
        iVar1 = eval_add_assign(plhs,prhs,op,result_node,do_eval);
        return iVar1;
      case 0x128:
        iVar1 = eval_sub_assign(plhs,prhs,op,result_node,do_eval);
        return iVar1;
      case 0x12e:
      case 0x12f:
        iVar1 = eval_logical(plhs,prhs,op,result_node,do_eval);
        return iVar1;
      case 0x130:
      case 0x131:
        iVar1 = eval_equality(plhs,prhs,op,result_node,do_eval);
        return iVar1;
      case 0x132:
      case 0x133:
        goto switchD_0046f923_caseD_132;
      case 0x139:
        if (do_eval == 0) {
          return 1;
        }
        iVar1 = eval_arrow_values(*(void **)(*(int *)plhs + 0x10),*(void **)(*(int *)prhs + 0x10),
                                  *(void **)((int)result_node + 0x10));
        return iVar1;
      case 0x13f:
        iVar1 = eval_cast(plhs,prhs,op,result_node,do_eval);
        return iVar1;
      case 0x144:
        iVar1 = eval_subscript(plhs,prhs,op,result_node,do_eval);
        return iVar1;
      case 0x146:
        iVar1 = eval_comma(plhs,prhs,op,result_node,do_eval);
        return iVar1;
      }
    }
    cdb_internal_error(0x4d413c,0x480);
  }
  return 0;
}


/* ==== eval_ternary @ 0046fb70 ==== */

int __cdecl eval_ternary(void *pcond,void *pa,void *pb,void *result_node,int do_eval)

{
  void *a;
  ulong type1;
  uint uVar1;
  int iVar2;
  ulong uVar3;
  
  if (do_eval == 0) {
    coerce_array_func(pcond);
    coerce_array_func(pa);
    coerce_array_func(pb);
  }
  iVar2 = *(int *)((int)*(void **)(*(int *)pcond + 0x10) + 0x20);
  if (((((iVar2 != 2) && (iVar2 != 3)) && (iVar2 != 4)) &&
      (((iVar2 != 0xb && (iVar2 != 10)) && ((iVar2 != 5 && ((iVar2 != 0xc && (iVar2 != 0xd))))))))
     && (((iVar2 != 0xe && (((iVar2 != 0xf && (iVar2 != 6)) && (iVar2 != 7)))) &&
         ((((iVar2 != 0x10000 && (iVar2 != 0x10001)) &&
           (((iVar2 != 0x10003 && ((iVar2 != 0x10002 && (iVar2 != 0x10004)))) && (iVar2 != 0x10005))
           )) && (((byte)iVar2 & 0x30) != 0x10)))))) {
    cdb_error(s_first_operand_to____must_have_sc_004d4190);
    return 0;
  }
  a = *(void **)(*(int *)pa + 0x10);
  type1 = *(ulong *)((int)a + 0x20);
  if ((((((type1 == 2) || (type1 == 3)) || (type1 == 4)) || ((type1 == 0xb || (type1 == 10)))) ||
      ((type1 == 5 || ((type1 == 0xc || (type1 == 0xd)))))) ||
     ((type1 == 0xe ||
      (((((type1 == 0xf || (type1 == 6)) || (type1 == 7)) ||
        (((type1 == 0x10000 || (type1 == 0x10001)) ||
         ((type1 == 0x10003 || ((type1 == 0x10002 || (type1 == 0x10004)))))))) || (type1 == 0x10005)
       ))))) {
    iVar2 = *(int *)((int)*(void **)(*(int *)pb + 0x10) + 0x20);
    if ((((iVar2 == 2) || (iVar2 == 3)) || (iVar2 == 4)) ||
       ((((iVar2 == 0xb || (iVar2 == 10)) || ((iVar2 == 5 || ((iVar2 == 0xc || (iVar2 == 0xd))))))
        || ((iVar2 == 0xe ||
            ((((((iVar2 == 0xf || (iVar2 == 6)) || (iVar2 == 7)) ||
               ((iVar2 == 0x10000 || (iVar2 == 0x10001)))) || (iVar2 == 0x10003)) ||
             (((iVar2 == 0x10002 || (iVar2 == 0x10004)) || (iVar2 == 0x10005)))))))))) {
      if (do_eval == 0) {
        usual_arith_conv(pa,pb);
        copy_node_type(result_node,*(void **)pa);
        return 1;
      }
      iVar2 = ternary_select_value
                        (*(void **)(*(int *)pcond + 0x10),a,*(void **)(*(int *)pb + 0x10),
                         *(void **)((int)result_node + 0x10));
      return iVar2;
    }
  }
  if (type1 == 8) {
    iVar2 = *(int *)(*(int *)pb + 0x10);
    uVar3 = *(ulong *)(iVar2 + 0x20);
    if (uVar3 == 8) goto LAB_0046fd85;
  }
  if (type1 == 9) {
    iVar2 = *(int *)(*(int *)pb + 0x10);
    uVar3 = *(ulong *)(iVar2 + 0x20);
    if (uVar3 == 9) {
LAB_0046fd85:
      iVar2 = cdb_types_match(type1,*(int *)((int)a + 0x28),uVar3,*(int *)(iVar2 + 0x28));
      if (iVar2 == 0) {
        cdb_error(s_incompatible_types_in____004d4174);
        return 0;
      }
      if (do_eval == 0) {
        copy_node_type(result_node,*(void **)pa);
        return 1;
      }
      iVar2 = ternary_select_value
                        (*(void **)(*(int *)pcond + 0x10),*(void **)(*(int *)pa + 0x10),
                         *(void **)(*(int *)pb + 0x10),*(void **)((int)result_node + 0x10));
      return iVar2;
    }
  }
  if (((byte)type1 & 0x30) == 0x10) {
    uVar3 = *(ulong *)(*(int *)(*(int *)pb + 0x10) + 0x20);
    if (((byte)uVar3 & 0x30) == 0x10) {
      iVar2 = cdb_types_match(type1,*(int *)((int)a + 0x28),uVar3,
                              *(int *)(*(int *)(*(int *)pb + 0x10) + 0x28));
      if (((iVar2 == 0) &&
          (uVar1 = *(uint *)(*(int *)(*(int *)pa + 0x10) + 0x20),
          (uVar1 >> 2 & 0x3ffebff0 | uVar1 & 0x1000f) != 1)) &&
         (uVar1 = *(uint *)(*(int *)(*(int *)pb + 0x10) + 0x20),
         (uVar1 >> 2 & 0x3ffebff0 | uVar1 & 0x1000f) != 1)) {
        cdb_error(s_invalid_types_in____004d4160);
        return 0;
      }
      if (do_eval == 0) {
        copy_node_type(result_node,*(void **)pa);
        return 1;
      }
      iVar2 = ternary_select_value
                        (*(void **)(*(int *)pcond + 0x10),*(void **)(*(int *)pa + 0x10),
                         *(void **)(*(int *)pb + 0x10),*(void **)((int)result_node + 0x10));
      return iVar2;
    }
  }
  cdb_error(s_invalid_types_in____004d4160);
  return 0;
}


/* ==== value_is_true @ 0046ff40 ==== */

int __cdecl value_is_true(void *value)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = cdb_load_value(value);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = *(int *)((int)value + 0x20);
  if (((byte)iVar2 & 0x30) == 0x10) goto LAB_00470113;
  if ((((iVar2 == 2) || (iVar2 == 3)) || (iVar2 == 4)) || ((iVar2 == 0xb || (iVar2 == 10)))) {
LAB_004700e4:
    if ((iVar2 != 5) && (iVar2 != 0xf)) goto LAB_00470113;
  }
  else if (iVar2 != 5) {
    if (((iVar2 != 0xc) && (iVar2 != 0xd)) && ((iVar2 != 0xe && (iVar2 != 0xf)))) {
      if ((iVar2 != 0x10000) && (iVar2 != 0x10001)) {
        if ((iVar2 == 0x10002) || (iVar2 == 0x10003)) {
          if (*(int *)((int)value + 0xc) != 0) {
            return 0;
          }
          if (*(int *)((int)value + 0x10) != 0) {
            return 0;
          }
          return 1;
        }
        if (iVar2 == 0x10005) {
          if (*(int *)((int)value + 0xc) != 0) {
            return 0;
          }
          if (*(int *)((int)value + 0x10) != 0) {
            return 0;
          }
          if (*(int *)((int)value + 0x14) != 0) {
            return 0;
          }
          return 1;
        }
        if (iVar2 == 0x10004) {
          if (*(int *)((int)value + 0xc) != 0) {
            return 0;
          }
          if (*(int *)((int)value + 0x10) != 0) {
            return 0;
          }
          return 1;
        }
        if ((iVar2 != 6) && (iVar2 != 7)) {
          cdb_internal_error(0x4d413c,0x554);
          return 0;
        }
        if ((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) {
          if ((((iVar2 == 6) || (cdb_arch == 0x2c7)) || (cdb_arch == 0x2c9)) ||
             ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))) {
            bVar1 = *(float *)((int)value + 8) == 0.0;
          }
          else {
            bVar1 = *(double *)value == 0.0;
          }
          if (!bVar1) {
            return 0;
          }
          return 1;
        }
        if (*(int *)((int)value + 0xc) != 0) {
          return 0;
        }
        if (*(int *)((int)value + 0x10) != 0) {
          return 0;
        }
        return 1;
      }
      goto LAB_00470113;
    }
    goto LAB_004700e4;
  }
  if (cdb_arch != 0x2c6) {
    if ((*(int *)((int)value + 0xc) == 0) && (*(int *)((int)value + 0x10) == 0)) {
      return 1;
    }
    return 0;
  }
LAB_00470113:
  return (uint)(*(int *)((int)value + 0xc) == 0);
}


/* ==== tree_mark_leaves @ 00470120 ==== */

void __cdecl tree_mark_leaves(void *node)

{
  void *pvVar1;
  undefined4 *puVar2;
  
  if (node != (void *)0x0) {
    if (*(int *)((int)node + 0xc) == 0) {
      *(undefined4 *)((int)node + 0x18) = 1;
      return;
    }
    pvVar1 = *(void **)node;
    if (pvVar1 != (void *)0x0) {
      if (*(int *)((int)pvVar1 + 0xc) == 0) {
        *(undefined4 *)((int)pvVar1 + 0x18) = 1;
      }
      else {
        tree_mark_leaves(pvVar1);
      }
    }
    pvVar1 = *(void **)((int)node + 4);
    if (pvVar1 != (void *)0x0) {
      if (*(int *)((int)pvVar1 + 0xc) == 0) {
        *(undefined4 *)((int)pvVar1 + 0x18) = 1;
      }
      else {
        tree_mark_leaves(pvVar1);
      }
      for (puVar2 = *(undefined4 **)(*(int *)((int)node + 4) + 0x14); puVar2 != (undefined4 *)0x0;
          puVar2 = (undefined4 *)puVar2[1]) {
        tree_mark_leaves((void *)*puVar2);
      }
    }
    pvVar1 = *(void **)((int)node + 8);
    if (pvVar1 != (void *)0x0) {
      if (*(int *)((int)pvVar1 + 0xc) != 0) {
        tree_mark_leaves(pvVar1);
        *(undefined4 *)((int)node + 0x18) = 0;
        return;
      }
      *(undefined4 *)((int)pvVar1 + 0x18) = 1;
    }
    *(undefined4 *)((int)node + 0x18) = 0;
  }
  return;
}


/* ==== eval_tree_core @ 004701d0 ==== */

int eval_tree_core(void)

{
  int iVar1;
  int *node;
  int *extraout_EAX;
  int *extraout_EAX_00;
  int iVar2;
  int *extraout_EAX_01;
  int *extraout_EAX_02;
  int *piVar3;
  int *node_00;
  bool bVar4;
  
  cdb_saved_pop();
  if (node != (int *)0x0) {
    piVar3 = node;
    if (((node[3] != 0) && (node[6] != 0)) &&
       (cdb_saved_pop(), piVar3 = extraout_EAX, extraout_EAX == (int *)0x0)) {
      cdb_saved_push(node);
      return 1;
    }
    if (piVar3 != (int *)0x0) {
      do {
        iVar2 = piVar3[3];
        node_00 = piVar3;
        while (iVar2 == 0x145) {
          cdb_saved_push(node_00);
          if (node_00[1] != 0) {
            arglist_free_temps(*(void **)(node_00[1] + 0x14));
          }
          cdb_saved_pop();
          bVar4 = extraout_EAX_00 == node_00;
          node_00 = extraout_EAX_00;
          if (bVar4) break;
          iVar2 = extraout_EAX_00[3];
        }
        iVar2 = *node_00;
        if ((iVar2 == 0) || (*(int *)(iVar2 + 0x18) != 1)) {
          iVar2 = node_00[1];
          if ((iVar2 != 0) && (node_00[3] == 0x138)) {
LAB_004702db:
            *(undefined4 *)(iVar2 + 0x18) = 1;
          }
        }
        else {
          iVar1 = node_00[3];
          if (iVar1 == 0x12f) {
            iVar2 = value_is_true(*(void **)(iVar2 + 0x10));
            if (iVar2 != 0) {
              iVar2 = node_00[2];
              goto joined_r0x004702c7;
            }
          }
          else if (iVar1 == 0x12e) {
            iVar2 = value_is_true(*(void **)(iVar2 + 0x10));
            if (iVar2 == 0) {
              iVar2 = node_00[2];
joined_r0x004702c7:
              if (iVar2 != 0) goto LAB_004702db;
            }
          }
          else if (iVar1 == 0x123) {
            iVar2 = value_is_true(*(void **)(iVar2 + 0x10));
            if (iVar2 == 0) {
              iVar2 = node_00[2];
            }
            else {
              iVar2 = node_00[1];
            }
            goto joined_r0x004702c7;
          }
        }
        iVar2 = *node_00;
        if (((iVar2 == 0) || (*(int *)(iVar2 + 0xc) == 0)) || (*(int *)(iVar2 + 0x18) == 1)) {
          iVar2 = node_00[1];
          if (((iVar2 == 0) || (*(int *)(iVar2 + 0xc) == 0)) || (*(int *)(iVar2 + 0x18) == 1)) {
            iVar2 = node_00[2];
            if (((iVar2 == 0) || (*(int *)(iVar2 + 0xc) == 0)) || (*(int *)(iVar2 + 0x18) == 1)) {
              iVar2 = eval_node(node_00);
              node_00[6] = 1;
              if (iVar2 == 0) {
                return 0;
              }
              if (node_00[3] == 0x145) {
                cdb_saved_push(node_00);
                return 2;
              }
              cdb_saved_pop();
              if ((extraout_EAX_01 == (int *)0x0) ||
                 (((piVar3 = extraout_EAX_01, extraout_EAX_01[3] != 0 && (extraout_EAX_01[6] != 0))
                  && (cdb_saved_pop(), piVar3 = extraout_EAX_02, node_00 = extraout_EAX_01,
                     extraout_EAX_02 == (int *)0x0)))) {
                cdb_saved_push(node_00);
                return 1;
              }
            }
            else {
              cdb_saved_push(node_00);
              piVar3 = (int *)node_00[2];
            }
          }
          else {
            cdb_saved_push(node_00);
            piVar3 = (int *)node_00[1];
          }
        }
        else {
          cdb_saved_push(node_00);
          piVar3 = (int *)*node_00;
        }
        if (piVar3 == (int *)0x0) {
          return 0;
        }
      } while( true );
    }
  }
  return 0;
}


/* ==== eval_node @ 004703c0 ==== */

int __cdecl eval_node(void *node)

{
  int iVar1;
  
  if (*(int *)node == 0) {
    if (*(int *)((int)node + 4) != 0) {
      iVar1 = eval_node_unary(node);
      return iVar1;
    }
    return 0;
  }
  if (*(int *)((int)node + 4) != 0) {
    iVar1 = eval_node_ternary(node);
    return iVar1;
  }
  iVar1 = eval_node_binary(node);
  return iVar1;
}


/* ==== arglist_free_temps @ 00470400 ==== */

void __cdecl arglist_free_temps(void *arglist)

{
  void *node;
  
  for (; arglist != (undefined4 *)0x0; arglist = *(void **)((int)arglist + 4)) {
    node = *(void **)arglist;
    if ((*(int *)((int)node + 0xc) != 0) && (*(int *)((int)node + 0x18) == 0)) {
      cdb_saved_push(node);
    }
  }
  return;
}


/* ==== eval_node_binary @ 00470430 ==== */

int __cdecl eval_node_binary(void *node)

{
  int iVar1;
  
  iVar1 = eval_binary(node,(void *)((int)node + 8),*(int *)((int)node + 0xc),node,1);
  return iVar1;
}


/* ==== eval_node_unary @ 00470450 ==== */

int __cdecl eval_node_unary(void *node)

{
  int iVar1;
  
  iVar1 = eval_unary((void *)((int)node + 4),*(int *)((int)node + 0xc),node,1);
  return iVar1;
}


/* ==== eval_node_ternary @ 00470470 ==== */

int __cdecl eval_node_ternary(void *node)

{
  int iVar1;
  
  iVar1 = eval_ternary(node,(void *)((int)node + 4),(void *)((int)node + 8),node,1);
  return iVar1;
}


/* ==== value_neg @ 00470490 ==== */

int __cdecl value_neg(void *src,void *dst)

{
  int iVar1;
  uint uVar2;
  double local_40 [8];
  
  iVar1 = cdb_load_value(src);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = *(int *)((int)src + 0x20);
  if ((iVar1 == 5) || (iVar1 == 0xf)) {
LAB_0047079e:
    *(ulong *)((int)dst + 0xc) = (~*(uint *)((int)src + 0xc) & cdb_word_mask) + 1;
    *(uint *)((int)dst + 0x10) = ~*(uint *)((int)src + 0x10);
    tw_normalize((ulong *)((int)dst + 0xc));
    return 1;
  }
  if (((iVar1 == 2) ||
      ((((iVar1 == 3 || (iVar1 == 4)) || (iVar1 == 0xb)) || ((iVar1 == 10 || (iVar1 == 0xc)))))) ||
     ((iVar1 == 0xd || (iVar1 == 0xe)))) {
    *(uint *)((int)dst + 0xc) = -*(int *)((int)src + 0xc) & cdb_word_mask;
    *(undefined4 *)((int)dst + 0x10) = 0;
    return 1;
  }
  if ((iVar1 == 0x10000) || (iVar1 == 0x10001)) {
    *(uint *)((int)dst + 0xc) = -*(int *)((int)src + 0xc) & cdb_word_mask;
    *(undefined4 *)((int)dst + 0x10) = 0;
    return 1;
  }
  if ((iVar1 == 0x10002) || (iVar1 == 0x10003)) goto LAB_0047079e;
  if (iVar1 == 0x10005) {
    *(ulong *)((int)dst + 0xc) = (~*(uint *)((int)src + 0xc) & cdb_word_mask) + 1;
    *(uint *)((int)dst + 0x10) = ~*(uint *)((int)src + 0x10) & cdb_word_mask;
    *(uint *)((int)dst + 0x14) = ~*(uint *)((int)src + 0x14) & cdb_ext_mask;
    tw_normalize((ulong *)((int)dst + 0xc));
    return 1;
  }
  if (iVar1 == 0x10004) {
    *(uint *)((int)dst + 0xc) = (~*(uint *)((int)src + 0xc) & cdb_word_mask) + 1;
    *(uint *)((int)dst + 0x10) = ~*(uint *)((int)src + 0x10) & cdb_ext_mask;
    return 1;
  }
  if (iVar1 == 6) {
    if ((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) {
      *(float *)((int)dst + 8) = -*(float *)((int)src + 8);
      return 1;
    }
    if (*(int *)((int)src + 0x10) == 0x800000) {
      *(undefined4 *)((int)dst + 0x10) = 0x400000;
      *(int *)((int)dst + 0xc) = *(int *)((int)src + 0xc) + 1;
      return 1;
    }
    *(undefined4 *)((int)dst + 0xc) = *(undefined4 *)((int)src + 0xc);
    uVar2 = (~*(uint *)((int)src + 0x10) & 0xffffff) + 1;
    *(uint *)((int)dst + 0x10) = uVar2;
    if (((uVar2 & 0x800000) == 0) || ((uVar2 & 0x400000) == 0)) goto LAB_00470723;
    *(uint *)((int)dst + 0x10) = uVar2 * 2;
  }
  else {
    if (iVar1 != 7) {
      cdb_internal_error(0x4d413c,0xdc0);
      return 0;
    }
    if ((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) {
      if ((((cdb_arch != 0x2c7) && (cdb_arch != 0x2c9)) && (cdb_arch != 0x2cb)) &&
         (cdb_arch != 0x2ca)) {
        value_copy_trunc(src,local_40);
        *(double *)dst = -local_40[0];
        value_copy_trunc(dst,dst);
        return 1;
      }
      *(float *)((int)dst + 8) = -*(float *)((int)src + 8);
      return 1;
    }
    if (*(int *)((int)src + 0x10) == 0x800000) {
      *(undefined4 *)((int)dst + 0x10) = 0x400000;
      *(int *)((int)dst + 0xc) = *(int *)((int)src + 0xc) + 1;
      return 1;
    }
    *(undefined4 *)((int)dst + 0xc) = *(undefined4 *)((int)src + 0xc);
    uVar2 = (~*(uint *)((int)src + 0x10) & 0xffffff) + 1;
    *(uint *)((int)dst + 0x10) = uVar2;
    if (((uVar2 & 0x800000) == 0) || ((uVar2 & 0x400000) == 0)) goto LAB_00470723;
    *(uint *)((int)dst + 0x10) = uVar2 * 2;
  }
  *(int *)((int)dst + 0xc) = *(int *)((int)dst + 0xc) + -1;
LAB_00470723:
  *(uint *)((int)dst + 0x10) = *(uint *)((int)dst + 0x10) & 0xffffff;
  return 1;
}


/* ==== value_copy_trunc @ 004707e0 ==== */

void __cdecl value_copy_trunc(void *src,void *dst)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = dst;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *(undefined4 *)src;
    src = (undefined4 *)((int)src + 4);
    puVar2 = puVar2 + 1;
  }
  *(uint *)dst = *(uint *)dst & 0xffe00000;
  return;
}


/* ==== ternary_select_value @ 00470800 ==== */

int __cdecl ternary_select_value(void *cond,void *a,void *b,void *out)

{
  int iVar1;
  
  iVar1 = cdb_load_value(cond);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = value_is_true(cond);
  if (iVar1 != 0) {
    a = b;
  }
  iVar1 = cdb_load_value(a);
  if (iVar1 == 0) {
    return 0;
  }
  *(undefined4 *)out = *(undefined4 *)a;
  *(undefined4 *)((int)out + 4) = *(undefined4 *)((int)a + 4);
  *(undefined4 *)((int)out + 8) = *(undefined4 *)((int)a + 8);
  *(undefined4 *)((int)out + 0xc) = *(undefined4 *)((int)a + 0xc);
  *(undefined4 *)((int)out + 0x10) = *(undefined4 *)((int)a + 0x10);
  *(undefined4 *)((int)out + 0x14) = *(undefined4 *)((int)a + 0x14);
  return 1;
}


/* ==== eval_dot_values @ 00470870 ==== */

int __cdecl eval_dot_values(void *base,void *member,void *out)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)((int)member + 0x24) == 0x12) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)((int)member + 0xc);
  }
  if (*(short *)((int)base + 0x3c) == 1) {
    iVar1 = *(int *)((int)base + 0x24);
    if ((iVar1 == 2) || (iVar1 == 3)) {
      member = *(void **)((int)base + 0x1c);
      base = *(void **)((int)base + 0x18);
    }
    else {
      if ((iVar1 != 1) && (iVar1 != 9)) {
        cdb_internal_error(0x4d413c,0x13c3);
        return 0;
      }
      iVar1 = cdb_frame_slot(*(int *)((int)base + 0x1c),*(int *)((int)base + 0x18),(int *)&member,
                             (ulong *)&base);
      if (iVar1 == 0) {
        return 0;
      }
    }
  }
  else {
    member = *(void **)((int)base + 0x10);
    base = *(void **)((int)base + 0xc);
  }
  *(void **)((int)out + 0x1c) = member;
  *(int *)((int)out + 0x18) = iVar2 + (int)base;
  *(uint *)((int)out + 0x18) = cdb_addr_mask & iVar2 + (int)base;
  return 1;
}


/* ==== eval_arrow_values @ 00470920 ==== */

int __cdecl eval_arrow_values(void *base,void *member,void *out)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = cdb_load_value(base);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = cdb_default_space();
  *(int *)((int)out + 0x1c) = iVar2;
  if (*(int *)((int)member + 0x24) != 0x12) {
    *(int *)((int)out + 0x18) = *(int *)((int)member + 0xc) + *(int *)((int)base + 0xc);
    *(uint *)((int)out + 0x18) = *(uint *)((int)out + 0x18) & cdb_addr_mask;
    return 1;
  }
  uVar1 = *(uint *)((int)base + 0xc);
  *(uint *)((int)out + 0x18) = uVar1;
  *(uint *)((int)out + 0x18) = uVar1 & cdb_addr_mask;
  return 1;
}


/* ==== dw_add @ 00470980 ==== */

int __cdecl dw_add(ulong *a,ulong *b,ulong *out)

{
  ulong uVar1;
  ulong uVar2;
  uint uVar3;
  
  uVar1 = *b;
  uVar2 = *a;
  *out = uVar2 + uVar1;
  uVar3 = ((~cdb_word_mask & uVar2 + uVar1) >> ((byte)cdb_word_bits & 0x1f)) + a[1] + b[1];
  out[1] = uVar3;
  *out = *out & cdb_word_mask;
  out[1] = uVar3 & cdb_word_mask;
  return 1;
}


/* ==== dw_add_b @ 004709e0 ==== */

int __cdecl dw_add_b(ulong *a,ulong *b,ulong *out)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0;
  uVar1 = *b + *a;
  *out = uVar1;
  if ((uVar1 < *a) || (uVar1 < *b)) {
    iVar2 = 1;
  }
  out[1] = b[1] + a[1] + iVar2;
  *out = *out & cdb_word_mask;
  out[1] = out[1] & cdb_word_mask;
  return 1;
}


/* ==== dw_neg @ 00470a40 ==== */

int __cdecl dw_neg(ulong *a)

{
  uint uVar1;
  
  uVar1 = (~*a & cdb_word_mask) + 1;
  *a = uVar1;
  a[1] = ((~cdb_word_mask & uVar1) >> ((byte)cdb_word_bits & 0x1f)) + ~a[1];
  *a = *a & cdb_word_mask;
  a[1] = a[1] & cdb_word_mask;
  return 1;
}


/* ==== dw_neg_b @ 00470a90 ==== */

int __cdecl dw_neg_b(ulong *a)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = ~*a & cdb_word_mask;
  uVar1 = uVar2 + 1;
  *a = uVar1;
  uVar2 = ~a[1] + (uint)(uVar1 < uVar2);
  a[1] = uVar2;
  *a = cdb_word_mask & uVar1;
  a[1] = cdb_word_mask & uVar2;
  return 1;
}


/* ==== dw_shl1 @ 00470ae0 ==== */

int __cdecl dw_shl1(ulong *a)

{
  uint uVar1;
  
  uVar1 = *a << 1;
  *a = uVar1;
  a[1] = (uint)((cdb_sign_bit * 2 & uVar1) != 0) | a[1] << 1;
  *a = cdb_word_mask & uVar1;
  a[1] = a[1] & cdb_word_mask;
  return 1;
}


/* ==== dw_shl1_b @ 00470b30 ==== */

int __cdecl dw_shl1_b(ulong *a)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = cdb_sign_bit & *a;
  uVar1 = *a * 2;
  *a = uVar1;
  uVar2 = a[1] << 1 | (uint)(uVar2 != 0);
  a[1] = uVar2;
  *a = cdb_word_mask & uVar1;
  a[1] = cdb_word_mask & uVar2;
  return 1;
}


/* ==== dw_shr1 @ 00470b70 ==== */

int __cdecl dw_shr1(ulong *a)

{
  if ((a[1] & 1) != 0) {
    *a = *a | cdb_sign_bit * 2;
  }
  a[1] = a[1] >> 1;
  *a = *a >> 1;
  return 1;
}


/* ==== dw_shr1_b @ 00470ba0 ==== */

int __cdecl dw_shr1_b(ulong *a)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = a[1];
  a[1] = uVar1 >> 1;
  uVar2 = *a;
  *a = uVar2 >> 1;
  *a = -(uint)((uVar1 & 1) != 0) & cdb_sign_bit | uVar2 >> 1;
  return 1;
}


/* ==== dw_cmp @ 00470bd0 ==== */

int __cdecl dw_cmp(ulong *a,ulong *b)

{
  if (b[1] < a[1]) {
    return 1;
  }
  if (a[1] < b[1]) {
    return -1;
  }
  if (*b < *a) {
    return 1;
  }
  return -(uint)(*a < *b);
}


/* ==== tw_normalize @ 00470c10 ==== */

void __cdecl tw_normalize(ulong *w)

{
  uint uVar1;
  
  uVar1 = ~cdb_word_mask & *w;
  if (uVar1 != 0) {
    w[1] = w[1] + (uVar1 >> ((byte)cdb_word_bits & 0x1f));
  }
  uVar1 = ~cdb_word_mask & w[1];
  if (uVar1 != 0) {
    w[2] = w[2] + (uVar1 >> ((byte)cdb_word_bits & 0x1f));
  }
  *w = cdb_word_mask & *w;
  w[1] = cdb_word_mask & w[1];
  w[2] = w[2] & cdb_ext_mask;
  return;
}


/* ==== mant_to_double @ 00470c80 ==== */

void __cdecl mant_to_double(void *value)

{
  if ((*(int *)((int)value + 0xc) == 0) && (*(int *)((int)value + 0x10) == 0)) {
    *(undefined4 *)value = 0;
    *(undefined4 *)((int)value + 4) = 0;
    return;
  }
  *(uint *)((int)value + 4) =
       *(uint *)((int)value + 0x10) >> 2 & 0xfffff | (*(int *)((int)value + 0xc) + 0x3ff) * 0x100000
  ;
  *(uint *)value = *(uint *)((int)value + 0x10) << 0x1e;
  return;
}


/* ==== double_to_mant @ 00470cc0 ==== */

void __cdecl double_to_mant(void *value)

{
  uint uVar1;
  
  if (*(double *)value == 0.0) {
    *(undefined4 *)((int)value + 0xc) = 0;
    *(undefined4 *)((int)value + 0x10) = 0;
    *(undefined4 *)((int)value + 0x14) = 0;
    return;
  }
  *(uint *)((int)value + 0xc) = (*(uint *)((int)value + 4) >> 0x14 & 0x7ff) + 0x1c01;
  uVar1 = (*(uint *)((int)value + 4) & 0xfffff | 0x100000) << 2 | *(uint *)value >> 0x1e;
  *(uint *)((int)value + 0x10) = uVar1;
  if (((*(uint *)value & 0x20000000) != 0) &&
     (*(uint *)((int)value + 0x10) = uVar1 + 1, (uVar1 + 1 & 0x800000) != 0)) {
    *(uint *)((int)value + 0x10) = uVar1;
  }
  return;
}


/* ==== eval_subscript @ 00470d40 ==== */

int __cdecl eval_subscript(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  void *idx;
  uint uVar1;
  int iVar2;
  void *src_node;
  
  src_node = *(void **)plhs;
  idx = *(void **)((int)src_node + 0x10);
  iVar2 = *(int *)((int)idx + 0x20);
  if (((byte)iVar2 & 0x30) == 0x10) {
    iVar2 = *(int *)((int)*(void **)(*(int *)prhs + 0x10) + 0x20);
    if (((((iVar2 != 2) && (iVar2 != 3)) && (iVar2 != 4)) &&
        (((iVar2 != 0xb && (iVar2 != 10)) && ((iVar2 != 5 && ((iVar2 != 0xc && (iVar2 != 0xd))))))))
       && ((iVar2 != 0xe && (iVar2 != 0xf)))) {
      cdb_error(s_array_subscript_is_not_an_intege_004d41f0);
      return 0;
    }
    if (do_eval != 0) {
      iVar2 = subscript_values(idx,*(void **)(*(int *)prhs + 0x10),
                               *(void **)((int)result_node + 0x10));
      return iVar2;
    }
  }
  else {
    src_node = *(void **)prhs;
    if (((byte)*(undefined4 *)((int)*(void **)((int)src_node + 0x10) + 0x20) & 0x30) != 0x10) {
      cdb_error(s_trying_to_subscript_something_wh_004d41bc);
      return 0;
    }
    if (((((((iVar2 != 2) && (iVar2 != 3)) && (iVar2 != 4)) && ((iVar2 != 0xb && (iVar2 != 10)))) &&
         ((iVar2 != 5 && ((iVar2 != 0xc && (iVar2 != 0xd)))))) && (iVar2 != 0xe)) && (iVar2 != 0xf))
    {
      cdb_error(s_array_subscript_is_not_an_intege_004d41f0);
      return 0;
    }
    plhs = prhs;
    if (do_eval != 0) {
      iVar2 = subscript_values(*(void **)((int)src_node + 0x10),idx,
                               *(void **)((int)result_node + 0x10));
      return iVar2;
    }
  }
  copy_node_type(result_node,src_node);
  uVar1 = *(uint *)(*(int *)(*(int *)plhs + 0x10) + 0x20);
  *(uint *)(*(int *)((int)result_node + 0x10) + 0x20) = uVar1 >> 2 & 0x3ffebff0 | uVar1 & 0x1000f;
  *(undefined2 *)(*(int *)((int)result_node + 0x10) + 0x3c) = 1;
  *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x24) = 2;
  return 1;
}


/* ==== subscript_values @ 00470ea0 ==== */

int __cdecl subscript_values(void *ptr,void *idx,void *out)

{
  ptr_add_values(ptr,idx,out);
  *(undefined4 *)((int)out + 0x1c) = *(undefined4 *)((int)out + 0x10);
  *(undefined4 *)((int)out + 0x18) = *(undefined4 *)((int)out + 0xc);
  return 1;
}


/* ==== ptr_add_values @ 00470ed0 ==== */

int __cdecl ptr_add_values(void *ptr,void *idx,void *out)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 va0;
  int local_100 [4];
  undefined4 local_f0;
  undefined4 local_e0;
  undefined4 local_c0 [8];
  uint local_a0;
  int local_80 [8];
  int local_60;
  undefined1 local_40 [12];
  int local_34;
  undefined4 local_20;
  
  iVar1 = cdb_load_value(ptr);
  if (iVar1 != 0) {
    iVar1 = cdb_load_value(idx);
    if (iVar1 != 0) {
      piVar2 = ptr;
      piVar3 = local_100;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *piVar3 = *piVar2;
        piVar2 = piVar2 + 1;
        piVar3 = piVar3 + 1;
      }
      piVar2 = local_80;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *piVar2 = *(int *)idx;
        idx = (int *)((int)idx + 4);
        piVar2 = piVar2 + 1;
      }
      if (((byte)local_e0 & 0x30) == 0x10) {
        if ((((((local_60 == 2) || (local_60 == 3)) || (local_60 == 4)) ||
             ((local_60 == 0xb || (local_60 == 10)))) ||
            ((local_60 == 5 || ((local_60 == 0xc || (local_60 == 0xd)))))) ||
           ((local_60 == 0xe || (local_60 == 0xf)))) {
          puVar4 = local_c0;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar4 = *(undefined4 *)ptr;
            ptr = (undefined4 *)((int)ptr + 4);
            puVar4 = puVar4 + 1;
          }
          local_20 = 4;
          local_a0 = local_a0 >> 2 & 0x3ffebff0 | local_a0 & 0x1000f;
          type_size(local_c0,local_40);
          *(uint *)((int)out + 0xc) = local_80[3] * local_34 + local_100[3] & cdb_addr_mask;
          *(undefined4 *)((int)out + 0x10) = local_f0;
          return 1;
        }
        va0 = 0x79c;
      }
      else {
        va0 = 0x7a2;
      }
      cdb_internal_error(0x4d413c,va0);
    }
  }
  return 0;
}


/* ==== coerce_array_func @ 00471020 ==== */

void __cdecl coerce_array_func(void *pnode)

{
  void *node;
  uint uVar1;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  
  node = *(void **)pnode;
  if (*(short *)(*(int *)((int)node + 0x10) + 0x3c) == 1) {
    uVar1 = *(uint *)(*(int *)((int)node + 0x10) + 0x20) & 0x30;
    if (uVar1 == 0x30) {
      make_array_ptr_node(node);
      *(undefined4 *)pnode = extraout_EAX;
      return;
    }
    if (uVar1 == 0x20) {
      make_func_ptr_node(node);
      *(undefined4 *)pnode = extraout_EAX_00;
    }
  }
  return;
}


/* ==== make_func_ptr_node @ 00471060 ==== */

void __cdecl make_func_ptr_node(void *node)

{
  uint uVar1;
  undefined4 *extraout_EAX;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  new_node();
  if (extraout_EAX == (undefined4 *)0x0) {
    return;
  }
  *extraout_EAX = 0;
  extraout_EAX[1] = node;
  extraout_EAX[2] = 0;
  extraout_EAX[5] = 0;
  puVar3 = *(undefined4 **)((int)node + 0x10);
  puVar4 = (undefined4 *)extraout_EAX[4];
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  uVar1 = *(uint *)(extraout_EAX[4] + 0x20);
  *(uint *)(extraout_EAX[4] + 0x20) = uVar1 & 0x1000f | (uVar1 & 0xfffefff4 | 4) << 2;
  extraout_EAX[3] = 0x149;
  *(undefined2 *)(extraout_EAX[4] + 0x3c) = 0;
  *(undefined4 *)(extraout_EAX[4] + 0x24) = 2;
  return;
}


/* ==== make_array_ptr_node @ 004710d0 ==== */

void __cdecl make_array_ptr_node(void *node)

{
  undefined4 *extraout_EAX;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  new_node();
  if (extraout_EAX == (undefined4 *)0x0) {
    return;
  }
  *extraout_EAX = 0;
  extraout_EAX[1] = node;
  extraout_EAX[2] = 0;
  extraout_EAX[5] = 0;
  puVar2 = *(undefined4 **)((int)node + 0x10);
  puVar3 = (undefined4 *)extraout_EAX[4];
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  *(uint *)(extraout_EAX[4] + 0x20) = *(uint *)(extraout_EAX[4] + 0x20) & 0xffffffdf | 0x10;
  *(undefined4 *)(extraout_EAX[4] + 0x2c) = *(undefined4 *)(extraout_EAX[4] + 0x30);
  *(undefined4 *)(extraout_EAX[4] + 0x30) = *(undefined4 *)(extraout_EAX[4] + 0x34);
  *(undefined4 *)(extraout_EAX[4] + 0x34) = *(undefined4 *)(extraout_EAX[4] + 0x38);
  *(undefined4 *)(extraout_EAX[4] + 0x38) = 1;
  extraout_EAX[3] = 0x148;
  *(undefined2 *)(extraout_EAX[4] + 0x3c) = 0;
  *(undefined4 *)(extraout_EAX[4] + 0x24) = 2;
  return;
}


/* ==== eval_cast @ 00471160 ==== */

int __cdecl eval_cast(void *ptype,void *pval,int op,void *result_node,int do_eval)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)((int)*(void **)(*(int *)ptype + 0x10) + 0x20);
  if ((((((iVar2 != 2) && (iVar2 != 3)) && (iVar2 != 4)) &&
       (((iVar2 != 0xb && (iVar2 != 10)) && ((iVar2 != 5 && ((iVar2 != 0xc && (iVar2 != 0xd))))))))
      && ((iVar2 != 0xe &&
          (((((iVar2 != 0xf && (iVar2 != 6)) && (iVar2 != 7)) &&
            ((iVar2 != 0x10000 && (iVar2 != 0x10001)))) && (iVar2 != 0x10003)))))) &&
     (((iVar2 != 0x10002 && (iVar2 != 0x10004)) &&
      ((iVar2 != 0x10005 && ((((byte)iVar2 & 0x30) != 0x10 && (iVar2 != 1)))))))) {
    cdb_error(s_conversion_to_non_scalar_type_at_004d428c);
    return 0;
  }
  iVar1 = *(int *)((int)*(void **)(*(int *)pval + 0x10) + 0x20);
  if ((iVar1 != 2) &&
     (((((iVar1 != 3 && (iVar1 != 4)) && (iVar1 != 0xb)) &&
       (((iVar1 != 10 && (iVar1 != 5)) && ((iVar1 != 0xc && ((iVar1 != 0xd && (iVar1 != 0xe))))))))
      && ((iVar1 != 0xf &&
          (((((iVar1 != 6 && (iVar1 != 7)) && (iVar1 != 0x10000)) &&
            ((iVar1 != 0x10001 && (iVar1 != 0x10003)))) &&
           (((iVar1 != 0x10002 && ((iVar1 != 0x10004 && (iVar1 != 0x10005)))) &&
            (((byte)iVar1 & 0x30) != 0x10)))))))))) {
    cdb_error(s_conversion_of_non_scalar_to_scal_004d425c);
    return 0;
  }
  if (((byte)iVar2 & 0x30) == 0x10) {
    if ((iVar1 == 6) || (iVar1 == 7)) {
      cdb_error(s_cannot_cast_from_float_to_pointe_004d4238);
      return 0;
    }
  }
  else if (((iVar2 == 6) || (iVar2 == 7)) && (((byte)iVar1 & 0x30) == 0x10)) {
    cdb_error(s_cannot_cast_from_pointer_to_floa_004d4214);
    return 0;
  }
  if (do_eval == 0) {
    integral_promote(pval);
    copy_node_type(result_node,*(void **)ptype);
    return 1;
  }
  iVar2 = cast_value(*(void **)(*(int *)ptype + 0x10),*(void **)(*(int *)pval + 0x10),
                     *(void **)((int)result_node + 0x10));
  return iVar2;
}


/* ==== cast_value @ 00471330 ==== */

int __cdecl cast_value(void *to_type,void *from_value,void *out)

{
  int iVar1;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int extraout_EAX_03;
  int extraout_EAX_04;
  int extraout_EAX_05;
  
  iVar1 = cdb_load_value(from_value);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = *(int *)((int)to_type + 0x20);
  if (((byte)iVar1 & 0x30) == 0x10) {
    iVar1 = cast_to_pointer(from_value,out);
    return iVar1;
  }
  if ((((iVar1 != 2) && (iVar1 != 3)) && (iVar1 != 4)) && ((iVar1 != 0xb && (iVar1 != 10)))) {
    if (iVar1 == 5) goto LAB_0047150a;
    if (((iVar1 != 0xc) && (iVar1 != 0xd)) && ((iVar1 != 0xe && (iVar1 != 0xf)))) {
      if (iVar1 == 6) {
        iVar1 = cast_to_float(from_value,out);
        return iVar1;
      }
      if (iVar1 == 7) {
        iVar1 = cast_to_double(from_value,out);
        return iVar1;
      }
      if (iVar1 == 1) {
        return 1;
      }
      if (((iVar1 == 0x10000) || (iVar1 == 0x10001)) ||
         ((iVar1 == 0x10003 || ((iVar1 == 0x10002 || (iVar1 == 0x10004)))))) {
        if (iVar1 != 0x10005) {
          if (iVar1 == 0x10003) {
            cast_to_fract_3(from_value,out);
            return extraout_EAX;
          }
          if (iVar1 == 0x10002) {
            cast_to_fract_2(from_value,out);
            return extraout_EAX_00;
          }
          if (iVar1 == 0x10004) {
            cast_to_fract_4(from_value,out);
            return extraout_EAX_01;
          }
          if (iVar1 == 0x10001) {
            cast_to_fract_0(from_value,out);
            return extraout_EAX_02;
          }
          if (iVar1 == 0x10000) {
            cast_to_fract_1(from_value,out);
            return extraout_EAX_03;
          }
          return 0;
        }
      }
      else if (iVar1 != 0x10005) {
        cdb_internal_error(0x4d413c,0xc3e);
        return 0;
      }
      iVar1 = cast_to_fract_common(from_value,out);
      return iVar1;
    }
  }
  if ((iVar1 != 5) && (iVar1 != 0xf)) {
    if ((((iVar1 != 2) && (iVar1 != 3)) && (iVar1 != 4)) && ((iVar1 != 0xb && (iVar1 != 10)))) {
      cast_to_int_kind(from_value,out,0);
      return extraout_EAX_04;
    }
    cast_to_int_kind(from_value,out,1);
    return extraout_EAX_05;
  }
LAB_0047150a:
  iVar1 = cast_to_uint_kind(from_value,out,(uint)(iVar1 == 5));
  return iVar1;
}


/* ==== cast_to_pointer @ 00471530 ==== */

int __cdecl cast_to_pointer(void *from_value,void *out)

{
  int iVar1;
  
  if ((*(int *)((int)from_value + 0x20) != 6) && (*(int *)((int)from_value + 0x20) != 7)) {
    *(uint *)((int)out + 0xc) = *(uint *)((int)from_value + 0xc) & cdb_addr_mask;
    iVar1 = cdb_default_space();
    *(int *)((int)out + 0x10) = iVar1;
    return 1;
  }
  cdb_c_error(s_cannot_cast_from_float_to_pointe_004d4238);
  return 0;
}


/* ==== cast_to_int_kind @ 00471580 ==== */

void __cdecl cast_to_int_kind(void *from,void *out,int flags)

{
  ulong *puVar1;
  int iVar2;
  uint *puVar3;
  bool bVar4;
  longlong lVar5;
  uint local_40 [4];
  uint local_30;
  uint local_20;
  
  *(undefined4 *)((int)out + 0x10) = 0;
  puVar3 = local_40;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *(uint *)from;
    from = (uint *)((int)from + 4);
    puVar3 = puVar3 + 1;
  }
  if ((((((((local_20 & 0x30) == 0x10) || (local_20 == 2)) || (local_20 == 3)) ||
        ((local_20 == 4 || (local_20 == 0xb)))) ||
       ((local_20 == 10 || ((local_20 == 5 || (local_20 == 0xc)))))) || (local_20 == 0xd)) ||
     ((local_20 == 0xe || (local_20 == 0xf)))) {
    if ((local_20 & 0x30) == 0x10) {
      *(uint *)((int)out + 0x10) = local_30;
    }
    *(uint *)((int)out + 0xc) = local_40[3] & cdb_word_mask;
    if (cdb_arch != 0x2cb) {
      return;
    }
    *(uint *)((int)out + 0x10) = local_30 & cdb_word_mask;
    return;
  }
  if (local_20 == 6) {
    if ((cdb_arch != 0x2c8) && (cdb_arch != 0x2c5)) {
      lVar5 = _ftol();
      *(uint *)((int)out + 0xc) = (uint)lVar5;
      *(uint *)((int)out + 0xc) = cdb_word_mask & (uint)lVar5;
      return;
    }
    bVar4 = (local_30 & 0x800000) != 0;
    if (bVar4) {
      value_neg(local_40,local_40);
    }
    puVar1 = (ulong *)((int)out + 0xc);
    iVar2 = 0x2016 - local_40[3];
    *(undefined4 *)((int)out + 0x10) = 0;
    *puVar1 = local_30;
    if (iVar2 < 0) {
      iVar2 = -iVar2;
      while ((local_30 & 0x800000) == 0) {
        dw_shl1(puVar1);
        iVar2 = iVar2 + -1;
        if (iVar2 == 0) break;
        local_30 = *puVar1;
      }
      goto LAB_004717f9;
    }
    if (local_30 == 0) goto LAB_004717f9;
    do {
      dw_shr1(puVar1);
      iVar2 = iVar2 + -1;
      if (iVar2 == 0) goto LAB_004717f9;
    } while (*puVar1 != 0);
    if ((flags != 0) && ((*puVar1 & 0x800000) != 0)) {
      *puVar1 = 0x7fffff;
      goto LAB_00471823;
    }
  }
  else {
    if (local_20 != 7) {
      return;
    }
    if ((cdb_arch != 0x2c8) && (cdb_arch != 0x2c5)) {
      if ((cdb_arch != 0x2c7) &&
         (((cdb_arch != 0x2c9 && (cdb_arch != 0x2cb)) && (cdb_arch != 0x2ca)))) {
        lVar5 = _ftol();
        *(uint *)((int)out + 0xc) = (uint)lVar5;
        *(uint *)((int)out + 0xc) = cdb_word_mask & (uint)lVar5;
        return;
      }
      lVar5 = _ftol();
      *(uint *)((int)out + 0xc) = (uint)lVar5;
      *(uint *)((int)out + 0xc) = cdb_word_mask & (uint)lVar5;
      return;
    }
    bVar4 = (local_30 & 0x800000) != 0;
    if (bVar4) {
      value_neg(local_40,local_40);
    }
    puVar1 = (ulong *)((int)out + 0xc);
    iVar2 = 0x2016 - local_40[3];
    *(undefined4 *)((int)out + 0x10) = 0;
    *puVar1 = local_30;
    if (iVar2 < 0) {
      iVar2 = -iVar2;
      while ((local_30 & 0x800000) == 0) {
        dw_shl1(puVar1);
        iVar2 = iVar2 + -1;
        if (iVar2 == 0) break;
        local_30 = *puVar1;
      }
    }
    else {
      while (local_30 != 0) {
        dw_shr1(puVar1);
        iVar2 = iVar2 + -1;
        if (iVar2 == 0) break;
        local_30 = *puVar1;
      }
    }
LAB_004717f9:
    if ((flags != 0) && ((*(uint *)((int)out + 0xc) & 0x800000) != 0)) {
      *(uint *)((int)out + 0xc) = 0x7fffff;
      goto LAB_00471823;
    }
  }
  if ((iVar2 != 0) && ((*(uint *)((int)out + 0xc) & 0x800000) != 0)) {
    *(uint *)((int)out + 0xc) = 0xffffff;
  }
LAB_00471823:
  if ((bVar4) && (flags != 0)) {
    value_neg(out,out);
    return;
  }
  return;
}


/* ==== cast_to_uint_kind @ 00471890 ==== */

int __cdecl cast_to_uint_kind(void *from,void *out,int flags)

{
  ulong *puVar1;
  int iVar2;
  uint *puVar3;
  bool bVar4;
  longlong lVar5;
  uint local_40 [4];
  uint local_30;
  int local_20;
  
  *(undefined4 *)((int)out + 0x10) = 0;
  puVar3 = local_40;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *(uint *)from;
    from = (uint *)((int)from + 4);
    puVar3 = puVar3 + 1;
  }
  if (((((((byte)local_20 & 0x30) == 0x10) || (local_20 == 2)) || (local_20 == 3)) ||
      ((local_20 == 4 || (local_20 == 0xb)))) || (local_20 == 10)) {
LAB_00471baa:
    if ((local_20 != 5) && (local_20 != 0xf)) goto LAB_00471bc3;
  }
  else if (local_20 != 5) {
    if (((local_20 != 0xc) && (local_20 != 0xd)) && ((local_20 != 0xe && (local_20 != 0xf)))) {
      if (local_20 == 6) {
        if ((cdb_arch != 0x2c8) && (cdb_arch != 0x2c5)) {
          lVar5 = _ftol();
          *(int *)((int)out + 0xc) = (int)lVar5;
          if ((cdb_arch == 0x2c7) ||
             (((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)) || (cdb_arch == 0x2c9)))) {
            word_split_hi(out);
          }
          *(uint *)((int)out + 0xc) = *(uint *)((int)out + 0xc) & cdb_word_mask;
          return 1;
        }
        bVar4 = (local_30 & 0x800000) != 0;
        if (bVar4) {
          value_neg(local_40,local_40);
        }
        puVar1 = (ulong *)((int)out + 0xc);
        iVar2 = 0x2016 - local_40[3];
        *(undefined4 *)((int)out + 0x10) = 0;
        *puVar1 = local_30;
        if (iVar2 < 0) {
          iVar2 = -iVar2;
          do {
            dw_shl1(puVar1);
            iVar2 = iVar2 + -1;
            if (iVar2 == 0) break;
          } while ((*(uint *)((int)out + 0x10) & 0x800000) == 0);
        }
        else {
          do {
            if ((*puVar1 == 0) && (*(int *)((int)out + 0x10) == 0)) break;
            dw_shr1(puVar1);
            iVar2 = iVar2 + -1;
          } while (iVar2 != 0);
        }
      }
      else {
        if (local_20 != 7) {
          return 0;
        }
        if ((cdb_arch != 0x2c8) && (cdb_arch != 0x2c5)) {
          if ((cdb_arch != 0x2c7) &&
             (((cdb_arch != 0x2c9 && (cdb_arch != 0x2cb)) && (cdb_arch != 0x2ca)))) {
            if (flags != 0) {
              lVar5 = _ftol();
              *(int *)((int)out + 0xc) = (int)lVar5;
              *(uint *)((int)out + 0xc) = *(uint *)((int)out + 0xc) & cdb_word_mask;
              return 1;
            }
            lVar5 = _ftol();
            *(int *)((int)out + 0xc) = (int)lVar5;
            *(uint *)((int)out + 0xc) = *(uint *)((int)out + 0xc) & cdb_word_mask;
            return 1;
          }
          lVar5 = _ftol();
          *(int *)((int)out + 0xc) = (int)lVar5;
          word_split_hi(out);
          *(uint *)((int)out + 0xc) = *(uint *)((int)out + 0xc) & cdb_word_mask;
          return 1;
        }
        bVar4 = (local_30 & 0x800000) != 0;
        if (bVar4) {
          value_neg(local_40,local_40);
        }
        iVar2 = 0x2016 - local_40[3];
        puVar1 = (ulong *)((int)out + 0xc);
        *(undefined4 *)((int)out + 0x10) = 0;
        *puVar1 = local_30;
        if (iVar2 < 0) {
          iVar2 = -iVar2;
          do {
            dw_shl1(puVar1);
            iVar2 = iVar2 + -1;
            if (iVar2 == 0) break;
          } while ((*(uint *)((int)out + 0x10) & 0x800000) == 0);
        }
        else {
          do {
            if ((*puVar1 == 0) && (*(int *)((int)out + 0x10) == 0)) break;
            dw_shr1(puVar1);
            iVar2 = iVar2 + -1;
          } while (iVar2 != 0);
        }
      }
      if ((flags == 0) || ((*(uint *)((int)out + 0x10) & 0x800000) == 0)) {
        if ((iVar2 == 0) || ((*(uint *)((int)out + 0x10) & 0x800000) == 0)) goto LAB_00471b75;
        *(undefined4 *)((int)out + 0x10) = 0xffffff;
      }
      else {
        *(undefined4 *)((int)out + 0x10) = 0x7fffff;
      }
      *(undefined4 *)((int)out + 0xc) = 0xffffff;
LAB_00471b75:
      if ((bVar4) && (flags != 0)) {
        value_neg(out,out);
        return 1;
      }
      return 1;
    }
    goto LAB_00471baa;
  }
  *(uint *)((int)out + 0x10) = local_30 & cdb_word_mask;
LAB_00471bc3:
  *(uint *)((int)out + 0xc) = local_40[3] & cdb_word_mask;
  if (((local_20 != 4) && (local_20 != 0xb)) && (local_20 != 10)) {
    return 1;
  }
  if ((((cdb_arch != 0x2c7) && (cdb_arch != 0x2c9)) &&
      ((cdb_arch != 0x2c5 && ((cdb_arch != 0x2cb && (cdb_arch != 0x2ca)))))) && (cdb_arch != 0x2c8))
  {
    return 1;
  }
  if ((cdb_sign_bit & local_40[3]) == 0) {
    return 1;
  }
  *(uint *)((int)out + 0x10) = cdb_word_mask;
  return 1;
}


/* ==== word_split_hi @ 00471c30 ==== */

void __cdecl word_split_hi(void *value)

{
  *(uint *)((int)value + 0x10) =
       *(uint *)((int)value + 0xc) >> ((byte)cdb_word_bits & 0x1f) & cdb_word_mask;
  *(uint *)((int)value + 0xc) = cdb_word_mask & *(uint *)((int)value + 0xc);
  return;
}


/* ==== cast_to_float @ 00471c60 ==== */

int __cdecl cast_to_float(void *from,void *out)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  double *pdVar6;
  uint local_4c;
  uint local_48;
  double local_40;
  undefined4 local_38;
  uint local_34;
  uint local_30;
  undefined4 local_2c;
  int local_20;
  
  bVar1 = false;
  pdVar6 = &local_40;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined4 *)pdVar6 = *(undefined4 *)from;
    from = (undefined4 *)((int)from + 4);
    pdVar6 = (double *)((int)pdVar6 + 4);
  }
  if ((((local_20 == 4) || (local_20 == 0xb)) || (local_20 == 10)) || (local_20 == 0xe)) {
    if ((((local_20 == 4) || (local_20 == 0xb)) || (local_20 == 10)) &&
       ((cdb_sign_bit & local_34) != 0)) {
      bVar1 = true;
    }
    if ((cdb_arch == 0x2c8) || (cdb_arch == 0x2c5)) {
      if (local_34 == 0) {
        *(undefined4 *)((int)out + 0xc) = 0;
        *(undefined4 *)((int)out + 0x10) = 0;
        *(undefined4 *)((int)out + 0x14) = 0;
        return 1;
      }
      if (bVar1) {
        value_neg(&local_40,&local_40);
      }
      *(undefined4 *)((int)out + 0xc) = 0x2016;
      *(uint *)((int)out + 0x10) = local_34;
      if ((local_34 & 0x800000) == 0) {
        while ((local_34 & 0x400000) == 0) {
          local_34 = *(int *)((int)out + 0x10) << 1;
          *(uint *)((int)out + 0x10) = local_34;
          *(int *)((int)out + 0xc) = *(int *)((int)out + 0xc) + -1;
        }
      }
      else {
        *(uint *)((int)out + 0x10) = local_34 >> 1;
        *(undefined4 *)((int)out + 0xc) = 0x2017;
      }
    }
    else {
      if (bVar1) {
        value_neg(&local_40,&local_40);
      }
      *(float *)((int)out + 8) = (float)local_34;
    }
  }
  else {
    if ((local_20 != 5) && (local_20 != 0xf)) {
      if (local_20 != 6) {
        if (local_20 != 7) {
          cdb_internal_error(0x4d413c,0x182f);
          return 0;
        }
        if ((cdb_arch != 0x2c8) && (cdb_arch != 0x2c5)) {
          if ((cdb_arch != 0x2c7) &&
             (((cdb_arch != 0x2c9 && (cdb_arch != 0x2cb)) && (cdb_arch != 0x2ca)))) {
            *(float *)((int)out + 8) = (float)local_40;
            return 1;
          }
          *(undefined4 *)((int)out + 8) = local_38;
          return 1;
        }
        *(uint *)((int)out + 0xc) = local_34;
        *(uint *)((int)out + 0x10) = local_30;
        *(undefined4 *)((int)out + 0x14) = local_2c;
        return 1;
      }
      if ((cdb_arch == 0x2c8) || (cdb_arch == 0x2c5)) {
        *(uint *)((int)out + 0xc) = local_34;
        *(uint *)((int)out + 0x10) = local_30;
        *(undefined4 *)((int)out + 0x14) = local_2c;
        return 1;
      }
      if (((cdb_arch != 0x2c7) && (cdb_arch != 0x2c9)) &&
         ((cdb_arch != 0x2cb && (cdb_arch != 0x2ca)))) {
        *(undefined4 *)((int)out + 8) = local_38;
        return 1;
      }
      *(undefined4 *)((int)out + 8) = local_38;
      return 1;
    }
    uVar5 = 0;
    if (local_20 == 5) {
      uVar2 = local_30;
      if (((((cdb_arch != 0x2c7) && (cdb_arch != 0x2c9)) && (cdb_arch != 0x2c5)) &&
          ((cdb_arch != 0x2cb && (cdb_arch != 0x2ca)))) && (cdb_arch != 0x2c8)) {
        uVar2 = local_34;
      }
      if ((cdb_sign_bit & uVar2) != 0) {
        bVar1 = true;
      }
    }
    if ((cdb_arch == 0x2c8) || (cdb_arch == 0x2c5)) {
      if ((local_34 == 0) && (local_30 == 0)) {
        *(undefined4 *)((int)out + 0xc) = 0;
        *(undefined4 *)((int)out + 0x10) = 0;
        *(undefined4 *)((int)out + 0x14) = 0;
        return 1;
      }
      if (bVar1) {
        value_neg(&local_40,&local_40);
      }
      local_4c = local_34;
      *(undefined4 *)((int)out + 0xc) = 0x2016;
      local_48 = local_30;
      do {
        if (local_48 == 0) {
          if ((local_4c & 0x800000) == 0) goto LAB_00471f61;
          if ((local_4c & 0x400000) == 0) {
            if ((local_4c & 0x800000) != 0) {
              uVar5 = local_4c & 1;
              local_4c = local_4c >> 1;
              *(int *)((int)out + 0xc) = *(int *)((int)out + 0xc) + 1;
            }
LAB_00471f61:
            local_48 = 0;
            uVar3 = local_4c;
            uVar2 = local_4c;
            while (local_4c = uVar3, (uVar2 & 0x400000) == 0) {
              dw_shl1(&local_4c);
              *(int *)((int)out + 0xc) = *(int *)((int)out + 0xc) + -1;
              uVar3 = local_4c | uVar5;
              uVar5 = 0;
              uVar2 = local_4c;
            }
            local_4c = local_4c | uVar5;
            *(uint *)((int)out + 0x10) = local_4c;
            if (!bVar1) {
              return 1;
            }
            value_neg(out,out);
            return 1;
          }
        }
        uVar5 = local_4c & 1;
        dw_shr1(&local_4c);
        *(int *)((int)out + 0xc) = *(int *)((int)out + 0xc) + 1;
      } while( true );
    }
    if (bVar1) {
      value_neg(&local_40,&local_40);
    }
    if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cb)) || (cdb_arch == 0x2ca)
       ) {
      word_join_hi(&local_40);
    }
    *(float *)((int)out + 8) = (float)local_34;
  }
  if (!bVar1) {
    return 1;
  }
  value_neg(out,out);
  return 1;
}


/* ==== word_join_hi @ 004720d0 ==== */

void __cdecl word_join_hi(void *value)

{
  *(uint *)((int)value + 0xc) =
       *(uint *)((int)value + 0xc) | *(int *)((int)value + 0x10) << ((byte)cdb_word_bits & 0x1f);
  return;
}


/* ==== cast_to_double @ 004720f0 ==== */

int __cdecl cast_to_double(void *from,void *out)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined8 *puVar6;
  uint local_4c;
  uint local_48;
  undefined8 local_40;
  float local_38;
  uint local_34;
  uint local_30;
  undefined4 local_2c;
  int local_20;
  
  puVar6 = &local_40;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined4 *)puVar6 = *(undefined4 *)from;
    from = (undefined4 *)((int)from + 4);
    puVar6 = (undefined8 *)((int)puVar6 + 4);
  }
  bVar1 = false;
  if ((((local_20 == 4) || (local_20 == 0xb)) || (local_20 == 10)) || (local_20 == 0xe)) {
    if ((((local_20 == 4) || (local_20 == 0xb)) || (local_20 == 10)) &&
       ((cdb_sign_bit & local_34) != 0)) {
      bVar1 = true;
    }
    if ((cdb_arch == 0x2c8) || (cdb_arch == 0x2c5)) {
      if (local_34 == 0) {
        *(undefined4 *)((int)out + 0xc) = 0;
        *(undefined4 *)((int)out + 0x10) = 0;
        *(undefined4 *)((int)out + 0x14) = 0;
        return 1;
      }
      if (bVar1) {
        value_neg(&local_40,&local_40);
      }
      *(undefined4 *)((int)out + 0xc) = 0x2016;
      *(uint *)((int)out + 0x10) = local_34;
      if ((local_34 & 0x800000) == 0) {
        while ((local_34 & 0x400000) == 0) {
          local_34 = *(int *)((int)out + 0x10) << 1;
          *(uint *)((int)out + 0x10) = local_34;
          *(int *)((int)out + 0xc) = *(int *)((int)out + 0xc) + -1;
        }
      }
      else {
        *(uint *)((int)out + 0x10) = local_34 >> 1;
        *(undefined4 *)((int)out + 0xc) = 0x2017;
      }
    }
    else if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cb)) ||
            (cdb_arch == 0x2ca)) {
      if (bVar1) {
        value_neg(&local_40,&local_40);
      }
      *(float *)((int)out + 8) = (float)local_34;
    }
    else {
      if (bVar1) {
        value_neg(&local_40,&local_40);
      }
      *(double *)out = (double)local_34;
    }
  }
  else {
    if ((local_20 != 5) && (local_20 != 0xf)) {
      if (local_20 != 6) {
        if (local_20 != 7) {
          cdb_internal_error(0x4d413c,0x192c);
          return 0;
        }
        if ((cdb_arch != 0x2c8) && (cdb_arch != 0x2c5)) {
          if ((cdb_arch != 0x2c7) &&
             (((cdb_arch != 0x2c9 && (cdb_arch != 0x2cb)) && (cdb_arch != 0x2ca)))) {
            *(undefined8 *)out = local_40;
            return 1;
          }
          *(float *)((int)out + 8) = local_38;
          return 1;
        }
        *(uint *)((int)out + 0xc) = local_34;
        *(uint *)((int)out + 0x10) = local_30;
        *(undefined4 *)((int)out + 0x14) = local_2c;
        return 1;
      }
      if ((cdb_arch == 0x2c8) || (cdb_arch == 0x2c5)) {
        *(uint *)((int)out + 0xc) = local_34;
        *(uint *)((int)out + 0x10) = local_30;
        *(undefined4 *)((int)out + 0x14) = local_2c;
        return 1;
      }
      if (((cdb_arch != 0x2c7) && (cdb_arch != 0x2c9)) &&
         ((cdb_arch != 0x2cb && (cdb_arch != 0x2ca)))) {
        *(double *)out = (double)local_38;
        return 1;
      }
      *(float *)((int)out + 8) = local_38;
      return 1;
    }
    uVar5 = 0;
    if (local_20 == 5) {
      uVar2 = local_30;
      if (((((cdb_arch != 0x2c7) && (cdb_arch != 0x2c9)) && (cdb_arch != 0x2c5)) &&
          ((cdb_arch != 0x2cb && (cdb_arch != 0x2ca)))) && (cdb_arch != 0x2c8)) {
        uVar2 = local_34;
      }
      if ((cdb_sign_bit & uVar2) != 0) {
        bVar1 = true;
      }
    }
    if ((cdb_arch == 0x2c8) || (cdb_arch == 0x2c5)) {
      if ((local_34 == 0) && (local_30 == 0)) {
        *(undefined4 *)((int)out + 0xc) = 0;
        *(undefined4 *)((int)out + 0x10) = 0;
        *(undefined4 *)((int)out + 0x14) = 0;
        return 1;
      }
      if (bVar1) {
        value_neg(&local_40,&local_40);
      }
      *(undefined4 *)((int)out + 0xc) = 0x2016;
      local_4c = local_34;
      local_48 = local_30;
      do {
        if (local_48 == 0) {
          if ((local_4c & 0x800000) == 0) goto LAB_00472425;
          if ((local_4c & 0x400000) == 0) {
            if ((local_4c & 0x800000) != 0) {
              uVar5 = local_4c & 1;
              local_4c = local_4c >> 1;
              *(int *)((int)out + 0xc) = *(int *)((int)out + 0xc) + 1;
            }
LAB_00472425:
            local_48 = 0;
            uVar3 = local_4c;
            uVar2 = local_4c;
            while (local_4c = uVar3, (uVar2 & 0x400000) == 0) {
              dw_shl1(&local_4c);
              *(int *)((int)out + 0xc) = *(int *)((int)out + 0xc) + -1;
              uVar3 = local_4c | uVar5;
              uVar5 = 0;
              uVar2 = local_4c;
            }
            local_4c = local_4c | uVar5;
            *(uint *)((int)out + 0x10) = local_4c;
            if (!bVar1) {
              return 1;
            }
            value_neg(out,out);
            return 1;
          }
        }
        uVar5 = local_4c & 1;
        dw_shr1(&local_4c);
        *(int *)((int)out + 0xc) = *(int *)((int)out + 0xc) + 1;
      } while( true );
    }
    if (bVar1) {
      value_neg(&local_40,&local_40);
    }
    if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cb)) || (cdb_arch == 0x2ca)
       ) {
      word_join_hi(&local_40);
      *(float *)((int)out + 8) = (float)local_34;
    }
    else {
      *(double *)out = (double)local_34;
    }
  }
  if (!bVar1) {
    return 1;
  }
  value_neg(out,out);
  return 1;
}


/* ==== cast_to_fract_common @ 004725e0 ==== */

int __cdecl cast_to_fract_common(void *from,void *out)

{
  int iVar1;
  undefined4 unaff_EDI;
  float *pfVar2;
  undefined8 local_48;
  float local_40 [3];
  uint local_34;
  uint local_30;
  int local_20;
  
  pfVar2 = local_40;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar2 = *(float *)from;
    from = (float *)((int)from + 4);
    pfVar2 = pfVar2 + 1;
  }
  if ((((((((byte)local_20 & 0x30) == 0x10) || (local_20 == 2)) || (local_20 == 3)) ||
       (((local_20 == 4 || (local_20 == 0xb)) ||
        ((local_20 == 10 || ((local_20 == 5 || (local_20 == 0xc)))))))) || (local_20 == 0xd)) ||
     ((local_20 == 0xe || (local_20 == 0xf)))) {
    *(undefined4 *)((int)out + 0xc) = 0;
    *(uint *)((int)out + 0x10) = -(uint)((local_34 & 1) != 0) & cdb_sign_bit;
    *(uint *)((int)out + 0x14) = local_34 >> 1 & cdb_ext_mask;
    return 0;
  }
  if ((local_20 != 0x10000) &&
     (((local_20 != 0x10001 && (local_20 != 0x10003)) && (local_20 != 0x10002)))) {
    if (local_20 == 0x10004) goto LAB_00472744;
    if (local_20 != 0x10005) {
      if (local_20 == 6) {
        if (cdb_arch != 0x2c9) {
          return 0;
        }
        double_to_fract_words((double)local_40[2],out,unaff_EDI);
        return 1;
      }
      if (local_20 != 7) {
        return 0;
      }
      if (cdb_arch != 0x2c9) {
        return 0;
      }
      local_48 = (double)local_40[2];
      if ((double)CONCAT44(local_40[1],local_40[0]) != 0.0) {
        local_48 = (double)CONCAT44(local_40[1],local_40[0]);
      }
      double_to_fract_words(local_48,out,unaff_EDI);
      return 1;
    }
  }
  if (local_20 != 0x10004) {
    if (local_20 == 0x10003) {
      *(uint *)((int)out + 0xc) = local_34;
      *(uint *)((int)out + 0x10) = local_30;
      *(undefined4 *)((int)out + 0x14) = 0;
      return 1;
    }
    if (local_20 == 0x10002) {
      *(uint *)((int)out + 0xc) = local_34;
    }
    else {
      if (local_20 == 0x10001) {
        *(undefined4 *)((int)out + 0xc) = 0;
        *(uint *)((int)out + 0x10) = local_34;
        *(undefined4 *)((int)out + 0x14) = 0;
        return 1;
      }
      if (local_20 != 0x10000) {
        return 0;
      }
      *(undefined4 *)((int)out + 0xc) = 0;
      local_30 = local_34;
    }
    *(uint *)((int)out + 0x10) = local_30;
    *(uint *)((int)out + 0x14) = -(uint)((local_30 & cdb_sign_bit) != 0) & cdb_ext_mask;
    return 1;
  }
LAB_00472744:
  *(undefined4 *)((int)out + 0xc) = 0;
  *(uint *)((int)out + 0x10) = local_34;
  *(uint *)((int)out + 0x14) = local_30;
  return 1;
}


/* ==== double_to_fract_words @ 00472850 ==== */

void __cdecl double_to_fract_words(double d,void *out)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  longlong lVar6;
  ulonglong local_8;
  
  uVar1 = cdb_word_mask;
  local_8 = (ulonglong)(cdb_ext_mask + 1);
  if (d <= -(double)local_8) {
    *(int *)((int)out + 0x14) = cdb_ext_sign_bit;
    *(undefined4 *)((int)out + 0xc) = 0;
    *(undefined4 *)((int)out + 0x10) = 0;
    return;
  }
  if ((double)local_8 <= d) {
    iVar3 = cdb_ext_sign_bit + -1;
    *(uint *)((int)out + 0xc) = cdb_word_mask;
    *(int *)((int)out + 0x14) = iVar3;
    *(uint *)((int)out + 0x10) = uVar1;
    return;
  }
  lVar6 = _ftol();
  uVar4 = (uint)lVar6;
  lVar6 = _ftol();
  uVar2 = (uint)lVar6 & uVar1;
  if (d < 0.0) {
    bVar5 = uVar2 == 0;
    if (bVar5 == 0) {
      uVar2 = ~uVar2 & uVar1;
    }
    else {
      uVar2 = 0;
    }
    uVar4 = ~uVar4 + (uint)bVar5;
  }
  *(uint *)((int)out + 0xc) = uVar2;
  *(uint *)((int)out + 0x10) = uVar1 & uVar4;
  *(uint *)((int)out + 0x14) = (int)uVar4 >> ((byte)cdb_word_bits & 0x1f) & cdb_ext_mask;
  return;
}


/* ==== cast_to_fract_3 @ 00472970 ==== */

void __cdecl cast_to_fract_3(void *from,void *out)

{
  cast_to_fract_common(from,out);
  *(undefined4 *)((int)out + 0x14) = 0;
  return;
}


/* ==== cast_to_fract_2 @ 00472990 ==== */

void __cdecl cast_to_fract_2(void *from,void *out)

{
  cast_to_fract_common(from,out);
  *(undefined4 *)((int)out + 0x14) = 0;
  return;
}


/* ==== cast_to_fract_4 @ 004729b0 ==== */

void __cdecl cast_to_fract_4(void *from,void *out)

{
  cast_to_fract_common(from,out);
  *(undefined4 *)((int)out + 0xc) = *(undefined4 *)((int)out + 0x10);
  *(undefined4 *)((int)out + 0x10) = *(undefined4 *)((int)out + 0x14);
  *(undefined4 *)((int)out + 0x14) = 0;
  return;
}


/* ==== cast_to_fract_0 @ 004729e0 ==== */

void __cdecl cast_to_fract_0(void *from,void *out)

{
  cast_to_fract_common(from,out);
  *(undefined4 *)((int)out + 0xc) = *(undefined4 *)((int)out + 0x10);
  *(undefined4 *)((int)out + 0x10) = 0;
  *(undefined4 *)((int)out + 0x14) = 0;
  return;
}


/* ==== cast_to_fract_1 @ 00472a10 ==== */

void __cdecl cast_to_fract_1(void *from,void *out)

{
  cast_to_fract_common(from,out);
  *(undefined4 *)((int)out + 0xc) = *(undefined4 *)((int)out + 0x10);
  *(undefined4 *)((int)out + 0x10) = 0;
  *(undefined4 *)((int)out + 0x14) = 0;
  return;
}


/* ==== eval_muldiv @ 00472a40 ==== */

int __cdecl eval_muldiv(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  void *a;
  void *b;
  int iVar1;
  
  a = *(void **)(*(int *)plhs + 0x10);
  iVar1 = *(int *)((int)a + 0x20);
  if ((((((((iVar1 == 2) || (iVar1 == 3)) || (iVar1 == 4)) || ((iVar1 == 0xb || (iVar1 == 10)))) ||
        ((iVar1 == 5 || ((iVar1 == 0xc || (iVar1 == 0xd)))))) || (iVar1 == 0xe)) ||
      ((((iVar1 == 0xf || (iVar1 == 6)) || (iVar1 == 7)) ||
       (((iVar1 == 0x10000 || (iVar1 == 0x10001)) ||
        ((iVar1 == 0x10003 || ((iVar1 == 0x10002 || (iVar1 == 0x10004)))))))))) ||
     (iVar1 == 0x10005)) {
    b = *(void **)(*(int *)prhs + 0x10);
    iVar1 = *(int *)((int)b + 0x20);
    if ((((((iVar1 == 2) || (iVar1 == 3)) || (iVar1 == 4)) ||
         (((iVar1 == 0xb || (iVar1 == 10)) ||
          (((iVar1 == 5 || ((iVar1 == 0xc || (iVar1 == 0xd)))) || (iVar1 == 0xe)))))) ||
        (((((iVar1 == 0xf || (iVar1 == 6)) || (iVar1 == 7)) ||
          ((iVar1 == 0x10000 || (iVar1 == 0x10001)))) ||
         ((iVar1 == 0x10003 || ((iVar1 == 0x10002 || (iVar1 == 0x10004)))))))) || (iVar1 == 0x10005)
       ) {
      if (do_eval == 0) {
        usual_arith_conv(plhs,prhs);
        copy_node_type(result_node,*(void **)plhs);
        return 1;
      }
      if (op != 0x2a) {
        if (op != 0x2f) {
          cdb_internal_error(0x4d413c,0x1c57);
          return 0;
        }
        iVar1 = div_values(a,b,*(void **)((int)result_node + 0x10));
        return iVar1;
      }
      iVar1 = mul_values(a,b,*(void **)((int)result_node + 0x10));
      return iVar1;
    }
  }
  if (op == 0x2a) {
    cdb_error(s_operands_of_binary___are_not_bot_004d42b4);
    return 0;
  }
  if (op != 0x2f) {
    cdb_internal_error(0x4d413c,0x1c6b);
    return 0;
  }
  cdb_error(s_operands_of_binary___are_not_bot_004d42e8);
  return 0;
}


/* ==== mul_values @ 00472c20 ==== */

int __cdecl mul_values(void *a,void *b,void *out)

{
  int iVar1;
  undefined4 *puVar2;
  double *pdVar3;
  double local_80;
  float local_78;
  ulong local_74 [5];
  int local_60;
  double local_40;
  float local_38;
  ulong local_34 [13];
  
  iVar1 = cdb_load_value(a);
  if (iVar1 != 0) {
    iVar1 = cdb_load_value(b);
    if (iVar1 != 0) {
      puVar2 = a;
      pdVar3 = &local_80;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *(undefined4 *)pdVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        pdVar3 = (double *)((int)pdVar3 + 4);
      }
      puVar2 = b;
      pdVar3 = &local_40;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *(undefined4 *)pdVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        pdVar3 = (double *)((int)pdVar3 + 4);
      }
      if ((((local_60 == 2) || (local_60 == 3)) || (local_60 == 4)) ||
         (((((local_60 == 0xb || (local_60 == 10)) ||
            ((local_60 == 5 || ((local_60 == 0xc || (local_60 == 0xd)))))) || (local_60 == 0xe)) ||
          (local_60 == 0xf)))) {
        sign_extend_word(&local_80);
        sign_extend_word(&local_40);
        if ((cdb_arch == 0x2c8) || (cdb_arch == 0x2c5)) {
          iVar1 = dw_mul(local_74,local_34,(int *)((int)out + 0xc));
          return iVar1;
        }
        if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cb)) ||
           (cdb_arch == 0x2ca)) {
          word_join_hi(&local_80);
          word_join_hi(&local_40);
        }
        if (((local_60 == 4) || (local_60 == 0xb)) || (local_60 == 10)) {
          *(ulong *)((int)out + 0xc) = local_34[0] * local_74[0];
        }
        else {
          *(ulong *)((int)out + 0xc) = local_34[0] * local_74[0];
        }
        if (((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) ||
           ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))) {
          word_split_hi(out);
        }
        *(uint *)((int)out + 0xc) = *(uint *)((int)out + 0xc) & cdb_word_mask;
      }
      else {
        if ((local_60 == 6) || (local_60 == 7)) {
          if ((cdb_arch != 0x2c8) && (cdb_arch != 0x2c5)) {
            if ((((local_60 != 6) && (cdb_arch != 0x2c7)) && (cdb_arch != 0x2c9)) &&
               ((cdb_arch != 0x2cb && (cdb_arch != 0x2ca)))) {
              value_copy_trunc(a,&local_80);
              value_copy_trunc(b,&local_40);
              *(double *)out = local_40 * local_80;
              value_copy_trunc(out,out);
              return 1;
            }
            *(float *)((int)out + 8) = local_38 * local_78;
            return 1;
          }
          iVar1 = mul_int_values(&local_80,&local_40,out);
          return iVar1;
        }
        if (((local_60 == 0x10000) || (local_60 == 0x10001)) ||
           ((local_60 == 0x10003 ||
            (((local_60 == 0x10002 || (local_60 == 0x10004)) || (local_60 == 0x10005)))))) {
          fract_mul_helper(&local_80);
          fract_mul_helper(&local_40);
          *(double *)out = local_40 * local_80;
          double_to_fract_value(out);
          return 1;
        }
      }
      return 1;
    }
  }
  return 0;
}


/* ==== sign_extend_word @ 00472f50 ==== */

void __cdecl sign_extend_word(void *value)

{
  int iVar1;
  
  iVar1 = *(int *)((int)value + 0x20);
  if ((((iVar1 == 4) || (iVar1 == 0xb)) || (iVar1 == 10)) &&
     ((*(uint *)((int)value + 0xc) & cdb_sign_bit) != 0)) {
    *(uint *)((int)value + 0xc) = ~cdb_word_mask | *(uint *)((int)value + 0xc);
  }
  return;
}


/* ==== double_to_fract_value @ 00472f90 ==== */

void __cdecl double_to_fract_value(void *value)

{
  int iVar1;
  
  double_to_fract_words(*(double *)value,value);
  iVar1 = *(int *)((int)value + 0x20);
  if (iVar1 == 0x10004) {
    *(undefined4 *)((int)value + 0xc) = *(undefined4 *)((int)value + 0x10);
    *(undefined4 *)((int)value + 0x10) = *(undefined4 *)((int)value + 0x14);
    *(undefined4 *)((int)value + 0x14) = 0;
    return;
  }
  if ((iVar1 == 0x10003) || (iVar1 == 0x10002)) {
    *(undefined4 *)((int)value + 0x14) = 0;
  }
  else if ((iVar1 == 0x10001) || (iVar1 == 0x10000)) {
    *(undefined4 *)((int)value + 0xc) = *(undefined4 *)((int)value + 0x10);
    *(undefined4 *)((int)value + 0x10) = 0;
    *(undefined4 *)((int)value + 0x14) = 0;
    return;
  }
  return;
}


/* ==== fract_mul_helper @ 00473000 ==== */

void __cdecl fract_mul_helper(void *value)

{
  int iVar1;
  double dVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar4 = 0;
  uVar3 = 0;
  iVar1 = *(int *)((int)value + 0x20);
  uVar5 = 0;
  if (iVar1 == 0x10004) {
    uVar4 = *(uint *)((int)value + 0xc);
    uVar3 = *(uint *)((int)value + 0x10);
  }
  else if (iVar1 == 0x10003) {
    uVar5 = *(uint *)((int)value + 0xc);
    uVar4 = *(uint *)((int)value + 0x10);
  }
  else {
    if (iVar1 == 0x10002) {
      uVar5 = *(uint *)((int)value + 0xc);
      uVar4 = *(uint *)((int)value + 0x10);
    }
    else {
      if (iVar1 == 0x10001) {
        uVar4 = *(uint *)((int)value + 0xc);
        goto LAB_00473085;
      }
      if (iVar1 != 0x10000) {
        if (iVar1 == 0x10005) {
          uVar5 = *(uint *)((int)value + 0xc);
          uVar4 = *(uint *)((int)value + 0x10);
          uVar3 = *(uint *)((int)value + 0x14);
        }
        goto LAB_00473085;
      }
      uVar4 = *(uint *)((int)value + 0xc);
    }
    uVar3 = -(uint)((cdb_sign_bit & uVar4) != 0) & cdb_ext_mask;
  }
LAB_00473085:
  uVar3 = uVar3 & cdb_ext_mask;
  uVar6 = cdb_word_mask << 8 | cdb_word_mask;
  uVar5 = uVar5 & cdb_word_mask;
  dVar2 = (double)(-cdb_ext_mask - 1);
  if (((uVar3 != cdb_ext_sign_bit) || ((uVar4 & cdb_word_mask) != 0)) || (uVar5 != 0)) {
    uVar4 = uVar4 & cdb_word_mask | uVar3 << ((byte)cdb_word_bits & 0x1f);
    if ((cdb_ext_sign_bit & uVar3) == 0) {
      uVar5 = uVar5 & cdb_word_mask;
    }
    else {
      if (cdb_ext_mask == 0xf) {
        uVar4 = uVar4 | 0xf00000;
      }
      if (uVar5 == 0) {
        uVar4 = (uVar6 & ~uVar4) + 1;
        uVar5 = 0;
      }
      else {
        uVar4 = uVar6 & ~uVar4;
        uVar5 = (cdb_word_mask & ~uVar5) + 1;
      }
    }
    dVar2 = (double)uVar4 / (double)(int)cdb_sign_bit +
            (double)uVar5 / ((double)(cdb_word_mask + 1) * (double)(int)cdb_sign_bit);
    if ((cdb_ext_sign_bit & uVar3) != 0) {
      dVar2 = -dVar2;
    }
  }
  *(double *)value = dVar2;
  return;
}


/* ==== div_values @ 00473180 ==== */

int __cdecl div_values(void *a,void *b,void *out)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  double *pdVar5;
  bool bVar6;
  double local_8c;
  float local_84;
  uint local_80;
  uint local_7c;
  int local_6c;
  double local_4c;
  float local_44;
  uint local_40;
  uint local_3c;
  int local_2c;
  ulong local_c [3];
  
  iVar4 = 0;
  iVar1 = cdb_load_value(a);
  if ((iVar1 == 0) || (iVar1 = cdb_load_value(b), iVar1 == 0)) {
    return 0;
  }
  pdVar5 = &local_4c;
  for (iVar1 = 0x10; iVar2 = local_2c, iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined4 *)pdVar5 = *(undefined4 *)a;
    a = (undefined4 *)((int)a + 4);
    pdVar5 = (double *)((int)pdVar5 + 4);
  }
  bVar6 = local_2c == 4;
  pdVar5 = &local_8c;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined4 *)pdVar5 = *(undefined4 *)b;
    b = (undefined4 *)((int)b + 4);
    pdVar5 = (double *)((int)pdVar5 + 4);
  }
  if ((((bVar6) || (iVar2 == 0xb)) || (iVar2 == 10)) || (iVar2 == 0xe)) {
    if (local_80 == 0) {
      cdb_c_error(s_attempt_to_divide_by_0_004d4148);
      return 0;
    }
    sign_extend_word(&local_4c);
    sign_extend_word(&local_8c);
    if (((local_2c == 4) || (local_2c == 0xb)) || (local_2c == 10)) {
      local_40 = (int)local_40 / (int)local_80;
    }
    else {
      local_40 = local_40 / local_80;
    }
    puVar3 = (uint *)((int)out + 0xc);
    *puVar3 = local_40;
    *puVar3 = *puVar3 & cdb_word_mask;
  }
  else if ((iVar2 == 5) || (iVar2 == 0xf)) {
    if ((cdb_arch != 0x2c8) && (cdb_arch != 0x2c5)) {
      if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cb)) ||
         (cdb_arch == 0x2ca)) {
        word_join_hi(&local_4c);
        word_join_hi(&local_8c);
        iVar2 = local_2c;
      }
      if (local_80 != 0) {
        if (iVar2 == 5) {
          local_40 = (int)local_40 / (int)local_80;
        }
        else {
          local_40 = local_40 / local_80;
        }
        *(uint *)((int)out + 0xc) = local_40;
        if (((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) ||
           ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))) {
          word_split_hi(out);
        }
        *(uint *)((int)out + 0xc) = *(uint *)((int)out + 0xc) & cdb_word_mask;
        return 1;
      }
      cdb_c_error(s_attempt_to_divide_by_0_004d4148);
      return 0;
    }
    if (((cdb_sign_bit & local_3c) == 0) || (iVar2 != 5)) {
      iVar1 = 0;
    }
    else {
      iVar1 = 1;
      value_neg(&local_4c,&local_4c);
    }
    if (((cdb_sign_bit & local_7c) != 0) && (local_6c == 5)) {
      iVar4 = 1;
      value_neg(&local_8c,&local_8c);
    }
    iVar2 = dw_udivmod(&local_40,&local_80,(ulong *)((int)out + 0xc),local_c);
    if (iVar2 == 0) {
      return 0;
    }
    if (iVar4 != iVar1) {
      value_neg(out,out);
      return 1;
    }
  }
  else {
    if ((iVar2 == 6) || (iVar2 == 7)) {
      if ((cdb_arch != 0x2c8) && (cdb_arch != 0x2c5)) {
        if ((((iVar2 != 6) && (cdb_arch != 0x2c7)) && (cdb_arch != 0x2c9)) &&
           ((cdb_arch != 0x2cb && (cdb_arch != 0x2ca)))) {
          value_copy_trunc(&local_4c,&local_4c);
          value_copy_trunc(&local_8c,&local_8c);
          if (local_8c != 0.0) {
            *(double *)out = local_4c / local_8c;
            value_copy_trunc(out,out);
            return 1;
          }
          cdb_c_error(s_attempt_to_divide_by_0_0_004d431c);
          return 0;
        }
        if (local_84 != 0.0) {
          *(float *)((int)out + 8) = local_44 / local_84;
          return 1;
        }
        cdb_c_error(s_attempt_to_divide_by_0_0_004d431c);
        return 0;
      }
      iVar1 = div_double_values(&local_4c,&local_8c,out);
      return iVar1;
    }
    if (((iVar2 == 0x10000) || (iVar2 == 0x10001)) ||
       ((iVar2 == 0x10003 || (((iVar2 == 0x10002 || (iVar2 == 0x10004)) || (iVar2 == 0x10005)))))) {
      fract_mul_helper(&local_4c);
      fract_mul_helper(&local_8c);
      *(double *)out = local_4c / local_8c;
      double_to_fract_value(out);
      return 1;
    }
  }
  return 1;
}


/* ==== dw_mul @ 00473600 ==== */

int __cdecl dw_mul(ulong *a,ulong *b,int *out)

{
  int iVar1;
  uint local_18;
  ulong local_14;
  ulong local_10;
  ulong local_c;
  ulong local_8;
  ulong local_4;
  
  iVar1 = dw_cmp(a,b);
  if (iVar1 < 0) {
    local_c = *b;
    local_8 = b[1];
    local_4 = b[2];
    local_18 = *a;
    local_14 = a[1];
    local_10 = a[2];
  }
  else {
    local_c = *a;
    local_8 = a[1];
    local_4 = a[2];
    local_18 = *b;
    local_14 = b[1];
    local_10 = b[2];
  }
  *out = 0;
  out[1] = 0;
  out[2] = 0;
  while ((local_14 != 0 || (local_18 != 0))) {
    if ((local_18 & 1) != 0) {
      dw_add(&local_c,(ulong *)out,(ulong *)out);
    }
    dw_shl1(&local_c);
    dw_shr1(&local_18);
  }
  return 1;
}


/* ==== mul_int_values @ 004736e0 ==== */

int __cdecl mul_int_values(void *a,void *b,ulong *out)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  ulong local_a8;
  uint local_a4;
  int local_9c;
  ulong local_98;
  undefined4 local_94;
  ulong local_8c;
  undefined4 local_88;
  int local_80 [4];
  uint local_70;
  int local_40 [4];
  uint local_30;
  
  piVar3 = local_80;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar3 = *(int *)a;
    a = (int *)((int)a + 4);
    piVar3 = piVar3 + 1;
  }
  piVar3 = local_40;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar3 = *(int *)b;
    b = (int *)((int)b + 4);
    piVar3 = piVar3 + 1;
  }
  uVar2 = local_70 & 0x800000;
  uVar4 = local_30 & 0x800000;
  local_94 = 0;
  local_88 = 0;
  if (uVar2 != 0) {
    value_neg(local_80,local_80);
  }
  if (uVar4 != 0) {
    value_neg(local_40,local_40);
  }
  local_98 = (local_30 & 0x7fffff) << 1;
  local_8c = (local_70 & 0x7fffff) << 1;
  local_9c = local_40[3];
  dw_mul(&local_8c,&local_98,(int *)&local_a8);
  if ((local_a4 == 0) && (local_a8 == 0)) {
    out[3] = 0;
    out[4] = 0;
    out[5] = 0;
    return 1;
  }
  out[3] = local_9c + -0x1fff + local_80[3];
  while ((local_a4 & 0x800000) == 0) {
    dw_shl1(&local_a8);
    out[3] = out[3] - 1;
  }
  if (((local_a4 & 1) != 0) && (local_a4 = local_a4 + 1, (local_a4 & 0x1000000) != 0)) {
    local_a4 = local_a4 >> 1;
    out[3] = out[3] + 1;
  }
  out[4] = local_a4 >> 1;
  if (uVar4 != uVar2) {
    value_neg(out,out);
  }
  return 1;
}


/* ==== div_double_values @ 00473870 ==== */

int __cdecl div_double_values(void *a,void *b,void *out)

{
  int iVar1;
  double *pdVar2;
  double local_80 [8];
  double local_40 [8];
  
  pdVar2 = local_40;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined4 *)pdVar2 = *(undefined4 *)a;
    a = (undefined4 *)((int)a + 4);
    pdVar2 = (double *)((int)pdVar2 + 4);
  }
  pdVar2 = local_80;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined4 *)pdVar2 = *(undefined4 *)b;
    b = (undefined4 *)((int)b + 4);
    pdVar2 = (double *)((int)pdVar2 + 4);
  }
  value_dsp_to_double(local_40);
  value_dsp_to_double(local_80);
  if (local_80[0] == 0.0) {
    cdb_c_error(s_attempt_to_divide_by_0_0_004d431c);
    return 0;
  }
  *(double *)out = local_40[0] / local_80[0];
  value_double_to_dsp(out);
  return 1;
}


/* ==== eval_add @ 00473910 ==== */

int __cdecl eval_add(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  void *a;
  uint uVar1;
  void *ptr;
  int iVar2;
  
  a = *(void **)((int)*(void **)plhs + 0x10);
  uVar1 = *(uint *)((int)a + 0x20);
  if (((((((uVar1 == 2) || (uVar1 == 3)) || (uVar1 == 4)) || ((uVar1 == 0xb || (uVar1 == 10)))) ||
       (uVar1 == 5)) ||
      (((uVar1 == 0xc || (uVar1 == 0xd)) ||
       ((uVar1 == 0xe || (((uVar1 == 0xf || (uVar1 == 6)) || (uVar1 == 7)))))))) ||
     (((uVar1 == 0x10000 || (uVar1 == 0x10001)) ||
      ((uVar1 == 0x10003 || (((uVar1 == 0x10002 || (uVar1 == 0x10004)) || (uVar1 == 0x10005))))))))
  {
    iVar2 = *(int *)((int)*(void **)(*(int *)prhs + 0x10) + 0x20);
    if (((((((iVar2 == 2) || (iVar2 == 3)) || (iVar2 == 4)) || ((iVar2 == 0xb || (iVar2 == 10)))) ||
         (((iVar2 == 5 || ((iVar2 == 0xc || (iVar2 == 0xd)))) || (iVar2 == 0xe)))) ||
        ((((iVar2 == 0xf || (iVar2 == 6)) || (iVar2 == 7)) ||
         ((iVar2 == 0x10000 || (iVar2 == 0x10001)))))) ||
       (((iVar2 == 0x10003 || ((iVar2 == 0x10002 || (iVar2 == 0x10004)))) || (iVar2 == 0x10005)))) {
      if (do_eval == 0) {
        usual_arith_conv(plhs,prhs);
        copy_node_type(result_node,*(void **)plhs);
        return 1;
      }
      iVar2 = add_values(a,*(void **)(*(int *)prhs + 0x10),*(void **)((int)result_node + 0x10));
      return iVar2;
    }
  }
  if ((((((uVar1 != 2) && (uVar1 != 3)) && (uVar1 != 4)) && ((uVar1 != 0xb && (uVar1 != 10)))) &&
      ((uVar1 != 5 && ((uVar1 != 0xc && (uVar1 != 0xd)))))) && ((uVar1 != 0xe && (uVar1 != 0xf)))) {
    iVar2 = *(int *)((int)*(void **)(*(int *)prhs + 0x10) + 0x20);
    if ((((iVar2 != 2) && (iVar2 != 3)) && (iVar2 != 4)) &&
       (((((iVar2 != 0xb && (iVar2 != 10)) && ((iVar2 != 5 && ((iVar2 != 0xc && (iVar2 != 0xd))))))
         && (iVar2 != 0xe)) && (iVar2 != 0xf)))) {
      cdb_error(s_operands_of_binary___invalid_004d43e8);
      return 0;
    }
    if (((byte)uVar1 & 0x30) != 0x10) {
      cdb_error(s_left_operand_of_binary___is_not_a_004d4374);
      return 0;
    }
    if ((uVar1 >> 2 & 0x3ffebff0 | uVar1 & 0x1000f) == 1) {
      cdb_error(s_pointer_arithmetic_with_void_poi_004d43b0);
      return 0;
    }
    if (do_eval == 0) {
      copy_node_type(result_node,*(void **)plhs);
      return 1;
    }
    iVar2 = ptr_add_values(a,*(void **)(*(int *)prhs + 0x10),*(void **)((int)result_node + 0x10));
    return iVar2;
  }
  ptr = *(void **)((int)*(void **)prhs + 0x10);
  uVar1 = *(uint *)((int)ptr + 0x20);
  if (((byte)uVar1 & 0x30) != 0x10) {
    cdb_error(s_right_operand_of_binary___is_not_004d4338);
    return 0;
  }
  if ((uVar1 >> 2 & 0x3ffebff0 | uVar1 & 0x1000f) == 1) {
    cdb_error(s_pointer_arithmetic_with_void_poi_004d43b0);
    return 0;
  }
  if (do_eval == 0) {
    copy_node_type(result_node,*(void **)prhs);
    return 1;
  }
  iVar2 = ptr_add_values(ptr,a,*(void **)((int)result_node + 0x10));
  return iVar2;
}


/* ==== add_values @ 00473c40 ==== */

int __cdecl add_values(void *a,void *b,void *out)

{
  int iVar1;
  double *pdVar2;
  double local_80;
  float local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_60;
  double local_40;
  float local_38;
  int local_34;
  int local_30;
  int local_2c;
  
  iVar1 = cdb_load_value(a);
  if (iVar1 != 0) {
    iVar1 = cdb_load_value(b);
    if (iVar1 != 0) {
      pdVar2 = &local_80;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *(undefined4 *)pdVar2 = *(undefined4 *)a;
        a = (undefined4 *)((int)a + 4);
        pdVar2 = (double *)((int)pdVar2 + 4);
      }
      pdVar2 = &local_40;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *(undefined4 *)pdVar2 = *(undefined4 *)b;
        b = (undefined4 *)((int)b + 4);
        pdVar2 = (double *)((int)pdVar2 + 4);
      }
      if (((((local_60 == 2) || (local_60 == 3)) || (local_60 == 4)) ||
          (((local_60 == 0xb || (local_60 == 10)) ||
           ((local_60 == 5 || ((local_60 == 0xc || (local_60 == 0xd)))))))) ||
         ((local_60 == 0xe || (local_60 == 0xf)))) {
        *(ulong *)((int)out + 0xc) = local_34 + local_74;
        *(int *)((int)out + 0x10) = local_30 + local_70;
        tw_normalize((ulong *)((int)out + 0xc));
      }
      else {
        if (((((local_60 == 0x10000) || (local_60 == 0x10001)) || (local_60 == 0x10003)) ||
            ((local_60 == 0x10002 || (local_60 == 0x10004)))) || (local_60 == 0x10005)) {
          *(ulong *)((int)out + 0xc) = local_34 + local_74;
          *(int *)((int)out + 0x10) = local_30 + local_70;
          *(int *)((int)out + 0x14) = local_2c + local_6c;
          tw_normalize((ulong *)((int)out + 0xc));
          return 1;
        }
        if (local_60 == 6) {
          if ((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) {
            *(float *)((int)out + 8) = local_38 + local_78;
            return 1;
          }
          iVar1 = add_words(&local_80,&local_40,(int)out);
          return iVar1;
        }
        if (local_60 == 7) {
          if ((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) {
            iVar1 = add_words(&local_80,&local_40,(int)out);
            return iVar1;
          }
          if ((((cdb_arch != 0x2c7) && (cdb_arch != 0x2c9)) && (cdb_arch != 0x2cb)) &&
             (cdb_arch != 0x2ca)) {
            value_copy_trunc(&local_80,&local_80);
            value_copy_trunc(&local_40,&local_40);
            *(double *)out = local_40 + local_80;
            value_copy_trunc(out,out);
            return 1;
          }
          *(float *)((int)out + 8) = local_38 + local_78;
          return 1;
        }
      }
      return 1;
    }
  }
  return 0;
}


/* ==== add_words @ 00473ef0 ==== */

int __cdecl add_words(void *a,void *b,int n)

{
  int iVar1;
  uint uVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  bool bVar8;
  bool bVar9;
  uint local_a4;
  uint local_a0;
  uint local_98;
  int local_94;
  uint local_8c;
  uint local_88;
  int local_80 [4];
  uint local_70;
  int local_40 [4];
  uint local_30;
  
  uVar5 = 0;
  piVar6 = local_40;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar6 = *(int *)a;
    a = (int *)((int)a + 4);
    piVar6 = piVar6 + 1;
  }
  piVar6 = local_80;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar6 = *(int *)b;
    b = (int *)((int)b + 4);
    piVar6 = piVar6 + 1;
  }
  local_a4 = local_30;
  bVar8 = (local_30 & 0x800000) != 0;
  local_a0 = 0;
  local_8c = local_70;
  local_88 = 0;
  iVar4 = local_40[3];
  if (bVar8) {
    local_a4 = local_30 >> 1 | 0xff800000;
    local_a0 = 0xffffffff;
    iVar4 = local_40[3] + 1;
  }
  bVar9 = (local_70 & 0x800000) != 0;
  iVar7 = local_80[3];
  if (bVar9) {
    local_88 = 0xffffffff;
    local_8c = local_70 >> 1 | 0xff800000;
    iVar7 = local_80[3] + 1;
  }
  iVar1 = iVar4 - iVar7;
  if (0x17 < iVar1) {
    *(int *)(n + 0xc) = local_40[3];
    *(uint *)(n + 0x10) = local_30;
    return 1;
  }
  if (iVar1 < -0x17) {
    *(int *)(n + 0xc) = local_80[3];
    *(uint *)(n + 0x10) = local_70;
    return 1;
  }
  piVar6 = (int *)(n + 0xc);
  if (iVar1 < 1) {
    if (iVar1 < 0) {
      *piVar6 = iVar7;
      for (iVar1 = -iVar1; iVar1 != 0; iVar1 = iVar1 + -1) {
        dw_shr1(&local_a4);
        if (bVar8) {
          local_a0 = local_a0 | 0x80000000;
        }
      }
    }
    else {
      *piVar6 = iVar4;
    }
  }
  else {
    *piVar6 = iVar4;
    do {
      dw_shr1(&local_8c);
      if (bVar9) {
        local_88 = local_88 | 0x80000000;
      }
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  dw_add(&local_a4,&local_8c,&local_98);
  if (local_98 != 0) {
    if ((local_94 == 0) && ((local_98 & 0x800000) != 0)) {
      uVar5 = local_98 & 1;
      dw_shr1(&local_98);
      *piVar6 = *piVar6 + 1;
    }
    bVar3 = (byte)(local_98 >> 0x16) ^ (byte)(local_98 >> 0x17);
    while ((bVar3 & 1) == 0) {
      dw_shl1(&local_98);
      *piVar6 = *piVar6 + -1;
      uVar2 = local_98 | uVar5;
      uVar5 = 0;
      bVar3 = (byte)(local_98 >> 0x16) ^ (byte)(local_98 >> 0x17);
      local_98 = uVar2;
    }
    *(uint *)(n + 0x10) = local_98;
    return 1;
  }
  *piVar6 = 0;
  *(undefined4 *)(n + 0x10) = 0;
  *(undefined4 *)(n + 0x14) = 0;
  return 1;
}


/* ==== eval_sub @ 00474130 ==== */

int __cdecl eval_sub(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  void *a;
  uint type1;
  void *q;
  int iVar1;
  
  a = *(void **)((int)*(void **)plhs + 0x10);
  type1 = *(uint *)((int)a + 0x20);
  if (((((((type1 == 2) || (type1 == 3)) || (type1 == 4)) || ((type1 == 0xb || (type1 == 10)))) ||
       ((type1 == 5 || ((type1 == 0xc || (type1 == 0xd)))))) ||
      (((type1 == 0xe || (((type1 == 0xf || (type1 == 6)) || (type1 == 7)))) ||
       (((type1 == 0x10000 || (type1 == 0x10001)) ||
        ((type1 == 0x10003 || ((type1 == 0x10002 || (type1 == 0x10004)))))))))) ||
     (type1 == 0x10005)) {
    iVar1 = *(int *)((int)*(void **)(*(int *)prhs + 0x10) + 0x20);
    if ((((((iVar1 == 2) || (iVar1 == 3)) || (iVar1 == 4)) || ((iVar1 == 0xb || (iVar1 == 10)))) ||
        (((iVar1 == 5 || ((iVar1 == 0xc || (iVar1 == 0xd)))) || (iVar1 == 0xe)))) ||
       ((((((iVar1 == 0xf || (iVar1 == 6)) || (iVar1 == 7)) ||
          ((iVar1 == 0x10000 || (iVar1 == 0x10001)))) || (iVar1 == 0x10003)) ||
        (((iVar1 == 0x10002 || (iVar1 == 0x10004)) || (iVar1 == 0x10005)))))) {
      if (do_eval != 0) {
        iVar1 = sub_values(a,*(void **)(*(int *)prhs + 0x10),*(void **)((int)result_node + 0x10));
        return iVar1;
      }
      usual_arith_conv(plhs,prhs);
      copy_node_type(result_node,*(void **)plhs);
      return 1;
    }
  }
  if ((type1 & 0x30) != 0x10) {
    cdb_error(s_operands_of_binary___invalid_004d4408);
    return 0;
  }
  q = *(void **)(*(int *)prhs + 0x10);
  if (((byte)*(ulong *)((int)q + 0x20) & 0x30) != 0x10) {
    iVar1 = *(int *)((int)*(void **)(*(int *)prhs + 0x10) + 0x20);
    if (((((iVar1 != 2) && (iVar1 != 3)) && (iVar1 != 4)) &&
        (((iVar1 != 0xb && (iVar1 != 10)) && ((iVar1 != 5 && ((iVar1 != 0xc && (iVar1 != 0xd))))))))
       && ((iVar1 != 0xe && (iVar1 != 0xf)))) {
      cdb_error(s_right_operand_of_binary___is_not_004d4428);
      return 0;
    }
    if (do_eval != 0) {
      iVar1 = ptr_sub_int_values(a,*(void **)(*(int *)prhs + 0x10),
                                 *(void **)((int)result_node + 0x10));
      return iVar1;
    }
    copy_node_type(result_node,*(void **)plhs);
    return 1;
  }
  if (do_eval != 0) {
    iVar1 = ptr_diff_values(a,q,*(void **)((int)result_node + 0x10));
    return iVar1;
  }
  iVar1 = cdb_types_match(type1,*(int *)((int)a + 0x28),*(ulong *)((int)q + 0x20),
                          *(int *)((int)q + 0x28));
  if (iVar1 == 0) {
    dsp_free_ext(s_subtracting_pointers_to_incompat_004d4464);
  }
  copy_node_type((void *)0x0,*(void **)prhs);
  *(undefined4 *)(iRam00000010 + 0x20) = 4;
  return 1;
}


/* ==== sub_values @ 004743e0 ==== */

int __cdecl sub_values(void *a,void *b,void *out)

{
  int iVar1;
  
  iVar1 = value_neg(b,out);
  if (iVar1 != 0) {
    iVar1 = add_values(a,out,out);
    return iVar1;
  }
  return 0;
}


/* ==== ptr_sub_int_values @ 00474410 ==== */

int __cdecl ptr_sub_int_values(void *ptr,void *idx,void *out)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 va0;
  undefined4 local_80 [8];
  uint local_60;
  undefined1 local_40 [12];
  int local_34;
  undefined4 local_20;
  
  iVar1 = cdb_load_value(ptr);
  if (iVar1 != 0) {
    iVar1 = cdb_load_value(idx);
    if (iVar1 != 0) {
      if (((byte)*(undefined4 *)((int)ptr + 0x20) & 0x30) == 0x10) {
        iVar1 = *(int *)((int)idx + 0x20);
        if ((((((iVar1 == 2) || (iVar1 == 3)) || (iVar1 == 4)) || ((iVar1 == 0xb || (iVar1 == 10))))
            || ((iVar1 == 5 || ((iVar1 == 0xc || (iVar1 == 0xd)))))) ||
           ((iVar1 == 0xe || (iVar1 == 0xf)))) {
          puVar2 = ptr;
          puVar3 = local_80;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar3 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar3 = puVar3 + 1;
          }
          local_20 = 4;
          local_60 = local_60 >> 2 & 0x3ffebff0 | local_60 & 0x1000f;
          type_size(local_80,local_40);
          *(uint *)((int)out + 0xc) =
               *(int *)((int)ptr + 0xc) - *(int *)((int)idx + 0xc) * local_34 & cdb_addr_mask;
          *(undefined4 *)((int)out + 0x10) = *(undefined4 *)((int)ptr + 0x10);
          return 1;
        }
        va0 = 0xcf6;
      }
      else {
        va0 = 0xcfc;
      }
      cdb_internal_error(0x4d413c,va0);
    }
  }
  return 0;
}


/* ==== ptr_diff_values @ 00474530 ==== */

int __cdecl ptr_diff_values(void *p,void *q,void *out)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 va0;
  undefined4 local_80 [8];
  uint local_60;
  undefined1 local_40 [12];
  uint local_34;
  undefined4 local_20;
  
  iVar1 = cdb_load_value(p);
  if ((iVar1 != 0) && (iVar1 = cdb_load_value(q), iVar1 != 0)) {
    if ((((byte)*(undefined4 *)((int)p + 0x20) & 0x30) == 0x10) &&
       (((byte)*(undefined4 *)((int)q + 0x20) & 0x30) == 0x10)) {
      local_20 = 4;
      *(undefined4 *)((int)out + 0x10) = 0;
      *(int *)((int)out + 0xc) = *(int *)((int)p + 0xc) - *(int *)((int)q + 0xc);
      puVar2 = local_80;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar2 = *(undefined4 *)p;
        p = (undefined4 *)((int)p + 4);
        puVar2 = puVar2 + 1;
      }
      local_60 = local_60 >> 2 & 0x3ffebff0 | local_60 & 0x1000f;
      iVar1 = type_size(local_80,local_40);
      if (iVar1 == 0) {
        return 0;
      }
      if (local_34 != 0) {
        *(uint *)((int)out + 0xc) = *(uint *)((int)out + 0xc) / local_34;
        return 1;
      }
      va0 = 0xd27;
    }
    else {
      va0 = 0xd12;
    }
    cdb_internal_error(0x4d413c,va0);
  }
  return 0;
}


/* ==== eval_bitop @ 00474630 ==== */

int __cdecl eval_bitop(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  void *a;
  void *b;
  int iVar1;
  
  a = *(void **)(*(int *)plhs + 0x10);
  iVar1 = *(int *)((int)a + 0x20);
  if (((((((iVar1 == 2) || (iVar1 == 3)) || (iVar1 == 4)) || ((iVar1 == 0xb || (iVar1 == 10)))) ||
       ((iVar1 == 5 || ((iVar1 == 0xc || (iVar1 == 0xd)))))) || (iVar1 == 0xe)) || (iVar1 == 0xf)) {
    b = *(void **)(*(int *)prhs + 0x10);
    iVar1 = *(int *)((int)b + 0x20);
    if (((((iVar1 == 2) || (iVar1 == 3)) || (iVar1 == 4)) ||
        (((iVar1 == 0xb || (iVar1 == 10)) || ((iVar1 == 5 || ((iVar1 == 0xc || (iVar1 == 0xd))))))))
       || ((iVar1 == 0xe || (iVar1 == 0xf)))) {
      if (do_eval == 0) {
        usual_arith_conv(plhs,prhs);
        copy_node_type(result_node,*(void **)plhs);
        return 1;
      }
      if (op < 0x5f) {
        if (op == 0x5e) {
          iVar1 = xor_values(a,b,*(void **)((int)result_node + 0x10));
          return iVar1;
        }
        if (op == 0x25) {
          iVar1 = mod_values(a,b,*(void **)((int)result_node + 0x10));
          return iVar1;
        }
        if (op == 0x26) {
          iVar1 = and_values(a,b,*(void **)((int)result_node + 0x10));
          return iVar1;
        }
      }
      else {
        if (op == 0x7c) {
          iVar1 = or_values(a,b,*(void **)((int)result_node + 0x10));
          return iVar1;
        }
        if (op == 0x134) {
          iVar1 = shl_values(a,b,*(void **)((int)result_node + 0x10));
          return iVar1;
        }
        if (op == 0x135) {
          iVar1 = shr_values(a,b,*(void **)((int)result_node + 0x10));
          return iVar1;
        }
      }
      cdb_internal_error(0x4d413c,0x1d53);
      return 0;
    }
  }
  if (op < 0x5f) {
    if (op == 0x5e) {
      cdb_error(s_operands_of_binary___are_not_bot_004d452c);
      return 0;
    }
    if (op == 0x25) {
      cdb_error(s_operands_of_binary___are_not_bot_004d4560);
      return 0;
    }
    if (op == 0x26) {
      cdb_error(s_operands_of_binary___are_not_bot_004d4594);
      return 0;
    }
  }
  else {
    if (op == 0x7c) {
      cdb_error(s_operands_of_binary___are_not_bot_004d4490);
      return 0;
    }
    if (op == 0x134) {
      cdb_error(s_operands_of_binary_<<_are_not_bo_004d44c4);
      return 0;
    }
    if (op == 0x135) {
      cdb_error(s_operands_of_binary_>>_are_not_bo_004d44f8);
      return 0;
    }
  }
  cdb_internal_error(0x4d413c,0x1d74);
  return 0;
}


/* ==== shl_values @ 00474870 ==== */

int __cdecl shl_values(void *a,void *b,void *out)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  uint local_84;
  uint local_80 [4];
  undefined4 local_70;
  undefined4 local_6c;
  int local_60;
  uint local_40 [4];
  int local_30;
  
  bVar1 = false;
  bVar2 = false;
  iVar3 = cdb_load_value(a);
  if ((iVar3 == 0) || (iVar3 = cdb_load_value(b), iVar3 == 0)) {
    return 0;
  }
  puVar7 = local_80;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar7 = *(uint *)a;
    a = (uint *)((int)a + 4);
    puVar7 = puVar7 + 1;
  }
  puVar7 = local_40;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar7 = *(uint *)b;
    b = (uint *)((int)b + 4);
    puVar7 = puVar7 + 1;
  }
  puVar7 = (uint *)((int)out + 0xc);
  *puVar7 = 0;
  *(undefined4 *)((int)out + 0x10) = 0;
  *(undefined4 *)((int)out + 0x14) = 0;
  uVar4 = cdb_word_bits;
  if ((((local_60 != 4) && (local_60 != 0xb)) && (local_60 != 10)) && (local_60 != 0xe)) {
    if ((local_60 == 5) || (local_60 == 0xf)) {
      if (((cdb_arch == 0x2c5) || ((cdb_arch == 0x2c8 || (cdb_arch == 0x2c7)))) ||
         ((cdb_arch == 0x2c9 || ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))))) {
        bVar1 = true;
        uVar4 = cdb_word_bits * 2;
      }
    }
    else if ((local_60 != 0x10000) && (local_60 != 0x10001)) {
      if ((local_60 == 0x10002) || (local_60 == 0x10003)) {
        uVar4 = cdb_word_bits * 2;
      }
      else if (local_60 == 0x10005) {
        uVar4 = cdb_ext_bits + cdb_word_bits * 2;
      }
      else {
        if (local_60 != 0x10004) {
          cdb_internal_error(0x4d413c,0xe06);
          return 0;
        }
        uVar4 = cdb_word_bits + cdb_ext_bits;
      }
    }
  }
  if (local_30 != 0) {
    return 1;
  }
  if (uVar4 <= local_40[3]) {
    return 1;
  }
  if (((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cb)) || (cdb_arch == 0x2ca))
     && ((local_60 == 5 || (local_60 == 0xf)))) {
    word_join_hi(local_80);
    bVar2 = true;
  }
  if ((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) {
    if ((local_60 != 4) && (((local_60 != 0xb && (local_60 != 10)) && (local_60 != 0xe)))) {
      *puVar7 = local_80[3];
      *(undefined4 *)((int)out + 0x10) = local_70;
      for (; local_40[3] != 0; local_40[3] = local_40[3] - 1) {
        uVar5 = *puVar7 << 1;
        uVar4 = *(int *)((int)out + 0x10) << 1;
        *puVar7 = uVar5;
        *(uint *)((int)out + 0x10) = uVar4;
        if ((uVar5 & ~cdb_word_mask) != 0) {
          *(uint *)((int)out + 0x10) = uVar4 | 1;
        }
        *puVar7 = cdb_word_mask & uVar5;
        *(uint *)((int)out + 0x10) = *(uint *)((int)out + 0x10) & cdb_word_mask;
      }
      goto LAB_00474c05;
    }
    local_80[3] = local_80[3] << ((byte)local_40[3] & 0x1f);
    *puVar7 = local_80[3];
  }
  else {
    if ((((local_60 == 0x10000) || (local_60 == 0x10001)) ||
        ((local_60 == 0x10003 || ((local_60 == 0x10002 || (local_60 == 0x10004)))))) ||
       (local_60 == 0x10005)) {
      *(undefined4 *)((int)out + 0x10) = local_70;
      *puVar7 = local_80[3];
      *(undefined4 *)((int)out + 0x14) = local_6c;
      if (local_40[3] != 0) {
        local_84 = local_40[3];
        do {
          uVar6 = *puVar7 << 1;
          uVar5 = *(int *)((int)out + 0x10) << 1;
          uVar4 = *(int *)((int)out + 0x14) << 1;
          *puVar7 = uVar6;
          *(uint *)((int)out + 0x10) = uVar5;
          *(uint *)((int)out + 0x14) = uVar4;
          if ((uVar6 & ~cdb_word_mask) != 0) {
            *(uint *)((int)out + 0x10) = uVar5 | 1;
          }
          if ((*(uint *)((int)out + 0x10) & ~cdb_word_mask) != 0) {
            *(uint *)((int)out + 0x14) = uVar4 | 1;
          }
          *puVar7 = cdb_word_mask & uVar6;
          *(uint *)((int)out + 0x10) = cdb_word_mask & *(uint *)((int)out + 0x10);
          local_84 = local_84 - 1;
        } while (local_84 != 0);
      }
      if ((local_60 == 0x10000) || (local_60 == 0x10001)) {
        *(undefined4 *)((int)out + 0x10) = 0;
      }
      else if ((local_60 != 0x10002) && (local_60 != 0x10003)) {
        if (local_60 == 0x10005) {
          *(uint *)((int)out + 0x14) = *(uint *)((int)out + 0x14) & cdb_ext_mask;
        }
        else if (local_60 == 0x10004) {
          *(uint *)((int)out + 0x10) = *(uint *)((int)out + 0x10) & cdb_ext_mask;
        }
        goto LAB_00474c05;
      }
      *(undefined4 *)((int)out + 0x14) = 0;
      goto LAB_00474c05;
    }
    local_80[3] = local_80[3] << ((byte)local_40[3] & 0x1f);
    *puVar7 = local_80[3];
    if (bVar1) {
      *puVar7 = local_80[3];
      goto LAB_00474c05;
    }
  }
  *puVar7 = cdb_word_mask & local_80[3];
LAB_00474c05:
  if (!bVar2) {
    return 1;
  }
  word_split_hi(out);
  return 1;
}


/* ==== shr_values @ 00474c50 ==== */

int __cdecl shr_values(void *a,void *b,void *out)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint *puVar9;
  uint local_80 [4];
  uint local_70;
  uint local_6c;
  int local_60;
  uint local_40 [4];
  int local_30;
  
  bVar4 = false;
  iVar5 = cdb_load_value(a);
  if ((iVar5 == 0) || (iVar5 = cdb_load_value(b), iVar5 == 0)) {
    return 0;
  }
  puVar9 = local_80;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar9 = *(uint *)a;
    a = (uint *)((int)a + 4);
    puVar9 = puVar9 + 1;
  }
  puVar9 = local_40;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar9 = *(uint *)b;
    b = (uint *)((int)b + 4);
    puVar9 = puVar9 + 1;
  }
  puVar9 = (uint *)((int)out + 0xc);
  *puVar9 = 0;
  *(undefined4 *)((int)out + 0x10) = 0;
  *(undefined4 *)((int)out + 0x14) = 0;
  if ((((local_60 == 4) || (local_60 == 0xb)) || (local_60 == 10)) || (local_60 == 0x10000)) {
    bVar1 = false;
LAB_00474d5a:
    bVar2 = false;
  }
  else if ((local_60 == 0xe) || (local_60 == 0x10001)) {
    bVar1 = false;
    bVar2 = true;
  }
  else {
    if ((local_60 == 5) || (local_60 == 0x10002)) {
      bVar1 = true;
      goto LAB_00474d5a;
    }
    if ((local_60 != 0xf) && (local_60 != 0x10003)) {
      cdb_internal_error(0x4d413c,0xea6);
      return 0;
    }
    bVar1 = true;
    bVar2 = true;
  }
  if ((bVar1) &&
     (((((cdb_arch == 0x2c5 || (cdb_arch == 0x2c8)) || (cdb_arch == 0x2cb)) ||
       ((cdb_arch == 0x2ca || (cdb_arch == 0x2c7)))) || (cdb_arch == 0x2c9)))) {
    bVar3 = true;
    uVar6 = cdb_word_bits * 2;
  }
  else if (local_60 == 0x10005) {
    bVar3 = true;
    uVar6 = cdb_ext_bits + cdb_word_bits * 2;
  }
  else if (local_60 == 0x10004) {
    bVar3 = true;
    uVar6 = cdb_word_bits + cdb_ext_bits;
  }
  else {
    bVar3 = false;
    uVar6 = cdb_word_bits;
  }
  if ((local_30 != 0) || (uVar6 <= local_40[3])) {
    if (local_60 == 0x10005) {
      if ((cdb_ext_sign_bit & local_6c) == 0) {
        return 1;
      }
      *puVar9 = cdb_word_mask;
      *(uint *)((int)out + 0x10) = cdb_word_mask;
      *(undefined4 *)((int)out + 0x14) = cdb_ext_mask;
      return 1;
    }
    if (local_60 == 0x10004) {
      if ((cdb_ext_sign_bit & local_70) == 0) {
        return 1;
      }
      *puVar9 = cdb_word_mask;
      *(undefined4 *)((int)out + 0x10) = cdb_ext_mask;
      return 1;
    }
    if (bVar2) {
      return 1;
    }
    if ((!bVar3) || ((local_70 & cdb_sign_bit) == 0)) {
      if (bVar3) {
        return 1;
      }
      if ((local_80[3] & cdb_sign_bit) == 0) {
        return 1;
      }
    }
    *puVar9 = cdb_word_mask;
    if (!bVar3) {
      return 1;
    }
    *(uint *)((int)out + 0x10) = cdb_word_mask;
    return 1;
  }
  if (((((cdb_arch == 0x2c7) || (cdb_arch == 0x2cb)) || (cdb_arch == 0x2ca)) || (cdb_arch == 0x2c9))
     && (bVar1)) {
    word_join_hi(local_80);
    bVar4 = true;
  }
  *puVar9 = local_80[3];
  *(uint *)((int)out + 0x10) = local_70;
  uVar6 = cdb_sign_bit;
  if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2cb)) || ((cdb_arch == 0x2ca || (cdb_arch == 0x2c9))))
     && (bVar1)) {
    uVar6 = cdb_sign_bit << ((byte)cdb_word_bits & 0x1f);
  }
  if ((!bVar3) || (bVar4)) {
    if (((uVar6 & local_80[3]) != 0) && (!bVar2)) {
      bVar1 = true;
      goto joined_r0x00474ec9;
    }
  }
  else if (((uVar6 & local_70) != 0) && (!bVar2)) {
    bVar1 = true;
    goto joined_r0x00474ec9;
  }
  bVar1 = false;
joined_r0x00474ec9:
  for (; local_40[3] != 0; local_40[3] = local_40[3] - 1) {
    if (((bVar3) && (!bVar4)) && ((*(byte *)((int)out + 0x10) & 1) != 0)) {
      *(uint *)((int)out + 0xc) = *(uint *)((int)out + 0xc) | uVar6 * 2;
    }
    uVar7 = *(uint *)((int)out + 0xc) >> 1;
    uVar8 = *(uint *)((int)out + 0x10) >> 1;
    *(uint *)((int)out + 0xc) = uVar7;
    *(uint *)((int)out + 0x10) = uVar8;
    if (bVar1) {
      if ((!bVar3) || (bVar4)) {
        *(uint *)((int)out + 0xc) = uVar6 | uVar7;
      }
      else {
        *(uint *)((int)out + 0x10) = uVar6 | uVar8;
      }
    }
  }
  if (!bVar4) {
    return 1;
  }
  word_split_hi(out);
  return 1;
}


/* ==== and_values @ 00475020 ==== */

int __cdecl and_values(void *a,void *b,void *out)

{
  int iVar1;
  
  iVar1 = cdb_load_value(a);
  if (iVar1 != 0) {
    iVar1 = cdb_load_value(b);
    if (iVar1 != 0) {
      *(undefined4 *)((int)out + 0x10) = *(undefined4 *)((int)a + 0x10);
      *(undefined4 *)((int)out + 0xc) = *(undefined4 *)((int)a + 0xc);
      *(undefined4 *)((int)out + 0x14) = *(undefined4 *)((int)a + 0x14);
      *(uint *)((int)out + 0x10) = *(uint *)((int)out + 0x10) & *(uint *)((int)b + 0x10);
      *(uint *)((int)out + 0xc) = *(uint *)((int)out + 0xc) & *(uint *)((int)b + 0xc);
      *(uint *)((int)out + 0x14) = *(uint *)((int)out + 0x14) & *(uint *)((int)b + 0x14);
      return 1;
    }
  }
  return 0;
}


/* ==== xor_values @ 00475090 ==== */

int __cdecl xor_values(void *a,void *b,void *out)

{
  int iVar1;
  
  iVar1 = cdb_load_value(a);
  if (iVar1 != 0) {
    iVar1 = cdb_load_value(b);
    if (iVar1 != 0) {
      *(undefined4 *)((int)out + 0x14) = *(undefined4 *)((int)a + 0x14);
      *(undefined4 *)((int)out + 0x10) = *(undefined4 *)((int)a + 0x10);
      *(undefined4 *)((int)out + 0xc) = *(undefined4 *)((int)a + 0xc);
      *(uint *)((int)out + 0x14) = *(uint *)((int)out + 0x14) ^ *(uint *)((int)b + 0x14);
      *(uint *)((int)out + 0x10) = *(uint *)((int)out + 0x10) ^ *(uint *)((int)b + 0x10);
      *(uint *)((int)out + 0xc) = *(uint *)((int)out + 0xc) ^ *(uint *)((int)b + 0xc);
      return 1;
    }
  }
  return 0;
}


/* ==== or_values @ 00475100 ==== */

int __cdecl or_values(void *a,void *b,void *out)

{
  int iVar1;
  
  iVar1 = cdb_load_value(a);
  if (iVar1 != 0) {
    iVar1 = cdb_load_value(b);
    if (iVar1 != 0) {
      *(undefined4 *)((int)out + 0x14) = *(undefined4 *)((int)a + 0x14);
      *(undefined4 *)((int)out + 0x10) = *(undefined4 *)((int)a + 0x10);
      *(undefined4 *)((int)out + 0xc) = *(undefined4 *)((int)a + 0xc);
      *(uint *)((int)out + 0x14) = *(uint *)((int)out + 0x14) | *(uint *)((int)b + 0x14);
      *(uint *)((int)out + 0x10) = *(uint *)((int)out + 0x10) | *(uint *)((int)b + 0x10);
      *(uint *)((int)out + 0xc) = *(uint *)((int)out + 0xc) | *(uint *)((int)b + 0xc);
      return 1;
    }
  }
  return 0;
}


/* ==== mod_values @ 00475170 ==== */

int __cdecl mod_values(void *a,void *b,void *out)

{
  int iVar1;
  uint *puVar2;
  bool bVar3;
  ulong local_8c;
  undefined4 local_88;
  uint local_80 [4];
  uint local_70;
  int local_60;
  uint local_40 [4];
  uint local_30;
  
  bVar3 = false;
  iVar1 = cdb_load_value(a);
  if ((iVar1 == 0) || (iVar1 = cdb_load_value(b), iVar1 == 0)) {
    return 0;
  }
  puVar2 = local_80;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *(uint *)a;
    a = (uint *)((int)a + 4);
    puVar2 = puVar2 + 1;
  }
  puVar2 = local_40;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *(uint *)b;
    b = (uint *)((int)b + 4);
    puVar2 = puVar2 + 1;
  }
  if (local_60 == 4) {
LAB_004753fb:
    bVar3 = (cdb_sign_bit & local_80[3]) != 0;
    if (bVar3) {
      value_neg(local_80,local_80);
    }
    if ((cdb_sign_bit & local_40[3]) != 0) {
      value_neg(local_40,local_40);
    }
  }
  else {
    if (((local_60 != 0xb) && (local_60 != 10)) && (local_60 != 0xe)) {
      if (local_60 == 5) {
        if ((((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) ||
              ((cdb_arch == 0x2c5 || ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))))) ||
             (cdb_arch == 0x2c8)) || (local_70 = local_80[3], cdb_arch == 0x2c6)) &&
           ((cdb_sign_bit & local_70) != 0)) {
          bVar3 = true;
          value_neg(local_80,local_80);
        }
        if ((((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2c5)) ||
             ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))) ||
            ((cdb_arch == 0x2c8 || (local_30 = local_40[3], cdb_arch == 0x2c6)))) &&
           ((cdb_sign_bit & local_30) != 0)) {
          value_neg(local_40,local_40);
        }
      }
      else if (local_60 != 0xf) {
        cdb_internal_error(0x4d413c,0x1159);
        return 0;
      }
      if ((cdb_arch == 0x2c8) || (cdb_arch == 0x2c5)) {
        iVar1 = dw_udivmod(local_80 + 3,local_40 + 3,(ulong *)((int)out + 0xc),&local_8c);
        if (iVar1 == 0) {
          return 0;
        }
        *(undefined4 *)((int)out + 0x10) = local_88;
        *(ulong *)((int)out + 0xc) = local_8c;
      }
      else {
        if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cb)) ||
           (cdb_arch == 0x2ca)) {
          word_join_hi(local_80);
          word_join_hi(local_40);
        }
        if (local_40[3] == 0) {
          cdb_c_error(s_attempt_to_perform_modulus_by_0_004d45c8);
          return 0;
        }
        *(uint *)((int)out + 0xc) = local_80[3] % local_40[3];
        if (((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) ||
           ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))) {
          word_split_hi(out);
        }
        *(uint *)((int)out + 0xc) = *(uint *)((int)out + 0xc) & cdb_word_mask;
      }
      goto LAB_0047547c;
    }
    if (((local_60 == 4) || (local_60 == 0xb)) || (local_60 == 10)) goto LAB_004753fb;
  }
  if (local_40[3] == 0) {
    cdb_c_error(s_attempt_to_perform_modulus_by_0_004d45c8);
    return 0;
  }
  *(uint *)((int)out + 0xc) = local_80[3] % local_40[3];
  *(uint *)((int)out + 0xc) = cdb_word_mask & local_80[3] % local_40[3];
LAB_0047547c:
  if (bVar3) {
    value_neg(out,out);
  }
  return 1;
}


/* ==== eval_relational @ 004754b0 ==== */

int __cdecl eval_relational(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  void *a;
  ulong type1;
  int iVar1;
  void *b;
  undefined4 va0;
  
  a = *(void **)(*(int *)plhs + 0x10);
  type1 = *(ulong *)((int)a + 0x20);
  if ((((((((type1 == 2) || (type1 == 3)) || (type1 == 4)) || ((type1 == 0xb || (type1 == 10)))) ||
        ((type1 == 5 || ((type1 == 0xc || (type1 == 0xd)))))) || (type1 == 0xe)) ||
      ((((type1 == 0xf || (type1 == 6)) || (type1 == 7)) ||
       (((type1 == 0x10000 || (type1 == 0x10001)) ||
        ((type1 == 0x10003 || ((type1 == 0x10002 || (type1 == 0x10004)))))))))) ||
     (type1 == 0x10005)) {
    b = *(void **)(*(int *)prhs + 0x10);
    iVar1 = *(int *)((int)b + 0x20);
    if ((((((iVar1 == 2) || (iVar1 == 3)) || (iVar1 == 4)) ||
         (((iVar1 == 0xb || (iVar1 == 10)) ||
          (((iVar1 == 5 || ((iVar1 == 0xc || (iVar1 == 0xd)))) || (iVar1 == 0xe)))))) ||
        (((((iVar1 == 0xf || (iVar1 == 6)) || (iVar1 == 7)) ||
          ((iVar1 == 0x10000 || (iVar1 == 0x10001)))) ||
         ((iVar1 == 0x10003 || ((iVar1 == 0x10002 || (iVar1 == 0x10004)))))))) || (iVar1 == 0x10005)
       ) {
      if (do_eval == 0) {
        usual_arith_conv(plhs,prhs);
        copy_node_type(result_node,*(void **)plhs);
        *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x20) = 4;
        return 1;
      }
      switch(op) {
      case 0x3c:
        goto switchD_00475671_caseD_3c;
      default:
        va0 = 0x1da7;
        goto LAB_004757bf;
      case 0x3e:
        goto switchD_00475671_caseD_3e;
      case 0x132:
        goto switchD_00475671_caseD_132;
      case 0x133:
        goto switchD_00475671_caseD_133;
      }
    }
  }
  if (((byte)type1 & 0x30) == 0x10) {
    b = *(void **)(*(int *)prhs + 0x10);
    if (((byte)*(ulong *)((int)b + 0x20) & 0x30) == 0x10) {
      if (do_eval == 0) {
        iVar1 = cdb_types_match(type1,*(int *)((int)a + 0x28),*(ulong *)((int)b + 0x20),
                                *(int *)((int)b + 0x28));
        if (iVar1 == 0) {
          dsp_free_ext(s_comparing_two_incompatible_point_004d4668);
        }
        copy_node_type((void *)0x0,*(void **)plhs);
        *(undefined4 *)(iRam00000010 + 0x20) = 4;
        return 1;
      }
      switch(op) {
      case 0x3c:
switchD_00475671_caseD_3c:
        iVar1 = lt_values(a,b,*(void **)((int)result_node + 0x10));
        return iVar1;
      default:
        va0 = 0x1dd8;
LAB_004757bf:
        cdb_internal_error(0x4d413c,va0);
        return 0;
      case 0x3e:
switchD_00475671_caseD_3e:
        iVar1 = gt_values(a,b,*(void **)((int)result_node + 0x10));
        return iVar1;
      case 0x132:
switchD_00475671_caseD_132:
        iVar1 = le_values(a,b,*(void **)((int)result_node + 0x10));
        return iVar1;
      case 0x133:
switchD_00475671_caseD_133:
        iVar1 = ge_values(a,b,*(void **)((int)result_node + 0x10));
        return iVar1;
      }
    }
  }
  switch(op) {
  case 0x3c:
    cdb_error(s_operands_of_binary_<_invalid_004d4648);
    return 0;
  default:
    cdb_internal_error(0x4d413c,0x1df2);
    return 0;
  case 0x3e:
    cdb_error(s_operands_of_binary_>_invalid_004d4628);
    return 0;
  case 0x132:
    cdb_error(s_operands_of_binary_<__invalid_004d4608);
    return 0;
  case 0x133:
    cdb_error(s_operands_of_binary_>__invalid_004d45e8);
    return 0;
  }
}


/* ==== ge_values @ 00475b00 ==== */

int __cdecl ge_values(void *a,void *b,void *out)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = gt_values(a,b,out);
  if (iVar2 == 0) {
    return 0;
  }
  uVar1 = *(uint *)((int)out + 0xc);
  iVar2 = eq_values(a,b,out);
  if (iVar2 == 0) {
    return 0;
  }
  *(uint *)((int)out + 0xc) = *(uint *)((int)out + 0xc) | uVar1;
  return 1;
}


/* ==== eq_values @ 00475b50 ==== */

int __cdecl eq_values(void *a,void *b,void *out)

{
  int iVar1;
  double *pdVar2;
  double local_80;
  float local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  int local_60;
  double local_40;
  float local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  
  iVar1 = cdb_load_value(a);
  if (iVar1 != 0) {
    iVar1 = cdb_load_value(b);
    if (iVar1 != 0) {
      pdVar2 = &local_80;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *(undefined4 *)pdVar2 = *(undefined4 *)a;
        a = (undefined4 *)((int)a + 4);
        pdVar2 = (double *)((int)pdVar2 + 4);
      }
      pdVar2 = &local_40;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *(undefined4 *)pdVar2 = *(undefined4 *)b;
        b = (undefined4 *)((int)b + 4);
        pdVar2 = (double *)((int)pdVar2 + 4);
      }
      *(undefined4 *)((int)out + 0x10) = 0;
      if (((byte)local_60 & 0x30) == 0x10) {
        *(uint *)((int)out + 0xc) = (uint)(local_74 == local_34);
        return 1;
      }
      if (((((local_60 == 4) || (local_60 == 0xb)) || (local_60 == 10)) ||
          ((local_60 == 0x10000 || (local_60 == 0x10001)))) || (local_60 == 0xe)) {
        *(uint *)((int)out + 0xc) = (uint)(local_74 == local_34);
        return 1;
      }
      if (local_60 == 0x10004) {
        if ((local_74 == local_34) && ((local_70 & cdb_ext_mask) == (local_30 & cdb_ext_mask))) {
          *(undefined4 *)((int)out + 0xc) = 1;
          return 1;
        }
      }
      else if (((local_60 == 5) || (local_60 == 0x10002)) ||
              ((local_60 == 0x10003 || (local_60 == 0xf)))) {
        if (cdb_arch == 0x2c6) {
          *(uint *)((int)out + 0xc) = (uint)(local_74 == local_34);
          return 1;
        }
        if ((local_74 == local_34) && (local_70 == local_30)) {
          *(undefined4 *)((int)out + 0xc) = 1;
          return 1;
        }
      }
      else if (local_60 == 0x10005) {
        if ((((local_74 & cdb_word_mask) == (local_34 & cdb_word_mask)) &&
            ((local_6c & cdb_ext_mask) == (local_2c & cdb_ext_mask))) &&
           ((local_70 & cdb_word_mask) == (local_30 & cdb_word_mask))) {
          *(undefined4 *)((int)out + 0xc) = 1;
          return 1;
        }
      }
      else {
        if ((local_60 != 6) && (local_60 != 7)) {
          cdb_internal_error(0x4d413c,0x125e);
          return 0;
        }
        if ((cdb_arch == 0x2c8) || (cdb_arch == 0x2c5)) {
          if ((local_74 == local_34) && (local_70 == local_30)) {
            *(undefined4 *)((int)out + 0xc) = 1;
            return 1;
          }
        }
        else {
          if ((((local_60 != 6) && (cdb_arch != 0x2c7)) && (cdb_arch != 0x2c9)) &&
             ((cdb_arch != 0x2cb && (cdb_arch != 0x2ca)))) {
            value_copy_trunc(&local_80,&local_80);
            value_copy_trunc(&local_40,&local_40);
            if (local_80 == local_40) {
              *(undefined4 *)((int)out + 0xc) = 1;
              value_copy_trunc(out,out);
              return 1;
            }
            *(undefined4 *)((int)out + 0xc) = 0;
            value_copy_trunc(out,out);
            return 1;
          }
          if (local_78 == local_38) {
            *(undefined4 *)((int)out + 0xc) = 1;
            return 1;
          }
        }
      }
      *(undefined4 *)((int)out + 0xc) = 0;
      return 1;
    }
  }
  return 0;
}


/* ==== le_values @ 00475ec0 ==== */

int __cdecl le_values(void *a,void *b,void *out)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = lt_values(a,b,out);
  if (iVar2 == 0) {
    return 0;
  }
  uVar1 = *(uint *)((int)out + 0xc);
  iVar2 = eq_values(a,b,out);
  if (iVar2 == 0) {
    return 0;
  }
  *(uint *)((int)out + 0xc) = *(uint *)((int)out + 0xc) | uVar1;
  return 1;
}


/* ==== gt_values @ 00475f10 ==== */

int __cdecl gt_values(void *a,void *b,void *out)

{
  int iVar1;
  
  iVar1 = lt_values(b,a,out);
  return (uint)(iVar1 != 0);
}


/* ==== lt_values @ 00475f30 ==== */

int __cdecl lt_values(void *a,void *b,void *out)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  double *pdVar4;
  bool bVar5;
  double local_80;
  float local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  int local_60;
  double local_40;
  float local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  
  iVar1 = cdb_load_value(a);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = cdb_load_value(b);
  if (iVar1 == 0) {
    return 0;
  }
  pdVar4 = &local_80;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined4 *)pdVar4 = *(undefined4 *)a;
    a = (undefined4 *)((int)a + 4);
    pdVar4 = (double *)((int)pdVar4 + 4);
  }
  pdVar4 = &local_40;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined4 *)pdVar4 = *(undefined4 *)b;
    b = (undefined4 *)((int)b + 4);
    pdVar4 = (double *)((int)pdVar4 + 4);
  }
  *(undefined4 *)((int)out + 0x10) = 0;
  if (((byte)local_60 & 0x30) == 0x10) {
LAB_004764e1:
    *(uint *)((int)out + 0xc) = (uint)(local_74 < local_34);
    return 1;
  }
  if ((((local_60 == 4) || (local_60 == 0xb)) || (local_60 == 10)) || (local_60 == 0x10000)) {
    if (((cdb_sign_bit & local_74) != 0) &&
       ((((cdb_arch == 0x2c7 || (cdb_arch == 0x2c9)) ||
         ((cdb_arch == 0x2cb || ((cdb_arch == 0x2ca || (cdb_arch == 0x2c8)))))) ||
        (cdb_arch == 0x2c5)))) {
      local_74 = local_74 | ~cdb_word_mask;
    }
    if (((cdb_sign_bit & local_34) != 0) &&
       ((((cdb_arch == 0x2c7 || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cb)) ||
        (((cdb_arch == 0x2ca || (cdb_arch == 0x2c8)) || (cdb_arch == 0x2c5)))))) {
      local_34 = local_34 | ~cdb_word_mask;
    }
    *(uint *)((int)out + 0xc) = (uint)((int)local_74 < (int)local_34);
    return 1;
  }
  if ((local_60 == 0xe) || (local_60 == 0x10001)) {
LAB_00476038:
    bVar5 = local_74 < local_34;
LAB_00476042:
    *(uint *)((int)out + 0xc) = (uint)bVar5;
    return 1;
  }
  if ((local_60 == 5) || (local_60 == 0x10002)) {
    if ((cdb_arch != 0x2c8) && (cdb_arch != 0x2c5)) {
      if ((cdb_arch == 0x2c7) ||
         (((cdb_arch == 0x2c9 || (cdb_arch == 0x2cb)) || (cdb_arch == 0x2ca)))) {
        word_join_hi(&local_80);
        word_join_hi(&local_40);
      }
      *(uint *)((int)out + 0xc) = (uint)((int)local_74 < (int)local_34);
      return 1;
    }
    uVar2 = local_70;
    if ((cdb_sign_bit & local_70) != 0) {
      uVar2 = local_70 | ~cdb_word_mask;
    }
    uVar3 = local_30;
    if ((cdb_sign_bit & local_30) != 0) {
      uVar3 = local_30 | ~cdb_word_mask;
    }
    if ((int)uVar2 < (int)uVar3) {
      *(undefined4 *)((int)out + 0xc) = 1;
      return 1;
    }
    if (local_70 != local_30) {
      *(undefined4 *)((int)out + 0xc) = 0;
      return 1;
    }
    goto LAB_004764e1;
  }
  if (local_60 == 0x10004) {
    if ((cdb_ext_sign_bit & local_70) != 0) {
      local_70 = local_70 | ~cdb_ext_mask;
    }
    if ((cdb_ext_sign_bit & local_30) != 0) {
      local_30 = local_30 | ~cdb_ext_mask;
    }
    if ((int)local_70 < (int)local_30) {
      *(undefined4 *)((int)out + 0xc) = 1;
      return 1;
    }
    if (local_70 != local_30) goto LAB_00476411;
    goto LAB_00476038;
  }
  if (local_60 == 0x10005) {
    if ((cdb_ext_sign_bit & local_6c) != 0) {
      local_6c = local_6c | ~cdb_ext_mask;
    }
    if ((cdb_ext_sign_bit & local_2c) != 0) {
      local_2c = local_2c | ~cdb_ext_mask;
    }
    if ((int)local_6c < (int)local_2c) {
      *(undefined4 *)((int)out + 0xc) = 1;
      return 1;
    }
    if (local_6c != local_2c) goto LAB_00476411;
    bVar5 = local_70 < local_30;
    if (local_70 == local_30) {
      *(uint *)((int)out + 0xc) = (uint)(local_74 < local_34);
      return 1;
    }
    goto LAB_00476042;
  }
  if ((local_60 == 0xf) || (local_60 == 0x10003)) {
    if ((cdb_arch != 0x2c8) && (cdb_arch != 0x2c5)) {
      if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2cb)) ||
         (cdb_arch == 0x2ca)) {
        word_join_hi(&local_80);
        word_join_hi(&local_40);
      }
      *(uint *)((int)out + 0xc) = (uint)(local_74 < local_34);
      return 1;
    }
    if (local_70 < local_30) {
      *(undefined4 *)((int)out + 0xc) = 1;
      return 1;
    }
    if (local_70 == local_30) goto LAB_004764e1;
    goto LAB_00476411;
  }
  if ((local_60 != 6) && (local_60 != 7)) {
    cdb_internal_error(0x4d413c,0x139b);
    return 0;
  }
  if ((cdb_arch != 0x2c8) && (cdb_arch != 0x2c5)) {
    if ((local_60 != 6) &&
       ((((cdb_arch != 0x2c7 && (cdb_arch != 0x2c9)) && (cdb_arch != 0x2cb)) && (cdb_arch != 0x2ca))
       )) {
      value_copy_trunc(&local_80,&local_80);
      value_copy_trunc(&local_40,&local_40);
      if (local_40 <= local_80) {
        *(undefined4 *)((int)out + 0xc) = 0;
        value_copy_trunc(out,out);
        return 1;
      }
      *(undefined4 *)((int)out + 0xc) = 1;
      value_copy_trunc(out,out);
      return 1;
    }
    if (local_38 <= local_78) {
      *(undefined4 *)((int)out + 0xc) = 0;
      return 1;
    }
    *(undefined4 *)((int)out + 0xc) = 1;
    return 1;
  }
  uVar2 = local_70 >> 0x17 & 1;
  uVar3 = local_30 >> 0x17 & 1;
  if (uVar2 == 0) {
LAB_004762f5:
    if (uVar3 != 0) {
      *(undefined4 *)((int)out + 0xc) = 0;
      return 1;
    }
    if (uVar2 != 0) goto LAB_00476310;
  }
  else {
    if (uVar3 == 0) {
      *(undefined4 *)((int)out + 0xc) = 1;
      return 1;
    }
    if (uVar2 == 0) goto LAB_004762f5;
LAB_00476310:
    if (uVar3 != 0) {
      value_neg(&local_80,&local_80);
      value_neg(&local_40,&local_40);
    }
  }
  if (local_74 < local_34) {
    *(undefined4 *)((int)out + 0xc) = 1;
    return 1;
  }
  if (local_74 == local_34) {
    *(uint *)((int)out + 0xc) = (uint)(local_70 < local_30);
    return 1;
  }
LAB_00476411:
  *(undefined4 *)((int)out + 0xc) = 0;
  return 1;
}


/* ==== eval_equality @ 00476520 ==== */

int __cdecl eval_equality(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  void *a;
  ulong type1;
  void *pvVar1;
  uint uVar2;
  int iVar3;
  
  a = *(void **)(*(int *)plhs + 0x10);
  type1 = *(ulong *)((int)a + 0x20);
  if ((((((type1 == 2) || (type1 == 3)) || (type1 == 4)) ||
       (((((type1 == 0xb || (type1 == 10)) || ((type1 == 5 || ((type1 == 0xc || (type1 == 0xd))))))
         || (type1 == 0xe)) || (((type1 == 0xf || (type1 == 6)) || (type1 == 7)))))) ||
      (((type1 == 0x10000 || (type1 == 0x10001)) ||
       ((type1 == 0x10003 || ((type1 == 0x10002 || (type1 == 0x10004)))))))) || (type1 == 0x10005))
  {
    pvVar1 = *(void **)(*(int *)prhs + 0x10);
    iVar3 = *(int *)((int)pvVar1 + 0x20);
    if ((((((((iVar3 == 2) || (iVar3 == 3)) || (iVar3 == 4)) || ((iVar3 == 0xb || (iVar3 == 10))))
          || (iVar3 == 5)) ||
         (((iVar3 == 0xc || (iVar3 == 0xd)) ||
          ((iVar3 == 0xe || (((iVar3 == 0xf || (iVar3 == 6)) || (iVar3 == 7)))))))) ||
        ((iVar3 == 0x10000 || (iVar3 == 0x10001)))) ||
       ((iVar3 == 0x10003 || (((iVar3 == 0x10002 || (iVar3 == 0x10004)) || (iVar3 == 0x10005)))))) {
      if (do_eval == 0) {
        usual_arith_conv(plhs,prhs);
        copy_node_type(result_node,*(void **)plhs);
        *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x20) = 4;
        return 1;
      }
      if (op != 0x130) {
        if (op != 0x131) {
          cdb_internal_error(0x4d413c,0x1e1b);
          return 0;
        }
        iVar3 = ne_values(a,pvVar1,*(void **)((int)result_node + 0x10));
        return iVar3;
      }
      iVar3 = eq_values(a,pvVar1,*(void **)((int)result_node + 0x10));
      return iVar3;
    }
  }
  if (((byte)type1 & 0x30) == 0x10) {
    pvVar1 = *(void **)(*(int *)prhs + 0x10);
    if (((byte)*(ulong *)((int)pvVar1 + 0x20) & 0x30) == 0x10) {
      if (do_eval == 0) {
        iVar3 = cdb_types_match(type1,*(int *)((int)a + 0x28),*(ulong *)((int)pvVar1 + 0x20),
                                *(int *)((int)pvVar1 + 0x28));
        if (((iVar3 == 0) &&
            (uVar2 = *(uint *)(*(int *)(*(int *)plhs + 0x10) + 0x20),
            (uVar2 >> 2 & 0x3ffebff0 | uVar2 & 0x1000f) != 1)) &&
           (uVar2 = *(uint *)(*(int *)(*(int *)prhs + 0x10) + 0x20),
           (uVar2 >> 2 & 0x3ffebff0 | uVar2 & 0x1000f) != 1)) {
          dsp_free_ext(s_comparing_two_incompatible_point_004d4668);
        }
        copy_node_type((void *)0x0,*(void **)plhs);
        *(undefined4 *)(iRam00000010 + 0x20) = 4;
        return 1;
      }
      if (op != 0x130) {
        if (op != 0x131) {
          cdb_internal_error(0x4d413c,0x1e45);
          return 0;
        }
        iVar3 = ne_values(a,pvVar1,*(void **)((int)result_node + 0x10));
        return iVar3;
      }
      iVar3 = eq_values(a,pvVar1,*(void **)((int)result_node + 0x10));
      return iVar3;
    }
  }
  if (op == 0x130) {
    cdb_error(s_operands_of_binary____invalid_004d4694);
    return 0;
  }
  if (op != 0x131) {
    cdb_internal_error(0x4d413c,0x1e58);
    return 0;
  }
  cdb_error(s_operands_of_binary____invalid_004d46b4);
  return 0;
}


/* ==== ne_values @ 00476860 ==== */

int __cdecl ne_values(void *a,void *b,void *out)

{
  int iVar1;
  
  iVar1 = eq_values(a,b,out);
  if (iVar1 == 0) {
    return 0;
  }
  *(uint *)((int)out + 0xc) = (uint)(*(int *)((int)out + 0xc) == 0);
  return 1;
}


/* ==== eval_logical @ 004768a0 ==== */

int __cdecl eval_logical(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  void *a;
  void *b;
  int iVar1;
  
  a = *(void **)((int)*(void **)plhs + 0x10);
  iVar1 = *(int *)((int)a + 0x20);
  if ((((((((iVar1 == 2) || (iVar1 == 3)) || (iVar1 == 4)) || ((iVar1 == 0xb || (iVar1 == 10)))) ||
        ((iVar1 == 5 || ((iVar1 == 0xc || (iVar1 == 0xd)))))) || (iVar1 == 0xe)) ||
      ((((iVar1 == 0xf || (iVar1 == 6)) || (iVar1 == 7)) ||
       (((iVar1 == 0x10000 || (iVar1 == 0x10001)) ||
        ((iVar1 == 0x10003 || ((iVar1 == 0x10002 || (iVar1 == 0x10004)))))))))) ||
     ((iVar1 == 0x10005 || (((byte)iVar1 & 0x30) == 0x10)))) {
    b = *(void **)(*(int *)prhs + 0x10);
    iVar1 = *(int *)((int)b + 0x20);
    if (((((iVar1 == 2) || (iVar1 == 3)) || (iVar1 == 4)) ||
        (((iVar1 == 0xb || (iVar1 == 10)) ||
         (((iVar1 == 5 || ((iVar1 == 0xc || (iVar1 == 0xd)))) || (iVar1 == 0xe)))))) ||
       (((((((iVar1 == 0xf || (iVar1 == 6)) || (iVar1 == 7)) ||
           ((iVar1 == 0x10000 || (iVar1 == 0x10001)))) ||
          ((iVar1 == 0x10003 || ((iVar1 == 0x10002 || (iVar1 == 0x10004)))))) || (iVar1 == 0x10005))
        || (((byte)iVar1 & 0x30) == 0x10)))) {
      if (do_eval == 0) {
        copy_node_type(result_node,*(void **)plhs);
        *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x20) = 4;
        return 1;
      }
      if (op != 0x12e) {
        if (op != 0x12f) {
          cdb_internal_error(0x4d413c,0x1e80);
          return 0;
        }
        iVar1 = logand_values(a,b,*(void **)((int)result_node + 0x10));
        return iVar1;
      }
      iVar1 = logor_values(a,b,*(void **)((int)result_node + 0x10));
      return iVar1;
    }
  }
  if (op == 0x12e) {
    cdb_error(s_operands_of_binary____invalid_004d46d4);
    return 0;
  }
  if (op != 0x12f) {
    cdb_internal_error(0x4d413c,0x1e94);
    return 0;
  }
  cdb_error(s_operands_of_binary____invalid_004d46f4);
  return 0;
}


/* ==== logand_values @ 00476a90 ==== */

int __cdecl logand_values(void *a,void *b,void *out)

{
  int iVar1;
  
  iVar1 = cdb_load_value(a);
  if (iVar1 != 0) {
    iVar1 = cdb_load_value(b);
    if (iVar1 != 0) {
      *(undefined4 *)((int)out + 0x10) = 0;
      iVar1 = value_is_true(a);
      if (iVar1 == 0) {
        iVar1 = value_is_true(b);
        if (iVar1 == 0) {
          *(undefined4 *)((int)out + 0xc) = 1;
          return 1;
        }
      }
      *(undefined4 *)((int)out + 0xc) = 0;
      return 1;
    }
  }
  return 0;
}


/* ==== logor_values @ 00476b00 ==== */

int __cdecl logor_values(void *a,void *b,void *out)

{
  int iVar1;
  
  iVar1 = cdb_load_value(a);
  if (iVar1 != 0) {
    iVar1 = cdb_load_value(b);
    if (iVar1 != 0) {
      *(undefined4 *)((int)out + 0x10) = 0;
      iVar1 = value_is_true(a);
      if (iVar1 != 0) {
        iVar1 = value_is_true(b);
        if (iVar1 != 0) {
          *(undefined4 *)((int)out + 0xc) = 0;
          return 1;
        }
      }
      *(undefined4 *)((int)out + 0xc) = 1;
      return 1;
    }
  }
  return 0;
}


/* ==== eval_assign @ 00476b70 ==== */

int __cdecl eval_assign(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  void *lhs;
  uint uVar1;
  int iVar2;
  undefined4 extraout_EAX;
  void *src_node;
  void *rhs;
  
  src_node = *(void **)plhs;
  lhs = *(void **)((int)src_node + 0x10);
  if (*(short *)((int)lhs + 0x3c) == 1) {
    uVar1 = *(uint *)((int)lhs + 0x20);
    if ((uVar1 & 0x30) != 0x30) {
      if ((((((uVar1 == 2) || (uVar1 == 3)) || (uVar1 == 4)) || ((uVar1 == 0xb || (uVar1 == 10))))
          || (((uVar1 == 5 || ((uVar1 == 0xc || (uVar1 == 0xd)))) ||
              ((uVar1 == 0xe ||
               ((((uVar1 == 0xf || (uVar1 == 6)) || (uVar1 == 7)) ||
                (((uVar1 == 0x10000 || (uVar1 == 0x10001)) ||
                 ((uVar1 == 0x10003 || ((uVar1 == 0x10002 || (uVar1 == 0x10004)))))))))))))) ||
         (uVar1 == 0x10005)) {
        iVar2 = *(int *)((int)*(void **)(*(int *)prhs + 0x10) + 0x20);
        if (((((iVar2 == 2) || (iVar2 == 3)) || (iVar2 == 4)) ||
            (((iVar2 == 0xb || (iVar2 == 10)) ||
             (((iVar2 == 5 || ((iVar2 == 0xc || (iVar2 == 0xd)))) || (iVar2 == 0xe)))))) ||
           ((((((iVar2 == 0xf || (iVar2 == 6)) || (iVar2 == 7)) ||
              ((iVar2 == 0x10000 || (iVar2 == 0x10001)))) || (iVar2 == 0x10003)) ||
            (((iVar2 == 0x10002 || (iVar2 == 0x10004)) || (iVar2 == 0x10005)))))) {
          if (do_eval == 0) {
            copy_node_type(result_node,src_node);
            make_cast_node(*(int *)(*(int *)(*(int *)plhs + 0x10) + 0x20),*(void **)prhs);
            *(undefined4 *)prhs = extraout_EAX;
            return 1;
          }
          iVar2 = assign_values(lhs,*(void **)(*(int *)prhs + 0x10),
                                *(void **)((int)result_node + 0x10));
          return iVar2;
        }
      }
      if ((uVar1 == 8) && (*(int *)(*(int *)(*(int *)prhs + 0x10) + 0x20) == 8)) {
        if ((*(int *)((int)lhs + 0x28) == 0) ||
           (iVar2 = *(int *)(*(int *)(*(int *)prhs + 0x10) + 0x28), iVar2 == 0)) {
          cdb_error(s_structure_type_and_contents_not_a_004d47e4);
          return 0;
        }
        iVar2 = cdb_types_match(8,*(int *)((int)lhs + 0x28),8,iVar2);
        if (iVar2 != 0) {
          cdb_error(s_incompatible_structure_types_in_a_004d4810);
          return 0;
        }
        if (do_eval == 0) {
          copy_node_type(result_node,*(void **)plhs);
          return 1;
        }
      }
      else {
        if ((uVar1 != 9) || (*(int *)(*(int *)(*(int *)prhs + 0x10) + 0x20) != 9)) {
          if ((uVar1 & 0x30) == 0x10) {
            rhs = *(void **)(*(int *)prhs + 0x10);
            if (((byte)*(ulong *)((int)rhs + 0x20) & 0x30) == 0x10) {
              if (do_eval != 0) {
LAB_00476ec3:
                iVar2 = assign_values(lhs,rhs,*(void **)((int)result_node + 0x10));
                return iVar2;
              }
              iVar2 = cdb_types_match(uVar1,*(int *)((int)lhs + 0x28),*(ulong *)((int)rhs + 0x20),
                                      *(int *)((int)rhs + 0x28));
              if ((iVar2 == 0) &&
                 (uVar1 = *(uint *)(*(int *)(*(int *)prhs + 0x10) + 0x20),
                 (uVar1 >> 2 & 0x3ffebff0 | uVar1 & 0x1000f) != 1)) {
                dsp_free_ext(s_assignment_of_two_incompatible_p_004d4764);
              }
              src_node = *(void **)prhs;
            }
            else {
              rhs = *(void **)(*(int *)prhs + 0x10);
              iVar2 = *(int *)((int)rhs + 0x20);
              if ((((((iVar2 != 2) && (iVar2 != 3)) && (iVar2 != 4)) &&
                   (((iVar2 != 0xb && (iVar2 != 10)) &&
                    ((iVar2 != 5 && ((iVar2 != 0xc && (iVar2 != 0xd)))))))) && (iVar2 != 0xe)) &&
                 (iVar2 != 0xf)) goto LAB_00476edb;
              if (do_eval != 0) goto LAB_00476ec3;
            }
            copy_node_type((void *)do_eval,src_node);
            return 1;
          }
LAB_00476edb:
          cdb_error(s_incompatible_types_in_assignment_004d4740);
          return 0;
        }
        if ((*(int *)((int)lhs + 0x28) == 0) ||
           (iVar2 = *(int *)(*(int *)(*(int *)prhs + 0x10) + 0x28), iVar2 == 0)) {
          cdb_error(s_union_type_and_contents_not_avai_004d4794);
          return 0;
        }
        iVar2 = cdb_types_match(9,*(int *)((int)lhs + 0x28),9,iVar2);
        if (iVar2 != 0) {
          cdb_error(s_incompatible_union_types_in_assi_004d47bc);
          return 0;
        }
        if (do_eval == 0) {
          copy_node_type(result_node,*(void **)plhs);
          return 1;
        }
      }
      iVar2 = assign_values(*(void **)(*(int *)plhs + 0x10),*(void **)(*(int *)prhs + 0x10),
                            *(void **)((int)result_node + 0x10));
      return iVar2;
    }
  }
  cdb_error(s_left_side_is_not_an_lvalue_in_as_004d4714);
  return 0;
}


/* ==== assign_values @ 00476f60 ==== */

int __cdecl assign_values(void *lhs,void *rhs,void *out)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_40 [4];
  undefined4 local_30;
  undefined4 local_2c;
  
  iVar1 = cdb_load_value(rhs);
  if (iVar1 == 0) {
    return 0;
  }
  puVar2 = local_40;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *(undefined4 *)rhs;
    rhs = (undefined4 *)((int)rhs + 4);
    puVar2 = puVar2 + 1;
  }
  if (cdb_arch == 0x2c6) {
    value_copy_trunc(local_40,local_40);
  }
  *(undefined4 *)lhs = local_40[0];
  *(undefined4 *)((int)lhs + 4) = local_40[1];
  *(undefined4 *)((int)lhs + 8) = local_40[2];
  *(undefined4 *)((int)lhs + 0xc) = local_40[3];
  *(undefined4 *)((int)lhs + 0x10) = local_30;
  *(undefined4 *)((int)lhs + 0x14) = local_2c;
  iVar1 = cdb_store_value(lhs);
  if (iVar1 == 0) {
    return 0;
  }
  *(undefined4 *)out = *(undefined4 *)lhs;
  *(undefined4 *)((int)out + 4) = *(undefined4 *)((int)lhs + 4);
  *(undefined4 *)((int)out + 8) = *(undefined4 *)((int)lhs + 8);
  *(undefined4 *)((int)out + 0xc) = *(undefined4 *)((int)lhs + 0xc);
  *(undefined4 *)((int)out + 0x10) = *(undefined4 *)((int)lhs + 0x10);
  *(undefined4 *)((int)out + 0x14) = *(undefined4 *)((int)lhs + 0x14);
  return 1;
}


/* ==== eval_muldiv_assign @ 00477020 ==== */

int __cdecl eval_muldiv_assign(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  int iVar1;
  undefined4 uVar2;
  void *src_node;
  undefined4 *dst_node;
  undefined4 extraout_EAX;
  
  iVar1 = *(int *)((int)*(void **)plhs + 0x10);
  if ((*(short *)(iVar1 + 0x3c) != 1) ||
     (iVar1 = *(int *)(iVar1 + 0x20), ((byte)iVar1 & 0x30) == 0x30)) {
    cdb_error(s_left_side_is_not_an_lvalue_in_as_004d4714);
    return 0;
  }
  if (((((((((iVar1 == 2) || (iVar1 == 3)) || (iVar1 == 4)) || ((iVar1 == 0xb || (iVar1 == 10)))) ||
         ((iVar1 == 5 || ((iVar1 == 0xc || (iVar1 == 0xd)))))) || (iVar1 == 0xe)) ||
       ((((iVar1 == 0xf || (iVar1 == 6)) || (iVar1 == 7)) ||
        (((iVar1 == 0x10000 || (iVar1 == 0x10001)) ||
         ((iVar1 == 0x10003 || ((iVar1 == 0x10002 || (iVar1 == 0x10004)))))))))) ||
      (iVar1 == 0x10005)) &&
     ((((((iVar1 = *(int *)(*(int *)(*(int *)prhs + 0x10) + 0x20), iVar1 == 2 || (iVar1 == 3)) ||
         (iVar1 == 4)) ||
        (((iVar1 == 0xb || (iVar1 == 10)) ||
         (((iVar1 == 5 || ((iVar1 == 0xc || (iVar1 == 0xd)))) || (iVar1 == 0xe)))))) ||
       (((((iVar1 == 0xf || (iVar1 == 6)) || (iVar1 == 7)) ||
         ((iVar1 == 0x10000 || (iVar1 == 0x10001)))) ||
        ((iVar1 == 0x10003 || ((iVar1 == 0x10002 || (iVar1 == 0x10004)))))))) || (iVar1 == 0x10005))
     )) {
    if (do_eval != 0) {
      return 0;
    }
    clone_tree(*(void **)plhs);
    usual_arith_conv(plhs,prhs);
    new_node();
    dst_node[3] = (-(uint)(op != 0x124) & 5) + 0x2a;
    uVar2 = *(undefined4 *)plhs;
    dst_node[1] = 0;
    *dst_node = uVar2;
    dst_node[2] = *(undefined4 *)prhs;
    dst_node[5] = 0;
    copy_node_type(dst_node,*(void **)plhs);
    make_cast_node(*(int *)(*(int *)((int)src_node + 0x10) + 0x20),dst_node);
    copy_node_type(result_node,src_node);
    *(undefined4 *)((int)result_node + 0xc) = 0x3d;
    *(void **)plhs = src_node;
    *(undefined4 *)prhs = extraout_EAX;
    return 1;
  }
  if (op == 0x124) {
    cdb_error(s_operands_of_binary____are_not_bo_004d483c);
    return 0;
  }
  if (op == 0x125) {
    cdb_error(s_operands_of_binary____are_not_bo_004d4870);
    return 0;
  }
  cdb_internal_error(0x4d413c,0x1f6f);
  return 0;
}


/* ==== eval_bitop_assign @ 00477250 ==== */

int __cdecl eval_bitop_assign(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  int iVar1;
  undefined4 uVar2;
  void *src_node;
  undefined4 *dst_node;
  undefined4 extraout_EAX;
  
  iVar1 = *(int *)((int)*(void **)plhs + 0x10);
  if ((*(short *)(iVar1 + 0x3c) == 1) &&
     (iVar1 = *(int *)(iVar1 + 0x20), ((byte)iVar1 & 0x30) != 0x30)) {
    if ((((((((iVar1 != 2) && (iVar1 != 3)) && (iVar1 != 4)) && ((iVar1 != 0xb && (iVar1 != 10))))
          && ((iVar1 != 5 && ((iVar1 != 0xc && (iVar1 != 0xd)))))) && (iVar1 != 0xe)) &&
        (iVar1 != 0xf)) ||
       (((((iVar1 = *(int *)(*(int *)(*(int *)prhs + 0x10) + 0x20), iVar1 != 2 && (iVar1 != 3)) &&
          (iVar1 != 4)) &&
         (((iVar1 != 0xb && (iVar1 != 10)) && ((iVar1 != 5 && ((iVar1 != 0xc && (iVar1 != 0xd)))))))
         ) && ((iVar1 != 0xe && (iVar1 != 0xf)))))) {
      switch(op) {
      case 0x126:
        cdb_error(s_operands_of_binary____are_not_bo_004d49a8);
        return 0;
      default:
        cdb_internal_error(0x4d413c,0x1fdd);
        return 0;
      case 0x129:
        cdb_error(s_operands_of_binary_<<__are_not_b_004d4974);
        return 0;
      case 0x12a:
        cdb_error(s_operands_of_binary_>>__are_not_b_004d4940);
        return 0;
      case 299:
        cdb_error(s_operands_of_binary____are_not_bo_004d490c);
        return 0;
      case 300:
        cdb_error(s_operands_of_binary____are_not_bo_004d48d8);
        return 0;
      case 0x12d:
        cdb_error(s_operands_of_binary____are_not_bo_004d48a4);
        return 0;
      }
    }
    if (do_eval == 0) {
      clone_tree(*(void **)plhs);
      usual_arith_conv(plhs,prhs);
      new_node();
      switch(op) {
      case 0x126:
        dst_node[3] = 0x25;
        break;
      case 0x129:
        dst_node[3] = 0x134;
        break;
      case 0x12a:
        dst_node[3] = 0x135;
        break;
      case 299:
        dst_node[3] = 0x26;
        break;
      case 300:
        dst_node[3] = 0x5e;
        break;
      case 0x12d:
        dst_node[3] = 0x7c;
      }
      uVar2 = *(undefined4 *)plhs;
      dst_node[1] = 0;
      *dst_node = uVar2;
      dst_node[2] = *(undefined4 *)prhs;
      dst_node[5] = 0;
      copy_node_type(dst_node,*(void **)plhs);
      make_cast_node(*(int *)(*(int *)((int)src_node + 0x10) + 0x20),dst_node);
      copy_node_type(result_node,src_node);
      *(undefined4 *)((int)result_node + 0xc) = 0x3d;
      *(void **)plhs = src_node;
      *(undefined4 *)prhs = extraout_EAX;
      return 1;
    }
  }
  else {
    cdb_error(s_left_side_is_not_an_lvalue_in_as_004d4714);
  }
  return 0;
}


/* ==== eval_add_assign @ 004774e0 ==== */

int __cdecl eval_add_assign(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  void *extraout_EAX;
  undefined4 *dst_node;
  void *extraout_EAX_00;
  undefined4 *dst_node_00;
  undefined4 *extraout_EAX_01;
  undefined4 *puVar4;
  void *pvVar5;
  
  pvVar5 = *(void **)plhs;
  if (*(short *)(*(int *)((int)pvVar5 + 0x10) + 0x3c) == 1) {
    uVar1 = *(uint *)(*(int *)((int)pvVar5 + 0x10) + 0x20);
    if ((uVar1 & 0x30) != 0x30) {
      if ((((((((uVar1 == 2) || (uVar1 == 3)) || (uVar1 == 4)) || ((uVar1 == 0xb || (uVar1 == 10))))
            || ((uVar1 == 5 || ((uVar1 == 0xc || (uVar1 == 0xd)))))) ||
           (((uVar1 == 0xe || (((uVar1 == 0xf || (uVar1 == 6)) || (uVar1 == 7)))) ||
            (((uVar1 == 0x10000 || (uVar1 == 0x10001)) ||
             ((uVar1 == 0x10003 || ((uVar1 == 0x10002 || (uVar1 == 0x10004)))))))))) ||
          (uVar1 == 0x10005)) &&
         ((((((iVar2 = *(int *)(*(int *)(*(int *)prhs + 0x10) + 0x20), iVar2 == 2 || (iVar2 == 3))
             || (iVar2 == 4)) || ((iVar2 == 0xb || (iVar2 == 10)))) ||
           (((iVar2 == 5 || ((iVar2 == 0xc || (iVar2 == 0xd)))) || (iVar2 == 0xe)))) ||
          ((((((iVar2 == 0xf || (iVar2 == 6)) || (iVar2 == 7)) ||
             ((iVar2 == 0x10000 || (iVar2 == 0x10001)))) || (iVar2 == 0x10003)) ||
           (((iVar2 == 0x10002 || (iVar2 == 0x10004)) || (iVar2 == 0x10005)))))))) {
        if (do_eval != 0) {
          return 0;
        }
        clone_tree(pvVar5);
        usual_arith_conv(plhs,prhs);
        new_node();
        dst_node_00[3] = 0x2b;
        *dst_node_00 = *(undefined4 *)plhs;
        dst_node_00[1] = 0;
        uVar3 = *(undefined4 *)prhs;
        dst_node_00[5] = 0;
        dst_node_00[2] = uVar3;
        copy_node_type(dst_node_00,*(void **)plhs);
        make_cast_node(*(int *)(*(int *)((int)extraout_EAX_00 + 0x10) + 0x20),dst_node_00);
        puVar4 = extraout_EAX_01;
        pvVar5 = extraout_EAX_00;
      }
      else {
        iVar2 = *(int *)(*(int *)(*(int *)prhs + 0x10) + 0x20);
        if (((((iVar2 != 2) && (iVar2 != 3)) && (iVar2 != 4)) &&
            (((iVar2 != 0xb && (iVar2 != 10)) &&
             ((iVar2 != 5 && ((iVar2 != 0xc && (iVar2 != 0xd)))))))) &&
           ((iVar2 != 0xe && (iVar2 != 0xf)))) {
          cdb_error(s_operands_of____invalid_004d4a14);
          return 0;
        }
        if ((uVar1 & 0x30) != 0x10) {
          cdb_error(s_left_operand_of____is_not_arithm_004d49dc);
          return 0;
        }
        if ((uVar1 >> 2 & 0x3ffebff0 | uVar1 & 0x1000f) == 1) {
          cdb_error(s_pointer_arithmetic_with_void_poi_004d43b0);
          return 0;
        }
        if (do_eval != 0) {
          return 0;
        }
        clone_tree(pvVar5);
        new_node();
        dst_node[3] = 0x2b;
        *dst_node = *(undefined4 *)plhs;
        dst_node[1] = 0;
        uVar3 = *(undefined4 *)prhs;
        dst_node[5] = 0;
        dst_node[2] = uVar3;
        copy_node_type(dst_node,*(void **)plhs);
        puVar4 = dst_node;
        pvVar5 = extraout_EAX;
      }
      copy_node_type(result_node,pvVar5);
      *(undefined4 *)((int)result_node + 0xc) = 0x3d;
      *(void **)plhs = pvVar5;
      *(undefined4 **)prhs = puVar4;
      return 1;
    }
  }
  cdb_error(s_left_side_is_not_an_lvalue_in_as_004d4714);
  return 0;
}


/* ==== eval_sub_assign @ 004777b0 ==== */

int __cdecl eval_sub_assign(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  void *node;
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  void *src_node;
  undefined4 *dst_node;
  void *src_node_00;
  undefined4 *dst_node_00;
  undefined4 extraout_EAX;
  
  node = *(void **)plhs;
  if (*(short *)(*(int *)((int)node + 0x10) + 0x3c) == 1) {
    uVar1 = *(uint *)(*(int *)((int)node + 0x10) + 0x20);
    if ((uVar1 & 0x30) != 0x30) {
      if ((((((((uVar1 == 2) || (uVar1 == 3)) || (uVar1 == 4)) || ((uVar1 == 0xb || (uVar1 == 10))))
            || ((uVar1 == 5 || ((uVar1 == 0xc || (uVar1 == 0xd)))))) ||
           (((uVar1 == 0xe || (((uVar1 == 0xf || (uVar1 == 6)) || (uVar1 == 7)))) ||
            (((uVar1 == 0x10000 || (uVar1 == 0x10001)) ||
             ((uVar1 == 0x10003 || ((uVar1 == 0x10002 || (uVar1 == 0x10004)))))))))) ||
          (uVar1 == 0x10005)) &&
         ((((((iVar2 = *(int *)(*(int *)(*(int *)prhs + 0x10) + 0x20), iVar2 == 2 || (iVar2 == 3))
             || (iVar2 == 4)) || ((iVar2 == 0xb || (iVar2 == 10)))) ||
           (((iVar2 == 5 || ((iVar2 == 0xc || (iVar2 == 0xd)))) || (iVar2 == 0xe)))) ||
          ((((((iVar2 == 0xf || (iVar2 == 6)) || (iVar2 == 7)) ||
             ((iVar2 == 0x10000 || (iVar2 == 0x10001)))) || (iVar2 == 0x10003)) ||
           (((iVar2 == 0x10002 || (iVar2 == 0x10004)) || (iVar2 == 0x10005)))))))) {
        if (do_eval != 0) {
          return 0;
        }
        clone_tree(node);
        usual_arith_conv(plhs,prhs);
        new_node();
        dst_node_00[3] = 0x2d;
        *dst_node_00 = *(undefined4 *)plhs;
        dst_node_00[1] = 0;
        uVar3 = *(undefined4 *)prhs;
        dst_node_00[5] = 0;
        dst_node_00[2] = uVar3;
        copy_node_type(dst_node_00,*(void **)plhs);
        make_cast_node(*(int *)(*(int *)((int)src_node_00 + 0x10) + 0x20),dst_node_00);
        copy_node_type(result_node,src_node_00);
        *(undefined4 *)((int)result_node + 0xc) = 0x3d;
        *(void **)plhs = src_node_00;
        *(undefined4 *)prhs = extraout_EAX;
        return 1;
      }
      if ((uVar1 & 0x30) != 0x10) {
        cdb_error(s_operands_of_binary____invalid_004d4a2c);
        return 0;
      }
      iVar2 = *(int *)(*(int *)(*(int *)prhs + 0x10) + 0x20);
      if (((((iVar2 != 2) && (iVar2 != 3)) && (iVar2 != 4)) &&
          (((iVar2 != 0xb && (iVar2 != 10)) && ((iVar2 != 5 && ((iVar2 != 0xc && (iVar2 != 0xd))))))
          )) && ((iVar2 != 0xe && (iVar2 != 0xf)))) {
        cdb_error(s_right_operand_of_binary____is_no_004d4a4c);
        return 0;
      }
      if (do_eval != 0) {
        return 0;
      }
      clone_tree(node);
      new_node();
      dst_node[3] = 0x2d;
      *dst_node = *(undefined4 *)plhs;
      dst_node[1] = 0;
      uVar3 = *(undefined4 *)prhs;
      dst_node[5] = 0;
      dst_node[2] = uVar3;
      copy_node_type(dst_node,*(void **)plhs);
      copy_node_type(result_node,src_node);
      *(undefined4 *)((int)result_node + 0xc) = 0x3d;
      *(void **)plhs = src_node;
      *(undefined4 **)prhs = dst_node;
      return 1;
    }
  }
  cdb_error(s_left_side_is_not_an_lvalue_in_as_004d4714);
  return 0;
}


/* ==== eval_comma @ 00477a80 ==== */

int __cdecl eval_comma(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  if (do_eval == 0) {
    copy_node_type(result_node,*(void **)prhs);
    *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x24) =
         *(undefined4 *)(*(int *)(*(int *)prhs + 0x10) + 0x24);
    return 1;
  }
  iVar4 = cdb_load_value(*(void **)(*(int *)prhs + 0x10));
  if (iVar4 == 0) {
    return 0;
  }
  puVar1 = *(undefined4 **)(*(int *)prhs + 0x10);
  puVar2 = *(undefined4 **)((int)result_node + 0x10);
  *puVar2 = *puVar1;
  puVar2[1] = puVar1[1];
  *(undefined4 *)(*(int *)((int)result_node + 0x10) + 8) =
       *(undefined4 *)(*(int *)(*(int *)prhs + 0x10) + 8);
  iVar4 = *(int *)(*(int *)prhs + 0x10);
  iVar3 = *(int *)((int)result_node + 0x10);
  *(undefined4 *)(iVar3 + 0xc) = *(undefined4 *)(iVar4 + 0xc);
  *(undefined4 *)(iVar3 + 0x10) = *(undefined4 *)(iVar4 + 0x10);
  *(undefined4 *)(iVar3 + 0x14) = *(undefined4 *)(iVar4 + 0x14);
  iVar4 = *(int *)((int)result_node + 0x10);
  iVar3 = *(int *)(*(int *)prhs + 0x10);
  *(undefined4 *)(iVar4 + 0x18) = *(undefined4 *)(iVar3 + 0x18);
  *(undefined4 *)(iVar4 + 0x1c) = *(undefined4 *)(iVar3 + 0x1c);
  return 1;
}


/* ==== eval_hash @ 00477b30 ==== */

int __cdecl eval_hash(void *plhs,void *prhs,int op,void *result_node,int do_eval)

{
  void *v;
  uint uVar1;
  int iVar2;
  
  v = *(void **)((int)*(void **)plhs + 0x10);
  uVar1 = *(uint *)((int)v + 0x20);
  if ((((byte)uVar1 & 0x30) != 0x10) ||
     ((((((iVar2 = *(int *)(*(int *)(*(int *)prhs + 0x10) + 0x20), iVar2 != 2 && (iVar2 != 3)) &&
         (iVar2 != 4)) && ((iVar2 != 0xb && (iVar2 != 10)))) &&
       ((iVar2 != 5 && ((iVar2 != 0xc && (iVar2 != 0xd)))))) && ((iVar2 != 0xe && (iVar2 != 0xf)))))
     ) {
    cdb_error(s_left_operand_of___is_not_a_point_004d4a8c);
    return 0;
  }
  if ((uVar1 >> 2 & 0x3ffebff0 | uVar1 & 0x1000f) == 1) {
    cdb_error(s_the___operator_can_not_be_used_o_004d4ab0);
    return 0;
  }
  if (do_eval != 0) {
    if ((*(short *)((int)v + 0x3c) == 1) && (iVar2 = cdb_load_value(v), iVar2 == 0)) {
      return 0;
    }
    *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x18) =
         *(undefined4 *)(*(int *)(*(int *)plhs + 0x10) + 0xc);
    *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x1c) =
         *(undefined4 *)(*(int *)(*(int *)plhs + 0x10) + 0x10);
    return 1;
  }
  copy_node_type(result_node,*(void **)plhs);
  *(uint *)(*(int *)((int)result_node + 0x10) + 0x20) =
       *(uint *)(*(int *)(*(int *)plhs + 0x10) + 0x20) | 0x30;
  *(undefined2 *)(*(int *)((int)result_node + 0x10) + 0x3c) = 1;
  *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x24) = 2;
  *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x2c) =
       *(undefined4 *)(*(int *)(*(int *)prhs + 0x10) + 0xc);
  return 1;
}


/* ==== eval_incdec @ 00477c60 ==== */

int __cdecl eval_incdec(void *pchild,int op,void *result_node,int do_eval)

{
  void *value;
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  value = *(void **)((int)*(void **)pchild + 0x10);
  if (*(short *)((int)value + 0x3c) == 1) {
    uVar1 = *(uint *)((int)value + 0x20);
    if ((uVar1 & 0x30) != 0x30) {
      if (((((((uVar1 != 2) && (uVar1 != 3)) && (uVar1 != 4)) && ((uVar1 != 0xb && (uVar1 != 10))))
           && ((uVar1 != 5 && ((uVar1 != 0xc && (uVar1 != 0xd)))))) && (uVar1 != 0xe)) &&
         (((((uVar1 != 0xf && (uVar1 != 6)) && (uVar1 != 7)) &&
           (((uVar1 != 0x10000 && (uVar1 != 0x10001)) &&
            ((uVar1 != 0x10003 && ((uVar1 != 0x10002 && (uVar1 != 0x10004)))))))) &&
          ((uVar1 != 0x10005 && ((uVar1 & 0x30) != 0x10)))))) {
        switch(op) {
        case 0x140:
          cdb_error(s_operand_to_post_increment_not_sc_004d4bd8);
          return 0;
        case 0x141:
          cdb_error(s_operand_to_pre_increment_not_sca_004d4c04);
          return 0;
        case 0x142:
          cdb_error(s_operand_to_post_decrement_not_sc_004d4b80);
          return 0;
        case 0x143:
          cdb_error(s_operand_to_pre_decrement_not_sca_004d4bac);
          return 0;
        default:
          cdb_internal_error(0x4d413c,0x218e);
          return 0;
        }
      }
      if (do_eval == 0) {
        copy_node_type(result_node,*(void **)pchild);
        return 1;
      }
      switch(op) {
      case 0x140:
        goto switchD_00477dea_caseD_140;
      case 0x141:
        iVar5 = value_inc(value);
        iVar6 = cdb_load_value(*(void **)(*(int *)pchild + 0x10));
        if (iVar6 != 0) {
          puVar2 = *(undefined4 **)(*(int *)pchild + 0x10);
          puVar3 = *(undefined4 **)((int)result_node + 0x10);
          *puVar3 = *puVar2;
          puVar3[1] = puVar2[1];
          *(undefined4 *)(*(int *)((int)result_node + 0x10) + 8) =
               *(undefined4 *)(*(int *)(*(int *)pchild + 0x10) + 8);
          iVar6 = *(int *)(*(int *)pchild + 0x10);
          iVar4 = *(int *)((int)result_node + 0x10);
          *(undefined4 *)(iVar4 + 0xc) = *(undefined4 *)(iVar6 + 0xc);
          *(undefined4 *)(iVar4 + 0x10) = *(undefined4 *)(iVar6 + 0x10);
          *(undefined4 *)(iVar4 + 0x14) = *(undefined4 *)(iVar6 + 0x14);
          return iVar5;
        }
        return 0;
      case 0x142:
        iVar5 = cdb_load_value(value);
        if (iVar5 != 0) {
          puVar2 = *(undefined4 **)(*(int *)pchild + 0x10);
          puVar3 = *(undefined4 **)((int)result_node + 0x10);
          *puVar3 = *puVar2;
          puVar3[1] = puVar2[1];
          *(undefined4 *)(*(int *)((int)result_node + 0x10) + 8) =
               *(undefined4 *)(*(int *)(*(int *)pchild + 0x10) + 8);
          iVar5 = *(int *)((int)result_node + 0x10);
          iVar6 = *(int *)(*(int *)pchild + 0x10);
          *(undefined4 *)(iVar5 + 0xc) = *(undefined4 *)(iVar6 + 0xc);
          *(undefined4 *)(iVar5 + 0x10) = *(undefined4 *)(iVar6 + 0x10);
          *(undefined4 *)(iVar5 + 0x14) = *(undefined4 *)(iVar6 + 0x14);
          iVar5 = value_dec(*(void **)(*(int *)pchild + 0x10));
          return iVar5;
        }
        return 0;
      case 0x143:
        iVar5 = value_dec(value);
        iVar6 = cdb_load_value(*(void **)(*(int *)pchild + 0x10));
        if (iVar6 != 0) {
          puVar2 = *(undefined4 **)(*(int *)pchild + 0x10);
          puVar3 = *(undefined4 **)((int)result_node + 0x10);
          *puVar3 = *puVar2;
          puVar3[1] = puVar2[1];
          *(undefined4 *)(*(int *)((int)result_node + 0x10) + 8) =
               *(undefined4 *)(*(int *)(*(int *)pchild + 0x10) + 8);
          iVar6 = *(int *)((int)result_node + 0x10);
          iVar4 = *(int *)(*(int *)pchild + 0x10);
          *(undefined4 *)(iVar6 + 0xc) = *(undefined4 *)(iVar4 + 0xc);
          *(undefined4 *)(iVar6 + 0x10) = *(undefined4 *)(iVar4 + 0x10);
          *(undefined4 *)(iVar6 + 0x14) = *(undefined4 *)(iVar4 + 0x14);
          return iVar5;
        }
        return 0;
      default:
        cdb_internal_error(0x4d413c,0x2174);
        return 0;
      }
    }
  }
  switch(op) {
  case 0x140:
    cdb_error(s_operand_to_post_increment_not_an_004d4b30);
    return 0;
  case 0x141:
    cdb_error(s_operand_to_pre_increment_not_an_l_004d4b58);
    return 0;
  case 0x142:
    cdb_error(s_operand_to_post_decrement_not_an_004d4ae0);
    return 0;
  case 0x143:
    cdb_error(s_operand_to_pre_decrement_not_an_l_004d4b08);
    return 0;
  default:
    cdb_internal_error(0x4d413c,0x21a7);
    return 0;
  }
switchD_00477dea_caseD_140:
  iVar5 = cdb_load_value(value);
  if (iVar5 != 0) {
    puVar2 = *(undefined4 **)(*(int *)pchild + 0x10);
    puVar3 = *(undefined4 **)((int)result_node + 0x10);
    *puVar3 = *puVar2;
    puVar3[1] = puVar2[1];
    *(undefined4 *)(*(int *)((int)result_node + 0x10) + 8) =
         *(undefined4 *)(*(int *)(*(int *)pchild + 0x10) + 8);
    iVar5 = *(int *)(*(int *)pchild + 0x10);
    iVar6 = *(int *)((int)result_node + 0x10);
    *(undefined4 *)(iVar6 + 0xc) = *(undefined4 *)(iVar5 + 0xc);
    *(undefined4 *)(iVar6 + 0x10) = *(undefined4 *)(iVar5 + 0x10);
    *(undefined4 *)(iVar6 + 0x14) = *(undefined4 *)(iVar5 + 0x14);
    iVar5 = value_inc(*(void **)(*(int *)pchild + 0x10));
    return iVar5;
  }
  return 0;
}


/* ==== value_inc @ 00478060 ==== */

int __cdecl value_inc(void *value)

{
  int iVar1;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  IMAGE_DOS_HEADER *local_70;
  undefined4 local_6c;
  uint local_60;
  undefined2 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  uint local_20;
  undefined2 local_4;
  
  iVar1 = cdb_load_value(value);
  if (iVar1 == 0) {
    return 0;
  }
  local_20 = *(uint *)((int)value + 0x20);
  local_60 = local_20;
  if ((local_20 & 0x30) == 0x10) {
    local_60 = 4;
  }
  local_44 = 0;
  local_4 = 0;
  if ((local_20 == 6) || (local_20 == 7)) {
    local_74 = 0x2000;
    local_70 = &IMAGE_DOS_HEADER_00400000;
    local_78 = 0x3f800000;
    local_80 = 0;
    local_7c = 0x3ff00000;
  }
  else {
    local_74 = 1;
    local_70 = (IMAGE_DOS_HEADER *)0x0;
  }
  local_6c = 0;
  if ((local_20 & 0x30) == 0x10) {
    ptr_add_values(value,&local_80,&local_40);
  }
  else {
    add_values(value,&local_80,&local_40);
  }
  *(undefined4 *)((int)value + 0xc) = local_34;
  if (((byte)*(undefined4 *)((int)value + 0x20) & 0x30) != 0x10) {
    *(undefined4 *)((int)value + 0x10) = local_30;
    *(undefined4 *)((int)value + 0x14) = local_2c;
  }
  *(undefined4 *)value = local_40;
  *(undefined4 *)((int)value + 8) = local_38;
  *(undefined4 *)((int)value + 4) = local_3c;
  iVar1 = cdb_store_value(value);
  return (uint)(iVar1 != 0);
}


/* ==== value_dec @ 00478190 ==== */

int __cdecl value_dec(void *value)

{
  int iVar1;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  IMAGE_DOS_HEADER *local_70;
  undefined4 local_6c;
  uint local_60;
  undefined2 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  uint local_20;
  undefined2 local_4;
  
  iVar1 = cdb_load_value(value);
  if (iVar1 == 0) {
    return 0;
  }
  local_20 = *(uint *)((int)value + 0x20);
  local_60 = local_20;
  if ((local_20 & 0x30) == 0x10) {
    local_60 = 4;
  }
  local_44 = 0;
  local_4 = 0;
  if ((local_20 == 6) || (local_20 == 7)) {
    local_74 = 0x2000;
    local_70 = &IMAGE_DOS_HEADER_00400000;
    local_78 = 0x3f800000;
    local_80 = 0;
    local_7c = 0x3ff00000;
  }
  else {
    local_74 = 1;
    local_70 = (IMAGE_DOS_HEADER *)0x0;
  }
  local_6c = 0;
  if ((local_20 & 0x30) == 0x10) {
    ptr_sub_int_values(value,&local_80,&local_40);
  }
  else {
    sub_values(value,&local_80,&local_40);
  }
  *(undefined4 *)((int)value + 0xc) = local_34;
  if (((byte)*(undefined4 *)((int)value + 0x20) & 0x30) != 0x10) {
    *(undefined4 *)((int)value + 0x10) = local_30;
    *(undefined4 *)((int)value + 0x14) = local_2c;
  }
  *(undefined4 *)value = local_40;
  *(undefined4 *)((int)value + 8) = local_38;
  *(undefined4 *)((int)value + 4) = local_3c;
  iVar1 = cdb_store_value(value);
  return (uint)(iVar1 != 0);
}


/* ==== eval_addr_of @ 004782c0 ==== */

int __cdecl eval_addr_of(void *pchild,int op,void *result_node,int do_eval)

{
  void *value;
  uint uVar1;
  int iVar2;
  
  value = *(void **)((int)*(void **)pchild + 0x10);
  if ((((byte)*(undefined4 *)((int)value + 0x20) & 0x30) != 0x20) &&
     ((((*(short *)((int)value + 0x3c) != 1 || (iVar2 = *(int *)((int)value + 0x24), iVar2 == 0x12))
       || (iVar2 == 4)) || ((iVar2 == 0x11 || (iVar2 == -0x80000000)))))) {
    if ((*(int *)((int)value + 0x24) != 4) && (*(int *)((int)value + 0x24) != 0x11)) {
      cdb_error(s_operand_of_unary___invalid_004d4c68);
      return 0;
    }
    cdb_error(s_operand_of_unary___invalid_since_004d4c30);
    return 0;
  }
  if (do_eval == 0) {
    copy_node_type(result_node,*(void **)pchild);
    uVar1 = *(uint *)(*(int *)((int)result_node + 0x10) + 0x20);
    *(uint *)(*(int *)((int)result_node + 0x10) + 0x20) =
         uVar1 & 0x1000f | (uVar1 & 0xfffefff4 | 4) << 2;
    return 1;
  }
  iVar2 = addr_of_value(value,*(void **)((int)result_node + 0x10));
  return iVar2;
}


/* ==== addr_of_value @ 00478380 ==== */

int __cdecl addr_of_value(void *value,void *out)

{
  int iVar1;
  ulong local_4;
  
  iVar1 = *(int *)((int)value + 0x24);
  if ((iVar1 == 2) || (iVar1 == 3)) {
    *(undefined4 *)((int)out + 0x10) = *(undefined4 *)((int)value + 0x1c);
    *(undefined4 *)((int)out + 0xc) = *(undefined4 *)((int)value + 0x18);
    return 1;
  }
  if ((iVar1 != 1) && (iVar1 != 9)) {
    cdb_internal_error(0x4d413c,0x7cd);
    return 0;
  }
  iVar1 = cdb_frame_slot(*(int *)((int)value + 0x1c),*(int *)((int)value + 0x18),(int *)&value,
                         &local_4);
  if (iVar1 == 0) {
    return 0;
  }
  *(void **)((int)out + 0x10) = value;
  *(ulong *)((int)out + 0xc) = local_4;
  return 1;
}


/* ==== eval_deref @ 00478410 ==== */

int __cdecl eval_deref(void *pchild,int op,void *result_node,int do_eval)

{
  void *v;
  uint uVar1;
  int iVar2;
  
  v = *(void **)((int)*(void **)pchild + 0x10);
  uVar1 = *(uint *)((int)v + 0x20);
  if ((((byte)uVar1 & 0x30) != 0x10) || ((uVar1 >> 2 & 0x3ffebff0 | uVar1 & 0x1000f) == 1)) {
    cdb_error(s_operand_of_unary___invalid_004d4c84);
    return 0;
  }
  if (do_eval == 0) {
    copy_node_type(result_node,*(void **)pchild);
    uVar1 = *(uint *)(*(int *)(*(int *)pchild + 0x10) + 0x20);
    *(uint *)(*(int *)((int)result_node + 0x10) + 0x20) = uVar1 >> 2 & 0x3ffebff0 | uVar1 & 0x1000f;
    *(undefined2 *)(*(int *)((int)result_node + 0x10) + 0x3c) = 1;
    *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x24) = 2;
    return 1;
  }
  if ((*(short *)((int)v + 0x3c) == 1) && (iVar2 = cdb_load_value(v), iVar2 == 0)) {
    return 0;
  }
  *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x18) =
       *(undefined4 *)(*(int *)(*(int *)pchild + 0x10) + 0xc);
  *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x1c) =
       *(undefined4 *)(*(int *)(*(int *)pchild + 0x10) + 0x10);
  return 1;
}


/* ==== eval_uplus @ 004784f0 ==== */

int __cdecl eval_uplus(void *pchild,int op,void *result_node,int do_eval)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)((int)*(void **)(*(int *)pchild + 0x10) + 0x20);
  if (((((((iVar4 != 2) && (iVar4 != 3)) && (iVar4 != 4)) && ((iVar4 != 0xb && (iVar4 != 10)))) &&
       ((iVar4 != 5 && ((iVar4 != 0xc && (iVar4 != 0xd)))))) && (iVar4 != 0xe)) &&
     (((((iVar4 != 0xf && (iVar4 != 6)) && (iVar4 != 7)) &&
       (((iVar4 != 0x10000 && (iVar4 != 0x10001)) &&
        ((iVar4 != 0x10003 && ((iVar4 != 0x10002 && (iVar4 != 0x10004)))))))) && (iVar4 != 0x10005))
     )) {
    cdb_error(s_operand_of_unary___invalid_004d4ca0);
    return 0;
  }
  if (do_eval == 0) {
    integral_promote(pchild);
    copy_node_type(result_node,*(void **)pchild);
    return 1;
  }
  iVar4 = cdb_load_value(*(void **)(*(int *)pchild + 0x10));
  if (iVar4 == 0) {
    return 0;
  }
  puVar1 = *(undefined4 **)(*(int *)pchild + 0x10);
  puVar2 = *(undefined4 **)((int)result_node + 0x10);
  *puVar2 = *puVar1;
  puVar2[1] = puVar1[1];
  *(undefined4 *)(*(int *)((int)result_node + 0x10) + 8) =
       *(undefined4 *)(*(int *)(*(int *)pchild + 0x10) + 8);
  iVar4 = *(int *)((int)result_node + 0x10);
  iVar3 = *(int *)(*(int *)pchild + 0x10);
  *(undefined4 *)(iVar4 + 0xc) = *(undefined4 *)(iVar3 + 0xc);
  *(undefined4 *)(iVar4 + 0x10) = *(undefined4 *)(iVar3 + 0x10);
  *(undefined4 *)(iVar4 + 0x14) = *(undefined4 *)(iVar3 + 0x14);
  return 1;
}


/* ==== eval_uminus @ 00478600 ==== */

int __cdecl eval_uminus(void *pchild,int op,void *result_node,int do_eval)

{
  int iVar1;
  
  iVar1 = *(int *)((int)*(void **)(*(int *)pchild + 0x10) + 0x20);
  if (((((((iVar1 != 2) && (iVar1 != 3)) && (iVar1 != 4)) && ((iVar1 != 0xb && (iVar1 != 10)))) &&
       ((iVar1 != 5 && ((iVar1 != 0xc && (iVar1 != 0xd)))))) && (iVar1 != 0xe)) &&
     (((((iVar1 != 0xf && (iVar1 != 6)) && (iVar1 != 7)) &&
       (((iVar1 != 0x10000 && (iVar1 != 0x10001)) &&
        ((iVar1 != 0x10003 && ((iVar1 != 0x10002 && (iVar1 != 0x10004)))))))) && (iVar1 != 0x10005))
     )) {
    cdb_error(s_operand_of_unary___invalid_004d4cbc);
    return 0;
  }
  if (do_eval == 0) {
    integral_promote(pchild);
    copy_node_type(result_node,*(void **)pchild);
    return 1;
  }
  iVar1 = value_neg(*(void **)(*(int *)pchild + 0x10),*(void **)((int)result_node + 0x10));
  return iVar1;
}


/* ==== eval_compl @ 004786c0 ==== */

int __cdecl eval_compl(void *pchild,int op,void *result_node,int do_eval)

{
  int iVar1;
  
  iVar1 = *(int *)((int)*(void **)(*(int *)pchild + 0x10) + 0x20);
  if ((((((iVar1 != 2) && (iVar1 != 3)) && (iVar1 != 4)) && ((iVar1 != 0xb && (iVar1 != 10)))) &&
      ((iVar1 != 5 && ((iVar1 != 0xc && (iVar1 != 0xd)))))) && ((iVar1 != 0xe && (iVar1 != 0xf)))) {
    cdb_error(s_operand_of_unary___invalid_004d4cd8);
    return 0;
  }
  if (do_eval == 0) {
    integral_promote(pchild);
    copy_node_type(result_node,*(void **)pchild);
    return 1;
  }
  iVar1 = compl_value(*(void **)(*(int *)pchild + 0x10),*(void **)((int)result_node + 0x10));
  return iVar1;
}


/* ==== compl_value @ 00478750 ==== */

int __cdecl compl_value(void *value,void *out)

{
  int iVar1;
  
  iVar1 = cdb_load_value(value);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = *(int *)((int)value + 0x20);
  if ((((iVar1 == 4) || (iVar1 == 0xb)) || (iVar1 == 10)) || (iVar1 == 0xe)) {
    *(uint *)((int)out + 0xc) = ~*(uint *)((int)value + 0xc) & cdb_word_mask;
    *(undefined4 *)((int)out + 0x10) = 0;
    return 1;
  }
  if ((iVar1 == 5) || (iVar1 == 0xf)) {
    *(uint *)((int)out + 0xc) = ~*(uint *)((int)value + 0xc) & cdb_word_mask;
    *(uint *)((int)out + 0x10) = ~*(uint *)((int)value + 0x10) & cdb_word_mask;
    return 1;
  }
  if ((iVar1 != 0x10000) && (iVar1 != 0x10001)) {
    if ((iVar1 == 0x10002) || (iVar1 == 0x10003)) {
      *(uint *)((int)out + 0xc) = ~*(uint *)((int)value + 0xc) & cdb_word_mask;
      *(uint *)((int)out + 0x10) = ~*(uint *)((int)value + 0x10) & cdb_word_mask;
      return 1;
    }
    if (iVar1 == 0x10005) {
      *(uint *)((int)out + 0xc) = ~*(uint *)((int)value + 0xc) & cdb_word_mask;
      *(uint *)((int)out + 0x10) = ~*(uint *)((int)value + 0x10) & cdb_word_mask;
      *(uint *)((int)out + 0x14) = ~*(uint *)((int)value + 0x14) & cdb_ext_mask;
      return 1;
    }
    if (iVar1 == 0x10004) {
      *(uint *)((int)out + 0xc) = ~*(uint *)((int)value + 0xc) & cdb_word_mask;
      *(uint *)((int)out + 0x10) = ~*(uint *)((int)value + 0x10) & cdb_ext_mask;
      return 1;
    }
    cdb_internal_error(0x4d413c,0xc73);
    return 0;
  }
  *(uint *)((int)out + 0xc) = ~*(uint *)((int)value + 0xc) & cdb_word_mask;
  *(undefined4 *)((int)out + 0x10) = 0;
  return 1;
}


/* ==== eval_lognot @ 004788f0 ==== */

int __cdecl eval_lognot(void *pchild,int op,void *result_node,int do_eval)

{
  int iVar1;
  
  iVar1 = *(int *)((int)*(void **)(*(int *)pchild + 0x10) + 0x20);
  if (((((((iVar1 != 2) && (iVar1 != 3)) && (iVar1 != 4)) && ((iVar1 != 0xb && (iVar1 != 10)))) &&
       ((iVar1 != 5 && ((iVar1 != 0xc && (iVar1 != 0xd)))))) && (iVar1 != 0xe)) &&
     (((((iVar1 != 0xf && (iVar1 != 6)) && (iVar1 != 7)) &&
       (((iVar1 != 0x10000 && (iVar1 != 0x10001)) &&
        ((iVar1 != 0x10003 && ((iVar1 != 0x10002 && (iVar1 != 0x10004)))))))) &&
      ((iVar1 != 0x10005 && (((byte)iVar1 & 0x30) != 0x10)))))) {
    cdb_error(s_operand_of_unary___invalid_004d4cf4);
    return 0;
  }
  if (do_eval == 0) {
    integral_promote(pchild);
    copy_node_type(result_node,*(void **)pchild);
    *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x20) = 4;
    return 1;
  }
  iVar1 = lognot_value(*(void **)(*(int *)pchild + 0x10),*(void **)((int)result_node + 0x10));
  return iVar1;
}


/* ==== lognot_value @ 004789c0 ==== */

int __cdecl lognot_value(void *value,void *out)

{
  int iVar1;
  
  iVar1 = cdb_load_value(value);
  if (iVar1 == 0) {
    return 0;
  }
  *(undefined4 *)((int)out + 0x10) = 0;
  iVar1 = *(int *)((int)value + 0x20);
  if ((((((byte)iVar1 & 0x30) == 0x10) || (iVar1 == 4)) || (iVar1 == 0xb)) ||
     ((iVar1 == 10 || (iVar1 == 0xe)))) {
    *(uint *)((int)out + 0xc) = (uint)(*(int *)((int)value + 0xc) == 0);
    return 1;
  }
  if ((iVar1 != 5) && (iVar1 != 0xf)) {
    if ((iVar1 == 0x10000) || (iVar1 == 0x10001)) {
      *(uint *)((int)out + 0xc) = (uint)(*(int *)((int)value + 0xc) == 0);
      return 1;
    }
    if ((iVar1 != 0x10002) && (iVar1 != 0x10003)) {
      if (iVar1 == 0x10005) {
        if (((*(int *)((int)value + 0xc) == 0) && (*(int *)((int)value + 0x10) == 0)) &&
           (*(int *)((int)value + 0x14) == 0)) {
          *(undefined4 *)((int)out + 0xc) = 1;
          return 1;
        }
      }
      else if (iVar1 == 0x10004) {
        if ((*(int *)((int)value + 0xc) == 0) && (*(int *)((int)value + 0x10) == 0)) {
          *(undefined4 *)((int)out + 0xc) = 1;
          return 1;
        }
      }
      else {
        if ((iVar1 != 6) && (iVar1 != 7)) {
          cdb_internal_error(0x4d413c,0xcbf);
          return 0;
        }
        if ((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) {
          if ((*(int *)((int)value + 0xc) == 0) && (*(int *)((int)value + 0x10) == 0)) {
            *(undefined4 *)((int)out + 0xc) = 1;
            return 1;
          }
        }
        else if ((((iVar1 == 6) || (cdb_arch == 0x2c7)) || (cdb_arch == 0x2c9)) ||
                ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))) {
          if (*(float *)((int)value + 8) == 0.0) {
            *(undefined4 *)((int)out + 0xc) = 1;
            return 1;
          }
        }
        else if (*(double *)value == 0.0) {
          *(undefined4 *)((int)out + 0xc) = 1;
          return 1;
        }
      }
      goto LAB_00478b7d;
    }
  }
  if ((*(int *)((int)value + 0xc) == 0) && (*(int *)((int)value + 0x10) == 0)) {
    *(undefined4 *)((int)out + 0xc) = 1;
    return 1;
  }
LAB_00478b7d:
  *(undefined4 *)((int)out + 0xc) = 0;
  return 1;
}


/* ==== eval_sizeof @ 00478ba0 ==== */

int __cdecl eval_sizeof(void *pchild,int op,void *result_node,int do_eval)

{
  void *value;
  int iVar1;
  
  value = *(void **)((int)*(void **)pchild + 0x10);
  if (((((byte)*(int *)((int)value + 0x20) & 0x30) != 0x20) && (*(int *)((int)value + 0x20) != 1))
     && ((*(short *)((int)value + 0x3c) != 1 || (*(int *)((int)value + 0x24) != 0x12)))) {
    if (do_eval == 0) {
      copy_node_type(result_node,*(void **)pchild);
      *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x20) = 4;
      return 1;
    }
    iVar1 = type_size(value,*(void **)((int)result_node + 0x10));
    return iVar1;
  }
  cdb_error(s_operand_of_sizeof_invalid_004d4d10);
  return 0;
}


/* ==== eval_call @ 00478c20 ==== */

int __cdecl eval_call(void *pfunc,int op,void *result_node,int do_eval)

{
  void *func_node;
  uint uVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
  func_node = *(void **)pfunc;
  uVar1 = *(uint *)(*(int *)((int)func_node + 0x10) + 0x20);
  uVar3 = uVar1 & 0x30;
  if ((uVar3 != 0x20) && ((uVar3 != 0x10 || (((byte)uVar1 & 0xc0) != 0x80)))) {
    cdb_error(s_attempting_function_call_on_non__004d4d64);
    return 0;
  }
  if (do_eval != 0) {
    iVar4 = call_target_function(func_node,result_node);
    return iVar4;
  }
  piVar2 = *(int **)((int)func_node + 0x14);
  while( true ) {
    if (piVar2 == (int *)0x0) {
      copy_node_type(result_node,func_node);
      uVar1 = *(uint *)(*(int *)(*(int *)pfunc + 0x10) + 0x20);
      if (((byte)uVar1 & 0x30) == 0x20) {
        *(uint *)(*(int *)((int)result_node + 0x10) + 0x20) =
             uVar1 >> 2 & 0x3ffebff0 | uVar1 & 0x1000f;
      }
      else {
        *(uint *)(*(int *)((int)result_node + 0x10) + 0x20) =
             uVar1 >> 4 & 0xffeaff0 | uVar1 & 0x1000f;
        *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x2c) =
             *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x30);
        *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x30) =
             *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x34);
        *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x34) =
             *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x38);
        *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x38) = 1;
      }
      *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x2c) =
           *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x30);
      *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x30) =
           *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x34);
      *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x34) =
           *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x38);
      *(undefined4 *)(*(int *)((int)result_node + 0x10) + 0x38) = 1;
      return 1;
    }
    if (*(int *)(*(int *)(*piVar2 + 0x10) + 0x20) == 1) break;
    piVar2 = (int *)piVar2[1];
  }
  cdb_error(s_attempting_to_pass_void_value_to_004d4d2c);
  return 0;
}


/* ==== call_target_function @ 00478d50 ==== */

int __cdecl call_target_function(void *func_node,void *result_node)

{
  void *v;
  int iVar1;
  
  v = *(void **)((int)func_node + 0x10);
  if (((*(short *)((int)v + 0x3c) == 1) && (((byte)*(undefined4 *)((int)v + 0x20) & 0x30) != 0x20))
     && (iVar1 = cdb_load_value(v), iVar1 == 0)) {
    return 0;
  }
  if (cdb_arch == 0x2c7) {
    iVar1 = call_setup_56100(func_node,result_node);
    if (iVar1 == 0) {
      return 0;
    }
    goto LAB_00478e28;
  }
  if (cdb_arch == 0x2c9) {
    iVar1 = call_setup_56800(func_node,result_node);
    if (iVar1 == 0) {
      return 0;
    }
    goto LAB_00478e28;
  }
  if (cdb_arch == 0x2c5) {
LAB_00478dbc:
    if (((cdb_arch != 0x2c8) && (cdb_arch != 0x2cb)) && (cdb_arch != 0x2ca)) {
      iVar1 = call_setup_56000(func_node,result_node);
      if (iVar1 == 0) {
        return 0;
      }
      goto LAB_00478e28;
    }
  }
  else if (cdb_arch != 0x2c8) {
    if ((cdb_arch != 0x2cb) && (cdb_arch != 0x2ca)) {
      iVar1 = call_setup_96000(func_node,result_node);
      if (iVar1 == 0) {
        return 0;
      }
      goto LAB_00478e28;
    }
    goto LAB_00478dbc;
  }
  iVar1 = call_setup_56300(func_node,result_node);
  if (iVar1 == 0) {
    return 0;
  }
LAB_00478e28:
  call_setup_run();
  return 1;
}


/* ==== call_setup_run @ 00478e40 ==== */

void call_setup_run(void)

{
  *(undefined4 *)(cur_sim + 0x3c) = 0;
  *(undefined4 *)(cur_sim + 0x34) = 0x10;
  *(undefined4 *)(cur_sim + 0x180) = 0;
  *(int *)(cur_sim + 0x17c) = *(int *)(cur_dev + 0x1c) + 2;
  *(undefined4 *)(cur_sim + 0x2c) = 0;
  cdb_free_frames();
  periph_reset();
  *(undefined4 *)(cur_sim + 0x40) = 1;
  return;
}


/* ==== call_setup_56000 @ 00478ea0 ==== */

int __cdecl call_setup_56000(void *func_node,void *result_node)

{
  int iVar1;
  int iVar2;
  long lVar3;
  int iVar4;
  int local_9c;
  int local_98;
  long local_94;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  long local_80;
  undefined4 local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  undefined1 local_68 [20];
  int local_54;
  undefined1 local_40 [12];
  int local_34;
  undefined4 local_20;
  
  iVar4 = *(int *)(cur_dev + 4);
  iVar2 = cdb_default_space();
  if (iVar2 == 3) {
    iVar2 = 2;
  }
  lVar3 = periph_find_reg(iVar4,&DAT_004b2948,&local_8c,&local_80);
  if (lVar3 != 0) {
    lVar3 = periph_find_reg(iVar4,&DAT_004b2930,&local_90,&local_94);
    if (lVar3 != 0) {
      lVar3 = periph_find_reg(iVar4,&DAT_004b294c,&local_74,&local_6c);
      if (lVar3 != 0) {
        lVar3 = periph_find_reg(iVar4,&DAT_004a8a6c,&local_70,&local_78);
        if (lVar3 != 0) {
          lVar3 = periph_call(iVar4,local_8c,local_80,(long)&local_98);
          if (lVar3 == 0) {
            cdb_c_error(s_unable_to_read_register_r0_004d4e2c);
            return 0;
          }
          lVar3 = periph_call(iVar4,local_90,local_94,(long)&local_9c);
          iVar1 = local_9c;
          if (lVar3 == 0) {
            cdb_c_error(s_unable_to_read_register_r6_004d4e10);
            return 0;
          }
          local_9c = local_9c + 1;
          lVar3 = dev_call_slot1(iVar4,iVar2,iVar1,(long)&local_98);
          iVar1 = local_9c;
          if (lVar3 == 0) {
            cdb_c_error(s_unable_to_write_memory_004d33f0);
            return 0;
          }
          local_9c = local_9c + 1;
          lVar3 = dev_call_slot1(iVar4,iVar2,iVar1,cur_dev + 0x1c);
          if (lVar3 == 0) {
            cdb_c_error(s_unable_to_write_memory_004d33f0);
            return 0;
          }
          local_98 = local_9c;
          iVar2 = *(int *)((int)*(void **)((int)result_node + 0x10) + 0x20);
          if ((iVar2 == 8) || (iVar2 == 9)) {
            local_20 = 4;
            type_size(*(void **)((int)result_node + 0x10),local_40);
            local_9c = local_9c + local_34;
            local_84 = local_98;
            iVar2 = dev_write_reg(iVar4,local_70,local_78,&local_84);
            if (iVar2 == 0) {
              cdb_c_error(s_unable_to_write_register_a1_004d4df4);
              return 0;
            }
            iVar2 = cdb_default_space();
            *(int *)(*(int *)((int)result_node + 0x10) + 0x10) = iVar2;
            *(int *)(*(int *)((int)result_node + 0x10) + 0xc) = local_84;
          }
          push_args_56000(*(void **)((int)func_node + 0x14),&local_9c);
          dbg_resolve_symbol(s_dummy_call_004d4de8,local_68);
          local_88 = local_54;
          iVar2 = dev_write_reg(iVar4,local_74,local_6c,&local_88);
          if (iVar2 == 0) {
            cdb_c_error(s_unable_to_write_register_pc_004d4dcc);
            return 0;
          }
          iVar2 = *(int *)((int)func_node + 0x10);
          if ((*(short *)(iVar2 + 0x3c) == 1) &&
             (((byte)*(undefined4 *)(iVar2 + 0x20) & 0x30) == 0x20)) {
            local_7c = *(undefined4 *)(iVar2 + 0x18);
          }
          else {
            local_7c = *(undefined4 *)(iVar2 + 0xc);
          }
          lVar3 = dev_call_slot1(iVar4,0,local_88 + 1,(long)&local_7c);
          if (lVar3 == 0) {
            cdb_c_error(s_unable_to_write_memory_004d33f0);
            return 0;
          }
          iVar2 = dev_write_reg(iVar4,local_8c,local_80,&local_98);
          if (iVar2 == 0) {
            cdb_c_error(s_unable_to_write_register_r0_004d4db0);
            return 0;
          }
          iVar4 = dev_write_reg(iVar4,local_90,local_94,&local_9c);
          if (iVar4 == 0) {
            cdb_c_error(s_unable_to_write_register_r6_004d4d94);
            return 0;
          }
          return 1;
        }
      }
    }
  }
  cdb_internal_error(0x4d413c,0x84f);
  return 0;
}


/* ==== call_setup_56100 @ 00479210 ==== */

int __cdecl call_setup_56100(void *func_node,void *result_node)

{
  int iVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  int local_98;
  int local_94;
  int local_90;
  long local_8c;
  int local_88;
  int local_84;
  undefined4 local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  undefined1 local_68 [20];
  int local_54;
  undefined1 local_40 [12];
  uint local_34;
  undefined4 local_20;
  
  local_88 = 0;
  local_94 = 0;
  iVar4 = *(int *)(cur_dev + 4);
  iVar1 = cdb_default_space();
  if (iVar1 == 3) {
    iVar1 = 2;
  }
  lVar2 = periph_find_reg(iVar4,&DAT_004b2940,&local_7c,&local_8c);
  if (lVar2 != 0) {
    lVar2 = periph_find_reg(iVar4,&DAT_004b294c,&local_74,&local_6c);
    if (lVar2 != 0) {
      lVar2 = periph_find_reg(iVar4,&DAT_004a8a6c,&local_70,&local_78);
      if (lVar2 != 0) {
        lVar2 = periph_call(iVar4,local_7c,local_8c,(long)&local_98);
        if (lVar2 == 0) {
          cdb_c_error(s_unable_to_read_register_r2_004d4e64);
          return 0;
        }
        iVar3 = *(int *)((int)*(void **)((int)result_node + 0x10) + 0x20);
        if ((iVar3 == 8) || (iVar3 == 9)) {
          local_20 = 4;
          type_size(*(void **)((int)result_node + 0x10),local_40);
          local_84 = local_98;
          local_98 = local_98 + local_34;
          local_88 = ~local_34 + 1;
          iVar3 = dev_write_reg(iVar4,local_70,local_78,&local_84);
          if (iVar3 == 0) {
            cdb_c_error(s_unable_to_write_register_a1_004d4df4);
            return 0;
          }
          iVar3 = cdb_default_space();
          *(int *)(*(int *)((int)result_node + 0x10) + 0x10) = iVar3;
          *(int *)(*(int *)((int)result_node + 0x10) + 0xc) = local_84;
        }
        iVar3 = local_98;
        local_98 = local_98 + 1;
        lVar2 = dev_call_slot1(iVar4,iVar1,iVar3,cur_dev + 0x1c);
        if (lVar2 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        local_94 = local_98;
        push_args_56000(*(void **)((int)func_node + 0x14),&local_98);
        local_94 = ~((local_98 - local_94) + 1U) + 1;
        dbg_resolve_symbol(s_dummy_call_004d4de8,local_68);
        local_90 = local_54;
        iVar1 = dev_write_reg(iVar4,local_74,local_6c,&local_90);
        if (iVar1 == 0) {
          cdb_c_error(s_unable_to_write_register_pc_004d4dcc);
          return 0;
        }
        iVar1 = *(int *)((int)func_node + 0x10);
        if ((*(short *)(iVar1 + 0x3c) == 1) &&
           (((byte)*(undefined4 *)(iVar1 + 0x20) & 0x30) == 0x20)) {
          local_80 = *(undefined4 *)(iVar1 + 0x18);
        }
        else {
          local_80 = *(undefined4 *)(iVar1 + 0xc);
        }
        lVar2 = dev_call_slot1(iVar4,0,local_90 + 1,(long)&local_80);
        if (lVar2 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        lVar2 = dev_call_slot1(iVar4,0,local_90 + 3,(long)&local_94);
        if (lVar2 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        lVar2 = dev_call_slot1(iVar4,0,local_90 + 7,(long)&local_88);
        if (lVar2 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        iVar4 = dev_write_reg(iVar4,local_7c,local_8c,&local_98);
        if (iVar4 == 0) {
          cdb_c_error(s_unable_to_write_register_r2_004d4e48);
          return 0;
        }
        return 1;
      }
    }
  }
  cdb_internal_error(0x4d413c,0x8cb);
  return 0;
}


/* ==== call_setup_56800 @ 00479550 ==== */

int __cdecl call_setup_56800(void *func_node,void *result_node)

{
  int iVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  int local_98;
  int local_94;
  int local_90;
  long local_8c;
  int local_88;
  int local_84;
  undefined4 local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  undefined1 local_68 [20];
  int local_54;
  undefined1 local_40 [12];
  uint local_34;
  undefined4 local_20;
  
  local_88 = 0;
  local_94 = 0;
  iVar4 = *(int *)(cur_dev + 4);
  iVar1 = cdb_default_space();
  if (iVar1 == 3) {
    iVar1 = 2;
  }
  lVar2 = periph_find_reg(iVar4,&DAT_004b2940,&local_7c,&local_8c);
  if (lVar2 != 0) {
    lVar2 = periph_find_reg(iVar4,&DAT_004b294c,&local_74,&local_6c);
    if (lVar2 != 0) {
      lVar2 = periph_find_reg(iVar4,&DAT_004a8a6c,&local_70,&local_78);
      if (lVar2 != 0) {
        lVar2 = periph_call(iVar4,local_7c,local_8c,(long)&local_98);
        if (lVar2 == 0) {
          cdb_c_error(s_unable_to_read_register_r2_004d4e64);
          return 0;
        }
        iVar3 = *(int *)((int)*(void **)((int)result_node + 0x10) + 0x20);
        if ((iVar3 == 8) || (iVar3 == 9)) {
          local_20 = 4;
          type_size(*(void **)((int)result_node + 0x10),local_40);
          local_84 = local_98;
          local_98 = local_98 + local_34;
          local_88 = ~local_34 + 1;
          iVar3 = dev_write_reg(iVar4,local_70,local_78,&local_84);
          if (iVar3 == 0) {
            cdb_c_error(s_unable_to_write_register_a1_004d4df4);
            return 0;
          }
          iVar3 = cdb_default_space();
          *(int *)(*(int *)((int)result_node + 0x10) + 0x10) = iVar3;
          *(int *)(*(int *)((int)result_node + 0x10) + 0xc) = local_84;
        }
        iVar3 = local_98;
        local_98 = local_98 + 1;
        lVar2 = dev_call_slot1(iVar4,iVar1,iVar3,cur_dev + 0x1c);
        if (lVar2 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        local_94 = local_98;
        push_args_56000(*(void **)((int)func_node + 0x14),&local_98);
        local_94 = ~((local_98 - local_94) + 1U) + 1;
        dbg_resolve_symbol(s_dummy_call_004d4de8,local_68);
        local_90 = local_54;
        iVar1 = dev_write_reg(iVar4,local_74,local_6c,&local_90);
        if (iVar1 == 0) {
          cdb_c_error(s_unable_to_write_register_pc_004d4dcc);
          return 0;
        }
        iVar1 = *(int *)((int)func_node + 0x10);
        if ((*(short *)(iVar1 + 0x3c) == 1) &&
           (((byte)*(undefined4 *)(iVar1 + 0x20) & 0x30) == 0x20)) {
          local_80 = *(undefined4 *)(iVar1 + 0x18);
        }
        else {
          local_80 = *(undefined4 *)(iVar1 + 0xc);
        }
        lVar2 = dev_call_slot1(iVar4,0,local_90 + 1,(long)&local_80);
        if (lVar2 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        lVar2 = dev_call_slot1(iVar4,0,local_90 + 3,(long)&local_94);
        if (lVar2 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        lVar2 = dev_call_slot1(iVar4,0,local_90 + 7,(long)&local_88);
        if (lVar2 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        iVar4 = dev_write_reg(iVar4,local_7c,local_8c,&local_98);
        if (iVar4 == 0) {
          cdb_c_error(s_unable_to_write_register_r2_004d4e48);
          return 0;
        }
        return 1;
      }
    }
  }
  cdb_internal_error(0x4d413c,0x94a);
  return 0;
}


/* ==== call_setup_56300 @ 00479890 ==== */

int __cdecl call_setup_56300(void *func_node,void *result_node)

{
  int iVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  int local_98;
  int local_94;
  int local_90;
  long local_8c;
  int local_88;
  int local_84;
  undefined4 local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  undefined1 local_68 [20];
  int local_54;
  undefined1 local_40 [12];
  uint local_34;
  undefined4 local_20;
  
  local_88 = 0;
  local_94 = 0;
  iVar4 = *(int *)(cur_dev + 4);
  iVar1 = cdb_default_space();
  if (iVar1 == 3) {
    iVar1 = 2;
  }
  lVar2 = periph_find_reg(iVar4,&DAT_004b2930,&local_7c,&local_8c);
  if (lVar2 != 0) {
    lVar2 = periph_find_reg(iVar4,&DAT_004b292c,&local_70,&local_78);
    if (lVar2 != 0) {
      lVar2 = periph_find_reg(iVar4,&DAT_004b294c,&local_74,&local_6c);
      if (lVar2 != 0) {
        lVar2 = periph_call(iVar4,local_7c,local_8c,(long)&local_98);
        if (lVar2 == 0) {
          cdb_c_error(s_unable_to_read_register_r6_004d4e10);
          return 0;
        }
        iVar3 = *(int *)((int)*(void **)((int)result_node + 0x10) + 0x20);
        if ((iVar3 == 8) || (iVar3 == 9)) {
          local_20 = 4;
          type_size(*(void **)((int)result_node + 0x10),local_40);
          local_84 = local_98;
          local_98 = local_98 + local_34;
          local_88 = ~local_34 + 1;
          iVar3 = dev_write_reg(iVar4,local_70,local_78,&local_84);
          if (iVar3 == 0) {
            cdb_c_error(s_unable_to_write_register_r7_004d4e80);
            return 0;
          }
          iVar3 = cdb_default_space();
          *(int *)(*(int *)((int)result_node + 0x10) + 0x10) = iVar3;
          *(int *)(*(int *)((int)result_node + 0x10) + 0xc) = local_84;
        }
        iVar3 = local_98;
        local_98 = local_98 + 1;
        lVar2 = dev_call_slot1(iVar4,iVar1,iVar3,cur_dev + 0x1c);
        if (lVar2 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        local_94 = local_98;
        push_args_56300(*(void **)((int)func_node + 0x14),&local_98);
        local_94 = ~((local_98 - local_94) + 1U) + 1;
        dbg_resolve_symbol(s_dummy_call_004d4de8,local_68);
        local_90 = local_54;
        iVar1 = dev_write_reg(iVar4,local_74,local_6c,&local_90);
        if (iVar1 == 0) {
          cdb_c_error(s_unable_to_write_register_pc_004d4dcc);
          return 0;
        }
        iVar1 = *(int *)((int)func_node + 0x10);
        if ((*(short *)(iVar1 + 0x3c) == 1) &&
           (((byte)*(undefined4 *)(iVar1 + 0x20) & 0x30) == 0x20)) {
          local_80 = *(undefined4 *)(iVar1 + 0x18);
        }
        else {
          local_80 = *(undefined4 *)(iVar1 + 0xc);
        }
        lVar2 = dev_call_slot1(iVar4,0,local_90 + 1,(long)&local_80);
        if (lVar2 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        lVar2 = dev_call_slot1(iVar4,0,local_90 + 3,(long)&local_94);
        if (lVar2 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        lVar2 = dev_call_slot1(iVar4,0,local_90 + 6,(long)&local_88);
        if (lVar2 == 0) {
          cdb_c_error(s_unable_to_write_memory_004d33f0);
          return 0;
        }
        iVar4 = dev_write_reg(iVar4,local_7c,local_8c,&local_98);
        if (iVar4 == 0) {
          cdb_c_error(s_unable_to_write_register_r6_004d4d94);
          return 0;
        }
        return 1;
      }
    }
  }
  cdb_internal_error(0x4d413c,0x9ca);
  return 0;
}


/* ==== call_setup_96000 @ 00479bd0 ==== */

int __cdecl call_setup_96000(void *func_node,void *result_node)

{
  int iVar1;
  int iVar2;
  long lVar3;
  int iVar4;
  int local_9c;
  int local_98;
  long local_94;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  long local_80;
  undefined4 local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  undefined1 local_68 [20];
  int local_54;
  undefined1 local_40 [12];
  int local_34;
  undefined4 local_20;
  
  iVar4 = *(int *)(cur_dev + 4);
  iVar2 = cdb_default_space();
  if (iVar2 == 3) {
    iVar2 = 2;
  }
  lVar3 = periph_find_reg(iVar4,&DAT_004b2948,&local_8c,&local_80);
  if (lVar3 != 0) {
    lVar3 = periph_find_reg(iVar4,&DAT_004b2930,&local_90,&local_94);
    if (lVar3 != 0) {
      lVar3 = periph_find_reg(iVar4,&DAT_004b292c,&local_70,&local_78);
      if (lVar3 != 0) {
        lVar3 = periph_find_reg(iVar4,&DAT_004b294c,&local_74,&local_6c);
        if (lVar3 != 0) {
          lVar3 = periph_call(iVar4,local_8c,local_80,(long)&local_98);
          if (lVar3 == 0) {
            cdb_c_error(s_unable_to_read_register_r0_004d4e2c);
            return 0;
          }
          lVar3 = periph_call(iVar4,local_90,local_94,(long)&local_9c);
          iVar1 = local_9c;
          if (lVar3 == 0) {
            cdb_c_error(s_unable_to_read_register_r6_004d4e10);
            return 0;
          }
          local_9c = local_9c + 1;
          lVar3 = dev_call_slot1(iVar4,iVar2,iVar1,(long)&local_98);
          iVar1 = local_9c;
          if (lVar3 == 0) {
            cdb_c_error(s_unable_to_write_memory_004d33f0);
            return 0;
          }
          local_9c = local_9c + 1;
          lVar3 = dev_call_slot1(iVar4,iVar2,iVar1,cur_dev + 0x1c);
          if (lVar3 == 0) {
            cdb_c_error(s_unable_to_write_memory_004d33f0);
            return 0;
          }
          local_98 = local_9c;
          iVar2 = *(int *)((int)*(void **)((int)result_node + 0x10) + 0x20);
          if ((iVar2 == 8) || (iVar2 == 9)) {
            local_20 = 4;
            type_size(*(void **)((int)result_node + 0x10),local_40);
            local_9c = local_9c + local_34;
            local_84 = local_98;
            iVar2 = dev_write_reg(iVar4,local_70,local_78,&local_84);
            if (iVar2 == 0) {
              cdb_c_error(s_unable_to_write_register_r7_004d4e80);
              return 0;
            }
            iVar2 = cdb_default_space();
            *(int *)(*(int *)((int)result_node + 0x10) + 0x10) = iVar2;
            *(int *)(*(int *)((int)result_node + 0x10) + 0xc) = local_84;
          }
          push_args_96000(*(void **)((int)func_node + 0x14),&local_9c);
          dbg_resolve_symbol(s_dummy_call_004d4de8,local_68);
          local_88 = local_54;
          iVar2 = dev_write_reg(iVar4,local_74,local_6c,&local_88);
          if (iVar2 == 0) {
            cdb_c_error(s_unable_to_write_register_pc_004d4dcc);
            return 0;
          }
          iVar2 = *(int *)((int)func_node + 0x10);
          if ((*(short *)(iVar2 + 0x3c) == 1) &&
             (((byte)*(undefined4 *)(iVar2 + 0x20) & 0x30) == 0x20)) {
            local_7c = *(undefined4 *)(iVar2 + 0x18);
          }
          else {
            local_7c = *(undefined4 *)(iVar2 + 0xc);
          }
          lVar3 = dev_call_slot1(iVar4,0,local_88 + 1,(long)&local_7c);
          if (lVar3 == 0) {
            cdb_c_error(s_unable_to_write_memory_004d33f0);
            return 0;
          }
          iVar2 = dev_write_reg(iVar4,local_8c,local_80,&local_98);
          if (iVar2 == 0) {
            cdb_c_error(s_unable_to_write_register_r0_004d4db0);
            return 0;
          }
          iVar4 = dev_write_reg(iVar4,local_90,local_94,&local_9c);
          if (iVar4 == 0) {
            cdb_c_error(s_unable_to_write_register_r6_004d4d94);
            return 0;
          }
          return 1;
        }
      }
    }
  }
  cdb_internal_error(0x4d413c,0xa4b);
  return 0;
}


/* ==== push_args_56000 @ 00479f40 ==== */

void __cdecl push_args_56000(void *arglist,int *sp)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 local_80 [6];
  int local_68;
  int local_64;
  undefined4 local_5c;
  undefined2 local_44;
  undefined1 local_40 [12];
  int local_34;
  
  iVar1 = cdb_default_space();
  for (; arglist != (int *)0x0; arglist = *(void **)((int)arglist + 4)) {
    cdb_load_value(*(void **)(*(int *)arglist + 0x10));
    local_68 = *sp;
    puVar3 = *(undefined4 **)(*(int *)arglist + 0x10);
    puVar4 = local_80;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    local_44 = 1;
    local_5c = 2;
    local_64 = iVar1;
    cdb_store_value(local_80);
    type_size(local_80,local_40);
    *sp = *sp + local_34;
  }
  return;
}


/* ==== push_args_56300 @ 00479fe0 ==== */

void __cdecl push_args_56300(void *arglist,int *sp)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 local_80 [6];
  int local_68;
  int local_64;
  int local_60;
  undefined4 local_5c;
  undefined2 local_44;
  undefined1 local_40 [12];
  int local_34;
  
  iVar5 = 0;
  iVar2 = cdb_default_space();
  pvVar3 = arglist;
  iVar7 = 0;
  if (arglist != (void *)0x0) {
    do {
      iVar6 = iVar7;
      pvVar3 = *(void **)((int)pvVar3 + 4);
      iVar7 = iVar6 + 1;
      iVar1 = iVar7;
    } while (pvVar3 != (void *)0x0);
    for (; arglist != (int *)0x0; arglist = *(void **)((int)arglist + 4)) {
      iVar5 = iVar5 + 1;
      cdb_load_value(*(void **)(*(int *)arglist + 0x10));
      puVar8 = *(undefined4 **)(*(int *)arglist + 0x10);
      puVar9 = local_80;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar9 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar9 = puVar9 + 1;
      }
      if ((((iVar5 == iVar6) || (iVar5 == iVar7)) && (local_60 != 8)) && (local_60 != 9)) {
        local_44 = 1;
        local_5c = 4;
        local_68 = iVar1 + -1;
      }
      else {
        local_44 = 1;
        local_68 = *sp;
        local_5c = 2;
        local_64 = iVar2;
        type_size(local_80,local_40);
        *sp = *sp + local_34;
      }
      cdb_store_value(local_80);
      iVar1 = iVar1 + -1;
    }
  }
  return;
}


/* ==== push_args_96000 @ 0047a0f0 ==== */

void __cdecl push_args_96000(void *arglist,int *sp)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int local_90;
  undefined4 local_80 [6];
  int local_68;
  int local_64;
  int local_60;
  undefined4 local_5c;
  undefined2 local_44;
  undefined1 local_40 [12];
  int local_34;
  
  iVar4 = 0;
  iVar1 = cdb_default_space();
  pvVar2 = arglist;
  iVar6 = 0;
  if (arglist != (void *)0x0) {
    do {
      iVar5 = iVar6;
      pvVar2 = *(void **)((int)pvVar2 + 4);
      iVar6 = iVar5 + 1;
    } while (pvVar2 != (void *)0x0);
    if (arglist != (void *)0x0) {
      local_90 = iVar6 * 3;
      do {
        local_90 = local_90 + -3;
        iVar4 = iVar4 + 1;
        cdb_load_value(*(void **)(*(int *)arglist + 0x10));
        puVar7 = *(undefined4 **)(*(int *)arglist + 0x10);
        puVar8 = local_80;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar8 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar8 = puVar8 + 1;
        }
        if ((((iVar4 == iVar5) || (iVar4 == iVar6)) && (local_60 != 8)) && (local_60 != 9)) {
          local_44 = 1;
          local_5c = 4;
          local_68 = local_90;
        }
        else {
          local_44 = 1;
          local_68 = *sp;
          local_5c = 2;
          local_64 = iVar1;
          type_size(local_80,local_40);
          *sp = *sp + local_34;
        }
        cdb_store_value(local_80);
        arglist = *(void **)((int)arglist + 4);
      } while (arglist != (int *)0x0);
    }
  }
  return;
}


/* ==== eval_array_to_ptr @ 0047a200 ==== */

int __cdecl eval_array_to_ptr(void *pchild,int op,void *result_node,int do_eval)

{
  int iVar1;
  
  if (((byte)*(undefined4 *)((int)*(void **)(*(int *)pchild + 0x10) + 0x20) & 0x30) != 0x30) {
    return 0;
  }
  if (do_eval == 0) {
    return 1;
  }
  iVar1 = array_to_ptr_value(*(void **)(*(int *)pchild + 0x10),*(void **)((int)result_node + 0x10));
  return iVar1;
}


/* ==== array_to_ptr_value @ 0047a240 ==== */

int __cdecl array_to_ptr_value(void *value,void *out)

{
  int iVar1;
  ulong local_4;
  
  iVar1 = *(int *)((int)value + 0x24);
  if ((iVar1 == 2) || (iVar1 == 3)) {
    *(undefined4 *)((int)out + 0x10) = *(undefined4 *)((int)value + 0x1c);
    *(undefined4 *)((int)out + 0xc) = *(undefined4 *)((int)value + 0x18);
    return 1;
  }
  if ((iVar1 != 1) && (iVar1 != 9)) {
    cdb_internal_error(0x4d413c,0xbb5);
    return 0;
  }
  iVar1 = cdb_frame_slot(*(int *)((int)value + 0x1c),*(int *)((int)value + 0x18),(int *)&value,
                         &local_4);
  if (iVar1 == 0) {
    return 0;
  }
  *(void **)((int)out + 0x10) = value;
  *(ulong *)((int)out + 0xc) = local_4;
  return 1;
}


/* ==== eval_func_to_ptr @ 0047a2d0 ==== */

int __cdecl eval_func_to_ptr(void *pchild,int op,void *result_node,int do_eval)

{
  int iVar1;
  
  if (((byte)*(undefined4 *)((int)*(void **)(*(int *)pchild + 0x10) + 0x20) & 0x30) != 0x20) {
    return 0;
  }
  if (do_eval == 0) {
    return 1;
  }
  iVar1 = func_to_ptr_value(*(void **)(*(int *)pchild + 0x10),*(void **)((int)result_node + 0x10));
  return iVar1;
}


/* ==== func_to_ptr_value @ 0047a310 ==== */

int __cdecl func_to_ptr_value(void *value,void *out)

{
  int iVar1;
  ulong local_4;
  
  iVar1 = *(int *)((int)value + 0x24);
  if ((iVar1 == 2) || (iVar1 == 3)) {
    *(undefined4 *)((int)out + 0x10) = *(undefined4 *)((int)value + 0x1c);
    *(undefined4 *)((int)out + 0xc) = *(undefined4 *)((int)value + 0x18);
    return 1;
  }
  if ((iVar1 != 1) && (iVar1 != 9)) {
    cdb_internal_error(0x4d413c,0xbe2);
    return 0;
  }
  iVar1 = cdb_frame_slot(*(int *)((int)value + 0x1c),*(int *)((int)value + 0x18),(int *)&value,
                         &local_4);
  if (iVar1 == 0) {
    return 0;
  }
  *(void **)((int)out + 0x10) = value;
  *(ulong *)((int)out + 0xc) = local_4;
  return 1;
}


/* ==== copy_node_type @ 0047a3a0 ==== */

void __cdecl copy_node_type(void *dst_node,void *src_node)

{
  int iVar1;
  int iVar2;
  
  *(undefined4 *)(*(int *)((int)dst_node + 0x10) + 0x20) =
       *(undefined4 *)(*(int *)((int)src_node + 0x10) + 0x20);
  *(undefined4 *)(*(int *)((int)dst_node + 0x10) + 0x28) =
       *(undefined4 *)(*(int *)((int)src_node + 0x10) + 0x28);
  *(undefined4 *)(*(int *)((int)dst_node + 0x10) + 0x24) = 0;
  iVar1 = *(int *)((int)src_node + 0x10);
  iVar2 = *(int *)((int)dst_node + 0x10);
  *(undefined4 *)(iVar2 + 0x2c) = *(undefined4 *)(iVar1 + 0x2c);
  *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar1 + 0x30);
  *(undefined4 *)(iVar2 + 0x34) = *(undefined4 *)(iVar1 + 0x34);
  *(undefined4 *)(iVar2 + 0x38) = *(undefined4 *)(iVar1 + 0x38);
  *(undefined2 *)(*(int *)((int)dst_node + 0x10) + 0x3c) = 0;
  return;
}


/* ==== usual_arith_conv @ 0047a400 ==== */

void __cdecl usual_arith_conv(void *pnode1,void *pnode2)

{
  void *node;
  int iVar1;
  int iVar2;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  undefined4 extraout_EAX_01;
  undefined4 extraout_EAX_02;
  undefined4 extraout_EAX_03;
  undefined4 extraout_EAX_04;
  undefined4 extraout_EAX_05;
  undefined4 extraout_EAX_06;
  undefined4 extraout_EAX_07;
  undefined4 extraout_EAX_08;
  undefined4 extraout_EAX_09;
  undefined4 extraout_EAX_10;
  undefined4 extraout_EAX_11;
  undefined4 extraout_EAX_12;
  undefined4 extraout_EAX_13;
  undefined4 extraout_EAX_14;
  undefined4 extraout_EAX_15;
  undefined4 extraout_EAX_16;
  undefined4 extraout_EAX_17;
  undefined4 extraout_EAX_18;
  undefined4 extraout_EAX_19;
  undefined4 extraout_EAX_20;
  undefined4 extraout_EAX_21;
  undefined4 extraout_EAX_22;
  undefined4 extraout_EAX_23;
  undefined4 extraout_EAX_24;
  undefined4 extraout_EAX_25;
  undefined4 extraout_EAX_26;
  
  integral_promote(pnode1);
  integral_promote(pnode2);
  node = *(void **)pnode1;
  iVar1 = *(int *)(*(int *)((int)node + 0x10) + 0x20);
  if ((iVar1 == 0x10005) ||
     (iVar2 = *(int *)(*(int *)(*(int *)pnode2 + 0x10) + 0x20), iVar2 == 0x10005)) {
    make_cast_node(0x10005,node);
    *(undefined4 *)pnode1 = extraout_EAX_25;
    make_cast_node(0x10005,*(void **)pnode2);
    *(undefined4 *)pnode2 = extraout_EAX_26;
    return;
  }
  if ((iVar1 == 0x10004) || (iVar2 == 0x10004)) {
    make_cast_node(0x10004,node);
    *(undefined4 *)pnode1 = extraout_EAX_23;
    make_cast_node(0x10004,*(void **)pnode2);
    *(undefined4 *)pnode2 = extraout_EAX_24;
    return;
  }
  if ((iVar1 == 0x10003) || (iVar2 == 0x10003)) {
    make_cast_node(0x10003,node);
    *(undefined4 *)pnode1 = extraout_EAX_21;
    make_cast_node(0x10003,*(void **)pnode2);
    *(undefined4 *)pnode2 = extraout_EAX_22;
    return;
  }
  if ((iVar1 == 0x10002) || (iVar2 == 0x10002)) {
    make_cast_node(0x10002,node);
    *(undefined4 *)pnode1 = extraout_EAX_19;
    make_cast_node(0x10002,*(void **)pnode2);
    *(undefined4 *)pnode2 = extraout_EAX_20;
    return;
  }
  if ((iVar1 == 0x10001) || (iVar2 == 0x10001)) {
    make_cast_node(0x10001,node);
    *(undefined4 *)pnode1 = extraout_EAX_17;
    make_cast_node(0x10001,*(void **)pnode2);
    *(undefined4 *)pnode2 = extraout_EAX_18;
    return;
  }
  if ((iVar1 == 0x10000) || (iVar2 == 0x10000)) {
    make_cast_node(0x10000,node);
    *(undefined4 *)pnode1 = extraout_EAX_15;
    make_cast_node(0x10000,*(void **)pnode2);
    *(undefined4 *)pnode2 = extraout_EAX_16;
    return;
  }
  if ((iVar1 == 7) || (iVar2 == 7)) {
    make_cast_node(7,node);
    *(undefined4 *)pnode1 = extraout_EAX_13;
    make_cast_node(7,*(void **)pnode2);
    *(undefined4 *)pnode2 = extraout_EAX_14;
    return;
  }
  if ((iVar1 == 6) || (iVar2 == 6)) {
    make_cast_node(6,node);
    *(undefined4 *)pnode1 = extraout_EAX_11;
    make_cast_node(6,*(void **)pnode2);
    *(undefined4 *)pnode2 = extraout_EAX_12;
    return;
  }
  if ((iVar1 == 0xf) || (iVar2 == 0xf)) {
    make_cast_node(0xf,node);
    *(undefined4 *)pnode1 = extraout_EAX_09;
    make_cast_node(0xf,*(void **)pnode2);
    *(undefined4 *)pnode2 = extraout_EAX_10;
    return;
  }
  if (iVar1 == 5) {
LAB_0047a500:
    if (iVar2 == 5) goto LAB_0047a50f;
  }
  else {
    if (iVar2 != 5) goto LAB_0047a50f;
    if (iVar1 == 5) goto LAB_0047a500;
  }
  if ((iVar1 == 0xe) || (iVar2 == 0xe)) {
    if (cdb_arch != 0x2c6) {
      make_cast_node(5,node);
      *(undefined4 *)pnode1 = extraout_EAX_05;
      make_cast_node(5,*(void **)pnode2);
      *(undefined4 *)pnode2 = extraout_EAX_06;
      return;
    }
    make_cast_node(0xf,node);
    *(undefined4 *)pnode1 = extraout_EAX_07;
    make_cast_node(0xf,*(void **)pnode2);
    *(undefined4 *)pnode2 = extraout_EAX_08;
    return;
  }
LAB_0047a50f:
  if ((iVar1 == 5) || (iVar2 == 5)) {
    make_cast_node(5,node);
    *(undefined4 *)pnode1 = extraout_EAX_03;
    make_cast_node(5,*(void **)pnode2);
    *(undefined4 *)pnode2 = extraout_EAX_04;
    return;
  }
  if ((iVar1 != 0xe) && (iVar2 != 0xe)) {
    make_cast_node(4,node);
    *(undefined4 *)pnode1 = extraout_EAX;
    make_cast_node(4,*(void **)pnode2);
    *(undefined4 *)pnode2 = extraout_EAX_00;
    return;
  }
  make_cast_node(0xe,node);
  *(undefined4 *)pnode1 = extraout_EAX_01;
  make_cast_node(0xe,*(void **)pnode2);
  *(undefined4 *)pnode2 = extraout_EAX_02;
  return;
}


/* ==== integral_promote @ 0047a710 ==== */

void __cdecl integral_promote(void *pnode)

{
  void *node;
  int iVar1;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  
  node = *(void **)pnode;
  iVar1 = *(int *)(*(int *)((int)node + 0x10) + 0x20);
  if (((byte)iVar1 & 0x30) != 0x10) {
    if ((iVar1 == 2) || (iVar1 == 3)) {
      make_cast_node(4,node);
      *(undefined4 *)pnode = extraout_EAX_00;
    }
    else if ((iVar1 == 0xc) || (iVar1 == 0xd)) {
      make_cast_node(0xe,node);
      *(undefined4 *)pnode = extraout_EAX;
      return;
    }
  }
  return;
}


/* ==== make_cast_node @ 0047a760 ==== */

void __cdecl make_cast_node(int kind,void *node)

{
  int extraout_EAX;
  int *extraout_EAX_00;
  
  if (*(int *)(*(int *)((int)node + 0x10) + 0x20) == kind) {
    return;
  }
  new_node();
  if (extraout_EAX == 0) {
    return;
  }
  new_node();
  if (extraout_EAX_00 == (int *)0x0) {
    return;
  }
  *extraout_EAX_00 = extraout_EAX;
  extraout_EAX_00[2] = (int)node;
  extraout_EAX_00[1] = 0;
  extraout_EAX_00[3] = 0x13f;
  *(int *)(*(int *)(extraout_EAX + 0x10) + 0x20) = kind;
  *(int *)(extraout_EAX_00[4] + 0x20) = kind;
  *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x24) = 0;
  *(undefined4 *)(extraout_EAX_00[4] + 0x24) = 0;
  *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x28) = 0;
  *(undefined4 *)(extraout_EAX_00[4] + 0x28) = 0;
  *(undefined2 *)(*(int *)(extraout_EAX + 0x10) + 0x3c) = 0;
  *(undefined2 *)(extraout_EAX_00[4] + 0x3c) = 0;
  return;
}


/* ==== clone_tree @ 0047a7f0 ==== */

void __cdecl clone_tree(void *node)

{
  undefined4 *extraout_EAX;
  undefined4 extraout_EAX_00;
  undefined4 extraout_EAX_01;
  undefined4 extraout_EAX_02;
  undefined4 extraout_EAX_03;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  new_node();
  if (extraout_EAX == (undefined4 *)0x0) {
    return;
  }
  extraout_EAX[3] = *(undefined4 *)((int)node + 0xc);
  puVar2 = *(undefined4 **)((int)node + 0x10);
  puVar3 = (undefined4 *)extraout_EAX[4];
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  if (*(void **)((int)node + 0x14) == (void *)0x0) {
    extraout_EAX[5] = 0;
  }
  else {
    clone_arglist(*(void **)((int)node + 0x14));
    extraout_EAX[5] = extraout_EAX_00;
  }
  if (*(void **)node == (void *)0x0) {
    *extraout_EAX = 0;
  }
  else {
    clone_tree(*(void **)node);
    *extraout_EAX = extraout_EAX_01;
  }
  if (*(void **)((int)node + 4) == (void *)0x0) {
    extraout_EAX[1] = 0;
  }
  else {
    clone_tree(*(void **)((int)node + 4));
    extraout_EAX[1] = extraout_EAX_02;
  }
  if (*(void **)((int)node + 8) != (void *)0x0) {
    clone_tree(*(void **)((int)node + 8));
    extraout_EAX[2] = extraout_EAX_03;
    return;
  }
  extraout_EAX[2] = 0;
  return;
}


/* ==== clone_arglist @ 0047a8a0 ==== */

void __cdecl clone_arglist(void *arglist)

{
  undefined4 *extraout_EAX;
  undefined4 *extraout_EAX_00;
  undefined4 extraout_EAX_01;
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)0x0;
  puVar1 = (undefined4 *)0x0;
  for (; arglist != (undefined4 *)0x0; arglist = *(void **)((int)arglist + 4)) {
    if (puVar1 == (undefined4 *)0x0) {
      cdb_malloc(8);
      puVar1 = extraout_EAX;
      puVar2 = extraout_EAX;
    }
    else {
      cdb_malloc(8);
      puVar2[1] = extraout_EAX_00;
      puVar2 = extraout_EAX_00;
    }
    puVar2[1] = 0;
    clone_tree(*(void **)arglist);
    *puVar2 = extraout_EAX_01;
  }
  return;
}


