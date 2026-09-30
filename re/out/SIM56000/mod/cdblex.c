/* ==== yyerror @ 004804c0 ==== */

int yyerror(char *msg)

{
  if (yytext_buf == '\0') {
    sprintf(&yyerror_buf,s_premature_end_of_C_expression_004d6c04);
    cdb_error(&yyerror_buf);
    return 0;
  }
  sprintf(&yyerror_buf,s__s_near__s_004d6bf8,msg,&yytext_buf);
  cdb_error(&yyerror_buf);
  return 0;
}


/* ==== mk_type_node @ 00480520 ==== */

void __cdecl mk_type_node(int kind)

{
  int extraout_EAX;
  
  new_node();
  if (extraout_EAX == 0) {
    return;
  }
  *(int *)(*(int *)(extraout_EAX + 0x10) + 0x20) = kind;
  return;
}


/* ==== mk_binary_node @ 00480540 ==== */

void __cdecl mk_binary_node(void *lhs,int op,void *rhs)

{
  undefined4 *result_node;
  int iVar1;
  
  if ((lhs != (void *)0x0) && (rhs != (void *)0x0)) {
    new_node();
    if (result_node != (undefined4 *)0x0) {
      result_node[3] = op;
      iVar1 = eval_binary(&lhs,&rhs,op,result_node,0);
      if (iVar1 == 0) {
        return;
      }
      result_node[1] = 0;
      *result_node = lhs;
      result_node[2] = rhs;
      result_node[5] = 0;
      return;
    }
  }
  return;
}


/* ==== mk_unary_node @ 004805b0 ==== */

void __cdecl mk_unary_node(int op,void *child)

{
  undefined4 *result_node;
  int iVar1;
  
  if (child == (void *)0x0) {
    return;
  }
  new_node();
  if (result_node == (undefined4 *)0x0) {
    return;
  }
  result_node[3] = op;
  iVar1 = eval_unary(&child,op,result_node,0);
  if (iVar1 == 0) {
    return;
  }
  *result_node = 0;
  result_node[1] = child;
  result_node[2] = 0;
  result_node[5] = 0;
  return;
}


/* ==== mk_ternary_node @ 00480610 ==== */

void __cdecl mk_ternary_node(void *cond,void *a,void *b)

{
  undefined4 *result_node;
  int iVar1;
  
  if (((cond != (void *)0x0) && (b != (void *)0x0)) && (a != (void *)0x0)) {
    new_node();
    if (result_node != (undefined4 *)0x0) {
      result_node[3] = 0x123;
      iVar1 = eval_ternary(&cond,&a,&b,result_node,0);
      if (iVar1 == 0) {
        return;
      }
      *result_node = cond;
      result_node[1] = a;
      result_node[2] = b;
      result_node[5] = 0;
      return;
    }
  }
  return;
}


/* ==== mk_call_node @ 00480690 ==== */

void __cdecl mk_call_node(void *func,void *arglist)

{
  undefined4 *extraout_EAX;
  int iVar1;
  undefined4 *extraout_EAX_00;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined1 local_1c [16];
  undefined4 *local_c;
  
  if (func == (void *)0x0) {
    return;
  }
  *(void **)((int)func + 0x14) = arglist;
  cdb_malloc(0x40);
  if (extraout_EAX != (undefined4 *)0x0) {
    local_c = extraout_EAX;
    iVar1 = eval_unary(&func,0x145,local_1c,0);
    if (iVar1 != 0) {
      new_node();
      if (extraout_EAX_00 == (undefined4 *)0x0) {
        return;
      }
      *extraout_EAX_00 = 0;
      extraout_EAX_00[2] = 0;
      extraout_EAX_00[1] = func;
      extraout_EAX_00[3] = 0x145;
      extraout_EAX_00[5] = 0;
      puVar2 = local_c;
      puVar3 = (undefined4 *)extraout_EAX_00[4];
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
    }
    cdb_free(local_c);
    return;
  }
  return;
}


/* ==== mk_arglist @ 00480740 ==== */

void __cdecl mk_arglist(void *node)

{
  undefined4 *extraout_EAX;
  
  cdb_malloc(8);
  *extraout_EAX = node;
  extraout_EAX[1] = 0;
  return;
}


/* ==== arglist_append @ 00480760 ==== */

void __cdecl arglist_append(void *list,void *node)

{
  undefined4 *extraout_EAX;
  
  cdb_malloc(8);
  *extraout_EAX = node;
  extraout_EAX[1] = list;
  return;
}


/* ==== track_list_cell @ 00480780 ==== */

void __cdecl track_list_cell(void *p)

{
  undefined4 *extraout_EAX;
  
  cdb_malloc(8);
  if (extraout_EAX != (undefined4 *)0x0) {
    *extraout_EAX = p;
    extraout_EAX[1] = tmp_list_cells;
    tmp_list_cells = extraout_EAX;
  }
  return;
}


/* ==== mk_member_dot @ 004807b0 ==== */

void __cdecl mk_member_dot(void *base,char *name)

{
  int iVar1;
  char *va1;
  int extraout_EAX;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 *extraout_EAX_00;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  char local_100 [256];
  
  if ((base != (void *)0x0) && (name != (char *)0x0)) {
    iVar1 = *(int *)(*(int *)((int)base + 0x10) + 0x20);
    if ((iVar1 != 8) && (iVar1 != 9)) {
      sprintf(local_100,s_requesting_member___s__in_item_t_004d6c44,name);
      cdb_error(local_100);
      return;
    }
    iVar1 = cdb_find_member(*(int *)(*(int *)((int)base + 0x10) + 0x28),name);
    if (iVar1 == -1) {
      va1 = s_structure_004d3198;
      if (*(int *)(*(int *)((int)base + 0x10) + 0x20) != 8) {
        va1 = s_union_004d31ac;
      }
      sprintf(local_100,s___s__is_not_a_member_of_the__s_004d6c24,name,va1);
      cdb_error(local_100);
      return;
    }
    new_node();
    if (extraout_EAX != 0) {
      iVar2 = iVar1 * 0x20;
      *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0xc) =
           *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar2);
      *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x10) = 0;
      *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x14) = 0;
      *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) =
           *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 0x14 + iVar2);
      *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x24) =
           *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 0x18 + iVar2);
      iVar2 = *(int *)(extraout_EAX + 0x10);
      uVar3 = *(uint *)(iVar2 + 0x20) & 0x1000f;
      if (((uVar3 == 8) || (uVar3 == 9)) || (uVar3 == 10)) {
        *(undefined4 *)(iVar2 + 0x28) =
             *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + (iVar1 + 1) * 0x20);
      }
      else {
        *(undefined4 *)(iVar2 + 0x28) = 0;
      }
      iVar2 = *(int *)(extraout_EAX + 0x10);
      if (((byte)*(undefined4 *)(iVar2 + 0x20) & 0x30) == 0x30) {
        iVar4 = *(int *)(cur_sim + 0x3fe0) + (iVar1 + 1) * 0x20;
        iVar5 = *(int *)(iVar4 + 0xc);
        if (iVar5 == 0) {
          iVar5 = 1;
        }
        *(int *)(iVar2 + 0x2c) = iVar5;
        iVar2 = *(int *)(iVar4 + 0x10);
        if (iVar2 == 0) {
          iVar2 = 1;
        }
        *(int *)(*(int *)(extraout_EAX + 0x10) + 0x30) = iVar2;
        iVar2 = *(int *)(iVar4 + 0x14);
        if (iVar2 == 0) {
          iVar2 = 1;
        }
        *(int *)(*(int *)(extraout_EAX + 0x10) + 0x34) = iVar2;
        iVar2 = *(int *)(iVar4 + 0x18);
        if (iVar2 == 0) {
          iVar2 = 1;
        }
        *(int *)(*(int *)(extraout_EAX + 0x10) + 0x38) = iVar2;
      }
      else {
        *(undefined4 *)(iVar2 + 0x2c) = 1;
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x30) = 1;
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x34) = 1;
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x38) = 1;
      }
      new_node();
      if (extraout_EAX_00 != (undefined4 *)0x0) {
        extraout_EAX_00[1] = 0;
        *extraout_EAX_00 = base;
        extraout_EAX_00[2] = extraout_EAX;
        extraout_EAX_00[3] = 0x2e;
        extraout_EAX_00[5] = 0;
        puVar6 = *(undefined4 **)(extraout_EAX + 0x10);
        puVar7 = (undefined4 *)extraout_EAX_00[4];
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar7 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar7 = puVar7 + 1;
        }
        if (*(int *)(*(int *)(extraout_EAX + 0x10) + 0x24) == 0x12) {
          *(undefined4 *)(extraout_EAX_00[4] + 0x24) = 0x12;
          *(int *)(extraout_EAX_00[4] + 0x28) = iVar1;
          *(undefined2 *)(extraout_EAX_00[4] + 0x3c) = 1;
          return;
        }
        *(undefined4 *)(extraout_EAX_00[4] + 0x24) = 2;
        *(undefined2 *)(extraout_EAX_00[4] + 0x3c) = 1;
        return;
      }
    }
  }
  return;
}


/* ==== mk_member_arrow @ 00480a10 ==== */

void __cdecl mk_member_arrow(void *base,char *name)

{
  uint uVar1;
  int iVar2;
  char *va1;
  int extraout_EAX;
  int iVar3;
  int iVar4;
  undefined4 *extraout_EAX_00;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  char local_100 [256];
  
  if ((base != (void *)0x0) && (name != (char *)0x0)) {
    uVar1 = *(uint *)(*(int *)((int)base + 0x10) + 0x20);
    if (((byte)uVar1 & 0x30) != 0x10) {
      sprintf(local_100,s_attempting_to_use__>_operator_on_004d6c84);
      cdb_error(local_100);
      return;
    }
    uVar1 = uVar1 & 0x1000f;
    if ((uVar1 != 8) && (uVar1 != 9)) {
      sprintf(local_100,s_requesting_member___s__in_item_t_004d6c44,name);
      cdb_error(local_100);
      return;
    }
    iVar2 = cdb_find_member(*(int *)(*(int *)((int)base + 0x10) + 0x28),name);
    if (iVar2 == -1) {
      va1 = s_structure_004d3198;
      if ((*(uint *)(*(int *)((int)base + 0x10) + 0x20) & 0x1000f) != 8) {
        va1 = s_union_004d31ac;
      }
      sprintf(local_100,s___s__is_not_a_member_of_the__s_004d6c24,name,va1);
      cdb_error(local_100);
      return;
    }
    new_node();
    if (extraout_EAX != 0) {
      iVar3 = iVar2 * 0x20;
      *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0xc) =
           *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar3);
      *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x10) = 0;
      *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x14) = 0;
      *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) =
           *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 0x14 + iVar3);
      *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x24) =
           *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 0x18 + iVar3);
      iVar3 = *(int *)(extraout_EAX + 0x10);
      uVar1 = *(uint *)(iVar3 + 0x20) & 0x1000f;
      if (((uVar1 == 8) || (uVar1 == 9)) || (uVar1 == 10)) {
        *(undefined4 *)(iVar3 + 0x28) =
             *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + (iVar2 + 1) * 0x20);
      }
      else {
        *(undefined4 *)(iVar3 + 0x28) = 0;
      }
      iVar3 = *(int *)(extraout_EAX + 0x10);
      if (((byte)*(undefined4 *)(iVar3 + 0x20) & 0x30) == 0x30) {
        iVar4 = *(int *)(cur_sim + 0x3fe0) + (iVar2 + 1) * 0x20;
        iVar5 = *(int *)(iVar4 + 0xc);
        if (iVar5 == 0) {
          iVar5 = 1;
        }
        *(int *)(iVar3 + 0x2c) = iVar5;
        iVar3 = *(int *)(iVar4 + 0x10);
        if (iVar3 == 0) {
          iVar3 = 1;
        }
        *(int *)(*(int *)(extraout_EAX + 0x10) + 0x30) = iVar3;
        iVar3 = *(int *)(iVar4 + 0x14);
        if (iVar3 == 0) {
          iVar3 = 1;
        }
        *(int *)(*(int *)(extraout_EAX + 0x10) + 0x34) = iVar3;
        iVar3 = *(int *)(iVar4 + 0x18);
        if (iVar3 == 0) {
          iVar3 = 1;
        }
        *(int *)(*(int *)(extraout_EAX + 0x10) + 0x38) = iVar3;
      }
      else {
        *(undefined4 *)(iVar3 + 0x2c) = 1;
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x30) = 1;
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x34) = 1;
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x38) = 1;
      }
      new_node();
      if (extraout_EAX_00 != (undefined4 *)0x0) {
        extraout_EAX_00[1] = 0;
        *extraout_EAX_00 = base;
        extraout_EAX_00[2] = extraout_EAX;
        extraout_EAX_00[3] = 0x139;
        extraout_EAX_00[5] = 0;
        puVar6 = *(undefined4 **)(extraout_EAX + 0x10);
        puVar7 = (undefined4 *)extraout_EAX_00[4];
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar7 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar7 = puVar7 + 1;
        }
        if (*(int *)(*(int *)(extraout_EAX + 0x10) + 0x24) == 0x12) {
          *(undefined4 *)(extraout_EAX_00[4] + 0x24) = 0x12;
          *(int *)(extraout_EAX_00[4] + 0x28) = iVar2;
          *(undefined2 *)(extraout_EAX_00[4] + 0x3c) = 1;
          return;
        }
        *(undefined4 *)(extraout_EAX_00[4] + 0x24) = 2;
        *(undefined2 *)(extraout_EAX_00[4] + 0x3c) = 1;
        return;
      }
    }
  }
  return;
}


/* ==== yylex @ 00480cb0 ==== */

int yylex(void)

{
  char cVar1;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  undefined4 extraout_EAX_01;
  undefined4 extraout_EAX_02;
  undefined4 extraout_EAX_03;
  char *extraout_EAX_04;
  int iVar2;
  int extraout_EAX_05;
  int extraout_EAX_06;
  char *extraout_EAX_07;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  DAT_005046bc = yy_scan();
  if (DAT_005046bc < 0) {
    return 0;
  }
  do {
    switch(DAT_005046bc) {
    case 0:
      iVar2 = yywrap();
      if (iVar2 != 0) {
        return 0;
      }
    default:
      DAT_005046bc = yy_scan();
      if (DAT_005046bc < 0) {
        return 0;
      }
      break;
    case 1:
      lex_int_const(&DAT_005057c2,0x10);
      DAT_005059c0 = (char *)extraout_EAX;
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x13b;
    case 2:
      lex_int_const(&yytext_buf,8);
      DAT_005059c0 = (char *)extraout_EAX_00;
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x13b;
    case 3:
      lex_int_const(&yytext_buf,10);
      DAT_005059c0 = (char *)extraout_EAX_01;
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x13b;
    case 4:
      lex_float_const(&yytext_buf);
      DAT_005059c0 = (char *)extraout_EAX_02;
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x13d;
    case 5:
      lex_char_const(&yytext_buf);
      DAT_005059c0 = (char *)extraout_EAX_03;
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x13c;
    case 6:
      uVar3 = 0xffffffff;
      pcVar5 = &yytext_buf;
      goto code_r0x00480de8;
    case 7:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      iVar2 = keyword_lookup(&yytext_buf);
      if (iVar2 != -1) {
        return *(int *)(&DAT_004d6cc4 + iVar2 * 8);
      }
      lex_symbol_name(&yytext_buf);
      DAT_005059c0 = (char *)extraout_EAX_05;
      if (extraout_EAX_05 != 0) {
        return 0x13e;
      }
      lex_typedef_name(&yytext_buf);
      DAT_005059c0 = (char *)extraout_EAX_06;
      if (extraout_EAX_06 != 0) {
        return 0x10f;
      }
      uVar3 = 0xffffffff;
      pcVar5 = &yytext_buf;
      goto code_r0x00480eb7;
    case 8:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x139;
    case 9:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x136;
    case 10:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x137;
    case 0xb:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x134;
    case 0xc:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x135;
    case 0xd:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x132;
    case 0xe:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x133;
    case 0xf:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x130;
    case 0x10:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x131;
    case 0x11:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x12f;
    case 0x12:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x12e;
    case 0x13:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x124;
    case 0x14:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x125;
    case 0x15:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x126;
    case 0x16:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x127;
    case 0x17:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x128;
    case 0x18:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x129;
    case 0x19:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x12a;
    case 0x1a:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 299;
    case 0x1b:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 300;
    case 0x1c:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x12d;
    case 0x1d:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return 0x116;
    case 0x1f:
      lex_token_col = (lex_pos - DAT_005057bc) + 1;
      return (int)yytext_buf;
    }
  } while( true );
  while( true ) {
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    if (cVar1 == '\0') break;
code_r0x00480eb7:
    if (uVar3 == 0) break;
  }
  cdb_malloc(~uVar3);
  DAT_005059c0 = extraout_EAX_07;
  if (extraout_EAX_07 != (char *)0x0) {
    uVar3 = 0xffffffff;
    pcVar5 = &yytext_buf;
    do {
      pcVar6 = pcVar5;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar6 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar6;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar5 = pcVar6 + -uVar3;
    pcVar6 = extraout_EAX_07;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar6 = pcVar6 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar6 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    }
  }
  return 0x112;
  while( true ) {
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    if (cVar1 == '\0') break;
code_r0x00480de8:
    if (uVar3 == 0) break;
  }
  cdb_malloc(~uVar3 - 1);
  DAT_005059c0 = extraout_EAX_04;
  if (extraout_EAX_04 != (char *)0x0) {
    uVar3 = 0xffffffff;
    pcVar5 = &DAT_005057c1;
    do {
      pcVar6 = pcVar5;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar6 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar6;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar5 = pcVar6 + -uVar3;
    pcVar6 = extraout_EAX_04;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar6 = pcVar6 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar6 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    }
  }
  lex_token_col = (lex_pos - DAT_005057bc) + 1;
  return 0x147;
}


/* ==== lex_init @ 00481220 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl lex_init(char *text)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  char cVar4;
  int iVar5;
  
  lex_token_col = 0;
  cVar4 = '\0';
  if (*text != '{') {
    return 0;
  }
  iVar3 = 0;
  iVar5 = 0;
  cVar1 = text[1];
  _DAT_005051ec = 0;
  pcVar2 = text;
  while (cVar1 != '\0') {
    if (cVar1 != ' ') {
      iVar5 = iVar5 + 1;
      _DAT_005051ec = iVar3;
      cVar4 = cVar1;
    }
    (&lex_input_line)[iVar3] = cVar1;
    iVar3 = iVar3 + 1;
    cVar1 = pcVar2[2];
    pcVar2 = pcVar2 + 1;
  }
  (&lex_input_line)[_DAT_005051ec] = 0;
  lex_pos = 0;
  if (cVar4 == '}') {
    if (1 < iVar5) {
      return 1;
    }
    cdb_error(s_empty_C_expression_004d7a0c);
    return 0;
  }
  cdb_error(s_incomplete_C_expression_004d7a20);
  lex_token_col = (int)(pcVar2 + 1) - (int)text;
  return 0;
}


/* ==== lex_get_column @ 004812d0 ==== */

int lex_get_column(void)

{
  return lex_token_col;
}


/* ==== yywrap @ 004812e0 ==== */

int yywrap(void)

{
  return 1;
}


/* ==== keyword_lookup @ 004812f0 ==== */

int __cdecl keyword_lookup(char *word)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  bool bVar8;
  
  iVar5 = 0;
  iVar4 = 0x21;
  do {
    iVar7 = (iVar4 + iVar5) / 2;
    pbVar6 = *(byte **)(iVar7 * 8 + 0x4d6cc0);
    pbVar2 = (byte *)word;
    do {
      bVar1 = *pbVar2;
      bVar8 = bVar1 < *pbVar6;
      if (bVar1 != *pbVar6) {
LAB_00481334:
        iVar3 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
        goto LAB_00481339;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar8 = bVar1 < pbVar6[1];
      if (bVar1 != pbVar6[1]) goto LAB_00481334;
      pbVar2 = pbVar2 + 2;
      pbVar6 = pbVar6 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_00481339:
    if (iVar3 < 0) {
      iVar4 = iVar7 + -1;
    }
    else {
      if (iVar3 < 1) {
        return iVar7;
      }
      iVar5 = iVar7 + 1;
    }
    if (iVar4 < iVar5) {
      return -1;
    }
  } while( true );
}


/* ==== lex_typedef_name @ 00481360 ==== */

void __cdecl lex_typedef_name(char *name)

{
  int iVar1;
  int iVar2;
  int extraout_EAX;
  
  iVar2 = cdb_lookup_typedef(name);
  if (iVar2 == -1) {
    return;
  }
  new_node();
  if (extraout_EAX == 0) {
    return;
  }
  iVar1 = *(int *)(cur_sim + 0x3fe0);
  *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) =
       *(undefined4 *)(iVar2 * 0x20 + 0x14 + iVar1);
  *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x28) =
       *(undefined4 *)((iVar2 + 1) * 0x20 + iVar1);
  *(undefined2 *)(*(int *)(extraout_EAX + 0x10) + 0x3c) = 0;
  return;
}


/* ==== lex_symbol_name @ 004813c0 ==== */

void __cdecl lex_symbol_name(char *name)

{
  int iVar1;
  int extraout_EAX;
  
  iVar1 = cdb_lookup_enum_member(name);
  if (iVar1 == -1) {
    return;
  }
  new_node();
  if (extraout_EAX == 0) {
    return;
  }
  *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0xc) =
       *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar1 * 0x20);
  *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x10) = 0;
  *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 0xb;
  *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x24) = 1;
  *(undefined2 *)(*(int *)(extraout_EAX + 0x10) + 0x3c) = 0;
  *(int *)(*(int *)(extraout_EAX + 0x10) + 0x28) = iVar1;
  return;
}


/* ==== lex_int_const @ 00481440 ==== */

void __cdecl lex_int_const(char *text,int base)

{
  int *piVar1;
  uint *puVar2;
  bool bVar3;
  bool bVar4;
  int extraout_EAX;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  new_node();
  if (extraout_EAX == 0) {
    return;
  }
  *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0xc) = 0;
  bVar3 = false;
  bVar4 = false;
  *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x10) = 0;
  while( true ) {
    if (__mb_cur_max < 2) {
      uVar5 = (byte)_pctype[*text * 2] & 0x80;
    }
    else {
      uVar5 = _isctype((int)*text,0x80);
    }
    iVar7 = *(int *)(extraout_EAX + 0x10);
    if (uVar5 == 0) break;
    *(int *)(iVar7 + 0xc) = base * *(int *)(iVar7 + 0xc);
    *(int *)(*(int *)(extraout_EAX + 0x10) + 0x10) =
         base * *(int *)(*(int *)(extraout_EAX + 0x10) + 0x10);
    if (__mb_cur_max < 2) {
      uVar5 = (byte)_pctype[*text * 2] & 4;
    }
    else {
      uVar5 = _isctype((int)*text,4);
    }
    if (uVar5 == 0) {
      iVar7 = *(int *)(extraout_EAX + 0x10);
      iVar6 = tolower((int)*text);
      *(int *)(iVar7 + 0xc) = *(int *)(iVar7 + 0xc) + iVar6 + -0x57;
    }
    else {
      piVar1 = (int *)(*(int *)(extraout_EAX + 0x10) + 0xc);
      *piVar1 = *piVar1 + *text + -0x30;
    }
    iVar7 = *(int *)(extraout_EAX + 0x10);
    uVar5 = *(uint *)(iVar7 + 0xc) & ~cdb_word_mask;
    if (uVar5 != 0) {
      *(uint *)(iVar7 + 0x10) = *(int *)(iVar7 + 0x10) + (uVar5 >> ((byte)cdb_word_bits & 0x1f));
      puVar2 = (uint *)(*(int *)(extraout_EAX + 0x10) + 0xc);
      *puVar2 = *puVar2 & cdb_word_mask;
    }
    text = text + 1;
  }
  *(uint *)(iVar7 + 0xc) = *(uint *)(iVar7 + 0xc) & cdb_word_mask;
  *(uint *)(*(int *)(extraout_EAX + 0x10) + 0x10) =
       *(uint *)(*(int *)(extraout_EAX + 0x10) + 0x10) & cdb_word_mask;
  uVar5 = *(uint *)(*(int *)(extraout_EAX + 0x10) + 0x10);
  if (uVar5 == 0) {
    if (((cdb_sign_bit & *(uint *)(*(int *)(extraout_EAX + 0x10) + 0xc)) == 0) ||
       ((base == 10 && (bVar3 = true, cdb_arch != 0x2c6)))) goto LAB_004815ad;
  }
  else {
    bVar3 = true;
    if ((uVar5 & cdb_sign_bit) == 0) goto LAB_004815ad;
  }
  bVar4 = true;
LAB_004815ad:
  iVar7 = tolower((int)*text);
  if (iVar7 == 0x6c) {
    bVar3 = true;
    text = text + 1;
  }
  else if ((*text != '\0') && (iVar7 = tolower((int)text[1]), iVar7 == 0x6c)) {
    bVar3 = true;
  }
  iVar7 = tolower((int)*text);
  if ((iVar7 == 0x75) || ((*text != '\0' && (iVar7 = tolower((int)text[1]), iVar7 == 0x75)))) {
    bVar4 = true;
  }
  if (bVar3) {
    if (bVar4) {
      *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 0xf;
    }
    else {
      *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 5;
    }
  }
  else if (bVar4) {
    *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 0xe;
  }
  else {
    *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 4;
  }
  *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x24) = 0;
  *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x28) = 0;
  *(undefined2 *)(*(int *)(extraout_EAX + 0x10) + 0x3c) = 0;
  return;
}


/* ==== lex_float_const @ 00481670 ==== */

void __cdecl lex_float_const(char *text)

{
  char cVar1;
  int extraout_EAX;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  double dVar5;
  
  new_node();
  *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x24) = 0;
  *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x28) = 0;
  *(undefined2 *)(*(int *)(extraout_EAX + 0x10) + 0x3c) = 0;
  if (extraout_EAX == 0) {
    return;
  }
  errno = 0;
  dVar5 = atof(text);
  **(double **)(extraout_EAX + 0x10) = dVar5;
  if (errno == 0x22) {
    cdb_error(s_float_constant_exceeds_range_004d7a38);
    return;
  }
  uVar3 = 0xffffffff;
  pcVar4 = text;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  iVar2 = tolower((int)text[~uVar3 - 2]);
  if (iVar2 == 0x66) {
    *(float *)(*(double **)(extraout_EAX + 0x10) + 1) = (float)**(double **)(extraout_EAX + 0x10);
    *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 6;
  }
  else {
    *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 7;
  }
  if ((cdb_arch == 0x2c5) || (cdb_arch == 0x2c8)) {
    value_double_to_dsp(*(void **)(extraout_EAX + 0x10));
  }
  else if ((((cdb_arch == 0x2c7) || (cdb_arch == 0x2ca)) || (cdb_arch == 0x2cb)) ||
          (cdb_arch == 0x2c9)) {
    *(float *)(*(double **)(extraout_EAX + 0x10) + 1) = (float)**(double **)(extraout_EAX + 0x10);
    return;
  }
  return;
}


/* ==== lex_char_const @ 00481760 ==== */

void __cdecl lex_char_const(char *text)

{
  char cVar1;
  int extraout_EAX;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  
  new_node();
  if (extraout_EAX != 0) {
    *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x10) = 0;
    if (text[1] == '\\') {
      pcVar3 = text + 2;
      switch(text[2]) {
      case '\"':
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0xc) = 0x22;
        break;
      default:
        iVar4 = 0;
        while( true ) {
          if (__mb_cur_max < 2) {
            uVar2 = (byte)_pctype[*pcVar3 * 2] & 4;
          }
          else {
            uVar2 = _isctype((int)*pcVar3,4);
          }
          if (uVar2 == 0) break;
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
          iVar4 = cVar1 + -0x30 + iVar4 * 8;
        }
        *(int *)(*(int *)(extraout_EAX + 0x10) + 0xc) = iVar4;
        break;
      case '\'':
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0xc) = 0x27;
        break;
      case '?':
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0xc) = 0x3f;
        break;
      case '\\':
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0xc) = 0x5c;
        break;
      case 'a':
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0xc) = 7;
        break;
      case 'b':
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0xc) = 8;
        break;
      case 'f':
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0xc) = 0xc;
        break;
      case 'n':
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0xc) = 10;
        break;
      case 'r':
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0xc) = 0xd;
        break;
      case 't':
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0xc) = 9;
        break;
      case 'v':
        *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0xc) = 0xb;
        break;
      case 'x':
        iVar4 = 0;
        pcVar3 = text + 3;
        while( true ) {
          if (__mb_cur_max < 2) {
            uVar2 = (byte)_pctype[*pcVar3 * 2] & 0x80;
          }
          else {
            uVar2 = _isctype((int)*pcVar3,0x80);
          }
          if (uVar2 == 0) break;
          if (__mb_cur_max < 2) {
            uVar2 = (byte)_pctype[*pcVar3 * 2] & 4;
          }
          else {
            uVar2 = _isctype((int)*pcVar3,4);
          }
          if (uVar2 == 0) {
            cVar1 = *pcVar3;
            pcVar3 = pcVar3 + 1;
            iVar4 = iVar4 * 0x10 + -0x57 + (int)cVar1;
          }
          else {
            cVar1 = *pcVar3;
            pcVar3 = pcVar3 + 1;
            iVar4 = iVar4 * 0x10 + -0x30 + (int)cVar1;
          }
        }
        *(int *)(*(int *)(extraout_EAX + 0x10) + 0xc) = iVar4;
      }
    }
    else {
      *(int *)(*(int *)(extraout_EAX + 0x10) + 0xc) = (int)text[1];
    }
    *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) = 4;
    *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x24) = 0;
    *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x28) = 0;
    *(undefined2 *)(*(int *)(extraout_EAX + 0x10) + 0x3c) = 0;
    return;
  }
  return;
}


/* ==== yy_scan @ 004819e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int yy_scan(void)

{
  char *pcVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined *puVar6;
  int *piVar7;
  char *pcVar8;
  
  DAT_00504ed4 = 1;
  if (DAT_005051e8 == 0) {
    DAT_005046b8 = &yytext_buf;
  }
  else {
    DAT_005051e8 = 0;
    DAT_005046b8 = &yytext_buf + (int)DAT_005057bc;
  }
LAB_00481a24:
  piVar7 = &DAT_005046c8;
  _DAT_005050e0 = PTR_PTR_004d78e4;
  puVar4 = (undefined4 *)PTR_PTR_004d78e4;
  if (DAT_004d7970 == 10) {
    puVar4 = (undefined4 *)(PTR_PTR_004d78e4 + 0xc);
  }
LAB_00481a3b:
  do {
    puVar6 = (undefined *)*puVar4;
    if (((puVar6 == &DAT_004d6fe8) && (DAT_00504ed4 == 0)) &&
       ((_DAT_005050dc = (undefined4 *)puVar4[1], _DAT_005050dc == (undefined4 *)0x0 ||
        ((undefined *)*_DAT_005050dc == &DAT_004d6fe8)))) goto LAB_00481bc8;
    DAT_005051f0 = (int)(char)(&lex_input_line)[lex_pos];
    *DAT_005046b8 = (&lex_input_line)[lex_pos];
    DAT_00504ed4 = 0;
    while( true ) {
      _DAT_00504ec8 = puVar6;
      if ((int)puVar6 < 0x4d6fe9) {
        if (0x4d6fe7 < (int)puVar6) goto LAB_00481b32;
        _DAT_00504ec8 = &DAT_004d6fe8 + ((int)&DAT_004d6fe8 - (int)puVar6 >> 1) * 2;
        pcVar8 = _DAT_00504ec8 + DAT_005051f0 * 2;
        if ((PTR_DAT_004d78e0 < pcVar8) || ((undefined4 *)(&DAT_004d7520 + *pcVar8 * 0xc) != puVar4)
           ) {
          pcVar8 = _DAT_00504ec8 + (char)(&DAT_004d78e8)[DAT_005051f0] * 2;
          if (pcVar8 <= PTR_DAT_004d78e0) {
            puVar2 = (undefined4 *)(&DAT_004d7520 + *pcVar8 * 0xc);
            goto joined_r0x00481b30;
          }
          goto LAB_00481b32;
        }
        puVar4 = (undefined4 *)(&DAT_004d7520 + pcVar8[1] * 0xc);
        if (puVar4 == (undefined4 *)&DAT_004d7520) goto LAB_00481ba8;
        DAT_005046b8 = DAT_005046b8 + 1;
        lex_pos = lex_pos + 1;
        *piVar7 = (int)puVar4;
        piVar7 = piVar7 + 1;
        goto LAB_00481a3b;
      }
      pcVar8 = puVar6 + DAT_005051f0 * 2;
      if (pcVar8 <= PTR_DAT_004d78e0) break;
LAB_00481b32:
      puVar4 = (undefined4 *)puVar4[1];
      if ((puVar4 == (undefined4 *)0x0) || (puVar6 = (undefined *)*puVar4, puVar6 == &DAT_004d6fe8))
      {
LAB_00481ba8:
        (&lex_input_line)[lex_pos] = *DAT_005046b8;
        goto LAB_00481bc8;
      }
    }
    puVar2 = (undefined4 *)(&DAT_004d7520 + *pcVar8 * 0xc);
joined_r0x00481b30:
    if (puVar2 != puVar4) goto LAB_00481b32;
    puVar4 = (undefined4 *)(&DAT_004d7520 + pcVar8[1] * 0xc);
    if (puVar4 == (undefined4 *)&DAT_004d7520) break;
    DAT_005046b8 = DAT_005046b8 + 1;
    lex_pos = lex_pos + 1;
    *piVar7 = (int)puVar4;
    piVar7 = piVar7 + 1;
  } while( true );
  (&lex_input_line)[lex_pos] = *DAT_005046b8;
LAB_00481bc8:
  pcVar8 = DAT_005046b8;
  if (&DAT_005046c8 < piVar7) {
    do {
      piVar7 = piVar7 + -1;
      *pcVar8 = '\0';
      pcVar8 = DAT_005046b8 + -1;
      DAT_005046b8 = pcVar8;
      if (((*piVar7 != 0) && (DAT_005046c0 = *(int **)(*piVar7 + 8), DAT_005046c0 != (int *)0x0)) &&
         (0 < *DAT_005046c0)) {
        _DAT_00504ecc = piVar7;
        if ((&DAT_005051f8)[*DAT_005046c0] != '\0') {
          iVar5 = int_list_contains(*(int **)(*piVar7 + 8),-*DAT_005046c0);
          iVar3 = lex_pos;
          while ((lex_pos = iVar3, iVar5 != 1 && ((int *)((int)&DAT_005046c8 + 1) <= piVar7))) {
            piVar7 = piVar7 + -1;
            lex_pos = iVar3 + -1;
            (&DAT_005050e7)[iVar3] = *DAT_005046b8;
            DAT_005046b8 = DAT_005046b8 + -1;
            iVar5 = int_list_contains(*(int **)(*piVar7 + 8),-*DAT_005046c0);
            iVar3 = lex_pos;
          }
        }
        DAT_004d7970 = (int)*DAT_005046b8;
        DAT_005057bc = DAT_005046b8 + -0x5057bf;
        _DAT_00504ed0 = piVar7;
        DAT_005046b8[1] = '\0';
        iVar3 = *DAT_005046c0;
        DAT_005046c0 = DAT_005046c0 + 1;
        return iVar3;
      }
      pcVar1 = &DAT_005050e7 + lex_pos;
      lex_pos = lex_pos + -1;
      *pcVar1 = *pcVar8;
    } while (&DAT_005046c8 < piVar7);
  }
  if (yytext_buf == '\0') {
    PTR_DAT_004d796c = &DAT_00504ed8;
    return 0;
  }
  DAT_005046b8 = &yytext_buf;
  yytext_buf = (&lex_input_line)[lex_pos];
  lex_pos = lex_pos + 1;
  DAT_004d7970 = (int)yytext_buf;
  goto LAB_00481a24;
}


/* ==== int_list_contains @ 00481d20 ==== */

int __cdecl int_list_contains(int *list,int value)

{
  int iVar1;
  
  if ((list != (int *)0x0) && (iVar1 = *list, iVar1 != 0)) {
    do {
      list = list + 1;
      if (iVar1 == value) {
        return 1;
      }
      iVar1 = *list;
    } while (iVar1 != 0);
    return 0;
  }
  return 0;
}


